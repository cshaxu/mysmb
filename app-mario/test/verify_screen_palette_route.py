#!/usr/bin/env python3
"""Check the bounded T52/S4 ROM/native ScreenRoutines palette route."""

import argparse
from pathlib import Path


HEADER = 12
RECORD = 4409
RAM = 4
CHAIN_BYTES = (0x073C, 0x0744, 0x074E, 0x0753, 0x0756, 0x0773, 0x0300)
CONTROL_OUTPUT = {
    0: (0x00, 0x22),
    4: (0x00, 0x0F),
    5: (0x09, 0x22),
    6: (0x0A, 0x0F),
    7: (0x04, 0x0F),
}


def load(path, magic):
    data = Path(path).read_bytes()
    if data[:8] != magic:
        raise SystemExit('%s has an unexpected trace header' % path)
    count = int.from_bytes(data[8:12], 'little')
    if count != 4 or len(data) != HEADER + count * RECORD:
        raise SystemExit('%s is not the bounded four-frame route' % path)
    return data


def frame(trace, index):
    start = HEADER + index * RECORD + RAM
    return trace[start:start + 0x0800]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('reference')
    parser.add_argument('native')
    parser.add_argument('--background-control', type=int, required=True,
                        choices=sorted(CONTROL_OUTPUT))
    args = parser.parse_args()
    reference = load(args.reference, b'MSFR\x02\x00\x00\x00')
    native = load(args.native, b'MSFN\x02\x00\x00\x00')

    for index in range(4):
        left = frame(reference, index)
        right = frame(native, index)
        for address in CHAIN_BYTES:
            if left[address] != right[address]:
                raise SystemExit('frame %d differs at $%04x' % (index, address))
        if left[0x0301:0x0309] != right[0x0301:0x0309]:
            raise SystemExit('frame %d differs in Buffer1 packet' % index)

    first = frame(reference, 0)
    address_control, background = CONTROL_OUTPUT[args.background_control]
    if (first[0x073C], first[0x0744], first[0x074E], first[0x0753],
            first[0x0756], first[0x0773], first[0x0300]) != \
            (0x0B, args.background_control, 0x01, 0x00, 0x01,
             address_control, 0x07):
        raise SystemExit('the source task-ten palette state was not observed')
    packet = bytes((0x3F, 0x10, 0x04, background, 0x16, 0x27, 0x18, 0x00))
    if first[0x0301:0x0309] != packet:
        raise SystemExit('the source did not emit the expected $3f10 packet')


if __name__ == '__main__':
    main()
