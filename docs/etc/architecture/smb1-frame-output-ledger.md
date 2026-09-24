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
| `$8082-$8181` | NMI display synchronization, controller/timer dispatch, and PPU control/scroll commit | Frame boundary, PPU control/scroll commit, OAM submission boundary | **Translated, partial OAM scope**; the portable tick consumes the selected VRAM buffer at its NMI boundary, commits `$2000` increment/NMI and display-mask state into the snapshot, retains source-owned scroll/name-table fields, and submits CPU `$0200-$02ff` to distinct hardware OAM state before the source frame writers run. Remaining OAM draw writers remain T11 work. |
| `$81c6-$81f9` | Sprite-offset shuffle and misc-sprite offset preparation | OAM ordering inputs | **Translated, partial OAM scope**; the source arithmetic, three-way rotation, and `Misc_SprDataOffset` derivation now write canonical OAM inputs. Draw families remain T11 work. |
| `$8220-$8230` | Move all/all-but-sprite-zero sprites offscreen | OAM offscreen entries | **Translated, partial OAM scope**; both source loops write `$0200` backing state, which the NMI submission boundary transfers to canonical hardware OAM state. Draw families remain T11 work. |
| `$8325-$833f` | Title mushroom icon | Tile/OAM title visual | **Partial**; the owner-local title generator extracts the icon's VRAM command and the title loader applies it after the title transfer. Its OAM-related title work remains T11 ownership. |
| `$84c3-$8566` | Floatey score numbers and screen-support sprites | OAM entries and score updates | **Translated, partial OAM scope**; FloateyNumbersRoutine writes its source-selected two-sprite score entries, while title and other screen-support sprites remain T11 work. |
| `$8567-$864c` | Screen tasks, area/player palettes, and VRAM buffer addressing | Palette, buffer selection, name-table updates | **Translated, background scope**; tasks 0--14, controls 1--18, player/background palettes, title transfer, and the mushroom alternate palette route have translated C owners. Sprite preparation remains T11 work. |
| `$8652-$889c` | Status text, two-player text, title, intermediate, and area display tasks | VRAM buffer writes, name-table and palette state | **Translated, background scope**; title/status/live-number, intermediate, Time Up, Game Over, Warp, and parser-display commands use the source-shaped buffers and NMI transfer. Intermediate player sprites remain T11 work. |
| `$88ae-$89bd` | Area metatile rows and attributes | Dynamic name-table and attribute updates | **Translated, background scope**; the incremental parser emits metatile rows, attributes, and buffer-two commands through the canonical snapshot. |
| `$89c3-$8acd` | Palette rotation and block/bridge metatile replacement | Palette and dynamic tile updates | **Translated, background scope**; palette rotation, block replacement, coin removal, and bridge collapse submit their source-shaped commands. Their animated sprites remain T11 work. |
| `$8e19-$8eed` | Name-table initialization, VRAM-buffer transfer, scroll, and PPU-control commit | All PPU-visible background state | **Translated, background scope**; initialization, controls 1--18, both VRAM buffers, display mask, scroll, name-table selection, and committed PPU address are owned by the portable NMI boundary. OAM draw writers remain T11 work. |
| `$92b0-$9bff` | Area parser and scenery/object metatile generation | Background page output and updates | **Translated, background scope**; persistent parser slots, scenery, terrain, all static object metatile families, attributes, and incremental column scheduling reach the snapshot. Object graphics remain T11 work. |
| `$e700-$edff` | Enemy graphics and draw families | Enemy OAM tiles, attributes, ordering, and animation | **Translated, partial OAM scope**; the Goomba writer emits the six ROM tiles, pair ordering, palette attributes, direction flip, world-to-screen X, and three-row OAM layout. Other enemy families remain T11 work. |
| `$eee9-$f12a` | Player graphics, action selection, offscreen calculation, and draw | Player OAM tiles, attributes, priority, and animation | **Translated, partial OAM scope**; normal player action selection, ROM-table tile rows, horizontal flip, attributes, injury blink, and prepared vertical-offscreen rows write OAM. Fireball-throw supplement and title/intermediate paths remain T11 work. |
| `$e6be-$e73d` | Power-up tile data and `DrawPowerUp` | Power-up OAM tiles, attributes, and offscreen state | **Translated**; the dedicated slot-five power-up writer emits the original two-row sprite square, type tiles, palette cadence, mirror flags, and world-to-screen X position. |
| `$e73e-$ebd0` | Enemy tile tables, selection, and row drawing | Enemy/Bowser/platform OAM tiles, attributes, ordering, and animation | **Missing**. |
| `$ebd1-$ec52` | Block and brick-chunk drawing | Block, coin, and debris OAM state | **Translated, partial OAM scope**; bouncing blocks and four brick chunks use source tiles, frame attributes, coordinates, and screen-edge clipping. Coin and other debris routes remain T11 work. |
| `$ec53-$eee0` | Fireball, firebar, explosion, and bubble drawing | Projectile and effect OAM state | **Translated, partial OAM scope**; regular fireball and fireball-explosion OAM are translated; firebar, bubble, and other effects remain T11 work. |
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
reference recorder reconstructs name-table selection, scroll, and address from
SMB1's `$0778/$073f/$0740` committed mirrors at RTI. Direct title-data reads
can alter nnes's internal PPU latch without changing that source-owned display
state. The leading reference PPU revision and native tick sequence are labels,
not output bytes, and are therefore not compared.

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

