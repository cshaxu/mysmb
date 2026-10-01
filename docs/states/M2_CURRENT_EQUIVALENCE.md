# M2 current-equivalence re-audit

This registry is the current-build complement to
[node progress](NODE_PROGRESS.md). Historical node-accounting status remains
`1,992 / 1,992`; it must never be read as a current end-to-end result until a
row below records a fresh audit disposition.

## Current static-classification checkpoint — Td S9

The Td S9 source pass has now assigned a current semantic disposition to every
known unit. These are **not** a current end-to-end completion claim: `exact`
requires its recorded ROM/native route, while `needs-evidence` still needs that
route.

For raw extractor relations only, `infeasible` is a distinct disposition: it
records a relation which the ROM's own instruction semantics make impossible.
It remains for provenance but is excluded from the feasible control-graph
denominator. It never means an unexecuted C path is correct.

| Ledger | Exact | Needs evidence | Mismatch | Unclassified | Total |
| --- | ---: | ---: | ---: | ---: | ---: |
| ROM labels | 38 | 1,944 | 10 | 0 | 1,992 |
| Control edges | 76 | 4,241 | 25 | 0 | 4,342 |
| Proven material edges | 3 | 483 | 1 | 0 | 487 |

All 11 semantic mismatches are mapped to the existing A2, A6, A7, B2, B3 and
H9 repair candidates. The remaining 15 control-edge mismatches are extractor
false relations and are mapped to existing H1–H8 graph-governance candidates.

The machine-readable node/control-edge ledger is
[`M2_CURRENT_EQUIVALENCE.json`](M2_CURRENT_EQUIVALENCE.json). It is generated
by `BuildM2CurrentAuditRegistry.py` for the baseline and then updated only by
cohort audit evidence. It contains no ROM bytes or source text: every node
records its current C owner/counterpart and both evidence tracks, while every
edge records its C integration counterpart and both evidence tracks.
[`VerifyM2CurrentAuditRegistry.py`](../../tools/VerifyM2CurrentAuditRegistry.py)
rejects an `exact` disposition lacking either track and rejects duplicate or
incomplete node/control-edge identities.

### T54 S1 screen-initialization and palette result

The 20 labels from `InitScreen` through `NoAltPal`, 25 internal executable
control relations, and four palette material relations are current-exact. A
fresh static comparison found no feasible C/ROM difference. Controlled
original-ROM/current x86/x64 routes cover task 0/1, every `AreaType`,
`BackgroundColorCtrl` 0/4/5/6/7, Mario/Luigi/fire selection, and both
alternate-palette paths. The compared S1 state is exact in work RAM
`$0300-$07ff` excluding the established PPU-shadow ABI bytes `$0778/$0779`,
plus applicable CIRAM, palette, OAM and physical PPU scalars. The task-11
route stops at its task boundary; its subsequent title transfer remains S3
scope. Focused x86/x64 checks, the shared DOS16 link and platform-purity pass.
The live registry is **122 exact nodes**, **253 exact feasible control
relations**, **10 exact material relations**, and **zero mismatches**;
historical conformance remains **1,992 / 1,992**.

### T52 S5 B3 full-callee-chain result

The former B3 mismatch is rejected. `DisplayTimeUp`, `OutputInter` and
`NoTimeUp` are now current-equivalence exact, as is `control-00225`.
The original static interpretation stopped at `OutputInter`; direct-ROM source
inspection and a source-reachable probe at its RTS (`$86d2`) show its
`ResetScreenTimer` callee increments `ScreenRoutineTask` to task 5 before the
return. Four-frame expired and non-expired original-ROM routes match the shared
C implementation on x86 and x64 for the owned task, latch, timer,
disable-screen and screen-buffer state. This raises the live registry to **53
exact nodes** and **87 exact control edges**; historical conformance remains
**1,992 / 1,992**.

### T52 S6 H9 large-platform Y-source result

`DrawLargePlatform` is now current-equivalence exact.  The original route uses
relative X for its six-sprite stack, then reads `Enemy_Y_Position,x` for the
first four OAM Y records.  The shared owner now does the same.  A focused
differential fixture keeps `$00cf+x=$40` and `$03b9=$70`; both x86 and x64
write `$40` to those rows while preserving castle, secondary-hard, cloud and
offscreen behavior.  Twelve retained original-ROM parent records replay with
zero non-stack RAM differences on both widths.  The live registry is now
**54 exact nodes**, **0 node mismatches**, **1,938 nodes needing evidence**;
historical conformance remains **1,992 / 1,992**.

### T52 S7 H1–H8 infeasible-edge result

The raw extractor still retains all **4,342** candidate relations for review,
but fifteen are now explicitly `infeasible`, rather than being misreported as
missing C integration. They are the H1–H8 IDs `control-01339`,
`control-01405`, `control-01408`, `control-01415`, `control-01502`,
`control-01515`, `control-01537`, `control-01552`, `control-01632`,
`control-01711`, `control-02036`, `control-03743`, `control-03769`,
`control-03784` and `control-03868`. The feasible graph denominator is
therefore **4,327**. The real parent calls, taken branches and 9/55/6/7/5
`JumpEngine` selector relations remain recorded as `needs-evidence`; no
unexecuted path receives `exact` credit and no shared C source changes.

### T53 S1 initial reset/NMI dispositions

`ScreenOff` is now a current-equivalence `mismatch`.  The ROM writes its
$2001 display-mask transaction before `InitScroll`, OAM DMA and
`UpdateScreen`; the current `frame_root.c` calls its VRAM commit before
`mysmb_game_commit_display_state`.  The same reversed transaction is recorded
on `control-00018`, `control-00019`, `control-03487` and `control-03488`.
This is one later unnumbered repair candidate in the shared frame-root owner;
it requires a controlled order trace before any source change.

`control-00076` is `infeasible`, not a missing C route.  `JumpEngine` removes
the caller return address with two `PLA` instructions and performs `JMP ($06)`;
there is no execution path from `OperModeExecutionTree` through its inline
vectors to `MoveAllSpritesOffscreen`.  The raw graph remains 4,342 relations,
with **16** infeasible records and **4,326** feasible control relations.
Historical conformance remains **1,992 / 1,992**.

### T53 S2 title-dispatch extractor correction

Two more Cohort A raw control records are `infeasible`: `control-00081`
(`TitleScreenMode` to `WSelectBufferTemplate`) and `control-03497`
(`JumpEngine` return to `TitleScreenMode`).  `TitleScreenMode` calls
`JumpEngine` immediately before its inline vector words.  The ROM's
`JumpEngine` consumes that return address with two `PLA` instructions and
uses `JMP ($0006)` to select the vector target.  It neither falls into those
words nor returns to `TitleScreenMode`.  The raw graph remains 4,342 records;
18 are now explicitly infeasible, leaving **4,324** feasible control
relations.  This is graph correction only; title-mode node and executable
route evidence remain in T53 S2.

### T53 S2 title/menu/demo result

All 26 title/menu/world-select/icon/demo labels are now current-exact. Six
fresh 600-frame original-ROM routes cover idle/demo, Select, enabled
world-select B, Start, A+Start and expired Select. Current x86 and x64 agree
with the ROM in work RAM `$0200-$07ff` except `$0778/$0779`, both CIRAM pages,
palette, OAM, audio and PPU scalars; the two native records are byte-identical.
The focused title-data and title-demo checks pass. The six-byte
`WSelectBufferTemplate` material relation is also exact. The live registry is
now **75 exact nodes**, **142 exact control relations**, **18 infeasible raw
relations**, **4,324 feasible control relations**, and one remaining
`ScreenOff` mismatch. Historical conformance remains **1,992 / 1,992**.

### T53 S3 `ScreenOff` corrective result

The shared NMI root now applies the temporary `ScreenOff` display mask before
the source scroll/OAM/VRAM sequence. `ScreenOff` and transaction relations
`control-00018`, `control-00019`, `control-03487`, and `control-03488` are
current-exact. Focused NMI-parent checks pass on x86 and x64, and the same C90
source linked into the refreshed DOS16 artifact. The live registry is now
**76 exact nodes**, **146 exact control relations**, **18 infeasible raw
relations**, **4,324 feasible control relations**, and **zero mismatches**.
Historical conformance remains **1,992 / 1,992**.

## Source-anchor resolvability finding

Td S9's independent counterpart-resolvability pass found that the existing
semantic descriptions are not yet uniformly machine-locatable: 1,445 of 1,992
node records, 3,361 of 4,342 control-edge records and 408 of 487 material-edge
records can currently be tied to one or more concrete `src/...` C files from
their recorded owner/counterpart text.  The remaining **547 nodes, 981 control
edges and 79 material edges** use aggregate owner descriptions (most often
ROM area-stream data, shared movement families or selector tables) and require
a precise data-consumer or shared-owner path before their source comparison is
reviewable at node/edge granularity.

This is an audit-metadata gap, not a new claim about game behavior and does not
change any `exact`, `needs-evidence` or `mismatch` disposition.  It is now a
mandatory normalization step of the source-order audit: no unresolved aggregate
description can receive current-exact credit until its concrete shared-C
owner/data consumer and integration counterpart are recorded.

All source-order cohorts A through N are now normalized: every one of the
1,992 nodes, 4,342 control edges and 487 proven material edges carries a
validated `currentSourcePaths` entry.  Area-stream labels remain ROM data:
`area_data.c` chooses each stream pointer, `enemy/stream.c` consumes `E_*`
enemy records and `area.c` consumes `L_*` area-object records.  The rest map
to their concrete shared-game owners, including dispatch, player state,
objects, area parsing, enemy systems, OAM rendering, collision and audio.
The registry verifier now requires a non-empty, existing `src/...` C path for
every record.  This closes the source-resolvability metadata gap only; it does
not change any semantic disposition or satisfy any pending ROM-route
obligation.

## Current evidence boundary

The retired baseline tables below the static checkpoint have been removed:
they described an earlier partial pass and are not current evidence. The
machine-readable registry is the authority for live counts.

The raw extractor graph is fixed at **4,342** candidate relations: 611 calls,
247 direct jumps, 1,566 branches, 1,058 fall-through relations, 611 returns,
two vectors and 247 `JumpEngine` selector edges. Fifteen have the explicit
`infeasible` disposition, so the current feasible-control denominator is
**4,327**. Material edges are different: the registry
currently contains **487 proven feasible** RAM/table producer-to-consumer
relations. Each is assigned once to a cohort; a later source-path audit may
add a relation only when it proves feasibility. Writer-reader Cartesian
products are forbidden.

Nodes, control edges and material edges retain independent dispositions. A
node is not current-exact merely because its output matches: its owned control
and feasible material connections must have their own source and route
evidence.

### Td S9 shared operational preflight

Two fresh, owner-ROM 600-frame routes establish the current cross-width
comparison baseline before cohort dispositions are changed.  Both use the
shared native game core, one newly built Win32 x86 recorder and one newly
built Win32 x64 recorder.  The recorders are byte-identical per route.

| Route | Reference controller script | Native controller script | A labels reached | Comparable result |
| --- | --- | --- | ---: | --- |
| Idle title | no buttons | `0:0` | 47 | Work RAM, CIRAM, palette, CPU/visible OAM, audio and all PPU scalars match for 600 samples. |
| Start/action | `0:0,200:8,201:0,240:128,310:129,340:128` | `0:0,200:16,201:0,240:1,310:129,340:1` | 52 | The same fields match for 600 samples. |

The reference script represents controller serial-bit order; the native
script represents the decoded saved-button byte.  It is therefore the
bit-reversal of each reference byte (`08h -> 10h`, `80h -> 01h`,
`81h -> 81h`).  The comparison excludes only ROM CPU scratch `$0000-$0007`
and the `$01f0-$01ff` APU/6502 execution-stack window.  These routes provide
operational evidence only for labels and edges actually reached; no
needs-evidence status is promoted by this preflight.

