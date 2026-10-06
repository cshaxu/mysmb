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
