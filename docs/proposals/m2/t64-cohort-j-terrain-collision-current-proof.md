# M2 T64: Cohort J terrain and collision current-equivalence proof

T64 continues the approved source-order program after closed T63. It audits the remaining **253** Cohort-J labels, from `OffscreenBoundsCheck` through `CollisionFound`. Historical mapping remains **1,992 / 1,992**; the incoming current-equivalence baseline is **1,227 / 1,992** nodes and **2,461 / 4,324** feasible controls.

Every chain below is a shared-game audit only. It retains historical receiver custody in the ledger, records node and edge results individually, and batches each chain's original-ROM routes per x86/x64 process. A mismatch stays in its current S until the shared C owner is repaired and re-audited. The plan splits only at a current shared-owner or source-route boundary; it does not create a separate S merely for a data table or helper leaf.

## Exact source-order S plan

| S | ROM lines | Current shared owner | Exact inventory labels |
| --- | --- | --- | --- |
| S1 | 11031-11075 | shared game core: enemy/actor_slots.c | OffscreenBoundsCheck; LimitB; ExtendLB; TooFar; ExScrnBd |
| S2 | 11085-11141 | shared game core: world/fireball_enemy.c | FireballEnemyCollision; FireballEnemyCDLoop; GoombaDie; NotGoomba; NoFToECol; ExitFBallEnemy |
| S3 | 11145-11224 | src/game/world/fireball_hit.c | BowserIdentities; HandleEnemyFBallCol; ChkBuzzyBeetle; HurtBowser; SetDBSte; ChkOtherEnemies; ShellOrBlockDefeat; StnE; GoombaPoints; EnemySmackScore; ExHCF |
| S4 | 11228-11258 | src/game/world/hammer_collision.c | PlayerHammerCollision; ClHCol; ExPHC |
| S5 | 11262-11305 | src/game/world/powerup_collision.c | HandlePowerUpCollision; Shroom_Flower_PUp; SetFor1Up; UpToSuper; UpToFiery; NoPUp |
| S6 | 11309-11566 | src/game/world/player_enemy_collision.c | ResidualXSpdData; KickedShellXSpdData; DemotedKoopaXSpdData; PlayerEnemyCollision; NoPECol; CheckForPUpCollision; EColl; KickedShellPtsData; HandlePECollisions; KSPts; ExPEC; ChkForPlayerInjury; ChkInj; ChkETmrs; TInjE; InjurePlayer; ForceInjury; SetKRout; SetPRout; ExInjColRoutines; KillPlayer; StompedEnemyPtsData; EnemyStomped; EnemyStompedPts; ChkForDemoteKoopa; RevivalRateData; HandleStompedShellE; SBnce; ChkEnemyFaceRight; LInj; EnemyFacePlayer; SFcRt; SetupFloateyNumber; ExSFN |
| S7 | 11571-11729 | src/game/world/enemy_collision.c | SetBitsMask; ClearBitsMask; EnemiesCollision; ECLoop; YesEC; NoEnemyCollision; ReadyNextEnemy; ExitECRoutine; ProcEnemyCollisions; ShellCollisions; ExitProcessEColl; ProcSecondEnemyColl; MoveEOfs; EnemyTurnAround; RXSpd; ExTA |
| S8 | 11734-11799 | src/game/enemy/platform_collision.c | LargePlatformCollision; ChkForPlayerC_LargeP; ExLPC; SmallPlatformCollision; ChkSmallPlatLoop; MoveBoundBox; ExSPC |
| S9 | 11804-11888 | src/game/enemy/platform_collision.c and src/game/enemy/platform_position.c | ProcSPlatCollisions; ProcLPlatCollisions; ChkForTopCollision; SetCollisionFlag; PlatformSideCollisions; SideC; NoSideC; PlayerPosSPlatData; PositionPlayerOnS_Plat; PositionPlayerOnVPlat; ExPlPos |
| S10 | 11892-11908 | src/game/world/collision.c | CheckPlayerVertical; ExCPV; GetEnemyBoundBoxOfs; GetEnemyBoundBoxOfsArg |
| S11 | 11924-11964 | src/game/player/terrain.c | PlayerBGUpperExtent; PlayerBGCollision; SetFallS; SetPSte; ChkOnScr; ExPBGCol; ChkCollSize; GBBAdr |
| S12 | 11971-12088 | src/game/player/terrain.c and terrain children | HeadChk; SolidOrClimb; NYSpd; DoFootCheck; AwardTouchedCoin; ChkFootMTile; ContChk; LandPlyr; InitSteP; DoPlayerSideCheck; SideCheckLoop; BHalf; ExSCH; CheckSideMTiles |
| S13 | 12094-12144 | src/game/player/terrain.c | ContSChk; ChkPBtm; PipeDwnS; PlyrPipe; SetCATmr; ChkGERtn; StopPlayerMove; ExCSM; AreaChangeTimerData |
| S14 | 12147-12217 | src/game/player/terrain_metatiles.c and climbing.c | HandleCoinMetatile; HandleAxeMetatile; ErACM; ClimbXPosAdder; ClimbPLocAdder; FlagpoleYPosData; HandleClimbing; ExHC; ChkForFlagpole; FlagpoleCollision; ChkFlagpoleYPosLoop; MtchF |
| S15 | 12218-12286 | src/game/player/climbing.c and terrain_metatiles.c | RunFR; VineCollision; PutPlayerOnVine; SetVXPl; ExPVne; ChkInvisibleMTiles; ExCInvT; ChkForLandJumpSpring; ExCJSp; ChkJumpspringMetatiles |
| S16 | 12292-12293 | src/game/player/terrain_metatiles.c | JSFnd; NoJSFnd |
| S17 | 12295-12372 | src/game/player/pipe_entry.c and terrain children | HandlePipeEntry; GetWNum; ExPipeE; ImpedePlayerMove; RImpd; NXSpd; PlatF; ExIPM |
| S18 | 12380-12415 | src/game/world/metatiles.c | SolidMTileUpperExt; CheckForSolidMTiles; ClimbMTileUpperExt; CheckForClimbMTiles; CheckForCoinMTiles; CoinSd; GetMTileAttrib; ExEBG |
| S19 | 12420-12611 | src/game/enemy/background.c | EnemyBGCStateData; EnemyBGCXSpdData; EnemyToBGCollisionDet; DoIDCheckBGColl; HBChk; CInvu; YesIn; NoEToBGCollision; HandleEToBGCollision; GiveOEPoints; ChkToStunEnemies; Demote; SetStun; SetWYSpd; SetNotW; ChkBBill; NoCDirF; ExEBGChk; LandEnemyProperly; SChkA; ChkLandedEnemyState; SetForStn; ExSteChk; ProcEnemyDirection; InvtD; CNwCDir; LandEnemyInitState; NMovShellFallBit; ChkForRedKoopa; Chk2MSBSt; GetSteFromD; SetD6Ste |
| S20 | 12617-12636 | src/game/enemy/side_collision.c:mysmb_objects_check_enemy_side | DoEnemySideCheck; SdeCLoop; NextSdeC; ExESdeC |
| S21 | 12638-12646 | src/game/objects.c:mysmb_objects_bump_enemy | ChkForBump_HammerBroJ; NoBump |
| S22 | 12654-12654 | src/game/objects.c:mysmb_objects_bump_enemy/RXSpd owner | InvEnemyDir |
| S23 | 12660-12660 | src/game/enemy/distance.c:mysmb_enemy_player_difference | PlayerEnemyDiff |
| S24 | 12671-12671 | src/game/world/collision.c:mysmb_world_land_enemy | EnemyLanding |
| S25 | 12679-12701 | src/game/enemy/jump_terrain.c:mysmb_objects_step_enemy_jump_terrain | SubtEnemyYPos; EnemyJump; DoSide |
| S26 | 12705-12705 | src/game/objects.c:mysmb_objects_step_hammer_terrain | HammerBroBGColl |
| S27 | 12711-12711 | src/game/objects.c:mysmb_objects_kill_enemy_above_block | KillEnemyAboveBlock |
| S28 | 12717-12726 | src/game/objects.c:mysmb_objects_step_hammer_terrain | UnderHammerBro; NoUnderHammerBro |
| S29 | 12732-12732 | src/game/world/block_buffer.c:mysmb_world_query_enemy_under | ChkUnderEnemy |
| S30 | 12737-12747 | src/game/world/metatiles.c:mysmb_world_enemy_metatile_is_non_solid | ChkForNonSolids; NSFnd |
| S31 | 12751-12777 | src/game/world/collision.c | FireballBGCollision; ClearBounceFlag; InitFireballExplode |
| S32 | 12791-12791 | src/game/world/bounding_box.c and src/game/world/geometry.c | BoundBoxCtrlData |
| S33 | 12805-12866 | src/game/world/collision.c and src/game/world/bounding_box.c | GetFireballBoundBox; GetMiscBoundBox; FBallB; GetEnemyBoundBox; SmallPlatformBoundBox; GetMaskedOffScrBits; CMBits; LargePlatformBoundBox; SetupEOffsetFBBox; MoveBoundBoxOffscreen |
| S34 | 12878-12878 | src/game/world/bounding_box.c and src/game/world/geometry.c | BoundingBoxCore |
| S35 | 12916-12949 | src/game/world/collision.c and src/game/world/bounding_box.c | CheckRightScreenBBox; SORte; NoOfs; CheckLeftScreenBBox; SOLft; NoOfs2 |
| S36 | 12956-13007 | src/game/world/bounding_box.c and src/game/world/geometry.c | PlayerCollisionCore; SprObjectCollisionCore; CollisionCoreLoop; SecondBoxVerticalChk; FirstBoxGreater; NoCollisionFound; CollisionFound |

