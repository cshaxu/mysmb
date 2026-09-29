# M2 T41: Bridge, Bowser and remaining actor chains

## Scope and source boundary

T40 closed in 9b3ff3f at 1,166/1,992. T41 follows the approved source-order
plan from BridgeCollapseData (line 10092) through ExScrnBd (11075), ending
before FireballEnemyCollision (11085). All 123 labels are listed below.
There are 118 expected new matches and five retained matches, maximum
1,284/1,992. StarFlagExit is audited but incomplete; all other expected
labels are open. KillAllEnemies/KillLoop retain T38 S1 proof; FlameTimerData,
SetFlameTimer and ExFl retain T39 S1 proof. No duplicate credit is allowed.

Only S1 is admitted now. Later rows plan S ownership but do not transfer
custody or permit concurrent execution. The current receivers below are the
admission snapshot; accepted events in the ledger govern subsequent custody.

## Source-ordered chain plan

Each S performs source mapping, shared C migration, original node/branch/data
comparison and operational validation together. Adjacent tables and local
loops stay with their consumer; distinct roots split at owner or route-family
boundaries. The balance-platform rope/fall graph remains one complete chain.

| S | Chain | Shared game owner | Expected / scoped | Original route and acceptance focus |
| --- | --- | --- | ---: | --- |
| S1 | Bridge collapse | bridge.c | 6 / 6 | VictoryMode task zero, all bridge stages, absent/normal/falling Bowser; RemBridge and graphics child handoffs. |
| S2 | Bowser control and defeated erasure | enemy/bowser.c | 17 / 19 | RunBowser from the original actor vector: defeated height, timers, facing/range, jump, hammer and world-dependent breath branches. |
| S3 | Bowser front/rear orchestration | enemy/bowser.c and oam/bowser_gfx.c | 4 / 4 | BowserGfxHandler front/rear slot handoffs, ObjectOffset restoration, ProcessBowserHalf collision gates. |
| S4 | Flame timer and full flame actor | enemy/bowser_flame.c and oam/bowser_flame_gfx.c | 9 / 12 | ProcBowserFlame fractional motion, relative position, original three-sprite loop and four offscreen-bit branches; retain timer proofs. |
| S5 | Fireworks lifetime and score tail | enemy/fireworks.c | 3 / 3 | RunFireworks timer/frame transitions, explosion child arguments and EndAreaPoints tail. |
| S6 | Star flag and end-area timer/score sequence | enemy/star_flag.c | 20 / 20 | RunStarFlagObj task vector through timer/fireworks choices, score conversion, raising/drawing and completion delay; all three tables. |
| S7 | Piranha movement and pipe priority | enemy/piranha.c | 6 / 6 | MovePiranhaPlant state/timer gates, player distance, speed reversal, endpoints and background-priority store. |
| S8 | Firebar angular primitive | enemy/firebar_children.c | 2 / 2 | FirebarSpin from existing ProcFirebar routes; both spin directions, low-byte carry/borrow, returned high byte and scratch. |
| S9 | Balanced platforms and ropes | enemy/balance_platform.c | 26 / 26 | BalancePlatform pair selection, collision-driven movement/fall, both rope updates and SetupPlatformRope address/carry paths. |
| S10 | Vertical oscillating platform | enemy/platform.c | 6 / 6 | YMovingPlatform rest/center/top branches, frame gate, shared up/down children and rider positioning. |
| S11 | Horizontal, drop and right-moving platform contacts | enemy/platform.c | 9 / 9 | Original platform vector selects XMovingPlatform, DropPlatform and RightPlatform; shared PositionPlayerOnHPlat carry/borrow and rider child. |
| S12 | Large/small lift movement and rider tail | enemy/platform.c | 5 / 5 | Both lift entry roots share MoveLiftPlatforms; timer, fractional carry and large/small rider collision tails. |
| S13 | Extended offscreen bounds and erasure | enemy/actor_slots.c | 5 / 5 | OffscreenBoundsCheck ID gates, original carry chain, signed page differences, right-edge exceptions and erase child. |

## Exact node checklist and receiving plan

Every row requires original branch/read/write, table binding, caller and
successor evidence at closure; the S route above groups execution, not credit.
Unproved child bodies stay with their own receivers. A child boundary may use
recorded returns only after full input comparison, while separate actual-child
execution keeps every remaining difference visible. No closure of a caller
implicitly closes its descendants.

| ROM line | Node | Incoming state | Current receiver | Planned chain |
| ---: | --- | --- | --- | --- |
| 10092 | `BridgeCollapseData` | open | M2 T19 S5 | S1 |
| 10098 | `BridgeCollapse` | open | M2 T19 S5 | S1 |
| 10111 | `SetM2` | open | M2 T19 S5 | S1 |
| 10116 | `MoveD_Bowser` | open | M2 T19 S5 | S1 |
| 10120 | `RemoveBridge` | open | M2 T19 S5 | S1 |
| 10152 | `NoBFall` | open | M2 T19 S5 | S1 |
| 10156 | `PRandomRange` | open | M2 T19 S5 | S2 |
| 10159 | `RunBowser` | open | M2 T19 S5 | S2 |
| 10167 | `KillAllEnemies` | ROM-match complete | M2 T38 S1 | S2 |
| 10169 | `KillLoop` | ROM-match complete | M2 T38 S1 | S2 |
| 10176 | `BowserControl` | open | M2 T19 S5 | S2 |
| 10182 | `ChkMouth` | open | M2 T19 S5 | S2 |
| 10185 | `FeetTmr` | open | M2 T19 S5 | S2 |
| 10192 | `ResetMDr` | open | M2 T19 S5 | S2 |
| 10197 | `B_FaceP` | open | M2 T19 S5 | S2 |
| 10211 | `GetPRCmp` | open | M2 T19 S5 | S2 |
| 10222 | `GetDToO` | open | M2 T19 S5 | S2 |
| 10237 | `CompDToO` | open | M2 T19 S5 | S2 |
| 10240 | `HammerChk` | open | M2 T19 S5 | S2 |
| 10250 | `SetHmrTmr` | open | M2 T19 S5 | S2 |
| 10258 | `SkipToFB` | open | M2 T19 S5 | S2 |
| 10259 | `MakeBJump` | open | M2 T19 S5 | S2 |
| 10265 | `ChkFireB` | open | M2 T19 S5 | S2 |
| 10270 | `SpawnFBr` | open | M2 T19 S5 | S2 |
| 10283 | `SetFBTmr` | open | M2 T19 S5 | S2 |
| 10289 | `BowserGfxHandler` | open | M2 T19 S5 | S3 |
| 10296 | `CopyFToR` | open | M2 T19 S5 | S3 |
| 10321 | `ExBGfxH` | open | M2 T19 S5 | S3 |
| 10323 | `ProcessBowserHalf` | open | M2 T19 S5 | S3 |
| 10337 | `FlameTimerData` | ROM-match complete | M2 T39 S1 | S4 |
| 10340 | `SetFlameTimer` | ROM-match complete | M2 T39 S1 | S4 |
| 10347 | `ExFl` | ROM-match complete | M2 T39 S1 | S4 |
| 10349 | `ProcBowserFlame` | open | M2 T19 S5 | S4 |
| 10356 | `SFlmX` | open | M2 T19 S5 | S4 |
| 10374 | `SetGfxF` | open | M2 T19 S5 | S4 |
| 10384 | `FlmeAt` | open | M2 T19 S5 | S4 |
| 10388 | `DrawFlameLoop` | open | M2 T19 S5 | S4 |
| 10417 | `M3FOfs` | open | M2 T19 S5 | S4 |
| 10423 | `M2FOfs` | open | M2 T19 S5 | S4 |
| 10429 | `M1FOfs` | open | M2 T19 S5 | S4 |
| 10434 | `ExFlmeD` | open | M2 T19 S5 | S4 |
| 10438 | `RunFireworks` | open | M2 T19 S5 | S5 |
| 10447 | `SetupExpl` | open | M2 T19 S5 | S5 |
| 10457 | `FireworksSoundScore` | open | M2 T19 S5 | S5 |
| 10468 | `StarFlagYPosAdder` | open | M2 T19 S5 | S6 |
| 10471 | `StarFlagXPosAdder` | open | M2 T19 S5 | S6 |
| 10474 | `StarFlagTileData` | open | M2 T19 S5 | S6 |
| 10477 | `RunStarFlagObj` | open | M2 T19 S5 | S6 |
| 10491 | `GameTimerFireworks` | open | M2 T19 S5 | S6 |
| 10503 | `SetFWC` | open | M2 T19 S5 | S6 |
| 10506 | `IncrementSFTask1` | open | M2 T19 S5 | S6 |
| 10509 | `StarFlagExit` | audited; evidence incomplete | M2 T19 S5 | S6 |
| 10512 | `AwardGameTimerPoints` | open | M2 T19 S5 | S6 |
| 10522 | `NoTTick` | open | M2 T19 S5 | S6 |
| 10529 | `EndAreaPoints` | open | M2 T19 S5 | S6 |
| 10534 | `ELPGive` | open | M2 T19 S5 | S6 |
| 10543 | `RaiseFlagSetoffFWorks` | open | M2 T19 S5 | S6 |
| 10549 | `SetoffF` | open | M2 T19 S5 | S6 |
| 10555 | `DrawStarFlag` | open | M2 T19 S5 | S6 |
| 10559 | `DSFLoop` | open | M2 T19 S5 | S6 |
| 10580 | `DrawFlagSetTimer` | open | M2 T19 S5 | S6 |
| 10585 | `IncrementSFTask2` | open | M2 T19 S5 | S6 |
| 10589 | `DelayToAreaEnd` | open | M2 T19 S5 | S6 |
| 10596 | `StarFlagExit2` | open | M2 T19 S5 | S6 |
| 10602 | `MovePiranhaPlant` | open | M2 T19 S5 | S7 |
| 10619 | `ChkPlayerNearPipe` | open | M2 T19 S5 | S7 |
| 10624 | `ReversePlantSpeed` | open | M2 T19 S5 | S7 |
| 10632 | `SetupToMovePPlant` | open | M2 T19 S5 | S7 |
| 10638 | `RiseFallPiranhaPlant` | open | M2 T19 S5 | S7 |
| 10656 | `PutinPipe` | open | M2 T19 S5 | S7 |
| 10664 | `FirebarSpin` | open | M2 T19 S5 | S8 |
| 10677 | `SpinCounterClockwise` | open | M2 T19 S5 | S8 |
| 10692 | `BalancePlatform` | open | M2 T19 S5 | S9 |
| 10697 | `DoBPl` | open | M2 T19 S5 | S9 |
| 10701 | `CheckBalPlatform` | open | M2 T19 S5 | S9 |
| 10709 | `ChkForFall` | open | M2 T19 S5 | S9 |
| 10720 | `MakePlatformFall` | open | M2 T19 S5 | S9 |
| 10723 | `ChkOtherForFall` | open | M2 T19 S5 | S9 |
| 10733 | `ChkToMoveBalPlat` | open | M2 T19 S5 | S9 |
| 10750 | `ColFlg` | open | M2 T19 S5 | S9 |
| 10752 | `PlatUp` | open | M2 T19 S5 | S9 |
| 10754 | `PlatSt` | open | M2 T19 S5 | S9 |
| 10756 | `PlatDn` | open | M2 T19 S5 | S9 |
| 10758 | `DoOtherPlatform` | open | M2 T19 S5 | S9 |
| 10771 | `DrawEraseRope` | open | M2 T19 S5 | S9 |
| 10796 | `EraseR1` | open | M2 T19 S5 | S9 |
| 10800 | `OtherRope` | open | M2 T19 S5 | S9 |
| 10819 | `EraseR2` | open | M2 T19 S5 | S9 |
| 10822 | `EndRp` | open | M2 T19 S5 | S9 |
| 10828 | `ExitRp` | open | M2 T19 S5 | S9 |
| 10831 | `SetupPlatformRope` | open | M2 T19 S5 | S9 |
| 10840 | `GetLRp` | open | M2 T19 S5 | S9 |
| 10857 | `GetHRp` | open | M2 T19 S5 | S9 |
| 10883 | `ExPRp` | open | M2 T19 S5 | S9 |
| 10885 | `InitPlatformFall` | open | M2 T19 S5 | S9 |
| 10898 | `StopPlatforms` | open | M2 T19 S5 | S9 |
| 10904 | `PlatformFall` | open | M2 T19 S5 | S9 |
| 10916 | `ExPF` | open | M2 T19 S5 | S9 |
| 10921 | `YMovingPlatform` | open | M2 T19 S5 | S10 |
| 10933 | `SkipIY` | open | M2 T19 S5 | S10 |
| 10935 | `ChkYCenterPos` | open | M2 T19 S5 | S10 |
| 10941 | `YMDown` | open | M2 T19 S5 | S10 |
| 10943 | `ChkYPCollision` | open | M2 T19 S5 | S10 |
| 10947 | `ExYPl` | open | M2 T19 S5 | S10 |
| 10952 | `XMovingPlatform` | open | M2 T19 S5 | S11 |
| 10959 | `PositionPlayerOnHPlat` | open | M2 T19 S5 | S11 |
| 10969 | `PPHSubt` | open | M2 T19 S5 | S11 |
| 10970 | `SetPVar` | open | M2 T19 S5 | S11 |
| 10973 | `ExXMP` | open | M2 T19 S5 | S11 |
| 10977 | `DropPlatform` | open | M2 T19 S5 | S11 |
| 10982 | `ExDPl` | open | M2 T19 S5 | S11 |
| 10987 | `RightPlatform` | open | M2 T19 S5 | S11 |
| 10995 | `ExRPl` | open | M2 T19 S5 | S11 |
| 10999 | `MoveLargeLiftPlat` | open | M2 T19 S5 | S12 |
| 11003 | `MoveSmallPlatform` | open | M2 T19 S5 | S12 |
| 11007 | `MoveLiftPlatforms` | open | M2 T19 S5 | S12 |
| 11019 | `ChkSmallPlatCollision` | open | M2 T19 S5 | S12 |
| 11023 | `ExLiftP` | open | M2 T19 S5 | S12 |
| 11031 | `OffscreenBoundsCheck` | open | M2 T19 S5 | S13 |
| 11041 | `LimitB` | open | M2 T19 S5 | S13 |
| 11042 | `ExtendLB` | open | M2 T19 S5 | S13 |
| 11074 | `TooFar` | open | M2 T19 S5 | S13 |
| 11075 | `ExScrnBd` | open | M2 T19 S5 | S13 |

## Shared verification and delivery

ROM logic evidence compares unchanged original execution at the declared
entry/exit, all feasible control branches, tables, RAM/scratch, call order and
live register results. Source-reachable NMI routes or declared controlled RAM
inputs at naturally reached entries are allowed; never patch ROM, PC, CPU
registers, hardware stack or outputs. Exclude hardware-stack storage only;
mapped $0109-$0139 variables remain checked. Include VRAM buffers, OAM and
audio queue writes where the scoped chain owns them. Record infeasible branch
sides with source justification rather than silently excluding them.

The independent operational track covers focused native contracts on x86/x64,
strict C90 builds, DOS16 link, platform purity, hidden-window response and all
three owner-authorized assets/mysmb16.exe, mysmb32.exe and mysmb64.exe per P.
Keep prior actual matches and their remaining differences. T closure combines
all chain routes in one integrated regression; no repeated per-label build or
new paperwork S. DOS remains link-only until separate graphical/runtime proof.

Reuse existing local owner-ROM/disassembly provenance under source policy;
no third-party translation import. Raw traces, derived program data, logs and
intermediates stay under ignored build output. Source-order successors own
relative/offscreen, bounding-box, collision, drawing and audio descendants.
T40's 1,374 actual differences remain explicit obligations, not T41 credit.

## S1 admission: bridge collapse

Coordinator accepts transfer-195 under the continuing approved M2 mandate.
The six scoped/expected names are BridgeCollapseData, BridgeCollapse, SetM2,
MoveD_Bowser, RemoveBridge and NoBFall. All are open; baseline 1,166/1,992,
maximum 1,172. Source $CFDD-$D060 includes the 15-byte table and original
BridgeCollapse entry, ending at its BowserGfxHandler/KillAllEnemies tails.
S2 is Bowser control; no later body is silently migrated by S1.

