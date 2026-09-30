# H7 large-platform vector graph repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no production-code change.

## Confirmed discrepancy

At `SMBDIS.ASM` line 9187, `LargePlatformSubroutines` calls `JumpEngine` immediately before seven target-pointer words. `control-01711` incorrectly records a fall-through from that dispatch table to `EraseEnemyObject`. JumpEngine consumes the JSR return and indirect-jumps through the selected pointer; no target resumes sequentially at the table tail.

## Smallest candidate chain

Correct the extractor/registry representation for this JumpEngine vector. Preserve all seven real large-platform dispatches and their target-to-caller return semantics; remove or reclassify only the infeasible fall-through. Shared C needs no modification.

## Required proof after a later admission

Regenerate this graph fragment and run original-ROM/x86/x64 routes for IDs `$24` through `$2a`; verify that the seven dispatches remain registered and that no `LargePlatformSubroutines -> EraseEnemyObject` fall-through remains.
