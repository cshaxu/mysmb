# Candidate: shared I/O contracts and operational graphic frames

Owner scheduling amendment (P153):remaining M2 acceptance verification is
queued after the three I/O/presentation candidates. Earlier proof completion
prerequisites are superseded by this explicit order;retain scoped evidence and
rebind affected dependencies at admission. This does not certify M2.

## Purpose and queue status

The owner wants one portable I/O boundary for controller input, video output,
and ordered music/sound output. `src/io` will own the host-neutral contracts
and reusable frame conversions; `src/platform` will own DOS16 and Win32 entry
points, timing, device access, and mode transitions. This is the first
unnumbered cross-host I/O candidate in the queue. Its S slots below are a forecast, not
admitted work or ROM-node completion credit.

The canonical video frame is the game's 256x240 indexed PPU result. The text
frame contract reserves 80x50 cells, but this candidate supplies only a
placeholder, not a playable ASCII scene. It does not deliver a graphics/text
mode switch on either host. The later queued text-frame candidate owns both
the colored ASCII game picture and DOS16/Win32 bidirectional graphics-to-text
switching. This candidate concentrates on a correct graphical path and a
normally running DOS16 executable.

## Current baseline and ownership

- `src/game/ppu_frame.h` already declares the 256x240 PPU frame. `game.h`
  declares decoded controller input and ordered APU writes. Keep translated
  game state and ROM semantics in `game/`; do not move original RAM or APU
  register ownership merely to make a new directory.
- `src/platform/text` currently converts PPU pixels to 80x25 cells.
  `src/platform/vga` converts them to a 320x200, five-index DOS-facing frame
  with four 16,000-byte pages. Neither representation may replace or reduce
  the canonical 256x240 video frame.
- The DOS16 root builds both presentation frames every tick and invokes both
  hooks. Its host selects the visible path with F1, but currently resets BIOS
  video mode on every present call. The text path still selects mode 3 and
  writes 80x25 cells. The current DOS executable needs an operational repair
  and real runtime verification, not just another successful link.
- Win32 currently presents the PPU frame directly through a GUI DIB, polls
  physical keys, and sends ordered APU output to its waveOut renderer. The
  audio adapter accepts the whole `mysmb_game`; the new boundary should expose
  only the output data it needs. Existing audio and pause behavior are
  preservation requirements.

## Target dependency boundary

```text
game: translated state and one logical tick
   -> io: decoded input, canonical graphic frame, ordered audio output contracts
   -> platform: Win32 GUI and DOS16 graphic input, presentation, audio, timing
```

The arrows describe data flow, not permission for `game/` to include host
headers or call platform functions. `src/io` exposes bounded, C90-compatible
types and pure conversions; it owns no Win32 handles, DOS interrupts, mutable
original RAM, or physical audio device. A platform composition root connects
the game to selected adapters. Keep the PPU compositor's game-visible output
semantics intact and move definitions only where that does not obscure ROM
provenance or create a circular dependency. Share controller mapping and
frame/audio submission contracts where they are genuinely identical; keep
host-specific keyboard decoding, console drawing, DIB drawing, BIOS/VBE mode
selection, and sound-device writes in the platform adapters.

`video_frame` remains 256x240 with the source color indices. Win32 GUI maps
those indices to display colors without passing through the current lossy VGA
frame. DOS16 graphics converts or scales that canonical frame to a supported
video mode; mode 13h is the initial baseline. The common 80x50 `text_frame`
type may be reserved as an inert placeholder, but neither a text renderer nor
a mode-switch user flow is accepted here. Translating game visuals into colored
ASCII cells is explicitly out of scope. VGA-specific storage and palette conversion remain an adapter
detail, even if their pure portions live under `src/io`. Audio output is an ordered per-tick APU write/snapshot contract,
not an invented music-note stream; a platform may report unsupported hardware
without silently replacing or mutating the game command stream.

## Planned S decomposition

| Planned S | Bounded deliverable | ROM-node scope / expected new matches |
| --- | --- | --- |
| S1 | Specify and introduce the portable `src/io` input, 256x240 graphic frame, ordered audio, and 80x50 text-placeholder contracts; prove C90 and 16-bit-safe ownership/dependency direction. | 0 / 0 |
| S2 | Migrate Win32 GUI input, PPU presentation, and existing waveOut audio to the contract without changing visible frames, sound, pause behavior, or x86/x64 output. | 0 / 0 |
| S3 | Adapt DOS16 graphics output, startup, keyboard, frame timing, and video-mode setup to the I/O contract; diagnose and repair actual runtime hangs or display failures so the graphical game can run normally. | 0 / 0 |
| S4 | Stabilize DOS16 graphical video-mode setup, frame presentation, input timing, audio capability reporting, and safe shutdown; keep the reserved text-frame interface inert and compatible with the later switching task. | 0 / 0 |
| S5 | Exercise DOS16 in an actual graphics-capable DOS runtime from boot/title through Start and sustained gameplay; repair observed input, rendering, timing, and exit failures rather than treating compile/link or Run16 alone as operational proof. | 0 / 0 |
| S6 | Run integrated DOS16 and Win32 x86/x64 graphic-frame, audio-continuity, focus/pause, and cross-build checks; close remaining boundary leaks and report any explicitly deferred hardware capability. | 0 / 0 |

At admission, rebase the current repository and active packet, register each
infrastructure S in the node/task ledger with exact empty node scope and zero
expected matches, and choose its focused tests. This candidate claims no
original-ROM node or graph-edge credit. A discovered translated-logic mismatch
requires a separately scoped corrective owner and proof; this I/O migration
must not change game semantics to make an adapter test pass.

## Acceptance

1. Win32 GUI and DOS16 graphics consume the same logical 256x240 game frame;
   neither host changes game logic or audio-write order to adapt the graphics
   output. The text placeholder is an interface boundary, not a user-visible
   game mode or a requirement to switch displays.
2. Win32 remains a working GUI application on x86 and x64, preserving current
   focus/pause, keyboard, visual, and audio behavior. Console creation and
   bidirectional switching belong to the later text-frame task.
3. DOS16 retains a single executable. Its
   graphics baseline uses a supported mode without assuming the monitor's
   desktop resolution. It does not reprogram the BIOS mode every frame or
   write to an unavailable mode's buffer. In a graphics-capable DOS runtime,
   the executable boots, shows title and gameplay, accepts controls, advances
   frames without hanging, and exits safely. A DOS16 link,
   self-test, or Run16-only result cannot satisfy this operational criterion.
4. Win32 x86/x64 existing audio remains correct in the graphical view. The I/O contract preserves the order of same-value APU
   retriggers. DOS16 audio hardware support is recorded as a separate
   capability where absent; creating this boundary does not claim sound that
   the DOS host does not produce.
5. Focused graphic-frame and interface tests, Win32 x86/x64 builds and
   self-tests, the real DOS16 link, and the DOS16 interactive gameplay route
   all pass. The later text-frame task owns ASCII glyph choice, color mapping,
   scene legibility, 80x50 playability, and runtime presentation switching.
   Verify dependency direction and a similar-issue sweep for every platform
   path that reads game internals directly or resets output devices per frame.

## Constraints and handoff

Preserve retained current-equivalence evidence. Before this T is admitted, reconcile its focus policy
with the then-current Win32 implementation; do not duplicate or bypass an
already accepted focus/pause owner. Keep owner-local ROM material, generated
program data, binaries, traces, and temporary build products out of tracked
sources. The admission packet will define the exact source files, evidence,
artifact refresh, and S order against the then-current baseline.
