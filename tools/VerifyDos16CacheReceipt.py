"""Validate neutral DOS cache ownership receipts, not game/PPU equivalence."""
import argparse
import json
from pathlib import Path


def fields(line):
    return {key: int(value) for key, value in
            (item.split("=", 1) for item in line.split() if "=" in item)}


def verify(text):
    lines = text.splitlines()
    if len(lines) != 35:
        raise ValueError("Expected seven bounded five-line cases")
    # Natural/near-denied retain ABC; optional allocation/preflight retain AB.
    expected = ((1, 1, 1), (0, 0, 0), (1, 0, 0),
                (1, 1, 0), (1, 1, 1), (1, 0, 0), (1, 1, 0))
    rows = []
    base = None
    for mode in range(7):
        group = lines[mode*5:mode*5+5]
        row = fields(group[0])
        for key, value in dict(mode=mode, result=0, observed=1, live=0, errors=0).items():
            if row.get(key) != value:
                raise ValueError(f"case{mode}: {key}={row.get(key)}, expected{value}")
        if tuple(row[key] for key in "ABC") != expected[mode]:
            raise ValueError(f"case{mode}: wrong retained tier")
        if row["exit"] != int(mode in (1, 2, 5)):
            raise ValueError(f"case{mode}: required-cache failure was not propagated")
        if row["near_try"] != 1 or (mode in (1, 4) and row["far_try"] != 1):
            raise ValueError(f"case{mode}: near/far fallback missing")
        if row["denied"] != (2 if mode == 1 else int(mode != 0)):
            raise ValueError(f"case{mode}: wrong injected failure count")
        if row.get("bands") != (0 if row["exit"] else 15):
            raise ValueError(f"case{mode}: product did not use ordinary RAM bands")
        storage = sum(row[key]*size for key, size in zip("ABC", (8192, 63488, 61440)))
        row["cache_bytes"] = storage
        root_bytes = row["peak"] - storage
        if base is None:
            base = root_bytes
        if root_bytes != base or root_bytes <= 0:
            raise ValueError(f"case{mode}: unaccounted live root allocation")
        for index, name in enumerate(("before", "during", "after"), 1):
            census = fields(group[index])
            if census.get("valid") != 1 or census["largest"] > census["free"]:
                raise ValueError(f"case{mode}: invalid MCB census")
            row[name] = census
        row["fit"] = fields(group[4])
        rows.append(row)
    return {"cases": rows, "root_workspace_bytes": base,
            "required_cache_bytes": 71680, "full_cache_bytes": 133120,
            "all_root_owned_allocations_released": True,
            "production_psp_measured": False, "rom_equivalence_credit": 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directory", type=Path)
    parser.add_argument("--pressure", action="store_true")
    args = parser.parse_args()
    directory = args.directory.resolve()
    build = Path(__file__).resolve().parents[1] / "build"
    if not directory.is_relative_to(build.resolve()):
        parser.error("Receipts must remain below build")
    text = (directory / "CACHE.LOG").read_text()
    if args.pressure:
        lines = text.splitlines()
        if len(lines) != 5:
            raise ValueError("Expected one natural memory-pressure case")
        row = fields(lines[0])
        expected = dict(mode=0, result=0, observed=1, A=1, B=1, bands=15,
                        exit=0, live=0, errors=0, denied=0)
        if any(row.get(key) != value for key, value in expected.items()) or row.get("C") not in (0,1):
            raise ValueError("Natural pressure did not retain a clean AB presenter")
        for i, name in enumerate(("before", "during", "after"), 1):
            row[name] = fields(lines[i])
            if row[name].get("valid") != 1:
                raise ValueError("Invalid pressure MCB census")
        row["fit"] = fields(lines[4])
        result = {"case": row, "resident_pressure_bytes": 65536,
                  "all_root_owned_allocations_released": True,
                  "production_psp_measured": False, "rom_equivalence_credit": 0}
    else:
        result = verify(text)
    (directory / "cache-receipt.json").write_text(json.dumps(result, indent=2)+"\n")
    print(json.dumps({key: value for key, value in result.items() if key != "cases"}))


if __name__ == "__main__":
    main()
