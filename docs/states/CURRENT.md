# Project Status

## Current Work

## M3 T41 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T41 S2 P2 — implementation |
| Admission And Approval | Owner approved T41 on 2026-10-12; S1 closed in P1 `63b06b85` after its shared projection and governance scope. |
| Objective | Separate the Win32 console session, geometry/input and presentation responsibilities; bound RGB VT storage to the selected 25/50-row frame; replace direct implementation inclusion with a declared test seam. |
| Non-goals | No ROM/core/PPU/text-scene change; no terminal input query; no DOS graphics or process-topology change. |
| Reference Baseline | M3 T40 S3 P9, commit `46909575`; accepted CMD, graphical Tab and run16 corpus. |
| Candidate Proposal | [M3 T41 proposal](../proposals/m3/text-presentation-quality.md). |
| Files And ABI Surface | `src/platform/win32/text_console.*` and focused Win32 tests; private adapter decomposition only, no game ABI change. |
| Applicable Rules | Execution, Architecture, Coding, documentation governance and source policy. |
| Verification | 25/50-row VT capacity tests; indexed and RGB presentation smoke tests through the declared seam; x86/x64 build/test; final DOS16 link and purity/documentation gates remain S3 closure work. |
| Expected Markers | One lifecycle contract; RGB capacity proportional to selected rows; unchanged glyph ownership; no VT input query; no production-source inclusion in tests. |
| Asset Needs | Existing owner-local build inputs only; no new research or imported assets. |
| Reporting Requirements | Report changed owners, test-owner mapping, build results, artifacts after code changes, and build cleanup at acceptance. |
| Stop Conditions | Any core/PPU semantic difference, terminal query requirement, or inability to preserve the accepted three-route corpus. |
| Exit Criteria | S2's Windows adapter has focused ownership boundaries, bounded VT allocation and contract-level tests; S3 remains planned for cross-adapter/product closure. |
| Original Owner Request | Audit and correct duplicate non-core paths, DOS/Win32 colour projections, VT capability architecture, code quality, cleanup and test closure. |
| Similar-Issue Sweep | Inspect every Win32 console session, close/suspend/resume, input/geometry, `terminal_output`, `WriteConsole*`, VT selection and production-source test inclusion. |

## Current Technical Baseline

The Win32 text adapter has two projections of the same shared text frame.
Normal or visible Console devices that accept output VT use authored RGB SGR.
The hidden no-window 2x4 carrier used by run16 uses indexed sixteen-colour
`CHAR_INFO` output even when it accepts a VT mode bit. Capability selection
does not inspect process identity, window title, launcher, run16 name or game
input; it emits no terminal query and normal Escape remains the text exit key.

## Recent M3 Closures

| Task | Compact result |
| --- | --- |
| T40 | Win32 console-session identity and capability presentation close with owner-accepted CMD, graphical-Tab and run16 corpus. Normal/visible devices retain RGB VT; the hidden 2x4 carrier uses the stable standard-colour projection. Zero ROM nodes and edges. [History](../history/M3-T40-win32-console-session-identity.md). |
