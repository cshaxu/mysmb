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
| ROM-match complete | 83 | PlayerOffscreenChk, PROfsLoop, NPROffscr, ScreenOff, Start, VBlank1, VBlank2, WBootCheck, ColdBoot, EndlessLoop, InitializeMemory, VRAM_AddrTable_Low, VRAM_AddrTable_High, VRAM_Buffer_Offset, InitBuffer, PauseRoutine, ChkPauseTimer, ChkStart, ClrPauseTimer, SetPause, ExitPause, VictoryMode, AutoPlayer, TitleScreenMode, GameMenuRoutine, NullJoypad, RunDemo, ResetTitle, StartGame. |
| Mapped / audited, not complete | 114 | Exact names below: 18 known mismatches, 3 missing implementations, 2 changed-body revalidations, and 93 evidence-incomplete mappings. |
| Open / unmatched | 1,795 | Exact open rows in the inventory; responsibility/evidence gaps are now linked individually. Open does not mean unimplemented. |
| **Total** | **1,992** | Unique label/source-line pairs. |

Verified conformance is **83 / 1,992 (4.17%)**. Initial deep verification covered
77 names, yielding three matches, 19 mismatch-affected names and 55 partial
results on the recorded snapshot. One mismatch-affected node and one partial node have since changed in the
working tree and are now marked revalidation required. Historical/current
owner maps contribute 90 additional mapped-but-unverified names (62 T14/T15, 27 T22, one current bullet-bill actor) omitted by the old
77-node accounting. With three additional confirmed missing scheduler/activation entries, the
explicitly dispositioned cohort is 170, of which 153 remain incomplete. These sets are disjoint in the current ledger.

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
| 776 | `ScreenOff` |
| 699 | `Start` |
| 706 | `VBlank1` |
| 708 | `VBlank2` |
| 712 | `WBootCheck` |
| 721 | `ColdBoot` |
| 737 | `EndlessLoop` |
| 2795 | `InitializeMemory` |
| 743 | `VRAM_AddrTable_Low` |
| 752 | `VRAM_AddrTable_High` |
| 761 | `VRAM_Buffer_Offset` |
| 796 | `InitBuffer` |
| 876 | `PauseRoutine` |
| 885 | `ChkPauseTimer` |
| 889 | `ChkStart` |
| 904 | `ClrPauseTimer` |
| 906 | `SetPause` |
| 907 | `ExitPause` |
| 814 | `DecTimers` |
| 820 | `DecTimersLoop` |
| 823 | `SkipExpTimer` |
| 825 | `NoDecTimers` |
| 826 | `PauseSkip` |
| 837 | `RotPRandomBit` |
| 912 | `SpriteShuffler` |
| 917 | `ShuffleLoop` |
| 926 | `StrSprOffset` |
| 927 | `NextSprOffset` |
| 934 | `SetAmtOffset` |
| 937 | `SetMiscOffset` |
| 954 | `OperModeExecutionTree` |
| 843 | `Sprite0Clr` |
| 851 | `Sprite0Hit` |
| 855 | `HBlankDelay` |
| 857 | `SkipSprite0` |
| 868 | `SkipMainOper` |
| 965 | `MoveAllSpritesOffscreen` |
| 969 | `MoveSpritesOffscreen` |
| 972 | `SprInitLoop` |
| 982 | `TitleScreenMode` |
| 996 | `GameMenuRoutine` |
| 1047 | `NullJoypad` |
| 1049 | `RunDemo` |
| 1053 | `ResetTitle` |
| 1004 | `StartGame` |
| 1005 | `ChkSelect` |
| 1013 | `ChkWorldSel` |
| 1018 | `SelectBLogic` |
| 14535 | `PlayerOffscreenChk` |
| 14547 | `PROfsLoop` |
| 14551 | `NPROffscr` |

The following 32 T26 labels have source branch and operational evidence in the
[T26 record](../proposals/m2/t26-victory-terminal.md#s7-closure).

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

## Mapped but not yet matched (114)

These rows have mapping, missing-implementation or deep-audit evidence but are not complete. Their
canonical inventory links identify individual gaps and responsible owners.

| ROM line | Node |
| ---: | --- |
| 764 | `NonMaskableInterrupt` |
| 1033 | `IncWorldSel` |
| 1039 | `UpdateShroom` |
| 1059 | `ChkContinue` |
| 1065 | `StartWorld1` |
| 1081 | `GoContinue` |
| 1119 | `DemoEngine` |
| 2674 | `InitializeGame` |
| 2971 | `GameOverMode` |
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
