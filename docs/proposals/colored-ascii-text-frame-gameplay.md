# M3 T11: colored ASCII text-frame gameplay and presentation switching

Owner scheduling amendment (P153):remaining M2 acceptance verification is
queued after the three I/O/presentation candidates. Earlier proof completion
prerequisites are superseded by this explicit order;retain scoped evidence and
rebind affected dependencies at admission. This does not certify M2.

## Purpose and queue position

Replace the common I/O text placeholder with a playable 80x50 character
scene. Each cell has a printable ASCII character and foreground/background
color. The same cell grid feeds the DOS16 text-mode adapter and the Win32
console adapter. Implement bidirectional switching between DOS16 graphics and
text modes, and between the one Win32 GUI executable's graphical window and
its console window. This is M3 T11,admitted from the queue head,
after the shared I/O graphic-frame task and the queued quick-snapshot task.
Its S slots below are a forecast, not admitted work or ROM-node credit.

The preceding I/O task establishes the 256x240 graphic-frame path, a stable
`src/io` boundary, an inert 80x50 text-frame type, and an operational DOS16
graphical executable. It does not need to provide playable text or a mode
switch. This candidate turns that placeholder into the second presentation
without altering the translated game's 60 Hz logic, original RAM semantics,
controller meaning, audio command order, or the graphical output.

## Shared text picture

`src/io` owns the neutral bounded 80x50 cell contract. The shared
`game/presentation/text` owner performs element/template-to-cell conversion. A cell contains one 7-bit printable ASCII code (`0x20`-`0x7e`)
and portable foreground/background color values. The mapping must be legible
without color and improve recognition with color. It draws the title/menu,
world and HUD, terrain and interactive blocks, Mario/Luigi, enemies,
projectiles, moving objects, effects, pause, death, and end-state scenes from
game-owned identities and visible state. Priority, clipping, scrolling,
animation, and object disappearance follow the current game frame. Do not
derive characters from pixel luminance or make the text renderer infer game
logic from a low-resolution bitmap.

The admission design first identifies the existing neutral scene/object
commands or read-only game state needed for those identities. Any additional
read-only presentation data crosses an explicit shared contract; it must not
duplicate ROM control flow or become a second gameplay model. Text-frame
storage and conversion must fit DOS16's memory model without a large stack
allocation or a segment-unsafe array access. Both hosts consume identical
cell contents before adapting color attributes to their display APIs.

## Runtime switching

- Use Tab as the owner-selected common presentation toggle. DOS16 changes between its supported
  graphics mode and VGA 80x50 text mode in one executable. Win32 keeps one
  GUI-subsystem executable and one game/audio instance, showing a real console
  text window in text mode and returning to its graphical window on Tab.
- Switching changes only the active presenter and physical-key source. It
  neither resets the game nor adds/skips a logical tick, replays APU writes,
  changes pause/Enter semantics, or duplicates audio output. Only the active
  presenter performs device writes; no BIOS mode reset occurs every frame.
- A focus transition caused by the program's own window switch must not
  synthesize START or consume keys from another application. Held Tab is one
  toggle. Console close/detach and unavailable 80x50 mode have safe behavior:
  return to or retain the working graphical presentation without disturbing
  gameplay. Existing P/O snapshot shortcuts remain available in both views.

## Planned S decomposition

| Planned S | Bounded deliverable | ROM-node scope / expected new matches |
| --- | --- | --- |
| S1 | Audit game-visible semantic sources; fix the `src/io` 80x50 cell, color, layering, scrolling, and ASCII glyph contract with bounded DOS16 storage. | 0 / 0 |
| S2 | Implement deterministic object-aware terrain, actor, effect, and HUD-to-cell conversion with focused overlap, clipping, color, and monochrome-legibility checks. | 0 / 0 |
| S3 | Complete title/menu, pause, death, warp, and terminal text scenes; verify representative full-route frame sequences against the game-owned visible state. | 0 / 0 |
| S4 | Implement DOS16 graphical/text-mode Tab switching and 80x50 text presentation with safe mode setup, keyboard continuity, and real DOS runtime checks. | 0 / 0 |
| S5 | Implement Win32 GUI/console Tab switching in one executable, console cell/color output, focus/input transfer, close/failure recovery, and audio continuity on x86/x64. | 0 / 0 |
| S6 | Run integrated DOS16 and Win32 playable text routes, graphics/text round trips, snapshot P/O in both modes, frame/audio continuity, 16-bit memory/performance, and three-target regression. | 0 / 0 |

