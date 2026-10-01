# Project Status

## Current Work

## M2 T61 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S7 audit - Cohort H player-head block and brick-shatter chain. |
| Admission And Approval | Owner-approved source-order proof program; S6 is closed and this packet admits S7 only. |
| Objective | Audit and, if required, repair `BlockYPosAdderData -> SpawnBrickChunks` against original-ROM semantics. |
| Non-goals | No semantic claim for area, score, coin, power-up, vine, audio or block-lifetime children beyond named S7 handoffs; no platform-adapter logic. |
| Reference Baseline | Historical 1,992 / 1,992; current 750 / 1,992 exact nodes and 1,474 / 4,324 exact feasible control relations. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | `src/game/blocks/head.c`, `bump.c`, `chunks.c`, and named shared game children; platform adapters remain consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 caller and full-product routes, focused head/block smoke, platform purity and DOS16 link. |
| Expected Markers | Twenty-eight scoped labels, all current-exact candidates; 55 owned internal feasible controls, one raw infeasible control, and four material handoffs. |
| Asset Needs | Audit initially; a shared-game repair refreshes three local EXEs. |
| Reporting Requirements | State every label and boundary disposition, historical 1,992 / 1,992, exact nodes / 1,992 and exact feasible controls / 4,324. |
| Stop Conditions | Any feasible difference remains in S7 until repaired and re-audited. |
| Exit Criteria | All 28 labels, 55 feasible internal controls and four material handoffs exact; platform adapters contain no game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Scratch-address high/low bytes, carry, small/big/crouch selection, timer branches, all dispatch selectors, block-buffer writes, chunk slot pairs and child-call order. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T61 S7 is closed; its successor requires a new admission packet.

## T61 S7 Closure

Twenty-eight block-chain nodes, fifty-five internal feasible controls and four material handoffs are exact; 296 caller and 296 full-current x86/x64 routes pass; no source changed.

## T61 S6 Closure

Ten power-up nodes, nineteen internal controls and two material handoffs are exact; current x86/x64 caller and full-product routes pass; no source changed.

## T61 S5 Closure

Eight newly exact score/tally nodes and seven internal edges; 112 x86/x64 caller and full-product routes passed; no source changed.
