# M2 T27: Screen routines, HUD and game text

## Status

T27 is the source-order screen/HUD/text task for ROM lines 1386--1824. It uses chain-based S delivery: each node remains individually tracked, while one admitted S covers a bounded contiguous source chain and its ROM route. S1 is closed. S2 is the active admitted contiguous status/text chain; S3 is reserved for the two integration roots whose dependencies extend into later source-order tasks.

## Scope and ownership

The 67 exact labels below remain ordered by original source. Shared game owners may write only game-owned RAM, VRAM-buffer, CIRAM, palette and PPU snapshot state. Win32 and DOS adapters only consume the neutral output; they may not choose text, status, palette, task or timer outcomes.

| S | Chain | Lines | Exact labels | ROM route and acceptance focus |
| --- | --- | ---: | --- | --- |
| S1 | Screen-task root, initial setup and palette initialization (`ScreenRoutines -> NoAltPal`) | 1386--1513 | `ScreenRoutines`, `InitScreen`, `SetupIntermediate`, `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal` | task-vector dispatch, screen setup, intermediate palette call, palette branches and VRAM address writes; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S2 | Status, intermediate display, title drawing and game text (`WriteTopStatusLine -> NoReset`) | 1517--1813 | exact 45 labels in the table below | one controlled contiguous screen route; all local branches/data loops plus title, status, two-player, time-up, lives/name, warp and reset behavior. `AreaParserTaskControl` is retained for S3 because it calls the T29 parser owner. |
| S3 | Dispatch/parser integration (`ScreenRoutines`, `AreaParserTaskControl`) | 1386, 1595 | `ScreenRoutines`, `AreaParserTaskControl` | close only after every ScreenRoutines table target and the T29 parser call are independently proven; no duplicate leaf credit. |

## Exact node list

| ROM line | Node | Incoming status | Planned S |
| ---: | --- | --- | --- |
| 1386 | `ScreenRoutines` | open | S3 |
| 1408 | `InitScreen` | ROM-match complete | S1 (closed) |
| 1418 | `SetupIntermediate` | ROM-match complete | S1 (closed) |
| 1436 | `AreaPalette` | ROM-match complete | S1 (closed) |
| 1439 | `GetAreaPalette` | ROM-match complete | S1 (closed) |
| 1442 | `SetVRAMAddr_A` | ROM-match complete | S1 (closed) |
| 1443 | `NextSubtask` | ROM-match complete | S1 (closed) |
| 1448 | `BGColorCtrl_Addr` | ROM-match complete | S1 (closed) |
| 1451 | `BackgroundColors` | ROM-match complete | S1 (closed) |
| 1455 | `PlayerColors` | ROM-match complete | S1 (closed) |
| 1460 | `GetBackgroundColor` | ROM-match complete | S1 (closed) |
| 1465 | `NoBGColor` | ROM-match complete | S1 (closed) |
| 1467 | `GetPlayerColors` | ROM-match complete | S1 (closed) |
| 1473 | `ChkFiery` | ROM-match complete | S1 (closed) |
| 1477 | `StartClrGet` | ROM-match complete | S1 (closed) |
| 1479 | `ClrGetLoop` | ROM-match complete | S1 (closed) |
| 1489 | `SetBGColor` | ROM-match complete | S1 (closed) |
| 1502 | `SetVRAMOffset` | ROM-match complete | S1 (closed) |
| 1507 | `GetAlternatePalette1` | ROM-match complete | S1 (closed) |
| 1512 | `SetVRAMAddr_B` | ROM-match complete | S1 (closed) |
| 1513 | `NoAltPal` | ROM-match complete | S1 (closed) |
| 1517 | `WriteTopStatusLine` | open | S2 |
| 1524 | `WriteBottomStatusLine` | open | S2 |
| 1553 | `DisplayTimeUp` | open | S2 |
| 1560 | `NoTimeUp` | open | S2 |
| 1565 | `DisplayIntermediate` | open | S2 |
| 1577 | `PlayerInter` | open | S2 |
| 1579 | `OutputInter` | open | S2 |
| 1584 | `GameOverInter` | open | S2 |
| 1589 | `NoInter` | open | S2 |
| 1595 | `AreaParserTaskControl` | open; T29 dependency | S3 |
| 1597 | `TaskLoop` | open | S2 |
| 1603 | `OutputCol` | open | S2 |
| 1612 | `DrawTitleScreen` | open | S2 |
| 1624 | `OutputTScr` | open | S2 |
| 1629 | `ChkHiByte` | open | S2 |
| 1639 | `ClearBuffersDrawIcon` | open | S2 |
| 1643 | `TScrClear` | open | S2 |
| 1648 | `IncSubtask` | open | S2 |
| 1653 | `WriteTopScore` | open | S2 |
| 1656 | `IncModeTask_B` | open | S2 |
| 1661 | `GameText` | open | S2 |
| 1662 | `TopStatusBarLine` | open | S2 |
| 1671 | `WorldLivesDisplay` | open | S2 |
| 1680 | `TwoPlayerTimeUp` | open | S2 |
| 1682 | `OnePlayerTimeUp` | open | S2 |
| 1686 | `TwoPlayerGameOver` | open | S2 |
| 1688 | `OnePlayerGameOver` | open | S2 |
| 1693 | `WarpZoneWelcome` | open | S2 |
| 1704 | `LuigiName` | open | S2 |
| 1707 | `WarpZoneNumbers` | open | S2 |
| 1712 | `GameTextOffsets` | open | S2 |
| 1719 | `WriteGameText` | open | S2 |
| 1728 | `Chk2Players` | open | S2 |
| 1731 | `LdGameText` | open | S2 |
| 1733 | `GameTextLoop` | open | S2 |
| 1740 | `EndGameText` | open | S2 |
| 1756 | `PutLives` | open | S2 |
| 1765 | `CheckPlayerName` | open | S2 |
| 1775 | `ChkLuigi` | open | S2 |
| 1778 | `NameLoop` | open | S2 |
| 1782 | `ExitChkName` | open | S2 |
| 1784 | `PrintWarpZoneNumbers` | open | S2 |
| 1790 | `WarpNumLoop` | open | S2 |
| 1804 | `ResetSpritesAndScreenTimer` | open | S2 |
| 1809 | `ResetScreenTimer` | open | S2 |
| 1813 | `NoReset` | open | S2 |

