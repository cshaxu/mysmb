"""Prepare an isolated 8086 candidate and stage-timed diagnostic below build."""
import argparse
from pathlib import Path
import re
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
    builder = builder.replace('/AL /Gs', '/AL /G0 /Gs')
    builder = builder.replace('$env:TEMP = (Get-Location).Path',
        "$env:TEMP = '" + str(repository / 'build/tmp16') + "'")
    builder = builder.replace('$env:TMP = (Get-Location).Path', '$env:TMP = $env:TEMP')
    # The historical driver also has a small command buffer. Keep copied-tree
    # arguments relative to its output directory, without mapping a drive.
    builder = builder.replace('& $Compiler ', 'Invoke-I86Compiler ')
    marker = '$toolDirectory = Split-Path -Parent $Compiler'
    helper = '''function Invoke-I86Compiler {
    $base=[Uri]((Get-Location).Path+'\\')
    $short=@($args | ForEach-Object {
        if ($_ -match '^[A-Za-z]:[\\\\/]') {
            [Uri]::UnescapeDataString($base.MakeRelativeUri([Uri]$_).ToString()).Replace('/','\\')
        } else { $_ }
    })
    & $Compiler @short
    $script:LASTEXITCODE=$LASTEXITCODE
}
'''
    builder = builder.replace(marker, helper + marker)
    builder = builder.replace("$memoryTool = Join-Path $PSScriptRoot 'VerifyDos16Memory.py'",
        "$memoryTool = '" + str(repository / 'tools/VerifyDos16Memory.py') + "'")
    (tree / 'tools/Build-OpenNt16Dos.ps1').write_text(builder)

    def change(relative, transform):
        path = tree / relative
        path.write_text(transform(path.read_text()))

    def word_copies(s):
        s = s.replace('        _emit 0x66\n', '')
        s = s.replace('        shr cx,1\n        shr cx,1', '        shr cx,1')
        return s.replace('and cx,3', 'and cx,1')

    change('src/lib/dos16/vga.c', word_copies)
    slot = tree / 'src/app-mario/kvm/platform/dos16/slot_copy.c'
    s = word_copies(slot.read_text())
    shifts = '        shl cx,1\n' * 6
    assert shifts in s
    slot.write_text(s.replace(shifts, shifts + '        shl cx,1\n', 1))

    planar = tree / 'src/app-mario/kvm/platform/dos16/planar_row.c'
    s = planar.read_text()
    s = re.sub(r'#define PACK_FOUR\(dst,a,b,c,d\).*?(?=#define PACK_TWO)',
        '#define PACK_FOUR(dst,a,b,c,d) PACK_TWO(dst,a,b) PACK_TWO(dst+2,c,d)\n',
        s, flags=re.S)
    s = s.replace('        _emit 0x66\n        _emit 0xc1\n        _emit 0xe0\n        _emit 0x10\n', '')
    s = s.replace('        _emit 0x66\n', '')
    s = s.replace('mov cx,64', 'mov cx,128').replace('mov cx,20', 'mov cx,40')
    assert '_emit' not in s
    planar.write_text(s)

    base = tree / 'src/app-mario/kvm/platform/dos16'
    (base / 'palette_expand.c').write_text('''#include "platform/dos16/palette_expand.h"
#include "io/palette_expand.h"
int mysmb_dos16_palette_expand(void *context,const mygames_kvm_u8 far *packed,
    mygames_kvm_u8 far *pixels,mygames_kvm_u16 count,const mygames_kvm_u8 far *palette)
{return mysmb_io_palette_expand_portable(context,packed,pixels,count,palette);}
''')
    # Same zero-span shortcut and nibble order; no GS, DWORD or scaled index.
    (base / 'nibble_expand.c').write_text('''#include "platform/dos16/nibble_expand.h"
int mysmb_dos16_nibble_expand(const mygames_kvm_u8 far *packed,
    mygames_kvm_u8 far *pixels,mygames_kvm_u16 count)
{
    if(!packed || !pixels || count>256U || (count&1U))return 0;
    _asm {
        push ds
        push es
        lds si,packed
        les di,pixels
        mov bx,di
        push es
        push ds
        pop es
        mov di,si
        xor ax,ax
        mov cx,count
        shr cx,1
        mov dx,cx
        and dx,1
        shr cx,1
        cld
        repe scasw
        jnz scan_done
        mov cx,dx
        repe scasb
scan_done:
        pop es
        mov di,bx
        jnz colored
        mov cx,count
        shr cx,1
        rep stosw
        jmp done
colored:
        lds si,packed
        mov cx,count
        shr cx,1
        jcxz done
next_byte:
        lodsb
        mov ah,al
        and al,15
        shr ah,1
        shr ah,1
        shr ah,1
        shr ah,1
        stosw
        loop next_byte
done:
        pop es
        pop ds
    }
    return 1;
}
''')
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
    print('Prepared private /G0 tree, word-copy/nibble substitutes and common timed probe')


if __name__ == '__main__':
    main()
