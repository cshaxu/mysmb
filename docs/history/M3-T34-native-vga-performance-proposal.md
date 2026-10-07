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

## T34 S1 P2 Native Adoption And S1 Closure

Native256x240production output replaces the scaled DOS path. Shared IO
validates/deinterleaves identity rows;DOS word gathers borrow segments once
and VGA transfers64-byte plane rows. Original game/PPU sources are unchanged.
Remove the unused scaled-frame device API rather than reinterpret its stride.
No new resident surface:4096source+4096plane bytes reuse15532-byte text storage.
Production delta156added/28removed lines across seven IO/DOS files;tests add
native band/guard/invalid coverage and an original-tool synthetic VRAM probe.

Both Windows widths20focused checks pass. Every legal first/1..16row band
is compared against independent identity indexing with guard/invalid checks.
Original DOS assembly/device readback matches61440pixels,with two text/graphics
round trips and BIOS mode3restoration. Actual local game capture is512x480,
every2x2pixel group equal;all240source rows retained. Native61fixed-input steps
from the same saved frame7466..7527each advance once and submit once,15band
reads versus25previously. This route exercises native snapshot load/ordinary
play;broader physical input/transition acceptance is consolidated in S3.

Same stock-config paired stage diagnostics:median step151.258to135.240ms,
10.590%lower;PPU59.550to55.194ms,mapping44.576to44.178ms,VGA18.062to9.839ms.
These are instrumented emulated PIT costs,not hardware FPS or a fair NESticle
speed ratio. Initial native group-pointer prototype was rejected in favor of
continuous word gathers;remaining mapping cost is recorded for S2.

Original compiler/link/memory checks pass:EXE323049B,DGROUP51472B including
2048stack,14064headroom;logical loader346320..350416B,excluding dynamic heap.
Current products DOS SHA8b6ba8641fa1543bf2306f721e312a4f253d1c4c0b1aea50faca0369ef7f7307,
x86330766B/SHA5745bf218caa476e617047a09d528c46ee3d62a14298c2cde2591157c42aab6d,
x64346126B/SHA8285224cae199c03f20bc54ffca9ab4c89c6b86ea98de3a278462371831a82c2.
All three are refreshed locally;no protected products committed. Stock DOSBox
configuration hash unchanged;no CPU/core/resolution setting changed.

Similar-issue sweep covers DOS timing,pitch/plane offsets,batch source limits,
graphics/text/reset/palette lifetime and the unused legacy-frame device API.
Shared retained scaling API remains tested;Win32 and accepted text art are
unchanged. Native mode proof and runtime entry transfer bind current sources.
S1 engineering adoption closes;no physical LCD/486SX or whole-ROM certificate.
New ROM credit0;historical1992/1992,local1991/1992nodes,4260/4261feasible
controls(raw4342,infeasible81)unchanged. S2 is admitted automatically.

## T34 S2 P1 Admission:Finite Performance And Memory Cohorts

Reprofile confirms remaining PPU and mapping costs dominate. Evaluate the six
registered candidates exactly once at bounded cohort level. Prototype byte
background surfaces with net61440B extra only if allocator fallback and
complete-stage cost justify adoption;share representation across all targets.
Also evaluate bounded coordinate folding,whole-row sprite/opacity work,
composition fusion,snapshot duplicate copies,and byte CHR independently.
No automatic bundling,unbounded new audit or speculative speed promise.
Estimate150-300production lines across neutral PPU/IO and composition roots,
plus focused packed/byte/canonical/cached/fallback tests. DOS host output stays
native;game logic/state serialization and PPU writer semantics are untouched.
Memory accounting covers baseline/extra cache/fallback loader and resident
allocations;each adopted change builds/tests/refreshes all three products.
Empty ROM scope/forecast;successor S3 is not yet admitted.

S2 fusion prototype finding:256x240fits the VGA chain4 aperture(61440bytes).
The project-owned original-tool mode probe changes only sequencer chain4 and
CRTC address units under the same timing. Linear VRAM readback61440pixels
matches,BIOS3restores,and scanout is512x480. This is a concrete implementation
of the registered composition/output fusion candidate:device submits the
unchanged borrowed row view directly. Expected20-40host lines replace the
plane submission path and remove scratch usage;no extra resident buffer.
Current pure byte background prototype is shared;retain packed fallback.
Measure adopted/fallback variants with the same source-bound finite route
before selecting either. No new reference-source import or performance claim.

## T34 S2 P1 Finite Cohort Delivery And S2 Closure

Selected shared byte-slot background cache replaces per-frame nibble expansion
with row copies. Two segment-bounded borrowed stores use124928bytes versus
63488packed;DOS secondary-allocation failure keeps packed storage,first failure
keeps uncached output. Both Windows widths use the same byte representation.
Shared bounded Y folding removes division within the proven0..494sum domain.
DOS chain4 directly consumes unchanged row views;no plane or scale scratch.
Neutral snapshot publication alternates two existing persistent buffers after
successful game/audio capture,removing the duplicate10015-byte copy. Failed
staging retains the current snapshot;load/copy-update resets the cache owner.
No snapshot schema,game decision,PPU writer or device-input meaning changes.

| Registered candidate | Final disposition | Cost,memory and correctness basis |
| --- | --- | --- |
| Bounded coordinate folding | Selected | Exact bounded subtraction;no allocation;included in final paired cost and independent reference-frame regressions. No separate speed claim. |
| Whole-row sprite/opacity composition | Rejected for this delivery | Keep source OAM priority,clipping and opacity scalar path;native16row bands already hoist visible-range/preparation. No separately proven faster sprite redesign;remaining measured PPU35.872ms is a stage bound,not a promised gain. |
| Coarse composition/output fusion | Selected | Chain4 removes measured44.178ms plane stage,retains61440pixels/512x480scanout;no extra RAM. |
| Snapshot capture/cache copies | Selected | Existing buffers swap publication;stage10.449to8.771ms,no extra snapshot allocation;failure/load/paused-save semantics tested. |
| Byte background cache | Selected | Same chain4route86.002packed to66.182byte ms;extra61440heap bytes,61472owned DOS bytes measured. Missing allocation retains exact fallback. |
| Byte CHR cache | Rejected for this delivery | Separate24576B extra,not bundled. Warm background uses its derived surfaces and source decoded8192-byte CHR remains;no demonstrated separate complete-stage gain justifying this memory cost. No speculative estimate or acceptance claim. |

All six candidates now have final dispositions;rejected designs are not
advertised as tested fast implementations. Current native byte61step median
66.182ms versus scaled baseline151.258ms,2.285xratio/56.246%less time,PPU35.872,
VGA7.329,snapshot8.771ms. Packed fallback86.002ms. Fixed source frames7466..7527
advance once and submit once,15reads each;both final encoded snapshot CRC
1900518261matches. This finite route is diagnostic,not full ROM proof,hardware
FPS or a fair NESticle comparison. No emulator setting changes.

Instrumented steady owned DOS blocks540864byte/479392packed,heap-used
168736/107296bytes. These include the same diagnostic image overhead;they are
not the product's exact startup/peak requirement. Actual loader347216..351312B,
page-rounded347360..351456B,DGROUP51472with2048stack,14064headroom;EXE323945B.
Global stack high-water/IRQ/real hardware applicability remains for S3 review.

Each Windows width23focused tests passes,including512byte/packed/canonical
state cases,source-read-only,slot output,guards,cache invalidation/fallback,
independent frame reference,retained text,snapshot continuation,paused-save,
load/file failures and platform purity. Synthetic DOS current chain4device
readback61440matches with two text round trips and BIOS3restoration. Additional
legacy whole-UI harness API compile drift is repaired:neutral palette frame,
current capability flag and active snapshot accessor. It builds;its legacy
50-row physical assumptions are not claimed as current25-row runtime proof.
Actual-product host probes are consolidated in S3 instead.

Production delta115added/49removed lines across nine IO/PPU/host files;
new byte-state test adds86lines plus scoped snapshot/device/API fixture updates.
All three local products refreshed: DOS323945B/SHA
95fae439137c19cc603924c768151fe2f32e83dd31a8f4e4d55a01e8d40923e9,
x86331278B/SHA5d6f0c5ba19efe03e8cb6971da07b16bf65b59b17e6f30535782b848a15819a3,
x64347150B/SHA0064b34ee1abce0741b11babe65ce61c0b4e8c0415bb193da4dabe1db7e4ef1f.
Source/game and device boundaries reviewed;protected binaries stay local.

Similar-issue sweep:all packed-address/read/opacity owners now select byte or
packed consistently;binding/invalidation/cold CHR/attribute/palette and
allocation/shutdown ownership checked. Snapshot capture consumers use the
published accessor;failure does not commit,load restores cache-owned storage.
DOS source/band/mode boundaries remove legacy-pitch ambiguity;no platform
game logic introduced. No unresolved scoped correctness difference found.
S2 closes and S3 admits;ROM credit0,historical1992/1992,local1991/1992nodes,
4260/4261feasible controls(raw4342,infeasible81)unchanged.

## T34 S3 P1 Combined Acceptance Admission

Verification-only successor under owner-authorized execution. Product source
and hashes above are frozen unless a concrete scoped failure needs repair.
Estimated0product lines,100-250contained harness/analysis lines if needed;
no EXE refresh absent product changes. Bind actual Windows Tab/CMD/input/exit
and DOS startup,graphics/text/graphics,input/save/load/exit to current products;
reuse pixel/state/guard proofs within dependencies. Exercise bounded available
memory arenas and name unobserved route/global/physical clauses explicitly.
Review retained S4 stack/IRQ/startup evidence applicability and fair-reference
constraint without changing installed emulator settings. Do not claim whole-ROM
or physical486SX qualification from these tests. S3 closure requires the
proposal's final gate reconciliation,not only a ledger validator pass.

### S3 P1 Scoped Implementation Amendment:Exit During Load

The actual fresh-game route starts,scrolls,jumps and switches text correctly,
but an Escape pressed during expensive load validation is lost:the DOS
after-load keyboard reset clears pending application exit along with stale
controller input. Earlier routes sent Escape after validation and missed this
window. S3 receives this concrete host-input lifecycle repair before closure;
role changes from audit to implementation,still empty ROM scope. Preserve
pending exit through after-load reset while retaining original held P/O/Tab
repeat guards and controller clearing. Expected2-4DOS lines plus a regression
case in the existing DOS root/keyboard harness. Windows clear-game already
excludes application keys and its exit latch is outside loaded game state.
No game logic or file schema change. Rebuild/test/publish three EXEs and rerun
the same failed fresh-game route;do not substitute a delayed-key workaround.

### S3 P1 Exit Repair And Current Combined Evidence

DOS reset now preserves only pending application exit while clearing controller
state and retaining held P/O/Tab guards. Production+4/-1lines;root regression
adds9lines. Controlled old code returns failure1,fixed code0. Windows source
already clears only game keys and holds exit outside loaded state;no change.
Both widths23checks pass with the added regression;original DOS build/link/
memory passes. No core or addressed PPU-state writer changed.

Actual fresh-game route demonstrates title/start,normal level,scroll,jump,
text/graphics switching,valid10035-byte save/load and BIOS3exit. Load remains
at49seconds and Escape at53seconds. One early-Enter retry stayed at title,
produced no save and is rejected as insufficient evidence. Confirmed retry
starts after observed readiness;it enters the actual level and exits. This
does not convert startup time into a universal bound or assert all-input proof.
Native512x480graphics,text640x400,source2x2repetition and palette/priority
proofs retained within their source dependencies. Both actual Windows products
pass three text entries,two Tab returns and Escape;interactive CMD input,
waiting and shell restoration pass. Physical Terminal/all-DPI claims remain
separate from notification-handle geometry.

Actual unchanged S2 product runs under available-memory arenas544/512/448/384KiB
execute and return0,MCB chains valid,no dropped sampler records. Observed owned
maxima526048/464576/401056/393216B. These respectively show byte,packed,
decoded-only and no-cache fallbacks;the last arena samples a brief allocation
at its limit before releasing it. They are route observations,not global peaks
or universally minimal launch requirements. A600KiB request exceeds the parent
fixture's available arena and never launches the child;it is rejected as a
fixture constraint,not counted as product pass/failure. Native text/graphics,
save/load and exit work in the accepted arenas. No installed DOSBox settings
are changed. Keyboard repair adds32logical loaded bytes,but leaves page-rounded
loader allocation,DGROUP and all dynamic allocation sizes unchanged;retained
arena evidence proves those dependencies only,not the patched IRQ window.

