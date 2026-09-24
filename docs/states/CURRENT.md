# Project Status

## Current Work

**M3 T1 S1 is active.**

## Current Technical Baseline

- `mysmb_game` is a C90 native title foundation with translated reset, OAM,
  name-table, title-command, area, player, and object routes. `mysmb_win32`
  builds x86 and x64 PE windows around that core; `mysmb_dos16_core` is its
  host-free DOS compiler input and has passed a local OpenNT large-model
  compile. Owner-local title data and CHR are generated only into ignored
  output. `nnes` is a validation-only local reference and is never linked into
  MySMB.

## M3 T1 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T1 S1, New. |
| Admission And Approval | Owner directed continuous M2 execution with automatic audit, repair, and next-task admission. |
| Objective | Define and implement the first presentation-neutral render-command seam needed to replace the temporary Win32 gameplay placeholder and later drive the DOS VGA and 80x25 colored-object adapters. |
| Non-goals | DOS graphics/sound, a CPU/PPU/APU emulator, ROM-derived presentation assets, and changes to validated gameplay logic are outside this S. |
| Reference Baseline | Completed M2 native game/oracle route and its Win32 composition audit. |
| Candidate Proposal | [M3 Presentation Adapters](../proposals/m3-presentation-adapters.md), candidate 1. |
| Files And ABI Surface | Portable C90 neutral render commands, focused project-owned tests, and M3 history evidence. |
| Applicable Rules | Architecture, coding, execution, and source-policy authorities named by the Task Reading Set. |
| Verification | ROM-free unit tests; x86/x64 Win32 build; OpenNT large-model core compile when locally available; documentation gate and diff check. |
| Expected Markers | Game-owned command schema, deterministic command generation, no renderer-owned gameplay state, and a Win32 consumer boundary. |
| Asset Needs | No protected asset is required; owner-local inputs remain outside tracked output. |
| Reporting Requirements | Record command ownership, fixed-input checks, source containment, presentation boundary, and deferred DOS adapter work before closure. |
| Stop Conditions | Stop and revise scope if the seam requires an emulator, changes gameplay behavior, embeds protected data, or requires a host-specific state path. |
| Exit Criteria | The portable core emits deterministic neutral commands that a Win32 adapter can consume without changing gameplay state. |
| Original Owner Request | Deliver a native C SMB1 suitable for future colored text and DOS presentation without contaminating the core. |
| Similar-Issue Sweep | Before closure, search for renderer-owned game mutation, host-specific command state, duplicated frame logic, and protected asset leakage; record every production hit and disposition. |

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
| T8 | Bounded title-to-play oracle, Win32 composition audit, and two original frame-order repairs closed. [History](../history/M2-T8-end-to-end-oracle-and-win32-route.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
