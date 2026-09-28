"""Project-owned synthetic framing and binding rejection cases; no ROM needed."""
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from smb_enemy_data_audit import audit, check_literal_span, record_layout


def rejected(function, *args):
    try:
        function(*args)
    except ValueError:
        return
    raise AssertionError("invalid input accepted")


def synthetic_binding():
    families = [("Castle", 6), ("Ground", 22), ("Underground", 3), ("Water", 3)]
    names = ["E_%sArea%d" % (family, n) for family, count in families
             for n in range(1, count + 1)]
    bodies = {name: [255] for name in names}
    bodies["E_GroundArea9"] = [0x21, 7]
    bodies["E_WaterArea1"] = [14, 0, 0, 255]
    cursor = 0x8048
    addresses = {}
    for name in names:
        addresses[name] = cursor
        cursor += len(bodies[name])
    tables = [
        ("EnemyAddrHOffsets", [names.index("E_" + f + "Area1")
                               for f in ("Water", "Ground", "Underground", "Castle")]),
        ("EnemyDataAddrLow", [addresses[n] & 255 for n in names]),
        ("EnemyDataAddrHigh", [addresses[n] >> 8 for n in names]),
    ]
    image = bytearray(16 + 32768 + 8192)
    image[:6] = b"NES\x1a\x02\x01"
    source = [".org $8000"]
    cursor = 16
    for name, data in tables + list(bodies.items()) + [("L_CastleArea1", [0])]:
        source += [name + ":", ".byte " + ",".join("$%02x" % x for x in data)]
        image[cursor:cursor + len(data)] = bytes(data)
        cursor += len(data)
    build = Path(__file__).resolve().parents[1] / "build"
    build.mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(dir=build, prefix="enemy-audit-") as directory:
        base = Path(directory)
        rom, asm = base / "synthetic.nes", base / "synthetic.asm"
        rom.write_bytes(image)
        asm.write_text("\n".join(source) + "\n", encoding="ascii")
        result = audit(rom, asm)
        assert result["pointersChecked"] == 34 and result["completeNodes"] == 0
        shared = next(x for x in result["streams"] if x["label"] == "E_GroundArea9")
        assert shared["bytes"] == 3 and shared["storageBytes"] == 2
        assert shared["sharedLabels"] == ["E_GroundArea10"]
        # Pointer and family-base errors are independent of literal payload binding.
        for offset in [16, 20, 54, 16 + 0x48]:
            altered = bytearray(image)
            altered[offset] ^= 1
            rom.write_bytes(altered)
            rejected(audit, rom, asm)


def main():
    counts, targets = record_layout(bytes([0x21, 7, 0x0f, 4, 0x3e, 2, 0x45, 255]))
    assert counts == {"ordinary": 1, "page": 1, "destination": 1}
    assert targets == [(4, 2, 0x45)]
    assert record_layout(bytes([255])) == ({"ordinary": 0, "page": 0, "destination": 0}, [])
    # A terminator-looking operand is data when it is inside a record.
    assert record_layout(bytes([0x21, 255, 255]))[0]["ordinary"] == 1
    assert record_layout(bytes([1, 2, 255, 3, 4, 255]), True)[0]["ordinary"] == 1
    assert record_layout(bytes([255, 3, 4, 255]), True)[0]["ordinary"] == 0
    for value in [[], [1], [1, 2], [14, 1, 255], [14, 1, 2], [255, 0]]:
        rejected(record_layout, bytes(value))
    source = ["; synthetic", ".byte $21, $07 ; item", ".byte $ff"]
    data = bytes([0x21, 7, 255])
    assert check_literal_span(data, 0x8000, 0x8003, source) == data
    rejected(check_literal_span, bytes([0x21, 8, 255]), 0x8000, 0x8003, source)
    rejected(check_literal_span, data, 0x8000, 0x8002, source)
    rejected(check_literal_span, data, 0x8000, 0x8003, [".byte mystery"])
    rejected(check_literal_span, data, 0x8000, 0x8003, [".word $0721"])
    synthetic_binding()
    print("enemy-data synthetic framing/binding: passed (14 rejection cases)")


if __name__ == "__main__":
    main()
