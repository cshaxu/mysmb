# M2 T27: Screen routines, HUD and game text

## Status

T27 is the source-order screen/HUD/text task for ROM lines 1386--1824. It uses chain-based S delivery: each node remains individually tracked, while one admitted S covers a bounded contiguous source chain and its ROM route. S1 is the active admitted chain; S2--S6 are planned successors and have no custody until their admission.

## Scope and ownership

The 67 exact labels below remain ordered by original source. Shared game owners may write only game-owned RAM, VRAM-buffer, CIRAM, palette and PPU snapshot state. Win32 and DOS adapters only consume the neutral output; they may not choose text, status, palette, task or timer outcomes.

| S | Chain | Lines | Exact labels | ROM route and acceptance focus |
| --- | --- | ---: | --- | --- |
| S1 | Screen-task root and initial task handoff (`ScreenRoutines -> InitScreen -> SetupIntermediate`) | 1386--1418 | `ScreenRoutines`, `InitScreen`, `SetupIntermediate` | screen task root and first task-vector handoff; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S2 | Area palette selection and VRAM address setup (`AreaPalette -> NoAltPal`) | 1436--1513 | `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal` | palette data, branches and VRAM address writes; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S3 | Status-line writers and intermediate-screen task dispatch (`WriteTopStatusLine -> OutputCol`) | 1517--1603 | `WriteTopStatusLine`, `WriteBottomStatusLine`, `DisplayTimeUp`, `NoTimeUp`, `DisplayIntermediate`, `PlayerInter`, `OutputInter`, `GameOverInter`, `NoInter`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol` | status bytes, time-up and parser task handoff; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S4 | Title-screen drawing and transition handoff (`DrawTitleScreen -> IncModeTask_B`) | 1612--1656 | `DrawTitleScreen`, `OutputTScr`, `ChkHiByte`, `ClearBuffersDrawIcon`, `TScrClear`, `IncSubtask`, `WriteTopScore`, `IncModeTask_B` | title VRAM construction and task increment; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S5 | Game-text table, selector and writer loop (`GameText -> EndGameText`) | 1661--1740 | `GameText`, `TopStatusBarLine`, `WorldLivesDisplay`, `TwoPlayerTimeUp`, `OnePlayerTimeUp`, `TwoPlayerGameOver`, `OnePlayerGameOver`, `WarpZoneWelcome`, `LuigiName`, `WarpZoneNumbers`, `GameTextOffsets`, `WriteGameText`, `Chk2Players`, `LdGameText`, `GameTextLoop`, `EndGameText` | text table, player branches, VRAM write loop; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S6 | Lives/name rendering, Warp Zone numbers and screen timer reset (`PutLives -> NoReset`) | 1756--1813 | `PutLives`, `CheckPlayerName`, `ChkLuigi`, `NameLoop`, `ExitChkName`, `PrintWarpZoneNumbers`, `WarpNumLoop`, `ResetSpritesAndScreenTimer`, `ResetScreenTimer`, `NoReset` | player-name selection, warp-number loop and reset branch; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |

## Exact node list

| ROM line | Node | Incoming status | Planned S |
| ---: | --- | --- | --- |
| 1386 | `ScreenRoutines` | open | S1 |
| 1408 | `InitScreen` | open | S1 |
| 1418 | `SetupIntermediate` | open | S1 |
| 1436 | `AreaPalette` | open | S2 |
| 1439 | `GetAreaPalette` | open | S2 |
| 1442 | `SetVRAMAddr_A` | open | S2 |
| 1443 | `NextSubtask` | open | S2 |
| 1448 | `BGColorCtrl_Addr` | open | S2 |
| 1451 | `BackgroundColors` | open | S2 |
| 1455 | `PlayerColors` | open | S2 |
| 1460 | `GetBackgroundColor` | open | S2 |
| 1465 | `NoBGColor` | open | S2 |
| 1467 | `GetPlayerColors` | open | S2 |
| 1473 | `ChkFiery` | open | S2 |
| 1477 | `StartClrGet` | open | S2 |
| 1479 | `ClrGetLoop` | open | S2 |
| 1489 | `SetBGColor` | open | S2 |
| 1502 | `SetVRAMOffset` | open | S2 |
| 1507 | `GetAlternatePalette1` | open | S2 |
| 1512 | `SetVRAMAddr_B` | open | S2 |
| 1513 | `NoAltPal` | open | S2 |
| 1517 | `WriteTopStatusLine` | open | S3 |
| 1524 | `WriteBottomStatusLine` | open | S3 |
| 1553 | `DisplayTimeUp` | open | S3 |
| 1560 | `NoTimeUp` | open | S3 |
| 1565 | `DisplayIntermediate` | open | S3 |
| 1577 | `PlayerInter` | open | S3 |
| 1579 | `OutputInter` | open | S3 |
| 1584 | `GameOverInter` | open | S3 |
| 1589 | `NoInter` | open | S3 |
| 1595 | `AreaParserTaskControl` | open | S3 |
| 1597 | `TaskLoop` | open | S3 |
| 1603 | `OutputCol` | open | S3 |
| 1612 | `DrawTitleScreen` | open | S4 |
| 1624 | `OutputTScr` | open | S4 |
| 1629 | `ChkHiByte` | open | S4 |
| 1639 | `ClearBuffersDrawIcon` | open | S4 |
| 1643 | `TScrClear` | open | S4 |
| 1648 | `IncSubtask` | open | S4 |
| 1653 | `WriteTopScore` | open | S4 |
| 1656 | `IncModeTask_B` | open | S4 |
| 1661 | `GameText` | open | S5 |
| 1662 | `TopStatusBarLine` | open | S5 |
| 1671 | `WorldLivesDisplay` | open | S5 |
| 1680 | `TwoPlayerTimeUp` | open | S5 |
| 1682 | `OnePlayerTimeUp` | open | S5 |
| 1686 | `TwoPlayerGameOver` | open | S5 |
| 1688 | `OnePlayerGameOver` | open | S5 |
| 1693 | `WarpZoneWelcome` | open | S5 |
| 1704 | `LuigiName` | open | S5 |
| 1707 | `WarpZoneNumbers` | open | S5 |
| 1712 | `GameTextOffsets` | open | S5 |
| 1719 | `WriteGameText` | open | S5 |
| 1728 | `Chk2Players` | open | S5 |
| 1731 | `LdGameText` | open | S5 |
| 1733 | `GameTextLoop` | open | S5 |
| 1740 | `EndGameText` | open | S5 |
| 1756 | `PutLives` | open | S6 |
| 1765 | `CheckPlayerName` | open | S6 |
| 1775 | `ChkLuigi` | open | S6 |
| 1778 | `NameLoop` | open | S6 |
| 1782 | `ExitChkName` | open | S6 |
| 1784 | `PrintWarpZoneNumbers` | open | S6 |
| 1790 | `WarpNumLoop` | open | S6 |
| 1804 | `ResetSpritesAndScreenTimer` | open | S6 |
| 1809 | `ResetScreenTimer` | open | S6 |
| 1813 | `NoReset` | open | S6 |

## S1 admission contract

S1 is one contiguous source chain: `ScreenRoutines -> InitScreen -> SetupIntermediate` at ROM lines 1386--1435. It receives exactly `ScreenRoutines`, `InitScreen`, and `SetupIntermediate` from T24 S2 custody. Its baseline is 100 / 1,992; all three are open and expected to become ROM-match complete, for a maximum 103 / 1,992. It compares the task-vector lookup, task byte increment, area/intermediate branch, `ScreenRoutineTask` writes, `OperMode_Task` increment and carry-return behavior against the owner-supplied local ROM/disassembly. Its operational lane uses focused screen status smoke plus a controlled title-to-area-entry original-ROM route, then x86/x64 native traces, DOS16 link and platform-purity check. Owner-supplied ROM/disassembly are local research inputs only; generated traces stay under ignored `build/` and are not committed.

## T27 closure

T27 closes only after every S1--S6 node has both ROM logic-equivalence evidence and operational evidence, a cross-chain title/area-entry/status/warp matrix passes, all incomplete labels are transferred to accepted successors, and one integrated three-target regression runs.