## T10 S1 P39 Title VRAM Task And NMI Route

The product Win32 composition root no longer writes title commands directly to
the portable name tables. It binds its owner-local title streams and begins
the translated title ScreenRoutines route. Task 12 copies the title stream to
the original CPU-RAM title buffer, selects address-control 5, and the next
translated NMI transfers that buffer. Task 13 clears the same buffer space,
queues the player-selection icon in the normal VRAM buffer, and the following
NMI consumes that command. Task 14 then hands control to the title menu.

The local bootstrap smoke drives the route through its source timer waits and
proves all three boundaries: address-control 5 is observed, the icon buffer
is queued, and the resulting state is title-menu mode. The frame summary and
trace recorder intentionally retain their prebuilt-title harness because the
current admitted reference script starts at that phase. They are validation
tools, never the product path, and this change makes no title-frame equality
claim.

### Similar-Issue Sweep

The sweep covered every product consumer of the generated title data, every
title command direct-write call, all address-control branches, and the local
title tests. The Win32 product root is the only product consumer and now uses
the staged route. Direct command application remains only in unit and
validation harnesses whose stated phase is prebuilt title state. No host
renderer, OAM producer, or runtime reference dependency was added.

## T10 S1 P40 Post-Title-Route Background Regression

The title VRAM task change was rechecked against the admitted 380-sample
Start/right script. The owner-local comparison covered samples 240--379 and
found zero differing bytes in both CIRAM pages, palette, PPU control, mask,
name-table selection, scroll coordinates, and reconstructed PPU address.

CPU RAM differs in every sampled frame, including OAM-backed RAM and working
RAM. OAM also differs in every sampled frame. Those results preserve the
ledger's T11 boundary and do not support an OAM or complete-state claim. The
raw traces were created in one ignored diagnostic directory and deleted by
the command that performed the comparison.

## T10 S1 P41 CPU-RAM Difference Ownership

The trace comparator now reports the most frequently differing CPU-RAM
addresses as neutral address/count pairs. On the admitted gameplay window,
the persistent low-RAM differences include `$006f-$0072` and `$0088-$008b`,
the enemy page and horizontal-position slots, plus `$00a8-$00ab`, the block
and miscellaneous vertical-motion slots. They are actor-state owners whose
visible output is OAM work, rather than background name-table ownership.

The remaining frequent entries at `$0001` and `$0006` are source scratch
bytes at the NMI return boundary. Stack and scratch bytes remain trace
transparency data, not translated persistent-state targets. This classifier
does not suppress any difference; it makes the T10/T11 handoff reviewable.

## T10 S1 P42 Title Baseline Limitation

The prebuilt-title helper and the translated ScreenRoutines bootstrap both
reach title-menu mode, but they are not interchangeable output baselines. A
local comparison found 64 name-table positions and one palette position
different after the bootstrap completes. The first name-table difference is
at its first position, so this is a construction-order difference rather than
a late timer race.

The product uses the translated bootstrap. The prebuilt helper remains only
for the established gameplay reference phase. It must not be used to assert
title-frame equality or to overwrite the bootstrap result. A title-phase ROM
oracle needs a separately aligned source checkpoint before T10 can make a
title-output equality claim.

## T10 S1 P43 Title Intermediate-Display Branch

The source `DisplayIntermediate` route bypasses intermediate-lives text and
its screen-timer waits when operating in title mode, proceeding directly to
the area-parser task. The native screen-task translation had missed that
condition, delaying the product title menu beyond the reference Start phase.
It now branches directly for title mode.

The local bootstrap smoke verifies that the staged title transfer, icon queue,
and title-menu handoff all complete before frame 40, the admitted Start-input
phase. The full x64 suite and x86 build passed after the repair. This proves
title input readiness, not title-frame equality.

## T10 S1 P44 Cold-Start Title Trace

The owner-local native recorder now has an explicit bootstrap-title diagnostic
mode while retaining its existing prebuilt-title default. An 80-sample cold
start comparison used the same frame-40 Start/release script on both sides.
It found the first CIRAM-page-0 difference at sample 3, the first palette
difference at sample 2, and later PPU-control and mask differences. Name-table
selection and horizontal scroll remained aligned in this short window.

This is the first direct product-startup comparison; it disproves any claim
that title menu input readiness establishes title-output equality. The bounded
raw traces were deleted in the comparison command. The remaining title-task
and palette route is T10 work; OAM differences remain T11 work.

## T10 S1 P45 Title SetupIntermediate Palette State

Title `SetupIntermediate` temporarily selects background-color control 2 and
normal player status before it queues the player palette, then restores both
state fields. The native title task now follows that sequence instead of
using the area-header values directly.

On the 80-sample cold-start comparison, palette differences fell from 77
samples and 473 bytes to 61 samples and 457 bytes. The first palette
difference remains at sample 2, so later title palette/task ordering is still
open T10 work. The comparison traces were deleted immediately.

## T10 S1 P46 Cold-Start InitializeGame Frame

The reference cold boot spends its first NMI in title `InitializeGame` before
ScreenRoutines task 0. The native bootstrap had prepared the same area state
but immediately executed task 0, advancing title VRAM work one frame early.
It now preserves the initialization frame before entering the screen-task
chain.

On the 80-sample cold-start comparison, the first CIRAM-page-0 difference
moved from sample 3 to sample 25 and the first palette difference moved from
sample 2 to sample 21. The early background/PPU phase is therefore aligned;
the later title area/parser and display-state differences remain T10 work.
The bounded traces were deleted immediately.

