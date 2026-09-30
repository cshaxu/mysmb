# Project Status

## Current Work

**M2 T47 S4 is closed at 1,746 / 1,992.** T46 closed all 43
player-graphics labels. T47 targets the next 40 source-order labels,
`ExPlyrAt` through `SetHFAt`; S1 proves `ExPlyrAt`; S2 proves all nine
relative-object-position labels; S3 proves `GetPlayerOffscreenBits`;
S4 proves all 26 shared offscreen labels; S5 is next and unadmitted.

## M2 T47 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T47 S4, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; T16 S4 transfers the exact 26 labels `GetFireballOffscreenBits` through `ExDivPD`. |
| Objective | Translate and prove shared offscreen entry, table, loop and divide chain. T47 targets 40 exact labels across five S. |
| Non-goals | No S5 sprite writer credit; no platform gameplay. |
| Reference Baseline | Closed from 1,720/1,992; S4 26 expected and actual matches, final 1,746; T47 maximum 1,749. |
| Candidate Proposal | [T47 S4](../proposals/m2/t47-object-position-and-sprite-output.md#s4-admission-shared-offscreen-bit-chain). |
| Files And ABI Surface | Shared src/game/oam/object_position.c and actor delegates, owner-ROM call/data records and native comparison; three EXEs; host adapters unchanged. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original GameEngine player/fireball/bubble/misc/enemy/block offscreen paths, tables, control and RAM/OAM; focused x86/x64 tests/builds, DOS16 link, purity and artifacts. |
| Expected Markers | Original nibble packing, fixed tables, `$00` and `$04–$07` scratch, restored X/ObjectOffset and exact actor result bytes. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are nonredistributable local research inputs only; raw records under ignored build, plus owner-authorized three EXEs. |
| Reporting Requirements | 26 individual S4 dispositions, separate ROM-logic and operational tracks, original PC/RAM/OAM/table proof and three artifact hashes. |
| Stop Conditions | Forced CPU branch, invented offscreen policy or platform gameplay. |
| Exit Criteria | Met: 26 source node proofs including repaired S3 scratch gap, native x86/x64 parity, DOS16 link, purity, three EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All player/fireball/bubble/misc/enemy/block offscreen callers and shared-helper handoffs in game code. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
