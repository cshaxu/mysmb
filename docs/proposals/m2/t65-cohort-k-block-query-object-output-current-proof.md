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

## S3 admission - hammer pose and two-sprite output

All twelve S3 labels enter needs-evidence, expected fresh exact twelve:
FirstSprXPos, FirstSprYPos, SecondSprXPos, SecondSprYPos, FirstSprTilenum,
SecondSprTilenum, HammerSprAttrib, DrawHammer, ForceHPose, GetHPose,
RenderH, NoHOffscr. Baseline exact nodes 1502/1992, controls 3204/4322,
material 373/492 partial; maximum nodes 1514. Historical 1992/1992, expected
new historical labels empty and custody unchanged. Scope controls 02774-02782
and 03999, ten pending; material-00409 through material-00415, seven pending.
External H caller edges remain in their original source-order audit scope.

Entry $E4DC and exit $E540; source table range $E4C0-$E4DB. Shared owner
hammer_gfx.c; prepared relative/offscreen state is an accepted input dependency,
not a fresh offscreen promotion. Actual DumpTwoSpr $E5C1 child and $E540
return are integrated without pre-crediting its S4-owned internal nodes.
Static audit identifies two graph issues before code work: ForceHPose LDX #0
makes its BEQ unconditional, so lexical control-02778 cannot reach GetHPose;
current C duplicates DumpTwoSpr stores instead of calling the shared source
child. The S will restore the native child edge and prove call input/output,
all four table indices, both timer/state gates, coordinate byte wrap and $FC
mask outcomes against original-ROM roots. Any feasible difference remains
here until repaired/re-audited. Expected controls: nine exact, one infeasible.

All scratch/OAM, persistent RAM and lower-stack aliases are compared; true
CPU stack excluded. Native register-only A/X/Y contracts are explicit, not
emulated. One complete product/native checker plus a child-sequence checker
separates final output equality from graph-call proof. Independent operation:
C90 x86/x64 focused misc/hammer/purity/audio/focus tests, Win32 self-tests and
original OpenNT DOS16 link. Product repair refreshes all three EXEs.

Owner-local nonredistributable ROM/ASM are research-only; reference sibling
is read-only. Ignored build/m2-t65-s3 owns <=96 MiB raw, <=524288 steps/case,
120 seconds/probe, checkpoint logs and cleanup. No ROM fixture or derived
implementation is imported; neutral harnesses record local inputs/output.
S4 flagpole/dump chain is next only after this bounded chain closes.

## S3 closure - indexed hammer output and real child edge

All twelve admitted labels become current exact, no scoped deferred label or
custody transfer: FirstSprXPos, FirstSprYPos, SecondSprXPos, SecondSprYPos,
FirstSprTilenum, SecondSprTilenum, HammerSprAttrib, DrawHammer, ForceHPose,
GetHPose, RenderH, NoHOffscr. Historical expected/actual new matches remain
empty; current exact credit is twelve.

Static audit found the hidden tail duplicated DumpTwoSpr's writes rather
than preserving the source child edge. Before repair, full output replay was
zero-difference but the independent child-sequence checker reported 13608
missing calls on each width. Shared hammer_gfx.c now invokes the existing
shared dump helper after clearing source Misc_State, and loads OAM, pose,
relative Y/X and offscreen input in original phase order. Both full output
and actual child-input/sequence checkers now report zero differences for
13824 original-ROM roots per width. The full checker links the actual child;
the separate caller checker validates pre-child RAM/arguments then replays
the original child's effects. Thus identical output cannot mask a missing
native graph edge. The child's internal S4 nodes are not pre-credited.

Neutral tools/reference_hammer_output_probe.c records original $E4DC roots,
actual $E5C1 child entry and $E5C7 RTS continuation $E540.
test/hammer_output_route_check.c supplies both native acceptance tracks.
Nine miscellaneous slots, six timer/state profiles and all 256 frame seeds
give 13824 roots. Profiles include timer zero/nonzero/high-bit and state
zero/one/high-bit-one/other/high-bit-other. Seed multipliers 17/13/29 each
cover all relative X/Y/offscreen byte values; two-sprite OAM allocations
include the final $F8 boundary. Each replay compares 1841 RAM bytes:
all scratch/OAM and $0109-$0139 game aliases, excluding only remaining CPU
stack. Original register-only returns restore X=ObjectOffset and Y=OAM;
native void ABI uses explicit slot/OAM values and does not emulate registers.

Original max instructions/root 45. ForceHPose 9216, GetHPose 4608,
RenderH 13824. Timer skips 4608; state animated/forced alternatives 4608
each. $FC-mask visible/hidden alternatives 216/13608. Actual child returns
13608. Each of all seven tables reads indices 0/1/2/3 10368/1152/1152/1152
times; native immutable table entries and indexed outputs agree with source.
Byte additions retain separate source CLC semantics before both coordinates.

Nine controls exact: control-02774, control-02775, control-02776,
control-02777, control-02779, control-02780, control-02781, control-02782,
control-03999. control-02778 is source-infeasible: original LDX #0 sets
Z and following BEQ always reaches RenderH; the probe rejects any non-render
continuation and any forced entry reaching GetHPose. Its raw identity remains
in the ledger, excluded only from feasible denominator. Seven original material
rows material-00409 through material-00415 become exact, no new enumeration.

