# Project Status

**Active: M3 T39 S2. DOS16 retained fixed-HUD plane-batching implementation.**

## M3 T39 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of M3 T39 after its closed zero-ROM S1 research step. |
| Admission And Approval | Owner explicitly approved four ordered S tasks: HUD plane batching, multi-stage census, evidence-led sprite-repair decision, then buffered-composition re-evaluation. This packet admits their first implementation step only. |
| Objective | Replace the DOS16 retained fixed-HUD one-line-at-a-time VGA plane selection with an equivalent plane-batched physical writer. Preserve every shared-PPU input, retained viewport calculation, slot choice, final A000 byte and cadence. |
| Non-goals | No translated ROM/core/PPU/text/Win32 change; no new frame buffer, page flip, retrace policy, frameskip, helper process, DOS4GW dependency or persistent DOSBox configuration change. S2 does not decide sprite repair or buffered composition. |
| Reference Baseline | T38 S18 selected retained presenter passed a 260-frame physical oracle. T39 S1's 60-frame normal-game census measured 16,384 fixed HUD A000 bytes and 128 HUD plane selections per frame within 200.1 total plane selections/frame. The historical source receipt is directional only. |
| Candidate Proposal | [Retained presentation performance qualification](../proposals/m3/retained-performance-qualification.md#s2----fixed-hud-plane-batching). |
| Files And ABI Surface | Production scope is `src/platform/dos16/devices.c` and its existing DOS16-focused test/build support only. Private timing/oracle fixtures, ROM input, captures and logs remain below ignored `build/`. No public ABI or shared component surface changes. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Before/after fixed-3000 PIT receipt from a source-matched product fixture; existing/expanded retained A000 physical oracle across the accepted route; focused DOS16 tests/link, Win32 x86/x64 regressions and platform-purity scan. Refresh local 16/32/64 artifacts only if product source changes. |
| Expected Markers | ROM scope[], expectedMatches[], actualMatches[], new0; historical 1992/1992; current local 1991/1992 and 4260/4261 feasible controls (raw 4342, infeasible 81) unchanged. |
| Asset Needs | Existing owner-local generated runtime input and ignored DOSBox temporary session only; no new third-party source, runtime, asset or persistent tool configuration. |
| Reporting Requirements | Report exact changed owner/files, before/after plane-selection and PIT measurements, exact-oracle result, all artifact build results and S2's actual source size. Report S3--S5 as planned dependencies, not completed work. |
| Stop Conditions | Any shared-PPU/ROM-state effect, changed final A000 byte/device end state, unsupported toolchain/runtime requirement, inadequate source-matched timing fixture or no measurable benefit. Revert/reject the candidate rather than mask it through cadence changes. |
| Exit Criteria | A reviewed plane-batched HUD path or explicit rejection, with exact physical-output evidence and an evidence-backed handoff to S3. |
| Original Owner Request | Apply the highest-return NESticle-inspired work first, measure different game phases before choosing sprite repair, and leave double buffering/background composition until the earlier evidence exists. |
| Similar-Issue Sweep | Fixed HUD restore/commit, retained background repair, sprite repair/draw, VGA map-plane selection, viewport wrapping, text/graphics presenter boundaries and direct-visible A000 writes. |

## Current Technical Baseline

- The selected DOS product is T38 S18 current-background sprite-union presentation; its 260-frame physical oracle was exact.
- T39 S1 closed as read-only comparative research. It found that the historical source's background cache and per-frame sprite redraw do not justify a core rewrite or suppressed sprites; its flat 32-bit RAM composition is not importable into real-mode DOS16.
- A contained DOS16 test rejected the naive 61,440-byte RAM composition surface: 11.983ms/frame versus 6.971ms/frame for the direct split-A000 control. This is not a ban on all later anti-tearing designs, only on repeating that unmodified layout.
- S2 changes only DOS16 physical write grouping. S3, S4 and S5 are admitted in the proposal sequence but are not active until S2 closes.

## Recent Closure Summaries

### T39 S1 -- comparative source and work-census research

S1 remained local-only and changed no product source, artifacts or ROM accounting. Its product-root 60-frame normal-game census found the retained background almost idle (4.3 changed-background A000 bytes/frame), while fixed HUD restore plus commit wrote 16,384 bytes/frame and the HUD commit alone selected VGA planes 128 times/frame. This justifies S2's bounded physical writer change. The full research receipt and opportunity ranking are retained in the [T39 proposal](../proposals/m3/retained-performance-qualification.md).
