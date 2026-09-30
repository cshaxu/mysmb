# Project Status

## Current Work

## M2 T51 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T51 S1 — implementation, residual source-order continuation |
| Admission And Approval | Continuing owner-approved M2 completion mandate; transfer `transfer-279-to-t51-s1` accepted. |
| Objective | Closed: certify `NonMaskableInterrupt` against the complete original NMI call and state sequence. |
| Non-goals | No host timing, renderer, input, or DOS-specific game-logic change. |
| Reference Baseline | 1,952 / 1,992 at admission; 1,953 / 1,992 at closure. |
| Candidate Proposal | `docs/proposals/m2/t51-residual-equivalence-and-certification.md` S1. |
| Files And ABI Surface | Shared owner `src/game/frame_root.c`; recorder/checker additions only if the source audit exposes a gap. |
| Applicable Rules | Execution, architecture, coding and source/research policy. |
| Verification | ROM-logic: controlled original NMI boundary and source call/branch/write order; operational: focused NMI checks, x86/x64 build, OpenNT DOS16 link, purity and three artifacts. |
| Expected Markers | `NonMaskableInterrupt`; one actual match; 1,953 / 1,992. |
| Asset Needs | Owner-local SMB1 ROM and local reference recorder only; all raw artifacts remain under ignored build. |
| Reporting Requirements | Record source route, child coverage, canonical stack exclusion, tests, artifact hashes and exact node disposition. |
| Stop Conditions | Stop only on a shared-C/ROM semantic discrepancy or an unaccepted scope transfer. |
| Exit Criteria | Met: parent order/output boundary, both verification tracks and all three artifacts are recorded in the S1 closure. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; DOS16 remains active through OpenNT, without DOSBox. |
| Similar-Issue Sweep | Inspect all shared NMI entry/commit calls for platform leakage and duplicated host-side state decisions. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 remains active: every M2 P uses the existing OpenNT toolchain to compile
and link the same shared C core, then refreshes `mysmb16.exe` alongside the
Win32 artifacts. DOSBox is not part of this workflow.