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
background cache work, sprite composition, RAM-band writes, band VGA copies,
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

## Preparation after accepted T46

This is the next queue candidate after owner acceptance of T46 on2026-10-16.
It was unnumbered at preparation; owner admission below now allocates M3 T47. T46 removed D; the current product is
AB-required/C-optional RAM-band composition/publication, not the older retained
or full-screen presenter. S1 confirms the exact local input identities and
existing evidence before any new executable/source observation.

Reuse [T46 evidence](../../history/M3-T46-dos16-ram-presenter-memory-tiers.md):
seven current allocation/lifetime joins, accepted source-pixel equivalence,
S4 complete historical ranking and S5 removal/space account. Current ABC
finite diagnostic route measured24.285ms calibrated/26.914ms raw rendering;
AB59.026ms. These exclude logical tick/audio/waits and are not product FPS.
ABC cache130KiB, AB70KiB; known conventional-memory arithmetic subtotals are
541.105KiB/481.105KiB plus allocator/environment/rounding overhead. The20ms
objective remains unmet. Do not repeat the cache factorial matrix, reopen
accepted ROM chains or restore D merely to compare a different work model.

| Planned S | Entry and responsibility | Reviewable output |
| --- | --- | --- |
| S1 | Check owner executable/archive and historical-source identities, prior receipts, legal/build boundaries, actual launch/video options | Input/path manifest with executable observations separated from source interpretations; list only the evidence still missing |
| S2 | Observe NESticle under unchanged DOSBox settings on reachable bounded routes | Publication/cadence/retrace/frameskip and memory-transfer census; unknown counters explicitly unknown, no inferred totals |
| S3 | Match current AB/ABC MySMB route and dimensions to S2; reuse applicable T46 proof | Per-stage/tick/publication work and directly comparable costs, with exclusions and any fixture mismatch |
| S4 | Reconcile differences and decide the next implementation | Ranked compatible mechanisms with saved-work units/memory cost; select at most one bounded successor or state no justified candidate |

Start with reproducible title/steady-overworld routes; water/castle/dense
scenes require explicit reachable entry/exit and comparable observations,
not an assumed counterpart. Do not call incomparable routes a matched result.
The admitted packet fixes actual input hashes, fixture boundaries, budgets,
no-progress limit and evidence applicability. A missing instrumentation counter
is a named gap, never an invented measurement. There is no new code/source
import, source compilation or probe execution in this preparation pass.

## M3 T47 S1 admission — 2026-10-16

Owner approves admission and execution of the queue-head mechanism audit.
Coordinator/executor is one agent in two explicitly reviewed roles. T47 is the
next ascending M3 identifier after accepted T46; only S1 is active. S2-S4
retain the responsibilities above and are not concurrent admissions.

S1 scope: identify the supplied archive, executable, extender, historical
source revision, prior source-build receipts, command options and reproducible
launch path. Separate observed executable properties, documented options and
source-only deductions. Do not repeat T46's factorial cache benchmarks.
Expected changes: CURRENT, QUEUE, this proposal and generated task ledger;
approximately100-180 neutral documentation lines, zero product/test/ABI lines.

Local third-party source is conceptual research, with no redistribution license
assumed. It remains unmodified/local-only unless a qualified diagnostic build
is explicitly recorded. Owner executable is freeware with a no-modification
notice; observe it unchanged. Existing owner approval for private historical
source diagnostics does not authorize product import or distribution.
Owner archive and DOS extender are staged from existing local asset copies;
ROM is read only for the existing local research launch, never tracked.
Public reference is the athros/NESticle repository; record commit and actual
notices before interpreting its source. All staged material, output and logs
stay in ignored build/t47-s1. No E-drive writes or emulator setting changes.

Bound:64MiB raw/output budget excluding a single source checkout up to64MiB;
180seconds per launch,30seconds without observable progress, at most two failed
attempts for one unchanged route before reporting the missing capability.
S1 exit is an identity/path manifest and executable/source evidence boundary,
not a claim of frame-cost coverage. Source toolchain recovery is not a new
project; reuse qualified receipts or record the precise missing dependency.

Historical incoming1992/1992; scope=[],expectedMatches=[],actualMatches=[],
maximum1992/1992. Retained local nodes1991/1992, feasible controls4260/4261
(raw4342,infeasible81), no whole-game certificate; no ROM credit requested.
Focused checks: artifact hash/header/option manifest, unchanged DOSBox config
hash, source provenance/receipt binding, node admission and documentation gate.
ROM-route baseline is accepted T37 title/Start/steady-overworld launch; only
routes with observable entry/exit can advance to S2 measurements.

## S1 P1 findings — identities and unequal automatic CPU budgets

This is an interim research P, not S1 or T47 closure. Actual VGA mode and
publication counters remain unproved. No product or test source changed;
all three accepted local Mario products remain byte-identical.

