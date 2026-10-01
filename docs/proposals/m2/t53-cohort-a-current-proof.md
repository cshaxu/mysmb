# M2 T53: Cohort A current-equivalence proof
## Task contract
T53 is the first source-order task in the fresh current-equivalence proof program. It audits the original reset/NMI/title/demo/victory/floatey cohort as bounded, contiguous chains. The historical migration ledger remains **1,992 / 1,992**; T53 makes no new historical-credit forecast. It records fresh current-build dispositions in `M2_CURRENT_EQUIVALENCE` only after both ROM-logic and operational evidence. A feasible mismatch is repaired and re-audited to zero before a successor chain advances.
Scope: **97 labels** (46 currently `exact`, 51 `needs-evidence`), **185 internal Cohort-A feasible control edges** (73 `exact`, 112 `needs-evidence`), and **6 internal material edges** (4 `exact`, 2 `needs-evidence`). The four chain interiors contain 182 edges; three inter-S handoffs form the T53 cross-chain matrix. The 62 A-to-other-cohort control interfaces and 11 A-to-other-cohort material interfaces are explicit dependency boundaries; T69 owns their final cross-cohort integration proof. All gameplay work stays in `src/game`; adapters only submit input, time and frames.
## Planned bounded S chains
| S | ROM lines | Chain / shared owner | Labels | Internal control / material relations | ROM route and operational focused tests |
| --- | ---: | --- | ---: | --- | --- |
| S1 | 699–981 | `Start` -> `SprInitLoop`, covering reset and the complete NMI/pause/timer/LFSR/sprite/OAM/dispatcher root; `src/game/boot.c` and `src/game/frame_root.c` as the shared reset/NMI root | 39 (22 exact, 17 pending) | 75 (36 exact, 39 pending) / 3 (3 exact, 0 pending) | Owner-ROM controlled reset and NMI records: cold/warm boot, display-disabled/enabled, buffer selector 0/6, timer branches, pause/unpaused, Sprite0 disabled/enabled, all four mode selectors. Operational: mysmb.nmi-parent-integration; mysmb.timer-root-smoke; mysmb.sprite-root-smoke; mysmb.sprite-shuffle-smoke; mysmb.joypad-vram-chain-smoke; mysmb.vram-address-table-smoke. |
| S2 | 982–1136 | `TitleScreenMode` -> `DemoOver`, including title menu, world select, icon and demo; `src/game/title_modes.c` plus `frame_root.c` title dispatch | 26 (21 exact, 5 pending) | 45 (33 exact, 12 pending) / 1 (0 exact, 1 pending) | Owner-ROM title route matrix: start, select/B world choice, demo timer zero/nonzero, continue/world-one and demo end. Operational: mysmb.title-demo-smoke; mysmb.core-smoke. |
| S3 | 776–814 | `ScreenOff` corrective display-mask -> scroll/OAM/VRAM transaction order; `src/game/frame_root.c` | 1 (0 exact, 1 mismatch) | 4 (0 exact, 4 mismatch) / 0 | Controlled display-disabled/enabled original-ROM NMI records; focused NMI-parent check; x86/x64/DOS16 build and platform purity. |
| S4 | 1137–1286 | `VictoryMode` -> `EndExitTwo`, including automatic player, messages and world exit; `src/game/terminal_modes.c` plus `frame_root.c` victory tail | 22 (0 exact, 22 pending) | 44 (0 exact, 44 pending) / 0 (0 exact, 0 pending) | Owner-ROM victory task matrix for tasks 0-4, message counters and end-world B-button branches. Operational: mysmb.endgame-objects-smoke; mysmb.bowser-smoke; mysmb.core-smoke. |
| S5 | 1287–1385 | `FloateyNumTileData` -> `SetupNumSpr`; `src/game/objects.c` | 10 (10 exact) | 25 incident controls (25 exact) / 1 material (1 exact) | Owner-ROM floatey-number timer, score-table, tall-enemy and two-sprite output matrix. Operational: mysmb.floatey-oam-smoke; mysmb.core-smoke. |

