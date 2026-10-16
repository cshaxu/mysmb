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

Measure the same warmed title and gameplay route under ABD and ABCD, excluding
pacing waits and recording logical ticks, submitted frames, pixels and bytes.
Report whether the measured benefit justifies its additional61,440bytes.
Keep C optional under the accepted policy; any policy change requires a
separate explicit owner decision.

## Acceptance

Both tiers must produce byte-identical PPU output, link and launch through the
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
