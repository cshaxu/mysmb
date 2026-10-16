# M3 T46: DOS16 RAM presenter memory-tier qualification

## Objective

Qualify the accepted DOS16 RAM-composition presenter on real allocation tiers
without changing the translated game, shared PPU decisions, or final pixels.
The product policy is fixed: D/A/B must exist for graphical presentation, and
C is optional.

| Tier | Storage | Bytes | Policy |
| --- | --- | ---: | --- |
| D | Final 256-by-240 RAM screen | 61,440 | required |
| A | Decoded CHR cache | 8,192 | required |
| B | Packed two-nametable background | 63,488 | required |
| C | Byte-background upgrade | 61,440 | optional |

The derived presentation allocation is 133,120bytes (130 KiB) for ABD and194,560bytes (190 KiB)
for ABCD.  The candidate must report actual DOS allocation receipts instead of
claiming a universal conventional-memory threshold from estimates.

## Scope

- `src/app-mario/kvm/platform/dos16` owns cache assembly and measurement;
  `src/lib/dos16` supplies neutral DOS allocation/video/timing mechanisms.
- Mirrored fixtures under `test/app-mario/kvm/platform/dos16`; generated
  probes, listings, ROM-derived products and logs remain under ignored build.
- Existing exact PPU byte oracle, actual DOS16 link, and ignored DOSBox probes.
- The same warmed graphical route with pacing waits excluded from cost figures.

## Non-goals

- No core, ROM, shared PPU, input, audio, Win32, text, DOS4GW, emulator
  configuration, or extra full-frame cache.
- No changed allocation policy or hidden compact-presenter fallback.

## Planned S tasks

### S1 — runtime allocation receipt

Record whether D, A, B and C were actually retained across the admitted DOS16
launch configurations.  Verify that a missing required D/A/B follows the clean
exit path and that C failure retains the ABD presenter.

### S2 — matched memory-tier route comparison

Measure the same warmed title and gameplay route under all12valid cache profiles, excluding
pacing waits and recording logical ticks, submitted frames, pixels and bytes.
Report whether the measured benefit justifies its additional61,440bytes.
Keep C optional under the accepted policy; any policy change requires a
separate explicit owner decision.

## Acceptance

All measured profiles must produce byte-identical final PPU output, link and launch through the
existing DOS16 route, and preserve the owner-approved D/A/B-required rule.
The resulting receipt states measured cost, allocation outcome and the chosen
C policy; it does not make a NESticle-parity claim.

## Admission and bounded execution

Owner selects queue position3 on2026-10-16. Allocate M3 T46 after the highest
existing M3 T45; this is a new task, not a continuation of closed T19.
Baseline4b962237, clean workspace. S1 is admitted; S2 is planned, not active.
Remove only this candidate from QUEUE; other candidates preserve order.

S1 first reads the actual root allocation path and records D/A/B/C pointer
retention, near/far provenance, requested bytes, failed stage, cleanup and
DOS free/largest-block readings. Current source requests D first, A via near
then far allocation, B after A, and C only after D/A/B. Missing required
storage requests clean exit; no compact fallback is accepted. This static
reading is not a runtime pass. The preflight fit test and real allocation
must both be observed; a fit estimate does not prove retained storage.

Use the original tools/dos16 compiler/linker, optimized existing build profile,
and unchanged DOSBox configuration. Test-only bounded allocation denial may
force D/A/B/C failure, but must be labelled fault injection, not a measured
natural memory tier. Distinguish loader minimum/reserve, dynamic live bytes,
conventional free memory and fragmentation. Do not publish a universal DOS
startup threshold from EXE size or injected cases.

S1 acceptance matrix: natural launch allocation receipt; denied D; denied A
including near and far attempts; denied B; denied C retaining ABD; successful
ABCD when naturally available; cleanup/no leaked owned blocks for each case.
Expected changes:3-6test/tool files,150-300lines; no production policy change.
An actual production defect requires a visible scope amendment before repair.

S2 compares title and a fixed gameplay input route after identical warmup:
logical ticks, composed/submitted frames, exact final pixel bytes, composed
bytes, composition/output CPU cost excluding waits, and total elapsed time
including waits reported separately. ABD vs ABCD must use the same compiler,
DOSBox cycles/device settings, input/audio/pacing and renderer; no NESticle
performance-parity claim. Record repeat count and spread, not only one mean.

ROM scope[], expectedMatches[], actualMatches[] for this task: no translated
logic modification or new certification credit. Historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls(4342raw,81infeasible)
remain unchanged. Owner-local ROM supplies build input only; no ROM bytes,
third-party code or generated products enter commits. Separate exact-pixel
operational proof from unperformed original-ROM logic certification.

Each S reports its bounded result before the next is admitted. Product changes
refresh the required local executables; test/governance-only commits do not
replace accepted products with diagnostic builds. Performance work does not
reopen unrelated game audit or Mine functionality.

## S1 runtime checkpoint

The optimized original DOS product builds185objects and links216segments.
Its MZ/map receipt reports388496minimum and392592maximum loaded image bytes,
including a4096-byte near reserve; it excludes the PSP and all dynamic heaps.
The diagnostic probe links217segments and reports395152minimum/399248maximum
loaded bytes. Its measured live PSP block is399920bytes. These are separate
figures: the diagnostic is larger and is not an exact production live census.

Actual DOSBox uses the unmodified owner configuration (svga_s3, core=auto,
cycles=auto, SB16/220/7/1); only mounting/commands are supplemented. SDL dummy
host drivers avoid desktop/audio interference without changing emulated devices.

| Case | Retained D/A/B/C | Root exit before diagnostic request | Owned live blocks after shutdown |
| --- | --- | --- | --- |
| Natural |1/1/1/1|0|0|
| Denied D allocation |0/1/1/0|1|0|
| Denied both A allocators |1/0/0/0|1|0|
| Denied B allocation |1/1/0/0|1|0|
| Denied C allocation |1/1/1/0|0|0|
| Denied near A only |1/1/1/1, far A retained|0|0|
| Denied D preflight |0/1/1/0|1|0|
| Denied B preflight |1/1/0/0|1|0|
| Denied C preflight |1/1/1/0|0|0|
| Natural64KiB DOS resident pressure |1/1/1/0, no denial|0|0|