## T10 S1 P47 Background And Alternate Palette Controls

Screen tasks 10 and 11 now translate `GetBackgroundColor` and
`GetAlternatePalette1`. Their address-control selections are consumed by the
same NMI palette-transfer owner as controls 1--4. The owner-local PRG binding
supplies the day-snow, night-snow, and mushroom streams; no palette data is
tracked in C.

The title area does not select those overrides, so this does not alter its
open cold-start differences. It completes the missing task-10/task-11 branch
semantics for qualifying area headers and styles.

The owner-local palette timing smoke reaches the post-SecondaryGameSetup NMI
boundary, verifies the existing ordinary palette transfer, then applies each
of controls 9--11 through the same portable palette state. It also rejects
the adjacent non-special controls. The test compares only outcomes within the
locally generated binding and retains no ROM palette bytes or derived output.

## T10 S1 P48 Title Menu GameCore Dispatch

After `WriteTopScore` hands title mode to its menu task, the source menu
routine continues into `GameCoreRoutine` on every non-start frame. Native C
had returned after latching title input, leaving its entrance dispatcher and
then display-state writers behind the source. The existing game-core route now
also runs when title mode remains in menu task 3 after input handling; a Start
transition remains excluded from that frame, matching the source branch.

An owner-local 80-sample cold-start comparison keeps the title scheduler
bytes aligned and reduces the persistent PPU-control mismatch from 55 samples
to one title-transfer boundary sample. The title-bootstrap smoke now requires
the translated GameCore dispatcher to advance after the menu handoff. Remaining
title palette, CIRAM, display-mask, and OAM differences are retained as open
owners; this is not a frame-equivalence claim.

## T10 S1 P49 Title Top-Score Buffer Command

`WriteTopScore` reaches the title-only `PrintStatusBarNumbers` destination at
PPU `$22f0`. Native C had ended task 14 at the mode handoff without producing
that six-digit command. The translated route now appends the source-shaped
command from persistent top-score digits and applies the source leading-zero
blank rule before entering title menu mode.

The 80-sample cold-start comparison now has no CIRAM difference before sample
42 and no PPU-control difference across the window. The bootstrap smoke covers
the command's bounded buffer layout and zero suppression. Palette, later
title/demo CIRAM, display-mask, and OAM differences remain open owners.

## T10 S1 P50 Title Primary And Secondary Setup

After title task 14, the source enters title-mode `PrimaryGameSetup` and then
falls through to `SecondaryGameSetup` before it reaches menu task 3. Native C
had skipped both tasks, leaving the title parser's screen-disable state active
through the menu and later game start. The translated title task now enters
task 2; the title-mode task-2 route applies the primary player-size/life setup and
the shared secondary setup, including its screen-enable handoff.

The corrected 100-sample cold-start route, with Start held at samples 40--41,
has exact PPU control, name-table selection, and horizontal scroll. CIRAM page
1 is exact in all samples; page 0 differs in only three bytes at sample 41.
The display mask differs once at sample 42. The bootstrap smoke requires the
primary setup state before menu GameCore begins. These bounded residuals and
all OAM differences remain open; they do not establish M2 closure.

## T10 S1 P51 Game-Timer Transition Guard

`RunGameTimer` is reachable only after the game-mode setup has advanced beyond
tasks 0 and 1. Native C had allowed a title-menu engine-subroutine value to
queue the live `$207a` timer command immediately after Start, before original
game-area initialization could reach its game core. The timer route now rejects
those two setup tasks while retaining the established task-2 timing route.

The core smoke exercises a game-mode task-0 state with otherwise eligible timer
fields and requires that it leave the timer and audio queue untouched. On the
corrected 100-sample cold-start route, both CIRAM pages are exact. Remaining
PPU scalar residuals are vertical scroll and reconstructed address at sample
22, plus one display-mask byte at sample 42; title palette and OAM residuals
remain separately open.

## T10 S1 P52 Title Player-Palette Handoff

After `GetAreaPalette` transfers the title ground stream, the title route
queues `GetPlayerColors` into `VRAM_Buffer1` for the following NMI. Native C
had selected the ground stream but did not restore that player-palette command
at the title-only task-10 handoff, leaving the universal palette entry at the
ground value for six extra frames.

The task-10 route now queues the existing source-shaped player palette only
when title mode has no overriding background-color stream. The title bootstrap
smoke observes the resulting `$3f10` command and its universal `$22` entry.
On the corrected 100-sample cold-start route, both CIRAM pages and all 32
palette bytes are exact. The three PPU scalar residuals from P51 and all OAM
differences remain open.

## T10 S1 P53 Game Player-Palette Handoff

The same `GetAreaPalette` to `GetPlayerColors` handoff is shared by the normal
game-mode setup route when no special background stream supersedes it. The
title-only repair left that game route at the ground universal color until its
later game-core synchronization. The task-10 handoff now queues the player
palette for either mode when no special stream was selected.

The palette-timing smoke observes the game-mode `$3f10` command at the
task-10/task-11 boundary. A corrected 380-sample cold-start comparison, with
Start held at samples 40--41, has exact CIRAM pages, palette, PPU control,
mask, name-table selection, scroll, and reconstructed PPU address throughout
samples 100--239. CPU RAM and OAM remain different and retain their T11
ownership; this background-window result does not close M2.

## T10 S1 P54 Preserve NMI-Committed Display State

