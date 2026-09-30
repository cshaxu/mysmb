# M2 current-equivalence re-audit

This registry is the current-build complement to
[node progress](NODE_PROGRESS.md). Historical node-accounting status remains
`1,992 / 1,992`; it must never be read as a current end-to-end result until a
row below records a fresh audit disposition.

The machine-readable node/control-edge ledger is
[`M2_CURRENT_EQUIVALENCE.json`](M2_CURRENT_EQUIVALENCE.json). It is generated
by `BuildM2CurrentAuditRegistry.py` for the baseline and then updated only by
cohort audit evidence. It contains no ROM bytes or source text: every node
records its current C owner/counterpart and both evidence tracks, while every
edge records its C integration counterpart and both evidence tracks.
[`VerifyM2CurrentAuditRegistry.py`](../../tools/VerifyM2CurrentAuditRegistry.py)
rejects an `exact` disposition lacking either track and rejects duplicate or
incomplete node/control-edge identities.

## Baseline

| Current-equivalence state | Labels | Meaning |
| --- | ---: | --- |
| Exact | 38 | Current source audit and original-ROM route both prove the label. |
| Needs evidence | 736 | Current source audit exists but the current original-ROM route is incomplete. |
| Mismatch | 9 | Current route or source audit finds a concrete semantic difference. |
| Unclassified | 1,209 | Not yet processed by this re-audit. |
| **Total** | **1,992** | Canonical inventory labels. |

The fresh T31 replay is preflight evidence, not a node classification: all
thirteen routes are output/RAM-exact on current x86/x64, but only their
executed chain may be credited after the relevant cohort's source audit.

## Edge baseline

The re-audit also owns the original ROM graph. Its first operation extracts a
canonical, deduplicated edge registry and records the total before any edge is
classified. It includes control edges (`JSR`, `JMP`, conditional branch,
fall-through, return and vector dispatch) plus material game-state edges
(source RAM/table producer to consuming node). The current edge count is
therefore intentionally **not estimated** in advance.

The reproducible control-graph extractor is
[`Extract-M2RomGraph.py`](../../tools/Extract-M2RomGraph.py). The companion
[`BuildM2CurrentAuditRegistry.py`](../../tools/BuildM2CurrentAuditRegistry.py)
turns that graph and the label inventory into the neutral audit baseline. Its
current owner-local listing run reads all 1,992 inventory labels and establishes
the control subledger at **4,342** edges: 611 calls, 247 direct jumps, 1,566
branches, 1,058 fall-through relations, 611 return relations, two vector
entries and 247 `JumpEngine` selector edges. Every control edge has a stable
identity and exactly one source-order cohort. This is a fixed subledger, not
the final edge denominator: material RAM/table producer-consumer edges are
enumerated only after source-path review. A writer-reader Cartesian product is
explicitly forbidden because it would count impossible paths as integrations.

| Current-equivalence edge state | Edges |
| --- | ---: |
| Exact | 76 control; 3 material RAM/table |
| Needs evidence | 1,396 control; 96 material RAM/table |
| Mismatch | 10 control; 1 material RAM/table |
| Unclassified | 2,860 control edges; material edge denominator pending feasible-path enumeration |
| **Total** | 4,342 control edges; material edge denominator pending feasible-path enumeration |

The two ledgers are separate acceptance requirements. A node is not
current-exact merely because its own outputs look right: its source contract
and every owned incoming/outgoing control connection must be accounted for.
Likewise, a control or feasible material edge is not exact merely because its
endpoints are mapped. Its predicate, ordering, state handoff and return or
dispatch behavior must have their own counterpart and route evidence.

### Control-edge allocation

The registry allocates **all 4,342 control edges** once, by the source label
that emits the edge (vectors are owned by their target label's cohort; return
records use the caller cohort because the original `JSR` is the source). This
is the integration-audit denominator for the first edge pass.

| Cohort | Nodes | Control edges |
| --- | ---: | ---: |
| A | 97 | 239 |
| B | 67 | 122 |
| C | 260 | 521 |
| D | 146 | 111 |
| E | 80 | 239 |
| F | 62 | 122 |
| G | 49 | 133 |
| H | 129 | 344 |
| I | 165 | 420 |
| J | 497 | 1,261 |
| K | 154 | 313 |
| L | 83 | 165 |
| M | 126 | 296 |
| N | 77 | 56 |
| **Total** | **1,992** | **4,342** |

## Source-order cohort plan

