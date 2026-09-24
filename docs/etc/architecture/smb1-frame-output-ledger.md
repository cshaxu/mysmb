# SMB1 Frame Output Ledger

This is the active M2 T9 output-ownership ledger for the admitted local ROM
revision. It contains source addresses and neutral ownership conclusions only;
it contains no ROM, listing, trace, generated data, or screenshots.

## Canonical Snapshot Contract

One native frame snapshot is sampled after the translated NMI output phase has
committed its frame state and before the next sampled controller input. The
owner-local reference recorder must sample at the same boundary. A snapshot
contains:

| Field | Size | Source meaning |
| --- | ---: | --- |
| Frame sequence | 32 bits | NMI sequence index. |
| CPU RAM | 2048 bytes | Original `$0000-$07ff`, including OAM and both VRAM buffers. |
| Name tables | 2 × 1024 bytes | PPU `$2000-$27ff`, including attributes. |
| Palette | 32 bytes | PPU palette state. |
| OAM | 256 bytes | Sprite Y, tile, attribute, and X entries in hardware order. |
| PPU controls and scroll | 6 bytes | Mirrored `$2000/$2001`, name-table selection, and committed scroll pair. |
| Audio command state | bounded neutral fields | Game-owned queues, events, and channel command state. |

The snapshot is an output record, not a PPU emulation API. The portable C
route owns the record; Win32, VGA, and text consumers only read it.

## Audited Output Owners

| ROM range | Original owner | Required snapshot effect | Current C disposition |
| --- | --- | --- | --- |
| `$8082-$81f9` | NMI display synchronization, sprite sequencing, and sprite-offset shuffle | Frame boundary, PPU control/scroll commit, OAM ordering | **Missing**; game tick has no NMI-output phase. |
| `$8220-$8227` | Move all sprites offscreen | OAM offscreen entries | **Partial**; RAM clear exists, but it is not submitted as OAM output. |
| `$8325-$833f` | Title mushroom icon | Tile/OAM title visual | **Partial**; title command data is consumed, icon/OAM route is absent. |
| `$84c3-$8566` | Floatey score numbers and screen-support sprites | OAM entries and score updates | **Missing**; logic explicitly excludes OAM. |
| `$8567-$864c` | Screen tasks, area/player palettes, and VRAM buffer addressing | Palette, buffer selection, name-table updates | **Missing**. |
| `$8652-$889c` | Status text, two-player text, title, intermediate, and area display tasks | VRAM buffer writes, name-table and palette state | **Partial**; title-only command stream is present. |
| `$88ae-$89bd` | Area metatile rows and attributes | Dynamic name-table and attribute updates | **Missing**; current area code does not emit the original output buffers. |
| `$89c3-$8acd` | Palette rotation and block/bridge metatile replacement | Palette and dynamic tile updates | **Missing**; replacement logic retains collision state only. |
| `$8e19-$8eed` | Name-table initialization, VRAM-buffer transfer, scroll, and PPU-control commit | All PPU-visible background state | **Partial**; initialization/title subset only. |
| `$92b0-$9bff` | Area parser and scenery/object metatile generation | Background page output and updates | **Partial**; parser state is translated, visible metatile output is not. |
| `$e700-$edff` | Enemy graphics and draw families | Enemy OAM tiles, attributes, ordering, and animation | **Missing**; current routes state that OAM is excluded. |
| `$eee9-$f12a` | Player graphics, action selection, offscreen calculation, and draw | Player OAM tiles, attributes, priority, and animation | **Missing**. |
| Later object-graphics families | Blocks, coins, fireballs, bubbles, platforms, Bowser, flame, and effects | Their OAM and dynamic VRAM output | **Missing**; exact subranges remain T9 direct-decode work. |

## Current Product Disqualification

`src/game/render.c` copies one name table and emits a player/enemy identity
marker. `src/platform/win32/main_win32.c` maps tile ranges to flat colors and
actors to rectangles. These paths may remain diagnostic views, but they are
not valid M2 gameplay output and cannot satisfy the snapshot contract.

## T9 Remaining Work

1. Resolve each later object-graphics source range directly from the admitted
   PRG and record its exact source address and RAM/OAM ownership.
2. Define the project-owned recorder serialization and bounded scripts without
   retaining raw reference traces.
3. Add a source-level snapshot ABI and tests that reject missing fields before
   T10 begins background-output translation.
