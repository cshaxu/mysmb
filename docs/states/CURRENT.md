# Project Status

## Current Work

## M2 T52 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T52 S6 — H9 DrawLargePlatform Y-source remediation. |
| Admission And Approval | Owner-directed continuation of T52 after closed S5. |
| Objective | Bind DrawLargePlatform's first four OAM Y records to `Enemy_Y_Position + slot`. |
| Non-goals | No platform-owned OAM logic, no change to final-two-row, tile, attribute or offscreen branches, and no historical-credit increase. |
| Reference Baseline | 1,992 / 1,992 historical; one received historical-complete label, expected delta zero. |
| Candidate Proposal | docs/proposals/m2/t52-current-audit-mismatch-remediation.md. |
| Files And ABI Surface | Shared src/game/oam/small_platform_gfx.c; focused large-platform tests and owner-local route records. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Controlled ROM DrawLargePlatform route with distinct `$00cf+slot` and `$03b9`, plus castle, hard, cloud and offscreen controls; x86/x64/DOS16 and purity. |
| Expected Markers | The first four platform OAM Y bytes equal `Enemy_Y_Position + slot`, independent of relative Y; final two rows retain their existing source branches. |
| Asset Needs | Owner-local ROM and ignored local three-EXE outputs. |
| Reporting Requirements | DrawLargePlatform, both verification tracks and unchanged numerator. |
| Stop Conditions | Any Y-source change outside the first-four-row producer or platform-adapter change. |
| Exit Criteria | DrawLargePlatform is current-equivalence exact with all neighboring graphics branches preserved. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | All platform drawing functions that distinguish world and relative coordinates. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64. Platform adapters do not own game logic.
