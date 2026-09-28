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
