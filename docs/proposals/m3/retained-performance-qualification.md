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
