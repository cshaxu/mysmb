# M3 T28: DOS rendering optimization without ROM logic changes

## Owner request and queue position

Place the six discussed optimization opportunities second in the queue,after
the core/PPU module split and before the text object/state visual audit.
Owner admits M3 T28 after completed T27;S1 is the sole active audit. The unresolved
T26 performance obligation is explicitly received below.
At admission,reconcile the completed T26 work and module migration so this
candidate implements only remaining opportunities,without repeating accepted
work or retaining obsolete source paths.

## Objective and ownership

Reduce the cost of producing and presenting the same frame. Preserve original
ROM control flow,state transitions,collision,movement,timers,ordered audio
writes and tick/input ordering. Retain the full256x240 indexed source and
borderless640x400 DOS stretch,no dropped frames/ticks or reduced detail.

CHR/background/sprite optimizations belong to the shared PPU compositor,
now src/ppu/frame after the completed component migration.
They must use the same semantics on DOS16,Win32 and x64. Platform VGA work
consumes only the neutral indexed frame;it cannot read Mario,enemy,level or
other gameplay state. Neutral IO and snapshot contracts remain unchanged.

## Owner-approved conventional-memory and playability contract

Owner approves a joint memory/performance evaluation after S2. Conventional
memory must accommodate the actual DOS product;minimize peak consumption while
preserving playability. A small measured whole-frame slowdown may be accepted
for substantial peak-memory savings. Faster rendering alone is not acceptance,
and a successful allocation in one DOSBox session is not DOS qualification.
S2 remains historical evidence,not a requirement to retain its32KiB cache.

The owner clarifies two independent hard gates:memory fit permits reliable
startup and runtime transitions;performance permits normal gameplay. Passing
one never compensates for failing the other. "Small extra cost" is permitted
only within the playable performance budget,not as permission for an unplayable
low-memory build. Before selecting a default,declare the tested runtime,normal
game-tick/presentation cadence and input-response limits;compare complete-frame
cost and tail latency against them. Report launch/fit and playability separately.
A slow but launchable product or a fast but unallocatable product cannot be
reported as accepted. Physical target-machine proof remains a named M4 gate.

For each candidate publish a paired result under identical inputs and unchanged
DOSBox settings:minimum loaded bytes,simultaneous live far/near allocations,
allocator/segment overhead,stack high-water evidence and margins,total peak
conventional memory,largest required contiguous allocation,smallest measured
remaining contiguous block,and measurement coverage/unknowns. Count static VGA
buffers and stack once inside the loaded image;do not count hardware VGA memory
as conventional RAM. File size,DGROUP headroom and fragmented free totals alone
cannot establish fit. Report startup,graphics,text,Tab,save/load and shutdown
lifetime peaks and mandatory-versus-optional allocation/failure behavior.

Pair memory results with warm and cold complete-frame/stage timings,input latency
and representative populated routes. Repeat comparable runs and distinguish
noise from small regressions;report absolute time and bytes as well as percent.
Each candidate records accepted/rejected/deferred,the memory saved versus S1 and
S2,the time cost,the tested minimum free conventional-memory requirement,and
remaining host/hardware limits. Prefer lower memory when the measured extra
cost is small and does not make controls or playability unacceptable. Retain
nondominated alternatives until integrated results select the default;do not
add user-facing tuning solely to avoid making that decision. No speed-only
acceptance rule overrides this owner-approved tradeoff.

Mandatory gates remain exact frame/state/audio/snapshot semantics,full borderless
640x400 output,every original tick/input operation and reliable allocation,
switch/load/exit behavior. Optional cache failure must fall back safely without
displacing required packs. Do not lower detail,drop work,shrink stack without
peak evidence,assume all640KiB is available,or enlarge/change emulator settings.
Declare software memory-fit evidence separately from physical486SX cadence and
DOS-version qualification,which remain M4. Unproved fit or playability is an
explicit deficit,never a success inferred from compositor timing.

The existing S plan receives these bounded additions,no new T or S numbering:

| S | Added memory/performance decision scope |
| --- | --- |
| S3 | Compare decoded occupancy,bitmaps and compact/bounded CHR representations. Include no-cache fallback;prefer avoiding another allocation unless integrated benefit justifies it. Reassess S2's32KiB default against memory saved and whole-frame cost. |
| S4 | Compare full four-plane buffers with scanline/small-batch conversion and direct contiguous submission. Preserve exact scaling,plane order and mode lifetime;measure memory savings and extra segment/device costs. |
| S5 | Consider graphics/text workspace lifetime reuse,including Tab/restore and allocation failure;unchanged-region caches must pay for their peak memory as well as checking cost. Inventory snapshot lifetimes before proposing any reduction;do not discard state or recovery buffers speculatively. |
| S6 | Select the cumulative default from paired peak-memory/frame/input results. Publish required free conventional memory,fit margins,complete-route outcomes and remaining performance/hardware deficits. No memory-fit or playability acceptance without scoped evidence. |

This amendment is governance-only;no product code or EXE changes. S3 remains
active,scope/expected/actual ROM labels[],new0;all conformance counters unchanged.

## Opportunities and suggested order

| Priority | Opportunity | Bounded implementation and correctness obligations |
| --- | --- | --- |
| 1 | CHR decode cache | Decode bound immutable CHR into palette-independent pixel indices once;share the cache between background and sprites. Preserve bounds/absent-resource behavior,flips and transparency. Rebinding resources invalidates the cache;palette animation uses current palette values,never cached final colors. Evaluate full versus bounded cache using actual DOS memory headroom. |
| 2 | Background calculation reuse | Prepare the palette once per frame and reuse tile-row/attribute/address calculations where their inputs are identical. Preserve status-bar split,scroll,mirroring,pattern-bank selection and left-edge masks. Do not cache across a changed visible-state input without an explicit invalidation rule. |
| 3 | Sprite background-occlusion reuse | Retain background opacity information while composing the background;behind-background sprites query that information instead of re-decoding background pixels. Preserve sprite order,transparent pixels,clipping and mask semantics. Select a bounded bit representation after measuring its memory and access cost. |
| 4 | Repeated stretch-row reuse | In the240-to400-row enlargement,convert each unique source row once per plane and copy duplicate output rows. Preserve the exact current coordinate mapping,all pixels and four32000-byte output planes;buffer storage may become bounded rows/batches under the approved memory contract. This reduces repeated conversion,not the required complete output or its video-memory writes. |
| 5 | VGA bulk-transfer optimization | Inspect original OpenNT16 generated copy code;optimize contiguous transfers and unnecessary segment setup within the device owner. Retain four correct plane selections,A000 offsets,far-pointer limits and complete submissions. Any specialized helper remains beneath the platform boundary and is admitted explicitly. |
| 6 | Unchanged-region reuse | Consider bounded dirty regions or unchanged-frame reuse only after earlier measurements. Account for every relevant PPU input,resource identity and presentation lifetime event. Scrolling,VRAM/palette/OAM/mask changes,mode switches and snapshot restore must rebuild the affected output. Continue every game tick,input and audio operation;reuse pixels only when equality is established. |

These opportunities can be combined,but their gains overlap. Record both
incremental and cumulative costs;do not multiply isolated speedup ratios or
promise60Hz on a25MHz486SX before qualification. Prefer priorities1-4 first;
use measurements to decide whether5/6 justify their complexity. A cache that
consumes excessive DOS memory or adds more checking cost than it saves is
rejected with a recorded disposition,not silently counted as implemented.

## Planned S breakdown

These are T28 planned S slots;only S1 is admitted. Estimated sizes below are
changed non-generated source/test lines,not node counts or commitments.

| Slot | Scope and exit |
| --- | --- |
| S1 | Reconcile T26/migration receipts;freeze a representative workload,baseline stage costs and DOS storage budget. Name actual owners,cache keys/lifetimes and all six opportunity dispositions. No speed gain claimed from planning. |
| S2 | Shared CHR cache and background calculation reuse as one composition chain. Compare all scoped frame/state outputs,resource/bounds cases and cache lifecycle;measure incremental and combined costs. |
| S3 | Shared background opacity and sprite-priority chain. Prove foreground/behind-background,mask,flip,clipping and overlap output equality;measure memory and time. |
| S4 | DOS stretch-row reuse and contiguous VGA submission chain. Keep the same full-screen mapping;verify all packed bytes,segment guards,plane readback and mode lifecycle. Retain transfer specialization only when measured beneficial. |
| S5 | Decide unchanged-region reuse using S1-S4 measurements. If worthwhile,implement the bounded invalidation contract and compare cache-hit/miss paths;otherwise record rejection and retain the complete redraw path. |
| S6 | Integrated cumulative regression and performance report,including startup,gameplay,transitions,pause,snapshot,graphics/text switching and exit. Report implemented/rejected/deferred opportunities and remaining performance deficit. |

Before each S,report owners,scope,expected size and exact node accounting.
Keep a reference implementation for the admitted comparison contract;each
optimization must pass on its own and combined with accepted predecessors.
An output/state difference is repaired and rechecked in that S before moving
on. If measurements change the proposed grouping,amend it before admission.

## Verification and acceptance

- Compare complete256x240 indexed frames and original game state,visible PPU
  state,OAM,ordered audio and snapshot semantics under identical inputs.
  Palette cycling,scroll/page boundaries,status-bar split,disabled layers,
  sprite priority,partial clipping and resource-rebind cases are explicit.
- Independently compare every packed VGA byte to the current stretch oracle;
  check far-buffer guards,all source-coordinate coverage and plane readback.
  Verify populated actual DOS graphics,Tab round trips,snapshot redraw and
  restored original video mode on Escape. Text output remains unchanged.
- Use the original DOS16 toolchain and Win32 x86/x64 builds,focused tests and
  platform-purity checks. Every product-code P refreshes all three local EXEs;
  documentation/audit-only work does not require a rebuild.
- Measure stage and complete-frame costs with the same workload and unchanged
  installed DOSBox configuration,including sound. Verify config identity;
  no CPU/cycle/frameskip/machine/render overrides or runtime speed shortcuts.
  Isolated dummy-host device checks earn no performance qualification.
- Report baseline,each retained optimization and cumulative results with
  timing overhead,input latency,DOS memory/stack headroom and remaining deficit.
  A faster compositor alone is not a claim that the complete product sustains
  nominal cadence. Physical486SX qualification remains a separate M4 obligation.

Closure requires all six opportunities explicitly disposed,accepted changes
passing both their scoped equality checks and integrated regression,and a
measured cumulative memory/performance/playability result with unresolved limits visible.
Any unmet performance obligation has a named receiver before closure;no new
ROM certification follows from presentation equivalence alone. Exact affected
labels and zero-credit expectations are registered at admission. Retain the
historical/local node and control counts separately from performance results.

All generated probes,profiles,traces,captures and build intermediates remain
under ignored build. This candidate imports no third-party implementation.
No new owner-local resources or derived source enter Git. The prior owner
exception for existing tracked product EXEs is retained;product-code P work
refreshes those three files. Only neutral research summaries enter this record.

## Accepted T26 remaining-work transfer

Owner closes T26 and admits component separation as T27. This candidate
receives the unproven fixed-config nominal gameplay cadence and remaining
performance optimization obligation. It is now admitted as T28 after completed T27;
reconcile completed T26 work and measure the actual post-split source before
implementation. Neither the transfer nor T26 closure proves playability or
25MHz486SX qualification. No ROM-node responsibility transfers with this
presentation-only obligation.

## S1 P1 admission audit and revised implementation plan

T27 closed at bb5a0f35;this P admits T28 and records a read-only source audit.
No implementation or measured performance improvement is claimed. S1 remains
active:the stage baseline and actual DOS heap/stack budget are not yet measured.

| Current owner | Audit conclusion and disposition |
| --- | --- |
| ppu/frame background_row | T26 already decodes once per tile row,stages a256-byte row,unrolls complete8-pixel tiles and preserves partial edges. Retain,do not implement or count again. It copies16palette entries per scanline;frame-local preparation remains a candidate. |
| ppu/frame pattern and sprite path | CHR bitplanes still decode on each composition. A full8KiB source expanded to one-byte indices needs32768bytes;bounded row cache is an alternative,not a predetermined win. Apply current palettes,bank,bounds and flips at use. Cache owner must be caller-owned compositor workspace,never core state or an implicit process-global cache. |
| ppu/frame behind-background test | Calls background_pixel again for opaque behind-background sprite dots. A full256x240opacity bitmap needs7680bytes;row/tile alternatives must measure access cost and preserve current ordering/masks/split. |
| platform/vga/vga_frame | Already direct full-source320x400 mapping with doubled640x400 scanout. Four400-row conversions repeat240source rows:160duplicate rows per plane. Reuse may avoid40percent of row conversions,not40percent of frame cost or required writes. |
| platform/dos16 devices_present | Already four contiguous32000-byte memcpy calls plus plane selection,not per-dot Win32 calls. Inspect actual OpenNT generated copy before specializing;no assumed transfer gain. |
| platform/dos16 root_step | Input,original tick,presentation,audio extraction/submission and snapshot capture/cache remain serial. Stage profiling must include all these and wait separately before attributing end-frame cost. DOS audio device reports unavailable;do not claim audible DOS sound. |
| Unchanged-region reuse | No reliable evidence yet that invalidation/checking beats redraw. Decision deferred until S2-S4;must include every PPU/resource/lifetime input and never suppress tick/input/audio. |

Memory audit distinguishes loaded/static storage from runtime free heap:
four static VGA pages consume128000bytes;indexed pixels allocate61440far bytes;
text and snapshot transaction packs also allocate far memory. A linker DGROUP
headroom check is not free conventional-memory or stack high-water evidence.
S1 must measure successful allocation sizes,remaining heap,largest block and
stack peak with all normal features enabled,including simultaneous cache candidates.
32768+7680extra bytes cannot be approved from EXE size alone. Bounded cache
segments,allocation failure fallback and DOS16 pointer limits are explicit.

### Revised bounded S ownership and estimates

| S | Components and scope | Estimated change | Exit |
| --- | --- | --- | --- |
| S1 active audit | Retained T26/T27 receipts,current ppu/VGA/root,local fixed-config timing and memory probes. Freeze baseline/reference/workload. | Product0;project-owned profiling/test support0-200lines only if needed,local probes below build. | Representative stage and complete-frame measurements,overhead/control samples,heap/stack budget and cache keys frozen. |
| S2 | Shared ppu/frame palette/background reuse plus measured CHR cache decision;roots only bind workspace lifetime if required. Same algorithm all widths. | 150-350product/test lines,about4-7files. | Full indexed equality,bounds/rebind/lifetime/fallback cases and independent/cumulative timings. Reject cache if not beneficial. |
| S3 | Shared background-opacity/sprite occlusion chain with S2 workspace. | 80-200lines,about2-4files. | Priority/masks/flips/clipping/split equality,far memory guards and incremental benefit;reject unhelpful representations. |
| S4 | VGA repeated-row conversion and measured contiguous transfer specialization. Generic IO scaler unchanged unless genuinely shared. | 80-220lines,about2-5files. | All128000packed bytes,coordinate coverage,plane readback,mode transitions and fixed-config incremental/cumulative costs. |
| S5 | Decide bounded unchanged-output reuse using retained S1-S4 costs. | Reject:product0;implement:100-250lines,about3-5files after explicit invalidation amendment. | Every relevant state/resource/lifetime input accounted for,hit/miss output equality and checking cost lower than savings;otherwise reject with evidence. |
| S6 | Cumulative integrated actual products,startup/gameplay/transitions/Tab/snapshot/input/exit and source boundary review. | Product0expected;test/report50-150lines;scoped repair only if identified. | Six dispositions,combined result and deficits,memory/input latency,three current builds/products for changed code;M4 hardware obligation separate. |

Do not add a separate lifecycle for each cache/table/helper. S2-S4 group their
continuous production path and its tests;each modified-product P builds/packages
three EXEs once. Equality failures are repaired in their scoped S before advancing.
Size estimates exclude local generated artifacts and mandatory governance rows.
No translated core routine is planned to change;workspace lifetime plumbing
belongs to composition and neutral pixel/VGA owners,not gameplay code.

### Fixed baseline and evidence limits

Retain the independent reference compositor and direct-coordinate VGA oracle.
Freeze fixture hashes and source identities under build/m3-t28-s1 before changes;
use title,scrolling ground,underground/water,dense sprites,split/mask/bounds,
palette animation,transitions and restored/Tab cases. Synthetic coverage alone
is not the representative DOS performance workload. Resource binding is immutable
per lifetime;pointer/length keys alone do not license stale results when test
fixtures mutate CHR in place. Tests must explicitly establish/invalidate that
lifetime and cover two simultaneous compositor instances.

T27's paired dummy-host cadence sample advances5frames in each run with equal
10035-byte snapshots. It shows a coarse unchanged paired result,not stage timing,
nominal cadence or hardware qualification. Native Windows QPC test timings
are useful compositor evidence but not a DOS speed estimate. Earlier accelerated
T26 configuration runs are excluded. Installed configuration identity must remain
0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917;
no overrides or alternate CPU/cycles/frameskip/sound settings. Dummy SDL tests
may prove correctness only. Qualified timing needs the normal host/device path,
with bounded nonintrusive execution and no foreground/input takeover. If that
cannot be measured without interference,record the limitation;do not substitute
dummy timing or declare S1 performance baseline complete.

S1 admission scope[],expectedMatches[],actualMatches[],incoming historical
1992/1992,maximum1992/1992,new0. Local nodes1991/1992 and feasible controls
4260/4261(raw4342,infeasible81) unchanged;CheckForEnemyGroup/control-01480
remains needs-evidence. No final M2 certificate or new node/edge credit.
Admission JSON and gate receipts remain under build/m3-t28-s1.

S1 P1 review:node admission validates1992inventory nodes,scope0,expected delta0,
maximum1992;ledger has1992receivers and0orphans. Documentation governance and
Git whitespace checks pass. Product code and three EXEs unchanged;no build is
required for this planning P. Remaining S1 measurements are explicit above.


## S1 P2 closure: fixed-config stage and memory baseline

S1 closes with a bounded instrumented DOS baseline,not a product optimization.
Contained source copies reuse the current original-toolchain product libraries;
only probe root/device timing wrappers and deterministic fixture input differ.
Normal SDL video/audio run on an owned private desktop,with no foreground
activation,global input injection or installed configuration change. All local
probe sources,executables,frames and logs stay below build/m3-t28-s1.
Build/link use the retained OpenNT large-model flags/runtime;no optimizer or
emulator-speed override is introduced. Existing three product hashes stay equal.

| Scope | Measured result in this DOSBox environment |
| --- | --- |
| Ordinary warmed title | PPU1002.30ms,stretch974.04ms,VGA21.59ms,game8.86ms;complete step2008.78ms mean over12steps. |
| Restored ground with decoded right/run input | PPU1002.28ms,stretch974.04ms,VGA21.59ms,game9.39ms,snapshot30.45ms. Complete-step mean2470.23ms includes the first load/redraw;exclude that separately for steady gameplay,never call it cadence. |
| Text route | Complete step925.20ms;graphics compositor/scale/VGA stages absent. Text optimization is outside T28;retained cost is an explicit S6 integration limit. |
| Timing-enabled versus disabled | Same102-second workload,101.972513/101.957322seconds,wall difference0.01490percent. Six complete61440-byte indexed buffers and10035-byte final snapshot equal. This controls clock collection cost,not all probe-versus-pristine overhead. |
| Clock calibration | 100paired collections22668PIT ticks,about0.190ms per pair. Unmodified BIOS PIT rate;wait measured separately. |

Only title/ground/text are complete root routes in the longer sample.
Initial parser-only water/castle fixtures had blank palettes;they are not
accepted colored-scene evidence. The final shorter paired corpus explicitly
applies the original area palette stream and establishes neutral pattern-bank/
mask inputs after original parser staging. Water/castle/dense variants are
controlled compositor workloads,not actual gameplay or new ROM equivalence.
Final six corpus buffers have10/12/12/7/7/10colors respectively;all six indexed
frames and the10035-byte final snapshot match with clock collection disabled.
Dense workload adds64controlled OAM entries with varied attributes. S2 retains
these exact fixture identities and the longer title/ground operational baseline.
Actual transition/split/palette/mask/bounds coverage comes from the independent
existing reference matrix;S6 still owns expanded actual route integration.

