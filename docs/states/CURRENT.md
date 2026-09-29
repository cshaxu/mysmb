# Project Status

## Current Work

**M2 T45 S5 and T45 are closed at 1,669 / 1,992.** All five S5
bubble/player graphics labels match the original ROM; the 45-label T45
slice is complete. T46 is next and not yet admitted.

## M2 T45 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T45 S5, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; DrawBubble, ExDBub and PlayerGfxTblOffsets transfer from M2 T17 S6; PlayerGraphicsTable and SwimKickTileNum transfer from M2 T16 S4. |
| Objective | Translate and prove the original DrawBubble through SwimKickTileNum OAM/data consumer chain, including T24 D5. |
| Non-goals | No unrelated PlayerGfxHandler node credit, platform gameplay, ROM emulator, or release claim. |
| Reference Baseline | Closed from 1,664/1,992; five actual new matches; final 1,669/1,992. |
| Candidate Proposal | [T45 S5 bubble and player graphics data](../history/M2-T45-object-oam-tail-and-graphics.md#s5-admission-record). |
| Files And ABI Surface | Shared src/game/fireball/bubble.c and src/game/oam/player_gfx.c, original-ROM child probes and three EXEs; host adapters unchanged. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original underwater GameEngine bubble/player child branches, owner-ROM table bytes and full nonstack RAM/OAM comparisons; focused native tests, x86/x64 and DOS16 builds, purity and artifacts. |
| Expected Markers | Bubble high-Y and offscreen d3 exits; table offset/indexed tile reads; swim kick facing/size/frame sprite-seven/eight writes. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are nonredistributable local research inputs only; raw records under ignored build, plus owner-authorized three EXEs. |
| Reporting Requirements | Five individual node dispositions, separate ROM-logic and operational tracks, original branch/RAM/OAM results and artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented sprite policy or platform gameplay. |
| Exit Criteria | Met: five ROM control/table/read/write proofs, native x86/x64 parity, DOS16 link, purity, three refreshed EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All bubble OAM and player swim-kick consumers sharing this table/attribute seam. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