At admission, rebase the S forecast against the completed I/O and snapshot
contracts and register each infrastructure S with exact empty ROM-node scope
and zero expected matches. A discovered translated-logic mismatch needs its
own source-proof owner; this text presentation earns no ROM-node or graph-edge
credit by looking similar to the original graphics.

## Acceptance

1. DOS16 and Win32 display the same deterministic 80x50 ASCII/color cell
   scene for the same game state. The scene remains readable without color and
   covers title, sustained gameplay, major object interactions, pause, death,
   and completion, rather than showing a placeholder or a luminance filter.
2. Tab switches DOS16 graphics/text and Win32 GUI/console in both directions
   during gameplay. The game, audio, input, and frame count continue across
   repeated switches; returning to graphics reproduces the current 256x240
   frame rather than restarting or displaying stale pixels.
3. Console focus, held keys, Enter/pause, P/O snapshots, console closure, and
   unavailable text-mode setup behave safely and do not create a second game
   instance or double-submit a game tick or audio event.
4. Focused cell-rendering and mode-transition tests, Win32 x86/x64 builds and
   interactive checks, the real DOS16 link and graphics-capable DOS runtime
   route, platform-purity review, and 16-bit memory/performance checks pass.
   Owner-local ROM data and derived output remain local and untracked.

## S1 admission and source audit

Owner continuation admits M3 T11 after T10. S1 owns the semantic-source audit
and neutral bounded scene/text foundation;S2-S6 remain planned. ROM scope and
expected matches are[],new0. Historical1992/1992,local1991/1992nodes,
4260/4261feasible controls and42/952facets remain scoped and unchanged.

Existing sources have concrete gaps. `game/render` copies only nametable0,
uses current player/enemy RAM rather than committed visible OAM,has an
ambiguous player/enemy identity0 and only five enemy slots. It cannot supply
a complete animated scene. The old `platform/text` sampler is80x25 and
samples PPU pixels;it remains a dormant compatibility target during S1 and
will not become the new production converter. `io/video` already defines
4000three-byte foreground/background cells but supplies no rendering.

Owner steering narrows the current P to feasibility research first. No source,
ABI, artwork or mode-switch implementation is admitted by this research step.
The earlier tile/sprite-part classifier and 1152-primitive layout are withdrawn
as selected designs: recognizing individual graphics parts does not establish
whole-element identity or pose. Automatic successor admission waits for the
research outcome to be incorporated into the implementation scope.

### Element-driven feasibility findings

Research uses the existing project-owned C architecture only; no additional
ROM, disassembly, trace or external source is imported. This is a source-reading
conclusion, not a runtime or exhaustive coverage claim.

| Area | Existing source and finding | Proposed presentation approach / remaining obligation |
| --- | --- | --- |
| Player | `game/oam/player_gfx.c` already selects action, size, facing, animation, throwing and swimming details. Some selection routines mutate animation/scratch state. | Observe the existing completed draw decision; never call the selector again from text rendering. Use authored whole-player pose templates. |
| Enemies and items | `game/oam/oam.h`, `normal_enemy_gfx.c` and `power_up_gfx.c` expose typed draw owners, including special power-up slot five. Sprite tile IDs alone are ambiguous. | Record kind, selected pose, facing, colors and bounds at their draw owners. Composite objects such as Bowser and firebars need explicit part ownership. |
| Visible frame | `boot.c` submits backing OAM into visible OAM at the NMI boundary; `frame_root.c` does this before the subsequent gameplay producers run. | Latch element metadata with that same transfer. Final OAM overwrites, hidden rows, slot shuffling and clipping must determine visible parts. Current RAM alone is insufficient. |
| Background | `area.c` constructs scenery/terrain metatiles, expands them into staged graphics, and filters collision-buffer entries. `frame_root.c` later commits VRAM commands. | Preserve element identity across staging and commit, or prove a lossless semantic reconstruction from committed metatiles. Group pipe/cloud/grass pieces into whole elements before selecting text templates. Collision buffers cannot supply scenery or hidden-block visibility. |
| HUD and screen split | `ppu_frame.c` consumes committed scroll, masks, nametables and the fixed top region. | Use the same visible split and scroll. Decode source-owned text symbols into text; do not sample pixels or move the HUD with the world. |
| Snapshot | `app/game_snapshot.c` serializes game/visible output but has no new semantic sidecar. | Prove metadata reconstruction on restore, or explicitly version and serialize the required producer/visible presentation metadata. No claim of zero snapshot changes is justified yet. |
| DOS memory | `io/video.h` defines 4000 three-byte cells: 12000 bytes before any auxiliary data. | Use bounded separate far allocations and integer C90 arithmetic. Descriptor capacity and total live-memory budget require measurement; no large stack or DGROUP allocation. |

