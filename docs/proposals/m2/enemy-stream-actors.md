# M2 candidate: Enemy stream and actors

## Status

**M2 T19 active — S3/P2.** Admission is triggered by the bounded title/demo continuation: after a free slot reaches `ProcessEnemyData`, ROM rewrites its page/X/Y inputs while native C retains stale slot values. The first source-visible output divergence is sample 172 / `$03ae`, but `RelativeEnemyPosition` only exposes this upstream producer difference.

## ROM scope

ROM lines 7788-11084: EnemiesAndLoopsCore, loops/frenzy, ProcessEnemyData, positioning, groups, initialization and enemy handlers.

## Existing-code disposition

Replace forced-slot scanning in area.c; split stream parsing, initialization and handlers out of generic object code.

## Graph contract

Six ROM slots are dispatched by GameEngine; consumes area stream/block state and produces enemy RAM, collision/OAM/audio events.

## Admission S plan

1. **S1 complete (P1) — source ownership and stream boundary.** Map `EnemiesAndLoopsCore`, `ProcessEnemyData`, `ObjectOffset`, `Enemy_PageLoc`, stream tables, and all current C entry points; move stream ownership out of `area.c` without changing bytes. Evidence: the bounded title/demo route remains unchanged before source fixes.
2. **S2 active — loops, bounds, records, and position semantics.** P1 first relocates the complete `GameEngine → ProcFireball_Bubble → EnemiesAndLoopsCore` schedule into `game/enemy/core`; P2 translates `LoopCommand`, page control, two/three-byte records, sixth-slot rules, and position-before-bounds semantics. Evidence: sample 172 free-slot producer input and controlled page-crossing records.
3. **S3 planned — group, frenzy, and initialization dispatch.** Translate group/frenzy paths and initialization dispatch including special IDs.
4. **S4 planned — normal and special handlers.** Translate normal and special enemy handler paths using shared collision contracts.
5. **S5 planned — source-route closure.** Compare W1-1 stream, group/frenzy, pipe enemy and representative special actor routes.

## Acceptance

Stream bytes, inactive slots, page controls, initialization/actor state and OAM match ROM without fabricated spawn scans.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.

## S1 P1: ProcessEnemyData source boundary

The full existing `ProcessEnemyData` adapter, including requested-slot reservation and actor initialization, now lives in `src/game/enemy/stream.c`. `area.c` no longer exposes an enemy-spawn API; frame root and all tests consume the T19 API directly. This is a source-owner extraction only: the 600-sample continuation remains at its prior first work-RAM difference, sample 172 / `$03ae`, with 1,352 differing work-RAM bytes; CIRAM, palette, audio commands, and PPU scalars remain zero-difference. x64 and x86 each pass 78/78 CTest cases. OpenNT links the DOS MZ using `stream.c` in the same shared source list with the established `OLDNAMES.LIB` warning. Refreshed artifacts: mysmb16.exe SHA-256 5CF522794B24FBC422BA155E3FDF7CF9AF63FC5DC179D6DE8EB5598B21481275, mysmb32.exe SHA-256 4B540FB1BA25D0B486CCFA73549C34F6856C853F779B2E88F7A28334110EABA1, mysmb64.exe SHA-256 44EB05E0C686F71C3887ABAA91116DB292BEAAE106D71EA10B1595408D384AA0.

## S2 P1: actor dispatch boundary

`frame_root.c` no longer contains fireball ordering, the six `ObjectOffset` passes, normal-enemy routing, sixth-slot power-up routing, stream invocation, or floatey-number ordering. Those ROM-owned operations now have one shared entry, `mysmb_enemy_core_step`, in `src/game/enemy/core.c`; its sole caller is the GameEngine mode route. This is a relocation only: the bounded 600-sample continuation is byte-identical to the prior baseline at the first meaningful work-RAM divergence (sample 172 / `$03ae`, 1,352 differing work-RAM bytes); CIRAM, palette, audio state, and PPU scalar outputs remain zero-difference. x64 and x86 each pass 78/78 tests. The OpenNT large-model build links an MZ image with the same module. Refreshed artifacts: mysmb16.exe SHA-256 F3E610D2048A2D62638EF5B00736F4AC5E72586A9BA4E6BD30418BF9D8643C69, mysmb32.exe SHA-256 F2FA32FA2085E31C3EE7DA2CEE258C7D6827513E5095CA43A863A706A7A65DBB, mysmb64.exe SHA-256 3E37F8AE550FED6514A63EEA517ECAF063036C68BC3932D21D209116836DAB27.

