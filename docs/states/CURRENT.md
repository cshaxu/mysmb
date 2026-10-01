# Project Status

## Current Work

## M2 T56 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T56 S3 - area-data decoder and attribute current-equivalence audit. |
| Admission And Approval | T56 S2 is closed; the owner-approved source-order program admits T56 S3. |
| Objective | Audit `ProcessAreaData` through `SetFore`, repair every feasible shared-C mismatch, and repeat ROM/native evidence until every scoped node and relation is exact. |
| Non-goals | No historical-node credit, no platform rendering/input decisions, and no expansion into S4 object-family handlers. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 267 exact and 1,725 needs-evidence nodes; 535 exact feasible controls. Scope: 32 labels; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`; focused parser recorder/tests only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: stream reads, slot state, row decoding, dispatch and attribute writes. Operational: controlled original-ROM/x86/x64 object-stream route, focused parser tests, DOS16 build if product source changes, and platform-purity audit. |
| Expected Markers | Stream offset, three parser slots, behind/rear state, area type/scenery/terrain attributes and dispatch handoffs remain in shared C. |
| Asset Needs | Refresh all three artifacts only if product source changes. |
| Reporting Requirements | Report all 32 labels and every scoped feasible relation with separate static and operational results; repair and re-audit before S4. |
| Stop Conditions | A feasible ROM/C difference remains after repair, a relation lacks a shared-C counterpart, or platform code makes an area-parser decision. |
| Exit Criteria | Every scoped node and feasible relation is exact under source and controlled-route evidence; no successor is admitted while a mismatch remains. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Stream offset carry, slot reuse, row-13/14 classification, object length, decoder selectors, rear state and area attribute writes. |

## T56 S2 Closure

S2 closed 20 current-exact scenery/terrain/block-buffer nodes, 45 feasible control relations and one material relation. The controlled original-ROM/current x86/x64 route has zero scoped staging/block-buffer differences across eight frames; x86/x64 recorder output is byte-identical. No feasible shared-C difference was found.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T56 S3 is active for the contiguous area-data decoder and attribute chain.