The independent platform-boundary audit also passes: `src/platform` has no
direct game RAM, CIRAM, palette, OAM, scroll or operating-mode access.  Win32
and DOS16 only translate host input, consume startup timing, call the shared
game tick, and submit a completed shared PPU frame.  This is an architecture
result, not ROM-node credit.

### Cohort allocation

The registry retains **all 4,342 raw control relations** once, by the source label
that emits the edge (vectors are owned by their target label's cohort; return
records use the caller cohort because the original `JSR` is the source).
Explicitly infeasible records remain visible for audit provenance and are
excluded from the feasible integration-audit denominator.

| Cohort | Nodes | Control edges | Proven material edges |
| --- | ---: | ---: | ---: |
| A | 97 | 239 | 6 |
| B | 67 | 122 | 8 |
| C | 260 | 521 | 51 |
| D | 146 | 111 | 12 |
| E | 80 | 239 | 1 |
| F | 62 | 122 | 12 |
| G | 49 | 133 | 8 |
| H | 129 | 344 | 19 |
| I | 165 | 420 | 60 |
| J | 497 | 1,261 | 245 |
| K | 154 | 313 | 21 |
| L | 83 | 165 | 9 |
| M | 126 | 296 | 5 |
| N | 77 | 56 | 30 |
| **Total** | **1,992** | **4,342** | **487** |

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

### T52 S4 — B2 current remediation result

The B2 repair has completed after the static source audit and five controlled
owner-ROM task-ten routes. `GetBackgroundColor`, `NoBGColor`,
`GetPlayerColors`, `control-00204`, `control-00205` and `control-00206` are
current-equivalence `exact`. The routes cover BackgroundColorCtrl values 0,
4, 5, 6 and 7 through ordinary `GameMode -> ScreenRoutines` dispatch; x86 and
x64 each agree with the ROM on task advancement, address control, Buffer1
offset and the emitted `$3f10` command. The current registry now reports 50
exact nodes, 1,940 needing route evidence and two remaining semantic
mismatches; it reports 86 exact control edges, 4,240 needing evidence and 16
remaining control mismatches. Material-edge dispositions are unchanged.

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

### Cohort H — B14d coin, score and misc-object integration

`CoinBlock` through `NoZSup` now has twenty-one node contracts, fifty
control/return relations and three feasible data paths. The audit records
carry-sensitive coin coordinate creation, bounded misc-slot fallback, jump
coin/floatey state changes, scroll carry, BCD coin/score routing, hundred-coin
life behavior and status zero suppression. No static discrepancy was found;
all entries remain `needs-evidence` pending controlled original-ROM/x86/x64
coin, score and misc-object routes.


### Cohort H — B14e PowerUp initialization, emergence and active-object integration

`SetupPowerUp` through `ExitPUp` now has ten independent node contracts, thirty-nine
control/return relations and two feasible RAM handoffs. The integration pass
records fixed slot-five initialization, PlayerStatus-derived mushroom/flower
selection, priority/sound tail, the state-bit dispatcher, the every-four-frame
emergence threshold, and the exact `RelativeEnemyPosition` → offscreen bits →
bounding box → graphics → player collision → bounds order. It also preserves
the source rule that an emerging item becomes visible and collidable at state
six, before its later active-state transition. No static discrepancy was
found. These nodes, relations and material paths remain `needs-evidence` until
controlled original-ROM/x86/x64 routes cover each type, timer gate, emergence
threshold, collision and offscreen branch.


### Cohort H — B14f player-head collision and block-content dispatch integration

`BlockYPosAdderData` through `MatchBump` now has twenty-four node contracts,
fifty-nine control/return/dispatch relations and four feasible RAM/table
handoffs. The audit records both PlayerSize block-state paths, coin-brick
timer behavior, buffer replacement and coordinate captures, alternating block
slots, the fourteen-entry descending metatile classifier, and all nine content
dispatch targets. The shared C control and state semantics are statically
aligned.

The integration pass also found two inaccurate control entries in the current
extracted graph: `control-01339` records a fall-through from `BlockCode` into
the first vector word and `control-03743` records a `JumpEngine` return to
`BlockCode`. Neither is reachable in the original ROM. `JumpEngine` consumes
the JSR return address and indirect-jumps through the selected vector; the
selected target's `RTS` resumes the caller of `BumpBlock`. These two **graph
ledger** edges are recorded as mismatches and have an unnumbered governance
repair candidate; they are not C game-logic defects. All remaining entries
remain `needs-evidence` pending controlled original-ROM/x86/x64 head-hit,
brick, question, hidden, coin, vine and content-dispatch routes.


### Cohort H — B14g brick shatter, block lifetime and replacement integration

`BrickShatter` through `NextBUpd` now has twelve node contracts, fifty-eight
control/return relations and three feasible material handoffs. The integration
pass records the above-block coin path, paired chunk initialization, distinct
bounce/chunk lifetime branches, high/low Y retirement predicates, and the
two-slot replacement updater's Buffer1-idle gate. No static shared-C
discrepancy was found. These entries remain `needs-evidence` pending
controlled original-ROM/x86/x64 routes for top coins, broken bricks, bounce
replacement, pair retirement and both updater slots.


### Cohort H — B14h shared horizontal and vertical movement/gravity integration

`MoveEnemyHorizontally` through `ExVMove` now has thirty-two node contracts,
seventy-eight control/return relations and three feasible material handoffs.
The audit records signed 4.4 horizontal speed expansion, both fractional and
page carries, the player jumpspring gate, every enemy vertical force/maximum
entry, block gravity table selection, BIT-overlap platform direction, and the
wrapped-subtraction tests that implement both gravity clamps. The shared C
logic is statically aligned.

Three extracted graph entries are mismatches rather than implementation
defects: `control-01405` and `control-01408` are fall-throughs after branches
whose freshly loaded nonzero operands make them unconditional, and
`control-01415` represents a BIT-overlap entry as a full target-label entry
even though it skips that label’s first load. The affected graph relations are
recorded as mismatches with an unnumbered governance repair candidate. The
remaining entries stay `needs-evidence` pending controlled original-ROM/x86/x64
routes spanning sign/carry boundaries, jumpspring, every force entry and both
velocity clamps.


### Cohort H — B14i enemy-loop core and castle loop-command integration

`EnemiesAndLoopsCore` through `ChkEnemyFrenzy` now has sixteen node contracts,
thirty-four control/return relations and four feasible table handoffs. The
audit records high-bit linked-enemy cleanup, parser-task-seven suppression,
reverse table search, World-7 three-pass logic, page rollback, parser-control
reset, kill-after-loopback ordering and frenzy activation. No static shared-C
discrepancy was found. These entries remain `needs-evidence` pending controlled
original-ROM/x86/x64 routes for linked flags, task-seven, each loop selector,
World-7 pass outcomes, loopback and queued frenzy activation.


### Cohort H — B14j enemy stream, range gate and initializer-vector integration

`ProcessEnemyData` through `InitEnemyRoutines` now has twenty-one node
contracts, one hundred and three control/return/dispatch relations and four
feasible material handoffs. The audit records the sixth-slot exception, normal
and extended right boundary carry, page-control records, row-$0e reuse, hard
mode gate, group range, Goomba mutation, fallback vine/frenzy initialization,
two/three-byte advancement and all fifty-five initializer-vector bindings.
The shared C stream and initializer semantics are statically aligned.

As with the block vector, two extracted entries are graph mismatches:
`control-01502` treats vector data after `JSR JumpEngine` as fall-through and
`control-03769` treats JumpEngine as returning to `InitEnemyRoutines`. Both
are infeasible in the ROM; the selected target returns to the caller context.
They are recorded in an unnumbered graph-governance candidate, not as a shared
C game-logic repair. All other entries remain `needs-evidence` pending
controlled original-ROM/x86/x64 stream, boundary, hard-mode, group, fallback
and vector routes.


### Cohort I — B14k ordinary enemy initializer integration

`NoInitCode` through `InitCheepCheep` now has twenty-one node contracts,
thirty-four control/call/tail/return relations and four feasible material
handoffs. The node pass records all normal, Goomba, Podoboo, retainer, red
Koopa, Hammer Brother, Bloober, paratroopa, Bullet Bill and Cheep Cheep
write footprints; it also records both mode-indexed tables and the inherited
carry at the red-paratroopa center calculation. The integration pass covers
every shared initializer tail and all later consumers of the persistent
paratroopa and Cheep Cheep state.

It found one graph-ledger discrepancy: `control-01515` treats `SmallBBox` as
falling through to `InitRedPTroopa`, although `LDA #$09; BNE SetBBox` makes
that not-taken path impossible. This is an extractor/registry repair
candidate, not a shared-C game-logic defect. All other entries remain
`needs-evidence` pending controlled original-ROM/x86/x64 routes for each
mode table, direct target, common-tail and persistent-state consumer path.


### Cohort I — B14l Lakitu/Spiny initializer and frenzy integration

`InitLakitu` through `ChpChpEx` now has sixteen node contracts, including the
reverse Lakitu and free-slot searches, timer and state gates, three-band random
adjustment copy, intentional loss of the computed speed through `SmallBBox`,
and final egg activation. The integration pass records every loop, early exit,
setup/position call, dispatch and return relation plus four feasible RAM/table
handoffs. Shared C is statically aligned with those source semantics.

Two extracted graph edges are impossible source paths: `control-01537` is a
sequential fall-through after the exhausted-slot `BMI`, and `control-01552` is
a negative branch after `SmallBBox` has returned A=$00. They are graph-ledger
mismatches in an unnumbered governance candidate, not C game-logic defects.
All other entries remain `needs-evidence` pending controlled original-ROM/x86/x64
routes for timer gates, both searches, reappearance, Spiny spawn/sign paths
and egg activation.


### Cohort I — B14m firebar and flying-Cheep initializer integration

`FirebarSpinSpdData` through `FinCCSt` now has fourteen node contracts and
all incident call, return, dispatch, branch and fall-through relations. The
node pass records the shared firebar table index, X page carry, long-firebar
child ordering, flying-Cheep timer/slot gates, player-speed bias, random seed
override, stationary reversal and both final page carry/borrow paths. Five
feasible table handoffs are separately registered. No static shared-C
discrepancy was found.

These entries remain `needs-evidence` pending controlled original-ROM/x86/x64
routes for every firebar ID, X wrap, timer gate, hard-mode capacity gate,
player-speed bias, random override, direction reversal and both position
branches.


### Cohort I — B14n Bowser initializer and object-duplication integration

`InitBowser` through `FlmEx` now has four node contracts, all incident call, loop, fall-through, return and dispatch relations, and three feasible material handoffs. The audit records the byte-wrapping free-slot scan and exact rear-object copy footprint separately from Bowser persistent control/timer initialization. No static shared-C discrepancy was found; entries remain `needs-evidence` pending controlled original-ROM/x86/x64 routes.


### Cohort I — B14o Bowser-flame generation integration

`FlameYPosData` through `FinishFlame` now has eight node contracts, every incident branch/call/tail/return/dispatch relation, and four feasible table/state handoffs. The audit records both generation paths, hard-mode timer adjustment, random height/force selection, right-edge page carry and shared activation tail. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending matched original-ROM/x86/x64 routes for timer gate, both generators, both force directions and X page carry.


### Cohort I — B14p fireworks frenzy integration

`FireworksXPosData` through `ExitFWk` now has five node contracts, all incident timer, loop, dispatch and return relations, and three feasible data handoffs. The audit records the source reverse star-flag scan, decrement/index order, subtract/add carry propagation, matched X/Y tables and final actor state. No static shared-C discrepancy was found; entries remain `needs-evidence` pending matched original-ROM/x86/x64 routes.


### Cohort I — B14q Bullet Bill/Cheep frenzy integration

