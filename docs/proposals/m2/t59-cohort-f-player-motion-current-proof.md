# M2 T59: Cohort F player motion and physics current-equivalence proof

T59 follows closed T58 in original ROM source order. It audits the 64 labels from PlayerMovementSubs through SetAbsSpd. Historical accounting remains 1,992 / 1,992; this task records current shared-C equivalence only.

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
