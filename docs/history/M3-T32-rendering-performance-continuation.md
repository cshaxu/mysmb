# M3 T32: rendering performance continuation

## Admission and boundaries

Owner explicitly closes T31 and admits the next performance T. Coordinator
accepts its named unfinished work here; this is a continuation of the finite
performance/memory goal, not a new whole-ROM audit. Baseline is T31 S6 P2
source and its three products; P3 text candidates are still prototypes.
Original DOS compiler/runtime, DOSBox settings, 2048-byte stack and current
exclusive presentation store remain. No game/PPU-visible semantics, source
rows, ticks, frames, colors, glyphs or input information may be lost. No helper
process, system terminal setting change or new resource import.

Existing owner-local ROM/runtime bindings have local research/build purposes
only under the source policy, with no new copying or redistribution. Raw
fixtures, protected derivatives, generated outputs and logs stay under build.
Only the existing three explicitly owner-authorized EXE slots are refreshed
when product code changes; they are not release or whole-ROM proof.

## S plan

1. S1 integrate bounded text object-coordinate math. Entry is private object
   drawing in src/text/background_scene.c; exit is identical authored frame,
   ownership workspace and receipt. Receive selected T31 object-row prototype.
   Estimate40-80 changed source lines plus focused regression as needed; no
   public ABI, resource binding, heap, persistent cache or template change.
   Retain first-cell rounding, signed origin differences and component order;
   narrow only after proven coordinate domains, hoist row invariants. Reuse
   byte-identical prototype evidence:396 comparisons per width,977235 DOS
   output bytes and72030 colored/monochrome view bytes. Diagnostic whole-text
   16.6194%shorter/-144owned bytes is not actual product saving or FPS. Adoption
   requires current source binding, native focused tests, original DOS compile/
   link/listing, actual memory/mixed-mode route and all three products. If the
   product differs or regresses, repair or reject within this S.
2. S2 dominant graphical background compositor. Owner src/ppu/frame.c,
   frame_build_internal -> background_row -> sprite composition. Current
   diagnostic PPU457.5ms/about64.2%ofgraphics step. Inspect generated original
   compiler loops before changing code: far pointer traffic, redundant division,
   bounded CHR/tile traversal and row-invariant work. Estimate60-180 candidate
   lines after evidence, no new full framebuffer/cache by default. Benchmark
   a bounded cohort together, select only meaningful speed/memory tradeoffs.
   Independent native512-case indexed output/guards plus original DOS ordinary,
   populated, cached/far/raw fallback, scroll/split/opacity/palette receipts.
   No changed NMI, OAM, PPU state, priority or producer timing.
3. S3 neutral palette mapping/submission. Owners src/io/ video mapping and
   src/platform/vga/vga_frame.c, only neutral indexed pixels to identical plane
   bytes. Current mapping197.6ms/about27.7%ofgraphics step. Estimate40-140 lines
   after profile; prefer bounded arithmetic/pointer simplification or removal
   of repeated conversions within existing synchronous band lifetime. Maintain
   full256x240 borderless640x400 scanout, all masks, palette colors and rows.
   Independent plane/scaling test and original DOS bytes/cost/stack/resident
   checks; no game/resource inspection in platform. Reject memory growth that
   prevents startup even if faster; document each selected/rejected tradeoff.
4. S4 final integrated performance/memory receipt. Receive MEM-S4-01..05 from
   T31 S6 now, as backlog only while S1-S3 execute. Reuse retained own/CRT/
   startup/IRQ9/file/error/arena proofs where dependencies apply; do not restart
   the census. Reconcile changed locals/callers and missing startup, fatal,
   firmware, kernel/contiguous and cadence clauses by their exact IDs. Estimate
   0-200 harness lines, no stack shrink without joined proof. Run final actual
   products graphics/text/Tab/save/restore/exit, report time/input/memory and
   tested startup budgets separately. Unsupported global/physical claims stay
   pending, not passed. Physical486SX qualification stays M4.

S1-S3 are closed; S3 pending host-startup acceptance is explicitly received by S4 below. S4 is the sole active integration executor and receives
backlog. The owner has since added [S5-S9, resolution-matched DOS graphics performance](../proposals/m3/dos-graphics-nesticle-performance.md) to this same T32.
These are five consecutive S tasks: S5 baseline/comparator, S6 PPU, S7 DOS
display, S8 residual 16-bit cost, and S9 final acceptance audit. S9 receives
the original proposal's last-stage closure work and does no product repair.
None is active or separately queued. S4's five clauses and suspended Windows
startup dependency retain their existing status and cannot be silently
transferred. Automatic next-S admission requires scoped S4 closure or explicit
owner-directed transfer and a fresh S5 packet; each later S requires its
predecessor's closure and its own fresh packet. T32 does not close before S9.
Each S starts with components/scope/size, ends with actual changes, candidate
dispositions and total/local counters. Product-code P builds/tests/publishes
DOS16/x86/x64; evidence-only P does not regenerate them. No remote exists.

## Acceptance and finite transferred register

S1 owns selected object-row adoption, S2 graphical PPU cost, S3 neutral mapping
cost. S4 owns MEM-S4-01 pre-main/env/args,02fatal/exit/hooks,03firmware/interrupts,
04continuous/kernel/contiguous memory,05final integrated cadence/stack.
Acceptance attribution is coordinator under the owner's explicit T31 closure/
next-performance mandate. Do not mark any received gate verified from transfer.
Retain original limits; new concrete findings require visible scope amendments.

Each adopted candidate must preserve output/state and improve a useful measured
time/memory tradeoff under unchanged tools/settings. Pure probes are not product
FPS. T closure joins selected source/build identities, all S output proofs,
actual routes, S9's equal-frame audit and explicit status of every received ID. Required open gates
prevent successful verification closure; only explicit owner-directed receiving
transfer may close administratively. The owner-requested S5-S9 comparison is an
explicit target, not a result inferred from the earlier T32 probes. Do not infer
whole-game bug absence from finite tests.

All S scopes/expected/actual ROM labels are[],new0,baseline/max1992/1992.
Historical1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342,
infeasible81) remain unchanged. No ROM custody event. Full M2 final certificate
remains incomplete in the queue tail, separate from presentation optimization.

## S1 P1 admission receipt

No product changes yet. Existing selected prototype has local scene/coordinate
domain proof and original generated listing locals64versus58; background-build
locals50unchanged. S1 must retain signed long differences before range-checked
16-bit divisions and preserve masks/inset/component membership exactly.
Review the source diff before adoption; original ordinary/populated and native
matrix receipts may be reused only for identical candidate behavior.

Reproducible contained inputs:build/m3-t31-s6/prepare-object-math.py,
object-row/background.c,object-row-summary.json,text-phase-summary.json,
text-views-summary.json and both-width background-matrix logs. Final logs and
admission evidence go under build/m3-t32-s1. Existing three products unchanged.

## S1 P2 closure: bounded authored object row math

Adopt selected row math only in src/text/background_scene.c,+19/-9lines.
Private centers use unsigned16-bit multiplication/division after x0..79/y0..49
guards:maximum center numerators20352/11880; signed short origins retain long
differences before nonnegative checks and narrow divisions. Maximum nonnegative
dx/dy33022/33005 fit unsigned16. Original first_cell negative rounding remains.
Hoist ycenter,source row and pure inset once per row;component membership,
palette,opacity masks,glyphs,ownership and writes stay unchanged. No public ABI,
heap,workspace,cache or persistent storage growth. Local object64versus58bytes;
background-build50unchanged. Do not shrink2048stack or infer a global bound.

Current source tokens equal the selected prototype except comments/whitespace.
Fresh complete background comparisons396each native width pass; all14focused
tests each width pass, including text/background/captions/actors,snapshot,
pixel/plane,performance,purity andself-test. Both actual stripped Windows
products pass144DPI768x720startup,three native80x30text entries,two graphic
returns andEscape. Packaging preserves all runtime section bytes/RVAs.
Retain source-identical DOS977235-byte route and72030-byte colored/monochrome
water/castle/dense view comparisons. Original diagnostic whole-text saving
16.6194%is scoped seeded cost,not measured product FPS or configured playability.

Original toolchain actual DOS product301561bytes,-144. DGROUP49072/headroom16464,
stack2048,max-extra3079unchanged;logical loader minimum325680/max342128bytes,
page-rounded same values. No dynamic heap in loader estimate. Actual370KiB
route passesload,input,Tab,text/graphics,save,restore,Escape:2033samples,no invalid
or dropped MCBrecords,observed378672bytes(-144from preceding same-budget case).
SaveCRC/resource binding valid,frame7548versus seed7465. Captured text view has
HUD,cloud/terrain/player and color output; three640x400captures are not exhaustive
visual proof.369KiB stillEXECsucceeds and returns1cleanly,seed save unchanged.
Sampled peak and tested startup budgets are not universal/continuous maxima.
DOSBox settings hash remains unchanged,normalSDL/private desktop,no foreground UI.

Three source-bound products published to existing owner-authorized slots:
- mysmb16.exe:301561bytes;3e9585b9fe568f2a3e269c1500a5b2b70104793fe463e7ac61b5981b87f15656.
- mysmb32.exe:311310bytes;391f6679dd9c3d4020d5c41073d55f0e3205ab35c2c66a3b6956f90edcc2630e.
- mysmb64.exe:324110bytes;1221205990c3d99fe2dda210d8343ad647c0d2169875ea6916f0bcbe7bf8ce80.
Contained recipes/results below build/m3-t32-s1:Build-Product/Build-Native,
strip-products,verify-current-native,run-product-resident,verify-resident,
source binding,memory receipt,native tests andactual Windows routes. Existing
owner/runtime material only,no new import or redistribution authorization.

Similar-issue sweep covers all private object callers/signed origins/rounding,
split/left masks,component membership,inset side effects(pure),glyph omissions,
palette animation andwater/castle/monochrome. No changes to core orplatform.
S1scope/expected/actual[],new0,custody unchanged,historical1992/1992,local1991/1992
nodes,4260/4261controls(raw4342,infeasible81). S1closes within its scoped output/
product/memory contract. Required T32 cadence/global stack/kernel peak acceptance
remains incomplete in S4(MEM-S4-01..05);not inferred from S1passing.

## S2 admission: dominant shared PPU background loop

S2sole active;receive T32planned graphics cost scope. Owner src/ppu/frame.c,
frame_build_internal -> background_row -> identical indexed output before
unchanged sprite composition. Estimate60-180candidate product lines,no new
full framebuffer/persistent cache/heap by default. Start with generated original
compiler instruction attribution and a bounded comparison cohort,especially
cached quad/perpixel far reads and row-invariant tile/address operations.
Preserve nametable mirroring,scroll/split,left masks,palette/raw opacity,sprites,
CHR cache allocation failure/raw paths,all bands/rows andreadonly PPU state.
Candidate timing alone is insufficient:independent512case native reference both
widths plus original DOSordinary/populated/far/raw outputs,cost andstack/memory
gate adoption. Product changes rebuild/publish three EXEs;prototype P does not.
Scope/expected/actual[],new0,counters unchanged;no game/ROMcontrol custody.
No emulator settings,helper process or toolchain change. S4receiving backlog
stays inactive;full goal/T32acceptance remains open. Node/documentation/diff
gates and semantic review precede S1commit/S2execution.

## S2 P1 checkpoint: pointer and fixed-index background cohort

Original /AL/Gs compiler listing shows repeated per-tile far nametable segment/
offset arithmetic and per-dot stack stores of postincremented target/shifted
bytes. Compare four candidates as one cohort against current S1source-bound
baseline. No product code or EXE change in this P; all sources/objects/dumps
stay under ignored build/m3-t32-s2. Same original compiler/runtime, normal SDL,
private desktop and installed DOSBox settings; no helper product process.

Span uses two far row pointers initialized before the loop from name_table&1,
then refreshed at source_x256. Initial scroll_x is byte0..255; increments cover
256logical pixels in aligned tile spans,so only that single boundary can occur
before loop exit. Pointer lifetimes borrow immutable state within one row.
Table masking, tile indices, attributes, fine scroll and palette lookup remain.
Indexed output replaces eight target postincrements and destructive packed-byte
shifts by fixed target0..7and constant shifts/masks. No aliasing word stores,
alignment assumptions or source pixels lost;partial cached/raw paths retained.
Combine these two. Fourth candidate copies64tile+16attribute bytes into caller
stack once per source tile row;no persistent cache/heap, but reject its tradeoff.

| Candidate | Phase0 whole-step diagnostic saving | Graphics-return phase3 saving | Diagnostic owned delta | Row/caller local bytes |
| --- | ---: | ---: | ---: | ---: |
| Baseline | 0 | 0 | 0 | 320/56 |
| Span pointers | 4.1236% | 5.0123% | +128 | 328/56 |
| Fixed indices | 3.0399% | 1.7614% | -80 | 320/56 |
| Combined | 7.1629% | 6.7507% | +32 | 328/56 |
| Row copy | 3.1035% | 1.6361% | +128 | 314/140 |

These seeded steps include device/file/mode work;phase1/5ordinary restore
steps improve only about0.8%with combined. Never treat the7.16%maximum as
stable gameplay FPS. Each candidate matches977235pixel/plane/text/save bytes.
Independent512cases each native width cover188743680strip and65536000plane
bytes,readonly state,guards and invalid calls. Indexed confirmations retained
in initial terminal runner output; span/combined/row-copy fresh logs are local.
Initial span/combined implicit first-loop pointer initialization provoked GCC
maybe-uninitialized warnings; changed to explicit pre-loop initialization and
reran both widths before timing. No unresolved warning presented as adoption.
The row-copy generator initially removed indented marker substrings before
matching its block; corrected exact line matching before compile/testing. These
driver failures are not product failures or acceptance evidence.

