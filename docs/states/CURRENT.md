# Project Status

## Current Work

## M2 T53 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T53 S2 ? Cohort A title/menu/world-select/icon/demo current-equivalence audit. |
| Admission And Approval | Owner-directed continuation under the approved source-order T53?T70 proof program. |
| Objective | Audit the 26-label title/menu/world-select/icon/demo chain and its 45 internal control relations against the original ROM. |
| Non-goals | No historical-node credit, no cross-cohort final proof, and no platform-owned game decision. Any mismatch becomes a later candidate rather than an unscoped repair. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 70 exact, 1 mismatch, 1,921 needs-evidence; 4,326 feasible control relations. S2 scope: 26 labels, 21 exact and 5 needs-evidence; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t53-cohort-a-current-proof.md. |
| Files And ABI Surface | Shared `src/game/title_modes.c`, `src/game/frame_root.c`, title data consumers and tests/registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: static node/edge audit plus controlled owner-local title routes. Operational: title/demo and core focused tests, x86/x64 records, OpenNT DOS16 link, platform-purity and three ignored local artifacts for any implementation P. |
| Expected Markers | Every scoped label and internal relation has a recorded current disposition; menu input, world select, icon copy, demo timing/action and demo reset evidence are separated. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t53-s2; local artifacts refresh only for a completed implementation P. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | An original branch lacks a shared-C counterpart, a route mismatch appears, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only with an individual disposition for all 26 labels and its 45 internal relations, reproducible route evidence and both verification tracks. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | All title menu, world-select, icon-copy and demo timing/action/reset call/return relations in lines 982?1136. |

## Current Technical Baseline

M2 T53 S1 is closed: 38 current-exact nodes, one `ScreenOff` mismatch, 74 exact internal control relations and one infeasible extractor relation. M2 T53 S2 is the sole active packet. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
