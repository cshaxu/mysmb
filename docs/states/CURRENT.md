# Project Status

## Current Work

**M3 T5 S1 is active.**

## Current Technical Baseline

- `mysmb_game` is a C90 native title foundation with translated reset, OAM,
  name-table, title-command, area, player, and object routes. `mysmb_win32`
  builds x86 and x64 PE windows around that core; `mysmb_dos16_core` is its
  host-free DOS compiler input and has passed a local OpenNT large-model
  compile. Owner-local title data and CHR are generated only into ignored
  output. `nnes` is a validation-only local reference and is never linked into
  MySMB.

## M3 T5 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T5 S1, New. |
| Admission And Approval | Owner directed continuous M2 execution with automatic audit, repair, and next-task admission. |
| Objective | Create a minimal real-mode DOS composition root that drives the existing native game, neutral VGA frame, and colored text frame through isolated hardware hooks. |
| Non-goals | Sound, a CPU/PPU/APU emulator, ROM-derived presentation assets, 486SX hardware qualification, and changes to validated gameplay logic are outside this S. |
| Reference Baseline | M3 neutral render, text, and VGA frames. |
| Candidate Proposal | [M3 Presentation Adapters](../proposals/m3-presentation-adapters.md), DOS composition continuation. |
| Files And ABI Surface | DOS16 composition root, hardware hook contract, OpenNT link evidence, and M3 history evidence. |
| Applicable Rules | Architecture, coding, execution, and source-policy authorities named by the Task Reading Set. |
| Verification | ROM-free unit tests; x86/x64 Win32 build; OpenNT large-model core compile when locally available; documentation gate and diff check. |
| Expected Markers | An isolated DOS platform root, BIOS keyboard/timer and VGA writer hooks outside the game core, and an OpenNT-linked MZ executable when local tools permit. |
| Asset Needs | No protected asset is required; owner-local inputs remain outside tracked output. |
| Reporting Requirements | Record DOS memory/hardware ownership, input/timing policy, link result, source containment, and deferred sound/qualification work before closure. |
| Stop Conditions | Stop and revise scope if the adapter requires an emulator, changes gameplay behavior, embeds protected data, or introduces a host-specific game-state path. |
| Exit Criteria | The project has a 16-bit DOS composition root whose portable and hardware boundaries are documented and whose local OpenNT executable link succeeds when the toolchain supports it. |
| Original Owner Request | Deliver a native C SMB1 suitable for future colored text and DOS presentation without contaminating the core. |
| Similar-Issue Sweep | Before closure, search for DOS API leakage into the game layer, platform-owned game mutation, duplicate scheduler/input paths, host-specific state, and protected asset leakage; record every production hit and disposition. |

## Recent M3 Closures

| Task | Compact result |
| --- | --- |
| T1 | Neutral tile-row and actor commands are generated read-only from the native C state; a bounded Win32 consumer and C90/OpenNT verification are in place. [History](../history/M3-T1-neutral-render-command-seam.md). |
| T2 | Win32 consumes every neutral tile-row and actor command with a deterministic host palette, without a second gameplay path. [History](../history/M3-T2-win32-command-consumer.md). |
| T3 | A neutral render frame now yields a deterministic 80x25 character/color frame with full background fill and object glyph/color overlays. [History](../history/M3-T3-colored-text-frame.md). |
| T4 | A 320x200 indexed frame is generated from neutral commands using explicit 16-bit-safe pages and compiles under OpenNT. [History](../history/M3-T4-vga-indexed-frame.md). |

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
