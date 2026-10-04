"""Bounded MZ/link-map memory checks;no game or resource bytes are decoded."""
import hashlib
import json
from pathlib import Path
import re
import struct
import sys

sys.dont_write_bytecode = True
root = Path(sys.argv[1]).resolve()
build = (Path(__file__).resolve().parents[1] / "build").resolve()
assert root.is_relative_to(build)
program = (root / "mysmb-dos16.exe").read_bytes()
assert program[:2] == b"MZ"
last, pages = struct.unpack_from("<HH", program, 2)
assert (pages - 1) * 512 + (last or 512) == len(program), "MZ length mismatch"
header, minimum = struct.unpack_from("<HH", program, 8)
assert header * 16 <= len(program)
link_map = (root / "mysmb-dos16.map").read_text()
segments = []
for match in re.finditer(r"^\s*([0-9A-F]+)H\s+([0-9A-F]+)H\s+([0-9A-F]+)H\s+(\S+)\s+(\S+)", link_map, re.M):
    start, stop, length = (int(match[i], 16) for i in (1, 2, 3))
    assert length <= 65536, "Segment exceeds 16-bit offset range"
    assert stop == start + max(length - 1, 0), "Inconsistent segment bounds"
    segments.append((start, stop, length, match[4], match[5]))
assert segments
group = re.search(r"^\s*([0-9A-F]+):([0-9A-F]+)\s+DGROUP\s*$", link_map, re.M)
assert group, "Missing DGROUP"
base = int(group[1], 16) * 16 + int(group[2], 16)
stacks = [s for s in segments if s[4] == "STACK"]
assert len(stacks) == 1
stack = stacks[0]
assert stack[0] >= base and stack[2] > 0
group_bytes = stack[1] + 1 - base
assert group_bytes <= 65536, "DGROUP exceeds 16-bit offset range"
receipt = {
    "productBytes": len(program), "productSha256": hashlib.sha256(program).hexdigest(),
    "segmentsChecked": len(segments), "maximumSegmentBytes": max(s[2] for s in segments),
    "dgroupBytesIncludingStack": group_bytes, "dgroupHeadroomBytes": 65536 - group_bytes,
    "stackBytes": stack[2],
    "minimumLoadedBytes": ((len(program) - header * 16 + 15) // 16 + minimum) * 16,
    "dynamicHeapIncluded": False, "stackHighWaterMeasured": False,
    "hardwarePerformanceQualified": False, "romEquivalenceCredit": 0,
}
(root / "memory-receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
print(json.dumps(receipt))
