# M3 T30: shared PPU background and DOS plane-loop optimization

## Owner request and status

Owner explicitly admits performance continuation after closing T29. M3 T30
S1 is sole active implementation chain. Retained queued proposal is moved here;
CURRENT owns execution. Reference code2959c348:Win32 corrective products retained,
DOS product still T28 P22 byte-identical. This is read-only rendering optimization,
not whole-game ROM certification. Scope/expected/actual[],new0.

## Baseline and concrete costs

Retain T28 S6 P22 products and all applicable accepted receipts. P23 current
actual-loop diagnostic has graphics median 879.420ms: PPU 572.288ms, conversion
249.597ms and direct VGA submission 28.808ms. P24 layered diagnostic places
background at about 91.76 percent of PPU time in its loaded graphics fixture.
These are fixed-configuration diagnostic costs, not physical 486SX results.
Configured DOS playability is not accepted.

Current background already processes tile rows, uses an optional 8192-byte
packed CHR cache and stages a 256-byte row. Do not re-propose these as new work.
Current DOS output already writes A000 directly and uses bounded bands.

Static analysis of src/ppu/frame.c and retained product-bound 16-bit listings:
- Roughly 32-33 tile spans per source scanline. The cached address expression
  (pattern / 16) * 16 emits DIV followed by four shifts in the retained listing.
- Adjacent cached bytes reload far pointers; scalar output repeatedly reloads
  locals, calculates palette/output addresses and spills intermediate values.
- Each scanline repeats tile ID, attribute, palette and pattern-base resolution
  that neighboring rows within a tile can share.
- Empty spans still perform tile lookup and a small far memset call each.
- VGA conversion stages each 16-byte group through a small memcpy and performs
  scalar plane stores; shortening this loop must be measured under DOS16.
- Sprite cached/raw duplication and per-pixel background opacity lookup exist,
  but deferred OAM/raw-read/boundary-row tuning retains its TODO admission path.

## Admitted T scope and S plan

S1 is admitted now;S2-S4 are bounded planned slots and register on admission.
Each S includes implementation,independent comparison,DOS cost/memory review
and disposition;node-level original semantics stay unchanged.

1. S1 compact background loop. Owner src/ppu/frame.c and independent frame tests.
   Separate cached full-tile spans from clipped edges and raw fallback;
   strength-reduce unsigned arithmetic, prepare row invariants once, reduce
   far-pointer reloads and stack traffic. Estimate 80-180 product lines.
   Inspect original compiler output; no blind optimizer/toolchain substitution.
2. S2 tile metadata reuse. Shared read-only PPU owner, frame-local bounded row
   descriptors for tile/attribute/palette/base, reused across applicable source
   scanlines. Estimate 100-220 product lines and a few hundred scratch bytes;
   publish exact stack/near/far/lifetime layout before adoption. Invalidate at
   tile-row, name-table, scroll/split and source-state boundaries. Assess merging
   continuous blank spans, preserving every clipped and nonblank pixel.
3. S3 neutral four-plane loop. Owner src/platform/vga/vga_frame.c, existing neutral
   video contracts and independent mapping tests. Estimate 60-160 product lines;
   reduce tiny copies/pointer reconstruction within existing band storage.
   No gameplay/CHR/object interpretation in the platform layer.
4. S4 integrated graphics review. Compare cumulative output and actual product
   frame/input costs, memory and original compiled hot loops. Retain only
   candidates with justified whole-route speed/memory tradeoffs. Report whether
   fixed-config nominal 60Hz is reached. If it fails, name the remaining measured
   bottleneck and receiver; no successful playability closure from micro-gains.

## Verification and adoption contract

Preserve original game ticks, input order, audio, snapshot bytes and PPU-visible
state. Retain full 256x240 source, all colors, exact borderless 640x400 mapping,
scroll/mirroring, fixed HUD split, left clipping, sprite order/priority and raw
background opacity. No discarded pixels, frames/ticks or DOSBox-setting changes.
Use independent reference pixels and plane mapping, x86/x64 builds and the
original DOS16 compiler/runtime. Exercise scroll edges, split enabled/disabled,
palette aliases/animation, CHR bounds, cached/raw/failure routes, disabled layers,
water/castle/dense sprites, mode changes, restore and guards/source immutability.

