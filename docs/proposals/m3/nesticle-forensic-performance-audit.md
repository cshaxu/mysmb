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

- Except the owner-approved S2 option/pacing change, no product-code change; no MySMB cache policy change, DOS4GW adoption, emulator
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

### S2 — owner-requested DOS turbo option

Implement the explicit owner amendment below: normal DOS tick/presentation
synchronization, with legacy skipping/catch-up only under --turbo.

### S3 — NESticle per-frame presentation census

For each reachable matched route, record logical emulation frames, published
frames, skipped frames, completed software-screen bytes, VGA bytes, cache/tile
updates, palette updates, retrace/page-handoff events and elapsed/PIT timing.
Classify frameskip from observed counters and display publication, not from a
README option alone.

### S4 — MySMB matched census

Use the same route entry/exit criteria, DOSBox cycle setting and measurement
window for MySMB.  Separate translated game tick, shared PPU preparation,
background cache work, sprite composition, RAM-band writes, band VGA copies,
waits and skipped publication.  Retain exact PPU-output checks; no source
change is required for an audit-only result.

### S5 — mechanism matrix and next implementation gate

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
| S3 | Observe NESticle under unchanged DOSBox settings on reachable bounded routes | Publication/cadence/retrace/frameskip and memory-transfer census; unknown counters explicitly unknown, no inferred totals |
| S4 | Match current AB/ABC MySMB route and dimensions to S2; reuse applicable T46 proof | Per-stage/tick/publication work and directly comparable costs, with exclusions and any fixture mismatch |
| S5 | Reconcile differences and decide the next implementation | Ranked compatible mechanisms with saved-work units/memory cost; select at most one bounded successor or state no justified candidate |

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

## S1 P3 — agent-measured original0.2 fixed3000 cadence

Owner corrects P2's handoff: the agent must collect elapsed time/counters and
report milliseconds itself, not ask the owner to read FPS. This P completes
that bounded automated measurement. It does not close the whole mechanism
census or claim MySMB parity. No product/third-party executable was patched,
compiled, rebuilt or imported for this measurement.

### Method and counter binding

Use the qualified original0.2 binary and bundled DOS4GW. The session override
is fixed3000cycles; core stays auto, resolution256x224, no-sound, GUI hidden,
no ShowFPS overlay. The default configuration hash remains the P1 hash.
There is no max launch, resident guest probe or emulator device change.

A host observer reads only its own DOSBox process. It locates exactly one
historical anesprofile layout using the200tick update duration, million-cycle
divisor and neighbouring1/1/10/10/10divisors, then samples named counter values
against host perf_counter monotonic time. The reference owners are PROF.H,
MAIN.CPP updatescreen's frame increment and CPU.CPP tickemu's virtual-frame
increment. These are specific counter-layout bindings, not a claim that the
entire source tree is byte-identical to this executable.

Each run obtains101samples at roughly200ms spacing over20seconds, after warmup.
The observer does not freeze the guest or write its memory. Counters remain
monotonic; every adjacent cycle/virtual-frame delta in all707samples has the
same26500cycles-per-virtual-frame ratio. The signature match is unique in each
process. Where independently collected, exactly one original NES RAM image
matches the emulator reset sentinels. Its game frame byte tracks the virtual
counter with at most one frame of phase uncertainty due to asynchronous
sampling and the NMI boundary. Mode/task reads independently classify the
measured scene. No whole RAM/process image is stored or committed.

Three title runs and three steady-gameplay runs are the qualified scene rows;
one additional Start-transition run is retained separately. The agent sends
Enter make/break messages only to its owned DOSBox window, with no foreground
input injection. The subsequent RAM mode/task change confirms Start worked.
After the life-screen transition, wait twelve seconds before the steady sample.
Every steady sample has mode1/task3; verified title runs have mode0/task3.

### Actual counter deltas and wall-clock intervals

