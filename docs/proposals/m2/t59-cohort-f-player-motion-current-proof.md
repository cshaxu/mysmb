# M2 T59: Cohort F player motion and physics current-equivalence proof

T59 follows closed T58 in original ROM source order. It audits the 63 labels from PlayerMovementSubs through SetAbsSpd. Historical accounting remains 1,992 / 1,992; this task records current shared-C equivalence only.

## Planned source-order S chains

| S | Entry to exit | Labels | Shared owner and route |
| --- | --- | ---: | --- |
| S1 | `PlayerMovementSubs -> ProcMove` | 3 | `src/game/player_movement.c` and `src/game/player.c`; player movement dispatcher and crouch gate. |
| S2 | `MoveSubs -> ExitMov1` | 12 | `src/game/player_movement.c` and `src/game/player.c`; ground air and water movement state chain. |
| S3 | `ClimbAdderLow -> InitMForceData` | 12 | `src/game/player_movement.c` and `src/game/player.c`; climb state and vertical-force tables. |
| S4 | `MaxLeftXSpdData -> ExitPhy` | 24 | `src/game/player_movement.c` and `src/game/player.c`; jump water and horizontal physics chain. |
| S5 | `PlayerAnimTmrData -> SetAnimSpd` | 6 | `src/game/player_movement.c` and `src/game/player.c`; animation timing skid and run-speed chain. |
| S6 | `ImposeFriction -> SetAbsSpd` | 6 | `src/game/player_movement.c` and `src/game/player.c`; directional friction and signed speed chain. |

## Exact node scope

| ROM node | Planned S | Current state |
| --- | --- | --- |
| `PlayerMovementSubs` | S1 | `needs-evidence` |
| `SetCrouch` | S1 | `needs-evidence` |
| `ProcMove` | S1 | `needs-evidence` |
| `MoveSubs` | S2 | `needs-evidence` |
| `NoMoveSub` | S2 | `needs-evidence` |
| `OnGroundStateSub` | S2 | `needs-evidence` |
| `GndMove` | S2 | `needs-evidence` |
| `FallingSub` | S2 | `needs-evidence` |
| `JumpSwimSub` | S2 | `needs-evidence` |
| `DumpFall` | S2 | `needs-evidence` |
| `ProcSwim` | S2 | `needs-evidence` |
| `LRWater` | S2 | `needs-evidence` |
| `LRAir` | S2 | `needs-evidence` |
| `JSMove` | S2 | `needs-evidence` |
| `ExitMov1` | S2 | `needs-evidence` |
| `ClimbAdderLow` | S3 | `needs-evidence` |
| `ClimbAdderHigh` | S3 | `needs-evidence` |
| `ClimbingSub` | S3 | `needs-evidence` |
| `MoveOnVine` | S3 | `needs-evidence` |
| `ClimbFD` | S3 | `needs-evidence` |
| `CSetFDir` | S3 | `needs-evidence` |
| `ExitCSub` | S3 | `needs-evidence` |
| `InitCSTimer` | S3 | `needs-evidence` |
| `JumpMForceData` | S3 | `needs-evidence` |
| `FallMForceData` | S3 | `needs-evidence` |
| `PlayerYSpdData` | S3 | `needs-evidence` |
| `InitMForceData` | S3 | `needs-evidence` |
| `MaxLeftXSpdData` | S4 | `needs-evidence` |
| `MaxRightXSpdData` | S4 | `needs-evidence` |
| `FrictionData` | S4 | `needs-evidence` |
| `Climb_Y_SpeedData` | S4 | `needs-evidence` |
| `Climb_Y_MForceData` | S4 | `needs-evidence` |
| `PlayerPhysicsSub` | S4 | `needs-evidence` |
| `ProcClimb` | S4 | `needs-evidence` |
| `SetCAnim` | S4 | `needs-evidence` |
| `CheckForJumping` | S4 | `needs-evidence` |
| `NoJump` | S4 | `needs-evidence` |
| `ProcJumping` | S4 | `needs-evidence` |
| `InitJS` | S4 | `needs-evidence` |
| `ChkWtr` | S4 | `needs-evidence` |
| `GetYPhy` | S4 | `needs-evidence` |
| `PJumpSnd` | S4 | `needs-evidence` |
| `SJumpSnd` | S4 | `needs-evidence` |
| `X_Physics` | S4 | `needs-evidence` |
| `ProcPRun` | S4 | `needs-evidence` |
| `ChkRFast` | S4 | `needs-evidence` |
| `FastXSp` | S4 | `needs-evidence` |
| `SetRTmr` | S4 | `needs-evidence` |
| `GetXPhy` | S4 | `needs-evidence` |
| `GetXPhy2` | S4 | `needs-evidence` |
| `ExitPhy` | S4 | `needs-evidence` |
| `PlayerAnimTmrData` | S5 | `needs-evidence` |
| `GetPlayerAnimSpeed` | S5 | `needs-evidence` |
| `ChkSkid` | S5 | `needs-evidence` |
| `SetRunSpd` | S5 | `needs-evidence` |
| `ProcSkid` | S5 | `needs-evidence` |
| `SetAnimSpd` | S5 | `needs-evidence` |
| `ImposeFriction` | S6 | `needs-evidence` |
| `JoypFrict` | S6 | `needs-evidence` |
| `LeftFrict` | S6 | `needs-evidence` |
| `RghtFrict` | S6 | `needs-evidence` |
| `XSpdSign` | S6 | `needs-evidence` |
| `SetAbsSpd` | S6 | `needs-evidence` |

