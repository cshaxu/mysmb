# Retained Presentation Performance Qualification

## Purpose

M3 T39 continues performance work after closed T38. It preserves T38 S18's
accepted current-background sprite-union presenter and has zero ROM-node and
control-edge scope. The task first investigates why the owner-observed
NESticle reference is stable where the current DOS product visibly flickers
and stalls; it then uses only independently derived, compatible ideas to
qualify further MySMB work.

## Third-party research boundary

S1 may copy the owner-provided historical 1997 NESticle source archive into
an ignored `build/` directory. It is an unredistributable research reference:
no third-party source, binary, ROM, generated output, assembly, data table or
translation may be committed, copied, transliterated or linked into MySMB.
The receipt records archive/source identity only in ignored local evidence and
tracks neutral findings in the eventual closure record. Its exact purpose is
to inspect the video presentation, cache invalidation, sprite priority and
frame submission mechanisms, and to compare their cost model with the current
MySMB PPU and DOS device boundary. S1 may build the identified historical
source with a temporary compatible toolchain and run an isolated standard-VGA benchmark harness assembled from its CPU/PPU/video sources against the owner-local SMB input, entirely below `build/`.
It cannot alter DOSBox's persistent settings or become an implementation
dependency. Third-party source, binary, runtime, toolchain and generated
output remain local research material and are never committed or distributed.

Historical public 0.2-source observations are context only. The S1 archive
must identify itself before conclusions are attributed to it; source-version
claims and binary-version claims remain distinct.

## Planned S sequence

| S | bounded owner | completion condition |
| --- | --- | --- |
| S1 | Read-only source/probe comparison of the owner-provided historical NESticle video pipeline and MySMB's selected retained presenter. | Archive/version receipt; concrete render/cache/transfer findings; a compatible/rejected opportunity matrix; zero product edits. |
| S2 | Batch the retained fixed-HUD commit by VGA plane in `platform/dos16`; restore and packed byte ownership remain unchanged. | Exact retained-A000 oracle, shared-PPU/ROM-state regression, PIT measurement and refreshed three artifacts if source changes. |
| S3 | Extend the source-matched physical-work census across title, normal gameplay, transition, dense-sprite and underwater/castle routes. | One reproducible census matrix with HUD, repair, sprite, cache and plane-selection counts; no product-policy change. |
| S4 | Use S2 timing and S3 workload evidence to decide whether sprite-repair plane batching clears its measured threshold; implement it only if it does. | Recorded accept/reject decision; if accepted, exact A000 oracle, PIT evidence and refreshed artifacts; if rejected, no speculative source edit. |
| S5 | Re-evaluate a back-buffer or background-composition design only after S2--S4, against the measured retained route and conventional-memory budget. | Explicit feasible/rejected decision with final-pixel, memory and cadence constraints; no unmeasured RAM-surface rewrite. |

The prior private `cycles=max` result remains diagnostic only. It cannot be
compared with fixed-3000 evidence. S1 does not reopen S18 exactness, change game/PPU policy, reduce cadence,
skip frames, change output dimensions, introduce DOS4GW or a 32-bit DOS
dependency into MySMB, add a helper process, or alter a persistent DOSBox
configuration. DOS4GW may exist only inside the ignored third-party build/run
containment needed to establish the historical comparison.

## Owner-approved S2--S5 admission plan

The owner selected the four candidate steps below in this order.  They are
separate S tasks because each has a distinct evidence question and a later
choice depends on the prior result.  They retain zero ROM nodes and zero
control edges: the translated core, shared PPU state, PPU frame view, game
cadence and final visible frame are all outside their edit authority.

### S2 -- fixed HUD plane batching

- **Owner and likely change:** `src/platform/dos16/devices.c` only.  Replace
  the current one-line-at-a-time plane selection in `retained_hud_rows` with
  a plane-selected outer loop that writes the same 32 rows.  It may reuse
  existing 8KiB HUD buffers but may not allocate a new resident frame surface.
- **Expected size:** one DOS16 source owner and its focused test/probe support;
  approximately 40--100 changed source lines, before evidence files below
  ignored `build/`.
- **Acceptance:** compare all retained A000 bytes and VGA end state on the
  existing 260-frame physical route; retain shared-PPU inputs and exact
  x86/x64 behavior; measure a fixed-3000 PIT delta.  A source change refreshes
  `mysmb16.exe`, `mysmb32.exe` and `mysmb64.exe` locally.
- **Stop/transfer:** a byte or device-state difference, or no defensible
  measurement fixture, rejects the source change and transfers the unresolved
  performance question to S5; it must not be hidden by altered cadence.

### S3 -- multi-stage work census

- **Owner and likely change:** ignored source-matched DOS16 probe/instrumented
  fixture under `build/` and neutral proposal evidence only; no product source
  change is planned.
- **Expected size:** no tracked C change; one census table covering stable
  title, normal gameplay, screen/pipe or area transition, a dense-sprite
  sequence, and a water or castle scene if their routes are reproducible.
- **Acceptance:** every row identifies warm-up, sample frame count, game mode
  and task, plus HUD restore/commit bytes, changed background bytes,
  repair-tile bytes, active OAM tiles, nontransparent sprite bytes and plane
  selections.  Unreachable categories are recorded as such, not replaced with
  synthetic claims.
- **Stop/transfer:** if a named game phase cannot be reached reproducibly, the
  census states that limit; S4 may decide only from observed routes and cannot
  claim a global sprite result.

### S4 -- sprite-repair decision and conditional batching

- **Owner and likely change:** `src/platform/dos16/devices.c`, specifically
  the retained repair path, only after S2 and S3 show a material residual
  plane-selection or time cost.  No shared PPU/compositor or core edit is in
  scope.
- **Decision rule:** accept implementation only when the measured residual
  work and a bounded design can plausibly remove at least 20 percent of the
  remaining DOS16 presenter interval without additional resident memory; else
  document a rejection.
- **Acceptance if implemented:** preserve tile traversal, viewport wrapping,
  slot selection and final A000 bytes; pass fixed-cycle PIT comparison,
  physical oracle and target builds; refresh all three local artifacts.
- **Acceptance if rejected:** preserve the current source and record the
  actual counts/timing that make the return insufficient.

### S5 -- buffered-composition feasibility re-evaluation

- **Owner and likely change:** initially read-only device/memory design work.
  No product source change is admitted by this S merely to repeat the rejected
  61,440-byte staging experiment.