| Scene/run | Host seconds | Display-loop delta | Virtual-frame delta | Display loops/s | Virtual frames/s | Mean display interval ms | Mean virtual interval ms |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| Title1 |20.046060|117|377|5.837|18.807|171.334|53.173|
| Title2 |20.055086|117|377|5.834|18.798|171.411|53.197|
| Title3 |20.054832|118|378|5.884|18.848|169.956|53.055|
| Steady gameplay1 |20.055810|104|389|5.186|19.396|192.844|51.557|
| Steady gameplay2 |20.052229|104|389|5.186|19.399|192.810|51.548|
| Steady gameplay, visible window |20.056507|104|389|5.185|19.395|192.851|51.559|
| Start transition, excluded from steady result |20.053479|108|391|5.386|19.498|185.680|51.288|

Title runs use SDL dummy host video. Steady gameplay1/2 use the Windows SDL
backend with the host window hidden after startup; the last steady run leaves
its actual window visible for all101samples. This final control produces the
same104/389deltas. Its foreground-only intervals cover10.830seconds with55
display loops/211virtual frames; background-only intervals cover9.026seconds
with48/175, excluding the focus-transition interval. No materially different
cadence emerges from that finite visibility/focus check. All process instances
are stopped by their creating observer after collection; none is left running.

The mean interval is1000*host_elapsed/counter_delta. It is end-to-end cadence,
including work between updates, not exclusive drawing-function CPU time.
The display-loop counter is incremented before its publication completes;
endpoint phase can therefore differ from completed VGA publications by at
most one loop under the reference path. Do not call this a hardware scanout
measurement, a measured VSync policy, or an exact internal frameskip setting.
Report rounded practical results, approximately170-171ms/title display loop
and193ms/steady-game display loop, rather than implying microsecond accuracy.

### Why directly reading the on-screen FPS would be wrong here

The profiler's own rate fields eventually report virtual60.0 and display
about15.9-18.6, while host-time counter deltas are approximately19.4virtual
frames/s and5.19steady display loops/s. Historical PROF.CPP computes rates
from the configured200tick duration/TIMERSPEED and uutimer follows game-timer
advancement; it does not use the observer's wall clock. Those internal rate
fields are therefore not accepted as wall-time FPS. This is precisely why
the observer reads cumulative increments and an independent monotonic clock,
instead of asking the owner to convert the displayed number into milliseconds.

### Conclusion and limits

Original0.2 is also slow at fixed3000in this measured route: approximately
5.2steady display updates/s and19.4NES virtual frames/s. There are roughly
3.74virtual frames per display loop; this establishes different work cadence,
not a user-selected skip setting or a reason to suppress core ticks in MySMB.
It does not prove that MySMB is faster, equivalent or qualified: the retained
MySMB24-27ms number is a rendering-kernel receipt, not the same end-to-end
counter/time measurement. Nor does it measure the later x.xx binary at fixed
3000, full-game playability, audio-on behavior, or actual25MHz486hardware.
The finite original0.2 result must not be substituted for any of those claims.

Review/verification: seven bounded runs,707samples, unique profiler signatures,
cycle-delta checks, independent RAM phase/mode checks where collected,
visible-window control and unchanged configuration pass. The transition row
is explicitly excluded from steady results. No unit/integration/product
suite rebuild is applicable to this private research-only observer. Existing
three Mario EXEs are unchanged. Historical1992/1992,retained1991/1992nodes,
4260/4261feasible controls(raw4342,infeasible81) unchanged; no ROM credit.
S1 remains open for actual video-path binding; the automatic fixed3000 timing
question is now measured rather than delegated to owner testing.

## S1 P4 — unchanged MySMB peer result and bounded S1 closure

Owner requests a same-clock comparison and then explicitly requests a DOS
command-line turbo option: normal execution must publish every game tick;
only mysmb16 --turbo may retain catch-up/skipping. Preserve the measured old
product baseline before that change. S1 closes its artifact/path and finite
cadence question here; detailed VGA transfer/retrace costs remain explicitly
assigned to the still-unadmitted mechanism census, not marked verified.

The original DOS compiler supplies metadata-only sizeof/offsetof constants;
no product was patched/rebuilt. A read-only observer finds exactly one live
root through original warm-boot state, matching CHR/workspace pointers/sizes,
initialized flags and compiler-derived offsets, and one pair of pacing clocks
with periods19886/119318PIT ticks. Core frame_number counts game ticks;
publication.last changes when the existing gate admits a presentation. That
is an admitted-start count, not a hardware scanout completion counter. The
root's original CPU frame byte tracks the core counter with one frame of NMI
phase uncertainty. Native output remains256x240, versus NESticle's256x224.

