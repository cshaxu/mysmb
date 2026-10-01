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
| S4 | `AreaDataOfsLoopback -> StoreStyle` | 7 | `src/game/enemy/loop.c` plus `src/game/area/area_data.c`; loopback, area-pointer, type and fore/style attribute matrix. |
| S5 | `WorldAddrOffsets -> AreaDataAddrHigh` | 16 | `src/game/area/area_data.c`; world/area pointer-table selection matrix. |
| S6 | `E_CastleArea1 -> E_WaterArea3` | 34 | `src/game/area/area_data.c` owner-local PRG data plus `src/game/enemy/stream.c`; enemy-area stream decoding matrix. |
| S7 | `L_CastleArea1 -> L_WaterArea3` | 34 | `src/game/area/area_data.c` owner-local PRG data plus area decoder; level-area stream decoding matrix. |

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

## S1 P1 and closure — flagpole, object-row and cannon chain

S1 closes all 26 scoped labels current-exact: `FlagpoleObject`, `EndlessRope`,
`BalancePlatRope`, `DrawRope`, `CoinMetatileData`, `RowOfCoins`,
`C_ObjectRow`, `C_ObjectMetatile`, `CastleBridgeObj`, `AxeObj`, `ChainObj`,
`EmptyBlock`, `ColObj`, `SolidBlockMetatiles`, `BrickMetatiles`,
`RowOfBricks`, `DrawBricks`, `RowOfSolidBlocks`, `GetRow`, `DrawRow`,
`ColumnOfBricks`, `ColumnOfSolidBlocks`, `GetRow2`, `BulletBillCannon`,
`SetupCannon` and `StrCOffset`. The source audit covers all 61 incident
control relations; 48 newly become exact and the 13 already-exact dispatch
relations remain confirmed. This chain has no material-relation entry.

P1 repaired the one feasible difference. Original `FlagpoleObject` calls
`RenderUnderPart` for rows 1--9, so it uses the shared protected-tile overlay
rule and leaves the final object-height value. The C loop had written those
rows directly. It now calls the same shared rendering primitive; ball/base
stores and flag object initialization remain in their original order. The new
flagpole regression sets both a protected foreground tile and a replaceable
`$c0` tile, and proves the ROM result, final height and flag object state.

The controlled original-ROM/current x86/x64 routes `t22-flagpole`,
`t29-special-object` and `t29-geometry-castle` agree for enemy flag state,
cannon ring, staging and parser RAM; x86/x64 records are byte-identical. Four
focused object tests pass on both widths, the same shared source links as
DOS16, and platform-purity passes. The rebuilt artifacts are `mysmb16.exe`
SHA-256 `1366D2D9BB535A129C0E3AFE2D4B90C5121CE21F0E8FB525AEF29E5984AB1A92`,
`mysmb32.exe` SHA-256 `D082F788987AA6D8F84DC68976B0D10D8F099A6D2CD677309E0626F72C9FC16E`,
and `mysmb64.exe` SHA-256 `2F74E41FA6F2A73E6E0EB9B9941D52B026ABD62F415D2519C84F8137B0FD7DB4`.
Historical conformance remains 1,992 / 1,992.

## S2 admission — staircase, jumpspring and question/brick chain

S2 admits the contiguous 13-label chain `StaircaseHeightData -> ExitDecBlock`:
`StaircaseHeightData`, `StaircaseRowData`, `StaircaseObject`, `NextStair`,
`Jumpspring`, `Hidden1UpBlock`, `QuestionBlock`, `BrickWithCoins`,
`BrickWithItem`, `BWithL`, `DrawQBlk`, `GetAreaObjectID` and `ExitDecBlock`.
S1 is its predecessor; S3 receives hole and block-buffer handling. The shared
owner is `src/game/area.c`. All labels are historically complete and need
current evidence, so expected historical credit remains zero.

The ROM-logic track compares staircase decrement/table indexing, jumpspring
slot and coordinate initialization, hidden-block gate, question/brick selector
and shared draw/return tails. The operational track uses a controlled
original-ROM/current x86/x64 staircase, jumpspring and question/brick matrix,
focused staircase/jumpspring/item-block tests and platform-purity. A product
repair must use shared C, rebuild the DOS16 link and refresh all three target
artifacts. A feasible difference remains in S2 until repair and repeated audit
close it.

