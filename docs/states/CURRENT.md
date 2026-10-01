# Project Status

## Current Work

## M2 T58 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T58 S1 closure — Cohort E game dispatcher and engine tail. |
| Admission And Approval | Owner-approved M2 source-order proof program; T58 S1 is closed; no successor S is admitted by this packet. |
| Objective | Audit and, if required, repair the shared-C `GameMode -> ExitEng` chain against its original-ROM control, state and output contract. |
| Non-goals | No child-actor, collision, OAM, timer, music or platform-adapter semantic claim beyond S1 call/return handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 499 exact / 1,493 needs-evidence labels; 888 exact / 3,436 needs-evidence feasible control relations. S1 scope: 11 labels, all 11 are current-exact after dual proof; historical expected delta: zero. |
| Candidate Proposal | docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md. |
| Files And ABI Surface | Shared `src/game/dispatcher.c`, `engine.c`, `engine_slots.c` and `engine_tail.c`; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 GameMode selector and source-reachable GameEngine route; focused dispatcher/engine tests, DOS16 shared-core link and platform-purity. |
| Expected Markers | All 11 scoped labels and 70 feasible incident controls have static and controlled-route proof; output widths are byte-identical. |
| Asset Needs | Audit only initially. Any shared product-source repair rebuilds and validates all three target artifacts. |
| Reporting Requirements | Report the 11 named labels, their before/after registry state, every feasible relation disposition, both verification tracks and any repair before S2 admission. |
| Stop Conditions | No S1 stop condition remains; S2 has not been admitted. |
| Exit Criteria | Met: all scoped labels and feasible incident relations are current-exact; no platform adapter contains game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Selector fallthrough, player-index reload, actor-loop slot/order, return handoffs, music/palette branch predicates, input partition clearing and parser-tail gates. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T58 S1 is closed; T58 S2 has not been admitted.
