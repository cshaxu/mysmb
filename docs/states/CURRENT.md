# Project Status

## Current Work

## M2 T54 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T54 S7 — Cohort B ScreenRoutines dispatcher current-equivalence audit. |
| Admission And Approval | S6 is closed with zero feasible differences; owner-directed source-order continuation. |
| Objective | Audit `ScreenRoutines` against the original JumpEngine task-vector dispatch and return integration after independently verified task chains; repair every feasible difference and repeat the audit to zero. |
| Non-goals | No historical-node credit, no re-audit of closed target internals, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 165 exact, 1,827 needs-evidence, 0 mismatch nodes; 330 exact, 3,994 needs-evidence, 0 mismatch feasible controls; 10 exact material relations. Scope: 1 label, incoming needs-evidence; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t54-cohort-b-current-proof.md. |
| Files And ABI Surface | Shared `src/game/game.c` screen-task dispatcher, focused tests, registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: task-vector/control-return audit and controlled original-ROM/x86/x64 screen-task matrix. Operational: focused checks, x86/x64 and DOS16 builds if source changes, platform-purity audit, and three artifacts if product code changes. |
| Expected Markers | Every scoped node and source-owned feasible relation has a current C counterpart with source-order, branch/state and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t54-s7; artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch/callee handoff lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | All task selectors, default handling, task-local successor writes and target return handoff. |

## Current Technical Baseline

M2 T54 S6 is closed. S7 is active and audits the final Cohort-B screen dispatcher.

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