The pressure helper frees its copied environment and keeps65536bytes including
PSP plus a16-byte DOS MCB; measured initial free memory drops249056to183504.
Normal largest-block preflights are219264(D),149568(B),86048(C). With pressure,
they become153712,84016,20496; C is naturally skipped because20496<61440.
Near A cannot fit in this4096-reserve profile, so real successful A uses the
far heap. Do not describe this as successful near-A allocation coverage.

Root-owned peak requested bytes are220140(ABCD) and158700(ABD):194560or133120
cache bytes plus25580runtime/text/snapshot workspace. Allocation headers,
alignment, device DMA and CRT pools are additional. Normal diagnostic MCB free
bytes before/during/after root shutdown are249056/24640/28736; pressured ABD
is183504/20560/24656. Root free operations leave no live tracked pointers,
but the CRT may retain free pools until DOS process exit; the after-shutdown
MCB value is not proof of a leak or of complete return to DOS while still live.
No universal real-machine conventional-memory threshold or timing is claimed.

The initial probe incorrectly converted a null near pointer to a far pointer,
creating a phantom DS:0000 allocation receipt. The probe now checks near null
before conversion; the complete corrected matrix passes. A separate DOSBox
batch issue created empty failure files before evaluating redirection; the
runner now uses a conditional branch before file creation. Neither defect was
in production code. The deep CMake probe path also exposed the old compiler's
temporary-name length limit; the existing short build/tmp16 convention is used.

The named non-default mysmb_dos16_cache_integration target contains the same
compile/link/runtime/receipt commands. Its initial deep-temp compile failed;
the corrected command sequence passes. The original loader receipt contract
passes7neutral MZ/map cases and10loader-bound cases plus idempotence. Receipt
parser unit checks pass3tests including six contradiction variants. Native
full regression is still running at this checkpoint; no result is inferred.

All test/probe source is project-authored; no third-party code import. The DOS
COM pressure helper is generated from its documented17-byte instruction stream
under ignored build, not installed on the host. No production behavior or
asset publication changes. Actual harness scope is larger than the initial
estimate because real MCB census, preflight/far/near failures, pressure and
reproducible host-target integration are all needed for the admitted matrix.
S2 still owns pixels and matched performance; S1 adds no ROM-node credit.

## Owner S2 factorial amendment

Owner clarifies that independent marginal benefit and interactions are the
objective, not only ABD versus ABCD. With C requiring B, valid masks (A=1,B=2,
C=4,D=8) are0,1,2,3,6,7,8,9,10,11,14,15:12profiles, not16independent profiles.

| Added cache | Fixed context | Marginal pairs |
| --- | --- | ---: |
| A | B/C=00,10,11; each with D=0or1 |6|
| B | C=0; each A/D combination |4|
| C | B=1; each A/D combination |4|
| D | A=0or1; B/C=00,10,11 |6|

The20pairs are computed from matched measurements of those12profiles. Report
per-frame composition/preparation, physical publish and total CPU cost, spread
and signed saved milliseconds, including zero/negative benefit; marginal
memory cost and milliseconds saved per KiB are descriptive, not new policy.
Repeat the same warmed title and active-gameplay source-input route, with exact
final pixels and original RAM outputs checked across profiles. Timing excludes
pacing/file-dump waits; elapsed run time is separately labelled. Calibration
must state whether video is forced for every measured logical frame; it must
not describe a controlled kernel cost as natural gameplay FPS.

Some diagnostic profiles intentionally lack production-required A/B/D. Use a
separate bounded test composition with existing unchanged public game/PPU/
DOS device APIs, not a permissive production-root fallback or a changed product
allocation policy. D denotes full-screen RAM composition/publication; D=0 uses
the equivalent bounded row/band output. Report this enabled-path difference
rather than pretending D is a passive unused buffer. Bind the existing shared
nibble/slot accelerators identically for all applicable profiles.

### S1 P2 closure and review

S1 runtime and ownership matrix is closed after9natural/injected cases plus
one natural64KiB pressure case. Corrected named host target passes end to end;
its first missing Get-FileHash PowerShell-module failure is resolved with a
bounded .NET SHA256 call. Configuration hash is stable before/after every run.
Native default suite315/315 plus newly registered receipt CTest1/1 pass after
final configuration; parser has3unit methods/six contradictory evidence cases.
Existing memory receipt17cases plus idempotence pass. No product C or device
logic changed; no diagnostic replaces an accepted local EXE. Original DOS
product build and217segment probe qualify16-bit ABI; x86 product code is
unchanged and no fresh x86 suite is claimed for this test-only work.

Single-person executor/coordinator reviewed old probe failures, bounded COM
memory pressure, actual near/far/frees, request/MCB/loader distinctions, source
policy and all diffs. Exact expected/actual node sets[]; no transfers or credit.
S2 has not yet run. Its expanded20pair objective is owner-approved above.

### S2 admission

Coordinator admits S2 from9701a9d1 under the owner's start and factorial
instructions. Diagnostic-only composition calls the unchanged public native
core and PPU APIs; it can bind B without A and D without A/B, independently
of production root admission. It uses the same game startup and source inputs,
standard audio submission and device open/close. Rendering only the matched
warmup/sample frames is an explicit benchmark schedule, not a gameplay frame
skip policy. D=0 uses4096-byte bounded rows; D=1 uses existing RAM compositor
and complete-screen publication. Output comparison reads the completed VGA
surface plus palette and original RAM, outside timed kernels. Three repeats,
eight measured title and eight gameplay frames per run; raw protected stream
budget48MiB, per-run180second budget. Report clock calibration and both raw
and adjusted costs because row-path timestamps have more boundaries. No extra
full-screen measurement cache or production change. S1 generated evidence is
retained for pending task acceptance; S2 runtime outputs stay separately scoped.

## S2 P1 closure and coordinator review

All12valid masks completed three repeats:36successful launches,16measured
frames per launch,576compared frame records (16distinct route positions),
and1152submitted frames including warmup. All final61440VGA slot pixels,
32active palette entries and2048original RAM bytes match byte-for-byte across
all profiles/repeats. All runs end at logical tick309. Protected streams total
36587520bytes, within48MiB. No emulator CPU/memory/device setting changed;
configuration SHA256 remains
0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917.

