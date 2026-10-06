# Project Status

## M3 T32 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: M3 T32 S7 P1; prototype segment-efficient DOS plane packing/transfer. |
| Admission And Approval | Owner-approved S5-S9 consecutive plan and automatic successor instruction;S6 compact-cache contract closed by P4;S7 sole active. |
| Objective | Reduce systemic DOS scaling/plane-packing/transfer overhead with exact output and no added resident storage. |
| Non-goals | No game/PPU semantics changes, lost frames, installed DOSBox config changes, toolchain change, helper process or T19 resumption. |
| Reference Baseline | Current S6 P3 products and unchanged mapper;original toolchain/2048stack/640x400. |
| Candidate Proposal | [S5-S9 performance plan](../proposals/m3/dos-graphics-nesticle-performance.md). |
| Files And ABI Surface | platform/vga/vga_frame.c and DOS-private neutral helper if justified;focused tests/original-DOS prototypes;estimate80-180candidate product and80-160test/harness lines. No core/PPU changes or new persistent allocation. |
| Applicable Rules | README Task Reading Set, EXECUTION, DOCUMENT, ARCHITECTURE, CODING, CONTRIBUTING and source policy. |
| Verification | Native full/band/plane math/guard tests and actual original-DOS exact output;segment/register/stack listing audit;whole mapping/submission cost and actual product routes;three EXEs after adoption. |
| Expected Markers | Scope/expected/actual[],new0;historical1992/1992,local1991/1992nodes and4260/4261feasible controls. |
| Asset Needs | Owner-local x.xx binary and ROM plus historical athros/NESticle0.2 source as conceptual reference only; copyright-only leaked tree grants no redistribution permission. Purpose frame/cache/transfer architecture comparison; raw source/probes only below ignored build, no copying/transliteration into product, exact-version claims require binary evidence. |
| Reporting Requirements | Candidate and measured whole-step cost, rejected variants, actual code/memory delta, source/products and total/local node counts. |
| Stop Conditions | Unbounded or foreground probe, source binding gap, ownership violation, output divergence or unsupported speed claim. |
| Exit Criteria | Segment-efficient candidate selected/rejected by exact output,current compiler/register/stack/memory proof and measured stage/system cost;three platforms verified after adoption. Whole-game/reference/global-stack gates remain named S8/S9 work. |
| Original Owner Request | Improve actual memory/performance/playability with original ROM semantics; follow approved S5-S9 division after fixing known S4 defects. |
| Similar-Issue Sweep | All band sizes/plane offsets, source/output capacity, row duplication, color masking, source/output alias contract, DS/ES/BP preservation and fallback. |



## Current Technical Baseline