Selected combined fresh populated water/castle/dense matches977235bytes and
whole diagnostic phases3/4/5are8.8732/5.6143/8.8061%shorter,owned+48bytes.
Fresh matched far-cache and allocation-failure/raw baselines use the same
retained controlled allocator objects,not a cached-versus-uncached cost
comparison. Both selected runs match977235bytes;their exact costs and original
cache-pointer/cleanup receipts are in far-combined-summary/raw-combined-summary.
Both normal3mode restoration and near/far heap cleanup pass,settings unchanged.
No product resident-saving inference from diagnostic owned deltas.

Select combined for product evaluation:better scoped benefit than either
component,8additional row-local bytes,no caller/ABI/heap/workspace growth.
Reject row-copy:78more combined row/caller local bytes plus4private argument
bytes than baseline,lower benefit;do not spend scarce stack on it. Original
2048stack retained;affected frame/caller/IRQ/private joins stay part of S4's
finite pending proof. No game/NMI/PPU-state/control or platform policy changes.

Contained recipes:prepare-cohort,Build-Cohort,native/run/compare scripts;
prepare-row-copy/Build-RowCopy;prepare-extended retained populated/far/raw
bindings;record-cohort sources/listings/hashes/costs. State/background masks,
both nametables,scroll/split,clipped/full/blank rows,palette aliases,CHR near/
far/raw, sprite opacity/priority and resource rebind remain integration gates.
Next P integrates only selected combined after source review and actual product
build/memory/operational checks,refreshing three EXEs if adopted. S2/T32/goal
remain active;MEM-S4-01..05remain open,S4backlog not executing. scope/expected/
actual[],new0,custody unchanged,historical1992/1992,local1991/1992nodes,
4260/4261controls(raw4342,infeasible81). No full-ROM or playability certificate.
Documentation/node/diff gates precede commit;no S/T/queue advancement.

## S2 P2 closure: source-bound background span/index integration

Adopt combined only in src/ppu/frame.c,+20/-17lines. Borrow two far row
pointers within immutable PPUstate and refresh at the single256pixel nametable
boundary; fixed eight-dot target indices remove repeated pointer/packed-byte
stores. Product tokens equal tested candidate except explanatory comment.
All fine-scroll/mirroring/attribute/palette/blank/raw/cache/priority semantics
remain. No game/NMI/state/platform/API edits, heap or workspace growth. Original
/ALnear scratch ABI remains;row locals328versus320,caller56unchanged. Retain
2048stack and record affected joins in S4;no unsupported global bound.

Fresh current product source passes independent512cases each native width:
188743680strip bytes/65536000plane bytes,readonly state,guards andinvalid calls.
All14focused tests each width pass. Actual stripped Windowsproducts preserve
compiled runtime sections and pass144DPI768x720startup,three native80x30text
entries,two graphic returns andEscape. No input/window/system settings changes.
Source-identical controlled DOSordinary/populated/far/raw receipts each match
977235bytes. Selected populated graphics phases8.8732/5.6143/8.8061%shorter;
ordinary graphics-return6.7507%,matched far/raw6.7969/3.4947%. These include
fixture/device work and do not establish stable actual FPS or60Hzplayability.

Original DOSproduct301609bytes,+48from S1. DGROUP49072/headroom16464,
stack2048,max-extra3079unchanged. Logical loader bounds325728/342176bytes;
page-rounded326192/342640versus S1's325680/342128. The48code bytes cross a page
boundary;rounded loader bounds are not measured resident usage. Actual370KiB
route passesload,input,Tab,text/graphics,save,restore,Escape;2015samples,no invalid
or dropped MCBrecords,observed378720bytes(+48from S1). SaveCRC/resource binding
valid,frame7553versus seed7465;369still loads and refuses initialization with
result1cleanly,seed save unchanged. Tested budget and observations do not prove
universal minimum, continuous/kernel peak or all-path stack. NoDOSBoxsettings
change,normalSDL/private desktop and original toolchain/runtime retained.

Published existing owner-authorized three slots:
- mysmb16.exe:301609bytes;687a4d1ba622e4102e2f2c69c9eb8035bdf75d0bc9ca1c61374ef69f465a5d9b.
- mysmb32.exe:311310bytes;b186a136d7caf6286174f086980e6552eb7b61a9d40ee657aba6bf03ffc55e50.
- mysmb64.exe:324110bytes;8fbb42fee7da37c9b58a359c67a7e9acf56eede6c9204ee3dbcb9e4dfdae0015.
Local build/m3-t32-s2recipes/logs:Build-Product/Build-Native,verify-current-native,
strip-products,actual Windowsroutes,run-product-resident/verify-resident,
source-binding,memory-receipt and cohort comparators. Existing restricted local
resource binding only,no new imported material or distribution authorization.
Similar-issue sweep:all row entrances,scroll0..255and masked bank values,
single-page transition,attribute limits,partial/blank/cache/far/raw paths,
full/clipped bands,palette aliases,source readonly guards andsprite priorities.

S2closes within its exact-output/product/memory contract. No ROMcredit or
custody:scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes,
4260/4261controls(raw4342,infeasible81). T32/goal remain active. S4retains all
MEM-S4-01..05and latest changed-frame joins;no successful global cadence/stack/
kernel acceptance. Next approved S3 is sole active;gates precede commit.

## S3 admission: neutral color mapping and plane submission

Owners src/io/color.c andsrc/platform/vga/vga_frame.c only;immutable neutral
color/index input -> identical text colors/VGAplanes. Estimate40-140candidate
lines. Start with two bounded cohorts:exact constant color classification versus
repeated squared-distance arithmetic,and near row-staging versus repeated far
plane writes. Former derives only from existing project-owned neutral palettes,
not ROMresources;enumerate every byte input and preserve first-choice ties and
contrast. Latter may trial80/320transient stack bytes only after source/listing
review;no new heap,persistent buffer,game/CHR inspection or public ABI by default.
Reject startup/stack/memory regressions that outweigh speed;original2048stack
cannot be reduced without proof. Full256x240borderless640x400mapping,rows,masks
and all colors remain;direct hardware configuration and toolchain stay.

Independent exhaustive color/scaling/plane/guards test both widths plus original
DOScontrolled bytes,cost,listing/memory andactual route gate adoption. Reuse
unaffected S1-S2proof within source/dependency limits;no whole-project restart.
Product-code P rebuilds/tests/publishes three EXEs;prototype P does not.
S3scope/expected/actual[],new0,baseline/max1992/1992,counters unchanged. S4backlog
only,not executing. Documentation/node admission/closure checks and diff review
must pass before S3execution;no new T/queue reordering.

## S3 P1 checkpoint: exact color lookup and rejected plane staging

Compare four candidates against current source:80-byte immutable neutral color
choices(64nearest+16contrast),80-byte per-plane row staging,320-byte shared row
staging,and lookup+320staging. All are local prototypes;product source and three
S2EXEs unchanged. New choices derive only from existing project-owned neutral
RGB/text palette arithmetic,not ROM bytes. Preserve strict-less-than first-index
tie selection,index&63 andbackground&15aliases and128000brightness threshold.
Public RGBfunctions and their64/16colors remain unchanged,no mutable cache.

Each candidate passes all256byte inputs against separately compiled original
RGB/textRGB/nearest/contrast on both native widths. Each plane candidate passes
all bandfirst/rows1..16:16972800bytes,width mappings,masks,guards and invalid
requests,plus existing full-frame projection. Original DOScompiler standalone
color reference/new lookup also passes all256inputs/four functions under /AL/Gs
with the original runtime. Same installed DOSBoxsettings,normalSDL/private desktop,
bounded run andclean exit;no host input/settings/product helper changes.

| Candidate | Whole text phase2 change | Graphics-return phase3 change | Diagnostic owned delta | Relevant original local bytes |
| --- | ---: | ---: | ---: | --- |
| Lookup only | -32.4856% | -0.0466% noise | -544 | nearest42->2,contrast18->2 |
| 80-byte plane staging | -0.0074% noise | +29.8481% slower | -128 | planes8 + staged helper108,versus original planes46 |
| 320-byte shared staging | +0.0006% noise | +4.9382% slower | +96 | planes364versus46 |
| Lookup +320staging | -32.4878% | +4.9365% slower | -448 | lookup gains plus rejected364-byte plane frame |

All verified DOScandidate receipts match977235pixel/plane/text/save bytes.
Plane320conversion stage itself rises from267736to306529ticks(about14.49%),
so extra copies/helper work outweigh reduced per-dot far addressing.80staging
also repeats source-plane reads. Reject both staging variants and combination;
select lookup only for product evaluation. No need to enlarge stack or persistent
workspace for these losing layouts. Diagnostic owned deltas are not product
resident savings.80constant bytes may consume DGROUP;evaluate actual loader/
near-heap/startup alongside code-size andtime gains before adopting.

First diagnostic link failed because forced archive members duplicated explicit
color/VGAobjects. A previously cloned executable was mistakenly launched after
that failure;its exact T32S3probe chain was terminated and old run-base-1/
run-lut-1are excluded,not acceptance evidence. Rebuild only affected local
archives removing the one old color/VGAmember. Verify every retained member's
records remain identical apart from librarian-added module-name comments;
preserve code,data,fixups,externs,publics andother records. Fresh successful links
precede all run-*-verified-1receipts. No product library/toolchain change.
The standalone runner requires its exact successful256-input result.

Recipes/receipts under ignored build/m3-t32-s3:prepare-cohort,native tests,
Build-Cohort,replace-libraries/library-replacement,run/compare verified receipts,
Build-ColorCheck/reference-color/color_check,cohort source hashes andlistings.
Palette aliases,ties,contrast,all byte inputs anddynamic source palette consumers
remain exact;source/output disjointness andsynchronous band lifetime remain.
Next P integrates selected color lookup only,adds a retained exhaustive color
contract check andrefreshes three products after actual builds/routes/memory.
S3/T32/goal active;S4receiving MEM-S4-01..05andlatest affected ABI/locals remains
backlog. No game/ROM/PPUsemantics,credit or custody changes:scope/expected/
actual[],new0,historical1992/1992,local1991/1992nodes,4260/4261controls(raw4342,
infeasible81). No gameplay FPS/global-memory/stack certificate. Documentation,
admission/diff gates precede commit;no S/T/queue advancement.

## S3 P2 color acceptance and S4 integration handoff

Adopt lookup only in src/io/color.c,+13/-18lines,80constant neutral bytes.
Public RGBvalues/functions and byte/alias/tie/contrast semantics unchanged.
No platform macro,game/PPU/resource logic,heap,mutable cache or API changes.
Nearest/contrast locals42/18->2/2under original /ALcompiler. Existing property
test io_contract_smoke adds32lines:compute nearest RGB andbrightness from the
neutral palette for all256inputs,including aliases andlowest-index ties.
Product tokens equal native/DOSexhaustively verified prototype except comments.
Seeded whole text32.4856%shorter and977235matched output bytes remain scoped
diagnostics,not actual gameplay FPS. VGAstaging is rejected;no VGAproduct edits.

Both native builds pass15focused tests,including new exhaustive IOcontract.
Original DOS301145bytes(-464),DGROUP49152(+80)/headroom16384,stack2048unchanged.
Logical loader325264/341632(-464/-544),page-rounded325680/342048;max-extra3074
maintains full-DGROUPbound. Actual370and369KiBroutes passinput,Tab,text/graphics,
save,restore,Escape;both valid CRC/resource-bound saves frame7563versus seed7465.
Samples1858/1859,zero invalid/dropped MCBrecords.370observed378432(-288against
S2):primary341904(-544)but auxiliary36368(+256),so do NOT call observed total
saving544.369observed377856;368loads but returns1cleanly before play,seed save
unchanged. Tested positive boundary improves370->369within this fixture,not a
universal minimum. No continuous/kernel/global-stack certificate or settings change.

Windows actual host validation discovers two separate conditions. Current
physical work area480x839,DPI144cannot fit requested768x720;old andnew products
both correctly clamp to448x420by retained16:15geometry. Fix verifier only,
tools/Verify-Win32OwnedConsole.py,+32/-3:expected DPIrequest bounded by actual
work/margins andwait for initial show. Keep strict1500msmessage responsiveness.
No product window/system setting edits or forced test geometry.

Strict initial message gate STILL FAILS for current x86/x64 andprior S2x64.
Window is shown before unchanged audio_open andmessage loop. Separate bounded
readiness observation records10.229/10.206seconds for current x86/x64;after
readiness,both pass three native31x30clipped text entries,two graphic returns,
input andEscape. These later routes are valid scoped operational evidence;
longer observation is NOT a repaired/passing startup responsiveness gate.
Attach this recurrence to the already retained
[suspended T19audio task](../proposals/m3/bounded-windows-audio-startup.md).
No new global audit/finding universe or silent resumption of T19.

