# Project Status

## M3 T44 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: T44 S6 design accepted; S7 P1 closed after implementation/review. |
| Admission And Approval | Owner authorizes automatic progression through T44 closure, using one executor with separate implementation and reviewer passes. S7 closure; S8 is the next sequential admission. |
| Objective | Implement G01-G04: neutral KVM geometry/palette/input/glyph contracts and atomic Mario adaptation. |
| Non-goals | No Mine import, game/PPU logic change, scheduling redesign or new ROM certification. |
| Reference Baseline | c663c306 and retained T44 receipts; sibling Mine source-only comparison. |
| Candidate Proposal | [Corrective audit and roadmap](../proposals/m3/t44-library-readiness-correction.md). |
| Files And ABI Surface | src/lib/kvm, dependent presenters, app-mario/kvm, mirrored tests and source lists; initial estimate20-40 files; actual contract propagation currently touches about70 source/test/build files, including mechanical app-owned type renames. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding and source policy. |
| Verification | Owner-local tests, both native suites and Console joins, DOS/Win16 build checks, three products; node/ledger/governance gates. |
| Expected Markers | Twelve tracked gaps with receiving S and acceptance; empty node scope and expected matches; historical1992/1992 unchanged. |
| Asset Needs | Read-only sibling Mine, redistribution unreviewed, no import. Existing owner-local SMB1 ROM and previously qualified DOS/Win16 tools only for local builds; no ROM-derived output committed. Active logs below build/t44-s7 and native build trees. |
| Reporting Requirements | Explain retained/moved/missing capabilities and planned S sizes/exits; zero new node/edge credit. |
| Stop Conditions | No unapproved source import, game/PPU semantic change or readiness claim based only on static review. |
| Exit Criteria | G01-G04 contracts implemented, Mario behavior retained, no NES mappings in lib, tests and all three product builds pass; reviewer checks ownership and failure paths. |
| Original Owner Request | Reopen T; audit gaps, support Console/window mouse, return game refresh policy to app-mario, provide new S roadmap. |
| Similar-Issue Sweep | Four lib families plus app adapters: geometry/palette, input/capture, scheduling, device services, memory-model/build/test isolation. |

## Current Technical Baseline

S6 closes under the owner-approved automatic progression mandate. Its source
findings and governance gates are retained in the proposal. S7 closes G01-G04 with both native suites, both host joins, DOS/Win16
operational receipts and three refreshed local products. G05-G12 remain open. No Mine import.
Historical1992/1992; retained1991/1992 nodes and4260/4261 feasible controls
(4342raw,81infeasible). Zero new ROM scope/credit. Preserve17 unrelated resource
deletions. S7 local products are published; detailed hashes and memory receipt are in the proposal.
