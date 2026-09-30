# H1 JumpEngine graph-edge repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no
production change and has no numeric M2 task.

## Confirmed discrepancy

The current extracted control graph contains `control-01339` (`BlockCode ->
MushFlowerBlock`, fall-through) and `control-03743` (`JumpEngine -> BlockCode`,
return). At `SMBDIS.ASM` lines 2395–2408, `JumpEngine` executes `PLA`, `PLA`
and `JMP ($06)`: it deliberately removes the JSR return address, obtains the
selected word from the following vector table, and transfers to the target.
The table bytes are not a fall-through path. A target `RTS` resumes the caller
of `BumpBlock`, not `BlockCode`.

## Smallest candidate chain

Correct the graph extractor/registry representation for `BlockCode ->
JumpEngine` and its nine `jump-engine-dispatch` targets. Preserve the actual
content-target return handoff; remove or reclassify the two infeasible edges.
No shared game C owner requires modification.

## Required proof after a later admission

Regenerate the affected graph fragment from the reviewed source, then compare
all nine selector values against the original ROM and x86/x64 shared-C content
dispatch. The corrected ledger must not change the canonical graph by silently
dropping any real dispatch or target-return relationship.
