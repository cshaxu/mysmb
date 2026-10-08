# M3 T38: Fixed-Cycle DOS16 Frame Attribution

## S1 admission

The owner observed the local NESticle reference as playable at DOSBox fixed
`3000` cycles while the current MySMB DOS16 product is not. S1 attributes the
current DOS16 product under the same temporary setting. It does not change the
product, shared core, cache policy, cadence, image contract, or any persistent
DOSBox configuration.

## Current receipt: graphics route

A private copy of the current source was built below ignored
`build/m3-t38-s1/` with the original OpenNT16 compiler and DOS LINK 3.65
route. Its only additions are PIT stage counters. The deterministic route boots
through the title, emits one Start edge at step 180, then holds right/run. It
runs 420 root steps without pacing; the final 200 steps are accumulated. DOSBox
was launched separately with `core=normal`, `cycles=fixed 3000`, sound disabled,
and no persistent config update.

PIT is 1,193,182 Hz. The receipt reports the following average virtual elapsed
cost per measured step:

| stage | PIT ticks | ms | share of root step |
| --- | ---: | ---: | ---: |
| whole root step | 60,174 | 50.432 | 100.0% |
| translated game tick | 8,091 | 6.781 | 13.4% |
| PPU palette/frame preparation | 5,790 | 4.853 | 9.6% |
| PPU slot-row composition | 38,495 | 32.262 | 64.0% |
| palette/DAC plus direct VGA band completion | 2,483 | 2.081 | 4.1% |
| audio-frame construction/submission | 1,078 | 0.903 | 1.8% |

Nested stage counters include their own PIT reads, so their sum is not used as
a second total. The independent whole-root counter is the timing reference.

The direct Chain-4 output is already active in this route; the 61,440 bytes are
written by the row producer directly into A000. Therefore the old separate
full-frame VGA copy is not the current limiting cost. The 15 producer calls
still collectively perform full PPU row composition and are the measured
bottleneck.

At 60 Hz the available period is about 16.667 ms. This route consumes about
50.432 ms before pacing can help, so it cannot maintain 60 Hz at the selected
DOSBox budget. Even an ideal 2x reduction of the 32.262 ms row-composition
portion would leave approximately 34.3 ms for the current route. Thus merely
changing the executable from 16 to 32 bits is neither established nor likely
sufficient by itself; the PPU composition algorithm and its 16-bit code
quality must be treated separately.

## Reference/toolchain comparison status

The owner-local NESticle package contains `NESTICLE.EXE`, DOS4GW 1.95/1.97 and
its README. The README identifies the product as a C++/assembly DOS4GW
emulator, supports native 256x240 mode, and says its DOS edition expects about
8MiB. The owner observed it as playable under the same visible DOSBox 3000
cycle setting. That is meaningful evidence that MySMB's current design has a
large performance gap, but it is not a same-route stage profile of NESticle.

The local tool inventory contains the existing OpenNT `cl16.exe` and
`link16.exe`; it contains no OpenWatcom, DJGPP, WCL386/WCC386, OWCC, WLINK or
other 32-bit DOS compiler. DOS4GW is a runtime extender, not a compiler or a
linker for the existing 16-bit OMF program. S1 therefore cannot honestly claim
a same-source 16/32-bit executable comparison. No new third-party toolchain
has been acquired.

## Result and next bounded work

S1 establishes a specific first target: replace or substantially reduce the
shared PPU's 256x240 per-frame slot-row composition work while preserving the
exact PPU state, palette, OAM ordering, pixels and frame cadence. A future
candidate must first profile the proposed shared preparation/cache shape under
the identical route. It must not use frame skipping or a reduced image contract.

Text-mode timing is a separate requested route. Its initial diagnostic variant
did not complete its text path within the 60-second isolated runner bound, so
no numeric text claim is recorded here; this confirms only that it needs its
own bounded fixture rather than extrapolation from the graphics numbers.


## Replanned S task sequence

The original S2--S7 plan made an implementation decision before it had a
reproducible post-Start route.  S3 demonstrated why that is unsafe: its
title-only gain did not survive a nonempty-OAM DOS route and the code was
removed.  The remaining work is therefore ordered by measurable owner and
uses one common graphics route before any accepted timing claim.

After S5/S6, the retained-VGA route is deliberately split at the only safe
composition boundary. S7 owns a scrollable, sprite-free PPU background
projection. S8 owns every transient pixel laid over it: the fixed status
region and sprites. A single S must not both change the permanent surface and
attempt damage restoration, because a failure in either would otherwise be
indistinguishable from an OAM/PPU semantic regression.

| S | scope | expected code scale | admission decision | closure condition |
| --- | --- | ---: | --- | --- |
| S1 | Fixed-3000-cycle stage attribution | diagnostics only | closed: row composition is the dominant cost | receipt identifies a bounded first owner |
| S2 | Exact byte-background span-copy accelerator at the PPU/neutral-output boundary; DOS16 provides only a physical equivalent copier | 80–180 product lines, 80–160 validation/probe lines | closed: accepted for exactness and operational build proof; no comparable timing delta claimed | pixel-equivalent graphics routes; current x86/x64 and DOS16 builds |
| S3 | Once-per-frame OAM-to-band schedule for aligned 16-row views | 100–170 product lines, 40–80 validation lines, about 975B transient view data | closed/rejected: title-only measurement and unstable nonempty-OAM DOS route | removed completely; no performance credit retained |
| S4 | Common-route fixture recovery and attribution | private diagnostic only | closed: post-Start route identifies the physical background store as the largest measured owner | title, post-Start gameplay and nonempty-OAM intervals each complete; root/PPU/publication costs have the same timer boundaries |
| S5 | DOS native-VGA surface feasibility: determine whether planar/page/panning storage can avoid the measured full A000 background rewrite without changing selected slot pixels | private probe first; production code only after a positive result | admitted from S4's largest measured block | exact 256x240 mapping, palette/split/text restore and no conventional-memory framebuffer; no PPU/core/game branch |
| S6 | Shared PPU dirty-output contract: neutral tile invalidation information derived from the existing compositor cache, never from game RAM | 100–220 shared PPU/IO lines, 100–180 validation lines | closed: exposes only the prepared-cache 1,920-bit descriptor | exact cache invalidation; no platform-visible game state or changed PPU decision |
| S7 | DOS16 retained **background only**: PPU-selected tile delivery, 512-by-480 planar projection, and CRTC/panning viewport | 200–400 DOS16/neutral-output lines, 140–260 validation/probe lines | admitted after S6 | exact scrollable background pixels against the established compositor; no sprites, fixed HUD, palette policy or conventional full-frame allocation |
| S8 | DOS16 temporary-overlay pass: restore old HUD/sprite rectangles from S7 background, then compose current HUD and descending OAM. P1 attributes retained work; P2 underlay reconstruction is rejected on a common route; P3 owns direct plane-pair access | 180–360 DOS16 lines, 140–260 validation/probe lines | only after S7 exact background route | exact fixed status split, sprite priority/masks, clipping and all dirty restore cases, plus a common-route result for P3 |
| S9 | Text presentation attribution and changed-cell output experiment | 80–180 product lines, 80–160 validation/probe lines | separate text route after S4 fixture is stable | all glyph IDs/cell colors/order exact; no platform game policy; comparable text-route gain |
| S10 | Portable core/root hot-loop profile and one shared candidate | diagnostics first; each accepted candidate gets a bounded patch | only if the common profile leaves core/root at least 20% of graphics cost | exact per-tick RAM/OAM/PPU/audio/input order; no DOS conditional game logic |
| S11 | Integrated graphics/text fixed-cycle validation, memory/stack/purity and local product build | mostly validation | only after accepted code from S7--S10 | report identical-route A/B deltas, memory cost and all rejected candidates; refresh local products only if code changed |

