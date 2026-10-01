# Project Status

## Current Work

## M2 T62 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T62 S2 audit — Cohort I enemy stream record and group-decode chain. |
| Admission And Approval | Continuing owner-approved T62 source-order program after closed S1; this packet admits S2 only. |
| Objective | Audit and repair `ProcessEnemyData -> Inc2B` against original-ROM semantics. |
| Non-goals | Initializer interiors, actor behavior, rendering and platform gameplay are outside S2. |
| Reference Baseline | Historical 1,992 / 1,992; current 853 / 1,992 nodes and 1,653 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md. |
| Files And ABI Surface | Shared `src/game/enemy/stream.c`; initializer is an explicit downstream boundary. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 stream routes, focused C90 stream checks, purity and DOS16 link. |
| Expected Markers | 19 nodes, 38 internal feasible controls and 3 internal material handoffs. |
| Asset Needs | Owner-supplied local ROM and derived recorder data stay below ignored build paths; source repair refreshes three local EXEs. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | Any feasible difference remains in S2 until repaired and re-audited. |
| Exit Criteria | Closed: all 19 nodes, 38 feasible internal controls and 3 material handoffs exact; no platform enemy-stream rule. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Slot-five gates, record-length/cursor updates, page crossings, boundary ordering, group/frenzy records and initializer call boundaries. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; T62 S2 is closed pending S3 admission.

## T62 S1 Closure

`EnemiesAndLoopsCore -> ChkEnemyFrenzy` closed with 16 exact nodes, 27 feasible controls and three material handoffs. Historical migration remains **1,992 / 1,992**; current registry is **834 / 1,992** exact nodes and **1,615 / 4,324** feasible controls (raw **4,342**, infeasible **18**).

## T62 S2 Closure

`ProcessEnemyData -> Inc2B` is current-exact: 19 nodes, 38 feasible internal controls and three material handoffs passed `$C0D7-$C175` static comparison, 80 controlled original-ROM/current x86/x64 routes per width, boundary and full stream C90 checks, platform purity and DOS16 link. Historical migration remains **1,992 / 1,992**; current registry is **853 / 1,992** exact nodes and **1,653 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.