## S1 admission — enemy offscreen bounds

S1 admits `OffscreenBoundsCheck -> ExScrnBd` at `$D67A-$D6D5`: `OffscreenBoundsCheck`, `LimitB`, `ExtendLB`, `TooFar`, and `ExScrnBd`. It is the first contiguous five-label chain and is owned by `src/game/enemy/actor_slots.c`. Predecessor `MoveLiftPlatforms` is closed in T63; S2 begins `FireballEnemyCollision`.

The ROM-logic track compares Flying Cheep's direct return, the two CPY-derived carry paths into special and ordinary left-bound arithmetic, borrow/carry propagation across all four scratch bytes, both out-of-range decisions, each retained special right-side ID, and the erase call/return. The operational track converts the existing 1,024 original-ROM record family into a batched x86/x64 manifest, runs the exhaustive focused bound oracle, platform-purity check and the OpenNT DOS16 shared-source link. It refreshes all three products only if shared product C changes.

### S1 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **1,227 / 1,992**.
- Current exact feasible controls: **2,461 / 4,324**.
- Scope: **5** labels; expected fresh matches: **5**; maximum current exact nodes: **1,232 / 1,992**.

## S1 closure

All five scoped nodes are current-exact: `OffscreenBoundsCheck`, `LimitB`,
`ExtendLB`, `TooFar`, and `ExScrnBd`. The static comparison confirms the
Flying Cheep early return, both special-ID carry paths, each scratch-bound
write, signed page decision, all five right-side exemptions, and the erase
call/return. The registry records its 15 source-owned Cohort-J control
relations and four source-owned material handoffs as exact.

The controlled original-ROM route ran 1,024 records through one x86 and one
x64 native process; both reports were zero differences. The exhaustive bound
oracle, x86/x64 audio/pause/offscreen tests and product self-tests passed.
OpenNT linked the shared DOS16 source after supplying its existing local
`OLDNAMES.LIB` runtime dependency in the ignored build tree. Platform purity
initially found a Win32 title helper reading `game.ram`; the repair moved that
read behind the shared `mysmb_game_is_paused` query and the gate now passes.
The C change refreshed all three owner-local package artifacts.

Current totals after S1: historical mapping **1,992 / 1,992**; current exact
nodes **1,232 / 1,992**; current exact feasible controls **2,476 / 4,324**
(4,342 raw, 18 infeasible). The two returns to unadmitted Cohort-H callers
remain `needs-evidence`; S1 does not claim cross-cohort caller proof.

## S2 admission — fireball enemy scan

S2 admits `FireballEnemyCollision -> ExitFBallEnemy` at `$D6D9-$D735`:
`FireballEnemyCollision`, `FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`,
`NoFToECol`, and `ExitFBallEnemy`. Its shared owner is
`src/game/world/fireball_enemy.c`; S1 is the predecessor and S3 owns the hit
handler called after a positive collision.

The ROM-logic track verifies early returns for zero/high-bit fireball state and
odd frame parity, every descending enemy slot, state/flag/ID eligibility gate,
Goomba defeated-state gate, masked offscreen gate, bounds-box offsets, hit d7
write, ordered hit-child call, and saved fireball-box restoration. The
operational track batches the controlled original-ROM family per width, then
runs the scan and collision regression tests, platform-purity gate and DOS16
shared-source link.

## S2 closure — fireball enemy scan

All six scoped nodes are current-exact: `FireballEnemyCollision`,
`FireballEnemyCDLoop`, `GoombaDie`, `NotGoomba`, `NoFToECol`, and
`ExitFBallEnemy`. Static `$D6D9-$D735` comparison found no shared-C
mismatch. The strengthened scan contract now explicitly covers inactive,
exploding and odd-frame entry exits plus the masked-offscreen path, in addition
to its 131,072 ID/state eligibility cases and child-mutation cases.

The controlled original-ROM caller replay ran the retained 1,024 bounded
records through one x86 and one x64 process, comparing full mapped RAM and
recorded child calls, with zero differences. The focused scan, collision
regression, audio/pause and Win32 audio tests pass on both widths; platform
purity passes and OpenNT links the same shared DOS16 source. Product C did not
change, so the existing three package artifacts were not refreshed.

S2 marks six nodes, 19 source-owned controls (`control-02191` through
`control-02209`) and four material handoffs (`material-00336` through
`material-00339`) exact. `HandleEnemyFBallCol` is deliberately retained for
S3. Current totals: historical **1,992 / 1,992**; current exact nodes
**1,238 / 1,992**; current exact feasible controls **2,495 / 4,324** (raw
**4,342**, infeasible **18**).

## S3 admission — fireball hit response

S3 admits `BowserIdentities -> ExHCF` at `$D736-$D7C3`: `BowserIdentities`,
`HandleEnemyFBallCol`, `ChkBuzzyBeetle`, `HurtBowser`, `SetDBSte`,
`ChkOtherEnemies`, `ShellOrBlockDefeat`, `StnE`, `GoombaPoints`,
`EnemySmackScore` and `ExHCF`. The shared owner is
`src/game/world/fireball_hit.c`; S2 proves the caller scan and S4 begins
hammer contact.

The ROM-logic track compares all eight identity bytes and unmasked source
indexing, duplicate enemy selection, Buzzy/Bowser/immune exits, decrement
wrap and Bowser death transition, Piranha carry-derived vertical adjustment,
stun child input, state masking, Hammer Bro/Goomba score selection and ordered
floating-score/audio writes. The operational track batches retained 512
original-ROM hit records once per x86/x64 width, then runs the focused hit and
scan contracts, platform purity and OpenNT DOS16 link.

## S3 closure — fireball hit response

All 11 scoped nodes are current-exact. Static `$D736-$D7C3` review found no
shared-C difference. The 512 retained controlled original-ROM caller records
replayed with full mapped RAM and recorded child calls in one x86 and one x64
process, each with zero differences. Focused fireball-hit and scan tests pass
on both widths; platform purity passes and OpenNT links the shared DOS16
source. Product C did not change, so package artifacts were not refreshed.

S3 marks 11 nodes, 26 source-owned controls (`control-02210` through
`control-02235`) and six material handoffs (`material-00340` through
`material-00345`) exact. Current totals: historical **1,992 / 1,992**;
current exact nodes **1,249 / 1,992**; current exact feasible controls
**2,521 / 4,324** (raw **4,342**, infeasible **18**).

## S4 admission — hammer-player contact

S4 admits `PlayerHammerCollision -> ExPHC` at `$D7C4-$D7FF`:
`PlayerHammerCollision`, `ClHCol` and `ExPHC`. Its shared owner is
`src/game/world/hammer_collision.c`; S3 is the predecessor and S5 begins
power-up contact. The geometry and guarded-injury callees retain their separate
owners, while this chain proves their caller inputs, result handling and call
order.

The ROM-logic track checks odd-frame polarity, the TimerControl/offscreen OR
gate, byte-wrapped `slot*4+$24` box selection, the live ObjectOffset reload
after `PlayerCollisionCore`, the clear-carry miss latch clear, the set-carry
already-latched exit, the two-complement speed reversal, star guard, and the
ordered injury tail. The operational track replays retained controlled
original-ROM contact records in one x86 and one x64 process, runs the focused
hammer-contact contract, platform-purity gate and OpenNT DOS16 shared-source
link.

### S4 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **1,249 / 1,992**.
- Current exact feasible controls: **2,521 / 4,324**.
- Scope: **3** labels; expected fresh historical matches: **0**; maximum
  historical complete: **1,992 / 1,992**.
- Current-exact promotions are determined only after both audit tracks finish.

## S4 closure — hammer-player contact

All three scoped nodes are current-exact: `PlayerHammerCollision`, `ClHCol`
and `ExPHC`. Static `$D7C4-$D7FF` comparison found no shared-C difference:
frame parity is active only on odd frames; the TimerControl and hammer
offscreen bytes form the source OR gate; the geometry box is `slot*4+$24`;
ObjectOffset is reloaded after geometry; a miss clears its live slot latch; and
a new hit latches, two-complement reverses speed, then uses the post-response
star guard before the injury tail.