## S2 closure — staircase, jumpspring and question/brick chain

S2 closes all 13 scoped labels current-exact. The source comparison finds no
feasible difference in post-decrement staircase table indexing, jump-spring
slot fallback and actor initialization, hidden-1UP early return, question/brick
selector arithmetic, or the `DrawQBlk -> GetLrgObjAttrib -> DrawRow` tail.
The 39 incident control relations are exact; 27 are newly exact and 12 were
already exact dispatch/shared-tail relations.

The controlled matrix covers 12 staircase cases, eight jump-spring ordinary
slot/full-pool cases, and 72 item-block selector/area-type/hidden-state cases.
Original ROM, current x86 and current x64 agree in every scoped state range,
and native records are byte-identical. Focused staircase, jump-spring and
item-block smokes pass on both widths. No product source changed, so the S1
three-artifact set remains current. Historical conformance remains 1,992 /
1,992.

## S3 admission — hole, under-part and block-buffer-address chain

S3 admits the contiguous 16-label chain `HoleMetatiles -> GetBlockBufferAddr`:
`HoleMetatiles`, `Hole_Empty`, `StrWOffset`, `NoWhirlP`, `RenderUnderPart`,
`DrawThisRow`, `WaitOneRow`, `ExitUPartR`, `ChkLrgObjLength`,
`ChkLrgObjFixedLength`, `LenSet`, `GetLrgObjAttrib`,
`GetAreaObjXPosition`, `GetAreaObjYPosition`, `BlockBufferAddr` and
`GetBlockBufferAddr`. S2 is its predecessor and S4 owns the pointer-loading
continuation. The shared owner is `src/game/area.c` with the shared block-buffer
consumer. All labels are historically complete and require current evidence,
so expected historical credit remains zero.

The ROM-logic track compares water-only whirlpool registration/ring wrap,
hole rendering, UnderPart loop/overlay paths, large-object length and
attribute helpers, coordinate helpers, and block-buffer address selection.
The operational track uses a controlled original-ROM/current x86/x64 matrix
and focused hole/helper/address tests. A feasible difference remains in S3
until shared-C repair and repeat audit close it.


## S3 closure — hole, under-part and block-buffer-address chain

S3 closes `HoleMetatiles`, `Hole_Empty`, `StrWOffset`, `NoWhirlP`,
`RenderUnderPart`, `DrawThisRow`, `WaitOneRow`, `ExitUPartR`,
`ChkLrgObjLength`, `ChkLrgObjFixedLength`, `LenSet`, `GetLrgObjAttrib`,
`GetAreaObjXPosition`, `GetAreaObjYPosition`, `BlockBufferAddr` and
`GetBlockBufferAddr`. Static source comparison found no remaining shared-C
difference: the water-only initialization gate, five-entry whirlpool ring,
page borrow, downward overlay predicate and loop, attribute/length helpers,
coordinate helpers, two-buffer pointer table and collision caller all preserve
the original branch/data ordering. The controlled original-ROM/current x86/x64
matrix executed 98 hole/UnderPart, 20 helper and 48 block-address routes; all
had zero persistent non-ABI work-RAM differences and byte-identical native
records. The three focused smokes passed on both widths. All 16 labels and 29
newly evidenced feasible incident controls are current-exact; no repair or
artifact refresh was required. Current registry: 408 exact nodes and 871 exact
feasible control relations; historical conformance remains 1,992 / 1,992.

## S4 admission — area-pointer/type/attribute chain

S4 admits the contiguous seven-label chain `AreaDataOfsLoopback -> StoreStyle`:
`AreaDataOfsLoopback`, `LoadAreaPointer`, `GetAreaType`, `FindAreaPointer`,
`GetAreaDataAddrs`, `StoreFore` and `StoreStyle`. S3 is its predecessor and
S5 owns the world/area-table continuation. The shared owners are
`src/game/enemy/loop.c` for the loopback table and
`src/game/area/area_data.c` for pointer/header semantics; `src/game/area.c`
is only the downstream area-offset consumer. All labels are historically complete and require current
evidence, so expected historical credit remains zero. The ROM-logic track will
compare parser loopback, pointer lookup, type masking, pointer-data reads and
foreground/style gates; the operational track will run the focused pointer
tests, controlled original-ROM/current x86/x64 route matrix, DOS16 link and
platform-purity check. A feasible difference remains in S4 until shared-C
repair and repeat audit close it.

