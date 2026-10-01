# Project Status

## Current Work

## M2 T61 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S2 audit - Cohort H cannon and Bullet Bill lifecycle. |
| Admission And Approval | Owner-approved M2 source-order proof program; S1 is closed and this packet admits T61 S2 only. |
| Objective | Audit and, if required, repair shared-C `CannonBitmasks -> KillBB` behavior against original-ROM control, state, material and output semantics. |
| Non-goals | No offscreen, movement, relative-position, bounding-box, collision, graphics, erase, dispatcher, or platform-adapter child semantic claim beyond named S2 handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current re-audit: 696 / 1,992 exact nodes and 1,391 / 4,324 exact feasible control relations. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | `src/game/cannon.c` and existing named shared game children; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Controlled original-ROM/current x86/x64 cannon and Bullet Bill routes; focused native route, cross-width comparison, shared DOS16 link and platform purity. |
| Expected Markers | Met: fourteen labels, 26 internal feasible relations and two material bindings are current-exact; x86/x64 records agree. |
| Asset Needs | Audit initially; any shared-game repair refreshes all three local executable artifacts. |
| Reporting Requirements | State S2's 14 label dispositions, both verification tracks, every boundary disposition, historical 1,992 / 1,992, exact nodes / 1,992 and exact feasible control relations / 4,324. |
| Stop Conditions | None remain in S2. |
| Exit Criteria | Met: all 14 labels and owned feasible relations are current-exact; no platform adapter contains game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Cannon scheduler, random mask, timer decrement/spawn carry, Bullet Bill direction/proximity, timer-control movement gate, descent, child call and erase boundaries. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T61 S2 is the sole active packet.

## T61 S2 Closure

All 14 cannon and Bullet Bill labels, 26 internal feasible control relations and two material bindings are current-exact. The fresh original-ROM/current route proof records 25 ROM routes and 50 current x86/x64 runs, with 1,782 persistent RAM bytes and complete output matching per route. Focused smoke, dispatcher static contract, platform purity and DOS16 link pass. No product source changed, so executable artifacts were not refreshed.