Similar-issue sweep inspected direct paired $F8 stores and shared dump callers
under game/oam. Hammer was repaired; flagpole/small-platform/sprite-dump call
sites already use the shared helper (their complete contracts retain planned
audit ownership). Source DrawBrickChunks and PlayerOffscreenChk also use
DumpTwoSpr where current block_gfx/player_gfx duplicate stores; these pending
graph repairs are explicitly assigned to T65 S10 and planned Cohort L T66,
respectively, with historical custody unchanged. Block column-specific stores
are not conflated with the horizontal DumpTwoSpr call. No later node or
call-site is promoted by this sweep.

Independent operational track: final C90 x86/x64 builds each pass 9/9
focused misc/hammer/core/platform-purity and Win32 audio/focus/product-self
tests. Original OpenNT DOS16 shared-source product links with its existing
OLDNAMES.LIB warning. Three refreshed owner-approved local artifacts:

- mysmb16.exe: 265141 bytes; SHA-256 3e00e1d55627b60c4727c9badee31cc1401bfefec5bb2a5895d2e4bfb3cbecdd.

- mysmb32.exe: 376206 bytes; SHA-256 3706e247040e61e12cd0380b9fd126965bcfb19c285d769610cd8646ee205a69.

- mysmb64.exe: 383134 bytes; SHA-256 abb06196e17f5e962fa7c9efdf05d24954106f7de062334c8eae95a0824d209e.

They retain committed audio/title/focus-pause behavior. Only neutral harness
logic is added; no protected input fixture or third-party code import.
Ignored raw records/probe binaries are removed after accepted gates; neutral
logs stay under build. Reproduction compiles the named project probe against
the read-only local reference core, records owner-ROM roots to an ignored
output, then runs both native checkers on the same batch for each width.

Totals: current nodes 1502 -> 1514/1992, controls 3204 -> 3213/4321
(raw 4342, infeasible 20 -> 21), material 373 -> 380/492 partial.
Historical mapping remains 1992/1992. Cohort K has 35 exact and 119 pending
nodes. S3 has no unresolved scoped feasible difference; T65 stays open and
S4 flagpole/dump output is next.

## S4 admission - flagpole graphics and dump leaves

Nine labels enter needs-evidence, expected fresh exact nine: FlagpoleScoreNumTiles,
FlagpoleGfxHandler, ChkFlagOffscreen, MoveSixSpritesOffscreen, DumpSixSpr,
DumpFourSpr, DumpThreeSpr, DumpTwoSpr, ExitDumpSpr. Baseline current nodes
1514/1992, controls 3213/4321, material 380/492 partial; maximum nodes 1523.
Historical 1992/1992, expected new historical labels empty; custody unchanged.
Scope controls 02783-02793 and 04000/04001, thirteen pending, and existing
material-00416. Earlier/later source-owned incoming dump calls are not credited.

Entries $E54B flagpole and $E5B3/$E5B5/$E5BB/$E5BE/$E5C1/$E5C7 dump
leaves. Shared owners flagpole_gfx.c/sprite_dump.c; sprite_row.c/oam.h may
restore the original DrawOneSpriteRow entry adapter (RAM01 store then tail
call), an invoked S9-owned dependency with no premature node credit.
Static audit finds source X+$08 then X+$0C carry survives DumpTwoSpr and is
consumed by the third sprite Y ADC #8; current C omits it. Current score
caller also writes RAM01 early and skips DrawOneSpriteRow directly to
DrawSpriteObject. First establish original full/child-sequence failures,
restore original semantics/edges and repeat the identical batch.

Original flag roots cover all six slots, no-score/all five score indices,
coordinate/carry boundaries and $0E mask alternatives, both real child inputs
and RTS continuations. Direct dump roots cover all byte values and absolute
indexed OAM/RAM boundary behavior; source carry/register preservation is
explicit. All scratch, persistent RAM/OAM and lower-stack aliases compare;
only true CPU stack excluded. Two independent native checkers prove final
outputs and original child order/input/effects. Pure operation: focused
flagpole/dump/sprite/core/purity/audio/self-tests, C90 x86/x64 and original
OpenNT DOS16 link; shared repair refreshes all three EXEs.

Owner-local nonredistributable ROM/ASM remain research-only, reference sibling
read-only. Ignored build/m2-t65-s4 owns <=112 MiB raw, 524288 steps/case,
120 seconds/probe, logs/checkpoints and cleanup. No protected fixture/import.
S5 large platform follows only after scoped feasible differences are resolved.

## S4 closure - flagpole carry and original row entry

All nine admitted labels are current exact, with none deferred or transferred:
FlagpoleScoreNumTiles, FlagpoleGfxHandler, ChkFlagOffscreen,
MoveSixSpritesOffscreen, DumpSixSpr, DumpFourSpr, DumpThreeSpr, DumpTwoSpr,
ExitDumpSpr. Historical expected/actual new matches remain empty.

