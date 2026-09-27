# M2 ROM conformance node progress

The [canonical inventory](../etc/architecture/smb1-rom-migration-inventory.md)
contains 1,992 unique original label nodes. This is conformance accounting,
not a percentage estimate of implemented gameplay.

Current receiving S and historical T/S relations are in the
[node/task ledger](NODE_TASK_LEDGER.md). Ownership registration does not change
the conformance counts below.

## Current baseline

| ROM-match state | Nodes | Named source |
| --- | ---: | --- |
| ROM-match complete | 336 | PlayerOffscreenChk, PROfsLoop, NPROffscr, RenderAreaGraphics, DrawMTLoop, RightCheck, LLeft, NextMTRow, SetAttrib, ExitDrawM, RenderAttributeTables, SetATHigh, AttribLoop, SetVRAMCtrl, MetatileGraphics_Low, MetatileGraphics_High, ColorRotatePalette, BlankPalette, Palette3Data, ColorRotation, GetBlankPal, GetAreaPal, ExitColorRot, BlockGfxData, RemoveCoin_Axe, WriteBlankMT, ReplaceBlockMetatile, DestroyBlockMetatile, WriteBlockMetatile, UseBOffset, MoveVOffset, PutBlockMetatile, SaveHAdder, RemBridge, Palette0_MTiles, Palette1_MTiles, Palette2_MTiles, Palette3_MTiles, WaterPaletteData, GroundPaletteData, UndergroundPaletteData, CastlePaletteData, DaySnowPaletteData, NightSnowPaletteData, MushroomPaletteData, BowserPaletteData, MarioThanksMessage, LuigiThanksMessage, MushroomRetainerSaved, PrincessSaved1, PrincessSaved2, WorldSelectMessage1, WorldSelectMessage2, JumpEngine, InitializeNameTables, WriteNTAddr, InitNTLoop, InitATLoop, ScreenOff, Start, VBlank1, VBlank2, WBootCheck, ColdBoot, EndlessLoop, InitializeMemory, VRAM_AddrTable_Low, VRAM_AddrTable_High, VRAM_Buffer_Offset, InitBuffer, PauseRoutine, ChkPauseTimer, ChkStart, ClrPauseTimer, SetPause, ExitPause, VictoryMode, AutoPlayer, TitleScreenMode, GameMenuRoutine, NullJoypad, RunDemo, ResetTitle, StartGame, ChkContinue, StartWorld1, InitScores, ExitMenu, GoContinue, WSelectBufferTemplate, MushroomIconData, DrawMushroomIcon, IconDataRead, ExitIcon, DemoActionData, DemoTimingData, DemoEngine, DoAction, DemoOver, InitScreen, SetupIntermediate, AreaPalette, GetAreaPalette, SetVRAMAddr_A, NextSubtask, BGColorCtrl_Addr, BackgroundColors, PlayerColors, GetBackgroundColor, NoBGColor, GetPlayerColors, ChkFiery, StartClrGet, ClrGetLoop, SetBGColor, SetVRAMOffset, GetAlternatePalette1, SetVRAMAddr_B, NoAltPal, WriteBottomStatusLine, WriteTopScore, WarpZoneWelcome, WarpZoneNumbers, WriteGameText, EndGameText, PrintStatusBarNumbers, PrintWarpZoneNumbers, WarpNumLoop, ReadJoypads, ReadPortBits, PortLoop, Save8Bits, WriteBufferToScreen, SetupWrites, GetLength, OutputToVRAM, RepeatByte, UpdateScreen, InitScroll, WritePPUReg1, MusicSelectData, GetAreaMusic, ChkAreaType, StoreMusic, ExitGetM, PlayerStarting_X_Pos, AltYPosOffset, PlayerStarting_Y_Pos, PlayerBGPriorityData, GameTimerData, Entrance_GameTimerSetup, ChkStPos, SetStPos, ChkOverR, ChkSwimE, SetPESub, HalfwayPageNybbles, PlayerLoseLife, StillInGame, GetHalfway, MaskHPNyb, SetHalfway, GameOverMode, SetupGameOver, RunGameOver, TerminateGame, ContinueGame, GameIsOn, TransposePlayers, TransLoop, ExTrans, DoNothing1, DoNothing2, AreaParserTaskHandler, DoAPTasks, SkipATRender, AreaParserTasks, IncrementColumnPos, NoColWrap, BSceneDataOffsets, BackSceneryData, BackSceneryMetatiles, FSceneDataOffsets, ForeSceneryData, TerrainMetatiles, TerrainRenderBits, AreaParserCore. |
| Mapped / audited, not complete | 106 | Exact names below: 18 known mismatches, 3 missing implementations, 2 changed-body revalidations, 54 audited evidence gaps, and 29 mapped evidence gaps. |
| Open / unmatched | 1,550 | Exact open rows in the inventory; responsibility/evidence gaps are now linked individually. Open does not mean unimplemented. |
| **Total** | **1,992** | Unique label/source-line pairs. |

