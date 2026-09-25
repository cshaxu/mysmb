# M2 candidate: Enemy stream and actors

## Status

**M2 T19 active — S2/P1.** Admission is triggered by the bounded title/demo continuation: after a free slot reaches `ProcessEnemyData`, ROM rewrites its page/X/Y inputs while native C retains stale slot values. The first source-visible output divergence is sample 172 / `$03ae`, but `RelativeEnemyPosition` only exposes this upstream producer difference.

## ROM scope

ROM lines 7788-11084: EnemiesAndLoopsCore, loops/frenzy, ProcessEnemyData, positioning, groups, initialization and enemy handlers.

## Existing-code disposition

Replace forced-slot scanning in area.c; split stream parsing, initialization and handlers out of generic object code.

## Graph contract

Six ROM slots are dispatched by GameEngine; consumes area stream/block state and produces enemy RAM, collision/OAM/audio events.

## Admission S plan

1. **S1 complete (P1) — source ownership and stream boundary.** Map `EnemiesAndLoopsCore`, `ProcessEnemyData`, `ObjectOffset`, `Enemy_PageLoc`, stream tables, and all current C entry points; move stream ownership out of `area.c` without changing bytes. Evidence: the bounded title/demo route remains unchanged before source fixes.
2. **S2 active (P1 next) — loops, bounds, records, and position semantics.** Translate `LoopCommand`, page control, `ProcessEnemyData`, two/three-byte records, and position-before-bounds semantics. Evidence: sample 172 free-slot producer input and controlled page-crossing records.
3. **S3 planned — group, frenzy, and initialization dispatch.** Translate group/frenzy paths and initialization dispatch including special IDs.
4. **S4 planned — normal and special handlers.** Translate normal and special enemy handler paths using shared collision contracts.
5. **S5 planned — source-route closure.** Compare W1-1 stream, group/frenzy, pipe enemy and representative special actor routes.

## Acceptance

Stream bytes, inactive slots, page controls, initialization/actor state and OAM match ROM without fabricated spawn scans.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.

## S1 P1: ProcessEnemyData source boundary

The full existing `ProcessEnemyData` adapter, including requested-slot reservation and actor initialization, now lives in `src/game/enemy/stream.c`. `area.c` no longer exposes an enemy-spawn API; frame root and all tests consume the T19 API directly. This is a source-owner extraction only: the 600-sample continuation remains at its prior first work-RAM difference, sample 172 / `$03ae`, with 1,352 differing work-RAM bytes; CIRAM, palette, audio commands, and PPU scalars remain zero-difference. x64 and x86 each pass 78/78 CTest cases. OpenNT links the DOS MZ using `stream.c` in the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 5CF522794B24FBC422BA155E3FDF7CF9AF63FC5DC179D6DE8EB5598B21481275, mysmb32.exe SHA-256 4B540FB1BA25D0B486CCFA73549C34F6856C853F779B2E88F7A28334110EABA1, mysmb64.exe SHA-256 44EB05E0C686F71C3887ABAA91116DB292BEAAE106D71EA10B1595408D384AA0.
