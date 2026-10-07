# Windows Text Console Fit And Restore

Archived M3 T33 proposal. Owner directs autonomous completion through
closure after P2;original admission and delivery stages below are retained
as history. The final P3contract accepts the owner's earlier allowance for
Terminal Restore to retain native size and clip excess cells. Engineering
closure is not a claim of every Terminal/DPI physical visual result. Named
remaining physical-observation applicability is in TODO;no new active task.

## Problem And Owner Contract

The authored text scene is 80x50 cells. The owner previously observed a usable,
fully visible, approximately square-cell text window at 150% desktop scaling;
the remaining defect then was maximize followed by the caption Restore button.
That operation fell back to the graphical window rather than keeping the game
in text mode. Current Windows Terminal presentation preserves its native font
and viewport, so an 80x30 view clips 20 scene rows and a tall cell remains tall
when the user merely reduces font size. The earlier live visual appearance is
owner evidence, not proof that `SetCurrentConsoleFontEx` changed Terminal's
physical glyph metrics. Reproduce and distinguish those facts.

Both Windows Terminal and classic Console Host must remain usable. On entry,
try the prior Consolas 8x8 request for both hosts and measure what actually
happens; do not skip the attempt merely because of a host-name classification.
The same fit and lifetime policy applies to both; differences are expressed as
observed device capabilities rather than a hard-coded host-type decision.
Prefer a complete 80x50 view with approximately square cells. When the window
is smaller, fit cells down to the available view; when enlarged, grow them only
up to the normal 8x8 target. After Restore, recompute the fit for the restored
view and return to the prior size when the view is unchanged. If a host does not
honor programmatic font or geometry changes, preserve its settings and keep
text mode responsive while using the best verified presentation it supports.
Do not claim a clipped or vertically stretched view is a complete visual fix.

Tab alone requests a normal graphics/text presenter switch. Maximize, Restore,
minimize, font/viewport change, DPI change or an in-flight partial write must
not be interpreted as Tab, exit, game-state loss or persistent device failure.
Escape, close and genuine device loss keep their existing explicit behavior.
No global Windows default-terminal setting, user's unrelated Terminal profile,
shell state or system font is modified. Borrowed console settings changed by
the game must be restored on Tab, exit and error.

## Code Boundary And Investigation

- `src/platform/win32/text_console.c`: host capability probe and font request
  in `mysmb_win32_text_console_open`, classic geometry in
  `mysmb_win32_console_geometry`, Terminal viewport/write in
  `mysmb_win32_terminal_present`, and borrowed-host restoration in close.
- `src/platform/win32/text_console.h` and the Win32 root: replace the current
  `terminal` flag's multiple behavioral meanings with only the capabilities
  actually needed, such as usable host window, mutable font/viewport, and VT
  output. The `GetClassNameA("ConsoleWindowClass")`/caption/message-parent
  heuristic must no longer decide whether font fit is attempted, whether a
  resize is fatal, or which window may be shown. A console HWND is optional;
  input/output handles remain the health authority. Root code that currently
  branches on `g_console.terminal` must receive the corresponding explicit
  window capability instead of reintroducing a new host-name check.
- `src/platform/win32/main_win32.c`: `mysmb_win32_build_frame` currently folds
  every presentation failure into `g_text_failed`; the tick then calls
  `mysmb_win32_switch_presenter`. Separate a transient unavailable frame from
  confirmed permanent device loss so Restore never silently invokes Tab's
  presenter switch.
- `src/io/video.h` and `src/text/` continue to own the neutral 80x50 authored
  scene. Do not change ROM/game/PPU semantics or silently discard text rows.
  A smaller-host projection, if needed, is a separately measured presentation
  design with visual review, not a change to original game logic.

Compare the pre-S4 T29 implementation with `2959c348` and the T24 Restore
record. Do not revert the whole T29 commit: it also introduced bounded
asynchronous console acquisition and native Terminal RGB output. Reintroduce
only useful font/fit behavior after testing it on both actual hosts. Read back
requested and effective console metrics, visible rows/columns and write status,
but do not equate a successful or virtualized API readback with physical glyph
geometry. Keep observations under an ignored `build/` directory.

Keep one Win32 console-device owner and one resize/fit state machine. Probe
capabilities on the game's output buffer after saving borrowed-shell state;
never destructively test the user's shell buffer. A failed optional operation
does not make the device unusable. Use direct console-cell writes or VT output
according to verified output capability and fidelity, not a window class name.
Do not add a second policy engine, duplicate scene composition, a platform
dependency in `io/` or `text/`, or a wrapper that merely forwards the same
state. The output backend may differ, but the requested font target,
ready/defer/lost result, resize policy and Tab semantics must be shared.

## Proposed Delivery Cohorts

These are planning cohorts, not allocated S identifiers. Split or combine at
admission according to the measured dependency boundary.

1. **Baseline and capability experiment.** On the current x86/x64 products,
   record 150% DPI entry, maximize, caption Restore and repeated Tab routes in
   Windows Terminal and classic Console Host. Compare a contained pre-T29-S4
   8x8/80x50 request with current behavior. Capture actual visible frame,
   viewport, font-cell ratio, API results, latency and whether an in-flight
   write causes the graphical fallback. Also exercise borrowed CMD/PowerShell
   and fresh owned-console lifetimes. Do not adopt the experiment as a fix.
