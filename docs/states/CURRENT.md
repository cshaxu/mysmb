# Project Status

**Active: M3 T33 S2, corrective reopening.**

## M3 T33 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Corrective; latest closed T33 reopened, S1 closure retained, S2 active. |
| Admission And Approval | Owner explicitly requests reopening T33 at S2 and redesigned 80x25 text; retain intact 80x50 alongside the new default 80x25 profile, with no selection switch yet. |
| Objective | Establish a bounded shared default-80x25 design with retained 80x50 compatibility, complete template/consumer census, migration cohorts and visual acceptance; retain console-subsystem regression findings. |
| Non-goals | No product-code change in this design P; no game/PPU changes, bitmap sampling, helper process, global Terminal settings or claim that 25 rows alone fixes console allocation/Tab latency. |
| Reference Baseline | Current source at 358beff9; owner accepts diagnostic 05 on both widths and rejects 06 physical 80x50 display. API readback is not physical acceptance. |
| Candidate Proposal | [T33 retained proposal, S2 amendment](../history/M3-T33-windows-console-fit-proposal.md#s2-corrective-reopening-and-80x25-design). |
| Files And ABI Surface | Planning records and node/task ledger only in this P. Future shared io/video and text element/actor/background/caption owners, both device adapters and focused tests are inventoried, not yet modified. |
| Applicable Rules | Execution, Architecture, Coding, Documentation and source policy; System Architecture and Source Layout. All temporary census/probe outputs remain under ignored build. |
| Verification | Current-source template census, fixed-dimension consumer search, caption collision and storage analysis; node admission and documentation gates. Future adoption needs shared text fidelity, graphics/state invariance, three products and actual-host visual/input/Restore proof. |
| Expected Markers | Empty ROM scope/expected matches; historical 1992/1992, local 1991/1992 nodes and 4260/4261 feasible controls remain unchanged. |
| Asset Needs | Existing project-authored templates only; no ROM/disassembly/resource import or product refresh for design-only P. |
| Reporting Requirements | Report planned components/size, inventory totals, proposed layout and all pending implementation/physical-host clauses; distinguish cell geometry from physical display. |
| Stop Conditions | Any proposed game-state mutation, original selector re-execution, information loss, unsupported host guarantee or unbounded state inventory requires visible redesign. |
| Exit Criteria | Complete reproducible current-source census, all affected owners and text-preservation risks named, bounded implementation plan and acceptance matrix recorded. S2 remains active until its admitted design review is resolved; this P does not close T33. |
| Original Owner Request | Reopen T33 as S2; assess 80x25 and redraw elements; preserve 80x50 code, add default 80x25, allow a selection switch later. |
| Similar-Issue Sweep | Scan shared layout constants, literal projection/row limits, template heights, occupancy masks, captions, DOS BIOS font/rows, Windows font/viewport/output and snapshot consumers; account for each owner. |

Queue head remains the unadmitted native VGA/performance package. T32/S9
remain suspended; the existing complete object/state gallery candidate is
retained and must be reconciled with any approved 80x25 implementation scope.

## Current Technical Baseline

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
- Published products:DOS307349B,x86318478B,x64331790B. DOS DGROUP49264,
  stack2048,loader331584..335680logical bytes unchanged. Global stack/memory
  proof and physical25MHz486SX playability remain unqualified.
- T32/S9suspended. S8P21counter137.665ms,PPU59.677/mapping44.716/VGA18.062ms
  are diagnostic costs,not hardware FPS/fair reference proof. Remaining native
  VGA/performance/acceptance work is the queued
  [performance package](../proposals/m3/native-vga-performance-package.md).
  Its original-tool pattern probe retains61440exact pixels/512x480hardware
  replication;no game-mode adoption yet.
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
