# Project Status

## Current Work

## M2 T57 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T57 S5 closure — world/area and stream-pointer table current-equivalence chain. |
| Admission And Approval | T57 S4 closed with complete dual-track evidence; the owner-approved source-order program admitted S5. |
| Objective | Audit and repair if needed `WorldAddrOffsets -> AreaDataAddrHigh` against original-ROM table bytes, indexed selection and pointer-pair semantics. |
| Non-goals | No S6 enemy-stream body work was performed; no platform-specific game logic was introduced. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 431 exact and 1,561 needs-evidence nodes; 888 exact feasible controls. Scope: sixteen labels; expected historical delta: zero. |
| Candidate Proposal | docs/proposals/m2/t57-cohort-d-renderer-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area/area_data.c` table consumer; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM logic compares each table byte, truncated index, pointer low/high pair and consumer handoff; controlled original-ROM/current x86/x64 table matrix plus focused smoke, DOS16 link and platform-purity. |
| Expected Markers | All sixteen scoped nodes and six material relations are exact. |
| Asset Needs | Audit-only work did not refresh artifacts because no product source changed. |
| Reporting Requirements | Closure records all sixteen labels, all table material relations, both verification tracks and before/after registry totals. |
| Stop Conditions | None remain: no feasible S5 mismatch was found. |
| Exit Criteria | Met: scoped nodes/material relations are exact and evidence/ledger gates passed. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Table-bank bounds, byte truncation, WorldNAreas aliases, type bases, paired pointer bytes and source-data ownership. |

## T57 S4 Closure

S4 closed seven labels and 17 newly evidenced feasible incident controls. `AreaDataOfsLoopback` is correctly owned by `src/game/enemy/loop.c`; 96 loop routes consumed all eleven bytes and 22 executed `ExecGameLoopback`. The companion 71-route pointer matrix consumed all 188 pointer/header bytes. Both original-ROM/current x86/x64 tracks had zero persistent RAM differences, focused smokes/platform-purity passed, and OpenNT linked DOS16. No product source changed. Current registry: 415 exact nodes and 888 exact feasible controls; historical conformance remains 1,992 / 1,992.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T57 S5 is the sole active closure packet; S6 has not yet been admitted.