- **Question:** after plane batching, can a distinct visible-page, retrace
  handoff or compact background-composition arrangement remove transient A000
  updates while remaining within the owner's roughly 500KiB conventional-memory
  preference and preserving every presentation tick?
- **Acceptance:** exact memory accounting, VGA-memory/page feasibility,
  final-pixel equivalence boundary and fixed-cycle comparison against S2/S4.
  It may recommend one later implementation S or reject the design; neither
  outcome changes shared game/PPU behavior.
## S1 research result: historical NESticle video pipeline

S1 inspected two strictly local-only inputs below ignored build output: the
owner-provided x.xx binary package and a read-only historical source tree at
public revision `7ede7dab54bc0cef85774b424025a7d6b8133d28`. The owner archive
hash matches the earlier local binary receipt. It contains only the executable
and README; it is not source. The source tree's own front end identifies
version 0.2, so its render architecture is evidence about that historical
source line, not proof of the x.xx binary's exact implementation.

### Direct source facts

- A `natablecache` owns a 256x240 surface per real nametable. It records
  per-tile and per-line dirty flags. A nametable byte write dirties one tile;
  an attribute write dirties its affected 4x4 tile region. Cache refresh locks
  a surface only if a dirty line exists, redraws only marked 8x8 tiles, then
  clears those marks.
- Every displayed background section first attempts a clipped blit from those
  cached surfaces. It falls back to tile drawing only when its selected pattern
  table differs. Pattern-table changes are converted to affected-tile marks,
  rather than forcing the entire surface to be repainted.
- Palette-slot information is stored in the cached pixels. Palette refresh
  updates only marked entries of a 32-entry palette; it does not recolor every
  cached background pixel.
- Moving objects are still redrawn every displayed frame: the video draw path
  does background-behind-sprites, then walks all 64 sprites in descending
  order, then draws foreground-priority background. Therefore NESticle does
  **not** become smooth by leaving Mario unchanged; the background cache is
  what removes most of the static-world reconstruction work.
- The visible tile and sprite fast paths use flat 32-bit assembly (`.486`,
  `MODEL flat`, 32-bit registers and DWORD stores). The supplied binary README
  separately declares DOS4GW, VESA support, optional VSync and manual/auto
  frameskip. Those are incompatible as a direct MySMB implementation source:
  MySMB remains a real-mode DOS16 program with no frame skipping.

### Presentation/flicker finding

The source declares distinct `video` and virtual `screen` pointers, and its
README exposes a VSync option. Its DOS implementation is packaged inside
`Source/NESSRC.ZIP`, where `copyscreentovideo` copies the completed software
surface to video memory. The outer source tree's project recipe still points
to a missing private make fragment, and the expected historical compiler is
not currently installed. S1 therefore cannot yet claim that the x.xx
executable page-flips, waits for retrace by default, or uses any particular
VESA mode; it now performs a contained build/run attempt before closing that
question.

By contrast, the selected MySMB DOS retained presenter writes current HUD and
sprite tile bytes directly to the presently visible A000 aperture while
presenting. There is no vertical-retrace gate or display-page swap in that
path. End-of-frame pixels are exact, but the monitor/emulator can expose the
intermediate writes; this is a concrete explanation for the owner's observed
Mario refresh flicker. It is separate from game logic and from the static
background-cache mechanism.

### Opportunity matrix

| Finding | MySMB status | Next action |
| --- | --- | --- |
| Background dirty tracking and current-background reconstruction | Already present through the selected S18 retained presenter. | Keep; do not duplicate a full nametable surface. |
| Indexed palette slots and palette-only updates | Already present in the shared slot compositor/DOS DAC path. | Keep; quantify no change. |
| Full 64-sprite redraw each visible frame | Required by both the historical source and MySMB semantics. | Do not suppress Mario redraw. |
| 32-bit flat assembly/DOS4GW | Incompatible with DOS16/MS-DOS 5 baseline and higher memory/runtime requirements. | Reject. |
| Frameskip | Changes observed presentation cadence. | Reject. |
| Buffered display page plus vertical-retrace handoff | Plausible cure for visible tearing, but historical source does not prove the exact DOS backend. | S2 first establishes source-matched fixed-cycle timing; a later device-only feasibility S may inspect CRTC page-flip/retrace capacity, memory cost and exact frame semantics. |
| Full 256x240 cached nametable surfaces | Historical source likely consumes at least two 61,440-byte surfaces in its 32-bit DOS runtime. | Reject as a direct DOS16 copy; compare only against MySMB's existing compact derived cache and memory policy. |

S1 does not change product source, artifacts, ROM-node status or control-edge
status. It identifies direct-visible VRAM updates as a separate presentation
quality question, but does not yet establish the cost, hardware feasibility or
correctness of a page-flipped MySMB device path.


### S2 result -- accepted fixed-HUD plane batching

S2 implemented a contained `src/platform/dos16/devices.c` candidate that selected
each of the four VGA planes once while committing all 32 fixed-HUD rows. Its
layout model covered both name-table choices and every horizontal origin: 512
cases produced identical final A000 bytes while reducing modeled HUD plane
selections from 128 to 4. A source-matched real-mode MZ before/after fixture
then exercised 258 retained frames at DOSBox `core=auto`, `cycles=fixed 3000`;
232 frames had `fixed_top` set. The measured final forty-frame presenter
interval regressed from **306,673** to **309,925** PIT ticks/frame (+1.06%).
The total root interval likewise changed from 319,560 to 322,811 ticks/frame.
Both routes completed with the fixture's existing exact marker
`exact1 bad0 firststep0`.

The lower plane-selection count is not itself an acceptance. Assembly inspection
identified the first regression's direct cause: its batch helper accepted
`slots` as a far pointer, so every one of the 8,192 HUD-byte extractions loaded
a segment and used `es:[bx]`. The removed 124 plane-select operations did not
repay that cost.

The accepted replacement leaves the raw `retained_hud_slots` extraction in
`retained_hud_rows`, where it already had known-good DOS16 data access, and
moves only `vga_retained_plane` outside that caller's 32-row loop. It therefore
preserves the original row extraction, scratch-buffer and byte-copy order while
reducing the commit selections from 128 to 4. A matched private 60-frame route
measured its final 40 frames after the Start/right+B transition. Both versions
completed frame 58 with 32 fixed-HUD frames and the existing route marker
`exact1 bad0 firststep0`; presenter time improved from **344,869** to
**338,395** PIT ticks/frame (**-1.88%**), and root-step time from **412,730**
to **406,215** (**-1.58%**). The 512-case final-A000 layout model remains
exact. A prior apparent early termination was traced to the test host cleaning
up a detached DOSBox process at its command timeout, not a DOS candidate fault.

