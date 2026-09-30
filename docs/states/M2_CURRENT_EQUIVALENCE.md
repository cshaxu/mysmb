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
| Exact | 19 | Current source audit and original-ROM route both prove the label. |
| Needs evidence | 31 | Current source audit exists but the current original-ROM route is incomplete. |
| Mismatch | 3 | Current route or source audit finds a concrete semantic difference. |
| Unclassified | 1,939 | Not yet processed by this re-audit. |
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
| Exact | 41 control; 3 material RAM/table |
| Needs evidence | 87 |
| Mismatch | 2 |
| Unclassified | 4,212 control edges; material edge denominator pending feasible-path enumeration |
| **Total** | 4,342 control edges; material edge denominator pending feasible-path enumeration |

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

### Cohort A — A6 title-menu static pass

The title-menu/start slice records 15 nodes from `TitleScreenMode` through
`GoContinue`, together with 32 menu/start control relations. They remain
`needs-evidence`: the source branches require controlled title state for
Start, A+Start, Select, enabled/disabled world-select B, demo timeout,
continue-world and score-clear paths. Demo action/timing data and `RunDemo`
remain a separate source-route family.
