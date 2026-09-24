# Project Status

## Current Work

**M3 T8 S1 is active.**

## Current Technical Baseline

- `mysmb_game` is a C90 native title foundation with translated reset, OAM,
  name-table, title-command, area, player, and object routes. `mysmb_win32`
  builds x86 and x64 PE windows around that core; `mysmb_dos16_core` is its
  host-free DOS compiler input and has passed a local OpenNT large-model
  compile. Owner-local title data and CHR are generated only into ignored
  output. `nnes` is a validation-only local reference and is never linked into
  MySMB.

## M3 T8 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T8 S1, New. |
| Admission And Approval | Owner directed continuous M2 execution with automatic audit, repair, and next-task admission. |
| Objective | Establish a repeatable DOS runtime verification path for the linked MZ and measure its first frame-pacing and memory-layout evidence. |
| Non-goals | Sound, a CPU/PPU/APU emulator, ROM-derived presentation assets, 486SX final qualification, and changes to validated gameplay logic are outside this S. |
| Reference Baseline | M3 T7 linked BIOS/VGA/text hardware path. |
| Candidate Proposal | [M3 Presentation Adapters](../proposals/m3-presentation-adapters.md), DOS runtime verification continuation. |
| Files And ABI Surface | Local DOS runtime wrapper or host evidence, bounded execution evidence, and M3 history evidence. |
| Applicable Rules | Architecture, coding, execution, and source-policy authorities named by the Task Reading Set. |
| Verification | ROM-free unit tests; x86/x64 Win32 build; OpenNT large-model core compile when locally available; documentation gate and diff check. |
| Expected Markers | A bounded local execution route, process outcome evidence, MZ structural checks, and measured pacing/memory observations. |
| Asset Needs | No protected asset is required; owner-local inputs remain outside tracked output. |
| Reporting Requirements | Record runtime provenance, bounded-run command, outcome, graphical-host limits, and deferred 486SX qualification before closure. |
| Stop Conditions | Stop and revise scope if runtime verification requires unreviewed guest media, emulator coupling into product code, gameplay changes, or protected data. |
| Exit Criteria | A bounded local DOS execution path produces reproducible structural/runtime evidence, or the exact host capability gap is demonstrated. |
| Original Owner Request | Deliver a native C SMB1 suitable for future colored text and DOS presentation without contaminating the core. |
| Similar-Issue Sweep | Before closure, search for unbounded DOS runs, unreviewed guest media, tracked binaries, local-path leakage in records, and product/runtime coupling; record every production hit and disposition. |

## Recent M3 Closures

| Task | Compact result |
| --- | --- |
| T1 | Neutral tile-row and actor commands are generated read-only from the native C state; a bounded Win32 consumer and C90/OpenNT verification are in place. [History](../history/M3-T1-neutral-render-command-seam.md). |
| T2 | Win32 consumes every neutral tile-row and actor command with a deterministic host palette, without a second gameplay path. [History](../history/M3-T2-win32-command-consumer.md). |
| T3 | A neutral render frame now yields a deterministic 80x25 character/color frame with full background fill and object glyph/color overlays. [History](../history/M3-T3-colored-text-frame.md). |
| T4 | A 320x200 indexed frame is generated from neutral commands using explicit 16-bit-safe pages and compiles under OpenNT. [History](../history/M3-T4-vga-indexed-frame.md). |
| T5 | The DOS16 root owns one native tick and both presentation-frame submissions through isolated hooks; its source compiles under OpenNT. [History](../history/M3-T5-dos16-composition-root.md). |
| T6 | A configured OpenNT large-model build links the actual DOS root and frame adapters into an ignored MZ executable. [History](../history/M3-T6-opennt-mz-link.md). |
| T7 | BIOS input/timing plus Mode 13h and colored-text hardware hooks are linked into the DOS root while remaining outside game code. [History](../history/M3-T7-dos-hardware-hooks.md). |

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
