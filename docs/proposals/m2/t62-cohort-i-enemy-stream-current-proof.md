# M2 T62: Cohort I enemy stream, initialization and groups current-equivalence proof

T62 continues the approved source-order current-equivalence program after T61.
It audits all 165 Cohort-I labels from `EnemiesAndLoopsCore` through
`RunBowserFlame`. Historical ROM-match accounting remains **1,992 / 1,992**;
this task supplies fresh current shared-C evidence only.

## Task contract

Each admitted chain must make every scoped node, feasible control relation and
material handoff current-exact. The ROM-logic track compares source predicates,
RAM reads/writes, table binding, calls and returns. The operational track uses
the same original-ROM route against current x86/x64, focused C90 tests,
platform-purity, and the shared DOS16 link. A source repair refreshes all three
local executables; an audit-only S does not.

Owner-supplied `smb1.nes` is a local, untracked verification input only.
The disassembly, raw snapshots and recorder traces remain under ignored
`build/`; no ROM bytes, generated derivatives, or executable artifacts are
committed.

## Source-ordered S chains

| S | Original range and chain | Labels | Shared C owners |
| --- | --- | ---: | --- |
| S1 | `$C047-$C0C3`, `EnemiesAndLoopsCore -> ChkEnemyFrenzy` | 16 | `enemy/core.c`, `enemy/loop.c`; flag turns, castle loops and frenzy handoff. |
| S2 | `$C0D7-$C175`, `ProcessEnemyData -> Inc2B` | 19 | `enemy/stream.c`; record fetch, bounds, page control and group record decode. |
| S3 | `$C180-$C22C`, `CheckpointEnemyID -> InitVStf` | 21 | `enemy/init.c`, `init_targets.c`; initializer vector and ordinary actor setup. |
| S4 | `$C233-$C2D3`, `InitBulletBill -> InitShortFirebar` | 22 | `init_targets.c`, `frenzy.c`; special initializers and Lakitu/Spiny state chain. |
| S5 | `$C2EA-$C395`, `FlyCCXPositionData -> SetFrT` | 18 | `init_targets.c`, `frenzy.c`; flying Cheep and Bowser/flame setup. |
| S6 | `$C39C-$C43F`, `PutAtRightExtent -> FireBulletBill` | 23 | `frenzy.c`; mouth/right-edge, fireworks, and Bullet Bill/Cheep frenzy paths. |
| S7 | `$C44C-$C4AD`, `HandleGroupEnemies -> EndFrenzy` | 12 | `stream.c`, `frenzy.c`; group allocation and frenzy dispatch/termination. |
| S8 | `$C4AF-$C541`, `LakituChk -> EndOfEnemyInitCode` | 25 | `init_targets.c`; Lakitu and platform initializer families. |
| S9 | `$C546-$C5B4`, `RunEnemyObjectsCore -> RunBowserFlame` | 9 | `enemy/core.c`; actor vector selection and dispatch boundaries. |

The nine rows cover all **165** current Cohort-I labels. Each later S remains
unadmitted until its exact packet records its internal relation count and
original-ROM route. S9 is a dispatch-boundary audit only; individual actor
interiors retain their source-order owner in the later Cohort-J chains.

## S1 admission — enemy flags, loop commands and frenzy handoff

S1 admits `$C047-$C0C3`, `EnemiesAndLoopsCore -> ChkEnemyFrenzy`:
`EnemiesAndLoopsCore`, `ChkAreaTsk`, `ChkBowserF`, `ExitELCore`,
`LoopCmdWorldNumber`, `LoopCmdPageNumber`, `LoopCmdYPosition`,
`ExecGameLoopback`, `ProcLoopCommand`, `FindLoop`, `IncMLoop`, `WrongChk`,
`DoLpBack`, `InitMLp`, `InitLCmd`, and `ChkEnemyFrenzy`.

All sixteen are `needs-evidence`; S1 expects zero historical-node credit
because the historical ledger is already complete. It owns 27 internal
feasible control relations and three internal material handoffs. It excludes
`ProcessEnemyData`, `InitEnemyObject`, `KillAllEnemies`, and actor dispatch
interiors; they are named successor/child boundaries and gain no credit here.

