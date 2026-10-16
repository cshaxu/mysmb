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
