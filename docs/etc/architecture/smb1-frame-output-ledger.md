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
| PPU controls and scroll | 8 bytes | Mirrored `$2000/$2001`, name-table selection, committed scroll pair, and reconstructed PPU `v` address. |
| Audio command state | bounded neutral fields | Game-owned queues, events, and channel command state. |

The snapshot is an output record, not a PPU emulation API. The portable C
route owns the record; Win32, VGA, and text consumers only read it.

The source-level `game/frame_snapshot.h` contract separates `captured_fields`
from `verified_fields`. The first states that a byte range was copied from the
native state. The second remains clear until its source owner has passed the
owner-local reference comparison. A full M2 frame requires every contract
field in both masks, so an unimplemented PPU/palette/scroll path cannot become
valid merely because its storage happens to be zero.

## Audited Output Owners

| ROM range | Original owner | Required snapshot effect | Current C disposition |
| --- | --- | --- | --- |
| `$8082-$8181` | NMI display synchronization, controller/timer dispatch, and PPU control/scroll commit | Frame boundary, PPU control/scroll commit, OAM submission boundary | **Missing**; game tick has no NMI-output phase. |
| `$81c6-$81f9` | Sprite-offset shuffle and misc-sprite offset preparation | OAM ordering inputs | **Missing**; the helper is not translated as output ownership. |
| `$8220-$8227` | Move all sprites offscreen | OAM offscreen entries | **Partial**; RAM clear exists, but it is not submitted as OAM output. |
| `$8325-$833f` | Title mushroom icon | Tile/OAM title visual | **Partial**; title command data is consumed, icon/OAM route is absent. |
| `$84c3-$8566` | Floatey score numbers and screen-support sprites | OAM entries and score updates | **Missing**; logic explicitly excludes OAM. |
| `$8567-$864c` | Screen tasks, area/player palettes, and VRAM buffer addressing | Palette, buffer selection, name-table updates | **Partial**; the ROM-bound game path now executes screen tasks 0–12 before entering `GameCoreRoutine`: name-table initialization, player palette, top/bottom status, intermediate text/timers, and area setup transition have native owners. `$85f1 GetPlayerColors` derives and queues the ROM `$3f10` sprite-palette command during area initialization and after a PPU-visible player-state change, including its background-color first byte. Title loading applies the ground palette followed by that player command, and the portable 32-byte palette backing state observes the 2C02 `$3f10/$14/$18/$1c` aliases. The title-stable palette hash matches the bounded local reference; Time Up/alternate-entry branches and buffer-address control remain incomplete. |
| `$8652-$889c` | Status text, two-player text, title, intermediate, and area display tasks | VRAM buffer writes, name-table and palette state | **Partial**; title plus initial gameplay top and bottom status commands reach the buffer and name table, including score, coin, world, and level digits. The title loader commits the fixed top status stream before its owner-local title transfer. `$9131` installs the header-selected three-digit timer on a new entrance; `RunGameTimer` queues time-running-out music at 100, appends its live three-digit `$207a` update, and calls the translated `ForceInjury` route at zero. The following NMI commits pending commands. The native `WriteGameText` route copies the ROM-authored lives, Time Up, Game Over, and Warp streams and patches their source-defined mutable bytes; live Time Up/Game Over/Warp dispatch and title area-display tasks remain incomplete. |
| `$88ae-$89bd` | Area metatile rows and attributes | Dynamic name-table and attribute updates | **Partial**; the admitted metatile table now expands collision pages and attributes into both name tables, while original incremental buffer scheduling and all scenery families remain incomplete. |
| `$89c3-$8acd` | Palette rotation and block/bridge metatile replacement | Palette and dynamic tile updates | **Partial**; area palette streams, queued palette-3 rotation, and block replacement refresh now reach the snapshot; bridge routes remain incomplete. |
| `$8e19-$8eed` | Name-table initialization, VRAM-buffer transfer, scroll, and PPU-control commit | All PPU-visible background state | **Partial**; initialization and the admitted `VRAM_Buffer1` transfer now reach the snapshot; status/title/gameplay screen tasks remain incomplete. |
| `$92b0-$9bff` | Area parser and scenery/object metatile generation | Background page output and updates | **Partial**; admitted terrain/object metatiles expand into visible name-table and attribute state, while incremental scenery families remain incomplete. |
| `$e700-$edff` | Enemy graphics and draw families | Enemy OAM tiles, attributes, ordering, and animation | **Missing**; current routes state that OAM is excluded. |
| `$eee9-$f12a` | Player graphics, action selection, offscreen calculation, and draw | Player OAM tiles, attributes, priority, and animation | **Missing**. |
| `$e6be-$e73d` | Power-up tile data and `DrawPowerUp` | Power-up OAM tiles, attributes, and offscreen state | **Missing**. |
| `$e73e-$ebd0` | Enemy tile tables, selection, and row drawing | Enemy/Bowser/platform OAM tiles, attributes, ordering, and animation | **Missing**. |
| `$ebd1-$ec52` | Block and brick-chunk drawing | Block, coin, and debris OAM state | **Missing**. |
| `$ec53-$eee0` | Fireball, firebar, explosion, and bubble drawing | Projectile and effect OAM state | **Missing**. |
| `$ee17-$f2cf` | Player tile table, action selection, player draw, and common sprite-row writer | Player/intermediate OAM tiles, attributes, priority, and animation | **Missing**. |

## Current Product Disqualification

`src/game/render.c` copies one name table and emits a player/enemy identity
marker. `src/platform/win32/main_win32.c` maps tile ranges to flat colors and
actors to rectangles. These paths may remain diagnostic views, but they are
not valid M2 gameplay output and cannot satisfy the snapshot contract.

## T9 Remaining Work

1. Use `tools/reference_frame_recorder.c` through the isolated
   `Build-ReferenceFrameRecorder.ps1` build to record reference frames at
   ROM `$8181`, immediately before the NMI `RTI`. Its `MSFR` v1 raw record is
   eight magic/version bytes and a 32-bit requested-frame count, followed by
   a 32-bit PPU frame sequence, 2048-byte CPU RAM, 2048-byte CIRAM, 32-byte
   palette, 256-byte OAM, PPU control/mask/name-table/scroll bytes, and a
   16-bit PPU address for each sample. This is 4,395 bytes per sample.
2. A recorder invocation is limited to 600 samples (2,637,012 bytes including
   header) and 512 reference-run calls without a sample per requested frame.
   It writes only to one caller-declared ignored output directory. The task
   executor deletes the raw trace after its neutral mismatch summary is
   recorded; no raw trace is evidence or a fixture.
3. The snapshot ABI and its smoke test reject complete status until every
   visible field is captured and reference-verified. T10 starts only after
   this contract is used by a translated background owner.
