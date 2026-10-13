# Project Status

## Current Work

## M3 T43 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T43 S6 P1 - Win16/Mine receiving seams |
| Admission And Approval | Owner approved the Mario-first S2-S7 sequence and automatic next-S admission. S5 has passed actual x86/x64 and DOS16 verification. |
| Objective | Define the Win16 callback/build seam and optional app-mine superbuild receiving interface, ready for a later provenance-reviewed import. |
| Non-goals | No Mine read/import, Win16 host implementation, Mario Win16 executable, game/PPU change, artwork change or input binding change. |
| Reference Baseline | S5: lib/kvm, lib/win32 and lib/dos16 expose neutral contracts/mechanics; Mario retains its controls and composition. |
| Candidate Proposal | [M3 T43 proposal](../proposals/m3/mygames-code-unification.md). |
| Files And ABI Surface | Neutral callback/capability declarations, lib/win16 interface target, optional app-mine root build seam, receiving documentation and owner-local contract tests. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Compile-contract tests, absent-Mine configure, dependency/purity scan, actual-width Win32 builds and documentation/ledger gates. |
| Expected Markers | Optional absent app builds cleanly; declarations contain no Mario rules; Win16 remains an explicitly unimplemented device; apps own all input/presentation meanings. |
| Asset Needs | None for new contracts. Existing owner-local product validation may use the admitted ROM without committing generated material. |
| Reporting Requirements | Report receiving targets, callback ownership, supported versus future capabilities and all remaining pre-import gates. |
| Stop Conditions | Mine material imported, fictitious Win16 runtime claim, host assigning app commands or reverse app dependencies in libraries. |
| Exit Criteria | The receiving interfaces compile, root build accepts an absent app-mine and ownership/verification are explicit for the later import. |
| Original Owner Request | Finish app-mario/lib separation before importing Mine; each app defines its keyboard and mouse semantics. |
| Similar-Issue Sweep | Check callback/capability declarations and build edges for application names, implicit key meaning, cross-app dependencies and unsupported platform claims. |

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