The retained controlled original-ROM contact route ran 288 records through one
x86 and one x64 native process, comparing full mapped RAM and recorded geometry
and injury child calls, with zero differences. The strengthened snapshot runner
now accepts a manifest, so each width handles the complete record family in one
process. The focused contact contract, platform purity and OpenNT DOS16 shared
source link pass. Product C did not change, so package artifacts were not
refreshed.

S4 marks three nodes, eight source-owned controls (`control-02236` through
`control-02243`) and three material handoffs (`material-00346`,
`material-00348`, `material-00349`) exact. Current totals: historical
**1,992 / 1,992**; current exact nodes **1,252 / 1,992**; current exact
feasible controls **2,529 / 4,324** (raw **4,342**, infeasible **18**).

## S5 admission — power-up pickup response

S5 admits `HandlePowerUpCollision -> NoPUp` at `$D800-$D84C`:
`HandlePowerUpCollision`, `Shroom_Flower_PUp`, `SetFor1Up`, `UpToSuper`,
`UpToFiery` and `NoPUp`. Its shared owner is
`src/game/world/powerup_collision.c`; S4 is the predecessor and S6 begins
player/enemy contact. Erase, score, palette and routine children retain their
separate owners while this chain proves their inputs, ordering and return paths.

The ROM-logic track compares common erase/score/sound ordering, type carry and
1UP equality dispatch, type three's modifier overwrite, star timer/music
path, status zero/one/other routing, palette call before fiery routine setup,
routine values nine/twelve and the return tails. The operational track replays
retained controlled original-ROM pickup records in one x86 and one x64 process,
then runs the focused pickup contract, platform-purity gate and OpenNT DOS16
shared-source link.

### S5 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **1,252 / 1,992**.
- Current exact feasible controls: **2,529 / 4,324**.
- Scope: **6** labels; expected fresh historical matches: **0**; maximum
  historical complete: **1,992 / 1,992**.
- Current-exact promotions are determined only after both audit tracks finish.

## S5 closure — power-up pickup response

All six scoped nodes are current-exact: `HandlePowerUpCollision`,
`Shroom_Flower_PUp`, `SetFor1Up`, `UpToSuper`, `UpToFiery` and `NoPUp`.
Static `$D800-$D84C` comparison found no shared-C difference in common child
order, type carry/equality paths, the one-up overwrite, star timer/music,
status dispatch, palette call, routine values or return tails.

The retained controlled original-ROM pickup route ran 128 records through one
x86 and one x64 native process, comparing full mapped RAM and recorded erase,
score, palette and routine child calls, with zero differences. The strengthened
snapshot runner now accepts a manifest, so each width handles the complete
record family in one process. The focused pickup contract, platform purity and
OpenNT DOS16 shared-source link pass. Product C did not change, so package
artifacts were not refreshed.

S5 marks six nodes, 11 source-owned controls (`control-02244` through
`control-02254`) and six material handoffs (`material-00350` through
`material-00355`) exact. Current totals: historical **1,992 / 1,992**;
current exact nodes **1,258 / 1,992**; current exact feasible controls
**2,540 / 4,324** (raw **4,342**, infeasible **18**).

## S6 admission — player/enemy collision response

S6 admits the contiguous `$D84D-$DA24` player/enemy collision chain: the 34
source-order labels assigned to S6 in the plan table, from `ResidualXSpdData`
through `ExSFN`. The shared owner is `src/game/world/player_enemy_collision.c`;
S5 is the predecessor and S7 starts enemy/enemy collision. Geometry, power-up,
enemy and palette children retain their own owners while this S audits all
caller-side input, output and ordering contracts.

The ROM-logic track compares data tables, every slot/state/timer predicate,
carry-equivalent collision and injury decisions, routine/death tails, stomp and
shell paths, score controls and child ordering. The operational track batches
retained controlled original-ROM contact records once per x86/x64 process, then
runs the focused contact contract, platform-purity gate and OpenNT DOS16
shared-source link.

### S6 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **1,258 / 1,992**.
- Current exact feasible controls: **2,540 / 4,324**.
- Scope: **34** labels; expected fresh historical matches: **0**; maximum
  historical complete: **1,992 / 1,992**.
- Current-exact promotions are determined only after both audit tracks finish.

## S6 closure — player/enemy collision response

All 34 scoped nodes from `ResidualXSpdData` through `ExSFN` are current-exact. Static `$D84D-$DA24` review confirms table bytes and binding, frame/offscreen/state gates, live-slot reload after geometry, collision latch behavior, power-up and star dispatch, shell score selection, injury/death transitions, stomp/demotion/revival paths, facing and floating-score writes.

The retained controlled original-ROM contact route replayed 1,024 records in one x86 and one x64 native process. Each compared mapped RAM and the recorded geometry, power-up, defeat, palette, stun, vertical-state, direction and routine child calls; both widths reported zero differences. The focused contact contract, platform-purity gate and OpenNT DOS16 shared-source link pass. The audio output and title-pause CTests also pass on both widths, with the owner separately confirming their interactive behavior. Product C did not change, so the three package artifacts were not refreshed.

S6 records 34 nodes, 92 source-address-owned control relations and 28 material handoffs as current-exact. Five edges carrying S6 label names but emitted at other ROM source addresses remain with their owning cohorts and were not claimed here. Current totals: historical **1,992 / 1,992**; current exact nodes **1,292 / 1,992**; current exact feasible controls **2,632 / 4,324** (raw **4,342**, infeasible **18**).

## S7 admission — enemy/enemy collision response

S7 admits the contiguous `$DA25-$DB44` chain from `SetBitsMask` through `ExTA`: `SetBitsMask`, `ClearBitsMask`, `EnemiesCollision`, `ECLoop`, `YesEC`, `NoEnemyCollision`, `ReadyNextEnemy`, `ExitECRoutine`, `ProcEnemyCollisions`, `ShellCollisions`, `ExitProcessEColl`, `ProcSecondEnemyColl`, `MoveEOfs`, `EnemyTurnAround`, `RXSpd`, and `ExTA`. Its shared owner is `src/game/world/enemy_collision.c`; S6 is closed and S8 begins platform collision.

The ROM-logic track checks the two seven-byte masks, frame/water/object/offscreen gates, descending candidate scan and live `$01`/`ObjectOffset` reloads, candidate-first box ordering, hit/miss latches, every shell state/score path and turnaround ID predicates. The retained original-ROM pair-root family covers all 134 instructions and 54 feasible branch outcomes; it will replay once per x86/x64 process with recorded child calls. The operational track runs the pair and collision contracts, platform purity and the OpenNT DOS16 shared-source link.

### S7 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **1,292 / 1,992**.
- Current exact feasible controls: **2,632 / 4,324**.
- Scope: **16** labels; expected fresh historical matches: **0**; maximum historical complete: **1,992 / 1,992**.
- Expected graph scope: **58** source-address-owned feasible controls and **9** material handoffs.

## S7 closure — enemy/enemy collision response

All 16 scoped nodes are current-exact: `SetBitsMask`, `ClearBitsMask`,
`EnemiesCollision`, `ECLoop`, `YesEC`, `NoEnemyCollision`,
`ReadyNextEnemy`, `ExitECRoutine`, `ProcEnemyCollisions`,
`ShellCollisions`, `ExitProcessEColl`, `ProcSecondEnemyColl`, `MoveEOfs`,
`EnemyTurnAround`, `RXSpd`, and `ExTA`. Static `$DA25-$DB44` comparison found
no shared-C difference in pair filtering, geometry ordering, collision latches,
shell response, score paths, or signed turnaround handling.

The retained original-ROM pair route executed all 134 instructions and 54
feasible branch outcomes across 1,024 roots. One x86 and one x64 native batch
replay compared full mapped RAM plus recorded geometry, defeat and score-child
calls with zero differences. The taken exits at `$DB20` and `$DB24` are
unreachable from a valid pair root because prior ID gates reject IDs 13 and 17;
the source condition remains present and full-byte native leaf tests cover it.
Focused pair/collision contracts, platform purity, and the OpenNT DOS16 shared
source link pass. Product C did not change, so no package artifact refresh was
required.

S7 records 16 nodes, 58 source-address-owned feasible controls and nine
material handoffs exact. Current totals: historical **1,992 / 1,992**; current
exact nodes **1,308 / 1,992**; current exact feasible controls **2,690 /
4,324** (raw **4,342**, infeasible **18**).

## S8 admission — platform collision front end

S8 admits the contiguous `$DB45-$DBBA` chain: `LargePlatformCollision`,
`ChkForPlayerC_LargeP`, `ExLPC`, `SmallPlatformCollision`,
`ChkSmallPlatLoop`, `MoveBoundBox`, and `ExSPC`. Its shared owner is
`src/game/enemy/platform_collision.c`; S7 is closed and S9 continues with the
platform collision response children. The ROM-logic track covers timer and
state gates, balance-partner ordering, live `ObjectOffset` reloads, vertical
and offscreen exits, both platform bounding boxes, `$00` counter semantics and
wrapped Y shifts. The operational track uses a batched original-ROM route per
x86/x64 width, focused platform collision tests, purity and DOS16 shared-source
link.