`Bitmasks` through `ExF17` now has thirteen node contracts, all incident timer, area, capacity, loop, call, tail, dispatch and return relations, plus four feasible data handoffs. The audit records water ID selection, land duplicate-bill suppression, full-filter reset, wrapped unique-height retry and final initialization. No static shared-C discrepancy was found; entries remain `needs-evidence` pending matched original-ROM/x86/x64 routes.


### Cohort I — B14r group-enemy integration

`HandleGroupEnemies` through `NextED` now has eight node contracts, all incident classification, loop, call, tail and return relations, and four feasible RAM handoffs. The audit records hard-mode substitution, d0/d1 group decoding, two/three member count, regular-slot restriction, $18 spacing with page carry and member-by-member initializer order. No static shared-C discrepancy was found; entries remain `needs-evidence` pending matched original-ROM/x86/x64 routes.


### Cohort I — B14s Piranha and frenzy dispatch integration

`InitPiranhaPlant` through `NextFSlot` now has six node contracts, all incident initializer, vector, loop and return relations, and three feasible RAM/vector handoffs. The audit records Piranha alias writes, six-target frenzy dispatch and complete Lakitu-state shutdown. Two graph-only mismatches were found: the extractor treats frenzy vector words as fall-through and JumpEngine as returning to its caller label; both are impossible in ROM. All remaining entries are `needs-evidence`.


### Cohort I — B14t jump-green-paratroopa box-tail integration

`InitJumpGPTroopa` through `SetBBox2` now has three node contracts, all incident fall-through/dispatch relations and one feasible state handoff. The audit confirms its intentionally narrow direction/speed/box write footprint. No static shared-C discrepancy was found; entries remain `needs-evidence`.


### Cohort I — B14u balance/drop/horizontal platform integration

`InitBalPlatform` through `PosPlatform` now has eleven node contracts, incident platform control relations and four feasible data handoffs. The audit records balance alignment alternation, collision/counter entries, vertical reset ordering, castle/hard box choice and all low/high page-carry position table use. No static shared-C discrepancy was found; entries remain `needs-evidence`.


### Cohort I — B14v vertical and lift-platform integration

`InitVertPlatform` through `CommonSmallLift` now has eight independent node contracts, all incident control relations (including dispatch, branch, fall-through, call, tail-jump and return) and five feasible material handoffs. The static shared-C audit matches signed top/center construction, force/speed ordering, position-before-box ordering and the large-lift box continuation. They remain `needs-evidence` until controlled original-ROM/x86/x64 routes cover both signed vertical branches and both lift directions.


### Cohort I — B15a enemy-object dispatcher integration

`EndOfEnemyInitCode` through `RunFirebarObj` now has eleven node contracts and every incident control relation recorded, including actor-vector and movement-vector dispatch selectors, calls, timer branches, terminal jumps and synthetic returns. Seven feasible material handoffs cover selector scratch, timer gating, vector selection and child-produced rendering/collision state. Static review found no shared-C order or selector discrepancy; all remain `needs-evidence` pending controlled original-ROM/x86/x64 paths.


### Cohort I — B15b platform runner integration

`RunSmallPlatform` through `LargePlatformSubroutines` now has four node contracts, all incident calls, timer branches, tail-jumps, returns and movement-vector edges, and five feasible material handoffs. Static source review matches small-platform draw-before-move, large-platform timer-gated move-before-draw, post-move relative-position refresh and the ID-$24 seven-entry dispatch table. All entries remain `needs-evidence` until the corresponding controlled ROM/x86/x64 paths run.


### Cohort I — B15c lifecycle and Podoboo integration

`EraseEnemyObject`, `MovePodoboo` and `PdbM` now have node contracts, all incident control relations and four feasible state handoffs. Static review matches all eight erase fields and both Podoboo timer paths. It also found one graph-only discrepancy: `control-01711` falsely treats a JumpEngine pointer table as fall-through into `EraseEnemyObject`; candidate H7 records the extractor repair, with no shared-C change. The three nodes otherwise remain `needs-evidence`.


### Cohort I — B15d Hammer Bro front-chain integration

`HammerThrowTmrData` through `SetShim` now has thirteen node contracts, every incident branch/call/fall-through/tail/return relation and six feasible table/state handoffs. Static review matches defeated-state priority, jump and throw timer progression, screen gating, spawn success/failure behavior, random/hard-mode jump selection and the direction-before-normal-move tail. These entries remain `needs-evidence` pending controlled ROM/x86/x64 hammer-spawn and jump routes.


### Cohort I — B15e normal-enemy movement integration

`MoveNormalEnemy` through `NKGmba` now has eleven node contracts, every incident state branch, call, tail-jump, fall-through, return and vector relation, plus six feasible table/state handoffs. Static review matches state-bit precedence, gravity/horizontal order, temporary speed restoration, revived-speed selection and the timer-$0e Goomba-only erase predicate. These entries remain `needs-evidence` pending controlled ROM/x86/x64 state-matrix routes.


### Cohort I — B15f jumping and red-paratroopa integration

`MoveJumpingEnemy` through `MovPTDwn` now has five node contracts, all incident calls, branches, tails and returns, and four feasible Y-state handoffs. Static review matches gravity-before-horizontal ordering, the frame-gated anchor correction and center-height direction choice. The entries remain `needs-evidence` pending controlled ROM/x86/x64 jump and vertical-cycle routes.


### Cohort I — B15g green paratroopa and X-counter integration

`MoveFlyGreenPTroopa` through `XMRight` now has ten node contracts, all incident calls, branches, fall-throughs and returns, and five feasible counter/direction handoffs. Static review matches every-fourth-frame counter and wave gates, endpoint primary updates, temporary two's-complement secondary displacement, direction selection and post-child secondary restoration. Entries remain `needs-evidence` pending controlled ROM/x86/x64 counter-cycle routes.


### Cohort I — B15h Bloober integration

`BlooberBitmasks` through `ChkNearPlayer` now has sixteen node contracts, all incident dispatches, branches, calls, fall-throughs, tails and returns, and six feasible table/state handoffs. Static review matches difficulty masks, slot-dependent direction, inherited carry into near-player evaluation, swim acceleration/deceleration cadence, status-bar Y limit, and bidirectional X/page carry rules. Entries remain `needs-evidence` pending controlled ROM/x86/x64 swim-cycle routes.


### Cohort I — B15i Bullet Bill and swimming Cheep integration

`MoveBulletBill` through `ExSwCC` now has nine node contracts, all incident dispatches, branches, tails and returns, plus six feasible state/table handoffs. Static review matches Bullet Bill's defeated/normal split, the Cheep type-force table, consecutive X/page borrow propagation, slot gate, vertical flag reversal and `$0f` distance threshold. Entries remain `needs-evidence` pending controlled ROM/x86/x64 movement paths.


### Cohort I — B15j Firebar state-preparation integration

`FirebarPosLookupTbl` through `SkipFBar` now has twelve node contracts, all incident control relations and seven feasible table/state handoffs. Static review matches bit-three return, timer-gated spin, short-firebar 8/24 axis skip, anchor ordering, five/eleven loop bounds and fifth-part OAM source switch. Entries remain `needs-evidence` pending controlled ROM/x86/x64 short/long Firebar routes.


### Cohort I — B15k Firebar segment and collision integration

`DrawFirebar_Collision` through `GetVAdder` now has twenty node contracts, all incident branches, calls, fall-throughs, tails and returns, plus seven feasible OAM/mirror/player-probe handoffs. Static review matches dual mirror signs, `$59`/`$f8` hiding, phase lookup, injury gates, 8x8 tests, body-size probe count, loop-counter preservation and OAM +4 exit. Entries remain `needs-evidence` pending controlled ROM/x86/x64 visible/hidden, small/big/crouching and injury routes.


### Cohort I — B15l Flying Cheep integration

`PRandomSubtracter` through `BPGet` now has six node contracts, all incident dispatches, branches, calls, fall-throughs, tails and returns, and five feasible PRG/state handoffs. Under the declared immutable PRG binding prerequisite, static review matches defeated attribute clearing, horizontal-before-gravity order, high-nibble indexing, absolute-distance `$08` force adjustment and priority-table write. Entries remain `needs-evidence` pending controlled ROM/x86/x64 routes.


### Cohort I — B15m Lakitu integration

`LakituDiffAdj` through `ExMoveLak` now has sixteen node contracts, all incident dispatches, branches, calls, loopbacks, fall-throughs, tails and returns, plus seven feasible adjustment/state handoffs. Static review matches defeated handling, Spiny request setup, descending adjustment copy, signed `$3c` saturated difference, turn/slowdown rule, player speed/scroll/Spiny index selection, pixel loop and final signed horizontal move. Entries remain `needs-evidence` pending controlled ROM/x86/x64 Lakitu and Spiny routes.


### Cohort J — B15n Bowser bridge-collapse integration

`BridgeCollapseData` through `NoBFall` now has six node contracts, every incident state branch, call, tail-jump, fall-through, return and victory-mode dispatch relation, plus seven feasible RAM/table handoffs. Static review matches the 15-byte collapse order, Bowser ID/state/Y terminal gates, four-call feet cadence, `$04/$05` staging, preserved VRAM-offset handoff, fifteenth-step falling transition, sound queue writes, and common Bowser graphics tail. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 routes for every terminal, bridge-removal and falling path.


### Cohort J — B15o Bowser dispatcher-front integration

`PRandomRange` and `RunBowser` now have node contracts and every incident dispatch, branch, fall-through and return relation, plus three feasible table/state handoffs. Static review matches d5-first defeated handling, the `$e0` falling-versus-clear split, and the ordered four-byte range binding used by the later Bowser control route. No static shared-C discrepancy was found. These entries remain `needs-evidence` pending controlled original-ROM/x86/x64 defeated/falling/terminal routes.


### Cohort J — B15p common enemy-clear-loop integration

`KillAllEnemies` and `KillLoop` now have node contracts, all incident call, loop, fall-through and return relations, and four feasible state handoffs. Static review matches initial slot four, exactly five descending erase calls, byte-wrap termination after slot zero, post-loop frenzy clear and caller-slot restoration semantics. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending a controlled original-ROM/x86/x64 terminal-clear route.


### Cohort J — B15q Bowser normal-control integration

`BowserControl` through `SetFBTmr` now has fifteen node contracts, every incident timer, world, mouth, movement-range, call, loop, tail and return relation, plus nine feasible state/table handoffs. Static review matches frenzy clearing, TimerControl bypass, feet cadence, chase/timer ordering, every-fourth-frame range selection, absolute range turn, hammer-world/frame gates, jump-expiry initialization, fire-world gate and mouth-toggle loop. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 normal, hammer, jump and flame routes.


### Cohort J — B15r Bowser front/rear OAM and collision integration

`BowserGfxHandler` through `ProcessBowserHalf` now has four node contracts, every incident child call, direction branch, fall-through, state exit, collision tail and return relation, plus five feasible OAM/state handoffs. Static review matches front-before-rear processing, `$10/$f0` rear placement, duplicate-slot/current-slot restoration, normal-state-only `$0a` bounding box, collision tail and final graphics-flag clear. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 front/rear, normal/non-normal and collision routes.


### Cohort J — B15s Bowser flame-timer integration

`FlameTimerData`, `SetFlameTimer` and `ExFl` now have node contracts, all incident call, return, fall-through and common-exit relations, plus two feasible table/state handoffs. Static review matches the eight bytes and the essential old-index-read before increment-and-mask ordering. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 counter-wrap and both caller routes.


### Cohort J — B15t Bowser-flame motion integration

`ProcBowserFlame` and `SFlmX` now have node contracts, all incident TimerControl/hard-mode/Y-target branches, graphics-tail and caller-return relations, plus three feasible force/carry/position handoffs. Static review matches the crucial carry propagation from force subtraction through X and page movement, and the equality-gated vertical movement. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 timer-freeze, both force and page-borrow routes.


