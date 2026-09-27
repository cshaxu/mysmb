# M2 T27: Screen routines, HUD and game text

## Status

T27 is the source-order screen/HUD/text task for ROM lines 1386--1824. It uses chain-based S delivery: each node remains individually tracked, while one admitted S covers a bounded contiguous source chain and its ROM route. S1 is closed. S2 is the active admitted contiguous status/text chain; S3 is reserved for the two integration roots whose dependencies extend into later source-order tasks.

## Scope and ownership

The 67 exact labels below remain ordered by original source. Shared game owners may write only game-owned RAM, VRAM-buffer, CIRAM, palette and PPU snapshot state. Win32 and DOS adapters only consume the neutral output; they may not choose text, status, palette, task or timer outcomes.

| S | Chain | Lines | Exact labels | ROM route and acceptance focus |
| --- | --- | ---: | --- | --- |
| S1 | Screen-task root, initial setup and palette initialization (`ScreenRoutines -> NoAltPal`) | 1386--1513 | `ScreenRoutines`, `InitScreen`, `SetupIntermediate`, `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal` | task-vector dispatch, screen setup, intermediate palette call, palette branches and VRAM address writes; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S2 | Status, intermediate display, title drawing and game text (`WriteTopStatusLine -> NoReset`) | 1517--1813 | exact 43 labels in the table below | one controlled contiguous screen route; all local branches/data loops plus title, status, two-player, time-up, lives/name, warp and reset behavior. `AreaParserTaskControl` is retained for S3 because it calls the T29 parser owner. |
| S3 | Dispatch/parser integration (`ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol`) | 1386, 1595 | `ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol` | close only after every ScreenRoutines table target and the T29 parser call are independently proven; no duplicate leaf credit. |

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
| 1597 | `TaskLoop` | open; T29 dependency | S3 |
| 1603 | `OutputCol` | open; T29 dependency | S3 |
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

## S2/P1: DisplayIntermediate castle precedence repair

Original ROM lines 1565--1589 take the `AreaType == 3` branch to
`PlayerInter` before testing `DisableIntermediate`. The shared C path had
combined the disable flag with the NoInter condition, causing a castle route
with that flag set to skip the lives display. `game.c` now preserves the
source branch order. `screen_status_smoke` covers the castle/disabled branch;
its intentionally incomplete text source proves the task remains at six
rather than incorrectly taking NoInter task eight. No S2 label is credited by
this narrow repair: the whole 45-label chain still requires its complete
source and ROM-route evidence.

P1 operational evidence: x64 screen-status/local-area/platform-purity CTests
pass; x86 screen-status smoke passes; the shared source rebuilds x86/x64
products and OpenNT DOS16 MZ. Refreshed local artifacts: `mysmb16.exe`
`8CA1BBE6BB79A765245F03E5312CD16C8EB7C06D11586E51462B99CDF62CEFB5`,
`mysmb32.exe` `AE2E88A5244A955250C12D62CD8D2588D3E219D08B17384C4E9A66CA208721FA`, `mysmb64.exe` `C0FDADA6D1DBA84C0CAD13CBBD889B0215A7D179ABF517D5C5C6D75D51B45B9E`.

## S2/P2: PlayerInter before OutputInter

ROM `PlayerInter` at lines 1577--1579 invokes `DrawPlayer_Intermediate`
before it enters `OutputInter/WriteGameText`. The shared screen state machine
now has that exact call order. Existing local-area intermediate and screen
status regressions pass, along with platform purity; x86/x64 products and
OpenNT DOS16 MZ rebuild from the shared source. Refreshed artifacts:
`mysmb16.exe` `22E30540D963EAB0530E3784A802AC5F7E048B790EF8E738512EC3EA94CFB603`,
`mysmb32.exe` `AE2E88A5244A955250C12D62CD8D2588D3E219D08B17384C4E9A66CA208721FA`,
and `mysmb64.exe` `C0FDADA6D1DBA84C0CAD13CBBD889B0215A7D179ABF517D5C5C6D75D51B45B9E`.
No S2 node credit is claimed before the complete chain proof.

## S2/P3: DisplayTimeUp OutputInter writes

ROM lines 1553--1561 clear `GameTimerExpiredFlag` before `OutputInter`, which
then restores `DisableScreenFlag`, resets the timer and advances the screen
task. The shared C now preserves those writes. Focused status, local-area and
platform-purity tests pass; x86/x64 and DOS16 rebuild. `mysmb16.exe`
`3BA599B460EBBB9E3C262BAB75CE2DE97D8B1EF7486B28F862F004D1FC8AE48A`;
x86/x64 artifacts remain the same byte hashes recorded in P2.

## S2/P4: WriteGameText lives and player-name tails