S1's mismatch was resolved by S3 at zero scoped differences. S5 is the active floatey-number audit. Each S preserves individual label/edge disposition despite using one chain route and one artifact pass.
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
| 1137 | `VictoryMode` | S4 | needs-evidence | src/game/frame_root.c:mysmb_frame_root_step victory branch plus src/game/terminal_modes.c:mysmb_game_step_victory |
| 1144 | `AutoPlayer` | S4 | needs-evidence | src/game/frame_root.c:mysmb_frame_root_step victory tail |
| 1147 | `VictoryModeSubroutines` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory OperMode_Task selector |
| 1159 | `SetupVictoryMode` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 1 branch |
| 1169 | `PlayerVictoryWalk` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 2 branch |
| 1178 | `PerformWalk` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 2 walk predicate |
| 1180 | `DontWalk` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 2 AutoControlPlayer/scroll continuation |
| 1195 | `ExitVWalk` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory task == 2 terminal condition |
| 1201 | `PrintVictoryMessages` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1215 | `MRetainerMsg` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1217 | `ThankPlayer` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1223 | `SecondPartMsg` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1232 | `EvalForMusic` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1236 | `PrintMsg` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1240 | `IncMsgCounter` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1248 | `SetEndTimer` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1251 | `IncModeTask_A` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1252 | `ExitMsgs` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_print_victory_messages |
| 1256 | `PlayerEndWorld` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory final PlayerEndWorld branch |
| 1271 | `EndExitOne` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory final PlayerEndWorld branch |
| 1272 | `EndChkBButton` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory final PlayerEndWorld branch |
| 1281 | `EndExitTwo` | S4 | needs-evidence | src/game/terminal_modes.c:mysmb_game_step_victory final PlayerEndWorld branch |
| 1287 | `FloateyNumTileData` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1303 | `ScoreUpdateData` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1308 | `FloateyNumbersRoutine` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1315 | `ChkNumTimer` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1320 | `DecNumTimer` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number timer/score section |
| 1328 | `LoadNumTiles` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1338 | `ChkTallEnemy` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1355 | `GetAltOffset` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1358 | `FloateyPart` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |
| 1363 | `SetupNumSpr` | S5 | exact | src/game/objects.c:mysmb_objects_step_floatey_number |

## Relation allocation
T53 owns the 185 internal Cohort-A relations. S1 owns 75 reset/NMI/dispatcher interior relations; S2 owns 45 title/demo relations; S4 owns 44 victory relations; S5 owns 18 floatey relations. S3 owns the separately recorded four-relation `ScreenOff` corrective transaction. The three inter-S relations are checked at their receiving-chain entry and recorded once in the T53 cross-chain matrix. Cross-cohort relations stay for T69.
## Closure standard
T53 closes only after every 97 label and 185 internal control relation has a current disposition, every required material relation is disposed, S closures list each label as exact/mismatch/deferred, and the task-level matrix proves the four handoffs. A mismatch becomes a later unnumbered queue candidate grouped by its smallest shared-owner chain; no repair is smuggled into this audit.

## S1 closure ? reset/NMI through operating-mode dispatch

S1 closed with no historical-credit change: historical progress remains 1,992 / 1,992. Its 39 current nodes are individually disposed as 38 exact and one mismatch (`ScreenOff`). All 75 internal control relations are disposed as 74 exact and `control-00076` infeasible. The four display-transaction mismatch relations are external to the S1 interior and remain the unnumbered shared-frame-root repair candidate. Owner-ROM four-vector and 600-frame pause/sprite routes, focused root tests, registry validation and platform-purity validation supplied the two evidence tracks. Raw traces were deleted after neutral summaries were recorded.

## S2 initial graph finding

`control-00081` and `control-03497` are raw extractor relations, not executable title paths. The source at line 984 calls `JumpEngine`; lines 2395-2408 remove that call's return address and indirect-jump through the inline vector words. The ROM therefore cannot fall into `WSelectBufferTemplate` or return from `JumpEngine` to `TitleScreenMode`. Both records remain in the raw ledger with an `infeasible` disposition. The executable title dispatch and menu routes remain open until controlled original-ROM/native route records establish their state and output contracts.


## S2 closure — title/menu/world-select/icon/demo chain