### S8 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **1,308 / 1,992**.
- Current exact feasible controls: **2,690 / 4,324**.
- Scope: **7** labels; expected fresh historical matches: **0**; maximum
  historical complete: **1,992 / 1,992**.
- Expected graph scope: **32** source-address-owned feasible controls and **5**
  material handoffs.

## S8 closure — platform collision front end

All seven scoped nodes are current-exact: `LargePlatformCollision`, `ChkForPlayerC_LargeP`, `ExLPC`, `SmallPlatformCollision`, `ChkSmallPlatLoop`, `MoveBoundBox`, and `ExSPC`. Static `$DB45-$DBBA` comparison found no shared-C difference in timer/state gates, balance partner ordering, live slot reloads, box selection, collision routing or byte-wrapped two-box iteration.

The retained controlled original-ROM platform route covers the containing `$DB45-$DC16` sequence (100 instructions and 38 feasible branch outcomes). Its S8 front-end route replayed against one x86 and one x64 native process with full mapped RAM and child-call comparison, zero differences. Focused platform collision contracts, platform purity and OpenNT DOS16 shared-source link pass. Product C did not change, so package executables were not refreshed.

S8 records seven nodes, 32 source-address-owned feasible controls and five material handoffs exact. Current totals: historical **1,992 / 1,992**; current exact nodes **1,315 / 1,992**; current exact feasible controls **2,722 / 4,324** (raw **4,342**, infeasible **18**).

## S9 admission — platform collision response and player positioning

S9 admits `$DBBC-$DC40`: `ProcSPlatCollisions`, `ProcLPlatCollisions`, `ChkForTopCollision`, `SetCollisionFlag`, `PlatformSideCollisions`, `SideC`, `NoSideC`, `PlayerPosSPlatData`, `PositionPlayerOnS_Plat`, `PositionPlayerOnVPlat`, and `ExPlPos`. It owns the contiguous response and position chain in `platform_collision.c` and `platform_position.c`; S8 is closed and S10 begins collision helper entries. The audit covers all 19 source-address-owned controls and eight material handoffs.

## S9 closure — platform collision response and player positioning

All 11 scoped nodes are current-exact. Static `$DBBC-$DC40` comparison preserves vertical-speed suppression, top/side collision thresholds, small-platform ID flag selection, side-impede ordering, two-byte position table indexing and the shared positioning tail. Retained ROM collision/position routes and focused x86/x64 checks report zero differences; purity and DOS16 link pass. S9 records 11 nodes, 19 controls and eight material handoffs exact. Current totals: historical **1,992 / 1,992**; current **1,326 / 1,992** nodes and **2,741 / 4,324** feasible controls (raw **4,342**, infeasible **18**). Product C did not change.

## S10 admission — player vertical and enemy box offsets

S10 admits `$DC41-$DC54`: `CheckPlayerVertical`, `ExCPV`, `GetEnemyBoundBoxOfs`, and `GetEnemyBoundBoxOfsArg`. Shared owner is `src/game/world/collision.c`; it verifies carry preservation through the high-byte gate, source slot/argument selection, box offset arithmetic and masked offscreen result. Scope: four nodes, four source-address-owned controls and two material handoffs.

## S10 closure — player vertical and enemy box offsets

All four scoped nodes are current-exact. Static `$DC41-$DC54` audit, retained x86/x64 original-ROM caller route, focused platform contract, platform purity and the S9-contiguous DOS16 shared-source link pass. S10 records four nodes, four controls and two material handoffs exact. Current totals: historical **1,992 / 1,992**; current **1,330 / 1,992** nodes and **2,745 / 4,324** feasible controls. Product C did not change.

## S11 admission — player background-collision entry

S11 admits `$DC64-$DC8C`: `PlayerBGUpperExtent`, `PlayerBGCollision`,
`SetFallS`, `SetPSte`, `ChkOnScr`, `ExPBGCol`, `ChkCollSize`, and `GBBAdr`.
The chain is owned by `src/game/player/terrain.c`; S10 is closed and S12 owns
the head/feet/side child chain. It proves the no-collision, routine and
off-screen exits; swimming/falling state selection; collision-bit reset; and
the crouching/small/swimming block-buffer base selection.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,330 / 1,992** nodes and **2,745 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **8** labels, all `needs-evidence`; expected historical matches:
  **0**; maximum historical complete: **1,992 / 1,992**.
- Graph scope: **16** source-address-owned feasible controls; no distinct
  material-handoff row begins in this address interval.

ROM logic evidence uses static source comparison and the retained controlled
`terrain-0` through `terrain-7` PlayerBGCollision roots per x86/x64 width.
Operational evidence runs `mysmb.player-terrain-chain`, platform purity and the
OpenNT DOS16 shared-source link. No product artifact refresh is needed unless
the shared C audit finds and repairs a discrepancy.

## S11 closure — player background-collision entry

All eight scoped nodes are current-exact: `PlayerBGUpperExtent`, `PlayerBGCollision`, `SetFallS`, `SetPSte`, `ChkOnScr`, `ExPBGCol`, `ChkCollSize`, and `GBBAdr`. Static `$DC64-$DC8C` comparison found no shared-C difference: the disable, death-routine and low-routine exits retain their original order; swimming and normal/climbing state selection writes occur before the vertical-high-byte guard; collision bits are reset only on-screen; `$cf` is the bottom exit; and the crouching/small/swimming index selects the original `BlockBufferAdderData` bytes `$00,$07,$0e` before the head child boundary.

The retained controlled original-ROM PlayerBGCollision root route replayed `terrain-0` through `terrain-7` against freshly compiled current x86 and x64 snapshot runners. Each width compared mapped RAM and recorded child-call arguments/returns with **8/8** zero-difference records. Focused `mysmb.player-terrain-chain` and `mysmb.platform-purity` CTests pass on both widths. The immediately preceding focus-pause product change already linked the unchanged shared terrain source through OpenNT DOS16; the reusable CMake configuration was no longer present for a redundant S11 relink. This audit changes no product C, so no package artifact refresh is required.

S11 records eight nodes and 16 source-address-owned feasible controls (`control-02426` through `control-02441`) exact; no material handoff originates in this interval. Current totals: historical **1,992 / 1,992**; current exact nodes **1,338 / 1,992**; current exact feasible controls **2,761 / 4,324** (raw **4,342**, infeasible **18**).

## S12 admission — player terrain child chain

S12 admits `$DC93-$DD5D`: `HeadChk`, `SolidOrClimb`, `NYSpd`, `DoFootCheck`, `AwardTouchedCoin`, `ChkFootMTile`, `ContChk`, `LandPlyr`, `InitSteP`, `DoPlayerSideCheck`, `SideCheckLoop`, `BHalf`, `ExSCH`, and `CheckSideMTiles`. Its shared game owner is `src/game/player/terrain.c`; S11 has closed the root and S13 begins the side-metatile continuation. This bounded chain includes only the caller-side control, RAM and child ABI behavior. Child interiors stay with their admitted owners.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,338 / 1,992** nodes and **2,761 / 4,324** feasible controls (raw **4,342**, infeasible **18**).
- Scope: **14** labels, all `needs-evidence`; expected historical matches: **0**; maximum historical complete: **1,992 / 1,992**.
- Graph scope: **72** source-address-owned feasible controls (`control-02444` through `control-02500`, and `control-03946` through `control-03960`); no material-handoff row originates in this interval.

The ROM-logic track audits the head, feet and side callers against `$DC93-$DD5D`, including guard order, carry-equivalent child results, live scratch-byte effects, relative child call/return order, byte-wrapped offsets, coin/axe/jumpspring handling and terminal exits. The retained controlled `terrain-0` through `terrain-7` PlayerBGCollision roots will replay against freshly compiled current x86/x64 snapshot runners; focused `mysmb.player-terrain-chain` and platform-purity tests provide the operational track. Product artifacts refresh only if a shared-C repair is required.

## S12 closure — player terrain child chain

All 14 scoped nodes are current-exact: `HeadChk`, `SolidOrClimb`, `NYSpd`,
`DoFootCheck`, `AwardTouchedCoin`, `ChkFootMTile`, `ContChk`, `LandPlyr`,
`InitSteP`, `DoPlayerSideCheck`, `SideCheckLoop`, `BHalf`, `ExSCH`, and
`CheckSideMTiles`. The static `$DC93-$DD5D` audit confirms the head, feet and
side caller guards, carry-equivalent child results, scratch-byte ordering,
wrapped offsets and terminal exits. Its 72 source-owned feasible controls
(`control-02444` through `control-02500` and `control-03946` through
`control-03960`) are exact.

