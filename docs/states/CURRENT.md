# Project Status

## M3 T28 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: M3 T28 S4 P2; formal integration after bounded single-plane/row-reuse prototype. |
| Admission And Approval | Owner authorizes execution and the joint conventional-memory/playability contract. S3 closed;S4 is active;P1 prototype evidence retained,formal integration pending. |
| Objective | Compare four-plane storage with single-plane/row/batch scratch and duplicate-row reuse;preserve every indexed/packed output and full borderless640x400 scanout;measure peak conventional storage and complete output cost;fit and playability remain independent hard gates. |
| Non-goals | No core ROM routine/state/timing changes,no emulator settings,no text artwork or VGA coordinate/mode changes,no nominal-cadence or M2/M4 acceptance. |
| Reference Baseline | Post-T27 source and retained three products;historical1992/1992,local1991/1992 nodes and4260/4261 feasible controls,raw4342/infeasible81. |
| Candidate Proposal | [T28 retained proposal and audit](../history/M3-T28-dos-rendering-optimization.md). Removed from pending QUEUE on admission. |
| Files And ABI Surface | platform/vga frame conversion,DOS device/main composition and focused tests/build membership;estimate4-7files,150-350 changed lines. No core/PPU-state/snapshot ABI changes. |
| Applicable Rules | README Task Reading Set,EXECUTION,DOCUMENT,ARCHITECTURE,CODING,CONTRIBUTING and source policy. |
| Verification | Independent128000-byte mapping and actual VGA-plane readback,far guards,mode/restore lifetime,native x86/x64 and original DOS16;fixed-config complete-output/input cost,MCB/near/far peak and contiguous/stack/fallback under the memory contract,platform purity and three EXEs for each product-code P. |
| Expected Markers | ROM scope[],expectedMatches[],actualMatches[],new0,maximum1992/1992;no custody transfer. S4 owns infrastructure-only implementation;original node custodians unchanged. |
| Asset Needs | Existing owner-local resources/derived products only,local ignored build containment;no new import or redistribution. Prior owner exception for existing tracked EXEs retained;every product-code P refreshes all three,with local probes/resources contained below ignored build. |
| Reporting Requirements | Before each S owners,scope and estimated size;after each P actual diff,tests/products and total/local counters. Report absolute peak bytes,contiguous requirements and whole-frame/input costs,accepted tradeoffs and unproved limits;separate opportunity from measured gain. |
| Stop Conditions | Pixel/state/snapshot/audio divergence,unbounded memory or cache lifetime,unproved required-storage fit,unacceptable playability regression,missing fixed-config timing,or proposed core/PPU semantic change prevents advancing the affected optimization. |
| Exit Criteria | S4 resolves exact128000-byte mapping/plane readback/mode lifetime,far guards and measured row/storage candidate dispositions;three products for code changes. T exit remains all six dispositions and integrated joint fit/playability proof. |
| Original Owner Request | Owner authorizes execution after reviewed T28 plan;preserve original ROM and PPU semantics. |
| Similar-Issue Sweep | Sweep scaled coordinate/duplicate-row consumers,plane/address submissions and storage/mode/restore lifetimes;record every hit and disposition. |

## Current Technical Baseline

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
- Current local DOS16/Win32/x64 products are429295/319627/328299bytes.
  T22 refreshes all three with RAM-authoritative NMI page handoff;T21 coral,T20 titles/tree/fence and T18 timing retained.
- T11-DOS-COLD-INPUT-P12 is reconciled as a historical incident not reproduced,
  cause unknown,no claimed repair. Historical/current unseeded input checks
  pass;seeded presenter equality is explicitly separate. Real486SX speed,
  full heap/stack peak and hardware/version qualification remain M4.

## Compact closure status

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

M3 T22 S1 fixes RAM$0778-to-next-NMI page handoff,not cached overwrite.
Old setup regression fails52,old-root controlled7-2 first frame fails14;
fixed source passes16page/128control cases and selects table1 on first restored
frame145,scroll0,with pipe/stairs/full terrain. Both widths8tests/7host groups,
2048boundary/1198native comparisons,DOS16/DOSBox pass. Products364801/312971/
320107bytes;two product/testfiles,+44/-1,no ABI/new node or M2 certification.
[T22 original source,missing integration clause and route limits](../history/M3-T22-pipe-exit-display-recovery.md).
