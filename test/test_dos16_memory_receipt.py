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
    struct.pack_into("<HHH", image, 8, 2, 22, 65535)
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
    # Mutation is bounded to the maximum-extra word; all rejected inputs stay intact.
    cap_cases = [("cap-valid", image, valid_map, True)]
    checksum = bytearray(image);struct.pack_into("<H", checksum, 18, 1)
    cap_cases.append(("checksum", checksum, valid_map, False))
    small_max = bytearray(image);struct.pack_into("<H", small_max, 12, 22)
    cap_cases.append(("small-max", small_max, valid_map, False))
    inverted = bytearray(image);struct.pack_into("<H", inverted, 12, 21)
    cap_cases.append(("inverted", inverted, valid_map, False))
    tiny_min = bytearray(image);struct.pack_into("<H", tiny_min, 10, 0)
    cap_cases.append(("map-minimum", tiny_min, valid_map, False))
    oversized_min = bytearray(image);struct.pack_into("<H", oversized_min, 10, 4095)
    cap_cases.append(("minimum-above-arena", oversized_min, valid_map, False))
    empty_pages = bytearray(image);struct.pack_into("<H", empty_pages, 4, 0)
    cap_cases.append(("empty-pages", empty_pages, valid_map, False))
    bad_last = bytearray(image);struct.pack_into("<H", bad_last, 2, 512)
    cap_cases.append(("bad-last-page", bad_last, valid_map, False))
    cap_cases.append(("truncated", image[:20], valid_map, False))
    cap_cases.append(("malformed-map", image, valid_map.replace("0017FH", "00180H"), False))
    for name, data, link_map, accepted in cap_cases:
        exe = root / "mysmb-dos16.exe";exe.write_bytes(data)
        (root / "mysmb-dos16.map").write_text(link_map)
        command = [sys.executable, "-B", str(tool), str(root), "--limit-loader-allocation"]
        result = subprocess.run(command, capture_output=True, text=True)
        assert (result.returncode == 0) == accepted, name
        limited = exe.read_bytes()
        if not accepted:
            assert limited == data, name
            continue
        assert limited[:12] == data[:12] and limited[14:] == data[14:]
        assert struct.unpack_from("<H", limited, 12)[0] == 4094
        receipt = json.loads(result.stdout)
        assert receipt["loaderBoundSatisfied"] and receipt["previousMaximumExtraParagraphs"] == 65535
        assert receipt["minimumLoadedBytes"] == 384
        assert receipt["dosPageRoundedMinimumLoadedBytes"] == 832
        assert receipt["maximumLoadedBytes"] == 65536
        again = subprocess.run(command, capture_output=True, text=True)
        assert again.returncode == 0 and exe.read_bytes() == limited
        assert json.loads(again.stdout)["previousMaximumExtraParagraphs"] == 4094
finally:
    assert root.resolve().is_relative_to((repo / "build").resolve())
    shutil.rmtree(root)
print("7 neutral MZ/map and 10 loader-bound cases plus idempotence pass")