The controlled `terrain-0` through `terrain-7` root and child routes ran in
fresh x86 and x64 native processes with full mapped-RAM comparisons and zero
differences. Those child routes exposed a shared dependency mismatch:
`RemoveCoin_Axe` must pass the ROM-loaded `AreaType` X value to
`PutBlockMetatile`, whose first operation stores it to zero-page `$00`.
`mysmb_area_remove_coin_axe` now preserves that byte instead of substituting
zero. The child-route runner also now accumulates failures and returns nonzero,
so a RAM mismatch cannot be misreported as a passing route. This repair does
not credit unadmitted `HandleAxeMetatile` or `ErACM` interiors; S14 retains
their independent ownership and audit.

Focused terrain-chain, terrain-metatile, platform-purity, focus-pause and
audio tests pass for x86 and x64. OpenNT16 rebuilt the same shared source and
produced the DOS executable. Because shared product C changed, all three local
package artifacts were refreshed. Current totals: historical mapping **1,992 /
1,992**; current exact nodes **1,352 / 1,992**; current exact feasible
controls **2,833 / 4,324** (raw **4,342**, infeasible **18**).

## S13 admission — side pipe and movement-stop chain

S13 admits `$DD5E-$DDC1`: `ContSChk`, `ChkPBtm`, `PipeDwnS`, `PlyrPipe`,
`SetCATmr`, `ChkGERtn`, `StopPlayerMove`, `ExCSM`, and
`AreaChangeTimerData`. The shared game owner is `src/game/player/terrain.c`.
S12 supplies the `CheckSideMTiles` predecessor; S14 owns the metatile-child
interiors reached from this caller chain. This chain ends before
`HandleCoinMetatile`.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,352 / 1,992** nodes and **2,833 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **9** labels, all `needs-evidence`; planned current-exact promotions:
  **9**; maximum current exact nodes: **1,361 / 1,992**.
- Graph scope: **28** source-owned feasible controls (`control-02502` through
  `control-02526`, plus `control-03963` through `control-03965`) and one
  material handoff, `material-k50-01` (`AreaChangeTimerData -> SetCATmr`).

The ROM-logic track compares the invisible/climb/coin/jumpspring child-result
paths; normal-state and facing gates; the `6c` and `1f` pipe choices; the
first-only pipe sound write; attributes, low-nibble and screen-page timer
paths; engine-subroutine transition; and the impeded-movement tail. The
controlled `terrain-0` through `terrain-7` roots and child manifests provide
the original-ROM route baseline in freshly compiled x86/x64 processes.
Operational proof runs terrain, collision and platform-purity tests, cross-width
builds and the OpenNT16 shared-source link. Product artifacts refresh only if
shared product C changes.
## S13 closure — side pipe and movement-stop chain

All nine scoped labels are current-exact: `ContSChk`, `ChkPBtm`, `PipeDwnS`,
`PlyrPipe`, `SetCATmr`, `ChkGERtn`, `StopPlayerMove`, `ExCSM`, and
`AreaChangeTimerData`. Static comparison of `$DD5E-$DDC1` confirms the
invisible/climb/coin/jumpspring result order; normal-state/right-facing gates;
both pipe metatiles; first-only pipe sound; priority-bit write; low-nibble and
page-selected timer table read; engine-routine `8 -> 2` transition; and the
movement-stop return. The initial review question around the upper climbing
probe was resolved against an actual ROM route: its carry path must continue to
the second half probe, which is exactly the existing shared-C filter behavior;
no product logic change was needed.

Eleven fresh controlled original-ROM PlayerBGCollision routes covered invisible,
coin, jumpspring, ordinary wall and seven pipe combinations. Fresh x86 and x64
caller runners compared full mapped RAM plus recorded child calls/returns for
**22** executions with zero differences. The seven pipe routes include both
`$1f`/`$6c`, zero/nonzero X low nibble, both screen-page timer values,
pre-set/clear attributes, engine routine 7/8, and left/right-facing paths.
The four side routes exercise the terminal non-pipe paths. Focused terrain,
collision-regression, pipe-entry and platform-purity CTests pass on both
widths.

The registry records all nine nodes, 28 source-owned feasible controls
(`control-02502` through `control-02526`, `control-03963` through
`control-03965`) and `material-k50-01` as exact. This is an audit-only P: no
shared product C changed, so the three packaged EXEs remain the tested S12
artifacts and are intentionally not refreshed. Current totals: historical
mapping **1,992 / 1,992**; current exact nodes **1,361 / 1,992**; current
exact feasible controls **2,861 / 4,324** (raw **4,342**, infeasible **18**).

## S14 admission — coin, axe and flagpole climbing chain

S14 admits `$DDC3-$DE5C`: `HandleCoinMetatile`, `HandleAxeMetatile`, `ErACM`,
`ClimbXPosAdder`, `ClimbPLocAdder`, `FlagpoleYPosData`, `HandleClimbing`,
`ExHC`, `ChkForFlagpole`, `FlagpoleCollision`, `ChkFlagpoleYPosLoop`, and
`MtchF`. Shared owners are `src/game/player/terrain_metatiles.c` and
`src/game/player/climbing.c`. S13 supplies the side-metatile caller;
`VineCollision -> PutPlayerOnVine` and its internal tail begin in S15.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,361 / 1,992** nodes and **2,861 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **12** labels, all `needs-evidence`; historical expected matches:
  **0**; maximum historical complete **1,992 / 1,992**.
- Graph scope: **20** source-owned feasible controls (`control-02527` through
  `control-02544`, `control-03966`, `control-03967`) and three material
  handoffs: `material-k51-01` through `material-k51-03`.

The ROM-logic track checks the erase/tally/coin call order; axe mode and speed
stores; all nine table bytes; climbing's nibble boundaries; flagpole versus
vine selection; flagpole state/sound/enemy-clear ordering; all five score
thresholds; and the exact run/return handoffs. The operational track runs
current x86/x64 route records and focused terrain-metatile, climbing and
platform-purity tests. Product artifacts refresh only if shared product C
changes.

## S14 closure — coin, axe and flagpole climbing chain

All twelve scoped labels are current-exact: `HandleCoinMetatile`,
`HandleAxeMetatile`, `ErACM`, `ClimbXPosAdder`, `ClimbPLocAdder`,
`FlagpoleYPosData`, `HandleClimbing`, `ExHC`, `ChkForFlagpole`,
`FlagpoleCollision`, `ChkFlagpoleYPosLoop`, and `MtchF`.

The static audit maps the two coin/axe entries through their common erase
tail, including the post-child coin-tally increment and the axe task/mode/
speed stores. It binds all nine adjacent climbing-table bytes, the two
contact-nibble exits, both flagpole metatiles, the vine successor edge,
engine-four/five gates, `KillEnemies($33)` call/return, and all five descending
flagpole-score thresholds. The 20 scoped feasible controls are exact; one
(`control-02530`) was already exact before this S, so 19 newly receive current
evidence. Material relations `material-k51-01`, `material-k51-02` and
`material-k51-03` are exact.

Controlled original-ROM routes use coin and axe roots plus climbing fixtures
for `$24`, `$25`, the non-flagpole vine handoff, engines 4 and 5, and player-Y
values crossing `$18`, `$22`, `$50`, `$68` and `$90`. Current x86 and x64
caller checkers replay every captured parent state and inject each recorded
child return only after comparing its full input RAM; all comparisons have
zero differences. The independent x86/x64 `climbing` smoke covers 515 cases;
`terrain-metatile` covers 6,144; platform purity passes. No product C changed,
so artifact refresh is not applicable.

Historical conformance remains **1,992 / 1,992**. Current exact totals are
**1,373 / 1,992 nodes** and **2,880 / 4,324 feasible controls** (raw
**4,342**, infeasible **18**); exact material relations are **356 / 487**.

## S15 admission — climbing tail and metatile predicates

S15 admits `$DE5D-$DEA6`: `RunFR`, `VineCollision`, `PutPlayerOnVine`,
`SetVXPl`, `ExPVne`, `ChkInvisibleMTiles`, `ExCInvT`, `ChkForLandJumpSpring`,
`ExCJSp`, and `ChkJumpspringMetatiles`. The shared owners are
`src/game/player/climbing.c` and `src/game/player/terrain_metatiles.c`.
S14 supplies the flagpole predecessor and its already-exact two table handoffs;
S16 begins the `JSFnd` / `NoJSFnd` return pair.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,373 / 1,992** nodes and **2,880 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **10** labels, all `needs-evidence`; historical expected matches:
  **0**; maximum historical complete **1,992 / 1,992**.
- Graph scope: **14** source-owned feasible controls (`control-02545` through
  `control-02557`, `control-03968`). `material-k51-01` and
  `material-k51-02` are incoming exact producer-to-consumer handoffs.

