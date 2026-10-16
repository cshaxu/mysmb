"""Validate neutral DOS cache ownership receipts, not game/PPU equivalence."""
import argparse
import json
from pathlib import Path


def fields(line):
    return {key: int(value) for key, value in
            (item.split("=", 1) for item in line.split() if "=" in item)}


def verify(text):
    lines = text.splitlines()
    if len(lines) != 45:
        raise ValueError("Expected nine bounded five-line cases")
    # Fault0/5 require naturally available ABCD; fault4/8 admit ABD.
    expected = ((1, 1, 1, 1), (0, 1, 1, 0), (1, 0, 0, 0),
                (1, 1, 0, 0), (1, 1, 1, 0), (1, 1, 1, 1),
                (0, 1, 1, 0), (1, 1, 0, 0), (1, 1, 1, 0))
    rows = []
    base = None
    for mode in range(9):
        group = lines[mode*5:mode*5+5]
        row = fields(group[0])
        for key, value in dict(mode=mode, result=0, observed=1, live=0, errors=0).items():
            if row.get(key) != value:
                raise ValueError(f"case{mode}: {key}={row.get(key)}, expected{value}")
        if tuple(row[key] for key in "DABC") != expected[mode]:
            raise ValueError(f"case{mode}: wrong retained tier")
        if row["exit"] != int(mode in (1, 2, 3, 6, 7)):
            raise ValueError(f"case{mode}: required-cache failure was not propagated")
        if row["near_try"] != 1 or (mode in (2, 5) and row["far_try"] != 1):
            raise ValueError(f"case{mode}: near/far fallback missing")
        if row["denied"] != (2 if mode == 2 else int(mode != 0)):
            raise ValueError(f"case{mode}: wrong injected failure count")
        storage = sum(row[key]*size for key, size in zip("DABC", (61440, 8192, 63488, 61440)))
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
            "required_cache_bytes": 133120, "full_cache_bytes": 194560,
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
        expected = dict(mode=0, result=0, observed=1, D=1, A=1, B=1, C=0,
                        exit=0, live=0, errors=0, denied=0)
        if any(row.get(key) != value for key, value in expected.items()):
            raise ValueError("Natural pressure did not retain a clean ABD presenter")
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
