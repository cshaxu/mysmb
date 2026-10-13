# M3 T44 corrective library-readiness audit

## Admission and evidence boundary

Owner reopens T44 and admits S6 audit/design on 2026-10-13. Baseline c663c306.
The [S1-S5 record](M3-T44-nxvm-source-test-layout.md) retains its
measured Mario results. Its whole-T closure is withdrawn: directory separation
and Mario passes do not establish a reusable Mine-capable host. S6 changes no
production code and imports no Mine code. S7 was subsequently admitted under owner automatic progression; see current receipts below.

Read-only Mine comparison covers core/app, text scene, DOS main, Windows
window, Win32 console and build script. The sibling snapshot has no established
revision/provenance receipt for import; redistribution is unreviewed. Only
neutral findings are retained. Its source-derived behavior is a requirement,
not new runtime qualification. No source, resources or game art are copied.

## Fixed scope

Prepare mechanisms for the current Mario/Mine requirements: DOS16, Win16,
Win32/x64 input, graphics/text presentation, lifecycle, timing, file/audio
devices, independent builds and owner-local tests. Apps own input meanings,
menus, save formats, palettes, rendering, refresh policy and game logic.

Mine requires left/right/middle press/drag/release/cancel; F1/F2, digits1/2/3,
N/H/M/Q and common keys; variable boards, menu commands, dirty/timer-driven
repaint and CP437 symbols. Its DOS implementation is text-only. Its Win16
text view is inside a Windows window, not a DOS prompt. New Mine DOS graphical
rendering and Win16-to-real-DOS handoff are not readiness prerequisites.
Mario continues to ignore Tab on Win16 as previously approved.

## Gap register

G01-G12 are closed after S13 integration and separate coordinator review. Each receiving S attaches
changed-owner tests and operational evidence before closing its entries.

| ID | Evidence and consequence | Disposition / receiver | Required proof |
| --- | --- | --- | --- |
| G01 | src/lib/kvm/video.h fixes256x240,32slots,80columns and master_map[64]; lacks dimensions/stride/capacity. Mine cannot supply its real board shape. | S7: bounded neutral views with geometry, stride, palette/count/lifetime; app owns NES slot maps and layout storage. | Non-Mario dimensions, invalid ranges,16-bit overflow and borrowed lifetime; Mario pixels unchanged. |
| G02 | src/lib/kvm/color.c owns NES64 RGB and NES-to-16 lookup. | S7: move NES data/conversions to app-mario; keep standard16 RGB, nearest-colour and attribute mechanics in lib. | No NES palette assumption in lib; VT/indexed/DOS colour corpus preserved. |
| G03 | input_event.h/windows_key.c cover Mario keys; unsigned mouse coordinates and incomplete held-button/cancel contract. | S7: both-app physical vocabulary, signed coordinates with explicit space, held buttons/modifiers, cancellation and neutral command IDs. | Negative/outside positions, key/repeat/chord transitions and capture loss assertions. |
| G04 | kvm/glyph.c only supports ASCII and selected box/block symbols; Mine smiley/triangle missing, unknown conversion returns zero. | S7: shared explicit encoding/mapping and bounded unsupported-glyph behavior; app chooses art. | Required Mine and existing Mario glyphs survive all projections; unknown symbol cannot discard a whole valid frame. |
| G05 | win16/clock.c fixes60Hz/four-tick cap; host.c chooses focus pause, skip and timer cadence. | S8: app-mario owns scheduler; lib exposes time/wakeup/retained repaint; app requests deadlines and dirty views. | Mario timing/audio order preserved; OS paint alone neither ticks nor recomposes; idle event-driven client has no forced60Hz work. |
| G06 | win32/text_console_input.c consumes but drops MOUSE_EVENT; text_console.c does not explicitly enable mouse. Generic window mechanics remain in app main. | S9: Console/window events, capture/cancel/resize and configurable window/pixel host; app owns actions/view/scheduling. | Actual PE32/PE64 window, VT/indexed Console, borrowed/owned sessions, mouse and Tab/focus restoration. |
| G07 | lib/dos16 has no mouse service; app DOS graphics mixes device transport and Mario composition. | S10: INT33 availability/poll/range/cursor and neutral VGA mode/palette/span services; retain PPU/cache/composition in app. | Actual DOS driver/no-driver cases, mode/cursor restoration, input; unchanged Mario pixels and memory budget. |
| G08 | win16/host.c/dib.c fix256x240,64-colour masks/aspect; application.h advertises text that host does not implement; no mouse/menu/capture delivery. | S11: configurable bounded DIB/palette/USER host, mouse/commands/cancel, text-in-window and truthful capabilities. | Actual Win3.x variable graphics/text/input/resize; Mario save/music retained, Tab inert. |
| G09 | app Win32 audio_output.c mixes waveOut transport and synthesis; DOS dos_audio_dos.c owns transport; file/startup services remain app adapters. | S12: extract reusable PCM/file/process mechanisms only; APU, audio cadence/overflow policy, save codec/pause transaction remain app. Reuse Win16 services. | No-game PCM/file fixture, partial-init/error/cleanup, Mario save/audio joins. T19 startup redesign remains separate. |
| G10 | Root CMake always includes Mario; optional Mine hook is a stub. Mine small-model and Mario large-model objects cannot be assumed ABI compatible. | S12: independent model-qualified libraries; app-owned resources/entries/binder composition. | No-ROM neutral client build; actual small/large model ABI/segment checks and three Mario products. |
| G11 | Existing suites prove Mario, not second-app shapes, mouse, glyphs or event-driven lifecycle. | S7-S12 test their changed owners; S13 consolidates neutral integration client and platform matrix. | Mirrored test ownership, each changed decision/return/conversion covered, no unavailable required capability counted as passing. |
| G12 | T44 closure and Mine candidate overstate readiness from directory migration. | S6 corrects status; S13 closes this register and updates readiness docs. | No open required gap, reverse dependency or game policy in lib; operational receipts and explicit exclusions. |

