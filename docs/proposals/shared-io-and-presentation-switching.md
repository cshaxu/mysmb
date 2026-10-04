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
report. Single executor/coordinator roles;no delegated agent. At initial admission
S1 was active and S2-S6 were planned;latest admission/closure sections below
and CURRENT own the subsequent state. No configured remote:local commits proceed,push unavailable
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

## S3 admission - DOS graphical IO bring-up

Automatically admitted after S2 commit5b9a6303. Single executor/coordinator.
Expected12-18 source/test/build files,600-900 changed lines. Components:DOS
root/main/keyboard/timing/mode lifecycle,VGA scaling and64-color palette,
shared color/conversion contracts,Win32 palette consumer if shared table moves,
original OpenNT16 generation/link and focused native adapter tests.

Observed concrete defects:mode13 BIOS reset every present;five-index lossy
VGA conversion/no matching64-color DAC;column*256 overflows unsigned16 for
large destination X;DOS root lacks immutable ROM/CHR/title bindings and
checks neither PPU allocation failure nor clean shutdown. BIOS buffered key
polling loses held/simultaneous actions. Address these adapter defects with
bounded storage,system-dependent code only in DOS adapters and no game rules.
Text contract remains inert;remove old simultaneous text production from the
admitted graphics path. Same256x240 canonical input,all game owners unchanged.

Register exact original-node scope/expectedMatches[],fresh0. Focused IO,
VGA/root/input/mode lifecycle tests at both widths,existing Win32 frame/audio/
focus and self-tests,original DOS16 full compile/link and three local EXEs.
S3 begins actual graphical runtime bring-up;S4 stabilizes timing/devices and
S5 owns sustained gameplay route proof. Do not call link-only graphics success.
Owner-local generation stays ignored/read-only ROM source,not distributable.
Runtime probe may link existing owner-local SoftPC library through its public
API and derive an ignored DOS boot image from its owner-local media. These
are local nonredistributable validation inputs,no sibling writes or product
dependency;probe source,media and screenshots remain below ignored build.
Record changed dependencies for queued M2 final snapshot;no match promotion.
No remote,push unavailable;commit/report then automatic S4 admission when
S3 scoped checks and review pass.

## S3 P1 closure - DOS graphical IO bring-up

DOS composition consumes decoded IO input and the canonical indexed frame;
no simultaneous text production. Shared color lookup preserves all64 original
Win32 presentation values byte-for-byte. Shared row scaling removes unsigned16
column overflow and avoids per-pixel division;VGA owns only paged storage and
devices. BIOS video mode/DAC setup occurs once,Esc restores prior mode and
keyboard vector,and per-root far allocation checks failure and frees once.
Physical set-1 make/break state preserves simultaneous WASD/J=B/K=A/Enter/
either Shift. DOS resources bind through the same public APIs as Win32.
PIT sampling preserves BIOS-owned rate/vector;S4 owns pacing stabilization.

Actual18 source/test/build files,+432/-292;within12-18/600-900 estimate.
Executor11focused tests eachwidth pass;full64000-pixel independent scaling
comparison and fourpage guard bytes,held combinations/release/extended prefix,
invalid hooks and idempotent shutdown covered. Real OpenNT16 large-model
compile/link with local resources passes;known OLDNAMES warning retained.
Read-only existing SoftPC public API/object archives and private derived boot
media prove Mode13 startup,40 nonempty output samples,Enter injection and Esc
restore to Mode3. This scoped bring-up is not S5 sustained gameplay or a ROM
certificate. No desktop window/input control was used. Raw media/capture/harness
and logs remain ignored below build;no sibling modification or product VM.

Three local products:16=303357bytes,
32=369617bytes,64=382035bytes.
Not staged or redistributed. Coordinator review:game owners/audio synthesis
unchanged;new adapters receive neutral contracts. Similar-defect sweep covered
all DOS root/presenter mode resets,color truncation,index products,allocation
and key buffering;legacy text module remains outside admitted graphical path.
Changed dependency identities recorded for deferred M2 rebinding,not new proof.
Historical1992/1992,local1991/1992 nodes,4260/4261 controls,42/952 facets
unchanged;scope/expected/actual[],fresh0. Closure gates required before commit.
No configured remote,push unavailable. Owner authorizes automatic S4 admission.

