# M2 candidate: Blocks, items and misc

## Status

**M2 T22 active — S1/P2.**

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

## S1/P1 result

SetupJumpCoin -> JCoinC now retains its source-owned $00fe = $01 queue write after misc activation; core smoke asserts it. The source-reachable hidden-block trace is the ROM proof. No platform code participates.

## Acceptance

Block buffer, metatiles/CIRAM, item behavior, score/audio and OAM match reference.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
## S1/P2 ROM label-owner map

This packet is a source-map only: it changes no gameplay byte.  It separates
labels already owned by `src/game` from missing or cross-slice work before any
T22 implementation packet is admitted.

| ROM labels (listing line) | Required source order / state | Current C owner | S1 disposition |
| --- | --- | --- | --- |
| `Setup_Vine` → `VineObjectHandler` (6702–6783) | reserve enemy slot 5; grow on frame bit 1; relative/offscreen before `DrawVine`; retire all vine slots on horizontal offscreen; write metatile `$26` once height reaches `$20` | `objects.c`: `mysmb_objects_start_vine`, `mysmb_objects_step_vine`; `oam/vine_gfx.c`: `mysmb_objects_draw_vine` | Split owner exists, but its relative/offscreen/retirement order has no ROM trace. S3 must compare it; no renderer or platform may own it. |
| `ProcessCannons` → `BulletBillHandler` (6788–6875) | non-water gate; slots 2→0; LFSR/hard-mode timer selection; cannon spawns bullet bill; source then executes common bullet-bill route | **Absent** for cannon scheduler. `mysmb_objects_step_bullet_bills` owns only an already-created bullet bill. | S4 must add the missing game-side scheduler before invoking the existing actor handler. |
| `CoinBlock` → `SetupJumpCoin` → `JCoinC` → `FindEmptyMiscSlot` (6988–7037) | use slots 8→6, fall back to 8; state/speed/high-page writes; Square2 coin queue; tally and 1-up counter | `objects.c`: `mysmb_objects_start_jump_coin`; callers in head-bump/top-of-block paths | Queue write is proven by P1. Slot selection, coordinate carry and tally writes remain S2 trace obligations. |
| `MiscObjectsCore` → `ProcJumpCoin` / `ProcHammerObj` (7038–7143) | iterate 8→0; bit 7 selects hammer; jumping coin becomes floatey number; relative/offscreen/bounding box/draw follow the state step | `objects.c`: `mysmb_objects_step_misc`, `mysmb_objects_step_hammer`; game OAM helper | Present but loop direction and complete source output order require S3 trace evidence. |
| `SetupPowerUp` → `PowerUpObjHandler` → `GrowThePowerUp` → `RunPUSubs` (7150–7241) | slot 5; type normalisation; priority attribute; 4-frame emergence; only state >= 6 enters relative/offscreen/bbox/draw/player collision/bounds sequence | `objects.c`: `mysmb_objects_start_power_up`, `mysmb_objects_step_power_up`, `mysmb_objects_finish_power_up`; `oam/power_up_gfx.c` | Present split. S3 must prove the exact state threshold and `RunPUSubs` order against mushroom, flower, star and 1-up traces. |
| `PlayerHeadCollision` → `InitBlock_XY_Pos` → `BumpBlock` / `BrickShatter` (7244–7419) | blank write first; preserve BlockBumpedChk carry; block-state/metatile choice; carry into page location; bounce or break branch; invert control bit only at tail | `objects.c`: `mysmb_objects_start_head_bump`, `mysmb_objects_start_brick_chunks`, helpers | Current owner is T22; P2 will trace all matched metatile paths. `DestroyBlockMetatile`/VRAM buffer implementation is explicitly T18's area-output boundary. |
| `BlockCode` / `BrickQBlockMetatiles` / `BlockBumpedChk` (7349–7403) | table maps each matched metatile to coin, mushroom/flower, 1-up, vine or star; coin-brick timer selects old vs empty metatile | `objects.c`: metatile classifiers and `mysmb_objects_power_up_for_block` | Current predicate shortcuts must be audited table-by-table in S2; no new heuristic permitted. |
| `CheckTopOfBlock` / `SpawnBrickChunks` (7420–7467) | remove a coin one row above through `RemoveCoin_Axe`; spawn two coupled chunks with source speeds/positions | `objects.c`: `mysmb_objects_check_top_of_block`, `mysmb_objects_collect_coin`, `mysmb_objects_start_brick_chunks` | S2 owns byte/order checks. Area metatile command emission remains T18. |
| `BlockObjectsCore` → `BouncingBlockHandler` → `BlockObjMT_Updater` (7468–7560) | slots 1→0; gravity/movement; relative/offscreen/draw; replacement flag and paired chunk retirement | `objects.c`: `mysmb_objects_step_blocks`; `area.c`: `mysmb_area_apply_block_replacements` | Split follows the ROM producer/consumer boundary. S2 tests block state; T18 owns replacement writer bytes. |
| `FlagpoleObject` (3991–4015) → `FlagpoleRoutine` (6604–6701) | area object initializes slot 5; slide drives score-state handoff; flag/floatey-number OAM and offscreen cleanup | `area.c`: object decode; `oam/flagpole_gfx.c`: start/step | S4 owns routine-level trace. OAM code remains under `src/game`, never a platform adapter. |
| `ProcessWhirlpools` → `WhirlpoolActivate` (6519–6603) | water-level gate, area-parser data, player range and force; source selects whirlpool jump behavior | **Absent** as a scheduler/activation owner. `player.c` only has the shared jump parameter. | S4 must translate the missing game routine and call it in ROM frame order. |

### S1/P2 implementation boundary

S2 may modify only the rows headed by `PlayerHeadCollision` through
`BlockObjectsCore`, plus ROM-free tests and owner-local trace fixtures.  S3
owns vine, power-up and misc state machines.  S4 owns cannon, whirlpool and
flagpole.  A packet may call an existing T17 primitive or T18 area writer but
must not duplicate either routine's state transition.  All platform code stays
outside this map and may only submit the completed game frame.
