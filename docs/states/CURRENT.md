# Project Status

## Current Work

## M2 T60 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T60 S4 audit - Cohort G game timer and warp chain. |
| Admission And Approval | S3 closed with no feasible mismatch; source-order S4 is admitted. |
| Objective | Prove `RunGameTimer -> WarpZoneObject` against original ROM behavior. |
| Non-goals | No bubble or fireball-core work, platform logic or unrelated repair. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 660 exact labels and 1,298 exact feasible relations; five scoped labels need evidence. |
| Candidate Proposal | docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md. |
| Files And ABI Surface | Shared timer and world owner boundaries; platform adapters remain consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM/current x86/x64 timer/warp routes, focused smoke, shared DOS16 link and platform purity. |
| Expected Markers | Mode exits, timer cadence, digit borrow, time-up latch and warp-zone transfer. |
| Asset Needs | Audit initially; a shared-game repair refreshes all three assets. |
| Reporting Requirements | Report all five labels, owned relations and both tracks at closure. |
| Stop Conditions | Any unresolved feasible ROM/C difference or platform-owned game logic. |
| Exit Criteria | All S4 labels and owned feasible relations exact, or repaired then re-audited. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Timer writers/readers, digit-borrow consumers and warp-area handoff consumers. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T60 S4 is active; all game behavior remains in shared C owners.