### Cohort J — B15u Bowser-flame OAM integration

`SetGfxF` through `ExFlmeD` now has seven node contracts, every incident state/frame/offscreen branch, three-iteration loop, child call and return relation, plus four feasible OAM/state handoffs. Static review matches relative-position-before-state gating, `$51` tiles, two-frame attribute flip, ordered three-sprite writes and the reverse `$0/$1/$2/$3` to `+12/+8/+4/+0` hide mapping. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 visible/hidden and flipped-frame routes.


### Cohort J — B15v fireworks actor integration

`RunFireworks` through `FireworksSoundScore` now has three node contracts, all incident actor dispatch, timer branches, child calls, score tail and return relations, plus four feasible timer/OAM/score handoffs. Static review matches byte-wrap decrement behavior, zero reload `$08`, terminal frame `>=3`, Y-then-X scratch copy, actor clear, blast queue and 500-point modifier before the common area-points tail. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 timer, frame and terminal-score routes.


### Cohort J — B15w star-flag dispatcher-front integration

`StarFlagYPosAdder` through `StarFlagExit` now has eight node contracts, all incident task-gate, digit-selection, dispatch, fall-through and return relations, plus five feasible table/state handoffs. Static review matches all three OAM tables, frenzy clear, task `>=5` exit and last-digit `1/3/6` selection. Two graph-only mismatches were found: the extractor represents both a sequential fall-through and a normal return across the `JumpEngine` vector table. Candidate H8 records this extractor repair; shared C has no discrepancy. All remaining entries stay `needs-evidence` pending controlled original-ROM/x86/x64 task and digit routes.


### Cohort J — B15x star-flag endgame integration

`AwardGameTimerPoints` through `DelayToAreaEnd` now has eleven node contracts, every incident timer, score, flag, frenzy, OAM loop, interval, music, dispatch and return relation, plus eight feasible handoffs. Static review matches zero-timer exit, d2 tick gate, `$ff` then `$05` modifier ordering, Mario/Luigi score offsets, flag `$72` threshold, signed fireworks eligibility, descending four-sprite table loop, interval `$06`, and final event-music gate. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 timer conversion, no/positive fireworks and final-delay routes.


### Cohort J — B15y Piranha Plant integration

`MovePiranhaPlant` through `PutinPipe` now has six node contracts, all incident state/timer/distance/endpoint branches, child call and return relations, plus four feasible handoffs. Static review matches the `$21` absolute-distance gate, two's-complement reversal, speed-sign endpoint selection, alternate-frame plus TimerControl move gate, endpoint `$40` delay and unconditional pipe-priority attribute. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 near/far, up/down and endpoint routes.


### Cohort J — B15z Firebar spin integration

`FirebarSpin` and `SpinCounterClockwise` now have node contracts, all incident direction/return relations and two feasible phase handoffs. Static review matches scratch `$07`, clockwise low-byte carry into high byte and counterclockwise low-byte borrow through `SBC #0`, with returned high phase preserved for `ProcFirebar`. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 carry and borrow routes.


### Cohort J — B16a balance-platform entry integration

`BalancePlatform` through `ChkOtherForFall` now has six node contracts, all incident dispatch, high-Y/state/peer/collision branches and fall/stop tails, plus four feasible paired-platform handoffs. Static review matches high-byte-three erase, signed peer-state exit, `$2d/$2f` threshold behavior and selector-matched fall versus clamp/stop behavior for both platforms. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 normal, current-threshold, peer-threshold and falling routes.


### Cohort J — B16b balance-platform coupled-motion integration

`ChkToMoveBalPlat` through `DoOtherPlatform` now has six node contracts, all incident force/speed/collision branches, gravity/stop calls, paired displacement, player-position and rope-tail relations, plus four feasible handoffs. Static review matches force-plus-five carry handling, signed movement selection, collision-slot equality, old-minus-new peer displacement and player-position ordering. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 up/down/stop and player-collision routes.


### Cohort J — B16c balance-platform rope and fall integration

`DrawEraseRope` through `ExPF` now has fourteen node contracts, every incident buffer gate, speed-sign branch, helper call, paired-fall, player-position and return relation, plus eight feasible VRAM/platform-state handoffs. Static review matches both rope command tile selections, source carry replacement in normal difficulty, name-table address construction, ten-byte buffer advance, fall floatey setup, dual stop and ordered dual fall. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 rope draw/erase, hard-mode address, fall and collision routes.


### Cohort J — B16d Y-moving-platform integration

`YMovingPlatform` through `ExYPl` now has six node contracts, all incident speed/force, top/center, frame, gravity, rider and return relations, plus four feasible handoffs. Static review matches stopped-platform dummy clear, below-top eighth-frame descent, center direction split, current-slot reload after gravity and nonnegative-only rider positioning. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 stopped, top, center, up/down and rider routes.


### Cohort J — B16e X/drop/right platform integration

`XMovingPlatform` through `ExRPl` now has nine node contracts, all incident counter/movement, collision, carry/borrow, rider, speed-assignment and return relations, plus five feasible platform/player handoffs. Static review matches `$0e` counter setup, movement-before-rider gate, negative page borrow semantics, scroll ordering, collision-only drop, and right-platform move-before-`$10` acceleration. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 positive/negative X, drop and right-platform routes.


### Cohort J — B16f lift-platform integration

`MoveLargeLiftPlat` through `ExLiftP` now has five node contracts, all incident TimerControl, call, large/small collision-tail and return relations, plus four feasible lift/rider handoffs. Static review matches frozen motion, fractional carry into Y, unconditional large rider path and nonzero-only small rider path. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 frozen, carry and both rider routes.


### Cohort J — B16g offscreen-bounds integration

`OffscreenBoundsCheck` through `ExScrnBd` now has five node contracts, all incident ID, carry, left/right bound, exception, erase and return relations, plus four feasible handoffs. Static review matches the non-obvious CPY carry propagation through special Hammer/Piranha left-edge arithmetic, cross-page comparisons and all retained right-side object IDs. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 left/right, special-ID and exception routes.


### Cohort J — B16h fireball-enemy collision-core integration

`FireballEnemyCollision` through `ExitFBallEnemy` now has six node contracts, all incident state/frame gates, descending loop, eligibility branches, geometry/hit calls and return relations, plus four feasible box/state handoffs. Static review matches d7/odd-frame suppression, both box offset formulas, five-slot scan, ID and Goomba filters, hit d7 marking without early loop exit and restored scan state. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 hit/miss, filters and multi-slot routes.


### Cohort J — B16i fireball-hit response integration

`BowserIdentities` through `ExHCF` now has eleven node contracts, every incident paired-slot, immunity, Bowser-health, world-table, eligibility, stun, score and return relation, plus six feasible producer-to-consumer handoffs. Static review matches live `$01` restoration, paired-slot substitution only for Bowser, Buzzy immunity, terminal-only Bowser replacement, direct WorldNumber table selection, `$23/$20` state split, Piranha CMP-carry `ADC #$18` result, defeat-state d5 and the Hammer/Goomba/default score modifiers. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 Buzzy, paired-Bowser, nonterminal/terminal Bowser, excluded-ID and Piranha/Hammer/Goomba routes.


### Cohort J — B16j hammer-player collision integration

`PlayerHammerCollision` through `ExPHC` now has three node contracts, every incident frame/timer/offscreen gate, geometry call, collision/latch branch, injury tail and return relation, plus four feasible collision-state handoffs. Static review matches odd-frame execution, combined timer/offscreen zero gate, misc box `slot*4+$24`, post-geometry ObjectOffset reload, one-hit latch/reversal, star-only injury suppression and miss latch clear. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 gated, miss, new-hit, repeated-hit and star-invincible routes.


### Cohort J — B16k power-up collection integration

`HandlePowerUpCollision` through `NoPUp` now has six node contracts, every incident erase/score/palette/routine call, type/status branch, caller edge and return relation, plus six feasible pickup handoffs. Static review matches common erase/modifier-six/PowerUpGrab order, `<2`, `==3` and star type dispatch, 1UP-only score overwrite, small-to-super and super-to-fiery restrictions, fiery palette order and the `$09/$0c` SetPRout tails. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 mushroom, flower, 1UP, star and nonconvertible-status routes.


### Cohort J — B16l player-enemy contact front integration

`PlayerEnemyCollision` through `ExPEC` now has seven node contracts, every incident caller, frame/vertical/offscreen/control/state gate, geometry, pickup/star/response branch, injury/stomp/score child and return relation, plus eight feasible collision/state handoffs. Static review matches even-frame gating, prepared-box use, current-slot reload, miss d0 clear, PowerUpObject dispatch, star defeat bypass, first-contact latch, source hazard order, shell conversion, direction speed and timer-dependent kick score tables. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 gate, miss, pickup, star, direct hazard, stomp and kicked-shell interval routes.


### Cohort J — B16m player injury and death response integration

`ChkForPlayerInjury` through `LInj` now has twelve node contracts, every incident contact/timer caller, signed speed and adjusted-Y branch, relative-facing jump, guarded injury/death/timer route, palette/movement child and return relation, plus seven feasible response handoffs. Static review matches the signed speed split, Bloober threshold adjusted-Y test, StompTimer/InjuryTimer order, facing reversal conditions, second injury guard, downgrade/death state writes, `$0a/$0b` routine selection, timer `$ff`, scroll clear and ObjectOffset restoration. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 stomp, timer suppression, turn/no-turn injury, downgrade and death routes.


### Cohort J — B16n enemy stomp, demotion and score integration

`EnemyStomped` through `ExSFN` now has nine node contracts, every incident injury, ID-class, score/stun/init, shell/demotion, direction, table, caller and return relation, plus seven feasible producer-to-consumer handoffs. Static review matches Spiny injury routing, all four fixed stomp-score classes, movement-direction preservation across stun, d5 defeat, `$fd/$fc` bounce split, ID-nine demotion threshold, low-bit Koopa conversion, hard-mode revival table, signed player-facing direction and all four floatey-number writes. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 fixed class, demotion, shell, normal/hard revival and direction routes.


### Cohort J — B16o enemy-pair collision integration

`SetBitsMask` through `ExTA` now has fifteen node contracts, every incident frame/area/ID/offscreen gate, descending loop, geometry, d7/d5/mask branch, defeat/score/turnaround child and return relation, plus nine feasible pair-state handoffs. Static review matches both unmasked seven-byte masks, source `$01` and stack preservation, candidate descending order, d7 fast path, one-hit latch and miss clear, alternate-state and Hammer Bro handling, shell-chain score ownership, dual turnaround order and the special turnable-ID filters. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 no-candidate, miss, repeated hit, d7 hit, shell-chain and dual-turn routes.


### Cohort J — B16p large and small platform collision integration

`LargePlatformCollision` through `ExSPC` now has seven node contracts, every incident platform runner, timer/state/vertical/offscreen gate, balance partner call, box/geometry/response child, two-box loop and return relation, plus six feasible platform/player handoffs. Static review matches `$ff` versus zero collision initialization, balance partner-first sequencing, saved `$00` platform Y, stack/current-slot restoration, small-platform d1 offscreen gate, Y `$20` threshold and byte-wrapped two-step `$80` box displacement. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 balance partner, large/small top/side/miss and shifted-box routes.


### Cohort J — B16q platform response and rider-position integration

`ProcSPlatCollisions` through `ExPlPos` now has eleven node contracts, every incident platform collision/runner caller, underside/top/side branch, collision flag, impedance call, small-position table, vertical gate and return relation, plus seven feasible platform/player handoffs. Static review matches rising-jump cancellation, top/side thresholds, small-ID counter ownership, borrow-aware side arithmetic, `$80/$00` small height table, death/high-byte gates, 32-pixel height subtraction and motion clear. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 underside, top, left/right side, both small-box offsets, vertical platform and gated rider routes.


