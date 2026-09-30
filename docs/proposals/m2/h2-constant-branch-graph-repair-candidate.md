# H2 constant-branch and BIT-overlap graph repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no
production-code change and has no numeric M2 task.

## Confirmed discrepancy

At `SMBDIS.ASM` lines 7656–7663, `MoveDropPlatform` loads `Y=$7f` before
`BNE SetMdMax`, and `SetMdMax` loads `A=$02` before `BNE SetXMoveAmt`. Their
not-taken paths are infeasible, yet the extracted graph contains
`control-01405` and `control-01408` as fall-through relations. At lines
7698–7702, `MovePlatformDown` uses a BIT-opcode overlap to skip
`MovePlatformUp`’s `LDA #$01`; `control-01415` therefore cannot represent a
full fall-through into the target-label entry.

## Smallest candidate chain

Correct the control-graph extractor/registry’s constant-condition and
instruction-overlap semantics for these three entries. Preserve the real
`SetMdMax -> SetXMoveAmt` path and the shared post-load platform body. The
shared C movement/gravity implementation requires no change.

## Required proof after a later admission

Regenerate the local movement graph fragment from reviewed source and compare
force, maximum-speed and direction handoffs for drop platform, slow enemy,
platform-up and platform-down routes against original ROM and x86/x64.
