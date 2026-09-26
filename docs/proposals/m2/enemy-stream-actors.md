# M2 candidate: Enemy stream and actors

## Status

**M2 T19 active — S5/P18.** Admission is triggered by the bounded title/demo continuation: after a free slot reaches `ProcessEnemyData`, ROM rewrites its page/X/Y inputs while native C retains stale slot values. The first source-visible output divergence is sample 172 / `$03ae`, but `RelativeEnemyPosition` only exposes this upstream producer difference.

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

## S4 P9: handler scratch-address closure

The complete S4 static audit searches every shared game writer for the fixed ROM scratch cells used by enemy, bubble, and misc OAM routes. No fixed scratch destination is slot-indexed: $03ae/$03b9/$03d1, $03b0/$03bb/$03d3, and $03b3/$03be/$03d6 each have one current-actor result. Remaining +slot expressions read true object arrays for source X/Y values or write the source EnemyOffscrBitsMasked array at $03d8; they are not aliases of temporary registers. This closes S4's normal/special handler audit and admits S5's source-reachable frame-route comparison. The physical adapters also retain the common control contract: J produces NES B and K produces NES A on both Win32 and DOS; the DOS regression passes in both x64 and x86 test trees. Full x64/x86 suites, shared DOS link, and all three refreshed artifacts accompany this closure packet.

## S5 P1: title-to-play source-route baseline

A fresh bounded 600-frame route was recorded from the original ROM at the NMI-return boundary and from the shared native frame snapshot: no input through frame 199, Start for frame 200, then Right from frame 360. The reference uses serial input $08 then $80; native uses decoded $10 then $01. The authoritative comparison records zero differences in CPU work RAM $0300-$07ff, both CIRAM pages, palette, visible OAM, audio command state, and all seven PPU-visible scalar fields. CPU zero page, stack, and $01f0 APU execution temporaries remain excluded from output equivalence. The x86 and x64 native recordings are byte-identical. This route proves the shared platform-independent output path at the S5 boundary; later S5 packets extend it to actor-producing scenarios rather than accepting synthetic slot edits.

## S5 P2: source-reachable movement and jump

The same NMI-return contract now covers a source-reachable first-area movement route: Start at frame 200, hold Right from frame 240, add A for frames 310–339, then retain Right. The original receives serial Start/Right/A bytes `$08`, `$80`, and `$81`; native receives decoded `$10`, `$01`, and `$81`. Across all 600 samples, CPU work RAM `$0300-$07ff`, both CIRAM pages, palette, visible OAM, audio command state, and all PPU-visible scalar fields have zero differences. The x86 and x64 native recordings remain byte-identical. The derived traces and comparator output stay under `build/t19-s5-p2`; no platform adapter owns the route or game decision.

## S5 P3: delayed source route and ownership transfer

A second source-reachable route warms through the first 600 frames and records frames 600–1199 while holding Right plus B, with periodic Right-plus-A jumps. It reaches scroll and actor-producing gameplay without forced object-slot writes. The first work-RAM difference is recorded sample 278 (global frame 878), at `$0301–$030d`; all visible output fields remain equal and x86/x64 native traces are byte-identical. The complete difference set is confined to the VRAM command buffer: `$0301` occurs in seven samples, `$0302–$0308` in 48, and `$0309–$030d` in 322. At the first sample the reference begins the timer command `$20,$7a,$03`, while native begins the preceding palette command. This is not an enemy stream or actor decision. Its ROM owners are `WriteBottomStatusLine` (line 1524), `PrintStatusBarNumbers` (line 2555), and their `RunGameTimer` caller; it is transferred to the unadmitted Screen, text and status slice. T19 makes no `area.c` change for this packet. Derived reference/native traces and the comparison live only in `build/t19-s5-p3-extended`.

## S5 P4: ProcessEnemyData row-$0e order

The delayed route isolated an inactive slot-zero page/X/YHigh/Y residue at the original `PositionEnemyObj → ParseRow0e` node. The native stream had consumed row `$0e` before `PositionEnemyObj`; it now writes the current `ObjectOffset` page/X first, handles the left/right boundary decision, writes `Enemy_Y_HighPos=1` and `Enemy_Y_Position=row<<4` for an in-range row, and only then consumes the third byte. A focused slot-two regression proves the precise page/X/YHigh/Y, world-selected AreaPointer/EntrancePage, offset increment, and page-select clear. Replaying the same frames 600–1199 route removes every difference in all six-slot enemy flag, ID, state, moving direction, X/Y speed, page/X/Y/Y-high, X/Y force, dummy, bounding-box, and stream-state arrays. CIRAM, palette, OAM, audio-command state, and all PPU-visible fields remain zero-difference; the only retained work-RAM difference is the separately transferred `$0301–$030d` status-buffer owner. x86/x64 full suites and the shared DOS MZ are rebuilt with this packet.

## S5 P5: HandleGroupEnemies