The accepted change is confined to `platform/dos16`; it does not alter ROM
state, shared game/PPU logic, cadence, output dimensions or persistent DOSBox
configuration. The DOS MZ and both existing Win32 product targets rebuilt and
the three local artifacts were refreshed. A full current Win32 CTest rebuild
is separately blocked by pre-existing `test/win32_terminal_present_smoke.c`
using the absent `mysmb_win32_text_console.terminal` member; that test is
outside this DOS16 S and was not changed. S3 remains planned and is not
admitted.

## Memory/performance decision

The owner accepts ordinary DOS memory use up to approximately **500KiB** when
it materially improves playability; lower use remains preferred. The next
DOS16 graphics qualification may therefore allocate one 256x240 indexed RAM
composition surface (61,440 bytes) plus a small precomputed row/span-address
table. It must first prove exact final pixels and a meaningful fixed-cycle
improvement against the selected direct-output route. A two-surface/page-flip
experiment (roughly 120KiB before metadata) is deferred: it is not the first
performance candidate because it risks exceeding the intended memory budget.

### S1 contained DOS16 physical-output microbenchmark

Before any MySMB source change, S1 will build a private DOS16 probe below
`build/m3-t39-s1/`. It exercises the current `slot_copy` physical owner with
the same deterministic 256-by-240, 16-row-band slot input in three forms:
direct composition to A000; composition to one 61,440-byte RAM surface then
one contiguous A000 transfer; and the latter with precomputed band addresses.
Every form must leave identical 61,440 final A000 bytes. Repeated samples use
the BIOS-owned PIT in a temporary fixed-3000 DOSBox run; the probe does not
change the PIT rate, game cadence, PPU semantics, source tree, or persistent
DOSBox configuration. It isolates the physical-memory and address-reload cost;
it does not claim a full game-frame delta or test any third-party code.

#### Result: one RAM surface is rejected for speed

The ignored probe copied the current `platform/dos16/slot_copy.c` owner into
its private build, compiled it with the existing OpenNT16 large-model route,
and ran five fixed-3000 DOSBox samples. It generated one deterministic
61,440-byte 256-by-240 palette-slot image and exercised the owner's normal
16-row-band contract. Alternating bands used either one full 256-byte source
span or the valid 192-plus-64 split form. Each candidate compared all 61,440
final A000 bytes with the source image; every sample reported `exact=1`.

| candidate | extra conventional memory | PIT ticks/frame | ms/frame at 1,193,182Hz | result |
| --- | ---: | ---: | ---: | --- |
| Direct A000, full spans | 0 | 7,247.5 | 6.074 | control/best physical move |
| Direct A000, alternating split spans | 0 | 8,317.4 | 6.971 | conservative split-bound control |
| RAM compose, alternating split spans, one contiguous A000 copy | 61,440 bytes | 14,500.4 | 12.153 | 74.3% slower than direct split |
| Same RAM route with precomputed band destinations | 61,440 bytes plus 60 bytes | 14,298.4 | 11.983 | 1.39% better than untableed RAM, still 5.012ms/frame slower than direct split |

The five receipts were byte-for-byte repeatable in DOSBox. This is deliberately
a physical-owner microbenchmark, not a game-frame claim: its split pattern is
a legal stress mix rather than a census of live PPU spans, and it excludes
background selection, sprite traversal, DAC work and game logic. It proves a
useful lower bound nonetheless: in this real DOS16 ABI, adding one RAM surface
and a 61,440-byte copy cannot be the explanation for NESticle's speed or a
safe MySMB speed improvement. The small address table does not remove the
owner's per-split source-segment reloads, so its measured benefit is not a
candidate on its own.

S1 therefore rejects the proposed one-surface RAM compose-and-copy rewrite.
It also does **not** attribute the remaining gap to 16-bit execution: the
accepted fixed-route profile still puts the larger cost in PPU composition,
and this probe only rules out a device-side staging shortcut. Future work must
measure and reduce exact shared composition/cache work, or separately qualify
a presentation-only anti-tearing path, without importing DOS4GW, changing
frame cadence, or changing the PPU result.

### S1 contained shared-PPU composition attribution

The next private probe reuses the current shared `ppu/frame.c` and current
DOS16 slot copier, with no game-core call and no source edit. It will build
one deterministic PPU state and compare complete 61,440-byte slot output to
the portable frame builder before timing four distinct conditions: stable
cached background with no visible sprites; the same state with dense visible
OAM; exactly one changed nametable tile per frame; and full cache
invalidation. Each condition measures `frame_begin` separately from all
fifteen 16-row `slot_rows` calls. This isolates cache preparation, row
selection/copy and sprite overlay cost without claiming that the synthetic
state distribution is a live-level profile.

#### Result: detached composition probe discarded

The private probe did compile and link the current `ppu/frame.c`, palette
helpers and DOS slot copier through the normal large-model toolchain.  It was
not allowed to contribute a timing result: even after reducing its frame count
and removing its unused reference surface, the minimal MZ did not return to
DOSBox `autoexec` or produce a non-empty receipt.  Its independently allocated
large far-workspace layout is therefore not a trustworthy representation of
the product root.  The attempted probe and all of its files remain ignored
below `build/m3-t39-s1/`; none of its elapsed time, including the deliberately
pathological full-background rebuild, is evidence about MySMB performance.

This is a useful containment result rather than a performance result.  The
authoritative numbers remain the source-matched T38 receipts: the current
shared game tick was 4,096 PIT ticks (about 3.43ms) in the matched route,
below the 20% threshold, while PPU row production was 21,129 ticks and the
pre-retained selected route's sprite traversal/opacity/overlay was 11,910
ticks.  Together with the accepted physical-output probe, this preserves the
ranking: do not add a RAM surface; do not fork game core for DOS; and do not
infer a 16-versus-32-bit cause from this failed harness.

