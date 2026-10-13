# Project Status

## M3 T44 S12 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: T44 S6 design accepted; S12 P1 closed after implementation and separate reviewer pass. |
| Admission And Approval | Owner authorizes automatic progression through T44 closure, using one executor with separate implementation and reviewer passes. S12 closed; S13 is next. |
| Objective | Implement G09-G10: reusable PCM/file mechanisms and independent model-qualified library builds. |
| Non-goals | No Mine import, game/PPU logic change, new ROM certification, or changed Mario tick/audio ordering. |
| Reference Baseline | c663c306 and retained T44 receipts; sibling Mine source-only comparison. |
| Candidate Proposal | [Corrective audit and roadmap](../proposals/m3/t44-library-readiness-correction.md). |
| Files And ABI Surface | src/lib devices, Mario service adapters, mirrored tests and build tools; estimate15-30files/600-1500lines. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Owner-local tests, both native suites and Console joins, DOS/Win16 build checks, three products; node/ledger/governance gates. |
| Expected Markers | Twelve tracked gaps with receiving S and acceptance; empty node scope and expected matches; historical1992/1992 unchanged. |
| Asset Needs | Read-only sibling Mine, redistribution unreviewed, no import. Existing owner-local SMB1 ROM and previously qualified DOS/Win16 tools only for local builds; no ROM-derived output committed. Active logs below build/t44-s12 and native build trees. |
| Reporting Requirements | Explain retained/moved/missing capabilities and planned S sizes/exits; zero new node/edge credit. |
| Stop Conditions | No unapproved source import, game/PPU semantic change or readiness claim based only on static review. |
| Exit Criteria | G09-G10 no-game PCM/file and no-ROM library build pass; small/large DOS model runtime joins and all products pass. |
| Original Owner Request | Reopen T; audit gaps, support Console/window mouse, return game refresh policy to app-mario, provide new S roadmap. |
| Similar-Issue Sweep | Four lib families plus app adapters: geometry/palette, input/capture, scheduling, device services, memory-model/build/test isolation. |

## Current Technical Baseline

S6-S12 are closed; G01-G10 have scoped implementation and runtime receipts in
the proposal. G11-G12 remain planned receiving work.
Latest products are S12; closure receipts are in the proposal. No Mine import and no core/PPU
semantic changes. Historical1992/1992, retained1991/1992 nodes and4260/4261
feasible controls (4342raw,81infeasible) unchanged; no final certificate claim.
Preserve17 unrelated resource deletions. Build artifacts stay ignored.
