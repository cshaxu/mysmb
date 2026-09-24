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
| `$8082-$8181` | NMI display synchronization, controller/timer dispatch, and PPU control/scroll commit | Frame boundary, PPU control/scroll commit, OAM submission boundary | **Partial**; the portable tick consumes the selected VRAM buffer at its NMI boundary, commits `$2000` increment/NMI and display-mask state into the snapshot, and retains source-owned scroll/name-table fields. OAM submission remains T11 work. |
| `$81c6-$81f9` | Sprite-offset shuffle and misc-sprite offset preparation | OAM ordering inputs | **Missing**; the helper is not translated as output ownership. |
| `$8220-$8227` | Move all sprites offscreen | OAM offscreen entries | **Partial**; RAM clear exists, but it is not submitted as OAM output. |
| `$8325-$833f` | Title mushroom icon | Tile/OAM title visual | **Partial**; the owner-local title generator extracts the icon's VRAM command and the title loader applies it after the title transfer. Its OAM-related title work remains T11 ownership. |
| `$84c3-$8566` | Floatey score numbers and screen-support sprites | OAM entries and score updates | **Missing**; logic explicitly excludes OAM. |
| `$8567-$864c` | Screen tasks, area/player palettes, and VRAM buffer addressing | Palette, buffer selection, name-table updates | **Partial**; the ROM-bound game path now executes screen tasks 0–12 before entering `GameCoreRoutine`: name-table initialization, player palette, top/bottom status, intermediate text/timers, and area setup transition have native owners. `$85f1 GetPlayerColors` derives and queues the ROM `$3f10` sprite-palette command during area initialization and after a PPU-visible player-state change, including its background-color first byte. Title loading applies the ground palette followed by that player command, and the portable 32-byte palette backing state observes the 2C02 `$3f10/$14/$18/$1c` aliases. The injected native title state has no verified ROM title-phase equality checkpoint; Time Up/alternate-entry branches, title-area display, and buffer-address control remain incomplete. |
| `$8652-$889c` | Status text, two-player text, title, intermediate, and area display tasks | VRAM buffer writes, name-table and palette state | **Partial**; title plus initial gameplay top and bottom status commands reach the buffer and name table, including score, coin, world, and level digits. The title loader commits both status streams before its owner-local title transfer. `$9131` installs the header-selected three-digit timer on a new entrance; `RunGameTimer` queues time-running-out music at 100, appends its live three-digit `$207a` update, and calls the translated `ForceInjury` route at zero. The following NMI commits pending commands. The native `WriteGameText` route copies the ROM-authored lives, Time Up, Game Over, and Warp streams and patches their source-defined mutable bytes; live Time Up/Game Over/Warp dispatch and title area-display tasks remain incomplete. |
| `$88ae-$89bd` | Area metatile rows and attributes | Dynamic name-table and attribute updates | **Partial**; the admitted metatile table now expands collision pages and attributes into both name tables, while original incremental buffer scheduling and all scenery families remain incomplete. |
| `$89c3-$8acd` | Palette rotation and block/bridge metatile replacement | Palette and dynamic tile updates | **Partial**; area palette streams, queued palette-3 rotation, and block replacement refresh now reach the snapshot; bridge routes remain incomplete. |
| `$8e19-$8eed` | Name-table initialization, VRAM-buffer transfer, scroll, and PPU-control commit | All PPU-visible background state | **Partial**; initialization and the admitted `VRAM_Buffer1` transfer now reach the snapshot; status/title/gameplay screen tasks remain incomplete. |
| `$92b0-$9bff` | Area parser and scenery/object metatile generation | Background page output and updates | **Partial**; admitted terrain/object metatiles expand into visible name-table and attribute state. The title loader invokes the same initial area route before overlaying the title stream, matching the original title task's ownership boundary. Incremental scenery families remain incomplete. |
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
2. A recorder invocation is limited to 600 NMI-return samples (2,637,012
   bytes including header) and 131,072 exact instruction steps per requested
   sample. This is the same maximum instruction work as the former 512
   driver calls of at most 256 instructions. It writes only to one
   caller-declared ignored output directory. The task executor deletes the
   raw trace after its neutral mismatch summary is recorded; no raw trace is
   evidence or a fixture.
3. The snapshot ABI and its smoke test reject complete status until every
   visible field is captured and reference-verified. T10 starts only after
   this contract is used by a translated background owner.

## T10 S1 P1 Parser-Column Foundation

`mysmb_area_render_scenery_terrain_column` is a C90 translation of the
`RenderSceneryTerrain` portion of `AreaParserCore`, with its source-owned
tables at `$92f7-$9507`. It produces one collision-qualified 13-metatile
column from the current page, current column, header scenery selectors, and
terrain selector. The project-owned smoke test uses synthetic table data to
cover background placement, foreground overwrite, terrain bits, cloud terrain
exception, and the four `BlockBuffLowBounds` filters.

