# Project Status

**Active: none. M3 T38 closed; the retained-performance qualification candidate is queued.**

## M3 T38 S19 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Zero-ROM selected retained-product timing and local artifact qualification after S18 exact union-repair closure; transferred at owner direction. |
| Admission And Approval | Owner authorized measured S repartition toward 20ms/10ms. S18 has already proven the retained presenter exactly; S19 measures the bound product rather than a dormant fixture. |
| Objective | Repeat the post-Start fixed-3000 route on the bound DOS product, compare it to S10's 39,026 ticks, then refresh the three local target artifacts only if the selected route remains exact. |
| Non-goals | No ROM/core semantic change, VGA readback as an authoritative source, full logical frame, output reduction, frame skip, DOSBox setting change, or PPU policy change. |
| Reference Baseline | S10 selected Chain-4: 39,026 PIT ticks. S18 private, diagnostic-separated presenter interval: 5,461 PIT ticks. |
| Candidate Proposal | [M3 T38 fixed-cycle DOS16 profile](../history/M3-T38-fixed-cycle-dos16-profile.md). |
| Files And ABI Surface | Existing DOS16 retained presenter and build/package outputs; optional private fixture instrumentation only. No core, ROM-state, or platform-selected PPU policy. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Reuse S18's 260-frame physical oracle, then run matched no-diagnostic bound-product timing, DOS16 MZ/memory receipt, x86/x64 builds, platform purity, and graphics/text lifecycle route. |
| Expected Markers | ROM scope[], expectedMatches[], actualMatches[], new0; historical1992/1992, local1991/1992,4260/4261 feasible controls unchanged(raw4342,infeasible81). |
| Asset Needs | None; owner ROM is a private timing input only. |
| Reporting Requirements | Quantify patch bytes, exactness matrix and complete fixed-route delta. |
| Stop Conditions | Any physical pixel divergence, full-frame allocation, game/PPU policy leak, or no material bound-product gain. |
| Exit Criteria | Transferred: the active T closes with accepted exact presenter, product builds and artifacts. Comparable fixed-3000 timing is owned only by the queued successor. |
| Original Owner Request | Compress the roughly 50ms path materially toward 20ms. |
| Similar-Issue Sweep | Sparse/dense OAM, overlap, priority, clipping, left-edge mask, fixed status, title, scrolling and text/graphics restore. |

## Current Technical Baseline

- The only selected product presenter is S10 Chain-4 at 39,026 PIT ticks (32.71ms).
- S11/S12/S17 saved-background retained candidates are rejected by physical readback; they are not product paths.
- S18 has zero ROM-node/control-edge scope; S13--S17 are closed. The independent S17 PPU background-mask cache fix has a focused host proof.