Final local products: DOS323977B/SHA
1eab4debc224b675d1d7c433aeb911d507c6add7f2fb874c5290492b660c152f,
x86331278B/SHA710d0670ffe19fa70522d505d786407fd686cef06774c06820867c4e1dd8a1f3,
x64347150B/SHAa6cf857b7d045b6d80cc509652cd94e411a13f5d85daedaba93a7588085d0c08.
Logical DOS loader347248..351344B,page-rounded347360..351456B,DGROUP51472,
stack2048,headroom14064. EXEs refreshed under assets,not staged. Similar-issue
sweep covers both hosts'after-load/reset paths,held shortcuts and application
exit ownership. The earlier fresh-route missing exit is repaired and rechecked;
neither rejected retry nor stale product receipts are called final acceptance.

### Fixed S3 Remaining Gate Register

| Gate | Current disposition | Required evidence before full closure |
| --- | --- | --- |
| Changed-source game/PPU preservation | Scoped pass | No game/state-writer diff;independent pixel,slot,guard/read-only proofs retained. Not full ROM certification. |
| Native output/current products | Pass | Original tools,current hashes,61440VRAM readback,512x480scanout,mode round trips and both Windows widths. |
| Input,exit and snapshot lifecycle | Scoped pass | Actual controlled host routes,transaction/paused-save/failure tests,old/fixed exit regression and confirmed fresh-game repeat. |
| Available-memory startup/fallback | Scoped pass | Four actual arenas and owned-block observations;global requirement not inferred. |
| Performance cohorts | Diagnostic pass | Fixed61steps,151.258to66.182ms,2.285xratio;no hardware FPS/reference claim. |
| Death/area/pipe operational matrix | Scoped pass | Six controller-generated entry checkpoints loaded by the actual current DOS EXE;named lifecycle,mode,snapshot and native pixel receipts below. No original-ROM replay or all-input claim. |
| Global conventional-memory peak | Unproved | Reconcile all allocation phases/stdio/near/far failure branches;sampled maxima alone insufficient. |
| Global stack/IRQ/NMI applicability | Unproved | Retain local CFG/register proofs;prove source/runtime/firmware bounds or record owner-accepted qualification boundary. |
| Equal-budget NESticle reference | Unproved | Resolution,frameskip,audio,guest CPU budget and frame/submission accounting bound to the same comparison;auto budgets are not equal by assumption. |
| Physical25MHz486SX/VGA/LCD cadence | Unproved | Actual target/hardware evidence;DOSBox screenshots and PIT diagnostics cannot discharge it. |

This is the remaining original S3 contract,not another whole-ROM audit or new
candidate round. S3/T34 stay active until the gates reconcile under the existing
proposal closure rule. Owner instruction to execute through closure does not
itself supply missing evidence. New ROM credit0;historical1992/1992,local
1991/1992nodes and4260/4261feasible controls(raw4342,infeasible81)unchanged.

### S3 P2 Six Named Transition Routes

Verification-only delivery;no product/source/harness ABI change and no rebuild
or EXE refresh required. The native route generator uses ordinary controller
input and bound owner-local resources,starting from normal power-on. It never
patches ROM,program counters or RAM to create a transition. One no-jump route
produces death/respawn;one running/jumping route enters the1-1bonus pipe and a
walking underground route reaches its side exit. Controller tuning is fixture
discovery,not a game implementation change. Wrong auto-climb selector was
discarded:upward pipe exit is source engine7with entrance2,not engine1.

Generated checkpoints and the six actual current DOS executions bind product
SHA1eab4debc224b675d1d7c433aeb911d507c6add7f2fb874c5290492b660c152f.
The stock configuration hash remains unchanged;no CPU/core/resolution tuning.
Input helpers/captures/seeds/temporary generator and receipts remain ignored
below build. Parallel runs are functional checks,not performance measurements.

| Case | Natural entry | Actual current-product result |
| --- | --- | --- |
| DEATH | Frame404,engine11,lives2 | Death progresses;last running save frame612/engine6 retained before level reset. Later captured intermediate shows two remaining displayed lives. Do not infer a new running frame from that prior cache. |
| RESPAWN | Frame613,engine0/task0,lives1 | Frame967,engine8,lives1,ground Y176;normal play resumes after life reduction. |
| ENTER | Frame862,engine3,area pointer194 | Frame1161,engine8,pointer165,Y176;vertical entry completes into underground area. |
| AREA | Frame935,engine7,entrance1,pointer165 | Frame1262,engine8,entrance0,pointer165,Y176;new-area initialization/entry completes. |
| SIDE | Frame1153,engine2,pointer165 | Frame1454,engine8,pointer194,Y144;side exit returns to surface. |
| EXIT | Frame1338,engine7,entrance2,Y240 | Frame1593,engine8,entrance0,Y144;upward emergence returns normal control. |

Each route has four native512x480captures with every2x2group identical,a
640x400text capture and restored BIOS text exit. All saves are10035bytes with
valid schema/CRC and no pending/error file. Records establish source-bound
presentation/snapshot/lifecycle operation only:shared C generated the inputs,
so this is not an independent original-ROM oracle or full-game certification.
Retained pixel/reference/guard evidence remains necessary for cache semantics.
No update is made to node/control equivalence dispositions.

The fixed remaining register now has six scoped/diagnostic passes and four
unproved gates:global memory,global stack/IRQ/NMI,equal-budget reference and
physical486SX/VGA/LCD. No denominator expansion,new T or new audit round.
The physical test entry question is pending;no permission or result is inferred
from elapsed time. S3/T34 and the active goal remain open. This P records
neutral evidence only;three local products remain exactly P1's tested hashes.

### S3 P3 Allocation-Bound Inspection Admission

Read-only verification of the current DOS composition allocation graph and
its already-linked historical Microsoft C runtime. The owner-installed
original16-bit compiler/runtime is the existing build provenance;library and
headers are copyright inputs with no redistribution grant. Inspect allocator/
stdio symbols,object relocation/immediate constants and current link bindings
to determine which runtime reservations remain unknown. Do not patch/import
runtime code or turn an observation into a global bound. All extracted members,
metadata/logs remain under ignored build;tracked evidence is neutral.
No product code change/EXE rebuild is planned. This discharges only the named
global-memory gate where evidence supports it;stack/reference/hardware gates
retain their separate original scope. No new ROM-node credit or T/S allocation.

### S3 P3 Application Payload Bound And CRT Binding

Read-only relink with public map reproduces the current loaded image byte for
byte:SHAfb717e0c869c426b752fdb0ab9c520ec4087f0a8cc8d37c9a979279b1d6fd68d.
No actual product is replaced by this diagnostic image. Historical runtime
library SHA5a1b1f376b59a029fd60dcdb3bcb1f1f350786e1442b09529590aac0c81f156f
binds the inspected members. Public map aliases malloc/fmalloc at0040:0A25;
getbuf at0040:1802and freebuf at0040:1358. Header BUFSIZ512agrees with the
linked allocation immediate512. The successful-buffer path owns512bytes;
allocation failure selects a stream-owned one-byte fallback. Freebuf releases
the owned buffer and clears its pointer/ownership fields. No runtime bytes,
disassembly or protected material are tracked.

| Allocation payload | Maximum bytes | Ownership/lifetime |
| --- | --- | --- |
| Exclusive text/row store | 15532 | Required once before device/loop;freed on initialization failure/shutdown. |
| Snapshot wire/staging store | 20084 | Required once;shared codec/load/save reuse it;freed at exit/failure. |
| Decoded CHR | 8192 | One optional near OR far allocation;matching allocator frees it. |
| First background store | 63488 | One optional allocation;failure preserves uncached output. |
| Second background store | 61440 | Attempt only after first success;failure preserves packed output. |
| Current stdio data buffer | 512 | At most one file stream in current save/load/log paths;close precedes replacement/error logging. |

Mandatory application payload35616B;optional persistent payload133120B;
temporary stdio payload512B. Total requested payload bound169248B. This is
not a total DOS-memory bound:initialized image/PSP/environment,allocator header
alignment/paragraph rounding,free-block fragmentation/coalescing,startup/CRT
and DOS transient reservations still require reconciliation. The near530-byte
palette-pair allocation belongs to the canonical non-slot root interface;
current production binds palette rows and cannot take that branch. Ordinary
frames allocate no application storage after the one-shot cache attempts;
all transitions reuse those allocations. Repeated file actions reuse/close
streams,but full allocator-reserved growth is not yet proved from that fact.

The169248payload bound and sampled526048owned bytes are separate quantities.
Global conventional-memory peak stays unproved. This verification-only P
changes0product lines and refreshes0EXEs;all three current hashes stay P1's.
Original /AL compiler metadata confirms text storage15532,snapshot store20084,
snapshot10015,file-service table32,snapshot cache10020and PPU workspace44bytes.
The store includes callback pointers,the extra file sentinel byte and16-bit
ABI alignment;it is not just the sum of the two serialized payload arrays.
Five persistent requests sum168736B,matching the measured occupied far-heap
payload in the byte-cache diagnostic;allocator-reserved space remains distinct.
Historical1992/1992,local1991/1992nodes and4260/4261feasible controls unchanged,
new0. S3/T34/goal remain active;no hardware answer or result is inferred.

### S3 P4 Current Compiler Stack Listings And Interrupt Boundary

Verification-only:original /AL compiler reproduces eight current units with
the exact product flags,including the safe renderer optimization whitelist.
Code/data/fixup records match each current product object;only debug/listing
metadata differ. Units are PPU frame,DOS main/root/devices/keyboard/nibble
expansion,neutral snapshot and application control. No core/ROM code import,
product edit or EXE refresh. Listings,objects and analyzer receipts stay local.

Local CFG analysis covers85functions and resolves their own stack balance and
return depths under their declared call ABI. Constant branches/loops and
switch tables are traversed with a bounded state register;GS PUSH/POP emitted
as split DB bytes are normalized. Semicolon annotations in optimized immediate
operands are parsed as comments. Maximum live caller-owned bytes:initialize596,
background row312,frame internal96,slot-cache prepare92,ordinary present48.
These omit each callee's own nested work and IRQ/firmware overlay;they cannot
be compared directly with the2048-byte whole-program stack as a full proof.
Thirteen indirect call sites still need target/callee-depth reconciliation.

Current installed keyboard handler has34caller-owned bytes at its deepest
call and balanced IRET restoration. Scan has22at its control-toggle call;
toggle owns8. With FAR returns and the6-byte hardware entry frame,the reviewed
keyboard/control branch sums78bytes;port I/O leaves are smaller. Current linked
inp/outp bodies preserve BP and return FAR without argument popping. This
bounded branch is not a proof of every foreground frame plus BIOS/NMI nesting.
The handler's original register-save prologue and installed IRQ vector remain
unchanged;the exit repair modifies only pending app state under the existing
interrupt-disabled reset transaction.

Native VRAM REP MOVSD uses USE16addresses/counts,balanced DS/ES saves and
12caller-owned bytes;it makes no nested call. Retained nibble acceleration
owns14bytes,makes no call and brackets its GS/32-bit indexed lookup with saved
FLAGS,CLI,saved/restored GS and POPF. The unmasked uniform path and normal
16-bit keyboard handler retain their distinct register/NMI applicability
requirements;CLI does not mask NMI. No global IRQ/NMI,firmware or all-context
stack certification is inferred from these local facts.

Runtime multiply/divide return windows are diagnostic only and not used to
promote the global stack gate. The inspected eight units call shift helpers,
not those four callee-pop arithmetic entries. Their leaf/helper depths and
remaining core/runtime calls still belong to global reconciliation. The85/85
local balance count is deliberately not an all-path whole-program result.
Four original gates remain unproved;S3/T34/goal stay active. New ROM credit0;
historical1992/1992,local1991/1992nodes and4260/4261feasible controls unchanged.

### S3 P7 State Guards Resolve The Two Abstract Cycles

Verification-only;no core/ROM/product edits. The frenzy back edge changes the
same slot's identifier to8or10/11before checkpoint reentry. Those identifiers
are disjoint from frenzy selectors18and20..23. The second checkpoint therefore
cannot take the same frenzy edge again. Maximum simultaneous checkpoint frames
on this cycle is2,not an unbounded recursive chain. Timer/duplicate-slot exits
only reduce the depth.

