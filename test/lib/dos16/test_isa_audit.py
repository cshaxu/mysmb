"""Neutral instruction/header fixtures for the optional DOS ISA audit tool."""
import importlib.util
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

sys.dont_write_bytecode = True
REPOSITORY = Path(__file__).resolve().parents[3]
SPEC = importlib.util.spec_from_file_location('isa_audit', REPOSITORY / 'tools/Audit-Dos16Isa.py')
AUDIT = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(AUDIT)


class IsaAuditTest(unittest.TestCase):
    def test_instruction_classification(self):
        hits = []
        AUDIT.inspect_line('not an instruction', 'test', hits)
        AUDIT.inspect_line(' 0: f3 a5    rep movsw', 'test', hits)
        AUDIT.inspect_line(' 2: 26 89 05 mov %ax,%es:(%di)', 'test', hits)
        self.assertEqual(hits, [])
        for line in (' 5: 66 f3 a5 rep movsl', ' 8: 65 67 8b 04 5a mov %gs:(%edx,%ebx,2),%ax',
                     ' d: 68 01 00 push $1', ' 10: d9 e8 fld1', ' 12: 0f (bad)'):
            AUDIT.inspect_line(line, 'test', hits)
        self.assertEqual(len(hits), 5)
        self.assertEqual(hits[0]['fileOffset'], 5)

    def test_switch_data_and_code_boundaries(self):
        parent = REPOSITORY / 'build/t47-s3'
        parent.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=parent) as temporary:
            root = Path(temporary)
            # AX <= 1; jump via CS:[BX+17]. Words21/22 point outside table.
            code = bytes.fromhex('3d01007603e90000d1e08bd82effa71100')
            code += struct.pack('<HH', 21, 22) + bytes.fromhex('c3c3')
            header = bytearray(64)
            header[:2] = b'MZ'
            struct.pack_into('<H', header, 8, 4)
            (root / 'mysmb-dos16.exe').write_bytes(header + code)
            (root / 'mysmb-dos16.map').write_text('00000H 00016H 00017H TEST CODE\n')
            report = root / 'audit.json'
            def invoke():
                subprocess.run([sys.executable, str(REPOSITORY / 'tools/Audit-Dos16Isa.py'),
                    '--directory', str(root), '--output', str(report)],
                    capture_output=True, check=True)
                return json.loads(report.read_text())
            result = invoke()
            self.assertEqual(result['candidateCount'], 0)
            self.assertEqual(len(result['provenSwitchTables']), 1)
            # A real newer instruction at a restored code boundary must survive
            # table exclusion, including when an inline table ends nearby.
            changed = bytearray(code)
            changed[21:23] = bytes.fromhex('6a01')
            (root / 'mysmb-dos16.exe').write_bytes(header + changed)
            self.assertEqual(invoke()['candidateCount'], 1)
            # A target into the table itself invalidates the exclusion proof.
            changed[17:19] = struct.pack('<H', 17)
            (root / 'mysmb-dos16.exe').write_bytes(header + changed)
            self.assertEqual(invoke()['provenSwitchTables'], [])


if __name__ == '__main__':
    unittest.main()
