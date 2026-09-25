# M2 candidate: Fireballs and bubbles

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 6298-6729: fireball/bubble dispatch, setup/core, relative position, offscreen bits and background/enemy collision.

## Existing-code disposition

Extract fireball code from objects.c; remove world-distance offscreen shortcuts and keep state in shared RAM.

## Graph contract

Called before enemy slots; consumes player/collision/enemy state and writes fireball RAM/OAM/audio.

## Admission S plan

1. **S1 after admission** - Map spawn and bubble/fireball labels, RAM fields and all current shortcuts.
2. **S2 after admission** - Translate spawn/page carry, movement/gravity and relative-position/offscreen-bit sequence.
3. **S3 after admission** - Translate background/enemy collision and clear/effect branches.
4. **S4 after admission** - Compare open travel, wall bounce, enemy hit and underwater bubble routes.

## Acceptance

Lifetime comes from ROM offscreen bits and collision branches, never a host distance test.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
