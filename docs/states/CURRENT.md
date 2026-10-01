# Project Status

## Current Work

## M2 T63 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T63 S4 audit — Cohort J Hammer Bro throw, jump and horizontal bridge. |
| Admission And Approval | S4 admitted after S3 closure under the owner-approved source-order program. |
| Objective | Prove `HammerThrowTmrData -> SetShim` and its owned relations current-exact before normal-enemy movement. |
| Non-goals | No normal/defeated movement child interior, Hammer sprite/OAM, terrain/collision logic, or platform adapter change. |
| Reference Baseline | Historical 1,992 / 1,992; current 991 / 1,992 nodes and 1,961 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md. |
| Files And ABI Surface | `src/game/enemy/hammer_bro.c`; shared game C90 only; no platform logic. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | `$C9CE-$CA76` audit; original-ROM/current x86/x64 Hammer Bro route; focused checks; purity and DOS16 link. |
| Expected Markers | 13 nodes, 24 feasible controls and eight material handoffs promoted only if both tracks agree. |
| Asset Needs | Owner ROM and generated records remain below ignored build paths; refresh three artifacts only if product source changes. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | A source, route or boundary difference keeps S4 open for shared-owner repair and re-audit. |
| Exit Criteria | All 13 labels, 24 feasible controls and eight material handoffs are current-exact with current source and route evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Hammer Bro tables, defeated precedence, timer gates, spawn result, PRNG jump selection, shimmy, direction and normal-move handoff. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T62 Cohort I
is closed. T63 S1/S2/S3/S4 are closed; the next source-order chain is normal/defeated enemy movement.


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


## T63 S3 Admission

S3 covers `EraseEnemyObject -> PdbM`: three labels, 11 feasible controls and
three material handoffs. Historical mapping is **1,992 / 1,992**; current
exact status is **988 / 1,992 nodes** and **1,950 / 4,324** feasible controls
(raw **4,342**, infeasible **18**).


## T63 S3 Closure

`EraseEnemyObject -> PdbM` closes three labels, 11 feasible controls and three
material handoffs exact. Static `$C998-$C9CD`, 128 fresh original-ROM/current
x86/x64 Podoboo caller comparisons, focused 6,144 Podoboo and 3,240 lifecycle
footprints per width, purity and DOS16 link agree. No product source changed,
so no artifact refresh applies. Historical mapping is **1,992 / 1,992**;
current exact status is **991 / 1,992 nodes** and **1,961 / 4,324 feasible
controls** (raw **4,342**, infeasible **18**).


## T63 S4 Admission

S4 covers `HammerThrowTmrData -> SetShim`: 13 labels, 24 feasible controls
and eight material handoffs. Historical mapping is **1,992 / 1,992**; current
exact status is **991 / 1,992 nodes** and **1,961 / 4,324** feasible controls
(raw **4,342**, infeasible **18**).


## T63 S4 Closure

`HammerThrowTmrData -> SetShim` closes 13 labels, 24 feasible controls and
eight material handoffs exact. Static `$C9CE-$CA76`, 712 fresh original-ROM /
current x86/x64 route comparisons, focused 12,288 caller footprints per width,
purity and DOS16 link agree. No product source changed, so no artifact refresh
applies. Historical mapping is **1,992 / 1,992**; current exact status is
**1,004 / 1,992 nodes** and **1,985 / 4,324 feasible controls** (raw
**4,342**, infeasible **18**).
