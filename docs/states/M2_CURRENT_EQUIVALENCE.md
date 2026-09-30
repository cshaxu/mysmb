# M2 current-equivalence re-audit

This registry is the current-build complement to
[node progress](NODE_PROGRESS.md). Historical node-accounting status remains
`1,992 / 1,992`; it must never be read as a current end-to-end result until a
row below records a fresh audit disposition.

## Baseline

| Current-equivalence state | Labels | Meaning |
| --- | ---: | --- |
| Exact | 0 | Current source audit and original-ROM route both prove the label. |
| Needs evidence | 0 | Owner/route exists but current proof is incomplete. |
| Mismatch | 0 | Current route or source audit finds a concrete semantic difference. |
| Unclassified | 1,992 | Not yet processed by this re-audit. |
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
[`Extract-M2RomGraph.py`](../../tools/Extract-M2RomGraph.py). Its current
owner-local listing run reads all 1,992 inventory labels and establishes the
control subledger at **4,342** edges: 611 calls, 247 direct jumps, 1,566
branches, 1,058 fall-through relations, 611 return relations, two vector
entries and 247 `JumpEngine` selector edges. This is a fixed subledger, not
the final edge denominator: normalized RAM/table producer-consumer edges are
still required.

| Current-equivalence edge state | Edges |
| --- | ---: |
| Exact | 0 |
| Needs evidence | 0 |
| Mismatch | 0 |
| Unclassified | established by Td S9 extraction |
| **Total** | established by Td S9 extraction |

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

Confirmed mismatch chains are appended to `QUEUE.md` without a numeric task
identifier. Only an owner-approved later implementation admission allocates
the next numeric T and its S entries.
