# Project Status

## Current Work

## M2 T57 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S1 audit - flagpole, object-row and cannon current-equivalence chain. |
| Admission And Approval | Owner-approved source-order continuation after closed T56; ledger registration and admission validation are required before investigation. |
| Objective | Audit and, if necessary, repair the 26-label `FlagpoleObject -> StrCOffset` shared-game chain against the original-ROM graph and controlled route. |
| Non-goals | No unscoped Cohort D promotion, no platform-specific game logic and no advance to S2 with an unresolved feasible S1 difference. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 353 exact and 1,639 needs-evidence nodes; 767 exact feasible controls. Scope: 26 labels; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`, with existing shared flagpole OAM consumer `src/game/oam/flagpole_gfx.c`; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic comparison of branch/table/read/write/call order plus original-ROM/current x86/x64 controlled object-family matrix; focused object smokes and platform-purity audit. |
| Expected Markers | Every scoped node and feasible edge is recorded exact, mismatch, or retained with an explicit reason; a repair repeats both tracks. |
| Asset Needs | Audit-only work does not refresh artifacts. Any product-source repair rebuilds and validates all three target executables. |
| Reporting Requirements | Report all 26 labels, actual current-exact count, every mismatch/repair, both verification tracks and before/after registry totals at S closure. |
| Stop Conditions | A feasible mismatch remains in S1 until shared-C repair and repeat audit; do not admit S2 before closure. |
| Exit Criteria | All 26 labels and scoped feasible relations are current-exact, evidence/ledger are validated, and no S1 mismatch remains. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Audit all adjacent object-row, rope, bridge and cannon table/loop variants owned by this chain. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S1 is the sole active packet.