ROM `EndGameText`/`PutLives` writes crown tile `$9f` when the displayed life
count reaches ten, while `CheckPlayerName` also applies to top status selector
zero. The shared text writer now preserves both branches and the TIME UP /
GAME OVER player-selection rule. Local ROM-table smoke coverage, platform
purity and x86/x64 builds pass; DOS16 links. `mysmb16.exe`
`E912E3F3E6967C6D31834F1256937585F5871FAC3358BF0BBE627AE0F67F4ECA`;
the x86/x64 hashes remain as recorded in P3.
## S2 chain-delivery confirmation

S2 retains its admitted 43-label `WriteTopStatusLine -> NoReset` scope and
will close it as one chain.  It does not create separate mapping, migration,
audit, test, or paperwork S stages.  Each remaining P may repair and compare
adjacent members of that chain, but credits none until the shared ROM route and
operational track cover the named label.  Any member blocked by the T29 parser
or another accepted owner transfers by exact name before S2 closes.
## S2/P5: unconditional screen-task continuations

The ROM source at lines 1517--1589 has no branch on a native output-capacity
result. `WriteTopStatusLine` and `WriteBottomStatusLine` always reach
`IncSubtask`; `GameOverInter` always reaches `IncModeTask_B`; and the castle
or enabled `PlayerInter` path calls `WriteGameText`, `ResetScreenTimer`, clears
`DisableScreenFlag`, and returns with task seven. The shared C had invented
retry branches when a safe native command writer returned zero. It now keeps
that return only as neutral-output containment and always performs the ROM
state transition. The focused status smoke intentionally supplies an incomplete
text binding for the castle path and proves task 6 becomes 7, screen timer is
7, and screen output is reenabled, so this test cannot confuse a C-only retry
with the original `NoInter` branch.

The similar-issue sweep reviewed every S2 caller of the three text/status
writers in `game.c`: task 2, task 3, GameOverInter and PlayerInter. Task 4 was
already unconditional; task 14 already advances `OperMode_Task` regardless of
the title-score writer result. No platform file contains these decisions.

Operational evidence: focused x64 `screen-status`, `local-area`, and
platform-purity CTests pass; x86 screen-status and local-area executables pass;
both refreshed Win32 products pass `--self-test`; and the same source compiles
and links to the OpenNT DOS16 MZ (existing C4761 warnings only). Refreshed
local artifacts are `mysmb16.exe`
`47ACB049659D01EAC904B698B7111441657D11B421DFE2133A32A50DBB02B06E`,
`mysmb32.exe`
`95D1AF2D2706D658CAFE9ED2122E3DD16F14EFC1BBFF74BB42D6CA6E7B9E4BB0`,
and `mysmb64.exe`
`56C07DD8C873BC12450EAC3C8DB555ED72383DAF8310A9EB4BFA0710704C69E5`.
No S2 node is credited yet: the remaining chain still requires its declared
source-level matrix and controlled original-ROM route.
## S2/P6: controlled cold-title ROM route

The owner-local reference recorder and the current shared-C recorder each
started from the ROM cold state, used zero controller input, and sampled 200
consecutive NMI returns through the title screen path. The native recorder used
its source-owned title bootstrap; the reference recorder ran the owner-supplied
local ROM. Their ignored raw records are bounded below `build/m2-t27-s2/`.
Across all 200 samples, work RAM `$0300-$07ff`, both CIRAM pages, palette, OAM,
audio-command state, and all PPU scalar bytes have zero differing frames. This
operational route exercises the S2 title/status progression with the ROM's
actual VRAM and OAM timing. It does not by itself prove every game-text,
intermediate, two-player, Time Up, Game Over, or Warp branch, so no node credit
is added.

The three focused local title tests also pass on the current x64 owner: title
command transfer, title palette oracle, and cold-title bootstrap sequence.
## S2/P7: controlled Time Up, intermediate and Game Over routes

Three named recorder-only S2 fixtures are applied at a real NMI boundary after
sixty ordinary cold-title samples. They are mirrored in the project-owned
native recorder and the isolated reference recorder; neither is linked into a
product or platform adapter. Each records four subsequent NMI returns.

- `t27-screen-timeup` enters GameMode/ScreenRoutines task four with the timer
  expiry latch set.
- `t27-screen-intermediate` enters GameMode task one/ScreenRoutines task six
  with castle `AreaType` and `DisableIntermediate` set, exercising the source
  `PlayerInter` precedence and its OAM/text/timer tail.
- `t27-screen-gameover` enters GameOverMode task one/ScreenRoutines task six,
  exercising `GameOverInter` and its mode-task transition.

For all three routes, the ROM and current shared C have zero differing frames
in work RAM `$0300-$07ff`, both CIRAM pages, palette, OAM, audio-command state
and PPU scalar output. The recorder source itself builds in the isolated MyNES
reference graph and the native recorder builds in the x64 project graph. This
adds operational branch evidence for the listed screen/text calls; it does not
credit individual labels before the S2 source-level matrix and remaining
text/warp branch routes are complete.
## S2/P8: controlled remaining screen-task branches and Warp selector matrix