S2 closed with no historical-credit change: historical progress remains 1,992 / 1,992. All 26 scoped current nodes are exact. The executable source-range relations are 52 exact, and `control-00081` plus `control-03497` are infeasible JumpEngine extractor records. The title material edge `material-k39-01` is exact: the six `WSelectBufferTemplate` bytes are copied in source order before the world-digit overwrite.

The ROM-logic evidence is six fresh 600-frame routes: natural idle/demo, Select, enabled-world-select B, Start, A+Start, and expired Select. For every route, the original ROM matches current x86 and x64 in work RAM `$0200-$07ff` except `$0778/$0779`, both CIRAM pages, palette, OAM, audio and PPU scalars; x86 and x64 records are byte-identical. Focused title-data and title-demo smoke checks also pass. Raw traces were deleted after the neutral route summary was created under the ignored build tree.

## S3 amendment — `ScreenOff` corrective loop

S1 found `ScreenOff` and four display transaction relations mismatched: the shared frame root committed VRAM before applying the temporary source display mask, while ROM NMI writes that mask first, then resets scroll, performs OAM DMA and updates VRAM. Under the owner rule, this cannot remain a queued candidate while later chains advance. `ScreenOff` transfers from its historical receiver to S3; S3 changes only the shared ordering, rebuilds all three targets, and repeats the static and controlled original-ROM NMI audit until the node and four relations are exact. The already gathered victory-route diagnostics are not a closure or an S4 admission.

## S3 corrective result

`mysmb_frame_root_begin` now calls `mysmb_game_commit_display_state` before
`mysmb_game_commit_vram_buffer`, matching ROM NMI's `ScreenOff` transaction
order. `ScreenOff` and all four recorded transaction edges are exact after
the source review and focused x86/x64 NMI-parent checks. The shared C90 source
also links into the DOS16 executable. Refreshed local artifacts are
`mysmb16.exe` `43A24D06A260C6E9B88B6E6E2E007B8DB3896F0E5E5381C75957A04EB16639DE`,
`mysmb32.exe` `D2A45B26EF817484B50F806011301FE39FD6ACE1CB0DC807EB7F513093AA5FBB`,
and `mysmb64.exe` `E8ED41F9E2E370E6DF7A602839599020AE80B7A7EEF0ABAC31BC78E5240EA222`.

## S3 closure — `ScreenOff` corrective transaction

S3 closed with no historical-credit change: historical progress remains 1,992 / 1,992. The shared frame root now applies the temporary display mask before the scroll/OAM/VRAM transaction, matching ROM NMI lines 764–814. `ScreenOff` and `control-00018`, `control-00019`, `control-03487`, and `control-03488` are current-exact after static source-order review and controlled owner-local NMI evidence. Focused x86/x64 NMI-parent checks pass; the same C90 source links for DOS16; all three ignored local executable artifacts were refreshed. No current mismatch remains, so the next source-order chain may be admitted separately.

## S4 admission — victory chain

S4 enters at `VictoryMode` and exits at `EndExitTwo`. Its 22 exact inventory labels are audited in source order with a zero historical-credit forecast. It first compares each ROM branch, selector, RAM/table access, call/return edge and output ordering to `terminal_modes.c` and the frame-root tail. It then runs the controlled victory task, message-counter and end-world B-button route matrix against current x86/x64. Any feasible discrepancy remains in S4, is repaired in the shared owner, and is re-audited before S5 can be admitted.

## S4 closure — victory chain

S4 closed with no historical-credit change: historical progress remains 1,992 / 1,992. All 22 scoped labels and 65 incident executable control relations are current-exact; the 44 interior relations remain separately identifiable within that set. Source review covers every selector, branch predicate, counter/table operation, call/return and end-world controller branch at ROM lines 1137–1281. Fifteen controlled owner-local routes, each with a 60-frame warmup and eight captured frames, match x86 and x64 against the original ROM in work RAM `$0200-$07ff` except `$0778/$0779`, CIRAM, palette, OAM, PPU scalars and audio; the two native recordings are byte-identical. Current x64 focused bowser, endgame-object, mode and victory-message checks pass. No product source changed during S4, so no artifact refresh was required.

## S5 admission — floatey-number chain

