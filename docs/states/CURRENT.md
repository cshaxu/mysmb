# Project Status

## Current Work

## M3 T43 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T43 S4 P1 — `lib/win32` host extraction |
| Admission And Approval | Owner approved the Mario-first restructure and specified that applications retain all keyboard and mouse semantics. |
| Objective | Extract generic Win32/x64 host ownership into `lib/win32`, with Mario retaining command mapping and view decisions. |
| Non-goals | No Mine read/import, Win16/DOS extraction, ROM/PPU change, text-art change, or Mario key/mouse semantic change. |
| Reference Baseline | T43 S3 closure: `lib/kvm` owns neutral presentation/physical-event contracts and the three Mario products build. |
| Candidate Proposal | [M3 T43 proposal](../proposals/m3/mygames-code-unification.md). |
| Files And ABI Surface | New `lib/win32` CMake/include/source/test ownership plus a narrow Mario host callback that consumes KVM physical events and app-requested presentation. No app command becomes a library API. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Library contracts, dependency/purity scan, borrowed/owned Console lifecycle tests, VT/indexed tests, raw-event-to-Mario adapter test, x86/x64 builds and DOS16 link. |
| Expected Markers | Win32 has no Mario constants or game state; it returns only KVM events and presentation results; Mario alone performs conversion and calls its own core/PPU. |
| Asset Needs | None. No ROM, asset, disassembly, trace or Mine material enters the task. |
| Reporting Requirements | Report exact moved files, callback surface, app-owned mapping boundary, lifecycle/colour test results and target matrix. |
| Stop Conditions | Mario constants or game state in `lib/win32`, an app command assigned by the library, duplicate old/new host owner, behavioural change, or Mine import. |
| Exit Criteria | `lib/win32` is the single Win32 host owner, Mario controls all command decisions, and all three products retain current behaviour. |
| Original Owner Request | Combine Mine and MySMB through reusable DOS16/Win16/Win32/KVM infrastructure while leaving each app responsible for its own controls. |
| Similar-Issue Sweep | Scan `lib/win32` headers/sources and CMake dependency edges for Mario constants, controller commands, PPU/core access, duplicate host owners and shell/process-name special cases. |

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