### Cohort J — B16r vertical and enemy-box offset integration

`CheckPlayerVertical` through `GetEnemyBoundBoxOfsArg` now has four node contracts, every incident caller, carry branch, fall-through and return relation, plus three feasible vertical/box handoffs. Static review matches the non-obvious clear-carry high-Y exit, `$f0/$d0` thresholds, ObjectOffset fall-through, `slot*4+4` box offset and unindexed low-nibble offscreen comparison. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 vertical and box/offscreen carry routes.


### Cohort J — B16s shared bounding-box and rectangle-core integration

`BoundBoxCtrlData` through `CollisionFound` now has nine node contracts, every incident box-builder/caller, core fall-through, coordinate branch, two-axis loop and return relation, plus six feasible table/box/carry handoffs. Static review matches all 48 bounding offsets, source coordinate write order, player box zero entry, `$06/$07` scratch protocol, horizontal short-circuit, vertical wrap cases, equality boundaries and clear/set carry returns. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 separated, edge-touching, wrapped and two-axis overlap routes.


### Cohort J — B16t bounding-box generation and screen-clip integration

`GetFireballBoundBox` through `NoOfs2` now has sixteen node contracts and every incident object builder, mask/page branch, bounding-box core call, full-offscreen path, right/left clipping and return relation. Static review matches fireball/misc offset transforms, enemy/platform masks, screen-left borrow arithmetic, all-four `$ff` path, right-side `$ff` clipping, and the left-side `$80-$9f` visible versus `$a0-$ff` hidden distinction. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 fireball/misc/enemy/platform, left/right/edge and full-offscreen routes.


### Cohort J — B16u block-buffer query integration

`BlockBufferChk_Enemy` through `RetYC` now has fourteen node contracts and every incident entry, table, query, coordinate-return and return relation. Static review matches enemy/misc/fireball object-offset transforms, `$1b/$1a` adders, 28-entry X/Y tables, wrapped page construction, status-bar row subtraction and low-nibble contact selection. No static shared-C discrepancy was found; entries remain `needs-evidence` pending controlled original-ROM/x86/x64 query routes.


### Cohort J — B16v vine OAM integration

`VineYPosAdder` through `StkLp` now has eight node contracts and all incident OAM stack, tile, attribute, hide-loop and return relations. Static review matches two stack offsets, six-sprite Y stack, alternating X/flip attributes, `$e0` top cap, `$e1` leaves and `$f8` hide threshold. No static shared-C discrepancy was found; entries remain `needs-evidence` pending controlled original-ROM/x86/x64 routes.

### Cohort K — K1 hammer OAM pose integration

`FirstSprXPos` through `NoHOffscr` now has twelve node contracts, every incident timer/state pose-selection, render/offscreen, helper-call and return relation, plus seven feasible pose-table-to-OAM handoffs. Static review matches all four X/Y/tile/attribute pose rows, the TimerControl and masked-state force-zero conditions, FrameCounter d3-d2 selection, source chained additions for the second record, and the `Misc_OffscreenBits & $fc` state-clear/two-Y-hide tail. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 forced-pose, animated-pose, visible and offscreen routes.

### Cohort K — K2 flagpole graphics and OAM dump integration

`FlagpoleScoreNumTiles` through `ExitDumpSpr` now has nine node contracts, the local flagpole caller, score-row, offscreen and return relations, plus one feasible score-table handoff. Static review matches the three fixed flag sprites, score-row `$00/$01` setup and tile-pair indexing, d1-d3 offscreen hide condition, and all six/four/three/two dump fall-through stores in descending OAM order. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 flag-visible, score-visible and d1-d3-offscreen routes.

### Cohort K — K3 large-platform OAM integration

`DrawLargePlatform` through `ExDLPl` now has eleven node contracts and all local stack, tile, area/hard-mode, cloud, per-column and full-offscreen control relations. Static review found one confirmed shared-C discrepancy: ROM line 13366 supplies `Enemy_Y_Position,x` to `DumpFourSpr`, while `mysmb_objects_draw_large_platform` reads `MYSMB_SMALL_PLATFORM_REL_Y`. `DrawLargePlatform` is therefore `mismatch`; H9 is the ordered, unnumbered minimal repair candidate. The ten downstream nodes remain `needs-evidence`; controlled original-ROM/x86/x64 castle, hard-mode, cloud and six-column-offscreen routes are still required.

### Cohort K — K4 jumping-coin and floatey-number OAM integration

`DrawFloateyNumber_Coin` through `ExJCGfx` now has five node contracts, every local state/frame, helper, branch and return relation, plus the feasible jumping-tile table handoff. Static review matches the `>= $02` state split, even-frame rise, equal floatey Ys, frame d2-d1 tile selection, vertical-flip attribute and ObjectOffset restoration. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 rising, floatey and four animation-phase routes.

### Cohort K — K5 power-up OAM integration

`PowerUpGfxTable` through `PUpOfs` now has six node contracts, every local row-loop, type, flip, tail-jump and return relation, plus two feasible table handoffs. Static review matches all four tile sets, base attributes, two-row scratch protocol, flower/star frame palettes, star-only lower palette update, both right-side flips and the shared offscreen tail. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 mushroom, flower, star, 1UP and offscreen routes.

### Cohort K — K6 enemy graphics-table integration

`EnemyGraphicsTable` through `JumpspringFrameOffsets` now has five table contracts and five feasible consumer handoffs. Static review matches the ordered tile rows, 27 offsets, 27 attributes, two animation masks and five jumpspring offsets. The C arrays deliberately preserve the source tables' contiguous indexed-overrun behavior rather than adding a clamp. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 normal-actor and jumpspring table routes.

### Cohort K — K7 enemy graphics front-dispatch integration

`EnemyGfxHandler` through `SBwsrGfxOfs` now has eight node contracts and every immediate actor selection, branch and return relation. Static review matches piranha's upward/timer early return, retainer code `$15`, cannon bullet Y/priority/state rewrite, jumpspring frame code, descending-Podoboo vertical flip, and Bowser front/rear code override. The shared C dispatch deliberately delegates the final specialized rendering to the corresponding actor owners. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 piranha, retainer, cannon, spring, Podoboo and both Bowser-half routes.

### Cohort K — K8 normal-enemy, Bowser, Spiny, Lakitu and shell graphics integration

`CheckForGoomba` through `CheckForDefdGoomba` now has fifteen node contracts and all local Goomba animation, Bowser front/rear, Spiny egg, Lakitu alternate-frame and shell-state control relations. Static review matches the Goomba d5/timer/d3 gate, Bowser mouth/feet frames and defeated flip/Y path, Spiny egg rewrite, Lakitu timer threshold, Buzzy versus Koopa shell selections and Goomba defeat decrement. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 normal, defeated, Bowser, egg, Lakitu and shell routes.

### Cohort K — K9 enemy animation and row-draw integration

`CheckForHammerBro` through `DrawEnemyObject` now has seven node contracts and all local Hammer Bro, Bloober/Cheep, animation, defeated-state and three-row control relations. Static review matches Hammer Bro d3 handling, interval gates and Bloober Y adjustment, retainer WorldNumber path, timing masks, d7/d5/timer animation suppression, defeated flip setup and the ordered three-row writes. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 Hammer Bro, Cheep, Bloober, retainer, defeated and Bullet Bill routes.

### Cohort K — K10 enemy OAM flip, mirror and offscreen integration

`SkipToOffScrChk` through `AllRowC` now has seventeen node contracts and every local vertical-flip, symmetry, Lakitu/jumpspring and d2/d3/d5/d6/d7 offscreen relation. Static review matches row-pair exchanges, egg and shell attribute transforms, Lakitu timer branches, spring row attributes, ordered column/row hiding and the Podoboo/high-Y erase exception. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 flip, mirror, Lakitu, spring, every offscreen-bit and erase route.

### Cohort K — K11 bouncing-block OAM integration

`DefaultBlockObjTiles` through `ExDBlk` now has ten node contracts, every local draw-row, replacement, area-palette, column-hide and return relation, plus one feasible default-tile handoff. Static review matches the two source tile pairs, non-ground lineless replacement, used-block palette/flip bytes, d2 right and d3 left column hiding, and the shared two-row f8 helper. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 normal/used, ground/non-ground and each offscreen-column route.

### Cohort K — K12 brick-chunk OAM integration

`DrawBrickChunks` through `ExBCDr` now has four node contracts and every local mode, helper, phase, offscreen and return relation. Static review matches end-level versus normal tile/palette selection, frame d3-d2 attribute phase, carry-sensitive reflected X arithmetic, left/top hide order and wrapped-left right-column suppression. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 normal/end-level, phase, offscreen and wrapped-left routes.

### Cohort K — K13 fireball, firebar and explosion OAM integration

`DrawFireball` through `KillFireBall` now has seven node contracts, every local fall-through, frame phase, explosion state and return relation, plus the feasible explosion-tile handoff. Static review matches fireball-to-firebar fall-through, d2/d3 phase selection, pre-increment explosion indexing, three-frame termination, four-sprite offsets and attributes. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 fireball, firebar phase, explosion frames and termination routes.

### Cohort K — K14 small-platform and bubble OAM integration

`DrawSmallPlatform` through `ExDBub` now has eight node contracts and all local helper, status-bar, offscreen, bubble-gate and return relations. Static review matches the six-sprite rows, top/bottom wrapped clipping, d3/d2/d1 column hides, and the exact Player_Y_HighPos-one plus bubble d3 gate. No static shared-C discrepancy was found. Entries remain `needs-evidence` pending controlled original-ROM/x86/x64 platform clipping/columns and bubble visible/hidden routes.
## K15 — player graphics data-table audit

- Source range: `PlayerGfxTblOffsets` through `SwimKickTileNum` (`SMBDIS.ASM` lines 14418–14459).
- Node-semantics result: three labels moved from `unclassified` to `needs-evidence`: `PlayerGfxTblOffsets`, `PlayerGraphicsTable`, and `SwimKickTileNum`. The current owner-local PRG bindings preserve their source offsets and consumers, but controlled original-ROM/x86/x64 routes are still required before any `exact` promotion.
- Independent material integration result: recorded `PlayerGfxTblOffsets → PlayerGfxHandler`, `PlayerGraphicsTable → DrawPlayerLoop`, and `SwimKickTileNum → BigKTS` as `needs-evidence`; no discrepancy is claimed from this static pass.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K16 — player graphics handler control-chain audit

- Source range: `PlayerGfxHandler` through `NPROffscr` (`SMBDIS.ASM` lines 14460–14557).
- Node-semantics result: thirteen labels moved from `unclassified` to `needs-evidence`: `PlayerGfxHandler`, `CntPl`, `SwimKT`, `BigKTS`, `ExPGH`, `FindPlayerAction`, `DoChangeSize`, `PlayerKilled`, `PlayerGfxProcessing`, `SUpdR`, `PlayerOffscreenChk`, `PROfsLoop`, and `NPROffscr`. The shared owner preserves the static dispatch, throw-row and OAM-mask structure; controlled routes are required before any `exact` promotion.
- Independent control integration result: 35 outgoing relations received `needs-evidence` contracts, including injury exits, graphics-mode dispatch, swim-kick selection, tail transfers, common render calls and the four-row offscreen loop. No discrepancy is claimed from this static pass.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K17 — intermediate-player and shared player-row rendering audit

- Source range: `IntermediatePlayerData` through `DrawPlayerLoop` (`SMBDIS.ASM` lines 14561–14608).
- Node-semantics result: five labels moved from `unclassified` to `needs-evidence`: `IntermediatePlayerData`, `DrawPlayer_Intermediate`, `PIntLoop`, `RenderPlayerSub`, and `DrawPlayerLoop`.
- Independent integration result: 10 outgoing control relations and the feasible `IntermediatePlayerData → DrawPlayer_Intermediate` material edge received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K18 — player-action graphics-selection audit

