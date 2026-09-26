# M2 T17: Collision and world primitives

## Status

**M2 T17 active — S5/P16 and S6/P1-P8 complete; S6 route closure remains active.** T16/S2 is complete: its relative-position/offscreen writers now consume the ROM state they are given. The source-reachable demo trace proves that the next discrepancy is a producer-side 6502 carry error in `ImposeGravityBlock`/`ImposeGravity`, so this admitted task owns it before any block or OAM work proceeds.

## ROM scope

ROM lines 11085-14459: background/object collision, bounding boxes, bounds, gravity, movement, score and shared geometry. The initial executable boundary is labels `MoveEnemyHorizontally` through `ExVMove` (lines 7555-7784), specifically `ImposeGravityBlock`, `ImposeGravitySprObj`, `ImposeGravity`, and `AlterYP`.

## Existing-code disposition

Extract shared world primitives from `player.c`, `objects.c`, `area.c`, and `game.c` into `src/game/world/`. Game-route modules call those primitives in their original sequence; they do not carry duplicate arithmetic, synthetic thresholds, or platform behavior.

## Graph contract

World primitives consume caller-selected object-array offsets and RAM fields, preserve ROM byte/carry semantics, and mutate only ROM-owned shared state. They do not schedule actors, decide modes, draw OAM, or call platform code.

## Formal S breakdown

1. **S1 complete (P1) — source ownership and movement boundary.** Map lines 7555-7784 to current owners, introduce the `src/game/world/` boundary, and physically extract `MoveObjectHorizontally`/gravity-family implementations without changing their byte behavior. Evidence: build and bounded continuation trace are unchanged by an extraction-only P.
2. **S2 complete (P1-P4) — exact movement and gravity.** Translate `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `ImposeGravity`, and `AlterYP` with explicit 6502 add-with-carry state. Evidence: block, misc, fireball, and enemy traces at signed-speed/carry boundaries.
3. **S3 complete (P1-P5) — coordinate, bounding-box, and screen-edge primitives.** Translate `BoundingBoxCore`, offscreen bounding behavior, relative coordinate helpers, and screen-edge checks. Evidence: actor and object bounding-box RAM plus OAM-facing positions.
4. **S4 planned — player/background and head/block collision.** Translate the player terrain, pipe, vine, head, and block-buffer probe branches. Evidence: wall, hidden-block, question-block, pipe, and vine routes.
5. **S5 active (P1-P2) — enemy/item/projectile collision and score handoffs.** Translate ground/side/background/object branches used by enemies, power-ups, fireballs, and score paths. Evidence: mushroom bounce, stomp/damage, fireball, and score/audio traces.
6. **S6 planned — cross-slice reference closure.** Run bounded ROM-reference traces covering each S2–S5 route and prove that remaining differences are transferred only to a named source owner.

## Acceptance

Every collision and movement result names its ROM probe/table/branch. Affected RAM, block buffer, score, audio, OAM, CIRAM, palette, and PPU output match the reference routes. Platform code may not read or write these game decisions. Replaced code is removed in the same admitted P after its trace proves the replacement.
## S1 P1: block gravity ownership boundary

`ImposeGravityBlock`/`ImposeGravity` was physically extracted from `objects.c` into `src/game/world/movement.c`, with its shared game-only declaration in `src/game/world/world.h`. `BlockObjectsCore` now calls the world primitive; no platform module participates. This packet intentionally preserves the pre-existing arithmetic while assigning its ROM owner before S2 corrects it. The 600-sample title-to-demo trace is byte-for-byte unchanged from the T16/S2 baseline: first work-RAM mismatch stays sample 72 / `$03d4`, with 3,417 differing work-RAM bytes; CIRAM, palette, audio commands, and all PPU scalars remain zero-difference, and visible OAM retains its prior sample-124 mismatch. x64 and x86 each pass 78/78 CTest cases. OpenNT recompiles and links the DOS MZ through the same source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.
## S2 P1: restore `ImposeGravity` ADC carry

The original `ImposeGravity` uses the carry from `ADC SprObject_Y_Position,x` in the following `ADC $07` high-byte update. The old C inferred carry from `new_y < old_y`, which fails for `old_y + $ff + carry-in = old_y`: the low byte is unchanged but the 6502 carry is set. `movement.c` now retains the full 16-bit low-byte sum and derives carry from bit 8, preserving the source sequence without changing force, maximum-speed, or state thresholds. On the same 600-sample ROM continuation, `$03d4` and the block high-position mismatch disappear; the first work-RAM mismatch moves from sample 72 / `$03d4` to sample 82 / `$03f0`, and work-RAM differences fall from 3,417 to 2,893 bytes. CPU-RAM differences fall from 33,337 to 31,844 bytes. CIRAM, palette, audio commands, and all PPU scalars remain zero-difference; visible OAM remains at the pre-existing sample-124 mismatch. x64 and x86 each pass 78/78 CTest cases. OpenNT recompiles and links the DOS MZ through the same shared source with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.

## S2 P2: restore misc-object gravity carry

`ImposeGravity` for the misc-object array now derives the high-position carry from the full low-byte ADC sum, including the `$ff + carry-in` case. The demo trace removes `$03d6`; the first remaining work-RAM difference moves to sample 124 / `$0491`.

## S3 P1: collision primitive ownership boundary

`BlockBufferCollision` page carry, `BoundingBoxCore`, and `PlayerCollisionCore` now live in `src/game/world/collision.c`, with no compatibility symbol left on the object route. Actor modules select objects and consume collision results; the world module only mutates or compares ROM bounding-box state. The 600-sample title/demo continuation is behavior-identical to the preceding T17/S2 baseline: first work-RAM difference remains sample 124 / `$0491`, work-RAM differences remain 2,286 bytes, visible OAM differences remain 3,622 bytes, and CIRAM, palette, audio commands, and PPU scalars remain zero-difference. x64 and x86 each pass 78/78 CTest cases. The OpenNT large-model DOS MZ relinks from the same source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.

## S5 P1: restore normal-enemy collision scheduling

`RunNormalEnemies` always calls `PlayerEnemyCollision` after `EnemyToBGCollisionDet` and before its ID-specific movement branch. The prior C route skipped that call for a defeated Goomba while its interval timer was nonzero, leaving `Enemy_CollisionBits` set after Mario had moved away. The normal-enemy route now makes the collision call before its defeated-object timer branch, matching the source order. The 600-sample title/demo continuation removes the sample-124 `$0491` discrepancy and moves the first remaining work-RAM difference to sample 142 / `$0484`; work-RAM differences fall from 2,286 to 1,810 bytes. x64 and x86 each pass 78/78 CTest cases. The OpenNT large-model DOS MZ relinks from the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.

## S4 P1: move and restore LandPlyr

`CheckForClimbMTiles`, `CheckForSolidMTiles`, and `LandPlyr` now belong to the shared collision owner. `LandPlyr` clears `Player_Y_Speed`, `Player_Y_MoveForce`, `StompChainCounter`, and `Player_State` in the original order after the successful foot probe. The player route retains only its source-order foot probes and invokes the world result. The 600-sample continuation removes the sample-142 `$0484` discrepancy and moves the first remaining work-RAM difference to sample 172 / `$03ae`; work-RAM differences fall from 1,810 to 1,352 bytes. x64 and x86 each pass 78/78 CTest cases. The OpenNT large-model DOS MZ relinks from the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.

## S2 P3: generic SprObject movement seam

`movement.c` now exposes the exact downward `ImposeGravity` path and `MoveObjectHorizontally` for a caller-selected ROM SprObject offset. The primitives retain the 6502 fractional carry into Y high position and the X-to-page carry; no caller changes in this P. The direct regression binds offset seven, the offset FireballObjCore obtains with `TXA; ADC #$07`, and covers both carry boundaries. T20 may now remove its duplicate arithmetic by consuming these T17 APIs in a separate source-slice P.

