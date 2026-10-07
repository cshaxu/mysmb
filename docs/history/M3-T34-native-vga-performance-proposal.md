# Native VGA Output And DOS Performance Package

Admitted M3 T34 after owner acceptance and closure of T33. S1 is active; S2/S3 are planned successors, not concurrently admitted.
This packages the former T32 S9 native-output work, planned S10 optimization
work and its final-audit role as three sequential S slots. There was no
previously allocated T32 S11. Admission allocates T34 and starts S1; never reuse T32 S9/S10 identifiers. T32 and S9 remain suspended,
not certified complete. Their receipts are retained and reusable only within
recorded dependencies; this package owns the queued remaining-work plan.

## Objective And Baseline

Make the original DOS16 game playable with less rendering work and a measured
conventional-memory budget, using native256x240 VGA output and hardware scan
repetition rather than software256-to320/240-to400resampling. Side black
borders are allowed; height filling on the owner's LCD is hardware-dependent
and must be distinguished from logical frame completeness. Preserve all
original game/PPU decisions,61440source pixels,colors,split,priority,updates
and display submissions. DOSBox installed settings remain unchanged.

Retain published T32 S8 P21 source and three products,commit bd4ad25c:
DOS307349B,x86317966B,x64330766B. Counter diagnostic137.665ms;instrumented
PPU59.677ms,mapping44.716ms,VGA18.062ms,game9.341ms,snapshot10.451ms.
Instrumentation and emulator CPU budgets prevent treating these as hardware
FPS or fair NESticle speed ratios. DGROUP49264B,stack2048B;sampled DOS owned
memory449152B with background cache and385632B fallback. These are route
observations,not global peak or universal minimum. Rebind then-current source
and artifacts at admission rather than rebuilding solely to repeat receipts.

