# M2 T66: Cohort L player graphics, relative positions and offscreen proof

T65 closed before this owner-approved next source-order task. Actual Cohort L
contains83 labels at ASM14460-15069,165 pending control relations and9
enumerated material rows (one already exact,8 pending). All83 nodes incoming
needs-evidence. Current1633/1992 nodes,3485/4317 feasible controls(raw4342,
infeasible25),394/492 material partial; historical1992/1992 separate.
Maximum T66 node exact1716/1992. Source order and existing custody retained;
this task registers audit/repair participation, not silent ownership transfers.

## Exact bounded S plan

| S | Contiguous chain and shared owner | Nodes / intended fresh | Exact labels | Control IDs |
| --- | --- | ---: | --- | --- |
| S1 | PlayerGfxHandler through ExPlyrAt: full player graphics/action/change-size/attribute chain; src/game/oam/player_gfx.c | 44 / 44 | PlayerGfxHandler; CntPl; SwimKT; BigKTS; ExPGH; FindPlayerAction; DoChangeSize; PlayerKilled; PlayerGfxProcessing; SUpdR; PlayerOffscreenChk; PROfsLoop; NPROffscr; IntermediatePlayerData; DrawPlayer_Intermediate; PIntLoop; RenderPlayerSub; DrawPlayerLoop; ProcessPlayerAction; ProcOnGroundActs; NonAnimatedActs; ActionFalling; ActionWalkRun; ActionClimbing; ActionSwimming; GetCurrentAnimOffset; FourFrameExtent; ThreeFrameExtent; AnimationControl; SetAnimC; ExAnimC; GetGfxOffsetAdder; SzOfs; ChangeSizeOffsetAdder; HandleChangeSize; CSzNext; GorSLog; GetOffsetFromAnimCtrl; ShrinkPlayer; ShrPlF; ChkForPlayerAttrib; KilledAtt; C_S_IGAtt; ExPlyrAt | control-03027, control-03028, control-03029, control-03030, control-03031, control-03032, control-03033, control-03034, control-03035, control-03036, control-03037, control-03038, control-03039, control-03040, control-03041, control-03042, control-03043, control-03044, control-03045, control-03046, control-03047, control-03048, control-03049, control-03050, control-03051, control-03052, control-03053, control-03054, control-03055, control-03056, control-03057, control-03058, control-03059, control-03060, control-03061, control-03062, control-03063, control-03064, control-03065, control-03066, control-03067, control-03068, control-03069, control-03070, control-03071, control-03072, control-03073, control-03074, control-03075, control-03076, control-03077, control-03078, control-03079, control-03080, control-03081, control-03082, control-03083, control-03084, control-03085, control-03086, control-03087, control-03088, control-03089, control-03090, control-03091, control-03092, control-03093, control-03094, control-03095, control-03096, control-03097, control-03098, control-03099, control-03100, control-03101, control-03102, control-03103, control-03104, control-03105, control-03106, control-03107, control-03108, control-03109, control-03110, control-03111, control-03112, control-03113, control-03114, control-04033, control-04034, control-04035, control-04036, control-04037, control-04038, control-04039, control-04040, control-04041, control-04042, control-04043, control-04044, control-04045, control-04046, control-04047 |
| S2 | Relative object entry aliases and shared coordinate subtraction; src/game/oam/object_position.c | 9 / 9 | RelativePlayerPosition; RelativeBubblePosition; RelativeFireballPosition; RelWOfs; RelativeMiscPosition; RelativeEnemyPosition; RelativeBlockPosition; VariableObjOfsRelPos; GetObjRelativePosition | control-03115, control-03116, control-03117, control-03118, control-03119, control-03120, control-03121, control-03122, control-03123, control-03124, control-03125, control-03126, control-04048, control-04049, control-04050, control-04051, control-04052, control-04053 |
| S3 | Object offscreen wrappers and shared X/Y call composition; src/game/oam/object_position.c | 11 / 11 | GetPlayerOffscreenBits; GetFireballOffscreenBits; GetBubbleOffscreenBits; GetMiscOffscreenBits; ObjOffsetData; GetProperObjOffset; GetEnemyOffscreenBits; GetBlockOffscreenBits; SetOffscrBitsOffset; GetOffScreenBitsSet; RunOffscrBitsSubs | control-03127, control-03128, control-03129, control-03130, control-03131, control-03132, control-03133, control-03134, control-03135, control-03136, control-03137, control-03138, control-03139, control-04054, control-04055, control-04056, control-04057, control-04058 |
| S4 | Horizontal offscreen data, page difference and loop; src/game/oam/object_position.c | 6 / 6 | XOffscreenBitsData; DefaultXOnscreenOfs; GetXOffscreenBits; XOfsLoop; XLdBData; ExXOfsBS | control-03140, control-03141, control-03142, control-03143, control-03144, control-03145, control-03146, control-03147, control-04059 |
| S5 | Vertical offscreen data, page difference and shared division; src/game/oam/object_position.c | 10 / 10 | YOffscreenBitsData; DefaultYOnscreenOfs; HighPosUnitData; GetYOffscreenBits; YOfsLoop; YLdBData; ExYOfsBS; DividePDiff; SetOscrO; ExDivPD | control-03148, control-03149, control-03150, control-03151, control-03152, control-03153, control-03154, control-03155, control-03156, control-03157, control-03158, control-03159, control-04060 |
| S6 | Shared two-sprite row emission and flip attributes; src/game/oam/sprite_row.c | 3 / 3 | DrawSpriteObject; NoHFlip; SetHFAt | control-03160, control-03161, control-03162, control-03163 |
| S7 | Cross-chain evidence census and current integration matrix, full native regressions and original DOS16 link | 83 / 0 | All83 labels above, already exact required | Remaining owned controls/material census, no inferred fresh credit. |

