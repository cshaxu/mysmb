"""Check owner-local enemy stream bindings; emit neutral metadata, not ROM bytes."""
import argparse
import json
import re
from pathlib import Path

from smb_asm_index import index_listing
from smb_rom_codegen import read_nrom


def record_layout(data, allow_suffix=False):
    """Validate framing only, without pretending to implement ProcessEnemyData."""
    offset = 0
    counts = {"ordinary": 0, "page": 0, "destination": 0}
    destinations = []
    while offset < len(data):
        first = data[offset]
        if first == 255:
            if not allow_suffix and offset != len(data) - 1:
                raise ValueError("bytes after enemy stream terminator")
            return counts, destinations
        row = first & 15
        size = 3 if row == 14 else 2
        if offset + size >= len(data):
            raise ValueError("truncated record or missing terminator")
        kind = "destination" if row == 14 else "page" if row == 15 else "ordinary"
        counts[kind] += 1
        if row == 14:
            destinations.append((offset, data[offset + 1], data[offset + 2]))
        offset += size
    raise ValueError("missing enemy stream terminator")


def check_literal_span(prg, start, end, lines):
    expected = bytearray()
    for raw in lines:
        source = raw.split(";", 1)[0].strip()
        if not source:
            continue
        match = re.fullmatch(r"\.byte\s+(.+)", source, re.IGNORECASE)
        if not match:
            raise ValueError("unexpected directive in enemy data span")
        for token in match[1].split(","):
            token = token.strip()
            if not re.fullmatch(r"\$[0-9a-fA-F]{2}", token):
                raise ValueError("nonliteral enemy data byte")
            expected.append(int(token[1:], 16))
    if len(expected) != end - start or prg[start - 0x8000:end - 0x8000] != expected:
        raise ValueError("enemy data assembly/ROM binding mismatch")
    return bytes(expected)


def audit(rom, listing):
    prg, _ = read_nrom(rom)
    labels, _, mismatch = index_listing(rom, listing)
    if mismatch:
        raise ValueError("listing opcode mismatch before binding audit")
    symbols = {name: (address, line) for name, address, line in labels}
    streams = [(name, address, line) for name, address, line in labels
               if re.fullmatch(r"E_(?:Castle|Ground|Underground|Water)Area\d+", name)]
    if len(streams) != 34:
        raise ValueError("expected exactly 34 original enemy streams")
    lines = listing.read_text(encoding="latin-1").splitlines()
    spans = []
    for i, (name, start, line) in enumerate(streams):
        end, next_line = streams[i + 1][1:] if i + 1 < len(streams) else symbols["L_CastleArea1"]
        data = check_literal_span(prg, start, end, lines[line:next_line - 1])
        try:
            # Labels need not delimit runtime streams: one empty-stream
            # label aliases the preceding stream's terminating byte.
            counts, destinations = record_layout(
                prg[start - 0x8000:symbols["L_CastleArea1"][0] - 0x8000], True)
        except ValueError as error:
            raise ValueError(name + ": " + str(error)) from error
        for _, pointer, _ in destinations:
            area_type, low = (pointer >> 5) & 3, pointer & 31
            if low >= (3, 22, 3, 6)[area_type]:
                raise ValueError("destination outside original legal area slots")
        used = 2 * (counts["ordinary"] + counts["page"]) + 3 * counts["destination"] + 1
        aliases = [other for other, address, _ in streams if start < address < start + used]
        spans.append(dict(label=name, address="0x%04x" % start,
                          endExclusive="0x%04x" % (start + used), bytes=used,
                          storageBytes=len(data), sharedLabels=aliases,
                          records=counts, destinationRecords=len(destinations),
                          binding="matched", consumerProof="pending"))
    low_base = symbols["EnemyDataAddrLow"][0] - 0x8000
    high_base = symbols["EnemyDataAddrHigh"][0] - 0x8000
    kind_base = symbols["EnemyAddrHOffsets"][0] - 0x8000
    checked = set()
    source_order = [x[0] for x in streams]
    for kind, family in enumerate(("Water", "Ground", "Underground", "Castle")):
        family_names = [x[0] for x in streams if x[0].startswith("E_" + family + "Area")]
        index = source_order.index(family_names[0])
        if prg[kind_base + kind] != index:
            raise ValueError("enemy family base binding mismatch")
        for name in family_names:
            address = prg[low_base + index] | (prg[high_base + index] << 8)
            if address != symbols[name][0]:
                raise ValueError("enemy pointer target mismatch: " + name)
            checked.add(index)
            index += 1
    return dict(streams=spans, totalBytes=sum(x["storageBytes"] for x in spans),
                pointersChecked=len(checked), completeNodes=0,
                limitation="Binding/framing only; ProcessEnemyData and actor consumers remain unproven.")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--asm", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    build = Path(__file__).resolve().parents[1] / "build"
    if not args.output.resolve().is_relative_to(build.resolve()):
        parser.error("audit output must remain below repository build")
    result = audit(args.rom, args.asm)
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="ascii")
    print("%d enemy streams / %d bytes bound; consumer proof remains pending" %
          (len(result["streams"]), result["totalBytes"]))


if __name__ == "__main__":
    main()