## S2 P4: correct SprObject base addresses

The P3 generic seam initially used fireball-specialized array addresses as its base and then applied the supplied offset again. ROM `FireballObjCore` first makes X equal to 7, so `ImposeGravity` and `MoveObjectHorizontally` must index the common bases (`$009f/$00b5/$00ce/$0416/$0433` and `$0057/$006d/$0086/$0400`) plus that offset. The corrected regression names both the common base and offset seven; it retains the carry checks and prevents a future double-offset caller.

## S5 P2: Fireball background-collision ownership boundary

ROM $cdbf-$cddc (FireballBGCollision, BlockBufferChk_FBall, and ChkForNonSolids) now has one shared game owner: `src/game/world/collision.c`. `FireballObjCore` keeps the source call position after relative coordinates, fireball offscreen bits, and its bounding box; it delegates the full existing bottom-probe, non-solid, bounce, and explosion state path to the world API. This is an extraction-only packet: no probe offset, tile classification, state branch, or audio write changed. `FireballEnemyCollision` and its score/defeat handoff remain explicitly outside this packet because they cross the T16/T19/T15 source owners. The full x64 and x86 suites pass 79/79 each; the OpenNT DOS MZ relinks from the same shared source with its established OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.
## S5 P3: Fireball enemy-collision ownership boundary

ROM $d644-$d746 (`FireballEnemyCollision`) now has one T17 owner in `src/game/world/collision.c`. It performs the source state and alternating-frame gates, scans ordinary slots 4 down to 0, preserves every source filter and the `SprObjectCollisionCore` byte-wrap box comparison, writes `Fireball_State=$80`, then returns the ROM `$01` enemy-slot handoff. `FireballObjCore` immediately calls the existing `HandleEnemyFBallCol` effect owner with that returned slot; no state/score, Bowser, Floatey, or audio branch was altered or moved in this packet. The direct shared-core regression covers even-frame gating, descending-slot precedence, defeated-Goomba rejection, state write, and returned handoff. The following P must migrate `HandleEnemyFBallCol` only after its T16 relative-position, T19 actor-state, and T15 Floatey/audio interfaces are individually named; it may not reimplement them locally. Full x64 and x86 suites pass 79/79 each; the OpenNT DOS MZ relinks from the same shared source with its established OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.
## S5 P4: exact fireball hit-effect chain

ROM $d747-$d7a8 (`HandleEnemyFBallCol`, `HurtBowser`, `ShellOrBlockDefeat`, `ChkToStunEnemies`, and `EnemySmackScore`) now has one T17 owner in `src/game/world/collision.c`; the old simplified handler is deleted from `objects.c`. The T17 owner first calls T16's `RelativeEnemyPosition`, preserves the d7 `Enemy_Flag` proxy-to-Bowser rule, Buzzy and special-enemy exits, Bowser HP/identity/state/audio/5000-score branch, Piranha's compare-carry `ADC #$18` as `Y+$19`, `ChkToStunEnemies` demotion and water/Bloober speed branch, and `PlayerEnemyDiff` low-byte borrow followed by page subtraction. It calls a narrow Floatey consumer API that reads the prepared source `$03ae` scratch; it does not recreate screen coordinates. Direct regressions cover normal state/direction/score/audio, cross-page direction, Piranha carry, and Bowser effects. No platform module participates. Full x64 and x86 suites pass 79/79 each; the OpenNT DOS MZ relinks from the same shared source with its established OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.
## S2 P5: restore `MoveObjectHorizontally` equal-low-byte carry and move the enemy wrapper

The prior shared `MoveObjectHorizontally` translation inferred the X-byte carry from `new_x < old_x`.  That is not equivalent to the ROM `ADC $00`: for `$22 + $ff + carry-in`, the result is `$22` while carry is set.  The T17 owner now derives the carry from the full 16-bit sum before applying the signed page adder, matching `MoveObjectHorizontally` at source lines 7587–7600.  `MoveEnemyHorizontally` is now its narrow source wrapper in `world/movement.c`: it maps `ObjectOffset` to common SprObject offset `slot + 1` and calls the one primitive.  The duplicate calculation is deleted from `objects.c`; all of its former actor callers preserve their original call positions.  The direct regression covers that exact `$ff + carry-in` case and proves X remains `$22` while page `$03` remains `$03` after the ROM's `$ff + carry` page arithmetic.  Full x64 and x86 CTest suites pass 79/79 each, and the OpenNT DOS MZ relinks from the same source set with its established `OLDNAMES.LIB` warning.  This is a reopened S2 correctness packet, not an additional actor behavior change.
## S3/P2-P4: primitive boundary evidence

Three focused packets now cover the shared source primitives without moving gameplay decisions: `98daf86` verifies block-buffer page carry, equal-edge contact, and horizontal-wrap non-contact; `175a7f6` verifies the ROM vertical-wrap contact branch; `29bba97` verifies `BoundingBoxCore` control `$07` and 8-bit right-edge wrap. Each focused regression passes on x86 and x64, and each packet refreshes the three required artifacts. These are S3 evidence only; T17 remains active for the larger S4-S6 routes.
## S4 P2: preserve invisible-foot branch

ROM ChkInvisibleMTiles ($5f hidden coin and $60 hidden 1-up) returns with Z set; ChkFootMTile then branches straight to DoPlayerSideCheck before LandPlyr.  The shared mysmb_player_check_feet route had this exception only in side collision, so either foot could incorrectly land on an invisible block.  It now preserves the source branch for both left and right foot samples.  collision_regression_smoke supplies the original right-foot probe fixture for each metatile and proves that player state, Y coordinate, and Y speed remain unchanged.  The source test proves the common game layer; no platform module changes or owns the decision.  Full x64 and x86 CTest suites pass 79/79 each, including platform-purity.  The OpenNT large-model DOS MZ rebuilds from the same source list with the established OLDNAMES.LIB warning.  Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.
## S4 P3: preserve water head-collision branch

ROM HeadChk calls CheckForSolidMTiles; on a non-solid result, AreaType= branches straight to NYSpd before PlayerHeadCollision.  The shared C route had omitted that water branch and could start a block bump beneath water.  It now writes Player_Y_Speed= and leaves the collision metatile and block state intact.  collision_regression_smoke explicitly separates a ground AreaType= brick-bump fixture from a water AreaType= fixture, proving the water result does not write Block_State, alter the metatile, or arm BlockBounceTimer.  This is game-core behavior; no platform code changed.  Full x64 and x86 CTest suites pass 79/79 each, including platform-purity.  The OpenNT large-model DOS MZ rebuilds from the same source list with the established OLDNAMES.LIB warning.  Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.
## S4 P4: restore side-pipe entry sound

