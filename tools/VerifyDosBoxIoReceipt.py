"""Check a bounded local first-level DOSBox I/O route,not ROM equivalence."""
import argparse
import hashlib
import json
import struct
from pathlib import Path


def pixels(path):
    data = path.read_bytes()
    offset = struct.unpack_from('<I', data, 10)[0]
    width, height = struct.unpack_from('<ii', data, 18)
    bits = struct.unpack_from('<H', data, 28)[0]
    if data[:2] != b'BM' or bits != 24 or width <= 0 or height == 0:
        raise ValueError('expected captured 24-bit surface')
    stride = (width * 3 + 3) & ~3
    if len(data) < offset + stride * abs(height):
        raise ValueError('truncated captured surface')
    rows = []
    for y in range(abs(height)):
        source = y if height < 0 else height - 1 - y
        row = data[offset + source * stride:offset + source * stride + width * 3]
        rows.append([tuple(reversed(row[x:x + 3])) for x in range(0, len(row), 3)])
    return rows


def verify(folder):
    build = Path(__file__).resolve().parents[1] / 'build'
    if not folder.resolve().is_relative_to(build.resolve()):
        raise ValueError('protected receipts must remain below ignored build')
    names = ['title', 'start', 'right-run', 'jump', 'before-left', 'release', 'stopped', 'exit']
    frames = {name: pixels(folder / (name + '.bmp')) for name in names}
    positions = {}
    for name in names[1:-1]:
        image = frames[name]
        assert len(image) == 400 and len(image[0]) == 640, name
        # This finite first-level fixture has no other red actor in this ROI.
        # DAC drops two low bits;this is the existing neutral palette's red.
        points = [(x, y) for y in range(60, 348) for x in range(640)
                  if image[y][x] == (152, 32, 32)]
        assert len(points) >= 20, (name, 'missing visible player')
        positions[name] = [min(x for x, _ in points), min(y for _, y in points),
                           max(x for x, _ in points), max(y for _, y in points)]
    center = lambda name: (positions[name][0] + positions[name][2]) / 2
    assert center('right-run') > center('start'), 'held right did not advance'
    assert positions['jump'][1] < positions['start'][1], 'K did not produce visible jump'
    assert center('release') < center('before-left'), 'held left did not reverse movement'
    assert abs(center('stopped') - center('release')) <= 4, 'release did not settle'
    title_brown = sum(color == (120, 60, 0) for row in frames['title'][40:160] for color in row)
    assert title_brown > 5000, 'title banner missing'
    sky = sum(color == (120, 124, 232) for row in frames['start'] for color in row)
    assert sky > 100000, 'Start remains in black transition'
    exit_colors = {color for row in frames['exit'] for color in row}
    assert len(exit_colors) <= 4 and (0, 0, 0) in exit_colors, 'DOS text mode not restored'
    assert (folder / 'exit.ok').read_text().strip() == 'MYSMB_EXIT_OK'
    log = (folder / 'probe.log').read_text()
    for name in names:
        assert f'capture {name}.bmp result=0' in log, name
    assert 'key 106 1' in log and 'key 107 1' in log
    for symbol in [13, 100, 106, 107, 97, 27]:
        assert log.count(f'key {symbol} 1 ') == log.count(f'key {symbol} 0 ') == 1
    receipt = {'runtime': 'DOSBox0.74-3/SDL1.2 dummy', 'playerBounds': positions,
               'skyPixels': sky, 'titleBannerPixels': title_brown, 'exitText': True,
               'gameplayObservationMilliseconds': 24000,
               'productSha256': hashlib.sha256((folder / 'MYSMB.EXE').read_bytes()).hexdigest(),
               'romEquivalenceCredit': 0, 'performanceQualification': False}
    (folder / 'receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
    print(json.dumps(receipt))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('folder', type=Path)
    verify(parser.parse_args().folder)