### Input binding

| Input | Measured identity | Disposition |
| --- | --- | --- |
| Owner ZIP |195802bytes;SHA256 `00f5b3fa3a8ba3e23d86d8feae36ec3684b43495aa62b63864e816b022c8fb47` | Two existing local archive copies match; no new E-drive access/write. |
| Owner NESticle EXE |400571bytes;SHA256 `224e348e1fd5c11b16ef096ff5607c7c57c49d65fa7e4dbbc9b2a5c9c53e832b` | Both retained executable copies match. Staged copy unchanged after observation. |
| Supplied DOS4GW |265396bytes;SHA256 `b8265123ac8a189637448618409ef3ecd2e9f3e1a47062c685a02240f688dec1` | Existing co-located owner runtime, not a new replacement. |
| Supplied README |15497bytes;SHA256 `080c9116f0c24871e2217f74ff9845265ad56b32a5645e65c159b0dfbc76f2d6` | Identifies x.xx and freeware/no modification/no ROM distribution conditions; no source redistribution grant assumed. |
| Historical source |athros/NESticle revision `7ede7dab54bc0cef85774b424025a7d6b8133d28` | Same revision as prior T39 research; LICENSE is a copyright notice, no permissive license assumed. Local reference only. |
| Existing DOSBox configuration |SHA256 `0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917` | Unchanged before/after every launch. CPU core and cycles both auto. |

The NESticle MZ points at an LE header at file offset11408. Its executable
object has flags0x2045 and a32-bit default-size flag; the second object has
flags0x2043. These are binary format observations, not a claim that every
instruction is32-bit or that bitness explains a timing ratio.

### Executable options actually read

An unchanged executable help invocation completed and returned to a DOS batch
DONE marker. It lists resolution, VSync, frameskip, virtual FPS, no-sound,
VESA/banked/linear selection and optional RDTSC/FPU-copy controls. The default
resolution printed by this executable is256x224. No RDTSC or FPU-copy option
was enabled. README documents frameskip1-8/AUTO; the presence of a parameter
or requesting1 is not evidence of observed published/skipped-frame counts.

Reproduction inside a private mounted working directory:

```text
NESTICLE.EXE -h > HELP.TXT
NESTICLE.EXE -res 256 240 -nosound -vsync OFF -frameskip 1 -run D:\SMB1.NES
```

D is the read-only-used owner-input directory; executable/save/output working
files are private build outputs. Commands change game options only; no DOSBox
CPU/memory/machine setting is overridden. The second command reached a live
NESTICLE process in the startup observation; this alone does not certify
successful ROM title pixels, selected VGA registers or entry into gameplay.
The no-sound reference differs from MySMB's ordinary audio path, so these
launches are startup observations, not fair whole-product benchmarks.

### New executable observation: automatic budget switching

A process-owned window-title observer sampled at50ms intervals for at most
eight seconds per launch. It sent no keyboard/mouse event. This observer was
outside the guest and installed no resident DOS probe. Both processes were
stopped by their creating observer after the bounded sample; no unrelated
process was killed.

| Executable | Before executable startup | During executable execution | Approximate observed transition |
| --- | --- | --- | --- |
| NESticle plus supplied DOS4GW |3000cycles,Program DOSBOX |max100%cycles,Program NESTICLE |1.874seconds after host process creation |
| Current MySMB DOS product |3000cycles,Program DOSBOX |3000cycles,Program MYSMB |1.884seconds after host process creation |

