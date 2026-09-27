# M2 T27: Screen routines, HUD and game text

## Status

T27 is the source-order screen/HUD/text task for ROM lines 1386--1824. It uses chain-based S delivery: each node remains individually tracked, while one admitted S covers a bounded contiguous source chain and its ROM route. S1 is the active admitted chain; S2--S5 are planned successors and have no custody until their admission.

## Scope and ownership

The 67 exact labels below remain ordered by original source. Shared game owners may write only game-owned RAM, VRAM-buffer, CIRAM, palette and PPU snapshot state. Win32 and DOS adapters only consume the neutral output; they may not choose text, status, palette, task or timer outcomes.

| S | Chain | Lines | Exact labels | ROM route and acceptance focus |
| --- | --- | ---: | --- | --- |
| S1 | Screen-task root, initial setup and palette initialization (`ScreenRoutines -> NoAltPal`) | 1386--1513 | `ScreenRoutines`, `InitScreen`, `SetupIntermediate`, `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal` | task-vector dispatch, screen setup, intermediate palette call, palette branches and VRAM address writes; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S2 | Status-line writers and intermediate-screen task dispatch (`WriteTopStatusLine -> OutputCol`) | 1517--1603 | `WriteTopStatusLine`, `WriteBottomStatusLine`, `DisplayTimeUp`, `NoTimeUp`, `DisplayIntermediate`, `PlayerInter`, `OutputInter`, `GameOverInter`, `NoInter`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol` | status bytes, time-up and parser task handoff; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S3 | Title-screen drawing and transition handoff (`DrawTitleScreen -> IncModeTask_B`) | 1612--1656 | `DrawTitleScreen`, `OutputTScr`, `ChkHiByte`, `ClearBuffersDrawIcon`, `TScrClear`, `IncSubtask`, `WriteTopScore`, `IncModeTask_B` | title VRAM construction and task increment; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S4 | Game-text table, selector and writer loop (`GameText -> EndGameText`) | 1661--1740 | `GameText`, `TopStatusBarLine`, `WorldLivesDisplay`, `TwoPlayerTimeUp`, `OnePlayerTimeUp`, `TwoPlayerGameOver`, `OnePlayerGameOver`, `WarpZoneWelcome`, `LuigiName`, `WarpZoneNumbers`, `GameTextOffsets`, `WriteGameText`, `Chk2Players`, `LdGameText`, `GameTextLoop`, `EndGameText` | text table, player branches and VRAM write loop; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S5 | Lives/name rendering, Warp Zone numbers and screen timer reset (`PutLives -> NoReset`) | 1756--1813 | `PutLives`, `CheckPlayerName`, `ChkLuigi`, `NameLoop`, `ExitChkName`, `PrintWarpZoneNumbers`, `WarpNumLoop`, `ResetSpritesAndScreenTimer`, `ResetScreenTimer`, `NoReset` | player-name selection, warp-number loop and reset branch; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |

## Exact node list

| ROM line | Node | Incoming status | Planned S |
| ---: | --- | --- | --- |
| 1386 | `ScreenRoutines` | open | S1 |
| 1408 | `InitScreen` | open | S1 |
| 1418 | `SetupIntermediate` | open | S1 |
| 1436 | `AreaPalette` | open | S1 |
| 1439 | `GetAreaPalette` | open | S1 |
| 1442 | `SetVRAMAddr_A` | open | S1 |
| 1443 | `NextSubtask` | open | S1 |
| 1448 | `BGColorCtrl_Addr` | open | S1 |
| 1451 | `BackgroundColors` | open | S1 |
| 1455 | `PlayerColors` | open | S1 |
| 1460 | `GetBackgroundColor` | open | S1 |
| 1465 | `NoBGColor` | open | S1 |
| 1467 | `GetPlayerColors` | open | S1 |
| 1473 | `ChkFiery` | open | S1 |
| 1477 | `StartClrGet` | open | S1 |
| 1479 | `ClrGetLoop` | open | S1 |
| 1489 | `SetBGColor` | open | S1 |
| 1502 | `SetVRAMOffset` | open | S1 |
| 1507 | `GetAlternatePalette1` | open | S1 |
| 1512 | `SetVRAMAddr_B` | open | S1 |
| 1513 | `NoAltPal` | open | S1 |
| 1517 | `WriteTopStatusLine` | open | S2 |
| 1524 | `WriteBottomStatusLine` | open | S2 |
| 1553 | `DisplayTimeUp` | open | S2 |
| 1560 | `NoTimeUp` | open | S2 |
| 1565 | `DisplayIntermediate` | open | S2 |
| 1577 | `PlayerInter` | open | S2 |
| 1579 | `OutputInter` | open | S2 |
| 1584 | `GameOverInter` | open | S2 |
| 1589 | `NoInter` | open | S2 |
| 1595 | `AreaParserTaskControl` | open | S2 |
| 1597 | `TaskLoop` | open | S2 |
| 1603 | `OutputCol` | open | S2 |
| 1612 | `DrawTitleScreen` | open | S3 |
| 1624 | `OutputTScr` | open | S3 |
| 1629 | `ChkHiByte` | open | S3 |
| 1639 | `ClearBuffersDrawIcon` | open | S3 |
| 1643 | `TScrClear` | open | S3 |
| 1648 | `IncSubtask` | open | S3 |
| 1653 | `WriteTopScore` | open | S3 |
| 1656 | `IncModeTask_B` | open | S3 |
| 1661 | `GameText` | open | S4 |
| 1662 | `TopStatusBarLine` | open | S4 |
| 1671 | `WorldLivesDisplay` | open | S4 |
| 1680 | `TwoPlayerTimeUp` | open | S4 |
| 1682 | `OnePlayerTimeUp` | open | S4 |
| 1686 | `TwoPlayerGameOver` | open | S4 |
| 1688 | `OnePlayerGameOver` | open | S4 |
| 1693 | `WarpZoneWelcome` | open | S4 |
| 1704 | `LuigiName` | open | S4 |
| 1707 | `WarpZoneNumbers` | open | S4 |
| 1712 | `GameTextOffsets` | open | S4 |
| 1719 | `WriteGameText` | open | S4 |
| 1728 | `Chk2Players` | open | S4 |
| 1731 | `LdGameText` | open | S4 |
| 1733 | `GameTextLoop` | open | S4 |
| 1740 | `EndGameText` | open | S4 |
| 1756 | `PutLives` | open | S5 |
| 1765 | `CheckPlayerName` | open | S5 |
| 1775 | `ChkLuigi` | open | S5 |
| 1778 | `NameLoop` | open | S5 |
| 1782 | `ExitChkName` | open | S5 |
| 1784 | `PrintWarpZoneNumbers` | open | S5 |
| 1790 | `WarpNumLoop` | open | S5 |
| 1804 | `ResetSpritesAndScreenTimer` | open | S5 |
| 1809 | `ResetScreenTimer` | open | S5 |
| 1813 | `NoReset` | open | S5 |

## S1 admission contract

S1 is one contiguous source chain: `ScreenRoutines -> InitScreen -> SetupIntermediate -> AreaPalette/GetAreaPalette -> GetBackgroundColor -> GetPlayerColors -> SetBGColor -> GetAlternatePalette1 -> NoAltPal` at ROM lines 1386--1513. It receives exactly the first 21 labels below from T24 S2 custody. Its baseline is 100 / 1,992; all are open; 20 leaf/data nodes are expected to become ROM-match complete, for a maximum 120 / 1,992. `ScreenRoutines` remains in S1 scope but cannot close until its remaining 11 dispatch targets receive their own chain evidence and the final T27 integration chain proves the whole table. It compares every task-vector selection, task-byte increment, area/intermediate branch, palette-table binding, player-status save/restore, VRAM address-control write and carry-return behavior against the owner-supplied local ROM/disassembly. Its operational lane uses focused screen status smoke plus a controlled title-to-area-entry original-ROM route, then x86/x64 native traces, DOS16 link and platform-purity check. Owner-supplied ROM/disassembly are local research inputs only; generated traces stay under ignored `build/` and are not committed.

## T27 closure

T27 closes only after every S1--S5 node has both ROM logic-equivalence evidence and operational evidence, a cross-chain title/area-entry/status/warp matrix passes, all incomplete labels are transferred to accepted successors, and one integrated three-target regression runs.