Recommended ownership is: game-owned observers and element interpretation,
then a neutral semantic scene contract, then a shared template compositor and
identical 80x50 cell output, then DOS/Win32 device presenters. `io` owns only
neutral geometry/color/cell operations; game-specific identity, pose mapping
and templates remain in the shared game presentation owner. Platform adapters
contain neither element recognition nor gameplay decisions.

Observation is presentation-only: it must not change original RAM, rerun AI,
collision, animation or random selection, or change OAM/VRAM/audio output.
Producer/visible buffers need explicit lifetime and reset/restore ownership;
there must be no implicit mutable global or second gameplay model.

At 80x50, a 16x16 source footprint spans about 5 by 3.3 cells, and a 16x32
player spans about 5 by 6.7 cells. That supports recognizable authored poses,
colored body fills and character outlines, but not pixel-detail preservation.
Tiny projectiles need a representative glyph. Original coordinates stay exact
in game state; only presentation is quantized. Console font aspect and moving
subcell positions need visual checks. The existing 80x25 sampler is not reused.

The work is feasible as a new shared element presentation path, not as a small
replacement of a pixel conversion table. Actor metadata, committed background
semantics, template coverage, snapshot continuity and DOS storage are the
bounded design obligations before full implementation. 486SX throughput is
unmeasured; feasibility does not promise 60 Hz on that machine.

Research acceptance records the sources, viable ownership and outstanding
obligations above. No product code changed, no fresh executable is required,
and no ROM node/edge/facet receives new credit. The subsequent S1 implementation
estimate must be revised after choosing metadata lifetime and restore design.

## S1 implementation amendment

Owner approves isolated implementation after the feasibility review. This P
adds bounded immutable element descriptors and authored whole-element templates
under game/presentation/text, with only the neutral IO cell contract as a
dependency. Pilot templates cover small/large player poses, Goomba, mushroom,
brick, coin and pipe. Descriptor order is explicit painter order; source pixel
coordinates remain caller-owned. Transparent template positions leave earlier
cells intact; body positions carry foreground and background fill.

The standalone S1 test uses project-authored descriptors, not live RAM, tiles
or a pixel sampler. It cannot claim production frame synchronization. S2 owns
observers at existing draw decisions, producer/visible latching, final OAM
visibility and background commits, plus restore handling. Original game
routines, struct, compositor, snapshot and hosts are unchanged in S1.

Estimate: three new source/test files plus CMake and governance,250-350 lines.
Focused x86/x64 tests cover template pose,mirror,negative clipping,layering,
colored fill,invalid-domain atomicity and input immutability. The existing
OpenNT16 compiler checks the new unit;three local product builds are refreshed.
No external materials are imported and no ROM conformance credit is added.

## S1 closure

The isolated foundation is implemented: three new source/test files260 lines,
CMake six lines and original DOS build probe five lines. Seven element kinds
and three player poses use authored templates, explicit color fill, horizontal
mirror and painter order. Signed-short coordinate extrema use bounded long
projection; negative coordinates floor correctly. Capacity64 and the12000-byte
frame are caller-owned; no heap/global game state or frame-sized stack exists
in production. Test-only static storage is separate from product storage.

Both x86 and x64 pass four focused tests: text-elements, IO contract, game
snapshot and platform purity. C90 warnings-as-errors compilation and the real
OpenNT16 large-model/far-pointer compilation pass. Original DOS product link
and both graphical Windows targets pass. Refreshed local products are byte
identical to the incoming products:DOS324239,x86394405,x64408431bytes. This
establishes that the dormant foundation is not linked into or changing those
products; it is not proof of future observer non-interference. Local preview
and build receipts remain in ignored build/m3-t11-s1. No external art, ROM
bytes or derived asset was added to source.

