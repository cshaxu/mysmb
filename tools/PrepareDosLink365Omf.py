"""Prepare current OpenNT OMF objects for the bounded DOS LINK 3.65 route.

This rewrites only each module's CODE segment name inside a private build
copy.  Existing DATA, CONST, BSS, FAR_DATA, relocation, and source records
are copied byte-for-byte apart from their enclosing OMF record checksums.
"""
import argparse
import json
import re
import shutil
from pathlib import Path


def checksum(record_type, length, payload):
    return (-sum(bytes((record_type, length & 0xff, length >> 8)) + payload)) & 0xff


def object_for_source(source):
    normalized = source.replace("\\", "/")
    if "/local-rom/" in normalized:
        return Path(normalized).with_suffix(".obj").name
    return normalized.split("/src/", 1)[1].replace("/", "_")


def library_members(library):
    text = library.read_bytes().decode("latin1", "ignore")
    # OpenNT records each source path in the librarian member metadata.  The
    # drive and checkout root are deliberately not part of the contract: a
    # checked-out repository may live anywhere.  We only need the stable tail
    # below src/ or the generated build/ local-ROM directory.
    pattern = r"[A-Za-z]:\\[^\x00\r\n]*?\\(?:src|build)\\[A-Za-z0-9_.\\-]+\.c"
    result = []
    for source in re.findall(pattern, text, re.IGNORECASE):
        source = source.replace("\\", "/")
        if source not in result:
            result.append(source)
    if not result:
        raise ValueError("no source members found in " + str(library))
    return result


def patch_code_name(source, destination, bucket):
    data = source.read_bytes()
    position = 0
    records = []
    text_names = 0
    while position + 3 <= len(data):
        record_type = data[position]
        length = data[position + 1] | (data[position + 2] << 8)
        end = position + 3 + length
        if end > len(data) or length == 0:
            raise ValueError("malformed OMF record in " + str(source))
        payload = bytearray(data[position + 3:end - 1])
        position = end
        if record_type == 0x96:  # LNAMES
            cursor = 0
            replacement = bytearray()
            while cursor < len(payload):
                name_length = payload[cursor]
                cursor += 1
                name = bytes(payload[cursor:cursor + name_length])
                cursor += name_length
                if name.decode("latin1").endswith("_TEXT"):
                    name = ("P%02dTEXT" % bucket).encode("ascii")
                    text_names += 1
                replacement.extend(bytes((len(name),)) + name)
            payload = replacement
        records.append((record_type, payload))
    if position != len(data) or text_names != 1:
        raise ValueError("expected one *_TEXT name in " + str(source))
    with destination.open("wb") as handle:
        for record_type, payload in records:
            length = len(payload) + 1
            handle.write(bytes((record_type, length & 0xff, length >> 8)))
            handle.write(payload)
            handle.write(bytes((checksum(record_type, length, payload),)))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--input", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    parser.add_argument("--direct", action="append", default=[])
    parser.add_argument("--stack", required=True)
    args = parser.parse_args()
    input_dir = args.input.resolve()
    output_dir = args.output.resolve()
    if output_dir.exists():
        shutil.rmtree(output_dir)
    objects_dir = output_dir / "obj"
    objects_dir.mkdir(parents=True)
    groups = []
    for bucket, library in enumerate(sorted(input_dir.glob("smbgrp??.lib"))):
        members = []
        for index, source in enumerate(library_members(library)):
            original = input_dir / object_for_source(source)
            if not original.is_file():
                raise FileNotFoundError(original)
            staged_name = "G%02d%02d.OBJ" % (bucket, index)
            patch_code_name(original, objects_dir / staged_name, bucket)
            members.append(staged_name)
        groups.append({"library": "L%02d.LIB" % bucket, "members": members})
    if not groups:
        raise ValueError("no smbgrp??.lib libraries under " + str(input_dir))
    direct = []
    for bucket, name in enumerate(args.direct, start=len(groups)):
        original = input_dir / name
        if not original.is_file():
            raise FileNotFoundError(original)
        staged_name = "D%02d.OBJ" % (bucket - len(groups))
        patch_code_name(original, objects_dir / staged_name, bucket)
        direct.append(staged_name)
    stack = input_dir / args.stack
    if not stack.is_file():
        raise FileNotFoundError(stack)
    shutil.copyfile(stack, output_dir / "STK.OBJ")
    manifest = {"groups": groups, "direct": direct, "stack": "STK.OBJ"}
    (output_dir / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="ascii")
    print(json.dumps({"groups": len(groups), "members": sum(len(x["members"]) for x in groups),
                      "direct": len(direct)}, sort_keys=True))


if __name__ == "__main__":
    main()