ROM group IDs $37–$3e now dispatch HandleGroupEnemies in the stream owner instead of falling into ordinary initialization. The translation preserves its source slot scan, 2/3 member count, Goomba/Buzzy hard-mode selection, Koopa selection, Y band, page carry after X plus $18, and CheckpointEnemyID handoff. Focused regression covers a $37 group crossing the page boundary. Full x64/x86 suites pass; DOS MZ and all three artifacts are refreshed with this packet.
## S5 P6: frenzy queue and end-of-data fallback

ROM `CheckFrenzyBuffer` now has one stream-owner translation. A pending `EnemyFrenzyQueue` is consumed before the area stream, reset to zero, and passed through `CheckpointEnemyID`; when `ProcessEnemyData` reaches the right extent or area end marker, `EnemyFrenzyBuffer` is used as the source fallback. With no buffer, the ROM's `VineFlagOffset == 1` fallback loads VineObject `$2f`; otherwise the slot remains inactive. Focused regressions cover queue priority, buffered end-of-data initialization, and the vine fallback. Full x64/x86 suites pass; the shared DOS MZ and all three artifacts were refreshed.

## S5 P7: BuzzyBeetleMutate

The ordinary two-byte stream path now preserves ROM `BuzzyBeetleMutate`: after the record ID is masked with `$3f`, ID 6 (Goomba) changes to ID 2 (Buzzy Beetle) only when `PrimaryHardMode` is nonzero, before `InitEnemyObject`. No stream position, record consumption, or initializer branch is otherwise changed. A focused primary-hard stream regression asserts the exact transformed ID. Full x64/x86 suites pass; the shared DOS MZ and all three artifacts are refreshed.
## S5 P8: sixth-slot power-up admission

ROM `CheckEndofBuffer` does not reject every non-row-0x0e record in object slot five. It reads the second byte, masks it with 0x3f, and continues only for PowerUpObject 0x2e; all other ordinary records return before page control or positioning. The stream owner now follows that precise exception, with a regression proving that 0x2e initializes in slot five. Full x64/x86 suites, shared DOS MZ, and all three artifacts accompany this packet.
## S5 P9: deterministic flying-Cheep stream fixture

The former flying-Cheep regression initialized game RAM with a fill byte but left the enemy-data low pointer, stream offset, page control, and first flag implicit. It now explicitly reads its two-byte record from PRG 0x8000 plus offset zero and begins with slot zero inactive. This changes no game logic; it makes the next InitEnemyFrenzy current-slot migration measurable rather than dependent on fill-byte residue. Full x64/x86 suites pass; the shared DOS MZ and all three artifacts are refreshed.
## S5 P10: physical J/K control correction

The documented physical-button layout is now J = NES B (run/fireball) and K = NES A (jump) in both Win32 and DOS. The correction is confined to platform keyboard adapters: the shared game receives the same ROM button bits on all targets, and no game state or rule is platform-specific. DOS scan-code regression asserts both keys directly; Win32 retains its button-bit adapter self-test. Full x64/x86 suites, shared DOS MZ build, and refreshed 16/32/64 artifacts accompany this packet.
## S5 P11: current-slot flying-Cheep initialization

ROM `$14` now travels through `ProcessEnemyData → InitEnemyObject → CheckpointEnemyID → InitEnemyFrenzy → InitFlyingCheepCheep` in the current `ObjectOffset`. `InitEnemyObject` retains the source stream Y-plus-eight setup before `CheckpointEnemyID` dispatches ID `$14`; `InitFlyingCheepCheep` has no free-slot scan and returns on its current slot when the frenzy timer or slot gate says so. The non-ROM `frame_root` spawner was removed. The focused stream regression starts from an actual two-byte `$14` record and proves the timer, PRNG-selected position/speed, current-slot flag and stream offset. A source-reachable 600-frame Start/Right/jump trace retains zero differences in work RAM `$0300-$07ff`, CIRAM, palette, visible OAM, audio commands, and all PPU scalars; x86/x64 native traces are byte-identical. Derived traces remain under `build/t19-s5-p11-regression`. Full x64/x86 suites, shared DOS MZ, and refreshed 16/32/64 artifacts accompany this packet.
## S5 P12: AreaFrenzy queue-to-flying-Cheep route

The original water-level producer is `AreaFrenzy`, which writes `FlyCheepCheepFrenzy` `$14` to `EnemyFrenzyQueue` rather than embedding `$14` in the enemy-data stream. The focused regression now drives that queue through `ChkEnemyFrenzy` into current slot two with no area source: it proves queue clear, frenzy-buffer retention, slot-local activation, timer, page/X, and below-screen Y result. This closes the producer-to-consumer edge for the P11 current-slot migration. Full x64/x86 suites, shared DOS MZ, and refreshed 16/32/64 artifacts accompany this packet.

## S5 P13: ChkEnemyFrenzy queue activation

