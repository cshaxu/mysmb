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
- S5: Original F239 vertical roots, high-page differences, both boundary loops and actual DividePDiff path. Owner src/game/oam/object_position.c; preceding source cohort/S must close first. Existing shared helpers are tested dependencies, no unobserved dependency-node credit. Later S owns any relation outside this exact ASM/caller range.
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

## S1 P2 player graphics source/graph repair and closure

All44 intended S1 nodes become current exact, no deferred/transferred names;
the exact completed names are S1's plan row and individual proof table below.
All103 listed controls and material00430/00431 become exact. Nodes1633 ->
1677/1992, feasible controls3485 ->3588/4317(raw4342,infeasible25 unchanged),
material394 ->396/492 partial. Historical1992/1992 unchanged, historical
expected/actualMatches empty. T66 open with39 pending planned nodes; S2 next,
not admitted. No later L or cross-cohort credit inferred.

### Findings and original-source corrections

1. PROfsLoop directly wrote two OAM bytes instead of the actual DumpTwoSpr
   call. The original stores shifted offscreen scratch before JSR. A2048-root
   pre-repair batch has equal full output but1792 independent caller failures.
   Restore the real shared pair dump with original byte Y and input scratch;
   final output equality alone cannot prove this connection.
2. HandleChangeSize translated CPY #0A / BCC as equality-only termination.
   Original INY wraps byte Y, then every value>=10 resets animation and flag.
   A2048-root extended animation baseline has3328 RAM-byte differences.
   Restore >=10 after byte increment; retain original modulo-byte wrap.
3. CntPl selects the swimming return before calling FindPlayerAction. Death
   and size-change tail jumps never return to that continuation. Native code
   retested the mutable size-change flag after rendering; clearing it this
   frame could wrongly animate a swimming foot. Expanded high-OAM/size-end
   fixtures reveal13 differing bytes in one2048-root batch. Save the original
   branch decision before selection/render; source priority/order is retained.
4. Original ordinary and intermediate entries share DrawPlayerLoop. Native
   had duplicated loops despite matching final RAM. Restore one shared
   mysmb_oam_player_draw_loop called by both. Its source row-count DEC/BNE
   loop and actual DrawOneSpriteRow dependency are the sole production path.

Similar-issue sweep covers every player graphics dispatch/return, both row
callers, all pair erases, grow/shrink termination, action animation and fixed
attribute/foot absolute bases versus byte Y adjustments. The sole size-change
comparison and swimming-return decision are corrected; duplicate player row
loops are eliminated. Source fall retains animation, animation obtains the
current offset before timer update, final ASL carry is retained, and shrink
adds ten in byte width. Attribute bases and facing-adjusted foot addressing
remain the accepted S14 repair. No platform/audio/focus behavior changes.

### Current original/native proof matrix

| Mode / original entry | Roots per width | Actual selected child returns | Contract |
| --- | ---: | ---: | --- |
| 16 / EEE9 | 1024 | 4096 DrawOneSpriteRow | Sizes, actions, animation, death/change-size and swimming; full/independent row input and returned indices/RAM. |
| 17 / EFA4 | 32 | 128 DrawOneSpriteRow | Six descending source-data reads into scratch, fixed shared loop and final attribute transfer. |
| 18 / EEE9 | 256 | 0 selected | All byte OAM offsets, three/four throwing redraw and final output. |
| 19 / EEE9 | 65536 | 122880 DumpTwoSpr | All256 byte OAM offsets x16 vertical masks x16 handler profiles; actual erase A/Y/scratch input and RTS continuation. |
| 20 / EEE9 | 8192 | 0 selected | All256 animation values x32 action/size/timer/frame profiles, grow/shrink completion and byte wrap; full output. |

All75040 roots match current x86/x64 across1841 RAM bytes, including OAM,
scratch and aliases0109-0139; true CPU stack is excluded. Selected127104
actual row/erase calls separately compare original inputs and returned RAM;
row X/Y values are asserted. Full mode executes the real native children.
Native API-unneeded temporary CPU registers/flags are explicitly excluded,
not silently called equivalent. Recorder table reads prove20/20 size-adder
and6/6 intermediate bytes, plus existing16/208/2 player graphics table reads.

The local ASM index is checked against the original ROM opcodes; scoped
addresses/instruction sizes have no discrepancy. Non-code segment/incbin
directives outside scope are explicit indexing exclusions. Per-instruction
actual PC transfers, branch taken/fall counts and selected actual return
continuations demonstrate every scoped label and listed relation. Every
conditional branch has both outcomes observed. Initial missing jump-crouch,
same-direction fast walk and A-only swimming alternatives were added before
credit. Source audit maps each native condition/read/write/call counterpart;
observed source execution alone is not the verdict.

## S1 individual node proof