| Cohort | ROM source family | Labels | Required current route families |
| --- | --- | ---: | --- |
| A | Reset, NMI, title/menu/demo | 699–1385 | cold/warm boot, pause, title, world select, demo, start |
| B | Screen, HUD, text and screen tasks | 1386–1824 | title/status, game-over, world/castle text, parser scheduling |
| C | Area bootstrap, VRAM, palette and parser | 1825–3990 | area entry, columns, pipe, hidden/question block, scroll |
| D | Renderer, metatile and block-buffer output | 3991–5314 | background/object rows, replacement, attribute and scroll output |
| E | Dispatcher and player control/transition | 5315–5900 | game entry, death/restart, pipe, vine, flagpole and area change |
| F | Player movement, physics and block actions | 5901–6297 | walk, run, jump, swim, head, wall and platform routes |
| G | Fireballs and bubbles | 6298–6729 | spawn, terrain, enemy, bubble and offscreen routes |
| H | Blocks, items and misc objects | 6730–7787 | coins, power-ups, vines, blocks, cannons, whirlpools and flagpole |
| I | Enemy stream, initialization and groups | 7788–9149 | area streams, groups, frenzy, all slot selectors |
| J | Enemy movement, terrain and collision | 9150–13022 | normal/special movement, terrain, player/enemy and projectile contacts |
| K | Shared collision and player terrain | 13023–14459 | platforms, climbing, bounding boxes, terrain and timers |
| L | OAM, relative/offscreen and graphics | 14460–15069 | title/player/enemy/projectile/endgame OAM and sprite split |
| M | Sound effects | 15070–15820 | jump, coin, grow, injury, timer, terminal and channel priority |
| N | Music channels and data | 15821–end | area/event selection, all channels, loops, headers and tables |

The line ranges allocate original source order; the cohort implementation
record must list every exact inventory label before audit begins. A label may
appear in only one cohort.

## Per-cohort method and results

For each cohort, record:

1. the exact inventory-label list, original callers/successors, current shared
   C owner, tables and direct dependencies, together with every owned incoming
   and outgoing original graph edge;
2. a source audit of branch predicates, reads, writes, table indexes and call
   order;
3. a reproducible original-ROM route and current x86/x64 run that compare
   persistent RAM, CIRAM, palette, visible OAM, PPU state and audio, with only
   explicitly justified ABI exclusions;
4. the node and edge dispositions and any smallest contiguous shared-owner
   mismatch chain.

For node semantics, the recorded comparison contains the original control
predicates, read/write set, table binding, successor order and current shared
C owner. For every control edge, it records the original endpoint/type, the
C call/branch/dispatch counterpart and both source and route evidence. For a
material RAM/table edge, it records the producing write or table selection,
the consuming read/index, the feasible original path between them and the
corresponding shared-C data flow. A route may mark only the items it executes;
all unexecuted items remain `needs-evidence` until source review closes them.
Every cohort performs the node-semantics pass before the independent edge and
integration pass. Node equality does not infer call/return/branch/data-flow
equality: each relation receives its own counterpart, ordering contract and
evidence. A cohort remains open until both scoped ledgers have dispositions.
[`ExtractM2RomDataAccesses.py`](../../tools/ExtractM2RomDataAccesses.py)
provides the source-addressed read/write atoms for that work. Its output is a
local audit input, not a data-edge list or a verdict.

Confirmed mismatch chains are appended to `QUEUE.md` without a numeric task
identifier. Only an owner-approved later implementation admission allocates
the next numeric T and its S entries.

### Cohort A — A1 boot and first-NMI boundary

The first reviewed chain is `Start -> VBlank1 -> VBlank2 -> WBootCheck ->
ColdBoot -> EndlessLoop`, with the adjacent `VRAM_AddrTable_Low`,
`VRAM_AddrTable_High` and `VRAM_Buffer_Offset` data labels. The six executable
reset labels and all 20 control edges are **exact**. Current static review maps
the reset sequence to `boot.c`, and three original-ROM pre-NMI captures cover
cold-marker failure, valid warm marker and an invalid top-score digit. Together
they execute both VBlank loops and exits, every WBootCheck branch, all ColdBoot
calls/returns, and the reset vector. Current x86/x64 snapshots at the same
boundary are byte-identical and have no persistent RAM, CIRAM, palette, OAM,
audio or PPU difference after the explicit sequence/CPU-stack exclusions.

The adjacent VRAM table labels are also **exact**. A controlled 19-selector
matrix captures the ROM after its selected low/high bytes are loaded into
`$00/$01`, before `UpdateScreen`, and compares those bytes with both current
x86 and x64 owners. A second capture after `UpdateScreen` and `InitBuffer`
compares the two buffer headers and cleared selector for all 19 choices. This
also establishes three source-path material edges: each pointer table to the
NMI consumer, and the buffer-offset table to `InitBuffer`. The ROM's pointer
may advance while parsing a command packet, whereas the C owner traverses its
buffer directly; the audit compares initial table binding separately from
post-consumption header state. The linked JSON ledger records those distinct
contracts without treating implementation shape as a mismatch.

### Cohort A — A2 NMI prologue node-semantics pass

The next source-order slice covers `NonMaskableInterrupt` through
`SkipSprite0` (lines 764–867). The node-semantics pass has recorded all 13
labels' branch/state/table/output contracts and their shared `frame_root.c`
counterparts. They are deliberately **needs-evidence**, rather than exact:
the controlled original-ROM route must still cover timer, pause, sprite-zero
and scroll alternatives, and the separate integration pass has not yet
completed its ROM route proof. Its static integration pass has now recorded
the counterpart and ordering contract for all 47 owned control relations:
branches, fall-throughs, calls and matching returns through the first
operation-mode-dispatch call. Those edges are also **needs-evidence** until
the controlled route observes the corresponding alternatives. This preserves
the distinction between a mapped node and a proven node/edge system.

