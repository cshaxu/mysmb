# Project Status

## Current Work

## M3 T43 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T43 S7 P1 - Mario structural parity and import readiness |
| Admission And Approval | Owner approved the Mario-first S2-S7 sequence and automatic next-S admission. S5 has passed actual x86/x64 and DOS16 verification; S6 receiving contracts have passed native tests and DOS16 ABI compilation. |
| Objective | Verify the completed Mario/lib split, single shared owners, actual three-product bindings and readiness for a later provenance-reviewed Mine import. |
| Non-goals | No Mine read/import, Win16 host implementation, Mario Win16 executable, game/PPU change, artwork change or input binding change. |
| Reference Baseline | S5: lib/kvm, lib/win32 and lib/dos16 expose neutral contracts/mechanics; Mario retains its controls and composition. |
| Candidate Proposal | [M3 T43 proposal](../proposals/m3/mygames-code-unification.md). |
| Files And ABI Surface | All app-mario/lib build and dependency edges, existing product artifacts, receiving declarations, purity tests and final evidence. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Complete actual PE32/PE64 test matrices, product self-tests and headers, retained DOS MZ/device-probe checks, duplicate/dependency scan and documentation/ledger gates. |
| Expected Markers | Optional absent app builds cleanly; declarations contain no Mario rules; Win16 remains an explicitly unimplemented device; apps own all input/presentation meanings. |
| Asset Needs | None for new contracts. Existing owner-local product validation may use the admitted ROM without committing generated material. |
| Reporting Requirements | Report receiving targets, callback ownership, supported versus future capabilities and all remaining pre-import gates. |
| Stop Conditions | Mine material imported, fictitious Win16 runtime claim, host assigning app commands or reverse app dependencies in libraries. |
| Exit Criteria | Mario uses single shared host owners, the three local products retain verified bindings, and Mine import gates and all future capabilities are explicit. |
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
