# M3 T32 S5-S9 proposal: DOS graphics performance beyond Nesticle

Owner-directed continuation within the current M3 T32, divided into five
consecutive S tasks, S5 through S9. None is admitted; `states/CURRENT.md`
retains S4 as the sole active packet. S5 follows S4 only after its actual
closure or an explicit owner-directed transfer with named receiving
obligations. Each later S follows the preceding S's scoped closure and a fresh
packet. These S tasks add a comparative graphics-performance gate to T32;
they do not retroactively weaken or close S4's five memory/cadence clauses or
the suspended Windows startup dependency. This is not a separate queue T and
receives no new T identifier.

## Objective and measured starting point

Make the existing 16-bit DOS MySMB executable render and advance SMB1 more
efficiently than the owner-supplied DOS Nesticle on the same DOSBox CPU budget,
without skipping game ticks, visible frames, source rows, colors, or input.
At equal sustained 60 game updates and 60 submitted display frames per second,
MySMB must require fewer fixed DOSBox cycles than Nesticle. Report the exact
thresholds and uncertainty; equality or an unverified default frameskip does
not satisfy the objective. Qualify representative title, ordinary play,
scrolling, dense sprites, death, and area transitions rather than one idle scene.

The initial headless comparison used DOSBox 0.74-3 dynamic core at fixed 20000
cycles, the same owner-local SMB1 content, and no audible output. At 22-34
seconds after launch the Nesticle HUD timer fell from 360 to 330 (about 60
game updates per second); the then-current 301609-byte MySMB DOS build fell
from 398 to 392 (about 12 updates per second). A repeat with the then-current
301145-byte S3 MySMB DOS binary (SHA-256
`B9624E4BDC7D192E0B9E19B1A36DDD6B941A0E28470D1B0069B63D6E290D1851`)
and the same DOSBox settings found HUD timer 400 at wall second 16, 398 at
22, 395 at 28, and 392 at 34: about 10.7 game updates per wall second over
18 seconds. That S3 binary has since been superseded by the S4 P6 DOS build
(300725 bytes); the comparison must be repeated against the S5 admission
product. This is still a stationary early-level scene. The HUD is a game-update proxy, not a displayed
frame counter. The two executables used different guest video modes: Nesticle
256x240; MySMB 320x400 logical pixels scanned as 640x400. The comparison
establishes a real configured-playability gap, not a proven compositor-only
fivefold ratio or equal-display proof. MySMB reached near-normal update cadence
with `cycles=max` in a separate headless check, which is not acceptance.

The current T32 S4 P1 MySMB graphics diagnostic totals 648.2154 ms: PPU
composition 393.2317 ms (60.66%), indexed-to-VGA mapping 197.5818 ms
(30.48%), VGA submission 28.8070 ms, game 9.1771 ms and snapshot/cache
10.4494 ms. These are
diagnostic phase costs, not product FPS. Current DOS presentation rebuilds
256x240 indexed rows, expands to 320x400, submits four VGA planes in 25
16-row bands, and scans the sprite list once per band. Removing mapping alone
cannot plausibly close the measured gap. No claim about Nesticle's internal
renderer is made without direct evidence.

The owner supplied the proprietary freeware NESticle x.xx ZIP for local
comparison (ZIP SHA-256 `00f5b3fa3a8ba3e23d86d8feae36ec3684b43495aa62b63864e816b022c8fb47`;
EXE SHA-256 `224e348e1fd5c11b16ef096ff5607c7c57c49d65fa7e4dbbc9b2a5c9c53e832b`).
Its bundled README identifies C++/assembly, DOS4GW, 256x240 mode, manual/auto
frameskip and lack of mid-frame palette changes. A bounded string inspection
of the owner-supplied binary finds a Settings-menu `Tile caching` toggle.
An isolated DOSBox GUI check confirms it is checked by default and can be
unchecked. With the same binary, ROM, 256x240 mode, fixed 20000 cycles,
`-frameskip 1`, no audible output and scripted start, the checked run's HUD
timer fell 356->287 from wall seconds 20->38 (69 timer units); unchecked fell
378->338 (40 units). At 24 game updates per timer unit, this is about 92 vs
53 updates/second, or 1.73x throughput in the stationary first-level scene.
This single paired run is preliminary evidence of a cache-option effect on
game updates, not a measured
display-frame count or proof of the cache's internal representation. The
unchecked Nesticle result was about five times that S3 MySMB update rate
at this CPU setting, but `-frameskip 1` may submit fewer video frames than
MySMB; this is not an equal-frame speed ratio. MySMB
already caches decoded CHR rows, so the option does not imply MySMB has no
tile caching. S5 must repeat moving/dense routes and count display submissions
before generalizing the gain.
The reference executable and owner ROM remain local research inputs below
ignored `build/`; no third-party code or protected data is imported.