Static source audit identified a lost carry: wrapped X+8 is followed by
CLC/ADC #12; its carry survives DumpTwoSpr and contributes to third sprite
Y+8. Before repair both native widths showed 36 differing output bytes.
The score caller also skipped DrawOneSpriteRow and stored RAM01 early.
Shared flagpole output now preserves carry explicitly and calls the restored
row entry; that entry stores incoming right-tile A into RAM01 before the
original DrawSpriteObject tail. Caller/child ownership and order now match.
The invoked S9 dependency is repaired without prematurely crediting its node.

tools/reference_flagpole_output_probe.c and test/flagpole_output_route_check.c
provide full actual-child output and independent child-input/order checks.
Each current width matches 4608 flagpole roots and 12288 direct dump roots
with zero differences across 1841 RAM bytes, including all scratch/OAM and
$0109-$0139 game aliases; only remaining CPU stack is excluded. The independent
4608-root caller checker also reports zero differences after repair.
Source register-only contracts use native explicit value/offset/carry locals,
not an emulated CPU. Full output equality does not substitute for child edges.

Flag fixtures cover six slots, six score profiles and 128 seeds: no score and
all five legal score indices, all byte X/Y/offscreen values across profiles,
and legal six-sprite allocations including $E8. Original max steps/root 89.
Dump returns to $E567: 4608; row returns to $E5A7: 3840. Preserved carry zero/
one: 4392/216. Score skip: 768. Offscreen keep/hide: 576/4032. All ten score
table indices are read 768 times each at the original table consumers.
Direct dump fixtures use six entries, all 256 values and eight offsets
0/1/$20/$7f/$e8/$f4/$fc/$ff, preserving both incoming carry values and absolute
indexed writes that cross $0300. Original observed entry counts:
MoveSixSpritesOffscreen 2048, DumpSixSpr 4096, DumpFourSpr 6144,
DumpThreeSpr 8192, DumpTwoSpr 10240, ExitDumpSpr 12288.

Thirteen controls become exact: control-02783 through control-02793 and
control-04000/control-04001. Existing material-00416 becomes exact; no new
material enumeration or infeasible classification. Out-of-scope registry rows
are asserted identical to the preceding commit. External incoming dump callers
retain their source owners and pending dispositions.

Similar-issue sweep: all six dump entries are store-only continuations and
preserve source carry; direct probes exercise both values and indexed borders.
Hammer coordinate additions explicitly clear carry before each ADC, so S3
remains valid. Flagpole's inherited X-to-Y carry is restored here. The row-entry
RAM01 store now belongs to its actual callee. Later row/enemy caller audits
retain S9 ownership, and block/player dump-call repairs retain S10/Cohort L.
No later-scope repair or exact credit is inferred from this sweep.

Operational track: C90 x86/x64 builds and 10/10 focused/product tests per width
pass, including audio rendering/output, death audio, focus pause, product self
test, flagpole/dump/core and platform purity. Original OpenNT DOS16 links the
same shared source with its existing OLDNAMES.LIB warning; no new DOS runtime
qualification is claimed. Updated three products retain committed audio,
title pause and focus-loss pause (owner independently tested those features).
The audio/focus commits are already ancestors of this P; no related candidate
remains in the To-Do queue. Owner-approved artifacts:

- mysmb16.exe: 265205 bytes; SHA-256 3fec2fa65a2c2fc8c3edd11cbdebae222204c79318482a89ae22ed8f23be6d8e.

- mysmb32.exe: 376273 bytes; SHA-256 ec69f1400fe1067cce06527545c23dcc93fb88c38db296dfa9c7e88f150e3c51.

- mysmb64.exe: 383200 bytes; SHA-256 657e73faf5aec4f5e627ca3178e5bbbb63cd517254fb5cd2c74b989893e63a1e.

Owner-local ROM/ASM remain research-only; no protected fixture or third-party
code import. Ignored raw records/probe binaries are removed after closure
gates; neutral logs remain under build. Reproduction compiles the named probe
against the read-only reference core, records owner-ROM roots to an ignored
bounded directory, then runs both native checkers against the same batch.

Totals: nodes 1514 -> 1523/1992; feasible controls 3213 -> 3226/4321
(raw 4342, infeasible 21); material 380 -> 381/492 partial. Historical mapping
remains 1992/1992. Cohort K has 44 exact and 110 pending nodes. S4 closes with
no unresolved scoped feasible difference. T65 remains open; S5 large-platform
output is next, with eleven scoped labels and ten expected fresh exact.

## S5 admission - large-platform ordered output and clipping

Scope eleven in source order: DrawLargePlatform (already exact), ShrinkPlatform,
SetLast2Platform, SetPlatformTilenum, SChk2, SChk3, SChk4, SChk5, SChk6,
SLChk, ExDLPl (ten needs-evidence, intended fresh exact ten). Historical
1992/1992, no new historical credit. Baseline current nodes 1523/1992,
controls 3226/4321, material 381/492 partial; maximum nodes 1533.
Scope control-02794 through control-02819 and control-04002 through
control-04006, all 31 needs-evidence. Existing external SkipPT relations and
material-00178 remain unchanged. No new material relation is presumed.

