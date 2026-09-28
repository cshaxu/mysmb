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
