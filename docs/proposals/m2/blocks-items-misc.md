# M2 candidate: Blocks, items and misc

## Status

**M2 T22 active — S1/P2, S2/P1 and S4/P1.**

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

## S2/P1: restore BrickCoinTimerFlag multi-coin branch

The controller-only page-twelve route transferred ROM `$06bc=BrickCoinTimerFlag` from T17: it was `$01` in every reference sample and `$00` in native C.  ROM `BlockBumpedChk` initializes `BrickCoinTimer=$0b` and increments the flag only on the first `$58/$5d` multi-coin brick bump; while the timer remains nonzero it retains the brick metatile, otherwise it emits `$c4`.  `objects.c` now follows that exact branch in the shared block-bump owner.  The focused regression covers first initialization and expired-timer behavior.  In the same 600-frame page-twelve route, the persistent `$06bc` mismatch disappears; first work-RAM/OAM mismatch is now sample 362, with later CIRAM differences downstream.  Full x64 and x86 CTest pass 83/83; OpenNT links the shared DOS MZ.  Artifacts: mysmb16.exe `CD637756EDB65712673DE10614AB2696520E9B63B3379517E82B36D87A384A44`, mysmb32.exe `D0CA1D1B71FD9D6698C5B1D1598FC716859F3C6ECC3A4BBE1C5C83B88FB63104`, mysmb64.exe `FE975D0F62596EE69B277DCA2AFA801B74C2280C2FA6F66F6E84DD18BE3A0C04`.
## S4/P1: restore FlagpoleRoutine frame order and fixed work bytes

ROM `GameEngine` reaches `FlagpoleRoutine` after its player/scroll update and
`MiscObjectsCore`.  The native root previously ran the flagpole before that
update.  Its `FPGfx` port also treated the slot-five input offset as an offset
into the outputs.  Direct ROM inspection shows `GetEnemyOffscreenBits` and
`RelativeEnemyPosition` select slot five only for input, then write the fixed
`Enemy_OffscreenBits` `$03d1`, `Enemy_Rel_XPos` `$03ae` and
`Enemy_Rel_YPos` `$03b9` bytes which `FlagpoleGfxHandler` consumes.

The shared game root now invokes the routine at the source position.  The
shared OAM writer now writes and consumes those fixed bytes.  The focused
smoke asserts all three work bytes and the resulting OAM.  On the existing
600-frame controller-only page-twelve route, this removes the former first
residual at sample 362 (`$03ae`) and reduces flagpole OAM divergence to three
bytes across three late samples; remaining work/CIRAM residuals first occur at
sample 526 and stay queued for their source owners.  No platform file changed.
Artifacts: mysmb16.exe CBDC82F47E98049B62586A9ACE5736F219FF906803CA999C333EDF43B557C48D; mysmb32.exe 705D76A5D9559838309E5960E09C05A9FDCDD08CDCEC4D56FEC04EF29CC8AEF5; mysmb64.exe 3D83CA4D91CB4C50EDC4EB05EF971EB803CED17F81EA16524A01D8F22865A55D.
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