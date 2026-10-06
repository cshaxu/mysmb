# DOS graphics performance beyond Nesticle

Owner-requested queue-head M3 T candidate. It is unnumbered and not admitted;
`states/CURRENT.md` remains the sole active packet. This candidate follows the
active T32 work. It receives no unfinished T32 S scope by implication: admission
must reconcile T32's actual closure or explicit transfer first.

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
game updates per second); current `assets/mysmb16.exe` fell from 398 to 392
(about 12 updates per second). The HUD is a game-update proxy, not a displayed
frame counter. The two executables used different guest video modes: Nesticle
256x240; MySMB 320x400 logical pixels scanned as 640x400. The comparison
establishes a real configured-playability gap, not a proven compositor-only
fivefold ratio or equal-display proof. MySMB reached near-normal update cadence
with `cycles=max` in a separate headless check, which is not acceptance.

The retained MySMB graphics diagnostic totals 712.58 ms: PPU composition
457.53 ms (64.21%) and indexed-to-VGA mapping 197.58 ms (27.73%). These are
diagnostic phase costs, not product FPS. Current DOS presentation rebuilds
256x240 indexed rows, expands to 320x400, submits four VGA planes in 25
16-row bands, and scans the sprite list once per band. Removing mapping alone
cannot plausibly close the measured gap. No claim about Nesticle's internal
renderer is made without direct evidence.

## Boundaries

- Keep original translated game logic, RAM/OAM/PPU state transitions, audio
  commands, input timing, sprite priority, masks, scroll, palette and frame
  output exact. Optimize presentation or pure composition only; no ROM-logic
  shortcut, fake timer, adaptive lost frame, or reduced drawing frequency.
- Primary product remains the DOS16 executable and the common 256x240 indexed
  video contract. A 256x240 VGA presentation may be prototyped to make the
  comparison resolution-matched, provided the current 640x400 presentation
  remains available until the owner reviews the display tradeoff. A mode or
  toolchain change is not silently charged to active T32.
- Preserve Win32 x86/x64 behavior and buildability, DOS memory/startup limits,
  2048-byte stack unless independently proved otherwise, and platform/IO/PPU
  ownership. No new ROM, third-party source, bundled DOS4GW, helper process,
  undocumented protected fixture, or committed derived image/EXE.
- This is an M3 presentation/performance candidate, not M2 certification.
  Expected ROM-node labels and control relations are `[]`; expected new node
  and control credit is zero in every proposed S. At admission, copy current
  historical/current counters and register this zero-credit responsibility in
  the node/task ledger without transferring node custody.

## Proposed S decomposition

The labels below are planning slots, not allocated identifiers. Re-estimate
source size, memory, exact files, and node counts in each admitted S packet.

1. **S1, comparable benchmark and bottleneck receipt.** Estimate 0 product
   lines and 100-250 contained probe/harness lines. Pin both EXE hashes,
   owner-local ROM identity, DOSBox version/core/settings, sound/input route,
   guest resolution, actual submitted frame counts, game updates, and
   transitions. Establish Nesticle's explicit frameskip behavior or mark the
   equal-frame comparison unproved. Measure minimum fixed cycles sustaining
   60/60 across each route; instrument MySMB game, PPU, mapping, VGA submission,
   and wait separately. Keep captures/traces below ignored `build/`, delete raw
   protected images after bounded analysis. Decision: a reproducible phase
   budget and fair comparator before accepting a speed claim.
2. **S2, dominant PPU composition.** Estimate 80-240 candidate product lines,
   subject to S1 findings, in `src/ppu/` and focused tests. Investigate
   reusable background tile/row work, scroll and dirty-region updates,
   band-invariant sprite classification and opacity lookup. Existing decoded
   CHR caching is baseline, not a new gain. Each candidate must beat the
   original DOS compiler's generated cost without unacceptable near/far,
   stack, or resident-memory growth. Verify exact indexed frames and state on
   title, split/status, scrolling, palette, sprite priority, dense, and
   fallback routes; reject a cache if its invalidation cannot be proved.
3. **S3, DOS display path.** Estimate 60-180 candidate product lines in
   `src/platform/dos16/`, VGA presentation and their IO adapter, plus focused
   tests. Compare existing 320x400 plane packing and a resolution-matched
   256x240 VGA route with exact palette/indexed pixels. Count VRAM bytes,
   plane selects, port writes, band calls, conversion time, mode behavior and
   peak memory. Preserve the existing mode pending owner display review;
   choose a product default only with an explicit, measurable presentation
   decision. Do not attribute removed scaling cost to a PPU speedup.
4. **S4, integrated 16-bit cost reduction.** Estimate 40-160 candidate product
   lines only where S1-S3 profiles still show a material deficit. Inspect
   original DOS compiler listings, far-pointer and call traffic, and render
   buffer lifetimes. Compare bounded loop/data-layout variants under the
   original toolchain and memory limits. A 32-bit DOS port or toolchain change
   requires its own explicit scope decision; it is not a substitute for
   meeting the DOS16 target. Keep any demonstrably beneficial candidate only
   after exact-output and three-product verification.
5. **S5, fair acceptance and closure.** Estimate 0-150 contained harness lines,
   no product changes unless a failing candidate returns to its owning S.
   Rebuild/refresh DOS16, Win32 x86 and x64 after adopted product changes.
   Run the pinned repeated workload matrix, count game updates and actual
   display submissions, compare representative exact output and user-visible
   pacing, find both minimum sustained-60/60 cycle thresholds, and report
   confidence intervals, peak startup/resident/stack evidence and all rejected
   approaches. Verify real DOSBox play with input and scene changes. The
   owner may review a resolution/display default separately. Do not close as
   "faster than Nesticle" unless the measured equal-frame threshold is lower.

## Admission and evidence gates

Planning may use the retained local benchmark summary. New ROM or third-party
research requires the active packet's provenance, license/redistributability,
purpose, containment and verification record under the source policy.
Benchmark captures and binaries remain ignored and local. Each implementation
S names exact components, estimated and actual changed lines, memory budget,
zero node-label scope, analogous defect sweep, focused byte/output cases and
three-product delivery. T closure reconciles T32's transfer, exact source and
product identities, meaningful per-phase savings, equal-frame comparator,
actual DOS playability, and any still-open 486SX qualification (M4).