## Ownership sweep and target design

This is an interface/ownership audit of all four library families and matching
app adapters, not a claim of line-by-line functional certification.

| Family | Library mechanisms retained or completed | Application ownership |
| --- | --- | --- |
| kvm types/input/video/color/glyph | Portable types, physical events, bounded views, standard colour/glyph conversion | NES maps, source geometry, text art/layout, controller bindings |
| win32 launch/input/text_console/window_geometry/frame_wait | Console membership/handles/capabilities, geometry/event delivery, generic deadline wait; reusable window/pixel target | Mario actions, tick/frameskip, view request, composition, captions/save/synthesis |
| dos16 host/video_mode/text_cells/raw_keyboard/pit_clock | Mode/font/cursor/IRQ lifetime, raw input/clock/cells; mouse and physical VGA transport | Scrolling/OAM/HUD/repair, caches/allocation strategy, frame cadence |
| win16 host/dib/clock/audio/file/file_replace | USER/GDI, caller-palette device reduction, clock/wakeup, PCM and file operations | Fixed60Hz/catch-up/focus pause, source palette/geometry, frame generation |
| app platform service adapters | Extract reusable device pieces only | APU synthesis, sample production, save schema/snapshot policy, entry composition |
| build/tests | Memory-model-qualified tools/targets, independent neutral client | App resources, fixtures, products and composition |

App callbacks receive physical events/time and decide advancement, view, dirty
content and next wakeup. Host waits/pumps messages and presents immutable views.
OS repaint replays retained output without ticking/recomposing. Generic deadline
wait, resize debounce, retrace and device capacity stay library mechanisms;
none chooses game FPS. Mouse conversion accounts for viewport scaling,
letterboxing and Console origin; outside events must not become valid board
clicks by clamping. App interprets gestures and owns menu contents.

Update Mario consumers atomically when changing public contracts; do not keep
two competing implementations. Use bounded bands when16-bit surfaces exceed
a segment. Check size/stride arithmetic before allocating or accessing memory.
Do not force Mine into Mario's memory model or cache footprint.

## Planned S roadmap

Estimates include production/tests; actual changed files/lines are reported at
closure. S6-S13 are closed. Tests ship with each changed owner, not at S13.

| S | Delivery and dependencies | Estimated files / lines | Exit |
| --- | --- | --- | --- |
| S6 closed | Audit, fixed register, status correction and design | Docs only, about6 files | All findings assigned; governance/admission pass |
| S7 closed | Neutral KVM and atomic Mario adapters, G01-G04 | 20-40 /700-1600 | Both-app data/input representable; no NES maps in lib; Mario output retained |
| S8 closed | App refresh/pause/deadlines, G05; after S7 | 8-16 /300-800 | Event-driven and60Hz clients work without host-imposed game cadence |
| S9 closed | Win32/x64 host and Console/window mouse, G06; after S8 | 15-28 /800-1800 | Both widths and view/session/input lifecycle joins pass |
| S10 closed | DOS mouse and physical graphics services, G07; after S9 | 12-24 /600-1400 | DOS probe and Mario regressions; PPU/cache semantics unchanged |
| S11 closed | Win16 configurable graphics, window text and mouse, G08; after S10 | 12-22 /600-1400 | Actual Win3.x receipts; accepted Mario behavior preserved |
| S12 closed | PCM/file/build ownership, G09-G10; after S11 | 15-30 /600-1500 | Independent no-ROM client, model ABI and product/service tests pass |
| S13 closed | Full readiness joins/register reconciliation, G11-G12; after S12 | 8-16 /400-1000 | All required gaps evidenced; final checklist satisfied |

