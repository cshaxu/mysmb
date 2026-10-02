# Project Status

## Current Work

## M2 T64 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S5 admitted — power-up pickup response. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S4. |
| Objective | Audit `HandlePowerUpCollision -> NoPUp` at `$D800-$D84C`: common erase/score/sound prefix, type dispatch, 1UP overwrite, super/fiery status transitions, palette ordering, routine tail and star return. |
| Non-goals | Erase, score, palette and player-routine child implementations remain under their independently admitted owners; this S proves their caller contracts. |
| Reference Baseline | Historical 1,992 / 1,992; incoming current exact 1,252 / 1,992 nodes and 2,529 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | `src/game/world/powerup_collision.c` and project-owned C90 test/oracle harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | Static `$D800-$D84C` audit, retained original-ROM pickup routes per x86/x64 width, focused pickup contract, platform purity and DOS16 link. |
| Expected Markers | Six nodes, 11 source-owned controls and six material handoffs. |
| Asset Needs | No product C change is expected; refresh all three artifacts only if shared product C changes. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current totals. |
| Stop Conditions | Any mismatch or missing route blocks closure. |
| Exit Criteria | Every scoped feasible path has identical C counterpart and original-ROM route evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | Child-mutated type/status, type two versus three, common-prefix ordering, nonzero non-super status, palette return, routine arguments and star-versus-1UP terminal writes. |

## Current Technical Baseline

T64 S5 is admitted at **1,252 / 1,992** current-exact nodes and **2,529 /
4,324** current-exact feasible controls. Historical conformance remains **1,992 /
1,992**. The S5 scoped labels are `HandlePowerUpCollision`,
`Shroom_Flower_PUp`, `SetFor1Up`, `UpToSuper`, `UpToFiery` and `NoPUp`.