The ROM-logic comparison covers duplicate high-bit slot flags, parser-task
seven suppression, all eleven world/page/Y table entries, world-seven
multi-loop counters, loopback page/cursor reset ordering, kill-all call
boundary, and frenzy queue handoff. The operational route uses ordinary
original-ROM NMI enemy turns and the matching current x86/x64 fixture records;
it also runs focused loop tests, platform-purity and the shared DOS16 link.
Any feasible difference remains in S1 until repaired and re-audited.

## S1 closure — enemy flags, loop commands and frenzy handoff

All sixteen scoped labels are current-exact. Static `$C047-$C0C3` comparison found no feasible difference in high-bit duplicate-flag handling, parser-task-seven suppression, all eleven loop records, world-seven counters, five page rewinds, cursor/page reset ordering, erase-call boundary, frenzy queue writes, or child handoff order. All 27 internal feasible controls and the three loop-table material handoffs are exact.

Fresh x86/x64 current caller checks match all 96 controlled original-ROM snapshots per width (192 comparisons). The four loop tables match 44 ROM bytes, and focused loop smoke passes for both widths. Platform purity passes and the OpenNT DOS16 link completes with its known OLDNAMES warning. `ProcessEnemyData`, initializer and actor bodies remain explicit successor boundaries and receive no S1 credit. No product source changed, so local executable artifacts were not refreshed. Historical migration remains **1,992 / 1,992**; current exact progress is **834 / 1,992 nodes** and **1,615 / 4,324 feasible controls** from **4,342 raw controls** with **18 infeasible**.

## S2 admission — enemy stream records, bounds and group decode

S2 admits `$C0D7-$C175`, `ProcessEnemyData -> Inc2B`: `ProcessEnemyData`, `CheckEndofBuffer`, `CheckRightBounds`, `CheckPageCtrlRow`, `PositionEnemyObj`, `CheckRightExtBounds`, `CheckForEnemyGroup`, `BuzzyBeetleMutate`, `StrID`, `CheckFrenzyBuffer`, `StrFre`, `InitEnemyObject`, `ExEPar`, `DoGroup`, `ParseRow0e`, `NotUse`, `CheckThreeBytes`, `Inc3B`, and `Inc2B`. All 19 are `needs-evidence`; this audit earns no historical-node credit. It owns 38 internal feasible controls and three internal material handoffs.

The route covers ordinary/end/group/frenzy stream records, screen-right page boundary cases, slot-five rejection, page-control row, position-before-boundary ordering, hard-mode Buzzy mutation, group handoff and two/three-byte cursor increments. `InitEnemyObject` is audited only for its direct call/return boundary; initializer interior belongs to S3. Original-ROM/current x86/x64 records, focused stream checks, purity and the shared DOS16 link are required.

## S2 closure — enemy stream records, bounds and group decode

All nineteen scoped labels are current-exact. Static `$C0D7-$C175` comparison found no feasible difference in end marker handling, sixth-slot exception, screen-right and extended-right arithmetic, page-select and row-$0f control, position-before-bound order, hard-mode Buzzy mutation, group/frenzy handoffs, two/three-byte cursor advance, or the initializer call/return boundary. All 38 internal feasible controls and three material handoffs are exact.

Fresh x86/x64 caller checks match 80 controlled original-ROM stream snapshots per width (160 comparisons). The focused boundary model passes 66,562 cases per width and complete stream smoke passes per width. Platform purity passes and the OpenNT DOS16 link completes with its known OLDNAMES warning. Initializer and group interiors remain named S3/S7 boundaries and receive no S2 credit. No product source changed, so local executable artifacts were not refreshed. Historical migration remains **1,992 / 1,992**; current exact progress is **853 / 1,992 nodes** and **1,653 / 4,324 feasible controls** from **4,342 raw controls** with **18 infeasible**.

## S3 admission — initializer vector and ordinary actor setup

