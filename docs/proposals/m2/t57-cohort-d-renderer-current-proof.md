# M2 T57: Cohort D renderer, metatiles and block-buffer current-equivalence proof

T57 continues the approved source-order current-equivalence program immediately after T56. It audits all 146 Cohort D labels from `FlagpoleObject` through `L_WaterArea3`. Historical ROM-match accounting remains 1,992 / 1,992; this T records fresh current ROM-logic and operational evidence only.

## Task scope and closure

T57 is divided into seven bounded chains. Each chain performs source comparison, any required shared-C repair, original-ROM/current x86/x64 controlled-route comparison, focused native verification and a platform-purity audit. Product-source changes also require the shared DOS16 link and refreshed `mysmb16.exe`, `mysmb32.exe` and `mysmb64.exe`. A feasible mismatch remains in its owning S until repair and repeat audit leave no scoped difference.

T57 closes only when every scoped label, feasible control relation and material producer-consumer relation is current-exact, and its cross-chain matrix proves the object rendering, address-selection and stream-consumer joins.

## Planned source-order S chains

| S | Entry to exit | Labels | Shared C owner and common route |
| --- | --- | ---: | --- |
| S1 | `FlagpoleObject -> StrCOffset` | 26 | `src/game/area.c plus src/game/oam/flagpole_gfx.c`; flagpole, rope, object-row and cannon object-family matrix. |
| S2 | `StaircaseHeightData -> ExitDecBlock` | 13 | `src/game/area.c`; staircase, jumpspring and question/brick object matrix. |
| S3 | `HoleMetatiles -> GetBlockBufferAddr` | 16 | `src/game/area.c`; hole, whirlpool, under-part and block-buffer address matrix. |
| S4 | `AreaDataOfsLoopback -> StoreStyle` | 7 | `src/game/area.c`; area-pointer, type and fore/style attribute matrix. |
| S5 | `WorldAddrOffsets -> AreaDataAddrHigh` | 16 | `src/game/game_data.c plus src/game/area.c consumer`; world/area pointer-table selection matrix. |
| S6 | `E_CastleArea1 -> E_WaterArea3` | 34 | `src/game/game_data.c plus src/game/area.c consumer`; enemy-area stream decoding matrix. |
| S7 | `L_CastleArea1 -> L_WaterArea3` | 34 | `src/game/game_data.c plus src/game/area.c consumer`; level-area stream decoding matrix. |

## Exact node scope

