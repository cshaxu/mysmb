#!/usr/bin/env python3
"""Check the bounded T52/S5 DisplayTimeUp screen-routine routes."""

import argparse
from pathlib import Path


HEADER = 12
RECORD = 4409
RAM_OFFSET = 4
OWNED_RAM = (0x073C, 0x0759, 0x07A0, 0x0774, 0x0300)


def load(path, magic):
    data = Path(path).read_bytes()
    if data[:8] != magic:
        raise SystemExit('%s has an unexpected trace header' % path)
    if int.from_bytes(data[8:12], 'little') != 4:
        raise SystemExit('%s is not a bounded four-frame route' % path)
    if len(data) != HEADER + 4 * RECORD:
        raise SystemExit('%s has an unexpected trace size' % path)
    return data


def ram_frame(data, index):
    start = HEADER + index * RECORD + RAM_OFFSET
    return data[start:start + 0x0800]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('reference')
    parser.add_argument('native')
    parser.add_argument('--route', choices=('timeup', 'no-timeup'), required=True)
    args = parser.parse_args()

    reference = load(args.reference, b'MSFR\x02\x00\x00\x00')
    native = load(args.native, b'MSFN\x02\x00\x00\x00')
    for index in range(4):
        left = ram_frame(reference, index)
        right = ram_frame(native, index)
        for address in OWNED_RAM:
            if left[address] != right[address]:
                raise SystemExit('frame %d differs at $%04x' % (index, address))
        if left[0x0301:0x0329] != right[0x0301:0x0329]:
            raise SystemExit('frame %d differs in the ScreenRoutines buffer' % index)

    first = ram_frame(reference, 0)
    expected_task = 5 if args.route == 'timeup' else 6
    if first[0x073C] != expected_task:
        raise SystemExit('source route did not reach expected screen task')
    if args.route == 'timeup' and (first[0x0759], first[0x07A0],
                                   first[0x0774]) != (0, 7, 0):
        raise SystemExit('source Time Up output contract was not observed')


if __name__ == '__main__':
    main()
