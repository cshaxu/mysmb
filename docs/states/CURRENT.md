# Project Status

## Current Work

## M2 T64 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S1 admitted — Cohort J enemy offscreen-bound chain. |
| Admission And Approval | Owner-approved continuation of the M2 current-equivalence source-order program after closed T63. |
| Objective | Audit `OffscreenBoundsCheck -> ExScrnBd` at `$D67A-$D6D5`: `OffscreenBoundsCheck`, `LimitB`, `ExtendLB`, `TooFar`, and `ExScrnBd`; repair any shared-C mismatch before closure. |
| Non-goals | No node outside the five-label chain, no platform-specific game behavior, and no historical-custody transfer. |
| Reference Baseline | Historical 1,992 / 1,992; current exact 1,227 / 1,992 nodes and 2,461 / 4,324 feasible controls (4,342 raw; 18 infeasible). |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | `src/game/enemy/actor_slots.c` and focused project-owned test harnesses; portable C90 shared game layer. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | ROM-logic: all ID/carry/page-bound branches, scratch reads/writes, erase call and returns against the controlled original-ROM record family. Operational: one-process x86/x64 manifest replay, exhaustive bound oracle, platform-purity check and OpenNT DOS16 shared-source link. |
| Expected Markers | Five current-exact nodes and every source-owned feasible control/material relation; any mismatch remains in S1 for repair and re-audit. |
| Asset Needs | Owner-supplied local SMB1 NROM is consumed only below ignored `build/m2-t64-s1` to replay the controlled 1,024 record family. No ROM, derived record, build output, or executable is tracked. Refresh three products only if product C changes. |
| Reporting Requirements | Report exact scoped/expected/completed/deferred labels, relation disposition, and historical/current node/control totals. |
| Stop Conditions | A ROM/C mismatch, missing controlled route or platform-purity failure prevents S1 closure and successor admission. |
| Exit Criteria | Both tracks show no unresolved scoped difference; tracker/ledger record every disposition and closure has an accepted receiver for any retained incomplete label. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | Carry/borrow propagation, page-bound comparisons, special-ID exclusions, scratch-byte ownership, erase call/return and platform-boundary purity. |

## Current Technical Baseline

T63 is closed at 1,227 current-exact nodes and 2,461 current-exact feasible
controls. T64 S1 is the sole active packet; its five-label forecast reaches at
most 1,232 current-exact nodes after both verification tracks pass.