`InitScreen` calls `InitializeNameTables` from the main operating-mode route,
after the NMI has already committed its physical display state. Native C had
made that helper reset the visible PPU fields as well as the source-owned name
tables and scroll variables. At game start this erased the current NMI's
screen-disabled `$2001` value, producing one display-mask mismatch.

Cold initialization now establishes the initial visible state explicitly;
later `InitializeNameTables` calls preserve the current NMI snapshot. The
frame-snapshot smoke verifies that the helper retains an already committed
mask and vertical scroll value. The 100-sample cold-start comparison has exact
name tables, palette, PPU control, mask, name-table selection, and horizontal
scroll. Only the title-data-read frame's transient vertical-scroll and PPU
address values, plus OAM, remain open.

## T10 S1 P55 Reconstructed PPU Address Contract

The frame contract defines the PPU address as a reconstruction of SMB1's
committed name-table and scroll state. The reference recorder had instead
derived its scalar fields from nnes's internal PPU temporary latch. During
`DrawTitleScreen`, direct `$2006/$2007` reads temporarily mutate that latch,
although the source's `$0778/$073f/$0740` display owners remain unchanged.

The recorder retains nnes's committed temporary latch and fine-X value on
ordinary frames. It reconstructs name-table, scroll, and address from those
three source-owned RAM mirrors only while the source is in title task 13 with
`VRAM_Buffer_AddrCtrl` 5, the direct-read exception. This matches the native
snapshot contract without adding a PPU emulator to the product. The rebuilt
owner-local reference recorder and the corrected 380-sample Start route have
exact CIRAM pages, palette, and all seven PPU scalar bytes across samples
0--379. CPU RAM and OAM remain different and retain their declared T11
ownership.

## T10 S1 P56 PrimaryGameSetup Player-Size Mapping

`PrimaryGameSetup` stores `$01` in `PlayerSize` at `$0754`; it does not store
that value in `PlayerStatus` at `$0756`. Native C had made the latter mapping
error. On a held-Right route, the original therefore selected the small-player
death route after an early collision while native C selected the powered-player
injury-blink route, which later altered movement and background updates.

The translated setup now writes `$0754` and preserves `$0756`. The title
bootstrap smoke requires both the small-player value and the zero player
status at the setup boundary. With Start held at samples 40--41 and Right held
from sample 240, a bounded 600-sample comparison has exact CIRAM pages,
palette, and all seven PPU scalar bytes across samples 0--599. CPU RAM and OAM
remain different under T11 ownership; this background result does not close
M2. An independent 600-sample Start-only route has the same background, palette,
and PPU-scalar result.

## T10 S1 P57 Game-Over ScreenRoutines Dispatch

Original `GameOverMode` dispatches `SetupGameOver`, `ScreenRoutines`, and then
`RunGameOver` through operating-mode tasks 0, 1, and 2. Native C had replaced
task 1 with a local countdown, so it never reached `DisplayIntermediate` at
ROM `$8652-$889c` and never submitted selector 3 (`Game Over`) to
`VRAM_Buffer1`.

Game-over task 1 now runs the shared translated screen routine. Its task-6
GameOver branch sets the original `$07a0` 18-tick gate, queues `WriteGameText`
selector 3, and advances to `RunGameOver`; the following NMI transfers that
command into the canonical name table. The owner-local area smoke binds the
admitted PRG, drives the complete task-0-to-task-2 route, and verifies the
committed `$220b` first Game Over text tile against its source command. The
ROM-free mode smoke retains only mode-transition coverage because it has no
admitted text source. OAM reset/output remains T11 ownership.

## T10 S1 P58 Warp-Zone Object Text Dispatch

`ScrollLockObject_Warp` at ROM `$3b9d-$3bb7` is row-13 object 5. It derives
one of `WriteGameText` selectors 4, 5, or 6 from `WorldNumber` and `AreaType`,
stores it in `WarpZoneControl` (`$06d6`), and submits the Warp Zone text.
The native persistent parser had rendered neither that control state nor the
VRAM command.

The row-13 handler now makes the source selection and invokes the existing
translated `WriteGameText` route. The owner-local area smoke copies the local
PRG only into process memory, inserts one row-13 object-5 stream entry in that
test copy, and verifies the `$06d6` selector, the `$2c` command length, and the
next command transfer's first `$2584` Warp Zone text tile against the local
source table. No generated or ROM-derived data is tracked. Piranha removal and
the movement-side WarpZoneObject remain object/OAM work outside T10.

## T10 S1 P59 Time-Up Screen-Task Route

`RunGameTimer` sets `GameTimerExpiredFlag` after its forced small-player death.
On the following game-mode setup, `DisplayTimeUp` at ROM `$871b-$872f` consumes
that flag, submits `WriteGameText` selector 2, and starts the seven-tick screen
gate before `ResetSpritesAndScreenTimer`. The existing C route already mirrors
that ownership but had no owner-local output proof.

The owner-local area smoke binds the admitted PRG, begins at game-mode
screen-task 4 with `$0759` set, and verifies its reset, task-5 transition,
seven-tick gate, and next-NMI `$220c` text tile against the selector-2 source
stream. This confirms the Time Up background output path; sprite reset remains
T11 ownership.

## T10 S1 P61 Bowser Palette Address Control

The row-13 `AxeObj` route sets `VRAM_Buffer_AddrCtrl` to 8. The original
address table maps that control to `BowserPaletteData` at ROM `$8d4c`, whose
`$3f14` command updates the aliased sprite-palette slot at `$3f04`. Native C
implemented controls 9--11 but silently ignored control 8, leaving the castle
palette stale after the axe object.

