# Project Status

## Current Work

## M2 T59 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T59 S4 audit - player physics, jump and horizontal-speed chain. |
| Admission And Approval | Owner-approved source-order program; S3 is closed and S4 is admitted. |
| Objective | Audit and repair MaxLeftXSpdData through ExitPhy against original ROM semantics. |
| Non-goals | No unadmitted animation execution, directional friction execution, terrain collision, fireball or platform semantics beyond declared handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 605 exact labels and 1,168 exact feasible relations. Scope has 24 labels. |
| Candidate Proposal | docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md. |
| Files And ABI Surface | Shared player and player-movement owners plus project-owned tests; platform adapters are consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original player-physics snapshots, x86/x64 C90 replays, focused tests, DOS16 link and purity. |
| Expected Markers | Physics-state dispatch, table selection, jump/swim gates, sound queue, run timer, friction and speed-limit writes. |
| Asset Needs | Audit only initially; any product repair refreshes all three artifacts. |
| Reporting Requirements | Report every scoped label/relation and both verification tracks before S closure. |
| Stop Conditions | Any unresolved source/C difference, route mismatch or platform game logic. |
| Exit Criteria | Scoped labels and feasible relations current-exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Adjacent force-table consumers, jump initiation callers, run-speed consumers and horizontal limit users. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T59 S4 is active.
