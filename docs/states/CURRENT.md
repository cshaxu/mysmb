# Project Status

## Current Work

## M2 T63 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T63 S7 audit — Cohort J green Paratroopa and X-counter movement. |
| Admission And Approval | S7 admitted after S6 closure under the owner-approved source-order program. |
| Objective | Prove `MoveFlyGreenPTroopa -> XMRight` and owned relations current-exact. |
| Non-goals | No green-child gravity/horizontal interior, platform caller interior, collision, OAM or platform adapter change. |
| Reference Baseline | Historical 1,992 / 1,992; current 1,020 / 1,992 nodes and 2,023 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md. |
| Files And ABI Surface | Shared game `enemy/green_paratroopa.c`, `enemy/x_counter.c`; C90 only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | `$CB25-$CB59` audit; original-ROM/current x86/x64 green-counter route; focused checks, purity and DOS16 link. |
| Expected Markers | 10 nodes, 19 feasible controls and five material handoffs. |
| Asset Needs | Owner ROM and generated records remain below ignored build paths; refresh artifacts only if product source changes. |
| Reporting Requirements | Historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | Any source, route or boundary difference remains S7 repair work. |
| Exit Criteria | All 10 labels, 19 feasible controls and five material handoffs exact with both tracks. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Four-frame counter gate, primary/secondary rollover, horizontal sign/direction, child return and vertical sway. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T62 Cohort I
is closed. T63 S1/S2/S3/S4 are closed; S5 has closed normal/defeated enemy movement; S6 has closed jumping/red-Paratroopa movement; S7 has closed green-Paratroopa/X-counter movement. The next source-order chain is Bloober movement.


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


## T63 S5 Closure

`MoveNormalEnemy -> NKGmba` closes 11 labels, 28 feasible controls and four
material handoffs exact. Static `$CA77-$CAF8`, 264 fresh original-ROM/current
x86/x64 comparisons and 1,253,376 focused movement footprints per width agree.
Platform purity passes and DOS16 links with its known `OLDNAMES.LIB` warning.
No product source changed, so no artifact refresh applies. Historical mapping
is **1,992 / 1,992**; current exact status is **1,015 / 1,992 nodes** and
**2,013 / 4,324 feasible controls** (raw **4,342**, infeasible **18**).


## T63 S6 Closure

`MoveJumpingEnemy -> MovPTDwn` closes five labels, ten feasible controls and
four material handoffs exact. Static `$CAF9-$CB24`, 320 fresh original-ROM/current
x86/x64 comparisons and exhaustive focused contracts per width agree. Platform
purity passes and DOS16 links with its known `OLDNAMES.LIB` warning. No product
source changed, so no artifact refresh applies. Historical mapping is **1,992 /
1,992**; current exact status is **1,020 / 1,992 nodes** and **2,023 / 4,324
feasible controls** (raw **4,342**, infeasible **18**).


## T63 S7 Closure

`MoveFlyGreenPTroopa -> XMRight` closes ten labels, 19 feasible controls and
five material handoffs exact. Static `$CB25-$CB59`, 576 fresh original-ROM/current
x86/x64 comparisons and exhaustive counter contracts per width agree. Platform
purity passes and DOS16 links with its known `OLDNAMES.LIB` warning. No source
changed, so no artifact refresh applies. Historical mapping is **1,992 / 1,992**;
current exact status is **1,030 / 1,992 nodes** and **2,042 / 4,324 feasible
controls** (raw **4,342**, infeasible **18**).
