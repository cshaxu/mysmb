# Project Status

## Current Work

## M3 T42 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T42 S1 P1 — DOS16 audio backend admission audit |
| Admission And Approval | Owner approved M3 T42 and directed S1 admission on 2026-10-12. |
| Objective | Establish the exact DOS16 platform-only route needed to consume the existing shared audio frame for music and effects in graphical and text modes. |
| Non-goals | No translated ROM/core/audio-command change; no Win32 change; no PC-speaker substitute; no imported driver, ROM asset or third-party source; no DOSBox configuration edit. |
| Reference Baseline | T41 closure `a85f5a13`; DOS root exports `mysmb_io_audio_frame` every tick and `mysmb_dos16_devices_audio` returns unavailable. |
| Candidate Proposal | [M3 T42 proposal](../proposals/m3/dos16-game-music.md). |
| Files And ABI Surface | Read-only initial scope: `src/io/audio.h`, `src/app/game_io.*`, `src/platform/dos16/main_dos16.c`, `dos16_root.*`, `devices.*`, current DOS build/test owners. Future implementation is constrained to `src/platform/dos16`. |
| Applicable Rules | Execution, Architecture, Coding, Documentation and source policy. |
| Verification | Static ownership/call-path audit; exact audio-frame contract inventory; DOS16 conventional-memory and interrupt/pacing ownership inventory; documented device/probe plan. |
| Expected Markers | One named device boundary, one synthesis owner, no platform header in core/app/io, and a bounded S2-S4 test matrix. |
| Asset Needs | Existing local product/source only; no new ROM, trace, third-party source or audio asset. |
| Reporting Requirements | Report actual frame path, silence point, proposed buffers/interrupt ownership, conventional-memory estimate, and exact future S boundaries before code changes. |
| Stop Conditions | Any need to alter original audio writes/order, dependency on a DOSBox setting, unbounded conventional-memory allocation, or a required imported driver/source. |
| Exit Criteria | A reviewable backend design and acceptance matrix identify the platform-only implementation route; no code or product artifact is changed by S1. |
| Original Owner Request | Implement DOS music support; graphical and text DOS modes currently have no music. |
| Similar-Issue Sweep | Inspect every DOS audio frame consumer, submit point, mode/reset path, timing gate, hardware/interrupt hook and audio-related allocation before proposing a backend. |

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