| ROM line | Node | Planned S |
| ---: | --- | --- |
| 3991 | `FlagpoleObject` | S1 |
| 4018 | `EndlessRope` | S1 |
| 4023 | `BalancePlatRope` | S1 |
| 4034 | `DrawRope` | S1 |
| 4039 | `CoinMetatileData` | S1 |
| 4042 | `RowOfCoins` | S1 |
| 4049 | `C_ObjectRow` | S1 |
| 4052 | `C_ObjectMetatile` | S1 |
| 4055 | `CastleBridgeObj` | S1 |
| 4060 | `AxeObj` | S1 |
| 4064 | `ChainObj` | S1 |
| 4070 | `EmptyBlock` | S1 |
| 4074 | `ColObj` | S1 |
| 4079 | `SolidBlockMetatiles` | S1 |
| 4082 | `BrickMetatiles` | S1 |
| 4086 | `RowOfBricks` | S1 |
| 4091 | `DrawBricks` | S1 |
| 4094 | `RowOfSolidBlocks` | S1 |
| 4097 | `GetRow` | S1 |
| 4099 | `DrawRow` | S1 |
| 4104 | `ColumnOfBricks` | S1 |
| 4109 | `ColumnOfSolidBlocks` | S1 |
| 4112 | `GetRow2` | S1 |
| 4120 | `BulletBillCannon` | S1 |
| 4135 | `SetupCannon` | S1 |
| 4146 | `StrCOffset` | S1 |
| 4151 | `StaircaseHeightData` | S2 |
| 4154 | `StaircaseRowData` | S2 |
| 4157 | `StaircaseObject` | S2 |
| 4162 | `NextStair` | S2 |
| 4172 | `Jumpspring` | S2 |
| 4197 | `Hidden1UpBlock` | S2 |
| 4204 | `QuestionBlock` | S2 |
| 4208 | `BrickWithCoins` | S2 |
| 4212 | `BrickWithItem` | S2 |
| 4220 | `BWithL` | S2 |
| 4223 | `DrawQBlk` | S2 |
| 4228 | `GetAreaObjectID` | S2 |
| 4233 | `ExitDecBlock` | S2 |
| 4237 | `HoleMetatiles` | S3 |
| 4240 | `Hole_Empty` | S3 |
| 4265 | `StrWOffset` | S3 |
| 4266 | `NoWhirlP` | S3 |
| 4273 | `RenderUnderPart` | S3 |
| 4289 | `DrawThisRow` | S3 |
| 4290 | `WaitOneRow` | S3 |
| 4296 | `ExitUPartR` | S3 |
| 4300 | `ChkLrgObjLength` | S3 |
| 4303 | `ChkLrgObjFixedLength` | S3 |
| 4310 | `LenSet` | S3 |
| 4313 | `GetLrgObjAttrib` | S3 |
| 4326 | `GetAreaObjXPosition` | S3 |
| 4336 | `GetAreaObjYPosition` | S3 |
| 4349 | `BlockBufferAddr` | S3 |
| 4353 | `GetBlockBufferAddr` | S3 |
| 4376 | `AreaDataOfsLoopback` | S4 |
| 4381 | `LoadAreaPointer` | S4 |
| 4384 | `GetAreaType` | S4 |
| 4392 | `FindAreaPointer` | S4 |
| 4402 | `GetAreaDataAddrs` | S4 |
| 4434 | `StoreFore` | S4 |
| 4472 | `StoreStyle` | S4 |
| 4485 | `WorldAddrOffsets` | S5 |
| 4491 | `AreaAddrOffsets` | S5 |
| 4492 | `World1Areas` | S5 |
| 4493 | `World2Areas` | S5 |
| 4494 | `World3Areas` | S5 |
| 4495 | `World4Areas` | S5 |
| 4496 | `World5Areas` | S5 |
| 4497 | `World6Areas` | S5 |
| 4498 | `World7Areas` | S5 |
| 4499 | `World8Areas` | S5 |
| 4509 | `EnemyAddrHOffsets` | S5 |
| 4512 | `EnemyDataAddrLow` | S5 |
| 4520 | `EnemyDataAddrHigh` | S5 |
| 4528 | `AreaDataHOffsets` | S5 |
| 4531 | `AreaDataAddrLow` | S5 |
| 4539 | `AreaDataAddrHigh` | S5 |
| 4550 | `E_CastleArea1` | S6 |
| 4558 | `E_CastleArea2` | S6 |
| 4565 | `E_CastleArea3` | S6 |
| 4574 | `E_CastleArea4` | S6 |
| 4583 | `E_CastleArea5` | S6 |
| 4589 | `E_CastleArea6` | S6 |
| 4598 | `E_GroundArea1` | S6 |
| 4606 | `E_GroundArea2` | S6 |
| 4613 | `E_GroundArea3` | S6 |
| 4619 | `E_GroundArea4` | S6 |
| 4627 | `E_GroundArea5` | S6 |
| 4636 | `E_GroundArea6` | S6 |
| 4643 | `E_GroundArea7` | S6 |
| 4650 | `E_GroundArea8` | S6 |
| 4656 | `E_GroundArea9` | S6 |
| 4662 | `E_GroundArea10` | S6 |
| 4666 | `E_GroundArea11` | S6 |
| 4674 | `E_GroundArea12` | S6 |
| 4679 | `E_GroundArea13` | S6 |
| 4687 | `E_GroundArea14` | S6 |
| 4695 | `E_GroundArea15` | S6 |
| 4700 | `E_GroundArea16` | S6 |
| 4704 | `E_GroundArea17` | S6 |
| 4714 | `E_GroundArea18` | S6 |
| 4722 | `E_GroundArea19` | S6 |
| 4731 | `E_GroundArea20` | S6 |
| 4738 | `E_GroundArea21` | S6 |
| 4743 | `E_GroundArea22` | S6 |
| 4751 | `E_UndergroundArea1` | S6 |
| 4760 | `E_UndergroundArea2` | S6 |
| 4769 | `E_UndergroundArea3` | S6 |
| 4777 | `E_WaterArea1` | S6 |
| 4783 | `E_WaterArea2` | S6 |
| 4791 | `E_WaterArea3` | S6 |
| 4799 | `L_CastleArea1` | S7 |
| 4814 | `L_CastleArea2` | S7 |
| 4832 | `L_CastleArea3` | S7 |
| 4849 | `L_CastleArea4` | S7 |
| 4865 | `L_CastleArea5` | S7 |
| 4884 | `L_CastleArea6` | S7 |
| 4900 | `L_GroundArea1` | S7 |
| 4915 | `L_GroundArea2` | S7 |
| 4931 | `L_GroundArea3` | S7 |
| 4944 | `L_GroundArea4` | S7 |
| 4963 | `L_GroundArea5` | S7 |
| 4980 | `L_GroundArea6` | S7 |
| 4995 | `L_GroundArea7` | S7 |
| 5009 | `L_GroundArea8` | S7 |
| 5027 | `L_GroundArea9` | S7 |
| 5042 | `L_GroundArea10` | S7 |
| 5048 | `L_GroundArea11` | S7 |
| 5059 | `L_GroundArea12` | S7 |
| 5066 | `L_GroundArea13` | S7 |
| 5081 | `L_GroundArea14` | S7 |
| 5096 | `L_GroundArea15` | S7 |
| 5113 | `L_GroundArea16` | S7 |
| 5123 | `L_GroundArea17` | S7 |
| 5143 | `L_GroundArea18` | S7 |
| 5160 | `L_GroundArea19` | S7 |
| 5177 | `L_GroundArea20` | S7 |
| 5191 | `L_GroundArea21` | S7 |
| 5200 | `L_GroundArea22` | S7 |
| 5210 | `L_UndergroundArea1` | S7 |
| 5231 | `L_UndergroundArea2` | S7 |
| 5252 | `L_UndergroundArea3` | S7 |
| 5271 | `L_WaterArea1` | S7 |
| 5282 | `L_WaterArea2` | S7 |
| 5299 | `L_WaterArea3` | S7 |

