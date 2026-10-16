# NESticle forensic DOS-performance audit

## Objective

Establish, from local executable behavior and read-only historical source
inspection, which presentation mechanisms make the owner-supplied NESticle run
materially smoother than MySMB in the same DOSBox environment.  The output is
a bounded, evidence-backed opportunity matrix.  It is not a performance claim
and does not authorize importing, translating, or compiling third-party code
into MySMB.

The prior comparison established that a public historical source line uses
RAM-backed screens, dirty nametable caches, contiguous VGA publication and
32-bit assembly.  It did **not** prove that the owner executable uses the same
backend, mode, vsync policy, frameskip policy, or per-frame work model.  This
audit closes those named gaps before more MySMB micro-optimizations are chosen.

## Provenance and containment

| Input | Status | Purpose | Containment |
| --- | --- | --- | --- |
| Owner-supplied NESticle executable archive | local proprietary/freeware research input; not redistributable | Observe actual display and cadence behavior | ignored `build/` only |
| Public historical NESticle source | third-party research reference; license/distribution status must be recorded at admission | Explain symbols and compare mechanisms | read-only copy below ignored `build/` only |
| Owner-local SMB input | local research input; not redistributable | Drive equivalent game routes | existing local-only runner only |
| MySMB executable and source | project product | Produce matched work census | ordinary project build plus ignored probes |

No archive, source, generated trace, ROM bytes, screenshot containing
recoverable ROM art, binary, disassembly, or derived program data may be
tracked.  Tracked evidence may retain only neutral hashes, facts, measurements,
commands without local paths, and conclusions.

## Scope

- Build and instrument the third-party source only below ignored `build/` when
  its license and build prerequisites permit a local diagnostic build.
- Otherwise instrument the owner executable as a black box with DOS-visible
  counters and timing observations; do not patch, redistribute, or retain an
  altered executable.
- Use matching scripted title, Start transition, steady overworld, dense-sprite,
  water and castle routes when reachable.
- Measure frame production, display publication, video mode/register policy,
  memory transfer work, cache invalidation work, vertical-retrace waits and
  actual frameskip behavior.
- Repeat the same census against MySMB's accepted AB/ABC RAM-band presentation tiers after T46 S5 removes D.

## Non-goals

- No product-code change, MySMB cache policy change, DOS4GW adoption, emulator
  configuration edit, ROM logic change, shared PPU change, Win32 change, or
  third-party code/data import.
- No inference that a public source revision is byte-identical to the owner
  executable.
- No FPS comparison across unlike routes, CPU-cycle settings, resolutions, or
  presentation modes.

## Planned S tasks

### S1 — artifact and execution-path receipt

Record neutral hashes, version strings, available command-line/configuration
options, DOS memory model, selected video mode and startup route for the owner
executable.  Establish a repeatable local benchmark launch without changing
DOSBox settings.  Record whether a source build is possible only as a local
diagnostic aid; do not treat success as proof of executable identity.

### S2 — NESticle per-frame presentation census

For each reachable matched route, record logical emulation frames, published
frames, skipped frames, completed software-screen bytes, VGA bytes, cache/tile
updates, palette updates, retrace/page-handoff events and elapsed/PIT timing.
Classify frameskip from observed counters and display publication, not from a
README option alone.

### S3 — MySMB matched census

Use the same route entry/exit criteria, DOSBox cycle setting and measurement
window for MySMB.  Separate translated game tick, shared PPU preparation,
background cache work, sprite composition, RAM-screen writes, final VGA copy,
waits and skipped publication.  Retain exact PPU-output checks; no source
change is required for an audit-only result.

### S4 — mechanism matrix and next implementation gate

Compare only normalized same-route work.  For every material difference, state
whether it is: already implemented, compatible DOS16 platform work, incompatible
with the DOS16 target, unproven, or blocked by memory.  Select at most one
measurable implementation candidate with a predicted saved work unit and a
byte-exact verification plan.  Reject speculation that lacks an observable
mechanism.

## Acceptance

The audit closes only when it can answer all of the following separately for
the owner executable and MySMB on comparable routes:

1. Which video mode and publication strategy are actually used.
2. Whether and when frames are skipped, versus merely displayed late.
3. How much per-frame work is cache rebuild, sprite composition, software-screen
   writing, VGA transfer, palette update and synchronization.
4. Which differences remain after normalizing routes, cycle budget and output
   dimensions.
5. One bounded successor candidate, or an explicit evidence-based decision that
   none is justified.

The result must explicitly distinguish executable observation from public-source
interpretation, and must not claim NESticle performance parity without a matched
route receipt.
