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

## S2 admission: climbing movement and side switching

S1 is closed at 691 / 1,992. Transfer-139 accepts the eight open S2 labels
listed in the plan from T23 S5. Scope eight, expected eight, maximum 699.
The contiguous ClimbAdderLow through InitCSTimer chain owns its two four-byte
side-switch tables, vertical fractional/signed/page carries, direction and
collision intersection, side timer, four-way offset index and facing flip.
The shared owner remains game/player.c for this bounded existing routine;
no platform variation or second implementation is introduced. S1 dispatches
this child after physics; S3 owns that preceding physics parameter setup.

ROM logic proof first maps the original $B3C7-$B423 data/control slice and
its reads, writes, branches and carry flow. Record natural NMI climbing entry
and return states without replacing the original physics child. Compare the
native ClimbingSub directly against those entries, including both page-cross
signs, timer branches, controller/collision combinations and both facings.
Bind both tables to the owner-local PRG in validation. Existing full movement
routes retain S3 physics differences instead of masking them.

Operational proof uses exhaustive bounded byte-carry and side-index checks,
strict C90 x86/x64 and full DOS16 link, existing movement regressions and
platform purity. One final build/package pass delivers all three local EXEs.
Local ROM/listing remain owner-local research inputs; no third-party source
is imported. All generated inputs and recordings stay under ignored
build/m2-t33-s2 with a four-MB raw limit and twenty seconds per run; S2 owns
cleanup through T review. DOS remains link-only.

Similar-issue sweep covers every mysmb_player_climb definition/caller,
ClimbSideTimer writer and side-offset consumer. Current code chooses only
indices 0/3 from facing; original code uses the collision-filtered direction
and facing to select all four entries. Repair only this admitted chain.
Closure requires all eight named dispositions, both verification tracks,
ledger/inventory agreement and reviewed artifact identities.

## S2 original climbing proof

The original instruction audit confirms fractional ADC carry flows through
LDY/LDA/BPL/DEY/STY into the signed Y-position ADC and then page ADC. Native
unsigned-byte writes and a bounded 16-bit sum preserve those carries. The
side-switch LSR consumes Left_Right_Buttons AND Player_CollisionBits; facing
is independently tested by DEY/BEQ. Previous C used only facing, selecting
indices 0/3 and making the 1/2 offsets unreachable. The repair restores all
four selectors and retains original timer and facing-inversion order.

| Node | Address | Proven contract |
| --- | --- | --- |
| ClimbAdderLow | $B3C7 | Four low displacement bytes match ROM and all four indices execute |
| ClimbAdderHigh | $B3CB | Four signed page adders match ROM and all four indices execute |
| ClimbingSub | $B3CF | Fractional carry and signed vertical-speed direction |
| MoveOnVine | $B3E0 | Vertical position/page carries, collision mask and timer gate |
| ClimbFD | $B406 | Independent facing test after filtered-direction selection |
| CSetFDir | $B40A | Low/page displacement and controller-facing inversion |
| ExitCSub | $B41F | Existing-timer return and completed-switch return |
| InitCSTimer | $B420 | Zero filtered direction clears side timer |

Seventy-two ordinary-NMI scenarios execute original physics and then record
the real ClimbingSub entry and stack-derived return. The native checker calls
the actual C climbing implementation, with no replayed child returns. All
144 comparisons on x86/x64 match 1,784 persistent RAM bytes. All five source
branches have both outcomes; all six code labels execute; both data tables
match their eight original PRG bytes and all four indices are exercised.
Scratch $00-$07 and hardware stack are outside the native ABI. Preceding
physics parameters retain S3 custody and are not certified by this proof.

The existing movement fixture cases 37-108 provide this chain's inputs.
For cases 37-100, let n be case minus 37: logical controller is n modulo four
OR the up/down value [0,8,4,12] indexed by floor(n/16). Cases 101-108 use
logical left+right and vary the collision mask and timer. Reverse the logical
byte for the recorder's serial input order. Record one frame with warmup one,
`--fixture=t33-movement=N`, `--movement-state-snapshot=...` and
`--control-children=...`; repeat with PC coverage and without observers.
Build `player_climbing_snapshot_check.c` against the native game and run
`test/verify_player_climbing_snapshots.py` against the contained recordings
and owner-local ROM. Observed, coverage and unobserved frames are identical;
raw evidence totals 2,962,992 bytes, below the admitted four-MB cap.

Independent operational tests pass 393,216 fixed-point carry cases and
16,384 side-selection cases per width. The same test rejects the previous
committed implementation at the side-displacement assertion. Both Windows
builds compile all 67 shared units as strict C90; self-tests and hidden
two-second window/message probes pass. DOS16 compiles/links and remains
link-only, without embedded owner resources or playability qualification.

