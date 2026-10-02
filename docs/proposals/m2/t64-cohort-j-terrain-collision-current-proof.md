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

## S29 admission — enemy under-block query

S29 admits `ChkUnderEnemy` at `$E1AE-$E1B4`, owned by
`src/game/world/block_buffer.c:mysmb_world_query_enemy_under`. It sets A to
zero and Y to `$15`, then tail-jumps to `BlockBufferChk_Enemy`; S30 starts at
`ChkForNonSolids`. The ROM track compares both setup immediates, the tail
relation and the returned metatile/scratch contract over empty, solid,
page-carry and row cases. The operational track runs the controlled
original-ROM entry once per x86/x64 checker, focused ground-query and purity
tests, and the shared DOS16 link.

- Incoming current exact: **1,449 / 1,992** nodes and **3,037 / 4,324** feasible controls.
- Scope: `ChkUnderEnemy`; expected current matches: **1**; maximum **1,450 / 1,992**.

## S29 closure — enemy under-block query

`ChkUnderEnemy` is current-exact. Static `$E1AE-$E1B4` comparison confirms
`LDA #$00`, `LDY #$15`, and the unconditional tail jump into
`BlockBufferChk_Enemy`. The prior C wrapper normalized that callee's returned
metatile to a boolean; it now preserves the direct ROM result while existing
callers retain their zero/nonzero tests. Five controlled original-ROM entries
cover empty, solid, page-carry and row variants. Their x86/x64 checks agree on
the returned metatile and scratch `$02/$04/$06/$07` with zero differences.

S29 marks `ChkUnderEnemy` and `control-02694` exact. Similar-query review
found the shared generic helper intentionally returns an availability boolean
for its separate API, while this direct tail wrapper alone requires the raw A
result. Focused ground-query, focus-pause, audio-renderer and platform-purity
CTests pass on x86/x64; OpenNT links the DOS16 product. Product C changed, so
all three package artifacts were refreshed.

Current totals: historical **1,992 / 1,992**; current exact nodes **1,450 /
1,992**; current exact feasible controls **3,038 / 4,324** (raw **4,342**,
infeasible **18**).

## S30 admission — non-solid metatile predicate

S30 admits `ChkForNonSolids -> NSFnd` at `$E1B5-$E1C6`, owned by
`src/game/world/metatiles.c:mysmb_world_enemy_metatile_is_non_solid`. S29 is
the predecessor; S31 begins fireball background collision. The ROM track
checks the ordered `$26,$c2,$c3,$5f,$60` comparisons, the four equality
branches, final `$60` fallthrough and Z equality result. The operational track
uses a direct original-ROM route covering all five matches and three
non-matches, x86/x64 predicate checks, focused CTests, purity and DOS16 link.

- Incoming current exact: **1,450 / 1,992** nodes and **3,038 / 4,324** feasible controls.
- Scope: `ChkForNonSolids`, `NSFnd`; expected current matches: **2**; maximum **1,452 / 1,992**.

## S30 closure — non-solid metatile predicate

`ChkForNonSolids` and `NSFnd` are current-exact. Static `$E1B5-$E1C6`
comparison confirms each immediate operand, all four taken equality branches,
the `$60` final-comparison fallthrough and direct return. Eight controlled
original-ROM entries cover all five matching metatiles and three non-matches;
x86/x64 predicates agree with the returned Z result in every case. The
similar-issue sweep found one shared membership predicate whose positive C
return intentionally represents the original Z-set branch; its callers use
that same polarity. Focused ground-query and platform-purity CTests pass on
both widths, and OpenNT links DOS16. Product C did not change, so the S29
package EXEs remain current.

S30 marks `ChkForNonSolids`, `NSFnd`, and `control-02695` through
`control-02699` exact. Caller return relations remain with their caller-chain
audits. Current totals: historical **1,992 / 1,992**; current exact nodes
**1,452 / 1,992**; current exact feasible controls **3,043 / 4,324** (raw
**4,342**, infeasible **18**).

## S31 admission — fireball background collision chain

S31 admits `$E1C8-$E1F0`: `FireballBGCollision`, `ClearBounceFlag` and
`InitFireballExplode`, all owned by `src/game/world/collision.c`. S30 supplies
the non-solid predicate; S32 begins the bounding-box data boundary. The ROM
logic track proves the status-bar BCC, bottom-probe call/return, empty and
non-solid clear paths, signed Y-speed explosion path, set-bounce explosion
path, and ordered `$fd` speed/bounce/Y-alignment writes. The operational track
uses controlled original-ROM direct entries and x86/x64 RAM checks, focused
fireball tests, platform purity and the shared DOS16 link. Product artifacts
refresh only if shared product C changes.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,452 / 1,992** nodes and **3,043 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: `FireballBGCollision`, `ClearBounceFlag`, `InitFireballExplode`;
  expected current matches: **3**; maximum **1,455 / 1,992**.

## S31 closure — fireball background collision chain

All three scoped labels are current-exact: `FireballBGCollision`,
`ClearBounceFlag` and `InitFireballExplode`. Static `$E1C8-$E1F0` comparison
confirms the status-bar BCC, the ordered `BlockBufferChk_FBall` and
`ChkForNonSolids` calls/returns, empty/non-solid clear paths, signed-Y-speed
and set-bounce explosion branches, then the downward `$fd` speed write,
bounce set and `$f8` Y alignment. The helper writes match the source exactly:
clear writes only `FireballBouncingFlag`; explode writes `$80` state then
`Sfx_Bump` to Square1.

Seven controlled original-ROM direct entries cover status-bar, empty, non-solid,
first solid bounce, upward-solid explosion, repeated-solid explosion and the
final non-solid table member. The x86/x64 actual check compares every
source-visible write in each record with zero differences. Fireball OAM smoke
and platform-purity CTests pass on both widths; the OpenNT DOS16 shared-source
link completes. The similar-issue sweep found no duplicate fireball-background
predicate or host-side game branch. Product C did not change, so the three
package EXEs intentionally remain the S29 artifacts.

S31 records nodes `FireballBGCollision`, `ClearBounceFlag` and
`InitFireballExplode`, plus feasible controls `control-02700` through
`control-02706`, `control-03991` and `control-03992`, exact. Current totals:
historical **1,992 / 1,992**; current exact nodes **1,455 / 1,992**; current
exact feasible controls **3,052 / 4,324** (raw **4,342**, infeasible **18**).

## S32 admission — bounding-box control data

S32 admits `BoundBoxCtrlData` at `$E1FD-$E22C`, owned by
`src/game/world/bounding_box.c:mysmb_world_set_bounding_box`. S31 is the
source predecessor; S33 begins the caller and bounding-box paths. The ROM logic
track reads all twelve four-byte records from the local ROM and verifies their
left/top/right/bottom ordering. The operational track executes every control
value through the shared C owner on x86/x64, runs focused table and purity
checks, and links the shared DOS16 source. The material relation
`BoundBoxCtrlData -> BoundingBoxCore` is in scope. Product artifacts refresh
only if shared product C changes.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,455 / 1,992** nodes and **3,052 / 4,324**
  feasible controls (raw **4,342**, infeasible **18**).
- Scope: `BoundBoxCtrlData`; expected current matches: **1**; maximum
  **1,456 / 1,992**.

## S32 closure — bounding-box control data

`BoundBoxCtrlData` is current-exact. A direct local-ROM PRG read located the
48-byte record at `$E1FD-$E22C`; this corrected the stale `$E2A5` source
comment without changing gameplay behavior. All twelve four-byte records
match the shared C table in exact left/top/right/bottom order. The material
relation `material-00403` (`BoundBoxCtrlData -> BoundingBoxCore`) is exact:
every valid control selects its corresponding four source offsets before the
later core consumes them.

Fresh x86/x64 checks run all twelve controls with wrapping X/Y inputs and
compare every produced box byte against the ignored ROM record; all pass.
Platform purity passes on both widths and the OpenNT DOS16 shared-source link
completes. The similar-issue sweep found no second bounding-box table or
platform geometry branch. Only source provenance and test/build wiring changed,
so package EXEs remain the S29 artifacts.

S32 records node `BoundBoxCtrlData` and material relation `material-00403`
exact. Current totals: historical **1,992 / 1,992**; current exact nodes
**1,456 / 1,992**; current exact feasible controls **3,052 / 4,324** (raw
**4,342**, infeasible **18**); exact material relations **359 / 487**.

## S33 admission - object bounding-box entry chain


`GetFireballBoundBox`, `GetMiscBoundBox`, `FBallB`, `GetEnemyBoundBox`, `SmallPlatformBoundBox`, `GetMaskedOffScrBits`, `CMBits`, `LargePlatformBoundBox`, `SetupEOffsetFBBox`, `MoveBoundBoxOffscreen`

All ten labels are incoming needs-evidence and expected current-exact; maximum 1,466/1,992. Historical mapping remains 1,992/1,992, expected new historical matches zero. S32 supplies table binding; S34/S35 own child core/clipping internals. RAM $00-$07 and CPU registers/stack are child ABI, audited at child boundaries; persistent outputs must agree unconditionally, including unchanged bytes.

ROM span $E22D-$E29B. Shared owners are world/collision.c, objects.c and enemy_bounds.c. Static instruction/control audit and bounded direct original-ROM entry matrix cover entry offset, fixed relative coordinate selection, left/right masks, hidden boxes and partial large-platform visibility. Operational proof uses fresh x86/x64 replay, focused purity and DOS16 shared-source link.

## S33 closure - object bounding-box entry chain

All ten scoped nodes are current-exact: `GetFireballBoundBox`, `GetMiscBoundBox`, `FBallB`, `GetEnemyBoundBox`, `SmallPlatformBoundBox`, `GetMaskedOffScrBits`, `CMBits`, `LargePlatformBoundBox`, `SetupEOffsetFBBox`, `MoveBoundBoxOffscreen`.
Static $E22D-$E29B comparison confirms +7 fireball, +9 misc and +1 enemy
selection, fixed relative-coordinate fields, ordinary $44/$48 and small-platform
$04/$08 masks, signed page/zero selection, masked hide/build ordering and the
large-platform raw horizontal $FE threshold. The identical box and clipping
children retain their own internal audits in S34/S35; their calls, returns and
tails are observed here without crediting child-internal nodes.

The original GetMiscBoundBox leaves X at slot+9 for the clipping tail. Both
coin and hammer C entries instead used misc movement slot+13 for clip input.
They now read the original $76+slot and $8f+slot, while keeping the ROM's
$04a2 control, fixed relative fields and $04d0 output box. A similar-issue
sweep reviewed all six shared clipping call sites: the two misc sites required
this repair; fireball, enemy, small and large-platform sites match their source
offsets. The strengthened checker compares all 1,784 persistent RAM bytes
unconditionally, so it catches spurious writes and unchanged-byte discrepancies.
Scratch $00-$07 and CPU stack/registers are explicit child ABI exclusions;
call/input/output semantics are checked at the shared owner seams.

Sixty controlled original-ROM entries cover all five entry families, twelve
controls, both fireball slots, nine misc slots, six enemy slots, page/position
variants and nonzero/zero mask outcomes. Each width also executes the twelve
misc records through the hammer counterpart. Both widths have zero differences.
Observed source branches: E25F 10 taken/14 fallthrough; E263 2/12; E26E
14/10; E27A 4/8. E234 is 12/0 because LDY #$02 immediately sets Z=0.
Thus control-02708 is infeasible, not an omitted feasible C connection.

The 19 newly exact feasible controls are control-02707, control-02709 through
control-02723, and control-03993 through control-03995. Caller-owned outer
returns remain with their caller audits. Current totals: historical mapping
**1,992/1,992**; current exact nodes **1,466/1,992**; current exact feasible
controls **3,071/4,323**, raw **4,342**, infeasible **19**; exact material
relations **359/487**. The former 4,324 denominator decreases by the newly
proven impossible fallthrough. Registry summary caches were refreshed from
individual authoritative rows.

Operational proof: fresh x86/x64 shared-owner replay and Win32 product builds,
product self-tests, focus-pause and audio-renderer tests, and platform-purity
checks pass; OpenNT DOS16 shared-source build and link complete. All three
assets/mysmb16.exe, mysmb32.exe and mysmb64.exe are refreshed from their
matching build outputs. The owner-approved local EXE submission continues;
no raw records, ROM bytes or generated data are staged. Unrelated working-tree
source/proposal/queue changes are preserved.

## S34 admission - bounding-box coordinate core

S34 admits `BoundingBoxCore` at $E29C-$E2DD, owned exclusively by
`src/game/world/bounding_box.c:mysmb_world_set_bounding_box`. S33 supplies
object/relative/control/address selection; S35 owns screen clipping. The
source has no internal control branch or child call. All six incident control
relations already have exact caller evidence; no new control credit is planned.

Incoming current exact nodes are **1,466/1,992**; `BoundingBoxCore` is
needs-evidence and the sole expected current promotion, maximum **1,467/1,992**.
Historical mapping remains **1,992/1,992**, with zero new historical credit.
Current exact feasible controls are **3,071/4,323**; material **359/487**.

Static proof covers four independent CLC/ADC byte additions, table/index
selection, UL-X/LR-X/UL-Y/LR-Y store order and restored X/box-offset Y.
Direct original-ROM entries cover twelve valid controls, all byte coordinates,
eighteen object slots and seven relative offsets. Native checks compare every
persistent RAM byte, including unchanged bytes, and explicitly check original
scratch/register contracts at the C argument seam. CPU stack and flags are
ABI-only, not persistent game outputs. Focused x86/x64 tests and platform
purity supply operational proof; product EXEs refresh only for behavior changes.

Owner ROM and disassembly remain nonredistributable local research inputs.
Raw records and probes stay below ignored build/m2-t64-s34, bounded to 20 MiB
and 524,288 steps per case; S34 owns cleanup. Only neutral harnesses and
conclusions are tracked. Review includes caller control-domain writes and
similar coordinate/box implementations in shared and platform code.

## S34 closure - bounding-box coordinate core

`BoundingBoxCore` is current-exact. The $E29C-$E2DD source has four
independent CLC/ADC operations and writes UL-X, LR-X, UL-Y, LR-Y in that
order. C casts each sum separately to the original byte width, with no carried
X addition affecting Y. Caller-selected address $04ac+4*object, relative
coordinates and control map to explicit C arguments; ROM restores X and
returns Y=4*object. The stale $DC71 provenance comment is corrected.

The similar-issue sweep reviews player, enemy initializer, cannon, hammer,
power-up, fireball and Bowser control writers: source-reachable initialized
controls remain 0..11. C's defensive >=12 fallback is outside that domain;
this evidence does not claim equivalence for arbitrary corrupted control RAM.
No duplicate platform geometry implementation was found. The rectangle test
and clipping helper are distinct successor owners, not credited by this proof.

