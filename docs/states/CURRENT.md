# Project Status

## Current Work

## M2 T54 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T54 S3 — Cohort B title-screen task current-equivalence audit. |
| Admission And Approval | S2 is closed with zero feasible differences; owner-directed source-order continuation. |
| Objective | Audit `DrawTitleScreen` through `IncModeTask_B` against original ROM title task 12/13/14 control flow, data-copy bounds, icon/buffer handoffs, score output and mode-task continuation; repair every feasible difference and repeat the same audit to zero. |
| Non-goals | No historical-node credit, no `ScreenRoutines` dispatcher proof, no title text-stream internals, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 128 exact, 1,864 needs-evidence, 0 mismatch nodes; 277 exact, 4,047 needs-evidence, 0 mismatch feasible controls; 10 exact material relations. Scope: 8 labels, all incoming needs-evidence; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t54-cohort-b-current-proof.md. |
| Files And ABI Surface | Shared `src/game/game.c` title task branches and shared title/OAM/status callees, focused tests, registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source/branch/state/copy-order audit and controlled owner-local title task 12/13/14 routes against current x86/x64. Operational: focused checks, x86/x64 and DOS16 builds if source changes, platform-purity audit, and three artifacts if product code changes. |
| Expected Markers | Every scoped node and source-owned feasible relation has a current C counterpart with source-order, branch/state and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t54-s3; artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch/callee handoff lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Every task-12/13/14 title/non-title branch, title data-copy bound, buffer/icon handoff, score queue result and mode-task continuation. |

## Current Technical Baseline

M2 T53 is closed: its 97 labels, 183 feasible relations and six material relations are current-exact. M2 T54 S1 closed with 20 labels, 25 internal control relations and four material relations current-exact. M2 T54 S2 closed with nine labels and 25 source-owned control relations current-exact after repairing `GameOverInter` mode-task increment semantics. The current registry has 128 exact nodes, 1,864 nodes needing evidence, 277 exact feasible control relations, 4,047 needing evidence, 10 exact material relations and zero mismatches. Historical conformance remains 1,992 / 1,992. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
