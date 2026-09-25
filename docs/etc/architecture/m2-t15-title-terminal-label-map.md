# M2 T15 S1 title and terminal-mode label map

Scope is SMBDIS lines 844-1124 plus the FloateyNumbers entry at 1148. This is
a code-owner and controller-edge audit. `translated` means the documented
owner exists; it does not replace S2�S4 route comparison.

| ROM label | C owner | Status | S2 consequence |
|---|---|---|---|
| `TitleScreenMode` | `frame_root.c:mysmb_frame_root_step` | translated dispatch | retain mode/task gate |
| `InitializeGame` | `game.c:mysmb_game_begin_title_bootstrap` | translated bootstrap phase | trace against first title NMI |
| `GameMenuRoutine` | `game.c:mysmb_game_title_step` | partial | replace menu branch as one ROM-order routine |
| `StartGame`, `ChkContinue`, `StartWorld1`, `GoContinue` | `game.c:mysmb_game_start_from_title` | translated for controller one | retain exact Start and A+Start equality |
| `ChkSelect`, `SelectBLogic` | `game.c:mysmb_game_title_step` | partial | Select debounce is present; call `DrawMushroomIcon` is missing |
| `IncWorldSel`, `UpdateShroom` | none | missing | implement world-select B route and VRAM template |
| `NullJoypad` | `game.c:mysmb_game_title_step` | translated | preserve clearing before demo/game core |
| `DemoEngine` | `game.c:mysmb_game_step_title_demo` | translated | preserve table index/timer/carry terminal condition |
| `ResetTitle` | `game.c:mysmb_game_title_step` | translated | preserve mode, task, sprite-zero, screen-disable writes |
| `VictoryMode` | `frame_root.c` + `game.c:mysmb_game_step_victory` | translated structure | S3 verifies task-zero object exclusion |
| `VictoryModeSubroutines` | `game.c:mysmb_game_step_victory` | translated structure | S3 verifies each task transition |
| `SetupVictoryMode`, `PlayerVictoryWalk` | `game.c:mysmb_game_step_victory` + `player.c` | translated structure | S3 traces scroll/auto-control sequence |
| `PrintVictoryMessages` | `game.c:mysmb_game_print_victory_messages` | translated | S3 compares text/music/timer branches |
| `PlayerEndWorld` | `game.c:mysmb_game_step_victory` | translated structure | S3 verifies world-8 B path |
| `FloateyNumbersRoutine` | `objects.c:mysmb_objects_step_floatey_number` | translated | preserve game-engine call ordering |
| `GameOverMode` | `frame_root.c` + `game.c:mysmb_game_step_game_over` | translated structure | S4 traces start/timer/player transpose route |

## Controller-edge contract

The shared NMI latch supplies one controller-one byte. Title menu compares the
whole byte exactly: `Start` (`$10`) and `A|Start` (`$90`) start a game;
`Select` (`$20`) toggles players only while `DemoTimer != 0` and `SelectTimer
== 0`; demo input replaces the latched byte only after the demo timer expires.
The native product has no second controller device, so `SavedJoypad2Bits` is
fixed zero rather than emulated by platform policy.

## S1 disposition

S1 is complete. S2 owns the two identified menu gaps and the existing
bootstrap/menu branch consolidation. It must not alter terminal-mode code.

## S1 P1 artifact record

This mapping changes no runtime source. The three executable artifacts remain the
validated T14 P18 build set: mysmb16.exe SHA-256
51bc5c0052aa9f06365866e71b1ce6e38bc3a6ec7cd9039775d2cda7349d0f65, mysmb32.exe`r
667f36dbb772273a218ab59f1be48591398056f575c50e245d4c6a567b482d2, and
mysmb64.exe 6360868dd9e7377aae666f13684a6b3b17243873f125eb7091be2107c6c19ae.
