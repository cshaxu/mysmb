# Project Status

## Current Work

## M2 T62 S9 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T62 S9 audit — Cohort I actor and movement dispatcher chain. |
| Admission And Approval | S9 closed after static and operational evidence; the T62 Cohort-I chain is complete. |
| Objective | Audit and repair `RunEnemyObjectsCore -> RunBowserFlame` against original-ROM semantics. |
| Non-goals | Firebar and later actor interiors, rendering and platform-specific gameplay are outside S9. |
| Reference Baseline | Historical 1,992 / 1,992; current 983 / 1,992 nodes and 1,922 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md. |
| Files And ABI Surface | Shared `src/game/enemy/core.c`, `normal.c` and `dispatch_targets.c`; no platform owner. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 actor-dispatch routes, focused C90 contracts, purity and DOS16 link. |
| Expected Markers | 9 nodes, 98 feasible internal controls and 6 material handoffs. |
| Asset Needs | Owner-supplied local ROM and derived recorder data stay below ignored build paths; source repair refreshes three local EXEs. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | No feasible difference remains in S9; every scoped path is closed. |
| Exit Criteria | Closed: all 9 nodes, 98 feasible internal controls and 6 material handoffs exact; no platform gameplay rule. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Actor/vector selector bounds and scratch, normal caller order/timer skip, retainer and flame tails. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; T62 S9 is closed; T62 Cohort-I source-order chains are complete.

## T62 S1 Closure

`EnemiesAndLoopsCore -> ChkEnemyFrenzy` closed with 16 exact nodes, 27 feasible controls and three material handoffs. Historical migration remains **1,992 / 1,992**; current registry is **834 / 1,992** exact nodes and **1,615 / 4,324** feasible controls (raw **4,342**, infeasible **18**).

## T62 S2 Closure

`ProcessEnemyData -> Inc2B` is current-exact: 19 nodes, 38 feasible internal controls and three material handoffs passed `$C0D7-$C175` static comparison, 80 controlled original-ROM/current x86/x64 routes per width, boundary and full stream C90 checks, platform purity and DOS16 link. Historical migration remains **1,992 / 1,992**; current registry is **853 / 1,992** exact nodes and **1,653 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.

## T62 S3 Closure

`CheckpointEnemyID -> InitVStf` is current-exact: 21 nodes, 46 feasible
internal controls and three material handoffs passed `$C180-$C22C` static
comparison, 110 controlled original-ROM/current x86/x64 caller routes per
width, 84,480 vector-handoff cases and 23,046 common-initializer footprint
cases per width, platform purity and DOS16 link. Historical migration remains
**1,992 / 1,992**; current registry is **874 / 1,992** exact nodes and
**1,699 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**).
No product source changed.

## T62 S4 Closure

`InitBulletBill -> InitShortFirebar` is current-exact: 22 nodes, 27 feasible internal controls and six material handoffs passed static `$C233-$C2D3`, original-ROM/current x86/x64 Lakitu/Spiny and Firebar routes, focused footprints, platform purity and DOS16 link. Historical migration is **1,992 / 1,992**; current registry is **896 / 1,992** exact nodes and **1,726 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.

## T62 S5 Closure

`FlyCCXPositionData -> SetFrT` is current-exact: 18 nodes, 21 feasible internal controls and five material handoffs passed static `$C2EA-$C395`, 624 actual original-ROM/current x86/x64 routes, focused C90 footprints, platform purity and DOS16 link. Historical migration is **1,992 / 1,992**; current registry is **914 / 1,992** exact nodes and **1,747 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.

## T62 S6 Closure

`PutAtRightExtent -> FireBulletBill` is current-exact: 23 nodes, 29 feasible internal controls and six material handoffs passed static `$C39C-$C43F`, fresh current original-ROM/x86/x64 routes and focused C90 footprints. The snapshot routes total 462 per width: 120 fireworks, 160 Bowser flame and 182 Bullet Bill/Cheep. Historical mapping is **1,992 / 1,992**; current registry is **937 / 1,992** exact nodes and **1,776 / 4,324** feasible controls (raw **4,342**, infeasible **18**). No product source changed.