This part was initially isolated for unit testing. P2 now connects the original
eight-step `AreaParserTaskHandler`, `$0341` `VRAM_Buffer2` column/attribute
commands, `$0773` buffer selection, and the next-NMI transfer to screen task
8. It remains partial: `ProcessAreaData` and its persistent object state are
not yet part of that parser core, so the pre-existing bounded object preload
still runs after the source-ordered scenery/terrain sets complete. This is not
frame-equivalence evidence.

### P2 Reference Check

A bounded owner-local 30-frame recorder probe sampled the original at the NMI
RTI under neutral input. During screen task 8, the original parser advances
`CurrentPageLoc`, `CurrentColumnPos`, `BlockBufferColumnPos`, and `ColumnSets`
as `00/00/00/0b` through `01/08/18/ff`. The native task control now follows
that same 12-set progression. A separate ten-frame probe established that the
first completed set fills terrain in physical columns zero and one; this caught
and corrected a reversed `JumpEngine` dispatch interpretation. Raw owner-ROM
traces were deleted after this neutral summary.

### Similar-Issue Sweep

The repair sweep searched `area.c`, `game.c`, and tests for bulk terrain page
generation, one-object-per-frame output, parser-task state, and physical block
buffer writes. `mysmb_area_render_initial_terrain`,
`mysmb_area_render_terrain_page`, `mysmb_area_render_initial_objects`,
`mysmb_area_emit_next_command`, and `mysmb_area_prepare_player_pages` remain
the older bulk or bounded routes. Task 8 no longer calls the terrain bulk
route. The bounded object preload remains only until `ProcessAreaData` replaces
it; none of these retained paths is claimed as the original incremental parser
path.

## T10 S1 P3 Object-Stream Baseline

A bounded owner-local 30-frame NMI probe captured the parser object state for
the first title-demo area load. The source begins with a page-control entry:
the header-following bytes are `07 81`, followed by `47 24`, `57 00`, and
`63 01`. The first entry advances `AreaObjectPageLoc` to one without occupying
an object slot. During the initial 12 column sets, all three length bytes stay
`ff` through page one, column four. At page one, column six, the ROM has
`AreaDataOffset=06`, slot offsets `00/04/02`, and lengths `ff/ff/02`; two
columns later it advances to offset `0a` and decrements the active slot to
zero. The corresponding 13-byte metatile buffers were summarized locally and
the raw trace was deleted.

This disproves the prior proposed shortcut of consuming one stream object per
parser column. P3 must translate page control, behind-renderer handling, and
the three persistent length slots before any family-specific object handler is
admitted. The old preload and one-object path remain explicitly partial.

## T10 S1 P4 Parser Slot State

`ProcessAreaData` stream control is now a portable C90 routine with the ROM
owners `$9508-$958f`: it maintains the three `$072d/$0730` parser slots,
page-select state, row-13 page-control advancement, column admission, and
active-slot length countdown. Family-specific handlers remain outside this
part, so this does not yet replace the temporary object preload or claim visual
equivalence. The ROM-free smoke test covers page control, column-matched
admission, and an active slot's subsequent countdown.

### Similar-Issue Sweep

The parser code and tests were searched for stream reads that advance once per
frame, page-control entries stored as regular objects, and direct block-buffer
writes before a family handler. The old `mysmb_area_next_object` and initial
preload remain retained compatibility paths and are explicitly excluded from
the new state owner until their callers move to the translated parser route.

## T10 S1 P5 Brick And Solid Rows

The `RowOfBricks` and `RowOfSolidBlocks` owners (`$4054-$4077`) are translated
within the parser-state owner: a newly admitted row object initializes its slot
length from the second byte's low nibble, overwrites its selected metatile row,
and then receives the original end-of-pass countdown. The smoke route covers a
ground-area brick row across its initial and next parser column. They remain
disconnected from the formal column transfer until the other loaded object
families have handlers; connecting only this subset overwrites valid existing
objects and fails the owner-local area route.

### Similar-Issue Sweep

The AreaParserCore path was checked for metatile writes occurring before the
scenery clear or after block-buffer transfer. The attempted partial connection
was rejected because it changed owner-local block-buffer state for unsupported
families. Other object families and the retained bulk preload remain deferred;
this change does not claim that their pixels or collision output are translated.

## T10 S1 P6 Small Blocks And Columns

The parser owner now translates the static metatile portions of normal question
and brick blocks, coin rows, brick columns, and solid-block columns. Their
address owners are `$4014-$4020`, `$4054-$4091`, and `$4179-$4201`. The
ROM-free parser test proves that small and vertical objects render once while
retaining an empty `AreaObjectLength` slot; horizontal rows alone create and
count down a persistent length. The handlers remain off the formal column path
until the object-family set is complete.

### Similar-Issue Sweep

