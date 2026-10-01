# Project Status

## Current Work

## M2 T62 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T62 S4 audit — Cohort I special initializer, Lakitu/Spiny and Firebar chain. |
| Admission And Approval | Continuing owner-approved T62 source-order program after closed S3; this packet admits S4 only. |
| Objective | Audit and repair `InitBulletBill -> InitShortFirebar` against original-ROM semantics. |
| Non-goals | Flying Cheep, Bowser/flame, terrain/distance, actor behavior, rendering and platform gameplay are outside S4. |
| Reference Baseline | Historical 1,992 / 1,992; current 874 / 1,992 nodes and 1,699 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md. |
| Files And ABI Surface | Shared `src/game/enemy/init_targets.c` and `src/game/enemy/frenzy.c`; no platform owner. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 special-initializer routes, focused C90 Lakitu/Spiny and Firebar checks, purity and DOS16 link. |
| Expected Markers | 22 nodes, 27 internal feasible controls, 2 raw infeasible fallthroughs and 6 internal material handoffs. |
| Asset Needs | Owner-supplied local ROM and derived recorder data stay below ignored build paths; source repair refreshes three local EXEs. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | Any feasible difference remains in S4 until repaired and re-audited. |
| Exit Criteria | Closed: all 22 nodes, 27 feasible internal controls and 6 material handoffs exact; no platform initializer rule. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Frenzy/timer gates, all slot scans, PRDiff table stride, original A-return dependency, Firebar table index, coordinate carry and direct no-extra-write entries. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; T62 S4 is closed and S5 remains unadmitted.

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
