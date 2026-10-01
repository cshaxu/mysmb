# Project Status

## Current Work

## M2 T54 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T54 S4 — Cohort B GameText current-equivalence audit. |
| Admission And Approval | S3 is closed with zero feasible differences; owner-directed source-order continuation. |
| Objective | Audit `GameText` through `WarpNumLoop` against original ROM text selection, stream copy, player-name replacement, Warp-number patching and post-copy dispatch; repair every feasible difference and repeat the same audit to zero. |
| Non-goals | No historical-node credit, no `ScreenRoutines` dispatcher proof, no title task re-audit, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 136 exact, 1,856 needs-evidence, 0 mismatch nodes; 293 exact, 4,031 needs-evidence, 0 mismatch feasible controls; 10 exact material relations. Scope: 23 labels, all incoming needs-evidence; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t54-cohort-b-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c` GameText chain and shared status/text callees, focused tests, registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source/branch/state/table/copy-order audit and controlled owner-local text-selector routes against current x86/x64. Operational: focused checks, x86/x64 and DOS16 builds if source changes, platform-purity audit, and three artifacts if product code changes. |
| Expected Markers | Every scoped node and source-owned feasible relation has a current C counterpart with source-order, branch/state and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t54-s4; artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch/callee handoff lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Every GameText selector, player count/name branch, stream terminator/copy boundary, Warp-number patch and post-copy output handoff. |

## Current Technical Baseline

M2 T54 S3 is closed: its eight title-screen task labels and sixteen source-owned control relations are current-exact after repairing live `OperMode_Task` continuation and unconditional title-score output. The current registry has 136 exact nodes, 1,856 nodes needing evidence, 293 exact feasible control relations, 4,031 needing evidence, 10 exact material relations and zero mismatches. Historical conformance remains 1,992 / 1,992. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
