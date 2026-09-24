# Project Status

## Current Work

**M2 T11 S1 is active.**

## Current Technical Baseline

- `mysmb_game` is a C90 native logic foundation with translated title, area,
  player, object, mode, audio-command, and background-output routes. Its
  canonical snapshot now has translated name-table, attribute, palette,
  scroll, status, and PPU-state ownership. OAM producers and faithful Win32
  frame consumption remain absent, so M2 is still open. `mysmb_win32` builds
  x86 and x64 PE windows; owner-local title data and CHR are generated only
  into ignored output. `nnes` is validation-only and is never linked into
  MySMB.

## M2 T11 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T11 S1, New. |
| Admission And Approval | Owner reopened M2 and admitted the dependency-ordered recovery queue. T10 closed the translated background-output route and its bounded PPU evidence. |
| Objective | Translate the original OAM output route: sprite offsets, player, enemy, item, projectile, effect, score, platform, boss, priority, animation, offscreen initialization, and NMI OAM submission into the canonical native frame snapshot. |
| Non-goals | A generic NES CPU/PPU/APU emulator, host-owned sprites, visual approximation, bitmap-to-text conversion, protected tracked output, CHR decoding in the Win32 consumer, and any M2 closure claim are outside this S. |
| Reference Baseline | M2 T9 frame-output ledger and recorder contract, M2 T10 background closure, M2 T1 PRG ledger, and the reopened frame-equivalence proposal. |
| Candidate Proposal | [M2 Reopened Frame Equivalence](../proposals/m2-reopened-frame-equivalence.md). |
| Files And ABI Surface | Portable OAM backing state and writers, canonical frame-snapshot OAM fields, source-address mappings, owner-local OAM-reference inputs, and corrected M2 evidence. |
| Applicable Rules | Architecture, coding, execution, and source-policy authorities named by the Task Reading Set. |
| Verification | Owner-local OAM-route probes at the T9 NMI boundary; ROM-free tests; x86/x64 builds; OpenNT large-model compile; documentation gate; diff check. |
| Expected Markers | The snapshot carries source-ordered OAM bytes from named ROM writers, including offscreen and priority state; no host renderer invents sprite state. |
| Asset Needs | The owner-supplied SMB1 ROM and local reference remain non-redistributable, ignored inputs. Each reference trace uses one unique ignored output directory, is limited to 600 NMI-return samples and 2,637,012 bytes. Its exact sampler is bounded to 131,072 instruction steps per requested sample, equivalent to the former 512 driver calls of at most 256 instructions, then the task executor deletes the trace after a neutral summary. Generated data, ROM-bound executables, frame traces, and screenshots remain local and untracked. |
| Reporting Requirements | Record source ranges, input scripts, frame phase, snapshot fields, hashes where lawful, every difference, and whether it is translated, deferred, or rejected. |
| Stop Conditions | Stop and revise if the work substitutes host drawing for translated output, requires a runtime emulator, embeds protected data in tracked output, or cannot name a source owner for a visible result. |
| Exit Criteria | T11 closes only when all admitted OAM owners write the portable snapshot through translated C and route tests establish their source semantics; it does not verify CHR consumption or close M2. |
| Original Owner Request | Make the native C result and logic match the original ROM, then close M2 only with evidence. |
| Similar-Issue Sweep | Search all production and test output paths for placeholder OAM, source-range omissions, host-owned sprite state, incomplete button mapping, unsupported playable claims, and local-path leakage; record every hit and disposition. |

## Recent M4 Closures

| Task | Compact result |
| --- | --- |
| T1 | The physical 486SX qualification protocol defines build identity, host facts, scripted routes, timing samples, and acceptance evidence without any fabricated measurement. [History](../history/M4-T1-486sx-qualification-protocol.md). |

## Deferred M4 Evidence

- An isolated SoftPC compatibility probe booted the ROM-free DOS MZ for a
  bounded fifteen seconds without host-process exit. It is not physical-host,
  performance, visual, or gameplay evidence. [Record](../history/M4-T2-S1-softpc-compatibility-probe.md).

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
| T8 | MZ/map structural evidence is reproducible; the local host's documented lack of graphical DOS presentation prevents a false runtime claim. [History](../history/M3-T8-dos-runtime-structural-evidence.md). |

## Prior M2 Records Under Correction

These records retain their original task evidence but no longer establish M2
completion. T9 audits and replaces the insufficient frame/output proof.

| Task | Compact result |
| --- | --- |
| T1 | Full direct-ROM PRG analysis, revision reconciliation, and source-address architecture record completed with zero unresolved PRG bytes. [History](../history/M2-T1-prg-static-analysis.md). |
| T2 | Title input/start C90 route and bounded owner-local transition checkpoint closed; A+Start mirror audit repaired. [History](../history/M2-T2-title-start-checkpoint.md). |
| T3 | Area bootstrap, actual area-pointer/header parsing, object stream classification, and native command queue closed. [History](../history/M2-T3-area-bootstrap-and-commands.md). |
| T4 | Player physics, terrain collision, entrances, scrolling, and bounded owner-local checkpoint closed. [History](../history/M2-T4-player-route-and-collision.md). |
| T5 | Blocks, items, enemies, projectiles, score/timer/power, firebars, Bowser, and platform routes closed. [History](../history/M2-T5-object-routes.md). |
| T6 | Death, restart, two-player exchange, Warp Zone, and completion modes closed. [History](../history/M2-T6-mode-routes.md). |
| T7 | Original audio queues, priorities, buffers, and neutral command state closed. [History](../history/M2-T7-audio-command-routes.md). |
| T8 | Bounded title-to-play oracle, Win32 composition audit, and two original frame-order repairs were recorded; the output proof is superseded by T9. [History](../history/M2-T8-end-to-end-oracle-and-win32-route.md). |

## Recent M2 Closures

| Task | Compact result |
| --- | --- |
| T10 | Source-owned name tables, attributes, palettes, status, scroll, and PPU commit state now reach the canonical snapshot through native C; OAM remains deferred to T11. [History](../history/M2-T10-translated-background-output.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