The stream page-select back edge requires selector0and increments it to1before
calling loop commands again. A matched loop command clears its command flag
before entering stream. An unmatched or inhibited command does not change
the match/inhibition inputs,and the page-select record changes only enemy
stream/page state before immediate reentry. Reentered loop handling therefore
cannot reset the selector via loopback before its next stream call. Maximum
simultaneous loop-command and stream frames are each2. Offset+2alone would
not prove this because the original offset wraps at8bits;the selector/command
guards are the actual depth argument.

Diagnostic wrappers around unchanged project function bodies count real call
depth while preserving normal return behavior. Synthetic,project-owned inputs
cover20480frenzy combinations(area type,world,random,zero/nonzero timer,five
ordinary slots)and4096stream combinations(all256offsets,selector,matched/wrong
loop and inhibition). Maxima checkpoint2/loop2/stream2support the source proof.
The byte filter is correctly exercised at RAM06dd;the earlier06d1address was
an unused fixture mistake and is not counted as filter coverage. These tests
are C nesting evidence,not independent ROM-equivalence classification.

The whole-source model now keys memoization by remaining bounded-entry counts,
not function name alone. Interior frenzy nodes revisited under a different
count are distinct states;no additional unreviewed cycle remains in that
model. Its1178memo states still leave28external runtime symbols plus startup,
firmware and IRQ/NMI overlay unknown. Main686/root_step664known-source
contributions remain partial and do not certify2048-byte total stack safety.
Original global-memory/reference/hardware gates likewise are unchanged.
New ROM credit0;historical1992/1992,local1991/1992nodes and4260/4261controls
unchanged. Listings,wrapper sources/logs remain ignored;neutral conclusions
only are tracked. S3/T34/goal remain active,with no EXE refresh needed.

### S3 P8 Linked Runtime Leaf Depths

Verification-only;inspect actual P1DOS MZ bytes with the current public map,
not source prototypes or a different CRT build. All28external entry symbols
are anchored;public-anchor windows are not assumed to be complete routines
when calls,service transfers or cross-window branches remain. Runtime/raw
disassembly stays ignored below build under the existing local-only policy.

Sixteen symbols at15unique addresses have complete leaf CFGs in their anchored
windows:all local stack paths balance and return depth0. Byte comparison/copy
own8bytes,fill4,port input/output2,strlen2,near/far free2;shift and CLI/STI
entries own0. Long signed divide owns8,unsigned divide6,multiply2. Their FAR
returns pop8argument bytes for multiply/divide and0for the other reviewed
leaves. This anchors the arithmetic cleanup assumption used in source CFGs.
Aliases count separately as imported symbols,but not as extra implementations.

The state-guarded source model incorporates these leaf costs. Twelve external
symbols still need deeper/runtime-service bounds:dos_getvect,dos_setvect,
fmalloc,nmalloc,fclose,fflush,fopen,fread,fwrite,int86,remove,rename. A window
containing INT21or a shared tail without a local return is explicitly not a
zero-cost leaf. BIOS/DOS interrupt services and NMI overlay remain outside
ordinary caller-owned stack accounting. No full2048-byte conclusion follows.

Source code/current three EXEs remain unchanged;current product SHA
1eab4debc224b675d1d7c433aeb911d507c6add7f2fb874c5290492b660c152f binds the
runtime extraction. Known leaf receipts narrow the existing global-stack gate,
not a new acceptance round or ROM node promotion. Four original gates remain
open;historical1992/1992,local1991/1992nodes and4260/4261controls unchanged,
new0. S3/T34/goal remain active.

### S3 P9 DOS/BIOS Service Wrapper Contributions

Verification-only;actual current MZ windows and shared-tail targets are bound
to the same product/map as P8. Get-vector/set-vector wrappers own2/4bytes;
remove/rename own4/6bytes. Their INT21hardware entry adds6bytes before the
unknown DOS service body. Remove/rename tail-jump to the common result path,
not a missing return. Its error branch calls the no-stack inner mapper via
a2-byte near return address,then restores the inherited BP frame and returns
FAR. Wrapper CFGs balance conditional on the service returning the original
SP. DOS/BIOS bodies are not silently assigned zero cost.

Current int86calls all request INT10. Its own pushes/local staging peak22bytes.
The generated normal thunk has a4-byte FAR return plus6-byte INTentry frame;
at the BIOS entry the wrapper/thunk/hardware contribution is28bytes. The
error path's private mapper is included in this wrapper analysis. Special
INT25/26flag-discard paths are not used by the current composition;arbitrary
interrupt-number API clients are outside this applicability statement.
No BIOS internal,firmware/NMI or whole-program2048-byte bound is inferred.

This resolves caller-owned contributions for five of the twelve P8service
entries,while preserving their delegated service-depth clauses. Seven runtime
entries remain without complete nested contributions:fmalloc,nmalloc,fclose,
fflush,fopen,fread,fwrite. The16leaf symbols and5wrappers must not be described
as21complete environment-inclusive bounds. Startup before main and IRQ/NMI
overlay likewise remain. Four original gate families stay open.

No product code or EXE changes;all three tested P1hashes retained. Neutral
conclusions only tracked,raw runtime bytes/disassembly remain ignored. ROM
credit0;historical1992/1992,local1991/1992nodes and4260/4261controls unchanged.
S3/T34/goal remain active pending the unresolved original requirements.

### S3 P5 Constructor-Bound Indirect Calls

Read-only verification. Original /AL offset metadata matches every previously
reported13indirect instruction's field offset. Current DOS constructor binds
11active sites;two generic interface branches are not used by production.
Following file replacement reaches one further existing indirect call,so the
review covers14sites in the known-component call chain. This is a callee-chain
expansion,not a new source-universe/candidate round or original-ROM edge count.

| Caller field / byte offset | Current target / disposition |
| --- | --- |
| workspace.nibble_expand /40 | DOS nibble expander;active packed fallback. |
| workspace.expand /32 | Portable palette expansion;canonical non-slot interface,not current DOS slot path. |
| source.read_rows /4 | DOS root read_rows. |
| root.present_palette_rows /30240 | Main native-band presenter. |
| root.set_mode /30224(two sites) | Main set_mode wrapper. |
| root.present_text /30228 | Main present_text wrapper. |
| root.present_rows /30236 | Palette-source bridge in root. |
| hooks.present_video /9986 | Explicit null;full-frame interface branch not current production. |
| store.files.log /28 | Shared file-service log_file. |
| root.reset_output /30208 | Main reset_output wrapper. |
| hooks.read_input /9982 | Main physical-input wrapper. |
| hooks.submit_audio /9990 | Main audio capability wrapper. |
| file_storage.replace /260 | DOS remove/rename replacement adapter. |

All active targets now have local listing receipts. Expanded11unit compilation
matches current code/data/fixups;97local functions have balanced own paths.
Shared file replacement owns540bytes because it stages two260-byte paths;
its downstream runtime calls remain part of global analysis. Constructors,
slot-row selection,null guards and snapshot binding determine applicability;
loaded snapshots do not serialize/replace these host callback tables.
This binding claim applies to the current composition,not arbitrary API users.

Known-component call contributions model674bytes for initialization,
598for presentation and650for root_step's reviewed subgraph. These are partial
models with missing external callee depths explicitly listed;they are neither
lower bounds on all-input behavior nor complete upper bounds. Text/core,
codec/stdio/runtime and firmware overlay still require full reconciliation.
No2048-byte safety conclusion follows from these figures. No product code,
EXE,game/PPU writer or equivalence disposition changes. Four original gates
remain open;new ROM credit0 and historical/local totals unchanged.

### S3 P6 Current Product-Wide Source Stack Census

Verification-only. Extract the fixed168project-source units from the actual
original-tool product build list,including startup hooks;exclude generated
owner resource arrays from function analysis. Recompile157previously unbound
units with identical defines/flags and reuse11verified listing units. All168
code/data/fixup records match current objects. No product code/binary changes,
no original-ROM certification or second source-universe audit is inferred.

The compiler census has897Cfunctions,2064direct call sites and30indirect sites.
These are compiler implementation counts,not the1992ROM-node or control-edge
denominators. Local abstract stack paths balance for896functions. The one
remaining model limitation is legacy pack_planar_band's local near subroutine
and near RET;it is not classified as a product bug. Constructor-bound symbolic
entry reachability excludes it because current chain4output calls no plane
encoder. The source model reaches784functions,with no unresolved local-stack
problem in that current-entry subgraph. Branches are overapproximated;this is
not execution coverage/all-input proof.

All30indirect sites are accounted for:retain14previous bindings,bind11shared
save/load file-table sites,two authored-text filters to actor visible_cell,
and classify three legacy planar encoder capabilities as non-production.
Current25-row output uses compact art;retained50-row interfaces remain intact.
Global-call depth still needs external runtime and firmware costs even after
these targets are known. Callback review does not silently classify old API
clients as current production.

The expanded symbolic model finds two cycles requiring state-guard review:
CheckpointEnemyID -> frenzy -> bullet/cheep producer -> CheckpointEnemyID,and
ProcLoopCommand -> stream process -> ProcLoopCommand. They are abstract call
cycles,not proven unbounded recursion or defects. Check identifiers/stream
progress before assigning finite nesting;no core rewrite is authorized here.
Twenty-eight external runtime symbols remain separately indexed. Startup
before main and BIOS/NMI overlay are not included in the source graph.

Known-source contributions model686bytes at main and664at root_step,with
external costs and cycle guards still missing;do not compare these figures
with2048as a completed upper bound. Four original global/reference/physical
gates remain open. New ROM credit0;historical1992/1992,local1991/1992nodes and
4260/4261feasible controls unchanged. Source listings/raw metadata stay ignored;
only this neutral evidence is tracked. S3/T34/goal remain active.

### S3 P10 Current Binary-File Runtime Contributions

Verification-only. Follow private near/FAR callees from the seven remaining
allocator/file entries in the current linked MZ. The decoder is anchored at
71 public entries; reachable fall-through must be byte-contiguous. Resolve
the allocator's private early-return jump separately. Return-address kinds,
argument cleanup and BP restoration are checked; interrupt service bodies
remain unknown rather than being assigned zero stack cost.

| Entry | Modeled internal peak bytes, excluding root return address |
| --- | --- |
| fmalloc | 64 |
| nmalloc | 50 |
| fclose | 64 |
| fflush | 34 |
| fopen | 56 |
| fread | 122 |
| fwrite | 136 |

These are conditional contributions for the current composition,not total
process bounds. Each modeled return balances at depth0 with argument-pop0.
The current file service opens only rb,wb and ab streams. The actual runtime
mode parser maps b to the binary open flag;the descriptor's text flag remains
clear. Therefore the write routine's text-conversion branch is excluded at
its explicit descriptor test. This is a reviewed caller condition,not blanket
removal of a failing path. Binary error/short-write branches remain included.

The generic text branch reserves128or512dynamic stack bytes and contains
saved-SP restoration plus fatal-exit/debug callbacks. Its general bound is
not established by this receipt. The verifier also distinguishes SP reads
from writes and rejects an unmodeled saved-SP restore. Those are analysis
tool corrections beneath ignored build,not product fixes.

Existing free-buffer evidence still applies:stream-owned buffering is freed
and fields cleared at close;the shared service calls fclose even when an
explicit fflush fails. Reopening can reuse a released stream and allocator
block;this does not prove fragmentation,allocator metadata or a global DOS
memory peak. DOS services,BIOS,firmware,NMI and pre-main startup contributions
remain outside these internal figures. The four fixed gate families stay open.

Current product hashes match the P1 delivery;no product/source change and no
artifact refresh. Raw runtime bytes,listings and analysis scripts remain
ignored. Neutral conclusions only tracked. Scope/expected/actual[],new0;
historical1992/1992,local1991/1992nodes and4260/4261feasible controls unchanged
(raw4342,infeasible81). S3/T34remain active;no global2048-byte or physical
486SX certificate is issued.

### S3 P11 Combined Runtime And Allocator Boundaries

Verification-only, no product change. Combine the retained constructor-bound
source graph with P8 leaves, P9 wrappers and P10 current binary-file entries.
Include hardware interrupt entry bytes at each reviewed service boundary and
propagate the unknown DOS/BIOS body as an unresolved dependency. The model has
1206 memoized contexts and no unreviewed abstract cycle. It does not promote
an unresolved service to a zero-cost leaf or a completed global bound.