The independent diagnostic main uses the same original optimized product
objects. It links217segments, largest32768bytes, DGROUP53968bytes; diagnostic
MZ bounds are397664minimum/401760maximum including4096near reserve. These are
not production live-memory numbers. No product C implementation or publication
changed. Accepted local executables remain unchanged; no diagnostic replaces
any Mario or Mine artifact. No additional x86 execution is claimed.

Each phase reports the median of three repeat means, each mean covering eight
warmed frames. PIT frequency1193182Hz; minimum of32clock pairs calibrates
98-99ticks per boundary. D=0 uses32timed kernels per frame (frame preparation,
palette and15compose/publish pairs); D=1 uses4. Thus calibration removes up to
2.655ms versus0.332ms. Repeat means have no observed spread under this
deterministic emulation clock; this is not real-hardware statistical certainty.
Raw and corrected margins are retained. No per-frame
logical game/audio tick, startup, file dump or pacing wait is included in the
rendering costs. Approximate batch-launch-to-DONE filesystem intervals are
reported separately; these are not stopwatch samples or gameplay FPS.

The strongest measured production-policy comparison is ABD to ABCD:
C costs60KiB and saves19.895ms/gameplay render (61.265to41.370ms), about32.5%.
A with BD saves1.731ms for8KiB; B with AD saves186.764ms for62KiB. Benefits are
context-dependent and cannot be added from unrelated baselines. Without B,
A saves about286.6ms/gameplay render; with B/C it saves only about1.7to1.9ms.

D compares complete output algorithms, not merely buffer allocation. With
none/A/B/AB, corrected D costs about2.1to2.4ms but raw differences are near zero:
those small margins are inconclusive because clock-boundary counts differ.
With BC or ABC, the existing row path is about17ms faster than the D-enabled
compositor even before choosing a production policy. This identifies a future
full-compositor/byte-row integration opportunity; it does not qualify removal
of required D or the retained-VGA production fallback. Static source follow-up
locates the boundary: ppu/frame.c groups background rows across the fixed HUD
and scroll spans; platform/dos16/slot_copy.c rejects groups over16rows. The
D-enabled compositor requests240rows at once, so groups over16are rejected
and fall back to the exact slower row loop. The16-row diagnostic path stays
within the accelerator contract. Splitting that full-frame request into
bounded groups is a concrete future candidate, not a measured product fix in
this task. No source or binary patch was made to obtain these numbers.
ABD-required/C-optional
remains unchanged. This task measures finite title/early-game routes, not all
areas, natural frame cadence, actual25MHz hardware or NESticle parity.

The named non-default mysmb_dos16_cache_matrix_integration target contains
compile, link and runtime commands. This qualification ran the same commands
manually with bounded build-local paths, rather than claiming an invocation
of that complete named target. Full current native suite317/317 passes; the
factorial arithmetic/receipt owner has4unit methods, including six malformed
receipt variants. Exact-output integration owns the real game/PPU/device join;
S1 retains actual allocator/failure/cleanup ownership. No duplicate production
assertion or new production branch was introduced. Postprocessing verifies
all12profiles, three paired repeats, all20pairs and timing/raw-stream receipts
before declaring completion.

Single-person executor/coordinator review checked the fixed20pair universe,
cache dependency, requested allocation failures, matched input/warmup,
original optimized bindings, band/full-path distinction, timing boundaries,
raw/calibrated sensitivity, resource containment, test ownership and source
policy. The code/build-tool diff is diagnostic-only. Both S tasks and T46 are
closed for owner acceptance. Generated S1/S2 evidence remains only until that
acceptance, then is removed under the cleanup rule. Other queued candidates
retain their order; no next T is admitted automatically.

ROM scope/expected/actual[],completed0,deferred0,transferred0. Historical
1992/1992,retained1991/1992nodes and4260/4261feasible controls(raw4342,
infeasible81) unchanged. No current-build whole-game certificate is issued.

## S2 measured matrix

Controlled warmed rendering costs, milliseconds per frame; not gameplay FPS.
PIT boundary overhead is calibrated. File I/O, startup and pacing are excluded.

| Profile | Cache KiB | Title total ms | Gameplay total ms |
| --- | ---: | ---: | ---: |
| none | 0 | 532.094 | 532.345 |
| A | 8 | 300.766 | 245.680 |
| B | 62 | 74.932 | 60.944 |
| AB | 70 | 73.162 | 59.026 |
| BC | 122 | 25.778 | 26.042 |
| ABC | 130 | 23.976 | 24.265 |
| D | 60 | 534.222 | 534.622 |
| AD | 68 | 302.988 | 248.029 |
| BD | 122 | 76.894 | 62.996 |
| ABD | 130 | 75.171 | 61.265 |
| BCD | 182 | 42.587 | 43.064 |
| ABCD | 190 | 40.965 | 41.370 |

Positive savings mean faster; negative savings mean slower.

| Added | Context | Added KiB | Title saved ms | Gameplay saved ms | Gameplay ms/KiB |
| --- | --- | ---: | ---: | ---: | ---: |
| A | none | 8 | +231.328 | +286.665 | +35.8331 |
| A | B | 8 | +1.770 | +1.918 | +0.2398 |
| A | BC | 8 | +1.802 | +1.777 | +0.2222 |
| A | D | 8 | +231.234 | +286.593 | +35.8242 |
| A | BD | 8 | +1.723 | +1.731 | +0.2164 |
| A | BCD | 8 | +1.622 | +1.695 | +0.2118 |
| B | none | 62 | +457.162 | +471.401 | +7.6032 |
| B | A | 62 | +227.604 | +186.654 | +3.0105 |
| B | D | 62 | +457.329 | +471.626 | +7.6069 |
| B | AD | 62 | +227.817 | +186.764 | +3.0123 |
| C | B | 60 | +49.155 | +34.902 | +0.5817 |
| C | AB | 60 | +49.186 | +34.761 | +0.5794 |
| C | BD | 60 | +34.307 | +19.932 | +0.3322 |
| C | ABD | 60 | +34.206 | +19.895 | +0.3316 |
| D | none | 60 | -2.128 | -2.278 | -0.0380 |
| D | A | 60 | -2.223 | -2.349 | -0.0392 |
| D | B | 60 | -1.962 | -2.052 | -0.0342 |
| D | AB | 60 | -2.009 | -2.239 | -0.0373 |
| D | BC | 60 | -16.809 | -17.022 | -0.2837 |
| D | ABC | 60 | -16.989 | -17.105 | -0.2851 |