Shared owner is bridge.c. Preserve ObjectOffset, source mode-task increment,
full KillAllEnemies tail, timer underflow, body toggle, scratch $04/$05,
RemBridge parameters, MoveVOffset's Y-derived result, audio queues, final
InitVStf and state $40, and the unconditional graphics tail on normal/falling
paths. Remove invented slot/index/buffer eligibility guards where absent in
the original valid-state contract. Correct address provenance. The existing
return-valued victory adapter must not duplicate the original task increment.

Use shared KillAllEnemies, InitVStf and MoveEnemySlowVertically owners.
RemBridge/MoveVOffset remain the area owner's child seams; exposing the
existing MoveVOffset tail as a typed Y-input helper is allowed to preserve
one owner and child-call identity, with no unrelated area algorithm repair.
BowserGfxHandler remains an explicit existing child pending S3. S1 compares
its complete input and reports actual output differences independently; no
graphics descendant receives S1 credit.

Original route: VictoryMode task zero from unchanged NMI, controlling absent
and present Bowser, state 0/$40/other, Y below/at $E0, feet timer 0/1/2,
all fifteen table offsets and both valid front slots. Native mutation tests
check source writes, fresh post-child ObjectOffset reads and preserved Y and queue order.
Focused target is mysmb.bridge-collapse-chain, alongside prior victory and
Bowser baselines. Compare caller and actual children separately, retain all
10,804 prior actual matches, run all three builds and refresh EXEs at P closure.

Similar-issue sweep covers bridge entry/caller, source kill and vertical-init
children, VRAM offset consumers, legacy Bowser graphics calls and mode-task
ownership. Out-of-scope defects retain their planned chain. Raw recording is
bounded to 512 original cases, 16 MB and twenty seconds per run under ignored
build/m2-t41-s1; unique paths/checkpoints support resumption. Coordinator owns
cleanup and retains only inputs needed by dependent regressions. Closure
requires six exact dispositions, both proof tracks, ledger/tracker agreement
and artifact hashes. Stop on hidden mismatches or unadmitted child repair.

## S1 source audit and implementation checkpoint

This is an open implementation checkpoint, not P closure or node credit.
Direct inspection of the owner ROM confirms the 15-byte table at $CFDD and
50 instructions in $CFEC-$D060. Six conditional branches are at $CFF3,
$CFF9, $CFFD, $D003, $D018 and $D051. Execution coverage is still pending.

| Node | Source contract | Current C implementation |
| --- | --- | --- |
| BridgeCollapseData | Fifteen ordered axe/chain/bridge addresses | Existing table bytes independently match local ROM |
| BridgeCollapse | Select front slot, test ID, then store ObjectOffset | Slot eligibility guard removed; ObjectOffset store restored |
| SetM2 | Music silence, increment mode task, full KillAllEnemies tail | Shared erase owner called; victory caller no longer overwrites task |
| MoveD_Bowser | MoveEnemySlowVert then BowserGfxHandler | Both child calls restored in original order |
| RemoveBridge | Timer/body/scratch stores, RemBridge, MoveVOffset, sounds, offset and InitVStf | Shared init/area seams and post-RemBridge ObjectOffset reload restored |
| NoBFall | Unconditional BowserGfxHandler tail | Same shared graphics entry used on timer wait and removal paths |

The seven source call/jump edges are KillAllEnemies ($D071),
MoveEnemySlowVert ($BF8C), BowserGfxHandler ($D17B, two sites), RemBridge
($8ACD), MoveVOffset ($8A8F), and InitVStf ($C363). Existing RemBridge leaves
Y unchanged; MoveVOffset consumes that preserved value rather than rereading
VRAM_Buffer1_Offset. Its prior area implementation is now one shared helper.
Existing child bodies are unchanged, including the known incomplete Bowser
renderer. Removing bridge guards does not claim arbitrary corrupt indices
are a supported game-state contract; original table indices 0..14 are covered.

Independent mutation contracts currently pass 319 cases per native width:
all fifteen removal stages at four buffer offsets, all 255 non-expiring timer
bytes including underflow, and absent/defeated/falling state gates. They check
full RAM footprints and child sequence, including a child-mutated ObjectOffset
and live VRAM offset. Changed C units pass strict C90 x86/x64 compilation;
platform purity passes. These tests do not constitute original-ROM execution
proof. Completion remains 1,166/1,992, all six scoped nodes still open.

Next action is the bounded original NMI bridge-route recorder and caller/
actual-child comparison, followed by cross-chain regression, full three-target
builds, refreshed EXEs and P review. Current assets still belong to 9b3ff3f;
no new artifact or completed P is claimed by this checkpoint. Local neutral
structure/native summaries are under ignored build/m2-t41-s1.

## S1 original bridge collapse proof

S1 P1 closes all six expected caller/data nodes: 1,166 -> 1,172/1,992.
No scoped unfinished node or transfer remains. S2 is next in the approved
plan. The still-incomplete BowserGfxHandler body remains with its original
receiver until planned S3 admission; this proof does not give it node credit.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| BridgeCollapseData | $CFDD | All fifteen collapse-table bytes and consumers match original ROM. New ROM-match complete. |
| BridgeCollapse | $CFEC | Front-slot selection, ID gate, ObjectOffset write and state branches match. New ROM-match complete. |
| SetM2 | $D005 | Music silence, byte task increment and complete KillAllEnemies tail match. New ROM-match complete. |
| MoveD_Bowser | $D00F | Source slow-vertical child followed by Bowser graphics tail matches. New ROM-match complete. |
| RemoveBridge | $D015 | Timer/body/scratch order, area children, audio, offset and final InitVStf/state writes match. New ROM-match complete. |
| NoBFall | $D05E | All normal-state exits reach the original unconditional graphics child. New ROM-match complete. |

All 50 instructions in $CFEC-$D060 and all fifteen data entries at $CFDD
execute in 180 unchanged original NMI routes through VictoryMode task zero.
All six conditional branches have both outcomes. Routes cover slots zero/four,
all fifteen bridge stages, expired/unexpired/underflowing feet timers, absent
Bowser, state $20/$40/zero and vertical positions below/at $E0. Original NMI
and children run normally: no ROM, CPU/register, PC, stack or output patch.
All 180 observer-free frames equal the observed originals. This verifies
observer noninterference, not native full-game frame equality.

Caller-boundary comparisons pass 360/360 across x86/x64. Complete child
entry RAM is checked before diagnostic recorded-return substitution; source
slot/Y arguments, RemBridge graphics index and unchanged Y are explicit.
All scratch and mapped $0109-$0139 variables remain checked. Only hardware
stack storage is excluded. VRAM/OAM/audio-queue RAM remains in the comparison.

Actual-child execution matches 72/360. Independent child isolation on each
original input proves KillAllEnemies 72/72, MoveEnemySlowVert 16/16,
RemBridge 120/120, MoveVOffset 120/120 and InitVStf 8/8. BowserGfxHandler
matches 0/288: its existing approximate renderer omits duplicate-slot writes,
source scratch, graphics/collision child effects and corresponding OAM output.
Every failed root has that failed graphics child. This is the named S3
dependency gap, not a hidden caller failure or a full-game equivalence claim.

Shared bridge.c now sets ObjectOffset, preserves original timer/body/scratch
write order, calls the full erasure and vertical-init owners, and reaches
BowserGfxHandler on every source normal/falling path. SetM2 increments the
mode task itself; the victory adapter no longer overwrites it. MoveVOffset is
one shared area helper taking preserved Y, independent of child-mutated RAM
offset. The existing area caller uses the same helper. Non-source bridge
slot/index/buffer gates are removed; original table inputs 0..14 are tested.
No unrelated area, Bowser graphics, collision or platform algorithm is changed.

Native mutation contracts pass 319 cases per width, checking full RAM and
child order, all non-expiring timer values, all table stages at four buffer
offsets and mode-byte wrap. Fifteen initializer/platform suites per width,
mode/layout tests and platform purity pass. Existing Bowser damage smoke
exit 4 and endgame star-timer exit 6 remain unchanged. The final actual-root
matrix is 10,876/12,538; all 10,804 prior matches remain. Its 1,662 differences
comprise 1,374 pre-existing cases and the 288 named Bowser graphics cases.

All 101 shared units build in strict C90 for x86/x64. Both self-tests and
hidden-window response probes pass. DOS16 compiles/links with the existing
OLDNAMES warning and remains link-only: graphical playability, resource binding
and physical 486SX performance are not certified. All three EXEs are refreshed.

Similar-issue sweep covers the bridge/victory caller, full erase/vertical
initialization owners, both MoveVOffset consumers and existing graphics entry.
There is one task-increment owner and one area-offset helper; no host gameplay.
Reproduce bridge_collapse_fixture.h cases 0..179 with
--fixture=t41-bridge-collapse=N, --bridge-collapse-snapshot,
--control-children and separate --pc-coverage recording. The caller checker
is bridge_collapse_snapshot_check; enemy_loop_actual_check runs real children.
Native target is mysmb.bridge-collapse-chain. Source/child/regression summaries
remain below ignored build/m2-t41-s1. Original inputs use unique paths,
twenty-second recorder deadlines and resumable checkpoints; coordinator retains
needed regression inputs and owns cleanup. Provenance and local-only source
restrictions are unchanged.

Raw original records occupy 2910792 bytes, below the declared 16-MB bound.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256515 | f55328eb0ba71c6deacde47e179446e3f33e3564ad3a0d0568d07dba94942b0e |
| mysmb32.exe | 348975 | 1ba445479a71827b6cd3ad86a131564f0c06542df0d19ad0de2fcc49ac84cb20 |
| mysmb64.exe | 356587 | df175a55eb0d8932e602190f94bb4c2b99ce03d14c00c24c95763ab61e633234 |

## S2 admission: Bowser control and defeated erasure

S1 closed in 1211e9e. Coordinator accepts transfers-196/197 under the
continuing M2 mandate. Source $D061-$D17A (lines 10156-10288) contains
nineteen nodes: seventeen open expected new, two retained complete. Baseline
1,172/1,992, maximum 1,189. Exact sets are listed below in source order.

Expected new (all open): `PRandomRange`, `RunBowser`, `BowserControl`, `ChkMouth`, `FeetTmr`, `ResetMDr`, `B_FaceP`, `GetPRCmp`, `GetDToO`, `CompDToO`, `HammerChk`, `SetHmrTmr`, `SkipToFB`, `MakeBJump`, `ChkFireB`, `SpawnFBr`, `SetFBTmr`.

Retained complete: `KillAllEnemies`, `KillLoop` (existing T38 S1 proof).

Create one shared enemy/bowser.c owner for RunBowser and BowserControl.
Remove the old approximate objects.c body and dispatch wrapper; legacy bulk
eligibility remains in objects.c before calling the same original entry.
Remove its invented inline player injury check; source collision belongs to
ProcessBowserHalf under planned S3. No gameplay moves into a host adapter.

Preserve defeat-height branch to MoveD_Bowser or full KillAllEnemies; frenzy
clear; TimerControl jumping to flame checks; mouth sign jumping to HammerChk;
feet toggle, facing reset and PlayerEnemyDiff returned page sign/scratch;
$C8 movement bypass; frame-gated range/random walk using signed byte result;
gravity then world/frame-gated hammer spawn; fresh Y/PRNG reads; InitVStf
jump setup; worlds 6/7 flame exclusion and world 8 inclusion; flame-timer
toggle loop, SetFlameTimer returned A and hard-mode subtraction; graphics tail.
No extra flag/ID/front-slot store or invented collision branch at RunBowser.

Reuse KillAllEnemies in enemy/loop.c, movement, hammer, distance and flame
timer owners. Extract S1's existing two-call MoveD_Bowser into one named shared
entry used by bridge and Bowser; this is dependency reuse, no extra node credit.
Retain the existing BowserGfxHandler child pending S3 and report its actual
output gaps separately. Keep typed live register returns at child seams;
source child input and original slot-reload semantics must be explicit.

Logic track: original NMI actor-vector RunBowser routes, controlled RAM inputs
at naturally reached entries if needed, all feasible branches, four table
bytes, scratch/queues and child call order. Preserve original ROM/CPU/PC/stack
and outputs. Compare complete child inputs before any diagnostic return
substitution and retain separate actual-child execution. Revalidate the two
retained erase nodes and all 10,876 prior actual matches; no duplicate credit.

Operational track: mysmb.bowser-control-chain native mutation contracts on
x86/x64, strict C90 full builds, DOS16 link, platform purity, original bridge
regression, actor dispatch, hidden-window response and three refreshed EXEs.
S closure names every disposition and updates tracker/ledger only with proof.
Existing graphics/collision gaps and DOS link-only limits remain explicit.

Similar-issue sweep covers actor and legacy callers, duplicate drawing,
defeated movement, world-number constants, timer/mouth gates, signed page/byte
distance, post-child loads and non-source injury. Existing owner ROM/listing
provenance and local-only restrictions remain. All temporary material stays
under ignored build/m2-t41-s2; at most 1,024 original cases, 32 MB raw output,
twenty-second per-record timeout and resumable unique checkpoints. Coordinator
owns cleanup and retains inputs required by dependent regression. Stop on
unadmitted child repair, source execution/output patches or hidden mismatch.

## S2 source audit and implementation checkpoint

S2 remains open with no new node credit. Direct owner-ROM inspection binds
four PRandomRange bytes and 122 instructions in $D065-$D17A, including the
retained erase loop. Original execution/branch coverage is still pending.

The source RunBowser now has one body in enemy/bowser.c. The former objects.c
approximation and dispatch wrapper are removed; only legacy bulk flag/ID
eligibility remains outside the source entry. MoveD_Bowser is one shared
slow-gravity/graphics tail in bridge.c. The source gravity child reloads X
from ObjectOffset; the C tail and Bowser caller preserve that handoff.

The implementation restores defeat-height erasure, TimerControl-to-flame and
mouth-to-hammer edges, page-sign distance, the $C8 movement bypass, signed
byte range comparison, hammer calls, post-child coordinate/PRNG reads and
jump initialization. World6 and World8 are source indices five and seven.
PRandomRange uses PseudoRandomBitReg at $07A7 plus slot, not the old off-by-one
$07A8 address. Mouth toggling retains its backward flame-check edge and the
SetFlameTimer return/hard-mode subtraction. Source graphics is called once;
the invented inline player injury check is removed in favor of planned S3's
ProcessBowserHalf collision responsibility. No graphics child body is repaired.

Twelve independent full-RAM and call-order cases pass on both native widths,
covering defeat, master timer, mouth state, world gates, post-hammer PRNG,
signed distance, $C8 skip and flame toggling. S1's 319-case native contract and
retainer contracts also pass on both widths. All 360 existing original bridge
caller comparisons remain equal after the shared tail extraction. Changed
owners compile under strict C90 on x86/x64; platform purity passes.

Next action is unchanged original NMI RunBowser recording with branch/data
coverage, caller and actual-child comparisons, followed by retained cross-chain
regression and three-target artifact delivery. Counts remain 1,172/1,992;
assets still belong to 1211e9e. This checkpoint is not a P or closure claim.
Local structure/native/bridge regression summaries stay below ignored
build/m2-t41-s2.

## S2 original Bowser control proof

