# M3 T44 corrective library-readiness audit

## Admission and evidence boundary

Owner reopens T44 and admits S6 audit/design on 2026-10-13. Baseline c663c306.
The [S1-S5 record](../../history/M3-T44-nxvm-source-test-layout.md) retains its
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

G01-G04 close with S7, G05 with S8 and G06 with S9; G07-G12 remain open. Each receiving S attaches
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
closure. S6-S9 are closed; S10 is next. Tests ship with each changed owner, not at S13.

| S | Delivery and dependencies | Estimated files / lines | Exit |
| --- | --- | --- | --- |
| S6 closed | Audit, fixed register, status correction and design | Docs only, about6 files | All findings assigned; governance/admission pass |
| S7 closed | Neutral KVM and atomic Mario adapters, G01-G04 | 20-40 /700-1600 | Both-app data/input representable; no NES maps in lib; Mario output retained |
| S8 closed | App refresh/pause/deadlines, G05; after S7 | 8-16 /300-800 | Event-driven and60Hz clients work without host-imposed game cadence |
| S9 closed | Win32/x64 host and Console/window mouse, G06; after S8 | 15-28 /800-1800 | Both widths and view/session/input lifecycle joins pass |
| S10 | DOS mouse and physical graphics services, G07; after S9 | 12-24 /600-1400 | DOS probe and Mario regressions; PPU/cache semantics unchanged |
| S11 | Win16 configurable graphics, window text and mouse, G08; after S10 | 12-22 /600-1400 | Actual Win3.x receipts; accepted Mario behavior preserved |
| S12 | PCM/file/build ownership, G09-G10; after S11 | 15-30 /600-1500 | Independent no-ROM client, model ABI and product/service tests pass |
| S13 | Full readiness joins/register reconciliation, G11-G12; after S12 | 8-16 /400-1000 | All required gaps evidenced; final checklist satisfied |

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