Verified conformance is **336 / 1,992 (16.87%)**. The 106 incomplete mappings comprise 18 known mismatches, three known missing implementations, two changed-body revalidations, 54 audited evidence gaps, and 29 mapped evidence gaps. These categories are disjoint.

The owner expanded scope to all integrated nodes and all prior T/S responsibilities.
The [full evidence census](../etc/architecture/m2-t24-s1-full-node-census.md)
checks all 1,992 labels for historical scope, C references, source address,
test linkage and route execution. It records all gaps; it does **not** claim a
full semantic audit of every implementation. Its 435 exact C-name references
and 857 executed ROM code labels are separate evidence dimensions, not counts
of equivalent native nodes. No product repair is part of this audit.

## Completed matches


| ROM line | Node |
| ---: | --- |
| 699 | `Start` |
| 706 | `VBlank1` |
| 708 | `VBlank2` |
| 712 | `WBootCheck` |
| 721 | `ColdBoot` |
| 737 | `EndlessLoop` |
| 743 | `VRAM_AddrTable_Low` |
| 752 | `VRAM_AddrTable_High` |
| 761 | `VRAM_Buffer_Offset` |
| 776 | `ScreenOff` |
| 796 | `InitBuffer` |
| 814 | `DecTimers` |
| 820 | `DecTimersLoop` |
| 823 | `SkipExpTimer` |
| 825 | `NoDecTimers` |
| 826 | `PauseSkip` |
| 837 | `RotPRandomBit` |
| 843 | `Sprite0Clr` |
| 851 | `Sprite0Hit` |
| 855 | `HBlankDelay` |
| 857 | `SkipSprite0` |
| 868 | `SkipMainOper` |
| 876 | `PauseRoutine` |
| 885 | `ChkPauseTimer` |
| 889 | `ChkStart` |
| 904 | `ClrPauseTimer` |
| 906 | `SetPause` |
| 907 | `ExitPause` |
| 912 | `SpriteShuffler` |
| 917 | `ShuffleLoop` |
| 926 | `StrSprOffset` |
| 927 | `NextSprOffset` |
| 934 | `SetAmtOffset` |
| 937 | `SetMiscOffset` |
| 954 | `OperModeExecutionTree` |
| 965 | `MoveAllSpritesOffscreen` |
| 969 | `MoveSpritesOffscreen` |
| 972 | `SprInitLoop` |
| 982 | `TitleScreenMode` |
| 993 | `WSelectBufferTemplate` |
| 996 | `GameMenuRoutine` |
| 1004 | `StartGame` |
| 1005 | `ChkSelect` |
| 1013 | `ChkWorldSel` |
| 1018 | `SelectBLogic` |
| 1033 | `IncWorldSel` |
| 1039 | `UpdateShroom` |
| 1047 | `NullJoypad` |
| 1049 | `RunDemo` |
| 1053 | `ResetTitle` |
| 1059 | `ChkContinue` |
| 1065 | `StartWorld1` |
| 1077 | `InitScores` |
| 1080 | `ExitMenu` |
| 1081 | `GoContinue` |
| 1090 | `MushroomIconData` |
| 1093 | `DrawMushroomIcon` |
| 1095 | `IconDataRead` |
| 1105 | `ExitIcon` |
| 1109 | `DemoActionData` |
| 1114 | `DemoTimingData` |
| 1119 | `DemoEngine` |
| 1129 | `DoAction` |
| 1133 | `DemoOver` |
| 1137 | `VictoryMode` |
| 1144 | `AutoPlayer` |
| 1147 | `VictoryModeSubroutines` |
| 1159 | `SetupVictoryMode` |
| 1169 | `PlayerVictoryWalk` |
| 1178 | `PerformWalk` |
| 1180 | `DontWalk` |
| 1195 | `ExitVWalk` |
| 1201 | `PrintVictoryMessages` |
| 1215 | `MRetainerMsg` |
| 1217 | `ThankPlayer` |
| 1223 | `SecondPartMsg` |
| 1232 | `EvalForMusic` |
| 1236 | `PrintMsg` |
| 1240 | `IncMsgCounter` |
| 1248 | `SetEndTimer` |
| 1251 | `IncModeTask_A` |
| 1252 | `ExitMsgs` |
| 1256 | `PlayerEndWorld` |
| 1271 | `EndExitOne` |
| 1272 | `EndChkBButton` |
| 1281 | `EndExitTwo` |
| 1287 | `FloateyNumTileData` |
| 1303 | `ScoreUpdateData` |
| 1308 | `FloateyNumbersRoutine` |
| 1315 | `ChkNumTimer` |
| 1320 | `DecNumTimer` |
| 1328 | `LoadNumTiles` |
| 1338 | `ChkTallEnemy` |
| 1355 | `GetAltOffset` |
| 1358 | `FloateyPart` |
| 1363 | `SetupNumSpr` |
| 1408 | `InitScreen` |
| 1418 | `SetupIntermediate` |
| 1436 | `AreaPalette` |
| 1439 | `GetAreaPalette` |
| 1442 | `SetVRAMAddr_A` |
| 1443 | `NextSubtask` |
| 1448 | `BGColorCtrl_Addr` |
| 1451 | `BackgroundColors` |
| 1455 | `PlayerColors` |
| 1460 | `GetBackgroundColor` |
| 1465 | `NoBGColor` |
| 1467 | `GetPlayerColors` |
| 1473 | `ChkFiery` |
| 1477 | `StartClrGet` |
| 1479 | `ClrGetLoop` |
| 1489 | `SetBGColor` |
| 1502 | `SetVRAMOffset` |
| 1507 | `GetAlternatePalette1` |
| 1512 | `SetVRAMAddr_B` |
| 1513 | `NoAltPal` |
| 1517 | `WriteTopStatusLine` |
| 1524 | `WriteBottomStatusLine` |
| 1553 | `DisplayTimeUp` |
| 1560 | `NoTimeUp` |
| 1565 | `DisplayIntermediate` |
| 1577 | `PlayerInter` |
| 1579 | `OutputInter` |
| 1584 | `GameOverInter` |
| 1589 | `NoInter` |
| 1612 | `DrawTitleScreen` |
| 1624 | `OutputTScr` |
| 1629 | `ChkHiByte` |
| 1639 | `ClearBuffersDrawIcon` |
| 1643 | `TScrClear` |
| 1648 | `IncSubtask` |
| 1653 | `WriteTopScore` |
| 1656 | `IncModeTask_B` |
| 1661 | `GameText` |
| 1662 | `TopStatusBarLine` |
| 1671 | `WorldLivesDisplay` |
| 1680 | `TwoPlayerTimeUp` |
| 1682 | `OnePlayerTimeUp` |
| 1686 | `TwoPlayerGameOver` |
| 1688 | `OnePlayerGameOver` |
| 1693 | `WarpZoneWelcome` |
| 1704 | `LuigiName` |
| 1707 | `WarpZoneNumbers` |
| 1712 | `GameTextOffsets` |
| 1719 | `WriteGameText` |
| 1728 | `Chk2Players` |
| 1731 | `LdGameText` |
| 1733 | `GameTextLoop` |
| 1740 | `EndGameText` |
| 1756 | `PutLives` |
| 1765 | `CheckPlayerName` |
| 1775 | `ChkLuigi` |
| 1778 | `NameLoop` |
| 1782 | `ExitChkName` |
| 1784 | `PrintWarpZoneNumbers` |
| 1790 | `WarpNumLoop` |
| 1804 | `ResetSpritesAndScreenTimer` |
| 1809 | `ResetScreenTimer` |
| 1813 | `NoReset` |
| 1825 | `RenderAreaGraphics` |
| 1840 | `DrawMTLoop` |
| 1878 | `RightCheck` |
| 1886 | `LLeft` |
| 1888 | `NextMTRow` |
| 1889 | `SetAttrib` |
| 1914 | `ExitDrawM` |
| 1920 | `RenderAttributeTables` |
| 1930 | `SetATHigh` |
| 1940 | `AttribLoop` |
| 1962 | `SetVRAMCtrl` |
| 1970 | `ColorRotatePalette` |
| 1973 | `BlankPalette` |
| 1977 | `Palette3Data` |
| 1983 | `ColorRotation` |
| 1991 | `GetBlankPal` |
| 2004 | `GetAreaPal` |
| 2024 | `ExitColorRot` |
| 2034 | `BlockGfxData` |
| 2041 | `RemoveCoin_Axe` |
| 2047 | `WriteBlankMT` |
| 2052 | `ReplaceBlockMetatile` |
| 2058 | `DestroyBlockMetatile` |
| 2061 | `WriteBlockMetatile` |
| 2076 | `UseBOffset` |
| 2080 | `MoveVOffset` |
| 2086 | `PutBlockMetatile` |
| 2097 | `SaveHAdder` |
| 2118 | `RemBridge` |
| 2145 | `MetatileGraphics_Low` |
| 2148 | `MetatileGraphics_High` |
| 2151 | `Palette0_MTiles` |
| 2192 | `Palette1_MTiles` |
| 2240 | `Palette2_MTiles` |
| 2252 | `Palette3_MTiles` |
| 2263 | `WaterPaletteData` |
| 2275 | `GroundPaletteData` |
| 2287 | `UndergroundPaletteData` |
| 2299 | `CastlePaletteData` |
| 2311 | `DaySnowPaletteData` |
| 2316 | `NightSnowPaletteData` |
| 2321 | `MushroomPaletteData` |
| 2326 | `BowserPaletteData` |
| 2331 | `MarioThanksMessage` |
| 2339 | `LuigiThanksMessage` |
| 2347 | `MushroomRetainerSaved` |
| 2358 | `PrincessSaved1` |
| 2366 | `PrincessSaved2` |
| 2375 | `WorldSelectMessage1` |
| 2382 | `WorldSelectMessage2` |
| 2395 | `JumpEngine` |
| 2412 | `InitializeNameTables` |
| 2421 | `WriteNTAddr` |
| 2427 | `InitNTLoop` |
| 2436 | `InitATLoop` |
| 2446 | `ReadJoypads` |
| 2454 | `ReadPortBits` |
| 2455 | `PortLoop` |
| 2474 | `Save8Bits` |
| 2482 | `WriteBufferToScreen` |
| 2495 | `SetupWrites` |
| 2501 | `GetLength` |
| 2504 | `OutputToVRAM` |
| 2506 | `RepeatByte` |
| 2523 | `UpdateScreen` |
| 2527 | `InitScroll` |
| 2533 | `WritePPUReg1` |
| 2544 | `StatusBarData` |
| 2552 | `StatusBarOffset` |
| 2555 | `PrintStatusBarNumbers` |
| 2564 | `OutputNumbers` |
| 2578 | `SetupNums` |
| 2592 | `DigitPLoop` |
| 2604 | `ExitOutputN` |
| 2608 | `DigitsMathRoutine` |
| 2613 | `AddModLoop` |
| 2619 | `StoreNewD` |
| 2623 | `EraseDMods` |
| 2625 | `EraseMLoop` |
| 2629 | `BorrowOne` |
| 2632 | `CarryOne` |
| 2639 | `UpdateTopScore` |
| 2644 | `TopScoreCheck` |
| 2647 | `GetScoreDiff` |
| 2655 | `CopyScore` |
| 2661 | `NoTopSc` |
| 2665 | `DefaultSprOffsets` |
| 2669 | `Sprite0Data` |
| 2674 | `InitializeGame` |
| 2678 | `ClrSndLoop` |
| 2685 | `InitializeArea` |
| 2690 | `ClrTimersLoop` |
| 2697 | `StartPage` |
| 2705 | `SetInitNTHigh` |
| 2728 | `SetSecHard` |
| 2729 | `CheckHalfway` |
| 2733 | `DoneInitArea` |
| 2742 | `PrimaryGameSetup` |
| 2750 | `SecondaryGameSetup` |
| 2754 | `ClearVRLoop` |
| 2775 | `ShufAmtLoop` |
| 2780 | `ISpr0Loop` |
| 2795 | `InitializeMemory` |
| 2799 | `InitPageLoop` |
| 2800 | `InitByteLoop` |
| 2804 | `InitByte` |
| 2805 | `SkipByte` |
| 2814 | `MusicSelectData` |
| 2818 | `GetAreaMusic` |
| 2830 | `ChkAreaType` |
| 2834 | `StoreMusic` |
| 2836 | `ExitGetM` |
| 2840 | `PlayerStarting_X_Pos` |
| 2844 | `AltYPosOffset` |
| 2847 | `PlayerStarting_Y_Pos` |
| 2851 | `PlayerBGPriorityData` |
| 2854 | `GameTimerData` |
| 2858 | `Entrance_GameTimerSetup` |
| 2874 | `ChkStPos` |
| 2881 | `SetStPos` |
| 2900 | `ChkOverR` |
| 2911 | `ChkSwimE` |
| 2914 | `SetPESub` |
| 2921 | `HalfwayPageNybbles` |
| 2931 | `PlayerLoseLife` |
| 2944 | `StillInGame` |
| 2951 | `GetHalfway` |
| 2960 | `MaskHPNyb` |
| 2965 | `SetHalfway` |
| 2971 | `GameOverMode` |
| 2981 | `SetupGameOver` |
| 2993 | `RunGameOver` |
| 3001 | `TerminateGame` |
| 3015 | `ContinueGame` |
| 3027 | `GameIsOn` |
| 3029 | `TransposePlayers` |
| 3039 | `TransLoop` |
| 3048 | `ExTrans` |
| 3052 | `DoNothing1` |
| 3055 | `DoNothing2` |
| 3060 | `AreaParserTaskHandler` |
| 3065 | `DoAPTasks` |
| 3071 | `SkipATRender` |
| 3073 | `AreaParserTasks` |
| 3087 | `IncrementColumnPos` |
| 3094 | `NoColWrap` |
| 3106 | `BSceneDataOffsets` |
| 3109 | `BackSceneryData` |
| 3131 | `BackSceneryMetatiles` |
| 3145 | `FSceneDataOffsets` |
| 3148 | `ForeSceneryData` |
| 3158 | `TerrainMetatiles` |
| 3161 | `TerrainRenderBits` |
| 3179 | `AreaParserCore` |
| 3184 | `RenderSceneryTerrain` |
| 3187 | `ClrMTBuf` |
| 3193 | `ThirdP` |
| 3198 | `RendBack` |
| 3223 | `SceLoop1` |
| 3231 | `RendFore` |
| 3235 | `SceLoop2` |
| 3238 | `NoFore` |
| 3242 | `RendTerr` |
| 3249 | `TerMTile` |
| 3253 | `StoreMT` |
| 3258 | `TerrLoop` |
| 3269 | `NoCloud2` |
| 3270 | `TerrBChk` |
| 3275 | `NextTBit` |
| 3285 | `EndUChk` |
| 3290 | `RendBBuf` |
| 3295 | `ChkMTLow` |
| 3306 | `StrBlock` |
| 3319 | `BlockBuffLowBounds` |
| 14535 | `PlayerOffscreenChk` |
| 14547 | `PROfsLoop` |
| 14551 | `NPROffscr` |

