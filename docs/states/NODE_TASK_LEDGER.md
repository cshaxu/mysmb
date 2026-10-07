# Node-to-task responsibility ledger

Generated from [NODE_TASK_LEDGER.json](NODE_TASK_LEDGER.json) by
`python tools/node_task_ledger.py --write`. JSON owns responsibility/history;
the [inventory](../etc/architecture/smb1-rom-migration-inventory.md) alone owns
conformance. This view must not be edited independently.

Every node has exactly one receiving S. Receipt is accountable backlog
ownership, not simultaneous active execution or a completion claim. Historical
mentions can overlap; historical T-only records retain an unknown S instead
of inventing one. Future tasks register and accept transfers on admission.
T24 S2 retains explicit custody of closed-root/unallocated candidates until
an admitted successor accepts them; it cannot close with unfinished custody.

## Receiving subtasks

| Receiving S | Exact node count | Exact node set |
| --- | ---: | --- |
| M2 T30 S16 | 6 | `L_CastleArea1`, `L_CastleArea2`, `L_CastleArea3`, `L_CastleArea4`, `L_CastleArea5`, `L_CastleArea6` |
| M2 T30 S17 | 22 | `L_GroundArea1`, `L_GroundArea2`, `L_GroundArea3`, `L_GroundArea4`, `L_GroundArea5`, `L_GroundArea6`, `L_GroundArea7`, `L_GroundArea8`, `L_GroundArea9`, `L_GroundArea10`, `L_GroundArea11`, `L_GroundArea12`, `L_GroundArea13`, `L_GroundArea14`, `L_GroundArea15`, `L_GroundArea16`, `L_GroundArea17`, `L_GroundArea18`, `L_GroundArea19`, `L_GroundArea20`, `L_GroundArea21`, `L_GroundArea22` |
| M2 T30 S18 | 3 | `L_UndergroundArea1`, `L_UndergroundArea2`, `L_UndergroundArea3` |
| M2 T30 S19 | 3 | `L_WaterArea1`, `L_WaterArea2`, `L_WaterArea3` |
| M2 T31 S1 | 1 | `GameCoreRoutine` |
| M2 T31 S2 | 9 | `GameEngine`, `ProcELoop`, `NoChgMus`, `CycleTwo`, `ClrPlrPal`, `SaveAB`, `UpdScrollVar`, `RunParser`, `ExitEng` |
| M2 T31 S4 | 9 | `PlayerEntrance`, `ChkBehPipe`, `IntroEntr`, `EntrMode2`, `VineEntr`, `OffVine`, `PlayerRdy`, `ExitEntr`, `AutoControlPlayer` |
| M2 T70 S17 | 2 | `GameMode`, `GameRoutines` |
| M3 T27 S2 | 14 | `SkipMainOper`, `WSelectBufferTemplate`, `RunDemo`, `VictoryMode`, `ScrollHandler`, `ChkNearMid`, `ScrollScreen`, `InitScrlAmt`, `ChkPOffscr`, `KeepOnscr`, `InitPlatScrl`, `X_SubtracterData`, `OffscrJoypadBitsData`, `GetScreenPosition` |
| M3 T27 S4 | 474 | `Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, `VRAM_AddrTable_Low`, `VRAM_AddrTable_High`, `VRAM_Buffer_Offset`, `NonMaskableInterrupt`, `ScreenOff`, `InitBuffer`, `DecTimers`, `DecTimersLoop`, `SkipExpTimer`, `NoDecTimers`, `PauseSkip`, `RotPRandomBit`, `Sprite0Clr`, `Sprite0Hit`, `HBlankDelay`, `SkipSprite0`, `PauseRoutine`, `ChkPauseTimer`, `ChkStart`, `ClrPauseTimer`, `SetPause`, `ExitPause`, `SpriteShuffler`, `ShuffleLoop`, `StrSprOffset`, `NextSprOffset`, `SetAmtOffset`, `SetMiscOffset`, `OperModeExecutionTree`, `MoveAllSpritesOffscreen`, `MoveSpritesOffscreen`, `SprInitLoop`, `TitleScreenMode`, `GameMenuRoutine`, `StartGame`, `ChkSelect`, `ChkWorldSel`, `SelectBLogic`, `IncWorldSel`, `UpdateShroom`, `NullJoypad`, `ResetTitle`, `ChkContinue`, `StartWorld1`, `InitScores`, `ExitMenu`, `GoContinue`, `MushroomIconData`, `DrawMushroomIcon`, `IconDataRead`, `ExitIcon`, `DemoActionData`, `DemoTimingData`, `DemoEngine`, `DoAction`, `DemoOver`, `AutoPlayer`, `VictoryModeSubroutines`, `SetupVictoryMode`, `PlayerVictoryWalk`, `PerformWalk`, `DontWalk`, `ExitVWalk`, `PrintVictoryMessages`, `MRetainerMsg`, `ThankPlayer`, `SecondPartMsg`, `EvalForMusic`, `PrintMsg`, `IncMsgCounter`, `SetEndTimer`, `IncModeTask_A`, `ExitMsgs`, `PlayerEndWorld`, `EndExitOne`, `EndChkBButton`, `EndExitTwo`, `ScreenRoutines`, `InitScreen`, `SetupIntermediate`, `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal`, `WriteTopStatusLine`, `DisplayTimeUp`, `NoTimeUp`, `DisplayIntermediate`, `PlayerInter`, `OutputInter`, `GameOverInter`, `NoInter`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol`, `DrawTitleScreen`, `OutputTScr`, `ChkHiByte`, `ClearBuffersDrawIcon`, `TScrClear`, `IncSubtask`, `WriteTopScore`, `IncModeTask_B`, `GameText`, `TopStatusBarLine`, `WorldLivesDisplay`, `TwoPlayerTimeUp`, `OnePlayerTimeUp`, `TwoPlayerGameOver`, `OnePlayerGameOver`, `WarpZoneWelcome`, `LuigiName`, `WarpZoneNumbers`, `GameTextOffsets`, `WriteGameText`, `Chk2Players`, `LdGameText`, `GameTextLoop`, `EndGameText`, `PutLives`, `CheckPlayerName`, `ChkLuigi`, `NameLoop`, `ExitChkName`, `PrintWarpZoneNumbers`, `WarpNumLoop`, `ResetSpritesAndScreenTimer`, `ResetScreenTimer`, `NoReset`, `RenderAreaGraphics`, `DrawMTLoop`, `RightCheck`, `LLeft`, `NextMTRow`, `SetAttrib`, `ExitDrawM`, `RenderAttributeTables`, `SetATHigh`, `AttribLoop`, `SetVRAMCtrl`, `ColorRotatePalette`, `BlankPalette`, `Palette3Data`, `ColorRotation`, `GetBlankPal`, `GetAreaPal`, `ExitColorRot`, `BlockGfxData`, `RemoveCoin_Axe`, `WriteBlankMT`, `ReplaceBlockMetatile`, `DestroyBlockMetatile`, `WriteBlockMetatile`, `UseBOffset`, `MoveVOffset`, `PutBlockMetatile`, `SaveHAdder`, `RemBridge`, `MetatileGraphics_Low`, `MetatileGraphics_High`, `Palette0_MTiles`, `Palette1_MTiles`, `Palette2_MTiles`, `Palette3_MTiles`, `WaterPaletteData`, `GroundPaletteData`, `UndergroundPaletteData`, `CastlePaletteData`, `DaySnowPaletteData`, `NightSnowPaletteData`, `MushroomPaletteData`, `BowserPaletteData`, `MarioThanksMessage`, `LuigiThanksMessage`, `MushroomRetainerSaved`, `PrincessSaved1`, `PrincessSaved2`, `WorldSelectMessage1`, `WorldSelectMessage2`, `JumpEngine`, `InitializeNameTables`, `WriteNTAddr`, `InitNTLoop`, `InitATLoop`, `ReadJoypads`, `ReadPortBits`, `PortLoop`, `Save8Bits`, `WriteBufferToScreen`, `SetupWrites`, `GetLength`, `OutputToVRAM`, `RepeatByte`, `UpdateScreen`, `InitScroll`, `WritePPUReg1`, `StatusBarData`, `StatusBarOffset`, `PrintStatusBarNumbers`, `OutputNumbers`, `SetupNums`, `DigitPLoop`, `ExitOutputN`, `DigitsMathRoutine`, `AddModLoop`, `StoreNewD`, `EraseDMods`, `EraseMLoop`, `BorrowOne`, `CarryOne`, `UpdateTopScore`, `TopScoreCheck`, `GetScoreDiff`, `CopyScore`, `NoTopSc`, `DefaultSprOffsets`, `Sprite0Data`, `InitializeGame`, `ClrSndLoop`, `InitializeArea`, `ClrTimersLoop`, `StartPage`, `SetInitNTHigh`, `SetSecHard`, `CheckHalfway`, `DoneInitArea`, `PrimaryGameSetup`, `SecondaryGameSetup`, `ClearVRLoop`, `ShufAmtLoop`, `ISpr0Loop`, `InitializeMemory`, `InitPageLoop`, `InitByteLoop`, `InitByte`, `SkipByte`, `MusicSelectData`, `GetAreaMusic`, `ChkAreaType`, `StoreMusic`, `ExitGetM`, `HalfwayPageNybbles`, `PlayerLoseLife`, `StillInGame`, `GetHalfway`, `MaskHPNyb`, `SetHalfway`, `GameOverMode`, `SetupGameOver`, `RunGameOver`, `TerminateGame`, `ContinueGame`, `GameIsOn`, `TransposePlayers`, `TransLoop`, `ExTrans`, `DoNothing1`, `DoNothing2`, `AreaParserTaskHandler`, `DoAPTasks`, `SkipATRender`, `AreaParserTasks`, `IncrementColumnPos`, `NoColWrap`, `BSceneDataOffsets`, `BackSceneryData`, `BackSceneryMetatiles`, `FSceneDataOffsets`, `ForeSceneryData`, `TerrainMetatiles`, `TerrainRenderBits`, `AreaParserCore`, `RenderSceneryTerrain`, `ClrMTBuf`, `ThirdP`, `RendBack`, `SceLoop1`, `RendFore`, `SceLoop2`, `NoFore`, `RendTerr`, `TerMTile`, `StoreMT`, `TerrLoop`, `NoCloud2`, `TerrBChk`, `NextTBit`, `EndUChk`, `RendBBuf`, `ChkMTLow`, `StrBlock`, `BlockBuffLowBounds`, `ProcessAreaData`, `ProcADLoop`, `Chk1Row13`, `Chk1Row14`, `CheckRear`, `RdyDecode`, `SetBehind`, `NextAObj`, `ChkLength`, `ProcLoopb`, `EndAParse`, `IncAreaObjOffset`, `DecodeAreaData`, `Chk1stB`, `ChkRow14`, `ChkRow13`, `Mask2MSB`, `ChkSRows`, `LrgObj`, `NotWPipe`, `SpecObj`, `MoveAOId`, `NormObj`, `LeavePar`, `InitRear`, `LoopCmdE`, `BackColC`, `StrAObj`, `RunAObj`, `AlterAreaAttributes`, `Alter2`, `SetFore`, `ScrollLockObject_Warp`, `WarpNum`, `ScrollLockObject`, `KillEnemies`, `KillELoop`, `NoKillE`, `FrenzyIDData`, `AreaFrenzy`, `FreCompLoop`, `ExitAFrenzy`, `AreaStyleObject`, `TreeLedge`, `MidTreeL`, `EndTreeL`, `MushroomLedge`, `EndMushL`, `AllUnder`, `NoUnder`, `PulleyRopeMetatiles`, `PulleyRopeObject`, `RenderPul`, `MushLExit`, `CastleMetatiles`, `CastleObject`, `CRendLoop`, `ChkCFloor`, `NotTall`, `PlayerStop`, `ExitCastle`, `WaterPipe`, `IntroPipe`, `VPipeSectLoop`, `NoBlankP`, `SidePipeShaftData`, `SidePipeTopPart`, `SidePipeBottomPart`, `ExitPipe`, `RenderSidewaysPipe`, `DrawSidePart`, `VerticalPipeData`, `VerticalPipe`, `WarpPipe`, `DrawPipe`, `GetPipeHeight`, `FindEmptyEnemySlot`, `EmptyChkLoop`, `ExitEmptyChk`, `Hole_Water`, `QuestionBlockRow_High`, `QuestionBlockRow_Low`, `Bridge_High`, `Bridge_Middle`, `Bridge_Low`, `FlagBalls_Residual`, `EndlessRope`, `BalancePlatRope`, `DrawRope`, `CoinMetatileData`, `RowOfCoins`, `C_ObjectRow`, `C_ObjectMetatile`, `CastleBridgeObj`, `AxeObj`, `ChainObj`, `EmptyBlock`, `ColObj`, `SolidBlockMetatiles`, `BrickMetatiles`, `RowOfBricks`, `DrawBricks`, `RowOfSolidBlocks`, `GetRow`, `DrawRow`, `ColumnOfBricks`, `ColumnOfSolidBlocks`, `GetRow2`, `BulletBillCannon`, `SetupCannon`, `StrCOffset`, `StaircaseHeightData`, `StaircaseRowData`, `StaircaseObject`, `NextStair`, `Jumpspring`, `Hidden1UpBlock`, `QuestionBlock`, `BrickWithCoins`, `BrickWithItem`, `BWithL`, `DrawQBlk`, `GetAreaObjectID`, `ExitDecBlock`, `HoleMetatiles`, `Hole_Empty`, `StrWOffset`, `NoWhirlP`, `RenderUnderPart`, `DrawThisRow`, `WaitOneRow`, `ExitUPartR`, `ChkLrgObjLength`, `ChkLrgObjFixedLength`, `LenSet`, `GetLrgObjAttrib`, `GetAreaObjXPosition`, `GetAreaObjYPosition`, `BlockBufferAddr`, `GetBlockBufferAddr`, `LoadAreaPointer`, `GetAreaType`, `FindAreaPointer`, `GetAreaDataAddrs`, `StoreFore`, `StoreStyle`, `WorldAddrOffsets`, `AreaAddrOffsets`, `World1Areas`, `World2Areas`, `World3Areas`, `World4Areas`, `World5Areas`, `World6Areas`, `World7Areas`, `World8Areas`, `EnemyAddrHOffsets`, `EnemyDataAddrLow`, `EnemyDataAddrHigh`, `AreaDataHOffsets`, `AreaDataAddrLow`, `AreaDataAddrHigh` |
| M3 T27 S5 | 1449 | `FloateyNumTileData`, `ScoreUpdateData`, `FloateyNumbersRoutine`, `ChkNumTimer`, `DecNumTimer`, `LoadNumTiles`, `ChkTallEnemy`, `GetAltOffset`, `FloateyPart`, `SetupNumSpr`, `WriteBottomStatusLine`, `PlayerStarting_X_Pos`, `AltYPosOffset`, `PlayerStarting_Y_Pos`, `PlayerBGPriorityData`, `GameTimerData`, `Entrance_GameTimerSetup`, `ChkStPos`, `SetStPos`, `ChkOverR`, `ChkSwimE`, `SetPESub`, `FlagpoleObject`, `AreaDataOfsLoopback`, `E_CastleArea1`, `E_CastleArea2`, `E_CastleArea3`, `E_CastleArea4`, `E_CastleArea5`, `E_CastleArea6`, `E_GroundArea1`, `E_GroundArea2`, `E_GroundArea3`, `E_GroundArea4`, `E_GroundArea5`, `E_GroundArea6`, `E_GroundArea7`, `E_GroundArea8`, `E_GroundArea9`, `E_GroundArea10`, `E_GroundArea11`, `E_GroundArea12`, `E_GroundArea13`, `E_GroundArea14`, `E_GroundArea15`, `E_GroundArea16`, `E_GroundArea17`, `E_GroundArea18`, `E_GroundArea19`, `E_GroundArea20`, `E_GroundArea21`, `E_GroundArea22`, `E_UndergroundArea1`, `E_UndergroundArea2`, `E_UndergroundArea3`, `E_WaterArea1`, `E_WaterArea2`, `E_WaterArea3`, `PlayerCtrlRoutine`, `DisJoyp`, `SaveJoyp`, `SizeChk`, `ChkMoveDir`, `SetMoveDir`, `PlayerSubs`, `PlayerHole`, `HoleDie`, `HoleBottom`, `ChkHoleX`, `ExitCtrl`, `CloudExit`, `Vine_AutoClimb`, `AutoClimb`, `SetEntr`, `VerticalPipeEntry`, `MovePlayerYAxis`, `SideExitPipeEntry`, `ChgAreaPipe`, `ChgAreaMode`, `ExitCAPipe`, `EnterSidePipe`, `RightPipe`, `PlayerChangeSize`, `EndChgSize`, `ExitChgSize`, `PlayerInjuryBlink`, `ExitBlink`, `InitChangeSize`, `ExitBoth`, `PlayerDeath`, `DonePlayerTask`, `PlayerFireFlower`, `CyclePlayerPalette`, `ResetPalFireFlower`, `ResetPalStar`, `ExitDeath`, `FlagpoleSlide`, `SlidePlayer`, `NoFPObj`, `Hidden1UpCoinAmts`, `PlayerEndLevel`, `ChkStop`, `InCastle`, `RdyNextA`, `NextArea`, `ExitNA`, `PlayerMovementSubs`, `SetCrouch`, `ProcMove`, `MoveSubs`, `NoMoveSub`, `OnGroundStateSub`, `GndMove`, `FallingSub`, `JumpSwimSub`, `DumpFall`, `ProcSwim`, `LRWater`, `LRAir`, `JSMove`, `ExitMov1`, `ClimbAdderLow`, `ClimbAdderHigh`, `ClimbingSub`, `MoveOnVine`, `ClimbFD`, `CSetFDir`, `ExitCSub`, `InitCSTimer`, `JumpMForceData`, `FallMForceData`, `PlayerYSpdData`, `InitMForceData`, `MaxLeftXSpdData`, `MaxRightXSpdData`, `FrictionData`, `Climb_Y_SpeedData`, `Climb_Y_MForceData`, `PlayerPhysicsSub`, `ProcClimb`, `SetCAnim`, `CheckForJumping`, `NoJump`, `ProcJumping`, `InitJS`, `ChkWtr`, `GetYPhy`, `PJumpSnd`, `SJumpSnd`, `X_Physics`, `ProcPRun`, `ChkRFast`, `FastXSp`, `SetRTmr`, `GetXPhy`, `GetXPhy2`, `ExitPhy`, `PlayerAnimTmrData`, `GetPlayerAnimSpeed`, `ChkSkid`, `SetRunSpd`, `ProcSkid`, `SetAnimSpd`, `ImposeFriction`, `JoypFrict`, `LeftFrict`, `RghtFrict`, `XSpdSign`, `SetAbsSpd`, `ProcFireball_Bubble`, `ProcFireballs`, `ProcAirBubbles`, `BublLoop`, `BublExit`, `FireballXSpdData`, `FireballObjCore`, `RunFB`, `EraseFB`, `NoFBall`, `FireballExplosion`, `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`, `Y_Bubl`, `ExitBubl`, `Bubble_MForceData`, `BubbleTimerData`, `RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer`, `WarpZoneObject`, `ProcessWhirlpools`, `WhLoop`, `NextWh`, `ExitWh`, `WhirlpoolActivate`, `LeftWh`, `SetPWh`, `WhPull`, `FlagpoleScoreMods`, `FlagpoleScoreDigits`, `FlagpoleRoutine`, `SkipScore`, `GiveFPScr`, `FPGfx`, `ExitFlagP`, `Jumpspring_Y_PosData`, `JumpspringHandler`, `DownJSpr`, `PosJSpr`, `BounceJS`, `DrawJSpr`, `ExJSpring`, `Setup_Vine`, `NextVO`, `VineHeightData`, `VineObjectHandler`, `RunVSubs`, `VDrawLoop`, `KillVine`, `WrCMTile`, `ExitVH`, `CannonBitmasks`, `ProcessCannons`, `ThreeSChk`, `FireCannon`, `Chk_BB`, `Next3Slt`, `ExCannon`, `BulletBillXSpdData`, `BulletBillHandler`, `SetupBB`, `ChkDSte`, `BBFly`, `RunBBSubs`, `KillBB`, `HammerEnemyOfsData`, `HammerXSpdData`, `SpawnHammerObj`, `SetMOfs`, `NoHammer`, `ProcHammerObj`, `SetHSpd`, `SetHPos`, `RunAllH`, `RunHSubs`, `CoinBlock`, `SetupJumpCoin`, `JCoinC`, `FindEmptyMiscSlot`, `FMiscLoop`, `UseMiscS`, `MiscObjectsCore`, `MiscLoop`, `ProcJumpCoin`, `JCoinRun`, `RunJCSubs`, `MiscLoopBack`, `CoinTallyOffsets`, `ScoreOffsets`, `StatusBarNybbles`, `GiveOneCoin`, `CoinPoints`, `AddToScore`, `GetSBNybbles`, `UpdateNumber`, `NoZSup`, `SetupPowerUp`, `PwrUpJmp`, `StrType`, `PutBehind`, `PowerUpObjHandler`, `ShroomM`, `GrowThePowerUp`, `ChkPUSte`, `RunPUSubs`, `ExitPUp`, `BlockYPosAdderData`, `PlayerHeadCollision`, `DBlockSte`, `ChkBrick`, `StartBTmr`, `ContBTmr`, `PutOldMT`, `PutMTileB`, `SmallBP`, `BigBP`, `Unbreak`, `InvOBit`, `InitBlock_XY_Pos`, `BumpBlock`, `BlockCode`, `MushFlowerBlock`, `StarBlock`, `ExtraLifeMushBlock`, `VineBlock`, `ExitBlockChk`, `BrickQBlockMetatiles`, `BlockBumpedChk`, `BumpChkLoop`, `MatchBump`, `BrickShatter`, `CheckTopOfBlock`, `TopEx`, `SpawnBrickChunks`, `BlockObjectsCore`, `ChkTop`, `BouncingBlockHandler`, `KillBlock`, `UpdSte`, `BlockObjMT_Updater`, `UpdateLoop`, `NextBUpd`, `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `SaveXSpd`, `UseAdder`, `ExXMove`, `MovePlayerVertically`, `NoJSChk`, `MoveD_EnemyVertically`, `MoveFallingPlatform`, `ContVMove`, `MoveRedPTroopaDown`, `MoveRedPTroopaUp`, `MoveRedPTroopa`, `MoveDropPlatform`, `MoveEnemySlowVert`, `SetMdMax`, `MoveJ_EnemyVertically`, `SetHiMax`, `SetXMoveAmt`, `MaxSpdBlockData`, `ResidualGravityCode`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `MovePlatformDown`, `MovePlatformUp`, `SetDplSpd`, `RedPTroopaGrav`, `ImposeGravity`, `AlterYP`, `ChkUpM`, `ExVMove`, `EnemiesAndLoopsCore`, `ChkAreaTsk`, `ChkBowserF`, `ExitELCore`, `LoopCmdWorldNumber`, `LoopCmdPageNumber`, `LoopCmdYPosition`, `ExecGameLoopback`, `ProcLoopCommand`, `FindLoop`, `IncMLoop`, `WrongChk`, `DoLpBack`, `InitMLp`, `InitLCmd`, `ChkEnemyFrenzy`, `ProcessEnemyData`, `CheckEndofBuffer`, `CheckRightBounds`, `CheckPageCtrlRow`, `PositionEnemyObj`, `CheckRightExtBounds`, `CheckForEnemyGroup`, `BuzzyBeetleMutate`, `StrID`, `CheckFrenzyBuffer`, `StrFre`, `InitEnemyObject`, `ExEPar`, `DoGroup`, `ParseRow0e`, `NotUse`, `CheckThreeBytes`, `Inc3B`, `Inc2B`, `CheckpointEnemyID`, `InitEnemyRoutines`, `NoInitCode`, `InitGoomba`, `InitPodoboo`, `InitRetainerObj`, `NormalXSpdData`, `InitNormalEnemy`, `GetESpd`, `SetESpd`, `InitRedKoopa`, `HBroWalkingTimerData`, `InitHammerBro`, `InitHorizFlySwimEnemy`, `InitBloober`, `SmallBBox`, `InitRedPTroopa`, `GetCent`, `TallBBox`, `SetBBox`, `InitVStf`, `InitBulletBill`, `InitCheepCheep`, `InitLakitu`, `SetupLakitu`, `KillLakitu`, `PRDiffAdjustData`, `LakituAndSpinyHandler`, `ChkLak`, `ChkNoEn`, `CreateL`, `RetEOfs`, `ExLSHand`, `CreateSpiny`, `DifLoop`, `UsePosv`, `SetSpSpd`, `SpinyRte`, `ChpChpEx`, `FirebarSpinSpdData`, `FirebarSpinDirData`, `InitLongFirebar`, `InitShortFirebar`, `FlyCCXPositionData`, `FlyCCXSpeedData`, `FlyCCTimerData`, `InitFlyingCheepCheep`, `MaxCC`, `GSeed`, `RSeed`, `D2XPos1`, `D2XPos2`, `FinCCSt`, `InitBowser`, `DuplicateEnemyObj`, `FSLoop`, `FlmEx`, `FlameYPosData`, `FlameYMFAdderData`, `InitBowserFlame`, `SetFrT`, `PutAtRightExtent`, `SpawnFromMouth`, `SetMF`, `FinishFlame`, `FireworksXPosData`, `FireworksYPosData`, `InitFireworks`, `StarFChk`, `ExitFWk`, `Bitmasks`, `Enemy17YPosData`, `SwimCC_IDData`, `BulletBillCheepCheep`, `ChkW2`, `Get17ID`, `Set17ID`, `GetRBit`, `ChkRBit`, `AddFBit`, `DoBulletBills`, `BB_SLoop`, `ExF17`, `FireBulletBill`, `HandleGroupEnemies`, `PullID`, `SnglID`, `SetYGp`, `CntGrp`, `GrLoop`, `GSltLp`, `NextED`, `InitPiranhaPlant`, `InitEnemyFrenzy`, `NoFrenzyCode`, `EndFrenzy`, `LakituChk`, `NextFSlot`, `InitJumpGPTroopa`, `TallBBox2`, `SetBBox2`, `InitBalPlatform`, `AlignP`, `SetBPA`, `InitDropPlatform`, `InitHoriPlatform`, `InitVertPlatform`, `SetYO`, `CommonPlatCode`, `SPBBox`, `CasPBB`, `LargeLiftUp`, `LargeLiftDown`, `LargeLiftBBox`, `PlatLiftUp`, `PlatLiftDown`, `CommonSmallLift`, `PlatPosDataLow`, `PlatPosDataHigh`, `PosPlatform`, `EndOfEnemyInitCode`, `RunEnemyObjectsCore`, `JmpEO`, `NoRunCode`, `RunRetainerObj`, `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode`, `RunBowserFlame`, `RunFirebarObj`, `RunSmallPlatform`, `RunLargePlatform`, `SkipPT`, `LargePlatformSubroutines`, `EraseEnemyObject`, `MovePodoboo`, `PdbM`, `HammerThrowTmrData`, `XSpeedAdderData`, `RevivedXSpeed`, `ProcHammerBro`, `ChkJH`, `DecHT`, `HammerBroJumpLData`, `HammerBroJumpCode`, `SetHJ`, `HJump`, `MoveHammerBroXDir`, `Shimmy`, `SetShim`, `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`, `SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`, `ChkKillGoomba`, `NKGmba`, `MoveJumpingEnemy`, `ProcMoveRedPTroopa`, `NoIncPT`, `MoveRedPTUpOrDown`, `MovPTDwn`, `MoveFlyGreenPTroopa`, `YSway`, `NoMGPT`, `XMoveCntr_GreenPTroopa`, `XMoveCntr_Platform`, `NoIncXM`, `IncPXM`, `DecSeXM`, `MoveWithXMCntrs`, `XMRight`, `BlooberBitmasks`, `MoveBloober`, `FBLeft`, `SBMDir`, `BlooberSwim`, `SwimX`, `LeftSwim`, `MoveDefeatedBloober`, `ProcSwimmingB`, `BSwimE`, `SlowSwim`, `NoSSw`, `ChkForFloatdown`, `Floatdown`, `NoFD`, `ChkNearPlayer`, `MoveBulletBill`, `NotDefB`, `SwimCCXMoveData`, `MoveSwimmingCheepCheep`, `CCSwim`, `CCSwimUpwards`, `ChkSwimYPos`, `YPDiff`, `ExSwCC`, `FirebarPosLookupTbl`, `FirebarMirrorData`, `FirebarTblOffsets`, `FirebarYPos`, `ProcFirebar`, `SusFbar`, `SkpFSte`, `SetupGFB`, `SetMFbar`, `DrawFbar`, `NextFbar`, `SkipFBar`, `DrawFirebar_Collision`, `AddHA`, `SubtR1`, `ChkFOfs`, `VAHandl`, `AddVA`, `SetVFbr`, `FirebarCollision`, `AdjSm`, `BigJp`, `FBCLoop`, `ChkVFBD`, `ChkFBCl`, `Chk2Ofs`, `ChgSDir`, `SetSDir`, `NoColFB`, `GetFirebarPosition`, `GetHAdder`, `GetVAdder`, `PRandomSubtracter`, `FlyCCBPriority`, `MoveFlyingCheepCheep`, `FlyCC`, `AddCCF`, `BPGet`, `LakituDiffAdj`, `MoveLakitu`, `ChkLS`, `Fr12S`, `LdLDa`, `SetLSpd`, `SetLMov`, `PlayerLakituDiff`, `ChkLakDif`, `SetLMovD`, `ChkPSpeed`, `ChkSpinyO`, `ChkEmySpd`, `SubDifAdj`, `SPixelLak`, `ExMoveLak`, `BridgeCollapseData`, `BridgeCollapse`, `SetM2`, `MoveD_Bowser`, `RemoveBridge`, `NoBFall`, `PRandomRange`, `RunBowser`, `KillAllEnemies`, `KillLoop`, `BowserControl`, `ChkMouth`, `FeetTmr`, `ResetMDr`, `B_FaceP`, `GetPRCmp`, `GetDToO`, `CompDToO`, `HammerChk`, `SetHmrTmr`, `SkipToFB`, `MakeBJump`, `ChkFireB`, `SpawnFBr`, `SetFBTmr`, `BowserGfxHandler`, `CopyFToR`, `ExBGfxH`, `ProcessBowserHalf`, `FlameTimerData`, `SetFlameTimer`, `ExFl`, `ProcBowserFlame`, `SFlmX`, `SetGfxF`, `FlmeAt`, `DrawFlameLoop`, `M3FOfs`, `M2FOfs`, `M1FOfs`, `ExFlmeD`, `RunFireworks`, `SetupExpl`, `FireworksSoundScore`, `StarFlagYPosAdder`, `StarFlagXPosAdder`, `StarFlagTileData`, `RunStarFlagObj`, `GameTimerFireworks`, `SetFWC`, `IncrementSFTask1`, `StarFlagExit`, `AwardGameTimerPoints`, `NoTTick`, `EndAreaPoints`, `ELPGive`, `RaiseFlagSetoffFWorks`, `SetoffF`, `DrawStarFlag`, `DSFLoop`, `DrawFlagSetTimer`, `IncrementSFTask2`, `DelayToAreaEnd`, `StarFlagExit2`, `MovePiranhaPlant`, `ChkPlayerNearPipe`, `ReversePlantSpeed`, `SetupToMovePPlant`, `RiseFallPiranhaPlant`, `PutinPipe`, `FirebarSpin`, `SpinCounterClockwise`, `BalancePlatform`, `DoBPl`, `CheckBalPlatform`, `ChkForFall`, `MakePlatformFall`, `ChkOtherForFall`, `ChkToMoveBalPlat`, `ColFlg`, `PlatUp`, `PlatSt`, `PlatDn`, `DoOtherPlatform`, `DrawEraseRope`, `EraseR1`, `OtherRope`, `EraseR2`, `EndRp`, `ExitRp`, `SetupPlatformRope`, `GetLRp`, `GetHRp`, `ExPRp`, `InitPlatformFall`, `StopPlatforms`, `PlatformFall`, `ExPF`, `YMovingPlatform`, `SkipIY`, `ChkYCenterPos`, `YMDown`, `ChkYPCollision`, `ExYPl`, `XMovingPlatform`, `PositionPlayerOnHPlat`, `PPHSubt`, `SetPVar`, `ExXMP`, `DropPlatform`, `ExDPl`, `RightPlatform`, `ExRPl`, `MoveLargeLiftPlat`, `MoveSmallPlatform`, `MoveLiftPlatforms`, `ChkSmallPlatCollision`, `ExLiftP`, `OffscreenBoundsCheck`, `LimitB`, `ExtendLB`, `TooFar`, `ExScrnBd`, `FireballEnemyCollision`, `FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`, `NoFToECol`, `ExitFBallEnemy`, `BowserIdentities`, `HandleEnemyFBallCol`, `ChkBuzzyBeetle`, `HurtBowser`, `SetDBSte`, `ChkOtherEnemies`, `ShellOrBlockDefeat`, `StnE`, `GoombaPoints`, `EnemySmackScore`, `ExHCF`, `PlayerHammerCollision`, `ClHCol`, `ExPHC`, `HandlePowerUpCollision`, `Shroom_Flower_PUp`, `SetFor1Up`, `UpToSuper`, `UpToFiery`, `NoPUp`, `ResidualXSpdData`, `KickedShellXSpdData`, `DemotedKoopaXSpdData`, `PlayerEnemyCollision`, `NoPECol`, `CheckForPUpCollision`, `EColl`, `KickedShellPtsData`, `HandlePECollisions`, `KSPts`, `ExPEC`, `ChkForPlayerInjury`, `ChkInj`, `ChkETmrs`, `TInjE`, `InjurePlayer`, `ForceInjury`, `SetKRout`, `SetPRout`, `ExInjColRoutines`, `KillPlayer`, `StompedEnemyPtsData`, `EnemyStomped`, `EnemyStompedPts`, `ChkForDemoteKoopa`, `RevivalRateData`, `HandleStompedShellE`, `SBnce`, `ChkEnemyFaceRight`, `LInj`, `EnemyFacePlayer`, `SFcRt`, `SetupFloateyNumber`, `ExSFN`, `SetBitsMask`, `ClearBitsMask`, `EnemiesCollision`, `ECLoop`, `YesEC`, `NoEnemyCollision`, `ReadyNextEnemy`, `ExitECRoutine`, `ProcEnemyCollisions`, `ShellCollisions`, `ExitProcessEColl`, `ProcSecondEnemyColl`, `MoveEOfs`, `EnemyTurnAround`, `RXSpd`, `ExTA`, `LargePlatformCollision`, `ChkForPlayerC_LargeP`, `ExLPC`, `SmallPlatformCollision`, `ChkSmallPlatLoop`, `MoveBoundBox`, `ExSPC`, `ProcSPlatCollisions`, `ProcLPlatCollisions`, `ChkForTopCollision`, `SetCollisionFlag`, `PlatformSideCollisions`, `SideC`, `NoSideC`, `PlayerPosSPlatData`, `PositionPlayerOnS_Plat`, `PositionPlayerOnVPlat`, `ExPlPos`, `CheckPlayerVertical`, `ExCPV`, `GetEnemyBoundBoxOfs`, `GetEnemyBoundBoxOfsArg`, `PlayerBGUpperExtent`, `PlayerBGCollision`, `SetFallS`, `SetPSte`, `ChkOnScr`, `ExPBGCol`, `ChkCollSize`, `GBBAdr`, `HeadChk`, `SolidOrClimb`, `NYSpd`, `DoFootCheck`, `AwardTouchedCoin`, `ChkFootMTile`, `ContChk`, `LandPlyr`, `InitSteP`, `DoPlayerSideCheck`, `SideCheckLoop`, `BHalf`, `ExSCH`, `CheckSideMTiles`, `ContSChk`, `ChkPBtm`, `PipeDwnS`, `PlyrPipe`, `SetCATmr`, `ChkGERtn`, `StopPlayerMove`, `ExCSM`, `AreaChangeTimerData`, `HandleCoinMetatile`, `HandleAxeMetatile`, `ErACM`, `ClimbXPosAdder`, `ClimbPLocAdder`, `FlagpoleYPosData`, `HandleClimbing`, `ExHC`, `ChkForFlagpole`, `FlagpoleCollision`, `ChkFlagpoleYPosLoop`, `MtchF`, `RunFR`, `VineCollision`, `PutPlayerOnVine`, `SetVXPl`, `ExPVne`, `ChkInvisibleMTiles`, `ExCInvT`, `ChkForLandJumpSpring`, `ExCJSp`, `ChkJumpspringMetatiles`, `JSFnd`, `NoJSFnd`, `HandlePipeEntry`, `GetWNum`, `ExPipeE`, `ImpedePlayerMove`, `RImpd`, `NXSpd`, `PlatF`, `ExIPM`, `SolidMTileUpperExt`, `CheckForSolidMTiles`, `ClimbMTileUpperExt`, `CheckForClimbMTiles`, `CheckForCoinMTiles`, `CoinSd`, `GetMTileAttrib`, `ExEBG`, `EnemyBGCStateData`, `EnemyBGCXSpdData`, `EnemyToBGCollisionDet`, `DoIDCheckBGColl`, `HBChk`, `CInvu`, `YesIn`, `NoEToBGCollision`, `HandleEToBGCollision`, `GiveOEPoints`, `ChkToStunEnemies`, `Demote`, `SetStun`, `SetWYSpd`, `SetNotW`, `ChkBBill`, `NoCDirF`, `ExEBGChk`, `LandEnemyProperly`, `SChkA`, `ChkLandedEnemyState`, `SetForStn`, `ExSteChk`, `ProcEnemyDirection`, `InvtD`, `CNwCDir`, `LandEnemyInitState`, `NMovShellFallBit`, `ChkForRedKoopa`, `Chk2MSBSt`, `GetSteFromD`, `SetD6Ste`, `DoEnemySideCheck`, `SdeCLoop`, `NextSdeC`, `ExESdeC`, `ChkForBump_HammerBroJ`, `NoBump`, `InvEnemyDir`, `PlayerEnemyDiff`, `EnemyLanding`, `SubtEnemyYPos`, `EnemyJump`, `DoSide`, `HammerBroBGColl`, `KillEnemyAboveBlock`, `UnderHammerBro`, `NoUnderHammerBro`, `ChkUnderEnemy`, `ChkForNonSolids`, `NSFnd`, `FireballBGCollision`, `ClearBounceFlag`, `InitFireballExplode`, `BoundBoxCtrlData`, `GetFireballBoundBox`, `GetMiscBoundBox`, `FBallB`, `GetEnemyBoundBox`, `SmallPlatformBoundBox`, `GetMaskedOffScrBits`, `CMBits`, `LargePlatformBoundBox`, `SetupEOffsetFBBox`, `MoveBoundBoxOffscreen`, `BoundingBoxCore`, `CheckRightScreenBBox`, `SORte`, `NoOfs`, `CheckLeftScreenBBox`, `SOLft`, `NoOfs2`, `PlayerCollisionCore`, `SprObjectCollisionCore`, `CollisionCoreLoop`, `SecondBoxVerticalChk`, `FirstBoxGreater`, `NoCollisionFound`, `CollisionFound`, `BlockBufferChk_Enemy`, `ResidualMiscObjectCode`, `BlockBufferChk_FBall`, `ResJmpM`, `BBChk_E`, `BlockBufferAdderData`, `BlockBuffer_X_Adder`, `BlockBuffer_Y_Adder`, `BlockBufferColli_Feet`, `BlockBufferColli_Head`, `BlockBufferColli_Side`, `BlockBufferCollision`, `RetXC`, `RetYC`, `VineYPosAdder`, `DrawVine`, `VineTL`, `SkpVTop`, `ChkFTop`, `NextVSp`, `SixSpriteStacker`, `StkLp`, `FirstSprXPos`, `FirstSprYPos`, `SecondSprXPos`, `SecondSprYPos`, `FirstSprTilenum`, `SecondSprTilenum`, `HammerSprAttrib`, `DrawHammer`, `ForceHPose`, `GetHPose`, `RenderH`, `NoHOffscr`, `FlagpoleScoreNumTiles`, `FlagpoleGfxHandler`, `ChkFlagOffscreen`, `MoveSixSpritesOffscreen`, `DumpSixSpr`, `DumpFourSpr`, `DumpThreeSpr`, `DumpTwoSpr`, `ExitDumpSpr`, `DrawLargePlatform`, `ShrinkPlatform`, `SetLast2Platform`, `SetPlatformTilenum`, `SChk2`, `SChk3`, `SChk4`, `SChk5`, `SChk6`, `SLChk`, `ExDLPl`, `DrawFloateyNumber_Coin`, `NotRsNum`, `JumpingCoinTiles`, `JCoinGfxHandler`, `ExJCGfx`, `PowerUpGfxTable`, `PowerUpAttributes`, `DrawPowerUp`, `PUpDrawLoop`, `FlipPUpRightSide`, `PUpOfs`, `EnemyGraphicsTable`, `EnemyGfxTableOffsets`, `EnemyAttributeData`, `EnemyAnimTimingBMask`, `JumpspringFrameOffsets`, `EnemyGfxHandler`, `CheckForRetainerObj`, `CheckForBulletBillCV`, `SBBAt`, `CheckForJumpspring`, `CheckForPodoboo`, `CheckBowserGfxFlag`, `SBwsrGfxOfs`, `CheckForGoomba`, `GmbaAnim`, `CheckBowserFront`, `ChkFrontSte`, `FlipBowserOver`, `DrawBowser`, `CheckBowserRear`, `ChkRearSte`, `CheckForSpiny`, `NotEgg`, `CheckForLakitu`, `NoLAFr`, `CheckUpsideDownShell`, `CheckRightSideUpShell`, `CheckForDefdGoomba`, `CheckForHammerBro`, `CheckForBloober`, `CheckToAnimateEnemy`, `CheckForSecondFrame`, `CheckAnimationStop`, `CheckDefeatedState`, `DrawEnemyObject`, `SkipToOffScrChk`, `CheckForVerticalFlip`, `FlipEnemyVertically`, `CheckForESymmetry`, `ContES`, `ESRtnr`, `SpnySC`, `MirrorEnemyGfx`, `EggExc`, `CheckToMirrorLakitu`, `NVFLak`, `CheckToMirrorJSpring`, `SprObjectOffscrChk`, `LcChk`, `Row3C`, `Row23C`, `AllRowC`, `ExEGHandler`, `DrawEnemyObjRow`, `DrawOneSpriteRow`, `MoveESprRowOffscreen`, `MoveESprColOffscreen`, `DefaultBlockObjTiles`, `DrawBlock`, `DBlkLoop`, `ChkRep`, `SetBFlip`, `BlkOffscr`, `PullOfsB`, `ChkLeftCo`, `MoveColOffscreen`, `ExDBlk`, `DrawBrickChunks`, `DChunks`, `ChnkOfs`, `ExBCDr`, `DrawFireball`, `DrawFirebar`, `FireA`, `ExplosionTiles`, `DrawExplosion_Fireball`, `DrawExplosion_Fireworks`, `KillFireBall`, `DrawSmallPlatform`, `TopSP`, `BotSP`, `SOfs`, `SOfs2`, `ExSPl`, `DrawBubble`, `ExDBub`, `PlayerGfxTblOffsets`, `PlayerGraphicsTable`, `SwimKickTileNum`, `PlayerGfxHandler`, `CntPl`, `SwimKT`, `BigKTS`, `ExPGH`, `FindPlayerAction`, `DoChangeSize`, `PlayerKilled`, `PlayerGfxProcessing`, `SUpdR`, `PlayerOffscreenChk`, `PROfsLoop`, `NPROffscr`, `IntermediatePlayerData`, `DrawPlayer_Intermediate`, `PIntLoop`, `RenderPlayerSub`, `DrawPlayerLoop`, `ProcessPlayerAction`, `ProcOnGroundActs`, `NonAnimatedActs`, `ActionFalling`, `ActionWalkRun`, `ActionClimbing`, `ActionSwimming`, `GetCurrentAnimOffset`, `FourFrameExtent`, `ThreeFrameExtent`, `AnimationControl`, `SetAnimC`, `ExAnimC`, `GetGfxOffsetAdder`, `SzOfs`, `ChangeSizeOffsetAdder`, `HandleChangeSize`, `CSzNext`, `GorSLog`, `GetOffsetFromAnimCtrl`, `ShrinkPlayer`, `ShrPlF`, `ChkForPlayerAttrib`, `KilledAtt`, `C_S_IGAtt`, `ExPlyrAt`, `RelativePlayerPosition`, `RelativeBubblePosition`, `RelativeFireballPosition`, `RelWOfs`, `RelativeMiscPosition`, `RelativeEnemyPosition`, `RelativeBlockPosition`, `VariableObjOfsRelPos`, `GetObjRelativePosition`, `GetPlayerOffscreenBits`, `GetFireballOffscreenBits`, `GetBubbleOffscreenBits`, `GetMiscOffscreenBits`, `ObjOffsetData`, `GetProperObjOffset`, `GetEnemyOffscreenBits`, `GetBlockOffscreenBits`, `SetOffscrBitsOffset`, `GetOffScreenBitsSet`, `RunOffscrBitsSubs`, `XOffscreenBitsData`, `DefaultXOnscreenOfs`, `GetXOffscreenBits`, `XOfsLoop`, `XLdBData`, `ExXOfsBS`, `YOffscreenBitsData`, `DefaultYOnscreenOfs`, `HighPosUnitData`, `GetYOffscreenBits`, `YOfsLoop`, `YLdBData`, `ExYOfsBS`, `DividePDiff`, `SetOscrO`, `ExDivPD`, `DrawSpriteObject`, `NoHFlip`, `SetHFAt`, `SoundEngine`, `SndOn`, `InPause`, `PTone1F`, `ContPau`, `PTone2F`, `PTRegC`, `DecPauC`, `SkipPIn`, `RunSoundSubroutines`, `SkipSoundSubroutines`, `NoIncDAC`, `StrWave`, `Dump_Squ1_Regs`, `PlaySqu1Sfx`, `SetFreq_Squ1`, `Dump_Freq_Regs`, `NoTone`, `Dump_Sq2_Regs`, `PlaySqu2Sfx`, `SetFreq_Squ2`, `SetFreq_Tri`, `SwimStompEnvelopeData`, `PlayFlagpoleSlide`, `PlaySmallJump`, `PlayBigJump`, `JumpRegContents`, `ContinueSndJump`, `N2Prt`, `FPS2nd`, `DmpJpFPS`, `PlayFireballThrow`, `PlayBump`, `Fthrow`, `ContinueBumpThrow`, `DecJpFPS`, `Square1SfxHandler`, `CheckSfx1Buffer`, `ExS1H`, `PlaySwimStomp`, `ContinueSwimStomp`, `BranchToDecLength1`, `PlaySmackEnemy`, `ContinueSmackEnemy`, `SmSpc`, `SmTick`, `DecrementSfx1Length`, `StopSquare1Sfx`, `ExSfx1`, `PlayPipeDownInj`, `ContinuePipeDownInj`, `NoPDwnL`, `ExtraLifeFreqData`, `PowerUpGrabFreqData`, `PUp_VGrow_FreqData`, `PlayCoinGrab`, `PlayTimerTick`, `CGrab_TTickRegL`, `ContinueCGrabTTick`, `N2Tone`, `PlayBlast`, `ContinueBlast`, `SBlasJ`, `PlayPowerUpGrab`, `ContinuePowerUpGrab`, `LoadSqu2Regs`, `DecrementSfx2Length`, `EmptySfx2Buffer`, `StopSquare2Sfx`, `ExSfx2`, `Square2SfxHandler`, `CheckSfx2Buffer`, `ExS2H`, `Cont_CGrab_TTick`, `JumpToDecLength2`, `PlayBowserFall`, `BlstSJp`, `ContinueBowserFall`, `PBFRegs`, `EL_LRegs`, `PlayExtraLife`, `ContinueExtraLife`, `DivLLoop`, `PlayGrowPowerUp`, `PlayGrowVine`, `GrowItemRegs`, `ContinueGrowItems`, `StopGrowItems`, `BrickShatterFreqData`, `PlayBrickShatter`, `ContinueBrickShatter`, `PlayNoiseSfx`, `DecrementSfx3Length`, `ExSfx3`, `NoiseSfxHandler`, `CheckNoiseBuffer`, `ExNH`, `PlayBowserFlame`, `ContinueBowserFlame`, `ContinueMusic`, `MusicHandler`, `LoadEventMusic`, `NoStopSfx`, `LoadAreaMusic`, `NoStop1`, `GMLoopB`, `HandleAreaMusicLoopB`, `FindAreaMusicHeader`, `FindEventMusicHeader`, `LoadHeader`, `HandleSquare2Music`, `EndOfMusicData`, `NotTRO`, `MusicLoopBack`, `VictoryMLoopBack`, `Squ2LengthHandler`, `Squ2NoteHandler`, `Rest`, `SkipFqL1`, `MiscSqu2MusicTasks`, `NoDecEnv1`, `HandleSquare1Music`, `FetchSqu1MusicData`, `Squ1NoteHandler`, `SkipCtrlL`, `MiscSqu1MusicTasks`, `NoDecEnv2`, `DeathMAltReg`, `DoAltLoad`, `HandleTriangleMusic`, `TriNoteHandler`, `NotDOrD4`, `MediN`, `LongN`, `LoadTriCtrlReg`, `HandleNoiseMusic`, `FetchNoiseBeatData`, `NoiseBeatHandler`, `StrongBeat`, `LongBeat`, `SilentBeat`, `PlayBeat`, `ExitMusicHandler`, `AlternateLengthHandler`, `ProcessLengthData`, `LoadControlRegs`, `NotECstlM`, `WaterMus`, `AllMus`, `LoadEnvelopeData`, `LoadUsualEnvData`, `LoadWaterEventMusEnvData`, `MusicHeaderData`, `TimeRunningOutHdr`, `Star_CloudHdr`, `EndOfLevelMusHdr`, `ResidualHeaderData`, `UndergroundMusHdr`, `SilenceHdr`, `CastleMusHdr`, `VictoryMusHdr`, `GameOverMusHdr`, `WaterMusHdr`, `WinCastleMusHdr`, `GroundLevelPart1Hdr`, `GroundLevelPart2AHdr`, `GroundLevelPart2BHdr`, `GroundLevelPart2CHdr`, `GroundLevelPart3AHdr`, `GroundLevelPart3BHdr`, `GroundLevelLeadInHdr`, `GroundLevelPart4AHdr`, `GroundLevelPart4BHdr`, `GroundLevelPart4CHdr`, `DeathMusHdr`, `Star_CloudMData`, `GroundM_P1Data`, `SilenceData`, `GroundM_P2AData`, `GroundM_P2BData`, `GroundM_P2CData`, `GroundM_P3AData`, `GroundM_P3BData`, `GroundMLdInData`, `GroundM_P4AData`, `GroundM_P4BData`, `DeathMusData`, `GroundM_P4CData`, `CastleMusData`, `GameOverMusData`, `TimeRunOutMusData`, `WinLevelMusData`, `UndergroundMusData`, `WaterMusData`, `EndOfCastleMusData`, `VictoryMusData`, `FreqRegLookupTbl`, `MusicLengthLookupTbl`, `EndOfCastleMusicEnvData`, `AreaMusicEnvData`, `WaterEventMusEnvData`, `BowserFlameEnvData`, `BrickShatterEnvData` |

## Future admission packages and queued plans

Custody is a current receipt. Planned coverage is a queued scope and does not
transfer existing ownership or allocate a numeric T.

| Candidate | Nodes held in custody | Queued scope / S slots | Admission path / reason |
| --- | ---: | --- | --- |
| historical-node-closure | 0 | 338 nodes / 57 planned S | [record](../../docs/proposals/m2/historical-node-closure-package.md); Owner-requested single priority package for the 338 named historical unresolved nodes; queued, not admitted. |
| root-revalidation | 0 | not decomposed here | [record](../../docs/proposals/m2/frame-root.md); T14 is closed; a new admitted T/S must accept outstanding root verification. |
| screen-status | 0 | not decomposed here | [record](../../docs/proposals/m2/screen-status.md); T27 S1 is admitted for the screen-task root; later T27 chains remain queued and their nodes retain T24 S2 custody until individual admission. |
| game-dispatcher | 0 | not decomposed here | [record](../../docs/history/M2-T31-game-dispatcher.md); Candidate has no allocated implementation T/S yet. |
| audio-engine-deferred | 0 | not decomposed here | [record](../../docs/proposals/m2/audio-engine.md); Prematurely numbered audio candidate held until later admission. |
| fireball-bubble-timer-warp-deferred | 0 | not decomposed here | [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md); T20 unfinished nodes await their source-order T32/T33 successors, not T21. |
| t22-nmi-ppu-deferred | 0 | not decomposed here | [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md); T21 closure found that the boot root and queued NMI/PPU nodes share the first-NMI ownership boundary; pending source-order T22 admission. |
| remaining-current-certification | 0 | not decomposed here | [record](../../docs/proposals/m2/remaining-current-certification.md); Owner-approved transfer of unfinished T70/S17 verification to queue tail;maintenance node receivers unchanged. |

## Every node

| ROM line | Node | Current receiving S | Future package / basis | Historical T/S records |
| ---: | --- | --- | --- | --- |
| 699 | `Start` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T11 / S not recorded; M2 T14 / S not recorded; M2 T15 / S not recorded; M2 T15 S4; M2 T17 S6; M2 T19 S5; M2 T2 / S not recorded; M2 T21 S1; M2 T21 S2; M2 T24 S1; M2 T3 / S not recorded; M2 T8 / S not recorded |
| 706 | `VBlank1` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 708 | `VBlank2` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 712 | `WBootCheck` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 721 | `ColdBoot` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 737 | `EndlessLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 743 | `VRAM_AddrTable_Low` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T22 S15; M2 T24 S1 |
| 752 | `VRAM_AddrTable_High` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T22 S15; M2 T24 S1 |
| 761 | `VRAM_Buffer_Offset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T22 S15; M2 T24 S1 |
| 764 | `NonMaskableInterrupt` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T22 S22; M2 T24 S1 |
| 776 | `ScreenOff` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 796 | `InitBuffer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S16; M2 T22 S23; M2 T24 S1 |
| 814 | `DecTimers` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 820 | `DecTimersLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 823 | `SkipExpTimer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 825 | `NoDecTimers` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 826 | `PauseSkip` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 837 | `RotPRandomBit` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 843 | `Sprite0Clr` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 851 | `Sprite0Hit` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 855 | `HBlankDelay` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 857 | `SkipSprite0` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 868 | `SkipMainOper` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 876 | `PauseRoutine` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 885 | `ChkPauseTimer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 889 | `ChkStart` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 904 | `ClrPauseTimer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 906 | `SetPause` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 907 | `ExitPause` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 912 | `SpriteShuffler` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1; M2 T9 / S not recorded |
| 917 | `ShuffleLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 926 | `StrSprOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 927 | `NextSprOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 934 | `SetAmtOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 937 | `SetMiscOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 954 | `OperModeExecutionTree` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S21; M2 T22 S28; M2 T24 S1 |
| 965 | `MoveAllSpritesOffscreen` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 969 | `MoveSpritesOffscreen` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 972 | `SprInitLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 982 | `TitleScreenMode` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 993 | `WSelectBufferTemplate` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 996 | `GameMenuRoutine` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1004 | `StartGame` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4; M2 T25 S9 |
| 1005 | `ChkSelect` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S10; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1013 | `ChkWorldSel` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1018 | `SelectBLogic` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1033 | `IncWorldSel` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1039 | `UpdateShroom` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1047 | `NullJoypad` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1049 | `RunDemo` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1053 | `ResetTitle` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1059 | `ChkContinue` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1065 | `StartWorld1` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1077 | `InitScores` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1080 | `ExitMenu` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1081 | `GoContinue` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T2 / S not recorded; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1090 | `MushroomIconData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1093 | `DrawMushroomIcon` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1095 | `IconDataRead` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1105 | `ExitIcon` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1109 | `DemoActionData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1114 | `DemoTimingData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1119 | `DemoEngine` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T15 S4; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1129 | `DoAction` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1133 | `DemoOver` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1137 | `VictoryMode` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5; M2 T26 S6; M2 T26 S7; M2 T6 / S not recorded |
| 1144 | `AutoPlayer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5; M2 T26 S6; M2 T26 S7 |
| 1147 | `VictoryModeSubroutines` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5; M2 T6 / S not recorded |
| 1159 | `SetupVictoryMode` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1169 | `PlayerVictoryWalk` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T15 S4; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1178 | `PerformWalk` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1180 | `DontWalk` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1195 | `ExitVWalk` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1201 | `PrintVictoryMessages` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1215 | `MRetainerMsg` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1217 | `ThankPlayer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1223 | `SecondPartMsg` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1232 | `EvalForMusic` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1236 | `PrintMsg` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1240 | `IncMsgCounter` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1248 | `SetEndTimer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1251 | `IncModeTask_A` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1252 | `ExitMsgs` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1256 | `PlayerEndWorld` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1271 | `EndExitOne` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1272 | `EndChkBButton` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1281 | `EndExitTwo` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1287 | `FloateyNumTileData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1303 | `ScoreUpdateData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1308 | `FloateyNumbersRoutine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1315 | `ChkNumTimer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1320 | `DecNumTimer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1328 | `LoadNumTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1338 | `ChkTallEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1355 | `GetAltOffset` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1358 | `FloateyPart` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1363 | `SetupNumSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1386 | `ScreenRoutines` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S2; M2 T15 S3; M2 T24 S1 |
| 1408 | `InitScreen` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1418 | `SetupIntermediate` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1436 | `AreaPalette` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1439 | `GetAreaPalette` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1442 | `SetVRAMAddr_A` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1443 | `NextSubtask` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1448 | `BGColorCtrl_Addr` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1451 | `BackgroundColors` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1455 | `PlayerColors` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1460 | `GetBackgroundColor` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1465 | `NoBGColor` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1467 | `GetPlayerColors` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S3; M2 T24 S1 |
| 1473 | `ChkFiery` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1477 | `StartClrGet` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1479 | `ClrGetLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1489 | `SetBGColor` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1502 | `SetVRAMOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1507 | `GetAlternatePalette1` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1512 | `SetVRAMAddr_B` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1513 | `NoAltPal` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1517 | `WriteTopStatusLine` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1524 | `WriteBottomStatusLine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T24 S1 |
| 1553 | `DisplayTimeUp` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1560 | `NoTimeUp` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1565 | `DisplayIntermediate` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S3; M2 T24 S1 |
| 1577 | `PlayerInter` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1579 | `OutputInter` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1584 | `GameOverInter` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1589 | `NoInter` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1595 | `AreaParserTaskControl` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1597 | `TaskLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1603 | `OutputCol` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1612 | `DrawTitleScreen` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1624 | `OutputTScr` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1629 | `ChkHiByte` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1639 | `ClearBuffersDrawIcon` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1643 | `TScrClear` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1648 | `IncSubtask` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1653 | `WriteTopScore` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1656 | `IncModeTask_B` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1661 | `GameText` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1662 | `TopStatusBarLine` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1671 | `WorldLivesDisplay` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1680 | `TwoPlayerTimeUp` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1682 | `OnePlayerTimeUp` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1686 | `TwoPlayerGameOver` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1688 | `OnePlayerGameOver` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1693 | `WarpZoneWelcome` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1704 | `LuigiName` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1707 | `WarpZoneNumbers` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1712 | `GameTextOffsets` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1719 | `WriteGameText` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S3; M2 T24 S1 |
| 1728 | `Chk2Players` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1731 | `LdGameText` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1733 | `GameTextLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1740 | `EndGameText` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1756 | `PutLives` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1765 | `CheckPlayerName` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1775 | `ChkLuigi` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1778 | `NameLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1782 | `ExitChkName` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1784 | `PrintWarpZoneNumbers` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1790 | `WarpNumLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1804 | `ResetSpritesAndScreenTimer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1809 | `ResetScreenTimer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1813 | `NoReset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T24 S1 |
| 1825 | `RenderAreaGraphics` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1 |
| 1840 | `DrawMTLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1878 | `RightCheck` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1886 | `LLeft` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1888 | `NextMTRow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1889 | `SetAttrib` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1914 | `ExitDrawM` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1920 | `RenderAttributeTables` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1 |
| 1930 | `SetATHigh` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1940 | `AttribLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1962 | `SetVRAMCtrl` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1970 | `ColorRotatePalette` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1973 | `BlankPalette` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1977 | `Palette3Data` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1983 | `ColorRotation` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 1991 | `GetBlankPal` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2004 | `GetAreaPal` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2024 | `ExitColorRot` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2034 | `BlockGfxData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2041 | `RemoveCoin_Axe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T17 S4; M2 T21 S4; M2 T22 S1; M2 T24 S1 |
| 2047 | `WriteBlankMT` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2052 | `ReplaceBlockMetatile` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 / S not recorded; M2 T18 S1; M2 T21 S4; M2 T24 S1 |
| 2058 | `DestroyBlockMetatile` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 / S not recorded; M2 T21 S4; M2 T22 S1; M2 T24 S1 |
| 2061 | `WriteBlockMetatile` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T17 S4; M2 T18 / S not recorded; M2 T21 S4; M2 T24 S1 |
| 2076 | `UseBOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2080 | `MoveVOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2086 | `PutBlockMetatile` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T17 S4; M2 T18 / S not recorded; M2 T21 S4; M2 T24 S1 |
| 2097 | `SaveHAdder` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2118 | `RemBridge` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2145 | `MetatileGraphics_Low` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2148 | `MetatileGraphics_High` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2151 | `Palette0_MTiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2192 | `Palette1_MTiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2240 | `Palette2_MTiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2252 | `Palette3_MTiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2263 | `WaterPaletteData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2275 | `GroundPaletteData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2287 | `UndergroundPaletteData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2299 | `CastlePaletteData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2311 | `DaySnowPaletteData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2316 | `NightSnowPaletteData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2321 | `MushroomPaletteData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2326 | `BowserPaletteData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2331 | `MarioThanksMessage` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2339 | `LuigiThanksMessage` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2347 | `MushroomRetainerSaved` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2358 | `PrincessSaved1` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2366 | `PrincessSaved2` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2375 | `WorldSelectMessage1` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2382 | `WorldSelectMessage2` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2395 | `JumpEngine` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2412 | `InitializeNameTables` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2421 | `WriteNTAddr` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2427 | `InitNTLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2436 | `InitATLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2446 | `ReadJoypads` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2454 | `ReadPortBits` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2455 | `PortLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2474 | `Save8Bits` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2482 | `WriteBufferToScreen` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2495 | `SetupWrites` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2501 | `GetLength` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2504 | `OutputToVRAM` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2506 | `RepeatByte` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2523 | `UpdateScreen` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T15 S2; M2 T21 S4; M2 T24 S1 |
| 2527 | `InitScroll` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2533 | `WritePPUReg1` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2544 | `StatusBarData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2552 | `StatusBarOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2555 | `PrintStatusBarNumbers` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T19 S5; M2 T21 S4; M2 T24 S1 |
| 2564 | `OutputNumbers` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2578 | `SetupNums` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2592 | `DigitPLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2604 | `ExitOutputN` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2608 | `DigitsMathRoutine` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2613 | `AddModLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2619 | `StoreNewD` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2623 | `EraseDMods` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2625 | `EraseMLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2629 | `BorrowOne` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2632 | `CarryOne` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2639 | `UpdateTopScore` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T21 S4; M2 T24 S1 |
| 2644 | `TopScoreCheck` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2647 | `GetScoreDiff` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2655 | `CopyScore` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2661 | `NoTopSc` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2665 | `DefaultSprOffsets` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2669 | `Sprite0Data` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2674 | `InitializeGame` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T21 S4; M2 T24 S1 |
| 2678 | `ClrSndLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2685 | `InitializeArea` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T2 / S not recorded; M2 T21 S4; M2 T24 S1 |
| 2690 | `ClrTimersLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2697 | `StartPage` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2705 | `SetInitNTHigh` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S13 |
| 2728 | `SetSecHard` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2729 | `CheckHalfway` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2733 | `DoneInitArea` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2742 | `PrimaryGameSetup` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2750 | `SecondaryGameSetup` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2754 | `ClearVRLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2775 | `ShufAmtLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2780 | `ISpr0Loop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2795 | `InitializeMemory` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T14 / S not recorded; M2 T15 S3; M2 T18 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 2799 | `InitPageLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2800 | `InitByteLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2804 | `InitByte` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2805 | `SkipByte` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2814 | `MusicSelectData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2818 | `GetAreaMusic` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2830 | `ChkAreaType` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2834 | `StoreMusic` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2836 | `ExitGetM` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2840 | `PlayerStarting_X_Pos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2844 | `AltYPosOffset` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2847 | `PlayerStarting_Y_Pos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2851 | `PlayerBGPriorityData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2854 | `GameTimerData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2858 | `Entrance_GameTimerSetup` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2874 | `ChkStPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2881 | `SetStPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2900 | `ChkOverR` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2911 | `ChkSwimE` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2914 | `SetPESub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 2921 | `HalfwayPageNybbles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2931 | `PlayerLoseLife` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T6 / S not recorded |
| 2944 | `StillInGame` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2951 | `GetHalfway` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2960 | `MaskHPNyb` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2965 | `SetHalfway` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 2971 | `GameOverMode` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T6 / S not recorded |
| 2981 | `SetupGameOver` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S3; M2 T21 S4; M2 T24 S1 |
| 2993 | `RunGameOver` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S3; M2 T21 S4; M2 T24 S1 |
| 3001 | `TerminateGame` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 3015 | `ContinueGame` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T6 / S not recorded |
| 3027 | `GameIsOn` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3029 | `TransposePlayers` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T6 / S not recorded |
| 3039 | `TransLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3048 | `ExTrans` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3052 | `DoNothing1` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3055 | `DoNothing2` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3060 | `AreaParserTaskHandler` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3065 | `DoAPTasks` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3071 | `SkipATRender` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3073 | `AreaParserTasks` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3087 | `IncrementColumnPos` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3094 | `NoColWrap` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3106 | `BSceneDataOffsets` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3109 | `BackSceneryData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3131 | `BackSceneryMetatiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3145 | `FSceneDataOffsets` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3148 | `ForeSceneryData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3158 | `TerrainMetatiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3161 | `TerrainRenderBits` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3179 | `AreaParserCore` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3184 | `RenderSceneryTerrain` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3187 | `ClrMTBuf` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3193 | `ThirdP` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3198 | `RendBack` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3223 | `SceLoop1` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3231 | `RendFore` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3235 | `SceLoop2` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3238 | `NoFore` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3242 | `RendTerr` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3249 | `TerMTile` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3253 | `StoreMT` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3258 | `TerrLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3269 | `NoCloud2` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3270 | `TerrBChk` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3275 | `NextTBit` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3285 | `EndUChk` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3290 | `RendBBuf` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3295 | `ChkMTLow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3306 | `StrBlock` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3319 | `BlockBuffLowBounds` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3326 | `ProcessAreaData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1 |
| 3328 | `ProcADLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3345 | `Chk1Row13` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3363 | `Chk1Row14` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3367 | `CheckRear` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3370 | `RdyDecode` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3372 | `SetBehind` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3373 | `NextAObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3374 | `ChkLength` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3378 | `ProcLoopb` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3384 | `EndAParse` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3386 | `IncAreaObjOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3393 | `DecodeAreaData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T3 / S not recorded; M2 T30 S11 |
| 3397 | `Chk1stB` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3408 | `ChkRow14` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3416 | `ChkRow13` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S16 |
| 3429 | `Mask2MSB` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3431 | `ChkSRows` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3442 | `LrgObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3450 | `NotWPipe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3452 | `SpecObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3455 | `MoveAOId` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3459 | `NormObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3472 | `LeavePar` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3473 | `InitRear` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3479 | `LoopCmdE` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3480 | `BackColC` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3489 | `StrAObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3492 | `RunAObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3561 | `AlterAreaAttributes` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3580 | `Alter2` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3586 | `SetFore` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3591 | `ScrollLockObject_Warp` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3600 | `WarpNum` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3606 | `ScrollLockObject` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3615 | `KillEnemies` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3619 | `KillELoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3623 | `NoKillE` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3629 | `FrenzyIDData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3632 | `AreaFrenzy` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T19 S5; M2 T21 S4; M2 T24 S1 |
| 3635 | `FreCompLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3640 | `ExitAFrenzy` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3646 | `AreaStyleObject` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3653 | `TreeLedge` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3665 | `MidTreeL` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3670 | `EndTreeL` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3673 | `MushroomLedge` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3682 | `EndMushL` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3696 | `AllUnder` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3699 | `NoUnder` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3706 | `PulleyRopeMetatiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3709 | `PulleyRopeObject` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3717 | `RenderPul` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3719 | `MushLExit` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 3724 | `CastleMetatiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3737 | `CastleObject` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T17 S6; M2 T18 S2; M2 T21 S4; M2 T24 / S not recorded; M2 T24 S1; M2 T29 S9 |
| 3748 | `CRendLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3759 | `ChkCFloor` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3772 | `NotTall` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3789 | `PlayerStop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3791 | `ExitCastle` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3795 | `WaterPipe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3810 | `IntroPipe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3817 | `VPipeSectLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3823 | `NoBlankP` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3825 | `SidePipeShaftData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3828 | `SidePipeTopPart` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3831 | `SidePipeBottomPart` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3835 | `ExitPipe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3840 | `RenderSidewaysPipe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3855 | `DrawSidePart` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3862 | `VerticalPipeData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3868 | `VerticalPipe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3876 | `WarpPipe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3900 | `DrawPipe` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9; M2 T30 S12 |
| 3911 | `GetPipeHeight` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3921 | `FindEmptyEnemySlot` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3923 | `EmptyChkLoop` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3929 | `ExitEmptyChk` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3933 | `Hole_Water` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3944 | `QuestionBlockRow_High` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3948 | `QuestionBlockRow_Low` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3960 | `Bridge_High` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3964 | `Bridge_Middle` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3968 | `Bridge_Low` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3983 | `FlagBalls_Residual` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3991 | `FlagpoleObject` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 4018 | `EndlessRope` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 4023 | `BalancePlatRope` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 4034 | `DrawRope` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 4039 | `CoinMetatileData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1 |
| 4042 | `RowOfCoins` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1 |
| 4049 | `C_ObjectRow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4052 | `C_ObjectMetatile` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4055 | `CastleBridgeObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4060 | `AxeObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4064 | `ChainObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4070 | `EmptyBlock` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4074 | `ColObj` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4079 | `SolidBlockMetatiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4082 | `BrickMetatiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4086 | `RowOfBricks` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4091 | `DrawBricks` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4094 | `RowOfSolidBlocks` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4097 | `GetRow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4099 | `DrawRow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4104 | `ColumnOfBricks` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4109 | `ColumnOfSolidBlocks` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4112 | `GetRow2` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4120 | `BulletBillCannon` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S5 |
| 4135 | `SetupCannon` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S5 |
| 4146 | `StrCOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S5 |
| 4151 | `StaircaseHeightData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S6 |
| 4154 | `StaircaseRowData` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S6 |
| 4157 | `StaircaseObject` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S6 |
| 4162 | `NextStair` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S6 |
| 4172 | `Jumpspring` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T11 / S not recorded; M2 T21 S4; M2 T24 S1; M2 T30 S7 |
| 4197 | `Hidden1UpBlock` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4204 | `QuestionBlock` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4208 | `BrickWithCoins` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4212 | `BrickWithItem` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4220 | `BWithL` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4223 | `DrawQBlk` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4228 | `GetAreaObjectID` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4233 | `ExitDecBlock` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4237 | `HoleMetatiles` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4240 | `Hole_Empty` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4265 | `StrWOffset` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4266 | `NoWhirlP` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4273 | `RenderUnderPart` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4289 | `DrawThisRow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4290 | `WaitOneRow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4296 | `ExitUPartR` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4300 | `ChkLrgObjLength` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4303 | `ChkLrgObjFixedLength` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4310 | `LenSet` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4313 | `GetLrgObjAttrib` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4326 | `GetAreaObjXPosition` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4336 | `GetAreaObjYPosition` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4349 | `BlockBufferAddr` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S13 |
| 4353 | `GetBlockBufferAddr` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T17 S4; M2 T21 S4; M2 T24 S1; M2 T30 S13 |
| 4376 | `AreaDataOfsLoopback` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1 |
| 4381 | `LoadAreaPointer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4384 | `GetAreaType` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4392 | `FindAreaPointer` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4402 | `GetAreaDataAddrs` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4434 | `StoreFore` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4472 | `StoreStyle` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4485 | `WorldAddrOffsets` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4491 | `AreaAddrOffsets` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4492 | `World1Areas` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4493 | `World2Areas` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4494 | `World3Areas` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4495 | `World4Areas` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4496 | `World5Areas` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4497 | `World6Areas` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4498 | `World7Areas` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4499 | `World8Areas` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4509 | `EnemyAddrHOffsets` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4512 | `EnemyDataAddrLow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4520 | `EnemyDataAddrHigh` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4528 | `AreaDataHOffsets` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4531 | `AreaDataAddrLow` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4539 | `AreaDataAddrHigh` | M3 T27 S4 | existing closure backlog; Owner-approved root/frame/mode/area component move;maintenance only,no new conformance credit | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4550 | `E_CastleArea1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4558 | `E_CastleArea2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4565 | `E_CastleArea3` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4574 | `E_CastleArea4` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4583 | `E_CastleArea5` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4589 | `E_CastleArea6` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4598 | `E_GroundArea1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4606 | `E_GroundArea2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4613 | `E_GroundArea3` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4619 | `E_GroundArea4` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4627 | `E_GroundArea5` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4636 | `E_GroundArea6` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4643 | `E_GroundArea7` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4650 | `E_GroundArea8` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4656 | `E_GroundArea9` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4662 | `E_GroundArea10` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4666 | `E_GroundArea11` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4674 | `E_GroundArea12` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4679 | `E_GroundArea13` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4687 | `E_GroundArea14` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4695 | `E_GroundArea15` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4700 | `E_GroundArea16` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4704 | `E_GroundArea17` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4714 | `E_GroundArea18` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4722 | `E_GroundArea19` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4731 | `E_GroundArea20` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4738 | `E_GroundArea21` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4743 | `E_GroundArea22` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4751 | `E_UndergroundArea1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4760 | `E_UndergroundArea2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4769 | `E_UndergroundArea3` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4777 | `E_WaterArea1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4783 | `E_WaterArea2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4791 | `E_WaterArea3` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4799 | `L_CastleArea1` | M2 T30 S16 | existing closure backlog; Accepted transfer-116: castle scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S16 |
| 4814 | `L_CastleArea2` | M2 T30 S16 | existing closure backlog; Accepted transfer-116: castle scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S16 |
| 4832 | `L_CastleArea3` | M2 T30 S16 | existing closure backlog; Accepted transfer-116: castle scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S16 |
| 4849 | `L_CastleArea4` | M2 T30 S16 | existing closure backlog; Accepted transfer-116: castle scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S16 |
| 4865 | `L_CastleArea5` | M2 T30 S16 | existing closure backlog; Accepted transfer-116: castle scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S16 |
| 4884 | `L_CastleArea6` | M2 T30 S16 | existing closure backlog; Accepted transfer-116: castle scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S16 |
| 4900 | `L_GroundArea1` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 4915 | `L_GroundArea2` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 4931 | `L_GroundArea3` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 4944 | `L_GroundArea4` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 4963 | `L_GroundArea5` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 4980 | `L_GroundArea6` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 4995 | `L_GroundArea7` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5009 | `L_GroundArea8` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5027 | `L_GroundArea9` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5042 | `L_GroundArea10` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5048 | `L_GroundArea11` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5059 | `L_GroundArea12` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5066 | `L_GroundArea13` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5081 | `L_GroundArea14` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5096 | `L_GroundArea15` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5113 | `L_GroundArea16` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5123 | `L_GroundArea17` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5143 | `L_GroundArea18` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5160 | `L_GroundArea19` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5177 | `L_GroundArea20` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5191 | `L_GroundArea21` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5200 | `L_GroundArea22` | M2 T30 S17 | existing closure backlog; Accepted transfer-118: ground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S17 |
| 5210 | `L_UndergroundArea1` | M2 T30 S18 | existing closure backlog; Accepted transfer-119: underground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S18 |
| 5231 | `L_UndergroundArea2` | M2 T30 S18 | existing closure backlog; Accepted transfer-119: underground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S18 |
| 5252 | `L_UndergroundArea3` | M2 T30 S18 | existing closure backlog; Accepted transfer-119: underground scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S18 |
| 5271 | `L_WaterArea1` | M2 T30 S19 | existing closure backlog; Accepted transfer-120: water scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S19 |
| 5282 | `L_WaterArea2` | M2 T30 S19 | existing closure backlog; Accepted transfer-120: water scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S19 |
| 5299 | `L_WaterArea3` | M2 T30 S19 | existing closure backlog; Accepted transfer-120: water scene data and full parser consumption. | M2 T21 S4; M2 T24 S1; M2 T30 S19 |
| 5315 | `GameMode` | M2 T70 S17 | existing closure backlog; P15 same-class omitted JumpEngine scratch call correction. | M2 T15 S3; M2 T24 S1; M2 T31 S1 |
| 5326 | `GameCoreRoutine` | M2 T31 S1 | existing closure backlog; Accepted transfer-121: exact game entry chain. | M2 T15 S3; M2 T24 S1; M2 T31 S1 |
| 5336 | `GameEngine` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T15 / S not recorded; M2 T15 S3; M2 T17 S4; M2 T19 / S not recorded; M2 T19 S2; M2 T20 S1; M2 T22 S4; M2 T24 S1; M2 T31 S2; M2 T8 / S not recorded |
| 5339 | `ProcELoop` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T24 S1; M2 T31 S2 |
| 5371 | `NoChgMus` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T24 S1; M2 T31 S2 |
| 5377 | `CycleTwo` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T24 S1; M2 T31 S2 |
| 5380 | `ClrPlrPal` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T24 S1; M2 T31 S2 |
| 5381 | `SaveAB` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T24 S1; M2 T31 S2; M2 T8 / S not recorded |
| 5385 | `UpdScrollVar` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T15 S3; M2 T24 S1; M2 T31 S2 |
| 5398 | `RunParser` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T24 S1; M2 T31 S2 |
| 5399 | `ExitEng` | M2 T31 S2 | existing closure backlog; Accepted transfer-122: GameEngine caller chain. | M2 T24 S1; M2 T31 S2 |
| 5403 | `ScrollHandler` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T15 S3; M2 T24 S1 |
| 5422 | `ChkNearMid` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T24 S1 |
| 5427 | `ScrollScreen` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T15 S3; M2 T24 S1 |
| 5451 | `InitScrlAmt` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T24 S1 |
| 5453 | `ChkPOffscr` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T24 S1 |
| 5463 | `KeepOnscr` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T24 S1 |
| 5475 | `InitPlatScrl` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T24 S1 |
| 5479 | `X_SubtracterData` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T24 S1 |
| 5482 | `OffscrJoypadBitsData` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T24 S1 |
| 5487 | `GetScreenPosition` | M3 T27 S2 | existing closure backlog; Owner-approved T27 PPU-state maintenance migration;no new conformance credit | M2 T24 S1 |
| 5499 | `GameRoutines` | M2 T70 S17 | existing closure backlog; P15 same-class omitted JumpEngine scratch call correction. | M2 T24 S1 |
| 5519 | `PlayerEntrance` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T24 S1 |
| 5532 | `ChkBehPipe` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T24 S1 |
| 5536 | `IntroEntr` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T24 S1 |
| 5541 | `EntrMode2` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T24 S1 |
| 5549 | `VineEntr` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T24 S1 |
| 5562 | `OffVine` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T24 S1 |
| 5567 | `PlayerRdy` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T24 S1 |
| 5575 | `ExitEntr` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T24 S1 |
| 5580 | `AutoControlPlayer` | M2 T31 S4 | existing closure backlog; Accepted planned entry-mode chain, transfer-133 | M2 T15 S3; M2 T24 S1 |
| 5583 | `PlayerCtrlRoutine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T23 / S not recorded; M2 T23 S2; M2 T24 S1 |
| 5595 | `DisJoyp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5597 | `SaveJoyp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5615 | `SizeChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5623 | `ChkMoveDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5629 | `SetMoveDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5630 | `PlayerSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5649 | `PlayerHole` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5661 | `HoleDie` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5670 | `HoleBottom` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5672 | `ChkHoleX` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5680 | `ExitCtrl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5682 | `CloudExit` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5691 | `Vine_AutoClimb` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5697 | `AutoClimb` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5702 | `SetEntr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5708 | `VerticalPipeEntry` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5722 | `MovePlayerYAxis` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5730 | `SideExitPipeEntry` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5733 | `ChgAreaPipe` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5736 | `ChgAreaMode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5740 | `ExitCAPipe` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5742 | `EnterSidePipe` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5751 | `RightPipe` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5757 | `PlayerChangeSize` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5762 | `EndChgSize` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5765 | `ExitChgSize` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5769 | `PlayerInjuryBlink` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5776 | `ExitBlink` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5778 | `InitChangeSize` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5786 | `ExitBoth` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5791 | `PlayerDeath` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5797 | `DonePlayerTask` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5804 | `PlayerFireFlower` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5812 | `CyclePlayerPalette` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5821 | `ResetPalFireFlower` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5824 | `ResetPalStar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5830 | `ExitDeath` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5835 | `FlagpoleSlide` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1; M2 T6 / S not recorded |
| 5847 | `SlidePlayer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5848 | `NoFPObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5853 | `Hidden1UpCoinAmts` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5856 | `PlayerEndLevel` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1; M2 T6 / S not recorded |
| 5868 | `ChkStop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5874 | `InCastle` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5876 | `RdyNextA` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5888 | `NextArea` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S3; M2 T24 S1 |
| 5895 | `ExitNA` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5899 | `PlayerMovementSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T23 S1; M2 T24 S1 |
| 5907 | `SetCrouch` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5908 | `ProcMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5916 | `MoveSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5923 | `NoMoveSub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5928 | `OnGroundStateSub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5933 | `GndMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5940 | `FallingSub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T24 S1 |
| 5947 | `JumpSwimSub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T24 S1 |
| 5959 | `DumpFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5961 | `ProcSwim` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5969 | `LRWater` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5972 | `LRAir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T24 S1 |
| 5975 | `JSMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5982 | `ExitMov1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5986 | `ClimbAdderLow` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5988 | `ClimbAdderHigh` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 5991 | `ClimbingSub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6000 | `MoveOnVine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6019 | `ClimbFD` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6022 | `CSetFDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6032 | `ExitCSub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6033 | `InitCSTimer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6039 | `JumpMForceData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6042 | `FallMForceData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6045 | `PlayerYSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6048 | `InitMForceData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6051 | `MaxLeftXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6054 | `MaxRightXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6058 | `FrictionData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6061 | `Climb_Y_SpeedData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6064 | `Climb_Y_MForceData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6067 | `PlayerPhysicsSub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6079 | `ProcClimb` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6086 | `SetCAnim` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6089 | `CheckForJumping` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6097 | `NoJump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6099 | `ProcJumping` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6109 | `InitJS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6133 | `ChkWtr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6141 | `GetYPhy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6159 | `PJumpSnd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6163 | `SJumpSnd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6164 | `X_Physics` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6172 | `ProcPRun` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6184 | `ChkRFast` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6191 | `FastXSp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6193 | `SetRTmr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6195 | `GetXPhy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6201 | `GetXPhy2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6213 | `ExitPhy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6217 | `PlayerAnimTmrData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6220 | `GetPlayerAnimSpeed` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6229 | `ChkSkid` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6236 | `SetRunSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6238 | `ProcSkid` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6246 | `SetAnimSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6252 | `ImposeFriction` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T23 S1; M2 T23 S2; M2 T24 S1 |
| 6260 | `JoypFrict` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6262 | `LeftFrict` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T23 S1; M2 T23 S2; M2 T24 S1 |
| 6274 | `RghtFrict` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T23 S1; M2 T23 S2; M2 T24 S1 |
| 6285 | `XSpdSign` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6290 | `SetAbsSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6298 | `ProcFireball_Bubble` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 / S not recorded; M2 T20 S1; M2 T20 S2; M2 T20 S3; M2 T21 S6; M2 T24 / S not recorded; M2 T24 S1 |
| 6330 | `ProcFireballs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6336 | `ProcAirBubbles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S6; M2 T24 S1 |
| 6340 | `BublLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6347 | `BublExit` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6349 | `FireballXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6352 | `FireballObjCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T17 S2; M2 T17 S5; M2 T20 / S not recorded; M2 T20 S1; M2 T20 S2; M2 T21 S6; M2 T24 / S not recorded; M2 T24 S1 |
| 6380 | `RunFB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6401 | `EraseFB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6403 | `NoFBall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6405 | `FireballExplosion` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S6; M2 T24 S1 |
| 6409 | `BubbleCheck` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T20 S1; M2 T21 S6; M2 T24 S1 |
| 6419 | `SetupBubble` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6425 | `PosBubl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6440 | `MoveBubl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6450 | `Y_Bubl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6451 | `ExitBubl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6453 | `Bubble_MForceData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6456 | `BubbleTimerData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6461 | `RunGameTimer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S3; M2 T19 S5; M2 T21 S6; M2 T24 S1 |
| 6486 | `ResGTCtrl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6494 | `TimeUpOn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6497 | `ExGTimer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6501 | `WarpZoneObject` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S6; M2 T24 S1 |
| 6519 | `ProcessWhirlpools` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 6526 | `WhLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6546 | `NextWh` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6548 | `ExitWh` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6550 | `WhirlpoolActivate` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 6577 | `LeftWh` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6586 | `SetPWh` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6587 | `WhPull` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6598 | `FlagpoleScoreMods` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6601 | `FlagpoleScoreDigits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6604 | `FlagpoleRoutine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S6; M2 T22 S1; M2 T22 S4; M2 T24 S1 |
| 6635 | `SkipScore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6636 | `GiveFPScr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6643 | `FPGfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S6; M2 T22 S4; M2 T24 S1 |
| 6646 | `ExitFlagP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6650 | `Jumpspring_Y_PosData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6653 | `JumpspringHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T24 S1 |
| 6667 | `DownJSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6669 | `PosJSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6682 | `BounceJS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6688 | `DrawJSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6698 | `ExJSpring` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6702 | `Setup_Vine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 6716 | `NextVO` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6727 | `VineHeightData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6730 | `VineObjectHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T22 S1; M2 T24 S1 |
| 6746 | `RunVSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6752 | `VDrawLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6760 | `KillVine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6766 | `WrCMTile` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6780 | `ExitVH` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6785 | `CannonBitmasks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6788 | `ProcessCannons` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 6792 | `ThreeSChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6809 | `FireCannon` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6832 | `Chk_BB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6840 | `Next3Slt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6842 | `ExCannon` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6846 | `BulletBillXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6849 | `BulletBillHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T22 S1; M2 T24 S1 |
| 6862 | `SetupBB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6876 | `ChkDSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6880 | `BBFly` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6881 | `RunBBSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6886 | `KillBB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6891 | `HammerEnemyOfsData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6895 | `HammerXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6898 | `SpawnHammerObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6904 | `SetMOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6919 | `NoHammer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6928 | `ProcHammerObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 6952 | `SetHSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6962 | `SetHPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6977 | `RunAllH` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6978 | `RunHSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 6988 | `CoinBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 7000 | `SetupJumpCoin` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T21 S5; M2 T22 S1; M2 T24 S1 |
| 7014 | `JCoinC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T21 S5; M2 T22 S1; M2 T24 S1 |
| 7025 | `FindEmptyMiscSlot` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T22 S1; M2 T24 S1 |
| 7027 | `FMiscLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7033 | `UseMiscS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7038 | `MiscObjectsCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T16 S3; M2 T22 S1; M2 T22 S4; M2 T24 S1 |
| 7040 | `MiscLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7053 | `ProcJumpCoin` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T22 S1; M2 T24 S1 |
| 7071 | `JCoinRun` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7088 | `RunJCSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7093 | `MiscLoopBack` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7100 | `CoinTallyOffsets` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7103 | `ScoreOffsets` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7106 | `StatusBarNybbles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7109 | `GiveOneCoin` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7125 | `CoinPoints` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7129 | `AddToScore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7134 | `GetSBNybbles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7138 | `UpdateNumber` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7145 | `NoZSup` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7150 | `SetupPowerUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 7163 | `PwrUpJmp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7175 | `StrType` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7176 | `PutBehind` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7184 | `PowerUpObjHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T22 S1; M2 T24 S1 |
| 7202 | `ShroomM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7206 | `GrowThePowerUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 7223 | `ChkPUSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7226 | `RunPUSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T22 S1; M2 T24 S1 |
| 7232 | `ExitPUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7241 | `BlockYPosAdderData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7244 | `PlayerHeadCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T22 S1; M2 T24 S1 |
| 7251 | `DBlockSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7265 | `ChkBrick` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7274 | `StartBTmr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7279 | `ContBTmr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7282 | `PutOldMT` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7283 | `PutMTileB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7297 | `SmallBP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7298 | `BigBP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7308 | `Unbreak` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7309 | `InvOBit` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7316 | `InitBlock_XY_Pos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T22 S1; M2 T24 S1 |
| 7332 | `BumpBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 7349 | `BlockCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S6; M2 T22 S1; M2 T24 S1 |
| 7363 | `MushFlowerBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7367 | `StarBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7371 | `ExtraLifeMushBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7376 | `VineBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7381 | `ExitBlockChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7386 | `BrickQBlockMetatiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S6; M2 T18 S2; M2 T22 S1; M2 T24 S1 |
| 7393 | `BlockBumpedChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S6; M2 T22 S1; M2 T22 S2; M2 T24 S1 |
| 7395 | `BumpChkLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7400 | `MatchBump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7404 | `BrickShatter` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 7420 | `CheckTopOfBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 7437 | `TopEx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7441 | `SpawnBrickChunks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 7468 | `BlockObjectsCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T16 S1; M2 T16 S2; M2 T17 S1; M2 T17 S6; M2 T22 S1; M2 T24 S1 |
| 7500 | `ChkTop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7506 | `BouncingBlockHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T22 S1; M2 T24 S1 |
| 7519 | `KillBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7520 | `UpdSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 7527 | `BlockObjMT_Updater` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T18 / S not recorded; M2 T18 S1; M2 T22 S1; M2 T24 S1 |
| 7529 | `UpdateLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 7546 | `NextBUpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S4; M2 T24 S1 |
| 7555 | `MoveEnemyHorizontally` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 / S not recorded; M2 T17 S2; M2 T21 S3; M2 T24 S1 |
| 7561 | `MovePlayerHorizontally` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T17 / S not recorded; M2 T21 S3; M2 T24 S1 |
| 7566 | `MoveObjectHorizontally` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 / S not recorded; M2 T17 S2; M2 T20 S2; M2 T21 S3; M2 T24 S1 |
| 7581 | `SaveXSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7586 | `UseAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7604 | `ExXMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7611 | `MovePlayerVertically` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7617 | `NoJSChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7624 | `MoveD_EnemyVertically` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T19 S2; M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 7630 | `MoveFallingPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7632 | `ContVMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7636 | `MoveRedPTroopaDown` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7640 | `MoveRedPTroopaUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7643 | `MoveRedPTroopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7656 | `MoveDropPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7660 | `MoveEnemySlowVert` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 7662 | `SetMdMax` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7667 | `MoveJ_EnemyVertically` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 7669 | `SetHiMax` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S2; M2 T21 S3; M2 T24 S1 |
| 7670 | `SetXMoveAmt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 7678 | `MaxSpdBlockData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7681 | `ResidualGravityCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7685 | `ImposeGravityBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 / S not recorded; M2 T17 S1; M2 T21 S3; M2 T24 S1 |
| 7691 | `ImposeGravitySprObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 / S not recorded; M2 T17 S5; M2 T19 S2; M2 T21 S3; M2 T24 S1 |
| 7698 | `MovePlatformDown` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7702 | `MovePlatformUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7711 | `SetDplSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7719 | `RedPTroopaGrav` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7729 | `ImposeGravity` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T17 / S not recorded; M2 T17 S1; M2 T17 S2; M2 T20 S2; M2 T21 S3; M2 T24 S1 |
| 7739 | `AlterYP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 / S not recorded; M2 T21 S3; M2 T24 S1 |
| 7761 | `ChkUpM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 7784 | `ExVMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 / S not recorded; M2 T21 S3; M2 T24 S1 |
| 7788 | `EnemiesAndLoopsCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 / S not recorded; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7796 | `ChkAreaTsk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7801 | `ChkBowserF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7807 | `ExitELCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7812 | `LoopCmdWorldNumber` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7815 | `LoopCmdPageNumber` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7818 | `LoopCmdYPosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7821 | `ExecGameLoopback` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7851 | `ProcLoopCommand` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7857 | `FindLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7875 | `IncMLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7883 | `WrongChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7886 | `DoLpBack` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7888 | `InitMLp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7891 | `InitLCmd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7896 | `ChkEnemyFrenzy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7911 | `ProcessEnemyData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S6; M2 T19 / S not recorded; M2 T19 S1; M2 T19 S2; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7918 | `CheckEndofBuffer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S2; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7931 | `CheckRightBounds` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7950 | `CheckPageCtrlRow` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 7967 | `PositionEnemyObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7983 | `CheckRightExtBounds` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8006 | `CheckForEnemyGroup` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8014 | `BuzzyBeetleMutate` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8020 | `StrID` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8028 | `CheckFrenzyBuffer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8035 | `StrFre` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8037 | `InitEnemyObject` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8041 | `ExEPar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8043 | `DoGroup` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8046 | `ParseRow0e` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8064 | `NotUse` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8066 | `CheckThreeBytes` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8072 | `Inc3B` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8073 | `Inc2B` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8080 | `CheckpointEnemyID` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8092 | `InitEnemyRoutines` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8158 | `NoInitCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8163 | `InitGoomba` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8169 | `InitPodoboo` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8181 | `InitRetainerObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8188 | `NormalXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8191 | `InitNormalEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8196 | `GetESpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8197 | `SetESpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8202 | `InitRedKoopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8210 | `HBroWalkingTimerData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8213 | `InitHammerBro` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8225 | `InitHorizFlySwimEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8231 | `InitBloober` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8234 | `SmallBBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8239 | `InitRedPTroopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8245 | `GetCent` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8248 | `TallBBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8249 | `SetBBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8252 | `InitVStf` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S5; M2 T24 S1 |
| 8259 | `InitBulletBill` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8268 | `InitCheepCheep` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8279 | `InitLakitu` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8283 | `SetupLakitu` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8289 | `KillLakitu` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8295 | `PRDiffAdjustData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8300 | `LakituAndSpinyHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8308 | `ChkLak` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8318 | `ChkNoEn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8323 | `CreateL` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8330 | `RetEOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8331 | `ExLSHand` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8335 | `CreateSpiny` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8355 | `DifLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8376 | `UsePosv` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8377 | `SetSpSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8383 | `SpinyRte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8390 | `ChpChpEx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8394 | `FirebarSpinSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8397 | `FirebarSpinDirData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8400 | `InitLongFirebar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8403 | `InitShortFirebar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8430 | `FlyCCXPositionData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8436 | `FlyCCXSpeedData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8441 | `FlyCCTimerData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8444 | `InitFlyingCheepCheep` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8457 | `MaxCC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8473 | `GSeed` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8483 | `RSeed` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8503 | `D2XPos1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8513 | `D2XPos2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8519 | `FinCCSt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8529 | `InitBowser` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8551 | `DuplicateEnemyObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8553 | `FSLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8569 | `FlmEx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8573 | `FlameYPosData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8576 | `FlameYMFAdderData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8579 | `InitBowserFlame` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8597 | `SetFrT` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8604 | `PutAtRightExtent` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8615 | `SpawnFromMouth` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8635 | `SetMF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8640 | `FinishFlame` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8653 | `FireworksXPosData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8656 | `FireworksYPosData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8659 | `InitFireworks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8666 | `StarFChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8697 | `ExitFWk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8701 | `Bitmasks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8704 | `Enemy17YPosData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8707 | `SwimCC_IDData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8710 | `BulletBillCheepCheep` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8722 | `ChkW2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8726 | `Get17ID` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8730 | `Set17ID` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8736 | `GetRBit` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8738 | `ChkRBit` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8746 | `AddFBit` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8755 | `DoBulletBills` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8757 | `BB_SLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8765 | `ExF17` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8767 | `FireBulletBill` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8780 | `HandleGroupEnemies` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8792 | `PullID` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8793 | `SnglID` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8798 | `SetYGp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8808 | `CntGrp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8809 | `GrLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8810 | `GSltLp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8835 | `NextED` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8839 | `InitPiranhaPlant` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8855 | `InitEnemyFrenzy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8872 | `NoFrenzyCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8877 | `EndFrenzy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8879 | `LakituChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8884 | `NextFSlot` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8893 | `InitJumpGPTroopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8898 | `TallBBox2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8899 | `SetBBox2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8904 | `InitBalPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8911 | `AlignP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8917 | `SetBPA` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8925 | `InitDropPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8932 | `InitHoriPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8939 | `InitVertPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8947 | `SetYO` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8955 | `CommonPlatCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8957 | `SPBBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8964 | `CasPBB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8969 | `LargeLiftUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8973 | `LargeLiftDown` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8976 | `LargeLiftBBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8981 | `PlatLiftUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8990 | `PlatLiftDown` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 8998 | `CommonSmallLift` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9007 | `PlatPosDataLow` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9010 | `PlatPosDataHigh` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9013 | `PosPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9025 | `EndOfEnemyInitCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9030 | `RunEnemyObjectsCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9038 | `JmpEO` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9080 | `NoRunCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9085 | `RunRetainerObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9092 | `RunNormalEnemies` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T19 S4; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 9105 | `SkipMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9107 | `EnemyMovementSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9135 | `NoMoveCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9140 | `RunBowserFlame` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9150 | `RunFirebarObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9156 | `RunSmallPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S5; M2 T24 S1; M2 T5 / S not recorded |
| 9168 | `RunLargePlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S5; M2 T24 S1; M2 T5 / S not recorded |
| 9176 | `SkipPT` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9182 | `LargePlatformSubroutines` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9198 | `EraseEnemyObject` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9212 | `MovePodoboo` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9224 | `PdbM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9229 | `HammerThrowTmrData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9232 | `XSpeedAdderData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9235 | `RevivedXSpeed` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9238 | `ProcHammerBro` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9243 | `ChkJH` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9260 | `DecHT` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9263 | `HammerBroJumpLData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9266 | `HammerBroJumpCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9285 | `SetHJ` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9295 | `HJump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9301 | `MoveHammerBroXDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9307 | `Shimmy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9316 | `SetShim` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9318 | `MoveNormalEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 9336 | `FallE` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 9347 | `MEHor` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9349 | `SlowM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9350 | `SteadM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9355 | `AddHS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9363 | `ReviveStunned` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9377 | `SetRSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9381 | `MoveDefeatedEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9385 | `ChkKillGoomba` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9392 | `NKGmba` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9396 | `MoveJumpingEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S5; M2 T24 S1 |
| 9402 | `ProcMoveRedPTroopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9414 | `NoIncPT` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9416 | `MoveRedPTUpOrDown` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9421 | `MovPTDwn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9427 | `MoveFlyGreenPTroopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9438 | `YSway` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9443 | `NoMGPT` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9445 | `XMoveCntr_GreenPTroopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9448 | `XMoveCntr_Platform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9460 | `NoIncXM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9461 | `IncPXM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9463 | `DecSeXM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9468 | `MoveWithXMCntrs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9481 | `XMRight` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9490 | `BlooberBitmasks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9493 | `MoveBloober` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9506 | `FBLeft` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9510 | `SBMDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9512 | `BlooberSwim` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9520 | `SwimX` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9532 | `LeftSwim` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9542 | `MoveDefeatedBloober` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S5; M2 T24 S1 |
| 9545 | `ProcSwimmingB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9565 | `BSwimE` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9567 | `SlowSwim` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9579 | `NoSSw` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9581 | `ChkForFloatdown` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9585 | `Floatdown` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9590 | `NoFD` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9592 | `ChkNearPlayer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9603 | `MoveBulletBill` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9608 | `NotDefB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9616 | `SwimCCXMoveData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9620 | `MoveSwimmingCheepCheep` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S5; M2 T24 S1 |
| 9625 | `CCSwim` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9660 | `CCSwimUpwards` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9671 | `ChkSwimYPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9682 | `YPDiff` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9686 | `ExSwCC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9703 | `FirebarPosLookupTbl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9716 | `FirebarMirrorData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9719 | `FirebarTblOffsets` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9723 | `FirebarYPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9726 | `ProcFirebar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9737 | `SusFbar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9745 | `SkpFSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9748 | `SetupGFB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9766 | `SetMFbar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9769 | `DrawFbar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9778 | `NextFbar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9782 | `SkipFBar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9784 | `DrawFirebar_Collision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9793 | `AddHA` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9803 | `SubtR1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9805 | `ChkFOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9809 | `VAHandl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9817 | `AddVA` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9819 | `SetVFbr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9822 | `FirebarCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9838 | `AdjSm` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9844 | `BigJp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9845 | `FBCLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9851 | `ChkVFBD` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9866 | `ChkFBCl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9868 | `Chk2Ofs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9877 | `ChgSDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9882 | `SetSDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9889 | `NoColFB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9896 | `GetFirebarPosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9904 | `GetHAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9922 | `GetVAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9941 | `PRandomSubtracter` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9944 | `FlyCCBPriority` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9947 | `MoveFlyingCheepCheep` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 9954 | `FlyCC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9971 | `AddCCF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9982 | `BPGet` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9990 | `LakituDiffAdj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 9993 | `MoveLakitu` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 9998 | `ChkLS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10005 | `Fr12S` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10008 | `LdLDa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10013 | `SetLSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10024 | `SetLMov` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10027 | `PlayerLakituDiff` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 10037 | `ChkLakDif` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10053 | `SetLMovD` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10055 | `ChkPSpeed` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10073 | `ChkSpinyO` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10078 | `ChkEmySpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10081 | `SubDifAdj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10083 | `SPixelLak` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10087 | `ExMoveLak` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10092 | `BridgeCollapseData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10098 | `BridgeCollapse` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10111 | `SetM2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10116 | `MoveD_Bowser` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10120 | `RemoveBridge` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10152 | `NoBFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10156 | `PRandomRange` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10159 | `RunBowser` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10167 | `KillAllEnemies` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10169 | `KillLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10176 | `BowserControl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10182 | `ChkMouth` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10185 | `FeetTmr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10192 | `ResetMDr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10197 | `B_FaceP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10211 | `GetPRCmp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10222 | `GetDToO` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10237 | `CompDToO` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10240 | `HammerChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10250 | `SetHmrTmr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10258 | `SkipToFB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10259 | `MakeBJump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10265 | `ChkFireB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10270 | `SpawnFBr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10283 | `SetFBTmr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10289 | `BowserGfxHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10296 | `CopyFToR` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10321 | `ExBGfxH` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10323 | `ProcessBowserHalf` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10337 | `FlameTimerData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10340 | `SetFlameTimer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10347 | `ExFl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10349 | `ProcBowserFlame` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10356 | `SFlmX` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10374 | `SetGfxF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10384 | `FlmeAt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10388 | `DrawFlameLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10417 | `M3FOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10423 | `M2FOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10429 | `M1FOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10434 | `ExFlmeD` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10438 | `RunFireworks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S3; M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10447 | `SetupExpl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10457 | `FireworksSoundScore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10468 | `StarFlagYPosAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10471 | `StarFlagXPosAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10474 | `StarFlagTileData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10477 | `RunStarFlagObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T18 S2; M2 T19 S3; M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10491 | `GameTimerFireworks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10503 | `SetFWC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10506 | `IncrementSFTask1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10509 | `StarFlagExit` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T18 S2; M2 T21 S5; M2 T24 / S not recorded; M2 T24 S1 |
| 10512 | `AwardGameTimerPoints` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10522 | `NoTTick` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10529 | `EndAreaPoints` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10534 | `ELPGive` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10543 | `RaiseFlagSetoffFWorks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10549 | `SetoffF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10555 | `DrawStarFlag` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T18 S2; M2 T21 S5; M2 T24 S1 |
| 10559 | `DSFLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10580 | `DrawFlagSetTimer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10585 | `IncrementSFTask2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10589 | `DelayToAreaEnd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10596 | `StarFlagExit2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10602 | `MovePiranhaPlant` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10619 | `ChkPlayerNearPipe` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10624 | `ReversePlantSpeed` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10632 | `SetupToMovePPlant` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10638 | `RiseFallPiranhaPlant` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10656 | `PutinPipe` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10664 | `FirebarSpin` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10677 | `SpinCounterClockwise` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10692 | `BalancePlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10697 | `DoBPl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10701 | `CheckBalPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10709 | `ChkForFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10720 | `MakePlatformFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10723 | `ChkOtherForFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10733 | `ChkToMoveBalPlat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10750 | `ColFlg` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10752 | `PlatUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10754 | `PlatSt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10756 | `PlatDn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10758 | `DoOtherPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10771 | `DrawEraseRope` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10796 | `EraseR1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10800 | `OtherRope` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10819 | `EraseR2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10822 | `EndRp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10828 | `ExitRp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10831 | `SetupPlatformRope` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10840 | `GetLRp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10857 | `GetHRp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10883 | `ExPRp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10885 | `InitPlatformFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10898 | `StopPlatforms` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10904 | `PlatformFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10916 | `ExPF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10921 | `YMovingPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10933 | `SkipIY` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10935 | `ChkYCenterPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10941 | `YMDown` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10943 | `ChkYPCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10947 | `ExYPl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10952 | `XMovingPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10959 | `PositionPlayerOnHPlat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10969 | `PPHSubt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10970 | `SetPVar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10973 | `ExXMP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10977 | `DropPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10982 | `ExDPl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10987 | `RightPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10995 | `ExRPl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 10999 | `MoveLargeLiftPlat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11003 | `MoveSmallPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11007 | `MoveLiftPlatforms` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11019 | `ChkSmallPlatCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11023 | `ExLiftP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11031 | `OffscreenBoundsCheck` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11041 | `LimitB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11042 | `ExtendLB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11074 | `TooFar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11075 | `ExScrnBd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S5; M2 T24 S1 |
| 11085 | `FireballEnemyCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11101 | `FireballEnemyCDLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11115 | `GoombaDie` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11120 | `NotGoomba` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11135 | `NoFToECol` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11141 | `ExitFBallEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11145 | `BowserIdentities` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11148 | `HandleEnemyFBallCol` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11160 | `ChkBuzzyBeetle` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11167 | `HurtBowser` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11182 | `SetDBSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11189 | `ChkOtherEnemies` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11197 | `ShellOrBlockDefeat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11204 | `StnE` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11215 | `GoombaPoints` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11220 | `EnemySmackScore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11224 | `ExHCF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11228 | `PlayerHammerCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11256 | `ClHCol` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11258 | `ExPHC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11262 | `HandlePowerUpCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T18 S3; M2 T21 S3; M2 T24 S1 |
| 11279 | `Shroom_Flower_PUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11292 | `SetFor1Up` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11297 | `UpToSuper` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11302 | `UpToFiery` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T18 S3; M2 T21 S3; M2 T24 S1 |
| 11305 | `NoPUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11309 | `ResidualXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11312 | `KickedShellXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11315 | `DemotedKoopaXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11318 | `PlayerEnemyCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 11339 | `NoPECol` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11341 | `CheckForPUpCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11346 | `EColl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11350 | `KickedShellPtsData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11353 | `HandlePECollisions` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11398 | `KSPts` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11399 | `ExPEC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11401 | `ChkForPlayerInjury` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11405 | `ChkInj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11413 | `ChkETmrs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11421 | `TInjE` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11426 | `InjurePlayer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1; M2 T6 / S not recorded |
| 11430 | `ForceInjury` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11440 | `SetKRout` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11441 | `SetPRout` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11448 | `ExInjColRoutines` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11452 | `KillPlayer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1; M2 T6 / S not recorded |
| 11461 | `StompedEnemyPtsData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11464 | `EnemyStomped` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11490 | `EnemyStompedPts` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11506 | `ChkForDemoteKoopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11521 | `RevivalRateData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11524 | `HandleStompedShellE` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11536 | `SBnce` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11540 | `ChkEnemyFaceRight` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11545 | `LInj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11549 | `EnemyFacePlayer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11554 | `SFcRt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11558 | `SetupFloateyNumber` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 11566 | `ExSFN` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11571 | `SetBitsMask` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 11574 | `ClearBitsMask` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11577 | `EnemiesCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 11595 | `ECLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11629 | `YesEC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11632 | `NoEnemyCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11637 | `ReadyNextEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11644 | `ExitECRoutine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11648 | `ProcEnemyCollisions` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 11667 | `ShellCollisions` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11680 | `ExitProcessEColl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11683 | `ProcSecondEnemyColl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11701 | `MoveEOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11707 | `EnemyTurnAround` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11721 | `RXSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11729 | `ExTA` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11734 | `LargePlatformCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11748 | `ChkForPlayerC_LargeP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11762 | `ExLPC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11768 | `SmallPlatformCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11777 | `ChkSmallPlatLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11788 | `MoveBoundBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11799 | `ExSPC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11804 | `ProcSPlatCollisions` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11807 | `ProcLPlatCollisions` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11818 | `ChkForTopCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11834 | `SetCollisionFlag` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11841 | `PlatformSideCollisions` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11855 | `SideC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11856 | `NoSideC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11861 | `PlayerPosSPlatData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11864 | `PositionPlayerOnS_Plat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11871 | `PositionPlayerOnVPlat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11888 | `ExPlPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11892 | `CheckPlayerVertical` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11901 | `ExCPV` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11905 | `GetEnemyBoundBoxOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11908 | `GetEnemyBoundBoxOfsArg` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11924 | `PlayerBGUpperExtent` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11927 | `PlayerBGCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 11942 | `SetFallS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11943 | `SetPSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11944 | `ChkOnScr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11952 | `ExPBGCol` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11954 | `ChkCollSize` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11964 | `GBBAdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 11971 | `HeadChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 11992 | `SolidOrClimb` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 11997 | `NYSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12000 | `DoFootCheck` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12019 | `AwardTouchedCoin` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12022 | `ChkFootMTile` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 12030 | `ContChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12040 | `LandPlyr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12049 | `InitSteP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12052 | `DoPlayerSideCheck` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 12059 | `SideCheckLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12075 | `BHalf` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12086 | `ExSCH` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12088 | `CheckSideMTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12094 | `ContSChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12101 | `ChkPBtm` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12111 | `PipeDwnS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12115 | `PlyrPipe` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12124 | `SetCATmr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12126 | `ChkGERtn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12140 | `StopPlayerMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12142 | `ExCSM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12144 | `AreaChangeTimerData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12147 | `HandleCoinMetatile` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12152 | `HandleAxeMetatile` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1; M2 T6 / S not recorded |
| 12159 | `ErACM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12169 | `ClimbXPosAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12172 | `ClimbPLocAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12175 | `FlagpoleYPosData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12178 | `HandleClimbing` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12184 | `ExHC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12186 | `ChkForFlagpole` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12192 | `FlagpoleCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12212 | `ChkFlagpoleYPosLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12217 | `MtchF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12218 | `RunFR` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12222 | `VineCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12231 | `PutPlayerOnVine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12244 | `SetVXPl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12259 | `ExPVne` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12263 | `ChkInvisibleMTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12267 | `ExCInvT` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12273 | `ChkForLandJumpSpring` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12284 | `ExCJSp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12286 | `ChkJumpspringMetatiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12292 | `JSFnd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12293 | `NoJSFnd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12295 | `HandlePipeEntry` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1; M2 T6 / S not recorded |
| 12326 | `GetWNum` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12341 | `ExPipeE` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12343 | `ImpedePlayerMove` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 12354 | `RImpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12358 | `NXSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12365 | `PlatF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12372 | `ExIPM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12380 | `SolidMTileUpperExt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12383 | `CheckForSolidMTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12388 | `ClimbMTileUpperExt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12391 | `CheckForClimbMTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12396 | `CheckForCoinMTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12403 | `CoinSd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12407 | `GetMTileAttrib` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12415 | `ExEBG` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12420 | `EnemyBGCStateData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12423 | `EnemyBGCXSpdData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12426 | `EnemyToBGCollisionDet` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T19 S3; M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 12439 | `DoIDCheckBGColl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12443 | `HBChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12446 | `CInvu` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12452 | `YesIn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12455 | `NoEToBGCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12461 | `HandleEToBGCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12476 | `GiveOEPoints` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12480 | `ChkToStunEnemies` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12489 | `Demote` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12491 | `SetStun` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12503 | `SetWYSpd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12504 | `SetNotW` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12509 | `ChkBBill` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12515 | `NoCDirF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12518 | `ExEBGChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12523 | `LandEnemyProperly` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12535 | `SChkA` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12537 | `ChkLandedEnemyState` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12552 | `SetForStn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12556 | `ExSteChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12558 | `ProcEnemyDirection` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12571 | `InvtD` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12575 | `CNwCDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12580 | `LandEnemyInitState` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12589 | `NMovShellFallBit` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12597 | `ChkForRedKoopa` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12603 | `Chk2MSBSt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12610 | `GetSteFromD` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12611 | `SetD6Ste` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12617 | `DoEnemySideCheck` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12624 | `SdeCLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12632 | `NextSdeC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12636 | `ExESdeC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12638 | `ChkForBump_HammerBroJ` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12646 | `NoBump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12654 | `InvEnemyDir` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12660 | `PlayerEnemyDiff` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12671 | `EnemyLanding` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12679 | `SubtEnemyYPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12686 | `EnemyJump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12701 | `DoSide` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12705 | `HammerBroBGColl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12711 | `KillEnemyAboveBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12717 | `UnderHammerBro` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12726 | `NoUnderHammerBro` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12732 | `ChkUnderEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12737 | `ChkForNonSolids` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12747 | `NSFnd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12751 | `FireballBGCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 S1 |
| 12772 | `ClearBounceFlag` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12777 | `InitFireballExplode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12791 | `BoundBoxCtrlData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12805 | `GetFireballBoundBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T17 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 12813 | `GetMiscBoundBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T17 S3; M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12819 | `FBallB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12822 | `GetEnemyBoundBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T17 S3; M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 12828 | `SmallPlatformBoundBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12833 | `GetMaskedOffScrBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12844 | `CMBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12850 | `LargePlatformBoundBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12857 | `SetupEOffsetFBBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12866 | `MoveBoundBoxOffscreen` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12878 | `BoundingBoxCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T17 / S not recorded; M2 T17 S3; M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12916 | `CheckRightScreenBBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S3; M2 T21 S3; M2 T24 S1 |
| 12935 | `SORte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12936 | `NoOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12939 | `CheckLeftScreenBBox` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S3; M2 T21 S3; M2 T24 S1 |
| 12948 | `SOLft` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12949 | `NoOfs2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12956 | `PlayerCollisionCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S3; M2 T21 S3; M2 T24 S1 |
| 12959 | `SprObjectCollisionCore` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12964 | `CollisionCoreLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12979 | `SecondBoxVerticalChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 12989 | `FirstBoxGreater` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13002 | `NoCollisionFound` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13007 | `CollisionFound` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13023 | `BlockBufferChk_Enemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 13032 | `ResidualMiscObjectCode` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13040 | `BlockBufferChk_FBall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 13046 | `ResJmpM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13047 | `BBChk_E` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13052 | `BlockBufferAdderData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13055 | `BlockBuffer_X_Adder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13061 | `BlockBuffer_Y_Adder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13067 | `BlockBufferColli_Feet` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13070 | `BlockBufferColli_Head` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13074 | `BlockBufferColli_Side` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13078 | `BlockBufferCollision` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S3; M2 T17 S4; M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 13111 | `RetXC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13112 | `RetYC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13126 | `VineYPosAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13129 | `DrawVine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T22 S1; M2 T24 S1 |
| 13156 | `VineTL` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13169 | `SkpVTop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13170 | `ChkFTop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13177 | `NextVSp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13187 | `SixSpriteStacker` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13189 | `StkLp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13203 | `FirstSprXPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13206 | `FirstSprYPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13209 | `SecondSprXPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13212 | `SecondSprYPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13215 | `FirstSprTilenum` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13218 | `SecondSprTilenum` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13221 | `HammerSprAttrib` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13224 | `DrawHammer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S3; M2 T24 S1 |
| 13232 | `ForceHPose` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13234 | `GetHPose` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13239 | `RenderH` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13268 | `NoHOffscr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13277 | `FlagpoleScoreNumTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13284 | `FlagpoleGfxHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S6; M2 T21 S3; M2 T22 S4; M2 T24 S1 |
| 13326 | `ChkFlagOffscreen` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13335 | `MoveSixSpritesOffscreen` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13338 | `DumpSixSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13342 | `DumpFourSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13345 | `DumpThreeSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13348 | `DumpTwoSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 13352 | `ExitDumpSpr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13357 | `DrawLargePlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13374 | `ShrinkPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13377 | `SetLast2Platform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13386 | `SetPlatformTilenum` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13402 | `SChk2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13408 | `SChk3` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13414 | `SChk4` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13420 | `SChk5` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13426 | `SChk6` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13431 | `SLChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13435 | `ExDLPl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13439 | `DrawFloateyNumber_Coin` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13444 | `NotRsNum` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13460 | `JumpingCoinTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13463 | `JCoinGfxHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13489 | `ExJCGfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13500 | `PowerUpGfxTable` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13506 | `PowerUpAttributes` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13509 | `DrawPowerUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 13530 | `PUpDrawLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13555 | `FlipPUpRightSide` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13562 | `PUpOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13576 | `EnemyGraphicsTable` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13621 | `EnemyGfxTableOffsets` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13627 | `EnemyAttributeData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13633 | `EnemyAnimTimingBMask` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13636 | `JumpspringFrameOffsets` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13639 | `EnemyGfxHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T19 S4; M2 T21 S3; M2 T24 S1 |
| 13661 | `CheckForRetainerObj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13674 | `CheckForBulletBillCV` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13682 | `SBBAt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13687 | `CheckForJumpspring` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13694 | `CheckForPodoboo` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13704 | `CheckBowserGfxFlag` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13711 | `SBwsrGfxOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13713 | `CheckForGoomba` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13722 | `GmbaAnim` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13732 | `CheckBowserFront` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13746 | `ChkFrontSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13750 | `FlipBowserOver` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13753 | `DrawBowser` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13756 | `CheckBowserRear` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13761 | `ChkRearSte` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13770 | `CheckForSpiny` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13780 | `NotEgg` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13782 | `CheckForLakitu` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13792 | `NoLAFr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13794 | `CheckUpsideDownShell` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13807 | `CheckRightSideUpShell` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 13819 | `CheckForDefdGoomba` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 13829 | `CheckForHammerBro` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13841 | `CheckForBloober` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13856 | `CheckToAnimateEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13878 | `CheckForSecondFrame` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13883 | `CheckAnimationStop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13893 | `CheckDefeatedState` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13905 | `DrawEnemyObject` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13916 | `SkipToOffScrChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13919 | `CheckForVerticalFlip` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13943 | `FlipEnemyVertically` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13957 | `CheckForESymmetry` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13965 | `ContES` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13975 | `ESRtnr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13979 | `SpnySC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 13982 | `MirrorEnemyGfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 13994 | `EggExc` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14007 | `CheckToMirrorLakitu` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14026 | `NVFLak` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14033 | `CheckToMirrorJSpring` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14044 | `SprObjectOffscrChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14054 | `LcChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14060 | `Row3C` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14067 | `Row23C` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14073 | `AllRowC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14085 | `ExEGHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14088 | `DrawEnemyObjRow` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14093 | `DrawOneSpriteRow` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14097 | `MoveESprRowOffscreen` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14104 | `MoveESprColOffscreen` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14119 | `DefaultBlockObjTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14122 | `DrawBlock` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S1; M2 T16 S2; M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 14133 | `DBlkLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14147 | `ChkRep` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14159 | `SetBFlip` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14167 | `BlkOffscr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14174 | `PullOfsB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14175 | `ChkLeftCo` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14178 | `MoveColOffscreen` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14182 | `ExDBlk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14187 | `DrawBrickChunks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T21 S3; M2 T24 S1 |
| 14197 | `DChunks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14242 | `ChnkOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14250 | `ExBCDr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14254 | `DrawFireball` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14261 | `DrawFirebar` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14275 | `FireA` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14280 | `ExplosionTiles` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14283 | `DrawExplosion_Fireball` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14292 | `DrawExplosion_Fireworks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14327 | `KillFireBall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14334 | `DrawSmallPlatform` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14361 | `TopSP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14369 | `BotSP` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14379 | `SOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14386 | `SOfs2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14392 | `ExSPl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14397 | `DrawBubble` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S3; M2 T24 S1 |
| 14413 | `ExDBub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14418 | `PlayerGfxTblOffsets` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S3; M2 T24 S1 |
| 14424 | `PlayerGraphicsTable` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14457 | `SwimKickTileNum` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14460 | `PlayerGfxHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S3; M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14466 | `CntPl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14489 | `SwimKT` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14495 | `BigKTS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14497 | `ExPGH` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14499 | `FindPlayerAction` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14503 | `DoChangeSize` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14507 | `PlayerKilled` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14511 | `PlayerGfxProcessing` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14532 | `SUpdR` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14535 | `PlayerOffscreenChk` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 14547 | `PROfsLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 / S not recorded; M2 T24 S1 |
| 14551 | `NPROffscr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 / S not recorded; M2 T24 S1 |
| 14561 | `IntermediatePlayerData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14564 | `DrawPlayer_Intermediate` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14566 | `PIntLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14587 | `RenderPlayerSub` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 / S not recorded; M2 T15 S3; M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14601 | `DrawPlayerLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14610 | `ProcessPlayerAction` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14626 | `ProcOnGroundActs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14642 | `NonAnimatedActs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14649 | `ActionFalling` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14654 | `ActionWalkRun` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14659 | `ActionClimbing` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14666 | `ActionSwimming` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14676 | `GetCurrentAnimOffset` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14680 | `FourFrameExtent` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14684 | `ThreeFrameExtent` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14687 | `AnimationControl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14701 | `SetAnimC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14702 | `ExAnimC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14705 | `GetGfxOffsetAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14712 | `SzOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14714 | `ChangeSizeOffsetAdder` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14718 | `HandleChangeSize` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14728 | `CSzNext` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14729 | `GorSLog` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14734 | `GetOffsetFromAnimCtrl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14741 | `ShrinkPlayer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14750 | `ShrPlF` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14753 | `ChkForPlayerAttrib` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14767 | `KilledAtt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14774 | `C_S_IGAtt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14781 | `ExPlyrAt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14786 | `RelativePlayerPosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S3; M2 T16 S3; M2 T17 S4; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14791 | `RelativeBubblePosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S2; M2 T24 S1 |
| 14797 | `RelativeFireballPosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14801 | `RelWOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14805 | `RelativeMiscPosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T17 S5; M2 T19 S4; M2 T21 S2; M2 T24 S1 |
| 14811 | `RelativeEnemyPosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T17 S5; M2 T19 / S not recorded; M2 T19 S4; M2 T21 S2; M2 T22 S4; M2 T24 S1 |
| 14816 | `RelativeBlockPosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T16 S1; M2 T16 S2; M2 T21 S2; M2 T24 S1 |
| 14825 | `VariableObjOfsRelPos` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14834 | `GetObjRelativePosition` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14846 | `GetPlayerOffscreenBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14851 | `GetFireballOffscreenBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T20 S2; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14857 | `GetBubbleOffscreenBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S2; M2 T24 S1 |
| 14863 | `GetMiscOffscreenBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T17 S5; M2 T19 S4; M2 T21 S2; M2 T24 S1 |
| 14869 | `ObjOffsetData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14872 | `GetProperObjOffset` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14879 | `GetEnemyOffscreenBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T19 S4; M2 T21 S2; M2 T22 S4; M2 T24 S1 |
| 14884 | `GetBlockOffscreenBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T15 S4; M2 T16 S1; M2 T16 S2; M2 T21 S2; M2 T24 S1 |
| 14888 | `SetOffscrBitsOffset` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14894 | `GetOffScreenBitsSet` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14911 | `RunOffscrBitsSubs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14927 | `XOffscreenBitsData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14931 | `DefaultXOnscreenOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14934 | `GetXOffscreenBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14937 | `XOfsLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14953 | `XLdBData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14959 | `ExXOfsBS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14963 | `YOffscreenBitsData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14968 | `DefaultYOnscreenOfs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14971 | `HighPosUnitData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14974 | `GetYOffscreenBits` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S2; M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14977 | `YOfsLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14993 | `YLdBData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 14999 | `ExYOfsBS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15003 | `DividePDiff` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15015 | `SetOscrO` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15016 | `ExDivPD` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15025 | `DrawSpriteObject` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 15036 | `NoHFlip` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15040 | `SetHFAt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15070 | `SoundEngine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 / S not recorded; M2 T24 S1; M2 T7 / S not recorded |
| 15075 | `SndOn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15084 | `InPause` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15099 | `PTone1F` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15101 | `ContPau` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15108 | `PTone2F` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15109 | `PTRegC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15112 | `DecPauC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15121 | `SkipPIn` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15125 | `RunSoundSubroutines` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15134 | `SkipSoundSubroutines` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15147 | `NoIncDAC` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15150 | `StrWave` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15155 | `Dump_Squ1_Regs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15160 | `PlaySqu1Sfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15163 | `SetFreq_Squ1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15166 | `Dump_Freq_Regs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15174 | `NoTone` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15176 | `Dump_Sq2_Regs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15181 | `PlaySqu2Sfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15184 | `SetFreq_Squ2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15188 | `SetFreq_Tri` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15194 | `SwimStompEnvelopeData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15198 | `PlayFlagpoleSlide` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15206 | `PlaySmallJump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15210 | `PlayBigJump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15213 | `JumpRegContents` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15220 | `ContinueSndJump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15227 | `N2Prt` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15230 | `FPS2nd` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15231 | `DmpJpFPS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15234 | `PlayFireballThrow` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15239 | `PlayBump` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15242 | `Fthrow` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15247 | `ContinueBumpThrow` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15253 | `DecJpFPS` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15256 | `Square1SfxHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15276 | `CheckSfx1Buffer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15294 | `ExS1H` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15296 | `PlaySwimStomp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15304 | `ContinueSwimStomp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15313 | `BranchToDecLength1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15316 | `PlaySmackEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15325 | `ContinueSmackEnemy` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15333 | `SmSpc` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15334 | `SmTick` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15336 | `DecrementSfx1Length` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15340 | `StopSquare1Sfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T21 S5; M2 T24 S1 |
| 15347 | `ExSfx1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15349 | `PlayPipeDownInj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15353 | `ContinuePipeDownInj` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15365 | `NoPDwnL` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15369 | `ExtraLifeFreqData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15372 | `PowerUpGrabFreqData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15380 | `PUp_VGrow_FreqData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15386 | `PlayCoinGrab` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15391 | `PlayTimerTick` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15395 | `CGrab_TTickRegL` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15401 | `ContinueCGrabTTick` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15407 | `N2Tone` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15409 | `PlayBlast` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15416 | `ContinueBlast` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15422 | `SBlasJ` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15424 | `PlayPowerUpGrab` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15428 | `ContinuePowerUpGrab` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15437 | `LoadSqu2Regs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15440 | `DecrementSfx2Length` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15444 | `EmptySfx2Buffer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15448 | `StopSquare2Sfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T21 S5; M2 T24 S1 |
| 15453 | `ExSfx2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15455 | `Square2SfxHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15478 | `CheckSfx2Buffer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15496 | `ExS2H` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15498 | `Cont_CGrab_TTick` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15501 | `JumpToDecLength2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15504 | `PlayBowserFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15509 | `BlstSJp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15511 | `ContinueBowserFall` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15517 | `PBFRegs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15518 | `EL_LRegs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15520 | `PlayExtraLife` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15524 | `ContinueExtraLife` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15527 | `DivLLoop` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15537 | `PlayGrowPowerUp` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15541 | `PlayGrowVine` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15544 | `GrowItemRegs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15551 | `ContinueGrowItems` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T24 S1 |
| 15564 | `StopGrowItems` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15569 | `BrickShatterFreqData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15573 | `PlayBrickShatter` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15577 | `ContinueBrickShatter` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15585 | `PlayNoiseSfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15591 | `DecrementSfx3Length` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15598 | `ExSfx3` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15600 | `NoiseSfxHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15609 | `CheckNoiseBuffer` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15616 | `ExNH` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15618 | `PlayBowserFlame` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15622 | `ContinueBowserFlame` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15632 | `ContinueMusic` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15635 | `MusicHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15645 | `LoadEventMusic` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T21 S2; M2 T21 S5; M2 T24 S1 |
| 15651 | `NoStopSfx` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15662 | `LoadAreaMusic` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15666 | `NoStop1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15667 | `GMLoopB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15669 | `HandleAreaMusicLoopB` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15682 | `FindAreaMusicHeader` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15686 | `FindEventMusicHeader` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15691 | `LoadHeader` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15720 | `HandleSquare2Music` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15730 | `EndOfMusicData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15736 | `NotTRO` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15750 | `MusicLoopBack` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15753 | `VictoryMLoopBack` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15756 | `Squ2LengthHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15763 | `Squ2NoteHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15769 | `Rest` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15771 | `SkipFqL1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15774 | `MiscSqu2MusicTasks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15783 | `NoDecEnv1` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15788 | `HandleSquare1Music` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15794 | `FetchSqu1MusicData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15806 | `Squ1NoteHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15816 | `SkipCtrlL` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15819 | `MiscSqu1MusicTasks` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15828 | `NoDecEnv2` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15830 | `DeathMAltReg` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15833 | `DoAltLoad` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15835 | `HandleTriangleMusic` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15853 | `TriNoteHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15863 | `NotDOrD4` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15871 | `MediN` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15873 | `LongN` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15875 | `LoadTriCtrlReg` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15878 | `HandleNoiseMusic` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15885 | `FetchNoiseBeatData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15894 | `NoiseBeatHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15911 | `StrongBeat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15917 | `LongBeat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15923 | `SilentBeat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15926 | `PlayBeat` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15931 | `ExitMusicHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15934 | `AlternateLengthHandler` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15942 | `ProcessLengthData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15951 | `LoadControlRegs` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15957 | `NotECstlM` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15962 | `WaterMus` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15963 | `AllMus` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15967 | `LoadEnvelopeData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15974 | `LoadUsualEnvData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15981 | `LoadWaterEventMusEnvData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 15989 | `MusicHeaderData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16027 | `TimeRunningOutHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16028 | `Star_CloudHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16029 | `EndOfLevelMusHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16030 | `ResidualHeaderData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16031 | `UndergroundMusHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16032 | `SilenceHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16033 | `CastleMusHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16034 | `VictoryMusHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16035 | `GameOverMusHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16036 | `WaterMusHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16037 | `WinCastleMusHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16038 | `GroundLevelPart1Hdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16039 | `GroundLevelPart2AHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16040 | `GroundLevelPart2BHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16041 | `GroundLevelPart2CHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16042 | `GroundLevelPart3AHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16043 | `GroundLevelPart3BHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16044 | `GroundLevelLeadInHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16045 | `GroundLevelPart4AHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16046 | `GroundLevelPart4BHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16047 | `GroundLevelPart4CHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16048 | `DeathMusHdr` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16077 | `Star_CloudMData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16089 | `GroundM_P1Data` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16094 | `SilenceData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16104 | `GroundM_P2AData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16114 | `GroundM_P2BData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16124 | `GroundM_P2CData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16134 | `GroundM_P3AData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16140 | `GroundM_P3BData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16148 | `GroundMLdInData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16158 | `GroundM_P4AData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16167 | `GroundM_P4BData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16176 | `DeathMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16179 | `GroundM_P4CData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16193 | `CastleMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16217 | `GameOverMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16226 | `TimeRunOutMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16236 | `WinLevelMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16253 | `UndergroundMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16264 | `WaterMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16295 | `EndOfCastleMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16313 | `VictoryMusData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16326 | `FreqRegLookupTbl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16341 | `MusicLengthLookupTbl` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16349 | `EndOfCastleMusicEnvData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16352 | `AreaMusicEnvData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16355 | `WaterEventMusEnvData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16362 | `BowserFlameEnvData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |
| 16368 | `BrickShatterEnvData` | M3 T27 S5 | existing closure backlog; Owner-approved remaining-core physical relocation;existing conformance dispositions and gaps retained | M2 T24 S1 |

## All known historical and planned T/S

Zero exact labels means the record supplies no exact per-node binding, not
that the task did no work. Consult its evidence; never manufacture an S or
claim the whole slice was completed. Future IDs are added here on admission.

| T or S | Exact historically mentioned nodes | Current received nodes | Evidence / record boundary |
| --- | ---: | ---: | --- |
| M0 T1 | 0 | - | [record](../../docs/history/M0-T1-governance-and-translation-plan-proposal.md); [record](../../docs/history/M0-T1-governance-and-translation-plan.md) |
| M0 T1 S1 | 0 | 0 | explicit-reference; [record](../../docs/history/M0-T1-governance-and-translation-plan.md) |
| M0 Td | 0 | - | [record](../../docs/states/CURRENT.md) |
| M0 Td S2 | 0 | 0 | explicit-reference; [record](../../docs/states/CURRENT.md) |
| M1 T2 | 0 | - | [record](../../docs/history/M1-T2-win32-platform-foundation.md); S not recorded |
| M1 T4 | 0 | - | [record](../../docs/history/M1-T5-title-oracle.md); S not recorded |
| M1 T5 | 0 | - | [record](../../docs/history/M1-T5-title-oracle.md); S not recorded |
| M2 T1 | 0 | - | [record](../../docs/etc/architecture/smb1-prg-analysis.md); [record](../../docs/history/M2-T1-prg-static-analysis.md); [record](../../docs/proposals/m2-native-logic-and-oracle.md); [record](../../docs/states/QUEUE.md); S not recorded |
| M2 T10 | 0 | - | [record](../../docs/history/M2-T10-translated-background-output.md); [record](../../docs/states/QUEUE.md); S not recorded |
| M2 T11 | 2 | - | [record](../../docs/history/M2-T11-translated-oam-output.md); [record](../../docs/states/QUEUE.md); S not recorded |
| M2 T12 | 0 | - | [record](../../docs/states/QUEUE.md); S not recorded |
| M2 T13 | 0 | - | [record](../../docs/states/QUEUE.md); S not recorded |
| M2 T14 | 42 | - | [record](../../docs/etc/architecture/m2-t14-frame-root-label-map.md); [record](../../docs/proposals/m2/frame-root.md); [record](../../docs/states/QUEUE.md) |
| M2 T14 S1 | 0 | 0 | declared-plan, explicit-reference; [record](../../docs/proposals/m2/frame-root.md); [record](../../docs/states/QUEUE.md) |
| M2 T14 S2 | 0 | 0 | declared-plan; [record](../../docs/proposals/m2/frame-root.md) |
| M2 T14 S3 | 0 | 0 | declared-plan; [record](../../docs/proposals/m2/frame-root.md) |
| M2 T14 S4 | 0 | 0 | declared-plan; [record](../../docs/proposals/m2/frame-root.md) |
| M2 T15 | 58 | - | [record](../../docs/etc/architecture/m2-t15-title-terminal-label-map.md); [record](../../docs/proposals/m2/title-terminal-modes.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T15 S1 | 22 | 0 | explicit-reference, recorded-section, declared-plan; [record](../../docs/etc/architecture/m2-t15-title-terminal-label-map.md); [record](../../docs/proposals/m2/title-terminal-modes.md) |
| M2 T15 S2 | 15 | 0 | recorded-section, declared-plan; [record](../../docs/etc/architecture/m2-t15-title-terminal-label-map.md); [record](../../docs/proposals/m2/title-terminal-modes.md) |
| M2 T15 S3 | 29 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/title-terminal-modes.md) |
| M2 T15 S4 | 12 | 0 | declared-plan, recorded-section, explicit-reference, declared-closure-plan; [record](../../docs/proposals/m2/title-terminal-modes.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T16 | 43 | - | [record](../../docs/proposals/m2/oam-graphics.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T16 S1 | 4 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/oam-graphics.md) |
| M2 T16 S2 | 15 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/oam-graphics.md) |
| M2 T16 S3 | 34 | 0 | declared-plan, recorded-section, explicit-reference; [record](../../docs/proposals/m2/oam-graphics.md); [record](../../docs/states/CURRENT.md) |
| M2 T16 S4 | 0 | 0 | declared-plan, declared-closure-plan; [record](../../docs/proposals/m2/oam-graphics.md) |
| M2 T17 | 109 | - | [record](../../docs/proposals/m2/collision-world.md); [record](../../docs/proposals/m2-rom-structural-recovery.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T17 S1 | 3 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/collision-world.md) |
| M2 T17 S2 | 4 | 0 | declared-plan, recorded-section, explicit-reference; [record](../../docs/proposals/m2/collision-world.md); [record](../../docs/states/CURRENT.md) |
| M2 T17 S3 | 8 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/collision-world.md) |
| M2 T17 S4 | 36 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/collision-world.md) |
| M2 T17 S5 | 51 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/collision-world.md) |
| M2 T17 S6 | 15 | 0 | declared-plan, recorded-section, explicit-reference, declared-closure-plan; [record](../../docs/proposals/m2/collision-world.md); [record](../../docs/states/CURRENT.md) |
| M2 T18 | 29 | - | [record](../../docs/proposals/m2/area-parser.md); [record](../../docs/proposals/m2-rom-structural-recovery.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T18 S1 | 2 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/area-parser.md) |
| M2 T18 S2 | 20 | 0 | declared-plan, recorded-section, explicit-reference; [record](../../docs/proposals/m2/area-parser.md); [record](../../docs/states/CURRENT.md) |
| M2 T18 S3 | 3 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/area-parser.md) |
| M2 T18 S4 | 0 | 0 | declared-plan, declared-closure-plan; [record](../../docs/proposals/m2/area-parser.md) |
| M2 T19 | 101 | - | [record](../../docs/proposals/m2/enemy-stream-actors.md); [record](../../docs/proposals/m2-rom-structural-recovery.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T19 S1 | 1 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/enemy-stream-actors.md) |
| M2 T19 S2 | 6 | 0 | declared-plan, recorded-section, explicit-reference; [record](../../docs/proposals/m2/enemy-stream-actors.md); [record](../../docs/states/CURRENT.md) |
| M2 T19 S3 | 21 | 0 | declared-plan, recorded-section, explicit-reference; [record](../../docs/proposals/m2/enemy-stream-actors.md); [record](../../docs/states/CURRENT.md) |
| M2 T19 S4 | 19 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/enemy-stream-actors.md) |
| M2 T19 S5 | 69 | 0 | declared-plan, recorded-section, explicit-reference, declared-closure-plan; [record](../../docs/proposals/m2/enemy-stream-actors.md); [record](../../docs/states/CURRENT.md) |
| M2 T2 | 3 | - | [record](../../docs/history/M2-T2-title-start-checkpoint.md); S not recorded |
| M2 T20 | 12 | - | [record](../../docs/proposals/m2/fireballs-bubbles.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T20 S1 | 4 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/fireballs-bubbles.md) |
| M2 T20 S2 | 5 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/fireballs-bubbles.md) |
| M2 T20 S3 | 6 | 0 | declared-plan, recorded-section, explicit-reference; [record](../../docs/proposals/m2/fireballs-bubbles.md); [record](../../docs/states/CURRENT.md) |
| M2 T20 S4 | 0 | 0 | declared-plan, declared-closure-plan; [record](../../docs/proposals/m2/fireballs-bubbles.md) |
| M2 T21 | 1439 | - | [record](../../docs/proposals/m2/t21-boot-cold-init.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T21 S1 | 70 | 0 | owner-approved-admission; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S2 | 95 | 0 | declared-plan; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S3 | 430 | 0 | declared-plan; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S4 | 406 | 0 | declared-plan; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S5 | 419 | 0 | declared-plan; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S6 | 24 | 0 | superseded-historical-receipt; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T22 | 71 | - | [record](../../docs/proposals/m2/blocks-items-misc.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T22 S1 | 34 | 0 | declared-plan, recorded-section, explicit-reference; [record](../../docs/proposals/m2/blocks-items-misc.md); [record](../../docs/states/CURRENT.md) |
| M2 T22 S2 | 1 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/blocks-items-misc.md) |
| M2 T22 S3 | 0 | 0 | declared-plan; [record](../../docs/proposals/m2/blocks-items-misc.md) |
| M2 T22 S4 | 7 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/blocks-items-misc.md) |
| M2 T22 S5 | 0 | 0 | declared-plan, declared-closure-plan; [record](../../docs/proposals/m2/blocks-items-misc.md) |
| M2 T22 S6 | 0 | 0 | source-order-intake; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S7 | 0 | 0 | source-order-migration; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S8 | 0 | 0 | source-order-branch-audit; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S9 | 0 | 0 | screenoff-evidence; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S10 | 0 | 0 | nmi-root-remainder; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S11 | 0 | 0 | boot-root-proof; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S12 | 0 | 0 | vram-table-migration; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S13 | 0 | 0 | nmi-integration-proof; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S14 | 0 | 0 | boot-root-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S15 | 3 | 0 | vram-table-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S16 | 1 | 0 | nmi-buffer-clear; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S17 | 6 | 0 | nmi-pause-route; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S18 | 6 | 0 | nmi-timer-lfsr-route; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S19 | 8 | 0 | nmi-sprite-split-route; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S20 | 6 | 0 | nmi-sprite-shuffle-route; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S21 | 1 | 0 | nmi-operation-dispatch; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S22 | 1 | 0 | nmi-parent-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S23 | 1 | 0 | initbuffer-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S24 | 6 | 0 | pause-route-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S25 | 6 | 0 | timer-lfsr-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S26 | 8 | 0 | sprite-oam-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S27 | 6 | 0 | sprite-shuffle-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S28 | 1 | 0 | owner-approved-independent-proof; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T23 | 5 | - | [record](../../docs/proposals/m2/player-route.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T23 S1 | 4 | 0 | declared-plan, recorded-section; [record](../../docs/proposals/m2/player-route.md) |
| M2 T23 S2 | 4 | 0 | declared-plan, recorded-section, explicit-reference; [record](../../docs/proposals/m2/player-route.md); [record](../../docs/states/CURRENT.md) |
| M2 T23 S3 | 0 | 0 | declared-plan; [record](../../docs/proposals/m2/player-route.md) |
| M2 T23 S4 | 0 | 0 | declared-plan; [record](../../docs/proposals/m2/player-route.md) |
| M2 T23 S5 | 0 | 0 | declared-plan, declared-closure-plan; [record](../../docs/proposals/m2/player-route.md) |
| M2 T24 | 1992 | - | [record](../../docs/history/M2-T24-S1-node-evidence-audit.md); [record](../../docs/proposals/m2/mapped-node-verification.md); [record](../../docs/proposals/m2/node-task-ledger.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T24 S1 | 1992 | 0 | explicit-reference, historical-record, closed-evidence-audit; [record](../../docs/history/M2-T24-S1-node-evidence-audit.md); [record](../../docs/proposals/m2/mapped-node-verification.md); [record](../../docs/states/QUEUE.md) |
| M2 T24 S2 | 0 | 0 | explicit-reference, owner-authorized-ledger; [record](../../docs/proposals/m2/node-task-ledger.md); [record](../../docs/states/CURRENT.md); [record](../../docs/states/QUEUE.md) |
| M2 T25 | 26 | - | [record](../../docs/proposals/m2/t25-title-menu-demo.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T25 S1 | 26 | 0 | source-order-node-contract; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S2 | 26 | 0 | planned-shared-c-migration; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S3 | 26 | 0 | planned-rom-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S4 | 26 | 0 | planned-operational-verification; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S5 | 0 | 0 | planned-closure; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S6 | 0 | 0 | post-dependency-integration-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S7 | 0 | 0 | source-order-title-idle-credit; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S8 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S9 | 1 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S10 | 1 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S11 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S12 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S13 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S14 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S15 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S16 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S17 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S18 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S19 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S20 | 0 | 0 | source-order-title-branch-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S21 | 0 | 0 | source-order-title-data-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S22 | 0 | 0 | source-order-title-routine-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S23 | 0 | 0 | source-order-icon-loop-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S24 | 0 | 0 | icon-return-chain-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S25 | 0 | 0 | title-idle-demo-chain-receipt; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T26 | 32 | - | [record](../../docs/proposals/m2/t26-victory-terminal.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T26 S1 | 0 | 0 | source-order-node-contract; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S2 | 0 | 0 | planned-shared-c-migration; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S3 | 0 | 0 | planned-floatey-actor-route; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S4 | 0 | 0 | planned-rom-equivalence; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S5 | 32 | 0 | planned-closure; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S6 | 2 | 0 | planned-outer-victory-call-order-repair; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S7 | 2 | 0 | planned-outer-victory-route-equivalence; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T27 | 0 | - | [record](../../docs/proposals/m2/screen-status.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T27 S1 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/screen-status.md) |
| M2 T27 S2 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/screen-status.md) |
| M2 T27 S3 | 0 | 0 | planned-dispatch-integration; [record](../../docs/proposals/m2/screen-status.md) |
| M2 T28 | 0 | - | [record](../../docs/proposals/m2/t28-area-output-bootstrap.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T28 S1 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S2 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S3 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S4 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S5 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S6 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S7 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S8 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T29 | 32 | - | [record](../../docs/proposals/m2/t29-area-parser-geometry.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T29 S1 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S2 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S3 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S4 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S5 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S6 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S7 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S8 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S9 | 22 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S10 | 10 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T3 | 2 | - | [record](../../docs/history/M2-T2-title-start-checkpoint.md); [record](../../docs/history/M2-T3-area-bootstrap-and-commands.md); S not recorded |
| M2 T30 | 144 | - | [record](../../docs/history/M2-T30-area-object-rendering.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T30 S1 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S2 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S3 | 7 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S4 | 10 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S5 | 3 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S6 | 4 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S7 | 1 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S8 | 8 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S9 | 8 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S10 | 6 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S11 | 1 | 0 | owner-approved-source-order, chain-based-implementation, corrective-revalidation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S12 | 1 | 0 | owner-approved-source-order, chain-based-implementation, corrective-revalidation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S13 | 3 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S14 | 23 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S15 | 34 | 0 | owner-approved-source-order, consumer-dependency-audit; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S16 | 7 | 6 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S17 | 22 | 22 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S18 | 3 | 3 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S19 | 3 | 3 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S20 | 0 | 0 | owner-approved-source-order, cross-chain-closure-audit; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T31 | 11 | - | [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S1 | 2 | 1 | owner-approved-source-order, entry-chain-implementation; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 9 | 9 | owner-approved-source-order, engine-chain-implementation; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S3 | 0 | 0 | owner-approved-source-order, scroll-chain-implementation; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S4 | 0 | 9 | owner-approved-source-order, entry-mode-chain-implementation; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T32 | 0 | - | [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S1 | 0 | 0 | owner-approved-source-order, player-control-chain; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S2 | 0 | 0 | owner-approved-source-order, vine-pipe-chain; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S3 | 0 | 0 | owner-approved-source-order, size-injury-death-palette-chain; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S4 | 0 | 0 | owner-approved-source-order, flagpole-end-level-chain; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T33 | 0 | - | [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S1 | 0 | 0 | owner-approved-source-order, movement-state-chain; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S2 | 0 | 0 | owner-approved-source-order, climbing-chain; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S3 | 0 | 0 | owner-approved-source-order, physics-chain; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S4 | 0 | 0 | owner-approved-source-order, animation-friction-chain; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T34 | 0 | - | [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| M2 T34 S1 | 0 | 0 | owner-approved-source-order, fireball-dispatch-chain; [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| M2 T34 S2 | 0 | 0 | owner-approved-source-order, fireball-core-chain; [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| M2 T35 | 0 | - | [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S1 | 0 | 0 | owner-approved-source-order, bubble-setup-movement-chain; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S2 | 0 | 0 | owner-approved-source-order, timer-chain; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S3 | 0 | 0 | owner-approved-source-order, jumpspring-chain; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S4 | 0 | 0 | owner-approved-source-order, vine-setup-chain; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T36 | 0 | - | [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S1 | 0 | 0 | owner-approved-source-order, vine-actor-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S2 | 0 | 0 | owner-approved-source-order, hammer-lifecycle-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S3 | 0 | 0 | owner-approved-source-order, coin-allocation-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S4 | 0 | 0 | owner-approved-source-order, misc-lifetime-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S5 | 0 | 0 | owner-approved-source-order, score-hud-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S6 | 0 | 0 | owner-approved-source-order, power-up-initialization; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T37 | 0 | - | [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S1 | 0 | 0 | owner-approved-source-order, power-up-actor-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S2 | 0 | 0 | owner-approved-source-order, head-hit-position-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S3 | 0 | 0 | owner-approved-source-order, block-content-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S4 | 0 | 0 | owner-approved-source-order, shatter-top-coin-chunks-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S5 | 0 | 0 | owner-approved-source-order, block-lifetime-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S6 | 0 | 0 | owner-approved-source-order, block-replacement-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S7 | 0 | 0 | owner-approved-source-order, horizontal-movement-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S8 | 0 | 0 | owner-approved-source-order, vertical-adapter-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S9 | 0 | 0 | owner-approved-source-order, common-gravity-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T38 | 0 | - | [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S1 | 0 | 0 | owner-approved-source-order, enemy-loop-dispatch-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S2 | 0 | 0 | owner-approved-source-order, enemy-record-parser-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S3 | 0 | 0 | owner-approved-source-order, initializer-vector-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S4 | 0 | 0 | owner-approved-source-order, common-initializer-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S5 | 0 | 0 | owner-approved-source-order, lakitu-spiny-allocation-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S6 | 0 | 0 | owner-approved-source-order, firebar-initialization-and-duplicate-dependency; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S7 | 0 | 0 | owner-approved-source-order, complete-flying-fish-initializer; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T39 | 0 | - | [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S1 | 0 | 0 | owner-approved-source-order, bowser-and-flame-initializer; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S2 | 0 | 0 | owner-approved-source-order, fireworks-initializer; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S3 | 0 | 0 | owner-approved-source-order, bullet-swimming-fish-allocation; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S4 | 0 | 0 | owner-approved-source-order, group-enemy-allocation; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S5 | 0 | 0 | owner-approved-source-order, small-initializers-frenzy-dispatch; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S6 | 0 | 0 | owner-approved-source-order, platform-initialization-chain; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S7 | 0 | 0 | owner-approved-source-order, actor-vector-retainer-chain; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S8 | 0 | 0 | owner-approved-source-order, normal-actor-movement-vector; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S9 | 0 | 0 | owner-approved-source-order, special-actor-platform-callers; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T4 | 0 | - | [record](../../docs/history/M2-T4-player-route-and-collision.md); S not recorded |
| M2 T40 | 0 | - | [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S1 | 0 | 0 | owner-approved-source-order, podoboo-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S2 | 0 | 0 | owner-approved-source-order, hammer-bro-normal-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S3 | 0 | 0 | owner-approved-source-order, jumping-red-paratroopa; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S4 | 0 | 0 | owner-approved-source-order, green-paratroopa-x-counters; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S5 | 0 | 0 | owner-approved-source-order, bloober-swimming; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S6 | 0 | 0 | owner-approved-source-order, bullet-bill-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S7 | 0 | 0 | owner-approved-source-order, swimming-cheep-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S8 | 0 | 0 | owner-approved-source-order, firebar-position-collision; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S9 | 0 | 0 | owner-approved-source-order, flying-cheep-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S10 | 0 | 0 | owner-approved-source-order, lakitu-movement-distance; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T41 | 0 | - | [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S1 | 0 | 0 | owner-approved-source-order, bridge-collapse; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S2 | 0 | 0 | owner-approved-source-order, bowser-control; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S3 | 0 | 0 | owner-approved-source-order, bowser-graphics-chain; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S4 | 0 | 0 | owner-approved-source-order, bowser-flame-chain; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S5 | 0 | 0 | owner-approved-source-order, fireworks-lifetime; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S6 | 0 | 0 | owner-approved-source-order, star-flag; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S7 | 0 | 0 | owner-approved-source-order, piranha-movement; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S8 | 0 | 0 | owner-approved-source-order, firebar-spin; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S9 | 0 | 0 | owner-approved-source-order, balanced-platforms; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S10 | 0 | 0 | owner-approved-source-order, vertical-platforms; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S11 | 0 | 0 | owner-approved-source-order, horizontal-platforms; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S12 | 0 | 0 | owner-approved-source-order, lift-platforms; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S13 | 0 | 0 | owner-approved-source-order, offscreen-bounds; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T42 | 0 | - | [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S1 | 0 | 0 | owner-approved-source-order, fireball-enemy-scan; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S2 | 0 | 0 | owner-approved-source-order, fireball-hit; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S3 | 0 | 0 | owner-approved-source-order, hammer-contact; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S4 | 0 | 0 | owner-approved-source-order, powerup-pickup; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S5 | 0 | 0 | owner-approved-source-order, player-enemy-contact; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S6 | 0 | 0 | owner-approved-source-order, enemy-pair-collision; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S7 | 0 | 0 | owner-approved-source-order, platform-collision; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S8 | 0 | 0 | owner-approved-source-order, platform-positioning; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S9 | 0 | 0 | owner-approved-source-order, collision-preflight; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T43 | 0 | - | [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S1 | 0 | 0 | owner-approved-source-order, player-terrain; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S2 | 0 | 0 | owner-approved-source-order, coin-axe-effects; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S3 | 0 | 0 | owner-approved-source-order, flagpole-vine-climbing; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S4 | 0 | 0 | owner-approved-source-order, hidden-spring-metatiles; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S5 | 0 | 0 | owner-approved-source-order, pipe-entry-warp; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S6 | 0 | 0 | owner-approved-source-order, side-impediment; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S7 | 0 | 0 | owner-approved-source-order, metatile-classification; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S8 | 0 | 0 | owner-approved-source-order, enemy-background-stun; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S9 | 0 | 0 | owner-approved-source-order, enemy-landing-grounded; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S10 | 0 | 0 | owner-approved-source-order, enemy-side-jump-hammer; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S11 | 0 | 0 | owner-approved-source-order, enemy-ground-query-nonsolids; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S12 | 0 | 0 | owner-approved-source-order, fireball-background-collision; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S13 | 0 | 0 | owner-approved-source-order, object-bounding-box-entry; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S14 | 0 | 0 | owner-approved-source-order, bounding-box-core-clipping; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S15 | 0 | 0 | owner-approved-source-order, shared-box-collision-geometry; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T44 | 0 | - | [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S1 | 0 | 0 | owner-approved-source-order, block-buffer-core; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S2 | 0 | 0 | owner-approved-source-order, vine-object-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S3 | 0 | 0 | owner-approved-source-order, six-sprite-hammer-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S4 | 0 | 0 | owner-approved-source-order, flagpole-oam-dump-helpers; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S5 | 0 | 0 | owner-approved-source-order, large-platform-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S6 | 0 | 0 | owner-approved-source-order, floatey-jumping-coin-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S7 | 0 | 0 | owner-approved-source-order, power-up-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S8 | 0 | 0 | owner-approved-source-order, enemy-graphics-animation; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T45 | 0 | - | [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S1 | 0 | 0 | owner-approved-source-order, enemy-graphics-oam-tail; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S2 | 0 | 0 | owner-approved-source-order, block-chunk-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S3 | 0 | 0 | owner-approved-source-order, fireball-firebar-explosion-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S4 | 0 | 0 | owner-approved-source-order, small-platform-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S5 | 0 | 0 | owner-approved-source-order, bubble-player-graphics-data; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T46 | 0 | - | [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S1 | 0 | 0 | owner-approved-source-order, player-graphics-dispatch-offscreen; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S2 | 0 | 0 | owner-approved-source-order, intermediate-player-row-render; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S3 | 0 | 0 | owner-approved-source-order, player-action-animation-control; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S4 | 0 | 0 | owner-approved-source-order, player-size-attribute-control; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T47 | 0 | - | [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S1 | 0 | 0 | owner-approved-source-order, player-attribute-exit; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S2 | 0 | 0 | owner-approved-source-order, relative-object-position; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S3 | 0 | 0 | owner-approved-source-order, player-offscreen-entry; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S4 | 0 | 0 | owner-approved-source-order, shared-offscreen-chain; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S5 | 0 | 0 | owner-approved-source-order, sprite-row-writer; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T48 | 0 | - | [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S1 | 0 | 0 | owner-approved-source-order, soundengine-entry; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S2 | 0 | 0 | owner-approved-source-order, apu-register-helpers; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S3 | 0 | 0 | owner-approved-source-order, square-one-effect-phases; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S4 | 0 | 0 | owner-approved-source-order, square-one-dispatch-lifetime; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S5 | 0 | 0 | owner-approved-source-order, square-two-effect-phases; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S6 | 0 | 0 | owner-approved-source-order, square-two-dispatch; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T49 | 0 | - | [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S1 | 0 | 0 | owner-approved-source-order, square-two-remaining-effects; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S2 | 0 | 0 | owner-approved-source-order, noise-effects-music-handoff; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S3 | 0 | 0 | owner-approved-source-order, music-selection-header-load; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S4 | 0 | 0 | owner-approved-source-order, square-two-music-stream; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S5 | 0 | 0 | owner-approved-source-order, square-one-music-stream; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S6 | 0 | 0 | owner-approved-source-order, triangle-music-stream; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S7 | 0 | 0 | owner-approved-source-order, noise-music-beat-stream; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S8 | 0 | 0 | owner-approved-source-order, shared-music-helpers; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S9 | 0 | 0 | owner-approved-source-order, music-header-data; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T5 | 2 | - | [record](../../docs/history/M2-T5-object-routes.md); S not recorded |
| M2 T50 | 0 | - | [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md); [record](../../docs/states/QUEUE.md) |
| M2 T50 S1 | 0 | 0 | owner-approved-source-order, music-stream-data; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T50 S2 | 0 | 0 | declared-plan, music-lookup-data; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T50 S3 | 0 | 0 | declared-plan, noise-envelope-data; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T51 | 0 | - | [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md); [record](../../docs/states/QUEUE.md) |
| M2 T51 S1 | 0 | 0 | owner-approved-completion, nmi-parent-integration; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S2 | 0 | 0 | owner-approved-completion, screen-parser-output-chain; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S3 | 0 | 0 | owner-approved-completion, kill-enemies-shared-primitive; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S4 | 0 | 0 | owner-approved-completion, enemy-stream-data-chain-and-consumer; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S5 | 0 | 0 | cross-route-integration-certification; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T52 | 0 | - | [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S1 | 0 | 0 | owner-approved-current-equivalence-remediation, a2-nmi-prefix-state-handoff; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S2 | 0 | 0 | owner-approved-current-equivalence-remediation, a6-title-demo-world-select-order; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S3 | 0 | 0 | owner-approved-current-equivalence-remediation, a7-floatey-score-timer-order; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S4 | 0 | 0 | owner-approved-current-equivalence-remediation, b2-background-player-palette-fallthrough; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S5 | 0 | 0 | owner-approved-current-equivalence-remediation, b3-timeup-task-handoff; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S6 | 0 | 0 | owner-approved-current-equivalence-remediation, h9-large-platform-y-source; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S7 | 0 | 0 | owner-approved-current-equivalence-remediation, h1-h8-infeasible-control-edge-disposition; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T53 | 0 | - | [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S1 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-a-reset-nmi-dispatch-chain, closed-s1-current-equivalence-audit; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S2 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-a-title-menu-demo-chain, closed-s2-current-equivalence-audit; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S3 | 0 | 0 | owner-directed-screenoff-corrective, cohort-a-screenoff-transaction-order, closed-screenoff-current-equivalence; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S4 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-a-victory-chain, closed-s4-current-equivalence-audit; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S5 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-a-floatey-number-chain; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T54 | 0 | - | [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S1 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-b-s1-planned-chain; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S2 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-b-s2-planned-chain; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S3 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-b-s3-planned-chain; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S4 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-b-s4-planned-chain; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S5 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-b-s5-planned-chain; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S6 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-b-s6-planned-chain; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S7 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-b-s7-planned-chain; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T55 | 0 | - | [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S1 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-c-s1-planned-chain; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S2 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-c-s2-planned-chain; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S3 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-c-s3-planned-chain; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S4 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-c-s4-planned-chain; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S5 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-c-s5-planned-chain; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S6 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-c-s6-planned-chain; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S7 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-c-s7-planned-chain; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S8 | 0 | 0 | owner-directed-source-order-current-equivalence, cohort-c-s8-planned-chain; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T56 | 0 | - | [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md); [record](../../docs/proposals/m2/current-equivalence-proof-program.md) |
| M2 T56 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-area-parser; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-area-parser; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-area-parser; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-area-parser; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-area-parser; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-area-parser; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T57 | 0 | - | [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md); [record](../../docs/proposals/m2/current-equivalence-proof-program.md) |
| M2 T57 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-d; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-d; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-d; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-d; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-d; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-d; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-d; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T58 | 0 | - | [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md); [record](../../docs/proposals/m2/current-equivalence-proof-program.md) |
| M2 T58 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-e; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-e; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-e; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-e; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-e; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-e; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T59 | 0 | - | [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md); [record](../../docs/proposals/m2/current-equivalence-proof-program.md) |
| M2 T59 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-f; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-f; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-f; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-f; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-f; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-f; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-f, cross-chain-closure; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T6 | 12 | - | [record](../../docs/history/M2-T6-mode-routes.md); S not recorded |
| M2 T60 | 0 | - | [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md); [record](../../docs/proposals/m2/current-equivalence-proof-program.md) |
| M2 T60 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S8 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S9 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-g, cross-chain-closure; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T61 | 0 | - | [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md); [record](../../docs/proposals/m2/current-equivalence-proof-program.md) |
| M2 T61 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-vine; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-cannon; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-hammer; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-coin-misc; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-score; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-powerup; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-head-block; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S8 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-block-lifetime; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S9 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-horizontal-motion; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S10 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-h-vertical-gravity; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T62 | 0 | - | [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md); [record](../../docs/states/CURRENT.md) |
| M2 T62 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S8 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S9 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S10 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-i, cross-chain-closure; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T63 | 0 | - | [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md); [record](../../docs/states/CURRENT.md) |
| M2 T63 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S8 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S9 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S10 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S11 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S12 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S13 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S14 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S15 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S16 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S17 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S18 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S19 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S20 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S21 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S22 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S23 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S24 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S25 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S26 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S27 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S28 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j, cross-chain-edge-closure; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S29 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j, integrated-regression-fixture-correction; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T64 | 0 | - | [record](../../docs/history/M2-T64-terrain-collision-current-proof.md); [record](../../docs/states/CURRENT.md) |
| M2 T64 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S8 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S9 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S10 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S11 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S12 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S13 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S14 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S15 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S16 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S17 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S18 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S19 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S20 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S21 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S22 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S23 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S24 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S25 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S26 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S27 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S28 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S29 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S30 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S31 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S32 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S33 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S34 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S35 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S36 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S37 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S38 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S39 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S40 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S41 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S42 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S43 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S44 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S45 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S46 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S47 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S48 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S49 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S50 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S51 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S52 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S53 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S54 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S55 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S56 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S57 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S58 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S59 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-j-aggregate; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T65 | 0 | - | [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S8 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S9 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S10 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S11 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S12 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S13 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S14 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S15 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-k; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T66 | 0 | - | [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-l; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-l; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-l; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-l; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-l; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-l; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-l; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T67 | 0 | - | [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-m; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-m; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-m; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-m; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-m; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-m; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T68 | 0 | - | [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-n; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-n; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-n; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-n; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-n; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cohort-n; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T69 | 0 | - | [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S1 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S2 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S3 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S4 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S5 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S6 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S7 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S8 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S9 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S10 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S11 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S12 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S13 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S14 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S15 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S16 | 0 | 0 | owner-approved-source-order, current-equivalence-cross-cohort; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T7 | 1 | - | [record](../../docs/history/M2-T7-audio-command-routes.md); S not recorded |
| M2 T70 | 0 | - | [record](../../docs/history/m2/t70-final-current-certification.md); [record](../../docs/history/M2-T70-deferred-verification-closure.md) |
| M2 T70 S1 | 0 | 0 | owner-approved-source-order, final-current-certification; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S2 | 0 | 0 | owner-approved-source-order, final-current-certification; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S3 | 0 | 0 | source-provenance-reconciliation; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S4 | 0 | 0 | nmi-prefix-material-phase-proof; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S5 | 0 | 0 | timer-random-material-audit; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S6 | 0 | 0 | sprite-zero-scroll-phase-audit; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S7 | 0 | 0 | sprite-shuffle-material-audit; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S8 | 0 | 0 | pause-state-material-audit; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S9 | 0 | 0 | serial-input-pause-material-chain; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S10 | 0 | 0 | title-menu-demo-material-audit; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S11 | 0 | 0 | victory-message-termination-material-repair; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S12 | 0 | 0 | floatey-score-oam-material-repair; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S13 | 0 | 0 | screen-palette-material-order-repair; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S14 | 0 | 0 | hud-intermediate-timer-chain; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S15 | 0 | 0 | final-reset-startup-source-and-graph-review; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S16 | 0 | 0 | executable-data-binding-manifest; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S17 | 0 | 2 | material-use-completeness-and-path-reconciliation, corrective-title-pointer-output-chain, corrective-column-output-chain, corrective-parser-output-chain; [record](../../docs/history/m2/t70-final-current-certification.md); [record](../../docs/history/M2-T70-deferred-verification-closure.md) |
| M2 T8 | 3 | - | [record](../../docs/history/M2-T8-end-to-end-oracle-and-win32-route.md); [record](../../docs/history/M4-T1-486sx-qualification-protocol.md); S not recorded |
| M2 T9 | 1 | - | [record](../../docs/etc/architecture/smb1-frame-output-ledger.md); [record](../../docs/history/M2-T9-frame-output-ledger-and-reference-recorder.md); S not recorded |
| M2 Td | 0 | - | [record](../../docs/proposals/m2-rom-structural-recovery.md); [record](../../docs/states/QUEUE.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 Td S3 | 0 | 0 | explicit-reference; [record](../../docs/proposals/m2-rom-structural-recovery.md) |
| M2 Td S2 | 0 | 0 | explicit-reference; [record](../../docs/states/QUEUE.md) |
| M2 Td S4 | 0 | 0 | out-of-order-custody; [record](../../docs/proposals/m2/audio-engine.md) |
| M2 Td S5 | 0 | 0 | future-source-order-custody; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 Td S6 | 0 | 0 | future-source-order-custody; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 Td S7 | 0 | 0 | source-order-identifier-reconciliation; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md); [record](../../docs/states/QUEUE.md) |
| M2 Td S8 | 0 | 0 | owner-approved-governance-reconciliation; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 Td S9 | 0 | 0 | owner-directed-current-equivalence-governance; [record](../../docs/proposals/m2/current-equivalence-reaudit.md); [record](../../docs/states/M2_CURRENT_EQUIVALENCE.md) |
| M3 T1 | 0 | - | [record](../../docs/history/M3-T1-neutral-render-command-seam.md); S not recorded |
| M3 T10 | 0 | - | [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S1 | 0 | 0 | snapshot-codec; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S2 | 0 | 0 | snapshot-storage-transaction; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S3 | 0 | 0 | win32-snapshot-binding; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S4 | 0 | 0 | dos-snapshot-binding; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S5 | 0 | 0 | integrated-snapshot-acceptance; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T11 | 0 | - | [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S1 | 0 | 0 | semantic-text-contract; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S2 | 0 | 0 | semantic-visible-observation; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S3 | 0 | 0 | semantic-full-scene-presentation; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S4 | 0 | 0 | dos-text-presenter-acceptance; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S5 | 0 | 0 | win32-text-presenter-acceptance; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S6 | 0 | 0 | integrated-text-presentation-acceptance; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S7 | 0 | 0 | corrective-caption-layer-join; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T12 | 0 | - | [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T12 S1 | 0 | 0 | authored-glyph-contract; [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T12 S2 | 0 | 0 | authored-half-block-contours; [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T12 S3 | 0 | 0 | integrated-glyph-word-host-acceptance; [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T12 S4 | 0 | 0 | completion-evidence-reconciliation; [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T13 | 0 | - | [record](../../docs/history/M3-T13-win32-startup-console-lifecycle.md) |
| M3 T13 S1 | 0 | 0 | win32-startup-console-lifecycle; [record](../../docs/history/M3-T13-win32-startup-console-lifecycle.md) |
| M3 T14 | 0 | - | [record](../../docs/history/M3-T14-win32-remote-keyboard.md) |
| M3 T14 S1 | 0 | 0 | win32-remote-keyboard; [record](../../docs/history/M3-T14-win32-remote-keyboard.md) |
| M3 T15 | 0 | - | [record](../../docs/history/M3-T15-presentation-performance.md) |
| M3 T15 S1 | 0 | 0 | presentation-performance; [record](../../docs/history/M3-T15-presentation-performance.md) |
| M3 T15 S2 | 0 | 0 | presentation-performance; [record](../../docs/history/M3-T15-presentation-performance.md) |
| M3 T16 | 0 | - | [record](../../docs/history/M3-T16-mushroom-text-colors.md) |
| M3 T16 S1 | 0 | 0 | mushroom-text-colors; [record](../../docs/history/M3-T16-mushroom-text-colors.md) |
| M3 T17 | 0 | - | [record](../../docs/history/M3-T17-text-object-role-audit.md) |
| M3 T17 S1 | 0 | 0 | text-object-role-audit; [record](../../docs/history/M3-T17-text-object-role-audit.md) |
| M3 T18 | 0 | - | [record](../../docs/history/M3-T18-window-performance-executable-footprint.md) |
| M3 T18 S1 | 0 | 0 | window-performance; [record](../../docs/history/M3-T18-window-performance-executable-footprint.md) |
| M3 T18 S2 | 0 | 0 | executable-footprint; [record](../../docs/history/M3-T18-window-performance-executable-footprint.md) |
| M3 T19 | 0 | - | [record](../../docs/proposals/m3/bounded-windows-audio-startup.md) |
| M3 T19 S1 | 0 | 0 | bounded-audio-device-lifetime; [record](../../docs/proposals/m3/bounded-windows-audio-startup.md) |
| M3 T2 | 0 | - | [record](../../docs/history/M3-T1-neutral-render-command-seam.md); [record](../../docs/history/M3-T2-win32-command-consumer.md); S not recorded |
| M3 T20 | 0 | - | [record](../../docs/history/M3-T20-text-interface-corrections.md) |
| M3 T20 S1 | 0 | 0 | bounded-character-interface-corrections; [record](../../docs/history/M3-T20-text-interface-corrections.md) |
| M3 T20 S2 | 0 | 0 | planned-background-clarity-correction; [record](../../docs/history/M3-T20-text-interface-corrections.md) |
| M3 T20 S3 | 0 | 0 | corrective-fence-text-color; [record](../../docs/history/M3-T20-text-interface-corrections.md) |
| M3 T21 | 0 | - | [record](../../docs/history/M3-T21-water-snow-text-colors.md) |
| M3 T21 S1 | 0 | 0 | water-snow-character-color; [record](../../docs/history/M3-T21-water-snow-text-colors.md) |
| M3 T21 S2 | 0 | 0 | corrective-coral-water-background; [record](../../docs/history/M3-T21-water-snow-text-colors.md) |
| M3 T22 | 0 | - | [record](../../docs/history/M3-T22-pipe-exit-display-recovery.md) |
| M3 T22 S1 | 0 | 0 | pipe-exit-output-integration; [record](../../docs/history/M3-T22-pipe-exit-display-recovery.md) |
| M3 T22 S2 | 0 | 0 | bounded-state-handoff-audit; [record](../../docs/history/M3-T22-pipe-exit-display-recovery.md) |
| M3 T23 | 0 | - | [record](../../docs/history/M3-T23-princess-text-detail.md) |
| M3 T23 S1 | 0 | 0 | princess-text-detail; [record](../../docs/history/M3-T23-princess-text-detail.md) |
| M3 T24 | 0 | - | [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T24 S1 | 0 | 0 | parent-console-lifecycle; [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T24 S2 | 0 | 0 | window-client-geometry; [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T24 S3 | 0 | 0 | console-restore-geometry; [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T24 S4 | 0 | 0 | rdp-input-focus-correction; [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T25 | 0 | - | [record](../../docs/history/M3-T25-dos16-performance-diagnosis.md) |
| M3 T25 S1 | 0 | 0 | dos16-performance-diagnosis; [record](../../docs/history/M3-T25-dos16-performance-diagnosis.md) |
| M3 T26 | 0 | - | [record](../../docs/history/M3-T26-dos16-playable-performance.md) |
| M3 T26 S1 | 0 | 0 | dos16-indexed-render-performance; [record](../../docs/history/M3-T26-dos16-playable-performance.md) |
| M3 T26 S2 | 0 | 0 | fixed-environment-performance-correction; [record](../../docs/history/M3-T26-dos16-playable-performance.md) |
| M3 T27 | 0 | - | [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S1 | 0 | 0 | core-ppu-text-validation-boundary-census; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S2 | 0 | 14 | ppu-state-storage-extraction; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S3 | 0 | 0 | ppu-read-only-compositor-extraction; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S4 | 0 | 474 | core-root-mode-area-mechanical-move; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S5 | 0 | 1449 | remaining-core-path-cohorts; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S6 | 0 | 0 | text-consumer-observation-boundary; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S7 | 0 | 0 | validation-only-link-separation; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S8 | 0 | 0 | integrated-component-completion-review; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T28 | 0 | - | [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S1 | 0 | 0 | post-split-dos-render-cost-memory-audit; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S2 | 0 | 0 | shared-background-chr-cache-chain; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S3 | 0 | 0 | shared-sprite-priority-occupancy-chain; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S4 | 0 | 0 | dos-exact-stretch-row-bounded-storage-chain; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S5 | 0 | 0 | presentation-reuse-workspace-lifetime-chain; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S6 | 0 | 0 | integrated-memory-fit-playability-chain; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T29 | 0 | - | [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T29 S1 | 0 | 0 | win32-usability-regression-diagnosis; [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T29 S2 | 0 | 0 | win32-dpi-console-device-repair; [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T29 S3 | 0 | 0 | win32-product-integrated-usability-review; [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T29 S4 | 0 | 0 | live-console-acquisition-blocking-repair; [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T3 | 0 | - | [record](../../docs/history/M3-T2-win32-command-consumer.md); [record](../../docs/history/M3-T3-colored-text-frame.md); S not recorded |
| M3 T30 | 0 | - | [record](../../docs/history/M3-T30-ppu-background-performance.md) |
| M3 T30 S1 | 0 | 0 | shared-background-compiled-inner-loop-performance; [record](../../docs/history/M3-T30-ppu-background-performance.md) |
| M3 T30 S2 | 0 | 0 | bounded-background-scanline-metadata-reuse; [record](../../docs/history/M3-T30-ppu-background-performance.md) |
| M3 T31 | 0 | - | [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S1 | 0 | 0 | shared-palette-preparation-performance-memory; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S2 | 0 | 0 | neutral-vga-plane-loop-performance-memory; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S3 | 0 | 0 | neutral-file-crt-error-lifetime-memory; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S4 | 0 | 0 | dos-stack-continuous-memory-acceptance; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S5 | 0 | 0 | shared-text-cell-performance-memory; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S6 | 0 | 0 | final-integrated-memory-cadence-receipt; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T32 | 0 | - | [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S1 | 0 | 0 | rendering-performance-memory-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S2 | 0 | 0 | rendering-performance-memory-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S3 | 0 | 0 | rendering-performance-memory-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S4 | 0 | 0 | rendering-performance-memory-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S5 | 0 | 0 | dos-performance-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md); [record](../../docs/proposals/m3/dos-graphics-nesticle-performance.md) |
| M3 T32 S6 | 0 | 0 | dos-performance-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md); [record](../../docs/proposals/m3/dos-graphics-nesticle-performance.md) |
| M3 T32 S7 | 0 | 0 | dos-performance-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md); [record](../../docs/proposals/m3/dos-graphics-nesticle-performance.md) |
| M3 T32 S8 | 0 | 0 | dos-performance-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md); [record](../../docs/proposals/m3/dos-graphics-nesticle-performance.md) |
| M3 T32 S9 | 0 | 0 | dos-performance-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md); [record](../../docs/proposals/m3/dos-graphics-nesticle-performance.md) |
| M3 T32 S10 | 0 | 0 | dos-performance-continuation; [record](../../docs/history/M3-T32-rendering-performance-continuation.md); [record](../../docs/proposals/m3/dos-graphics-nesticle-performance.md) |
| M3 T4 | 0 | - | [record](../../docs/history/M3-T3-colored-text-frame.md); [record](../../docs/history/M3-T4-vga-indexed-frame.md); S not recorded |
| M3 T5 | 0 | - | [record](../../docs/history/M3-T4-vga-indexed-frame.md); [record](../../docs/history/M3-T5-dos16-composition-root.md); S not recorded |
| M3 T6 | 0 | - | [record](../../docs/history/M3-T5-dos16-composition-root.md); [record](../../docs/history/M3-T6-opennt-mz-link.md); S not recorded |
| M3 T7 | 0 | - | [record](../../docs/history/M3-T6-opennt-mz-link.md); [record](../../docs/history/M3-T7-dos-hardware-hooks.md); S not recorded |
| M3 T8 | 0 | - | [record](../../docs/history/M3-T7-dos-hardware-hooks.md); [record](../../docs/history/M3-T8-dos-runtime-structural-evidence.md); S not recorded |
| M3 T9 | 0 | - | [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S1 | 0 | 0 | portable-io-contracts; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S2 | 0 | 0 | win32-io-contract-migration; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S3 | 0 | 0 | dos-graphical-io-bringup; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S4 | 0 | 0 | dos-device-stabilization; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S5 | 0 | 0 | dos-sustained-graphics-route; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S6 | 0 | 0 | integrated-io-boundary-review; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M4 T1 | 0 | - | [record](../../docs/history/M4-T1-486sx-qualification-protocol.md); S not recorded |
| M4 T2 | 0 | - | [record](../../docs/history/M4-T2-S1-softpc-compatibility-probe.md) |
| M4 T2 S1 | 0 | 0 | explicit-reference, historical-record; [record](../../docs/history/M4-T2-S1-softpc-compatibility-probe.md) |

## Accepted ownership events

| Event | From | Receiving S | Nodes | Acceptance evidence |
| --- | --- | --- | ---: | --- |
| accept-001 | initial ledger | M2 T15 S4 | 58 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-002 | initial ledger | M2 T16 S4 | 87 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-003 | initial ledger | M2 T17 S6 | 430 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-004 | initial ledger | M2 T18 S4 | 406 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-005 | initial ledger | M2 T19 S5 | 414 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-006 | initial ledger | M2 T20 S4 | 24 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-007 | initial ledger | M2 T21 S5 | 203 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-008 | initial ledger | M2 T22 S5 | 121 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-009 | initial ledger | M2 T23 S5 | 111 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| accept-010 | initial ledger | M2 T24 S2 | 138 | M2 T24 S2 coordinator under explicit owner request; [record](../../docs/proposals/m2/node-task-ledger.md) |
| transfer-021-audio-deferral | M2 T21 S5 | M2 Td S4 | 203 | Owner-directed linear-sequence recovery on 2026-09-26; [record](../../docs/proposals/m2/t21-prior-node-closure.md) |
| transfer-021-01 | M2 T15 S4 | M2 T21 S1 | 58 | Owner-directed linear-sequence recovery on 2026-09-26; [record](../../docs/proposals/m2/t21-prior-node-closure.md) |
| transfer-021-02 | M2 T16 S4 | M2 T21 S2 | 84 | Owner-directed linear-sequence recovery on 2026-09-26; [record](../../docs/proposals/m2/t21-prior-node-closure.md) |
| transfer-021-03 | M2 T17 S6 | M2 T21 S3 | 430 | Owner-directed linear-sequence recovery on 2026-09-26; [record](../../docs/proposals/m2/t21-prior-node-closure.md) |
| transfer-021-04 | M2 T18 S4 | M2 T21 S4 | 406 | Owner-directed linear-sequence recovery on 2026-09-26; [record](../../docs/proposals/m2/t21-prior-node-closure.md) |
| transfer-021-05 | M2 T19 S5 | M2 T21 S5 | 414 | Owner-directed linear-sequence recovery on 2026-09-26; [record](../../docs/proposals/m2/t21-prior-node-closure.md) |
| transfer-021-06 | M2 T20 S4 | M2 T21 S6 | 24 | Owner-directed linear-sequence recovery on 2026-09-26; [record](../../docs/proposals/m2/t21-prior-node-closure.md) |
| transfer-021-replan-1 | M2 T21 S1 | M2 T15 S4 | 58 | Owner-directed small-task replanning on 2026-09-26; [record](../../docs/proposals/m2/t21-fireball-bubble-timer-warp.md) |
| transfer-021-replan-2 | M2 T21 S2 | M2 T16 S4 | 84 | Owner-directed small-task replanning on 2026-09-26; [record](../../docs/proposals/m2/t21-fireball-bubble-timer-warp.md) |
| transfer-021-replan-3 | M2 T21 S3 | M2 T17 S6 | 430 | Owner-directed small-task replanning on 2026-09-26; [record](../../docs/proposals/m2/t21-fireball-bubble-timer-warp.md) |
| transfer-021-replan-4 | M2 T21 S4 | M2 T18 S4 | 406 | Owner-directed small-task replanning on 2026-09-26; [record](../../docs/proposals/m2/t21-fireball-bubble-timer-warp.md) |
| transfer-021-replan-5 | M2 T21 S5 | M2 T19 S5 | 414 | Owner-directed small-task replanning on 2026-09-26; [record](../../docs/proposals/m2/t21-fireball-bubble-timer-warp.md) |
| transfer-021-replan-6 | M2 T21 S6 | M2 T21 S1 | 24 | Owner-directed small-task replanning on 2026-09-26; [record](../../docs/proposals/m2/t21-fireball-bubble-timer-warp.md) |
| transfer-021-source-order-fireball | M2 T21 S1 | M2 Td S5 | 24 | Owner-approved source-order replanning on 2026-09-26; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-021-boot-root | M2 T24 S2 | M2 T21 S1 | 11 | Owner approved source-order T21 admission on 2026-09-26; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| transfer-021-nmi-boundary | M2 T21 S1 | M2 Td S6 | 5 | T21 S1 source-contract decision under owner-approved source-order plan; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| transfer-021-initialize-memory | M2 T24 S2 | M2 T21 S1 | 1 | T21 S1 source-contract decision under owner-approved source-order plan; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| transfer-021-s1-s2 | M2 T21 S1 | M2 T21 S2 | 7 | T21 S1 completion under the owner-approved S plan; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| transfer-021-s2-s3 | M2 T21 S2 | M2 T21 S3 | 7 | Owner-approved T21 S-plan: S3 ROM logic-equivalence follows S2 shared-C migration.; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| transfer-021-s3-s4 | M2 T21 S3 | M2 T21 S4 | 7 | Owner-approved T21 S-plan: S4 operational verification follows S3 ROM logic-equivalence audit.; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| transfer-021-s4-s5 | M2 T21 S4 | M2 T21 S5 | 7 | Owner-approved T21 S-plan: S5 closure follows S4 operational verification.; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| transfer-021-s5-t22-deferred | M2 T21 S5 | M2 Td S6 | 7 | T21 S5 closure under the owner-approved source-order plan: the boot root requires the queued T22 NMI/PPU boundary.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-022-source-order-intake | M2 Td S6 | M2 T22 S6 | 12 | Owner-approved T21T49 source-order plan; T22 S6 is the next unused T22 slot because historical T22 S1S5 records remain immutable.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-023-t22-s6-to-s7 | M2 T22 S6 | M2 T22 S7 | 12 | T22/S6 completed the source contract with no node credit; T22/S7 accepts its bounded shared-C first-NMI call-placement migration.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-024-t22-s7-to-s8 | M2 T22 S7 | M2 T22 S8 | 12 | T22/S7 completed the bounded shared-C call-placement migration with no node credit; T22/S8 accepts the source-branch audit and only source-owned repair.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-025-t22-s8-to-s9 | M2 T22 S8 | M2 T22 S9 | 1 | T22/S8 isolated the source-owned ScreenOff repair and T22/S9 accepts its explicit one-label proof forecast.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-026-t22-s8-to-s10 | M2 T22 S8 | M2 T22 S10 | 11 | T22/S8 found the remaining route differences depend on descendants outside the ScreenOff proof; T22/S10 accepts the unchanged root package.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-027-t22-s10-to-s11 | M2 T22 S10 | M2 T22 S11 | 7 | T22/S10 classified the cold-start root separately from later initialization descendants; T22/S11 accepts exact boot-root proof and repair custody.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-028-t22-s10-to-s12 | M2 T22 S10 | M2 T22 S12 | 3 | T22/S10 identified the NMI $00/$01 pointer writes as direct address-table semantics; T22/S12 accepts the three table labels.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-029-t22-s10-to-s13 | M2 T22 S10 | M2 T22 S13 | 1 | T22/S10 isolates the parent NMI control path after its boot and table children; T22/S13 accepts the remaining root integration proof.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-030-t22-s11-to-s14 | M2 T22 S11 | M2 T22 S14 | 7 | T22/S11 completed the shared Start/VBlank/ColdBoot/EndlessLoop implementation and supplies its branch, timing and controlled-route evidence; T22/S14 accepts the isolated seven-label equivalence review.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-031-t22-s12-to-s15 | M2 T22 S12 | M2 T22 S15 | 3 | T22/S12 completed the table/write migration with no completion forecast; T22/S15 accepts independent controlled-NMI ROM-equivalence review.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-032-t24-s2-to-s16 | M2 T24 S2 | M2 T22 S16 | 1 | Accepted source-ordered NMI selected-buffer clear work from T24/S2.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-032-t24-s2-to-s17 | M2 T24 S2 | M2 T22 S17 | 6 | Accepted the NMI pause-call branch group from T24/S2.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-032-t24-s2-to-s18 | M2 T24 S2 | M2 T22 S18 | 6 | Accepted the NMI timer and LFSR continuation group from T24/S2.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-032-t24-s2-to-s19 | M2 T24 S2 | M2 T22 S19 | 8 | Accepted the NMI sprite-zero split and OAM-offscreen group from T24/S2.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-032-t24-s2-to-s20 | M2 T24 S2 | M2 T22 S20 | 6 | Accepted the NMI sprite-shuffle group from T24/S2.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-032-t24-s2-to-s21 | M2 T24 S2 | M2 T22 S21 | 1 | Accepted the NMI operation-mode dispatch root from T24/S2.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-033-t22-s13-to-s22 | M2 T22 S13 | M2 T22 S22 | 1 | Accepted the parent NMI node from T22/S13 for final integration review after every direct child closes.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-034-t22-s16-to-s23 | M2 T22 S16 | M2 T22 S23 | 1 | T22/S16 completed the source contract with no completion forecast; T22/S23 accepts independent controlled-NMI equivalence review.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-035-t22-s17-to-s24 | M2 T22 S17 | M2 T22 S24 | 6 | T22/S24 accepts the completed pause source contract for independent six-label ROM-equivalence review.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-036-t22-s18-to-s25 | M2 T22 S18 | M2 T22 S25 | 6 | T22/S25 accepts the repaired timer/LFSR source contract for independent controlled-NMI equivalence review.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-037-t22-s19-to-s26 | M2 T22 S19 | M2 T22 S26 | 8 | T22/S26 accepts the S19 sprite-zero/OAM source contract for independent controlled-ROM equivalence review.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-038-t22-s20-to-s27 | M2 T22 S20 | M2 T22 S27 | 6 | T22/S27 accepts the S20 sprite-shuffle source contract for independent controlled-ROM equivalence review.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-039-t22-s21-to-s28 | M2 T22 S21 | M2 T22 S28 | 1 | Owner-approved independent proof follows the S21 source-contract repair.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-040-t22-s22-to-t24-s2 | M2 T22 S22 | M2 T24 S2 | 1 | Owner-authorized custody accepts the parent until every direct NMI dependency has independent ROM-match evidence.; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| transfer-041-t15-s4-to-t25-s2-title | M2 T15 S4 | M2 T25 S2 | 26 | M2 T25 S2 pre-accepted by the owner-approved T25 S plan after its completed S1 source contract.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-042-t25-s2-to-s3-title | M2 T25 S2 | M2 T25 S3 | 26 | M2 T25 S3 pre-accepted by the owner-approved T25 S plan after S2 shared-C migration.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-043-t25-s3-to-s4-title | M2 T25 S3 | M2 T25 S4 | 26 | M2 T25 S4 is the owner-approved repair and operational-verification successor after S3 recorded exact source gaps.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-044-t25-s4-to-s5-title | M2 T25 S4 | M2 T25 S5 | 26 | M2 T25 S5 is the owner-approved closure successor; S4 recorded the T18 InitializeGame route prerequisite without creating duplicate title ownership.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-046-t25-s5-to-s6-retained-integration | M2 T25 S5 | M2 T25 S6 | 26 | M2 T25 S6 is the owner-approved retained integration receiver after S5 recorded exact title-route evidence and named T16/T26 prerequisites.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-047-t15-s4-to-t26-s2-terminal | M2 T15 S4 | M2 T26 S2 | 32 | M2 T26 S2 is the pre-accepted source-order receiver after its S1 audit identified the exact terminal tree and its external collaborators.; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| transfer-048-t26-s2-to-s3-floatey | M2 T26 S2 | M2 T26 S3 | 10 | M2 T26 S3 is the pre-accepted floatey actor receiver under the owner-approved T26 S plan.; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| transfer-049-t26-s2-to-s4-terminal-equivalence | M2 T26 S2 | M2 T26 S4 | 22 | M2 T26 S4 is the pre-accepted integration receiver for terminal route-equivalence after S2 repair.; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| transfer-050-t26-s3-to-s4-floatey-equivalence | M2 T26 S3 | M2 T26 S4 | 10 | M2 T26 S4 is the pre-accepted unified route-equivalence receiver after S3 completed the floating-score source-order audit.; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| transfer-051-t26-s4-to-s5-closure | M2 T26 S4 | M2 T26 S5 | 32 | M2 T26 S5 is the owner-approved pre-accepted closure receiver; S4 recorded the exact controlled ROM branch evidence and retains no unfinished custody.; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| transfer-052-t26-s5-to-s6-outer-victory | M2 T26 S5 | M2 T26 S6 | 2 | M2 T26 S6 is the pre-accepted source-order repair receiver after S5 completed its 30 direct labels and isolated the two outer-route residuals.; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| transfer-053-t26-s6-to-s7-outer-victory | M2 T26 S6 | M2 T26 S7 | 2 | M2 T26 S7 is the pre-accepted independent outer-route equivalence receiver after S6 restored the source call order with zero node credit.; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| transfer-054-t25-s6-to-s7-title-idle-prefix | M2 T25 S6 | M2 T25 S7 | 26 | M2 T25 S7 accepts S6's complete title/menu/demo receipt, credits only the first source-order idle prefix in this admission, and retains the other 22 labels for later exact branch admissions.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-055-t25-s7-to-s8-title-branches | M2 T25 S7 | M2 T25 S8 | 22 | M2 T25 S8 accepts every label not completed by S7; its first admission begins at the next source-order ResetTitle branch and retains the other labels for later exact branch packets.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-056-t25-s8-to-s9-title-branches | M2 T25 S8 | M2 T25 S9 | 21 | M2 T25 S9 accepts every title/menu/demo label not completed by S8; later packets must scope and prove each source-order branch independently.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-057-t25-s9-to-s10-title-branches | M2 T25 S9 | M2 T25 S10 | 20 | M2 T25 S10 accepts every title/menu/demo label not completed by S9; later packets must scope and prove each source-order branch independently.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-058-t25-s10-to-s11-title-branches | M2 T25 S10 | M2 T25 S11 | 19 | M2 T25 S11 accepts all labels not completed by S10.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-059-t25-s11-to-s12-title-branches | M2 T25 S11 | M2 T25 S12 | 18 | M2 T25 S12 accepts all labels not completed by S11.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-060-t25-s12-to-s13 | M2 T25 S12 | M2 T25 S13 | 17 | S13 accepts all uncompleted labels.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-061-t25-s13-to-s14 | M2 T25 S13 | M2 T25 S14 | 16 | S14 accepts all uncompleted labels.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-062-t25-s14-to-s15 | M2 T25 S14 | M2 T25 S15 | 15 | S15 accepts all uncompleted labels.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-063-t25-s15-to-s16 | M2 T25 S15 | M2 T25 S16 | 14 | S16 accepts every uncompleted title/menu/demo label after S15.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-064-t25-s16-to-s17 | M2 T25 S16 | M2 T25 S17 | 13 | S17 accepts every uncompleted title/menu/demo label after S16.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-065-t25-s17-to-s18 | M2 T25 S17 | M2 T25 S18 | 12 | S18 accepts every uncompleted title/menu/demo label after S17.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-066-t25-s18-to-s19 | M2 T25 S18 | M2 T25 S19 | 11 | S19 accepts every uncompleted title/menu/demo label after S18.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-067-t25-s19-to-s20 | M2 T25 S19 | M2 T25 S20 | 10 | S20 accepts every uncompleted title/menu/demo label after S19.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-068-t25-s20-to-s21 | M2 T25 S20 | M2 T25 S21 | 9 | S21 accepts every uncompleted title/menu/demo label after S20.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-069-t25-s21-to-s22 | M2 T25 S21 | M2 T25 S22 | 8 | S22 accepts every uncompleted title/menu/demo label after S21.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-070-t25-s22-to-s23 | M2 T25 S22 | M2 T25 S23 | 7 | S23 accepts every uncompleted title/menu/demo label after S22.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-071-t25-s23-to-s24 | M2 T25 S23 | M2 T25 S24 | 6 | S24 accepts every uncompleted title/menu/demo label after S23.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| transfer-072-t25-s24-to-s25 | M2 T25 S24 | M2 T25 S25 | 5 | S25 accepts the complete retained title-idle/demo chain after S24.; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| E-T24S2-T27S1-screen-root | M2 T24 S2 | M2 T27 S1 | 3 | Owner-approved source-order T27 admission; [record](../../docs/proposals/m2/screen-status.md) |
| E-T24S2-T27S1-screen-init-palette | M2 T24 S2 | M2 T27 S1 | 18 | Corrected owner-approved source-chain receipt; direct dependencies cannot remain outside S1.; [record](../../docs/proposals/m2/screen-status.md) |
| E-T24S2-T27S2-screen-status-text | M2 T24 S2 | M2 T27 S2 | 46 | Owner-approved source-order T27 S2 chain admission; [record](../../docs/proposals/m2/screen-status.md) |
| E-T27S1-T27S3-screen-dispatch-root | M2 T27 S1 | M2 T27 S3 | 1 | S1 closure requires full dispatch-table integration before credit; [record](../../docs/proposals/m2/screen-status.md) |
| E-T27S2-T27S3-parser-integration-root | M2 T27 S2 | M2 T27 S3 | 1 | Owner-approved T27 S2 pre-implementation scope correction; S3 is the registered accepted parser-integration receiver.; [record](../../docs/proposals/m2/screen-status.md) |
| E-T27S2-T27S3-parser-loop-tail | M2 T27 S2 | M2 T27 S3 | 2 | Owner-approved T27 S2 source-order dependency correction; S3 is the registered parser-integration receiver.; [record](../../docs/proposals/m2/screen-status.md) |
| transfer-073-t27-s3-to-t24-s2-parser-integration-deferred | M2 T27 S3 | M2 T24 S2 | 4 | Owner-authorized T24 S2 custody accepts the unresolved T27 integration roots until source-order T29 parser evidence is admitted.; [record](../../docs/proposals/m2/screen-status.md) |
| transfer-074-t18-s4-to-t28-s1-renderer | M2 T18 S4 | M2 T28 S1 | 13 | Owner-approved Td S8 source-order receipt for the first bounded T28 renderer/attribute chain.; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| transfer-075-t18-s4-to-t28-s2-color-rotation | M2 T18 S4 | M2 T28 S2 | 7 | Owner-approved T28 source-order S2 receipt.; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| transfer-076-t18-s4-to-t28-s3-block-graphics | M2 T18 S4 | M2 T28 S3 | 11 | Owner-approved T28 source-order S3 receipt.; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| transfer-077-t18-s4-to-t28-s4-area-data | M2 T18 S4 | M2 T28 S4 | 19 | Owner-approved T28 continuation; contiguous metatile, palette and message data chain.; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| transfer-078-t18-s4-to-t28-s5-name-tables | M2 T18 S4 | M2 T28 S5 | 5 | Owner-approved T28 source-order continuation.; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| transfer-079-t18-s4-to-t28-s6-joypad-vram | M2 T18 S4 | M2 T28 S6 | 12 | Owner-approved T28 source-order continuation.; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| transfer-080-t18-s4-to-t28-s7-status-arithmetic | M2 T18 S4 | M2 T28 S7 | 19 | Owner-approved T28 source-order continuation under the chain-based S delivery rule.; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| transfer-081-t18-s4-to-t28-s8-initialization-bootstrap | M2 T18 S4 | M2 T28 S8 | 16 | Owner-approved source-order continuation; T28 S8 acceptance is recorded in its active packet and proposal.; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| transfer-082-t18-s4-to-t29-s1-initialize-memory-loop | M2 T18 S4 | M2 T29 S1 | 4 | Owner-approved source-order continuation after T28 closure; T29 S1 accepts the four-label InitializeMemory loop chain.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-083-t18-s4-to-t29-s2-area-music | M2 T18 S4 | M2 T29 S2 | 5 | Owner-approved source-order continuation after T29 S1 closure.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-084-t18-s4-to-t29-s3-area-entry | M2 T18 S4 | M2 T29 S3 | 11 | Owner-approved source-order continuation after T29 S2 closure.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-085-t18-s4-to-t29-s4-life-mode | M2 T18 S4 | M2 T29 S4 | 17 | Owner-approved source-order continuation after T29 S3 closure.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-086-t18-s4-to-t29-s5-area-parser-dispatch | M2 T18 S4 | M2 T29 S5 | 14 | Owner-approved source-order continuation after T29 S4 closure.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-087-t18-s4-to-t29-s6-scenery-column | M2 T18 S4 | M2 T29 S6 | 20 | Owner-approved source-order continuation after T29 S5 closure.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-088-t18-s4-to-t29-s7-area-stream | M2 T18 S4 | M2 T29 S7 | 32 | Owner-approved source-order continuation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-089-t18-s4-to-t29-s8-special-objects | M2 T18 S4 | M2 T29 S8 | 22 | Owner-approved source-order continuation after T29 S7 closure.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-090-t18-s4-to-t29-s9-large-object-geometry | M2 T18 S4 | M2 T29 S9 | 22 | Owner-approved source-order continuation after T29 S8 closure.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-091-t18-s4-to-t29-s10-allocation-final-geometry | M2 T18 S4 | M2 T29 S10 | 10 | Owner-approved source-order continuation after T29 S9 closure.; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| transfer-097-t22-s5-to-t24-s2-legacy-object-residual | M2 T22 S5 | M2 T24 S2 | 113 | Owner-authorized M2 T24 S2 custody receives the obsolete T22 S5 object backlog until exact source-order T35--T37 chain admissions accept each label.; [record](../../docs/proposals/m2/blocks-items-misc.md) |
| transfer-098-t18-s4-to-t30-s1-rope-rendering | M2 T18 S4 | M2 T30 S1 | 3 | Owner-approved M2 T30/S1 source-order rope-chain receipt.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-099-t18-s4-to-t30-s2-coin-selector | M2 T18 S4 | M2 T30 S2 | 2 | Owner-approved M2 T30/S2 source-order coin-selector receipt.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-100-t18-s4-to-t30-s3-castle-column | M2 T18 S4 | M2 T30 S3 | 7 | Owner-approved M2 T30/S3 source-order castle-column receipt.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-101-t18-s4-to-t30-s4-row-column | M2 T18 S4 | M2 T30 S4 | 10 | Coordinator under owner-approved source-order continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-102-t18-s4-to-t30-s5-cannon | M2 T18 S4 | M2 T30 S5 | 3 | Coordinator under owner-approved source-order continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-103-t18-s4-to-t30-s6-staircase | M2 T18 S4 | M2 T30 S6 | 4 | Coordinator under owner-approved source-order continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-104-t18-s4-to-t30-s7-jumpspring | M2 T18 S4 | M2 T30 S7 | 1 | Coordinator under owner-approved source-order continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-105-t18-s4-to-t30-s8-item-blocks | M2 T18 S4 | M2 T30 S8 | 8 | Coordinator under owner-approved source-order continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-106-t18-s4-to-t30-s9-hole-underpart | M2 T18 S4 | M2 T30 S9 | 8 | Coordinator under owner-approved source-order continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-107-t18-s4-to-t30-s10-common-helpers | M2 T18 S4 | M2 T30 S10 | 6 | Coordinator under owner-approved source-order continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-108-t29-s7-to-t30-s11-parser-index | M2 T29 S7 | M2 T30 S11 | 1 | Coordinator under owner-approved M2 source-order recovery and queued corrective audit.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-109-t29-s9-to-t30-s12-draw-pipe | M2 T29 S9 | M2 T30 S12 | 1 | Coordinator under owner-approved M2 continuation and queued audit correction.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-110-t18-s4-to-t30-s13-block-buffer-address | M2 T18 S4 | M2 T30 S13 | 2 | Coordinator under owner-approved M2 source-order continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-111-t28-s8-to-t30-s13-initial-column | M2 T28 S8 | M2 T30 S13 | 1 | Coordinator accepts concrete producer contradiction under owner M2 continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-112-area-pointer-header | M2 T18 S4 | M2 T30 S14 | 22 | Coordinator under owner-approved source-order chain/dependency policy.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-113-loopback-data-consumer | M2 T18 S4 | M2 T19 S5 | 1 | Coordinator under owner-approved source-order chain/dependency policy.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-114-t29-s4-to-t30-s14-terminate-music | M2 T29 S4 | M2 T30 S14 | 1 | Coordinator accepts immediate caller contradiction under owner M2 continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-115-t18-s4-to-t19-s5-enemy-stream-data | M2 T18 S4 | M2 T19 S5 | 34 | Coordinator accepts enemy data with its existing ProcessEnemyData owner under source-order dependency policy.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-116-t18-s4-to-t30-s16-castle-scenes | M2 T18 S4 | M2 T30 S16 | 6 | Coordinator under owner-approved source-order implementation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-117-t29-s7-to-t30-s16-loop-command | M2 T29 S7 | M2 T30 S16 | 1 | Coordinator accepts concrete parser-consumer contradiction under M2 continuation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-118-t18-s4-to-t30-s17-ground-scenes | M2 T18 S4 | M2 T30 S17 | 22 | Coordinator under owner-approved source-order implementation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-119-t18-s4-to-t30-s18-underground-scenes | M2 T18 S4 | M2 T30 S18 | 3 | Coordinator under owner-approved source-order implementation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-120-t18-s4-to-t30-s19-water-scenes | M2 T18 S4 | M2 T30 S19 | 3 | Coordinator under owner-approved source-order implementation.; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| transfer-121-t24-s2-to-t31-s1-game-entry | M2 T24 S2 | M2 T31 S1 | 2 | Coordinator under owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-122-t24-s2-to-t31-s2-engine-chain | M2 T24 S2 | M2 T31 S2 | 9 | Coordinator under owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-123-t24-s2-to-t31-s2-engine-dependencies | M2 T24 S2 | M2 T31 S2 | 22 | Coordinator under owner-approved M2 continuation: required GameEngine dependencies; combined S2 delivery.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-124-t19-s5-to-t31-s2-cannon-callers | M2 T19 S5 | M2 T31 S2 | 4 | Coordinator under owner-approved continuing M2 mandate: source-identified cannon and engine-dispatch dependencies.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-125-t17-s6-to-t31-s2-cannon-graphics | M2 T17 S6 | M2 T31 S2 | 2 | Coordinator under owner-approved continuing M2 mandate: source-identified cannon and engine-dispatch dependencies.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-126-td-s5-to-t31-s2-warp-target | M2 Td S5 | M2 T31 S2 | 1 | Coordinator under owner-approved continuing M2 mandate: missing original enemy-vector target.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-127-t19-s5-to-t31-s2-normal-chain | M2 T19 S5 | M2 T31 S2 | 17 | Coordinator under owner-approved continuing M2 mandate: normal-enemy caller and movement chain required by engine dispatch.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-128-t17-s6-to-t31-s2-vertical-entry | M2 T17 S6 | M2 T31 S2 | 3 | Coordinator under owner-approved continuing M2 mandate: normal-enemy caller and movement chain required by engine dispatch.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-129-t17-s6-to-t31-s2-background-entry | M2 T17 S6 | M2 T31 S2 | 10 | Coordinator under owner-approved continuing M2 mandate: normal-enemy caller and movement chain required by engine dispatch.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-130-t17-s6-to-t31-s2-side-check | M2 T17 S6 | M2 T31 S2 | 4 | Coordinator under continuing owner-approved M2 mandate; complete bounded side-check prerequisite for admitted background chain.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-131-t31-enemy-caller-return | M2 T31 S2 | M2 T19 S5 | 6 | Coordinator under continuing owner-approved M2 mandate. Return six incomplete enemy caller/vector labels to accepted enemy closure custody for their original source-order slice; do not broaden the dispatcher chain.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-132-t31-scroll-chain | M2 T24 S2 | M2 T31 S3 | 10 | Coordinator under continuing owner-approved M2 mandate. Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-133-t24-s2-to-t31-s4-entry-modes | M2 T24 S2 | M2 T31 S4 | 10 | Coordinator under continuing owner-approved M2 mandate; next planned chain after closed S3.; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| transfer-134-t23-s5-to-t32-s1-player-control | M2 T23 S5 | M2 T32 S1 | 13 | Coordinator under continuing owner-approved source-order M2 mandate.; [record](../../docs/history/M2-T32-player-control-modes.md) |
| transfer-135-t23-s5-to-t32-s2-vine-pipe | M2 T23 S5 | M2 T32 S2 | 11 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T32-player-control-modes.md) |
| transfer-136-t23-s5-to-t32-s3-timer-state | M2 T23 S5 | M2 T32 S3 | 14 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T32-player-control-modes.md) |
| transfer-137-t23-s5-to-t32-s4-end-level | M2 T23 S5 | M2 T32 S4 | 10 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T32-player-control-modes.md) |
| transfer-138-t23-s5-to-t33-s1-movement-state | M2 T23 S5 | M2 T33 S1 | 15 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T33-player-movement-state.md) |
| transfer-139-t23-s5-to-t33-s2-climbing | M2 T23 S5 | M2 T33 S2 | 8 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T33-player-movement-state.md) |
| transfer-140-t23-s5-to-t33-s3-physics | M2 T23 S5 | M2 T33 S3 | 28 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T33-player-movement-state.md) |
| transfer-141-t23-s5-to-t33-s3-physics | M2 T23 S5 | M2 T33 S4 | 12 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T33-player-movement-state.md) |
| transfer-142-td-s5-to-t34-s1-fireball-dispatch | M2 Td S5 | M2 T34 S1 | 5 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| transfer-143-td-s5-to-t34-s2-fireball-core | M2 Td S5 | M2 T34 S2 | 6 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| transfer-144-td-s5-to-t35-s1-bubbles | M2 Td S5 | M2 T35 S1 | 8 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| transfer-145-td-s5-to-t35-s2-timer | M2 Td S5 | M2 T35 S2 | 4 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| transfer-146-t24-s2-to-t35-s3-jumpspring | M2 T24 S2 | M2 T35 S3 | 7 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| transfer-147-t24-s2-to-t35-s4-vine-setup | M2 T24 S2 | M2 T35 S4 | 3 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| transfer-148-t24-s2-to-t36-s1-vine-actor | M2 T24 S2 | M2 T36 S1 | 6 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| transfer-149-t24-s2-to-t36-s2-hammer | M2 T24 S2 | M2 T36 S2 | 10 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| transfer-150-t24-s2-to-t36-s3-coin-allocation | M2 T24 S2 | M2 T36 S3 | 6 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| transfer-151-t24-s2-to-t36-s4-misc-lifetime | M2 T24 S2 | M2 T36 S4 | 6 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| transfer-152-t24-s2-to-t36-s5-score-hud | M2 T24 S2 | M2 T36 S5 | 9 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| transfer-153-t24-s2-to-t36-s6-power-up-init | M2 T24 S2 | M2 T36 S6 | 4 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| transfer-154-t24-s2-to-t37-s1-power-up-actor | M2 T24 S2 | M2 T37 S1 | 6 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-155-t24-s2-to-t37-s2-head-hit | M2 T24 S2 | M2 T37 S2 | 13 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-156-t24-s2-to-t37-s3-block-content | M2 T24 S2 | M2 T37 S3 | 11 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-157-t24-s2-to-t37-s4-shatter-chunks | M2 T24 S2 | M2 T37 S4 | 4 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-158-to-t37-s5-block-lifetime | M2 T24 S2 | M2 T37 S5 | 5 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-159-to-t37-s6-block-replacement | M2 T24 S2 | M2 T37 S6 | 1 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-160-to-t37-s6-block-replacement | M2 T18 S4 | M2 T37 S6 | 2 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-161-to-t37-s7-horizontal | M2 T17 S6 | M2 T37 S7 | 6 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-162-to-t37-s8-vertical-adapters | M2 T17 S6 | M2 T37 S8 | 11 | Coordinator under continuing owner-approved M2 source-order mandate; retained matches keep prior conformance evidence.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-163-to-t37-s8-vertical-adapters | M2 T31 S2 | M2 T37 S8 | 3 | Coordinator under continuing owner-approved M2 source-order mandate; retained matches keep prior conformance evidence.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-164-to-t37-s9-common-gravity | M2 T17 S6 | M2 T37 S9 | 12 | Coordinator under continuing owner-approved M2 source-order mandate.; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| transfer-165-to-t38-s1-enemy-loops | M2 T19 S5 | M2 T38 S1 | 19 | Coordinator under continuing owner-approved source-order M2 mandate; explicit loop dependencies.; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| transfer-166-to-t38-s2-enemy-stream | M2 T19 S5 | M2 T38 S2 | 19 | Coordinator under continuing owner-approved source-order M2 mandate.; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| transfer-167-to-t38-s3-initializer-vector | M2 T19 S5 | M2 T38 S3 | 3 | Coordinator under continuing owner-approved source-order M2 mandate.; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| transfer-168-to-t38-s4-common-initializers | M2 T19 S5 | M2 T38 S4 | 23 | Coordinator under continuing owner-approved source-order M2 mandate.; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| transfer-169-to-t38-s5-lakitu-spiny | M2 T19 S5 | M2 T38 S5 | 13 | Coordinator under continuing owner-approved source-order M2 mandate.; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| transfer-170-to-t38-s6-firebar | M2 T19 S5 | M2 T38 S6 | 7 | Coordinator under continuing owner-approved source-order M2 mandate; admits missing immediate dependency, no placeholder.; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| transfer-171-to-t38-s7-flying-fish | M2 T19 S5 | M2 T38 S7 | 10 | Coordinator under continuing owner-approved source-order M2 mandate.; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| transfer-172-to-t39-s1 | M2 T19 S5 | M2 T39 S1 | 12 | Coordinator under continuing owner-approved source-order M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-173-to-t39-s1 | M2 T38 S6 | M2 T39 S1 | 3 | Coordinator under continuing owner-approved source-order M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-174-to-t39-s2 | M2 T19 S5 | M2 T39 S2 | 5 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-175-to-t39-s3 | M2 T19 S5 | M2 T39 S3 | 14 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-176-to-t39-s4 | M2 T19 S5 | M2 T39 S4 | 8 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-177-to-t39-s5 | M2 T19 S5 | M2 T39 S5 | 9 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-178-to-t39-s6 | M2 T19 S5 | M2 T39 S6 | 20 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-179-to-t39-s7 | M2 T19 S5 | M2 T39 S7 | 3 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-180-to-t39-s7 | M2 T31 S2 | M2 T39 S7 | 1 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-181-to-t39-s8 | M2 T19 S5 | M2 T39 S8 | 4 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-182-to-t39-s9 | M2 T19 S5 | M2 T39 S9 | 6 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-183-to-t39-s9 | M2 T31 S2 | M2 T39 S9 | 1 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| transfer-184-to-t40-s1 | M2 T19 S5 | M2 T40 S1 | 2 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-185-to-t40-s2 | M2 T19 S5 | M2 T40 S2 | 11 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-186-to-t40-s2 | M2 T31 S2 | M2 T40 S2 | 13 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-187-to-t40-s3 | M2 T19 S5 | M2 T40 S3 | 5 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-188-to-t40-s4 | M2 T19 S5 | M2 T40 S4 | 10 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-189-to-t40-s5 | M2 T19 S5 | M2 T40 S5 | 16 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-190-to-t40-s6 | M2 T19 S5 | M2 T40 S6 | 2 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-191-to-t40-s7 | M2 T19 S5 | M2 T40 S7 | 7 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-192-to-t40-s8 | M2 T19 S5 | M2 T40 S8 | 32 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-193-to-t40-s9 | M2 T19 S5 | M2 T40 S9 | 6 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-194-to-t40-s9 | M2 T19 S5 | M2 T40 S10 | 16 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| transfer-195-to-t41-s1 | M2 T19 S5 | M2 T41 S1 | 6 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-196-to-t41-s2 | M2 T19 S5 | M2 T41 S2 | 17 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-197-to-t41-s2 | M2 T38 S1 | M2 T41 S2 | 2 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-198-to-t41-s3 | M2 T19 S5 | M2 T41 S3 | 4 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-199-to-t41-s4 | M2 T19 S5 | M2 T41 S4 | 9 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-200-to-t41-s4 | M2 T39 S1 | M2 T41 S4 | 3 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-201-to-t41-s5 | M2 T19 S5 | M2 T41 S5 | 3 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-202-to-t41-s6 | M2 T19 S5 | M2 T41 S6 | 20 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-203-to-t41-s7 | M2 T19 S5 | M2 T41 S7 | 6 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-204-to-t41-s8 | M2 T19 S5 | M2 T41 S8 | 2 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-205-to-t41-s9 | M2 T19 S5 | M2 T41 S9 | 26 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-206-to-t41-s10 | M2 T19 S5 | M2 T41 S10 | 6 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-207-to-t41-s10 | M2 T19 S5 | M2 T41 S11 | 9 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-208-to-t41-s12 | M2 T19 S5 | M2 T41 S12 | 5 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-209-to-t41-s13 | M2 T19 S5 | M2 T41 S13 | 5 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| transfer-210-to-t42-s1 | M2 T17 S6 | M2 T42 S1 | 6 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-211-to-t42-s2 | M2 T17 S6 | M2 T42 S2 | 11 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-212-to-t42-s3 | M2 T17 S6 | M2 T42 S3 | 3 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-213-to-t42-s4 | M2 T17 S6 | M2 T42 S4 | 6 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-214-to-t42-s5 | M2 T17 S6 | M2 T42 S5 | 34 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-215-to-t42-s6 | M2 T17 S6 | M2 T42 S6 | 16 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-216-to-t42-s7 | M2 T17 S6 | M2 T42 S7 | 14 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-217-to-t42-s8 | M2 T17 S6 | M2 T42 S8 | 4 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-218-to-t42-s8 | M2 T17 S6 | M2 T42 S9 | 4 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| transfer-219-to-t43-s1 | M2 T17 S6 | M2 T43 S1 | 31 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-220-to-t43-s2 | M2 T17 S6 | M2 T43 S2 | 3 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-221-to-t43-s3 | M2 T17 S6 | M2 T43 S3 | 14 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-222-to-t43-s4 | M2 T17 S6 | M2 T43 S4 | 7 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-223-to-t43-s5 | M2 T17 S6 | M2 T43 S5 | 3 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-224-to-t43-s6 | M2 T17 S6 | M2 T43 S6 | 5 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-225-to-t43-s7 | M2 T17 S6 | M2 T43 S7 | 7 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-226-to-t43-s7 | M2 T31 S2 | M2 T43 S7 | 1 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-227-to-t43-s8 | M2 T17 S6 | M2 T43 S8 | 12 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-228-to-t43-s8 | M2 T31 S2 | M2 T43 S8 | 6 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-229-to-t43-s9 | M2 T17 S6 | M2 T43 S9 | 14 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-230-to-t43-s10 | M2 T17 S6 | M2 T43 S10 | 9 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-231-to-t43-s11 | M2 T17 S6 | M2 T43 S11 | 3 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-232-to-t43-s12 | M2 T17 S6 | M2 T43 S12 | 3 | Coordinator under continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-233-to-t43-s13 | M2 T17 S6 | M2 T43 S13 | 11 | Coordinator accepts the contiguous source-order bounding-box entry chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-234-to-t43-s14 | M2 T17 S6 | M2 T43 S14 | 7 | Coordinator accepts this contiguous source-order chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-235-to-t43-s15 | M2 T17 S6 | M2 T43 S15 | 7 | Coordinator accepts this contiguous source-order collision geometry chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| transfer-236-to-t44-s1 | M2 T17 S6 | M2 T44 S1 | 14 | Coordinator accepts this contiguous source-order block-buffer core chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-237-to-t44-s2 | M2 T17 S6 | M2 T44 S2 | 6 | Coordinator accepts this contiguous source-order vine graphics chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-238-to-t44-s3 | M2 T17 S6 | M2 T44 S3 | 14 | Coordinator accepts this contiguous source-order shared OAM and hammer graphics chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-239-to-t44-s4 | M2 T17 S6 | M2 T44 S4 | 9 | Coordinator accepts the contiguous source-order flagpole graphics and generic OAM dump-helper chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-240-to-t44-s5 | M2 T17 S6 | M2 T44 S5 | 11 | Coordinator accepts the contiguous source-order large-platform graphics chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-241-to-t44-s6 | M2 T17 S6 | M2 T44 S6 | 5 | Coordinator accepts the contiguous source-order floatey-number and jumping-coin graphics chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-242-to-t44-s7 | M2 T17 S6 | M2 T44 S7 | 6 | Coordinator accepts the contiguous source-order power-up graphics chain under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-243-to-t44-s8 | M2 T17 S6 | M2 T44 S8 | 42 | Coordinator accepts the contiguous source-order EnemyGfxHandler tree under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-244-to-t44-s8 | M2 T31 S2 | M2 T44 S8 | 2 | Coordinator accepts the contiguous source-order EnemyGfxHandler tree under the continuing owner-approved M2 mandate.; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| transfer-245-to-t45-s1 | M2 T17 S6 | M2 T45 S1 | 13 | Coordinator accepts the contiguous original EnemyGfxHandler mirror/row/offscreen tail under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| transfer-246-to-t45-s2 | M2 T17 S6 | M2 T45 S2 | 14 | Coordinator accepts the source-contiguous DrawBlock and DrawBrickChunks OAM chain under the owner-approved M2 mandate.; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| transfer-247-to-t45-s3 | M2 T16 S4 | M2 T45 S3 | 2 | Coordinator accepts the contiguous projectile and explosion OAM tail under the owner-approved M2 mandate.; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| transfer-248-to-t45-s3 | M2 T17 S6 | M2 T45 S3 | 5 | Coordinator accepts the contiguous projectile and explosion OAM tail under the owner-approved M2 mandate.; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| transfer-249-to-t45-s4 | M2 T17 S6 | M2 T45 S4 | 6 | Coordinator accepts the contiguous small-platform OAM chain under the owner-approved M2 mandate.; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| transfer-250-to-t45-s5 | M2 T17 S6 | M2 T45 S5 | 3 | Coordinator accepts the source-order bubble/player graphics data chain under the owner-approved M2 mandate.; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| transfer-251-to-t45-s5 | M2 T16 S4 | M2 T45 S5 | 2 | Coordinator accepts the source-order bubble/player graphics data chain under the owner-approved M2 mandate.; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| transfer-252-to-t46-s1 | M2 T16 S4 | M2 T46 S1 | 13 | Coordinator accepts the source-order player graphics dispatch and offscreen chain under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| transfer-253-to-t46-s2 | M2 T16 S4 | M2 T46 S2 | 5 | Coordinator accepts the source-order intermediate/player row-renderer chain under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| transfer-254-to-t46-s3 | M2 T16 S4 | M2 T46 S3 | 13 | Coordinator accepts the source-order player action and animation control chain under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| transfer-255-to-t46-s4 | M2 T16 S4 | M2 T46 S4 | 12 | Coordinator accepts the source-order size offset, transformation and attribute chain under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| transfer-256-to-t47-s1 | M2 T16 S4 | M2 T47 S1 | 1 | Coordinator accepts the exact player attribute exit label under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| transfer-257-to-t47-s2 | M2 T16 S4 | M2 T47 S2 | 9 | Coordinator accepts the nine-label shared relative-coordinate chain under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| transfer-258-to-t47-s3 | M2 T16 S4 | M2 T47 S3 | 1 | Coordinator accepts the exact player offscreen entry under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| transfer-259-to-t47-s4 | M2 T16 S4 | M2 T47 S4 | 26 | Coordinator accepts the 26-label shared offscreen-bit chain under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| transfer-260-to-t47-s5 | M2 T16 S4 | M2 T47 S5 | 3 | Coordinator accepts the three-label shared sprite-row writer under the continuing owner-approved M2 mandate.; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| transfer-261-to-t48-s1 | M2 Td S4 | M2 T48 S1 | 13 | Coordinator accepts the 13-label SoundEngine entry chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| transfer-262-to-t48-s2 | M2 Td S4 | M2 T48 S2 | 9 | Coordinator accepts the nine-label APU register/frequency helper chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| transfer-263-to-t48-s3 | M2 Td S4 | M2 T48 S3 | 14 | Coordinator accepts the 14-label square-one jump, flagpole and throw phase chain under the owner-approved source-order mandate.; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| transfer-264-to-t48-s4 | M2 Td S4 | M2 T48 S4 | 16 | Coordinator accepts the 16-label square-one dispatcher, swim/stomp, smack, pipe and lifetime chain under the owner-approved source-order mandate.; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| transfer-265-to-t48-s5 | M2 Td S4 | M2 T48 S5 | 18 | Coordinator accepts the 18-label square-two effect data, phase and lifetime chain under the owner-approved source-order mandate.; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| transfer-266-to-t48-s6 | M2 Td S4 | M2 T48 S6 | 4 | Coordinator accepts the four-label square-two queue and buffer dispatcher chain under the owner-approved source-order mandate.; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| transfer-267-to-t49-s1 | M2 Td S4 | M2 T49 S1 | 14 | Coordinator accepts the 14-label remaining square-two effect chain under the owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-268-to-t49-s2 | M2 Td S4 | M2 T49 S2 | 12 | Coordinator accepts the 12-label noise-effect and music-handoff chain under the owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-269-to-t49-s3 | M2 Td S4 | M2 T49 S3 | 10 | Coordinator accepts the 10-label music selection and header-load chain under the owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-270-to-t49-s4 | M2 Td S4 | M2 T49 S4 | 11 | Coordinator accepts the 11-label square-two music-stream and envelope-tail chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-271-to-t49-s5 | M2 Td S4 | M2 T49 S5 | 8 | Coordinator accepts the next eight-label square-one music-stream and alternate-control chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-272-to-t49-s6 | M2 Td S4 | M2 T49 S6 | 6 | Coordinator accepts the six-label triangle music-stream and control-register chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-273-to-t49-s7 | M2 Td S4 | M2 T49 S7 | 8 | Coordinator accepts the eight-label noise music beat chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-274-to-t49-s8 | M2 Td S4 | M2 T49 S8 | 9 | Coordinator accepts the nine-label shared music helper chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-275-to-t49-s9 | M2 Td S4 | M2 T49 S9 | 23 | Coordinator accepts the 23-label music-header table and record chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| transfer-276-to-t50-s1 | M2 Td S4 | M2 T50 S1 | 21 | Coordinator accepts the 21-label music-stream payload chain under the continuing owner-approved M2 source-order mandate.; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| transfer-277-to-t50-s2 | M2 Td S4 | M2 T50 S2 | 5 | Coordinator; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| transfer-278-to-t50-s3 | M2 Td S4 | M2 T50 S3 | 2 | Coordinator under the continuing owner-approved M2 source-order mandate; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| transfer-279-to-t51-s1 | M2 T24 S2 | M2 T51 S1 | 1 | Coordinator under the continuing owner-approved M2 completion mandate; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| transfer-280-to-t51-s2 | M2 T24 S2 | M2 T51 S2 | 4 | Coordinator accepts the source-contiguous screen/parser output chain under the continuing owner-approved M2 completion mandate.; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| transfer-281-to-t51-s3 | M2 T29 S8 | M2 T51 S3 | 1 | Coordinator accepts the residual KillEnemies primitive under the continuing owner-approved M2 completion mandate.; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| transfer-282-to-t51-s4 | M2 T19 S5 | M2 T51 S4 | 34 | Coordinator accepts the residual original enemy-stream data chain under the continuing owner-approved M2 completion mandate.; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| t52-s1-nmi-parent | M2 T51 S1 | M2 T52 S1 | 1 | Owner-approved T52 corrective admission under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| t52-s1-random-prefix | M2 T22 S25 | M2 T52 S1 | 1 | Owner-approved T52 corrective admission under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| t52-s1-sprite-prefix | M2 T22 S26 | M2 T52 S1 | 1 | Owner-approved T52 corrective admission under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| t52-s2-chkselect | M2 T25 S10 | M2 T52 S2 | 1 | Owner-approved T52 corrective admission under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| t52-s2-chkworldsel | M2 T25 S11 | M2 T52 S2 | 1 | Owner-approved T52 corrective admission under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| t52-s3-floatey | M2 T26 S5 | M2 T52 S3 | 3 | Owner-approved T52 corrective admission under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| t52-s3-score | M2 T36 S5 | M2 T52 S3 | 1 | Owner-approved T52 corrective admission under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| t52-s4-background-palette | M2 T27 S1 | M2 T52 S4 | 3 | Owner-approved T52 corrective continuation under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| transfer-m2-t27-s2-to-t52-s5-b3-timeup | M2 T27 S2 | M2 T52 S5 | 3 | Owner-approved T52 corrective continuation under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| transfer-m2-t44-s5-to-t52-s6-h9-platform-y | M2 T44 S5 | M2 T52 S6 | 1 | Owner-approved T52 corrective continuation under the continuing M2 ROM-equivalence mandate.; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| transfer-283-t22-s9-to-t53-s3 | M2 T22 S9 | M2 T53 S3 | 1 | Owner directed that every current-audit mismatch is repaired and re-audited to zero before any successor S admission.; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| transfer-t70-s2-parser-1 | M2 T29 S7 | M2 T70 S2 | 27 | Coordinator under owner ongoing original-source M2 mandate accepts bounded29-node parser maintenance receipt before implementation.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s2-parser-2 | M2 T30 S11 | M2 T70 S2 | 1 | Coordinator under owner ongoing original-source M2 mandate accepts bounded29-node parser maintenance receipt before implementation.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s2-parser-3 | M2 T30 S16 | M2 T70 S2 | 1 | Coordinator under owner ongoing original-source M2 mandate accepts bounded29-node parser maintenance receipt before implementation.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s4-nmi-1 | M2 T22 S15 | M2 T70 S4 | 3 | Coordinator under owner ongoing M2 mandate accepts6-node NMI prefix maintenance before shared repair.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s4-nmi-2 | M2 T52 S1 | M2 T70 S4 | 1 | Coordinator under owner ongoing M2 mandate accepts6-node NMI prefix maintenance before shared repair.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s4-nmi-3 | M2 T53 S3 | M2 T70 S4 | 1 | Coordinator under owner ongoing M2 mandate accepts6-node NMI prefix maintenance before shared repair.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s4-nmi-4 | M2 T22 S23 | M2 T70 S4 | 1 | Coordinator under owner ongoing M2 mandate accepts6-node NMI prefix maintenance before shared repair.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s6-phase-1 | M2 T52 S1 | M2 T70 S6 | 2 | Coordinator accepts bounded sprite-zero visible-phase maintenance repair under owner ongoing M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s6-phase-2 | M2 T22 S26 | M2 T70 S6 | 4 | Coordinator accepts bounded sprite-zero visible-phase maintenance repair under owner ongoing M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s6-child-1 | M2 T22 S26 | M2 T70 S6 | 3 | Coordinator accepts shared sprite-clear entry dependencies under owner ongoing M2 corrective mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s7-shuffle-1 | M2 T22 S27 | M2 T70 S7 | 6 | Coordinator accepts bounded shared shuffle/preset repair under owner ongoing M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s9-input-1 | M2 T22 S24 | M2 T70 S9 | 6 | Coordinator accepts shared input/pause repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s9-input-2 | M2 T28 S6 | M2 T70 S9 | 4 | Coordinator accepts shared input/pause repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-1 | M2 T25 S20 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-2 | M2 T25 S7 | M2 T70 S10 | 3 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-3 | M2 T25 S9 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-4 | M2 T52 S2 | M2 T70 S10 | 2 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-5 | M2 T25 S12 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-6 | M2 T25 S13 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-7 | M2 T25 S14 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-8 | M2 T25 S8 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-9 | M2 T25 S15 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-10 | M2 T25 S16 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-11 | M2 T25 S17 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-12 | M2 T25 S18 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-13 | M2 T25 S19 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-14 | M2 T25 S21 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-15 | M2 T25 S22 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-16 | M2 T25 S23 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-17 | M2 T25 S24 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-18 | M2 T25 S25 | M2 T70 S10 | 5 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s11-victory-1 | M2 T26 S5 | M2 T70 S11 | 14 | Coordinator receives victory-message/final shared-call repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s11-victory-2 | M2 T30 S14 | M2 T70 S11 | 1 | Coordinator receives victory-message/final shared-call repair under owner ongoing mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s12-floatey-1 | M2 T26 S5 | M2 T70 S12 | 7 | Coordinator receives original floating-score chain under owner ongoing M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s12-floatey-2 | M2 T52 S3 | M2 T70 S12 | 3 | Coordinator receives original floating-score chain under owner ongoing M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s13-palette-1 | M2 T27 S1 | M2 T70 S13 | 16 | Coordinator accepts screen palette source-order maintenance under owner M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s13-palette-2 | M2 T52 S4 | M2 T70 S13 | 3 | Coordinator accepts screen palette source-order maintenance under owner M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s14-hud-1 | M2 T27 S2 | M2 T70 S14 | 9 | Coordinator accepts under owner ongoing M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s14-hud-2 | M2 T52 S5 | M2 T70 S14 | 3 | Coordinator accepts under owner ongoing M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s15-startup-1 | M2 T22 S14 | M2 T70 S15 | 7 | Coordinator accepts original reset/startup subtree under owner M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s15-startup-2 | M2 T28 S5 | M2 T70 S15 | 4 | Coordinator accepts original reset/startup subtree under owner M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s15-startup-3 | M2 T28 S6 | M2 T70 S15 | 2 | Coordinator accepts original reset/startup subtree under owner M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s15-startup-4 | M2 T29 S1 | M2 T70 S15 | 4 | Coordinator accepts original reset/startup subtree under owner M2 mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-title-pointer-1 | M2 T27 S2 | M2 T70 S17 | 3 | Coordinator under standing owner M2 repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-column-output-1 | M2 T28 S1 | M2 T70 S17 | 11 | Coordinator under owner same-S M2 repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-parser-output-1 | M2 T70 S2 | M2 T70 S17 | 29 | Coordinator under owner same-S M2 repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-parser-output-2 | M2 T29 S7 | M2 T70 S17 | 3 | Coordinator under owner same-S M2 repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-castle-counter-1 | M2 T29 S9 | M2 T70 S17 | 6 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-pipe-scratch-1 | M2 T29 S9 | M2 T70 S17 | 6 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-scenery-output-1 | M2 T29 S6 | M2 T70 S17 | 19 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-1 | M2 T22 S28 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-2 | M2 T25 S7 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-3 | M2 T26 S5 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-4 | M2 T29 S5 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-5 | M2 T29 S8 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-6 | M2 T31 S1 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-7 | M2 T31 S4 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-8 | M2 T33 S1 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-hole-threshold-1 | M2 T32 S1 | M2 T70 S17 | 2 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-raw-pipe-2 | M2 T29 S9 | M2 T70 S17 | 4 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-raw-pipe-3 | M2 T30 S12 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-raw-pipe-4 | M2 T30 S9 | M2 T70 S17 | 4 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-whirlpool-1 | M2 T31 S2 | M2 T70 S17 | 3 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-fireball-index-1 | M2 T34 S2 | M2 T70 S17 | 2 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-color-counter-1 | M2 T28 S2 | M2 T70 S17 | 4 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-injury-palette-1 | M2 T70 S13 | M2 T70 S17 | 6 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-bowser-timer-1 | M2 T41 S4 | M2 T70 S17 | 3 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-bbox-scratch-1 | M2 T43 S13 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-platform-oam-index-1 | M2 T52 S6 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-platform-oam-index-2 | M2 T44 S5 | M2 T70 S17 | 10 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-p114-duplicate | M2 T39 S1 | M2 T70 S17 | 3 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-p115-platform-0 | M2 T38 S4 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-p115-platform-1 | M2 T39 S6 | M2 T70 S17 | 17 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| transfer-t70-s17-p123-rembridge | M2 T28 S3 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/history/m2/t70-final-current-certification.md) |
| m3-t27-s2-ppu-state-1 | M2 T70 S15 | M3 T27 S2 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s2-ppu-state-2 | M2 T70 S4 | M3 T27 S2 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s2-ppu-state-3 | M2 T22 S25 | M3 T27 S2 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s2-ppu-state-4 | M2 T70 S6 | M3 T27 S2 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s2-ppu-state-5 | M2 T70 S17 | M3 T27 S2 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s2-ppu-state-6 | M2 T70 S10 | M3 T27 S2 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s2-ppu-state-7 | M2 T26 S7 | M3 T27 S2 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s2-ppu-state-8 | M2 T28 S6 | M3 T27 S2 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s2-ppu-state-9 | M2 T31 S3 | M3 T27 S2 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-1 | M3 T27 S2 | M3 T27 S4 | 28 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-2 | M2 T70 S15 | M3 T27 S4 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-3 | M2 T70 S4 | M3 T27 S4 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-4 | M2 T22 S25 | M3 T27 S4 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-5 | M2 T70 S6 | M3 T27 S4 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-6 | M2 T70 S9 | M3 T27 S4 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-7 | M2 T70 S7 | M3 T27 S4 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-8 | M2 T70 S10 | M3 T27 S4 | 23 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-9 | M2 T70 S17 | M3 T27 S4 | 100 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-10 | M2 T26 S5 | M3 T27 S4 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-11 | M2 T70 S11 | M3 T27 S4 | 15 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-12 | M2 T51 S2 | M3 T27 S4 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-13 | M2 T27 S1 | M3 T27 S4 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-14 | M2 T70 S13 | M3 T27 S4 | 13 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-15 | M2 T70 S14 | M3 T27 S4 | 12 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-16 | M2 T27 S2 | M3 T27 S4 | 28 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-17 | M2 T28 S2 | M3 T27 S4 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-18 | M2 T28 S3 | M3 T27 S4 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-19 | M2 T28 S1 | M3 T27 S4 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-20 | M2 T28 S4 | M3 T27 S4 | 19 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-21 | M2 T28 S5 | M3 T27 S4 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-22 | M2 T28 S7 | M3 T27 S4 | 19 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-23 | M2 T28 S8 | M3 T27 S4 | 15 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-24 | M2 T30 S13 | M3 T27 S4 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-25 | M2 T29 S2 | M3 T27 S4 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-26 | M2 T29 S4 | M3 T27 S4 | 16 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-27 | M2 T29 S5 | M3 T27 S4 | 13 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-28 | M2 T29 S6 | M3 T27 S4 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-29 | M2 T29 S8 | M3 T27 S4 | 20 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-30 | M2 T51 S3 | M3 T27 S4 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-31 | M2 T29 S9 | M3 T27 S4 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-32 | M2 T29 S10 | M3 T27 S4 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-33 | M2 T30 S1 | M3 T27 S4 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-34 | M2 T30 S2 | M3 T27 S4 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-35 | M2 T30 S3 | M3 T27 S4 | 7 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-36 | M2 T30 S4 | M3 T27 S4 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-37 | M2 T30 S5 | M3 T27 S4 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-38 | M2 T30 S6 | M3 T27 S4 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-39 | M2 T30 S7 | M3 T27 S4 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-40 | M2 T30 S8 | M3 T27 S4 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-41 | M2 T30 S9 | M3 T27 S4 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-42 | M2 T30 S10 | M3 T27 S4 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s4-core-roots-43 | M2 T30 S14 | M3 T27 S4 | 22 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-1 | M2 T70 S12 | M3 T27 S5 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-2 | M3 T27 S4 | M3 T27 S5 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-3 | M2 T29 S3 | M3 T27 S5 | 11 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-4 | M2 T22 S5 | M3 T27 S5 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-5 | M2 T38 S1 | M3 T27 S5 | 17 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-6 | M2 T51 S4 | M3 T27 S5 | 34 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-7 | M2 T32 S1 | M3 T27 S5 | 11 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-8 | M2 T70 S17 | M3 T27 S5 | 44 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-9 | M2 T32 S2 | M3 T27 S5 | 11 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-10 | M2 T32 S3 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-11 | M2 T32 S4 | M3 T27 S5 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-12 | M2 T33 S1 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-13 | M2 T33 S2 | M3 T27 S5 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-14 | M2 T33 S3 | M3 T27 S5 | 28 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-15 | M2 T33 S4 | M3 T27 S5 | 12 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-16 | M2 T34 S1 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-17 | M2 T34 S2 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-18 | M2 T35 S1 | M3 T27 S5 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-19 | M2 T35 S2 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-20 | M2 T31 S2 | M3 T27 S5 | 27 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-21 | M2 T35 S3 | M3 T27 S5 | 7 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-22 | M2 T35 S4 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-23 | M2 T36 S1 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-24 | M2 T36 S2 | M3 T27 S5 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-25 | M2 T36 S3 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-26 | M2 T36 S4 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-27 | M2 T36 S5 | M3 T27 S5 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-28 | M2 T52 S3 | M3 T27 S5 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-29 | M2 T36 S6 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-30 | M2 T37 S1 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-31 | M2 T37 S2 | M3 T27 S5 | 13 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-32 | M2 T37 S3 | M3 T27 S5 | 11 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-33 | M2 T37 S4 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-34 | M2 T37 S5 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-35 | M2 T37 S6 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-36 | M2 T37 S7 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-37 | M2 T37 S8 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-38 | M2 T37 S9 | M3 T27 S5 | 12 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-39 | M2 T38 S2 | M3 T27 S5 | 19 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-40 | M2 T38 S3 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-41 | M2 T38 S4 | M3 T27 S5 | 22 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-42 | M2 T38 S5 | M3 T27 S5 | 13 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-43 | M2 T38 S6 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-44 | M2 T38 S7 | M3 T27 S5 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-45 | M2 T39 S1 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-46 | M2 T39 S2 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-47 | M2 T39 S3 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-48 | M2 T39 S4 | M3 T27 S5 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-49 | M2 T39 S5 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-50 | M2 T39 S6 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-51 | M2 T39 S7 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-52 | M2 T39 S8 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-53 | M2 T39 S9 | M3 T27 S5 | 7 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-54 | M2 T40 S1 | M3 T27 S5 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-55 | M2 T40 S2 | M3 T27 S5 | 24 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-56 | M2 T40 S3 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-57 | M2 T40 S4 | M3 T27 S5 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-58 | M2 T40 S5 | M3 T27 S5 | 16 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-59 | M2 T40 S6 | M3 T27 S5 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-60 | M2 T40 S7 | M3 T27 S5 | 7 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-61 | M2 T40 S8 | M3 T27 S5 | 32 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-62 | M2 T40 S9 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-63 | M2 T40 S10 | M3 T27 S5 | 16 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-64 | M2 T41 S1 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-65 | M2 T41 S2 | M3 T27 S5 | 19 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-66 | M2 T41 S3 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-67 | M2 T41 S4 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-68 | M2 T41 S5 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-69 | M2 T41 S6 | M3 T27 S5 | 20 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-70 | M2 T41 S7 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-71 | M2 T41 S8 | M3 T27 S5 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-72 | M2 T41 S9 | M3 T27 S5 | 26 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-73 | M2 T41 S10 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-74 | M2 T41 S11 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-75 | M2 T41 S12 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-76 | M2 T41 S13 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-77 | M2 T42 S1 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-78 | M2 T42 S2 | M3 T27 S5 | 11 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-79 | M2 T42 S3 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-80 | M2 T42 S4 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-81 | M2 T42 S5 | M3 T27 S5 | 34 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-82 | M2 T42 S6 | M3 T27 S5 | 16 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-83 | M2 T42 S7 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-84 | M2 T42 S8 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-85 | M2 T42 S9 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-86 | M2 T43 S1 | M3 T27 S5 | 31 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-87 | M2 T43 S2 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-88 | M2 T43 S3 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-89 | M2 T43 S4 | M3 T27 S5 | 7 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-90 | M2 T43 S5 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-91 | M2 T43 S6 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-92 | M2 T43 S7 | M3 T27 S5 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-93 | M2 T43 S8 | M3 T27 S5 | 18 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-94 | M2 T43 S9 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-95 | M2 T43 S10 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-96 | M2 T43 S11 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-97 | M2 T43 S12 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-98 | M2 T43 S13 | M3 T27 S5 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-99 | M2 T43 S14 | M3 T27 S5 | 7 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-100 | M2 T43 S15 | M3 T27 S5 | 7 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-101 | M2 T44 S1 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-102 | M2 T44 S2 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-103 | M2 T44 S3 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-104 | M2 T44 S4 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-105 | M2 T44 S6 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-106 | M2 T44 S7 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-107 | M2 T44 S8 | M3 T27 S5 | 44 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-108 | M2 T45 S1 | M3 T27 S5 | 13 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-109 | M2 T45 S2 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-110 | M2 T45 S3 | M3 T27 S5 | 7 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-111 | M2 T45 S4 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-112 | M2 T45 S5 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-113 | M2 T46 S1 | M3 T27 S5 | 13 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-114 | M2 T46 S2 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-115 | M2 T46 S3 | M3 T27 S5 | 13 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-116 | M2 T46 S4 | M3 T27 S5 | 12 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-117 | M2 T47 S1 | M3 T27 S5 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-118 | M2 T47 S2 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-119 | M2 T47 S3 | M3 T27 S5 | 1 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-120 | M2 T47 S4 | M3 T27 S5 | 26 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-121 | M2 T47 S5 | M3 T27 S5 | 3 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-122 | M2 T48 S1 | M3 T27 S5 | 13 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-123 | M2 T48 S2 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-124 | M2 T48 S3 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-125 | M2 T48 S4 | M3 T27 S5 | 16 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-126 | M2 T48 S5 | M3 T27 S5 | 18 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-127 | M2 T48 S6 | M3 T27 S5 | 4 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-128 | M2 T49 S1 | M3 T27 S5 | 14 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-129 | M2 T49 S2 | M3 T27 S5 | 12 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-130 | M2 T49 S3 | M3 T27 S5 | 10 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-131 | M2 T49 S4 | M3 T27 S5 | 11 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-132 | M2 T49 S5 | M3 T27 S5 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-133 | M2 T49 S6 | M3 T27 S5 | 6 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-134 | M2 T49 S7 | M3 T27 S5 | 8 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-135 | M2 T49 S8 | M3 T27 S5 | 9 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-136 | M2 T49 S9 | M3 T27 S5 | 23 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-137 | M2 T50 S1 | M3 T27 S5 | 21 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-138 | M2 T50 S2 | M3 T27 S5 | 5 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| m3-t27-s5-core-cohorts-139 | M2 T50 S3 | M3 T27 S5 | 2 | coordinator under owner-approved component split; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |

## Recorded S estimates and actual matches

Only runs with retained exact evidence appear here; older missing estimates
are not reconstructed as historical promises. Exact scope arrays are in JSON.

| S | Scope count | Incoming complete | Expected new names / count | Actual new names / count | State / evidence |
| --- | ---: | ---: | --- | --- | --- |
| M2 T24 S1 | 1992 | 0 | `RelativePlayerPosition`, `RenderPlayerSub`, `DrawPlayerLoop`, `PlayerOffscreenChk`, `PROfsLoop`, `NPROffscr`, `DrawPlayer_Intermediate`, `PIntLoop` / 8 | `PlayerOffscreenChk`, `PROfsLoop`, `NPROffscr` / 3 | closed-evidence-audit-with-transferred-responsibility; [record](../../docs/etc/architecture/m2-t24-s1-node-verification.md) |
| M2 T24 S2 | 1992 | 3 | none / 0 | none / 0 | metadata-verified-custody-open; [record](../../docs/proposals/m2/node-task-ledger.md) |
| M2 T20 S4 | 24 | 3 | none / 0 | none / 0 | closed-transferred-to-M2-T21; [record](../../docs/proposals/m2/fireballs-bubbles.md) |
| M2 T21 S1 | 7 | 3 | none / 0 | none / 0 | closed-contract-complete; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S2 | 7 | 3 | none / 0 | none / 0 | closed-migration-transferred-to-s3; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S3 | 7 | 3 | none / 0 | none / 0 | closed-transferred-to-s4; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S4 | 7 | 3 | `Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, `InitializeMemory` / 7 | none / 0 | closed-transferred-to-s5; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 T21 S5 | 7 | 3 | none / 0 | none / 0 | closed-transferred-to-t22-deferred; [record](../../docs/proposals/m2/t21-boot-cold-init.md) |
| M2 Td S6 | 12 | 3 | none / 0 | none / 0 | closed-transferred-to-t22-s6; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S6 | 12 | 3 | none / 0 | none / 0 | closed-transferred-to-t22-s7; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S7 | 12 | 3 | none / 0 | none / 0 | closed-transferred-to-t22-s8; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S8 | 12 | 3 | none / 0 | none / 0 | closed-transferred-to-t22-s9-and-s10; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S9 | 1 | 3 | `ScreenOff` / 1 | `ScreenOff` / 1 | closed-complete-screenoff; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S10 | 11 | 4 | none / 0 | none / 0 | closed-classified-transferred; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S11 | 7 | 4 | none / 0 | none / 0 | closed-implemented-transferred-to-s14; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S14 | 7 | 4 | `Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, `InitializeMemory` / 7 | `Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, `InitializeMemory` / 7 | closed-complete-boot-root; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S12 | 3 | 11 | none / 0 | none / 0 | closed-migrated-transferred-to-s15; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S15 | 3 | 11 | `VRAM_AddrTable_Low`, `VRAM_AddrTable_High`, `VRAM_Buffer_Offset` / 3 | `VRAM_AddrTable_Low`, `VRAM_AddrTable_High`, `VRAM_Buffer_Offset` / 3 | closed-complete-vram-address-tables; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S13 | 1 | 14 | none / 0 | none / 0 | closed-parent-audit-transferred-to-s22; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S16 | 1 | 14 | none / 0 | none / 0 | closed-contract-transferred-to-s23; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S23 | 1 | 14 | `InitBuffer` / 1 | `InitBuffer` / 1 | closed-complete-initbuffer; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S17 | 6 | 15 | none / 0 | none / 0 | closed-source-contract-transfer-to-s24; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S24 | 6 | 15 | `PauseRoutine`, `ChkPauseTimer`, `ChkStart`, `ClrPauseTimer`, `SetPause`, `ExitPause` / 6 | `PauseRoutine`, `ChkPauseTimer`, `ChkStart`, `ClrPauseTimer`, `SetPause`, `ExitPause` / 6 | closed-complete-pause-equivalence; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S18 | 6 | 21 | none / 0 | none / 0 | closed-timer-lfsr-contract-transfer-to-s25; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S25 | 6 | 21 | `DecTimers`, `DecTimersLoop`, `SkipExpTimer`, `NoDecTimers`, `PauseSkip`, `RotPRandomBit` / 6 | `DecTimers`, `DecTimersLoop`, `SkipExpTimer`, `NoDecTimers`, `PauseSkip`, `RotPRandomBit` / 6 | closed-complete-timer-lfsr-equivalence; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S19 | 8 | 27 | none / 0 | none / 0 | closed-sprite-oam-contract-transfer-to-s26; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S26 | 8 | 27 | `Sprite0Clr`, `Sprite0Hit`, `HBlankDelay`, `SkipSprite0`, `SkipMainOper`, `MoveAllSpritesOffscreen`, `MoveSpritesOffscreen`, `SprInitLoop` / 8 | `Sprite0Clr`, `Sprite0Hit`, `HBlankDelay`, `SkipSprite0`, `SkipMainOper`, `MoveAllSpritesOffscreen`, `MoveSpritesOffscreen`, `SprInitLoop` / 8 | closed-complete-sprite-oam-equivalence; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S20 | 6 | 35 | none / 0 | none / 0 | closed-sprite-shuffle-contract-transfer-to-s27; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S27 | 6 | 35 | `SpriteShuffler`, `ShuffleLoop`, `StrSprOffset`, `NextSprOffset`, `SetAmtOffset`, `SetMiscOffset` / 6 | `SpriteShuffler`, `ShuffleLoop`, `StrSprOffset`, `NextSprOffset`, `SetAmtOffset`, `SetMiscOffset` / 6 | closed-complete-sprite-shuffle-equivalence; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S21 | 1 | 41 | none / 0 | none / 0 | closed-operation-mode-dispatch-contract-transferred; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S28 | 1 | 41 | `OperModeExecutionTree` / 1 | `OperModeExecutionTree` / 1 | closed-complete-operation-mode-dispatch-equivalence; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T22 S22 | 1 | 42 | none / 0 | none / 0 | closed-dependency-audit-transferred-to-t24-s2; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 Td S7 | 0 | 42 | none / 0 | none / 0 | closed-source-order-identifier-reconciliation; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T25 S1 | 26 | 42 | none / 0 | none / 0 | closed-title-source-contract-transferred-to-s2; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S2 | 26 | 42 | none / 0 | none / 0 | closed-shared-migration-transferred-to-s3; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S3 | 26 | 42 | none / 0 | none / 0 | closed-rom-audit-transferred-to-s4; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S4 | 26 | 42 | none / 0 | none / 0 | closed-repair-and-controlled-route-disposition-transferred-to-s5; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S5 | 26 | 42 | none / 0 | none / 0 | closed-zero-credit-route-evidence-transferred-to-s6; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T18 S4 | 1 | 42 | none / 0 | none / 0 | closed-initializegame-prerequisite-repaired-no-node-credit; [record](../../docs/proposals/m2/area-parser.md) |
| M2 T26 S1 | 32 | 42 | none / 0 | none / 0 | closed-zero-credit-source-contract-transferred-to-s2; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S2 | 32 | 42 | none / 0 | none / 0 | closed-zero-credit-terminal-repairs-transferred; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S3 | 10 | 42 | none / 0 | none / 0 | closed-zero-credit-source-order-audited-transferred-to-s4; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S4 | 32 | 42 | none / 0 | none / 0 | closed-zero-credit-route-evidence-transferred-to-s5; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S5 | 32 | 42 | `VictoryModeSubroutines`, `SetupVictoryMode`, `PlayerVictoryWalk`, `PerformWalk`, `DontWalk`, `ExitVWalk`, `PrintVictoryMessages`, `MRetainerMsg`, `ThankPlayer`, `SecondPartMsg`, `EvalForMusic`, `PrintMsg`, `IncMsgCounter`, `SetEndTimer`, `IncModeTask_A`, `ExitMsgs`, `PlayerEndWorld`, `EndExitOne`, `EndChkBButton`, `EndExitTwo`, `FloateyNumTileData`, `ScoreUpdateData`, `FloateyNumbersRoutine`, `ChkNumTimer`, `DecNumTimer`, `LoadNumTiles`, `ChkTallEnemy`, `GetAltOffset`, `FloateyPart`, `SetupNumSpr` / 30 | `VictoryModeSubroutines`, `SetupVictoryMode`, `PlayerVictoryWalk`, `PerformWalk`, `DontWalk`, `ExitVWalk`, `PrintVictoryMessages`, `MRetainerMsg`, `ThankPlayer`, `SecondPartMsg`, `EvalForMusic`, `PrintMsg`, `IncMsgCounter`, `SetEndTimer`, `IncModeTask_A`, `ExitMsgs`, `PlayerEndWorld`, `EndExitOne`, `EndChkBButton`, `EndExitTwo`, `FloateyNumTileData`, `ScoreUpdateData`, `FloateyNumbersRoutine`, `ChkNumTimer`, `DecNumTimer`, `LoadNumTiles`, `ChkTallEnemy`, `GetAltOffset`, `FloateyPart`, `SetupNumSpr` / 30 | closed-30-direct-labels-complete-transferred-outer-residuals-to-s6; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S6 | 2 | 72 | none / 0 | none / 0 | closed-zero-credit-outer-call-order-restored-transferred-to-s7; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S7 | 2 | 72 | `VictoryMode`, `AutoPlayer` / 2 | `VictoryMode`, `AutoPlayer` / 2 | closed-complete-repeatable-outer-victory-route-equivalence; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T25 S6 | 26 | 74 | none / 0 | none / 0 | closed-zero-credit-source-order-title-integration-repaired; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S7 | 4 | 74 | `TitleScreenMode`, `GameMenuRoutine`, `NullJoypad`, `RunDemo` / 4 | `TitleScreenMode`, `GameMenuRoutine`, `NullJoypad`, `RunDemo` / 4 | closed-complete-first-title-idle-prefix-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S8 | 1 | 78 | `ResetTitle` / 1 | `ResetTitle` / 1 | closed-complete-reset-title-branch-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S9 | 1 | 79 | `StartGame` / 1 | `StartGame` / 1 | closed-complete-start-game-direct-jump-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S10 | 1 | 80 | `ChkSelect` / 1 | `ChkSelect` / 1 | closed-complete-chk-select-branch-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S11 | 1 | 81 | `ChkWorldSel` / 1 | `ChkWorldSel` / 1 | closed-complete-chk-world-select-zero-flag-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S12 | 1 | 82 | `SelectBLogic` / 1 | `SelectBLogic` / 1 | closed-complete-select-b-logic-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S13 | 1 | 83 | `IncWorldSel` / 1 | `IncWorldSel` / 1 | closed-complete-inc-world-select-controlled-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S14 | 1 | 84 | `UpdateShroom` / 1 | `UpdateShroom` / 1 | closed-complete-update-shroom-loop-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S15 | 1 | 85 | `ChkContinue` / 1 | `ChkContinue` / 1 | closed-complete-chk-continue-dual-branch-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S16 | 1 | 86 | `StartWorld1` / 1 | `StartWorld1` / 1 | closed-complete-start-world-one-common-continuation-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S17 | 1 | 87 | `InitScores` / 1 | `InitScores` / 1 | closed-complete-start-world-one-common-continuation-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S18 | 1 | 88 | `ExitMenu` / 1 | `ExitMenu` / 1 | closed-complete-start-world-one-common-continuation-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S19 | 1 | 89 | `GoContinue` / 1 | `GoContinue` / 1 | closed-complete-start-world-one-common-continuation-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S20 | 1 | 90 | `WSelectBufferTemplate` / 1 | `WSelectBufferTemplate` / 1 | closed-complete-world-select-buffer-template-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S21 | 1 | 91 | `MushroomIconData` / 1 | `MushroomIconData` / 1 | closed-complete-mushroom-icon-data-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S22 | 1 | 92 | `DrawMushroomIcon` / 1 | `DrawMushroomIcon` / 1 | closed-complete-draw-mushroom-icon-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S23 | 1 | 93 | `IconDataRead` / 1 | `IconDataRead` / 1 | closed-complete-icon-data-read-equivalence; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S24 | 1 | 94 | `ExitIcon` / 1 | `ExitIcon` / 1 | closed-complete-exit-icon-return-chain; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T25 S25 | 5 | 95 | `DemoActionData`, `DemoTimingData`, `DemoEngine`, `DoAction`, `DemoOver` / 5 | `DemoActionData`, `DemoTimingData`, `DemoEngine`, `DoAction`, `DemoOver` / 5 | closed-complete-title-idle-demo-chain; [record](../../docs/proposals/m2/t25-title-menu-demo.md) |
| M2 T27 S1 | 21 | 100 | `InitScreen`, `SetupIntermediate`, `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal` / 20 | `InitScreen`, `SetupIntermediate`, `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal` / 20 | closed-complete-screen-init-palette-leaves; [record](../../docs/proposals/m2/screen-status.md) |
| M2 T27 S2 | 43 | 120 | `WriteTopStatusLine`, `WriteBottomStatusLine`, `DisplayTimeUp`, `NoTimeUp`, `DisplayIntermediate`, `PlayerInter`, `OutputInter`, `GameOverInter`, `NoInter`, `DrawTitleScreen`, `OutputTScr`, `ChkHiByte`, `ClearBuffersDrawIcon`, `TScrClear`, `IncSubtask`, `WriteTopScore`, `IncModeTask_B`, `GameText`, `TopStatusBarLine`, `WorldLivesDisplay`, `TwoPlayerTimeUp`, `OnePlayerTimeUp`, `TwoPlayerGameOver`, `OnePlayerGameOver`, `WarpZoneWelcome`, `LuigiName`, `WarpZoneNumbers`, `GameTextOffsets`, `WriteGameText`, `Chk2Players`, `LdGameText`, `GameTextLoop`, `EndGameText`, `PutLives`, `CheckPlayerName`, `ChkLuigi`, `NameLoop`, `ExitChkName`, `PrintWarpZoneNumbers`, `WarpNumLoop`, `ResetSpritesAndScreenTimer`, `ResetScreenTimer`, `NoReset` / 43 | `WriteTopStatusLine`, `WriteBottomStatusLine`, `DisplayTimeUp`, `NoTimeUp`, `DisplayIntermediate`, `PlayerInter`, `OutputInter`, `GameOverInter`, `NoInter`, `DrawTitleScreen`, `OutputTScr`, `ChkHiByte`, `ClearBuffersDrawIcon`, `TScrClear`, `IncSubtask`, `WriteTopScore`, `IncModeTask_B`, `GameText`, `TopStatusBarLine`, `WorldLivesDisplay`, `TwoPlayerTimeUp`, `OnePlayerTimeUp`, `TwoPlayerGameOver`, `OnePlayerGameOver`, `WarpZoneWelcome`, `LuigiName`, `WarpZoneNumbers`, `GameTextOffsets`, `WriteGameText`, `Chk2Players`, `LdGameText`, `GameTextLoop`, `EndGameText`, `PutLives`, `CheckPlayerName`, `ChkLuigi`, `NameLoop`, `ExitChkName`, `PrintWarpZoneNumbers`, `WarpNumLoop`, `ResetSpritesAndScreenTimer`, `ResetScreenTimer`, `NoReset` / 43 | closed-complete-screen-status-text-chain; [record](../../docs/proposals/m2/screen-status.md) |
| M2 T27 S3 | 4 | 163 | none / 0 | none / 0 | closed-deferred-parser-integration-audit; [record](../../docs/proposals/m2/screen-status.md) |
| M2 Td S8 | 0 | 163 | none / 0 | none / 0 | closed-source-order-receiver-reconciliation; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T28 S1 | 13 | 163 | `RenderAreaGraphics`, `DrawMTLoop`, `RightCheck`, `LLeft`, `NextMTRow`, `SetAttrib`, `ExitDrawM`, `RenderAttributeTables`, `SetATHigh`, `AttribLoop`, `SetVRAMCtrl`, `MetatileGraphics_Low`, `MetatileGraphics_High` / 13 | `RenderAreaGraphics`, `DrawMTLoop`, `RightCheck`, `LLeft`, `NextMTRow`, `SetAttrib`, `ExitDrawM`, `RenderAttributeTables`, `SetATHigh`, `AttribLoop`, `SetVRAMCtrl`, `MetatileGraphics_Low`, `MetatileGraphics_High` / 13 | closed-renderer-attribute-chain; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S2 | 7 | 176 | `ColorRotatePalette`, `BlankPalette`, `Palette3Data`, `ColorRotation`, `GetBlankPal`, `GetAreaPal`, `ExitColorRot` / 7 | `ColorRotatePalette`, `BlankPalette`, `Palette3Data`, `ColorRotation`, `GetBlankPal`, `GetAreaPal`, `ExitColorRot` / 7 | closed-palette-rotation-chain; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S3 | 11 | 183 | `BlockGfxData`, `RemoveCoin_Axe`, `WriteBlankMT`, `ReplaceBlockMetatile`, `DestroyBlockMetatile`, `WriteBlockMetatile`, `UseBOffset`, `MoveVOffset`, `PutBlockMetatile`, `SaveHAdder`, `RemBridge` / 11 | `BlockGfxData`, `RemoveCoin_Axe`, `WriteBlankMT`, `ReplaceBlockMetatile`, `DestroyBlockMetatile`, `WriteBlockMetatile`, `UseBOffset`, `MoveVOffset`, `PutBlockMetatile`, `SaveHAdder`, `RemBridge` / 11 | closed-block-graphics-chain; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S4 | 19 | 194 | `Palette0_MTiles`, `Palette1_MTiles`, `Palette2_MTiles`, `Palette3_MTiles`, `WaterPaletteData`, `GroundPaletteData`, `UndergroundPaletteData`, `CastlePaletteData`, `DaySnowPaletteData`, `NightSnowPaletteData`, `MushroomPaletteData`, `BowserPaletteData`, `MarioThanksMessage`, `LuigiThanksMessage`, `MushroomRetainerSaved`, `PrincessSaved1`, `PrincessSaved2`, `WorldSelectMessage1`, `WorldSelectMessage2` / 19 | `Palette0_MTiles`, `Palette1_MTiles`, `Palette2_MTiles`, `Palette3_MTiles`, `WaterPaletteData`, `GroundPaletteData`, `UndergroundPaletteData`, `CastlePaletteData`, `DaySnowPaletteData`, `NightSnowPaletteData`, `MushroomPaletteData`, `BowserPaletteData`, `MarioThanksMessage`, `LuigiThanksMessage`, `MushroomRetainerSaved`, `PrincessSaved1`, `PrincessSaved2`, `WorldSelectMessage1`, `WorldSelectMessage2` / 19 | closed-area-data-chain; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S5 | 5 | 213 | `JumpEngine`, `InitializeNameTables`, `WriteNTAddr`, `InitNTLoop`, `InitATLoop` / 5 | none / 0 | active-name-table-chain; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S6 | 12 | 218 | `ReadJoypads`, `ReadPortBits`, `PortLoop`, `Save8Bits`, `WriteBufferToScreen`, `SetupWrites`, `GetLength`, `OutputToVRAM`, `RepeatByte`, `UpdateScreen`, `InitScroll`, `WritePPUReg1` / 12 | `ReadJoypads`, `ReadPortBits`, `PortLoop`, `Save8Bits`, `WriteBufferToScreen`, `SetupWrites`, `GetLength`, `OutputToVRAM`, `RepeatByte`, `UpdateScreen`, `InitScroll`, `WritePPUReg1` / 12 | closed-joypad-vram-nmi-chain; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S7 | 19 | 230 | `StatusBarData`, `StatusBarOffset`, `PrintStatusBarNumbers`, `OutputNumbers`, `SetupNums`, `DigitPLoop`, `ExitOutputN`, `DigitsMathRoutine`, `AddModLoop`, `StoreNewD`, `EraseDMods`, `EraseMLoop`, `BorrowOne`, `CarryOne`, `UpdateTopScore`, `TopScoreCheck`, `GetScoreDiff`, `CopyScore`, `NoTopSc` / 19 | `StatusBarData`, `StatusBarOffset`, `PrintStatusBarNumbers`, `OutputNumbers`, `SetupNums`, `DigitPLoop`, `ExitOutputN`, `DigitsMathRoutine`, `AddModLoop`, `StoreNewD`, `EraseDMods`, `EraseMLoop`, `BorrowOne`, `CarryOne`, `UpdateTopScore`, `TopScoreCheck`, `GetScoreDiff`, `CopyScore`, `NoTopSc` / 19 | closed-status-arithmetic-chain; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S8 | 16 | 249 | `DefaultSprOffsets`, `Sprite0Data`, `InitializeGame`, `ClrSndLoop`, `InitializeArea`, `ClrTimersLoop`, `StartPage`, `SetInitNTHigh`, `SetSecHard`, `CheckHalfway`, `DoneInitArea`, `PrimaryGameSetup`, `SecondaryGameSetup`, `ClearVRLoop`, `ShufAmtLoop`, `ISpr0Loop` / 16 | `DefaultSprOffsets`, `Sprite0Data`, `InitializeGame`, `ClrSndLoop`, `InitializeArea`, `ClrTimersLoop`, `StartPage`, `SetInitNTHigh`, `SetSecHard`, `CheckHalfway`, `DoneInitArea`, `PrimaryGameSetup`, `SecondaryGameSetup`, `ClearVRLoop`, `ShufAmtLoop`, `ISpr0Loop` / 16 | closed-initialization-bootstrap-chain; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T29 S1 | 4 | 265 | `InitPageLoop`, `InitByteLoop`, `InitByte`, `SkipByte` / 4 | `InitPageLoop`, `InitByteLoop`, `InitByte`, `SkipByte` / 4 | closed-initialize-memory-loop-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S2 | 5 | 269 | `MusicSelectData`, `GetAreaMusic`, `ChkAreaType`, `StoreMusic`, `ExitGetM` / 5 | `MusicSelectData`, `GetAreaMusic`, `ChkAreaType`, `StoreMusic`, `ExitGetM` / 5 | closed-area-music-selection-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S3 | 11 | 274 | `PlayerStarting_X_Pos`, `AltYPosOffset`, `PlayerStarting_Y_Pos`, `PlayerBGPriorityData`, `GameTimerData`, `Entrance_GameTimerSetup`, `ChkStPos`, `SetStPos`, `ChkOverR`, `ChkSwimE`, `SetPESub` / 11 | `PlayerStarting_X_Pos`, `AltYPosOffset`, `PlayerStarting_Y_Pos`, `PlayerBGPriorityData`, `GameTimerData`, `Entrance_GameTimerSetup`, `ChkStPos`, `SetStPos`, `ChkOverR`, `ChkSwimE`, `SetPESub` / 11 | closed-complete-area-entry-initialization-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S4 | 17 | 285 | `HalfwayPageNybbles`, `PlayerLoseLife`, `StillInGame`, `GetHalfway`, `MaskHPNyb`, `SetHalfway`, `GameOverMode`, `SetupGameOver`, `RunGameOver`, `TerminateGame`, `ContinueGame`, `GameIsOn`, `TransposePlayers`, `TransLoop`, `ExTrans`, `DoNothing1`, `DoNothing2` / 17 | `HalfwayPageNybbles`, `PlayerLoseLife`, `StillInGame`, `GetHalfway`, `MaskHPNyb`, `SetHalfway`, `GameOverMode`, `SetupGameOver`, `RunGameOver`, `TerminateGame`, `ContinueGame`, `GameIsOn`, `TransposePlayers`, `TransLoop`, `ExTrans`, `DoNothing1`, `DoNothing2` / 17 | closed-life-mode-state-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S5 | 14 | 302 | `AreaParserTaskHandler`, `DoAPTasks`, `SkipATRender`, `AreaParserTasks`, `IncrementColumnPos`, `NoColWrap`, `BSceneDataOffsets`, `BackSceneryData`, `BackSceneryMetatiles`, `FSceneDataOffsets`, `ForeSceneryData`, `TerrainMetatiles`, `TerrainRenderBits`, `AreaParserCore` / 14 | `AreaParserTaskHandler`, `DoAPTasks`, `SkipATRender`, `AreaParserTasks`, `IncrementColumnPos`, `NoColWrap`, `BSceneDataOffsets`, `BackSceneryData`, `BackSceneryMetatiles`, `FSceneDataOffsets`, `ForeSceneryData`, `TerrainMetatiles`, `TerrainRenderBits`, `AreaParserCore` / 14 | closed-parser-dispatch-data-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S6 | 20 | 316 | `RenderSceneryTerrain`, `ClrMTBuf`, `ThirdP`, `RendBack`, `SceLoop1`, `RendFore`, `SceLoop2`, `NoFore`, `RendTerr`, `TerMTile`, `StoreMT`, `TerrLoop`, `NoCloud2`, `TerrBChk`, `NextTBit`, `EndUChk`, `RendBBuf`, `ChkMTLow`, `StrBlock`, `BlockBuffLowBounds` / 20 | `RenderSceneryTerrain`, `ClrMTBuf`, `ThirdP`, `RendBack`, `SceLoop1`, `RendFore`, `SceLoop2`, `NoFore`, `RendTerr`, `TerMTile`, `StoreMT`, `TerrLoop`, `NoCloud2`, `TerrBChk`, `NextTBit`, `EndUChk`, `RendBBuf`, `ChkMTLow`, `StrBlock`, `BlockBuffLowBounds` / 20 | closed-scenery-column-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S7 | 32 | 336 | `ProcessAreaData`, `ProcADLoop`, `Chk1Row13`, `Chk1Row14`, `CheckRear`, `RdyDecode`, `SetBehind`, `NextAObj`, `ChkLength`, `ProcLoopb`, `EndAParse`, `IncAreaObjOffset`, `DecodeAreaData`, `Chk1stB`, `ChkRow14`, `ChkRow13`, `Mask2MSB`, `ChkSRows`, `LrgObj`, `NotWPipe`, `SpecObj`, `MoveAOId`, `NormObj`, `LeavePar`, `InitRear`, `LoopCmdE`, `BackColC`, `StrAObj`, `RunAObj`, `AlterAreaAttributes`, `Alter2`, `SetFore` / 32 | `ProcessAreaData`, `ProcADLoop`, `Chk1Row13`, `Chk1Row14`, `CheckRear`, `RdyDecode`, `SetBehind`, `NextAObj`, `ChkLength`, `ProcLoopb`, `EndAParse`, `IncAreaObjOffset`, `DecodeAreaData`, `Chk1stB`, `ChkRow14`, `ChkRow13`, `Mask2MSB`, `ChkSRows`, `LrgObj`, `NotWPipe`, `SpecObj`, `MoveAOId`, `NormObj`, `LeavePar`, `InitRear`, `LoopCmdE`, `BackColC`, `StrAObj`, `RunAObj`, `AlterAreaAttributes`, `Alter2`, `SetFore` / 32 | closed-area-stream-decoder-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S8 | 22 | 368 | `ScrollLockObject_Warp`, `WarpNum`, `ScrollLockObject`, `KillEnemies`, `KillELoop`, `NoKillE`, `FrenzyIDData`, `AreaFrenzy`, `FreCompLoop`, `ExitAFrenzy`, `AreaStyleObject`, `TreeLedge`, `MidTreeL`, `EndTreeL`, `MushroomLedge`, `EndMushL`, `AllUnder`, `NoUnder`, `PulleyRopeMetatiles`, `PulleyRopeObject`, `RenderPul`, `MushLExit` / 22 | `ScrollLockObject_Warp`, `WarpNum`, `ScrollLockObject`, `KillEnemies`, `KillELoop`, `NoKillE`, `FrenzyIDData`, `AreaFrenzy`, `FreCompLoop`, `ExitAFrenzy`, `AreaStyleObject`, `TreeLedge`, `MidTreeL`, `EndTreeL`, `MushroomLedge`, `EndMushL`, `AllUnder`, `NoUnder`, `PulleyRopeMetatiles`, `PulleyRopeObject`, `RenderPul`, `MushLExit` / 22 | closed-special-object-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S9 | 22 | 390 | `CastleMetatiles`, `CastleObject`, `CRendLoop`, `ChkCFloor`, `NotTall`, `PlayerStop`, `ExitCastle`, `WaterPipe`, `IntroPipe`, `VPipeSectLoop`, `NoBlankP`, `SidePipeShaftData`, `SidePipeTopPart`, `SidePipeBottomPart`, `ExitPipe`, `RenderSidewaysPipe`, `DrawSidePart`, `VerticalPipeData`, `VerticalPipe`, `WarpPipe`, `DrawPipe`, `GetPipeHeight` / 22 | `CastleMetatiles`, `CastleObject`, `CRendLoop`, `ChkCFloor`, `NotTall`, `PlayerStop`, `ExitCastle`, `WaterPipe`, `IntroPipe`, `VPipeSectLoop`, `NoBlankP`, `SidePipeShaftData`, `SidePipeTopPart`, `SidePipeBottomPart`, `ExitPipe`, `RenderSidewaysPipe`, `DrawSidePart`, `VerticalPipeData`, `VerticalPipe`, `WarpPipe`, `DrawPipe`, `GetPipeHeight` / 22 | closed-large-object-geometry-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S10 | 10 | 412 | `FindEmptyEnemySlot`, `EmptyChkLoop`, `ExitEmptyChk`, `Hole_Water`, `QuestionBlockRow_High`, `QuestionBlockRow_Low`, `Bridge_High`, `Bridge_Middle`, `Bridge_Low`, `FlagBalls_Residual` / 10 | `FindEmptyEnemySlot`, `EmptyChkLoop`, `ExitEmptyChk`, `Hole_Water`, `QuestionBlockRow_High`, `QuestionBlockRow_Low`, `Bridge_High`, `Bridge_Middle`, `Bridge_Low`, `FlagBalls_Residual` / 10 | admitted-allocation-final-geometry-chain; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T22 S5 | 8 | 422 | `FlagpoleObject`, `FlagpoleScoreMods`, `FlagpoleScoreDigits`, `FlagpoleRoutine`, `SkipScore`, `GiveFPScr`, `FPGfx`, `ExitFlagP` / 8 | `FlagpoleObject`, `FlagpoleScoreMods`, `FlagpoleScoreDigits`, `FlagpoleRoutine`, `SkipScore`, `GiveFPScr`, `FPGfx`, `ExitFlagP` / 8 | p1-flagpole-chain-complete-awaiting-custody-transfer; [record](../../docs/proposals/m2/blocks-items-misc.md) |
| M2 T30 S1 | 3 | 430 | `EndlessRope`, `BalancePlatRope`, `DrawRope` / 3 | `EndlessRope`, `BalancePlatRope`, `DrawRope` / 3 | p1-rope-chain-complete; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S2 | 2 | 433 | `CoinMetatileData`, `RowOfCoins` / 2 | `CoinMetatileData`, `RowOfCoins` / 2 | p1-coin-selector-chain-complete; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S3 | 7 | 435 | `C_ObjectRow`, `C_ObjectMetatile`, `CastleBridgeObj`, `AxeObj`, `ChainObj`, `EmptyBlock`, `ColObj` / 7 | `C_ObjectRow`, `C_ObjectMetatile`, `CastleBridgeObj`, `AxeObj`, `ChainObj`, `EmptyBlock`, `ColObj` / 7 | closed-castle-column-chain-442; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S4 | 10 | 442 | `SolidBlockMetatiles`, `BrickMetatiles`, `RowOfBricks`, `DrawBricks`, `RowOfSolidBlocks`, `GetRow`, `DrawRow`, `ColumnOfBricks`, `ColumnOfSolidBlocks`, `GetRow2` / 10 | `SolidBlockMetatiles`, `BrickMetatiles`, `RowOfBricks`, `DrawBricks`, `RowOfSolidBlocks`, `GetRow`, `DrawRow`, `ColumnOfBricks`, `ColumnOfSolidBlocks`, `GetRow2` / 10 | closed-row-column-chain-452; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S5 | 3 | 452 | `BulletBillCannon`, `SetupCannon`, `StrCOffset` / 3 | `BulletBillCannon`, `SetupCannon`, `StrCOffset` / 3 | closed-cannon-chain-455; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S6 | 4 | 455 | `StaircaseHeightData`, `StaircaseRowData`, `StaircaseObject`, `NextStair` / 4 | `StaircaseHeightData`, `StaircaseRowData`, `StaircaseObject`, `NextStair` / 4 | closed-staircase-chain-459; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S7 | 1 | 459 | `Jumpspring` / 1 | `Jumpspring` / 1 | closed-jumpspring-chain-460; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S8 | 8 | 460 | `Hidden1UpBlock`, `QuestionBlock`, `BrickWithCoins`, `BrickWithItem`, `BWithL`, `DrawQBlk`, `GetAreaObjectID`, `ExitDecBlock` / 8 | `Hidden1UpBlock`, `QuestionBlock`, `BrickWithCoins`, `BrickWithItem`, `BWithL`, `DrawQBlk`, `GetAreaObjectID`, `ExitDecBlock` / 8 | closed-item-block-chain-468; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S9 | 8 | 468 | `HoleMetatiles`, `Hole_Empty`, `StrWOffset`, `NoWhirlP`, `RenderUnderPart`, `DrawThisRow`, `WaitOneRow`, `ExitUPartR` / 8 | `HoleMetatiles`, `Hole_Empty`, `StrWOffset`, `NoWhirlP`, `RenderUnderPart`, `DrawThisRow`, `WaitOneRow`, `ExitUPartR` / 8 | closed-hole-underpart-chain-476; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S10 | 6 | 476 | `ChkLrgObjLength`, `ChkLrgObjFixedLength`, `LenSet`, `GetLrgObjAttrib`, `GetAreaObjXPosition`, `GetAreaObjYPosition` / 6 | `ChkLrgObjLength`, `ChkLrgObjFixedLength`, `LenSet`, `GetLrgObjAttrib`, `GetAreaObjXPosition`, `GetAreaObjYPosition` / 6 | closed-common-helper-chain-480; six new matches, two prior matches revoked; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S11 | 1 | 480 | `DecodeAreaData` / 1 | `DecodeAreaData` / 1 | closed-parser-index-correction-481; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S12 | 1 | 481 | `DrawPipe` / 1 | `DrawPipe` / 1 | closed-draw-pipe-correction-482; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S13 | 3 | 481 | `SetInitNTHigh`, `BlockBufferAddr`, `GetBlockBufferAddr` / 3 | `SetInitNTHigh`, `BlockBufferAddr`, `GetBlockBufferAddr` / 3 | closed-block-address-and-initial-page-484; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S14 | 23 | 483 | `TerminateGame`, `LoadAreaPointer`, `GetAreaType`, `FindAreaPointer`, `GetAreaDataAddrs`, `StoreFore`, `StoreStyle`, `WorldAddrOffsets`, `AreaAddrOffsets`, `World1Areas`, `World2Areas`, `World3Areas`, `World4Areas`, `World5Areas`, `World6Areas`, `World7Areas`, `World8Areas`, `EnemyAddrHOffsets`, `EnemyDataAddrLow`, `EnemyDataAddrHigh`, `AreaDataHOffsets`, `AreaDataAddrLow`, `AreaDataAddrHigh` / 23 | `TerminateGame`, `LoadAreaPointer`, `GetAreaType`, `FindAreaPointer`, `GetAreaDataAddrs`, `StoreFore`, `StoreStyle`, `WorldAddrOffsets`, `AreaAddrOffsets`, `World1Areas`, `World2Areas`, `World3Areas`, `World4Areas`, `World5Areas`, `World6Areas`, `World7Areas`, `World8Areas`, `EnemyAddrHOffsets`, `EnemyDataAddrLow`, `EnemyDataAddrHigh`, `AreaDataHOffsets`, `AreaDataAddrLow`, `AreaDataAddrHigh` / 23 | closed-pointer-header-and-terminal-caller-506; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S15 | 34 | 506 | none / 0 | none / 0 | closed-audit-34-consumer-transfers-zero-matches; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S16 | 7 | 505 | `ChkRow13`, `L_CastleArea1`, `L_CastleArea2`, `L_CastleArea3`, `L_CastleArea4`, `L_CastleArea5`, `L_CastleArea6` / 7 | `ChkRow13`, `L_CastleArea1`, `L_CastleArea2`, `L_CastleArea3`, `L_CastleArea4`, `L_CastleArea5`, `L_CastleArea6` / 7 | closed-seven-matches-castle-streams-and-chkrow13; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S17 | 22 | 512 | `L_GroundArea1`, `L_GroundArea2`, `L_GroundArea3`, `L_GroundArea4`, `L_GroundArea5`, `L_GroundArea6`, `L_GroundArea7`, `L_GroundArea8`, `L_GroundArea9`, `L_GroundArea10`, `L_GroundArea11`, `L_GroundArea12`, `L_GroundArea13`, `L_GroundArea14`, `L_GroundArea15`, `L_GroundArea16`, `L_GroundArea17`, `L_GroundArea18`, `L_GroundArea19`, `L_GroundArea20`, `L_GroundArea21`, `L_GroundArea22` / 22 | `L_GroundArea1`, `L_GroundArea2`, `L_GroundArea3`, `L_GroundArea4`, `L_GroundArea5`, `L_GroundArea6`, `L_GroundArea7`, `L_GroundArea8`, `L_GroundArea9`, `L_GroundArea10`, `L_GroundArea11`, `L_GroundArea12`, `L_GroundArea13`, `L_GroundArea14`, `L_GroundArea15`, `L_GroundArea16`, `L_GroundArea17`, `L_GroundArea18`, `L_GroundArea19`, `L_GroundArea20`, `L_GroundArea21`, `L_GroundArea22` / 22 | closed-22-ground-stream-matches; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S18 | 3 | 534 | `L_UndergroundArea1`, `L_UndergroundArea2`, `L_UndergroundArea3` / 3 | `L_UndergroundArea1`, `L_UndergroundArea2`, `L_UndergroundArea3` / 3 | closed-three-underground-stream-matches; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S19 | 3 | 537 | `L_WaterArea1`, `L_WaterArea2`, `L_WaterArea3` / 3 | `L_WaterArea1`, `L_WaterArea2`, `L_WaterArea3` / 3 | closed-three-water-stream-matches; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S20 | 151 | 540 | none / 0 | none / 0 | closed-cross-chain-audit-zero-new-matches; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T31 S1 | 2 | 540 | `GameMode`, `GameCoreRoutine` / 2 | `GameMode`, `GameCoreRoutine` / 2 | closed-two-entry-node-matches; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 9 | 542 | `GameEngine`, `ProcELoop`, `NoChgMus`, `CycleTwo`, `ClrPlrPal`, `SaveAB`, `UpdScrollVar`, `RunParser`, `ExitEng` / 9 | `GameEngine`, `ProcELoop`, `NoChgMus`, `CycleTwo`, `ClrPlrPal`, `SaveAB`, `UpdScrollVar`, `RunParser`, `ExitEng` / 9 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 22 | 549 | `ProcessWhirlpools`, `WhLoop`, `NextWh`, `ExitWh`, `WhirlpoolActivate`, `LeftWh`, `SetPWh`, `WhPull`, `CannonBitmasks`, `ProcessCannons`, `ThreeSChk`, `FireCannon`, `Chk_BB`, `Next3Slt`, `ExCannon`, `BulletBillXSpdData`, `BulletBillHandler`, `SetupBB`, `ChkDSte`, `BBFly`, `RunBBSubs`, `KillBB` / 22 | `ProcessWhirlpools`, `WhLoop`, `NextWh`, `ExitWh`, `WhirlpoolActivate`, `LeftWh`, `SetPWh`, `WhPull`, `CannonBitmasks`, `ProcessCannons`, `ThreeSChk`, `FireCannon`, `Chk_BB`, `Next3Slt`, `ExCannon`, `BulletBillXSpdData`, `BulletBillHandler`, `SetupBB`, `ChkDSte`, `BBFly`, `RunBBSubs`, `KillBB` / 22 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 6 | 549 | `NoRunCode`, `EraseEnemyObject`, `CheckForBulletBillCV`, `SBBAt` / 4 | `NoRunCode`, `EraseEnemyObject`, `CheckForBulletBillCV`, `SBBAt` / 4 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 3 | 576 | `GameEngine`, `RunEnemyObjectsCore`, `JmpEO` / 3 | `GameEngine` / 1 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 1 | 576 | `WarpZoneObject` / 1 | `WarpZoneObject` / 1 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 17 | 576 | `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode`, `XSpeedAdderData`, `RevivedXSpeed`, `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`, `SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`, `ChkKillGoomba`, `NKGmba` / 17 | `XSpeedAdderData`, `RevivedXSpeed`, `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`, `SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`, `ChkKillGoomba`, `NKGmba` / 13 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 3 | 576 | `MoveD_EnemyVertically`, `MoveFallingPlatform`, `ContVMove` / 3 | `MoveD_EnemyVertically`, `MoveFallingPlatform`, `ContVMove` / 3 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 10 | 576 | `ExEBG`, `EnemyToBGCollisionDet`, `DoIDCheckBGColl`, `HBChk`, `CInvu`, `YesIn`, `ExEBGChk`, `SubtEnemyYPos`, `EnemyJump`, `DoSide` / 10 | `ExEBG`, `EnemyToBGCollisionDet`, `DoIDCheckBGColl`, `HBChk`, `CInvu`, `YesIn`, `ExEBGChk`, `SubtEnemyYPos`, `EnemyJump`, `DoSide` / 10 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 4 | 594 | `DoEnemySideCheck`, `SdeCLoop`, `NextSdeC`, `ExESdeC` / 4 | `DoEnemySideCheck`, `SdeCLoop`, `NextSdeC`, `ExESdeC` / 4 | closed-66-proven-six-transferred-131; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S3 | 10 | 608 | `ScrollHandler`, `ChkNearMid`, `ScrollScreen`, `InitScrlAmt`, `ChkPOffscr`, `KeepOnscr`, `InitPlatScrl`, `X_SubtracterData`, `OffscrJoypadBitsData`, `GetScreenPosition` / 10 | `ScrollHandler`, `ChkNearMid`, `ScrollScreen`, `InitScrlAmt`, `ChkPOffscr`, `KeepOnscr`, `InitPlatScrl`, `X_SubtracterData`, `OffscrJoypadBitsData`, `GetScreenPosition` / 10 | closed-P1-ten-matches; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S4 | 10 | 618 | `GameRoutines`, `PlayerEntrance`, `ChkBehPipe`, `IntroEntr`, `EntrMode2`, `VineEntr`, `OffVine`, `PlayerRdy`, `ExitEntr`, `AutoControlPlayer` / 10 | `GameRoutines`, `PlayerEntrance`, `ChkBehPipe`, `IntroEntr`, `EntrMode2`, `VineEntr`, `OffVine`, `PlayerRdy`, `ExitEntr`, `AutoControlPlayer` / 10 | closed-P2-integrated-review-628; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T32 S1 | 13 | 628 | `PlayerCtrlRoutine`, `DisJoyp`, `SaveJoyp`, `SizeChk`, `ChkMoveDir`, `SetMoveDir`, `PlayerSubs`, `PlayerHole`, `HoleDie`, `HoleBottom`, `ChkHoleX`, `ExitCtrl`, `CloudExit` / 13 | `PlayerCtrlRoutine`, `DisJoyp`, `SaveJoyp`, `SizeChk`, `ChkMoveDir`, `SetMoveDir`, `PlayerSubs`, `PlayerHole`, `HoleDie`, `HoleBottom`, `ChkHoleX`, `ExitCtrl`, `CloudExit` / 13 | closed-P2-thirteen-caller-matches-641; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S2 | 11 | 641 | `Vine_AutoClimb`, `AutoClimb`, `SetEntr`, `VerticalPipeEntry`, `MovePlayerYAxis`, `SideExitPipeEntry`, `ChgAreaPipe`, `ChgAreaMode`, `ExitCAPipe`, `EnterSidePipe`, `RightPipe` / 11 | `Vine_AutoClimb`, `AutoClimb`, `SetEntr`, `VerticalPipeEntry`, `MovePlayerYAxis`, `SideExitPipeEntry`, `ChgAreaPipe`, `ChgAreaMode`, `ExitCAPipe`, `EnterSidePipe`, `RightPipe` / 11 | closed-P1-eleven-caller-matches-652; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S3 | 14 | 652 | `PlayerChangeSize`, `EndChgSize`, `ExitChgSize`, `PlayerInjuryBlink`, `ExitBlink`, `InitChangeSize`, `ExitBoth`, `PlayerDeath`, `DonePlayerTask`, `PlayerFireFlower`, `CyclePlayerPalette`, `ResetPalFireFlower`, `ResetPalStar`, `ExitDeath` / 14 | `PlayerChangeSize`, `EndChgSize`, `ExitChgSize`, `PlayerInjuryBlink`, `ExitBlink`, `InitChangeSize`, `ExitBoth`, `PlayerDeath`, `DonePlayerTask`, `PlayerFireFlower`, `CyclePlayerPalette`, `ResetPalFireFlower`, `ResetPalStar`, `ExitDeath` / 14 | closed-P1-fourteen-caller-matches-666; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S4 | 10 | 666 | `FlagpoleSlide`, `SlidePlayer`, `NoFPObj`, `Hidden1UpCoinAmts`, `PlayerEndLevel`, `ChkStop`, `InCastle`, `RdyNextA`, `NextArea`, `ExitNA` / 10 | `FlagpoleSlide`, `SlidePlayer`, `NoFPObj`, `Hidden1UpCoinAmts`, `PlayerEndLevel`, `ChkStop`, `InCastle`, `RdyNextA`, `NextArea`, `ExitNA` / 10 | closed-P2-integrated-review-676; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T33 S1 | 15 | 676 | `PlayerMovementSubs`, `SetCrouch`, `ProcMove`, `MoveSubs`, `NoMoveSub`, `OnGroundStateSub`, `GndMove`, `FallingSub`, `JumpSwimSub`, `DumpFall`, `ProcSwim`, `LRWater`, `LRAir`, `JSMove`, `ExitMov1` / 15 | `PlayerMovementSubs`, `SetCrouch`, `ProcMove`, `MoveSubs`, `NoMoveSub`, `OnGroundStateSub`, `GndMove`, `FallingSub`, `JumpSwimSub`, `DumpFall`, `ProcSwim`, `LRWater`, `LRAir`, `JSMove`, `ExitMov1` / 15 | closed-P1-movement-state-chain-691; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S2 | 8 | 691 | `ClimbAdderLow`, `ClimbAdderHigh`, `ClimbingSub`, `MoveOnVine`, `ClimbFD`, `CSetFDir`, `ExitCSub`, `InitCSTimer` / 8 | `ClimbAdderLow`, `ClimbAdderHigh`, `ClimbingSub`, `MoveOnVine`, `ClimbFD`, `CSetFDir`, `ExitCSub`, `InitCSTimer` / 8 | closed-P1-climbing-chain-699; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S3 | 28 | 699 | `JumpMForceData`, `FallMForceData`, `PlayerYSpdData`, `InitMForceData`, `MaxLeftXSpdData`, `MaxRightXSpdData`, `FrictionData`, `Climb_Y_SpeedData`, `Climb_Y_MForceData`, `PlayerPhysicsSub`, `ProcClimb`, `SetCAnim`, `CheckForJumping`, `NoJump`, `ProcJumping`, `InitJS`, `ChkWtr`, `GetYPhy`, `PJumpSnd`, `SJumpSnd`, `X_Physics`, `ProcPRun`, `ChkRFast`, `FastXSp`, `SetRTmr`, `GetXPhy`, `GetXPhy2`, `ExitPhy` / 28 | `JumpMForceData`, `FallMForceData`, `PlayerYSpdData`, `InitMForceData`, `MaxLeftXSpdData`, `MaxRightXSpdData`, `FrictionData`, `Climb_Y_SpeedData`, `Climb_Y_MForceData`, `PlayerPhysicsSub`, `ProcClimb`, `SetCAnim`, `CheckForJumping`, `NoJump`, `ProcJumping`, `InitJS`, `ChkWtr`, `GetYPhy`, `PJumpSnd`, `SJumpSnd`, `X_Physics`, `ProcPRun`, `ChkRFast`, `FastXSp`, `SetRTmr`, `GetXPhy`, `GetXPhy2`, `ExitPhy` / 28 | closed-P1-physics-chain-727; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S4 | 12 | 727 | `PlayerAnimTmrData`, `GetPlayerAnimSpeed`, `ChkSkid`, `SetRunSpd`, `ProcSkid`, `SetAnimSpd`, `ImposeFriction`, `JoypFrict`, `LeftFrict`, `RghtFrict`, `XSpdSign`, `SetAbsSpd` / 12 | `PlayerAnimTmrData`, `GetPlayerAnimSpeed`, `ChkSkid`, `SetRunSpd`, `ProcSkid`, `SetAnimSpd`, `ImposeFriction`, `JoypFrict`, `LeftFrict`, `RghtFrict`, `XSpdSign`, `SetAbsSpd` / 12 | closed-P2-final-review-739; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T34 S1 | 5 | 739 | `ProcFireball_Bubble`, `ProcFireballs`, `ProcAirBubbles`, `BublLoop`, `BublExit` / 5 | `ProcFireball_Bubble`, `ProcFireballs`, `ProcAirBubbles`, `BublLoop`, `BublExit` / 5 | closed-P1-dispatch-chain-744; [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| M2 T34 S2 | 6 | 744 | `FireballXSpdData`, `FireballObjCore`, `RunFB`, `EraseFB`, `NoFBall`, `FireballExplosion` / 6 | `FireballXSpdData`, `FireballObjCore`, `RunFB`, `EraseFB`, `NoFBall`, `FireballExplosion` / 6 | closed-P1-core-chain-750; [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| M2 T35 S1 | 8 | 750 | `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`, `Y_Bubl`, `ExitBubl`, `Bubble_MForceData`, `BubbleTimerData` / 8 | `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`, `Y_Bubl`, `ExitBubl`, `Bubble_MForceData`, `BubbleTimerData` / 8 | closed-P1-bubble-chain-758; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S2 | 4 | 758 | `RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer` / 4 | `RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer` / 4 | closed-P1-timer-chain-762; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S3 | 7 | 762 | `Jumpspring_Y_PosData`, `JumpspringHandler`, `DownJSpr`, `PosJSpr`, `BounceJS`, `DrawJSpr`, `ExJSpring` / 7 | `Jumpspring_Y_PosData`, `JumpspringHandler`, `DownJSpr`, `PosJSpr`, `BounceJS`, `DrawJSpr`, `ExJSpring` / 7 | closed-P1-jumpspring-chain-769; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S4 | 3 | 769 | `Setup_Vine`, `NextVO`, `VineHeightData` / 3 | `Setup_Vine`, `NextVO`, `VineHeightData` / 3 | closed-P1-vine-setup-chain-772; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T36 S1 | 6 | 772 | `VineObjectHandler`, `RunVSubs`, `VDrawLoop`, `KillVine`, `WrCMTile`, `ExitVH` / 6 | `VineObjectHandler`, `RunVSubs`, `VDrawLoop`, `KillVine`, `WrCMTile`, `ExitVH` / 6 | closed-P1-vine-actor-chain-778; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S2 | 10 | 778 | `HammerEnemyOfsData`, `HammerXSpdData`, `SpawnHammerObj`, `SetMOfs`, `NoHammer`, `ProcHammerObj`, `SetHSpd`, `SetHPos`, `RunAllH`, `RunHSubs` / 10 | `HammerEnemyOfsData`, `HammerXSpdData`, `SpawnHammerObj`, `SetMOfs`, `NoHammer`, `ProcHammerObj`, `SetHSpd`, `SetHPos`, `RunAllH`, `RunHSubs` / 10 | closed-P1-hammer-lifecycle-chain-788; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S3 | 6 | 788 | `CoinBlock`, `SetupJumpCoin`, `JCoinC`, `FindEmptyMiscSlot`, `FMiscLoop`, `UseMiscS` / 6 | `CoinBlock`, `SetupJumpCoin`, `JCoinC`, `FindEmptyMiscSlot`, `FMiscLoop`, `UseMiscS` / 6 | closed-P1-coin-allocation-chain-794; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S4 | 6 | 794 | `MiscObjectsCore`, `MiscLoop`, `ProcJumpCoin`, `JCoinRun`, `RunJCSubs`, `MiscLoopBack` / 6 | `MiscObjectsCore`, `MiscLoop`, `ProcJumpCoin`, `JCoinRun`, `RunJCSubs`, `MiscLoopBack` / 6 | closed-P1-misc-lifetime-chain-800; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S5 | 9 | 800 | `CoinTallyOffsets`, `ScoreOffsets`, `StatusBarNybbles`, `GiveOneCoin`, `CoinPoints`, `AddToScore`, `GetSBNybbles`, `UpdateNumber`, `NoZSup` / 9 | `CoinTallyOffsets`, `ScoreOffsets`, `StatusBarNybbles`, `GiveOneCoin`, `CoinPoints`, `AddToScore`, `GetSBNybbles`, `UpdateNumber`, `NoZSup` / 9 | closed-P1-score-hud-chain-809; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S6 | 4 | 809 | `SetupPowerUp`, `PwrUpJmp`, `StrType`, `PutBehind` / 4 | `SetupPowerUp`, `PwrUpJmp`, `StrType`, `PutBehind` / 4 | closed-P1-power-up-initialization-813; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T37 S1 | 6 | 813 | `PowerUpObjHandler`, `ShroomM`, `GrowThePowerUp`, `ChkPUSte`, `RunPUSubs`, `ExitPUp` / 6 | `PowerUpObjHandler`, `ShroomM`, `GrowThePowerUp`, `ChkPUSte`, `RunPUSubs`, `ExitPUp` / 6 | closed-P1-power-up-actor-819; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S2 | 13 | 819 | `BlockYPosAdderData`, `PlayerHeadCollision`, `DBlockSte`, `ChkBrick`, `StartBTmr`, `ContBTmr`, `PutOldMT`, `PutMTileB`, `SmallBP`, `BigBP`, `Unbreak`, `InvOBit`, `InitBlock_XY_Pos` / 13 | `BlockYPosAdderData`, `PlayerHeadCollision`, `DBlockSte`, `ChkBrick`, `StartBTmr`, `ContBTmr`, `PutOldMT`, `PutMTileB`, `SmallBP`, `BigBP`, `Unbreak`, `InvOBit`, `InitBlock_XY_Pos` / 13 | closed-P1-head-hit-position-832; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S3 | 11 | 832 | `BumpBlock`, `BlockCode`, `MushFlowerBlock`, `StarBlock`, `ExtraLifeMushBlock`, `VineBlock`, `ExitBlockChk`, `BrickQBlockMetatiles`, `BlockBumpedChk`, `BumpChkLoop`, `MatchBump` / 11 | `BumpBlock`, `BlockCode`, `MushFlowerBlock`, `StarBlock`, `ExtraLifeMushBlock`, `VineBlock`, `ExitBlockChk`, `BrickQBlockMetatiles`, `BlockBumpedChk`, `BumpChkLoop`, `MatchBump` / 11 | closed-P1-block-content-843; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S4 | 4 | 843 | `BrickShatter`, `CheckTopOfBlock`, `TopEx`, `SpawnBrickChunks` / 4 | `BrickShatter`, `CheckTopOfBlock`, `TopEx`, `SpawnBrickChunks` / 4 | closed-P1-shatter-chunks-847; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S5 | 5 | 847 | `BlockObjectsCore`, `ChkTop`, `BouncingBlockHandler`, `KillBlock`, `UpdSte` / 5 | `BlockObjectsCore`, `ChkTop`, `BouncingBlockHandler`, `KillBlock`, `UpdSte` / 5 | closed-P1-block-lifetime-852; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S6 | 3 | 852 | `BlockObjMT_Updater`, `UpdateLoop`, `NextBUpd` / 3 | `BlockObjMT_Updater`, `UpdateLoop`, `NextBUpd` / 3 | closed-P1-block-replacement-855; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S7 | 6 | 855 | `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `SaveXSpd`, `UseAdder`, `ExXMove` / 6 | `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `SaveXSpd`, `UseAdder`, `ExXMove` / 6 | closed-P1-horizontal-movement-861; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S8 | 14 | 861 | `MovePlayerVertically`, `NoJSChk`, `MoveRedPTroopaDown`, `MoveRedPTroopaUp`, `MoveRedPTroopa`, `MoveDropPlatform`, `MoveEnemySlowVert`, `SetMdMax`, `MoveJ_EnemyVertically`, `SetHiMax`, `SetXMoveAmt` / 11 | `MovePlayerVertically`, `NoJSChk`, `MoveRedPTroopaDown`, `MoveRedPTroopaUp`, `MoveRedPTroopa`, `MoveDropPlatform`, `MoveEnemySlowVert`, `SetMdMax`, `MoveJ_EnemyVertically`, `SetHiMax`, `SetXMoveAmt` / 11 | closed-P1-vertical-adapters-872; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S9 | 12 | 872 | `MaxSpdBlockData`, `ResidualGravityCode`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `MovePlatformDown`, `MovePlatformUp`, `SetDplSpd`, `RedPTroopaGrav`, `ImposeGravity`, `AlterYP`, `ChkUpM`, `ExVMove` / 12 | `MaxSpdBlockData`, `ResidualGravityCode`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `MovePlatformDown`, `MovePlatformUp`, `SetDplSpd`, `RedPTroopaGrav`, `ImposeGravity`, `AlterYP`, `ChkUpM`, `ExVMove` / 12 | closed-P1-common-gravity-884; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T38 S1 | 19 | 884 | `EnemiesAndLoopsCore`, `ChkAreaTsk`, `ChkBowserF`, `ExitELCore`, `LoopCmdWorldNumber`, `LoopCmdPageNumber`, `LoopCmdYPosition`, `ExecGameLoopback`, `ProcLoopCommand`, `FindLoop`, `IncMLoop`, `WrongChk`, `DoLpBack`, `InitMLp`, `InitLCmd`, `ChkEnemyFrenzy`, `AreaDataOfsLoopback`, `KillAllEnemies`, `KillLoop` / 19 | `EnemiesAndLoopsCore`, `ChkAreaTsk`, `ChkBowserF`, `ExitELCore`, `LoopCmdWorldNumber`, `LoopCmdPageNumber`, `LoopCmdYPosition`, `ExecGameLoopback`, `ProcLoopCommand`, `FindLoop`, `IncMLoop`, `WrongChk`, `DoLpBack`, `InitMLp`, `InitLCmd`, `ChkEnemyFrenzy`, `AreaDataOfsLoopback`, `KillAllEnemies`, `KillLoop` / 19 | closed-P1-loop-chain-903; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S2 | 19 | 903 | `ProcessEnemyData`, `CheckEndofBuffer`, `CheckRightBounds`, `CheckPageCtrlRow`, `PositionEnemyObj`, `CheckRightExtBounds`, `CheckForEnemyGroup`, `BuzzyBeetleMutate`, `StrID`, `CheckFrenzyBuffer`, `StrFre`, `InitEnemyObject`, `ExEPar`, `DoGroup`, `ParseRow0e`, `NotUse`, `CheckThreeBytes`, `Inc3B`, `Inc2B` / 19 | `ProcessEnemyData`, `CheckEndofBuffer`, `CheckRightBounds`, `CheckPageCtrlRow`, `PositionEnemyObj`, `CheckRightExtBounds`, `CheckForEnemyGroup`, `BuzzyBeetleMutate`, `StrID`, `CheckFrenzyBuffer`, `StrFre`, `InitEnemyObject`, `ExEPar`, `DoGroup`, `ParseRow0e`, `NotUse`, `CheckThreeBytes`, `Inc3B`, `Inc2B` / 19 | closed-P1-enemy-parser-922; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S3 | 3 | 922 | `CheckpointEnemyID`, `InitEnemyRoutines`, `NoInitCode` / 3 | `CheckpointEnemyID`, `InitEnemyRoutines`, `NoInitCode` / 3 | closed-P1-initializer-vector-925; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S4 | 23 | 925 | `InitGoomba`, `InitPodoboo`, `InitRetainerObj`, `NormalXSpdData`, `InitNormalEnemy`, `GetESpd`, `SetESpd`, `InitRedKoopa`, `HBroWalkingTimerData`, `InitHammerBro`, `InitHorizFlySwimEnemy`, `InitBloober`, `SmallBBox`, `InitRedPTroopa`, `GetCent`, `TallBBox`, `SetBBox`, `InitVStf`, `InitBulletBill`, `InitCheepCheep`, `InitLakitu`, `SetupLakitu`, `KillLakitu` / 23 | `InitGoomba`, `InitPodoboo`, `InitRetainerObj`, `NormalXSpdData`, `InitNormalEnemy`, `GetESpd`, `SetESpd`, `InitRedKoopa`, `HBroWalkingTimerData`, `InitHammerBro`, `InitHorizFlySwimEnemy`, `InitBloober`, `SmallBBox`, `InitRedPTroopa`, `GetCent`, `TallBBox`, `SetBBox`, `InitVStf`, `InitBulletBill`, `InitCheepCheep`, `InitLakitu`, `SetupLakitu`, `KillLakitu` / 23 | closed-P1-common-initializers-948; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S5 | 13 | 948 | `PRDiffAdjustData`, `LakituAndSpinyHandler`, `ChkLak`, `ChkNoEn`, `CreateL`, `RetEOfs`, `ExLSHand`, `CreateSpiny`, `DifLoop`, `UsePosv`, `SetSpSpd`, `SpinyRte`, `ChpChpEx` / 13 | `PRDiffAdjustData`, `LakituAndSpinyHandler`, `ChkLak`, `ChkNoEn`, `CreateL`, `RetEOfs`, `ExLSHand`, `CreateSpiny`, `DifLoop`, `UsePosv`, `SetSpSpd`, `SpinyRte`, `ChpChpEx` / 13 | closed-P1-lakitu-spiny-caller-961; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S6 | 7 | 961 | `FirebarSpinSpdData`, `FirebarSpinDirData`, `InitLongFirebar`, `InitShortFirebar`, `DuplicateEnemyObj`, `FSLoop`, `FlmEx` / 7 | `FirebarSpinSpdData`, `FirebarSpinDirData`, `InitLongFirebar`, `InitShortFirebar`, `DuplicateEnemyObj`, `FSLoop`, `FlmEx` / 7 | closed-P1-firebar-duplicate-968; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S7 | 10 | 968 | `FlyCCXPositionData`, `FlyCCXSpeedData`, `FlyCCTimerData`, `InitFlyingCheepCheep`, `MaxCC`, `GSeed`, `RSeed`, `D2XPos1`, `D2XPos2`, `FinCCSt` / 10 | `FlyCCXPositionData`, `FlyCCXSpeedData`, `FlyCCTimerData`, `InitFlyingCheepCheep`, `MaxCC`, `GSeed`, `RSeed`, `D2XPos1`, `D2XPos2`, `FinCCSt` / 10 | closed-P1-flying-fish-978; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T39 S1 | 15 | 978 | `InitBowser`, `FlameYPosData`, `FlameYMFAdderData`, `InitBowserFlame`, `SetFrT`, `PutAtRightExtent`, `SpawnFromMouth`, `SetMF`, `FinishFlame`, `FlameTimerData`, `SetFlameTimer`, `ExFl` / 12 | `InitBowser`, `FlameYPosData`, `FlameYMFAdderData`, `InitBowserFlame`, `SetFrT`, `PutAtRightExtent`, `SpawnFromMouth`, `SetMF`, `FinishFlame`, `FlameTimerData`, `SetFlameTimer`, `ExFl` / 12 | closed-P1-bowser-flame-990; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S2 | 5 | 990 | `FireworksXPosData`, `FireworksYPosData`, `InitFireworks`, `StarFChk`, `ExitFWk` / 5 | `FireworksXPosData`, `FireworksYPosData`, `InitFireworks`, `StarFChk`, `ExitFWk` / 5 | closed-P1-fireworks-995; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S3 | 14 | 995 | `Bitmasks`, `Enemy17YPosData`, `SwimCC_IDData`, `BulletBillCheepCheep`, `ChkW2`, `Get17ID`, `Set17ID`, `GetRBit`, `ChkRBit`, `AddFBit`, `DoBulletBills`, `BB_SLoop`, `ExF17`, `FireBulletBill` / 14 | `Bitmasks`, `Enemy17YPosData`, `SwimCC_IDData`, `BulletBillCheepCheep`, `ChkW2`, `Get17ID`, `Set17ID`, `GetRBit`, `ChkRBit`, `AddFBit`, `DoBulletBills`, `BB_SLoop`, `ExF17`, `FireBulletBill` / 14 | closed-P1-bullet-swim-1009; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S4 | 8 | 1009 | `HandleGroupEnemies`, `PullID`, `SnglID`, `SetYGp`, `CntGrp`, `GrLoop`, `GSltLp`, `NextED` / 8 | `HandleGroupEnemies`, `PullID`, `SnglID`, `SetYGp`, `CntGrp`, `GrLoop`, `GSltLp`, `NextED` / 8 | closed-P1-group-1017; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S5 | 9 | 1017 | `InitPiranhaPlant`, `InitEnemyFrenzy`, `NoFrenzyCode`, `EndFrenzy`, `LakituChk`, `NextFSlot`, `InitJumpGPTroopa`, `TallBBox2`, `SetBBox2` / 9 | `InitPiranhaPlant`, `InitEnemyFrenzy`, `NoFrenzyCode`, `EndFrenzy`, `LakituChk`, `NextFSlot`, `InitJumpGPTroopa`, `TallBBox2`, `SetBBox2` / 9 | closed-P1-small-initializers-1026; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S6 | 20 | 1026 | `InitBalPlatform`, `AlignP`, `SetBPA`, `InitDropPlatform`, `InitHoriPlatform`, `InitVertPlatform`, `SetYO`, `CommonPlatCode`, `SPBBox`, `CasPBB`, `LargeLiftUp`, `LargeLiftDown`, `LargeLiftBBox`, `PlatLiftUp`, `PlatLiftDown`, `CommonSmallLift`, `PlatPosDataLow`, `PlatPosDataHigh`, `PosPlatform`, `EndOfEnemyInitCode` / 20 | `InitBalPlatform`, `AlignP`, `SetBPA`, `InitDropPlatform`, `InitHoriPlatform`, `InitVertPlatform`, `SetYO`, `CommonPlatCode`, `SPBBox`, `CasPBB`, `LargeLiftUp`, `LargeLiftDown`, `LargeLiftBBox`, `PlatLiftUp`, `PlatLiftDown`, `CommonSmallLift`, `PlatPosDataLow`, `PlatPosDataHigh`, `PosPlatform`, `EndOfEnemyInitCode` / 20 | closed-P1-platform-initialization-1046; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S7 | 4 | 1046 | `RunEnemyObjectsCore`, `JmpEO`, `RunRetainerObj` / 3 | `RunEnemyObjectsCore`, `JmpEO`, `RunRetainerObj` / 3 | closed-P1-actor-callers-1049; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S8 | 4 | 1049 | `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode` / 4 | `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode` / 4 | closed-P1-normal-callers-1053; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S9 | 7 | 1053 | `RunBowserFlame`, `RunFirebarObj`, `RunSmallPlatform`, `RunLargePlatform`, `SkipPT`, `LargePlatformSubroutines` / 6 | `RunBowserFlame`, `RunFirebarObj`, `RunSmallPlatform`, `RunLargePlatform`, `SkipPT`, `LargePlatformSubroutines` / 6 | closed-P1-special-platform-callers-1059; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T40 S1 | 2 | 1059 | `MovePodoboo`, `PdbM` / 2 | `MovePodoboo`, `PdbM` / 2 | closed-P1-podoboo-1061; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S2 | 24 | 1061 | `HammerThrowTmrData`, `ProcHammerBro`, `ChkJH`, `DecHT`, `HammerBroJumpLData`, `HammerBroJumpCode`, `SetHJ`, `HJump`, `MoveHammerBroXDir`, `Shimmy`, `SetShim` / 11 | `HammerThrowTmrData`, `ProcHammerBro`, `ChkJH`, `DecHT`, `HammerBroJumpLData`, `HammerBroJumpCode`, `SetHJ`, `HJump`, `MoveHammerBroXDir`, `Shimmy`, `SetShim` / 11 | closed-P1-hammer-normal-1072; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S3 | 5 | 1072 | `MoveJumpingEnemy`, `ProcMoveRedPTroopa`, `NoIncPT`, `MoveRedPTUpOrDown`, `MovPTDwn` / 5 | `MoveJumpingEnemy`, `ProcMoveRedPTroopa`, `NoIncPT`, `MoveRedPTUpOrDown`, `MovPTDwn` / 5 | closed-P1-jumping-red-1077; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S4 | 10 | 1077 | `MoveFlyGreenPTroopa`, `YSway`, `NoMGPT`, `XMoveCntr_GreenPTroopa`, `XMoveCntr_Platform`, `NoIncXM`, `IncPXM`, `DecSeXM`, `MoveWithXMCntrs`, `XMRight` / 10 | `MoveFlyGreenPTroopa`, `YSway`, `NoMGPT`, `XMoveCntr_GreenPTroopa`, `XMoveCntr_Platform`, `NoIncXM`, `IncPXM`, `DecSeXM`, `MoveWithXMCntrs`, `XMRight` / 10 | closed-P1-green-counter-1087; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S5 | 16 | 1087 | `BlooberBitmasks`, `MoveBloober`, `FBLeft`, `SBMDir`, `BlooberSwim`, `SwimX`, `LeftSwim`, `MoveDefeatedBloober`, `ProcSwimmingB`, `BSwimE`, `SlowSwim`, `NoSSw`, `ChkForFloatdown`, `Floatdown`, `NoFD`, `ChkNearPlayer` / 16 | `BlooberBitmasks`, `MoveBloober`, `FBLeft`, `SBMDir`, `BlooberSwim`, `SwimX`, `LeftSwim`, `MoveDefeatedBloober`, `ProcSwimmingB`, `BSwimE`, `SlowSwim`, `NoSSw`, `ChkForFloatdown`, `Floatdown`, `NoFD`, `ChkNearPlayer` / 16 | closed-P1-bloober-1103; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S6 | 2 | 1103 | `MoveBulletBill`, `NotDefB` / 2 | `MoveBulletBill`, `NotDefB` / 2 | closed-P1-bullet-1105; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S7 | 7 | 1105 | `SwimCCXMoveData`, `MoveSwimmingCheepCheep`, `CCSwim`, `CCSwimUpwards`, `ChkSwimYPos`, `YPDiff`, `ExSwCC` / 7 | `SwimCCXMoveData`, `MoveSwimmingCheepCheep`, `CCSwim`, `CCSwimUpwards`, `ChkSwimYPos`, `YPDiff`, `ExSwCC` / 7 | closed-P1-swimming-cheep-1112; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S8 | 32 | 1112 | `FirebarPosLookupTbl`, `FirebarMirrorData`, `FirebarTblOffsets`, `FirebarYPos`, `ProcFirebar`, `SusFbar`, `SkpFSte`, `SetupGFB`, `SetMFbar`, `DrawFbar`, `NextFbar`, `SkipFBar`, `DrawFirebar_Collision`, `AddHA`, `SubtR1`, `ChkFOfs`, `VAHandl`, `AddVA`, `SetVFbr`, `FirebarCollision`, `AdjSm`, `BigJp`, `FBCLoop`, `ChkVFBD`, `ChkFBCl`, `Chk2Ofs`, `ChgSDir`, `SetSDir`, `NoColFB`, `GetFirebarPosition`, `GetHAdder`, `GetVAdder` / 32 | `FirebarPosLookupTbl`, `FirebarMirrorData`, `FirebarTblOffsets`, `FirebarYPos`, `ProcFirebar`, `SusFbar`, `SkpFSte`, `SetupGFB`, `SetMFbar`, `DrawFbar`, `NextFbar`, `SkipFBar`, `DrawFirebar_Collision`, `AddHA`, `SubtR1`, `ChkFOfs`, `VAHandl`, `AddVA`, `SetVFbr`, `FirebarCollision`, `AdjSm`, `BigJp`, `FBCLoop`, `ChkVFBD`, `ChkFBCl`, `Chk2Ofs`, `ChgSDir`, `SetSDir`, `NoColFB`, `GetFirebarPosition`, `GetHAdder`, `GetVAdder` / 32 | closed-P1-firebar-caller-data-1144; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S9 | 6 | 1144 | `PRandomSubtracter`, `FlyCCBPriority`, `MoveFlyingCheepCheep`, `FlyCC`, `AddCCF`, `BPGet` / 6 | `PRandomSubtracter`, `FlyCCBPriority`, `MoveFlyingCheepCheep`, `FlyCC`, `AddCCF`, `BPGet` / 6 | closed-P1-flying-cheep-1150; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S10 | 16 | 1150 | `LakituDiffAdj`, `MoveLakitu`, `ChkLS`, `Fr12S`, `LdLDa`, `SetLSpd`, `SetLMov`, `PlayerLakituDiff`, `ChkLakDif`, `SetLMovD`, `ChkPSpeed`, `ChkSpinyO`, `ChkEmySpd`, `SubDifAdj`, `SPixelLak`, `ExMoveLak` / 16 | `LakituDiffAdj`, `MoveLakitu`, `ChkLS`, `Fr12S`, `LdLDa`, `SetLSpd`, `SetLMov`, `PlayerLakituDiff`, `ChkLakDif`, `SetLMovD`, `ChkPSpeed`, `ChkSpinyO`, `ChkEmySpd`, `SubDifAdj`, `SPixelLak`, `ExMoveLak` / 16 | closed-P1-lakitu-1166; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T41 S1 | 6 | 1166 | `BridgeCollapseData`, `BridgeCollapse`, `SetM2`, `MoveD_Bowser`, `RemoveBridge`, `NoBFall` / 6 | `BridgeCollapseData`, `BridgeCollapse`, `SetM2`, `MoveD_Bowser`, `RemoveBridge`, `NoBFall` / 6 | closed-P1-bridge-1172; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S2 | 19 | 1172 | `PRandomRange`, `RunBowser`, `BowserControl`, `ChkMouth`, `FeetTmr`, `ResetMDr`, `B_FaceP`, `GetPRCmp`, `GetDToO`, `CompDToO`, `HammerChk`, `SetHmrTmr`, `SkipToFB`, `MakeBJump`, `ChkFireB`, `SpawnFBr`, `SetFBTmr` / 17 | `PRandomRange`, `RunBowser`, `BowserControl`, `ChkMouth`, `FeetTmr`, `ResetMDr`, `B_FaceP`, `GetPRCmp`, `GetDToO`, `CompDToO`, `HammerChk`, `SetHmrTmr`, `SkipToFB`, `MakeBJump`, `ChkFireB`, `SpawnFBr`, `SetFBTmr` / 17 | closed-P1-bowser-1189; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S3 | 4 | 1189 | `BowserGfxHandler`, `CopyFToR`, `ExBGfxH`, `ProcessBowserHalf` / 4 | `BowserGfxHandler`, `CopyFToR`, `ExBGfxH`, `ProcessBowserHalf` / 4 | closed-P1-bowser-graphics-1193; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S4 | 12 | 1193 | `ProcBowserFlame`, `SFlmX`, `SetGfxF`, `FlmeAt`, `DrawFlameLoop`, `M3FOfs`, `M2FOfs`, `M1FOfs`, `ExFlmeD` / 9 | `ProcBowserFlame`, `SFlmX`, `SetGfxF`, `FlmeAt`, `DrawFlameLoop`, `M3FOfs`, `M2FOfs`, `M1FOfs`, `ExFlmeD` / 9 | closed-P1-flame-actor-1202; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S5 | 3 | 1202 | `RunFireworks`, `SetupExpl`, `FireworksSoundScore` / 3 | `RunFireworks`, `SetupExpl`, `FireworksSoundScore` / 3 | closed-P1-fireworks-lifetime-1205; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S6 | 20 | 1205 | `StarFlagYPosAdder`, `StarFlagXPosAdder`, `StarFlagTileData`, `RunStarFlagObj`, `GameTimerFireworks`, `SetFWC`, `IncrementSFTask1`, `StarFlagExit`, `AwardGameTimerPoints`, `NoTTick`, `EndAreaPoints`, `ELPGive`, `RaiseFlagSetoffFWorks`, `SetoffF`, `DrawStarFlag`, `DSFLoop`, `DrawFlagSetTimer`, `IncrementSFTask2`, `DelayToAreaEnd`, `StarFlagExit2` / 20 | `StarFlagYPosAdder`, `StarFlagXPosAdder`, `StarFlagTileData`, `RunStarFlagObj`, `GameTimerFireworks`, `SetFWC`, `IncrementSFTask1`, `StarFlagExit`, `AwardGameTimerPoints`, `NoTTick`, `EndAreaPoints`, `ELPGive`, `RaiseFlagSetoffFWorks`, `SetoffF`, `DrawStarFlag`, `DSFLoop`, `DrawFlagSetTimer`, `IncrementSFTask2`, `DelayToAreaEnd`, `StarFlagExit2` / 20 | closed-P1-star-flag-1225; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S7 | 6 | 1225 | `MovePiranhaPlant`, `ChkPlayerNearPipe`, `ReversePlantSpeed`, `SetupToMovePPlant`, `RiseFallPiranhaPlant`, `PutinPipe` / 6 | `MovePiranhaPlant`, `ChkPlayerNearPipe`, `ReversePlantSpeed`, `SetupToMovePPlant`, `RiseFallPiranhaPlant`, `PutinPipe` / 6 | closed-P1-piranha-movement-1231; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S8 | 2 | 1231 | `FirebarSpin`, `SpinCounterClockwise` / 2 | `FirebarSpin`, `SpinCounterClockwise` / 2 | closed-P1-firebar-spin-1233; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S9 | 26 | 1233 | `BalancePlatform`, `DoBPl`, `CheckBalPlatform`, `ChkForFall`, `MakePlatformFall`, `ChkOtherForFall`, `ChkToMoveBalPlat`, `ColFlg`, `PlatUp`, `PlatSt`, `PlatDn`, `DoOtherPlatform`, `DrawEraseRope`, `EraseR1`, `OtherRope`, `EraseR2`, `EndRp`, `ExitRp`, `SetupPlatformRope`, `GetLRp`, `GetHRp`, `ExPRp`, `InitPlatformFall`, `StopPlatforms`, `PlatformFall`, `ExPF` / 26 | `BalancePlatform`, `DoBPl`, `CheckBalPlatform`, `ChkForFall`, `MakePlatformFall`, `ChkOtherForFall`, `ChkToMoveBalPlat`, `ColFlg`, `PlatUp`, `PlatSt`, `PlatDn`, `DoOtherPlatform`, `DrawEraseRope`, `EraseR1`, `OtherRope`, `EraseR2`, `EndRp`, `ExitRp`, `SetupPlatformRope`, `GetLRp`, `GetHRp`, `ExPRp`, `InitPlatformFall`, `StopPlatforms`, `PlatformFall`, `ExPF` / 26 | closed-P1-balanced-platforms-1259; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S10 | 6 | 1259 | `YMovingPlatform`, `SkipIY`, `ChkYCenterPos`, `YMDown`, `ChkYPCollision`, `ExYPl` / 6 | `YMovingPlatform`, `SkipIY`, `ChkYCenterPos`, `YMDown`, `ChkYPCollision`, `ExYPl` / 6 | closed-P1-vertical-platforms-1265; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S11 | 9 | 1265 | `XMovingPlatform`, `PositionPlayerOnHPlat`, `PPHSubt`, `SetPVar`, `ExXMP`, `DropPlatform`, `ExDPl`, `RightPlatform`, `ExRPl` / 9 | `XMovingPlatform`, `PositionPlayerOnHPlat`, `PPHSubt`, `SetPVar`, `ExXMP`, `DropPlatform`, `ExDPl`, `RightPlatform`, `ExRPl` / 9 | closed-P1-horizontal-platforms-1274; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S12 | 5 | 1274 | `MoveLargeLiftPlat`, `MoveSmallPlatform`, `MoveLiftPlatforms`, `ChkSmallPlatCollision`, `ExLiftP` / 5 | `MoveLargeLiftPlat`, `MoveSmallPlatform`, `MoveLiftPlatforms`, `ChkSmallPlatCollision`, `ExLiftP` / 5 | closed-P1-lift-platforms-1279; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S13 | 5 | 1279 | `OffscreenBoundsCheck`, `LimitB`, `ExtendLB`, `TooFar`, `ExScrnBd` / 5 | `OffscreenBoundsCheck`, `LimitB`, `ExtendLB`, `TooFar`, `ExScrnBd` / 5 | closed-P1-offscreen-bounds-1284; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T42 S1 | 6 | 1284 | `FireballEnemyCollision`, `FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`, `NoFToECol`, `ExitFBallEnemy` / 6 | `FireballEnemyCollision`, `FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`, `NoFToECol`, `ExitFBallEnemy` / 6 | closed-P1-fireball-enemy-scan-1290; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S2 | 11 | 1290 | `BowserIdentities`, `HandleEnemyFBallCol`, `ChkBuzzyBeetle`, `HurtBowser`, `SetDBSte`, `ChkOtherEnemies`, `ShellOrBlockDefeat`, `StnE`, `GoombaPoints`, `EnemySmackScore`, `ExHCF` / 11 | `BowserIdentities`, `HandleEnemyFBallCol`, `ChkBuzzyBeetle`, `HurtBowser`, `SetDBSte`, `ChkOtherEnemies`, `ShellOrBlockDefeat`, `StnE`, `GoombaPoints`, `EnemySmackScore`, `ExHCF` / 11 | closed-P1-fireball-hit-1301; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S3 | 3 | 1301 | `PlayerHammerCollision`, `ClHCol`, `ExPHC` / 3 | `PlayerHammerCollision`, `ClHCol`, `ExPHC` / 3 | closed-P1-hammer-contact-1304; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S4 | 6 | 1304 | `HandlePowerUpCollision`, `Shroom_Flower_PUp`, `SetFor1Up`, `UpToSuper`, `UpToFiery`, `NoPUp` / 6 | `HandlePowerUpCollision`, `Shroom_Flower_PUp`, `SetFor1Up`, `UpToSuper`, `UpToFiery`, `NoPUp` / 6 | closed-P1-powerup-pickup-1310; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S5 | 34 | 1310 | `ResidualXSpdData`, `KickedShellXSpdData`, `DemotedKoopaXSpdData`, `PlayerEnemyCollision`, `NoPECol`, `CheckForPUpCollision`, `EColl`, `KickedShellPtsData`, `HandlePECollisions`, `KSPts`, `ExPEC`, `ChkForPlayerInjury`, `ChkInj`, `ChkETmrs`, `TInjE`, `InjurePlayer`, `ForceInjury`, `SetKRout`, `SetPRout`, `ExInjColRoutines`, `KillPlayer`, `StompedEnemyPtsData`, `EnemyStomped`, `EnemyStompedPts`, `ChkForDemoteKoopa`, `RevivalRateData`, `HandleStompedShellE`, `SBnce`, `ChkEnemyFaceRight`, `LInj`, `EnemyFacePlayer`, `SFcRt`, `SetupFloateyNumber`, `ExSFN` / 34 | `ResidualXSpdData`, `KickedShellXSpdData`, `DemotedKoopaXSpdData`, `PlayerEnemyCollision`, `NoPECol`, `CheckForPUpCollision`, `EColl`, `KickedShellPtsData`, `HandlePECollisions`, `KSPts`, `ExPEC`, `ChkForPlayerInjury`, `ChkInj`, `ChkETmrs`, `TInjE`, `InjurePlayer`, `ForceInjury`, `SetKRout`, `SetPRout`, `ExInjColRoutines`, `KillPlayer`, `StompedEnemyPtsData`, `EnemyStomped`, `EnemyStompedPts`, `ChkForDemoteKoopa`, `RevivalRateData`, `HandleStompedShellE`, `SBnce`, `ChkEnemyFaceRight`, `LInj`, `EnemyFacePlayer`, `SFcRt`, `SetupFloateyNumber`, `ExSFN` / 34 | closed-P1-player-enemy-contact-1344; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S6 | 16 | 1344 | `SetBitsMask`, `ClearBitsMask`, `EnemiesCollision`, `ECLoop`, `YesEC`, `NoEnemyCollision`, `ReadyNextEnemy`, `ExitECRoutine`, `ProcEnemyCollisions`, `ShellCollisions`, `ExitProcessEColl`, `ProcSecondEnemyColl`, `MoveEOfs`, `EnemyTurnAround`, `RXSpd`, `ExTA` / 16 | `SetBitsMask`, `ClearBitsMask`, `EnemiesCollision`, `ECLoop`, `YesEC`, `NoEnemyCollision`, `ReadyNextEnemy`, `ExitECRoutine`, `ProcEnemyCollisions`, `ShellCollisions`, `ExitProcessEColl`, `ProcSecondEnemyColl`, `MoveEOfs`, `EnemyTurnAround`, `RXSpd`, `ExTA` / 16 | closed-P1-enemy-pair-1360; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S7 | 14 | 1360 | `LargePlatformCollision`, `ChkForPlayerC_LargeP`, `ExLPC`, `SmallPlatformCollision`, `ChkSmallPlatLoop`, `MoveBoundBox`, `ExSPC`, `ProcSPlatCollisions`, `ProcLPlatCollisions`, `ChkForTopCollision`, `SetCollisionFlag`, `PlatformSideCollisions`, `SideC`, `NoSideC` / 14 | `LargePlatformCollision`, `ChkForPlayerC_LargeP`, `ExLPC`, `SmallPlatformCollision`, `ChkSmallPlatLoop`, `MoveBoundBox`, `ExSPC`, `ProcSPlatCollisions`, `ProcLPlatCollisions`, `ChkForTopCollision`, `SetCollisionFlag`, `PlatformSideCollisions`, `SideC`, `NoSideC` / 14 | closed-P1-platform-collision-1374; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S8 | 4 | 1374 | `PlayerPosSPlatData`, `PositionPlayerOnS_Plat`, `PositionPlayerOnVPlat`, `ExPlPos` / 4 | `PlayerPosSPlatData`, `PositionPlayerOnS_Plat`, `PositionPlayerOnVPlat`, `ExPlPos` / 4 | closed-P1-platform-positioning-1378; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S9 | 4 | 1378 | `CheckPlayerVertical`, `ExCPV`, `GetEnemyBoundBoxOfs`, `GetEnemyBoundBoxOfsArg` / 4 | `CheckPlayerVertical`, `ExCPV`, `GetEnemyBoundBoxOfs`, `GetEnemyBoundBoxOfsArg` / 4 | closed-P1-collision-preflight-1382; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T43 S1 | 31 | 1382 | `PlayerBGUpperExtent`, `PlayerBGCollision`, `SetFallS`, `SetPSte`, `ChkOnScr`, `ExPBGCol`, `ChkCollSize`, `GBBAdr`, `HeadChk`, `SolidOrClimb`, `NYSpd`, `DoFootCheck`, `AwardTouchedCoin`, `ChkFootMTile`, `ContChk`, `LandPlyr`, `InitSteP`, `DoPlayerSideCheck`, `SideCheckLoop`, `BHalf`, `ExSCH`, `CheckSideMTiles`, `ContSChk`, `ChkPBtm`, `PipeDwnS`, `PlyrPipe`, `SetCATmr`, `ChkGERtn`, `StopPlayerMove`, `ExCSM`, `AreaChangeTimerData` / 31 | `PlayerBGUpperExtent`, `PlayerBGCollision`, `SetFallS`, `SetPSte`, `ChkOnScr`, `ExPBGCol`, `ChkCollSize`, `GBBAdr`, `HeadChk`, `SolidOrClimb`, `NYSpd`, `DoFootCheck`, `AwardTouchedCoin`, `ChkFootMTile`, `ContChk`, `LandPlyr`, `InitSteP`, `DoPlayerSideCheck`, `SideCheckLoop`, `BHalf`, `ExSCH`, `CheckSideMTiles`, `ContSChk`, `ChkPBtm`, `PipeDwnS`, `PlyrPipe`, `SetCATmr`, `ChkGERtn`, `StopPlayerMove`, `ExCSM`, `AreaChangeTimerData` / 31 | closed-P1-terrain-control-1413; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S2 | 3 | 1413 | `HandleCoinMetatile`, `HandleAxeMetatile`, `ErACM` / 3 | `HandleCoinMetatile`, `HandleAxeMetatile`, `ErACM` / 3 | closed-P1-coin-axe-1416; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S3 | 14 | 1416 | `ClimbXPosAdder`, `ClimbPLocAdder`, `FlagpoleYPosData`, `HandleClimbing`, `ExHC`, `ChkForFlagpole`, `FlagpoleCollision`, `ChkFlagpoleYPosLoop`, `MtchF`, `RunFR`, `VineCollision`, `PutPlayerOnVine`, `SetVXPl`, `ExPVne` / 14 | `ClimbXPosAdder`, `ClimbPLocAdder`, `FlagpoleYPosData`, `HandleClimbing`, `ExHC`, `ChkForFlagpole`, `FlagpoleCollision`, `ChkFlagpoleYPosLoop`, `MtchF`, `RunFR`, `VineCollision`, `PutPlayerOnVine`, `SetVXPl`, `ExPVne` / 14 | closed-P1-climbing-1429-one-baseline-claim-revoked; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S4 | 7 | 1429 | `ChkInvisibleMTiles`, `ExCInvT`, `ChkForLandJumpSpring`, `ExCJSp`, `ChkJumpspringMetatiles`, `JSFnd`, `NoJSFnd` / 7 | `ChkInvisibleMTiles`, `ExCInvT`, `ChkForLandJumpSpring`, `ExCJSp`, `ChkJumpspringMetatiles`, `JSFnd`, `NoJSFnd` / 7 | closed-P1-hidden-spring-1436; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S5 | 3 | 1436 | `HandlePipeEntry`, `GetWNum`, `ExPipeE` / 3 | `HandlePipeEntry`, `GetWNum`, `ExPipeE` / 3 | closed-P1-pipe-entry-1439; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S6 | 5 | 1439 | `ImpedePlayerMove`, `RImpd`, `NXSpd`, `PlatF`, `ExIPM` / 5 | `ImpedePlayerMove`, `RImpd`, `NXSpd`, `PlatF`, `ExIPM` / 5 | closed-P1-impede-1444; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S7 | 8 | 1444 | `SolidMTileUpperExt`, `CheckForSolidMTiles`, `ClimbMTileUpperExt`, `CheckForClimbMTiles`, `CheckForCoinMTiles`, `CoinSd`, `GetMTileAttrib` / 7 | `SolidMTileUpperExt`, `CheckForSolidMTiles`, `ClimbMTileUpperExt`, `CheckForClimbMTiles`, `CheckForCoinMTiles`, `CoinSd`, `GetMTileAttrib` / 7 | closed-P1-metatiles-1451; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S8 | 18 | 1451 | `EnemyBGCStateData`, `EnemyBGCXSpdData`, `NoEToBGCollision`, `HandleEToBGCollision`, `GiveOEPoints`, `ChkToStunEnemies`, `Demote`, `SetStun`, `SetWYSpd`, `SetNotW`, `ChkBBill`, `NoCDirF` / 12 | `EnemyBGCStateData`, `EnemyBGCXSpdData`, `NoEToBGCollision`, `HandleEToBGCollision`, `GiveOEPoints`, `ChkToStunEnemies`, `Demote`, `SetStun`, `SetWYSpd`, `SetNotW`, `ChkBBill`, `NoCDirF` / 12 | closed-enemy-background-stun; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S9 | 14 | 1463 | `LandEnemyProperly`, `SChkA`, `ChkLandedEnemyState`, `SetForStn`, `ExSteChk`, `ProcEnemyDirection`, `InvtD`, `CNwCDir`, `LandEnemyInitState`, `NMovShellFallBit`, `ChkForRedKoopa`, `Chk2MSBSt`, `GetSteFromD`, `SetD6Ste` / 14 | `LandEnemyProperly`, `SChkA`, `ChkLandedEnemyState`, `SetForStn`, `ExSteChk`, `ProcEnemyDirection`, `InvtD`, `CNwCDir`, `LandEnemyInitState`, `NMovShellFallBit`, `ChkForRedKoopa`, `Chk2MSBSt`, `GetSteFromD`, `SetD6Ste` / 14 | closed-enemy-landing-grounded; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S10 | 9 | 1477 | `ChkForBump_HammerBroJ`, `NoBump`, `InvEnemyDir`, `PlayerEnemyDiff`, `EnemyLanding`, `HammerBroBGColl`, `KillEnemyAboveBlock`, `UnderHammerBro`, `NoUnderHammerBro` / 9 | `ChkForBump_HammerBroJ`, `NoBump`, `InvEnemyDir`, `PlayerEnemyDiff`, `EnemyLanding`, `HammerBroBGColl`, `KillEnemyAboveBlock`, `UnderHammerBro`, `NoUnderHammerBro` / 9 | closed-enemy-side-jump-hammer; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S11 | 3 | 1486 | `ChkUnderEnemy`, `ChkForNonSolids`, `NSFnd` / 3 | `ChkUnderEnemy`, `ChkForNonSolids`, `NSFnd` / 3 | closed-enemy-ground-query-nonsolids; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S12 | 3 | 1489 | `FireballBGCollision`, `ClearBounceFlag`, `InitFireballExplode` / 3 | `FireballBGCollision`, `ClearBounceFlag`, `InitFireballExplode` / 3 | closed-fireball-background-collision; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S13 | 11 | 1492 | `BoundBoxCtrlData`, `GetFireballBoundBox`, `GetMiscBoundBox`, `FBallB`, `GetEnemyBoundBox`, `SmallPlatformBoundBox`, `GetMaskedOffScrBits`, `CMBits`, `LargePlatformBoundBox`, `SetupEOffsetFBBox`, `MoveBoundBoxOffscreen` / 11 | `BoundBoxCtrlData`, `GetFireballBoundBox`, `GetMiscBoundBox`, `FBallB`, `GetEnemyBoundBox`, `SmallPlatformBoundBox`, `GetMaskedOffScrBits`, `CMBits`, `LargePlatformBoundBox`, `SetupEOffsetFBBox`, `MoveBoundBoxOffscreen` / 11 | closed-object-bounding-box-entry; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S14 | 7 | 1503 | `BoundingBoxCore`, `CheckRightScreenBBox`, `SORte`, `NoOfs`, `CheckLeftScreenBBox`, `SOLft`, `NoOfs2` / 7 | `BoundingBoxCore`, `CheckRightScreenBBox`, `SORte`, `NoOfs`, `CheckLeftScreenBBox`, `SOLft`, `NoOfs2` / 7 | closed-bounding-box-core-clipping; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S15 | 7 | 1510 | `PlayerCollisionCore`, `SprObjectCollisionCore`, `CollisionCoreLoop`, `SecondBoxVerticalChk`, `FirstBoxGreater`, `NoCollisionFound`, `CollisionFound` / 7 | `PlayerCollisionCore`, `SprObjectCollisionCore`, `CollisionCoreLoop`, `SecondBoxVerticalChk`, `FirstBoxGreater`, `NoCollisionFound`, `CollisionFound` / 7 | closed-shared-box-collision-geometry; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T44 S1 | 14 | 1517 | `BlockBufferChk_Enemy`, `ResidualMiscObjectCode`, `BlockBufferChk_FBall`, `ResJmpM`, `BBChk_E`, `BlockBufferAdderData`, `BlockBuffer_X_Adder`, `BlockBuffer_Y_Adder`, `BlockBufferColli_Feet`, `BlockBufferColli_Head`, `BlockBufferColli_Side`, `BlockBufferCollision`, `RetXC`, `RetYC` / 14 | `BlockBufferChk_Enemy`, `ResidualMiscObjectCode`, `BlockBufferChk_FBall`, `ResJmpM`, `BBChk_E`, `BlockBufferAdderData`, `BlockBuffer_X_Adder`, `BlockBuffer_Y_Adder`, `BlockBufferColli_Feet`, `BlockBufferColli_Head`, `BlockBufferColli_Side`, `BlockBufferCollision`, `RetXC`, `RetYC` / 14 | closed-block-buffer-core; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S2 | 6 | 1531 | `VineYPosAdder`, `DrawVine`, `VineTL`, `SkpVTop`, `ChkFTop`, `NextVSp` / 6 | `VineYPosAdder`, `DrawVine`, `VineTL`, `SkpVTop`, `ChkFTop`, `NextVSp` / 6 | closed-vine-object-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S3 | 14 | 1537 | `SixSpriteStacker`, `StkLp`, `FirstSprXPos`, `FirstSprYPos`, `SecondSprXPos`, `SecondSprYPos`, `FirstSprTilenum`, `SecondSprTilenum`, `HammerSprAttrib`, `DrawHammer`, `ForceHPose`, `GetHPose`, `RenderH`, `NoHOffscr` / 14 | `SixSpriteStacker`, `StkLp`, `FirstSprXPos`, `FirstSprYPos`, `SecondSprXPos`, `SecondSprYPos`, `FirstSprTilenum`, `SecondSprTilenum`, `HammerSprAttrib`, `DrawHammer`, `ForceHPose`, `GetHPose`, `RenderH`, `NoHOffscr` / 14 | closed-six-sprite-hammer-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S4 | 9 | 1551 | `FlagpoleScoreNumTiles`, `FlagpoleGfxHandler`, `ChkFlagOffscreen`, `MoveSixSpritesOffscreen`, `DumpSixSpr`, `DumpFourSpr`, `DumpThreeSpr`, `DumpTwoSpr`, `ExitDumpSpr` / 9 | `FlagpoleScoreNumTiles`, `FlagpoleGfxHandler`, `ChkFlagOffscreen`, `MoveSixSpritesOffscreen`, `DumpSixSpr`, `DumpFourSpr`, `DumpThreeSpr`, `DumpTwoSpr`, `ExitDumpSpr` / 9 | closed-flagpole-oam-dump-helpers; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S5 | 11 | 1560 | `DrawLargePlatform`, `ShrinkPlatform`, `SetLast2Platform`, `SetPlatformTilenum`, `SChk2`, `SChk3`, `SChk4`, `SChk5`, `SChk6`, `SLChk`, `ExDLPl` / 11 | `DrawLargePlatform`, `ShrinkPlatform`, `SetLast2Platform`, `SetPlatformTilenum`, `SChk2`, `SChk3`, `SChk4`, `SChk5`, `SChk6`, `SLChk`, `ExDLPl` / 11 | closed-large-platform-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S6 | 5 | 1571 | `DrawFloateyNumber_Coin`, `NotRsNum`, `JumpingCoinTiles`, `JCoinGfxHandler`, `ExJCGfx` / 5 | `DrawFloateyNumber_Coin`, `NotRsNum`, `JumpingCoinTiles`, `JCoinGfxHandler`, `ExJCGfx` / 5 | closed-floatey-jumping-coin-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S7 | 6 | 1576 | `PowerUpGfxTable`, `PowerUpAttributes`, `DrawPowerUp`, `PUpDrawLoop`, `FlipPUpRightSide`, `PUpOfs` / 6 | `PowerUpGfxTable`, `PowerUpAttributes`, `DrawPowerUp`, `PUpDrawLoop`, `FlipPUpRightSide`, `PUpOfs` / 6 | closed-power-up-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S8 | 44 | 1582 | `EnemyGraphicsTable`, `EnemyGfxTableOffsets`, `EnemyAttributeData`, `EnemyAnimTimingBMask`, `JumpspringFrameOffsets`, `EnemyGfxHandler`, `CheckForRetainerObj`, `CheckForJumpspring`, `CheckForPodoboo`, `CheckBowserGfxFlag`, `SBwsrGfxOfs`, `CheckForGoomba`, `GmbaAnim`, `CheckBowserFront`, `ChkFrontSte`, `FlipBowserOver`, `DrawBowser`, `CheckBowserRear`, `ChkRearSte`, `CheckForSpiny`, `NotEgg`, `CheckForLakitu`, `NoLAFr`, `CheckUpsideDownShell`, `CheckRightSideUpShell`, `CheckForDefdGoomba`, `CheckForHammerBro`, `CheckForBloober`, `CheckToAnimateEnemy`, `CheckForSecondFrame`, `CheckAnimationStop`, `CheckDefeatedState`, `DrawEnemyObject`, `SkipToOffScrChk`, `CheckForVerticalFlip`, `FlipEnemyVertically`, `CheckForESymmetry`, `ContES`, `ESRtnr`, `SpnySC`, `MirrorEnemyGfx`, `EggExc` / 42 | `EnemyGraphicsTable`, `EnemyGfxTableOffsets`, `EnemyAttributeData`, `EnemyAnimTimingBMask`, `JumpspringFrameOffsets`, `EnemyGfxHandler`, `CheckForRetainerObj`, `CheckForJumpspring`, `CheckForPodoboo`, `CheckBowserGfxFlag`, `SBwsrGfxOfs`, `CheckForGoomba`, `GmbaAnim`, `CheckBowserFront`, `ChkFrontSte`, `FlipBowserOver`, `DrawBowser`, `CheckBowserRear`, `ChkRearSte`, `CheckForSpiny`, `NotEgg`, `CheckForLakitu`, `NoLAFr`, `CheckUpsideDownShell`, `CheckRightSideUpShell`, `CheckForDefdGoomba`, `CheckForHammerBro`, `CheckForBloober`, `CheckToAnimateEnemy`, `CheckForSecondFrame`, `CheckAnimationStop`, `CheckDefeatedState`, `DrawEnemyObject`, `SkipToOffScrChk`, `CheckForVerticalFlip`, `FlipEnemyVertically`, `CheckForESymmetry`, `ContES`, `ESRtnr`, `SpnySC`, `MirrorEnemyGfx`, `EggExc` / 42 | closed-enemy-graphics-animation; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T45 S1 | 13 | 1624 | `CheckToMirrorLakitu`, `NVFLak`, `CheckToMirrorJSpring`, `SprObjectOffscrChk`, `LcChk`, `Row3C`, `Row23C`, `AllRowC`, `ExEGHandler`, `DrawEnemyObjRow`, `DrawOneSpriteRow`, `MoveESprRowOffscreen`, `MoveESprColOffscreen` / 13 | `CheckToMirrorLakitu`, `NVFLak`, `CheckToMirrorJSpring`, `SprObjectOffscrChk`, `LcChk`, `Row3C`, `Row23C`, `AllRowC`, `ExEGHandler`, `DrawEnemyObjRow`, `DrawOneSpriteRow`, `MoveESprRowOffscreen`, `MoveESprColOffscreen` / 13 | closed-enemy-oam-tail; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S2 | 14 | 1637 | `DefaultBlockObjTiles`, `DrawBlock`, `DBlkLoop`, `ChkRep`, `SetBFlip`, `BlkOffscr`, `PullOfsB`, `ChkLeftCo`, `MoveColOffscreen`, `ExDBlk`, `DrawBrickChunks`, `DChunks`, `ChnkOfs`, `ExBCDr` / 14 | `DefaultBlockObjTiles`, `DrawBlock`, `DBlkLoop`, `ChkRep`, `SetBFlip`, `BlkOffscr`, `PullOfsB`, `ChkLeftCo`, `MoveColOffscreen`, `ExDBlk`, `DrawBrickChunks`, `DChunks`, `ChnkOfs`, `ExBCDr` / 14 | closed-block-and-chunk-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S3 | 7 | 1651 | `DrawFireball`, `DrawFirebar`, `FireA`, `ExplosionTiles`, `DrawExplosion_Fireball`, `DrawExplosion_Fireworks`, `KillFireBall` / 7 | `DrawFireball`, `DrawFirebar`, `FireA`, `ExplosionTiles`, `DrawExplosion_Fireball`, `DrawExplosion_Fireworks`, `KillFireBall` / 7 | closed-projectile-explosion-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S4 | 6 | 1658 | `DrawSmallPlatform`, `TopSP`, `BotSP`, `SOfs`, `SOfs2`, `ExSPl` / 6 | `DrawSmallPlatform`, `TopSP`, `BotSP`, `SOfs`, `SOfs2`, `ExSPl` / 6 | closed-small-platform-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S5 | 5 | 1664 | `DrawBubble`, `ExDBub`, `PlayerGfxTblOffsets`, `PlayerGraphicsTable`, `SwimKickTileNum` / 5 | `DrawBubble`, `ExDBub`, `PlayerGfxTblOffsets`, `PlayerGraphicsTable`, `SwimKickTileNum` / 5 | closed-bubble-player-graphics; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T46 S1 | 13 | 1669 | `PlayerGfxHandler`, `CntPl`, `SwimKT`, `BigKTS`, `ExPGH`, `FindPlayerAction`, `DoChangeSize`, `PlayerKilled`, `PlayerGfxProcessing`, `SUpdR` / 10 | `PlayerGfxHandler`, `CntPl`, `SwimKT`, `BigKTS`, `ExPGH`, `FindPlayerAction`, `DoChangeSize`, `PlayerKilled`, `PlayerGfxProcessing`, `SUpdR` / 10 | closed-player-graphics-dispatch-offscreen; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S2 | 5 | 1679 | `IntermediatePlayerData`, `DrawPlayer_Intermediate`, `PIntLoop`, `RenderPlayerSub`, `DrawPlayerLoop` / 5 | `IntermediatePlayerData`, `DrawPlayer_Intermediate`, `PIntLoop`, `RenderPlayerSub`, `DrawPlayerLoop` / 5 | closed-intermediate-player-row-render; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S3 | 13 | 1684 | `ProcessPlayerAction`, `ProcOnGroundActs`, `NonAnimatedActs`, `ActionFalling`, `ActionWalkRun`, `ActionClimbing`, `ActionSwimming`, `GetCurrentAnimOffset`, `FourFrameExtent`, `ThreeFrameExtent`, `AnimationControl`, `SetAnimC`, `ExAnimC` / 13 | `ProcessPlayerAction`, `ProcOnGroundActs`, `NonAnimatedActs`, `ActionFalling`, `ActionWalkRun`, `ActionClimbing`, `ActionSwimming`, `GetCurrentAnimOffset`, `FourFrameExtent`, `ThreeFrameExtent`, `AnimationControl`, `SetAnimC`, `ExAnimC` / 13 | closed-player-action-animation-control; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S4 | 12 | 1697 | `GetGfxOffsetAdder`, `SzOfs`, `ChangeSizeOffsetAdder`, `HandleChangeSize`, `CSzNext`, `GorSLog`, `GetOffsetFromAnimCtrl`, `ShrinkPlayer`, `ShrPlF`, `ChkForPlayerAttrib`, `KilledAtt`, `C_S_IGAtt` / 12 | `GetGfxOffsetAdder`, `SzOfs`, `ChangeSizeOffsetAdder`, `HandleChangeSize`, `CSzNext`, `GorSLog`, `GetOffsetFromAnimCtrl`, `ShrinkPlayer`, `ShrPlF`, `ChkForPlayerAttrib`, `KilledAtt`, `C_S_IGAtt` / 12 | closed-player-size-attribute-control; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T47 S1 | 1 | 1709 | `ExPlyrAt` / 1 | `ExPlyrAt` / 1 | closed-player-attribute-exit; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S2 | 9 | 1710 | `RelativePlayerPosition`, `RelativeBubblePosition`, `RelativeFireballPosition`, `RelWOfs`, `RelativeMiscPosition`, `RelativeEnemyPosition`, `RelativeBlockPosition`, `VariableObjOfsRelPos`, `GetObjRelativePosition` / 9 | `RelativePlayerPosition`, `RelativeBubblePosition`, `RelativeFireballPosition`, `RelWOfs`, `RelativeMiscPosition`, `RelativeEnemyPosition`, `RelativeBlockPosition`, `VariableObjOfsRelPos`, `GetObjRelativePosition` / 9 | closed-relative-object-coordinates; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S3 | 1 | 1719 | `GetPlayerOffscreenBits` / 1 | `GetPlayerOffscreenBits` / 1 | closed-player-offscreen-entry; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S4 | 26 | 1720 | `GetFireballOffscreenBits`, `GetBubbleOffscreenBits`, `GetMiscOffscreenBits`, `ObjOffsetData`, `GetProperObjOffset`, `GetEnemyOffscreenBits`, `GetBlockOffscreenBits`, `SetOffscrBitsOffset`, `GetOffScreenBitsSet`, `RunOffscrBitsSubs`, `XOffscreenBitsData`, `DefaultXOnscreenOfs`, `GetXOffscreenBits`, `XOfsLoop`, `XLdBData`, `ExXOfsBS`, `YOffscreenBitsData`, `DefaultYOnscreenOfs`, `HighPosUnitData`, `GetYOffscreenBits`, `YOfsLoop`, `YLdBData`, `ExYOfsBS`, `DividePDiff`, `SetOscrO`, `ExDivPD` / 26 | `GetFireballOffscreenBits`, `GetBubbleOffscreenBits`, `GetMiscOffscreenBits`, `ObjOffsetData`, `GetProperObjOffset`, `GetEnemyOffscreenBits`, `GetBlockOffscreenBits`, `SetOffscrBitsOffset`, `GetOffScreenBitsSet`, `RunOffscrBitsSubs`, `XOffscreenBitsData`, `DefaultXOnscreenOfs`, `GetXOffscreenBits`, `XOfsLoop`, `XLdBData`, `ExXOfsBS`, `YOffscreenBitsData`, `DefaultYOnscreenOfs`, `HighPosUnitData`, `GetYOffscreenBits`, `YOfsLoop`, `YLdBData`, `ExYOfsBS`, `DividePDiff`, `SetOscrO`, `ExDivPD` / 26 | closed-shared-offscreen-chain; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S5 | 3 | 1746 | `DrawSpriteObject`, `NoHFlip`, `SetHFAt` / 3 | `DrawSpriteObject`, `NoHFlip`, `SetHFAt` / 3 | closed-rom-match-complete; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T48 S1 | 13 | 1749 | `SoundEngine`, `SndOn`, `InPause`, `PTone1F`, `ContPau`, `PTone2F`, `PTRegC`, `DecPauC`, `SkipPIn`, `RunSoundSubroutines`, `SkipSoundSubroutines`, `NoIncDAC`, `StrWave` / 13 | `SoundEngine`, `SndOn`, `InPause`, `PTone1F`, `ContPau`, `PTone2F`, `PTRegC`, `DecPauC`, `SkipPIn`, `RunSoundSubroutines`, `SkipSoundSubroutines`, `NoIncDAC`, `StrWave` / 13 | closed-rom-match-complete; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S2 | 9 | 1762 | `Dump_Squ1_Regs`, `PlaySqu1Sfx`, `SetFreq_Squ1`, `Dump_Freq_Regs`, `NoTone`, `Dump_Sq2_Regs`, `PlaySqu2Sfx`, `SetFreq_Squ2`, `SetFreq_Tri` / 9 | `Dump_Squ1_Regs`, `PlaySqu1Sfx`, `SetFreq_Squ1`, `Dump_Freq_Regs`, `NoTone`, `Dump_Sq2_Regs`, `PlaySqu2Sfx`, `SetFreq_Squ2`, `SetFreq_Tri` / 9 | closed-rom-match-complete; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S3 | 14 | 1771 | `SwimStompEnvelopeData`, `PlayFlagpoleSlide`, `PlaySmallJump`, `PlayBigJump`, `JumpRegContents`, `ContinueSndJump`, `N2Prt`, `FPS2nd`, `DmpJpFPS`, `PlayFireballThrow`, `PlayBump`, `Fthrow`, `ContinueBumpThrow`, `DecJpFPS` / 14 | `SwimStompEnvelopeData`, `PlayFlagpoleSlide`, `PlaySmallJump`, `PlayBigJump`, `JumpRegContents`, `ContinueSndJump`, `N2Prt`, `FPS2nd`, `DmpJpFPS`, `PlayFireballThrow`, `PlayBump`, `Fthrow`, `ContinueBumpThrow`, `DecJpFPS` / 14 | closed-rom-match-complete; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S4 | 16 | 1785 | `Square1SfxHandler`, `CheckSfx1Buffer`, `ExS1H`, `PlaySwimStomp`, `ContinueSwimStomp`, `BranchToDecLength1`, `PlaySmackEnemy`, `ContinueSmackEnemy`, `SmSpc`, `SmTick`, `DecrementSfx1Length`, `StopSquare1Sfx`, `ExSfx1`, `PlayPipeDownInj`, `ContinuePipeDownInj`, `NoPDwnL` / 16 | `Square1SfxHandler`, `CheckSfx1Buffer`, `ExS1H`, `PlaySwimStomp`, `ContinueSwimStomp`, `BranchToDecLength1`, `PlaySmackEnemy`, `ContinueSmackEnemy`, `SmSpc`, `SmTick`, `DecrementSfx1Length`, `StopSquare1Sfx`, `ExSfx1`, `PlayPipeDownInj`, `ContinuePipeDownInj`, `NoPDwnL` / 16 | closed-rom-match-complete; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S5 | 18 | 1801 | `ExtraLifeFreqData`, `PowerUpGrabFreqData`, `PUp_VGrow_FreqData`, `PlayCoinGrab`, `PlayTimerTick`, `CGrab_TTickRegL`, `ContinueCGrabTTick`, `N2Tone`, `PlayBlast`, `ContinueBlast`, `SBlasJ`, `PlayPowerUpGrab`, `ContinuePowerUpGrab`, `LoadSqu2Regs`, `DecrementSfx2Length`, `EmptySfx2Buffer`, `StopSquare2Sfx`, `ExSfx2` / 18 | `ExtraLifeFreqData`, `PowerUpGrabFreqData`, `PUp_VGrow_FreqData`, `PlayCoinGrab`, `PlayTimerTick`, `CGrab_TTickRegL`, `ContinueCGrabTTick`, `N2Tone`, `PlayBlast`, `ContinueBlast`, `SBlasJ`, `PlayPowerUpGrab`, `ContinuePowerUpGrab`, `LoadSqu2Regs`, `DecrementSfx2Length`, `EmptySfx2Buffer`, `StopSquare2Sfx`, `ExSfx2` / 18 | closed-rom-match-complete; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S6 | 4 | 1819 | `Square2SfxHandler`, `CheckSfx2Buffer`, `ExS2H`, `Cont_CGrab_TTick` / 4 | `Square2SfxHandler`, `CheckSfx2Buffer`, `ExS2H`, `Cont_CGrab_TTick` / 4 | closed-rom-match-complete; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T49 S1 | 14 | 1823 | `JumpToDecLength2`, `PlayBowserFall`, `BlstSJp`, `ContinueBowserFall`, `PBFRegs`, `EL_LRegs`, `PlayExtraLife`, `ContinueExtraLife`, `DivLLoop`, `PlayGrowPowerUp`, `PlayGrowVine`, `GrowItemRegs`, `ContinueGrowItems`, `StopGrowItems` / 14 | `JumpToDecLength2`, `PlayBowserFall`, `BlstSJp`, `ContinueBowserFall`, `PBFRegs`, `EL_LRegs`, `PlayExtraLife`, `ContinueExtraLife`, `DivLLoop`, `PlayGrowPowerUp`, `PlayGrowVine`, `GrowItemRegs`, `ContinueGrowItems`, `StopGrowItems` / 14 | closed-rom-match-complete; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S2 | 12 | 1837 | `BrickShatterFreqData`, `PlayBrickShatter`, `ContinueBrickShatter`, `PlayNoiseSfx`, `DecrementSfx3Length`, `ExSfx3`, `NoiseSfxHandler`, `CheckNoiseBuffer`, `ExNH`, `PlayBowserFlame`, `ContinueBowserFlame`, `ContinueMusic` / 12 | `BrickShatterFreqData`, `PlayBrickShatter`, `ContinueBrickShatter`, `PlayNoiseSfx`, `DecrementSfx3Length`, `ExSfx3`, `NoiseSfxHandler`, `CheckNoiseBuffer`, `ExNH`, `PlayBowserFlame`, `ContinueBowserFlame`, `ContinueMusic` / 12 | closed; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S3 | 10 | 1849 | `MusicHandler`, `LoadEventMusic`, `NoStopSfx`, `LoadAreaMusic`, `NoStop1`, `GMLoopB`, `HandleAreaMusicLoopB`, `FindAreaMusicHeader`, `FindEventMusicHeader`, `LoadHeader` / 10 | `MusicHandler`, `LoadEventMusic`, `NoStopSfx`, `LoadAreaMusic`, `NoStop1`, `GMLoopB`, `HandleAreaMusicLoopB`, `FindAreaMusicHeader`, `FindEventMusicHeader`, `LoadHeader` / 10 | closed-rom-match-complete; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S4 | 11 | 1859 | `HandleSquare2Music`, `EndOfMusicData`, `NotTRO`, `MusicLoopBack`, `VictoryMLoopBack`, `Squ2LengthHandler`, `Squ2NoteHandler`, `Rest`, `SkipFqL1`, `MiscSqu2MusicTasks`, `NoDecEnv1` / 11 | `HandleSquare2Music`, `EndOfMusicData`, `NotTRO`, `MusicLoopBack`, `VictoryMLoopBack`, `Squ2LengthHandler`, `Squ2NoteHandler`, `Rest`, `SkipFqL1`, `MiscSqu2MusicTasks`, `NoDecEnv1` / 11 | closed-rom-match-complete; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S5 | 8 | 1870 | `HandleSquare1Music`, `FetchSqu1MusicData`, `Squ1NoteHandler`, `SkipCtrlL`, `MiscSqu1MusicTasks`, `NoDecEnv2`, `DeathMAltReg`, `DoAltLoad` / 8 | `HandleSquare1Music`, `FetchSqu1MusicData`, `Squ1NoteHandler`, `SkipCtrlL`, `MiscSqu1MusicTasks`, `NoDecEnv2`, `DeathMAltReg`, `DoAltLoad` / 8 | closed-rom-match-complete; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S6 | 6 | 1878 | `HandleTriangleMusic`, `TriNoteHandler`, `NotDOrD4`, `MediN`, `LongN`, `LoadTriCtrlReg` / 6 | `HandleTriangleMusic`, `TriNoteHandler`, `NotDOrD4`, `MediN`, `LongN`, `LoadTriCtrlReg` / 6 | closed-rom-match-complete; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S7 | 8 | 1884 | `HandleNoiseMusic`, `FetchNoiseBeatData`, `NoiseBeatHandler`, `StrongBeat`, `LongBeat`, `SilentBeat`, `PlayBeat`, `ExitMusicHandler` / 8 | `HandleNoiseMusic`, `FetchNoiseBeatData`, `NoiseBeatHandler`, `StrongBeat`, `LongBeat`, `SilentBeat`, `PlayBeat`, `ExitMusicHandler` / 8 | closed-rom-match-complete; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S8 | 9 | 1892 | `AlternateLengthHandler`, `ProcessLengthData`, `LoadControlRegs`, `NotECstlM`, `WaterMus`, `AllMus`, `LoadEnvelopeData`, `LoadUsualEnvData`, `LoadWaterEventMusEnvData` / 9 | `AlternateLengthHandler`, `ProcessLengthData`, `LoadControlRegs`, `NotECstlM`, `WaterMus`, `AllMus`, `LoadEnvelopeData`, `LoadUsualEnvData`, `LoadWaterEventMusEnvData` / 9 | closed-rom-match-complete; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S9 | 23 | 1901 | `MusicHeaderData`, `TimeRunningOutHdr`, `Star_CloudHdr`, `EndOfLevelMusHdr`, `ResidualHeaderData`, `UndergroundMusHdr`, `SilenceHdr`, `CastleMusHdr`, `VictoryMusHdr`, `GameOverMusHdr`, `WaterMusHdr`, `WinCastleMusHdr`, `GroundLevelPart1Hdr`, `GroundLevelPart2AHdr`, `GroundLevelPart2BHdr`, `GroundLevelPart2CHdr`, `GroundLevelPart3AHdr`, `GroundLevelPart3BHdr`, `GroundLevelLeadInHdr`, `GroundLevelPart4AHdr`, `GroundLevelPart4BHdr`, `GroundLevelPart4CHdr`, `DeathMusHdr` / 23 | `MusicHeaderData`, `TimeRunningOutHdr`, `Star_CloudHdr`, `EndOfLevelMusHdr`, `ResidualHeaderData`, `UndergroundMusHdr`, `SilenceHdr`, `CastleMusHdr`, `VictoryMusHdr`, `GameOverMusHdr`, `WaterMusHdr`, `WinCastleMusHdr`, `GroundLevelPart1Hdr`, `GroundLevelPart2AHdr`, `GroundLevelPart2BHdr`, `GroundLevelPart2CHdr`, `GroundLevelPart3AHdr`, `GroundLevelPart3BHdr`, `GroundLevelLeadInHdr`, `GroundLevelPart4AHdr`, `GroundLevelPart4BHdr`, `GroundLevelPart4CHdr`, `DeathMusHdr` / 23 | closed-rom-match-complete; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T50 S1 | 21 | 1924 | `Star_CloudMData`, `GroundM_P1Data`, `SilenceData`, `GroundM_P2AData`, `GroundM_P2BData`, `GroundM_P2CData`, `GroundM_P3AData`, `GroundM_P3BData`, `GroundMLdInData`, `GroundM_P4AData`, `GroundM_P4BData`, `DeathMusData`, `GroundM_P4CData`, `CastleMusData`, `GameOverMusData`, `TimeRunOutMusData`, `WinLevelMusData`, `UndergroundMusData`, `WaterMusData`, `EndOfCastleMusData`, `VictoryMusData` / 21 | `Star_CloudMData`, `GroundM_P1Data`, `SilenceData`, `GroundM_P2AData`, `GroundM_P2BData`, `GroundM_P2CData`, `GroundM_P3AData`, `GroundM_P3BData`, `GroundMLdInData`, `GroundM_P4AData`, `GroundM_P4BData`, `DeathMusData`, `GroundM_P4CData`, `CastleMusData`, `GameOverMusData`, `TimeRunOutMusData`, `WinLevelMusData`, `UndergroundMusData`, `WaterMusData`, `EndOfCastleMusData`, `VictoryMusData` / 21 | closed-rom-match-complete; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T50 S2 | 5 | 1945 | `FreqRegLookupTbl`, `MusicLengthLookupTbl`, `EndOfCastleMusicEnvData`, `AreaMusicEnvData`, `WaterEventMusEnvData` / 5 | `FreqRegLookupTbl`, `MusicLengthLookupTbl`, `EndOfCastleMusicEnvData`, `AreaMusicEnvData`, `WaterEventMusEnvData` / 5 | closed-music-lookup-envelope-chain; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T50 S3 | 2 | 1950 | `BowserFlameEnvData`, `BrickShatterEnvData` / 2 | `BowserFlameEnvData`, `BrickShatterEnvData` / 2 | closed-noise-envelope-chain; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T51 S1 | 1 | 1952 | `NonMaskableInterrupt` / 1 | `NonMaskableInterrupt` / 1 | closed-nmi-parent-integration; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S2 | 4 | 1953 | `ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol` / 4 | `ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol` / 4 | closed-screen-parser-output-chain; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S3 | 1 | 1957 | `KillEnemies` / 1 | `KillEnemies` / 1 | closed-kill-enemies-shared-primitive; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S4 | 34 | 1958 | `E_CastleArea1`, `E_CastleArea2`, `E_CastleArea3`, `E_CastleArea4`, `E_CastleArea5`, `E_CastleArea6`, `E_GroundArea1`, `E_GroundArea2`, `E_GroundArea3`, `E_GroundArea4`, `E_GroundArea5`, `E_GroundArea6`, `E_GroundArea7`, `E_GroundArea8`, `E_GroundArea9`, `E_GroundArea10`, `E_GroundArea11`, `E_GroundArea12`, `E_GroundArea13`, `E_GroundArea14`, `E_GroundArea15`, `E_GroundArea16`, `E_GroundArea17`, `E_GroundArea18`, `E_GroundArea19`, `E_GroundArea20`, `E_GroundArea21`, `E_GroundArea22`, `E_UndergroundArea1`, `E_UndergroundArea2`, `E_UndergroundArea3`, `E_WaterArea1`, `E_WaterArea2`, `E_WaterArea3` / 34 | `E_CastleArea1`, `E_CastleArea2`, `E_CastleArea3`, `E_CastleArea4`, `E_CastleArea5`, `E_CastleArea6`, `E_GroundArea1`, `E_GroundArea2`, `E_GroundArea3`, `E_GroundArea4`, `E_GroundArea5`, `E_GroundArea6`, `E_GroundArea7`, `E_GroundArea8`, `E_GroundArea9`, `E_GroundArea10`, `E_GroundArea11`, `E_GroundArea12`, `E_GroundArea13`, `E_GroundArea14`, `E_GroundArea15`, `E_GroundArea16`, `E_GroundArea17`, `E_GroundArea18`, `E_GroundArea19`, `E_GroundArea20`, `E_GroundArea21`, `E_GroundArea22`, `E_UndergroundArea1`, `E_UndergroundArea2`, `E_UndergroundArea3`, `E_WaterArea1`, `E_WaterArea2`, `E_WaterArea3` / 34 | closed-enemy-stream-data-chain; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S5 | 0 | 1992 | none / 0 | none / 0 | closed-historical-certification-handoff; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 Td S9 | 0 | 1992 | none / 0 | none / 0 | closed-current-equivalence-governance; [record](../../docs/proposals/m2/current-equivalence-reaudit.md) |
| M2 T52 S1 | 3 | 1992 | none / 0 | none / 0 | closed-a2-current-equivalence-remediation; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S2 | 2 | 1992 | none / 0 | none / 0 | closed-a6-title-demo-world-select-order; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S3 | 4 | 1992 | none / 0 | none / 0 | closed-a7-floatey-score-timer-order; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S4 | 3 | 1992 | none / 0 | none / 0 | closed-b2-background-player-palette-fallthrough; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S5 | 3 | 1992 | none / 0 | none / 0 | closed-b3-timeup-candidate-rejected; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S6 | 1 | 1992 | none / 0 | none / 0 | closed-h9-large-platform-y-source; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S7 | 0 | 1992 | none / 0 | none / 0 | closed-h1-h8-infeasible-control-edge-disposition; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T53 S1 | 39 | 1992 | none / 0 | none / 0 | closed-s1-current-equivalence-audit; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S2 | 26 | 1992 | none / 0 | none / 0 | closed-s2-current-equivalence-audit; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S3 | 1 | 1992 | none / 0 | none / 0 | closed-screenoff-current-exact; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S4 | 22 | 1992 | none / 0 | none / 0 | closed-victory-current-exact; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T53 S5 | 10 | 1992 | none / 0 | none / 0 | closed-floatey-current-equivalence-audit; [record](../../docs/proposals/m2/t53-cohort-a-current-proof.md) |
| M2 T54 S1 | 20 | 1992 | none / 0 | none / 0 | closed-screen-palette-current-equivalence-audit; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S2 | 9 | 1992 | none / 0 | none / 0 | closed-status-intermediate-current-equivalence-audit; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S3 | 8 | 1992 | none / 0 | none / 0 | closed-title-screen-current-equivalence-audit; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S4 | 23 | 1992 | none / 0 | none / 0 | closed-game-text-current-equivalence-audit; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S5 | 3 | 1992 | none / 0 | none / 0 | closed-reset-screen-timer-current-equivalence-audit; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S6 | 3 | 1992 | none / 0 | none / 0 | closed-parser-task-handoff-current-equivalence-audit; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T54 S7 | 1 | 1992 | none / 0 | none / 0 | admitted-screen-routines-dispatcher-current-equivalence-audit; [record](../../docs/proposals/m2/t54-cohort-b-current-proof.md) |
| M2 T55 S1 | 11 | 1992 | none / 0 | none / 0 | closed-renderer-current-equivalence-audit; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S2 | 7 | 1992 | none / 0 | none / 0 | closed-palette-current-equivalence-audit; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S3 | 11 | 1992 | none / 0 | none / 0 | closed-block-metatile-current-equivalence-audit; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S4 | 14 | 1992 | none / 0 | none / 0 | closed-metatile-data-current-equivalence-audit; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S5 | 7 | 1992 | none / 0 | none / 0 | closed-message-stream-current-equivalence-audit; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S6 | 5 | 1992 | none / 0 | none / 0 | closed-current-exact-audit; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S7 | 4 | 1992 | none / 0 | none / 0 | closed-joypad-current-equivalence-audit; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T55 S8 | 8 | 1992 | none / 0 | none / 0 | closed-vram-ppu-current-equivalence-audit; [record](../../docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md) |
| M2 T56 S1 | 14 | 1992 | none / 0 | none / 0 | closed-parser-task-and-scenery-current-equivalence-audit; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S2 | 20 | 1992 | none / 0 | none / 0 | closed-scenery-terrain-and-block-buffer-current-equivalence-audit; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S3 | 32 | 1992 | none / 0 | none / 0 | closed-area-data-decoder-and-attribute-current-equivalence-audit; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S4 | 27 | 1992 | none / 0 | none / 0 | closed-warp-scroll-frenzy-style-pulley-castle-current-equivalence-audit; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S5 | 22 | 1992 | none / 0 | none / 0 | closed-castle-pipe-allocation-question-row-current-equivalence-audit; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T56 S6 | 5 | 1992 | none / 0 | none / 0 | closed-low-question-bridge-flag-balls-current-equivalence-audit; [record](../../docs/proposals/m2/t56-cohort-c-area-parser-current-proof.md) |
| M2 T57 S1 | 26 | 1992 | none / 0 | none / 0 | closed-flagpole-object-row-cannon-current-equivalence-audit; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S2 | 13 | 1992 | none / 0 | none / 0 | closed-staircase-jumpspring-question-block-current-equivalence-audit; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S3 | 16 | 1992 | none / 0 | none / 0 | closed-hole-underpart-block-buffer-current-equivalence-audit; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S4 | 7 | 1992 | none / 0 | none / 0 | closed-loopback-area-pointer-header-current-equivalence-audit; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S5 | 16 | 1992 | none / 0 | none / 0 | closed-world-area-pointer-table-current-equivalence-audit; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S6 | 34 | 1992 | none / 0 | none / 0 | closed-enemy-area-stream-current-equivalence-audit; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T57 S7 | 34 | 1992 | none / 0 | none / 0 | closed-area-object-stream-current-equivalence-audit; [record](../../docs/proposals/m2/t57-cohort-d-renderer-current-proof.md) |
| M2 T58 S1 | 11 | 1992 | none / 0 | none / 0 | closed-current-equivalence-exact; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S2 | 10 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S3 | 23 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S4 | 11 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S5 | 14 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T58 S6 | 10 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md) |
| M2 T59 S1 | 3 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S2 | 12 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S3 | 12 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S4 | 24 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S5 | 6 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S6 | 6 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T59 S7 | 0 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t59-cohort-f-player-motion-current-proof.md) |
| M2 T60 S1 | 5 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S2 | 6 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S3 | 8 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S4 | 5 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S5 | 8 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S6 | 7 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S7 | 7 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S8 | 3 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T60 S9 | 0 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t60-cohort-g-fireball-timer-current-proof.md) |
| M2 T61 S1 | 6 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S2 | 14 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S3 | 10 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S4 | 12 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S5 | 9 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S6 | 10 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S7 | 28 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S8 | 8 | 1992 | none / 0 | none / 0 | admitted-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S9 | 6 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T61 S10 | 26 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md) |
| M2 T62 S1 | 16 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S2 | 19 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S3 | 21 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S4 | 22 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S5 | 18 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S6 | 23 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S7 | 12 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S8 | 25 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S9 | 9 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T62 S10 | 0 | 1992 | none / 0 | none / 0 | closed-cross-chain-closure; [record](../../docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md) |
| M2 T63 S1 | 1 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S2 | 4 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S3 | 3 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S4 | 13 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S5 | 11 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S6 | 5 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S7 | 10 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S8 | 16 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S9 | 9 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S10 | 32 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S11 | 6 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S12 | 16 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S13 | 6 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S14 | 2 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S15 | 2 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S16 | 15 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S17 | 4 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S18 | 3 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S19 | 2 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S20 | 7 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S21 | 3 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S22 | 19 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S23 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S24 | 6 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S25 | 2 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S26 | 26 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S27 | 20 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S28 | 3 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T63 S29 | 0 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/proposals/m2/t63-cohort-j-actor-movement-current-proof.md) |
| M2 T64 S1 | 5 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S2 | 6 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S3 | 11 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S4 | 3 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S5 | 6 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S6 | 34 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S7 | 16 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S8 | 7 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S9 | 11 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S10 | 4 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S11 | 8 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S12 | 14 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S13 | 9 | 1992 | none / 0 | none / 0 | admitted-current-audit; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S14 | 12 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S15 | 10 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S16 | 2 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S17 | 8 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S18 | 8 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S19 | 32 | 1992 | none / 0 | none / 0 | closed-current-audit; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S20 | 4 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S21 | 2 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S22 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S23 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S24 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S25 | 3 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S26 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S27 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S28 | 2 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S29 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S30 | 2 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S31 | 3 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S32 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S33 | 10 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S34 | 1 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S35 | 6 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S36 | 7 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S37 | 8 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S38 | 13 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S39 | 7 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S40 | 17 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S41 | 27 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S42 | 15 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S43 | 18 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S44 | 36 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S45 | 9 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S46 | 19 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S47 | 13 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S48 | 23 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S49 | 7 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S50 | 12 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S51 | 6 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S52 | 26 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S53 | 7 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S54 | 26 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S55 | 22 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S56 | 10 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S57 | 30 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S58 | 19 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T64 S59 | 497 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T64-terrain-collision-current-proof.md) |
| M2 T65 S1 | 14 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S2 | 8 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S3 | 12 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S4 | 9 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S5 | 11 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S6 | 5 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S7 | 6 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S8 | 35 | 1992 | none / 0 | none / 0 | closed-current-exact; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S9 | 22 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S10 | 14 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S11 | 7 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S12 | 6 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S13 | 2 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S14 | 3 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T65 S15 | 154 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T65-block-query-object-output-current-proof.md) |
| M2 T66 S1 | 44 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S2 | 9 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S3 | 11 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S4 | 6 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S5 | 10 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S6 | 3 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T66 S7 | 83 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T66-player-relative-offscreen-current-proof.md) |
| M2 T67 S1 | 22 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S2 | 30 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S3 | 36 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S4 | 11 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S5 | 27 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T67 S6 | 126 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T67-sound-command-current-proof.md) |
| M2 T68 S1 | 17 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S2 | 9 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S3 | 23 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S4 | 21 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S5 | 7 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T68 S6 | 77 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T68-music-data-current-proof.md) |
| M2 T69 S1 | 19 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S2 | 24 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S3 | 5 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S4 | 14 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S5 | 19 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S6 | 18 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S7 | 32 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S8 | 26 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S9 | 29 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S10 | 36 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S11 | 34 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S12 | 27 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S13 | 35 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S14 | 3 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S15 | 22 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T69 S16 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M2-T69-cross-cohort-current-proof.md) |
| M2 T70 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S2 | 29 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S4 | 6 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S5 | 7 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S6 | 9 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S7 | 6 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S8 | 6 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S9 | 10 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S10 | 25 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S11 | 15 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S12 | 10 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S13 | 19 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S14 | 12 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S15 | 17 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S16 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M2 T70 S17 | 1667 | 1992 | none / 0 | none / 0 | closed-with-owner-approved-deferred-verification; [record](../../docs/history/m2/t70-final-current-certification.md) |
| M3 T9 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S5 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T9 S6 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T9-shared-io-and-graphical-output.md) |
| M3 T10 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T10 S5 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T10-shared-io-quick-snapshot.md) |
| M3 T11 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S5 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S6 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T11 S7 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T11-colored-ascii-text-frame-gameplay.md) |
| M3 T12 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T12 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T12 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T12 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T12-authored-text-detail.md) |
| M3 T13 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T13-win32-startup-console-lifecycle.md) |
| M3 T14 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T14-win32-remote-keyboard.md) |
| M3 T15 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T15-presentation-performance.md) |
| M3 T15 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T15-presentation-performance.md) |
| M3 T16 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T16-mushroom-text-colors.md) |
| M3 T17 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T17-text-object-role-audit.md) |
| M3 T18 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T18-window-performance-executable-footprint.md) |
| M3 T18 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T18-window-performance-executable-footprint.md) |
| M3 T19 S1 | 0 | 1992 | none / 0 | none / 0 | suspended; [record](../../docs/proposals/m3/bounded-windows-audio-startup.md) |
| M3 T20 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T20-text-interface-corrections.md) |
| M3 T20 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T20-text-interface-corrections.md) |
| M3 T20 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T20-text-interface-corrections.md) |
| M3 T21 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T21-water-snow-text-colors.md) |
| M3 T21 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T21-water-snow-text-colors.md) |
| M3 T22 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T22-pipe-exit-display-recovery.md) |
| M3 T22 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T22-pipe-exit-display-recovery.md) |
| M3 T23 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T23-princess-text-detail.md) |
| M3 T24 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T24 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T24 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T24 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T24-win32-window-console-integration.md) |
| M3 T25 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T25-dos16-performance-diagnosis.md) |
| M3 T26 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T26-dos16-playable-performance.md) |
| M3 T26 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T26-dos16-playable-performance.md) |
| M3 T27 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S2 | 42 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S4 | 475 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S5 | 1449 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S6 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S7 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T27 S8 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T27-core-ppu-module-boundaries.md) |
| M3 T28 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S5 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T28 S6 | 0 | 1992 | none / 0 | none / 0 | active; [record](../../docs/history/M3-T28-dos-rendering-optimization.md) |
| M3 T29 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T29 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T29 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T29 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T29-win32-usability-regression.md) |
| M3 T30 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T30-ppu-background-performance.md) |
| M3 T30 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T30-ppu-background-performance.md) |
| M3 T31 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S5 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T31 S6 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T31-dos-performance-memory-continuation.md) |
| M3 T32 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S2 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S4 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S5 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S6 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S7 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S8 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
| M3 T32 S9 | 0 | 1992 | none / 0 | none / 0 | active; [record](../../docs/history/M3-T32-rendering-performance-continuation.md) |
