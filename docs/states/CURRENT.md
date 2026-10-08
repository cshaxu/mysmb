# Project Status

**Active: M3 T39 S1. Read-only NESticle source/probe comparison for retained-presentation performance qualification.**

## M3 T39 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New M3 performance-qualification task; zero-ROM audit. |
| Admission And Approval | Owner requested inspection of the historical 1997 NESticle source and authorized local build/probe containment under `build/`. |
| Objective | Identify the reference pipeline's concrete cache, composition, transfer and cadence mechanisms; compare them against the selected MySMB DOS16 retained presenter and publish only a compatible opportunity matrix. |
| Non-goals | No product code, artifact, core/PPU policy, ROM logic, DOSBox persistent setting, DOS4GW/toolchain, binary/source import, source transliteration or performance claim. |
| Reference Baseline | T38 S10 selected Chain-4: 39,026 PIT ticks (32.71ms); T38 S18 exact retained presenter with 260-frame physical oracle. Owner reports NESticle visually stable at the same visible DOSBox 3000-cycle setting. |
| Candidate Proposal | [Retained presentation performance qualification](../proposals/m3/retained-performance-qualification.md). |
| Files And ABI Surface | Ignored `build/m3-t39-s1/` only for archive copy, extraction, optional build and probes; tracked output is limited to neutral research conclusions in the proposal/history. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Archive identity/version inspection; source call-path and data-flow review; optional local build/probe below `build/`; compare each proposed concept with current exactness/memory/platform constraints. |
| Expected Markers | ROM scope[], expectedMatches[], actualMatches[], new0; historical1992/1992, local1991/1992,4260/4261 feasible controls unchanged(raw4342,infeasible81). |
| Asset Needs | Owner-provided historical NESticle source archive; local-only, unredistributable, copied only below ignored `build/`. No ROM material is needed for source inspection. |
| Reporting Requirements | State exact archive/version identity locally; distinguish source facts, probe observations and inferences; list compatible, conditional and rejected design ideas with affected MySMB owner and anticipated cost/memory impact. |
| Stop Conditions | Missing/unidentified archive; source redistribution ambiguity; any requirement to import third-party code/runtime, alter core semantics, modify persistent DOSBox settings, or reduce observable frame/update work. |
| Exit Criteria | A bounded source/probe report identifies the actual reference render path and leaves a ranked, independently implementable MySMB candidate list or a defensible no-change result. |
| Original Owner Request | Determine why historical NESticle has stable, smooth DOS presentation while MySMB visibly refreshes/flickers, and find lawful, compatible performance mechanisms. |
| Similar-Issue Sweep | Existing public 0.2 observations, owner-local x.xx executable receipts, MySMB PPU/frame composition, DOS Chain-4/retained device and text presenter boundaries. |

## Current Technical Baseline

- The selected DOS product is T38 S18 current-background sprite-union presentation; its 260-frame physical oracle was exact.
- T38 S10's fixed-3000 diagnostic baseline is 39,026 PIT ticks (32.71ms); the `cycles=max` interval is diagnostic only.
- T39 S1 is read-only research. It changes no product code, ROM-state accounting or selected presenter.

## T39 S1 Research Checkpoint

The local research result is recorded in the active proposal. The historical
source confirms dirty cached nametables, palette-slot retention, full moving
sprite redraw and flat-32-bit assembly, while its missing DOS platform backend
prevents a claim about x.xx page flipping or default VSync. Current MySMB
writes transient overlay bytes directly to visible A000, making visible
intermediate updates a concrete device-only flicker candidate. No source,
artifact or ROM accounting changed.