Review/similar-issue sweep: the new owner includes only its header and the IO
cell contract; it has no original-state, graphics selector, collision, host or
snapshot access. Old pixel sampling remains isolated and unused. Invalid
kind/pose/color/facing/count/pointer inputs reject before clearing output.
Input immutability, player pose distinction, mirror, fill, negative/extreme
clipping and overlapping painter order pass. Only player templates currently
have pose variants; enemy animation, terrain assembly and semantic visibility
are unfinished S2/S3 coverage. Pilot art is not yet owner-tested in live play.

S1 closes its amended standalone scope. Scope/expected/actual labels are empty;
historical1992/1992,local1991/1992nodes,4260/4261feasible controls,42/952facets
remain unchanged. T11 remains open. S2 must connect source decisions and
visible latches without rerunning game selectors, handle restore lifetime and
prove unchanged RAM/OAM/VRAM/audio under enabled/disabled observation before
calling text frames game-synchronized. Tab switching remains S4/S5, not an
existing feature in the three executables. No Git remote is configured.

## S2 admission

Automatic continuation after reviewed S1 closure, under the owner's existing
mandate. Scope: shared game presentation observation and visible-scene assembly,
including actor draw-decision families, final OAM visibility/ownership,
background commit identity, HUD split/scroll and restore lifetime. Templates
must consume already-selected source results, never repeat action selection.
Tab presenter switching remains S4/S5. Original ROM node scope/expected/new
matches are empty/empty/zero; prior local evidence counters remain unchanged.

Before source edits, choose bounded producer/visible storage and explicit
snapshot restore handling, enumerate every draw-owner hit and disposition,
and identify the smallest observation sites needed. Estimated10-18source/test/
build files,600-1000lines;amend visibly if the census changes this bound.
Verify disabled/enabled observation produces identical original state,
OAM/VRAM/palette/audio and pixels over the same input route;also verify visible
latching,overwritten/clipped slots,hidden-block visibility,scroll and restore.
Compile both native widths and the original DOS16 toolchain,refresh all three
local products on source change and run purity/governance gates. No claim of
live text completeness precedes this evidence. S2 remains active,not closed.

### S2 P1 bounded observation step

P1 establishes optional per-instance producer/visible observation buffers and
hooks only completed player,ordinary EnemyGfxHandler/convenience Goomba and
power-up draws. Source-selected graphics offsets and raw identities are
recorded without translating them into a second animation state machine.
Final OAM entry snapshots travel with each observation;visible masks reject
changed/hidden entries. Capture resets when backing OAM is cleared and commits
at the same DMA boundary. Embedded bounded storage avoids global bindings or
host-pointer lifetime and will be measured with the real16-bit compiler.

The original4782-byte snapshot schema is unchanged in this P. A successful
restore explicitly invalidates observer buffers while preserving enablement;
rejected restores do not touch them. This prevents stale descriptions but does
not yet supply text for the immediate loaded frame. S2 remains open until
persistent/reconstructible metadata,background/HUD and all draw-owner coverage
are reconciled. No roots enable observation or show a text mode in this P.

Remaining draw census includes fireball/explosion,firebar,hammer,block/chunks,
vine,platform,flagpole,Bowser-specific,fireworks,bubble and retainer paths;
background area metatiles/replacements and title/HUD writers need their own
commit ownership. Existing ordinary EnemyGfxHandler covers multiple enemy
families,not every dedicated convenience owner. No family is silently deemed
covered from sharing a tile. P1 tests include source-bound twin-game output
comparison and controlled final-entry overwrite/latch/restore cases.

### S2 P1 review receipt

P1 completes the bounded observer step,not S2 closure. Three new source/test
files289lines plus40added/1removed integration/build lines establish1413-byte
per-instance buffers. Completed decision receipts capture source identity,
selection token,facing,size and final OAM entries. Producer/visible lifetime,
source-entry ownership and overwritten/hidden/blank masks are exercised.
Ordinary enemy selection captures its graphics index before the draw helpers
advance it. Player swimming's early return also records the completed output.
No root enables observation;default graphical products retain original output.

