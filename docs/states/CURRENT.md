# Project Status

## Current Work

**M2 T8 S1 is active.**

## Current Technical Baseline

- `mysmb_game` is a C90 native title foundation with translated reset, OAM,
  name-table, title-command, area, player, and object routes. `mysmb_win32`
  builds x86 and x64 PE windows around that core; `mysmb_dos16_core` is its
  host-free DOS compiler input and has passed a local OpenNT large-model
  compile. Owner-local title data and CHR are generated only into ignored
  output. `nnes` is a validation-only local reference and is never linked into
  MySMB.

## M2 T8 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T8 S1, New. |
| Admission And Approval | Owner directed continuous M2 execution with automatic audit, repair, and next-task admission. |
| Objective | Run a bounded native title-to-play route through the Win32 composition root and compare named C90 checkpoints against the owner-local original reference. |
| Non-goals | DOS graphics/sound, host audio playback, a CPU/PPU/APU emulator, and unbounded ROM tracing are outside this S. |
| Reference Baseline | M2 T1 full PRG analysis; T2 title oracle; T3-T7 translated native state routes; existing Win32 owner-local title composition. |
| Candidate Proposal | [M2 Native Logic And Oracle](../proposals/m2-native-logic-and-oracle.md), candidate 8. |
| Files And ABI Surface | Portable C90 deterministic route/checkpoint support, focused project-owned tests, Win32 composition changes, local-only validation tooling, and M2 history evidence. |
| Applicable Rules | Architecture, coding, execution, and source-policy authorities named by the Task Reading Set. |
| Verification | ROM-free unit tests; x86/x64 Win32 build; OpenNT large-model core compile when locally available; bounded owner-local reference comparison with neutral checkpoint summary; documentation gate and diff check. |
| Expected Markers | Explicit fixed input/frame script; native and reference checkpoint table; title-to-game mode transfer; Win32 route exercising the same core. |
| Asset Needs | Owner-local admitted ROM and optional reconciled listing/reference runner are research/validation input only. Generated data, traces, and embedded binaries remain ignored. |
| Reporting Requirements | Record address ranges, input script, checkpoints, reference disposition, source containment, any presentation boundary, and any unresolved semantic branch in history before closure. |
| Stop Conditions | Stop and revise scope if a route needs an emulator in the product, a protected artifact would enter Git, the measured ROM/listing mapping is contradicted, or a state difference cannot be bounded. |
| Exit Criteria | Reviewed native Win32 path traverses the bounded route with deterministic C90 checkpoints and every reference difference is explained. |
| Original Owner Request | M2 must run the game in Win32 and every translated code path must have validation. |
| Similar-Issue Sweep | Before closure, search the composition root and portable game layer for a bypass around `mysmb_game_tick`, host-only gameplay state, unbounded reference output, and stale checkpoint provenance; record every production hit and disposition. |

## Recent M2 Closures

| Task | Compact result |
| --- | --- |
| T1 | Full direct-ROM PRG analysis, revision reconciliation, and source-address architecture record completed with zero unresolved PRG bytes. [History](../history/M2-T1-prg-static-analysis.md). |
| T2 | Title input/start C90 route and bounded owner-local transition checkpoint closed; A+Start mirror audit repaired. [History](../history/M2-T2-title-start-checkpoint.md). |
| T3 | Area bootstrap, actual area-pointer/header parsing, object stream classification, and native command queue closed. [History](../history/M2-T3-area-bootstrap-and-commands.md). |
| T4 | Player physics, terrain collision, entrances, scrolling, and bounded owner-local checkpoint closed. [History](../history/M2-T4-player-route-and-collision.md). |
| T5 | Blocks, items, enemies, projectiles, score/timer/power, firebars, Bowser, and platform routes closed. [History](../history/M2-T5-object-routes.md). |
| T6 | Death, restart, two-player exchange, Warp Zone, and completion modes closed. [History](../history/M2-T6-mode-routes.md). |
| T7 | Original audio queues, priorities, buffers, and neutral command state closed. [History](../history/M2-T7-audio-command-routes.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