S2 is deliberately narrower than a generic PPU rewrite. The current byte background tier already retains two 256×240 palette-slot surfaces. Its hot byte-cache path copies one or two contiguous spans per visible row through the shared `mysmb_ppu_slot_row` implementation. The first experiment may introduce a neutral, synchronous span-copy capability with a portable fallback;DOS16 may bind an equivalent segment-once/DWORD copier. It cannot observe or alter game state, PPU writes, scroll selection, palette choice, sprite ordering or cadence.

S3 does not assume that an OAM index list wins: an earlier broad candidate was rejected on mixed/dense regressions. It is conditional on S2 measurement and must compare its schedule to the current descending OAM behavior.

## S2 closure: byte-background batch copier

S2 keeps the byte-background cache's shared PPU selection rules intact, but
lets a host copy a contiguous group of already-selected 256-slot rows through
one neutral callback. The grouping stops at the status split, vertical wrap,
or the requested row boundary. A callback rejection uses the pre-existing
portable per-row compositor, so it has no alternate visual semantics. DOS16
binds only a segment-preserving DWORD/byte copier; Windows and every other
host retain the portable path.

The focused byte-background smoke suite compares cache and uncached pixels
across 512 generated states, including split, wrap, masks, OAM and rejected
callback cases. `ppu-rows-smoke`, the DOS root smoke and platform-purity
checks pass on both Win32 widths. The original OpenNT16 plus LINK 3.65 route
also links the current source; a private fixed-3000 DOSBox graphics route
with the callback bound reaches game frame 418 without a device or memory
fault.

The current no-text-toggle graphics fixture reports 39,601 PIT ticks per
measured root step (33.19ms, 200 steps). It is deliberately **not** a claimed
delta from S1's 50.432ms result: S1's diagnostic route included a text toggle
and the two fixtures are not interchangeable. A disabled-callback A/B runner
did not emit its completion receipt, so S2 records no numerical copier saving
rather than inferring one. Its accepted result is the pixel-identical
capability and its bounded operational proof; T38 S5 must obtain one common
route before publishing an integrated gain.

S2 has zero ROM-node and control-edge scope. Historical nodes remain
`1992/1992`, local current nodes `1991/1992`, and feasible controls
`4260/4261` (raw `4342`, infeasible `81`). The next independent owner is S3:
derive a transient, descending OAM-to-16-row-band schedule once per prepared
view, then use it only for exact full bands. It must retain every OAM order,
clipping, opacity and priority decision and fall back to the existing range
scan for partial bands.

## S3 active implementation checkpoint

S3 stores up to 15 descending OAM index lists in a prepared frame view. It is
about 975 bytes of transient view data, has no allocation, serialization or
platform branch, and is used only when a caller asks for one aligned 16-row
band. Full-frame and partial-row callers retain the established range scan.
The focused test asserts list order across a band boundary and the final band,
then compares all three generated bands to the reference pixels. Its wider
512-state route covers 188,743,680 row pixels. The current x64 host build
passes that route, byte-background equivalence, DOS-root smoke and platform
purity. OpenNT16 plus LINK 3.65 also links the implementation to a 326,377B
local MZ output.

## S3 rejected: shared OAM-to-band schedule

The same private DOS16 fixture was linked twice with the same compiler,
resources, fixed `3000` DOSBox configuration, 60-step route and per-stage PIT
instrumentation. The only difference was whether aligned 16-row calls
received the prepared schedule. The no-schedule run averaged 47,034 root PIT
ticks and 28,079 row-composition ticks; the schedule run averaged 45,343 and
26,462 respectively. That is a root reduction of 1,691 ticks (3.60%, about
1.42ms) and a row-composition reduction of 1,617 ticks (about 1.36ms).

The stage reads add identical diagnostic overhead to both binaries, so these
are comparative—not physical-486—figures. The schedule adds 975 transient
view bytes and the linked private MZ grows from 329,981B to 330,157B. Exact
host pixel routes cover complete/partial rows, OAM ordering, crossing-band
sprites and the final band; the DOS16 link and both fixture routes complete.
This fixture sends Start at step 180 but runs only 60 steps, so it measures
title rendering rather than gameplay. When extended, the schedule variant
stops before the title demonstration's nonempty OAM route completes; therefore
the host pixel suite did not cover a safe DOS16 operational ABI. The attempted
schedule is fully removed from production rather than retained behind a flag.
The title-route figures are not a game-performance claim. S3 records a
rejection, has zero ROM-node/control scope, and leaves the historical counters
unchanged. A fresh S4 will profile a route that first proves the unchanged S2
baseline can pass the same nonempty-OAM interval before selecting another
optimization.

## S4 closure: common-route attribution

S4 rebuilt a private fixture from the current S2-only production sources. It
sends Start at root step 180, holds right/run thereafter, completes 260
unpaced root steps at fixed DOSBox 3000 cycles, and measures the last 40
steps. It returns normally at translated game frame 258. This is the first
accepted post-Start route for the current source; it is not a title-only
substitute and it changes no product source.