The special-palette reader now maps control 8 to the source-owned Bowser
stream, and the NMI buffer-commit route accepts controls 8--11. The owner-local
palette smoke verifies all four resulting palette bytes against the PRG stream,
then sets `$0773` to 8 and verifies the following native tick commits and
clears it. Message controls 12--18 and bridge metatile replacement were
separate T10 owners and are recorded below.

## T10 S1 P62 Victory Message Address Controls

`PrintVictoryMessages` at ROM `$83c9-$8426` selects address controls 12--18
from its primary and secondary message counters. The original NMI resolves
those controls through `VRAM_AddrTable` to the Mario/Luigi thanks, retainer,
princess, and world-select command streams. Native C advanced its counters
without submitting an address control, and its NMI treated all those values as
ordinary buffer-1 traffic, so no victory text reached the name table.

The victory route now preserves the source's 64-call secondary-counter divider,
world-1--7 retainer branch, world-8 music/message sequence, and end-timer
handoff. Its NMI path dispatches controls 12--18 to source-owned PRG streams.
The owner-local victory-message smoke verifies Mario's first message, the
world-1 retainer message, the world-8 princess message and music boundary, and
the final world-select stream directly against their PRG command tiles. The
bridge metatile replacement is recorded by P63.

## T10 S1 P63 Bridge-Collapse Name-Table Output

Victory-mode task zero is `BridgeCollapse` at ROM `$d8aa-$d91d`, not an
immediate handoff to the victory walk. While Bowser is alive, every fourth
call removes the next axe, chain, or bridge metatile by appending two
two-tile blank commands to `VRAM_Buffer1`; the following NMI makes those
commands visible. Native C skipped task zero entirely, so the castle bridge
never changed in its portable name-table snapshot.

The translated owner uses the original 15-entry `$1a,$58,$98..$80` address
sequence, four-call feet timer, blank metatile command form, collapse audio
queues, and defeated-Bowser transition before allowing victory mode to advance.
The Bowser smoke verifies the first queued pair and its following NMI name-table
updates, plus the final entry's defeated state and end handoff. The related
block-replacement writer was searched: it owns only bouncing blocks and keeps
its separate buffer form; no duplicate bridge path remains. OAM rendering of
Bowser remains T11 ownership.

## T10 S1 P64 Alternate Buffer-Two Address Control

The NMI address table at ROM `$805a-$807f` maps both controls 6 and 7 to
`VRAM_Buffer2`. Native C recognized only control 6; if an original route
selected control 7, it would incorrectly consume `VRAM_Buffer1` instead of
the `$0341` level-graphics stream. The NMI commit now treats both controls as
buffer two while preserving `UpdScrollVar`'s source-specific control-6 parser
guard. The parser-buffer smoke commits distinct commands through controls 6
and 7 and verifies both selected name-table bytes and buffer reset behavior.

## T10 S1 P60 Title-Area Display Evidence

Title `ScreenRoutines` task 8 first invokes the title demo area's ordinary
area-output route, then `DrawTitleScreen` overlays its title stream. Native C
implements this through `mysmb_game_apply_title_area`: it preserves the title
mode task, initializes the title area, loads the original pointer/header,
renders initial terrain and objects, and returns to the title stream.

The owner-local title-bootstrap smoke observes task progression, the title
transfer, icon queue, palette handoff, title score, and title menu handoff.
The bounded Start route independently has exact CIRAM pages, palette, and PPU
scalars through 600 samples. Therefore title-area display is no longer an open
background owner. This evidence does not cover alternate entry branches or
the remaining buffer-address controls.

## T10 S1 P65 Jumping Gameplay Background Route

A bounded local reference route selects Start on frame 40, releases it on
frame 42, and holds Right plus A from frame 240 through sample 599. The first
comparison exposed a native vertical-position carry defect: the C translation
inferred the low-byte carry by comparing its result with the old byte. That
loses the 6502 `ADC` carry for `$6f + $ff + 1 = $16f`, changing
`Player_Y_HighPos` from the original value 1 and then suppressing the status
timer's name-table update.

Both player vertical movement owners now retain the full 16-bit intermediate
sum before deriving the carry, matching the source `ADC` chain. The repaired
600-sample route has exact CIRAM pages, palette, PPU control, mask, selected
name table, scroll pair, and reconstructed PPU address. CPU RAM and OAM are
still outside this result: their remaining differences are T11 ownership and
do not constitute background-output evidence. Raw captures were discarded
after this neutral summary.

## T10 S1 P66 Running Route And Death-Transition Gap

The bounded running route selects Start on frame 40, releases it on frame 42,
and holds Right plus B from frame 120 through sample 599. It reaches a normal
death fall and therefore exercises `PlayerHole` at ROM `$aeed-$af35`, followed
by `PlayerLoseLife` and the screen-task background reset. The first comparison
found that native C omitted `PlayerHole` and had attached the life-loss
dispatcher to screen task 1 rather than the real game-core task 3. Those two
source control-flow defects are now translated and covered by the player and
mode route smokes.

The original `HandleSquare2Music` path controls the observed gate: its death
event stream at ROM `$fb72` uses the length table at `$ff66`, then its zero
terminator reaches `EndOfMusicData` and clears `EventMusicBuffer`. Native C
now advances that source stream through the owner-local PRG binding, retaining
the original counter fields and clearing the buffer only at the terminator.
The owner-local death-music smoke verifies the 181-step stream lifetime.

