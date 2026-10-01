# Project Status

## Current Work

## M2 T54 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T54 S1 — Cohort B screen-initialization and palette current-equivalence audit. |
| Admission And Approval | T53 closed at zero feasible differences; owner-directed continuation under the approved source-order proof program. |
| Objective | Audit `InitScreen` through `NoAltPal` against the original ROM task, palette, table, VRAM-output and call-order contract; repair any feasible difference and repeat until zero remains. |
| Non-goals | No historical-node credit, no unproven `ScreenRoutines` dispatch promotion, no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 105 exact, 1,887 needs-evidence, 0 mismatch nodes; 231 exact, 4,093 needs-evidence, 0 mismatch feasible controls; 6 exact material relations. Scope: 20 labels, 3 incoming exact and 17 needs-evidence; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t54-cohort-b-current-proof.md. |
| Files And ABI Surface | Shared `src/game/game.c` and `src/game/area.c` palette/output collaborators, focused tests, and registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source/table/state/OAM-VRAM audit and controlled owner-local task 0/1/9/10/11 palette routes against current x86/x64. Operational: focused checks, x86/x64 and DOS16 builds only if source changes, and platform-purity audit. |
| Expected Markers | Every scoped node and feasible control/material relation has a current C counterpart with source-order, table/state and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t54-s1; three local artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Every screen task selector, palette-table consumer, queued palette command and task-byte continuation in the S1 range. |

## Current Technical Baseline

M2 T53 is closed: its 97 labels, 183 feasible relations and six material relations are current-exact; two raw extractor relations are proven infeasible. M2 T54 S1 is the sole active source-order audit. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
