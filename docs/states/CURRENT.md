# Project Status

## Current Work

## M3 T41 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T41 S3 P3 — closure |
| Admission And Approval | Owner approved T41 on 2026-10-12; S1 closed in P1 `63b06b85` and S2 closed in P2 `8949fb51`. |
| Objective | Close T41 with complete x86/x64 unit and integration matrices, DOS16 compiler/link/product verification, platform-purity and documentation gates, refreshed local products for changed code, and a test-owner receipt. |
| Non-goals | No ROM/core/PPU/text-scene change; no terminal input query; no DOS graphics or process-topology change. |
| Reference Baseline | M3 T40 S3 P9, commit `46909575`; accepted CMD, graphical Tab and run16 corpus. |
| Candidate Proposal | [M3 T41 proposal](../proposals/m3/text-presentation-quality.md). |
| Files And ABI Surface | Existing T41 source owners and tests; local `assets/mysmb16.exe`, `assets/mysmb32.exe`, `assets/mysmb64.exe` only after each target validates. |
| Applicable Rules | Execution, Architecture, Coding, documentation governance and source policy. |
| Verification | Full x86/x64 build and CTest matrices; DOS16 compile/link and DOS product probe; all three product self-tests; platform-purity, ledger and documentation governance gates; product artifact hashes. |
| Expected Markers | 283/283 x86 and x64 tests; a linked DOS16 MZ executable; three fresh product artifacts; no platform leakage or unowned test path. |
| Asset Needs | Existing owner-local build inputs only; no new research or imported assets. |
| Reporting Requirements | Report changed owners, test-owner mapping, build results, artifacts after code changes, and build cleanup at acceptance. |
| Stop Conditions | Any core/PPU semantic difference, terminal query requirement, or inability to preserve the accepted three-route corpus. |
| Exit Criteria | All T41 acceptance criteria are evidenced; T is ready for owner acceptance and only then may its active generated build outputs be cleaned. |
| Original Owner Request | Audit and correct duplicate non-core paths, DOS/Win32 colour projections, VT capability architecture, code quality, cleanup and test closure. |
| Similar-Issue Sweep | Rebuild every changed target; inspect every `platform/` include boundary, text palette projection, Win32 console source inclusion and product artifact source timestamp. |

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
