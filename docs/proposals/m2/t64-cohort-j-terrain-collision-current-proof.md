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
