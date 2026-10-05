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
