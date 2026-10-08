# Project Status

**Active: M3 T39 S5. DOS16 buffered-composition feasibility decision.**

## M3 T39 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of M3 T39 after closed S4 rejection. |
| Admission And Approval | Owner approved the S1?S5 evidence-led DOS16 performance sequence. S4 rejected repair-plane batching from measured return. |
| Objective | Determine whether a presentation-only visible-page, retrace handoff or compact composition arrangement can reduce visible-A000 tearing and materially improve DOS16 cadence within the conventional-memory policy. |
| Scope | Read-only DOS16 device/VGA-memory feasibility research and proposal/ledger evidence. No product source change is admitted. |
| Non-goals | Do not change game/PPU semantics, cadence, dimensions, RAM cache policy, persistent DOSBox configuration, introduce DOS4GW, frameskip or a helper process. Do not repeat the rejected naive 61,440-byte RAM surface. |
| Reference Baseline | The current retained path has exact physical output but writes overlays directly to visible A000. The rejected naive RAM surface measured 11.983ms/frame versus 6.971ms/frame direct split-A000. S2/S3 reject micro-batching as a material speed path. |
| Candidate Proposal | [Retained presentation performance qualification](../proposals/m3/retained-performance-qualification.md#s5----buffered-composition-feasibility-re-evaluation). |
| Files And ABI Surface | Ignored research/probe material and tracked governance records only. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Expected Markers | ROM scope[], expectedMatches[], actualMatches[], new0; historical 1992/1992 unchanged. |
| Asset Needs | Existing owner-local DOS toolchain, DOSBox and current product inputs only. |
| Stop Conditions | Reject any option requiring an unmeasured full RAM surface, changing shared semantics, unbounded conventional memory, unavailable VGA memory, or a synthetic visual claim. |
| Verification | Establish VGA page/address feasibility, exact final-pixel boundary, conventional-memory accounting and a matched cadence comparison only if a bounded candidate exists. Run ledger and documentation validation. |
| Exit Criteria | Explicit feasible/rejected decision with memory, timing and pixel-equivalence constraints; any implementation requires a later S. |
| ROM scope | `[]`; zero nodes and zero control edges. Historical markers unchanged. |
| Reporting | Report VGA capacity, memory cost, tear/cadence mechanism, feasible candidate or rejection and resulting implementation state. |
| Reporting Requirements | State route count, frame count, retained-mode status, counter categories, code/artifact status and explicit next-S state. |
| Original Owner Request | Improve DOS16 speed through evidence-led work; prioritize HUD batching, phase census, sprite repair decision and only then composition buffering. |
| Similar-Issue Sweep | Visible A000 writes, retrace, display pages, retained background, RAM surfaces, HUD, repair and sprite paths. |

## Current Technical Baseline

- S1 found a NESticle-style flat 32-bit RAM screen is a different model, not an importable DOS16 dependency.
- S2's accepted HUD plane batching gave only a 1.88 percent matched presenter improvement.
- S3 recorded title, transition and steady retained work. S4 rejected repair batching because even an idealized change is bounded near one percent.
- No product source or local executable changes have occurred in S3/S4.

## Recent Closure Summaries

### T39 S4 -- sprite-repair plane-batching decision

S4 changed no product code or artifact. S3's stable route had twelve repair tiles and five sprite tiles per frame. Even eliminating all associated plane selections scales to at most about 1.03 percent from S2's measured 1.88-percent result for removing 124 HUD selects. It cannot meet the 20-percent threshold, so the device rewrite was rejected. The quantified decision is retained in the [T39 proposal](../proposals/m3/retained-performance-qualification.md#s4-decision----reject-sprite-repair-plane-batching).
