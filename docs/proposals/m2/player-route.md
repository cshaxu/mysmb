# M2 candidate: Player route

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 5583-6297: PlayerCtrlRoutine, movement/state/size, pipe/vine/scroll interaction and player-originated block actions.

## Existing-code disposition

Audit player.c and player code in game.c/objects.c; retain fixed-width arithmetic/RAM offsets only with label proof.

## Graph contract

Consumes latched input, block buffer and object state; writes player state, scroll, block events, OAM/audio queues.

## Admission S plan

1. **S1 after admission** - Create label-to-function/write map for controller partition, state and movement.
2. **S2 after admission** - Translate horizontal/vertical physics, acceleration, gravity and page carry.
3. **S3 after admission** - Translate player/background/head collision and block handoffs.
4. **S4 after admission** - Translate size, injury, pipe, vine, entrance and scroll branches.
5. **S5 after admission** - Compare walk/jump, walls, hidden blocks, powerups, pipes, damage/death and scrolling.

## Acceptance

Player state, collision results, scroll, block events, OAM and audio agree with every approved ROM route.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