S3 admits `$C180-$C22C`, `CheckpointEnemyID -> InitVStf`: `CheckpointEnemyID`,
`InitEnemyRoutines`, `NoInitCode`, `InitGoomba`, `InitPodoboo`,
`InitRetainerObj`, `NormalXSpdData`, `InitNormalEnemy`, `GetESpd`, `SetESpd`,
`InitRedKoopa`, `HBroWalkingTimerData`, `InitHammerBro`,
`InitHorizFlySwimEnemy`, `InitBloober`, `SmallBBox`, `InitRedPTroopa`,
`GetCent`, `TallBBox`, `SetBBox`, and `InitVStf`. All 21 labels are
`needs-evidence`; this current audit earns no historical-node credit. It owns
46 internal feasible controls, two explicitly infeasible raw fallthroughs
(`InitEnemyRoutines -> NoInitCode` and `SmallBBox -> InitRedPTroopa`), and
three material handoffs.

The ROM-logic route covers the `< $15` Y-plus-eight/masked-offscreen setup,
the full 55-entry `JumpEngine` vector and scratch return address, no-init
returns, and the ordinary normal/Goomba/Koopa/Hammer/Bloober/Podoboo/Paratroopa
initializers through the shared bounding-box and vertical-state tails. It
excludes vector targets beginning at `InitBulletBill`, which belong to S4,
and all child actor interiors outside this address range. The operational track
uses controlled original-ROM/current x86/x64 vector snapshots, exhaustive
initializer-vector and common-initializer C90 smoke, platform purity and the
shared DOS16 link. Any feasible difference remains in S3 until repaired and
re-audited.

## S3 closure — initializer vector and ordinary actor setup

All 21 scoped labels are current-exact. Static `$C180-$C22C` comparison found
no feasible difference in the ID-$15 threshold/carry path, 55-entry initializer
vector and scratch return address, no-init aliases, Goomba/Podoboo/retainer
writes, normal and Hammer hard-mode tables, signed red-Paratroopa center, or
the shared box and vertical-state tail order. All 46 internal feasible controls
and material vector/normal-speed/Hammer-timer handoffs are exact; the two raw
fallthrough relations remain correctly infeasible.

Current x86/x64 caller checks match 110 controlled original-ROM snapshots per
width (220 comparisons). Exhaustive vector handoff passes 84,480 cases per
width, and ordinary initializer footprints pass 23,046 cases per width.
Platform purity passes and the OpenNT DOS16 link completes with the known
OLDNAMES warning. Special initializer interiors remain S4/S5/S8 scope, and
actor-consumer material edges remain their later source-order owner. No product
source changed, so local executable artifacts were not refreshed. Historical
migration remains **1,992 / 1,992**; current exact progress is **874 / 1,992
nodes** and **1,699 / 4,324 feasible controls** from **4,342 raw controls**
with **18 infeasible**.

## S4 admission — special initializers, Lakitu/Spiny and firebars

S4 admits `$C233-$C2D3`, `InitBulletBill -> InitShortFirebar`: `InitBulletBill`,
`InitCheepCheep`, `InitLakitu`, `SetupLakitu`, `KillLakitu`,
`PRDiffAdjustData`, `LakituAndSpinyHandler`, `ChkLak`, `ChkNoEn`, `CreateL`,
`RetEOfs`, `ExLSHand`, `CreateSpiny`, `DifLoop`, `UsePosv`, `SetSpSpd`,
`SpinyRte`, `ChpChpEx`, `FirebarSpinSpdData`, `FirebarSpinDirData`,
`InitLongFirebar`, and `InitShortFirebar`. All 22 labels are
`needs-evidence`; this current audit earns no historical-node credit. It owns
27 internal feasible controls, two explicitly infeasible raw fallthroughs
(`ChkNoEn -> CreateL` and `SetSpSpd -> SpinyRte`), and six internal material
handoffs.

The ROM-logic route covers Bullet Bill and Cheep direct initialization; Lakitu
frenzy rejection and setup; timer/slot scans and empty-slot allocation; the
Spiny Y/PRDiff/direction/egg-state path; and long/short Firebar table lookup,
anchor adjustment and page carry. It stops before flying Cheep setup in S5 and
keeps terrain/distance, actor and graphics children as later boundaries. The
operational track uses controlled original-ROM/current x86/x64 snapshots,
Lakitu/Spiny and Firebar C90 smoke, platform purity and the shared DOS16 link.
Any feasible difference remains in S4 until repaired and re-audited.