Memory evidence:current product427455bytes,minimum loaded451968bytes,193
segments(max64000),DGROUP49440bytes including2048-byte stack. Runtime packs
are61440-byte pixels,20084-byte snapshot store and15400-byte text storage;
128000static VGA bytes are already included in the loaded image,not added twice.
Probe heap has5458free bytes plus a largest DOS block of4640paragraphs
(74240bytes);32768-byte CHR and7680-byte opacity allocations succeed together.
The instrumented product is slightly larger than pristine;this is a conservative
allocation trial in this DOSBox memory layout,not a guarantee on other DOS hosts.
Stack marking begins before initialization in the final bounded memory probe;
458patterned bytes remain after initialization,mode/load and controlled workloads.
Marking margins are96bytes and the result covers only those finite paths.
Full-route stack peak,physical486SX and DOS-version qualification remain M4.

### Frozen decisions for implementation

- S2 tries caller-owned palette-independent full CHR cache against bounded-row
  alternatives;32KiB is feasible here but speed decides retention. Keep per-frame
  palette staging small;no large automatic buffers or near-heap cache arrays.
  Allocation failure uses the existing uncached path and leaves controls unchanged.
- Resource pointer/size and an explicit immutable binding lifetime define decoded
  cache validity. In-place mutated fixtures explicitly reset the workspace;
  simultaneous instances cannot share hidden globals. Palette/bank/scroll/mask/
  split/OAM remain current-frame inputs;no final-color CHR cache.
- S3 may spend7680far bytes for opacity only if measured benefit outweighs its
  construction/access cost;key occupancy before palette conversion,not color equality.
- S4 reuses duplicate row conversion first. Already-bulk VGA writes are a small
  measured cost;specialization is optional,not a prerequisite or assumed win.
- S5 remains conditional on cumulative measurements. No game tick,input,audio
  or snapshot work may be suppressed to improve the benchmark.

Native baseline:both widths pass3focused tests,presentation-performance,
VGA-frame-smoke and platform-purity. Retained matrix independently compares
2048boundary and1198native frames,game-state preservation and packed VGA mapping.
Neutral summary,source/product fingerprints,fixture hashes and paired reports
are retained under build/m3-t28-s1. Early compile/launch and blank-fixture attempts
are excluded;only final-profile and memory-lifetime paired receipts are accepted.
All normal device runs exit0 and installed configuration hash remains unchanged.

Product code0files/0lines changed;local probes are not production and are not
committed. Three EXEs unchanged,no refresh required. Historical1992/1992,
local1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81) unchanged.
Scope/expected/actual[],new0;no custody transfer. No M2/M4 completion or nominal
DOS cadence claim. S1's evidence/workload/storage decision contract is closed;
T28 remains active and S2 receives the bounded implementation below.

## S2 admission: shared background and CHR-cache comparison

Owner execution authorization continues;S2 is the only active S after S1.
Scope:ppu/frame implementation/header,shared cache workspace and its lifecycle
binding at Windows/DOS composition roots,focused compositor/cache tests and
build membership only if a real workspace owner requires it. Core ROM routines,
PPU state/latch semantics,snapshot bytes,text artwork and VGA mapping stay fixed.
Expected size150-350non-generated product/test lines,4-7files;amend visibly if
benchmark evidence requires a materially different interface or footprint.

Keep the reference path available for comparison. Test full indexed output,
source state preservation,absent/truncated CHR,palette changes,pattern banks,
scroll/split/masks,flips/priority/clipping,resource replacement,explicit reset,
allocation fallback and two independent instances. Compare on both widths and
original DOS far-memory ABI;measure each candidate alone and with frame-local
background reuse under S1's unchanged configuration/workloads. Keep only an
observed improvement and publish the independent plus cumulative result.
Product-code P builds/tests and refreshes all three EXEs once;scope equality
failure prevents closure or next-S admission until repaired and rechecked.
S2 scope[],expectedMatches[],baseline/maximum1992/1992,new0,no ROM promotion.

## S2 P1 closure: optional per-instance decoded CHR cache

Retain a caller-owned32768-byte cache of palette-independent two-bit CHR
indices. Each complete row uses a single decoded pointer and eight expanded
loads;partial tiles retain bounded loops. The shared compositor retains its
uncached entry point and optional-storage fallback. Palette,bank,scroll,split,
mask,OAM,flips,priority and clipping remain current-frame inputs. No core or
PPU-state write semantics change. Windows binds static root-owned storage;
DOS attempts one far allocation on first graphics presentation,after mandatory
pixels,snapshot and optional text storage are initialized. Failed allocation
uses the original uncached path and never aborts or repeatedly allocates.

Resource/lifetime sweep:the production CHR binder writes only immutable pointer
and size;both composition roots bind local immutable program resources. Snapshot
restore retains those resources. Workspace pointer/size keys detect replacement;
explicit workspace rebind invalidates same-address replacement/mutable fixtures.
No hidden shared compositor cache exists. Native synthetic consumers retain the
uncached API;Windows/DOS graphics consumers use the shared optional workspace.
Text paths do not read it. Shutdown frees DOS storage;power-on resets Windows
workspace. Dynamic palette changes never require CHR invalidation because final
colors are not cached. All identified consumers have these dispositions.

| Candidate | Fixed-config measured disposition |
| --- | --- |
| Naive full cache with indexed pixel loop | Reject:about33-37percent slower warm PPU stage despite equal output. |
| Expanded-row cache prototype alone | Warm PPU reduction12.695-15.597percent;prototype single-instance globals remain local and are not imported. |
| Frame-local palette staging alone | Reject:3.265-3.592percent slower in the same corpus;reverted. |
| Palette staging plus per-instance cache | Warm reduction11.028-13.558percent;superseded by the better cache-only implementation. |
| Final per-instance cache only | Warm PPU ticks ground1009609,water1142572,castle1142567,dense1276422;versus1195923/1330367/1330367/1461802:12.682-15.579percent less stage time. |
| Final cold first title frame | 1511516versus1195922ticks:26.389percent slower,including first allocation/decode. This is an explicit one-time cost,not a warm speedup. |

Every candidate above uses the same six complete61440-byte corpus outputs and
10035-byte final snapshot;all match S1. Formal probes compile current root
layouts/current compositor rather than reusing pre-workspace objects. Normal SDL
runs on an isolated desktop with installed DOSBox configuration unchanged;
configuration SHA remains0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917.
Controlled water/castle/dense cases remain output workloads,not full gameplay
acceptance. Stage measurements isolate compositor benefit;complete startup/load,
text cost,nominal cadence and physical486SX performance are not proved here.

Both native widths pass seven focused tests:compositor/reference,boundary and
cache performance,DOS root,frame snapshot,snapshot continuation,platform purity,
Windows self-test. The performance matrix covers2048boundary and1198native
frames,source-state preservation,two independently alternating instances,resource
replacement,explicit in-place reset,null workspace/storage,and guarded arrays.
Original DOS compiler/linker passes;four bounded real far-memory cases pass
independent reference equality,null/truncated/full resources,fallback,guard bytes
and unchanged state. Both widths pass13private-host startup/input/Tab/snapshot/
focus/close/shell routes on current products. These are operational proofs and
carry no new ROM certification credit.

DOS product minimum loaded453568bytes,193segments,max64000,DGROUP49456including
2048stack,headroom16080. Runtime cache32768is additional far storage,not DGROUP.
Instrumented normal packs plus cache succeed;after finite workload heap free13104
and largest DOS block1971paragraphs. Another32768trial fails while7680succeeds:
there is no unlimited cache budget.458stack-marked bytes remain in the bounded
lifecycle corpus;all-path/hardware/version qualification remains M4.

Product/test six files,+139/-10;no core/state/snapshot ABI change. Three refreshed
products:429039/319627/328299bytes for16/32/64. Their neutral fingerprints:
- mysmb16.exe: `9a4d3dcec7b5cebfe42db1dab04d83fa91feaa5e234d5d01d73a7a4661fbf44d`.
- mysmb32.exe: `96e4e34a356943bb5c7aba8d41f351e717a1bde96c4c55f9328d60d0601dea80`.
- mysmb64.exe: `79ffaae8618f98df9b7cc8625b6c7aff8deaf4f92d68a286a71214948dda8d4a`.

All local source/probe/frame/log artifacts stay below ignored build/m3-t28-s2.
Scope/expected/actual[],new0;historical1992/1992,local1991/1992nodes and4260/4261
feasible controls(raw4342,infeasible81) unchanged. S2 closes its bounded cache
contract;T28 remains active,S3 receives the next planned optimization chain.

## S3 admission: shared sprite-priority occupancy comparison

Compare behind-background occupancy queries using decoded indices,compact/bounded
CHR representations and a bounded7680-byte opacity bitmap;retain measured joint
memory/performance benefit under the owner-approved contract above. Preserve raw CHR
index-zero transparency before palette mapping,not final color equality. Scope
shared ppu/frame/workspace,root storage binding only if needed,and focused tests;
initial estimate80-200lines,2-4files for occupancy. A compact cache may extend
to150-350lines,4-7files;report the selected representation before code changes. No core or visible PPU/snapshot/text/VGA semantic
change. Uncached and failed-storage paths must remain exact.

Verify independent full frames,behind/in-front overlap,transparent palette alias,
masks,banks,split,flips,clipping,resource/reset lifetime and real far-memory guards.
Compare incremental and cumulative fixed-config costs against frozen S1 and
accepted S2;reject a bitmap if construction/allocation outweighs savings. Product
changes require all three builds/EXEs and focused native/host checks. Scope[],
expectedMatches[],baseline/maximum1992/1992,new0,no node custody transfer.

## S3 P2 admission: S1/S2 memory lifecycle baseline first

Owner approves a bounded memory baseline inside active S3 before selecting its
optimization. Compare retained S1 no-cache and S2 current-cache builds,plus an
explicit optional-cache allocation-failure probe. Read-only DOS MCB/allocator
observations cover initialization,required pixels/snapshot packs,text pack,
graphics/text round trips,save/load transaction callbacks and shutdown. Report
process-owned conventional blocks separately from minimum image bytes and
requested dynamic storage;keep environment/PSP/probe/runtime overhead visible.
Use unmodified installed DOSBox configuration and the original compiler/runtime.
Local probe-only injection must not alter core/game semantics;compare complete
indexed output and snapshots across cache/no-cache/fallback routes. Estimated
2-4test/governance files,no product change or EXE refresh in this audit P.
Historical1992/1992,local1991/1992nodes,4260/4261feasible controls unchanged;
scope/expected/actual[],new0. S3 remains open after the baseline;its occupancy/
compact-cache decision and all-route/hardware limits are separate obligations.

## S3 P2 audit result: bounded conventional-memory lifecycle baseline

The S1/S2 prerequisite audit is complete for the six declared lifecycle phases;
S3 itself remains open for occupancy/compact-cache decisions. Original large-model
compiler/runtime builds four contained probes:S1 retained no-cache root/header/
libraries,S2 current cache,injected optional-cache failure,and real allocation
pressure with the unmodified S2 allocator call. Read-only DOS MCB walking queries
the process PSP and environment;far-heap walking reports allocated/free entries.
File callbacks sample before/after open/read/write/close;unbuffered report output
reduces observer allocation. All probes/resources/frames remain ignored below
build/m3-t28-s3. Temporary compiler path-length failures were resolved using
shorter ignored build temp paths,not a different compiler or product workaround.

| Final bounded probe | Owned conventional peak,including observer/MCB/environment | Minimum external contiguous free block | Peak far-heap live payload |
| --- | --- | --- | --- |
| S1 no cache | 575632bytes(562.141KiB) | 73440bytes | 97436bytes |
| S2 full cache | 610160bytes(595.859KiB) | 38912bytes | 130204bytes |
| S2 injected cache failure | 577408bytes(563.875KiB) | 71664bytes | 97436bytes |

These are measured instrumented-process reservations,not exact pristine-product
minimum requirements. Final probe minimum MZ image sizes are457696/459472/459520;
pristine S1/S2 minima are451968/453568. The MZ image figures exclude PSP and are
not total runtime footprints. Initial S1/S2 primary MCBs are473024/474752bytes,
with160-byte owned environment blocks;primary reservations contain image plus
PSP/runtime reserve/observer,not just touched data. Do not subtract image deltas
to invent a proven product minimum. No fragmented/loaded-only arithmetic can
certify DOS5 or physical486SX fit;those runtime/host bounds remain explicit.
Earlier roughly570KiB loaded-plus-requested estimate omitted reservation and
allocation overhead and is not the actual conventional-memory acceptance value.

Measured initialization sequence:S1/S2 requested pixel61440bytes consumes a
61472-byte auxiliary DOS block;adding snapshot20084consumes20128more. Text15400
adds20848reserved bytes,including allocator slack. After mandatory and text
packs,auxiliary owned storage is102448bytes for both versions. The optional
32768-byte cache adds32800reserved bytes,bringing S2 auxiliary storage to135248.
Primary-image difference1728bytes explains the rest of the34528-byte measured
peak difference. All four explicit production allocations were inventoried:
pixels and snapshot mandatory;text optional;cache optional and attempted after
normal pack initialization. Source file adapters additionally request standard
stdio storage:observed save/load adds512live heap bytes within existing reserves,
without an additional owned DOS block in this corpus.

Declared phases are warmed title,restored populated ground,text switch,return
to graphics,explicit save,and explicit load. S1/S2/failure sample counts41/42/42
include initialization,file transactions and shutdown. Graphical pixel storage,
text storage,snapshot packs and S2 cache coexist through text mode;Tab releases
none. After root shutdown,pixels/cache are free;after main cleanup far-heap live
payload is zero. The runtime retains DOS heap blocks until process exit,so heap
free space and DOS free blocks are distinct. This is allocator behavior,not a
claimed leak. Only actual process termination returns its blocks to DOS.

A fourth unchanged-allocator probe reserves55136DOS bytes after normal packs,
leaving a16KiB target external block. It observes16368bytes largest contiguous
free,cache allocation/validity zero,and completes all six phases,file callbacks
and shutdown. Its raw process-owned peak includes deliberate ballast and is
excluded from the product-peak table. Both pressure and injected failure remain
uncached;normal S2 cache allocates and stays valid across switching/save/load.
All four runs exit0;24 complete61440-byte indexed outputs and four10035-byte
final snapshots match across modes. Installed DOSBox configuration identity is
unchanged,no speed/memory/machine overrides;owned private desktops avoid global
input or foreground disruption. Concurrent runs are memory/correctness probes,
not accepted timing measurements.

Stack marking starts before initialization and retains100patterned bytes in
S1/S2/injected observer paths(with two96-byte marking margins);pressure retains94patterned bytes in its
reported bounded watermark. The observer adds nested stack work,so this is
not a replacement for pristine all-route stack qualification. No stack reduction
is authorized by these results. Snapshots/files were sampled at declared
boundaries;arbitrary gameplay/all runtime internals remain unobserved. A complete
controlled free-memory threshold sweep for pristine products and real DOS/486SX
qualification is not done and must not be inferred from successful launches.

Decision:S2 caching earns no unconditional memory-fit acceptance. Its32KiB cost
and bounded fallback are now quantified;S3 compares compact/no-cache alternatives.
S4 receives the measured125KiB static VGA-plane opportunity;S5 receives graphical/
text coexistence and allocator lifetime findings. S6 must integrate these results
with complete-frame/input budgets before selecting a default. S1/S2 performance
proofs remain scoped and valid;normal playability is a separate unsatisfied gate.
No gameplay/PPU semantics or three product EXEs changed;two governance files
carry this audit. Historical1992/1992,local1991/1992nodes and4260/4261feasible
controls(raw4342,infeasible81),scope/expected/actual[],new0,unchanged. Original
custody and active S3 remain in place;no successor S is admitted by this audit.


## S3 P3 closure: compact raw-index cache and bounded opacity queries

S3 closes its incremental representation/lifetime comparison,not T28 or the
joint final fit/playability gate. Shared compositor caches8192bytes of packed
two-bit indices instead of32768;two bytes encode each eight-pixel row. An
immutable16-entry nibble-spread table bounds cold decode work. Sprite priority
queries raw background index zero directly,without palette lookup or an extra
opacity bitmap. Current scroll/split/masks,banks,OAM,flips and palette values
remain frame inputs. Cache bindings remain per instance;reset/rebind invalidates
immutable CHR identity/size,including explicit reset after in-place test mutation.
Null/short resources retain bounded zero reads;allocation failure uses the
unchanged uncached path. No core routine,PPU storage or snapshot ABI changes.

DOS composition attempts the optional cache only after required packs. It
first uses the primary-block near-heap reserve,then far heap;the root records
allocation provenance and matches _nmalloc/_nfree or _fmalloc/_ffree explicitly.
An automatic review rejected an earlier unmatched near/far release proposal;
no rejected change was applied. The matched ownership alternative is implemented
and verified. Windows caller storage shrinks through the same shared size constant.
No global mutable cache or platform gameplay policy is introduced.

| Candidate | Disposition and paired result |
| --- | --- |
| Packed8KiB naive decoder | Rejected in favor of the same-size faster spread/row-staged decoder. |
| Packed16KiB | Rejected:more memory and slower cold/warm costs than the8KiB alternative. |
| Per-frame7680-byte opacity bitmap | Rejected:extra memory and substantially slower corpus output,including dense sprites. |
| Packed8KiB,staged row reads,direct raw opacity | Retained incremental S3 default;S6 must qualify the cumulative product against both fit and playability gates. |

Original compiler/runtime and unchanged installed DOSBox configuration are
used. Two sequential final runs have identical PIT costs for the paired stages;
all six61440-byte buffers and10035-byte snapshots equal retained S1/S2 colored
fixtures. Configuration SHA256 remains
0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917.
Private-desktop normal SDL avoids foreground input;no emulator override is used.

| Paired scene | S1 PPU ticks | S2 PPU ticks | S3 PPU ticks | S2 total ticks | S3 total ticks |
| --- | ---: | ---: | ---: | ---: | ---: |
| First colored title,cold | 1195922 | 1511516 | 1252314 | 2712451 | 2453373 |
| Restored ground | 1195923 | 1009609 | 1071430 | 8411815 | 8474104 |
| Water output fixture | 1330366 | 1142572 | 1229956 | 2331035 | 2418417 |
| Castle output fixture | 1330367 | 1142567 | 1229956 | 2331028 | 2418417 |
| Dense64-sprite output fixture | 1461802 | 1276422 | 1310047 | 2464883 | 2498507 |

A PIT tick uses1193182Hz nominal conversion. S3 water/castle/dense composed
PPU+stretch+device outputs cost about2.027/2.027/2.094seconds in this fixed
probe environment,versus1.954/1.954/2.066seconds for S2. This is not playable
cadence acceptance. Cold total is9.551percent shorter;restored-ground total
is0.740percent longer and includes root/snapshot bookkeeping. The output-only
water/castle/dense totals are3.749/3.749/1.364percent longer than S2;their PPU
stages alone are7.648/7.648/2.634percent longer. Warm ground PPU is6.123percent
longer. S3 remains faster than S1 warm PPU. Do not extrapolate these isolated
output fixtures to original-game cadence,input responsiveness or486SX speed.
Normal cadence/input and cumulative acceptance remain S6/M4 obligations.

| Current lifetime route | Owned conventional peak | Minimum external DOS contiguous block | Peak live far / near payload |
| --- | ---: | ---: | ---: |
| Normal matched near-first allocation | 578176bytes | 70896bytes | 97436 /8192bytes |
| Both cache allocators injected to fail | 577728bytes | 71344bytes | 97436 /0bytes |
| Near reserve exhausted,real far fallback | 586432bytes,includes test near ballast | 62640bytes | 105628 /8192bytes,test ballast |
| Both heaps under real pressure | 648064bytes,includes deliberate ballast | 1008bytes | 97436 /8192bytes,test ballast |

Normal primary block475568bytes,environment160 and auxiliary reservations
102448bytes include instrumentation. Compared with bounded S2 peak610160,
normal S3 is31984bytes lower;observer/layout differences prevent treating that
as an exact pristine saving. Cache storage itself saves24576bytes;using primary
reserve avoids an extra cache DOS block in the normal observed route. Compared
with S1 peak575632,S3 is2544bytes higher. Required pixel/snapshot/text packs
remain61440/20084/15400bytes;no mandatory storage is displaced. New near-heap
walking distinguishes payload from the primary reserve already included in MCB
counts;the earlier far-only payload table was not a total-live-payload claim.

Four routes cover warmed title,restored ground,text,graphics,save/load and
shutdown. Normal/far routes allocate valid cache;injected and genuine pressure
routes remain uncached. Each matches all six complete outputs and final snapshot.
Real pressure reserves the near heap as well as leaving only1008bytes external;
external pressure alone is insufficient because runtime allocation can reuse
primary reserves. Final near/far live counts are zero after matching frees and
ballast cleanup;CRT retains free blocks until exit,as already documented.
Stack observer marks78/100/76/76bytes untouched,with previous marking margins;
no stack reduction or pristine/all-route stack certification follows.