| Node | Original address | Observations / indexed reads | Current counterpart and audited contract |
| --- | --- | ---: | --- |
| PlayerGfxHandler | eee9 | 75008 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Checks injury flashing before the graphics-mode dispatch, then routes ordinary, size-change, death and swimming paths in source order. |
| CntPl | eef3 | 70912 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Dispatches death and size-change before the swimming-state continuation; only nonzero swimming player state returns from ordinary drawing to the kick-tile path. |
| SwimKT | ef1f | 11392 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Chooses the applicable seventh/eighth foot sprite from facing, size and replacement-tile predicates before selecting a swim-kick tile. |
| BigKTS | ef2d | 11080 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Writes the selected SwimKickTileNum byte into the guarded foot sprite tile, then exits the graphics handler. |
| ExPGH | ef33 | 19072 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Returns from the graphics handler without further OAM modification on the source early-exit routes. |
| FindPlayerAction | ef34 | 51328 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Calls ProcessPlayerAction and tail-transfers the selected offset to PlayerGfxProcessing. |
| DoChangeSize | ef3a | 11584 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Calls HandleChangeSize and tail-transfers the selected offset to PlayerGfxProcessing. |
| PlayerKilled | ef40 | 8000 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Selects index 14 from PlayerGfxTblOffsets and falls through to common player graphics processing. |
| PlayerGfxProcessing | ef45 | 70912 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Stores PlayerGfxOffset, renders rows, applies player attributes, conditionally rerenders throw rows, then enters vertical offscreen masking. |
| SUpdR | ef76 | 8448 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Preserves the source three-versus-four throw-row count and calls RenderPlayerSub before the offscreen stage. |
| PlayerOffscreenChk | ef7a | 70912 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Moves the vertical offscreen nibble into scratch and initializes a bottom-to-top four-row OAM masking loop. |
| PROfsLoop | ef8c | 283648 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Tests one vertical-offscreen bit per iteration, conditionally dumps a pair offscreen, and advances upward through four rows. |
| NPROffscr | ef95 | 283648 | mysmb_oam_render_player and its player graphics selection/rendering helpers; Moves to the preceding row and loops until all four player OAM rows are processed. |
| IntermediatePlayerData | ef9e | 192 | mysmb_oam_draw_intermediate_player; Binds six ordered bytes for the fixed world/lives intermediate-player scratch setup. |
| DrawPlayer_Intermediate | efa4 | 32 | mysmb_oam_draw_intermediate_player; Copies IntermediatePlayerData into scratch in descending index order, draws the small-standing four-row player at OAM offset four, then sets the bottom-right horizontal flip bit from the subsequent empty sprite attributes. |
| PIntLoop | efa6 | 192 | mysmb_oam_draw_intermediate_player; Copies one descending IntermediatePlayerData byte to scratch $02 through $07 and loops until all six bytes are present before DrawPlayerLoop. |
| RenderPlayerSub | efbe | 79360 | mysmb_oam_player_render_rows publishes scratch then enters mysmb_oam_player_draw_loop; Publishes row count, relative coordinates, facing and attributes to source scratch, then initializes PlayerGfxOffset and Player_SprDataOffset for the shared player-row loop. |
| DrawPlayerLoop | efdc | 313344 | mysmb_oam_player_draw_loop shared by mysmb_oam_player_render_rows and mysmb_oam_draw_intermediate_player; Reads adjacent PlayerGraphicsTable tile bytes, draws one sprite row, decrements the requested row count and repeats until zero. |
| ProcessPlayerAction | efec | 51328 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Selects the graphics-action family by Player_State before testing swimming, crouching and ground movement. |
| ProcOnGroundActs | f00b | 20224 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Selects crouch, stand, walk/run or skid using crouching, horizontal input/speed, absolute speed and moving/facing-direction relation. |
| NonAnimatedActs | f028 | 23696 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Applies the size action offset, clears PlayerAnimCtrl and returns the selected PlayerGfxTblOffsets entry. |
| ActionFalling | f034 | 3584 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Selects walk/run action with size adjustment and obtains the retained current animation offset without advancing it. |
| ActionWalkRun | f03c | 6896 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Selects walk/run action with size adjustment and enters the four-frame animation path. |
| ActionClimbing | f044 | 6784 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Selects climbing action; zero vertical speed is non-animated while nonzero speed enters the three-frame animation path. |
| ActionSwimming | f050 | 13952 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Selects swimming action and advances animation only when jump/swim timer, animation control or A-button predicate requires it. |
| GetCurrentAnimOffset | f062 | 27632 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Reads PlayerAnimCtrl and tail-transfers to the table-offset calculation. |
| FourFrameExtent | f068 | 17264 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Sets an exclusive three-frame upper bound before common animation processing. |
| ThreeFrameExtent | f06d | 3200 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Sets an exclusive two-frame upper bound before common animation processing. |
| AnimationControl | f06f | 20464 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Obtains the current tile-table offset first, then only on expired timer reloads the timer and advances/wraps PlayerAnimCtrl. |
| SetAnimC | f08c | 4352 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Stores the bounded next PlayerAnimCtrl before restoring the already-selected graphics offset. |
| ExAnimC | f08f | 20464 | mysmb_oam_process_player_action with mysmb_oam_get_gfx_offset_adder and mysmb_oam_get_offset_from_anim_ctrl; Returns the selected graphics offset without changing it after timer/animation handling. |
| GetGfxOffsetAdder | f091 | 51328 | mysmb_oam_handle_change_size and graphics-offset helpers; Leaves a big-player action index unchanged and adds eight for a small player before table lookup. |
| SzOfs | f09b | 51328 | mysmb_oam_handle_change_size and graphics-offset helpers; Returns the size-adjusted action index to the requesting action path. |
| ChangeSizeOffsetAdder | f09c | 8570 | mysmb_oam_handle_change_size and graphics-offset helpers; Binds twenty ordered grow/shrink animation offset-adder bytes. |
| HandleChangeSize | f0b0 | 11584 | mysmb_oam_handle_change_size and graphics-offset helpers; Advances PlayerAnimCtrl only each fourth frame, clears the size-change flag on the ten-frame wrap, then dispatches grow versus shrink selection. |
| CSzNext | f0c3 | 6160 | mysmb_oam_handle_change_size and graphics-offset helpers; Stores the valid next size-change animation frame before common grow/shrink logic. |
| GorSLog | f0c6 | 11584 | mysmb_oam_handle_change_size and graphics-offset helpers; Selects big-player grow offset calculation or transfers to small-player shrink calculation based on PlayerSize. |
| GetOffsetFromAnimCtrl | f0d0 | 33428 | mysmb_oam_handle_change_size and graphics-offset helpers; Converts the animation selector to an eight-byte graphics-table displacement and adds the selected PlayerGfxTblOffsets base. |
| ShrinkPlayer | f0d7 | 5788 | mysmb_oam_handle_change_size and graphics-offset helpers; Offsets the animation selector by ten, uses ChangeSizeOffsetAdder and selects the applicable big/small swimming graphics base. |
| ShrPlF | f0e5 | 5788 | mysmb_oam_handle_change_size and graphics-offset helpers; Returns the selected shrink graphics-table base after the zero/nonzero offset-adder choice. |
| ChkForPlayerAttrib | f0e9 | 70912 | mysmb_oam_check_player_attributes; Selects the third-row and/or fourth-row OAM flip corrections from GameEngineSubroutine and PlayerGfxOffset values. |
| KilledAtt | f105 | 12062 | mysmb_oam_check_player_attributes; Clears flip bits in third-row first tile and sets horizontal flip in the paired tile before fourth-row handling. |
| C_S_IGAtt | f117 | 23199 | mysmb_oam_check_player_attributes; Clears flip bits in fourth-row first tile and sets horizontal flip in the paired tile. |
| ExPlyrAt | f129 | 70912 | mysmb_oam_check_player_attributes; Returns after the applicable player OAM attribute corrections. |

## S1 individual control proof