The first controlled route exposes a confirmed shared-core mismatch chain.
At the boundary immediately before `OperModeExecutionTree`, ROM
`RotPRandomBit` leaves `$00=$02`; current x86/x64 leave `$00=$01` because the
shared C owner does not perform the source scratch write. At the same boundary
ROM physical `$2000=$10`, while current x86/x64 expose `$90`: d7 is restored
before mode dispatch rather than at the RTI equivalent. The registry marks
`RotPRandomBit`, `SkipSprite0`, `NonMaskableInterrupt`, and their two
state-handoff control edges as mismatches. The ordered unnumbered repair
candidate is [A2 NMI-prefix state handoff](../proposals/m2/a2-nmi-prefix-repair-candidate.md).

### Cohort A — A3 pause and sprite-shuffle static passes

The next independent slice covers `PauseRoutine` through `SetMiscOffset`
(lines 876–953). All 12 node contracts and all 21 source-owned branch and
fall-through relations are mapped to their shared `frame_root.c` owners and
are `needs-evidence`. The required controlled routes still need to cover the
mode gate, timer-active and timer-zero paths, Start/debounce alternatives,
shuffle overflow and non-overflow, modulo-three reset, and all three misc
offset groups. No node or edge has been promoted from this static work.

The pause subchain is now **exact** for `PauseRoutine`, `ChkPauseTimer`,
`ChkStart`, `ClrPauseTimer`, `SetPause` and `ExitPause`, together with its 11
owned control relations. Seven controlled cold-boot NMI-prefix routes cover
the VictoryMode and GameMode gates, non-pausable and non-task alternatives,
active and zero timer paths, Start, d7 debounce and the common return.
ROM and current x86/x64 pause-owned state matches in every route. The known
NMI `$00` and pre-dispatch `$2000` mismatches remain separately recorded and
are not attributed to this proof.

The timer subchain is **exact** for `DecTimers`, `DecTimersLoop`,
`SkipExpTimer` and `NoDecTimers`, with all ten of their owned control
relations. Controlled routes cover master timer nonzero and expiry, interval
timer non-expiry and expiry, zero/nonzero timer cells and loop termination.
Timer-owned RAM and `FrameCounter` agree between ROM and current x86/x64;
the independently confirmed NMI-prefix mismatches remain outside this proof.

### Cohort A — A5 NMI mode-dispatch and OAM-tail static passes

`OperModeExecutionTree`, `MoveAllSpritesOffscreen`, `MoveSpritesOffscreen`
and `SprInitLoop` now have node contracts and ten owned control relations in
the registry, all `needs-evidence`. The mode tree still requires controlled
title/game/victory/game-over routes. The nonzero-sprite loop requires a route
with the real sprite-zero hardware condition; ColdBoot's all-sprite pass is
not substituted as evidence for that distinct entry.

### Cohort A — A6 title-menu node and edge passes

The title-menu/start slice records 15 nodes from `TitleScreenMode` through
`GoContinue`, together with 32 menu/start control relations. A controlled
original-ROM route now enters through the ordinary NMI mode dispatcher, reaches
`GameMenuRoutine`, and captures immediately before `RunDemo` calls
`GameCoreRoutine`. Its ordinary, Select, world-select B and initial-demo cases
match current x86/x64 on their title-owned state. The complete world-select B
subchain is exact: `GoContinue`, `IncWorldSel`, `UpdateShroom` and
`NullJoypad`, plus its six individual call/return, loop and fall-through
relations. Start, A+Start and expired-demo Start additionally prove the exact
`StartGame -> ChkContinue -> StartWorld1 -> InitScores -> ExitMenu` chain,
its A+Start continuation call, its `LoadAreaPointer` return, and the
expired-demo `ChkContinue -> ResetTitle` branch.

The remaining title labels and relations stay `needs-evidence`. In particular,
`TitleScreenMode` must still prove all four dispatch vectors; `GameMenuRoutine`,
`ChkSelect`, `ChkWorldSel` and `SelectBLogic` need their remaining debounce,
disabled/enabled and reset branches; and `RunDemo` with its post-
`GameCoreRoutine` reset condition remains a separate route family. Demo
action/timing data is also deferred to that route family. The zero-demo-timer,
world-select-B case is a confirmed `ChkSelect` mismatch: the source enters
`DemoEngine` before world-select handling, while current C enters
`SelectBLogic` and resets title mode. Its ordered repair candidate is
[A6 title-menu timer gate](../proposals/m2/a6-title-menu-order-repair-candidate.md).

The adjacent independent demo-data chain is exact: `DemoActionData`,
`DemoTimingData`, `DemoEngine`, `DoAction` and `DemoOver`, together with its
eight caller, branch, fall-through and return relations. Controlled action
switch, held-action and terminal-zero routes match ROM and x86/x64. `RunDemo`
remains open because its `GameCoreRoutine` call and post-return reset condition
belong to the later game-core route family.

The preceding icon chain is also exact: `MushroomIconData`,
`DrawMushroomIcon`, `IconDataRead` and `ExitIcon`, plus its Select caller,
return, descending loop and player-count conditional relations. Both icon
layouts match the original-ROM NMI path and current x86/x64 state.
The two executed upstream dispatch edges, `OperModeExecutionTree ->
TitleScreenMode` and `TitleScreenMode -> GameMenuRoutine`, are independently
exact. The `TitleScreenMode` node remains pending because its other task
vectors have not yet received this route proof.

