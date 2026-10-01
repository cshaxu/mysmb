# A2 NMI-prefix state-handoff repair record

## Status

Closed by M2 T52 S1. This retained record identifies the discrepancy that was
corrected; it is no longer an unadmitted candidate.

## Confirmed chain

The bounded shared-owner chain is `RotPRandomBit -> SkipSprite0 ->
OperModeExecutionTree` inside `src/game/frame_root.c`, with
`NonMaskableInterrupt` as the enclosing owner. Its predecessor is the NMI
timer/pause prefix; its successor is the mode-dispatch call and then the RTI
tail.

## Closure evidence

At source `$8175`, immediately before the original dispatch call, a controlled
owner-ROM route recorded scratch `$00=$02`, the rotated LFSR state and physical
`$2000=$10` after a recorder-only NMI-entry mirror precondition of `$0778=$10`.
The shared C now performs the same scratch write and holds d7 clear through
dispatch; its RTI-equivalent tail restores d7. ROM-configured x86/x64 focused
regressions, Win32 self-tests, platform-purity and the OpenNT DOS16 link pass.

The current-equivalence registry records three nodes and two control edges as
`exact`. This repair changes no historical node-accounting numerator.
