# Project Status

## Current Work

## M2 T57 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S2 audit - staircase, jumpspring and question/brick current-equivalence chain. |
| Admission And Approval | T57 S1 closed after its shared-C repair and repeated dual-track proof; the owner-approved source-order program admits S2. |
| Objective | Audit and, if necessary, repair `StaircaseHeightData -> ExitDecBlock` against original-ROM control/data/state semantics. |
| Non-goals | No S3 hole/block-buffer work, no platform-specific game logic and no advance while a feasible S2 difference remains. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 379 exact and 1,613 needs-evidence nodes; 815 exact feasible controls. Scope: 13 labels; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic comparison of stair/spring/block tables, branch predicates, RAM reads/writes and tail order; controlled original-ROM/current x86/x64 matrix plus focused smokes and platform-purity. |
| Expected Markers | Every scoped node and feasible edge is recorded exact, mismatch, or retained with an explicit reason; a repair repeats both tracks. |
| Asset Needs | Audit-only work does not refresh artifacts. Any product-source repair rebuilds and validates all three target executables. |
| Reporting Requirements | Report all 13 labels, actual current-exact count, every mismatch/repair, both verification tracks and before/after registry totals at S closure. |
| Stop Conditions | A feasible mismatch remains in S2 until shared-C repair and repeat audit; do not admit S3 before closure. |
| Exit Criteria | All 13 labels and scoped feasible relations are current-exact, evidence/ledger are validated, and no S2 mismatch remains. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Staircase decrement/index order, jumpspring allocation/coordinates and every question/brick selector sharing DrawQBlk. |

## T57 S1 Closure

S1 closes 26 current-exact labels and 61 incident control relations. P1 restored `FlagpoleObject` shaft rendering through shared `RenderUnderPart`, preserving ROM overlay priority and object-height state. The controlled original-ROM/current x86/x64 routes match; focused tests, DOS16 link and platform-purity pass; all three artifacts were rebuilt. Historical conformance remains 1,992 / 1,992.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S2 is the sole active packet.
