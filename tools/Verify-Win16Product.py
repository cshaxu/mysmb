"""Private Win3.1 startup/Tab/exit qualification of a locally built NE product."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('compiler', 'sdk', 'windows-library', 'runtime-library',
                 'windows-directory', 'dosbox', 'config', 'product', 'output'):
        parser.add_argument('--' + name, type=Path, required=True)
    args = parser.parse_args()
    repository = Path(__file__).resolve().parents[1]
    root = args.output.resolve()
    root.relative_to(repository / 'build')
    root.mkdir(parents=True, exist_ok=True)
    for name in ('compiler', 'sdk', 'windows_library', 'runtime_library',
                 'windows_directory', 'dosbox', 'config', 'product'):
        value = getattr(args, name).resolve()
        assert (value.is_dir() if name in ('sdk', 'windows_directory') else value.is_file()), 'Missing configured input: ' + name
        setattr(args, name, value)
    temporary = repository / 'build/tmp16'
    temporary.mkdir(exist_ok=True)
    environment = dict(os.environ, PATH=str(args.compiler.parent) + ';' + os.environ['SystemRoot'] + '/System32',
                       TMP=str(temporary), TEMP=str(temporary))
    source = repository / 'test/app-mario/kvm/platform/win16/isa_runtime_probe.c'
    with (root / 'build.log').open('w') as log:
        subprocess.run([str(args.compiler), '/nologo', '/AL', '/G0sw', '/Gs', '/c', '/Focheck.obj',
            '/I', os.path.relpath(args.sdk, root), os.path.relpath(source, root)],
            cwd=root, env=environment, stdout=log, stderr=subprocess.STDOUT, check=True, timeout=120)
        (root / 'check.def').write_text('NAME CHECK\nEXETYPE WINDOWS\nCODE PRELOAD MOVEABLE DISCARDABLE\n'
            'DATA PRELOAD MOVEABLE MULTIPLE\nHEAPSIZE 4096\nSTACKSIZE 4096\nEXPORTS\n CheckProc @1\n')
        (root / 'check.rsp').write_text('check.obj\ncheck.exe\ncheck.map\n' + str(args.windows_library) + '+\n' +
            str(args.runtime_library) + '\ncheck.def;\n')
        subprocess.run([str(args.compiler.parent / 'link16.exe'), '/nologo', '/NOE', '/NOD', '@check.rsp'],
            cwd=root, env=environment, input='', text=True, stdout=log, stderr=subprocess.STDOUT,
            check=True, timeout=120)
    shutil.copytree(args.windows_directory, root / 'WINDOWS', dirs_exist_ok=True)
    ini = root / 'WINDOWS/SYSTEM.INI'
    config = ini.read_text(errors='replace')
    config = re.sub(r'(?im)^shell=.*', lambda _: 'shell=c:\\check.exe', config)
    config = re.sub(r'(?im)^PermSwap.*\n?', '', config)
    config = re.sub(r'(?im)^\[386Enh\]', '[386Enh]\nPaging=off', config)
    ini.write_text(config)
    shutil.copyfile(args.product, root / 'MYSMB86W.EXE')
    receipt = root / 'CHECK.LOG'
    receipt.unlink(missing_ok=True)
    (root / 'boot.conf').write_text('[cpu]\ncycles=fixed 3000\n[autoexec]\nmount c "' + str(root) +
        '"\nc:\nset path=c:\\windows\ncd windows\nwin /3\nexit\n')
    before = hashlib.sha256(args.config.read_bytes()).hexdigest()
    startup = subprocess.STARTUPINFO()
    startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW
    startup.wShowWindow = 0
    with (root / 'host.log').open('w') as log:
        process = subprocess.Popen([str(args.dosbox), '-conf', str(args.config), '-conf', str(root / 'boot.conf'),
            '-noconsole'], cwd=root, startupinfo=startup, stdout=log, stderr=subprocess.STDOUT,
            env=dict(os.environ, SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy'))
        try:
            assert process.wait(timeout=150) == 0, 'DOSBox failed'
        finally:
            if process.poll() is None:
                process.terminate()
                process.wait(timeout=5)
    assert hashlib.sha256(args.config.read_bytes()).hexdigest() == before, 'Persistent config changed'
    values = dict(line.split() for line in receipt.read_text().splitlines() if line.strip())
    assert int(values['WinExec']) >= 32 and values.get('window') == '1' and values.get('exit') == '1', values
    assert 'timeout' not in values, values
    for phase in ('graphics_colors', 'text_colors', 'graphics_return_colors'):
        assert int(values[phase]) > 1, ('Blank presentation', phase, values)
    result = dict(productSha256=hashlib.sha256(args.product.read_bytes()).hexdigest(),
        configUnchanged=True, cycles=3000, stages=values,
        scope='Win3.1 enhanced-mode startup, graphics/text/graphics and exit; not8088 hardware qualification')
    (root / 'result.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result))


if __name__ == '__main__':
    main()