Every S admits only its exact source-order set; a mismatch is repaired and
re-audited within that S before its successor. ROM-logic proof and operational
proof are separate. The former checks branches, reads/writes, byte arithmetic,
tables, actual caller inputs/returns and producer-consumer handoffs. The latter
checks focused native tests, x86/x64 builds, purity and original OpenNT DOS16
link; every product-code P refreshes three owner-authorized assets EXEs.
Pure audit/test/evidence P retains latest products. No platform business logic.

## Exact node receiving and audit participation map

| ASM line | Inventory label | Existing maintenance receiver | T66 audit S | Incoming |
| --- | --- | --- | --- | --- |
| 14460 | `PlayerGfxHandler` | M2 T46 S1 | S1 | needs-evidence |
| 14466 | `CntPl` | M2 T46 S1 | S1 | needs-evidence |
| 14489 | `SwimKT` | M2 T46 S1 | S1 | needs-evidence |
| 14495 | `BigKTS` | M2 T46 S1 | S1 | needs-evidence |
| 14497 | `ExPGH` | M2 T46 S1 | S1 | needs-evidence |
| 14499 | `FindPlayerAction` | M2 T46 S1 | S1 | needs-evidence |
| 14503 | `DoChangeSize` | M2 T46 S1 | S1 | needs-evidence |
| 14507 | `PlayerKilled` | M2 T46 S1 | S1 | needs-evidence |
| 14511 | `PlayerGfxProcessing` | M2 T46 S1 | S1 | needs-evidence |
| 14532 | `SUpdR` | M2 T46 S1 | S1 | needs-evidence |
| 14535 | `PlayerOffscreenChk` | M2 T46 S1 | S1 | needs-evidence |
| 14547 | `PROfsLoop` | M2 T46 S1 | S1 | needs-evidence |
| 14551 | `NPROffscr` | M2 T46 S1 | S1 | needs-evidence |
| 14561 | `IntermediatePlayerData` | M2 T46 S2 | S1 | needs-evidence |
| 14564 | `DrawPlayer_Intermediate` | M2 T46 S2 | S1 | needs-evidence |
| 14566 | `PIntLoop` | M2 T46 S2 | S1 | needs-evidence |
| 14587 | `RenderPlayerSub` | M2 T46 S2 | S1 | needs-evidence |
| 14601 | `DrawPlayerLoop` | M2 T46 S2 | S1 | needs-evidence |
| 14610 | `ProcessPlayerAction` | M2 T46 S3 | S1 | needs-evidence |
| 14626 | `ProcOnGroundActs` | M2 T46 S3 | S1 | needs-evidence |
| 14642 | `NonAnimatedActs` | M2 T46 S3 | S1 | needs-evidence |
| 14649 | `ActionFalling` | M2 T46 S3 | S1 | needs-evidence |
| 14654 | `ActionWalkRun` | M2 T46 S3 | S1 | needs-evidence |
| 14659 | `ActionClimbing` | M2 T46 S3 | S1 | needs-evidence |
| 14666 | `ActionSwimming` | M2 T46 S3 | S1 | needs-evidence |
| 14676 | `GetCurrentAnimOffset` | M2 T46 S3 | S1 | needs-evidence |
| 14680 | `FourFrameExtent` | M2 T46 S3 | S1 | needs-evidence |
| 14684 | `ThreeFrameExtent` | M2 T46 S3 | S1 | needs-evidence |
| 14687 | `AnimationControl` | M2 T46 S3 | S1 | needs-evidence |
| 14701 | `SetAnimC` | M2 T46 S3 | S1 | needs-evidence |
| 14702 | `ExAnimC` | M2 T46 S3 | S1 | needs-evidence |
| 14705 | `GetGfxOffsetAdder` | M2 T46 S4 | S1 | needs-evidence |
| 14712 | `SzOfs` | M2 T46 S4 | S1 | needs-evidence |
| 14714 | `ChangeSizeOffsetAdder` | M2 T46 S4 | S1 | needs-evidence |
| 14718 | `HandleChangeSize` | M2 T46 S4 | S1 | needs-evidence |
| 14728 | `CSzNext` | M2 T46 S4 | S1 | needs-evidence |
| 14729 | `GorSLog` | M2 T46 S4 | S1 | needs-evidence |
| 14734 | `GetOffsetFromAnimCtrl` | M2 T46 S4 | S1 | needs-evidence |
| 14741 | `ShrinkPlayer` | M2 T46 S4 | S1 | needs-evidence |
| 14750 | `ShrPlF` | M2 T46 S4 | S1 | needs-evidence |
| 14753 | `ChkForPlayerAttrib` | M2 T46 S4 | S1 | needs-evidence |
| 14767 | `KilledAtt` | M2 T46 S4 | S1 | needs-evidence |
| 14774 | `C_S_IGAtt` | M2 T46 S4 | S1 | needs-evidence |
| 14781 | `ExPlyrAt` | M2 T47 S1 | S1 | needs-evidence |
| 14786 | `RelativePlayerPosition` | M2 T47 S2 | S2 | needs-evidence |
| 14791 | `RelativeBubblePosition` | M2 T47 S2 | S2 | needs-evidence |
| 14797 | `RelativeFireballPosition` | M2 T47 S2 | S2 | needs-evidence |
| 14801 | `RelWOfs` | M2 T47 S2 | S2 | needs-evidence |
| 14805 | `RelativeMiscPosition` | M2 T47 S2 | S2 | needs-evidence |
| 14811 | `RelativeEnemyPosition` | M2 T47 S2 | S2 | needs-evidence |
| 14816 | `RelativeBlockPosition` | M2 T47 S2 | S2 | needs-evidence |
| 14825 | `VariableObjOfsRelPos` | M2 T47 S2 | S2 | needs-evidence |
| 14834 | `GetObjRelativePosition` | M2 T47 S2 | S2 | needs-evidence |
| 14846 | `GetPlayerOffscreenBits` | M2 T47 S3 | S3 | needs-evidence |
| 14851 | `GetFireballOffscreenBits` | M2 T47 S4 | S3 | needs-evidence |
| 14857 | `GetBubbleOffscreenBits` | M2 T47 S4 | S3 | needs-evidence |
| 14863 | `GetMiscOffscreenBits` | M2 T47 S4 | S3 | needs-evidence |
| 14869 | `ObjOffsetData` | M2 T47 S4 | S3 | needs-evidence |
| 14872 | `GetProperObjOffset` | M2 T47 S4 | S3 | needs-evidence |
| 14879 | `GetEnemyOffscreenBits` | M2 T47 S4 | S3 | needs-evidence |
| 14884 | `GetBlockOffscreenBits` | M2 T47 S4 | S3 | needs-evidence |
| 14888 | `SetOffscrBitsOffset` | M2 T47 S4 | S3 | needs-evidence |
| 14894 | `GetOffScreenBitsSet` | M2 T47 S4 | S3 | needs-evidence |
| 14911 | `RunOffscrBitsSubs` | M2 T47 S4 | S3 | needs-evidence |
| 14927 | `XOffscreenBitsData` | M2 T47 S4 | S4 | needs-evidence |
| 14931 | `DefaultXOnscreenOfs` | M2 T47 S4 | S4 | needs-evidence |
| 14934 | `GetXOffscreenBits` | M2 T47 S4 | S4 | needs-evidence |
| 14937 | `XOfsLoop` | M2 T47 S4 | S4 | needs-evidence |
| 14953 | `XLdBData` | M2 T47 S4 | S4 | needs-evidence |
| 14959 | `ExXOfsBS` | M2 T47 S4 | S4 | needs-evidence |
| 14963 | `YOffscreenBitsData` | M2 T47 S4 | S5 | needs-evidence |
| 14968 | `DefaultYOnscreenOfs` | M2 T47 S4 | S5 | needs-evidence |
| 14971 | `HighPosUnitData` | M2 T47 S4 | S5 | needs-evidence |
| 14974 | `GetYOffscreenBits` | M2 T47 S4 | S5 | needs-evidence |
| 14977 | `YOfsLoop` | M2 T47 S4 | S5 | needs-evidence |
| 14993 | `YLdBData` | M2 T47 S4 | S5 | needs-evidence |
| 14999 | `ExYOfsBS` | M2 T47 S4 | S5 | needs-evidence |
| 15003 | `DividePDiff` | M2 T47 S4 | S5 | needs-evidence |
| 15015 | `SetOscrO` | M2 T47 S4 | S5 | needs-evidence |
| 15016 | `ExDivPD` | M2 T47 S4 | S5 | needs-evidence |
| 15025 | `DrawSpriteObject` | M2 T47 S5 | S6 | needs-evidence |
| 15036 | `NoHFlip` | M2 T47 S5 | S6 | needs-evidence |
| 15040 | `SetHFAt` | M2 T47 S5 | S6 | needs-evidence |