The neutral integration client is original test code under test/lib, with no
Mine or Mario linkage. It exercises board-sized output, mouse, commands,
text/glyphs and dirty updates. It does not become a new game/product.
Unexpected defects attach to a named gap and are repaired before its S closes;
new product wishes require separate scope, not an unlimited audit cycle.

## T closure checklist

- G01-G12 required capabilities have owner-local and integration evidence;
  missing functions cannot be relabelled documentation debt.
- Libraries build without Mario/ROM and have no reverse include/link/runtime
  dependency or NES/game policy. Independent client exercises non-Mario demands.
- Actual DOS16, Win16, x86 and x64 supported-view joins pass. Simulated events
  alone do not claim live RDP evidence. Unsupported required runtime evidence
  remains open, not a skipped pass.
- Mouse geometry/drag/chord/cancel/focus/Tab work; bindings remain app-owned.
  Win16 neutral client proves window text, Mario remains graphics-only there.
  Missing DOS mouse is explicitly reported as a capability, not fabricated input.
- Applicable configured units/integration pass. Each production-changing P
  refreshes16/32/64 EXEs with hashes and platform receipts. Measure memory and
  timing impact under unchanged host settings; preserve DOS loadability.
- Source/test ownership, receiving docs and queue agree. Mine import remains
  separate. T19 startup, inherited ROM certification debt, physical-machine
  performance and real Win16/DOS prompt switching are explicit exclusions.
- Historical1992/1992, retained1991/1992 nodes and4260/4261 feasible controls
  (4342raw,81infeasible) remain separate; this task earns no ROM credit.

## S6 verification receipt

Static design only: scope=[], expectedMatches=[], actualMatches=[], incoming
and maximum1992/1992. Production, tests and EXEs unchanged. No repaired
capability or new runtime qualification is claimed. Gate results follow after
execution; S6 remains active at design delivery, implementation not admitted.

Executed: node_task_ledger.py --write --admission and Verify-NodeProgress
pass with scope0/expected0,1992 total, zero orphan nodes.
Verify-DocumentationGovernance passes. git diff --check passes.
No product build/test was required or claimed for this documentation-only P.

## S6 closure and S7 admission

Owner authorizes single-person implementation/review roles and automatic S
progression through T closure. S6 closes with its source design and passing
gates; no production/runtime claim. S7 admits G01-G04 with empty ROM scope
and expected matches, baseline/maximum1992. Reviewer will separately inspect
ABI, ownership, bounds and corpus preservation after implementation.

S7 implementation note: removing app-owned text storage and palette-slot types
requires atomic signature/include changes through about70 app/library/test/build
files, exceeding the initial file-count estimate. Core source is unchanged.
Win16 DIB geometry/palette consumption is updated with its contract rather than
leaving a library-side NES compatibility path until S11. S11 still owns USER
mouse/menu/text/lifecycle completion. This is contract propagation, not a new
game or imported Mine scope.

## S7 P1 closure receipt

G01-G04 close: borrowed bounded pixel/text views replace NES storage in KVM;
Mario owns the unchanged64-colour tables and4000-cell storage. Physical input
now represents signed coordinates, button masks, cancellation, commands and
both-app keys. CP437 maps all256 byte slots. Mouse delivery remains G06-G08;
representability here is not a claim of implemented device delivery.

Single-person reviewer pass checked all lib palette/geometry consumers,
16-bit multiplication/capacity, borrowed lifetime, invalid projections and
source ownership. No core or PPU algorithm changed. The neutral glyph test
moved out of Mario tests; two old tests assumed a deliberately narrow glyph
set and ignored F1 delivery. Their owner assertions were corrected; no failed
production route was hidden. Win16 geometry/palette changes were pulled into
this atomic contract update; USER/window-text/mouse remain S11.

Test-owner closure: KVM owns span/palette/glyph invalid and success cases;
Windows-key owner covers vocabulary; DIB owns odd widths/padding/4/8-bit
projection and bounds; DOS text owns destination projection; Console joins
cover borrowed palette/cells and real buffer lifecycle. Contract-only mouse
fields are not executed routes; delivery tests belong to their receiving S.