ROM `ChkEnemyFrenzy` writes the pending `EnemyFrenzyQueue` ID to the current slot, activates its flag, clears `Enemy_State` and the queue, then enters `InitEnemyObject`. The shared stream owner now preserves that activation before `CheckpointEnemyID`; a timer-held Flying Cheep queue regression proves the current slot remains present rather than being silently discarded.

## S5 P14: Lakitu/Spiny current-slot controller

ROM `LakituAndSpinyHandler` is no longer a frame-root global scan. `$12` now follows `ProcessEnemyData → InitEnemyObject → CheckpointEnemyID → InitEnemyFrenzy` with the current `ObjectOffset`; the handler only scans ordinary slots in its source `CreateL` branch. When an existing Lakitu throws a Spiny, it writes the current slot directly, as `CreateSpiny` does. The focused stream regression verifies a real `$12` record activates and retains slot two while the reappearance path waits. The shared owner is used by all targets. Full x64/x86 suites pass 79/79 each; the shared DOS MZ links and all three executable artifacts are refreshed.
## S5 P15: Bowser-flame and fireworks current-slot controllers

The remaining `InitEnemyFrenzy` leaves now follow the same ROM slot contract. `$15 InitBowserFlame` and `$16 InitFireworks` receive the current `ObjectOffset` from `CheckpointEnemyID`; neither frame root nor either leaf searches for a free actor slot. Bowser flame retains both source branches, including the missing-Bowser timer/PRNG/right-extent fallback and the mouth branch's buffer clear. Fireworks scans all six source slots for the star flag and initializes the current slot's X/Y speeds in source order. Focused controllers supply the source-owned controller ID and timer precondition. Full x64/x86 suites pass; DOS links the same shared code and all three artifacts are refreshed.
## S5 P16: `$15` and `$16` source-record closure

P15's controller leaves are now exercised through real two-byte `ProcessEnemyData` records. The `$15` fixture proves current slot two takes the no-Bowser timer/PRNG/right-extent branch; the `$16` fixture proves current slot one finds a star flag in slot five and receives its source page, position, and speed state. Neither route injects a replacement actor after parsing. Full x64/x86 suites pass; DOS links the shared core and all three artifacts are refreshed.

## S5 P17: $17/$18 checkpoint dispatch order

CheckpointEnemyID now dispatches Bullet/Cheep frenzy $17 and StopFrenzy $18 before the normal-enemy initializer, matching the ROM jump table. This prevents the timer-gated controller returns from fabricating ordinary movement, state, bounding-box, or activation writes. Focused frenzy regressions pass; full target validation and refreshed artifacts accompany this packet.


## S5 P18: post-frenzy shared source-route check

The established 600-frame Start/Right/jump ROM trace was rerun after P17. x86 and x64 native traces are byte-identical (D06BE291...D64C8E6); the comparator reports zero differences for both CIRAM pages, palette, visible OAM, audio commands, and every PPU-visible scalar. Remaining CPU temporary RAM differences remain outside the output contract. Derived evidence is under uild/t19-s5-p18-regression.
## S5 P19: restore CheckpointEnemyID vertical staging

A fresh source-reachable running trace reached `HandleGroupEnemies` and exposed
that its second Goomba entered `CheckpointEnemyID` at `$b0`; the ROM then
writes `$b8`, while native had left `$b0`. The C translation had incorrectly
put the ROM `ADC #$08` in `mysmb_enemy_initialize_loaded`, bypassing group and
frenzy producers that jump directly to the checkpoint. The add now belongs
solely to `mysmb_enemy_checkpoint_loaded` for IDs `$00-$14`; the ordinary
stream initializer supplies only `row << 4`. The group regression asserts two
Goombas at `$b8`; Bullet/Cheep and firebar fixtures assert the same source
entry rule for direct normal and non-normal IDs. Replaying the exposing route
removes the enemy page/X/Y/state discrepancy. The remaining first difference
is the separately owned Goomba OAM scratch/output path (`$02d8`, `$04b4-$04b7`),
transferred to T16 rather than patched in the stream owner. Full x64/x86 CTest
passes 83/83; the shared DOS16 link succeeds and all three executable artifacts
are refreshed.

## S5 P20: current-slot EnemiesCollision ownership

`RunNormalEnemies` now invokes `EnemiesCollision` only from the already-audited ordinary actor route, after its existing `EnemyToBGCollisionDet` call and before `PlayerEnemyCollision`.  The former frame-root all-slot scan has been removed.  The shared collision owner follows the ROM current-`ObjectOffset` traversal: it compares only lower-numbered slots, consumes their previously prepared `GetEnemyBoundBox` results without writing any box, preserves `Enemy_CollisionBits[candidate]` with `SetBitsMask[current]`/clear semantics, and applies `ProcEnemyCollisions` with current/candidate operand order.  This removes the manufactured box for a newly streamed slot.  On the established 600-sample ROM route, visible OAM, palette, and all PPU-visible scalars are zero-difference; the first retained work-RAM difference moves to sample 584, while the former samples 232–346 box/OAM divergence is absent.  Full x64/x86 CTest passes 83/83; DOS16 links the same shared source.