## S4 closure — loopback, area-pointer and header-attribute chain

S4 closes all seven labels current-exact: `AreaDataOfsLoopback`,
`LoadAreaPointer`, `GetAreaType`, `FindAreaPointer`, `GetAreaDataAddrs`,
`StoreFore` and `StoreStyle`. The source audit corrected the former ownership
claim: the eleven-byte loopback table is owned by `src/game/enemy/loop.c`,
where `mysmb_enemy_exec_loopback` consumes its retained matched index before
the downstream parser sees `AreaDataOffset`; the pointer/type/header sequence
is owned by `src/game/area/area_data.c`. No shared-C behavior differed from
the original ROM.

The pointer matrix has 70 lookup/header routes plus the no-swap termination
route. It executes all 188 relevant source table bytes, all foreground,
background-color and style/cloud-override predicates, and the ContinueGame /
SetInitNTHigh continuations. The loop matrix has 96 `ProcLoopCommand` routes:
all enter `$c047`, 22 take `ExecGameLoopback` at `$c08c`, and all eleven
`AreaDataOfsLoopback` entries are selected. Both matrices have zero persistent
work-RAM differences between original ROM and current x86/x64, and the x86 and
x64 records are byte-identical. The pointer/header, parser-data and
enemy-loop smokes pass on both widths; platform-purity passes; the shared
OpenNT DOS16 link produces `mysmb-dos16.exe` with only its established
`OLDNAMES.LIB` warning.

All seven labels, 17 newly evidenced feasible incident control relations and
the loopback material relation are now exact. No product source changed: the
test-only recorder fixture adds an existing controlled loop input to the
native recorder, so no three-artifact refresh is required. The current registry
is 415 exact nodes and 888 exact feasible control relations; historical
conformance remains 1,992 / 1,992.

## S5 admission — world/area and stream-pointer table chain

S5 admits the contiguous 16-label data chain `WorldAddrOffsets ->
AreaDataAddrHigh`: `WorldAddrOffsets`, `AreaAddrOffsets`, `World1Areas`,
`World2Areas`, `World3Areas`, `World4Areas`, `World5Areas`, `World6Areas`,
`World7Areas`, `World8Areas`, `EnemyAddrHOffsets`, `EnemyDataAddrLow`,
`EnemyDataAddrHigh`, `AreaDataHOffsets`, `AreaDataAddrLow` and
`AreaDataAddrHigh`. S4 is its predecessor and S6 receives the selected enemy
streams. The shared owner is `src/game/area/area_data.c`; platform code stays
a consumer. All labels are historically complete and need current evidence,
so expected historical credit remains zero.

The ROM-logic track compares all source bytes, WorldNAreas aliases, 8-bit
world/area and type-base additions, enemy and area low/high pointer pairing,
and the resulting consumer handoff. The operational track uses the controlled
original-ROM/current x86/x64 table matrix, focused pointer/header smoke, DOS16
link and platform-purity. A feasible difference remains in S5 until shared-C
repair and the same audit leave no scoped difference.

## S5 closure — world/area and stream-pointer table chain

S5 closes all 16 scoped labels current-exact: `WorldAddrOffsets`,
`AreaAddrOffsets`, `World1Areas`, `World2Areas`, `World3Areas`,
`World4Areas`, `World5Areas`, `World6Areas`, `World7Areas`, `World8Areas`,
`EnemyAddrHOffsets`, `EnemyDataAddrLow`, `EnemyDataAddrHigh`,
`AreaDataHOffsets`, `AreaDataAddrLow` and `AreaDataAddrHigh`. The generated
owner-local C source matches all 188 original-ROM bytes across these table
regions. Static comparison also confirms the byte-truncated world/area and
type-base sums, aliases and paired low/high loads in `area_data.c`.