### Cohort A — A7 Victory entry node and integration static passes

The next source-order chain begins at `VictoryMode` and covers `AutoPlayer`,
`VictoryModeSubroutines` and `SetupVictoryMode` (lines 1137–1165). The four
node contracts are mapped to the shared `frame_root.c` and `terminal_modes.c`
owners and remain `needs-evidence`. The integration ledger independently
records every relation touching this entry chain: the outer leaf call,
task-zero branch, optional enemy call and fall-through; the relative-position
call and player-graphics tail; the JumpEngine call, return and five selector
entries; SetupVictoryMode's task increment tail; and the relevant caller and
callee returns. Eighteen newly recorded edges remain `needs-evidence`; the
already recorded operation-mode dispatch edge remains `needs-evidence`.

Promotion requires controlled original-ROM and current x86/x64 routes for at
least the bridge-collapse task-zero path, setup task-one path, a nonzero
post-leaf enemy path, and the shared relative-position/player-graphics tail.
The route records must compare the task selector, ObjectOffset handoff,
destination page, event music, player-relative output and OAM-visible result.

The adjacent `PlayerVictoryWalk -> PerformWalk -> DontWalk -> ExitVWalk`
branch (lines 1169–1197) has now received its separate static node pass. All
four nodes remain `needs-evidence`. Its thirteen previously unclassified
relations are independently recorded as `needs-evidence`: both page/X walk
predicates, their fall-throughs, the auto-control call/return, the
screen-left branch, fixed-point scroll and parser calls/returns, the terminal
fall-through, and the zero-control task increment. This makes the
`VictoryModeSubroutines` selector-to-walk integration auditable without
claiming that the current `mysmb_player_step` and scroll collaborators have
already been proved by a current route. The required route pair is the
same-page no-walk/task-advance case and the walking/non-destination-page case;
both must compare auto buttons, walk control, fractional carry, screen pages,
parser handoff and task result.

The next `PrintVictoryMessages -> ExitMsgs` message chain (lines 1201–1252)
has ten node contracts and all twenty-three currently associated control
relations recorded independently. Every item remains `needs-evidence`.
The edge pass covers the secondary-counter early branch; primary/world
threshold tree; Mario/Luigi first-message fork; World 8 music ordering;
message-control-to-counter handoff; carry into the primary counter; and the
WorldEndTimer/task-increment terminal path. Promotion requires controlled ROM
and current x86/x64 records for Mario and Luigi initial messages, worlds 1–7
counter/message/end-timer alternatives, World 8 pre-music/music message
alternatives, nonzero secondary counter, and primary counter carry/terminal
thresholds. Each record must compare both the selected VRAM control and the
counter, music, timer and task state that reaches the successor.

The Victory terminal-exit chain `PlayerEndWorld -> EndExitOne /
EndChkBButton -> EndExitTwo` (lines 1256–1281) now has four node contracts
and all ten associated control relations independently recorded as
`needs-evidence`. The integration pass distinguishes active-timer return,
worlds 1–7 next-world ordering around `LoadAreaPointer`, World 8 no-B return,
World 8 B's pre-`TerminateGame` writes, its post-helper return, and the
separate floatey-number use of the shared `EndExitOne` RTS leaf. Required
current route evidence is an active-timer return, ordinary next-world
transition, World 8 no-B, and B from each controller latch. It must compare
area/level/world/task/mode order, fetch-timer flag, both controller latches,
world-select/lives writes, and the complete `TerminateGame` handoff.

### Cohort A — A7 Floatey timer-gate discrepancy

The next source label, `DecNumTimer`, has a confirmed shared-core timing
mismatch. The ROM decrements `FloateyNum_Timer` before comparing its result to
`$2b`; current `mysmb_objects_step_floatey_number` performs the comparison
before decrement. The registry marks `DecNumTimer` and four affected score
gate/call relations as `mismatch`: the non-score branch, both score/one-up
paths to `LoadNumTiles`, and `LoadNumTiles -> AddToScore`. The ordered
unnumbered repair record is [A7 Floatey timer-gate repair]
(../proposals/m2/a7-floatey-timer-gate-repair-candidate.md). It must receive a
later numeric task before any production source change.

The remainder of the Floatey chain is now statically mapped: the two local
tables, `FloateyNumbersRoutine`, timer-zero return, score caller/return,
enemy OAM-offset selector, vertical/carry path and two-sprite output. Eight
nodes and twenty currently unclassified control relations are
`needs-evidence`; `FloateyNumbersRoutine` is also `mismatch` because its entry
has different observable results at the two timer boundary inputs. Two
feasible material edges are registered separately: `ScoreUpdateData ->
LoadNumTiles` is `mismatch` because its otherwise matching table is consumed
on the wrong timer frame, while `FloateyNumTileData -> SetupNumSpr` remains
`needs-evidence`. Required route evidence spans zero, `$2b`, `$2c`, ordinary
score, 1-UP, every alternate-OAM selector family, both vertical regions and
the complete two-sprite output.

### Cohort B — B1 screen-task root and first leaves

