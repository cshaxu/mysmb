# Project Status

## Current Work

## M2 T54 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T54 S5 — Cohort B reset-screen timer current-equivalence audit. |
| Admission And Approval | S4 is closed with zero feasible differences; owner-directed source-order continuation. |
| Objective | Audit `ResetSpritesAndScreenTimer` through `NoReset` against original ROM timer predicate, sprite clear, timer reload and task increment; repair every feasible difference and repeat the same audit to zero. |
| Non-goals | No historical-node credit, no ScreenRoutines dispatcher proof, no parser handoff proof, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 159 exact, 1,833 needs-evidence, 0 mismatch nodes; 319 exact, 4,005 needs-evidence, 0 mismatch feasible controls; 10 exact material relations. Scope: 3 labels, all incoming needs-evidence; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t54-cohort-b-current-proof.md. |
| Files And ABI Surface | Shared `src/game/game.c` task-five/task-seven reset chain, focused tests, registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source/branch/state/call-order audit and controlled original-ROM/x86/x64 task-five/task-seven timer-zero/nonzero routes. Operational: focused checks, x86/x64 and DOS16 builds if source changes, platform-purity audit, and three artifacts if product code changes. |
| Expected Markers | Every scoped node and source-owned feasible relation has a current C counterpart with source-order, branch/state and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t54-s5; artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch/callee handoff lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Timer zero/nonzero branches for both screen tasks, sprite clear order, timer reload and task increment. |

## Current Technical Baseline

M2 T54 S4 is closed. S5 is active and audits the next source-order reset chain.
One shared native C90 game implementation serves DOS16 and Win32 x86/x64;
platform adapters do not own game logic.