Entry $E5C8 to $E654: shared small_platform_gfx.c, accepted stacker/dump
dependencies and implemented GetXOffscreenBits dependency (no later node
credit). S4 dump proof precedes this chain; S6 coin output follows. Source
SetLast2Platform directly writes final two Y coordinates, while current C
introduces an extra DumpTwoSpr call: repair original graph, not just pixels.
Both full actual-child and independent caller-input/order records must match.
Fixtures cover six slots, castle/hard/cloud choices, byte X/Y, screen-edge
page/borrow cases, every six-column mask alternative, vertical hide and OAM
allocation boundaries. Compare 1841 RAM bytes including scratch/OAM and
$0109-$0139 aliases; true CPU stack alone excluded. Child return registers
are recorded and mapped to explicit native arguments/results. Source static
audit precedes replay and every scoped mismatch is repaired before S6.

Operational track: current C90 x86/x64 checks and focused platform/core/audio/
focus/purity tests, original OpenNT DOS16 shared-source link; shared changes
refresh all three owner-approved EXEs. Owner-local nonredistributable ROM/ASM
are research-only; sibling reference core is read-only. Ignored
build/m2-t65-s5 owns <=192 MiB raw, 524288 steps/root, 120 seconds/probe,
checkpoint logs and cleanup. No protected fixture or code import.
Similar-issue sweep covers direct-vs-helper stores, child scratch/order and
six sequential offscreen bit branches; later owners retain their scope.

## S5 closure - large-platform original stores and child graph

All eleven scoped labels now have fresh current proof, ten newly exact:
DrawLargePlatform (already exact), ShrinkPlatform, SetLast2Platform,
SetPlatformTilenum, SChk2, SChk3, SChk4, SChk5, SChk6, SLChk, ExDLPl.
None deferred or transferred; historical expected/actual new matches empty.

Static audit found SetLast2Platform introduced an extra DumpTwoSpr child and
reversed the original direct-store order. Before repair, full native output
already matched all 6144 roots, but independent caller proof failed (18362
argument/input/output comparison failures, not distinct gameplay defects).
Shared small_platform_gfx.c now performs original direct +16 then +20 stores,
loads Y after SixSpriteStacker and selects the tile at its original stage.
No platform code changes. Both x86/x64 full and independent caller checkers
then match 6144 original-ROM roots with zero differences each.

tools/reference_large_platform_output_probe.c records actual original $E5C8
roots, all invoked child inputs/effects and stack-depth-qualified RTS returns.
test/large_platform_output_route_check.c full runner links actual children;
separate caller runner checks child input/order then replays recorded effects.
Unexpected DumpTwoSpr is rejected, so identical final pixels cannot hide the
graph discrepancy. 1841 RAM bytes compare: scratch/OAM and lower-stack game
aliases $0109-$0139 included; remaining CPU stack excluded. Native explicit
slot/value/OAM variables and offscreen return value represent useful register
contracts; GetX entry A/Y and final hide entry A are unused by those children
and omitted from argument comparison. Original inputs are still recorded.

Six slots, eight castle/hard/cloud profiles, 128 seeds give 6144 roots. Across
paired slots, relative X and absolute Y span every byte. Allocations include
the last legal six-sprite base $E8. World pages 0/1/2 and screen edges
page1/X$80, page2/X$7f exercise borrow/sign/near-edge cases. Vertical mask
uses all byte values across slots. Max source instructions/root 209.
ShrinkPlatform executes 4608 times; every other scoped entry 6144.
All six actual child continuations are verified against original PC:
SixSpriteStacker $E5D6, DumpFourSpr $E5DD, first DumpSixSpr $E603,
second DumpSixSpr $E609, GetXOffscreenBits $E60D (6144 each), final
MoveSixSpritesOffscreen $E654 (3072). Vertical keep/hide both 3072.
Castle branch taken/fall 3072/3072; secondary-hard branch 1536/1536;
cloud-default branch 3072/3072. Six horizontal skip/hide alternatives:
1911/4233, 1935/4209, 1959/4185, 1983/4161, 2007/4137, 2031/4113.
The probe rejects any unobserved node, child or conditional alternative.

All 31 admitted controls become exact: control-02794 through control-02819
and control-04002 through control-04006. Existing external SkipPT call/return
and material-00178 are unchanged. GetX dependency-node and cross-cohort
producer contracts retain later ownership; no fresh material enumeration or
global material-completeness claim is made. Out-of-scope registry rows are
asserted unchanged from the prior commit.

Similar-issue sweep covered every large-platform store and helper site.
Original stacker/four/six/six/GetX/final-hide calls remain; the final-two
direct-store stage alone had an invented helper and is restored. The six
sequential shift/branch stages match source bit7 through bit2 in order, then
the independent vertical mask. Small-platform output in the same source file
retains S12 audit ownership and is not changed or credited. Earlier hammer
and flagpole real DumpTwoSpr calls remain required, not removed indiscriminately.

Operational track: C90 x86/x64 products/checkers build; each width passes
9/9 large-platform, small-platform-OAM, core, platform purity, focus pause,
audio rendering/output, death audio and product-self tests. Original OpenNT
DOS16 shared-source product links, existing OLDNAMES.LIB warning retained.
This is compile/link evidence, not DOS hardware qualification. Three refreshed
owner-approved local artifacts retain audio/title/focus-pause behavior:

- mysmb16.exe: 265237 bytes; SHA-256 e368211fc72e30fc6d97fcdde76299febf57d511cf4d4e89e2771dda807f176d.

- mysmb32.exe: 376273 bytes; SHA-256 c78c557ae4e58ea110d7eb7d60aeddbde399f89a0300ce5e72f8b29b93136e6c.

- mysmb64.exe: 383200 bytes; SHA-256 18a919fb7d03f1a47470160fc5f3e16126530943e0905c10e32e0af29d23132a.

Neutral original-input harness logic only, no protected fixtures or third-party
implementation import. Raw records/probe binaries are removed after accepted
gates, neutral logs remain under ignored build. Reproduction compiles the
named probe against the read-only local reference core, records owner-ROM
roots to a bounded ignored output, then runs both native checkers on the same
batch for each width. Admission node/ledger/documentation gates passed.

Totals: nodes 1523 -> 1533/1992; controls 3226 -> 3257/4321 (raw 4342,
infeasible 21); material remains 381/492 partial. Historical mapping 1992/1992
is separate. Cohort K now has 54 exact, 100 pending nodes. T65 remains open;
S6 five-node floating/jumping coin output is next. No scoped difference remains.

## S6 admission - coin and floating score output

Five needs-evidence labels, intended fresh exact five: DrawFloateyNumber_Coin,
NotRsNum, JumpingCoinTiles, JCoinGfxHandler, ExJCGfx. Baseline current nodes
1533/1992, controls 3257/4321, material 381/492 partial; maximum nodes 1538.
Historical 1992/1992, no new historical credit or custody transfer.
Scope controls 02820-02826 and 04008/04009 (nine pending), material-00417.
External RunJCSubs call/return retain caller ownership and are not pre-credited.
Original $E686 through $E6BD with floating branch $E655/$E65C; shared owner
objects.c and accepted sprite_dump.c dependency. S5 precedes; S7 follows.
Static audit found duplicated child stores and reordered OAM writes in both
paths. Restore the actual original DumpTwoSpr calls and ordered phases, and
prove four indexed tile consumers. ROM batches compare all scratch/OAM and
$0109-$0139 game aliases (1841 bytes), excluding only true CPU stack.
Native caller verification independently checks original child A/X/Y and
pre-state/order with recorded child effects; full check invokes real child.
Operational C90 x86/x64 tests, platform purity and original OpenNT DOS16 link;
product repairs require three refreshed owner-approved EXEs.
Owner-local nonredistributable ROM/ASM remain research-only, sibling core
read-only; ignored build/m2-t65-s6 owns <=80 MiB raw, 524288 steps/root,
120 seconds/probe and cleanup. Similar-issue sweep: both output paths,
parity/wrapped Y, all table indices, child inputs/returns and store ordering.

## S6 closure - coin/floating score original child boundaries

All five scoped labels freshly exact: DrawFloateyNumber_Coin, NotRsNum,
JumpingCoinTiles, JCoinGfxHandler, ExJCGfx. None deferred or transferred;
historical expected/actual new matches remain empty.
Static audit found both native paths duplicated original DumpTwoSpr writes
and reordered OAM phases. Before repair the full output checker matched 9216
roots, while independent caller checking found one missing child per root
(9216 failures). Shared objects.c now calls actual DumpTwoSpr for floating Y
and coin tiles, preserves source Y/X/tile/attribute store sequence and binds
the original four-entry JumpingCoinTiles table instead of arithmetic synthesis.

tools/reference_coin_output_probe.c records original $E686 roots with actual
$E5C1 input RAM/A/X/Y and $E5C7 returns to $E661 or $E6B0. The neutral
test/coin_output_route_check.c supplies full actual-child output and independent
caller proof. The latter uses GNU link wrapping only in the test executable,
checks pre-child RAM/value/OAM and count then replays recorded child RAM;
production and DOS code have no wrapping or test macro. Source X is preserved
by the dump leaf, not consumed; native caller index/slot convention is checked
against the recorded X, without adding a runtime emulated register.
Both x86/x64 checkers report zero differences for all 9216 roots after repair.
1841 RAM bytes compare: all scratch/OAM and $0109-$0139 game aliases included;
only remaining CPU stack is excluded.

Nine miscellaneous slots, four states 0/1/2/$80 and all 256 frame seeds cover
unsigned state threshold and both parity alternatives. Y seed multiplier13
and relative X multiplier17 cover all byte values/wraps. Two-sprite OAM
allocations include final legal $F8. Original maximum steps/root 29.
Coin return $E6B0 and floating return $E661 occur 4608 times each.
DrawFloateyNumber_Coin raises/holds 2304/2304 times; NotRsNum executes 4608,
ExJCGfx 9216. All four table indices have 1152 actual reads each at $E6A9.
The probe rejects missing indexed reads, wrong returns and incomplete counts.
Static source tests match unsigned CMP #2, LSR parity carry, cleared-carry
X/Y additions, decrement wrapping, immutable table and exit order.

