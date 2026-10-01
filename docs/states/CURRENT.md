# Project Status

## Current Work

## M2 T61 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S1 audit - Cohort H vine actor lifecycle. |
| Admission And Approval | Owner-approved M2 source-order proof program; T60 is closed and this packet admits T61 S1 only. |
| Objective | Audit and, if required, repair the shared-C `VineObjectHandler -> ExitVH` lifecycle against original-ROM control, state, material and output semantics. |
| Non-goals | No cannon, block, collision, OAM, relative-position, dispatcher or platform-adapter child semantic claim beyond named S1 handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current re-audit: 690 / 1,992 exact nodes and 1,376 / 4,324 exact feasible control relations; S1 scope is six pending labels and can raise current exact nodes to 696. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | `src/game/vine.c` and existing named shared game children; platform adapters remain consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Controlled original-ROM/current x86/x64 vine actor lifecycle routes; focused native route, cross-width comparison, shared DOS16 link and platform purity. |
| Expected Markers | Six labels and their owned feasible relations receive branch/read/write/table/call-order proof; x86/x64 records agree. |
| Asset Needs | Audit initially; any shared-game repair refreshes all three local executable artifacts. |
| Reporting Requirements | State S1's six label dispositions, both verification tracks, every boundary disposition, historical 1,992 / 1,992, exact nodes / 1,992 and exact feasible control relations / 4,324. |
| Stop Conditions | A feasible mismatch remains in S1 until repaired and the identical audit route passes. |
| Exit Criteria | All six labels and owned feasible relations are current-exact; no platform adapter contains game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Vine setup/actor ownership, height-data consumer, growth gate, offscreen retirement, OAM loop, metatile write and child return boundaries. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; platform
adapters do not own game logic. T61 S1 is the sole active packet.
