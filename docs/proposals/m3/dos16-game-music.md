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

#### S1 closure receipt

The current call path is exact and complete: `mysmb_dos16_root_step` calls
`mysmb_game_io_audio` after every logical `mysmb_game_tick`, then invokes the
composition hook; `main_dos16.c` delegates that hook to
`mysmb_dos16_devices_audio`. The latter is the only DOS physical consumer and
currently discards the frame. It is invoked after the optional video gate, so
stale graphical frames can be dropped without dropping audio state. Text mode
only changes the video device; it neither stops nor reinitializes the audio
hook.

The selected backend is an integer, Sound Blaster-compatible 8-bit PCM device
configured solely from the standard `BLASTER` fields for base I/O, IRQ and
8-bit DMA channel. It will use a bounded 11,025 Hz mono DMA ring: two
individually DMA-safe 2 KiB blocks plus a sub-1 KiB renderer/device state,
for a maximum new conventional-memory payload of 5 KiB before allocator
metadata. Blocks are allocated at open, never during a game tick or interrupt;
the IRQ handler only acknowledges the DSP/PIC and selects a prebuilt block.
The foreground platform consumer advances the integer NES synthesis state from
each ordered frame and fills a block before it is handed to DMA. The renderer
uses a 60 Hz to 11,025 Hz fractional sample accumulator, so it does not couple
audio cadence to graphics publication.

`devices_open`/`devices_close` own device open, vector restoration and DMA
shutdown; `devices_mode` must remain video-only. `devices_after_load` needs a
platform reset/resynchronization hook so a restored frame cannot leave a stale
DMA waveform playing. A missing or malformed `BLASTER`, failed DSP reset, DMA
allocation failure or incomplete setup remains nonfatal and returns the
existing unavailable capability. No core, app, IO contract or Win32 renderer
needs alteration. DOSBox validation will use its existing configured Sound
Blaster device; this task does not edit emulator settings.

### S2 — DOS16 Sound Blaster device lifecycle

Implement platform-only BLASTER parsing/probe, DSP reset, fixed DMA-buffer
reservation and idempotent shutdown. Actual DMA programming and IRQ ownership
begin only once S3 has PCM blocks to submit; reserving the future blocks first
keeps this setup phase safe and independently testable. A focused device test
must prove parsing, absent-device fallback and rollback after every present
setup phase. Graphical/text switches leave the prepared device untouched.

#### S2 closure receipt

`platform/dos16/dos_audio.*` now separates a portable, testable lifecycle
state machine from the DOS physical binding. It accepts one `BLASTER` value
with exactly one valid `A` (hex base I/O), `I` (IRQ), and `D` (8-bit DMA)
field, ignores unrelated standard fields such as `T`, probes the DSP reset
handshake, and reserves exactly 256 paragraphs (4096 bytes) through DOS
allocation. `devices_open`, `devices_close`, and `devices_after_load` own
open, idempotent release, and loss-safe reprobe. `devices_mode` remains
strictly video-only, so graphical/text switching cannot reopen, reset, or
reallocate audio.

The OpenNT startup policy rejects CRT `getenv`; the physical binder therefore
obtains the process PSP through DOS `AH=62h` and copies only `BLASTER` to a
bounded 128-byte buffer. This avoids a CRT startup-vector dependency. The
platform still returns unavailable for frames: S2 has no PCM, DMA transfer or
IRQ handler and does not claim audible output. The owner-local unit test covers
valid/malformed configuration, probe loss, allocation rollback and idempotent
close. Focused x86/x64 tests, platform purity, OpenNT compilation and the DOS
LINK 3.65 MZ route passed. The actual DOS image reports a 377,376-byte minimum
load and a 4,096-byte initial near heap reserve; the 4,096-byte future audio
allocation is a dynamic far-heap cost and is not included in that loader
receipt.

### S3 — Integer NES-frame synthesis and submission

Implement the DOS16 integer synthesis owner that consumes each unchanged
`mysmb_io_audio_frame` exactly once, preserves repeated source writes, and
fills the two reserved DMA blocks without heap allocation during gameplay.
This S activates DMA/IRQ ownership only after a complete silent starter block
exists, and restores the prior vector/DMAs on every partial startup failure.
Unit tests
compare register/write consumption, pause/silence and event priority against
the shared frame contract; no game-side timing changes are allowed.

**Closure receipt.** S3 adds a platform-local 11,025 Hz integer renderer.  It
consumes every source-order write, including repeated register writes, and
uses a remainder accumulator so sixty NES ticks produce exactly 11,025
samples.  PCM is accumulated into two fixed 2 KiB far-memory blocks; the
first DSP transfer is armed only after a full block is ready.  The device path
programs DMA before the DSP transfer command, restores the prior interrupt
vector on close or failed reprobe, masks DMA before release, and rejects the
AT cascade DMA channel.  It adds a 4,096-byte dynamic far allocation and
about 0.4 KiB of fixed near state (renderer and staging samples), with no
allocation in the frame path.  Focused x86/x64 tests pass, as do platform
purity and the actual OpenNT/DOS LINK 3.65 MZ build.  Audible hardware
validation is deliberately deferred to S4.