## S4 admission - DOS device stabilization

Automatically admitted after S3 f02c90f8 under owner approval. Expected8-12
source/test/build files,300-500 changed lines. Shared pacing uses bounded
clock deltas;DOS samples BIOS-owned PIT without changing IRQ0/rate. Late frames
must not incur an additional full wait or unbounded catch-up. Device setup and
teardown remain idempotent. DOS root exports ordered audio through the neutral
contract;the host explicitly reports absent audio hardware,never invented
sound. Focused clock rollover/late-frame/audio lifetime checks and scoped real
DOS startup/Esc restore precede closure;S5 retains sustained gameplay proof.
Owner-local inputs/provenance follow S3,all outputs ignored. Empty ROM scope,
expected/actual[] and zero new node/control credit;no game owner edits.

PIT review uses the public [Intel8254 datasheet](https://www.cs.umb.edu/cs341/Intel8254/I8254PIT.pdf)
as a hardware-interface reference only,no code or protected program data
copied. Mode3 decrements by two and reloads each half cycle;read-back OUT and
count must be combined. A focused physical decoder and exhaustive cycle test
are included in S4 rather than accepting a double-rate timing interpretation.

## S4 P1 closure - DOS device stabilization

Shared pacing waits only the remainder of a frame,preserves fractional
lateness,and discards missed-frame backlog. DOS reads BIOS ticks and latched
8254 status/count without altering PIT frequency/vector;mode3 half-cycle
decoding and pending IRQ0 correction prevent double-rate interpretation.
Midnight/clock discontinuity is bounded. Ordered game audio is exported once
per tick through IO;DOS explicitly returns audio-unavailable and announces
that before graphical setup. No sound hardware or game semantics invented.
Mode and keyboard lifetime retain idempotent device open/close and root free.

Actual16 source/test/build files,+161/-20,versus8-12/300-500 estimate.
The separate physical PIT decoder,exhaustive cycle test and strengthened
device purity gate explain the extra files;these are admitted timing/sweep
scope.13focused tests per width pass,including all65536 mode3 positions,
mode2 and alias modes,clock32 rollover/discontinuity/late frames,ordered audio
callback and existing Win32 frame/audio/focus checks. Original OpenNT16 full
resource-bound build/link passes. S3 read-only SoftPC probe rerun on the S4
binary observes40 nonempty graph samples,Enter injection and Esc restore3.
This remains scoped bring-up,S5 sustained route proof is pending.

Three local products:16=308893bytes,
32=369617bytes,64=382035bytes.
Protected products/media remain local/unstaged. Coordinator review:only IO and
DOS infrastructure changed,existing Win32 synthesis/game owners unchanged.
Similar-issue sweep covers all device code imports,BIOS timer mode3/rollover,
frame backlog and silent audio capability;legacy text path stays inert.
Changed dependencies recorded without semantic promotion. Historical1992/1992,
local1991/1992 nodes,4260/4261 controls and42/952 facets unchanged;scope/expected/
actual[],fresh0. Governance/registry/node gates required before commit.
No remote,push unavailable;automatic S5 admission follows reviewed commit.

## S5 admission - sustained DOS graphics

Automatically admitted after S4 39cdf306. Expected3-6 test/tool/build files,
250-400 changed lines. Project-owned probe links read-only existing SoftPC
public API/compiled archives,boots private derived owner-local DOS media and
drives only guest keyboard without a desktop window. Record actual graphical
title/Start/held movement/run/jump/release and restored text mode. Capture
pixels remains ignored local evidence;process exit/nonzero pixels alone are
not sustained gameplay proof. Resource-bound DOS16 and two Win32 builds plus
focused regressions remain required. Original node scope/expected/actual[],
fresh0;no game rule changes or new ROM equivalence credit. Provenance/local
containment follows S3/S4. Repairs stay inside observed platform failures.

Observed unoptimized 8086-target rendering makes title/input tests take tens
of seconds in the DOS VM and lets short test key holds miss frame sampling.
S5 attempted original compiler /Ox /G3 target flags for the declared486SX
integer-only product and bounded scene-state probe waits. No translated C
owner or game rule is changed;optimized DOS behavior needs actual route proof.

The existing compiler optimizer rejected even the tiny color unit with its
internal buffer/out-of-memory diagnostic,including confined-temp and ordinary
permission checks. /Ox and /G3 were withdrawn;the accepted original flags are
retained. Performance qualification/optimizer investigation remains M4 work.
S5 probes now wait for distinct complete title/game scenes,not a fixed early
timeout or an all-zero VGA initialization buffer. Continuous Common execution
and its synchronized frame/input queues replace the insufficient finite-slice
capture;no desktop frontend is opened.

Owner subsequently authorizes DOSBox testing and directs SoftPC to stop.
Use installed DOSBox0.74-3 with SDL dummy video/audio in a private ignored
build directory;original DOS16 compiler/linker/flags remain unchanged. A
project-owned SDL public-ABI probe supplies balanced input events and saves
the emulator surface without desktop input or guest-RAM mutation. Public
[SDL1.2 event declarations](https://github.com/libsdl-org/SDL-1.2/blob/main/include/SDL_events.h)
and [DOSBox manual](https://www.dosbox.com/DOSBoxManual.html) are interface
references only. DOSBox GPL/SDL LGPL runtime copies stay local,not committed;
no imported implementation or product dependency. Retired SoftPC experiments
remain below ignored build and do not count as the DOSBox acceptance route.

## S5 P1 closure - actual DOSBox gameplay

Delivered4 project-owned test/tool files,+281/-0 lines,within the3-6
file estimate and near the250-400 line estimate. No product/game source edit.
Original OpenNT16 accepted flags/link and x86/x64 products pass;13focused
tests per width plus the existing player-friction test per width pass.
Three local products remain16=308893,32=369617,
64=382035 bytes,identical to S4 products.

Owner-directed DOSBox0.74-3/SDL1.2 dummy-video/audio route uses the actual
resource-bound EXE. Installed runtime copies and all captured protected pixels
remain local under ignored build. The public event ABI proxy injects balanced
Enter,D+J,K,A and Escape events;every other SDL export forwards to the original
runtime. No desktop window/input,guest RAM patch or product emulator dependency.
Reproduce with Build/Invoke-DosBoxIoProbe and VerifyDosBoxIoReceipt using the
local compiler/runtime/product/output arguments. Neutral receipt binds the EXE
hash;stale declared captures are removed before each run.

Finite56-second route observes title,Start and24seconds of gameplay:
player red bounds advance right,rise with K,return left,and stay identical
in two captures three seconds apart after deceleration. Escape restores DOS
text output and execution returns to the caller's completion marker. This
is an operational route,not ROM equivalence or486SX performance qualification.
Early scripts hit the startup transition or captured before deceleration
finished;these were rejected,not counted. Keep the strict positional check
and wait for settled motion. Buffered Escape could prematurely satisfy a DOS
shell pause;bounded repeated pauses retain the restored text screen for capture.

Coordinator review:only project harness/build plumbing and governance changed;
no ROM implementation,compiler flag,game state or platform synthesis changed.
Similar-issue sweep covers partial/blank frames,missing resources,unbalanced
events,missed short holds,stale captures,early shell termination and link-only
acceptance. SoftPC attempts are retired local experiments,not DOSBox receipts.
Optimizer flags remain withdrawn;M4 owns real-machine performance qualification.
Historical1992/1992/local1991/1992 nodes,4260/4261 controls,42/952facets unchanged;
scope/expected/actual[],fresh0. Ledger/registry/governance gates required before
commit. Push unavailable:no configured remote. Automatic S6 admission follows.
