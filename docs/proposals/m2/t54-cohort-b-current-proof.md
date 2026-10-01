# M2 T54: Cohort B current-equivalence proof

## Task contract

T54 continues the approved source-order re-audit after T53 closure. It covers the ROM screen-task, HUD and game-text cohort at lines 1386–1813. Historical conformance remains **1,992 / 1,992**. Its sole outcome is a current ROM/C disposition for each listed label, feasible control relation and material handoff; any feasible mismatch remains in its admitting S for repair and repeat audit before the next S is admitted. All game decisions remain in shared `src/game`; platform adapters only submit input/time and consume frames.

## Planned bounded S chains

| S | Entry → exit / shared owner | Labels | Route family |
| --- | --- | ---: | --- |
| S1 | `InitScreen` → `NoAltPal`; `game.c` plus `area.c` palette queue | 20 | screen task 0/1/9/10/11 and palette selector matrix |
| S2 | `WriteTopStatusLine` → `NoInter`; `game.c` screen-task branches | 9 | top/bottom status, Time Up and intermediate/Game Over branches |
| S3 | `DrawTitleScreen` → `IncModeTask_B`; `game.c` title-screen tasks | 8 | tasks 12–14 and title drawing/clear/address variants |
| S4 | `GameText` → `WarpNumLoop`; `area.c` text owner | 23 | status/lives/two-player/warp text selector and patch matrix |
| S5 | `ResetSpritesAndScreenTimer` → `NoReset`; `game.c` reset leaves | 3 | task-five/task-seven timer zero and nonzero variants |
| S6 | `AreaParserTaskControl` → `OutputCol`; `area.c` parser handoff | 3 | parser task loop and VRAM selector output |
| S7 | `ScreenRoutines`; `game.c` screen-task dispatcher | 1 | all validated task-vector targets and returns after S1–S6 |

S1 is now admitted. Its 20 labels contain three already current-exact labels (`GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`) and 17 `needs-evidence` labels; its historical-credit forecast is zero. S2–S7 are planned boundaries only. S7 is deliberately last because its source dispatch needs its preceding target chains to be proven first.

## Exact node allocation

