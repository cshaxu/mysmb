"""Architecture gate: platform code may adapt host I/O only, never inspect game state."""
from pathlib import Path
import sys

root = Path(__file__).resolve().parents[1]
platform = root / "src" / "platform"
for path in platform.rglob("*.[ch]"):
    text = path.read_text(encoding="utf-8")
    forbidden = (
        "->ram[", ".ram[", "->name_table", "->palette", "->visible_oam",
        "->visible_scroll", "->visible_ppu_", "->ppu_control_", "->scroll_",
    )
    for token in forbidden:
        if token in text:
            print(f"{path.relative_to(root)}: forbidden game-state access {token}")
            sys.exit(1)
print("platform purity: passed")