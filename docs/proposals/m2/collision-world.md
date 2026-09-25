# M2 T17: Collision and world primitives

## Status

**M2 T17 active — S2/P2.** T16/S2 is complete: its relative-position/offscreen writers now consume the ROM state they are given. The source-reachable demo trace proves that the next discrepancy is a producer-side 6502 carry error in `ImposeGravityBlock`/`ImposeGravity`, so this admitted task owns it before any block or OAM work proceeds.

## ROM scope

ROM lines 11085-14459: background/object collision, bounding boxes, bounds, gravity, movement, score and shared geometry. The initial executable boundary is labels `MoveEnemyHorizontally` through `ExVMove` (lines 7555-7784), specifically `ImposeGravityBlock`, `ImposeGravitySprObj`, `ImposeGravity`, and `AlterYP`.

## Existing-code disposition

Extract shared world primitives from `player.c`, `objects.c`, `area.c`, and `game.c` into `src/game/world/`. Game-route modules call those primitives in their original sequence; they do not carry duplicate arithmetic, synthetic thresholds, or platform behavior.

## Graph contract

World primitives consume caller-selected object-array offsets and RAM fields, preserve ROM byte/carry semantics, and mutate only ROM-owned shared state. They do not schedule actors, decide modes, draw OAM, or call platform code.

## Formal S breakdown

