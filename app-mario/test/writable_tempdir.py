"""Keep synthetic test artifacts below build/ with Windows-safe access."""

from contextlib import contextmanager
import os
from pathlib import Path
import secrets
import shutil


@contextmanager
def writable_temporary_directory(*, dir=None, prefix="tmp-"):
    parent = Path(dir) if dir is not None else Path(__file__).resolve().parents[1] / "build"
    parent.mkdir(parents=True, exist_ok=True)
    mode = 0o777 if os.name == "nt" else 0o700
    for _ in range(10):
        path = parent / (prefix + secrets.token_hex(12))
        try:
            path.mkdir(mode=mode)
            break
        except FileExistsError:
            continue
    else:
        raise FileExistsError("cannot allocate temporary test directory")
    try:
        yield str(path)
    finally:
        shutil.rmtree(path)