Both runs use fixed3000, default core=auto, Windows SDL host video and visible
windows. The game's BLASTER environment value is unset only in its private DOS
shell, disabling optional physical PCM through its existing capability path,
matching NESticle's no-sound test without changing emulated SB hardware.
Observed audio_available=0; A/B/C all allocated. The default configuration and
accepted EXE SHA256 remain unchanged. No additional cache or resident probe.

The first20second window observed1464ticks/187admitted displays, but is
**excluded from steady comparisons**: publication clock versus tick deadline
showed roughly9.8seconds initial startup debt, reducing to5.4seconds. Its
73.2ticks/s is catch-up, not steady game speed or evidence of a faulty PIT.
Publication clock elapsed tracks wall time within about0.3percent in this
window. Wait for debt to settle and a three-second recent57-63tick/s rate
before starting the qualified20second window.

| Settled run | Seconds | Game ticks | Admitted displays | Tick/s | Display/s | Tick interval ms | Display interval ms |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| MySMB1 |19.997834|1199|282|59.956|14.102|16.679|70.914|
| MySMB2 |19.999137|1198|282|59.903|14.101|16.694|70.919|

Both complete windows retain mode1/task3. Warmup required about38.3/50.0seconds
beyond the initial startup/Start delay. No owner testing was needed. The first
window has8098polls, maximum10.8ms gap and at most one tick between polls;
its observed publication-stamp increments are66.0-84.0ms. The second tighter
polling window has maximum6.1ms gap and at most one tick between polls.
Publication deltas are observed continuously, not inferred from changing art.
As with NESticle's pre-copy loop counter, an endpoint can differ by one in-flight
publication; use rounded cadence results rather than sub-millisecond claims.

Finite native-mode comparison: MySMB approximately60logic ticks/s and14.1
admitted images/s, NESticle0.2 approximately19.4virtual frames/s and5.19display
loops/s. MySMB updates about2.72times as frequently in this route, while doing
240rather than224output rows. This supports a limited product-cadence advantage,
not a pixel-normalized renderer ratio, x.xx comparison,50/60display FPS,
whole-game/audio-on guarantee or25MHz486qualification. Both still have skipped
intermediate visible states; original per-tick logic proof receives zero credit.

Source audit confirms the UX mechanism: DOS root always ticks then optionally
presents; the wait routine marks lateness and the gate suppresses intermediate
renders. Rendering is synchronous, not a separate producer thread. Owner's
new preference supersedes the old always-skip policy. No implementation in S1.

S1 review: identity/startup/cadence evidence complete within this bounded scope;
actual transfer work/VSync/mode-register binding still missing and retained for
later census. Historical1992/1992,retained1991/1992nodes and4260/4261feasible
controls unchanged. Expected/actual node sets empty, no transfers of ROM nodes.
Three products unchanged. Close S1 and admit the owner-prioritized S2 below;
shift only the unadmitted old S2-S4 census slots to S3-S5.

## S2 admission — DOS normal and --turbo presentation policy

Owner explicitly requires mysmb16 --turbo to enable the previous skip/catch-up
behavior; without the flag, one original tick must complete one presentation,
and slow output must not accumulate hidden catch-up debt. Scope is DOS
application option parsing/assembly and shared pacing arithmetic plus generic
DOS command-tail access. No ROM core/PPU/art/cache change, no new thread or
emulator setting. Win32/Win16 behavior remains unchanged in this DOS CLI S;
all three Mario product artifacts still refresh for the implementation P.

Expected size:8-14production/build files,100-180production lines plus focused
owner tests. Generic command-tail mechanics belong to lib/dos16; --turbo means
something only in app-mario. Shared C90 pacing helper retains/rebases debt
according to its declared caller parameter. Startup command buffer is bounded
and transient; one policy flag, no new resident image cache.