Publish existing owner-authorized products with explicit startup limitation:
- mysmb16.exe:301145bytes;b9624e4bdc7d192e0b9e19b1a36ddd6b941a0e28470d1b0069b63d6e290d1851.
- mysmb32.exe:311310bytes;b2598401c1a9f164517dc62ee9ea6cfe8a2697af566fedb4c9c569ea601102bd.
- mysmb64.exe:324110bytes;6ce56e66b7385bba015aacadd2d9e08ac9fcf65933ba09b3272dd9044d5aa149.
Stripping preserves runtime sections/RVAs. Local recipes/logs under
build/m3-t32-s3:integrate/prepare-product,Build-Product/Build-Native,original
color check,strip,actual resident/CRC/source bindings,old/new startup observations
and corrected work-area verifier. No raw resource/code import or distribution
permission beyond established local bindings and three authorized slots.

Similar-issue sweep covers all color-byte inputs,aliases,ties,brightness,
readonly palettes/dynamic callers andunchanged RGBtables;new tables' near-data
cost andcaller/CRT stack reductions. Host sweep separates work-area clamp from
startup readiness by prior/current products,not by discarding failing checks.

Coordinator accepts S3's pending strict Windowsstartup condition into approved
S4final integration as MEM-S4-05/WIN-T19-STARTUP. Local color/output/build/DOS
memory acceptance is complete;S3 closes by this explicit integration handoff,
NOT fully healthy host-startup acceptance. T19 remains owner-suspended andin
the queue;S4records this dependency andmay not silently repair/resume it.
S4sole active,all five MEM-S4clauses remain required/open,including newest
data/layout/local joins andfinal actual cadence. T32/goal remain active.
scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes,
4260/4261controls(raw4342,infeasible81),no node custody change. Gates precede commit.

## S4 admission: final integrated finite memory and cadence register

S4now sole executor of approved integration scope. Required IDs remain
MEM-S4-01startup/environment/argument domains;02fatal/exit/hook lifetimes;
03firmware/interrupt joins;04continuous/kernel/contiguous memory;05final
source-bound cadence/stack/input,including explicit existing WIN-T19-STARTUP
host dependency. No successful T32verification closure with unexplained gates.
Retain accepted scoped source/CRT/error/arena/IRQ9receipts andupdate only affected
S1-S3bindings/locals/layout. No census restart,source universe growth or credit.
Estimate0-200harness lines initially;original2048stack,tools/settings andshared
ROM/PPUsemantics remain. Measure current low-observation graphics/text costs,
reported input/time andactual budget/error/restore paths;separate diagnostics
from actual products andphysical486SX M4qualification. Needed repairs require
visible bounded scope amendment andthree EXEs;unrelated suspended T19repair
is not automatically resumed. Current source/product hashes bind the register.
scope/expected/actual[],new0,counters unchanged;documentation/admission/closure
checks andsemantic review precede execution,one active packet only.

## S4 P1 checkpoint: final current costs and affected stack bindings

Bind current S3products/source;no product repair or EXErefresh in this P.
Regenerate low-observation current-loop main/root/device instrumentation from
current owners;all other160-unit product objects/libraries use final S3build.
Originalcompiler/runtime andinstalled DOSBoxsettings unchanged,normalSDLon
private desktop.154records/zero drops,10title logs skipped only(no game/draw
skip),81qualifying graphics and25text steps;CRC/resource-bound save valid.
Clock1000reads cost88.1039ms,so numbers are diagnostics,not formal product FPS.

| Current diagnostic | Final median | T31 S6 baseline | Reduction |
| --- | ---: | ---: | ---: |
| Graphics step | 648.2154ms | 712.5786ms | 9.0324% |
| Text step | 453.2544ms | 815.5009ms | 44.4201% |

Current graphicsPPU393.2317ms(60.6637%),mapping197.5818ms(30.4809%),VGA28.8070ms;
game9.1771ms,snapshotcache10.4494ms. Text assembly366.3590ms(80.8286%),device
65.4527ms,game9.1864ms. Step-only rates1.543/2.206Hz;38.894/27.196times nominal
16.67ms. Gains are genuine within fixture;configured cadence gate FAILS.
Do not turn the improved startup memory boundary or nominal Win32speed into
DOSplayability. Physical25MHz486SXqualification remains M4.

Rebind final160compiled units against retained T31 S4software proof:156retain
all execution records,including data/segments/publics/fixups/externs,not only
source names. Exactly four changed owners:io/color,ppu/frame,text/background_scene,
text/elements. Original compiler regenerates31affected function listings and
binds their code/fixups/externs to final product objects. No functions added or
removed;851total functions.31fresh CFGs have balanced returns/call-site depths,
no unsupported stack effect;820unchanged function proofs retained.

| Affected function | Old/current locals | New/removed call effect |
| --- | ---: | --- |
| io/color nearest | 42/2 | removes multiply/shift andRGBcallee |
| io/color contrast | 18/2 | removes multiply/shift andtextRGBcallee |
| PPU background_row | 324/328 | no new callee;private colors argument remains current near ABI |
| text background object | 58/64 | removes longdivide/multiply/shift calls |
| text elements build | 4/8 | adds memcpy;current CRT contribution still needs final runtime join |

Own-source recomposition851functions,1744own edges/180CRTsites resolved by name;
retained two source-ranked cycles and23indirect target bindings apply. Main
own-only bound690unchanged,owned keyboardIRQ72+CPUentry6=78unchanged. External
names classify edges only;old CRTaddresses/bounds are NOT a current linked-CRT
certificate. No global stack bound inferred from these totals.

Rebind current MZ/stack/startup relocation:declared stack2048,begin47104,
top49152,stabilized SS=DGROUP/SP49150,2unused top bytes. Startup opcodes and
five argument pushes preserved;their linked data operands shift80with neutral
tables,main call remains identical.14main-entry residence+2top+690own=706,
explicitly EXCLUDES CRTcallee/private helpers,pre-main/env/argv peak andpersistent
argv,exit/hooks,BIOS/DOS/IRQnesting andkernel allocation peaks. This is not the
old758conditional combined proof anddoes not replace it with a smaller claim.
Initial driver incorrectly assumed CRTaddress0;actual mapped base1126and
link-patched global offsets are checked before accepting current layout.

## S4 finite gate status after P1

| Gate | Accepted current or retained clauses | Still required / present failure |
| --- | --- | --- |
| MEM-S4-01 | current MZ/SP/main residence;retained declared argument-domain receipts | pre-main/cinit/envp/argv maximum andall admitted pathname/tail domains;final bindings |
| MEM-S4-02 | unchanged own exit/file owners;retained normal/fatal/error receipts | current linked CRT/data/global callback lifetime andfull fatal/cleanup joins |
| MEM-S4-03 | unchanged owned IRQ9body/targets andCPUentry78 | firmware/DOS/BIOSbodies,other IRQ/exception/critical-error nesting;physical domain stays M4 |
| MEM-S4-04 | final369/370pass,368clean refusal;current loader/DGROUP;sampled memory/source identities | continuous allocation/kernel transients andall-phase contiguous requirements;sampled maxima are insufficient |
| MEM-S4-05 | current851function/31changed CFG/own690proof;three products/native15tests/DOSroutes;after-ready WindowsTab/input/exit | configured DOScadence FAILS;full joined stack andstrict WIN-T19-STARTUP FAILS;T19remains owner-suspended |

All five parent gates remain OPEN;P1closes concrete rebinding subclauses only.
Next P follows affected current CRT/startup/exit joins andnamed missing memory
conditions,not a new851function/whole-ROM audit. Material repairs require scope
amendment/three products. No T/S/queue advancement or silently resumed T19.
The existing queue-head resolution-matched Nesticle candidate remains unnumbered,
unadmitted andrequires T32reconciliation. Its benchmark/cycle/mode proposals
do not authorize settings orresolution changes in active T32.

Local build/m3-t32-s4recipes/evidence:prepare-current-cost/Build-Cost/run/analyze,
rebind-current,Build-Listings,verify-changed-listings,changed-callflow,
join-own,current-startup-layout andtheir source/layout/cost summaries. Raw
runtime/ROM material stays local/ignored,no new import/distribution. Scope/
expected/actual[],new0,custody unchanged,historical1992/1992,local1991/1992nodes,
4260/4261controls(raw4342,infeasible81). Documentation/admission/diff gates
precede commit;S4/T32/goal remain active andunverified complete.

## S4 P2 checkpoint: current CRT binary joins and exit-data relocation

Generate original /MAPrelink from final S3entry/stack/libraries,apply only the
same declared loader bound andrequire byte identity with assets/mysmb16.exe.
Identity passes:301145bytes,original SHA retained. No product/EXEchange or
compiler/runtime/setting substitution. Default product map has no public
symbols;attempting to use it as a public map failed andwas corrected by this
byte-equal relink,not by assuming copied old addresses.

Current actual CRTregion1126..9021,7896bytes;78public aliases/74entry anchors,
28external names/27entry addresses. Relative public entry addresses unchanged;
DATAoperands move with the80-byte table,so old linked bytes are not globally
claimed equal. Fresh decode proves the four arithmetic LRET8cleanup conventions.
Re-run the retained bounded local-flow algorithm on current bytes:54reachable
application-binary FILEflows all complete,28named CRTcontributions bounded.
No unresolved return/argument convention;examples memcpy/memcmp8,fmalloc70,
nmalloc56,fopen62,fread128,fwrite142,fclose68,fflush38,int8628. These local bounds
EXCLUDE BIOS/DOSservice bodies,CPUexception/critical-error handlers andstartup.
The binary FILErestriction is retained explicitly;owned file/provider160-unit
bindings support it,not runtime text/termination descriptors.

Fresh851function source+current conditional CRTjoin yields main720bytes,
unchanged from retained application-binary subtotal. Owned IRQ9 remains72+6=78.
With14main-entry residence and2unused top bytes,subtotal736 EXCLUDES persistent
argv andpre-main/exit/BIOS/other IRQ/kernel conditions. Retained no-argument
argv22would give758under its original applicability;not promoted to an all-
argument/current measured maximum. Stack stays2048andall-path proof remains open.

Current relocated loaded globals verified:debug callback0,alternate-stack
sentinelFFFFFFFF,default exit offset0271,FPinitializer0. All current own
objects have no direct references to those hook globals. XI/XCconstructor/
cleanup tables empty,XPone4-byte entry points tocurrent _flushall. Loaded
defaults andabsence of own direct references are NOT whole-lifetime proofs.
Normal _exit06BAanddefault fatal __exit06D1retain distinct cleanup entrances;
early runtime failure writes025AtoSS:369E,shared termination INT21AH4Cat0716.
Data-linked operands rechecked after80-byte relocation rather than matching
stale constants. Return cleanup/data source is now current,not assumed.

Separate startup/termination flow expands to57entries,48locally resolved,
nine entries explicitly pending:__setenvp15F6,__myalloc1E7E,
__FF_MSGBANNER13FE,__setargv144E(entry stack rewrite),fflush0DDA,write1BAA,
fwrite0B12,__flsbuf1816andfclose077C. This excludes no original behavior:
each unresolved return/stack transition remains required under MEM-S4-01/02.
Next P focuses these exact startup/exit/callback conditions andtheir data
lifetimes;do not rerun the already bound851own/54binary-only flow set.

Finite register:MEM-S4-01current layout/entry proof accepted,pre-main/argv
domains pending;02current binary CRTjoin/loaded exit structure accepted,
runtime hook/cleanup/text/termination lifetime pending;03owned IRQ78accepted,
other firmware/nesting pending;04final tested369/370/368andloader observations
retained,continuous/kernel/contiguous proof pending;05conditional main720
accepted,full stack andDOScadence FAILstill open,WIN-T19-STARTUPunchanged.
No successful T32/S4/goal closure andno new audit universe or task admission.

Recipes below ignored build/m3-t32-s4:relink-map/prepare-current-crt,
fresh CRTentries/flow/bounds/join outputs,current-exit-globals andtheir actual
product hashes/maps. Raw runtime disassembly remains local/ignored,no new
import or committed vendor/ROMbytes. Scope/expected/actual[],new0,custody
unchanged;historical1992/1992,local1991/1992nodes,4260/4261controls(raw4342,
infeasible81). Documentation/node/diff checks precede P2commit;products unchanged.

## S4 P3 checkpoint: fatal nonreturn and saved-BP contracts

The nine retained unresolved entries are not nine product defects. Most were
stopped by a return-only auditor when allocation/text write errors transferred
to the CRTfatal chain. Preserve original required behaviors rather than
silently pretending fatal calls return or omitting their stack consumption.
Current byte-anchored analysis recognizes INT21AH4C0716as process termination;
after its reached default __exit06D1there is no caller continuation/cleanup.
Calls that can either return normally or reach that terminal retain both paths.

Run an explicitly CONDITIONAL model:debug callback high word0,FPinitializer0,
exit pointer remains loaded0271/default06D1. Verify actual branch operands,
loaded words and empty constructor/cleanup ranges before using them. This
model excludes early025Aexit override anddoes NOT prove these globals remain
unchanged over all runtime paths. Keep original unconditioned flow ledger and
its nine gaps;never relabel loaded defaults as a lifetime certificate.

Under those named conditions,65reachable local entries/64resolved flows:
eight of the original nine get their return/terminal convention. Newly reached
fatal/nullcheck/vector-restoration helpers belong to the existing7896-byte CRT
region;no source/audit universe expansion. Default fatal06D1has terminal paths,
not a fabricatedRET. The initial diagnostic limited indirect-exit resolution
to one nominal entry;tail transfers reach the same05F1call from other entries,
so resolution is correctly attached to its verified instruction site instead.

