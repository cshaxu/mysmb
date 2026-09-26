# M2 candidate: Enemy stream and actors

## Status

**M2 T19 active — S4/P8.** Admission is triggered by the bounded title/demo continuation: after a free slot reaches `ProcessEnemyData`, ROM rewrites its page/X/Y inputs while native C retains stale slot values. The first source-visible output divergence is sample 172 / `$03ae`, but `RelativeEnemyPosition` only exposes this upstream producer difference.

## ROM scope

ROM lines 7788-11084: EnemiesAndLoopsCore, loops/frenzy, ProcessEnemyData, positioning, groups, initialization and enemy handlers.

## Existing-code disposition

Replace forced-slot scanning in area.c; split stream parsing, initialization and handlers out of generic object code.

## Graph contract

Six ROM slots are dispatched by GameEngine; consumes area stream/block state and produces enemy RAM, collision/OAM/audio events.

## Admission S plan

1. **S1 complete (P1) — source ownership and stream boundary.** Map `EnemiesAndLoopsCore`, `ProcessEnemyData`, `ObjectOffset`, `Enemy_PageLoc`, stream tables, and all current C entry points; move stream ownership out of `area.c` without changing bytes. Evidence: the bounded title/demo route remains unchanged before source fixes.
2. **S2 active — loops, bounds, records, and position semantics.** P1 first relocates the complete `GameEngine → ProcFireball_Bubble → EnemiesAndLoopsCore` schedule into `game/enemy/core`; P2 translates `LoopCommand`, page control, two/three-byte records, sixth-slot rules, and position-before-bounds semantics. Evidence: sample 172 free-slot producer input and controlled page-crossing records.
3. **S3 active — group, frenzy, and initialization dispatch.** Translate group/frenzy paths and initialization dispatch including special IDs.
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

## S3 P3: Enemy initialization dispatch ownership boundary

The existing native translation of `InitEnemyObject → CheckpointEnemyID → InitEnemyRoutines` now has one T19 owner in `src/game/enemy/init.c`.  `stream.c` retains record parsing, page/bounds handling, persistent frenzy request routing, and stream-offset consumption; it calls the explicit initializer only after a loadable ordinary record has been positioned.  The moved dispatch preserves its prior ID branches and RAM writes for normal enemies, Hammer Bros, water enemies, firebars, platforms, Bowser, and the OAM handoff marker.  This is extraction only.  Full x64/x86 CTest is 79/79 for each target and the OpenNT DOS MZ links the same module.

## S3 P4: Bowser-flame frenzy ownership boundary

`InitEnemyFrenzy → InitBowserFlame` now has one T19 owner in `src/game/enemy/frenzy.c`.  The moved spawn routine retains its living-Bowser validation, first-free regular slot search, PRNG target selection, page/X/Y derivation, collision-box assignment, activation and frenzy-buffer clear.  `ProcBowserFlame` remains an S4 handler concern.  This is ownership-only; full x64/x86 CTest is 79/79 and the OpenNT DOS MZ relinks from the shared source.

## S3 P5: Stop-frenzy dispatch restoration

ROM `EndFrenzy` is now translated in `game/enemy/frenzy.c` and dispatched by `InitEnemyObject` when the `$18 Stop_Frenzy` controller is loaded. It scans slots 5 through 0, clears every Lakitu flag, clears `EnemyFrenzyBuffer`, then removes the current controller slot. A focused regression proves both Lakitu removals and preservation of a non-Lakitu slot. x64/x86 are 79/79; DOS links the same shared code.

## S3 P6: InitEnemyObject checkpoint split

The translated `InitEnemyObject` now writes stream row Y/ID and enters a separate `CheckpointEnemyID → InitEnemyRoutines` API. Special spawners can enter that checkpoint after their own source-defined position setup, matching ROM calls such as `PutAtRightExtent → CheckpointEnemyID`. Existing stream behavior is unchanged. x64/x86 are 79/79 and the DOS MZ links the same shared owner.

## S3 P7: Bullet Bill/Cheep-Cheep frenzy restoration

ROM `BulletBillCheepCheep` is now owned by `game/enemy/frenzy.c`, reached from the single `CheckpointEnemyID` special-controller dispatch in `game/enemy/init.c`. Both water Cheep-Cheep selection and land Bullet Bill selection join the ROM’s shared `Set17ID → GetRBit → PutAtRightExtent → CheckpointEnemyID` tail: the unique `BitMFilter` height bit, screen-right `+ $20` carry, `FinishFlame` dummy result, `$20` frenzy timer, and target actor initialization are shared rather than copied by branch. The persistent `$17` frenzy request is written at the `InitEnemyFrenzy` boundary. This packet also corrects pre-existing random-register off-by-one accesses: `PseudoRandomBitReg` is `$07a7`; Flying Cheep uses `+1` for timer/branch and `+2` only for the third-byte override, while Bowser flame and Bullet/Cheep use the base byte. Focused regressions cover water and land branches, duplicate-Bill suppression, and all three Flying-Cheep PRNG bytes. Full x64/x86 CTest is 79/79 each; the DOS MZ links the same shared code.
## S3 P8: Fireworks frenzy ownership boundary

ROM `InitEnemyFrenzy → InitFireworks` now has one T19 owner in `game/enemy/frenzy.c`. The migration moves the complete controller leaf, including its timer gate, descending star-flag scan, fireworks counter decrement, table-derived position/page carry, and new-object activation. `RunFireworks` and `RunStarFlagObj` remain in `endgame_objects.c`; frame order is unchanged, with the existing call site now targeting the T19 API. The endgame regression calls the explicit frenzy owner. Full x64/x86 CTest is 79/79 each; OpenNT links the same source to DOS MZ.
## S4 P1: Fireworks completion sound restoration