## Phase costs and repeat spread

Three repeats; each phase is the mean of eight measured frames. Ranges below are repeat means.

| Profile | Phase | Prepare ms | Compose ms | Publish ms | Total range ms | Raw total ms |
| --- | --- | ---: | ---: | ---: | --- | ---: |
| none | title | 0.218 | 525.392 | 6.484 | 532.094 to 532.094 | 534.749 |
| none | gameplay | 0.218 | 525.641 | 6.486 | 532.345 to 532.345 | 535.000 |
| A | title | 0.222 | 294.059 | 6.485 | 300.766 to 300.766 | 303.421 |
| A | gameplay | 0.222 | 238.972 | 6.486 | 245.680 to 245.680 | 248.335 |
| B | title | 0.481 | 67.966 | 6.485 | 74.932 to 74.932 | 77.587 |
| B | gameplay | 0.570 | 53.889 | 6.485 | 60.944 to 60.944 | 63.599 |
| AB | title | 0.472 | 66.205 | 6.484 | 73.162 to 73.162 | 75.817 |
| AB | gameplay | 0.481 | 52.058 | 6.487 | 59.026 to 59.026 | 61.681 |
| BC | title | 0.542 | 18.750 | 6.486 | 25.778 to 25.778 | 28.433 |
| BC | gameplay | 0.551 | 19.005 | 6.487 | 26.042 to 26.042 | 28.697 |
| ABC | title | 0.474 | 17.003 | 6.498 | 23.976 to 23.976 | 26.604 |
| ABC | gameplay | 0.575 | 17.192 | 6.498 | 24.265 to 24.265 | 26.893 |
| D | title | 0.218 | 528.569 | 5.435 | 534.222 to 534.222 | 534.554 |
| D | gameplay | 0.218 | 528.970 | 5.435 | 534.622 to 534.622 | 534.954 |
| AD | title | 0.222 | 297.332 | 5.434 | 302.988 to 302.988 | 303.320 |
| AD | gameplay | 0.222 | 242.372 | 5.435 | 248.029 to 248.029 | 248.361 |
| BD | title | 0.534 | 70.926 | 5.434 | 76.894 to 76.894 | 77.226 |
| BD | gameplay | 0.570 | 56.991 | 5.435 | 62.996 to 62.996 | 63.328 |
| ABD | title | 0.476 | 69.259 | 5.435 | 75.171 to 75.171 | 75.503 |
| ABD | gameplay | 0.588 | 55.242 | 5.435 | 61.265 to 61.265 | 61.597 |
| BCD | title | 0.448 | 36.703 | 5.436 | 42.587 to 42.587 | 42.915 |
| BCD | gameplay | 0.524 | 37.104 | 5.436 | 43.064 to 43.064 | 43.393 |
| ABCD | title | 0.497 | 35.034 | 5.434 | 40.965 to 40.965 | 41.297 |
| ABCD | gameplay | 0.587 | 35.349 | 5.434 | 41.370 to 41.370 | 41.702 |

## Paired timing sensitivity

D changes the complete composition/publication path. Its margins are not passive-buffer costs.
Band output has more PIT boundaries. Small raw/calibrated sign changes are inconclusive.

| Added | Context | Phase | Saved range ms | Raw saved ms |
| --- | --- | --- | --- | ---: |
| A | none | title | +231.328 to +231.328 | +231.328 |
| A | none | gameplay | +286.665 to +286.665 | +286.665 |
| A | B | title | +1.770 to +1.770 | +1.770 |
| A | B | gameplay | +1.918 to +1.918 | +1.918 |
| A | BC | title | +1.802 to +1.802 | +1.828 |
| A | BC | gameplay | +1.777 to +1.777 | +1.804 |
| A | D | title | +231.234 to +231.234 | +231.234 |
| A | D | gameplay | +286.593 to +286.593 | +286.593 |
| A | BD | title | +1.723 to +1.723 | +1.723 |
| A | BD | gameplay | +1.731 to +1.731 | +1.731 |
| A | BCD | title | +1.622 to +1.622 | +1.618 |
| A | BCD | gameplay | +1.695 to +1.695 | +1.691 |
| B | none | title | +457.162 to +457.162 | +457.162 |
| B | none | gameplay | +471.401 to +471.401 | +471.401 |
| B | A | title | +227.604 to +227.604 | +227.604 |
| B | A | gameplay | +186.654 to +186.654 | +186.654 |
| B | D | title | +457.329 to +457.329 | +457.329 |
| B | D | gameplay | +471.626 to +471.626 | +471.626 |
| B | AD | title | +227.817 to +227.817 | +227.817 |
| B | AD | gameplay | +186.764 to +186.764 | +186.764 |
| C | B | title | +49.155 to +49.155 | +49.155 |
| C | B | gameplay | +34.902 to +34.902 | +34.902 |
| C | AB | title | +49.186 to +49.186 | +49.213 |
| C | AB | gameplay | +34.761 to +34.761 | +34.788 |
| C | BD | title | +34.307 to +34.307 | +34.311 |
| C | BD | gameplay | +19.932 to +19.932 | +19.935 |
| C | ABD | title | +34.206 to +34.206 | +34.206 |
| C | ABD | gameplay | +19.895 to +19.895 | +19.895 |
| D | none | title | -2.128 to -2.128 | +0.195 |
| D | none | gameplay | -2.278 to -2.278 | +0.046 |
| D | A | title | -2.223 to -2.223 | +0.101 |
| D | A | gameplay | -2.349 to -2.349 | -0.026 |
| D | B | title | -1.962 to -1.962 | +0.362 |
| D | B | gameplay | -2.052 to -2.052 | +0.271 |
| D | AB | title | -2.009 to -2.009 | +0.314 |
| D | AB | gameplay | -2.239 to -2.239 | +0.084 |
| D | BC | title | -16.809 to -16.809 | -14.482 |
| D | BC | gameplay | -17.022 to -17.022 | -14.696 |
| D | ABC | title | -16.989 to -16.989 | -14.692 |
| D | ABC | gameplay | -17.105 to -17.105 | -14.809 |

