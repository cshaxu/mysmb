# Queue

## To-Do

This file lists work that has not started.  It is not a source-order archive,
a task ledger, or a record of completed work.  Active work is recorded only in
[CURRENT.md](CURRENT.md); closed tasks remain in their proposal/history record
and in the generated [node/task ledger](NODE_TASK_LEDGER.md).

A queue item has no numeric T/S identifier until it is admitted under the
[execution policy](../rules/EXECUTION.md).  Ordering is a priority and
source-dependency order, not a historical task-number list.

## M2: unadmitted shared-core repair candidates

The current `M2 T51 S5` audit is active and therefore is not a queue item.
When it closes or admits its next bounded implementation S, take the first
candidate whose dependencies are satisfied.  Each repair belongs exclusively
in shared `src/game/` code and must prove the same behavior on DOS16, Win32
x86 and Win32 x64.

1. [A2 NMI-prefix state-handoff repair](../proposals/m2/a2-nmi-prefix-repair-candidate.md)
   — `RotPRandomBit -> SkipSprite0 -> OperModeExecutionTree`, including the
   enclosing `NonMaskableInterrupt` handoff.  Restore ROM scratch `$00` and
   d7-clear PPU-control timing through mode dispatch.

2. [A6 title-menu timer-gate repair](../proposals/m2/a6-title-menu-order-repair-candidate.md)
   — restore the `ChkSelect -> ChkWorldSel` decision order for a zero demo
   timer and world-select B input.

3. [A7 Floatey timer-gate repair](../proposals/m2/a7-floatey-timer-gate-repair-candidate.md)
   — restore decrement-before-`$2b` comparison in the floatey score/one-up
   chain.

4. [B2 palette fall-through repair](../proposals/m2/b2-palette-fallthrough-repair-candidate.md)
   — restore the unconditional `GetBackgroundColor -> NoBGColor ->
   GetPlayerColors` palette producer path.

5. [B3 time-up task-handoff repair](../proposals/m2/b3-timeup-task-handoff-repair-candidate.md)
   — restore `DisplayTimeUp -> OutputInter -> NoTimeUp` task progression.

6. [H9 large-platform Y-source repair](../proposals/m2/h9-large-platform-y-source-repair-candidate.md)
   — make the first four large-platform sprite Y records read
   `Enemy_Y_Position,x` as the ROM does.

## M3: presentation adapters

1. [Presentation adapters](../proposals/m3-presentation-adapters.md) — neutral
   render-command seam and deterministic core ownership.
2. [Presentation adapters](../proposals/m3-presentation-adapters.md) — Win32
   consumption of neutral tile-row and actor commands.
3. [Presentation adapters](../proposals/m3-presentation-adapters.md) —
   deterministic 80x25 colored-object adapter.
4. [Presentation adapters](../proposals/m3-presentation-adapters.md) — DOS VGA
   indexed-frame adapter and OpenNT compile coverage.
5. [Presentation adapters](../proposals/m3-presentation-adapters.md) — real-mode
   DOS composition root, hardware hooks and local MZ link.
6. [Presentation adapters](../proposals/m3-presentation-adapters.md) — reviewed
   DOS runtime recovery and MZ link evidence.
7. [Presentation adapters](../proposals/m3-presentation-adapters.md) — DOS BIOS
   input/timing and VGA/text hardware hooks.
8. [Presentation adapters](../proposals/m3-presentation-adapters.md) — bounded
   DOS runtime verification and pacing evidence.

## M4: 486SX qualification

1. [486SX qualification](../design/ROADMAP.md) — physical-host protocol and
   measured DOS/VGA route evidence.
2. [486SX qualification](../design/ROADMAP.md) — execute the physical-host
   protocol and record measured route evidence.