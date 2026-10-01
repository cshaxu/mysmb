# M2 T53: Cohort A current-equivalence proof
## Task contract
T53 is the first source-order task in the fresh current-equivalence proof program. It audits the original reset/NMI/title/demo/victory/floatey cohort as four bounded, contiguous chains. The historical migration ledger remains **1,992 / 1,992**; T53 makes no new historical-credit forecast. It records fresh current-build dispositions in `M2_CURRENT_EQUIVALENCE` only after both ROM-logic and operational evidence.
Scope: **97 labels** (46 currently `exact`, 51 `needs-evidence`), **185 internal Cohort-A feasible control edges** (73 `exact`, 112 `needs-evidence`), and **6 internal material edges** (4 `exact`, 2 `needs-evidence`). The four chain interiors contain 182 edges; three inter-S handoffs form the T53 cross-chain matrix. The 62 A-to-other-cohort control interfaces and 11 A-to-other-cohort material interfaces are explicit dependency boundaries; T69 owns their final cross-cohort integration proof. All gameplay work stays in `src/game`; adapters only submit input, time and frames.
## Planned bounded S chains
| S | ROM lines | Chain / shared owner | Labels | Internal control / material relations | ROM route and operational focused tests |
| --- | ---: | --- | ---: | --- | --- |
| S1 | 699–981 | `Start` -> `SprInitLoop`, covering reset and the complete NMI/pause/timer/LFSR/sprite/OAM/dispatcher root; `src/game/boot.c` and `src/game/frame_root.c` as the shared reset/NMI root | 39 (22 exact, 17 pending) | 75 (36 exact, 39 pending) / 3 (3 exact, 0 pending) | Owner-ROM controlled reset and NMI records: cold/warm boot, display-disabled/enabled, buffer selector 0/6, timer branches, pause/unpaused, Sprite0 disabled/enabled, all four mode selectors. Operational: mysmb.nmi-parent-integration; mysmb.timer-root-smoke; mysmb.sprite-root-smoke; mysmb.sprite-shuffle-smoke; mysmb.joypad-vram-chain-smoke; mysmb.vram-address-table-smoke. |
| S2 | 982–1136 | `TitleScreenMode` -> `DemoOver`, including title menu, world select, icon and demo; `src/game/title_modes.c` plus `frame_root.c` title dispatch | 26 (21 exact, 5 pending) | 45 (33 exact, 12 pending) / 1 (0 exact, 1 pending) | Owner-ROM title route matrix: start, select/B world choice, demo timer zero/nonzero, continue/world-one and demo end. Operational: mysmb.title-demo-smoke; mysmb.core-smoke. |
| S3 | 1137–1286 | `VictoryMode` -> `EndExitTwo`, including automatic player, messages and world exit; `src/game/terminal_modes.c` plus `frame_root.c` victory tail | 22 (0 exact, 22 pending) | 44 (0 exact, 44 pending) / 0 (0 exact, 0 pending) | Owner-ROM victory task matrix for tasks 0-4, message counters and end-world B-button branches. Operational: mysmb.endgame-objects-smoke; mysmb.bowser-smoke; mysmb.core-smoke. |
| S4 | 1287–1385 | `FloateyNumTileData` -> `SetupNumSpr`; `src/game/objects.c` | 10 (3 exact, 7 pending) | 18 (3 exact, 15 pending) / 2 (1 exact, 1 pending) | Owner-ROM floatey-number timer, score-table, tall-enemy and two-sprite output matrix. Operational: mysmb.floatey-oam-smoke; mysmb.core-smoke. |

