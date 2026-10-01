# Project Status

## Current Work

## M2 T57 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S4 audit — area-pointer/type/attribute current-equivalence chain. |
| Admission And Approval | T57 S3 closed with complete dual-track evidence; the owner-approved source-order program admits S4. |
| Objective | Audit and repair if needed `AreaDataOfsLoopback -> StoreStyle` against original-ROM control/data/state semantics. |
| Non-goals | No S5 world/area-table work, no platform-specific game logic and no advance while a feasible S4 difference remains. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 408 exact and 1,584 needs-evidence nodes; 871 exact feasible controls. Scope: seven labels; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM logic compares loopback, pointer lookup, area type and fore/style branches and state; controlled original-ROM/current x86/x64 pointer/attribute matrix plus focused smokes and platform-purity. |
| Expected Markers | Every scoped node and feasible edge is recorded exact, mismatch, or retained with an explicit reason; a repair repeats both tracks. |
| Asset Needs | Audit-only work does not refresh artifacts. Any product-source repair rebuilds and validates all three target executables. |
| Reporting Requirements | Report all seven labels, actual current-exact count, every mismatch/repair, both verification tracks and before/after registry totals at S closure. |
| Stop Conditions | A feasible mismatch remains in S4 until shared-C repair and repeat audit; do not admit S5 before closure. |
| Exit Criteria | All seven labels and scoped feasible relations are current-exact, evidence/ledger are validated, and no S4 mismatch remains. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Area-data pointer carry/page translation, world/area lookup bounds, type masking, foreground/style attribute gating and parser-loop continuation. |

## T57 S3 Closure

S3 closes all 16 labels and 29 newly evidenced incident control relations. The original-ROM/current x86/x64 matrix covered 98 hole/UnderPart, 20 helper and 48 block-address routes with zero persistent RAM differences and byte-identical native outputs. Focused smokes passed on both widths. No product source changed; the prior artifact set remains current. Historical conformance remains 1,992 / 1,992.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S4 is the sole active packet.