The new neutral `tools/reference_bounding_box_core_probe.c` directly executes
$E29C without modifying ROM. Its ignored MSBC records are consumed by
`mysmb_bounding_box_core_actual_check` built from
`test/bounding_box_core_actual_check.c`. There are 3,072 fixtures: twelve
controls times all 256 X values, Y=255-X (thus all Y byte values), rotating
eighteen object slots and seven relative-coordinate indices. This is not the
Cartesian product of X and Y: independence is established by the four source
CLC instructions and separate C sums. Each fixture restores the same booted
reference machine, preventing unrelated accumulated NMI timing from entering
the isolated core route. Every route completes in 36 instructions.

Fresh x86 and x64 checks each compare all 1,784 persistent RAM bytes including
unchanged bytes: **3,072/3,072, zero differences** per width. Separately they
validate returned X/Y, original scratch $00/$01/$02 against the explicit
argument seam, and unchanged $03-$07. The CPU stack and flags have no C
register counterpart and are explicitly excluded. Core smoke and platform
purity pass on both widths. The unchanged shared core also builds and links
with the original OpenNT DOS16 toolchain (the pre-existing OLDNAMES.LIB
warning remains). No behavior changed, so existing three EXEs
remain the committed S33 delivery; no package refresh is required. Raw records
and the reference probe executable are cleaned after evidence review.

The six incident controls retain prior exact evidence: `control-00871`,
`control-02710`, `control-02722`, `control-03647`, `control-03993`,
`control-03995`. No new control or material credit is claimed. Material
`material-00403` retains the S32 table-binding proof; `material-00404` is
still consumer-owned, not promoted by this producer audit. Historical mapping
remains **1,992/1,992**; current exact nodes **1,467/1,992** (+1), current
exact feasible controls **3,071/4,323** (raw 4,342, infeasible 19), exact
material relations **359/487**. S35 owns the next screen-clipping chain.

## S35 admission - bounding-box screen clipping

S35 admits the $E2DE-$E324 chain: `CheckRightScreenBBox`, `SORte`, `NoOfs`,
`CheckLeftScreenBBox`, `SOLft`, `NoOfs2`. All six need current evidence and
are expected exact, maximum **1,473/1,992** from **1,467/1,992**. Shared
owner is `src/game/world/bounding_box.c:mysmb_world_clip_bounding_box_to_screen`;
S34 supplies box construction and S36 owns rectangle comparison. Historical
mapping remains **1,992/1,992**, with zero new historical credit.

The ten unresolved source-owned controls `control-02724` through
`control-02733` are in scope. Incoming exact feasible controls **3,071/4,323**
(raw 4,342, infeasible 19); material **359/487**. Source audit proves
ScreenLeft+$80 low-byte carry/page wrap, CMP/SBC borrow polarity, signed
corner predicates, $80-$9f near-left visibility, $a0-$ff clip and restored
ObjectOffset. Direct ROM entries use a restored boot baseline per fixture,
all byte input values and page/corner branch families. x86/x64 native checks
compare all persistent RAM, plus explicit scratch/register argument seams.
Focused tests, purity and unchanged shared DOS16 link are operational proof.
Behavior changes require all three product EXEs; provenance-only changes do not.

Owner-local ROM/disassembly are nonredistributable research only. Ignored
build/m2-t64-s35 holds raw records <=24 MiB, 524288 steps/case and a
120-second total route budget; S35 owns cleanup. Similar-issue sweep reviews
all shared clipping callers and platform geometry ownership. No successor
node or unrelated I/O change is credited.

## S35 closure - bounding-box screen clipping

All six scoped nodes are current-exact: `CheckRightScreenBBox`, `SORte`,
`NoOfs`, `CheckLeftScreenBBox`, `SOLft`, `NoOfs2`. Static $E2DE-$E324
review proves the midpoint low carry into byte-wrapped page, followed by
object-low CMP borrow into page SBC. The C unsigned world comparison has
the same carry predicate, including middle-page wrap. Right clipping checks
DR sign before UL sign; left clipping preserves $80-$9f and clips $a0-$ff,
with the original conditional opposite-corner store. Both returns restore
ObjectOffset and retain the selected box Y offset at the explicit C seam.

No behavior repair was needed. The stale $DC9F/$DCF5 provenance is corrected
to the actual $E2DE-$E324 span. The similar-issue sweep finds one shared
clipping implementation and five physical call sites representing the six
fireball/misc-coin/misc-hammer/enemy/small-platform/large-platform paths.
Their input selections retain the S33 proof; platforms contain no clip logic.
The unadmitted rectangle consumers remain successor-owned.

The neutral probe `tools/reference_bounding_box_clip_probe.c` directly runs
$E2DE, with isolated boot-state restoration and no ROM changes. The native
`mysmb_bounding_box_clip_actual_check` consumes its ignored MSCL records
through `test/bounding_box_clip_actual_check.c`. Actual record inspection
confirms all 256 values each for screen X, object X, UL-X and DR-X, 18
object offsets, every side/UL-sign/DR-sign family, 12 exact-midpoint ties and
512 screen-page wraps. This 4,096-fixture route is a branch-family matrix,
not an exhaustive Cartesian product of all bytes. Source arithmetic and
branch comparison provide the independent static track.

All 32 instructions in the chain are observed, maximum 23 per route. Branch
taken/fallthrough counts are E2F5 **2426/1670**, E2FA **836/834**, E301
**414/420**, E30F **1217/1209**, E313 **314/895**, E31A **449/446**.
Fresh x86/x64 native owners each match all 1,784 persistent RAM bytes
unconditionally for **4,096/4,096** records, zero differences. Returned
X=ObjectOffset, unchanged Y=4*object, middle scratch $01/$02 and unchanged
other scratch bytes are separately checked; CPU flags and stack have no C
register counterpart and are explicitly excluded. Focused core smoke and
platform-purity checks pass on both widths. The original OpenNT DOS16
shared-core build/link succeeds with the existing OLDNAMES.LIB warning.

The ten newly exact controls are `control-02724` through `control-02733`.
The incoming tail edges `control-02711` and `control-02723` retain S33
evidence. No new material relation is credited; box-to-consumer material
relations remain with their consumer audits. Historical mapping stays
**1,992/1,992**; exact nodes **1,473/1,992** (+6), exact feasible controls
**3,081/4,323** (+10; raw 4,342, infeasible 19), material **359/487**.
No product behavior changed, so the three committed S33 EXEs remain the
delivery. Raw records/probe binary are cleaned after review. S36 is the next
rectangle-comparison chain.

## S36 admission - rectangle collision core

S36 admits $E325-$E387: `PlayerCollisionCore`, `SprObjectCollisionCore`,
`CollisionCoreLoop`, `SecondBoxVerticalChk`, `FirstBoxGreater`,
`NoCollisionFound`, `CollisionFound`. All seven need evidence, expected
current exact **1,473 -> 1,480 / 1,992**; historical mapping remains
**1,992/1,992**, zero new historical credit. Shared owner is
`src/game/world/geometry.c:mysmb_world_boxes_collide`; S35 is the source
predecessor and T64 aggregate integration review follows the final planned chain.

Scope includes internal controls `control-02734` through `control-02750`,
actual fireball/hammer returns `control-03901` and `control-03907`, internal
material handoffs `material-00405` through `material-00408`, producer handoff
`material-00404` and hammer miss consumption `material-00347`. Other
consumer relations require their own aggregate integration proof. Incoming
exact controls **3,081/4,323**; material **359/487**.

Static proof follows every unsigned comparison, inclusive equality and wrap
branch, horizontal short circuit, vertical loop, $06 restoration, $07 values
1/0/$ff and carry-equivalent return. Direct ROM player/object entries cover
all 6^4 endpoint rank combinations per axis, with isolated boot state. Actual
fireball and hammer roots connect the proven child to source return consumers;
a bounded box-producer/core route checks source coordinate handoff. Native
x86/x64 owners compare all persistent RAM plus source-live $06/$07; transient
CPU stack/flags/registers use explicit seam checks. Focused tests, purity and
original OpenNT DOS16 link are separate operational proof. Any difference
remains here for repair and repeated audit; behavior changes refresh all EXEs.

Owner ROM/disassembly are nonredistributable local research. Raw records and
probe outputs stay under ignored build/m2-t64-s36, bounded to 48 MiB,
524288 steps/case and 120 seconds total; S36 owns cleanup. Similar-issue
sweep covers geometry calls and return consumption without changing unrelated
source. Only neutral harnesses and conclusions are committed.

## S36 closure - rectangle collision core

All seven scoped labels are current-exact: `PlayerCollisionCore`,
`SprObjectCollisionCore`, `CollisionCoreLoop`, `SecondBoxVerticalChk`,
`FirstBoxGreater`, `NoCollisionFound`, `CollisionFound`. Static $E325-$E387
review follows every unsigned comparison, inclusive equality, wrapped interval
branch and early return. Horizontal rejection skips vertical evaluation;
overlap advances both offsets and decrements $07 from 1 to 0 to $ff, then
returns set carry. The C owner preserves live $06/$07 and exposes the original
carry as its byte return. Original Y restoration and X advancement are checked
at that explicit address/result seam. No behavior discrepancy was found; only
the stale $DCF6/$DD27 provenance is corrected.

The neutral `tools/reference_geometry_core_probe.c` produces ignored MSGE
records for `mysmb_geometry_core_route_check`, built from
`test/geometry_core_route_check.c`. It executes 10,512 isolated original-ROM
routes without ROM patches: 5,184 direct player/object entries; 2,592 real
hammer callers; 2,592 real fireball callers with one Buzzy immune enemy; and
144 source box-producer/player-core chains. The direct matrix contains all
1,296 combinations of four endpoints drawn from six ordered representative
byte values per entry/axis, with the other axis overlapping. Comparison-only
branch predicates depend on endpoint weak ordering; this matrix covers every
such ordering, equality and interval-wrap family. It is not an exhaustive
Cartesian product of all eight box bytes.

All 46 original core instructions are observed. Fourteen branch
taken/fallthrough totals are E333 **15283/4419**, E338 **2734/1685**, E33A
**720/965**, E342 **401/564**, E347 **281/283**, E352 **964/1770**, E35A
**895/875**, E362 **1736/13547**, E367 **10180/3367**, E369 **720/2647**,
E36E **400/2247**, E370 **440/1807**, E378 **1121/686**, E382 **9190/7828**.
There are 2,592 actual ROM child-return continuations each into the hammer
and fireball caller, not synthetic caller-result replay. Every family reaches
$07=1 horizontal miss, $07=0 vertical miss and $07=$ff full overlap.

Fresh x86/x64 native checks use real shared owners, with no substituted
geometry result: each **10,512/10,512**, zero differences. All 1,792
non-stack RAM bytes are compared, including live $06/$07 and unchanged
bytes. The box-producer family instead compares 1,789 bytes: transient
producer $00-$02 is checked separately against its explicit arguments.
CPU stack and non-carry flags are excluded; direct routes compare carry and
returned X/Y. The hammer miss route compares the reloaded misc latch; the
fireball route checks full scan state; the producer route checks actual
generated box bytes consumed by geometry. Focused core smoke/platform purity
pass on both widths; original OpenNT DOS16 shared-core build/link succeeds
with the existing OLDNAMES.LIB warning.

The similar-issue sweep finds six production geometry calls: fireball, hammer,
player-enemy, enemy-pair, large-platform and small-platform. All use the same
shared owner; no platform geometry copy exists. Already exact caller scopes
retain their evidence; GetEnemyBoundBoxOfsArg-to-platform consumer handoff
`material-00402` is still pending aggregate integration proof and is not
credited by a direct core route.

New exact controls: `control-02734` through `control-02750`,
`control-03901`, `control-03907` (**19**). New exact material relations:
`material-00347`, `material-00404`, `material-00405`, `material-00406`,
`material-00407`, `material-00408` (**6**). Historical mapping stays
**1,992/1,992**; current exact nodes **1,480/1,992** (+7), exact feasible
controls **3,100/4,323** (+19; raw 4,342, infeasible 19), material
**365/487** (+6). No product behavior changed; the three committed S33
EXEs remain the delivery. Raw records/probe executable are cleaned after
review. All planned source-order chains have now reached their S closures;
T64 itself still requires the aggregate cross-chain/node-edge review before
closure and T65 admission.

## Aggregate closure gate after S36

Cohort J has **497/497 current-exact nodes**, combining the preceding
source-order owner work and the 253 T64 labels. This does not close the graph:
**81 feasible controls** and **3 material relations** still need current
connection evidence. These are missing proofs, not newly confirmed behavior
mismatches. T64 remains open. Its next admitted aggregate work must give each
relation a source/C counterpart and actual caller/return or producer/consumer
route before promotion; existing child or caller exact status alone is not
sufficient. A bounded plan must group source-adjacent return families and
retain explicit later-owner dependencies rather than silently mark all exact.

