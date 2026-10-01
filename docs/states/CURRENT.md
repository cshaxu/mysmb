# Project Status

## Current Work

## M2 T57 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S7 closure — Cohort D renderer, metatile, block-buffer, pointer and stream chains. |
| Admission And Approval | Owner-approved T57 source-order program; S1–S7 are closed and T-level cross-chain review completed. |
| Objective | Close the seven audited chains only after their rendering, address-selection and stream-consumer joins pass original-ROM/current native regression. |
| Non-goals | No new Cohort-E scope or platform-specific game logic. |
| Reference Baseline | Historical 1,992 / 1,992. Incoming current registry: 353 exact / 1,639 needs-evidence; closure registry: 499 exact / 1,493 needs-evidence; 888 exact feasible controls. Scope: 146 labels; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Shared `src/game` area, stream and OAM owners; `test/verify_area_chain_regression.py` now confines pointer fixtures to their actual persistent-RAM oracle; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | 107 original-ROM/current routes per width: 36 scene routes with full visible output and 71 pointer routes with persistent RAM; focused x86/x64 tests, DOS16 shared-core link, cross-width byte comparison and platform-purity. |
| Expected Markers | Met: all 146 scoped labels, their feasible in-scope relations and the S-chain handoffs are current-equivalence exact. |
| Asset Needs | Test-only correction; no shared product source changed, so the existing three artifacts remain the release package. |
| Reporting Requirements | Closure records the seven chains, dual tracks, cross-chain results and before/after registry totals. |
| Stop Conditions | None remain: the only initial regression was an overclaimed pointer-fixture output comparison, corrected and re-run. |
| Exit Criteria | Met: all seven chains and their joins have no unresolved feasible difference. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Object overlays, length/row guards, block-buffer selectors, pointer/header tables, stream terminators, scene output, pointer fixture ABI exclusions and x86/x64 output identity. |

## T57 Closure

All 146 Cohort-D labels are exact. The final matrix covers 36 original-ROM/current scene routes (4,772 samples and 3,372 consumed scene bytes) plus 71 pointer/terminal routes (141 samples) per width. Scene routes compare persistent state and all visible output; pointer routes compare their source-reachable persistent RAM contract. All 107 x86 and x64 native records are byte-identical. Focused object/parser/stream tests, platform purity and a shared DOS16 link pass. No product source mismatch was found.

## T57 S6 Closure

All 34 enemy-area stream labels and `material-00075` are exact.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 is closed; T58 has not been admitted.
