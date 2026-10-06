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
limit_loader = sys.argv[2:] == ["--limit-loader-allocation"]
assert not sys.argv[2:] or limit_loader, "Unknown option"
program_path = root / "mysmb-dos16.exe"
program = program_path.read_bytes()
assert len(program) >= 28, "Truncated MZ header"
assert program[:2] == b"MZ"
last, pages = struct.unpack_from("<HH", program, 2)
assert pages > 0 and last < 512, "Invalid MZ page counts"
assert (pages - 1) * 512 + (last or 512) == len(program), "MZ length mismatch"
header, minimum, maximum = struct.unpack_from("<HHH", program, 8)
assert 28 <= header * 16 <= len(program), "Invalid header extent"
assert maximum >= minimum, "Maximum allocation below minimum"
image_paragraphs = (len(program) - header * 16 + 15) // 16
loaded_minimum = (image_paragraphs + minimum) * 16
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
assert loaded_minimum >= max(s[1] + (s[2] > 0) for s in segments), "Minimum allocation cannot hold map"
# The original large-model startup retains a full 64 KiB data-segment arena.
# Limit only the loader's initial reservation, never that arena or the image.
loader_bound = (base + 65536 + 15) // 16 - image_paragraphs
assert minimum <= loader_bound <= 65535, "Invalid full-DGROUP allocation bound"
previous_maximum = maximum
if limit_loader:
    assert struct.unpack_from("<H", program, 18)[0] == 0, "Nonzero checksum requires separate policy"
    assert maximum >= loader_bound, "Existing maximum cannot retain full DGROUP"
    if maximum != loader_bound:
        limited = bytearray(program)
        struct.pack_into("<H", limited, 12, loader_bound)
        assert limited[:12] == program[:12] and limited[14:] == program[14:]
        program_path.write_bytes(limited)
        program = bytes(limited)
    maximum = loader_bound

receipt = {
    "productBytes": len(program), "productSha256": hashlib.sha256(program).hexdigest(),
    "segmentsChecked": len(segments), "maximumSegmentBytes": max(s[2] for s in segments),
    "dgroupBytesIncludingStack": group_bytes, "dgroupHeadroomBytes": 65536 - group_bytes,
    "stackBytes": stack[2],
    "minimumLoadedBytes": loaded_minimum,
    "dosPageRoundedMinimumLoadedBytes": pages * 512 - header * 16 + minimum * 16,
    "maximumExtraParagraphs": maximum, "previousMaximumExtraParagraphs": previous_maximum,
    "fullDgroupLoaderBoundParagraphs": loader_bound,
    "loaderBoundSatisfied": maximum == loader_bound,
    "loaderLimitRequested": limit_loader,
    "maximumLoadedBytes": (image_paragraphs + maximum) * 16,
    "dosPageRoundedMaximumLoadedBytes": pages * 512 - header * 16 + maximum * 16,
    "loadedImageSha256": hashlib.sha256(program[header * 16:]).hexdigest(),
    "dynamicHeapIncluded": False, "stackHighWaterMeasured": False,
    "hardwarePerformanceQualified": False, "romEquivalenceCredit": 0,
}
(root / "memory-receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
print(json.dumps(receipt))
