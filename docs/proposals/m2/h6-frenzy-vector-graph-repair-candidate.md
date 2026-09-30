# H6 frenzy-vector graph repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no production-code change.

## Confirmed discrepancies

At `SMBDIS.ASM` line 8860, `InitEnemyFrenzy` calls `JumpEngine` immediately before six pointer words. `control-01632` incorrectly records a fall-through to `NoFrenzyCode`; `control-03784` incorrectly records a return to `InitEnemyFrenzy`. JumpEngine consumes the JSR return and indirect-jumps to the selected target.

## Required correction

Regenerate the frenzy-vector graph preserving its six real dispatches and target-to-caller returns while removing or reclassifying the two infeasible relations. Shared C needs no modification.
