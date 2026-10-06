# Project Status

## M3 T31 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: M3 T31 S2 P1; neutral plane loop. |
| Admission And Approval | Owner-approved T31 plan; S1 closed and coordinator admits S2. |
| Objective | Reduce tiny far copies and pointer/index work in exact four-plane conversion. |
| Non-goals | No game/PPU semantic changes, framebuffer, row/frame skipping, Windows UI or DOSBox settings. |
| Reference Baseline | S1 P2 integrated source/products and independent plane/PPU references. |
| Candidate Proposal | [T31 plan](../history/M3-T31-dos-performance-memory-continuation.md). |
| Files And ABI Surface | src/platform/vga/vga_frame.c,independent tests; estimate60-160lines,bounded scratch reviewed before adoption,no ABI/heap growth. |
| Applicable Rules | README Task Reading Set,EXECUTION,DOCUMENT,ARCHITECTURE,CODING,CONTRIBUTING and source policy. |
| Verification | Independent plane mapping/guards both widths,original DOS ordinary/populated whole outputs,cost/listing/stack/memory;three EXEs for adoption. |
| Expected Markers | scope/expected/actual[],new0,baseline/max1992/1992;local1991/1992nodes,4260/4261controls,no custody change. |
| Asset Needs | Existing owner-local resources/comparators only;local-only source-policy purpose,no new import;all diagnostics below build. |
| Reporting Requirements | S scope/size first;P actual diff,cost/memory,evidence/products,total/local counts;no diagnostic timing as FPS. |
| Stop Conditions | Any plane/source/guard divergence,unbounded memory,semantic change or unjustified cost regression. |
| Exit Criteria | Candidates adopted/rejected with exact output and time/memory proof;adoption has three products and actual routes. |
| Original Owner Request | Continue performance and memory optimization after T30 closure. |
| Similar-Issue Sweep | Plane interleave,index masking,scale/repeated rows,first/last bands,capacity/address bounds,far ABI and cleanup. |

## Current Technical Baseline

- T31 S1 P2closed:shared palette preparation+9/-5,no heap/DGROUP change;
  ordinary diagnostic2.6427%shorter,populated1.7504/2.3721/1.5815%;exact fallback
  and native gates pass. Actual448/374/373KiBroutes pass;sampled386736/382640/381872bytes.
  Three refreshed products305323/310798/324110bytes. No playable-cadence/global peak proof;
  S2 neutral plane conversion is active.
  [S1 closure/S2 scope](../history/M3-T31-dos-performance-memory-continuation.md#s1-p2-closure-integrate-call-local-palette-preparation).

- T30 S1 P3closed:+35/-18shared PPU lines,independent output/fallback/repeat
  gates pass;ordinary diagnostic graphics-return10.5375percent shorter.
  Actual448/374/373KiBroutes pass,sampled386688/382592/381824bytes(+112).
  Historical products305275/311310/323598bytes;no heap increase,stack2048
  retained. Eight tests per width and final-assets Windows routes pass.
  No cadence/global peak certificate. T30 closed by owner-directed transfer; T31 S1 receives unfinished candidates.
  [S1 closure/S2 scope](../history/M3-T30-ppu-background-performance.md#s1-p3-closure-shared-blank-span-integration).

- T29 S4 corrective implementation retained after owner rejects the earlier live
  Tab/Terminal result. Terminal native viewport/RGB/clipping and same-process
  fresh acquisition implemented;classic80x50and shell attach/release retained.
  Both-width actual native80x30entries/Tab/exit,5focused and sequential13host
  groups pass;VT parser checks8600cells per width. Owner-directed T29 closure transfers live Restore/visual and parallel fixture
  observation to TODO;no new live acceptance.
  [S4 scope/evidence/limits](../history/M3-T29-win32-usability-regression.md#s4-p1-corrective-implementation-checkpoint).
- T29 historical products:305163/310798/323598bytes;current S1 products above.
  Win32 code/test/tool/build8files,+311/-44;no game/PPU/DOS logic changes or
  Windows system settings. DPI initial-size repair remains accepted.
- Current DOS graphics/text diagnostic medians879.420/849.317ms; configured
  playability fails. Graphics PPU65.08percent, conversion28.38, direct VGA3.28;
  P24 loaded-route background about91.76percent of PPU. Actual physical486SX
  performance remains unqualified. Original toolchain and DOSBox settings stay.
- P24 offset-only graphics prototype about3.52percent shorter ordinary route,
  about3.07-3.28percent populated routes; output/reference checks pass within
  fixtures. Prototype is not adopted and not a playable-cadence result.
- Current bounded presentation: shared8192-byte optional CHR cache;
  DOS15400-byte exclusive graphics/text store, source band<=2560 and plane
  band5120, full256x240 source stretched borderlessly to640x400. Original ROM
  logic/PPU-visible state retained by scoped receipts.
- Loader max bound3076paragraphs, DGROUP49520/headroom16016 and2048stack.
  P22 observed startup boundary maximum386576 versus original458752bytes;
  stable occupancy unchanged.373KiB caller-free fixture passes,372fails;
  not a universal minimum. CRT/error, continuous peak and all-path stack remain
  pending in the receiving proposal.
- Historical1992/1992; local1991/1992nodes and4260/4261feasible controls
  (raw4342/infeasible81). CheckForEnemyGroup/control-01480 remains outside M3.
  No node credit or custody transfer in T28 closure; full M2 certificate incomplete.
- [Fixed-universe audit ledger](M2_AUDIT_LEDGER.md):10691retained sites/4171accesses,
  6/136groups and42/952facets closed,130groups/910facets pending; material993partial
  is not a denominator. Two findings/all13coverage slots open; final packages2/6
  closed, material/pixels/routes/snapshot pending. Deferred M2 queue tail retained.

## Compact closure status

- [T30 closure](../history/M3-T30-ppu-background-performance.md#s2-p1-and-t30-owner-directed-closure): S1 gain retained; S2 candidates and unstarted plane/integration clauses received by T31. No DOS playability acceptance.

- [T29 Win32 usability](../history/M3-T29-win32-usability-regression.md#s3-p1-integrated-closure):
  Owner closes S4/T29 with retained implementation and explicit TODO transfers.
  Earlier scoped receipts remain historical,no new live acceptance or ROM credit.

- [T28 closure](../history/M3-T28-dos-rendering-optimization.md#s6-p24-owner-directed-closure-and-remaining-work-transfer):
  accepted memory/loader/output improvements retained; graphics work and remaining
  acceptance have explicit queued receivers. S6/T28 closed by owner transfer,
  not successful playability. Products unchanged, ROM new0.
- [T27 component split](../history/M3-T27-core-ppu-module-boundaries.md#s8-p1-closure---integrated-completion-audit):
  mechanical ownership boundaries and scoped three-platform proof retained.
- [T26 performance transfer](../history/M3-T26-dos16-playable-performance.md#s2-p3-owner-directed-closure-and-remaining-work-transfer):
  full640x400 output retained; unresolved speed received by T28 and now named successors.
- [T24 input correction](../history/M3-T24-win32-window-console-integration.md#s4-corrective-closure):
  both widths targeted window/console checks pass; live owner RDP qualification separate.
- [T23 retainer details](../history/M3-T23-princess-text-detail.md): shared authored
  princess/Toad details retained; no ROM certification credit.
- [T22 display handoff](../history/M3-T22-pipe-exit-display-recovery.md#s2-closure-ten-bounded-contract-dispositions):
  named RAM/PPU handoff repair and scoped first-frame proof retained.