- Source range: `ProcessPlayerAction` through `ExAnimC` (`SMBDIS.ASM` lines 14610–14703).
- Node-semantics result: thirteen labels moved from `unclassified` to `needs-evidence`: state dispatch, ground-action dispatch, non-animated selection, falling/walk/climb/swim action paths and the common animation control sequence.
- Independent control integration result: 33 outgoing relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 route evidence remains required for every action family and timer boundary.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K19 — player size-change, offset and attribute audit

- Source range: `GetGfxOffsetAdder` through `ExPlyrAt` (`SMBDIS.ASM` lines 14705–14781).
- Node-semantics result: thirteen labels moved from `unclassified` to `needs-evidence`, covering size adjustment, growth/shrink frame selection, graphics-table offset construction, and death/crouch/intermediate OAM attribute correction.
- Independent integration result: 25 outgoing control relations and the feasible `ChangeSizeOffsetAdder → HandleChangeSize` material edge received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K20 — relative-object-position audit

- Source range: `RelativePlayerPosition` through `GetObjRelativePosition` (`SMBDIS.ASM` lines 14786–14841).
- Node-semantics result: nine labels moved from `unclassified` to `needs-evidence`: all player/bubble/fireball/misc/enemy/block position wrappers and their common helpers.
- Independent integration result: 42 outgoing control relations and the feasible `ObjOffsetData → GetProperObjOffset` material edge received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K21 — offscreen-bit entry and combination audit

- Source range: `GetPlayerOffscreenBits` through `RunOffscrBitsSubs` (`SMBDIS.ASM` lines 14846–14918).
- Node-semantics result: eleven labels moved from `unclassified` to `needs-evidence`, covering all object-family wrapper offsets, common X/Y-nibble assembly and result write-back.
- Independent integration result: 42 outgoing control relations received `needs-evidence` contracts. `ObjOffsetData` retains its previously-recorded feasible material edge; static review found no discrepancy. Controlled original-ROM/x86/x64 routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K22 — X/Y offscreen-bit algorithm audit

- Source range: `XOffscreenBitsData` through `ExDivPD` (`SMBDIS.ASM` lines 14927–15016).
- Node-semantics result: sixteen labels moved from `unclassified` to `needs-evidence`, covering X/Y tables, boundary loops and the shared pixel-difference partition helper.
- Independent integration result: 26 outgoing control relations plus five feasible table-to-consumer material edges received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 left/right/top/bottom and partition-boundary routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K23 — shared sprite-row OAM writer audit

- Source range: `DrawSpriteObject` through `SetHFAt` (`SMBDIS.ASM` lines 15025–15061).
- Node-semantics result: three labels moved from `unclassified` to `needs-evidence`; the shared writer's tile order, horizontal-flip attribute contribution, coordinates and caller-index advances have distinct contracts.
- Independent integration result: 4 outgoing control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 flipped and unflipped routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K24 — SoundEngine main, pause and dispatch audit

- Source range: `SoundEngine` through `StrWave` (`SMBDIS.ASM` lines 15070–15151).
- Node-semantics result: thirteen labels moved from `unclassified` to `needs-evidence`, covering title mute, APU initialization, pause state, square-tone timing, SFX/music dispatch, queue clearing and DAC tail behavior.
- Independent integration result: 32 outgoing control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 title/pause/normal/DAC routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K25 — audio register and frequency primitive audit

- Source range: `Dump_Squ1_Regs` through `SetFreq_Tri` (`SMBDIS.ASM` lines 15155–15190).
- Node-semantics result: nine labels moved from `unclassified` to `needs-evidence`, covering channel-specific control write order, shared frequency lookup and zero-frequency suppression.
- Independent integration result: 29 outgoing control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 channel and zero/nonzero lookup routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K26 — square-one basic SFX audit

- Source range: `SwimStompEnvelopeData` through `DecJpFPS` (`SMBDIS.ASM` lines 15194–15253).
- Node-semantics result: fourteen labels moved from `unclassified` to `needs-evidence`, covering flagpole, small/big jump, bump and fireball-throw setup and timing continuations.
- Independent integration result: 26 outgoing control relations and the feasible `SwimStompEnvelopeData → ContinueSwimStomp` material edge received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 SFX timing routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K27 — square-one queue, swim, smack and pipe SFX audit

- Source range: `Square1SfxHandler` through `NoPDwnL` (`SMBDIS.ASM` lines 15256–15365).
- Node-semantics result: sixteen labels moved from `unclassified` to `needs-evidence`, covering queue priority scan, buffer continuation, swim/stomp, smack, pipe/injury and terminal channel reset.
- Independent integration result: 47 outgoing control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 priority and timing routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K28 — square-two tables, effects and queue audit

- Source range: `ExtraLifeFreqData` through `JumpToDecLength2` (`SMBDIS.ASM` lines 15369–15502).
- Node-semantics result: twenty-three labels moved from `unclassified` to `needs-evidence`, covering square-two effect tables, coin/timer, blast, power-up, terminal reset, one-up protection and queue/buffer priority dispatch.
- Independent integration result: 49 outgoing control relations plus three feasible table-to-consumer material edges received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 timing and priority routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K29 — square-two Bowser, one-up and grow/vine audit

- Source range: `PlayBowserFall` through `StopGrowItems` (`SMBDIS.ASM` lines 15504–15565).
- Node-semantics result: thirteen labels moved from `unclassified` to `needs-evidence`, covering Bowser tone transition, one-up divisibility scan and grow/vine secondary-counter lifecycle.
- Independent integration result: 21 outgoing control relations received `needs-evidence` contracts. Existing feasible frequency-table edges remain linked; static review found no discrepancy.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K30 — noise SFX audit

- Source range: `BrickShatterFreqData` through `ContinueBowserFlame` (`SMBDIS.ASM` lines 15569–15628).
- Node-semantics result: eleven labels moved from `unclassified` to `needs-evidence`, covering brick/Bowser-flame queue handling, noise APU writes, length decrement and terminal mute.
- Independent integration result: 18 outgoing control relations plus three feasible noise-table material edges received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 noise timing routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K31 — music dispatch and header-load audit

- Source range: `ContinueMusic` through `LoadHeader` (`SMBDIS.ASM` lines 15632–15718).
- Node-semantics result: eleven labels moved from `unclassified` to `needs-evidence`, covering queue priority, death-event SFX stops, time-running-out length selection, ground-loop counter wrap, bit-mask header selection and six-byte header initialization.
- Independent integration result: 25 outgoing control relations received `needs-evidence` contracts, including each event/area branch, SFX call, structural fall-through, loop-back and header-to-square-two transfer. Static review found no discrepancy; controlled original-ROM/x86/x64 event, area, death, time-running-out and ground-loop routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K32 — square-two music stream audit

- Source range: `HandleSquare2Music` through `NoDecEnv1` (`SMBDIS.ASM` lines 15720–15787).
- Node-semantics result: eleven labels moved from `unclassified` to `needs-evidence`, covering stream counter/fetch classification, terminator loops and reset, length/note paths, SFX channel ownership and envelope tail behavior.
- Independent integration result: 33 outgoing and return control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 note, rest, length, terminator, loopback, SFX-owned and envelope routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K33 — square-one music stream audit

- Source range: `HandleSquare1Music` through `DoAltLoad` (`SMBDIS.ASM` lines 15788–15834).
- Node-semantics result: eight labels moved from `unclassified` to `needs-evidence`, covering absent-stream skip, null-byte controls, alternate length encoding, SFX ownership, death/D4 envelope behavior and alternate high control.
- Independent integration result: 28 outgoing and return control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K34 — triangle/noise music and length-helper audit

- Source range: `HandleTriangleMusic` through `ProcessLengthData` (`SMBDIS.ASM` lines 15835–15947).
- Node-semantics result: sixteen labels moved from `unclassified` to `needs-evidence`, covering triangle stream/control selection, noise stream loopback and beats, and both shared length transforms.
- Independent integration result: 41 outgoing and return control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K35 — music control and envelope selector audit

- Source range: `LoadControlRegs` through `LoadWaterEventMusEnvData` (`SMBDIS.ASM` lines 15951–15981).
- Node-semantics result: seven labels moved from `unclassified` to `needs-evidence`, covering end-castle, water/event and usual area control/envelope selection.
- Independent integration result: 9 control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K36 — music header table audit

- Source range: `MusicHeaderData` through `DeathMusHdr` (`SMBDIS.ASM` lines 15989–16048).
- Node-semantics result: 23 data labels moved from `unclassified` to `needs-evidence`; C reads owner-local PRG offsets rather than reproducing header data.
- Independent material integration result: 23 selected-header-to-`LoadHeader` edges received `needs-evidence` contracts. Static review found no discrepancy; controlled selector/header routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K37 — labeled music stream data audit

- Source range: `Star_CloudMData` through `VictoryMusData` (`SMBDIS.ASM` lines 16077–16313).
- Node-semantics result: 21 labeled music stream data nodes moved from `unclassified` to `needs-evidence`; C retains source PRG bytes behind header-selected CPU pointers rather than re-encoding streams.
- Material stream-consumer relations remain coupled to their header and channel offset routes and require controlled execution evidence.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K38 — music lookup and envelope table audit

- Source range: `FreqRegLookupTbl` through `WaterEventMusEnvData` (`SMBDIS.ASM` lines 16326–16355).
- Node-semantics result: five table labels moved from `unclassified` to `needs-evidence`.
- Independent material integration result: 5 table-reader edges received `needs-evidence` contracts. Static review found no discrepancy; controlled routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K39 — early NMI/title-demo audit

- Source range: `SkipMainOper`, `WSelectBufferTemplate` and `RunDemo` (`SMBDIS.ASM` lines 868, 993, 1049–1052).
- Node-semantics result: three labels moved from `unclassified` to `needs-evidence`.
- Independent integration result: 4 RunDemo call/return/reset relations and one world-select-template material edge received `needs-evidence` contracts. Static review found no discrepancy; controlled title routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K40 — DoNothing residual leaf audit

- Source range: `DoNothing1` through `DoNothing2` (`SMBDIS.ASM` lines 3052–3055).
- Node-semantics result: two labels moved from `unclassified` to `needs-evidence`; current secondary setup preserves the residual `$06c9 = $ff` write and return behavior.
- Independent integration result: 3 fall-through/return relations received `needs-evidence` contracts. Static review found no discrepancy; controlled startup route remains required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K41 — jumpspring tail audit

- Source range: `PosJSpr` through `ExJSpring` (`SMBDIS.ASM` lines 6669–6698).
- Node-semantics result: three labels moved from `unclassified` to `needs-evidence`, covering frame position, one-press bounce force and terminal animation lifecycle.
- Independent integration result: 6 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K42 — FireBulletBill node audit

- Source range: `FireBulletBill` (`SMBDIS.ASM` lines 8767–8772).
- Node-semantics result: one label moved from `unclassified` to `needs-evidence`; existing incident edge contracts remain applicable. Static review found no discrepancy; controlled fire route remains required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K43 — StarFlagExit2 node audit

- Source range: `StarFlagExit2` (`SMBDIS.ASM` line 10596).
- Node-semantics result: one label moved from `unclassified` to `needs-evidence`; existing incident edge contracts remain applicable. Static review found no discrepancy; controlled flag route remains required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K44 — player/enemy collision table audit

- Source range: collision speed, point and revival tables (`SMBDIS.ASM` lines 11309–11521).
- Node-semantics result: six labels moved from `unclassified` to `needs-evidence`.
- Independent material integration result: 6 table-consumer edges received `needs-evidence` contracts. Static review found no discrepancy; controlled collision routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K45 — ExitProcessEColl node audit

