# M2 candidate: Blocks, items and misc

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 6730-7787: vines, coins, block bump/break, power-ups, misc objects, cannon, whirlpool and flagpole setup.

## Existing-code disposition

Split objects.c and graphics helpers into source-owned block/item/misc writers; retain only ROM-backed state.

## Graph contract

Consumes block buffer/player state and emits item/misc state, score, audio and OAM work.

## Admission S plan

1. **S1 after admission** - Map block/item/misc labels/tables to current code and identify synthetic rules.
2. **S2 after admission** - Translate block bump/break/coin/metatile replacement paths.
3. **S3 after admission** - Translate power-up, vine and misc-object state machines/collision handoffs.
4. **S4 after admission** - Translate cannon, whirlpool and flagpole setup/output paths.
5. **S5 after admission** - Compare hidden blocks, powerups, vine, cannon/whirlpool and flagpole scenarios.

## Acceptance

Block buffer, metatiles/CIRAM, item behavior, score/audio and OAM match reference.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
