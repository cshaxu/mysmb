# Project Status

## Current Work

## M2 T59 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T59 S1 audit - player movement dispatcher and crouch gate. |
| Admission And Approval | Owner-approved source-order program; T58 is closed and T59 S1 is admitted. |
| Objective | Audit and repair PlayerMovementSubs through ProcMove against original ROM semantics. |
| Non-goals | No unadmitted physics, animation, friction, fireball or platform semantics beyond declared handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 578 exact labels and 1,115 exact feasible relations. Scope has 3 labels. |
| Candidate Proposal | docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md. |
| Files And ABI Surface | Shared player movement owner and project-owned tests; platform adapters are consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original movement snapshots, x86/x64 C90 caller replays, focused tests, DOS16 link and purity. |
| Expected Markers | Crouch predicate, button mask, ordered child handoffs and player-state gate. |
| Asset Needs | Audit only initially; any product repair refreshes all three artifacts. |
| Reporting Requirements | Report every scoped label/relation and both verification tracks before S closure. |
| Stop Conditions | Any unresolved source/C difference, route mismatch or platform game logic. |
| Exit Criteria | Scoped labels and feasible relations current-exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Movement dispatcher callers, crouch state consumers and child ordering. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T59 S1 is active.
