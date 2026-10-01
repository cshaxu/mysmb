# Project Status

## Current Work

## M2 T59 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T59 S6 audit - friction and signed-speed chain. |
| Admission And Approval | Owner-approved source-order program; S5 is closed and S6 is admitted. |
| Objective | Audit and repair ImposeFriction through SetAbsSpd against original ROM semantics. |
| Non-goals | No unadmitted fireball, terrain, platform or next-cohort logic beyond declared handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 635 exact labels and 1,225 exact feasible relations. Scope has 6 labels. |
| Candidate Proposal | docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md. |
| Files And ABI Surface | Shared player owner plus project-owned tests; platform adapters are consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original friction snapshots, x86/x64 C90 replays, focused tests, DOS16 link and purity. |
| Expected Markers | Collision-filtered direction, released-input sign split, right-bit precedence, fractional carry/borrow, wrapped clamp tests and absolute-speed store. |
| Asset Needs | Audit only initially; any product repair refreshes all three artifacts. |
| Reporting Requirements | Report every scoped label/relation and both verification tracks before S closure. |
| Stop Conditions | Any unresolved source/C difference, route mismatch or platform game logic. |
| Exit Criteria | Scoped labels and feasible relations current-exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | All collision-filtered friction callers, signed-speed consumers and clamp paths. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T59 S5 is active.