ROM `CheckSideMTiles -> PipeDwnS -> PlyrPipe` tests the pipe metatiles `$6c/$1f`, a grounded right-facing player, and then tests `Player_SprAttrib`.  Only when that source byte is zero does it write `Sfx_PipeDown_Injury=$10` to `Square1SoundQueue/$00ff`; it then sets the pipe attribute bit, selects `ChangeAreaTimer` `$a0/$34` from `ScreenLeft_PageLoc`, and transitions engine routine `$08` to `$02`.  The shared player route had the latter writes but omitted the sound-queue write.  It now performs the missing write in the existing source-order branch, before OR-ing `$20` into the attribute.

`collision_regression_smoke` constructs the original first-entry condition against a `$6c` side probe and proves the shared RAM results: `Player_SprAttrib=$20`, `Square1SoundQueue=$10`, `ChangeAreaTimer/$06de=$a0`, and `GameEngineSubroutine=$02`.  This is game-core logic used unchanged by DOS16, Win32 x86, and Win32 x64; no platform source changed.  Full x64 and x86 CTest suites pass 79/79, including platform-purity.  The OpenNT DOS MZ rebuilds from the same source list with the established `OLDNAMES.LIB` warning.  Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.

## S4 P5: preserve jumpspring side-stop gate

ROM `CheckSideMTiles` calls `ChkJumpspringMetatiles`; its carry-clear branch reaches `ChkPBtm`, while an identified `$67/$68` jumpspring reads `JumpspringAnimCtrl/$070e`. A nonzero controller exits the side handler; zero reaches `StopPlayerMove -> ImpedePlayerMove`. The old shared C returned for both values and therefore omitted the idle-spring wall stop. The player route now preserves the ROM ordering after hidden blocks and climbable metatiles, with the zero controller falling into the existing shared impede primitive.

`collision_regression_smoke` uses the original `$67` side probe twice: idle `$070e=0` clears collision bit d1 (`$fd`) through `ImpedePlayerMove`; active `$070e=1` leaves the freshly initialized collision mask `$ff` and horizontal speed unchanged. This remains one game-core path shared by DOS16, Win32 x86, and Win32 x64. Full x64 and x86 CTest suites pass 79/79, including platform-purity. The OpenNT DOS MZ rebuilds from the same source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.
## S4 P6: restore solid-head bump sound

ROM `HeadChk -> CheckForSolidMTiles -> SolidOrClimb` writes `Sfx_Bump=$02` to `Square1SoundQueue/$00ff` for a solid head metatile, except `$26`, which follows the climbing no-sound branch. The shared C path set `Player_Y_Speed=$01` but omitted that queue write. It now writes `$02` before the original vertical-speed update, retaining the source exception for `$26`.

`collision_regression_smoke` drives the source small-Mario head probe against `$61` with upward speed and asserts `Player_Y_Speed=$01` plus `Square1SoundQueue=$02`. This is shared game-core behavior across DOS16, Win32 x86, and Win32 x64. Full x64 and x86 CTest suites pass 79/79, including platform-purity. The OpenNT DOS MZ rebuilds from the same source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 2FCECD8A2DBE4F1DA17563EB119C58B5471A62D6258A6B88AF0ED3A6AA18A831, mysmb32.exe SHA-256 54D40E2247A21B437621369437C0976EAAB1BE9602D090EC71223B122D8F3AB0, mysmb64.exe SHA-256 E4DC43C4E34E9BF189ED632352C55E46B6FC7E1695FB0631618EFDE9C7D78E67.

## S4 P7: preserve HeadChk bounce-timer NYSpd branch

ROM `HeadChk` tests `BlockBounceTimer` after a non-solid, non-water head contact. A nonzero timer branches directly to `NYSpd`, leaves the block untouched, and writes `Player_Y_Speed=$01`. The old C skipped the bump call but returned without this required speed write. The shared game route now preserves the source branch.

`collision_regression_smoke` supplies a non-solid `$51` head probe with a live bounce timer and verifies the block state/metatile remain untouched while `Player_Y_Speed` becomes `$01`. Full x64 and x86 CTest suites pass 79/79, including platform-purity; OpenNT DOS MZ rebuilds from the same source list. Refreshed artifacts: mysmb16.exe SHA-256 9CC40A31AC5E28416FA158C26998DF2E18CC88AFFD1043DC2964D6BAABC7B08E, mysmb32.exe SHA-256 156A406C9DCFC2230070997A0E57FBDD114665BD7867AA0B8B56D43F1C2654F8, mysmb64.exe SHA-256 1FFC627CC895C2FF8233AFE06326BE44E6746AA0FC7723F833120B3189D7C150.

## S4 P8: restore land-jumpspring handoff

ROM `ChkFootMTile -> ChkForLandJumpSpring -> LandPlyr` recognizes `$67/$68` only after the foot route has rejected climbing tiles, upward motion, axes, and invisible blocks. On an idle spring and a low-nibble contact below `$05`, it writes `VerticalForce/$0709=$70`, `JumpspringForce/$06db=$f9`, `JumpspringTimer/$0786=$03`, and `JumpspringAnimCtrl/$070e=$01`, then reaches `LandPlyr`. When `JumpspringAnimCtrl` is already nonzero, the source takes `InitSteP`: it writes only `Player_State=$00`, leaving position and vertical motion for `JumpspringHandler` to own.

The shared player route now makes that exact handoff before its existing land primitive, and preserves the active-animation `InitSteP` branch for both foot samples. `JumpspringHandler` remains the sole consumer that advances `$070e` and finally copies `JumpspringForce` to `Player_Y_Speed`; no platform module owns any portion of the rule. `collision_regression_smoke` verifies the first-contact four-byte handoff and the live-animation branch's unchanged Y position, Y speed, Y force, and spring bytes. Full x64 and x86 CTest suites pass 79/79, including platform-purity. The OpenNT DOS MZ rebuilds from the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 AD36D1FBA37E16378D5EFAE6DB1F77BF4E161821687D5EE20CA8F1F0EF9295AF, mysmb32.exe SHA-256 5189FFE02018DF686F812C50A1760E89D75E6F24BA942C81ED810B823AAFEF63, mysmb64.exe SHA-256 4FBE54D9BF180C78247DD99BA6351331EBF081BDA9DDE78DA56997A1370AF017.
## S4 P9: restore late-foot-contact impediment

ROM `ChkFootMTile` tests the collision low nibble after it has rejected climbable, upward-moving, hidden, axe, and active-jumpspring routes. For `$05-$0f`, it stores `Player_MovingDir` in source scratch `$00` and jumps to `ImpedePlayerMove`; it does not call `LandPlyr`. `ImpedePlayerMove` uses the same one/two encoding supplied by the side-check counter, so this path stops and corrects the corresponding horizontal direction while retaining the player's falling state and vertical motion.