With the repair, the same 600-sample running route has exact CIRAM pages,
palette, PPU control, mask, selected name table, scroll pair, and reconstructed
PPU address, including the death fall and screen rebuild. CPU RAM and OAM
differences remain T11 ownership. Raw captures were discarded after this
summary.

## T10 S1 P67 Sustained Jump Death Physics

A second bounded local route selects Start on frame 40, releases it on frame
42, and holds Right plus A from frame 120 through sample 599. The first
comparison diverged at sample 582 after the native player entered the
life-loss rebuild early. Source inspection found the omitted `LRAir` branch:
when `GameEngineSubroutine` is `$0b`, it writes `$28` to `VerticalForce`
immediately before `MovePlayerVertically`. The ordinary C falling path had
left the previous `$70` force in place.

The translated player step now applies that source-owned death force before
the shared vertical movement primitive, with a direct route-smoke regression.
The repaired 600-sample route has exact CIRAM pages, palette, PPU control,
mask, selected name table, scroll pair, and reconstructed PPU address. CPU
RAM and OAM differences remain deferred T11 ownership. Raw captures were
discarded after this neutral summary.

## T10 S1 P68 Opposite-Direction Jump Route

A bounded local reference route selects Start on frame 40, releases it on
frame 42, and holds Left plus A from frame 120 through sample 599. This is the
opposite-direction counterpart to P67 and exercises the left-facing movement,
jump, death, and rebuild path. Across all 600 samples, both CIRAM pages,
palette, PPU control, mask, selected name table, scroll pair, and reconstructed
PPU address are exact. CPU RAM and OAM differences remain deferred T11
ownership. Raw captures were discarded after this neutral summary.

## T10 S1 P69 CoinBlock And Block-Object Background Output

A bounded local route selects Start on frame 40, releases it on frame 42,
then uses alternating short Right-plus-A jumps from frame 120 through sample
599. Its first comparison found a name-table difference at sample 370. The
source had appended two `$2640/$2660` blank-metatile commands and the coin
and score status commands after a `CoinBlock` collision, while native C
emitted only the status commands. This was the visible `RemoveCoin_Axe` /
`PutBlockMetatile` owner reached from the `BumpBlock` path. The same review
found native `BlockObjectsCore` processed state zero and retained the high
state nibble, whereas the source skips zero and stores its masked low-nibble
state after each object pass.

The native block owner now queues the source-shaped two-row blank metatile
before the shared coin/status tail, covers water-area blank graphics, handles
the direct-above-coin branch, and preserves the source block-state pass
semantics. The ROM-free core smoke verifies queued metatile plus status order
and the masked block state. The repaired 600-sample route has exact CIRAM
pages, palette, PPU control, mask, selected name table, scroll pair, and
reconstructed PPU address. CPU RAM and OAM differences remain deferred T11
ownership. Raw captures were discarded after this neutral summary.

## T10 S1 P70 Sprint-Hop Physics And Goomba Initialization Sweep

A bounded owner-local route selects Start on frame 40, releases it on frame
42, then alternates short Right-plus-A-plus-B presses through sample 599. Its
initial comparison found two source-control defects before the first visible
background difference. `X_Physics` reaches `FastXSp` only through `ChkRFast`:
an airborne player already at absolute speed `$19` branches straight to
`GetXPhy` and retains `FrictionData[0]=$e4`. The C implementation had applied
the later running-speed / `$21` condition to that unreachable branch.

The same route then exposed an early stomp of enemy ID `$06`. ROM
`InitGoomba` runs `InitNormalEnemy` and then `SmallBBox`, setting
`Enemy_BoundBoxCtrl=$09`; the generic C initializer had left `$03`. Its taller
collision box changed the stomp frame and the following jump trajectory. The
translation now keeps the source friction reachability and applies the Goomba
bounding-box override. The complete 38-test ROM-enabled suite passes.

The repair moves the first name-table difference from sample 369 to sample
391. At that point player position, scroll, palette, and every compared PPU
scalar are equal; the remaining difference is a newly generated name-table
column. It remains a T10 area-column/commit owner and is not an exact-route or
M2-closure claim. Raw captures were discarded after this neutral summary.

## T10 S1 P71 Vertical-Pipe Table Index

The generated column at sample 391 belongs to `VerticalPipe` at ROM
`$3843-$3894`. `GetPipeHeight` stores the object's three-bit vertical extent,
but then reloads the fixed two-column object's remaining-length byte before
the non-warp table adjustment. The first pass therefore selects table index
five and the second pass index four, regardless of the vertical extent. Native
C had selected the entry from the extent itself, which deferred the pipe's
left half by one parser column and consequently wrote the wrong name-table
column.

The parser now selects the pipe table from its initialized or decremented
length slot. A ROM-free two-pass smoke uses a height-two pipe to distinguish
that source rule from the old accidental height-one case. The bounded route
starts on frame 40, releases on frame 42, and alternates short
Right-plus-A-plus-B presses from frame 120 through sample 599. After the
repair, both CIRAM pages, palette, and all seven compared PPU scalar fields
are exact for samples 380--599. CPU RAM and OAM remain deferred T11 owners;
this is neither OAM evidence nor an M2-closure claim. Raw captures were
discarded after this neutral summary.

## T10 S1 P72 Background-Owner Closure Audit