Nine controls exact: control-02820 through control-02826, control-04008,
control-04009. Existing material-00417 becomes exact. External RunJCSubs
call/return remain with caller custody and pending evidence; no new relation
enumeration or later node credit. Out-of-scope registry rows are asserted
identical to the preceding commit.
Similar-issue sweep examines every paired OAM store in objects.c. Both coin
paths are repaired. Coin Y/Y+8 stores remain direct because source values
differ; floating tiles $f7/$fb also remain separate. Other floating enemy
number output follows its own distinct source sequence and accepted ownership,
not the coin's dump call. Earlier flagged block/player duplicate-dump repairs
retain T65 S10/Cohort L ownership; no unrelated edit or inferred promotion.

Operational track: C90 x86/x64 products/checkers build, 8/8 focused/product
tests pass per width (floating OAM, core, purity, focus pause, audio renderer/
output, death audio and self test). Original OpenNT DOS16 same-source build
links with existing OLDNAMES.LIB warning; no DOS runtime qualification claim.
Owner-approved three refreshed artifacts retain audio/title/focus pause:

- mysmb16.exe: 265113 bytes; SHA-256 81be3fcc115ef5acaa6bcce82b43e1181349bfa03e08c9f1f8accdff18a63d2e.

- mysmb32.exe: 376313 bytes; SHA-256 f6373750d17c5b86435219adf69c508ac09560b29bb2ae35860d3079acdc3fda.

- mysmb64.exe: 383239 bytes; SHA-256 81de837bdb263105dcc4521168f87542125e7d0f610ad339ce9fd2daf015c879.

Owner-local nonredistributable ROM/ASM remain ignored research inputs; no
protected test fixture or third-party implementation import. Raw records and
probe binary removed after accepted gates, neutral logs retained under build.
Reproduction compiles the named project probe against the read-only reference
core, records owner-ROM roots to a bounded ignored output then runs both
current native checkers on the same batch. Admission gates passed.

Totals: nodes 1533 -> 1538/1992; controls 3257 -> 3266/4321 (raw 4342,
infeasible 21); material 381 -> 382/492 partial. Historical mapping 1992/1992
remains separate. Cohort K has 59 exact, 95 pending nodes. T65 remains open;
S7 six-node power-up output chain is next. No scoped feasible difference remains.

## S7 admission - power-up indexed rows, attributes and offscreen handoff

Six needs-evidence labels, intended fresh exact six: PowerUpGfxTable,
PowerUpAttributes, DrawPowerUp, PUpDrawLoop, FlipPUpRightSide, PUpOfs.
Baseline nodes1538/1992, controls3266/4321, material382/492 partial;
maximum nodes1544. Historical1992/1992, expected new historical matches empty.
Ten controls02827-02835 and04010, two material rows00418/00419 pending.
External RunPUSubs call/return retain caller ownership. Entry $E6D2 to $E73B
then original SprObjectOffscrChk dependency; shared power_up_gfx.c and invoked
row/offscreen entries. S6 precedes; S8 enemy selection follows.
Static source audit found skipped DrawOneSpriteRow, early RAM01 ownership,
missing flower/star RAM00 type store and absent offscreen erase guard.
Restore shared dependency entry as needed without promoting S9 internals;
no unrelated enemy caller migration. Full and independent caller proof compare
actual two row inputs/returns plus tail input and final effects. All scratch,
OAM and $0109-$0139 aliases compare (1841 bytes); true CPU stack excluded.
Four legal types, frame/coordinate/offscreen bytes, base attributes and high-Y/
Podoboo guard profiles exercise tables, loops, palette/flip and tail outcomes.
C90 x86/x64 focused operational tests, purity and original OpenNT DOS16 link;
product repairs refresh three owner-approved local EXEs.
Owner-local nonredistributable ROM/ASM research-only, sibling core read-only.
Ignored build/m2-t65-s7 owns <=208 MiB raw, 524288 steps/root,
120 seconds/probe, checkpoints and cleanup. Similar-issue sweep: row entry
scratch ownership, post-row type scratch, actual tail entry/erase and callers.

## S7 closure - power-up original row and tail boundaries

Six scoped labels freshly exact: PowerUpGfxTable, PowerUpAttributes,
DrawPowerUp, PUpDrawLoop, FlipPUpRightSide, PUpOfs. None deferred or
transferred; historical expected/actual new matches empty.

Static audit found direct DrawSpriteObject skipped original DrawOneSpriteRow,
caller prematurely wrote RAM01, flower/star omitted RAM00=type, and raw
offscreen clipping omitted original final erase guard. Before repair the
full checker reported 11760 differing byte comparisons; the caller checker
reported 19952 comparisons/call-count failures (not distinct gameplay bugs).
Shared power_up_gfx.c now invokes original row entry, stores type at the
original stage, sets palette rows before top-right/bottom-right OR stores,
and enters a shared offscreen entry. sprite_row.c's meaningful entry loads
source ObjectOffset/Enemy_OffscreenBits, applies existing clipping and calls
the accepted EraseEnemyObject owner only for bit7, non-Podoboo and highY=2.
The previous forwarding-only power-up helper is removed. No platform changes.