Four additional recorder-only snapshots were applied after sixty ordinary
cold-title NMIs on both the local original-ROM reference and the shared-C
recorder. They are injected at the same NMI boundary and each records the next
four NMI returns.

- `t27-screen-no-timeup` enters GameMode task one / screen task four without
  `GameTimerExpiredFlag`, proving the source `NoTimeUp -> IncSubtask` path.
- `t27-screen-player-intermediate` enters the ordinary, non-castle
  `PlayerInter` route and proves its lives-text/OAM/reset tail separately from
  the castle precedence route in P7.
- `t27-screen-reset-pending` enters screen task five with a nonzero
  `ScreenTimer`, proving `NoReset` leaves the task and OAM state intact.
- `t27-screen-reset-expired` enters the same task with zero `ScreenTimer`,
  proving `MoveAllSpritesOffscreen -> ResetScreenTimer -> IncSubtask`.

All four ROM/native comparisons have zero differing samples in work RAM
`$0300-$07ff`, both CIRAM pages, palette, OAM, audio-command state and PPU
scalar output. Raw records remain ignored under
`build/m2-t27-s2/p8-screen-fixtures/`.

The project-owned local-area smoke now independently checks the source table
indices for all three Warp Zone selectors: selector four uses `$07f2-$07f4`,
selector five `$07f6-$07f8`, and selector six `$07fa-$07fc`, with the ROM's
three writes spaced four bytes apart and `$2c` buffer offset. This completes
the local selector matrix but does not replace the still-required
source-reachable original-ROM warp route.

Focused x64 `screen-status`, `local-area` and platform-purity CTests pass; x86
`local-area`, `screen-status` and product self-test pass; the same shared
source links to the OpenNT DOS16 MZ with only the established C4761 and
OLDNAMES warnings. The three user-testable artifacts were refreshed from those
builds: `mysmb16.exe`
`47ACB049659D01EAC904B698B7111441657D11B421DFE2133A32A50DBB02B06E`,
`mysmb32.exe`
`95D1AF2D2706D658CAFE9ED2122E3DD16F14EFC1BBFF74BB42D6CA6E7B9E4BB0`,
and `mysmb64.exe`
`56C07DD8C873BC12450EAC3C8DB555ED72383DAF8310A9EB4BFA0710704C69E5`.

## S2 per-node source/evidence matrix

This matrix is the S2 source-review record. `Mapped` means the ROM branch,
read/write sequence and shared-C owner were reviewed. `Route` names operational
coverage already obtained; it is not a completion mark. `Pending` names the
remaining required branch or dependency. Every row remains incomplete until
both tracks are accepted at S2 closure.