The S4 ROM audit of `RunFireworks → FireworksSoundScore` found that the native completion branch wrote `$01` to `Square2SoundQueue`. The ROM writes `Sfx_Blast`, `$08`, after clearing the actor flag and before awarding the 500-point score. The shared endgame owner now writes `$08`; its focused regression asserts flag removal, graphics counter progression, and the source sound byte. Full x64/x86 CTest is 79/79 each; OpenNT links the same source to DOS MZ.
## S4 P2: Endgame relative scratch restoration

The `RunFireworks`/`RunStarFlagObj` audit restored source-owned fixed scratch semantics. `Enemy_Rel_XPos` `$03ae` and `Enemy_Rel_YPos` `$03b9` are fixed `RelativeEnemyPosition` outputs, not per-slot arrays; endgame code no longer adds the actor slot. `RunFireworks` then copies the pair in source order to `Fireball_Rel_XPos` `$03af` and `Fireball_Rel_YPos` `$03ba` before explosion drawing. The endgame regression exercises a nonzero star-flag slot and asserts both fixed pairs. Full x64/x86 CTest is 79/79 each; OpenNT links the same source to DOS MZ.
## S4 P3: Star-flag timer tick sound restoration

The `RunStarFlagObj → AwardGameTimerPoints` audit restored `Sfx_TimerTick` `$10` in `Square2SoundQueue`; native C had written `$02`. The focused state-machine regression enters task 2 with a nonzero game timer and frame-counter bit 2 set, asserting both the timer decrement and `$10` command. Full x64/x86 CTest is 79/79 each; OpenNT links the same source to DOS MZ.
## S4 P4: Bowser-flame relative scratch restoration

`ProcBowserFlame` reaches `RelativeEnemyPosition` before its state gate. Its C OAM collaborator incorrectly treated fixed `Enemy_Rel_XPos` `$03ae` and `Enemy_Rel_YPos` `$03b9` as slot-indexed arrays. The owner now writes the fixed pair, and a slot-2 OAM regression asserts that adjacent scratch bytes remain unchanged. Full x64/x86 CTest is 79/79 each; OpenNT links the same source to DOS MZ.
## S4 P5: RunNormalEnemies fixed scratch and dispatch restoration

ROM `RunNormalEnemies` (`$d68b`) now follows its source order in the shared game core: clear `Enemy_SprAttrib,x`, run `GetEnemyOffscreenBits`, run `RelativeEnemyPosition`, emit `EnemyGfxHandler` OAM, then enter the ordinary collision/movement branch. `Enemy_Rel_XPos` `$03ae`, `Enemy_Rel_YPos` `$03b9`, and `Enemy_OffscreenBits` `$03d1` are fixed scratch outputs for the current actor, never per-slot arrays. The normal-enemy, Goomba, Cheep-Cheep, retainer and jumpspring renderers no longer write slot-indexed aliases; their fixtures explicitly construct ROM-valid screen/object page and Y-high state. Focused OAM/collision probes and full x64/x86 CTest each pass 79/79. OpenNT relinks the shared DOS MZ with its established `OLDNAMES.LIB` warning. All three packaged executables were refreshed.

## S4 P6: aquatic and piranha fixed scratch restoration

ROM `RunNormalEnemies → RelativeEnemyPosition → EnemyGfxHandler` supplies one fixed `Enemy_Rel_XPos` `$03ae`, `Enemy_Rel_YPos` `$03b9`, and `Enemy_OffscreenBits` `$03d1` result to the Piranha, Bloober, and Podoboo graphics leaves. Their C handlers no longer add actor slots to these source addresses and now consume the complete vertical-plus-horizontal `GetEnemyOffscreenBits` result. The three OAM fixtures explicitly establish visible object page, screen edges, and `Enemy_Y_HighPos = 1`, rather than relying on fill-byte artefacts. Focused OAM tests and full x64/x86 CTest each pass 79/79; OpenNT relinks the same DOS MZ with the established `OLDNAMES.LIB` warning. The required 16/32/64 artifacts were refreshed.

## S4 P7: platform and Bowser-flame fixed scratch restoration

ROM `RunSmallPlatform` and `RunLargePlatform` call `RelativeEnemyPosition` immediately before their drawing leaves, so `$03ae/$03b9` are fixed current-actor outputs. `ProcBowserFlame → DrawFlameLoop → GetEnemyOffscreenBits` likewise uses fixed `$03ae/$03b9/$03d1`. The shared platform and flame OAM owners no longer add a slot to those addresses and use the complete enemy offscreen result. Focused OAM tests and full x64/x86 CTest pass 79/79; OpenNT relinks the DOS MZ. The 16/32/64 artifacts were refreshed.

## S4 P8: Bubble and hammer fixed scratch restoration

ROM `ProcAirBubbles` runs `RelativeBubblePosition → GetBubbleOffscreenBits → DrawBubble` for slots 2 through 0, using fixed `Bubble_Rel_XPos` `$03b0`, `Bubble_Rel_YPos` `$03bb`, and `Bubble_OffscreenBits` `$03d3`; the final fixed values therefore belong to slot 0 while slot 2 OAM remains drawn. `RelativeMiscPosition → GetMiscOffscreenBits → DrawHammer` similarly uses fixed `$03b3/$03be/$03d6`. The shared bubble and hammer owners no longer fabricate slot-indexed scratch arrays, and Bubble regression explicitly verifies loop-final scratch separately from slot-2 OAM. Full x64/x86 CTest passes 79/79 each; the shared DOS MZ relinks and all three artifacts were refreshed.
