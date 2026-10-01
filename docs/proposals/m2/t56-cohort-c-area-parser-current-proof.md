# M2 T56: Cohort C area-parser current-equivalence proof

T56 is the source-order second half of Cohort C. It audits the contiguous area-parser slice from `AreaParserTaskHandler` through `FlagBalls_Residual`. Historical ROM-match accounting remains unchanged; this task records current ROM-logic and operational evidence only.

## Task scope and closure

T56 contains six contiguous shared-game chains. Each S performs the source comparison, repair if needed, controlled original-ROM/current x86/x64 route, focused native test, DOS16 build when product code changes, platform-purity audit and artifact refresh for product changes. A mismatch stays with its S until repair and repeat audit leave no feasible difference.

T56 closes only when all 120 labels, every owned feasible control relation and every material producer-consumer relation are current-exact, and its cross-chain matrix covers parser cadence, scenery/terrain, stream decoding, special objects, pipe/allocation and bridge selectors.

## Planned source-order S chains

| S | Entry to exit | Labels | Shared C owner and common route |
| --- | --- | ---: | --- |
| S1 | `AreaParserTaskHandler -> AreaParserCore` | 14 | `src/game/area.c`; Parser task cadence, wrap and scenery-table selector chain. |
| S2 | `RenderSceneryTerrain -> BlockBuffLowBounds` | 20 | `src/game/area.c`; Scenery construction, terrain mask and block-buffer handoff chain. |
| S3 | `ProcessAreaData -> SetFore` | 32 | `src/game/area.c`; Area-data stream decoding, normalization and parser attribute chain. |
| S4 | `ScrollLockObject_Warp -> NotTall` | 27 | `src/game/area.c`; Warp/scroll, frenzy, style-object, pulley and castle construction chain. |
| S5 | `PlayerStop -> QuestionBlockRow_High` | 22 | `src/game/area.c`; Castle finish, pipe variants, allocation and high question-row chain. |
| S6 | `QuestionBlockRow_Low -> FlagBalls_Residual` | 5 | `src/game/area.c`; Low question-row, bridge selector and residual flag-ball data chain. |

## Exact node scope

