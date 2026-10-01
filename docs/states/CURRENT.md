# Project Status

## Current Work

## M2 T55 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T55 S2 — Cohort C palette-rotation current-equivalence audit. |
| Admission And Approval | T55 S1 closed with zero scoped feasible differences; owner-directed source-order continuation. |
| Objective | Audit `ColorRotatePalette` through `ExitColorRot`, repair every feasible shared-C difference, and repeat the scoped ROM/native and graph audit to zero. |
| Non-goals | No historical-node credit, no block-metatile implementation, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 177 exact, 1,815 needs-evidence nodes; 370 exact, 3,954 needs-evidence feasible controls. Scope: 7 labels, all incoming `needs-evidence`; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`, focused recorder/tests and current-equivalence registry only; platforms remain presentation/input adapters. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: controlled original-ROM/x86/x64 palette route plus node/edge and palette-buffer handoff audit. Operational: focused checks, x86/x64 and DOS16 builds if source changes, platform-purity audit, and three artifacts if product code changes. |
| Expected Markers | All 7 labels and their incident feasible relations have a current shared-C counterpart with source-order, frame/buffer predicates, state/output and return evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces below build/m2-t55-s2; artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, edge/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, a source relation lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | Met: every scoped feasible node, control relation and material handoff is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Frame-eight gate, buffer-full gate, blank-palette copy, area-type selector, rotation wrap and caller/return handoff. |

## Current Technical Baseline

M2 T55 S2 is active after the closed S1 renderer/attribute audit. It continues Cohort C with the contiguous palette-rotation chain.

## S1 Closure

`RenderAreaGraphics`, `DrawMTLoop`, `RightCheck`, `LLeft`, `NextMTRow`,
`SetAttrib`, `ExitDrawM`, `RenderAttributeTables`, `SetATHigh`, `AttribLoop`
and `SetVRAMCtrl` are current-exact. The controlled original-ROM/x86/x64
left/right renderer and attribute matrix has zero scoped byte differences.
The four parser renderer selectors, final attribute call and return were
checked against the source dispatch and shared `area.c` owner. Focused x86/x64
area-output tests pass. No product code changed; product artifacts remain the
previous S7 release. The registry advances to 177 exact nodes and 370 exact
feasible controls; historical conformance remains 1,992 / 1,992.

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