| Control | Original source | Original destination | Relation |
| --- | --- | --- | --- |
| `control-02442` | `GBBAdr` | `HeadChk` | branch |
| `control-02443` | `GBBAdr` | `HeadChk` | fallthrough |
| `control-02501` | `CheckSideMTiles` | `ChkInvisibleMTiles` | call |
| `control-03809` | `GetEnemyOffscreenBits` | `RunSmallPlatform` | return |
| `control-03810` | `RelativeEnemyPosition` | `RunSmallPlatform` | return |
| `control-03811` | `SmallPlatformBoundBox` | `RunSmallPlatform` | return |
| `control-03812` | `SmallPlatformCollision` | `RunSmallPlatform` | return |
| `control-03813` | `RelativeEnemyPosition` | `RunSmallPlatform` | return |
| `control-03814` | `DrawSmallPlatform` | `RunSmallPlatform` | return |
| `control-03816` | `GetEnemyOffscreenBits` | `RunLargePlatform` | return |
| `control-03817` | `RelativeEnemyPosition` | `RunLargePlatform` | return |
| `control-03818` | `LargePlatformBoundBox` | `RunLargePlatform` | return |
| `control-03819` | `LargePlatformCollision` | `RunLargePlatform` | return |
| `control-03821` | `RelativeEnemyPosition` | `SkipPT` | return |
| `control-03822` | `DrawLargePlatform` | `SkipPT` | return |
| `control-03824` | `InitPodoboo` | `MovePodoboo` | return |
| `control-03825` | `SpawnHammerObj` | `ChkJH` | return |
| `control-03826` | `PlayerEnemyDiff` | `Shimmy` | return |
| `control-03827` | `MoveD_EnemyVertically` | `FallE` | return |
| `control-03828` | `MoveEnemyHorizontally` | `AddHS` | return |
| `control-03829` | `MoveD_EnemyVertically` | `MoveDefeatedEnemy` | return |
| `control-03831` | `MoveJ_EnemyVertically` | `MoveJumpingEnemy` | return |
| `control-03834` | `MoveEnemyHorizontally` | `XMRight` | return |
| `control-03835` | `PlayerEnemyDiff` | `FBLeft` | return |
| `control-03837` | `GetEnemyOffscreenBits` | `ProcFirebar` | return |
| `control-03839` | `RelativeEnemyPosition` | `SetupGFB` | return |
| `control-03844` | `DrawFirebar` | `FirebarCollision` | return |
| `control-03845` | `InjurePlayer` | `SetSDir` | return |
| `control-03846` | `MoveEnemyHorizontally` | `FlyCC` | return |
| `control-03847` | `SetXMoveAmt` | `FlyCC` | return |
| `control-03849` | `PlayerEnemyDiff` | `PlayerLakituDiff` | return |
| `control-03850` | `MoveEnemySlowVert` | `MoveD_Bowser` | return |
| `control-03853` | `InitVStf` | `RemoveBridge` | return |
| `control-03855` | `PlayerEnemyDiff` | `B_FaceP` | return |
| `control-03856` | `MoveEnemySlowVert` | `HammerChk` | return |
| `control-03857` | `SpawnHammerObj` | `HammerChk` | return |
| `control-03858` | `InitVStf` | `MakeBJump` | return |
| `control-03862` | `RunRetainerObj` | `ProcessBowserHalf` | return |
| `control-03863` | `GetEnemyBoundBox` | `ProcessBowserHalf` | return |
| `control-03864` | `RelativeEnemyPosition` | `SetGfxF` | return |
| `control-03865` | `GetEnemyOffscreenBits` | `DrawFlameLoop` | return |
| `control-03866` | `RelativeEnemyPosition` | `SetupExpl` | return |
| `control-03867` | `DrawExplosion_Fireworks` | `SetupExpl` | return |
| `control-03869` | `DigitsMathRoutine` | `NoTTick` | return |
| `control-03870` | `DigitsMathRoutine` | `ELPGive` | return |
| `control-03871` | `RelativeEnemyPosition` | `DrawStarFlag` | return |
| `control-03874` | `PlayerEnemyDiff` | `MovePiranhaPlant` | return |
| `control-03887` | `MovePlatformUp` | `ChkYCenterPos` | return |
| `control-03888` | `MovePlatformDown` | `YMDown` | return |
| `control-03889` | `PositionPlayerOnVPlat` | `ChkYPCollision` | return |
| `control-03892` | `PositionPlayerOnVPlat` | `SetPVar` | return |
| `control-03893` | `MoveDropPlatform` | `DropPlatform` | return |
| `control-03894` | `PositionPlayerOnVPlat` | `DropPlatform` | return |
| `control-03895` | `MoveEnemyHorizontally` | `RightPlatform` | return |
| `control-03899` | `PositionPlayerOnS_Plat` | `ChkSmallPlatCollision` | return |
| `control-03902` | `HandleEnemyFBallCol` | `NotGoomba` | return |
| `control-03903` | `RelativeEnemyPosition` | `HandleEnemyFBallCol` | return |
| `control-03904` | `InitVStf` | `HurtBowser` | return |
| `control-03906` | `SetupFloateyNumber` | `EnemySmackScore` | return |
| `control-03909` | `SetupFloateyNumber` | `HandlePowerUpCollision` | return |
| `control-03910` | `GetPlayerColors` | `Shroom_Flower_PUp` | return |
| `control-03911` | `SetPRout` | `UpToFiery` | return |
| `control-03961` | `ChkInvisibleMTiles` | `CheckSideMTiles` | return |
| `control-03971` | `SubtEnemyYPos` | `EnemyToBGCollisionDet` | return |
| `control-03972` | `ChkUnderEnemy` | `YesIn` | return |
| `control-03973` | `ChkForNonSolids` | `HandleEToBGCollision` | return |
| `control-03974` | `KillEnemyAboveBlock` | `HandleEToBGCollision` | return |
| `control-03975` | `SetupFloateyNumber` | `GiveOEPoints` | return |
| `control-03976` | `PlayerEnemyDiff` | `SetNotW` | return |
| `control-03977` | `EnemyLanding` | `SetForStn` | return |
| `control-03978` | `PlayerEnemyDiff` | `InvtD` | return |
| `control-03979` | `ChkForBump_HammerBroJ` | `CNwCDir` | return |
| `control-03980` | `EnemyLanding` | `LandEnemyInitState` | return |
| `control-03981` | `BlockBufferChk_Enemy` | `SdeCLoop` | return |
| `control-03982` | `ChkForNonSolids` | `SdeCLoop` | return |
| `control-03983` | `InitVStf` | `EnemyLanding` | return |
| `control-03984` | `SubtEnemyYPos` | `EnemyJump` | return |
| `control-03985` | `ChkUnderEnemy` | `EnemyJump` | return |
| `control-03986` | `ChkForNonSolids` | `EnemyJump` | return |
| `control-03987` | `EnemyLanding` | `EnemyJump` | return |
| `control-03988` | `ChkUnderEnemy` | `HammerBroBGColl` | return |

| Material | Producer | Consumer |
| --- | --- | --- |
| `material-00402` | `GetEnemyBoundBoxOfsArg` | `PlayerCollisionCore` |
| `material-k54-01` | `SolidMTileUpperExt` | `CheckForSolidMTiles` |
| `material-k54-02` | `ClimbMTileUpperExt` | `CheckForClimbMTiles` |

## Aggregate S37 admission - terrain entry and metatile connections

S37 is the first bounded aggregate connection audit after the 36 source-order
node chains. It owns `control-02442`, `control-02443`, `control-02501`,
`control-03961`, `material-k54-01`, `material-k54-02`: crouch/noncrouch
GBBAdr-to-HeadChk entry, side hidden-predicate call/return, and solid/climb
threshold-table consumer bindings. These belong to one player-background
collision route with already proven classifier children.

The exact node scope is `GBBAdr`, `HeadChk`, `CheckSideMTiles`,
`ChkInvisibleMTiles`, `SolidMTileUpperExt`, `CheckForSolidMTiles`,
`ClimbMTileUpperExt`, `CheckForClimbMTiles`. All eight are incoming exact;
expected new nodes **0**, maximum unchanged **1,480/1,992**. This is an
explicit zero-node-credit audit because the concrete missing proof is the
six named connections, not a new mapping pass. Historical **1,992/1,992**
also stays unchanged. Incoming exact controls **3,100/4,323** and material
**365/487**; expected closing controls **3,104/4,323**, material **367/487**.

Read source branch/child/table contracts, execute real original-ROM terrain
roots, and compare current native owners without installing child return
records. Classifier routes cover every tile byte against actual source data.
CPU scratch/register/stack contracts must be explicit; differences remain
here for repair and repeated proof. Operational proof uses focused tests,
x86/x64 checks, purity and unchanged OpenNT DOS16 link. Product behavior
changes require three refreshed EXEs. Preserve unrelated terrain edits.

Owner ROM/disassembly are nonredistributable local research. Ignored
build/m2-t64-s37 owns <=8 MiB raw records, 524288 steps/case, 120-second
route budget and cleanup. Only neutral harnesses/evidence are committed.
Review terrain entry, classifier/hidden predicate callers and duplicate host
logic. Remaining return families and platform material-00402 stay explicitly
open in the aggregate gate; this S does not close T64.

## Aggregate S37 closure - terrain entry and metatile connections

Four controls are newly exact: `control-02442`, `control-02443`,
`control-02501`, `control-03961`. Two material relations are newly exact:
`material-k54-01`, `material-k54-02`. All eight scoped nodes retain their
prior exact state; no duplicate node credit is claimed. The eight existing
labels are `GBBAdr`, `HeadChk`, `CheckSideMTiles`, `ChkInvisibleMTiles`,
`SolidMTileUpperExt`, `CheckForSolidMTiles`, `ClimbMTileUpperExt`,
`CheckForClimbMTiles`.

Source GBBAdr's crouch-zero branch and crouch-nonzero increment reach the
same HeadChk with the same size-derived extent X. The C head owner computes
the same index; no mutation occurs between entry selection and consumption.
Source CheckSideMTiles passes unchanged tile A into the hidden predicate and
consumes returned Z for its early exit. The actual C call preserves that tile
and consumes its equivalent byte result. Solid/climb table handoffs retain
the original top-two-bit group, corresponding threshold and unsigned compare;
actual ROM binding and the resource-free fallback have the same result.

The neutral `tools/reference_terrain_connection_probe.c` produces ignored
MSTC records for `mysmb_terrain_connection_route_check`, built from
`test/terrain_connection_route_check.c`. It runs 32 actual $DC64 terrain
roots covering size/crouch/swim selection and empty/$5f/$60/$61 buffer
contents, then 768 direct classifier entries covering every tile byte for
solid, climbable and invisible predicates. Original $DCB7 has **16 taken /
16 fallthrough**; the actual $DD9C hidden call and $DEC3->$DD9F return are
each observed **24** times, including both true hidden IDs and the false
solid-tile path. Root fixtures start from a restored boot machine, with no
ROM changes. Maximum **474 instructions** per complete route.

Fresh real x86/x64 owners, without installing oracle child returns, each
match **800/800**, zero differences. Terrain roots compare every 1,784
persistent RAM byte including unchanged bytes; query scratch $00-$07 and
CPU stack are declared ABI exclusions, with head X and side predicate Z
checked explicitly at their argument/result seams. Pure predicates compare
all 1,792 non-stack RAM bytes plus source A, group X/Y and carry/Z results.
All 256 tiles per threshold also match without a bound ROM, proving the
fallback table path. Both widths pass focused terrain/metatile smokes and
platform purity; original OpenNT DOS16 builds/links the unchanged core with
the existing OLDNAMES.LIB warning.

The similar-issue sweep checks all solid/climb/hidden predicate consumers in
shared game sources. Head, feet and side use the same owned classifiers;
enemy terrain's non-solid classifier remains a distinct ROM rule. No host
predicate copy was found. Unrelated terrain work is preserved, no product
source changes or EXE refresh occur. Raw record/probe files are cleaned.

Historical **1,992/1,992** and current exact nodes **1,480/1,992** remain
unchanged. Exact controls rise **3,100 -> 3,104 / 4,323** (raw 4,342,
infeasible 19); material **365 -> 367 / 487**. The S36 aggregate table is
a closure-time snapshot: its four terrain controls and two table materials
are now resolved. Current Cohort J remainder is **77 feasible controls and
one material relation (`material-00402`)**. T64 remains open; the next
bounded connection family is the small/large-platform call/return path.

## Aggregate S38 admission - platform return and box-offset handoff

S38 owns twelve pending returns: `control-03809` through `control-03814`,
`control-03816` through `control-03819`, `control-03821`, `control-03822`,
and `material-00402` GetEnemyBoundBoxOfsArg-to-PlayerCollisionCore. It audits
actual small/large-platform roots at $C94D/$C965, not the stale $C5BB/$C5E9
provenance in the old T63 S2 closure narrative. Source call bytes and native
call order will be verified before replay.

The exact node scope is RunSmallPlatform, RunLargePlatform, SkipPT,
GetEnemyOffscreenBits, RelativeEnemyPosition, SmallPlatformBoundBox,
SmallPlatformCollision, LargePlatformBoundBox, LargePlatformCollision,
DrawSmallPlatform, DrawLargePlatform, GetEnemyBoundBoxOfsArg,
PlayerCollisionCore. Ten are exact; GetEnemyOffscreenBits,
RelativeEnemyPosition and DrawSmallPlatform still require their generic
child-owner audits. This S credits only the platform boundary routes, with
**zero new nodes**, current total unchanged **1,480/1,992**. Generic child
status/custody remains with its planned later owner; a platform route alone
cannot promote all generic child paths.

Incoming exact controls **3,104/4,323**, material **367/487**; expected
closing controls **3,116/4,323**, material **368/487**. Historical
**1,992/1,992** stays unchanged. This zero-node-credit S addresses concrete
missing return/handoff evidence. Real ROM roots exercise position/mask,
box/collision, timer/movement, drawing and bounds descendants; native replay
uses actual children and compares persistent RAM including OAM. CPU scratch,
register and stack seams must be explicit. Any feasible platform connection
difference stays here for a bounded shared-owner repair and repeated proof.

Owner ROM/disassembly are nonredistributable local research. Ignored
build/m2-t64-s38 owns <=8 MiB records, 524288 steps/case, 120-second
route budget and cleanup. Focused caller/collision tests, native x86/x64,
purity and original OpenNT DOS16 link are operational proof. Behavior repair
refreshes all three EXEs under owner approval. Preserve unrelated work.
Review child return slot, box offset/unindexed nibble, OAM handoff, original
source addresses and duplicate host platform logic. T64 remains open.

## Aggregate S38 closure - platform connections exact

All twelve scoped returns are exact: `control-03809` through `control-03814`,
`control-03816` through `control-03819`, `control-03821`, `control-03822`.
`material-00402` is exact. All thirteen admission labels retain their node
dispositions: ten exact and GetEnemyOffscreenBits, RelativeEnemyPosition,
DrawSmallPlatform still needs-evidence under their generic child owners.
Expected and actual newly completed nodes are both empty; no custody transfer.

Original call bytes and shared platform_callers.c establish roots $C94D,
$C965 and SkipPT $C979. These correct the stale $C5BB/$C5E9 provenance in
the historical T63 S2 narrative; that historical record is not rewritten.
Small-platform drawing precedes movement; large-platform movement is gated
by TimerControl and precedes drawing. Each original descendant RTS restores
ObjectOffset. Native immutable slot arguments preserve the same consumer
identity, including balance-platform partner checks and original-slot reload.

The neutral `tools/reference_platform_integration_probe.c` and
`test/platform_integration_route_check.c` run 512 actual original-ROM roots
against real current native descendants, without oracle-return substitution.
Each x86/x64 checker reports **512/512, zero differences**, comparing every
one of **1,784 persistent RAM bytes**, including all OAM and unchanged bytes.
CPU scratch $00-$07 and stack are explicit ABI exclusions. Twelve return
PCs each occur **256** times with **zero wrong-slot returns**. Box producer
$DC5F occurs **205** times and returns Y=slot*4+4 and A=unindexed $03D1&15;
**42 small / 109 large** handoffs enter $E325 with the same Y. The original
small mask gate and large mask-ignore semantics are preserved by the native
box helper and actual geometry calls. Observed source low masks are
0, 3, 8, e, f; distinct shadow array cells check the unindexed source.

Fixtures cover both small IDs and all seven large IDs, all six slots,
world pages 1/2, byte boundaries, eight heights and both timer paths.
Maximum route length is **934 instructions**. Routes change **6,016 small /
6,089 large** OAM bytes in aggregate. Focused platform-caller,
platform-collision-chain and platform-purity tests pass on both widths;
original OpenNT DOS16 compiles/links with the existing OLDNAMES.LIB warning.
Audio/focus/pause regressions additionally pass **6/6 on each width**.