| Original pending entry | Conditional current result |
| --- | --- |
| __setenvp15F6 | balanced LRET0;6local bytes; preserve saved BP separately from environment scan register |
| __myalloc1E7E | balanced RET0normal path or default fatal termination;8local bytes |
| __FF_MSGBANNER13FE | LRET0under null debug hook;4local bytes |
| fflush0DDA | LRET0return convention connected;16local bytes |
| write1BAA | LRET0or default fatal;544local maximum includes existing512-byte scratch |
| fwrite0B12 | LRET0connected;40local bytes |
| __flsbuf1816 | LRET0connected;22local bytes |
| fclose077C | LRET0connected;30local bytes |
| __setargv144E | nonstandard persistent stack return;domain bound remains required |

Local maxima above exclude entry return addresses andcallee/BIOS-DOSservice
bodies;the analyzer includes explicit INT CPUentry where encountered. They
are NOT additive stack sizes or composed global bounds. Setenvp's
15F9pushBP saves its established frame pointer,uses BPfor environment counts/
heap output,and166CpopBP restores it before166DmovBP,SP. The prior scalar
model discarded that saved value andreported unknownBP;current instruction-
checked save/restore yields a balanced normal return. No program change.

Setargv structural contract is now explicit:144E/1452pop the4-byte far return
into globals3760/3762,1520subtract runtime DXfromSP,15F1jumps through the saved
far PC. Relative to caller beforeCALL,SP remains lower by DXthrough main.
It is neither ordinary LRET0nor a callback termination. Required remaining
domain proof covers decoded pathname length/termination,PSPtail quote/backslash
paths,argc/vector arithmetic/16-bit wrap andspace before persistent allocation.
Retained tested22/152/400byte domains remain scoped;no all-path bound inferred.

MEM-S4-01now has current setenvp local save/return andargv return mechanism;
allocation domains/peak still open.02has conditional error-chain conventions;
hook lifetimes,early025Aoverride,normal XPflushall iterator andfull exit bounds
still open.03firmware/nesting,04continuous/kernel/contiguous,and05full stack/
failed cadence/strict Windowsstartup remain open. Products,2048stack and
640x400final DOSoutput unchanged. No suspended T19execution or T/Sadvancement.

Contained recipes/receipts:prepare-fatal-contract-flow,current byte-anchored
crt-default-hook-flow andargv-return-contract under build/m3-t32-s4. Preserve
unconditioned crt-startup-flow alongside conditional outputs. Next Pproves
specific lifetime/early-exit/argv domain obligations,not a reset audit of all
65/851entries. No source/ROM/import/output changes,scope/expected/actual[],new0,
historical1992/1992,local1991/1992nodes,4260/4261controls(raw4342,infeasible81).
Five parent gates remain open. Documentation/node/diff checks precede commit.

## S4 P4 checkpoint: parameterized argv bound and current DOS tail routes

Current setargv first-pass grammar andallocation instructions rebound by exact
sites:skip space/tab,terminate NUL/CR,increment argc at token entry,quoted and
unquoted runs,backslash parity/ADC andfinal vector/terminator additions.
For pathname bytes P INCLUDING NUL,decoded parameter bytes D andargc A,
persistent DX=(P+D+A+4*(A+1))&FFFE. This matches its nonstandard saved far-PC
return;space stays allocated through main,not released by LRET.

Abstract-state exhaustive walk of the declared tail domain lengths0..126:
ordinary byte,space,tab,quote,backslash;NUL/CRterminate a prefix already covered.
State(mode,pending slash run,argc) keeps maximum decoded count because larger D
dominates smaller Dandfinal even-floor is monotone before16-bit wrap.353536
states/1726725transitions;no string sampling presented as exhaustion. Ordinary
bytes share the same current comparisons;lookahead/rewind slash runs are charged
once,quote parity consumes itself andquoted spaces remain decoded data.
A<=1+ceil(N/2),D<=N;maximum D+5A+4overall N<=126is388. Therefore persistent
allocation is at most(P+388)&FFFE within a no-wrap,terminated-path domain.
For CONDITIONAL P<=260,it is648bytes;intermediate arithmetic stays below65536.

This does NOT prove DOSkernel pathname maximum. Appmain has path[260],butits
post-startup executable_path check cannot constrain CRTwhich runs BEFORE main.
Do not convert that application capacity into a universal loader assumption.
Malformed/unbounded environment,larger tail andOS-specific pathname domains
remain explicit MEM-S4-01requirements. Abstract grammar proof is accompanied
by independent current real-DOS fixture evidence below,not a replacement for it.

Rebuild retained bounded stack/MCBobserver with current DGROUP4368andrelocated
globals;original toolchain/installed DOSBoxsettings unchanged,private desktops.
Run final unmodified product at369KiBfor three command tails,each full input/
Tab/text/graphics/save/restore/Escape route. Product SHAmatchescurrent asset;
zero invalid/dropped MCBrecords,2048timer samples and109DOSentries each.
Current SPtop49150,arg vectors andexit/debug sampled values match predictions:

| Command domain at P13 | argc | Persistent bytes | Main+CRT+entry+argv subtotal | With one owned IRQ9 |
| --- | ---: | ---: | ---: | ---: |
| Empty tail | 1 | 22 | 758 | 836 |
| 126-byte tail of63small arguments | 64 | 400 | 1136 | 1214 |
| 126-byte tail with one125-byte argument | 2 | 152 | 888 | 966 |

All three save CRC/resource bindings andcontinuation pass,current default
exit0271/debug0observed. These are finite sampled routes,not whole callback
lifetime proof. The observer borrows caller stack andis not a global product
high-water measure. No settings/frame loss orproduct/code/resolution changes.
For hypothetical P<=260,N<=126andretained binary-FILEmain/owned IRQconditions,
subtotal720+16+648+78=1462 EXCLUDES pre-main peak,exit/hooks,other IRQ/BIOS/DOS
bodies andkernel conditions;not a certified2048stack margin.

MEM-S4-01now has a parameterized declared-tail-domain allocation bound,current
return mechanism andthree source-bound paths;valid pathname/environment domains
andpre-main peak remain open.02conditional hooks/early-exit/cleanup lifetimes,
03firmware/nesting,04continuous/kernel/contiguous,and05full stack/failed cadence/
Windowsstartup remain open. No new source/audit universe ornode credit;no T/S
advancement orsilently resumed T19. Next Paddresses the missing domain/lifetime
premises rather than repeating these three paths or the full grammar walk.

Contained build/m3-t32-s4recipes/results:prepare-current-argv-probes,three
original observer builds/runs,argv-domain-bound andverify-current-argv. Raw
runtime/dump/artifacts remain ignored;no third-party/ROM import orEXErefresh.
scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes,
4260/4261controls(raw4342,infeasible81). Five parent gates/S4/T32/goal stay open;
documentation,node anddiff checks precede commit.

## S4 P5 checkpoint: unused DOS argument setup elimination candidate

Rather than only proving a domain for unused CRTargv, evaluate eliminating its
work. This is a contained host-startup correction cohort,not ROM/game logic or
an alternate compiler/runtime. Product DOSentry is main(void);160compiled
owned units have no parsed argc/argv/getenv/environ consumer references.
Direct linked CRTargc/argv references are only its construction routine and
five-word main-entry argument pushes. Real DOSpath discovery reads PSP
environment itself,not argv0. Environment setup andstdio/heap/exit stay original.
Future consumers of parsed args require re-review;this is not a generic C
runtime replacement or permission to remove all environment processing.

Own four-line Cprobe _setargv(void)has an empty body. The reserved name is
deliberately the existing private CRTentry symbol,not a public game API.
Original /AL/Gs emits normal far return0,2locals andpreserved callee registers;
link resolves that symbol before the same LLIBCE.LIB. All game/product object
libraries remain S3bound. CRTargc/argv globals remain initially zero,the DOS
main ignores incoming values,andthere is no persistent DXallocation or saved-
PCjump. Original setenvp still executes. No binary patch,stack shrink,DOSBox
settings,resolution change,new process,resource import orWin32logic change.

Candidate300725bytes(-420from current301145),DGROUP49152/headroom16384/2048stack
unchanged;logical loader324848/341216(-416/-416),page-rounded325168/341536.
Original bound3074retained. Not adopted;these are prototype figures,no refreshed
product orclaimed universal startup minimum. The far-return stub itself uses
an ephemeral frame;zero below means ZERO PERSISTENT argv rather than zero
startup stack use. Other constructor/exit/firmware/kernel conditions remain.

Controlled original DOScandidate matches977235bytes against current S3lookup
baseline:all admitted pixels,planes,text andgame save,including mixed-mode and
restore. Three separate final-candidate actual369KiBroutes,empty/many/single
tails,all passload,input,graphics/text/Tab,save/restore/Escape;valid CRC/resource
binding,zero invalid/dropped MCBrecords,2010timer samples/7records each.
Current candidate observer rebound to434E DGroup;data offsets unchanged.
All three observe argc0/argv0,top49150/defaultexit0271/debug0;22/400/152bytes
of persistent argv are eliminated. This is finite sampled runtime evidence,
not a whole-lifetime/global-stack certificate. Paths/saves still work through
unchanged PSP-based discovery. Original product source/three S3EXEs unchanged.

Select noargv for product integration evaluation:removes the unnecessary
pathname/tail-dependent allocation altogether andsaves linked code/loader
space. Does not solve envp/cinit peak,callbacks,other IRQ/BIOS/DOSbodies,
continuous/kernel memory,failed graphics cadence orWindowsaudio startup.
Required next Pscope amendment:small owned DOSstartup adapter andoriginal
build linking selection,estimate10-30product/build lines,all three EXEs and
actual memory/output/operational checks before acceptance. No silent adoption
from this probe,no change toshared ROM/C behavior orgame input.

Contained recipes/results below build/m3-t32-s4:prepare-noargv/Build-NoArgv,
original dependency scan,private reserved-symbol listing/map,controlled byte
comparison andthree independent rebased observer loaders/routes. Any temporary
verification process remains local;do not restart oraccept a stale yielded
operation without terminal evidence. Raw local material not committed/imported.
MEM-S4-01argv cost has an actual elimination candidate,not completed acceptance;
all five parent gates stay open. S4/T32/goal active,scope/expected/actual[],new0,
historical1992/1992,local1991/1992nodes,4260/4261controls(raw4342,infeasible81).
Documentation/admission/diff checks precede commit;no T/S/queue advancement.

## S4 P6 checkpoint: integrate original-ABI DOS noargv hook

Adopt src/platform/dos16/process_startup.c,8lines,private _setargv(void)hook;
tools/Build-OpenNt16Dos.ps1+9/-1links its explicit object before original LLIBCE.
Reserved symbol is a narrow original-runtime ABI exception beneath DOSplatform,
not a game API orimported implementation. Original /AL/Gs compiler emits the
checked normal FARreturn0,2local bytes andcallee-saved registers. No parsed
argument consumer in current main(void)/160owned units;PSPexecutable path and
environment initialization remain. Build guard rejects a changed main signature
andrequires review of future parsed-argument consumers. It accepts current
source;post-build addition only guards the compile,no binary semantics change.
Shared core/PPU/IO/input/ROM andWin32product source unchanged. No lost input,
new process,settings change,stack shrink orresolution change. The guard does
not purport to detect arbitrary indirect future consumers;review remains required.

Formal original-toolchain DOSproduct bytes EXACTLY equal the tested P5candidate:
all977235controlled pixel/plane/text/save bytes andthree actual369KiBempty/
many/single-tail routes remain current product evidence,not repeated runs.
No use of old product evidence across different image bytes. Observed argv
persistence0across all tails,valid CRC/resource-bound save/input/Tab/restore/exit.
Supplemental actual368KiBexecutes but refuses initialization,result1clean,
seed save unchanged. Tested startup boundary remains369positive/368negative
for this fixture,not a universal minimum orhigh-water. The small hook has an
ephemeral stack frame;zero persistence is not zero startup stack use.

DOSproduct300725bytes(-420),DGROUP49152/headroom16384/2048stackunchanged;
logical loader324848/341216(-416),page-rounded325168/341536,bound3074retained.
No new heap/workspace orargument-dependent DXallocation. Own product units
now include the additional host-only hook;old851software function proof needs
one explicit hook/current CRTlayout join,not a new ROMnode. Current main's
parsed argv values are intentionally0because it ignores them.

Fresh both Windows builds pass15focused tests each;packaging preserves runtime
sections/RVAs. Compared with S3,each current native product's runtime sections
are byte-identical;header/package identities differ. Retain source-identical
after-ready Tab/input/exit scope andFAILED strict WIN-T19-STARTUPgate. Do not
claim fresh strict healthy startup,frame-rate change orsilently resume T19.
No Windowscode orsystem settings changes. New hook is absent from native targets.

Three refreshed existing owner-authorized slots:
- mysmb16.exe:300725bytes;33413d575a87b31969b5dc6227154a925a09a4e10a73ea35c7598a3e3580c8f7.
- mysmb32.exe:311310bytes;397ff7af59d5d95368b375989627077abc92997f00050a7cbb5d63e86f81284d.
- mysmb64.exe:324110bytes;4c7f09da0b5521729fa03f53c3ce793542d0d426c60bd4ed78aa2777faf25f5e.
Actual source change8new platform lines/build+9/-1;no game logic orvendor code
copied. Existing local build/resource/runtime policy retained,no new source
import ordistribution permission beyond established three artifact slots.

