# B3 time-up task-handoff repair candidate

## Status

Unnumbered current-equivalence repair candidate. This audit record admits no
production change.

## Confirmed discrepancy

`DisplayTimeUp` at `SMBDIS.ASM` lines 1553–1561 clears the expiration flag
and reaches `OutputInter` without writing `ScreenRoutineTask`. `OutputInter`
resets `ScreenTimer` and returns, leaving the task at 4. On the following
main-loop visit, the cleared flag takes `NoTimeUp`, whose explicit increment
plus `IncSubtask` advances directly to task 6.

Current [`src/game/game.c`](../../src/game/game.c) case 4 writes task 5 during
the expired branch. Case 5 then waits for the reloaded screen timer to reach
zero before it reaches task 6. This inserts a state and a delay that the ROM
does not take on the time-up path.

## Smallest candidate chain

`DisplayTimeUp -> OutputInter -> ResetScreenTimer -> return to task 4 ->
NoTimeUp -> IncSubtask` in `mysmb_game_step_screen_routine`. The fix must
retain the common output write order and must not move any behavior into a
Win32, x64 or DOS adapter.

## Required proof after a later admission

Use an original-ROM and x86/x64 fixture with `ScreenRoutineTask=4`, expired
flag set and a nonzero preexisting screen timer. Compare both the expired
frame and the next main-loop invocation: flag clear, text command, screen
timer, disable-screen flag, sprite OAM and task byte. Repeat the non-expired
task-4 path and task-5/task-7 timer-expiry paths to prove the correction does
not alter `ResetSpritesAndScreenTimer` behavior.