The retained S9 P1 mode prototype uses original16-bit tools:61440VRAM pixels
read back exactly,512x480scanout repeats each source pixel2x2,BIOS mode3
restored. No product code changed and no real-game/LCD/cost acceptance yet.
[Retained evidence](M3-T32-rendering-performance-continuation.md#s9-p1-reference-route-and-independent-native-mode-probe).

## Planned S1: Native-resolution VGA Output

Entry: current const PPU slot-row producer. Exit: correctly timed VGA scanout
and restored prior BIOS display mode. Estimated150-300product lines in
platform/dos16 devices,physical plane encoder and composition root;neutral
IO layout only where reusable. No core/state-writer change or new full-frame
allocation. Reuse the current15532-byte exclusive row/text storage; do not revert the accepted T33 text layout.

- Reuse pinned NESticle parameter/mode research as conceptual guidance.
  Native256x240 is preferred; compare320x240with static side borders only if
  required by actual hardware compatibility. Do not silently crop to224rows.
- Directly deinterleave native pixels into four VGA planes;remove software
  resampling and preserve all240rows and256columns. Hardware repeats scanlines.
- Verify exact source-to-VRAM mapping and palette slots,edge pixels,HUD split,
  scroll,sprite priority,dirty-cache/fallback and no lost submissions.
- Run actual DOS startup,WSAD/JK/Enter/Shifts/Escape,Tab both directions,P/O,
  death/area transitions and device reset/exit mode restoration. Check Win32
  regression and original compiler/segment/stack/loader memory.
- Measure PPU,encoding,VGA and whole-step costs on pinned routes before/after;
  report what software work disappears,not only a transfer microbenchmark.

Close only after adoption is source-bound and three EXEs are published/tested,
or after a measured rejection with named unresolved display requirements.
No real-LCD height-fill claim from DOSBox screenshots alone. Physical486SX
qualification remains M4; retain the previous working products until adoption.

## Planned S2: Remaining Performance And Memory Balance

Depends on S1 output decision; first reprofile because eliminating scaling
changes priorities. Estimated80-300product lines per selected bounded cohort,
with actual files and size announced before work. Share general algorithms
and representations across targets; only host ISA/segments/VRAM are host-only.

| Candidate | Remaining question | Memory budget / required disposition |
| --- | --- | --- |
| Bounded coordinate folding | Remove repeated240/480division without changing coordinates | No new cache;unfinished S8 P22 fixture is not a passed candidate |
| Whole-row sprite/opacity composition | Hoist invariant addressing and priority work | Prefer bounded row scratch;prove OAM order,clipping and raw opacity |
| Coarse composition/output fusion | Avoid repeated traversals under the new native path | Reuse existing buffers;drop if S1 already removes the targeted work |
| Snapshot capture/cache copies | Remove duplicate per-tick serialization/copy | Preserve last-running,failed-load and save/restore transaction behavior |
| Byte background cache | Compare direct-copy cost against packed cache | Two surfaces net+61440B;actual loader/resident/fallback evidence required |
| Byte CHR cache | Test only if remaining profile justifies it | Separate net+24576B;not automatically bundled with background cache |

Do not retry rejected transparent-row masks,fine callback fusion or staged
sprite lists without a materially different design/evidence. Every candidate
has one final selected/rejected/not-applicable disposition with complete-stage
cost,memory and correctness. No speculative gain promise;low-memory startup
and no added memory with pure speed gains both remain valued. Close after
this finite candidate register is resolved and every adopted change is tested
and publishes all three EXEs. Any concrete new finding gets a visible scope
amendment,not an endless implicit audit round.

## Planned S3: Combined Acceptance And Reporting

Depends on S1/S2 dispositions. Normally zero product lines;reuse compatible
scoped proofs and repair only concrete remaining defects before closure.
Estimate100-250contained harness/analysis lines if needed.

- Bind current source,original compiler/runtime and three executable hashes.
- Separate source/game/PPU semantic preservation from operational tests;
  unchanged core execution records do not certify the whole ROM.
- Repeat title,ordinary play,scroll,dense sprites,death,area/pipe transitions,
  text switching and P/O;count updates and actual display submissions.
- Resolve the retained S4 global memory/stack/IRQ/NMI and startup applicability
  clauses with exact retained evidence and named limitations. T19 unrelated
  Windows audio startup remains separately suspended;do not hide dependencies.
- Compare NESticle using explicit resolutions,frameskip,audio and CPU budget.
  Same configuration alone is insufficient when auto cycles differ. If the
  no-setting-change constraint prevents fair thresholds,report that gate open,
  never claim faster-than-reference acceptance. Installed settings must not
  be modified to improve a score.
- Report startup/steady-state conventional memory,cache/fallback allocation,
  loader bounds and stack separately;sampled maxima are not global proofs.
- Report playability evidence separately from real25MHz486SX qualification.

T success requires adopted code correct and operational,no open scoped
regression,and all claimed performance/memory gates supported by their own
evidence. Unproved cadence/reference/global clauses remain explicit;only an
owner-directed transfer can close with them unfinished. This is not a new
whole-ROM certification round or M2 node promotion.

## Common Execution And Source Boundaries

Before each S:report objective,components,estimated code/memory delta and
fixed verification scope. After each S:report actual changes,candidate
results,open clauses and node/edge totals;automatically admit its successor
only after scoped closure. Each product-code P builds/tests/publishes the
existing mysmb16/32/64EXEs;documentation/test-only P does not refresh them.
No remote exists,so commit locally without inventing a push target.

DOS stays16-bit real mode with original OpenNT toolchain,2048-byte stack,
MS-DOS5baseline,486SX target. No DOS4GW,new driver,helper process,gameplay
shortcut,frameskip,pixel sampling or installed emulator setting changes.
platform contains onlydos16/win32;shared PPU/IO logic stays neutral. All
intermediates,source research,traces and probes remain below ignored build.

Historical athros/NESticle0.2 source is copyright-only conceptual reference,
not redistributable code or provenx.xx implementation. Owner-local x.xx README
confirms-res256240;archived0.2dispatcher enables224while240entry is commented.
Do not copy/transliterate source or mode tables. ROM/binary inputs retain
existing local research authority;record provenance at each new admission.

All three S slots have scope[],expectedMatches[],actualMatches[],new0. Retain
historical1992/1992 and local1991/1992nodes,4260/4261feasible controls
(raw4342,infeasible81);no ROM-node custody moves with this infrastructure plan.
The deferred M2 certificate stays in its separate queue-tail proposal.

## T34 S1 P1 Admission And Current Baseline

Owner accepts T33's delivered text presentation and directs admission of the
queue head. Source baseline is f7ff2b2f; this admission changes documentation
only. Current local products bind DOS320681B/SHA
96178bbc6ded32956a6c871f9964614abd9a8c52b1798db5d6b51c0f549343bf,
x86330766B/SHA3a4aada18d064e9d954240cd73cf9d691c5cdad84a2b1bcd87ce9550a4c37d58,
x64346126B/SHAcfb5b288d2b47a35a396617b64a9507592f20bd51e5dfa80371fc1d02829f8e8.
DOS DGROUP51472B includes2048B stack; logical loader343952..348048B excludes
dynamic allocations. Retained T32 costs are historical diagnostic measurements,
not a measurement of this baseline. Keep working products until native adoption
passes. Shared text defaults80x25; legacy80x50 and accepted Tab behavior remain.

S1 begins with review of current row-to-plane ownership and the retained mode
prototype,then one bounded implementation and source-to-VRAM verification.
Expected150-300product lines in platform/dos16 devices/encoder/root,plus scoped
tests. Expected no new full-frame buffer; actual loader/resident deltas must be
measured. Neutral reusable changes belong in IO,not a third platform component.
No core/PPU decision changes. Actual scope expansion requires a visible amendment.

Fixed S1 acceptance:61440pixels,all240rows/palette slots and edge coordinates;
HUD split,scroll and priority;cache/fallback;mode restoration and graphics/text
switching;actual DOS input/transition routes;Windows regression;original16-bit
compiler/link/segment/stack/loader;before/after stage costs and three products.
DOSBox stock settings stay unchanged. Hardware scan repetition does not prove
owner LCD height filling or physical486SX cadence. Preserve those distinctions.

S1/S2/S3 each have empty ROM scope/expected/actual sets. Only S1 has a current
admission/run record; successor admission follows scoped closure. Historical
1992/1992,local1991/1992nodes and4260/4261feasible controls remain unchanged,
raw4342/infeasible81,new0. Full M2 certification stays separately queued.
