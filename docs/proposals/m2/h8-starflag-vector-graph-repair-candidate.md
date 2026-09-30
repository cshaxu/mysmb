# H8 star-flag vector graph repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no production-code change.

## Confirmed discrepancy

At `SMBDIS.ASM` line 10483, `RunStarFlagObj` calls `JumpEngine` immediately before five target-pointer words. `control-02036` falsely records sequential fall-through to `GameTimerFireworks`, and `control-03868` falsely records a `JumpEngine` return to `RunStarFlagObj`. JumpEngine consumes the JSR return and indirect-jumps through the selected pointer; neither path is feasible.

## Smallest candidate chain

Correct only the extractor/registry representation of this vector. Preserve five real selector dispatches (`StarFlagExit`, `GameTimerFireworks`, `AwardGameTimerPoints`, `RaiseFlagSetoffFWorks`, `DelayToAreaEnd`) and each target return behavior. Shared C needs no modification.

## Required proof after a later admission

Regenerate this graph fragment and run controlled original-ROM/x86/x64 task selectors 0 through 4. Verify that each selected dispatch remains registered and neither infeasible fall-through nor synthetic return remains.