## S1 admission - player movement dispatcher and crouch gate

S1 admits `PlayerMovementSubs -> ProcMove`: PlayerMovementSubs, SetCrouch and ProcMove. Its shared owner is `src/game/player_movement.c`. It owns only the top-level crouch selection and ordered child handoffs to physics, movement, animation and friction; child algorithms remain in their respective S chains. The current registry baseline is 578 exact labels and 1,115 exact feasible control relations. All three scoped labels need fresh evidence; historical expected matches are empty.

**ROM-logic track.** Compare original lines 5899-5915 with the C90 dispatch path, including small-player/state gates, down-button mask, crouch write and exact physics/movement/animation/friction ordering. Replay controlled original movement-entry snapshots with recorded child boundaries.

**Operational track.** Run x86/x64 C90 movement caller checks and focused movement chain smoke, link unchanged DOS16 core and run platform purity. A product-source repair refreshes all three target artifacts.

## S1 closure criteria

Every S1 label and feasible incident relation is current-exact with static and controlled-route evidence. Any discrepancy remains in its shared owner until repaired and re-audited before S2.

## S1 closure - player movement dispatcher and crouch gate

All three labels from PlayerMovementSubs through ProcMove are current-equivalence exact. Static comparison of original lines 5899-5915 found no shared-owner difference. All 37 movement snapshots replay recorded child boundaries through fresh C90 x86/x64 owners; 74 caller comparisons over 1,784 persistent bytes pass. Platform purity and unchanged shared DOS16 link pass. No product source changed, so no artifact refresh is due. Of 11 feasible incident controls, nine receive fresh S1 evidence and two retain compatible prior proof.

## S2 admission - ground, air and water movement chain

S2 admits `MoveSubs -> ExitMov1`: MoveSubs, NoMoveSub, OnGroundStateSub, GndMove, FallingSub, JumpSwimSub, DumpFall, ProcSwim, LRWater, LRAir, JSMove and ExitMov1. Shared owner: `src/game/player_movement.c`. It owns state-vector selection, growth freeze, climb-side timer, ground/air/swim branch predicates, input-facing writes and movement call order. Physics, animation, friction and climb children retain their separate chains. Registry baseline is 581 exact labels and 1,124 exact feasible controls; all 12 labels need fresh evidence. ROM route: controlled original movement snapshots with caller boundaries. Operational route: x86/x64 C90 replays, focused smoke, DOS16 link and platform purity.

## S2 closure - ground, air and water movement chain

All 12 labels from MoveSubs through ExitMov1 are current-equivalence exact. Static ROM comparison found no shared-owner difference. All 37 movement snapshots replay recorded child boundaries through fresh C90 x86/x64 owners; 74 caller comparisons pass. Platform purity passes. No product source changed, so no artifact refresh is due. Of 40 feasible incident controls, 35 receive fresh S2 evidence and 5 retain compatible prior proof.


## S3 admission - climb movement and vertical-force binding