The ROM-logic track covers `RunFR`'s engine store and tail transfer;
metatile-`$26` automatic-climb gating; state, speed, wrapped relative-X and
page-adjust ordering in common vine placement; both invisible metatiles; and
the two jumpspring metatiles and their no-match return. The operational track
uses controlled original-ROM climbing and predicate routes with current x86/x64
callers, then focused climbing, hidden-spring and platform-purity tests.
Product artifacts refresh only if shared product C changes.


## S15 closure — climbing tail and metatile predicates

All ten scoped labels are current-exact: RunFR, VineCollision, PutPlayerOnVine,
SetVXPl, ExPVne, ChkInvisibleMTiles, ExCInvT, ChkForLandJumpSpring, ExCJSp,
and ChkJumpspringMetatiles. Static $DE5D-$DEA6 comparison preserves the
engine-four tail transfer; vine $26 and player-Y $20 gates; state, speed,
wrapped relative-X and page ordering; both hidden metatiles; and the $67/$68
spring predicate and four activation writes.

Current x86/x64 climbing callers replayed controlled original-ROM automatic-vine
and page-adjust routes with full mapped RAM and child-call comparison, zero
differences. Freshly compiled current x86/x64 predicate checkers then replayed
all 177 retained source-reachable original-ROM predicate records (354
width-runs), including original Z/C flag contracts and full mapped RAM, with
zero differences. Focused climbing (515 cases), hidden/spring (256 predicate
inputs x 1,024 RAM cases) and platform-purity checks pass. No product C
changed, so packaged executables were not refreshed.

The registry records ten nodes and 14 source-owned feasible controls
(control-02545 through control-02557, control-03968) exact. Historical
conformance remains 1,992 / 1,992; current exact totals are 1,383 / 1,992
nodes and 2,894 / 4,324 feasible controls (raw 4,342, infeasible 18);
exact material relations remain 356 / 487.

## S16 admission — jumpspring terminal return pair

S16 admits $DEE6-$DEE7: JSFnd and NoJSFnd, the terminal carry-set and
carry-clear returns of ChkJumpspringMetatiles. Its shared owner is
src/game/player/terrain_metatiles.c; S15 supplies the already-exact predicate
entry and S17 begins pipe entry. The ROM-logic track compares both return
flags, input preservation and all callers consuming carry. The operational
track reuses the source-reachable predicate manifest with current x86/x64
checkers, focused hidden-spring test, platform purity and the OpenNT DOS16
shared-source link.

- Historical mapping: 1,992 / 1,992.
- Incoming current exact: 1,383 / 1,992 nodes and 2,894 / 4,324 feasible
  controls (raw 4,342, infeasible 18).
- Scope: 2 labels; historical expected matches: 0; maximum historical complete
  1,992 / 1,992.
- Graph scope: 4 source-owned feasible controls (control-02558 through
  control-02561).


## S16 closure — jumpspring terminal return pair

Both scoped labels, JSFnd and NoJSFnd, are current-exact. Static $DEE6-$DEE7
comparison confirms the carry-set matched return, the carry-clear unmatched
return and the absence of input/RAM writes. The same freshly compiled x86/x64
predicate checkers replayed all 177 source-reachable original-ROM records with
zero differences. Hidden-spring and platform-purity checks pass. No product C
changed, so executable artifacts were not refreshed.

The four terminal controls (control-02558 through control-02561) are exact.
Historical conformance remains 1,992 / 1,992; current exact totals are 1,385 /
1,992 nodes and 2,898 / 4,324 feasible controls (raw 4,342, infeasible 18).

## S17 admission — pipe entry and movement impedance

S17 admits $DEE8-$DF8A: HandlePipeEntry, GetWNum, ExPipeE,
ImpedePlayerMove, RImpd, NXSpd, PlatF and ExIPM. Shared owners are
src/game/player/pipe_entry.c and src/game/player/impede.c. S16 supplies the
jumpspring return; S18 begins world metatile predicates. ROM logic covers all
pipe gates, raw table index arithmetic, transition writes, signed collision
response, coordinate carry and collision-mask tail. The operational track uses
controlled original-ROM pipe/impede routes per x86/x64 width, focused pipe and
collision tests, platform purity and the OpenNT DOS16 shared-source link.

- Historical mapping: 1,992 / 1,992.
- Incoming current exact: 1,385 / 1,992 nodes and 2,898 / 4,324 feasible
  controls (raw 4,342, infeasible 18).
- Scope: 8 labels; historical expected matches: 0; maximum historical complete
  1,992 / 1,992.
- Graph scope: 19 source-owned feasible controls (control-02562 through
  control-02577, control-03945, control-03957 and control-03965).

## S17 closure — pipe entry and movement impedance

All eight scoped labels are current-exact. Static `$DEE8-$DF8A` comparison
confirms Down/right/left pipe gating, entry-store order, raw warp-table index
semantics, both X-region boundaries, signed collision-side speed predicates,
position carry/page arithmetic, and the collision-mask tail. Controlled original
ROM routes directly reached each owner: 512 pipe-entry records and 1,024
movement-impedance records replayed through freshly compiled current x86 and
x64 owners with zero differences across all mapped 2KB RAM bytes. Focused
pipe-entry, impedance and platform-purity tests pass on both widths. No product
C changed, so the executable artifacts were not refreshed.

The 16 newly audited source-owned feasible controls
`control-02562` through `control-02577` are exact. The three cross-chain
return controls (`control-03945`, `control-03957`, `control-03965`) were
already exact and remain so. Historical conformance remains **1,992 / 1,992**;
current exact totals are **1,393 / 1,992** nodes and **2,914 / 4,324** feasible
controls (raw **4,342**, infeasible **18**).

## S18 admission — world metatile predicates

S18 admits `$DF8C-$DFAF`: SolidMTileUpperExt, CheckForSolidMTiles,
ClimbMTileUpperExt, CheckForClimbMTiles, CheckForCoinMTiles, CoinSd,
GetMTileAttrib and ExEBG. The shared owner is `src/game/world/metatiles.c`.
S17 supplies the pipe/impede tail; S19 begins enemy background collision. The
ROM-logic track checks table selection from the two metatile high bits, carry
semantics, coin sound write and terminal return. The operational track uses
controlled original-ROM metatile routes per x86/x64 width, focused
classification checks, platform-purity and the shared-source DOS16 link.

- Historical mapping: 1,992 / 1,992.
- Incoming current exact: 1,393 / 1,992 nodes and 2,914 / 4,324 feasible
  controls (raw 4,342, infeasible 18).
- Scope: 8 labels; historical expected matches: 0; maximum historical complete
  1,992 / 1,992.

## S18 closure — world metatile predicates

All eight scoped labels are current-exact. Static `$DF8B-$DFB8` comparison
confirms original solid/climb threshold binding by high-bit group, shared
attribute extraction, carry semantics, ordered C2/C3 coin checks, the coin
sound queue store and terminal return. Controlled original-ROM parent routes
yielded 5,050 naturally reached classifier calls: DF8F 257, DF9A 1,407,
DFA1 1,722 and DFB0 1,664. Freshly compiled current x86/x64 owners matched
every call register contract and mapped RAM with zero differences. Complete
predicate-domain and platform-purity checks pass on both widths. No product C
changed, so executable artifacts were not refreshed.

The eight internal controls `control-02578` through `control-02582`,
`control-03962`, `control-03969` and `control-03970` are exact. Historical
conformance remains **1,992 / 1,992**; current exact totals are **1,401 /
1,992** nodes and **2,922 / 4,324** feasible controls (raw **4,342**,
infeasible **18**).

## S19 admission — enemy background collision and landing state

S19 admits `$DFC0-$E07A`: EnemyBGCStateData, EnemyBGCXSpdData,
EnemyToBGCollisionDet, DoIDCheckBGColl, HBChk, CInvu, YesIn,
NoEToBGCollision, HandleEToBGCollision, GiveOEPoints, ChkToStunEnemies,
Demote, SetStun, SetWYSpd, SetNotW, ChkBBill, NoCDirF, ExEBGChk,
LandEnemyProperly, SChkA, ChkLandedEnemyState, SetForStn, ExSteChk,
ProcEnemyDirection, InvtD, CNwCDir, LandEnemyInitState, NMovShellFallBit,
ChkForRedKoopa, Chk2MSBSt, GetSteFromD and SetD6Ste. The shared owner is
`src/game/enemy/background.c`. S18 supplies classifier returns; S20 begins
enemy side collision. ROM logic covers state and ID dispatch, ground contact,
block effects, stun/demotion, landing and direction state. The operational
track uses controlled original-ROM enemy-background routes per x86/x64 width,
focused background/landing checks, platform purity and the shared-source DOS16
link.

- Historical mapping: 1,992 / 1,992.
- Incoming current exact: 1,401 / 1,992 nodes and 2,922 / 4,324 feasible
  controls (raw 4,342, infeasible 18).
- Scope: 32 labels; historical expected matches: 0; maximum historical complete
  1,992 / 1,992.

## S19 closure — enemy background collision and landing state