Validation: Release Ninja/ccache x86 and x64 each300/300 configured tests;
latest added invalid-span assertions also pass both widths. Both private-desktop
host-integration targets pass13/13 routes. DOS compiler/linker/memory gate,
actual hidden DOSBox graphics/text/input/font/cursor/IRQ/exit probe pass.
Win16 compile/link/MZ binding pass; owner-local Win3.1 standard-VGA runtime
shows title, Enter into gameplay, movement and Escape termination. An early
capture caught the progressive title-to-game draw; the later movement capture
is fully composed. No live RDP, audio audibility or performance claim added.
DOSBox CPU/cycle settings were not changed.

DOS214segments, DGROUP53600bytes, minimum loader386816bytes excludingPSP;
page-rounded minimum387216bytes. Compared with S5 the rounded resident minimum
increases976bytes; DGROUP increases512bytes for complete glyph mapping. Dynamic
caches are additional, not included in this minimum. No new frame allocation.

Local products refreshed (bytes / SHA256):
-16:645821 /60fe0eb416f7562b8dadac0105be1629cd68eba4c48b17957f150f4fcd05ab63
-32:413835 /d6a88ac94dabdba100b8cd32d286034ddd9536395d50ca61e324f335f3126fa7
-64:378475 /358d666c4a8857e538efefcd2c5c00e5bf84c14687c65e666c7b73050a83758a

No product or protected probe image is committed. Zero node scope, expected
and actual promotions; historical1992/1992 and retained1991/1992 nodes,
4260/4261 feasible controls unchanged. The inherited final certificate remains
incomplete. Unrelated resource deletions remain untouched.

## S8 admission

G05 only; zero ROM scope/promotions. Move the existing60Hz/four-tick budget
and focus pause into Mario. The USER host accepts requested wake delays and
dirty output; paint only replays retained pixels. Add owner scheduler tests
and a no-game host lifecycle fixture, including idle/no-timer behavior.

## S8 P1 closure receipt

G05 closes. The existing60Hz/four-tick credit algorithm moved unchanged from
lib/win16/clock to app-mario/platform/win16/scheduler. Mario owns focus pause,
file-transaction rebase, logical tick/audio order and overdue-image skipping.
The library receives dirty output plus an app-requested wake delay; zero means
wait for input. WM_PAINT only replays the retained DIB. Exit is serviced after
input even for clients that never request a timer; shutdown guards prevent
recursive focus-loss teardown. Library documentation now reflects this contract.

Single-person reviewer checked all former clock/focus/pacing references in
lib/win16 and its consumers. No second scheduler, core/PPU change or Mine import.
Test-owner closure: app scheduler retains credit/cap/wrap/backward-time cases;
neutral host fixture compiles the actual host separately against a synthetic
USER device and proves idle/no-timer, app-selected123ms wake, dirty-only
composition, retained paint, focus delivery, timer failure and recursive
shutdown. Application ABI fixture migrated to update requests. This device
fixture is not described as actual Windows execution.

Release x86/x64 suites each301/301 pass; final owner tests including recursive
shutdown pass both widths. Win16 compiler/linker/MZ binding pass. Actual
owner-local Win3.1 standard-VGA probe passes startup, Enter gameplay, D movement
and Escape exit0 with retained captures inspected locally. DOSBox settings
unchanged. DOS entry/code/resident bounds unchanged from S7; Win32 source and
product hashes unchanged after incremental builds. Prior13-route Console joins
remain applicable to unchanged sources; they were not needlessly rerun.

Local products republished:16=646061bytes,
SHA2562cba8dc5d092fd4bc96bac82b9998c24a4eeef33a491b4e9ca02e22edcb3321a;
32/64 retain S7 sizes/hashes. No protected products/captures committed.
Expected/actual ROM promotions0; historical1992/1992, retained1991/1992nodes
and4260/4261feasible controls unchanged. G06-G12 remain required T work.

## S9 admission

G06 scope; zero ROM promotions. Extract neutral window creation/messages/pixel
submission, deliver Console/window mouse state with capture/cancel/resize.
Applications keep input meanings, focus/pause, view choice and message-pump
cadence. Portable pointer transitions serve later DOS/Win16 adapters too.

## S9 P1 closure receipt

G06 closes. Library window services now own class/window creation, sizing/DPI,
physical key/mouse/focus/command/resize delivery, capture cancellation and GDI
pixel submission. Mario keeps its loop, input meaning, focus-pause/save and
view choice. Console polling delivers physical records through the same app
mapper; obsolete key-only API is removed. Mouse mode is enabled without Quick
Edit. CP437/RGB/indexed presentation and existing launch/Tab policy remain.

