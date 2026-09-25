# M2 candidate: Collision and world primitives

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 11085-14459: background/object collision, bounding boxes, bounds, gravity, movement, score and shared geometry.

## Existing-code disposition

Extract helpers from player.c, objects.c, area.c and game.c; remove generalized predicates without ROM tables/branches.

## Graph contract

Called by player, fireball, blocks/items and enemies; mutates their shared RAM contract without scheduling them.

## Admission S plan

1. **S1 after admission** - Inventory collision/bounds labels, offset tables and helper thresholds.
2. **S2 after admission** - Translate coordinate conversion, bounding boxes, movement/gravity and background probes.
3. **S3 after admission** - Translate player/background/head/object collision branches.
4. **S4 after admission** - Translate enemy/item/fireball side, ground and object collisions plus score handoffs.
5. **S5 after admission** - Compare wall, ground, pipe, hidden block, mushroom, stomp/damage and fireball edge routes.

## Acceptance

Every collision result names ROM probe/table/branch; affected RAM, block buffer, score, audio and OAM match reference.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
