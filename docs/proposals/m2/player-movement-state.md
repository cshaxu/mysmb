# M2 T33: Player movement state and physics

## Status and exact chain plan

T33 follows closed T32 in the original source sequence. Baseline 676 / 1,992;
63 open labels, all intended matches, maximum 739. This includes the deferred
PlayerMovementSubs entry at line 5899 with the 62 successors in the planned
5901-6297 slice. All incoming nodes have existing T23 S5 custody; only S1's
fifteen transfer at this admission. Later S receipts are not yet allocated.
Each S carries mapping, C translation, ROM proof and operational delivery
together. Adjacent tables remain with their consuming algorithms.

| S | Exact labels in original order | Shared-game responsibility |
| --- | --- | --- |
| S1 | `PlayerMovementSubs`, `SetCrouch`, `ProcMove`, `MoveSubs`, `NoMoveSub`, `OnGroundStateSub`, `GndMove`, `FallingSub`, `JumpSwimSub`, `DumpFall`, `ProcSwim`, `LRWater`, `LRAir`, `JSMove`, `ExitMov1` | Movement dispatch, crouch/freeze gates and ground/jump/swim/fall control chain |
| S2 | `ClimbAdderLow`, `ClimbAdderHigh`, `ClimbingSub`, `MoveOnVine`, `ClimbFD`, `CSetFDir`, `ExitCSub`, `InitCSTimer` | Climbing movement, side-switch tables, facing and timer chain |
| S3 | `JumpMForceData`, `FallMForceData`, `PlayerYSpdData`, `InitMForceData`, `MaxLeftXSpdData`, `MaxRightXSpdData`, `FrictionData`, `Climb_Y_SpeedData`, `Climb_Y_MForceData`, `PlayerPhysicsSub`, `ProcClimb`, `SetCAnim`, `CheckForJumping`, `NoJump`, `ProcJumping`, `InitJS`, `ChkWtr`, `GetYPhy`, `PJumpSnd`, `SJumpSnd`, `X_Physics`, `ProcPRun`, `ChkRFast`, `FastXSp`, `SetRTmr`, `GetXPhy`, `GetXPhy2`, `ExitPhy` | Physics tables, climb/jump/swim setup, X-speed/friction parameter chain |
| S4 | `PlayerAnimTmrData`, `GetPlayerAnimSpeed`, `ChkSkid`, `SetRunSpd`, `ProcSkid`, `SetAnimSpd`, `ImposeFriction`, `JoypFrict`, `LeftFrict`, `RghtFrict`, `XSpdSign`, `SetAbsSpd` | Animation timing and signed friction/absolute-speed chain |

## S1 admission: movement dispatch and ground air states

Scope and expected matches are the fifteen S1 labels above, all open.
Baseline 676, expected fifteen, maximum 691. Transfer-138 accepts them from
T23 S5. Source lines 5899-5982 span PlayerMovementSubs through ExitMov1.
The predecessor is T32's PlayerCtrlRoutine; original physics/animation/
friction/climbing children retain existing T23 S5 responsibility until their
planned S2-S4 admission. Horizontal/vertical world movement keeps its existing
owner. Caller seams may expose unchanged children but grant no child credit.

Implement one shared game/player_movement.c owner. Restore crouch behavior
for small/large and airborne states, physics before size-freeze read, the
four-way state vector, climb-side timer reset, ground animation/facing/
friction/movement ordering, falling-force selection, held/released jump
and wrapped height threshold, swim/water-height gates, airborne directional
friction, horizontal scroll result and death vertical-force override.
Do not fold animation, jump-parameter or friction interiors into this S.

ROM track compares original branches, byte arithmetic, reads/writes, tables
and call graph before testing. Use ordinary-NMI source-RAM states and read-only
child/root boundaries. Record actual native child failures independently of
scoped caller proof. Operational track uses mutating child callbacks, bounded
state/byte combinations and existing player-chain regressions; strict C90
x86/x64, full DOS16 link, platform purity and three EXEs per implementation P.

Existing owner-local ROM/listing remain non-redistributable research inputs;
no third-party implementation import. Temporary data stay in ignored
build/m2-t33-s1, capped at 4 MB raw and twenty seconds per recorder run,
with S1 cleanup ownership through T review. DOS remains link-only. Similar-
issue sweep covers all movement dispatch and ground/air state callers,
freeze/crouch/climb timer writers and duplicated movement orchestration.
Platforms keep physical input, timing and presentation only.

T closure requires all 63 named dispositions, accepted transfers for any
unfinished received node, both verification tracks and one cross-S matrix.
The previous T32 child failures motivate checking integration; they do not
replace original-node source order or authorize unrelated repairs.