tools/reference_power_up_output_probe.c records original $E6D2 roots,
actual two $EBB2 row inputs and RTS continuation $E702, plus $EB64 tail
pre-state and complete final output. test/power_up_output_route_check.c full
checker links actual shared descendants; independent GNU-test-only wrapped
checker validates row RAM/A/X/Y and tail RAM/OAM/count/order before replaying
recorded effects. No test wrapping or macro enters any product target.
Both x86/x64 checkers match 8192 roots with zero differences across1841 RAM
bytes: scratch/OAM and $0109-$0139 game aliases included, only true CPU stack
excluded. Original saved type/CPU registers become native type/index/OAM
locals; original tail A/X inputs are overwritten/unused at entry and not
emulated. Native row argument increments agree with recorded next row input.

Four legal types, eight attribute/highY/Podoboo profiles and all256 frame
seeds give8192 roots. Base attributes0/$20; highY1/2; ID$2e/Podoboo$0c;
relativeX/Y multiplier17/13 and offscreen multiplier29 each cover all bytes.
OAM$20/$e8 includes final legal three-row allocation (stale third row checked).
Original max steps215, row returns16384, tail entries8192, erase calls1024.
Mushroom/1-up palette skips2048 each, flower/star branches2048 each, flip4096;
loop taken/exit8192 each. All16 tile indices read2048 times each and all4
attribute indices read2048 times each at actual original consumers. The probe
rejects wrong returns, missing table indices and incomplete branch counts.

Ten scoped controls exact: control-02827 through control-02835 and
control-04010. Material00418/00419 exact; no new enumeration/infeasible row.
External RunPUSubs call/return and S9 row/offscreen internal nodes/edges are
not promoted. Every out-of-scope registry row is asserted unchanged from HEAD.
Full tail effects prove the dependency needed by this caller; they do not
close unobserved internal graph connections.

Similar-issue sweep: both power-up row calls now share original RAM01 owner;
flower/star RAM00 store and flip order restored. Shared raw clip consumers
are normal_enemy_gfx, bloober_gfx, bowser_gfx, hammer_bro_gfx, podoboo_gfx and
spiny_gfx. Their exact source-stage consolidation remains the existing S8/S9
scope; no broad rewrite is made here. S9 must replace simplified raw clipping
with original column/row child calls and reconcile existing caller-owned erase
guards, avoiding duplicated erase when adopting the new shared entry. The
entry has current root output proof but its internal node/edge statuses remain
pending. Earlier block/player dump-call repairs retain S10/Cohort L ownership.
The focused power-up fixture now sets actual caller ObjectOffset=5 rather than
using an unrelated default slot. No unrelated code or maintenance transfer.

Operational track: current C90 x86/x64 products/checkers build and8/8 focused
tests pass per width (power-up OAM/core/purity/focus/audio renderer/output/death
audio/self test). Original OpenNT DOS16 same-source build/link passes with
existing OLDNAMES.LIB warning; no DOS hardware qualification is inferred.
Three refreshed owner-approved local artifacts retain audio/title/focus pause:

- mysmb16.exe: 265289 bytes; SHA-256 dd132023f47e4fa49757fef910a5d62f836f1841173f4b0ecc82b0347758fddf.

- mysmb32.exe: 376322 bytes; SHA-256 608fe9d3721a4436aadee5d41e6391cc0f827da13824dc79dcb48288dc27fa8b.

- mysmb64.exe: 383248 bytes; SHA-256 28ed6d4296e3afe3532ce8e48e32747737080436b84ac48223ff6db8507669c6.

Owner-local nonredistributable ROM/ASM remain research-only; neutral harnesses
contain no protected fixture or imported third-party implementation. Raw record/
probe binaries removed after accepted gates; neutral logs stay below ignored
build. Reproduction compiles the named probe against the read-only reference
core, records owner-ROM roots to bounded ignored output then runs both current
native checkers on the same batch. Admission gates passed.

Totals: nodes1538 ->1544/1992; controls3266 ->3276/4321 (raw4342,
infeasible21); material382 ->384/492 partial. Historical1992/1992 is separate.
Cohort K has65 exact and89 pending nodes. T65 remains open; S8 enemy graphics
selection's35-node chain is next. No scoped feasible difference remains.


## S8 admission - enemy graphics selection and original row calls

Scope is exactly the35 labels in the unchanged S8 plan above, source order,
all incoming needs-evidence. Intended fresh current promotions35; maximum
1579/1992 from1544. Historical expected/actual new matches remain empty,
1992/1992 is historical mapping only. Maintenance receivers retain custody.

Entry is original EnemyGfxHandler $E87D; exit is DrawEnemyObject's three
DrawEnemyObjRow calls and handoff to CheckForVerticalFlip or SkipToOffScrChk.
Shared normal_enemy_gfx.c and specialized actor owners implement selection.
S7 is closed; S9 owns the downstream flip/mirror/offscreen internal proof.
Invoking or repairing a row dependency does not promote S9 nodes by inference.
Source-owned controls are control-02836 through control-02920 (85 pending)
plus already exact return edges control-03689 and control-03796. Material
rows00420-00424 remain pending. Raw fallthroughs02895 and02908 require explicit
infeasibility review: LDX #$B4/BNE and LDA #$03/STA/BNE respectively; no
denominator change or infeasible disposition is made before the full proof.