Similar-issue review covers all twelve platform return seams, partner-slot
reloads, the shared box offset/unindexed nibble handoff and call order.
No scoped difference or host gameplay copy was found. No product source
changes or EXE refresh are needed; the existing S33 artifacts retain the
committed audio/title/focus fixes. Raw record/probe outputs are cleaned.

Historical **1,992/1,992** and exact nodes **1,480/1,992** are unchanged.
Exact feasible controls rise **3,104 -> 3,116 / 4,323** (raw **4,342**,
infeasible **19**); exact material rises **367 -> 368 / 487**.
Cohort J now has **65 controls and zero material relations** needing
evidence. The S36 aggregate table remains its historical snapshot. T64 is
open; actor-movement return integration is the next bounded source-order
family. T65 is not admitted.

## Aggregate S39 admission - Podoboo initialization return

The next source-order missing edge is `control-03824`, InitPodoboo return
to MovePodoboo. Scope labels, all already exact, are InitPodoboo,
MovePodoboo, PdbM, MoveJ_EnemyVertically, SetHiMax, SetXMoveAmt,
ImposeGravitySprObj. Expected node promotions are empty; historical
1,992/1,992 and current exact 1,480/1,992 remain unchanged. Controls enter
at 3,116/4,323 and can reach 3,117/4,323; material remains 368/487.

Entry is MovePodoboo $C9B0, exit is the completed gravity tail; shared
owners are enemy/podoboo.c, enemy/init_targets.c, enemy/movement.c and
world/gravity.c. The missing dependency is fresh evidence of the real
initializer return, previously tested with oracle-return substitution.
The predecessor is the S38 platform-return group; the next branch owner
is Hammer Bro movement. No unadmitted child or node promotion is assumed.

Static proof compares timer predicate, initializer tail and eight writes,
slot preservation, post-return PRNG read and gravity arguments. Actual ROM
routes restore a boot machine each case and execute all children. Native
x86/x64 compare every persistent RAM byte, with CPU scratch and stack
declared ABI exclusions and initializer return inputs/outputs checked
explicitly. Cases cover every PRNG byte, six slots and both timer paths.
Focused Podoboo/purity tests and original OpenNT DOS16 are independent
operational gates. Any scoped difference is repaired here and re-audited.

Owner ROM/disassembly are nonredistributable local research, not product
imports. Ignored build/m2-t64-s39 contains <=16 MiB raw records, with
524288 steps/case and 120-second total budget; S39 cleans raw records and
probe executable after verification. Only neutral harness and summaries
are tracked. Product repairs refresh all three owner-approved EXEs;
pure evidence does not. Preserve unrelated work and T64 remains open.

## Aggregate S39 closure - real Podoboo initialization return exact

`control-03824` is exact. All seven scoped nodes retain exact status:
InitPodoboo, MovePodoboo, PdbM, MoveJ_EnemyVertically, SetHiMax,
SetXMoveAmt, ImposeGravitySprObj. Expected/actual new nodes are both empty;
no deferred or transferred labels and no custody change.

Static source establishes MovePodoboo $C9B0, its timer-zero JSR $C2F7
and return $C9B8. InitPodoboo tails through SmallBBox, SetBBox and InitVStf;
it writes Y high/position=2, timer=1, state=0, box=9, direction=2,
speed=0 and force=0. The native real child does those same eight stores.
The source and C then read the same PRNG byte after the child return,
OR $80 into force, use low nibble OR 6 for timer and set speed $F9.
Both timer paths tail to MoveJ_EnemyVertically, force $1C, maximum $03,
enemy-to-sprite offset slot+1, shared gravity and original-slot restoration.

Neutral `tools/reference_podoboo_integration_probe.c` generates ignored
records for `test/podoboo_integration_route_check.c`. Each of the six
slots runs all 256 PRNG bytes with timer zero and again with nonzero timer
(1/2/3/$ff across fixtures). Thus **3,072 actual ROM roots** execute real
initialization and gravity children, with no oracle-return substitution.
**1,536 initializer returns** preserve A=0, X=slot and Y=$44. At every
return the probe checks every persistent byte against the input, allowing
only the eight original stores. **3,072 gravity entries** retain the slot.
Maximum route length is **66 instructions**; boot state is restored per case.

Fresh native x86/x64 each pass **3,072/3,072**, zero differences over every
**1,784 persistent RAM byte**, including unchanged RAM/OAM. Scratch $00-$07
and stack are declared CPU ABI exclusions; source return A/X/Y and slot
consumption are checked separately. CPU flags are not native data: the
post-return LDA overwrites N/Z and gravity resets carry before arithmetic.
Focused Podoboo movement and platform-purity tests pass on both widths;
original OpenNT DOS16 builds/links with its existing OLDNAMES.LIB warning.

The similar-issue review finds one real initializer call in the Podoboo
movement owner; all six slots and both timer branches are checked. The
initializer dispatcher also shares that same child. No host implementation
or PRNG read preceding initialization exists. No scoped difference or
product source change was found; three EXEs remain the prior delivery.
Raw records/probe executable are cleaned after accepted proof.

Historical **1,992/1,992**, current exact nodes **1,480/1,992**, material
**368/487** remain unchanged. Exact feasible controls rise
**3,116 -> 3,117 / 4,323** (raw **4,342**, infeasible **19**).
T64 remains open with **64 Cohort-J controls**, zero pending material.
Next source-order branch is Hammer Bro throw/relative-position returns.
T65 is not admitted.

## Aggregate S40 admission - Hammer Bro real child returns

S40 owns `control-03825` SpawnHammerObj-to-ChkJH and `control-03826`
PlayerEnemyDiff-to-Shimmy. Seventeen exact labels in scope are
HammerThrowTmrData, XSpeedAdderData, RevivedXSpeed, ProcHammerBro, ChkJH,
DecHT, HammerBroJumpLData, HammerBroJumpCode, SetHJ, HJump,
MoveHammerBroXDir, Shimmy, SetShim, SpawnHammerObj, PlayerEnemyDiff,
MoveNormalEnemy, MoveDefeatedEnemy. Expected new node set is empty.
Historical 1,992/1,992 and exact nodes 1,480/1,992 remain unchanged;
controls enter at 3,117/4,323 and can reach 3,119/4,323; material 368/487.

Entry ProcHammerBro $C9D8 reaches throw/jump/shimmy and normal movement,
or defeated movement, then returns. Shared owners are enemy/hammer_bro.c,
hammer.c, enemy/distance.c, enemy/movement.c and world movement/gravity.
The missing dependency is real child return evidence beyond the earlier
caller-only substituted returns. S39 is the predecessor; normal/defeated
movement return integration follows. All children already have node evidence.

Static proof audits carry-to-throw-state/timer, X slot restoration and
page subtraction/sign-to-facing/speed, including low-byte borrow and Y=1.
Actual ROM roots and native real descendants compare all persistent RAM.
Fixtures cover six slots, allocation success and both failure predicates,
all nine hammer slots, hard mode, offscreen/throw/jump timer gates, facing,
page borrow and defeated movement. Explicit CPU scratch/stack exclusions
do not exclude return carry/sign/slot contracts. Focused caller, allocation,
normal movement, purity and original OpenNT DOS16 are operational gates.

Owner ROM/disassembly are local nonredistributable research. Ignored
build/m2-t64-s40 owns <=16 MiB raw, 524288 steps/case and 120 seconds
total; S40 cleans raw records/probe after proof. Neutral harnesses and
summaries alone are tracked. Scoped mismatch stays here for repair/re-audit;
product repair refreshes all three approved EXEs. Preserve unrelated work.

## Aggregate S40 closure - Hammer Bro real child returns exact

`control-03825` and `control-03826` are exact. All seventeen scoped labels
retain exact status: HammerThrowTmrData, XSpeedAdderData, RevivedXSpeed,
ProcHammerBro, ChkJH, DecHT, HammerBroJumpLData, HammerBroJumpCode,
SetHJ, HJump, MoveHammerBroXDir, Shimmy, SetShim, SpawnHammerObj,
PlayerEnemyDiff, MoveNormalEnemy, MoveDefeatedEnemy. Expected/actual new
node sets are empty; no deferral or transfer and custody remains unchanged.

Original ProcHammerBro $C9D8 calls SpawnHammerObj $BA94 at $C9FC and
continues at $C9FF. Both failures reload ObjectOffset and clear carry;
success reloads it, stores parent/current hammer state/control and sets
carry. The shared C helper returns the same carry byte and the caller
consumes it to set enemy bit 3 or decrement the newly set throw timer.
The consumer does not re-test eligibility after the return. Dependency
table selection includes zero low bits selecting either misc slot 0 or 8.

At $CA66 the shimmy caller calls PlayerEnemyDiff $E143; $CA69 consumes
N to choose facing and walking speed. The helper's low subtraction borrow,
scratch low result, page subtraction and high sign match the shared byte
helper. Source X retains the original enemy slot and Y stays 1 before the
consumer increment. Native immutable slot and local direction preserve
those values. Both tails execute the actual current normal/defeated
movement and shared gravity/horizontal children.

Neutral `tools/reference_hammer_bro_integration_probe.c` and
`test/hammer_bro_integration_route_check.c` execute **3,072 actual ROM
roots** from restored boot state with no child substitution. Four fixture
phases (throw, timer/offscreen gate, jump, defeated) each have **768** cases,
covering all six enemy slots, nine misc allocation slots, both hard modes,
frame directions, walking timers, page ordering and low-byte borrow.
Source ABI checks **960 spawn returns**: carry clear **675**, set **285**;
allocation reasons are success **285**, misc occupied **320**, enemy
occupied **355**. Every return preserves X and selected Y. At each return
all **1,784 persistent bytes** match the pre-child state except the three
original success stores. **2,304 distance returns** check A, X, Y, scratch
low result, N and carry; signs split **1,152 / 1,152**.

Current x86/x64 real roots each match **3,072/3,072**, zero differences
over every **1,784 persistent RAM byte**, including unchanged RAM/OAM.
CPU scratch $00-$07 and stack are declared ABI exclusions; original
child return carry/sign/slot are checked separately and mapped to native
return values/consumer branches by the static audit. The routes change
**17,814 persistent bytes** in aggregate; maximum **179 instructions**.
Both widths pass focused hammer-movement-caller, hammer-chain,
normal-enemy-movement and platform-purity tests. Original OpenNT DOS16
builds/links with the existing OLDNAMES.LIB warning.

The similar-issue sweep checks both actual child seams, all allocation
blockers and nine dependency offsets, immutable/current slot use, source
subtraction borrow and sign consumption, and real movement tails. Bowser
uses the same hammer child and remains its later explicit return-audit
owner; other distance consumers remain their scoped connection tasks.
No duplicate host gameplay owner or scoped difference was found. No
product source changes or artifact refresh are needed. Raw records and
probe executable are cleaned after verification.

Historical **1,992/1,992**, exact nodes **1,480/1,992** and material
**368/487** remain unchanged. Exact feasible controls rise
**3,117 -> 3,119 / 4,323** (raw **4,342**, infeasible **19**).
T64 remains open with **62 Cohort-J controls**, zero pending material.
Next source-order group is normal/defeated/jumping movement return
integration. T65 is not admitted.

## Aggregate S41 admission - shared movement return integration

S41 owns `control-03827`, `control-03828`, `control-03829`,
`control-03831`. The 27 exact scoped labels are XSpeedAdderData,
RevivedXSpeed, MoveNormalEnemy, FallE, MEHor, SlowM, SteadM, AddHS,
ReviveStunned, SetRSpd, MoveDefeatedEnemy, ChkKillGoomba, NKGmba,
MoveJumpingEnemy, MoveD_EnemyVertically, MoveFallingPlatform, ContVMove,
MoveJ_EnemyVertically, SetHiMax, SetXMoveAmt, ImposeGravitySprObj,
MoveEnemyHorizontally, MoveObjectHorizontally, SaveXSpd, UseAdder,
ExXMove, EraseEnemyObject. Expected new node set is empty.
Historical 1,992/1,992 and exact 1,480/1,992 remain unchanged; controls
enter at 3,119/4,323 and can reach 3,123/4,323, material stays 368/487.

One shared movement-entry matrix covers the contiguous $CA77-$CAFE
normal/defeated/jumping entries, all using enemy/movement.c and world
movement/gravity children; erase is the existing lifecycle dependency.
Entry selects the mode, exit is its complete return. Missing evidence is
the real gravity/horizontal return ABI beyond earlier substituted children.
S40 is predecessor; movement-counter branch is the next distinct owner.

Static audit checks state-bit precedence, exact state-five gravity force,
returned slot, state reload, signed speed-table selection, stack-saved
speed restoration, revive/erase and jumping tail. Actual ROM roots use
real children and restored boot state; x86/x64 compare persistent RAM.
All state bytes, six slots, both speed signs, timer/hard-mode/frame
selection, page/fraction boundaries and all three entries are covered.
Game-owned stack-page arrays $0110-$0115 and $0125-$012A are compared
explicitly rather than hidden by CPU-stack exclusions. Return slot,
gravity force/max and horizontal temporary speed have separate seam checks.

Owner ROM/disassembly are nonredistributable local research. Ignored
build/m2-t64-s41 owns <=40 MiB raw, 524288 steps/case and 120 seconds
total; S41 cleans raw records/probe. Neutral harness/metadata only are
tracked. Focused movement, purity and original OpenNT DOS16 link are
independent operational proof. Any scoped diff stays here for repair and
re-audit; product repairs refresh three approved EXEs. Preserve unrelated work.

## Aggregate S41 closure - shared movement returns exact

`control-03827`, `control-03828`, `control-03829`, `control-03831` are
exact. All 27 scoped labels retain exact status: XSpeedAdderData,
RevivedXSpeed, MoveNormalEnemy, FallE, MEHor, SlowM, SteadM, AddHS,
ReviveStunned, SetRSpd, MoveDefeatedEnemy, ChkKillGoomba, NKGmba,
MoveJumpingEnemy, MoveD_EnemyVertically, MoveFallingPlatform, ContVMove,
MoveJ_EnemyVertically, SetHiMax, SetXMoveAmt, ImposeGravitySprObj,
MoveEnemyHorizontally, MoveObjectHorizontally, SaveXSpd, UseAdder,
ExXMove, EraseEnemyObject. Expected/actual new node sets are empty;
no deferred labels or transfers and existing custody remains unchanged.

Static $CA77-$CAFE and shared enemy/movement.c agree on state-bit
precedence (bit 6, bit 7, bit 5, low-state branches), exact state-five
force $20 versus ordinary $3D, state reload after gravity, state-two
horizontal tail, PowerUp exception, signed speed-adder indexing,
revival/Goomba erase and defeated/jumping tails. Native saved speed
corresponds to source PHA/PLA, with no mutation of it by the actual child.
Both child adapters select slot+1 and restore original ObjectOffset X;
native immutable slot preserves that same identity. Jumping force is $1C
and all three gravity routes use maximum $03.