Approximate batch-launch-to-DONE intervals: 17.484 to 32.737 seconds.
These are filesystem timestamp intervals, not stopwatch samples or per-frame costs.
They include startup, game/audio work, warmup and file output; no pacing wait was requested.

## Owner-directed reopening: S3 full-span copy repair

Owner explicitly reopens T46 and admits S3, continuing the measured bottleneck
rather than allocating a new T. S1/S2 acceptance remains retained. The mistaken
uncommitted new-task admission is withdrawn; no subsequent T is allocated.
Baseline736020ea. Existing compile/measurement jobs belong to this S3 and are
retained as active-task generated work; no completed task's stale trees remain.

### S3 scope and exit

The sole product owner is app-mario/kvm/platform/dos16/slot_copy. The unchanged
shared PPU can submit up to240rows, split by HUD/scroll/wrap. Its DOS callback
rejects rows over16 although its DWORD count can fit240*64=15360in16bits.
Qualify complete spans and permit valid full-height requests. Preserve neutral
slot values, source/destination bounds, source immutability and the C ABI's
callee-preserved registers.
Reject invalid counts including16-bit count-sum overflow; no new allocation.
Search all callback binds and alternate row-limit checks for the same defect.
No game/core, PPU pixel decision, policy, memory tier, emulator setting, frame
cadence or third-party import changes. Source is project-authored; owner ROM
is local-only comparison/build input, never committed or distributed.

Use one owner-local actual-DOS neutral copy probe: contiguous/split widths,
odd tails,1/16/17/32/208/240rows, sentinel boundaries and rejected parameters.
First show the old callback fails the larger cases. Then prove success with
the actual DOS assembly. Existing native exact-compositor tests own PPU/OAM
joins; do not replace their owner contracts with another implementation.

Compare old/new optimized diagnostic executables for ABC/ABD/ABCD, three
repeats, identical8warm+8measured title/gameplay phases. Retain raw/calibrated
phase costs and byte-identical VGA/palette/original RAM. Streams below ignored
the active ignored build workspace only,48MiB total,180seconds per run; owner config read unchanged.
Keep only current-task build inputs from accepted T46, delete its stale trees.
The fixed fixture is not actual486hardware or end-to-end FPS.20ms is the user
objective, not a promised outcome of this one repair; record the remaining gap.

Run configured native unit/integration suites, original optimized DOS compile/
link, actual copy/runtime comparisons, dependency purity, node/document gates.
Refresh the three local Mario EXEs, preserving the MZ+NE hybrid; no binaries
or protected generated data enter Git. Report loader+root caches/workspace,
DMA,PSP and unmeasured allocator/environment overhead separately. Do not add
loader reserve twice or describe a probe's live PSP as production usage.

Estimated product change1file/under10lines; fixture/build integration roughly
4-6files/200-300lines. S3 closes when valid spans are accepted with exact bytes,
invalid inputs fail safely, before/after timing improves reproducibly without
new cache allocation, all relevant tests pass and local products are current.
Single-person executor/coordinator reviews the complete diff before closure.
ROM scope/expected/actual[],historical1992/1992,retained1991/1992nodes and
4260/4261feasible controls(raw4342,infeasible81) unchanged; no new certification.

## S3 P1 closure: full-height acceleration and space account

Owner-directed T46 reopening and S3 admission supersede the mistaken
uncommitted new-task allocation. No new T was allocated. Coordinator closes S3
and T46 for owner acceptance after the following repair/verification; S1/S2
accepted evidence remains retained within its original scope.

The only product change is DOS slot_copy.c and its header contract. Valid
1..240row PPU-selected spans now use the existing DWORD loop;240*64=15360fits
its16-bit count. Widths over256are rejected individually before adding, avoiding
16-bit sum wrap. No ROM/game/shared-PPU decisions, source values, output order,
cache binding/policy or emulator setting changed. No new allocation. Existing
loop/register code is unchanged; the real large-model assembly is exercised.

Similar-issue sweep: every slot_rows_copy bind is either the DOS root/current
diagnostic or a neutral PPU fixture. The shared PPU already permits240rows and
splits at HUD/scroll/wrap boundaries. The remaining two devices.c limits of16
belong to bounded4096-byte band/pixel I/O, not this full-screen RAM transfer;
they remain correct and unchanged. Frame/planar bounds already permit the
appropriate full240-row/source geometry. No second erroneous callback cap found.

The old optimized object rejects the first17-row case after passing1/16rows.
The fixed actual-DOS fixture passes36height/split combinations, nine invalid
arguments and optional unused second source. Synthetic sources are immutable;
destination guard/tail bytes stay intact. Tests cover heights1,16,17,32,208,240
and widths0,1,3,128,255,256. This is the single owner for new guard/copy decisions;
existing native compositor fixtures continue to own PPU/OAM joins. Initially
naming the diagnostic COPY.EXE collided with DOSBox's internal COPY command;
renaming it SPAN.EXE resolves that harness issue. The old/fixed receipts were
rerun successfully; no application workaround was needed.

Matched ABC/ABD/ABCD routes each run three times before/after:18launches,
288compared records (16distinct positions),18293760protected bytes. All final
VGA slots, palette and original RAM match byte-for-byte;309logical ticks per
run. Same original optimized core/PPU objects and unchanged owner DOSBox config.
Raw files stay ignored under the active task's build workspace, below48MiB and
180seconds per-run. No third-party source or raw/generated data enters Git.

| Profile | Title before ms | Title after ms | Gameplay before ms | Gameplay after ms | Gameplay saved ms |
| --- | ---: | ---: | ---: | ---: | ---: |
| ABC | 23.976 | 23.988 | 24.265 | 24.285 | -0.021 |
| ABD | 75.171 | 75.171 | 61.265 | 61.265 | +0.000 |
| ABCD | 40.965 | 25.318 | 41.370 | 25.746 | +15.624 |

