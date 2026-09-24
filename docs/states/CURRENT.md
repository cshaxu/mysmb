# Project Status

## Current Work

**M3 T3 S1 is active.**

## Current Technical Baseline

- `mysmb_game` is a C90 native title foundation with translated reset, OAM,
  name-table, title-command, area, player, and object routes. `mysmb_win32`
  builds x86 and x64 PE windows around that core; `mysmb_dos16_core` is its
  host-free DOS compiler input and has passed a local OpenNT large-model
  compile. Owner-local title data and CHR are generated only into ignored
  output. `nnes` is a validation-only local reference and is never linked into
  MySMB.

## M3 T3 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T3 S1, New. |
| Admission And Approval | Owner directed continuous M2 execution with automatic audit, repair, and next-task admission. |
| Objective | Define and implement the first 80x25 colored-object adapter over the neutral render commands, with a host-visible deterministic test harness while preserving the portable game core. |
| Non-goals | DOS graphics/sound, a CPU/PPU/APU emulator, ROM-derived presentation assets, a DOS executable, and changes to validated gameplay logic are outside this S. |
| Reference Baseline | M3 T1 neutral render-command seam and M3 T2 Win32 consumer. |
| Candidate Proposal | [M3 Presentation Adapters](../proposals/m3-presentation-adapters.md), candidate 3. |
| Files And ABI Surface | Portable text-frame adapter contract, project-owned deterministic tests, and M3 history evidence. |
| Applicable Rules | Architecture, coding, execution, and source-policy authorities named by the Task Reading Set. |
| Verification | ROM-free unit tests; x86/x64 Win32 build; OpenNT large-model core compile when locally available; documentation gate and diff check. |
| Expected Markers | An 80x25 character/color frame derived solely from neutral commands, object glyph mapping, background fill policy, and no console escape sequence in the game core. |
| Asset Needs | No protected asset is required; owner-local inputs remain outside tracked output. |
| Reporting Requirements | Record glyph/background policy, command-to-cell mapping, fixed-input checks, source containment, and deferred DOS VGA work before closure. |
| Stop Conditions | Stop and revise scope if the adapter requires an emulator, changes gameplay behavior, embeds protected data, or introduces a host-specific game-state path. |
| Exit Criteria | A deterministic 80x25 colored-object frame is built from neutral commands and is independently testable without a terminal host. |
| Original Owner Request | Deliver a native C SMB1 suitable for future colored text and DOS presentation without contaminating the core. |
| Similar-Issue Sweep | Before closure, search for gameplay-RAM reads in the text adapter, terminal sequence leakage into the core, command bypasses, host-owned game mutation, and protected asset leakage; record every production hit and disposition. |

## Recent M3 Closures

| Task | Compact result |
| --- | --- |
| T1 | Neutral tile-row and actor commands are generated read-only from the native C state; a bounded Win32 consumer and C90/OpenNT verification are in place. [History](../history/M3-T1-neutral-render-command-seam.md). |
| T2 | Win32 consumes every neutral tile-row and actor command with a deterministic host palette, without a second gameplay path. [History](../history/M3-T2-win32-command-consumer.md). |

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
