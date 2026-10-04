"""Neutral receipts for the actual owned DOSBox product text-switch route."""
import hashlib
import json
import pathlib
import struct
import sys
import zlib
sys.dont_write_bytecode = True
from VerifyDosBoxIoReceipt import pixels

root = pathlib.Path(sys.argv[1])
assert root.resolve().is_relative_to((pathlib.Path(__file__).resolve().parents[1]/"build").resolve())
assert sum(path.stat().st_size for path in root.glob("*.bmp")) <= 20000000

def picture(name):
    return pixels(root / name)

def size(image):
    return [len(image[0]), len(image)]

before = picture("graphics-before.bmp")
after = picture("graphics-after.bmp")
text = picture("text.bmp")
held = picture("text-held.bmp")
again = picture("text-again.bmp")
loaded = picture("text-loaded.bmp")
graphics_loaded = picture("graphics-loaded.bmp")
assert size(before) == size(after) == size(graphics_loaded)
assert before == after, "paused graphics changed across Tab"
assert size(text) == size(held) == size(again) == size(loaded)
assert text == held == again, "held Tab/round trip changed paused text"
width, height = size(text)
assert width % 80 == 0 and height % 50 == 0
assert size(text) != size(before), "text mode was not entered"
colors = len({color for row in text for color in row})
assert colors >= 4, "text lost object foreground/background colors"
cw, ch = width // 80, height // 50
patterns = {tuple(color for row in text[y*ch:(y+1)*ch] for color in row[x*cw:(x+1)*cw])
            for y in range(50) for x in range(80)}
assert len(patterns) >= 12, "text scene has insufficient glyph/color variation"
save = (root / "mysmb.sav").read_bytes()
assert len(save) == 10035 and struct.unpack_from("<H", save, 8)[0] == 2
assert save[36+4746] == 1, "snapshot lost enabled source observations"
assert struct.unpack_from("<I", save, 32)[0] == zlib.crc32(save[:32]+save[36:])
assert (root / "exit.ok").exists(), "Escape did not return to DOS"
receipt = {
    "runtime": "DOSBox0.74-3/SDL1.2 dummy", "cells": 4000,
    "textDimensions": size(text), "graphicsDimensions": size(before),
    "textColors": colors, "cellPatterns": len(patterns),
    "pausedGraphicsRoundTripEqual": True, "heldTabTextEqual": True,
    "secondTextEntryEqual": True, "observedSnapshotBytes": len(save),
    "loadRetainsTextMode": True, "exitToDos": True,
    "productSha256": hashlib.sha256((root / "MYSMB.EXE").read_bytes()).hexdigest(),
    "romEquivalenceCredit": 0, "performanceQualification": False,
}
(root / "receipt.json").write_text(json.dumps(receipt, indent=2)+"\n")
print(json.dumps(receipt))
