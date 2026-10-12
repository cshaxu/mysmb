# Project Status

## Current Work

## M3 T41 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T41 S1 P1 — implementation |
| Admission And Approval | Owner approved the code-quality task and its governance additions on 2026-10-12. |
| Objective | Establish one shared indexed text-colour projection and the rules needed for bounded, owner-closed quality work. |
| Non-goals | No ROM/core/PPU/text-scene change; no terminal input query; no DOS graphics or process-topology change. |
| Reference Baseline | M3 T40 S3 P9, commit `46909575`; accepted CMD, graphical Tab and run16 corpus. |
| Candidate Proposal | [M3 T41 proposal](../proposals/m3/text-presentation-quality.md). |
| Files And ABI Surface | `src/io/color.*`, DOS16 text device, Win32 text-console adapter and focused tests; no game ABI change. |
| Applicable Rules | Execution, Architecture, Coding, documentation governance and source policy. |
| Verification | Shared projection unit test; DOS16 and Win32 focused presentation tests; x86/x64 build/test; DOS16 link; purity and documentation gates. |
| Expected Markers | Canonical/source palette equivalence; all 16 slots; foreground/background attributes; unchanged glyph ownership; no VT input query. |
| Asset Needs | Existing owner-local build inputs only; no new research or imported assets. |
| Reporting Requirements | Report changed owners, test-owner mapping, build results, artifacts after code changes, and build cleanup at acceptance. |
| Stop Conditions | Any core/PPU semantic difference, terminal query requirement, or inability to preserve the accepted three-route corpus. |
| Exit Criteria | S1 shared projection and governance rules pass focused checks; remaining T41 S2/S3 stay planned. |
| Original Owner Request | Audit and correct duplicate non-core paths, DOS/Win32 colour projections, VT capability architecture, code quality, cleanup and test closure. |
| Similar-Issue Sweep | Inspect every `mysmb_io_color_text_*`, `source_colors`, `CHAR_INFO`, B800 text write, VT selection and direct production-source test include. |

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
