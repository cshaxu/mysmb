# Project Status

## Current Work

## M2 T54 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T54 S6 — Cohort B parser-task handoff current-equivalence audit. |
| Admission And Approval | S5 is closed with zero feasible differences; owner-directed source-order continuation. |
| Objective | Audit `AreaParserTaskControl` through `OutputCol` against original ROM parser-task loop, conditional task advance and VRAM selector output; repair every feasible difference and repeat the same audit to zero. |
| Non-goals | No historical-node credit, no ScreenRoutines dispatcher proof, no parser-handler internal proof, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 162 exact, 1,830 needs-evidence, 0 mismatch nodes; 324 exact, 4,000 needs-evidence, 0 mismatch feasible controls; 10 exact material relations. Scope: 3 labels, all incoming needs-evidence; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t54-cohort-b-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c` parser-task handoff, focused tests, registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source/branch/state/call-order audit and controlled original-ROM/x86/x64 parser task-count variants. Operational: focused checks, x86/x64 and DOS16 builds if source changes, platform-purity audit, and three artifacts if product code changes. |
| Expected Markers | Every scoped node and source-owned feasible relation has a current C counterpart with source-order, branch/state and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t54-s6; artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch/callee handoff lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Parser task-count zero/nonzero, handler loop count, screen-disable ordering, task advance and VRAM selector output. |

## Current Technical Baseline

M2 T54 S6 is closed. No successor S is admitted until the coordinator opens it.

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
One shared native C90 game implementation serves DOS16 and Win32 x86/x64;
platform adapters do not own game logic.
