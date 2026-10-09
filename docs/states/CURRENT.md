# Project Status

**Active: M3 T39 S8. NESticle-style DOS16 RAM composition foundation.**

## M3 T39 S8 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of open M3 T39 after S7 rejection. |
| Admission And Approval | Owner directed: rebuild the DOS16 presenter around NESticle-style dirty RAM surfaces, contiguous composition and final VGA submission. |
| Objective | Establish the DOS16 RAM-composition foundation while preserving one shared translated game and PPU semantics. |
| Scope | `src/platform/dos16`, DOS composition root, neutral presentation contracts only when required; focused tests and ignored timing evidence. |
| Non-goals | No core/ROM logic, shared PPU decisions, Win32/text behavior, DOS4GW, third-party import, helper process or persistent DOSBox change. |
| Reference Baseline | S7: 601 root steps, 2 submitted/596 skipped graphical steps; gate rejected as a performance solution. |
| Candidate Proposal | [Retained presentation performance qualification](../proposals/m3/retained-performance-qualification.md#s8-admission----nesticle-style-ram-composition-foundation). |
| Files And ABI Surface | DOS16 presentation storage, presenter binding and neutral presentation views only. |
| Applicable Rules | Execution, Architecture, Coding and source policy. |
| Expected Markers | ROM scope[]; expectedMatches[], actualMatches[], new0; historical 1992/1992 unchanged. |
| Asset Needs | Existing local DOS toolchain, DOSBox and owner-local ROM only. |
| Stop Conditions | Any shared-game/PPU behavior change, output mismatch, memory-budget failure, third-party import, or no measurable whole-route improvement. |
| Verification | Exact PPU-output oracle, dirty/cache composition receipts, focused x86/x64 tests, DOS16 link/run, platform purity, fixed-route timing and memory receipt. |
| Exit Criteria | A bounded RAM-composition foundation is accepted only with exact output, documented memory ownership and measurable route improvement; otherwise reject without frameskip substitution. |
| ROM scope | `[]`; zero nodes and zero control edges. |
| Reporting | Report RAM/VGA sizes, dirty work, composition/final-copy timing, exact route coverage, artifacts and successor state. |
| Reporting Requirements | State submitted frame count separately from logical ticks; never substitute skipped frames for speed evidence. |
| Original Owner Request | Rebuild MySMB DOS presenter according to NESticle's architecture without copying its code. |
| Similar-Issue Sweep | Background tile invalidation, scroll seams, HUD split, sprite priority/opacity, palette changes, transition/full invalidation, text mode and output fallback. |
## M3 T39 S6 Archived Packet

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

## M3 T39 S6 Closure Record

The accepted device-only route uses 249,600 of 262,144 VGA bytes and adds zero
conventional-memory allocation.  Its original per-slot HUD addressing made the
first product route slow; the similar-issue sweep found the same avoidable
address recomputation only in compact HUD output.  Replacing it with
plane-major row spans produced 252,787 PIT ticks/frame in the warm-cache
product route, 25.3 percent below the 338,395-tick reference and 15.3 percent
below the matched 298,397-tick legacy route.  No shared game, PPU, text or
Win32 production hit exists.  Exhaustive compact-layout coverage, the
canonical-PPU overlay oracle, retained background/apply/overlay tests,
platform purity, both host focused suites and a DOS16 MZ DOSBox launch pass.
All three packaged target artifacts were refreshed.  T39 remains open only
for a separately admitted successor candidate.

## Current Technical Baseline

- S1 found a NESticle-style flat 32-bit RAM screen is a different model, not an importable DOS16 dependency.
- S2's accepted HUD plane batching gave only a 1.88 percent matched presenter improvement.
- S3 recorded title, transition and steady retained work. S4 rejected repair batching because even an idealized change is bounded near one percent.
- No product source or local executable changes have occurred in S3/S4.

## Recent Closure Summaries

### T39 S4 -- sprite-repair plane-batching decision

S4 changed no product code or artifact. S3's stable route had twelve repair tiles and five sprite tiles per frame. Even eliminating all associated plane selections scales to at most about 1.03 percent from S2's measured 1.88-percent result for removing 124 HUD selects. It cannot meet the 20-percent threshold, so the device rewrite was rejected. The quantified decision is retained in the [T39 proposal](../proposals/m3/retained-performance-qualification.md#s4-decision----reject-sprite-repair-plane-batching).