## S1 admission — flagpole, object-row and cannon chain

S1 admits the contiguous 26-label chain `FlagpoleObject -> StrCOffset`: `FlagpoleObject`, `EndlessRope`, `BalancePlatRope`, `DrawRope`, `CoinMetatileData`, `RowOfCoins`, `C_ObjectRow`, `C_ObjectMetatile`, `CastleBridgeObj`, `AxeObj`, `ChainObj`, `EmptyBlock`, `ColObj`, `SolidBlockMetatiles`, `BrickMetatiles`, `RowOfBricks`, `DrawBricks`, `RowOfSolidBlocks`, `GetRow`, `DrawRow`, `ColumnOfBricks`, `ColumnOfSolidBlocks`, `GetRow2`, `BulletBillCannon`, `SetupCannon`, `StrCOffset`. Its predecessor is T56 S6's parser-object dispatch; S2 receives the adjacent staircase/question-block family. The principal shared owner is `src/game/area.c`; flagpole OAM output is consumed through the existing shared `src/game/oam/flagpole_gfx.c` owner.

All 26 labels are historically ROM-match complete and currently need fresh evidence. This is therefore a zero historical-credit audit: it may mark labels current-exact only after both verification tracks pass. The ROM-logic track compares dispatch, object-type selection, table binding, object length/state writes, rope and bridge tile loops, cannon setup and direct caller/return relations. The operational track records the same controlled original-ROM/current x86/x64 flagpole, rope, castle-bridge and cannon routes; runs `mysmb.area-special-object-smoke`, `mysmb.area-rope-object-smoke`, `mysmb.area-cannon-smoke` and `mysmb.area-castle-column-smoke`; and runs platform-purity verification. A product repair uses the same shared source in the DOS16 link and refreshes all three executable artifacts.

## S1 closure

Pending. No T57 label is promoted merely by admission. Any mismatch is repaired in S1 and the same ROM-logic and operational routes are repeated before S2 is admitted.