| Control | Original relation | Instruction PC | Actual transfers/returns |
| --- | --- | --- | ---: |
| control-03027 | PlayerGfxHandler -> CntPl (branch) | eeec | 66816 |
| control-03028 | PlayerGfxHandler -> ExPGH (branch) | eef1 | 4096 |
| control-03029 | PlayerGfxHandler -> CntPl (fallthrough) | eef1 | 4096 |
| control-03030 | CntPl -> PlayerKilled (branch) | eef7 | 8000 |
| control-03031 | CntPl -> DoChangeSize (branch) | eefc | 11584 |
| control-03032 | CntPl -> FindPlayerAction (branch) | ef01 | 32256 |
| control-03033 | CntPl -> FindPlayerAction (branch) | ef07 | 4096 |
| control-03034 | CntPl -> FindPlayerAction (call) | ef09 | 14976 |
| control-03035 | CntPl -> ExPGH (branch) | ef10 | 3584 |
| control-03036 | CntPl -> SwimKT (branch) | ef19 | 5696 |
| control-03037 | CntPl -> SwimKT (fallthrough) | ef1e | 5696 |
| control-03038 | SwimKT -> BigKTS (branch) | ef22 | 5696 |
| control-03039 | SwimKT -> ExPGH (branch) | ef2a | 312 |
| control-03040 | SwimKT -> BigKTS (fallthrough) | ef2c | 5384 |
| control-03041 | BigKTS -> ExPGH (fallthrough) | ef30 | 11080 |
| control-03042 | FindPlayerAction -> ProcessPlayerAction (call) | ef34 | 51328 |
| control-03043 | FindPlayerAction -> PlayerGfxProcessing (jump) | ef37 | 51328 |
| control-03044 | DoChangeSize -> HandleChangeSize (call) | ef3a | 11584 |
| control-03045 | DoChangeSize -> PlayerGfxProcessing (jump) | ef3d | 11584 |
| control-03046 | PlayerKilled -> PlayerGfxProcessing (fallthrough) | ef42 | 8000 |
| control-03047 | PlayerGfxProcessing -> RenderPlayerSub (call) | ef4a | 70912 |
| control-03048 | PlayerGfxProcessing -> ChkForPlayerAttrib (call) | ef4d | 70912 |
| control-03049 | PlayerGfxProcessing -> PlayerOffscreenChk (branch) | ef53 | 58368 |
| control-03050 | PlayerGfxProcessing -> PlayerOffscreenChk (branch) | ef60 | 4096 |
| control-03051 | PlayerGfxProcessing -> SUpdR (branch) | ef73 | 4224 |
| control-03052 | PlayerGfxProcessing -> SUpdR (fallthrough) | ef75 | 4224 |
| control-03053 | SUpdR -> RenderPlayerSub (call) | ef77 | 8448 |
| control-03054 | SUpdR -> PlayerOffscreenChk (fallthrough) | ef77 | 8448 |
| control-03055 | PlayerOffscreenChk -> PROfsLoop (fallthrough) | ef8b | 70912 |
| control-03056 | PROfsLoop -> NPROffscr (branch) | ef90 | 160768 |
| control-03057 | PROfsLoop -> DumpTwoSpr (call) | ef92 | 122880 |
| control-03058 | PROfsLoop -> NPROffscr (fallthrough) | ef92 | 122880 |
| control-03059 | NPROffscr -> PROfsLoop (branch) | ef9b | 212736 |
| control-03060 | DrawPlayer_Intermediate -> PIntLoop (fallthrough) | efa4 | 32 |
| control-03061 | PIntLoop -> PIntLoop (branch) | efac | 160 |
| control-03062 | PIntLoop -> DrawPlayerLoop (call) | efb2 | 32 |
| control-03063 | RenderPlayerSub -> DrawPlayerLoop (fallthrough) | efd9 | 79360 |
| control-03064 | DrawPlayerLoop -> DrawOneSpriteRow (call) | efe4 | 313344 |
| control-03065 | DrawPlayerLoop -> DrawPlayerLoop (branch) | efe9 | 233952 |
| control-03066 | ProcessPlayerAction -> ActionClimbing (branch) | eff0 | 6784 |
| control-03067 | ProcessPlayerAction -> ActionFalling (branch) | eff4 | 3584 |
| control-03068 | ProcessPlayerAction -> ProcOnGroundActs (branch) | eff8 | 20224 |
| control-03069 | ProcessPlayerAction -> ActionSwimming (branch) | effd | 13952 |
| control-03070 | ProcessPlayerAction -> NonAnimatedActs (branch) | f004 | 3584 |
| control-03071 | ProcessPlayerAction -> NonAnimatedActs (jump) | f008 | 3200 |
| control-03072 | ProcOnGroundActs -> NonAnimatedActs (branch) | f010 | 3712 |
| control-03073 | ProcOnGroundActs -> NonAnimatedActs (branch) | f018 | 6912 |
| control-03074 | ProcOnGroundActs -> ActionWalkRun (branch) | f01f | 3312 |
| control-03075 | ProcOnGroundActs -> ActionWalkRun (branch) | f025 | 3584 |
| control-03076 | ProcOnGroundActs -> NonAnimatedActs (fallthrough) | f027 | 2704 |
| control-03077 | NonAnimatedActs -> GetGfxOffsetAdder (call) | f028 | 23696 |
| control-03078 | ActionFalling -> GetGfxOffsetAdder (call) | f036 | 3584 |
| control-03079 | ActionFalling -> GetCurrentAnimOffset (jump) | f039 | 3584 |
| control-03080 | ActionWalkRun -> GetGfxOffsetAdder (call) | f03e | 6896 |
| control-03081 | ActionWalkRun -> FourFrameExtent (jump) | f041 | 6896 |
| control-03082 | ActionClimbing -> NonAnimatedActs (branch) | f048 | 3584 |
| control-03083 | ActionClimbing -> GetGfxOffsetAdder (call) | f04a | 3200 |
| control-03084 | ActionClimbing -> ThreeFrameExtent (jump) | f04d | 3200 |
| control-03085 | ActionSwimming -> GetGfxOffsetAdder (call) | f052 | 13952 |
| control-03086 | ActionSwimming -> FourFrameExtent (branch) | f05b | 6784 |
| control-03087 | ActionSwimming -> FourFrameExtent (branch) | f060 | 3584 |
| control-03088 | ActionSwimming -> GetCurrentAnimOffset (fallthrough) | f060 | 3584 |
| control-03089 | GetCurrentAnimOffset -> GetOffsetFromAnimCtrl (jump) | f065 | 27632 |
| control-03090 | FourFrameExtent -> AnimationControl (jump) | f06a | 17264 |
| control-03091 | ThreeFrameExtent -> AnimationControl (fallthrough) | f06d | 3200 |
| control-03092 | AnimationControl -> GetCurrentAnimOffset (call) | f071 | 20464 |
| control-03093 | AnimationControl -> ExAnimC (branch) | f078 | 16112 |
| control-03094 | AnimationControl -> SetAnimC (branch) | f088 | 3592 |
| control-03095 | AnimationControl -> SetAnimC (fallthrough) | f08a | 760 |
| control-03096 | SetAnimC -> ExAnimC (fallthrough) | f08c | 4352 |
| control-03097 | GetGfxOffsetAdder -> SzOfs (branch) | f094 | 25664 |
| control-03098 | GetGfxOffsetAdder -> SzOfs (fallthrough) | f09a | 25664 |
| control-03099 | HandleChangeSize -> GorSLog (branch) | f0b7 | 5424 |
| control-03100 | HandleChangeSize -> CSzNext (branch) | f0bc | 1221 |
| control-03101 | HandleChangeSize -> CSzNext (fallthrough) | f0c0 | 4939 |
| control-03102 | CSzNext -> GorSLog (fallthrough) | f0c3 | 6160 |
| control-03103 | GorSLog -> ShrinkPlayer (branch) | f0c9 | 5788 |
| control-03104 | GorSLog -> GetOffsetFromAnimCtrl (fallthrough) | f0ce | 5796 |
| control-03105 | ShrinkPlayer -> ShrPlF (branch) | f0e1 | 4663 |
| control-03106 | ShrinkPlayer -> ShrPlF (fallthrough) | f0e3 | 1125 |
| control-03107 | ChkForPlayerAttrib -> KilledAtt (branch) | f0f0 | 8000 |
| control-03108 | ChkForPlayerAttrib -> C_S_IGAtt (branch) | f0f7 | 3654 |
| control-03109 | ChkForPlayerAttrib -> C_S_IGAtt (branch) | f0fb | 6649 |
| control-03110 | ChkForPlayerAttrib -> C_S_IGAtt (branch) | f0ff | 834 |
| control-03111 | ChkForPlayerAttrib -> ExPlyrAt (branch) | f103 | 47713 |
| control-03112 | ChkForPlayerAttrib -> KilledAtt (fallthrough) | f103 | 4062 |
| control-03113 | KilledAtt -> C_S_IGAtt (fallthrough) | f114 | 12062 |
| control-03114 | C_S_IGAtt -> ExPlyrAt (fallthrough) | f126 | 23199 |
| control-04033 | FindPlayerAction -> CntPl (return) | ef09 | 14976 |
| control-04034 | ProcessPlayerAction -> FindPlayerAction (return) | ef34 | 51328 |
| control-04035 | HandleChangeSize -> DoChangeSize (return) | ef3a | 11584 |
| control-04036 | RenderPlayerSub -> PlayerGfxProcessing (return) | ef4a | 70912 |
| control-04037 | ChkForPlayerAttrib -> PlayerGfxProcessing (return) | ef4d | 70912 |
| control-04038 | RenderPlayerSub -> SUpdR (return) | ef77 | 8448 |
| control-04039 | DumpTwoSpr -> PROfsLoop (return) | ef92 | 122880 |
| control-04040 | DrawPlayerLoop -> PIntLoop (return) | efb2 | 32 |
| control-04041 | DrawOneSpriteRow -> DrawPlayerLoop (return) | efe4 | 4224 |
| control-04042 | GetGfxOffsetAdder -> NonAnimatedActs (return) | f028 | 23696 |
| control-04043 | GetGfxOffsetAdder -> ActionFalling (return) | f036 | 3584 |
| control-04044 | GetGfxOffsetAdder -> ActionWalkRun (return) | f03e | 6896 |
| control-04045 | GetGfxOffsetAdder -> ActionClimbing (return) | f04a | 3200 |
| control-04046 | GetGfxOffsetAdder -> ActionSwimming (return) | f052 | 13952 |
| control-04047 | GetCurrentAnimOffset -> AnimationControl (return) | f071 | 20464 |

