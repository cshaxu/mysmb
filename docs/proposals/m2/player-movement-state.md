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

## S1 implementation checkpoint

Shared player_movement.c now owns the admitted dispatch/ground/air chain.
The original source audit identifies three errors in the previous combined
body: a large airborne player must preserve crouch; PlayerPhysicsSub runs
before the size-change freeze guard and climb timer reset; FallingSub jumps
directly to LRAir, bypassing swimming animation/facing logic. The new owner
also restores force-selection before child calls and post-child reads.

PlayerPhysicsSub's existing climb/jump/horizontal-parameter body is extracted
behind its declared seam in player.c without claiming its tables/branches.
MovePlayerVertically similarly exposes the prior gravity call; its omitted
jumpspring/timer gate remains with the existing world-motion responsibility.
Climbing, animation and friction interiors are not repaired or credited here.

The [focused test](../../../test/player_movement_chain_smoke.c) passes on
x86/x64, checking all size/state/freeze combinations; post-physics freeze
and state mutations; child call order; swim/fall separation; child-return
direction/Y/death reads; all origin/Y byte pairs with released and held jump.
Seven focused suites pass on both widths (fourteen executions). All 67 shared
game units build as strict C90 on both widths with passing Windows self-tests;
the full OpenNT DOS16 link also succeeds. No platform source changed.

A diagnostic rerun against the previous original-ROM child boundaries uses
the current full native game, not replayed child returns:

| Prior family | Current actual-native matches | Retained failures |
| --- | ---: | ---: |
| T32 S2 vine/pipe | 38 | 18 |
| T32 S3 size/injury/death/palette | 44 | 0 |
| T32 S4 flagpole/end-level | 58 | 0 |

This removes 70 prior child-boundary failures across the two widths. These
diagnostics do not prove the new S1 branches or full frames. All fifteen S1
nodes remain open at 676 / 1,992 pending their own original-ROM node proof.
Three-target package publication and P review remain pending; DOS stays
link-only. Local scripts and diagnostic differences are under the admitted
ignored S1 build directory.

## S1 original movement proof

The original-ROM recorder now observes PlayerMovementSubs at $B329 and its
natural hardware-stack return. Immediate children execute normally: physics
$B450, animation $B58F, friction $B5CC, horizontal movement $BF09, vertical
movement $BF4D and climbing $B3CF. Horizontal movement's returned A is recorded
as well as RAM because the caller stores it in Player_X_Scroll. The observer
does not replace any original child, instruction, stack value or ROM byte.

The shared C caller checker replays those observed child returns, checking
1,784 persistent RAM bytes at every child entry and the final return. Scratch
$00-$07 and the hardware stack are outside the declared native ABI. A second
checker runs actual native children and retains every difference separately.

| Original node | Address | Scoped semantics |
| --- | --- | --- |
| PlayerMovementSubs | $B329 | Small-player crouch clear and large-player state gate |
| SetCrouch | $B338 | Store zero or down-button bit |
| ProcMove | $B33B | Physics before freeze read; climb timer gate |
| MoveSubs | $B34E | Ground, jump/swim, falling, climbing vector order |
| NoMoveSub | $B359 | Frozen movement returns after physics |
| OnGroundStateSub | $B35A | Animation before direction reload |
| GndMove | $B363 | Friction, horizontal movement, returned scroll byte |
| FallingSub | $B36D | Downward force then direct LRAir entry |
| JumpSwimSub | $B376 | Signed Y speed, current/previous A and wrapped height |
| DumpFall | $B38D | Copy downward force |
| ProcSwim | $B393 | Swim gate, animation, returned Y threshold |
| LRWater | $B3A6 | Reload direction before facing write |
| LRAir | $B3AC | Friction only with directional input |
| JSMove | $B3B3 | Horizontal return then death-mode force test |
| ExitMov1 | $B3C4 | Tail call to vertical movement |

All fifteen labels execute in 37 ordinary-NMI controlled scenarios. All
thirteen conditional instructions have both outcomes; the four vector words
match their original targets. The 74 caller comparisons pass on x86/x64.
Actual native calls produce 66 matches and eight failures: scenarios
3/7/11/15 on each width differ only at $070C, original 04 versus native 08.
This physics/climb-animation parameter remains with the planned S3 owner;
S1 grants no child credit. Both widths have identical diagnostic results.

Input coverage uses the reference controller's actual serial button bits.
An initial attempt to seed SavedJoypadBits at NMI was overwritten by the
original ReadJoypads; the final runs supply controller input normally. No
post-read patch is used. The observed, coverage-enabled and unobserved frame
outputs are byte-identical for all 37 scenarios. Raw outputs total 1,716,124
bytes beneath the admitted ignored directory, within its four-MB cap.

Reproduction uses the reference recorder with `--fixture=t33-movement=N`,
one frame, `--warmup=1`, `--movement-state-snapshot=...` and
`--control-children=...`. Repeat with `--pc-coverage=...`, and without
observers. Logical input is zero for cases 0-15, right for 16, down for 17;
cases 18-33 use bit 1 of N-18 for held A and bit 2 for right; cases 34-36
use left. Reverse these logical controller bytes into the recorder's serial
bit order. The project-owned fixture documents the remaining RAM inputs.
Build both modes of `player_movement_snapshot_check.c` and run
`test/verify_player_movement_snapshots.py` on the contained recordings and
owner-local ROM. It verifies branches, nodes, vector, observation invariance,
caller comparisons and cross-width diagnostic equality.

Three local artifacts have been refreshed. Windows self-tests pass; each
hidden Windows process creates its game window, remains alive for two seconds
and responds to a bounded message probe. These probes do not establish
playability, performance or full ROM parity. DOS remains link-only.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258605 | dd85fa8ef526e3a4c5ffcadf666a739e4adc77016e316c54e437467f5179ee4b |
| mysmb32.exe | 325271 | 76defe4c5c8d0860e271a21f07bf1e43d96a1cb1afda77e85c8572c1dfb590cd |
| mysmb64.exe | 332810 | 9ec9bc1d0649687c0e29d3ff424f9e087a36c1fa4e558fa1e893bb5c069c8ddf |

S1 P1 final review accepts 15/15 expected caller matches, increasing global
progress from 676 to 691 / 1,992. The fifteen rows above are the exact completed
set; no received node remains unfinished and no child receives credit.
The eight actual-child failures retain S3 physics custody. Similar-issue
sweep finds one production movement-dispatch definition in player_movement.c
and one caller in player_control.c; the former combined body is removed.
No platform source changed. Platform-purity and documentation gates pass.
Three local artifacts follow the owner-authorized delivery exception; they
are not redistribution or complete-game qualification evidence. S1 closes;
T33 remains open and S2 requires its own receipt before implementation.