Measure fixed-config DOS whole-route cost, not just one isolated function;
account for probe overhead. Bind listing claims to current product owners.
Every product-code P builds/tests/reports all three existing authorized EXEs.
Audit/doc-only P retains products. All prototypes/logs/generated resources stay
below ignored build; retain only neutral summaries. No new source imports.

No new large framebuffer or unlimited cache. Evaluate stack and conventional
memory together with speed. Metadata reuse must respect the existing row-store
lifetime and interrupt/stack headroom; a larger lookup is a separate reviewed
candidate. Existing deferred sprite/repeated-boundary-row work is not activated.

ROM scope/expected/actual are empty, new matches zero; historical 1992/1992,
local 1991/1992 nodes and 4260/4261 feasible controls (raw4342/infeasible81)
remain unchanged. Original node custodians retain responsibility.

## Retained experiments and rejected directions

T28 P24 offset-only prototype yields about 3.52 percent shorter ordinary
return-to-graphics route, about 3.07-3.28 percent in populated routes, with
32 additional diagnostic owned bytes. Native reference checks and DOS route
output agree; it is not adopted product code or a playability solution.
Pointer-array, eight scalar zero stores and 128-byte palette-pair variants
are weaker than this candidate. Prior whole-row prefill and fused direct-VRAM
alternatives have measured regressions. Do not repeat them without a specific
new explanation of the old regression.

## Exit and remaining-work boundary

Every slot records adopted/rejected findings, independent equality, cumulative
DOS costs and memory tradeoffs. Implementation closes only with no scoped output
or state differences and refreshed products. A failed cadence gate remains
explicit and requires an owner-directed transfer, not a performance-pass claim.
Full CRT/error/all-path stack/continuous peak, text performance and final mixed
mode cadence acceptance belong to the [remaining acceptance candidate](../proposals/m3/dos-memory-cadence-remaining-acceptance.md).
Physical 25MHz486SX/DOS-version qualification remains M4.
See [T28 retained closure](M3-T28-dos-rendering-optimization.md#s6-p24-owner-directed-closure-and-remaining-work-transfer).


## S1 admission

Owner src/ppu/frame.c and independent pixel/plane reference tests;estimate80-180
product lines. Begin with contained cached span/address/palette/output-pointer
variants;retain raw fallback and partial edges. Original16-bit listing binds
instruction claims. Native512-case equality plus actual fixed-config DOS output/
whole-route comparison precedes adoption. No new cache/framebuffer or deferred
OAM tuning;no assumptions that fewer C lines mean faster code. Current admitted
node baseline1992,total1992,scope/expected[],max1992;current local counts remain
1991/1992and4260/4261. Every adopted code P refreshes three products and reports
memory tradeoff;prototype-only P keeps them unchanged.


## S1 P1 first contained comparison

Prototype combines retained row-offset strength reduction with full cached-span
palette/output cursors and destructive two-bit extraction. No product source
change. Both widths independent512-case tests compare188743680strip bytes and
65536000plane bytes;guards,source immutability,invalid requests and raw/cache/
edge/split/alias paths pass. Original16-bit owner compiles/links.
Fixed-config normal SDL/private-desktop DOS route matches977235bytes of frame,
planes,text,cells and save;mode3restored,near/far storage freed. Installed config
hash unchanged. Whole return-to-graphics stage7cost is3.734percent shorter than
retained P24base,roughly0.2percentage points better than offset-only candidate.
Diagnostic owned393040versus392992(+48bytes),patterned unused stack72retained;
this is not actual product resident acceptance. Stage3is plane conversion,not
PPU;do not misattribute that unchanged stage to background gains.

Candidate remains contained,not adopted. Narrow gain does not discharge DOS
playability. Continue the S1 compiled-loop cohort before integration;original
fallback/full output/low-memory constraints remain. Three2959c348products and
ROM counters unchanged. Local reproduction:ignored native.py,Build-Compact.ps1,
run-compact.py and compact-summary.json under S1 build containment. No protected
trace/code/binary is committed. S1/T30remain active.
