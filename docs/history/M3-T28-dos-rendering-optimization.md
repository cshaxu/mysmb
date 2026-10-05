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

## Opportunities and suggested order

| Priority | Opportunity | Bounded implementation and correctness obligations |
| --- | --- | --- |
| 1 | CHR decode cache | Decode bound immutable CHR into palette-independent pixel indices once;share the cache between background and sprites. Preserve bounds/absent-resource behavior,flips and transparency. Rebinding resources invalidates the cache;palette animation uses current palette values,never cached final colors. Evaluate full versus bounded cache using actual DOS memory headroom. |
| 2 | Background calculation reuse | Prepare the palette once per frame and reuse tile-row/attribute/address calculations where their inputs are identical. Preserve status-bar split,scroll,mirroring,pattern-bank selection and left-edge masks. Do not cache across a changed visible-state input without an explicit invalidation rule. |
| 3 | Sprite background-occlusion reuse | Retain background opacity information while composing the background;behind-background sprites query that information instead of re-decoding background pixels. Preserve sprite order,transparent pixels,clipping and mask semantics. Select a bounded bit representation after measuring its memory and access cost. |
| 4 | Repeated stretch-row reuse | In the240-to400-row enlargement,convert each unique source row once per plane and copy duplicate output rows. Preserve the exact current coordinate mapping,all pixels and four32000-byte planes. This reduces repeated conversion,not the required complete output or its video-memory writes. |
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
measured cumulative performance result with unresolved limits visible.
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