Native x86/x64 each pass seven focused tests,including2048 boundary fixtures,
1198 native-route comparisons,two instances/reset/resource fallback/guards and
four explicit palette-alias/behind/front/left-mask priority cases. Each actual
Windows product passes13 private-host startup/input/Tab/snapshot/focus/close
regression groups. Original DOS far-pointer ABI probe passes four complete
frames,null/truncated/full/fallback,guards and unchanged state. Current original
DOS product compiles/links;DGROUP49472,max segment64000,stack2048 and minimum
loaded image453824bytes are structural checks,not total-runtime requirements.

Three refreshed owner-authorized tracked artifacts are429295/319627/328299bytes:

- DOS16 SHA256 ed8725eb0a9bb56040a1ee522ecde89091ab336214e27cbad3ecf2375413ff14.
- Win32 SHA256 4629d477cb4ac7df71ea4a28858d9540f1c0599c8abadfd00167262b32d11a01.
- x64 SHA256 c9a9fa965bb23f16fda27be1b42147b36bddb12d09a47a02cfc6708690fc7d3d.

Owner exception applies only to these existing tracked EXEs,not new protected
imports or release permission. All compiler/probe/raw-frame/snapshot/report
outputs stay ignored under build/m3-t28-s3. Five product/test files,+84/-33;
shared frame representation and root allocation ownership are the only changes.
Source sweep covers all decoded-row/sprite/opacity consumers,workspace bindings,
mandatory/optional allocation ordering and shutdown provenance. Every identified
hit is updated or unchanged by contract;no unresolved scoped output difference.
Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81) unchanged;scope/expected/actual[],new0,no custody transfer.

S3 bounded comparison is complete;pristine minimum-free threshold,full-stack,
input/cadence and real DOS/486SX qualification are not. S4 receives full128000-byte
VGA-plane storage and repeated-row conversion;S5 retains pack-lifetime/reuse
analysis;S6 receives the cumulative memory/playability default decision.

## S4 admission: exact stretch-row reuse and bounded VGA storage

M3 T28 S4 P1 is admitted automatically under the owner's ongoing execution
mandate. Owners are platform/vga frame conversion,DOS devices/main composition
and corresponding focused tests/build membership. Estimate4-7 product/test/build
files,150-350 changed lines. No original game or PPU state/semantics changes.

Compare four retained32000-byte planes with single-plane,scanline or small-batch
scratch and repeated-row reuse. Every256x240 source coordinate,full640x400
borderless scanout,plane/address selection,palette and presenter mode lifetime
must remain identical. Keep complete output;no frame/tick/input suppression.
Measure incremental/cumulative memory and complete output costs in the unchanged
runtime before selecting an alternative. Specialized transfers require actual
far/segment guards and readback,not just native arithmetic tests.

Entry is the const indexed frame;exit is complete VGA device submission. S3 is
the accepted representation dependency;S5 consumes resulting lifetime/storage
facts. Scope/expected/actual ROM labels[];historical1992/1992,local1991/1992 and
4260/4261feasible controls unchanged,maximum1992/1992,new0. Original receiving
node custodians are retained. Verification combines independent128000-byte
packed mapping equality,native/far boundaries,actual plane readback/mode restore,
focused tests/platform purity and three products for each product-code P.
Exit requires a documented accepted/rejected bounded-storage and row-reuse
choice with exact output,state and measured memory/time evidence. T28 remains open.


## S4 P1 checkpoint: single-plane and duplicate-row prototype

Contained original-compiler prototype compares one32000-byte plane with the
four128000-byte production planes. Prototype guard bytes make scratch32002bytes;
static-storage difference is95998bytes. Convert a plane,submit it to its selected
A000 plane,then reuse the scratch. Repeated source rows copy the previous80-byte
output row;every source-coordinate formula and palette-index mask is retained.
No product source or executable changes in P1;S3 products remain the published
baseline. S4 stays open for formal integration,lifetime and peak proof.

Independent native comparison checks all128000packed bytes against explicit
x*4/5,y*3/5mapping and both guards. Actual DOS prototype checks far guards during
every submission and reads back all four A000planes after the dense fixture;
128000hardware bytes equal the independently calculated expected frame. Six
complete61440-byte source buffers and10035-byte final snapshot match S3/S1.
Text/graphics fixture phases use existing devices and input/ticks;no gameplay
shortcut is promoted. Probe/link outputs remain ignored under build/m3-t28-s4.

| Fixed-config probe | S3 stretch ticks | Single-plane/repeated-row stretch ticks | S3 complete output ticks | Prototype complete output ticks |
| --- | ---: | ---: | ---: | ---: |
| Water | 1162215 | 725490 | 2418417 | 1982772 |
| Castle | 1162206 | 725483 | 2418417 | 1982775 |
| Dense sprites | 1162213 | 725497 | 2498507 | 2062862 |

Conversion is about37.58percent shorter;complete output about18.01/18.01/
17.44percent shorter. Four plane selections/bulk submissions remain. PIT values
include instrumentation;roughly1.662/1.662/1.729seconds output costs still fail
nominal playability,so this is an opportunity result,not final performance
acceptance. First title total17.76percent shorter;restored-ground root total
5.15percent shorter,including snapshot/root work. Configuration hash matches S3;
normal SDL/private desktop uses no CPU/memory/render override or foreground input.

Paired probe minimum MZ loaded images458939/363627bytes exclude PSP,dynamic
allocations and environment. Difference95312bytes includes prototype code/header
layout;it is not a measured pristine peak saving. The formal P must repeat MCB/
near/far/stack lifecycle sampling,contiguous fit and fallback under current
product composition,then refresh all three EXEs. Device mode restoration and
all-path source/mode lifetime need explicit integration tests before closure.
Row/batch alternatives must be compared or rejected with a cost justification;
no general dirty-frame policy is introduced by this bounded row reuse.

Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81) unchanged;scope/expected/actual[],new0. Ledger S4 remains active.
P1 retains a measured candidate and defined remaining obligations,not S/T closure.


## S4 P2 closure: bounded batch storage and exact repeated rows

S4 closes its incremental neutral video conversion/submission scope. Production
DOS now uses1280bytes for16rows,not four128000-byte planes. All100batches are
converted and submitted for each complete frame;four physical VGA planes and
full borderless640x400scanout remain. Adjacent repeated source rows reuse the
previous80bytes within a batch;the first row reconstructs from immutable pixels.
No previous-batch contents or cross-frame cache is needed. Generic row-range
conversion and submission reject out-of-range planes/rows before writing.
Existing complete-frame APIs remain supported through the same coordinate owner.

Six product/test files,+71/-34. Only neutral VGA conversion,DOS main/device
submission and mapping tests change. Core,PPU state/compositor,snapshot bytes,
input,ticks,audio,text artwork and mode selection are unchanged. Maximum source
address remains61439;A000ranges end at32000per plane. All fixed16row chunks divide
400exactly. Independent tests also exercise1/7/16/63/400row groups,partial final
batches,all128000packed coordinates,guard bytes and invalid plane/range rejection.

| Storage alternative | Scratch | Decision |
| --- | ---: | --- |
| Four complete planes | 128000bytes | Replaced;unnecessary simultaneous conventional storage. |
| One complete plane | 32000bytes | Valid faster alternative;not selected because bounded batch saves30720more bytes for under1.74percent measured complete-output cost. |
| One row | 80bytes | Rejected for current default:aggregate output about9.96-10.37percent slower than single-plane;extra per-row calls/selection/division outweigh its modest additional saving. |
| Sixteen rows | 1280bytes | Selected incremental default;126720static bytes saved versus S3,no extra heap allocation. Final playability selection still requires S6/M4. |

Prototype per-row internal timing was discarded:1600stamp pairs add material
observer work and expose isolated unsigned-clock underflow samples. The comparison
uses aggregate-only row timing and paired complete-output costs. This finding is
received by S6's clock/input/cadence qualification;it is not a silent repair of
production pacing. No emulator setting or original game logic changed.

| Fixed-config scene | S3 complete-output ticks | Final16row output ticks | Difference |
| --- | ---: | ---: | ---: |
| Water | 2418417 | 2017248 | -16.588percent |
| Castle | 2418417 | 2017242 | -16.588percent |
| Dense sprites | 2498507 | 2097339 | -16.056percent |

Two sequential final runs have identical aggregate costs. Water/castle/dense
output costs about1.691/1.691/1.758seconds in the unchanged fixed probe runtime;
these are not nominal cadence or486SX playability acceptance. Relative to the
single-plane candidate,final output is1.737/1.737/1.670percent longer. First-title
total is16.352percent shorter than S3;restored-ground root total4.740percent
shorter,including snapshot/root bookkeeping. Stage3 now aggregates conversion
and device submission;do not compare it directly with S3's conversion-only stage.

Final timing probe initially closed its report before writing the restore footer;
this harness-only lifetime fault was corrected and both final runs repeated.
No product has that report operation. Current final receipts contain before3/
after3mode restoration,complete source/plane outputs and matching snapshots.
Installed configuration SHA256 is unchanged from S3,normal SDL on private desktops,
without foreground input or CPU/machine/memory/render overrides.

| Final DOS lifecycle route | Owned conventional peak | Minimum external contiguous block | Live payload peak |
| --- | ---: | ---: | --- |
| Normal near-cache path | 452432bytes | 196640bytes | far97436,near8192bytes |
| Injected optional-cache failure | 451952bytes | 197120bytes | far97436,no cache |
| Real external/near pressure | 648064bytes,includes ballast | 1008bytes | far97436,near8192test ballast observed |

Normal primary349824,environment160,auxiliary102448bytes include probe overhead.
Compared with S3 normal578176,the instrumented peak is125744bytes lower;compared
with S1/S2 peaks575632/610160,it is123200/157728lower. These are bounded probe
reservations,not a claimed pristine minimum requirement. No-cache fallback and
real pressure both complete the declared phases. Every route covers title,
restored ground,text,graphics,save/load and shutdown;each reads five complete
four-plane VGA outputs(640000bytes),compares six source frames and10035-byte
snapshot. Graphics/text BIOS modes are19/3,then initial mode3is restored at exit.
Final live far payload is zero in all routes;near zero where walking is present.
Injected-failure probe has no near allocation/walker,not an independently
observed near-heap census. Stack observer marks76/98/74bytes untouched,with
existing margins;no stack reduction or all-route qualification follows.

Current original DOS16 product is302927bytes,minimum MZ loaded image327440,
DGROUP49456,stack2048,max segment32768. Compared with S3 image453824,this saves
126384loaded bytes;MZ image excludes dynamic heap,PSP and environment. The actual
minimum free-memory threshold,full-route stacks and DOS-version/physical486SX
fit remain S6/M4 obligations. Windows targets each pass eight focused tests,
including2048boundary/1198native comparisons and the new batch mapper. Thirteen
actual private-host launch/input/Tab/snapshot/focus/close groups pass per width;
final Windows binaries equal the tested hashes because VGA device work is DOS-only.

Three product build targets are current;all three owner-authorized asset paths
are refreshed. DOS changes,Windows binary identities remain unchanged:

- mysmb16.exe: 302927bytes,SHA256 3b0d82ad40e3ba3621f35f9e9cf42a3359367b64e3284d94761536c92408b67e.
- mysmb32.exe: 319627bytes,SHA256 4629d477cb4ac7df71ea4a28858d9540f1c0599c8abadfd00167262b32d11a01.
- mysmb64.exe: 328299bytes,SHA256 c9a9fa965bb23f16fda27be1b42147b36bddb12d09a47a02cfc6708690fc7d3d.

Source sweep covers every production frame/page builder,plane submitter and
static page allocation;DOS main receives bounded batches,legacy complete-frame
consumers/tests retain the shared row-range owner. No named scoped output or
lifetime difference remains. Local raw outputs/probes/resources remain ignored
under build/m3-t28-s4 until S6 consumes them. Historical1992/1992,local1991/1992
nodes,4260/4261feasible controls(raw4342,infeasible81),scope/expected/actual[],new0.
No node custody transfer,new ROM claim or M2/M4 certificate. S4 is closed;T28
remains open and S5 is admitted below. The observed clock clause is assigned S6.

## S5 admission: unchanged-region cost and workspace lifetime decision

M3 T28 S5 P1 is automatically admitted under ongoing owner execution approval.
First inventory current pixel,text,snapshot,cache and VGA lifetimes after S4;
assess whether presentation workspaces can safely share storage without changing
mode-switch/restore/failure behavior. Assess dirty-region/frame reuse only with
all PPU/resource/mode/restore invalidation inputs and its own memory/time cost.
No optimization is required merely because it was listed;retain complete redraw
if cache costs outweigh benefits. Snapshot integrity,transaction staging and
last-running recovery guarantees cannot be weakened to reclaim space.

Owners are DOS composition/workspace lifetimes and read-only compositor cache
contracts;IO/snapshot owners participate only if their exact neutral contracts
require an admitted change. Initial audit0product lines;possible implementation
estimate3-5files,80-200changed lines,reported before code. No core/PPU-state,
snapshot schema,original input/tick/audio or DOSBox setting changes. Scope and
expected/actual ROM labels[],new0,maximum1992/1992;original receiving custodians
remain. S4 output/storage is the predecessor;S6 receives cumulative choice,
minimum-fit/stack/cadence/input and the observed clock sampling clause.

S5 exit requires an explicit accepted/rejected/deferred reuse choice,complete
output/state/snapshot and lifecycle equality,paired peak-memory/time costs and
failure recovery. Any product-code P builds/tests/refreshed three EXEs;pure audit
does not repackage. Neither candidate savings nor fast isolated stages establish
whole-product fit/playability. T28 still needs S5/S6 and all named dispositions.


## S5 P1 closure: exclusive presenter storage and measured reuse decisions

S5 accepts DOS text workspace/frame reuse of the first15400bytes of the mandatory
61440-byte pixel allocation. Compile-time extent checking and synchronous
presenters establish one active view;only the root frees this allocation.
Graphics fully rebuilds on return from text. Source sweep covers DOS main/root,
text maps/visited/queues/claims,compositor/device callbacks and all snapshot
consumers. No persistent text state depends on previous pixel bytes.

Snapshot staging/result and last-running recovery have overlapping lifetimes
and atomic failure obligations;keep the20084-byte transaction store and embedded
capture/recovery buffers independent. No core,PPU state,compositor algorithm,
snapshot bytes,text artwork,input,tick or audio changes. Source/test3files,+66/-4.
VGA1280-byte scratch and optional8KiB raw CHR cache retain existing ownership.

Reject unchanged-region/frame caching for this delivery:an exact key needs2048
nametable,32palette,256visible OAM,six visible control/scroll/split bytes and
resource identity/size,about2.4KiB plus tracking. Hash-only equality is insufficient.
Resource rebinding/content/lifetime,all visible key fields,mode,restore and text
alias writes require invalidation. A full output mirror adds61440/128000bytes.
A scoped1198-frame native route has225equal-key frames,including138of1080game
frames;this is eligibility,not general hit rate or speed proof. Most game frames
still redraw,and hits still need VGA submission. Static pause eligibility does
not justify additional persistent storage without measured whole-output gain.
Retain full redraw under the owner's memory priority;no hidden deferred cache.

| Paired actual DOS route | Conventional owned peak | Minimum external contiguous block | Live far peak | Untouched stack pattern |
| --- | ---: | ---: | ---: | ---: |
| Separate-storage baseline | 452656bytes | 196416bytes | 97436bytes | 76bytes |
| Reused storage,normal cache | 436240bytes | 212832bytes | 82036bytes | 76bytes |
| Reused storage,injected cache failure | 435760bytes | 213312bytes | 82036bytes | 98bytes |
| Reused storage,real pressure | 648608bytes,includes ballast | 464bytes | 82036bytes | 74bytes |

Normal reservation falls16416bytes,live payload15400bytes. Baseline/candidate
carry identical text-readback instrumentation. Retained S1/S2 peaks575632/610160
are139392/173920bytes higher,with source/instrumentation limits;not pristine
minimum launch requirements. Pressure includes ballast and a later stdio block.
All routes free live far payload,near where walking is present,and restore BIOS
mode3. CRT free reservations persist until process exit;stack is not reduced.

Every route matches five active indexed graphics frames,640000bytes of actual
VGA-plane readback,8000bytes of B800text,12000bytes of authored cells and10035
snapshot bytes against the separate-storage baseline. Inactive FRAME2pixel bytes
are intentionally overwritten by text and are not a valid graphical output.
Both native widths compare1198borrowed text/rebuilt pixel frames,extent guards
and unchanged game state. Missing-resource text failure plus rejected mode reset
submits nothing;subsequent successful reset reconstructs all pixels,matching
baseline RAM,frame number,frame output and audio submissions.

Two paired unchanged-config,normal-SDL private-desktop runs produce identical
complete water/castle/dense output costs2017248/2017242/2097339PIT ticks;restored
root/load8072470and text1105453also equal. Title differs by one tick only.
These long diagnostic costs are not playable cadence;clock sampling,input tail,
minimum-free thresholds and target486SX qualification remain explicit S6/M4 work.
No DOSBox CPU/memory/machine/render settings changed. Both widths pass8focused
tests;retained13actual Windows host groups remain applicable to identical rebuilt
binary hashes. Original DOS product302879bytes,minimum MZ327392,DGROUP49456,
stack2048,max segment32768;MZ excludes heaps,PSP and environment.

All three owner-authorized assets refreshed:

- mysmb16.exe:302879bytes,SHA256 3d49eea9198359d4a16d2651b260ec42762acd5b48d5ca17c17bf035d729a905.
- mysmb32.exe:319627bytes,SHA256 4629d477cb4ac7df71ea4a28858d9540f1c0599c8abadfd00167262b32d11a01.
- mysmb64.exe:328299bytes,SHA256 c9a9fa965bb23f16fda27be1b42147b36bddb12d09a47a02cfc6708690fc7d3d.

Local receipts stay under ignored build/m3-t28-s5 until S6. No scoped output or
lifetime difference remains. Scope/expected/actual[],new0,historical1992/1992,
local1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81),custodians
unchanged. S5 closes incremental reuse,not joint T28 fit/playability or M2/M4.

## S6 admission: cumulative memory fit and complete-route performance

M3 T28 S6 P1 automatically admits under ongoing execution approval. Reconcile
S1/S2 baseline allocations and S3-S5 choices in one cumulative census,without
redoing accepted unrelated audits. Verify actual product minimum-free launch/
runtime fit,required61440/20084packs,optional8192cache,borrowed15400text view,
1280scratch,MCB/near/far/stack ownership,and startup,gameplay,transition,pause,
Tab,snapshot and exit lifetimes. Separate image,heaps,allocator,PSP/environment
and pressure ballast. Audit original PIT phase/underflow before timing claims;
declare normal cadence/input budgets and assess complete cost/tails.

Initial audit0product lines;possible platform timing/probe/test corrections
3-6files,80-250lines,reported before code. No original ROM tick/core/PPU/snapshot
semantic or emulator setting changes. Cumulative exact output/state/snapshot,
failure checks,both widths and original DOS16 remain mandatory;product changes
refresh three EXEs. Scope/expected/actual[],new0,maximum1992/1992,custody retained.
S6/T28 exit requires all six dispositions,measured fit and playable-budget proof;
a failed required clause keeps them open. Physical486SX/DOS versions remain M4.


## S6 P1 checkpoint: timer reload sampling and actual-product fit boundary

S6/T28 remain open. One product source file changes,+12/-6:the DOS device timer
recaptures a complete BIOS/PIT pair when read-back yields zero count,up to four
attempts. No PIT frequency,IRQ vector,game tick,core/PPU or input/audio semantics
change. It bounds interrupt-disabled work rather than looping forever. This
addresses an observed sampled reload boundary,not every hardware timer fault.
If all four samples are zero,the last bounded sample remains the result;the
normal test never exhausts retries,so stalled-device behavior is not qualified.