All 32 scoped labels are current-exact: `EnemyBGCStateData`,
`EnemyBGCXSpdData`, `EnemyToBGCollisionDet`, `DoIDCheckBGColl`, `HBChk`,
`CInvu`, `YesIn`, `NoEToBGCollision`, `HandleEToBGCollision`,
`GiveOEPoints`, `ChkToStunEnemies`, `Demote`, `SetStun`, `SetWYSpd`,
`SetNotW`, `ChkBBill`, `NoCDirF`, `ExEBGChk`, `LandEnemyProperly`, `SChkA`,
`ChkLandedEnemyState`, `SetForStn`, `ExSteChk`, `ProcEnemyDirection`,
`InvtD`, `CNwCDir`, `LandEnemyInitState`, `NMovShellFallBit`,
`ChkForRedKoopa`, `Chk2MSBSt`, `GetSteFromD`, and `SetD6Ste`.

Static `$DFC0-$E07A` comparison confirms the state/Y and Spiny gates, jump and
Hammer dispatch, under-enemy query outcome, `$23` erase/score/demotion/stun
sequence, both original tables, water/Bloober vertical speed selection, bullet
direction exceptions, every landing-nibble/state branch, Spiny timing, player
facing decision, shell falling-bit handling and red-koopa transition. The
chain contains 80 source-owned feasible control relations; all are exact. Its
two material table handoffs are exact.

A fresh controlled original-ROM capture produced 1,643 naturally reached
background roots and 549 natural landing entries. Freshly compiled x86 and x64
checkers ran 2,192 comparisons each with zero differences in mapped RAM and
recorded child-call sequence. Focused background caller, stun, landing and
platform-purity CTests pass on both widths. No product C changed, so product
EXEs were intentionally not refreshed.

Current totals: historical mapping **1,992 / 1,992**; current exact nodes
**1,433 / 1,992**; current exact feasible controls **3,000 / 4,324** (raw
**4,342**, infeasible **18**); exact material relations **358 / 487**.

## S20 admission — enemy side collision loop

S20 admits `$E0FE-$E123`: `DoEnemySideCheck`, `SdeCLoop`, `NextSdeC` and
`ExESdeC`. Its shared owner is `src/game/enemy/side_collision.c`; S19 provides
the landing-side transfer and S21 begins the bump path. The ROM logic track
will compare status-bar gate, moving-direction iteration, two horizontal
probe coordinates, non-solid result and terminal return. The operational track
uses controlled original-ROM side-collision routes per x86/x64 width, focused
side-caller and jump/hammer checks, platform purity and the shared-source DOS16
link. Product artifacts refresh only if shared product C changes.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,433 / 1,992** nodes and **3,000 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **4** labels; expected historical matches: **0**; maximum historical
  complete **1,992 / 1,992**.


## S20 closure — enemy side collision loop

All four scoped labels are current-exact: `DoEnemySideCheck`, `SdeCLoop`,
`NextSdeC` and `ExESdeC`. The corrected original span is `$E0FE-$E123`
(the prior `$E0B0-$E0D7` admission text was a documentation address error;
the labels and ownership were always correct). Static comparison confirms the
status-bar return, `$eb` initial value/decrement and child-visible tail state,
direction-selected `$16/$17` horizontal probes, zero result bypass, non-solid
fallthrough, solid bump tail, and two-pass terminal return.

The controlled original-ROM verifier reached all four side labels in 33
original boundaries and checked 66 x86/x64 comparisons over 1,782 persistent
bytes. It covers both outcomes of the side body branches at `$E102`, `$E10E`,
`$E115` and `$E11A`. Fresh x86/x64 `mysmb.enemy-side-caller`,
`mysmb.enemy-side-jump-hammer-chain` and `mysmb.platform-purity` tests pass.
No product C changed, so the three product EXEs are intentionally unchanged.

Current totals: historical mapping **1,992 / 1,992**; current exact nodes
**1,437 / 1,992**; current exact feasible controls **3,010 / 4,324** (raw
**4,342**, infeasible **18**); exact material relations **358 / 487**.


## S21 admission — bump and Hammer Bro response entry

S21 admits `$E124-$E131`: `ChkForBump_HammerBroJ` and `NoBump`. This is an
audit-only continuation, preserving historical custody at M2 T43 S10 while
current-equivalence evidence is refreshed. It starts at the S20 solid-bump
handoff and stops before `InvEnemyDir` in S22. The shared owner is
`src/game/objects.c:mysmb_objects_bump_enemy`. The ROM logic track compares
slot-five sound suppression, state-bit-7 sound gate, Hammer Bro ID fork and
the `$00`/Y handoff. The operational track uses controlled original-ROM
bump/Hammer routes, current x86/x64 tests, platform purity and the shared
DOS16 link. No product artifact refresh is due unless shared product C changes.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,437 / 1,992** nodes and **3,010 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **2** labels; expected historical matches: **0**; maximum historical
  complete **1,992 / 1,992**.


## S21 closure — bump and Hammer Bro response entry

Both scoped labels are current-exact: `ChkForBump_HammerBroJ` and `NoBump`.
Static `$E124-$E131` comparison confirms that slot five bypasses the sound
write, state bit 7 alone enables `Sfx_Bump`, and the Hammer Bro fork clears
`$00`, loads Y with `$FA`, and jumps to the separately owned `SetHJ` entry.
The ordinary ID path reaches the separately owned `InvEnemyDir` tail.

The project-owned controlled ROM probe records five `$E124` entries after reset:
slot-five BEQ, state-clear BCC, sound-write fallthrough, ordinary BNE to the
`RXSpd` return sentinel, and both Hammer variants at the original `$CA37`
`SetHJ` boundary. The x86 and x64 current checkers replay all five with zero
differences. Focused jump/Hammer, terrain-state, and platform-purity CTests
pass on both widths. The existing OpenNT DOS16 shared-source configuration is
currently blocked by an unrelated pre-existing `enemy/movement.h` compiler EOF
failure; no product C changed in this S, and no package EXE refresh is due.

S21 records `ChkForBump_HammerBroJ`, `NoBump`, and five source-owned feasible
controls (`control-02669` through `control-02673`) exact. Current totals:
historical mapping **1,992 / 1,992**; current exact nodes **1,439 / 1,992**;
current exact feasible controls **3,015 / 4,324** (raw **4,342**, infeasible
**18**); exact material relations **358 / 487**.

## S22 admission — enemy direction inversion tail

S22 admits `$E132-$E140`: `InvEnemyDir`. It is the one-instruction ROM tail
from the ordinary `NoBump` path to the separately owned `RXSpd` routine. Its
shared owner is `src/game/objects.c:mysmb_objects_bump_enemy`. The ROM logic
track compares the original tail jump and its preceding signed X-speed/direction
state; the operational track reuses the controlled ordinary-bump route, current
x86/x64 checker, focused jump/Hammer test and platform-purity checks. This is
audit-only work: no product artifact refresh is due unless product C changes.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,439 / 1,992** nodes and **3,015 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **1** label (`InvEnemyDir`); expected historical matches: **0**;
  maximum historical complete **1,992 / 1,992**.

## S22 closure — enemy direction inversion tail

`InvEnemyDir` is current-exact. The original instruction at `$E140` is the
unconditional `jmp RXSpd`. The ordinary branch of
`mysmb_objects_bump_enemy` is its shared C counterpart: it writes the two's
complement of `Enemy_X_Speed` and XORs `Enemy_MovingDir` with 3, exactly as
the separately owned `RXSpd` body does. No source discrepancy was found.

The controlled original-ROM bump records include the ordinary route to the
real `RXSpd` return sentinel. Current x86 and x64 replays compare the sound
queue, X speed and direction with zero differences. Focused enemy-side/jump/
Hammer, terrain-state and platform-purity CTests pass on both widths. No
product C changed, so no product EXE refresh is due.

S22 records `InvEnemyDir` and `control-02674` exact. Current totals:
historical mapping **1,992 / 1,992**; current exact nodes **1,440 / 1,992**;
current exact feasible controls **3,016 / 4,324** (raw **4,342**, infeasible
**18**); exact material relations **358 / 487**.

## S23 admission — player/enemy horizontal difference

S23 admits `$E143-$E14A`: `PlayerEnemyDiff`. The single shared owner is
`src/game/enemy/distance.c:mysmb_enemy_player_difference`; all return edges
remain with their individual callers. The ROM logic track checks `$00` low-byte
subtraction and its borrow into the page return. The operational track uses a
controlled four-case original-ROM entry probe covering borrow, no-borrow and
page wrap, then replays it on x86/x64. No product artifact refresh is due
unless product C changes.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,440 / 1,992** nodes and **3,016 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **1** label (`PlayerEnemyDiff`); expected historical matches: **0**;
  maximum historical complete **1,992 / 1,992**.

## S23 closure — player/enemy horizontal difference

`PlayerEnemyDiff` is current-exact. Static comparison confirms the exact ROM
order: low X subtraction is saved in `$00`, and the resulting borrow is then
subtracted from the page difference. The C owner uses the same unsigned-byte
predicate and arithmetic order, so both wrapping bytes and returned sign match.

