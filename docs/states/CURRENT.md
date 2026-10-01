# Project Status

## Current Work

## M2 T57 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S7 closure — area-object stream data and shared decoder chain. |
| Admission And Approval | Owner-approved T57 source-order program; S7 completed under its approved packet. |
| Objective | Audit and repair if needed `L_CastleArea1 -> L_WaterArea3` against original-ROM stream bytes, terminators and shared area-decoder semantics. |
| Non-goals | No new object-family scope or platform-specific game logic. |
| Reference Baseline | Historical 1,992 / 1,992. Incoming current registry: 465 exact / 1,527 needs-evidence; closure registry: 499 exact / 1,493 needs-evidence; 888 exact feasible controls. Scope: 34 labels; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Generated owner-local PRG through `src/game/area/area_data.c`; shared decoder `src/game/area.c`; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Static ROM byte/span/terminator audit; 36 controlled original-ROM/current x86/x64 parser routes; focused tests, DOS16 shared-core link and platform-purity. |
| Expected Markers | Met: all 34 scoped labels are current-equivalence exact. |
| Asset Needs | Audit-only work did not refresh artifacts because no shared product source changed. |
| Reporting Requirements | Closure records all scoped labels, both tracks and before/after registry totals. |
| Stop Conditions | None remain: no feasible S7 mismatch was found. |
| Exit Criteria | Met: every scoped data/decoder path exact and all gates pass. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Header offsets, adjacent labels, `$fd` termination, two/three-byte records, object length, loop commands, source offset wrap and terminal slots. |

## T57 S7 Closure

All 34 area-object stream labels are exact. The static binding covers 3,372 bytes; 36 original-ROM/current x86/x64 scene routes cover 3,955 samples with zero state or visible-output differences. No product source mismatch was found.

## T57 S6 Closure

All 34 enemy-area stream labels and `material-00075` are exact.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S7 is the sole active closure packet; T57 is ready for its cross-chain closure audit.
