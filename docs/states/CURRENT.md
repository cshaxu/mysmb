# Project Status

## Current Work

## M2 T58 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T58 S3 admission — Cohort E game routine, entrance and player-control chain. |
| Admission And Approval | Owner-approved M2 source-order proof program; S2 is closed and S3 is formally admitted. |
| Objective | Audit and, if required, repair shared-C `GameRoutines -> CloudExit` against the original-ROM control, state, table and output contract. |
| Non-goals | No child movement, pipe transition, OAM, collision, mode or platform-adapter semantic claim beyond the named call/return handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 520 exact / 1,472 needs-evidence labels; 971 exact / 3,353 needs-evidence feasible control relations. S3 scope: 23 labels, all incoming `needs-evidence`; expected current delta: 23 labels and 92 unresolved feasible relations, maximum 543 / 1,992 and 1,063 / 4,324. Historical expected delta: zero. |
| Candidate Proposal | docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md. |
| Files And ABI Surface | Shared `src/game/entry.c`, `src/game/player_control.c`, their declared child interfaces and project-owned tests/recorders; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM `t31-entrance` and `t32` player-control controlled routes; x86/x64 C90 owner replays; focused entry/control/caller tests; DOS16 shared-core link; platform-purity. |
| Expected Markers | 13-vector dispatch, pipe/vine/ordinary entrance choice, controller suppression/partition/crouch gates, selector writes, child order, scroll handoff, hole thresholds and cloud exit. |
| Asset Needs | Audit only initially. Any shared product-source repair rebuilds and validates all three target artifacts. |
| Reporting Requirements | Report all 23 named labels, after state, every feasible relation disposition, both tracks and any repair before S4 admission. |
| Stop Conditions | Any unresolved feasible source/C difference, route mismatch, unverified child handoff or platform code holding game semantics. |
| Exit Criteria | All scoped labels and feasible incident relations are current-exact; no platform adapter contains game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Dispatch vectors, alternate-entry values, pipe timer wrap, input masks, crouch suppression, signed direction, child call/return handoffs, death music and cloud transfer. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T58 S3 is active. S4 is not admitted.