The uninstrumented route reports 36,851 PIT ticks per root step (30.88ms):
25,279 ticks (21.19ms) in PPU row composition and 2,397 ticks (2.01ms) in
palette plus device submission. A separate diagnostic build adds two nested
PIT boundaries to every one of the fifteen PPU bands. Its extra clock reads
raise the total to 43,382 ticks, so its nested values are attribution data,
not a replacement baseline: 13,203 ticks surround byte-background row output
to the direct A000 aperture and 11,911 surround sprite traversal/overlay.
Their 25,114-tick sum accounts for the uninstrumented 25,279-tick composition
block once the additional timer overhead and small band setup are excluded.

The largest measured owner is therefore not ROM logic or a shared PPU policy:
it is the DOS16 physical background-store loop in platform/dos16/slot_copy.c.
That loop currently enters its segment-copy routine once per row, up to 240
times per frame, although the PPU has already chosen all source spans. S5
receives only this bounded physical-output owner, first as a native-VGA
feasibility probe rather than a small segment-loop rewrite. It must preserve
the same 61,440 logical slot pixels and leave core, PPU, cache selection,
palette selection and cadence untouched. S6 remains the separate
shared-sprite candidate.

S4 has zero ROM-node/control scope. Historical nodes remain 1992/1992, local
current nodes 1991/1992, and feasible controls remain 4260/4261 (raw 4342,
infeasible 81).

## S5 admission: DOS16 native VGA-surface feasibility

S4 shows that a small segment-loop cleanup cannot plausibly close the gap: the
current direct A000 background rewrite alone is about 13.2ms in the nested
attribution. S5 therefore has no production edit at admission. It evaluates a
DOS16-only planar VGA surface that uses VGA memory, not conventional memory,
for a 256x240 retained background and page/panning presentation. The neutral
PPU remains the exclusive producer of the same selected slot pixels.

The owner-supplied NESticle binary is a local reference only. Its README
documents native 256x224/256x240/256x256 VGA modes, but its third-party binary
is neither imported nor treated as source. It only supports investigating a
VGA-resident presentation strategy; it supplies no implementation or behavior
claim.

The feasibility probe must establish the planar address formula, page and
viewport capacity within 256KiB VGA memory, 256x240 scan repeat, palette
updates and restoration to text. It must reconstruct selected rows byte for
byte, use no added conventional-memory frame buffer, and retain the status
split. If it still requires a full 61,440-byte rewrite per game frame, S5
rejects the approach rather than disguising it as an optimization. Only a
successful probe may admit a later DOS adapter; core, PPU, shared IO and game
logic remain outside S5.

Initial static capacity accounting is positive, but it is not an acceptance:
an unchained 256x240 surface occupies 15,360 bytes in each of four planes
(61,440 bytes total). A 512x240 virtual background occupies 30,720 bytes per
plane, and two 256x240 display pages add 30,720 bytes per plane. Their total
is 61,440 bytes per plane, or 245,760 bytes across the standard 256KiB VGA
aperture, leaving 16,384 bytes. The unresolved issue is composition, not
capacity: sprites and the fixed status region must be restored from a neutral
background source without forcing a full rewrite. That is why a positive S5
would lead to the explicit PPU dirty-output contract in S6 before any product
presenter is admitted.

The first isolated OpenNT16/LINK 3.65 probe now confirms the storage premise
under the unchanged fixed-cycle DOSBox VGA model. It switches from BIOS mode
13h to unchained four-plane addressing, writes and reads distinct values at
per-plane offsets 0, 30,720, 46,080 and 61,439, and reconstructs a 256-pixel
row by selecting plane `x mod 4` at byte `x / 4`. It returns `ok=1`, reports
a 128-byte virtual stride and restores text mode. This proves only VGA memory
addressability and capacity in the emulator; it does not yet prove CRTC scan
presentation, line-compare status splitting, physical VGA compatibility, or a
performance gain. S5 remains active for those bounded checks.

### S5 working receipt: CRTC viewport addressing

The second private probe uses the product's existing 800-by-525,
double-scanned 256-by-240 CRTC timing, then changes only the sequencer memory
mode to planar addressing.  It verifies the following device-level contract
under the same unmodified DOSBox VGA model:

| item | result |
| --- | --- |
| CRTC timing registers | `63,65,223`: 256 logical columns, two physical scanlines per logical row, 240 logical rows |
| virtual row stride | CRTC offset `64` words = 128 bytes per plane = 512 logical pixels |
| display-page starts | CRTC start accepts and reads back page A `0` and page B `15360` words (`30720` bytes per plane) |
| viewport addressing | page B plus logical row 17 plus coarse X 23 reads back as word address `16471` |
| fine scroll | attribute-controller horizontal panning accepts and reads back both `7` and `0` |
| plane storage | four plane-specific values through byte offset `61439` reconstruct without mismatch; text mode restores normally |

This is a hardware-register feasibility receipt, not a rendered-frame or
performance result.  Register read-back cannot prove physical scanout, tear
behavior, line-compare splitting, or 486 VGA compatibility.  It does prove
the address units required by a later presenter: a 512-by-240 retained region
is 30,720 bytes per plane; a vertically wrapping 512-by-480 region is 61,440
bytes per plane and consumes 245,760 bytes of a 256KiB VGA aperture.  That
leaves no independent full display page.  A viable future design must therefore
restore sprite/HUD damage from the same retained background and synchronize
updates; it cannot silently reintroduce a complete per-frame background copy.
S5 remains active until that design has a bounded scanout/split disposition.

## S5 closure: retained-surface disposition

S5 closes its feasibility scope with a positive DOSBox-device result and no
product edit.  The accepted next design is a single planar VGA-resident
surface, rather than a page-flipped display:

1. The PPU background is retained as a 512-by-480 physical projection.  Its
   second 240 logical rows duplicate the first vertical-mirroring period, so a
   240-row viewport may begin at any `visible_scroll_y` without hardware
   wrapping.
2. The DOS presenter selects the current horizontal/vertical viewport through
   the validated CRTC start and 0--7 pixel panning registers.  It does not
   choose PPU scroll, palette, sprite ordering, or game state.
3. Fixed status pixels and sprites are temporary damage over that retained
   surface.  Before their next locations are drawn, the shared PPU restores
   their previous rectangles from the same background projection.  This avoids
   a second full display page and avoids copying all 61,440 logical pixels.