`ScreenRoutines`, `InitScreen` and `SetupIntermediate` (lines 1386–1432) are
now mapped to the shared `mysmb_game_step_screen_routine` owner and remain
`needs-evidence`. The independent integration pass records all fifteen
ScreenRoutineTask selector entries, the Title/Game/GameOver incoming dispatch
relations, the JumpEngine return, and every first-leaf helper, branch and
return relation. The root mapping does not classify the other thirteen task
leaves: each still needs its own node-semantics pass and route proof. Required
B1 routes must separately exercise title and non-title `InitScreen`, plus
`SetupIntermediate` with non-default PlayerStatus and BackgroundColorCtrl, and
compare the pre-helper temporary values, restored values, VRAM selector and
task handoff.

### Cohort B — B2 palette chain

`AreaPalette` through `SetVRAMOffset` are now individually mapped, including
four feasible table-to-consumer paths. The static edge pass identifies a
confirmed shared-core mismatch at `GetBackgroundColor -> NoBGColor ->
GetPlayerColors`: the ROM always falls into the palette producer after the
task increment, while current case 10 exits early for BackgroundColorCtrl
4–7. `GetBackgroundColor`, `NoBGColor`, `control-00205`, `control-00206` and
the `BGColorCtrl_Addr -> GetBackgroundColor` material path therefore remain
explicitly non-exact; the repair candidate records the required route matrix.

### Cohort B — B3 screen-flow and parser handoff

The audit now maps `GetAlternatePalette1` through
`AreaParserTaskControl`, including the parser loop, status-line helpers and
`ResetSpritesAndScreenTimer` return relations. It found a second confirmed
screen-state mismatch: on an expired timer, ROM `DisplayTimeUp` returns with
task 4 and reaches task 6 on its next non-expired invocation; current C writes
task 5 immediately and waits on its screen timer. `DisplayTimeUp` and its
`OutputInter` jump are mismatched. The remaining nodes and relations are
static-mapped but await route evidence.

### Cohort B — B4 title-copy and handoff chain

`DrawTitleScreen` through `WriteTopScore` are now node-mapped with all local
loop, call, return, non-title branch and shared task/mode-handoff edges. The
static pass found no new discrepancy: fixed `$13a` title-copy bounds, the
descending buffer clear, mushroom-icon call and title-score update all have
named shared-C counterparts. They remain `needs-evidence` until title and
non-title ROM/x86/x64 routes compare their RAM, VRAM command and task state.

### Cohort B — B5 status-text, mutable fields and timer-tail chain

`GameText` through `NoReset` are now mapped, with independent control edges
for text selection, player-count/name routing, mutable lives fields, Warp
numbering and timer return behavior. Four feasible data paths are registered:
offset-table selection, message stream copy, LUIGI replacement and Warp
numbers. Current static mapping retains the source behavior for normal
resource-bound routes, but all entries remain `needs-evidence` until fixtures
cover selectors 0–6, one/two players, Mario/Luigi, Time Up/Game Over, crown
lives and each Warp table row.

### Cohort B — B6 column renderer, attribute output and palette rotation

The current audit maps every node from `RenderAreaGraphics` through
`ExitColorRot`, all local and known inbound/outbound control relations, and
seven feasible material paths. The node contracts cover the 13-row vertical
tile command, attribute quadrants and clears, name-table wrap, seven-row
attribute command output, every-eighth-frame gate, bounded Buffer1 gate and
the six-step color cycle. No static mismatch was found; source/x86/x64 routes
must still compare Buffer2, AttributeBuffer, nametable state and palette
commands before these become exact.

### Cohort B — B7 block-metatile replacement and static palettes

`BlockGfxData` through `CastlePaletteData` now have node contracts. The edge
pass records blank/coin/axe replacement, block-replace and destroy paths,
graphic-set selection, two-command block output, and return handoffs. Five
new feasible material paths cover BlockGfxData and the four static palette
streams. No static discrepancy is confirmed; required routes include each
block graphics selector, water/non-water blank replacement, both name-table
halves and palette controls one through four.

### Cohort B — B8 special palettes, PPU packet path and controller serialization

The audit maps every node from `DaySnowPaletteData` through `WritePPUReg1`.
It covers special palettes and seven selector-driven message streams,
JumpEngine dispatch, name-table clearing, input serialisation/debounce and
the VRAM packet decoder/scroll tail. Thirty control relations and eleven
feasible stream-to-NMI data edges are recorded. No new static discrepancy is
confirmed. Route proof must cover selectors 8–18, both controller ports and
Select/Start repeat suppression, packet increment/repeat variants, empty and
multi-packet buffers, plus both cleared name tables.

### Cohort B — B9a status numbers, BCD arithmetic and top-score comparison

`StatusBarData` through `NoTopSc` are now mapped. The independent edge pass
covers dual-nybble number output, selector rejection, digit loops,
title-mode modifier clearing, BCD borrow/carry paths, and Mario/Luigi
top-score comparison/copy. Two feasible data edges cover status command and
digit-offset tables. Static source comparison found no new discrepancy; route
proof must cover every valid/invalid selector, title/non-title arithmetic,
borrow/carry chains and both player high-score outcomes.

### Cohort B — B9b game and area initialization chain

