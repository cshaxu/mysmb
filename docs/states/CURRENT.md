# Project Status

## Current Work

## M2 T53 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T53 S4 — Cohort A victory-chain current-equivalence audit. |
| Admission And Approval | S3 closed with zero scoped mismatches; owner-directed continuation under the approved T53 source-order program. |
| Objective | Audit `VictoryMode` through `EndExitTwo` against the original ROM control/state/output contract; repair any feasible difference and repeat the audit until zero remains. |
| Non-goals | No historical-node credit, no floatey successor admission, no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 76 exact, 1,916 needs-evidence, 0 mismatch nodes; 146 exact, 4,178 needs-evidence, 0 mismatch feasible controls. Scope: 22 labels, expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t53-cohort-a-current-proof.md. |
| Files And ABI Surface | Shared `src/game/terminal_modes.c` and `src/game/frame_root.c`, focused tests, and registry/ledger evidence; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source-control/data/edge audit and controlled owner-local victory routes against current x86/x64. Operational: focused endgame checks, x86/x64 and DOS16 builds only if source changes, and platform-purity audit. |
| Expected Markers | Every scoped node and feasible control relation has a current C counterpart with source-order, state/table and output evidence; no scoped difference remains. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t53-s4; three local artifacts are refreshed only if product code changes. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an original branch lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when every scoped feasible node and relation is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | All `VictoryMode` task selectors, message counters, automatic player/scroll transitions and end-world B-button exit branches. |

## Current Technical Baseline

M2 T53 S3 repaired the `ScreenOff` NMI transaction order and closed at zero scoped mismatches. M2 T53 S4 is the sole active source-order audit. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