S2 P1 closes seventeen expected new nodes and revalidates two retained nodes:
1,172 -> 1,189/1,992. All nineteen scoped nodes are complete; none remains
unfinished or transfers at closure. S3 is next for the four Bowser graphics
orchestration nodes; its body is not certified by this caller proof.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| PRandomRange | $D061 | Four original bytes and both PRNG consumers; source base $07A7 plus slot. New ROM-match complete. |
| RunBowser | $D065 | Defeat bit and $E0 height choose shared MoveD_Bowser or complete erasure. New ROM-match complete. |
| KillAllEnemies | $D071 | Retained shared reverse-slot erase loop and frenzy clear; no duplicate credit. Retained ROM match. |
| KillLoop | $D073 | All five original erase child inputs in descending slot order; retained proof. Retained ROM match. |
| BowserControl | $D07F | Frenzy clear and master timer branch directly to flame checks. New ROM-match complete. |
| ChkMouth | $D08C | Mouth sign chooses feet/movement or HammerChk, without skipping jump handling. New ROM-match complete. |
| FeetTmr | $D094 | Byte decrement, expiry reset and body-bit toggle order. New ROM-match complete. |
| ResetMDr | $D0A6 | Every-sixteenth-frame facing reset. New ROM-match complete. |
| B_FaceP | $D0B0 | Timer gate, typed distance/page sign, facing/speed/timers and $C8 bypass. New ROM-match complete. |
| GetPRCmp | $D0D1 | Every-fourth-frame and original-X gates select PRandomRange. New ROM-match complete. |
| GetDToO | $D0EA | Byte X addition, facing branch and signed wrapped difference. New ROM-match complete. |
| CompDToO | $D107 | Absolute byte range chooses original left/right movement speed. New ROM-match complete. |
| HammerChk | $D10F | Timer priority, slow gravity and world/frame-gated hammer child. New ROM-match complete. |
| SetHmrTmr | $D127 | Fresh post-child Y/PRNG reads and timer store. New ROM-match complete. |
| SkipToFB | $D139 | Source jump to flame checks from timer hold or completed gravity phase. New ROM-match complete. |
| MakeBJump | $D13C | Timer-one Y decrement, InitVStf then upward speed store. New ROM-match complete. |
| ChkFireB | $D149 | World 8 inclusion and worlds 6/7 exclusion use zero-based constants. New ROM-match complete. |
| SpawnFBr | $D154 | Breath timer, body toggle, backward edge and SetFlameTimer return. New ROM-match complete. |
| SetFBTmr | $D173 | Hard-mode subtraction, breath timer, frenzy store and graphics fallthrough. New ROM-match complete. |

All 122 instructions in $D065-$D17A execute; all 25 conditional branches
have both outcomes. The four PRandomRange bytes bind directly to the local
original ROM. The 1,024 routes start from the real NMI actor vector and apply
declared RAM inputs at the naturally reached RunBowser entry. They cover
slots zero/five, defeat heights, master timer, mouth/feet, frame gates,
player/enemy pages, signed X/range, timers, worlds, PRNG and hard mode.
Observer choice never controls inputs. No ROM, CPU/register, PC, stack or
output patch is used. All 1,024 observer-free frames equal their observed
original counterparts; this is not native full-game frame equality.

Caller comparisons pass 2,048/2,048 across x86/x64, including source scratch,
queue stores, complete child inputs and live distance/flame A returns.
KillAllEnemies and MoveD_Bowser execute their actual shared C bodies in this
caller check; recorded returns apply only at their observed descendant seams.
Five descending erase calls preserve the retained KillAllEnemies/KillLoop
proof. RAM comparisons include mapped $0109-$0139 and all VRAM/OAM/audio
queue cells; only hardware-stack storage is excluded.

Actual roots match 16/2,048. Per-child isolation on the same original input
states proves EraseEnemyObject 80/80, MoveEnemySlowVert 516/516,
PlayerEnemyDiff 744/744, SpawnHammerObj 92/92, InitVStf 368/368 and
SetFlameTimer 512/512. BowserGfxHandler matches 0/2,032; every failed root
contains this known approximate graphics child. Missing duplicate-slot,
scratch, OAM and collision effects retain their S3/later-child responsibility.
No recorded substitution is used in the actual-root or isolated-child runs.
External nodes receive no incidental completion credit.

RunBowser has one shared body in enemy/bowser.c. The old objects.c body and
double-draw dispatch wrapper are removed; bulk eligibility stays outside the
original entry. The shared MoveD_Bowser tail reloads the original ObjectOffset
after gravity and is reused by bridge and Bowser. Timer/mouth/range branches,
post-child reads, hammer spawning and the flame backward edge now follow
source order. Random reads use $07A7 plus slot. The source graphics child
replaces the fabricated inline proximity/injury check; its internal repair
belongs to S3, so gameplay fidelity remains incomplete until that chain and
its dependencies are proved. No platform algorithm changes.

Independent native contracts pass twelve full-RAM/call-order cases on both
widths. S1 native and retainer contracts pass, and all 360 prior original
bridge caller comparisons remain equal after shared-tail extraction. Fifteen
initializer/platform suites per width, mode/layout tests and platform purity
pass. Existing Bowser damage exit 4 and endgame star-timer exit 6 persist.
Final actual-root matrix: 10,892/14,586, retaining all 10,876 previous matches.
The 3,694 differences are 1,662 retained cases plus 2,032 new graphics-child
cases. These are sample counts, not unfinished-node counts.

All 102 shared units compile under strict C90 for x86/x64. Self-tests and
hidden-window message-response probes pass on both widths. DOS16 compiles
and links with the existing OLDNAMES warning; it remains link-only without
graphical playability, resource binding or 486SX performance certification.
The three owner-authorized executable artifacts are refreshed together.

Similar-issue sweep covers actor/bulk callers, duplicate drawing, world
constants, PRNG base, signed page/byte differences, master/mouth gates,
post-child X/PRNG reads and non-source injury. The source entry has no extra
flag/ID/front-slot store. S3 remains the next original graphics boundary.
Reproduce bowser_control_fixture.h cases 0..1023 using
--fixture=t41-bowser-control=N, --bowser-control-snapshot, --control-children
and separate --pc-coverage runs. bowser_control_snapshot_check checks caller
handoffs; enemy_loop_actual_check executes real children. Native target is
mysmb.bowser-control-chain. Local source/child/regression summaries stay under
ignored build/m2-t41-s2. Raw inputs occupy 17,784,774 bytes under the 32-MB
bound, with unique paths, twenty-second deadlines and resumable checkpoints.
Coordinator retains required regression inputs and owns cleanup. Existing
source provenance and local-only restrictions remain unchanged.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256131 | 5f144368ee82f50ab4bcfc0266acc5477b904ab732b05f9577f39b97f37457e5 |
| mysmb32.exe | 348709 | d930ff6ade69f2c95805542ebb0e008577c093e210a8d93f34881588e9b72d07 |
| mysmb64.exe | 356357 | d27da7a6362a533f5f65a90a7b21121bc9a6ed24e023e33cc98c4682577af635 |

## S3 admission: Bowser front and rear orchestration

S2 closed in c8e1cf1. Coordinator accepts transfer-198 under the continuing
approved M2 mandate. Scope and expected-new set are the same four open nodes,
in source order: `BowserGfxHandler`, `CopyFToR`, `ExBGfxH`,
`ProcessBowserHalf`. Baseline 1,189/1,992; maximum 1,193. Original entry/exit
is $D17B-$D1D0, lines 10289-10332, before FlameTimerData. The sole chain
owner remains oam/bowser_gfx.c, called by S1/S2; no duplicate control owner.

Restore front processing, fresh post-child direction and coordinates, byte
X offset without page carry, Y+8, state/direction copy into DuplicateObj_Offset,
saved ObjectOffset, rear ID and second-half processing, then restore offset
and clear BowserGfxFlag. Each half increments the graphics flag, runs
RunRetainerObj, checks fresh enemy state, assigns bounding control ten only
for state zero, and calls GetEnemyBoundBox then PlayerEnemyCollision.
Preserve original live-X handoffs; do not invent eligibility or injury tests.

Dependencies remain separate: RunRetainerObj's original three-call wrapper,
relative/offscreen helpers, EnemyGfxHandler, bounds and player collision.
The existing retainer graphics seam currently accepts only retainer ID 53.
Dependency wiring may extract the existing Bowser single-half renderer and
select it there using BowserGfxFlag, preserving a renderable product while
replacing the approximate two-half orchestration. This grants no child-node
credit and does not authorize rewriting generic graphics/collision algorithms.
Legacy bulk eligibility stays outside the original entry. No host changes.

Logic proof: original NMI Bowser actor routes naturally reaching $D17B,
controlled RAM input without ROM/CPU/PC/stack/output patching; both direction
and state branches, duplicate-slot and byte-wrap cases, flag and ObjectOffset
restoration. Compare full child inputs before any recorded-return diagnostic,
and retain separate real-child execution and remaining discrepancies.
Retain all 10,892 prior actual matches and S1/S2 caller proofs. Node credit
requires original source/branch/write and route evidence, not native tests.

Operational proof: mysmb.bowser-graphics-chain independent mutation contracts,
retainer and prior Bowser/bridge suites, strict C90 x86/x64 full builds,
DOS16 link, platform purity, hidden-window probes and three refreshed EXEs.
DOS remains link-only. One chain/P delivery covers all four nodes together.
Similar-issue sweep covers flag/ID guards, duplicate-slot/page writes, saved
versus fresh child state, double drawing, state gates and invented collisions.

Existing owner-ROM/listing provenance and local-only restrictions apply.
Unique ignored build/m2-t41-s3 outputs: up to 1,024 cases, 32 MB raw traces,
twenty-second per-record timeout, resumable checkpoints. Coordinator owns
cleanup and retains dependent regression inputs. Stop on unadmitted child
repair, hidden mismatches or execution patches. No node is complete yet.

## S3 implementation checkpoint

S3 remains active; no node credit or P closure. Direct original-ROM decoding
identifies forty instructions and two conditional branches in $D17B-$D1D0.
Runtime branch coverage and original child-entry/return comparison are pending.

The shared Bowser graphics owner now processes the front, copies original
byte coordinates/state/direction into the duplicate slot, processes the rear,
restores ObjectOffset and clears BowserGfxFlag. Per-half logic calls the
existing retainer chain, then bounding and player collision only for fresh
state zero. Source child X reloads are explicit. The former direct two-half
renderer is removed; its existing individual rows are selected through the
retainer graphics seam. Generic graphics/collision interiors remain unproved.

Twenty-four independent full-RAM/call-order scenarios pass on each native
width: opposite initial/post-draw states, direction and coordinate mutation,
byte wrap without page writes, slots zero/five and graphics flag wrap.
Retainer OAM tests pass on both widths; platform purity passes. The legacy
Bowser movement fixture omitted InitBowser's distinct duplicate slot and
therefore aliased its front after the faithful copy; supplying that existing
source precondition restores the prior result. Existing Bowser damage exit 4
and endgame exit 6 remain explicit. These results do not prove ROM equality.

Next: record naturally reached BowserGfxHandler with original child seams,
compare forty-instruction/two-branch execution and actual-child output,
retain prior root matches, then run the single three-target delivery pass.
Progress stays 1,189/1,992; the three assets still belong to c8e1cf1.
Ignored build/m2-t41-s3 holds source-audit and native checkpoint results.

## S3 original front/rear proof

S3 P1 closes all four expected nodes: 1,189 -> 1,193/1,992. No scoped node
remains unfinished or transfers at closure. This certifies the original
orchestration, not the unproved generic graphics or collision descendants.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| BowserGfxHandler | Front call, fresh child state and duplicate-slot handoff, saved ObjectOffset, rear ID and second call. ROM-match complete. |
| CopyFToR | Both direction offsets, byte X/Y wrap without page carry and ordered state/direction writes. ROM-match complete. |
| ExBGfxH | Normal/non-normal half exits, final ObjectOffset restore and graphics-flag reset. ROM-match complete. |
| ProcessBowserHalf | Flag increment, RunRetainerObj, fresh state gate, bounding control ten, bounds then player collision. ROM-match complete. |

Direct original-ROM decoding and execution cover all forty instructions in
$D17B-$D1D0 and both sides of both conditional branches. The 512 routes enter
through the real NMI actor vector; declared RAM inputs apply at naturally
reached BowserGfxHandler regardless of observer selection. No ROM, CPU, PC,
stack or output patches are used. All observer-free output frames equal their
observed original frames; this does not assert native whole-game equality.
Source return checks verify each child's live X equals ObjectOffset.

Caller comparisons match 1,024/1,024 across x86/x64, checking every child input
before using recorded diagnostic returns and all final RAM, including mapped
$0109-$0139 and OAM/VRAM/audio queues. Only hardware stack storage is excluded.
Cases cover front slots zero/five, rear slots one/four, both directions,
state-zero/nonzero gates, coordinate wrapping, independent page locations,
body controls and graphics-flag byte wrap. These are the four nodes' evidence.

Actual-child roots match 0/1,024. Independent original child-input isolation
finds RunRetainerObj 0/2,048, GetEnemyBoundBox 0/512 and PlayerEnemyCollision
432/512. These descendants remain with their existing source-order receivers;
the retained RunRetainerObj caller proof does not certify its graphics body.
No child receives incidental credit. No substitution occurs in these actual
comparisons. Full-game Bowser fidelity remains incomplete.

The production chain has one owner in oam/bowser_gfx.c. It calls the original
front/rear sequence and state-gated bounding/player collision children, uses
fresh child state, copies duplicate-slot bytes without invented page writes,
and restores ObjectOffset/graphics flag. The old direct two-half orchestration
is removed. Existing single-half rows are wired through the graphics seam;
their generic scratch/flip limitations remain explicit, not newly certified.
Legacy bulk eligibility remains outside the original entry. No platform logic.

Twenty-four independent full-RAM/call-order scenarios pass per native width.
Retainer OAM and fifteen initializer/platform suites per width pass. The
legacy Bowser fixture now supplies InitBowser's distinct rear slot; without
it the new faithful copy aliases the front. Existing damage exit 4 and endgame
exit 6 remain. Platform purity passes. The final actual matrix is
10,892/15,610, retaining every prior 10,892 match with zero regressions.
The 4,718 differences are 3,694 prior cases plus 1,024 new child-gap cases.
Prior S1/S2 caller owners and their child-substitution contracts are unchanged.

All 102 shared units compile under strict C90 on x86/x64. Both executable
self-tests and hidden-window message probes pass. DOS16 compiles/links with
the existing OLDNAMES warning; DOS remains link-only without graphical,
resource-binding or 486SX performance certification. Three EXEs are refreshed.

Similar-issue sweep covers source guards, duplicate/page writes, fresh child
state, flag wrap, double drawing, collision gates and legacy fixture setup.
Reproduce bowser_graphics_fixture.h cases 0..511 with
--fixture=t41-bowser-graphics=N, --bowser-graphics-snapshot, --control-children
and independent --pc-coverage. bowser_graphics_snapshot_check checks caller
handoffs; enemy_loop_actual_check uses real children. Native target is
mysmb.bowser-graphics-chain. Local bounded evidence is under ignored
build/m2-t41-s3, with twenty-second run deadlines and resumable checkpoints.
Coordinator retains regression inputs and owns cleanup. Existing source
provenance and local-only restrictions remain. S4 flame actor is next.

Raw trace output: 10696545 bytes, below the 32-MB limit.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256099 | a67b78c8217779efc8f18b500d8b21f3ba1bfd8ae9d6ae42697461b0d9495d00 |
| mysmb32.exe | 348823 | c79175ee05d1a0c87ccda83570e57e3b808b460ff21e7a1c4e66152852bb7055 |
| mysmb64.exe | 356981 | a5a00641af5687c2195275c240cd402f5ffc401f135cfc3144339b1b27e78be2 |

## S4 admission: flame timer and full flame actor

S3 closed in f3617ca. Coordinator accepts transfers-199/200 under the continuing
M2 mandate. Scope is twelve source-ordered nodes in $D1D1-$D294, lines
10337-10434. Baseline 1,193/1,992; nine expected new, maximum 1,202.

Retained complete: `FlameTimerData`, `SetFlameTimer`, `ExFl`.

Expected new (all open): `ProcBowserFlame`, `SFlmX`, `SetGfxF`, `FlmeAt`, `DrawFlameLoop`, `M3FOfs`, `M2FOfs`, `M1FOfs`, `ExFlmeD`.

Move ProcBowserFlame out of objects.c into enemy/bowser_flame.c; keep the
source SetGfxF-to-ExFlmeD tail in oam/bowser_flame_gfx.c. Reuse the timer owner
in enemy/frenzy.c. Share the existing FlameYPosData binding with its initializer
instead of another copied table; this is dependency reuse without new credit.
Preserve timer bypass, hard-mode force, scratch zero, fractional/X/page borrow,
unmasked source-valid PRNG index, Y target/force and RelativeEnemyPosition.
The state gate precedes tile/attribute scratch; the three-sprite loop mutates
relative X and scratch tile each iteration, wraps Y indexing as a byte, reloads
ObjectOffset, calls GetEnemyOffscreenBits and applies all four low-bit masks,
including the source residual fourth-sprite Y write. No new entry guards.
Collision and terminal bounds stay in the existing RunBowserFlame caller.

