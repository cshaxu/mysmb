# M3 T9: shared I/O contracts and operational graphic frames

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

## T9 admission and S1 plan

Owner admits T9 and authorizes sequential automatic S admissions,each with
advance component/scope/size brief and post-closure build/test/commit/push
report. Single executor/coordinator roles;no delegated agent. S1 active;
S2-S6 planned only. No configured remote:local commits proceed,push unavailable
until a remote is supplied;never invent one.

S1 introduces io-only C90 types for two controller ports,read-only256x240
indexed video,ordered per-tick APU writes/snapshot,and inert80x50 text cells.
Do not move original RAM/compositor/audio logic or introduce host headers.
Expected8-12 source/build files,250-450 lines plus governance records.
Focused contract checks/C90 compile at x86/x64 and actual OpenNT16 compile;
three current products compile/link and focused existing frame/audio/pause
regressions. Exact ROM-node scope[],expectedMatches[],credit0;historical
baseline1992/1992 unchanged,local1991/1992 nodes/4260/4261 feasible controls.
Any changed dependency identity is recorded for deferred M2 rebinding,not
silently blessed as an unchanged full certificate.

## S1 P1 closure - portable contracts

Delivered4 IO headers,one cross-boundary ABI probe,CMake test registration,
real OpenNT16 probe compile hook and IO dependency purity checks.
Actual8 source/build files,+184/-1 lines;estimate8-12 files/250-450
lines was conservative. Architecture/source layout records updated separately.
Executor verified C90 byte/word widths,61440-byte far view,4000 text cells,
two controller ports and ordered repeated audio writes. Coordinator review
confirms IO imports only IO headers and no translated RAM or host APIs.
Current compositor/game logic and Win32/DOS device paths are unchanged.

x86/x64 each6 exact tests passed:contract,PPU frame,focus pause,audio renderer,
purity and native product self-test. Real OpenNT16 /AL contract probe compile
and full product link pass. Existing linker OLDNAMES library warning remains;
link completes and this receipt does not certify runtime graphics or audio.
S3-S5 must deliver actual DOS graphical play. Initial scoped-runner selection
rejected unbuilt test commands;built exact targets then accepted only complete
six-test reports. Enum compatibility comparisons use explicit byte values.

Three products published locally:16=260011bytes,
32=368377bytes,64=380216bytes.
Neutral identities retained below ignored build. No protected outputs staged.
Build-only CMake identity update records additive test registration;production
source/flags unchanged and retained semantic dispositions not promoted.
Historical1992/1992/local1991/1992 nodes,4260/4261 feasible controls unchanged.
S1 original scope/expected/actual matches all[];0 new nodes/controls.
Registry/ledger and documentation gates required for closure. No configured
remote:local commit deliverable,unavailable push reported without inventing URL.
Owner authorizes automatic S2 admission following this reviewed S1 commit.

## S2 admission - Win32 contract consumers

Automatically admitted after S1 commit ada029c3 under owner authorization.
Single executor/coordinator roles. Expected8-12 source/test files,250-400
changed lines. Scope:Win32 composition root controller/video/audio export,
audio_output and audio_renderer contract signatures,focused audio regressions
and any required root-boundary test/build registration. No game semantic or
DOS device edit. Keep waveOut synthesis/sample count,same-value retriggers,
DIB colors,frame pacing,input J=B/K=A and focus/title-pause behavior identical.
Input contracts decoded at root;read-only full frame submitted to GUI;audio
adapter receives only IO snapshot,never full game. Existing renderer behavior
is compared with old renderer under deterministic neutral write sequences.
Original node scope/expectedMatches[],fresh0. Operational checks include
contract/PPU/audio-output/audio-renderer/death-audio/focus/product self-tests,
both widths,original DOS16 compilation/link and three local EXEs. Update
changed source dependencies as explicit pending rebinding for queued M2
verification;do not convert platform migration into game-node credit.

## S2 P1 closure - Win32 IO consumers

Win32 root now passes decoded IO input through app/game_io,submits a borrowed
read-only full compositor view,and exports an owned ordered audio tick.
Audio device/renderer interfaces consume only mysmb_io_audio_frame;no full
game pointer or game-header dependency. Shared composition glue copies public
output only,no original RAM or device APIs. Existing focus/title pause and
keyboard mappings unchanged. Frame dimensions,color table and synthesis
arithmetic unchanged;whole renderer inverse transformation equals S1 source.

Actual14 source/test/build files,+253/-121;estimate8-12/250-400 changed
lines grew by the reusable composition header/source,marshalling regression
and real16-bit bridge probe needed for the later DOS consumer. These belong
to admitted optional root-boundary scope,not game migration. Governance/source
layout records and dependency bindings are additional reviewed metadata.

Old/current native comparison1024ticks/752640PCM samples per width:zero sample
and renderer-state differences. Fixed writes cover0..64 events,invalid ignored
register indices and same-value duplicates;finite adaptation equivalence,
not a new ROM/all-input certificate. New marshalling test covers both input
ports,full-frame borrowed last byte,source immutability,owned audio lifetime,
64th ordered write and empty-tick clearing. x86/x64 each9 focused tests pass,
including actual waveOut submission,death sound,focus/pause and product self-test.
Real OpenNT16 bridge/contract compilation and full product link pass;retained
OLDNAMES linker warning,actual DOS graphics remains S3-S5. Three local products:
16=260011bytes,32=369309bytes,
64=381692bytes. Protected binaries not staged.

Coordinator review:only presentation interfaces/fixtures/glue changed;game
owners and synthesis arithmetic intact. Six changed build/Win32 dependency
identities and six new IO/glue paths recorded explicitly;no source-site universe
or match-status changes. Deferred final snapshot must still bind then-current
sources. Historical1992/1992,local1991/1992 nodes,4260/4261 feasible controls,
42/952 facets and all deferred findings/coverage unchanged. Original scope,
expected/actual matches[],fresh0. Registry/governance gates must pass before
commit. Push unavailable:no configured remote. Automatic S3 admission follows
reviewed S2 commit under owner authorization.