Owner-authorized, read-only inspection of the historical source tree at
`https://github.com/athros/NESticle` (repository `master`, `Source/`) adds an
architectural lead, not a source-bound proof for the x.xx executable. The tree
describes itself as a 1997 leak; its `LICENSE` contains only a Bloodlust
copyright notice and grants no redistribution rights. `Source/MAIN.CPP`
identifies this tree as version 0.2, whereas the measured owner binary is
x.xx. No source bytes were imported into MySMB or stored in tracked files.
The inspection purpose was to identify historical rendering organization and
compare it with the measured current MySMB phases. Exact-version behavior
must still be verified from the x.xx executable or observation.

In that 0.2 tree, `Source/NESVIDEO.CPP` and `Source/NESVIDEO.H` show a two-level
cache: NES pattern bits are decoded into 8x8 byte tiles, while each real
32x30 nametable has a 256x240 surface whose dirty flags track individual
tile writes and 4x4-tile attribute effects. `Source/NES.CPP` connects PPU
name/attribute writes to those flags. Background drawing refreshes only dirty
tiles and blits clipped scrolling regions from the surfaces; a tile-by-tile
fallback is present when the active pattern-table mapping differs. The frame
draws background-behind-sprites, sprites, then foreground-priority background.
`Source/TILE.ASM` has a flat 32-bit, unclipped 8x8 fast path with two DWORD
stores per tile row, and `Source/SPRITEBG.ASM` checks an already produced
destination pixel's encoded opacity before writing a behind-background
sprite. The palette-index encoding also lets palette changes update the
display palette rather than recolor all tile pixels. These are conceptual
comparators only; x.xx may have changed any of them, and MySMB must preserve
its own exact frame contract. Two full real nametable surfaces would cost
122,880 bytes before metadata, so a DOS16 adaptation needs an explicit far
memory and startup budget or a smaller bounded cache.

## Boundaries for S5-S9

- Keep original translated game logic, RAM/OAM/PPU state transitions, audio
  commands, input timing, sprite priority, masks, scroll, palette and frame
  output exact. Optimize presentation or pure composition only; no ROM-logic
  shortcut, fake timer, adaptive lost frame, or reduced drawing frequency.
- Primary product remains the DOS16 executable and the common 256x240 indexed
  video contract. A 256x240 VGA presentation may be prototyped to make the
  comparison resolution-matched, provided the current 640x400 presentation
  remains available until the owner reviews the display tradeoff. A mode or
  toolchain change is not silently charged to active S4.
- Preserve Win32 x86/x64 behavior and buildability, DOS memory/startup limits,
  2048-byte stack unless independently proved otherwise, and platform/IO/PPU
  ownership. No new ROM, third-party source, bundled DOS4GW, helper process,
  undocumented protected fixture, or committed derived image/EXE.
- These are M3 T32 presentation/performance S tasks, not M2 certification.
  Expected ROM-node labels and control relations are `[]`; expected new node
  and control credit is zero for each of S5-S9. At each admission, copy current
  historical/current counters and register this zero-credit responsibility in
  the node/task ledger without transferring node custody.

## Proposed consecutive S tasks

S5-S9 are planned identifiers within T32, not completed or simultaneously
admitted work. Each S receives its own packet, source-size and memory estimate,
exact files, tests and P breakdown at admission. The successor may be amended
when the preceding measurement changes the best implementation boundary.
No S overlaps S4 or another active S.