4. Palette updates remain per-frame DAC writes.  The later presenter waits for
   retrace before modifying currently scanned damage; physical-VGA tear and
   LCD qualification remain an explicit later operational check.

This gives S6 a bounded shared responsibility: report *which PPU background
tiles changed*, as a 1,920-bit nametable map, after the existing cache has
made its normal decision.  It cannot inspect gameplay RAM or publish DOS
addresses.  S7 receives only the mapping of those neutral PPU tiles to the
validated VGA surface; S8 separately owns sprite/HUD restoration.  This is a
device-feasibility closure, not a physical-display acceptance or a performance
claim.

## S6 admission: neutral PPU background-damage contract

S6 adds a bounded 240-byte, two-nametable 32-by-30 tile bitset to the existing
PPU workspace.  `mysmb_ppu_slot_prepare` marks a tile only when it rebuilds it;
an invalidated CHR/pattern binding marks all 1,920 tiles.  A read-only PPU API
copies that map after frame preparation.  The API has no platform parameter,
DOS pointer, game-state field, cadence decision, or cache-policy branch.

The S6 test fixture will drive unchanged, one-tile, shared-attribute and
full-invalidation states.  For every marked tile it reconstructs the existing
slot cache and compares all 64 palette-slot pixels against the pre-existing
row compositor; it also proves unchanged states return an empty map.  Existing
graphics/text outputs must remain byte-identical.  No product target or DOS
artifact is rebuilt until this shared contract passes its focused test and both
host widths.  S6 has zero ROM-node/control scope; counters remain historical
`1992/1992`, local `1991/1992`, feasible `4260/4261` (`4342` raw, `81`
infeasible).

### S6 implementation checkpoint

The first shared implementation adds the 240-byte descriptor and no platform
consumer. It is reset at workspace/background binding and at the beginning of
each ordinary cache preparation. The cache's existing per-tile rebuild branch
sets the matching `table * 960 + row * 32 + column` bit; the existing complete
CHR/pattern/rebind invalidation fills all 240 bytes and sets `full`. The
descriptor is copied only from an active prepared frame view, so callers cannot
borrow internal cache or platform memory.

The new focused smoke reports `initial1920 unchanged0 tile1 attribute16
palette0 full1920 readonly=1`. It passes in fresh x86 and x64 build trees
alongside `ppu-rows`, `ppu-byte-background`, `ppu-frame`, `dos16-root` and
platform-purity. The original OpenNT16 compiler also compiles the modified
shared `ppu/frame.c` to a 16,209-byte OMF object with the real far-pointer ABI.
The checkpoint made no visible product-output, DOS-presenter or timing claim;
the closure below records its completed build and review evidence.

## S6 closure: neutral cache-output contract

S6 closes after the focused descriptor test, the companion tile-output test,
existing PPU frame/damage/root smoke suites, both Windows widths and direct
OpenNT16 compilation of `ppu/frame.c`. The descriptor reports 1,920 initial
tiles, zero unchanged tiles, one direct tile, sixteen tiles for a shared
attribute and 1,920 after a CHR/pattern invalidation. The new tile accessor
returns the same 64 slot bytes as the existing row compositor for both byte
and packed background cache layouts. No game state, platform address or
rendering policy enters either API.

## S7 admission: retained background and viewport

S7 is intentionally two bounded layers within one physical-output owner:

1. A neutral bridge delivers only the already-selected 8-by-8 palette-slot
   tile bytes for S6-marked nametable positions. It has no scroll, palette,
   OAM or game-RAM choice.
2. DOS16 maps those bytes to a 512-by-480 four-plane VGA projection and sets
   a CRTC/fine-pan viewport. The 240-row second copy supplies vertical
   wrapping without a conventional frame buffer.

The first checkpoint supplies both layers but does not switch the normal
presenter. A host smoke proves initial 1,920-tile projection, zero work for an
unchanged prepared view and one write after one changed tile. A second smoke
proves the plane/offset mapping through the final byte `61439`. OpenNT16
compiles the bridge and the device implementation with the real far-pointer
ABI. The current chain-4 presenter remains the only user-visible path until
S8 owns HUD/sprite restoration, so this checkpoint makes no visual or timing
claim.

## S1 closure

S1 completes its zero-ROM audit scope. It changes no node or control relation: historical `1992/1992`, local current `1991/1992`, feasible controls `4260/4261` (`4342` raw, `81` infeasible) remain unchanged. The fixed-cycle receipt identifies shared PPU output as the receiving owner; no ROM logic or node correction is transferred. S2 is admitted as an implementation task with an explicit zero-ROM scope, and must not claim ROM-equivalence credit merely from a rendering optimization.
## S7 closure: retained background and viewport

S7 closes without changing the normal product presenter. The shared PPU now
provides only a changed-tile map, individual selected 8-by-8 slot tiles and a
read-only scene viewport. DOS16 maps the two nametables to a 512-by-480,
four-plane surface and duplicates the 240-row period. Its device code sets the
S5-proven unchained timing, CRTC start and fine pan, but rejects any
sprite-0/fixed-status view because S8 must own that overlay.

Host tests prove 1,920 initial writes, no work for an unchanged view and one
write for one changed tile, as well as all plane offsets through byte 61,439.
The focused x86/x64 suites and platform-purity check pass. OpenNT16 compiles
`frame.c`, `retained_background.c` and `devices.c`. A private, source-built
DOSBox probe originally failed before `main` because its >2KiB PPU state was
placed on the 2KiB DOS stack; after moving that probe state to static far data,
it records `start`, `prepared`, `open`, `present`, `closed`. This validates the
actual S7 device call and mode restoration path. It is not a performance or
user-visible-product result.

## S8 admission: retained-surface overlays

S8 owns the missing transient composition layer. Before writing current-frame
fixed HUD or sprites, it restores every prior transient pixel rectangle from
the S7 retained PPU background. It then obtains neutral PPU overlay output and
writes the current fixed-HUD/sprite pixels in original descending-OAM order.
The shared PPU, not DOS16, must decide sprite opacity, priority, clipping,
left-edge masks and fixed-status behavior. DOS16 may only restore/write the
already-selected coordinates and palette slots.