The known contribution is720bytes at main and676bytes at a standalone
root_step entry. The linked CRT retains five pushed argument words and a
four-byte FAR return while main executes, adding14bytes:the known main-chain
contribution is734bytes. This remains a partial model,not an environment-
inclusive upper bound or proof that the2048-byte stack is sufficient. Startup
failure/exit,service bodies and IRQ/NMI overlays remain separately required.

The current linked runtime initializes its heap-growth preference to8192bytes.
Its expansion loop tries smaller granularities when an expansion cannot fit;
8192is not a mandatory allocation size for every request. Far free only sets
the reusable-block flag and returns;it does not invoke DOS block release.
Therefore169248application-requested bytes cannot be equated with an owned
MCB peak, nor can close/free be assumed to shrink that peak. Bound retained
segments, growth attempts and reuse of the single temporary file buffer next.
Do not change the original runtime or its preference solely for a score.

Current startup uses the existing empty argument/environment-copy hooks.
The cinit initialization-table ranges are empty and its optional early
initialization callback count is zero in this product. These facts exclude
those ordinary startup allocation paths only;DOS environment ownership,
inherited descriptors and failure/exit behavior are not certified by them.
The retained arena maxima bind their older product hashes,not the current
P1 EXE. Preserve their documented applicability instead of silently rebinding.

An executable-hash-bound receipt checks the initialized growth value, free
instructions, main call/push sequence and combined model. Three local product
hashes are unchanged. Raw machine data/tools stay ignored below build;only
neutral conclusions are tracked. Scope/expected/actual[],new0;historical
1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342,infeasible81)
unchanged. All four fixed gate families remain open;S3/T34remain active.

### S3 P12 Repeated Buffer And File Reuse Probe

Verification-only. Build a contained DOS harness with the original /AL /Gs
compiler,2048-byte stack,existing empty startup hooks and the same historical
CRT library hash as P3. It holds five far allocations of15532,20084,8192,
63488and61440bytes,then repeats1000times:allocate/free512bytes,open a binary
file,write513bytes and close. A second cohort first opens/writes/closes a
file before allocating those five persistent blocks. No protected game data
or game routines are needed. This is an allocator/stdio probe,not a product
substitute or real486SX performance measurement.

At each sample the harness walks the DOS MCB chain and sums current-PSP-owned
paragraphs including MCB overhead. The packed MCB layout is checked at compile
time in the second build. Both cohorts report1000completed iterations and
zero allocation/file/stability failures. In the fixed-first cohort,baseline,
first/last iteration,observed peak and after-free samples all equal249264bytes.
In the file-first cohort they all equal249376bytes. These absolute figures
include the smaller harness image and its different DGROUP/heap layout;they
must not be quoted as MySMB memory usage. Product near-first decoded-cache
fallback and low-memory failure branches are not exercised by these cohorts.

The unchanged observations support reuse of the temporary buffer after the
fixed allocations;the post-free samples corroborate retained DOS blocks.
The static allocator review explains why:it tests/coalesces free block tags
and searches existing segment chains before expansion. A reusable sufficiently
large far block can satisfy the next equal-sized request without a new DOS
allocation. This scoped invariant does not establish all startup placement,
near-fallback,fragmentation or global segment-capacity bounds. No global
memory gate is closed from two finite successful cohorts.

Cold probe SHA5e034897dd0f91f00b0b1c636370248d3df57eba416fc4a4c5122c89343d6e7e;
file-first SHA1eca41f50de93540acc7ffba9f74b4a09b7a79910d0e79b80036d2583339b913.
Stock DOSBox configuration SHA remains
0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917.
SDL dummy output avoids foreground use;no CPU/core/resolution setting changes.
Harnesses,receipts and raw runtime material remain ignored below build.
No product/source/EXE changes,scope/expected/actual[],new0. Historical1992/1992,
local1991/1992nodes and4260/4261feasible controls(raw4342,infeasible81)remain
unchanged. S3/T34stay active with the same four original gate families.

### S3 P13 Current Product Memory-Arena Endpoints

Verification-only. Repeat the retained384and544KiB parent-arena fixtures with
the actual current DOS product SHA
1eab4debc224b675d1d7c433aeb911d507c6add7f2fb874c5290492b660c152f.
Prior arena receipts remain bound to their older binary. Do not silently
replace their identity or claim that this repeats the512/448KiB cohorts.
The two current runs use independent hidden SDL-dummy DOSBox instances and
unchanged stock configuration. Parallel elapsed times are not used as
performance measurements or an equal-budget reference comparison.

Both parent fixtures report execError0,result0,badChains0,dropped0 and current
product hashes. Each has four512x480graphics captures,640x400text and restored
exit captures. The10035-byte schema2save has a valid CRC and absent DOS audio
state;completed saved frames are7492and7641respectively. No pending file or
error log remains. These observations bind startup,load/save,Tab and Escape
to the current product within the declared fixture,not all input/transition
paths or physical hardware. Native pixel equivalence keeps its existing
scoped receipts;capture dimensions alone do not establish pixel equality.

Current observed owned maxima are393216bytes at384KiB and526048bytes at544KiB.
The higher fixture's final sample separates351728primary bytes,160environment
bytes and174160auxiliary bytes across five owned MCBs(primary,environment and
three auxiliary blocks). Primary351728equals the page-rounded351456loader
envelope plus256PSP and16MCB bytes. Auxiliary capacity includes CRT headers,
paragraph rounding and retained slack;it is not the169248requested-payload
bound. The lower route includes a transient auxiliary expansion and later
returns to392864owned bytes,so stable post-file samples alone would miss its
393216peak. Do not use an after-close sample as a global peak proof.

These current endpoints corroborate the retained operational cache/fallback
evidence and narrow the product-identity gap. All startup placement,near/far
failure/resizing and service/firmware clauses remain required for global
memory/stack acceptance. No new product defect or justified product change
is established by these runs. No code/EXE refresh,ROM credit or whole-ROM
certificate. Scope/expected/actual[],new0;historical1992/1992,local1991/1992nodes
and4260/4261feasible controls(raw4342,infeasible81)unchanged. Raw fixtures,
captures and scripts stay ignored;four fixed gate families remain open.

### S3 P14 Cache Inventory, Priority And Controlled Costs

Owner requests all large caches/workspaces and marginal costs,automatic
lower-memory cache tiers,and synchronous on-demand P saving. This part first
delivers DOS packed-background priority and its measurements. On-demand
snapshot/streaming work remains explicitly unfinished below;do not describe
the current products as having removed per-frame capture.

Only DOS composition allocation order changes:request the63488-byte packed
background before the8192-byte optional CHR buffer;retain second-allocation
failure as packed output. No game/PPU writer,codec or input decision changes.
The previous448KiB route spent its optional capacity on CHR and lacked a
background cache. Current448KiB retains packed background without decoded CHR.
This is a reviewed fallback-priority repair,not a new game behavior.

Original /AL sizeof metadata identifies every current DOS cache/work block
above4096bytes. Static members and combined allocations are distinguished:

| DOS block | Bytes | Purpose / residency |
| --- | --- | --- |
| Decoded CHR | 8192 | Optional derived tile indices;near or far,never both. |
| First background allocation | 63488 | Optional2048-byte nametable snapshot plus two30720-byte packed surfaces;byte mode reuses its61440image bytes as one surface. |
| Second background allocation | 61440 | Optional second256x240byte surface;adds60KiB over packed mode,total124928background bytes. |
| Recent-running snapshot cache | 10020 | Static root member,10015snapshot bytes plus management. |
| Snapshot spare | 10015 | Static root member,alternates capture/publication with the cache. |
| Snapshot file transaction store | 20084 | Far allocation:10036wire bytes,10015staging and file-service/padding bytes. Do not add its children again. |
| Exclusive text/row store | 15532 | Far allocation:12132text-frame plus3400scene workspace;4096graphics row bytes borrow this allocation. |
| Text decision observer | 5253 | Static game member:two2626-byte producer/visible receipts plus enable byte. |

The last five rows total60904bytes,mostly snapshot/text functionality rather
than optional pixel acceleration. Static cache/spare/observer bytes already
belong to the primary block and must not be added to the total again. The old
full61440-byte DOS pixel frame and scaled/planar scratch are not additional
current allocations. Immutable ROM resources and code are not caches.

Windows additionally owns a61440-byte indexed frame,245760-byte DWORD frame,
two16000-byte CHAR_INFOarrays,11760PCM sample bytes across eight buffers,
and a12132-byte neutral text frame. Its VT allocation requests386048bytes
and borrowed shell-title allocation131072bytes. These Windows-only buffers,
their structure overhead and OS allocations do not consume DOS conventional
memory. Shared background/snapshot/observer blocks retain their own owners.

Seven contained original-tool cohorts use current source/libraries,one fixed
controller route,64steps with three warm-up samples omitted,and unchanged
stock DOSBox settings. Six cache combinations plus copy-publication control
complete61samples,one update/submission and15row reads per sample. Each ends
at frame7527with snapshotCRC1900518261;all actual allocation flags match the
intended combinations. Current raw-CHR/packed pixels additionally match the
canonical compositor across512generated states on both Windows widths.

| Optional cache combination | Payload KiB | Median step ms | Mean step ms | Median PPU ms |
| --- | --- | --- | --- | --- |
| None | 0 | 557.285 | 561.041 | 527.003 |
| CHR only | 8 | 272.830 | 275.571 | 242.544 |
| Packed background only | 62 | 85.614 | 88.999 | 55.330 |
| Packed background plus CHR | 70 | 85.999 | 89.347 | 55.722 |
| Byte background only | 122 | 65.801 | 67.021 | 35.480 |
| Byte background plus CHR | 130 | 66.196 | 67.406 | 35.871 |

Marginal median costs are conditional,not additive:CHR alone saves284.455ms
relative to no cache;packed-only saves471.671ms relative to no cache. Adding
CHR after packed/byte background shows no benefit on this route(0.386/0.396ms
slower),not proof that CHR is useless in every scene. Extra60KiB saves19.813ms
without CHR or19.803ms with it. Earlier86.002/66.182figures were61-sample
medians,not arithmetic means. Neither table qualifies physical486SX FPS or
an equal-budget NESticle ratio.

Copy-publication control retains the same130KiB pixel caches and existing
snapshot buffers:median step67.846ms versus66.196no-copy;median snapshot stage
10.443versus8.771ms. The publication optimization saves about1.672ms in that
stage with no additional buffer. Per-frame capture itself still costs8.771ms;
the owner's on-demand instruction targets that larger remaining expense.
Snapshot/text functional blocks have no separately established acceleration
delta;do not fabricate per-block milliseconds for them.

First no-background runs hit the28-second probe deadline and were rejected;
only probe deadlines were extended for the repeat,not emulator settings or
the64-step workload. DOS shell IF redirection creates an empty fail marker
even when the condition is false;reject nonempty failure content,not mere
file existence. Original compiler drivers stalled with long TMP paths;only
the six verified owned processes were stopped,and short distinct ignored-build
TMP paths allowed all cohort builds to complete. No product workaround or
runtime replacement follows from those harness issues.

Current product DOS323993bytes,SHA
76842453b6742e40c316ff28baf3eeb66abbad56e22cace9ca4f104f81419c59;
x86331278bytes,SHA
1f2edd1999a3cadfc3fbe96bf49ffb9beae99cc3450d2a065ac828084f55e981;
x64347150bytes,SHA
aa1a89ac8665b4cb28b9d4c1621b22fb99f3861484c3c3fe9a556bf749fc6044.
Both Windows widths pass23focused checks. Original DOS compile/link/memory
passes:D GROUP51472,stack2048,logical loader347264..351360,page-rounded
347360..351456bytes. Actual current448/544KiB routes pass startup,P/O,Tab,
save CRC and exit;observed owned peaks456384/526080bytes. The higher sample
is32bytes above the preceding product because reordered allocations have an
extra far segment/header;no global peak inference. Prior product-wide stack
and runtime receipts keep their dependency/hash limits,not an automatic
global bound for this changed DOS root.

