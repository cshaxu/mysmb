# M3 T44 corrective library-readiness audit

## Admission and evidence boundary

Owner reopens T44 and admits S6 audit/design on 2026-10-13. Baseline c663c306.
The [S1-S5 record](../../history/M3-T44-nxvm-source-test-layout.md) retains its
measured Mario results. Its whole-T closure is withdrawn: directory separation
and Mario passes do not establish a reusable Mine-capable host. S6 changes no
production code and imports no Mine code. Later S slots are planned only.

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

All twelve entries are open at design delivery. Each receiving S attaches
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
closure. Only S6 is admitted. Tests ship with each changed owner, not at S13.

| S | Delivery and dependencies | Estimated files / lines | Exit |
| --- | --- | --- | --- |
| S6 active | Audit, fixed register, status correction and design | Docs only, about6 files | All findings assigned; governance/admission pass |
| S7 | Neutral KVM and atomic Mario adapters, G01-G04 | 20-40 /700-1600 | Both-app data/input representable; no NES maps in lib; Mario output retained |
| S8 | App refresh/pause/deadlines, G05; after S7 | 8-16 /300-800 | Event-driven and60Hz clients work without host-imposed game cadence |
| S9 | Win32/x64 host and Console/window mouse, G06; after S8 | 15-28 /800-1800 | Both widths and view/session/input lifecycle joins pass |
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
