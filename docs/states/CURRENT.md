# Project Status

## Current Work

## M2 T56 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T56 S6 - low question-row, bridge and residual flag-ball current-equivalence audit. |
| Admission And Approval | T56 S5 is closed; the owner-approved source-order program admits T56 S6. |
| Objective | Audit `QuestionBlockRow_Low` through `FlagBalls_Residual`, repair every feasible shared-C mismatch, and repeat ROM/native evidence until every scoped node and relation is exact. |
| Non-goals | No historical-node credit, no platform rendering/input decisions, and no expansion beyond the final T56 special-row chain. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 348 exact and 1,644 needs-evidence nodes; 757 exact feasible controls. Scope: 5 labels; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`; focused parser recorder/tests only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: shared low-row entry, bridge selectors, helper order, rail/body metatile writes and flag-ball extent. Operational: controlled original-ROM/x86/x64 routes, focused parser tests, DOS16 build if product source changes, and platform-purity audit. |
| Expected Markers | Special-row selector, object length, staged bridge/question metatiles and flag-ball extent remain in shared C. |
| Asset Needs | Refresh all three artifacts only if product source changes. |
| Reporting Requirements | Report all five labels and every scoped feasible relation with separate static and operational results; repair and re-audit before T56 closure. |
| Stop Conditions | A feasible ROM/C difference remains after repair, a relation lacks a shared-C counterpart, or platform code makes an area-parser decision. |
| Exit Criteria | Every scoped node and feasible relation is exact under source and controlled-route evidence; no successor is admitted while a mismatch remains. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Low-row common entry, bridge row selectors, helper carry/length state, rail/body ordering and residual ball height. |

## T56 S5 Closure

S5 closes 22 current-exact castle/pipe/allocation/high-row nodes, 49 feasible control relations and two material relations. Original-ROM/current x86/x64 vertical-pipe, question-row and special-object routes agree; x86/x64 are byte-identical. No product source changed. Historical conformance remains 1,992 / 1,992.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T56 S6 is active for the final low question-row, bridge and residual flag-ball chain.
