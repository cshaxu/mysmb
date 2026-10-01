# B3 time-up task-handoff repair candidate

## Status

Rejected by M2 T52 S5 ROM and full-chain source audit. This record remains as
the original false-positive finding; it admits no production change.

## Rejected discrepancy

The original review stopped at `DisplayTimeUp` and missed the internal call
made by `OutputInter`: `ResetScreenTimer` at listing lines 1809–1813 writes
`ScreenTimer = 7` **and increments `ScreenRoutineTask`** before returning.
The admitted ROM probe at `$86d2`, the RTS immediately after that call chain,
observes task 5. Current [`src/game/game.c`](../../src/game/game.c) case 4
performs the same state transition. The former discrepancy was therefore a
static-call-chain omission, not a native C behavior defect.

## Smallest candidate chain

`DisplayTimeUp -> OutputInter -> ResetScreenTimer -> return at task 5` in
`mysmb_game_step_screen_routine`. The evidence must include the complete
callee chain; a leaf-only inference is not sufficient.

## Required proof after a later admission

Use an original-ROM and x86/x64 fixture with `ScreenRoutineTask=4`, expired
flag set and a nonzero preexisting screen timer. Capture both the normal
NMI-return route and the `OutputInter` RTS boundary; compare flag clear, text
command, screen timer, disable-screen flag, sprite OAM and task byte. Repeat
the non-expired task-4 path and task-5/task-7 timer controls to prove the
audit does not overclaim the neighboring reset behavior.