Checks: exact/unknown/empty/whitespace option ownership; bounded DOS tail copies;
normal late/on-time/wrap/reset and turbo legacy pacing; native x86/x64 suites;
original optimized DOS compile/link and preserved native NE payload; automatic
actual-EXE default and --turbo joins, one tick per admitted frame in normal,
legacy suppression/catch-up in turbo, Enter/Tab/exit and cache/audio state;
three current local products. No repeat NESticle or cache factorial matrix.

Incoming historical1992/1992; scope=[],expectedMatches=[],maximum1992/1992.
The S remains implementation-only zero-credit infrastructure. App mode changes
are not an original-ROM equivalence claim. Evidence/output under ignored
build/t47-s2; bounded180seconds/run and16MiB raw counter budget, no max tests.
Implementation outcome and all actual changed branches must be reviewed before
closure. S3 retains original NESticle detailed census, S4 matched work census,
S5 normalized mechanism/next-candidate decision; none is concurrently admitted.


## S2 P1 implementation and closure

Owner syntax is `mysmb16 --turbo`. Default has no option and publishes after
every completed game tick, in DOS graphics and authored text alike. Late
normal frames rebase their next logical deadline instead of accumulating
catch-up debt. On-time frames still wait for the nominal tick deadline.
Turbo opts into the previous logical catch-up and bounded video suppression.
The logical ROM tick itself, original execution order and audio-command
production are unchanged; slow normal mode intentionally slows game time.

Ownership: lib/dos16 copies the current PSP command tail with explicit bounds;
it has no option names. Mario app/runtime_options owns exact-token parsing,
whitespace, idempotent repetition and unknown-argument rejection. The DOS root
selects the policy before opening devices. A transient128-byte startup buffer
expires before the loop. App IO owns the pure C90 finish-frame arithmetic;
DOS clock/sleep binds it and keeps one policy byte. Existing Win32/Win16
pacing functions and their bindings are unchanged. No core/PPU/art/cache diff,
new thread or emulator persistent change.

### Test-owner and similar-issue closure

- lib/dos16 command-line unit owns null output, zero capacity, absent tail,
  empty input, exact capacity, insufficient capacity, maximum126-byte tail
  and malformed length. Physical PSP retrieval is covered by actual DOS
  empty/valid/invalid command joins, not a duplicate host mock.
- Mario options unit owns null/empty/whitespace input, --turbo, repetition,
  unknown tokens/prefixes/case and excessive token length. Unknown arguments
  return DOS code2 and print usage before any graphics/device initialization.
- IO pacing unit owns normal on-time/overdue and turbo debt, period guards,
  32-bit wrap and BIOS reset. Actual product counter joins cover default
  always-publish versus turbo suppression and title-to-game startup debt.
- Search of product-main callers found the cache-allocation diagnostic as
  the sole numeric-tail consumer. It now consumes its own numeric option
  before invoking product main; production does not accept diagnostic digits.
  The original compiler/linker rebuilt this diagnostic and actual DOS mode0
  reports result0, observed1, A/B/C1, live0, errors0. This is an entry/cleanup
  check, not a repeat performance factorial matrix.
- Shared host link consumers were searched; the Mine DOS build adds only
  the neutral tail-copy member needed by host.c. No Mine game/input policy
  changes. Native Mine tests pass in both complete suites.
- Pause/load/resume retain their original clock resets; normal publication
  bypasses the gate regardless of stale present_due, while turbo keeps the
  original clock formula. Text and graphics share the same root gate.

Ninja/ccache Release builds pass both widths. CTest passes318/318 x86 and
318/318 x64. Named private-desktop host integration passes15routes per width,
including delivered game startup, owned/borrowed console lifecycle, Tab,
snapshots, focus and interactive CMD prompt restoration. Initial sandbox
CreateDesktop error5 is resolved by running the same isolated target with the
existing host permission; no user desktop input is injected.

Original optimized DOS build passes in the qualified short build output
path: the old compiler returns4 with a deeply nested CMake temporary path.
The short-path retry uses the same source/flags/runtime/linker and succeeds.
No alternate compiler, emulator settings or product behavior bypass. There
are216segments, largest32768bytes, DGROUP53648bytes including2048stack;
minimum loaded bytes388544, maximum392640 including4096near reserve,
excluding PSP/dynamic allocations. Both loaded bounds grow1600bytes versus
S1; no new persistent cache. The command buffer is startup-stack scratch.

