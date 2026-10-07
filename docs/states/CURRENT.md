# Project Status

**Active: M3 T34 S2, performance and memory cohorts.**

## M3 T34 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation; S1 native adoption closed; S2 active under owner instruction to execute T34 through closure. |
| Admission And Approval | Owner reports delivered text successful and explicitly requests T closure and next queue admission; queue-head native VGA/performance package admitted. |
| Objective | Resolve finite six-candidate performance/memory register;prototype shared byte background cache with bounded low-memory fallback,adopt only measured gains with unchanged semantics. |
| Non-goals | No game/PPU decision changes,DOS4GW,new driver,helper process,frameskip,emulator settings changes,text redesign or whole-ROM certification. |
| Reference Baseline | S1 source/delivery bound in proposal; local products DOS323049B,x86330766B,x64346126B. Current DGROUP51472B/stack2048B; hashes and loader bound in proposal. Reprofile current source; retained T32 costs are historical. |
| Candidate Proposal | [Admitted T34 plan and S1 baseline](../history/M3-T34-native-vga-performance-proposal.md#t34-s2-p1-admissionfinite-performance-and-memory-cohorts). |
| Files And ABI Surface | neutral PPU/IO representation and composition roots;scoped packed/byte/canonical/fallback tests and original builds. Estimate150-300product lines;byte background candidate net61440B only if measured gain and allocation fallback qualify. |
| Applicable Rules | Execution,Documentation,Architecture,Coding,source policy;System Architecture and Source Layout. |
| Verification | Exact61440source-to-VRAM pixels/palette/edges,HUD split/scroll/priority,cache/fallback,mode restoration and Tab;actual DOS input/transition routes,Windows regression,original16-bit compiler/link/segment/stack/loader and before/after stage costs;three local products on code change. |
| Expected Markers | ROM scope[],expectedMatches[],actualMatches[],new0;historical1992/1992,local1991/1992nodes,4260/4261feasible controls unchanged(raw4342,infeasible81). |
| Asset Needs | Existing owner-local SMB1 ROM is Nintendo material without redistribution grant;read-only for local embedded builds and bounded runtime probes. Existing NESticle conceptual research is copyright-only:do not copy code/mode tables or import. Generated data,captures,traces/products remain local;neutral evidence only tracked. No fresh third-party research/import in P1 admission. |
| Reporting Requirements | Before every S report objective,components/code and memory estimates;after report actual changes,scoped results,candidate dispositions and total/local node/edge counts. Do not infer hardware cadence/LCD filling from emulator captures. |
| Stop Conditions | Pixel/priority/split loss,core mutation,installed-setting change,new unbounded audit,unmeasured full-frame allocation or unsupported timing requires redesign within the admitted scope. |
| Exit Criteria | Source-bound native adoption correct and operational with fixed verification and three products,or measured rejection naming unresolved display requirements. S2 closes when all six candidates have measured selected/rejected/not-applicable disposition and adopted changes pass scoped tests;S3 then admitted. Physical486SX qualification stays M4. |
| Original Owner Request | Close successful T33 and admit next queued task;retain native-resolution VGA/performance plan. |
| Similar-Issue Sweep | Review all DOS graphics coordinate/row/plane constants,palette invalidation,mode/text switch/reset and output submissions;retained50/new25 text and Win32 presentation must not regress. |

T34 plan:S1 native output;S2 finite performance/memory register after reprofile;
S3 combined acceptance. Only S2 active. T32/S9 remains suspended;T19 audio
and M2 final certification remain queued. T33 broader gallery debt is recorded
explicitly in TODO rather than asserted complete.

## Current Technical Baseline

- T33 S2 P12delivers default80x25on all three products;50-row code/art and
  interfaces remain. Shared semantic compact art/palette/layout owns output;
  hosts only adapt devices. White HUD,question marks and spring white edges
  are retained. Core/PPU code unchanged;ROM credit0.
  [Delivery](../history/M3-T33-windows-console-fit-proposal.md#s2-p12-implementation-and-local-play-test-delivery).
- Each Windows width20checks passes;53legacy cell cases byte-identical,
  1200native frames read-only,owned and interactiveCMD Tab/input/exit pass.
  DOS original build/link/memory and stock-config startup/text/Enter/exit pass.
  Products:16-bit320681B,32-bit330766B,64-bit346126B. Owner accepts S2and closes T33;unreviewed gallery
  and broader host applicability remain explicit TODO clauses.

- T33closed by owner-directed engineering acceptance. P3entry/Restore share
  bounded rollback/retry;actual classic capture and4000glyph checks pass.
  [Closure](../history/M3-T33-windows-console-fit.md#s1-p3-and-t33-owner-directed-engineering-closure).
- T33 S1 P2 restores the T24one-time80x50geometry sequence independently of
  HWND availability,+31/-10Win32device/header lines. Same-host neutral probe
  and actual x86/x64products report80x50;rollback/borrowed restoration and
  each width18tests pass. Fonts still have separate physical acceptance.
  [Correction](../history/M3-T33-windows-console-fit.md#s1-p2-restore-the-actual-t24-geometry-contract).
- T29classified Terminal and skipped working geometry;P1restored font but
  still gated geometry on a real HWND. P2corrects that unsupported inference.
  No per-frame forced Terminal resize. Terminal physical glyph/live caption applicability
  is retained in TODO;no all-host visual certification or next admission.
- Historical S1 products:DOS307349B,x86318478B,x64331790B. DOS DGROUP49264,
  stack2048,loader331584..335680logical bytes at that closure. Global stack/memory
  proof and physical25MHz486SX playability remain unqualified.
- T32/S9suspended. S8P21counter137.665ms,PPU59.677/mapping44.716/VGA18.062ms
  are diagnostic costs,not hardware FPS/fair reference proof. Remaining native
  VGA/performance/acceptance work is the
  [admitted T34 package](../history/M3-T34-native-vga-performance-proposal.md).
  Its original-tool pattern probe retains61440exact pixels/512x480hardware
  replication;S1 now adopts this native path in the actual game.
- Historical1992/1992,local1991/1992nodes and4260/4261feasible controls
  (raw4342,infeasible81),new0. Full M2certificate remains incomplete:
  10691sites/4171accesses,6/136groups and42/952facets accepted;
  130groups/910facets and four final packages pending in
  [audit ledger](M2_AUDIT_LEDGER.md). Do not infer whole-game correctness.

## Compact closure status

- [T32 retained checkpoints](../history/M3-T32-rendering-performance-continuation.md):
  S8transfer closure stands;T32/S9suspended by owner queue packaging.
- [T29 retained host work](../history/M3-T29-win32-usability-regression.md):
  asynchronous acquisition and native RGB retained;T33fit/Restore repair closes.
- T19Windows audio startup remains separately suspended in the queue.