### Operational proof and three artifacts

Current C90 x86/x64 products and affected game/test targets build. Each width
passes12/12 focused CTests: player OAM/route, core/bounding/geometry/block
regressions, platform purity, audio/focus/death-audio and product self-test.
Original OpenNT DOS16 links the same shared source, exit0 with existing
OLDNAMES.LIB warning; no DOS graphical/performance qualification claimed.
No platform business logic added. All three owner-authorized EXEs refreshed,
including the existing audio/title/focus pause; artifact authorization
overrides the default local-output exclusion.

- mysmb16.exe: 260823 bytes; SHA-256 ab215c6a6c16aa4a6eea989ba914f831a746ba022645aa64c91cad71e89b6643.
- mysmb32.exe: 373854 bytes; SHA-256 91f320ca561efd0587ae620794b2a1fd9305294a9910d7b5c05cda8540105989.
- mysmb64.exe: 380886 bytes; SHA-256 5b5426001f050901435ccad839456943915c732d563a54de59ea99f956ee06f4.

Raw snapshots and diagnostic probe binaries removed from ignored admitted
output directory; neutral summaries/logs remain. Chunk cap2048/58851344
bytes,192MiB aggregate,120seconds/run and524288steps/case observed. No ROM,
raw fixture or reference-emulator runtime enters tracked product source.
Ledger admission/closure, registry, documentation and whitespace gates pass.
S1 closes; T66/M2 stay open pending remaining nodes and complete certification.

## S2 admission - shared relative coordinate entries and paired block return

Unchanged scope9/intended fresh9, all incoming needs-evidence: RelativePlayerPosition; RelativeBubblePosition; RelativeFireballPosition; RelWOfs; RelativeMiscPosition; RelativeEnemyPosition; RelativeBlockPosition; VariableObjOfsRelPos; GetObjRelativePosition.
Current1677/1992 nodes,3588/4317 feasible controls(raw4342,infeasible25),
396/492 material partial. Maximum1686/1992 nodes; historical1992 baseline/
maximum, expectedMatches empty and maintenance custody unchanged. All18
owned controls in S2's plan row are pending; no material row promotions.

Shared object_position.c wrappers enter one GetObjRelativePosition helper,
store source Y first, then byte X-ScreenLeftX to fixed family destinations.
Proper source offsets are existing dependencies without S3 table/node credit.
RelativeBlockPosition first calls VariableObjOfsRelPos; that routine restores
X from ObjectOffset before the second block's INX/INX. Audit must distinguish
the incoming slot argument from that RAM-restored offset, not assume equality.
Current C uses incoming slot+2 for the second phase; compare controlled valid
slot combinations independently before deciding whether repair is required.

Original six family entries cover all256 world-X x256 left-X byte pairs,
all valid family slots, all Y bytes and selected independent ObjectOffset
values; page/high state varies and must remain untouched because this routine
reads low coordinates only. Full current native output compares1841 bytes,
including scratch/OAM/aliases0109-0139; true CPU stack excluded. Source PC
visits, actual transfers/RTS continuations and per-node native source mappings
prove the listed graph relations. CPU registers unused by the native API are
excluded; the block's consumed first-return X is a required semantic input,
not an exclusion. Full output executes real shared helpers without mocks.

Owner ROM/local reviewed ASM are nonredistributable research inputs. Ignored
build/m2-t66-s2 contains all raw/log/script artifacts,192MiB raw aggregate,
2048 roots/chunk,120seconds/run,524288steps/case and coordinator cleanup.
Separate focused native tests/builds/purity and original OpenNT DOS16 link;
product corrections refresh three owner-authorized EXEs. Sweep covers all
relative wrappers, source-index restoration, byte addition and Y-before-X
store order. No S3/later credit or platform/audio changes. No closure while
any scoped semantic difference or unproved claimed relation remains.

## S2 P2 relative-coordinate source/return correction and closure

All9 intended labels become current exact, no deferred/transferred names:
RelativePlayerPosition; RelativeBubblePosition; RelativeFireballPosition;
RelWOfs; RelativeMiscPosition; RelativeEnemyPosition; RelativeBlockPosition;
VariableObjOfsRelPos; GetObjRelativePosition. All18 listed control relations
close exact. Nodes1677 ->1686/1992, controls3588 ->3606/4317(raw4342,
infeasible25 unchanged). Historical mapping1992/1992 remains separate,
historical expected/actualMatches empty. S3 next unadmitted; T66 remains open
with30 pending planned nodes. No later table/offscreen node credit.

### Original source finding, repair and similar-issue sweep

Original RelativeBlockPosition calls VariableObjOfsRelPos once. After the
coordinate stores, that routine loads X from ObjectOffset and returns. The
caller increments this restored X twice, then enters the second coordinate
phase. Native had used the incoming slot+2 instead. When the valid input slot
and valid ObjectOffset differ, the second relative X/Y and scratch use the
wrong actor index. A2048-root original pre-repair block batch has3068 RAM-byte
differences. The shared C second call now reads ObjectOffset+2 in byte width.
No claimed ordinary-game failure follows merely from the controlled divergent
slot case; the correction restores the actual ROM data/control dependency.

