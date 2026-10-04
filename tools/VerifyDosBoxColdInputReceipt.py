"""Cold-start input/progress evidence,independent of pause-frame acceptance."""
import hashlib
import json
from pathlib import Path
import struct
import sys
import zlib
sys.dont_write_bytecode = True
from VerifyDosBoxIoReceipt import pixels

root = Path(sys.argv[1]).resolve()
assert root.is_relative_to((Path(__file__).resolve().parents[1] / "build").resolve())
assert sum(p.stat().st_size for p in root.glob("*.bmp")) <= 20000000
script = (root / "input.script").read_text().splitlines()
assert "7000 key 13 1" in script and "7000 key 111 1" not in script, "seeded route is not cold-start evidence"
title = pixels(root / "title.bmp")
graphics = pixels(root / "graphics-before.bmp")
text = pixels(root / "text.bmp")
assert [len(title[0]), len(title)] == [640, 400]
assert [len(text[0]), len(text)] == [720, 400], "Tab was not consumed"
assert title != graphics, "cold-start picture did not progress"
assert (root / "exit.ok").read_text().strip() == "MYSMB_EXIT_OK", "Escape did not return to DOS"
slot = (root / "mysmb.sav").read_bytes()
assert len(slot) == 10035 and struct.unpack_from("<H", slot, 8)[0] == 2
assert struct.unpack_from("<I", slot, 32)[0] == zlib.crc32(slot[:32] + slot[36:])
log = (root / "probe.log").read_text()
for symbol in (13, 9, 112, 111, 27):
    assert f"key {symbol} 1 " in log and f"key {symbol} 0 " in log
receipt = {
    "contract": "unseeded cold-start progress,Tab,save and Escape",
    "coldStart": True, "graphicsProgressed": True, "textEntered": True,
    "runningSnapshotCreated": True, "snapshotBytes": len(slot), "exitToDos": True,
    "loadRequestsInjected": True, "loadEqualityProved": False,
    "pauseAcceptanceProved": False, "historicalFailureCauseProved": False,
    "productSha256": hashlib.sha256((root / "MYSMB.EXE").read_bytes()).hexdigest(),
    "romEquivalenceCredit": 0, "performanceQualification": False,
}
(root / "cold-input-receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
print(json.dumps(receipt))