The original50,000-sample actual DOS probe has one backward jump:BIOS927683,
status182,pending0,count254/phase32641to count0/phase0,delta-32641. This is a
concrete missing sampling condition in prior short-operation timing evidence.
A retry prototype has0backwards in50,000samples;expanded250,000samples observes
10zero recaptures,0retry exhaustion,0backwards,max forward166PIT ticks. These
samples prove the observed mitigation under unchanged configured DOSBox,not
universal monotonicity. Integer pure phase tests remain exhaustive over65536
phases for BIOS mode2/mode3;the decoder itself is unchanged. The read-back and
mode3 hardware model is cross-checked against the Intel8254datasheet,public
research reference only,no implementation import:
[original Intel document](https://www.cs.umb.edu/cs341/Intel8254/I8254PIT.pdf).

Both native widths pass10focused tests including clock,pacing,presentation,
VGA,root/failure recovery,frame/snapshot continuation,platform purity and product
self-test. Three actual DOS lifecycle routes match the paired S5reference:
each640000VGA bytes,five active indexed frames,8000text hardware bytes,12000text
cell bytes and10035snapshot bytes. Normal owned peak436288,minimum external
contiguous212784,far live82036;cache-failure435808/213264/82036. Pressure peak
648608includes ballast,remaining contiguous464;all live payload frees and initial
mode3returns. Stack untouched76/98/74with unchanged margins,no stack shrink.

The cumulative retained memory census now includes S1/S2 instead of only the
latest optimization. Comparable bounded normal owned peaks are575632(S1),
610160(S2),578176(S3),452432(S4),436240(S5),436288(S6instrumented). S1/S2 live far
97436/130204includes the original independent15400text pack;S2's decoded cache
adds32768far bytes. S3replaces it with8192near bytes;S4removes126720static VGA
scratch bytes;S5eliminates15400live text bytes and16416paired reservation bytes.
Image/probe differences prevent calling these a pristine all-route minimum.
Static buffers and stack count once in the primary image;VGA hardware memory
is excluded. Snapshot transaction/recovery is retained,CRT block slack remains
owned after free until process exit,and pressure ballast is reported separately.

A separately compiled small DOS loader reserves a conventional-memory ballast
block,then invokes the actual published EXE through DOS EXEC. It never patches
child memory/code or changes emulator settings. Normal SDL,private desktop,
finite public-ABI key script and contained BMPs exercise load,movement,Tab both
directions,save and Esc. Original loader/compiler/runtime remain;local probe
and all owner-resource outputs stay below ignored build/m3-t28-s6.

| Requested remaining KiB | Observed largest block before EXEC | Actual child result | Scoped outcome |
| --- | ---: | ---: | --- |
| 448 | 458736bytes | 0 | Ground/text/graphics captures,save,Esc successful |
| 416 | 425968bytes | 0 | Same complete scoped actual-product route successful |
| 415 | 424944bytes | 1 | DOS EXEC succeeds,product returns startup failure |
| 414 | 423920bytes | 1 | Startup failure |
| 412 | 421872bytes | 1 | Startup failure |
| 410 | 419824bytes | 1 | Startup failure |
| 408 | 417776bytes | 1 | Startup failure |

This bounds the tested caller-free launch/route threshold between424944and425968
bytes with this environment/loader. It includes child environment/PSP and CRT
startup behavior;it is not the327424-byte minimum MZ image and not a statement
that all DOS drivers/versions or every game route fit in416KiB. Lower-budget
failure is not an out-of-memory emulator crash. Ground/text/graphics captures
and scripted input/snapshot responses prove operation,not ROM frame equivalence
or playable input latency. The latter remain unmet integrated S6 clauses.

Three owner-authorized products refreshed,Windows hashes retain prior host
receipt applicability:

- mysmb16.exe:302911bytes,SHA256 b3d291cb2f22246a802e65e492ba1dabd2d125bf2a337cb0cb3b7a1c88d0bc30.
- mysmb32.exe:319627bytes,SHA256 4629d477cb4ac7df71ea4a28858d9540f1c0599c8abadfd00167262b32d11a01.
- mysmb64.exe:328299bytes,SHA256 c9a9fa965bb23f16fda27be1b42147b36bddb12d09a47a02cfc6708690fc7d3d.

DOS MZ327424,DGROUP49456,stack2048,max segment32768. Scope/expected/actual[],
new0,historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),custody unchanged. Local snapshot/planes and timer receipts are
retained through S6. This P does not close S6 or declare fit/playability jointly
accepted;normal cadence/input-tail,full-route stack/fit and remaining opportunity
choices still need integrated evidence. No M2/M4 certificate.

## S6 P2 next work: complete-output cost and original-toolchain candidates

Continue the same S. Inspect actual OpenNT16 transfer/compositor cost and missing
cadence/input budgets;no emulator adjustments or original ROM changes. An ignored
original-compiler /O1candidate fails during the contract probe with its internal
buffer/out-of-memory diagnostic,even with short local compiler/source/temp paths.
All copied compiler helpers retain original bytes and are local toolchain
experiments,not a new dependency or adopted build. No optimized product or gain
is claimed. Investigate the generated bulk-transfer path and bounded read-only
renderer costs before selecting a verified size/speed candidate. Report scope/
size before any next production edit;retain current products as tested baseline.

## S6 P2 checkpoint: exact grouped VGA coordinates and evidence correction

S6/T28 stay open. One product source file,platform VGA row conversion,changes
+14/-6. The exact horizontal expression floor((4*column+plane)*4/5) has a
five-output/sixteen-source period. Four five-byte constant offset rows replace
80per-dot recurrence operations with16groups. The20-byte constant and bounded
local indices add no heap or full-frame storage. Vertical mapping,partial batch
bounds,source-index masking,plane order,640x400 scanout and the1280-byte scratch
stay unchanged. Similar-issue review covers all four plane offsets,first/last
source pixels,arbitrary row batches and repeated-row reuse;no other converter
or device/core/PPU-state/snapshot change is required.

Independent native mapping sweeps all128000coordinates and guarded batches
1/7/16/63/400,invalid bounds and high source bits. Both x86/x64 pass10focused
tests. Existing2048boundary/1198native presentation checks and platform purity
pass. Original OpenNT16/historical DOS runtime builds the full actual product;
no /O1compiler experiment is adopted. Windows product bytes/hashes are unchanged,
so the accepted13private-host groups per width retain their dependency binding.

Three fixed-config DOS normal/cache-failure/pressure routes each match five
active61440-byte indexed frames,640000hardware VGA-plane bytes,8000hardware text
bytes,12000neutral text-cell bytes and10035snapshot bytes. Initial mode3returns,
all live payload allocations are released. Inactive text-overwritten bitmap
storage is not falsely compared as an active graphics frame. Normal owned probe
peak436448(+160versus P1),minimum external contiguous212624,far payload82036.
Cache-failure435952/213120/82036;pressure648608includes ballast and leaves464bytes.
Stack untouched76/98/74retains the same narrow observation,not all-route safety.
These are instrumented reservations,not the actual product's measured peak.

Separate diagnostic per-batch stamps show conversion about42.11percent shorter,
device transfer unchanged;observer overhead prevents treating this split as the
acceptance timing. Two paired aggregate fixed-config runs have identical scoped
outputs/snapshots. Title complete step15.724percent shorter,load step3.997percent
shorter;water/castle/dense output-only steps15.996/15.996/15.386percent shorter.
Text differs by two PIT ticks. These are output-only fixture costs,not measured
normal gameplay FPS or input latency. Nominal output time remains about1.42-1.49
seconds in those configured probes;playable cadence is still unmet. Configuration,
normal SDL and private-desktop isolation remain unchanged.

The actual newly built product exits0at416/417KiBcaller-free budgets:observed
largest blocks425968/426992bytes,loader DOS EXEC/result0. Directly inspected
captures prove title text/graphics switching and exit,but the early capture is
blank and later captures remain title screens. This corrects the prior P1 claim
of a completed load/movement/save route:injected key/capture events and a save
hash are insufficient proof of those game actions. The416save is unchanged from
the seed;417differs,but that alone does not prove a successful intended route.
P1 startup-failure results remain receipts;no new all-route fit or exact actual
resident-memory claim follows. P3 must observe the formal product's owned memory
blocks and a completed game route,with finite bounds and unchanged settings.

All three owner-authorized existing products refreshed and manifest checked:

- mysmb16.exe:303091bytes,SHA256 0074d4cdec81e34933c000d53465ca9e711ad6ce23a051b241a3fcf035d6f11f.
- mysmb32.exe:319627bytes,SHA256 4629d477cb4ac7df71ea4a28858d9540f1c0599c8abadfd00167262b32d11a01.
- mysmb64.exe:328299bytes,SHA256 c9a9fa965bb23f16fda27be1b42147b36bddb12d09a47a02cfc6708690fc7d3d.

Minimum MZ load327600(+176),DGROUP49472,headroom16064,stack2048,max segment32768.
No dynamic heap/environment/PSP is included in this MZ figure. All local routes,
raw images and traces remain ignored under build/m3-t28-s6. Scope/expected/actual[],
new0,historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),custody unchanged. No M2 or hardware/DOS-version qualification.

## S6 P3 continuation: actual resident occupancy and redundant cache reads

The owner clarifies actual runtime DOS memory is required,not EXE file size or
caller-free startup threshold. Measure the actual product's primary/environment/
auxiliary blocks separately from instrumentation and VGA hardware;report sampled
occupancy versus proven peak honestly. Reconcile primary image code/static data/
resources with the link map before selecting any further storage tradeoff.

A contained original-compiler candidate suppresses two raw CHR reads only when
the already-valid decoded cache supplies all pixels. One fixed-config trial
matches all five active frames,twenty hardware planes and the final snapshot;
PPU cost9.562-11.692percent shorter,output-only complete steps7.059-7.393percent
shorter versus P2. This is a candidate,not a production change or accepted gain.
Before adoption,report scope/size,review cached/uncached partial tiles,bounds and
resource invalidation,repeat paired timing and refresh all three products after
focused tests. No core ROM routine/state/PPU semantic change or new cache storage.
Actual-product occupancy/game route and cadence/input clauses remain mandatory.

## S6 P3 audit: formal-product resident blocks and loaded-image decomposition

The owner asks for occupied DOS conventional RAM,not disk file size or caller-free
launch budget. A separately compiled original-toolchain loader observes the
unchanged actual product through a bounded BIOS timer callback. It follows the
MCB chain,identifies the child primary owner/name,reads its environment binding,
and sums only blocks owned by that PSP. Each block includes its16-byte MCB;the
primary includes PSP. Parent/ballast/observer blocks and VGA hardware are excluded.
The observer performs no DOS,file,heap or console call inside the callback;it
chains the prior callback and restores its vector after EXEC returns. It has128
bounded change records,512-block traversal bounds,and reports invalid chains or
dropped records. This is sampled occupancy,not an allocation-event-exhaustive
proof of continuous peak;observer interrupt cost is not performance acceptance.

The product SHA256 remains the P2published identity. Unchanged installed DOSBox
configuration,normal SDL and private desktop are verified. The448KiBbudget title/
Tab/exit route has997timer samples,one changed occupancy record,no bad chains or
drops. Actual owned425680bytes comprises343920primary,160environment,81600auxiliary
in four blocks. A separately scripted post-startup load/game/Tab/save/exit route
has2043samples,two records,no bad chains/drops. Maximum observed430144bytes is
343920primary+160environment+86064auxiliary:an extra4464auxiliary bytes appears.
This is about420.1KiB,versus415.7KiBtitle occupancy,and excludes the observer.
CRT owned reservation is not synonymous with live useful payload;free heap space
retained inside those blocks still occupies DOS memory.

Reviewed game graphics/text/graphics captures show the loaded1-1scene rather
than title. The saved10035-byte file changes from the seed,frame7465to7512,with
startup phase4preserved. This proves scoped load/advance/presentation/save/exit
operation,not ROM equivalence,input-tail/playable cadence or all-game peak. Do
not extrapolate observed420.1KiBto every DOS environment/route or label the earlier
416KiBcaller-free startup threshold as a runtime-occupation measurement.

The actual linked minimum image is327600bytes,distinct from resident primary
343920bytes. Segment-class sum327492plus108bytes alignment/MZ paragraph reserve
reconciles it exactly:

| Linked category | Bytes | Accounting |
| --- | ---: | --- |
| Machine code | 243977 | All linked CODE segments |
| Owner-local PRG data | 32768 | Embedded raw data source,not a6502 runtime |
| VGA row scratch | 1280 | Count once in FAR_DATA |
| Initialized data/constants/runtime messages | 16275 | DATA/CONST/BEGDATA/MSG |
| Uninitialized static state | 31144 | BSS,includes DOS root |
| Stack | 2048 | Retained,not reduced |
| Alignment/minimum-load reserve | 108 | Difference to actual MZ minimum |

Local object metadata reconciles machine-code owners:core182217,text27110,
platform10200,io5516,ppu4952,app2929bytes;11050bytes in the combined legacy_TEXT
segment remain attributed only as library/startup,with three inter-object padding
bytes in combined segments. Do not mislabel all243977bytes as translated gameplay.
Initialized data includes8192CHR and322title bytes;unattributed remaining bytes
must not be called dispensable. BSS includes the30182-byte DOS root;its two
snapshot objects are real storage alongside live game/observer/output state.
The normal primary343920equals linked DGROUP origin278112+65536+256PSP+16MCB.
Thus this route reserves the full64KiBnear segment even though the linked DGROUP
uses49472. Removing BSS alone can reduce minimum MZ load without reducing this
observed primary reservation. A scratch reuse candidate must measure actual
reservation,not claim its sizeof as runtime savings;safe CRT heap bounds cannot
be bypassed by blindly shrinking the primary DOS block. The16320bytes above MZ
minimum include PSP/MCB/runtime reserve,not another whole framebuffer. No file-size compression gain is claimed.

Evaluate reduced working storage before pixel bit-packing. Current general
64-index frame61440bytes could be packed into46080at6bits,only15360saved with
additional read/write extraction;4bits cannot directly represent all64indices.
Any palette indirection requires explicit binding/priority/output proof. Rowwise
composition could avoid a complete pixel frame but must independently provide
15400text workspace and preserve every indexed pixel,scroll split,priority and
resource invalidation;net savings cannot simply be called61440. The current
full-frame IO contract stays unchanged;these are candidates,not adopted code.
PRG compaction needs every source read/address and canonical snapshot identity
reconciled;discarding original instruction-looking bytes without that proof is
not permitted. No compressed resources or overlays are introduced.

A narrower follow-up investigates the DOS root's separate10016-byte capture
scratch versus synchronous transaction staging. The last-running recovery cache
must remain independent. The S5statement retaining all embedded capture/recovery
buffers is not reversed by this audit:prove that staging borrow is consumed before
the next capture,and that failed capture/load/save preserves recovery,then pair
output/snapshot/failure routes and actual memory. Only that evidence may select
reuse. Report components/estimated delta before any product edit;refresh three
EXEs if selected. Redundant cached CHR-read candidate remains unadopted.

This P is evidence/documentation only,zero product-code changes. P2three products
and binary-bound native/host/DOS equality remain. Historical1992/1992,local1991/1992
nodes,4260/4261feasible controls(raw4342,infeasible81),scope/expected/actual[],new0.
S6/T28 remain open for joint fit/cadence/input/stack/full-route obligations;no M2
or physical486SX/DOS-version certification. Raw maps/MCB logs/images/probes remain
under ignored build/m3-t28-s6;tracked evidence contains neutral conclusions only.

The tighter416KiBcaller-free post-startup route also exits0with game/text/graphics
captures and a changed same-resource10035-byte save,frame7465to7511,startup4.
Both game saves pass independent file-CRC/length/resource-identity checks. Its2041
samples,two records,zero bad chains/drops observe maximum425984bytes:primary343920,
environment160,auxiliary81904. This includes MCB overhead;the caller-largest425968
excludes the original free block's16-byte header. Extra auxiliary reservation is
304rather than the roomy route's4464;this does not establish identical CRT buffer
policy or equal IO performance. This demonstrates scoped constrained operation,
not a universal416KiBrequirement or the420.1KiBroomy reservation being mandatory.

## S6 P4 checkpoint: omit overwritten raw reads in the valid CHR-cache path

One shared read-only PPU source file changes,+4/-2. Raw CHR low/high reads now
execute only when no valid decoded cache is supplied. A full cached tile instead
loads its two decoded bytes before use;partial cached tiles read decoded indices
without consuming raw low/high. Uncached full/partial tiles retain both original
bounded reads and shifts. No core ROM path/state,PPU state,priority/palette/scroll,
snapshot schema,IO ABI,new allocation or emulator setting changes. Similar-issue
sweep covers background full/partial tile reads,sprite and background-opacity
readers,cache preparation,binding/invalidation and null/short resources;those
other owners already select raw/decoded paths and need no edit. Low/high are
initialized on every consuming branch. This is a scoped optimization acceptance,
not acceptance of the still-unplayable integrated DOS runtime.

Both native widths build the product and needed targets,then pass10focused
checks,including2048boundary and1198native state/output presentation cases,
independent raw renderer comparison,cached/uncached/null/short resources,two cache
instances/reset/resource replacement,raw-opacity priority aliases,clock/pacing,
VGA mapping,snapshot continuation and platform purity. Each width also passes
13private-desktop host groups against the newly built Windows binary:borrowed/
owned console,input/focus/Unicode,recovery,Tab,shell wait/return and close routes.
Native logs are UTF16;the local summary reader was corrected to decode their
actual encoding rather than treating NUL-delimited bytes as missing assertions.

An unintended default-all target build fails in both widths on the unrelated
legacy Cannon Children harness:bullet_bill_gfx references observation record but
that harness lacks its linked owner. Needed product/test targets build and pass.
This is registered in TODO with this checkpoint;no claim that the default-all
build passed,no out-of-scope harness/core repair or retest of unrelated chains.
The first subsequent target invocation also used the wrong output-file name as
a CMake target;the corrected mysmb_win32 target build is the accepted receipt.

Original OpenNT16/historical runtime builds the formal product. Three DOS normal,
cache-failure and constrained lifecycle runs match all five active61440-byte
frames,640000VGA readback bytes,8000hardware text bytes,12000neutral cells and
10035snapshot bytes each. Modes and all live near/far frees remain unchanged.
Normal instrumented owned peak436464(+16),minimum contiguous212608,far payload
82036. Failure435984/213088/82036;pressure648608includes ballast,largest464.
Observed untouched stack76/98/74is unchanged narrow coverage,not universal safety.

Two fixed-config paired aggregate profiles match all active frames,twenty VGA
planes and final snapshots. PPU costs9.562-11.692percent shorter,ordinary output
water/castle10.185percent shorter. Complete output-only water/castle/dense costs
7.393/7.393/7.059percent shorter;title7.243,load1.616,text about10PIT ticks shorter.
Both repetitions retain the same values. Output-only absolute cost remains about
1.315-1.382seconds at nominal PIT conversion,not normal gameplay FPS/input-tail
proof. The separate actual wall-key route is not a fixed-tick equivalence test.
Configuration,normal SDL and private desktop remain verified unchanged.

The external MCB observer runs the actual candidate,not an instrumented child.
Roomy448KiBbudget route exits0with2055samples/two records,no bad chains/drops:
maximum430160=343936primary+160environment+86064auxiliary,+16versus P3. Constrained
416KiBbudget route exits0with2058samples/two records,no bad chains/drops:
maximum425984=343936+160+81888,the same bounded occupied total as P3. Parent/ballast/
observer are excluded;MCBs/PSP are included. This is sampled occupancy,not complete
transient peak or identical CRT buffering policy. Reviewed game/text/graphics
captures and CRC/resource-bound10035-byte saves pass;seed frame7465advances to7515
(roomy) or7514(constrained),startup4preserved. Esc restores and returns0. No all-
route416KiBrequirement,physical486SX speed or DOS-version claim.

Three owner-authorized tracked products refreshed and manifest/asset identities
checked:

- mysmb16.exe:303107bytes,SHA256 0290ce11018cdd10c49c0403b6b339cf029a813faebd4d733e9f7b537c7c143b.
- mysmb32.exe:319627bytes,SHA256 fec0079a8f9216b46fb26d283691e94f914eb773fd65f6e4c31ba431c925e89d.
- mysmb64.exe:328299bytes,SHA256 f5cbee86f719e122600a40a7c5eb9148abb594b3b413b2fc440306a50a696772.

DOS minimum MZ327616(+16),DGROUP49472,headroom16064,stack2048,max segment32768.
No new heap/cache/frame storage. P4 changes one product file,with the independent
instrumentation/logs/resources contained below ignored build/m3-t28-s6. Historical
1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81),scope/
expected/actual[],new0,custody unchanged. S6/T28 stay open for joint fit/playability,
continuous/full-route stack/peak,input-tail and remaining candidate dispositions.
No M2/M4 certificate is inferred from these receipts.

## S6 P5 continuation: measured zero-pattern tile fill and memory alternatives

A contained candidate fills a full cached eight-pixel zero-pattern row with the
universal background color instead of eight repeated index/lookup stores. All
four background palette-zero entries already alias that color. Partial tiles,
raw renderer,priority queries,left mask,split and source semantics must remain.
No extra tile/frame cache or dirty-state approximation is permitted. Evaluate
exact full buffers/planes/snapshots and complete timing before adoption;then
report source scope/size and repeat required product/memory/failure checks.