Both widths pass eight focused tests plus the actual-product hidden-window
self-test. The owner-resource-bound1000-step twin route records730running
frames,801visible-player and1003visible-enemy observations with zero original
core/frame/pixel differences. All four power-up types have controlled draw
fixtures with identical RAM and correct visible masks. Capacity overflow,
disabled capture,late overwrite,entry ownership,DMA phase,clearing and failed/
successful restore dispositions pass. These are finite native non-interference
checks,not new original-ROM equivalence proof or exhaustive path coverage.

Original DOS16 compile/link passes;DGROUP through stack spans41696bytes.
Actual hidden DOSBox56-second route passes title,Start,24seconds gameplay,
run/jump/left/release and Escape exit. This is not486SX speed qualification.
Refreshed local products:DOS326127,x86396559,x64410615bytes. Raw BMPs and
continuation streams/saves are deleted after neutral receipts are retained.

The graphics-file census has21files:four hooked in P1,seventeen dedicated
owners still need disposition. This file count is not a node/pose coverage
metric. Normal EnemyGfxHandler serves multiple families;its hook does not
certify every alternate convenience writer. Remaining S2 work is:

- Reconcile all dedicated draw owners and unobserved OAM overwrite/clear sites.
  Mixed player throw/swim rows retain final entry bytes,but per-part template
  interpretation is still pending;one final selection token alone is not a
  complete mixed-pose description.
- Assemble committed terrain/scenery,Hud split/scroll and element templates;
  no live80x50scene is produced by P1.
- Preserve or reconstruct producer/visible metadata on restore. P1 merely
  invalidates it,so it cannot display immediate loaded text correctly yet.
- Complete visible clipping/priority and the full-scope non-interference/
  storage/route matrix before closing S2 or admitting S3.

Historical mapping1992/1992,local1991/1992nodes,4260/4261feasible controls and
42/952facets remain unchanged. S2 stays active;no labels transfer or promote.

### S2 P2 scope amendment

Continue the same S with typed projectile/firebar/explosion,hammer,block/chunk,
vine,platform,flag and bubble receipts. Capacity becomes64,with reuse of fully
superseded receipts:at most64records can retain OAM entry ownership. This
expands per-game observer storage to5253bytes;real DOS DGROUP must be checked
before acceptance. Existing16record assumption was insufficient for multiple
segmented firebars plus actors/effects. Family-specific selection tokens are
recorded at already-selected draw results;no additional game decisions occur.
P2 refreshes three products and repeats non-interference/restore tests. Scene
assembly,background/HUD,remaining dedicated enemies and restore persistence
remain inside S2. The earlier10-18file forecast is amended to25-35files for
whole S2 because dedicated draw ownership cannot be inferred from ordinary
EnemyGfxHandler;estimated600-1000lines remains provisional.

### S2 P2 review receipt

Twelve source/test files change88added/8removed lines. Typed observations now
include projectile/firebar/explosion,hammer,block/chunks,vine,small/large
platform,flag and bubble owners. The gfx-file census now has hooks in12/21files;
this is integration-site accounting,not whole-family animation proof. Dedicated
alternate enemies and intermediate player output remain to be reconciled.
The64-record producer reuses wholly superseded entries before capacity checks;
a controlled64-entry saturation/replacement fixture passes. Per-instance
observer storage is5253bytes;DOS DGROUP through stack is45536bytes.

Both widths pass five focused tests including product self-test,C90 strict
compilation,and1000-step twin output comparison:zero original core/frame/pixel
differences. New controlled fireball/explosion/hammer/block/chunk fixtures
compare RAM and require typed visible receipts. OriginalDOS16 compile/link
and the actual hiddenDOSBox title/Start/run/jump/left/release/Escape route pass.
Three local products refreshed:DOS327503,x86397583,x64411639bytes. No ROM credit.
Raw captures stay local and are removed after the neutral receipt is retained.

P2 is complete;S2 remains open. Next work must produce a committed-background/
HUD and observed-actor80x50scene,resolve remaining dedicated writers and
snapshot metadata continuity. Generic per-sprite glyph substitution is not an
acceptable replacement for authored whole-element templates. Tab remains
S4/S5. Historical1992/1992,local1991/1992nodes,4260/4261feasible controls and
42/952facets retain their prior scoped meanings.
