# Project Status

**Active: M3 T39 S6. DOS16 compact-VRAM double-page presenter integration.**

## M3 T39 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of M3 T39 after S5 found a compact-VRAM latch-copy candidate. |
| Admission And Approval | Owner approved implementation after the S5 feasibility result. |
| Objective | Implement a DOS16-only compact 512-by-240 retained cache with two hidden 264-by-240 VGA composition pages, then decide by exact output and matched timing whether it can replace the direct-visible retained presenter. |
| Scope | `src/platform/dos16/devices.c`, `retained_background.[ch]`, DOS16-only tests and ignored probe material. |
| Non-goals | Do not change game/PPU semantics, cadence, dimensions, shared IO, Win32, text presentation, persistent DOSBox configuration, DOS4GW, frameskip or a helper process. |
| Reference Baseline | The current retained presenter has exact output and a 338,395-tick steady presenter interval. S5's wrapped latch viewport copy is 143,551 ticks in the same diagnostic environment. |
| Candidate Proposal | [Retained presentation performance qualification](../proposals/m3/retained-performance-qualification.md#s5-result----compact-vram-display-page-candidate-is-feasible-for-implementation). |
| Files And ABI Surface | DOS16 device implementation and focused owned tests; ignored owner-local DOS toolchain, DOSBox and probe material. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Expected Markers | ROM scope[], expectedMatches[], actualMatches[], new0; historical 1992/1992 unchanged. |
| Asset Needs | Existing owner-local DOS toolchain, DOSBox and current product inputs only. |
| Stop Conditions | Revert/reject on a pixel, palette, OAM-order or VGA-state difference; any conventional-memory allocation; >256KiB VGA requirement; or no material matched timing improvement. |
| Verification | Exhaustive scroll/panning layout test, retained-frame byte oracle on actual PPU frames, focused DOS16 build/run and fixed-cycle matched timing against the current retained route. Run ledger and documentation validation. |
| Exit Criteria | Compact path accepted only with exact final output and at least 20-percent retained-presenter improvement; otherwise preserve/restore current path and record the rejection. |
| ROM scope | `[]`; zero nodes and zero control edges. Historical markers unchanged. |
| Reporting | Report page/cache capacity, conventional-memory delta, exactness route/frame count, before/after timing, artifact state and acceptance/rejection. |
| Reporting Requirements | State route count, frame count, retained-mode status, counter categories, code/artifact status and explicit next-S state. |
| Original Owner Request | Improve DOS16 speed through evidence-led work; implement the proven compact-VRAM page candidate without changing shared semantics. |
| Similar-Issue Sweep | Visible A000 writes, latch modes, CRTC pages, horizontal panning, vertical wrap, retained background, HUD, repair and sprites. |

## Current Technical Baseline

- S1 found a NESticle-style flat 32-bit RAM screen is a different model, not an importable DOS16 dependency.
- S2's accepted HUD plane batching gave only a 1.88 percent matched presenter improvement.
- S3 recorded title, transition and steady retained work. S4 rejected repair batching because even an idealized change is bounded near one percent.
- No product source or local executable changes have occurred in S3/S4.

## Recent Closure Summaries

### T39 S4 -- sprite-repair plane-batching decision

S4 changed no product code or artifact. S3's stable route had twelve repair tiles and five sprite tiles per frame. Even eliminating all associated plane selections scales to at most about 1.03 percent from S2's measured 1.88-percent result for removing 124 HUD selects. It cannot meet the 20-percent threshold, so the device rewrite was rejected. The quantified decision is retained in the [T39 proposal](../proposals/m3/retained-performance-qualification.md#s4-decision----reject-sprite-repair-plane-batching).