## S1 admission contract

S1 is one contiguous source chain: `ScreenRoutines -> InitScreen -> SetupIntermediate -> AreaPalette/GetAreaPalette -> GetBackgroundColor -> GetPlayerColors -> SetBGColor -> GetAlternatePalette1 -> NoAltPal` at ROM lines 1386--1513. It receives exactly the first 21 labels below from T24 S2 custody. Its baseline is 100 / 1,992; all are open; 20 leaf/data nodes are expected to become ROM-match complete, for a maximum 120 / 1,992. `ScreenRoutines` remains in S1 scope but cannot close until its remaining 11 dispatch targets receive their own chain evidence and the final T27 integration chain proves the whole table. It compares every task-vector selection, task-byte increment, area/intermediate branch, palette-table binding, player-status save/restore, VRAM address-control write and carry-return behavior against the owner-supplied local ROM/disassembly. Its operational lane uses focused screen status smoke plus a controlled title-to-area-entry original-ROM route, then x86/x64 native traces, DOS16 link and platform-purity check. Owner-supplied ROM/disassembly are local research inputs only; generated traces stay under ignored `build/` and are not committed.

## T27 closure

T27 closes only after every S1--S3 node has both ROM logic-equivalence evidence and operational evidence, a cross-chain title/area-entry/status/warp matrix passes, all incomplete labels are transferred to accepted successors, and one integrated three-target regression runs.

## S1 closure: screen initialization and palette chain

S1 closes exactly 20 labels: `InitScreen`, `SetupIntermediate`, `AreaPalette`,
`GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`,
`BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`,
`GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`,
`SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B` and `NoAltPal`.
`ScreenRoutines` remains uncredited because its 15-entry table reaches chains
outside S1. The shared C owner now preserves GetBackgroundColor's source order:
it increments `ScreenRoutineTask` before falling through to GetPlayerColors.

The focused smoke covers InitScreen's mode-zero and nonzero branches,
SetupIntermediate's status/background save and restore, the four-color palette
packet, area palette selection, background-control selection and mushroom-style
selection. Title/demo, local-area and platform-purity regressions pass. A
source-reachable one-Start 200-frame ROM route has zero differing frames for
ROM/x86, ROM/x64 and x86/x64 in work RAM `$0300-$07ff`, CIRAM, palette, OAM,
audio and PPU scalars. The shared C builds as the x86/x64 product and links as
OpenNT DOS16 MZ. Refreshed artifacts: `mysmb16.exe`
`646C4FAC9ECA0DDC4D4208177FBB025D5225FDB40787D513A5131996BDF2DAA3`,
`mysmb32.exe` `AE2E88A5244A955250C12D62CD8D2588D3E219D08B17384C4E9A66CA208721FA`,
and `mysmb64.exe` `C0FDADA6D1DBA84C0CAD13CBBD889B0215A7D179ABF517D5C5C6D75D51B45B9E`.
