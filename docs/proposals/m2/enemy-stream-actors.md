# M2 candidate: Enemy stream and actors

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 7788-11084: EnemiesAndLoopsCore, loops/frenzy, ProcessEnemyData, positioning, groups, initialization and enemy handlers.

## Existing-code disposition

Replace forced-slot scanning in area.c; split stream parsing, initialization and handlers out of generic object code.

## Graph contract

Six ROM slots are dispatched by GameEngine; consumes area stream/block state and produces enemy RAM, collision/OAM/audio events.

## Admission S plan

1. **S1 after admission** - Map stream labels, ObjectOffset/PageLoc fields, tables and current C entry points.
2. **S2 after admission** - Translate loops, bounds/pages, two/three-byte records and position-before-bounds semantics.
3. **S3 after admission** - Translate group, frenzy and initialization dispatch including special IDs.
4. **S4 after admission** - Translate normal and special enemy handler paths using shared collision contracts.
5. **S5 after admission** - Compare W1-1 stream, group/frenzy, pipe enemy and representative special actor routes.

## Acceptance

Stream bytes, inactive slots, page controls, initialization/actor state and OAM match ROM without fabricated spawn scans.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
