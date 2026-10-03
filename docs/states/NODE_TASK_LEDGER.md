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
| M2 T22 S25 | 5 | `DecTimers`, `DecTimersLoop`, `SkipExpTimer`, `NoDecTimers`, `PauseSkip` |
| M2 T22 S5 | 8 | `FlagpoleObject`, `FlagpoleScoreMods`, `FlagpoleScoreDigits`, `FlagpoleRoutine`, `SkipScore`, `GiveFPScr`, `FPGfx`, `ExitFlagP` |
| M2 T26 S5 | 5 | `SetupVictoryMode`, `PlayerVictoryWalk`, `PerformWalk`, `DontWalk`, `ExitVWalk` |
| M2 T26 S7 | 2 | `VictoryMode`, `AutoPlayer` |
| M2 T27 S1 | 1 | `InitScreen` |
| M2 T27 S2 | 28 | `ClearBuffersDrawIcon`, `TScrClear`, `IncSubtask`, `WriteTopScore`, `IncModeTask_B`, `GameText`, `TopStatusBarLine`, `WorldLivesDisplay`, `TwoPlayerTimeUp`, `OnePlayerTimeUp`, `TwoPlayerGameOver`, `OnePlayerGameOver`, `WarpZoneWelcome`, `LuigiName`, `WarpZoneNumbers`, `GameTextOffsets`, `WriteGameText`, `Chk2Players`, `LdGameText`, `GameTextLoop`, `EndGameText`, `PutLives`, `CheckPlayerName`, `ChkLuigi`, `NameLoop`, `ExitChkName`, `PrintWarpZoneNumbers`, `WarpNumLoop` |
| M2 T28 S1 | 2 | `MetatileGraphics_Low`, `MetatileGraphics_High` |
| M2 T28 S2 | 3 | `ColorRotatePalette`, `BlankPalette`, `Palette3Data` |
| M2 T28 S3 | 11 | `BlockGfxData`, `RemoveCoin_Axe`, `WriteBlankMT`, `ReplaceBlockMetatile`, `DestroyBlockMetatile`, `WriteBlockMetatile`, `UseBOffset`, `MoveVOffset`, `PutBlockMetatile`, `SaveHAdder`, `RemBridge` |
| M2 T28 S4 | 19 | `Palette0_MTiles`, `Palette1_MTiles`, `Palette2_MTiles`, `Palette3_MTiles`, `WaterPaletteData`, `GroundPaletteData`, `UndergroundPaletteData`, `CastlePaletteData`, `DaySnowPaletteData`, `NightSnowPaletteData`, `MushroomPaletteData`, `BowserPaletteData`, `MarioThanksMessage`, `LuigiThanksMessage`, `MushroomRetainerSaved`, `PrincessSaved1`, `PrincessSaved2`, `WorldSelectMessage1`, `WorldSelectMessage2` |
| M2 T28 S5 | 1 | `JumpEngine` |
| M2 T28 S6 | 6 | `WriteBufferToScreen`, `SetupWrites`, `GetLength`, `OutputToVRAM`, `RepeatByte`, `UpdateScreen` |
| M2 T28 S7 | 19 | `StatusBarData`, `StatusBarOffset`, `PrintStatusBarNumbers`, `OutputNumbers`, `SetupNums`, `DigitPLoop`, `ExitOutputN`, `DigitsMathRoutine`, `AddModLoop`, `StoreNewD`, `EraseDMods`, `EraseMLoop`, `BorrowOne`, `CarryOne`, `UpdateTopScore`, `TopScoreCheck`, `GetScoreDiff`, `CopyScore`, `NoTopSc` |
| M2 T28 S8 | 15 | `DefaultSprOffsets`, `Sprite0Data`, `InitializeGame`, `ClrSndLoop`, `InitializeArea`, `ClrTimersLoop`, `StartPage`, `SetSecHard`, `CheckHalfway`, `DoneInitArea`, `PrimaryGameSetup`, `SecondaryGameSetup`, `ClearVRLoop`, `ShufAmtLoop`, `ISpr0Loop` |
| M2 T29 S10 | 10 | `FindEmptyEnemySlot`, `EmptyChkLoop`, `ExitEmptyChk`, `Hole_Water`, `QuestionBlockRow_High`, `QuestionBlockRow_Low`, `Bridge_High`, `Bridge_Middle`, `Bridge_Low`, `FlagBalls_Residual` |
| M2 T29 S2 | 5 | `MusicSelectData`, `GetAreaMusic`, `ChkAreaType`, `StoreMusic`, `ExitGetM` |
| M2 T29 S3 | 11 | `PlayerStarting_X_Pos`, `AltYPosOffset`, `PlayerStarting_Y_Pos`, `PlayerBGPriorityData`, `GameTimerData`, `Entrance_GameTimerSetup`, `ChkStPos`, `SetStPos`, `ChkOverR`, `ChkSwimE`, `SetPESub` |
| M2 T29 S4 | 16 | `HalfwayPageNybbles`, `PlayerLoseLife`, `StillInGame`, `GetHalfway`, `MaskHPNyb`, `SetHalfway`, `GameOverMode`, `SetupGameOver`, `RunGameOver`, `ContinueGame`, `GameIsOn`, `TransposePlayers`, `TransLoop`, `ExTrans`, `DoNothing1`, `DoNothing2` |
| M2 T29 S5 | 13 | `AreaParserTaskHandler`, `DoAPTasks`, `SkipATRender`, `IncrementColumnPos`, `NoColWrap`, `BSceneDataOffsets`, `BackSceneryData`, `BackSceneryMetatiles`, `FSceneDataOffsets`, `ForeSceneryData`, `TerrainMetatiles`, `TerrainRenderBits`, `AreaParserCore` |
| M2 T29 S6 | 1 | `BlockBuffLowBounds` |
| M2 T29 S8 | 20 | `ScrollLockObject_Warp`, `WarpNum`, `ScrollLockObject`, `KillELoop`, `NoKillE`, `FrenzyIDData`, `AreaFrenzy`, `FreCompLoop`, `ExitAFrenzy`, `TreeLedge`, `MidTreeL`, `EndTreeL`, `MushroomLedge`, `EndMushL`, `AllUnder`, `NoUnder`, `PulleyRopeMetatiles`, `PulleyRopeObject`, `RenderPul`, `MushLExit` |
| M2 T29 S9 | 5 | `CastleMetatiles`, `SidePipeShaftData`, `SidePipeTopPart`, `SidePipeBottomPart`, `VerticalPipeData` |
| M2 T30 S1 | 3 | `EndlessRope`, `BalancePlatRope`, `DrawRope` |
| M2 T30 S10 | 6 | `ChkLrgObjLength`, `ChkLrgObjFixedLength`, `LenSet`, `GetLrgObjAttrib`, `GetAreaObjXPosition`, `GetAreaObjYPosition` |
| M2 T30 S13 | 3 | `SetInitNTHigh`, `BlockBufferAddr`, `GetBlockBufferAddr` |
| M2 T30 S14 | 22 | `LoadAreaPointer`, `GetAreaType`, `FindAreaPointer`, `GetAreaDataAddrs`, `StoreFore`, `StoreStyle`, `WorldAddrOffsets`, `AreaAddrOffsets`, `World1Areas`, `World2Areas`, `World3Areas`, `World4Areas`, `World5Areas`, `World6Areas`, `World7Areas`, `World8Areas`, `EnemyAddrHOffsets`, `EnemyDataAddrLow`, `EnemyDataAddrHigh`, `AreaDataHOffsets`, `AreaDataAddrLow`, `AreaDataAddrHigh` |
| M2 T30 S16 | 6 | `L_CastleArea1`, `L_CastleArea2`, `L_CastleArea3`, `L_CastleArea4`, `L_CastleArea5`, `L_CastleArea6` |
| M2 T30 S17 | 22 | `L_GroundArea1`, `L_GroundArea2`, `L_GroundArea3`, `L_GroundArea4`, `L_GroundArea5`, `L_GroundArea6`, `L_GroundArea7`, `L_GroundArea8`, `L_GroundArea9`, `L_GroundArea10`, `L_GroundArea11`, `L_GroundArea12`, `L_GroundArea13`, `L_GroundArea14`, `L_GroundArea15`, `L_GroundArea16`, `L_GroundArea17`, `L_GroundArea18`, `L_GroundArea19`, `L_GroundArea20`, `L_GroundArea21`, `L_GroundArea22` |
| M2 T30 S18 | 3 | `L_UndergroundArea1`, `L_UndergroundArea2`, `L_UndergroundArea3` |
| M2 T30 S19 | 3 | `L_WaterArea1`, `L_WaterArea2`, `L_WaterArea3` |
| M2 T30 S2 | 2 | `CoinMetatileData`, `RowOfCoins` |
| M2 T30 S3 | 7 | `C_ObjectRow`, `C_ObjectMetatile`, `CastleBridgeObj`, `AxeObj`, `ChainObj`, `EmptyBlock`, `ColObj` |
| M2 T30 S4 | 10 | `SolidBlockMetatiles`, `BrickMetatiles`, `RowOfBricks`, `DrawBricks`, `RowOfSolidBlocks`, `GetRow`, `DrawRow`, `ColumnOfBricks`, `ColumnOfSolidBlocks`, `GetRow2` |
| M2 T30 S5 | 3 | `BulletBillCannon`, `SetupCannon`, `StrCOffset` |
| M2 T30 S6 | 4 | `StaircaseHeightData`, `StaircaseRowData`, `StaircaseObject`, `NextStair` |
| M2 T30 S7 | 1 | `Jumpspring` |
| M2 T30 S8 | 8 | `Hidden1UpBlock`, `QuestionBlock`, `BrickWithCoins`, `BrickWithItem`, `BWithL`, `DrawQBlk`, `GetAreaObjectID`, `ExitDecBlock` |
| M2 T30 S9 | 4 | `HoleMetatiles`, `Hole_Empty`, `StrWOffset`, `NoWhirlP` |
| M2 T31 S1 | 1 | `GameCoreRoutine` |
| M2 T31 S2 | 36 | `GameEngine`, `ProcELoop`, `NoChgMus`, `CycleTwo`, `ClrPlrPal`, `SaveAB`, `UpdScrollVar`, `RunParser`, `ExitEng`, `WarpZoneObject`, `ProcessWhirlpools`, `NextWh`, `ExitWh`, `LeftWh`, `SetPWh`, `CannonBitmasks`, `ProcessCannons`, `ThreeSChk`, `FireCannon`, `Chk_BB`, `Next3Slt`, `ExCannon`, `BulletBillXSpdData`, `BulletBillHandler`, `SetupBB`, `ChkDSte`, `BBFly`, `RunBBSubs`, `KillBB`, `DoEnemySideCheck`, `SdeCLoop`, `NextSdeC`, `ExESdeC`, `SubtEnemyYPos`, `EnemyJump`, `DoSide` |
| M2 T31 S3 | 10 | `ScrollHandler`, `ChkNearMid`, `ScrollScreen`, `InitScrlAmt`, `ChkPOffscr`, `KeepOnscr`, `InitPlatScrl`, `X_SubtracterData`, `OffscrJoypadBitsData`, `GetScreenPosition` |
| M2 T31 S4 | 9 | `PlayerEntrance`, `ChkBehPipe`, `IntroEntr`, `EntrMode2`, `VineEntr`, `OffVine`, `PlayerRdy`, `ExitEntr`, `AutoControlPlayer` |
| M2 T32 S1 | 11 | `PlayerCtrlRoutine`, `DisJoyp`, `SaveJoyp`, `SizeChk`, `ChkMoveDir`, `SetMoveDir`, `PlayerSubs`, `HoleDie`, `ChkHoleX`, `ExitCtrl`, `CloudExit` |
| M2 T32 S2 | 11 | `Vine_AutoClimb`, `AutoClimb`, `SetEntr`, `VerticalPipeEntry`, `MovePlayerYAxis`, `SideExitPipeEntry`, `ChgAreaPipe`, `ChgAreaMode`, `ExitCAPipe`, `EnterSidePipe`, `RightPipe` |
| M2 T32 S3 | 14 | `PlayerChangeSize`, `EndChgSize`, `ExitChgSize`, `PlayerInjuryBlink`, `ExitBlink`, `InitChangeSize`, `ExitBoth`, `PlayerDeath`, `DonePlayerTask`, `PlayerFireFlower`, `CyclePlayerPalette`, `ResetPalFireFlower`, `ResetPalStar`, `ExitDeath` |
| M2 T32 S4 | 10 | `FlagpoleSlide`, `SlidePlayer`, `NoFPObj`, `Hidden1UpCoinAmts`, `PlayerEndLevel`, `ChkStop`, `InCastle`, `RdyNextA`, `NextArea`, `ExitNA` |
| M2 T33 S1 | 14 | `PlayerMovementSubs`, `SetCrouch`, `ProcMove`, `NoMoveSub`, `OnGroundStateSub`, `GndMove`, `FallingSub`, `JumpSwimSub`, `DumpFall`, `ProcSwim`, `LRWater`, `LRAir`, `JSMove`, `ExitMov1` |
| M2 T33 S2 | 8 | `ClimbAdderLow`, `ClimbAdderHigh`, `ClimbingSub`, `MoveOnVine`, `ClimbFD`, `CSetFDir`, `ExitCSub`, `InitCSTimer` |
| M2 T33 S3 | 28 | `JumpMForceData`, `FallMForceData`, `PlayerYSpdData`, `InitMForceData`, `MaxLeftXSpdData`, `MaxRightXSpdData`, `FrictionData`, `Climb_Y_SpeedData`, `Climb_Y_MForceData`, `PlayerPhysicsSub`, `ProcClimb`, `SetCAnim`, `CheckForJumping`, `NoJump`, `ProcJumping`, `InitJS`, `ChkWtr`, `GetYPhy`, `PJumpSnd`, `SJumpSnd`, `X_Physics`, `ProcPRun`, `ChkRFast`, `FastXSp`, `SetRTmr`, `GetXPhy`, `GetXPhy2`, `ExitPhy` |
| M2 T33 S4 | 12 | `PlayerAnimTmrData`, `GetPlayerAnimSpeed`, `ChkSkid`, `SetRunSpd`, `ProcSkid`, `SetAnimSpd`, `ImposeFriction`, `JoypFrict`, `LeftFrict`, `RghtFrict`, `XSpdSign`, `SetAbsSpd` |
| M2 T34 S1 | 5 | `ProcFireball_Bubble`, `ProcFireballs`, `ProcAirBubbles`, `BublLoop`, `BublExit` |
| M2 T34 S2 | 4 | `RunFB`, `EraseFB`, `NoFBall`, `FireballExplosion` |
| M2 T35 S1 | 8 | `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`, `Y_Bubl`, `ExitBubl`, `Bubble_MForceData`, `BubbleTimerData` |
| M2 T35 S2 | 4 | `RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer` |
| M2 T35 S3 | 7 | `Jumpspring_Y_PosData`, `JumpspringHandler`, `DownJSpr`, `PosJSpr`, `BounceJS`, `DrawJSpr`, `ExJSpring` |
| M2 T35 S4 | 3 | `Setup_Vine`, `NextVO`, `VineHeightData` |
| M2 T36 S1 | 6 | `VineObjectHandler`, `RunVSubs`, `VDrawLoop`, `KillVine`, `WrCMTile`, `ExitVH` |
| M2 T36 S2 | 10 | `HammerEnemyOfsData`, `HammerXSpdData`, `SpawnHammerObj`, `SetMOfs`, `NoHammer`, `ProcHammerObj`, `SetHSpd`, `SetHPos`, `RunAllH`, `RunHSubs` |
| M2 T36 S3 | 6 | `CoinBlock`, `SetupJumpCoin`, `JCoinC`, `FindEmptyMiscSlot`, `FMiscLoop`, `UseMiscS` |
| M2 T36 S4 | 6 | `MiscObjectsCore`, `MiscLoop`, `ProcJumpCoin`, `JCoinRun`, `RunJCSubs`, `MiscLoopBack` |
| M2 T36 S5 | 8 | `CoinTallyOffsets`, `ScoreOffsets`, `StatusBarNybbles`, `GiveOneCoin`, `CoinPoints`, `GetSBNybbles`, `UpdateNumber`, `NoZSup` |
| M2 T36 S6 | 4 | `SetupPowerUp`, `PwrUpJmp`, `StrType`, `PutBehind` |
| M2 T37 S1 | 6 | `PowerUpObjHandler`, `ShroomM`, `GrowThePowerUp`, `ChkPUSte`, `RunPUSubs`, `ExitPUp` |
| M2 T37 S2 | 13 | `BlockYPosAdderData`, `PlayerHeadCollision`, `DBlockSte`, `ChkBrick`, `StartBTmr`, `ContBTmr`, `PutOldMT`, `PutMTileB`, `SmallBP`, `BigBP`, `Unbreak`, `InvOBit`, `InitBlock_XY_Pos` |
| M2 T37 S3 | 11 | `BumpBlock`, `BlockCode`, `MushFlowerBlock`, `StarBlock`, `ExtraLifeMushBlock`, `VineBlock`, `ExitBlockChk`, `BrickQBlockMetatiles`, `BlockBumpedChk`, `BumpChkLoop`, `MatchBump` |
| M2 T37 S4 | 4 | `BrickShatter`, `CheckTopOfBlock`, `TopEx`, `SpawnBrickChunks` |
| M2 T37 S5 | 5 | `BlockObjectsCore`, `ChkTop`, `BouncingBlockHandler`, `KillBlock`, `UpdSte` |
| M2 T37 S6 | 3 | `BlockObjMT_Updater`, `UpdateLoop`, `NextBUpd` |
| M2 T37 S7 | 6 | `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `SaveXSpd`, `UseAdder`, `ExXMove` |
| M2 T37 S8 | 14 | `MovePlayerVertically`, `NoJSChk`, `MoveD_EnemyVertically`, `MoveFallingPlatform`, `ContVMove`, `MoveRedPTroopaDown`, `MoveRedPTroopaUp`, `MoveRedPTroopa`, `MoveDropPlatform`, `MoveEnemySlowVert`, `SetMdMax`, `MoveJ_EnemyVertically`, `SetHiMax`, `SetXMoveAmt` |
| M2 T37 S9 | 12 | `MaxSpdBlockData`, `ResidualGravityCode`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `MovePlatformDown`, `MovePlatformUp`, `SetDplSpd`, `RedPTroopaGrav`, `ImposeGravity`, `AlterYP`, `ChkUpM`, `ExVMove` |
| M2 T38 S1 | 17 | `AreaDataOfsLoopback`, `EnemiesAndLoopsCore`, `ChkAreaTsk`, `ChkBowserF`, `ExitELCore`, `LoopCmdWorldNumber`, `LoopCmdPageNumber`, `LoopCmdYPosition`, `ExecGameLoopback`, `ProcLoopCommand`, `FindLoop`, `IncMLoop`, `WrongChk`, `DoLpBack`, `InitMLp`, `InitLCmd`, `ChkEnemyFrenzy` |
| M2 T38 S2 | 19 | `ProcessEnemyData`, `CheckEndofBuffer`, `CheckRightBounds`, `CheckPageCtrlRow`, `PositionEnemyObj`, `CheckRightExtBounds`, `CheckForEnemyGroup`, `BuzzyBeetleMutate`, `StrID`, `CheckFrenzyBuffer`, `StrFre`, `InitEnemyObject`, `ExEPar`, `DoGroup`, `ParseRow0e`, `NotUse`, `CheckThreeBytes`, `Inc3B`, `Inc2B` |
| M2 T38 S3 | 3 | `CheckpointEnemyID`, `InitEnemyRoutines`, `NoInitCode` |
| M2 T38 S4 | 23 | `InitGoomba`, `InitPodoboo`, `InitRetainerObj`, `NormalXSpdData`, `InitNormalEnemy`, `GetESpd`, `SetESpd`, `InitRedKoopa`, `HBroWalkingTimerData`, `InitHammerBro`, `InitHorizFlySwimEnemy`, `InitBloober`, `SmallBBox`, `InitRedPTroopa`, `GetCent`, `TallBBox`, `SetBBox`, `InitVStf`, `InitBulletBill`, `InitCheepCheep`, `InitLakitu`, `SetupLakitu`, `KillLakitu` |
| M2 T38 S5 | 13 | `PRDiffAdjustData`, `LakituAndSpinyHandler`, `ChkLak`, `ChkNoEn`, `CreateL`, `RetEOfs`, `ExLSHand`, `CreateSpiny`, `DifLoop`, `UsePosv`, `SetSpSpd`, `SpinyRte`, `ChpChpEx` |
| M2 T38 S6 | 4 | `FirebarSpinSpdData`, `FirebarSpinDirData`, `InitLongFirebar`, `InitShortFirebar` |
| M2 T38 S7 | 10 | `FlyCCXPositionData`, `FlyCCXSpeedData`, `FlyCCTimerData`, `InitFlyingCheepCheep`, `MaxCC`, `GSeed`, `RSeed`, `D2XPos1`, `D2XPos2`, `FinCCSt` |
| M2 T39 S1 | 12 | `InitBowser`, `DuplicateEnemyObj`, `FSLoop`, `FlmEx`, `FlameYPosData`, `FlameYMFAdderData`, `InitBowserFlame`, `SetFrT`, `PutAtRightExtent`, `SpawnFromMouth`, `SetMF`, `FinishFlame` |
| M2 T39 S2 | 5 | `FireworksXPosData`, `FireworksYPosData`, `InitFireworks`, `StarFChk`, `ExitFWk` |
| M2 T39 S3 | 14 | `Bitmasks`, `Enemy17YPosData`, `SwimCC_IDData`, `BulletBillCheepCheep`, `ChkW2`, `Get17ID`, `Set17ID`, `GetRBit`, `ChkRBit`, `AddFBit`, `DoBulletBills`, `BB_SLoop`, `ExF17`, `FireBulletBill` |
| M2 T39 S4 | 8 | `HandleGroupEnemies`, `PullID`, `SnglID`, `SetYGp`, `CntGrp`, `GrLoop`, `GSltLp`, `NextED` |
| M2 T39 S5 | 9 | `InitPiranhaPlant`, `InitEnemyFrenzy`, `NoFrenzyCode`, `EndFrenzy`, `LakituChk`, `NextFSlot`, `InitJumpGPTroopa`, `TallBBox2`, `SetBBox2` |
| M2 T39 S6 | 20 | `InitBalPlatform`, `AlignP`, `SetBPA`, `InitDropPlatform`, `InitHoriPlatform`, `InitVertPlatform`, `SetYO`, `CommonPlatCode`, `SPBBox`, `CasPBB`, `LargeLiftUp`, `LargeLiftDown`, `LargeLiftBBox`, `PlatLiftUp`, `PlatLiftDown`, `CommonSmallLift`, `PlatPosDataLow`, `PlatPosDataHigh`, `PosPlatform`, `EndOfEnemyInitCode` |
| M2 T39 S7 | 4 | `RunEnemyObjectsCore`, `JmpEO`, `NoRunCode`, `RunRetainerObj` |
| M2 T39 S8 | 4 | `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode` |
| M2 T39 S9 | 7 | `RunBowserFlame`, `RunFirebarObj`, `RunSmallPlatform`, `RunLargePlatform`, `SkipPT`, `LargePlatformSubroutines`, `EraseEnemyObject` |
| M2 T40 S1 | 2 | `MovePodoboo`, `PdbM` |
| M2 T40 S10 | 16 | `LakituDiffAdj`, `MoveLakitu`, `ChkLS`, `Fr12S`, `LdLDa`, `SetLSpd`, `SetLMov`, `PlayerLakituDiff`, `ChkLakDif`, `SetLMovD`, `ChkPSpeed`, `ChkSpinyO`, `ChkEmySpd`, `SubDifAdj`, `SPixelLak`, `ExMoveLak` |
| M2 T40 S2 | 24 | `HammerThrowTmrData`, `XSpeedAdderData`, `RevivedXSpeed`, `ProcHammerBro`, `ChkJH`, `DecHT`, `HammerBroJumpLData`, `HammerBroJumpCode`, `SetHJ`, `HJump`, `MoveHammerBroXDir`, `Shimmy`, `SetShim`, `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`, `SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`, `ChkKillGoomba`, `NKGmba` |
| M2 T40 S3 | 5 | `MoveJumpingEnemy`, `ProcMoveRedPTroopa`, `NoIncPT`, `MoveRedPTUpOrDown`, `MovPTDwn` |
| M2 T40 S4 | 10 | `MoveFlyGreenPTroopa`, `YSway`, `NoMGPT`, `XMoveCntr_GreenPTroopa`, `XMoveCntr_Platform`, `NoIncXM`, `IncPXM`, `DecSeXM`, `MoveWithXMCntrs`, `XMRight` |
| M2 T40 S5 | 16 | `BlooberBitmasks`, `MoveBloober`, `FBLeft`, `SBMDir`, `BlooberSwim`, `SwimX`, `LeftSwim`, `MoveDefeatedBloober`, `ProcSwimmingB`, `BSwimE`, `SlowSwim`, `NoSSw`, `ChkForFloatdown`, `Floatdown`, `NoFD`, `ChkNearPlayer` |
| M2 T40 S6 | 2 | `MoveBulletBill`, `NotDefB` |
| M2 T40 S7 | 7 | `SwimCCXMoveData`, `MoveSwimmingCheepCheep`, `CCSwim`, `CCSwimUpwards`, `ChkSwimYPos`, `YPDiff`, `ExSwCC` |
| M2 T40 S8 | 32 | `FirebarPosLookupTbl`, `FirebarMirrorData`, `FirebarTblOffsets`, `FirebarYPos`, `ProcFirebar`, `SusFbar`, `SkpFSte`, `SetupGFB`, `SetMFbar`, `DrawFbar`, `NextFbar`, `SkipFBar`, `DrawFirebar_Collision`, `AddHA`, `SubtR1`, `ChkFOfs`, `VAHandl`, `AddVA`, `SetVFbr`, `FirebarCollision`, `AdjSm`, `BigJp`, `FBCLoop`, `ChkVFBD`, `ChkFBCl`, `Chk2Ofs`, `ChgSDir`, `SetSDir`, `NoColFB`, `GetFirebarPosition`, `GetHAdder`, `GetVAdder` |
| M2 T40 S9 | 6 | `PRandomSubtracter`, `FlyCCBPriority`, `MoveFlyingCheepCheep`, `FlyCC`, `AddCCF`, `BPGet` |
| M2 T41 S1 | 6 | `BridgeCollapseData`, `BridgeCollapse`, `SetM2`, `MoveD_Bowser`, `RemoveBridge`, `NoBFall` |
| M2 T41 S10 | 6 | `YMovingPlatform`, `SkipIY`, `ChkYCenterPos`, `YMDown`, `ChkYPCollision`, `ExYPl` |
| M2 T41 S11 | 9 | `XMovingPlatform`, `PositionPlayerOnHPlat`, `PPHSubt`, `SetPVar`, `ExXMP`, `DropPlatform`, `ExDPl`, `RightPlatform`, `ExRPl` |
| M2 T41 S12 | 5 | `MoveLargeLiftPlat`, `MoveSmallPlatform`, `MoveLiftPlatforms`, `ChkSmallPlatCollision`, `ExLiftP` |
| M2 T41 S13 | 5 | `OffscreenBoundsCheck`, `LimitB`, `ExtendLB`, `TooFar`, `ExScrnBd` |
| M2 T41 S2 | 19 | `PRandomRange`, `RunBowser`, `KillAllEnemies`, `KillLoop`, `BowserControl`, `ChkMouth`, `FeetTmr`, `ResetMDr`, `B_FaceP`, `GetPRCmp`, `GetDToO`, `CompDToO`, `HammerChk`, `SetHmrTmr`, `SkipToFB`, `MakeBJump`, `ChkFireB`, `SpawnFBr`, `SetFBTmr` |
| M2 T41 S3 | 4 | `BowserGfxHandler`, `CopyFToR`, `ExBGfxH`, `ProcessBowserHalf` |
| M2 T41 S4 | 12 | `FlameTimerData`, `SetFlameTimer`, `ExFl`, `ProcBowserFlame`, `SFlmX`, `SetGfxF`, `FlmeAt`, `DrawFlameLoop`, `M3FOfs`, `M2FOfs`, `M1FOfs`, `ExFlmeD` |
| M2 T41 S5 | 3 | `RunFireworks`, `SetupExpl`, `FireworksSoundScore` |
| M2 T41 S6 | 20 | `StarFlagYPosAdder`, `StarFlagXPosAdder`, `StarFlagTileData`, `RunStarFlagObj`, `GameTimerFireworks`, `SetFWC`, `IncrementSFTask1`, `StarFlagExit`, `AwardGameTimerPoints`, `NoTTick`, `EndAreaPoints`, `ELPGive`, `RaiseFlagSetoffFWorks`, `SetoffF`, `DrawStarFlag`, `DSFLoop`, `DrawFlagSetTimer`, `IncrementSFTask2`, `DelayToAreaEnd`, `StarFlagExit2` |
| M2 T41 S7 | 6 | `MovePiranhaPlant`, `ChkPlayerNearPipe`, `ReversePlantSpeed`, `SetupToMovePPlant`, `RiseFallPiranhaPlant`, `PutinPipe` |
| M2 T41 S8 | 2 | `FirebarSpin`, `SpinCounterClockwise` |
| M2 T41 S9 | 26 | `BalancePlatform`, `DoBPl`, `CheckBalPlatform`, `ChkForFall`, `MakePlatformFall`, `ChkOtherForFall`, `ChkToMoveBalPlat`, `ColFlg`, `PlatUp`, `PlatSt`, `PlatDn`, `DoOtherPlatform`, `DrawEraseRope`, `EraseR1`, `OtherRope`, `EraseR2`, `EndRp`, `ExitRp`, `SetupPlatformRope`, `GetLRp`, `GetHRp`, `ExPRp`, `InitPlatformFall`, `StopPlatforms`, `PlatformFall`, `ExPF` |
| M2 T42 S1 | 6 | `FireballEnemyCollision`, `FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`, `NoFToECol`, `ExitFBallEnemy` |
| M2 T42 S2 | 11 | `BowserIdentities`, `HandleEnemyFBallCol`, `ChkBuzzyBeetle`, `HurtBowser`, `SetDBSte`, `ChkOtherEnemies`, `ShellOrBlockDefeat`, `StnE`, `GoombaPoints`, `EnemySmackScore`, `ExHCF` |
| M2 T42 S3 | 3 | `PlayerHammerCollision`, `ClHCol`, `ExPHC` |
| M2 T42 S4 | 6 | `HandlePowerUpCollision`, `Shroom_Flower_PUp`, `SetFor1Up`, `UpToSuper`, `UpToFiery`, `NoPUp` |
| M2 T42 S5 | 34 | `ResidualXSpdData`, `KickedShellXSpdData`, `DemotedKoopaXSpdData`, `PlayerEnemyCollision`, `NoPECol`, `CheckForPUpCollision`, `EColl`, `KickedShellPtsData`, `HandlePECollisions`, `KSPts`, `ExPEC`, `ChkForPlayerInjury`, `ChkInj`, `ChkETmrs`, `TInjE`, `InjurePlayer`, `ForceInjury`, `SetKRout`, `SetPRout`, `ExInjColRoutines`, `KillPlayer`, `StompedEnemyPtsData`, `EnemyStomped`, `EnemyStompedPts`, `ChkForDemoteKoopa`, `RevivalRateData`, `HandleStompedShellE`, `SBnce`, `ChkEnemyFaceRight`, `LInj`, `EnemyFacePlayer`, `SFcRt`, `SetupFloateyNumber`, `ExSFN` |
| M2 T42 S6 | 16 | `SetBitsMask`, `ClearBitsMask`, `EnemiesCollision`, `ECLoop`, `YesEC`, `NoEnemyCollision`, `ReadyNextEnemy`, `ExitECRoutine`, `ProcEnemyCollisions`, `ShellCollisions`, `ExitProcessEColl`, `ProcSecondEnemyColl`, `MoveEOfs`, `EnemyTurnAround`, `RXSpd`, `ExTA` |
| M2 T42 S7 | 14 | `LargePlatformCollision`, `ChkForPlayerC_LargeP`, `ExLPC`, `SmallPlatformCollision`, `ChkSmallPlatLoop`, `MoveBoundBox`, `ExSPC`, `ProcSPlatCollisions`, `ProcLPlatCollisions`, `ChkForTopCollision`, `SetCollisionFlag`, `PlatformSideCollisions`, `SideC`, `NoSideC` |
| M2 T42 S8 | 4 | `PlayerPosSPlatData`, `PositionPlayerOnS_Plat`, `PositionPlayerOnVPlat`, `ExPlPos` |
| M2 T42 S9 | 4 | `CheckPlayerVertical`, `ExCPV`, `GetEnemyBoundBoxOfs`, `GetEnemyBoundBoxOfsArg` |
| M2 T43 S1 | 31 | `PlayerBGUpperExtent`, `PlayerBGCollision`, `SetFallS`, `SetPSte`, `ChkOnScr`, `ExPBGCol`, `ChkCollSize`, `GBBAdr`, `HeadChk`, `SolidOrClimb`, `NYSpd`, `DoFootCheck`, `AwardTouchedCoin`, `ChkFootMTile`, `ContChk`, `LandPlyr`, `InitSteP`, `DoPlayerSideCheck`, `SideCheckLoop`, `BHalf`, `ExSCH`, `CheckSideMTiles`, `ContSChk`, `ChkPBtm`, `PipeDwnS`, `PlyrPipe`, `SetCATmr`, `ChkGERtn`, `StopPlayerMove`, `ExCSM`, `AreaChangeTimerData` |
| M2 T43 S10 | 9 | `ChkForBump_HammerBroJ`, `NoBump`, `InvEnemyDir`, `PlayerEnemyDiff`, `EnemyLanding`, `HammerBroBGColl`, `KillEnemyAboveBlock`, `UnderHammerBro`, `NoUnderHammerBro` |
| M2 T43 S11 | 3 | `ChkUnderEnemy`, `ChkForNonSolids`, `NSFnd` |
| M2 T43 S12 | 3 | `FireballBGCollision`, `ClearBounceFlag`, `InitFireballExplode` |
| M2 T43 S13 | 11 | `BoundBoxCtrlData`, `GetFireballBoundBox`, `GetMiscBoundBox`, `FBallB`, `GetEnemyBoundBox`, `SmallPlatformBoundBox`, `GetMaskedOffScrBits`, `CMBits`, `LargePlatformBoundBox`, `SetupEOffsetFBBox`, `MoveBoundBoxOffscreen` |
| M2 T43 S14 | 7 | `BoundingBoxCore`, `CheckRightScreenBBox`, `SORte`, `NoOfs`, `CheckLeftScreenBBox`, `SOLft`, `NoOfs2` |
| M2 T43 S15 | 7 | `PlayerCollisionCore`, `SprObjectCollisionCore`, `CollisionCoreLoop`, `SecondBoxVerticalChk`, `FirstBoxGreater`, `NoCollisionFound`, `CollisionFound` |
| M2 T43 S2 | 3 | `HandleCoinMetatile`, `HandleAxeMetatile`, `ErACM` |
| M2 T43 S3 | 14 | `ClimbXPosAdder`, `ClimbPLocAdder`, `FlagpoleYPosData`, `HandleClimbing`, `ExHC`, `ChkForFlagpole`, `FlagpoleCollision`, `ChkFlagpoleYPosLoop`, `MtchF`, `RunFR`, `VineCollision`, `PutPlayerOnVine`, `SetVXPl`, `ExPVne` |
| M2 T43 S4 | 7 | `ChkInvisibleMTiles`, `ExCInvT`, `ChkForLandJumpSpring`, `ExCJSp`, `ChkJumpspringMetatiles`, `JSFnd`, `NoJSFnd` |
| M2 T43 S5 | 3 | `HandlePipeEntry`, `GetWNum`, `ExPipeE` |
| M2 T43 S6 | 5 | `ImpedePlayerMove`, `RImpd`, `NXSpd`, `PlatF`, `ExIPM` |
| M2 T43 S7 | 8 | `SolidMTileUpperExt`, `CheckForSolidMTiles`, `ClimbMTileUpperExt`, `CheckForClimbMTiles`, `CheckForCoinMTiles`, `CoinSd`, `GetMTileAttrib`, `ExEBG` |
| M2 T43 S8 | 18 | `EnemyBGCStateData`, `EnemyBGCXSpdData`, `EnemyToBGCollisionDet`, `DoIDCheckBGColl`, `HBChk`, `CInvu`, `YesIn`, `NoEToBGCollision`, `HandleEToBGCollision`, `GiveOEPoints`, `ChkToStunEnemies`, `Demote`, `SetStun`, `SetWYSpd`, `SetNotW`, `ChkBBill`, `NoCDirF`, `ExEBGChk` |
| M2 T43 S9 | 14 | `LandEnemyProperly`, `SChkA`, `ChkLandedEnemyState`, `SetForStn`, `ExSteChk`, `ProcEnemyDirection`, `InvtD`, `CNwCDir`, `LandEnemyInitState`, `NMovShellFallBit`, `ChkForRedKoopa`, `Chk2MSBSt`, `GetSteFromD`, `SetD6Ste` |
| M2 T44 S1 | 14 | `BlockBufferChk_Enemy`, `ResidualMiscObjectCode`, `BlockBufferChk_FBall`, `ResJmpM`, `BBChk_E`, `BlockBufferAdderData`, `BlockBuffer_X_Adder`, `BlockBuffer_Y_Adder`, `BlockBufferColli_Feet`, `BlockBufferColli_Head`, `BlockBufferColli_Side`, `BlockBufferCollision`, `RetXC`, `RetYC` |
| M2 T44 S2 | 6 | `VineYPosAdder`, `DrawVine`, `VineTL`, `SkpVTop`, `ChkFTop`, `NextVSp` |
| M2 T44 S3 | 14 | `SixSpriteStacker`, `StkLp`, `FirstSprXPos`, `FirstSprYPos`, `SecondSprXPos`, `SecondSprYPos`, `FirstSprTilenum`, `SecondSprTilenum`, `HammerSprAttrib`, `DrawHammer`, `ForceHPose`, `GetHPose`, `RenderH`, `NoHOffscr` |
| M2 T44 S4 | 9 | `FlagpoleScoreNumTiles`, `FlagpoleGfxHandler`, `ChkFlagOffscreen`, `MoveSixSpritesOffscreen`, `DumpSixSpr`, `DumpFourSpr`, `DumpThreeSpr`, `DumpTwoSpr`, `ExitDumpSpr` |
| M2 T44 S5 | 10 | `ShrinkPlatform`, `SetLast2Platform`, `SetPlatformTilenum`, `SChk2`, `SChk3`, `SChk4`, `SChk5`, `SChk6`, `SLChk`, `ExDLPl` |
| M2 T44 S6 | 5 | `DrawFloateyNumber_Coin`, `NotRsNum`, `JumpingCoinTiles`, `JCoinGfxHandler`, `ExJCGfx` |
| M2 T44 S7 | 6 | `PowerUpGfxTable`, `PowerUpAttributes`, `DrawPowerUp`, `PUpDrawLoop`, `FlipPUpRightSide`, `PUpOfs` |
| M2 T44 S8 | 44 | `EnemyGraphicsTable`, `EnemyGfxTableOffsets`, `EnemyAttributeData`, `EnemyAnimTimingBMask`, `JumpspringFrameOffsets`, `EnemyGfxHandler`, `CheckForRetainerObj`, `CheckForBulletBillCV`, `SBBAt`, `CheckForJumpspring`, `CheckForPodoboo`, `CheckBowserGfxFlag`, `SBwsrGfxOfs`, `CheckForGoomba`, `GmbaAnim`, `CheckBowserFront`, `ChkFrontSte`, `FlipBowserOver`, `DrawBowser`, `CheckBowserRear`, `ChkRearSte`, `CheckForSpiny`, `NotEgg`, `CheckForLakitu`, `NoLAFr`, `CheckUpsideDownShell`, `CheckRightSideUpShell`, `CheckForDefdGoomba`, `CheckForHammerBro`, `CheckForBloober`, `CheckToAnimateEnemy`, `CheckForSecondFrame`, `CheckAnimationStop`, `CheckDefeatedState`, `DrawEnemyObject`, `SkipToOffScrChk`, `CheckForVerticalFlip`, `FlipEnemyVertically`, `CheckForESymmetry`, `ContES`, `ESRtnr`, `SpnySC`, `MirrorEnemyGfx`, `EggExc` |
| M2 T45 S1 | 13 | `CheckToMirrorLakitu`, `NVFLak`, `CheckToMirrorJSpring`, `SprObjectOffscrChk`, `LcChk`, `Row3C`, `Row23C`, `AllRowC`, `ExEGHandler`, `DrawEnemyObjRow`, `DrawOneSpriteRow`, `MoveESprRowOffscreen`, `MoveESprColOffscreen` |
| M2 T45 S2 | 14 | `DefaultBlockObjTiles`, `DrawBlock`, `DBlkLoop`, `ChkRep`, `SetBFlip`, `BlkOffscr`, `PullOfsB`, `ChkLeftCo`, `MoveColOffscreen`, `ExDBlk`, `DrawBrickChunks`, `DChunks`, `ChnkOfs`, `ExBCDr` |
| M2 T45 S3 | 7 | `DrawFireball`, `DrawFirebar`, `FireA`, `ExplosionTiles`, `DrawExplosion_Fireball`, `DrawExplosion_Fireworks`, `KillFireBall` |
| M2 T45 S4 | 6 | `DrawSmallPlatform`, `TopSP`, `BotSP`, `SOfs`, `SOfs2`, `ExSPl` |
| M2 T45 S5 | 5 | `DrawBubble`, `ExDBub`, `PlayerGfxTblOffsets`, `PlayerGraphicsTable`, `SwimKickTileNum` |
| M2 T46 S1 | 13 | `PlayerGfxHandler`, `CntPl`, `SwimKT`, `BigKTS`, `ExPGH`, `FindPlayerAction`, `DoChangeSize`, `PlayerKilled`, `PlayerGfxProcessing`, `SUpdR`, `PlayerOffscreenChk`, `PROfsLoop`, `NPROffscr` |
| M2 T46 S2 | 5 | `IntermediatePlayerData`, `DrawPlayer_Intermediate`, `PIntLoop`, `RenderPlayerSub`, `DrawPlayerLoop` |
| M2 T46 S3 | 13 | `ProcessPlayerAction`, `ProcOnGroundActs`, `NonAnimatedActs`, `ActionFalling`, `ActionWalkRun`, `ActionClimbing`, `ActionSwimming`, `GetCurrentAnimOffset`, `FourFrameExtent`, `ThreeFrameExtent`, `AnimationControl`, `SetAnimC`, `ExAnimC` |
| M2 T46 S4 | 12 | `GetGfxOffsetAdder`, `SzOfs`, `ChangeSizeOffsetAdder`, `HandleChangeSize`, `CSzNext`, `GorSLog`, `GetOffsetFromAnimCtrl`, `ShrinkPlayer`, `ShrPlF`, `ChkForPlayerAttrib`, `KilledAtt`, `C_S_IGAtt` |
| M2 T47 S1 | 1 | `ExPlyrAt` |
| M2 T47 S2 | 9 | `RelativePlayerPosition`, `RelativeBubblePosition`, `RelativeFireballPosition`, `RelWOfs`, `RelativeMiscPosition`, `RelativeEnemyPosition`, `RelativeBlockPosition`, `VariableObjOfsRelPos`, `GetObjRelativePosition` |
| M2 T47 S3 | 1 | `GetPlayerOffscreenBits` |
| M2 T47 S4 | 26 | `GetFireballOffscreenBits`, `GetBubbleOffscreenBits`, `GetMiscOffscreenBits`, `ObjOffsetData`, `GetProperObjOffset`, `GetEnemyOffscreenBits`, `GetBlockOffscreenBits`, `SetOffscrBitsOffset`, `GetOffScreenBitsSet`, `RunOffscrBitsSubs`, `XOffscreenBitsData`, `DefaultXOnscreenOfs`, `GetXOffscreenBits`, `XOfsLoop`, `XLdBData`, `ExXOfsBS`, `YOffscreenBitsData`, `DefaultYOnscreenOfs`, `HighPosUnitData`, `GetYOffscreenBits`, `YOfsLoop`, `YLdBData`, `ExYOfsBS`, `DividePDiff`, `SetOscrO`, `ExDivPD` |
| M2 T47 S5 | 3 | `DrawSpriteObject`, `NoHFlip`, `SetHFAt` |
| M2 T48 S1 | 13 | `SoundEngine`, `SndOn`, `InPause`, `PTone1F`, `ContPau`, `PTone2F`, `PTRegC`, `DecPauC`, `SkipPIn`, `RunSoundSubroutines`, `SkipSoundSubroutines`, `NoIncDAC`, `StrWave` |
| M2 T48 S2 | 9 | `Dump_Squ1_Regs`, `PlaySqu1Sfx`, `SetFreq_Squ1`, `Dump_Freq_Regs`, `NoTone`, `Dump_Sq2_Regs`, `PlaySqu2Sfx`, `SetFreq_Squ2`, `SetFreq_Tri` |
| M2 T48 S3 | 14 | `SwimStompEnvelopeData`, `PlayFlagpoleSlide`, `PlaySmallJump`, `PlayBigJump`, `JumpRegContents`, `ContinueSndJump`, `N2Prt`, `FPS2nd`, `DmpJpFPS`, `PlayFireballThrow`, `PlayBump`, `Fthrow`, `ContinueBumpThrow`, `DecJpFPS` |
| M2 T48 S4 | 16 | `Square1SfxHandler`, `CheckSfx1Buffer`, `ExS1H`, `PlaySwimStomp`, `ContinueSwimStomp`, `BranchToDecLength1`, `PlaySmackEnemy`, `ContinueSmackEnemy`, `SmSpc`, `SmTick`, `DecrementSfx1Length`, `StopSquare1Sfx`, `ExSfx1`, `PlayPipeDownInj`, `ContinuePipeDownInj`, `NoPDwnL` |
| M2 T48 S5 | 18 | `ExtraLifeFreqData`, `PowerUpGrabFreqData`, `PUp_VGrow_FreqData`, `PlayCoinGrab`, `PlayTimerTick`, `CGrab_TTickRegL`, `ContinueCGrabTTick`, `N2Tone`, `PlayBlast`, `ContinueBlast`, `SBlasJ`, `PlayPowerUpGrab`, `ContinuePowerUpGrab`, `LoadSqu2Regs`, `DecrementSfx2Length`, `EmptySfx2Buffer`, `StopSquare2Sfx`, `ExSfx2` |
| M2 T48 S6 | 4 | `Square2SfxHandler`, `CheckSfx2Buffer`, `ExS2H`, `Cont_CGrab_TTick` |
| M2 T49 S1 | 14 | `JumpToDecLength2`, `PlayBowserFall`, `BlstSJp`, `ContinueBowserFall`, `PBFRegs`, `EL_LRegs`, `PlayExtraLife`, `ContinueExtraLife`, `DivLLoop`, `PlayGrowPowerUp`, `PlayGrowVine`, `GrowItemRegs`, `ContinueGrowItems`, `StopGrowItems` |
| M2 T49 S2 | 12 | `BrickShatterFreqData`, `PlayBrickShatter`, `ContinueBrickShatter`, `PlayNoiseSfx`, `DecrementSfx3Length`, `ExSfx3`, `NoiseSfxHandler`, `CheckNoiseBuffer`, `ExNH`, `PlayBowserFlame`, `ContinueBowserFlame`, `ContinueMusic` |
| M2 T49 S3 | 10 | `MusicHandler`, `LoadEventMusic`, `NoStopSfx`, `LoadAreaMusic`, `NoStop1`, `GMLoopB`, `HandleAreaMusicLoopB`, `FindAreaMusicHeader`, `FindEventMusicHeader`, `LoadHeader` |
| M2 T49 S4 | 11 | `HandleSquare2Music`, `EndOfMusicData`, `NotTRO`, `MusicLoopBack`, `VictoryMLoopBack`, `Squ2LengthHandler`, `Squ2NoteHandler`, `Rest`, `SkipFqL1`, `MiscSqu2MusicTasks`, `NoDecEnv1` |
| M2 T49 S5 | 8 | `HandleSquare1Music`, `FetchSqu1MusicData`, `Squ1NoteHandler`, `SkipCtrlL`, `MiscSqu1MusicTasks`, `NoDecEnv2`, `DeathMAltReg`, `DoAltLoad` |
| M2 T49 S6 | 6 | `HandleTriangleMusic`, `TriNoteHandler`, `NotDOrD4`, `MediN`, `LongN`, `LoadTriCtrlReg` |
| M2 T49 S7 | 8 | `HandleNoiseMusic`, `FetchNoiseBeatData`, `NoiseBeatHandler`, `StrongBeat`, `LongBeat`, `SilentBeat`, `PlayBeat`, `ExitMusicHandler` |
| M2 T49 S8 | 9 | `AlternateLengthHandler`, `ProcessLengthData`, `LoadControlRegs`, `NotECstlM`, `WaterMus`, `AllMus`, `LoadEnvelopeData`, `LoadUsualEnvData`, `LoadWaterEventMusEnvData` |
| M2 T49 S9 | 23 | `MusicHeaderData`, `TimeRunningOutHdr`, `Star_CloudHdr`, `EndOfLevelMusHdr`, `ResidualHeaderData`, `UndergroundMusHdr`, `SilenceHdr`, `CastleMusHdr`, `VictoryMusHdr`, `GameOverMusHdr`, `WaterMusHdr`, `WinCastleMusHdr`, `GroundLevelPart1Hdr`, `GroundLevelPart2AHdr`, `GroundLevelPart2BHdr`, `GroundLevelPart2CHdr`, `GroundLevelPart3AHdr`, `GroundLevelPart3BHdr`, `GroundLevelLeadInHdr`, `GroundLevelPart4AHdr`, `GroundLevelPart4BHdr`, `GroundLevelPart4CHdr`, `DeathMusHdr` |
| M2 T50 S1 | 21 | `Star_CloudMData`, `GroundM_P1Data`, `SilenceData`, `GroundM_P2AData`, `GroundM_P2BData`, `GroundM_P2CData`, `GroundM_P3AData`, `GroundM_P3BData`, `GroundMLdInData`, `GroundM_P4AData`, `GroundM_P4BData`, `DeathMusData`, `GroundM_P4CData`, `CastleMusData`, `GameOverMusData`, `TimeRunOutMusData`, `WinLevelMusData`, `UndergroundMusData`, `WaterMusData`, `EndOfCastleMusData`, `VictoryMusData` |
| M2 T50 S2 | 5 | `FreqRegLookupTbl`, `MusicLengthLookupTbl`, `EndOfCastleMusicEnvData`, `AreaMusicEnvData`, `WaterEventMusEnvData` |
| M2 T50 S3 | 2 | `BowserFlameEnvData`, `BrickShatterEnvData` |
| M2 T51 S2 | 4 | `ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol` |
| M2 T51 S3 | 1 | `KillEnemies` |
| M2 T51 S4 | 34 | `E_CastleArea1`, `E_CastleArea2`, `E_CastleArea3`, `E_CastleArea4`, `E_CastleArea5`, `E_CastleArea6`, `E_GroundArea1`, `E_GroundArea2`, `E_GroundArea3`, `E_GroundArea4`, `E_GroundArea5`, `E_GroundArea6`, `E_GroundArea7`, `E_GroundArea8`, `E_GroundArea9`, `E_GroundArea10`, `E_GroundArea11`, `E_GroundArea12`, `E_GroundArea13`, `E_GroundArea14`, `E_GroundArea15`, `E_GroundArea16`, `E_GroundArea17`, `E_GroundArea18`, `E_GroundArea19`, `E_GroundArea20`, `E_GroundArea21`, `E_GroundArea22`, `E_UndergroundArea1`, `E_UndergroundArea2`, `E_UndergroundArea3`, `E_WaterArea1`, `E_WaterArea2`, `E_WaterArea3` |
| M2 T52 S3 | 1 | `AddToScore` |
| M2 T52 S6 | 1 | `DrawLargePlatform` |
| M2 T70 S10 | 25 | `WSelectBufferTemplate`, `GameMenuRoutine`, `StartGame`, `ChkSelect`, `ChkWorldSel`, `SelectBLogic`, `IncWorldSel`, `UpdateShroom`, `NullJoypad`, `RunDemo`, `ResetTitle`, `ChkContinue`, `StartWorld1`, `InitScores`, `ExitMenu`, `GoContinue`, `MushroomIconData`, `DrawMushroomIcon`, `IconDataRead`, `ExitIcon`, `DemoActionData`, `DemoTimingData`, `DemoEngine`, `DoAction`, `DemoOver` |
| M2 T70 S11 | 15 | `PrintVictoryMessages`, `MRetainerMsg`, `ThankPlayer`, `SecondPartMsg`, `EvalForMusic`, `PrintMsg`, `IncMsgCounter`, `SetEndTimer`, `IncModeTask_A`, `ExitMsgs`, `PlayerEndWorld`, `EndExitOne`, `EndChkBButton`, `EndExitTwo`, `TerminateGame` |
| M2 T70 S12 | 10 | `FloateyNumTileData`, `ScoreUpdateData`, `FloateyNumbersRoutine`, `ChkNumTimer`, `DecNumTimer`, `LoadNumTiles`, `ChkTallEnemy`, `GetAltOffset`, `FloateyPart`, `SetupNumSpr` |
| M2 T70 S13 | 13 | `SetupIntermediate`, `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal` |
| M2 T70 S14 | 12 | `WriteTopStatusLine`, `WriteBottomStatusLine`, `DisplayTimeUp`, `NoTimeUp`, `DisplayIntermediate`, `PlayerInter`, `OutputInter`, `GameOverInter`, `NoInter`, `ResetSpritesAndScreenTimer`, `ResetScreenTimer`, `NoReset` |
| M2 T70 S15 | 17 | `Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, `InitializeNameTables`, `WriteNTAddr`, `InitNTLoop`, `InitATLoop`, `InitScroll`, `WritePPUReg1`, `InitializeMemory`, `InitPageLoop`, `InitByteLoop`, `InitByte`, `SkipByte` |
| M2 T70 S17 | 111 | `OperModeExecutionTree`, `TitleScreenMode`, `VictoryModeSubroutines`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `DrawTitleScreen`, `OutputTScr`, `ChkHiByte`, `RenderAreaGraphics`, `DrawMTLoop`, `RightCheck`, `LLeft`, `NextMTRow`, `SetAttrib`, `ExitDrawM`, `RenderAttributeTables`, `SetATHigh`, `AttribLoop`, `SetVRAMCtrl`, `ColorRotation`, `GetBlankPal`, `GetAreaPal`, `ExitColorRot`, `AreaParserTasks`, `RenderSceneryTerrain`, `ClrMTBuf`, `ThirdP`, `RendBack`, `SceLoop1`, `RendFore`, `SceLoop2`, `NoFore`, `RendTerr`, `TerMTile`, `StoreMT`, `TerrLoop`, `NoCloud2`, `TerrBChk`, `NextTBit`, `EndUChk`, `RendBBuf`, `ChkMTLow`, `StrBlock`, `ProcessAreaData`, `ProcADLoop`, `Chk1Row13`, `Chk1Row14`, `CheckRear`, `RdyDecode`, `SetBehind`, `NextAObj`, `ChkLength`, `ProcLoopb`, `EndAParse`, `IncAreaObjOffset`, `DecodeAreaData`, `Chk1stB`, `ChkRow14`, `ChkRow13`, `Mask2MSB`, `ChkSRows`, `LrgObj`, `NotWPipe`, `SpecObj`, `MoveAOId`, `NormObj`, `LeavePar`, `InitRear`, `LoopCmdE`, `BackColC`, `StrAObj`, `RunAObj`, `AlterAreaAttributes`, `Alter2`, `SetFore`, `AreaStyleObject`, `CastleObject`, `CRendLoop`, `ChkCFloor`, `NotTall`, `PlayerStop`, `ExitCastle`, `WaterPipe`, `IntroPipe`, `VPipeSectLoop`, `NoBlankP`, `ExitPipe`, `RenderSidewaysPipe`, `DrawSidePart`, `VerticalPipe`, `WarpPipe`, `DrawPipe`, `GetPipeHeight`, `RenderUnderPart`, `DrawThisRow`, `WaitOneRow`, `ExitUPartR`, `GameMode`, `GameRoutines`, `PlayerHole`, `HoleBottom`, `MoveSubs`, `FireballXSpdData`, `FireballObjCore`, `WhLoop`, `WhirlpoolActivate`, `WhPull` |
| M2 T70 S4 | 6 | `VRAM_AddrTable_Low`, `VRAM_AddrTable_High`, `VRAM_Buffer_Offset`, `NonMaskableInterrupt`, `ScreenOff`, `InitBuffer` |
| M2 T70 S6 | 9 | `RotPRandomBit`, `Sprite0Clr`, `Sprite0Hit`, `HBlankDelay`, `SkipSprite0`, `SkipMainOper`, `MoveAllSpritesOffscreen`, `MoveSpritesOffscreen`, `SprInitLoop` |
| M2 T70 S7 | 6 | `SpriteShuffler`, `ShuffleLoop`, `StrSprOffset`, `NextSprOffset`, `SetAmtOffset`, `SetMiscOffset` |
| M2 T70 S9 | 10 | `PauseRoutine`, `ChkPauseTimer`, `ChkStart`, `ClrPauseTimer`, `SetPause`, `ExitPause`, `ReadJoypads`, `ReadPortBits`, `PortLoop`, `Save8Bits` |

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