The design must avoid a 61,440-byte conventional frame. It may keep bounded
previous-overlay rectangles/bitmaps only when their maximum size, restoration
source and invalidation lifetime are explicit. Acceptance requires exact
comparison to the existing full compositor across fixed status, sparse/dense
OAM, priority, clipping, background tile changes, scroll and all-visible-mask
combinations, then the S4 fixed-cycle route. No product switch or timing claim
precedes those comparisons.

## S8 closure: retained-surface overlay rejected

S8 satisfies its investigative acceptance with a negative result. The shared
PPU and host exact-model checks establish that the retained presentation can
restore fixed status and descending OAM coverage without changing PPU policy.
The common fixed-3000 DOSBox route rejects it for performance: P3's direct
per-plane C loop measures 49,524 uninstrumented PIT ticks per post-Start step
(about 41.5ms). Its comparable nested receipt is 51,006 ticks, versus 116,703
before direct pairing, but the established S4 Chain-4 route is 36,851 ticks
(30.88ms). The retained path is therefore not product-enabled.

`main_dos16.c` leaves the retained binding dormant and returns the DOS product
to the established Chain-4 row presenter. The retained source remains an
isolated, nonselected feasibility record; it makes no ROM-node or control-edge
claim. Historical nodes remain 1992/1992, local current nodes 1991/1992, and
feasible controls 4260/4261 (raw 4342, infeasible 81). The next performance
receiver must optimize the selected Chain-4 pipeline or establish a new
compiler/display architecture that beats its 30.88ms common-route baseline.

## Superseding S9--S15 partition: selected-path performance work

The retained experiment demonstrated that changing a large architecture before
measuring the selected presenter loses both time and a useful comparison.  The
remaining T38 work is therefore repartitioned by measured owner.  Every S uses
the same post-Start, fixed-3000-cycle route and reports an uninstrumented
whole-step result before it can claim a gain.  No S may use frame skipping,
fewer pixels, a DOS-specific game core, or a second presentation semantic.

| S | owner and purpose | allowed change | transfer / close condition |
| --- | --- | --- | --- |
| S9 | Selected Chain-4 attribution | private fixture only | Split the 36,851-tick route into shared background selection, physical A000 store, sprite traversal/opacity/write, and remaining root work. Close with a reproducible table and one receiving owner. |
| S10 | Selected physical-output owner | `platform/dos16` only | Test one bounded Chain-4 store strategy against the same neutral rows. Keep it only if the uninstrumented route beats 30.88ms and pixels remain exact. |
| S11 | Retained physical-output v2 feasibility | `platform/dos16` only, private binding until exact | Replace S8's per-pixel fixed-HUD restore/redraw with plane-contiguous transfers. It is accepted only when physical VGA readback equals the shared slot compositor on title, scrolling, fixed HUD and OAM routes and the common route beats 39,026 ticks. |
| S12 | Retained transient sprite physical owner | `platform/dos16` only, conditional on S11 acceptance | Batch the physical sprite backup/restore/write route by plane without changing PPU OAM enumeration, opacity, clipping or ordering. Keep it only if it beats the accepted S11 route under the same readback proof. |
| S13 | Shared PPU sprite attribution | private `ppu/` probe only | Establish whether repeated OAM scheduling, decoded-pattern work or per-pixel overlay is the material owner; do not retain a cache whose measured ceiling is immaterial. |
| S14 | Staged Chain-4 composition feasibility | private `platform/dos16` root/device only | Compare PPU composition into the existing 4KiB band RAM followed by one Chain-4 publish against direct A000 composition. Keep no change without exact pixels and a material whole-route gain. |
| S15 | Selected shared compositor reduction | `ppu/` and neutral `io/` only, conditional on S14 | Optimize the proven shared owner only; preserve slot rows, OAM order, clipping, priority and masks. |
| S16 | Portable game/root hot path | shared C only, conditional on a measured >=20% owner | Make at most one semantics-preserving common-C reduction after proving the owner share. Verify original state/output order before and after. |
| S17 | Exact retained-overlay reconstruction | private `platform/dos16` plus existing neutral PPU views | Replace rejected VGA readback backup with bounded software reconstruction of the previous overlay coverage; accept only after physical readback is exact and route beats S10. |
| S18 | Integrated qualification | validation and packaging only unless a prior S is accepted | Compare graphics and text separately, sparse/dense OAM, scrolling, title and restore routes; record conventional memory and publish current artifacts only if product code changed. |

S9 began this partition with zero product lines and zero ROM-node
and control-edge scope; its purpose was to prevent later work from optimizing
a dormant path again. S10--S15 are conditional successors, not pre-approved
product edits. S11 is now the active owner.

## S9 closure: selected Chain-4 receipt and S10 admission

S9 rebuilt the current selected presenter from the active source and used the
same post-Start 40-step fixture at fixed DOSBox 3000 cycles.  The private
instrumented executable reports 46,722 PIT ticks per root step; the probes
raise the whole-step reading and are used only for nested attribution.  Its
separate uninstrumented build reports **44,038 PIT ticks (36.91ms)**.  This is
the current source baseline; the older 36,851-tick S4 receipt remains
historical evidence, not an interchangeable present-day baseline.

| current selected-path owner | nested PIT ticks | interpretation |
| --- | ---: | --- |
| row compositor total | 32,026 | background, sprites and view setup for the 15 submitted bands |
| background path | 16,483 | selected slot-row work for all visible rows |
| `platform/dos16/slot_copy.c` A000 store | 12,242 | subset of background path; physical selected-slot transfer |
| sprite traversal/opacity/overlay | 11,910 | complete descending-OAM overlay path |
| remaining row-compositor work | 3,633 | row selection/setup outside the two attributed bodies |
| palette plus direct-band completion | 2,398 | DAC/device work |
| root outside row presentation | 9,614 | translated tick, frame preparation, audio/frame marshaling and root work |

The fixture also removed only the per-frame bookkeeping writes for the
rejected retained-presenter tile-damage map.  It measured 44,037 ticks, a
one-tick difference.  That path is not a credible S10 target and no product
code changes from the test.

S10 is now admitted with zero ROM-node/control-edge scope.  It owns only the
normal Chain-4 physical copy in `platform/dos16/slot_copy.c`: retain the same
source spans, 61,440 selected palette slots, rows, destination addresses and
failure contract, but replace repeated per-row segment setup with a bounded
band transfer when contiguous runs allow it.  The expected product change is
40--100 DOS16 lines and no shared/core/PPU line.  It closes only after exact
row-copy tests, x86/x64/purity checks, DOS16 link and an uninstrumented common
route comparison against 44,038 ticks.  A marginal result is rejected rather
than presented as a route to 20ms.

