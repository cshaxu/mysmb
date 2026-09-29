# Project Status

## Current Work

**M2 T46 S1 is closed at 1,679 / 1,992.** Ten new player-graphics
control labels match; three offscreen labels were retained and
rechecked. T46 S2 is next and not yet admitted.

## M2 T46 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T46 S1, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; T16 S4 transfers the 13 exact PlayerGfxHandler through NPROffscr labels. |
| Objective | Prove original player draw dispatch, swimming kick, throw rendering and offscreen control in shared C. |
| Non-goals | No S2-S4 player action, intermediate draw, size/attribute node credit; no T47 relative-position credit or platform gameplay. |
| Reference Baseline | Closed from 1,669/1,992; scope 13, actual new 10, retained/rechecked 3, final 1,679; 54 original player children per width. |
| Candidate Proposal | [T46 S1 player graphics control](../proposals/m2/t46-player-graphics-control.md#s1-admission-record). |
| Files And ABI Surface | Shared src/game/oam/player_gfx.c, project-owned oracle harness, original-ROM recorder and three EXEs; host adapters unchanged. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original GameEngine player child control/read/write and nonstack RAM/OAM comparison; focused native tests, x86/x64 and DOS16 builds, purity and artifacts. |
| Expected Markers | Injury skip, normal/killed/size dispatch, swimming kick gates, throw rerender and four offscreen rows. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are nonredistributable local research inputs only; raw records under ignored build, plus owner-authorized three EXEs. |
| Reporting Requirements | Thirteen individual node dispositions, separate ROM-logic and operational tracks, original PC/RAM/OAM results and artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented sprite policy or platform gameplay. |
| Exit Criteria | Met: ten new node control/read/write proofs and three retained rechecks, native x86/x64 parity, DOS16 link, purity, three refreshed EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All player draw, kick, throw and offscreen branches in shared game OAM. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