Dependencies: completed S3 precedes this source slice; S5 RunFireworks follows.
Relative/offscreen and initializer/RunBowserFlame/timer bodies keep their own
proof states. No unrelated graphics, collision, platform or frame-loop repair.
Similar-issue sweep covers duplicate table/owner, flags/slot guards, scratch
writes, byte/page borrow, OAM addressing and offscreen residual writes.

Logic proof compares original naturally reached ProcBowserFlame and timer
routes, all source branches and table consumers, child inputs and final RAM;
separate actual-child comparisons retain lower-level gaps. No original ROM,
CPU/register, PC, stack or output patches. Retain all 10,892 previous actual
matches and the three timer nodes' existing evidence; no duplicate credit.
Operational proof covers mysmb.bowser-flame-chain native cases, initializer
and actor regression, strict C90 x86/x64, DOS16 link, platform purity, hidden
window probes and all three EXEs once per P. DOS remains link-only.

Existing local owner ROM/listing provenance and restrictions remain. Every
temporary file stays under ignored build/m2-t41-s4. Original runs have unique
paths, twenty-second per-record deadlines, up to 1,024 cases and 32 MB raw
output, resumable checkpoints and coordinator cleanup ownership. Stop on
unadmitted child repair, execution patches or hidden discrepancies. No node
credit until original proof and operational delivery are complete.

## S4 implementation checkpoint

S4 remains active with no new credit or P closure. Original-ROM decoding
identifies ninety instructions and ten branches in $D1D9-$D294, plus the eight
FlameTimerData bytes. The four existing FlameYPosData dependency bytes are
also directly bound to the owner ROM. Runtime coverage is still pending.

ProcBowserFlame now has one owner in enemy/bowser_flame.c. The former guarded
objects.c implementation is removed. Movement preserves scratch zero,
fractional/X/page borrow, the source-valid unmasked Y index and Y force.
Initializer and movement share one Y-data binding. The graphics tail calls
RelativeEnemyPosition, reloads ObjectOffset, gates on fresh state, writes
tile/attribute scratch and advances the shared relative X inside the three
sprite loop. It reloads the source OAM offset after the offscreen child and
preserves all four mask writes, including the residual fourth sprite.
No platform changes or added gameplay rule.

Independent native testing passes 4,096 combinations per width, using a
24-bit fixed-point subtraction oracle for motion and covering both timer
and hard-mode states, state-gated drawing, all sixteen masks and both flips.
Existing 107,522 Bowser/flame initializer footprints per width and updated
flame OAM tests pass. The old OAM expectation incorrectly retained the initial
relative X; it now expects the source loop's +24 and supplies ObjectOffset
for its direct slot-two call. Existing Bowser damage exit 4 remains explicit.
Platform purity passes. Changed owners compile under strict C90 on x86/x64.

Next action is original NMI ProcBowserFlame recording with source branch,
child-input and final-state comparisons, timer proof retention, actual-child
gap isolation and cross-chain regression, then one three-platform delivery.
The legacy offscreen child's const API omits source scratch writes; it retains
its own proof debt. Test-only child mutation checks the caller's preservation
of those writes without claiming that dependency is fixed. Counts stay
1,193/1,992; assets still belong to f3617ca. Local source/native summaries are
under ignored build/m2-t41-s4. No implementation P has been committed yet.

## S4 original flame actor proof

S4 P1 closes nine expected new nodes and retains three timer nodes:
1,193 -> 1,202/1,992. All twelve scoped nodes complete; none remains
unfinished or transfers at closure. Unproved child bodies retain their owners.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| FlameTimerData | Retained original eight-byte binding and initializer consumers. Retained ROM match; no duplicate credit. |
| SetFlameTimer | Unchanged original counter increment/mask and indexed return; retained initializer route proof. Retained ROM match; no duplicate credit. |
| ExFl | Retained timer return and fresh actor non-normal-state return. Retained ROM match; no duplicate credit. |
| ProcBowserFlame | Master timer bypass and hard-mode force selection with original source entry. New ROM-match complete. |
| SFlmX | Scratch force, fractional/X/page borrow, Y data binding and unmasked source-valid index. New ROM-match complete. |
| SetGfxF | Relative child handoff, live-X restoration and state gate. New ROM-match complete. |
| FlmeAt | Original tile/attribute scratch and OAM start offset. New ROM-match complete. |
| DrawFlameLoop | Three byte-indexed OAM entries, incremented tile scratch and shared relative X. New ROM-match complete. |
| M3FOfs | Offscreen bit zero and residual fourth-sprite Y write. New ROM-match complete. |
| M2FOfs | Offscreen bit one and third-sprite Y write. New ROM-match complete. |
| M1FOfs | Offscreen bit two and second-sprite Y write. New ROM-match complete. |
| ExFlmeD | Offscreen bit three and first-sprite write or unchanged return. New ROM-match complete. |

Original execution covers all 83 actor instructions in $D1EB-$D294 and both
sides of all ten branches, including the state jump to shared ExFl. The seven
timer instructions retain T39 S1 execution proof; the timer C body is byte-for-
byte unchanged. The eight timer and four Y-data bytes bind to the local ROM.
All prior initializer matches remain after sharing the Y-data owner.

The 1,024 routes start from the actual NMI actor vector and apply declared
RAM inputs at naturally reached ProcBowserFlame. No ROM, CPU/register, PC,
stack or output patches are used. Every observer-free original output frame
equals its observed counterpart. This does not certify native whole-game
frames. Source child returns verify live X equals ObjectOffset.

Caller comparisons pass 2,048/2,048 on x86/x64, comparing full child inputs
before diagnostic recorded returns and final RAM including mapped
$0109-$0139, OAM/VRAM/audio queues. Only hardware stack storage is excluded.
Cases cover slots zero/five, timer and hard mode, force borrow, page wrap,
source Y indices/targets/force, state gates, both flips, OAM byte wrapping and
all four mask branches. The residual fourth-sprite write remains intentional.

Actual-child roots match 8/2,048. Independent original child-input checks:
RelativeEnemyPosition 114/2048; GetEnemyOffscreenBits 0/1926.
These helpers still omit original scratch effects; the offscreen adapter's
returned byte/store contract does not repair its internals. No substitution
is used in actual comparisons and no descendant gets incidental credit.
The full gameplay path remains incomplete. Their existing ledger receivers
retain responsibility rather than silently assigning their bodies to S4.

ProcBowserFlame now has one shared owner in enemy/bowser_flame.c; its source
graphics tail remains in oam/bowser_flame_gfx.c. Removed entry guards and
restored scratch, borrow, shared relative-X and original child order replace
the old objects.c approximation. Initializer and movement share one Y table.
RunBowserFlame still owns collision/bounds. No host gameplay changes.
The legacy bulk entry has no production callers and is not a new certified
runtime path. Similar-issue sweep includes table/owner duplication, guards,
scratch, borrow, OAM indexing, mask writes and direct-test ObjectOffset setup.

Independent 24-bit movement/OAM contracts pass 4,096 combinations per width;
107,522 initializer footprints per width and flame OAM tests pass. The direct
OAM test now expects source relative X+24 and supplies its slot-two offset.
Fifteen initializer/platform suites per width and platform purity pass.
Existing Bowser damage exit 4 remains explicit. Final actual matrix is
10,900/17,658: all prior 10,892 matches retained, plus eight new actor matches.
The 6,758 differences remain explicit child-gap samples, not node counts.

All 103 shared units compile as strict C90 for x86/x64. Self-tests and hidden
window message probes pass. DOS16 compiles/links with the existing OLDNAMES
warning; DOS is link-only, without graphical playability, resource-binding or
physical 486SX certification. All three owner-authorized EXEs are refreshed.

Reproduce flame_actor_fixture.h cases 0..1023 using
--fixture=t41-flame-actor=N, --flame-actor-snapshot, --control-children and
separate --pc-coverage. flame_actor_snapshot_check compares caller handoffs;
enemy_loop_actual_check uses real children. Native target is
mysmb.bowser-flame-chain. Ignored build/m2-t41-s4 holds bounded evidence,
twenty-second recording deadlines and resumable checkpoints. Coordinator
retains regression inputs and owns cleanup. Existing provenance/local-only
restrictions remain. S5 fireworks lifetime and score tail is next.

Raw trace output: 16897247 bytes, below 32 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255983 | 5e9d883c56be109eed0ad813b9fb5ee5d82ac1b9d0903833a3416fc7fe560234 |
| mysmb32.exe | 349018 | a60038d9818ab24ff61c6e0ecdff7a2b8f73ea46501e4432ee76d0df07ddcf8c |
| mysmb64.exe | 357360 | 9560f050e9fb049a3317e188369b0ebe698cf1d98c46e89714d03d720e2654a5 |

## S5 admission: fireworks lifetime and score tail

S4 closed in db21c96. Coordinator accepts transfer-201 under the continuing
M2 mandate. Scope and expected-new set are the same three open nodes:
`RunFireworks`, `SetupExpl`, `FireworksSoundScore`, in source order at
$D295-$D2CC (lines 10438-10464). Baseline 1,202/1,992, maximum 1,205.

Move the caller from endgame_objects.c to enemy/fireworks.c, restoring the
exact timer decrement/wrap, expiry reset, graphics increment and unsigned
termination gate. Drawing calls RelativeEnemyPosition, copies Y then X into
fireball scratch and passes fresh frame/OAM values to DrawExplosion_Fireworks.
Expiry clears the source enemy flag, assigns blast sound (not OR), writes
DigitModifier+4=5 and tail-calls EndAreaPoints. No entry flag/ID guard or
invented frame/timer rule. Legacy bulk eligibility remains outside this entry.

Dependencies retain their owners. Extract the existing four-sprite rendering
body into oam/fireworks_gfx.c with explicit frame/OAM arguments. Expose the
existing endgame score tail as one shared child used by fireworks and star
flag, retaining its current behavior; S6 owns EndAreaPoints/ELPGive migration.
This wiring grants no descendant-node credit and does not permit generic
explosion, score/HUD, star-flag or platform algorithm rewrites.

Logic proof uses naturally reached original NMI RunFireworks routes, input-only
controlled RAM when needed, source branches and complete child inputs before
recorded-return diagnostics. Separate actual-child execution retains every
remaining graphics/score discrepancy. No ROM/CPU/PC/stack/output patches.
Operational proof covers mysmb.fireworks-lifetime-chain mutation contracts,
initializer/endgame regression, strict C90 x86/x64, DOS16 link, platform purity,
hidden-window response and all three EXEs once per P. Retain all 10,900 prior
actual matches. DOS remains link-only. No credit before both proof tracks.

Similar-issue sweep covers duplicate owners, timer/frame wrap, guard placement,
post-child coordinates/arguments, sound assignment and duplicate score writes.
S4 is the predecessor; planned S6 star-flag/score is the successor. Existing
owner-ROM/listing provenance and local-only restrictions remain. Unique ignored
build/m2-t41-s5 outputs have a 32-MB raw limit, up to 512 original cases,
twenty-second per-record deadline and resumable checkpoints; coordinator owns
cleanup and dependent-regression retention. Stop on scope expansion, hidden
mismatches or execution patches.

## S5 implementation checkpoint

S5 remains active with no node credit or P closure. Direct ROM decoding
identifies 24 instructions and two conditional branches in $D295-$D2CC;
runtime source coverage is pending. RunFireworks now has one shared owner
in enemy/fireworks.c. Its exact timer/frame and terminal branches replace
the old guarded, combined endgame body. SetupExpl calls relative positioning,
reloads the source ObjectOffset and copies Y then X before passing fresh
frame/OAM arguments. FireworksSoundScore clears the flag, assigns sound eight,
sets modifier five and calls the separated existing score tail.

The old four-sprite body is extracted unchanged into oam/fireworks_gfx.c;
its generic explosion semantics remain unproved. The existing score tail is
shared with star-flag code, retaining its current score/coin HUD behavior
until S6 proves EndAreaPoints. No descendant credit or silent child rewrite.
Legacy bulk eligibility and its ObjectOffset preparation are outside the
original entry. Host adapters have no changes.

Thirty-two independent full-RAM/mutation cases pass per width, covering
zero/one/hold timers, byte frame wrap, absent/active flags, live ObjectOffset
and fresh drawing arguments, sound replacement and score handoff. All
139,770 fireworks initializer footprints per width remain equal. Existing
endgame test exit 6 remains unchanged. Strict C90 changed-owner compilation
and platform purity pass.

Next: naturally reached original RunFireworks snapshots and typed child
arguments, full branch/input/return comparisons, separate actual-child gaps,
retained cross-chain regression and a single three-target delivery pass.
Counts remain 1,202/1,992; assets still belong to db21c96. Local source/native
summaries stay below ignored build/m2-t41-s5. No P is committed yet.

## S5 original fireworks lifetime proof

S5 P1 closes all three expected caller nodes: 1,202 -> 1,205/1,992.
No scoped node remains unfinished or transfers at closure. Dependency
algorithms retain their separate proof state and current ledger receivers.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| RunFireworks | Byte timer decrement, reset to eight, graphics increment/wrap and unsigned termination branch. ROM-match complete. |
| SetupExpl | Relative child, fresh X/ObjectOffset, Y-then-X scratch copies and explicit original A/Y drawing arguments. ROM-match complete. |
| FireworksSoundScore | Flag clear, assigned blast sound, modifier five and EndAreaPoints tail call. ROM-match complete. |

All 24 original instructions in $D295-$D2CC execute, with both sides of both
conditional branches. The 512 routes start at the real NMI actor vector;
declared RAM inputs apply at naturally reached RunFireworks independently of
observer selection. No ROM, CPU/register, PC, stack or output patch is used.
Every observer-free original frame equals the observed original frame; this
does not assert native full-game frame equality.

Caller comparisons match 1,024/1,024 across x86/x64. Complete child input RAM
is checked before recorded-return diagnostics, including mapped $0109-$0139
and OAM/VRAM/audio queues; only hardware stack storage is excluded. Recorder
checks original relative-child returned X equals ObjectOffset. At explosion
entry it verifies original A equals the fresh graphics counter and Y equals
the fresh OAM offset; the C checker checks those explicit arguments against
the original record. Coordinate copies precede the child in source order.
Cases include slots zero/five, timer zero/one/hold/wrap, graphics wrap and
termination, coordinates/OAM boundaries, both players and nonzero timer control.

Actual roots match 472/1,024, with 552 descendant-affected differences.
Independent original child-input isolation gives:

- RelativeEnemyPosition: 472/944 exact full-RAM matches.
- DrawExplosion_Fireworks: 944/944 exact full-RAM matches.
- EndAreaPoints: 0/80 exact full-RAM matches.

These are bounded child diagnostics, not new descendant-node credit. No
recorded substitution occurs in actual comparisons. Relative scratch and
generic explosion/score behavior retain their source-order responsibilities;
EndAreaPoints/ELPGive belongs to planned S6. Passing a subset does not certify
the full child algorithm or complete gameplay.

RunFireworks has one shared owner in enemy/fireworks.c. The old combined
endgame actor is removed; existing explosion layout is extracted into
oam/fireworks_gfx.c with typed frame/OAM inputs. The pre-existing score tail
is shared with star-flag code and keeps its existing score/coin HUD behavior
until S6. Bulk eligibility and ObjectOffset setup remain outside the source
entry. No host code or gameplay rule changes.

Thirty-two independent full-RAM/mutation contracts pass per native width,
including fresh child arguments, absent flags, timer/frame wrap, sound
replacement and score handoff. All 139,770 fireworks initializer footprints
per width remain equal; existing endgame exit 6 remains explicit. Fifteen
initializer/platform suites per width and platform purity pass. The final
actual matrix is 11,372/18,682: every prior 10,900 match remains, with 472 new
root matches. The 7,310 remaining differences are sample counts, not nodes.

All 105 shared units compile under strict C90 on x86/x64; self-tests and
hidden-window response probes pass. DOS16 compiles/links with the existing
OLDNAMES warning. DOS remains link-only, without graphical playability,
resource-binding or physical 486SX certification. Three EXEs are refreshed.