Qualification helper correction removes stale Arrow/Z/X/F1instructions and
the false no-derived-resource claim,uses current controls/native presentation
and enforces ignored-build output containment. Generated current EXE copy is
byte-identical;outside-build output is rejected before creation. Similar-issue
sweep finds the older historical M4protocol with legacy instructions;retain
it as historical and stop routing current packages to it. No authority or
installed setting is changed by a package preparation.

Tracked diff:5added/1removed DOS lines,7added/2removed focused-test lines,
17added/4removed helper lines,plus neutral governance. Three local EXEs are
refreshed,never staged. Scope/expected/actual[],new0;historical1992/1992,
local1991/1992nodes and4260/4261controls(raw4342,infeasible81)unchanged. Four
fixed gate families and the newly directed snapshot work remain open.

#### Owner-Directed On-Demand Snapshot Continuation

Next bounded corrective segment in this same active S:normal play must not
capture/publish a snapshot every tick. P may synchronously capture,validate,
write the pending file in pieces,close and replace before resuming. Rebase
host timing so synchronous I/O does not become catch-up gameplay;preserve
held input and pending exit. Keep existing paused-P last-running semantics
with an entry-boundary capture rather than continuous capture. All original
game/PPU decisions remain unchanged and shared across targets.

Eliminate the full-file wire allocation through shared IO streaming while
retaining complete validation before any loaded game state is committed.
Reuse existing transaction staging and remove redundant independent snapshot
storage where the audited lifetimes permit. Expected request reduction is
about20KiB under preserved paused-save semantics,not an established DOS MCB
reduction. Source roles:io codec/store,app snapshot marshalling,host roots and
clock adapters;no original core/PPU writer changes. Estimate150-250product
lines plus focused transaction/paused-boundary/clock tests;measure actual diff.

After reduced base memory changes allocation thresholds,recheck the owner's
policy that four-hundred-KiB budgets stay on packed/lower cache tiers even if
the byte allocation could fit;keep required P/O storage ahead of optional
caches. Capture failure,short I/O,bad/trailing/legacy files,resource mismatch,
paused P and load/exit must preserve their declared transaction contracts.
Build/test/publish all three products on code change,then remeasure normal
and P-request steps separately. This plan is not completed implementation.

### S3 P15 Single Workspace On-Demand IO

Owner supersedes the P14continuation's pause-boundary cache and cutoff plan:
merge all snapshot work into one buffer,capture current state only on P,
allow synchronous I/O,audit every space above4KiB,and discuss allocation
strategies before installing new cache thresholds. No500KiB cutoff/query
module is retained. P14's existing allocation-failure fallback remains.

#### Adopted Snapshot Lifetime

One store contains a10015-byte snapshot and file-service hooks:sizeof10048
on DOS16/x86,10080on x64. The10036-byte file image,independent10015-byte spare
and10020/10024-byte frame/pause cache instances are removed from products.
Generic cache APIs remain compatible but no product instance allocates them.
No snapshot is captured or published during ordinary ticks or pause entry.

P synchronously captures current gameplay,including true paused state,into
that buffer;the codec produces a36-byte stack header and streams header/body.
Complete writes,close-before-replace and pending-file cleanup remain. O reads
the bounded header/body into the same scratch,checks exact length/trailing EOF,
version,CRC,resource fingerprint and canonical audio fields before publishing
a candidate to composition. Original-ROM/game/text field validation remains
in app/text consumers before game restore. Failed reads can dirty scratch,
not live state;the next P recaptures all state. No destructive restore/rollback
or second disk pass is used. The generic contiguous decoder still leaves its
output intact on rejection. Both schemas retain their exact file formats.

Application ticks stop during synchronous requests. Save rebases timing
without clearing held input;load rebases even on a failed file operation.
Successful load retains the existing device/input/audio reset owners.
No Start input or original pause flag is changed for I/O. Paused saves now
restore their actual pause state,per the owner's complete-current-state
instruction;Enter resumes through the original control path. This explicitly
supersedes the earlier paused-P last-running-frame policy,not a ROM rewrite.

#### Verification And Costs

Both Windows widths pass23focused checks. Transaction tests cover partial
17-byte writes/23-byte reads,open/read/write/close/replace failures,short and
trailing files,corruption and legacy EOF-versus-error. Failed commits preserve
live state;paused P after a dirty failed load writes a fresh valid snapshot.
Normal-step tests leave a poisoned scratch unchanged;P advances no game frame
and invokes clock reset. Both widths' direct isolated text snapshot route
passes console shortcuts,focus pause,current paused restore,scene equality,
60audio-continuation buffers and presenter return. The full host fixture
stops earlier at unrelated geometry assertion131;it is not reported passed
and has a named TODO. Only the changed snapshot route is discharged here.

Original /AL compiler/link passes,DGROUP31440including2048stack;logical loader
328112..332208,page-rounded328352..332448bytes. These are structural envelopes,
not complete heap/IRQ bounds. Three actual pre-final-clock-fix DOS arenas
384/448/500KiB show peaks373856/437408/498880bytes;all pass P/O,Tab,native/text
capture dimensions,save CRC and exit. The final clock-only binary repeats
the500KiBroute. Retain the other two receipts' exact earlier hashes rather
than silently relabeling them. No emulator configuration changes.

Same61-step source route,one update/submission and15row reads each,ends at
frame7527with snapshotCRC1900518261. Fresh final capture occurs outside timing.
Packed step median85.999to77.162ms(mean89.347to80.497);byte66.196to57.314ms
(mean67.406to58.512). Savings8.838/8.882median ms;per-frame snapshot stage is
zero. PPU medians remain55.715/35.872ms. These are diagnostic PIT costs,not
physical486SX rates or an equal-budget reference result. A separate P request
keeps frame7527fixed while synchronously saving;its1225689PIT ticks are about
1027ms on this fixture,not a physical disk-latency promise. DOS truncates that
probe's long receipt filename to8.3;the actual receipt is explicitly read.

Before P15,DOS root30276/store20084bytes;now root10244/store10048. Requested
application storage is reduced30068bytes(about29.4KiB). The root includes the
game and must not be added to its members again. Full-cache observed owned
memory526080to498880saves27200bytes(26.56KiB);new code and allocator/segment
rounding explain why the request saving differs. With all pixel caches,
application heap payload is158700,plus a possible512stdio buffer,not a global
DOS peak. Root/time/header changes invalidate automatic reuse of the previous
product-wide stack hash;existing partial receipts remain within their limits.

No core/PPU writer changes,new ROM credit0. Historical1992/1992,local1991/1992
nodes and4260/4261feasible controls(raw4342,infeasible81)unchanged. All four
original global/reference/physical gate families remain unresolved.

#### Complete Project-Owned Large-Space Census And Policies

Scope is current product-owned heap/static/reserved space above4096bytes,
not diagnostic/test buffers. Allocation-site sweep covers all source malloc,
near/far malloc,HeapAlloc,VirtualAlloc,DIB and thread creation entries;ABI
sizeof and DOS MAP/Windows PE reconcile static containers and load regions.
Children/aliases below are explanatory and never counted twice. External
CRT/OS/driver internal reservations are opaque named dependencies,not zero.

| Space | Bytes / shape | Current use and allocation policy | Strategy status |
| --- | --- | --- | --- |
| DOS root | 10244 | Static;includes9902game and small IO/device composition state. | Adopted:no snapshot slots;retain original state. |
| Game container | DOS9902,x869912,x649944 | DOS inside root;Windows separate static game. CPU2048and PPU2354/2356/2368are members. | Mandatory;do not add children or remove original state. |
| Text observer | 5253,two2626records plus enable | Member of game,source draw receipts for semantic text. | Functional;preserve source/visible phases. Not a pixel cache. |
| Single IO store | DOS/x8610048,x6410080 | DOS far before optional caches;Windows static.10015snapshot plus service hooks. | Adopted:one transaction scratch;valid only after complete check. |
| DOS text/row store | 15532 | One far allocation,12132text frame plus3400scene scratch;graphics4096rows alias it. | Adopted exclusive reuse;retain50-row capacity and25-row default. |
| Windows neutral text frame | 12132 | Static4000three-byte cells plus palette/layout.3400scene scratch is separate and below cutoff. | Current;layout-sized allocation is a proposal,not removal of50-row support. |
| CHR decode | 8192,4096rows times2bytes | DOS near-or-far one optional block;Windows static. | Existing behavior retained;combination priority awaits discussion. |
| Background first | 63488 | DOS optional far,Windows static.2048source snapshot plus61440image bytes. | Packed baseline retained;byte mode reuses this block. |
| Background second | 61440,256x240 | DOS optional far after first,Windows static. | Extra60KiB;failure retains packed. New cutoff deferred. |
| Windows indexed frame | 61440,256x240 | Static final palette-slot surface;DOS has no full-frame allocation. | Functional;possible exclusive text/frame storage proposal. |
| Windows DWORD frame | 245760,256x240x4 | Static RGB DIB submission pixels. | Current;direct indexed DIB is a proposal requiring color/DPI/presentation proof. |
| Console objects | x8616372,x6416408,each of two | Main console and acquisition job each contain16000CHAR_INFObytes. | Current;separate device acquisition from presentation cells is proposed. |
| VT output string | 386048,193024WCHAR | Heap only when VT output succeeds;released on close. | Proposed:selected-row sizing or bounded streaming;must measure extra writes before adoption. |
| Borrowed shell title | 131072,65536WCHAR | Heap only for borrowed host;released after restoration. | Proposed:bounded growth preserving full title;no truncated restoration. |
| Windows PCM/output | samples11760,8x735x2;whole x8612224/x6412352 | Static audio queue/renderer. DOS has no equivalent renderer allocation. | Current;queue changes need underrun/latency evidence and separate audio ownership. |
| Main/console thread stacks | PE2097152reserve,4096initial commit per thread | Windows address reservation;job stack exists during console acquisition only. | Not2MiBphysical RAM by assumption;measure actual commitment before reducing. DOS stack2048is below cutoff. |
| Immutable PRG/CHR | 32768far PRG and8192CHR | Owner-local compiled read-only resources,not acceleration caches. | Retain;table-only pruning needs proven source address domains,not guessed unused bytes. |
| Other read-only art/tables | Within DATA/CONST pools | Individual project art/table entries below4KiB;aggregate pools remain in loader accounting. | Retain accepted art;no duplicate cache allocation. |
| DOS load regions | CODE263286,FAR_DATA33280,DATA18200,BSS10898plus small classes/alignment | Current MAP load pool;13CODEsegments above4KiB plus PRG/DATA/BSS regions. | Keep separate from heap;CODE is the main footprint,not a framebuffer. Compiler/unused-code optimization remains proposed. |
| OS console/GDI/audio/CRT allocations | Implementation-owned size unknown | Handle APIs and allocator metadata/retained blocks. | Track as external,never infer all-process memory from explicit payloads. |
| Legacy snapshot/cache and full-frame interfaces | No current product cache instance;legacy DOS full-frame call can request61440 | Retained API/test compatibility,not additional current allocations. | No product cost counted;require explicit admission before selecting another path. |

The adopted ordering reserves mandatory IO/text storage first;P14 packed
background-first behavior remains. Proposed strategies in this table are not
new allocation rules. In particular no500KiB threshold,CHR removal,layout
shrink,queue reduction,thread-stack change or resource pruning is installed.
The six-cache conditional cost matrix in P14 remains the basis for owner
discussion,not an all-scenes ranking. This finite census does not close the
global conventional-memory or stack/firmware gate.

#### P15 Final Product Binding

Final DOS324873bytes,SHA
30741023c54daea38f6d4efcf8ef1ce201ce509eda442ae48988d6db4d64f726;
x86331790bytes,SHA
f27bc9de503a26c503b01517c552c9ccdae2e1c3b5038478dcd98bd76f52cabc;
x64347662bytes,SHA
ad859df5d6d08ce10d7359a1b0e3c76099c5bdd9d1750e9c6187e628966dd1a1.
Final DOS loaded-image SHA
aa6111356c261d909cde3f29ae0a681618db9a96dbb40582a5252b969b1968fd.
All three local asset paths are refreshed;no protected EXE is staged.
The final500KiBactual route confirms successful launch/load/save/Tab/Escape,
unchanged configuration and current product identity. Other pre-final
receipts retain the declared clock-only applicability limit.

