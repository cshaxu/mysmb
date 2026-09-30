# Project Status

## Current Work

**M2 T47 S2 is closed at 1,719 / 1,992.** T46 closed all 43
player-graphics labels. T47 targets the next 40 source-order labels,
`ExPlyrAt` through `SetHFAt`; S1 proves `ExPlyrAt`; S2 proves all nine
relative-object-position labels; S3 is next and unadmitted.

## M2 T47 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T47 S2, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; T16 S4 transfers the nine exact `RelativePlayerPosition` through `GetObjRelativePosition` labels. |
| Objective | Translate and prove shared relative-coordinate chain. T47 targets 40 exact labels, all intended matches across five S. |
| Non-goals | No S3 player offscreen or later T47 node credit; no platform gameplay. |
| Reference Baseline | Closed from 1,710/1,992; S2 nine expected and actual matches, final 1,719; T47 maximum 1,749. |
| Candidate Proposal | [T47 task and S2](../proposals/m2/t47-object-position-and-sprite-output.md#s2-admission-shared-relative-object-coordinates). |
| Files And ABI Surface | Shared src/game/oam/object_position.c with bubble caller delegation, owner-ROM child records and native comparison; three EXEs; host adapters unchanged. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original GameEngine player/enemy/bubble/fireball/block/misc relative-position paths, source scratch and full RAM/OAM parity; focused x86/x64 tests/builds, DOS16 link, purity and artifacts. |
| Expected Markers | Source indexed coordinate reads, relative X/Y writes, `$00` scratch and `ObjectOffset` restoration across actor variants. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are nonredistributable local research inputs only; raw records under ignored build, plus owner-authorized three EXEs. |
| Reporting Requirements | Nine individual S2 dispositions and T47's 40-node S allocation, separate ROM-logic and operational tracks, original PC/RAM/OAM result and artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented coordinate policy or platform gameplay. |
| Exit Criteria | Met: nine relative-position node proofs, native x86/x64 parity, DOS16 link, purity, three EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All player size-change, graphics offset and attribute consumers in shared game code. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