| Node | Shared-C mapping | Current evidence and remaining proof |
| --- | --- | --- |
| `WriteTopStatusLine` | `game.c` task 2 -> `area.c` top-text writer | Mapped; cold-title route and local-area smoke. Pending two-player name route in a full screen chain. |
| `WriteBottomStatusLine` | `game.c` task 3 -> `area.c` bottom-status writer | Mapped; cold-title route and local-area smoke. Pending its `GetSBNybbles` collaborator's later-source evidence. |
| `DisplayTimeUp` | `game.c` task 4 | Mapped; screen-status smoke and `t27-screen-timeup` zero-difference route. Pending final chain matrix. |
| `NoTimeUp` | `game.c` task 4 else | Mapped; screen-status smoke and `t27-screen-no-timeup` zero-difference route. Pending final chain matrix. |
| `DisplayIntermediate` | `game.c` task 6 | Mapped; castle and ordinary intermediate fixtures. Pending alternate-entrance matrix. |
| `PlayerInter` | `game.c` task 6 and intermediate OAM owner | Mapped; castle and ordinary fixtures prove call order and output tail. Pending final text/name matrix. |
| `OutputInter` | `game.c` task 4/task 6 common writes | Mapped; Time Up and intermediate fixtures. Pending common-path byte matrix. |
| `GameOverInter` | `game.c` task 6, `terminal_modes.c` game-over root | Mapped; `t27-screen-gameover` zero-difference route. Pending two-player name branch. |
| `NoInter` | `game.c` task 6 direct task-8 assignment | Mapped; local-area route. Pending alternate-entry controlled route. |
| `DrawTitleScreen` | `game.c` task 12 | Mapped; local title tests and 200-frame cold-title route. Pending exact title-transfer byte matrix. |
| `OutputTScr` | `game.c` title-data copy loop | Mapped; title bootstrap smoke and cold-title route. Pending source-byte/count audit record. |
| `ChkHiByte` | `game.c` title-data copy bound | Mapped; title bootstrap smoke. Pending exact `$043a` boundary record. |
| `ClearBuffersDrawIcon` | `game.c` task 13 | Mapped; title bootstrap smoke and cold-title route. Pending mode-nonzero exit route. |
| `TScrClear` | `game.c` task 13 clear loop | Mapped; title bootstrap smoke. Pending complete `$0300-$04ff` byte audit. |
| `IncSubtask` | `game.c` task transitions | Mapped; all screen fixtures. Pending final table-wide transition matrix. |
| `WriteTopScore` | `game.c` task 14 -> `area.c` title-score writer | Mapped; title bootstrap smoke. Pending source `UpdateNumber` collaborator audit. |
| `IncModeTask_B` | `game.c` tasks 12/14 and Game Over branch | Mapped; title and Game Over routes. Pending non-title DrawTitle exit route. |
| `GameText` | bound local PRG data in `area.c` | Mapped; local-area smoke. Pending data-byte audit. |
| `TopStatusBarLine` | selector zero in `area.c` | Mapped; cold-title route and top-text smoke. Pending two-player Luigi replacement route. |
| `WorldLivesDisplay` | selector one in `area.c` | Mapped; local-area lives/crown smoke and ordinary `PlayerInter` ROM fixture. Pending full selector/name matrix. |
| `TwoPlayerTimeUp` | selector two source offset in `area.c` | Mapped; source review only. Pending two-player Time Up route. |
| `OnePlayerTimeUp` | selector two source offset in `area.c` | Mapped; Time Up fixture. Pending source-byte audit. |
| `TwoPlayerGameOver` | selector three source offset in `area.c` | Mapped; source review only. Pending two-player Game Over route. |
| `OnePlayerGameOver` | selector three source offset in `area.c` | Mapped; Game Over fixture. Pending source-byte audit. |
| `WarpZoneWelcome` | selector four source offset in `area.c` | Mapped; local-area warp smoke. Pending controlled original ROM warp route. |
| `LuigiName` | `area.c` name replacement loop | Mapped; local-area top-status Luigi smoke. Pending Time Up/Game Over player-selection routes. |
| `WarpZoneNumbers` | `area.c` selector-four-to-six patch source | Mapped; local-area smoke checks all three selector table routes. Pending source-reachable original-ROM warp route. |
| `GameTextOffsets` | local PRG offset selection in `area.c` | Mapped; local-area selector smoke. Pending direct table-byte audit. |
| `WriteGameText` | `area.c` text writer | Mapped; local-area, Time Up, intermediate, Game Over routes. Pending complete selector matrix. |
| `Chk2Players` | `area.c` selector two/three offset choice | Mapped; source review only. Pending two-player routes. |
| `LdGameText` | `area.c` PRG source selection | Mapped; local-area selector routes. Pending table-byte audit. |
| `GameTextLoop` | `area.c` terminator-copy loop | Mapped; local-area smoke. Pending maximum-length boundary audit. |
| `EndGameText` | `area.c` terminator/tail dispatch | Mapped; local-area lives/name/warp smoke. Pending full selector matrix. |
| `PutLives` | `area.c` lives/world/level patch | Mapped; local-area ordinary/crown smoke and ordinary `PlayerInter` ROM fixture. Pending full selector/name matrix. |
| `CheckPlayerName` | `area.c` player-name selection | Mapped; top-status Luigi smoke. Pending Time Up inversion and Game Over non-inversion routes. |
| `ChkLuigi` | `area.c` current-player branch | Mapped; top-status Luigi smoke. Pending Time Up/Game Over routes. |
| `NameLoop` | `area.c` five-byte Luigi replacement | Mapped; top-status Luigi smoke. Pending direct five-byte source audit. |
| `ExitChkName` | `area.c` name tail exit | Mapped; local-area smoke. Pending selector matrix. |
| `PrintWarpZoneNumbers` | `area.c` selector-four-to-six patch | Mapped; local-area smoke checks selectors four, five and six. Pending source-reachable original-ROM warp route. |
| `WarpNumLoop` | `area.c` three spaced writes | Mapped; local-area smoke checks selectors four, five and six. Pending source-reachable original-ROM warp route. |
| `ResetSpritesAndScreenTimer` | `game.c` tasks 5 and 7 -> `boot.c` sprite hide | Mapped; `t27-screen-reset-pending` and `t27-screen-reset-expired` zero-difference routes. Pending task-seven and common-tail matrix. |
| `ResetScreenTimer` | `game.c` OutputInter and tasks 5/7 | Mapped; Time Up and intermediate routes. Pending common-tail matrix. |
| `NoReset` | `game.c` tasks 5/7 timer-nonzero branch | Mapped; `t27-screen-reset-pending` zero-difference route. Pending task-seven matrix. |
