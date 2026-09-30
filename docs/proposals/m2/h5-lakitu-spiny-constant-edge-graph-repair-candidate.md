# H5 Lakitu/Spiny constant-edge graph repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no
production-code change and has no numeric M2 task.

## Confirmed discrepancies

At `SMBDIS.ASM` lines 8318–8322, `ChkNoEn` takes `BPL ChkNoEn` for every
nonnegative post-decrement slot. Reaching the following `BMI RetEOfs` requires
X=$ff, making `control-01537`, the sequential fall-through to `CreateL`,
infeasible. At lines 8377–8382, `SmallBBox` returns through `InitVStf` with
A=$00, so `CMP #$00; BMI SpinyRte` cannot take its branch;
`control-01552` is likewise infeasible.

## Smallest candidate chain

Correct constant-condition and loop-exhaustion representation for these two
control relations. Preserve the real inactive-slot `CreateL` branch and the
real `SetSpSpd` fall-through through `DEY` into `SpinyRte`. No shared C
Lakitu/Spiny implementation requires modification.

## Required proof after a later admission

Regenerate this graph fragment and replay original-ROM/x86/x64 routes for
Lakitu absence with full slots, free-slot recreation, and Spiny egg creation.
Verify all feasible loop/branch paths remain registered while the two false
relations are removed or reclassified.