## S10 closure: selected physical-store transfer

S10 replaces the selected Chain-4 row copier's per-row `DS`/`ES` setup with a
single contiguous band move when the row source is complete; split sources keep
the same first/second spans and advance both far pointers by exactly 256 bytes
per row. The host-free DOS16 fixture checks 16 rows for complete 256/0 and
split 255/1, 128/128, 17/239 and 1/255 spans byte-for-byte. Its full
post-Start, fixed-3000-cycle route remains at frame 258 and measures **39,026
PIT ticks (32.71ms)** per step, against S9's 44,038 ticks (36.91ms): **5,012
ticks / 4.20ms / 11.4% lower**. This is a real selected-path improvement, not
a retained-path claim.

The change is confined to `platform/dos16/slot_copy.c`; it adds no allocation,
no game/ROM/PPU decision and no Windows behavior. Focused PPU row, byte
background, DOS-root and platform-purity tests pass in an isolated host build;
Win32 x86/x64 rebuild; OpenNT16 compiles and LINK 3.65 produces a 346,365-byte
MZ. The three local product artifacts were refreshed. ROM scope, exact nodes
and control relations are unchanged: scope[], historical 1992/1992, local
1991/1992, feasible controls 4260/4261 (raw 4342, infeasible 81).

## S11 re-admission: retained physical output, second design

S10 changed the decision boundary. Its 5,012-tick saving establishes that the
selected physical transfer was material, but the remaining 39,026-tick route
cannot reach 20ms through a small shared-PPU cache. The nested S9 receipt puts
only 4,241 ticks between background selection and the physical store, whereas
sprite overlay remains 11,910 ticks. The earlier S8 retained path is therefore
not repeated as an unchanged proposal: it is a rejected reference because its
per-plane C writes were 49,524 ticks.

S11 owns a bounded **DOS16 retained physical-output v2 feasibility study**.
It may inspect and test only neutral PPU rows/viewports and physical VGA
addressing. The candidate must retain a scrollable background and restore/redraw
transient HUD/OAM without submitting a complete 61,440-slot frame. Its new
criterion is physical work: it must show exact pixels and an uninstrumented
selected route below S10's 39,026 ticks before product binding. The experiment
cannot add game/PPU policy, alter a translated update order, introduce a full
second logical frame, use frame skipping, or change DOSBox settings. Shared
PPU work is deferred to S12 unless this S11 measurement proves it is at least
20 percent of the selected path; core work stays conditional after that.
## S11 closure: retained physical-output v2 is not accepted

S11 measured a private DOS16 retained-v2 route at 30,636 PIT ticks (25.68ms)
on the established post-Start fixed-cycle fixture, below S10's 39,026 ticks.
That timing result is not an acceptance result. The private device readback
compared the final physical VGA surface with `mysmb_ppu_frame_slot_rows` on the
same prepared PPU view. It found 233 mismatching pixels in the gameplay route
(`x=88..158`, `y=80..118`). The current frame's 143 emitted sprite pixels all
read back exactly after their writes, so the discrepancy is stale prior-frame
sprite coverage rather than the S11 HUD/background transfer. The temporary
plane-packed HUD implementation is removed from the dormant product path;
there is no product switch, artifact refresh or ROM-node change.

S11 therefore closes as a useful negative integration result: its background
transfer candidate is bounded and faster, but cannot enter the product while
the inherited retained sprite restoration fails exact physical readback.
Counters remain scope[], historical 1992/1992, local 1991/1992 and feasible
controls 4260/4261 (raw 4342, infeasible 81).

## S12 admission: retained transient sprite restoration and batching

S12 owns only `src/platform/dos16`'s retained sprite backup, restoration and
physical write path. It must first make prior-frame transient coverage exact
across movement/scrolling, overlap, clipping, fixed status and dense OAM by
using the same physical-VGA readback oracle. Only after that exactness proof
may it batch plane operations or reduce register traffic. It may not change
PPU sprite enumeration, order, opacity, clipping, scroll/status policy, core
state, DOSBox settings, output resolution or cadence. The candidate stays
private and unbound until its whole route beats S10's 39,026 ticks and passes
all readback cases. ROM scope[], expectedMatches[], actualMatches[]; this is
an implementation S with zero ROM-node/control-edge credit.
## S12 closure: retained sprite recovery rejected

S12 first isolated the S11 residue to the retained transient model, then tested
two private replacement recovery sources. Direct old-VGA restoration leaves 233
pixels; current-screen scene recovery and old-world tile recovery both leave
425 pixels. A frame-by-frame physical oracle finds the first divergence at
fixture frame 29, during title OAM animation before Start, scrolling or normal
gameplay movement. The retained model is therefore rejected as a whole: it is
not a trustworthy base for additional batching. All S12 changes remain below
ignored `build/`; the selected S10 Chain-4 presenter is unchanged.

## S13 admission: shared sprite-composition attribution and reduction

S13 receives the measured 11,910-tick selected-route sprite traversal,
opacity and overlay owner. It will profile this shared `ppu/frame` work on the
healthy Chain-4 presenter, then test one bounded cross-platform reduction that
retains descending OAM order, clipping, left-edge masks, behind-background
priority and all selected slot pixels. Any candidate must pass the existing
sprite overlay matrix on x86/x64 and improve the fixed 39,026-tick DOS route;
otherwise it is removed. ROM scope[], expectedMatches[], actualMatches[].

## S13 closure: sprite cache rejected before product change

The private fixed-3000, post-Start probe records 11,913 nested PIT ticks for
the complete sprite loop, matching S9's 11,910-tick attribution. A second
probe around every vertically intersecting sprite records 10,792 ticks but
adds a clock/probe call to every intersecting sprite and raises the whole
instrumented step from 35,998 to 38,591 ticks. Thus the apparent remainder is
dominated by probe overhead; repeated 64-entry band scanning is not a credible
multi-millisecond owner. A 4KiB pre-expanded sprite cache would retain the
same pattern/opacity/priority and per-pixel work while adding resident memory,
so S13 rejects it before any product change.