`DefaultSprOffsets` through `InitPageLoop` are static-mapped with startup,
restart, area-entry, hard-mode, render-preload and secondary setup edges.
The two OAM initialization tables are registered as feasible data paths. No
new static discrepancy is confirmed; route proof must cover title startup,
death restart, alternate entrance, halfway page, hard-mode thresholds and
the full secondary OAM/VRAM initialization sequence.

### Cohort C — B10a memory clear, area music and player entrance integration

`InitializeMemory` through `SetPESub` (lines 2795–2917) now have individual
node contracts and a separate integration record for all 34 local control and
return relations. The audit explicitly separates the protected stack-page
clear loop, title/pipe/cloud music selection, alternate-entrance coordinate
tables, palette return, timer reset gates, override-driven block/vine calls,
water-only bubble setup, and the final engine-subroutine handoff. Six feasible
material paths are registered: music selector, X position, alternate Y-index,
Y position, sprite attribute and game-timer tables. Static comparison found no
new discrepancy. All 21 nodes, 34 control/return relations and six material
relations remain `needs-evidence` until controlled original-ROM and current
x86/x64 route records cover title/non-title music, pipe/cloud selection,
ordinary/water/alternate entrances, timer reload/no-reload and override/vine
paths. This is intentionally not an `exact` claim.

### Cohort C — B10b death restart, Game Over and player-record integration

`HalfwayPageNybbles` through `ExTrans` (lines 2921–3049) now have individual
node contracts. The independent edge pass records 30 control/return/dispatch
relations: life-underflow, world/level checkpoint indexing and nibble choice,
screen-page acceptance, death restart, all three Game Over task vectors,
Start/timer termination, restart pointer ordering, and the two-player
seven-byte exchange. Two feasible material paths record the checkpoint table
and the player-record exchange. Static comparison found no new discrepancy.
All 15 nodes, 30 relations and two material paths remain `needs-evidence`
until controlled original-ROM and x86/x64 runs cover no-life Game Over,
checkpoint accepted/rejected paths, Start/non-Start timer paths and both
successful and failed two-player transpositions.

### Cohort C — B10c parser-task cadence and column-advance integration

`AreaParserTaskHandler` through `NoColWrap` (lines 3060–3102) now have node
contracts and 21 reviewed local control/return/selector relations. The audit
keeps the screen task's full two-column loop distinct from the runtime's
one-slot parser call: zero initializes the persistent task counter to eight;
each call executes one descending selector; only the terminal slot emits
attributes. It also records both column-advance selector entries, all four
graphics entries, both parser-core entries, the 16-column page wrap and the
32-column block-buffer wrap. No static discrepancy was found. The six nodes
and newly reviewed relations remain `needs-evidence` pending controlled ROM
and x86/x64 column-set and runtime scrolling routes.

### Cohort C — B10d scenery tables, terrain masks and parser-core entry

`BSceneDataOffsets` through `AreaParserCore` (lines 3106–3183) now have
individual table and control contracts. Seven feasible data edges record the
background/foreground offset and data tables, background triplets, terrain
metatile selector and two-byte terrain masks. The integration pass separately
records ordinary versus backloading parser-core entry and both task-selector
edges. Current C's ROM-free unit-test entry skips stream processing only when
no area PRG is bound; the audited production route has a loaded area stream
and follows the ROM's unconditional call. No static production-route mismatch
was found. These eight nodes, four newly classified control relations and
seven data paths remain `needs-evidence` pending original-ROM/x86/x64 scenery,
terrain and backloading route captures.

### Cohort C — B10e scenery construction and block-buffer handoff

`RenderSceneryTerrain` through `BlockBuffLowBounds` (lines 3184–3318) now
have individual contracts, and all 43 internal control relations plus two
return handoffs are independently registered. The audit covers staged-column
clear, modulo-three background selection, bounded background overlay,
zero-preserving foreground overlay, water/world/cloud/underground terrain
exceptions, both terrain-mask bytes, object-stream-before-buffer ordering,
and all thirteen qualified physical block-buffer stores. The threshold-table
producer-to-consumer path is recorded separately. No static discrepancy was
found; these 20 nodes, 45 relations and the new material path remain
`needs-evidence` pending controlled original-ROM/x86/x64 scenery and block
buffer route comparisons.

### Cohort C — B10f area-object stream entry and normalization

`ProcessAreaData` through `NormObj` (lines 3326–3480) now have individual
contracts and 57 control/return relations. The audit records the three-slot
descending loop, resident-object offset selection, page-control sequencing,
row-13 loop-control behavior, row-14 backloading exception, behind-page
rescan, object-length handling, normalized small/large/special identity and
pipe-warp override. One feasible material edge records slot-selected area-data
offset to decoder record consumption. No static discrepancy was found. These
23 nodes, 57 relations and the data path remain `needs-evidence` until ROM and
x86/x64 routes cover control records, resident slots, backloading and each
object-family entry.

### Cohort C — B10g parser object-family selector and attribute/warp leaves

`LeavePar` through `NoKillE`, plus all 47 `RunAObj` selector edges, now have
static contracts. The audit records rear/page/column placement gating, the
normalized `$00 + $07` dispatch input, row-14 attribute paths, warp text and
scroll-lock ordering, and piranha removal across the five regular enemy
slots. The normalized-ID material handoff to the object-family selector is
registered independently. No static discrepancy was found. These 15 nodes,
69 relations and the data path remain `needs-evidence` until routes exercise
every object family, warp variant, placement gate and enemy-slot outcome.