Portable KVM pointer owner emits ordered button transitions with complete held
masks, signed coordinates, drag movement and cancellation. Console coordinates
subtract the actual viewport origin. Window coordinates remain client pixels,
matching its full-client image destination; resize reports its dimensions.
Apps decide board/cell semantics. No outside coordinate is clamped into a click.
Suspend/close clear held mouse state; reopening cannot deliver stale gestures.

Reviewer sweep found and repaired a real ownership hazard: hidden GUI focus
messages must not pause or clear the active Console device. A root integration
assertion now retains that behavior. Leaf paint assertions moved from a macro
intercept in the Mario fixture to actual GDI memory-bitmap output in the neutral
host probe; root resize/state joins remain. No core/PPU change or Mine import.

Test-owner closure: pointer transition test owns chord order, drag/outside,
release and cancel; no-game Win32 device probe owns physical window/Console
conversion, capture/focus, Unicode-only key2, repeat/F2/menu, invalid geometry,
actual RGB blit/readback, invalid pixel spans, mouse input mode and session
cancel/resume. Existing owner tests cover vocabulary/palette/geometry. OS API
failure paths use natural invalid handles/spans plus retained host-error joins;
this is bounded capability evidence, not exhaustive OS fault injection.

Release x86/x64 suites each302/302 pass including purity. Both private-desktop
host targets pass15/15 routes: two neutral device routes and13 retained Mario
routes. A hidden console initially could not supply a resizable visible window;
the classic probe explicitly shows its own window on the private desktop and
then proves nonzero scrolled origin. It does not change the system terminal.
Direct screen GetPixel was unsuitable for an inactive desktop, so the exact
same GDI submission is verified on an actual memory DIB, not mocked output.
Live RDP is not claimed. No extra product process is introduced.

All three products rebuilt/republished. DOS compile/link/memory and Win16
compile/link/binder pass. DOS image hash/resident limits exactly match S7;
Win16 source behavior is unchanged and retains S8 actual runtime receipt.
Local sizes / SHA256:
-16:646093 /7ef289174267359e06e52030d8bb06a4a7ec113ed067747dcf902ac474d6dd4b
-32:418443 /05abaafabebcfb49eac2b2df130635a20fbe5a2131af631664ce3686a9d5c780
-64:382059 /35aec024d7d6f82c2d5cc299be8f624643e7508f1768fa9f8b48a354af17c8d8

Actual implementation spans17 source/test/build files (including new owners),
about650 inserted/170 removed lines, plus governance. Products remain ignored.
ROM scope/expected/actual promotions0; historical1992/1992, retained1991/1992
nodes and4260/4261feasible controls unchanged. G07-G12 remain T obligations.

## S10 admission

G07 only; zero ROM scope. Mouse uses caller-owned driver-save storage and
physical events; absence is explicit. VGA register/palette/span mechanisms
move to lib/dos16; all PPU-selected geometry, scene composition and cache
policy remain Mario-owned. Preserve existing mode/register/transfer behavior.

## S10 P1 closure receipt

G07 closes. DOS library owns BIOS mode selection, VGA register profiles,
plane/DAC/viewport writes and bounded segment copy primitives. Mario retains
PPU interpretation, viewport/cache selection and scene composition. Extracted
register sequences and assembly copy bodies retain their original ordering;
mode initialization programs each DAC entry explicitly. No core/PPU change.

Optional mouse service preserves the caller's driver state, configures physical
ranges, emits KVM pointer events and restores on close. Storage is caller-owned;
Mario does not link or allocate mouse storage. Missing driver/unsupported save
state is explicit failure, never a fabricated capability.

Reviewer sweep: DOS band submission now checks neutral span capacity, width
and stride before its fixed Mario copy. Native probe supplies those fields.
Mouse owner-local assertions cover absence, insufficient storage, reset failure
rollback, duplicate open/close, range configuration, scaled position, chord
queue, visibility and restore. Shared pointer tests own detailed transitions.
Actual BIOS/port/assembly joins are integration-only, not host mock assertions.

Both Release suites303/303 pass. Actual hidden DOSBox probe reports driver
save484bytes, position12,9, restored320,100 and absent driver0. Actual VGA probe
compares61440pixels with0 buffered and0 direct mismatches,61440 direct bytes,
two graphics/text round trips, font/cursor/IRQ restoration and mode3 restored.
No CPU/cycles configuration was changed. These are runtime capability receipts,
not physical486 performance evidence. Win16 behavior retains S8 runtime proof;
its rebuilt hybrid binds the new DOS stub. All three local products refreshed.