Neutral `tools/reference_enemy_movement_integration_probe.c` and
`test/enemy_movement_integration_route_check.c` execute **9,216 actual
ROM roots**, with real gravity, horizontal and erase children. Normal
entry contributes **6,144**, defeated and jumping **1,536 each**.
Every entry covers all **256 state values** in all six slots; normal
states have four signed-speed/timer variants. Fixtures vary hard mode,
frame phase, object ID, fractional position/force and page boundaries.
Restored boot state is used per case; maximum **126 instructions**.

Original return observations are **$CA9B: 3,360**, **$CAC4: 4,968**,
**$CAE8: 2,304**, **$CAFC: 1,536**. All preserve the enemy slot. Gravity
returns separately check force and maximum. Force observations are
**$1C: 1,536 / $20: 30 / $3D: 5,634**. Horizontal AddHS seams check
the actual temporary table-adjusted speed and returned fractional/integer
displacement before the caller restores the original speed. Source and
current native control/table contracts have no scoped difference.

Current x86/x64 each match **9,216/9,216**, zero differences over all
**1,796 persistent bytes**. This includes both six-byte game arrays
**$0110-$0115 and $0125-$012A** inside the lower stack page; their initial
values are nonzero and **32 actual erase calls** clear both selected
entries. Scratch $00-$07 and the remaining CPU-stack bytes are declared
ABI exclusions, not exclusions of those game-owned aliases. Original
return X/force/max/speed/displacement checks are separate seam evidence.
The focused test manifest uses the existing normal-enemy-movement,
vertical-adapters, gravity and platform-purity tests; all **4/4** pass on
both widths. There is no separate jumping-enemy-movement CTest name;
the real jumping routes and vertical-adapters cover that admission intent.
Original OpenNT DOS16 compiles/links with its existing OLDNAMES.LIB warning.

The similar-issue sweep checks all four movement returns, exact-state
force selection, native/source saved speed, byte carry/page propagation,
state reload and erase's eight stores including its two lower-stack
aliases. No host gameplay copy or scoped mismatch exists. No product
source changed, so EXEs remain the previous delivery. Raw records and
probe executable are cleaned after accepted verification.

Historical **1,992/1,992**, exact nodes **1,480/1,992**, material
**368/487** remain unchanged. Exact feasible controls rise
**3,119 -> 3,123 / 4,323** (raw **4,342**, infeasible **19**).
T64 remains open with **58 Cohort-J controls**, zero pending material.
The next source-order branch is green paratroopa/platform X-counter
horizontal-return integration. T65 is not admitted.

## Aggregate S42 admission - X-counter horizontal result return

S42 owns `control-03834` MoveEnemyHorizontally-to-XMRight. Fifteen
already-exact labels in scope are MoveFlyGreenPTroopa, YSway, NoMGPT,
XMoveCntr_GreenPTroopa, XMoveCntr_Platform, NoIncXM, IncPXM, DecSeXM,
MoveWithXMCntrs, XMRight, MoveEnemyHorizontally, MoveObjectHorizontally,
SaveXSpd, UseAdder, ExXMove. Expected new node set is empty. Historical
1,992/1,992 and current nodes 1,480/1,992 remain unchanged; controls
enter 3,123/4,323 and can reach 3,124/4,323; material stays 368/487.

Entry is the X-counter mover $CB66, also exercised through its green
wrapper $CB25; exit is the completed horizontal result save/counter restore
and wrapper frame/Y continuation. Shared owners are enemy/x_counter.c,
enemy/green_paratroopa.c and world/movement.c. Missing evidence is the
real horizontal returned A beyond earlier substituted child results.
S41 precedes this distinct counter owner; Bloober distance follows.

Static proof checks direction/temporary negated counter, source PHA/PLA,
returned X/A, scratch $00 save and wrapper frame/Y overwrite. Actual ROM
roots restore boot state and execute real children. Native x86/x64 compare
all persistent RAM plus $00 and declared lower-stack game aliases.
Six slots, all secondary bytes/both directions, fraction/page carry,
counter endpoints and wrapper frame branches are exercised. Focused
green-counter/purity tests and original OpenNT DOS16 form operational proof.

Owner ROM/disassembly are nonredistributable local research. Ignored
build/m2-t64-s42 owns <=24 MiB raw, 524288 steps/case and 120 seconds;
S42 cleans raw records/probe. Only neutral tools and summaries are tracked.
Any scoped mismatch stays here for repair/re-audit; product repairs refresh
three approved EXEs. Preserve unrelated work; T64 remains open.

## Aggregate S42 closure - X-counter result return exact

`control-03834` is exact. All fifteen scoped labels retain exact status:
MoveFlyGreenPTroopa, YSway, NoMGPT, XMoveCntr_GreenPTroopa,
XMoveCntr_Platform, NoIncXM, IncPXM, DecSeXM, MoveWithXMCntrs,
XMRight, MoveEnemyHorizontally, MoveObjectHorizontally, SaveXSpd,
UseAdder, ExXMove. Expected/actual new node sets are empty; no deferral,
transfer or custody change.

Static $CB66-$CB86 and shared enemy/x_counter.c agree on saving the
original secondary, two's-complement temporary speed when primary bit 1
is clear, facing 1/2, real horizontal call at $CB7E and return $CB81,
STA $00 before restoring secondary via PLA/STA. The current return byte
and saved local are those same handoffs. Original horizontal wrapper
restores ObjectOffset X; native immutable slot preserves it. Green $CB25
first updates counters, then calls this mover and finally applies its
every-fourth-frame Y change, with the same optional $00 overwrite.

Neutral `tools/reference_x_counter_integration_probe.c` and
`test/x_counter_integration_route_check.c` execute **4,608 actual ROM
roots** from restored boot state, with real counter and horizontal
children, no substituted results. **3,072 direct mover** fixtures cover
every secondary byte with both directions in all six slots; **1,536 green
wrapper** fixtures add counter endpoints 0/$13/$ff, primary 0/1/$fe/$ff,
frame/Y branches, fractional carry and page 0/1/$ff boundaries.
Maximum **89 instructions** per route.

The source observes **4,608 horizontal returns**, **4,608 $00 saves** and
**4,608 secondary restorations**. Return X/A and temporary speed/facing
are checked explicitly before the consumer; the source $00 save and
restored byte are then checked after their instructions. Direction counts
are **2,304/2,304**; zero/positive/negative displacements are
**354/1,464/2,790**.

Current x86/x64 each match **4,608/4,608**, zero differences over
**1,797 compared bytes**: all 1,784 non-stack persistent bytes, twelve
lower-stack game aliases and **$00**. Other transient scratch $01-$07
and CPU-stack bytes are explicit ABI exclusions. Including $00 proves
the return value is handed to its consumer, not merely final coordinates.
Both widths pass green-paratroopa-counters and platform-purity tests;
original OpenNT DOS16 builds/links with its existing OLDNAMES.LIB warning.

Similar-issue review finds green and X-platform callers using the same
counter/mover owner. No duplicate host movement implementation exists.
Platform's $0E limit remains its existing platform-node proof and later
platform connection scope; this S does not infer an unobserved outer
platform edge. No scoped difference or product source change exists;
EXEs remain the prior delivery. Raw records/probe executable are cleaned.

Historical **1,992/1,992**, exact nodes **1,480/1,992**, material
**368/487** remain unchanged. Exact feasible controls rise
**3,123 -> 3,124 / 4,323** (raw **4,342**, infeasible **19**).
T64 remains open with **57 Cohort-J controls**, zero pending material.
Next source-order group is Bloober player-distance result/return
integration. T65 is not admitted.

## Aggregate S43 admission - Bloober distance sign and carry return

S43 owns `control-03835` PlayerEnemyDiff-to-FBLeft. Eighteen exact
scoped labels are BlooberBitmasks, MoveBloober, FBLeft, SBMDir,
BlooberSwim, SwimX, LeftSwim, MoveDefeatedBloober, ProcSwimmingB,
BSwimE, SlowSwim, NoSSw, ChkForFloatdown, Floatdown, NoFD,
ChkNearPlayer, PlayerEnemyDiff, MoveEnemySlowVert. Expected new node
set is empty. Historical 1,992/1,992 and exact nodes 1,480/1,992 stay
unchanged; controls enter 3,124/4,323 and can reach 3,125/4,323;
material remains 368/487.

Entry is MoveBloober $CB89 and exit is completed swim/coordinate movement
or defeated gravity return. Shared owners are enemy/bloober.c,
enemy/distance.c and movement/gravity children. Missing evidence is the
real distance return and carry consumption beyond earlier child-boundary
proof. S42 precedes this owner; Firebar returns form the next branch.

Static proof audits low borrow/page SBC, returned X/Y/A/N/C, facing and
preserved carry through the float-state/timer branch into ADC $10.
The source movement dispatcher ASL for ID 7 supplies entry carry zero;
controlled root fixtures reproduce that original CPU input. Actual ROM
roots execute all children. Native x86/x64 compare persistent RAM plus
$00 and lower-stack game aliases. Six slots, all page/Y bytes, equal/next
player pages and low borrow, both hard masks, odd/even direction paths,
PRNG gates, swim counters/timers/frame phases and defeated routes are covered.

Owner ROM/disassembly are nonredistributable local research. Ignored
build/m2-t64-s43 owns <=16 MiB raw, 524288 steps/case and 120 seconds;
S43 cleans records/probe. Neutral tools/summaries alone are tracked.
Focused Bloober/purity tests and original OpenNT DOS16 are operational
proof. Scoped diff stays here for repair/re-audit; product repairs refresh
three approved EXEs. Preserve unrelated work; T64 remains open.

## Aggregate S43 closure - Bloober distance/carry return exact

`control-03835` is exact. All eighteen scoped labels retain exact status:
BlooberBitmasks, MoveBloober, FBLeft, SBMDir, BlooberSwim, SwimX,
LeftSwim, MoveDefeatedBloober, ProcSwimmingB, BSwimE, SlowSwim,
NoSSw, ChkForFloatdown, Floatdown, NoFD, ChkNearPlayer,
PlayerEnemyDiff, MoveEnemySlowVert. Expected/actual new node sets are
empty; no deferral or transfer and custody remains unchanged.

Static $CB89-$CC35 and shared Bloober/distance code agree on PRNG
mask/direction eligibility, odd-slot player direction and carry one,
even-slot distance call $CBA4 returning at $CBA7, sign-to-facing and
low-byte borrow/page subtraction. The page-SBC carry is independent of
the sign byte. Native unsigned page comparison includes the low borrow,
including page $ff versus $ff plus borrow (comparison against 256).
The source's float-state AND, timer LDA/branch and Y LDA retain that carry
until **$CC2B ADC $10**, with no CLC. Current swim's near_y includes
the same carry before byte wrapping and the player-Y comparison. Other
directions retain original dispatcher entry carry zero or odd-slot LSR one.

Neutral `tools/reference_bloober_integration_probe.c` and
`test/bloober_integration_route_check.c` execute **3,072 actual ROM
roots** with real distance/swim/defeated gravity children, no substitution.
Each of six slots has 256 focused near-player cases and 256 mixed cases.
Fixtures cover every page/Y byte, equal/next player pages and page wrap,
low borrow, hard-mask and PRNG eligibility, odd/even slot directions,
four swim counter states, timer/frame paths and defeated movement.
The original ID-7 movement-dispatch ASL carry-zero input is reproduced
at the controlled root; boot machine state is restored per case.
Maximum **59 instructions**.

Actual distance returns occur **888** times and check X=slot, Y=2,
A/high sign, $00/low and C. Carry clear/set counts are **501/387**;
positive-or-zero/negative signs are **384/504**. Near-player ADC
executes with input C=0 **777** times and C=1 **1,167** times; output
A and carry are checked immediately after the original instruction.
Thus this is both a direction and a carry-consumer proof.

Current x86/x64 each match **3,072/3,072**, zero differences across
**1,797 compared bytes**, including $00, every non-stack persistent byte
and the twelve lower-stack game aliases. Other transient scratch and
CPU-stack bytes are explicit ABI exclusions; source return sign/carry/slot
and ADC output checks are separate seam evidence. Focused Bloober movement
and platform-purity tests pass on both widths. Original OpenNT DOS16
builds/links with its existing OLDNAMES.LIB warning.

Similar-issue review checks all three carry origins (dispatcher, odd slot,
distance return), page/low borrow, both mask entries, source carry-preserving
float branches and shared defeated gravity owner. No host duplicate or
scoped difference exists. Product source and EXEs remain unchanged.
Raw records/probe executable are cleaned after accepted proof.

Historical **1,992/1,992**, exact nodes **1,480/1,992**, material
**368/487** remain unchanged. Exact feasible controls rise
**3,124 -> 3,125 / 4,323** (raw **4,342**, infeasible **19**).
T64 remains open with **56 Cohort-J controls**, zero pending material.
Next source-order branch is Firebar position/draw/injury returns.
T65 is not admitted.

## Aggregate S44 admission - Firebar real child returns

S44 owns `control-03837`, `control-03839`, `control-03844`,
`control-03845`. The 36 scoped labels are FirebarPosLookupTbl,
FirebarMirrorData, FirebarTblOffsets, FirebarYPos, ProcFirebar, SusFbar,
SkpFSte, SetupGFB, SetMFbar, DrawFbar, NextFbar, SkipFBar,
DrawFirebar_Collision, AddHA, SubtR1, ChkFOfs, VAHandl, AddVA,
SetVFbr, FirebarCollision, AdjSm, BigJp, FBCLoop, ChkVFBD, ChkFBCl,
Chk2Ofs, ChgSDir, SetSDir, NoColFB, GetFirebarPosition, GetHAdder,
GetVAdder, GetEnemyOffscreenBits, RelativeEnemyPosition, DrawFirebar,
InjurePlayer. Thirty-three are exact; the three generic position/drawing
children remain needs-evidence under their later owners. Expected node
promotions are empty; no inference of their unobserved generic paths.
Historical 1,992/1,992 and nodes 1,480/1,992 stay unchanged; controls
enter 3,125/4,323 and can reach 3,129/4,323; material stays 368/487.

Entry ProcFirebar $CD3C reaches real offscreen, spin, relative, position,
draw/collision, injury and return. Shared owners are enemy/firebar.c,
firebar_children.c, OAM position/firebar and shared player injury/palette.
The missing evidence is real descendant return/consumer behavior beyond
earlier substituted child records. S43 is predecessor; flying Cheep-Cheep
movement returns follow. Child status/custody stays with its existing owner.

Static audit checks offscreen return slot/mask, relative returned X position
used by residual lookup, OAM Y preservation, injury loop/OAM stack saves
and guard/active/death continuation. Actual ROM roots restore boot state
and execute every child; native x86/x64 bind the same local PRG data and
compare persistent RAM/OAM including lower-stack game aliases. $00 loop
counter is compared on entered drawing paths; early-offscreen query scratch
is explicitly child-owned, not silently treated as persistent. Fixtures
cover short/long bars, six slots, phase/spin/timer/offscreen, small/big
players, injury/star gates and real palette/death output.

