# M2 T65: Cohort K block queries and object output proof

T65 follows closed T64 in the existing source-order proof program. The actual
registry Cohort K contains 154 labels at ASM lines 13023-14457: shared block
queries then object/OAM output and player graphics table bindings. The old
program's generic collision/player-terrain title is corrected to this exact
inventory; no node is reordered or moved between cohorts.

Incoming historical mapping 1992/1992, exact nodes 1480/1992, controls
3181/4323 (raw 4342, infeasible 19), material 368/487 with partial enumeration.
Scope 154 labels: DrawLargePlatform already exact; the other 153 need evidence.
Maximum task current-exact nodes 1633/1992. K has 310 pending and three exact
controls, and 21 pending material rows. Existing maintenance receivers retain
custody; the following S plan owns audit/repair participation, not silent transfers.

## Exact source-order S plan

| S | Chain and current shared owner | Nodes / intended fresh exact | Exact labels |
| --- | --- | ---: | --- |
| S1 | Shared block-buffer query entries, table bindings, coordinate/scratch return; src/game/world/block_buffer.c | 14 / 14 | BlockBufferChk_Enemy; ResidualMiscObjectCode; BlockBufferChk_FBall; ResJmpM; BBChk_E; BlockBufferAdderData; BlockBuffer_X_Adder; BlockBuffer_Y_Adder; BlockBufferColli_Feet; BlockBufferColli_Head; BlockBufferColli_Side; BlockBufferCollision; RetXC; RetYC |
| S2 | Vine drawing and six-sprite stack; src/game/oam/vine_gfx.c and sprite_stacker.c | 8 / 8 | VineYPosAdder; DrawVine; VineTL; SkpVTop; ChkFTop; NextVSp; SixSpriteStacker; StkLp |
| S3 | Hammer pose and two-sprite output; src/game/oam/hammer_gfx.c | 12 / 12 | FirstSprXPos; FirstSprYPos; SecondSprXPos; SecondSprYPos; FirstSprTilenum; SecondSprTilenum; HammerSprAttrib; DrawHammer; ForceHPose; GetHPose; RenderH; NoHOffscr |
| S4 | Flagpole score output and sprite dump leaves; src/game/oam/flagpole_gfx.c and sprite_dump.c | 9 / 9 | FlagpoleScoreNumTiles; FlagpoleGfxHandler; ChkFlagOffscreen; MoveSixSpritesOffscreen; DumpSixSpr; DumpFourSpr; DumpThreeSpr; DumpTwoSpr; ExitDumpSpr |
| S5 | Large platform tiles and offscreen columns; src/game/oam/small_platform_gfx.c | 11 / 10 | DrawLargePlatform; ShrinkPlatform; SetLast2Platform; SetPlatformTilenum; SChk2; SChk3; SChk4; SChk5; SChk6; SLChk; ExDLPl |
| S6 | Floating coin number and jumping coin output; src/game/objects.c | 5 / 5 | DrawFloateyNumber_Coin; NotRsNum; JumpingCoinTiles; JCoinGfxHandler; ExJCGfx |
| S7 | Power-up tile/attribute/flip output; src/game/oam/power_up_gfx.c | 6 / 6 | PowerUpGfxTable; PowerUpAttributes; DrawPowerUp; PUpDrawLoop; FlipPUpRightSide; PUpOfs |
| S8 | Enemy graphics data/selection/animation and drawing; src/game/oam/normal_enemy_gfx.c and specialized actor owners | 35 / 35 | EnemyGraphicsTable; EnemyGfxTableOffsets; EnemyAttributeData; EnemyAnimTimingBMask; JumpspringFrameOffsets; EnemyGfxHandler; CheckForRetainerObj; CheckForBulletBillCV; SBBAt; CheckForJumpspring; CheckForPodoboo; CheckBowserGfxFlag; SBwsrGfxOfs; CheckForGoomba; GmbaAnim; CheckBowserFront; ChkFrontSte; FlipBowserOver; DrawBowser; CheckBowserRear; ChkRearSte; CheckForSpiny; NotEgg; CheckForLakitu; NoLAFr; CheckUpsideDownShell; CheckRightSideUpShell; CheckForDefdGoomba; CheckForHammerBro; CheckForBloober; CheckToAnimateEnemy; CheckForSecondFrame; CheckAnimationStop; CheckDefeatedState; DrawEnemyObject |
| S9 | Enemy flip/mirror/offscreen and row/column helpers; src/game/oam/normal_enemy_gfx.c and enemy_offscreen_tail.h | 22 / 22 | SkipToOffScrChk; CheckForVerticalFlip; FlipEnemyVertically; CheckForESymmetry; ContES; ESRtnr; SpnySC; MirrorEnemyGfx; EggExc; CheckToMirrorLakitu; NVFLak; CheckToMirrorJSpring; SprObjectOffscrChk; LcChk; Row3C; Row23C; AllRowC; ExEGHandler; DrawEnemyObjRow; DrawOneSpriteRow; MoveESprRowOffscreen; MoveESprColOffscreen |
| S10 | Block and brick chunk sprite output; src/game/oam/block_gfx.c | 14 / 14 | DefaultBlockObjTiles; DrawBlock; DBlkLoop; ChkRep; SetBFlip; BlkOffscr; PullOfsB; ChkLeftCo; MoveColOffscreen; ExDBlk; DrawBrickChunks; DChunks; ChnkOfs; ExBCDr |
| S11 | Fireball/firebar and shared explosion output; src/game/oam/fireball_gfx.c, firebar_gfx.c and fireworks_gfx.c | 7 / 7 | DrawFireball; DrawFirebar; FireA; ExplosionTiles; DrawExplosion_Fireball; DrawExplosion_Fireworks; KillFireBall |
| S12 | Small platform sprite rows; src/game/oam/small_platform_gfx.c | 6 / 6 | DrawSmallPlatform; TopSP; BotSP; SOfs; SOfs2; ExSPl |
| S13 | Bubble sprite output; src/game/fireball/bubble.c | 2 / 2 | DrawBubble; ExDBub |
| S14 | Player graphics table bindings and indexed consumers; src/game/oam/player_gfx.c | 3 / 3 | PlayerGfxTblOffsets; PlayerGraphicsTable; SwimKickTileNum |
| S15 | Cross-chain ledger/evidence census, current ROM matrix, complete native regressions and original DOS16 link | 154 / 0 | All exact labels above; no inferred fresh coverage. |