DOS215segments; DGROUP53600 including2048stack; minimum load386736bytes,
page-rounded387216; bounded maximum390832/page391312, dynamic caches excluded.
Resident DGROUP unchanged; DOS file363035bytes,80 fewer than S9. This extraction
claims no speedup. Native host joins retain the current15-route owner matrix.

Local products (bytes / SHA256):
- 16: 646093 / 23853cc48195e0bc484372a6681338f0d27a6716d3b70061509b6b8d79a85cae
- 32: 418443 / 05abaafabebcfb49eac2b2df130635a20fbe5a2131af631664ce3686a9d5c780
- 64: 382059 / 35aec024d7d6f82c2d5cc299be8f624643e7508f1768fa9f8b48a354af17c8d8

Implementation affects14 source/test/build files, approximately440 added and
165 removed lines including new owners. Products remain ignored. ROM scope,
expected and actual promotions0; historical1992/1992, retained1991/1992 nodes
and4260/4261 feasible controls unchanged. G08-G12 remain required T work.

## S11 admission

G08 only, no ROM promotions. Retain output independently of app callbacks;
allow segment-bounded bands for large surfaces and app-selected window text.
Physical mouse/capture/cancel/menu events have no game meaning in the host.
Mario stays graphics-only on Win16. Neutral client proves additional views.

## S11 P1 closure receipt

G08 closes. Win16 keeps immutable segment-bounded DIB bands; Mario remains a
single band, larger boards no longer require one segment. App update may change
geometry/palette and request dirty composition. Paint only replays retained
output. The host accepts app-selected window text with CP437 OEM font and16
logical colours. A retained copy protects paint from later producer mutation.
Two-level app-defined menu labels/IDs and mutable checked/enabled flags have no
game semantics. Mouse chords, signed outside coordinates, capture/cancel,
focus loss, resize and command events use the common physical vocabulary.
View switches cancel held gestures; apps retain bindings, cadence and policy.
Mario Win16 remains graphics-only with inert Tab. No Mine import or core/PPU edit.

Reviewer sweep fixed allocation/lock rollback for every band, silent invalid
composition, paint failure timer rearming and initial oversize window geometry.
Actual SDK compile has no new library warnings. Owner tests assert large-band
allocation, every partial allocation/lock cleanup, physical conversion/chord/
cancel/command/resize, dynamic geometry, retained text, RGB-to-COLORREF, opaque
cell extents, font/output failure, idle/timer scheduling and retained repaint.
No second unit duplicates shared pointer or palette algorithm assertions.

Both Release suites303/303 pass. Actual Win3.x neutral client, with no ROM/game
linkage, reports result0/failure0, four phases, mouse2/cancel1/command1/resize1,
66 produced bands:504x323 graphics,80x25 CP437 text, then320x200 graphics.
Captured graphics/text visibly include all256 OEM codes and distinct colours.
Actual Mario Win3.x route proves title/start/move/exit. Windows runtime uses the
previous qualified standard VGA environment; DOSBox cycles/CPU unchanged.
A pre-existing swap-file utility prompt was acknowledged in the probe script;
it is not a game failure or performance-setting change. No live RDP claim.
Win32/DOS source behavior retains S10 host/probe receipts. Final paint-failure
cleanup guard is unit-tested; normal runtime route is unchanged by that guard.

Win16 allocates actual4-bit rows on standard VGA: Mario retained pixels now
30720bytes rather than61440, plus a small descriptor and about1KiB palette
comparison state. Large boards allocate multiple blocks; no block exceeds
65520bytes. DOS stub/resident footprint unchanged. No speedup claim.
All products republished (bytes / SHA256):
- 16: 652461 / 7e94f07139f7f907954aad43086ff00a521e87e166611ac6581598e78dc6f975
- 32: 418443 / 05abaafabebcfb49eac2b2df130635a20fbe5a2131af631664ce3686a9d5c780
- 64: 382059 / 35aec024d7d6f82c2d5cc299be8f624643e7508f1768fa9f8b48a354af17c8d8

Actual source/test/build scope11files, about570 inserted/70 removed lines.
Scope/expected/actual ROM promotions0; historical1992/1992, retained1991/1992
nodes and4260/4261feasible controls unchanged. G09-G12 remain required work.

## S12 admission

G09-G10 only. Move physical PCM and file replacement out of Mario; preserve
app synthesis, save/pause and audio overflow/tick policy. Build shared libraries
without ROM/Mario; qualify separate16-bit memory models, never mix objects.
No T19 startup redesign or Mine import; zero ROM node credit.