Three repeat means have no observed spread in this deterministic emulation
profile; no real-hardware statistical certainty is inferred. The ABC control
has about0.021ms extra gameplay cost from the two width checks; ABD is unchanged
because the C-dependent callback is not used. ABCD saves15.624ms/about37.8%.
The additional C60KiB now saves35.519ms versus ABD in this route, rather than
the old19.895ms. Do not add marginal savings from unrelated contexts.

| ABCD gameplay phase | Before ms | After ms | Saved ms |
| --- | ---: | ---: | ---: |
| prepare | 0.587 | 0.588 | -0.001 |
| compose | 35.349 | 19.724 | +15.625 |
| publish | 5.434 | 5.434 | -0.000 |
| raw_total | 41.702 | 26.078 | +15.624 |

Clock methodology and timestamp sensitivity remain as S2. These are warmed
rendering kernels, excluding logical game/audio ticks, startup, file dumping
and waits; they are not playable FPS. The25.746ms result still misses20ms by
5.746ms before logical tick/audio cost. That broader performance objective is
not closed by this bounded repair. Residual cost is mostly composition, then
physical publication; no further optimization or new S was silently admitted.
Existing queued performance work retains its original order.

### S3 DOS conventional memory

All numbers below describe RAM, not the699349-byte hybrid EXE file. The native
Win16 NE payload is byte-identical to the accepted product; the DOS loader does
not load that appended Windows payload. The repaired optimized DOS product
links216segments, largest32768bytes, DGROUP53632bytes, stack2048bytes. Its
MZ loader minimum388512/maximum392608bytes includes the4096near reserve and
excludes PSP/dynamic memory. The patch adds16loader bytes, no resident cache.

| Category | Bytes | KiB | Basis |
| --- | ---: | ---: | --- |
| A decoded CHR |8192|8| unchanged requested block |
| B packed background/snapshot |63488|62| unchanged requested block |
| C byte-background upgrade |61440|60| unchanged optional block |
| D final RAM screen |61440|60| unchanged required block |
| ABCD subtotal |194560|190| no additional surface |
| Root text/runtime/save workspace |25580|24.980| retained S1 live-allocation receipt, unchanged owner |
| Loaded code/static data/stack/near reserve |392608|383.406| new MZ/map receipt |
| Audio DMA when available |4096|4| lib/dos16/pcm_dos.c,256paragraphs |
| PSP |256|0.250| DOS process block |
| Known arithmetic subtotal |617100|602.637| before heap/MCB/environment overhead |

Page-rounding allowance adds up to272bytes in this image (loader bound392880),
so that conservative subtotal is602.902KiB. Heap/MCB headers/alignment, process
environment and optional CRT retention are additional. A useful planning figure
is around603KiB plus environment/allocator headroom, not a universal exact live
PSP census or startup threshold. Without C, the known subtotal drops exactly
60KiB to542.637KiB before the same overhead. ABD-required/C-optional remains
unchanged; fragmentation and driver-resident memory can still prevent allocation.
No new production live-MCB measurement is claimed from a larger diagnostic.

### S3 operational review and local products

Original DOS build185objects compiles/links with existing toolchain and Safe
render flags. Actual copy fixture and matched output/timing checks pass. Full
x86 and x64 native suites each pass317/317, including Mine/library regressions.
Both named Win32 host-integration targets pass15launch/input/Tab/close routes
on private desktops, including interactive CMD. The first sandboxed private-
desktop attempt failed with access-denied; the authorized qualified host run
passes on each width. No app defect was inferred from that host-capability error.

Win16+MZ links and bind_win16_mz verifies DOS code/relocations/CS/IP/SS/SP and
resident allocation preservation. The appended NE payload is byte-for-byte
identical to the accepted local EXE; no new Win3.x gameplay run is claimed.
Package-MySMB validates ROM-bound Ninja configurations and PE machine types,
then publishes all three local assets/mario products. No local EXE, ROM or
protected output is committed. Mine products are unchanged.

The named mysmb_dos16_slot_copy_integration target records the same original-
object compile/link/host commands; this task invokes its equivalent commands
manually against old and new optimized objects. The test build tool's SlotCopy
entry links only the neutral fixture/object/CRT; no game resources are needed.
Existing Benchmark/allocation modes retain their separate composition paths.

Single-person executor/coordinator reviews product scope, neutral fixture,
count/segment bounds, unchanged loop ABI, absence of allocations, exact frames,
phase timing, memory categories, local artifacts, original-toolchain/source
policy and governance. S3 product delta is two small DOS source/header changes;
remaining changes are test/tool/host-target integration and task evidence.
Generated active-task work is removed after owner acceptance.

Scope/expected/actual[],new0,deferred0,transferred0. Historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls(raw4342,infeasible81)
unchanged. No whole-game current-build certificate is issued.

## S4 owner-requested current-build ranking

Owner asks every valid cache combination ordered by speed and memory value.
Admit continuation T46 S4 (audit/evidence only) from1e5e3163 to avoid mixing
S2 pre-repair numbers with S3's three-profile correction. Product/test/tool
source and accepted executables remain unchanged. Existing fixed diagnostic,
unchanged configuration,12profiles and three repeats,16measured frames/run,
48MiB raw-output budget and180seconds/run. Protected output below ignored
build/t46-s4; no third-party import or redistribution. Retain S3 current-build
inputs until pending owner acceptance; delete all task evidence on acceptance.

Publish calibrated and raw costs, ordering uncertainty from different timer
boundaries, cache KiB, relative speed and diminishing benefit. Do not describe
synthetic D=0 output as a qualified production fallback or assume ABCD fastest.
No policy change, new resident allocation, code repair or ROM conformance credit.
Exit: same-current-build full12profile/20pair receipts, byte-identical output,
ranked report, scope/expected/actual[],gate/review/commit. No product rebuild is
needed for an evidence-only P. Historical1992/1992,retained1991/1992nodes and
4260/4261feasible controls(raw4342,infeasible81) unchanged.

## S4 P1 closure: ranked current-build cache results