## Every node

| ROM line | Node | Current receiving S | Future package / basis | Historical T/S records |
| ---: | --- | --- | --- | --- |
| 699 | `Start` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T11 / S not recorded; M2 T14 / S not recorded; M2 T15 / S not recorded; M2 T15 S4; M2 T17 S6; M2 T19 S5; M2 T2 / S not recorded; M2 T21 S1; M2 T21 S2; M2 T24 S1; M2 T3 / S not recorded; M2 T8 / S not recorded |
| 706 | `VBlank1` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 708 | `VBlank2` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 712 | `WBootCheck` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 721 | `ColdBoot` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 737 | `EndlessLoop` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 743 | `VRAM_AddrTable_Low` | M2 T70 S4 | existing closure backlog; Accepted bounded NMI pointer/display transaction maintenance;prior proof retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T22 S15; M2 T24 S1 |
| 752 | `VRAM_AddrTable_High` | M2 T70 S4 | existing closure backlog; Accepted bounded NMI pointer/display transaction maintenance;prior proof retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T22 S15; M2 T24 S1 |
| 761 | `VRAM_Buffer_Offset` | M2 T70 S4 | existing closure backlog; Accepted bounded NMI pointer/display transaction maintenance;prior proof retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T22 S15; M2 T24 S1 |
| 764 | `NonMaskableInterrupt` | M2 T70 S4 | existing closure backlog; Accepted bounded NMI pointer/display transaction maintenance;prior proof retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T22 S22; M2 T24 S1 |
| 776 | `ScreenOff` | M2 T70 S4 | existing closure backlog; Accepted bounded NMI pointer/display transaction maintenance;prior proof retained. | M2 T14 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 796 | `InitBuffer` | M2 T70 S4 | existing closure backlog; Accepted bounded NMI pointer/display transaction maintenance;prior proof retained. | M2 T14 / S not recorded; M2 T22 S16; M2 T22 S23; M2 T24 S1 |
| 814 | `DecTimers` | M2 T22 S25 | existing closure backlog; T22/S18 completed the timer/LFSR source contract and source-order repair; T22/S25 independently reviews ROM equivalence. | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 820 | `DecTimersLoop` | M2 T22 S25 | existing closure backlog; T22/S18 completed the timer/LFSR source contract and source-order repair; T22/S25 independently reviews ROM equivalence. | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 823 | `SkipExpTimer` | M2 T22 S25 | existing closure backlog; T22/S18 completed the timer/LFSR source contract and source-order repair; T22/S25 independently reviews ROM equivalence. | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 825 | `NoDecTimers` | M2 T22 S25 | existing closure backlog; T22/S18 completed the timer/LFSR source contract and source-order repair; T22/S25 independently reviews ROM equivalence. | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 826 | `PauseSkip` | M2 T22 S25 | existing closure backlog; T22/S18 completed the timer/LFSR source contract and source-order repair; T22/S25 independently reviews ROM equivalence. | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 837 | `RotPRandomBit` | M2 T70 S6 | existing closure backlog; Accepted sprite-zero conditional visible-phase maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S18; M2 T22 S25; M2 T24 S1 |
| 843 | `Sprite0Clr` | M2 T70 S6 | existing closure backlog; Accepted sprite-zero conditional visible-phase maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 851 | `Sprite0Hit` | M2 T70 S6 | existing closure backlog; Accepted sprite-zero conditional visible-phase maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 855 | `HBlankDelay` | M2 T70 S6 | existing closure backlog; Accepted sprite-zero conditional visible-phase maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 857 | `SkipSprite0` | M2 T70 S6 | existing closure backlog; Accepted sprite-zero conditional visible-phase maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 868 | `SkipMainOper` | M2 T70 S6 | existing closure backlog; Accepted sprite-zero conditional visible-phase maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 876 | `PauseRoutine` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 885 | `ChkPauseTimer` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 889 | `ChkStart` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 904 | `ClrPauseTimer` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 906 | `SetPause` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 907 | `ExitPause` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S17; M2 T22 S24; M2 T24 S1 |
| 912 | `SpriteShuffler` | M2 T70 S7 | existing closure backlog; Accepted shared sprite-shuffle preset/index/material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1; M2 T9 / S not recorded |
| 917 | `ShuffleLoop` | M2 T70 S7 | existing closure backlog; Accepted shared sprite-shuffle preset/index/material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 926 | `StrSprOffset` | M2 T70 S7 | existing closure backlog; Accepted shared sprite-shuffle preset/index/material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 927 | `NextSprOffset` | M2 T70 S7 | existing closure backlog; Accepted shared sprite-shuffle preset/index/material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 934 | `SetAmtOffset` | M2 T70 S7 | existing closure backlog; Accepted shared sprite-shuffle preset/index/material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 937 | `SetMiscOffset` | M2 T70 S7 | existing closure backlog; Accepted shared sprite-shuffle preset/index/material maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S20; M2 T22 S27; M2 T24 S1 |
| 954 | `OperModeExecutionTree` | M2 T70 S17 | existing closure backlog; P15 same-class omitted JumpEngine scratch call correction. | M2 T14 / S not recorded; M2 T22 S21; M2 T22 S28; M2 T24 S1 |
| 965 | `MoveAllSpritesOffscreen` | M2 T70 S6 | existing closure backlog; Accepted common sprite-clear entry/loop maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 969 | `MoveSpritesOffscreen` | M2 T70 S6 | existing closure backlog; Accepted common sprite-clear entry/loop maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 972 | `SprInitLoop` | M2 T70 S6 | existing closure backlog; Accepted common sprite-clear entry/loop maintenance;prior evidence retained. | M2 T14 / S not recorded; M2 T22 S19; M2 T22 S26; M2 T24 S1 |
| 982 | `TitleScreenMode` | M2 T70 S17 | existing closure backlog; P15 same-class omitted JumpEngine scratch call correction. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 993 | `WSelectBufferTemplate` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 996 | `GameMenuRoutine` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1004 | `StartGame` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4; M2 T25 S9 |
| 1005 | `ChkSelect` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S10; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1013 | `ChkWorldSel` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1018 | `SelectBLogic` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1033 | `IncWorldSel` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1039 | `UpdateShroom` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1047 | `NullJoypad` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1049 | `RunDemo` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1053 | `ResetTitle` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1059 | `ChkContinue` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1065 | `StartWorld1` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1077 | `InitScores` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1080 | `ExitMenu` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1081 | `GoContinue` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T2 / S not recorded; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1090 | `MushroomIconData` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1093 | `DrawMushroomIcon` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 S2; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1095 | `IconDataRead` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1105 | `ExitIcon` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1109 | `DemoActionData` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1114 | `DemoTimingData` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1119 | `DemoEngine` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S2; M2 T15 S4; M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1129 | `DoAction` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1133 | `DemoOver` | M2 T70 S10 | existing closure backlog; Accepted source-confirmed InitScores and complete title/menu material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T25 S1; M2 T25 S2; M2 T25 S3; M2 T25 S4 |
| 1137 | `VictoryMode` | M2 T26 S7 | existing closure backlog; accepted S6 repaired-route transfer; S7 performs the independent outer-victory equivalence decision | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5; M2 T26 S6; M2 T26 S7; M2 T6 / S not recorded |
| 1144 | `AutoPlayer` | M2 T26 S7 | existing closure backlog; accepted S6 repaired-route transfer; S7 performs the independent outer-victory equivalence decision | M2 T21 S1; M2 T24 S1; M2 T26 S5; M2 T26 S6; M2 T26 S7 |
| 1147 | `VictoryModeSubroutines` | M2 T70 S17 | existing closure backlog; P15 same-class omitted JumpEngine scratch call correction. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5; M2 T6 / S not recorded |
| 1159 | `SetupVictoryMode` | M2 T26 S5 | existing closure backlog; accepted S4 route-equivalence closure; S5 performs per-label completion accounting | M2 T15 / S not recorded; M2 T15 S1; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1169 | `PlayerVictoryWalk` | M2 T26 S5 | existing closure backlog; accepted S4 route-equivalence closure; S5 performs per-label completion accounting | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T15 S4; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1178 | `PerformWalk` | M2 T26 S5 | existing closure backlog; accepted S4 route-equivalence closure; S5 performs per-label completion accounting | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1180 | `DontWalk` | M2 T26 S5 | existing closure backlog; accepted S4 route-equivalence closure; S5 performs per-label completion accounting | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1195 | `ExitVWalk` | M2 T26 S5 | existing closure backlog; accepted S4 route-equivalence closure; S5 performs per-label completion accounting | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1201 | `PrintVictoryMessages` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1215 | `MRetainerMsg` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1217 | `ThankPlayer` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1223 | `SecondPartMsg` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1232 | `EvalForMusic` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1236 | `PrintMsg` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1240 | `IncMsgCounter` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1248 | `SetEndTimer` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1251 | `IncModeTask_A` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1252 | `ExitMsgs` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1256 | `PlayerEndWorld` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1271 | `EndExitOne` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1272 | `EndChkBButton` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1281 | `EndExitTwo` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1287 | `FloateyNumTileData` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1303 | `ScoreUpdateData` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1308 | `FloateyNumbersRoutine` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1315 | `ChkNumTimer` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1320 | `DecNumTimer` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1328 | `LoadNumTiles` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1338 | `ChkTallEnemy` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1355 | `GetAltOffset` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1358 | `FloateyPart` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1363 | `SetupNumSpr` | M2 T70 S12 | existing closure backlog; Accepted source-order floatey score/OAM maintenance;prior evidence retained. | M2 T21 S1; M2 T24 S1; M2 T26 S5 |
| 1386 | `ScreenRoutines` | M2 T51 S2 | existing closure backlog; Accepted T51 S2 source-contiguous screen/parser output transfer. | M2 T15 S2; M2 T15 S3; M2 T24 S1 |
| 1408 | `InitScreen` | M2 T27 S1 | existing closure backlog; M2 T27 S1 contiguous screen-task root chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1418 | `SetupIntermediate` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1436 | `AreaPalette` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1439 | `GetAreaPalette` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1442 | `SetVRAMAddr_A` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1443 | `NextSubtask` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1448 | `BGColorCtrl_Addr` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1451 | `BackgroundColors` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1455 | `PlayerColors` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1460 | `GetBackgroundColor` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1465 | `NoBGColor` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1467 | `GetPlayerColors` | M2 T70 S17 | existing closure backlog; Accepted existing Firebar injury palette raw-index corrective chain;prior S13 evidence retained. | M2 T18 S3; M2 T24 S1 |
| 1473 | `ChkFiery` | M2 T70 S17 | existing closure backlog; Accepted existing Firebar injury palette raw-index corrective chain;prior S13 evidence retained. | M2 T24 S1 |
| 1477 | `StartClrGet` | M2 T70 S17 | existing closure backlog; Accepted existing Firebar injury palette raw-index corrective chain;prior S13 evidence retained. | M2 T24 S1 |
| 1479 | `ClrGetLoop` | M2 T70 S17 | existing closure backlog; Accepted existing Firebar injury palette raw-index corrective chain;prior S13 evidence retained. | M2 T24 S1 |
| 1489 | `SetBGColor` | M2 T70 S17 | existing closure backlog; Accepted existing Firebar injury palette raw-index corrective chain;prior S13 evidence retained. | M2 T24 S1 |
| 1502 | `SetVRAMOffset` | M2 T70 S17 | existing closure backlog; Accepted existing Firebar injury palette raw-index corrective chain;prior S13 evidence retained. | M2 T24 S1 |
| 1507 | `GetAlternatePalette1` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1512 | `SetVRAMAddr_B` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1513 | `NoAltPal` | M2 T70 S13 | existing closure backlog; Accepted source-order screen palette maintenance;prior evidence retained. | M2 T24 S1 |
| 1517 | `WriteTopStatusLine` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1524 | `WriteBottomStatusLine` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T19 S5; M2 T24 S1 |
| 1553 | `DisplayTimeUp` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1560 | `NoTimeUp` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1565 | `DisplayIntermediate` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T15 S3; M2 T24 S1 |
| 1577 | `PlayerInter` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1579 | `OutputInter` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1584 | `GameOverInter` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1589 | `NoInter` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1595 | `AreaParserTaskControl` | M2 T51 S2 | existing closure backlog; Accepted T51 S2 source-contiguous screen/parser output transfer. | M2 T24 S1 |
| 1597 | `TaskLoop` | M2 T51 S2 | existing closure backlog; Accepted T51 S2 source-contiguous screen/parser output transfer. | M2 T24 S1 |
| 1603 | `OutputCol` | M2 T51 S2 | existing closure backlog; Accepted T51 S2 source-contiguous screen/parser output transfer. | M2 T24 S1 |
| 1612 | `DrawTitleScreen` | M2 T70 S17 | existing closure backlog; S17 P3 bounded title pointer-output correction, accepted same-S custody. | M2 T24 S1 |
| 1624 | `OutputTScr` | M2 T70 S17 | existing closure backlog; S17 P3 bounded title pointer-output correction, accepted same-S custody. | M2 T24 S1 |
| 1629 | `ChkHiByte` | M2 T70 S17 | existing closure backlog; S17 P3 bounded title pointer-output correction, accepted same-S custody. | M2 T24 S1 |
| 1639 | `ClearBuffersDrawIcon` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1643 | `TScrClear` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1648 | `IncSubtask` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1653 | `WriteTopScore` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1656 | `IncModeTask_B` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1661 | `GameText` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1662 | `TopStatusBarLine` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1671 | `WorldLivesDisplay` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1680 | `TwoPlayerTimeUp` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1682 | `OnePlayerTimeUp` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1686 | `TwoPlayerGameOver` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1688 | `OnePlayerGameOver` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1693 | `WarpZoneWelcome` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1704 | `LuigiName` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1707 | `WarpZoneNumbers` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1712 | `GameTextOffsets` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1719 | `WriteGameText` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T15 S3; M2 T24 S1 |
| 1728 | `Chk2Players` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1731 | `LdGameText` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1733 | `GameTextLoop` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1740 | `EndGameText` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1756 | `PutLives` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1765 | `CheckPlayerName` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1775 | `ChkLuigi` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1778 | `NameLoop` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1782 | `ExitChkName` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1784 | `PrintWarpZoneNumbers` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1790 | `WarpNumLoop` | M2 T27 S2 | existing closure backlog; M2 T27 S2 contiguous remaining screen/status/text chain; accepted from T24 S2 custody. | M2 T24 S1 |
| 1804 | `ResetSpritesAndScreenTimer` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1809 | `ResetScreenTimer` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1813 | `NoReset` | M2 T70 S14 | existing closure backlog; Accepted HUD/intermediate timer maintenance;prior evidence retained. | M2 T24 S1 |
| 1825 | `RenderAreaGraphics` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T18 S2; M2 T21 S4; M2 T24 S1 |
| 1840 | `DrawMTLoop` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1878 | `RightCheck` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1886 | `LLeft` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1888 | `NextMTRow` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1889 | `SetAttrib` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1914 | `ExitDrawM` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1920 | `RenderAttributeTables` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T18 S2; M2 T21 S4; M2 T24 S1 |
| 1930 | `SetATHigh` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1940 | `AttribLoop` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1962 | `SetVRAMCtrl` | M2 T70 S17 | existing closure backlog; S17 P4 complete column output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 1970 | `ColorRotatePalette` | M2 T28 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 1973 | `BlankPalette` | M2 T28 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 1977 | `Palette3Data` | M2 T28 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 1983 | `ColorRotation` | M2 T70 S17 | existing closure backlog; P57 accepted continuous GameEngine scratch counter repair. | M2 T21 S4; M2 T24 S1 |
| 1991 | `GetBlankPal` | M2 T70 S17 | existing closure backlog; P57 accepted continuous GameEngine scratch counter repair. | M2 T21 S4; M2 T24 S1 |
| 2004 | `GetAreaPal` | M2 T70 S17 | existing closure backlog; P57 accepted continuous GameEngine scratch counter repair. | M2 T21 S4; M2 T24 S1 |
| 2024 | `ExitColorRot` | M2 T70 S17 | existing closure backlog; P57 accepted continuous GameEngine scratch counter repair. | M2 T21 S4; M2 T24 S1 |
| 2034 | `BlockGfxData` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2041 | `RemoveCoin_Axe` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S4; M2 T21 S4; M2 T22 S1; M2 T24 S1 |
| 2047 | `WriteBlankMT` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2052 | `ReplaceBlockMetatile` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T18 / S not recorded; M2 T18 S1; M2 T21 S4; M2 T24 S1 |
| 2058 | `DestroyBlockMetatile` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T18 / S not recorded; M2 T21 S4; M2 T22 S1; M2 T24 S1 |
| 2061 | `WriteBlockMetatile` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S4; M2 T18 / S not recorded; M2 T21 S4; M2 T24 S1 |
| 2076 | `UseBOffset` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2080 | `MoveVOffset` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2086 | `PutBlockMetatile` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S4; M2 T18 / S not recorded; M2 T21 S4; M2 T24 S1 |
| 2097 | `SaveHAdder` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2118 | `RemBridge` | M2 T28 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2145 | `MetatileGraphics_Low` | M2 T28 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2148 | `MetatileGraphics_High` | M2 T28 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2151 | `Palette0_MTiles` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2192 | `Palette1_MTiles` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2240 | `Palette2_MTiles` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2252 | `Palette3_MTiles` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2263 | `WaterPaletteData` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2275 | `GroundPaletteData` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2287 | `UndergroundPaletteData` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2299 | `CastlePaletteData` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2311 | `DaySnowPaletteData` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2316 | `NightSnowPaletteData` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2321 | `MushroomPaletteData` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2326 | `BowserPaletteData` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2331 | `MarioThanksMessage` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2339 | `LuigiThanksMessage` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2347 | `MushroomRetainerSaved` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2358 | `PrincessSaved1` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2366 | `PrincessSaved2` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2375 | `WorldSelectMessage1` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2382 | `WorldSelectMessage2` | M2 T28 S4 | existing closure backlog; owner-approved T28 S4 source-order data-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2395 | `JumpEngine` | M2 T28 S5 | existing closure backlog; owner-approved T28 S5 source-order receipt | M2 T21 S4; M2 T24 S1 |
| 2412 | `InitializeNameTables` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2421 | `WriteNTAddr` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2427 | `InitNTLoop` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2436 | `InitATLoop` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2446 | `ReadJoypads` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2454 | `ReadPortBits` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2455 | `PortLoop` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2474 | `Save8Bits` | M2 T70 S9 | existing closure backlog; Accepted input-to-pause material maintenance;prior evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2482 | `WriteBufferToScreen` | M2 T28 S6 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2495 | `SetupWrites` | M2 T28 S6 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2501 | `GetLength` | M2 T28 S6 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2504 | `OutputToVRAM` | M2 T28 S6 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2506 | `RepeatByte` | M2 T28 S6 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2523 | `UpdateScreen` | M2 T28 S6 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T14 / S not recorded; M2 T15 S2; M2 T21 S4; M2 T24 S1 |
| 2527 | `InitScroll` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2533 | `WritePPUReg1` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2544 | `StatusBarData` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2552 | `StatusBarOffset` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2555 | `PrintStatusBarNumbers` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T19 S5; M2 T21 S4; M2 T24 S1 |
| 2564 | `OutputNumbers` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2578 | `SetupNums` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2592 | `DigitPLoop` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2604 | `ExitOutputN` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2608 | `DigitsMathRoutine` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2613 | `AddModLoop` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2619 | `StoreNewD` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2623 | `EraseDMods` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2625 | `EraseMLoop` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2629 | `BorrowOne` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2632 | `CarryOne` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2639 | `UpdateTopScore` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T14 / S not recorded; M2 T21 S4; M2 T24 S1 |
| 2644 | `TopScoreCheck` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2647 | `GetScoreDiff` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2655 | `CopyScore` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2661 | `NoTopSc` | M2 T28 S7 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S4; M2 T24 S1 |
| 2665 | `DefaultSprOffsets` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2669 | `Sprite0Data` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2674 | `InitializeGame` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T15 / S not recorded; M2 T15 S1; M2 T21 S4; M2 T24 S1 |
| 2678 | `ClrSndLoop` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2685 | `InitializeArea` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T2 / S not recorded; M2 T21 S4; M2 T24 S1 |
| 2690 | `ClrTimersLoop` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2697 | `StartPage` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2705 | `SetInitNTHigh` | M2 T30 S13 | existing closure backlog; Accepted transfer-111: initial block-column parity correction. | M2 T21 S4; M2 T24 S1; M2 T30 S13 |
| 2728 | `SetSecHard` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2729 | `CheckHalfway` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2733 | `DoneInitArea` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2742 | `PrimaryGameSetup` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2750 | `SecondaryGameSetup` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2754 | `ClearVRLoop` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2775 | `ShufAmtLoop` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2780 | `ISpr0Loop` | M2 T28 S8 | existing closure backlog; owner-approved source-order T28 S8 initialization/bootstrap receipt | M2 T21 S4; M2 T24 S1 |
| 2795 | `InitializeMemory` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T14 / S not recorded; M2 T15 S3; M2 T18 / S not recorded; M2 T21 S1; M2 T24 S1 |
| 2799 | `InitPageLoop` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2800 | `InitByteLoop` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2804 | `InitByte` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2805 | `SkipByte` | M2 T70 S15 | existing closure backlog; Accepted final reset/startup source and graph review;old evidence retained. | M2 T21 S4; M2 T24 S1 |
| 2814 | `MusicSelectData` | M2 T29 S2 | existing closure backlog; owner-approved source-order T29 S2 area-music chain receipt | M2 T21 S4; M2 T24 S1 |
| 2818 | `GetAreaMusic` | M2 T29 S2 | existing closure backlog; owner-approved source-order T29 S2 area-music chain receipt | M2 T21 S4; M2 T24 S1 |
| 2830 | `ChkAreaType` | M2 T29 S2 | existing closure backlog; owner-approved source-order T29 S2 area-music chain receipt | M2 T21 S4; M2 T24 S1 |
| 2834 | `StoreMusic` | M2 T29 S2 | existing closure backlog; owner-approved source-order T29 S2 area-music chain receipt | M2 T21 S4; M2 T24 S1 |
| 2836 | `ExitGetM` | M2 T29 S2 | existing closure backlog; owner-approved source-order T29 S2 area-music chain receipt | M2 T21 S4; M2 T24 S1 |
| 2840 | `PlayerStarting_X_Pos` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2844 | `AltYPosOffset` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2847 | `PlayerStarting_Y_Pos` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2851 | `PlayerBGPriorityData` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2854 | `GameTimerData` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2858 | `Entrance_GameTimerSetup` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2874 | `ChkStPos` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2881 | `SetStPos` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2900 | `ChkOverR` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2911 | `ChkSwimE` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2914 | `SetPESub` | M2 T29 S3 | existing closure backlog; owner-approved source-order T29 S3 area-entry chain receipt | M2 T21 S4; M2 T24 S1 |
| 2921 | `HalfwayPageNybbles` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2931 | `PlayerLoseLife` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T6 / S not recorded |
| 2944 | `StillInGame` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2951 | `GetHalfway` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2960 | `MaskHPNyb` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2965 | `SetHalfway` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 2971 | `GameOverMode` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T15 / S not recorded; M2 T15 S1; M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T6 / S not recorded |
| 2981 | `SetupGameOver` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T15 S3; M2 T21 S4; M2 T24 S1 |
| 2993 | `RunGameOver` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T15 S3; M2 T21 S4; M2 T24 S1 |
| 3001 | `TerminateGame` | M2 T70 S11 | existing closure backlog; Accepted victory-message/final shared termination material maintenance;prior evidence retained. | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 3015 | `ContinueGame` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T6 / S not recorded |
| 3027 | `GameIsOn` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 3029 | `TransposePlayers` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T6 / S not recorded |
| 3039 | `TransLoop` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 3048 | `ExTrans` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 3052 | `DoNothing1` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 3055 | `DoNothing2` | M2 T29 S4 | existing closure backlog; owner-approved source-order T29 S4 life/mode state-chain receipt | M2 T21 S4; M2 T24 S1 |
| 3060 | `AreaParserTaskHandler` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3065 | `DoAPTasks` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3071 | `SkipATRender` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3073 | `AreaParserTasks` | M2 T70 S17 | existing closure backlog; P15 same-class omitted JumpEngine scratch call correction. | M2 T21 S4; M2 T24 S1 |
| 3087 | `IncrementColumnPos` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3094 | `NoColWrap` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3106 | `BSceneDataOffsets` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3109 | `BackSceneryData` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3131 | `BackSceneryMetatiles` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3145 | `FSceneDataOffsets` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3148 | `ForeSceneryData` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3158 | `TerrainMetatiles` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3161 | `TerrainRenderBits` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3179 | `AreaParserCore` | M2 T29 S5 | existing closure backlog; owner-approved source-order T29 S5 area-parser dispatch receipt | M2 T21 S4; M2 T24 S1 |
| 3184 | `RenderSceneryTerrain` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3187 | `ClrMTBuf` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3193 | `ThirdP` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3198 | `RendBack` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3223 | `SceLoop1` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3231 | `RendFore` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3235 | `SceLoop2` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3238 | `NoFore` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3242 | `RendTerr` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3249 | `TerMTile` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3253 | `StoreMT` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3258 | `TerrLoop` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3269 | `NoCloud2` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3270 | `TerrBChk` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3275 | `NextTBit` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3285 | `EndUChk` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3290 | `RendBBuf` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3295 | `ChkMTLow` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3306 | `StrBlock` | M2 T70 S17 | existing closure backlog; S17 P13 scenery scratch/output priority correction. | M2 T21 S4; M2 T24 S1 |
| 3319 | `BlockBuffLowBounds` | M2 T29 S6 | existing closure backlog; Owner-approved source-order continuation for the RenderSceneryTerrain through BlockBuffLowBounds scenery-column chain. | M2 T21 S4; M2 T24 S1 |
| 3326 | `ProcessAreaData` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T18 S2; M2 T21 S4; M2 T24 S1 |
| 3328 | `ProcADLoop` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3345 | `Chk1Row13` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3363 | `Chk1Row14` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3367 | `CheckRear` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3370 | `RdyDecode` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3372 | `SetBehind` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3373 | `NextAObj` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3374 | `ChkLength` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3378 | `ProcLoopb` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3384 | `EndAParse` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3386 | `IncAreaObjOffset` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3393 | `DecodeAreaData` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1; M2 T3 / S not recorded; M2 T30 S11 |
| 3397 | `Chk1stB` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3408 | `ChkRow14` | M2 T70 S17 | existing closure backlog; P28 accepted original parser00/07 phase-publication correction. | M2 T21 S4; M2 T24 S1 |
| 3416 | `ChkRow13` | M2 T70 S17 | existing closure backlog; P28 accepted original parser00/07 phase-publication correction. | M2 T21 S4; M2 T24 S1; M2 T30 S16 |
| 3429 | `Mask2MSB` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3431 | `ChkSRows` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3442 | `LrgObj` | M2 T70 S17 | existing closure backlog; P28 accepted original parser00/07 phase-publication correction. | M2 T21 S4; M2 T24 S1 |
| 3450 | `NotWPipe` | M2 T70 S17 | existing closure backlog; P28 accepted original parser00/07 phase-publication correction. | M2 T21 S4; M2 T24 S1 |
| 3452 | `SpecObj` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3455 | `MoveAOId` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3459 | `NormObj` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3472 | `LeavePar` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3473 | `InitRear` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3479 | `LoopCmdE` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3480 | `BackColC` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3489 | `StrAObj` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3492 | `RunAObj` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3561 | `AlterAreaAttributes` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3580 | `Alter2` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3586 | `SetFore` | M2 T70 S17 | existing closure backlog; S17 P6 complete parser output chain correction under standing owner mandate. | M2 T21 S4; M2 T24 S1 |
| 3591 | `ScrollLockObject_Warp` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3600 | `WarpNum` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3606 | `ScrollLockObject` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3615 | `KillEnemies` | M2 T51 S3 | existing closure backlog; Accepted transfer-281: source-exact residual KillEnemies primitive and its shared warp/flagpole callers. | M2 T21 S4; M2 T24 S1 |
| 3619 | `KillELoop` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3623 | `NoKillE` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3629 | `FrenzyIDData` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3632 | `AreaFrenzy` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T19 S5; M2 T21 S4; M2 T24 S1 |
| 3635 | `FreCompLoop` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3640 | `ExitAFrenzy` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3646 | `AreaStyleObject` | M2 T70 S17 | existing closure backlog; P15 same-class omitted JumpEngine scratch call correction. | M2 T21 S4; M2 T24 S1 |
| 3653 | `TreeLedge` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3665 | `MidTreeL` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3670 | `EndTreeL` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3673 | `MushroomLedge` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3682 | `EndMushL` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3696 | `AllUnder` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3699 | `NoUnder` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3706 | `PulleyRopeMetatiles` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3709 | `PulleyRopeObject` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3717 | `RenderPul` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3719 | `MushLExit` | M2 T29 S8 | existing closure backlog; Owner-approved source-order continuation for the ScrollLockObject_Warp through MushLExit special-object chain. | M2 T21 S4; M2 T24 S1 |
| 3724 | `CastleMetatiles` | M2 T29 S9 | existing closure backlog; accepted transfer-090: owner-approved source-order large-object geometry chain | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3737 | `CastleObject` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T17 S6; M2 T18 S2; M2 T21 S4; M2 T24 / S not recorded; M2 T24 S1; M2 T29 S9 |
| 3748 | `CRendLoop` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3759 | `ChkCFloor` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3772 | `NotTall` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3789 | `PlayerStop` | M2 T70 S17 | existing closure backlog; S17 P9 actual castle06 scratch counter correction. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3791 | `ExitCastle` | M2 T70 S17 | existing closure backlog; S17 P9 actual castle06 scratch counter correction. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3795 | `WaterPipe` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3810 | `IntroPipe` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3817 | `VPipeSectLoop` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3823 | `NoBlankP` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3825 | `SidePipeShaftData` | M2 T29 S9 | existing closure backlog; accepted transfer-090: owner-approved source-order large-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3828 | `SidePipeTopPart` | M2 T29 S9 | existing closure backlog; accepted transfer-090: owner-approved source-order large-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3831 | `SidePipeBottomPart` | M2 T29 S9 | existing closure backlog; accepted transfer-090: owner-approved source-order large-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3835 | `ExitPipe` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3840 | `RenderSidewaysPipe` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3855 | `DrawSidePart` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3862 | `VerticalPipeData` | M2 T29 S9 | existing closure backlog; accepted transfer-090: owner-approved source-order large-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3868 | `VerticalPipe` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3876 | `WarpPipe` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3900 | `DrawPipe` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9; M2 T30 S12 |
| 3911 | `GetPipeHeight` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T29 S9 |
| 3921 | `FindEmptyEnemySlot` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3923 | `EmptyChkLoop` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3929 | `ExitEmptyChk` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3933 | `Hole_Water` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3944 | `QuestionBlockRow_High` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3948 | `QuestionBlockRow_Low` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3960 | `Bridge_High` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3964 | `Bridge_Middle` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3968 | `Bridge_Low` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3983 | `FlagBalls_Residual` | M2 T29 S10 | existing closure backlog; accepted transfer-091: owner-approved source-order allocation/final-object geometry chain | M2 T21 S4; M2 T24 S1; M2 T29 S10 |
| 3991 | `FlagpoleObject` | M2 T22 S5 | existing closure backlog; T22 S1/P2 label-owner map or confirmed missing scheduler obligation | M2 T22 S1; M2 T24 S1 |
| 4018 | `EndlessRope` | M2 T30 S1 | existing closure backlog; Owner-approved M2 T30/S1 source-order receipt for the EndlessRope through DrawRope area-object rendering chain. | M2 T21 S4; M2 T24 S1 |
| 4023 | `BalancePlatRope` | M2 T30 S1 | existing closure backlog; Owner-approved M2 T30/S1 source-order receipt for the EndlessRope through DrawRope area-object rendering chain. | M2 T21 S4; M2 T24 S1 |
| 4034 | `DrawRope` | M2 T30 S1 | existing closure backlog; Owner-approved M2 T30/S1 source-order receipt for the EndlessRope through DrawRope area-object rendering chain. | M2 T21 S4; M2 T24 S1 |
| 4039 | `CoinMetatileData` | M2 T30 S2 | existing closure backlog; Owner-approved M2 T30/S2 source-order receipt for the CoinMetatileData through RowOfCoins selector chain. | M2 T21 S4; M2 T24 S1 |
| 4042 | `RowOfCoins` | M2 T30 S2 | existing closure backlog; Owner-approved M2 T30/S2 source-order receipt for the CoinMetatileData through RowOfCoins selector chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1 |
| 4049 | `C_ObjectRow` | M2 T30 S3 | existing closure backlog; Owner-approved M2 T30/S3 source-order receipt for the C_ObjectRow through ColObj castle-column chain. | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4052 | `C_ObjectMetatile` | M2 T30 S3 | existing closure backlog; Owner-approved M2 T30/S3 source-order receipt for the C_ObjectRow through ColObj castle-column chain. | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4055 | `CastleBridgeObj` | M2 T30 S3 | existing closure backlog; Owner-approved M2 T30/S3 source-order receipt for the C_ObjectRow through ColObj castle-column chain. | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4060 | `AxeObj` | M2 T30 S3 | existing closure backlog; Owner-approved M2 T30/S3 source-order receipt for the C_ObjectRow through ColObj castle-column chain. | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4064 | `ChainObj` | M2 T30 S3 | existing closure backlog; Owner-approved M2 T30/S3 source-order receipt for the C_ObjectRow through ColObj castle-column chain. | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4070 | `EmptyBlock` | M2 T30 S3 | existing closure backlog; Owner-approved M2 T30/S3 source-order receipt for the C_ObjectRow through ColObj castle-column chain. | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4074 | `ColObj` | M2 T30 S3 | existing closure backlog; Owner-approved M2 T30/S3 source-order receipt for the C_ObjectRow through ColObj castle-column chain. | M2 T21 S4; M2 T24 S1; M2 T30 S3 |
| 4079 | `SolidBlockMetatiles` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4082 | `BrickMetatiles` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4086 | `RowOfBricks` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4091 | `DrawBricks` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4094 | `RowOfSolidBlocks` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4097 | `GetRow` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4099 | `DrawRow` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4104 | `ColumnOfBricks` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4109 | `ColumnOfSolidBlocks` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4112 | `GetRow2` | M2 T30 S4 | existing closure backlog; Accepted transfer-101: source-order row/column block chain. | M2 T21 S4; M2 T24 S1; M2 T30 S4 |
| 4120 | `BulletBillCannon` | M2 T30 S5 | existing closure backlog; Accepted transfer-102: source-order cannon geometry and coordinate registration chain. | M2 T21 S4; M2 T24 S1; M2 T30 S5 |
| 4135 | `SetupCannon` | M2 T30 S5 | existing closure backlog; Accepted transfer-102: source-order cannon geometry and coordinate registration chain. | M2 T21 S4; M2 T24 S1; M2 T30 S5 |
| 4146 | `StrCOffset` | M2 T30 S5 | existing closure backlog; Accepted transfer-102: source-order cannon geometry and coordinate registration chain. | M2 T21 S4; M2 T24 S1; M2 T30 S5 |
| 4151 | `StaircaseHeightData` | M2 T30 S6 | existing closure backlog; Accepted transfer-103: source-order staircase rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S6 |
| 4154 | `StaircaseRowData` | M2 T30 S6 | existing closure backlog; Accepted transfer-103: source-order staircase rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S6 |
| 4157 | `StaircaseObject` | M2 T30 S6 | existing closure backlog; Accepted transfer-103: source-order staircase rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S6 |
| 4162 | `NextStair` | M2 T30 S6 | existing closure backlog; Accepted transfer-103: source-order staircase rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S6 |
| 4172 | `Jumpspring` | M2 T30 S7 | existing closure backlog; Accepted transfer-104: source-order jumpspring creation chain. | M2 T11 / S not recorded; M2 T21 S4; M2 T24 S1; M2 T30 S7 |
| 4197 | `Hidden1UpBlock` | M2 T30 S8 | existing closure backlog; Accepted transfer-105: source-order item-block selection/rendering chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4204 | `QuestionBlock` | M2 T30 S8 | existing closure backlog; Accepted transfer-105: source-order item-block selection/rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4208 | `BrickWithCoins` | M2 T30 S8 | existing closure backlog; Accepted transfer-105: source-order item-block selection/rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4212 | `BrickWithItem` | M2 T30 S8 | existing closure backlog; Accepted transfer-105: source-order item-block selection/rendering chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4220 | `BWithL` | M2 T30 S8 | existing closure backlog; Accepted transfer-105: source-order item-block selection/rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4223 | `DrawQBlk` | M2 T30 S8 | existing closure backlog; Accepted transfer-105: source-order item-block selection/rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4228 | `GetAreaObjectID` | M2 T30 S8 | existing closure backlog; Accepted transfer-105: source-order item-block selection/rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4233 | `ExitDecBlock` | M2 T30 S8 | existing closure backlog; Accepted transfer-105: source-order item-block selection/rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S8 |
| 4237 | `HoleMetatiles` | M2 T30 S9 | existing closure backlog; Accepted transfer-106: source-order hole/whirlpool registration and UnderPart rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4240 | `Hole_Empty` | M2 T30 S9 | existing closure backlog; Accepted transfer-106: source-order hole/whirlpool registration and UnderPart rendering chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4265 | `StrWOffset` | M2 T30 S9 | existing closure backlog; Accepted transfer-106: source-order hole/whirlpool registration and UnderPart rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4266 | `NoWhirlP` | M2 T30 S9 | existing closure backlog; Accepted transfer-106: source-order hole/whirlpool registration and UnderPart rendering chain. | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4273 | `RenderUnderPart` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T18 S2; M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4289 | `DrawThisRow` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4290 | `WaitOneRow` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4296 | `ExitUPartR` | M2 T70 S17 | existing closure backlog; P39 accepted raw pipe/castle and returned-row fidelity repair. | M2 T21 S4; M2 T24 S1; M2 T30 S9 |
| 4300 | `ChkLrgObjLength` | M2 T30 S10 | existing closure backlog; Accepted transfer-107: common attribute/length/coordinate helper chain. | M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4303 | `ChkLrgObjFixedLength` | M2 T30 S10 | existing closure backlog; Accepted transfer-107: common attribute/length/coordinate helper chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4310 | `LenSet` | M2 T30 S10 | existing closure backlog; Accepted transfer-107: common attribute/length/coordinate helper chain. | M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4313 | `GetLrgObjAttrib` | M2 T30 S10 | existing closure backlog; Accepted transfer-107: common attribute/length/coordinate helper chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4326 | `GetAreaObjXPosition` | M2 T30 S10 | existing closure backlog; Accepted transfer-107: common attribute/length/coordinate helper chain. | M2 T18 S2; M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4336 | `GetAreaObjYPosition` | M2 T30 S10 | existing closure backlog; Accepted transfer-107: common attribute/length/coordinate helper chain. | M2 T21 S4; M2 T24 S1; M2 T30 S10 |
| 4349 | `BlockBufferAddr` | M2 T30 S13 | existing closure backlog; Accepted transfer-110: shared block-buffer address chain. | M2 T21 S4; M2 T24 S1; M2 T30 S13 |
| 4353 | `GetBlockBufferAddr` | M2 T30 S13 | existing closure backlog; Accepted transfer-110: shared block-buffer address chain. | M2 T17 S4; M2 T21 S4; M2 T24 S1; M2 T30 S13 |
| 4376 | `AreaDataOfsLoopback` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T19 S5; M2 T21 S4; M2 T24 S1 |
| 4381 | `LoadAreaPointer` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T15 S3; M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4384 | `GetAreaType` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4392 | `FindAreaPointer` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4402 | `GetAreaDataAddrs` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4434 | `StoreFore` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4472 | `StoreStyle` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4485 | `WorldAddrOffsets` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4491 | `AreaAddrOffsets` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4492 | `World1Areas` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4493 | `World2Areas` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4494 | `World3Areas` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4495 | `World4Areas` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4496 | `World5Areas` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4497 | `World6Areas` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4498 | `World7Areas` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4499 | `World8Areas` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4509 | `EnemyAddrHOffsets` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4512 | `EnemyDataAddrLow` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4520 | `EnemyDataAddrHigh` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4528 | `AreaDataHOffsets` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4531 | `AreaDataAddrLow` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4539 | `AreaDataAddrHigh` | M2 T30 S14 | existing closure backlog; Accepted transfer-112: area-pointer-header | M2 T21 S4; M2 T24 S1; M2 T30 S14 |
| 4550 | `E_CastleArea1` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4558 | `E_CastleArea2` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4565 | `E_CastleArea3` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4574 | `E_CastleArea4` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4583 | `E_CastleArea5` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4589 | `E_CastleArea6` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4598 | `E_GroundArea1` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4606 | `E_GroundArea2` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4613 | `E_GroundArea3` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4619 | `E_GroundArea4` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4627 | `E_GroundArea5` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4636 | `E_GroundArea6` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4643 | `E_GroundArea7` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4650 | `E_GroundArea8` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4656 | `E_GroundArea9` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4662 | `E_GroundArea10` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4666 | `E_GroundArea11` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4674 | `E_GroundArea12` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4679 | `E_GroundArea13` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4687 | `E_GroundArea14` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4695 | `E_GroundArea15` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4700 | `E_GroundArea16` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4704 | `E_GroundArea17` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4714 | `E_GroundArea18` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4722 | `E_GroundArea19` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4731 | `E_GroundArea20` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4738 | `E_GroundArea21` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4743 | `E_GroundArea22` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4751 | `E_UndergroundArea1` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4760 | `E_UndergroundArea2` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4769 | `E_UndergroundArea3` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4777 | `E_WaterArea1` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4783 | `E_WaterArea2` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
| 4791 | `E_WaterArea3` | M2 T51 S4 | existing closure backlog; M2 T51 S4 accepted original enemy-stream data-chain completion, transfer-282 | M2 T19 S5; M2 T21 S4; M2 T24 S1; M2 T30 S15 |
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
| 5403 | `ScrollHandler` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T15 S3; M2 T24 S1 |
| 5422 | `ChkNearMid` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T24 S1 |
| 5427 | `ScrollScreen` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T15 S3; M2 T24 S1 |
| 5451 | `InitScrlAmt` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T24 S1 |
| 5453 | `ChkPOffscr` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T24 S1 |
| 5463 | `KeepOnscr` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T24 S1 |
| 5475 | `InitPlatScrl` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T24 S1 |
| 5479 | `X_SubtracterData` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T24 S1 |
| 5482 | `OffscrJoypadBitsData` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T24 S1 |
| 5487 | `GetScreenPosition` | M2 T31 S3 | existing closure backlog; transfer-132-t31-scroll-chain; Admit the next planned dispatcher scroll chain under the continuing owner-approved M2 mandate. | M2 T24 S1 |
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
| 5583 | `PlayerCtrlRoutine` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T17 S4; M2 T23 / S not recorded; M2 T23 S2; M2 T24 S1 |
| 5595 | `DisJoyp` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5597 | `SaveJoyp` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5615 | `SizeChk` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5623 | `ChkMoveDir` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5629 | `SetMoveDir` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5630 | `PlayerSubs` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5649 | `PlayerHole` | M2 T70 S17 | existing closure backlog; P23 accepted bounded original RAM07 threshold correction. | M2 T24 S1 |
| 5661 | `HoleDie` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5670 | `HoleBottom` | M2 T70 S17 | existing closure backlog; P23 accepted bounded original RAM07 threshold correction. | M2 T24 S1 |
| 5672 | `ChkHoleX` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5680 | `ExitCtrl` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5682 | `CloudExit` | M2 T32 S1 | existing closure backlog; Accepted transfer-134, source-order player control chain. | M2 T24 S1 |
| 5691 | `Vine_AutoClimb` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5697 | `AutoClimb` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5702 | `SetEntr` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5708 | `VerticalPipeEntry` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5722 | `MovePlayerYAxis` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5730 | `SideExitPipeEntry` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5733 | `ChgAreaPipe` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5736 | `ChgAreaMode` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5740 | `ExitCAPipe` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5742 | `EnterSidePipe` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5751 | `RightPipe` | M2 T32 S2 | existing closure backlog; Accepted transfer-135: bounded vine/pipe transition chain. | M2 T24 S1 |
| 5757 | `PlayerChangeSize` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5762 | `EndChgSize` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5765 | `ExitChgSize` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5769 | `PlayerInjuryBlink` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5776 | `ExitBlink` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5778 | `InitChangeSize` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5786 | `ExitBoth` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5791 | `PlayerDeath` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5797 | `DonePlayerTask` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5804 | `PlayerFireFlower` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5812 | `CyclePlayerPalette` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5821 | `ResetPalFireFlower` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5824 | `ResetPalStar` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5830 | `ExitDeath` | M2 T32 S3 | existing closure backlog; Accepted transfer-136: bounded size/injury/death/palette timer-state chain. | M2 T24 S1 |
| 5835 | `FlagpoleSlide` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1; M2 T6 / S not recorded |
| 5847 | `SlidePlayer` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1 |
| 5848 | `NoFPObj` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1 |
| 5853 | `Hidden1UpCoinAmts` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1 |
| 5856 | `PlayerEndLevel` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1; M2 T6 / S not recorded |
| 5868 | `ChkStop` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1 |
| 5874 | `InCastle` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1 |
| 5876 | `RdyNextA` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1 |
| 5888 | `NextArea` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T15 S3; M2 T24 S1 |
| 5895 | `ExitNA` | M2 T32 S4 | existing closure backlog; Accepted transfer-137: bounded flagpole/end-level chain. | M2 T24 S1 |
| 5899 | `PlayerMovementSubs` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T23 S1; M2 T24 S1 |
| 5907 | `SetCrouch` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5908 | `ProcMove` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5916 | `MoveSubs` | M2 T70 S17 | existing closure backlog; P15 same-class omitted JumpEngine scratch call correction. | M2 T24 S1 |
| 5923 | `NoMoveSub` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5928 | `OnGroundStateSub` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5933 | `GndMove` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5940 | `FallingSub` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T15 S4; M2 T24 S1 |
| 5947 | `JumpSwimSub` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T15 S4; M2 T24 S1 |
| 5959 | `DumpFall` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5961 | `ProcSwim` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5969 | `LRWater` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5972 | `LRAir` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T15 S4; M2 T24 S1 |
| 5975 | `JSMove` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5982 | `ExitMov1` | M2 T33 S1 | existing closure backlog; Accepted transfer-138: movement dispatch and ground/air chain. | M2 T24 S1 |
| 5986 | `ClimbAdderLow` | M2 T33 S2 | existing closure backlog; Accepted transfer-139: climbing movement and side-switch chain. | M2 T24 S1 |
| 5988 | `ClimbAdderHigh` | M2 T33 S2 | existing closure backlog; Accepted transfer-139: climbing movement and side-switch chain. | M2 T24 S1 |
| 5991 | `ClimbingSub` | M2 T33 S2 | existing closure backlog; Accepted transfer-139: climbing movement and side-switch chain. | M2 T24 S1 |
| 6000 | `MoveOnVine` | M2 T33 S2 | existing closure backlog; Accepted transfer-139: climbing movement and side-switch chain. | M2 T24 S1 |
| 6019 | `ClimbFD` | M2 T33 S2 | existing closure backlog; Accepted transfer-139: climbing movement and side-switch chain. | M2 T24 S1 |
| 6022 | `CSetFDir` | M2 T33 S2 | existing closure backlog; Accepted transfer-139: climbing movement and side-switch chain. | M2 T24 S1 |
| 6032 | `ExitCSub` | M2 T33 S2 | existing closure backlog; Accepted transfer-139: climbing movement and side-switch chain. | M2 T24 S1 |
| 6033 | `InitCSTimer` | M2 T33 S2 | existing closure backlog; Accepted transfer-139: climbing movement and side-switch chain. | M2 T24 S1 |
| 6039 | `JumpMForceData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6042 | `FallMForceData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6045 | `PlayerYSpdData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6048 | `InitMForceData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6051 | `MaxLeftXSpdData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6054 | `MaxRightXSpdData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6058 | `FrictionData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6061 | `Climb_Y_SpeedData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6064 | `Climb_Y_MForceData` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6067 | `PlayerPhysicsSub` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6079 | `ProcClimb` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6086 | `SetCAnim` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6089 | `CheckForJumping` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6097 | `NoJump` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6099 | `ProcJumping` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6109 | `InitJS` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6133 | `ChkWtr` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6141 | `GetYPhy` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6159 | `PJumpSnd` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6163 | `SJumpSnd` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6164 | `X_Physics` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6172 | `ProcPRun` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6184 | `ChkRFast` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6191 | `FastXSp` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6193 | `SetRTmr` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6195 | `GetXPhy` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6201 | `GetXPhy2` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6213 | `ExitPhy` | M2 T33 S3 | existing closure backlog; Accepted transfer-140: physics tables and initialization chain. | M2 T24 S1 |
| 6217 | `PlayerAnimTmrData` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6220 | `GetPlayerAnimSpeed` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6229 | `ChkSkid` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6236 | `SetRunSpd` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6238 | `ProcSkid` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6246 | `SetAnimSpd` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6252 | `ImposeFriction` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T15 S4; M2 T23 S1; M2 T23 S2; M2 T24 S1 |
| 6260 | `JoypFrict` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6262 | `LeftFrict` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T23 S1; M2 T23 S2; M2 T24 S1 |
| 6274 | `RghtFrict` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T23 S1; M2 T23 S2; M2 T24 S1 |
| 6285 | `XSpdSign` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6290 | `SetAbsSpd` | M2 T33 S4 | existing closure backlog; Accepted transfer-141: animation timing and friction chain. | M2 T24 S1 |
| 6298 | `ProcFireball_Bubble` | M2 T34 S1 | existing closure backlog; Accepted transfer-142: fireball and bubble dispatch chain. | M2 T19 / S not recorded; M2 T20 S1; M2 T20 S2; M2 T20 S3; M2 T21 S6; M2 T24 / S not recorded; M2 T24 S1 |
| 6330 | `ProcFireballs` | M2 T34 S1 | existing closure backlog; Accepted transfer-142: fireball and bubble dispatch chain. | M2 T21 S6; M2 T24 S1 |
| 6336 | `ProcAirBubbles` | M2 T34 S1 | existing closure backlog; Accepted transfer-142: fireball and bubble dispatch chain. | M2 T19 S4; M2 T21 S6; M2 T24 S1 |
| 6340 | `BublLoop` | M2 T34 S1 | existing closure backlog; Accepted transfer-142: fireball and bubble dispatch chain. | M2 T21 S6; M2 T24 S1 |
| 6347 | `BublExit` | M2 T34 S1 | existing closure backlog; Accepted transfer-142: fireball and bubble dispatch chain. | M2 T21 S6; M2 T24 S1 |
| 6349 | `FireballXSpdData` | M2 T70 S17 | existing closure backlog; P46 accepted actualsimultaneousdirection producer andadjacentPRG speed-read repair. | M2 T21 S6; M2 T24 S1 |
| 6352 | `FireballObjCore` | M2 T70 S17 | existing closure backlog; P46 accepted actualsimultaneousdirection producer andadjacentPRG speed-read repair. | M2 T16 S3; M2 T17 S2; M2 T17 S5; M2 T20 / S not recorded; M2 T20 S1; M2 T20 S2; M2 T21 S6; M2 T24 / S not recorded; M2 T24 S1 |
| 6380 | `RunFB` | M2 T34 S2 | existing closure backlog; Accepted transfer-143: fireball core state and explosion dispatch. | M2 T21 S6; M2 T24 S1 |
| 6401 | `EraseFB` | M2 T34 S2 | existing closure backlog; Accepted transfer-143: fireball core state and explosion dispatch. | M2 T21 S6; M2 T24 S1 |
| 6403 | `NoFBall` | M2 T34 S2 | existing closure backlog; Accepted transfer-143: fireball core state and explosion dispatch. | M2 T21 S6; M2 T24 S1 |
| 6405 | `FireballExplosion` | M2 T34 S2 | existing closure backlog; Accepted transfer-143: fireball core state and explosion dispatch. | M2 T16 S3; M2 T21 S6; M2 T24 S1 |
| 6409 | `BubbleCheck` | M2 T35 S1 | existing closure backlog; Accepted transfer-144: bubble setup and movement chain. | M2 T20 S1; M2 T21 S6; M2 T24 S1 |
| 6419 | `SetupBubble` | M2 T35 S1 | existing closure backlog; Accepted transfer-144: bubble setup and movement chain. | M2 T21 S6; M2 T24 S1 |
| 6425 | `PosBubl` | M2 T35 S1 | existing closure backlog; Accepted transfer-144: bubble setup and movement chain. | M2 T21 S6; M2 T24 S1 |
| 6440 | `MoveBubl` | M2 T35 S1 | existing closure backlog; Accepted transfer-144: bubble setup and movement chain. | M2 T21 S6; M2 T24 S1 |
| 6450 | `Y_Bubl` | M2 T35 S1 | existing closure backlog; Accepted transfer-144: bubble setup and movement chain. | M2 T21 S6; M2 T24 S1 |
| 6451 | `ExitBubl` | M2 T35 S1 | existing closure backlog; Accepted transfer-144: bubble setup and movement chain. | M2 T21 S6; M2 T24 S1 |
| 6453 | `Bubble_MForceData` | M2 T35 S1 | existing closure backlog; Accepted transfer-144: bubble setup and movement chain. | M2 T21 S6; M2 T24 S1 |
| 6456 | `BubbleTimerData` | M2 T35 S1 | existing closure backlog; Accepted transfer-144: bubble setup and movement chain. | M2 T21 S6; M2 T24 S1 |
| 6461 | `RunGameTimer` | M2 T35 S2 | existing closure backlog; Accepted transfer-145: timer gate, countdown and expiry chain. | M2 T15 S3; M2 T19 S5; M2 T21 S6; M2 T24 S1 |
| 6486 | `ResGTCtrl` | M2 T35 S2 | existing closure backlog; Accepted transfer-145: timer gate, countdown and expiry chain. | M2 T21 S6; M2 T24 S1 |
| 6494 | `TimeUpOn` | M2 T35 S2 | existing closure backlog; Accepted transfer-145: timer gate, countdown and expiry chain. | M2 T21 S6; M2 T24 S1 |
| 6497 | `ExGTimer` | M2 T35 S2 | existing closure backlog; Accepted transfer-145: timer gate, countdown and expiry chain. | M2 T21 S6; M2 T24 S1 |
| 6501 | `WarpZoneObject` | M2 T31 S2 | existing closure backlog; Accepted original enemy-vector missing-target dependency, transfer-126 | M2 T21 S6; M2 T24 S1 |
| 6519 | `ProcessWhirlpools` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T22 S1; M2 T24 S1 |
| 6526 | `WhLoop` | M2 T70 S17 | existing closure backlog; P45 accepted actual whirlpool scratch publication/order fidelity repair. | M2 T24 S1 |
| 6546 | `NextWh` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6548 | `ExitWh` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6550 | `WhirlpoolActivate` | M2 T70 S17 | existing closure backlog; P45 accepted actual whirlpool scratch publication/order fidelity repair. | M2 T22 S1; M2 T24 S1 |
| 6577 | `LeftWh` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6586 | `SetPWh` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6587 | `WhPull` | M2 T70 S17 | existing closure backlog; P45 accepted actual whirlpool scratch publication/order fidelity repair. | M2 T24 S1 |
| 6598 | `FlagpoleScoreMods` | M2 T22 S5 | existing closure backlog; T22 cannon/whirlpool/flagpole/vine responsibility includes continuations outside its physical slice | M2 T24 S1 |
| 6601 | `FlagpoleScoreDigits` | M2 T22 S5 | existing closure backlog; T22 cannon/whirlpool/flagpole/vine responsibility includes continuations outside its physical slice | M2 T24 S1 |
| 6604 | `FlagpoleRoutine` | M2 T22 S5 | existing closure backlog; T22 S1/P2 label-owner map or confirmed missing scheduler obligation | M2 T17 S6; M2 T22 S1; M2 T22 S4; M2 T24 S1 |
| 6635 | `SkipScore` | M2 T22 S5 | existing closure backlog; T22 cannon/whirlpool/flagpole/vine responsibility includes continuations outside its physical slice | M2 T24 S1 |
| 6636 | `GiveFPScr` | M2 T22 S5 | existing closure backlog; T22 cannon/whirlpool/flagpole/vine responsibility includes continuations outside its physical slice | M2 T24 S1 |
| 6643 | `FPGfx` | M2 T22 S5 | existing closure backlog; T22 cannon/whirlpool/flagpole/vine responsibility includes continuations outside its physical slice | M2 T17 S6; M2 T22 S4; M2 T24 S1 |
| 6646 | `ExitFlagP` | M2 T22 S5 | existing closure backlog; T22 cannon/whirlpool/flagpole/vine responsibility includes continuations outside its physical slice | M2 T24 S1 |
| 6650 | `Jumpspring_Y_PosData` | M2 T35 S3 | existing closure backlog; Accepted transfer-146: jumpspring state and caller chain. | M2 T24 S1 |
| 6653 | `JumpspringHandler` | M2 T35 S3 | existing closure backlog; Accepted transfer-146: jumpspring state and caller chain. | M2 T17 S4; M2 T24 S1 |
| 6667 | `DownJSpr` | M2 T35 S3 | existing closure backlog; Accepted transfer-146: jumpspring state and caller chain. | M2 T24 S1 |
| 6669 | `PosJSpr` | M2 T35 S3 | existing closure backlog; Accepted transfer-146: jumpspring state and caller chain. | M2 T24 S1 |
| 6682 | `BounceJS` | M2 T35 S3 | existing closure backlog; Accepted transfer-146: jumpspring state and caller chain. | M2 T24 S1 |
| 6688 | `DrawJSpr` | M2 T35 S3 | existing closure backlog; Accepted transfer-146: jumpspring state and caller chain. | M2 T24 S1 |
| 6698 | `ExJSpring` | M2 T35 S3 | existing closure backlog; Accepted transfer-146: jumpspring state and caller chain. | M2 T24 S1 |
| 6702 | `Setup_Vine` | M2 T35 S4 | existing closure backlog; Accepted transfer-147: vine initialization and height data. | M2 T22 S1; M2 T24 S1 |
| 6716 | `NextVO` | M2 T35 S4 | existing closure backlog; Accepted transfer-147: vine initialization and height data. | M2 T24 S1 |
| 6727 | `VineHeightData` | M2 T35 S4 | existing closure backlog; Accepted transfer-147: vine initialization and height data. | M2 T24 S1 |
| 6730 | `VineObjectHandler` | M2 T36 S1 | existing closure backlog; Accepted transfer-148: complete vine actor caller chain. | M2 T17 S5; M2 T22 S1; M2 T24 S1 |
| 6746 | `RunVSubs` | M2 T36 S1 | existing closure backlog; Accepted transfer-148: complete vine actor caller chain. | M2 T24 S1 |
| 6752 | `VDrawLoop` | M2 T36 S1 | existing closure backlog; Accepted transfer-148: complete vine actor caller chain. | M2 T24 S1 |
| 6760 | `KillVine` | M2 T36 S1 | existing closure backlog; Accepted transfer-148: complete vine actor caller chain. | M2 T24 S1 |
| 6766 | `WrCMTile` | M2 T36 S1 | existing closure backlog; Accepted transfer-148: complete vine actor caller chain. | M2 T24 S1 |
| 6780 | `ExitVH` | M2 T36 S1 | existing closure backlog; Accepted transfer-148: complete vine actor caller chain. | M2 T24 S1 |
| 6785 | `CannonBitmasks` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6788 | `ProcessCannons` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T22 S1; M2 T24 S1 |
| 6792 | `ThreeSChk` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6809 | `FireCannon` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6832 | `Chk_BB` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6840 | `Next3Slt` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6842 | `ExCannon` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6846 | `BulletBillXSpdData` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6849 | `BulletBillHandler` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T17 S5; M2 T22 S1; M2 T24 S1 |
| 6862 | `SetupBB` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6876 | `ChkDSte` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6880 | `BBFly` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6881 | `RunBBSubs` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6886 | `KillBB` | M2 T31 S2 | existing closure backlog; Accepted necessary cannon/whirlpool dependency correction within active GameEngine S2. | M2 T24 S1 |
| 6891 | `HammerEnemyOfsData` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6895 | `HammerXSpdData` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6898 | `SpawnHammerObj` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6904 | `SetMOfs` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6919 | `NoHammer` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6928 | `ProcHammerObj` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T22 S1; M2 T24 S1 |
| 6952 | `SetHSpd` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6962 | `SetHPos` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6977 | `RunAllH` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6978 | `RunHSubs` | M2 T36 S2 | existing closure backlog; Accepted transfer-149: complete hammer allocation and actor caller chain. | M2 T24 S1 |
| 6988 | `CoinBlock` | M2 T36 S3 | existing closure backlog; Accepted transfer-150: coin creation and misc allocation chain. | M2 T22 S1; M2 T24 S1 |
| 7000 | `SetupJumpCoin` | M2 T36 S3 | existing closure backlog; Accepted transfer-150: coin creation and misc allocation chain. | M2 T21 S2; M2 T21 S5; M2 T22 S1; M2 T24 S1 |
| 7014 | `JCoinC` | M2 T36 S3 | existing closure backlog; Accepted transfer-150: coin creation and misc allocation chain. | M2 T21 S2; M2 T21 S5; M2 T22 S1; M2 T24 S1 |
| 7025 | `FindEmptyMiscSlot` | M2 T36 S3 | existing closure backlog; Accepted transfer-150: coin creation and misc allocation chain. | M2 T16 S2; M2 T22 S1; M2 T24 S1 |
| 7027 | `FMiscLoop` | M2 T36 S3 | existing closure backlog; Accepted transfer-150: coin creation and misc allocation chain. | M2 T24 S1 |
| 7033 | `UseMiscS` | M2 T36 S3 | existing closure backlog; Accepted transfer-150: coin creation and misc allocation chain. | M2 T24 S1 |
| 7038 | `MiscObjectsCore` | M2 T36 S4 | existing closure backlog; Accepted transfer-151: misc dispatch and jumping coin lifetime. | M2 T16 S2; M2 T16 S3; M2 T22 S1; M2 T22 S4; M2 T24 S1 |
| 7040 | `MiscLoop` | M2 T36 S4 | existing closure backlog; Accepted transfer-151: misc dispatch and jumping coin lifetime. | M2 T24 S1 |
| 7053 | `ProcJumpCoin` | M2 T36 S4 | existing closure backlog; Accepted transfer-151: misc dispatch and jumping coin lifetime. | M2 T16 S3; M2 T22 S1; M2 T24 S1 |
| 7071 | `JCoinRun` | M2 T36 S4 | existing closure backlog; Accepted transfer-151: misc dispatch and jumping coin lifetime. | M2 T24 S1 |
| 7088 | `RunJCSubs` | M2 T36 S4 | existing closure backlog; Accepted transfer-151: misc dispatch and jumping coin lifetime. | M2 T24 S1 |
| 7093 | `MiscLoopBack` | M2 T36 S4 | existing closure backlog; Accepted transfer-151: misc dispatch and jumping coin lifetime. | M2 T24 S1 |
| 7100 | `CoinTallyOffsets` | M2 T36 S5 | existing closure backlog; Accepted transfer-152: coin tally, score and HUD handoff. | M2 T24 S1 |
| 7103 | `ScoreOffsets` | M2 T36 S5 | existing closure backlog; Accepted transfer-152: coin tally, score and HUD handoff. | M2 T24 S1 |
| 7106 | `StatusBarNybbles` | M2 T36 S5 | existing closure backlog; Accepted transfer-152: coin tally, score and HUD handoff. | M2 T24 S1 |
| 7109 | `GiveOneCoin` | M2 T36 S5 | existing closure backlog; Accepted transfer-152: coin tally, score and HUD handoff. | M2 T24 S1 |
| 7125 | `CoinPoints` | M2 T36 S5 | existing closure backlog; Accepted transfer-152: coin tally, score and HUD handoff. | M2 T24 S1 |
| 7129 | `AddToScore` | M2 T52 S3 | existing closure backlog; T52 S3 accepted current-equivalence corrective transfer for the A7 floatey-number score chain. | M2 T24 S1 |
| 7134 | `GetSBNybbles` | M2 T36 S5 | existing closure backlog; Accepted transfer-152: coin tally, score and HUD handoff. | M2 T24 S1 |
| 7138 | `UpdateNumber` | M2 T36 S5 | existing closure backlog; Accepted transfer-152: coin tally, score and HUD handoff. | M2 T24 S1 |
| 7145 | `NoZSup` | M2 T36 S5 | existing closure backlog; Accepted transfer-152: coin tally, score and HUD handoff. | M2 T24 S1 |
| 7150 | `SetupPowerUp` | M2 T36 S6 | existing closure backlog; Accepted transfer-153: power-up initialization. | M2 T22 S1; M2 T24 S1 |
| 7163 | `PwrUpJmp` | M2 T36 S6 | existing closure backlog; Accepted transfer-153: power-up initialization. | M2 T24 S1 |
| 7175 | `StrType` | M2 T36 S6 | existing closure backlog; Accepted transfer-153: power-up initialization. | M2 T24 S1 |
| 7176 | `PutBehind` | M2 T36 S6 | existing closure backlog; Accepted transfer-153: power-up initialization. | M2 T24 S1 |
| 7184 | `PowerUpObjHandler` | M2 T37 S1 | existing closure backlog; Accepted transfer-154: complete power-up actor state and child handoff chain. | M2 T17 S5; M2 T22 S1; M2 T24 S1 |
| 7202 | `ShroomM` | M2 T37 S1 | existing closure backlog; Accepted transfer-154: complete power-up actor state and child handoff chain. | M2 T24 S1 |
| 7206 | `GrowThePowerUp` | M2 T37 S1 | existing closure backlog; Accepted transfer-154: complete power-up actor state and child handoff chain. | M2 T22 S1; M2 T24 S1 |
| 7223 | `ChkPUSte` | M2 T37 S1 | existing closure backlog; Accepted transfer-154: complete power-up actor state and child handoff chain. | M2 T24 S1 |
| 7226 | `RunPUSubs` | M2 T37 S1 | existing closure backlog; Accepted transfer-154: complete power-up actor state and child handoff chain. | M2 T16 S3; M2 T22 S1; M2 T24 S1 |
| 7232 | `ExitPUp` | M2 T37 S1 | existing closure backlog; Accepted transfer-154: complete power-up actor state and child handoff chain. | M2 T24 S1 |
| 7241 | `BlockYPosAdderData` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7244 | `PlayerHeadCollision` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T17 S4; M2 T22 S1; M2 T24 S1 |
| 7251 | `DBlockSte` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7265 | `ChkBrick` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7274 | `StartBTmr` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7279 | `ContBTmr` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7282 | `PutOldMT` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7283 | `PutMTileB` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7297 | `SmallBP` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7298 | `BigBP` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7308 | `Unbreak` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7309 | `InvOBit` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T24 S1 |
| 7316 | `InitBlock_XY_Pos` | M2 T37 S2 | existing closure backlog; Accepted transfer-155: complete head-hit and block-position caller chain. | M2 T15 S4; M2 T22 S1; M2 T24 S1 |
| 7332 | `BumpBlock` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T22 S1; M2 T24 S1 |
| 7349 | `BlockCode` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T17 S6; M2 T22 S1; M2 T24 S1 |
| 7363 | `MushFlowerBlock` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T24 S1 |
| 7367 | `StarBlock` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T24 S1 |
| 7371 | `ExtraLifeMushBlock` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T24 S1 |
| 7376 | `VineBlock` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T24 S1 |
| 7381 | `ExitBlockChk` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T24 S1 |
| 7386 | `BrickQBlockMetatiles` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T17 S6; M2 T18 S2; M2 T22 S1; M2 T24 S1 |
| 7393 | `BlockBumpedChk` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T17 S6; M2 T22 S1; M2 T22 S2; M2 T24 S1 |
| 7395 | `BumpChkLoop` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T24 S1 |
| 7400 | `MatchBump` | M2 T37 S3 | existing closure backlog; Accepted transfer-156: original bump/content/lookup chain. | M2 T24 S1 |
| 7404 | `BrickShatter` | M2 T37 S4 | existing closure backlog; Accepted transfer-157: shatter, top coin and chunk creation chain. | M2 T22 S1; M2 T24 S1 |
| 7420 | `CheckTopOfBlock` | M2 T37 S4 | existing closure backlog; Accepted transfer-157: shatter, top coin and chunk creation chain. | M2 T22 S1; M2 T24 S1 |
| 7437 | `TopEx` | M2 T37 S4 | existing closure backlog; Accepted transfer-157: shatter, top coin and chunk creation chain. | M2 T24 S1 |
| 7441 | `SpawnBrickChunks` | M2 T37 S4 | existing closure backlog; Accepted transfer-157: shatter, top coin and chunk creation chain. | M2 T22 S1; M2 T24 S1 |
| 7468 | `BlockObjectsCore` | M2 T37 S5 | existing closure backlog; Accepted transfer-158: block and brick-chunk lifetime chain. | M2 T15 S4; M2 T16 S1; M2 T16 S2; M2 T17 S1; M2 T17 S6; M2 T22 S1; M2 T24 S1 |
| 7500 | `ChkTop` | M2 T37 S5 | existing closure backlog; Accepted transfer-158: block and brick-chunk lifetime chain. | M2 T24 S1 |
| 7506 | `BouncingBlockHandler` | M2 T37 S5 | existing closure backlog; Accepted transfer-158: block and brick-chunk lifetime chain. | M2 T22 S1; M2 T24 S1 |
| 7519 | `KillBlock` | M2 T37 S5 | existing closure backlog; Accepted transfer-158: block and brick-chunk lifetime chain. | M2 T24 S1 |
| 7520 | `UpdSte` | M2 T37 S5 | existing closure backlog; Accepted transfer-158: block and brick-chunk lifetime chain. | M2 T24 S1 |
| 7527 | `BlockObjMT_Updater` | M2 T37 S6 | existing closure backlog; Accepted transfer-159: two-slot block metatile replacement chain. | M2 T18 / S not recorded; M2 T18 S1; M2 T22 S1; M2 T24 S1 |
| 7529 | `UpdateLoop` | M2 T37 S6 | existing closure backlog; Accepted transfer-160: two-slot block metatile replacement chain. | M2 T21 S4; M2 T24 S1 |
| 7546 | `NextBUpd` | M2 T37 S6 | existing closure backlog; Accepted transfer-160: two-slot block metatile replacement chain. | M2 T21 S4; M2 T24 S1 |
| 7555 | `MoveEnemyHorizontally` | M2 T37 S7 | existing closure backlog; Accepted transfer-161: horizontal movement primitive and entries. | M2 T17 / S not recorded; M2 T17 S2; M2 T21 S3; M2 T24 S1 |
| 7561 | `MovePlayerHorizontally` | M2 T37 S7 | existing closure backlog; Accepted transfer-161: horizontal movement primitive and entries. | M2 T15 S4; M2 T17 / S not recorded; M2 T21 S3; M2 T24 S1 |
| 7566 | `MoveObjectHorizontally` | M2 T37 S7 | existing closure backlog; Accepted transfer-161: horizontal movement primitive and entries. | M2 T17 / S not recorded; M2 T17 S2; M2 T20 S2; M2 T21 S3; M2 T24 S1 |
| 7581 | `SaveXSpd` | M2 T37 S7 | existing closure backlog; Accepted transfer-161: horizontal movement primitive and entries. | M2 T21 S3; M2 T24 S1 |
| 7586 | `UseAdder` | M2 T37 S7 | existing closure backlog; Accepted transfer-161: horizontal movement primitive and entries. | M2 T21 S3; M2 T24 S1 |
| 7604 | `ExXMove` | M2 T37 S7 | existing closure backlog; Accepted transfer-161: horizontal movement primitive and entries. | M2 T21 S3; M2 T24 S1 |
| 7611 | `MovePlayerVertically` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7617 | `NoJSChk` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7624 | `MoveD_EnemyVertically` | M2 T37 S8 | existing closure backlog; Accepted transfer-163: vertical adapter implementation and retained-match maintenance. | M2 T17 S5; M2 T19 S2; M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 7630 | `MoveFallingPlatform` | M2 T37 S8 | existing closure backlog; Accepted transfer-163: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7632 | `ContVMove` | M2 T37 S8 | existing closure backlog; Accepted transfer-163: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7636 | `MoveRedPTroopaDown` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7640 | `MoveRedPTroopaUp` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7643 | `MoveRedPTroopa` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7656 | `MoveDropPlatform` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7660 | `MoveEnemySlowVert` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 7662 | `SetMdMax` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T21 S3; M2 T24 S1 |
| 7667 | `MoveJ_EnemyVertically` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 7669 | `SetHiMax` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T19 S2; M2 T21 S3; M2 T24 S1 |
| 7670 | `SetXMoveAmt` | M2 T37 S8 | existing closure backlog; Accepted transfer-162: vertical adapter implementation and retained-match maintenance. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 7678 | `MaxSpdBlockData` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T21 S3; M2 T24 S1 |
| 7681 | `ResidualGravityCode` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T21 S3; M2 T24 S1 |
| 7685 | `ImposeGravityBlock` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T17 / S not recorded; M2 T17 S1; M2 T21 S3; M2 T24 S1 |
| 7691 | `ImposeGravitySprObj` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T17 / S not recorded; M2 T17 S5; M2 T19 S2; M2 T21 S3; M2 T24 S1 |
| 7698 | `MovePlatformDown` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T21 S3; M2 T24 S1 |
| 7702 | `MovePlatformUp` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T21 S3; M2 T24 S1 |
| 7711 | `SetDplSpd` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T21 S3; M2 T24 S1 |
| 7719 | `RedPTroopaGrav` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T21 S3; M2 T24 S1 |
| 7729 | `ImposeGravity` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T16 S2; M2 T17 / S not recorded; M2 T17 S1; M2 T17 S2; M2 T20 S2; M2 T21 S3; M2 T24 S1 |
| 7739 | `AlterYP` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T17 / S not recorded; M2 T21 S3; M2 T24 S1 |
| 7761 | `ChkUpM` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T21 S3; M2 T24 S1 |
| 7784 | `ExVMove` | M2 T37 S9 | existing closure backlog; Accepted transfer-164: common gravity chain. | M2 T17 / S not recorded; M2 T21 S3; M2 T24 S1 |
| 7788 | `EnemiesAndLoopsCore` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T19 / S not recorded; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7796 | `ChkAreaTsk` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7801 | `ChkBowserF` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7807 | `ExitELCore` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7812 | `LoopCmdWorldNumber` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7815 | `LoopCmdPageNumber` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7818 | `LoopCmdYPosition` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7821 | `ExecGameLoopback` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7851 | `ProcLoopCommand` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7857 | `FindLoop` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7875 | `IncMLoop` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7883 | `WrongChk` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7886 | `DoLpBack` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7888 | `InitMLp` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7891 | `InitLCmd` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T21 S5; M2 T24 S1 |
| 7896 | `ChkEnemyFrenzy` | M2 T38 S1 | existing closure backlog; Accepted transfer-165: complete enemy flag/loop/frenzy chain and exact dependencies. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7911 | `ProcessEnemyData` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T17 S6; M2 T19 / S not recorded; M2 T19 S1; M2 T19 S2; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7918 | `CheckEndofBuffer` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T19 S2; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7931 | `CheckRightBounds` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 7950 | `CheckPageCtrlRow` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 7967 | `PositionEnemyObj` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 7983 | `CheckRightExtBounds` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8006 | `CheckForEnemyGroup` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8014 | `BuzzyBeetleMutate` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8020 | `StrID` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8028 | `CheckFrenzyBuffer` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8035 | `StrFre` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8037 | `InitEnemyObject` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8041 | `ExEPar` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8043 | `DoGroup` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8046 | `ParseRow0e` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8064 | `NotUse` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8066 | `CheckThreeBytes` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8072 | `Inc3B` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8073 | `Inc2B` | M2 T38 S2 | existing closure backlog; Accepted transfer-166: complete enemy stream parsing chain, original continuation and initializer handoff. | M2 T21 S5; M2 T24 S1 |
| 8080 | `CheckpointEnemyID` | M2 T38 S3 | existing closure backlog; Accepted transfer-167: checkpoint, initializer vector and no-init return. | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8092 | `InitEnemyRoutines` | M2 T38 S3 | existing closure backlog; Accepted transfer-167: checkpoint, initializer vector and no-init return. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8158 | `NoInitCode` | M2 T38 S3 | existing closure backlog; Accepted transfer-167: checkpoint, initializer vector and no-init return. | M2 T21 S5; M2 T24 S1 |
| 8163 | `InitGoomba` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8169 | `InitPodoboo` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8181 | `InitRetainerObj` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8188 | `NormalXSpdData` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8191 | `InitNormalEnemy` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8196 | `GetESpd` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8197 | `SetESpd` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8202 | `InitRedKoopa` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8210 | `HBroWalkingTimerData` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8213 | `InitHammerBro` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8225 | `InitHorizFlySwimEnemy` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8231 | `InitBloober` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8234 | `SmallBBox` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8239 | `InitRedPTroopa` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8245 | `GetCent` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8248 | `TallBBox` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8249 | `SetBBox` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8252 | `InitVStf` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T17 S5; M2 T21 S5; M2 T24 S1 |
| 8259 | `InitBulletBill` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8268 | `InitCheepCheep` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8279 | `InitLakitu` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8283 | `SetupLakitu` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8289 | `KillLakitu` | M2 T38 S4 | existing closure backlog; Accepted transfer-168: common initializers and shared reset tails. | M2 T21 S5; M2 T24 S1 |
| 8295 | `PRDiffAdjustData` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8300 | `LakituAndSpinyHandler` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8308 | `ChkLak` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8318 | `ChkNoEn` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8323 | `CreateL` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8330 | `RetEOfs` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8331 | `ExLSHand` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8335 | `CreateSpiny` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8355 | `DifLoop` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8376 | `UsePosv` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8377 | `SetSpSpd` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8383 | `SpinyRte` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8390 | `ChpChpEx` | M2 T38 S5 | existing closure backlog; Accepted transfer-169: Lakitu/Spiny allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8394 | `FirebarSpinSpdData` | M2 T38 S6 | existing closure backlog; Accepted transfer-170: firebar initializer and mandatory duplicate child. | M2 T21 S5; M2 T24 S1 |
| 8397 | `FirebarSpinDirData` | M2 T38 S6 | existing closure backlog; Accepted transfer-170: firebar initializer and mandatory duplicate child. | M2 T21 S5; M2 T24 S1 |
| 8400 | `InitLongFirebar` | M2 T38 S6 | existing closure backlog; Accepted transfer-170: firebar initializer and mandatory duplicate child. | M2 T21 S5; M2 T24 S1 |
| 8403 | `InitShortFirebar` | M2 T38 S6 | existing closure backlog; Accepted transfer-170: firebar initializer and mandatory duplicate child. | M2 T21 S5; M2 T24 S1 |
| 8430 | `FlyCCXPositionData` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8436 | `FlyCCXSpeedData` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8441 | `FlyCCTimerData` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8444 | `InitFlyingCheepCheep` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8457 | `MaxCC` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8473 | `GSeed` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8483 | `RSeed` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8503 | `D2XPos1` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8513 | `D2XPos2` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8519 | `FinCCSt` | M2 T38 S7 | existing closure backlog; Accepted transfer-171: complete flying-fish initializer. | M2 T21 S5; M2 T24 S1 |
| 8529 | `InitBowser` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8551 | `DuplicateEnemyObj` | M2 T39 S1 | existing closure backlog; Accepted transfer-173: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8553 | `FSLoop` | M2 T39 S1 | existing closure backlog; Accepted transfer-173: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8569 | `FlmEx` | M2 T39 S1 | existing closure backlog; Accepted transfer-173: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8573 | `FlameYPosData` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8576 | `FlameYMFAdderData` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8579 | `InitBowserFlame` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8597 | `SetFrT` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8604 | `PutAtRightExtent` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8615 | `SpawnFromMouth` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8635 | `SetMF` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T21 S5; M2 T24 S1 |
| 8640 | `FinishFlame` | M2 T39 S1 | existing closure backlog; Accepted transfer-172: Bowser/flame initializer chain and dependency. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8653 | `FireworksXPosData` | M2 T39 S2 | existing closure backlog; Accepted transfer-174: complete fireworks initializer chain. | M2 T21 S5; M2 T24 S1 |
| 8656 | `FireworksYPosData` | M2 T39 S2 | existing closure backlog; Accepted transfer-174: complete fireworks initializer chain. | M2 T21 S5; M2 T24 S1 |
| 8659 | `InitFireworks` | M2 T39 S2 | existing closure backlog; Accepted transfer-174: complete fireworks initializer chain. | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8666 | `StarFChk` | M2 T39 S2 | existing closure backlog; Accepted transfer-174: complete fireworks initializer chain. | M2 T21 S5; M2 T24 S1 |
| 8697 | `ExitFWk` | M2 T39 S2 | existing closure backlog; Accepted transfer-174: complete fireworks initializer chain. | M2 T21 S5; M2 T24 S1 |
| 8701 | `Bitmasks` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8704 | `Enemy17YPosData` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8707 | `SwimCC_IDData` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8710 | `BulletBillCheepCheep` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8722 | `ChkW2` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8726 | `Get17ID` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8730 | `Set17ID` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8736 | `GetRBit` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8738 | `ChkRBit` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8746 | `AddFBit` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8755 | `DoBulletBills` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8757 | `BB_SLoop` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8765 | `ExF17` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8767 | `FireBulletBill` | M2 T39 S3 | existing closure backlog; Accepted transfer-175: complete Bullet Bill / swimming-fish allocation chain. | M2 T21 S5; M2 T24 S1 |
| 8780 | `HandleGroupEnemies` | M2 T39 S4 | existing closure backlog; Accepted transfer-176: complete grouped enemy record chain. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8792 | `PullID` | M2 T39 S4 | existing closure backlog; Accepted transfer-176: complete grouped enemy record chain. | M2 T21 S5; M2 T24 S1 |
| 8793 | `SnglID` | M2 T39 S4 | existing closure backlog; Accepted transfer-176: complete grouped enemy record chain. | M2 T21 S5; M2 T24 S1 |
| 8798 | `SetYGp` | M2 T39 S4 | existing closure backlog; Accepted transfer-176: complete grouped enemy record chain. | M2 T21 S5; M2 T24 S1 |
| 8808 | `CntGrp` | M2 T39 S4 | existing closure backlog; Accepted transfer-176: complete grouped enemy record chain. | M2 T21 S5; M2 T24 S1 |
| 8809 | `GrLoop` | M2 T39 S4 | existing closure backlog; Accepted transfer-176: complete grouped enemy record chain. | M2 T21 S5; M2 T24 S1 |
| 8810 | `GSltLp` | M2 T39 S4 | existing closure backlog; Accepted transfer-176: complete grouped enemy record chain. | M2 T21 S5; M2 T24 S1 |
| 8835 | `NextED` | M2 T39 S4 | existing closure backlog; Accepted transfer-176: complete grouped enemy record chain. | M2 T21 S5; M2 T24 S1 |
| 8839 | `InitPiranhaPlant` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T21 S5; M2 T24 S1 |
| 8855 | `InitEnemyFrenzy` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T19 S3; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 8872 | `NoFrenzyCode` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T21 S5; M2 T24 S1 |
| 8877 | `EndFrenzy` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 8879 | `LakituChk` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T21 S5; M2 T24 S1 |
| 8884 | `NextFSlot` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T21 S5; M2 T24 S1 |
| 8893 | `InitJumpGPTroopa` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T21 S5; M2 T24 S1 |
| 8898 | `TallBBox2` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T21 S5; M2 T24 S1 |
| 8899 | `SetBBox2` | M2 T39 S5 | existing closure backlog; Accepted transfer-177: small initializers and frenzy dispatch/stop chain. | M2 T21 S5; M2 T24 S1 |
| 8904 | `InitBalPlatform` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8911 | `AlignP` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8917 | `SetBPA` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8925 | `InitDropPlatform` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8932 | `InitHoriPlatform` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8939 | `InitVertPlatform` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8947 | `SetYO` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8955 | `CommonPlatCode` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8957 | `SPBBox` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8964 | `CasPBB` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8969 | `LargeLiftUp` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8973 | `LargeLiftDown` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8976 | `LargeLiftBBox` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8981 | `PlatLiftUp` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8990 | `PlatLiftDown` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 8998 | `CommonSmallLift` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 9007 | `PlatPosDataLow` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 9010 | `PlatPosDataHigh` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 9013 | `PosPlatform` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 9025 | `EndOfEnemyInitCode` | M2 T39 S6 | existing closure backlog; Accepted transfer-178: original platform initialization and positioning chain. | M2 T21 S5; M2 T24 S1 |
| 9030 | `RunEnemyObjectsCore` | M2 T39 S7 | existing closure backlog; Accepted transfer-179: actor vector and retainer call boundaries. | M2 T21 S5; M2 T24 S1 |
| 9038 | `JmpEO` | M2 T39 S7 | existing closure backlog; Accepted transfer-179: actor vector and retainer call boundaries. | M2 T21 S5; M2 T24 S1 |
| 9080 | `NoRunCode` | M2 T39 S7 | existing closure backlog; Accepted transfer-180: actor vector and retainer call boundaries. | M2 T21 S5; M2 T24 S1 |
| 9085 | `RunRetainerObj` | M2 T39 S7 | existing closure backlog; Accepted transfer-179: actor vector and retainer call boundaries. | M2 T21 S5; M2 T24 S1 |
| 9092 | `RunNormalEnemies` | M2 T39 S8 | existing closure backlog; Accepted transfer-181: normal actor caller and movement vector. | M2 T17 S5; M2 T19 S4; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 9105 | `SkipMove` | M2 T39 S8 | existing closure backlog; Accepted transfer-181: normal actor caller and movement vector. | M2 T21 S5; M2 T24 S1 |
| 9107 | `EnemyMovementSubs` | M2 T39 S8 | existing closure backlog; Accepted transfer-181: normal actor caller and movement vector. | M2 T21 S5; M2 T24 S1 |
| 9135 | `NoMoveCode` | M2 T39 S8 | existing closure backlog; Accepted transfer-181: normal actor caller and movement vector. | M2 T21 S5; M2 T24 S1 |
| 9140 | `RunBowserFlame` | M2 T39 S9 | existing closure backlog; Accepted transfer-182: special actor/platform callers and shared erasure. | M2 T21 S5; M2 T24 S1 |
| 9150 | `RunFirebarObj` | M2 T39 S9 | existing closure backlog; Accepted transfer-182: special actor/platform callers and shared erasure. | M2 T21 S5; M2 T24 S1 |
| 9156 | `RunSmallPlatform` | M2 T39 S9 | existing closure backlog; Accepted transfer-182: special actor/platform callers and shared erasure. | M2 T19 S4; M2 T21 S5; M2 T24 S1; M2 T5 / S not recorded |
| 9168 | `RunLargePlatform` | M2 T39 S9 | existing closure backlog; Accepted transfer-182: special actor/platform callers and shared erasure. | M2 T19 S4; M2 T21 S5; M2 T24 S1; M2 T5 / S not recorded |
| 9176 | `SkipPT` | M2 T39 S9 | existing closure backlog; Accepted transfer-182: special actor/platform callers and shared erasure. | M2 T21 S5; M2 T24 S1 |
| 9182 | `LargePlatformSubroutines` | M2 T39 S9 | existing closure backlog; Accepted transfer-182: special actor/platform callers and shared erasure. | M2 T21 S5; M2 T24 S1 |
| 9198 | `EraseEnemyObject` | M2 T39 S9 | existing closure backlog; Accepted transfer-183: special actor/platform callers and shared erasure. | M2 T21 S5; M2 T24 S1 |
| 9212 | `MovePodoboo` | M2 T40 S1 | existing closure backlog; Accepted transfer-184: complete Podoboo movement caller. | M2 T21 S5; M2 T24 S1 |
| 9224 | `PdbM` | M2 T40 S1 | existing closure backlog; Accepted transfer-184: complete Podoboo movement caller. | M2 T21 S5; M2 T24 S1 |
| 9229 | `HammerThrowTmrData` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9232 | `XSpeedAdderData` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9235 | `RevivedXSpeed` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9238 | `ProcHammerBro` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9243 | `ChkJH` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9260 | `DecHT` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9263 | `HammerBroJumpLData` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9266 | `HammerBroJumpCode` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9285 | `SetHJ` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9295 | `HJump` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9301 | `MoveHammerBroXDir` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9307 | `Shimmy` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9316 | `SetShim` | M2 T40 S2 | existing closure backlog; Accepted transfer-185: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9318 | `MoveNormalEnemy` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T17 S5; M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 9336 | `FallE` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T19 S5; M2 T21 S5; M2 T24 S1 |
| 9347 | `MEHor` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9349 | `SlowM` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9350 | `SteadM` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9355 | `AddHS` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9363 | `ReviveStunned` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9377 | `SetRSpd` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9381 | `MoveDefeatedEnemy` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9385 | `ChkKillGoomba` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9392 | `NKGmba` | M2 T40 S2 | existing closure backlog; Accepted transfer-186: Hammer Bro and normal movement chain. | M2 T21 S5; M2 T24 S1 |
| 9396 | `MoveJumpingEnemy` | M2 T40 S3 | existing closure backlog; Accepted transfer-187: jumping/red Paratroopa movement chain. | M2 T17 S5; M2 T21 S5; M2 T24 S1 |
| 9402 | `ProcMoveRedPTroopa` | M2 T40 S3 | existing closure backlog; Accepted transfer-187: jumping/red Paratroopa movement chain. | M2 T21 S5; M2 T24 S1 |
| 9414 | `NoIncPT` | M2 T40 S3 | existing closure backlog; Accepted transfer-187: jumping/red Paratroopa movement chain. | M2 T21 S5; M2 T24 S1 |
| 9416 | `MoveRedPTUpOrDown` | M2 T40 S3 | existing closure backlog; Accepted transfer-187: jumping/red Paratroopa movement chain. | M2 T21 S5; M2 T24 S1 |
| 9421 | `MovPTDwn` | M2 T40 S3 | existing closure backlog; Accepted transfer-187: jumping/red Paratroopa movement chain. | M2 T21 S5; M2 T24 S1 |
| 9427 | `MoveFlyGreenPTroopa` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9438 | `YSway` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9443 | `NoMGPT` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9445 | `XMoveCntr_GreenPTroopa` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9448 | `XMoveCntr_Platform` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9460 | `NoIncXM` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9461 | `IncPXM` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9463 | `DecSeXM` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9468 | `MoveWithXMCntrs` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9481 | `XMRight` | M2 T40 S4 | existing closure backlog; Accepted transfer-188: green Paratroopa/shared X-counter chain. | M2 T21 S5; M2 T24 S1 |
| 9490 | `BlooberBitmasks` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9493 | `MoveBloober` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9506 | `FBLeft` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9510 | `SBMDir` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9512 | `BlooberSwim` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9520 | `SwimX` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9532 | `LeftSwim` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9542 | `MoveDefeatedBloober` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T17 S5; M2 T21 S5; M2 T24 S1 |
| 9545 | `ProcSwimmingB` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9565 | `BSwimE` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9567 | `SlowSwim` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9579 | `NoSSw` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9581 | `ChkForFloatdown` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9585 | `Floatdown` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9590 | `NoFD` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9592 | `ChkNearPlayer` | M2 T40 S5 | existing closure backlog; Accepted transfer-189: Bloober movement/swimming chain. | M2 T21 S5; M2 T24 S1 |
| 9603 | `MoveBulletBill` | M2 T40 S6 | existing closure backlog; Accepted transfer-190: Bullet Bill movement chain. | M2 T21 S5; M2 T24 S1 |
| 9608 | `NotDefB` | M2 T40 S6 | existing closure backlog; Accepted transfer-190: Bullet Bill movement chain. | M2 T21 S5; M2 T24 S1 |
| 9616 | `SwimCCXMoveData` | M2 T40 S7 | existing closure backlog; Accepted transfer-191: swimming Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9620 | `MoveSwimmingCheepCheep` | M2 T40 S7 | existing closure backlog; Accepted transfer-191: swimming Cheep-Cheep movement chain. | M2 T17 S5; M2 T21 S5; M2 T24 S1 |
| 9625 | `CCSwim` | M2 T40 S7 | existing closure backlog; Accepted transfer-191: swimming Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9660 | `CCSwimUpwards` | M2 T40 S7 | existing closure backlog; Accepted transfer-191: swimming Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9671 | `ChkSwimYPos` | M2 T40 S7 | existing closure backlog; Accepted transfer-191: swimming Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9682 | `YPDiff` | M2 T40 S7 | existing closure backlog; Accepted transfer-191: swimming Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9686 | `ExSwCC` | M2 T40 S7 | existing closure backlog; Accepted transfer-191: swimming Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9703 | `FirebarPosLookupTbl` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9716 | `FirebarMirrorData` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9719 | `FirebarTblOffsets` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9723 | `FirebarYPos` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9726 | `ProcFirebar` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9737 | `SusFbar` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9745 | `SkpFSte` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9748 | `SetupGFB` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9766 | `SetMFbar` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9769 | `DrawFbar` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9778 | `NextFbar` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9782 | `SkipFBar` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9784 | `DrawFirebar_Collision` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9793 | `AddHA` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9803 | `SubtR1` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9805 | `ChkFOfs` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9809 | `VAHandl` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9817 | `AddVA` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9819 | `SetVFbr` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9822 | `FirebarCollision` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9838 | `AdjSm` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9844 | `BigJp` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9845 | `FBCLoop` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9851 | `ChkVFBD` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9866 | `ChkFBCl` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9868 | `Chk2Ofs` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9877 | `ChgSDir` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9882 | `SetSDir` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9889 | `NoColFB` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9896 | `GetFirebarPosition` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9904 | `GetHAdder` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9922 | `GetVAdder` | M2 T40 S8 | existing closure backlog; Accepted transfer-192: firebar position/drawing/collision chain. | M2 T21 S5; M2 T24 S1 |
| 9941 | `PRandomSubtracter` | M2 T40 S9 | existing closure backlog; Accepted transfer-193: flying Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9944 | `FlyCCBPriority` | M2 T40 S9 | existing closure backlog; Accepted transfer-193: flying Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9947 | `MoveFlyingCheepCheep` | M2 T40 S9 | existing closure backlog; Accepted transfer-193: flying Cheep-Cheep movement chain. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 9954 | `FlyCC` | M2 T40 S9 | existing closure backlog; Accepted transfer-193: flying Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9971 | `AddCCF` | M2 T40 S9 | existing closure backlog; Accepted transfer-193: flying Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9982 | `BPGet` | M2 T40 S9 | existing closure backlog; Accepted transfer-193: flying Cheep-Cheep movement chain. | M2 T21 S5; M2 T24 S1 |
| 9990 | `LakituDiffAdj` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 9993 | `MoveLakitu` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 9998 | `ChkLS` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10005 | `Fr12S` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10008 | `LdLDa` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10013 | `SetLSpd` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10024 | `SetLMov` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10027 | `PlayerLakituDiff` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T19 S3; M2 T21 S5; M2 T24 S1 |
| 10037 | `ChkLakDif` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10053 | `SetLMovD` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10055 | `ChkPSpeed` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10073 | `ChkSpinyO` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10078 | `ChkEmySpd` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10081 | `SubDifAdj` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10083 | `SPixelLak` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10087 | `ExMoveLak` | M2 T40 S10 | existing closure backlog; Accepted transfer-194: Lakitu movement/distance chain. | M2 T21 S5; M2 T24 S1 |
| 10092 | `BridgeCollapseData` | M2 T41 S1 | existing closure backlog; Accepted transfer-195: bridge collapse chain. | M2 T21 S5; M2 T24 S1 |
| 10098 | `BridgeCollapse` | M2 T41 S1 | existing closure backlog; Accepted transfer-195: bridge collapse chain. | M2 T21 S5; M2 T24 S1 |
| 10111 | `SetM2` | M2 T41 S1 | existing closure backlog; Accepted transfer-195: bridge collapse chain. | M2 T21 S5; M2 T24 S1 |
| 10116 | `MoveD_Bowser` | M2 T41 S1 | existing closure backlog; Accepted transfer-195: bridge collapse chain. | M2 T21 S5; M2 T24 S1 |
| 10120 | `RemoveBridge` | M2 T41 S1 | existing closure backlog; Accepted transfer-195: bridge collapse chain. | M2 T21 S5; M2 T24 S1 |
| 10152 | `NoBFall` | M2 T41 S1 | existing closure backlog; Accepted transfer-195: bridge collapse chain. | M2 T21 S5; M2 T24 S1 |
| 10156 | `PRandomRange` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10159 | `RunBowser` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10167 | `KillAllEnemies` | M2 T41 S2 | existing closure backlog; Accepted transfer-197: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10169 | `KillLoop` | M2 T41 S2 | existing closure backlog; Accepted transfer-197: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10176 | `BowserControl` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10182 | `ChkMouth` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10185 | `FeetTmr` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10192 | `ResetMDr` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10197 | `B_FaceP` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10211 | `GetPRCmp` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10222 | `GetDToO` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10237 | `CompDToO` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10240 | `HammerChk` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10250 | `SetHmrTmr` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10258 | `SkipToFB` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10259 | `MakeBJump` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10265 | `ChkFireB` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10270 | `SpawnFBr` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10283 | `SetFBTmr` | M2 T41 S2 | existing closure backlog; Accepted transfer-196: Bowser control/erasure chain. | M2 T21 S5; M2 T24 S1 |
| 10289 | `BowserGfxHandler` | M2 T41 S3 | existing closure backlog; Accepted transfer-198: Bowser front/rear orchestration. | M2 T21 S5; M2 T24 S1 |
| 10296 | `CopyFToR` | M2 T41 S3 | existing closure backlog; Accepted transfer-198: Bowser front/rear orchestration. | M2 T21 S5; M2 T24 S1 |
| 10321 | `ExBGfxH` | M2 T41 S3 | existing closure backlog; Accepted transfer-198: Bowser front/rear orchestration. | M2 T21 S5; M2 T24 S1 |
| 10323 | `ProcessBowserHalf` | M2 T41 S3 | existing closure backlog; Accepted transfer-198: Bowser front/rear orchestration. | M2 T21 S5; M2 T24 S1 |
| 10337 | `FlameTimerData` | M2 T41 S4 | existing closure backlog; Accepted transfer-200: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10340 | `SetFlameTimer` | M2 T41 S4 | existing closure backlog; Accepted transfer-200: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10347 | `ExFl` | M2 T41 S4 | existing closure backlog; Accepted transfer-200: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10349 | `ProcBowserFlame` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T19 S3; M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10356 | `SFlmX` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10374 | `SetGfxF` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10384 | `FlmeAt` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10388 | `DrawFlameLoop` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10417 | `M3FOfs` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10423 | `M2FOfs` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10429 | `M1FOfs` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10434 | `ExFlmeD` | M2 T41 S4 | existing closure backlog; Accepted transfer-199: flame actor/timer chain. | M2 T21 S5; M2 T24 S1 |
| 10438 | `RunFireworks` | M2 T41 S5 | existing closure backlog; Accepted transfer-201: fireworks lifetime/score tail. | M2 T19 S3; M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10447 | `SetupExpl` | M2 T41 S5 | existing closure backlog; Accepted transfer-201: fireworks lifetime/score tail. | M2 T21 S5; M2 T24 S1 |
| 10457 | `FireworksSoundScore` | M2 T41 S5 | existing closure backlog; Accepted transfer-201: fireworks lifetime/score tail. | M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10468 | `StarFlagYPosAdder` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10471 | `StarFlagXPosAdder` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10474 | `StarFlagTileData` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10477 | `RunStarFlagObj` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T18 S2; M2 T19 S3; M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10491 | `GameTimerFireworks` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10503 | `SetFWC` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10506 | `IncrementSFTask1` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10509 | `StarFlagExit` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T18 S2; M2 T21 S5; M2 T24 / S not recorded; M2 T24 S1 |
| 10512 | `AwardGameTimerPoints` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T19 S4; M2 T21 S5; M2 T24 S1 |
| 10522 | `NoTTick` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10529 | `EndAreaPoints` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10534 | `ELPGive` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10543 | `RaiseFlagSetoffFWorks` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10549 | `SetoffF` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10555 | `DrawStarFlag` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T18 S2; M2 T21 S5; M2 T24 S1 |
| 10559 | `DSFLoop` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10580 | `DrawFlagSetTimer` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10585 | `IncrementSFTask2` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10589 | `DelayToAreaEnd` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10596 | `StarFlagExit2` | M2 T41 S6 | existing closure backlog; Accepted transfer-202: star-flag and end-area score chain. | M2 T21 S5; M2 T24 S1 |
| 10602 | `MovePiranhaPlant` | M2 T41 S7 | existing closure backlog; Accepted transfer-203: Piranha movement and pipe priority. | M2 T21 S5; M2 T24 S1 |
| 10619 | `ChkPlayerNearPipe` | M2 T41 S7 | existing closure backlog; Accepted transfer-203: Piranha movement and pipe priority. | M2 T21 S5; M2 T24 S1 |
| 10624 | `ReversePlantSpeed` | M2 T41 S7 | existing closure backlog; Accepted transfer-203: Piranha movement and pipe priority. | M2 T21 S5; M2 T24 S1 |
| 10632 | `SetupToMovePPlant` | M2 T41 S7 | existing closure backlog; Accepted transfer-203: Piranha movement and pipe priority. | M2 T21 S5; M2 T24 S1 |
| 10638 | `RiseFallPiranhaPlant` | M2 T41 S7 | existing closure backlog; Accepted transfer-203: Piranha movement and pipe priority. | M2 T21 S5; M2 T24 S1 |
| 10656 | `PutinPipe` | M2 T41 S7 | existing closure backlog; Accepted transfer-203: Piranha movement and pipe priority. | M2 T21 S5; M2 T24 S1 |
| 10664 | `FirebarSpin` | M2 T41 S8 | existing closure backlog; Accepted transfer-204: Firebar angular primitive. | M2 T21 S5; M2 T24 S1 |
| 10677 | `SpinCounterClockwise` | M2 T41 S8 | existing closure backlog; Accepted transfer-204: Firebar angular primitive. | M2 T21 S5; M2 T24 S1 |
| 10692 | `BalancePlatform` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10697 | `DoBPl` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10701 | `CheckBalPlatform` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10709 | `ChkForFall` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10720 | `MakePlatformFall` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10723 | `ChkOtherForFall` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10733 | `ChkToMoveBalPlat` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10750 | `ColFlg` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10752 | `PlatUp` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10754 | `PlatSt` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10756 | `PlatDn` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10758 | `DoOtherPlatform` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10771 | `DrawEraseRope` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10796 | `EraseR1` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10800 | `OtherRope` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10819 | `EraseR2` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10822 | `EndRp` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10828 | `ExitRp` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10831 | `SetupPlatformRope` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10840 | `GetLRp` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10857 | `GetHRp` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10883 | `ExPRp` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10885 | `InitPlatformFall` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10898 | `StopPlatforms` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10904 | `PlatformFall` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10916 | `ExPF` | M2 T41 S9 | existing closure backlog; Accepted transfer-205: complete balance/rope/fall chain. | M2 T21 S5; M2 T24 S1 |
| 10921 | `YMovingPlatform` | M2 T41 S10 | existing closure backlog; Accepted transfer-206: complete vertical-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10933 | `SkipIY` | M2 T41 S10 | existing closure backlog; Accepted transfer-206: complete vertical-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10935 | `ChkYCenterPos` | M2 T41 S10 | existing closure backlog; Accepted transfer-206: complete vertical-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10941 | `YMDown` | M2 T41 S10 | existing closure backlog; Accepted transfer-206: complete vertical-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10943 | `ChkYPCollision` | M2 T41 S10 | existing closure backlog; Accepted transfer-206: complete vertical-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10947 | `ExYPl` | M2 T41 S10 | existing closure backlog; Accepted transfer-206: complete vertical-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10952 | `XMovingPlatform` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10959 | `PositionPlayerOnHPlat` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10969 | `PPHSubt` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10970 | `SetPVar` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10973 | `ExXMP` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10977 | `DropPlatform` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10982 | `ExDPl` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10987 | `RightPlatform` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10995 | `ExRPl` | M2 T41 S11 | existing closure backlog; Accepted transfer-207: complete horizontal/drop/right-platform chain. | M2 T21 S5; M2 T24 S1 |
| 10999 | `MoveLargeLiftPlat` | M2 T41 S12 | existing closure backlog; Accepted transfer-208: large/small lift chain. | M2 T21 S5; M2 T24 S1 |
| 11003 | `MoveSmallPlatform` | M2 T41 S12 | existing closure backlog; Accepted transfer-208: large/small lift chain. | M2 T21 S5; M2 T24 S1 |
| 11007 | `MoveLiftPlatforms` | M2 T41 S12 | existing closure backlog; Accepted transfer-208: large/small lift chain. | M2 T21 S5; M2 T24 S1 |
| 11019 | `ChkSmallPlatCollision` | M2 T41 S12 | existing closure backlog; Accepted transfer-208: large/small lift chain. | M2 T21 S5; M2 T24 S1 |
| 11023 | `ExLiftP` | M2 T41 S12 | existing closure backlog; Accepted transfer-208: large/small lift chain. | M2 T21 S5; M2 T24 S1 |
| 11031 | `OffscreenBoundsCheck` | M2 T41 S13 | existing closure backlog; Accepted transfer-209: complete offscreen bounds chain. | M2 T21 S5; M2 T24 S1 |
| 11041 | `LimitB` | M2 T41 S13 | existing closure backlog; Accepted transfer-209: complete offscreen bounds chain. | M2 T21 S5; M2 T24 S1 |
| 11042 | `ExtendLB` | M2 T41 S13 | existing closure backlog; Accepted transfer-209: complete offscreen bounds chain. | M2 T21 S5; M2 T24 S1 |
| 11074 | `TooFar` | M2 T41 S13 | existing closure backlog; Accepted transfer-209: complete offscreen bounds chain. | M2 T21 S5; M2 T24 S1 |
| 11075 | `ExScrnBd` | M2 T41 S13 | existing closure backlog; Accepted transfer-209: complete offscreen bounds chain. | M2 T21 S5; M2 T24 S1 |
| 11085 | `FireballEnemyCollision` | M2 T42 S1 | existing closure backlog; Accepted transfer-210: complete fireball-enemy scan caller. | M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11101 | `FireballEnemyCDLoop` | M2 T42 S1 | existing closure backlog; Accepted transfer-210: complete fireball-enemy scan caller. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11115 | `GoombaDie` | M2 T42 S1 | existing closure backlog; Accepted transfer-210: complete fireball-enemy scan caller. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11120 | `NotGoomba` | M2 T42 S1 | existing closure backlog; Accepted transfer-210: complete fireball-enemy scan caller. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11135 | `NoFToECol` | M2 T42 S1 | existing closure backlog; Accepted transfer-210: complete fireball-enemy scan caller. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11141 | `ExitFBallEnemy` | M2 T42 S1 | existing closure backlog; Accepted transfer-210: complete fireball-enemy scan caller. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11145 | `BowserIdentities` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11148 | `HandleEnemyFBallCol` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T16 S3; M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11160 | `ChkBuzzyBeetle` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11167 | `HurtBowser` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11182 | `SetDBSte` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11189 | `ChkOtherEnemies` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11197 | `ShellOrBlockDefeat` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11204 | `StnE` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11215 | `GoombaPoints` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11220 | `EnemySmackScore` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11224 | `ExHCF` | M2 T42 S2 | existing closure backlog; Accepted transfer-211: complete fireball-hit response. | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11228 | `PlayerHammerCollision` | M2 T42 S3 | existing closure backlog; Accepted transfer-212: complete hammer contact chain. | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11256 | `ClHCol` | M2 T42 S3 | existing closure backlog; Accepted transfer-212: complete hammer contact chain. | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11258 | `ExPHC` | M2 T42 S3 | existing closure backlog; Accepted transfer-212: complete hammer contact chain. | M2 T17 S5; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 11262 | `HandlePowerUpCollision` | M2 T42 S4 | existing closure backlog; Accepted transfer-213: complete power-up pickup chain. | M2 T18 S3; M2 T21 S3; M2 T24 S1 |
| 11279 | `Shroom_Flower_PUp` | M2 T42 S4 | existing closure backlog; Accepted transfer-213: complete power-up pickup chain. | M2 T21 S3; M2 T24 S1 |
| 11292 | `SetFor1Up` | M2 T42 S4 | existing closure backlog; Accepted transfer-213: complete power-up pickup chain. | M2 T21 S3; M2 T24 S1 |
| 11297 | `UpToSuper` | M2 T42 S4 | existing closure backlog; Accepted transfer-213: complete power-up pickup chain. | M2 T21 S3; M2 T24 S1 |
| 11302 | `UpToFiery` | M2 T42 S4 | existing closure backlog; Accepted transfer-213: complete power-up pickup chain. | M2 T18 S3; M2 T21 S3; M2 T24 S1 |
| 11305 | `NoPUp` | M2 T42 S4 | existing closure backlog; Accepted transfer-213: complete power-up pickup chain. | M2 T21 S3; M2 T24 S1 |
| 11309 | `ResidualXSpdData` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11312 | `KickedShellXSpdData` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11315 | `DemotedKoopaXSpdData` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11318 | `PlayerEnemyCollision` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T17 S5; M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 11339 | `NoPECol` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11341 | `CheckForPUpCollision` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11346 | `EColl` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11350 | `KickedShellPtsData` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11353 | `HandlePECollisions` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11398 | `KSPts` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11399 | `ExPEC` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11401 | `ChkForPlayerInjury` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11405 | `ChkInj` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11413 | `ChkETmrs` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11421 | `TInjE` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11426 | `InjurePlayer` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1; M2 T6 / S not recorded |
| 11430 | `ForceInjury` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11440 | `SetKRout` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11441 | `SetPRout` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11448 | `ExInjColRoutines` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11452 | `KillPlayer` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1; M2 T6 / S not recorded |
| 11461 | `StompedEnemyPtsData` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11464 | `EnemyStomped` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11490 | `EnemyStompedPts` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11506 | `ChkForDemoteKoopa` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11521 | `RevivalRateData` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11524 | `HandleStompedShellE` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11536 | `SBnce` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11540 | `ChkEnemyFaceRight` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11545 | `LInj` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11549 | `EnemyFacePlayer` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11554 | `SFcRt` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11558 | `SetupFloateyNumber` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 11566 | `ExSFN` | M2 T42 S5 | existing closure backlog; Accepted transfer-214: complete player contact/response chain. | M2 T21 S3; M2 T24 S1 |
| 11571 | `SetBitsMask` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 11574 | `ClearBitsMask` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11577 | `EnemiesCollision` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 11595 | `ECLoop` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11629 | `YesEC` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11632 | `NoEnemyCollision` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11637 | `ReadyNextEnemy` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11644 | `ExitECRoutine` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11648 | `ProcEnemyCollisions` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 11667 | `ShellCollisions` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11680 | `ExitProcessEColl` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11683 | `ProcSecondEnemyColl` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11701 | `MoveEOfs` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11707 | `EnemyTurnAround` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11721 | `RXSpd` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11729 | `ExTA` | M2 T42 S6 | existing closure backlog; Accepted transfer-215: complete enemy-pair collision chain. | M2 T21 S3; M2 T24 S1 |
| 11734 | `LargePlatformCollision` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11748 | `ChkForPlayerC_LargeP` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11762 | `ExLPC` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11768 | `SmallPlatformCollision` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11777 | `ChkSmallPlatLoop` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11788 | `MoveBoundBox` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11799 | `ExSPC` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11804 | `ProcSPlatCollisions` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11807 | `ProcLPlatCollisions` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11818 | `ChkForTopCollision` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11834 | `SetCollisionFlag` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11841 | `PlatformSideCollisions` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11855 | `SideC` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11856 | `NoSideC` | M2 T42 S7 | existing closure backlog; Accepted transfer-216: complete platform collision chain. | M2 T21 S3; M2 T24 S1 |
| 11861 | `PlayerPosSPlatData` | M2 T42 S8 | existing closure backlog; Accepted transfer-217: complete platform positioning chain. | M2 T21 S3; M2 T24 S1 |
| 11864 | `PositionPlayerOnS_Plat` | M2 T42 S8 | existing closure backlog; Accepted transfer-217: complete platform positioning chain. | M2 T21 S3; M2 T24 S1 |
| 11871 | `PositionPlayerOnVPlat` | M2 T42 S8 | existing closure backlog; Accepted transfer-217: complete platform positioning chain. | M2 T21 S3; M2 T24 S1 |
| 11888 | `ExPlPos` | M2 T42 S8 | existing closure backlog; Accepted transfer-217: complete platform positioning chain. | M2 T21 S3; M2 T24 S1 |
| 11892 | `CheckPlayerVertical` | M2 T42 S9 | existing closure backlog; Accepted transfer-218: complete collision preflight chain. | M2 T21 S3; M2 T24 S1 |
| 11901 | `ExCPV` | M2 T42 S9 | existing closure backlog; Accepted transfer-218: complete collision preflight chain. | M2 T21 S3; M2 T24 S1 |
| 11905 | `GetEnemyBoundBoxOfs` | M2 T42 S9 | existing closure backlog; Accepted transfer-218: complete collision preflight chain. | M2 T21 S3; M2 T24 S1 |
| 11908 | `GetEnemyBoundBoxOfsArg` | M2 T42 S9 | existing closure backlog; Accepted transfer-218: complete collision preflight chain. | M2 T21 S3; M2 T24 S1 |
| 11924 | `PlayerBGUpperExtent` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 11927 | `PlayerBGCollision` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 11942 | `SetFallS` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 11943 | `SetPSte` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 11944 | `ChkOnScr` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 11952 | `ExPBGCol` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 11954 | `ChkCollSize` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 11964 | `GBBAdr` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 11971 | `HeadChk` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 11992 | `SolidOrClimb` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 11997 | `NYSpd` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12000 | `DoFootCheck` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12019 | `AwardTouchedCoin` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12022 | `ChkFootMTile` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 12030 | `ContChk` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12040 | `LandPlyr` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12049 | `InitSteP` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12052 | `DoPlayerSideCheck` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 12059 | `SideCheckLoop` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12075 | `BHalf` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12086 | `ExSCH` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12088 | `CheckSideMTiles` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12094 | `ContSChk` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12101 | `ChkPBtm` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12111 | `PipeDwnS` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12115 | `PlyrPipe` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12124 | `SetCATmr` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12126 | `ChkGERtn` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12140 | `StopPlayerMove` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12142 | `ExCSM` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12144 | `AreaChangeTimerData` | M2 T43 S1 | existing closure backlog; Accepted transfer-219: complete player terrain root chain. | M2 T21 S3; M2 T24 S1 |
| 12147 | `HandleCoinMetatile` | M2 T43 S2 | existing closure backlog; Accepted transfer-220: coin and axe effects chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12152 | `HandleAxeMetatile` | M2 T43 S2 | existing closure backlog; Accepted transfer-220: coin and axe effects chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1; M2 T6 / S not recorded |
| 12159 | `ErACM` | M2 T43 S2 | existing closure backlog; Accepted transfer-220: coin and axe effects chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12169 | `ClimbXPosAdder` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12172 | `ClimbPLocAdder` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12175 | `FlagpoleYPosData` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12178 | `HandleClimbing` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12184 | `ExHC` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12186 | `ChkForFlagpole` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12192 | `FlagpoleCollision` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12212 | `ChkFlagpoleYPosLoop` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12217 | `MtchF` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12218 | `RunFR` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12222 | `VineCollision` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12231 | `PutPlayerOnVine` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12244 | `SetVXPl` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12259 | `ExPVne` | M2 T43 S3 | existing closure backlog; Accepted transfer-221: flagpole and vine climbing chain. | M2 T21 S3; M2 T24 S1 |
| 12263 | `ChkInvisibleMTiles` | M2 T43 S4 | existing closure backlog; Accepted transfer-222: invisible and jumpspring metatile chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12267 | `ExCInvT` | M2 T43 S4 | existing closure backlog; Accepted transfer-222: invisible and jumpspring metatile chain. | M2 T21 S3; M2 T24 S1 |
| 12273 | `ChkForLandJumpSpring` | M2 T43 S4 | existing closure backlog; Accepted transfer-222: invisible and jumpspring metatile chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12284 | `ExCJSp` | M2 T43 S4 | existing closure backlog; Accepted transfer-222: invisible and jumpspring metatile chain. | M2 T21 S3; M2 T24 S1 |
| 12286 | `ChkJumpspringMetatiles` | M2 T43 S4 | existing closure backlog; Accepted transfer-222: invisible and jumpspring metatile chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12292 | `JSFnd` | M2 T43 S4 | existing closure backlog; Accepted transfer-222: invisible and jumpspring metatile chain. | M2 T21 S3; M2 T24 S1 |
| 12293 | `NoJSFnd` | M2 T43 S4 | existing closure backlog; Accepted transfer-222: invisible and jumpspring metatile chain. | M2 T21 S3; M2 T24 S1 |
| 12295 | `HandlePipeEntry` | M2 T43 S5 | existing closure backlog; Accepted transfer-223: pipe-entry and warp destination chain. | M2 T17 S4; M2 T21 S3; M2 T24 S1; M2 T6 / S not recorded |
| 12326 | `GetWNum` | M2 T43 S5 | existing closure backlog; Accepted transfer-223: pipe-entry and warp destination chain. | M2 T21 S3; M2 T24 S1 |
| 12341 | `ExPipeE` | M2 T43 S5 | existing closure backlog; Accepted transfer-223: pipe-entry and warp destination chain. | M2 T21 S3; M2 T24 S1 |
| 12343 | `ImpedePlayerMove` | M2 T43 S6 | existing closure backlog; Accepted transfer-224: side impediment chain. | M2 T17 S4; M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 12354 | `RImpd` | M2 T43 S6 | existing closure backlog; Accepted transfer-224: side impediment chain. | M2 T21 S3; M2 T24 S1 |
| 12358 | `NXSpd` | M2 T43 S6 | existing closure backlog; Accepted transfer-224: side impediment chain. | M2 T21 S3; M2 T24 S1 |
| 12365 | `PlatF` | M2 T43 S6 | existing closure backlog; Accepted transfer-224: side impediment chain. | M2 T21 S3; M2 T24 S1 |
| 12372 | `ExIPM` | M2 T43 S6 | existing closure backlog; Accepted transfer-224: side impediment chain. | M2 T21 S3; M2 T24 S1 |
| 12380 | `SolidMTileUpperExt` | M2 T43 S7 | existing closure backlog; Accepted transfer-225: shared metatile classifiers. | M2 T21 S3; M2 T24 S1 |
| 12383 | `CheckForSolidMTiles` | M2 T43 S7 | existing closure backlog; Accepted transfer-225: shared metatile classifiers. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12388 | `ClimbMTileUpperExt` | M2 T43 S7 | existing closure backlog; Accepted transfer-225: shared metatile classifiers. | M2 T21 S3; M2 T24 S1 |
| 12391 | `CheckForClimbMTiles` | M2 T43 S7 | existing closure backlog; Accepted transfer-225: shared metatile classifiers. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12396 | `CheckForCoinMTiles` | M2 T43 S7 | existing closure backlog; Accepted transfer-225: shared metatile classifiers. | M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12403 | `CoinSd` | M2 T43 S7 | existing closure backlog; Accepted transfer-225: shared metatile classifiers. | M2 T21 S3; M2 T24 S1 |
| 12407 | `GetMTileAttrib` | M2 T43 S7 | existing closure backlog; Accepted transfer-225: shared metatile classifiers. | M2 T21 S3; M2 T24 S1 |
| 12415 | `ExEBG` | M2 T43 S7 | existing closure backlog; Accepted transfer-226: shared metatile classifiers. | M2 T21 S3; M2 T24 S1 |
| 12420 | `EnemyBGCStateData` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12423 | `EnemyBGCXSpdData` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12426 | `EnemyToBGCollisionDet` | M2 T43 S8 | existing closure backlog; Accepted transfer-228: enemy terrain dispatch and stun chain. | M2 T17 S5; M2 T19 S3; M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 12439 | `DoIDCheckBGColl` | M2 T43 S8 | existing closure backlog; Accepted transfer-228: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12443 | `HBChk` | M2 T43 S8 | existing closure backlog; Accepted transfer-228: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12446 | `CInvu` | M2 T43 S8 | existing closure backlog; Accepted transfer-228: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12452 | `YesIn` | M2 T43 S8 | existing closure backlog; Accepted transfer-228: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12455 | `NoEToBGCollision` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12461 | `HandleEToBGCollision` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12476 | `GiveOEPoints` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12480 | `ChkToStunEnemies` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12489 | `Demote` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12491 | `SetStun` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12503 | `SetWYSpd` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12504 | `SetNotW` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12509 | `ChkBBill` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12515 | `NoCDirF` | M2 T43 S8 | existing closure backlog; Accepted transfer-227: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12518 | `ExEBGChk` | M2 T43 S8 | existing closure backlog; Accepted transfer-228: enemy terrain dispatch and stun chain. | M2 T21 S3; M2 T24 S1 |
| 12523 | `LandEnemyProperly` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12535 | `SChkA` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12537 | `ChkLandedEnemyState` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12552 | `SetForStn` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12556 | `ExSteChk` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12558 | `ProcEnemyDirection` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12571 | `InvtD` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12575 | `CNwCDir` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12580 | `LandEnemyInitState` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12589 | `NMovShellFallBit` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12597 | `ChkForRedKoopa` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12603 | `Chk2MSBSt` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12610 | `GetSteFromD` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12611 | `SetD6Ste` | M2 T43 S9 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12617 | `DoEnemySideCheck` | M2 T31 S2 | existing closure backlog; Accepted side-check loop dependency, transfer-130 | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12624 | `SdeCLoop` | M2 T31 S2 | existing closure backlog; Accepted side-check loop dependency, transfer-130 | M2 T21 S3; M2 T24 S1 |
| 12632 | `NextSdeC` | M2 T31 S2 | existing closure backlog; Accepted side-check loop dependency, transfer-130 | M2 T21 S3; M2 T24 S1 |
| 12636 | `ExESdeC` | M2 T31 S2 | existing closure backlog; Accepted side-check loop dependency, transfer-130 | M2 T21 S3; M2 T24 S1 |
| 12638 | `ChkForBump_HammerBroJ` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12646 | `NoBump` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12654 | `InvEnemyDir` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12660 | `PlayerEnemyDiff` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12671 | `EnemyLanding` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12679 | `SubtEnemyYPos` | M2 T31 S2 | existing closure backlog; Accepted original normal-enemy caller/movement dependency, transfer-129 | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12686 | `EnemyJump` | M2 T31 S2 | existing closure backlog; Accepted original normal-enemy caller/movement dependency, transfer-129 | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12701 | `DoSide` | M2 T31 S2 | existing closure backlog; Accepted original normal-enemy caller/movement dependency, transfer-129 | M2 T21 S3; M2 T24 S1 |
| 12705 | `HammerBroBGColl` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12711 | `KillEnemyAboveBlock` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12717 | `UnderHammerBro` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12726 | `NoUnderHammerBro` | M2 T43 S10 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 12732 | `ChkUnderEnemy` | M2 T43 S11 | existing closure backlog; M2 T43 S11 admitted source-order ground-query continuation. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12737 | `ChkForNonSolids` | M2 T43 S11 | existing closure backlog; M2 T43 S11 admitted source-order ground-query continuation. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12747 | `NSFnd` | M2 T43 S11 | existing closure backlog; M2 T43 S11 admitted source-order ground-query continuation. | M2 T21 S3; M2 T24 S1 |
| 12751 | `FireballBGCollision` | M2 T43 S12 | existing closure backlog; M2 T43 S12 admitted source-order fireball-background continuation. | M2 T17 S5; M2 T20 S3; M2 T21 S3; M2 T24 S1 |
| 12772 | `ClearBounceFlag` | M2 T43 S12 | existing closure backlog; M2 T43 S12 admitted source-order fireball-background continuation. | M2 T21 S3; M2 T24 S1 |
| 12777 | `InitFireballExplode` | M2 T43 S12 | existing closure backlog; M2 T43 S12 admitted source-order fireball-background continuation. | M2 T21 S3; M2 T24 S1 |
| 12791 | `BoundBoxCtrlData` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T21 S3; M2 T24 S1 |
| 12805 | `GetFireballBoundBox` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T16 S3; M2 T17 S3; M2 T21 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 12813 | `GetMiscBoundBox` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T16 S2; M2 T17 S3; M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12819 | `FBallB` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T21 S3; M2 T24 S1 |
| 12822 | `GetEnemyBoundBox` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T16 S3; M2 T17 S3; M2 T19 S5; M2 T21 S3; M2 T24 S1 |
| 12828 | `SmallPlatformBoundBox` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T21 S3; M2 T24 S1 |
| 12833 | `GetMaskedOffScrBits` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T21 S3; M2 T24 S1 |
| 12844 | `CMBits` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T21 S3; M2 T24 S1 |
| 12850 | `LargePlatformBoundBox` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T21 S3; M2 T24 S1 |
| 12857 | `SetupEOffsetFBBox` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T21 S3; M2 T24 S1 |
| 12866 | `MoveBoundBoxOffscreen` | M2 T43 S13 | existing closure backlog; M2 T43 S13 accepted source-order object bounding-box entry chain. | M2 T21 S3; M2 T24 S1 |
| 12878 | `BoundingBoxCore` | M2 T43 S14 | existing closure backlog; M2 T43 S14 accepted transfer 234 for the contiguous BoundingBoxCore clipping chain. | M2 T16 S3; M2 T17 / S not recorded; M2 T17 S3; M2 T17 S4; M2 T21 S3; M2 T24 S1 |
| 12916 | `CheckRightScreenBBox` | M2 T43 S14 | existing closure backlog; M2 T43 S14 accepted transfer 234 for the contiguous BoundingBoxCore clipping chain. | M2 T17 S3; M2 T21 S3; M2 T24 S1 |
| 12935 | `SORte` | M2 T43 S14 | existing closure backlog; M2 T43 S14 accepted transfer 234 for the contiguous BoundingBoxCore clipping chain. | M2 T21 S3; M2 T24 S1 |
| 12936 | `NoOfs` | M2 T43 S14 | existing closure backlog; M2 T43 S14 accepted transfer 234 for the contiguous BoundingBoxCore clipping chain. | M2 T21 S3; M2 T24 S1 |
| 12939 | `CheckLeftScreenBBox` | M2 T43 S14 | existing closure backlog; M2 T43 S14 accepted transfer 234 for the contiguous BoundingBoxCore clipping chain. | M2 T17 S3; M2 T21 S3; M2 T24 S1 |
| 12948 | `SOLft` | M2 T43 S14 | existing closure backlog; M2 T43 S14 accepted transfer 234 for the contiguous BoundingBoxCore clipping chain. | M2 T21 S3; M2 T24 S1 |
| 12949 | `NoOfs2` | M2 T43 S14 | existing closure backlog; M2 T43 S14 accepted transfer 234 for the contiguous BoundingBoxCore clipping chain. | M2 T21 S3; M2 T24 S1 |
| 12956 | `PlayerCollisionCore` | M2 T43 S15 | existing closure backlog; M2 T43 S15 accepted transfer 235 for the contiguous box-collision geometry chain. | M2 T17 S3; M2 T21 S3; M2 T24 S1 |
| 12959 | `SprObjectCollisionCore` | M2 T43 S15 | existing closure backlog; M2 T43 S15 accepted transfer 235 for the contiguous box-collision geometry chain. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 12964 | `CollisionCoreLoop` | M2 T43 S15 | existing closure backlog; M2 T43 S15 accepted transfer 235 for the contiguous box-collision geometry chain. | M2 T21 S3; M2 T24 S1 |
| 12979 | `SecondBoxVerticalChk` | M2 T43 S15 | existing closure backlog; M2 T43 S15 accepted transfer 235 for the contiguous box-collision geometry chain. | M2 T21 S3; M2 T24 S1 |
| 12989 | `FirstBoxGreater` | M2 T43 S15 | existing closure backlog; M2 T43 S15 accepted transfer 235 for the contiguous box-collision geometry chain. | M2 T21 S3; M2 T24 S1 |
| 13002 | `NoCollisionFound` | M2 T43 S15 | existing closure backlog; M2 T43 S15 accepted transfer 235 for the contiguous box-collision geometry chain. | M2 T21 S3; M2 T24 S1 |
| 13007 | `CollisionFound` | M2 T43 S15 | existing closure backlog; M2 T43 S15 accepted transfer 235 for the contiguous box-collision geometry chain. | M2 T21 S3; M2 T24 S1 |
| 13023 | `BlockBufferChk_Enemy` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 13032 | `ResidualMiscObjectCode` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13040 | `BlockBufferChk_FBall` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 13046 | `ResJmpM` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13047 | `BBChk_E` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13052 | `BlockBufferAdderData` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13055 | `BlockBuffer_X_Adder` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13061 | `BlockBuffer_Y_Adder` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13067 | `BlockBufferColli_Feet` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13070 | `BlockBufferColli_Head` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13074 | `BlockBufferColli_Side` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13078 | `BlockBufferCollision` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T17 S3; M2 T17 S4; M2 T17 S5; M2 T21 S3; M2 T24 S1 |
| 13111 | `RetXC` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13112 | `RetYC` | M2 T44 S1 | existing closure backlog; M2 T44 S1 accepted transfer 236 for the contiguous block-buffer core chain. | M2 T21 S3; M2 T24 S1 |
| 13126 | `VineYPosAdder` | M2 T44 S2 | existing closure backlog; M2 T44 S2 accepted transfer 237 for the contiguous vine object graphics chain. | M2 T21 S3; M2 T24 S1 |
| 13129 | `DrawVine` | M2 T44 S2 | existing closure backlog; M2 T44 S2 accepted transfer 237 for the contiguous vine object graphics chain. | M2 T21 S3; M2 T22 S1; M2 T24 S1 |
| 13156 | `VineTL` | M2 T44 S2 | existing closure backlog; M2 T44 S2 accepted transfer 237 for the contiguous vine object graphics chain. | M2 T21 S3; M2 T24 S1 |
| 13169 | `SkpVTop` | M2 T44 S2 | existing closure backlog; M2 T44 S2 accepted transfer 237 for the contiguous vine object graphics chain. | M2 T21 S3; M2 T24 S1 |
| 13170 | `ChkFTop` | M2 T44 S2 | existing closure backlog; M2 T44 S2 accepted transfer 237 for the contiguous vine object graphics chain. | M2 T21 S3; M2 T24 S1 |
| 13177 | `NextVSp` | M2 T44 S2 | existing closure backlog; M2 T44 S2 accepted transfer 237 for the contiguous vine object graphics chain. | M2 T21 S3; M2 T24 S1 |
| 13187 | `SixSpriteStacker` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13189 | `StkLp` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13203 | `FirstSprXPos` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13206 | `FirstSprYPos` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13209 | `SecondSprXPos` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13212 | `SecondSprYPos` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13215 | `FirstSprTilenum` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13218 | `SecondSprTilenum` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13221 | `HammerSprAttrib` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13224 | `DrawHammer` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T19 S4; M2 T21 S3; M2 T24 S1 |
| 13232 | `ForceHPose` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13234 | `GetHPose` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13239 | `RenderH` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13268 | `NoHOffscr` | M2 T44 S3 | existing closure backlog; M2 T44 S3 admitted contiguous source-order shared OAM and hammer graphics chain | M2 T21 S3; M2 T24 S1 |
| 13277 | `FlagpoleScoreNumTiles` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T21 S3; M2 T24 S1 |
| 13284 | `FlagpoleGfxHandler` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T17 S6; M2 T21 S3; M2 T22 S4; M2 T24 S1 |
| 13326 | `ChkFlagOffscreen` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T21 S3; M2 T24 S1 |
| 13335 | `MoveSixSpritesOffscreen` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T21 S3; M2 T24 S1 |
| 13338 | `DumpSixSpr` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T21 S3; M2 T24 S1 |
| 13342 | `DumpFourSpr` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T21 S3; M2 T24 S1 |
| 13345 | `DumpThreeSpr` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T21 S3; M2 T24 S1 |
| 13348 | `DumpTwoSpr` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T17 S6; M2 T21 S3; M2 T24 S1 |
| 13352 | `ExitDumpSpr` | M2 T44 S4 | existing closure backlog; M2 T44 S4 admitted contiguous source-order flagpole graphics and OAM dump-helper chain | M2 T21 S3; M2 T24 S1 |
| 13357 | `DrawLargePlatform` | M2 T52 S6 | existing closure backlog; Owner-approved T52 corrective continuation under the continuing M2 ROM-equivalence mandate. | M2 T21 S3; M2 T24 S1 |
| 13374 | `ShrinkPlatform` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13377 | `SetLast2Platform` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13386 | `SetPlatformTilenum` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13402 | `SChk2` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13408 | `SChk3` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13414 | `SChk4` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13420 | `SChk5` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13426 | `SChk6` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13431 | `SLChk` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13435 | `ExDLPl` | M2 T44 S5 | existing closure backlog; M2 T44 S5 admitted contiguous source-order large-platform graphics chain | M2 T21 S3; M2 T24 S1 |
| 13439 | `DrawFloateyNumber_Coin` | M2 T44 S6 | existing closure backlog; M2 T44 S6 admitted contiguous source-order floatey-number and jumping-coin graphics chain | M2 T21 S3; M2 T24 S1 |
| 13444 | `NotRsNum` | M2 T44 S6 | existing closure backlog; M2 T44 S6 admitted contiguous source-order floatey-number and jumping-coin graphics chain | M2 T21 S3; M2 T24 S1 |
| 13460 | `JumpingCoinTiles` | M2 T44 S6 | existing closure backlog; M2 T44 S6 admitted contiguous source-order floatey-number and jumping-coin graphics chain | M2 T21 S3; M2 T24 S1 |
| 13463 | `JCoinGfxHandler` | M2 T44 S6 | existing closure backlog; M2 T44 S6 admitted contiguous source-order floatey-number and jumping-coin graphics chain | M2 T21 S3; M2 T24 S1 |
| 13489 | `ExJCGfx` | M2 T44 S6 | existing closure backlog; M2 T44 S6 admitted contiguous source-order floatey-number and jumping-coin graphics chain | M2 T21 S3; M2 T24 S1 |
| 13500 | `PowerUpGfxTable` | M2 T44 S7 | existing closure backlog; M2 T44 S7 admitted contiguous source-order power-up graphics chain | M2 T21 S3; M2 T24 S1 |
| 13506 | `PowerUpAttributes` | M2 T44 S7 | existing closure backlog; M2 T44 S7 admitted contiguous source-order power-up graphics chain | M2 T21 S3; M2 T24 S1 |
| 13509 | `DrawPowerUp` | M2 T44 S7 | existing closure backlog; M2 T44 S7 admitted contiguous source-order power-up graphics chain | M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 13530 | `PUpDrawLoop` | M2 T44 S7 | existing closure backlog; M2 T44 S7 admitted contiguous source-order power-up graphics chain | M2 T21 S3; M2 T24 S1 |
| 13555 | `FlipPUpRightSide` | M2 T44 S7 | existing closure backlog; M2 T44 S7 admitted contiguous source-order power-up graphics chain | M2 T21 S3; M2 T24 S1 |
| 13562 | `PUpOfs` | M2 T44 S7 | existing closure backlog; M2 T44 S7 admitted contiguous source-order power-up graphics chain | M2 T21 S3; M2 T24 S1 |
| 13576 | `EnemyGraphicsTable` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13621 | `EnemyGfxTableOffsets` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13627 | `EnemyAttributeData` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13633 | `EnemyAnimTimingBMask` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13636 | `JumpspringFrameOffsets` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13639 | `EnemyGfxHandler` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T19 S4; M2 T21 S3; M2 T24 S1 |
| 13661 | `CheckForRetainerObj` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13674 | `CheckForBulletBillCV` | M2 T44 S8 | existing closure backlog; Accepted exact cannon counterexample and required source-dispatch dependency in active S2. | M2 T21 S3; M2 T24 S1 |
| 13682 | `SBBAt` | M2 T44 S8 | existing closure backlog; Accepted exact cannon counterexample and required source-dispatch dependency in active S2. | M2 T21 S3; M2 T24 S1 |
| 13687 | `CheckForJumpspring` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13694 | `CheckForPodoboo` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13704 | `CheckBowserGfxFlag` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13711 | `SBwsrGfxOfs` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13713 | `CheckForGoomba` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13722 | `GmbaAnim` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13732 | `CheckBowserFront` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13746 | `ChkFrontSte` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13750 | `FlipBowserOver` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13753 | `DrawBowser` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13756 | `CheckBowserRear` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13761 | `ChkRearSte` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13770 | `CheckForSpiny` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13780 | `NotEgg` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13782 | `CheckForLakitu` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13792 | `NoLAFr` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13794 | `CheckUpsideDownShell` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13807 | `CheckRightSideUpShell` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 13819 | `CheckForDefdGoomba` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 13829 | `CheckForHammerBro` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13841 | `CheckForBloober` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13856 | `CheckToAnimateEnemy` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13878 | `CheckForSecondFrame` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13883 | `CheckAnimationStop` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13893 | `CheckDefeatedState` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13905 | `DrawEnemyObject` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13916 | `SkipToOffScrChk` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13919 | `CheckForVerticalFlip` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13943 | `FlipEnemyVertically` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13957 | `CheckForESymmetry` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13965 | `ContES` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13975 | `ESRtnr` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13979 | `SpnySC` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 13982 | `MirrorEnemyGfx` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 13994 | `EggExc` | M2 T44 S8 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14007 | `CheckToMirrorLakitu` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14026 | `NVFLak` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14033 | `CheckToMirrorJSpring` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14044 | `SprObjectOffscrChk` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14054 | `LcChk` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14060 | `Row3C` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14067 | `Row23C` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14073 | `AllRowC` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14085 | `ExEGHandler` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14088 | `DrawEnemyObjRow` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14093 | `DrawOneSpriteRow` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14097 | `MoveESprRowOffscreen` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14104 | `MoveESprColOffscreen` | M2 T45 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14119 | `DefaultBlockObjTiles` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14122 | `DrawBlock` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S1; M2 T16 S2; M2 T16 S3; M2 T21 S3; M2 T24 S1 |
| 14133 | `DBlkLoop` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14147 | `ChkRep` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14159 | `SetBFlip` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14167 | `BlkOffscr` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14174 | `PullOfsB` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14175 | `ChkLeftCo` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14178 | `MoveColOffscreen` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14182 | `ExDBlk` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14187 | `DrawBrickChunks` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S2; M2 T21 S3; M2 T24 S1 |
| 14197 | `DChunks` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14242 | `ChnkOfs` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14250 | `ExBCDr` | M2 T45 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14254 | `DrawFireball` | M2 T45 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14261 | `DrawFirebar` | M2 T45 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14275 | `FireA` | M2 T45 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14280 | `ExplosionTiles` | M2 T45 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14283 | `DrawExplosion_Fireball` | M2 T45 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14292 | `DrawExplosion_Fireworks` | M2 T45 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14327 | `KillFireBall` | M2 T45 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14334 | `DrawSmallPlatform` | M2 T45 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14361 | `TopSP` | M2 T45 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14369 | `BotSP` | M2 T45 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14379 | `SOfs` | M2 T45 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14386 | `SOfs2` | M2 T45 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14392 | `ExSPl` | M2 T45 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14397 | `DrawBubble` | M2 T45 S5 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T19 S4; M2 T21 S3; M2 T24 S1 |
| 14413 | `ExDBub` | M2 T45 S5 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14418 | `PlayerGfxTblOffsets` | M2 T45 S5 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S3; M2 T24 S1 |
| 14424 | `PlayerGraphicsTable` | M2 T45 S5 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14457 | `SwimKickTileNum` | M2 T45 S5 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14460 | `PlayerGfxHandler` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T15 S3; M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14466 | `CntPl` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14489 | `SwimKT` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14495 | `BigKTS` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14497 | `ExPGH` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14499 | `FindPlayerAction` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14503 | `DoChangeSize` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14507 | `PlayerKilled` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14511 | `PlayerGfxProcessing` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14532 | `SUpdR` | M2 T46 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14535 | `PlayerOffscreenChk` | M2 T46 S1 | existing closure backlog; canonical audited OAM owner overrides physical source slice | M2 T16 S3; M2 T24 / S not recorded; M2 T24 S1 |
| 14547 | `PROfsLoop` | M2 T46 S1 | existing closure backlog; canonical audited OAM owner overrides physical source slice | M2 T24 / S not recorded; M2 T24 S1 |
| 14551 | `NPROffscr` | M2 T46 S1 | existing closure backlog; canonical audited OAM owner overrides physical source slice | M2 T24 / S not recorded; M2 T24 S1 |
| 14561 | `IntermediatePlayerData` | M2 T46 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14564 | `DrawPlayer_Intermediate` | M2 T46 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14566 | `PIntLoop` | M2 T46 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14587 | `RenderPlayerSub` | M2 T46 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T15 / S not recorded; M2 T15 S3; M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14601 | `DrawPlayerLoop` | M2 T46 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14610 | `ProcessPlayerAction` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14626 | `ProcOnGroundActs` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14642 | `NonAnimatedActs` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14649 | `ActionFalling` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14654 | `ActionWalkRun` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14659 | `ActionClimbing` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14666 | `ActionSwimming` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14676 | `GetCurrentAnimOffset` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14680 | `FourFrameExtent` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14684 | `ThreeFrameExtent` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14687 | `AnimationControl` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14701 | `SetAnimC` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14702 | `ExAnimC` | M2 T46 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14705 | `GetGfxOffsetAdder` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14712 | `SzOfs` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14714 | `ChangeSizeOffsetAdder` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14718 | `HandleChangeSize` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14728 | `CSzNext` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14729 | `GorSLog` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14734 | `GetOffsetFromAnimCtrl` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14741 | `ShrinkPlayer` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14750 | `ShrPlF` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14753 | `ChkForPlayerAttrib` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14767 | `KilledAtt` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14774 | `C_S_IGAtt` | M2 T46 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14781 | `ExPlyrAt` | M2 T47 S1 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14786 | `RelativePlayerPosition` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T15 S3; M2 T16 S3; M2 T17 S4; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14791 | `RelativeBubblePosition` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T19 S4; M2 T21 S2; M2 T24 S1 |
| 14797 | `RelativeFireballPosition` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14801 | `RelWOfs` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14805 | `RelativeMiscPosition` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S2; M2 T17 S5; M2 T19 S4; M2 T21 S2; M2 T24 S1 |
| 14811 | `RelativeEnemyPosition` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T17 S5; M2 T19 / S not recorded; M2 T19 S4; M2 T21 S2; M2 T22 S4; M2 T24 S1 |
| 14816 | `RelativeBlockPosition` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T15 S4; M2 T16 S1; M2 T16 S2; M2 T21 S2; M2 T24 S1 |
| 14825 | `VariableObjOfsRelPos` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14834 | `GetObjRelativePosition` | M2 T47 S2 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S2; M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14846 | `GetPlayerOffscreenBits` | M2 T47 S3 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14851 | `GetFireballOffscreenBits` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T20 S2; M2 T21 S2; M2 T24 / S not recorded; M2 T24 S1 |
| 14857 | `GetBubbleOffscreenBits` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T19 S4; M2 T21 S2; M2 T24 S1 |
| 14863 | `GetMiscOffscreenBits` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S2; M2 T17 S5; M2 T19 S4; M2 T21 S2; M2 T24 S1 |
| 14869 | `ObjOffsetData` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14872 | `GetProperObjOffset` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14879 | `GetEnemyOffscreenBits` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T19 S4; M2 T21 S2; M2 T22 S4; M2 T24 S1 |
| 14884 | `GetBlockOffscreenBits` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T15 S4; M2 T16 S1; M2 T16 S2; M2 T21 S2; M2 T24 S1 |
| 14888 | `SetOffscrBitsOffset` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14894 | `GetOffScreenBitsSet` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S2; M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14911 | `RunOffscrBitsSubs` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14927 | `XOffscreenBitsData` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14931 | `DefaultXOnscreenOfs` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14934 | `GetXOffscreenBits` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S2; M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14937 | `XOfsLoop` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14953 | `XLdBData` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14959 | `ExXOfsBS` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14963 | `YOffscreenBitsData` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14968 | `DefaultYOnscreenOfs` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14971 | `HighPosUnitData` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14974 | `GetYOffscreenBits` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S2; M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 14977 | `YOfsLoop` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14993 | `YLdBData` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 14999 | `ExYOfsBS` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 15003 | `DividePDiff` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 15015 | `SetOscrO` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 15016 | `ExDivPD` | M2 T47 S4 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 15025 | `DrawSpriteObject` | M2 T47 S5 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T16 S3; M2 T21 S2; M2 T24 S1 |
| 15036 | `NoHFlip` | M2 T47 S5 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 15040 | `SetHFAt` | M2 T47 S5 | existing closure backlog; restored pending small-task planning after oversized T21 replan | M2 T21 S2; M2 T24 S1 |
| 15070 | `SoundEngine` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T21 / S not recorded; M2 T24 S1; M2 T7 / S not recorded |
| 15075 | `SndOn` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15084 | `InPause` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15099 | `PTone1F` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15101 | `ContPau` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15108 | `PTone2F` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15109 | `PTRegC` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15112 | `DecPauC` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15121 | `SkipPIn` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15125 | `RunSoundSubroutines` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15134 | `SkipSoundSubroutines` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15147 | `NoIncDAC` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15150 | `StrWave` | M2 T48 S1 | existing closure backlog; admitted T48 S1 source-order implementation | M2 T24 S1 |
| 15155 | `Dump_Squ1_Regs` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15160 | `PlaySqu1Sfx` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15163 | `SetFreq_Squ1` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15166 | `Dump_Freq_Regs` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15174 | `NoTone` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15176 | `Dump_Sq2_Regs` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15181 | `PlaySqu2Sfx` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15184 | `SetFreq_Squ2` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15188 | `SetFreq_Tri` | M2 T48 S2 | existing closure backlog; admitted T48 S2 source-order implementation | M2 T24 S1 |
| 15194 | `SwimStompEnvelopeData` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15198 | `PlayFlagpoleSlide` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15206 | `PlaySmallJump` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15210 | `PlayBigJump` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15213 | `JumpRegContents` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15220 | `ContinueSndJump` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15227 | `N2Prt` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15230 | `FPS2nd` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15231 | `DmpJpFPS` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15234 | `PlayFireballThrow` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15239 | `PlayBump` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15242 | `Fthrow` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15247 | `ContinueBumpThrow` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15253 | `DecJpFPS` | M2 T48 S3 | existing closure backlog; admitted T48 S3 source-order implementation | M2 T24 S1 |
| 15256 | `Square1SfxHandler` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15276 | `CheckSfx1Buffer` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15294 | `ExS1H` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15296 | `PlaySwimStomp` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15304 | `ContinueSwimStomp` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15313 | `BranchToDecLength1` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15316 | `PlaySmackEnemy` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15325 | `ContinueSmackEnemy` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15333 | `SmSpc` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15334 | `SmTick` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15336 | `DecrementSfx1Length` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15340 | `StopSquare1Sfx` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T21 S2; M2 T21 S5; M2 T24 S1 |
| 15347 | `ExSfx1` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15349 | `PlayPipeDownInj` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15353 | `ContinuePipeDownInj` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15365 | `NoPDwnL` | M2 T48 S4 | existing closure backlog; admitted T48 S4 source-order implementation | M2 T24 S1 |
| 15369 | `ExtraLifeFreqData` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15372 | `PowerUpGrabFreqData` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15380 | `PUp_VGrow_FreqData` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15386 | `PlayCoinGrab` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15391 | `PlayTimerTick` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15395 | `CGrab_TTickRegL` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15401 | `ContinueCGrabTTick` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15407 | `N2Tone` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15409 | `PlayBlast` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15416 | `ContinueBlast` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15422 | `SBlasJ` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15424 | `PlayPowerUpGrab` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T21 S2; M2 T24 S1 |
| 15428 | `ContinuePowerUpGrab` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15437 | `LoadSqu2Regs` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15440 | `DecrementSfx2Length` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15444 | `EmptySfx2Buffer` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15448 | `StopSquare2Sfx` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T21 S2; M2 T21 S5; M2 T24 S1 |
| 15453 | `ExSfx2` | M2 T48 S5 | existing closure backlog; admitted T48 S5 source-order implementation | M2 T24 S1 |
| 15455 | `Square2SfxHandler` | M2 T48 S6 | existing closure backlog; admitted T48 S6 source-order implementation | M2 T21 S2; M2 T24 S1 |
| 15478 | `CheckSfx2Buffer` | M2 T48 S6 | existing closure backlog; admitted T48 S6 source-order implementation | M2 T24 S1 |
| 15496 | `ExS2H` | M2 T48 S6 | existing closure backlog; admitted T48 S6 source-order implementation | M2 T24 S1 |
| 15498 | `Cont_CGrab_TTick` | M2 T48 S6 | existing closure backlog; admitted T48 S6 source-order implementation | M2 T24 S1 |
| 15501 | `JumpToDecLength2` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15504 | `PlayBowserFall` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15509 | `BlstSJp` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15511 | `ContinueBowserFall` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15517 | `PBFRegs` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15518 | `EL_LRegs` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15520 | `PlayExtraLife` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15524 | `ContinueExtraLife` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15527 | `DivLLoop` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15537 | `PlayGrowPowerUp` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T21 S2; M2 T24 S1 |
| 15541 | `PlayGrowVine` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15544 | `GrowItemRegs` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T21 S2; M2 T24 S1 |
| 15551 | `ContinueGrowItems` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T21 S2; M2 T24 S1 |
| 15564 | `StopGrowItems` | M2 T49 S1 | existing closure backlog; admitted T49 S1 source-order implementation | M2 T24 S1 |
| 15569 | `BrickShatterFreqData` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15573 | `PlayBrickShatter` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15577 | `ContinueBrickShatter` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15585 | `PlayNoiseSfx` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15591 | `DecrementSfx3Length` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15598 | `ExSfx3` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15600 | `NoiseSfxHandler` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15609 | `CheckNoiseBuffer` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15616 | `ExNH` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15618 | `PlayBowserFlame` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15622 | `ContinueBowserFlame` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15632 | `ContinueMusic` | M2 T49 S2 | existing closure backlog; admitted T49 S2 source-order implementation | M2 T24 S1 |
| 15635 | `MusicHandler` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15645 | `LoadEventMusic` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T21 S2; M2 T21 S5; M2 T24 S1 |
| 15651 | `NoStopSfx` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15662 | `LoadAreaMusic` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15666 | `NoStop1` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15667 | `GMLoopB` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15669 | `HandleAreaMusicLoopB` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15682 | `FindAreaMusicHeader` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15686 | `FindEventMusicHeader` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15691 | `LoadHeader` | M2 T49 S3 | existing closure backlog; accepted source-order music selection/header-load chain | M2 T24 S1 |
| 15720 | `HandleSquare2Music` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15730 | `EndOfMusicData` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15736 | `NotTRO` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15750 | `MusicLoopBack` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15753 | `VictoryMLoopBack` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15756 | `Squ2LengthHandler` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15763 | `Squ2NoteHandler` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15769 | `Rest` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15771 | `SkipFqL1` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15774 | `MiscSqu2MusicTasks` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15783 | `NoDecEnv1` | M2 T49 S4 | existing closure backlog; M2 T49 S4 accepted source-order square-two music-stream custody | M2 T24 S1 |
| 15788 | `HandleSquare1Music` | M2 T49 S5 | existing closure backlog; M2 T49 S5 accepted source-order square-one music-stream custody | M2 T24 S1 |
| 15794 | `FetchSqu1MusicData` | M2 T49 S5 | existing closure backlog; M2 T49 S5 accepted source-order square-one music-stream custody | M2 T24 S1 |
| 15806 | `Squ1NoteHandler` | M2 T49 S5 | existing closure backlog; M2 T49 S5 accepted source-order square-one music-stream custody | M2 T24 S1 |
| 15816 | `SkipCtrlL` | M2 T49 S5 | existing closure backlog; M2 T49 S5 accepted source-order square-one music-stream custody | M2 T24 S1 |
| 15819 | `MiscSqu1MusicTasks` | M2 T49 S5 | existing closure backlog; M2 T49 S5 accepted source-order square-one music-stream custody | M2 T24 S1 |
| 15828 | `NoDecEnv2` | M2 T49 S5 | existing closure backlog; M2 T49 S5 accepted source-order square-one music-stream custody | M2 T24 S1 |
| 15830 | `DeathMAltReg` | M2 T49 S5 | existing closure backlog; M2 T49 S5 accepted source-order square-one music-stream custody | M2 T24 S1 |
| 15833 | `DoAltLoad` | M2 T49 S5 | existing closure backlog; M2 T49 S5 accepted source-order square-one music-stream custody | M2 T24 S1 |
| 15835 | `HandleTriangleMusic` | M2 T49 S6 | existing closure backlog; M2 T49 S6 accepted source-order triangle music-stream custody | M2 T24 S1 |
| 15853 | `TriNoteHandler` | M2 T49 S6 | existing closure backlog; M2 T49 S6 accepted source-order triangle music-stream custody | M2 T24 S1 |
| 15863 | `NotDOrD4` | M2 T49 S6 | existing closure backlog; M2 T49 S6 accepted source-order triangle music-stream custody | M2 T24 S1 |
| 15871 | `MediN` | M2 T49 S6 | existing closure backlog; M2 T49 S6 accepted source-order triangle music-stream custody | M2 T24 S1 |
| 15873 | `LongN` | M2 T49 S6 | existing closure backlog; M2 T49 S6 accepted source-order triangle music-stream custody | M2 T24 S1 |
| 15875 | `LoadTriCtrlReg` | M2 T49 S6 | existing closure backlog; M2 T49 S6 accepted source-order triangle music-stream custody | M2 T24 S1 |
| 15878 | `HandleNoiseMusic` | M2 T49 S7 | existing closure backlog; Accepted source-order T49 S7 noise music beat chain transfer. | M2 T24 S1 |
| 15885 | `FetchNoiseBeatData` | M2 T49 S7 | existing closure backlog; Accepted source-order T49 S7 noise music beat chain transfer. | M2 T24 S1 |
| 15894 | `NoiseBeatHandler` | M2 T49 S7 | existing closure backlog; Accepted source-order T49 S7 noise music beat chain transfer. | M2 T24 S1 |
| 15911 | `StrongBeat` | M2 T49 S7 | existing closure backlog; Accepted source-order T49 S7 noise music beat chain transfer. | M2 T24 S1 |
| 15917 | `LongBeat` | M2 T49 S7 | existing closure backlog; Accepted source-order T49 S7 noise music beat chain transfer. | M2 T24 S1 |
| 15923 | `SilentBeat` | M2 T49 S7 | existing closure backlog; Accepted source-order T49 S7 noise music beat chain transfer. | M2 T24 S1 |
| 15926 | `PlayBeat` | M2 T49 S7 | existing closure backlog; Accepted source-order T49 S7 noise music beat chain transfer. | M2 T24 S1 |
| 15931 | `ExitMusicHandler` | M2 T49 S7 | existing closure backlog; Accepted source-order T49 S7 noise music beat chain transfer. | M2 T24 S1 |
| 15934 | `AlternateLengthHandler` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15942 | `ProcessLengthData` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15951 | `LoadControlRegs` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15957 | `NotECstlM` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15962 | `WaterMus` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15963 | `AllMus` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15967 | `LoadEnvelopeData` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15974 | `LoadUsualEnvData` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15981 | `LoadWaterEventMusEnvData` | M2 T49 S8 | existing closure backlog; Accepted source-order T49 S8 shared music helper chain transfer. | M2 T24 S1 |
| 15989 | `MusicHeaderData` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16027 | `TimeRunningOutHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16028 | `Star_CloudHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16029 | `EndOfLevelMusHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16030 | `ResidualHeaderData` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16031 | `UndergroundMusHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16032 | `SilenceHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16033 | `CastleMusHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16034 | `VictoryMusHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16035 | `GameOverMusHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16036 | `WaterMusHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16037 | `WinCastleMusHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16038 | `GroundLevelPart1Hdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16039 | `GroundLevelPart2AHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16040 | `GroundLevelPart2BHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16041 | `GroundLevelPart2CHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16042 | `GroundLevelPart3AHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16043 | `GroundLevelPart3BHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16044 | `GroundLevelLeadInHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16045 | `GroundLevelPart4AHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16046 | `GroundLevelPart4BHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16047 | `GroundLevelPart4CHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16048 | `DeathMusHdr` | M2 T49 S9 | existing closure backlog; Accepted T49 S9 source-order music-header transfer. | M2 T24 S1 |
| 16077 | `Star_CloudMData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16089 | `GroundM_P1Data` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16094 | `SilenceData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16104 | `GroundM_P2AData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16114 | `GroundM_P2BData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16124 | `GroundM_P2CData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16134 | `GroundM_P3AData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16140 | `GroundM_P3BData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16148 | `GroundMLdInData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16158 | `GroundM_P4AData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16167 | `GroundM_P4BData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16176 | `DeathMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16179 | `GroundM_P4CData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16193 | `CastleMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16217 | `GameOverMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16226 | `TimeRunOutMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16236 | `WinLevelMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16253 | `UndergroundMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16264 | `WaterMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16295 | `EndOfCastleMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16313 | `VictoryMusData` | M2 T50 S1 | existing closure backlog; Accepted T50 S1 source-order music-stream payload transfer. | M2 T24 S1 |
| 16326 | `FreqRegLookupTbl` | M2 T50 S2 | existing closure backlog; Accepted T50 S2 source-order music lookup/envelope transfer. | M2 T24 S1 |
| 16341 | `MusicLengthLookupTbl` | M2 T50 S2 | existing closure backlog; Accepted T50 S2 source-order music lookup/envelope transfer. | M2 T24 S1 |
| 16349 | `EndOfCastleMusicEnvData` | M2 T50 S2 | existing closure backlog; Accepted T50 S2 source-order music lookup/envelope transfer. | M2 T24 S1 |
| 16352 | `AreaMusicEnvData` | M2 T50 S2 | existing closure backlog; Accepted T50 S2 source-order music lookup/envelope transfer. | M2 T24 S1 |
| 16355 | `WaterEventMusEnvData` | M2 T50 S2 | existing closure backlog; Accepted T50 S2 source-order music lookup/envelope transfer. | M2 T24 S1 |
| 16362 | `BowserFlameEnvData` | M2 T50 S3 | existing closure backlog; Accepted T50 S3 source-order noise-envelope transfer. | M2 T24 S1 |
| 16368 | `BrickShatterEnvData` | M2 T50 S3 | existing closure backlog; Accepted T50 S3 source-order noise-envelope transfer. | M2 T24 S1 |

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
| M2 T22 S5 | 0 | 8 | declared-plan, declared-closure-plan; [record](../../docs/proposals/m2/blocks-items-misc.md) |
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
| M2 T22 S25 | 6 | 5 | timer-lfsr-equivalence-review; [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
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
| M2 T26 S5 | 32 | 5 | planned-closure; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S6 | 2 | 0 | planned-outer-victory-call-order-repair; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T26 S7 | 2 | 2 | planned-outer-victory-route-equivalence; [record](../../docs/proposals/m2/t26-victory-terminal.md) |
| M2 T27 | 0 | - | [record](../../docs/proposals/m2/screen-status.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T27 S1 | 0 | 1 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/screen-status.md) |
| M2 T27 S2 | 0 | 28 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/screen-status.md) |
| M2 T27 S3 | 0 | 0 | planned-dispatch-integration; [record](../../docs/proposals/m2/screen-status.md) |
| M2 T28 | 0 | - | [record](../../docs/proposals/m2/t28-area-output-bootstrap.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T28 S1 | 0 | 2 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S2 | 0 | 3 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S3 | 0 | 11 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S4 | 0 | 19 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S5 | 0 | 1 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S6 | 0 | 6 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S7 | 0 | 19 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T28 S8 | 0 | 15 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t28-area-output-bootstrap.md) |
| M2 T29 | 32 | - | [record](../../docs/proposals/m2/t29-area-parser-geometry.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T29 S1 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S2 | 0 | 5 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S3 | 0 | 11 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S4 | 0 | 16 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S5 | 0 | 13 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S6 | 0 | 1 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S7 | 0 | 0 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S8 | 0 | 20 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S9 | 22 | 5 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T29 S10 | 10 | 10 | owner-approved-source-order, chain-based-implementation; [record](../../docs/proposals/m2/t29-area-parser-geometry.md) |
| M2 T3 | 2 | - | [record](../../docs/history/M2-T2-title-start-checkpoint.md); [record](../../docs/history/M2-T3-area-bootstrap-and-commands.md); S not recorded |
| M2 T30 | 144 | - | [record](../../docs/history/M2-T30-area-object-rendering.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md) |
| M2 T30 S1 | 0 | 3 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S2 | 0 | 2 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S3 | 7 | 7 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S4 | 10 | 10 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S5 | 3 | 3 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S6 | 4 | 4 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S7 | 1 | 1 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S8 | 8 | 8 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S9 | 8 | 4 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S10 | 6 | 6 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S11 | 1 | 0 | owner-approved-source-order, chain-based-implementation, corrective-revalidation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S12 | 1 | 0 | owner-approved-source-order, chain-based-implementation, corrective-revalidation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S13 | 3 | 3 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S14 | 23 | 22 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S15 | 34 | 0 | owner-approved-source-order, consumer-dependency-audit; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S16 | 7 | 6 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S17 | 22 | 22 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S18 | 3 | 3 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S19 | 3 | 3 | owner-approved-source-order, chain-based-implementation; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T30 S20 | 0 | 0 | owner-approved-source-order, cross-chain-closure-audit; [record](../../docs/history/M2-T30-area-object-rendering.md) |
| M2 T31 | 11 | - | [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S1 | 2 | 1 | owner-approved-source-order, entry-chain-implementation; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S2 | 9 | 36 | owner-approved-source-order, engine-chain-implementation; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S3 | 0 | 10 | owner-approved-source-order, scroll-chain-implementation; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T31 S4 | 0 | 9 | owner-approved-source-order, entry-mode-chain-implementation; [record](../../docs/history/M2-T31-game-dispatcher.md) |
| M2 T32 | 0 | - | [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S1 | 0 | 11 | owner-approved-source-order, player-control-chain; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S2 | 0 | 11 | owner-approved-source-order, vine-pipe-chain; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S3 | 0 | 14 | owner-approved-source-order, size-injury-death-palette-chain; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T32 S4 | 0 | 10 | owner-approved-source-order, flagpole-end-level-chain; [record](../../docs/history/M2-T32-player-control-modes.md) |
| M2 T33 | 0 | - | [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S1 | 0 | 14 | owner-approved-source-order, movement-state-chain; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S2 | 0 | 8 | owner-approved-source-order, climbing-chain; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S3 | 0 | 28 | owner-approved-source-order, physics-chain; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T33 S4 | 0 | 12 | owner-approved-source-order, animation-friction-chain; [record](../../docs/history/M2-T33-player-movement-state.md) |
| M2 T34 | 0 | - | [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| M2 T34 S1 | 0 | 5 | owner-approved-source-order, fireball-dispatch-chain; [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| M2 T34 S2 | 0 | 4 | owner-approved-source-order, fireball-core-chain; [record](../../docs/history/M2-T34-fireball-dispatch-core.md) |
| M2 T35 | 0 | - | [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S1 | 0 | 8 | owner-approved-source-order, bubble-setup-movement-chain; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S2 | 0 | 4 | owner-approved-source-order, timer-chain; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S3 | 0 | 7 | owner-approved-source-order, jumpspring-chain; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T35 S4 | 0 | 3 | owner-approved-source-order, vine-setup-chain; [record](../../docs/history/M2-T35-bubbles-timer-warp.md) |
| M2 T36 | 0 | - | [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S1 | 0 | 6 | owner-approved-source-order, vine-actor-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S2 | 0 | 10 | owner-approved-source-order, hammer-lifecycle-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S3 | 0 | 6 | owner-approved-source-order, coin-allocation-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S4 | 0 | 6 | owner-approved-source-order, misc-lifetime-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S5 | 0 | 8 | owner-approved-source-order, score-hud-chain; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T36 S6 | 0 | 4 | owner-approved-source-order, power-up-initialization; [record](../../docs/history/M2-T36-misc-object-chains.md) |
| M2 T37 | 0 | - | [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S1 | 0 | 6 | owner-approved-source-order, power-up-actor-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S2 | 0 | 13 | owner-approved-source-order, head-hit-position-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S3 | 0 | 11 | owner-approved-source-order, block-content-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S4 | 0 | 4 | owner-approved-source-order, shatter-top-coin-chunks-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S5 | 0 | 5 | owner-approved-source-order, block-lifetime-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S6 | 0 | 3 | owner-approved-source-order, block-replacement-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S7 | 0 | 6 | owner-approved-source-order, horizontal-movement-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S8 | 0 | 14 | owner-approved-source-order, vertical-adapter-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T37 S9 | 0 | 12 | owner-approved-source-order, common-gravity-chain; [record](../../docs/history/M2-T37-power-up-block-movement.md) |
| M2 T38 | 0 | - | [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S1 | 0 | 17 | owner-approved-source-order, enemy-loop-dispatch-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S2 | 0 | 19 | owner-approved-source-order, enemy-record-parser-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S3 | 0 | 3 | owner-approved-source-order, initializer-vector-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S4 | 0 | 23 | owner-approved-source-order, common-initializer-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S5 | 0 | 13 | owner-approved-source-order, lakitu-spiny-allocation-chain; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S6 | 0 | 4 | owner-approved-source-order, firebar-initialization-and-duplicate-dependency; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T38 S7 | 0 | 10 | owner-approved-source-order, complete-flying-fish-initializer; [record](../../docs/history/M2-T38-enemy-stream-initialization.md) |
| M2 T39 | 0 | - | [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S1 | 0 | 12 | owner-approved-source-order, bowser-and-flame-initializer; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S2 | 0 | 5 | owner-approved-source-order, fireworks-initializer; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S3 | 0 | 14 | owner-approved-source-order, bullet-swimming-fish-allocation; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S4 | 0 | 8 | owner-approved-source-order, group-enemy-allocation; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S5 | 0 | 9 | owner-approved-source-order, small-initializers-frenzy-dispatch; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S6 | 0 | 20 | owner-approved-source-order, platform-initialization-chain; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S7 | 0 | 4 | owner-approved-source-order, actor-vector-retainer-chain; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S8 | 0 | 4 | owner-approved-source-order, normal-actor-movement-vector; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T39 S9 | 0 | 7 | owner-approved-source-order, special-actor-platform-callers; [record](../../docs/history/M2-T39-special-initialization-and-dispatch.md) |
| M2 T4 | 0 | - | [record](../../docs/history/M2-T4-player-route-and-collision.md); S not recorded |
| M2 T40 | 0 | - | [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S1 | 0 | 2 | owner-approved-source-order, podoboo-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S2 | 0 | 24 | owner-approved-source-order, hammer-bro-normal-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S3 | 0 | 5 | owner-approved-source-order, jumping-red-paratroopa; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S4 | 0 | 10 | owner-approved-source-order, green-paratroopa-x-counters; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S5 | 0 | 16 | owner-approved-source-order, bloober-swimming; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S6 | 0 | 2 | owner-approved-source-order, bullet-bill-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S7 | 0 | 7 | owner-approved-source-order, swimming-cheep-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S8 | 0 | 32 | owner-approved-source-order, firebar-position-collision; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S9 | 0 | 6 | owner-approved-source-order, flying-cheep-movement; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T40 S10 | 0 | 16 | owner-approved-source-order, lakitu-movement-distance; [record](../../docs/history/M2-T40-enemy-movement-and-firebar.md) |
| M2 T41 | 0 | - | [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S1 | 0 | 6 | owner-approved-source-order, bridge-collapse; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S2 | 0 | 19 | owner-approved-source-order, bowser-control; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S3 | 0 | 4 | owner-approved-source-order, bowser-graphics-chain; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S4 | 0 | 12 | owner-approved-source-order, bowser-flame-chain; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S5 | 0 | 3 | owner-approved-source-order, fireworks-lifetime; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S6 | 0 | 20 | owner-approved-source-order, star-flag; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S7 | 0 | 6 | owner-approved-source-order, piranha-movement; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S8 | 0 | 2 | owner-approved-source-order, firebar-spin; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S9 | 0 | 26 | owner-approved-source-order, balanced-platforms; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S10 | 0 | 6 | owner-approved-source-order, vertical-platforms; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S11 | 0 | 9 | owner-approved-source-order, horizontal-platforms; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S12 | 0 | 5 | owner-approved-source-order, lift-platforms; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T41 S13 | 0 | 5 | owner-approved-source-order, offscreen-bounds; [record](../../docs/history/M2-T41-bridge-bowser-and-platforms.md) |
| M2 T42 | 0 | - | [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S1 | 0 | 6 | owner-approved-source-order, fireball-enemy-scan; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S2 | 0 | 11 | owner-approved-source-order, fireball-hit; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S3 | 0 | 3 | owner-approved-source-order, hammer-contact; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S4 | 0 | 6 | owner-approved-source-order, powerup-pickup; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S5 | 0 | 34 | owner-approved-source-order, player-enemy-contact; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S6 | 0 | 16 | owner-approved-source-order, enemy-pair-collision; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S7 | 0 | 14 | owner-approved-source-order, platform-collision; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S8 | 0 | 4 | owner-approved-source-order, platform-positioning; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T42 S9 | 0 | 4 | owner-approved-source-order, collision-preflight; [record](../../docs/history/M2-T42-shared-collision-and-platforms.md) |
| M2 T43 | 0 | - | [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S1 | 0 | 31 | owner-approved-source-order, player-terrain; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S2 | 0 | 3 | owner-approved-source-order, coin-axe-effects; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S3 | 0 | 14 | owner-approved-source-order, flagpole-vine-climbing; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S4 | 0 | 7 | owner-approved-source-order, hidden-spring-metatiles; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S5 | 0 | 3 | owner-approved-source-order, pipe-entry-warp; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S6 | 0 | 5 | owner-approved-source-order, side-impediment; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S7 | 0 | 8 | owner-approved-source-order, metatile-classification; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S8 | 0 | 18 | owner-approved-source-order, enemy-background-stun; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S9 | 0 | 14 | owner-approved-source-order, enemy-landing-grounded; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S10 | 0 | 9 | owner-approved-source-order, enemy-side-jump-hammer; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S11 | 0 | 3 | owner-approved-source-order, enemy-ground-query-nonsolids; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S12 | 0 | 3 | owner-approved-source-order, fireball-background-collision; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S13 | 0 | 11 | owner-approved-source-order, object-bounding-box-entry; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S14 | 0 | 7 | owner-approved-source-order, bounding-box-core-clipping; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T43 S15 | 0 | 7 | owner-approved-source-order, shared-box-collision-geometry; [record](../../docs/history/M2-T43-terrain-and-bounding-boxes.md) |
| M2 T44 | 0 | - | [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S1 | 0 | 14 | owner-approved-source-order, block-buffer-core; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S2 | 0 | 6 | owner-approved-source-order, vine-object-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S3 | 0 | 14 | owner-approved-source-order, six-sprite-hammer-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S4 | 0 | 9 | owner-approved-source-order, flagpole-oam-dump-helpers; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S5 | 0 | 10 | owner-approved-source-order, large-platform-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S6 | 0 | 5 | owner-approved-source-order, floatey-jumping-coin-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S7 | 0 | 6 | owner-approved-source-order, power-up-graphics; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T44 S8 | 0 | 44 | owner-approved-source-order, enemy-graphics-animation; [record](../../docs/history/M2-T44-block-buffer-and-object-graphics.md) |
| M2 T45 | 0 | - | [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S1 | 0 | 13 | owner-approved-source-order, enemy-graphics-oam-tail; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S2 | 0 | 14 | owner-approved-source-order, block-chunk-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S3 | 0 | 7 | owner-approved-source-order, fireball-firebar-explosion-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S4 | 0 | 6 | owner-approved-source-order, small-platform-oam; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T45 S5 | 0 | 5 | owner-approved-source-order, bubble-player-graphics-data; [record](../../docs/proposals/m2/t45-object-oam-tail-and-graphics.md) |
| M2 T46 | 0 | - | [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S1 | 0 | 13 | owner-approved-source-order, player-graphics-dispatch-offscreen; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S2 | 0 | 5 | owner-approved-source-order, intermediate-player-row-render; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S3 | 0 | 13 | owner-approved-source-order, player-action-animation-control; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T46 S4 | 0 | 12 | owner-approved-source-order, player-size-attribute-control; [record](../../docs/proposals/m2/t46-player-graphics-control.md) |
| M2 T47 | 0 | - | [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S1 | 0 | 1 | owner-approved-source-order, player-attribute-exit; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S2 | 0 | 9 | owner-approved-source-order, relative-object-position; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S3 | 0 | 1 | owner-approved-source-order, player-offscreen-entry; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S4 | 0 | 26 | owner-approved-source-order, shared-offscreen-chain; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T47 S5 | 0 | 3 | owner-approved-source-order, sprite-row-writer; [record](../../docs/proposals/m2/t47-object-position-and-sprite-output.md) |
| M2 T48 | 0 | - | [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S1 | 0 | 13 | owner-approved-source-order, soundengine-entry; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S2 | 0 | 9 | owner-approved-source-order, apu-register-helpers; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S3 | 0 | 14 | owner-approved-source-order, square-one-effect-phases; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S4 | 0 | 16 | owner-approved-source-order, square-one-dispatch-lifetime; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S5 | 0 | 18 | owner-approved-source-order, square-two-effect-phases; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T48 S6 | 0 | 4 | owner-approved-source-order, square-two-dispatch; [record](../../docs/proposals/m2/t48-sound-effects-and-channel-handlers.md) |
| M2 T49 | 0 | - | [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S1 | 0 | 14 | owner-approved-source-order, square-two-remaining-effects; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S2 | 0 | 12 | owner-approved-source-order, noise-effects-music-handoff; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S3 | 0 | 10 | owner-approved-source-order, music-selection-header-load; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S4 | 0 | 11 | owner-approved-source-order, square-two-music-stream; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S5 | 0 | 8 | owner-approved-source-order, square-one-music-stream; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S6 | 0 | 6 | owner-approved-source-order, triangle-music-stream; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S7 | 0 | 8 | owner-approved-source-order, noise-music-beat-stream; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S8 | 0 | 9 | owner-approved-source-order, shared-music-helpers; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T49 S9 | 0 | 23 | owner-approved-source-order, music-header-data; [record](../../docs/proposals/m2/t49-music-engine-and-channel-handlers.md) |
| M2 T5 | 2 | - | [record](../../docs/history/M2-T5-object-routes.md); S not recorded |
| M2 T50 | 0 | - | [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md); [record](../../docs/states/QUEUE.md) |
| M2 T50 S1 | 0 | 21 | owner-approved-source-order, music-stream-data; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T50 S2 | 0 | 5 | declared-plan, music-lookup-data; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T50 S3 | 0 | 2 | declared-plan, noise-envelope-data; [record](../../docs/proposals/m2/t50-music-data-and-audio-consumers.md) |
| M2 T51 | 0 | - | [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md); [record](../../docs/proposals/m2/t21-t49-source-order-recovery.md); [record](../../docs/states/QUEUE.md) |
| M2 T51 S1 | 0 | 0 | owner-approved-completion, nmi-parent-integration; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S2 | 0 | 4 | owner-approved-completion, screen-parser-output-chain; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S3 | 0 | 1 | owner-approved-completion, kill-enemies-shared-primitive; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S4 | 0 | 34 | owner-approved-completion, enemy-stream-data-chain-and-consumer; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T51 S5 | 0 | 0 | cross-route-integration-certification; [record](../../docs/proposals/m2/t51-residual-equivalence-and-certification.md) |
| M2 T52 | 0 | - | [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S1 | 0 | 0 | owner-approved-current-equivalence-remediation, a2-nmi-prefix-state-handoff; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S2 | 0 | 0 | owner-approved-current-equivalence-remediation, a6-title-demo-world-select-order; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S3 | 0 | 1 | owner-approved-current-equivalence-remediation, a7-floatey-score-timer-order; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S4 | 0 | 0 | owner-approved-current-equivalence-remediation, b2-background-player-palette-fallthrough; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S5 | 0 | 0 | owner-approved-current-equivalence-remediation, b3-timeup-task-handoff; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
| M2 T52 S6 | 0 | 1 | owner-approved-current-equivalence-remediation, h9-large-platform-y-source; [record](../../docs/proposals/m2/t52-current-audit-mismatch-remediation.md) |
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
| M2 T70 | 0 | - | [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S1 | 0 | 0 | owner-approved-source-order, final-current-certification; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S2 | 0 | 0 | owner-approved-source-order, final-current-certification; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S3 | 0 | 0 | source-provenance-reconciliation; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S4 | 0 | 6 | nmi-prefix-material-phase-proof; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S5 | 0 | 0 | timer-random-material-audit; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S6 | 0 | 9 | sprite-zero-scroll-phase-audit; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S7 | 0 | 6 | sprite-shuffle-material-audit; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S8 | 0 | 0 | pause-state-material-audit; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S9 | 0 | 10 | serial-input-pause-material-chain; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S10 | 0 | 25 | title-menu-demo-material-audit; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S11 | 0 | 15 | victory-message-termination-material-repair; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S12 | 0 | 10 | floatey-score-oam-material-repair; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S13 | 0 | 13 | screen-palette-material-order-repair; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S14 | 0 | 12 | hud-intermediate-timer-chain; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S15 | 0 | 17 | final-reset-startup-source-and-graph-review; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S16 | 0 | 0 | executable-data-binding-manifest; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S17 | 0 | 111 | material-use-completeness-and-path-reconciliation, corrective-title-pointer-output-chain, corrective-column-output-chain, corrective-parser-output-chain; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
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
| M3 T2 | 0 | - | [record](../../docs/history/M3-T1-neutral-render-command-seam.md); [record](../../docs/history/M3-T2-win32-command-consumer.md); S not recorded |
| M3 T3 | 0 | - | [record](../../docs/history/M3-T2-win32-command-consumer.md); [record](../../docs/history/M3-T3-colored-text-frame.md); S not recorded |
| M3 T4 | 0 | - | [record](../../docs/history/M3-T3-colored-text-frame.md); [record](../../docs/history/M3-T4-vga-indexed-frame.md); S not recorded |
| M3 T5 | 0 | - | [record](../../docs/history/M3-T4-vga-indexed-frame.md); [record](../../docs/history/M3-T5-dos16-composition-root.md); S not recorded |
| M3 T6 | 0 | - | [record](../../docs/history/M3-T5-dos16-composition-root.md); [record](../../docs/history/M3-T6-opennt-mz-link.md); S not recorded |
| M3 T7 | 0 | - | [record](../../docs/history/M3-T6-opennt-mz-link.md); [record](../../docs/history/M3-T7-dos-hardware-hooks.md); S not recorded |
| M3 T8 | 0 | - | [record](../../docs/history/M3-T7-dos-hardware-hooks.md); [record](../../docs/history/M3-T8-dos-runtime-structural-evidence.md); S not recorded |
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
| transfer-t70-s2-parser-1 | M2 T29 S7 | M2 T70 S2 | 27 | Coordinator under owner ongoing original-source M2 mandate accepts bounded29-node parser maintenance receipt before implementation.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s2-parser-2 | M2 T30 S11 | M2 T70 S2 | 1 | Coordinator under owner ongoing original-source M2 mandate accepts bounded29-node parser maintenance receipt before implementation.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s2-parser-3 | M2 T30 S16 | M2 T70 S2 | 1 | Coordinator under owner ongoing original-source M2 mandate accepts bounded29-node parser maintenance receipt before implementation.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s4-nmi-1 | M2 T22 S15 | M2 T70 S4 | 3 | Coordinator under owner ongoing M2 mandate accepts6-node NMI prefix maintenance before shared repair.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s4-nmi-2 | M2 T52 S1 | M2 T70 S4 | 1 | Coordinator under owner ongoing M2 mandate accepts6-node NMI prefix maintenance before shared repair.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s4-nmi-3 | M2 T53 S3 | M2 T70 S4 | 1 | Coordinator under owner ongoing M2 mandate accepts6-node NMI prefix maintenance before shared repair.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s4-nmi-4 | M2 T22 S23 | M2 T70 S4 | 1 | Coordinator under owner ongoing M2 mandate accepts6-node NMI prefix maintenance before shared repair.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s6-phase-1 | M2 T52 S1 | M2 T70 S6 | 2 | Coordinator accepts bounded sprite-zero visible-phase maintenance repair under owner ongoing M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s6-phase-2 | M2 T22 S26 | M2 T70 S6 | 4 | Coordinator accepts bounded sprite-zero visible-phase maintenance repair under owner ongoing M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s6-child-1 | M2 T22 S26 | M2 T70 S6 | 3 | Coordinator accepts shared sprite-clear entry dependencies under owner ongoing M2 corrective mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s7-shuffle-1 | M2 T22 S27 | M2 T70 S7 | 6 | Coordinator accepts bounded shared shuffle/preset repair under owner ongoing M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s9-input-1 | M2 T22 S24 | M2 T70 S9 | 6 | Coordinator accepts shared input/pause repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s9-input-2 | M2 T28 S6 | M2 T70 S9 | 4 | Coordinator accepts shared input/pause repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-1 | M2 T25 S20 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-2 | M2 T25 S7 | M2 T70 S10 | 3 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-3 | M2 T25 S9 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-4 | M2 T52 S2 | M2 T70 S10 | 2 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-5 | M2 T25 S12 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-6 | M2 T25 S13 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-7 | M2 T25 S14 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-8 | M2 T25 S8 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-9 | M2 T25 S15 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-10 | M2 T25 S16 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-11 | M2 T25 S17 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-12 | M2 T25 S18 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-13 | M2 T25 S19 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-14 | M2 T25 S21 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-15 | M2 T25 S22 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-16 | M2 T25 S23 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-17 | M2 T25 S24 | M2 T70 S10 | 1 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s10-title-18 | M2 T25 S25 | M2 T70 S10 | 5 | Coordinator receives source-confirmed title score-clear repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s11-victory-1 | M2 T26 S5 | M2 T70 S11 | 14 | Coordinator receives victory-message/final shared-call repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s11-victory-2 | M2 T30 S14 | M2 T70 S11 | 1 | Coordinator receives victory-message/final shared-call repair under owner ongoing mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s12-floatey-1 | M2 T26 S5 | M2 T70 S12 | 7 | Coordinator receives original floating-score chain under owner ongoing M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s12-floatey-2 | M2 T52 S3 | M2 T70 S12 | 3 | Coordinator receives original floating-score chain under owner ongoing M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s13-palette-1 | M2 T27 S1 | M2 T70 S13 | 16 | Coordinator accepts screen palette source-order maintenance under owner M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s13-palette-2 | M2 T52 S4 | M2 T70 S13 | 3 | Coordinator accepts screen palette source-order maintenance under owner M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s14-hud-1 | M2 T27 S2 | M2 T70 S14 | 9 | Coordinator accepts under owner ongoing M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s14-hud-2 | M2 T52 S5 | M2 T70 S14 | 3 | Coordinator accepts under owner ongoing M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s15-startup-1 | M2 T22 S14 | M2 T70 S15 | 7 | Coordinator accepts original reset/startup subtree under owner M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s15-startup-2 | M2 T28 S5 | M2 T70 S15 | 4 | Coordinator accepts original reset/startup subtree under owner M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s15-startup-3 | M2 T28 S6 | M2 T70 S15 | 2 | Coordinator accepts original reset/startup subtree under owner M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s15-startup-4 | M2 T29 S1 | M2 T70 S15 | 4 | Coordinator accepts original reset/startup subtree under owner M2 mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-title-pointer-1 | M2 T27 S2 | M2 T70 S17 | 3 | Coordinator under standing owner M2 repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-column-output-1 | M2 T28 S1 | M2 T70 S17 | 11 | Coordinator under owner same-S M2 repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-parser-output-1 | M2 T70 S2 | M2 T70 S17 | 29 | Coordinator under owner same-S M2 repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-parser-output-2 | M2 T29 S7 | M2 T70 S17 | 3 | Coordinator under owner same-S M2 repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-castle-counter-1 | M2 T29 S9 | M2 T70 S17 | 6 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-pipe-scratch-1 | M2 T29 S9 | M2 T70 S17 | 6 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-scenery-output-1 | M2 T29 S6 | M2 T70 S17 | 19 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-1 | M2 T22 S28 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-2 | M2 T25 S7 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-3 | M2 T26 S5 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-4 | M2 T29 S5 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-5 | M2 T29 S8 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-6 | M2 T31 S1 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-7 | M2 T31 S4 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-dispatch-scratch-8 | M2 T33 S1 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-hole-threshold-1 | M2 T32 S1 | M2 T70 S17 | 2 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-raw-pipe-2 | M2 T29 S9 | M2 T70 S17 | 4 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-raw-pipe-3 | M2 T30 S12 | M2 T70 S17 | 1 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-raw-pipe-4 | M2 T30 S9 | M2 T70 S17 | 4 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-whirlpool-1 | M2 T31 S2 | M2 T70 S17 | 3 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-fireball-index-1 | M2 T34 S2 | M2 T70 S17 | 2 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-color-counter-1 | M2 T28 S2 | M2 T70 S17 | 4 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| transfer-t70-s17-injury-palette-1 | M2 T70 S13 | M2 T70 S17 | 6 | Coordinator under owner same-S repair mandate.; [record](../../docs/proposals/m2/t70-final-current-certification.md) |

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
| M2 T70 S1 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S2 | 29 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S3 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S4 | 6 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S5 | 7 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S6 | 9 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S7 | 6 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S8 | 6 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S9 | 10 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S10 | 25 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S11 | 15 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S12 | 10 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S13 | 19 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S14 | 12 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S15 | 17 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S16 | 0 | 1992 | none / 0 | none / 0 | closed; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
| M2 T70 S17 | 950 | 1992 | none / 0 | none / 0 | admitted; [record](../../docs/proposals/m2/t70-final-current-certification.md) |