The next valid measurement must repair the earlier **source-matched,
no-readback retained-product fixture** rather than construct another detached
PPU executable.  It must use the product root's existing far allocations and
selected presenter, record the same post-Start fixed-3000 route, and first
prove that its timing-only instrumented path reaches the fixture completion
marker.  Only then may it separate product-root, `frame_begin`, row production
and presenter intervals.
### Contained Mode 13h runtime receipt

The public 0.2 source package was buildable only after an **ignored, local-only
benchmark harness** removed its missing GUI/menu, mouse, sound and
VESA/SciTech front-end dependencies.  It keeps the source CPU, PPU,
pattern-cache, nametable and sprite routines, uses the source’s 32-bit
M6502 assembly, loads the owner-local `smb1.nes`, and submits a completed
320x200 software surface with one 64,000-byte Mode 13h copy.  The temporary
harness uses a generic DAC palette and is not a reconstruction or a claim
about the owner x.xx executable’s exact output.

A fixed 1,200-frame run emitted `BENCH.OK` with `frames=1200`, proving that
ROM loading and the CPU/PPU/video loop completed.  In a temporary copy of
the DOSBox configuration with `cycles=fixed 3000`, host elapsed time was
20,924ms: **17.44ms/frame**.  The default `cycles=auto` comparison took
3,523ms.  The former is the useful direction-only receipt beside MySMB’s
selected 32.71ms/frame diagnostic baseline: it is not a like-for-like
product benchmark because it uses DOS4GW/flat 32-bit code and a simplified
front end.  No toolchain, ROM, harness, executable, DOSBox configuration or
third-party source leaves ignored `build/m3-t39-s1/`.
The harness’s coarse DOS `clock()` attribution over those 1,200 frames was
`cpu=110ms`, `draw=11205ms`, `copy=6426ms` (total `17906ms`; timer granularity
and instrumentation explain the difference from host elapsed time). It
therefore corroborates the existing MySMB fixed-cycle profile: the practical
first target is native PPU composition, not translated ROM logic. The
historical implementation spends most of its time drawing to RAM, then pays
one contiguous VGA transfer; MySMB’s earlier selected route spends 21.19ms in
slot-row composition but only 2.01ms in DAC/device submission. A future
candidate must reduce the DOS16 compositor’s repeated row/span/address work
while preserving the shared PPU’s exact completed pixels. Replacing MySMB
with DOS4GW or importing the historical source remains rejected.

### S1 mechanism comparison: the remaining gap is not only word size

The contained source inspection now establishes the actual DOS-side work
models.  This is a source-structure comparison, not a claim that the public
0.2 source is byte-identical to the owner's historical executable.

| layer | historical NESticle DOS source | current MySMB DOS16 selected presenter | consequence |
| --- | --- | --- | --- |
| Working target | A conventional contiguous software `screen` allocation. | The retained scene occupies the VGA's four unchained planes as a 512-by-480 scrollable cache. | NESticle pays RAM writes then one sequential transfer; MySMB saves conventional RAM but must address VGA plane bytes during composition. |
| Static background | Dirty nametable tiles refresh a RAM cache; every visible section then performs clipped cached blits into `screen`. | Changed background tiles update the retained VGA cache; this is already the comparable useful cache. | Neither product needs to redraw a complete static tile field each frame.  Duplicating the cache is not a candidate. |
| Moving sprites | All 64 entries are traversed each frame by flat-32 assembly into contiguous RAM. | Old and new sprite coverage is marked, affected 8-by-8 background tiles are reconstructed, then each sprite is drawn through four VGA planes. | Both retain full moving-object semantics, but MySMB incurs per-plane selection and non-contiguous VGA writes on the hot path. |
| Fixed HUD | It is naturally part of the RAM background blit. | The current path restores the prior 32-row HUD, prepares and packs the next 32 rows, then commits it plane by plane every frame. | MySMB has an irreducible current fixed work floor of 8,192 bytes restored plus 8,192 bytes committed, excluding PPU extraction and packing. |
| Final publication | In non-VESA Mode 13h the historical DOS source copies the completed buffer in one 64,000-byte `memcpy` to VGA. | The selected presenter writes its individual background/HUD/sprite changes directly to the visible A000 aperture. | Direct writes explain visible transient flicker; they also replace one linear transfer with many short writes and VGA-port state changes. |
| Instruction model | Flat 32-bit registers and specialized assembly tile/sprite loops. | Real-mode 16-bit C plus small copy assembly; retained overlay paths perform far address arithmetic, clipping, transparency and plane selection in C. | Flat 32-bit code is a real advantage, but it compounds the larger difference in write granularity and memory layout. |

The most important correction to the earlier hypothesis is therefore: **DOS4GW
and 32-bit registers help, but do not by themselves explain the observed gap.**
The two programs choose different cost models.  MySMB's low-memory retained
strategy moves less bulk data than a complete 64KiB Mode-13 copy, but it
replaces that copy with expensive per-tile/per-plane composition on a 16-bit
VGA aperture.  The earlier one-surface probe shows that merely adding the
NESticle-style RAM surface and retaining the current composition costs more;
it does not invalidate the analysis above because that probe did not remove
the current fine-grained overlay work.

This ranks the lawful next candidates without changing ROM or shared PPU
semantics:

1. Measure the selected retained presenter's actual per-frame counts: changed
   background tiles, fixed-HUD bytes, old/new sprite-covered tiles, plane
   selections and VGA bytes.  This identifies whether HUD or sprite repair is
   the dominant live workload.
2. If sprite repair dominates, replace only the DOS16 physical inner loop with
   a pre-packed, plane-contiguous sprite/tile writer.  It must consume the
   same PPU-selected slots, preserve order, clipping and transparency, and
   remain wholly under `platform/dos16`.
3. If the fixed HUD dominates, cache its already PPU-selected packed form and
   avoid restore/repack/commit when its viewport, palette slots and tiles are
   unchanged.  The PPU still produces the same output; only redundant physical
   writes disappear.
4. Separately qualify a presentation-only back-buffer or page-handoff route
   only if it can remove visible-A000 tearing within the conventional-memory
   budget and beat the measured retained route.  The existing 61,440-byte
   naive surface-plus-copy experiment remains rejected; this is not approval
   to reintroduce it unchanged.