2. **Stable presenter lifetime.** Give presentation an explicit
   ready/defer/device-lost result. A temporarily zero, changing or clipped
   viewport, a bounded resize race and a partial write defer drawing without
   switching presenters. Confirmed invalid input/output handles or persistent
   failures use the existing recovery path. Avoid infinite retries, a busy
   loop, and suppression of a real close request. Audit every production caller
   of console presentation and the equivalent classic geometry path.
3. **Capability-based fit.** Remove the window-class-based behavior switch and
   audit every former use of the `terminal` flag, including root window
   activation, shell restoration, font/palette/geometry and output selection.
   On entry and after a settled size change, attempt
   the normal 8x8 target for either host, then smaller approximately square
   candidates only as needed to fit 80x50. Use measured effective dimensions
   and visible rows/columns; retain a last known good setting and restore the
   shell's saved state. Maximize may grow up to 8x8; Restore reapplies the fit
   for its view. Never mutate font/window geometry per video frame or force a
   Terminal resize that its owner does not support. If two output mechanisms
   remain, select by verified device ability and actual rendering fidelity;
   neither gets a separate game or fit policy.
4. **Terminal no-effect branch and acceptance.** If Terminal ignores the font
   request, preserve its font and retain responsive input/Tab/close through
   all resize cycles. Measure whether the complete 80x50 scene fits. If it
   does not, evaluate a bounded viewport-aware presentation or an opt-in
   game-specific Terminal profile; show the owner its exact visual result and
   any lost text detail before adopting it. A global default-terminal change,
   hidden clipping presented as success, or a separate GUI text clone is not
   presumed approved. Record the unresolved full-view limitation explicitly
   if no acceptable in-Terminal solution is demonstrated; do not declare the
   full product-experience objective met.

## Regression And Exit Contract

Use real maximize and caption Restore operations, not just synthetic
`SetWindowPos` resizing. Test at 100%, 150% and 200% DPI where available, with
small/restored/maximized views and repeated cycles. Check actual glyph aspect,
all 80 columns/50 rows when claimed, authored colors and Unicode glyphs, frame
continuity, the same running game state, responsive keyboard/audio, Tab in
both directions, Escape/close, fresh owned and borrowed shell restoration. A
user-visible actual-window check is necessary; console buffer readback and a
private-desktop probe alone cannot certify Terminal's visible font or Restore.
Add capability-matrix tests whose fake window class names do not determine
results: usable/unusable host HWND, accepted/no-effect font request,
resizeable/fixed viewport, direct/VT output, temporary write failure and true
handle loss. Verify the same high-level behavior for equivalent capabilities
on both real hosts. Compare before/after first text entry, maximum, Restore,
Tab return and borrowed-shell exit; reject a fix that improves one host by
regressing the other or weakening the existing game and window behavior.
Preserve current passing graphics, DOS16 behavior, snapshots, focus semantics
and T29 asynchronous acquisition. Product-code adoption requires focused
tests, x86/x64 native builds, DOS16 compilation and refreshed three local
products under the normal task rules; protected products stay local.

The task can close as a full visual repair only when both hosts retain text
mode across maximize/Restore, Tab switches intentionally, and the admitted
display-quality acceptance is visibly met without a regression from the
owner-observed earlier usable view. Report host-specific actual behavior and
remaining limits; no API success flag alone counts as visual acceptance.
This host-presentation task expects no ROM-node or control-edge credit:
scope/expected/actual are empty, new credit zero, with the then-current ledger
totals recorded at admission. No source material is imported.

## T33 S1 P1 delivered state