Owner ROM/disassembly are nonredistributable local research. Ignored
build/m2-t64-s44 owns <=8 MiB raw, 524288 steps/case, 120 seconds total;
S44 cleans raw records/probe. Neutral tools/summaries only are tracked.
Focused Firebar/spin/purity and original OpenNT DOS16 are operational
gates. Any scoped difference stays here for bounded repair/re-audit;
product repair refreshes three approved EXEs. Preserve unrelated work.

## Aggregate S44 closure - real Firebar return integration

The four admitted returns control-03837/03839/03844/03845 are exact.
All 36 admitted labels retain their incoming status: 33 exact, with
GetEnemyOffscreenBits, RelativeEnemyPosition and DrawFirebar still
needs-evidence under later generic owners. No node credit or custody transfer.

Static $CD3C-$CED4 comparison preserves offscreen-before-relative order,
relative A consumed by residual lookup, immutable PRG table binding,
center/segment OAM output, and loop/OAM saves around guarded injury.
Return checks at $CD3F/$CD6F/$CE0B/$CE82 observe restored slot/mask,
relative A, unchanged drawing X/Y, and injury X=ObjectOffset on every
exit, including invincibility. The source reloads X even on the guard exit;
the probe was corrected to reflect that instruction rather than assume X=0.
$CE85 also receives no-injury paths, so its saved-loop check applies only
after an observed $CE7F call. Neither probe correction changes product C.

The 512 real ROM roots execute 368 visible paths, 3,312 drawing returns,
102 injury returns and 102 loop restores. Injury cases include 69 guarded,
11 deaths and 22 demotions. Six slots, short/long bars, phase/spin/timer,
screen boundaries, player size/crouch, star/injury gates and palettes are
covered. Both current x86/x64 runners match 512/512 with zero differences.
Each compares 1,796 persistent bytes (including OAM and twelve lower-stack
game aliases), plus $00 on visible paths. Other scratch and CPU stack are
explicit ABI exclusions; return-register and OAM/loop consumers are checked
separately at real source seams. This does not certify unobserved generic
position/drawing paths.

Focused Firebar, spin and platform-purity tests pass 3/3 per width. Fresh
C90 checker builds and the original OpenNT DOS16 link pass; the pre-existing
OLDNAMES.LIB warning remains. Audio/pause/purity checks also pass 7/7 per
width. No product source changes or artifact refresh: current three EXEs
continue to include the committed audio, title and focus-pause fixes.

Similar-issue sweep checks all four returns, skipped-injury convergence,
invincibility/death/demotion exits, OAM saves, loop restoration and long-bar
second OAM selection. No scoped difference or platform gameplay duplicate
was found. Raw records and probe executable are cleaned after acceptance.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487 remain
unchanged. Exact feasible controls rise 3,125 to 3,129/4,323 (raw 4,342,
infeasible 19). T64 remains open with 52 Cohort-J controls, zero pending
material. Next source-order chain is Flying Cheep movement returns;
T65 is not admitted.

## Aggregate S45 admission - Flying Cheep real movement returns

S45 owns control-03846/03847: MoveEnemyHorizontally and SetXMoveAmt
return to FlyCC. Nine scoped labels, all already exact, are
PRandomSubtracter, FlyCCBPriority, MoveFlyingCheepCheep, FlyCC,
AddCCF, BPGet, MoveEnemyHorizontally, SetXMoveAmt and
MoveJ_EnemyVertically. Expected new nodes are empty; historical
1,992/1,992 and nodes 1,480/1,992 stay unchanged. Controls enter
3,129/4,323 and can reach 3,131/4,323; material remains 368/487.

Entry $CEDF through $CF24 is shared enemy/flying_cheep.c, with shared
world/movement.c, enemy/movement.c and world/gravity.c descendants.
S44 is predecessor; Lakitu distance-return chain follows. Existing node
custody is retained. Missing evidence is real movement return and consumer
behavior beyond prior child-substituted records.

ROM logic track audits live/defeated call order, return X=ObjectOffset,
$0d force/$05 maximum parameters, fractional/page movement and real
high-nibble/table-adjacent priority consumer. Real ROM roots and current
x86/x64 bind the same immutable owner PRG and compare persistent RAM and
lower-stack game aliases, plus declared live scratch. Fixtures cover six
slots, signed speeds, force carries, vertical saturation and defeated tail.
Operational track builds C90 checkers, focused movement/frenzy/purity tests
and original OpenNT DOS16. Any scoped diff remains here for repair/re-audit;
product changes refresh all three approved EXEs.

Owner ROM/disassembly are nonredistributable local research only. Ignored
build/m2-t64-s45 contains raw output <=8 MiB, 524288 steps/case,
120 seconds total; S45 owns cleanup. Only neutral harness/summary is tracked.
Preserve unrelated changes; no generic node promotion or T65 admission.

## Aggregate S45 closure - real Flying Cheep movement returns

Both control-03846/03847 are exact. All nine admitted labels remain exact:
PRandomSubtracter, FlyCCBPriority, MoveFlyingCheepCheep, FlyCC,
AddCCF, BPGet, MoveEnemyHorizontally, SetXMoveAmt and
MoveJ_EnemyVertically. No new node credit or ownership transfer.

Static $CEDF-$CF24 audit preserves state-bit-5 defeated tail, horizontal
then gravity order, source $0d force/$05 maximum, restored ObjectOffset,
high-nibble indexed reads including table-adjacent PRG bytes, signed
absolute subtraction, strict below-eight force update and priority output.
Horizontal returned displacement A is observed at $CEF0 then overwritten
by the caller's next LDY/LDA; gravity return at $CEF7 restores the slot
before the force/Y consumer. Native C retains the slot argument and shared
RAM outputs rather than exposing dead CPU registers.

The 1,536 actual ROM roots cover six slots with 224 live and 32 defeated
cases each. Real horizontal/gravity returns occur 1,344 times each; defeated
tail occurs 192 times. Horizontal displacement zero/positive/negative counts
are 48/720/576. Absolute difference below-eight/other counts are 108/1,236;
all 16 priority indices occur. Maximum root execution is 115 instructions.
All descendants execute without substitutions. Both freshly built current
x86/x64 runners match 1,536/1,536, zero differences across 1,800 bytes:
all non-stack persistent RAM, OAM and twelve lower-stack game aliases,
plus $00/$01/$02/$07. Scratch $03-$06 and CPU stack are explicit exclusions.
Return-register, parameter and indexed-consumer checks are separate source
seam evidence. ROM bytes remain local, bound through the immutable PRG view.

Each native width passes focused flying-cheep-movement, flying-cheep-smoke
and platform-purity 3/3. C90 current runners and the original OpenNT DOS16
build/link pass, retaining the existing OLDNAMES.LIB warning. Similar-issue
sweep checks both live return slots, horizontal carry/page effects, defeated
gravity parameters, saturated speed/force and adjacent-data consumer. No
scoped discrepancy or host gameplay duplicate was found. Product C and
three delivered EXEs remain unchanged. Raw records/probe are cleaned.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487
remain unchanged. Exact feasible controls rise 3,129 to 3,131/4,323
(raw 4,342, infeasible 19). T64 remains open with 50 Cohort-J controls,
zero pending material; next source-order chain is Lakitu distance return.
T65 is not admitted.

## Aggregate S46 admission - Lakitu real distance return

S46 owns control-03849 PlayerEnemyDiff -> PlayerLakituDiff. Scope is
LakituDiffAdj, MoveLakitu, ChkLS, Fr12S, LdLDa, SetLSpd, SetLMov, PlayerLakituDiff, ChkLakDif, SetLMovD, ChkPSpeed, ChkSpinyO, ChkEmySpd, SubDifAdj, SPixelLak, ExMoveLak, PlayerEnemyDiff, MoveEnemyHorizontally, MoveD_EnemyVertically. All 19 labels are already exact; expected new nodes
are empty. Historical 1,992/1,992 and current nodes 1,480/1,992 stay
unchanged; feasible controls enter 3,131/4,323 and can reach 3,132/4,323;
material remains 368/487. No custody transfer.

Entry PlayerLakituDiff $CF6C-$CFDC plus outer MoveLakitu $CF28
executes real shared distance and movement descendants. Owners are
shared enemy/lakitu.c, distance.c, movement.c and world movement/gravity.
S45 precedes; Bowser bridge movement returns follow. The missing proof
is real distance return and caller consumption beyond substituted records.
Static track checks low/page borrow, returned A/N/X/Y, absolute-low clamp,
Lakitu direction-change deceleration, Spiny adjustment selection and exact
subtraction-loop count. Actual ROM/native routes compare persistent RAM,
$00-$03 and lower-stack game aliases, plus direct return A. Six slots and
outer normal/special/defeated branches are included. Focused current x86/x64,
platform purity and original OpenNT DOS16 form the operational track.

Owner-local nonredistributable ROM/ASM are research only; ignored
build/m2-t64-s46 owns <=8 MiB raw, 524288 steps/case, 120 seconds,
and cleans records/probe at closure. A scoped discrepancy stays here for
repair/re-audit. Product repairs refresh all three approved EXEs; preserve
unrelated changes and do not admit T65.

## Aggregate S46 closure - real Lakitu distance return

Control-03849 is exact. All 19 admitted labels retain exact status:
LakituDiffAdj, MoveLakitu, ChkLS, Fr12S, LdLDa, SetLSpd,
SetLMov, PlayerLakituDiff, ChkLakDif, SetLMovD, ChkPSpeed,
ChkSpinyO, ChkEmySpd, SubDifAdj, SPixelLak, ExMoveLak,
PlayerEnemyDiff, MoveEnemyHorizontally and MoveD_EnemyVertically.
No new nodes or custody transfers.

Static $CF28-$CFDC and $E143 distance child audit preserves low-byte
subtraction/borrow, page result A/N, unchanged X/Y at $CF71, sign-to-low
absolute conversion, $3c clamp, direction-change deceleration and early
return. Adjustment index predicates include player speed/scroll, Spiny ID
and vertical-speed alias; the decrement loop executes distance+one times.
The outer path loads the three adjustment bytes, consumes returned speed,
sets direction and performs real horizontal movement; special/defeated
states retain their original movement tails. Native retained slot replaces
CPU X, and the returned page byte feeds the exact source BPL predicate.

Real ROM roots total 1,920: 1,536 direct PlayerLakituDiff and 384 outer
MoveLakitu. They observe 1,824 real distance returns with sign clear/set
708/1,116 and borrow clear/set 1,014/810. Clamp executes 1,266 times;
198 speed-decrement branches return early. Adjustment index 0/1/2 counts
are 942/576/108; pixel loop executes 22,326 times. Outer normal/special/
defeated counts are 288/48/48, across all six slots. Maximum root execution
is 190 instructions. Branch counters use decoded instruction addresses,
not operand-byte addresses.

Fresh current x86/x64 each match 1,920/1,920, zero differences across
1,800 RAM bytes and direct returned A. Compared bytes include $00-$03,
all non-stack persistent RAM/OAM and twelve lower-stack game aliases.
Other scratch $04-$07 and CPU stack are explicit exclusions. Source return
register/flag checks independently cover the distance seam; no child is
substituted. Focused Lakitu movement, Lakitu/Spiny and platform-purity
pass 3/3 on each width. C90 runners and original OpenNT DOS16 build/link
pass with the existing OLDNAMES.LIB warning. No game source or product
EXE changes. Raw records/probe executable are cleaned after acceptance.

Similar-issue sweep covers both borrow/sign directions, low wrapping,
clamp boundary, zero/wrapped deceleration, three indices, adjustment loop
and outer state tails. No scoped discrepancy or host gameplay copy found.
Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487
remain unchanged. Exact feasible controls rise 3,131 to 3,132/4,323
(raw 4,342, infeasible 19). T64 remains open with 49 Cohort-J controls,
zero pending material; Bowser bridge movement returns follow. T65 is
not admitted.

## Aggregate S47 admission - bridge vertical and initialization returns

S47 owns control-03850/03853: MoveEnemySlowVert -> MoveD_Bowser
and InitVStf -> RemoveBridge. Scoped labels are BridgeCollapseData, BridgeCollapse, SetM2, MoveD_Bowser, RemoveBridge, NoBFall, MoveEnemySlowVert, SetMdMax, SetXMoveAmt, InitVStf, RemBridge, MoveVOffset, BowserGfxHandler.
All 13 are already exact; expected node promotions empty. Historical
1,992/1,992, exact nodes 1,480/1,992 and material 368/487 stay
unchanged; feasible controls enter 3,132/4,323 and can reach 3,134/4,323.
No ownership transfer. S46 precedes; normal Bowser control returns follow.

Shared bridge.c owns $CFEC-$D060, with real shared movement/gravity,
area/block_metatile.c, init_targets.c and Bowser OAM descendants.
Static track checks restored slot after slow gravity, source force/max,
bridge countdown, preserved VRAM Y, last-section InitVStf return A/X,
state $40 and fall sound before drawing. Original-ROM and native roots
execute real descendants; compare persistent RAM/OAM and lower-stack
aliases plus documented live scratch. Six slots, signed vertical speeds,
force carry/saturation, bridge offsets, timer and last-section paths are
covered. Focused x86/x64 bridge/purity and original OpenNT DOS16 are
operational gates. Scoped differences stay here for repair and repeated
proof; broader unobserved nodes gain no inferred credit.

Owner-local ROM/ASM are nonredistributable research only. Ignored
build/m2-t64-s47 owns <=8 MiB raw, 524288 steps/case, 120 seconds,
and cleanup. Any product repair refreshes all three approved EXEs.
Preserve unrelated changes; T64 remains open and T65 is not admitted.

## Aggregate S47 closure - real bridge vertical/init returns

Control-03850/03853 are exact. The 13 scoped labels retain exact status:
BridgeCollapseData, BridgeCollapse, SetM2, MoveD_Bowser, RemoveBridge,
NoBFall, MoveEnemySlowVert, SetMdMax, SetXMoveAmt, InitVStf,
RemBridge, MoveVOffset and BowserGfxHandler. No node credit or custody
transfer. This scoped proof does not infer unobserved generic descendants.

Static $CFEC-$D060 audit and current shared owners preserve the slow
vertical return at $D012, force $0f/max two, ObjectOffset reload and real
drawing tail. Bridge removal decrements the feet timer, toggles body control,
selects the original low-address table, writes real VRAM metatile data,
retains Y for MoveVOffset, increments collapse index and sets blast/shatter
sounds. At index fifteen, real InitVStf returns at $D056 with A=0 and
restored slot, clearing speed/force; source state $40 and fall sound $80
precede real drawing. Source stack/CPU registers are represented by explicit
slot arguments and shared RAM, without platform logic.