The shared player route now takes that branch for either foot sample before the jumpspring/land path. The shared impede primitive documentation identifies both valid source callers; no arithmetic or rule moved to a platform adapter. `collision_regression_smoke` drives a right-foot contact nibble `$05` with positive `Player_MovingDir` and verifies the source left correction (`X-1`), cleared X speed, side timer `$10`, collision-bit d0 clear, and untouched Y/state. Full x64 and x86 CTest suites pass 79/79, including platform-purity. The OpenNT DOS MZ rebuilds from the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 79F9B2494CF0962E61A9252119305B33E9D0CBA7267B3C892904DF086C6149CF, mysmb32.exe SHA-256 7F042DE6614700F1132FA2738A83E6A485B496D4878606B3EBF933AE6F903B60, mysmb64.exe SHA-256 AF0F00E472629A22E7E8F8922486D866B188725C3AA9BBB35500A0D001349FF8.
## S4 P10: restore vertical-pipe sound queue

ROM `HandlePipeEntry` accepts held Down with left/right foot metatiles `$10/$11`, then writes `ChangeAreaTimer=$30`, `GameEngineSubroutine=$03`, `Sfx_PipeDown_Injury=$10` to `Square1SoundQueue/$00ff`, and `Player_SprAttrib=$20` before the optional warp-zone table branch. The shared C route had every adjacent state transition but omitted the sound-queue write.

`mysmb_player_handle_vertical_pipe` now performs that source write in order between the subroutine and player-attribute writes. `player_route_smoke` drives the actual `$10/$11` and Down condition and asserts timer, engine routine, attribute, and queue byte. The shared game route is unchanged across DOS16, Win32 x86, and Win32 x64; no platform source changed. Full x64 and x86 CTest suites pass 79/79, including platform-purity. The OpenNT DOS MZ rebuilds from the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 507806656C093912F13B2245CB7B232B028E49E7C56F07B563774B63438EBCA4, mysmb32.exe SHA-256 C9D5590CC7A234C7EEE010F17D1D5DEDDBF093228D0E3D740532CF84AF9110CD, mysmb64.exe SHA-256 83075BAC0F621826FCA228710293E3BA580C315DBB24911E9C58CEB662B1156F.

## S4 P11: restore player coin sound queue

`CheckForCoinMTiles` writes `Sfx_CoinGrab=$01` to `Square2SoundQueue/$00fe` before `HandleCoinMetatile`. Player head, foot, and side collision routes now use a shared player-only handoff that performs that write before the existing metatile-removal/score owner; block-emitted jump coins retain their separate sound producer. The foot-coin regression verifies tile removal and `$00fe=$01`. x86/x64 CTest: 79/79; DOS MZ rebuilt. Artifacts: 507806656C093912F13B2245CB7B232B028E49E7C56F07B563774B63438EBCA4, C9D5590CC7A234C7EEE010F17D1D5DEDDBF093228D0E3D740532CF84AF9110CD, 83075BAC0F621826FCA228710293E3BA580C315DBB24911E9C58CEB662B1156F.

## S4 P12: restore RemoveCoin_Axe VRAM-buffer route

ROM `HandleCoinMetatile -> ErACM -> RemoveCoin_Axe` and `HandleAxeMetatile -> ErACM -> RemoveCoin_Axe` both write their two blank metatile rows at fixed `VRAM_Buffer2/$0341` through `PutBlockMetatile` with source `Y=$41`, then set `VRAM_Buffer_AddrCtrl/$0773=$06`. The previous C code incorrectly appended that work to `VRAM_Buffer1/$0301`, while the NMI commit incorrectly skipped a selected `$0341` list when `$0340` was zero. The shared game core now has distinct, explicitly named owners: ordinary block replacement retains `WriteBlockMetatile`'s buffer-one route, while coins and axes use `RemoveCoin_Axe`'s fixed buffer-two route; the shared NMI owner always commits selected address controls six/seven as the ROM does.

`core_smoke` verifies independent `$0341` blank output, `$06` selection, a zero `$0340` selected-list commit, and the separate score/tally buffer-one commands. `collision_regression_smoke` drives the actual left-foot axe route and verifies mode, speed, collision-tile removal, and the exact buffer-two command. No platform module changed.
Artifacts refreshed for this P: mysmb16.exe SHA-256 1F09A11C087352432C9BC15B6F6B0DFCAD3EC9EB575A3CE0CA8E9F0E5494466C; mysmb32.exe SHA-256 1915C97405DE7C3C90407A6F3EBD82FBE5E9C6E300F02B2CDC487D618C20B9E2; mysmb64.exe SHA-256 F59D904761A5092DE7E5C6068F17394D8D8282FD62BA67C052F521065104CBB5.

## S4 P13: restore PlayerBGCollision bottom guard

ROM PlayerBGCollision initializes Player_CollisionBits to $ff after the on-screen high-byte check, then returns before HeadChk when Player_Y_Position is $cf or higher. Both shared player call sites now establish that byte and gate the complete head/feet/side chain on the same Y < $cf condition. The focused regression drives PlayerBGCollision through mysmb_player_step at Y=$cf and proves the collision bits reset without terrain probes. x86/x64 CTest: 79/79; DOS MZ rebuilt; artifacts: A6B39A7D00077C1DBE69FC2BFDA73CE692F2C20DD91130C849E904AE57CB9C98, D3144F578C8DD7E1DDFCB17B6358B24BCE52F64D6099B32C686B9F00FA63E62D, 3ECED3EBFB9758CD3218BA1C0B885DE8C267C9BCBF005678E9B3EAE8EC2807E3.

## S4 P14: preserve AwardTouchedCoin and axe terminal branches

ROM PlayerBGCollision jumps from a head or foot scene-coin sample to AwardTouchedCoin/HandleCoinMetatile and returns, while HandleAxeMetatile also exits its frame route. The shared player owner now returns an internal terminal result only for those source exits; both normal and climbing PlayerBGCollision call sites stop later terrain probes on that result. Solid/head/water and ordinary land results retain their original continuation. Focused regression identifies terminal head coin, either foot coin, and axe results. x86/x64 CTest: 79/79; DOS MZ rebuilt. Artifacts: 233637B9153D9B163624C092BFB4712A33180530ECFDAEBFCBAD39C11BF0A288, 7C2CDBA3AC9004F2915CE72CEA51B3A94845150276FF751ECAFE7F3E8A8A4526, 979728258FC07EC6E5EA39D04BE5B8578A457AD069704F1025C5416659042D78.

## S4 P15: retain PlayerCtrlRoutine collision box through enemy processing

ROM `PlayerCtrlRoutine` performs `RelativePlayerPosition -> BoundingBoxCore -> PlayerBGCollision`; later `GameEngine` enemy handlers consume that already-produced player box.  The native Paratroopa, hammer, and shared special-enemy collision helpers incorrectly rebuilt `$04ac-$04af` after `PlayerBGCollision`, using a position that can have been corrected by the collision branch.  This altered persistent RAM despite matching visible output.

Those helpers now create only their own enemy or misc box and consume the player box unchanged. `paratroopa_smoke` supplies the PlayerCtrlRoutine-produced box and proves the collision result does not overwrite its left/right edges. A source-reachable 600-sample hidden-coin route now has zero differences in work RAM `$0300-$07ff`, CPU OAM backing, CIRAM, palette, visible OAM, audio state, and all PPU fields; the remaining zero-page/stack differences are emulator scratch state outside the translated game-owned range. x86/x64 native traces are byte-identical: `B52B4661859558B57229CB1042B27D58AF3FA38DDF8F7F62160E4B30DF3DE3E9`. Full x86/x64 CTest suites pass 79/79; OpenNT links the shared DOS MZ with its established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16 `281034243EC46E4160DE9AE883E1AA6C261D837121EF90D704FF42AE24727BE8`, mysmb32 `599FDFF075B102A29C9EB0CC540EEE01A927F633CBA992389F8E8B6C548B9713`, mysmb64 `15DB8266B65291AEA842A68180830FC33FD396B1F9B5BEFD71C91384914F68BB`.
## S4 P16: repair direct collision fixtures after primary-box ownership recovery

