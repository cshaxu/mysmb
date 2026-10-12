# Project Status

## Current Work

## M3 T43 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T43 S2 P1 — Mario-only structural baseline |
| Admission And Approval | Owner approved execution after accepting the app-owned input boundary and Mario-first sequence. |
| Objective | Move the complete existing MySMB application source and project-owned tests beneath `app-mario`, with a root superbuild that preserves the current target matrix. |
| Non-goals | No Mine read/import, `lib` behavioral extraction, C logic modification, ROM/resource change, input-binding change, executable behavior change or new Win16 target. |
| Reference Baseline | T43 S1 architecture receipt and the pre-move MySMB CMake target/source inventory. |
| Candidate Proposal | [M3 T43 proposal](../proposals/m3/mygames-code-unification.md). |
| Files And ABI Surface | Root `CMakeLists.txt`, `app-mario/CMakeLists.txt`, moved `app-mario/src` and `app-mario/test`, plus build scripts whose source/test root is explicit. No public header/ABI change. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Source inventory comparison, root CMake configure, focused CTest, Win32 x86/x64 builds, OpenNT DOS16 build, platform-purity test, ledger and documentation governance. |
| Expected Markers | No root `src` or `test`; all Mario targets resolve below `app-mario`; root configure remains stable; generated outputs stay ignored. |
| Asset Needs | Existing owner-local ROM is used only by already configured local build paths; no asset is moved or committed. |
| Reporting Requirements | Report moved source/test counts, unchanged product target names, each build result and any tool path migrated. |
| Stop Conditions | Any Mine import/read beyond S1, behavior-affecting source edit, duplicated compatibility source tree, or need to change a game input/PPU decision to make the move build. |
| Exit Criteria | The Mario source/test tree has one `app-mario` owner; all three existing product build routes and focused tests pass from the root superbuild. |
| Original Owner Request | Combine Mine and MySMB, extract shared DOS16/Win16/Win32/KVM integration, and close cross-project platform capability gaps. |
| Similar-Issue Sweep | Search every CMake and project tool source/test root reference; retain only explicit app ownership or a root tool reference, never a stale root `src`/`test` path. |

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
| T42 | DOS Sound Blaster backend closes: unchanged shared frames feed the DOS16 integer renderer, DSP/DMA/IRQ route, and actual DOSBox product PCM capture. DOSBox host sound output remained unavailable in the owner's environment, while run16 is a documented no-device host. [History](../history/M3-T42-dos16-game-music.md). |
| T41 | Text-presentation quality closes: shared DOS/Win32 indexed colour projection, bounded conservative Win32 RGB VT presentation, owner-local tests and private-desktop host integration. x86/x64 283-test matrices and DOS16 link/I/O evidence passed; owner accepted and generated build outputs were removed. [History](../history/M3-T41-text-presentation-quality.md). |
| T40 | Win32 console-session identity and capability presentation close with owner-accepted CMD, graphical-Tab and run16 corpus. Normal/visible devices retain RGB VT; the hidden 2x4 carrier uses the stable standard-colour projection. Zero ROM nodes and edges. [History](../history/M3-T40-win32-console-session-identity.md). |
