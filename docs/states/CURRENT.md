# Project Status

## Current Work

## M2 T57 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S6 closure — enemy-area stream data and shared decode chain. |
| Admission And Approval | Owner-approved T57 source-order program; S6 completed under its approved packet. |
| Objective | Audit and repair if needed `E_CastleArea1 -> E_WaterArea3` against original-ROM bytes, terminators and shared stream-decoder semantics. |
| Non-goals | No S7 area-object-data work; no platform-specific game logic. |
| Reference Baseline | Historical 1,992 / 1,992. Incoming current registry: 431 exact / 1,561 needs-evidence; closure registry: 465 exact / 1,527 needs-evidence; 888 exact feasible controls. Scope: 34 labels; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Generated owner-local PRG data through `src/game/area/area_data.c`; shared decoder `src/game/enemy/stream.c`; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Static ROM-byte/terminator/pointer audit; 80 controlled original-ROM/current x86/x64 stream fixtures; focused x86/x64 tests, DOS16 shared-core link and platform-purity. |
| Expected Markers | Met: all 34 scoped labels and `material-00075` are current-equivalence exact. |
| Asset Needs | Audit/test-only work did not refresh target artifacts because no shared product source changed. |
| Reporting Requirements | Closure records all scoped labels, both verification tracks and before/after registry totals. |
| Stop Conditions | None remain: no feasible S6 mismatch was found. |
| Exit Criteria | Met: byte/data and shared-consumer paths are exact; evidence, ledger and documentation gates pass. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Stream pointer bounds, adjacent-label aliases, `$ff` terminators, 8-bit offset wrap, page commands, rows, group IDs, hard-mode suppression and fallback. |

## T57 S6 Closure

All 34 enemy-area stream labels and `material-00075` are exact. The static binding covers 1,087 bytes and all 34 pointer targets. Eighty original-ROM/current x86/x64 routes have zero persistent-state differences and byte-identical native records. No product source mismatch was found.

## T57 S5 Closure

S5 closed 16 world/area and stream-pointer table labels plus six material relations.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S6 is the sole active closure packet; S7 has not yet been admitted.
