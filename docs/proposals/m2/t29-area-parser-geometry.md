# M2 T29: Area parser and large-object geometry

T29 is the source-order receiver for ROM lines 2796--3990.  It follows the
closed T28 bootstrap chains and precedes T30's rendering and metatile chains.
All business behavior belongs in shared C90 game code.  Windows and DOS are
limited to physical input, timing, and submission of the completed frame.

## Delivery contract

This task uses the binding [M2 chain-based S delivery
rule](../../rules/EXECUTION.md#m2-chain-based-s-delivery).  Each S admits one
bounded contiguous control/data chain with one shared owner and one
reproducible original-ROM route.  It performs source mapping, any necessary
shared-C repair, node-level ROM control/data/call comparison, and operational
proof in the same delivery.  Labels remain individually accounted in the
inventory, ledger, and progress tracker.

ROM-equivalence and operational evidence are separate.  Every implementation
P refreshes and records `assets/mysmb16.exe`, `assets/mysmb32.exe`, and
`assets/mysmb64.exe`; one chain-level replay and one three-target build package
cover all labels in that P.  T29 closure additionally requires a cross-chain
parser/area-entry regression matrix.  A chain splits only at an unadmitted
dependency, a shared-game owner boundary, or a branch family that needs a
different source route.

## Planned source-order chains

The table is a planning map, not an advance completion claim.  Every row must
receive an exact ledger receipt and active-packet admission before code work.

| S | Entry and exit | Labels in source order | Shared owner and ROM route |
| --- | --- | --- | --- |
| S1 | `InitPageLoop -> SkipByte` | `InitPageLoop`, `InitByteLoop`, `InitByte`, `SkipByte` | Shared memory-clear primitive; natural reset/cold-start route proves page descent, stack exclusion, and byte writes. |
| S2 | `MusicSelectData -> ExitGetM` | `MusicSelectData`, `GetAreaMusic`, `ChkAreaType`, `StoreMusic`, `ExitGetM` | Shared area/music selector; ordinary area-entry route covers title return, pipe, cloud, and area-type selection. |
| S3 | `PlayerStarting_X_Pos -> SetPESub` | `PlayerStarting_X_Pos`, `AltYPosOffset`, `PlayerStarting_Y_Pos`, `PlayerBGPriorityData`, `GameTimerData`, `Entrance_GameTimerSetup`, `ChkStPos`, `SetStPos`, `ChkOverR`, `ChkSwimE`, `SetPESub` | Shared player/area entry boundary; normal GameEngine entrance route covers water, alternate entrance, timer reload, vine, and bubble branches. |
| S4 | `HalfwayPageNybbles -> DoNothing2` | `HalfwayPageNybbles`, `PlayerLoseLife`, `StillInGame`, `GetHalfway`, `MaskHPNyb`, `SetHalfway`, `GameOverMode`, `SetupGameOver`, `RunGameOver`, `TerminateGame`, `ContinueGame`, `GameIsOn`, `TransposePlayers`, `TransLoop`, `ExTrans`, `DoNothing1`, `DoNothing2` | Shared mode/life-transition family; death, game-over, continue, and two-player routes are separately sampled under one state-transition owner. |
| S5 | `AreaParserTaskHandler -> AreaParserCore` | `AreaParserTaskHandler`, `DoAPTasks`, `SkipATRender`, `AreaParserTasks`, `IncrementColumnPos`, `NoColWrap`, `BSceneDataOffsets`, `BackSceneryData`, `BackSceneryMetatiles`, `FSceneDataOffsets`, `ForeSceneryData`, `TerrainMetatiles`, `TerrainRenderBits`, `AreaParserCore` | Shared parser dispatch; natural area-parser task route proves task vector, column wrap, and scenery data selection. |
| S6 | `RenderSceneryTerrain -> BlockBuffLowBounds` | `RenderSceneryTerrain`, `ClrMTBuf`, `ThirdP`, `RendBack`, `SceLoop1`, `RendFore`, `SceLoop2`, `NoFore`, `RendTerr`, `TerMTile`, `StoreMT`, `TerrLoop`, `NoCloud2`, `TerrBChk`, `NextTBit`, `EndUChk`, `RendBBuf`, `ChkMTLow`, `StrBlock`, `BlockBuffLowBounds` | Shared parser/metatile staging; parser-column route proves metatile buffer and block-buffer write order. |
| S7 | `ProcessAreaData -> SetFore` | `ProcessAreaData`, `ProcADLoop`, `Chk1Row13`, `Chk1Row14`, `CheckRear`, `RdyDecode`, `SetBehind`, `NextAObj`, `ChkLength`, `ProcLoopb`, `EndAParse`, `IncAreaObjOffset`, `DecodeAreaData`, `Chk1stB`, `ChkRow14`, `ChkRow13`, `Mask2MSB`, `ChkSRows`, `LrgObj`, `NotWPipe`, `SpecObj`, `MoveAOId`, `NormObj`, `LeavePar`, `InitRear`, `LoopCmdE`, `BackColC`, `StrAObj`, `RunAObj`, `AlterAreaAttributes`, `Alter2`, `SetFore` | Shared area-stream decoder; source-reachable object-stream route covers row/length/rear-column and normal/large/special object decisions. |
| S8 | `ScrollLockObject_Warp -> MushLExit` | `ScrollLockObject_Warp`, `WarpNum`, `ScrollLockObject`, `KillEnemies`, `KillELoop`, `NoKillE`, `FrenzyIDData`, `AreaFrenzy`, `FreCompLoop`, `ExitAFrenzy`, `AreaStyleObject`, `TreeLedge`, `MidTreeL`, `EndTreeL`, `MushroomLedge`, `EndMushL`, `AllUnder`, `NoUnder`, `PulleyRopeMetatiles`, `PulleyRopeObject`, `RenderPul`, `MushLExit` | Shared special-object parser path; source object streams cover scroll locks, enemy cleanup, frenzy, ledges, and pulley geometry. |
| S9 | `CastleMetatiles -> GetPipeHeight` | `CastleMetatiles`, `CastleObject`, `CRendLoop`, `ChkCFloor`, `NotTall`, `PlayerStop`, `ExitCastle`, `WaterPipe`, `IntroPipe`, `VPipeSectLoop`, `NoBlankP`, `SidePipeShaftData`, `SidePipeTopPart`, `SidePipeBottomPart`, `ExitPipe`, `RenderSidewaysPipe`, `DrawSidePart`, `VerticalPipeData`, `VerticalPipe`, `WarpPipe`, `DrawPipe`, `GetPipeHeight` | Shared large-object geometry path; castle and pipe object streams cover all floor/height/warp variants. |
| S10 | `FindEmptyEnemySlot -> FlagBalls_Residual` | `FindEmptyEnemySlot`, `EmptyChkLoop`, `ExitEmptyChk`, `Hole_Water`, `QuestionBlockRow_High`, `QuestionBlockRow_Low`, `Bridge_High`, `Bridge_Middle`, `Bridge_Low`, `FlagBalls_Residual` | Shared allocation/final object geometry; natural object route covers slot scan and terminal stream data consumers. |

## S1 admission: InitializeMemory loop chain

S1 receives exactly `InitPageLoop`, `InitByteLoop`, `InitByte`, and
`SkipByte` from legacy `M2 T18 S4`.  Its baseline is **265 / 1,992**.  All
four labels are currently open and are expected to become ROM-match complete,
for a maximum of **269 / 1,992**.

The common shared-game owner is the portable memory-clear primitive already
called by the translated cold-start path.  The ROM track audits the original
`$8fbe` parent and `$8fc2-$8fda` loop: descending page traversal, the
`$0100-$015f` write region, the preserved stack window `$0160-$01ff`, Y-byte
wrap, and return condition.  The route is ordinary reset/cold start; the
recorder may set only documented reset input/state and must never inject a
leaf PC or stack.

The operational track adds a focused shared-memory smoke on x86 and x64,
paired ROM/native cold-start recording, the platform-purity gate, OpenNT
DOS16 link, and the three required artifacts.  No platform file may own a
clear range, RAM boundary, or game-state default.

T29 closes only after every planned chain has dual-track evidence, every
incomplete label has an accepted successor, and the integrated area-entry,
parser-column, object-stream, and large-object regression matrix passes on
all three targets.