Similar-issue sweep:all owned parsed-argument/environment symbol consumers,
direct CRTargc/argvuses,main signature/original FARreturn contract,explicit
library resolution,PSPpath/envp/stdio preservation,no-argument/max-tail input,
source-identical controlled outputs,loader/near-data/stackandnative isolation.
Contained build/m3-t32-s4/p6logs:original build/memory/source/candidate identity,
fresh native15tests,stripping/runtime section equality and368clean refusal;
P5exact-image routes/dependency proof remain linked current evidence.

MEM-S4-01argument parsing/persistent stack cost is removed in product;the
previous pathname-dependent argv precondition no longer controls that cost.
Environment/cinit/exit/hook/firmware/kernel andfull stack/cadence gates still
remain;rebind changed startup/CRTmap next Pbefore reusing address-specific
receipts. No blanket claim about startup peak,BIOS/DOS/OEMdomains orplayability.
S4/T32/goal active;all five parent gates not completely accepted,scope/expected/
actual[],new0,historical1992/1992,local1991/1992nodes,4260/4261controls(raw4342,
infeasible81). Documentation/node/diff gates precede commit;no T/Sadvancement.

## S4 P7 checkpoint: current noargv startup and CRT binding

Bind current P6published DOSimage to byte-identical original /MAPcandidate.
Runtime _TEXTnow1142..8613,7472bytes. Original argv144E..15F5routine424bytes
is absent;owned15-byte hook/alignment precedes the image.77retained CRTpublic
aliases/73entry anchors rebased,old aliases differ only by removed setargv.
Before deleted routine,entry/site addresses move+16;after it,-408. Check all
public names/addresses before rebasing concrete flow sites;DATAoffsets remain
unchanged. The initial broad address rewrite also changed a Windowsprocess
flag;restrict rewrite to the actual CRTaddress interval before any accepted
decode/run. No product code ortool flags changed by this diagnostic correction.

Fresh original arithmetic return anchors still LRET8;current binary-FILE54
local flows and28CRTcontributions rechecked at new addresses,their bytes
unchanged. Add owned empty hook to retained own graph:852owned functions,
conditional main+current binary-FILECRT720,ownedIRQ72+CPUentry6=78,no unresolved
owned call target. This is not whole-system stack proof;body/service/other IRQ/
startup/exit qualifiers remain. One platform hook adds no ROMnode/custody credit.

Loaded current debug/FPglobals remain0,exit0271. Rebase the explicit default-
hook/error-flow conditions rather than replay old raw addresses:64reachable
local flows/64connected under those declared conditions,no remaining argv
stack-rewrite entry. Runtime setenvp still executes;hook lifetime/early025A
override/normal XPiterator are NOT accepted merely from loaded defaults.
Do not call64/64a global runtime orM2certificate.

Current caller is __astart05BC ->own hook0000:0000,not __cinit. Direct current
instruction scan caught the incorrect initial caller guess before accepting a
join. Before this call,normal __cinit and __setenvp return balanced;SSpush/DS
pop has net0relative to stabilizedSP. Owned machine bytes match compiledhook:
BP/SI/DI saved6+local2+far entry4=12ephemeral bytes,normal far-return0,
no persistent argv. No argument/path tail affects this frame. Loader/code
memory savings andP5/P6real369/368bound/output/input/snapshot evidence retained.

Current parent status:MEM-S4-01argv-dependent allocation removed/entry12bound
accepted;envp/cinit/full supported domains andpeak still open.02conditional
default runtime flow accepted,hook lifetimes/early-exit/cleanup still open.
03ownedIRQ78accepted,other firmware/nesting open.04loader/startup fixture
boundaries accepted,continuous/kernel/contiguous proof open.05main720accepted,
full stack andconfigured graphics/text cadence FAILremain open,strict existing
WIN-T19-STARTUPstill FAIL/SUSPENDED.2048stack/640x400output/products unchanged.

The owner's added S5-S9plan stays planned,not admitted;S4sole active. It creates
a dependency issue if S4must pass final cadence before admitting the S tasks
intended to repair that cadence. Coordinator requested explicit owner direction
for named five-gate handoff to S9under CURRENT/Execution closure authority.
No pending question is treated as approval;no silent gate transfer/closure,
registry/admission change orresumed T19. Until directed,retain S4scope.

Recipes/results below ignored build/m3-t32-s4/p7:current-map extraction,
address-rebind/current CRTentries/flow/bounds,default-hook conditions,owned
startup byte/return join and852function application join. Existing restricted
runtime/owner material only;no imported source/protected bytes orEXErefresh.
Scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes,
4260/4261controls(raw4342,infeasible81). All five gates/goal remain open.
Documentation/node/diff checks precede commit;fresh S5packet only after direction.

## S4 P8 correction and owner-directed responsibility boundary

Owner approved the S5-S9 plan, then clarified that repairable known issues
must be fixed in S4; performance work belongs in S5-S8 and S9 is final audit.
The proposed wholesale five-gate transfer was withdrawn before commit.
S4 remains the sole active S. No gate is marked passed by transfer and no S5
admission or node-custody event is retained.

Correct P7's statement that DATA offsets were unchanged: removing saved
argv-return globals shifts the FP initializer to 3EE6, XP to 3EF2..3EF6 and
the empty cleanup table to B7F2. Debug 375C and exit 369E stay unchanged.
Current product bytes confirm null debug/FP hooks, exit 0271 and XP's single
_flushall callback. The contained validators now read these actual addresses.

Invoke default-flow analysis with both --startup and --app-binary. Omitting
these flags analyzes only the external-call roots and cannot establish the
startup/exit joins. Fresh default analysis reaches 63 local entries, all 63
resolved; the prior 64/64 summary is superseded by this reproducible result.
The normal-exit generator additionally includes _exit, the loaded XP callback
and the subsequent fatal-cleanup fallthrough. Its empty-table rule now also
applies when that cleanup is reached from normal _exit. Fresh analysis reaches
65 entries, all 65 resolved with no pending local return convention.

These results remain conditional on original callee/DOS register contracts,
unchanged default hook lifetimes and source table contents. They do not prove
early 025A override, firmware bodies, other interrupts, kernel transients or
a global joined stack bound. Retain those named S4 obligations rather than
promoting conditional counts to a whole-system certificate. No product bug
or original-ROM semantic change was discovered by this evidence correction.

Recipes remain below ignored build/m3-t32-s4/p7. Run the corrected
prepare-noargv-default-flow.py, crt-default-hook-flow.py --startup --app-binary,
prepare-normal-exit-flow.py, then crt-normal-exit-flow.py --startup --app-binary.
Similar-issue sweep covered shifted runtime data reads, code-address versus
data-address rebinding, root-selection flags and normal/fatal cleanup joins.

Three EXEs are current S4 P6, verified by SHA256 and unchanged source since
that product commit: DOS 300725 bytes, x86 311310, x64 324110. Respect the
owner's latest instruction: no rebuild or publication refresh without new
product-code changes. Hashes in target order:

- 33413d575a87b31969b5dc6227154a925a09a4e10a73ea35c7598a3e3580c8f7
- 397ff7af59d5d95368b375989627077abc92997f00050a7cbb5d63e86f81284d
- 4c7f09da0b5521729fa03f53c3ce793542d0d426c60bd4ed78aa2777faf25f5e

S4 must finish named repairable runtime/memory and evidence defects before
closure. S5-S8 own measured performance deficits; S9 checks their combined
acceptance, not a backlog of known repairs. Strict WIN-T19-STARTUP remains a
failed suspended dependency; changing its ownership requires a visible scope
decision, not silent resumption. Physical 25 MHz 486SX qualification remains M4.
No new audit universe or unrelated revalidation is introduced.

Scope/expected/actual empty, new zero. Historical 1992/1992; local 1991/1992
nodes and 4260/4261 feasible controls (raw 4342, infeasible 81). Full M2
certification and configured DOS cadence remain incomplete. Documentation,
node and diff gates precede commit; S4/T32 remain open.

## S4 P9 checkpoint: normal and DIV exit software chains

Current CRT __cintDIV at 05E2 writes 025A to SS:369E at 05EA, then
falls through into __amsg_exit. Its indirect call at 0601 is preceded by
PUSH CS. Thus treating all error calls as default 0271 is insufficient;
the declared DIV domain must select normal _exit at 06CA instead of fatal
cleanup 06E1. No product source or machine bytes changed.

Add __cintDIV as an explicit root and run two separate conditional models:
normal/default cleanup and the DIV-installed 025A override. Both resolve
65/65 local entries. Recursively compose concrete call depths, near/far entry
bytes and callee bounds, skipping only checked empty constructor tables and
already accounted same-frame helpers/generated interrupt thunks. Neither
model has a recursive CRT chain or unresolved target. The largest conditional
local CRT bound is 142 bytes excluding its caller's entry.

| Entry | Normal/default domain | DIV override domain | Bound scope |
| --- | ---: | ---: | --- |
| __cinit | 6 | 6 | Excludes far entry and DOS service body |
| __setenvp | 52 | 78 | Includes reached software error/exit chains; excludes far entry and DOS service body |
| _exit | 64 | 64 | Includes current XP _flushall and following cleanup; excludes far entry and DOS service body |
| __cintDIV | Not a selected root | 70 | Includes error printing/normal exit; excludes CPU interrupt entry and firmware/nesting |

This resolves the named software exit-target omission in MEM-S4-02. It does
not prove default debug/FP/table lifetimes under arbitrary memory writes,
environment allocation domains, __astart's segment/stack transition, other
interrupt nesting or a whole-system peak. Those remain explicit S4 work,
not passed receipts and not a S9 repair transfer. Existing configured
performance failure remains for S5-S8. Strict host startup retains its named
suspended T19 dependency; no repair claimed or resumption performed.

Contained recipes: prepare-exit-override.py, crt-exit-override-flow.py
--startup --app-binary, bound-exit-domains.py; current product SHA matches P8.
The bound excludes BIOS/DOS bodies explicitly and does not mistake an INT's
six-byte CPU entry for the service's whole stack. Similar-issue sweep covers
the current direct write to exit target, saved-CS indirect call, normal/fatal
fallthrough, table iterator callback and near/far child entry accounting.

Expected and actual product changes zero; three EXEs remain current P6 and
are not rebuilt. Scope/expected/actual empty, new zero; historical1992/1992,
local1991/1992 nodes and4260/4261 feasible controls(raw4342,infeasible81).
Documentation/ledger/diff gates validate this checkpoint before commit.

## S4 P10 checkpoint: current hook observations and unused envp candidate

Re-run the published P6 DOS EXE at the unchanged 369 KiB fixture budget,
original compiler and installed DOSBox configuration on a private desktop.
Extend the read-only timer/DOS-entry observer to FP hook 3EE6 and relocated
XP callback 3EF2. All 2024 timer samples/84 DOS entries produce seven valid
events, zero invalid arena chains and zero dropped records. At recorded
boundaries debug/FP remain null, exit remains 0271 and XP equals the actual
load-relocated _flushall pointer. Argc/argv remain absent, stabilized SP49150.
Actual game, Tab text/graphics, snapshot restore/save and Escape exit pass.
All three captures and the CRC-valid resource-bound save are byte-identical
to the retained P6 route. Graphical capture is the expected 640x400 scene.
Observed owned peak remains377856bytes with160bytes external environment.
This closes the missing observed FP/XP fields for that route, not continuous
write/kernel observation or universal hook lifetime.

Also evaluate a contained unused-envp prototype: preserve __cinit, physical
PSP environment and executable-path discovery, replace only the unused CRT
environment-vector copy with an original-ABI empty hook. Existing owned-unit
consumer inspection is the hypothesis basis, not final adoption evidence.
No product source or published EXE changed. Candidate links successfully,
EXE300549(-176), logical loader324672/341040(-176), page-rounded loader
325168/341536unchanged, DGROUP49152/stack2048unchanged.

Actual candidate369KiB route returns normally, seven valid events/2036timer
samples/83DOS entries, no dropped/invalid chains. Primary shrinks176bytes,
but peak auxiliary grows176bytes, leaving the same377856owned peak. Ground
capture matches; later text/graphics and save differ (44savebytes, including
CRC). Wall-timed routes are not a deterministic equal-update comparison, so
do not infer a game-logic fault or exact output from these differences.
The candidate is NOT adopted: no measured page-rounded/owned-peak reduction
in this fixture and no controlled equal-state output proof. Keep current
__setenvp product behavior while reconciling its named memory domain.

Contained hook-observer-summary.json and noenv-product memory receipt retain
the source/product/config bindings; run-hook and run-noenv are terminal,
not restarted on observation timeout. No settings, helper process, source
import or default resolution change. Actual product lines0, published three
EXEs unchanged/current. Node scope/expected/actual[],new0; historical1992/1992,
local1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81).
S4 remains active; runtime/all-phase memory conditions remain named open,
performance repair belongs to S5-S8 and S9 remains final audit.

## S4 P11 repair: dense environment CRT allocation overflow

Use a contained synthetic environment with9363terminated NAME= strings and
a final NUL:28090bytes, no ROM/third-party input. Current __setenvp calculates
aligned string bytes28090 plus37456pointer bytes:65546. Its16-bit request
wraps to10 before __myalloc; the subsequent vector/string stores still copy
the full count. Source-bound arithmetic identifies an underallocation and
out-of-range writes, not an original-ROM game-rule change.