Pixel packing,rowwise API changes and PRG compaction remain unadopted alternatives,
with P3storage/identity/latency obligations. Capturing into transaction staging
alone has no measured runtime gain while CRT retains the complete near segment;
minimum MZ reduction is insufficient. Do not shrink stack/CRT blocks blindly or
change emulator settings. Keep progress tied to measured complete output and
actual DOS reservations;cadence/input gates remain unfulfilled.

## S6 P5 checkpoint: exact full zero-pattern tile row fill

One shared read-only PPU source file adds3lines. When a full cached eight-pixel
row has both decoded bytes zero,all eight source indices are zero. Local palette
entries0/4/8/12 already alias the universal background color,so one bounded
memset fills exactly those eight pixels. Nonzero rows retain all eight lookups;
partial tiles and uncached paths are unchanged. Sprite opacity/priority,scroll
split,left masks,state,resource binding,game ticks/audio and snapshot/IO schema
are unchanged. No dirty-frame approximation,pixel suppression or extra cache.
The current candidate source matches the contained two-run performance prototype.

The similar-issue sweep covers universal palette aliases,zero/nonzero full rows,
partial first/last tiles,short/null resources,cache resource/reset and raw sprite
priority queries. It also identifies an overlooked optimization opportunity:
the cached sprite path selects decoded pixel values but still performs two
unused raw pattern reads first. P4's statement that other readers already select
paths did not prove those reads were skipped. Its scoped output/cost evidence
remains valid;the remaining sprite-read cost is explicitly received by P6,not
misrepresented as a ROM logic mismatch or already optimized code.

Both widths pass10focused tests,including independent raw/full renderer checks,
2048boundary and1198native game-state/output cases,cache lifetime/resource/null/
short/priority cases,VGA guards,snapshot continuation,clock/pacing and purity.
Each width passes13new private-desktop host routes for the actual changed Windows
product and its rebuilt fixtures. The unrelated default-all legacy Cannon Children
link debt from P4 remains in TODO;these are focused receipts,not all-target proof.
Original OpenNT16/historical runtime builds the full DOS product without new flags.

Three DOS normal/cache-failure/pressure routes each match five active61440-byte
frames,640000VGA-plane readback bytes,8000hardware text bytes,12000neutral text
cells and10035snapshot bytes. Initial mode3returns and all live heap payloads free.
Normal instrumented peak436528(+64versus P4),minimum contiguous212544,far live82036;
failure436048/213024/82036;pressure648608includes ballast,largest464. Stack untouched
76/98/74retains existing bounded evidence;no all-route stack shrink or peak claim.

Two paired fixed-config prototype profiles match all active output frames,twenty
VGA planes and final snapshots. Complete output-only water/castle/dense cost
0.649/14.116/13.430percent shorter versus P4;title7.710/load2.742percent shorter,
text differs by9PIT ticks. PPU stage0.922/20.053/18.697percent shorter for those
output cases;improvement depends on zero-pattern occupancy. Absolute output-only
cost remains about1.13-1.31seconds,not accepted normal cadence/input latency.
No settings,normal SDL,private desktop or physical target qualification change.
Scoped optimization acceptance does not close the unplayable integrated budget.

The actual formal product also completes the bounded448/416KiBcaller-free routes.
External observer sees2042/2060samples,two records each,zero bad chains/drops.
Roomy maximum430224=344000primary+160environment+86064auxiliary,+64versus P4;
constrained maximum425984=344000+160+81824,unchanged budget-bound total. Observer/
parent/ballast are excluded,MCB/PSP included. This is sampled occupancy,not
continuous peak or identical CRT buffering. Reviewed game/text/graphics captures,
CRC/resource-bound10035-byte saves and Esc result0pass;both saves advance seed
frame7465to7521with startup4preserved. Input script wall timing is not fixed-tick
ROM equivalence or playable latency proof. No all-route minimum-free claim.

All three owner-authorized products refreshed after the operational gates:

- mysmb16.exe:303171bytes,SHA256 86372380f7ceaa877f2dd3bdbc40a1d36d2f989e36fcd15fd79bc72b7d26629c.
- mysmb32.exe:319627bytes,SHA256 d7a4941958fd1a219d4eef11a7228dc9ce869f1b537535b0a71374adc97a36ba.
- mysmb64.exe:328811bytes,SHA256 c9b7766138d509342baa0ccaacd1449ac14a30b1078677277183d5b790ec4ed7.

Minimum MZ327680(+64),DGROUP49472,headroom16064,stack2048,max segment32768. No
new heap/workspace. Raw artifacts and tests stay under ignored build/m3-t28-s6.
Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28 remain open
for actual continuous/full-route peak/stack,nominal cadence/input and integrated
opportunity dispositions;no M2/M4 certificate or all-input equivalence claim.

## S6 P6 continuation: bounded rowwise-composition memory prototype

Prioritize actual conventional-memory savings rather than another standalone
sizeof reduction. Investigate a compatible rowwise read-only PPU producer and
neutral IO/VGA band submission:produce every logical256x240pixel from the same
immutable state,then stretch the same complete640x400output. Existing full-frame
Windows APIs and snapshot schema stay supported;no core ROM routine or PPU-state
representation changes. Text remains authored element presentation,not pixel
sampling. Its15400-byte working store must be provided independently or reused
exclusively with bounded graphics bands;do not claim the entire61440pixel pack
as net savings. The first P6step is contained prototype/design and scope review,
not an already adopted IO contract or measured gain.

Prove strip clipping,full/partial tiles,sprite flips/offscreen and source priority,
status split,resource/cache invalidation,all output rows/planes,text/Tab/restore,
allocation failure and exact snapshots before adopting a producer extension.
Measure repeated sprite scans and boundary-row duplication as whole-output costs;
keep full-frame reference/probes for comparison. Do not save memory by dropping
pixels/ticks,lowering resolution or blindly shrinking the CRT primary block.
Cached sprite-read omission may be evaluated in the same bounded renderer cohort,
with independent dispositions. Report affected components/estimated size before
any production edit;three EXEs remain required for product-code P work. Pixel
bit-packing/PRG compaction remain unadopted alternatives with P3identity/cost gates.


## S6 P6 checkpoint: contained rowwise feasibility and integration boundary

No product source or executable changes. A contained C90 prototype narrows the
same read-only compositor to a requested source-row span. Background source
coordinates remain absolute;only the output address is rebased. Sprite rows are
clipped against that span while reverse OAM priority,flips,opacity queries,left
masks and the visible status split retain the full-frame algorithm. Cached
sprite raw reads remain unchanged to isolate this experiment.

Native x86 and x64 each pass512synthetic cases. Raw and cached full-frame output
agree;cached and uncached strips of1/11/16source rows compare188743680bytes per
width against the retained raw full-frame path. Twenty-five destination bands
compare65536000VGA-plane bytes per width against the production full-frame VGA
path and an independent coordinate formula. Tests include varying scroll,
control/mask combinations,split phases,zero/random patterns,null/short CHR,
workspace resource rebinds and overlapping/flipped/behind-background sprites.
Source-state immutability,output guards and invalid-span rejection pass. These
are renderer fixtures,not original-ROM routes,actual device readback,complete
branch enumeration or DOS performance/peak acceptance.

The fixed16destination-row bands need at most10source rows/2560bytes. Across a
complete frame they compose250source rows,ten repeated boundary rows rather
than240. Each band may scan64OAM entries again;the paired synthetic costs below
include these overheads,with actual integrated product timing still required. The existing15400-byte text store can contain the
pixel band exclusively. Replacing61440bytes with15400has a potential46040-byte
payload saving;actual DOS block/CRT/MCB savings and launch threshold remain
unmeasured. VGA1280-byte scratch,CHR cache,snapshot staging and last-running
cache remain separate. No fidelity-reducing color packing is adopted.

Production integration must preserve current full-frame APIs and the Windows
path. Add an explicit band initialization/binding entry rather than appending
uninitialized callback members to legacy hooks. Composition alone binds const
PPU state and workspace to a synchronous neutral IO producer;VGA consumes only
bounded neutral rows and never receives game/PPU pointers. The band lifetime
ends before the next request,mode change or game tick. Root initialization must
allocate the smaller store directly,not allocate61440then shrink,so launch fit
can improve. Text and band views are exclusive;restores rebuild the selected
presenter without changing snapshot bytes or translated decisions.

Contained implementation,tests and receipts remain under ignored build/m3-t28-s6.
The original OpenNT large-model compiler and historical runtime now compile and
link the contained far-pointer probe. Two existing integral-conversion warnings
also occur in the production full-frame source;link retains the existing optional
OLDNAMES lookup warning. The successful invocation uses the prior short temporary
directory and absolute source path. Earlier invocations produced no object and
were terminated with their logs retained;do not count them as passing builds.

Normal SDL on a private desktop and the unchanged DOSBox configuration completes
the eight-case DOS probe in105.51seconds. It compares2949120strip bytes and
1024000VGA-plane bytes,with source-state immutability,guards and invalid-span
rejection. This proves scoped large-model execution and neutral plane mapping,
not hardware VGA readback,integrated Tab/load/exit,new product resident memory,
continuous peak,full-route stack or playable cadence.

Two additional runs of the same large-model probe also verify the optimized
band-relative VGA mapping against the retained complete raw pixels. Each run
retains all eight far/guard/state cases. Summed cached PPU composition plus
complete plane mapping costs8790to9210and8780to9260clock units,approximately
4.778and5.467percent longer. CLK_TCK is1000with coarse legacy-clock resolution;
these sums are synthetic fixture costs,not game FPS. Both runs use identical
probe bytes,the unchanged configuration and private normal-SDL desktops;
wall execution147.22seconds each includes correctness comparisons. Timed
regions exclude physical VGA writes,presenter changes,game ticks and input.
This supports a named CPU/memory tradeoff,not a claim of integrated playable
cadence. Actual resident-memory savings still require the product integration.

Prospective production
scope is approximately8-10files/350-550changed lines across PPU frame,neutral IO,
composition root,VGA mapping and focused tests,with no core or PPU-state/schema
change. This expands the original estimate explicitly. The owner subsequently
accepts the approximately45KiB allocation-saving tradeoff and admits P7 memory
implementation. Required equality,mode/load/exit,allocation-failure,actual DOS
resident savings and product gates stay in scope. Extra speed recovery from
repeated rows/OAM scans and cached sprite raw reads is recorded in TODO and
revisited only if further speed is needed;it does not block memory adoption.
No claim of accepted normal cadence,input latency or physical486qualification
follows from that deferral. S6/T28 remain open.

Historical1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342,
infeasible81);scope/expected/actual[],new0,no custody transfer. Products retain
the P5 hashes and are not refreshed for this prototype/design-only part.


## S6 P7 checkpoint: adopted bounded row producer and smaller DOS store

Owner admits the rowwise memory implementation and defers additional speed
recovery to TODO. Shared PPU frame composition has one algorithm for full-frame
and bounded rows:logical coordinates,source scroll/split,opacity,reverse OAM
priority and CHR/cache bounds are unchanged;only output offsets and sprite-row
clipping narrow to the requested span. Explicit capacity validation rejects
invalid requests before output/cache changes. Every original logical pixel still
reaches the same full640x400VGA mapping. Core,PPU-state,snapshot encoding,source
sound and tick/input decisions have no changes.

Neutral IO declares a synchronous source and returned const row view. DOS
composition binds it to const PPU state/cache;VGA consumes only pixels and absolute
row ranges. Four planes consume each band before reuse. No device gains a game,
OAM,nametable or CHR dependency. Existing full-frame entry points and legacy hook
layout remain supported;an explicit opt-in initializer allocates the requested
store directly. The actual product requests sizeof its15400-byte text pack,
which also holds each at-most2560-byte graphics band. Text/graphics remain
exclusive;mode return and load rebuild all selected output. Source callback or
mapping failure feeds the shared exit latch;optional near/far cache fallback
and matching free provenance remain unchanged.

The similar-issue sweep covers all DOS pixel/text consumers,root initialization,
full-frame fallback,mode failure,snapshot redraw,cache/resource/reset,shutdown,
VGA coordinate bounds and mutable ownership. The full-frame consumer executes
only for legacy full-frame roots;the row root never submits its short storage as
a complete frame. Main borrows that storage only for the declared text pack.
Devices submit neutral planes/cells only. No unrelated raw/cache/tick repair is
included;repeated rows/OAM scans and redundant cached sprite reads stay in TODO.

Both widths pass11focused tests. The new512-case test uses the retained independent
per-pixel reference,compares188743680cached/uncached strip bytes and65536000plane
bytes per width,and verifies guards,state immutability,invalid ranges/capacity
and cache rebinds. Root tests also exercise opt-in initialization,oversized reads,
sink-failure exit and idempotent shutdown. Existing2048boundary/1198native scene
checks,snapshot continuation,clock/pacing and platform-purity tests pass. Each
changed Windows product passes13private-desktop host routes. Original OpenNT16
large-model compiler/historical runtime builds the DOS product;existing conversion
and optional OLDNAMES lookup warnings remain. Focused receipts do not resolve the
unrelated default-all Cannon Children harness debt.

Three actual DOS device/lifetime routes(normal,optional cache failure,near/far
pressure) each match five61440-byte active logical frames,640000hardware VGA
plane bytes,8000hardware text bytes,12000neutral text-cell bytes and10035snapshot
bytes against the retained S5 route. The inactive text-overwritten graphics view
is excluded explicitly. Frame files are reconstructed in bounded rows outside
timed regions;no full-frame scratch allocation is hidden in the row probe.
Mode3restores and observed live far/near payloads return to zero. Instrumented
normal/failure peaks392880/392384bytes,far payload35996;pressure648064includes
ballast. Minimum largest free256192/256688/1008bytes. Untouched stack72/94/70bytes
preserves only the retained bounded pattern test,not all-route stack headroom.

The formal uninstrumented product completes448/384KiBcaller-free game/load,
Tab/text/graphics,save and Escape routes. External BIOS observer sees1866/1863
samples,one change record each,zero bad chains/drops. Both sampled maxima are
386512=345376primary+160environment+40976auxiliary bytes,including MCB/PSP and
excluding observer/parent/ballast. Against P5roomy430224,this is43712bytes less
(about42.69KiB);the61440to15400payload reduction remains46040bytes. CRT blocks,
new code and allocation rounding explain why the net observed result differs.
This is sampled occupancy,not proven continuous peak or a whole-game minimum.
CRC/resource-valid10035-byte saves advance seed frame7465to7519and startup4;
wall-script frame counts are not deterministic ROM-equivalence/input-latency
proof. Captures show actual gameplay,text and reconstructed graphics.

Retained same-state instrumented phase totals change+4.958percent(title),
+0.911(load),-0.105(text),+5.620(return graphics),+2.647(save),+0.927(reload).
These include census/instrumentation and full route work;they are not isolated
render-stage or playable FPS claims. P6paired synthetic compute overhead remains
separate evidence. Extra row/OAM speed recovery is owner-deferred;no pixels,
ticks or output size are dropped and no DOSBox configuration is modified.

An additional376KiBcaller-free formal-product route also completes:1867observer
samples,one record,zero bad chains/drops,sampled382416=345376+160+36880bytes.
The CRT uses a smaller auxiliary reservation under this budget. Its10035-byte
CRC/resource-bound save advances frame7465to7518;reviewed game/text/graphics
captures and Escape result0pass. This lowers the tested successful budget to
376KiBbut does not prove an absolute or all-route minimum. No configuration
changes or physical hardware/DOS-version qualification are claimed.

Actual source/test/build diff is11files,+265/-26:8product source/header files,
2focused tests and one CMake binding. No core/PPU-state/schema edit.
All three owner-authorized existing products refreshed:

- mysmb16.exe:304547bytes,SHA256 ffe82b1d6976e82dcd73e9630e7e0a793275d2af51ac0d1afe98965e79e261f3.
- mysmb32.exe:320139bytes,SHA256 a1be524024fd48de068ad4b20bf175e22698a7cd993ea587bd5c442de671c835.
- mysmb64.exe:328811bytes,SHA256 66ab9c17df3b0afb3c644ff0b6e73ad91353095fc723bbf77103211bbfe333cc.

DOS minimum MZ329072bytes,DGROUP49488/headroom16048,stack2048,max segment32768.
MZ increases1392bytes versus P5and omits dynamic heap/PSP/environment. Primary
actual block increases1376bytes;the reduction comes from smaller far storage,
not a misleading EXE-size decrease or blind CRT-block shrink. Raw logs/probes,
readbacks/captures/resources remain ignored below build/m3-t28-s6.
Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28 remain open for cumulative cadence/input,full-route
continuous peak/stack and opportunity dispositions. No M2/M4 certificate or
exhaustive behavior claim is inferred from this bounded adoption.


## S6 P8 checkpoint: lower launch boundary and actual-loop deficit

Read-only product audit;formal P7code/products unchanged. The owner-deferred
row/OAM speed recovery remains TODO. This part strengthens memory failure and
cadence/input evidence rather than accepting an unplayable small-memory build.
All diagnostic sources,libraries,logs and captures are contained under ignored
build/m3-t28-s6;no source or asset import into the tracked product.

The formal product under372KiBcaller-free budget(before-EXEC largest380912bytes)
loads successfully but exits1before sustained execution;the seed save is intact.
Under374KiB(before-EXEC largest382960) it completes the same game,Tab/save/Escape
route as376. External observer records1867samples,one event,zero bad chains/drops,
owned382416=345376primary+160environment+36880auxiliary. CRC/resource-valid
10035-byte save advances7465to7518. This is a tested successful budget and a
failed lower budget,not a proof that373works or an all-route/absolute minimum.

A contained diagnostic initializer distinguishes root allocation exit11,
snapshot-store allocation exit12 and device-open exit13. The372KiBroute exits12:
the required20084-byte transaction allocation cannot be provided after row-store
initialization. The diagnostic has the same304547file bytes,329072minimum MZ,
49488DGROUP,2048stack and existing product libraries. It is independently linked,
not binary-identical apart from status constants;its result is source-level
failure localization that supplements the unmodified product failure. No allocator
or cleanup change is made merely to suppress this valid capacity failure.

The source allocation census finds four explicit sites,all in DOS composition:
required15400-byte row/text store,required20084-byte transaction store,optional
8192-byte near cache and its optional far fallback. No explicit malloc/calloc/
realloc/DOS-block allocation call exists in core,text,PPU,IO or app source.
File adapter has two fopen sites;store control flow closes the data handle before
replacement or error logging,so at most one of these product file handles is
live. This census does not bound opaque CRT buffers/fragmentation,prove every
stack path or upgrade18HzMCB samples to a continuous peak.

Actual-loop timing probe uses the P7product libraries and the same DOS main/device
flow,adding bounded in-memory frame/IRQ telemetry and one report only after
shutdown. PIT rate,IRQ0,source ticks,input decoding and all output work are
unchanged. IRQ telemetry reads BIOS time only;sampling the PIT inside IRQ1 would
incorrectly re-enable interrupts and is deliberately avoided. Last run captures
its published event limit inside the existing input critical section. Physical
transition coalescing affects telemetry only;production keyboard decoding still
receives every scan,including typematic repeats. No virtual input or clock shim.

First run has97frame records without overflow,but raw typematic telemetry drops
559key records;its input latency is excluded. Second run has97frames/13physical
transitions and no drops;its post-read event-drain boundary remains diagnostic.
Third run fixes the input/event sampling boundary and retains97frames/13events,
zero drops. The two complete frame-cost runs agree:78ordinary graphical ticks
have885467minimum,1315640.5median and1367909maximum PIT units;12ordinary text ticks
have1102719minimum,1103785median and1105392maximum. Median costs are approximately
1102.63and925.08milliseconds. Every selected frame exceeds the existing19886PIT
period(about16.67ms). Start/load/save/mode-control frames are excluded from those
steady-state summaries,not omitted from the raw trace or general lifetime work.

Third-run D/Jdown and release records feed buttons65and0to their actual original
next ticks. Coarse BIOS/IRQ bounds allow two65536-count cycles of uncertainty,
including a pending timer update. Even conservative sample-lag lower bounds are
about807msfor the down pair and409msfor releases,far beyond a two-period33.33ms
comparison limit. First completed submission is approximately1.91-2.02seconds
from down and1.51-1.62seconds from release within that coarse interval model.
These are scoped diagnostic timings,not formal-product FPS,all-key latency,
wall-clock precision,physical486SXor audible DOS sound qualification. DOS audio
adapter remains unavailable,as already recorded by S1;no sound-load claim.

Installed configuration identity remains unchanged;normal SDL/private desktops,
core/cputype/cycles auto,frameskip0and existing video/memory settings are retained.
No cycles,machine,scaler or other override is introduced. Thus the fixed-runtime
cadence/input gate fails even though memory fit improves. The owner-approved
small-memory tradeoff does not convert this failure into performance acceptance.
M4physical target qualification remains separate,not inferred from this emulator.