### Cohort C — B10h frenzy, style ledges, pulleys and castle construction

`FrenzyIDData` through `NotTall` (lines 3629–3780) now have individual
contracts and 43 control/selector relations. The audit covers the exact
regular-slot 4→0 frenzy scan, AreaStyle's three-way selector, tree/mushroom
length states, pulley ends, castle grid row stride and star-flag gate. Two
material paths record frenzy table consumption and castle grid use. No static
discrepancy was found. These 21 nodes, 43 relations and both data paths remain
`needs-evidence` pending ROM/x86/x64 routes for each style, frenzy occupancy,
pulley phase and castle-column outcome.

### Cohort C — B10i castle finish, pipe variants and regular-slot search

`PlayerStop` through `QuestionBlockRow_High` (lines 3772–3945) now have
individual contracts and 39 control/return relations. The audit records water,
intro, exit and vertical pipes; side-pipe shaft/part tables; piranha spawn
gates; and the five-slot empty search. It explicitly distinguishes castle's
carry-ignoring star-flag allocation from vertical-pipe's carry-gated piranha
allocation. Two material paths record vertical-pipe table consumption and the
caller-specific slot-search handoff. No static discrepancy was found. These
22 nodes, 39 relations and both data paths remain `needs-evidence` pending
ROM/x86/x64 pipe, slot-full and piranha-route captures.

### Cohort C — B10j water, question-row and bridge-object integration

`Hole_Water` through `FlagBalls_Residual` (lines 3933–3989) now have individual
shared-`area.c` node contracts and fourteen local control/return relations in the
integration ledger. The audit preserves the source's intentional BIT-opcode
fall-through selectors for high/low question rows and high/middle/low bridges,
the large-object length handoff, fixed buffer rows, and the single-row versus
vertical underpart rendering distinction. No static discrepancy was found. All
seven nodes and fourteen relations remain `needs-evidence` until controlled
original-ROM and current x86/x64 routes compare water, both question rows, all
three bridge rows and flag-ball extent with the parser's persistent length and
metatile-buffer state. `FlagpoleObject` is source-ordered in Cohort D and is
intentionally excluded from this chain.

### Cohort D — B11a flagpole, rope, object-row and block-row integration

`FlagpoleObject` through `GetRow2` (lines 3991–4119) now have individual
shared-game node contracts, thirty-five local/incoming control and return
relations, and five feasible table-to-consumer paths. The audit preserves the
flag's slot-five X/page borrow initialization; distinct endless and balance
rope setup; paired row-13 tables; fixed castle-bridge length; axe's palette
selector fall-through; and the source's cloud override applying only to brick
rows, never brick columns. No static discrepancy was found. All twenty-three
nodes, thirty-five relations and five material paths remain `needs-evidence`
until controlled original-ROM and current x86/x64 parser routes compare flag
initialization, both rope variants, all row-13 objects, coin rows, cloud and
non-cloud brick rows, solid rows and both vertical column paths.

### Cohort D — B11b cannon, staircase, spring and block-object integration

`BulletBillCannon` through `ExitDecBlock` (lines 4120–4233) now have static
node contracts and forty newly classified control and return relations. The
audit distinguishes each cannon-height exit before ring registration, the
first-column-only staircase initialization, the full-slot jumpspring path,
hidden 1-UP suppression, the coin-timer fall-through, and the area-dependent
question/brick metatile selection. No static discrepancy was found. All
sixteen nodes and forty relations remain `needs-evidence` until controlled
original-ROM and current x86/x64 routes compare every cannon height, ring
wrap, staircase continuation, full ordinary slot pool, hidden flag state, and
ground/non-ground block selector outcomes.

### Cohort D — B11c hole, underpart and parser-helper integration

`HoleMetatiles` through `GetBlockBufferAddr` now have static node contracts and
twenty-seven local control and return relations. The audit records water-only,
first-column whirlpool registration, the five-slot wrap, every `RenderUnderPart`
overwrite predicate, byte-length carry initialization, wrapped attribute read,
and pixel coordinate conversion. No static discrepancy was found; all sixteen
nodes and relations remain `needs-evidence` pending controlled ROM/x86/x64
object routes.

### Cohort E — B12a game-engine root integration

`GameMode` through `ProcELoop` now have twenty-two static node contracts and
forty-nine control/return relations. The audit records game-mode dispatch,
timer, palette and music ordering, engine-subroutine execution and parser/
scroll handoff. Star-palette reset and area-music selection are confirmed in
the shared game core rather than a platform adapter. These entries remain
`needs-evidence` until a controlled original-ROM/x86/x64 matrix covers the
mode, timer, palette and engine-subroutine alternatives.

### Cohort E — B12b player entry and control integration

`GameRoutines` through the player-control, pipe, vine, automatic-control and
hole paths now have twenty-five node contracts and sixty-four control
relations. The audit records the source dispatch and entry sequencing, with
the shared player core as the only game-logic owner. No static discrepancy was
found; the nodes and edges remain `needs-evidence` pending controlled routes
for each entrance, pipe/vine and automatic-control branch.