Each completion links its branch/write, ROM probe and route evidence in the
[77-node audit](../etc/architecture/m2-t24-s1-node-verification.md).

## Accounting audit, 2026-09-26

The interrupted tally used rows rather than unique labels: duplicate open rows
for PlayerHammerCollision, ClHCol and ExPHC inflated 1,992 to 1,995. They were
removed without dropping unique nodes, and malformed evidence cells repaired.
All 1,992 label/line pairs match the hash-pinned listing. The old baseline of
zero complete / 77 mapped was the pre-verification snapshot, not current status.
The subsequent audit found 90 additional historical/current C mappings and three missing entries. Every source
slice and every retained prior M2 history/proposal section was checked for
responsibility evidence; unnamed descendants remain in the full census.

The accounting checker validates row uniqueness, recognized states, aggregate
counts and exact named lists. It does not validate semantics by itself.

## Mapped but not yet matched (106)

| ROM line | Node |
| ---: | --- |
| 764 | `NonMaskableInterrupt` |
| 3737 | `CastleObject` |
| 3991 | `FlagpoleObject` |
| 6298 | `ProcFireball_Bubble` |
| 6352 | `FireballObjCore` |
| 6519 | `ProcessWhirlpools` |
| 6550 | `WhirlpoolActivate` |
| 6604 | `FlagpoleRoutine` |
| 6702 | `Setup_Vine` |
| 6730 | `VineObjectHandler` |
| 6788 | `ProcessCannons` |
| 6849 | `BulletBillHandler` |
| 6928 | `ProcHammerObj` |
| 6988 | `CoinBlock` |
| 7000 | `SetupJumpCoin` |
| 7014 | `JCoinC` |
| 7025 | `FindEmptyMiscSlot` |
| 7038 | `MiscObjectsCore` |
| 7053 | `ProcJumpCoin` |
| 7150 | `SetupPowerUp` |
| 7184 | `PowerUpObjHandler` |
| 7206 | `GrowThePowerUp` |
| 7226 | `RunPUSubs` |
| 7244 | `PlayerHeadCollision` |
| 7316 | `InitBlock_XY_Pos` |
| 7332 | `BumpBlock` |
| 7349 | `BlockCode` |
| 7386 | `BrickQBlockMetatiles` |
| 7393 | `BlockBumpedChk` |
| 7404 | `BrickShatter` |
| 7420 | `CheckTopOfBlock` |
| 7441 | `SpawnBrickChunks` |
| 7468 | `BlockObjectsCore` |
| 7506 | `BouncingBlockHandler` |
| 7527 | `BlockObjMT_Updater` |
| 10509 | `StarFlagExit` |
| 11085 | `FireballEnemyCollision` |
| 11101 | `FireballEnemyCDLoop` |
| 11115 | `GoombaDie` |
| 11120 | `NotGoomba` |
| 11135 | `NoFToECol` |
| 11141 | `ExitFBallEnemy` |
| 11145 | `BowserIdentities` |
| 11148 | `HandleEnemyFBallCol` |
| 11160 | `ChkBuzzyBeetle` |
| 11167 | `HurtBowser` |
| 11182 | `SetDBSte` |
| 11189 | `ChkOtherEnemies` |
| 11197 | `ShellOrBlockDefeat` |
| 11204 | `StnE` |
| 11215 | `GoombaPoints` |
| 11220 | `EnemySmackScore` |
| 11224 | `ExHCF` |
| 11228 | `PlayerHammerCollision` |
| 11256 | `ClHCol` |
| 11258 | `ExPHC` |
| 12805 | `GetFireballBoundBox` |
| 14254 | `DrawFireball` |
| 14283 | `DrawExplosion_Fireball` |
| 14424 | `PlayerGraphicsTable` |
| 14457 | `SwimKickTileNum` |
| 14460 | `PlayerGfxHandler` |
| 14466 | `CntPl` |
| 14489 | `SwimKT` |
| 14495 | `BigKTS` |
| 14497 | `ExPGH` |
| 14499 | `FindPlayerAction` |
| 14503 | `DoChangeSize` |
| 14507 | `PlayerKilled` |
| 14511 | `PlayerGfxProcessing` |
| 14532 | `SUpdR` |
| 14561 | `IntermediatePlayerData` |
| 14564 | `DrawPlayer_Intermediate` |
| 14566 | `PIntLoop` |
| 14587 | `RenderPlayerSub` |
| 14601 | `DrawPlayerLoop` |
| 14610 | `ProcessPlayerAction` |
| 14626 | `ProcOnGroundActs` |
| 14642 | `NonAnimatedActs` |
| 14649 | `ActionFalling` |
| 14654 | `ActionWalkRun` |
| 14659 | `ActionClimbing` |
| 14666 | `ActionSwimming` |
| 14676 | `GetCurrentAnimOffset` |
| 14680 | `FourFrameExtent` |
| 14684 | `ThreeFrameExtent` |
| 14687 | `AnimationControl` |
| 14701 | `SetAnimC` |
| 14702 | `ExAnimC` |
| 14705 | `GetGfxOffsetAdder` |
| 14712 | `SzOfs` |
| 14714 | `ChangeSizeOffsetAdder` |
| 14718 | `HandleChangeSize` |
| 14728 | `CSzNext` |
| 14729 | `GorSLog` |
| 14734 | `GetOffsetFromAnimCtrl` |
| 14741 | `ShrinkPlayer` |
| 14750 | `ShrPlF` |
| 14753 | `ChkForPlayerAttrib` |
| 14767 | `KilledAtt` |
| 14774 | `C_S_IGAtt` |
| 14781 | `ExPlyrAt` |
| 14786 | `RelativePlayerPosition` |
| 14797 | `RelativeFireballPosition` |
| 14846 | `GetPlayerOffscreenBits` |
| 14851 | `GetFireballOffscreenBits` |

## Reporting contract

At **S admission**, the proposal and active packet must state the baseline as ROM-match complete / 1,992, name every inventory label the S may change, state each node's incoming status, identify the exact subset expected to become matches, and declare the maximum expected closing fraction with its focused CTest and original-ROM route baseline. At **S closure**, the closure report must repeat the fraction, name every label whose status changed, link the evidence that allows each changed label to count as a match, and name every deferred label and its owner. No aggregate increase is allowed without matching inventory-row updates. The [node-backfill validation matrix](../etc/architecture/m2-node-backfill-validation-matrix.md) holds the shared retrospective batches and test lanes.

Every M2 P report also retains the existing delivery record: refreshed `assets/mysmb16.exe`, `assets/mysmb32.exe`, and `assets/mysmb64.exe`, their build/validation result, and the ordinary source/evidence/deferred-issue summary. The three executables demonstrate target delivery; they do not replace per-node ROM conformance evidence.