Similar-issue sweep finds one climbing definition and one production caller
in player_movement.c. Both offset tables and consumers are local to that
definition. ClimbSideTimer clear/reload belongs here; the non-climbing reload
remains in the proven S1 dispatcher and decrement stays with the timer owner.
No duplicate side selector or platform gameplay path was added. Platform
purity passes. The prior S1 physics differences remain explicitly incomplete.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258637 | f7d0a8e0d004717c2fd3a5d9d37d923ca61e21c7e3195cd1d6a72e83d080bfde |
| mysmb32.exe | 325271 | 8ef020bab942d199e16b8a0b24d444305b64ddfcb1070e8a477ef8b78b2250a1 |
| mysmb64.exe | 332810 | e2f99c3744c40cb4e71405d6d53a5ae5a47044d7c1c554fd9e807c1c56ae6d6c |

These are the owner-authorized local delivery artifacts, not full-game or
DOS qualification. Final review accepts 8/8 expected matches: the exact eight
rows above complete, with no received node deferred and no child credit.
Progress increases 691 -> 699 / 1,992. Both verification tracks, platform
purity, ledger closure and documentation checks pass. S2 closes; T33 remains
open, and the planned 28-node physics S3 requires its next admission.

## S3 admission: physics tables and initialization

S2 is closed at 699 / 1,992. Transfer-140 receives the exact 28 open S3
labels listed in the plan from T23 S5: scope 28, expected 28, maximum 727.
The chain starts with JumpMForceData and ends with ExitPhy; the shared owner
is game/player.c, entered by the proven movement dispatcher. Existing C
helpers divide contiguous source phases without introducing new gameplay.
S4 animation/friction algorithms and world movement/collision stay outside.

First audit all nine source tables and original branches, byte reads/writes,
jump eligibility, jump origin/force/sound, water-surface gate, climb animation
and horizontal limits/friction setup. Observe original PlayerPhysicsSub
entry and natural return under ordinary NMI execution; compare the real C
physics routine directly, without substituting child returns. Include all
speed thresholds, dry/swim/whirlpool, small/large, press/hold/release,
jumpspring, climbing and running/skidding parameter branches. Track table
bindings and node coverage individually; actual caller regressions validate
integration without granting later-node credit.

Independent operational tests exercise the admitted parameter contracts;
strict C90 x86/x64, DOS16 compile/link, platform purity and three local EXEs
complete one delivery. Owner ROM/listing remain local research inputs;
no imported implementation. Raw recordings stay under ignored build/m2-t33-s3,
limited to four MB per retained batch and twenty seconds per recorder run,
with S3 cleanup ownership through T review. DOS remains link-only.

Similar-issue sweep covers every physics helper definition/caller and the
source table consumers. Initial source audit finds reversed climb animation
selection (negative speed keeps 8, nonnegative selects 4) and missing swim
surface speed clear at Y below $14. Both belong here; no child behavior is
changed without original evidence. Closure requires all 28 exact dispositions,
both verification tracks, ledger/tracker agreement and artifact identities.

## S3 implementation checkpoint

Source-first audit of PlayerPhysicsSub finds two missing/reversed original
semantics. ProcClimb's BMI keeps animation eight for negative speed; the LSR
fallthrough selects four for zero/positive speed. Previous C did the reverse.
GetYPhy queues the swim sound, then clears vertical speed when Y is below
$14 before X_Physics. Previous C queued the sound but omitted that gate.
Both are now restored in their existing shared helpers. The horizontal-route
address comment is corrected to $B51C-$B58B; its behavior is unchanged.

The new independent physics test passes on both widths with 4,096 climbing
input/mask cases and 1,536 combinations of jump eligibility, swim timer,
vertical sign, jumpspring, current/previous A, surface threshold, whirlpool
and player size. It also checks climbing returns before horizontal setup,
ineligible jumps preserve jump state, and surface speed clearing preserves
the swim sound queue. These tests are operational evidence, not node credit.

Re-running all 37 prior S1 entry snapshots with the actual updated native
physics and movement yields 74/74 matching comparisons across x86/x64.
The eight former $070C mismatches are removed. This certifies only those
prior scenarios, not all S3 branches or complete frames. All 28 S3 labels
remain open at 699 / 1,992 pending their own table/branch/ROM proof, final
three-target build/package, review and accounting. No new P is committed
and the published artifacts remain the closed S2 delivery.

## S3 original physics proof

The admitted original slice is $B424-$B58B. All nine tables bind to the 44
owner-ROM bytes; all nineteen code labels execute. Source audit maps each
branch/read/write to the existing shared physics helpers, including fallthrough
from jump initialization into X_Physics. There is one production caller for
each helper, within PlayerPhysicsSub; the dispatcher calls that entry. No
platform implementation or alternative physics owner is introduced.

