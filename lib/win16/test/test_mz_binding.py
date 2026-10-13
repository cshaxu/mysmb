"""Owner-local binder tests use synthetic executable bytes, never ROM data."""
import importlib.util
from pathlib import Path
import struct
import sys
import unittest

sys.dont_write_bytecode = True
spec = importlib.util.spec_from_file_location('binder', Path(__file__).resolve().parents[3] / 'tools' / 'bind_win16_mz.py')
binder = importlib.util.module_from_spec(spec)
spec.loader.exec_module(binder)


def inputs():
    stub = bytearray(96)
    stub[:2] = b'MZ'
    for offset, value in ((2, 96), (4, 1), (6, 1), (8, 4), (10, 20), (12, 30), (14, 1), (16, 128), (20, 2), (22, 1), (24, 28)):
        struct.pack_into('<H', stub, offset, value)
    stub[28:32] = b'\x00\x00\x01\x00'
    stub[64:96] = bytes(range(32))
    hybrid = bytearray(stub) + bytearray(96)
    struct.pack_into('<H', hybrid, 2, 112)
    struct.pack_into('<I', hybrid, 60, 128)
    hybrid[128:130] = b'NE'
    return stub, hybrid


class Binding(unittest.TestCase):
    def test_allocation_repair_preserves_resident_image(self):
        stub, hybrid = inputs()
        repaired, receipt = binder.preserve(stub, hybrid, True)
        self.assertEqual(repaired[64:96], stub[64:96])
        self.assertEqual((binder.word(repaired, 10), binder.word(repaired, 12)), (19, 29))
        self.assertEqual(receipt['dos_minimum_resident_bytes'], 608)
        self.assertEqual(binder.preserve(stub, repaired)[0], repaired)

    def test_no_silent_acceptance_of_bad_bounds(self):
        stub, hybrid = inputs()
        with self.assertRaisesRegex(ValueError, 'allocation changed'):
            binder.preserve(stub, hybrid)

    def test_changed_program_relocations_and_entry_are_rejected(self):
        for offset in (64, 28, 14, 16, 20, 22):
            stub, hybrid = inputs()
            hybrid[offset] ^= 1
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                binder.preserve(stub, hybrid, True)

    def test_missing_ne_and_bad_mz_are_rejected(self):
        for offset in (0, 4, 8, 24, 60, 128):
            stub, hybrid = inputs()
            hybrid[offset] = 255
            with self.subTest(offset=offset), self.assertRaises(ValueError):
                binder.preserve(stub, hybrid, True)


if __name__ == '__main__':
    unittest.main()