## S4 closure — special initializers, Lakitu/Spiny and firebars

All 22 scoped labels are current-exact. Static `$C233-$C2D3` comparison found no feasible difference in Bullet Bill/Cheep direct writes; Lakitu erase/setup; timer and reverse slot scans; reappearance allocation; the twelve PRDiff adjustment bytes and Spiny egg tail; or five-entry Firebar table selection, long-entry duplicate ordering, coordinate adjustment and page carry. All 27 internal feasible controls and six material handoffs are exact. The two raw relations `ChkNoEn -> CreateL` and `SetSpSpd -> SpinyRte` remain source-infeasible.

Current full-game x86/x64 builds produced 160 controlled original-ROM Lakitu/Spiny caller-boundary matches (80 per width), with original child return snapshots deliberately substituted only after their input and call order were compared; those child interiors remain later source-order boundaries. Twenty direct Firebar original/current routes (10 per width) match without substitution. Focused current C90 checks pass 71,163 Lakitu/Spiny caller footprints, 9,216 Firebar/duplicate footprints, and 23,046 common-initializer footprints per width. Platform purity passes and the shared DOS16 link completes with the known OLDNAMES warning. No product source changed, so no executable artifact refresh is required. Historical migration remains **1,992 / 1,992**; current exact progress is **896 / 1,992 nodes** and **1,726 / 4,324 feasible controls** from **4,342 raw controls** with **18 infeasible**.

## S5 admission — flying Cheep and Bowser/flame initialization

S5 admits `$C2EA-$C395`, `FlyCCXPositionData -> SetFrT`: `FlyCCXPositionData`, `FlyCCXSpeedData`, `FlyCCTimerData`, `InitFlyingCheepCheep`, `MaxCC`, `GSeed`, `RSeed`, `D2XPos1`, `D2XPos2`, `FinCCSt`, `InitBowser`, `DuplicateEnemyObj`, `FSLoop`, `FlmEx`, `FlameYPosData`, `FlameYMFAdderData`, `InitBowserFlame`, and `SetFrT`. All 18 are currently `needs-evidence`; this audit earns no historical-node credit. It owns 21 internal feasible controls and five internal material handoffs.

The ROM-logic route covers all flying-Cheep timer, hard-mode slot, pseudorandom/table, speed and position/page-borrow paths; Bowser duplication and setup; and the Bowser-flame timer, mouth/non-mouth, hard-mode, random-Y and timer-store paths. It stops at `PutAtRightExtent`, `SpawnFromMouth` and `FinishFlame`, which are S6 boundaries, and at prior shared children with their accepted source-order owners. The operational track uses controlled original-ROM/current x86/x64 routes, focused C90 checks, platform purity and the shared DOS16 link. Any feasible difference remains in S5 until repaired and re-audited.

## S5 closure — flying Cheep and Bowser/flame initialization

All 18 scoped labels are current-exact. Static `$C2EA-$C395` comparison found no feasible difference in all 16 Flying Cheep position bytes, 12 speed bytes and four timer bytes; timer and hard-mode slot gates; random seed transformations; stationary/moving-player position lookup; signed speed and page-borrow paths; Bowser duplicate scan and setup; or Bowser-flame timer, front-object, hard-mode, sound, height and timer-store paths. All 21 internal feasible controls and five material handoffs are exact.

Current full-game x86/x64 builds match 624 direct original-ROM snapshot routes: 304 Flying Cheep routes and 320 Bowser/flame routes. No child return substitution or old product binary is used. Focused current C90 checks pass 26,106 Flying Cheep and 107,522 Bowser/flame full-RAM footprints per width. Platform purity passes and the shared DOS16 link completes with the known OLDNAMES warning. No product source changed, so no executable artifact refresh is required. Historical migration remains **1,992 / 1,992**; current exact progress is **914 / 1,992 nodes** and **1,747 / 4,324 feasible controls** from **4,342 raw controls** with **18 infeasible**.
