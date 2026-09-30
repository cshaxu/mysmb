# Project Status

## Current Work

## M2 T51 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T51 S2 — implementation, screen/parser output chain |
| Admission And Approval | Continuing owner-approved M2 completion mandate; transfer `transfer-280-to-t51-s2` accepted. |
| Objective | Closed: certify the source-contiguous `ScreenRoutines -> AreaParserTaskControl -> TaskLoop -> OutputCol` chain. |
| Non-goals | No platform rendering, timing, input, or DOS-specific game-logic change. |
| Reference Baseline | 1,953 / 1,992 at admission; 1,957 / 1,992 at closure. |
| Candidate Proposal | `docs/proposals/m2/t51-residual-equivalence-and-certification.md` S2. |
| Files And ABI Surface | Shared owners `src/game/game.c` and `src/game/area.c`; tests only if the source audit exposes a gap. |
| Applicable Rules | Execution, architecture, coding and source/research policy. |
| Verification | ROM-logic: dispatch selector, parser loop, decrement/branch and selector-six write; operational: parser/NMI checks, x86/x64 build, OpenNT DOS16 link, purity and three artifacts. |
| Expected Markers | `ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol`; four actual matches; 1,957 / 1,992. |
| Asset Needs | Owner-local SMB1 ROM and local reference recorder only; all raw artifacts remain under ignored build. |
| Reporting Requirements | Record source route, loop/underflow branches, tests, artifact hashes and exact node disposition. |
| Stop Conditions | Stop only on a shared-C/ROM semantic discrepancy or an unaccepted scope transfer. |
| Exit Criteria | Met: ROM dispatch/loop/output behavior, both verification tracks and all three artifacts are recorded in the S2 closure. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; DOS16 remains active through OpenNT, without DOSBox. |
| Similar-Issue Sweep | Inspect every screen-routine task path for host-side parser or VRAM-selector interpretation. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 remains active: every M2 P uses the existing OpenNT toolchain to compile
and link the same shared C core, then refreshes `mysmb16.exe` alongside the
Win32 artifacts. DOSBox is not part of this workflow.