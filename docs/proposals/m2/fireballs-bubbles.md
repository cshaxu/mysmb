# M2 candidate: Fireballs and bubbles

## Status

**M2 T20 active — S1/P1.** This task is admitted after T19 because the next isolated source-slice defect is FireballObjCore: the native branch omits the ROM `Sfx_Fireball` queue write. T20 owns only ROM lines 6298–6729 and its named callees; OAM scratch/output remains delegated to T16 and shared movement/collision primitives remain delegated to T17.

## ROM scope

ROM lines 6298-6729: fireball/bubble dispatch, setup/core, relative position, offscreen bits and background/enemy collision.

## Existing-code disposition

Extract fireball code from objects.c; remove world-distance offscreen shortcuts and keep state in shared RAM.

## Graph contract

Called before enemy slots; consumes player/collision/enemy state and writes fireball RAM/OAM/audio.

## Admission S plan

1. **S1 active (P1)** - Establish the source owner boundary: extract fireball/bubble dispatch and its named labels from `objects.c` into `src/game/fireball/` without behavior changes; map every RAM field, helper and cross-slice call.
2. **S2 planned** - Translate spawn/page carry, the Sfx_Fireball queue write, movement/gravity and the relative-position/offscreen-bit call sequence, consuming T16/T17 primitives rather than duplicating them.
3. **S3 planned** - Translate background/enemy collision and clear/effect branches.
4. **S4 planned** - Compare open travel, wall bounce, enemy hit and underwater bubble routes.

## Acceptance

Lifetime comes from ROM offscreen bits and collision branches, never a host distance test.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.\n\n## S1/P1 admission record\n\nThe existing implementation interleaves `ProcFireball_Bubble`, `FireballObjCore`, fireball collision, and bubble calls with unrelated block/item/enemy owners in `objects.c`. S1/P1 moves only this source slice to an explicit game owner and declares its call dependencies: T16 supplies relative/offscreen/OAM writes; T17 supplies common gravity, horizontal movement, bounding-box and block-buffer primitives; T19 retains enemy-slot scheduling. No state transition, sound value, collision threshold, or renderer behavior may change in S1. S2 begins only after this boundary compiles and has the three-target artifact baseline.
