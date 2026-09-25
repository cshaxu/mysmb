# M2 T17: Collision and world primitives

## Status

**M2 T17 active — S1/P2.** T16/S2 is complete: its relative-position/offscreen writers now consume the ROM state they are given. The source-reachable demo trace proves that the next discrepancy is a producer-side 6502 carry error in `ImposeGravityBlock`/`ImposeGravity`, so this admitted task owns it before any block or OAM work proceeds.

## ROM scope

ROM lines 11085-14459: background/object collision, bounding boxes, bounds, gravity, movement, score and shared geometry. The initial executable boundary is labels `MoveEnemyHorizontally` through `ExVMove` (lines 7555-7784), specifically `ImposeGravityBlock`, `ImposeGravitySprObj`, `ImposeGravity`, and `AlterYP`.

## Existing-code disposition

Extract shared world primitives from `player.c`, `objects.c`, `area.c`, and `game.c` into `src/game/world/`. Game-route modules call those primitives in their original sequence; they do not carry duplicate arithmetic, synthetic thresholds, or platform behavior.

## Graph contract

World primitives consume caller-selected object-array offsets and RAM fields, preserve ROM byte/carry semantics, and mutate only ROM-owned shared state. They do not schedule actors, decide modes, draw OAM, or call platform code.

## Formal S breakdown

1. **S1 active (P1 complete; P2 next) — source ownership and movement boundary.** Map lines 7555-7784 to current owners, introduce the `src/game/world/` boundary, and physically extract `MoveObjectHorizontally`/gravity-family implementations without changing their byte behavior. Evidence: build and bounded continuation trace are unchanged by an extraction-only P.
2. **S2 planned — exact movement and gravity.** Translate `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `ImposeGravity`, and `AlterYP` with explicit 6502 add-with-carry state. Evidence: block, misc, fireball, and enemy traces at signed-speed/carry boundaries.
3. **S3 planned — coordinate, bounding-box, and screen-edge primitives.** Translate `BoundingBoxCore`, offscreen bounding behavior, relative coordinate helpers, and screen-edge checks. Evidence: actor and object bounding-box RAM plus OAM-facing positions.
4. **S4 planned — player/background and head/block collision.** Translate the player terrain, pipe, vine, head, and block-buffer probe branches. Evidence: wall, hidden-block, question-block, pipe, and vine routes.
5. **S5 planned — enemy/item/projectile collision and score handoffs.** Translate ground/side/background/object branches used by enemies, power-ups, fireballs, and score paths. Evidence: mushroom bounce, stomp/damage, fireball, and score/audio traces.
6. **S6 planned — cross-slice reference closure.** Run bounded ROM-reference traces covering each S2–S5 route and prove that remaining differences are transferred only to a named source owner.

## Acceptance

Every collision and movement result names its ROM probe/table/branch. Affected RAM, block buffer, score, audio, OAM, CIRAM, palette, and PPU output match the reference routes. Platform code may not read or write these game decisions. Replaced code is removed in the same admitted P after its trace proves the replacement.
## S1 P1: block gravity ownership boundary

`ImposeGravityBlock`/`ImposeGravity` was physically extracted from `objects.c` into `src/game/world/movement.c`, with its shared game-only declaration in `src/game/world/world.h`. `BlockObjectsCore` now calls the world primitive; no platform module participates. This packet intentionally preserves the pre-existing arithmetic while assigning its ROM owner before S2 corrects it. The 600-sample title-to-demo trace is byte-for-byte unchanged from the T16/S2 baseline: first work-RAM mismatch stays sample 72 / `$03d4`, with 3,417 differing work-RAM bytes; CIRAM, palette, audio commands, and all PPU scalars remain zero-difference, and visible OAM retains its prior sample-124 mismatch. x64 and x86 each pass 78/78 CTest cases. OpenNT recompiles and links the DOS MZ through the same source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 973559C3A6D145E7A26560ED82EC4B6E2CF4E6C7DA7A94D582F0574B6D15E177, mysmb32.exe SHA-256 7CC65F2C743A25D8571560AFA8940416B95E3B747E2A4EA7B9E9FCDACBDDAA5D, mysmb64.exe SHA-256 B8934C233C2CE863DD9B8A99EEC09559CC6738981060D7A17B178863A2D6D37F.
