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
| S2 | Rebuild a no-readback PIT fixture from selected product source and time the post-Start route at `core=normal`, `cycles=fixed 3000`. | Same source/presenter identity as the selected MZ; a separate prior 260-frame physical oracle; comparable root-step delta against T38 S10's 39,026 ticks. |
| S3 | Attribute retained graphics only if S2 still exceeds the 16.67ms frame budget. | One named >=20% owner and one bounded candidate, or explicit no-change rejection. |
| S4 | Attribute DOS and Win32 text paths separately; test at most one exact changed-cell or batched-output improvement. | Exact neutral cells, colors, request order and text-mode lifecycle. |
| S5 | Package and target-era qualification. | Current x86/x64/DOS16 artifacts, DOS memory/stack receipt, and explicitly limited 486-class or calibrated run receipt. |

The prior private `cycles=max` result remains diagnostic only. It cannot be
compared with fixed-3000 evidence. S1 does not reopen S18 exactness, change game/PPU policy, reduce cadence,
skip frames, change output dimensions, introduce DOS4GW or a 32-bit DOS
dependency into MySMB, add a helper process, or alter a persistent DOSBox
configuration. DOS4GW may exist only inside the ignored third-party build/run
containment needed to establish the historical comparison.
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
