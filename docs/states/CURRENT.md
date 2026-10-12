# Project Status

## Current Work

## M3 T42 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T42 S3 P3 — integer NES-frame PCM synthesis and Sound Blaster submission |
| Admission And Approval | Owner approved M3 T42; this P3 closes S2 and admits S3. |
| Objective | Consume every unchanged shared audio frame exactly once in a DOS16 integer renderer, fill the already bounded PCM blocks, and activate DMA/IRQ only after a full starter block exists. |
| Non-goals | No translated ROM/core/audio-command change; no Win32 renderer reuse; no floating point; no PC-speaker substitute; no imported driver, ROM asset or third-party source; no DOSBox configuration edit. |
| Reference Baseline | S2 receipt: the DOS binding parses/probes BLASTER and reserves 4096 bytes but still returns unavailable because no PCM/DMA/IRQ owner exists. |
| Candidate Proposal | [M3 T42 proposal](../proposals/m3/dos16-game-music.md). |
| Files And ABI Surface | `src/platform/dos16/dos_audio.*`, `devices.*`, platform-local tests and DOS build owner. The shared `mysmb_io_audio_frame` ABI stays read-only. |
| Applicable Rules | Execution, Architecture, Coding, Documentation and source policy. |
| Verification | Owner-local integer render/write-order, silence and start/rollback tests; DOS16 link; existing DOSBox Sound Blaster route; platform-purity and source-boundary review. |
| Expected Markers | Ordered repeated-write retention, 60Hz→11025Hz integer cadence, bounded 2×2 KiB blocks, DMA/IRQ startup only after a full block, restored vector/DMA state on every failure path, and no audio lifecycle event on Tab. |
| Asset Needs | Existing local product/source and existing DOSBox installation only; no new ROM, trace, third-party source or audio asset. |
| Reporting Requirements | Report sample/block geometry, exact conventional-memory delta, DMA/IRQ rollback coverage, audio-frame ordering proof and audible/deferred boundary. |
| Stop Conditions | Any need to alter original audio writes/order, dependency on a DOSBox setting, unbounded conventional-memory allocation, or a required imported driver/source. |
| Exit Criteria | The platform returns available only when it submits PCM from the unchanged frame; all startup/close/failure paths preserve game/video behavior and remain bounded. |
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
