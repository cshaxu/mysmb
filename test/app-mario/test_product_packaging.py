"""Mario delivery contract; synthetic, independently authored headers only."""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import subprocess


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    repository = Path(__file__).resolve().parents[2]
    output = args.output.resolve()
    output.relative_to(repository / 'build')
    output.mkdir(parents=True, exist_ok=True)
    products = output / 'products'
    products.mkdir(exist_ok=True)

    def word(data, offset, value):
        struct.pack_into('<H', data, offset, value)

    pure = bytearray(128)
    pure[:2] = b'MZ'
    for offset, value in ((2, 128), (4, 1), (8, 4), (10, 2), (12, 3), (24, 64)):
        word(pure, offset, value)
    pure[64:] = bytes(range(64))
    hybrid = bytearray(pure) + bytearray(64)
    struct.pack_into('<I', hybrid, 60, 128)
    hybrid[128:130] = b'NE'
    pe = bytearray(128)
    pe[:2] = b'MZ'
    struct.pack_into('<I', pe, 60, 64)
    pe[64:68] = b'PE\0\0'
    word(pe, 68, 0x14c)
    pe64 = bytearray(pe)
    word(pe64, 68, 0x8664)
    inputs = {'Dos16Executable': pure, 'Win16Executable': hybrid,
              'Win32Executable': pe, 'Win64Executable': pe64,
              'Dos86Executable': pure, 'Win86Executable': hybrid}
    paths = {}
    for name, data in inputs.items():
        paths[name] = output / (name + '.exe')
        paths[name].write_bytes(data)
    for name, product, kind in [('Dos86IsaReceipt', 'Dos86Executable', 'MZ'),
                                 ('Win86IsaReceipt', 'Win86Executable', 'NE')]:
        paths[name] = output / (name + '.json')
        paths[name].write_text(json.dumps(dict(binarySha256=hashlib.sha256(inputs[product]).hexdigest(),
            format=kind, candidateCount=0, codeSegments=1, codeBytes=64)))
    for name in ('Win32BuildDirectory', 'Win64BuildDirectory'):
        paths[name] = output / name
        paths[name].mkdir(exist_ok=True)
        (paths[name] / 'CMakeCache.txt').write_text('MYSMB_ROM_PATH:FILEPATH=private-input.nes\n')
        (paths[name] / 'build.ninja').write_text('MYSMB_LOCAL_TITLE=1\n')

    def invoke(expected, **replacements):
        command = ['powershell.exe', '-NoProfile', '-ExecutionPolicy', 'Bypass',
                   '-File', str(repository / 'tools/Package-MySMB.ps1')]
        for name, value in dict(paths, **replacements).items():
            command.extend(['-' + name, str(value)])
        command.extend(['-OutputDirectory', str(products)])
        result = subprocess.run(command, capture_output=True, text=True, timeout=20)
        assert (result.returncode == 0) == expected, result.stdout + result.stderr

    (products / 'mysmb16.exe').write_bytes(b'retired alias')
    invoke(True)
    for name, source in zip(('mysmb16c.exe', 'mysmb16w.exe', 'mysmb32.exe', 'mysmb64.exe', 'mysmb86c.exe', 'mysmb86w.exe'), inputs):
        assert (products / name).read_bytes() == inputs[source]
    assert not (products / 'mysmb16.exe').exists()
    invoke(True)
    invoke(False, Dos86IsaReceipt=paths['Win86IsaReceipt'])
    invoke(False, Win86Executable=paths['Win32Executable'])
    bad_receipt = output / 'bad-isa.json'
    bad_receipt.write_text(json.dumps(dict(binarySha256=hashlib.sha256(pure).hexdigest(),
        format='MZ', candidateCount=1, codeSegments=1, codeBytes=64)))
    invoke(False, Dos86IsaReceipt=bad_receipt)
    invoke(False, Dos16Executable=paths['Win16Executable'])
    invoke(False, Win16Executable=paths['Dos16Executable'])
    invoke(False, Dos16Executable=paths['Win32Executable'])
    invoke(False, Win32Executable=paths['Win64Executable'])
    invoke(False, Win64Executable=output / 'missing.exe')
    changed = bytearray(hybrid)
    changed[64] ^= 1
    mismatch = output / 'mismatch.exe'
    mismatch.write_bytes(changed)
    invoke(False, Win16Executable=mismatch)
    truncated = output / 'truncated.exe'
    truncated.write_bytes(b'MZ')
    invoke(False, Dos16Executable=truncated)
    truncated.write_bytes(hybrid[:130])
    invoke(False, Win16Executable=truncated)
    (paths['Win32BuildDirectory'] / 'build.ninja').write_text('no resources\n')
    invoke(False)
    (paths['Win32BuildDirectory'] / 'build.ninja').write_text('MYSMB_LOCAL_TITLE=1\n')
    (paths['Win32BuildDirectory'] / 'CMakeCache.txt').write_text('no resource binding\n')
    invoke(False)
    print('Six-product packaging: two positive and thirteen negative joins passed')


if __name__ == '__main__':
    main()
