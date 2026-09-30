# Project Status

## Current Work

**M2 T47 S1 is closed at 1,710 / 1,992.** T46 closed all 43
player-graphics labels. T47 targets the next 40 source-order labels,
`ExPlyrAt` through `SetHFAt`; S1 proves `ExPlyrAt`; S2 is next and unadmitted.

## M2 T47 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T47 S1, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; T16 S4 transfers exact `ExPlyrAt` to T47 S1. |
| Objective | Prove original player attribute exit before admitting object-relative positioning. T47 targets 40 exact labels, all intended matches across five S. |
| Non-goals | No S2 relative-position or later T47 node credit; no platform gameplay. |
| Reference Baseline | Closed from 1,709/1,992; S1 one expected and actual new match, final 1,710; T47 maximum 1,749. |
| Candidate Proposal | [T47 task and S1](../proposals/m2/t47-object-position-and-sprite-output.md). |
| Files And ABI Surface | Shared src/game/oam/player_gfx.c, owner-ROM child records and native comparison; three EXEs; host adapters unchanged. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original GameEngine player attribute child entry/exit and RAM/OAM parity; focused x86/x64 tests/builds, DOS16 link, purity and artifacts. |
| Expected Markers | Source `$f129` reached from attribute-changing and no-op branches; RTS adds no write and C path returns with matching RAM/OAM. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are nonredistributable local research inputs only; raw records under ignored build, plus owner-authorized three EXEs. |
| Reporting Requirements | One individual S1 disposition and T47's 40-node S allocation, separate ROM-logic and operational tracks, original PC/RAM/OAM result and artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented sprite policy or platform gameplay. |
| Exit Criteria | Met: `ExPlyrAt` control/read/write proof, native x86/x64 parity, DOS16 link, purity, three EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All player size-change, graphics offset and attribute consumers in shared game code. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