Similar-issue sweep covers owner duplication, guards, byte counters, fresh
child state/register arguments, coordinate order, sound assignment and score
modifier writes. Reproduce fireworks_lifetime_fixture.h cases 0..511 with
--fixture=t41-fireworks-lifetime=N, --fireworks-lifetime-snapshot,
--control-children and independent --pc-coverage. The caller checker is
fireworks_lifetime_snapshot_check; enemy_loop_actual_check executes real
children. Native target is mysmb.fireworks-lifetime-chain. Ignored
build/m2-t41-s5 holds bounded inputs and resumable checkpoints with twenty-
second per-record deadlines. Coordinator owns cleanup and dependent inputs.
Existing provenance and local-only restrictions remain. S6 star-flag/score
is next, not admitted by this closure.

Raw trace output: 8418057 bytes, below 32 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256015 | a29d79b5554029ea297cb7d0660790f37afdd837340aa7b1fc5c04473ad79ffd |
| mysmb32.exe | 350649 | 615526680f859d2a3c93ef8efd67cab400bf342c443855ddc4078d11765c9b6a |
| mysmb64.exe | 358037 | c0d67b68232462f146a7a8dedf9451d5c61f949e44f4fc430764450d12ba8feb |

## S6 admission: star flag and end-area score chain

S5 closed in ae621ce. Coordinator accepts transfer-202 under the continuing
M2 mandate. Baseline 1,205/1,992; all twenty S6 checklist labels above are in
scope and expected new, maximum 1,225. StarFlagExit enters as audited with
incomplete evidence; the other nineteen are open. The exact source-order set:

`StarFlagYPosAdder`, `StarFlagXPosAdder`, `StarFlagTileData`, `RunStarFlagObj`, `GameTimerFireworks`, `SetFWC`, `IncrementSFTask1`, `StarFlagExit`, `AwardGameTimerPoints`, `NoTTick`, `EndAreaPoints`, `ELPGive`, `RaiseFlagSetoffFWorks`, `SetoffF`, `DrawStarFlag`, `DSFLoop`, `DrawFlagSetTimer`, `IncrementSFTask2`, `DelayToAreaEnd`, `StarFlagExit2`.

Entry RunStarFlagObj ($D2D9), three preceding tables ($D2CD-$D2D8), through
StarFlagExit2 ($D3AF), including the shared EndAreaPoints entry ($D336).
One shared owner enemy/star_flag.c replaces the approximate endgame caller.
Restore JumpEngine scratch, five task paths, timer/fireworks choices, per-frame
50-point conversion, fresh post-child player/slot reads, reverse four-sprite
loop with byte OAM wrap, draw-before-delay writes and EventMusicBuffer gate.
Keep bulk eligibility outside original entries. Fireworks S5 is the predecessor;
Piranha S7 is the successor. RelativeEnemyPosition, DigitsMathRoutine and
UpdateNumber remain external dependencies; this S grants no child credit.

Logic proof: naturally reached original NMI actor route, bounded input-only
fixtures at the root, all branches/tables and full child inputs before recorded
returns. Record real-child comparisons independently and preserve all 11,372
previous actual matches. No execution, stack, ROM, PC or output patches.
Operational proof: mysmb.star-flag-chain native mutation contracts, prior
fireworks/endgame regression, C90 x86/x64, DOS16 link, platform purity and
hidden-window response. Refresh all three owner-authorized EXEs once per P.
DOS remains link-only; node credit needs both tracks.

Similar-issue sweep: duplicate score/draw owner, task guards, frame/sound gate,
modifier index, fresh child state, byte OAM wrap and music queue/buffer choice.
Existing local ROM/listing provenance and redistribution limits remain.
Unique ignored build/m2-t41-s6 outputs: at most 1,024 original cases, 32-MB raw
budget, twenty-second per-record deadline, resumable checkpoints. Coordinator
owns cleanup and dependent-regression retention. Stop on unadmitted child
repair, hidden differences, execution patches or platform gameplay logic.

## S6 original star-flag and score proof

S6 P1 closes all twenty expected caller/data nodes: 1,205 -> 1,225/1,992.
No scoped node remains unfinished or transfers at closure. External child
algorithms retain their individual proof boundaries and ledger receivers.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| StarFlagYPosAdder | Original four bytes bound to reverse-index draw loop; every index exercised. ROM-match complete. |
| StarFlagXPosAdder | Original four bytes bound to reverse-index draw loop; byte coordinate carry wraps. ROM-match complete. |
| StarFlagTileData | Original four tiles emitted in source reverse-index order. ROM-match complete. |
| RunStarFlagObj | Frenzy clear, unsigned task gate, original JumpEngine scratch and all five native targets. ROM-match complete. |
| GameTimerFireworks | Last digit 1/3/6 versus other digits selects exact count and state. ROM-match complete. |
| SetFWC | Fireworks counter and source enemy state stores precede task increment. ROM-match complete. |
| IncrementSFTask1 | Task byte increment reached from setup or all-zero game timer. ROM-match complete. |
| StarFlagExit | Task zero and task >=5 exit without drawing; scratch differs as original. ROM-match complete. |
| AwardGameTimerPoints | OR of all timer digits, frame bit gates only tick sound, not arithmetic. ROM-match complete. |
| NoTTick | Modifier+5=-1 and math Y=23, then modifier+5=5 and score tail. ROM-match complete. |
| EndAreaPoints | CurrentPlayer zero/nonzero selects score offset 0B/11 after timer math. ROM-match complete. |
| ELPGive | Math child precedes fresh CurrentPlayer shift/OR4 and typed UpdateNumber tail. ROM-match complete. |
| RaiseFlagSetoffFWorks | Unsigned Y >=72 decrements once then draws, including 72->71 boundary. ROM-match complete. |
| SetoffF | Zero/negative fireworks draws then delays; positive count requests fireworks. ROM-match complete. |
| DrawStarFlag | Relative child precedes fresh ObjectOffset/OAM reads; no alternative world-position formula. ROM-match complete. |
| DSFLoop | Four reverse table indices, fresh relative fields, absolute indexed stores and byte OAM increment. ROM-match complete. |
| DrawFlagSetTimer | Draw finishes before fresh returned-slot interval timer store of six. ROM-match complete. |
| IncrementSFTask2 | Task increment after timer setup or fully completed delay. ROM-match complete. |
| DelayToAreaEnd | Draw first, then fresh interval timer and EventMusicBuffer (not queue). ROM-match complete. |
| StarFlagExit2 | Delay exits preserve task when interval or music remains. ROM-match complete. |

All 92 original instructions in $D2D9-$D3AF execute (excluding the ten-byte
JumpEngine vector); both sides of thirteen conditional branches execute.
All twelve bytes in the three data tables match the owner PRG and every index
is exercised. The five native task branches preserve original JumpEngine
scratch; this is data provenance, not CPU emulation or runtime ROM dispatch.

The 1,024 original NMI actor routes cover slots zero/five, all five tasks and
unsigned invalid-task exits, timer zero/nonzero and last-digit choices, both
frame-bit outcomes/players, Y=71/72/73 and byte boundaries, positive/zero/
negative fireworks, OAM FC wrap and interval/music combinations. Controlled
RAM inputs are applied at naturally reached RunStarFlagObj independently of
observer selection. Every observer-free original frame matches its observed
original frame. No CPU/register, PC, stack, ROM or output execution patches.
This does not claim native full-frame equivalence.

Original caller comparisons pass 2,048/2,048 across x86/x64. Child input RAM
and typed arguments are compared before any recorded-return substitution:
RelativeEnemyPosition ($F152, X), DigitsMathRoutine ($8F5F, Y) and UpdateNumber
($BC36, A). The observer verifies returned relative X equals ObjectOffset.
Mapped stack-page RAM $0109-$0139 is included; hardware return-stack storage
is excluded. All VRAM/OAM/audio-queue RAM changes are compared. Source edges
and the exact child entry addresses are reconciled against owner PRG bytes.

Separate actual-child roots pass 1,552/2,048. Independent child tests from
original inputs give RelativeEnemyPosition 256/512, DigitsMathRoutine 480/480,
and UpdateNumber 0/240 exact RAM footprints. The 496 failed actual roots
split into 256 relative-scratch and 240 number-output descendant cases.
RelativeEnemyPosition remains with M2 T16 S4; UpdateNumber remains M2 T36 S5,
with PrintStatusBarNumbers/OutputNumbers under M2 T28 S7. No new descendant
credit is claimed, no mismatch is suppressed, and no generic child is rewritten.
EndAreaPoints now uses the correct score/timer tail; the S5 fireworks roots
still show score-output child differences, rather than claiming they are fixed.

Implementation has one shared owner, enemy/star_flag.c. Legacy bulk eligibility
and ObjectOffset setup remain outside source entries in endgame_objects.c.
There is no platform gameplay branch or host-code change. Similar-issue sweep
found and replaced the old task-1 default state, whole-arithmetic frame gate,
wrong modifier slot, post-task extra drawing, inline relative calculation,
nonwrapping OAM progression, delay writes before drawing and music queue gate.
Both star flag and fireworks now call one EndAreaPoints owner.

Operational proof passes 779 native mutation/branch cases per width, all
32 fireworks lifetime contracts per width, 139,770 fireworks initializer
footprints per width and the endgame smoke. The latter's historical exit-6
fixture used title OperMode=0, where the original deliberately locks digits;
setting gameplay OperMode=1 now checks 100->099 and +50 points and passes.
Mutation cases prove fresh post-child player/slot/OAM reads and draw-before-
delay ordering. Fifteen initializer/platform suites per width remain green.
CTest star-flag-chain, fireworks-lifetime-chain and platform-purity pass 3/3.

Final actual matrix: 12,928/20,730; all previous 11,372 exact matches remain,
plus 1,552 star-flag roots and four improved actor-dispatch cases. The 7,802
remaining sample differences are not node counts or a playability percentage.
All 106 shared sources compile under strict C90 x86/x64; hidden-window response
and self-tests pass. DOS16 compiles/links with the existing OLDNAMES warning.
DOS remains link-only, without graphical, resource-binding or 486SX certification.
All three owner-authorized EXEs are refreshed; raw ROM/derived resources stay ignored.

Reproduce star_flag_fixture.h cases 0..1023 with --fixture=t41-star-flag=N,
--star-flag-snapshot, --control-children and independent --pc-coverage.
star_flag_snapshot_check checks the caller; enemy_loop_actual_check runs real
children. Native CTest target: mysmb.star-flag-chain. Ignored build/m2-t41-s6
holds bounded records/checkpoints with twenty-second per-record deadlines.
Coordinator retains only dependent regression inputs and owns cleanup.
S7 Piranha movement is next and is not admitted by this closure.

Raw trace output: 11262160 bytes, below 32 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255929 | 1b66417bddea1bbdce7a63daac884ed930abf4d754807ae94190cdb14e5926c0 |
| mysmb32.exe | 350797 | 57198aa82843b65a3d19616ee3788badfab514f566ad6e05c5a2b612d06f5d09 |
| mysmb64.exe | 358735 | c9278a722428d24582b4aa580a9fd00bb6e2b862a40f563b21d68ffbb1c4ec3a |

## S7 admission: Piranha movement and pipe priority

S6 closed in 7e00445. Coordinator accepts transfer-203 under the continuing
M2 mandate. Six scoped and expected-new labels, all open at admission:
`MovePiranhaPlant`, `ChkPlayerNearPipe`, `ReversePlantSpeed`,
`SetupToMovePPlant`, `RiseFallPiranhaPlant`, `PutinPipe`.
Baseline 1,225/1,992; maximum 1,231. Entry $D3B0 through $D40F,
lines 10602-10660, one shared enemy/piranha.c owner replacing objects.c.

Restore state/frame-timer gates, movement flag and signed-speed branch,
PlayerEnemyDiff page-result sign and low-byte negation, 21 proximity gate,
speed reversal, target scratch before frame/timer gates, byte Y motion,
endpoint delay and unconditional final attribute assignment. Flag/ID
eligibility stays at the legacy bulk caller. PlayerEnemyDiff retains its
existing owner and typed return; no child-node credit or graphics rewrite.
Predecessor S6 star flag; successor S8 FirebarSpin.

Logic proof uses naturally reached original NMI movement dispatch, bounded
input-only root fixtures, all original branch/read/write and child arguments.
Caller comparisons check full child input before recorded returns; actual-child
runs remain separate. Retain all 12,928 existing actual matches. No original
CPU/register, PC, stack, ROM or output patches. Operational proof: focused
mysmb.piranha-movement-chain, existing actor regressions, strict C90 x86/x64,
DOS16 link, platform purity, hidden-window probes and three EXEs once per P.
No node credit before both tracks. DOS remains link-only.

Similar-issue sweep: duplicate owner, entry eligibility versus source gates,
page/sign distance, negative-speed reversal, scratch timing, byte movement,
endpoint timer and priority assignment on all exits. Existing owner-ROM/listing
provenance and local-only restrictions apply. Unique ignored build/m2-t41-s7
records have 32-MB raw budget, up to 512 routes, twenty-second per-record
timeout and resumable checkpoints. Coordinator owns cleanup/dependent records.
Stop on unadmitted repair, hidden mismatch, execution patch or host gameplay.

## S7 original Piranha movement proof

S7 P1 closes all six expected nodes: 1,225 -> 1,231/1,992. No scoped node
remains unfinished or transfers at closure. PlayerEnemyDiff keeps its own
ledger responsibility; this bounded chain proof grants it no separate credit.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| MovePiranhaPlant | State/frame-timer gates, movement flag, signed speed and original PlayerEnemyDiff call order. ROM-match complete. |
| ChkPlayerNearPipe | Returned page-result sign controls low-byte negation; unsigned 21 proximity boundary. ROM-match complete. |
| ReversePlantSpeed | Byte negation and movement-flag increment, including pre-existing negative speed. ROM-match complete. |
| SetupToMovePPlant | Speed sign selects exact down/up endpoint before frame/timer gates. ROM-match complete. |
| RiseFallPiranhaPlant | Target scratch, odd-frame/master-timer gates, byte Y addition and endpoint delay. ROM-match complete. |
| PutinPipe | Every path assigns sprite attributes 20, including all early exits. ROM-match complete. |

All 47 original instructions in $D3B0-$D40F execute, with both outcomes of all
ten conditional branches. The 512 original NMI movement routes exercise
slots zero/five, state and frame-timer exits, idle/moving flags, positive and
negative speeds, both distance signs and the 20/21 boundary, page differences,
odd/even frames, timer-control gates, byte Y wrap and exact/nonexact endpoints.
Input-only root fixtures are independent of observer selection. Every original
observer-free frame equals the observed original frame; this does not claim
native full-game frame equality. No ROM, CPU/register, PC, stack or output patch.

Caller comparisons and separate actual-child comparisons both pass 1,024/1,024
across x86/x64. The caller harness compares full input RAM at original
PlayerEnemyDiff ($E143) before applying recorded returns, including mapped
$0109-$0139 and all VRAM/OAM/audio queues; hardware return-stack storage is
excluded. The observer validates input X and preserved returned X and records
returned A. Native arguments and the A sign drive the same subsequent branch.
Actual comparisons use the real shared distance implementation without any
recorded substitution. No unexplained difference remains in this S route set.

The old approximate owner in objects.c is removed. Shared enemy/piranha.c owns
the source body. The existing normal-enemy vector keeps its entry; flag/ID
eligibility stays outside it in the legacy bulk caller. Source state/timer gates
still execute PutinPipe. No graphics-child or platform behavior is rewritten.
Similar-issue sweep covers the removed low-byte-only absolute distance formula,
missing negative-speed reversal, lost scratch writes, misplaced frame/timer
checks and missing priority assignment. The same-source entry is unique;
initializer endpoints and unrelated physics aliases keep their existing owners.

Independent native tests pass 1,282 cases per width: every nonzero state/timer,
all low-byte distances under both page signs, all byte speeds and Y wrap,
exact endpoint delays, near-player exit, odd/even/frozen frames, absent entry
flags and changed ObjectOffset with source-preserved X. Focused CTest passes;
platform purity and fifteen prior initializer/platform suites per width pass.
Final actual matrix: 13,956/21,754. All 12,928 prior matches remain, plus all
1,024 new Piranha roots and four improved prior cases. Remaining 7,798 sample
differences retain prior descendant responsibilities; they are not node counts.