Actual reviewed source delta is154added/77removed product lines across12files;
tests50added/31removed across four files,plus architecture/UX/evidence updates.
The temporary DOS budget-query source/header,root cutoff field and cutoff
tests were withdrawn completely;no surviving build-list change. Core/PPU
writer diffs remain empty. Governance and whitespace gates pass before commit.

### S3 P16 Post-Consolidation Local Stack Binding

Audit only;no source or product change. Re-run the P15 binding and local CFG
tools under ignored build/m3-t34-s3. Six changed source units (app snapshot,
shared snapshot codec/store,DOS main/root/devices) have identical code,data
and fixup records to the final P15 production objects. All72listed functions
have resolved own-stack paths and balanced returns. This is a local bound;
callee depths and asynchronous service overlays are excluded.

The current own maxima are596bytes for initialize,74for snapshot_load,68for
snapshot_save,52for present_current and40for snapshot validation/video mode
setup. The single-workspace change therefore does not move the removed
snapshot buffers onto the2048-byte stack. The36-byte header and bounded
streaming helpers explain the save/load local contributions. The24indirect
call sites still require current constructor/callee integration;older global
stack sums are not silently promoted to current-product certification.

Evidence:stack-p15/bindings.json,stack-p15/local-cfg.json and re-run logs
p16-stack-bind.log/p16-stack-cfg.log below build/m3-t34-s3. No ROM node or
edge credit;all four original global/reference/physical gates remain open.
Owner directs cache decisions by marginal benefit,prefer smaller memory when
benefits are similar,and requests the complete current optional-cache list.
The P14 six-combination matrix remains the measured basis;no new allocation
policy or cutoff is installed by this audit.

### S3 P17 Current Callback Constructor Review

Audit only. Review all24indirect call operands in the P16bound six-unit
compiler listings against current constructors and source lifetimes. Eleven
store sites bind to seven validated file services;one main presenter site
binds to the root read_rows wrapper;the twelve root sites bind to input,
audio,mode,text,row/palette presentation,reset,clock and logging callbacks.
Twenty-three sites are active;the legacy present_video site is inactive
because the current main supplies null and selects row presentation.

The file initializer copies directory bytes into static storage;the store
copies the validated service table before startup scratch expires. Root hooks
are copied likewise. The new clock callback is bound to the main adapter and
uses the root reset context (null in current production);it resets pacing
only,without altering held keys,pending exit or ROM pause state. Save/load
calls remain synchronous before GameTick;no callback retains staging for
later asynchronous use. Failed load scratch is recaptured on the next save.

Evidence below ignored build/m3-t34-s3:p17-callback-bind.py and JSON receipt
with24source/listing site mappings and source hashes. This is constructor
target/lifetime evidence,not a complete ABI or transitive-stack proof. Nested
file replacement/compositor callbacks,callee depths and external service
overlays retain separate obligations. No code,EXE or ROM-credit change;
all four original gates remain open.

### S3 P18 Conditional CHR Cost On Retained Transition Seeds

Test-only local probes;no product source change. Clone the current P15packed
diagnostic and suppress only decoded-CHR allocation in its paired variant.
Original16-bit compiler/linker and stock DOSBox configuration are retained.
Two controller-generated checkpoints (AREA and EXIT) each run both variants;
61normal-step samples follow warmup/load. Allocation flags confirm packed
background,no byte upgrade,and the intended presence/absence of CHR.

| Seed | With8KiB CHR median ms | Without CHR median ms | CHR saving ms | Rebuilt tiles in measured window |
| --- | --- | --- | --- | --- |
| AREA | 95.898 | 95.554 | -0.344 | 4 |
| EXIT | 97.199 | 96.463 | -0.736 | 0 |

Each step advances one game frame;paired final states agree:AREA frame997,
payload CRC4240562589;EXIT frame1400,CRC3441348231. This is state equality,
not independent pixel equality. Both route pairs exit successfully with
unchanged configuration hash. Runs are finite diagnostic observations,not
physical cadence or equal-budget reference qualification. Small timing
differences are not established regressions without repeated cohorts.

The warm windows do not exercise sustained scroll/rebuild storms or prove
sprite-density coverage. Retain the P14canonical pixel tests and source
contract;do not infer an all-scenes CHR-removal decision from these timings.
Evidence and generator/analyzer stay below ignored build/m3-t34-s3/scene-cache
and build/m3-t34-s3. The8KiBcache remains unchanged pending owner strategy and
the named cold/rebuild coverage gap. No new ROM credit or gate closure.

### S3 P19 Forced Background Rebuild CHR Stress Comparison

Test-only diagnostic,not normal gameplay cadence. Current source review
identifies decoded CHR consumers in background rebuilding,uncached background
rows,sprite pixel extraction and uncached background-opacity checks. Cached
background opacity instead reads the retained slot surfaces. Thus warm
background timings cannot alone justify removing decoded CHR.

Paired original-tool probes retain AREA input/state and packed background;
the probe clears only derived bg_valid before each timed step. Both rebuild
1920tiles per step. The initial64-step windows reached the55000ms script quit
without complete exit/final records;reject them. Rebuilt16-step probes use
separate output directories,retain13samples after warmup and complete normally.
Configuration hash is unchanged;no CPU/core/resolution adjustment.

| Variant | Median step ms | Mean step ms | Median PPU ms | Measured rebuilt tiles |
| --- | --- | --- | --- | --- |
| Packed plus8KiB CHR | 1312.501 | 1312.555 | 1291.440 | 24960 |
| Packed without CHR | 1614.275 | 1614.324 | 1593.210 | 24960 |

The additional8KiB saves301.774diagnostic ms per forced full rebuild. Both
finish frame949with payload CRC3147582427. These finite state receipts do not
independently prove pixel equality,all sprite densities,normal transition
latency,physical FPS or equal-budget reference performance. Source cache
semantics and retained canonical pixel tests remain separate evidence.

The result changes the decision basis:CHR is not established redundant when
background storage exists. Warm cost and rebuild latency must both appear in
the owner cache strategy;no new strategy is installed here. Probe scripts,
failed long windows,completed short windows and result.json remain below
ignored build/m3-t34-s3/cold-cache;analyze-p19-short.py checks13samples per
variant,allocation flags,frame advancement and paired final CRC. Product
source/EXEs unchanged;new ROM credit0;four original gates remain open.

### S3 P20 Final Product Low-Memory Routes And Payload Bound

Audit/runtime only;no product change. Repeat384/448KiBarena routes using the
final P15clock-corrected DOS SHA30741023c54daea38f6d4efcf8ef1ce201ce509eda442ae48988d6db4d64f726.
Combine them with the retained final500KiBroute;do not relabel the older
pre-clock receipts. Each current-hash route has execError0,result0,badChains0,
dropped0,successful script exit,valid schema2save CRC,no pending/log file and
expected native512x480/text640x400capture dimensions. Scripted key,save/load
and Tab operations are covered,not every possible input or visual pixel.

| Conventional arena KiB | Maximum sampled owned DOS bytes |
| --- | --- |
| 384 | 373856 |
| 448 | 437408 |
| 500 | 498880 |

Current production allocation-site review yields mandatory15532text/row plus
10048store bytes,optional63488background+8192CHR+61440byte upgrade,and at most
one512-byte stdio data buffer:159212application-requested heap bytes. CHR near
and far success are exclusive;cache attempts occur once. The530-byte palette
pair branch is not selected by the current palette-row constructor. Core,
text,app and shared PPU have no additional allocator calls;P/O stream through
the same staging and do not request another snapshot. This bound replaces
the older169248payload figure for current source only. It excludes loaded
code/static data,environment,CRT metadata/retained segments,fragmentation and
external startup/services;it does not certify global DOS memory.

Evidence below ignored build/m3-t34-s3:Run-p20-final384/448.ps1,their separate
run directories,verify-p20-final.py and p20-final-memory.json. The verifier
also checks current product/config hashes and retained final500output. All
four original gates remain open;ROM node/control credit0.

### S3 P21 Current Project-Wide Stack Evidence Rebinding

Audit only;no product change. Compare code/data/fixup records of all168current
production source objects to retained compiler listings. Beyond the P16six
units,io/file/snapshot_files.c also differs from P6;compile and bind that
single unit with original flags. Reuse161unchanged units and replace seven
changed listings. The differing file service uses the already delivered
bounded log formatter;this is an evidence update,not another code repair.

The current merged census contains908functions and32indirect call sites.
Current constructor bindings reconcile every site,including the file-storage
replacement callback whose operand/call offset remains unchanged. Entry
reachability includes787functions,all with resolved balanced own paths. The
retained legacy planar internal-return limitation is outside this reachable
set. Retained core cycle guards are reused only after their production object
records match;no new recursion assumption is introduced.

Project-source contributions alone are708bytes from main and692from root_step.
The maximal chain is main/root_step/snapshot_request/snapshot_save/
replace_file/path. These sums exclude CRT callee depths,retained startup,
DOS/BIOS service bodies,IRQ/NMI overlays and firmware;they are not a complete
2048-byte-stack certification. Older runtime-inclusive sums are not rebound
implicitly. No current-source unclassified local path was found;external
integration obligations remain explicit.

Evidence below ignored build/m3-t34-s3:Build-P21File.ps1,
prepare-p21-listings.py,merge-p21-stack.py,stack-p21listings and
stack-current/bindings.json,local-cfg.json,callback-bindings.json,
guarded-chain.json,merge-receipt.json. All four original gates remain open;
ROM node/control credit0.

### S3 P26 Current Keyboard IRQ9 Application Contribution

Audit only. The current keyboard installation replaces IRQ9 while its device
is open and restores the saved vector before normal return. Its interrupt
handler reads the scan byte, updates the bounded project keyboard state, sends
a direct PIC EOI and never chains the saved BIOS keyboard handler. Current
compiler listings give the longest branch as keyboard_interrupt,
keyboard_scan and io_control_toggle: 72 bytes including the C/CRT leaf calls,
plus the six-byte hardware FLAGS/CS/IP entry frame, for a 78-byte known
application-side IRQ9 contribution.

The handler has no allocation, stdio, game tick, PPU or file-callback path.
The current input reader disables interrupts only while copying or clearing
the small keyboard state; it does not assert NMI or establish an arbitrary
firmware nesting policy. This receipt closes the previously unbound project
keyboard contribution, not the global interrupt-stack gate.

Evidence below ignored build/m3-t34-s3:check-p26-keyboard-irq.py and
p26-keyboard-irq.json bind the current product hash, handler CFG, direct EOI
and no-BIOS-chain condition. NMI/firmware, other DOS/BIOS interrupt services
and interrupt-nesting policy remain external. Product source/EXEs unchanged;
ROM credit0;all four original gates remain open.

### S3 P27 Current Application Stack Budget

Audit only. Combine the already current-byte-bound foreground path with the
current IRQ9 application handler without silently adding an external service
depth. The main path contributes720 bytes plus its retained14-byte startup
frame, or734 bytes. IRQ9 can interrupt that path and contributes78 bytes
including its hardware entry frame. The configured DOS stack is2048 bytes, so
the known combined application contribution is812 bytes and1236 bytes remain
unallocated by this accounting.

This is a capacity accounting result, not a global maximum: DOS/BIOS/NMI and
firmware bodies, their interrupt policy and any nesting inside them remain
explicitly excluded. It does establish that the project-owned main and
keyboard paths do not by themselves consume the configured stack. No product
source/EXE changes or ROM credit are implied;all four original gates remain
open.

Evidence below ignored build/m3-t34-s3:check-p27-application-stack-budget.py
and p27-application-stack-budget.json bind the current product SHA, MAP-derived
2048-byte stack, P23 foreground contribution and P26 IRQ9 contribution.

### S3 P28 Current Host Presentation Remeasurement

Run the current x86 and x64 presentation executable after the on-demand
snapshot delivery. Both variants pass2048 exact pixel/reference comparisons,
cache lifetime and priority guards, and1198 native-route frames including
text/graphics workspace alias checks. Dense cached graphics measure339.524us
per host frame on x86 and282.393us on x64;the current VGA scale stage measures
106.560us and98.791us respectively. The retained in-probe snapshot exercise
measures4.322us/4.168us per host frame, but production no longer captures a
snapshot every frame.

These measurements describe the current Windows-host harness only. They do
not establish a before/after DOS comparison, 486SX cadence, physical VGA/LCD
behavior or an equal-budget reference result. Product source and EXEs are
unchanged;all four original gates remain open and ROM credit is zero.