The closure sweep covered every portable production writer of canonical
background state. `game.c` owns screen tasks, address-control selection, NMI
buffer transfer, and committed display state; `area.c` owns parser columns,
metatile graphics, attributes, palettes, status text, and message streams;
`objects.c` owns dynamic block and bridge command producers. The sweep found
no host-owned mutation of name tables, palette, scroll, attributes, or PPU
state. `render.c` and platform code remain consumers only.

The source ranges in the ownership table now have a translated background
owner. Their source semantics are covered by the parser, buffer, palette,
title-bootstrap, area, mode, victory, block, and frame-snapshot smokes, and
by the bounded title, running, jumping, death, coin-block, and sprint-hop ROM
routes recorded in P60 and P65--P71. The latest sprint-hop route has exact
two-page CIRAM, palette, and all seven PPU scalar fields through sample 599.
Raw captures were deleted after comparison.

The old bulk title helper remains a test-compatibility API only. The Win32
composition root starts through `mysmb_game_begin_title_bootstrap`, which
uses the normal screen-task and parser path. T10 therefore closes its
background scope. OAM RAM and hardware OAM remain explicitly unverified and
move to T11; this record does not claim an OAM, renderer, Win32-playability,
or M2 closure result.

## T11 S1 P1 NMI OAM Initialization And Shuffle

`SpriteShuffler` at `$81c6-$81f9` and `MoveSpritesOffscreen` at
`$8220-$8230` now have C90 owners in `game.c`. `SecondaryGameSetup` installs
the original fifteen `$06e4-$06f2` offsets, three shuffle amounts, and sprite
zero data; each following native NMI phase hides sprite entries 1--63 and
rotates the offsets with the original 8-bit carry rule. The routine then
derives `$06f3-$06fb` in the source order. `frame_snapshot_capture` copies
the resulting `$0200-$02ff` data to the canonical OAM field.

The ROM-free `mysmb.sprite-oam-smoke` verifies source defaults, sprite-zero
preservation, all-but-zero offscreen initialization, the first shuffle
rotation, and all nine derived misc offsets. A bounded owner-local 600-sample
title-bootstrap route presses Start on frames 40--41 and otherwise uses
neutral input. At the shared NMI boundary it retained exact CIRAM pages,
palette, and all seven PPU-visible scalars; OAM still differed in 571 samples
(14,290 bytes, first sample 0) and CPU OAM RAM differed in 568 samples
(14,048 bytes, first sample 26). These are the unimplemented source draw
families, not a claim of OAM equivalence. The two raw 2,637,012-byte traces
were deleted after this summary.

## T11 S1 P2 Player OAM Rows

`PlayerGfxHandler`, `PlayerGfxProcessing`, `RenderPlayerSub`,
`DrawPlayerLoop`, `DrawSpriteObject`, and `ChkForPlayerAttrib` are translated
into the portable player owner. The normal player route reads the original
tile-offset and graphics tables from owner-local PRG CPU addresses `$ee07` and
`$ee17`; no ROM-derived tile table is tracked. It writes the original four
two-sprite rows at the shuffled player OAM offset, including left-facing tile
order and horizontal-flip bits, big/small/standing/jump/fall/skid/swim/climb
selection, injury blinking, size-change selection, and the prepared vertical
offscreen-row mask.

The ROM-free `mysmb.player-oam-smoke` supplies a synthetic PRG table and
checks source row order, coordinates, attributes, and left-facing flip. A
bounded owner-local title-bootstrap route presses Start on frames 40--41 and
otherwise uses neutral input. At NMI samples 300, 400, 500, and 599, the
player's 32-byte OAM range is exact. Across all 600 samples, total OAM
differences fell from 14,290 before player rows to 4,172 bytes in 167 samples;
CPU OAM-RAM differences fell from 14,048 to 3,856 bytes in 160 samples.
The remaining differences belong to title, enemy, item, projectile, effect,
score, platform, and boss draw owners. CIRAM pages, palette, and all seven
PPU-visible scalars remained exact. Raw 600-sample traces were deleted after
the comparison.

## T11 S1 P3 Intermediate-Player OAM

`DrawPlayer_Intermediate` at `$f02b-$f047` now uses the same owner-local
player graphics table to write its four small-standing rows at OAM offset
four, including the source's bottom-right horizontal flip. `DisplayIntermediate`
invokes that owner only on the normal lives-display route; title, alternate
entrance, and skip-intermediate routes retain their source exclusions. The
player OAM smoke extends its synthetic-table check through this path.

The same bounded 600-sample title-bootstrap route makes CPU OAM RAM
`$0200-$02ff` exact at every NMI sample. Hardware OAM still differs in 366
bytes across eleven transition samples (0, 1, 25, 26, 40--42, 47, 189,
206, and 207). This isolates the remaining discrepancy to the portable
snapshot's NMI/DMA submission phase rather than an unimplemented player or
intermediate draw writer. CIRAM pages, palette, and all seven PPU-visible
scalars remain exact. Raw traces were deleted after the comparison.

## T11 S1 P4 NMI OAM DMA Submission

`NonMaskableInterrupt` resets the PPU sprite address and writes `$02` to
`$4014` before `UpdateScreen`, controller dispatch, sprite hiding, and game
mode execution. The portable game state now preserves that boundary explicitly:
`visible_oam` is the hardware OAM image sampled by the snapshot, while CPU RAM
`$0200-$02ff` remains the producer backing store for the following frame. Cold
boot submits the initialized image before the first recorder-visible NMI; each
subsequent native tick submits the prior producer image before the translated
writers execute.

