"""Receipt parser owns rejection of incomplete or contradictory evidence."""
import importlib.util
from pathlib import Path
import sys
import unittest

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[5]
spec = importlib.util.spec_from_file_location("cache_receipt", ROOT / "tools/VerifyDos16CacheReceipt.py")
receipt = importlib.util.module_from_spec(spec)
spec.loader.exec_module(receipt)


class CacheReceiptTest(unittest.TestCase):
    def setUp(self):
        # Neutral invented evidence exercises the parser, never a ROM fixture.
        tiers = ("111", "000", "100", "110", "111", "100", "110")
        lines = []
        for mode, tier in enumerate(tiers):
            caches = sum(int(v)*n for v, n in zip(tier, (8192, 63488, 61440)))
            flags = " ".join(f"{k}={v}" for k, v in zip("ABC", tier))
            lines += [f"mode={mode} result=0 observed=1 {flags} exit={int(mode in (1,2,5))} "
                      f"live=0 errors=0 denied={2 if mode==1 else int(mode!=0)} "
                      f"near_try=1 far_try=1 bands={0 if mode in (1,2,5) else 15} peak={caches+1000}",
                      "before valid=1 psp=400000 free=200000 largest=190000",
                      "during valid=1 psp=400000 free=20000 largest=19000",
                      "after valid=1 psp=400000 free=25000 largest=24000",
                      "fit count=2 B=120000 C=60000"]
        self.text = "\n".join(lines)

    def test_complete(self):
        self.assertEqual(receipt.verify(self.text)["root_workspace_bytes"], 1000)

    def test_rejects_missing_case(self):
        with self.assertRaises(ValueError):
            receipt.verify("\n".join(self.text.splitlines()[:-5]))

    def test_rejects_contradictions(self):
        for old, new in (("live=0", "live=1"), ("bands=15", "bands=0"), ("exit=1", "exit=0"),
                         ("denied=0", "denied=1"), ("valid=1", "valid=0"),
                         ("largest=190000", "largest=210000"),
                         ("A=1 B=1 C=1", "A=0 B=1 C=1")):
            with self.subTest(new=new), self.assertRaises(ValueError):
                receipt.verify(self.text.replace(old, new, 1))


if __name__ == "__main__":
    unittest.main()
