# Project Status

## Current Work

## M2 T56 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T56 S2 — scenery, terrain and block-buffer current-equivalence audit. |
| Admission And Approval | T56 S1 is closed; the owner-approved source-order program admits T56 S2. |
| Objective | Audit `RenderSceneryTerrain` through `BlockBuffLowBounds`, repair every feasible shared-C mismatch, and repeat ROM/native evidence until every scoped node and relation is exact. |
| Non-goals | No historical-node credit, no platform rendering/input decisions, and no expansion into S3's AreaData decoder. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 247 exact and 1,745 needs-evidence nodes; 490 exact feasible controls. Scope: 20 labels; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`; focused parser recorder/tests only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: scenery/terrain table and loop semantics, AreaData-to-block-buffer order and collision bounds. Operational: controlled original-ROM/x86/x64 parser route, focused parser tests, DOS16 build if product source changes, and platform-purity audit. |
| Expected Markers | 13-row clear, background/foreground overlays, terrain-bit iteration, pre-commit `ProcessAreaData`, and physical block-buffer write remain in shared C. |
| Asset Needs | Refresh all three artifacts only if product source changes. |
| Reporting Requirements | Report all 20 labels and every scoped feasible relation with separate static and operational results; repair and re-audit before S3. |
| Stop Conditions | A feasible ROM/C difference remains after repair, a relation lacks a shared-C counterpart, or platform code makes a scenery/terrain decision. |
| Exit Criteria | Every scoped node and feasible relation is exact under source and controlled-route evidence; no successor is admitted while a mismatch remains. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Clear-loop bounds, scenery table offsets, foreground zero retention, cloud masks, terrain bit ordering, source call order and block-buffer bounds. |

## T56 S1 Closure

S1 closed 14 current-exact parser-task and scenery-table nodes, 19 newly exact feasible control relations and seven material relations. The controlled original-ROM/current x86/x64 route is exact on its 32 scoped persistent parser RAM bytes over eight frames; x86/x64 recorder output is byte-identical. It found no feasible shared-C difference. Historical conformance remains 1,992 / 1,992.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T56 S2 is active for the contiguous scenery, terrain and block-buffer handoff chain.
