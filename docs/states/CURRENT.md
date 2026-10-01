# Project Status

## Current Work

## M2 T58 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T58 S2 admission — Cohort E scroll threshold and player-edge chain. |
| Admission And Approval | Owner-approved M2 source-order proof program; S1 is closed and S2 is formally admitted. |
| Objective | Audit and, if required, repair shared-C `ScrollHandler -> GetScreenPosition` against the original-ROM control, state, table and output contract. |
| Non-goals | No player physics, pipe-entry, offscreen-bit producer, renderer or platform-adapter semantic claim beyond declared caller/return handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 510 exact / 1,482 needs-evidence labels; 946 exact / 3,378 needs-evidence feasible control relations. S2 scope: ten labels, all ten incoming `needs-evidence`; expected current delta: ten labels and 26 unresolved feasible relations, maximum 520 / 1,992 and 972 / 4,324. Historical expected delta: zero. |
| Candidate Proposal | docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md. |
| Files And ABI Surface | Shared `src/game/scroll.c`, `src/game/player.h`, project-owned scroll tests/recorders and evidence; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM source/natural-entry scroll matrix; x86/x64 snapshot checks; focused scroll test; DOS16 shared-core link; platform-purity. |
| Expected Markers | Force addition, `$50`/`$70` signed gates, scroll/page carry, PPU mirror bit zero, two edge tables, edge borrow, speed predicate and right-screen `$ff` carry. |
| Asset Needs | Audit only initially. Any shared product-source repair rebuilds and validates all three target artifacts. |
| Reporting Requirements | Report all ten named labels, incoming/after registry state, each feasible relation disposition, both verification tracks and any repair before S3 admission. |
| Stop Conditions | Any unresolved feasible source/C difference, a route mismatch, unverified table binding or platform code holding game semantics. |
| Exit Criteria | All scoped labels and feasible incident relations are current-exact; no platform adapter contains game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Scroll callers, force carry, page/nametable state, raw offscreen-bit polarity, edge-table lookup, page borrow and return handoffs. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T58 S2 is active. S3 is not admitted.