P15 correctly removed post-`PlayerBGCollision` writes to the player primary
box from object handlers.  Three direct-object fixtures still began at those
handlers without representing the preceding `PlayerCtrlRoutine` frame, so
`hazard-collision`, `bullet-bill`, and `hammer-bro` read uninitialised
`$04ac-$04af`.  Their shared test helper now supplies the control-0
`BoundingBoxCore` result from the configured relative player position:
`X+2`, `Y+8`, `X+14`, `Y+32`.  It changes no production source and asserts the
correct source call contract instead of reviving a synthetic object-side
producer.  Full x64 and x86 CTest suites pass 80/80, including platform purity.
The three executable artifacts remain the same shared-source T23/P1 builds:
`mysmb16` `4485D9BAA0FD7488130C91BE880BF7EA5A8A3FCE984BEED822C48D75A02DC80D`,
`mysmb32` `A5A3D6DB2124387DEC73C44E8C88BF3A4A347D4D5C029DFBA22A2FEA3931F392`, and
`mysmb64` `A6C357AE988CFC126AC6176AF1E70F4A13245582B0596FBEBC11C1A0FD4E5417`.

## S3 P5: consolidate screen-edge bounding-box clipping

ROM `GetFireballBoundBox`, `GetMiscBoundBox`, and `GetEnemyBoundBox` all fall through `BoundingBoxCore` to `CheckRightScreenBBox` / `CheckLeftScreenBBox`. This packet moves that byte/carry comparison into the shared `world` owner and makes those three source callers invoke it immediately after their existing bounding-box writes. It must use the object page/X arrays only to choose the source half-screen branch; it must not make actor, OAM, collision-result, or platform decisions. The focused regression must cover the exact middle-screen equality, true left-offscreen `$a0-$ff` branch, and retained `$80-$9f` near-edge wrap.
## S3 P5: exact shared screen-edge bounding-box clipping

ROM `GetFireballBoundBox`, `GetMiscBoundBox`, and `GetEnemyBoundBox` each enter `BoundingBoxCore` and then unconditionally tail-call `CheckRightScreenBBox` / `CheckLeftScreenBBox`. `mysmb_world_clip_bounding_box_to_screen` is now that single game-core implementation. It retains the source middle coordinate (`ScreenLeft_X_Pos + $80` with its page carry), the equality-to-right branch, right-side `$ff` replacement, and left-side `$a0-$ff` cutoff while preserving the `$80-$9f` near-edge wrap. Fireball, misc, and enemy routes call it immediately after their existing bounding-box writes; the duplicated enemy implementation is deleted. No platform module reads or writes these game values.

`bounding_box_clip_smoke` proves the source middle equality, true left-offscreen cutoff, and retained near-left wrap. Full CTest passes 81/81 on both x64 and x86, including `platform-purity`; the OpenNT DOS MZ links from the identical shared source set. Refreshed artifacts: mysmb16.exe SHA-256 1A1657D57BD7363C95DAD69CD081D69EB43415A9673F03167F47879231A4FF49; mysmb32.exe SHA-256 EAFE2EB8EAE9A56F34034FE998B6BE3CCA268EB71F9391D005CB347FD01EABE5; mysmb64.exe SHA-256 5BE6FDD00D594CC01F87D7E534F291E74FF0E7A23C5FC298E0817C9D7248789A.
## S5 P5: enemy block-buffer probe boundary

ROM BlockBufferChk_Enemy now has one shared T17 owner. It uses the source 28-entry X/Y adder tables, byte ADC page carry, page-local block-buffer selection, ROM row masking, and the $04 contact-low-nibble selection. It returns terrain metadata only; actor state remains for the following EnemyToBGCollisionDet packet. Focused x86/x64 test and both Win32 self-tests pass; DOS16 relinks. Artifacts: 250006DA29644D8572708CE89C2A405F7B9DE7F0E1B070911FCDA612000FAE00, E0A859D294F8F56370AAA3236C8D1C8FFAD121C5E0035485D193BC8817AD6AAC, 10F0CF80FFBA2418A86015B93F629CBA1ED26B1065F6CAD07F46660658035E50.


## S5 P8: shared EnemyLanding primitive

ROM EnemyLanding -> InitVStf now has one T17 world owner: it clears Enemy_Y_Speed and Enemy_Y_MoveForce and aligns Enemy_Y_Position to $08. The direct regression covers all three RAM writes. x86 and platform-purity pass; DOS16 relinks from the shared source. This primitive is intentionally not yet wired into every caller; S5's following state-machine packet will replace only source EnemyLanding call sites.

## S5 P9: restore ordinary-enemy terrain state machine

`EnemyToBGCollisionDet` for the ordinary walking route now follows the ROM control tree rather than treating ground and side probes as independent ad-hoc checks: d5 and vertical-entry gates, `ChkUnderEnemy`, non-solid classification, `LandEnemyProperly`, `ChkForRedKoopa`, and `DoEnemySideCheck` execute in source order. `EnemyLanding` uses the existing shared `mysmb_world_land_enemy` primitive; the actor route retains only actor-state, player-facing, sound, and direction effects. The collision node is exposed as the shared game API `mysmb_objects_step_normal_enemy_terrain` so its RAM result can be tested without platform or unrelated OAM/collision scheduling. The new direct regression covers falling Goomba landing (`Y|$08`, vertical state reset), empty-bottom state transition through `EnemyBGCStateData[0]`, and the normal Red Koopa turn path. `core_smoke` now supplies the ROM d6 falling precondition for its landing fixture instead of relying on the former simplified always-land behavior. Full x64 and x86 CTest suites pass 83/83, including platform-purity; OpenNT relinks the DOS16 MZ from the same game sources. The `$23` bumped-block effect chain remains the next named S5 packet because it hands off to block defeat, floatey score, and audio owners.

## S5 P10: restore bumped-block enemy chain

The `$23` `HandleEToBGCollision` branch is no longer treated as empty terrain. The shared block query now carries the exact block-buffer address, and the normal-enemy collision node clears that location before executing the ROM chain: Goomba `KillEnemyAboveBlock`/`ShellOrBlockDefeat`, `SetupFloateyNumber` through the existing source-relative seam, the accumulator-dependent `ChkToStunEnemies` demotion interval, `SetStun`, vertical speed selection by `AreaType`, and player-relative direction/X speed. The direct terrain-state test now proves buffer clearing and the Goomba block-defeat/100-point/stun output as well as the non-Goomba stun path. Full x64 and x86 CTest suites pass 83/83, including platform purity; OpenNT relinks DOS16 from the same shared game sources.

## S5 P11: unify ROM enemy gravity arithmetic

