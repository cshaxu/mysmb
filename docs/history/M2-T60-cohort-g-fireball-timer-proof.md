# M2 T60 closure: Cohort G fireballs, bubbles and timers proof

T60 closed the source-order Cohort G slice from `ProcFireball_Bubble` through
`VineHeightData`.

- All 49 scoped labels are current-equivalence exact.
- 138 feasible control relations are exact, taking the current re-audit from
  1,238 to 1,376 exact feasible control relations.
- The final matrix reconciles fireball/bubble dispatch and core state,
  game timer/warp, whirlpool, flagpole, jumpspring and vine setup paths on
  original ROM and current x86/x64 records.

`control-04306` (`JmpEO -> JumpspringHandler`) remains with the later
object-dispatcher audit and `material-00095` (`VineHeightData ->
VineObjectHandler`) remains with the later vine-actor audit. Both are explicit
uncredited boundaries, not T60 discrepancies.

The shared DOS16 link and platform-purity audit pass. T60 made no product source
change, so no target artifact refresh was due.

Historical migration accounting remains **1,992 / 1,992**. The independent
current-equivalence registry closes this task at **690 / 1,992 exact nodes**
and **1,376 / 4,324 exact feasible control relations** (with 18 separately
proven infeasible raw control edges). Detailed chain evidence remains in the
retained [T60 proposal](../proposals/m2/t60-cohort-g-fireball-timer-current-proof.md).