576 real ROM roots comprise 384 direct MoveD_Bowser and 192 bridge roots
across six slots. They observe 384 slow vertical returns, 12 final-section
initialization returns and 576 actual Bowser drawing entries. All gravity,
metatile, offset, initializer and drawing descendants execute without
substitutions. Maximum root execution is 976 instructions. Signed speed,
force/fraction carry, saturation, both body phases, all fifteen bridge offsets,
VRAM offset choices and expired/unexpired feet timers are represented.

Current x86/x64 each match 576/576 with zero differences across 1,796
persistent bytes, including OAM, VRAM and twelve lower-stack game aliases.
Transient drawing scratch $00-$07 and CPU stack are explicit exclusions;
return slot, gravity force/max and initialized speed/force are independently
checked at their real source seams before the drawing child overwrites
scratch. Products and oracle bind the same immutable owner-local PRG data.
This route covers the declared vertical/init handoffs, not a new generic
Bowser graphics certification.

Fresh C90 checkers and bridge-collapse/purity CTests pass 2/2 per width;
original OpenNT DOS16 builds/links with the existing OLDNAMES.LIB warning.
Similar-issue sweep checks both returns, signed vertical movement, slot
restoration, bridge VRAM Y retention, last-section reset and following
state/sound/draw consumption. No scoped difference or platform gameplay
copy found. Product C and three delivered EXEs remain unchanged. Raw
records/probe executable are cleaned after acceptance.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487
remain unchanged. Exact feasible controls rise 3,132 to 3,134/4,323
(raw 4,342, infeasible 19). T64 remains open with 47 Cohort-J controls,
zero pending material; normal Bowser control returns follow. T65 remains
unadmitted.

## Aggregate S48 admission - real Bowser control returns

S48 owns control-03855/03856/03857/03858. Scoped labels are
BowserControl, ChkMouth, FeetTmr, ResetMDr, B_FaceP, GetPRCmp, GetDToO, CompDToO, HammerChk, SetHmrTmr, SkipToFB, MakeBJump, ChkFireB, SpawnFBr, SetFBTmr, PRandomRange, RunBowser, PlayerEnemyDiff, MoveEnemySlowVert, SpawnHammerObj, InitVStf, SetFlameTimer, BowserGfxHandler. All 23 are already exact; no expected new node
credit or custody transfer. Historical 1,992/1,992, exact nodes
1,480/1,992 and material 368/487 stay unchanged; controls enter
3,134/4,323 and can reach 3,138/4,323. S47 precedes; front/rear
Bowser drawing and bounding-box returns follow.

Shared enemy/bowser.c owns $D065-$D17A, using real distance,
slow gravity, hammer allocator, vertical initializer, flame timer and
Bowser graphics descendants. Static track checks $D0B8 page/low/sign
consumption, $D117 force/max/slot, $D127 allocation result/slot and
$D145 zeroed speed/force followed by $fe launch speed. Roots cover six
slots, timer/body/frame/world gates, both distance signs, hammer allocation
success/blocked states, jump and flame/drawing continuation. Persistent
RAM/OAM and lower-stack game aliases are compared; transient scratch/CPU
stack exclusions are named, with return seams checked separately.
Focused x86/x64 control/graphics/purity and original OpenNT DOS16 form
operational evidence. Any scoped mismatch remains for repair/re-audit.

Owner-local ROM/ASM are nonredistributable research only. Ignored
build/m2-t64-s48 owns <=8 MiB raw, 524288 steps/case and 120 seconds;
S48 cleans records/probe after acceptance. Product repairs refresh all
three approved EXEs. Preserve unrelated work and do not admit T65.

## Aggregate S48 closure - real Bowser control returns

Control-03855/03856/03857/03858 are exact. All 23 scoped labels
retain exact: BowserControl, ChkMouth, FeetTmr, ResetMDr, B_FaceP,
GetPRCmp, GetDToO, CompDToO, HammerChk, SetHmrTmr, SkipToFB,
MakeBJump, ChkFireB, SpawnFBr, SetFBTmr, PRandomRange,
RunBowser, PlayerEnemyDiff, MoveEnemySlowVert, SpawnHammerObj,
InitVStf, SetFlameTimer and BowserGfxHandler. No node promotions
or custody transfers; unobserved descendant paths receive no inferred credit.

Static $D065-$D17A comparison preserves body/frame/timer/world gates,
feet reset, distance borrow/sign consumed by BPL, original-range selection,
wrapped horizontal movement, slow downward gravity and slot reload,
hammer call/return ordering, jumping vertical reset followed by $fe speed,
fire-mouth toggle and final drawing. Source return checks use $D0B8,
$D117, $D127 and $D145. Allocation returns restore X and expose selected
Y/carry; the Bowser caller intentionally ignores carry and then consumes
current-slot Y position. Native C uses explicit result and retained slot,
without invented failure branches or CPU-register persistence.

1,536 real RunBowser roots cover six slots and distance, falling/allocation,
jump and timer-pause families. Each of the four target returns executes
384 times. Distance sign clear/set is 204/180; allocation carry clear/set
267/117. Allocation success/misc-blocked/enemy-blocked counts are
117/126/141. All nine allocation slots occur (slot zero 48 times, others
42 each). Actual Bowser drawing occurs 1,536 times; maximum root execution
is 1,048 instructions. Distinct world, frame, body phase, origin/range,
flame timer and hardness values feed their original consumers.

Current freshly built x86/x64 each match 1,536/1,536 with zero differences
across 1,796 persistent bytes including OAM and twelve lower-stack game
aliases. Transient $00-$07 and CPU-stack bytes are explicit exclusions;
low/page/sign return, gravity force/max, allocation X/Y/carry and initialized
speed/force are checked at actual source seams before drawing replaces
scratch. All descendants execute rather than supplying recorded child
outputs. ROM/resource bytes remain owner-local and immutable.

Focused Bowser control, graphics and platform-purity tests pass 3/3 on
each width; C90 current runners and original OpenNT DOS16 build/link pass
with the existing OLDNAMES.LIB warning. Similar-issue sweep covers all
four real returns and consumers, both distance signs, allocation failure
classes/slots, init reset/$fe launch and shared graphics continuation.
No scoped discrepancy or host gameplay duplicate found. Product C and
three delivered EXEs remain unchanged. Raw records/probe are cleaned.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487
remain unchanged. Exact feasible controls rise 3,134 to 3,138/4,323
(raw 4,342, infeasible 19). T64 remains open with 43 Cohort-J controls,
zero pending material; front/rear Bowser graphics and box returns follow.
T65 is not admitted.

## Aggregate S49 admission - Bowser half graphics/box returns

S49 owns control-03862/03863. Seven scoped labels are
BowserGfxHandler, CopyFToR, ExBGfxH, ProcessBowserHalf,
RunRetainerObj, GetEnemyBoundBox and PlayerEnemyCollision.
All already exact; expected new nodes empty, custody unchanged.
Historical 1,992/1,992 and exact nodes 1,480/1,992 stay unchanged;
controls enter 3,138/4,323 and can reach 3,140/4,323; material 368/487.
S48 precedes; flame/explosion position returns follow.

Shared oam/bowser_gfx.c owns $D17B-$D1D0, with real retainer,
relative/offscreen/OAM, enemy bounds and player collision descendants.
Static track checks retainer return slot before state test, control ten before
box child, box return slot before collision tail, front-to-rear coordinate/
state/direction copying, saved front ObjectOffset and graphics flag reset.
Real ROM/native roots cover six front slots, rear selection, direction/body
phases, edge masking, state gates and enabled collision. Persistent RAM/OAM,
box output and lower-stack game aliases are compared; transient scratch/CPU
stack exclusions and real return consumers are explicit. x86/x64 graphics/
OAM/purity plus original OpenNT DOS16 provide operational gates.

Owner-local nonredistributable ROM/ASM remain research only. Ignored
build/m2-t64-s49 owns <=8 MiB raw, 524288 steps/case, 120 seconds,
and cleanup. Scoped differences stay here for repair/re-audit; product
repairs refresh all three approved EXEs. Preserve unrelated work; no T65.

## Aggregate S49 closure - real front/rear retainer and box returns

Control-03862/03863 are exact. Seven admitted labels retain exact:
BowserGfxHandler, CopyFToR, ExBGfxH, ProcessBowserHalf,
RunRetainerObj, GetEnemyBoundBox and PlayerEnemyCollision.
No node credit or custody transfer; no inference of unobserved generic paths.

Static $D17B-$D1D0 audit preserves active front/rear slot after retainer
return at $D1C2, state predicate, control-ten box generation and same-slot
collision tail after $D1CE. The outer routine uses source direction bit to
select wrapped rear X displacement, adds eight to Y, copies state/direction,
saves front ObjectOffset, switches to DuplicateObj_Offset, assigns Bowser
ID, runs the rear and restores front slot/graphics flag. C reloads RAM[8]
at child boundaries rather than assuming the incoming argument survived.

1,536 actual BowserGfxHandler roots span six front slots, four distinct
rear choices, facing/body phases, horizontal/page and vertical edges,
normal/defeated states, player size/status/injury/star and overlap/non-overlap
fixtures. They observe 3,072 real retainer returns (1,536 front and rear
each), 2,100 real box returns and exactly 2,100 following collision tails.
Box mask clear/set counts are 132/1,968; injury entry executes 24 times.
Maximum root execution is 1,063 instructions. All graphics, relative/
offscreen, box/clip and collision descendants execute without substitution.

Current x86/x64 each match 1,536/1,536 with zero differences across
1,833 bytes: every non-stack persistent byte, OAM/box outputs and the
full 49-byte game region $0109-$0139. Initial narrower twelve-alias
comparison was broadened and rerun on both widths before closure.
Transient scratch $00-$07 and other CPU-stack bytes are explicit exclusions;
active slot, box control and final front-slot/graphics-flag restoration are
independently checked at real source seams. Same immutable owner-local
PRG supplies resources, with no runtime emulation in the native product.

Fresh C90 checkers and graphics/OAM/platform-purity tests pass 3/3 per
width. Original OpenNT DOS16 builds/links with the existing OLDNAMES.LIB
warning. Similar-issue sweep checks front/rear slot handoff, erase/defeated
state gate, masked/visible box generation, collision tail, copied coordinates/
state and saved front slot. No scoped difference or host gameplay duplicate
found. Product C and three delivered EXEs remain unchanged. Raw records
and probe are cleaned after acceptance.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487
remain unchanged. Exact feasible controls rise 3,138 to 3,140/4,323
(raw 4,342, infeasible 19). T64 remains open with 41 Cohort-J controls,
zero pending material; flame relative/offscreen returns follow before
explosion positioning. T65 is not admitted.

## Aggregate S50 admission - flame relative/offscreen returns

S50 owns control-03864/03865. Twelve scoped labels are
ExFl, ProcBowserFlame, SFlmX, SetGfxF, FlmeAt, DrawFlameLoop, M3FOfs, M2FOfs, M1FOfs, ExFlmeD, RelativeEnemyPosition, GetEnemyOffscreenBits. Ten flame nodes are exact; RelativeEnemyPosition
and GetEnemyOffscreenBits remain needs-evidence under later generic owners.
Expected new nodes empty and custody unchanged. Historical 1,992/1,992,
exact nodes 1,480/1,992 and material 368/487 stay unchanged; controls enter
3,140/4,323 and can reach 3,142/4,323. S49 precedes; explosion position
return follows.

Shared enemy/bowser_flame.c and oam/bowser_flame_gfx.c own $D1EB-$D294.
Static track checks relative return slot/coordinates before state gate,
three-sprite OAM loop and relative X increment, offscreen return slot/mask,
and four LSR/stack-mask consumers including residual fourth-sprite hide.
Actual ROM/native roots exercise real children and compare persistent RAM,
OAM and $0109-$0139 game aliases. CPU-stack/transient scratch exclusions
and real return checks are explicit. Fixtures span six slots, full/draw-only
roots, state/timer/hardness gates, carry/page wrapping, edge masks and OAM
boundary offsets. Generic children gain no unobserved node credit.
Focused current x86/x64 flame/OAM/purity and original OpenNT DOS16 are
operational gates; scoped differences stay here for repair/re-audit.

Owner-local nonredistributable ROM/ASM are research only. Ignored
build/m2-t64-s50 owns <=8 MiB raw, 524288 steps/case, 120 seconds,
and cleanup. Product repairs refresh three approved EXEs. Preserve
unrelated work; T64 stays open and T65 is not admitted.

## Aggregate S50 closure - real flame relative/offscreen returns

Control-03864/03865 are exact. Ten admitted flame nodes remain exact:
ExFl, ProcBowserFlame, SFlmX, SetGfxF, FlmeAt, DrawFlameLoop,
M3FOfs, M2FOfs, M1FOfs and ExFlmeD. RelativeEnemyPosition and
GetEnemyOffscreenBits retain needs-evidence with their generic owners;
no inferred generic path coverage, new node credit or custody transfer.

Static $D1EB-$D294 audit preserves movement force/borrow/page and Y
selection before drawing. Relative return at $D223 restores the current
slot and exposes relative A; the following state gate executes before OAM
writes. Three sprite writes advance relative X by eight each time, using
byte-wrapped OAM Y. Offscreen return at $D268 restores the slot and exposes
full $03D1; OAM offset reload and four low-bit shifts hide the residual
fourth, third, second and first sprite in exact source order. C explicit bit
checks consume the same mask without a new geometry/range rule.

1,536 actual roots comprise 768 ProcBowserFlame and 768 SetGfxF entries,
across six slots. Real relative/offscreen returns are 1,536/768; the state
exit executes 768 times. Each low mask bit is clear/set 246/522 times.
Observed horizontal masks: $0 (228), $f (504), and $1/$3/$7/$8/$c/$e
(six each). Thus partial-edge masks and each hide branch are exercised,
including the source residual fourth-sprite hide. Maximum root execution is
258 instructions. Timer/hardness, fractional/page borrow, matched/unmatched
Y target, vertical edges, frame flip and OAM $20/$f0/$f8/$fc are included.
OAM loop wrapping and absolute-indexed tail writes that cross into adjacent
RAM are compared rather than clamped or omitted.

Fresh current x86/x64 each match 1,536/1,536 with zero differences across
1,833 bytes: non-stack persistent RAM/OAM and all 49 game bytes at
$0109-$0139. Transient scratch $00-$07 and other CPU stack are explicit
exclusions; returned slot/relative A/full mask are checked separately at
actual source seams. Both generic children execute; their broader scratch
and unobserved generic contracts remain deferred to their later owners.
The same immutable owner PRG supplies local resources only.

