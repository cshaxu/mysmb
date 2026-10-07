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
