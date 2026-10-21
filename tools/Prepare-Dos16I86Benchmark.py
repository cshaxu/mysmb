"""Prepare an isolated 8086 candidate and stage-timed diagnostic below build."""
import argparse
from pathlib import Path
import shutil


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    repository = Path(__file__).resolve().parents[1]
    output = args.output.resolve()
    output.relative_to(repository / 'build')
    tree = output / 'tree'
    for owner in ('src/app-mario', 'src/lib', 'test/app-mario/kvm/io'):
        shutil.copytree(repository / owner, tree / owner, dirs_exist_ok=True)
    (tree / 'tools').mkdir(parents=True, exist_ok=True)
    for script in (repository / 'tools').glob('*.py'):
        shutil.copyfile(script, tree / 'tools' / script.name)
    builder = (repository / 'tools/Build-OpenNt16Dos.ps1').read_text()
    builder = builder.replace("$InstructionSet = 'Accelerated'", "$InstructionSet = '8086'")
    builder = builder.replace("$env:TEMP = Join-Path (Split-Path -Parent $PSScriptRoot) 'build/tmp16'",
        "$env:TEMP = '" + str(repository / 'build/tmp16') + "'")
    builder = builder.replace("$memoryTool = Join-Path $PSScriptRoot 'VerifyDos16Memory.py'",
        "$memoryTool = '" + str(repository / 'tools/VerifyDos16Memory.py') + "'")
    (tree / 'tools/Build-OpenNt16Dos.ps1').write_text(builder)

    probe = (repository / 'test/app-mario/kvm/platform/dos16/cache_factorial_probe.c').read_text()
    probe = probe.replace('static unsigned long overhead,', 'static unsigned long logic,raw_logic,whole_start,whole_raw;\nstatic unsigned long overhead,')
    probe = probe.replace('raw_publish=%lu\\n",', 'raw_publish=%lu logic=%lu raw_logic=%lu whole_raw=%lu\\n",')
    probe = probe.replace('raw_prepare,raw_compose,raw_publish);', 'raw_prepare,raw_compose,raw_publish,logic,raw_logic,whole_raw);')
    probe = probe.replace('    if(sample) {', '    whole_raw=mygames_dos16_clock_stamp()-whole_start;\n    if(sample) {')
    probe = probe.replace('mysmb_game_io_input(&decoded,&input);mysmb_game_tick(&game,&input,&frame);',
        'mysmb_game_io_input(&decoded,&input);raw_logic=0UL;\n'
        '        whole_start=start=mygames_dos16_clock_stamp();mysmb_game_tick(&game,&input,&frame);\n'
        '        logic=elapsed(start,&raw_logic);')
    (output / 'probe.c').write_text(probe)
    probe_builder = (repository / 'tools/Build-Dos16CacheProbe.ps1').read_text()
    probe_builder = probe_builder.replace('$repository=Split-Path -Parent $PSScriptRoot',
        "$repository='" + str(repository) + "'")
    probe_builder = probe_builder.replace("(Join-Path $repository 'test/app-mario/kvm/platform/dos16/cache_factorial_probe.c')",
        "'" + str(output / 'probe.c') + "'")
    probe_builder = probe_builder.replace('/AL\',\'/Gs', '/AL\',\'/G0\',\'/Gs')
    (output / 'Build-Probe.ps1').write_text(probe_builder)
    print('Prepared private8086 build profile and common timed probe')


if __name__ == '__main__':
    main()