C90 checkers and flame/OAM/platform-purity tests pass 3/3 per width.
Original OpenNT DOS16 builds/links with the existing OLDNAMES.LIB warning.
Similar-issue sweep checks both return slots, early state exit, relative-X
consumer, wrapped OAM loop and all four mask hides. No scoped discrepancy
or host gameplay copy found. Product C and three delivered EXEs remain
unchanged. Raw records/probe executable are cleaned after acceptance.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487
remain unchanged. Exact feasible controls rise 3,140 to 3,142/4,323
(raw 4,342, infeasible 19). T64 remains open with 39 Cohort-J controls,
zero pending material; explosion relative-position return follows.
T65 is not admitted.

## Aggregate S51 admission - fireworks relative return

S51 owns control-03866. Six scoped labels: RunFireworks, SetupExpl,
FireworksSoundScore, RelativeEnemyPosition, DrawExplosion_Fireworks,
EndAreaPoints. Four retain exact; RelativeEnemyPosition and
DrawExplosion_Fireworks retain needs-evidence under generic later owners.
Expected new nodes empty; no custody transfer. Historical 1992/1992,
exact nodes 1480/1992 and material 368/487 unchanged. Controls enter
3142/4323 and can reach 3143/4323. S50 precedes; star-flag returns follow.

Shared enemy/fireworks.c owns $D295-$D2CC. Static track checks timer
byte decrement, reset/phase increment and terminal score tail; relative
return slot then Y-before-X copy and current-slot phase/OAM arguments.
Actual ROM/native roots execute real position, explosion and scoring
children across six slots, timer and three drawing phases, both players,
score carries, page/coordinate wrapping and aligned OAM boundary offsets.
Persistent RAM/OAM and all $0109-$0139 aliases are compared; scratch/CPU
stack exclusions and real return seams are explicit. x86/x64 focused tests,
platform purity and original OpenNT DOS16 provide operational evidence.

Owner-local nonredistributable ROM/ASM are research only. Ignored
build/m2-t64-s51 owns <=8 MiB raw, 524288 steps/case, 120 seconds
and cleanup. A scoped difference stays here for repair/re-audit; product
repairs refresh all three approved EXEs. Preserve unrelated work; no T65.

## Aggregate S51 closure - real fireworks relative return

Control-03866 is exact. Four scoped nodes retain exact: RunFireworks,
SetupExpl, FireworksSoundScore and EndAreaPoints. RelativeEnemyPosition
and DrawExplosion_Fireworks retain needs-evidence under generic later
owners. No new node credit, custody transfer or inferred generic coverage.

Static $D295-$D2CC audit confirms byte-decrement before nonzero branch,
reset to eight, byte-wrapped phase increment and unsigned terminal gate.
The return at $D2A8 restores ObjectOffset and relative A. The caller copies
relative Y before X, then loads current-slot OAM offset and frame before
calling DrawExplosion_Fireworks. Terminal phase disables the enemy, queues
blast sound, sets modifier +4 to five and tails into EndAreaPoints. Its
current-player score modifier and status-number descendants execute for real.

1,536 actual RunFireworks roots across six slots observe 1,410 relative
returns and 1,410 drawing calls, plus 126 terminal score tails. Drawing
phases zero/one/two occur 402/504/504 times; maximum execution is 270
instructions. Fixtures include timer zero wrapping to 255, timers one/two/
eight, phase rollover and terminal cutoff, both players, mode-dependent
score modification, decimal score carry, page/coordinate wrapping and
aligned OAM offsets $20/$f0/$f8/$fc. The real source seam checks X/relative A
on return and X/Y/frame plus both coordinate copies before drawing. No child
is replaced by a synthetic return or test stub.

Fresh current x86/x64 each match 1,536/1,536 with zero differences across
1,833 compared bytes: all persistent non-stack RAM, OAM and VRAM score
packets, plus all 49 game aliases $0109-$0139. Scratch $00-$07 and other
CPU-stack bytes are explicit ABI exclusions; generic child scratch and
unaligned/non-source fireworks OAM inputs remain with their generic owners.
Immutable owner-local PRG binds score resources, with no emulator in product.

Focused fireworks lifetime/initialization and platform-purity tests pass
3/3 on each width; fresh C90 route checkers pass on both. Original OpenNT
DOS16 builds/links with the existing OLDNAMES.LIB warning. Similar-issue
sweep checks return-slot restoration, coordinate order, frame/timer branches,
aligned OAM boundary crossing and terminal sound/score handoff. No scoped
discrepancy or platform gameplay copy found. Product C and three delivered
EXEs are unchanged; only neutral harness and audit evidence were added.
Raw records and probe executable are cleaned after acceptance.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487 remain
unchanged. Exact feasible controls rise 3,142 to 3,143/4,323 (raw 4,342,
infeasible 19). T64 remains open with 38 Cohort-J controls and zero pending
material; star-flag/end-level control returns follow. T65 is not admitted.

## Aggregate S52 admission - end-level actor child returns

S52 owns control-03867/03869/03870/03871 across the contiguous $D295-$D3AF
end-level actor family, including the preceding fireworks drawing return.
Its 26 scoped labels in source order are:
RunFireworks, SetupExpl, FireworksSoundScore, RelativeEnemyPosition, DrawExplosion_Fireworks, EndAreaPoints, StarFlagYPosAdder, StarFlagXPosAdder, StarFlagTileData, RunStarFlagObj, GameTimerFireworks, SetFWC, IncrementSFTask1, StarFlagExit, AwardGameTimerPoints, NoTTick, ELPGive, RaiseFlagSetoffFWorks, SetoffF, DrawStarFlag, DSFLoop, DrawFlagSetTimer, IncrementSFTask2, DelayToAreaEnd, StarFlagExit2, DigitsMathRoutine.
Twenty-three are already exact. DigitsMathRoutine, RelativeEnemyPosition
and DrawExplosion_Fireworks retain needs-evidence under later generic
owners. Expected new nodes empty; no custody transfer. Historical 1992/1992,
exact nodes 1480/1992 and material 368/487 stay unchanged; feasible controls
enter 3143/4323 and can reach 3147/4323. S51 precedes; piranha distance
return follows. T64 stays open; no T65 admission.

Common shared owner is the end-level actor family in enemy/fireworks.c and
star_flag.c. The same batch covers adjacent fireworks/star-flag entries that
share EndAreaPoints and position/OAM children; it reuses the accepted S51
fixture design instead of repeating separate lifecycles per leaf return.
Static track checks draw-return completion, timer decrement before score
award, digit-modifier reset between calls, player score selection, real
relative return before OAM selection, vector dispatch and flag/timer exits.
Real ROM/native roots cover six slots, fireworks phases, all valid star-flag
tasks and out-of-range exit, timer borrow/score carry, both players,
flag rise/frenzy/delay branches and wrapped OAM offsets. Compare persistent
RAM/OAM/VRAM and $0109-$0139; transient scratch/CPU-stack exclusions and
actual seam outputs are explicit. Generic unobserved contracts gain no credit.

Focused x86/x64 chain tests/purity and original OpenNT DOS16 are operational
gates. Owner-local nonredistributable ROM/ASM stay research-only. Ignored
build/m2-t64-s52 owns <=8 MiB raw, 524288 steps/case, 120 seconds and
cleanup. Scoped differences stay here for repair/re-audit. Product repairs
refresh three approved EXEs; preserve unrelated work.

## Aggregate S52 closure - real end-level actor child returns

Control-03867/03869/03870/03871 are exact. Twenty-three scoped labels retain
exact: RunFireworks, SetupExpl, FireworksSoundScore, EndAreaPoints,
StarFlagYPosAdder, StarFlagXPosAdder, StarFlagTileData, RunStarFlagObj,
GameTimerFireworks, SetFWC, IncrementSFTask1, StarFlagExit,
AwardGameTimerPoints, NoTTick, ELPGive, RaiseFlagSetoffFWorks, SetoffF,
DrawStarFlag, DSFLoop, DrawFlagSetTimer, IncrementSFTask2, DelayToAreaEnd
and StarFlagExit2. DigitsMathRoutine, RelativeEnemyPosition and
DrawExplosion_Fireworks retain needs-evidence with later generic owners.
No new node credit, custody transfer or inferred generic path coverage.

Static $D295-$D3AF audit checks the fireworks draw return at $D2BC restoring
the slot before the root RTS; the timer math return at $D331 clears all seven
modifier bytes before loading five into modifier +5; the player-selected
score math return at $D342 precedes selector formation and UpdateNumber
tail. Relative return at $D368 restores the slot before OAM lookup; the
four-sprite reverse-index loop uses source adders, wrapped OAM stepping,
absolute indexed field writes and final ObjectOffset restoration. Source
JumpEngine vectors, task guard, timer zero exit, firework digit selection,
flag rise/frenzy and interval/music delay exits are retained.

A single 1,536-case manifest includes 768 real RunFireworks and 768 real
RunStarFlagObj roots across six slots. Real explosion/timer/score/flag
returns execute 702/102/168/252 times, with seam checks for restored X and
relative A, and all-seven-byte digit-modifier clearing. Star task 0/1/2/3/4/5
fixture counts are 132/132/126/126/126/126; task five exercises the guarded
exit. Timer subtraction executes 102 times and zero timer exits account
for the remaining 24 task-two cases. Fireworks terminal tails occur 66
times; drawing phases occur 204/258/240 times. Maximum root execution is
381 instructions. Real descendants run without substituted child outputs.

Fixtures span timer borrow (001/010/100), zero/999 displays, both players,
mode-dependent decimal score carry, fireworks digit 1/3/6/other selection,
flag Y below/at/above $72, positive/zero/negative frenzy count, interval and
music gates, page wrapping and aligned OAM $20/$f0/$f8/$fc. Current x86/x64
each match 1,536/1,536 with zero differences across 1,833 compared bytes:
all non-stack persistent RAM, OAM and score VRAM output plus $0109-$0139.
Transient scratch $00-$07 and other CPU-stack bytes are explicit exclusions;
generic unobserved child contracts retain their later owner scope.

Fresh C90 checkers and fireworks/star-flag/purity tests pass 3/3 per width.
Original OpenNT DOS16 builds/links with the existing OLDNAMES.LIB warning.
Similar-issue sweep checks draw/relative slot restoration, consecutive math
modifier clearing and consumer order, vector guard, flag/interval/music
branches, OAM boundary addressing and terminal score handoff. No scoped
difference or platform gameplay duplicate found. Product C and the three
approved EXEs remain unchanged. Raw records/probe are cleaned after gates.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487 stay
unchanged. Exact feasible controls rise 3,143 to 3,147/4,323 (raw 4,342,
infeasible 19). T64 remains open with 34 Cohort-J controls, zero pending
material. The piranha distance return follows; T65 remains unadmitted.

## Aggregate S53 admission - piranha distance return

S53 owns control-03874. Seven scoped labels are MovePiranhaPlant,
ChkPlayerNearPipe, ReversePlantSpeed, SetupToMovePPlant,
RiseFallPiranhaPlant, PutinPipe and PlayerEnemyDiff. All are already exact;
expected new nodes empty, no custody transfer. Historical 1992/1992,
exact nodes 1480/1992 and material 368/487 unchanged; controls enter
3147/4323 and can reach 3148/4323. S52 precedes; vertical platform
movement/position returns follow. T64 stays open; no T65 admission.

Shared enemy/piranha.c owns $D3B0-$D40F with real enemy/distance.c child.
Static track checks returned high-byte sign, low scratch subtraction and
borrow, negative-distance two's complement and unsigned $21 threshold;
state/timer/moving/rising gates, byte speed reversal, endpoint selection,
frame/timer movement gates, endpoint equality and priority write. Actual
ROM/native roots span all six slots, low distances, high-byte signs and
borrow, then bounded state/movement variants. Persistent RAM including
scratch and all $0109-$0139 game aliases are compared; CPU-stack-only
exclusion and actual return seams are explicit. x86/x64 movement/OAM/purity
and original OpenNT DOS16 are operational gates. Scoped differences stay
here for repair/re-audit; product repairs refresh three approved EXEs.

Owner-local nonredistributable ROM/ASM remain research-only. Ignored
build/m2-t64-s53 owns <=8 MiB raw, 524288 steps/case, 120 seconds and
cleanup. Preserve unrelated work.

## Aggregate S53 closure - real piranha distance return

Control-03874 is exact. Seven scoped nodes retain exact: MovePiranhaPlant,
ChkPlayerNearPipe, ReversePlantSpeed, SetupToMovePPlant,
RiseFallPiranhaPlant, PutinPipe and PlayerEnemyDiff. No new node credit,
custody transfer or inference about unobserved generic routes.

Static $D3B0-$D40F audit confirms state/frame-timer gates precede the idle
move flag and speed sign gates. Real distance return at $D3C4 retains X,
low subtraction in $00 and borrow-adjusted page subtraction in A/N.
The caller negates only the low byte when the returned high sign is negative;
it compares this source byte magnitude against $21, without introducing a
new full-world-coordinate range test. Speed reversal is byte two's complement,
move flag increments, speed sign selects the original endpoint, frame parity
and TimerControl gate Y addition, equality clears move flag and sets $40
frame delay. Every path finally writes $20 background priority.

1,920 actual MovePiranhaPlant roots comprise 1,536 idle distance fixtures
(all 256 low-byte results in each of six slots) plus 384 bounded state,
timer and movement variants. The source observes 1,752 real distance returns;
high sign clear/set 888/864 and low borrow clear/set 912/840. At the actual
return seam X, low/high subtraction, N sign and final page-subtraction carry
are checked independently. The absolute-low-byte consumer is checked before
the threshold comparison. Near/far counts are 486/1,266, negative conversion
864, reversal 1,314, and endpoint stops 312; maximum execution 54 instructions.
No child return is stubbed. Fixtures cover $20/$21 from both directions,
page wrapping, state/timer early exits, existing movement, signed/zero/wrapped
speeds, endpoint equality/non-equality, parity, paused movement and priority.

Current x86/x64 each match 1,920/1,920 with zero differences across 1,841
compared bytes: all zero-page scratch, persistent RAM and all 49 game aliases
$0109-$0139. Only other CPU-stack bytes are excluded. This broader comparison
retains the distance/endpoint scratch itself rather than excluding it as an
ABI temporary. Same project-owned C90 checker is built on both widths;
the native product contains no reference emulator or new ROM material.

Fresh movement/OAM/platform-purity tests pass 3/3 per width. Original OpenNT
DOS16 builds/links with the existing OLDNAMES.LIB warning. Similar-issue
sweep checks subtraction borrow/sign return, low-byte magnitude threshold,
speed and move-flag wrapping, endpoint selection, timer/parity gates and
common priority exit. No scoped discrepancy or host gameplay duplicate found.
Product C and three approved EXEs remain unchanged; raw records/probe are
cleaned after governance and registry gates.

Historical 1,992/1,992, exact nodes 1,480/1,992 and material 368/487 stay
unchanged. Exact feasible controls rise 3,147 to 3,148/4,323 (raw 4,342,
infeasible 19). T64 remains open with 33 Cohort-J controls, zero pending
material; platform movement/position returns follow. T65 is not admitted.