## S2 P2: current ObjectOffset stream entry

The GameEngine actor path now calls `mysmb_enemy_stream_process_current(game, source, ObjectOffset)` for every empty slot, including the sixth slot. `ProcessEnemyData` records its page/X into that same slot before the right-boundary decision, and it no longer reserves sibling slots or searches the first free normal slot. The sixth slot rejects ordinary records before page-control/activation, matching `CheckEndofBuffer`; `process_next` remains only as an isolated-test convenience and is absent from the game-frame call path. The 600-sample ROM continuation reduces total CPU-RAM differences from 29,786 to 24,226 while retaining the known first work-RAM difference at sample 172 / `$03ae` (1,352 bytes); CIRAM, palette, audio state, and PPU scalars remain zero-difference. x64 and x86 each pass 78/78 tests. The OpenNT large-model build links the same source to an MZ executable. Refreshed artifacts: mysmb16.exe SHA-256 C0A56CC53CD4A4EAC3BE0A0F490D2B868958D3B9E3C320CCE93D9389F651D6C0, mysmb32.exe SHA-256 F8955A2DC2BF9069CC13BFC6832D7364AB10AF985CE8993D4F0EA7951401185D, mysmb64.exe SHA-256 F4D913C01608982FA55EAA44F027170454CB8EAF2582EF10595154B60FD3C677.
## S2 P3: actor downward-movement ownership boundary

`MoveD_EnemyVertically` and its `SetHiMax`/`ImposeGravitySprObj` arithmetic no longer live in the catch-all `objects.c`.  They have one shared actor owner in `src/game/enemy/movement.c`, declared by `src/game/enemy/movement.h`; all existing Lakitu, Spiny, Hammer Bro, Cheep-Cheep, Bowser, and bridge-collapse callers retain their original amount/max-speed literals and call sequence.  This is extraction only: no RAM value, branch, sprite write, or platform path changes.  The DOS build now gives source-relative object names to OpenNT, so `game/enemy/movement.c` and `game/world/movement.c` cannot overwrite one another as `movement.obj`; the resulting 16-bit link consumes the same source module as x86 and x64.  Full x64/x86 CTest is 79/79 for each target and the OpenNT MZ relinks with its established `OLDNAMES.LIB` warning.  This establishes the actor-side extraction pattern; later S2/S3/S4 packets move only complete ROM-labelled function groups, never new logic into `objects.c`.
## S3 P1: Lakitu/Spiny frenzy ownership boundary

The complete ROM group `PlayerLakituDiff → MoveLakitu → LakituAndSpinyHandler`, together with the Spiny egg's `EnemyToBGCollisionDet` landing consumer, now has one T19 owner in `src/game/enemy/frenzy.c`.  `frame_root.c` calls its explicit T19 interface; `objects.c` has neither the group nor its private helper.  The moved functions retain their existing state writes, free-slot scan order, Lakitu reappearance counter, screen-right page carry, Spiny spawn values, landing tile probes, and calls into the separately owned T17 movement/collision primitives.  This P is an owner extraction only: it does not redefine frenzy scheduling or initialization policy.  The existing direct Lakitu/Spiny regressions now invoke the T19 API.  Full x64/x86 CTest is 79/79 for each target and the OpenNT DOS MZ relinks from the same shared source set with its established `OLDNAMES.LIB` warning.
## S3 P2: Flying Cheep frenzy spawn ownership boundary

The complete `InitEnemyFrenzy → InitFlyingCheepCheep` spawn routine now has one T19 owner in `src/game/enemy/frenzy.c`.  Its PRNG reads, free-slot scan, hard-mode slot gate, player-relative page/X calculation, timer selection, and enemy RAM writes retain the prior translated ROM sequence.  `frame_root.c` and the focused spawn probes use the explicit T19 interface.  `MoveFlyingCheepCheep` remains in `objects.c` for S4, where the ordinary/special actor handler package will be migrated as its own complete ROM-labelled group.  This P changes ownership only; it does not redefine group/frenzy scheduling or initialization policy.  Full x64/x86 CTest is 79/79 for each target and the OpenNT DOS MZ relinks from the same shared source set with its established `OLDNAMES.LIB` warning.