| Node | Address | Proven contract |
| --- | --- | --- |
| JumpMForceData | $B424 | Seven upward jump/swim force entries |
| FallMForceData | $B42B | Seven downward force entries |
| PlayerYSpdData | $B432 | Seven initial signed vertical speeds |
| InitMForceData | $B439 | Seven initial fractional force entries |
| MaxLeftXSpdData | $B440 | Three maximum left speeds |
| MaxRightXSpdData | $B443 | Three right speeds and entrance override |
| FrictionData | $B447 | Three friction coefficients |
| Climb_Y_SpeedData | $B44A | Three signed climbing speeds |
| Climb_Y_MForceData | $B44D | Three climbing fractional forces |
| PlayerPhysicsSub | $B450 | State-three dispatch and collision-filtered vertical selector |
| ProcClimb | $B465 | Climb force/speed loads and sign test |
| SetCAnim | $B475 | Negative speed keeps eight; other speeds select four |
| CheckForJumping | $B479 | Jumpspring and current/previous A gates |
| NoJump | $B488 | No-jump edge to horizontal parameter setup |
| ProcJumping | $B48B | Ground/swim/timer/vertical-sign eligibility |
| InitJS | $B4A0 | Timer, origin, dummy/force clear, state and speed thresholds |
| ChkWtr | $B4D2 | Minimum-height flag and swim/whirlpool selector |
| GetYPhy | $B4E4 | Four table loads, swim sound and surface speed clear |
| PJumpSnd | $B511 | Dry big/small jump sound selector |
| SJumpSnd | $B51A | Selected dry jump sound write |
| X_Physics | $B51C | Airborne speed threshold and ground-state split |
| ProcPRun | $B52D | Area, direction, B and running-timer gates |
| ChkRFast | $B545 | Slow-path speed/friction index and RunningSpeed test |
| FastXSp | $B554 | Second friction increment |
| SetRTmr | $B559 | Running timer reload to ten |
| GetXPhy | $B55E | Left limit then entrance-mode right-index override |
| GetXPhy2 | $B56C | Right limit, friction load and facing-dependent doubling |
| ExitPhy | $B58B | Return after parameter initialization |

Seventy-three ordinary-NMI scenarios record the actual physics entry and its
hardware-stack return. Original children are never replaced or redirected.
The native checker invokes actual PlayerPhysicsSub on the recorded input;
146 comparisons match all 1,784 persistent RAM bytes across x86/x64. Scratch
$00-$07 and hardware stack are outside the native ABI. All 31 conditional
instructions are covered: 30 have both outcomes. The BCC at $B52B always
branches because the preceding BCS at $B529 has already consumed carry-set;
the verifier checks both original opcodes and retains this unreachable
fallthrough explicitly, rather than fabricating coverage.

Fixture cases 109-180 cover dry speed thresholds, both sizes, swim/whirlpool
and surface boundaries, eligibility gates, air/ground/water, running/skidding,
all climbing parameters and entrance speed override. Case 181 covers speed
$21 with RunningSpeed clear. Initial entrance case 179 did not reach physics;
setting original PlayerEntranceCtrl to six supplies the normal auto-control
path, without patching the program counter or stack. Current retained runs
all reach the declared entry and return.

Reproduce using the source-RAM fixture in player_movement_fixture.h and
`--fixture=t33-movement=N`, one frame and warmup one. Logical controller is A
for cases 109-140 except case 139; cases 141-156 use B+right, cases 157-172
right, cases 173-178 cycle zero/up/down, and remaining cases use right.
Reverse that byte into the recorder's serial bit order. Record with
`--movement-state-snapshot=...` and `--control-children=...`, repeat with PC
coverage and without observers. Run the native player_physics_snapshot_check
on each child record and verify_player_physics_snapshots.py on the whole batch.
All observed/coverage/unobserved frame outputs match. Raw evidence totals
2,694,614 bytes below the four-MB batch limit.

Both widths pass the physics, climbing and player-route regression suites;
all 67 shared units compile as strict C90, Windows self-tests and hidden
startup/message probes pass, and DOS16 compiles/links. Player-route's obsolete
upward-climb expectation was corrected from four to the ROM-proven eight.
The additional core_smoke still fails at its entrance-loop assertion (source
line 136); comparing the prior S2 objects shows the same first failure. It is
retained legacy-suite debt, not a passing test or a newly introduced physics
regression. No later assertions in that suite are claimed executed.

The earlier S1 actual-child matrix now matches 74/74 comparisons, eliminating
its eight $070C differences. This is scoped integration evidence, not full
frame or whole-game certification. Source/code proof remains the basis for
node completion. No downstream animation, friction or collision node receives
credit. Platform purity passes; published DOS remains link-only.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258653 | 84ab7e70f2d09f32f130c3ad82a97ff4936855bd5502ba67f17054b9f99a041b |
| mysmb32.exe | 325271 | fc95f7213db008f5763057a37027e0d497e824fbf7dcaf881f8df225f26f84a9 |
| mysmb64.exe | 332810 | 2c2c632854ea2af591a12aeed2ef3e0a0ea3db2284561f4d76849fd6b443307a |

Final review accepts 28/28 expected matches: every node in the S3 table above
is complete, no received node is deferred, and no downstream node is credited.
Progress increases 699 -> 727 / 1,992. Ledger and documentation checks pass.
S3 closes; T33 remains open. Local artifacts use the owner-
authorized delivery exception and are not redistribution/qualification claims.