ROM-logic track: audit each node's branch, RAM/table binding and call/return,
then record the original selection boundary, indexed reads, three real row
inputs/returns and full output. Run one bounded family batch per width, not
one process per micro-label. Compare mapped RAM including game stack aliases;
document actual CPU-stack exclusion. Operational track separately checks
normal/Bowser/spring/OAM/core/purity/audio/pause/self tests, current x86/x64
builds and original OpenNT DOS16 link. Code changes refresh three products.

Original ROM and ASM remain owner-local nonredistributable research inputs.
Ignored build/m2-t65-s8 owns raw outputs:192MiB cap,120seconds/run,
524288steps/case, checkpoint summaries, coordinator cleanup after closure.

### S8 initial source audit - findings awaiting repair and ROM replay

This is an active corrective S, not a closure or completion claim.

| Source phase / exact labels | Native comparison and remaining proof |
| --- | --- |
| EnemyGraphicsTable; EnemyGfxTableOffsets; EnemyAttributeData | Indexed native arrays exist; audit original extents, adjacent-byte/wrapping reads and all reachable consumers in the controlled batch. Specialized Bowser/spring arrays must not replace original binding without proof. |
| EnemyAnimTimingBMask; JumpspringFrameOffsets | Native mask8 and spring5 values match visible source constants. Original second timing-mask index is residual; prove unreachable before accepting its contract. All five spring indices require actual reads. |
| EnemyGfxHandler; CheckForRetainerObj | Prefix and Piranha early return present. Audit ObjectOffset reload versus explicit slot and scratch write stage. Retainer normalizes code21/direction1/state0. |
| CheckForBulletBillCV; SBBAt; CheckForJumpspring; CheckForPodoboo | Cannon code8, Y decrement and priority; spring code24-26/state3; Podoboo nonnegative velocity flip are present. Prove timer/sign and rewritten-code branches. |
| CheckBowserGfxFlag; SBwsrGfxOfs | **Mismatch:** generic C returns0 on nonzero flag instead of selecting code22/front or23/rear. Specialized retainer dispatch bypasses this original shared branch. |
| CheckForGoomba; GmbaAnim | Native state>=2, state bit5/timer/frame gate and direction XOR exist; audit ordering and all branch combinations. |
| CheckBowserFront; ChkFrontSte; FlipBowserOver; DrawBowser; CheckBowserRear; ChkRearSte | Specialized bowser_gfx.c duplicates tile selection/front-mouth/rear-step/defeat-Y logic; generic path never reaches it. Rejoin the original shared selection and drawing path, then prove exact scratch and row effects. No visual-equivalence assumption. |
| CheckForSpiny; NotEgg | **Mismatch:** native jumps to hammer only for egg state5; original offset24 always jumps through NotEgg, bypassing shell selection even for ordinary Spiny. State4 can select a shell and alter height incorrectly. |
| CheckForLakitu; NoLAFr | Native alternate offset96 and defeated jump exist; prove bit5 and timer boundary16. |
| CheckUpsideDownShell; CheckRightSideUpShell; CheckForDefdGoomba | Native shell/Goomba offset and Y adjustments exist; need corrected Spiny predecessor and controlled state/type branches. |
| CheckForHammerBro | **Mismatch:** original HammerBro state0 branches directly to animation; current C falls into Bloober interval checks. Interval>=5 can suppress the expected frame change. State-bit3 paths also need proof. |
| CheckForBloober | Offset48 bypass, interval>=5, Bloober interval1 and three Y increments are present; prove actual entry and exits. |
| CheckToAnimateEnemy; CheckForSecondFrame; CheckAnimationStop; CheckDefeatedState | Native exclusion, retainer/world, mask8, ED A0/timer gates and defeated flip/state clear exist; prove each branch, wrap and original residual infeasibility. |
| DrawEnemyObject | **Mismatch:** three native helper calls go directly to DrawSpriteObject after prematurely writing RAM01; original calls DrawEnemyObjRow then DrawOneSpriteRow. Restore meaningful indexed row entry and actual three returns, not just equal final pixels. |

Similar-issue sweep covers ordinary generic rendering, retainer/Bowser
dispatch and spring specialization plus all three row sites. Specialized
consumers remain pending until a shared canonical route and original-ROM
contracts are demonstrated. S9 internals stay pending, with no custody transfer.
Current exact counts remain1544/1992 nodes,3276/4321 feasible controls and
384/492 material(partial). Existing three S7 products are unchanged.

### S8 P1 admission review

Verify-NodeProgress accepts audit scope35 with historical baseline/maximum1992,
zero expected historical additions and no custody transfer. The generated
ledger validates1992 receivers, no orphan nodes,81 tasks and475 subtasks.
Documentation governance and diff whitespace checks pass. Registry review
changes only the four named source findings and controls02851,02852,02853,
02875,02892,02916,02917,02918; exact counters are unchanged.
The flag-zero branch02850 remains needs-evidence because the generic C still
reaches ordinary selection on that condition; it is not mislabeled a mismatch.
No product code changes, so no executable refresh is required for this P.
S8 remains admitted, with repair and ROM/native evidence unfinished.