1. **S1 complete (P1) — source ownership and movement boundary.** Map lines 7555-7784 to current owners, introduce the `src/game/world/` boundary, and physically extract `MoveObjectHorizontally`/gravity-family implementations without changing their byte behavior. Evidence: build and bounded continuation trace are unchanged by an extraction-only P.
2. **S2 active (P1 complete; P2 next) — exact movement and gravity.** Translate `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `ImposeGravity`, and `AlterYP` with explicit 6502 add-with-carry state. Evidence: block, misc, fireball, and enemy traces at signed-speed/carry boundaries.
3. **S3 planned — coordinate, bounding-box, and screen-edge primitives.** Translate `BoundingBoxCore`, offscreen bounding behavior, relative coordinate helpers, and screen-edge checks. Evidence: actor and object bounding-box RAM plus OAM-facing positions.
4. **S4 planned — player/background and head/block collision.** Translate the player terrain, pipe, vine, head, and block-buffer probe branches. Evidence: wall, hidden-block, question-block, pipe, and vine routes.
5. **S5 planned — enemy/item/projectile collision and score handoffs.** Translate ground/side/background/object branches used by enemies, power-ups, fireballs, and score paths. Evidence: mushroom bounce, stomp/damage, fireball, and score/audio traces.
6. **S6 planned — cross-slice reference closure.** Run bounded ROM-reference traces covering each S2–S5 route and prove that remaining differences are transferred only to a named source owner.

## Acceptance

Every collision and movement result names its ROM probe/table/branch. Affected RAM, block buffer, score, audio, OAM, CIRAM, palette, and PPU output match the reference routes. Platform code may not read or write these game decisions. Replaced code is removed in the same admitted P after its trace proves the replacement.
## S1 P1: block gravity ownership boundary

`ImposeGravityBlock`/`ImposeGravity` was physically extracted from `objects.c` into `src/game/world/movement.c`, with its shared game-only declaration in `src/game/world/world.h`. `BlockObjectsCore` now calls the world primitive; no platform module participates. This packet intentionally preserves the pre-existing arithmetic while assigning its ROM owner before S2 corrects it. The 600-sample title-to-demo trace is byte-for-byte unchanged from the T16/S2 baseline: first work-RAM mismatch stays sample 72 / `$03d4`, with 3,417 differing work-RAM bytes; CIRAM, palette, audio commands, and all PPU scalars remain zero-difference, and visible OAM retains its prior sample-124 mismatch. x64 and x86 each pass 78/78 CTest cases. OpenNT recompiles and links the DOS MZ through the same source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 973559C3A6D145E7A26560ED82EC4B6E2CF4E6C7DA7A94D582F0574B6D15E177, mysmb32.exe SHA-256 7CC65F2C743A25D8571560AFA8940416B95E3B747E2A4EA7B9E9FCDACBDDAA5D, mysmb64.exe SHA-256 B8934C233C2CE863DD9B8A99EEC09559CC6738981060D7A17B178863A2D6D37F.
## S2 P1: restore `ImposeGravity` ADC carry

The original `ImposeGravity` uses the carry from `ADC SprObject_Y_Position,x` in the following `ADC $07` high-byte update. The old C inferred carry from `new_y < old_y`, which fails for `old_y + $ff + carry-in = old_y`: the low byte is unchanged but the 6502 carry is set. `movement.c` now retains the full 16-bit low-byte sum and derives carry from bit 8, preserving the source sequence without changing force, maximum-speed, or state thresholds. On the same 600-sample ROM continuation, `$03d4` and the block high-position mismatch disappear; the first work-RAM mismatch moves from sample 72 / `$03d4` to sample 82 / `$03f0`, and work-RAM differences fall from 3,417 to 2,893 bytes. CPU-RAM differences fall from 33,337 to 31,844 bytes. CIRAM, palette, audio commands, and all PPU scalars remain zero-difference; visible OAM remains at the pre-existing sample-124 mismatch. x64 and x86 each pass 78/78 CTest cases. OpenNT recompiles and links the DOS MZ through the same shared source with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 E1FCBC7E3DED1840449969FB75FB5F814BFF0006BDC036C2ED803B7F72B0A144, mysmb32.exe SHA-256 DD9659F3A1F887741000B671F17F495B0D27E7F82EFC60C6ABEAEDF81381403A, mysmb64.exe SHA-256 48E9479A6AD6453F8561E7A3300CAE1F4D0FDA4F803CDF4F9410C3D39A96BD22.

## S2 P2: restore misc-object gravity carry

`ImposeGravity` for the misc-object array now derives the high-position carry from the full low-byte ADC sum, including the `$ff + carry-in` case. The demo trace removes `$03d6`; the first remaining work-RAM difference moves to sample 124 / `$0491`.

## S3 P1: collision primitive ownership boundary

`BlockBufferCollision` page carry, `BoundingBoxCore`, and `PlayerCollisionCore` now live in `src/game/world/collision.c`, with no compatibility symbol left on the object route. Actor modules select objects and consume collision results; the world module only mutates or compares ROM bounding-box state. The 600-sample title/demo continuation is behavior-identical to the preceding T17/S2 baseline: first work-RAM difference remains sample 124 / `$0491`, work-RAM differences remain 2,286 bytes, visible OAM differences remain 3,622 bytes, and CIRAM, palette, audio commands, and PPU scalars remain zero-difference. x64 and x86 each pass 78/78 CTest cases. The OpenNT large-model DOS MZ relinks from the same source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 1EA7D8D18DFC60D23CFDDBACDFEF4407DD4BA649562B84FCBCBCC222FD61A989, mysmb32.exe SHA-256 4446FBA19910944F28840E915F3504F494777B34800EA8A8F5552AEE5F331B85, mysmb64.exe SHA-256 366D60FF6BDE63D04E4B12DF6F0AF82687AA0DF2D2A75C2ADD3B3550D08A6390.

## S5 P1: restore normal-enemy collision scheduling

`RunNormalEnemies` always calls `PlayerEnemyCollision` after `EnemyToBGCollisionDet` and before its ID-specific movement branch. The prior C route skipped that call for a defeated Goomba while its interval timer was nonzero, leaving `Enemy_CollisionBits` set after Mario had moved away. The normal-enemy route now makes the collision call before its defeated-object timer branch, matching the source order. The 600-sample title/demo continuation removes the sample-124 `$0491` discrepancy and moves the first remaining work-RAM difference to sample 142 / `$0484`; work-RAM differences fall from 2,286 to 1,810 bytes. x64 and x86 each pass 78/78 CTest cases. The OpenNT large-model DOS MZ relinks from the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 56948897C5189ECAE797788B8D9B74AABCA54C3E9B48775C8FED181ACE48CAFA, mysmb32.exe SHA-256 22381B6D5A159543BB8E01906321A854D9123BFBC9C2A9B4E6AD83CB1A438F04, mysmb64.exe SHA-256 847CF0F8C9BDA3B603C11F93AB910F86D87111D6F3D542B818153DE3B09E582D.

## S4 P1: move and restore LandPlyr

`CheckForClimbMTiles`, `CheckForSolidMTiles`, and `LandPlyr` now belong to the shared collision owner. `LandPlyr` clears `Player_Y_Speed`, `Player_Y_MoveForce`, `StompChainCounter`, and `Player_State` in the original order after the successful foot probe. The player route retains only its source-order foot probes and invokes the world result. The 600-sample continuation removes the sample-142 `$0484` discrepancy and moves the first remaining work-RAM difference to sample 172 / `$03ae`; work-RAM differences fall from 1,810 to 1,352 bytes. x64 and x86 each pass 78/78 CTest cases. The OpenNT large-model DOS MZ relinks from the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 BD8ED44D95E7C7494AF366613B288245FBC2BF58C11D04B25217460F1C9A57AD, mysmb32.exe SHA-256 31A54AB44A6341C656D912561AB58624A79E9D5F4F766AF81766CD1C37812DC1, mysmb64.exe SHA-256 44EB05E0C686F71C3887ABAA91116DB292BEAAE106D71EA10B1595408D384AA0.