| Remaining cumulative clause | Current evidence and disposition |
| --- | --- |
| Required store/startup boundary | Four source sites and372fail/374pass are established;373and full-route minimum remain unproved. Preserve orderly failure. |
| Continuous peak/CRT | Existing sampled product and three lifecycle censuses retained;opaque runtime reservation/error-path coverage remains pending. No whole-game peak claim. |
| Stack | P7bounded72/94/70untouched-byte patterns retained;no shrink or all-path bound. Pending. |
| Nominal cadence/input | Actual-loop configured-runtime test explicitly fails. Identify cumulative stage costs before choosing further work;do not silently enable deferred micro-optimization or claim60Hz. |
| Six opportunity dispositions | Retain S2/S3compact CHR/direct opacity,S4bounded rows/bulk memcpy,S5rejected unchanged-region cache and P7memory adoption;no new speculative cache or transfer specialization. Extra recovery remains TODO. |
| Final integration/hardware | P7pixel/state/snapshot/native/device receipts retained within their fixtures. M2certification,DOS sound/version and real486performance remain independent obligations. |

Historical1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. Three products retain
P7hashes;no rebuild for this product-code-free diagnostic part. S6/T28 stay open;
P9receives cumulative stage attribution and the named runtime/stack gaps.


## S6 P9 checkpoint: cumulative stage attribution without product edits

A contained stage probe links unchanged P7libraries with diagnostic copies of
DOS composition/device calls. Ten disjoint accumulators record input,original
game tick,PPU row production,VGA mapping,VGA transfer,text assembly,text transfer,
snapshot capture/cache,audio extraction/submission and wait. Per-frame start/end
brackets exclude post-frame telemetry writes;all logs are emitted after shutdown.
No source tick,controller operation,presentation,mode or snapshot work is skipped.
No product file,original ROM routine,PPU state or text artwork changes.

The instrumented root/device modules must replace their original library modules,
not coexist. A contained library group is rebuilt from the exact P7objects while
excluding those two modules. Initial duplicate-symbol link attempts are not
passing evidence;the corrected group builds with original OpenNT16/runtime.
No formal product library is edited. This avoids mistaking a stale full-frame or
uninstrumented owner for the timed implementation.

First run records100frames but drops the final two records;accepted only as a
partial stage comparison. Second run keeps the same100-slot buffer and explicitly
omits telemetry for ten repeated early title frames. Those game ticks still run.
It retains92records,zero drops,all selected game/Tab/save/load/exit stages and the
actual Escape request. Calibration costs105129PIT units for1000clock calls,about
88microseconds per call including the calibration loop. All selected warm rows
confirm cacheNear1:the diagnostic storage does not switch the optional CHR cache
to a slower far or uncached path. The added telemetry is not a product-memory
measurement or an all-route stack proof.

Both runs have12steady text samples and44/45steady graphical game samples. Their
stage medians agree within the retained measurement resolution. Each frame's
non-wait component sum is checked against its outer root-step interval;no nested
component is double-counted. Ratios below divide component medians by total
median,not a claim that medians add exactly or every workload has that ratio.

| Scoped steady-state component | Graphics median ms | Text median ms |
| --- | ---: | ---: |
| Input | 0.142 | 0.142 |
| Original game tick | 9.179 | 9.188 |
| PPU logical row composition | 671.975 | 0 |
| VGA full-screen plane mapping | 374.365 | 0 |
| VGA plane transfer | 35.376 | 0 |
| Authored text scene construction | 0 | 819.287 |
| Text device transfer | 0 | 65.452 |
| Snapshot capture/running cache | 30.451 | 30.451 |
| Audio extraction/unavailable-device submission | 0.906 | 0.906 |
| Total root step | 1144.329 | 926.078 |

Graphical PPU/mapping/transfer account for approximately58.722/32.715/3.091percent;
text construction/transfer account for88.469/7.068percent. Original game tick is
0.802/0.992percent. Wait contributes about0.200ms after those intervals;it is not
the bottleneck. Graphics has about21.85msunattributed inside the instrumented root
step,text about0.707ms. Numerous nested graphics clocks also add cost inside their
brackets:do not subtract the residual alone or call these formal-product FPS.
P8lower-instrumentation timings remain the overall-cadence evidence. App-request,
startup and mode/control frames stay in raw records but are excluded from these
steady-state rows. DOS audible sound remains unavailable;this is no sound-load
or physical486SXperformance qualification.

Same installed configuration hash,normal SDL and private desktop are retained,
without cycles/frameskip/video/memory overrides. Both10035-byte saves retain CRC
and resource binding;the wall-script frame count is not a deterministic ROM route.
No new M2node/control credit. The configured cadence gate still fails;stage timing
now shows why renderer-only micro-tuning or changing game logic would be an
unsupported response to the measured deficit.

The next bounded evaluation targets read-only composition and neutral VGA mapping:
compare shared-row/four-plane staging against the current repeated far reads,
using existing15400-byte exclusive storage before considering another allocation.
Account for near/stack constraints,alias lifetimes,all pixels/planes,clipping,
mode/load/exit and complete cost. PPU/table and text-construction alternatives need
separate scoped evidence;no guessed gain or artwork simplification is admitted.
The owner-deferred ten-row/OAM/raw-read recovery remains TODO. No ROM business
rewrite,frame/tick suppression,compiler replacement or emulator setting changes.
This is a prospective contained prototype,not adopted product optimization.

CRT/error-path and all-path stack bounds remain pending alongside failing
configured cadence/input and M4hardware obligations. Retain P7memory/pixel/native
receipts;do not restart a whole-project audit. Three products retain P7hashes.
Historical1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28remain open;
P10continues bounded renderer/mapping evaluation and the named memory/stack gaps.


## S6 P10 checkpoint: bounded four-plane alternatives and selected prototype

Contained prototype only;formal product source and three EXEs remain P7.
Evaluate the same neutral indexed row band into four contiguous VGA plane bands.
Each candidate shares the exact floor(x*4/5),floor(y*3/5)mapping,63mask,repeated
source-row reuse,capacity/band validation and synchronous source lifetime. It
never receives game,nametable,OAM,CHR or audio state. No changes to PPU composition,
original control flow,display mode,output size,pixel coverage or input/tick work.

Three alternatives are compared as one bounded cohort:

| Candidate | Storage and measured disposition |
| --- | --- |
| Sixteen-byte input plus four local80-byte outputs | Copy one16-byte source group,stage all four rows,then copy them into plane bands. Mapping/submission improves only about0.91percent;whole graphics-return route about0.31percent. Instrumented peak392752(-128versus P7row probe). Reject as too weak for the remaining deficit. |
| Full256-byte input plus four local80-byte outputs | One source-row copy saves small memcpy calls,but variable-index access costs more with the actual compiler. Mapping/submission about34.95percent slower,whole graphics-return route12.17percent slower. Peak393088(+208). Reject;native intuition is not DOS performance evidence. |
| Sixteen-byte input and direct four-plane writes | Read each group once,unroll exact per-plane indices,and advance four far output pointers. No320-byte local outputs or256-byte source array. Mapping/submission about29.85percent shorter;whole graphics-return route10.43percent shorter. Peak392592(-288). Select for the subsequent production integration gates,not as completed playability. |

The5120-byte plane band borrows row/text storage after the first2560source bytes.
It uses existing15400-byte allocation,not an additional far/near heap request.
The independent1280-byte static scratch is removed in the DOS prototypes. Source
and destination ranges are disjoint during graphics;authored text owns the whole
store only while active. Rebuild every band after text/load. Tests use two guard
bytes around packed scratch;production integration must declare bounds/lifetime
and require the text pack to fit2560+5120bytes. No output mirror or hidden cache.

Each candidate passes both x86/x64 C90 harnesses across every legal destination
first row and batch size1through16. Each width compares16972800bytes with the
retained single-plane implementation and independent coordinate formula,including
high-bit input masking,all rows/planes,guards and invalid bounds/capacity. This is
scalar mapping proof,not original-ROM or physical hardware qualification.

Each actual DOS candidate route matches five61440-byte active logical frames,
640000hardware VGA-plane readback bytes,8000hardware text bytes,12000neutral cells
and10035snapshot bytes against the retained S5route. Text-phase inactive pixel
view remains excluded. Mode3restores and observed near/far live payloads free.
All candidates retain far payload35996bytes and72untouched stack-pattern bytes
in this route. The unchanged low-water mark does not prove every potential stack
path safe;it prevents inventing an all-route margin or shrinking the stack.

The selected direct-write candidate repeats under the same unchanged installed
configuration,normal SDL and private desktop. Same probe bytes,both runs have
identical active frames,all twenty plane readbacks,text/cells and snapshot bytes.
Paired timing totals retain about29.85percent mapping/submission reduction. Whole
instrumented title/load/graphics-return/save/reload route costs decrease roughly
8.93/1.85/10.43/5.28/1.85percent versus P7row probe. Those totals include route and
memory census work;not all are render-only frames. Do not use shorter wall time
or this scoped reduction as a nominal60Hzor actual product-memory claim.

The similar-issue review covers duplicate source reads,local variable indexing,
far pointer updates,partial bands,last row239,column255,first-row duplicate guards,
capacity arithmetic,source/destination aliasing,text reuse,resource-independent
mapping and complete device submissions. All hits have the above explicit
candidate dispositions. Original compiler/runtime flags are retained;no compiler
replacement,settings override,frame/tick dropping or artwork change is used.

P11receives production integration of the selected neutral converter and DOS
composition scratch binding. Expected3product files plus focused test(s),roughly
100-220changed source/test lines;existing scalar/full-frame APIs remain supported.
Required gates:independent mapping/guards,actual normal/cache-failure/pressure
routes and snapshots,formal-product startup/resident fit,stack/lifetimes,Windows
focused/host regression,original DOS16 and all three refreshed EXEs. No success
is inferred from the prototype before these integrated results. Deferred row/OAM
recovery stays TODO;PPU/text major costs and CRT/stack/cadence limits remain open.

Historical1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. No product-code or
EXE refresh for this prototype-only P. S6/T28remain open.


## S6 P11 checkpoint: direct four-plane product integration

Adopt the P10selected converter in the neutral VGA owner. It reads one16-byte
source group into a local16-byte array and writes the four exact plane patterns
directly. Rows use the same coordinate formula,63mask,source-span/capacity checks
and duplicate-row copies. Existing scalar/full-frame interfaces remain supported.
No core,PPU-state/composition,authored artwork,snapshot schema,tick,input or source
sound change. Device receives only pixels,plane and row offsets.

DOS composition borrows a5120-byte output band at offset2560in its existing15400-
byte exclusive text/pixel store. The compile-time fit condition covers7680bytes.
The separate1280-byte static scratch is removed. Source and packed output never
overlap;the four planes submit before the next source rebuild. Text owns the full
store only while active;graphics regenerates source/output after mode/load.
There is no new allocator,process,retained output mirror or cache. Root initializer,
matching near/far ownership,required snapshot storage and error cleanup remain.

Similar-issue sweep covers all DOS scratch consumers/initialization/shutdown,
source/output ranges,old API consumers,partial bands,first duplicate row,column255,
last source239,capacity overflow/invalid spans,mode/restore alias lifetimes and
fallback/pressure. VGA source includes neutral IO only;game/resource binding stays
in the composition root. All original logical pixels and full640x400output remain.
Actual product/test diff4files,+103/-9,including3product files and one focused test;
architecture authority is updated separately. No ROM-node implementation credit.

Both widths pass11focused tests,including retained2048boundary/1198native scene
checks,snapshots,purity,clock/pacing and the expanded production VGA test. It checks
all legal first rows and1-16row sizes:16972800bytes against the old single-plane
path and independent coordinates,guards,high-bit masking and invalid spans/
capacity. Each width's current product passes13private-desktop host routes.
A migrated test's stale array name is repaired before passing results;initial
compile failures are excluded. A header comment is clarified and focused builds
rerun;the actual Windows product hashes remain identical to the tested products.
The unrelated default-all legacy harness debt remains outside this proof.

Original OpenNT16/historical runtime builds the formal DOS product with unchanged
flags. Final main source is recompiled/relinked after a comment clarification;
product hash remains the same. Existing conversion/optional OLDNAMES lookup
warnings persist. MZminimum328800(-272versus P7),DGROUP49488/headroom16048,
stack2048,max segment32768. File304275bytes(-272);no dynamic heap or PSP/environment
is included in the minimum MZ figure.

Three production-converter DOS normal/cache-failure/near-far-pressure routes each
match five61440-byte active frames,640000hardware VGA bytes,8000hardware text bytes,
12000neutral text-cell bytes and10035snapshot bytes against retained S5. Mode3
restores;observed live near/far payloads free. Cache allocated/valid1/1in normal,
0/0in failure and pressure confirms actual raw fallback. Instrumented owned peaks
392576/392624/648064(last includes ballast),largest minima256496/256448/1008bytes,
far payload35996. Stack patterns72/72/70are bounded observations,not an all-route
margin. A pressure probe's duplicated C90declarations are repaired before these
passes;its failed build is excluded. No full-frame temporary heap hides the reuse.

Formal actual products under448/374KiBcaller-free budgets both complete game,
load,Tab/text/graphics,save and Escape. External observer takes2048samples each,
one change record,zero bad chains/drops. Sampled owned386240/382144bytes equals
345104primary+160environment+40976/36880auxiliary. Both are272below P7;roomy
comparison to P5saves43984bytes. No continuous peak or all-route minimum claim.
Reviewed captures and CRC/resource-valid10035-byte saves advance seed7465to7523
with startup4retained. Different wall-script frame totals reflect cadence,not
original-ROM equivalence or measured all-key latency. Configuration hash unchanged.

Production-converter normal route retains the P10timing gain:about29.85percent
shorter mapping/submission;whole title/load/graphics-return/save/reload totals
8.93/1.85/10.43/5.28/1.85percent shorter versus P7. These are same-fixture,
instrumented route measurements,not formal-product FPS or a physical486SXclaim.
P10paired output/timing evidence remains applicable to the matching converter;
P9larger PPU/text costs and the configured cadence/input deficit are unresolved.

Three owner-authorized existing product files are refreshed from current builds:

- mysmb16.exe:304275bytes,SHA256 546d2b5d51f49f38a2847edc1c0f556c970bfe347f1e36055cf248667dfdb8c4.
- mysmb32.exe:320139bytes,SHA256 a1be524024fd48de068ad4b20bf175e22698a7cd993ea587bd5c442de671c835.
- mysmb64.exe:328811bytes,SHA256 66ab9c17df3b0afb3c644ff0b6e73ad91353095fc723bbf77103211bbfe333cc.

Windows bytes/hashes are unchanged after rebuild;its renderer does not select
this DOS presenter. All new probes/resources/logs/captures stay ignored in build.
Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28stay open for
CRT/error-path and all-path stack bounds,remaining populated/cadence/input costs
and integrated opportunity disposition. Extra row/OAM recovery remains TODO.
P12first investigates the measured read-only PPU cost with contained prototypes;
no original-game rewrite,settings changes or promised speedup.


## S6 P12 checkpoint: bounded PPU zero-row and disabled-layer alternatives

Contained PPU prototypes only;formal product code/three EXEs stay at P11. Preserve
all original RAM/ticks,input/audio,PPU state,resource/cache ownership,snapshot
schema and artwork. The background compositor is a pure const-state projection;
attribute reads may be avoided only when raw decoded indices prove the universal
background result. Opacity queries still use original raw indices,not output color.

| Candidate | Measured scope and disposition |
| --- | --- |
| Cached row prefill | Fill256local pixels once,then skip8pixel zero fills. Ordinary graphics-return route7.64percent shorter,no instrumented owned increase. Valid but superseded by the more selective candidate below. |
| Row prefill plus early zero-row attribute skip | Ordinary route16.11percent shorter,castle16.18percent shorter,but water4.23percent and no-zero-row-eligibility64sprite workload7.20percent slower. Instrumented owned+192bytes. Reject the occupancy-dependent regression;do not publish only its best case. |
| Single cached fetch plus bounded zero-span fill/attribute skip | Compute count once,read both packed bytes once;if both zero,fill exactly count pixels and advance without palette/attribute lookup. Nonzero and uncached paths retain complete output. Final ordinary graphics-return9.88percent shorter,water1.16percent shorter,castle9.63percent shorter;no-zero-row workload0.22percent slower. Instrumented owned+48bytes,no new heap. Select this balanced candidate for product gates. |
| Disabled-background bulk fill | Replace256individual far writes per row with the same palette0memset. Existing enabled-layer route has no gain,as expected. Explicit disabled-background/64sprite output fixture39.65percent shorter and instrumented owned16bytes lower. Select the disjoint disabled-layer optimization with explicit coverage,not a general frame-speed claim. |

Each initial candidate and the final single-fetch variant passes x86/x64 C90
comparison against the retained independent per-pixel reference:512cases,
188743680cached/uncached strip bytes and65536000VGA-plane bytes per width. Scroll,
status split,palette aliases,resource null/short/rebind,partial clipping,masks,
sprite flips/priority,guards and invalid spans remain covered. No state mutation.
A compiler may-uninitialized warning in the intermediate separated branches is
resolved by a mutually exclusive raw/cached initialization and explicit decoded
view initialization. Final native builds pass without that warning. Intermediate
warning-stopped helper calls are not passing tests;no product warning is hidden.

All ordinary candidate DOS routes compare five61440-byte active logical frames,
640000actual VGA plane bytes,8000hardware text bytes,12000neutral cells and10035-
byte snapshot bytes against retained S5. Initial mode3restores and observed live
near/far payloads free. No new allocation beyond the retained row/text,transaction
and optional cache stores. Ordinary final single-fetch peak392624versus392576,
far payload35996,stack pattern72. This is an instrumented comparison,not formal
product resident memory or all-route stack qualification.

Additional paired output-only fixtures use current four-plane conversion and
identical water/castle preparation. The final populated route compares the same
five frames,twenty complete planes,text and snapshot bytes. Its final dense case
uses an immutable source tile whose eight rows each have nonzero low|high and
fills both960-entry nametables;64sprites remain active. This removes zero-row
skip eligibility,not a claim that every individual pixel is opaque or that this
is a reachable original game state. Only output-fixture PPU fields are changed;
no source resources or game functions are rewritten. Populated final owned
393744(+48),stack pattern64matching its baseline;no inferred extra global margin.

The disabled-layer pair preserves visible64sprites and masks out only background
for its explicit final fixture. All logical pixels/planes and final snapshots
compare with its own identical baseline. That fixture exercises bulk background
initialization before normal sprite composition,including behind-background
flags when background is disabled. Other enabled-layer phases retain zero gain.
No timing benefit is attributed to an unexecuted branch.

Repeat the selected single-fetch source after explicit pointer initialization:
ordinary title/load/graphics-return/save/reload changes about-5.28/-1.57/-9.88/
-4.64/-1.58percent;populated title/load/water/castle/no-zero-row changes about
-5.28/-1.57/-1.16/-9.63/+0.22percent. Exact frames/planes/text/snapshot equality
and source fingerprints bind those final runs;older pre-initialization results
are retained separately. No settings change,compiler replacement,frame/tick
suppression or array/stack-size reduction. All probes remain ignored in build.

Similar-issue sweep covers full/partial zero patterns,all universal aliases,
left-edge mask,raw fallback,nonzero row cost,rebind/reset,pure read ordering and
sprite opacity independently of RGB. Single-fetch and disabled-layer changes
are disjoint paths;P13must verify their combined product rather than infer all
integration from separate prototypes. Expected1PPU source plus focused test
coverage,about50-140changed lines. Require native broad comparison/purity/host,
original DOS16,actual normal/failure/pressure/pixel/snapshot routes,formal product
fit and three refreshed EXEs. CRT/error-path,all-path stack and configured
cadence/input deficits remain;this scoped gain is not playable60Hzacceptance.
Extra row/OAM recovery remains TODO;no original ROM business rewrite.

Historical1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. Product hashes stay
P11;no refresh for this prototype-only part. S6/T28remain open,P13receives selected
combined read-only PPU integration and the mandatory product gates.


## S6 P13 checkpoint: combined shared PPU product adoption

Adopt the selected single-fetch zero-span and disabled-background bulk-fill
changes in one shared const PPU compositor. Packed raw bytes are read once;zero
spans fill exactly their clipped count with universal palette0before advancing.
Attributes are read only when they can affect color. Nonzero/raw paths remain
complete;opacity still queries raw indices independently. Disabled background
uses the same per-row palette0memset before unchanged sprite composition.
No core/original ROM control,PPU-state,snapshot ABI,artwork,input/tick or audio
change;no new cache,heap allocation,pixel/tick suppression or emulator settings.
Actual source/test diff2files,+48/-14.

