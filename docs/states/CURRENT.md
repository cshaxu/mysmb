# Project Status

## Current Work

## M2 T61 S10 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S10 audit - Cohort H vertical movement and gravity chain. |
| Admission And Approval | Owner-approved source-order proof program; S9 is closed and this packet admits S10 only. |
| Objective | Audit and repair `MovePlayerVertically -> ExVMove` against original-ROM semantics. |
| Non-goals | `EnemiesAndLoopsCore` and platform-adapter behavior are outside this chain. |
| Reference Baseline | Historical 1,992 / 1,992; current 792 / 1,992 nodes and 1,554 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | Shared `src/game/world/gravity.c`, player and actor call boundaries; platform adapters are consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 vertical/gravity routes, focused C90 harnesses, purity and DOS16 link. |
| Expected Markers | 26 nodes and 37 internal feasible controls. |
| Asset Needs | Shared-game repair refreshes three local EXEs. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | Any feasible difference remains in S10 until repaired and re-audited. |
| Exit Criteria | 26 nodes and 37 internal controls exact; platform code has no movement rule. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Jumpspring gates, vertical wrapper offsets, platform and red-troopa selectors, signed gravity arithmetic and return paths. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; T61 S10 is active.

## T61 S7 Closure

Twenty-eight block-chain nodes and fifty-five controls exact; no source changed.

## T61 S8 Closure

`BlockObjectsCore -> NextBUpd` is current-exact: eight nodes and sixteen internal feasible control relations passed static source comparison, controlled original-ROM/current x86/x64 caller and complete-current routes, focused C90 tests, platform purity and DOS16 link. Historical migration remains **1,992 / 1,992**; current registry is **786 / 1,992** exact nodes and **1,545 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.

## T61 S9 Closure

`MoveEnemyHorizontally -> ExXMove` is current-exact: six nodes and nine internal feasible controls passed `$BF02-$BF4C` static comparison, 96 controlled original-ROM snapshots per width, focused C90 arithmetic, platform purity and DOS16 link. Historical migration remains **1,992 / 1,992**; current registry is **792 / 1,992** exact nodes and **1,554 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.