S1 is active. S2–S4 remain planned only; no later S is active or has node custody transferred. Each S preserves individual label/edge disposition despite using one chain route and one artifact pass.
## T53 S1 admission: reset/NMI through operating-mode dispatch
S1 enters at `Start` and exits after the `OperModeExecutionTree` selection boundary / `SkipMainOper` RTI tail, retaining the OAM loop label at the source-order end. It includes reset, pause, timer, LFSR, sprite-zero, OAM-offscreen, sprite-shuffle and dispatcher labels because they form the source reset/NMI root. Its direct callees `InitScroll`, `UpdateScreen`, `SoundEngine`, `ReadJoypads`, `UpdateTopScore`, `JumpEngine`, and the four mode leaves remain external dependency boundaries and are not promoted by this S.
The ROM-logic track performs a static label and edge review, then uses controlled owner-local ROM reset/NMI captures for cold/warm boot, both display-mask branches, both buffer offsets, timer paths, pause gate, sprite-zero off/on and every mode selector. It compares call order, branch predicates, RAM writes, OAM effects, scroll/control phase and selector outcome against fresh x86/x64 records. The operational track runs the named focused checks, both Win32 builds/self-tests, the common-source OpenNT DOS16 link, platform-purity audit and refreshes the three ignored local artifacts once for the completed P. Raw ROM traces stay under `build/m2-t53-s1/`.
Historical completion is already 1,992, so `expectedMatches` is intentionally empty. Current-exact promotions are not historical credit and will be enumerated by label in the S closure.
## Exact inventory-label plan