`MoveD_EnemyVertically` and `MoveJ_EnemyVertically` both reach `ImposeGravitySprObj`. The shared `mysmb_enemy_move_downward` owner now preserves the second ADC carry exactly: when a signed vertical speed plus the fractional carry wraps to the same Y byte, the high-byte update still receives that carry after its signed decrement. The prior comparison-based implementation lost that case. The ordinary enemy falling/defeat paths and `PowerUpObjHandler` now call this one primitive with their source literals (`$3d` or `$1c`, maximum `$03`), removing three duplicate arithmetic implementations. `world_movement_smoke` exercises the exact `$ff + carry` equality case.

Full x64 and x86 CTest suites pass 83/83, including platform purity; DOS16 links from the same source set with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe `6DFE93A94E48A592C19D07BF59498F1F5D803BF4B7A66D956DEA7CEDBAB3CC7F`; mysmb32.exe `D85AA73947E7D10FC885D573A8E5ACAEE7EA7CAA1128F1ED748EEC7F97C44671`; mysmb64.exe `CDF6FC47D5E9D24E165DD8041BD46E3D6BB07F5D2E87A9973D1F9C70848F3D14`.

## S5 P12: restore star `EnemyJump` call tree

`PowerUpObjHandler` now sends only `PowerUpType=$02` through a shared game-only `EnemyJump` node after `MoveJumpingEnemy`. It reproduces `SubtEnemyYPos`'s wrapped-byte `$44` comparison, the `YSpeed + $02 >= $03` gate, `ChkUnderEnemy`, non-solid rejection, `EnemyLanding`, and the `$fd` re-jump speed. It then always reaches `DoEnemySideCheck`, including that routine's `$20` status-bar early return and original leading-side probe. Mushrooms and 1-ups retain their separate `MoveNormalEnemy -> EnemyToBGCollisionDet` route. Focused regression asserts the landing/re-jump RAM sequence and the status-bar side-check guard.

Full x64 and x86 CTest suites pass 83/83, including platform purity; DOS16 links from the same source set with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe `43E6B77F655AB7030B4EAC1940137E30A422DAC1BC9FFB779B869A4F01E854D5`; mysmb32.exe `7913E59BC8990A00D3B8E82EFAA18ADE4F0CD3B6FB3E46DB30EA05E494B2119E`; mysmb64.exe `D16BF242FBF99E60D3A843F695B016F1A9EC588D3EFC47344EF049A9F385E461`.

## S5 P13: restore Bullet Bill falling gravity

`BulletBillHandler` with defeated-state d5 reaches `MoveD_EnemyVertically`, whose source force is `$3d`, not `$1c`. The old local C arithmetic used `$1c` and also lost the signed-speed/fractional ADC carry. It now calls `mysmb_enemy_move_downward($3d,$03)`, the same game-only ROM primitive used by the verified enemy paths. The Bullet Bill regression checks both the normal defeated fall and the `$ff + carry` high-byte boundary.

x64/x86 CTest pass 83/83 including platform purity; DOS16 links from the same source with the established `OLDNAMES.LIB` warning. Artifacts: `mysmb16.exe` `ECBF5AD8F9285E14EB84E8DA89A50FBA633F55B14F0D19F7EEE649BDCFDD99B0`; `mysmb32.exe` `FCBA25469D7862D4DB2EA5E4875CEB2EFB6BD5B8A53B5D0171254BDCB9B1B2B4`; `mysmb64.exe` `A5D9DCEC062B5383A4BFBC2EBD13A080BA58077372425A3AB2DAAF5C99CA8640`.

## S5 P14: unify direct `MoveJ_EnemyVertically` callers

Podoboo and jumping green paratroopa each directly invoke ROM `MoveJ_EnemyVertically`, which supplies `$1c` downward force and maximum speed `$03`. Their duplicate C arithmetic is replaced by the verified shared `mysmb_enemy_move_downward` primitive; scheduling, initialization, horizontal movement, and actor rules remain in their existing routes. Focused Podoboo OAM and paratroopa tests pass, as do full x64/x86 suites (83/83) and platform purity. DOS16 links from the same source set with its established `OLDNAMES.LIB` warning. Artifacts: `mysmb16.exe` `0674DE5FF99142531CB356BEBDE15186613D3E7F243F8231907BF4CF364CE5CC`; `mysmb32.exe` `1B9244B5C1FEAAC6F5448F06803DC716BF1453F4A83631A34CAD6B189B2F64B0`; `mysmb64.exe` `18CD54BCBCA8D900B1842056B263DEC502309FD4ED20186874E5508BB364CD6D`.

## S5 P15: restore defeated Bloober slow gravity

ROM `MoveDefeatedBloober -> MoveEnemySlowVert` calls `SetXMoveAmt` with `$0f` force and maximum speed `$02`. The old C duplicate mutated the fractional byte but dropped its carry into Y. The route now calls `mysmb_enemy_move_downward($0f,$02)`, preserving all 6502 carry, high-byte, and cap behavior in shared game code. Full x64/x86 suites pass 83/83 including platform purity; DOS16 links from the same source with its established `OLDNAMES.LIB` warning. Artifacts: `mysmb16.exe` `2FC78448E2DC75D4811421F19566F113E0DEFEF5F900964CD932798DE9ECAAC6`; `mysmb32.exe` `466C5CFEE682DEC7B32750892B4D43669B88C7CBC39FD86B0443C089FDDCFE3C`; `mysmb64.exe` `23BFD96BDA83D15E2A43FAF21C5859EB0F0EA96D1EE2342A1F1DBF396E874855`.

## S5 P16: restore defeated swimming Cheep-Cheep gravity

The `Enemy_State` d5 branch in `MoveSwimmingCheepCheep` reaches ROM
`MoveEnemySlowVert`, which is `SetXMoveAmt($0f,$02)` followed by the common
vertical move. The previous C path skipped that branch entirely. It now calls
the same shared `mysmb_enemy_move_downward($0f,$02)` primitive as defeated
Bloober, retaining the source fractional carry, signed high-byte update, and
maximum-speed gate. The regression drives the actual d5 branch; no platform or
renderer code takes part.

## S6 P1: source-reachable world-route baseline

Two fresh original-ROM/NMI-return comparisons were generated below
`build/m2-t17-s6-current/traces` with the same `smb1.nes`, controller changes,
and real title bootstrap used by the shared native recorder. Route one records
frames 0--599: Start at 200, Right at 240, and Right+A from 310--339. Route two
warms those first 600 frames, then records frames 600--1199 while holding
Right+B and adding two Right+B+A jumps. Neither route injects object state.
For both routes, CPU work RAM `$0300-$07ff`, both CIRAM pages, palette, visible
OAM, all fourteen audio-command bytes, and all seven PPU-visible scalar bytes
have zero differences. The x86 and x64 native recordings are byte-identical.
The only recorded CPU RAM differences are execution-private zero-page/stack
state, outside the output-equivalence contract. This is positive route evidence
for the shared T17 movement/collision calls, not task closure: S6 still needs
the named wall, hidden-block, pipe, power-up, fireball, stomp, and score route
coverage before T17 can close.
## S6 P2: first-mushroom collision route

