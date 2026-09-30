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
| Exact | 0 | Current source audit and original-ROM route both prove the label. |
| Needs evidence | 9 | Current source audit exists but the current original-ROM route is incomplete. |
| Mismatch | 0 | Current route or source audit finds a concrete semantic difference. |
| Unclassified | 1,983 | Not yet processed by this re-audit. |
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
| Exact | 0 |
| Needs evidence | 20 |
| Mismatch | 0 |
| Unclassified | 4,322 control edges; material edge denominator pending feasible-path enumeration |
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
[`ExtractM2RomDataAccesses.py`](../../tools/ExtractM2RomDataAccesses.py)
provides the source-addressed read/write atoms for that work. Its output is a
local audit input, not a data-edge list or a verdict.

Confirmed mismatch chains are appended to `QUEUE.md` without a numeric task
identifier. Only an owner-approved later implementation admission allocates
the next numeric T and its S entries.

### Cohort A — A1 boot and first-NMI boundary

The first reviewed chain is `Start -> VBlank1 -> VBlank2 -> WBootCheck ->
ColdBoot -> EndlessLoop`, with the adjacent `VRAM_AddrTable_Low`,
`VRAM_AddrTable_High` and `VRAM_Buffer_Offset` data labels. Its 9 nodes and
20 control edges are `needs-evidence`, never exact: current static review
maps the reset sequence to `boot.c` and the table consumers to `frame_root.c`,
including all two VBlank branches, warm/cold branches, calls and return paths.
The fresh cold route now records the original reset through its first NMI
return: it reaches the two VBlank loops and exits, checks all six score digits,
takes the cold-marker branch, completes ColdBoot and enters the idle boundary.
Current x86/x64 frames are byte-identical and have no persistent RAM, CIRAM,
palette, OAM, audio or PPU difference from that record after the explicit
sequence/CPU-stack exclusions. This remains `needs-evidence`: the warm-marker
outcome, invalid-score outcome and complete 19-selector VRAM matrix are not
yet exercised. The linked JSON ledger names all 29 stable identities and their
current counterparts.