1. **S5, comparable benchmark and bottleneck receipt.** Estimate 0 product
   lines and 100-250 contained probe/harness lines. Pin both EXE hashes,
   owner-local ROM identity, DOSBox version/core/settings, sound/input route,
   guest resolution, actual submitted frame counts, game updates, and
   transitions. Establish Nesticle's explicit frameskip behavior or mark the
   equal-frame comparison unproved. Measure minimum fixed cycles sustaining
   60/60 across each route; instrument MySMB game, PPU, mapping, VGA submission,
   per-frame snapshot capture/cache, and wait separately. The DOS root currently
   serializes a 9999-byte snapshot and copies its cache on each running frame;
   quantify this separately rather than charging it to the compositor. Keep
   captures/traces below ignored `build/`, delete raw
   protected images after bounded analysis. Decision: a reproducible phase
   budget and fair comparator before accepting a speed claim.
2. **S6, dominant PPU composition.** Estimate 80-240 candidate product lines,
   subject to S5 findings, in `src/ppu/` and focused tests. Investigate
   reusable background tile/row work, scroll and dirty-region updates,
   band-invariant sprite classification and opacity lookup. Measure a
   palette-slot/opacity intermediate that can test behind-background priority
   without recomputing the background for each candidate sprite pixel, while
   preserving the public 256x240 indexed-color contract. Existing decoded
   CHR caching is baseline, not a new gain. Each candidate must beat the
   original DOS compiler's generated cost without unacceptable near/far,
   stack, or resident-memory growth. Verify exact indexed frames and state on
   title, split/status, scrolling, palette, sprite priority, dense, and
   fallback routes; reject a cache if its invalidation cannot be proved.
3. **S7, DOS display path.** Estimate 60-180 candidate product lines in
   `src/platform/dos16/`, VGA presentation and their IO adapter, plus focused
   tests. Compare existing 320x400 plane packing and a resolution-matched
   256x240 VGA route with exact palette/indexed pixels. Count VRAM bytes,
   plane selects, port writes, band calls, conversion time, mode behavior and
   peak memory. Preserve the existing mode pending owner display review;
   choose a product default only with an explicit, measurable presentation
   decision. Do not attribute removed scaling cost to a PPU speedup.
4. **S8, integrated 16-bit cost reduction.** Estimate 40-160 candidate product
   lines only where S5-S7 profiles still show a material deficit. Inspect
   original DOS compiler listings, far-pointer and call traffic, render
   buffer lifetimes, and any measured per-frame snapshot overhead. Compare
   bounded loop/data-layout variants under the
   original toolchain and memory limits. A 32-bit DOS port or toolchain change
   requires its own explicit scope decision; it is not a substitute for
   meeting the DOS16 target. Keep any demonstrably beneficial candidate only
   after exact-output and three-product verification.
5. **S9, final acceptance audit and T32 closure.** This is the original
   proposal's fifth and last stage. Estimate 0-150 contained audit/harness
   lines and zero product lines. A finding returns to its owning S for repair;
   S9 does not implement fixes or claim their acceptance without rerunning the
   affected audit.
   Rebuild/refresh DOS16, Win32 x86 and x64 after adopted product changes.
   Run the pinned repeated workload matrix, count game updates and actual
   display submissions, compare representative exact output and user-visible
   pacing, find both minimum sustained-60/60 cycle thresholds, and report
   confidence intervals, source/product bindings, peak startup/resident/stack
   evidence, S4's remaining named gates and all rejected approaches. Verify
   real DOSBox play with input and scene changes. The
   owner may review a resolution/display default separately. Do not close as
   "faster than Nesticle" unless the measured equal-frame threshold is lower.

## Admission and evidence gates

