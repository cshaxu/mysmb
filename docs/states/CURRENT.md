# Project Status

## Current Work

## M2 T59 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T59 S3 audit - climb movement and vertical-force binding. |
| Admission And Approval | Owner-approved source-order program; S2 is closed and S3 is admitted. |
| Objective | Audit and repair ClimbAdderLow through InitMForceData against original ROM semantics. |
| Non-goals | No unadmitted jump, horizontal physics, animation, friction, fireball or platform semantics beyond declared handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 593 exact labels and 1,159 exact feasible relations. Scope has 12 labels. |
| Candidate Proposal | docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md. |
| Files And ABI Surface | Shared player and player-movement owners plus project-owned tests; platform adapters are consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original climbing and force-table snapshots, x86/x64 C90 replays, focused tests, DOS16 link and purity. |
| Expected Markers | Fractional and page coordinate carries, direction/facing inversion, climb-side timer and all four table selections. |
| Asset Needs | Audit only initially; any product repair refreshes all three artifacts. |
| Reporting Requirements | Report every scoped label/relation and both verification tracks before S closure. |
| Stop Conditions | Any unresolved source/C difference, route mismatch or platform game logic. |
| Exit Criteria | Scoped labels and feasible relations current-exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Adjacent vertical-force data users, vine movement consumers and direction-dependent coordinate updates. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T59 S3 is active.