All 107 shared sources pass strict C90 x86/x64 builds and self-tests; both
hidden Win32 windows create and answer messages. DOS16 compiles/links with the
existing OLDNAMES warning. DOS remains link-only, without graphical playability,
resource-binding or physical 486SX certification. Three EXEs are refreshed.

Reproduce piranha_movement_fixture.h cases 0..511 using
--fixture=t41-piranha-movement=N, --piranha-movement-snapshot,
--control-children and independent --pc-coverage. piranha_movement_snapshot_check
checks source calls; enemy_loop_actual_check executes actual dependencies.
Native target is mysmb.piranha-movement-chain. Ignored build/m2-t41-s7 holds
bounded records and checkpoints, twenty-second per-record deadlines and
coordinator-owned dependent regression retention/cleanup. Existing local-only
source restrictions remain. S8 FirebarSpin is next, not admitted by this closure.

Raw trace output: 5549120 bytes, below 32 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255865 | 76aeb212ce0bc8fb3710e7188142be30108ec31fa29dc02905d7d9b4b5ee870a |
| mysmb32.exe | 351013 | 7d7973abc7fd499d74cba0bad62b1742945e444a460a287b1af7fc404549f1c7 |
| mysmb64.exe | 358987 | b470b4e6935dbcd85db5c7456b54731e048346d98f5f1690f0f5f1ae78276c42 |

## S8 admission: Firebar angular primitive

S7 closed in e199ada. Coordinator accepts transfer-204 under the continuing
M2 mandate. FirebarSpin and SpinCounterClockwise are both open, both scoped
and expected new. Baseline 1,231/1,992; maximum 1,233. Original $D410-$D431,
source lines 10664-10687, shared enemy/firebar_children.c owner. S7 is the
predecessor; S9 balanced platforms is the successor.

Review the existing typed leaf against source: speed store to scratch 07,
zero/nonzero direction, byte low update, carry/borrow high return without
storing or masking high state. ProcFirebar owns the high-state mask/store.
No new gameplay algorithm, sibling leaf or platform changes are admitted.
Original unused Y loads are accounted for against the caller's live inputs.

Logic proof reuses bounded T40 S8 original child records, compares complete
input/output RAM and returned A, and freshly reproduces representative original
NMI routes with instruction/branch coverage. Recorded source inputs are never
native expected fixtures or tracked data. No child substitution is needed by
this leaf. Validate original entry speed/slot and source reachability. Native
proof exhausts low-byte/speed pairs, zero/nonzero direction, high-byte boundary
and slot variants; keep original caller/actual-root regressions separate.
Retain all 13,956 prior actual matches. No CPU/PC/stack/ROM/output patches.

Operational proof: mysmb.firebar-spin-chain, prior firebar callers and actual
matrix, strict C90 x86/x64, DOS16 link, platform purity and hidden-window probes.
Refresh three EXEs once per P. DOS remains link-only. Similar-issue sweep covers
spin-owner duplication, carry/borrow width, high-state write ownership and
scratch/order across caller and leaf. Existing local owner-ROM/listing source
policy applies. Unique ignored build/m2-t41-s8 output has 16-MB raw budget,
up to sixteen fresh routes with twenty-second deadlines/checkpoints;
coordinator owns dependent-record retention and cleanup. Stop on scope growth,
hidden differences, execution patches or platform gameplay.

## S8 original Firebar spin proof

S8 P1 closes both expected leaf nodes: 1,231 -> 1,233/1,992. No scoped node
remains unfinished or transfers. Existing production arithmetic already agrees
with source and is retained; only its provenance comment and proof are updated.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| FirebarSpin | Scratch 07 receives speed, zero direction adds low byte with carry, returns high byte without storing it. ROM-match complete. |
| SpinCounterClockwise | Nonzero direction subtracts low byte with borrow, returns high byte without storing it; byte wrap preserved. ROM-match complete. |

Source reconciliation fixes the exact boundary at $D410-$D431: BalancePlatform
starts at $D432 and remains S9. All nineteen spin instructions execute, with
both outcomes of the direction branch. Original Y loads (18/08) are checked
by the observer; ProcFirebar overwrites Y with Enemy_ID before any use. The
native ABI therefore returns only live A, preserving input slot X. The caller
masks A with 1F and stores high state; the leaf never assumes that responsibility.

The original T40 S8 512 NMI route records contain 320 executed spin calls;
the remaining 192 skip the leaf at caller timer/offscreen gates. Both native
widths independently execute the leaf from those original inputs: 640/640
full RAM and returned-A comparisons match. No recorded child substitution is
used by this leaf. Hardware return-stack storage is excluded; mapped
$0109-$0139 and all VRAM/OAM/audio queue RAM remain included. The 384 no-call
records across widths are not inflated into spin matches.

Eight fresh original NMI routes (0,1,4,5,8,9,12,13) reproduce prior frame,
root and child records byte-for-byte. Independent observer-free frames match
the observed frames, and PC coverage proves all instructions/branch outcomes.
At spin entry the observer checks X=ObjectOffset and A=FirebarSpinSpeed[X];
at return it checks preserved X and source direction-dependent Y and records A.
No original CPU/register, PC, stack, ROM or output is patched. Source listing,
PRG instruction boundaries, and native reads/writes/returned result agree.

Native tests pass 1,572,864 exact RAM/A combinations per width: all 65,536
low-byte/speed pairs, high bytes 00/01/7F/FF, slots zero/five, and directions
00/01/FF. Independent 16-bit phase arithmetic checks carry/borrow and wrap;
expected RAM permits only scratch 07 and low-state writes. Full memcmp also
checks that high state and all unrelated RAM remain unchanged. CTest spin
and platform-purity pass 2/2. Fifteen prior initializer/platform suites per
width remain green. The integrated root matrix remains 13,956/21,754 with
zero lost matches; its existing 7,798 descendant sample differences are not
new failures or node counts. Spin child tests are not added again as roots.

Similar-issue review finds one production spin owner, one caller mask/store,
no platform gameplay, and safe 16-bit intermediate ranges (low plus speed at
most 510). Unrelated offscreen/relative functions in the same source file
are unchanged and retain their own proof state. No speculative repair.

All 107 shared units pass strict C90 x86/x64 compilation and self-tests;
both hidden Win32 windows respond. DOS16 compiles/links with the existing
OLDNAMES warning; it remains link-only, without graphical/resource-binding
or physical 486SX certification. Three EXEs are rebuilt and refreshed; DOS16
is byte-identical to S7, consistent with unchanged gameplay instructions.

Reproduce existing firebar_chain_fixture.h routes with the original recorder's
--fixture=t40-firebar-chain=N, --firebar-chain-snapshot, --control-children
and independent --pc-coverage. firebar_spin_snapshot_check consumes only child
2 records; firebar_spin_smoke provides the independent exhaustive native proof.
Ignored build/m2-t41-s8 contains fresh bounded records and neutral summaries;
T40 S8 records remain retained dependent inputs. Deadlines are twenty seconds
per route; coordinator owns retention/cleanup. Existing local-only source
restrictions remain. S9 balanced platforms is next, not admitted by this closure.

Fresh raw trace output: 371516 bytes, below 16 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255865 | 76aeb212ce0bc8fb3710e7188142be30108ec31fa29dc02905d7d9b4b5ee870a |
| mysmb32.exe | 351013 | 6f42e218f0e99a434028c61e906090b339ecf87be59551c8aad26cd4f0799eee |
| mysmb64.exe | 358987 | 9dc2900483b339a12c8cfae63af0a1f094dbaf32ade57e59c76d5806203a252f |

## S9 admission: balanced platforms and ropes

S8 closed in ae0d120. Coordinator accepts transfer-205 under the continuing
M2 mandate. Baseline 1,233/1,992; 26 open scoped/expected-new nodes, maximum
1,259. Exact source-ordered labels:

`BalancePlatform`, `DoBPl`, `CheckBalPlatform`, `ChkForFall`, `MakePlatformFall`, `ChkOtherForFall`, `ChkToMoveBalPlat`, `ColFlg`, `PlatUp`, `PlatSt`, `PlatDn`, `DoOtherPlatform`, `DrawEraseRope`, `EraseR1`, `OtherRope`, `EraseR2`, `EndRp`, `ExitRp`, `SetupPlatformRope`, `GetLRp`, `GetHRp`, `ExPRp`, `InitPlatformFall`, `StopPlatforms`, `PlatformFall`, `ExPF`.

Original $D432-$D5D2, from BalancePlatform through ExPF; the successor
YMovingPlatform begins at $D5D3. One shared enemy/balance_platform.c owner
replaces the approximate objects.c body. S8 spin is predecessor; S10 vertical
platform motion is successor. Keep the complete pair/rope/fall graph in one S.

Restore signed pair-state eligibility, high-Y erasure, both top limits,
collision/inertia choice, original up/down/stop order, inverse pair movement,
player-placement child, two rope writes and buffer gates, exact horizontal
carry resets and vertical rotations, falling score/init and dual gravity.
Track live X/Y across calls explicitly: offscreen restores ObjectOffset and
Y=1; InitVStf preserves Y and returns zero. No extra peer flag/ID/range filters.

Dependencies retain their node owners: EraseEnemyObject, MovePlatformUp/Down,
MoveFallingPlatform, InitVStf, GetEnemyOffscreenBits, SetupFloateyNumber and
PositionPlayerOnVPlat. Existing up/down, falling, init and score typed seams
are reused. An offscreen adapter owns the existing returned-bit store. Extract
only the four existing legacy-contact player-placement writes into one shared
objects.c child seam; the collision caller invokes that same body unchanged.
The newly explicit placement boundary retains missing source guards/high-byte
semantics and extra legacy state clear for its future owner. This is no child
algorithm rewrite or child completion credit. Actual-child failures stay visible.

Logic proof: original naturally reached NMI large-platform dispatch, bounded
input-only root cases, all feasible source branch/write paths and rope addresses.
Compare complete child inputs and explicit arguments before recorded-return
caller diagnostics, then independently run actual children and preserve all
13,956 prior exact root matches. No CPU/PC/stack/ROM/output execution patches.
Operational proof: mysmb.balance-platform-chain mutation/rope contracts,
prior platform suites, strict C90 x86/x64, DOS16 link, platform purity,
hidden-window response and all three EXEs once per P. DOS remains link-only.

Similar-issue review covers duplicate owner, invented eligibility, carry/borrow,
live slots, stack-saved values, player-placement boundary, rope buffer writes
and source child order. Existing owner-local ROM/listing restrictions remain.
Unique ignored build/m2-t41-s9 records: at most 1,024 routes, 48-MB raw budget,
twenty-second per-record deadlines and resumable checkpoints; coordinator owns
retention/cleanup. Stop on unadmitted child repair, unexplained proof gaps,
source execution patches or platform gameplay.

## S9 original balanced platform proof

S9 P1 closes all 26 expected nodes: 1,233 -> 1,259/1,992. No scoped
node remains unfinished or transfers. Dependency nodes retain their owners.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| BalancePlatform | High-Y equals three erases through the original child. ROM-match complete. |
| DoBPl | Signed pair-state gate exits without invented eligibility filters. ROM-match complete. |
| CheckBalPlatform | Pair offset and collision scratch precede the falling flag. ROM-match complete. |
| ChkForFall | Current-deck top comparison and collision-peer test. ROM-match complete. |
| MakePlatformFall | Tail transfer into the original falling initializer. ROM-match complete. |
| ChkOtherForFall | Peer-deck top comparison and collision-current test. ROM-match complete. |
| ChkToMoveBalPlat | Saved old Y, collision choice and force-plus-five carry chain. ROM-match complete. |
| ColFlg | Collision flag compared with live ObjectOffset. ROM-match complete. |
| PlatUp | Upward child followed by inverse-peer update. ROM-match complete. |
| PlatSt | Stop child preserves the source peer register. ROM-match complete. |
| PlatDn | Downward child falls through to inverse-peer update. ROM-match complete. |
| DoOtherPlatform | Byte old-minus-new displacement added to peer; placement child ordering. ROM-match complete. |
| DrawEraseRope | Live ObjectOffset, movement and VRAM offset gates precede rope writes. ROM-match complete. |
| EraseR1 | Negative first speed writes two blank tiles. ROM-match complete. |
| OtherRope | Saved speed XOR FF selects the peer address calculation. ROM-match complete. |
| EraseR2 | Nonnegative original speed erases the second rope. ROM-match complete. |
| EndRp | Null terminator and ten-byte buffer advance. ROM-match complete. |
| ExitRp | Rope early exits preserve queues and restore source slot semantics. ROM-match complete. |
| SetupPlatformRope | Eight-pixel X addition and normal-mode carry reset before adding sixteen. ROM-match complete. |
| GetLRp | Page carry and masked horizontal address contribution. ROM-match complete. |
| GetHRp | Y rotations, page bit, vertical contribution and E8 bottom adjustment. ROM-match complete. |
| ExPRp | Address return preserves buffer offset and scratch contract. ROM-match complete. |
| InitPlatformFall | Offscreen then score child; restored X and Y=1 drive initialization. ROM-match complete. |
| StopPlatforms | InitVStf zero return clears peer speed and force. ROM-match complete. |
| PlatformFall | Saved peer survives first gravity; live collision flag selects placement. ROM-match complete. |
| ExPF | Falling exit restores ObjectOffset semantics. ROM-match complete. |

All 201 instructions in $D432-$D5D2 execute. All 43 feasible conditional
outcomes execute; the sole impossible outcome is fallthrough at $D492:
the preceding CMP #0B / BCC admits this BCS only with carry set.
The 1,024 original NMI routes cover slots zero/five, both top limits,
collision/no-collision inertia, force carry and speed sign, pair inversion,
both falling calls, buffer boundaries, X/page carries, hard-mode carry reset,
Y rotation/wrap and both rope directions. Inputs are patched only at the
original root entry; ROM, CPU/PC, stack and output are never patched.
Observer-free original frames equal observed frames, not native full frames.

Caller RAM and child-input proof passes 2,048/2,048 across x86/x64. Each
recorded return is applied only after complete input RAM and argument checks.
Mapped $0109-$0139, queues and scratch are included; hardware return-stack
storage is excluded. Observer contracts check live/restored X, preserved X,
offscreen/score Y=1, InitVStf A=0 and score control six. Native locals preserve
the source stack-saved old Y, peer and two speed copies without an emulator.

Independent actual-child roots pass 1,088/2,048. Child isolation gives:

| Existing dependency | Exact / tested calls, both widths |
| --- | ---: |
| EraseEnemyObject | 64 / 64 |
| MovePlatformUp | 704 / 704 |
| MovePlatformDown | 640 / 640 |
| InitVStf | 448 / 448 |
| PositionPlayerOnVPlat | 0 / 832 |
| GetEnemyOffscreenBits | 0 / 128 |
| SetupFloateyNumber | 128 / 128 |
| MoveFallingPlatform | 256 / 256 |

The 960 failing actual roots correspond to the placement and offscreen
children. Placement still lacks original guards/high-byte borrow and clears
Player_State unnecessarily; offscreen still lacks original scratch writes.
These dependencies remain incomplete under their existing ledger owners.
Caller proof grants no child completion or full-game equivalence claim.

The approximate balance body is removed from objects.c. Shared
enemy/balance_platform.c owns the complete pair/rope/fall chain. The four
legacy player-placement writes are extracted unchanged and reused by the
legacy collision path. Offscreen adapts the existing return value only.
No platform adapter changes or child algorithm repairs are included.
The similar-issue sweep covers duplicate ownership, invented peer guards,
lost carry resets, live slot reloads, saved peer/speed, VRAM offset/terminator
and call order; all same-chain hits now use this source body. Unrelated
platform movement and collision interiors retain their scheduled owners.

Native rope/mutation contracts pass 262,150 cases per width, including all
X/Y bytes, both difficulty and speed signs, buffer offsets and child slot
mutation. Focused CTest and platform purity pass. Fifteen prior initializer/
platform suites pass per width. The old platform smoke incorrectly required
an immediate pixel step on contact and made both decks movement owners; it
now checks first-frame fractional acceleration, negative-state peer gating,
and subsequent inverse displacement at whole-pixel speed.
Final actual-root matrix: 15,048/23,802; all 13,956 previous matches remain,
plus 1,088 new matches and four special-actor improvements. The remaining
8,754 sample differences retain descendant debt; these are not node counts.