The frame-snapshot smoke deliberately stores distinct CPU and hardware OAM
bytes, so a future direct CPU-RAM copy cannot pass. On the same bounded
600-sample title-bootstrap route as P1--P3, CPU OAM RAM and hardware OAM are
both exact for every sample. Both CIRAM pages, palette, and all seven
PPU-visible scalar fields remain exact. This resolves P3's eleven
DMA-boundary-only samples; unimplemented OAM writer families remain open and
no M2 or renderer closure is claimed. Raw captures were deleted after the
neutral comparison summary.

## T11 S1 P5 Floatey-Number OAM

`FloateyNumbersRoutine` at `$84c3-$8566` now preserves its two-sprite score
entry: regular and alternate OAM-group selection, timer and vertical motion,
tile pairs, palette attributes, saved relative X coordinate, and the carry
from `CMP #$18` into `SBC #$08`. The ROM-free floatey OAM smoke covers a tall
enemy's regular group and an ordinary living enemy's alternate group, including
the status-region carry case. Other enemy, item, projectile, block, and
screen-support draw writers remain open T11 owners.

## T11 S1 P6 Jumping-Coin OAM

`ProcJumpCoin`, `JCoinGfxHandler`, and `DrawFloateyNumber_Coin` now emit their
source-selected misc OAM pairs. The owner uses `Misc_SprDataOffset`, saves the
world-to-screen X coordinate, maintains the two coin rows or the two score
glyphs, selects the four-frame coin tile cycle, and retains the every-other-
frame score rise. The ROM-free misc OAM smoke verifies both the jumping-coin
and score forms. Hammer OAM remains a distinct owner despite sharing the misc
object loop.

## T11 S1 P7 Regular-Fireball OAM

`FireballObjCore` now reaches the source-shaped one-sprite `DrawFireball`
output after its collision path. It uses the original `FBall_SprDataOffset`,
world-to-screen X coordinate, two-frame tile cadence, and eight-frame flip
cadence. The ROM-free fireball OAM smoke verifies both visual phases. The
four-sprite explosion route is deliberately deferred to the next T11 slice;
firebar, bubble, and other effects remain open owners.

## T11 S1 P8 Fireball-Explosion OAM

`DrawExplosion_Fireball` now writes the original four-sprite square through
`Alt_SprDataOffset`, with its three tile frames, mirrored attributes, and
relative four-pixel expansion. The translation selects its frame from the
pre-increment state, then stores the incremented state, matching the ROM's
`LDA`/`INC` ordering. The fireball OAM smoke verifies the first explosion
frame and its next state. Firebar, bubble, and fireworks remain separate T11
owners.

## T11 S1 P9 Power-Up OAM

`DrawPowerUp` now owns the slot-five power-up sprite square in portable C.  Its
four type-specific tile groups, base palette attributes, flower/star palette
cadence, horizontal mirrors, and emergence threshold follow the source writer.
The ROM-free power-up OAM smoke covers a star, a flower, and the first visible
mushroom-emergence frame.  Enemy and firebar/bubble writers remain separate
T11 owners.

## T11 S1 P10 Block and Brick-Chunk OAM

DrawBlock and DrawBrickChunks now have a separate portable C owner to preserve the 16-bit code-segment limit. The OAM smoke checks a used bouncing block and the four fragment layout. Coin/debris writers remain distinct.

## T11 S1 P11 Goomba OAM

The portable Goomba writer now follows the ROM graphics table and the
CheckForGoomba/row-draw path. It writes all six tiles into the enemy slot's
three OAM rows, including the stomped-goomba record and its one-pixel Y shift,
uses the ROM palette base and horizontal mirror behavior, and computes X from
the world and screen positions. The smoke test compares all 24 OAM bytes in
flipped, normal, and stomped animation states; the remaining enemy families are
separate T11 owners.


## T13 S1 P12 First Frame-Trace Baseline

A fresh owner-local 60-sample trace used a one-frame Start input at samples 30--31.
The source recorder was built against the current MyNES-only NXVM route; the
native recorder used the same script and title bootstrap. Raw traces were kept
only in an ignored build directory. The neutral comparison first reports CPU
RAM differences at sample 0. PPU-visible output differences begin after Start:
CPU OAM RAM at sample 30, hardware OAM at sample 31, both CIRAM pages at
sample 32, palette at sample 33, and PPU mask at sample 32. In this bounded
route, PPU control, name-table selection, scroll X/Y, and PPU address match.
This is an active mismatch baseline, not M2 equivalence evidence.

## T13 S1 P13 Corrected Start/Right Frame Trace

The reference recorder consumes NES serial controller bits (`Start=$08`,
`Right=$80`), while the native recorder consumes MySMB's decoded input masks
(`Start=$10`, `Right=$01`). An earlier 60-sample baseline incorrectly passed
the native Start byte to MyNES, which pressed Up and did not exercise the ROM
Start route; it is superseded.

A fresh 380-sample owner-local trace pressed Start for one frame at sample 30
and then held Right from sample 60. With the correct encoding on both sides,
CIRAM pages, palette, and all seven PPU-visible scalar values are exact at all
380 samples. CPU OAM RAM is exact through sample 283; hardware OAM is exact
through sample 284. The first real gameplay OAM difference is sprite 12 at
sample 285, leaving the enemy lifecycle/draw owner open. CPU RAM still differs
in source scratch, stack, and untranslated working-state bytes, so this is
valid output evidence only and does not close M2.
