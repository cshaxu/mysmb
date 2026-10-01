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