The next measured question is physical locality: the selected presenter copies
cached background slots straight to A000 and then the shared compositor writes
sprite pixels to that aperture. S14 will privately compare this with composing
the same 16-row band in the already-reserved 4KiB RAM band and publishing it
once through the existing Chain-4 path. No PPU or game rule changes transfer;
scope[], historical 1992/1992, local 1991/1992 and feasible 4260/4261
(raw4342,infeasible81) remain unchanged.

## S14 admission: staged Chain-4 composition feasibility

S14 owns a private DOS16 presentation experiment only. It changes the physical
destination of the existing synchronous 16-row PPU output from direct A000 to
the already allocated 4KiB band, then invokes the existing Chain-4 publisher.
The PPU receives the same state, rows, palette slots, OAM ordering, priority,
clipping and masks. There is no new frame allocation, retained surface,
cadence change, core fork or DOSBox setting change. Exact byte/physical output
and the common fixed-3000 route decide acceptance. The candidate is rejected
unless it materially beats 39,026 PIT ticks; ROM scope[], expectedMatches[]
and actualMatches[].

## S14 closure: full-band RAM staging rejected

The private A/B used the same current source tree, fixture and fixed-3000
DOSBox configuration. Direct A000 composition measured **32,642 PIT ticks**;
the otherwise identical RAM-band composition followed by the existing
Chain-4 publish measured **38,849 ticks**, 6,207 ticks (19.0%) slower. The
extra complete 4KiB physical submission costs more than avoiding direct sprite
writes can recover. The experiment changes no product source, allocation or
ROM control. S15 therefore receives only the narrower sparse-current-overlay
question: it must never re-submit an unchanged complete band.

## S15 admission: sparse current-frame sprite patch feasibility

S15 privately evaluates a current-frame-only DOS16 patch publisher. It begins
from the same shared background rows and uses the existing neutral descending
sprite tile enumeration. It may stage and submit only coalesced sprite-covered
spans of the current 16-row band, never retain prior-frame pixels or create a
second logical frame. PPU ownership of OAM order, opacity, background priority,
clipping and left-edge masks remains unchanged. The candidate must prove exact
slot/physical pixels on the full overlay matrix and materially beat the
32,642-tick direct-A000 control before product code is considered. ROM
scope[], expectedMatches[] and actualMatches[].

## S15 closure: sparse sprite publication rejected

The private candidate published the existing shared background rows, then
consumed the unchanged neutral `mysmb_ppu_frame_sprite_tiles` enumeration in
descending OAM order. It measured **36,938 PIT ticks** on the matched route,
against S14 direct composition's **32,642 ticks**: 4,296 ticks (13.2%) slower.
The separate API traversal and device callback outweigh the avoided per-band
sprite scheduling; no product source, allocation or PPU policy changed.

The remaining work is consequently not a menu of small caches. S16 receives a
fresh measurement of the portable root/core interval against the same selected
frame route. It may move only a demonstrated >=20% shared owner, preserving
the original RAM/write/order contract. S17 remains the only integration and
artifact publication receiver.

## S16 closure: shared game/root change rejected

The private matched fixed-3000 receipt measures 32,928 total PIT ticks,
21,129 ticks inside row production, 2,398 in device palette/publish, and
4,096 inside `mysmb_game_tick`. Game tick is about 12% of the route, below
the 20% admission threshold for shared core surgery. No ROM state, call order,
source or product allocation changed. The remaining target is physical output.

## S17 admission: retained-overlay software reconstruction

S11 proved a retained physical output can reach 30,636 ticks (25.68ms), but
S12 correctly rejected its VGA-readback sprite restoration after a title OAM
divergence. S17 does not revive that algorithm. It may privately reconstruct
prior transient coverage from PPU-selected background slots plus the prior
descending overlay order in bounded software patch storage; it must not read
VGA for authoritative pixels, retain a full logical frame, alter PPU policy or
change core state. Physical VGA readback must equal the shared slot compositor
on title animation, scroll, fixed status, sparse/dense overlap, priority and
clipping before timing matters. ROM scope[], expectedMatches[] and
actualMatches[].

## S17 closure: saved-background retained overlay rejected

S17 removed authoritative VGA readback and repaired a real PPU cache-key
omission: re-enabling `PPUMASK` background output now invalidates the derived
background map even if the nametables did not change. The focused host damage
test covers both mask transitions. The private physical route still diverges:
after the title transition, sparse repair leaves five old sprite pixels at
frame 30 and then sixteen at frame 31. The readback oracle classifies every
one as background, not a current OAM write. A diagnostic that rewrites every
background tile every frame is physically exact for all 260 fixture frames,
which proves that the retained sprite reconstruction itself lacks a sufficient
current-background repair boundary. It costs 652,614 PIT ticks per measured
frame, so it is only a diagnostic and cannot be selected.

S18 receives a different bounded design: collect the prior and current
PPU-selected sprite rectangles, repaint their union from the **current**
PPU-selected background, then write current descending OAM tiles. It does not
reuse saved background pixels, read VGA, retain a full logical frame, or alter
core/PPU policy. The same physical oracle must be zero for every fixture frame
before timing. ROM scope[], expectedMatches[], actualMatches[].

## S18 admission: current-background sprite-union reconstruction

S18 privately tests a two-pass retained overlay: PPU-selected current sprite
rectangles are gathered in original descending order; the union of prior and
current bounded rectangles is restored from current selected background; then
the unchanged current tiles are published in their original order. The
candidate owns only DOS16 physical storage and register writes. It cannot
change object order, visibility, masks, priority, scroll, fixed status, ROM
state, cadence, resolution, DOSBox configuration or allocate a frame-sized
logical surface. It must pass title, scroll, fixed status, sparse/dense OAM,
overlap, priority and clipping readback before its fixed-3000 timing is
considered. A result no better than the 39,026-tick selected baseline is
rejected. ROM scope[], expectedMatches[], actualMatches[].

## S18 implementation checkpoint: exact union repair and separated timing

S18 replaces the rejected saved-pixel restore with a current-background union:
it enumerates the previous and current descending-OAM 8-by-8 rectangles,
repaints their bounded union from the immutable PPU view, then submits the
current rectangles in their original order. The DOS device selects no game or
PPU policy. The shared PPU helper only copies a screen rectangle using the
already-latched split, scroll, name-table and mask selection.