At unchanged448KiB caller budget/default DOSBox configuration, the published
P6image does not reach graphics or return from EXEC before the bounded scripted
DOSBox quit; FIT contains only the pre-EXEC record. Its verifier fails for
missing return evidence. Do not classify DOSBox's eventual exit as game success.
The isolated noenv candidate completes the same dense-environment route,
2043timer/74DOS-entry samples,4events/no drops or invalid chains. Three
captures and resource-bound CRC-valid save are byte-identical to the retained
normal P6route. Actual observed external environment28192bytes remains;
owned peak410480bytes applies to this larger-environment fixture only.

Adopt an original /AL empty _setenvp hook in platform/dos16/process_startup.c.
It removes only the unused C vector/string copy. __cinit, inherited descriptor
setup, actual PSP environment and executable-path discovery remain. Current
main(void) and160retained owned units have no vector consumers. The new build
gate checks163compiled objects, including generated-resource/link entry units,
for argv/envp/environment API external references:zero hits. Real original-
compiler getenv and environ consumer objects are correctly rejected. Future
consumers require explicit ABI review; no silently broken environment API.
The private reserved hook remains a narrow DOS-runtime ABI exception.

Formal full original-toolchain DOSbuild is byte-identical to the tested
candidate. Both hooks have original far-return0/2local/6saved-register frames,
12ephemeral bytes including entry, zero persistent C-vector allocation.
Stack2048, DGROUP49152 and640x400output unchanged. Actual369normal route
passes; formal368EXEC succeeds then returns1cleanly without changing seed save.
No new universal minimum, whole-system peak or hardware FPS claim.
P10's noenv deferral is superseded by this concrete correctness defect and
the new source-bound dense-route output evidence, not a speculative speed gain.

Native x86/x64 freshly build and each pass15focused tests, including platform
purity. Stripping preserves runtime sections; those sections are also identical
to the preceding published native products. Retain scoped after-ready behavior
and the failed strict WIN-T19-STARTUP dependency; no Windowsaudio repair claim.
Three owner-authorized product slots refreshed together:

| Target | Bytes | SHA256 |
| --- | ---: | --- |
| mysmb16.exe | 300549 | 122669c5818ad939402c51a59676dd658ea6e4d3817e2b57dc50c4eec08415f6 |
| mysmb32.exe | 311310 | cc4fd97d081651532960c590e766c7b19ec9ddc687cafd0c3bde42824c76044c |
| mysmb64.exe | 324110 | aaf48b47ac47e600ae70c6cb7ecae1de6035c9da79be8625cb0d02edea947720 |

DOS EXE/logical loader shrink176bytes to324672/341040; page-rounded
325168/341536unchanged. Ordinary fixture owned peak377856unchanged; do not
present176file bytes as176resident bytes. Actual source/build change+9/-4
and+4/-0; new consumer verifier67lines. No shared game/PPU/input code changes,
settings changes, product helper or imported implementation. Raw material,
recipes, failed-control record and proofs remain below ignored build.

Similar-issue sweep:both omitted vector capabilities and all163owned-link
external records; actual16-bit count/size arithmetic, private ALreturn/entry,
retained cinit/PSP/file path, ordinary/dense environments, insufficient-memory
refusal, save integrity, exact captured output and native isolation. The
named envp copying/allocation defect is closed in MEM-S4-01. Current address-
specific CRT evidence needs binding to the new image before reuse; firmware,
kernel/continuous memory, joined stack and strict host startup remain open.
S4/T32remain active; performance work remains S5-S8, S9combined audit.
Scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes,
4260/4261feasible controls(raw4342,infeasible81). Governance/node/diff gates
precede commit; no full certification is inferred from these tests.

## S4 P12 staged closure and S5 admission

Owner's approved division is binding: fix known repairable defects in S4,
implement performance in S5-S8, perform combined acceptance in S9. Close S4's
repair/delivery stage under that instruction. This is not successful closure
of all five final proof gates and does not close T32 or the goal. No known
repair is handed to S9; any concrete finding returns to its component owner.
S9 receives only the explicit unproved acceptance checks listed below.

Bind the current P11 product to its byte-identical original /MAP prototype.
Current CRT7282bytes/75aliases/71anchors; removed __setenvp and __myalloc.
Both owned hooks are original far-return0,12ephemeral bytes each; argc/argv/
envp copies consume zero persistent bytes. Debug/FP null, exit0271 and XP's
actual current _flushall pointer independently checked. Rebind3016concrete
instruction sites by retained public anchor/instruction order, checking
mnemonic and encoded lengths; this mapping alone is not semantic proof.
Fix the emitted decimal XP target as well as hexadecimal sites before running
the current conditional flow: default/normal62/62, DIV63/63, no unresolved
local returns; largest conditional CRT142bytes excluding caller entry.
Retain original object/source contracts, not stale address-specific receipts.

Both current native products pass the unchanged1500ms first-message gate,
three owned Tab cycles, actual text input/graphics returns and Escape exit.
Current host is DPI144/workarea1920x1008, client768x720 and Terminal80x30
viewport. This differs from the earlier480x839host; those failures remain
historical condition-specific evidence. No audio code changed and no general
acquisition/lifetime repair is claimed. Suspended T19 remains queued under
its original owner; successful ordinary launches do not close that task.

| Register | S4 disposition | Remaining responsibility |
| --- | --- | --- |
| MEM-S4-01 | Unused argv cost removed; reproduced dense-env allocation overflow fixed; current hooks/loader and ordinary/dense routes bound | S9 checks supported startup/physical-environment domains and complete phase binding; no known copy defect remains |
| MEM-S4-02 | Data/site/decimal-target defects corrected; current normal and DIV software joins resolved under explicit conditions | S9 audits callback/table lifetime, alias assumptions and combined error/text/exit applicability |
| MEM-S4-03 | Owned IRQ78 and retained software contracts remain accepted locally | S9 checks firmware/other-interrupt/exception nesting premises; physical25MHz486SX qualification stays M4 |
| MEM-S4-04 | Current loader,369pass/368clean refusal and scoped arena observations retained; no universal minimum/peak claim | S9 audits continuous/kernel transient and all-phase contiguous-memory evidence |
| MEM-S4-05 | Three current products and current-host strict operational routes accepted within their conditions | S5 measures the known configured-cadence deficit; S6-S8 repair performance; S9 integrates joined stack/cadence and named host applicability |

S4's concrete envp/product and validator defects are fixed. Final proof
conditions above remain OPEN; configured cadence remains FAIL. This named
division replaces the withdrawn blanket five-gate repair transfer. Accepting
these checks is coordinator action under the owner's explicit new-plan/S4
repair/S9-audit direction, not a claim that unknown premises passed.

S5 alone is now admitted. Estimate0product lines/100-250contained harness
lines/no product resident-memory increase. Pin current EXEs, local reference,
config/CPU budget, audio/input/resolution/frameskip and actual game/display
counts. Existing HUD proxies and unequal-resolution measurements do not prove
a speed ratio. Begin by reconciling retained benchmark dependencies and phase
measurements; then instrument only missing accounting. Installed DOSBox config
and640x400default stay unchanged; separate per-run experiments cannot stand
in for default playability. No new source/runtime import or product helper.

Products remain P11, no code change or refresh in P12. ROM scope/expected/
actual[],new0,historical1992/1992,local1991/1992nodes and4260/4261feasible
controls(raw4342,infeasible81). S5 receipt has zero node credit/custody transfer.
Governance/node/diff gates precede commit. T32 remains open through S9.

## S5 P1 initial dependency inventory

Read-only reconciliation finds six retained comparator trials:five MySMB
images and one reference image. None uses the current300549-byte DOSproduct;
the named current-20000trial is301145bytes. Local historical trials also mix
fixed20000/max cycles and audible/muted output. Keep them as historical leads,
not current speed or equal-frame acceptance. One reference binary identity
is present; actual display-submission counts are absent from these receipts.
No installed config change or new run/source import occurred.
Next measurement must bind the current per-frame owners and count actual
game updates/submissions; retained S4 phase timings guide instrumentation
but do not replace fresh current-output accounting. Reconcile changed startup
hooks and probe overhead separately from game/PPU/mapping/VGA/cache costs.
Contained inventory harness30lines,zero product lines/resident changes.
All three current products stay P11. Expected/actual node/control credit zero.

## S5 P2 current counted phase budget

Rebuild the contained diagnostic from current main/root/devices owners and
the actual P11objects, including both startup hooks. Count reached game tick
calls and completed VGA/text writes, not HUD timer changes. Installed DOSBox
config hash remains0494236f2308e2e615f428d04e6470db4b0d162c95b51f4e276f1b7e73241917;
no setting or product code changed. The private-desktop scripted route covers
title, restore, ordinary play/movement, graphics/text switching, save and exit.
It does not establish dense/scroll/death route thresholds or a reference ratio.

Full phase probe:173updates,148graphical/26text submissions,3700successful
row reads;167records,zero drops,10title logs skipped without dropping updates
or drawing. Restore produces one extra presentation without a game update.
Selected running cohorts:81graphics and25text updates, each exactly one
completed presentation. Graphics median648.462ms:PPU393.232(60.64%),mapping
197.582(30.47%),VGA28.941,game9.181,snapshot10.446. Text453.254ms:assembly
366.358(80.83%),device65.454,game9.186,snapshot10.446.

Repeat with phase timer calls removed, retaining update/submission counters:
177updates,152graphics/26text,3800row reads;171records/zero drops. Selected
84graphics/25text updates each submit once. Counter-only medians634.259/
452.101ms. Observed full-versus-control difference14.203ms(2.19%)graphics and
1.153ms(0.25%)text; wall-timed routes have different update counts, so this
is an observed instrumentation control, not a matched-state causal speedup.
Both remain far over16.67ms; do not publish diagnostic Hz as formal product FPS.
Both runs exit normally with source-bound CRC-valid saves and unchanged config.

Static current-source workload explains a bounded S6 lead:25bands rebuild
250source rows for240logical rows. At scrollY0,50coarse tile-row groups still
repeat8000horizontal span calculations; preparing32spans per group would
reduce that setup work to1600, not the whole frame cost by five times. An
initial33entry temporary span descriptor can fit198near bytes with no new
resident cache. Evaluate DOS-generated code, stack and exact raw/cached output
before adoption. Existing CHR decoding is baseline, not a new optimization.
Avoid per-sprite raw CHR reads when decoded rows already provide the values,
and defer out-of-band sprite attributes until after vertical rejection.

S6 decision:one bounded PPU candidate cohort,not repeated single-line repairs:
temporary coarse-row span preparation plus sprite-row/classification costs.
Keep each candidate only with measured material benefit and no unacceptable
startup/resident/stack cost. Retain existing scroll/split/mirroring,palette,
clipping,priority and fallback behavior. Optional opacity representations
need independent proof; never infer background opacity from final RGB color.

The reference's actual submission counts and equal-route/minimum-cycle
thresholds remain unproved. The only retained reference comparison used
different resolution/frameskip and stale MySMB products. No faster-than-
reference claim is accepted. Broader route matrices are required during
candidate validation and final S9 acceptance, not inferred from this cohort.
Recipes/count receipts below ignored build/m3-t32-s5;zero product lines,
no product resident increase or three-EXE refresh. Historical1992/1992,
local1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81),new0.

## S5 P3 baseline-budget closure and S6 admission

S5's current packet exit is a source-bound phase budget, measured or explicitly
unproved comparator disposition, memory costs and bounded S6 decision. Those
deliverables are now present in P1/P2. Close this baseline measurement S;
do not call the fair reference/minimum-cycle or full-route acceptance passed.
Those named final-work obligations stay open in S9, whose approved contract
already requires them. Candidate scroll/dense/death/output coverage belongs
to S6-S8 validation as well. No claim that the single measured running cohort
represents every game phase. Default cadence remains FAIL, not repaired by
changing cycles, resolution, draws or frameskip.

Admit S6 alone under the approved consecutive plan:one shared PPU composition
cohort in src/ppu/frame.c and focused tests, 80-240candidate product lines.
First prototype coarse tile-row span preparation and sprite classification/
decoded-row work together; retain an individual variant only when exact
output and original-DOS cost/memory justify it. A33entry span representation
can use198temporary near bytes; no new persistent allocation is authorized
without a measured budget amendment. Audit actual compiler stack and all
affected call frames before adoption. Current2048stack,640x400default,
256x240indexed contract, 64colors and three-platform shared semantics remain.

Entry/exit is const PPU state -> exact indexed full frame or requested rows;
no translated game/RAM/NMI/OAM/palette mutation. Invalidate temporary span
work at tile-row, fixed-HUD/scene, scroll/bank transitions; lifetime is one
const compositor call, not an unchecked cache across game ticks. Preserve
sprite order/priority, clipping, flip, raw CHR bounds and no-cache fallback.
Do not encode opacity in final palette colors or mask away input values.
Optional opacity schemes require a separately checked variant in this cohort.

Verification:independent512-state raw/cache/band cases on x86/x64, guarded
capacity/edge/split/palette/CHR routes, original-DOS controlled exact-output
and cost scenes plus actual gameplay before adopted delivery. Compare current
source/object and memory/stack bindings; require material whole-step benefit,
not only one inner-loop statistic. No new ROM/source/runtime import, helper
process or installed DOSBox settings. Product-code P rebuilds/publishes three
EXEs; prototype/evidence P does not. S9 final checks remain OPEN.