Sweep: all six relative wrappers use the same GetObjRelativePosition stores;
only RelativeBlockPosition consumes its first child-return index in a second
coordinate phase. Enemy/misc/fireball/bubble inputs use their original
displacements and fixed output cells. Player resets source/destination0.
VariableObjOfsRelPos retains incoming scratch before byte addition. Relative
Y store precedes relative X subtraction. Page/high coordinates are not used
or modified. Every relative call site is inspected; only the paired block
consumer required code repair. Later offscreen routines remain unchanged.

### Newly enumerated in-scope material dependency

Coordinator accepts material-t66-block-return-slot within the already admitted
two-node chain: VariableObjOfsRelPos -> RelativeBlockPosition, RAM ObjectOffset
to returned X to second coordinate index/scratch. Source path above and native
read after first call prove feasibility; this is a consumed state dependency,
not a writer-reader cartesian candidate. Block65536 roots include32768 cases
with independent valid incoming/ObjectOffset values. Final relative cells and
scratch independently expose wrong substitution. The node/control scope did
not grow. Material396/492 ->397/493, enumeration remains partial. Existing
pending material00432 proper-offset table retains S3 ownership/no credit.

### Current original/native route matrix

| Mode / original entry | Root family | Roots per width | Contract |
| --- | --- | ---: | --- |
| 21 / F12A | Player | 65536 | Source/destination zero, Y then byte X-left subtraction. |
| 22 / F131 | Bubble | 65536 | Proper source slot+22, fixed output3. |
| 23 / F13B | Fireball | 65536 | Proper source slot+7, fixed output2 and RelWOfs continuation. |
| 24 / F148 | Misc | 65536 | Proper source slot+13, fixed output6. |
| 25 / F152 | Enemy | 65536 | Incoming slot scratch, byte slot+1, fixed output1. |
| 26 / F159 | Paired block | 65536 | First slot+9 at output4, restored ObjectOffset+2+9 at output5. |

Each family spans all256 world-X x256 left-X pairs; valid slots are distributed
across that matrix, not claimed as a full extra Cartesian dimension. All Y
bytes and wrapped subtraction results occur; page/high state varies and
must remain untouched. Original controlled records compare1841 RAM bytes,
including all scratch/OAM/aliases0109-0139; only true CPU stack excluded.
Every393216 root matches real current x86/x64 shared C, zero differences.
No child mocking or substituted child output is used in these full routes.
Native-API unused CPU registers/flags are explicit exclusions. Original X
restoration consumed by the paired block is mandatory and preserved through
the RAM read, not excluded. Source index/table constants are checked locally
against original owner PRG; bytes are not imported into new tracked fixtures.

Local ASM index agrees with original opcode/instruction sizes; non-code
segment/incbin directives outside scope remain explicit indexing exclusions.
Actual source PC transfers/RTS continuations cover every9 labels and18
relations. Static native source audit maps wrapper selection, helper calls,
destination, scratch and consumed continuation individually. No source-only
visit count is substituted for native equivalence or unobserved node credit.

## S2 individual node and edge proof

| Node | Original address | Visits | Current counterpart and audited contract |
| --- | --- | ---: | --- |
| RelativePlayerPosition | f12a | 65536 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Initializes source and relative-result offsets to zero, then tail-transfers to the common relative-coordinate routine. |
| RelativeBubblePosition | f131 | 65536 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Uses ObjOffsetData bubble displacement and writes the selected SprObject coordinates into the bubble relative-result cells. |
| RelativeFireballPosition | f13b | 65536 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Uses ObjOffsetData fireball displacement and writes the selected SprObject coordinates into the fireball relative-result cells. |
| RelWOfs | f142 | 262144 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Calls the common coordinate calculation and restores ObjectOffset for its caller. |
| RelativeMiscPosition | f148 | 65536 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Uses ObjOffsetData misc displacement and writes the selected SprObject coordinates into the misc relative-result cells. |
| RelativeEnemyPosition | f152 | 65536 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Adds the enemy-array displacement and writes selected object coordinates into enemy relative-result cells. |
| RelativeBlockPosition | f159 | 65536 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Performs two relative-coordinate calculations for the selected block object and its paired object at source slot plus two. |
| VariableObjOfsRelPos | f165 | 196608 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Preserves ObjectOffset in scratch, adds the supplied array displacement, calls the common coordinate routine and restores ObjectOffset. |
| GetObjRelativePosition | f171 | 458752 | relative-position wrappers with mysmb_oam_get_obj_relative_position and mysmb_oam_variable_obj_relative_position; Copies source Y to destination relative Y and stores source X minus ScreenLeft_X_Pos as destination relative X. |

| Control | Original relation | Instruction PC | Actual transfers/returns |
| --- | --- | --- | ---: |
| control-03115 | RelativePlayerPosition -> RelWOfs (jump) | f12e | 65536 |
| control-03116 | RelativeBubblePosition -> GetProperObjOffset (call) | f133 | 65536 |
| control-03117 | RelativeBubblePosition -> RelWOfs (jump) | f138 | 65536 |
| control-03118 | RelativeFireballPosition -> GetProperObjOffset (call) | f13d | 65536 |
| control-03119 | RelativeFireballPosition -> RelWOfs (fallthrough) | f140 | 65536 |
| control-03120 | RelWOfs -> GetObjRelativePosition (call) | f142 | 262144 |
| control-03121 | RelativeMiscPosition -> GetProperObjOffset (call) | f14a | 65536 |
| control-03122 | RelativeMiscPosition -> RelWOfs (jump) | f14f | 65536 |
| control-03123 | RelativeEnemyPosition -> VariableObjOfsRelPos (jump) | f156 | 65536 |
| control-03124 | RelativeBlockPosition -> VariableObjOfsRelPos (call) | f15d | 65536 |
| control-03125 | RelativeBlockPosition -> VariableObjOfsRelPos (fallthrough) | f164 | 65536 |
| control-03126 | VariableObjOfsRelPos -> GetObjRelativePosition (call) | f16b | 196608 |
| control-04048 | GetProperObjOffset -> RelativeBubblePosition (return) | f133 | 65536 |
| control-04049 | GetProperObjOffset -> RelativeFireballPosition (return) | f13d | 65536 |
| control-04050 | GetObjRelativePosition -> RelWOfs (return) | f142 | 262144 |
| control-04051 | GetProperObjOffset -> RelativeMiscPosition (return) | f14a | 65536 |
| control-04052 | VariableObjOfsRelPos -> RelativeBlockPosition (return) | f15d | 65536 |
| control-04053 | GetObjRelativePosition -> VariableObjOfsRelPos (return) | f16b | 196608 |

### Operational proof and delivery

