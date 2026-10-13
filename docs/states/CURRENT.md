# Project Status

## M3 T44 S11 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: T44 S6 design accepted; S11 P1 closed after implementation and separate reviewer pass. |
| Admission And Approval | Owner authorizes automatic progression through T44 closure, using one executor with separate implementation and reviewer passes. S11 closed; S12 is next. |
| Objective | Implement G08: Win16 variable graphics, retained window text and physical mouse/menu/cancel events. |
| Non-goals | No Mine import, game/PPU logic change, new ROM certification, or changed Mario tick/audio ordering. |
| Reference Baseline | c663c306 and retained T44 receipts; sibling Mine source-only comparison. |
| Candidate Proposal | [Corrective audit and roadmap](../proposals/m3/t44-library-readiness-correction.md). |
| Files And ABI Surface | src/lib/win16, Mario Win16 adapter, mirrored tests/build lists; estimate12-22files/600-1400lines. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Owner-local tests, both native suites and Console joins, DOS/Win16 build checks, three products; node/ledger/governance gates. |
| Expected Markers | Twelve tracked gaps with receiving S and acceptance; empty node scope and expected matches; historical1992/1992 unchanged. |
| Asset Needs | Read-only sibling Mine, redistribution unreviewed, no import. Existing owner-local SMB1 ROM and previously qualified DOS/Win16 tools only for local builds; no ROM-derived output committed. Active logs below build/t44-s11 and native build trees. |
| Reporting Requirements | Explain retained/moved/missing capabilities and planned S sizes/exits; zero new node/edge credit. |
| Stop Conditions | No unapproved source import, game/PPU semantic change or readiness claim based only on static review. |
| Exit Criteria | G08 neutral client actual Win3.x graphics/text/input/lifecycle joins pass; Mario behavior preserved and three products refreshed. |
| Original Owner Request | Reopen T; audit gaps, support Console/window mouse, return game refresh policy to app-mario, provide new S roadmap. |
| Similar-Issue Sweep | Four lib families plus app adapters: geometry/palette, input/capture, scheduling, device services, memory-model/build/test isolation. |

## Current Technical Baseline

S6-S11 are closed; G01-G08 have scoped implementation and runtime receipts in
the proposal. G09-G12 remain planned receiving work.
Latest products are S11; closure receipts are in the proposal. No Mine import and no core/PPU
semantic changes. Historical1992/1992, retained1991/1992 nodes and4260/4261
feasible controls (4342raw,81infeasible) unchanged; no final certificate claim.
Preserve17 unrelated resource deletions. Build artifacts stay ignored.