These timestamps describe host startup observation, not per-frame costs.
The NESticle DOSBox log independently reports the automatic switch to max.
The installed0.74-3 manual, performance section, explains automatic real-mode
and protected-mode budgets; the official [CPU configuration reference](https://www.dosbox.com/wiki/Configuration:CPU)
likewise describes3000real-mode/default versus max protected-mode behavior,
and the automatic normal/dynamic core selection. The title/log prove the
budget switch here; they do not directly observe the selected execution core.

Therefore the current default-config visual comparison is **not an equal
CPU-budget comparison**. A3000cycle label seen before the protected-mode
program starts does not bind its later runtime. This does not quantify how
much of the performance difference is budget versus render architecture,
and does not establish that default switching occurred in every historical
user launch. Prior T46 within-MySMB real-mode/cache comparisons retain their
stated finite rendering-only applicability. Historical explicitly fixed-cycle
receipts are separate and are not rewritten as automatic-mode results.
No emulator setting was changed to improve either result. A subsequent
same-work census can compare work units under this unchanged configuration;
wall-time cross-program ratios cannot be called equal-budget results.

### Historical-source binding and applicability

The [pinned historical source](https://github.com/athros/NESticle/tree/7ede7dab54bc0cef85774b424025a7d6b8133d28)
front end explicitly identifies0.2. Its command parser has a waitvsync switch,
while the actual x.xx executable exposes vsync ON/OFF and additional options.
The nested NESSRC ZIP supplies an older DOS backend; it does not establish
that its body is the backend linked into the owner executable.

Rechecked mechanism facts remain source-only: dirty nametable surfaces,
clipped surface blits, descending64-sprite traversal, and completed RAM-screen
publication. Nested DOS/DOS.CPP:163-185 has separate conventional, banked and
linear publication paths; the conventional branch uses a fixed64000-byte copy.
Its mode fallback at445-469 recognizes320x200 and256x224, not the owner's
requested256x240. These mismatches make a freshly rebuilt0.2 diagnostic an
unsuitable stand-in for the exact x.xx executable without further binding.

The historical project makefile references an absent private make fragment.
No qualified source-built x.xx executable receipt was found in the retained
research record. T39 recorded the same missing build prerequisites and source
identity gap. No speculative toolchain recovery or source compilation was
performed here; existing source mechanism conclusions are reused with their
original version limit, not presented as newly measured x.xx counters.

### Bounded observer attempt and remaining S1 work

A private project-owned5675-byte DOS16 resident observer was compiled/linked
with the established local compiler/CRT. Its timer callback samples BIOS,
sequencer and CRTC state without DOS file calls or framebuffer writes, then
chains the predecessor. It reserves64KiB solely for this diagnostic, so it
could not be used as a product-memory or speed benchmark. Its corresponding
host observer only reads its owned DOSBox process and stops that process.

Two bounded collection attempts returned no valid resident-marker record for
either program. The scans did not prove guest marker placement, timer-hook
execution, selected mode, or register contents. No zero-filled record was
accepted as an observation. The read budget stayed below64MiB per process;
no process-memory dump or ROM-derived trace was saved. This failed technique
is stopped; it is not a reason to rerun the cache matrix or rebuild MySMB.

S1 remains open for a valid execution-path/video-mode receipt or an explicitly
reviewed scope amendment. S2-S4 are still planned, not admitted. Actual guest
resolution/layout, default/manual skip behavior, per-frame RAM/VGA transfers,
retrace/page handoff and matched-route costs remain unverified. The owner
executable's smoothness and a historical source reconstruction do not fill
those missing measurements.

Single-person coordinator review: input/version distinctions and failed
observation limits are explicit; no import, product change, ROM credit,
performance-parity claim or emulator setting drift. Documentation/admission
gates apply; no unit/integration/product rebuild is required for this
research-only P. Scope/expected/actual remain empty, historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls(raw4342,infeasible81).

## S1 P2 — owner-requested original0.2 at fixed3000

Owner explicitly permits this temporary fixed-cycle session after the max
MySMB launch proved unusable in their test and they reported a host restart.
No further max test is authorized by this amendment. Persistent DOSBox config
remains unchanged; only a private secondary configuration sets fixed3000.

Retrieved the historical distribution from [Internet Archive item nestc020](https://archive.org/details/nestc020).
The archive is381553bytes,SHA256
`a3f3f6f87ce44e8ed2029297e71b1a46bcf035fd1916aa4015ea7426e55fa8a2`;
its downloaded SHA1 matches the archive catalog. The original bundled README
identifies Version0.2(4/2/97), with unchanged freeware/no-ROM distribution
terms. Local reference only, no tracked executable, archive, GUI art or palette.
It contains no game ROM. The unmodified DOS executable is342115bytes,SHA256
`c41c36e3bb422ac33f5312a41392282009d61f2ce49f50e621b5eb597af29c98`.
Bundled DOS4GW matches the prior owner runtime. This is the original release,
not a newly compiled source tree or proof of source/binary byte identity.

Launch requests native256x224, no-sound, hidden emulator GUI, ShowFPS and the
existing owner Mario ROM. Default core/video/memory settings are retained;
no frameskip/VSync override unavailable in this version is invented. The
process remains live seven seconds after startup, with DOSBox title showing
3000cycles,Frameskip0,Program NESTICLE. A secondary startup observer confirms
fixed3000 remains selected after protected-mode entry rather than switching
to max. The title's Frameskip0 describes DOSBox, not an independently measured
internal NESticle publication rate. User now has the interactive window.
No input was injected; no subjective gameplay/FPS result is fabricated.

The README's Enter/Tab are Start/Select; Space disables GUI/maximizes the NES
viewport, and Escape toggles emulator menus. Other mappings remain the release
defaults and can be inspected in its Settings/RedefineInput UI.

This establishes a fixed3000 historical release launch, not an equal-output
240-row performance ratio or a25MHz486qualification. S1 remains open for the
remaining actual video/publication receipt. Scope and ROM counts unchanged;
no product build/test change or EXE refresh. All inputs and records are under
the active ignored research workspace, below the16MiB amendment budget.
