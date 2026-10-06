"""Reject consumers of CRT vectors omitted by the private DOS startup hooks.

Read OMF external symbol records without copying code or resource bytes.
Definitions and unused declarations are not consumers. External references
are conservative: even a currently unreachable consumer requires ABI review.
"""
import argparse
import json
from pathlib import Path


CONSUMERS = {
    "_getenv", "__getenv", "_putenv", "__putenv",
    "_environ", "__environ", "___environ",
    "_envp", "__envp", "___envp", "___argc", "___argv",
}


def external_names(path):
    raw = path.read_bytes()
    if not raw or raw[0] not in (0x80, 0x82):
        raise ValueError("Expected OMF object: " + path.name)
    offset = 0
    names = set()
    while offset < len(raw):
        if offset + 3 > len(raw):
            raise ValueError("Truncated OMF header: " + path.name)
        kind = raw[offset]
        length = int.from_bytes(raw[offset + 1:offset + 3], "little")
        end = offset + 3 + length
        if length < 1 or end > len(raw):
            raise ValueError("Truncated OMF record: " + path.name)
        body = raw[offset + 3:end - 1]
        offset = end
        if kind not in (0x8C, 0xB4):
            continue
        cursor = 0
        while cursor < len(body):
            size = body[cursor]
            cursor += 1
            if cursor + size >= len(body):
                raise ValueError("Truncated external name: " + path.name)
            names.add(body[cursor:cursor + size].decode("ascii"))
            cursor += size
            cursor += 2 if body[cursor] & 0x80 else 1
            if cursor > len(body):
                raise ValueError("Truncated type index: " + path.name)
    return names


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("objects", nargs="+", type=Path)
    args = parser.parse_args()
    hits = []
    for path in args.objects:
        found = sorted(name for name in external_names(path)
                       if name.lower() in CONSUMERS)
        if found:
            hits.append({"object": path.name, "consumers": found})
    print(json.dumps({"objectsChecked": len(args.objects), "consumerHits": hits}))
    if hits:
        raise SystemExit("Review DOS startup hooks before adding CRT vector consumers.")


if __name__ == "__main__":
    main()