The object decoder and parser handler were checked for treating the second
byte's d6-d4 selector as a length or treating every rendered object as
persistent. Small blocks and vertical columns now leave their slot at `ff`;
horizontal rows retain the low-nibble length. Animated block effects, pipes,
style objects, and special rows remain deferred.

## T10 S1 P7 Vertical Pipe Metatiles

The static `GetPipeHeight`/`VerticalPipe` metatile route (`$3837-$3894`) now
uses its original fixed horizontal length of one, low-three-bit shaft height,
and pipe-top/shaft table selection. The parser smoke test exercises the first
pipe column from a `0x71` object byte and verifies both metatiles and slot
countdown. Piranha-plant allocation and pipe transitions remain separate
dynamic-object owners; the pipe handler is not yet connected to formal column
output.

### Similar-Issue Sweep

Pipe processing was checked for incorrectly treating its low nibble as a
generic row length, and for updating enemy state from a static renderer. The
fixed-length parser slot and static metatiles are translated here. Dynamic
piranha creation, sideways pipes, and transition semantics remain deferred.

## T10 S1 P8 Special-Row Question Blocks

The parser now distinguishes the row-12/13/14/15 JumpEngine table from the
normal-row table. The two row-12 question-block row owners (`$3919-$3931`) use
selectors six and seven, set their fixed rows three and seven, and retain the
horizontal length slot. The parser smoke test covers selector seven specifically
so it cannot regress into the normal-row vertical-pipe handler.

### Similar-Issue Sweep

The object handler was searched for direct d6-d4 selector dispatch without a
row-table distinction. Normal-row selector seven remains vertical pipe; row-12
selectors six and seven now route to question-block rows. Other special rows
remain deferred.

## T10 S1 P9 Special-Row Holes And Bridges

The row-12 static `Hole_Empty`, `Hole_Water`, and three bridge handlers are
translated from `$3908-$3954` and `$4212-$4244`. They install original
hole/water/bridge metatiles at their fixed rows and initialize only the
horizontal length families. The parser smoke test covers a ground hole and a
high bridge across the parser slot state.

### Similar-Issue Sweep

The special-row handler was checked for normal-row fallthrough and for using
the source byte's lower nibble as vertical height. Holes and bridges now use
their special fixed row positions and horizontal length. Whirlpool allocation,
pulley ropes, and collapse behavior remain deferred dynamic owners.

## T10 S1 P10 Row-15 Ropes And Staircases

The row-15 dispatcher now admits the static `EndlessRope`, `BalancePlatRope`,
and `StaircaseObject` metatile paths (`$3993-$4010`, `$4126-$4143`). Ropes use
their original top-to-bottom or bounded height rules; a staircase initializes
its source-owned control byte and consumes one original step per parser column.
The parser smoke test covers both a full rope and a newly started staircase.

### Similar-Issue Sweep

The dispatcher was checked for a generic row-range rejection masking the
row-15 JumpEngine table. It now rejects only unimplemented rows 13 and 14.
Row-15 rope and staircase paths are explicit. Castle, exit-pipe, and dynamic
balance-platform behavior remain deferred.

## T10 S1 P11 Row-13 Flagpole Metatiles

The row-13 low-six-bit object table now translates the static `FlagpoleObject`
metatile writes at `$3966-$3974`: ball, shaft, and base. Its owner-specific
flag object, floatey number, and score state remain dynamic-object work. The
parser smoke test verifies row-13 code one cannot fall through the ordinary
object selector table.

### Similar-Issue Sweep

Row-13 parsing was checked for interpreting d6-d4 as a normal object family.
The static flagpole now dispatches by its dedicated object code. Intro pipe,
axe, castle bridge, and frenzy objects remain deferred.

## T10 S1 P12 Area-Style Objects

The normal-row `AreaStyleObject` static metatile paths now translate the tree,
mushroom, and cannon choices from `$3621-$3676` and `$4095-$4109`. Tree and
mushroom ledges initialize and revisit their persistent slots; cannon visual
segments are static only. The parser smoke test covers a tree start and its
following middle-column replay from the saved object offset.

### Similar-Issue Sweep

Style object handling was checked for treating selector one as an empty family
or rereading a later stream record while its slot is active. The parser now
uses the saved object offset for persistent ledges. Cannon firing and dynamic
platform behavior remain deferred.

## T10 S1 P13 Metatile Overlap Rules

The parser now shares the exact `RenderUnderPart` staging-column rule from
`$4247-$4273` for vertical pipe shafts and brick/solid columns. It preserves
tree and mushroom ledge centers and palette-three foreground metatiles, while
allowing a coin block (`$c0`) and ordinary scenery to be overwritten. The
special cracked-rock/mushroom-stem condition is retained as the source's
comparison of an existing `$54` against an incoming `$50`. The ROM-free parser
smoke test seeds each relevant existing metatile and verifies the replacement
or preservation result through the public parser owner.