### Cohort E — B12c player transition integration

The pipe, vine, size, death, fire-flower, flagpole and end-level transition
chain now has thirty-three node contracts and sixty-nine control relations.
The static pass confirms that `ChgAreaPipe` decrements zero to `$ff` and that
vertical-pipe selection occurs only after its source scrolling decision. No
static discrepancy was found. All entries remain `needs-evidence` until ROM,
x86 and x64 routes cover the transition alternatives and their persistent
state handoffs.

### Cohort F — B12d player movement-state and jump-physics integration

`PlayerMovementSubs` through `GetYPhy`, including the player-state dispatch,
ground/air/climb state paths, jump initialization and vertical-physics tables,
now has forty static node contracts and fifty-eight control relations. The
audit preserves the source state dispatch, jump/swim selectors and physics
table ordering. No static discrepancy was found. These items remain
`needs-evidence` pending controlled original-ROM/x86/x64 movement-state and
jump/swim route comparisons.

### Cohort F — B12e horizontal physics, animation and friction integration

The source-contiguous player chain from `PJumpSnd` through `SetAbsSpd` now has
an independent node-semantics and integration pass. It records twenty-two node
contracts, forty internal branch/fall-through/jump relations, four caller
return relations, and twelve feasible table-to-consumer paths. The contracts
cover jump-sound selection; grounded, water and airborne X-physics indices;
run timer and fast-friction gates; entrance maximum-right substitution;
animation timer/skid behavior; and every friction branch.

The friction contract specifically keeps the source's released-input split:
positive speed takes the subtractive path and negative speed takes the
additive path, so both converge toward zero. Held directions instead use the
right-bit LSR precedence. No static discrepancy was found in this chain. All
twenty-two nodes, forty-four control relations and twelve material paths are
`needs-evidence` until the same original-ROM, x86 and x64 route matrix covers
the listed branch families, clamps, table indices, speed-sign paths and caller
returns. This batch therefore increases audit coverage but makes no
current-exact claim.

### Cohort G — B13a fireball, explosion and bubble-core integration

`ProcFireball_Bubble` through `BubbleTimerData` now has nineteen independent
node contracts, fifty-nine newly classified control/return relations and three
feasible data paths. The integration audit records fireball status and
creation gates, two-slot order, cross-page creation carry, the exact
relative-position → offscreen bits → bounding box → terrain sequence, the
`FBall_OffscreenBits & $cc` erase gate, and enemy collision before drawing.
It also records the water-only descending bubble loop, facing carry into bubble
placement, fractional-force borrow and the `$f8` inactive sentinel. No static
discrepancy was found. All entries remain `needs-evidence` until controlled
original-ROM/x86/x64 routes exercise every fireball state, boundary, collision
and bubble timer/random-bit branch.

### Cohort G — B13b timer, warp, whirlpool, flagpole and jumpspring integration

`RunGameTimer` through `DrawJSpr` now has twenty-four node contracts, seventy
control/return relations and three feasible data paths. The audit records all
timer exits and zero-time ordering; Warp Zone's bitwise gate; descending,
carry-correct whirlpool extent/center tests; flagpole score and movement
carries; and each spring animation/bounce transition. No static discrepancy
was found. These entries remain `needs-evidence` until controlled
original-ROM/x86/x64 routes cover every gate, table index, timer and actor
state transition.

### Cohort G — B13c vine initialization tail

The final source-order Cohort G chain, `Setup_Vine` through `VineHeightData`,
now has three node contracts, three newly classified branch/return relations
and one feasible data path into the next cohort's growth handler. The audit
records the first-vine-only start-Y write, ordered slot append, sound queue and
decrement-before-height-index consumer. No static discrepancy was found; all
entries remain `needs-evidence` pending the shared original-ROM/x86/x64 vine
route.

### Cohort H — B14a vine growth and block-buffer integration

`VineObjectHandler` through `ExitVH` now has six node contracts, twenty-five
control/return relations and the growth-threshold data path. The audit records
slot-five gating, two-of-four-frame growth, ordered drawing, descending
offscreen cleanup, and the qualified empty-cell climb-metatile write. No
static discrepancy was found; all entries remain `needs-evidence` pending a
controlled original-ROM/x86/x64 vine-growth route.

### Cohort H — B14b cannon and Bullet Bill integration

`CannonBitmasks` through `KillBB` now has fourteen node contracts,
forty-eight control/return relations and two feasible data paths. The audit
records the descending three-slot cannon scan, hard-mode random mask, timer
borrow, cannon-spawn initialization, signed player-distance/carry test,
defeated movement and the fixed collision/graphics tail. No static discrepancy
was found; all entries remain `needs-evidence` pending controlled
original-ROM/x86/x64 cannon and Bullet Bill routes.

### Cohort H — B14c hammer generation and motion integration

`HammerEnemyOfsData` through `RunHSubs` now has ten node contracts,
twenty-nine control/return relations and two feasible table paths. The audit
records random slot selection, carry-result allocation, state-two speed setup,
carry-correct parent-relative placement, movement/collision ordering and the
common graphics tail. No static discrepancy was found; all entries remain
`needs-evidence` pending controlled original-ROM/x86/x64 hammer routes.
