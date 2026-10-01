# Project Status

## Current Work

## M2 T64 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S2 closed — Fireball-to-enemy collision scan. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S1. |
| Objective | Audit `FireballEnemyCollision -> ExitFBallEnemy` at `$D6D9-$D735`: `FireballEnemyCollision`, `FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`, `NoFToECol`, and `ExitFBallEnemy`; repair shared-C differences before closure. |
| Non-goals | `HandleEnemyFBallCol` begins S3; caller/return edges owned by unadmitted cohorts remain unchanged. |
| Reference Baseline | Historical 1,992 / 1,992; incoming current exact 1,232 / 1,992 nodes and 2,476 / 4,324 feasible controls (4,342 raw; 18 infeasible). |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | `src/game/world/fireball_enemy.c` and project-owned C90 test harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | ROM logic: static `$D6D9-$D735` comparison and 1,024 original-ROM caller records batched once per x86/x64 width with recorded child calls. Operational: strengthened scan, collision regression, audio/pause tests, DOS16 link and platform purity. |
| Expected Markers | Six nodes, 19 source-owned Cohort-J control edges and four material handoffs. |
| Asset Needs | Owner-local ROM records remain below ignored build directories. No product C changed, so no product artifact refresh is due. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current aggregate node/control totals. |
| Stop Conditions | Any mismatch or missing route blocks S2 closure and S3 admission. |
| Exit Criteria | Met: both tracks report no scoped difference and tracker/ledger record each result. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | High-bit state gates, frame parity, stack-equivalent saved box identity, child-mutated RAM, descending-loop termination and host-boundary purity; no additional product-owner difference found. |

## Closure Result

All six scoped nodes are current-exact: `FireballEnemyCollision`,
`FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`, `NoFToECol`, and
`ExitFBallEnemy`. The static audit found no shared-C repair. The original-ROM
caller replay ran 1,024 records in one x86 process and one x64 process with
zero RAM or recorded-child-call differences. The strengthened scan contract,
collision regression and audio/pause tests pass on both widths; platform
purity passes and OpenNT links the shared DOS16 source.

Current status: historical mapping **1,992 / 1,992**; current exact nodes
**1,238 / 1,992**; current exact feasible controls **2,495 / 4,324** (raw
**4,342**, infeasible **18**). The four source-owned material handoffs are
current-exact. `HandleEnemyFBallCol` remains S3 scope; no child implementation
is claimed by this closure.

## Current Technical Baseline

T64 S2 is closed at **1,238 / 1,992** current-exact nodes and **2,495 /
4,324** current-exact feasible controls. A successor is not admitted in this
packet.
