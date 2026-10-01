# Project Status

## Current Work

## M2 T53 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T53 S5 — Cohort A floatey-number current-equivalence audit. |
| Admission And Approval | S4 closed with zero scoped mismatches; owner-directed continuation under the approved T53 source-order program. |
| Objective | Audit `FloateyNumTileData` through `SetupNumSpr` against the original ROM control/state/table/OAM contract; repair any feasible difference and repeat the audit until zero remains. |
| Non-goals | No historical-node credit, no successor admission, no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry after the S5 repair/re-audit: 105 exact, 1,887 needs-evidence, 0 mismatch nodes; 231 exact, 4,093 needs-evidence, 0 mismatch feasible controls; 6 exact material relations. Scope: 10 labels, expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t53-cohort-a-current-proof.md. |
| Files And ABI Surface | Shared `src/game/objects.c`, score/OAM collaborators, focused tests, and registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source-control/table/OAM audit and controlled owner-local floatey routes against current x86/x64. Operational: focused checks, x86/x64 and DOS16 builds only if source changes, and platform-purity audit. |
| Expected Markers | Every scoped node and feasible control/material relation has a current C counterpart with source-order, state/table and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t53-s5; three local artifacts are refreshed only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Every floatey score-table consumer, timer-zero/decrement branch, tall-enemy offset path and multi-sprite OAM tail. |

## Current Technical Baseline

M2 T53 S5 has repaired and re-audited its sole feasible mismatch: `ChkTallEnemy -> GetAltOffset` now selects the ROM OAM group for Spiny, Hammer Bro and IDs at or above `TallEnemy`. All ten scoped labels, 25 scoped controls and the floatey tile material relation are exact under static and controlled ROM/native evidence. This closure record remains the active packet until its ledger/documentation gates pass; no successor is admitted yet. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