The first-mushroom route was rerun from a cold title bootstrap against the
original ROM: neutral through frame 39, Start at 40--41, Right from 220, and
Right+A at 300--341 and 390--431. It reaches the player head/block request,
power-up emergence, falling and terrain-collision chain through normal
execution, without object-slot injection. Across all 600 NMI-return samples,
CPU work RAM `$0300-$07ff`, CIRAM pages, palette, visible OAM, audio command
state and all PPU scalar outputs are zero-difference. Current x86 and x64
native trace files are byte-identical. The route artifacts and comparator
output remain under `build/m2-t17-s6-current/traces`; it is route evidence,
not a substitute for the still-required hidden-block, pipe, fireball, stomp
and score cases.
## S6 P3: hidden-block and jump-coin route

A separate cold-title route holds Right+B from frame 340 and Right+B+A from
436--451, reaching the first hidden coin block without synthetic RAM setup.
The original-ROM trace records the block and jump-coin progression; the fresh
current native x64 and x86 records are byte-identical and match the ROM for all
600 samples in work RAM `$0300-$07ff`, both CIRAM pages, palette, visible OAM,
audio command bytes, and PPU scalar output. The new artifacts are retained only
under `build/m2-t17-s6-current/traces`. An earlier extended running route ends
in the normal death path before any pipe contact, so it is explicitly excluded
from pipe coverage rather than being counted as a false positive.

## S6 P4: terminal foot-impede continuation

The pipe-search route exposed a source-control-flow error in the shared
`PlayerBGCollision` translation.  In ROM `ChkFootMTile`, a solid foot sample
whose `$04` low nibble is `$05-$0f` loads `Player_MovingDir` and `JMP`s to
`ImpedePlayerMove`; that path returns from `PlayerBGCollision` and never
reaches `DoPlayerSideCheck`.  The C code previously returned the same local
result as a normal landing, so both callers continued into the side probe and
applied a second correction.  `mysmb_player_check_feet` now returns a named
internal terminal-control result for that source jump, and both existing
`mysmb_player_step` call sites return from their collision sequence when they
receive it.  This is only C control-flow representation; the RAM mutation
remains the existing ROM `ImpedePlayerMove` owner.  The focused regression
asserts that this exact `$05` route produces the terminal result as well as
the original position, speed, collision-bit and side-counter writes.

The original-ROM pipe-search trace was regenerated with the documented
600-frame warmup and controller script.  At samples 251--260, the previously
incorrect native player X (`$d2` instead of `$d3` at sample 251), collision
bits, X speed and movement force now match the ROM on every recorded sample.
The full comparison still first differs at sample 232 in CPU OAM attribute
`$02da` and work RAM `$04b4`; those residuals precede this player route and
remain transferred to T16 OAM writer/staging investigation.  No platform
source changed.  x64 and x86 CTest each pass 83/83, and DOS16 relinks from the
same shared game source.  The regenerated x86 and x64 native pipe traces are byte-identical (`6128B90D6596EC07FEA39B37D8694C6D7F36BD52457551371749E6CC01029CF5`).
## S6 P5: source-reachable pipe-route closure

The P4 pipe-search controller script was rerun after T16/T19 removed its transferred actor-staging residual.  It records 600 NMI-return samples following the documented 600-frame warmup, with no RAM or actor-slot injection.  Both x64 and x86 native traces are byte-identical (`6C2A27330A2099D16412940C0557` prefix) and both match the original ROM for visible OAM, palette, all audio-command bytes, and all seven PPU-visible scalars.  The earlier sample-232 to sample-346 enemy bounding-box/OAM divergence is absent.  The first remaining difference is sample 584 in work RAM/nametable output; it is the previously transferred status-buffer owner and is outside this pipe/collision route.  The recordings and comparator reports remain in `build/m2-t17-s6-current/traces`; no platform module participates.
## S6 P6: source-reachable stomp and score handoff

The reproducible P5 pipe route also contains the first ordinary-Goomba stomp, so the three non-stomping exploratory recordings are not used as evidence.  At sample 231, slot zero transitions from ID `$06`/state `$00` to state `$04`; the same ROM-visible sample sets `StompChainCounter/$0484=$01`, `Enemy_CollisionBits/$0491=$01`, `StompTimer/$0791=$01`, interval timer `$0796=$10`, and player Y speed `$fc`.  The frame sequence then clears the collision bit, advances the floatey-score controller, lands the player, and erases the defeated object at sample 257.  Every named byte matches the x64 recording and the complete x86/x64 recordings are byte-identical; the route’s visible OAM, palette, audio commands, CIRAM, and PPU fields remain ROM-equal.  This closes source-reachable ordinary stomp/score handoff coverage for T17 without object injection.
## S4 P17: shared player block-buffer query boundary

`PlayerBGCollision` chooses its head, foot, and side probe-table entries, but
`BlockBufferCollision/GetBlockBufferAddr` is a shared geometry primitive. The
exact player coordinate query now has one owner in `world/collision.c` as
`mysmb_world_query_player_block`. It retains byte X addition, page carry,
page-local block-buffer selection, row masking, address-low scratch result,
and contact-nibble selection. `player.c` retains every source-order probe and
all player-only branches; no platform code participates. A fresh 600-sample
source-reachable pipe/stomp/score route uses the original ROM and the same
controller transition sequence after a 600-frame warmup. Native x86 and x64
traces are byte-identical (`6C2A27330A2099D16412940C05575F541EE02C290008B0C9EBEFECD4A3FBBF7A`).
For both, CPU OAM backing, visible OAM, palette, audio-command state, and all
seven PPU-visible scalars have zero differences from the ROM. The first
remaining work-RAM difference is sample 584 at `$03f0`, followed by the
known CIRAM page-zero status-buffer output at sample 592; these residuals are
outside the player block-query route and remain with the named area/status
producer. `core_smoke` invokes
the extracted primitive directly, and collision regressions exercise its head,
foot, and side callers.
## S5 P17: route Spiny eggs through shared enemy block query

`MoveD_EnemyVertically`'s Spiny-egg landing path duplicated the coordinate,
page-carry, row, and block-buffer arithmetic already owned by
`BlockBufferChk_Enemy`. It now calls `mysmb_world_query_enemy_block` with the
source `$15` probe index (X+$08, Y+$18). The frenzy route retains its ROM
non-solid test and all Spiny-only landing/state writes. `lakitu_smoke` covers
both falling and landed eggs, while `enemy_terrain_state_smoke` covers the
ordinary route that shares the primitive. Full x86/x64 CTest suites pass 83/83, including platform-purity. No platform source participates.
## S5 P18: route Hammer Bro through shared enemy block query

`HammerBroBGColl` duplicated `ChkUnderEnemy`'s `$15` block-buffer probe.
It now calls `mysmb_world_query_enemy_block` with the original probe index;
Hammer Bro retains only its non-solid, interval-timer, landing, and state
rules. The focused enemy-terrain, Hammer Bro, and Hammer Bro OAM regressions
pass on x86 and x64. Full x86/x64 CTest suites pass 83/83, including platform-purity. No platform source participates.
## S5 P19: route Vine handler through shared enemy block query

