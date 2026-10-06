# Shared PPU background and DOS plane-loop optimization

## Owner request and status

Owner requests this static-analysis plan as the first queue candidate and
closes T28 by explicit remaining-work transfer. Unnumbered, not admitted;
allocate the next ascending M3 T only upon admission. This proposal owns the
bounded graphics implementation, not whole-game ROM certification.

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

## Proposed S scopes

These are proposal slots; actual S identifiers and estimated sizes are
published at admission. Each implementation slot includes its own scoped
comparison, repairs and re-audit, rather than a separate paperwork S.

1. Compact background loop. Owner src/ppu/frame.c and independent frame tests.
   Separate cached full-tile spans from clipped edges and raw fallback;
   strength-reduce unsigned arithmetic, prepare row invariants once, reduce
   far-pointer reloads and stack traffic. Estimate 80-180 product lines.
   Inspect original compiler output; no blind optimizer/toolchain substitution.
2. Tile metadata reuse. Shared read-only PPU owner, frame-local bounded row
   descriptors for tile/attribute/palette/base, reused across applicable source
   scanlines. Estimate 100-220 product lines and a few hundred scratch bytes;
   publish exact stack/near/far/lifetime layout before adoption. Invalidate at
   tile-row, name-table, scroll/split and source-state boundaries. Assess merging
   continuous blank spans, preserving every clipped and nonblank pixel.
3. Neutral four-plane loop. Owner src/platform/vga/vga_frame.c, existing neutral
   video contracts and independent mapping tests. Estimate 60-160 product lines;
   reduce tiny copies/pointer reconstruction within existing band storage.
   No gameplay/CHR/object interpretation in the platform layer.
4. Integrated graphics review. Compare cumulative output and actual product
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
mode cadence acceptance belong to the [remaining acceptance candidate](dos-memory-cadence-remaining-acceptance.md).
Physical 25MHz486SX/DOS-version qualification remains M4.
See [T28 retained closure](../../history/M3-T28-dos-rendering-optimization.md#s6-p24-owner-directed-closure-and-remaining-work-transfer).