## S12 P1 closure receipt

G09-G10 close. Win32 waveOut queue, DOS DSP/DMA/PIC transport and file/path
mechanisms now live in their library owners. Mario retains APU synthesis,
sample generation/drop policy, save codec and pause/load/reset transaction.
Win16 PCM block size/count are caller-selected; Mario still supplies184/8.
No core/PPU change, scheduling change or Mine import.

Reviewer sweep covered open/partial-prepare/write/reset/unprepare/close
failure, borrowed-buffer lifetime, invalid capacities and retry. Failed device
cleanup retains driver-owned memory and cannot submit an unprepared header.
DOS file replacement retains its existing remove/rename semantics; it is not
claimed atomic. Win32 owns MoveFileEx and executable-path mechanics. DOS PCM
native submission now uses a16-bit sample index, so non-Mario512-byte blocks
cannot wrap at256. No device knows APU registers or a game frame rate.

Independent small-model qualification exposed missing far qualifiers and
near CRT copies of GlobalLock data. Shared bounded views and Win16 palette,
DIB and PCM consumers now preserve far addresses; segmented copies use the
appropriate far CRT. Small/large objects and CRTs are built separately.
No-ROM/Mario CMake configuration passes18/18 owner tests. Actual DOS small
and large static-library clients each pass36 PCM blocks of512samples, reset
and PIC restoration. Model probes report nearPointer2/4 respectively, far4,
16cells and a palette outside DGROUP. Actual small-model mouse reports saved
484bytes,12/9 position,320/100 restored and absent-driver0. These are device
lifecycle receipts, not an audible-speaker claim.

Actual small-model Win3.x neutral client passes result0/failure0, four phases,
mouse2/cancel1/command1/resize1/bands66, variable graphics/window text plus
file replacement/path. Actual large-model Mario title/start/move/exit passes.
Win16 PCM availability is optional on a host without a waveform driver;
fault paths are owner-unit covered, not relabelled real audio output.
Actual DOS Mario audio integration reports passed. VGA integration compares
61440pixels: bufferedMismatch0/directMismatch0, directBytes61440, two round
trips and mode3/font/cursor/IRQ restored. DOSBox CPU/cycles remain unchanged.

Both Release suites306/306 and both private-desktop15-route Win32 integration
matrices pass, including save/load/audio reset and borrowed/owned Console
teardown. All local products refreshed. DOS216segments, DGROUP53600 including
2048stack; minimum386832/page387216, bounded maximum390928/page391312bytes,
dynamic caches excluded. Page-rounded load requirement remains unchanged;
no performance improvement is claimed by this extraction.

Local products (bytes / SHA256):
- 16: 652919 / c39b9d5dfa109b6ad2ff6764df30206ad7794654ebb803e43a2304fee25b1ebc
- 32: 419979 / 7e60ccb94a6aa67d903e069b17462b0666c7b0108084815f74738a74eeca65cd
- 64: 383595 / d47dd8630e7d6d449d5b83a45475ea0de0785de29a9600bc4b94e7f54009b812

Actual58source/test/build files,929added/704removed lines; larger than the
initial file estimate because atomic consumer moves and far-ABI correction
must ship together. Owner units cover each changed portable decision; physical
BIOS/ports/WinMM/USER joins use the native receipts above. Historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls unchanged; zero scope,
expected or actual promotions. G11-G12 remain required S13 work.

## S13 admission

G11-G12 only. Complete independent shared-test target ownership and a no-ROM
private-desktop integration entry, then reconcile the fixed capability matrix.
Retain S7-S12 actual DOS/Win16 joins for unchanged owners; rerun native suites
and host joins after build/test changes. No game code or Mine import. Review
all four library families for reverse dependencies and app policy. Report
explicit capability limits, local products, memory and zero ROM promotions.

## S13 P1 and T44 closure

The fixed G01-G12 register is complete. Coordinator reviewed the owner request,
production ownership, changed contracts, test owners and runtime receipts
separately from implementation. Libraries are ready for the scoped Mine
adoption; Mine itself is neither imported nor runtime-qualified. No library
owns an app input meaning, game frame rate, APU synthesis or NES resource.
The only active task ends here; later queue candidates are not auto-admitted.

