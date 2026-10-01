# Project Status

## Current Work

## M2 T57 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S6 audit — enemy-area stream data and shared decode chain. |
| Admission And Approval | Owner-approved T57 source-order program; S5 closed with complete dual-track evidence. |
| Objective | Audit and repair if needed `E_CastleArea1 -> E_WaterArea3` against original-ROM bytes, terminators and shared stream-decoder semantics. |
| Non-goals | No S7 area-object-data work; no platform-specific game logic. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 431 exact and 1,561 needs-evidence nodes; 888 exact feasible controls. Scope: 34 labels, all currently needs-evidence; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Generated owner-local PRG data through `src/game/area/area_data.c`; shared decoder `src/game/enemy/stream.c`; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM logic compares bounded bytes, `$ff` terminators, record/page/row/group/fallback paths and state writes; controlled original-ROM/current x86/x64 stream fixtures. Operational verification runs focused x86/x64 tests, DOS16 shared-core link and platform-purity. |
| Expected Markers | All 34 scoped labels and `material-00075` are current-equivalence exact. |
| Asset Needs | Refresh `assets/mysmb16.exe`, `assets/mysmb32.exe`, `assets/mysmb64.exe` only if shared product source changes. |
| Reporting Requirements | Report each scoped label's disposition, both verification tracks, any repair/re-audit, and registry counts before/after. |
| Stop Conditions | A feasible mismatch remains in this S until repaired and re-audited. |
| Exit Criteria | All scoped byte/data and shared-consumer paths exact; evidence, ledger and documentation gates pass. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Stream pointer bounds, adjacent-label aliases, `$ff` terminators, 8-bit offset wrap, page commands, rows, group IDs, hard-mode suppression and fallback. |

## Exact S6 labels

`E_CastleArea1`, `E_CastleArea2`, `E_CastleArea3`, `E_CastleArea4`, `E_CastleArea5`, `E_CastleArea6`, `E_GroundArea1` through `E_GroundArea22`, `E_UndergroundArea1` through `E_UndergroundArea3`, and `E_WaterArea1` through `E_WaterArea3`.

## T57 S5 Closure

S5 closed 16 world/area and stream-pointer table labels plus six material relations. The current registry was 431 exact nodes and 888 exact feasible controls; no product source changed.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S6 is the sole active packet.