`VineObjectHandler` uses `BlockBufferCollision` probe `$1b` (X+$04,
Y+$10) before conditionally writing vine metatile `$26`. Its duplicate
page/column/row arithmetic now uses `mysmb_world_query_enemy_block`; the
handler retains the source row guard and writes only when the returned tile is
blank. Focused Vine OAM and enemy block-query regressions pass on x86 and x64. The latter explicitly proves Vine probe `$1b` crosses X `$fc+$04` into block address `$0600` with row `$30` from Y `$40+$10`. Full x86/x64 CTest suites pass 83/83, including platform-purity.
No platform source participates.
P19's residual-address audit finds no actor or player collision probe outside
`world/collision.c`: player head/foot/side, ordinary enemies, power-ups,
Spiny eggs, Hammer Bros, and vines all use the shared query APIs. Remaining
`$0500/$05d0` operations are deliberately excluded: T18 area parser and
metatile-replacement writers, plus T22 block/coin/axe event writers that
consume an already-selected source block address. They are not alternative
collision geometry implementations.

## S6 P7: controller-only page-12 route transfer

A controller-only route now preserves Super Mario through the page-nine gap, the page-ten actor crossing, and the three page-eleven staircase jumps, reaching page twelve without RAM or PPU injection.  The ROM recorder and native x64 recorder compare the 600 samples after a 2,220-frame warmup; scripts, traces, and report remain under `build/m2-t17-s6-fireball-search/`.  The first shared-state residual is already present at sample zero: ROM `$06bc=01`, native `$06bc=00`.  The source declares this as `BrickCoinTimerFlag`; `BlockBumpedChk` sets it for brick-with-coins metatiles `$58/$5d` before `BlockObjectsCore` chooses the retained or empty metatile.  It is therefore a T22/S2 block bump/coin-metatile producer, precisely listed in T22’s `BlockCode / BrickQBlockMetatiles / BlockBumpedChk` row, and is not a T17 collision primitive.  Later OAM difference begins at sample 362 and CIRAM difference at sample 528, so they are downstream of that untransferred block producer.  No collision or platform code changed in this packet.  Current artifacts used for the route: mysmb16.exe `70989598666E6CDA85239E7D43A5BBFFC764E1AB1D4E872CA7DFBD36612F03E1`, mysmb32.exe `2862DDBB1D816A38819D2F36B65343EA5B568DEDA81A35CF15C17A645AAA0877`, mysmb64.exe `9EEC3920CB4EC230E87C24C9CBC7E93741CD2AB4E3141C49F3345E14C2914F75`.
## S6 P8: page-twelve post-transfer ownership check

The same controller-only 600-frame page-twelve route was replayed after
T22/S2 restored `BrickCoinTimerFlag` and T22/S4 restored
`FlagpoleRoutine`.  The former sample-zero `$06bc` and sample-362 flagpole
`$03ae` residuals are absent.  The first remaining work difference is sample
526: ROM emits VRAM-buffer bytes `$06a9-$06ab = $45,$47,$47`, while native
still has zero, alongside the parser/column state difference `$0732 = $03`
versus `$05`.  The first CIRAM-page-zero difference is sample 528.

`$06a9-$06ab` are `VRAM_Buffer1` command bytes, and `$0732` is area-parser
state.  Their producer is T18's shared area/parser output path, not a T17
world primitive.  This packet changes no code and transfers the next residual
to T18 without masking it.  The checked-out artifacts are the immediately
preceding three-target build: mysmb16.exe
`CBDC82F47E98049B62586A9ACE5736F219FF906803CA999C333EDF43B557C48D`,
mysmb32.exe `705D76A5D9559838309E5960E09C05A9FDCDD08CDCEC4D56FEC04EF29CC8AEF5`,
and mysmb64.exe
`3D83CA4D91CB4C50EDC4EB05EF971EB803CED17F81EA16524A01D8F22865A55D`.
## S6 P9: page-twelve post-parser ownership check

After T18/S2/P4 restores the `$af,$26` `CastleObject` column, the same
source-reachable 2,220-frame-warmup route has zero CIRAM, palette, and PPU
scalar differences for all 600 recorded samples. The former sample-526 parser
and sample-528 CIRAM differences are absent. The remaining three CPU/visible
OAM bytes are one byte at OAM `$78` in samples 553--555: ROM Y is `$39`, C is
`$38`.

This is not a T17 collision write. At sample 553 the ROM has
`Enemy_Flag[0]=$01`, `Enemy_ID[0]=$31`, `Enemy_Y[0]=$7f`, and
`Enemy_SprDataOffset[0]=$0c`; native has the slot inactive and its stream
offset is `$0a` instead of `$0c`. The producer is `ProcessEnemyData` in the
T19 enemy-stream/actor owner. T17 transfers this actor spawn/stream residual
without altering collision or OAM code. The checked-out three-target artifacts
are mysmb16.exe `BFED12E8BC1201BFE63F774584291DC701D7713523BE91341C5EB1C8942BB790`,
mysmb32.exe `F27A8D690D20AD0D4B58F962F4F7491E01066E2AEE777A5785B5DE39862EDC0D`,
and mysmb64.exe `4A3067235777F65EAD2912B31E238549A087D6E20F3549EDB11B2FE367F4DA3E`.

## S6 P10: correct page-twelve actor ownership transfer

S6/P9's transfer to T19 is superseded. The source area bytes `$af,$26` enter
`CastleObject`; at length `$02` that routine directly creates `StarFlagObject`
(`$31`). `EnemyDataOffset` is `$1d` in both ROM and C, so `ProcessEnemyData`
is not the producer. T18/S2/P5 owns and now restores this parser leaf. The
remaining OAM `$78` samples 553--555 were present before this correction and
remain independently queued; no T17 collision or platform code changes here.
The three executable artifacts are mysmb16.exe
`8A9E4C90528E8372E7CAC276C48B5B2C52EB68B227793D844F1EAA33C262F630`,
mysmb32.exe `E4315D3069E66040681145013DE5CD7A37603B017CB9213C1C7393DBF17E4C19`,
and mysmb64.exe `320F187940BD8C59D48EBE4D9E2620B249D2472A1AD118E3EDBB6E84BDEA3534`.## S6 P11: transfer the final page-twelve OAM residual

**ROM-node accounting:** baseline remains **0 / 1,992** complete; this
closure packet changes no node to complete. It records `FlagpoleGfxHandler`
(line 13284) and `DumpTwoSpr` (line 13348) as deferred graphics nodes for T16.

The controller-only page-twelve trace has no collision, movement, CIRAM,
palette, PPU-scalar, or actor-state mismatch. Its only remaining visual
residual is CPU OAM `$78` in samples 553--555 (visible one NMI later): at
sample 553 the reference writes Y `$39`, while C writes `$38`; tile `$7e`,
attribute `$01`, and X `$f7` agree. This is the third flagpole sprite emitted
by `FlagpoleGfxHandler`, whose source `FPGfx` call is after all collision and
object routes. The slot-five flag state and relative coordinates match at this
sample, while the post-frame sprite-offset shuffle differs from the offset used
when the source writes OAM. The precise writer/timing relationship therefore
belongs to T16's OAM graph, not T17's world primitives. No game or platform
code changes in this transfer. Current three-target artifacts: mysmb16.exe
`8A9E4C90528E8372E7CAC276C48B5B2C52EB68B227793D844F1EAA33C262F630`,
mysmb32.exe `E4315D3069E66040681145013DE5CD7A37603B017CB9213C1C7393DBF17E4C19`,
and mysmb64.exe `320F187940BD8C59D48EBE4D9E2620B249D2472A1AD118E3EDBB6E84BDEA3534`.