## Per-chain execution and exits

Each S audits source branches, RAM reads/writes, immutable indexed tables,
call order, tail jumps and actual child returns, then runs the same original-ROM
input batch through current x86/x64 C. Shared descendants may be invoked as
already implemented dependencies without promoting their unobserved contracts.
At an owner/route-family split the successor gets its own admitted packet;
large graphics families may be split further only with exact node custody and
source-order rationale, never into one lifecycle per small data label.
Tables close only when bindings and indexed consumer use are proved, not merely
because bytes exist. S14 must establish the table contract through its real
implemented indexed consumer before credit; it does not pre-credit T66 logic.

Every mismatch is repaired and re-audited inside its admitted S before advancing.
Operational proof independently builds C90 x86/x64, focused tests, platform
purity and original OpenNT DOS16. Product-code changes refresh all three owner-
approved EXEs; pure audit/test/evidence changes retain the latest delivery.
T closure requires all scoped nodes and feasible owned controls/material rows
exact or a specifically accepted source-infeasible proof, named pending external
boundaries, a cross-chain route matrix and integrated regression.

## Current maintenance receivers

BlockBufferChk_Enemy -> M2 T44 S1; ResidualMiscObjectCode -> M2 T44 S1; BlockBufferChk_FBall -> M2 T44 S1; ResJmpM -> M2 T44 S1; BBChk_E -> M2 T44 S1; BlockBufferAdderData -> M2 T44 S1; BlockBuffer_X_Adder -> M2 T44 S1; BlockBuffer_Y_Adder -> M2 T44 S1; BlockBufferColli_Feet -> M2 T44 S1; BlockBufferColli_Head -> M2 T44 S1; BlockBufferColli_Side -> M2 T44 S1; BlockBufferCollision -> M2 T44 S1; RetXC -> M2 T44 S1; RetYC -> M2 T44 S1; VineYPosAdder -> M2 T44 S2; DrawVine -> M2 T44 S2; VineTL -> M2 T44 S2; SkpVTop -> M2 T44 S2; ChkFTop -> M2 T44 S2; NextVSp -> M2 T44 S2; SixSpriteStacker -> M2 T44 S3; StkLp -> M2 T44 S3; FirstSprXPos -> M2 T44 S3; FirstSprYPos -> M2 T44 S3; SecondSprXPos -> M2 T44 S3; SecondSprYPos -> M2 T44 S3; FirstSprTilenum -> M2 T44 S3; SecondSprTilenum -> M2 T44 S3; HammerSprAttrib -> M2 T44 S3; DrawHammer -> M2 T44 S3; ForceHPose -> M2 T44 S3; GetHPose -> M2 T44 S3; RenderH -> M2 T44 S3; NoHOffscr -> M2 T44 S3; FlagpoleScoreNumTiles -> M2 T44 S4; FlagpoleGfxHandler -> M2 T44 S4; ChkFlagOffscreen -> M2 T44 S4; MoveSixSpritesOffscreen -> M2 T44 S4; DumpSixSpr -> M2 T44 S4; DumpFourSpr -> M2 T44 S4; DumpThreeSpr -> M2 T44 S4; DumpTwoSpr -> M2 T44 S4; ExitDumpSpr -> M2 T44 S4; DrawLargePlatform -> M2 T52 S6; ShrinkPlatform -> M2 T44 S5; SetLast2Platform -> M2 T44 S5; SetPlatformTilenum -> M2 T44 S5; SChk2 -> M2 T44 S5; SChk3 -> M2 T44 S5; SChk4 -> M2 T44 S5; SChk5 -> M2 T44 S5; SChk6 -> M2 T44 S5; SLChk -> M2 T44 S5; ExDLPl -> M2 T44 S5; DrawFloateyNumber_Coin -> M2 T44 S6; NotRsNum -> M2 T44 S6; JumpingCoinTiles -> M2 T44 S6; JCoinGfxHandler -> M2 T44 S6; ExJCGfx -> M2 T44 S6; PowerUpGfxTable -> M2 T44 S7; PowerUpAttributes -> M2 T44 S7; DrawPowerUp -> M2 T44 S7; PUpDrawLoop -> M2 T44 S7; FlipPUpRightSide -> M2 T44 S7; PUpOfs -> M2 T44 S7; EnemyGraphicsTable -> M2 T44 S8; EnemyGfxTableOffsets -> M2 T44 S8; EnemyAttributeData -> M2 T44 S8; EnemyAnimTimingBMask -> M2 T44 S8; JumpspringFrameOffsets -> M2 T44 S8; EnemyGfxHandler -> M2 T44 S8; CheckForRetainerObj -> M2 T44 S8; CheckForBulletBillCV -> M2 T44 S8; SBBAt -> M2 T44 S8; CheckForJumpspring -> M2 T44 S8; CheckForPodoboo -> M2 T44 S8; CheckBowserGfxFlag -> M2 T44 S8; SBwsrGfxOfs -> M2 T44 S8; CheckForGoomba -> M2 T44 S8; GmbaAnim -> M2 T44 S8; CheckBowserFront -> M2 T44 S8; ChkFrontSte -> M2 T44 S8; FlipBowserOver -> M2 T44 S8; DrawBowser -> M2 T44 S8; CheckBowserRear -> M2 T44 S8; ChkRearSte -> M2 T44 S8; CheckForSpiny -> M2 T44 S8; NotEgg -> M2 T44 S8; CheckForLakitu -> M2 T44 S8; NoLAFr -> M2 T44 S8; CheckUpsideDownShell -> M2 T44 S8; CheckRightSideUpShell -> M2 T44 S8; CheckForDefdGoomba -> M2 T44 S8; CheckForHammerBro -> M2 T44 S8; CheckForBloober -> M2 T44 S8; CheckToAnimateEnemy -> M2 T44 S8; CheckForSecondFrame -> M2 T44 S8; CheckAnimationStop -> M2 T44 S8; CheckDefeatedState -> M2 T44 S8; DrawEnemyObject -> M2 T44 S8; SkipToOffScrChk -> M2 T44 S8; CheckForVerticalFlip -> M2 T44 S8; FlipEnemyVertically -> M2 T44 S8; CheckForESymmetry -> M2 T44 S8; ContES -> M2 T44 S8; ESRtnr -> M2 T44 S8; SpnySC -> M2 T44 S8; MirrorEnemyGfx -> M2 T44 S8; EggExc -> M2 T44 S8; CheckToMirrorLakitu -> M2 T45 S1; NVFLak -> M2 T45 S1; CheckToMirrorJSpring -> M2 T45 S1; SprObjectOffscrChk -> M2 T45 S1; LcChk -> M2 T45 S1; Row3C -> M2 T45 S1; Row23C -> M2 T45 S1; AllRowC -> M2 T45 S1; ExEGHandler -> M2 T45 S1; DrawEnemyObjRow -> M2 T45 S1; DrawOneSpriteRow -> M2 T45 S1; MoveESprRowOffscreen -> M2 T45 S1; MoveESprColOffscreen -> M2 T45 S1; DefaultBlockObjTiles -> M2 T45 S2; DrawBlock -> M2 T45 S2; DBlkLoop -> M2 T45 S2; ChkRep -> M2 T45 S2; SetBFlip -> M2 T45 S2; BlkOffscr -> M2 T45 S2; PullOfsB -> M2 T45 S2; ChkLeftCo -> M2 T45 S2; MoveColOffscreen -> M2 T45 S2; ExDBlk -> M2 T45 S2; DrawBrickChunks -> M2 T45 S2; DChunks -> M2 T45 S2; ChnkOfs -> M2 T45 S2; ExBCDr -> M2 T45 S2; DrawFireball -> M2 T45 S3; DrawFirebar -> M2 T45 S3; FireA -> M2 T45 S3; ExplosionTiles -> M2 T45 S3; DrawExplosion_Fireball -> M2 T45 S3; DrawExplosion_Fireworks -> M2 T45 S3; KillFireBall -> M2 T45 S3; DrawSmallPlatform -> M2 T45 S4; TopSP -> M2 T45 S4; BotSP -> M2 T45 S4; SOfs -> M2 T45 S4; SOfs2 -> M2 T45 S4; ExSPl -> M2 T45 S4; DrawBubble -> M2 T45 S5; ExDBub -> M2 T45 S5; PlayerGfxTblOffsets -> M2 T45 S5; PlayerGraphicsTable -> M2 T45 S5; SwimKickTileNum -> M2 T45 S5.

