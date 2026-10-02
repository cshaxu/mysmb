# Project Status

## Current Work

## M2 T64 S20 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S20 admitted — enemy side-collision loop. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S19. |
| Objective | Audit `$E0B0-$E0D7` enemy side-collision loop. |
| Non-goals | Bump/hammer response begins in S21; no platform adaptation changes. |
| Reference Baseline | Historical 1,992 / 1,992; incoming current exact 1,433 / 1,992 nodes and 3,000 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | src/game/enemy/side_collision.c, project-owned route/oracle harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | Static `$E0B0-$E0D7` audit; controlled original-ROM enemy-side routes per x86/x64 width; focused side/jump-hammer and purity tests. |
| Expected Markers | 4 nodes; source-address-owned feasible controls recorded by the graph audit. |
| Asset Needs | Refresh all three artifacts only if shared product C changes. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current totals. |
| Stop Conditions | Any mismatch or missing route blocks closure. |
| Exit Criteria | Every scoped feasible path has an identical shared-C counterpart and original-ROM route evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | Direction loop ordering, probe offsets, status-bar gate, non-solid predicate and return ordering. |

## Current Technical Baseline

T64 S20 is admitted at **1,433 / 1,992** current-exact nodes and **3,000 /
4,324** current-exact feasible controls. Historical conformance remains **1,992 /
1,992**.