All12valid profiles run three times using the fixed S3 executable, not a mix
of S2 pre-repair and S3 post-repair values.36launches/576frame records match
byte-for-byte across active palette, original RAM and final VGA slots. There
are16distinct source positions per repeat; this is finite route evidence,
not all-input proof. All20marginal pairs are complete; protected stream bytes
36587520remain below48MiB. Every run completes309logical ticks, within180seconds.
Owner configuration hash remains
0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917.
Original optimized diagnostic/product bindings, slot accelerators, audio and
scripted input remain unchanged. No production/test/tool source or EXE changed.

Ranking below sorts calibrated gameplay render costs. Raw totals include PIT
reads. Band and full-screen paths have different clock-boundary counts, so
adjacent calibrated versus raw ranks can reverse. Do not infer a true speed
winner between near-tied paths from this instrumentation. Repeat means are
identical in this deterministic emulator profile, not a hardware confidence
interval. Costs exclude game/audio ticks, startup, raw dumping and pacing;
relative speed is rendering-kernel throughput only, not playable FPS.

Cache bytes are requested cache payload only, not complete program memory.
Saved ms per cache KiB means(no-cache calibrated cost minus combination cost)
divided by its cache KiB; this is cumulative efficiency against one baseline,
not the incremental value of each cache or an allocation priority rule.
C requires B: twelve valid combinations, including none; four C-without-B
combinations are invalid and omitted. D=0 uses diagnostic bounded-band output;
it is not a qualified replacement for the mandatory production D presenter.

| Rank | Profile | Cache KiB | Gameplay ms | Raw gameplay ms | Relative kernel speed | Saved ms per cache KiB |
| ---: | --- | ---: | ---: | ---: | ---: | ---: |
| 1 | ABC | 130 | 24.285 | 26.914 | 21.92 | 3.908 |
| 2 | ABCD | 190 | 25.746 | 26.078 | 20.68 | 2.666 |
| 3 | BC | 122 | 26.063 | 28.718 | 20.43 | 4.150 |
| 4 | BCD | 182 | 27.461 | 27.789 | 19.39 | 2.774 |
| 5 | AB | 70 | 59.026 | 61.681 | 9.02 | 6.762 |
| 6 | B | 62 | 60.944 | 63.599 | 8.73 | 7.603 |
| 7 | ABD | 130 | 61.265 | 61.597 | 8.69 | 3.624 |
| 8 | BD | 122 | 62.996 | 63.328 | 8.45 | 3.847 |
| 9 | A | 8 | 245.680 | 248.335 | 2.17 | 35.833 |
| 10 | AD | 68 | 248.029 | 248.361 | 2.15 | 4.181 |
| 11 | none | 0 | 532.345 | 535.000 | 1.00 | - |
| 12 | D | 60 | 534.622 | 534.954 | 1.00 | -0.038 |

### Current-build full phase and marginal receipts

Controlled warmed rendering costs, milliseconds per frame; not gameplay FPS.
PIT boundary overhead is calibrated. File I/O, startup and pacing are excluded.

| Profile | Cache KiB | Title total ms | Gameplay total ms |
| --- | ---: | ---: | ---: |
| none | 0 | 532.094 | 532.345 |
| A | 8 | 300.766 | 245.680 |
| B | 62 | 74.932 | 60.944 |
| AB | 70 | 73.162 | 59.026 |
| BC | 122 | 25.795 | 26.063 |
| ABC | 130 | 23.988 | 24.285 |
| D | 60 | 534.222 | 534.622 |
| AD | 68 | 302.988 | 248.029 |
| BD | 122 | 76.894 | 62.996 |
| ABD | 130 | 75.171 | 61.265 |
| BCD | 182 | 27.027 | 27.461 |
| ABCD | 190 | 25.318 | 25.746 |

Positive savings mean faster; negative savings mean slower.

| Added | Context | Added KiB | Title saved ms | Gameplay saved ms | Gameplay ms/KiB |
| --- | --- | ---: | ---: | ---: | ---: |
| A | none | 8 | +231.328 | +286.665 | +35.8331 |
| A | B | 8 | +1.770 | +1.918 | +0.2398 |
| A | BC | 8 | +1.806 | +1.778 | +0.2222 |
| A | D | 8 | +231.234 | +286.593 | +35.8242 |
| A | BD | 8 | +1.723 | +1.731 | +0.2164 |
| A | BCD | 8 | +1.709 | +1.715 | +0.2143 |
| B | none | 62 | +457.162 | +471.401 | +7.6032 |
| B | A | 62 | +227.604 | +186.654 | +3.0105 |
| B | D | 62 | +457.329 | +471.626 | +7.6069 |
| B | AD | 62 | +227.817 | +186.764 | +3.0123 |
| C | B | 60 | +49.137 | +34.881 | +0.5814 |
| C | AB | 60 | +49.174 | +34.740 | +0.5790 |
| C | BD | 60 | +49.867 | +35.535 | +0.5923 |
| C | ABD | 60 | +49.853 | +35.519 | +0.5920 |
| D | none | 60 | -2.128 | -2.278 | -0.0380 |
| D | A | 60 | -2.223 | -2.349 | -0.0392 |
| D | B | 60 | -1.962 | -2.052 | -0.0342 |
| D | AB | 60 | -2.009 | -2.239 | -0.0373 |
| D | BC | 60 | -1.232 | -1.398 | -0.0233 |
| D | ABC | 60 | -1.330 | -1.461 | -0.0243 |

## Phase costs and repeat spread

Three repeats; each phase is the mean of eight measured frames. Ranges below are repeat means.

