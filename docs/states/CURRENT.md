# Project Status

## Current Work

## M3 T43 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T43 S1 P1 — MyGames monorepo architecture audit and design |
| Admission And Approval | Owner approved a new task to unify MySMB and Mine in this repository and requested an audit/design before source relocation or extraction. |
| Objective | Establish the exact ownership map and staged design for `app-mario`, `app-mine`, `lib/kvm`, `lib/dos16`, `lib/win16` and `lib/win32`. |
| Non-goals | No source import, directory relocation, application behavior change, ROM work, product build, executable refresh or third-party/code copy. |
| Reference Baseline | Closed M3 T42 products; current MySMB source and a read-only owner-managed Mine audit. |
| Candidate Proposal | [M3 T43 proposal](../proposals/m3/mygames-code-unification.md). |
| Files And ABI Surface | Proposal, active packet and zero-scope ledger only.  The proposed libraries are design targets, not present ABI. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Ledger validation, documentation governance, clean working tree and semantic review of each listed platform boundary. |
| Expected Markers | One clear owner for every shared candidate; no copied sibling source and no claimed Win16 Mario product. |
| Asset Needs | None.  Mine is read only during S1. |
| Reporting Requirements | Distinguish existing capability from target capability; identify which project supplies each missing capability. |
| Stop Conditions | Any import without an explicit Mine provenance/revision receipt, any game renderer moved into `lib/kvm`, or any host library choosing gameplay logic. |
| Exit Criteria | Committed design names the migration order, acceptance matrix, provenance gate and retained app boundaries; owner can approve S2 without reopening discovery. |
| Original Owner Request | Combine Mine and MySMB, extract shared DOS16/Win16/Win32/KVM integration, and close cross-project platform capability gaps. |
| Similar-Issue Sweep | Audit startup classification, borrowed/owned Console lifetime, Tab switching, VT/indexed colour, text cells, keyboard input, DOS B800 and Win16 windowing in both projects. |

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
