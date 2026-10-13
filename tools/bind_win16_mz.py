"""Verify a functional DOS MZ inside NE; retain its resident allocation bounds."""
import argparse
import json
import struct
from pathlib import Path


def word(data, offset):
    return struct.unpack_from('<H', data, offset)[0]


def mz(data):
    if len(data) < 64 or data[:2] != b'MZ':
        raise ValueError('Missing MZ header')
    last, pages = word(data, 2), word(data, 4)
    size = pages * 512 - (512 - last if last else 0)
    start = word(data, 8) * 16
    if not start <= size <= len(data):
        raise ValueError('Invalid DOS loaded-image range')
    reloc_start, reloc_count = word(data, 24), word(data, 6)
    if reloc_start + reloc_count * 4 > start:
        raise ValueError('Invalid DOS relocation range')
    return start, size, (size - start + 15) // 16, data[reloc_start:reloc_start + reloc_count * 4]


def preserve(stub, hybrid, repair=False):
    start, size, paragraphs, relocations = mz(stub)
    new_start, new_size, new_paragraphs, new_relocations = mz(hybrid)
    ne = struct.unpack_from('<I', hybrid, 60)[0]
    if ne < size or ne + 64 > len(hybrid) or hybrid[ne:ne + 2] != b'NE':
        raise ValueError('Missing native NE entry after DOS image')
    if hybrid[new_start:new_start + size - start] != stub[start:size]:
        raise ValueError('DOS loaded image changed')
    if new_relocations != relocations:
        raise ValueError('DOS relocations changed')
    if any(word(stub, off) != word(hybrid, off) for off in (14, 16, 20, 22)):
        raise ValueError('DOS CS/IP/SS/SP changed')
    result = bytearray(hybrid)
    for offset in (10, 12):
        expected = paragraphs + word(stub, offset) - new_paragraphs
        if not 0 <= expected <= 65535:
            raise ValueError('DOS resident allocation cannot be preserved')
        if repair:
            struct.pack_into('<H', result, offset, expected)
        elif word(hybrid, offset) != expected:
            raise ValueError('DOS resident allocation changed')
    return result, {
        'dos_image_bytes': size - start,
        'dos_relocations': len(relocations) // 4,
        'dos_minimum_resident_bytes': (paragraphs + word(stub, 10) + 16) * 16,
        'dos_maximum_resident_bytes': (paragraphs + word(stub, 12) + 16) * 16,
        'ne_offset': ne, 'hybrid_file_bytes': len(result),
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--stub', type=Path, required=True)
    parser.add_argument('--hybrid', type=Path, required=True)
    parser.add_argument('--repair', action='store_true')
    args = parser.parse_args()
    result, receipt = preserve(args.stub.read_bytes(), args.hybrid.read_bytes(), args.repair)
    if args.repair:
        args.hybrid.write_bytes(result)
    print(json.dumps(receipt, indent=2))


if __name__ == '__main__':
    main()