| ROM line | Label | S | Incoming current state | Shared C counterpart |
| ---: | --- | --- | --- | --- |
| 1386 | `ScreenRoutines` | S7 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine ScreenRoutineTask switch |
| 1408 | `InitScreen` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 0 |
| 1418 | `SetupIntermediate` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 1 |
| 1436 | `AreaPalette` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 9 AreaType + 1 selector |
| 1439 | `GetAreaPalette` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 9 |
| 1442 | `SetVRAMAddr_A` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine cases 0 and 9 selector write |
| 1443 | `NextSubtask` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine task handoff |
| 1448 | `BGColorCtrl_Addr` | S1 | needs-evidence | src/game/game.c:background_controls[4] in case 10 |
| 1451 | `BackgroundColors` | S1 | needs-evidence | src/game/area.c:mysmb_area_queue_player_palette background-index lookup |
| 1455 | `PlayerColors` | S1 | needs-evidence | src/game/area.c:mysmb_area_queue_player_palette player color lookup |
| 1460 | `GetBackgroundColor` | S1 | exact | src/game/game.c:mysmb_game_step_screen_routine case 10 |
| 1465 | `NoBGColor` | S1 | exact | src/game/game.c:mysmb_game_step_screen_routine case 10 |
| 1467 | `GetPlayerColors` | S1 | exact | src/game/area.c:mysmb_area_queue_player_palette |
| 1473 | `ChkFiery` | S1 | needs-evidence | src/game/area.c:mysmb_area_queue_player_palette PlayerStatus color_offset selection |
| 1477 | `StartClrGet` | S1 | needs-evidence | src/game/area.c:mysmb_area_queue_player_palette four ordered color writes |
| 1479 | `ClrGetLoop` | S1 | needs-evidence | src/game/area.c:mysmb_area_queue_player_palette ordered palette stores |
| 1489 | `SetBGColor` | S1 | needs-evidence | src/game/area.c:mysmb_area_queue_player_palette background_index selection |
| 1502 | `SetVRAMOffset` | S1 | needs-evidence | src/game/area.c:mysmb_area_queue_player_palette offset update |
| 1507 | `GetAlternatePalette1` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 11 |
| 1512 | `SetVRAMAddr_B` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 11 address-control write |
| 1513 | `NoAltPal` | S1 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 11 task increment |
| 1517 | `WriteTopStatusLine` | S2 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 2 |
| 1524 | `WriteBottomStatusLine` | S2 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 3 |
| 1553 | `DisplayTimeUp` | S2 | exact | src/game/game.c:mysmb_game_step_screen_routine case 4 |
| 1560 | `NoTimeUp` | S2 | exact | src/game/game.c:mysmb_game_step_screen_routine case 4 non-expired path |
| 1565 | `DisplayIntermediate` | S2 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 6 |
| 1577 | `PlayerInter` | S2 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 6 player-intermediate path |
| 1579 | `OutputInter` | S2 | exact | src/game/game.c:mysmb_game_step_screen_routine cases 4 and 6 output sequence |
| 1584 | `GameOverInter` | S2 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 6 game-over path |
| 1589 | `NoInter` | S2 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 6 skip path |
| 1595 | `AreaParserTaskControl` | S6 | needs-evidence | src/game/area.c:mysmb_area_parser_task_control |
| 1597 | `TaskLoop` | S6 | needs-evidence | src/game/area.c:mysmb_area_parser_task_control parser loop |
| 1603 | `OutputCol` | S6 | needs-evidence | src/game/area.c:mysmb_area_parser_task_control VRAM selector write |
| 1612 | `DrawTitleScreen` | S3 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 12 |
| 1624 | `OutputTScr` | S3 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 12 title-data copy loop |
| 1629 | `ChkHiByte` | S3 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 12 fixed-size copy bound |
| 1639 | `ClearBuffersDrawIcon` | S3 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 13 |
| 1643 | `TScrClear` | S3 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 13 buffer clear loop |
| 1648 | `IncSubtask` | S3 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine task increments |
| 1653 | `WriteTopScore` | S3 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine case 14 |
| 1656 | `IncModeTask_B` | S3 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine OperMode_Task handoffs |
| 1661 | `GameText` | S4 | needs-evidence | mysmb_area_queue_game_text ROM-authored stream base |
| 1662 | `TopStatusBarLine` | S4 | needs-evidence | mysmb_area_queue_game_text selector 0 |
| 1671 | `WorldLivesDisplay` | S4 | needs-evidence | mysmb_area_queue_game_text selector 1 |
| 1680 | `TwoPlayerTimeUp` | S4 | needs-evidence | mysmb_area_queue_game_text selector 2 two-player stream |
| 1682 | `OnePlayerTimeUp` | S4 | needs-evidence | mysmb_area_queue_game_text selector 2 one-player stream |
| 1686 | `TwoPlayerGameOver` | S4 | needs-evidence | mysmb_area_queue_game_text selector 3 two-player stream |
| 1688 | `OnePlayerGameOver` | S4 | needs-evidence | mysmb_area_queue_game_text selector 3 one-player stream |
| 1693 | `WarpZoneWelcome` | S4 | needs-evidence | mysmb_area_queue_game_text selectors 4-6 |
| 1704 | `LuigiName` | S4 | needs-evidence | mysmb_area_queue_game_text five-byte replacement copy |
| 1707 | `WarpZoneNumbers` | S4 | needs-evidence | mysmb_area_queue_game_text warp-number copy |
| 1712 | `GameTextOffsets` | S4 | needs-evidence | mysmb_area_queue_game_text offset_index selection |
| 1719 | `WriteGameText` | S4 | needs-evidence | mysmb_area_queue_game_text |
| 1728 | `Chk2Players` | S4 | needs-evidence | mysmb_area_queue_game_text selector < 4 player-count branch |
| 1731 | `LdGameText` | S4 | needs-evidence | mysmb_area_queue_game_text stream source selection |
| 1733 | `GameTextLoop` | S4 | needs-evidence | mysmb_area_queue_game_text terminator copy loop |
| 1740 | `EndGameText` | S4 | needs-evidence | mysmb_area_queue_game_text post-copy dispatch |
| 1756 | `PutLives` | S4 | needs-evidence | mysmb_area_queue_game_text selector 1 patch |
| 1765 | `CheckPlayerName` | S4 | needs-evidence | mysmb_area_queue_game_text player-name branch |
| 1775 | `ChkLuigi` | S4 | needs-evidence | mysmb_area_queue_game_text name_player branch |
| 1778 | `NameLoop` | S4 | needs-evidence | mysmb_area_queue_game_text Luigi replacement loop |
| 1782 | `ExitChkName` | S4 | needs-evidence | mysmb_area_queue_game_text completion |
| 1784 | `PrintWarpZoneNumbers` | S4 | needs-evidence | mysmb_area_queue_game_text selector >= 4 patch |
| 1790 | `WarpNumLoop` | S4 | needs-evidence | mysmb_area_queue_game_text warp number loop |
| 1804 | `ResetSpritesAndScreenTimer` | S5 | needs-evidence | src/game/game.c:mysmb_game_step_screen_routine cases 5 and 7 |
| 1809 | `ResetScreenTimer` | S5 | needs-evidence | mysmb_game_step_screen_routine timer reset paths |
| 1813 | `NoReset` | S5 | needs-evidence | mysmb_game_step_screen_routine cases 5 and 7 no-reset paths |

