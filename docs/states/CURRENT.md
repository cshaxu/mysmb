# Project Status

**Active: M3 T39 S1. Contained historical NESticle source build/run qualification for retained-presentation performance research.**

## M3 T39 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New M3 performance-qualification task; zero-ROM audit. |
| Admission And Approval | Owner requested inspection of the historical 1997 NESticle source and authorized local build/probe containment under `build/`. |
| Objective | Build the identified historical source locally under ignored `build/`, run an isolated standard-VGA benchmark harness assembled from its CPU/PPU/video sources with the owner-local SMB input in a temporary DOSBox session, then run an independent pure-DOS16 physical-output microbenchmark against the current MySMB slot-copy owner. Identify concrete cache, composition, transfer and cadence mechanisms against the selected MySMB DOS16 retained presenter. |
| Non-goals | No MySMB product code or artifact change; no core/PPU policy or ROM-logic change; no persistent DOSBox setting; no third-party binary/source/runtime import, source transliteration, redistribution, or product dependency. |
| Reference Baseline | T38 S10 selected Chain-4: 39,026 PIT ticks (32.71ms); T38 S18 exact retained presenter with 260-frame physical oracle. Owner reports NESticle visually stable at the same visible DOSBox 3000-cycle setting. |
| Candidate Proposal | [Retained presentation performance qualification](../proposals/m3/retained-performance-qualification.md). |
| Files And ABI Surface | Ignored `build/m3-t39-s1/` only for archive copy, source extraction, temporary compatible toolchain, build, DOSBox commands and probes. The microbenchmark may copy the current physical-output owner and test it against a private RAM destination, but changes no tracked product source or ABI; tracked output is limited to neutral research conclusions in the proposal/history. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Archive/source identity receipt; dependency inventory; contained build attempt using a temporary toolchain; temporary DOSBox launch with the owner-local SMB input; only after successful launch, bounded local timing probes. For the independent DOS16 probe, use identical deterministic 256x240 slot rows, compare final A000 bytes for each candidate, and attribute repeated samples using the BIOS-owned PIT without changing its rate; compare each proposed concept with current exactness/memory/platform constraints. |
| Expected Markers | ROM scope[], expectedMatches[], actualMatches[], new0; historical1992/1992, local1991/1992,4260/4261 feasible controls unchanged(raw4342,infeasible81). |
| Asset Needs | Owner-provided historical NESticle binary archive and public historical source revision, both local-only and unredistributable research inputs; owner-local SMB ROM used only as an ignored DOSBox runtime input. |
| Reporting Requirements | State exact archive/version identity locally; distinguish source facts, probe observations and inferences; list compatible, conditional and rejected design ideas with affected MySMB owner and anticipated cost/memory impact. |
| Stop Conditions | Missing/unidentified source dependency after an evidenced compatible-toolchain attempt; source redistribution ambiguity; any requirement to import third-party code/runtime into MySMB, alter core semantics, modify persistent DOSBox settings, or reduce observable frame/update work. |
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
sprite redraw and flat-32-bit assembly. A contained Open Watcom/DOS4GW
build now runs 1,200 owner-local SMB frames through a standard-VGA Mode 13h
harness at fixed 3,000 DOSBox cycles in 20.92 seconds (17.4ms/frame). The
harness retains the historical CPU/PPU/pattern/sprite code but substitutes a
small direct ROM launcher, generic palette and Mode 13h sink because the
public package lacks GUI and VESA dependencies; it is a directional
performance receipt, not an x.xx-binary equivalence claim. Current MySMB
writes transient overlay bytes directly to visible A000, making visible
intermediate updates a concrete device-only flicker candidate. No source,
artifact or ROM accounting changed.

The independent DOS16 physical-output probe has now rejected a single
61,440-byte RAM staging surface as a speed candidate: with the copied current
slot-copy owner and identical final A000 bytes, its fixed-3000 cost was
11.983ms/frame versus 6.971ms/frame for the split direct-A000 form. A small
address table recovered only 0.169ms/frame of that extra cost. This confines
the next performance investigation to composition/cache work, rather than a
RAM compose-and-copy rewrite; it does not establish a 16-versus-32-bit cause.