Implementation,three builds,focused/native and actual host-device tests are
committed and products published. Owner verification is pending;T33/S1remain
active and full visual closure is not claimed. Classic actual caption Restore
reports80x50/8x8. Current Terminal ignores the font request and retains80x30;
full-scene/physical glyph/Terminal caption acceptance remains explicitly open.
[Implementation evidence](M3-T33-windows-console-fit.md#s1-p1-implementation-and-delivery-awaiting-owner-visual-verification).

## T33 S1 P2 geometry correction

P1's HWND-gated entry geometry omitted a working T24operation sequence.
Same-host neutral and actual product probes now observe80x50after restoring
one optional all-device entry request;borrowed restoration and rollback pass.
Do not infer physical font geometry from readback. The earlier80x30delivery
state is historical;P2products supersede it. Owner live visual/Restore review
remains pending. [Correction](M3-T33-windows-console-fit.md#s1-p2-restore-the-actual-t24-geometry-contract).

## Final closure boundary

T33 S1 P3closes entry/Restore fit,transient recovery,full accepted-view glyph
fidelity,keyboard/presenter/shell lifetime and three-product delivery. Actual
classic caption and physical capture pass at150%DPI;default Terminal device
readback is80x50and actual product Tab/input/exit passes. Private notification
handles do not certify Terminal UI glyph aspect or its physical caption. That
observation is retained by name in TODO,not asserted passed and not a new
whole-project audit. Owner-directed closure supersedes the earlier wait-for-
owner lifecycle instruction;no human visual result is inferred.

## S2 corrective reopening and 80x25 design

Owner reopens the latest closed T33 at S2. S1 engineering receipts remain
historical. S2 P1 is current-source analysis and design only; the active packet
is CURRENT. No product code or EXE is changed by this P.

The owner accepts both latest-code GUI diagnostic 05 products, but rejects
console diagnostic 06 with detached allocation manifest. Both diagnostics
can pass device input and geometry readback; 06 still fails visible fit.
Neither virtualized 80x50 readback nor changing to 25 rows proves physical
Terminal fit, startup latency or caption Restore. Retain these as separate
acceptance clauses. Console subsystem remains a design preference; no helper
process or system setting is authorized as its workaround.

### Frozen source census and boundary

At source baseline 358beff9, elements.c contains 129 stored template entries
in 17 declarations, representing 46 presentation kinds. Small and large
player tables each have 17 pose entries; Luigi reuses their artwork. This is
a storage census, not the number of reachable kind/pose/palette combinations.
Background shapes are procedural and captions are separate consumers.

| Template declaration | Entries |
| --- | ---: |
| small / large | 17 / 17 |
| parts / flag_scores / jump_coins / scores | 3 / 5 / 4 / 11 |
| star_flag / actors / goomba_second / winged | 1 / 38 / 1 / 2 |
| fire_phases / explosions / springs / hammer_throw | 2 / 3 / 3 / 2 |
| egg_second / hammers / scenery | 1 / 4 / 15 |

All 129 entries require an explicit keep/redesign verdict. One-row scores,
fireballs and platforms can retain useful glyphs; multi-row art requires
compact redesign. Review every kind and state, not just Mario. Record aliases,
inversion, facing, clipped emergence and palette phases separately from art
storage. The owner's withdrawn standalone [full object/state gallery contract](M3-T33-text-gallery-transferred-proposal.md)
is now received by T33 at task level. This table and S2's bounded implementation
do not discharge its complete manifest, gallery, per-state review and disposition;
plan remaining cohorts through later admitted S work before T33 closure.

### Proposed shared layout

- Owner amendment: retain existing 80x50 code/artwork as a supported profile.
  Add 80x25 as default on all three targets, without a selection switch yet.
  Both consume the same immutable observations. Shared text owns the layout
  and art bank; hosts receive neutral dimensions/cells, never artwork policy.
  Reuse traversal/priority only where retained-profile equivalence is proven.
- Use an 80x25, 2000-cell neutral output for the new default. Preserve the
  whole 256x240 logical scene: X maps at 3.2 source pixels/cell, Y at 9.6.
  No bottom-half truncation, row dropping or conversion from an 80x50 bitmap.
- With approximately 1:2 physical cells, this grid has approximately the
  source aspect ratio. Font metrics are a host capability, not guaranteed.
  Win32 requests a normal approximately 8x16 cell only when supported; DOS
  uses its normal VGA 80x25 text mode. Unsupported host resizing retains
  responsive clipping without claiming the full view is visible.
- HUD has two information rows within the top approximately three scene
  rows. Preserve score, coins, world and timer; the lower scene uses the
  source's existing fixed/scroll split. Do not change original scroll writes.
- Small characters target roughly 5x2 cells; large characters roughly 5x3
  or 5x4, with crouch and defeat variants. Anchor footprints/heads to source
  bounds and check subcell vertical phases; never introduce gameplay motion.
  A 16-pixel terrain block spans one or two rows by its phase, about five
  columns. Pipes, steps and connected silhouettes need continuous boundaries.
- Captions must extract recognized information runs and lay out distinct
  source lines in distinct output rows. Directly projecting 30 tile rows
  into 25 can overwrite adjacent lines. Preserve all title/menu, lives,
  time-up, game-over, warp and ending words, including dynamic digits and
  floating scores. Reflow text using declared source bounds and scene output,
  not game-mode decisions or rerunning translated routines.
- Preserve committed palette changes, foreground/background distinction,
  OAM order, behind-background priority, visibility and clipping. A cell
  still has one glyph/foreground/background: fewer vertical details are an
  explicit design trade-off, not grounds to discard text or object states.

### Component inventory and migration cohorts

These are bounded implementation cohorts, not newly allocated S identifiers.
S2 is the active design S; later admission allocates actual receiving S.

| Cohort | Owners and expected scale | Required result |
| --- | --- | --- |
| Shared geometry and information | io/video.h; text/elements, actor_scene, background_scene and caption_scene; shared tests, about 200-400 changed lines initially | One dimension contract and safe signed projection; 250-byte opacity/claim masks; complete non-overlapping information text; no host-specific scene |
| Compact actor and effect art | text/elements and actor_scene, about 300-600 changed lines | Verdicts for 129 stored entries and source-selected state aliases; redesigned multi-row poses, palette roles, anchors and clipping; readable retainers and scores |
| Procedural scenery | text/background_scene and caption_scene, about 150-350 changed lines | Pipes, terrain, scenery and all connected forms audited at 25 rows, distinct fence/coral colors, foreground/background and small components preserved |
| Host integration and acceptance | platform/win32/text_console and platform/dos16/devices plus roots/tests, about 150-300 changed lines | 2000-cell output, correct DOS font/mode checks, borrowed-shell restoration, graphics/Tab/input/Restore, actual visible fit and console-startup defect disposition |

Estimates overlap and are planning ranges, not additive promised patch sizes.
Product changes refresh all three local EXEs using the existing toolchains;
pure design P1 does not. Retain accepted 05 and existing 80x50 products as
ignored comparison artifacts, and retain the 80x50 source profile in the
product. Separate compact/legacy art banks use shared observation contracts;
do not duplicate game state, observers or host-specific scene engines.
No changes belong in translated core, PPU writers or original observation
selectors. Snapshot receipts retain source decisions rather than cell arrays;
check their consumers and old-save compatibility before declaring invariance.

### Memory and performance estimate

The three-byte neutral frame shrinks from 12000 to 6000 bytes. Background
opacity and actor claim masks shrink from 500 to 250 bytes each. With the
other work arrays unchanged, the combined text frame/workspace is estimated
to shrink from 15400 to 8900 bytes, saving 6500 bytes. DOS currently shares
this storage with the 7680-byte graphical band requirement, which still fits;
confirm compiler sizeof/alignment and actual allocation before publishing a
memory result. These savings require selected-profile allocation rather than
reserving the largest frame or both frames; retaining 80x50 code alone must
not be reported as 6500 bytes saved. Account for both art banks' resident code
and data overhead. VGA text writes shrink from 8000 to 4000 bytes; Win32 output
visits half as many cells. These are work/storage bounds, not a measured 2x
FPS improvement; game ticks and graphical work remain unchanged.

### Acceptance and remaining clauses

1. Freeze and account for all 129 template entries, 46 kinds, procedural
   background families and information scenes. Enumerate reachable state
   variants in the gallery rather than multiplying arbitrary combinations.
2. Validate captions by exact expected strings and non-overlap, including
   every dynamic score. Validate geometry through all relevant anchor phases,
   partial emergence, inversion, mirroring, connected pipes and scene edges.
3. Compare shared x86/x64 cell outputs and retain DOS16 build compatibility;
   test rendering is read-only and graphical/state/snapshot output unchanged.
   Also compare retained 80x50 cells/colors with the source baseline, including
   captions, actor poses and connected backgrounds. No legacy regression is
   accepted merely because the new default looks satisfactory.
4. Exercise fresh and borrowed consoles, RDP-compatible input, repeated Tab,
   close/Escape and maximize/Restore. Use actual visual acceptance for all
   80x25 cells when claimed. Do not promote API readback to visual proof.
5. Resolve console-subsystem startup/Tab behavior independently. If a host
   ignores requested size/font, record its actual limit; 80x25 is not itself
   a fix for console allocation or delegation. Keep the known-good 05 path
   available as the isolated comparison, not a disguised shell-wait solution.

S2 P1 completes admission and this analysis. S2/T33 are still active; there is
no implementation or full visual closure. Empty ROM scope/forecast/credit;
historical mapping 1992/1992, local 1991/1992 nodes and 4260/4261 feasible
controls (raw 4342, infeasible 81) are unchanged. Full M2 certification remains
separate and incomplete. Source census and diagnostics stay under ignored
build; only neutral conclusions are tracked.

### S2 P2 complete sprite review catalogue

Owner requires three columns for every reviewed state: original pixel state,
current 80x50 colored character output, proposed 80x25 colored character art.
No candidate is adopted before its visual decision. All rows below are
pending, with suggested compact cell footprints, not approved dimensions.
Cell footprints are nominal: connected spans and source clipping vary.

| Kind ID | Object | State/color review | Compact proposal |
| --- | --- | --- | --- |
| 0 | Small Mario | All 17 player pose slots, left/right, normal/invincible and blink visibility | 5x2; distinguish face/cap, arms and foot phase |
| 1 | Large/fire Mario | Same pose slots, crouch, growth transition, mixed throw/kick components and palette changes | 5x4, crouch 5x2; cap/face/torso/legs |
| 2 | Goomba | Both walk phases, inversion, brown/scene palette | 5x2; colored cap, eyes and alternate feet |
| 3 | Growth / 1UP mushroom | Both item identities, emergence, palette | 5x2; spotted colored cap and light stalk |
| 4 | Moving brick/block | Bump displacement, active palette, clipping | 5x1 or 5x2 by phase; clear filled boundary |
| 5 | Coin | Static element alias, rotation/color variants where observed | 2x1 or 2x2; round/thin face |
| 6 | Pipe element | Legacy standalone template and scene pipe aliases | Variable width/height; continuous lip and shaft |
| 7 | Fire flower | Emergence, rotating palette, stem/body contrast | 5x2; flower head over green stem |
| 8 | Star | Rotating palette, partial visibility | 4x2; pointed outline and face |
| 9 | Player fireball | Two glyph phases, clipping | 1x1; alternating colored @ / * |
| 10 | Explosion | Three source phases | 1x1 then 3x1/3x2 burst |
| 11 | Hammer | Four orientations | 2x1/2x2; head and handle distinct |
| 12 | Brick chunk | Independently positioned fragments | 1x1; source-colored filled chip |
| 13 | Vine | Growing span, source components | 1-2 columns, variable height; alternating leaves |
| 14 | Platform | Full moving span, source widths | Variable width x1; single continuous top |
| 15 | Flag | Pole/cloth separation, descending/partial visibility | Cloth about 4x2; pole stays continuous |
| 16 | Bubble | Source positions, clipping | 1x1; light hollow circle on water |
| 17 | Flattened Goomba | Defeat flattening; distinct from inversion | 5x1; low brown cap |
| 18 | Shell | Turtle/beetle palettes, stationary/moving/revival/inverted visuals | 5x1/5x2; shell rim and revival face |
| 19 | Koopa | Red/green/dark source palettes, walk phases, inversion | 5x3; head, colored shell, alternating feet |
| 20 | Beetle | Walk phases, inverted defeat; shell uses kind 18 | 5x2; dark dome, eyes and feet |
| 21 | Bloober | Both selected phases and inversion | 5x2/5x3; mantle and contracting tentacles |
| 22 | Bullet Bill | Dedicated/ordinary producer aliases, facing | 5x2; nose, eye and casing |
| 23 | Fish / flying fish | Source fish identities/palettes, phases, inversion | 5x2; eye, tail and fin |
| 24 | Podoboo | Rising/falling and inverted source appearance | 3x2; flame outline |
| 25 | Piranha plant | Two mouth phases, partial emergence/retraction | 5x3; head, teeth and stem |
| 26 | Hammer Bro | Walk phases, two throws, inversion | 5x3; helmet, shell, arm and feet |
| 27 | Spiny | Walk phases, inversion | 5x2; spikes and alternating feet |
| 28 | Spiny egg | Two source graphics; symmetry is not whole-object inversion | 4x2; spikes and rounded egg |
| 29 | Lakitu | Two selected phases, cloud/body palette separation | 5x3; goggles above cloud |
| 30 | Bowser front | Both phases, source-facing/inversion handling | 5x3; head, mouth and forelegs |
| 31 | Bowser rear | Both phases, source join with front | 5x3; shell, tail and hindlegs |
| 32 | Bowser flame | Two source-selected phases | 7x1; pointed animated streak |
| 33 | Toad / Princess | Separate selected templates and castle palette roles | Toad 5x2/3, Princess 5x3; face and dress/cap must remain distinct |
| 34 | Spring | Three compression states | 5x2, 5x1 plus compressed mark |
| 35 | Spent block | Visible after use, source palette and displacement | 5x1/2; solid outlined block, never blank |
| 36 | Vine leaf | Individual positioned segment | 2x1; green leaf next to stem |
| 37 | Vine cap | Top component | 2x1; cap and stem |
| 38 | Platform part | Per-component priority/clipping in whole span | About 3x1; preserve continuous span |
| 39 | Flag score | Five literal score strings | 3-4x1; preserve readable digits, never mirror |
| 40 | Jump coin | Four rotation phases | 2x1/2; gold round/thin variants |
| 41 | Floating score | Eleven values including 1UP | 3-4x1; preserve exact text and contrast |
| 42 | Star flag | Separate star-flag source identity | 5x2; patterned cloth |
| 43 | Small Luigi | Same 17 pose slots, distinct identity/palette | Small-Mario geometry with own colors/mark |
| 44 | Large/fire Luigi | Large poses, crouch, partial throw/kick and palettes | Large-Mario geometry with own colors/mark |
| 45 | Winged Koopa | Red/green/dark source palettes, both wing phases, inversion | 5x3; distinguish wings from ordinary shell |

This accounts for all 46 current presentation kinds. Identity variants such
as Toad/Princess and growth/1UP are separate review cases inside their kinds.
Do not invent visible animation for different gameplay states that genuinely
share source graphics. Player pose slots are stand, run1, jump, skid, swim1,
climb1, crouch, throw, dead, run2, run3, swim2, swim3, climb2, swim-kick1,
swim-kick2, swim-kick3; aliases/unreachable slots must be recorded explicitly.
Palette/color changes, left/right, inversion, partial visibility and joins
are reviewed where source output supports them, not a blind Cartesian product.

Review order: players; mushrooms/flower/star/coins; common ground enemies and
shells; winged/water enemies; plant/Lakitu/Spiny/Bro; Bowser/flame/firebar;
retainers; projectiles/effects; connected components and information sprites.
Firebar is a producer family rendered through repeated fireball components,
not a missing new kind. Background-only question/hidden blocks, ground,
stairs, scenery and all caption scenes have a separate procedural review;
they are not NES actor sprites even though they are visible game objects.

Each review case records stable ID, source-selected graphics/OAM/palette,
fixture provenance, both old/new cells, nominal size, color roles, aliases and
owner decision: pending / accept / revise. Current first panel has eight
controlled Mario cases (small stand, three runs, jump; large stand, run1,
jump). Pixel reference decodes original local CHR using native OAM and
original PlayerColors. The middle column is actual existing renderer output,
including any clipping defect; it is not a cleaned-up template illustration.
The right column is a hand-authored draft with explicit colors, not sampling.
Enlarged cell-buffer panels are not screenshots or Terminal fit evidence.
Native fixtures do not independently certify original-ROM logic equivalence.

P2 creates local review panels and this catalogue only. Existing 80x50 source,
product EXEs, original game state and node/control classifications are unchanged.

P3 owner review rejects the initial Mario draft's invented bright-yellow
skin/detail color. All eight local comparison drafts now bind cap,skin and
lower-body roles to the fixture's original palette through the existing
shared text-color mapping. No contrast-driven hue substitution is accepted.
The owner requires maximum visual fidelity,including color placement and
relative area,not merely recognizable poses. V2 removes the invented yellow;
shape,16-color approximation and overall likeness remain pending review.
Existing 80x50 and products remain untouched. The original draft stays as
superseded local visual evidence,not an accepted design.

P4 owner review rejects compact run1's narrow leg spread and jump's missing
raised fist/separate feet. V3 redraws run1 with left/right feet separated by
a scene-background cell; jump has an explicit skin-colored lower-half-block
fist in the upper-right cell,raised arm and separately bent feet. Colors
remain source-palette-derived. The preview renderer now draws CP437 half/full
blocks as exact cell rectangles rather than font-dependent symbol outlines;
the middle column still consumes the unchanged 80x50 cell buffer.
Pose review must compare limb landmarks,direction,spacing and negative space,
not just the action label. V3 is pending owner review;no product adoption,
ROM-node promotion or 80x50 source change occurs.

P5 owner identifies the source's raised,right-side shoe pointing upward.
V4 moves that shoe above the left foot in both run1 and jump,using an upright
half-block and diagonal bent leg over the scene background rather than a
horizontal arrow or a second grounded shoe. This is a pending compact-art
proposal,not a verified product repair;existing source/EXEs remain unchanged.

P6 owner corrects the design method: colored masses carry the principal
silhouette and pose;ordinary characters supply only landmarks/edge details.
The review format is now four columns: original graphics,current 80x50,new
80x50,new 80x25. Current output remains the unchanged native cell receipt;
both new columns are pending hand-authored designs,not adopted products.
Large stand/run1/jump have separate semantic mass grids:5x7cells for the new
50-row art and5x4cells for25rows. Each cell is uniform or a two-color half
block;one eye detail uses an otherwise uniform skin cell. No pixel sampler
creates these grids. Color roles use the original source palette exactly in
the preview,avoiding the standard16-color mapper's gray approximation to
dark brown. This exposes a new acceptance clause:the neutral text palette
and DOS/Win32 device bindings must support these colors consistently before
adoption. The previews do not prove that current devices already support the
proposed palette. Do not change global Terminal settings or call a hardcoded
standard palette faithful. Both new art banks and palette binding require
review;the retained 80x50 source and all products remain unchanged.

P7 owner requests ordinary character accents on the accepted color-mass
direction. V7 retains the mass silhouettes and adds cap mark/brim,eye,
moustache/back-head edge,overall straps/buttons,fist and upturned-shoe marks
where uniform cells allow them. A mark replaces a uniform cell only,keeping
one foreground/background pair;no third-color overlay over a half-block is
pretended representable. Original/current columns remain unchanged. New50
has more landmark cells than new25;both are still pending visual review and
native palette integration. All three four-column states render locally;
no product or ROM logic change occurs.

P8 owner explicitly accepts V7's reviewed large-Mario stand/run1/jump
designs (M06,M07,M08),both new50/new25. This is visual design acceptance,
not native palette integration or approval of all other player poses.
The next group contains ten source-bound item cases: I01 growth mushroom,
I02 1UP,I03-I06 flower palette phases,I07-I10 star palette phases. All are
pending owner review. Native DrawPowerUp/OAM and the original ground-palette
command provide reference colors;the unchanged text renderer supplies the
current50 column. Local fixture checks observe one drawn actor and zero
unsupported cases for each of ten states. New50 uses5x4cells,new25 uses5x2;
semantic masses distinguish mushroom cap/spots/stalk,flower outer rim/inner
ring/core from its independently colored stem,and star outline/eye marks.
Every cell remains a two-color glyph;all four flower/star phases are rendered
in the supplementary panel. Emergence/partial clipping and alternate scene
palettes remain separate pending review cases. No new product code,ROM
equivalence credit or published EXE is introduced by this design P.

### P9 accepted item designs and remaining batch

Owner accepts the reviewed item gallery: I01-I10,including both new50/new25
profiles and all four displayed flower/star palette phases. Partial emergence
and scene-specific variants still require placement/visibility checks;
do not report this visual acceptance as product adoption or ROM proof.
Together with M06-M08,this is13accepted controlled-state review IDs,not13ROM
nodes or all player/item states. No new product code is changed.

Owner requests one remaining batch rather than repeated single-family turns.
The complete46-kind catalogue above owns the identities and detailed state
scope. The grouped remainder and proposed visual decisions are:

| Review cohort | Remaining scope | Proposed visual emphasis |
| --- | --- | --- |
| Player variants | Small Mario;large/fire poses beyond the three accepted cases;Luigi sizes/poses;growth,swim,climb,skid,crouch,throw,death and palette variants | Reuse accepted masses/accents;each actual source pose changes limb landmarks,not merely its label |
| Coins and blocks | Coin/jump-coin phases;question/hidden/spent blocks;bump and shatter | Rotating gold silhouettes,literal question mark,solid visible spent block,colored fragments |
| Common enemies | Goomba walk/flat/inverted;red/green/dark Koopa;winged Koopa;shell movement/revival/inversion;Beetle | Cap/eyes/feet,shell-color identity,wings and separate defeat silhouettes |
| Water/flying enemies | Bloober,fish/flying fish,Bullet Bill | Tentacle/fin/tail silhouettes,eyes and source-facing nose |
| Special enemies | Piranha,Hammer Bro,Lakitu,Spiny/egg,Podoboo | Mouth/head/stem,helmet/throwing arm,goggles/cloud,spikes,flame contours |
| Boss and retainers | Bowser front/rear and flame;Toad/Princess | Joined shell/body/head,opening mouth,flame direction;cap versus hair/crown/dress and face |
| Projectiles/effects | Fireball phases,explosion stages,firebar segments,hammer orientations,chunks,bubbles | Distinct small color masses;character marks only clarify motion/outline |
| Connected dynamic objects | Vine/cap/leaves,platform/parts,spring stages,flag/star-flag | Continuous colored spans,source component positions and compressed spring states |
| Information sprites | Floating scores,flag scores,1UP | Preserve exact readable text over the current scene;never replace with blocks |
| Background objects | Pipes/orientations,ground/stairs/bricks,clouds/bushes/hills,water/coral,tree/fence/ledges,castle/cannon,rope/pulley/chain/axe/flags | Foreground/background distinction,continuous boundaries,source colors;pink coral over water and light fence separate from ground |
| Information scenes | HUD,title/menu,lives,time-up,game-over,warp,ending/world-select | All source information and dynamic digits retained without line collisions |

Each future batch panel retains the four-column format and stable case IDs.
Accepted designs remain reference anchors;the remainder is pending actual
visual review. Design-pattern approval cannot silently approve unseen cases
or hardware palette/input/geometry behavior. Keep native/gameplay fixtures
distinct from descriptor-only proposals. Existing50code stays unchanged.

P10 produces the remaining dynamic-element batch:53controlled native source
states R01-R53,with nine four-column pages and a local browsable index. It
covers Goomba walk/flat/inversion;green/red Koopa and winged forms;colored
and inverted shells;Beetle/Bloober/fish/Bill;plant mouth phases;Bro walk/throw;
Lakitu/Spiny/egg/Podoboo;Toad/Princess;three spring stages;Bowser front/rear;
two fireball phases,three explosions,four hammer angles,two flames;vine,
small/large platforms,brick/spent block,fragments and six firebar components.
Native fixtures report52single-actor cases and one six-component firebar
case,with zero unsupported observations. The reference is native OAM with
original CHR and explicit ground/water/castle/Bowser palette bindings,not an
independent original-ROM gameplay replay. New art is independently authored
semantic color masses plus representable character landmarks.

Review before publication catches and corrects proposal eye marks placed on
feet,missing pose distinctions,incorrect effect-core hue and disconnected
small-platform spans. Current50is not repaired:the flat-Goomba fixture has
no visible character cells despite a recognized receipt,and its panel labels
that limitation. This needs a named clipping/anchor follow-up before product
adoption;no finding expands ROM certification credit. Each panel is bounded
to its column and has a content-dependent row height;fragments use a bounded
controlled spatial fixture. All53designs are pending owner review.
Background/terrain,information scenes/score sprites and remaining player
poses are still outside this batch;do not call the full46-kind review closed.
Protected panels/raw fixtures and local tools remain in ignored build. No
product change or three-EXE refresh is required for this design-only P.

P11 owner finds R31-R33 spring proposals unsatisfactory and requests stronger
object-specific character/foreground accents across the generally promising
batch. This is feedback,not approval of all53cases. Spring V2 preserves red
end plates and source-gold diagonal/curved coil characters on scene-colored
interior;white vertical highlights are used only from the original palette.
Extended,intermediate and compressed profiles have distinct heights. Thin
plate half-blocks replace the bulky opaque white/red tube interpretation.
The spring panel remains pending owner review. Other accent opportunities
are shell pattern,fish eye/tail,Bill eye/casing,Piranha mouth/teeth,Bro hand,
Lakitu goggles/cloud,retainer face/dress and effect centers. Add only useful
source-aligned landmarks with a legitimate two-color cell;do not uniformly
outline every mass or silently promote unseen refinements to accepted art.
Retained current50and all formal products remain unchanged.

### S2 P12 implementation and local play-test delivery

Owner authorizes implementation and requests the spring's original white
side highlights. Default text is now80x25on DOS16/Win32/x64. The legacy50-row
interface/artwork remains;no user-facing layout selector is introduced.
Shared text owns compact semantic art,palette binding,projection,priority and
captions. Hosts own font/mode,neutral RGB submission and console lifetime.
No translated core/PPU source changes or ROM-node/control credit occur.

The neutral frame retains4000-cell capacity for50-row compatibility,with
selected rows,16RGB colors and a64-entry color map. Default output consumes
2000cells;retained capacity means this delivery does not claim6000bytes of
resident storage savings. Source colors exceeding16unique resident entries
use nearest RGB fallback. Windows VT uses explicit RGB;classic palettes are
programmed where supported with standard-color fallback otherwise. DOS VGA
programs the same neutral palette and uses16-pixel text font for25rows.
Old50-row construction initializes the original standard palette.

Compact projection uses source object bounds and committed ownership rather
than requiring each coarse cell center to land inside an8-pixel sprite.
This retains small components and partial ownership,with the same background
priority masks. Caption lines that collide after projection receive distinct
available rows. Information sprites remain literal words. Spring three-state
art includes white side blocks and gold wire accents;source-selected palette
phases remain live. Unreviewed scene/pose details remain subject to the
transferred complete-gallery contract and owner play review.

The owner flags black blue-sky lettering and missing question marks during
implementation. RGB-distance contrast incorrectly favored black on blue;
custom contrast now keeps light information text on blue/dark scenes. A
one/two-row block was entirely classified as border,so its question mark
could never execute;compact information marks now precede that edge decision.
Tests cover16vertical phases,blue-sky white ink and adjacent caption lines.
Actual native game captures show white HUD and visible question marks.

Further owner play feedback exposes two presentation omissions. The Windows
VT writer still interpreted custom palette slots through the standard16
palette, producing wrong colors. It now emits the frame's explicit RGB
foreground/background and resets SGR before output;the capability test checks
actual emitted bytes for custom and retained legacy colors. The compact
player selector also aliased three running poses to one artwork. Each small
and large Mario/Luigi running phase now has distinct limbs,including both
facing directions. Original source pose selection,animation timing,movement
and game/PPU state remain untouched. Native source-selected three-frame
comparisons cover all four player/size identities and both directions.
The similar-issue sweep includes the retained50-row selector,other compact
pose families,VT and classic palette submission,and DOS neutral palette output.
The53legacy cases remain byte-identical;no further palette-owner omission
is identified within this sweep. Physical-host and broader gallery acceptance
remain pending rather than being inferred from these tests.

Verification:

- Each Windows width passes20focused checks:compact/legacy text,IO,PPU,row
  output,snapshot,keyboard,launch,console capability,DOS root,purity and native
  self-test. The strengthened compact case additionally passes110kind/pose
  proposals,64RGB fallback cases,palette/capacity/read-only and16question-block
  phases. A borrowed-frame regression exposed uninitialized metadata padding;
  deterministic metadata initialization fixes it without removing the test.
- All53retained legacy actor cell buffers remain byte-identical. Actual
  compact fixtures have53nonblank outputs. A1200-frame native title/gameplay
  route checks renderer read-only state and exports six local cell captures.
  This is operational evidence,not independent original-ROM equivalence.
- Both actual stripped Windows products retain identical non-debug PE sections
  to their builds and pass three text entries,two Tab returns and Escape on a
  private desktop. Current host reports80x25/2000cells. Notification handles
  do not prove Terminal physical font/caption behavior;owner acceptance stays
  open. Interactive CMD waits,reuses text,accepts Tab both ways and resumes
  shell input after exit on both widths,without a helper process.
- Original OpenNT DOS16 compiler/linker and memory checks pass:EXE320681B,
  DGROUP51472including2048stack,14064headroom,logical loader343952..348048B
  excluding dynamic allocations. No hardware performance/stack-high-water
  qualification is inferred. Stock DOSBox configuration hash is unchanged;
  no CPU/core/resolution tuning. Actual product enters25-row text,accepts
  Enter into the world/lives screen and Escape returns to DOS. Slow stock
  startup required delayed input;no gameplay-speed qualification is claimed.

Local products:mysmb16.exe320681B,mysmb32.exe330766B,mysmb64.exe346126B.
They are delivered under assets for owner testing;protected derived products
remain local under the current source policy. Neutral receipts/logs/probes
and images remain below ignored build. Source/documentation submission does
not stage these existing tracked binaries.

S2 remains active awaiting owner play feedback;T33 is not closed. The broader
complete state/background/information gallery remains a task-level obligation.
Reviewed delivery spans32source/test/build/document files,approximately
842added and119removed lines before this size note;production changes are
under the neutral IO/text owners and the two host components. No game or PPU
implementation file is changed. The gallery proposal transfer is preserved.
Historical mapping1992/1992,local1991/1992nodes and4260/4261feasible controls
(raw4342,infeasible81) are unchanged,new credit0. Full M2certification remains
incomplete. No remote is configured;source commits are local.

## S2 Owner Acceptance And T33 Closure

Owner reports the delivered result perfect/successful and explicitly closes
T33,then requests the next queue task. Accept default80x25 and retained80x50,
white information text,question marks,source-bound colors,spring highlights
and distinct running phases under the observed play conditions. Source
delivery is f7ff2b2f,32files,+846/-119lines; three current local product hashes
and sizes are bound in the T34 admission record. Each Windows width20checks,
53legacy byte-identical cells,1200read-only native frames,actual Tab/CMD routes
and original DOS build/stock-config startup/text/input/exit evidence are retained.
This documentation closure rebuilds no EXE and changes no product code.

S2/T33 close by owner-directed acceptance. The transferred complete-gallery
contract was not exhaustively reviewed:53remaining-object fixture cases and
approved player/power-up groups are retained,not a complete reachable-state
census. Its unresolved full pose/background/information inventory remains
explicitly deferred as TEXT-GALLERY-REMAINDER in TODO under this closure
mandate. Do not call unreviewed rows visually approved. Physical host/all-DPI
and486SX qualification likewise are not inferred from owner acceptance.

No ROM-node custody changes or promotions. Historical1992/1992,local1991/1992
nodes and4260/4261feasible controls,raw4342/infeasible81,new0. M2 final
certification remains incomplete. T34 S1 receives only native VGA work; no
character redesign or whole-ROM audit is folded into its scope.