Current C90 x86/x64 product and affected core/player/checker targets build;
12/12 focused tests pass per width, including platform purity, core, player
OAM/route, audio/focus, death audio and product self-test. Original OpenNT
DOS16 links the same shared sources, exit0 with existing OLDNAMES.LIB warning.
No DOS graphical/performance qualification is claimed. All three products
refresh for the code correction; existing audio/title/focus pause retained
under the owner's explicit artifact delivery override.

- mysmb16.exe: 260839 bytes; SHA-256 1f99e8e864fcd5da449f3a643eab4f82e550b5b2229e71e167dd77ac96025fa0.
- mysmb32.exe: 373854 bytes; SHA-256 efb2534dc2bb7074afb4c79db301431ef47beb18d09cd99c7f73a3ee631bed8b.
- mysmb64.exe: 380886 bytes; SHA-256 87c198fc900fe0a4b744dd70459117c19d711ecf67957ebf7894374c6f0fdc84.

All raw snapshots/probe binaries cleaned from ignored admitted output path;
neutral logs/summaries remain. Max2048 roots/58851344 bytes per chunk,
192MiB aggregate,120seconds/run and524288steps/case observed. No ROM/raw
fixture/reference-emulator runtime added to production. Ledger, node
admission/closure, registry, documentation and whitespace gates pass.
S2 closes, T66/M2 remain open pending remaining proof and final certification.

## S3 admission - object offscreen entries and mask composition

Scope11/intended fresh11, all incoming needs-evidence: GetPlayerOffscreenBits; GetFireballOffscreenBits; GetBubbleOffscreenBits; GetMiscOffscreenBits; ObjOffsetData; GetProperObjOffset; GetEnemyOffscreenBits; GetBlockOffscreenBits; SetOffscrBitsOffset; GetOffScreenBitsSet; RunOffscrBitsSubs.
Current1686/1992 nodes,3606/4317 feasible controls(raw4342,infeasible25),
397/493 material partial. Maximum1697/1992 nodes and3624/4317 controls;
material00432 pending, maximum398/493. Historical1992/1992, expectedMatches
empty; audit participation leaves maintenance custody unchanged.

Entry six family roots F180/F187/F191/F19B/F1AF/F1B6; exit shared mask store.
Player wrapper lives in player_gfx.c; other wrappers/composition/table belong
to object_position.c. S2 is closed. Real GetX/GetYOffscreenBits are dependency
execution only, with independent arithmetic/table certification reserved for
S4/S5. No production test hook or mock replaces either dependency.

Static audit checks byte source displacement, fixed destination, incoming
slot scratch, X-before-Y calls, four right/left shifts, OR/store order and
the caller-consumed result. Original source transfers/RTS continuations and
all three existing offset-table reads are observed. Native counterparts are
audited individually; actual original visits alone never certify C edges.
Unused CPU A/X/Y and true CPU stack0100-0108/013A-01FF are explicit ABI
exclusions. Native full output compares1841 RAM bytes including0109-0139.

Six families each run65536 controlled byte X/Y pairs with valid family slots,
independent valid ObjectOffset, selected page/high and screen-edge states.
These varied dimensions are not a full Cartesian proof; static semantics
and actual transfer evidence form the separate equivalence track. Focused
native offscreen/player/core tests and purity form the operational track;
original DOS16 toolchain is retained. Only product-code changes refresh all
three owner-authorized EXEs; otherwise S2 products remain current.

Owner-local ROM/reviewed ASM are nonredistributable inputs. All scripts/raw
and logs stay below ignored build/m2-t66-s3,192MiB aggregate raw budget,
2048 roots/chunk,120seconds/run,524288steps/case; coordinator deletes raw
after comparison. Sweep all six wrappers and composition. No successor
admission with scoped diff/unproved edge; repair and re-audit within S3.

## S3 P2 offscreen composition audit and closure

All11 intended labels and18 controls close exact, no deferred/transferred
names. Nodes1686 ->1697/1992; controls3606 ->3624/4317(raw4342,
infeasible25); material00432 closes,397 ->398/493 enumeration partial.
Historical1992/1992 expected/actualMatches remain empty and separate.
T66 remains open with19 pending nodes; S4 next unadmitted.

### Static per-node and integration conclusions

No scoped production discrepancy found. Player source/destination0 is set
by its player_gfx.c wrapper. Fireball/bubble/misc use existing proper-offset
helper with selector0/1/2 and fixed destination2/3/6. Enemy/block preserve
incoming slot in scratch00, add displacement1/9 in byte width and select
fixed destination1/4. GetProperObjOffset uses cleared carry byte addition;
existing offset table matches original local PRG and every entry is read.
GetOffScreenBitsSet saves destination across its real child calls, shifts
Y result four times, ORs saved X nibble, writes00 then fixed offscreen cell.
RunOffscrBitsSubs calls real X helper, shifts its result right four times,
writes00 and tail-enters real Y helper; the Y return resumes the composition
caller. Native functions preserve that data/control sequence via shared C
calls and return values. X/Y arithmetic/table nodes stay S4/S5 dependencies,
without fresh credit. There is no platform branch or host API in this path.

Similar-issue sweep covers all six wrappers, both slot-plus-displacement
routes, shared nibble composition and proper-offset helper relative users.
No correction required in that scope; original CPU restored ObjectOffset
is unused by these void native roots and excluded as a register, not RAM.
Destination save on CPU stack is represented by an immutable native value;
all game RAM/scratch remains compared. Source visits alone do not establish
native equivalence: each current counterpart/contract below was inspected.

### Controlled original/native route and table evidence

Modes27-32 enter original F180/F187/F191/F19B/F1AF/F1B6,65536 roots each.
Each family covers all byte X/Y pairs, distributed valid slots, independently
valid ObjectOffset and selected page/high/screen-edge states. These latter
dimensions are not claimed as exhaustive extra Cartesian combinations.
All393216 roots match real x86/x64 shared C across1841 RAM bytes, including
scratch/OAM/aliases0109-0139; true CPU stack0100-0108/013A-01FF and unused
CPU A/X/Y/flags excluded. No mock or substitute helper output is used.
Proper-offset indexed reads0/1/2 each occur65536 times; original ROM binding
checks existing constants without importing protected bytes or raw fixtures.
Material00432 shares that helper with S2's already accepted relative roots.
Actual original PC transfers/RTS continuations observe every listed control
relation. Source opcode/index agrees locally; non-code directives outside
the admitted range remain indexing exclusions. Helper dependency execution
does not certify later nodes. No end-to-end game/DOS performance claim.