- Source range: `ExitProcessEColl` (`SMBDIS.ASM` line 11680).
- Node-semantics result: one label moved from `unclassified` to `needs-evidence`; existing incident edge contracts remain applicable. Static review found no discrepancy; controlled pair-collision routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K46 — player background collision entry audit

- Source range: `PlayerBGUpperExtent` through `HeadChk` (`SMBDIS.ASM` lines 11924–11971).
- Node-semantics result: nine labels moved from `unclassified` to `needs-evidence`, covering guards, falling/swimming state, screen gate and probe-base selection.
- Independent integration result: 18 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled collision routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K47 — player head-probe audit

- Source range: `HeadChk` through `DoFootCheck` (`SMBDIS.ASM` lines 11971–12000).
- Node-semantics result: four labels moved from `unclassified` to `needs-evidence`, covering head/coin/solid handling and vertical-speed reset.
- Independent integration result: 20 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled head routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K48 — player feet and landing audit

- Source range: `DoFootCheck` through `InitSteP` (`SMBDIS.ASM` lines 12000–12051).
- Node-semantics result: six labels moved from `unclassified` to `needs-evidence`, covering dual feet probes, coin/axe/invisible/jumpspring paths and landing resets.
- Independent integration result: 33 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled feet routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K49 — player side-probe first-half audit

- Source range: `DoPlayerSideCheck` through `ContSChk` (`SMBDIS.ASM` lines 12052–12094).
- Node-semantics result: six labels moved from `unclassified` to `needs-evidence`, covering two-half probes, bounds, climb/invisible and coin/jumpspring gates.
- Independent integration result: 28 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled side routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K50 — player side pipe and impede audit

- Source range: `ContSChk` through `AreaChangeTimerData` (`SMBDIS.ASM` lines 12094–12147).
- Node-semantics result: nine labels moved from `unclassified` to `needs-evidence`, covering side pipe entry, timer choice and movement impedance.
- Independent integration result: 24 control relations plus one timer-table material edge received `needs-evidence` contracts. Static review found no discrepancy; controlled side-pipe routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K51 — coin, axe and climbing audit

- Source range: `HandleCoinMetatile` through `MtchF` (`SMBDIS.ASM` lines 12147–12217).
- Node-semantics result: thirteen labels moved from `unclassified` to `needs-evidence`, covering coin/axe erase tails, vine/flag entry and flag score selection.
- Independent integration result: 20 relations plus three climb/flag table edges received `needs-evidence` contracts. Static review found no discrepancy; controlled routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K52 — climbing and jumpspring metatile audit

- Source range: `RunFR` through `ChkJumpspringMetatiles` (`SMBDIS.ASM` lines 12218–12286).
- Node-semantics result: ten labels moved from `unclassified` to `needs-evidence`, covering vine alignment, hidden blocks and landing-spring setup.
- Independent integration result: 14 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K53 — vertical pipe and movement impedance audit

- Source range: `HandlePipeEntry` through `ExIPM` (`SMBDIS.ASM` lines 12295–12372).
- Node-semantics result: eight labels moved from `unclassified` to `needs-evidence`, covering foot-gated pipe/warp transition and side-aware motion stop.
- Independent integration result: 16 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K54 — metatile predicate audit

- Source range: `SolidMTileUpperExt` through `ExEBG` (`SMBDIS.ASM` lines 12380–12415).
- Node-semantics result: eight labels moved from `unclassified` to `needs-evidence`, covering solid/climb/coin predicates and attribute grouping.
- Independent integration result: 7 local relations plus two threshold-table edges received `needs-evidence` contracts. Static review found no discrepancy; controlled predicate routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K55 — enemy background collision entry audit

- Source range: `EnemyBGCStateData` through `NoEToBGCollision` (`SMBDIS.ASM` lines 12420–12461).
- Node-semantics result: eight labels moved from `unclassified` to `needs-evidence`, covering ID dispatch, under-enemy eligibility and no-ground path.
- Independent integration result: 20 relations plus two state/speed table edges received `needs-evidence` contracts. Static review found no discrepancy; controlled enemy terrain routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K56 — enemy background landing and stun audit

- Source range: `HandleEToBGCollision` through `ChkLandedEnemyState` (`SMBDIS.ASM` lines 12461–12537).
- Node-semantics result: thirteen labels moved from `unclassified` to `needs-evidence`, covering block-hit stun, landing alignment and state dispatch.
- Independent integration result: 35 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled enemy terrain routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K57 — jumpspring predicate terminals audit

- Source range: `JSFnd` through `NoJSFnd` (`SMBDIS.ASM` lines 12292–12293).
- Node-semantics result: two labels moved from `unclassified` to `needs-evidence`.
- Independent integration result: 4 predicate relations received `needs-evidence` contracts. Static review found no discrepancy; controlled routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K58 — enemy landing state audit

- Source range: `SetForStn` through `SetD6Ste` (`SMBDIS.ASM` lines 12552–12611).
- Node-semantics result: eleven labels moved from `unclassified` to `needs-evidence`, covering landing state transitions, player-facing and red-koopa exception.
- Independent integration result: 25 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K59 — enemy side and terrain chain audit

- Source range: `DoEnemySideCheck` through `NSFnd` (`SMBDIS.ASM` lines 12617–12747).
- Node-semantics result: nineteen labels moved from `unclassified` to `needs-evidence`, covering directional side probes, bump/Hammer Bro dispatch, enemy/player subtraction, landing, jump terrain, under-probe and non-solid predicates.
- Independent integration result: 51 control relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 side-probe, jumping and Hammer Bro routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K60 — fireball background collision audit

- Source range: `FireballBGCollision` through `InitFireballExplode` (`SMBDIS.ASM` lines 12751–12777).
- Node-semantics result: three labels moved from `unclassified` to `needs-evidence`, covering the status-bar/bottom-probe gate, bounce assignment and explosion state/sound handoff.
- Independent integration result: 9 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 bounce, non-solid and explosion routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K61 — enemy OAM row leaf audit

- Source range: `ExEGHandler` through `MoveESprColOffscreen` (`SMBDIS.ASM` lines 14085–14110).
- Node-semantics result: five labels moved from `unclassified` to `needs-evidence`, covering two-tile row loading/drawing and row/column OAM hiding leaves.
- Independent integration result: 5 relations received `needs-evidence` contracts. Static review found no discrepancy; controlled original-ROM/x86/x64 normal-enemy OAM routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K62 — terminal noise-envelope data audit

- Source range: `BowserFlameEnvData` and `BrickShatterEnvData` (`SMBDIS.ASM` lines 16362–16370).
- Node-semantics result: both final unclassified labels moved to `needs-evidence`; their existing material producer-to-consumer records were strengthened with index and handoff contracts.
- No control-edge classification was inferred from table endpoint status. Static review found no discrepancy; controlled original-ROM/x86/x64 sound routes remain required.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.
## K63 — residual control-edge integration audit

- Scope: all 87 remaining extracted, unclassified control relations: one vector edge and source bands 0/vector: 1, 0xxx: 5, 12xxx: 6, 14xxx: 2, 2xxx: 4, 3xxx: 18, 5xxx: 51.
- Integration result: every edge is now independently mapped to its two named shared-C endpoint counterparts with a type-specific branch, fall-through, call, return, vector or JumpEngine-dispatch ordering contract.
- Static review found no newly confirmed discrepancy. These relations are `needs-evidence`, not `exact`, until their controlled original-ROM/x86/x64 route records cover the stated predicates and continuations.
- No production source, platform adapter, ROM, executable, trace, or generated artifact changed.

### T53 S1 dispatch-route result

`OperModeExecutionTree` is now current-equivalence **exact**. Static review
established that the portable NMI-prefix callees do not write `OperMode` or
`OperMode_Task`, so the C selector snapshot is the same value loaded by the
ROM at the original dispatch point. A bounded owner-ROM route then exercised
all four inline `JumpEngine` vector targets and both post-child continuations.
For x86 and x64, every fixture had zero non-scratch RAM and visible-output
differences. The same current binaries also passed paired 600-frame idle and
start/action routes with exact work RAM and output. This establishes the
selector node only; its incident control relations, pause-tail route and the
separate `ScreenOff` transaction mismatch retain their individual statuses.

### T53 S1 pause/sprite-root result

Fourteen further S1 labels are current-equivalence **exact**: `PauseSkip`,
`Sprite0Clr`, `Sprite0Hit`, `HBlankDelay`, `SkipMainOper`, the six
`SpriteShuffler` labels, and the three offscreen-OAM labels. A controlled
owner-ROM start/move/pause/resume route reached each label, including the
shuffle store path, and compared zero work-RAM, selected NMI-state and visible
output differences for both x86 and x64 across 600 frames. Static review
separately establishes the shared-C timer/LFSR gate, sprite-zero OAM phase,
abstracted scanline split, NMI tail, shuffle arithmetic and OAM-loop order.
Only `InitBuffer` remains pending in this S1 chain; `ScreenOff` remains the
separate order mismatch. Individual control-edge dispositions remain open.

`InitBuffer` is also current-equivalence **exact**. It was reached on every
sample of that route and its selector-six buffer choice, header/offset clear,
and address-selector reset match the shared C transaction. Its successor
relationship to display restoration remains distinct from the preceding
`ScreenOff` order mismatch.

### T53 S1 internal-edge result

All 75 S1 internal control relations now have a current disposition: 74 are
**exact** and `control-00076` is **infeasible**. The 38 newly exact relations
are the NMI display predicates, pause/timer-to-LFSR handoff, sprite-zero
synchronization and tail, shuffle loop, OAM loop and their source call/return
pairs. Their edge identities remain separate in the registry, while sharing
one source-order audit and the bounded dispatch plus pause/sprite route
matrix. The four `ScreenOff` transaction-order mismatches are cross-boundary
relations to `InitScroll`/`UpdateScreen`, so they remain open repair evidence
and are not part of the S1 internal-edge result.

### T53 S4 victory-chain result

The 22 labels from `VictoryMode` through `EndExitTwo` and their 65 incident executable control relations are current-exact. Static source-order comparison found no ROM/C difference. Fifteen controlled original-ROM/x86/x64 fixtures are exact over eight recorded frames after a 60-frame warmup, with byte-identical x86/x64 records. The current x64 bowser, endgame-object, mode and victory-message checks pass. The live registry is now **98 exact nodes**, **211 exact control relations**, **18 infeasible raw relations**, **4,324 feasible control relations**, and **zero mismatches**; historical conformance remains **1,992 / 1,992**.

### T53 S5 floatey-number-chain result

The ten labels from `FloateyNumTileData` through `SetupNumSpr`, 25 incident executable control relations, and `material-00005` are current-exact. A source-order review found and repaired the `ChkTallEnemy -> GetAltOffset` OAM-group branch in the shared game owner; the re-audit found no remaining scoped difference. Three controlled original-ROM fixtures—one-up, timer-zero and numeric-alt—used a 60-frame warmup and eight captured frames each. Current x86 and x64 match the ROM in work RAM `$0200-$07ff` excluding `$0778/$0779`, CIRAM, palette, OAM, PPU scalars and audio, and their native records are byte-identical. The focused OAM regression passes; DOS16 links the same C90 owner; platform-purity passes. The live registry is **105 exact nodes**, **231 exact feasible control relations**, **6 exact material relations**, and **zero mismatches**; historical conformance remains **1,992 / 1,992**.
### T54 S2 status and intermediate result

`WriteTopStatusLine`, `WriteBottomStatusLine`, `DisplayTimeUp`, `NoTimeUp`,
`DisplayIntermediate`, `PlayerInter`, `OutputInter`, `GameOverInter` and
`NoInter` are current-equivalence exact. The audit repaired the `GameOverInter`
mode-task continuation: original `IncModeTask_B` increments the live task byte,
where the prior C code set it to two. Seven controlled task-2/3/4/6 routes now
match original ROM and current x86/x64 output under the established CPU ABI
exclusions. Its 25 source-owned control relations are exact. The live registry
is **128 exact nodes**, **277 exact feasible control relations**, **10 exact
material relations**, and **zero mismatches**; historical conformance remains
**1,992 / 1,992**.


