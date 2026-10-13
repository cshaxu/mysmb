# Project Status

## Current Work

## M3 T43 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T43 S5 P1 — `lib/dos16` host extraction |
| Admission And Approval | Owner approved the Mario-first restructure and specified that applications retain all keyboard and mouse semantics. S4 has completed its implementation closure. |
| Objective | Extract generic DOS16 bootstrap, raw physical input, B800 text device and timer ownership into `lib/dos16`, retaining Mario's game and VGA/PPU decisions in `app-mario`. |
| Non-goals | No Mine read/import, Win16 extraction, ROM/PPU change, text-art change, DOS graphics-compositor/sound move, or Mario key/mouse semantic change. |
| Reference Baseline | T43 S4 closure: `lib/win32` owns reusable Win32 host mechanics while Mario maps neutral KVM events to app commands. |
| Candidate Proposal | [M3 T43 proposal](../proposals/m3/mygames-code-unification.md). |
| Files And ABI Surface | New `lib/dos16` CMake/include/source/test ownership plus neutral KVM cell/event/timer interfaces. Mario's DOS composition root consumes the services and remains the sole mapper of app controls and selector of text/graphics. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | DOS16 library contracts, dependency/purity scan, KVM physical-event and indexed-cell adapter tests, Win32 regression builds, DOS16 Link 3.65 product link and applicable DOSBox I/O probe. |
| Expected Markers | DOS16 has no Mario constants or game state; it returns neutral KVM events and device results; Mario alone maps controls and calls its core/PPU/VGA compositor. |
| Asset Needs | None. No ROM, asset, disassembly, trace or Mine material enters the task. |
| Reporting Requirements | Report exact moved files, callback surface, app-owned mapping boundary, indexed-cell/physical-event results and target matrix. |
| Stop Conditions | Mario constants or game state in `lib/dos16`, an app command assigned by the library, duplicate old/new host owner, behavioural change, or Mine import. |
| Exit Criteria | `lib/dos16` is the single owner of its generic DOS host mechanics, Mario controls all command and presentation decisions, and all three products retain current behaviour. |
| Original Owner Request | Combine Mine and MySMB through reusable DOS16/Win16/Win32/KVM infrastructure while leaving each app responsible for its own controls. |
| Similar-Issue Sweep | Scan `lib/dos16` headers/sources and CMake dependency edges for Mario constants, controller commands, PPU/core access, duplicate host owners and text/graphics-selection special cases. |

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
