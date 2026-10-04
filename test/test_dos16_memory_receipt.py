"""Neutral synthetic MZ/map acceptance and rejection checks."""
import json
from pathlib import Path
import struct
import subprocess
import sys
import shutil
import uuid

repo = Path(__file__).resolve().parents[1]
tool = repo / "tools/VerifyDos16Memory.py"
valid_map = " 00000H 000FFH 00100H _DATA DATA\n 00100H 0017FH 00080H STACK STACK\n 0000:0 DGROUP\n"
root = repo / "build" / ("memory-contract-" + uuid.uuid4().hex)
root.mkdir()
try:
    image = bytearray(64)
    image[:2] = b"MZ"
    struct.pack_into("<HH", image, 2, 64, 1)
    struct.pack_into("<HH", image, 8, 2, 0)
    cases = [("valid", image, valid_map, True)]
    wrong_length = bytearray(image)
    struct.pack_into("<H", wrong_length, 2, 63)
    cases.append(("length", wrong_length, valid_map, False))
    wrong_header = bytearray(image)
    struct.pack_into("<H", wrong_header, 8, 5)
    cases.append(("header", wrong_header, valid_map, False))
    cases.append(("segment", image, " 00000H 10000H 10001H STACK STACK\n 0000:0 DGROUP\n", False))
    cases.append(("group", image, " 10000H 10000H 00001H STACK STACK\n 0000:0 DGROUP\n", False))
    cases.append(("missing-group", image, valid_map.replace(" 0000:0 DGROUP\n", ""), False))
    cases.append(("bounds", image, valid_map.replace("0017FH", "00180H"), False))
    for name, data, link_map, accepted in cases:
        (root / "mysmb-dos16.exe").write_bytes(data)
        (root / "mysmb-dos16.map").write_text(link_map)
        result = subprocess.run([sys.executable, "-B", str(tool), str(root)], capture_output=True, text=True)
        assert (result.returncode == 0) == accepted, name
        if accepted:
            receipt = json.loads(result.stdout)
            assert receipt["dgroupBytesIncludingStack"] == 384
            assert receipt["stackBytes"] == 128
            assert not receipt["dynamicHeapIncluded"] and not receipt["hardwarePerformanceQualified"]
finally:
    assert root.resolve().is_relative_to((repo / "build").resolve())
    shutil.rmtree(root)
print("7 neutral MZ/map contract cases pass")