The private physical oracle ran all 260 fixture frames with a complete VGA
readback after every presentation and reported `exact1 bad0 firststep0`.
That diagnostic reads all 61,440 physical pixels every frame and must not be
included in a presenter timing result. In the separately timed last forty
frames, after the full per-frame exactness pass, the same presenter reported
**218,468 / 40 = 5,461 PIT ticks per root step** (about **4.58ms** at
1,193,182Hz). This is provisional pending product-width builds, the normal
DOS16 MZ link and a no-diagnostic product route; it is not an artifact release
or an M2 node/control-edge claim.

The first partition instrumented the candidate internally: normal cache-damage
application averaged 18 ticks, fixed-status work 13 ticks, and the bounded
previous/current sprite-union reconstruction 4,898 ticks. The latter is the
remaining presentation cost in this fixture. The implementation's added
resident data is bounded overlay state: 8,192 bytes of packed prior HUD, 8,192
bytes of current HUD/scene scratch, and a second at-most-64 sprite record
array (4,288 bytes), rather than a frame-sized logical surface. The next S18
part is product qualification: build all targets, link the DOS MZ, re-run the
physical route from its private oracle source, then measure conventional-memory
load and text/graphics restore behavior before artifacts are refreshed.

Product-width qualification checkpoint: the regular source tree links with the
OpenNT16/DOS LINK 3.65 route to a 344,669-byte MZ. Its 48 map segments remain
within 16-bit bounds; DGROUP including the 2,048-byte stack is 52,592 bytes,
leaving 12,944 bytes before the near 64KiB boundary. With the established
4KiB initial near-heap policy, the loader reservation is 372,640 bytes
(373,056 page-rounded). This is only a load reservation receipt: it does not
claim dynamic far-heap use or real-hardware performance.

Focused x64 smoke tests pass for the rectangle accessor, mask-cache damage,
retained background delivery/application/overlay, and DOS root. The regular
source was also compiled and linked in the DOS16 product configuration. The
remaining active work is x86 product-width confirmation plus the graphics/text
restore route and artifact packaging; no artifact has been refreshed from this
checkpoint.

## S18 closure: exact retained presenter integrated

S18 binds the current-background sprite-union presenter to the normal DOS16
root.  It is no longer a dormant probe.  The private oracle source has the
same `ppu/frame.c`, retained device source, retained header and DOS root as the
bound product; the only private difference is its diagnostic `main`, which
adds physical VGA readback and PIT counters.  The one product header addition
is the declaration for the already-tested rectangle helper.  This establishes
that the 260-frame `exact1 bad0 firststep0` result applies to the selected
implementation rather than an adjacent experimental copy.

The normal product was then linked through the OpenNT16/DOS LINK 3.65 route
and exercised in the headless DOSBox fixture without changing any persistent
DOSBox setting.  Its graphics -> Tab text -> graphics route reports all of:

- stable paused graphics before Tab and byte-identical graphics after return;
- stable held and second text entries, with seven RGB colors and 58 distinct
  cell/color patterns;
- save, load while text is active, and Escape return to DOS.

The linked MZ is 344,733 bytes.  Its 48 map segments have a largest segment
of 58,312 bytes; DGROUP including the 2,048-byte stack is 52,592 bytes with
12,944 bytes of headroom.  The bounded 4KiB initial near-heap receipt reserves
372,704 bytes before DOS page rounding (373,056 after).  This is a loader
bound, not a claim about measured real-machine heap use or frame rate.

Focused retained-background/overlay/root and PPU rectangle/damage tests pass
on both x86 and x64, together with the platform-purity check.  S18 adds no
ROM node or control-edge credit: scope[], expectedMatches[] and
actualMatches[] remain empty; historical 1992/1992, local 1991/1992 and
4,260/4,261 feasible controls (raw 4,342; infeasible 81) are unchanged.

## Repartition after S18

The prior sequence mixed formal integration, timing, text throughput and
hardware applicability in one closing step.  The remaining work is now split
so that a result from one path cannot be represented as evidence for another:

| S | owner and bounded change | exit evidence |
| --- | --- | --- |
| S19 | selected retained graphics route only: repeat the post-Start fixed-3000 measurement on the **bound product**, compare it to S10's 39,026 ticks, then package the three local targets if the result remains exact | same 260-frame physical oracle, no-diagnostic product timing, DOS MZ memory receipt, x86/x64 builds and graphics/text lifecycle route |
| S20 | DOS and Win32 text presenters only: attribute cell construction, conversion and host output separately; accept at most one changed-cell/batched-output candidate | exact neutral 80x25/80x50 cells, colors and request order; separate text-route timing; no graphics/core policy change |
| S21 | shared portable preparation/root only: re-profile after S19, then admit one common-C reduction only if a named owner is at least 20% of the retained route | original RAM/OAM/PPU/audio/input-order equality, x86/x64 checks and DOS route; no DOS conditional logic |
| S22 | target-era qualification only: collect a reproducible 486-class or calibrated execution receipt and memory/stack observations for the chosen product | explicitly labeled hardware/calibration limits; no source change merely to satisfy a benchmark |

S19 is the next executable S.  S20--S22 are conditional successors, not
pre-approved code edits.  The target stays the owner's 20ms/10ms direction;
the measured 4.58ms private presenter interval is not yet a whole-game
real-hardware claim.

## T38 closure and transfer

The owner directed T38 to close around the optimizations that are already
integrated, rather than leaving the task open for unfinished measurement work.
The accepted product result is the S18 current-background sprite-union
presenter: it is selected by the normal DOS root, passed the 260-frame physical
oracle, the regular DOS graphics/text/save/load/exit route, focused x86/x64
tests and platform-purity check, and linked into the local DOS MZ.  The three
local target artifacts were rebuilt from this source.

S19 did not establish a comparable fixed-3000 timing number.  The old 5,461
PIT figure used `cycles=max`; it is retained only as a diagnostic.  The first
fixed-3000 rerun still executed the 61,440-pixel physical readback each frame
and reached fixture frame 40 before the sixty-second runner bound.  A private
attempt to rebuild the readback-free timing harness then exposed unresolved
private probe symbols; it did not change product source or product artifacts.
Neither result is a performance claim or a regression of S18 exactness.

Those unresolved items transfer intact to the queued
`retained-performance-qualification` candidate: a source-matched,
no-readback fixed-3000 timing fixture; any conditional graphics owner; text
throughput attribution; and target-era qualification.  The successor must not
reopen S18's accepted pixel contract without a concrete divergence.
