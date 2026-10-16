"""Own the factorial universe and signed interaction arithmetic."""
import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[5]
spec = importlib.util.spec_from_file_location("matrix", ROOT/"tools/MeasureDos16CacheMatrix.py")
matrix = importlib.util.module_from_spec(spec)
spec.loader.exec_module(matrix)


class CacheMatrixTest(unittest.TestCase):
    def setUp(self):
        self.rows = []
        for repeat in range(3):
            for mask in matrix.PROFILES:
                cost = 100 + repeat - 5*bool(mask&1) - 20*bool(mask&2) - 10*bool(mask&4)
                cost += 7*bool(mask&1)*bool(mask&2)  # A becomes slower with B.
                self.rows.append(dict(mask=mask, repeat=repeat,
                    phases={name: {k: cost for k in ("prepare", "compose", "publish", "total", "raw_total")}
                            for name in ("title", "gameplay")}))

    def test_pair_universe(self):
        result = matrix.summarize(self.rows)
        self.assertEqual({k: sum(p["cache"]==k for p in result["margins"]) for k in "ABC"}, dict(A=3,B=2,C=2))
        self.assertFalse(any(m&4 and not m&2 for m in result["profiles"]))

    def test_signed_interaction_and_paired_spread(self):
        pairs = matrix.summarize(self.rows)["margins"]
        plain = next(p for p in pairs if p["cache"]=="A" and p["without"]==0)
        context = next(p for p in pairs if p["cache"]=="A" and p["without"]==2)
        self.assertEqual(plain["phases"]["gameplay"]["total_saved_ms"], 5)
        self.assertEqual(context["phases"]["gameplay"]["total_saved_ms"], -2)
        self.assertEqual(context["phases"]["gameplay"]["total_saved_range"], [-2,-2])
        self.assertEqual(context["phases"]["gameplay"]["saved_ms_per_KiB"], -0.25)

    def test_explicit_empty_baseline(self):
        self.assertEqual(matrix.label(0), "none")
        self.assertEqual(matrix.label(7), "ABC")

    def test_timing_receipt_contract(self):
        lines = ["mask=0 overhead=1 PIT_HZ=1193182"]
        lines += [f"phase={phase} frame={phase*8+i} prepare=1 compose=2 publish=3 raw_prepare=2 raw_compose=3 raw_publish=4"
                  for phase in (0,1) for i in range(8)]
        lines += ["done title=8 gameplay=8 ticks=309 submitted=32 bytes=1966080"]
        scratch = ROOT/"build/cache-matrix-unit"
        scratch.mkdir(parents=True, exist_ok=True)
        with tempfile.TemporaryDirectory(dir=scratch) as temporary:
            receipt = Path(temporary)/"TIME.LOG"
            receipt.write_text("\n".join(lines))
            result = matrix.read_timing(receipt,0)
            self.assertEqual(result["logical_ticks"],309)
            self.assertAlmostEqual(result["phases"]["title"]["total"],6000/1193182)
            for description, changed in (
                    ("truncated", lines[:-1]),
                    ("wrong mask", [lines[0].replace("mask=0","mask=1")]+lines[1:]),
                    ("wrong clock", [lines[0].replace("1193182","1000")]+lines[1:]),
                    ("missing output", lines[:-1]+[lines[-1].replace("1966080","0")]),
                    ("wrong phase", lines[:1]+[lines[1].replace("phase=0","phase=1")]+lines[2:]),
                    ("impossible timing", lines[:1]+[lines[1].replace("prepare=1 ","prepare=9 ")]+lines[2:])):
                with self.subTest(description=description):
                    receipt.write_text("\n".join(changed))
                    with self.assertRaises(ValueError):
                        matrix.read_timing(receipt,0)


if __name__ == "__main__":
    unittest.main()
