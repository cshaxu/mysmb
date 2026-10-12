# M3 T42: DOS16 game music

## Objective

Make the existing translated SMB audio stream audible in the DOS16 product in
both graphical and text presentation modes. The same logical ticks, ordered
APU writes, music/sound-effect priority and pause behavior already consumed by
Win32 remain the sole game-audio truth.

## Current fact

`mysmb_dos16_root_step` exports one `mysmb_io_audio_frame` after every game
tick, including the final register image and source-ordered repeated writes.
The DOS composition root submits that frame to `mysmb_dos16_devices_audio`.
That device currently discards it and returns `MYSMB_IO_AUDIO_UNAVAILABLE`.
This is a DOS platform-output gap, not a missing ROM music routine or a
graphics/text mode distinction.

## Boundaries

- `src/core`, `src/app` and `src/io/audio.h` preserve current values, ordering
  and per-tick ownership. No DOS conditional enters translated game logic.
- New physical synthesis, DOS hardware discovery, DMA/IRQ service and teardown
  belong exclusively to `src/platform/dos16`.
- The backend must continue ticking while graphical presentation is dropped or
  text mode is active. Tab switches video/text presentation only; it does not
  restart music or discard a pending sound effect.
- The initial target is a conventional Sound Blaster-compatible DSP route
  selected from the standard DOS environment/device probe. Absence or failed
  initialization remains a silent, nonfatal platform capability; no PC speaker
  approximation is presented as SMB music.
- No third-party source, ROM asset, audio recording, driver binary or emulator
  configuration is imported. All generated probes/logs stay below `build/`.

## Planned S tasks

### S1 — DOS audio backend admission audit

Trace the actual shared audio frame through the DOS root, inventory the current
DOS16 memory/interrupt/pacing ownership, and define the Sound Blaster DSP
backend ABI: discovery inputs, fixed buffers, IRQ/DMA lifetime, mixer cadence,
failure behavior and shutdown. Compare its required integer synthesis state
with the existing Win32 renderer only as an internal behavioral reference; do
not copy floating-point or Win32 device code. Produce a bounded source and
probe plan with explicit conventional-memory budget before implementation.

### S2 — DOS16 Sound Blaster device lifecycle

Implement platform-only BLASTER parsing/probe, DSP reset, DMA/IRQ setup and
idempotent shutdown. A focused device test must prove parsing, absent-device
fallback, rollback after every failed setup phase, and that graphical/text
switches leave a ready device alive.

### S3 — Integer NES-frame synthesis and submission

Implement the DOS16 integer synthesis owner that consumes each unchanged
`mysmb_io_audio_frame` exactly once, preserves repeated source writes, and
fills fixed DMA blocks without heap allocation during gameplay. Unit tests
compare register/write consumption, pause/silence and event priority against
the shared frame contract; no game-side timing changes are allowed.

### S4 — Integrated DOS music route

Bind the backend to the DOS root and validate title music, gameplay music,
jump/coin/enemy sound effects, pause, text/graphics Tab switching, save/load
reset and Escape teardown. Run the normal DOS16 link, DOSBox Sound Blaster
route, applicable Windows regressions and all three product builds for code
changes. Hardware absence must leave a playable silent game without changing
logical audio state.

## Acceptance

1. A detected Sound Blaster-compatible DOS device plays music and effects in
   both DOS presenters from the unchanged shared audio frame.
2. Video/text switching, dropped video presentation and load/reset do not
   alter game audio order or spuriously restart the device.
3. Failure or absence of the device is safe, silent and leak-free.
4. The implementation uses fixed, bounded DOS16 state and reports its
   conventional-memory cost; it adds no core/platform cross-dependency.
5. Every changed platform decision has one owner-local test plus real DOS
   device-route evidence. Code changes refresh validated 16/32/64 artifacts.