Four controlled original-ROM entries cover low-byte borrow, no-borrow and two
page-wrap cases. Fresh x86/x64 checks compare returned A and `$00` with zero
differences; focused enemy-side/jump/Hammer, terrain-state and platform-purity
CTests pass on both widths. No product C changed, so no product EXE refresh is
due.

S23 records `PlayerEnemyDiff` exact. Its caller return edges retain their
source-owned audits. Current totals: historical mapping **1,992 / 1,992**;
current exact nodes **1,441 / 1,992**; current exact feasible controls
**3,016 / 4,324** (raw **4,342**, infeasible **18**); exact material relations
**358 / 487**.

## S24 admission and closure — EnemyLanding

S24 admits $E14F-: EnemyLanding, owned by src/game/world/collision.c:mysmb_world_land_enemy; control-02675 is its InitVStf call. Static comparison shows the shared C implementation clears vertical speed and force before setting Y to its high nibble plus 8. Two controlled original-ROM landing entries with distinct Y low nibbles replay with zero x86/x64 differences in those outputs. Focused chain, terrain-state and platform-purity CTests pass. No product C changed, so no EXE refresh is due.

S24 records EnemyLanding and control-02675 exact. Current totals: historical **1,992 / 1,992**; current exact nodes **1,442 / 1,992**; current exact feasible controls **3,017 / 4,324** (raw **4,342**, infeasible **18**).

## S25 admission — jumping enemy terrain chain

S25 admits `$E15B-$E182`: `SubtEnemyYPos`, `EnemyJump`, and `DoSide`, owned by `src/game/enemy/jump_terrain.c:mysmb_objects_step_enemy_jump_terrain`. S24 supplies the landing child; S26 begins Hammer Bro terrain. The ROM logic track proves the wrapped `Y+$3e` compare, both early DoSide branches, ordered under/non-solid/landing calls, `$fd` speed assignment and unconditional side tail. The operational track replays controlled original-ROM chain entries on x86/x64, then runs focused terrain-chain and purity checks. Product artifacts refresh only if shared product C changes.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,442 / 1,992** nodes and **3,017 / 4,324** feasible controls (raw **4,342**, infeasible **18**).
- Scope: **3** labels; expected historical matches: **0**; maximum historical complete **1,992 / 1,992**.

## S25 closure — jumping enemy terrain chain

All three scoped labels are current-exact: `SubtEnemyYPos`, `EnemyJump` and `DoSide`. Static `$E15B-$E182` comparison confirms wrapped `Y+$3e` carry gating, the signed-speed threshold, ordered `ChkUnderEnemy`/`ChkForNonSolids`/`EnemyLanding` calls, post-landing `$fd` write and unconditional `DoEnemySideCheck` tail. Four controlled original-ROM `$E163` entries cover the Y-tail, speed-tail, empty-ground and solid-landing paths; current x86 and x64 owner replays have zero non-stack RAM differences. Focused landing/jump/Hammer and platform-purity tests pass on both widths. No product C changed, so package EXEs are intentionally unchanged.

S25 records nodes `SubtEnemyYPos`, `EnemyJump`, `DoSide`, and source-owned feasible controls `control-02676` through `control-02685` exact. Current totals: historical **1,992 / 1,992**; current exact nodes **1,445 / 1,992**; current exact feasible controls **3,027 / 4,324** (raw **4,342**, infeasible **18**).

## S26 admission — Hammer Bro terrain entry

S26 admits `$E185-$E18A` `HammerBroBGColl`, owned by `src/game/objects.c:mysmb_objects_step_hammer_terrain`. S25 supplies the preceding jumping-enemy tail; S27 owns the blank-metatile fallthrough. Static audit found caller-owned state/Y guards duplicated in this direct C entry, although the ROM begins with `ChkUnderEnemy`. The ROM logic track proves that direct query and its empty, `$23` and other-tile targets. The operational track replays controlled direct entries on x86/x64, focused chains and platform purity; product C changes require all three EXE artifacts.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,445 / 1,992** nodes and **3,027 / 4,324** feasible controls (raw **4,342**, infeasible **18**).
- Scope: **1** label; expected historical matches: **0**; maximum historical complete **1,992 / 1,992**.


## S26 closure — Hammer Bro terrain entry

`HammerBroBGColl` is current-exact. The original direct entry `$E185` begins with
`ChkUnderEnemy`; shared C now does likewise, with the caller-only state/Y guards
remaining solely in `EnemyToBGCollisionDet`. Four controlled original-ROM direct
entries cover inherited state/Y, empty terrain, blank `$23`, and a solid landing
path. Current x86 and x64 replay all four with zero non-stack RAM differences.
Focused terrain/purity checks, Win32 x86/x64 product self-tests and the existing
OpenNT DOS16 build complete successfully. Because shared product C changed,
`assets/mysmb16.exe`, `assets/mysmb32.exe` and `assets/mysmb64.exe` were rebuilt.

S26 records `HammerBroBGColl` and `control-02686` through `control-02689` exact.
This closure also reconciles the previously closed S21-S25 registry entries, so
current totals are historical **1,992 / 1,992**; current exact nodes **1,446 /
1,992**; current exact feasible controls **3,031 / 4,324** (raw **4,342**,
infeasible **18**).


## S27 admission — bumped-block enemy defeat tail

S27 admits `$E18B-$E18F` `KillEnemyAboveBlock`, owned by
`src/game/objects.c:mysmb_objects_kill_enemy_above_block`. S26 supplies the
blank-metatile fallthrough and S28 resumes Hammer Bro ground handling. The
ROM-logic track checks the ordered `ShellOrBlockDefeat` call, its return, then
the `$FC` `Enemy_Y_Speed` write and return to each original caller. The
operational track records controlled original-ROM direct entries and replays
them through x86/x64 current owners, then runs the focused defeat/terrain and
platform-purity checks plus the existing OpenNT DOS16 shared-source build.
Product artifacts refresh only if shared product C changes.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,446 / 1,992** nodes and **3,031 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: **1** label (`KillEnemyAboveBlock`); expected current matches: **1**;
  maximum current exact: **1,447 / 1,992**.


## S27 closure — bumped-block enemy defeat tail

`KillEnemyAboveBlock` is current-exact. Static `$E18B-$E18F` comparison
confirms the `ShellOrBlockDefeat` call and return precede the `$FC` enemy-Y-speed
write, with no caller predicate copied into the leaf. Four controlled original-ROM
direct entries cover Goomba, Hammer Bro, Piranha ADC-carry and high-state-mask
paths; current x86/x64 full persistent-RAM replays have zero differences.
Focused terrain-chain and platform-purity CTests pass on both widths. No product
C changed, so package EXEs remain those from S26.

S27 records `KillEnemyAboveBlock`, `control-02690` and `control-03989` exact.
The caller-owned return `control-03974` remains for its caller integration audit.
Current totals: historical **1,992 / 1,992**; current exact nodes **1,447 /
1,992**; current exact feasible controls **3,033 / 4,324** (raw **4,342**,
infeasible **18**).


## S28 admission — Hammer Bro ground/no-ground state chain

S28 admits `$E191-$E19A`: `UnderHammerBro` and `NoUnderHammerBro`, both owned
by `src/game/objects.c:mysmb_objects_step_hammer_terrain`. S27 supplies the
blank-block tail; S29 owns the ground-query leaf. The ROM track verifies timer
fallthrough/branch, `$88` state mask, landing call/return, side-check tail and
the no-ground state-d0 write. It extends the controlled Hammer direct route
with the nonzero-timer path and replays it on x86/x64; focused terrain/purity
checks and the OpenNT DOS16 shared-source build complete the operational track.

- Incoming current exact: **1,447 / 1,992** nodes and **3,033 / 4,324** feasible controls.
- Scope: `UnderHammerBro`, `NoUnderHammerBro`; expected current matches: **2**; maximum **1,449 / 1,992**.


## S28 closure — Hammer Bro ground/no-ground state chain

`UnderHammerBro` and `NoUnderHammerBro` are current-exact. Static `$E191-$E19A`
comparison confirms the timer branch, `$88` state mask, ordered landing call and
side-check tail, and state-d0 no-ground return. Five controlled original-ROM
HammerBroBGColl records cover no ground, blank tile, timer-expired solid landing
and timer-nonzero solid ground; x86/x64 full persistent-RAM replays have zero
differences. Focused terrain-chain and platform-purity CTests pass. The registry
now maps both nodes to their actual shared owner, `src/game/objects.c`.

S28 records `UnderHammerBro`, `NoUnderHammerBro`, `control-02691` through
`control-02693`, and `control-03990` exact. Current totals: historical **1,992 /
1,992**; current exact nodes **1,449 / 1,992**; current exact feasible controls
**3,037 / 4,324** (raw **4,342**, infeasible **18**).
