# Project Status

## M3 T32 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: M3 T32 S3 P1; neutral color mapping and VGA plane cost. |
| Admission And Approval | Approved T32 plan; S1-S2 closed, S3 sole active; S4 receiving backlog only. |
| Objective | Reduce neutral color classification and indexed-to-plane submission cost with exact colors/planes and useful time/memory tradeoffs. |
| Non-goals | No game/PPU/resource semantics, lost ticks/frames/rows/colors, helper process, DOSBox settings, toolchain change or unsupported stack shrink. |
| Reference Baseline | T32 S2 source-bound three products and retained exact compositor/plane/color contracts. |
| Candidate Proposal | [T32 S3 scope and acceptance](../history/M3-T32-rendering-performance-continuation.md#s3-admission-neutral-color-mapping-and-plane-submission). |
| Files And ABI Surface | src/io/color.c and src/platform/vga/vga_frame.c;estimate40-140candidate lines,possible80/320transient stack trial,no new heap/persistent buffer/public ABI by default. |
| Applicable Rules | README Task Reading Set, EXECUTION, DOCUMENT, ARCHITECTURE, CODING, CONTRIBUTING and source policy. |
| Verification | Exhaustive byte-color/contrast and independent plane/scaling/guards both widths; original DOSbytes/cost/listing, memory/actual routes and three products on adoption. |
| Expected Markers | scope/expected/actual[],new0,baseline/max1992/1992;local1991/1992nodes,4260/4261controls,no custody transfer. |
| Asset Needs | Existing owner-local build/oracle bindings only;new constants derive solely from project-owned neutral palette math,not ROM. Restricted diagnostics remain below build. |
| Reporting Requirements | Candidate disposition, actual source/product/time/memory delta and stack limits plus total/local counters; no diagnostic FPS as acceptance. |
| Stop Conditions | Color/tie/scaling/plane divergence, invalid near/far lifetime, startup/stack regression, source-binding gap or invalid probe. |
| Exit Criteria | Bounded cohort dispositions and useful selected implementation passes exact-output/build/actual-route/memory gates with three products;repair/reject differences within S. |
| Original Owner Request | Continue performance and memory optimization while preserving original ROM/PPU semantics and balancing DOS resident memory with playability. |
| Similar-Issue Sweep | All byte indices/ties/contrast, source/output bounds and disjoint lifetime, plane masks/repeated rows/band boundaries, near/far ABI and existing three-target callers. |

## Current Technical Baseline

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
- T31 closed by owner-directed transfer, not verification success. T32 S3 is
  active; S4 receives all five MEM-S4 gates as backlog only. Actual DOS cadence,
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
