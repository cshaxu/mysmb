# Project Status

## Current Work

## M2 T55 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T55 S1 — Cohort C renderer and attribute-output current-equivalence audit. |
| Admission And Approval | T54 S7 is closed with zero scoped feasible differences; owner-directed source-order continuation. |
| Objective | Audit `RenderAreaGraphics` through `SetVRAMCtrl`, repair every feasible shared-C difference, and repeat the scoped ROM/native and graph audit to zero. |
| Non-goals | No historical-node credit, no palette-rotation implementation, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 166 exact, 1,826 needs-evidence nodes; 347 exact, 3,977 needs-evidence feasible controls. Scope: 11 labels, all incoming `needs-evidence`; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`, focused recorder/tests and current-equivalence registry only; platforms remain presentation/input adapters. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: controlled original-ROM/x86/x64 renderer route plus node/edge and material-handoff audit. Operational: focused checks, x86/x64 and DOS16 builds if source changes, platform-purity audit, and three artifacts if product code changes. |
| Expected Markers | All 11 labels and their incident feasible relations have a current shared-C counterpart with source-order, predicate, state/output and return evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces below build/m2-t55-s1; artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, edge/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, a source relation lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S closes only when every scoped feasible node, control relation and material handoff is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Renderer row direction, attribute boundaries, control-six ownership, caller/return handoff and all four AreaParserTasks renderer selectors. |

## Current Technical Baseline

M2 T55 S1 is active after the closed T54 S7 dispatcher audit. It begins Cohort C with renderer and attribute output.

## S5 Closure

`ResetSpritesAndScreenTimer`, `ResetScreenTimer` and `NoReset` are current-exact.
The source audit against SMB1 lines 1804–1813 found no shared-C difference:
task cases five and seven both preserve the nonzero early return and the
zero-timer `MoveAllSpritesOffscreen`, timer-seven reload, task-increment order.
The controlled task-five/task-seven zero/nonzero matrix agrees across original
ROM, x86 and x64 for `ScreenRoutineTask`, `ScreenTimer` and every OAM byte.
The focused screen-status smoke and platform-purity audit pass. The registry
advances from 159 to 162 exact nodes and from 319 to 324 exact feasible
controls; historical conformance remains 1,992 / 1,992. The only code change
is a focused test assertion, so product artifacts were not refreshed.

## S6 Closure

`AreaParserTaskControl`, `TaskLoop` and `OutputCol` are current-exact. The
normal Start route executes 12 parser column sets in ROM, x86 and x64: task 8
remains active through the non-final sets, each selects control 6, and the
final decrement underflows to 255 before advancing to task 9. The five
tracked state bytes agree for samples 6–18. The registry advances from 162 to
165 exact nodes and from 324 to 330 exact feasible controls; historical
conformance remains 1,992 / 1,992. No product code changed.

## S7 Closure

`ScreenRoutines` and its 17 source-owned task-vector relations are
current-exact. The repeat static audit corrects its ROM entry to `$8567` and
removes the former synthetic out-of-domain `OperMode_Task=2` recovery write.
The controlled selector 0–14 original-ROM/x86/x64 matrix is exact, including
`ColumnSets` and `AreaParserTaskNum` for task eight. Focused x86/x64 smoke and
platform-purity checks pass; the shared OpenNT DOS16 build links. Three product
artifacts were refreshed. The registry advances to 166 exact nodes and 347
exact feasible controls; historical conformance remains 1,992 / 1,992.
No successor S is admitted.

One shared native C90 game implementation serves DOS16 and Win32 x86/x64;
platform adapters do not own game logic.