## Per-S dependency and route contract

- S1: Original EEE9/EFA4 player roots, injury/swim/death/action/size/throw/offscreen alternatives; actual row, dump and state-selector children. Owner src/game/oam/player_gfx.c; preceding source cohort/S must close first. Existing shared helpers are tested dependencies, no unobserved dependency-node credit. Later S owns any relation outside this exact ASM/caller range.
- S2: Original player/bubble/fireball/misc/enemy/block relative entries, world-page/byte-borrow domains and paired block continuation. Owner src/game/oam/object_position.c; preceding source cohort/S must close first. Existing shared helpers are tested dependencies, no unobserved dependency-node credit. Later S owns any relation outside this exact ASM/caller range.
- S3: Original object-family offsets and real GetX/GetYOffscreenBits input/return plus composed mask scratch. Owner src/game/oam/object_position.c; preceding source cohort/S must close first. Existing shared helpers are tested dependencies, no unobserved dependency-node credit. Later S owns any relation outside this exact ASM/caller range.
- S4: Original F1F6 horizontal roots, both boundary loops, page difference and all table consumers. Owner src/game/oam/object_position.c; preceding source cohort/S must close first. Existing shared helpers are tested dependencies, no unobserved dependency-node credit. Later S owns any relation outside this exact ASM/caller range.
- S5: Original F282 vertical roots, high-page differences, both boundary loops and actual DividePDiff path. Owner src/game/oam/object_position.c; preceding source cohort/S must close first. Existing shared helpers are tested dependencies, no unobserved dependency-node credit. Later S owns any relation outside this exact ASM/caller range.
- S6: Original DrawSpriteObject with all byte X/Y and facing/attribute/carry domains, actual return and OAM order. Owner src/game/oam/sprite_row.c; preceding source cohort/S must close first. Existing shared helpers are tested dependencies, no unobserved dependency-node credit. Later S owns any relation outside this exact ASM/caller range.