Similar-issue sweep covers zero/partial spans,all universal aliases,source page/
scroll/status split,both mask layers,behind-background opacity,sprite order,
raw resource bounds,null/short/rebind/reset and uncached fallback. Count advances
are positive and bounded to256;zero skip never derives opacity from final color.
A new256-case deterministic test varies eight fine scroll phases/all32masks with
nonzero alias palette slots and attributes,plus a behind-background sprite
crossing the fixed/scrolled split at the right edge. It compares full and clipped
cached output to independent per-pixel reference,with guards. Existing512cases,
188743680strip bytes/65536000plane bytes and2048boundary/1198native frame/state
checks remain. Both widths pass11focused tests and13private-desktop host routes
on the rebuilt product,including input/Tab/snapshot/focus/console lifetimes.

Original OpenNT16/runtime builds the full product with unchanged flags. Existing
integral-conversion/optional OLDNAMES lookup warnings remain. MZminimum328832,
DGROUP49488/headroom16048,stack2048,max segment32768. File304307and loaded minimum
increase32bytes versus P11;this is not a new runtime work buffer. No compiler
replacement or obsolete emulator runtime is substituted.

Three actual DOS normal/cache-failure/near-far-pressure routes each match five
61440-byte active frames,640000hardware plane bytes,8000hardware text bytes,
12000neutral cells and10035snapshot bytes against retained S5. Mode3restores and
observed live near/far payloads free. Instrumented owned392608/392656/648064(last
includes ballast),far payload35996,largest minima256464/256416/1008bytes. Stack
patterns72/72/70remain bounded observations only. Cache failure/pressure use raw
fallback. Combined code,not merely separate prototypes,passes these lifetimes.

Paired populated water/castle/no-zero-row64sprite and disabled-background64sprite
fixtures also compare all five active frames/twenty planes,text and snapshots.
Current output-only total changes versus their identical P11baselines:water
-1.157percent,castle-9.633percent,no-zero-row+0.218percent;disabled background
-39.650percent. Ordinary graphics-return retains about9.88percent reduction.
These fixtures deliberately set PPU display fields and are not whole-game ROM
routes. The small measured dense cost is retained honestly;no worst-case gain
claim. Larger PPU/text/cadence and M4hardware/sound deficits are still unresolved.

Formal actual448/374KiBcaller-free routes complete game/load,Tab/text/graphics,
save and Escape. Observer takes2046samples each,one record,zero bad chains/drops;
sampled386272/382176=345136primary+160environment+40976/36880auxiliary bytes,
32above P11. Reviewed captures and CRC/resource-valid10035-byte saves advance
seed7465to7528with startup4. Samples are not a continuous peak and wall-script
frame counts are not fixed-tick equivalence/input-latency certification.
Installed configuration identity is unchanged;normal/private host protocols
are retained. MZ/file size and a successful374KiBroute do not qualify all DOS
versions or the physical25MHz486SXtarget.

Three owner-authorized existing products refreshed from current builds:

- mysmb16.exe:304307bytes,SHA256 d5771bf983e3baf77efa8e3637e1d72a86e20c7e11350d6a3486d22f24ff9c5c.
- mysmb32.exe:320139bytes,SHA256 d5a691def78183dcf48d83b31a331561ebee25773008b6a2599c7eeb59f0664e.
- mysmb64.exe:328811bytes,SHA256 b17a65cc5850ffe0c789516207331f6d93514bde6018ab9f2e750958ec17f11b.

Owner asks about direct DOS video-memory optimization during this part. Current
DOS device already writes A000directly with plane mask and memcpy;its source
initialization also selects mask15for all four planes. P14receives a contained
hardware-only experiment:when neutral plane bytes are exactly identical,compare
one all-plane masked write with four independent submissions;otherwise retain
the exact existing path. Compare any fused mapping/write alternative by complete
cost,not assumed removal of copies. Never import game/object knowledge into the
adapter or assume physical-hardware timing from DOSBox. All source pixels,plane
selection,mode/Tab/restore/snapshot semantics remain mandatory. This experiment
is not yet production code or an accepted gain;deferred row/OAM recovery stays
TODO. CRT/error/all-path stack and nominal cadence/input remain open.

Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28remain open;
all new resources/probes/logs/captures are ignored below build.


## S6 P14 checkpoint: direct-VRAM alternatives rejected by actual costs

Owner asks whether direct DOS video memory can improve performance. Current
product already selects VGA planes and memcpywrites A000;S1/P9transfer attribution
is retained. This part evaluates additional hardware-only alternatives in ignored
build. Every adapter receives neutral indexed pixels/bands only;no Mario,object,
level,RAM,OAM or CHR interpretation is added. Formal code and three P13EXEs stay
unchanged. No configuration,compiler/runtime or logical work suppression.

| Contained alternative | Measured disposition |
| --- | --- |
| Exact packed-plane equality then broadcast | Compare each whole plane against plane0;when equal,mask15and one copy write all four planes,then restore mask8. Otherwise retain four submissions. Ordinary mapping/submission0.69-1.23percent slower;populated0.70-2.93percent slower. Complete route changes are positive0.05-0.82percent. Reject:comparison cost consumes transfer savings even when many bands qualify. |
| Fused single-plane mapping directly to VRAM | Avoid packed scratch submission by selecting a plane and directing existing scalar mapper to A000. Its duplicate-row memcpyreads VRAM,so read-map is explicitly set to the same plane before mapping. Actual output remains exact,but mapping/submission34.49percent slower and graphics-return route10.44percent slower. Reject repeated source traversal/direct-store cost. |
| Conversion-time exact broadcast hint | Derive equality from each masked16-byte group's exact four-plane index relations,stop checking after a mismatch,and return the hint to the device. Saves the separate whole-plane memcmpbut adds scalar checking in conversion. Ordinary stage10.39-28.79percent slower,populated7.30-41.34percent slower;complete route1.29-11.58percent slower in tested phases. Reject rather than shipping a theoretically attractive shortcut. |

Whole-band broadcast is exercised,not merely compiled:ordinary title2of25bands
qualify,load/graphics-return/save/reload12of25;water2,castle18and dense4. Hint and
memcmp eligibility counters agree. The existing last-plane write-mask8is restored
on the broadcast path. No image is inferred from a hash or approximate equality.
The fused path's read-map selection is necessary because reads of A000can otherwise
come from another plane. Setting write-mask alone does not establish correct
repeated-row copies. Its four real readbacks verify the chosen plane relation.

Five ordinary/populated candidate routes each compare five61440-byte active logical
frames,640000actual hardware plane bytes,8000hardware text bytes,12000neutral cells
and10035snapshot bytes against their identical P13fixture. Mode3returns and observed
live near/far payloads free. No new heap work store is hidden. Instrumented owned
peaks:ordinary broadcast392976(+368),fused392752(+144),hint393296(+688);populated
broadcast394112/hint394432against393744baseline. Counters themselves occupy48static
bytes in broadcast diagnostics. All far payloads35996. Ordinary stack pattern72,
populated64match their own baselines;these are bounded patterns,not full-route
stack or formal product residency. Larger code/static overhead is reported even
for rejected variants.

The conversion hint independently passes x86/x64 C90harnesses over every legal
first row and1-16batch sizes:16972800output bytes per width,old scalar path and
coordinate formula,guards and invalid capacity/bounds. Uniform,high-bit-different
but masked-equal,and varying indexed inputs check that the hint exactly matches
memcmpof resulting plane bytes. Only nonzero-row valid hint-pointer requests are
used by this prototype;no new general API is admitted. Hardware readback establishes
actual broadcast behavior under the unchanged installed DOSBox configuration,
normal SDL and private desktop. This is not a cycle-accurate real486SXor VGA-board
speed claim. Large regressions do not justify repeat-until-fast tuning or changing
cycles/memory/scaler settings.

Similar-issue sweep covers all plane selection/read-map state,destination A000
bounds,first repeated row,four-plane equality,masked source bits,post-mask,state
lifetime,mode/Tab/restore,device-only ownership and preserved source/output bytes.
All variants are explicitly rejected;retain the P11bounded shared conversion
and bulk hardware submission. PPU/text costs and CRT/error/all-path stack plus
configured cadence/input deficits remain open. This closes the investigated
hardware alternatives only,not S6/T28or the broader optimization goal.

Next P15investigates shared presentation/receipt work rather than forcing another
VRAM variant. Use measured owners and bounded prototypes;preserve original core
and snapshot wire/rollback contracts,all text/artwork and complete output. Existing
owner-deferred row/OAM recovery stays TODO. No product edit is implied by this
read-only audit;all local probes/resources/logs/captures remain below ignored build.
Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. Products retain P13hashes.


## S6 P15 checkpoint: bounded text classification and receipt prototypes

P15 measures shared read-only presentation/receipt costs in ignored build only.
No product source,artwork,core RAM,PPU state,wire schema or three P13EXEs change.
Original DOS16 compiler/runtime,installed DOSBox configuration,normal SDL and
private desktop remain unchanged. Diagnostic route settings select telemetry,
not emulator CPU/video/memory overrides. The text scene is fully rebuilt.

Stage attribution in the diagnostic baseline:background943947PIT ticks versus
actors33726;background is96.55percent of those two text construction stages.
These are fixture-local totals,not general FPS or physical486SX measurements.

| Contained alternative | Result and disposition |
| --- | --- |
| Bulk observation record copy | Byte-identical tested records;complete-route change at most0.004percent. Reject for negligible benefit and avoid binding wire bytes to native struct layout. |
| Bulk copy plus zero-tail memcmp | Text route2.13percent shorter,graphics-return2.20percent shorter;load/save/reload0.32/1.03/0.34percent shorter. Retain as provisional evidence,not adoption:bulk/layout coupling is unnecessary and a validation-only final candidate needs its own comparison. |
| Wrapper frame-local visual memo | Text route5.82percent shorter but repeats source reads on every miss and adds more code. Superseded by integrated decoder. |
| Integrated frame-local visual memo | Text route6.0349percent shorter in two runs,background943947to876255ticks;actors33726to33727. Select for production integration proof;not yet product acceptance. |

Integrated memo holds seven unsigned bytes:valid,palette,four metatile bytes and
visual class. It lives in the scene builder's stack and is invalidated on every
build. The decoder reads the original nametable/attribute once,checks an exact
key after the blank fast path,and otherwise executes the original complete table
search and spent-block fallback. Only a completed nonambiguous result is cached;
invalid pointers and conflicting aliases keep the original early return. Caller
state/resource bindings are immutable during this synchronous build. Palette and
all four bytes are part of the key;coordinates are irrelevant to this pure visual
classification. No persistent ROM cache,allocation,workspace increase,caption,
object grouping,geometry,color,priority,opacity or gameplay change is introduced.

Two selected DOS runs each compare28files/977235bytes against the same diagnostic
baseline:five active logical frames,twenty actual VGA planes,hardware text,neutral
cells and10035-byte snapshot. Inactive text-mode logical frame is not counted.
Both outputs and probe hashes agree,restore mode3and free live heaps. Diagnostic
owned maximum393120against392848baseline(+272bytes),near payload8192/far35996
unchanged,patterned unused stack72in both;these do not establish formal product
residency,continuous peak or all-path stack bounds. Graphics-return/save/reload
cost changes are -0.0451/-0.0416/+0.0056percent,negligible fixture-local variation.
Stage6is not instrumented in this probe;its recorded zero is not zero snapshot
cost. Snapshot claims derive from exact byte comparison,not those zero counters.

Both native widths pass existing background/caption/actor smoke suites for both
memo prototypes. Independent integrated-vs-original comparisons cover128synthetic
resource/PPU fixtures per width and1536000text-cell bytes,full receipt structs,
500-byte opacity and unchanged game state. Fixtures include palette changes,
repeated tuples,blank tiles,conflicting visual aliases,two nametables,scroll and
layer-mask variations;resource contents change between calls to exercise reset.
This proves those fixtures,not an exhaustive original-ROM route matrix.

Both receipt prototypes pass5451cases each on each native width:enabled states,
producer/visible counts0through65,poisoned unused source records,full5253encoded
bytes,guards,immutable game state and5253single-byte validation mutations against
the original codec. A file-scope struct-size assertion protects the bulk prototype.
It was moved from local scope after DOS trials solely to remove a native warning;
no execution logic changes,final native checks pass. This is not a final proposed
wire-layout change or proof of all restore/error paths.

Similar-issue sweep covers all decode exits,key/palette/resource lifetime,
ambiguous/spent/blank tuples,grouping/caption/opaque consumers and both receipt
phases/counts/unused records. No core or platform game logic is introduced. P16
receives only the integrated text classification memo,plus project-owned focused
regressions:estimate one product file about20changed lines and a bounded test
extension. Before adoption require three products,focused/host tests,DOS normal,
cache-failure/pressure and populated-scene comparisons,actual output/snapshot
checks and product memory census. Receipt codec adoption is excluded until its
validation-only variant is measured separately. Extra row/OAM tuning stays TODO.

Scope/expected/actual[],new0,custody unchanged. Historical1992/1992,local1991/1992
nodes,4260/4261feasible controls(raw4342,infeasible81). S6/T28remain open;
configured cadence/input,CRT/error/continuous peak and all-path stack remain
required gaps. No global ROM certification or playable60Hz claim follows.

P15 local reproduction remains below ignored build/m3-t28-s6:run-textmemo2.py
with arguments1and2,verify-p15-repeat.py,Build-memo-diff.ps1,
Build-memo-native.ps1 and Build-receipt-native.ps1 with x86/x64arguments.
The retained source is textmemo2/background.c,SHA256
fde9a4d3533de0fea86230a63d6c0ebd688c14a95fcea52b555aed634ab5a0c6;
DOS probe SHA25633dbfc3accfb7d27cdfb97975090364cea2ba2da1f11cd78f826b39ee5056868.
Summaries p15-repeat-summary.json,p15-memo2-cost-summary.json and
p15-receipt-cost-summary.json bind the measured fixtures;native result logs
remain in textmemo2,memodiff and receiptcheck-native. These files are local
investigation receipts,not shipped assets or global certification evidence.


## S6 P16 checkpoint: integrated frame-local text classification

Adopt only the selected exact frame-local classification memo in shared text
background assembly. Seven unsigned bytes live on the builder stack;all keys
include palette and four tile bytes,reset on every build. Original blank,
invalid-table,conflicting-alias and spent-tuple fallback semantics remain.
No gameplay/state/PPU-state/tick/observer/wire/artwork/host input change,no new
heap or persistent cache. Actual product/test diff2files,+43/-2.

Similar-issue sweep covers every decode return,key and palette identity,
resource lifetime,ambiguous/unknown/blank/spent branches,readonly state and
opaque/caption/grouping consumers. Added regressions populate480repeated tuples,
change one palette-table identity,change the resource table with unchanged
nametables,and introduce/remove a conflicting alias between builds. Original
source inputs must remain unchanged;no fixture copies protected artwork.
Both widths pass14focused tests including background/caption/actors,pixel/row,
VGA/clock/root/snapshot,purity and product self-test,plus13private-desktop host
routes each. Integrated source independently matches128synthetic fixtures and
1536000cell bytes per width,full receipts/opacity/game-state checks.

Original OpenNT DOS16/runtime builds full product. Existing optional OLDNAMES
lookup warning remains;no compiler or flag replacement. MZminimum329104bytes,
DGROUP49488/headroom16048,stack2048,maxsegment32768. Product file and minimum
increase272bytes;no runtime work allocation is added.

Four contained DOS routes(normal,cache failure,pressure,populated PPU fixtures)
each match977235bytes:five active logical frames,twenty actual VGA planes,
hardware text,neutral cells and10035snapshot bytes. Independent coordinate
formula checks every hardware byte. All free live heaps and restore mode3;
raw cache fallback runs in failure/pressure routes. Complete text stage is
6.0367/6.0392/6.0402/6.0370percent shorter,ordinary graphics-return/save/reload
-0.0451/-0.0416/+0.0056percent changes are negligible. Populated PPU mutations
occur in the graphical phases;this is not distinct water/castle text timing.
Stack patterns72/72/70/64are bounded observations. Ordinary diagnostic owned
393008,populated394128,far payload35996;pressure648064includes intentional
ballast and must not be called product residency. Library regrouping failures
from duplicate owners are rejected attempts;final probes exclude explicitly
replaced modules and all output checks pass.

Formal product448/374KiBcaller-free game/load/input/Tab/save/Escape routes pass:
- 448KiB:sampled386544bytes,2049samples,seed7465to7529;CRC/resource-valid save and three capture files.
- 374KiB:sampled382448bytes,2049samples,seed7465to7529;CRC/resource-valid save and three capture files.
Sampling is not continuous peak or all-path stack proof. Primary345408and
environment160bytes plus auxiliary40976/36880give the recorded maxima;each is
272above P13. Reviewed448KiBtext/returned graphics captures preserve the scene.
Installed configuration hash/settings remain unchanged;normal SDL private
surfaces never switch the owner's desktop. Routes do not certify physical486SX,
all DOS versions,nominal60Hz or input-latency budgets.

Three existing owner-authorized product artifacts refreshed and verified:
- mysmb16.exe:304579bytes,SHA2563c78b95adf78e7124f1d9a0cdae2ca8d804540b581a029acd7def621257f5cc5.
- mysmb32.exe:320139bytes,SHA25677b8d1100be2f2d8b4a7b2f3f791d01df3edab41d515ab447b9447207cab9785.
- mysmb64.exe:329323bytes,SHA2566ddcf579b4809602e8f679e740cae4f86ea17e3eff6a63850d0054574c940f06.

Local reproduction scripts Build-p16-product/native/host/diff and run-p16normal,
run-p16fail,run-p16tight,run-p16pop plus run-p16resident-game with448/374are retained
below ignored build/m3-t28-s6. verify-p16-device.py,verify-p16-resident.py and
check-p16-products.py bind result summaries and product hashes. No new resource,
trace,generated source or probe binary is tracked. Only the three previously
owner-authorized EXEs are retained under their existing exception.

Scope/expected/actual[],new0,custody unchanged;historical1992/1992,local1991/1992
nodes,4260/4261feasible controls(raw4342/infeasible81). S6/T28remain open.
Next P17measures the validation-only receipt zero-tail alternative without bulk
struct serialization;product memo baseline is retained. Required cadence/input,
CRT/error/continuous-peak/all-path stack gaps are not discharged by this P.


## S6 P17 checkpoint: validation-only zero-tail alternatives

Contained probes use the P16memo baseline and original field-by-field receipt
serialization. Capture/read_buffer/schema/restore and observer producers remain
unchanged. Product code/three EXEs remain P16. Two alternatives replace only
validation work;no native struct-to-wire copy is admitted. Original OpenNT16,
normal SDL/private desktop and installed DOSBox settings remain unchanged.

| Candidate | Complete-route cost and memory disposition |
| --- | --- |
| Per-record memcmp against forty constant zero bytes | Load/text/graphics-return/save/reload0.324/2.260/2.156/0.990/0.335percent shorter. Diagnostic owned392992against393008baseline(-16bytes);far35996 and stack pattern72unchanged. Select for product integration proof:retains validation order and most benefit with the smaller observed footprint. |
| Whole-tail adjacent-byte equality with zero first byte | Two runs match,load/text/graphics-return/save/reload0.384/2.633/2.497/1.140/0.385percent shorter. Diagnostic owned393088(+80bytes),far35996 and stack72unchanged. No zero pattern is needed but helper/code cost outweighs that storage reduction in this build. Supersede for current adoption:extra0.37percentage-point text gain costs96more observed bytes versus the selected candidate. |

The selected candidate introduces a40-byte constant zero pattern and replaces
only the original40-byte scalar scan of each unused record with exact memcmp.
Its lower total diagnostic footprint is measured compiled code/data,not a claim
that the constant occupies no storage. Active record checks,owner checks,count
bounds and disabled-receipt validation retain their original order. No new
heap,resource cache,game/object interpretation or platform branch is added.
Formal DGROUP/headroom/loaded and resident budgets remain P18adoption gates.

The adjacent candidate is mathematically exact:for a bounded nonempty sequence,
first byte zero plus every adjacent pair equal proves every byte zero. Read-only
memcmp operands may overlap;zero count short-circuits before any dereference.
Count bounds precede tail arithmetic,and zero-length tails may point one past
valid storage. No extra sentinel may be read. The tested implementation also
uses this helper for disabled receipts;that change is not selected for adoption.