| Profile | Phase | Prepare ms | Compose ms | Publish ms | Total range ms | Raw total ms |
| --- | --- | ---: | ---: | ---: | --- | ---: |
| none | title | 0.218 | 525.392 | 6.484 | 532.094 to 532.094 | 534.749 |
| none | gameplay | 0.218 | 525.641 | 6.486 | 532.345 to 532.345 | 535.000 |
| A | title | 0.222 | 294.059 | 6.485 | 300.766 to 300.766 | 303.421 |
| A | gameplay | 0.222 | 238.972 | 6.486 | 245.680 to 245.680 | 248.335 |
| B | title | 0.481 | 67.966 | 6.485 | 74.932 to 74.932 | 77.587 |
| B | gameplay | 0.570 | 53.889 | 6.485 | 60.944 to 60.944 | 63.599 |
| AB | title | 0.472 | 66.205 | 6.484 | 73.162 to 73.162 | 75.817 |
| AB | gameplay | 0.481 | 52.058 | 6.487 | 59.026 to 59.026 | 61.681 |
| BC | title | 0.539 | 18.770 | 6.486 | 25.795 to 25.795 | 28.450 |
| BC | gameplay | 0.551 | 19.025 | 6.487 | 26.063 to 26.063 | 28.718 |
| ABC | title | 0.467 | 17.023 | 6.498 | 23.988 to 23.988 | 26.617 |
| ABC | gameplay | 0.575 | 17.212 | 6.499 | 24.285 to 24.285 | 26.914 |
| D | title | 0.218 | 528.569 | 5.435 | 534.222 to 534.222 | 534.554 |
| D | gameplay | 0.218 | 528.970 | 5.435 | 534.622 to 534.622 | 534.954 |
| AD | title | 0.222 | 297.332 | 5.434 | 302.988 to 302.988 | 303.320 |
| AD | gameplay | 0.222 | 242.372 | 5.435 | 248.029 to 248.029 | 248.361 |
| BD | title | 0.534 | 70.926 | 5.434 | 76.894 to 76.894 | 77.226 |
| BD | gameplay | 0.570 | 56.991 | 5.435 | 62.996 to 62.996 | 63.328 |
| ABD | title | 0.476 | 69.259 | 5.435 | 75.171 to 75.171 | 75.503 |
| ABD | gameplay | 0.588 | 55.242 | 5.435 | 61.265 to 61.265 | 61.597 |
| BCD | title | 0.517 | 21.074 | 5.436 | 27.027 to 27.027 | 27.356 |
| BCD | gameplay | 0.545 | 21.479 | 5.437 | 27.461 to 27.461 | 27.789 |
| ABCD | title | 0.477 | 19.406 | 5.436 | 25.318 to 25.318 | 25.650 |
| ABCD | gameplay | 0.588 | 19.724 | 5.434 | 25.746 to 25.746 | 26.078 |

## Paired timing sensitivity

D changes the complete composition/publication path. Its margins are not passive-buffer costs.
Band output has more PIT boundaries. Small raw/calibrated sign changes are inconclusive.

| Added | Context | Phase | Saved range ms | Raw saved ms |
| --- | --- | --- | --- | ---: |
| A | none | title | +231.328 to +231.328 | +231.328 |
| A | none | gameplay | +286.665 to +286.665 | +286.665 |
| A | B | title | +1.770 to +1.770 | +1.770 |
| A | B | gameplay | +1.918 to +1.918 | +1.918 |
| A | BC | title | +1.806 to +1.806 | +1.833 |
| A | BC | gameplay | +1.778 to +1.778 | +1.804 |
| A | D | title | +231.234 to +231.234 | +231.234 |
| A | D | gameplay | +286.593 to +286.593 | +286.593 |
| A | BD | title | +1.723 to +1.723 | +1.723 |
| A | BD | gameplay | +1.731 to +1.731 | +1.731 |
| A | BCD | title | +1.709 to +1.709 | +1.706 |
| A | BCD | gameplay | +1.715 to +1.715 | +1.711 |
| B | none | title | +457.162 to +457.162 | +457.162 |
| B | none | gameplay | +471.401 to +471.401 | +471.401 |
| B | A | title | +227.604 to +227.604 | +227.604 |
| B | A | gameplay | +186.654 to +186.654 | +186.654 |
| B | D | title | +457.329 to +457.329 | +457.329 |
| B | D | gameplay | +471.626 to +471.626 | +471.626 |
| B | AD | title | +227.817 to +227.817 | +227.817 |
| B | AD | gameplay | +186.764 to +186.764 | +186.764 |
| C | B | title | +49.137 to +49.137 | +49.137 |
| C | B | gameplay | +34.881 to +34.881 | +34.881 |
| C | AB | title | +49.174 to +49.174 | +49.200 |
| C | AB | gameplay | +34.740 to +34.740 | +34.767 |
| C | BD | title | +49.867 to +49.867 | +49.870 |
| C | BD | gameplay | +35.535 to +35.535 | +35.539 |
| C | ABD | title | +49.853 to +49.853 | +49.853 |
| C | ABD | gameplay | +35.519 to +35.519 | +35.519 |
| D | none | title | -2.128 to -2.128 | +0.195 |
| D | none | gameplay | -2.278 to -2.278 | +0.046 |
| D | A | title | -2.223 to -2.223 | +0.101 |
| D | A | gameplay | -2.349 to -2.349 | -0.026 |
| D | B | title | -1.962 to -1.962 | +0.362 |
| D | B | gameplay | -2.052 to -2.052 | +0.271 |
| D | AB | title | -2.009 to -2.009 | +0.314 |
| D | AB | gameplay | -2.239 to -2.239 | +0.084 |
| D | BC | title | -1.232 to -1.232 | +1.094 |
| D | BC | gameplay | -1.398 to -1.398 | +0.929 |
| D | ABC | title | -1.330 to -1.330 | +0.967 |
| D | ABC | gameplay | -1.461 to -1.461 | +0.836 |
### S4 review and closure

Single-person executor/coordinator review checks12mask identities, three paired
repeats,20marginal pairs, same executable/config and complete output equality.
Old tables are retained explicitly as historical S2/S3 receipts; this S4 table
owns the current all-profile ranking. No product policy decision is inferred
from diagnostic speed. Retain ABD required/C optional pending an independently
qualified replacement; accepted local artifacts remain at S3 revision.
Evidence-only work reuses accepted source/ABI unit and integration results;
no new production decision or unit assertion is introduced. Documentation and
node accounting gates pass. S4 and T46 close for owner acceptance; no next T
or S is automatically admitted. Cleanup removes task-generated outputs after
owner acceptance. The20ms objective remains unmet even by the fastest tested
calibrated path. This report does not claim486hardware or NESticle parity.
Scope/expected/actual[],new0,transfers0. Historical1992/1992,retained1991/1992
nodes and4260/4261feasible controls(raw4342,infeasible81) unchanged; no whole-game
certificate or new ROM equivalence credit.