Material00430 IntermediatePlayerData and00431 ChangeSizeOffsetAdder belong
to S1 and must prove actual indexed consumers. Material00432 ObjOffsetData
belongs to S3,00433/00434 horizontal tables to S4,00435-00437 vertical tables
to S5. Existing material00279 remains exact without fresh credit. Additional
real producer-consumer gaps are registered by name, never silently omitted.
S7 combines accepted member proofs plus current cross-chain replay and full
native regression; scope does not imply exhaustive global material enumeration.

## S1 admission - complete player graphics owner chain

Entry EEE9 PlayerGfxHandler and EFA4 DrawPlayer_Intermediate, exit F129
ExPlyrAt/handler RTS. Scope44/intended fresh44, all needs-evidence; maximum
current1677/1992 from1633. Historical baseline/maximum1992 and expectedMatches
empty because historical mapping is already complete. Exact names are S1's
row and receiving map above. All S1 control IDs are listed in its plan row;
scope follows original caller ASM lines including child-return relations.
Two pending material relations00430/00431; later L nodes retain pending status.

Shared owner player_gfx.c consumes original player RAM and owner-local PRG;
actual DrawOneSpriteRow and DumpTwoSpr are already implemented K dependencies.
Source audit found PlayerOffscreenChk still replaces the meaningful DumpTwoSpr
call with direct writes. Restore that actual shared call, byte-wrapped Y and
source call/return order; compare actual child inputs and returned RAM before
credit. Sweep covers all player row/erase calls, action/size/attribute branches
and source byte/absolute-indexed address distinctions.

Bounded original EEE9 fixtures cover injury blink, swim feet, normal/death/
change-size selectors, throw timer comparison and three/four-row redraw,
all vertical mask/OAM byte combinations, both facings/sizes, crouch/jump/
fall/walk/skid/climb/swim and grow/shrink completion. EFA4 proves reverse
data copy and actual row loop. Selected row and erase seams are recorded
separately to stay within per-record child budgets; original state-selector
and render/attribute boundaries are audited against source and actual routes.
1841 source-visible RAM bytes include scratch/OAM/aliases0109-0139; true CPU
call stack, unused transient registers/flags are explicit ABI exclusions.
Record visit/branch/continuation counts for each claimed label/edge; no label
or edge becomes exact merely from adjacent full-output equality.

Owner ROM/reviewed local ASM are nonredistributable research inputs; no raw
bytes become tracked fixtures. Ignored build/m2-t66-s1 contains all temporary
work, at most192MiB raw aggregate,2048 roots/chunk,120seconds/run,524288
steps/case, checkpoints and coordinator cleanup. Both dual tracks must pass
with no scoped differences. Product corrections refresh16/32/64 EXEs under
prior explicit owner authorization, including existing audio/title/focus pause.
