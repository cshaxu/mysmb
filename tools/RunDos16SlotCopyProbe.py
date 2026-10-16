"""Qualify the neutral copy fixture with the unchanged owner DOSBox profile."""
import argparse
import hashlib
import os
from pathlib import Path
import shutil
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ("probe", "dosbox", "configuration", "output"):
        parser.add_argument("--"+name, type=Path, required=True)
    parser.add_argument("--expect-span-rejection", action="store_true")
    args = parser.parse_args()
    output = args.output.resolve()
    if not output.is_relative_to(Path(__file__).resolve().parents[1]/"build"):
        parser.error("Output must stay below build")
    output.mkdir(parents=True, exist_ok=True)
    digest = hashlib.sha256(args.configuration.read_bytes()).digest()
    shutil.copyfile(args.probe, output/"SPAN.EXE")
    for stale in ("COPY.LOG", "DONE", "REJECT", "FAILED"):
        (output/stale).unlink(missing_ok=True)
    (output/"RUN.BAT").write_text(
        "@echo off\nSPAN.EXE\nif errorlevel 2 goto failed\n"
        "if errorlevel 1 goto rejected\necho done>DONE\ngoto end\n"
        ":rejected\necho rejected>REJECT\ngoto end\n"
        ":failed\necho failed>FAILED\n:end\nexit\n")
    (output/"probe.conf").write_text(f'[autoexec]\nmount c "{output}"\nc:\nRUN.BAT\nexit\n')
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    environment = dict(os.environ, SDL_VIDEODRIVER="dummy", SDL_AUDIODRIVER="dummy")
    with (output/"host.log").open("w") as log:
        subprocess.run([str(args.dosbox), "-conf", str(args.configuration), "-conf", "probe.conf", "-noconsole"],
                       cwd=output, env=environment, startupinfo=startup, stdout=log,
                       stderr=subprocess.STDOUT, timeout=180, check=True)
    if hashlib.sha256(args.configuration.read_bytes()).digest() != digest:
        raise ValueError("DOSBox profile changed")
    if (output/"FAILED").exists():
        raise ValueError("Unexpected DOS fixture failure")
    if args.expect_span_rejection:
        if not (output/"REJECT").exists() or (output/"DONE").exists():
            raise ValueError("Old callback must reject the first17-row case")
        print("old_contract_span_rejection=1")
    else:
        if not (output/"DONE").exists() or (output/"REJECT").exists():
            raise ValueError("Valid full-span copy rejected")
        receipt = (output/"COPY.LOG").read_text().strip()
        if receipt != "valid=36 invalid=9 optional_second=1 exact=1":
            raise ValueError("Incomplete copy contract receipt")
        print(receipt)


if __name__ == "__main__":
    main()
