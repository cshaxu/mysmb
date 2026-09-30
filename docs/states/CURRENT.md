# Project Status

## Current Work

## M2 T51 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T51 S3 — implementation, KillEnemies shared primitive |
| Admission And Approval | Continuing owner-approved M2 completion mandate; `transfer-281-to-t51-s3` accepted from M2 T29 S8. |
| Objective | Closed: reproduce source `$9716 KillEnemies` in its shared C owner, including its scratch-RAM contract and five-slot scan. |
| Non-goals | No platform rendering, timing, input, or DOS-specific game-logic change. |
| Reference Baseline | 1,957 / 1,992 at admission; 1,958 / 1,992 at closure. |
| Candidate Proposal | `docs/proposals/m2/t51-residual-equivalence-and-certification.md` S3. |
| Files And ABI Surface | Shared owner `src/game/area.c`, declaration `src/game/area.h`, and a focused shared test. |
| Applicable Rules | Execution, architecture, coding and source/research policy. |
| Verification | ROM-logic: `$00` entry store, zero load, X=4..0 loop and conditional Enemy_Flag stores; operational: focused x86/x64 tests, OpenNT DOS16 link, purity and three artifacts. |
| Expected Markers | `KillEnemies`; one actual match; 1,958 / 1,992. |
| Asset Needs | Owner-local SMB1 ROM and local reference source only; raw artifacts remain under ignored build. |
| Reporting Requirements | Record both callers, every scanned slot, artifact hashes and exact node disposition. |
| Stop Conditions | Stop only on a shared-C/ROM semantic discrepancy or an unaccepted scope transfer. |
| Exit Criteria | Met: entry scratch store, inclusive five-slot loop and selective flag clear agree with ROM; both verification tracks and all three artifacts are recorded. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; DOS16 remains active through OpenNT, without DOSBox. |
| Similar-Issue Sweep | Inspect other shared scratch-RAM C primitives for omitted entry-register stores. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 remains active: every M2 P uses the existing OpenNT toolchain to compile
and link the same shared C core, then refreshes `mysmb16.exe` alongside the
Win32 artifacts. DOSBox is not part of this workflow.