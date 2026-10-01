# Project Status

## Current Work

## M2 T58 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T58 S2 closure — Cohort E scroll threshold and player-edge chain. |
| Admission And Approval | Owner-approved M2 source-order proof program; T58 S2 is closed; no successor S is admitted by this packet. |
| Objective | Audit and, if required, repair shared-C `ScrollHandler -> GetScreenPosition` against the original-ROM control, state, table and output contract. |
| Non-goals | No player physics, pipe-entry, offscreen-bit producer, renderer or platform-adapter semantic claim beyond declared caller/return handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 520 exact / 1,472 needs-evidence labels; 971 exact / 3,353 needs-evidence feasible control relations. S2 scope: ten labels, all ten are current-exact after dual proof; 27 feasible incident relations are exact, 25 with fresh S2 evidence and two retaining compatible prior proof. Historical expected delta: zero. |
| Candidate Proposal | docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md. |
| Files And ABI Surface | Shared `src/game/scroll.c`, `src/game/player.h`, project-owned scroll tests/recorders and evidence; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | 24 original-ROM natural-entry snapshots; x86/x64 C90 snapshot checks; exhaustive focused scroll test; platform-purity. |
| Expected Markers | Force addition, `$50`/`$70` signed gates, scroll/page carry, PPU mirror bit zero, two edge tables, edge borrow, speed predicate and right-screen `$ff` carry. |
| Asset Needs | Audit-only conclusion: no shared product source changed, so the three target artifacts are unchanged. |
| Reporting Requirements | Report all ten named labels, their after state, 27 feasible relation dispositions, both verification tracks and the absence of a repair before S3 admission. |
| Stop Conditions | No S2 stop condition remains; S3 is not admitted. |
| Exit Criteria | Met: all scoped labels and feasible incident relations are current-exact; no platform adapter contains game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Scroll callers, force carry, page/nametable state, raw offscreen-bit polarity, edge-table lookup, page borrow and return handoffs. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T58 S2 is closed. S3 is not admitted.
