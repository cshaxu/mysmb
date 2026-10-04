"""Bounded actual DOS EXE snapshot route;no ROM equivalence claim."""
import hashlib
import json
import struct
import sys
import zlib
from pathlib import Path
sys.dont_write_bytecode = True
from VerifyDosBoxIoReceipt import pixels


def verify(folder):
    build = Path(__file__).resolve().parents[1] / 'build'
    assert folder.resolve().is_relative_to(build.resolve())
    save = folder / 'GAME' / 'mysmb.sav'
    data = save.read_bytes()
    assert len(data) == 10035 and data[:8] == b'MYSMBSAV'
    assert struct.unpack_from('<HHI', data, 8) == (2, 2, 9999)
    assert zlib.crc32(data[:32] + data[36:]) == struct.unpack_from('<I', data, 32)[0]
    assert not any(data[36 + 4622:36 + 4746]), 'DOS snapshot must declare absent audio renderer'
    assert data[36 + 4746] == 1, 'current DOS root must preserve enabled text observations'
    assert not data[36 + 5 + 0x776] & 1, 'paused save must retain a running boundary'
    assert not (folder / 'mysmb.sav').exists(), 'save incorrectly follows CWD'
    assert not (folder / 'GAME' / 'mysmb.tmp').exists()
    assert not (folder / 'GAME' / 'mysmb.log').exists(), 'operation failed silently'
    positions = {}
    for name in ['saved', 'moved', 'loaded']:
        image = pixels(folder / (name + '.bmp'))
        points = [(x, y) for y in range(60, 348) for x in range(640)
                  if image[y][x] == (152, 32, 32)]
        assert len(points) >= 20, (name, 'player missing')
        positions[name] = [min(x for x, _ in points), min(y for _, y in points),
                           max(x for x, _ in points), max(y for _, y in points)]
    center = lambda name: (positions[name][0] + positions[name][2]) / 2
    assert center('moved') > center('saved') + 10, 'right did not move player'
    assert abs(center('loaded') - center('saved')) <= 4, 'O did not restore position'
    paused = (folder / 'paused.bmp').exists()
    if paused:
        assert pixels(folder / 'paused.bmp') == pixels(folder / 'paused-again.bmp'), 'Enter did not pause'
    assert (folder / 'exit.ok').read_text().strip() == 'MYSMB_EXIT_OK'
    assert len({c for row in pixels(folder / 'exit.bmp') for c in row}) <= 4
    log = (folder / 'probe.log').read_text()
    for name in ['saved', 'moved', 'loaded', 'exit']:
        assert f'capture {name}.bmp result=0' in log
    receipt = {'runtime': 'DOSBox0.74-3/SDL1.2 dummy', 'saveBytes': len(data),
               'exeDirectoryIndependentOfCwd': True, 'playerBounds': positions,
               'saveFrame': struct.unpack_from('<I', data, 36)[0],
               'audioRenderer': 'unavailable', 'exitText': True,
               'pausedCacheAndTitleSeed': paused,
               'productSha256': hashlib.sha256((folder / 'GAME' / 'MYSMB.EXE').read_bytes()).hexdigest(),
               'romCredit': 0, 'performanceQualification': False}
    (folder / 'receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(json.dumps(receipt))


if __name__ == '__main__':
    verify(Path(sys.argv[1]))
