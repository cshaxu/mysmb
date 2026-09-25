# M2 candidate: Game frame dispatcher

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 5315-5582: GameMode, GameCoreRoutine, GameEngine, GameRoutines and player-control dispatch boundary.

## Existing-code disposition

Replace the central gameplay section of game.c with a thin ROM-order dispatcher. Child behavior remains in owned modules.

## Graph contract

Called by the frame root; orders fireball, six enemy/loop slots, player, graphics and object tails.

## Admission S plan

1. **S1 after admission** - Map every current game_tick branch to a dispatcher label or deletion target.
2. **S2 after admission** - Translate GameMode, GameCoreRoutine and task-table dispatch.
3. **S3 after admission** - Translate GameEngine call order and slot iteration without inlining child handlers.
4. **S4 after admission** - Trace one NMI through title, area init, play and pause boundaries.

## Acceptance

Dispatcher task-byte transitions and call ordering match ROM evidence; it contains no approximated child behavior.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