The source also gives a bounded cost model for the selected MySMB physical
path.  On a frame with the sprite-zero HUD split it always restores and
rewrites 32 rows in four planes: **16,384 VGA bytes** before sprite repair.
Each changed background cache tile writes 128 VGA bytes because the retained
512-by-480 scroll surface stores two vertical copies.  Each marked 8-by-8
sprite-repair tile writes 64 bytes; a visible sprite then issues up to 64
transparent-tested byte stores and four plane selections.  The exact live
counts are still unmeasured, but these fixed units show why a small number of
sprites can cost materially more than their pixel count suggests on a 486:
the work is split across byte stores, far address calculations and VGA
sequencer changes rather than one linear memory stream.

#### Result: source-matched live work census

The previous detached fixture was not reused.  A private product-root build
instead sent one Start only when the translated title state reported
`OperMode=0, Task=3`, then confirmed normal game execution at `OperMode=1,
Task=3`.  It warmed for 60 game frames, reset only private physical-work
counters, then collected 60 further game frames at temporary fixed 3,000
cycle DOSBox settings.  Its main and DOS device source were private ignored
copies; optimization was deliberately disabled because this is a count receipt
and does not contribute a timing result.

| retained physical work over 60 steady gameplay frames | total | average/frame |
| --- | ---: | ---: |
| fixed-HUD restore A000 bytes | 491,520 | 8,192 |
| fixed-HUD commit A000 bytes | 491,520 | 8,192 |
| changed cached-background A000 bytes | 256 | 4.3 |
| sprite-repair tiles | 720 | 12 |
| sprite-repair A000 bytes | 46,080 | 768 |
| active OAM tiles | 300 | 5 |
| nontransparent sprite A000 bytes | 8,880 | 148 |
| VGA map-plane selections | 12,008 | 200.1 |

The static background cache is therefore working: it was almost idle in the
steady sample.  Sprite drawing is not the primary physical byte volume either.
The dominating fixed work is the HUD's 16,384 A000 bytes every frame.  Source
inspection explains the exceptionally high plane count: `retained_hud_rows`
issues a HUD line write for each of 32 rows in each of four planes, and the
line helper selects the VGA plane itself.  That creates **128 HUD plane
selections per frame**, before sprite repair, sprite writes and restore.

This makes the first implementation candidate precise and limited: introduce
a DOS16-only plane-batched HUD commit that selects each plane once and writes
all of its 32 already PPU-selected rows.  It must preserve the existing source
row order, split-wrap handling, palette slots, viewport coordinates and final
A000 bytes.  It changes no game or PPU code.  The candidate is expected to
remove roughly 124 of 128 HUD commit plane selections per frame; its actual
PIT effect and physical byte oracle remain future acceptance criteria.

### NESticle-inspired opportunity register, ranked by return on cost

The ranking below is deliberately based on the live work census rather than
on the historical program's age, implementation language or a final image
comparison.  “Memory” is additional conventional memory; VRAM reuse is stated
separately.  All compatible entries retain the shared PPU frame view and can
live entirely in `platform/dos16`.

| rank | opportunity | expected result | memory | implementation / semantic risk | disposition |
| ---: | --- | --- | ---: | --- | --- |
| 1 | Batch each HUD plane once, then copy its 32 rows as spans. | Removes about 124 of 128 HUD plane selections/frame and collapses 128 small copy setups into 4–8 spans. | 0 | Low / none: identical selected bytes and destination order within each plane. | First candidate. |
| 2 | Batch sprite-repair writes by VGA plane rather than by tile. | The live route repairs 12 tiles/frame; changes its approximate 48 plane selections to 4 while retaining the same 768 bytes. | 0 | Low / none: changed background tiles do not overlap within a plane. | Bundle with rank 1 only if the physical oracle remains simple. |
| 3 | Precompute viewport-relative plane offsets for HUD and 8-by-8 repair cells. | Removes repeated far address arithmetic and wrap branches from fixed HUD and repair loops. | 1–4KiB table, or 0 with a small per-frame row table. | Low / none if generated from the existing viewport formulas. | Candidate after 1–2; qualify separately to identify its value. |
| 4 | Pre-pack each collected sprite into its four plane lanes and carry its transparency mask. | Removes repeated slot indexing, per-pixel plane selection math and many transparency branches; five active sprite tiles/frame make this a secondary improvement. | 0 if replacing the current 64-byte sprite copy; otherwise up to 4KiB. | Low–medium: must preserve OAM order, clipping and transparent-slot behavior. | Candidate after the HUD path. |
| 5 | Retain an already packed HUD image keyed by its PPU-selected 32 rows and palette slots. | Skips HUD PPU extraction/packing when text is unchanged; does not remove the required physical HUD write. | about 8KiB unless existing transient storage can be safely repurposed. | Medium: cache invalidation must include title/status digits, palette and mode/split changes. | Conditional: measure CPU preparation after ranks 1–2. |
| 6 | Generate a changed background tile’s 64 slots once, then distribute its four plane lanes. | Avoids four equivalent PPU tile queries for an invalidated cache tile; valuable during area construction, negligible in the steady sample (4.3B/frame). | 0 | Low / none. | Startup/load smoothness candidate, not frame-rate first. |
| 7 | Use a dedicated 16-bit assembly bulk writer for the now-contiguous HUD spans. | Can improve rank 1’s remaining far-copy overhead with `rep movs`/careful segment setup. | 0 | Medium implementation / none if byte oracle is exact. | Only after the C/inline-assembly batched version is measured; do not hand-write assembly preemptively. |
| 8 | RAM composition surface followed by one linear VGA copy. | Mirrors the historical shape and eliminates visible intermediate A000 writes. | 61,440B plus metadata. | Medium–high: a page-wide composition rewrite. | **Rejected as tested:** with current composition it cost 11.983ms versus 6.971ms for direct split A000. Revisit only if ranks 1–7 first remove the current fine-grained composition. |
| 9 | Double-buffer/page-handoff or retrace presentation. | May remove tearing/flicker, but is primarily presentation quality, not CPU throughput. | at least about 120KiB for two full indexed surfaces; current 512x480 retained VRAM cache consumes nearly all VGA memory. | High: memory budget and device timing. | Deferred; no evidence it is the fastest route. |
| 10 | Dirty cached nametables, palette-slot retention, decoded patterns. | Avoids static-world regeneration. | Already allocated by the selected shared/retained route. | None. | **Already present**; do not duplicate. |
| 11 | Suppress sprite redraw. | Would reduce work superficially. | 0 | Unacceptable: violates current OAM state and visible semantics. | Rejected. |
| 12 | Frameskip or decouple publication cadence. | Makes an overloaded machine appear smoother. | 0 | Unacceptable: changes observed cadence. | Rejected. |
| 13 | Port MySMB to DOS4GW / flat 32-bit runtime. | Could reduce pointer and loop overhead. | Material runtime and memory cost; loses real-mode DOS16 target. | Architectural incompatibility. | Rejected. |
| 14 | Rewrite shared ROM core for host-specific addressing. | The source-matched profile places core near 12% of the old route; it cannot explain the present device work. | uncertain | High semantic-regression risk. | Rejected as the first performance path. |

