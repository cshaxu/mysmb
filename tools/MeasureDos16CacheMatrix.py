"""Run bounded, local-only DOS16 cache factorial diagnostics."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import statistics
import subprocess
import time

PROFILES = (0, 1, 2, 3, 6, 7)
SIZES = {1: 8192, 2: 63488, 4: 61440}
RECORD_BYTES = 32 + 2048 + 61440


def fields(line):
    return {k: int(v) for k, v in (part.split("=", 1) for part in line.split())}


def read_timing(path, mask):
    lines = path.read_text().splitlines()
    if len(lines) != 18:
        raise ValueError("Expected header,16frames and completion")
    header = fields(lines[0])
    if header["mask"] != mask or header["PIT_HZ"] != 1193182:
        raise ValueError("Wrong mask or PIT scale")
    rows = [fields(line) for line in lines[1:-1]]
    final = fields(lines[-1].removeprefix("done "))
    if (final["title"] != 8 or final["gameplay"] != 8 or final["submitted"] != 32
            or final["bytes"] != 32*61440):
        raise ValueError("Incomplete warmed route")
    if [r["phase"] for r in rows] != [0]*8 + [1]*8:
        raise ValueError("Wrong phase ordering")
    if any(r[key] < 0 or r[key] > r["raw_"+key]
           for r in rows for key in ("prepare", "compose", "publish")):
        raise ValueError("Invalid raw/calibrated clock costs")
    result = {"mask": mask, "clock_overhead_ticks": header["overhead"],
              "logical_ticks": final["ticks"], "submitted_frames": 32,
              "submitted_bytes": final["bytes"], "phases": {}}
    for phase, name in enumerate(("title", "gameplay")):
        subset = [r for r in rows if r["phase"] == phase]
        costs = {key: statistics.mean(r[key] for r in subset)*1000/1193182
                 for key in ("prepare", "compose", "publish", "raw_prepare", "raw_compose", "raw_publish")}
        costs["total"] = sum(costs[key] for key in ("prepare", "compose", "publish"))
        costs["raw_total"] = sum(costs[key] for key in ("raw_prepare", "raw_compose", "raw_publish"))
        result["phases"][name] = costs
    return result


def summarize(rows):
    profiles = {}
    for mask in sorted({row["mask"] for row in rows}):
        repeats = [row for row in rows if row["mask"] == mask]
        profiles[mask] = {"cache_bytes": sum(size for bit, size in SIZES.items() if mask & bit), "phases": {}}
        for phase in ("title", "gameplay"):
            metrics = {}
            for metric in repeats[0]["phases"][phase]:
                values = [r["phases"][phase][metric] for r in repeats]
                metrics[metric] = {"median": statistics.median(values), "min": min(values), "max": max(values)}
            profiles[mask]["phases"][phase] = metrics
    margins = []
    for bit, name in ((1, "A"), (2, "B"), (4, "C")):
        for without in PROFILES:
            with_cache = without | bit
            if without & bit or with_cache not in profiles or without not in profiles:
                continue
            pair = {"cache": name, "without": without, "with": with_cache,
                    "added_KiB": SIZES[bit]/1024, "phases": {}}
            for phase in ("title", "gameplay"):
                pair["phases"][phase] = {}
                for metric in ("prepare", "compose", "publish", "total", "raw_total"):
                    left = {r["repeat"]: r for r in rows if r["mask"] == without}
                    right = {r["repeat"]: r for r in rows if r["mask"] == with_cache}
                    saved = [left[i]["phases"][phase][metric]-right[i]["phases"][phase][metric]
                             for i in sorted(left.keys() & right.keys())]
                    pair["phases"][phase][metric+"_saved_ms"] = statistics.median(saved)
                    pair["phases"][phase][metric+"_saved_range"] = [min(saved), max(saved)]
                pair["phases"][phase]["saved_ms_per_KiB"] = pair["phases"][phase]["total_saved_ms"]/pair["added_KiB"]
            margins.append(pair)
    return {"profiles": profiles, "margins": margins}


def label(mask):
    return "".join(name for bit, name in ((1, "A"), (2, "B"), (4, "C")) if mask & bit) or "none"


def write_report(output, result):
    text = ["# DOS16 cache factorial timing", "",
            "Controlled warmed rendering costs, milliseconds per frame; not gameplay FPS.",
            "PIT boundary overhead is calibrated. File I/O, startup and pacing are excluded.", "",
            "| Profile | Cache KiB | Title total ms | Gameplay total ms |",
            "| --- | ---: | ---: | ---: |"]
    for mask, profile in result["profiles"].items():
        text.append(f"| {label(mask)} | {profile['cache_bytes']/1024:g} | "
                    f"{profile['phases']['title']['total']['median']:.3f} | "
                    f"{profile['phases']['gameplay']['total']['median']:.3f} |")
    text += ["", "Positive savings mean faster; negative savings mean slower.", "",
             "| Added | Context | Added KiB | Title saved ms | Gameplay saved ms | Gameplay ms/KiB |",
             "| --- | --- | ---: | ---: | ---: | ---: |"]
    for pair in result["margins"]:
        text.append(f"| {pair['cache']} | {label(pair['without'])} | {pair['added_KiB']:g} | "
                    f"{pair['phases']['title']['total_saved_ms']:+.3f} | "
                    f"{pair['phases']['gameplay']['total_saved_ms']:+.3f} | "
                    f"{pair['phases']['gameplay']['saved_ms_per_KiB']:+.4f} |")
    text += ["", "## Phase costs and repeat spread", "",
             "Three repeats; each phase is the mean of eight measured frames. Ranges below are repeat means.", "",
             "| Profile | Phase | Prepare ms | Compose ms | Publish ms | Total range ms | Raw total ms |",
             "| --- | --- | ---: | ---: | ---: | --- | ---: |"]
    for mask, profile in result["profiles"].items():
        for phase, costs in profile["phases"].items():
            text.append(f"| {label(mask)} | {phase} | {costs['prepare']['median']:.3f} | "
                        f"{costs['compose']['median']:.3f} | {costs['publish']['median']:.3f} | "
                        f"{costs['total']['min']:.3f} to {costs['total']['max']:.3f} | "
                        f"{costs['raw_total']['median']:.3f} |")
    text += ["", "## Paired timing sensitivity", "",
             "All profiles use the same bounded RAM-band composition/publication path.",
             "Raw costs retain PIT boundary overhead; calibrated costs subtract it.", "",
             "| Added | Context | Phase | Saved range ms | Raw saved ms |",
             "| --- | --- | --- | --- | ---: |"]
    for pair in result["margins"]:
        for phase, costs in pair["phases"].items():
            low, high = costs["total_saved_range"]
            text.append(f"| {pair['cache']} | {label(pair['without'])} | {phase} | "
                        f"{low:+.3f} to {high:+.3f} | {costs['raw_total_saved_ms']:+.3f} |")
    if all("approx_launch_to_done_seconds" in row for row in result["runs"]):
        intervals = [row["approx_launch_to_done_seconds"] for row in result["runs"]]
        text += ["", f"Approximate batch-launch-to-DONE intervals: {min(intervals):.3f} to {max(intervals):.3f} seconds.",
                 "These are filesystem timestamp intervals, not stopwatch samples or per-frame costs.",
                 "They include startup, game/audio work, warmup and file output; no pacing wait was requested."]
    (output/"report.md").write_text("\n".join(text)+"\n")


def finalize(output):
    result = json.loads((output/"matrix.json").read_text())
    rows = result["runs"]
    if sorted((r["mask"], r["repeat"]) for r in rows) != sorted((m, r) for m in PROFILES for r in range(3)):
        raise ValueError("Final qualification requires all6profiles and three repeats")
    if len({r["logical_ticks"] for r in rows}) != 1:
        raise ValueError("Different logical route lengths")
    reference = None
    for row in rows:
        directory = output/f"m{row['mask']:02x}r{row['repeat']}"
        measured = read_timing(directory/"TIME.LOG", row["mask"])
        if any(row[key] != value for key, value in measured.items()):
            raise ValueError("Summary differs from retained timing receipt")
        data = (directory/"FRAME.BIN").read_bytes()
        if len(data) != 16*RECORD_BYTES or (reference is not None and data != reference):
            raise ValueError("Final exact-output audit failed")
        reference = data
        # Older receipts did not wrap the process in a host stopwatch. Keep
        # their filesystem interval separate and explicitly approximate.
        if "host_process_seconds" not in row:
            row["approx_launch_to_done_seconds"] = ((directory/"DONE").stat().st_mtime_ns
                                                    -(directory/"RUN.BAT").stat().st_mtime_ns)/1e9
    result.update(summarize(rows))
    if {name: sum(p["cache"] == name for p in result["margins"]) for name in "ABC"} != dict(A=3, B=2, C=2):
        raise ValueError("Incomplete marginal-pair universe")
    result["complete"] = True
    result["exact_frame_records"] = len(rows)*16
    result["raw_output_bytes"] = len(rows)*16*RECORD_BYTES
    (output/"matrix.json").write_text(json.dumps(result, indent=2)+"\n")
    write_report(output, result)
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--probe", type=Path, required=True)
    parser.add_argument("--dosbox", type=Path, required=True)
    parser.add_argument("--configuration", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--profiles", default=",".join(map(str, PROFILES)))
    parser.add_argument("--repeats", type=int, default=3)
    args = parser.parse_args()
    output = args.output.resolve()
    build = Path(__file__).resolve().parents[1]/"build"
    if not output.is_relative_to(build.resolve()):
        parser.error("Output must be below build")
    requested = [int(x) for x in args.profiles.split(",")]
    if any(mask not in PROFILES for mask in requested) or not 1 <= args.repeats <= 3:
        parser.error("Invalid factorial masks or repeats")
    output.mkdir(parents=True, exist_ok=True)
    config_hash = hashlib.sha256(args.configuration.read_bytes()).hexdigest()
    env = dict(os.environ, SDL_VIDEODRIVER="dummy", SDL_AUDIODRIVER="dummy")
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    rows, reference = [], None
    for repeat in range(args.repeats):
        for mask in requested:
            directory = output/f"m{mask:02x}r{repeat}"
            directory.mkdir(exist_ok=True)
            shutil.copyfile(args.probe, directory/"BENCH.EXE")
            for old in ("DONE", "FAILED", "FRAME.BIN", "TIME.LOG"):
                (directory/old).unlink(missing_ok=True)
            (directory/"RUN.BAT").write_text(f"@echo off\nBENCH.EXE {mask:X}\nif errorlevel 1 goto failed\necho done>DONE\ngoto end\n:failed\necho failed>FAILED\n:end\nexit\n")
            (directory/"probe.conf").write_text(f'[autoexec]\nmount c "{directory}"\nc:\nRUN.BAT\nexit\n')
            started = time.perf_counter()
            subprocess.run([str(args.dosbox), "-conf", str(args.configuration), "-conf", "probe.conf", "-noconsole"],
                           cwd=directory, env=env, startupinfo=startup, timeout=180, check=True)
            process_seconds = time.perf_counter()-started
            if not (directory/"DONE").exists() or (directory/"FAILED").exists():
                raise RuntimeError(f"Failed mask{mask} repeat{repeat}")
            data = (directory/"FRAME.BIN").read_bytes()
            if len(data) != 16*RECORD_BYTES:
                raise ValueError("Incomplete output stream")
            if reference is None:
                reference = data
            elif data != reference:
                offset = next(i for i, (a, b) in enumerate(zip(data, reference)) if a != b)
                raise ValueError(f"Exact output mismatch mask{mask} repeat{repeat} record{offset//RECORD_BYTES} offset{offset%RECORD_BYTES}")
            row = read_timing(directory/"TIME.LOG", mask)
            row["host_process_seconds"] = process_seconds
            row["repeat"] = repeat
            row["output_sha256"] = hashlib.sha256(data).hexdigest()
            rows.append(row)
            if sum(p.stat().st_size for p in output.glob("*/FRAME.BIN")) > 48*1024*1024:
                raise RuntimeError("Protected output budget exceeded")
            if hashlib.sha256(args.configuration.read_bytes()).hexdigest() != config_hash:
                raise RuntimeError("DOSBox configuration changed")
            result = {"configuration_sha256": config_hash, "runs": rows, **summarize(rows)}
            (output/"matrix.json").write_text(json.dumps(result, indent=2)+"\n")
            write_report(output, result)
            print(f"mask={mask:02X} repeat={repeat} exact=1 title_ms={row['phases']['title']['total']:.3f} gameplay_ms={row['phases']['gameplay']['total']:.3f}", flush=True)
    if set(requested) == set(PROFILES) and args.repeats == 3:
        finalize(output)


if __name__ == "__main__":
    main()