All 108 shared sources build with strict C90 x86/x64 and pass self-tests.
Both hidden Win32 windows create and respond to messages. DOS16 compiles/
links with the existing OLDNAMES warning; it remains link-only, without
graphical playability, resource binding or physical 486SX certification.
The three owner-authorized local test EXEs are refreshed for this P.

Reproduce balance_platform_fixture.h cases 0..1023 using
--fixture=t41-balance-platform=N, --balance-platform-snapshot,
--control-children and --pc-coverage. balance_platform_snapshot_check checks
caller contracts; enemy_loop_actual_check executes actual dependencies.
Native CTest: mysmb.balance-platform-chain. Ignored build/m2-t41-s9 contains
bounded traces, child isolation and checkpoints with twenty-second record
deadlines and coordinator-owned dependent regression retention/cleanup.
S10 vertical oscillating platforms is next, not admitted by this closure.

Raw trace output: 15294592 bytes, below 48 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258585 | 777f189d11275382c5f922830273b7346b14a1c75c3206f7c9eb154c84c73ffb |
| mysmb32.exe | 353680 | 391256309bde51c5aa1fb3cd9c4508dc1cd8f8d5dfebc35c772a42b350bc34ba |
| mysmb64.exe | 362195 | 05fbc951679a53151efd56aff43da0265084ef6a0872445129b6da22359cc5b3 |

## S10 admission: vertical oscillating platforms

S9 closed in 430a24f. Coordinator accepts transfer-206 under the continuing
approved M2 mandate. Baseline 1,259/1,992; six open scoped/expected-new nodes,
maximum 1,265. Exact source-ordered labels:

`YMovingPlatform`, `SkipIY`, `ChkYCenterPos`, `YMDown`, `ChkYPCollision`, `ExYPl`.

Original $D5D3-$D606, YMovingPlatform through ExYPl. S9 balance/rope is
predecessor; S11 horizontal/drop/right platforms is successor. One shared
enemy/platform.c owner replaces the approximate objects.c body. Restore the
stationary dummy clear, unsigned top/center tests, eight-frame increment,
up/down child order and the final signed collision gate for rider positioning.
Gravity returns X=ObjectOffset; placement preserves X. Do not replace the
current slot with the collision flag or add caller-level timer/flag guards.

Dependencies MovePlatformUp/Down and PositionPlayerOnVPlat keep their owners.
Reuse existing typed seams unchanged; placement gaps from S9 remain explicit.
Logic proof uses original NMI large-platform entry and bounded input fixtures,
complete child-input comparison before recorded returns, original branch
coverage, then independent actual-child comparisons. Preserve all 15,048 prior
root matches. No ROM/CPU/PC/stack/output execution patches or child repairs.
Operational proof uses mysmb.vertical-platform-chain, previous platform suites,
strict C90 x86/x64 builds, DOS16 link, platform purity, hidden-window response
and all three EXEs per P. DOS remains link-only.

Similar-issue sweep: unique owner, missing dummy reset/placement, unsigned
comparisons, frame gate, live slot and source child ordering. Existing owner
ROM/listing provenance and nonredistributable local research containment apply.
Ignored build/m2-t41-s10: at most 512 routes, 24-MB raw budget, twenty-second
record deadlines and resumable checkpoints; coordinator owns retention and
cleanup. Stop on unexplained proof gaps, unadmitted dependency changes or host
gameplay. Every scoped node must be proved or explicitly transferred at closure.

## S10 original vertical platform proof

S10 P1 closes all six expected nodes: 1,259 -> 1,265/1,992. No scoped
node remains incomplete or transfers. Dependencies retain their owners.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| YMovingPlatform | Speed/force OR, stationary dummy clear and unsigned top comparison. ROM-match complete. |
| SkipIY | Eight-frame increment path goes directly to rider collision gate. ROM-match complete. |
| ChkYCenterPos | Unsigned current-Y/center comparison selects up or down child. ROM-match complete. |
| YMDown | Down child returns live ObjectOffset before collision evaluation. ROM-match complete. |
| ChkYPCollision | Signed collision gate calls placement with current slot, not flag value. ROM-match complete. |
| ExYPl | No-collision and placement return share the original exit. ROM-match complete. |

All 22 instructions in $D5D3-$D606 and both outcomes of all five branches
execute. The 512 original NMI platform routes cover slots zero/five, all
frame residues, stationary/nonzero speed/nonzero force, unsigned top/center
boundaries, negative/positive gravity, fractional carry and rider gates.
Root input fixtures are independent of observer selection. Observer-free
original frames equal observed original frames; this is not native full-frame
equivalence. No ROM, CPU/register, PC, stack or output execution patch.

Caller comparisons pass 1,024/1,024 across x86/x64. Each child input RAM and
slot/direction argument is checked before recorded-return substitution.
Mapped $0109-$0139, scratch and queues are included; hardware return-stack
storage is excluded. Gravity's returned X=ObjectOffset and placement's
preserved X are asserted against the original instructions and observer.

Independent actual roots pass 512/1,024. Isolated actual up calls pass
360/360 and down calls pass 216/216. All 512 placement calls differ: the
legacy child retains missing original guards/high-byte borrow and extra
Player_State clear. That existing dependency stays incomplete with its own
ledger receiver; this S grants no child credit or full-game equivalence.

Shared enemy/platform.c replaces the approximate objects.c movement body.
It restores stationary dummy clearing and the final rider call, preserves
the original rest-path slot and reloads ObjectOffset after gravity. No timer,
flag or collision-value eligibility filter is added. Similar-issue review
covers duplicate owners, unsigned thresholds, missing writes, frame gates
and source call order; unrelated platform children retain scheduled owners.

Native tests pass 204,800 cases per width: all byte Y/top and Y/center pairs,
speed-only/force-only movement, all frame residues, slot zero/five, changed
ObjectOffset and collision flags distinct from the current slot. They check
full caller RAM footprint and ordered typed-child arguments. Focused CTest,
platform purity and fifteen previous initializer/platform suites pass per
width. Final actual-root matrix: 15,560/24,826, retaining all 15,048 prior
matches and adding 512. The remaining 9,266 sample differences remain
explicit descendant debt, not node counts.

All 109 shared sources compile in strict C90 x86/x64; both self-tests and
hidden-window creation/message-response probes pass. DOS16 compiles/links
with the existing OLDNAMES warning. DOS is link-only, without graphical
playability, resource binding or physical 486SX certification. All three
owner-authorized test EXEs are refreshed.

Reproduce vertical_platform_fixture.h cases 0..511 with
--fixture=t41-vertical-platform=N, --vertical-platform-snapshot,
--control-children and --pc-coverage. vertical_platform_snapshot_check checks
caller inputs; enemy_loop_actual_check executes actual children. Native
CTest: mysmb.vertical-platform-chain. Ignored build/m2-t41-s10 retains bounded
records/checkpoints under twenty-second deadlines and coordinator-owned
dependent regression retention/cleanup. S11 horizontal/drop/right platforms
is next, not admitted by this closure.

Raw trace output: 6598208 bytes, below 24 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258745 | b142de399c10e7928b23397150b4d1242b674c7c24902d990a8f423d0b1d86db |
| mysmb32.exe | 353896 | 61a9032bbcf2e03af95edfc66564fee348ca75f8f20f4c0a2335d91cf07c2a11 |
| mysmb64.exe | 362447 | 716ec1e18ea248f085542d5f37165295ecd7e24c33099747173df4fe47c2b02f |

## S11 admission: horizontal drop and right platforms

S10 closed in f4d73f8. Coordinator accepts transfer-207 under the continuing
M2 mandate. Baseline 1,265/1,992; nine open scoped/expected-new nodes, maximum
1,274. Exact source-ordered labels:

`XMovingPlatform`, `PositionPlayerOnHPlat`, `PPHSubt`, `SetPVar`, `ExXMP`, `DropPlatform`, `ExDPl`, `RightPlatform`, `ExRPl`.

Original $D607-$D64E, XMovingPlatform through ExRPl. S10 vertical platforms
is predecessor; S12 lifts is successor. One shared enemy/platform.c owns this
contiguous three-entry chain and its shared horizontal-rider tail. Replace
the approximate objects.c horizontal/drop/right bodies. Preserve counter
maximum 0E, counter/movement call order, saved displacement, signed page
carry/borrow, scroll handoff, drop collision gate, right-platform returned A
and post-collision speed 10. Reload ObjectOffset exactly after source children
that restore X; horizontal positioning retains its incoming current slot.

Reuse XMoveCntr_Platform, MoveWithXMCntrs, MoveEnemyHorizontally,
MoveDropPlatform and PositionPlayerOnVPlat as typed dependencies. These keep
their individual ownership/status; the known placement-child gap is explicit.
No child algorithm or host gameplay repair is admitted. Logic proof observes
the three original NMI large-platform entries with bounded input fixtures,
complete child-input RAM/argument checks before recorded returns, original
branches and separate actual-child roots. Assert returned A and source X
contracts. Preserve all 15,560 prior root matches; no ROM/CPU/PC/stack/output
execution patches. Operational proof: mysmb.horizontal-platform-chain,
cross-chain regressions, strict C90 x86/x64, DOS16 link, platform purity,
hidden-window response and three EXEs once per P. DOS remains link-only.

Similar-issue sweep covers duplicate owners, missing counter/rider calls,
signed displacement versus unsigned carry, source slot reload, drop snap
and right-speed timing. Existing owner-local ROM/listing provenance and
nonredistributable research containment apply. Ignored build/m2-t41-s11 uses
at most 768 routes, 40-MB raw budget, twenty-second record deadlines and
resumable checkpoints; coordinator owns dependent retention/cleanup.
Stop on unadmitted child changes, source execution patches or unexplained
proof gaps. Every scoped node must be proved or explicitly transferred.

## S11 original horizontal platform proof

S11 P1 closes all nine expected nodes: 1,265 -> 1,274/1,992. No scoped
node remains incomplete or transfers; dependencies retain their owners.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| XMovingPlatform | Counter maximum 0E, counter then movement call order and live collision slot. ROM-match complete. |
| PositionPlayerOnHPlat | Saved signed displacement moves player X and keeps source carry. ROM-match complete. |
| PPHSubt | Negative displacement uses SBC zero with the preceding X-add carry. ROM-match complete. |
| SetPVar | Page result, Platform_X_Scroll and vertical placement child order. ROM-match complete. |
| ExXMP | Horizontal no-collision and shared placement paths return. ROM-match complete. |
| DropPlatform | Signed collision gate precedes drop child and live-slot placement. ROM-match complete. |
| ExDPl | No-collision drop exits without writes or movement. ROM-match complete. |
| RightPlatform | Horizontal returned A stored in scratch; only collision sets speed 10. ROM-match complete. |
| ExRPl | Right-platform exit preserves no-collision speed and scratch return. ROM-match complete. |

All 32 instructions in $D607-$D64E and both outcomes of all four branches
execute. The 768 original NMI large-platform routes divide equally among
XMovingPlatform, DropPlatform and RightPlatform. They exercise slots zero/
five, counter phase/frame/secondary boundaries, positive/negative fractional
displacement, player X/page edges, collision gates, drop gravity and speed
assignment after rightward movement. Root input fixtures are independent of
observer selection. Observer-free original frames equal observed originals;
this is not native full-frame equality. No ROM/CPU/PC/stack/output patch.

Caller proof passes 1,536/1,536 across x86/x64, comparing full RAM and typed
child arguments before recorded returns. Mapped $0109-$0139, scratch and
queues are included; hardware return-stack storage is excluded. Observer
assertions prove counter A=0E, restored X after movement/drop, preserved X
for counter and placement, and record MoveEnemyHorizontally's returned A
after verifying its input X equals ObjectOffset. Native code stores that A
before collision checks and retains the original horizontal-tail arithmetic.

Independent actual roots pass 768/1,536. Isolated actual children match:
XMoveCntr_Platform 512/512, MoveWithXMCntrs 512/512, MoveDropPlatform 256/256,
MoveEnemyHorizontally 512/512 (including returned A). All 768 placement
children differ; this is the existing PositionPlayerOnVPlat missing guards/
high-byte borrow and extra Player_State clear. Its separate ledger owner
remains responsible; this S grants no child completion or whole-game claim.

The approximate horizontal/drop/right bodies are removed from objects.c.
Shared enemy/platform.c now owns the contiguous source entries and common
horizontal rider tail. Signed byte displacement uses the original page
carry/borrow, drop calls absolute placement, and rightward speed changes
after movement. The similar-issue sweep covers duplicate ownership, missing
counter/placement calls, left-crossing page increments, source slot reloads
and acceleration timing; all same-chain hits use the new body. Child
algorithms and platform adapters are unchanged.

Native tests pass 393,728 cases per width: all X/displacement bytes with
page zero/255 wrap, no-collision preservation, changed ObjectOffset, typed
child order and right-speed timing; drop checks both gate outcomes. The
previous vertical suite also passes after linkage-only fail-fast stubs for
the added sibling entries. The old horizontal platform smoke now supplies
source counter phase two and a non-counter frame for its expected +1 pixel.
Focused CTests, platform purity and fifteen prior initializer/platform suites
per width pass. Final actual-root matrix: 16,332/26,362; all 15,560 prior
matches remain, plus 768 new and four improved special-actor cases. Remaining
10,030 sample differences retain descendant debt and are not node counts.

All 109 shared sources pass strict C90 x86/x64 builds and self-tests. Both
hidden Win32 windows create and respond to messages. DOS16 compiles/links
with the existing OLDNAMES warning; it remains link-only without graphical
playability, resource binding or physical 486SX certification. Three
owner-authorized local test EXEs are refreshed for this P.

Reproduce horizontal_platform_fixture.h cases 0..767 with
--fixture=t41-horizontal-platform=N, --horizontal-platform-snapshot,
--control-children and --pc-coverage. horizontal_platform_snapshot_check
checks caller contracts; enemy_loop_actual_check executes actual children.
Native CTest: mysmb.horizontal-platform-chain; retained vertical test:
mysmb.vertical-platform-chain. Ignored build/m2-t41-s11 retains bounded
records/checkpoints under twenty-second deadlines and coordinator-owned
dependent regression retention/cleanup. S12 lift platforms is next, not
admitted by this closure.

Raw trace output: 11798784 bytes, below 40 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258809 | a0478c5759cb7149deb3e60ae3f2e421e36d72199c9c21fb530caf809c76d6bc |
| mysmb32.exe | 353896 | 17f169e6ff75edb38e412840e18b3f6454db038d9a41e49a927445d4709c7bef |
| mysmb64.exe | 362447 | 0fc1888fc28c47a2678bfca5d565034e2f8bf26a9d669b7230696e7b3feea593 |

## S12 admission: large and small lifts

S11 closed in 45ab618. Coordinator accepts transfer-208 under the continuing
M2 mandate. Baseline 1,274/1,992; five open scoped/expected-new nodes, maximum
1,279. Exact source-ordered labels:

`MoveLargeLiftPlat`, `MoveSmallPlatform`, `MoveLiftPlatforms`, `ChkSmallPlatCollision`, `ExLiftP`.

Original $D64F-$D679 covers the two lift entries, shared movement and small
collision tail. The large lift reuses ChkYPCollision ($D5FE), already owned
by S10; retain that proof without duplicate node credit. S11 is predecessor,
S13 bounds is successor. Shared enemy/platform.c replaces the approximate
objects.c lift body: timer gates movement only, fractional addition carries
into low Y without touching high Y, then large signed/small nonzero collision
gates call their distinct placement children with preserved X.

PositionPlayerOnVPlat remains an existing child. PositionPlayerOnS_Plat is
still unimplemented; extract only the existing small-rider delta expression
into an explicitly legacy child seam in objects.c. A native old-Y argument
preserves that existing behavior; it is not a ROM argument or certified child
implementation. The actual source collision value A is also passed and must
be checked by the original caller harness. The recorded-child proof verifies
input RAM/slot/A before applying original returns. Separate actual-child
comparisons report the legacy small delta and known large-placement gaps;
neither child gains credit or new source semantics in this S.

