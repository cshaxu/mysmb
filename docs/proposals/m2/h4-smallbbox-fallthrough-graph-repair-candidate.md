# H4 SmallBBox fall-through graph repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no
production-code change and has no numeric M2 task.

## Confirmed discrepancy

At `SMBDIS.ASM` line 8235, `SmallBBox` loads `A=$09` then executes
`BNE SetBBox`. The loaded value makes the branch unconditionally taken, so
`control-01515`, the extracted fall-through from `SmallBBox` to
`InitRedPTroopa`, is infeasible.

## Smallest candidate chain

Correct the graph extractor/registry treatment of constant-condition branches
for this entry. Preserve `SmallBBox -> SetBBox` and the normal tail's exact
box, direction and vertical-state writes. No shared C initializer code
requires modification.

## Required proof after a later admission

Regenerate this initializer graph fragment and compare direct Goomba, Podoboo,
Bloober and Cheep Cheep target routes against original ROM and x86/x64. Verify
that the taken tail remains registered and the false sequential relation is
removed or reclassified.
