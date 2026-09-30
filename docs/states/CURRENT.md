# Project Status

## Current Work

**M2 T47 S3 is closed at 1,720 / 1,992.** T46 closed all 43
player-graphics labels. T47 targets the next 40 source-order labels,
`ExPlyrAt` through `SetHFAt`; S1 proves `ExPlyrAt`; S2 proves all nine
relative-object-position labels; S3 proves `GetPlayerOffscreenBits`; S4 is next and unadmitted.

## M2 T47 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T47 S3, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; T16 S4 transfers exact `GetPlayerOffscreenBits` label. |
| Objective | Prove original player offscreen entry and shared C dataflow. T47 targets 40 exact labels across five S. |
| Non-goals | No S4 offscreen-helper node credit; no platform gameplay. |
| Reference Baseline | Closed from 1,719/1,992; S3 one expected and actual match, final 1,720; T47 maximum 1,749. |
| Candidate Proposal | [T47 S3](../proposals/m2/t47-object-position-and-sprite-output.md#s3-admission-player-offscreen-entry). |
| Files And ABI Surface | Shared src/game/oam/player_gfx.c, owner-ROM entry record and native comparison; three EXEs; host adapters unchanged. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original GameEngine player offscreen entry and successor, registers and RAM/OAM; focused x86/x64 player tests/builds, DOS16 link, purity and artifacts. |
| Expected Markers | `$f180` loads X=Y=0 and jumps to `GetOffScreenBitsSet`; player offscreen byte is returned through shared game logic. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are nonredistributable local research inputs only; raw records under ignored build, plus owner-authorized three EXEs. |
| Reporting Requirements | One exact S3 disposition, separate ROM-logic and operational tracks, original PC/register/result proof and three artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted S4 helper credit, invented offscreen policy or platform gameplay. |
| Exit Criteria | Met: player offscreen entry proof, native x86/x64 parity, DOS16 link, purity, three EXEs and ledger closure; S4 helper scratch gap retained. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All player offscreen callers and shared-helper handoffs in game code. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