### T55 S7 joypad serial-read result

`ReadJoypads`, `ReadPortBits`, `PortLoop` and `Save8Bits` are now current-equivalence **exact**. The audit repaired the pre-dispatch physical `$2000` packet write in shared `frame_root.c`; the ROM writes it before the joypad caller continuation, while the NMI tail later restores the saved d7-enabled control value. The bounded 120-frame original-ROM/x86/x64 route reaches both port passes, every serial-loop turn and both Select/Start debounce outcomes, with zero differences in the four joypad RAM bytes and all seven PPU scalars. The live registry is **225 exact nodes**, **458 exact feasible control relations**, **18 infeasible raw relations**, **4,324 feasible control relations**, and zero mismatches; historical conformance remains **1,992 / 1,992**.


## T55 S8 closure

The current VRAM/PPU chain is exact for `WriteBufferToScreen`, `SetupWrites`, `GetLength`, `OutputToVRAM`, `RepeatByte`, `UpdateScreen`, `InitScroll`, and `WritePPUReg1`. The repaired C owner advances the `$00/$01` packet pointer after each ROM-format packet and commits the packet header control state at the original write point. The repeat and vertical fixture addresses are identical between the original-ROM recorder and native recorder.

## T55 closure

T55 closes its Cohort C bootstrap slice with 67 exact nodes, 137 exact feasible controls, five source-infeasible controls and 25 exact material edges. The final cross-chain evidence combines renderer output, both-port joypad/debounce and VRAM/scroll/PPU-control routes.

### T57 S4 loopback and area-pointer result

`AreaDataOfsLoopback`, `LoadAreaPointer`, `GetAreaType`, `FindAreaPointer`,
`GetAreaDataAddrs`, `StoreFore` and `StoreStyle` are current-equivalence
exact. The original table belongs to the shared enemy loop owner, not the area
pointer owner: all eleven bytes are selected by 96 controlled loop routes and
22 routes execute `ExecGameLoopback`. The companion 71-route pointer matrix
consumes all 188 pointer/header table bytes and both header branch families.
Original ROM, x86 and x64 have zero persistent work-RAM differences in both
matrices and the native records are byte-identical. Focused x86/x64 smokes,
platform-purity and the shared OpenNT DOS16 link pass. The live registry is
415 exact nodes, 888 exact feasible controls, 18 infeasible raw controls and
zero mismatches; historical conformance remains 1,992 / 1,992.

### T57 S5 pointer-table result

The 16 source table labels from `WorldAddrOffsets` through
`AreaDataAddrHigh` and their six table-to-consumer relations are
current-equivalence exact. Generated owner-local source matches all 188
original table bytes, and the 71-route ROM/current matrix consumes every byte
through the translated pointer owner with zero persistent work-RAM differences
and byte-identical x86/x64 results. Pointer/header smokes, platform-purity and
the shared OpenNT DOS16 link pass. The live registry is 431 exact nodes, 888
exact feasible controls, 18 infeasible raw controls and zero mismatches;
historical conformance remains 1,992 / 1,992.


### T57 S6 enemy-area stream result

The 34 labels from `E_CastleArea1` through `E_WaterArea3` and `material-00075` are current-exact. The static audit bound all 1,087 stream bytes, pointer targets, `$ff` terminators and the `E_GroundArea9` / `E_GroundArea10` alias to the generated local PRG and shared stream decoder. All 80 controlled original-ROM/current x86/x64 stream fixtures enter `ProcessEnemyData` at `$c144`, cover record/page/row/suppression/group/fallback paths, have zero compared persistent-state differences, and produce byte-identical x86/x64 records. The registry is **465 exact nodes**, **1,527 nodes needing evidence**, **888 exact feasible controls**, 18 infeasible raw controls and zero mismatches; historical conformance remains **1,992 / 1,992**.


### T57 S7 area-object stream result

The 34 labels from `L_CastleArea1` through `L_WaterArea3` are current-exact.
Static audit binds all 3,372 level-object stream bytes, headers, `$fd` terminators
and adjacent-label boundaries to the generated local PRG and shared area decoder.
The complete 36-route original-ROM/current x86/x64 scene matrix consumes every
stream byte over 3,955 samples and matches persistent state plus visible output;
x86 and x64 records are byte-identical. The registry is **499 exact nodes**,
**1,493 nodes needing evidence**, **888 exact feasible controls**, 18 infeasible
raw controls and zero mismatches; historical conformance remains **1,992 / 1,992**.

### T57 Cohort-D cross-chain closure

All 146 Cohort-D labels are current-exact. The cross-chain matrix combines the
object-rendering, block-buffer, pointer/header, enemy-stream and area-stream
owners. Per native width it executes 36 original-ROM/current scene routes,
consumes every one of the 3,372 level-stream bytes and compares 4,772 samples
of persistent state plus full visible output. It also executes 71
pointer/terminal routes against their valid persistent-RAM oracle. The 107
native records produced by x86 and x64 are byte-identical. Focused tests,
platform-purity and the shared DOS16 link pass. The registry remains **499
exact nodes**, **1,493 needing evidence**, **888 exact feasible controls**,
18 infeasible raw controls and zero mismatches; historical conformance remains
**1,992 / 1,992**.

### T58 S1 dispatcher and engine-tail result

All eleven labels from `GameMode` through `ExitEng` are current-equivalence exact. The static contract locks the four-vector selector, controller-byte selection and post-child task reload, GameEngine call order, six-slot actor loop, two block slots, palette/music predicate, input partition and parser tail. Four controlled entry routes cover all selector vectors and both post-child outcomes; two ordinary 600-frame routes and fifteen engine-tail routes compare declared persistent RAM and full output on current x86 and x64. The native records are byte-identical. The registry advances from **499 to 510 exact labels** and from **888 to 946 exact feasible control relations**; historical conformance remains **1,992 / 1,992**. Child semantics remain assigned to their later source-order cohorts.

### T58 S2 scroll threshold and player-edge result

All ten labels from `ScrollHandler` through `GetScreenPosition` are current-equivalence exact. The static source audit found no C/ROM difference across scroll force, signed and threshold gates, page/PPU carry, raw offscreen-bit selection, both tables, edge borrow and return handoffs. Twenty-four natural original-ROM entries take both outcomes of all nine branches; every snapshot matches a fresh current x86 and x64 C90 owner replay over 1,784 persistent bytes under only CPU scratch/stack ABI exclusions, and the two native widths are byte-identical. The registry advances from **510 to 520 exact labels** and **946 to 971 exact feasible control relations**. Historical conformance remains **1,992 / 1,992**.


## S3 closure — game routine, entrance and player-control chain

All 23 scoped labels are current-equivalence exact. Static source comparison of original lines 5499–5687 found no shared-owner difference across the task vector, entrance branches, input partitions, child ordering, hole/death and cloud branches. The controlled ROM/caller matrix replays 23 entrance snapshots and 50 player-control snapshots through fresh C90 x86/x64 owners; every recorded child boundary and 1,784-byte persistent-state comparison passes with only CPU scratch/stack exclusions. Child algorithms retain their separately admitted owners. Platform-purity and a fresh shared OpenNT DOS16 MZ link pass. No product source changed, so no three-EXE refresh is due. All 100 incident feasible relations are exact: 92 have fresh S3 evidence and eight retain compatible prior proof.

### T58 S4 vine and pipe transition result

All 11 labels from Vine_AutoClimb through RightPipe are current-equivalence exact. Static shared-C audit covers vine gate, climb controls, coordinate move, vertical and side-pipe modes, timer wrap, area-mode writes and right-pipe control. Twenty-eight original transition snapshots replay recorded child calls and returns through fresh x86/x64 owners with 56 passing persistent-state comparisons and byte-identical widths. Child bodies remain separately assigned. Platform purity and shared OpenNT DOS16 link pass. Registry advances from 543 to 554 exact labels and from 1,063 to 1,082 exact feasible control relations; historical conformance remains 1,992 / 1,992.

### T58 S5 player mode result

All 14 labels from PlayerChangeSize through ExitDeath are current-equivalence exact. The static audit covers the size, blink, death and fire-flower timer gates, task writes and palette state. Twenty-two original snapshots replay their recorded caller boundaries through x86/x64 with 44 passing comparisons and byte-identical widths. Registry advances from 554 to 568 exact labels and from 1,082 to 1,100 exact feasible control relations; historical conformance remains 1,992 / 1,992.

### T58 S6 end-level result

All 10 labels from FlagpoleSlide through ExitNA are current-equivalence exact. The static audit covers flagpole control, task countdown, hidden one-up threshold and next-area reset. Twenty-nine original snapshots replay their recorded caller boundaries through x86/x64 with 58 passing comparisons and byte-identical widths. Registry advances from 568 to 578 exact labels and from 1,100 to 1,115 exact feasible control relations; historical conformance remains 1,992 / 1,992.

### T59 S1 movement dispatcher result

All three labels from PlayerMovementSubs through ProcMove are current-equivalence exact. Thirty-seven original snapshots replay caller boundaries through x86/x64 with 74 passing comparisons. Registry advances from 578 to 581 exact labels and from 1,115 to 1,124 exact feasible control relations; historical conformance remains 1,992 / 1,992.

### T59 S2 movement state result

All 12 labels from MoveSubs through ExitMov1 are current-equivalence exact. Registry advances from 581 to 593 exact labels and records the current state-vector, ground, air and water movement evidence.

### T59 S3 climb movement result

All 12 labels from ClimbAdderLow through InitMForceData are current-equivalence exact. Fresh x86/x64 replay confirms all original climb branches, both signed page-carry directions and all four side offsets. Registry advances from 593 to 605 exact labels and from 1,159 to 1,168 exact feasible control relations; historical conformance remains 1,992 / 1,992.

### T59 S4 player physics result

All 24 labels from MaxLeftXSpdData through ExitPhy are current-equivalence exact. Fresh x86/x64 replay confirms the physics state machine, table selection, jump/swim gates and horizontal parameter writes. Registry advances from 605 to 629 exact labels and from 1,168 to 1,216 exact feasible control relations; historical conformance remains 1,992 / 1,992.

### T59 S5 animation-speed result

All six labels from `PlayerAnimTmrData` through `SetAnimSpd` are current-equivalence exact. ROM table, thresholds, masks, skid writes and timer-store exit match current shared C; 64 ROM child-call streams replay through x86/x64 for 128 matching comparisons, and animation smoke, DOS16 link and platform purity pass. Registry advances from 629 to 635 exact labels and from 1,216 to 1,225 exact feasible control relations; historical conformance remains 1,992 / 1,992.

### T59 S6 friction result

All six labels from `ImposeFriction` through `SetAbsSpd` are current-equivalence exact. ROM friction branches and signed-speed output match shared C; 64 ROM child-call streams replay through x86/x64 for 128 matching comparisons, and friction smoke, DOS16 link and platform purity pass. Registry advances from 635 to 641 exact labels and from 1,225 to 1,238 exact feasible control relations; historical conformance remains 1,992 / 1,992.

### T59 Cohort-F cross-chain closure

The zero-credit S7 integration matrix combines all closed player movement,
movement-state, climb, physics, animation and friction chains. Twenty-four
original-ROM/current four-frame routes have zero persistent-RAM and
visible-output differences on both current x86 and x64; their native records
are byte-identical, and every declared composition join is reached. The
focused chain checks remain recorded at each S closure. A fresh OpenNT DOS16
MZ link and platform-purity audit pass. The live registry remains **641 exact
labels**, **1,238 exact feasible controls** and **18 source-infeasible raw
controls**; historical conformance remains **1,992 / 1,992**.