Coordinator admits under the owner's approved S5-S9 plan and automatic
successor instruction. Scope/expected/actual[],new0;historical1992/1992,
local1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81). No ROM
custody event. S5 closes only its stated measurement contract; T32/goal remain
open. Documentation/node/diff gates precede commit.

## S6 P1 systemic comparison and rejected incremental direction

Owner explicitly stops the small-percentage optimization strategy and asks
for a systemic comparison with NESticle's multi-fold advantage. All five
initial prototypes remain local and unadopted. Each passed512independent
native states per width and1,161,555controlled DOS output bytes. Temporary
span preparation regresses ordinary PPU cost2.68%;combined improves ordinary/
dense-background/dense-sprite PPU2.18/8.28/8.89%;lazy4.35/2.29/5.19%;sprites
4.85/2.06/5.05%;coordinate variant4.87/2.07/5.19%. These compositor-only
single paired cases do not address the owner's gap. No micro-optimization
is selected for product integration.

Direct read-only inspection binds athros/NESticle master Source files and
their directory blob identities below ignored build. MAIN.CPP identifies0.2;
owner binary/README identifyx.xx. LICENSE is only a Bloodlust copyright notice,
no redistribution grant. No source is copied/transliterated into MySMB;
retain conceptual architecture and neutral metadata. No exactx.xx claim.

| Axis | Direct historical reference evidence | Current MySMB consequence |
| --- | --- | --- |
| Cache level | NESVIDEO.CPP199-255/H107-140 retain composed256x240 surfaces; writes mark dirty tiles/attribute regions | Workspace retains only8192decoded CHR bytes;unchanged backgrounds are recomposed every frame |
| Scroll | NESVIDEO.CPP363-419 clips/blits cached regions, with pattern-bank fallback | 25callbacks rebuild250source rows/8000tile-row spans and scan64sprites per band |
| Pixel meaning | TILE.ASM keeps palette-slot/raw-color information;SPRITEBG.ASM tests destination information;palette refresh changes display slots | Flattened master-color bytes lose opacity/slot identity;behind sprites re-decode background opacity |
| Transfer | TILE.ASM flat486 path uses two DWORD stores per8pixel row | Original/AL mapper16source->20destination loop has36LES instructions;4000groups execute144000segment loads per frame |
| Payload | Ownerx.xx configuration requests256x240;README also lists other modes | Required320x400ModeX/640x400scanout writes128000plane bytes vs61440native indexed pixels,2.083times payload |