Ranks 1–4 are the complete near-term compatible set derived from the observed
NESticle difference: make the same pixels through contiguous plane work,
without changing the game/PPU owner.  Ranks 5–7 are conditional refinements;
ranks 8–14 are retained as explicit non-default decisions so they cannot
reappear as unmeasured “obvious” optimizations.

### S3 work census (in progress)

This private probe uses only the normal title-to-game Start input; it never
writes translated RAM or substitutes a scene. It counts physical device work,
not elapsed time. The title and transition/steady routes were collected at a
private fixed 12,000-cycle DOSBox setting solely to bound host runtime; counter
values are independent of that setting and are not PIT timing evidence.

| route | receipt state | sampled frames | HUD restore / frame | HUD commit / frame | changed background / frame | repair tiles / frame | repair bytes / frame | OAM tiles / frame | sprite bytes / frame | plane selections / frame |
| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| title startup | `OperMode=0, Task=1` | 15 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| Start transition | `OperMode=1, Task=1` | 66 | 124 | 0 | 3,724 | 7.8 | 500 | 3.9 | 139 | 46.9 |
| steady normal play | `OperMode=1, Task=3` | 68 after five-frame warm-up | 8,192 | 8,192 | 7.5 | 12 | 768 | 5 | 148 | 76.1 |

The zero title row means only that startup had not selected the retained
presenter. It is not a claim that title rendering is free. The transition is
background-heavy; steady play is fixed-HUD-heavy. The stable route confirms
the S1 work units after S2: the HUD still writes 16,384 bytes per frame, while
background invalidation remains almost idle.

The S2 fixed-HUD change already removed roughly 124 plane selects per steady
frame for a measured 1.88 percent presenter improvement. The remaining
steady repair-path plane-select budget is about 48 selects/frame (twelve tiles
by four planes), with another roughly 20 for five sprite tiles. Even a perfect
repair-plane batching change cannot plausibly meet S4's predeclared 20 percent
residual-presenter threshold. S3 therefore supplies an evidence-led rejection
basis for that speculative implementation, rather than a further micro-edit.

The admitted Start-only input route does not reproducibly reach a dense-sprite,
underwater, or castle scene within this probe. Those rows remain unavailable;
no RAM-seeded substitute was used. The current S3 results are sufficient for
the S4 repair-batching decision but not a general claim about every game area.

### S4 decision -- reject sprite-repair plane batching

**Decision: reject; no product source or executable changes.**

S3's steady route has about twelve repair tiles per frame, so its repair
writer selects a VGA plane about 48 times. Five sprite tiles add about 20
more selections. S2 removed approximately 124 fixed-HUD selections per steady
frame while preserving all bytes and yielded only a 1.88 percent presenter
improvement. Treating that observed result as linearly scalable gives an
optimistic upper bound of `(48 + 20) / 124 * 1.88 = 1.03` percent for making
both remaining classes free. A repair-only change is bounded near 0.73 percent.

Those bounds are generous: they assume no added collection, sorting, packing,
or far-pointer overhead. The candidate also leaves the steady path's 16,384
fixed-HUD bytes, 768 repair bytes and roughly 148 sprite bytes untouched. It
therefore cannot satisfy S4's required plausible 20-percent residual-presenter
reduction. No implementation, byte oracle, target rebuild or executable
refresh is justified. The next owner is S5's separate buffered-composition
feasibility decision; it may not revive the rejected 61,440-byte naive RAM
surface without a new measured cost model.

## S5 result -- compact-VRAM display-page candidate is feasible for implementation

S5 did not change product source or refresh an executable. It first corrected
the proposed memory model: the current retained cache is **512 by 480**, not
512 by 240. It stores the two horizontal nametables and a second vertical copy
so CRTC scrolling can expose any 240-row viewport directly. That uses 61,440
bytes in each of the four VGA planes (245,760 bytes total), leaving no room for
a display page. Consequently, two display pages cannot simply be added to the
current surface.

There is nevertheless a different, bounded device-only candidate. The current
retained-tile address function makes both vertical copies identical. Therefore a
composition path can retain one 512-by-240 name-table period, assemble a
scrolled viewport in software, and make the vertical wrap explicit while
preserving the same selected PPU tile slots. Its VGA layout is:

| region | bytes per plane | all four planes |
| --- | ---: | ---: |
| 512-by-240 retained background | 30,720 | 122,880 |
| hidden composition page A, 264-by-240 | 15,840 | 63,360 |
| hidden composition page B, 264-by-240 | 15,840 | 63,360 |
| total | 62,400 | 249,600 |
| unused VGA capacity | 3,136 | 12,544 |

The eight-pixel margin in each 264-pixel page is required for CRTC horizontal
panning; a nominal 256-by-240 page is not enough to prove all scroll phases.
The design consumes **no new conventional memory**. It is distinct from the
rejected conventional-RAM surface: all source, composition and display pages
stay in the existing 256KiB VGA aperture.

An ignored DOS16 MZ microbenchmark built with the product toolchain tested the
only hardware assumption that matters before an implementation: VGA latch
copying in graphics-controller write mode 1. It filled each source plane with a
different pattern, copied it, read every destination plane back, and required
zero mismatches. The viewport case used a 66-byte-per-plane destination row,
240 rows, source stride 128, a nonzero source column, and a vertical wrap. It
also had zero mismatches. At the same DOSBox normal, fixed 3000 diagnostic
setting used for relative device probes, the 16-sample totals were:

| operation | PIT ticks / sample | relation to 338,395-tick retained presenter baseline |
| --- | ---: | ---: |
| four-plane CPU VGA copy of a 256-by-240 page | 431,674 | 127.6% |
| contiguous latch copy | 119,056 | 35.2% |
| wrapped, strided 264-by-240 latch viewport copy | 143,551 | 42.4% |
| CRTC page-start update | 41 ticks | negligible |

