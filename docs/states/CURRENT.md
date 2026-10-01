# Project Status

## Current Work

## M2 T61 S9 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S9 audit - Cohort H horizontal-movement primitive chain. |
| Admission And Approval | Owner-approved source-order proof program; S8 is closed and this packet admits S9 only. |
| Objective | Audit and repair `MoveEnemyHorizontally -> ExXMove` against original-ROM semantics. |
| Non-goals | No vertical movement/gravity or platform-adapter behavior claim. |
| Reference Baseline | Historical 1,992 / 1,992; current 786 / 1,992 nodes and 1,545 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | Shared `src/game/world/movement.c` plus shared player boundary; platform adapters are consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 movement routes, focused arithmetic smoke, purity and DOS16 link. |
| Expected Markers | Six nodes and eight internal feasible controls. |
| Asset Needs | Shared-game repair refreshes three local EXEs. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | Any feasible difference remains in S9 until repaired and re-audited. |
| Exit Criteria | Six nodes and scoped feasible controls exact; no platform code carries horizontal-motion rules. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Signed-nibble extraction, carry propagation, equal-low-byte ADC, page carry, wrapper slot restore and jumpspring gate. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; T61 S9 is active.

## T61 S7 Closure

Twenty-eight block-chain nodes and fifty-five controls exact; no source changed.

## T61 S8 Closure

`BlockObjectsCore -> NextBUpd` is current-exact: eight nodes and sixteen internal feasible control relations passed static source comparison, controlled original-ROM/current x86/x64 caller and complete-current routes, focused C90 tests, platform purity and DOS16 link. Historical migration remains **1,992 / 1,992**; current registry is **786 / 1,992** exact nodes and **1,545 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.