Logic evidence: two naturally reached original NMI lift roots, timer on/off,
fractional carry, signed speed/wrap, large/small collision outcomes, complete
child inputs and original branch coverage; preserve all 16,332 prior actual
root matches. No ROM/CPU/PC/stack/output patches. Operational evidence:
mysmb.lift-platform-chain, retained platform chains, strict C90 x86/x64,
DOS16 link, platform purity, hidden-window response and three EXEs per P.
DOS remains link-only. Similar-issue sweep: shared movement ownership,
misplaced timer gate, carry width, accidental Y-high writes, player-delta
mixing and distinct placement arguments. No unadmitted child repair.

Owner-local ROM/listing provenance and nonredistributable research policy
remain unchanged. Ignored build/m2-t41-s12 allows at most 512 routes, 24-MB
raw output, twenty-second record deadlines and resumable checkpoints.
Coordinator owns dependent trace retention/cleanup. Stop on unexplained
proof gaps or source execution patches. Every scoped node must be proved
or explicitly transferred before closure.

## S12 original lift platform proof

S12 P1 closes all five expected nodes: 1,274 -> 1,279/1,992. No scoped
node remains incomplete or transfers. Placement dependencies retain their owners.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| MoveLargeLiftPlat | Movement precedes the retained signed large-rider collision tail. ROM-match complete. |
| MoveSmallPlatform | Movement precedes the nonzero small-rider collision tail. ROM-match complete. |
| MoveLiftPlatforms | Timer gates movement only; fractional ADC carry feeds low Y without high-Y mutation. ROM-match complete. |
| ChkSmallPlatCollision | Nonzero collision counter is the source A input to the small positioning child. ROM-match complete. |
| ExLiftP | Timer and small-no-collision exits preserve the source footprint. ROM-match complete. |

All eighteen instructions in $D64F-$D679 and both outcomes of its two
branches execute. The reused $D5FE-$D606 large-rider tail also executes all
four instructions and both collision outcomes; it retains S10 ownership
without duplicate credit. The 512 original NMI routes cover both lift roots,
slots zero/five, timer on/off, fractional carry, byte speed/Y wrap, large
signed and small nonzero collision gates, and small collision counters one/
two. Root input fixtures are independent of observer selection; observer-free
original frames equal observed originals, not native frames. No ROM, CPU,
PC, stack or output execution patches.

Caller comparisons pass 1,024/1,024 across x86/x64, checking complete RAM
and slot/collision arguments before recorded-return substitution. Mapped
$0109-$0139, scratch and queues are included; hardware return-stack storage
is excluded. Original child input/return X is asserted against ObjectOffset;
small-child input A is asserted equal to the collision flag. Native old-Y
compatibility metadata is checked against root input, not claimed as a ROM
argument. It exists solely to preserve the old incomplete child's behavior.

Independent actual roots pass 528/1,024. Isolated large-position child
matches 0/256; the legacy small-position child matches 16/256. Thus 256 large
and 240 small differences remain explicit. Large positioning lacks original
guards/high-byte handling and has an extra Player_State clear. Small
positioning still uses the previous player delta instead of the original
two-deck table and vertical placement. Those nodes remain incomplete with
their ledger owners. No child or whole-game completion credit is granted.

Shared enemy/platform.c owns both source entries and MoveLiftPlatforms.
The large collision tail is shared with YMovingPlatform rather than copied.
The old mixed lift body is removed from objects.c; only its unchanged small
player-delta expression remains behind an explicitly legacy child seam.
TimerControl skips motion but still reaches the positioning gate. Arithmetic
updates dummy and low Y only, preserving high Y and incoming slot. The
similar-issue sweep covers duplicate movement ownership, misplaced timer
gate, carry width, high-byte writes and mixed player compensation. Related
placement algorithms remain scheduled dependencies; host adapters unchanged.

Native tests pass 1,048,576 cases per width: every pair of fractional bytes,
positive/negative speed, Y wrap, timer state, both roots, both rider gates,
collision arguments, old-Y metadata, preserved slot and full RAM footprint.
Vertical and horizontal suites retain their assertions with fail-fast link
seams for the added sibling entry. Four focused CTests (including platform
purity) and fifteen previous initializer/platform suites per width pass.
Final actual-root matrix: 16,860/27,386. All 16,332 prior exact matches remain,
plus 528 new. Remaining 10,526 sample differences retain descendant debt;
they are not node counts.

All 109 shared sources pass strict C90 x86/x64 builds and self-tests. Both
hidden Win32 windows create and respond. DOS16 compiles/links with its
existing OLDNAMES warning. DOS remains link-only without graphical
playability, resource binding or physical 486SX certification. Three
owner-authorized local test EXEs are refreshed.

Reproduce lift_platform_fixture.h cases 0..511 with --fixture=t41-lift-platform=N,
--lift-platform-snapshot, --control-children and --pc-coverage.
lift_platform_snapshot_check checks caller contracts; enemy_loop_actual_check
executes actual dependencies. Native CTest: mysmb.lift-platform-chain.
Ignored build/m2-t41-s12 contains bounded traces/checkpoints under twenty-
second deadlines and coordinator-owned dependent regression retention/cleanup.
S13 extended offscreen bounds is next, not admitted by this closure.

Raw trace output: 5417984 bytes, below 24 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 259289 | 31408c06837a3dfc1a6a0745e8b3a5bc735f0520e9b4083794cdb25235120637 |
| mysmb32.exe | 354017 | 68ee2fe68a13a3fd48648feeeca911dc3f9c387b76fa3289d5f387528353c8cf |
| mysmb64.exe | 362566 | a54bb858632c4bd80baa0aa8e534955ca7af9e19972b8e962c500183d32f391e |

## S13 admission: extended offscreen bounds

S12 closed in ce394b9. Coordinator accepts transfer-209 under the continuing
M2 mandate. Baseline 1,279/1,992; five open scoped/expected-new nodes, maximum
1,284. Exact source-ordered labels:

`OffscreenBoundsCheck`, `LimitB`, `ExtendLB`, `TooFar`, `ExScrnBd`.

Original $D67A-$D6D5, OffscreenBoundsCheck through ExScrnBd, is the final
T41 chain; three unused bytes precede the following collision source slice.
Extract the existing enemy_bounds.c routine and its private subtraction
helper into planned enemy/actor_slots.c. Restore original $00-$03 boundary
scratch and remove the invented slot-range gate; preserve the actual source
carry chain, sign-bit page comparisons and ID/state erasure exceptions.
EraseEnemyObject is the existing certified dependency; keep its own owner.
No relative/offscreen-bits, boxes, collision or host algorithm rewrite.

Logic proof uses naturally reached NMI OffscreenBoundsCheck with bounded
entry input fixtures: every source branch, ID/state exceptions, boundary
equality, low-byte carry/borrow and page sign/wrap. Check full child inputs
before recorded returns and independently compare real erasure. Preserve
all 16,860 prior actual matches. No ROM/CPU/PC/stack/output execution patches.
Operational proof: mysmb.offscreen-bounds-chain, previous actor/platform
suites, strict C90 x86/x64, DOS16 link, platform purity, hidden-window
response and three EXEs once per P. DOS remains link-only.

Similar-issue sweep covers unique owner, missing source scratch, invented
entry gates, CPY/ADC/SBC carry continuity, signed-page versus host ordering,
and left/right-specific exceptions. Existing owner-local ROM/listing
provenance and nonredistributable research containment remain unchanged.
Ignored build/m2-t41-s13 allows at most 1,024 routes, 40-MB raw output,
twenty-second deadlines and resumable checkpoints; coordinator owns
dependent trace retention/cleanup. Every scoped node must be proved or
explicitly transferred. After S13, audit all 123 T41 scoped nodes and
cross-chain evidence before closing T41; no milestone completion is implied.

## S13 original offscreen bounds proof

S13 P1 closes all five expected nodes: 1,279 -> 1,284/1,992. No scoped
node remains incomplete or transfers; erasure keeps its own maintenance owner.

| Node | Individual ROM evidence and disposition |
| --- | --- |
| OffscreenBoundsCheck | Flying-fish early exit, source ID comparisons and ordered boundary scratch. ROM-match complete. |
| LimitB | Special-ID low-byte +38 consumes CPY carry before subtraction. ROM-match complete. |
| ExtendLB | Left borrow and right carry flow continuously through all four boundary bytes. ROM-match complete. |
| TooFar | Left/right erasure decisions call the original EraseEnemyObject input. ROM-match complete. |
| ExScrnBd | Inside-screen and each original state/ID exception return without erasure. ROM-match complete. |

All 44 instructions in $D67A-$D6D5 and both outcomes of all ten branches
execute. The 1,024 original NMI routes cover slots zero/five, flying-fish
exit, ordinary and special left bounds, left/right page sign wrap, boundary
carry/borrow and all right-edge state/ID exceptions. Inputs are patched only
at the naturally reached root. Observer-free original frames equal observed
originals, not native full frames. No ROM, CPU/PC, stack or output patch.

Caller and separate actual-child comparisons both pass 2,048/2,048 across
x86/x64. Full RAM and original erasure-slot inputs are checked before any
recorded return; actual comparisons use the real erasure implementation.
Mapped $0109-$0139, scratch, queues and OAM backing are included; hardware
return-stack storage is excluded. Erasure preserves source X. No unexplained
root difference remains in this S, and no extra credit is given to erasure.

The existing body and its private subtraction helper move from enemy_bounds.c
to planned enemy/actor_slots.c. Original $00-$03 scratch stores are restored
in source order and the invented slot-range exit is removed. Existing exact
carry arithmetic and special cases are preserved. The similar-issue sweep
covers duplicate ownership, invented gates, missing scratch, CPY/ADC/SBC
carry continuity, wrapped page sign versus host signed ordering and left/
right exception asymmetry. Every product caller selects this shared body;
relative/offscreen-bit, bounds-box and collision owners remain unchanged.

Native tests pass 524,288 cases per width using a word-domain oracle: all
IDs and left-X bytes, page-zero/255 wrap, both boundary equalities, adjacent
positions, half-range sign changes, erasure input footprint and early-return
preservation. Slots five/seven also prove absence of an invented native
range guard. All thirteen T41 chain CTests and platform purity pass together;
fifteen existing initializer/platform suites pass per width. Final actual
matrix is 18,928/29,434: all 16,860 prior matches remain, plus 2,048 new and
twenty improved older samples (sixteen special actor, four normal actor).
Remaining 10,506 samples retain unrelated descendant debt, not node counts.

All 110 shared sources pass strict C90 x86/x64 and self-tests. Both hidden
Win32 windows create/respond. DOS16 compiles/links with the existing
OLDNAMES warning. Three owner-authorized EXEs are refreshed. DOS remains
link-only: no graphical playability, resource binding or physical 486SX
certification. No platform gameplay or runtime emulator is introduced.

Reproduce offscreen_bounds_fixture.h cases 0..1023 using
--fixture=t41-offscreen-bounds=N, --offscreen-bounds-snapshot,
--control-children and --pc-coverage. offscreen_bounds_snapshot_check checks
caller contracts; enemy_loop_actual_check executes real erasure. Native
CTest: mysmb.offscreen-bounds-chain. Ignored build/m2-t41-s13 holds bounded
records/checkpoints with twenty-second deadlines and coordinator-owned
dependent regression retention/cleanup. T41 aggregate audit follows.

Raw trace output: 11065456 bytes, below 40 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 259305 | de7e0710a344b06ea4dd1787a44fcb63297c6da9693f1821a28258b3849b0ac3 |
| mysmb32.exe | 354233 | 5f9956630f2b637b1ea1a6a5e07e5f6affbb935279c9eace8fa21572337c3739 |
| mysmb64.exe | 362818 | 824d561514e82dcffe2386f4227eb8cfaaac847f855bc22773dc8fd0d6c41299 |

## T41 closure

All thirteen source-ordered S chains are closed. All 123 unique planned
nodes are individually ROM-match complete: 118 new and five retained,
bringing the canonical count from 1,166 to 1,284/1,992. Exact plan rows equal
the union of admitted S scopes. Every expected-new label equals its recorded
actual match; no scoped unfinished node or closure transfer remains. Each
label retains its maintenance receiver. External child nodes get no credit.

| Chain | Scoped nodes | New matches |
| --- | ---: | ---: |
| M2 T41 S1 | 6 | 6 |
| M2 T41 S2 | 19 | 17 |
| M2 T41 S3 | 4 | 4 |
| M2 T41 S4 | 12 | 9 |
| M2 T41 S5 | 3 | 3 |
| M2 T41 S6 | 20 | 20 |
| M2 T41 S7 | 6 | 6 |
| M2 T41 S8 | 2 | 2 |
| M2 T41 S9 | 26 | 26 |
| M2 T41 S10 | 6 | 6 |
| M2 T41 S11 | 9 | 9 |
| M2 T41 S12 | 5 | 5 |
| M2 T41 S13 | 5 | 5 |

Retained labels: KillAllEnemies, KillLoop, FlameTimerData, SetFlameTimer, ExFl.

The integrated matrix executes current shared C and actual children without
recorded-return substitution. It complements the node-level source and
caller/data proofs; completed callers do not certify unfinished descendants.
S8 FirebarSpin additionally retains its 640 original RAM/A comparisons and
1,572,864 native combinations per width; its native suite passes in the
final T41 run and its enclosing firebar routes are included below.

| Original route family | Actual matches | Remaining sample differences |
| --- | ---: | ---: |
| loop | 192/192 | 0 |
| stream | 160/160 | 0 |
| init | 220/220 | 0 |
| common | 104/104 | 0 |
| spiny | 160/160 | 0 |
| firebar | 80/80 | 0 |
| fish | 304/304 | 0 |
| bowser-flame | 320/320 | 0 |
| fireworks | 240/240 | 0 |
| bullet-swim | 364/364 | 0 |
| group | 230/230 | 0 |
| small-init | 392/392 | 0 |
| platform-init | 480/480 | 0 |
| actor-dispatch | 46/360 | 314 |
| normal-actor | 88/252 | 164 |
| special-actor | 56/184 | 128 |
| podoboo | 128/128 | 0 |
| hammer-movement | 712/712 | 0 |
| paratroopa | 320/320 | 0 |
| green-counter | 576/576 | 0 |
| bloober | 1024/1024 | 0 |
| bullet-movement | 256/256 | 0 |
| swimming-cheep | 1024/1024 | 0 |
| firebar-chain | 292/1024 | 732 |
| flying-cheep-movement | 1024/1024 | 0 |
| lakitu-movement | 2048/2048 | 0 |
| bridge-collapse | 72/360 | 288 |
| bowser-control | 16/2048 | 2032 |
| bowser-graphics | 0/1024 | 1024 |
| flame-actor | 8/2048 | 2040 |
| fireworks-lifetime | 472/1024 | 552 |
| star-flag | 1552/2048 | 496 |
| piranha-movement | 1024/1024 | 0 |
| balance-platform | 1088/2048 | 960 |
| vertical-platform | 512/1024 | 512 |
| horizontal-platform | 768/1536 | 768 |
| lift-platform | 528/1024 | 496 |
| offscreen-bounds | 2048/2048 | 0 |

Total: 18,928/29,434 actual comparisons match. All 16,860 pre-S13 matches
remain; S13 adds 2,048 matches and improves twenty older samples. Remaining
10,506 sample differences retain explicit child owners: graphics, relative/
offscreen bits, boxes/collision, status output and platform positioning are
not certified by their callers. In particular, the small-platform legacy
delta bridge remains incomplete; its native old-Y metadata is no ROM
implementation claim. No full-game or full-frame equality claim is made.

S13 supplies the integrated delivery: 110 shared C90 units for x86/x64,
both self-tests and hidden-window response probes, DOS16 compile/link, all
thirteen T41 chain CTests and platform purity in one final run, and the
actual-root matrix on both widths. Fifteen preceding initializer/platform
suites per width also pass. Final EXE sizes/hashes above match assets/.
Accepted original node proofs are reused without repeating every lifecycle.
All gameplay remains in shared game code; no host algorithm or runtime
NES emulator was introduced. DOS remains link-only, without graphical
playability, resource binding or physical 486SX qualification.

T41 is closed; M2 remains incomplete at 1,284/1,992. The next queued source
slice starts FireballEnemyCollision at line 11085 and covers shared collision,
bounding boxes and movement primitives. No later T is admitted by this
closure; publish its exact nodes and S ownership before implementation under
the continuing approved M2 mandate.