Evidence below ignored build/m3-t34-s3:p28-presentation-x86.log and
p28-presentation-x64.log.

### S3 P29 Current DOS Cache-Tier Route Revalidation

Rerun the actual current DOS16 product with the stock DOSBox configuration at
both384KiB and448KiB loader quotas. Both runs bind the same product SHA and
the unchanged configuration SHA. The injected route captures title, loaded,
text, graphics, reloaded and exit surfaces;it exercises WSAD, J/K, Enter,
both Shift keys, Tab, P/O and Escape before normal exit. The capture probe
reports success for every capture and exit receipt.

This revalidates functional fallback/cache-tier behavior after the current
memory and stack work. It deliberately makes no DOSBox timing, 486SX
performance, physical scanout or global-memory claim. Product source and EXEs
are unchanged;all four original gates remain open and ROM credit is zero.

Evidence below ignored build/m3-t34-s3:run-p20-final384 and
run-p20-final448, including their receipts, captures and probe logs.

### S3 P30 Decoded Sprite-Row Binding

The shared PPU decoded-sprite path previously reconstructed the same far CHR
row base for every one of the row's eight pixels. Bind that decoded row once
per sprite row, then retain the existing flip, two-bit extraction, clipping,
left-edge, priority and palette decisions for each pixel. The change adds no
cache, heap allocation, platform branch, game-state write or PPU-visible
semantic decision.

Controlled x86 host samples in the same build tree place the dense cached
graphics median at254.331us per frame for the candidate versus335.529us for
the reverted baseline;the native-route graphics median is180.781us versus
188.684us. Host scheduling remains noisy and these numbers are diagnostic,
not DOS or486 performance claims. The original DOS compiler emits the same
60-byte local frame for the internal compositor;the linked DOS EXE grows16
bytes while DGROUP,2048-byte stack and allocation policy remain unchanged.

Both x86/x64 established23-test suites pass,including2048 pixel/reference
cases,PPU row/cache cases and platform-purity checks. The original-tool DOS
product passes the unchanged-stock-config384KiB title/load,input,Tab,P/O and
Escape route. Windows packaging strips only debug material and verifies
runtime sections byte-identical before the local x86/x64 products are
refreshed. Current local artifact hashes are DOS16
c148870ddbc2550f1c4892e5b37f5d1a05d1de7a6612b386490c7f40df26f65f,
x86 ed9d946d53759b9b00f30870a775f7b587246288308d7a27423d6152b92932e9
and x64 2283bbdaf16c83cc291a98ea628006fbfee27c39031a0a14c8a250a6c655bfee.

Similar decoded-CHR uses were reviewed. Background rows already bind their
decoded source per tile;background-opacity lookup is only a behind-sprite
priority query and has no repeated row base suitable for this binding. No
additional production hit shares the repeated eight-pixel far-row pattern.
ROM credit remains zero;all four original global/reference/physical gates
remain open.

Evidence below ignored build/m3-t34-s3:p30-candidate-x86-samples.txt,
p30-baseline-x86-samples.txt,p30-ppu-frame.cod,final-tests-x86.log,
final-tests-x64.log,dos16-single-workspace,mysmb32.exe,mysmb64.exe,
product-win-strip.json and run-p20-final384.

### S3 P31 Decoded Sprite Dead-Read Removal

When the shared compositor has a decoded CHR source, its two raw pattern-row
fetches are dead: the existing decoded-row path supplies both pixel planes.
Move those reads into the unchanged no-decoded-CHR fallback, retaining the
same row offset, flip, clipping, priority, palette and output rules. This is
not a cache, heap, platform or game-state change.

Both current x86 and x64 23-test suites pass, including the 2048 exact
pixel/reference cases, PPU row/cache checks and platform-purity checks. The
original DOS compiler/linker returns the DOS executable to 324873 bytes;
DGROUP remains 31440 bytes, configured stack remains 2048 bytes and runtime
allocation policy is unchanged. The current DOS product passes the unchanged
stock-config 384KiB title/load, WSAD/JK, Tab, P/O and Escape route; the
receipt binds product SHA256
c879892da49982c933b61fb8da3837f0808422cb9b3a734d4334f712661052bb and
configuration SHA256
0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917.

The elimination is static and restores sixteen bytes of DOS code relative to
P30. Host timing was not used to claim a quantitative P31 speed result.
ROM credit remains zero; all four global/reference/physical gates remain open.

Evidence below ignored build/m3-t34-s3:final-tests-x86.log,
final-tests-x64.log,dos16-single-workspace,run-p20-final384,
p20-final-memory.json,mysmb32.exe,mysmb64.exe and product-win-strip.json.

### S3 P32 Sprite-Loop Invariant-Hoist Rejection

Review the next adjacent shared-compositor candidate: hoisting a sprite tile
base from its eight rows and a row Y coordinate from its eight pixels. The
candidate preserved the Windows exact-pixel suite on both widths, but the
original DOS compiler grew the executable from324873 to324905 bytes. It
removes only two small arithmetic expressions outside the existing per-pixel
composition, priority and output work;it does not reduce the dominant work
or any allocation. The candidate is therefore rejected and reverted rather
than exchanged for code size or presented as a measurable performance gain.

P31 remains the current source/product baseline. No artifact refresh or
ROM-node/control credit follows from a rejected candidate. Evidence remains
below ignored build/m3-t34-s3:final-tests-x86.log,final-tests-x64.log and
dos16-single-workspace.

### S3 P33 Row-Band Sprite-Range Rejection

The rowwise DOS source presenter invokes the shared compositor in fifteen
sixteen-row bands, so a view-local OAM interval per band was evaluated. Exact
band/full-frame pixels, OAM ordering, clipping, split/priority cases, both
Windows suites and the unchanged-stock DOSBox route all passed. The original
DOS build, however, grew from324873 to325241 bytes and DGROUP from31440 to
31472 bytes.

A paired host diagnostic initially suggested a large benefit, but three
repeat samples measured only about one to two percent difference in the
row-band compositor. That host result is neither stable enough nor a 486
measurement, and does not justify the 368-byte code plus32-byte DGROUP cost.
The candidate and its temporary diagnostic are reverted;P31 remains the
current source/product baseline. No artifact refresh or ROM-node/control
credit follows. Evidence remains below ignored build/m3-t34-s3:final-tests-
x86.log,final-tests-x64.log,dos16-single-workspace and run-p20-final384.

### S3 P34 Current Memory-Tier Route Revalidation

Rebind the accepted P31 DOS16 product, SHA256
c879892da49982c933b61fb8da3837f0808422cb9b3a734d4334f712661052bb, to
unchanged-stock-configuration 384,448 and500KiB routes. Every route completes
the same title/load, WSAD/JK, Shift, Tab text/graphics, P/O and Escape
lifecycle, emits its captures, validates the10035-byte save and exits normally.
The configuration hash remains
0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917 with no
CPU or resolution tuning.

Maximum observed owned bytes are373856 at384KiB,437408 at448KiB and498880 at
500KiB. The staged increases agree with the source's mandatory-first,
optional-cache allocation order and demonstrate that the current product
continues to run through low-memory fallback and progressively richer optional
tiers. They do not enumerate CRT,loader,fragmentation or external-service
paths, so neither a global conventional-memory peak nor a physical-performance
claim follows. Product source and artifacts are unchanged;ROM credit remains
zero and all four global/reference/physical gates remain open.

Evidence below ignored build/m3-t34-s3:run-p20-current384,
run-p20-current448,run-p20-current500,p20-final-memory.json,
verify-p20-final.py and the parameterized route runner.

### S3 P35 Current Application Allocation-Surface Rebinding

Rebind the project-owned allocation statement from P20 to P31 rather than
silently carrying an older product identity forward. The production `src/`
diff from P20's commit774b0a13 to current P31 contains only `ppu/frame.c`;
its nine added/four removed lines select an already bound decoded sprite row
and contain no allocator or file-service call. The DOS allocation owners and
their matched shutdown paths remain exactly `main_dos16.c` and
`dos16_root.c`;the shared binary snapshot service remains in
`io/file/snapshot_files.c`.

The current project request bound therefore remains mandatory15532-byte
text/row storage plus10048-byte transaction store, optional63488-byte first
background store, one exclusive8192-byte decoded CHR store and61440-byte byte
background upgrade, with at most one512-byte stream buffer:159212 bytes.
Palette pairs are not selected by the current palette-row root. Current P34
routes independently bind the same P31 executable at384/448/500KiB.

This proves only the application allocation surface stayed unchanged. It does
not bound CRT metadata, retained free blocks, loader/environment, DOS service
allocation or fragmentation, and so cannot close the global conventional
memory gate. Product source/artifacts are unchanged;ROM credit remains zero.
Evidence below ignored build/m3-t34-s3:p20-final-memory.json,
run-p20-current384,run-p20-current448 and run-p20-current500.

### S3 P36 Equal-Budget Reference Availability Disposition

Review the retained NESticle comparison contract against the current task
environment. The owner-local x.xx reference executable required by that
contract is not currently accessible. The retained result cannot be promoted:
it used a stale MySMB product and differs in resolution/frameskip, while the
historical public0.2 source is copyright-only conceptual material and cannot
prove x.xx binary behavior. No executable, source or installed setting is
changed by this review.

The equal-budget gate therefore remains explicitly unproved. Reopening it
requires the owner-local reference binary and a fixed matrix which binds both
products' hashes, same guest CPU budget, resolution, frameskip, sound/input
route, actual game-update count and actual submitted-display-frame count
across title, ordinary scrolling, dense sprites, death and area transition
routes. Until that material exists, old fivefold observations are historical
context only and cannot be compared to current P31 performance.

Product source/artifacts and ROM-node/control accounting are unchanged. The
other global memory, stack/IRQ/NMI and physical486SX/VGA/LCD gates also remain
open. Evidence is the retained comparison contract and current task artifact
inventory;no local paths or third-party bytes are tracked.

### S3 P37 Physical Qualification Packet Readiness

The physical qualification helper now rejects non-MZ input, records the
executable/map hashes, sizes, MZ relocation count and header length, and
generates a structured `RESULT.TXT` beside the local executable and map copy.
The result form requires the exact host, boot, display and media facts plus
three gameplay routes, all specified controls, three 600-frame samples and
visual/cadence observations. The M4 protocol's obsolete F1 instruction now
matches the current Tab mode-switch contract.

This is only a reproducible handoff package. It neither performs a physical
run nor establishes a global memory peak, stack/IRQ/NMI bound, equal-budget
reference comparison or 25MHz486SX/VGA/LCD cadence. Product source and EXEs
are unchanged;ROM credit remains zero and all four gates remain open. The
local package and its copied executable/map stay below ignored `build/`.

### S3 P38 Reference Artifact Recovery And Launch Probe

The owner-supplied NESticle x.xx ZIP is again available as a local comparison
input. Its retained ZIP hash is`00f5b3fa3a8ba3e23d86d8feae36ec3684b43495aa62b63864e816b022c8fb47`;
the embedded executable is400571bytes and matches
`224e348e1fd5c11b16ef096ff5607c7c57c49d65fa7e4dbbc9b2a5c9c53e832b`.
The external DOS4GW1.97 selected for the local reference has hash
`b8265123ac8a189637448618409ef3ecd2e9f3e1a47062c685a02240f688dec1`.

Under the existing DOSBox settings, the reference remains alive after an
eight-second `256x240`,no-sound launch probe with that extender. This replaces
P36's missing-reference-artifact condition. It is not an equal-budget result:
the probe does not establish frameskip policy,game-update count,submitted
display-frame count,transition coverage or an equivalent MySMB route. The
third-party ZIP,EXE and extender remain outside the repository;no code,table,
runtime or product linkage is imported. Product source/artifacts and ROM
credit remain unchanged.

### S3 P24 Current Startup And Exit Dispatcher Binding

Audit only. Current loaded bytes confirm the two unused argument/environment
copy hooks use balanced large-model no-op bodies;no copying/allocation call
is introduced there. The current cinit early dynamic-hook count is zero and
both initialization dispatch ranges are empty. Five retained words plus the
far main return contribute14bytes at main entry;combined with P23the known
contribution is734bytes. This excludes startup-before-stack-reset and service
bodies and does not certify the whole stack.

