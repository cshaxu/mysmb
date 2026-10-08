# Project Status

**Active: M3 T39 S2. DOS16 retained fixed-HUD plane-batching root-cause analysis.**

## M3 T39 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of M3 T39 after closed S1 research. S2 has an accepted DOS16-only physical-writer implementation awaiting ordinary S closure. |
| Admission And Approval | Owner approved the four ordered S tasks, then explicitly directed that S3 must not be entered until the S2 regression has been analysed. |
| Objective | Explain the measured regression of the plane-batched fixed-HUD candidate and decide whether a different bounded S2 implementation remains justified. |
| Scope | `src/platform/dos16/devices.c` only for rejected/probed candidates plus ignored source-matched fixtures and proposal evidence. No shared PPU/core, ROM, text, Win32, cadence, DOSBox persistent configuration, buffer or page-flip change. |
| Non-goals | Do not admit S3; do not treat a reduction in plane selections as a proxy for speed; do not change shared PPU/core, frame cadence, display dimensions, or persistent DOSBox configuration. |
| Measured fact | At fixed `core=auto`, `cycles=fixed 3000`, the first source-matched real-mode candidate regressed presenter time: 306,673→309,925 PIT ticks/frame (+1.06%). The accepted caller-local version completed the matched 60-frame route with 32 fixed-HUD frames: presenter 344,869→338,395 PIT ticks/frame (-1.88%), root 412,730→406,215 (-1.58%). |
| Reference Baseline | T38 S18 selected retained presenter; S1 census found 16,384 fixed-HUD A000 bytes/frame and 128 HUD plane selections/frame. The S2 candidate is compared against that same retained route. |
| Candidate Proposal | [Retained presentation performance qualification](../proposals/m3/retained-performance-qualification.md#s2----fixed-hud-plane-batching). |
| Files And ABI Surface | Product candidate scope remains `src/platform/dos16/devices.c`; private probes remain below ignored `build/`. No public ABI change. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Expected Markers | ROM scope[], expectedMatches[], actualMatches[], new0; historical 1992/1992 unchanged. |
| Asset Needs | Existing owner-local generated runtime input and ignored temporary DOSBox sessions only. |
| Stop Conditions | Any final-A000/device-state difference, unsupported toolchain, or no measured improvement rejects the candidate rather than changing cadence. |
| Verification | Compare generated 16-bit assembly and instruction/data-access cost of the old/new HUD paths; retain the exact 512-case final-A000 layout model; any new candidate requires same route PIT and existing physical-output contract. |
| Exit Criteria | A causal account backed by code-generation evidence, byte-layout and route evidence, three target builds and documented closure. S3 remains planned until the owner admits it. |
| ROM scope | `[]`; zero nodes and zero control edges. Historical markers unchanged. |
| Reporting | Report why reduced plane writes failed to improve time, exact affected instruction/data paths, and whether there is a viable S2 successor. |
| Reporting Requirements | Report before/after PIT, fixed-HUD frame count, assembly-level causal evidence, byte-layout result, code/artifact status and the explicit S3 admission state. |
| Original Owner Request | Improve DOS16 speed through evidence-led work; prioritize HUD batching, then phase census, then sprite repair decision and only then composition buffering. |
| Similar-Issue Sweep | Fixed HUD restore/commit, plane selection, far/near slot extraction, retained background repair and sprite presentation. |

## Current Technical Baseline

- The selected DOS product is T38 S18 current-background sprite-union presentation; its 260-frame physical oracle was exact.
- T39 S1 closed as read-only comparative research. It found that the historical source's background cache and per-frame sprite redraw do not justify a core rewrite or suppressed sprites; its flat 32-bit RAM composition is not importable into real-mode DOS16.
- A contained DOS16 test rejected the naive 61,440-byte RAM composition surface: 11.983ms/frame versus 6.971ms/frame for the direct split-A000 control. This is not a ban on all later anti-tearing designs, only on repeating that unmodified layout.
- S2's far-pointer plane-batch candidate was rejected after an actual retained-presenter regression. The accepted replacement keeps raw-slot extraction in its original caller and moves only `vga_retained_plane` outside the 32-row loop. The prior apparent early exits were test-host cleanup of a detached DOSBox process, not candidate crashes. S3–S5 remain planned and are not active.

## Recent Closure Summaries

### T39 S1 -- comparative source and work-census research

S1 remained local-only and changed no product source, artifacts or ROM accounting. Its product-root 60-frame normal-game census found the retained background almost idle (4.3 changed-background A000 bytes/frame), while fixed HUD restore plus commit wrote 16,384 bytes/frame and the HUD commit alone selected VGA planes 128 times/frame. This justifies S2's bounded physical writer change. The full research receipt and opportunity ranking are retained in the [T39 proposal](../proposals/m3/retained-performance-qualification.md).