- S6 P4 closes the compact-cache stage with exact current-object cost and
  local compiler stack evidence:17PPUfunctions balanced;row chain+caller
  arguments482bytes in both versions,external bodies excluded. Final linked
  object diagnostic confirms1.478-1.643PPU ratio;no product change/EXErefresh.
  S7 alone active for segment-efficient VGA packing/transfer;S8/S9 remain
  planned with whole-game/global-stack/continuous-memory gates unproved.
  [Scoped closure and admission](../history/M3-T32-rendering-performance-continuation.md#s6-p4-bound-coststack-evidence-and-scoped-closure).

- S6 P3 owner-approved63488-byte background-slot cache adopted in shared PPU;
  roots allocate/bind and DOS25bands share one prepared view. Native15tests
  per width plus final512-state/guards/fallback checks pass;actual Windows
  startup/Tab/input/exit and actual DOS448/384routes pass. Observed owned
  449904cached/386384fallback bytes;cache block63520bytes.370clean init refusal.
  Three EXEs refreshed304485/314894/328206bytes;DOS49168DGROUP/2048stack.
  Warm1.478-1.643PPU ratio is diagnostic,not game FPS;global memory/stack,
  transition/cadence/fivefold target stay open.140304-byte tier stays unadopted.
  [Adoption and limits](../history/M3-T32-rendering-performance-continuation.md#s6-p3-owner-approved-compact-cache-adoption).

- S6 P1:owner stops micro-optimization adoption. Five exact-output prototypes
  remain local/unadopted;direct0.2reference confirms composed background cache,
  dirty-tile refresh,palette-slot/opacity pixels and flat DWORD stores. Current
  mapper36LES per16->20group/144000perframe. Fivefold budget needs about87.8%
  less PPU+mapping time. S6persistent cache,S7bulk transfer,S8integrated budget;
  no game/product/resolution/toolchain/installed settings change.
  [Systemic comparison](../history/M3-T32-rendering-performance-continuation.md#s6-p1-systemic-comparison-and-rejected-incremental-direction).

- S5 P2:current-owner default-config phase probe counts173updates/148graphics/
  26text submissions;counter-only177/152/26. Every selected running update
  submits once;restore adds one presentation. Counter-only graphics634.259/
  text452.101ms;phase shares PPU60.64%,mapping30.47%,snapshot1.61%. No formal
  FPS/reference claim. Bounded S6lead:198temporary near-byte span metadata,
  original semantics/stack/output validation required. Product code/EXEs unchanged.
  [Counted budget and limits](../history/M3-T32-rendering-performance-continuation.md#s5-p2-current-counted-phase-budget).

- P12 ends S4's owner-approved repair/delivery stage; final proof gates are
  OPEN, not passed by closure. S5 measurement closed by P3; S6 compact stage closed;S7 active,S8 planned, S9 named final
  audit checks. Current DOS normal62/62/DIV63/63 conditional flows rebound;
  current-host strict native routes pass without repairing suspended T19.
  S5 initial inventory finds6retained trials,zero with current300549-byte
  DOSproduct;old comparative speed ratios are not current product evidence.
  [Division and remaining checks](../history/M3-T32-rendering-performance-continuation.md#s4-p12-staged-closure-and-s5-admission).

- S4 P11: fix reproduced dense-environment CRT65546->10allocation overflow
  by omitting unused C envp copy, retaining cinit/physical PSPenvironment/path.
  Build gate163objects/zero consumers; actual getenv/environ negative objects
  rejected. Formal DOS equals tested candidate; dense448route three captures/
  save exact to normal P6;369passes/368clean refusal. Native15tests per width,
  runtime sections unchanged;three EXEs refreshed. DOS300549/logical324672/
  341040(-176),page-rounded/ordinary observed peak unchanged. New CRTaddresses
  need rebinding; other memory/stack/host gates remain open, S4repair stage closed by P12; final gates remain unproved.
  [Repair and product bindings](../history/M3-T32-rendering-performance-continuation.md#s4-p11-repair-dense-environment-crt-allocation-overflow).

- S4 P10: published DOS369KiB route passes with FP/XP observer added,
  2024timer/84DOS-entry observations,7events/no drops;three captures/save
  exact to P6,377856observed owned peak unchanged. Unused-envp prototype
  NOT adopted: EXE/logical loader-176 but page-rounded/observed peak unchanged,
  later wall-timed outputs differ and lack controlled equal-state proof.
  Product source/three EXEs unchanged. Remaining S4 gates stay open.
  [Current route and envp candidate](../history/M3-T32-rendering-performance-continuation.md#s4-p10-checkpoint-current-hook-observations-and-unused-envp-candidate).

- S4 P9: default/normal and DIV-installed025A exit domains both65/65
  conditional local flows; composed CRT maximum142bytes excluding entry,
  cinit6/envp52or78/exit64/DIV70. Named software exit-target gap resolved;
  hook/table lifetime, environment allocation, startup stack transition and
  firmware/kernel/nesting remain unproved. Source/three current EXEs unchanged.
  [Exit-chain bounds](../history/M3-T32-rendering-performance-continuation.md#s4-p9-checkpoint-normal-and-div-exit-software-chains).

- S4 P8: runtime DATA rebind corrected (FP3EE6, XP3EF2..3EF6,
  empty table B7F2); correct startup/binary flags give default63/63 and
  normal-exit65/65 conditional local flows, replacing P7's64/64 summary.
  Product source and three P6EXEs unchanged/current; no refresh required.
  S4 retains repairable known obligations, S5-S8 address performance, S9
  audits combined acceptance. Blanket transfer withdrawn; no S5 admission.
  [Correction and scope](../history/M3-T32-rendering-performance-continuation.md#s4-p8-correction-and-owner-directed-responsibility-boundary).

- T32 S4 P7:current noargv image rebind7472CRTbytes/77aliases;removed
  424-byte parser,852owned functions/current conditional main720/IRQ78.
  Default-hook conditional64/64local flows connected,not lifetime proof.
  __astart05BCcalls owned normal far-return hook,12ephemeral bytes,argv
  persistence0. Product/2048stack/640x400unchanged;five parent gates open.
  S5-S9planned; blanket handoff withdrawn under P8owner clarification.
  [Current startup/CRT binding](../history/M3-T32-rendering-performance-continuation.md#s4-p7-checkpoint-current-noargv-startup-and-crt-binding).
- Owner added [T32 S5-S9 DOS graphics performance](../proposals/m3/dos-graphics-nesticle-performance.md)
  after S4. P12 admits S5 only; S6-S8 planned, S9 combined audit. Final
  memory/cadence conditions remain explicitly unproved.
- T32 S4 P6:noargv hook ADOPTED,8platform lines/build+9/-1,normal original
  ALfar-return. Formal DOSexactP5candidate;977235bytes/three369KiBroutes
  reused by full-image identity,368clean init refusal.Persisted argv0;envp/PSP
  path/input preserved. DOS300725(-420),logical324848/341216(-416),DGROUP49152/
  2048stack unchanged. Native15tests each width/runtime sections equal S3;
  three products refreshed. Strict Windowsstartup/cadence/global stack remain
  unaccepted. P7rebinds current changed startup/CRTlayout andremaining premises.
  [Startup integration](../history/M3-T32-rendering-performance-continuation.md#s4-p6-checkpoint-integrate-original-abi-dos-noargv-hook).
- T32 S4 P5:noargv prototype selected for integration,not adopted.160owned
  units have no parsed-argument consumers;PSPpath/environment setup retained.
  Original ALempty CRTentry far-returns;argc/argv remain0,persistent argc stack
  0observed in three369KiBroutes.977235controlled output bytes exact. Candidate
  300725(-420),logical324848/341216(-416),DGroup49152/2048stack unchanged.
  Product source/three S3EXEs unchanged;P6integrates only DOSstartup/build
  adapter then refreshes three targets. All five parent gates remain open.
  [Unused-argument cohort](../history/M3-T32-rendering-performance-continuation.md#s4-p5-checkpoint-unused-dos-argument-setup-elimination-candidate).
- T32 S4 P4:declared tail0..126grammar353536states/1726725transitions,
  persistent argv=(P+D+A+4*(A+1))&FFFE <=(P+388)&FFFE. P<=260would give648,
  but DOSpathname limit is NOT proved by app's later path[260]. Final369KiB
  empty/many/one routes pass,observed22/400/152bytes/current49150top andvalid
  saves. Conditional own+CRT+entry+args+IRQ1462 still EXCLUDES global premises.
  Parent gates/source/products unchanged;P5follows domain/lifetime premises.
  [Declared argv domain/current routes](../history/M3-T32-rendering-performance-continuation.md#s4-p4-checkpoint-parameterized-argv-bound-and-current-dos-tail-routes).
- T32 S4 P3:under explicit unchanged-null-hook/default-exit conditions,
  8/9prior unresolved CRTentries have normal/terminal conventions;65reachable/
  64local flows. Defaultfatal06D1terminates;setenvp saved-BP restored. This is
  CONDITIONAL,not global hook lifetime proof. Setargv144E/15F1persistently
  subtracts runtime DXandjumps saved far PC;domain/peak bound still open.
  All five gates/source/products/resolution remain unchanged;P4targets lifetime,
  early-exit andargv obligations. [Conditional contracts](../history/M3-T32-rendering-performance-continuation.md#s4-p3-checkpoint-fatal-nonreturn-and-saved-bp-contracts).
- T32 S4 P2:byte-equal current /MAPrelink;7896CRTbytes/78aliases/74anchors
  rebound.54current binary-FILEflows/28CRTcontributions complete,conditional
  source+CRTmain720unchanged,plusentry/top736 EXCLUDES argv/startup/exit/BIOS/
  IRQ/kernel. Current relocated globals andXPflushall rechecked;loaded defaults
  do not prove lifetime. Startup/text/exit57entries has9named pending entries.
  Five parent gates remain open,products unchanged;P3follows only those joins.
  [Current CRT/exit checkpoint](../history/M3-T32-rendering-performance-continuation.md#s4-p2-checkpoint-current-crt-binary-joins-and-exit-data-relocation).
- T32 S4 P1:current diagnostic graphics648.2154/text453.2544ms(-9.0324/
  -44.4201%vsT31 S6),154records0drops;configured cadence FAILS. GraphicsPPU
  393.2317ms,mapping197.5818ms;text assembly366.3590ms. No settings/frame loss.
- Final160units:156all execution records unchanged,four known changed owners.
 31current CFGs balanced,851functions retained;own-only main690/IRQ78unchanged.
 Current SP49150/top49152/main residence14,own+startup706 EXCLUDES CRT/argv/
 firmware/kernel. All MEM-S4-01..05OPEN;strict Windowsstartup failure retained.
 Source/three S3products unchanged;P2follows current CRT/data andnamed joins.
  [Final cost/binding gate table](../history/M3-T32-rendering-performance-continuation.md#s4-finite-gate-status-after-p1).
- T32 S3adopted:shared color+13/-18,IOcontract+32,verifier+32/-3;15tests
  per width pass andoriginalDOS256-input proof retained. DOS301145(-464),
  DGROUP49152(+80),2048stack;logical325264/341632. Actual369/370full routes
  pass,368clean init refusal.370sampled378432(-288),primary-544/auxiliary+256;
  369sampled377856. Scoped text diagnostic32.5%saving,not actual FPS.
- Strict Windowsstartup fails old/new under current480x839work area/RDP context.
  Correct geometry448x420atDPI144;after10.23/10.21seconds,both new products
  passTab/input/exit withnative31x30viewport. Late readiness is not repaired
  startup;MEM-S4-05/WIN-T19-STARTUP records suspended T19dependency. S3closed
  by explicit integration handoff;T32/goal not verified complete.
  [S3 acceptance/handoff](../history/M3-T32-rendering-performance-continuation.md#s3-p2-color-acceptance-and-s4-integration-handoff).
- T32 S3 P1:lookup-only selected,all256inputs/four color functions exact on
  x86/x64 andoriginalDOS16. Whole seeded text step32.4856%shorter,diagnostic
  owned-544;80constant bytes need actual DGROUP/loader check. Both plane staging
  variants match16972800native band bytes/977235DOSoutput bytes but regress,
  rejected. Product source/three S2EXEs unchanged. No actual FPS/peak proof.
  [Cohort dispositions](../history/M3-T32-rendering-performance-continuation.md#s3-p1-checkpoint-exact-color-lookup-and-rejected-plane-staging).
- T32 S2 adopted:+20/-17shared PPUlines,512current independent cases each
  native width/14tests andactual Windowsstartup/Tab/exit pass. DOS301609(+48),
  native311310/324110bytes;DGROUP49072/2048stackunchanged,rowlocals+8. Logical
  loader325728/342176,page-rounded326192/342640. Actual370route passes,sampled
  378720(+48),369clean init refusal. Seeded populated5.6-8.9%saving is not
  actual product FPS. S3active,S4five memory/cadence clauses remain open.
  [S2 product closure](../history/M3-T32-rendering-performance-continuation.md#s2-p2-closure-source-bound-background-spanindex-integration).
- T32 S2 P1cohort:four exact-output candidates,combined selected for product
  evaluation;whole diagnostic phase0/graphics-return7.1629/6.7507%shorter,
  populated water/castle/dense8.8732/5.6143/8.8061%.512native cases each width;
  each DOSordinary/populated/far/raw receipt977235bytes exact.8row-local bytes
  extra,no heap/workspace;row-copy rejected for weak benefit and stack growth.
  Source and three S1products unchanged;not actual gameplay FPS or acceptance.
  [Cohort evidence/limits](../history/M3-T32-rendering-performance-continuation.md#s2-p1-checkpoint-pointer-and-fixed-index-background-cohort).
- T32 S1 closed:shared text row math+19/-9,396current background comparisons
  and14tests per native width pass; actual Windowsstartup/Tab/exit pass. DOS
  product301561(-144),native311310/324110bytes;DGROUP49072/stack2048unchanged.
  Loader bounds325680/342128bytes;actual370route passes,sampled378672(-144),
  369clean init refusal retained. No universal/continuous peak or FPS certificate.
  Diagnostic text16.6194%shorter applies to source-identical seeded route only.
  [S1 source-bound closure](../history/M3-T32-rendering-performance-continuation.md#s1-p2-closure-bounded-authored-object-row-math).
- T31 closed by owner-directed transfer, not verification success. T32 S4 is
  active and executes the five MEM-S4 gates and named host dependency. Actual DOS cadence,
  global stack and continuous/kernel memory remain unproved.
- Historical T31 S6 P2 products: DOS301705, x86311310, x64324110bytes.
  Private original-ABI PPU scratch+10/-3, DOS-176bytes; no heap/DGROUP/stack
  increase. DGROUP49072, stack2048, page-rounded loader326192/342640bytes.
  Actual370KiB full route passes,369cleanly refuses initialization; observed
  peak378816bytes is not a global maximum or universal minimum.
- T31 final text prototype:816.46ms diagnostic step, object/flood549.85ms;
  selected row math16.6194%shorter whole text,diagnostic owned-144bytes.
  Native396cases per width and DOS977235+72030bytes exact; adopted by S1
  under the scoped closure above. Larger recognition caches rejected for weak benefit/memory growth.
- Graphics diagnostic712.58ms:PPU457.53ms(64.21%),mapping197.58ms(27.73%).
  Configured playability fails; unchanged DOSBox/settings/original tools.
  Physical25MHz486SX qualification remains M4.
- Current exclusive DOS presentation store15400bytes and optional CHR8192cache;
  identical indexed256x240 is stretched borderlessly to640x400. No game logic
  belongs in platform. Retained source-bound proofs apply within their limits.
- Historical1992/1992; local1991/1992nodes and4260/4261feasible controls
  (raw4342,infeasible81),new0. CheckForEnemyGroup/control-01480 remains outside
  M3. Full M2 certificate is incomplete; these counters are local dispositions.
- [Fixed M2 ledger](M2_AUDIT_LEDGER.md):10691sites/4171accesses;6/136groups,
  42/952facets closed,130groups/910facets pending;four final packages pending.
  Deferred certificate queue tail remains unchanged.

## Compact closure status

- [T31 closure/transfer](../history/M3-T31-dos-performance-memory-continuation.md#s6-p3-and-t31-owner-directed-closure): adopted palette, plane, FILE, text clear and near scratch retained; selected text row prototype and five memory/cadence clauses received by T32.
- [T30 closure](../history/M3-T30-ppu-background-performance.md#s2-p1-and-t30-owner-directed-closure): blank-span gain retained; unfinished work transferred, no playability acceptance.
- [T29 Win32 usability](../history/M3-T29-win32-usability-regression.md#s4-p1-corrective-implementation-checkpoint): native viewport/RGB/clipping and asynchronous owned-console acquisition retained; live Restore/visual and parallel fixture debt remains in TODO.
- [T28 memory/output](../history/M3-T28-dos-rendering-optimization.md#s6-p24-owner-directed-closure-and-remaining-work-transfer): memory/loader/output gains retained, unresolved speed/peak proof transferred.
- [T27 component boundaries](../history/M3-T27-core-ppu-module-boundaries.md#s8-p1-closure---integrated-completion-audit): mechanical ownership split and scoped three-platform proof retained.