S13 moves four remaining shared Win32 fixture targets out of Mario CMake,
splits the library dependency gate from Mario's gate and adds a devices-only
private-desktop target. No production C/H changes. Independent x86/x64 Ninja
build graphs contain no app source, ROM or ROM generator. Both independent
suites22/22 pass; each no-ROM host run passes neutral window/Console/mouse/
capture/dirty-pixel and classic scrolled-Console routes. Both full Release
suites307/307 pass with no skipped case, and both complete15-route product
host matrices pass. Test counts increased because the independent dependency
gate is separately owned; no extra ROM equivalence coverage is claimed.

### Final bounded capability and evidence matrix

| Gap | Implementation / owner assertion | Operational join / final disposition |
| --- | --- | --- |
| G01 | KVM dimensions/stride/capacity and overflow/lifetime checks, S7 contract unit | Non-Mario geometry in Win32 and actual Win16 bands; closed |
| G02 | App owns NES maps; KVM owns standard colour and attribute mapping, S7 colour unit | VT/indexed Console plus actual VGA/Win16 projection; closed |
| G03 | Physical vocabulary and pointer transition owner units, S7/S9/S10/S11 | Both native widths, actual DOS mouse and Win3.x mouse/cancel/commands; closed |
| G04 | CP437 mapping including smiley/triangle and fallback, S7 glyph assertions | All256codes in actual Win16 text; Console and DOS cell projection; closed |
| G05 | App scheduler unit; Win16 host dirty/deadline/paint lifecycle unit, S8 | Actual neutral event-driven client and Mario title/start/move/exit; closed |
| G06 | Window/Console event, geometry, capability and lifecycle owner tests, S9 | Both15-route matrices including borrowed/owned sessions, Tab/focus/save/input; closed |
| G07 | DOS mouse unit and existing physical device projection contracts, S10 | Actual native61440pixels0mismatch, mode/font/cursor/IRQ restore and mouse present/absent; closed |
| G08 | Win16 retained bands/text/menu/capture/cleanup units, S11 | Actual504x323 graphics,80x25 text,320x200 graphics; result0/failure0; closed |
| G09 | PCM fault/lifetime/capacity and file/path owner units, S12 | Actual DOS PCM and Mario audio join, actual Win3.x file join, native save/audio-reset host routes; closed |
| G10 | Far-qualified view/copy contracts and independent build ownership, S12 | Separate small/large DOS static libraries and small/large Win16 clients; no-ROM builds; closed |
| G11 | Mirrored shared/app test owners and distinct dependency gates, S13 | Independent22/22 eachwidth, full307/307 eachwidth, actual platform receipts retained; closed |
| G12 | This fixed register, current architecture, queue and receiving proposal, S13 | No required open gap or reverse app dependency; explicit exclusions retained; closed |

Portable decisions, failure returns and conversions are asserted by their
named owner tests. BIOS/port/segment/WinMM/USER behavior is validated at the
physical integration boundary; fake SDK units do not replace those joins.
S13 changes no16-bit production source or build recipe, so S12 actual DOS and
Win3.x receipts remain current and are not repeated solely to inflate counts.

Product bytes equal S12 after final native build:16/32/64 hashes and sizes are
in its receipt above. No new product implementation, cache or cadence change
in S13; no performance claim. DOS page-rounded allocation remains387216minimum,
391312bounded maximum before dynamic app caches. Win16 standard VGA Mario
retained pixels are30720bytes rather than the old61440. A physical486 or live
RDP/Terminal visual qualification is not inferred from private-desktop probes.

The old HOST-TEXT-FIXTURE-131 and default-all Cannon Children link blockers
are superseded by current passing complete fixtures/builds; TODO records this
bounded closure. Remaining Win16 host work is8bpp/Win3.0/standard-mode and real
DOS-prompt handoff qualification, not a missing window-text implementation.
Standard Win3.x16colour reduction remains a device limitation. Mario Win16
continues graphics-only with inert Tab. Mouse/audio device absence remains
explicit; runtime sound-driver availability is not an audible-speaker claim.

T19 bounded startup, Mine provenance/import/app bindings, physical-machine
performance and M2 final certification remain separately queued/excluded.
Scope=[], expectedMatches=[], actualMatches=[]; historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls (4342raw,81infeasible)
are unchanged. This readiness closure is not a whole-ROM certificate.

Task-generated build/probe/runtime copies and native build outputs are removed
at acceptance after retaining these receipts. Local products under assets/mario
and the qualified tools/dos16 toolchain remain. Seventeen pre-existing resource
deletions are preserved unstaged; they are not part of this task's commits.

S13 actual source/test/build/receiving-note scope: 7files, 111added/67removed lines; production C/H unchanged. Governance and history relocation are additional.

Acceptance cleanup removed11generated directories and289883800bytes; build is empty. Qualified tools and all three local products remain.
