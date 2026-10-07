# Project Status

**Active: M3 T33 S2, corrective reopening.**

## M3 T33 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Corrective; latest closed T33 reopened, S1 closure retained, S2 active. |
| Admission And Approval | Owner explicitly requests reopening T33 at S2 and redesigned 80x25 text; retain intact 80x50 alongside the new default 80x25 profile, with no selection switch yet. |
| Objective | P12 owner authorizes implementation of default shared80x25 with retained80x50;adopt reviewed color-mass/character art,including spring side highlights,and publish three local EXEs for owner play testing. |
| Non-goals | No game/PPU changes,bitmap sampling,helper process,global Terminal settings,user-facing layout switch or claim that25rows alone fixes allocation/Tab latency. |
| Reference Baseline | Current source at 358beff9; owner accepts diagnostic 05 on both widths and rejects 06 physical 80x50 display. API readback is not physical acceptance. |
| Candidate Proposal | [T33 retained proposal, S2 amendment](../history/M3-T33-windows-console-fit-proposal.md#s2-corrective-reopening-and-80x25-design). |
| Files And ABI Surface | io/video neutral layout/palette metadata;text shared compact artwork,actor/background/caption/scene layout;Win32/DOS text devices and composition roots;CMake/DOS source list;focused tests. Retain50-row interfaces/art. Expected800-1200lines;translated core and original state ABI untouched. |
| Applicable Rules | Execution, Architecture, Coding, Documentation and source policy; System Architecture and Source Layout. All temporary census/probe outputs remain under ignored build. |
| Verification | Legacy50-row regression;compact artwork/color/pose and all caption coverage;read-only state,priority/clipping,snapshot and graphics invariance;x86/x64 focused tests/native Tab/input/exit;originalDOS16 compiler/link/memory checks;three local products. Device probes do not replace owner visible/play acceptance. |
| Expected Markers | Empty ROM scope/expected matches; historical 1992/1992, local 1991/1992 nodes and 4260/4261 feasible controls remain unchanged. |
| Asset Needs | Existing owner-local SMB1 iNES/reviewed disassembly are read-only Nintendo material without a redistribution grant. P2-P11owner-requested local review panels remain under ignored build. P12uses the same admitted revision for embedded local Win32/DOS builds and stock DOSBox diagnostics;generated resource declarations,raw captures and traces remain local/ignored. Only project-authored compact art and neutral records are tracked;protected products are not staged. Header/PRG/CHR bounds and palette/OAM bindings are verified;native fixtures are not original-ROM replay proof. |
| Reporting Requirements | Report planned components/size, inventory totals, proposed layout and all pending implementation/physical-host clauses; distinguish cell geometry from physical display. |
| Stop Conditions | Any proposed game-state mutation, original selector re-execution, information loss, unsupported host guarantee or unbounded state inventory requires visible redesign. |
| Exit Criteria | Default80x25 runs through shared scene logic on all targets,retained50passes regression,scoped tests/builds and three products delivered;report remaining visual/host clauses. T33 stays open pending owner play acceptance. |
| Original Owner Request | Reopen T33 as S2; assess 80x25 and redraw elements; preserve 80x50 code, add default 80x25, allow a selection switch later. |
| Similar-Issue Sweep | Scan shared layout constants, literal projection/row limits, template heights, occupancy masks, captions, DOS BIOS font/rows, Windows font/viewport/output and snapshot consumers; account for each owner. |

Queue head remains the unadmitted native VGA/performance package. T32/S9
remain suspended. The owner withdrew the separate complete object/state gallery
queue candidate and transferred its still-unreviewed coverage to T33's task-level
scope; S2's admitted implementation and owner play acceptance remain distinct
from the later complete-gallery review.

## Current Technical Baseline

- T33 S2 P12delivers default80x25on all three products;50-row code/art and
  interfaces remain. Shared semantic compact art/palette/layout owns output;
  hosts only adapt devices. White HUD,question marks and spring white edges
  are retained. Core/PPU code unchanged;ROM credit0.
  [Delivery](../history/M3-T33-windows-console-fit-proposal.md#s2-p12-implementation-and-local-play-test-delivery).
- Each Windows width20checks passes;53legacy cell cases byte-identical,
  1200native frames read-only,owned and interactiveCMD Tab/input/exit pass.
  DOS original build/link/memory and stock-config startup/text/Enter/exit pass.
  Products:16-bit320681B,32-bit330766B,64-bit346126B. S2and T33remain active
  pending owner play/physical display review and the transferred gallery scope.

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
