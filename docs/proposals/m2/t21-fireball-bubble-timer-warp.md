# Supersession

This early duplicate T21 draft is not an executable candidate.  Its fireball
range belongs to the bounded T34 chain and its bubbles/timer/Warp range belongs
to T35 in the authoritative [T21--T51 source-order plan](t21-t49-source-order-recovery.md).  Retain the observations below as historical research only; do
not admit, transfer, or allocate an S from this document.
# M2 T21 — bounded T20 successor

## Scope

T21 receives exactly **24** unfinished T20 labels: `ProcFireball_Bubble`, `ProcFireballs`, `ProcAirBubbles`, `BublLoop`, `BublExit`, `FireballXSpdData`, `FireballObjCore`, `RunFB`, `EraseFB`, `NoFBall`, `FireballExplosion`, `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`, `Y_Bubl`, `ExitBubl`, `Bubble_MForceData`, `BubbleTimerData`, `RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer`, `WarpZoneObject`. Baseline: **3 / 1,992**; expected matches at admission: none.

## S plan

1. **S1 active — ROM contract intake:** map every branch, RAM/table read-write and call boundary; establish both verification plans.
2. **S2 — fireball implementation:** `ProcFireball_Bubble` through `FireballExplosion`.
3. **S3 — bubble, timer and Warp implementation:** `ProcAirBubbles` through `WarpZoneObject`.
4. **S4 — ROM logic-equivalence verification:** compare source branches, writes, tables and ordered reachable routes.
5. **S5 — operational verification and closure:** focused tests, x86/x64, DOS16, platform purity, `NODE_PROGRESS` update and accepted transfers.

S4 and S5 are independent required gates.
