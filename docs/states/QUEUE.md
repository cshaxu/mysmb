# Queue

## To-Do

This file lists work that has not started. It is not a source-order archive,
a task ledger, or a record of completed work. Active work is recorded only in
[CURRENT.md](CURRENT.md); closed tasks remain in their proposal/history record
and in the generated [node/task ledger](NODE_TASK_LEDGER.md).

## M2: current-equivalence work

M2 T53 is active. The following unnumbered repair candidate was discovered by
its current audit and cannot receive a numeric T until a later admission:

1. **NMI display-mask / VRAM transaction order** — `ScreenOff` and
   `control-00018`, `control-00019`, `control-03487`, `control-03488` require
   the shared `frame_root.c` order to match the ROM: display mask, InitScroll,
   OAM DMA, UpdateScreen, then buffer initialization and display restore.
   T53 must first preserve a controlled order trace; no adapter changes are
   involved.

The [T53–T70 current-equivalence proof program](../proposals/m2/current-equivalence-proof-program.md)
continues in source order. Each later task stays unadmitted until its exact S
packet, node/edge scope and original-ROM route are recorded.

## M3: presentation adapters

1. [Presentation adapters](../proposals/m3-presentation-adapters.md) — neutral render-command seam and deterministic core ownership.
2. [Presentation adapters](../proposals/m3-presentation-adapters.md) — Win32 consumption of neutral tile-row and actor commands.
3. [Presentation adapters](../proposals/m3-presentation-adapters.md) — deterministic 80x25 colored-object adapter.
4. [Presentation adapters](../proposals/m3-presentation-adapters.md) — DOS VGA indexed-frame adapter and OpenNT compile coverage.
5. [Presentation adapters](../proposals/m3-presentation-adapters.md) — real-mode DOS composition root, hardware hooks and local MZ link.
6. [Presentation adapters](../proposals/m3-presentation-adapters.md) — reviewed DOS runtime recovery and MZ link evidence.
7. [Presentation adapters](../proposals/m3-presentation-adapters.md) — DOS BIOS input/timing and VGA/text hardware hooks.
8. [Presentation adapters](../proposals/m3-presentation-adapters.md) — bounded DOS runtime verification and pacing evidence.

## M4: 486SX qualification

1. [486SX qualification](../design/ROADMAP.md) — physical-host protocol and measured DOS/VGA route evidence.
2. [486SX qualification](../design/ROADMAP.md) — execute the physical-host protocol and record measured route evidence.
