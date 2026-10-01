# Project Status

## Current Work

## M2 T54 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T54 S2 — Cohort B status and intermediate current-equivalence audit. |
| Admission And Approval | T54 S1 closed at zero feasible differences; owner-directed continuation under the approved source-order proof program. |
| Objective | Audit `WriteTopStatusLine` through `NoInter` against original ROM screen-task branches, text/score output handoffs, timer/latch writes and mode-task continuation; repair any feasible difference and repeat until zero remains. |
| Non-goals | No historical-node credit, no unproven `ScreenRoutines` dispatcher promotion, no platform-owned game decision, and no title task 12+ evidence. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 122 exact, 1,870 needs-evidence, 0 mismatch nodes; 253 exact, 4,071 needs-evidence, 0 mismatch feasible controls; 10 exact material relations. Scope: 9 labels, 3 incoming exact and 6 needs-evidence; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t54-cohort-b-current-proof.md. |
| Files And ABI Surface | Shared `src/game/game.c` screen-task branches and `src/game/area.c` text/status collaborators, focused tests, and registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source/branch/state/call-order audit and controlled owner-local task 2/3/4/6 routes against current x86/x64. Operational: focused checks, x86/x64 and DOS16 builds only if source changes, and platform-purity audit. |
| Expected Markers | Every scoped node and feasible control/material relation has a current C counterpart with source-order, branch/state and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t54-s1; three local artifacts refresh only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch/callee handoff lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Every S2 screen-task branch, text/score queue result, timer/latch write and task/mode continuation in the S2 range. |

## Current Technical Baseline

M2 T53 is closed: its 97 labels, 183 feasible relations and six material relations are current-exact; two raw extractor relations are proven infeasible. M2 T54 S1 closed with 20 labels, 25 internal control relations and four material relations current-exact. M2 T54 S2 is the sole active source-order audit. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