Owner approved this plan, then clarified the boundary: S4 fixes and closes
its repairable known runtime/memory/evidence defects first. S5-S8 implement
the measured performance work. S9 is combined final audit, not a receiver for
unfinished known repairs. The proposed blanket S4 five-gate transfer is
withdrawn. S4 was active at P8; current P12 closes its repair stage and admits S5. See the
[S4 P8 correction](../../history/M3-T32-rendering-performance-continuation.md#s4-p8-correction-and-owner-directed-responsibility-boundary).
Current three products need no refresh without further product-code changes.

Planning may use the retained local benchmark summary. New ROM or third-party
research requires the relevant active S packet's provenance, license/redistributability,
purpose, containment and verification record under the source policy.
Benchmark captures and binaries remain ignored and local. Each S admission
names exact components, estimated and actual changed lines, memory budget,
zero node-label scope, analogous defect sweep, focused byte/output cases and
three-product delivery. Every S closure records expected and actual zero
node/control credit. T32 closure reconciles S4's actual disposition, exact
source and product identities, meaningful per-phase savings, equal-frame
comparator, actual DOS playability, and any still-open 486SX qualification (M4).

## Current S5 admission after S4 repair closure

[S4 P12](../../history/M3-T32-rendering-performance-continuation.md#s4-p12-staged-closure-and-s5-admission)
records the exact division: known envp and evidence defects repaired in S4;
S5 measures and S6-S8 fix performance; S9 performs the named unproved
integration checks only. No final gate is passed by handoff. At P12 S5 was active,
S6-S8 planned and S9 holds final audit checks. T19 remains suspended; current
large-workarea ordinary startup passes without claiming its full repair.
S5 estimates0product/100-250contained harness lines and no resident growth.

## S5 current measurement and S6 candidate boundary

[S5 P2 counted measurement](../../history/M3-T32-rendering-performance-continuation.md#s5-p2-current-counted-phase-budget)
binds the current product owners/objects and separates actual update calls
from completed submissions. Default-config counter-only running graphics/
text medians are634.259/452.101ms;instrumented phase shares put graphics PPU/
mapping at60.64%/30.47%,snapshot1.61%. These are diagnostic budgets,not product
FPS or reference-speed acceptance. Broader dense/scroll/death and fair
equal-submission reference thresholds remain explicit final-work obligations.
S6's bounded first cohort should test temporary coarse-row span preparation
(up to198near bytes,zero resident cache) and sprite-row/classification reuse.
Estimate80-240candidate product lines as before;require original-DOS listing,
stack/loader audit and byte-exact raw/cached/band output before adoption.

## Current S6 admission

[S5 P3 closure/S6 packet](../../history/M3-T32-rendering-performance-continuation.md#s5-p3-baseline-budget-closure-and-s6-admission)
closes the baseline phase-budget/comparator-disposition decision contract,
not the unproved reference/minimum-cycle/full-route acceptance. Those remain
explicit S9 requirements. S6 is active;S7-S9 planned. S6 first cohort is
temporary coarse-row span and sprite-work reuse in the shared pure PPU,
80-240candidate product lines/up to198temporary near bytes/no new resident
cache absent budget amendment, with exact fallback/output and DOS stack/cost
checks. Candidate validation must cover the broader scenes before adoption.

## Owner-directed systemic revision of S6-S8

Owner rejects incremental single-digit-percentage optimization.
[S6 P1 comparison](../../history/M3-T32-rendering-performance-continuation.md#s6-p1-systemic-comparison-and-rejected-incremental-direction)
records cache/representation/assembly differences and an approximate87.8%
PPU+mapping reduction needed for fivefold overall at fixed other costs.
Initial prototypes stay unadopted. This section supersedes the temporary-span/
sprite cohort as the implementation direction.

S6 investigates persistent composed-background caching, once-per-frame
invalidation and opacity/palette-slot representation under the shared PPU.
Original CPU/game/PPU writers and timing remain untouched. Compare122880-byte
full surfaces with approximately63488-byte compact slot/source storage and
smaller alternatives;no resident storage adoption without measured original
DOS startup/heap/stack/output proof. New memory estimates require explicit
prototype budget amendments before use, not silent allocation.
S7 owns bulk segment-efficient scaling/packing/device transfer at640x400;
S8 owns integrated system-level speed/memory acceptance. No toolchain or
protected-mode switch, helper process, crop, lost frame, reduced color or
copied implementation substitutes for DOS16. S9 remains final audit;source
comparison alone proves neither equal-framex.xx performance nor ROM semantics.

## S6 compact-cache result and next memory tier

[S6 P2](../../history/M3-T32-rendering-performance-continuation.md#s6-p2-compact-persistent-background-prototype)
implements63488-byte packed slot/source caching only below build. Native
512-state/mutation/lifetime/guard and original-DOS pixel tests pass; warm PPU
ratios1.478-1.643, cold1920tiles1.986seconds at unchanged diagnostic settings.
No fivefold/full-product memory/playability acceptance;EXEs remain P11.
Next local budget may compare122880master-color bytes plus15360raw opacity,
2048source and16palette bytes (140304before small fields), palette-group and
universal-color invalidation, and separately bounded far blocks. Test actual
DOS startup/resident/fallback and cold/steady/transition costs before adoption;
retain compact/smaller tiers in the tradeoff. No source timing/state changes.

## Approved compact adoption

Owner approves the63488-byte compact tier and its measured warm PPU benefit.
[S6 P3](../../history/M3-T32-rendering-performance-continuation.md#s6-p3-owner-approved-compact-cache-adoption)
integrates it in shared PPU with optional DOS allocation and uncached fallback,
plus explicit synchronous prepared views. Product startup/input/restore/Tab/
save/exit, actual conventional-memory observations and three builds are its
acceptance scope. The140304-byte byte-surface comparison remains unadopted.
Neither the compact benchmark nor these routes establish fivefold whole-game
speed, global stack bounds or physical486qualification;those named gates
remain with S8/S9. S7 retains segment-efficient VGA packing/transfer scope.

## Current S7 admission after scoped S6 closure

[S6 P4 closure/S7 packet](../../history/M3-T32-rendering-performance-continuation.md#s6-p4-bound-coststack-evidence-and-scoped-closure)
closes the owner-approved compact-cache contract with product-bound compiler
and cost evidence. S7 alone is active:segment-efficient320x400plane packing/
transfer with unchanged640x400scanout,portable fallback and zero new resident
storage. Estimate80-180candidate product and80-160test/harness lines. First
prototype segment-once packing,verify exact full/band output and ABI/stack,
measure whole-stage cost before product adoption. S8/S9 named integration and
final checks remain planned/open;no fivefold or global-stack acceptance claim.

## S7 selected packing candidate

[S7 P1](../../history/M3-T32-rendering-performance-continuation.md#s7-p1-segment-once-packing-prototype)
passes original-DOS pixel/register/guard tests and native fallback matrices.
Controlled entire plane-packing stage is1.926times faster with zero new
persistent storage;helper own stack12bytes. Select for product integration,
not acceptance of overall game speed. P2 must bind current product listings,
refresh all three EXEs and verify actual game/snapshot/presenter/memory routes.

## Owner-directed platform layout

[S7 P3](../../history/M3-T32-rendering-performance-continuation.md#s7-p3-owner-directed-two-component-platform-layout)
implements the owner's stricter boundary:platform has only dos16/win32;
shared formats/services are IO and the retired sampler is validation-only.
DOS-private row execution is supplied explicitly by the composition root,
without an IO-to-platform dependency. Component,host-import and declaration
guards prevent recurrence. Original game/PPU state and output semantics stay
unchanged;the measured0.36%packing overhead is retained as integration cost,
not hidden by another performance claim. S8/S9 obligations remain open.

## Current S8 admission

[S7 P4 budget/closure](../../history/M3-T32-rendering-performance-continuation.md#s7-p4-current-integrated-budget-and-scoped-closure)
records current counter-only405.309ms graphics and unresolved60Hz/fivefold
target. S7 display stage closes;S8 alone is active for integrated rendering
reduction. First cohort combines dirty-cache rejection and packed palette-pair
expansion under shared PPU/neutral IO/DOS-private bulk ownership. Estimate
160-300candidate product lines,prototype530byte optional near workspace plus
small binding fields;no extra far surface. No adoption until exact output,
current compiler/stack/resident/startup/cost evidence. S9 final gates stay open.

## S8 selected combined candidate

[S8 P1](../../history/M3-T32-rendering-performance-continuation.md#s8-p1-combined-dirty-cache-and-pair-expansion-prototype)
passes native512state and original-DOS pixel/2064primitive/local-stack checks.
Controlled full-PPU benefit2.205/2.233/1.510times versus current compact cache,
530byte optional near workspace,PPU workspace+8DOS bytes. Select combined
dirty rejection/pair expansion for P2 integration under the existing budget.
No extra surface or game/PPU semantic change;all DOS execution under dos16.
Actual product/fallback/global budgets and full-frame benefit remain unproved;
three EXEs refresh only after product-code adoption. S8/S9 remain unfinished.

## Current safe rendering build policy

[S8 P3](../../history/M3-T32-rendering-performance-continuation.md#s8-p3-original-compiler-safe-render-generation)
selects original8.00x safe optimization only for five rendering units. Core,
IRQ,input,clock,roots and startup retain original flags and core execution
records. Process-local short PATH fixes historical optimizer driver overflow;
no system/compiler change. Actual output/routes and measured footprint support
adoption,while252.089ms current diagnostic still fails nominal60Hz/fivefold.
Global stack/reference/continuous memory/physical486 gates stay open.