### Similar-Issue Sweep

The static handlers were searched for duplicated vertical overwrite loops.
The pipe shaft and both brick/solid column paths now call one C90 helper with
the original row/height stop condition. Direct top and cap writes remain with
their owning object routines; dynamic objects and the formal column transfer
remain deferred.

## T10 S1 P14 Exit-Pipe Metatiles

The row-15 `ExitPipe` static renderer is translated from `$3810-$3835`. It
uses the original fixed length of three, the four-column sideways-pipe tables,
and the two trailing shaft columns through the shared `RenderUnderPart` rule.
The parser smoke test proves the first three source columns, their countdown,
and the first shaft metatile. Player entrance/exit state remains a dynamic
logic owner and is not claimed by this background implementation.

### Similar-Issue Sweep

The row-15 table was checked for a generic staircase or rope fallthrough.
Exit-pipe length and vertical geometry are now independent from the source
location-byte row selector. Intro pipe, transition state, and warp routing
remain deferred.

## T10 S1 P15 Formal Parser-Column Integration

`RenderSceneryTerrain` now follows the original `$936f-$9376` order: it first
creates the scenery/terrain staging column, then runs `ProcessAreaData`, and
only then writes collision-qualified metatiles to the physical block buffer.
The eight-step parser task therefore owns the initial visible area output; the
game tick no longer consumes the same area stream through the incompatible
one-object-per-frame diagnostic producer. A ROM-free test establishes that an
admitted brick-row object changes both the staging column and its committed
block-buffer cell. The owner-local ROM smoke continues through screen task 8
using the formal parser state.

### Similar-Issue Sweep

`mysmb_area_emit_next_command` remains as a diagnostic API only and is no
longer called by the native game path. The older bulk page preparation and
initial object preload remain separate migration work; they are not evidence
for the incremental parser route and must be removed or replaced before T10
can close.

## T10 S1 P16 Pulley-Rope Metatiles

The static row-12 `PulleyRopeObject` route at `$3680-$3694` now emits its
source-defined left pulley, rope, and right pulley sequence at row zero while
using the existing parser slot length. The smoke test covers all three columns
and their countdown states. Balance-platform movement and collision state are
separate dynamic owners.

### Similar-Issue Sweep

The row-12 dispatcher was checked for treating selector one as a bridge or a
normal-row style object. It now has an explicit static pulley route; no
platform state is synthesized in the background parser.

## T10 S1 P17 Row-13 Static Pipe And Castle Objects

The static row-13 table now translates `IntroPipe` (`$3785-$3798`) and the
`AxeObj`/`ChainObj`/`CastleBridgeObj` metatile route (`$4024-$4050`). Intro
pipe retains the source's fixed four-column sideways data, its late vertical
cap/shaft column, and the original slot countdown. Axe, chain, and bridge use
the source row/metatile table, with the bridge's fixed length of twelve. The
parser smoke test covers the pipe sequence and the axe/bridge entries.

### Similar-Issue Sweep

The row-13 low-six-bit dispatcher now distinguishes background metatile codes
zero through four from flag, warp, scroll-lock, frenzy, and victory state.
Only the static PPU-address-control write owned by `AxeObj` is retained here;
game-mode, enemy, and transition effects remain deferred.

## T10 S1 P18 Continuous Parser Scheduling

The GameCore tail now translates the original `$94a5-$9539` parser trigger:
after NMI has committed pending column output, it executes one active parser
subtask per frame or begins one after each 32 accumulated scroll pixels. This
replaces the native game tick's bulk `prepare_player_pages` fallback, so
scrolling advances the same persistent `ProcessAreaData` state that generated
the initial lead-in. The source's VRAM-buffer-controller guard and buffer-two
reset are preserved.

### Similar-Issue Sweep

The game path no longer calls bulk terrain-page preparation. The legacy bulk
functions remain only for title/diagnostic compatibility and are explicitly
outside the gameplay parser route. Their callers must not be used as output
equivalence evidence.

## T10 S1 P19 Area Attribute Objects

The row-14 `AlterAreaAttributes` branch is translated from `$3536-$3562`.
With bit 6 clear it writes the terrain selector from the low nibble and the
background selector from bits 5-4. With bit 6 set it writes a foreground
selector below four, or writes background color four through seven while
clearing foreground, exactly as the source branch does. The ROM-free parser
smoke test covers all three observable attribute outcomes through the public
parser state owner.

### Similar-Issue Sweep

Row 14 remains an attribute-only stream item: it neither allocates a parser
slot length nor emits a metatile. Palette application and scenery generation
continue to own the later consumption of these fields; dynamic graphics and
PPU output remain outside this parser slice.

## T10 S1 P20 Flagball Residual Metatiles

