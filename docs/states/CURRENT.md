# Project Status

## Current Work

**M2 T3 S1 is active.**

## Current Technical Baseline

- `mysmb_game` is a C90 native title foundation with translated reset, OAM, name-table, and title-command routines. `mysmb_win32` builds x86 and x64 PE windows around that core; `mysmb_dos16_core` is its host-free DOS compiler input and has passed a local OpenNT large-model compile. Owner-local title data and CHR are generated only into ignored output. `nnes` is a validation-only local reference and is never linked into MySMB.

## M2 T3 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T3 S1, New. |
| Admission And Approval | Owner directed continuous M2 execution with automatic audit, repair, and next-task admission. |
| Objective | Translate the actual-ROM area bootstrap, pointer/header state, and first background/object command route entered after T2's title start boundary. |
| Non-goals | Player physics, object behavior, audio playback, DOS graphics, a CPU/PPU/APU emulator, and visual-only level replacement are outside this S. |
| Reference Baseline | M2 T1 architecture record; T2 start boundary at gameplay mode 1/task 0; actual ROM `$92b0`, `$9508`, `$9c03`, and gameplay root `$aedc`. |
| Candidate Proposal | [M2 Native Logic And Oracle](../proposals/m2-native-logic-and-oracle.md), candidate 3. |
| Files And ABI Surface | Portable `src/game` C90 area state and commands, focused project-owned tests, local-only validation tooling as needed, and M2 history/architecture evidence. |
| Applicable Rules | Architecture, coding, execution, and source-policy authorities named by the Task Reading Set. |
| Verification | ROM-free unit tests; x86/x64 Win32 build; OpenNT large-model core compile when locally available; bounded owner-local reference comparison with neutral checkpoint summary; documentation gate and diff check. |
| Expected Markers | Explicit actual-ROM address provenance; area pointer/header fields; page and name-table setup; deterministic command output; task-0 to task-1 checkpoint. |
| Asset Needs | Owner-local admitted ROM and optional reconciled listing are research/validation input only. Generated data, traces, and embedded binaries remain ignored. |
| Reporting Requirements | Record address ranges, area input assumptions, checkpoints, reference disposition, source containment, and any unresolved semantic branch in history before closure. |
| Stop Conditions | Stop and revise scope if a route needs an emulator, a protected artifact would enter Git, the measured ROM/listing mapping is contradicted, or a state difference cannot be bounded. |
| Exit Criteria | A reviewed C90 task-0 area bootstrap reaches its task-1 boundary with pointer/header state and neutral commands verified by bounded local reference evidence. |
| Original Owner Request | M2 must run the game in Win32 and every translated code path must have validation. |
| Similar-Issue Sweep | Before closure, search the portable game layer for host parsing, non-C90 widths, unproven area transitions, and stale listing-address provenance; record every production hit and disposition. |

## Recent M0 Closures

| Task | Compact result |
| --- | --- |
| T1 | M0 governance, source boundary, MTSP lifecycle, roadmap, and local documentation gate established at `3771fbc`; no ROM or third-party material admitted. [History](../history/M0-T1-governance-and-translation-plan.md). |

## Recent M1 Closures

| Task | Compact result |
| --- | --- |
| T2 | Shared C90 core, x64/x86 Win32 window builds, and DOS16 compiler input established at `62e2d22`; both core smoke tests pass. [History](../history/M1-T2-win32-platform-foundation.md). |
| T5 | Local title oracle closes M1. The checkpoint mismatch is bounded and deferred to M2 state-route translation. [History](../history/M1-T5-title-oracle.md). |

## Recent M2 Closures

| Task | Compact result |
| --- | --- |
| T1 | Full direct-ROM PRG analysis, revision reconciliation, and source-address architecture record completed with zero unresolved PRG bytes. [History](../history/M2-T1-prg-static-analysis.md). |
| T2 | Title input/start C90 route and bounded owner-local transition checkpoint closed; A+Start mirror audit repaired. [History](../history/M2-T2-title-start-checkpoint.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
