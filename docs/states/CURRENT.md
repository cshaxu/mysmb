# Project Status

## M3 T28 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: M3 T28 S6 P12; contained read-only PPU cost evaluation after four-plane adoption; CRT/stack/cadence gaps retained. |
| Admission And Approval | Owner authorizes execution and the joint conventional-memory/playability contract. Owner accepts the rowwise memory/performance tradeoff and admits implementation;repeat-row/OAM tuning is deferred to TODO. S5 closed;S6 remains active. |
| Objective | Reconcile S1-S5 memory census;verify actual minimum-free launch/runtime fit,stack/lifetimes,normal cadence/input budgets and clock sampling;dispose all six opportunities with fit/playability separate hard gates. |
| Non-goals | No core ROM routine/state/timing changes,no emulator settings,no text artwork or VGA coordinate/mode changes,no emulator-based physical486SX/DOS-version or M2 certification. |
| Reference Baseline | Post-T27 source and retained three products;historical1992/1992,local1991/1992 nodes and4260/4261 feasible controls,raw4342/infeasible81. |
| Candidate Proposal | [T28 retained proposal and audit](../history/M3-T28-dos-rendering-optimization.md). Removed from pending QUEUE on admission. |
| Files And ABI Surface | Integrated DOS root/device timing and memory/performance probes;initial audit0product lines,selected four-plane integration3product files plus focused tests,100-220changed lines after pre-code report. No core/PPU-state/snapshot schema changes. |
| Applicable Rules | README Task Reading Set,EXECUTION,DOCUMENT,ARCHITECTURE,CODING,CONTRIBUTING and source policy. |
| Verification | Independent128000-byte mapping and actual VGA-plane readback,far guards,mode/restore lifetime,native x86/x64 and original DOS16;fixed-config complete-output/input cost,MCB/near/far peak and contiguous/stack/fallback under the memory contract,platform purity and three EXEs for each product-code P. |
| Expected Markers | ROM scope[],expectedMatches[],actualMatches[],new0,maximum1992/1992;no custody transfer. S6 owns infrastructure-only implementation;original node custodians unchanged. |
| Asset Needs | Existing owner-local resources/derived products only,local ignored build containment;no new import or redistribution. Prior owner exception for existing tracked EXEs retained;every product-code P refreshes all three,with local probes/resources contained below ignored build. |
| Reporting Requirements | Before each S owners,scope and estimated size;after each P actual diff,tests/products and total/local counters. Report absolute peak bytes,contiguous requirements and whole-frame/input costs,accepted tradeoffs and unproved limits;separate opportunity from measured gain. |
| Stop Conditions | Pixel/state/snapshot/audio divergence,unbounded memory or cache lifetime,unproved required-storage fit,unacceptable playability regression,missing fixed-config timing,or proposed core/PPU semantic change prevents advancing the affected optimization. |
| Exit Criteria | S6/T28 require cumulative complete-route equality,measured minimum-free fit and playable cadence/input budgets,all six dispositions and no unresolved required clause;owner defers extra rowwise micro-optimization to TODO without claiming cadence acceptance;three products for changed code. |
| Original Owner Request | Owner authorizes execution after reviewed T28 plan;preserve original ROM and PPU semantics. |
| Similar-Issue Sweep | Sweep all pixel/text/snapshot/cache consumers and simultaneous lifetimes,resource/mode/restore invalidations and allocation-failure cleanup;record every hit and disposition. |

## Current Technical Baseline