## S1 admission - shared block-buffer query chain

Scope and expected current promotions are all 14 S1 labels, incoming
needs-evidence. Maximum exact nodes 1494/1992; historical expected new labels
empty because historical mapping already complete. Prove control-02751 through
control-02762 and control-03996/03997; twelve enter needs-evidence and
control-02759/03997 already enter exact (corrected in the closure census). Existing
material enumeration omitted three explicit table-to-consumer dependencies;
record them under this S only after source and actual indexed routes prove them:
BlockBufferAdderData -> PlayerBGCollision, BlockBuffer_X_Adder -> BlockBufferCollision,
BlockBuffer_Y_Adder -> BlockBufferCollision. This expands enumeration transparently,
not a claim that global material enumeration is complete.

Original entries $E388/$E392/$E39C/$E3E8/$E3E9/$E3EC/$E3F0 cover enemy,
misc/fireball and player head/feet/side selectors, all reviewed 28-entry table
indices, X addition/page carry/parity, Y row wrapping/status subtraction,
metatile A, pointer/row and low-nibble scratch. Actual GetBlockBufferAddr return
$E40B and BBChk_E continuation restore ObjectOffset. Full scratch and persistent
RAM plus $0109-$0139 are compared; only other CPU stack bytes excluded. Existing
PlayerBGCollision $DC64 route replays size/crouch/swim selector use for the three
base-table indices; its existing ABI exclusions stay explicit. Table-read
coverage and scalar A/terrain result are checked separately from RAM equality.