The row-15 selector-five `FlagBalls_Residual` path is translated from
`$3958-$3964`. It begins at metatile row two and invokes the shared
`RenderUnderPart` rule with the second object's low nibble as its downward
extent and `$6d` as its source metatile. It does not allocate a parser-length
slot. The ROM-free parser smoke test proves the three metatiles produced by a
height-two object and the retained empty slot.

### Similar-Issue Sweep

This residual renderer is kept separate from `FlagpoleObject`: the latter's
flag actor, score, and OAM work remain deferred dynamic owners. No flag
object state is created by this background-only route.

## T10 S1 P21 NMI Display-State Commit

The native NMI boundary now translates the PPU-control details in
`$740-$842` and the command increment selection in `$2457-$2478`. A VRAM
command selects `$2000` d2 only while it transfers; the NMI tail restores the
mirror control byte, clears that transient d2 state, and sets `$2000` d7 for
the canonical RTI-boundary snapshot. The same boundary restores the source
display-mask bits according to `DisableScreenFlag`. The snapshot smoke test
covers vertical command increment during transfer, enabled display, and the
disabled-screen mask result.

### Similar-Issue Sweep

The change only commits scalar PPU-visible state after existing native logic
has updated its scroll/name-table fields. It does not submit OAM graphics,
invent a host PPU, or claim reference-frame verification; those remain owned
by T11 and T13.

## T10 S1 P22 Incremental Block Metatile Updates

`BlockObjMT_Updater` and its `WriteBlockMetatile`/`PutBlockMetatile` output
route (`$bed4`, `$2027-$209d`) now update the collision block buffer and queue
the original pair of two-tile name-table commands in `VRAM_Buffer1`. The
source loop starts with block slot one and stops its other slot while the
first command occupies the buffer; the following NMI is the only path that
makes the update PPU-visible. The core smoke test covers command bytes,
slot ordering, collision state, and the two committed name-table rows.

### Similar-Issue Sweep

The old whole-page `refresh_background_page` shortcut was removed from this
dynamic replacement owner. Palette choice uses the original five
`BlockGfxData` cases and no platform renderer decides the result. Bouncing
block, brick debris, coin, and item sprites remain T11 OAM owners.

## T10 S1 P23 Owner-Local NMI Phase Baseline

An isolated recorder build ran the admitted owner ROM at the NMI RTI boundary.
The accepted controller script was `40:0x08,42:0`: the recorder uses NES
serial order, so Start is bit three rather than the portable game's internal
button representation. At sampled frame 40 the original enters game mode
task zero; frame 41 is game task one with screen task zero; frame 42 has
screen output disabled (`$2001=$06`); and by frame 220 it is game task three,
engine subroutine eight, with parser page/column `01/08`. The sampled final
PPU control is `$90`, and screen-visible phases use `$2001=$1e`.

The probes were limited to 120, 180, and 600 frames respectively. Each raw
`MSFR` trace stayed in its unique ignored output directory and was deleted
immediately after this neutral summary; no ROM bytes, trace data, or
recoverable graphics were retained.

### Next Difference Owner

The next owner-local comparison must drive the translated Start route to the
same screen-task and parser checkpoints, then compare canonical RAM,
name-table, palette, scroll, and PPU fields at the declared NMI boundary.
OAM is deliberately recorded but remains T11 scope.

## T10 S1 P24 Preserve Display Mask Through Name-Table Setup

The native `InitializeNameTables` owner no longer clears the portable `$2001`
state. The original `$8e19-$8e5b` clears name/attribute tables and commits
the `$2000` arrangement but does not write the display-mask mirror; cold boot
alone initializes that field. The snapshot smoke test covers preservation,
and the owner-local phase probe now observes `$2001=$06` at local screen task
one, matching the recorded disabled-screen reference phase.

## T10 S1 P25 Live Coin and Score Status Commands

The missing `GiveOneCoin`/`AddToScore` continuation is translated from
`PrintStatusBarNumbers` at `$8ebe-$8ef7`. Coin collection, brick score, and
floatey-score settlement now append the source's two commands to
`VRAM_Buffer1`: current-player coins at `$206d` followed by the six-digit
score at `$2062`. The selector offsets are source-derived: Mario reads coin
digits 22--23 and score digits 6--11 from `DisplayDigits`; Luigi reads
28--29 and 12--17. The initial bottom-status writer uses the same corrected
coin offsets. The first emitted zero score digit becomes tile `$24`, as in
the ROM.

The core smoke test checks the queued bytes and applies them through the NMI
command consumer, proving the two live values reach the canonical name table.

### Similar-Issue Sweep

The timer remains its own selector `$a4` command and may share a pending NMI
list. This repair does not draw the coin or score sprites, produce OAM, or
interpret presentation on the host; those boundaries remain T11 work.

## T10 S1 P26 Initial Area Display-Mask Phase

