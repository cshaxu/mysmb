"""Check original-NMI slot-loop evidence without certifying child interiors."""
import argparse
import csv
import json
from pathlib import Path

from verify_engine_tail_routes import frame


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    directory = parser.parse_args().directory.resolve()
    root = Path(__file__).resolve().parents[1] / 'build'
    assert directory.is_relative_to(root.resolve())
    excluded = set(range(8)) | set(range(256, 512)) | {0x778, 0x779}
    # Corrected owner-ROM symbols, not addresses from another ROM revision.
    counts = {0xaefe: 1, 0xb624: 1, 0xaf03: 6, 0xc047: 6,
              0x84c3: 6, 0xbe70: 2}
    for case in range(2):
        original = frame(directory / ('slots-rom-%d.msfr' % case), b'MSFR')
        with (directory / ('slots-pc-%d.csv' % case)).open() as stream:
            pcs = {int(row['pc'], 16): row for row in csv.DictReader(stream)}
        for pc, expected in counts.items():
            assert int(pcs[pc]['hits']) == expected, (case, hex(pc), expected)
        assert int(pcs[0xaf0e]['fallthrough2']) == 1
        assert int(pcs[0xaf0e]['other']) == 5
        for bits in (32, 64):
            native = frame(directory / ('slots-native%d-%d.msfn' % (bits, case)), b'MSFN')
            assert all(original[4+i] == native[4+i]
                       for i in range(2048) if i not in excluded), (case, bits, 'RAM')
            assert original[2052:] == native[2052:], (case, bits, 'output')
        assert (directory / ('slots-native32-%d.msfn' % case)).read_bytes() == (
            directory / ('slots-native64-%d.msfn' % case)).read_bytes()
    result = dict(routes=2, widthRuns=4, persistentBytesPerSample=1782,
                  outputExceptions=[], originalCallCounts={hex(k): v for k, v in counts.items()},
                  limits='Inactive enemies and inactive/active floatey numbers only. '
                         'PC totals do not prove call order; engine_slots_smoke observes '
                         'native order against source. GameEngine and child interiors '
                         'remain incomplete; no node completion is assigned here.')
    (directory / 'slots-verified.json').write_text(json.dumps(result, indent=2) + '\n')
    print('Two original slot routes, four native runs: persistent RAM and full output match')


if __name__ == '__main__':
    main()
