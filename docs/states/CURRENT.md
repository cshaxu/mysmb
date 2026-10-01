# Project Status

## Current Work

## M2 T61 S8 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S8 audit - Cohort H block lifetime and metatile-update chain. |
| Admission And Approval | Owner-approved source-order proof program; S7 is closed and this packet admits S8 only. |
| Objective | Audit and repair `BlockObjectsCore -> NextBUpd` against original-ROM semantics. |
| Non-goals | No platform-adapter logic or unadmitted motion/graphics child semantic claim. |
| Reference Baseline | Historical 1,992 / 1,992; current 778 / 1,992 nodes and 1,529 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | Shared `src/game/blocks/lifetime.c` and `replacement.c`; platform adapters are consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 routes, focused lifetime smoke, purity and DOS16 link. |
| Expected Markers | Eight nodes and 16 internal feasible controls. |
| Asset Needs | Shared-game repair refreshes three local EXEs. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992 and exact feasible controls / 4,324. |
| Stop Conditions | Any feasible difference remains in S8 until repaired and re-audited. |
| Exit Criteria | Eight nodes and 16 internal controls exact; platform adapters contain no game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | State masks, slot loop order, bounce/kill thresholds, metatile writes and child order. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; T61 S8 is active.

## T61 S7 Closure

Twenty-eight block-chain nodes and fifty-five controls exact; no source changed.
