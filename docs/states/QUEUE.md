# Queue

## M1 Candidates

1. [Win32 and 16-bit-compatible platform foundation](../proposals/m1-win32-platform-foundation.md) — closed in M1.
2. [Static-C source pipeline](../proposals/m1-source-corpus-and-local-toolchain.md) — closed in M1.
3. [Native title-scene runtime](../proposals/m1-native-title-runtime.md) — closed in M1.
4. [Title-scene oracle](../proposals/m1-title-oracle.md) — closed in M1; title-route equality transfers to M2.

## M2 Candidates

1. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — complete direct-ROM PRG analysis and architecture inventory closed in M2 T1.
2. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — title progression, deterministic input, and the first transition checkpoint.
3. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — area bootstrap and background/object command route.
4. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — player route and collision.
5. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — object route: enemies, items, projectiles, timer, score, and power state.
6. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — death, restart, warp, continue, and completion mode routes.
7. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — neutral audio command route.
8. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — end-to-end playable-route oracle and Win32 validation.
9. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — active T9 output-ownership ledger and local frame-oracle contract; prior M2 closure claims are under correction.
10. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — translated background output; closed in M2 T10.
11. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — translated OAM output; closed in M2 T11.
12. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — Win32 native frame consumer and complete controller mapping; closed in M2 T12.
13. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — frame-indexed owner-local oracle; active in M2 T13.
14. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — cross-width route proof.
15. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — closure audit.

## M2 Structural-Recovery Candidates

These candidates exhaustively map the ROM executable source index. They are ordered candidates only; no numeric T or S is allocated here. The complete label checklist is [SMB1 ROM migration inventory](../etc/architecture/smb1-rom-migration-inventory.md), and the source-slice/call-graph map is [M2 structural recovery coverage](../proposals/m2-rom-structural-recovery.md).

1. **Frame root** — active as M2 T14 S1: reset/NMI/input/timing/PPU phase/mode dispatch.
2. **Title and terminal modes** — active as M2 T15 S4: source-reachable title-start, demo, victory and game-over NMI routes.
3. **Screen, text and status** — lines 1386–1824: status, text, screen routines and parser scheduling.
4. **M2 T18 active — Area graphics and parser** — lines 1825–5314 except `InitializeMemory`: metatiles, attributes, palettes, area/object parsing and block buffer.
5. **Game frame dispatcher** — lines 5315–5582: game mode/core/engine and ROM call order.
6. **Player route** — lines 5583–6297: control, physics, player state, pipes/vines/scroll and block actions.
7. **M2 T20 active — Fireballs and bubbles** — lines 6298–6729: spawn, movement, collision and offscreen semantics.
8. **Blocks, items and misc** — lines 6730–7787: coins, blocks, power-ups, vines, cannon/whirlpool/flagpole.
9. **M2 T19 active — Enemy stream and actors** — lines 7788–11084: `ObjectOffset`, stream parser, groups, frenzy, init and handlers.
10. **M2 T17 active — Collision and world primitives** — lines 11085–14459: all collision/bounds/gravity/shared geometry paths.
11. **M2 T16 active — OAM, offscreen and graphics** — lines 14460–15069: relative positions, offscreen bits and source OAM writers.
12. **Audio engine** — lines 15070–16368: sound queues, priorities, music and channel handlers.

The next approved candidate receives the next valid numeric T; only then is that T's S breakdown created. `M2 Td S2` governs this mapping.
## M3 Candidates

1. [Presentation adapters](../proposals/m3-presentation-adapters.md) — neutral render-command seam and deterministic core ownership.
2. [Presentation adapters](../proposals/m3-presentation-adapters.md) — Win32 consumption of neutral tile-row and actor commands.
3. [Presentation adapters](../proposals/m3-presentation-adapters.md) — deterministic 80x25 colored-object adapter.
4. [Presentation adapters](../proposals/m3-presentation-adapters.md) — DOS VGA indexed-frame adapter and OpenNT compile coverage.
5. [Presentation adapters](../proposals/m3-presentation-adapters.md) — real-mode DOS composition root, hardware hooks, and local MZ link.
6. [Presentation adapters](../proposals/m3-presentation-adapters.md) — reviewed DOS runtime recovery and MZ link evidence.
7. [Presentation adapters](../proposals/m3-presentation-adapters.md) — DOS BIOS input/timing and VGA/text hardware hooks.
8. [Presentation adapters](../proposals/m3-presentation-adapters.md) — bounded DOS runtime verification and pacing evidence.

## M4 Candidates

1. [486SX qualification](../design/ROADMAP.md) — physical host protocol and measured DOS/VGA route evidence.
2. [486SX qualification](../design/ROADMAP.md) — execute the physical-host protocol and record measured route evidence.