The benchmark rejects ordinary CPU VGA-to-VGA copy, but it establishes the
latch path as a bounded candidate: the necessary wrapped viewport transfer uses
less than half of the current measured retained presenter interval before the
destination-only HUD and sprite work is added. It can eliminate visible-page
restore and repair writes, and a CRTC start-address swap makes the completed
page visible atomically; this directly addresses tearing/flicker.

This is **not** a product performance claim yet. A later implementation S must
prove all of the following before it replaces the retained path:

1. compose a page from actual PPU frame slots at every horizontal phase and
   vertical wrap, then compare final pixels and VGA register state against the
   current retained oracle;
2. retain fixed-top HUD and OAM ordering exactly while writing only the hidden
   page;
3. compare steady, transition, title, water/castle and dense-sprite routes
   against the 338,395-tick reference; and
4. keep the 249,600-byte VGA layout within the standard 256KiB aperture with
   no conventional-memory allocation or shared PPU/game change.

S5 therefore closes as **feasible for a separate implementation S**, not as an
accepted optimization. The private fixture, MZ binary, DOSBox configuration and
result files remain below ignored build/m3-t39-s5/.

## S6 admission -- compact-VRAM double-page integration

The owner approved implementation after S5. S6 owns only the DOS16 device
adapter and project-owned tests. It may replace the current 512-by-480 retained
VGA arrangement with a 512-by-240 background period plus two 264-by-240
composition pages, using VGA latch mode 1 for the wrapped viewport copy and a
CRTC handoff only after the hidden page is complete. The 264-pixel row includes
the necessary panning margin; its 249,600-byte total must remain within the
standard 256KiB VGA aperture.

The exact PPU frame view remains the only source of background, fixed HUD and
OAM slots. S6 may reorganize their physical VGA writes, but it cannot change
their order, palette, clipping, scroll, cadence, state, or shared API. It must
preserve the existing presenter as a fallback until final-pixel and VGA-state
comparison passes. There is no conventional-memory allocation, no Win32/text/
core/PPU change, no DOSBox configuration change, and no refresh of three
product artifacts unless product source passes acceptance.

Acceptance requires all of: exhaustive page-layout coverage for horizontal
panning and vertical wrap; exact retained-frame output comparison on actual PPU
frames; a DOS16 MZ build/run; and a matched fixed-cycle measurement showing at
least 20 percent improvement from the 338,395-tick steady presenter baseline.
Otherwise S6 removes the candidate path and records a rejection.

## S6 result -- accepted compact-VRAM double-page presenter

S6 accepts the DOS16-only compact VGA route.  It retains one 512-by-240
background period and uses two 264-by-240 composition pages, for 62,400 bytes
per VGA plane (249,600 bytes total), leaving 12,544 bytes of the standard
256KiB aperture unused.  It adds no conventional-memory allocation and does
not change the shared core, PPU view, cadence, palette selection or OAM order.

The initial complete-page copy was not accepted on its first implementation:
the warm cache route measured 425,886 PIT ticks/frame.  The cause was confined
to the DOS HUD commit: it recomputed a far VGA address for every HUD slot.
S6 changed that adapter-only loop to the same plane-major, row-span shape as
the accepted retained HUD path.  The same fixed `normal`, `cycles=3000`
product fixture then measured 252,787 PIT ticks/frame across four warm-cache
frames (the preceding first frame rebuilt all 7,680 plane-tile writes).  The
old retained route on that exact fixture measured 298,397 ticks/frame.  The
accepted route is therefore 15.3 percent faster on the paired fixture and
25.3 percent below the 338,395-tick S2 accepted reference, clearing S6's
20-percent requirement.

Exactness evidence consists of exhaustive page/layout coverage for both
scene pages, all 256 horizontal origins, all 240 vertical origins and all 240
output rows; a four-frame canonical-PPU overlay oracle covering split HUD,
OAM order, scroll phases and bottom-to-top vertical wrap; and the established
retained background/apply/overlay checks.  The focused suite passed on both
x86 and x64 hosts, platform-purity passed, and the actual MZ linked and ran
under an unmodified standard-VGA DOSBox invocation without an immediate exit.
The three target artifacts were refreshed after the source acceptance.

## S7 admission -- DOS16 deadline-driven frame skipping

The owner directs DOS16 to retain every logical game tick but to omit video
composition and submission whenever the tick is already late for the next
60Hz deadline.  This is an explicit presentation policy change: it preserves
translated game state, input sampling, ordered audio construction and PPU
state writes, while allowing intermediate visible frames to be discarded.

S7 owns the platform composition roots and their host clocks.  Both DOS16 and
Win32 apply the same neutral rule: after every logical tick/catch-up batch,
omit video composition/submission when the display deadline is already past.
DOS uses PIT and Win32 uses QPC; the host clock is the only platform-specific
part.  It must not alter shared core/PPU code, text scene ownership, ROM
timing logic, input mapping, persistent DOSBox settings, add a helper or use
DOS4GW.  Save/load may force one redraw after restoration.

Acceptance requires a deterministic root test proving that skipped output
does not change game/frame state, input or audio frame construction; a pacing
test proving late debt is carried until catch-up; focused x86/x64 tests,
platform-purity, DOS16 link/run and refreshed artifacts.  The DOS route must
record logical ticks, submitted frames and skipped frames separately.  A
skipped frame is never counted as a PPU or ROM-equivalence difference.

## S7 closure -- frame gate is rejected as a performance solution

S7 preserved logical game/input/audio work while skipping stale video.  Its
current-product fixed-3000 DOSBox probe ran 601 root steps: 598 graphical-gate
steps, two submitted images and 596 dropped images.  The average root cost was
21,127 PIT ticks; dropped steps averaged 12,001 ticks.  This proves the gate
cannot make the selected presenter playable: it exposes the cost but cannot
reduce it.  No product change is accepted from S7; the experimental timing
sources were removed.  The next S replaces the DOS16 presentation architecture,
not the translated game or shared PPU decision layer.

## S8 admission -- NESticle-style RAM composition foundation

The owner directs MySMB DOS16 presentation to adopt the independently derived
NESticle organization: dirty 8-by-8 background RAM surfaces, a contiguous RAM
screen composition target, ordered background/sprite/foreground composition,
and one final contiguous VGA submission.  This is an independently implemented
architecture; no third-party code, data, tables, assembly or binary is copied.

