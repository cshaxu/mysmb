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
