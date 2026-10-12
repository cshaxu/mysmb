# Project Status

## Current Work

## M3 T41 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T41 S3 P10 — independent code-quality closure audit |
| Admission And Approval | Owner approved T41 on 2026-10-12; S1 closed in P1 `63b06b85` and S2 closed in P2 `8949fb51`. |
| Objective | Close T41 with complete x86/x64 unit and integration matrices, DOS16 compiler/link/product verification, platform-purity and documentation gates, refreshed local products for changed code, and a test-owner receipt. |
| Non-goals | No ROM/core/PPU/text-scene change; no terminal input query; no DOS graphics or process-topology change. |
| Reference Baseline | M3 T40 S3 P9, commit `46909575`; accepted CMD, graphical Tab and run16 corpus. |
| Candidate Proposal | [M3 T41 proposal](../proposals/m3/text-presentation-quality.md). |
| Files And ABI Surface | Existing T41 source owners and tests; local `assets/mysmb16.exe`, `assets/mysmb32.exe`, `assets/mysmb64.exe` only after each target validates. |
| Applicable Rules | Execution, Architecture, Coding, documentation governance and source policy. |
| Verification | Full x86/x64 build and 283-test CTest matrices; focused policy-owner test; DOS16 compiler/link and DOS product probe; all three product self-tests; platform-purity, ledger and documentation governance gates; product artifact hashes. |
| Expected Markers | 283/283 x86 and x64 tests; a linked DOS16 MZ executable; three fresh product artifacts; no platform leakage or unowned test path. |
| Asset Needs | Existing owner-local build inputs only; no new research or imported assets. |
| Reporting Requirements | Report changed owners, test-owner mapping, build results, artifacts after code changes, and build cleanup at acceptance. |
| Stop Conditions | Any core/PPU semantic difference, terminal query requirement, or inability to preserve the accepted three-route corpus. |
| Exit Criteria | All T41 acceptance criteria are evidenced; T is ready for owner acceptance and only then may its active generated build outputs be cleaned. |
| Original Owner Request | Audit and correct duplicate non-core paths, DOS/Win32 colour projections, VT capability architecture, code quality, cleanup and test closure. |
| Similar-Issue Sweep | Rebuild every changed target; inspect every `platform/` include boundary, text palette projection, Win32 console source inclusion and product artifact source timestamp. |

### S3 DOS16 evidence

The direct host `tools/dos16/link16.exe` and run16 attempts are not the
accepted DOS16 link route. The restored project route is OpenNT CL16 OMF,
`PrepareDosLink365Omf.py` bucketing, then the private DOSBox Microsoft
Segmented-Executable Linker 5.10. It compiled all 174 objects, linked a current
350,511-byte MZ executable, and passed `VerifyDos16Memory.py` with 49 segments,
52,624 DGROUP bytes, and a 387,520-byte page-rounded maximum load. The actual
product then passed the automated DOSBox0.74-3 I/O receipt: title, start,
right-run, jump, left-release, and Escape exit. The output hash is
`063fc4c06a6f9edc42393da0f7cbcccf254d75ce83119539d5dcc572f80a2f1d`.

The x86 and x64 matrices remain 283/283 passing. All three locally ignored
product artifacts were refreshed from those validated target outputs. S3 is
ready for owner acceptance; acceptance cleanup, rather than an invented linker
blocker, is the remaining lifecycle step.

### S3 host-integration ownership

The borrowed-console and text-switch fixtures cannot be ordinary CTest tests:
a normal CTest worker may be a ConPTY and lacks the classic Console contract
being verified. They are now bound to the named non-default
`mysmb_win32_host_integration` CMake target, which runs them through
`Verify-Win32StartupConsole.py` on a private desktop and stores receipts below
the build directory. P9 ran the target successfully: borrowed and detached
owned Console fixtures, six launch sources, and the interactive CMD
Tab-to-window-to-text-to-Escape return all passed. The fixture now distinguishes
the indexed Console API contract from VT output: exact RGB bytes belong to the
presentation owner-local test, while a VT host owns its restored viewport and
may lack classic maximize or system-menu capabilities. The ordinary x86/x64
CTest matrix remains 283 tests per width.

### P10 independent code-quality closure audit

The final independent source audit found no unresolved duplicate conversion or
unowned text-presentation test path. `src/text/layout.c` and
`src/text/background_scene.c` remain the scene-side users of the portable
NES-to-neutral-sixteen-colour projection in `io/color`; DOS B800 and Win32
indexed Console output then share `mysmb_io_color_text_attributes` exactly at
their separate physical device boundaries. RGB VT encodes those same neutral
frame slots and is not a third palette or game-side conversion.

The only production implementation inclusions in tests are the documented
composition-root fixtures: one DOS root and two Win32 roots. No
`text_console*.c` implementation is directly included by a test. A source
sweep found no TODO/FIXME/TEMP markers in `src/platform`, `src/io`, tests or
CMake. `git diff --check` passes. This audit changed no production code or
product artifact; the clean tracked state is commit `236d133f`. It completes
the review evidence, while preserving current generated P9 outputs solely
until owner acceptance triggers the mandatory cleanup.

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
