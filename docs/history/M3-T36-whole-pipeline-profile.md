# M3 T36: Whole-Pipeline Performance Assessment

The owner directs a comprehensive search for further performance opportunities,
including shared core, PPU, DOS presentation and Win32 presentation, while
retaining original game semantics and one portable core implementation.

## S1 Admission

S1 owns instrumentation and evidence only.  It will construct an ignored,
profile-only measurement route that separates input/control, startup/game tick,
PPU preparation/composition, palette work, device publication, audio handoff
and pacing.  It will report each stage separately for the current DOS16 and
host routes where a valid clock exists.  It does not modify translated game
decisions, render output, platform behavior, cache allocation, executable
release artifacts or ROM-facing code.

The expected change is 200--350 lines of project-owned profile/test support,
or no tracked source if the existing diagnostic surfaces are sufficient.  Any
temporary source, executable, trace, image and receipt stays below ignored
`build/`.  The measurement must not change persistent DOSBox configuration or
use host wall-clock time as a 486SX claim.

The output is a finite candidate table.  Every candidate names its owner,
shared/DOS/Win32 applicability, measured stage, expected memory effect,
semantic risk, exact proof route and accept/defer/reject disposition.  Core
candidates must use the same C90 source for all targets: no DOS-specific game
logic, platform macros, pointer representation or state layout may enter
`src/core`.

S1 has zero ROM node and edge scope, expected matches and actual matches.  If
no product code remains changed, it needs no artifact refresh.  A retained
optimization requires a successor S with focused ROM-route/state evidence,
operational tests, platform-purity review and three refreshed local targets.

## S1 Result And Closure

### Measurement boundary

The assessment deliberately keeps three clocks separate.

| Boundary | Evidence | What it includes | Limit |
| --- | --- | --- | --- |
| Shared host route | Current x64 presentation probe, two completed repeated runs, 1,198 native-route frames each | translated game tick, shared PPU compositor, authored text scene, retained planar scale projection and snapshot capture | Modern host timing only; it does not describe DOS16 or a 486SX. |
| DOS16 device publication | Retained P58 PIT receipt, eighteen warm samples for each cache topology | palette submission, fifteen ordered 16-row PPU reads and direct chain-4 publication | DOSBox PIT evidence only; it is not physical-machine qualification. |
| DOS16 enclosing title step | Retained P59 PIT receipt | translated tick, PPU preparation/rebuild, composition and direct publication | Initial title construction only; cache rebuild bursts make it unsuitable as steady-play evidence. |

Input/control is sampled before `mysmb_game_tick`; the DOS audio adapter only
reports unavailable after the shared audio frame is produced; and pacing is an
intentional wait after the root step. None is a useful computational target:
removing or coalescing any of them would change input, sound-command or 60 Hz
frame semantics. The Windows root similarly retains one logical game tick
sequence before building a frame, then invalidates the window once.

### Current stage costs

The current x64 probe passed 2,048 randomized pixel-equality cases, cache
lifetime and priority guards, and 1,198 native-route frames on each completed
run. Its repeated range is below. These figures locate ownership on the host;
they are not extrapolated to DOS.

| Shared stage | x64 microseconds per native-route frame | Interpretation |
| --- | ---: | --- |
| `mysmb_game_tick` | 17.751--18.331 | Translated-game execution is small on this host. |
| `mysmb_ppu_frame_build_cached` | 182.251--185.621 | Largest measured shared computation. |
| `mysmb_text_scene_build` | 144.449--149.068 | Separate authored text preview cost; it is not paid by graphical Win32 or DOS graphics presentation. |
| `mysmb_vga_frame_build` retained scale projection | 105.635--106.967 | Test/legacy planar projection; not the current direct DOS publication path. |
| snapshot capture/cache update | 5.617--5.768 | Probe-only measurement; normal products capture only on P. |

The dense synthetic PPU comparison measured 302.112--360.720 microseconds for
the cached compositor, versus 470.384--482.698 for the uncached current
compositor and 3,153.699--3,267.495 for the reference implementation. The
cached shared path is therefore already the correct graphical computation
baseline. T35 separately established that a 1,234-byte scanline OAM schedule
made a dense shared workload about 24 percent slower, so it remains rejected.

For DOS16 graphics, the current root creates the same PPU slot view, supplies
fifteen 16-row bands in order and writes each band directly to the matching
chain-4 `A000:` aperture. The P58 publication interval was 15.30--17.29ms
across the five accepted cache states. Earlier buffered publication was
20.32--20.48ms; the direct path therefore already removed one full-frame copy.
VGA repeats stored rows to fill the selected 640x400 display, so no software
enlargement is present. The product must still produce 61,440 indexed pixels
per graphical frame; reducing that traffic requires a color, geometry or
frame-semantics change and is outside the product contract.

P59's 25.90ms no-cache title-construction step and 102.16--119.72ms cache-build
steps are retained as transient construction evidence only. They do not rank
steady gameplay and are not used to delete the accepted B -> A -> C cache
policy. Pacing remains outside both reported intervals.

Windows graphical presentation is one `StretchDIBits` call per paint from the
already-built indexed DIB to the current client rectangle. It has no extra
software scale buffer, no game-state access and no per-pixel Win32 call. The
current probe does not time the desktop compositor/GDI driver, so no numerical
Win32-driver claim is made. The only responsible follow-up would be an
optional platform-only paint timer if a reproducible Windows presentation
symptom is reported; it is not a reason to alter the shared compositor.

### Candidate register

| Candidate | Owner and applicability | Evidence and expected memory | Disposition |
| --- | --- | --- | --- |
| Rewrite translated core for DOS16 | Shared portable core, all targets | No stage evidence identifies the core as dominant; a DOS-only core would violate the architecture. | Rejected. |
| Add a scanline OAM schedule | Shared PPU, all graphical targets | +1,234B; T35 measured about 24 percent slower before VGA publication. | Rejected. |
| Remove more DOS framebuffer work | DOS16 device only | Direct chain-4 already removes the duplicate RAM-to-VGA copy; 61,440 exact indexed bytes remain required. | Rejected. |
| Change DOS resolution, reduce colors, or skip frames | DOS16 device/root | Could reduce traffic only by changing the pixel contract or logical-frame cadence. | Rejected. |
| Change B/A/C cache order or remove a tier | Shared PPU plus DOS allocation policy | P14/P60 remain the accepted route-scoped cache decision; this audit adds no contradicting steady-play evidence. | Rejected. |
| Optimize Win32 DIB presentation | `platform/win32` only | One GDI stretch per paint, no added buffer; no reproducible desktop cost was measured. | Deferred pending a concrete Windows paint-latency symptom and a platform-only timer. |
| Qualify 25MHz 486SX performance | Physical-DOS/M4 evidence only | DOSBox timing cannot answer physical CPU, VGA-bus or LCD behavior. | Deferred to the existing physical qualification package. |

S1 found no retained product optimization. It closes without source, ABI,
cache-policy, ROM-node, control-edge or executable changes. The finite outcome
is useful: future effort should not reopen the core or invent a new framebuffer
scheme without a measured, owner-observed platform bottleneck.
