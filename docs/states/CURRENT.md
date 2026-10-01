# Project Status

## Current Work

## M2 T63 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T63 S1 audit — Cohort J Firebar actor caller/bounds bridge. |
| Admission And Approval | S1 closed after ROM-logic and operational tracks agreed; T63 S2 remains unadmitted. |
| Objective | Prove `RunFirebarObj` and its two direct control relations current-exact before admitting the next source-owner chain. |
| Non-goals | No Firebar interior, offscreen-bounds interior, platform caller, platform behavior, or platform adapter change. |
| Reference Baseline | Historical 1,992 / 1,992; current 984 / 1,992 nodes and 1,924 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md. |
| Files And ABI Surface | `src/game/enemy/special_callers.c`; shared game C90 only; no platform logic. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | `$C5B5-$C5B9` source audit; controlled original-ROM/current x86/x64 Firebar caller route; focused caller check; purity and DOS16 link. |
| Expected Markers | One node, two feasible direct controls, and one material handoff promoted only if both tracks agree. |
| Asset Needs | Owner ROM and generated records remain below ignored build paths; refresh three artifacts only if product source changes. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | A source, route or boundary difference keeps S1 open for shared-owner repair and re-audit. |
| Exit Criteria | `RunFirebarObj`, both direct controls and its bounds material handoff are current-exact with current source and route evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | All special actor callers: child return handling, unconditional bounds tail, slot preservation and platform/actor boundary ownership. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T62 Cohort I
is closed. T63 S1 has closed the source-order Firebar actor-caller boundary.


## T63 S1 Closure

`RunFirebarObj` closes exact with its two direct controls and one material
handoff. Current-source x86/x64 replay passes 64 Firebar caller comparisons;
the focused caller test covers 3,072 footprints per width, platform purity
passes and DOS16 links with its known `OLDNAMES.LIB` warning. No source code
changed, so no artifact refresh applies. Historical mapping is **1,992 / 1,992**;
current exact status is **984 / 1,992 nodes** and **1,924 / 4,324 feasible
controls** (raw **4,342**, infeasible **18**).