Each alternative passes11279original-vs-candidate cases on each native width:
enabled states/counts0through65,full5253capture bytes and guards,immutable game,
single-byte mutations across enabled records,all5252disabled tail positions,
255uniform nonzero disabled encodings,and valid/first/last unused-byte checks
for both buffers at every count0through64. Both widths first passed the retained
5451case corpus as well. Valid count64has an empty unused tail;count0checks all
unused records. Invalid canonical inputs remain rejected;wire bytes remain exact.
These cases do not certify every transactional restore/error path.

Selected DOS route and two adjacent route runs each match977235bytes against
the freshly linked P16-equivalent codec baseline:five active logical frames,
twenty VGA plane readbacks,hardware text,neutral cells and10035snapshot bytes.
All restore mode3and free live near/far payloads. Source/code-only changes are
isolated in the codec;other probe owners are the same. No extra heap is hidden.
The underlying snapshot stage counter is uninstrumented and stays zero;cost
claims are whole-route differences,not that snapshot computation is free.
These ordinary fixture-local savings are not60Hz or physical486SXqualification.

Similar-issue sweep covers both phase buffers,count/overflow/owner bounds,
unused first/last bytes,disabled encoding,active source-size/family/OAM fields,
all read/write/capture paths and zero-pattern lifetime. Original serializer,
restore and snapshot schema have no changes. No general memcpy layout shortcut.

Local evidence below ignored build/m3-t28-s6:prepare-p17.py,Build-p17base,
Build-p17memcmp,Build-p17adjacent,Build-p17-extended with x86/x64arguments;
run-p17base/memcmp/adjacent and verify-p17-cost.py. Native result logs live in
p17-native. Run-adjacent arguments1and2select diagnostics,not emulator settings.
P18receives selected per-record validation integration:one product file about
three changed lines plus a bounded canonical-tail regression extension;three
products,focused/host/DOS fallback-pressure/populated equality and actual memory
routes are required before adoption. No product refresh is needed for this
prototype-only P. Deferred row/OAM work remains TODO.

Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28remain open;
configured cadence/input and CRT/error/continuous peak/all-path stack remain gaps.

Selected codec SHA2569d5a53422c40f282cadd3e981659bb9274430537194ec6028510f8bf6dfaa785.


## S6 P18 checkpoint: canonical unused-record validation integration

Adopt only the per-record exact memcmpagainst a40-byte constant zero pattern.
Original active-record checks,owner checks,count limits,disabled-receipt loop,
field serialization,capture and restore order remain unchanged. No core,PPU-state,
wire layout,artwork,input/tick change or native struct-to-wire shortcut;no heap
allocation. Source/test2files,+44/-2. The constant is real storage,not free memory.

Similar-issue sweep covers both receipt phases,all unused record boundaries,
active family/OAM/sprite fields,count/overflow/owner limits,disabled bytes,
capture and rollback/restore consumers. Added canonical-contract tests exercise
13703valid/invalid cases per width:all counts0through64,first/last byte of every
unused record in both buffers,and every disabled trailing byte. Independent
original-vs-integrated11279case comparison additionally checks capture bytes,
guards,unchanged game state,enabled states/counts0through65 and mutations.
Both widths pass15focused tests including observation and continued snapshot
routes plus13private-desktop host groups. The observation suite retains its
1000-step twin/core/frame/pixel checks and immediate/240future-tick restore
contracts;these finite routes do not credit unobserved original-ROM nodes.

Original OpenNT16/runtime builds full product. MZminimum329120(+16versus P16),
DGROUP49520(+32)/headroom16016,stack2048,maxsegment32768,191segments.
File305115(+536)is distinct from loaded minimum and actual runtime occupancy.
Do not report prototype-16as a product-memory saving without the formal census.
Optional OLDNAMES lookup warning is retained;compiler/runtime/flags unchanged.

Four actual DOS normal/cache-failure/pressure/populated probes each compare
977235bytes against their identical P16fixtures:five active61440-byte frames,
twenty hardware VGA planes,hardware text,neutral cells and10035snapshot bytes.
Every VGA byte also matches the independent coordinate formula. All live heaps
free,mode3restores;failure/pressure exercise raw cache fallback. Stack patterns
72/72/70/64remain bounded receipts,not all-path proof. Far payload35996unchanged.
Normal diagnostic owned392992(-16versus P16);failure393040,pressure648064includes
ballast,populated394112. Text-stage costs2.260/2.272/2.272/2.261percent shorter;
normal graphics-return2.156and save0.990percent shorter. Populated graphical
fixture costs essentially unchanged;its text phase is ordinary before injected
PPU mutations. Zero snapshot stage counters are uninstrumented,not free work.

Formal actual448/374KiBcaller-free product routes complete load/input/Tab/text/
graphics/save/Escape,with CRC/resource-valid10035-byte saves and capture files:
- 448KiB:sampled386528bytes,2053samples,seed7465to7531.
- 374KiB:sampled382432bytes,2053samples,seed7465to7531.
Primary345392and environment160plus auxiliary40976/36880give those maxima;
formal sampled occupancy is16below P16although minimum-loaded increases16and
DGROUPincreases32. This illustrates why file,min-loaded and observed occupancy
must be measured separately. No continuous-peak,all-path stack,physical486SX,
all-DOS-version or nominal60Hz/input-latency qualification is inferred. Installed
DOSBox configuration is unchanged;normal SDL/private surfaces remain isolated.

Three existing owner-authorized product artifacts refreshed:
- mysmb16.exe:305115bytes,SHA256771b21c726c17ab57c4b2ff8e479441590ae2cad27aa61a8c12818580aab504a.
- mysmb32.exe:320651bytes,SHA256beb301aa1c7fc7729efaaf610d56276b129fa40b6a98b56a861a2400cf0cc00b.
- mysmb64.exe:329323bytes,SHA256681b45e879cc42c2b34be7884fc40cc360cfcb2be830ab51bde6623db8830a44.

Local P18build/host/diff/device/resident scripts and result summaries remain
below ignored build/m3-t28-s6. Build-p18-product/native/host/diff,run-p18normal/
fail/tight/pop,run-p18resident-game448/374and verify-p18-device/resident plus
check-p18-products bind the evidence. No new probe,ROM,derived data or research
artifact is tracked. Only the existing three EXEs retain the owner exception.

Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28remain open.
Next P19prioritizes the existing CRT/error/continuous-peak/all-path stack gaps:
read-only bounded allocation/compiled-stack census,with any contained probe
specified before use. No further small receipt prototype or deferred row/OAM
activation. Configured cadence/input deficits remain visible,not discharged.


## S6 P19 checkpoint: product-bound allocation and compiled-frame census

Read-only P19binds current P18products to allocation and stack facts. No product
source or three EXEs change,no new original-ROM node audit. Existing owner-local
OpenNT16/compiler plus historical runtime remain the reviewed local build tools;
project-owned C is compiled with original flags plus diagnostic listing output.
No third-party source is imported,no redistribution qualification is inferred.
Raw listings/objects remain ignored below build;tracked evidence is neutral
metadata only. Bound160product-owned units,less than8MiBlistings/2MiBobjects;
source/object hashes and output counts are retained. Cleanup belongs to S6when
these bounded inputs are no longer needed. Generated resource-only units and
runtime binary implementation are excluded from the owned-frame census.

160own compilation units regenerate successfully. Comparing each original and
listing object proves equal CODE segment definitions/bytes,fixup records and
external definitions for160/160;source and object hashes bind each comparison.
Thus listing frame sizes belong to current compiled owners,not a different
compiler/optimization model.850Local-Size entries are extracted. These are C
compiled entries,not850ROM nodes or new conformance matches.

| Current compiled function | Local bytes | Saved prologue bytes | Interpretation |
| --- | --- | --- | --- |
| DOS composition main | 570 | 6 | Includes two260-byte startup path buffers and local hook/file structs;its frame persists throughout the loop. |
| File replace callback | 526 | 6 | Two260-byte paths coexist during replace;called after the pending file is closed. |
| Shared PPU background row | 320 | 6 | Caller-owned row/opacity work must be counted in graphical call depth. |
| File open callback | 266 | 6 | One260-byte path plus local FILE pointer. |
| File error logger | 266 | 6 | One260-byte path;stdio/formatting stack is additional. |
| File remove callback | 262 | 6 | One260-byte path. |
| Shared text actor scene | 158 | 6 | Read-only actor assembly,not a platform gameplay function. |

These columns exclude arguments,return addresses,callee frames,CRT and hardware
interrupt entries. Never sum unrelated functions or present the largest local
frame as the complete stack bound.8functions contain23indirect call sites;
29external symbols remain unresolved by the own-source census,including memory,
stdio,arithmetic and DOS/device services. Callback targets and interrupt/BIOS
stack joins must be reconciled before all-path acceptance. The keyboard ISR has
its own compiled save/local sequence in addition to CPU interrupt frame and
callee work. Retained probe pattern72/70/64belongs to those instrumented routes;
it is not high-water proof for the different formal-product main.

Allocation sweep across the linked product owners finds four explicit sites:
required15400-byte exclusive presenter and20084-byte transaction store;optional
8192-byte cache first near,then far. Required far payload35484;observed file
buffer adds512to35996when cache is near. A successful far cache can add8192;
optional failure retains raw rendering. These are payload bounds,not MCB/CRT
allocator block bounds. No allocator call is found in shared core/PPU/text/IO.
The historical stdio header declares512-byte BUFSIZand20stream slots;that header
alone does not prove runtime allocation or a complete CRT upper bound.

The production file callbacks have two fopenowners:save/load and error logger.
Source-order review finds at most one application-owned FILE live:save closes
before replace/remove/log;load closes before decode/error log;open/encode failures
have no open handle. close_file calls fcloseeven if fflushfails. No product
stdout/stderr printing owner is found;the only fprintfis the snapshot log.
Executable path reads the existing PSP environment and copies into supplied
buffers;directory/file-service initialization copies the directory and callbacks
into persistent owners. No startup path pointer is retained. These source facts
reduce pending cases but do not prove hidden runtime/DOS scratch or allocator
continuous peaks. The external FIT observer is periodic and can miss short-lived
blocks;its sampled maxima remain accepted within that limitation.

The specific actionable lifetime defect is startup-only main scratch retaining
520path bytes during every frame,save/load,render and keyboard interruption.
P20receives a composition-root startup lifetime refactor:move existing startup
sequence into an initializer,return before the main loop,keep all existing calls/
cleanup/resource binding order. Local hooks/files are copied by the receiving
root/store,and directory bytes are copied by file storage;retain those ownership
proofs. Do not replace stack scratch with globals or a new allocation. Estimate
one root file about20-30structural changed lines,plus a focused owner/lifetime
check if needed. Verify actual compiled startup/loop frames,code/state/output,
three products,normal/failure/pressure paths and formal448/374KiBmemory routes.
Do not shrink the2048-byte stack or claim total memory savings until startup,
CRT,error and interrupt bounds are proved. Startup adds one wrapper call,so its
peak must also be measured rather than inferred from the smaller loop frame.

Local reproduction:prepare-p19-listings.py,Build-p19-listings.ps1,
verify-p19-bindings.py,analyze-p19-stack.py and bound-p19-output.py under ignored
build/m3-t28-s6. p19-source-bindings/object-bindings/stack-frames/stack-summary
JSON bind850entries to160units. One exploratory compiler help request hung;only
that explicitly identified help process was stopped. Listing compilation with
normal tool paths succeeds;no toolchain replacement or product evidence credit
comes from the failed help request. No new program-input trace is generated.

Scope/expected/actual[],new0,custody unchanged;historical1992/1992,local1991/1992
nodes,4260/4261feasible controls(raw4342/infeasible81). S6/T28remain open.
Pending clauses are named:callback/CRT/interrupt stack joins,allocation-service
continuous peak and error routes,configured cadence/input. No whole-ROM audit
restart,aggregate certificate or silent deferred row/OAM activation.


## S6 P20 checkpoint: startup scratch expires before the game loop

Move the existing DOS composition startup into a static initializer. Caller
maps initializer failure to the original exit1;startup statements/order,resource
binding,optional file setup,cleanup and the complete loop/exit suffix normalize
identically to P18. No shared game/PPU/IO/wire/artwork change,new allocation/global
scratch or stack-size reduction. Source/test2files,+14/-4. root hook lifetime
regression clears the caller descriptor after initialization and then executes
input/audio/video/exit;copied callbacks remain valid. File directory/services
already copy their values into persistent owners,no startup pointer is retained.

Compiler listing binds exactly to the new product root object;159other owned
units retain equal CODE/fixup/extern records. mainlocals570to2,saved prologue6
unchanged;initializerlocals570. Gameplay root frame falls576to8bytes. Startup
has the additional caller frame8and far return4,so its own-chain cost grows12;
no complete stack-safety inference follows. Existing2048stack,DGROUP49520and
headroom16016remain. DOS file305163/minimum329168each+48versus P18;this change
improves runtime stack margin,not allocated conventional-memory size or FPS.

Both widths15focused tests/13private-host groups pass;Windows binary hashes
remain P18. Actual new DOS product448/374/373KiBcaller-free routes pass startup,
input/load,Tab/text/graphics,save and Escape with valid resource/CRC snapshots
and three captures. Required resources and callback lifetimes survive initializer
return. Installed configuration/SDL/private protocol unchanged. Sampled maxima:
- 448KiB:386576bytes,2053samples,seed7465to7531.
- 374KiB:382480bytes,2053samples,seed7465to7531.
- 373KiB:381712bytes,2053samples,seed7465to7531.
373KiBshows auxiliary35856to36112(+256)around file activity;primary345440and
environment160remain.372KiBactually executes then returns1without completing the
route;not a successful run and no exact failure-site claim is added. This brackets
this fixture's whole-KiBbudget at372failure/373success,not a universal gameplay
minimum or continuous peak.448/374sampled bytes increase48versus P18. No stack
shrinking,nominal cadence or hardware/version acceptance is claimed.

Similar-issue sweep checks all startup error returns,hook/file/directory copy
lifetimes,static callback anchors,shared storage views,allocation/free provenance,
resource binding and shutdown suffix.159unchanged compiled owners preserve P18
pixel/plane/text/snapshot and cache-failure/pressure receipts within their existing
fixtures;four unmodified producer probes were rebuilt but not rerun or counted as
new runtime evidence. Actual composition runs are used for the changed lifetime.
This avoids repeating unaffected render work while retaining the required joins.

Three existing owner-authorized product artifacts refreshed:
- mysmb16.exe:305163bytes,SHA256886f48abccaef2d450f8e375f0fdb5d671ad4289a87abceb3c13266ff3f623cd.
- mysmb32.exe:320651bytes,SHA256beb301aa1c7fc7729efaaf610d56276b129fa40b6a98b56a861a2400cf0cc00b.
- mysmb64.exe:329323bytes,SHA256681b45e879cc42c2b34be7884fc40cc360cfcb2be830ab51bde6623db8830a44.

Local build/native/host scripts,root listing and source normalization,compiled
binding checks,resident448/374/373/372and verification summaries remain below
ignored build/m3-t28-s6. verify-p20-bindings.py and verify-p20-resident/lower.py
bind changed/unchanged owners and actual child results;check-p20-products.py
binds three products. No new ROM,derived source,probe binary or raw trace tracked.

Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28remain open.
P21receives bounded allocation-event/CRT/interrupt stack evidence for existing
remaining clauses;no stack shrinking before proof. Retain P20startup/runtime
tradeoff and P18render gains. Cadence/input gaps and deferred row/OAM TODOremain
explicit;no whole-ROM audit restart or final certificate follows.


## S6 P21 checkpoint: product-bound CRT and startup allocation events

Read-only P21uses the existing owner-local historical compiler/runtime,license
and redistributability not newly qualified;no implementation is imported. Raw
runtime CODE/entry listings stay ignored below build. The isolated /MAPrelink
is byte-identical to P20product(SHA886f48abccaef2d450f8e375f0fdb5d671ad4289a87abceb3c13266ff3f623cd).
29previous external symbols resolve in its linked runtime region11050bytes.
79public addresses are decoded independently;not all public labels are functions.
Initial linear decoding misaligned after embedded data;discard its affected
prefix interpretation. Restart from exact symbol addresses before inspecting
entry prefixes/call targets. Private/internal paths still require control-flow
review;this is not a completed29routine stack certificate.

Linked CRT __getbufrequests512bytes from far mallocand falls back to aone-byte
buffer on failure. This is actual linked-code evidence rather than BUFSIZheader
inference;the fallback can make file IO expensive under pressure. __outputuses
a10-byte request through the runtime stack checker;this excludes callers,
private helpers and saved registers. Runtime allocation uses DOS48/4Aservices,
and startup resizes the original primary block. Arithmetic/IO wrappers and
interrupt/BIOS joins are still separate obligations. Archive metadata confirms
DOS open/close/read/write and setvbufexports in the existing210877-byte runtime;
no source or implementation copy. A later direct DOS file-service candidate
could remove stdio buffering/formatting dependencies,with full byte/error/close/
append/partial-transfer compatibility proof first;no gain or adoption claimed.

Named missing condition in P18/P20FIT receipts:18Hzsamples started after CRT
startup trimming and therefore did not see the earlier DOS-loader reservation.
MZmaximum-extra is65535;the CRT later clips its data-segment span to4096paragraphs.
Map-derived safe candidate retains that full64KiBDGROUParena,setting maximum
extra to3076paragraphs(minimum2076,image18497paragraphs). No smaller near arena,
stack or cache reserve. The affected owner is build/load metadata,ROM scope[].
Impact is unnecessary temporary use of caller-free memory before game startup,
not a new gameplay defect or lower mandatory stable-resident requirement.

Declared contained external observer hooks INT21and1c,walks bounded512MCBheaders,
records up to256changes and delegates original vectors. No DOS/stdio/allocation
inside callbacks;all output is after restoration.150seconds per route/2MiBlogs,
normal SDL/private desktop and unchanged installed DOSBox configuration. It
observes DOS-service boundaries plus timer samples,not hidden kernel-internal
transients. Observer code/data live in the parent;its interrupt frame temporarily
uses caller stack,so do not use it as formal stack-high-water or cadence evidence.
No raw game RAM is logged. Observed chain/errors/drops are explicit gates.

Clone changes only bytes12/13,MZmax-extra65535to3076;checksum field is zero and
all other bytes,loaded image and resource identity are identical. Paired448KiB
actual original/capped routes pass load/input/Tab/text/graphics/save/Escape with
exactly equal10035-byte save and three captures. Both record2055timer samples,
74DOS calls,four changes,zero bad chains/drops. Service-boundary ownership:

| Phase | Original bytes | Capped bytes |
| --- | --- | --- |
| Initial loader primary plus environment | 458752 | 346096 |
| After CRT trim | 345600 | 345600 |
| After required presenter | 361040 | 361040 |
| After required transaction arena | 386576 | 386576 |

Boundary maximum458752to386576,saving72176bytes(70.484375KiB)in this route.
Stable residence unchanged;no FPS or universal minimum claim. Initial capped
primary345936is496above byte-image prediction345440;this matches the496difference
between byte-paragraph and full512-page image rounding. That is an inference,
not a portable exact-loader-size guarantee. Retain full64KiBbound;do not shave
those496bytes without cross-loader proof. Whole-KiB373pass/372failure belongs
to unmodified P20;the capped low-budget route remains an adoption requirement.

Similar-issue sweep covers MZminimum/maximum/checksum,image identity,DGROUP/
stack/near reserve,CRT trim,all direct syscall hooks/vector restoration,MCB
owner/environment/auxiliary accounting,drops/bounds and file-buffer fallback.
This resolves the named sampling blind spot for the measured startup route;
not all-phase/all-path CRT/kernel peak or interrupt stack certification.

P22receives build-metadata adoption of the map-derived MZmax-extra bound:extend
the DOS build/verification owner and synthetic malformed/boundary/idempotence
checks,then build/validate three products. Preserve minimum/checksum policy,
image bytes,64KiBarena and original toolchain;report byte-image and page-rounded
estimates separately. Require nonhooked actual373/374/448and the startup-failure
boundary plus external-event verification before adoption. No core/PPU/source
logic change,no emulator tuning,stack shrinking or deferred row/OAM activation.

Local ignored reproduction:prepare-p21-map/extract-p21-crt/restart-p21-entries,
inspect-p21-runtime-exports/inspect-p21-mz,prepare-p21-loader.py and external
original/capped448routes plus verify-p21-loader.py. CRTCODE<16KiB,entry listings
<512KiB;all records/hash manifests remain below build/m3-t28-s6. Probe-only P21
leaves three P20products unchanged. Cleanup remains S6's responsibility.
Historical1992/1992,local1991/1992nodes,4260/4261feasible controls(raw4342,
infeasible81),scope/expected/actual[],new0,custody unchanged. S6/T28remain open;
private CRT paths,interrupt/kernel bounds,error routes and cadence/input remain.
