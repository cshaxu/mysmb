# Project Status

## Current Work

**M2 T46 S3 is closed at 1,697 / 1,992.** Its 13
`ProcessPlayerAction` through `ExAnimC` action/animation labels
have original-ROM and native proof. T46 S4 is next and not yet admitted.

## M2 T46 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T46 S3, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; T16 S4 transfers the 13 exact ProcessPlayerAction through ExAnimC labels. |
| Objective | Translate and prove original player action selection and animation timing in shared C. |
| Non-goals | No S4 size/attribute node credit, T47 relative position or platform gameplay. |
| Reference Baseline | Closed from 1,684/1,992; thirteen actual new matches, final 1,697; forty original action children verified. |
| Candidate Proposal | [T46 S3 player action/animation](../proposals/m2/t46-player-graphics-control.md#s3-admission-record). |
| Files And ABI Surface | Shared src/game/oam/player_gfx.c, original-ROM child recorder and native comparison tests; three EXEs; host adapters unchanged. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original GameEngine ProcessPlayerAction child branch/return, offset/timer/scratch and full player RAM/OAM parity; focused x86/x64 tests/builds, DOS16 link, purity and artifacts. |
| Expected Markers | Standing/walk/skid, jump/fall, climb, swim gate, three/four-frame extent and timer expiry/wrap. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are nonredistributable local research inputs only; raw records under ignored build, plus owner-authorized three EXEs. |
| Reporting Requirements | Thirteen individual node dispositions, separate ROM-logic and operational tracks, original PC/RAM/OAM results and artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented sprite policy or platform gameplay. |
| Exit Criteria | Met: thirteen action/animation node control/read/write proofs, native x86/x64 parity, DOS16 link, purity, three refreshed EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All player action, animation timer and graphics-offset consumers in shared game code. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