S5 enters at `FloateyNumTileData` and exits at `SetupNumSpr`, covering ten labels in the same shared `objects.c` owner chain. It audits timer-zero and decrement paths, score-table selection, tall-enemy alternate sprite offset, and all two-sprite OAM output relations against controlled original-ROM/x86/x64 records. Any feasible difference is repaired in the shared game owner and re-audited to zero before a successor chain is admitted.

## S5 active finding — tall-enemy OAM-group branch

The current-source review found a feasible shared-C mismatch in the
`ChkTallEnemy -> GetAltOffset` family. ROM lines 1338–1357 preserve the
ordinary `Enemy_SprDataOffset` for Spiny (`$05`), Piranha Plant (`$0d`) and
both Cheep-Cheep IDs (`$0a/$0b`); they select `Alt_SprDataOffset` immediately
for Hammer Bro (`$09`) and every ID at or above `TallEnemy` (`$12`), and use
enemy state only for the remaining ordinary IDs. The prior collapsed C
predicate selected the alternate group for Spiny and omitted the immediate
Hammer Bro/large-enemy cases.

`src/game/objects.c` now follows those source branches in that order. The
focused `mysmb.floatey-oam-smoke` cases cover Hammer Bro, a `TallEnemy`-range
ID, Spiny, the timer `$2b` award path, a non-award decrement, timer zero,
control clamping, both vertical-coordinate paths and the two-sprite tile/OAM
tail. This is a repair-in-progress record, not an exact promotion: S5 still
must complete its source/edge matrix and controlled ROM/native route evidence
before any registry row or successor admission changes.

### P1 repair and re-audit record

The shared branch repair was re-read against ROM lines 1287–1378. The static
review found no remaining difference in the ten scoped labels, the 25
incident control relations, or the `FloateyNumTileData -> SetupNumSpr`
material lookup: the clamp, zero-timer return, pre-decrement `$2b` test,
score-table nibble update, score-call continuation, six ID/state OAM-group
outcomes, vertical carry semantics, and both OAM sprite writes all have the
source-order counterpart in `objects.c`. This static result is deliberately
kept separate from a current-route promotion.

Operationally, `mysmb.floatey-oam-smoke` passed from the rebuilt x86 and x64
shared source sets, the DOS16 OpenNT large-model link produced an MZ image,
and `test_platform_purity.py` passed. Local artifacts were refreshed after
the product change: `mysmb16.exe` SHA-256
`78D9F77D405307E53F5F11526AB028ABAA9F481CD1A95F754CF5DDEA1419EF57`,
`mysmb32.exe` SHA-256
`8172842C63151D6D3021D19FCE831ECB4A36DE66877DE0971309EBD1997AF75D`, and
`mysmb64.exe` SHA-256
`15087A3913DC1F8323577EA923659F1AF8C31068EFC6383584A33EC6EB8EF6B4`.
The recorder was then rebuilt from its current source and the controlled original-ROM route was repeated. The three fixtures—one-up, timer-zero and numeric-alt—each used a 60-frame warmup plus eight captured frames. Original ROM, current x86 and current x64 match exactly in work RAM `$0200-$07ff` excluding `$0778/$0779`, CIRAM, palette, OAM, PPU scalars and audio; x86 and x64 records are byte-identical. Raw diagnostic records are deleted after the neutral route summary.

## S5 closure — floatey-number chain

S5 closes with no historical-credit change: historical progress remains 1,992 / 1,992. All ten scoped labels—`FloateyNumTileData`, `ScoreUpdateData`, `FloateyNumbersRoutine`, `ChkNumTimer`, `DecNumTimer`, `LoadNumTiles`, `ChkTallEnemy`, `GetAltOffset`, `FloateyPart`, and `SetupNumSpr`—are current-exact. All 25 scoped incident executable control relations (`control-00172` through `control-00192`, `control-00777`, `control-03513`, `control-03514`, and `control-03620`) and material relation `material-00005` are current-exact. The only found ROM/C mismatch, the tall-enemy OAM-group selector, was repaired in the shared game owner and re-audited to zero. The focused OAM regression passes on x86/x64; the shared C90 source links for DOS16; platform-purity passes; and the three local artifacts were refreshed. No scoped difference remains, so only now may the next source-order chain be admitted.
