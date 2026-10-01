# Project Status

## Current Work

## M2 T61 S8 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S8 audit - Cohort H block lifetime and metatile-update chain. |
| Admission And Approval | Owner-approved source-order proof program; S7 is closed and this packet admits S8 only. |
| Objective | Audit and repair `BlockObjectsCore -> NextBUpd` against original-ROM semantics. |
| Non-goals | No platform-adapter logic or unadmitted motion/graphics child semantic claim. |
| Reference Baseline | Historical 1,992 / 1,992; current 786 / 1,992 nodes and 1,545 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | Shared `src/game/blocks/lifetime.c` and `replacement.c`; platform adapters are consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 routes, focused lifetime smoke, purity and DOS16 link. |
| Expected Markers | Eight nodes and 16 internal feasible controls. |
| Asset Needs | Shared-game repair refreshes three local EXEs. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992 and exact feasible controls / 4,324. |
| Stop Conditions | Any feasible difference remains in S8 until repaired and re-audited. |
| Exit Criteria | Closed: eight nodes and 16 internal controls exact; platform adapters contain no game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | State masks, slot loop order, bounce/kill thresholds, metatile writes and child order. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; T61 S8 is closed pending admission of its source-order successor.

## T61 S7 Closure

Twenty-eight block-chain nodes and fifty-five controls exact; no source changed.

## T61 S8 Closure

`BlockObjectsCore -> NextBUpd` is current-exact: eight nodes and sixteen internal feasible control relations passed static source comparison, controlled original-ROM/current x86/x64 caller and complete-current routes, focused C90 tests, platform purity and DOS16 link. Historical migration remains **1,992 / 1,992**; current registry is **786 / 1,992** exact nodes and **1,545 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.