## T54 closure standard

T54 closes only after all 67 labels and its allocated feasible relations have fresh static and controlled ROM/native evidence, each S records its individual zero-difference result or transfer, and the task-level screen/HUD/text route matrix is exact. A build or visible screen alone is not ROM equivalence evidence.

## S1 admission — screen initialization and palette chain

S1 begins at `InitScreen` because `ScreenRoutines` is a multi-target dispatcher whose complete proof belongs to S7 after its children. It compares the original task-byte writes, palette table indexing, player/background selection, queued VRAM output and call/return order at ROM lines 1408–1513. Its ROM route uses controlled task 0/1/9/10/11 snapshots with palette/player-status alternatives; its operational lane uses focused screen/palette checks, x86/x64 builds, the common-source DOS16 link and platform-purity audit. A feasible difference is repaired in `src/game` and this same S is repeated to zero.

## S1 closure — zero feasible difference

All 20 S1 labels are now current-exact. The static pass compared ROM lines
1408–1513 with `mysmb_game_step_screen_routine` and
`mysmb_area_queue_player_palette`, including table order, predicates,
read/write order and the palette-command byte protocol. The controlled
original-ROM routes covered task 0/1, all four `AreaType` table entries,
`BackgroundColorCtrl` 0/4/5/6/7, Mario/Luigi/fire palette selection, and both
alternate-palette paths. Current x86 and x64 match in S1-owned work RAM,
CIRAM, palette, OAM and PPU scalar outputs; `$0778/$0779` remain the
established PPU-shadow ABI exclusion, with physical PPU scalars compared.

The task-11 route is checked at its task boundary. Its next-frame title data
transfer belongs to S3, so it is not inferred as S1 evidence. Focused
screen-status and local-area checks pass on x86/x64; the shared DOS16 link and
platform-purity check pass. This is a test-evidence-only P: no shared product
or platform source changed, so no product artifact refresh is required.

## S2 admission — status and intermediate chain

S2 starts after the closed S1 palette chain and owns nine labels in ROM source
order: `WriteTopStatusLine`, `WriteBottomStatusLine`, `DisplayTimeUp`,
`NoTimeUp`, `DisplayIntermediate`, `PlayerInter`, `OutputInter`,
`GameOverInter` and `NoInter`. Three are already current-exact
(`DisplayTimeUp`, `NoTimeUp`, `OutputInter`); the remaining six require fresh
current evidence. The chain is bounded at the task-two entry and the task-eight
or mode-task exit, with controlled title/game/expired/normal/intermediate
branch routes. It does not claim the dispatcher vector, text-stream internals
or later parser/title tasks. Historical accounting remains 1,992/1,992, so the
expected historical delta is zero.
## S2 closure — status and intermediate chain

S2 closes with no remaining feasible difference in its nine labels. The audit
found one shared-C mismatch in `GameOverInter`: ROM `IncModeTask_B` increments
the current `OperMode_Task`; the former C path wrote the literal value two.
`src/game/game.c` now increments that byte, and the focused regression starts
from `$37` and requires `$38` with the ROM timer value `$12`.