- S6 P11direct four-plane converter adopted:4source/testfiles,+103/-9,no heap
  added. Both widths11tests/13host routes and three actual DOS device/fallback/
  pressure comparisons pass. Formal448/374KiBgame/Tab/save/Esc runs sample
  386240/382144bytes,272below P7. Mapping/submission about29.85percent shorter,
  graphics-return route10.43percent shorter;not nominal cadence acceptance.
  Three products refreshed;Windows hashes unchanged. S6/T28remain open.
  [Integrated output,memory and proof limits](../history/M3-T28-dos-rendering-optimization.md#s6-p11-checkpoint-direct-four-plane-product-integration).

- S6 P10three four-plane prototypes pass both widths16972800-byte mapping tests
  and actual DOS five-frame/640000-plane-byte/text/snapshot equality. Reject
  weak local-output and slower full-row staging;select16-byte/direct-plane
  candidate:about29.85percent shorter mapping/submission,10.43percent shorter
  graphics-return route,288fewer instrumented owned bytes,stack pattern72retained.
  Two selected runs match output. Product source/EXEs unchanged;P11integration
  still needs formal products/fallback/pressure/host gates. S6/T28remain open.
  [Measured alternatives and adoption gates](../history/M3-T28-dos-rendering-optimization.md#s6-p10-checkpoint-bounded-four-plane-alternatives-and-selected-prototype).

- S6 P9stage probe retains92records/zero drops after ten declared title-record
  omissions;all original ticks still execute,cacheNear1preserved. Scoped graphics
  PPU/mapping/transfer occupy58.7/32.7/3.1percent;text construction/transfer88.5/7.1.
  Game tick about9.2ms,less than1percent. Two stage runs agree;diagnostic overhead
  remains explicit. No product edits. Next prototype evaluates shared row/plane
  staging within existing storage;configured cadence and CRT/stack remain open.
  [Measured owners and limits](../history/M3-T28-dos-rendering-optimization.md#s6-p9-checkpoint-cumulative-stage-attribution-without-product-edits).

- S6 P8formal product372KiBbudget exits1,374KiBgame/Tab/save/Esc passes with
  sampled382416bytes;diagnostic localizes failure to20084-byte transaction store.
  Actual-loop78graphics/12text ticks cost about1103/925msmedian;scoped IRQ/input
  lag also exceeds nominal budget. Cadence/input gate fails in unchanged DOSBox.
  Four source allocation sites are bounded,but CRT/continuous peak/all-path
  stack remain unproved. No product edits/EXE refresh;S6/T28remain open.
  [Boundary,deficits and fixed remaining clauses](../history/M3-T28-dos-rendering-optimization.md#s6-p8-checkpoint-lower-launch-boundary-and-actual-loop-deficit).

- S6 P7 adopts shared bounded rows and15400-byte DOS text/pixel store. Formal
  product448/384/376KiBcaller-free routes pass;sampled386512/386512/382416bytes,
  roomy43712bytes below P5. Three device/fallback/pressure routes match five
  frames,640000VGA bytes,text and10035snapshot bytes;heap frees/mode restores.
  Both widths11tests/13host groups pass,three EXEs refreshed. Extra speed work
  stays in TODO;continuous/full-route peak,stack and cadence/input remain open.
  [Adoption and exact limits](../history/M3-T28-dos-rendering-optimization.md#s6-p7-checkpoint-adopted-bounded-row-producer-and-smaller-dos-store).

- S6 P6 contained rowwise prototype passes512synthetic cases per width,
  188743680strip bytes and65536000VGA-plane bytes with guards/state unchanged.
  Maximum2560-byte band fits15400-byte exclusive text store;potential46040-byte
  payload saving is not measured DOS occupancy. Ten repeated source rows and
  repeated OAM scans incur a measured cost. Original DOS16 eight-case far/plane
  probe passes;paired synthetic compute cost rises4.778/5.467percent. Actual
  resident savings remain unproved. No product code/EXE change;owner admits
  P7memory implementation,with extra speed recovery in TODO. S6/T28remain open.
  [Feasibility and boundaries](../history/M3-T28-dos-rendering-optimization.md#s6-p6-checkpoint-contained-rowwise-feasibility-and-integration-boundary).

- S6 P5 full zero-pattern row fill:+3/-0,one PPU source file,no heap. Paired
  output-only water/castle/dense costs0.649/14.116/13.430percent shorter. Both
  widths10focused tests/13private-host groups,three DOS equality routes and
  actual448/416KiBgame/Tab/save/Esc pass. Roomy sampled430224bytes(+64),constrained
  425984;no continuous-peak claim. Three products refreshed. Cached sprite raw
  reads remain a named P6opportunity;default-all harness debt stays in TODO.
  Historical P5receipt retained;rowwise adoption is the P7baseline above.
  [Checkpoint and limits](../history/M3-T28-dos-rendering-optimization.md#s6-p5-checkpoint-exact-full-zero-pattern-tile-row-fill).
- M2 T70/S17 closed by owner-approved deferred-verification transfer (P153);
  [closure record](../history/M2-T70-deferred-verification-closure.md).
  This is not successful full-game acceptance;M2 certificate remains incomplete.
- Historical mapping1992/1992;local scoped nodes1991/1992,feasible controls
  4260/4261(raw4342,infeasible81). CheckForEnemyGroup/control-01480 needs evidence.
- [Audit ledger](M2_AUDIT_LEDGER.md):10691 retained sites/4171 accesses,
  6/136 groups and42/952 facets closed,130 groups/910 facets pending.
  Material993 partial,not a denominator;two findings/all13 coverage slots open.
  Final packages2/6 closed,material/pixels/routes/snapshot pending.
- M3 T9/T10/T11/T12/T13/T14/T15/T16/T17/T18 are closed. Remaining M2 verification stays at the
  [queue](QUEUE.md) tail. Text presentation earns zero ROM certification credit.
- Current local DOS16/Win32/x64 products are304275/320139/328811bytes.
  T22 refreshes all three with RAM-authoritative NMI page handoff;T21 coral,T20 titles/tree/fence and T18 timing retained.
- T11-DOS-COLD-INPUT-P12 is reconciled as a historical incident not reproduced,
  cause unknown,no claimed repair. Historical/current unseeded input checks
  pass;seeded presenter equality is explicitly separate. Real486SX speed,
  full heap/stack peak and hardware/version qualification remain M4.

## Compact closure status

T28 S5 closes exclusive pixel/text reuse,removing15400live bytes. Paired peak
452656to436240bytes,largest contiguous196416to212832. Three DOS routes each
640000graphics/8000text readback,12000text cells and10035snapshot bytes match;
two paired output timing runs equal. Both widths8tests,Windows13host receipts
retain identical binary hashes. Products302879/319627/328299;3code/testfiles,
+66/-4,new0. Full redraw/snapshot recovery retained;S6 fit/cadence/input/clock
clauses remain. S4 storage/output results below remain accepted scoped evidence.
[Evidence and limits](../history/M3-T28-dos-rendering-optimization.md#s5-p1-closure-exclusive-presenter-storage-and-measured-reuse-decisions).
S4 predecessor closes16row batch VGA scratch1280bytes,down from128000;full640x400
mapping and every output retained. Bounded normal peak452432bytes versus S3
578176;complete output16.056-16.588percent shorter in fixed probe. Three DOS
lifetime routes each640000readback bytes,six frames and snapshot equal;mode
restores. Both widths8tests/13host groups pass. Products302927/319627/328299;
6files,+71/-34,new0. Nominal cadence/minimum-free/clock sampling clause remains
S6/M4;T28 incomplete,S5 now closed,S6 integrated audit active.
[Evidence and limits](../history/M3-T28-dos-rendering-optimization.md#s4-p2-closure-bounded-batch-storage-and-exact-repeated-rows).

T28 S3 closes compact8KiB raw-index cache/direct opacity and matched near/far
allocation ownership. Bounded normal peak578176bytes versus S2 610160;external
largest70896 versus38912. Output-only total cost+1.364-3.749percent versus S2,
cold total-9.551percent;not playable cadence certification. Both widths7tests/
13host groups,four DOS ABI cases,four lifetime/fallback routes and paired full
frames/snapshots pass. Products429295/319627/328299bytes;5files,+84/-33,new0.
S4 bounded VGA storage/row reuse active;T28 and M2/M4 qualification unfinished.
[Evidence and limits](../history/M3-T28-dos-rendering-optimization.md#s3-p3-closure-compact-raw-index-cache-and-bounded-opacity-queries).

T28 S2 closes optional per-instance decoded CHR cache;rejected slower palette
staging/naive cache. Fixed-config warm PPU stage12.682-15.579percent shorter,
cold first frame26.389percent longer. Both widths7tests/13host groups,DOS16/far
reference guards,six complete buffers and10035snapshot equality pass. Products
429039/319627/328299bytes;6product/testfiles,+139/-10,new0. No core semantics or
M2/M4/cadence qualification. S3 occupancy comparison active,T28 unfinished.
[Evidence and limits](../history/M3-T28-dos-rendering-optimization.md#s2-p1-closure-optional-per-instance-decoded-chr-cache).

T27 S1-S8 closed:185original file destinations,751functions,143macro entries,
1996consumer sites and206PPU/receipt sites/four seams reconciled.173original
Cfiles normalize equal with declared DMA/PPU/helper owner changes only.
Both widths50tests/13private-host groups pass;original DOS16 and actual DOS
restore/Tab/exit plus paired10035-byte snapshot equality pass. Coarse same-config
cadence sample unchanged;normal DOS/486SX performance remains queued/M4.
Products427455/318603/327275bytes retained,new0;M2 final certificate incomplete.
[Complete requirement dispositions and proof limits](../history/M3-T27-core-ppu-module-boundaries.md#s8-p1-closure---integrated-completion-audit).

T26 S2/T26 close by owner-directed remaining-work transfer:scoped compositor
improvement and full640x400 DOS output retained;fixed-config nominal cadence
remains unproven and belongs to the queued DOS rendering optimization candidate.
No M2/M4 acceptance. Three P2 products unchanged by governance-only closure.
[Closure and transfer](../history/M3-T26-dos16-playable-performance.md#s2-p3-owner-directed-closure-and-remaining-work-transfer).

M3 T24 S4 corrects window/console input gating under unavailable/different
foreground HWND. Old root rejects both targeted event paths,current accepts.
Both widths9tests/13host groups pass,including actual product CONIN Tab->window
Tab->CONIN Escape and waiting CMD prompt. Products364939/318603/326251bytes;
6product/test/toolfiles,+187/-41,new0. Shared game/DOS unchanged;live owner RDP
trial remains separate. [Correction and proof limits](../history/M3-T24-win32-window-console-integration.md#s4-corrective-closure).

M3 T23 S1 closes princess/Toad authored details and retainer-only crown
cell-center anchoring.64palette/form/offset/latch cases,existing864enemy and
16384word cases pass. Both widths9tests/7host groups,2048boundary/1198native
graphics/state checks,actual retainer writer->DMA equality,DOS16/DOSBox pass.
Three products364939/312971/320619bytes;code/test3files,+60/-2,no ABI/new0.
[Retainer evidence and limits](../history/M3-T23-princess-text-detail.md).

M3 T22 S2 closes bounded H01-H10 handoff review:one packet-header RAM/cache
source mismatch repaired in game.c;512divergent control cases fail62 before
repair and pass after. Scroll/split/OAM phases,selectors6/7,palette alias and
snapshot/receipt boundaries reviewed;11tests and7host groups per width pass.
Controlled7-2 retains first-frame page/pipe,2048boundary/1198native comparisons
pass;DOS16/DOSBox pass. Products364817/312971/320107bytes;product/test2files,
+96/-0,no ABI/new node or full-game credit. [Ten dispositions and limits](../history/M3-T22-pipe-exit-display-recovery.md#s2-closure-ten-bounded-contract-dispositions).
