# M2 T15 S1 title and terminal-mode label map

Scope is SMBDIS lines 844-1124 plus the FloateyNumbers entry at 1148. This is
a code-owner and controller-edge audit. `translated` means the documented
owner exists; it does not replace S2�S4 route comparison.

| ROM label | C owner | Status | S2 consequence |
|---|---|---|---|
| `TitleScreenMode` | `frame_root.c:mysmb_frame_root_step` | translated dispatch | retain mode/task gate |
| `InitializeGame` | `title_modes.c:mysmb_game_begin_title_bootstrap` | translated bootstrap phase | trace against first title NMI |
| `GameMenuRoutine` | `title_modes.c:mysmb_game_title_step` | translated | one ROM-order menu routine |
| `StartGame`, `ChkContinue`, `StartWorld1`, `GoContinue` | `title_modes.c:mysmb_game_start_from_title` | translated for controller one | retain exact Start and A+Start equality |
| `ChkSelect`, `SelectBLogic` | `title_modes.c:mysmb_game_title_step` | translated | exact Select/B debounce, icon, and reset route |
| `IncWorldSel`, `UpdateShroom` | `title_modes.c:mysmb_game_title_step` | translated | ROM template writes from the post-increment index |
| `NullJoypad` | `title_modes.c:mysmb_game_title_step` | translated | preserve clearing before demo/game core |
| `DemoEngine` | `title_modes.c:mysmb_game_step_title_demo` | translated | preserve table index/timer/carry terminal condition |
| `ResetTitle` | `title_modes.c:mysmb_game_title_step` | translated | preserve mode, task, sprite-zero, screen-disable writes |
| `VictoryMode` | `frame_root.c` + `terminal_modes.c:mysmb_game_step_victory` | translated structure | S3 verifies task-zero object exclusion |
| `VictoryModeSubroutines` | `terminal_modes.c:mysmb_game_step_victory` | translated structure | S3 verifies each task transition |
| `SetupVictoryMode`, `PlayerVictoryWalk` | `terminal_modes.c:mysmb_game_step_victory` + `player.c` | translated scroll route | S3 P2 maps auto-control and forced-scroll order |
| `PrintVictoryMessages` | `terminal_modes.c:mysmb_game_print_victory_messages` | translated | S3 compares text/music/timer branches |
| `PlayerEndWorld` | `terminal_modes.c:mysmb_game_step_victory` | translated structure | S3 verifies world-8 B path |
| `FloateyNumbersRoutine` | `objects.c:mysmb_objects_step_floatey_number` | translated | preserve game-engine call ordering |
| `GameOverMode` | `frame_root.c` + `terminal_modes.c:mysmb_game_step_game_over` | translated structure | S4 traces start/timer/player transpose route |

## Controller-edge contract

The shared NMI latch supplies one controller-one byte. Title menu compares the
whole byte exactly: `Start` (`$10`) and `A|Start` (`$90`) start a game;
`Select` (`$20`) toggles players only while `DemoTimer != 0` and `SelectTimer
== 0`; demo input replaces the latched byte only after the demo timer expires.
The native product has no second controller device, so `SavedJoypad2Bits` is
fixed zero rather than emulated by platform policy.

## S1 disposition

S1 is complete. S2 owns the menu route comparison and the existing
bootstrap/menu branch consolidation. It must not alter terminal-mode code.

## S1 P1 artifact record

This mapping changed no runtime source. The three executable artifacts associated
with S1 P1 were `mysmb16.exe`
`51bc5c0052aa9f06365866e71b1ce6e38bc3a6ec7cd9039775d2cda7349d0f65`,
`mysmb32.exe`
`b667f36dbb772273a218ab59f1be48591398056f575c50e245d4c6a567b482d2`, and
`mysmb64.exe`
`a6360868dd9e7377aae666f13684a6b3b17243873f125eb7091be2107c6c19ae`.

## S2 P2 menu-route migration

GameMenuRoutine now follows the ROM labels ChkSelect, ChkWorldSel, SelectBLogic, IncWorldSel, UpdateShroom, NullJoypad, RunDemo, and ResetTitle in one title-mode owner. DrawMushroomIcon is also owned by that module and is invoked by ScreenRoutines only as its original caller. Focused tests assert the source bytes and state transitions; both Windows widths pass 78/78, and OpenNT links the same source.

## Module-boundary gate before further terminal logic changes

The current C tree is deliberately aligned to the admitted ROM slices:

| Owner | Admitted responsibility | Forbidden responsibility |
| --- | --- | --- |
| boot.c, frame_root.c | reset/NMI order, input latch, timer bank, PPU commit, operation-mode dispatch | title/menu, terminal-mode, actor or host-window decisions |
| title_modes.c | lines 982-1136 title, selection, demo and title bootstrap leaves | victory/game-over, screen-task implementation or platform input |
| terminal_modes.c | lines 1137-1385 victory, end-world, life-loss, game-over and their area-pointer transitions | frame scheduling, object-loop execution or host presentation |
| game.c | currently admitted shared setup, timer and parser hand-off leaves; screen/task code remains reserved for the next Screen/text/status T | title and terminal decisions |
| objects.c | actor/object leaves; FloateyNumbersRoutine stays here because GameEngine calls it per enemy slot | operation-mode dispatch or platform output |
| src/platform/** | physical input to mysmb_input, pacing and submission of a completed shared frame | RAM state writes, mode/task decisions, collision, scroll, text/HUD or OAM construction |

Future extraction occurs only when its owning ROM slice is admitted as a T task. A repair inside a current slice may not use game.c or a platform adapter as a convenience owner.