S3 admits `ClimbAdderLow -> InitMForceData`: ClimbAdderLow, ClimbAdderHigh, ClimbingSub, MoveOnVine, ClimbFD, CSetFDir, ExitCSub, InitCSTimer, JumpMForceData, FallMForceData, PlayerYSpdData and InitMForceData. Shared owner: `src/game/player.c` with the movement dispatcher in `src/game/player_movement.c` as predecessor. It covers climb fractional and page-coordinate movement, left/right vine side movement, facing inversion, climb-side timer and the four vertical-force tables. It does not admit the subsequent physics consumer chain. Registry baseline is 593 exact labels and 1,159 exact feasible controls; all 12 scoped labels need fresh current evidence. ROM logic route: controlled climbing snapshots recording movement and table-selected state. Operational route: x86/x64 C90 replays, focused smoke, DOS16 link and platform purity.


## S3 closure - climb movement and vertical-force binding

All 12 labels from ClimbAdderLow through InitMForceData are current-equivalence exact. Static ROM comparison found no shared-owner difference. The two side tables and all four vertical-force tables bind exact ROM bytes. Fresh C90 x86/x64 replays pass 72 original climbing entries each, for 144 entry-return comparisons; all five control branches exercised both outcomes and all four side indices appeared. Focused smoke, DOS16 link and platform purity pass. No product source changed, so no artifact refresh is due. All nine previously unproved feasible internal controls receive fresh S3 evidence; the incoming dispatcher control retains compatible S2 proof.


## S4 admission - player physics, jump and horizontal-speed chain

S4 admits `MaxLeftXSpdData -> ExitPhy`: MaxLeftXSpdData, MaxRightXSpdData, FrictionData, Climb_Y_SpeedData, Climb_Y_MForceData, PlayerPhysicsSub, ProcClimb, SetCAnim, CheckForJumping, NoJump, ProcJumping, InitJS, ChkWtr, GetYPhy, PJumpSnd, SJumpSnd, X_Physics, ProcPRun, ChkRFast, FastXSp, SetRTmr, GetXPhy, GetXPhy2 and ExitPhy. Shared owner: `src/game/player.c` with `src/game/player_movement.c` as caller and S3 force tables as predecessor. It covers physics-state dispatch, climb parameters, jump initiation, swim/sound gates, run timer, friction and horizontal limit selection. Animation and friction execution remain in S5/S6. Registry baseline is 605 exact labels and 1,168 exact feasible controls; all 24 scoped labels need fresh current evidence. ROM logic route: controlled original player-physics snapshots with child boundaries and table-selected state. Operational route: x86/x64 C90 replays, focused smoke, DOS16 link and platform purity.


## S4 closure - player physics, jump and horizontal-speed chain

All 24 labels from MaxLeftXSpdData through ExitPhy are current-equivalence exact. Static ROM comparison found no shared-owner difference. The five S4 tables bind exact ROM bytes. Fresh C90 x86/x64 replays pass 73 original player-physics entries each, for 146 entry-return comparisons; every reachable branch outcome passes, while the B52B fallthrough is instruction-infeasible after B529 consumes carry. Focused smoke, DOS16 link and platform purity pass. No product source changed, so no artifact refresh is due. Of 50 feasible incident controls, 48 receive fresh S4 evidence and two retain compatible caller proof.


## S5 admission - animation speed and skid chain

S5 admits `PlayerAnimTmrData -> SetAnimSpd`: PlayerAnimTmrData, GetPlayerAnimSpeed, ChkSkid, SetRunSpd, ProcSkid and SetAnimSpd. Shared owner: `src/game/player.c`; S4 supplies speed and direction parameters, and S6 separately owns friction execution. It covers animation-timer table selection, running-speed write, input/moving-direction comparison and low-speed skid reset. Registry baseline is 629 exact labels and 1,216 exact feasible controls; all six scoped labels need fresh current evidence. ROM logic route: controlled original animation-speed snapshots. Operational route: x86/x64 C90 replays, focused smoke, DOS16 link and platform purity.


## S5 closure - animation speed and skid chain

All six labels from `PlayerAnimTmrData` through `SetAnimSpd` are current-equivalence exact. Static comparison of original ROM lines 6220-6248 found no shared-owner difference: the 2/4/7 timer bytes, $1c and $0e thresholds, A-button mask, moving-direction comparison, fast-path running-speed write, low-speed skid reset and common timer store are preserved. Fresh C90 x86/x64 replay passes all 64 original movement child-call streams, for 128 entry-return comparisons over 1,784 persistent bytes with CPU scratch and stack excluded; exhaustive animation smoke, DOS16 link and platform purity pass. No product source changed, so no three-EXE refresh is due. All nine feasible internal controls receive fresh S5 evidence; compatible incoming and return controls retain S2 proof.