### S4 — Integrated DOS music route

Bind the backend to the DOS root and validate title music, gameplay music,
jump/coin/enemy sound effects, pause, text/graphics Tab switching, save/load
reset and Escape teardown. Run the normal DOS16 link, DOSBox Sound Blaster
route, applicable Windows regressions and all three product builds for code
changes. Hardware absence must leave a playable silent game without changing
logical audio state.

**P5 route receipt (in progress).** The installed, unmodified DOSBox 0.74-3
configuration exposes `BLASTER=A220 I7 D1 H5 T6`, which selects the supported
8-bit DMA route.  The new MZ image completes its OpenNT/DOS LINK 3.65 build
and remains live through a five-second title-route smoke run under that
configuration.  The smoke result proves device discovery and startup do not
terminate the game; it is not presented as an audible title/effect result.
The audible title/gameplay, text/graphics transition, load and Escape corpus
remains S4's open acceptance work.

**P6 environment-route correction (in progress).** The P5 startup result did
not prove that the DOS process found `BLASTER`.  The physical binder had read
the PSP segment returned by DOS `AH=62h` as though it were the environment
segment.  In the DOS PSP, the environment segment is the word at `PSP:002Ch`.
The binder now follows that word before copying the bounded `BLASTER` value;
the old code therefore selected the silent no-device fallback on ordinary DOS
hosts.  The corrected MZ image passes its DOS LINK 3.65 build and the focused
x86/x64 audio/root tests.  A read-only review of the run16/NTVDM64 production
sources finds no configured Sound Blaster device or VDD binding; its only
Sound Blaster implementation is the excluded `vdd/samples/vsbd` sample.
Consequently run16 currently cannot provide the DSP/DMA/IRQ hardware that this
Sound Blaster route requires.  It remains a valid silent-fallback witness, but
not an audible SB acceptance host.  DOSBox or real SB-compatible DOS hardware
is required for this S4 route until NTVDM64 separately admits a sound-device
provider.

**P7 physical interrupt-route correction (in progress).** A target-built
probe now follows the same `BLASTER` discovery, renderer, DSP, DMA and IRQ
path as the product.  The corrected environment lookup opened DOSBox's DSP,
but the first full PCM block still exhausted both DMA buffers: the driver had
installed the IRQ vector without unmasking the configured PIC line.  The
backend now preserves the master/slave masks, enables the selected IRQ (and
the master IRQ2 cascade for a slave IRQ), and restores both masks before it
releases the vector and DMA storage.  The default unmodified DOSBox SB16
route now returns `BLASTER-DSP-DMA-IRQ` after two seconds of paced source-frame
submissions.  This is a real device-route witness; audible title/effect and
presenter transition acceptance remain open.

**P8 source-audio join receipt (in progress).** `dos16_death_audio_smoke`
now drives a real translated game audio route through `mysmb_audio_step`, its
unchanged `mysmb_game_io_audio` frame, and the DOS integer renderer.  It
proves expected non-silent/dead intervals across 180 source frames, while the
separate DOSBox device witness proves that the same renderer's samples reach
the DSP/DMA/IRQ sink.  The focused DOS audio, root and source-audio joins pass
on both x86 and x64.  The remaining manual acceptance is audible title and
effect playback in both DOS presenters, plus transition/load/Escape checks.

**P9 physical load-reset receipt (in progress).** The target device witness
now invokes the same `mysmb_dos16_audio_dos_after_load` boundary used by the
DOS root halfway through its paced DMA route.  It stops the active transfer,
re-probes the DSP, resets only adapter-owned synthesis/buffer state, and then
continues to receive DMA IRQs through the unchanged shared source sequence.
The unmodified default DOSBox SB16 route again returns
`BLASTER-DSP-DMA-IRQ`.  This closes the device side of save/load recovery;
audible presenter and Escape acceptance remain manual S4 evidence.

**P10 run16 host-limit receipt (in progress).** Owner testing of
`run16 mysmb16.exe` produced no audible output. This is the expected
no-device path, not a regression in the DOS Sound Blaster route: the
read-only NTVDM64 production tree has no registered Sound Blaster VDD or
DSP/DMA/IRQ provider. Its `vdd/samples/vsbd` directory is an excluded sample,
not a loaded production device. MySMB therefore neither finds a `BLASTER`
endpoint nor touches unprovided hardware, and remains silently playable.
`run16` is retained as the required no-device fallback witness; DOSBox or
physical Sound Blaster-compatible DOS hardware remains the audible acceptance
host. Making run16 audible requires a separately admitted NTVDM64 task to
provide and register a Sound Blaster-compatible virtual device; it cannot be
correctly implemented by adding a MySMB-only special case.

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