The owner-local 240-frame NMI probe used the admitted Start script
`40:0x08,42:0` and retained only neutral summaries. At original checkpoints
41--42 the game is in mode one, task one with `$2000=$90` and `$2001=$06`.
The translated route had `$2001=$00`, because title completion never restored
the visible mask and `AreaParserTaskControl` omitted its source `inc
DisableScreenFlag` at `$86e6`. The title completion now restores the visible
mask, and the parser owner increments the disable flag before a two-column
set. Native checkpoints 41--42 now carry `$2000=$90/$2001=$06`; after setup,
task three carries `$90/$1e`.

The audit also corrected a NMI-boundary capture error: d2 is temporary for a
VRAM command and must be cleared when the source reloads its `$2000` mirror
before RTI. The frame snapshot test proves this restoration. The probe's raw
trace was deleted immediately after summary; no ROM bytes or frame records
are tracked.

### Remaining Difference Owner

Initial name-table and palette checksums still differ after phase alignment.
Those differences remain T10 background-route work; this record does not
claim frame equivalence or M2 closure.

## T10 S1 P27 Initial Attribute-Table Difference Isolation

The admitted 240-frame Start route was sampled at frame 202, when both
implementations have completed the initial two-page block-buffer load while
screen output is disabled. The two source-compatible `Block_Buffer` pages
match byte-for-byte (512 of 512 bytes). Name-table comparison has 61 differing
bytes: one tile byte and 60 attribute-table bytes (45 in page zero and 16 in
page one). The differences are therefore downstream of metatile parsing.

An adjacent native-frame sweep against the original frame-202 NMI record
produced 144, 121, 89, 61, 61, and 61 differences for native frames
199 through 204. The stable residual rejects a one-frame VRAM commit offset;
the next owner is the attribute-byte construction/address path.

All temporary original and native snapshots were deleted after these neutral
counts were produced. No snapshot bytes or ROM-derived graphics are tracked.

## T10 S1 P28 Attribute Command Vertical Address Step

The effective frame-201 `VRAM_Buffer2` comparison isolated six differences
at the low-address header byte of consecutive attribute commands. Source
`RenderAttributeTables` at `$8985-$898c` reloads its low byte and adds eight
for every attribute row. The native route instead emitted `low + 8` once and
then advanced the saved value by one, leaving the first command correct and
misaddressing the following six rows. The queue now advances its saved low
address by eight before each command; the parser smoke test asserts the
vertical low-address step.

With the same bounded Start script, the frame-202 name-table comparison fell
from 61 differences to one. The remaining byte is name-table zero offset
`$062`, the leading Mario score-status tile, and is a separate status-number
owner. Original and native temporary snapshots were deleted after producing
this neutral result.

## T10 S1 P29 Initial Name-Table Match

`WriteBottomStatusLine` now applies the same first-score-zero blanking rule
as `UpdateNumber`, replacing the emitted zero with tile `$24`. A fresh
owner-local reference run with the admitted `40:0x08,42:0` Start script
compared both 1024-byte name tables at frame 202 and found zero differences.
This establishes the initial 1-1 background tile and attribute state at the
declared NMI boundary; it does not establish palette, scroll, OAM, or later
gameplay-frame equivalence. The temporary reference trace and native snapshot
were deleted immediately after the neutral count.

## T10 S1 P30 Initial Palette Phase

The same admitted Start route was checked after the initial palette-owner flow
at frame 206. The original and translated 32-byte PPU palette snapshots have
zero differing offsets at that checkpoint. An earlier frame-202 check had 12
differences while the parser/display transition was still in progress, so it
is not a valid substitute for the completed palette-owner checkpoint.

This records only the palette bytes. Scroll, PPU scalar state, OAM, and
later-frame equality remain open T10/T11 work. The temporary reference trace
and native snapshot were deleted after the neutral count.

## T10 S1 P31 NMI Display Mirrors

The original NMI owner at `$0740-$0842` keeps two different results: the
physical `$2000` value at RTI has NMI re-enabled, while RAM `$0778`
(`Mirror_PPU_CTRL_REG1`) retains the pre-RTI mirror without d7. RAM `$0779`
(`Mirror_PPU_CTRL_REG2`) retains the selected display mask. Native code had
only maintained its portable visible fields, leaving both RAM bytes zero.

`mysmb_game_commit_display_state` now saves the pre-restoration control
mirror, including a command-selected d2 when present, and saves the resolved
mask. `InitializeNameTables` establishes the source `$10` control mirror.
The ROM-free snapshot smoke covers initialization, a vertical command, NMI
restoration, and both mask outcomes. The owner-local summary was extended to
print only display-mirror and scroll metadata. Across frames 201--210 of the
admitted Start route, original and native agree on `$0778`, `$0779`,
`DisableScreenFlag`, `HorizontalScroll`, and `VerticalScroll`.