| Node | Original address | Visits or table reads | Current counterpart / semantic audit |
| --- | --- | ---: | --- |
| GetPlayerOffscreenBits | f180 | 65536 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Selects player SprObject source and player offscreen destination offsets before common offscreen-bit calculation. |
| GetFireballOffscreenBits | f187 | 65536 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Applies fireball ObjOffsetData displacement then selects the fixed fireball offscreen destination before common calculation. |
| GetBubbleOffscreenBits | f191 | 65536 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Applies bubble ObjOffsetData displacement then selects the bubble offscreen destination before common calculation. |
| GetMiscOffscreenBits | f19b | 65536 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Applies misc ObjOffsetData displacement then selects the misc offscreen destination before common calculation. |
| ObjOffsetData | f1a5 | 196608 | mysmb_obj_offset_data and mysmb_oam_proper_source_offset; Binds ordered fireball, bubble and misc SprObject array displacements used by both relative-position and offscreen wrappers. |
| GetProperObjOffset | f1a8 | 196608 | mysmb_obj_offset_data and mysmb_oam_proper_source_offset; Adds the selected ObjOffsetData displacement to the input object slot. |
| GetEnemyOffscreenBits | f1af | 65536 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Selects enemy array displacement and enemy offscreen destination before common calculation. |
| GetBlockOffscreenBits | f1b6 | 65536 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Selects block array displacement and block offscreen destination before common calculation. |
| SetOffscrBitsOffset | f1ba | 131072 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Preserves ObjectOffset in scratch, adds the supplied array displacement, and enters common offscreen-bit calculation. |
| GetOffScreenBitsSet | f1c0 | 393216 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Calls the X/Y offscreen chain, combines X low and Y high nibbles, stores the composite to the selected offscreen byte and restores ObjectOffset. |
| RunOffscrBitsSubs | f1d7 | 393216 | mysmb_oam_get_offscreen_bits_set and mysmb_oam_set_offscreen_bits_offset; Obtains X offscreen bits, shifts them into scratch low nibble, then tail-transfers to Y offscreen calculation. |

| Control | Original relation | Instruction PC | Actual transfers/returns |
| --- | --- | --- | ---: |
| control-03127 | GetPlayerOffscreenBits -> GetOffScreenBitsSet (jump) | f184 | 65536 |
| control-03128 | GetFireballOffscreenBits -> GetProperObjOffset (call) | f189 | 65536 |
| control-03129 | GetFireballOffscreenBits -> GetOffScreenBitsSet (jump) | f18e | 65536 |
| control-03130 | GetBubbleOffscreenBits -> GetProperObjOffset (call) | f193 | 65536 |
| control-03131 | GetBubbleOffscreenBits -> GetOffScreenBitsSet (jump) | f198 | 65536 |
| control-03132 | GetMiscOffscreenBits -> GetProperObjOffset (call) | f19d | 65536 |
| control-03133 | GetMiscOffscreenBits -> GetOffScreenBitsSet (jump) | f1a2 | 65536 |
| control-03134 | GetEnemyOffscreenBits -> SetOffscrBitsOffset (jump) | f1b3 | 65536 |
| control-03135 | GetBlockOffscreenBits -> SetOffscrBitsOffset (fallthrough) | f1b8 | 65536 |
| control-03136 | SetOffscrBitsOffset -> GetOffScreenBitsSet (fallthrough) | f1bf | 131072 |
| control-03137 | GetOffScreenBitsSet -> RunOffscrBitsSubs (call) | f1c2 | 393216 |
| control-03138 | RunOffscrBitsSubs -> GetXOffscreenBits (call) | f1d7 | 393216 |
| control-03139 | RunOffscrBitsSubs -> GetYOffscreenBits (jump) | f1e0 | 393216 |
| control-04054 | GetProperObjOffset -> GetFireballOffscreenBits (return) | f189 | 65536 |
| control-04055 | GetProperObjOffset -> GetBubbleOffscreenBits (return) | f193 | 65536 |
| control-04056 | GetProperObjOffset -> GetMiscOffscreenBits (return) | f19d | 65536 |
| control-04057 | RunOffscrBitsSubs -> GetOffScreenBitsSet (return) | f1c2 | 393216 |
| control-04058 | GetXOffscreenBits -> RunOffscrBitsSubs (return) | f1d7 | 393216 |

### Operational verification and retained delivery

Current checker builds x86/x64;14/14 focused tests each pass including
offscreen bounds/chain, player OAM/route/core, platform purity and Win32
audio/focus/self tests. Original OpenNT DOS16 shared-source link exit0,
existing OLDNAMES.LIB warning retained. No production source changed; all
three S2 P2 assets EXEs are byte-for-byte equal to committed HEAD and retained
under the owner's explicit delivery authorization. Audio/title/focus pause
remains included. Neutral harness extensions only, no product runtime probe.

Raw/probe artifacts cleaned from the ignored admitted path; neutral summaries
and logs retained. Limits192MiB aggregate/2048 roots per chunk/120seconds per
run/524288steps per case enforced. Ledger/admission/closure/current registry,
documentation and whitespace gates pass. S3 closes; T66/M2 remain open.

## S4 admission - horizontal offscreen partition loop

Scope6/intended fresh6, all incoming needs-evidence: XOffscreenBitsData; DefaultXOnscreenOfs; GetXOffscreenBits; XOfsLoop; XLdBData; ExXOfsBS.
Current1697/1992 nodes,3624/4317 feasible controls(raw4342,infeasible25),
398/493 material partial. Maximum1703/1992 nodes,3633/4317 controls,
400/493 material partial. Controls03140-03147 and04059 and material00433/
00434 are the exact receiving set. Historical1992/1992 expectedMatches
empty; audit participation preserves existing maintenance custody.

Entry GetXOffscreenBits F1F6 through ExXOfsBS; owner object_position.c.
S3 is closed. DividePDiff is executed as a real dependency, with own node
credit reserved for S5. Static audit checks saved source offset04, right
edge before left, byte subtraction borrow into page subtraction, signed
page partitions, default offsets, real division call/return, table index,
source reload, nonzero mask early exit and both loop continuations.

Controlled roots cover all256 object X x256 object pages with viewport
left0/right255/page0; additional wrapped scrolling viewport variants cover
carry changes. Returned A mask is consumed by native API and compared,
not excluded. All1841 RAM bytes compare including0109-0139; true CPU stack
and unused CPU X/Y/flags excluded. Source branch outcomes, actual transfers/
returns and indexed table reads accompany per-node native source inspection.
Calls' fall-through joins require actual child RTS continuation, not a
fictional direct JSR fall-through instruction. Existing constants are bound
locally to owner PRG; no protected data imported into new tracked fixtures.

Operational track: x86/x64 checker builds, focused offscreen/player/core/
purity/audio/focus/self tests, original OpenNT DOS16 shared-source link.
Products retained for audit/test-only work; refresh3 EXEs if code correction.
Sweep covers common horizontal implementation and every public caller.
No S5/later promotion or platform rewrite. Scoped diff must be repaired and
re-audited within S4 before successor admission.

Owner-local ROM/reviewed ASM nonredistributable research inputs. Raw/logs/
scripts stay below ignored build/m2-t66-s4;192MiB aggregate,2048 roots/chunk,
120seconds/run,524288steps/case; coordinator deletes raw/probe after proof.

## S4 P2 horizontal offscreen loop audit and closure

All6 intended labels/9 controls/material00433-00434 close exact, no deferred
or transferred labels. Nodes1697 ->1703/1992, controls3624 ->3633/4317
(raw4342,infeasible25), material398 ->400/493 partial. Historical1992/1992
expected/actualMatches empty remains separate. T66 has13 pending nodes;
S5 next unadmitted. No dependency node credit for DividePDiff.