S1 shared owner world/block_buffer.c; exact GetBlockBufferAddr and
PlayerBGCollision dependencies retain their accepted custody/status. Native
query APIs expose ROM A as terrain.metatile and normalize only their explicit
boolean presence return; source carry/sign/predicates use the original result.
No runtime emulator or platform gameplay path is admitted.

Owner-local nonredistributable ROM/ASM remain research-only. Ignored
build/m2-t65-s1 owns <=96 MiB raw, 524288 steps/case, 120 seconds/probe,
checkpoint logs and cleanup. Preserve unrelated work. S2 vine output follows.

### S1 raw graph correction

control-02757 is a lexical extractor fall-through, not a feasible head-to-side
LDA edge. Original Head loads A=0 then BIT $01A9 consumes Side's LDA #1
bytes as its operand and continues at $E3EE (LDX #0). Actual head/feet roots
never execute Side entry $E3EC; direct side roots do. Mark only this raw edge
infeasible, retain its identity/proof, and preserve the shared LDX/kernel
continuation. Expected scoped result is 13 exact controls plus one infeasible;
raw total stays 4342, feasible denominator becomes 4322, infeasible 20.

## S1 closure - current query semantics and returns

All fourteen admitted labels are current exact; no deferred labels, custody
transfers or new historical-match credit. Named completed labels:
BlockBufferChk_Enemy, ResidualMiscObjectCode, BlockBufferChk_FBall, ResJmpM, BBChk_E, BlockBufferAdderData, BlockBuffer_X_Adder, BlockBuffer_Y_Adder, BlockBufferColli_Feet, BlockBufferColli_Head, BlockBufferColli_Side, BlockBufferCollision, RetXC, RetYC.

The source audit maps each entry, original slot/index, byte-wrapped X carry,
page parity, Y row/status subtraction, pointer and scratch writes, coordinate
low nibble and metatile return to the shared game owner. Source A is preserved
in terrain.metatile; only the declared presence API normalizes zero/nonzero.
Native CPU X is not an emulated register: source ObjectOffset restoration is
recorded at the ABI and all game-state effects are compared.

The project-owned neutral probe tools/reference_block_query_integration_probe.c
executes original entries $E388/$E392/$E39C/$E3E8/$E3E9/$E3EC. Its native
checker test/block_query_integration_route_check.c runs one batch per width:
7168 enemy, 3456 feet, 3456 head, 3456 side, 1152 miscellaneous and 256 fireball
roots, total 18944 per width, zero differences across 1841 RAM bytes each.
All scratch and $0109-$0139 game aliases are compared; only remaining CPU
stack bytes are excluded. Max original instructions/root is 61. Fixture X,
page and Y wrap through byte values; rows/parity and both selector outcomes
are audited. Actual indexed X and Y reads cover every index 0-27: index 0
512, indices 1-25 each 640, index 26 896 and index 27 1536 reads per table.
Actual GetBlockBufferAddr RTS continuation $E40B occurs 18944 times;
BBChk_E continuation $E3A8 occurs 8576. RetXC executes 7040 times and RetYC
18944, proving both coordinate-return branches.

tools/reference_terrain_connection_probe.c additionally records actual
PlayerBGCollision base-table consumption. Its existing current native checker
replays 800 roots per width with zero differences: 32 player roots compare
1784 persistent RAM bytes (scratch $00-$07 and CPU stack excluded), and 768
pure predicate roots compare 1792 non-stack bytes. Base indices 0/1/2 have
4/4/24 original reads, covering size, crouch and swimming choices. This
does not claim unobserved downstream player nodes.

Two scoped controls, control-02759 and control-03997, were already exact at admission; this S adds fresh integrated return proof without counting them twice. The admission wording incorrectly called all fourteen pending; actual incoming scope was twelve pending and two exact. Scoped exact controls: control-02751, control-02752, control-02753,
control-02754, control-02755, control-02756, control-02758, control-02759,
control-02760, control-02761, control-02762, control-03996, control-03997.
control-02757 is source-infeasible as proved above; raw identity remains.
Feet $E3E8 executes 3456 times; Head $E3E9 6912, direct Side $E3EC 3456,
and common LDX $E3EE 10368. Head/feet never execute Side entry.

Three previously omitted feasible table relations are newly enumerated exact:
material-t65-query-base (BlockBufferAdderData -> PlayerBGCollision),
material-t65-query-x (BlockBuffer_X_Adder -> BlockBufferCollision),
material-t65-query-y (BlockBuffer_Y_Adder -> BlockBufferCollision).
No earlier material relation or out-of-scope node/control is promoted.

Independent operational track: current C90 x86/x64 query/selector checkers
build and each width passes 6/6 focused CTests: block-buffer-core,
area-block-address, enemy-terrain-state, enemy-side-jump-hammer-chain,
local-area and platform-purity. Original OpenNT DOS16 shared-source build
links successfully with its existing OLDNAMES.LIB warning. Audio/focus-pause
regressions separately pass 5/5 on each width. Product C is unchanged;
assets/mysmb16.exe, mysmb32.exe and mysmb64.exe retain the latest S58
delivery including committed audio/title/focus-pause behavior.

Similar-issue sweep: all six entry families and legal original table domains
are covered, immutable production PRG binding is authoritative, local fallback
tables agree with reviewed source, Head BIT skip is explicit, and both actual
child returns precede their consumers. No feasible semantic mismatch was found;
the only graph correction is the infeasible lexical edge. Neutral test/probe
changes contain no ROM table bytes or imported implementation. Ignored S1
raw record/probe artifacts are deleted after accepted gates; neutral logs stay
under build. Reproduction compiles the named project probes against the
read-only local reference core, invokes each with owner ROM/output paths,
then runs both native checkers with those same records and ROM.

Result: current nodes 1480 -> 1494/1992; exact feasible controls
3181 -> 3192/4322 (raw 4342, infeasible 19 -> 20); exact material
368/487 -> 371/490, enumeration still partial. Historical 1992/1992 stays
separate. Cohort K now has 15 exact and 139 pending nodes. T65 stays open;
S2 vine output is next, not admitted by this closure.

## S2 admission - vine sprite chain

All eight planned S2 labels enter needs-evidence, intended fresh exact eight:
VineYPosAdder, DrawVine, VineTL, SkpVTop, ChkFTop, NextVSp,
SixSpriteStacker, StkLp. Baseline exact nodes 1494/1992, controls 3192/4322,
material 371/490 partial; maximum nodes 1502/1992. Historical 1992/1992,
no new historical labels and no custody transfer. Scope control-02763 through
control-02773 and control-03998, twelve pending. External H vine caller and
later large-platform call/return edges retain their source-order receivers.

Entry DrawVine $E435 and its actual SixSpriteStacker $E4AE child return;
standalone stacker covers byte value/OAM wrapping. Shared owners vine_gfx.c
and sprite_stacker.c; accepted relative-position caller state is the input,
not promoted here. Intended original routes cover both vine indices, all six
registered enemy slots, aligned six-record OAM allocations, coordinate wrapping,
cap selection, both clipping outcomes and full stacker value range. Compare
all RAM except true CPU stack; include lower-stack game aliases. Register-only
A/X/Y contracts are mapped explicitly at the native API rather than emulated.

Static read finds DrawVine omitted original scratch $00/$02 writes. This S
will establish a failing original-ROM comparison, restore original writes and
repeat the same complete route. Audit absolute-indexed X/attribute stores,
byte-index tile/clipping loops and actual child return order for similar omissions.
Only shared-game repairs are allowed; refresh all three EXEs if product changes.
Two absent material relations (VineYPosAdder -> DrawVine and SixSpriteStacker
OAM Y output -> DrawVine clipping) are enumerated only after dual proof.

Provenance: owner-local nonredistributable ROM/ASM remain research-only;
project probes are neutral and reference core remains a read-only sibling.
Ignored build/m2-t65-s2 owns <=80 MiB raw records, <=524288 steps/case,
120-second probe budget, checkpoint logs and cleanup. Focused vine OAM,
six-sprite-stacker, vine actor and platform-purity tests, C90 x86/x64 and
original OpenNT DOS16 link are the separate operational track. S3 hammer
output follows only after all scoped feasible differences are repaired.

## S2 closure - vine/stacker source stages and scratch repair

All eight admitted labels are current exact, no scoped deferred labels or
custody transfers: VineYPosAdder, DrawVine, VineTL, SkpVTop, ChkFTop,
NextVSp, SixSpriteStacker, StkLp. Historical expected/actual new matches
remain empty because historical mapping is already complete.

Static audit first found original DrawVine STY $00 and STY $02 omitted.
The pre-fix original-ROM batch reported 24480 byte differences on each native
width. All arise from those two scratch slots: the old source already generated
the same final OAM for legal allocations, but merged tile/cap/clip phases.
The shared game owner now writes saved index/base and follows the original
stack -> absolute-indexed X stores -> attributes -> six-tile loop -> cap ->
separate six-clipping loop order. Only a non-below unsigned wrapped $64
difference writes $F8. The original two-entry offset table is unchanged;
current literal entries and their two indexed consumers agree with the ROM.
No host-specific gameplay branch, new gameplay rule or emulator was added.

The neutral tools/reference_vine_output_probe.c and
test/vine_output_route_check.c execute one original/native batch per width:
12288 DrawVine roots cover both indices, all six registered enemy slots,
four legal aligned six-sprite allocations (including the final OAM boundary),
and 256 coordinate/threshold seeds per combination. X and Y seed multipliers
17 and 13 cover all byte values; start-minus-Y multiplier 25 covers every
wrapped clip difference, including $63/$64/$65. Another 4096 direct stacker
roots cover all 256 starting coordinate bytes and sixteen OAM indices,
including unaligned and $FC/$FE/$FF wrap cases. All 16384 roots compare
1841 RAM bytes: all scratch/OAM and $0109-$0139 game aliases; only remaining
CPU stack is excluded. The final current x86/x64 results are zero differences.

Original maximum instructions/root 223. Actual indexed VineYPosAdder reads:
6144 per index. Cap set/skip: 6144 each. Clip keep/hide: 28800/44928.
Original PC visits: DrawVine 12288, VineTL 73728, SkpVTop 12288,
ChkFTop 73728, NextVSp 73728, SixSpriteStacker 16384, StkLp 98304.
Actual child RTS $E4BF resumes DrawVine $E449 12288 times. Original vine
returns X=6/Y=saved index; direct stacker returns X=0, A=initial+48 and
Y=$02. Native void APIs do not emulate registers: the vine caller explicitly
reloads $02, subsequent phases reload coordinate inputs, and loop/index
control realizes the original return behavior. Unobserved later platform or
outer vine call-site contracts are not promoted.

All twelve admitted controls become exact: control-02763, control-02764,
control-02765, control-02766, control-02767, control-02768, control-02769,
control-02770, control-02771, control-02772, control-02773, control-03998.
Newly enumerated exact material relations: material-t65-vine-adder
(VineYPosAdder -> DrawVine indexed Y offset), material-t65-vine-stack
(SixSpriteStacker -> DrawVine OAM Y clipping). Enumeration remains partial;
no unrelated registry row changed.

Similar-issue sweep: both production stacker callers were inspected.
DrawVine needed saved $00/$02 and separate phases; DrawLargePlatform already
saves $02 and remains reserved for S5. The stacker itself already matches all
byte-wrap cases and was not changed. All original absolute indexed X/attribute
stores and byte-index tile/clipping loops were reviewed; the restored source
distinguishes their address arithmetic. Scoped table/clip/cap/return contracts
are now zero-difference; no outstanding scoped repair is deferred.

Independent operational proof: final C90 x86/x64 builds each pass 14/14
focused/native audio/pause/core/vine/purity CTests and the newly built Win32
product self-test 1/1. Original OpenNT DOS16 shared-source product links with
the existing OLDNAMES.LIB warning. Three refreshed owner-approved artifacts:

- mysmb16.exe: 265173 bytes; SHA-256 1a0cab9d8c6572e4d4737a6f170d759e37bdd42fad0fa07437cd1110e5b95ae9.

- mysmb32.exe: 376206 bytes; SHA-256 cc224bd7e0def5037b23c31794e083f5b0757806f3aecdd031b72ca921512a80.

- mysmb64.exe: 383134 bytes; SHA-256 a6716a70f763cf62c7b042fac57dd691f1904fbf001b0a00f9418060506bb422.

The artifacts retain committed audio, title-pause and focus-pause behavior.
No external redistributability/release claim is made. Only neutral harness
logic/metadata is tracked besides the owner-approved local products. Raw S2
record/probe outputs are removed after accepted gates; logs remain ignored.
Reproduction compiles the named probe against the read-only reference core,
runs it with the owner ROM and an ignored records path, then runs the native
checker on that same records file on each width.

Current totals: nodes 1494 -> 1502/1992, feasible controls 3192 -> 3204/4322
(raw 4342, infeasible 20 unchanged), material 371/490 -> 373/492 partial.
Historical mapping stays 1992/1992. Cohort K has 23 exact and 131 pending
nodes. T65 remains open; S3 hammer pose/output is next, not admitted here.