The recorder's physical PPU address is not used as a camera oracle: at the
NMI return it can reflect a preceding VRAM-address write rather than the
source scroll variables. The canonical snapshot's semantic scroll record and
later scrolling routes remain T10 work. The bounded raw trace was deleted
after the neutral metadata comparison.

### Similar-Issue Sweep

The display-field sweep covered every production and test reference to
`ppu_control_0`, `ppu_mask`, `$0778`, and `$0779`. Initialization and the NMI
commit were the two missing RAM-mirror writers and are corrected here.
`WriteBufferToScreen` keeps its command-local d2 selection so the NMI can
preserve the source mirror before restoring the physical output. The player
scroll owner supplies the name-table bit before that commit. Snapshot capture
remains a read-only copy and needs no writer. No host renderer or OAM path was
changed; those remain outside T10.

## T10 S1 P32 Right-Scroll Physics Isolation

The local summary now accepts the recorder's bounded `frame:buttons` syntax
and reports neutral player/scroll metadata. Its values are MySMB decoded masks;
the validation recorder uses controller serial masks, so the admitted right
route is `240:0x01` for native and `240:0x80` for the reference.

The route exposed two translation errors in the `PlayerCtrlRoutine`,
`PlayerMovementSubs`, `X_Physics`, `ImposeFriction`, and
`MovePlayerHorizontally` owners. First, zero player speed falls through
`beq PlayerSubs` without changing `Player_MovingDir`; native C had forced it
to right. Second, original `MoveObjectHorizontally` uses
`SprObject_X_MoveForce` at `$0400` for player offset zero, while
`Player_X_MoveForce` at `$0705` belongs to friction. Native C had combined
the two accumulators. The direct smoke test now proves that movement carries
through `$0400` without changing `$0705`.

With Start at frames 40--41 and held right from frame 240, native and original
match every checked player position/page, relative position, speed, movement
force, screen-left coordinate, horizontal scroll, and display mirror through
frame 353. The next comparison finds a remaining first difference at frame
354: source `ScreenLeft_X_Pos` is `$45`, native is `$47`. At that frame the
original also holds player position at `$b5`, while native advances it to
`$b7`. This is recorded as an open player/object-frame owner, not masked as a
scroll rounding adjustment.

### Similar-Issue Sweep

The movement-force sweep covered every native writer of `$0400` and `$0705`,
the direct movement primitive, friction, skid handling, player collision, and
the route smoke. Only the primitive used the wrong owner; friction and skid
continue to own `$0705`. The zero-speed direction assignment was the only
native unconditional `Player_MovingDir` publication; it now retains the
source value. No PPU renderer, OAM producer, or host input path changed.

## T10 S1 P33 Reference Frame Uniqueness And PPU d2

The earlier `frame_revision` de-duplication rule is withdrawn. A direct
instruction-step recorder audit shows two distinct returns at `$8181` can
share one PPU revision: at revision 11, the first return leaves `$077f` at
`$0f` and the next leaves it at `$0e`. They are two source timer states and
must be recorded separately. The reference frame ordinal is therefore the
NMI-return sequence; `frame_revision` remains metadata and may repeat or
have gaps.

The recorder now steps past every observed RTI and records each return unless
the PPU revision regresses. It no longer uses the driver/breakpoint batch
loop, which could hide a same-revision return. This local validation tool is
not part of the native product.

The d2 repair remains valid. With the corrected sequence, original and native
both retain `$14/$94` after the vertical command and both return to `$10/$90`
after the following horizontal command in the admitted right-route window.

## T10 S1 P34 Recorder Boundary Audit And Timer Ordering

The recorder samples immediately before the NMI RTI and advances its input
script only after that sample. A comparison declares its NMI-return ordinal,
input script, and source state fields; it does not use physical PPU-frame
count as the game-tick index. The bounded Start route now aligns the original
and native screen task, operating-mode task, game-engine subroutine, `$077f`,
and `$0787` through the entrance-to-play transition at samples 204--211.

The local summary now exposes the source-owned scheduler bytes needed to make
that alignment reviewable: `$073c`, `$0747`, `$077f`, `$0787`, `$07a0`, the
three game-timer digits, and the pending VRAM-buffer header. During this
audit, `RunGameTimer` was moved after the translated game-engine dispatcher:
the source state can enter subroutine 8 and load its first 24-frame game
timer interval in that same NMI-owned frame. The corrected exact-NMI trace
now verifies that dependency instead of leaving it as an inference.

### Similar-Issue Sweep

The scheduler sweep covered every production caller of `mysmb_game_run_timer`,
the shared timer decrement owner, the screen-task timer state, and the
owner-local summary. `game.c` has one timer-route caller, so no parallel
production ordering path remains. The recorder sweep covered duplicate,
equal, increasing, and regressing PPU revisions at `$8181`. The summary is
test-only and contains no ROM data. No OAM producer, host renderer, or runtime
reference dependency changed.

