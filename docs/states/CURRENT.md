# Project Status

## Current Work

## M2 T64 S19 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S19 admitted — enemy background collision and landing state. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S18. |
| Objective | Audit $DFC0-$E07A enemy background collision and landing-state chain. |
| Non-goals | Enemy side collision begins in S20; no platform adaptation changes. |
| Reference Baseline | Historical 1,992 / 1,992; incoming current exact 1,401 / 1,992 nodes and 2,922 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | src/game/enemy/background.c, project-owned route/oracle harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | Static $DFC0-$E07A audit; controlled original-ROM enemy-background routes per x86/x64 width; focused background/landing and purity tests. |
| Expected Markers | 32 nodes; source-address-owned feasible controls recorded by the graph audit. |
| Asset Needs | Refresh all three artifacts only if shared product C changes. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current totals. |
| Stop Conditions | Any mismatch or missing route blocks closure. |
| Exit Criteria | Every scoped feasible path has an identical shared-C counterpart and original-ROM route evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | State-bit ordering, ID threshold dispatch, table offsets, landing alignment, direction and timer transitions. |

## Current Technical Baseline

T64 S19 is admitted at **1,401 / 1,992** current-exact nodes and **2,922 /
4,324** current-exact feasible controls. Historical conformance remains **1,992 /
1,992**.
