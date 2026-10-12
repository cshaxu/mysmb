# Project Status

## Current Work

## M3 T43 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T43 S3 P1 — `lib/kvm` neutral contracts |
| Admission And Approval | Owner approved the Mario-first restructure and specified that applications retain all keyboard and mouse semantics. |
| Objective | Extract portable presentation and lossless physical-event contracts into `lib/kvm` while retaining Mario command decisions in `app-mario`. |
| Non-goals | No Mine read/import; no Win32/DOS host extraction; no game binding, ROM/PPU, text-art, mouse or controller semantic change. |
| Reference Baseline | T43 S2 structural closure: `app-mario` root and three product targets compile from the root superbuild. |
| Candidate Proposal | [M3 T43 proposal](../proposals/m3/mygames-code-unification.md). |
| Files And ABI Surface | New `lib/kvm` CMake/include/source/test ownership plus `app-mario` include and target dependency updates. No app-facing input meaning becomes a library API. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Contract unit tests, owner/dependency scan, focused Mario text/launch tests, x86/x64 builds and DOS16 link when the moved source is linked there. |
| Expected Markers | KVM has no host/game includes; one owner per moved neutral contract; raw event payloads carry no Mario command; Mario performs conversion. |
| Asset Needs | None. No ROM, asset, disassembly, trace or Mine material enters the task. |
| Reporting Requirements | Report exact moved files, API surface, app-owned mapping boundary, test results and target matrix. |
| Stop Conditions | Any host API in KVM, app key/mouse semantic in KVM, duplicated compatibility owner, game-state/PPU decision in a library, or Mine import. |
| Exit Criteria | KVM contracts build as an independent target and Mario consumes them without a behaviour or semantic-binding change. |
| Original Owner Request | Combine Mine and MySMB through reusable DOS16/Win16/Win32/KVM infrastructure while leaving each app responsible for its own controls. |
| Similar-Issue Sweep | Scan library headers/sources and CMake dependency edges for Mario constants, Windows/DOS APIs, and duplicate former `io` contract owners. |

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