Static review covered ROM lines 1517–1591, including status-text/number
handoffs, the Time Up latch, title/game-over/alternate/castle/disable branches,
player OAM draw before text output, timer and disable-screen ordering, and
mode-task continuation. All nine labels are current-exact. The 25 source-owned
control relations `control-00220` through `control-00238` and
`control-03519` through `control-03524` are exact; no S2 material relation was
introduced. Dispatcher vector edges remain S7 scope and text/status callee
internals remain with their separately admitted chains.

Controlled original-ROM/current x86/x64 routes cover top/bottom status,
expired and non-expired Time Up, castle and ordinary player intermediate,
Game Over and alternate-entry NoInter. Each route has zero persistent-RAM
difference after the established CPU incidental exclusions (zero-page, stack,
and PPU shadows `$0778/$0779`), zero CIRAM/palette/OAM/physical-PPU/audio
output difference, and byte-identical x86/x64 native output. Focused
screen-status and local-area tests pass on both widths; the common DOS16 link
and platform-purity audit pass. Because the shared game C changed, all three
local target artifacts were refreshed. The registry advances from 122 to 128
exact labels and from 253 to 277 exact feasible control relations; historical
conformance remains 1,992 / 1,992.
## S3 admission — title-screen task chain

S3 is admitted only after S2's zero-difference closure. It owns the contiguous
ROM task-12 through task-14 chain: `DrawTitleScreen`, `OutputTScr`,
`ChkHiByte`, `ClearBuffersDrawIcon`, `TScrClear`, `IncSubtask`,
`WriteTopScore` and `IncModeTask_B`. All eight enter as `needs-evidence`; it
claims no historical credit and therefore has an expected historical delta of
zero. The route matrix covers title and non-title task-12/13 exits, the title
copy-bound path, title buffer clear/icon handoff and task-14 top-score/mode-task
continuation. Its source-owned control edges include the external icon and
status helpers only as call/return integration edges; their internal logic
remains in the owning S.

## S3 closure — title-screen task chain

S3 closes with no feasible remaining difference in `DrawTitleScreen`,
`OutputTScr`, `ChkHiByte`, `ClearBuffersDrawIcon`, `TScrClear`, `IncSubtask`,
`WriteTopScore` and `IncModeTask_B`. The audit found and repaired four shared
C control-flow differences: non-title task 12 and task 13 had assigned the
literal mode subtask two instead of taking `IncModeTask_B`; task 14 had both
skipped its unconditional `UpdateNumber($fa)` call outside title mode and
assigned rather than incremented the mode subtask.

The repeat source audit compares ROM lines 1612–1657 with the shared task
switch. It proves the task-12 `$013a` copy into `$0300..$0439`, the task-13
zero fill of both `$0300..$03ff` and `$0400..$04ff` pages before the icon
call, the icon and status helper call/return handoffs, and all mode/screen
counter exits. The sixteen source-owned control relations `control-00244`
through `control-00257`, `control-03526` and `control-03527` are exact.

Controlled title task-12/13/14 owner-local recorder fixtures execute through
the ordinary frame dispatcher in current x86/x64. Their source-owned task and
Buffer1 outcomes agree; recorder cold-start differences in CPU temporary
state and the pre-existing title scene are explicit comparison exclusions,
not outputs of this chain. Focused screen-status checks pass on x86 and x64,
Win32 self-tests pass, the shared OpenNT DOS16 link succeeds, and the platform
purity audit passes. Product code changed, so all three local artifacts were
refreshed: `mysmb16.exe` SHA-256
`60379847F75E83A57046EE69C3F691EE17BF6A466AB292867613E134C37762C8`,
`mysmb32.exe` SHA-256
`7E19E14F15D7B5DD67E58C44F39B639972D24280072491F1D1845F0F135128DA`,
and `mysmb64.exe` SHA-256
`E433DEE110D8BF3661A1E6638820081ADED4DBA151E39F6A9D34957BEE2EE75C`.
Historical conformance remains 1,992 / 1,992. The current-equivalence
registry advances from 128 to 136 exact nodes and from 277 to 293 exact
feasible control relations.
