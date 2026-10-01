# Project Status

## Current Work

## M2 T63 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T63 S2 audit — Cohort J small/large platform caller and movement-vector bridge. |
| Admission And Approval | S2 closed after ROM-logic and operational tracks agreed; T63 S3 remains unadmitted. |
| Objective | Prove four platform caller/vector labels and their direct edges current-exact before lifecycle/Podoboo. |
| Non-goals | No platform child interior, lifecycle/Podoboo chain, terrain/collision logic, or platform adapter change. |
| Reference Baseline | Historical 1,992 / 1,992; current 988 / 1,992 nodes and 1,950 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md. |
| Files And ABI Surface | `src/game/enemy/platform_callers.c`; shared game C90 only; no platform logic. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | `$C5BB-$C5E9` audit; original-ROM/current x86/x64 platform caller route; focused caller check; purity and DOS16 link. |
| Expected Markers | Four nodes, 27 feasible direct controls, and five material handoffs promoted only if both tracks agree. |
| Asset Needs | Owner ROM and generated records remain below ignored build paths; refresh three artifacts only if product source changes. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | A source, route or boundary difference keeps S1 open for shared-owner repair and re-audit. |
| Exit Criteria | All four platform caller/vector labels, 27 feasible direct controls and five material handoffs are current-exact with current source and route evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Small/large platform callers: child order, TimerControl skip, vector index/scratch, lift alias, bounds tail and ownership. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T62 Cohort I
is closed. T63 S1 and S2 are closed; T63 S3 remains the next source-order lifecycle/Podoboo chain.


## T63 S1 Closure

`RunFirebarObj` closes exact with its two direct controls and one material
handoff. Current-source x86/x64 replay passes 64 Firebar caller comparisons;
the focused caller test covers 3,072 footprints per width, platform purity
passes and DOS16 links with its known `OLDNAMES.LIB` warning. No source code
changed, so no artifact refresh applies. Historical mapping is **1,992 / 1,992**;
current exact status is **984 / 1,992 nodes** and **1,924 / 4,324 feasible
controls** (raw **4,342**, infeasible **18**).


## T63 S2 Admission

S2 covers `RunSmallPlatform -> LargePlatformSubroutines`: four labels, 27
feasible direct controls and five material handoffs. It excludes platform
children and lifecycle/Podoboo. Historical mapping is **1,992 / 1,992**;
current exact status is **984 / 1,992 nodes** and **1,924 / 4,324** feasible
controls (raw **4,342**, infeasible **18**).


## T63 S2 Closure

`RunSmallPlatform -> LargePlatformSubroutines` closes four labels, 27 feasible
controls and five material handoffs exact. Fresh original-ROM/current x86/x64
caller replay passes 72 platform comparisons and focused 3,240 footprints per
width; purity passes and DOS16 links with its known warning. No product source
changed, so no artifact refresh applies. Historical mapping is **1,992 / 1,992**;
current exact status is **988 / 1,992 nodes** and **1,950 / 4,324** feasible
controls (raw **4,342**, infeasible **18**).