| ROM line | Label | S | Incoming current state | Shared C counterpart |
| ---: | --- | --- | --- | --- |
| 699 | `Start` | S1 | exact | src/game/boot.c:mysmb_game_power_on |
| 706 | `VBlank1` | S1 | exact | src/game/boot.c:mysmb_game_power_on (host timing boundary pending) |
| 708 | `VBlank2` | S1 | exact | src/game/boot.c:mysmb_game_power_on (host timing boundary pending) |
| 712 | `WBootCheck` | S1 | exact | src/game/boot.c:mysmb_game_reset |
| 721 | `ColdBoot` | S1 | exact | src/game/boot.c:mysmb_game_reset |
| 737 | `EndlessLoop` | S1 | exact | src/game/boot.c:mysmb_game_reset -> shared NMI tick boundary |
| 743 | `VRAM_AddrTable_Low` | S1 | exact | src/game/frame_root.c:mysmb_vram_address_low |
| 752 | `VRAM_AddrTable_High` | S1 | exact | src/game/frame_root.c:mysmb_vram_address_high |
| 761 | `VRAM_Buffer_Offset` | S1 | exact | src/game/frame_root.c:mysmb_game_commit_vram_buffer selector branch |
| 764 | `NonMaskableInterrupt` | S1 | exact | src/game/frame_root.c:mysmb_frame_root_begin / mysmb_frame_root_step |
| 776 | `ScreenOff` | S1 | needs-evidence | mysmb_game_commit_display_state |
| 796 | `InitBuffer` | S1 | needs-evidence | mysmb_game_commit_vram_buffer and mysmb_frame_root_begin |
| 814 | `DecTimers` | S1 | exact | mysmb_game_tick_player_timers |
| 820 | `DecTimersLoop` | S1 | exact | mysmb_game_tick_player_timers descending loop |
| 823 | `SkipExpTimer` | S1 | exact | mysmb_game_tick_player_timers descending loop |
| 825 | `NoDecTimers` | S1 | exact | mysmb_frame_root_begin |
| 826 | `PauseSkip` | S1 | needs-evidence | mysmb_frame_root_begin |
| 837 | `RotPRandomBit` | S1 | exact | src/game/frame_root.c:mysmb_game_rotate_pseudorandom |
| 843 | `Sprite0Clr` | S1 | needs-evidence | mysmb_frame_root_begin sprite-zero branch |
| 851 | `Sprite0Hit` | S1 | needs-evidence | mysmb_frame_root_begin / shared frame output state |
| 855 | `HBlankDelay` | S1 | needs-evidence | mysmb_frame_root_begin / renderer frame boundary |
| 857 | `SkipSprite0` | S1 | exact | src/game/frame_root.c:mysmb_frame_root_commit_scene_scroll and mysmb_frame_root_step |
| 868 | `SkipMainOper` | S1 | needs-evidence | mysmb_frame_root_restore_nmi_control / mysmb_frame_root_step / title world-select template |
| 876 | `PauseRoutine` | S1 | exact | mysmb_frame_root_pause_step |
| 885 | `ChkPauseTimer` | S1 | exact | mysmb_frame_root_pause_step |
| 889 | `ChkStart` | S1 | exact | mysmb_frame_root_pause_step |
| 904 | `ClrPauseTimer` | S1 | exact | mysmb_frame_root_pause_step |
| 906 | `SetPause` | S1 | exact | mysmb_frame_root_pause_step |
| 907 | `ExitPause` | S1 | exact | mysmb_frame_root_pause_step return |
| 912 | `SpriteShuffler` | S1 | needs-evidence | mysmb_game_shuffle_sprite_offsets |
| 917 | `ShuffleLoop` | S1 | needs-evidence | mysmb_game_shuffle_sprite_offsets first loop |
| 926 | `StrSprOffset` | S1 | needs-evidence | mysmb_game_shuffle_sprite_offsets first loop store |
| 927 | `NextSprOffset` | S1 | needs-evidence | mysmb_game_shuffle_sprite_offsets loop/index transition |
| 934 | `SetAmtOffset` | S1 | needs-evidence | mysmb_game_shuffle_sprite_offsets |
| 937 | `SetMiscOffset` | S1 | needs-evidence | mysmb_game_shuffle_sprite_offsets misc-offset loop |
| 954 | `OperModeExecutionTree` | S1 | needs-evidence | mysmb_frame_root_step mode_before selector |
| 965 | `MoveAllSpritesOffscreen` | S1 | needs-evidence | mysmb_game_reset OAM clear and mysmb_frame_root_begin sprite-zero path |
| 969 | `MoveSpritesOffscreen` | S1 | needs-evidence | mysmb_frame_root_begin sprite-zero branch |
| 972 | `SprInitLoop` | S1 | needs-evidence | shared OAM Y-byte loop |
| 982 | `TitleScreenMode` | S2 | needs-evidence | mysmb_frame_root_step title mode/task dispatch |
| 993 | `WSelectBufferTemplate` | S2 | needs-evidence | mysmb_frame_root_restore_nmi_control / mysmb_frame_root_step / title world-select template |
| 996 | `GameMenuRoutine` | S2 | needs-evidence | mysmb_game_title_step |
| 1004 | `StartGame` | S2 | exact | mysmb_game_start_from_title |
| 1005 | `ChkSelect` | S2 | exact | mysmb_game_title_step |
| 1013 | `ChkWorldSel` | S2 | exact | mysmb_game_title_step |
| 1018 | `SelectBLogic` | S2 | needs-evidence | mysmb_game_title_step |
| 1033 | `IncWorldSel` | S2 | exact | mysmb_game_title_step |
| 1039 | `UpdateShroom` | S2 | exact | mysmb_game_title_step template loop |
| 1047 | `NullJoypad` | S2 | exact | mysmb_game_title_step |
| 1049 | `RunDemo` | S2 | needs-evidence | mysmb_frame_root_restore_nmi_control / mysmb_frame_root_step / title world-select template |
| 1053 | `ResetTitle` | S2 | exact | mysmb_game_reset_title |
| 1059 | `ChkContinue` | S2 | exact | mysmb_game_chk_continue |
| 1065 | `StartWorld1` | S2 | exact | mysmb_game_start_world1 |
| 1077 | `InitScores` | S2 | exact | mysmb_game_init_scores |
| 1080 | `ExitMenu` | S2 | exact | mysmb_game_exit_menu |
| 1081 | `GoContinue` | S2 | exact | mysmb_game_go_continue |
| 1090 | `MushroomIconData` | S2 | exact | mysmb_game_draw_mushroom_icon |
| 1093 | `DrawMushroomIcon` | S2 | exact | mysmb_game_draw_mushroom_icon |
| 1095 | `IconDataRead` | S2 | exact | mysmb_game_draw_mushroom_icon |
| 1105 | `ExitIcon` | S2 | exact | mysmb_game_draw_mushroom_icon |
| 1109 | `DemoActionData` | S2 | exact | mysmb_game_step_title_demo |
| 1114 | `DemoTimingData` | S2 | exact | mysmb_game_step_title_demo |
| 1119 | `DemoEngine` | S2 | exact | mysmb_game_step_title_demo |
| 1129 | `DoAction` | S2 | exact | mysmb_game_step_title_demo |
| 1133 | `DemoOver` | S2 | exact | mysmb_game_step_title_demo |
| 1137 | `VictoryMode` | S3 | needs-evidence | src/game/frame_root.c:mysmb_frame_root_step victory branch plus src/game/terminal_modes.c:mysmb_game_step_victory |
| 1144 | `AutoPlayer` | S3 | needs-evidence | src/game/frame_root.c:mysmb_frame_root_step victory tail |
| 1147 | `VictoryModeSubroutines` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory OperMode_Task selector |
| 1159 | `SetupVictoryMode` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 1 branch |
| 1169 | `PlayerVictoryWalk` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 2 branch |
| 1178 | `PerformWalk` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 2 walk predicate |
| 1180 | `DontWalk` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 2 AutoControlPlayer/scroll continuation |
| 1195 | `ExitVWalk` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 2 terminal condition |
| 1201 | `PrintVictoryMessages` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1215 | `MRetainerMsg` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1217 | `ThankPlayer` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1223 | `SecondPartMsg` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1232 | `EvalForMusic` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1236 | `PrintMsg` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1240 | `IncMsgCounter` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1248 | `SetEndTimer` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1251 | `IncModeTask_A` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1252 | `ExitMsgs` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1256 | `PlayerEndWorld` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory final PlayerEndWorld branch |
| 1271 | `EndExitOne` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory final PlayerEndWorld branch |
| 1272 | `EndChkBButton` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory final PlayerEndWorld branch |
| 1281 | `EndExitTwo` | S3 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory final PlayerEndWorld branch |
| 1287 | `FloateyNumTileData` | S4 | needs-evidence | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1303 | `ScoreUpdateData` | S4 | needs-evidence | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1308 | `FloateyNumbersRoutine` | S4 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1315 | `ChkNumTimer` | S4 | needs-evidence | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1320 | `DecNumTimer` | S4 | exact | src/game/objects.c:mysmb_objects_step_floatey_number timer/score section |
| 1328 | `LoadNumTiles` | S4 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1338 | `ChkTallEnemy` | S4 | needs-evidence | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1355 | `GetAltOffset` | S4 | needs-evidence | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1358 | `FloateyPart` | S4 | needs-evidence | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1363 | `SetupNumSpr` | S4 | needs-evidence | src/game/objects.c:mysmb_objects_step_floatey_number |

## Relation allocation
T53 owns the 185 internal Cohort-A relations. S1 owns 75 reset/NMI/dispatcher interior relations; S2 owns 45 title/demo relations; S3 owns 44 victory relations; S4 owns 18 floatey relations. The three inter-S relations are checked at their receiving-chain entry and recorded once in the T53 cross-chain matrix. Cross-cohort relations stay for T69.
## Closure standard
T53 closes only after every 97 label and 185 internal control relation has a current disposition, every required material relation is disposed, S closures list each label as exact/mismatch/deferred, and the task-level matrix proves the four handoffs. A mismatch becomes a later unnumbered queue candidate grouped by its smallest shared-owner chain; no repair is smuggled into this audit.