References:[video/cache](https://github.com/athros/NESticle/blob/master/Source/NESVIDEO.CPP),
[write invalidation](https://github.com/athros/NESticle/blob/master/Source/NESVIDEO.H),
[tile assembly](https://github.com/athros/NESticle/blob/master/Source/TILE.ASM),
[sprite priority](https://github.com/athros/NESticle/blob/master/Source/SPRITEBG.ASM).
These are structural findings, not measured attribution forx.xx. Do not copy
reference clipping/palette/timing limitations into the faithful PPU contract.

Current648.462ms diagnostic has393.232PPU/197.582mapping/game9.181ms.
With other costs fixed, fivefold needs total129.692ms, leaving about72.044ms
for PPU+mapping vs590.813:87.81%less time, about8.2times faster there.
Deleting game work alone buys1.014times;mapping alone1.438times;PPU alone
2.541times. These are approximate budget-model limits from scoped medians,
not hardware promises. Both major stages need architectural change.

Revised existing S6-S8 direction, no new identifiers:

- S6:cache composed nametable information across frames, refresh changes once
  per frame, preserve opacity/palette slots through composition. Keep CPU/RAM/
  NMI/OAM/palette writers unchanged;detect changes at the const PPU consumer
  boundary. An explicit prepared-frame lifetime avoids25cache validations.
- Compare memory tiers. Two8-bit surfaces cost122880bytes before metadata;
  four-bit background slots cost61440plus2048source bytes, about62KiB before
  control fields. This compact form is a design lead, not implemented or
  accepted. Prototype real DOS allocation/startup/stack/fallback costs first.
- S7:bounded bulk scaling/packing/transfer with segment setup outside inner
  loops;word/DWORD-capable DOS paths only if original tools support them.
  Evaluate staging fusion. Preserve640x400, colors/rows and neutral output;
  device code receives pixels, never game objects or PPU business decisions.
- S8:integrated speed/conventional-memory balance. A remaining multi-fold
  deficit triggers a pipeline revision, not more tiny repairs as closure.
  Equal-frame reference/representative-route thresholds remain S9requirements.

No product/source/EXE/settings change. An earlier failed harness compile
launched a stale control;it lacks new RENDER markers and is excluded. Corrected
supervision stops on build failure and checks new marker/image bindings.
Accepted runs are terminal, outputs/save exact and installed config unchanged;
102observed stack-pattern bytes unused is a fixture result, not global proof.
S6/T32/goal active;scope/expected/actual[],new0,historical1992/1992,
local1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81).

## S6 P2 compact persistent-background prototype

Project-owned implementation stays below ignored build. Two nametables use
61440packed slot bytes plus2048source snapshot bytes:63488borrowed bytes.
DOSworkspace28bytes vs original12,prepared view10bytes;existing8192CHR cache
separate/optional. Refresh only changed tiles/attribute regions, keyed by
immutable CHR pointer/size and pattern bank. Palette/scroll/HUD changes reuse
slots and map current colors. Prepared const-state batch has explicit begin/
end;standalone calls validate independently. Original state is never written.

Both native widths pass512independent states/256zero-alias cases, full/raw/
cache/bands/planes, source immutability and guards. Additional cases prove
cold1920tiles,steady0,one tile1,attribute16,palette/scroll/HUD0,pattern/resource
changes1920,ended-view rejection,short-cache fallback and cache bounds. Bulk
row reading initially failed scroll255at a nametable edge;corrected table
switch passes the same test. Arbitrary palette bytes remain exact, not masked.

Original/AL/Gs DOS compile and real DOSBox diagnostic pass with installed
settings unchanged. Probe allocates63488cache and two4096output bands and
compares requested pixels with a separately compiled baseline. Three warm
passes update0tiles. This allocation is not full-product startup proof.

| Synthetic case | Baseline ticks/3passes | Cache ticks/3passes | PPU ratio |
| --- | ---: | ---: | ---: |
| Uniform tile | 2072454 | 1296338 | 1.599times |
| Mixed tiles,fine scroll/HUD | 2265234 | 1378369 | 1.643times |
| Same background,dense behind sprites | 3332270 | 2254603 | 1.478times |

Cold1920tiles2369346PIT ticks is1.986seconds;changed1912tiles2327333ticks.
Unchanged preparation uses one2048-byte comparison (614ticks in the sampled
third case). These are single diagnostic pairs, not game FPS/hardware proof.
Pixel output is exact but cache memory/cold cost are material. Fivefold target
is unmet;no product adoption or EXErefresh. S6/T32/goal remain active.

The compact representation still unpacks/maps all rows. Next compare directly
copyable master-color byte surfaces with separate raw opacity. Two122880-byte
surfaces plus15360opacity/2048source/16palette bytes total140304before small
fields. This is an explicit local prototype budget lead, not product adoption.
It requires palette-group/universal-color invalidation, bounded far blocks,
actual conventional-memory/startup/fallback and cold/steady/transition proof;
compare smaller tiers as well. Original game/2048stack/640x400stay unchanged.
Recipes/logs remain below build/m3-t32-s6/slot;no imported implementation.
Scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes,
4260/4261feasible controls(raw4342,infeasible81).

## S6 P3 owner-approved compact-cache adoption

Owner explicitly accepts the63488-byte compact cache and measured warm PPU
benefit. Shared PPU owns packed palette slots, source snapshot/invalidation
and raw opacity. DOS/Windows roots only allocate/bind;the DOS prepared view
ends after the synchronous25-band presentation, including failure. Mandatory
root/text/snapshot/device initialization precedes optional allocation. Matching
far free runs at shutdown;failure falls back without changing game state.
Windows uses static cache storage. No core/writer/tick/device-mapper change.

Production change shared PPU+190/-11, DOS composition+11/-3, Windows+3;
tests+57/-4. Review scope includes tile and attribute updates, all fine scroll
values/nametable crossing, sprite priority/flips/clipping, universal palette
aliases, arbitrary palette bytes, pattern bank/CHR bounds/null/short resources,
restore/state changes, cache allocation failure and ended-view lifetime.
All production call sites bind through roots or the standalone legacy APIs;
there is no host-owned invalidation or serialized cache. No scope transfer or
ROM-node promotion. The scroll255prototype correction remains covered.

Native15tests per width pass, including independent512-state row comparisons
(188743680strip/65536000plane bytes per width),256zero-alias cases and cache
mutation/count/guard/fallback checks. Final rows add null-workspace prepared
fallback and null-state rejection. Actual Windows startup, three owned-console
Tab/input routes and Escape pass on private desktops. Strip preserves PE
runtime sections;subsystem and machine types are verified.

Original/AL/Gs product build passes,192segments/max32768bytes;DGROUP49168,
stack2048. DOS EXE304485bytes(+3936);logical loader328624..344976,
page-rounded328768..345120. These bounds exclude dynamic heap. Actual product
DOSBox routes use unchanged installed configuration and private desktops:
448KiB available passes with observed owned449904bytes;384KiB passes with
386384bytes and cache allocation fallback;370KiB returns clean init failure.
Cache adds63520arena bytes (63488payload+32management) in the same product.
The fallback floor is not unchanged:compiled code/root/heap layout growth
also costs memory. Prior377856observed peak is not a universal bound. Both
successful routes restore, exercise D/J, switch text/graphics,save and exit;
three640x400captures and valid changed10035-byte snapshots are retained locally.
Arena observers avoid stale CRT offsets;STACKMETA zeros are not stack proof.
Their samples show no bad chains/drops, not continuous/kernel maxima.

Products refreshed in the three existing owner-authorized slots:

| Product | Bytes | SHA-256 |
| --- | ---: | --- |
| DOS16 | 304485 | bfddd77d941d5932cbb329e37b22bcab81563d988e28c13dd279f044a41bc2fe |
| Win32 | 314894 | 4e51f68b48a38c5182b5305832a8b28a1f22f0edb993d85c737ac601b4fe8652 |
| Win64 | 328206 | 523f0159df62ad97c3a81f39260388e71dab25fde284df376fdabb0609a5864a |

Warm compact PPU1.478..1.643times is the retained controlled prototype result,
not actual full-game FPS. Cold1920-tile1.986second diagnostic remains a material
cost;transition/cadence/global stack/continuous memory and physical486 checks
are unproved. An optional extra listing probe stalled and was stopped;it is
excluded as evidence. The complete original-toolchain product build passed.
The140304-byte byte-surface comparison passes native/DOS pixel checks and
shows warm synthetic ratios11.002/11.103/3.060;it is NOT adopted or a product
speed claim. No new third-party implementation enters the repository.

S6/T32/goal remain active;system-level acceptance has not been declared.
S7's144000segment-load VGA mapping issue remains the next architectural lead.
Recipes/logs/output identities are in ignored build/m3-t32-s6/p3.
Scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes,
4260/4261feasible controls(raw4342,infeasible81);fixed M2 certificate remains
6/136groups and42/952facets with four final packages pending.

## S6 P4 bound cost/stack evidence and scoped closure

The current original-compiler listing object's execution records match the
published DOS product object's OMF segment/external/public/data/fixup records.
The current DOS root listing is similarly bound and confirms14argument bytes
at its prepared-row call versus the former18-byte ABI. Current PPU17functions
have balanced local control-flow/returns. Original-source baseline10functions
provide the comparator;not a replacement global linked-runtime certificate.
Own row chain excluding entry/external bodies is468bytes versus464;adding
the root's row-call arguments gives482in both. Cached row scratch296bytes
versus fallback328;frame internal56,prepare local52/own composed96. External
memcpy/memset/memcmp bodies, CRT/startup, IRQ and firmware/kernel remain outside
this local proof. It establishes the changed-compositor stack budget, not a
global2048-byte stack certificate. No current local CFG mismatch remains.

The first temporary-source compile produced different execution records and
is excluded from published-product claims. Rebuilding with the full product
invocation/source location restores exact binding. A long baseline command
hit the historical wrapper's argument buffer;shortened commands work. No
toolchain/settings change or failed/stale benchmark is accepted.

The final cost runner links the exact published PPU object and exact P11
baseline object in one process. Only five baseline public symbols are renamed
in OMF for coexistence;no baseline code/data/fixup bytes change. DOS output
comparisons pass with current constants/palette/scroll/split/behind-sprite
cases, same installed DOSBox configuration. Three-pass baseline/cache ticks:
2072455/1296338,2265234/1378367,3332270/2254604;ratios1.599/1.643/1.478.
Cold1920tiles2369351ticks,changed1912tiles2327338,steady608/zero rebuilds.
These remain controlled PPU costs,not full-game FPS or equal-framex.xx speed.

S6 closes its bounded cache architecture/adoption contract:variants disposed,
owner-approved memory tier selected,pixel/invalidation/lifetime/fallback
verified,current compiler cost/local stack bound,actual startup/resident routes
and three delivered products. No product code changed in P4;P3's three EXEs
remain current. The already named S8/S9 integration/transition/cadence/global
stack/continuous-memory/reference/hardware checks remain OPEN. Closure does
not assert fivefold speed or complete the goal. No unfinished ROM custody.

Admit S7 alone under the approved consecutive plan. Entry neutral indexed
source rows -> exact320x400four-plane packed output -> unchanged640x400VGA
scanout. Main lead is repeated far pointer segment loads:36LES per16->20
group/144000perframe in the retained mapper. Prototype explicit segment-once
packing under platform/vga and/or a DOS-private neutral helper;retain portable
C fallback,all64colors/full source rows and legacy interfaces. Do not change
core/PPU writers,cache tier,640x400default,toolchain,installed DOSBox settings,
frame cadence or production process count. No new persistent allocation.

Estimate80-180candidate product lines and80-160focused test/harness lines;
prototype first,inspect register/far-pointer/stack ownership,verify every plane
and strip against existing math on native and original DOS,then measure whole
mapping/submission cost and actual scenes. An adopted product-code P must
rebuild,verify and publish all three EXEs. S7 fixes its own known failures
before closure;S9 is final audit only. S8/S9 remain planned,queue unchanged.
No third-party code copied;retained conceptual comparison/source policy applies.
Scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes and
4260/4261feasible controls(raw4342,infeasible81). M2 fixed audit remains
6/136groups,42/952facets,four final packages pending. Local recipes/receipts
stay in ignored build/m3-t32-s6/p4;S7 in build/m3-t32-s7.

## S7 P1 segment-once packing prototype

Project-owned DOS-private inline assembly stays below ignored build. The
validated neutral row helper loads DS source and ES destination once per row,
packs the exact four80-byte plane sequences with word/byte stores,then restores
DS/ES. Compiler preserves SI/DI/BP;BX/CX/DX/AX are transient computation
registers. Ten argument bytes plus four return-address bytes reach a helper
whose local scratch is2bytes and maximum own stack12bytes. Seven current
prototype functions have balanced local CFG/returns;helper has no nested call
or loop stack growth. This is a local compiler contract,not global stack proof.
Source/destination remain disjoint borrowed spans;no new persistent allocation.
Source/output segments may differ;stride1..16rows is within1280bytes. Both
regions stay within the existing single-segment capacity contract.

The source offset table and320x400mapping/masking/math remain unchanged.
Every output byte still equals source[floor(y*3/5)*256+floor(x*4/5)]&63;
640x400scanout remains unchanged. Segment setup moves from36LES per16->20
group to one LDS/one LES per source row,not a new game/PPU code path. Portable
C fallback remains selected on native builds;legacy interfaces are untouched.

Original/AL/Gs compiler/link pass. Paired DOS runner reuses the current
published mapper object's code/data/fixups,renaming five exports and one
internal external-name reference only. Same process compares64cases/155520
bytes with zero/repeated/end rows,all8-bit source values,guards and DS restore;
the second run additionally checks source bytes unchanged. Three full-frame
packing passes use699524/363243ticks and699525/363248ticks:1.92577/1.92575times.
Default installed DOSBox configuration is unchanged;private desktops only.
These are controlled complete-packing-stage costs,not full-game/frame cadence.

Native original portable fallback checks all valid first-row and1..16row
heights:16972800compared bytes per width,guard/invalid rejection pass. No new
ROM or third-party code/asset import. Initial prototype setup expected five
OMF names but found the retained sixth internal reference;all six are renamed,
no code bytes changed. That failed setup produced no accepted/stale run.

P1 selects the segment-once candidate for P2 product integration and actual
startup/restore/Tab/input/output/exit/memory proof. S7 remains active. Product
source and all three S6 P3 EXEs are unchanged;no artifact refresh required.
No global stack/continuous-memory/fivefold speed/playability acceptance.
Exact recipes,objects,listings and run identities remain below build/m3-t32-s7.
Scope/expected/actual[],new0;historical1992/1992,local1991/1992nodes and
4260/4261feasible controls(raw4342,infeasible81). Fixed M2 final work unchanged.

## S7 P2 integrate and deliver segment-once packing

Adopt81platform/vga lines:private DOS row helper and compile-time selection;
portable C fallback/public ABI unchanged. No core/PPU/root/input/device-mode
changes or new persistent buffer. Register/stack/capacity/color/source alias
sweep retains P1 proof;product-bound original compiler listing matches the
linked VGA object's execution records. All seven local CFGs balance;helper
local2/own maximum12bytes,arguments10/far return4. IRQ source/prologue still
preserves incoming DS/ES and establishes its own data segment;no handler
changes. Global IRQ/kernel/CRT stack proof remains open,not inferred here.

171directory object outputs compared to S6 P3;only the VGA mapper's execution
records differ. This count includes auxiliary probes,not a linked-unit claim.
Native runtime sections remain identical;rebuild/strip/actual startup/Tab/input/
Escape checks pass on both widths,plus15focused tests each. Exact product
mapper/P3 baseline paired runner passes64cases/155520bytes,DS/guard/source
checks:699525vs363248ticks for three full mapping passes,1.92575times. This
is complete-packing-stage evidence,not actual whole-game/FPS acceptance.

Actual original-DOS products pass restored gameplay,D/J,Tab text/graphics,
save/Escape routes in448KiB(cache enabled) and384KiB(fallback) arenas.
Observed owned peaks449696/386176bytes,each208below S6 P3;370returns clean
initialization refusal. Arena chains/drops remain zero,all three640x400
captures and changed10035-byte snapshots are valid. Installed DOSBox
configuration/scanout remain unchanged;all UI on private desktops. Observer
STACKMETA zeros do not prove stack usage. Sampling is not a global maximum.

DOS EXE304277bytes(-208),DGROUP49168/stack2048unchanged;logical loader
328416..344768,page-rounded328768..345120unchanged. Three products refreshed:

| Product | Bytes | SHA-256 |
| --- | ---: | --- |
| DOS16 | 304277 | 14fedb007d624aa0466f7a417a4643d9dd3542db157836bcc84590c4729f8471 |
| Win32 | 314894 | e799387472eec2f173f82477435b75cb24dbe40b5b2198196af432a6ba6781e2 |
| Win64 | 328206 | a9fdb14f25678f4cdd482da23ebe478f0eb8910e58b5da1fffb6faff92671428 |

Only owner-authorized existing product slots are refreshed. Native hash
changes do not imply runtime changes;section comparison passes. No imported
implementation or protected fixture enters tracked source/evidence. Local
recipes/listings/probes in build/m3-t32-s7/p2. S7/goal remain active;stage
acceptance does not close S8/S9 whole-game/reference/transition/global memory/
stack/hardware obligations. Scope/expected/actual[],new0,historical1992/1992,
local1991/1992nodes,4260/4261feasible controls(raw4342,infeasible81);M2 final
certificate unchanged6/136groups,42/952facets,four packages pending.

## S7 P3 owner-directed two-component platform layout

Owner requires platform to contain only dos16 and win32. Remove file,text,vga
children entirely. Shared file/path services move to io/file;host replacement
and executable-discovery declarations move into the appropriate platform
headers. Portable plane mapping moves to io/planar_frame;DOS assembly is
platform/dos16/planar_row. DOS composition explicitly supplies the neutral
synchronous row encoder;IO has no platform selection/import/assembly. Legacy
public mapping interfaces retain portable behavior. Retired80x25pixel sampler
moves to validate/text_frame and remains test-only. CMake owner targets,
original-DOS source lists,all source/test/tool includes and current design
authorities are reconciled;historical source-location receipts remain history.

Architecture gate enforces exactly two platform components,no cross-host API
imports,no host declarations/assembly in IO;portable stdio is allowed only for
io/file. Synthetic negative checks reject a third component,IO assembly,IO
host declaration and cross-host include. No dummy source is placed in the
repository's production directories;all fixtures below ignored build.

Both native widths pass15existing focused tests plus three moved-file/path/
retired-sampler/snapshot-binding tests. The complete first-row/1..16height
plane matrix additionally compares the optional row encoder with the portable
owner byte-for-byte. The Windows text-switch fixture is rebuilt but not a
registered CTest;actual product startup/Tab/text input/Escape routes pass on
private desktops. DOS actual448KiBcached/384KiBfallback restore,D/J,Tab,save/
exit and all640x400captures/10035-byte snapshot integrity pass. No installed
DOSBox configuration or foreground desktop change.134core/PPU object outputs
have identical execution records to P2;no original game/PPU semantics change.

Actual selected IO+DOS product objects are linked against the previous fast
mapper:64cases/155520bytes,source/DS/guard equality passes. Three-frame
packing363249->364555ticks(+0.35953%cost),not a whole-game speed result.
Explicit component separation costs528EXE/resident bytes,no persistent buffer.
Observed owned450224cached/386704fallback;sampling is not a global maximum.
Original/AL/Gs compile/link:193segments,max32768,DGROUP49168/stack2048unchanged;
logical loader328944..345296,page-rounded329280..345632. Global memory/stack,
whole-game/reference/physical486qualification remains unproved S8/S9 work.

Three existing owner-authorized products refreshed:

| Product | Bytes | SHA-256 |
| --- | ---: | --- |
| DOS16 | 304805 | dbb554cc1b6275a5b7fb6b3e1c6d78cbd293ac0d612e3f0b4f31f5d5dc2691f7 |
| Win32 | 314894 | 576f134262432f671147fd13c649fab6773048156188f57e912a3df86a9d84f9 |
| Win64 | 328206 | 9777faa28df309bb17d6d31b4cdfbf3c20114c231c274fc65e757e71f213f3fa |

Scope/expected/actual[],new0;historical1992/1992,local1991/1992nodes and
4260/4261feasible controls(raw4342,infeasible81),M2 certificate counters
unchanged. No new third-party/protected fixture import. Reproducible local
build/test/negative/cost/source-product receipts below build/m3-t32-s7/p3.
S7 and the memory/performance goal remain active beyond this ownership fix.

## S7 P4 current integrated budget and scoped closure

Current three platform owners regenerated with bounded instrumentation;
all other objects are exact current-product library members. Current game/
PPU/IO/DOS row encoder unchanged. Cache begin preparation is included in PPU
phase,not missed between25row callbacks. Diagnostic sampler256far records
about24KiB,not product memory. First link failed on a nested PowerShell JSON
array;fixed recipe flattens object names,no stale failed build accepted.
Each unique private-desktop route bounds150seconds/4MiB captured output;
installed DOSBox settings and all game/work/presenter/input behavior retained.

Phase probe227records/zero drops:233updates,208graphics,26text,5200row reads.
Restore adds one presentation. Counter-only235records/zero drops retains
actual tick/submission counters with no per-stage clocks. Successful graph
submissions require25reads;one completed game update produces one selected
presentation. Phase running graphics125frames median419.402ms;steady120frames
same,dirty5frames472.669ms,each one rebuilt tile. Phase medians PPU257.645,
mapping104.008,VGA28.942,game9.181,snapshot10.450ms. Median component values
are not additive exact per-frame totals. PPU61.43%,mapping24.80%,VGA6.90%.

Counter-only running graphics131frames405.309ms;steady125frames405.307ms,
dirty6frames458.132ms. Text25frames451.980ms remains unchanged. Counter-only
reduces phase-clock overhead;it is still an instrumented diagnostic,not actual
product FPS. Prior S5counter634.259ms/current405.309ms suggests36.10%lower
cost/1.565throughput in comparable running cohorts,not equal-state paired
end-to-end proof. Nominal60Hz/fivefold acceptance FAILS;physical486 unqualified.
One-tile preparation costs about53ms from scanning unchanged cache entries.
This finite finding belongs to S8's already planned integrated reduction.

S7 closes its display-stage contract:segment-efficient candidate adopted,
exact/native/original-DOS/register/local-stack/product routes verified,
ownership correction delivered,whole-stage and current system budget recorded.
No P4product change;three P3EXEs remain current. This closure does not complete
T32/goal or pass S8/S9 whole-game/reference/transition/global memory/stack gates.

Admit S8 alone under the approved consecutive plan. Focus one shared rendering
chain:frame begin/background invalidation -> palette-slot row expansion ->
unchanged indexed output. First compare row/block-level dirty rejection and
generic packed4-bit palette-pair expansion,with explicit DOS-private bulk
operations if justified. Shared PPU retains all source/scroll/priority/mask/
opacity/control semantics;IO sees only bytes/colors/capacity,platform sees no
game/PPU state. Keep two platform components and no target execution in IO.

Estimate160-300candidate product lines plus150-250contained tests. Local
prototype budget permits a530-byte pair/palette workspace plus small bind
fields,preferably optional near storage within existing reserve;no extra far
surface or full-frame buffer. This is comparison budget,not adoption. Actual
code/load/resident/stack and original-toolchain cost decide retention;failure
must retain the original output path. Pair colors preserve arbitrary8-bit
values. Require512independent native states,source/cache/guard/restore/palette/
bank/scroll/priority and actual DOS exact output,then whole-stage/current-frame
cost. Adopted product code refreshes all three EXEs. No140304-byte tier or
sampling/artwork/game rewrite. S8 repairs its own findings before closure;
S9 remains final audit. Source/research containment/queue unchanged.
Scope/expected/actual[],new0,historical1992/1992,local1991/1992nodes and
4260/4261feasible controls(raw4342,infeasible81);fixed M2 certificate unchanged.
Recipes/source bindings and outputs remain below build/m3-t32-s7/p4;
new bounded prototypes under build/m3-t32-s8. Global goal remains active.
