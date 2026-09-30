# Project Status

## Current Work

## M2 T51 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T51 S4 — implementation, original enemy-stream data and consumer chain |
| Admission And Approval | Continuing owner-approved M2 completion mandate; `transfer-282-to-t51-s4` accepted from M2 T19 S5. |
| Objective | Prove the exact 34 original enemy streams are selected and consumed by shared native C with original data semantics. |
| Non-goals | No platform rendering, input, timing, DOS-specific game logic, or invented actor behavior. |
| Reference Baseline | 1,958 / 1,992 at admission; 34 labels in scope and 34 expected matches; maximum 1,992 / 1,992. |
| Candidate Proposal | `docs/proposals/m2/t51-residual-equivalence-and-certification.md` S4. |
| Files And ABI Surface | Shared owner `src/game/enemy/stream.c`; source pointer owner `src/game/area/area_data.c`; local-ROM test/audit only. |
| Applicable Rules | Execution, architecture, coding, documentation and source/research policy. |
| Verification | ROM-logic: literal ROM/ASM binding, pointer tables, framing, terminators and source consumer read/cursor sequence; operational: focused local-ROM test and audit on x86/x64, OpenNT DOS16 link, purity and three artifacts. |
| Expected Markers | `E_CastleArea1` through `E_WaterArea3`; 34 exact labels; `E_GroundArea9`/`E_GroundArea10` alias; 1,992 / 1,992. |
| Asset Needs | Owner-local SMB1 ROM and local reference source only; generated data, traces and logs remain under ignored build. |
| Reporting Requirements | Record all 34 label dispositions, family pointer selection, alias and terminator cases, artifact hashes and shared-owner boundary. |
| Stop Conditions | Stop only on a ROM/shared-C semantic discrepancy or a failed ownership transfer. |
| Exit Criteria | Every target label has both exact data-binding and actual shared-consumer proof; all three artifacts are rebuilt from the same game layer. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; DOS16 stays active via OpenNT, without DOSBox. |
| Similar-Issue Sweep | Inspect every existing E-stream auditor and consumer test for a binding-only assertion that omits runtime consumption. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 remains active: every M2 P uses the existing OpenNT toolchain to compile
and link the same shared C core, then refreshes `mysmb16.exe` alongside the
Win32 artifacts. DOSBox is not part of this workflow.
