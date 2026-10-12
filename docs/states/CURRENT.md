# Project Status

## Current Work

## M3 T42 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T42 S4 P14 — owner-accepted closure and cleanup |
| Admission And Approval | Owner approved T42 and directed closure of the current S after P13 evidence. |
| Objective | Archive the completed DOS Sound Blaster route, record the host-output limit accurately, and remove active generated outputs. |
| Non-goals | No production code, ROM/core/audio semantics, DOSBox configuration, external driver, or host-audio repair. |
| Reference Baseline | P12 product DMA reservation and P13 actual-product DOSBox PCM capture. |
| Candidate Proposal | [M3 T42 proposal](../proposals/m3/dos16-game-music.md). |
| Files And ABI Surface | Closure documentation and ledger only; the shared audio ABI remains unchanged. |
| Applicable Rules | Execution, Documentation and source policy. |
| Verification | Ledger validation, documentation governance gate, clean diff, and absent active task outputs. |
| Expected Markers | Closed S4/T42, retained factual evidence, and no `build/t42-s4` artifacts. |
| Asset Needs | None. |
| Reporting Requirements | State the product-PCM proof separately from unavailable host audibility. |
| Stop Conditions | Any claim that the local DOSBox/RDP host listening check passed. |
| Exit Criteria | Historical record and ledger are closed; generated task output is removed. |
| Original Owner Request | Implement DOS music support; graphical and text DOS modes currently have no music. |
| Similar-Issue Sweep | Close the product allocation, device route, source-frame and host-output evidence as separate dispositions. |

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