| ROM line | Node | Planned S |
| ---: | --- | --- |
| 3060 | `AreaParserTaskHandler` | S1 |
| 3065 | `DoAPTasks` | S1 |
| 3071 | `SkipATRender` | S1 |
| 3073 | `AreaParserTasks` | S1 |
| 3087 | `IncrementColumnPos` | S1 |
| 3094 | `NoColWrap` | S1 |
| 3106 | `BSceneDataOffsets` | S1 |
| 3109 | `BackSceneryData` | S1 |
| 3131 | `BackSceneryMetatiles` | S1 |
| 3145 | `FSceneDataOffsets` | S1 |
| 3148 | `ForeSceneryData` | S1 |
| 3158 | `TerrainMetatiles` | S1 |
| 3161 | `TerrainRenderBits` | S1 |
| 3179 | `AreaParserCore` | S1 |
| 3184 | `RenderSceneryTerrain` | S2 |
| 3187 | `ClrMTBuf` | S2 |
| 3193 | `ThirdP` | S2 |
| 3198 | `RendBack` | S2 |
| 3223 | `SceLoop1` | S2 |
| 3231 | `RendFore` | S2 |
| 3235 | `SceLoop2` | S2 |
| 3238 | `NoFore` | S2 |
| 3242 | `RendTerr` | S2 |
| 3249 | `TerMTile` | S2 |
| 3253 | `StoreMT` | S2 |
| 3258 | `TerrLoop` | S2 |
| 3269 | `NoCloud2` | S2 |
| 3270 | `TerrBChk` | S2 |
| 3275 | `NextTBit` | S2 |
| 3285 | `EndUChk` | S2 |
| 3290 | `RendBBuf` | S2 |
| 3295 | `ChkMTLow` | S2 |
| 3306 | `StrBlock` | S2 |
| 3319 | `BlockBuffLowBounds` | S2 |
| 3326 | `ProcessAreaData` | S3 |
| 3328 | `ProcADLoop` | S3 |
| 3345 | `Chk1Row13` | S3 |
| 3363 | `Chk1Row14` | S3 |
| 3367 | `CheckRear` | S3 |
| 3370 | `RdyDecode` | S3 |
| 3372 | `SetBehind` | S3 |
| 3373 | `NextAObj` | S3 |
| 3374 | `ChkLength` | S3 |
| 3378 | `ProcLoopb` | S3 |
| 3384 | `EndAParse` | S3 |
| 3386 | `IncAreaObjOffset` | S3 |
| 3393 | `DecodeAreaData` | S3 |
| 3397 | `Chk1stB` | S3 |
| 3408 | `ChkRow14` | S3 |
| 3416 | `ChkRow13` | S3 |
| 3429 | `Mask2MSB` | S3 |
| 3431 | `ChkSRows` | S3 |
| 3442 | `LrgObj` | S3 |
| 3450 | `NotWPipe` | S3 |
| 3452 | `SpecObj` | S3 |
| 3455 | `MoveAOId` | S3 |
| 3459 | `NormObj` | S3 |
| 3472 | `LeavePar` | S3 |
| 3473 | `InitRear` | S3 |
| 3479 | `LoopCmdE` | S3 |
| 3480 | `BackColC` | S3 |
| 3489 | `StrAObj` | S3 |
| 3492 | `RunAObj` | S3 |
| 3561 | `AlterAreaAttributes` | S3 |
| 3580 | `Alter2` | S3 |
| 3586 | `SetFore` | S3 |
| 3591 | `ScrollLockObject_Warp` | S4 |
| 3600 | `WarpNum` | S4 |
| 3606 | `ScrollLockObject` | S4 |
| 3615 | `KillEnemies` | S4 |
| 3619 | `KillELoop` | S4 |
| 3623 | `NoKillE` | S4 |
| 3629 | `FrenzyIDData` | S4 |
| 3632 | `AreaFrenzy` | S4 |
| 3635 | `FreCompLoop` | S4 |
| 3640 | `ExitAFrenzy` | S4 |
| 3646 | `AreaStyleObject` | S4 |
| 3653 | `TreeLedge` | S4 |
| 3665 | `MidTreeL` | S4 |
| 3670 | `EndTreeL` | S4 |
| 3673 | `MushroomLedge` | S4 |
| 3682 | `EndMushL` | S4 |
| 3696 | `AllUnder` | S4 |
| 3699 | `NoUnder` | S4 |
| 3706 | `PulleyRopeMetatiles` | S4 |
| 3709 | `PulleyRopeObject` | S4 |
| 3717 | `RenderPul` | S4 |
| 3719 | `MushLExit` | S4 |
| 3724 | `CastleMetatiles` | S4 |
| 3737 | `CastleObject` | S4 |
| 3748 | `CRendLoop` | S4 |
| 3759 | `ChkCFloor` | S4 |
| 3772 | `NotTall` | S4 |
| 3789 | `PlayerStop` | S5 |
| 3791 | `ExitCastle` | S5 |
| 3795 | `WaterPipe` | S5 |
| 3810 | `IntroPipe` | S5 |
| 3817 | `VPipeSectLoop` | S5 |
| 3823 | `NoBlankP` | S5 |
| 3825 | `SidePipeShaftData` | S5 |
| 3828 | `SidePipeTopPart` | S5 |
| 3831 | `SidePipeBottomPart` | S5 |
| 3835 | `ExitPipe` | S5 |
| 3840 | `RenderSidewaysPipe` | S5 |
| 3855 | `DrawSidePart` | S5 |
| 3862 | `VerticalPipeData` | S5 |
| 3868 | `VerticalPipe` | S5 |
| 3876 | `WarpPipe` | S5 |
| 3900 | `DrawPipe` | S5 |
| 3911 | `GetPipeHeight` | S5 |
| 3921 | `FindEmptyEnemySlot` | S5 |
| 3923 | `EmptyChkLoop` | S5 |
| 3929 | `ExitEmptyChk` | S5 |
| 3933 | `Hole_Water` | S5 |
| 3944 | `QuestionBlockRow_High` | S5 |
| 3948 | `QuestionBlockRow_Low` | S6 |
| 3960 | `Bridge_High` | S6 |
| 3964 | `Bridge_Middle` | S6 |
| 3968 | `Bridge_Low` | S6 |
| 3983 | `FlagBalls_Residual` | S6 |

## S1 admission - parser task and scenery-table chain

S1 receives `AreaParserTaskHandler -> AreaParserCore`. Its predecessor is T55's completed PPU handoff; S2 consumes its parser-core handoff. The ROM-logic track covers persistent parser-task initialization, descending task selectors, column/page wrap, scenery offsets and terrain-mask table binding. The operational track uses a controlled original-ROM/current x86/x64 parser-column route, focused parser schedule and buffer-commit checks, the shared DOS16 link when product code changes, and the platform-purity audit. All labels were historically complete at admission, so S1 expects zero historical-credit delta.
