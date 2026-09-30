# Project Status

## Current Work

**M2 T46 is closed at 1,709 / 1,992.** S4 completes its twelve
`GetGfxOffsetAdder` through `C_S_IGAtt` size/attribute labels;
all 43 T46 labels now have original-ROM and native proof. T47 is
next and not yet admitted.

## M2 T46 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T46 S4, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; T16 S4 transfers the twelve exact GetGfxOffsetAdder through C_S_IGAtt labels. |
| Objective | Translate and prove original size-change graphics and player sprite attribute logic in shared C. |
| Non-goals | No T47 ExPlyrAt or relative-position node credit, no platform gameplay. |
| Reference Baseline | Closed from 1,697/1,992; twelve actual new matches, final 1,709; all 43 T46 labels complete. |
| Candidate Proposal | [T46 S4 size/attribute chain](../proposals/m2/t46-player-graphics-control.md#s4-admission-record). |
| Files And ABI Surface | Shared src/game/oam/player_gfx.c, owner-ROM child recorder and native comparison tests; three EXEs; host adapters unchanged. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original GameEngine player graphic/attribute child branches, offset/table/animation and full non-stack RAM/OAM parity; focused x86/x64 tests/builds, DOS16 link, purity and artifacts. |
| Expected Markers | Big/small offset, all 20 growth/shrink table indices, fourth-frame wrap, killed/crouch/intermediate OAM attributes. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are nonredistributable local research inputs only; raw records under ignored build, plus owner-authorized three EXEs. |
| Reporting Requirements | Twelve individual node dispositions, separate ROM-logic and operational tracks, original PC/RAM/OAM results and artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented sprite policy or platform gameplay. |
| Exit Criteria | Met: twelve size/attribute node control/read/write proofs, native x86/x64 parity, DOS16 link, purity, three refreshed EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All player size-change, graphics offset and attribute consumers in shared game code. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