The controlled original-ROM/current x86/x64 pointer matrix repeats 70
lookup/header routes plus the no-swap termination route and consumes every
one of the 188 table bytes. All compared persistent work RAM matches, and
x86/x64 records are byte-identical. The pointer/header smoke and
platform-purity pass on both widths; the shared OpenNT DOS16 link passes with
the established `OLDNAMES.LIB` warning. No shared-C difference or product
source change was found, so no three-artifact refresh is required.

All 16 nodes and six table-to-consumer material relations are exact. The
current registry is 431 exact nodes and 888 exact feasible controls; historical
conformance remains 1,992 / 1,992.


## S6 admission — enemy-area stream data and consumer chain

**Entry / exit.** `E_CastleArea1` through `E_WaterArea3`, as bound by the S5
enemy-pointer tables, then consumed by `mysmb_enemy_stream_process_current` in
`src/game/enemy/stream.c` through record termination, page command, row command,
spawn/group dispatch and fallback.  This S ends at the stream owner boundary; its
callees retain their independently admitted obligations.

**Scope and incoming state.** The exact 34 labels below are all
`needs-evidence` in the current-equivalence registry.  Historical M2 completion is
already 1,992 / 1,992, so the node-progress expected-match subset is empty; the
current-equivalence target is to make all 34 labels exact.  S5 is the predecessor;
S7 begins the distinct area-object-data consumer chain.

`E_CastleArea1`, `E_CastleArea2`, `E_CastleArea3`, `E_CastleArea4`,
`E_CastleArea5`, `E_CastleArea6`, `E_GroundArea1`, `E_GroundArea2`,
`E_GroundArea3`, `E_GroundArea4`, `E_GroundArea5`, `E_GroundArea6`,
`E_GroundArea7`, `E_GroundArea8`, `E_GroundArea9`, `E_GroundArea10`,
`E_GroundArea11`, `E_GroundArea12`, `E_GroundArea13`, `E_GroundArea14`,
`E_GroundArea15`, `E_GroundArea16`, `E_GroundArea17`, `E_GroundArea18`,
`E_GroundArea19`, `E_GroundArea20`, `E_GroundArea21`, `E_GroundArea22`,
`E_UndergroundArea1`, `E_UndergroundArea2`, `E_UndergroundArea3`,
`E_WaterArea1`, `E_WaterArea2`, `E_WaterArea3`.

**Shared ownership.** The generated owner-local PRG array is materialized through
`src/game/area/area_data.c`; `src/game/enemy/stream.c` alone owns the portable C90
read, page, decode and stream state transition.  No platform adapter participates.

**ROM-logic track.** Compare every bounded stream byte and `$ff` terminator with
the admitted owner ROM, including the `E_GroundArea9` / `E_GroundArea10` shared
terminator.  Run controlled original-ROM/current x86/x64 stream fixtures that
cover record read, page advance, row command, hard-mode suppression, group ID,
end-of-buffer fallback and offset wrap.  Compare only source-relevant persistent
RAM/OAM/PPU fields and record established ABI exclusions explicitly.

**Operational track.** Run `mysmb.enemy-stream-smoke`,
`mysmb.enemy-stream`, `mysmb.enemy-stream-local-consumer`,
`mysmb.platform-purity` for x86/x64, plus the shared-core DOS16 link.  A product
repair would refresh all three local target artifacts; an audit-only closure will
not.

**Exit.** Static byte/ownership/edge audit and controlled ROM/native route must
have no unresolved scoped difference.  Any feasible mismatch is repaired in this
S and re-audited before S7 admission.


## S6 closure — enemy-area stream data and consumer chain

All 34 scoped labels are current-equivalence exact. The static audit bound 1,087 stream bytes, all 34 pointer targets, every `$ff` termination and the `E_GroundArea9` / `E_GroundArea10` shared terminator to the generated owner-local PRG and the shared `area_data.c` / `enemy/stream.c` chain. The 80 controlled `t38-stream` original-ROM/current x86/x64 routes all entered `ProcessEnemyData` at `$c144`; compared persistent state had zero differences and x86/x64 records were byte-identical. Focused stream/local-consumer and platform-purity tests pass in both widths; OpenNT relinked the unchanged shared DOS16 core. No product source mismatch was found, so target artifacts were not refreshed. `material-00075` is exact.
