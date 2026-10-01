# Project Status

## Current Work

## M2 T57 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S7 audit — area-object stream data and shared decoder chain. |
| Admission And Approval | Owner-approved T57 source-order program; S6 closed with complete dual-track evidence. |
| Objective | Audit and repair if needed `L_CastleArea1 -> L_WaterArea3` against original-ROM stream bytes, terminators and shared area-decoder semantics. |
| Non-goals | No new object-family scope or platform-specific game logic. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 465 exact and 1,527 needs-evidence nodes; 888 exact feasible controls. Scope: 34 labels, all needs-evidence; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Generated owner-local PRG through `src/game/area/area_data.c`; shared decoder `src/game/area.c`; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Static ROM-byte/span/terminator audit and controlled original-ROM/current x86/x64 parser routes; focused tests, DOS16 shared-core link and platform-purity. |
| Expected Markers | All 34 scoped labels current-equivalence exact; accepted `material-00076` rechecked without duplicate credit. |
| Asset Needs | Refresh all three artifacts only if shared product source changes. |
| Reporting Requirements | Report each scoped label, both tracks, repairs and registry before/after totals. |
| Stop Conditions | A feasible mismatch remains in S7 until repaired and re-audited. |
| Exit Criteria | Every scoped data/decoder path exact and all gates pass. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Header offsets, adjacent labels, `$fd` termination, two/three-byte records, object length, loop commands, source offset wrap and terminal slots. |

## Exact S7 labels

`L_CastleArea1` through `L_CastleArea6`, `L_GroundArea1` through `L_GroundArea22`, `L_UndergroundArea1` through `L_UndergroundArea3`, and `L_WaterArea1` through `L_WaterArea3`.

## T57 S6 Closure

All 34 enemy-area stream labels and `material-00075` are exact.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S7 is the sole active packet.