S8 first establishes the product-owned DOS16 storage and neutral contracts for
the RAM surfaces, then proves exact pixels against the existing shared PPU view
on title, split HUD, scrolling, palette, priority and OAM routes.  It may alter
only `platform/dos16`, the DOS composition root and neutral presentation
contracts needed by both implementations.  It may not alter core, PPU decision
semantics, game/audio/input timing, Win32, text mode, ROM resources or add
DOS4GW.  The memory receipt must separately state mandatory memory, optional
A/B/C caches and peak conventional usage; failure to fit the owner's ordinary
memory budget rejects or reduces the DOS16 layout before product selection.

The first P is a contained product-structure implementation plus exact oracle
and fixed-cycle measurement.  It must report separate dirty-background,
RAM-screen composition and final-VGA costs.  Acceptance requires a real DOS16
MZ link/run, host tests, exact existing PPU-output oracle, no shared-game
change, refreshed three local artifacts for source changes, and a measurable
whole-route improvement.  A failed foundation is not hidden by frame skipping.

## S8 P1 result -- RAM composition foundation

P1 introduces an optional DOS16 256-by-240, one-byte-per-selected-pixel RAM
screen (`61,440B`) after the established B/A/C cache choices.  The shared PPU
remains the exclusive owner of scroll selection, status split, palette choice,
OAM ordering, priority and transparency.  The DOS16 RAM compositor obtains the
PPU-selected background rows, overlays only the PPU-authorized sprite slots,
and makes one contiguous Chain-4 VGA submission.  If the optional allocation
or presenter is unavailable, the existing compact VGA presenter remains the
fallback.  No core, shared PPU decision, Win32 or text code changed.

The focused byte oracle covers title/split, non-zero scroll, masked sprites,
background-priority sprites, top/bottom clipping and palette-slot values.  It
compares every byte of the new RAM surface with `mysmb_ppu_frame_slot_rows`;
all four cases pass.  The DOS16 product linked as an MZ via the historical
DOS LINK 3.65 compatibility route and remained alive at title for five seconds
in an unchanged DOSBox standard-VGA run at `core=normal`, `cycles=fixed 3000`.
The product MZ is 350,093B.  Its link receipt estimates 378,208B mandatory
load allocation; B+A+C+RAM screen can request 194,560B more, so P1 retains the
existing allocation fallback rather than claim a stock-memory fit before the
runtime receipt.

A synthetic, warmed, identical-PPU-view fixed-3000 DOSBox probe measured 16
completed presentation operations: compact VGA `267,964` PIT ticks per frame;
RAM compose plus one contiguous commit `48,934` ticks per frame (5.48x faster).
This is evidence that the new physical model warrants full-route measurement,
not a claim about gameplay root-step timing.  The next P must add the bounded
post-Start whole-route receipt and report whether optional RAM allocation was
actually retained; no frame-skip result can substitute for it.

## S8 P2 -- DOS16 late-deadline recovery

The faster RAM presenter exposed a defect in the DOS physical clock adapter.
When a presentation took two or more frame periods, the gate correctly omitted
the stale image, but `mysmb_dos16_devices_wait` advanced the deadline by only
one period.  The next tick therefore remained late, was omitted again, and
waited zero time indefinitely.  The symptom is uncontrolled fast-forward in
DOSBox; it is unrelated to translated game timing or PPU decisions.

The adapter now waits through `mysmb_io_pacing_remaining`, the existing neutral
clock primitive that retains ordinary fractional lateness and rebases a
multi-period missed-frame backlog.  Logical ticks, input sampling and audio
construction remain unchanged; only DOS's physical wait recovery changes.
Focused host pacing, RAM compositor, PPU overlay, compact overlay and DOS root
smokes pass.  The actual DOS16 MZ links through DOS LINK 3.65 and remains alive
for five seconds in an unchanged standard-VGA DOSBox launch at `core=normal`,
`cycles=fixed 3000`; both Windows product self-tests also pass after packaging.
The refreshed DOS executable is `350,077B`.  Owner play testing is still the
acceptance evidence for visible 60Hz pace; this P does not claim a new
whole-route performance measurement or close S8.

## S8 P3 -- DOS16 logical catch-up instead of renderer-paced simulation

Owner testing showed that P2 removed uncontrolled fast-forward but rebased the
logical deadline after every multi-period composition.  Since the RAM path can
still consume roughly 41ms in its synthetic presenter probe, that made one
logical game tick wait for each slow presentation and visibly slowed motion.

The DOS adapter now advances exactly one 60Hz logical deadline per root step.
If the physical renderer consumed one or more following deadlines, it marks
the subsequent root steps as video-skipped while they continue to read input,
run the unchanged translated game tick and construct audio.  It waits only
after those ticks reach the next future deadline, then permits one current
image to compose.  A BIOS clock discontinuity re-establishes the schedule
without a catch-up burst.  This is the same policy already used by the Win32
bounded catch-up loop: retain game time, discard only stale display work.

No core, ROM, PPU, audio, input mapping, text or Win32 source changed.  The
focused host suites remain green; the updated DOS LINK 3.65 MZ is `350,255B`
and passes an unchanged standard-VGA DOSBox five-second launch.  Both native
Windows self-tests pass after packaging.  Owner play testing remains required
to qualify perceived motion and visual cadence, and S8 remains open for its
separate whole-route timing and allocation receipt.


## S8 closure — usable RAM-composition baseline

The owner accepted the current DOS16 product as a usable baseline.  The final
allocation policy is D then A then B then C: the 61,440-byte RAM composition
surface (D), 8,192-byte decoded CHR cache (A), and 63,488-byte packed
background cache (B) are required for graphical presentation.  The 61,440-byte
byte-background upgrade (C) is requested only after those three allocations
succeed.  Missing D, A, or B requests clean application exit instead of
falling back to the compact presenter that owner testing found non-playable.

The exact PPU overlay oracle, focused DOS root/RAM compositor/pacing tests,
DOS16 MZ link, and unchanged standard-VGA DOSBox launch pass.  The P1 synthetic
presenter probe remains 267,964 compact ticks versus 48,934 RAM-composition
ticks; it is not an end-to-end performance-parity claim.  No ROM node, control
edge, shared game, shared PPU, text, or Win32 behavior changed.  Actual runtime
allocation receipts and a matched whole-route ABD-versus-ABCD cost comparison
are deferred to [DOS16 RAM presenter memory-tier qualification](dos16-ram-presenter-memory-tiers.md).