The unchanged accepted Win16 payload is rebound to the new DOS image rather
than falsely claiming a fresh Win16 source build. Eight segment byte ranges
and the full NE tail, after normalization of nine absolute file addresses,
match the accepted payload exactly; there are no resources. Its payload hash
is c29dae2fa85eec9ee8e4321117003fa7cc613e4b43eeb3bd53d7b7aa2c0f462e.
DOS relocations move within existing header padding to leave e_lfanew free;
all2694relocation entries, loaded bytes and CS/IP/SS/SP remain identical to
the freshly linked DOS stub. bind_win16_mz verifies resident bounds and the
new NE offset365568. No new Win3.x runtime qualification is claimed.

### Actual product policy joins

Read-only host polling uses the same compiled root offsets and publication
clock as S1. Each fixed3000 run binds one root/clock signature, verifies the
actual executable hash and no physical audio, and confirms A/B/C enabled.
No max run or third-party rerun. Counters count admissions to the synchronous
presenter, not physical scanout or renderer-only CPU time.

| Route | Window seconds | Logic ticks | Images admitted | Tick/s | Images/s |
| --- | ---: | ---: | ---: | ---: | ---: |
| Default steady graphics |19.999119|573|573|28.651|28.651|
| --turbo after startup debt settles |19.998978|1199|280|59.953|14.001|
| Default graphics lifecycle check |1.998632|57|57|28.520|28.520|

Every graphics sample remains mode1/task3; polling observes at most one tick
between samples. Default text additionally advances8ticks and8publication
stamps over a four-second join, then Tab returns to graphics. Both policies
pass Enter start, Tab text/graphics and Esc exit. The first normal run's probe
asserted a key-up against an already exited window; corrected lifecycle
checking accepts successful process exit on Esc key-down and passes. This
was not a product hang or patch. Invalid --turbo=1 exits2; DOSBox exits0.
The initial invalid-option batch lacked its own exit and incorrectly treated
empty redirected files as failed conditions; corrected batch checking passes.
Persistent DOSBox configuration hash stays unchanged throughout.

### Local artifacts and review

All three products are repackaged below assets/mario; local-only and ignored:

| Artifact | Bytes | SHA256 |
| --- | ---: | --- |
| mysmb16.exe |699349|360daa8448394326d5ec5b804678e1d6a407289539ff870a9954149bfaec3891|
| mysmb32.exe |427659|7cbc8b25929dd4cf2a00e420764a4235e66984f5e2891a8a83ba1a95f9e9ff12|
| mysmb64.exe |391275|bad201751b9ca7f2c2a029c7a4b945720a6ddd1a93758edfcb712ecb2d43c8b5|

Actual implementation size:14production/build files,118added/16removed lines;
four owner test files,70added/1removed lines. Five governance/UX records are
updated separately; the ledger adds the explicit empty-scope S2 run.

Single-person executor/coordinator review confirms the owner switch/default,
no core/PPU/platform-Windows source changes, bounded parsing, normal debt
rebase, equivalent turbo branch, test owners, diagnostic-tail ownership,
unchanged native NE payload and fresh three artifacts. The ledger semantic
comparison retains all unrelated nodes/events/runs/tasks. S2 closes for owner
acceptance; T47 remains open. Detailed NESticle transfer/retrace census S3,
matched MySMB work census S4 and mechanism decision S5 remain unadmitted.
Scope/expected/actual[],new0,transfers0. Historical1992/1992; retained exact
1991/1992nodes and4260/4261feasible controls(raw4342,infeasible81), unchanged.
These local counts are not a final whole-game equivalence certificate.


## S2 P2 owner-directed four-product packaging admission