## T10 S1 P35 Dynamic Buffer Separation

The admitted Start/right route has a stable comparable window at NMI samples
370--379. In that window the original and native values agree for parser task
`$071f`, scroll accumulator `$073d`, both VRAM-buffer offsets and checked
command bytes, game-timer control and digits, and the PPU control mirror.
The matched command sequence includes `$2498`, `$2499`, `$249a`, `$249b`,
`$27ce`, and the live status update `$207a/03:09:03`. The apparent one-sample
timer delay was caused solely by dropping the same-revision NMI return.

The local diagnostic summary now also reports both VRAM buffers plus parser
task and scroll-accumulator state. It is a ROM-free test executable: it emits
only native state and hashes, never owner-ROM bytes.

### Similar-Issue Sweep

The separation sweep covered both buffer offsets and producers, the parser
tail, screen-routine transition, and `RunGameTimer` eligibility. Both buffer
paths are source-aligned over the declared window. OAM and host rendering
remain separately incomplete T11/T12 owners; the reference runtime is
validation-only and remains outside the product.

## T10 S1 P36 Dynamic Pipe Continuation

The stable Start/right route has an exact background window at NMI samples
370--379: both vertically mirrored CIRAM pages and palette match the native
snapshot. The earlier claim that sample 377 was the first CIRAM difference
was based on a temporary native dump that accidentally omitted the held-right
input script; it is withdrawn.

The source parser's vertical-pipe continuation at `$9929` selects a different
pipe-table row from its first-column pass. The C parser now preserves the
one-column object length state before selecting that row. A synthetic two-pass
smoke test covers both the new-object and continuation values, without
containing owner-ROM data. This correction is source-semantic; the table and
its data remain owner-local inputs.

### Similar-Issue Sweep

The sweep covered the parser staging buffer, graphics-column writer,
attribute writer, buffer terminator, active object slots, and every native
pipe-table use. The table data is unchanged. Other pipe encodings remain
subject to the same stateful parser comparison before any shared formula is
altered.

## T10 S1 P37 Exact Trace Comparator

`test/local_frame_recorder.c` writes a bounded owner-local `MSFN` v1 native
trace in the reference recorder's 4,395-byte record layout. It samples one
native tick after the translated NMI output phase and accepts the same bounded
Start/release plus held-input syntax as the local summary tool. The trace is
not a product path, fixture, or evidence artifact; it is written only under
an ignored build directory and deleted immediately after comparison.

`tools/Compare-M2FrameTrace.ps1` validates both trace headers and lengths,
enforces the 600-sample limit, and compares CPU RAM, each CIRAM page, palette,
OAM, and PPU scalar fields independently. SMB1's mapper-0 vertical mirroring
maps the two physical CIRAM pages directly to the two native name tables. The
recorder reads nnes PPU `t` plus fine X at RTI, rather than render-time `v`:
the source has just written `$2005/$2000`, so `t` is its next-frame committed
scroll/name-table state. The leading reference PPU revision and native tick
sequence are labels, not output bytes, and are therefore not compared.

The comparison report also splits CPU RAM into zero page, 6502 stack,
OAM-backed RAM, and `$0300-$07ff` working RAM. Stack bytes are reported for
trace transparency but are not a translated persistent-state target; the
other three groups retain source ownership and must be assigned before M2
closure.

On the admitted 380-sample Start/right route, title samples 0--41 still have
background differences. Samples 42--379 have exact CIRAM pages; samples
240--379 have exact palette and all PPU scalar state, including the reconstructed
committed address. CPU RAM and OAM still differ in the gameplay window. OAM
is T11 ownership; RAM differences require field-by-field ownership before
they can be assigned to T10 or a later task. This comparator replaces
summary-hash claims for all subsequent M2 frame evidence.

## T10 S1 P38 Static Screen-Routine Palette Chain

The source ScreenRoutines chain at `$8567-$864c` does not make a static
palette visible when the area header is parsed. `InitScreen` selects its
initial static stream through the address-control table, `SetupIntermediate`
queues player colors, and `GetAreaPalette` later selects the final area stream.
NMI `UpdateScreen` owns each selected stream's visible transfer.

The native route now preserves that ownership: area-header parsing leaves
palette transfer pending; screen tasks 0 and 9 select the source-defined
static table entries; and the translated NMI buffer transfer consumes entries
1--4 before ordinary buffer paths. A local timing smoke test reaches the
post-SecondaryGameSetup NMI boundary before checking the resulting palette,
rather than treating the header parser as a PPU writer.

The owner-local 0--239 Start route reduced palette byte differences from
2,432 to 673 while retaining the existing exact 240--379 gameplay palette,
CIRAM, and PPU-scalar window. The remaining title/intermediate palette
differences are separate screen-task and title-path owners; they are not
hidden by a direct header write.