### Source and native graph/semantics audit

GetXOffscreenBits saves the input source index to04 and initializes right
edge1. XOfsLoop subtracts pixel coordinate in byte width, writes07, and
subtracts its borrow with source page from edge page. C tests page difference
bit7 before selecting alternate defaults. For nonnegative page differences,
original CMP1/BPL selects alternate default for values1-127; zero alone
sets06 to the threshold and calls real DividePDiff. C's zero comparison is
equivalent after its preceding negative branch, including wrapped page bytes.
Defaults/table indices match the existing locally bound owner-ROM tables.
XLdBData reads the selected mask and restores source X from04. Nonzero
returns immediately; zero decrements edge and loops only while nonnegative.
Native returns bits on nonzero or edge0, otherwise continues once at edge0.
This preserves both zero-result exits and scratch effects; returned mask
is an explicit native result, not an excluded CPU register.

Call control03143 enters real DividePDiff; return04059 and fall-through
join03144 both require its observed RTS target at JSR+3. The call instruction
does not directly fall through while its child executes. Other branch/loop
and fall-through relations have actual immediate PC transfer evidence.
Four original conditional instructions have taken and fall-through outcomes.
Static counterparts are inspected individually below; no visit count alone
proves C equivalence. S3's full caller routes already prove real X integration;
this S proves the independent helper's mask and scratch contract.

Similar-issue sweep: all horizontal implementation/public call sites were
inspected. Shared RunOffscrBitsSubs passes the same source page/X, then shifts
returned mask; scroll passes player0 page/X; small-platform output passes
slot+1 with enemy page/X. All use this shared owner. No scoped discrepancy,
duplicate algorithm or platform business logic found. No production repair.

### Original route and comparison evidence

Modes33/34 each execute65536 roots, all256 object-X x256 object-page pairs.
Viewport33 uses left0/page0 and right255/page0. Viewport34 uses a nonzero
left position on page254, right=left-1 on page255. Valid source indices0-24
and independent ObjectOffset0-5 vary; these are not claimed as extra Cartesian
dimensions. Source offset04 and all scratch changes expose wrong source/
partition substitutions. Current real x86/x64 output matches131072 original
roots across1841 RAM bytes plus returned A mask, zero differences. True CPU
stack0100-0108/013A-01FF and unused CPU X/Y/flags excluded;0109-0139 compared.
No child mock, substitute division result or runtime emulator in product.

All16 X mask indices and3 default indices are observed. Existing C constants
are checked directly against local original PRG with no new raw data fixture.
Original opcode/index validation agrees; non-code directives outside scope
remain indexing exclusions. Raw records/probe cleaned; neutral summaries
retained under ignored admitted output path. Limits192MiB aggregate,
2048 roots/chunk,120seconds/run and524288steps/case enforced.

| Node | Original address | Entry visits or table reads | Current counterpart / contract |
| --- | --- | ---: | --- |
| XOffscreenBitsData | f1e3 | 196496 | mysmb_oam_get_x_offscreen_bits, mysmb_oam_get_y_offscreen_bits and mysmb_oam_divide_pixel_diff with owner-local constant tables; Binds sixteen ordered X-axis offscreen bit masks indexed by the resolved X boundary/partition offset. |
| DefaultXOnscreenOfs | f1f3 | 327058 | mysmb_oam_get_x_offscreen_bits, mysmb_oam_get_y_offscreen_bits and mysmb_oam_divide_pixel_diff with owner-local constant tables; Binds the three ordered default X partition offsets used by right/left boundary selection. |
| GetXOffscreenBits | f1f6 | 131072 | mysmb_oam_get_x_offscreen_bits, mysmb_oam_get_y_offscreen_bits and mysmb_oam_divide_pixel_diff with owner-local constant tables; Starts at the right boundary, computes page/pixel difference and selects an X offscreen mask, examining the left boundary only when the right result is zero. |
| XOfsLoop | f1fa | 196496 | mysmb_oam_get_x_offscreen_bits, mysmb_oam_get_y_offscreen_bits and mysmb_oam_divide_pixel_diff with owner-local constant tables; For one X screen edge, derives default or divided partition index from page difference, signed comparison and pixel difference. |
| XLdBData | f21e | 196496 | mysmb_oam_get_x_offscreen_bits, mysmb_oam_get_y_offscreen_bits and mysmb_oam_divide_pixel_diff with owner-local constant tables; Loads the selected X mask, restores source offset and either exits on nonzero bits or retries the remaining left edge. |
| ExXOfsBS | f22a | 131072 | mysmb_oam_get_x_offscreen_bits, mysmb_oam_get_y_offscreen_bits and mysmb_oam_divide_pixel_diff with owner-local constant tables; Returns the selected X offscreen mask. |

| Control | Original relation | Instruction PC | Actual transfers/returns |
| --- | --- | --- | ---: |
| control-03140 | GetXOffscreenBits -> XOfsLoop (fallthrough) | f1f8 | 131072 |
| control-03141 | XOfsLoop -> XLdBData (branch) | f20c | 65934 |
| control-03142 | XOfsLoop -> XLdBData (branch) | f213 | 129538 |
| control-03143 | XOfsLoop -> DividePDiff (call) | f21b | 1024 |
| control-03144 | XOfsLoop -> XLdBData (fallthrough) | f21b | 1024 |
| control-03145 | XLdBData -> ExXOfsBS (branch) | f225 | 130674 |
| control-03146 | XLdBData -> XOfsLoop (branch) | f228 | 65424 |
| control-03147 | XLdBData -> ExXOfsBS (fallthrough) | f228 | 398 |
| control-04059 | DividePDiff -> XOfsLoop (return) | f21b | 1024 |

| Table | Index | Actual indexed reads |
| --- | ---: | ---: |
| xmask | 0 | 16 |
| xmask | 1 | 16 |
| xmask | 2 | 16 |
| xmask | 3 | 16 |
| xmask | 4 | 16 |
| xmask | 5 | 16 |
| xmask | 6 | 16 |
| xmask | 7 | 65822 |
| xmask | 8 | 16 |
| xmask | 9 | 16 |
| xmask | 10 | 16 |
| xmask | 11 | 16 |
| xmask | 12 | 16 |
| xmask | 13 | 16 |
| xmask | 14 | 16 |
| xmask | 15 | 130450 |
| xdefault | 0 | 65424 |
| xdefault | 1 | 196098 |
| xdefault | 2 | 65536 |

### Operational proof and delivery

Current x86/x64 checker builds and14/14 focused tests each pass: offscreen
bounds/chain, player OAM/route/core, purity, audio/focus and product self-test.
Original OpenNT DOS16 shared-source link exit0 with existing OLDNAMES.LIB
warning; no DOS graphics/performance qualification. Product code unchanged,
three S2 P2 assets EXEs verified byte-for-byte against committed HEAD and
retained with audio/title/focus pause. Only neutral checker/probe extensions.
Ledger/admission/closure/registry/documentation/whitespace gates pass.
S4 closes, T66/M2 remain open pending later chains/final certification.
