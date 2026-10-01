# Project Status

## Current Work

## M2 T59 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T59 S2 audit - ground, air and water movement chain. |
| Admission And Approval | Owner-approved source-order program; S1 is closed and S2 is admitted. |
| Objective | Audit and repair MoveSubs through ExitMov1 against original ROM semantics. |
| Non-goals | No unadmitted physics, animation, friction, climb, fireball or platform semantics beyond declared handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 581 exact labels and 1,124 exact feasible relations. Scope has 12 labels. |
| Candidate Proposal | docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md. |
| Files And ABI Surface | Shared player movement owner and project-owned tests; platform adapters are consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original movement snapshots, x86/x64 C90 caller replays, focused tests, DOS16 link and purity. |
| Expected Markers | State vector, growth freeze, climb timer, water/air predicates and movement ordering. |
| Asset Needs | Audit only initially; any product repair refreshes all three artifacts. |
| Reporting Requirements | Report every scoped label/relation and both verification tracks before S closure. |
| Stop Conditions | Any unresolved source/C difference, route mismatch or platform game logic. |
| Exit Criteria | Scoped labels and feasible relations current-exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | State-vector callers, movement child ordering and vertical-force consumers. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T59 S2 is active.
