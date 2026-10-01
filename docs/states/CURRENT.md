# Project Status

## Current Work

## M2 T59 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T59 S5 audit - animation speed and skid chain. |
| Admission And Approval | Owner-approved source-order program; S4 is closed and S5 is admitted. |
| Objective | Audit and repair PlayerAnimTmrData through SetAnimSpd against original ROM semantics. |
| Non-goals | No unadmitted friction execution, physics parameter, terrain, fireball or platform semantics beyond declared handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 629 exact labels and 1,216 exact feasible relations. Scope has 6 labels. |
| Candidate Proposal | docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md. |
| Files And ABI Surface | Shared player owner plus project-owned tests; platform adapters are consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original animation-speed snapshots, x86/x64 C90 replays, focused tests, DOS16 link and purity. |
| Expected Markers | Timer table index, running speed, direction comparison, low-speed skid writes and animation-timer output. |
| Asset Needs | Audit only initially; any product repair refreshes all three artifacts. |
| Reporting Requirements | Report every scoped label/relation and both verification tracks before S closure. |
| Stop Conditions | Any unresolved source/C difference, route mismatch or platform game logic. |
| Exit Criteria | Scoped labels and feasible relations current-exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Animation-timer table consumers, running-speed writers and moving-direction reset paths. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T59 S5 is active.
