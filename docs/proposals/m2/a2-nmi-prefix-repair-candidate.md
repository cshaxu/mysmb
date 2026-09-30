# A2 NMI-prefix state-handoff repair candidate

## Status

Unnumbered repair candidate produced by the active Td S9 current-equivalence
audit. It has no admitted implementation task or numeric identifier.

## Confirmed chain

The smallest shared-owner chain is `RotPRandomBit -> SkipSprite0 ->
OperModeExecutionTree` inside `src/game/frame_root.c`, with
`NonMaskableInterrupt` as its enclosing owner. Its predecessor is the NMI
timer/pause prefix; its successor is the mode-dispatch call and then the RTI
tail.

## Evidence and required outcome

A controlled cold-boot NMI-prefix route stops immediately before the ROM's
`OperModeExecutionTree` call. It establishes two differences on both current
x86 and x64:

- ROM `RotPRandomBit` leaves scratch `$00=$02`; C leaves `$00=$01`, the old
  VRAM-pointer low byte, because the C LFSR owner keeps the first masked bit
  only in a local variable.
- ROM physical `$2000=$10` at the dispatch boundary; C exposes `$90`, because
  it re-enables d7 before the source would reach its RTI tail.

The repair must restore the source scratch write and preserve a d7-clear
control state through mode dispatch, restoring d7 only at the RTI equivalent.
It must not move these decisions into a Win32 or DOS adapter.

## Receiving audit items

Nodes: `RotPRandomBit`, `SkipSprite0`, `NonMaskableInterrupt`.

Control edges: `control-00040` (`RotPRandomBit -> SkipSprite0`) and
`control-00052` (`SkipSprite0 -> OperModeExecutionTree`).

Expected current-audit delta after a successful repair and fresh route proof:
three nodes and two control edges from `mismatch` to `exact`; no historical
node-accounting credit is implied by this candidate.
