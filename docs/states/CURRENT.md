# Project Status

## Current Work

## M2 T64 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S2 admitted — Fireball-to-enemy collision scan. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S1. |
| Objective | Audit `FireballEnemyCollision -> ExitFBallEnemy` at `$D6D9-$D735`: `FireballEnemyCollision`, `FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`, `NoFToECol`, and `ExitFBallEnemy`; repair shared-C differences before closure. |
| Non-goals | `HandleEnemyFBallCol` begins S3; caller/return edges owned by unadmitted cohorts remain unchanged. |
| Reference Baseline | Historical 1,992 / 1,992; current exact 1,232 / 1,992 nodes and 2,476 / 4,324 feasible controls (4,342 raw; 18 infeasible). |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | `src/game/world/fireball_enemy.c` and project-owned C90 test harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | ROM logic: state/frame gates, descending five-slot scan, box offsets, child ordering, hit mark and restore/return. Operational: batched x86/x64 original-ROM routes, scan and collision regression tests, DOS16 link and platform purity. |
| Expected Markers | Six exact nodes; 19 source-owned Cohort-J control edges and four material handoffs, unless a static or route difference remains. |
| Asset Needs | Owner-local ROM records live only below ignored build directories. Refresh all three products only if product C changes. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current aggregate node/control totals. |
| Stop Conditions | Any mismatch or missing route blocks S2 closure and S3 admission. |
| Exit Criteria | Both tracks have no unresolved scoped difference and tracker/ledger record each result. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | High-bit state gates, frame parity, stack-equivalent saved box identity, child-mutated RAM, descending-loop termination and host-boundary purity. |

## Current Technical Baseline

T64 S1 closed at 1,232 current-exact nodes and 2,476 current-exact feasible
controls. T64 S2 is the sole active packet and can raise the current exact
node total by six when both verification tracks pass.
