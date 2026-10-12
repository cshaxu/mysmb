# Project Status

## Current Work

## M3 T42 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T42 S4 P8 — integrated DOS music route |
| Admission And Approval | Owner approved M3 T42; P5 closed S3 and admitted S4. P6–P8 are corrective/evidence parts within S4. |
| Objective | Validate the completed DOS Sound Blaster route in both presenters and prove that music/effects, load/reset and teardown preserve shared game/audio semantics. |
| Non-goals | No translated ROM/core/audio-command change; no Win32 renderer reuse; no floating point; no PC-speaker substitute; no imported driver, ROM asset or third-party source; no DOSBox configuration edit. |
| Reference Baseline | P6 corrected PSP-to-environment discovery; P7 proves the DOSBox SB16 physical route; P8 proves translated source audio reaches the DOS renderer. |
| Candidate Proposal | [M3 T42 proposal](../proposals/m3/dos16-game-music.md). |
| Files And ABI Surface | DOS launcher/route evidence, `src/platform/dos16/dos_audio.*`, `devices.*`, platform-local tests and DOS build owner. The shared `mysmb_io_audio_frame` ABI stays read-only. |
| Applicable Rules | Execution, Architecture, Coding, Documentation and source policy. |
| Verification | Existing unit and DOS16-link evidence, real DOSBox Sound Blaster route, title/gameplay effect markers, pause/load/Tab/Escape transitions and platform-purity review. |
| Expected Markers | Audible title/gameplay/effect route, safe silent no-device fallback, restored vector/DMA state on Escape, and no audio lifecycle event on Tab. |
| Asset Needs | Existing local product/source and existing DOSBox installation only; no new ROM, trace, third-party source or audio asset. |
| Reporting Requirements | Report device-route corpus, observed audible markers, no-device behaviour, fixed conventional-memory cost and any remaining host-only limit. |
| Stop Conditions | Any need to alter original audio writes/order, dependency on a DOSBox setting, unbounded conventional-memory allocation, or a required imported driver/source. |
| Exit Criteria | A detected Sound Blaster-compatible DOS device plays music/effects in both presenters; absence is silent and playable; teardown/reset never leaves IRQ/DMA state active. |
| Original Owner Request | Implement DOS music support; graphical and text DOS modes currently have no music. |
| Similar-Issue Sweep | Inspect all DOS vector, PIC, DMA, DSP, environment-parser, mode/reset and close paths; ensure no graphics/text transition opens, closes or reallocates audio hardware. |

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
| T41 | Text-presentation quality closes: shared DOS/Win32 indexed colour projection, bounded conservative Win32 RGB VT presentation, owner-local tests and private-desktop host integration. x86/x64 283-test matrices and DOS16 link/I/O evidence passed; owner accepted and generated build outputs were removed. [History](../history/M3-T41-text-presentation-quality.md). |
| T40 | Win32 console-session identity and capability presentation close with owner-accepted CMD, graphical-Tab and run16 corpus. Normal/visible devices retain RGB VT; the hidden 2x4 carrier uses the stable standard-colour projection. Zero ROM nodes and edges. [History](../history/M3-T40-win32-console-session-identity.md). |