Before owner acceptance, reopen this same S for the requested delivery split:
mysmb16c.exe is the original linked pure DOS MZ, mysmb16w.exe is the accepted
MZ/NE hybrid; mysmb32.exe/mysmb64.exe retain their names. Packaging must take
both16-bit inputs explicitly and reject a hybrid in the pure-DOS slot or a
non-NE Windows16 input; verify their DOS loaded bytes/relocations/entry/loader
bounds match with the existing binder. The old mysmb16.exe delivery alias is
retired after successful packaging. Scope: packaging tool, app-owned packaging
test/registration, current delivery rules and product-path documentation.
No game/host runtime source or third-party input change; reuse qualified S2 P1
builds. Original ROM inputs/products remain local-only under source policy.
Estimated under100tool lines plus contract test; temp artifacts build/t47-s2.
Scope/expected/actual[],historical1992/1992; no changed node/edge credit.
Single-person executor/coordinator accepts this owner-authorized packaging
addendum, not an admission of the reserved S3 performance research.


## S2 P2 four-product packaging closure

Delivery now requires two explicit16-bit inputs. The packager accepts pure DOS
MZ only in Dos16Executable and native NE hybrid only in Win16Executable. It
then invokes the existing binder to verify identical DOS loaded bytes,
relocations, entry/stack and resident bounds. PE widths and owner-local
resource build receipts remain required. Four products are copied only after
validation; successful packaging removes the retired mysmb16.exe alias.
The default output directory is assets/mario. Internal compiler/link output
names remain private build artifacts, not extra published aliases.

Changed owners: tools/Package-MySMB, one Windows-only app product-packaging
CTest registered by the app CMake owner, current delivery rules, source-layout
and UX documentation. No runtime C source changes. The project-owned synthetic
header test covers two successful packages (with/without the retired alias)
and ten rejected joins: NE/PE in pure DOS, MZ in Win16, wrong PE architecture,
missing input, mismatched DOS payload, short MZ/NE headers, missing Ninja
resource binding and missing CMake resource binding. It uses no ROM or copied
program bytes. The existing binder unit owns its arithmetic; this test owns
only packaging joins and output identities. All generated test files stay
below build; package/readme products below assets remain ignored/local.

Ninja/ccache builds pass, with unchanged C objects. Complete native CTest now
passes319/319 per width, including the new package contract. P1's15private-host
joins per width and default/turbo runtime evidence remain applicable because
all runtime inputs are byte-unchanged. The final local package verifies all
2694DOS relocation entries and resident bounds. Four current products:

| Artifact | Kind | Bytes | SHA256 |
| --- | --- | ---: | --- |
| mysmb16c.exe |pure DOS MZ|365339|c806c1b047e00350d702852673edfabe43a7b11f99ed3890e3b4cba8d16b14c3|
| mysmb16w.exe |DOS/Win16 NE hybrid|699349|360daa8448394326d5ec5b804678e1d6a407289539ff870a9954149bfaec3891|
| mysmb32.exe |Win32 x86|427659|7cbc8b25929dd4cf2a00e420764a4235e66984f5e2891a8a83ba1a95f9e9ff12|
| mysmb64.exe |Win32 x64|391275|bad201751b9ca7f2c2a029c7a4b945720a6ddd1a93758edfcb712ecb2d43c8b5|

The16c bytes are exactly the freshly qualified S2 P1 standalone DOS link;16w
is exactly the qualified S2 P1 hybrid. Both PE outputs are also unchanged.
An actual DOS16c launch checks the full8-character executable name and same
root/clock/cache signatures, Enter start, default per-tick publication,
Tab text/graphics and Esc exit. The original ten-second title assumption
observed DOSBox before guest launch; a bounded wait for the owned product
window replaces that harness assumption, not a game-code change.

Single-person executor/coordinator review covers four-file identity, explicit
MZ versus NE validation, no runtime diff, old alias retirement and caller
sweep (no other active Package-MySMB caller). Historical proposals and build
intermediate names are preserved as history, not rewritten into new evidence.
Current rule applies to subsequent Mario implementation deliveries; Mine keeps
its separate product boundary. S2 closes for owner acceptance; T47 remains
open, S3-S5 not admitted. Zero new ROM scope/matches/transfers; historical
1992/1992, retained1991/1992nodes and4260/4261feasible controls remain unchanged.