The first exit dispatch range is empty;the second contains the actual
flushall handler. Its unpruned nested CFG has unresolved dynamic-SP,text/error
and fatal-handler paths. The84-byte modeled partial contribution is expressly
not an upper bound and is not included as a proven exit result. The existing
startup/exit clause must reconcile current stream flags/buffer lifetimes or
bound those paths;this names a prior pending condition,not a new audit round.
No application edit is justified by this missing evidence alone.

Evidence below ignored build/m3-t34-s3:check-p24-startup.py,
p24-startup-receipt.json,check-p24-flushall.py and
rtl-private-current/flushall-cfg.json. Product source/EXEs unchanged;ROM credit0.
All four original global/reference/physical gates remain open.

### S3 P25 Normal Exit Stream Ownership Condition

Audit only. Resolve the normal flushall condition left by P24 without claiming
its general-purpose CFG safe. Current initialized20FILE slots have five
active standard streams and fifteen unused slots. Current production source
does not read/write standard streams,change their buffering or reopen them.
For the untouched standard streams,fflush's mode/buffer tests take the
no-output path. Private fopen uses only the other slots;getstream first
clears the flag,and openfile publishes its active flag only after successful
open. Its failure path leaves the slot inactive.

Source ownership review confirms every successful snapshot/log open is
synchronously closed. Current fclose's shared return clears the active flag
even when flushing/closing reports failure. Thus private slots are inactive
at ordinary main return. No asynchronous callback retains an open FILE.
These conditions exclude write/text-conversion/allocation paths from normal
flushall:own10bytes plus argument4,far return4 and no-output fflush own8,
total26bytes before caller frames. This conditional bound does not replace
the unpruned84-byte incomplete model for abnormal/fatal paths.

Evidence below ignored build/m3-t34-s3:check-p25-normal-flush.py and
p25-normal-flush.json bind initialized FILE data,current instruction predicates,
source ownership and the absence of standard-stream consumers. The existing
P20normal-exit routes supply separate operational corroboration. New stream
writers,unclosed owners or memory corruption invalidate this condition;no
all-abnormal-input assertion. Startup failure/fatal exit,DOS/BIOS and IRQ/NMI
clauses remain open. Product/EXEs unchanged;ROM credit0.

### S3 P22 Current Linked CRT Leaf Rebinding

Audit only. Relink current production objects using the original linker with
public MAP output and verify loaded-image bytes identical to final P15EXE.
Runtime segment/offset locations have shifted;old raw offsets are not used.
The current external-symbol set remains28. Public-anchored current-byte CFGs
prove16leaf symbols at15addresses balanced,with the same own depths and
argument-pop contracts as P8. Arithmetic helper argument-pop8remains valid.

Merge only these current-byte-proven leaf depths into the P21current project
model. Known contributions are720bytes from main and704from root_step;no
global stack assertion. The twelve remaining entries are dos_getvect,
dos_setvect,fmalloc,nmalloc,fclose,fflush,fopen,fread,fwrite,int86,remove and
rename (linked names retain their ordinary C underscores in receipts).
Prior wrapper/nested-service analysis remains historical until current
dependencies are rebound. Startup,external DOS/BIOS bodies and IRQ/NMI overlays
are still excluded;all four original gates remain open.

Evidence below ignored build/m3-t34-s3:crt-current-map.ps1,crt-current,
rebind-p22-rtl.py,rtl-current/census.json,leaf-bounds.json,rebind-receipt.json,
merge-p22-leaves.py and stack-current/guarded-chain-with-rtl-leaves.json.
No product source/EXE changes;ROM node/control credit0.

### S3 P23 Current Nested CRT And Service Wrapper Integration

Audit only;current byte analysis completes the twelve-entry rebinding left
by P22. Decode current runtime private/public anchors,repair the already
known instruction-boundary gap at its current address and rerun seven nested
allocator/binary-stream CFGs. Own-plus-nested contributions remain64/50/
64/34/56/122/136bytes respectively for fmalloc,nmalloc,fclose,fflush,fopen,
fread and fwrite. Returns balance;no internal undecoded path remains under
the admitted binary-stream condition. The current descriptor flag test and
rb/wb/ab caller bindings retain that condition,not general text-mode proof.

Recheck getvect,setvect,remove and rename wrappers with shared error tails.
The int86window is instruction-identical after explicit near/far code-address
rebasing;retain its22-byte wrapper/28-byte BIOS-entry contribution. No DOS or
BIOS internal body is treated as zero. Merge current leaves,nested entries,
wrappers and hardware service-entry frames with P21project callbacks.
Known contributions remain main720/root_step704bytes,with delegated unknown
DOS/BIOS service bodies rather than unresolved project/CRT callees.

This completes current binding of the previously reviewed project/CRT
contributions. Remaining global stack clauses are before-main/exit,
DOS/BIOS bodies and IRQ/NMI/firmware overlays;they cannot be discharged by
repeating application CFG audits. All four original gates remain open.
Evidence below ignored build/m3-t34-s3:rebind-p23-nested.py,
rebind-p23-wrappers.py,rtl-private-current/nested-binary-cfg.json,
rtl-current/service-bounds.json,nested-service-rebind.json and
stack-current/guarded-chain-with-runtime.json. Product source/EXEs unchanged;
ROM node/control credit0.

### S3 P39 Owner-Directed DOS16 Cache-Tier Ordering

This implementation packet narrows only the DOS16 composition-root optional
allocation order. It requests B, the 63,488-byte packed background tier,
before A, the 8,192-byte decoded-CHR tier. When B fails, it tries A and stops;
when B succeeds, it tries A, and requests C, the 61,440-byte byte-background
upgrade, only if A also succeeded. Thus C failure retains A+B, while A failure
after B retains B alone. The guard is local to `dos16_root.c`; shared PPU
selection, game logic, Windows allocation, cache formats and source pixels do
not change.

Admission evidence is the source-order and allocation-guard review plus the
existing low/mid/high DOS memory routes. Closure requires rebuilt DOS16,
Win32 x86 and Win32 x64 local products, focused cache/fallback verification,
and a route matrix that records each observed retained tier without making a
global-DOS-memory or physical-performance claim. Generated route receipts stay
below ignored build/m3-t34-s3; ROM node/control credit is zero.

The current source-order receipt records B at the first optional allocation,
A immediately after it, and C behind the `bg && decoded` guard. An
allocation-only diagnostic assembled from the current OpenNT objects and the
current root ran through the unchanged owner DOSBox configuration at384KiB.
Its FIT result is `execError0 result0` and its root-owned receipt is
`decoded=1,packed=0,byteCache=0`: B was unavailable, then A was retained,
and C was not requested. This is the first actual fallback observation, not
an inference from the source order.

The same diagnostic can retain `decoded=1,packed=1,byteCache=1` when launched
without the FIT memory arena; that private-configuration feasibility run does
not qualify as a stock memory receipt. Under the unchanged owner configuration,
the 416/448KiB FIT routes have not written FIT's post-exec result. The prior
500KiB child did return `execError0 result0`, but that first diagnostic opened
its report file only after cache allocation and thus could not report retained
tiers. These routes therefore establish neither B-only nor A+B nor A+B+C
behavior. The configuration hash remained
`0494236F2308E2E615F428D04E6470DB4B0D162C95B51F4E276F1B7E73241917`; the
unresolved route must be diagnosed before P39 can close. A private
configuration may not substitute for those stock-route receipts.

The owner-installed OpenNT `link16.exe` is currently rejected by the Windows
loader before link input is processed. P39 may therefore run one ignored-tree
feasibility probe with a local historical Microsoft DOS segmented linker,
using the same OpenNT-generated OMF objects and runtime library. This is a
build-host diagnostic only: it adds no product dependency, changes no DOSBox
setting, and cannot replace the admitted linker without a separate output,
format, segment-limit and runtime review.

### S3 P40 Historical DOS LINK 3.65 Segment-Reduction Feasibility

The current Windows host cannot load the fixed-base OpenNT LINK16 image.  The
admitted local feasibility probe therefore retained OpenNT CL16 object output
and used the owner-local historical Microsoft DOS LINK 3.65 inside a private
DOSBox configuration.  The first unmodified OMF attempt stopped at the old
linker's segment limit.  The probe copied 170 generated object modules below
`build/`, renamed only each module's `*_TEXT` OMF segment into its existing
11 bounded library buckets (largest code bucket 58,304 bytes), rebuilt the
same group libraries with the installed OpenNT librarian, and linked with
LINK's documented `/NOE` duplicate-library policy.  DATA, CONST, BSS, FAR
resource-data, source bytes, and all game/PPU decisions remained unmodified.

LINK 3.65 then emitted a 324,889-byte MZ from the current startup/main/stack,
11 group libraries, and LLIBCE.  The tracked parameterized adapter retains
OpenNT CL16 for compilation, creates private rewritten OMF/library copies,
invokes LINK 3.65 in DOSBox, checks `LINK.DON`, MZ magic, and emits a normal
`mysmb-dos16.exe`/MAP pair below the selected build directory.  The resulting
MAP contains 11 library code buckets plus two direct entry buckets; all are
below the 64KiB old-linker code-segment ceiling.  Original DATA, CONST, BSS,
FAR_DATA and relocation records remain separate.

Actual DOSBox routes reached title, start, right/run, left/release/stop, K
input edge, Escape exit and return to DOS.  The updated receipt recognizes
the current 512x480 native 2x scanout as well as historical 640x400 captures;
it no longer rejects a valid current product before behavior is checked.
The deterministic DOS keyboard smoke separately proves scan `$25` maps to A.
A snapshot route wrote and CRC-validated the 10,035-byte schema-2 file and
restored the saved frame.  These are route and build-host results, not ROM
equivalence or physical performance evidence.

This route is ready for the remaining P39 fallback-memory matrix and ordinary
three-product packaging; it does not by itself close those conditions or add
a third-party runtime dependency.

### S3 P41 DOS16 Optional-C Allocation Preflight

The B/A/C policy retains its prescribed order: B is requested first, A second,
and C only after both are retained. The DOS16 root now uses the standard DOS
allocation query form of `AH=48h` with an intentionally impossible request to
read the largest available conventional block before it asks its far heap for
C's 61,440-byte byte-background cache. If that maximum cannot fit C, the root
does not make an allocation known to fail; it keeps the already selected B/A
state. A positive preflight reserves nothing and preserves the ordinary
allocation failure fallback, so fragmentation between query and allocation is
still handled by the existing allocator result.

This change is confined to the DOS16 composition root. It neither selects a
different PPU/game result nor changes pixels, cache formats, Windows behavior
or the B/A/C allocation order. OpenNT CL16 compiled the resulting source. The
same generated objects were prepared as bounded code buckets and linked by the
installed Microsoft LINK 3.65 inside a private DOSBox configuration. The
325,113-byte MZ MAP has fourteen nonempty CODE segments; the largest is 58,312
bytes, below the 64 KiB old-linker ceiling. A short private DOSBox smoke route
reached title, Enter, D+J, Escape and a normal DOS return. Focused keyboard,
focus-pause and DOS-root tests passed in both Windows widths.

The 384 KiB fallback observation remains B unavailable then A retained. This
preflight does not invent an intermediate-memory result, close the 416/448 KiB
matrix, or establish a physical performance result. Generated compiler,
linker, MAP and DOSBox receipts remain below ignored `build/m3-t34-s3`.

### S3 P42 DOS16 Optional-B Allocation Preflight

The same largest-block query now also precedes B's63,488-byte compact
background allocation. When DOS reports no contiguous block large enough for
B, the root moves directly to A; when it can fit B, the ordinary far allocation
still decides success. Thus the owner-selected order remains B, then A, then C;
the change removes only a request known to fail, and leaves shared PPU/game
decisions, cache bytes and Windows paths untouched.

The current LINK3.65 product completed unchanged-configuration FIT routes at
384KiB and448KiB with title/input and normal Escape return. Neither route's
allocation log contains B's63,488-byte block;both therefore take the B-fail to
A path. At416KiB, the observed post-initialization available bound is below B
and proves the same B impossibility, but the complete product did not reach its
SDL input loop inside the automated30-second observation window. It remains an
open operational route rather than a passing receipt. The current500KiB direct
cache diagnostic retains B+A and not C. Both Windows widths passed focused
keyboard,focus-pause and DOS-root smoke suites. The evidence does not claim a
physical cadence result or close the remaining runtime/memory qualification.
