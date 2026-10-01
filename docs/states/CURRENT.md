# Project Status

## Current Work

## M2 T57 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S4 closure — area-pointer/type/attribute current-equivalence chain. |
| Admission And Approval | T57 S3 closed with complete dual-track evidence; the owner-approved source-order program admitted S4. |
| Objective | Audit and repair if needed `AreaDataOfsLoopback -> StoreStyle` against original-ROM control/data/state semantics. |
| Non-goals | No S5 world/area-table work was performed; no platform-specific game logic was introduced. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 415 exact and 1,577 needs-evidence nodes; 888 exact feasible controls. Scope: seven labels; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Shared `src/game/enemy/loop.c` loopback-table owner and `src/game/area/area_data.c` pointer/header owner; `src/game/area.c` is the downstream offset consumer and platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM logic compares loopback-table consumption, pointer lookup, area type and fore/style branches and state; controlled original-ROM/current x86/x64 loopback plus pointer/attribute matrices, focused smokes, DOS16 link and platform-purity. |
| Expected Markers | All seven scoped nodes and feasible incident relations are exact; the loopback material relation is exact. |
| Asset Needs | Audit/test-only work did not refresh artifacts because no product source changed. |
| Reporting Requirements | Closure records all seven labels, the ownership correction, both verification tracks and before/after registry totals. |
| Stop Conditions | None remain: no feasible S4 mismatch was found. |
| Exit Criteria | Met: scoped nodes/relations are exact and evidence/ledger gates passed. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Area-data pointer carry/page translation, world/area lookup bounds, type masking, foreground/style attribute gating and parser-loop continuation. |

## T57 S3 Closure

S3 closes all 16 labels and 29 newly evidenced incident control relations. The original-ROM/current x86/x64 matrix covered 98 hole/UnderPart, 20 helper and 48 block-address routes with zero persistent RAM differences and byte-identical native outputs. Focused smokes passed on both widths. No product source changed; the prior artifact set remains current. Historical conformance remains 1,992 / 1,992.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S4 is the sole active closure packet; S5 has not yet been admitted.
