# Project Status

## Current Work

## M2 T56 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T56 S5 - castle finish, pipe, allocation and high question-row current-equivalence audit. |
| Admission And Approval | T56 S4 is closed; the owner-approved source-order program admits T56 S5. |
| Objective | Audit `PlayerStop` through `QuestionBlockRow_High`, repair every feasible shared-C mismatch, and repeat ROM/native evidence until every scoped node and relation is exact. |
| Non-goals | No historical-node credit, no platform rendering/input decisions, and no expansion into S6 low question-row/bridge handlers. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 326 exact and 1,666 needs-evidence nodes; 708 exact feasible controls. Scope: 22 labels; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`; focused parser recorder/tests only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: castle exit, pipe geometry/warp, enemy-slot allocation, water-hole and high question-row branches/tables/state. Operational: controlled original-ROM/x86/x64 routes, focused parser tests, DOS16 build if product source changes, and platform-purity audit. |
| Expected Markers | Castle exit state, pipe metatiles, allocated enemy slot, water-hole state and question-row staging remain in shared C. |
| Asset Needs | Refresh all three artifacts only if product source changes. |
| Reporting Requirements | Report all 22 labels and every scoped feasible relation with separate static and operational results; repair and re-audit before S6. |
| Stop Conditions | A feasible ROM/C difference remains after repair, a relation lacks a shared-C counterpart, or platform code makes an area-parser decision. |
| Exit Criteria | Every scoped node and feasible relation is exact under source and controlled-route evidence; no successor is admitted while a mismatch remains. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Castle-stop edge ordering, pipe selector/height carries, side-shaft rows, full enemy pool behavior, hole/water state and question-row high nibble. |

## T56 S4 Closure

S4 closes 27 current-exact warp, scroll, frenzy, style, pulley and castle nodes, 63 scoped feasible control relations and two material relations. The original-ROM/current x86/x64 special-object and castle-geometry routes agree; x86/x64 are byte-identical. No product source changed. Historical conformance remains 1,992 / 1,992.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T56 S5 is active for the contiguous castle-finish, pipe, allocation and high question-row chain.
