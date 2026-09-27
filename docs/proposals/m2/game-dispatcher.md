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
## Chain-delivery governance amendment

The fixed "map, migrate, equivalence audit, operational test, closure" S
sequence in this proposal is historical planning evidence only.  For the next
admission or continuation in this task, one S must deliver one bounded,
contiguous ROM control/data chain: it records the exact labels in source order,
its entry and exit, one shared C owner, predecessor/successor dependencies,
and one ROM route that exercises the chain.  Mapping, the shared-C repair when
needed, node-by-node control/read/write/table/call-order comparison, and the
operational proof belong to that same S.

The node inventory and ledger still retain a separate row and final
completion disposition for every label.  A chain P runs one common ROM replay,
focused tests, x86/x64 builds, DOS16 link, platform-purity check, and refreshes
the three required local target artifacts.  T closure adds only the
cross-chain route matrix and integrated three-target regression.  It must not
recreate those gates for each leaf.  A chain may not cross an unadmitted
dependency, a different shared-owner boundary, or a branch family requiring a
different ROM route.  The binding authority is
[the M2 chain-delivery rule](../../rules/EXECUTION.md#m2-chain-based-s-delivery).