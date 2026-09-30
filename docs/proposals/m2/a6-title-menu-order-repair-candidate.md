# A6 title-menu timer-gate repair candidate

## Status

Unnumbered repair candidate produced by the active Td S9 current-equivalence
audit. It has no admitted implementation task or numeric identifier.

## Confirmed chain

The smallest shared-owner chain is `ChkSelect -> ChkWorldSel` inside
`src/game/title_modes.c`, in the `mysmb_game_title_step` title-menu decision
tree. Its predecessor is `GameMenuRoutine`; its successors are `DemoEngine`
and the world-select `SelectBLogic` path.

## Evidence and required outcome

A controlled original-ROM route enters `GameMenuRoutine` through the ordinary
NMI dispatcher with `DemoTimer = 0`, `WorldSelectEnableFlag = 1`, and B as the
latched input. The source checks `DemoTimer` in `ChkSelect` before it reaches
`ChkWorldSel`, therefore it enters `DemoEngine`; its first action then reaches
`RunDemo` with the title task intact. Current x86 and x64 instead evaluate the
enabled-B condition before this timer gate, take `ChkWorldSel -> SelectBLogic`,
and reset the title mode. The first divergent title-owned field at the common
post-menu boundary is `OperMode_Task`: ROM 3, C 0.

The repair must preserve the source order: Start tests, Select test, then the
`DemoTimer` gate and DemoEngine path; only a nonzero timer may proceed to
world-select B handling. It belongs solely in the shared game owner, never in
a Win32 or DOS adapter.

## Receiving audit items

Node: `ChkSelect`.

Control edge: `control-00087` (`ChkSelect -> ChkWorldSel`).

Expected current-audit delta after a successful repair and fresh route proof:
one node and one control edge from `mismatch` to `exact`; no historical
node-accounting credit is implied by this candidate.
