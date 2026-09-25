# M2 candidate: OAM, offscreen and graphics

## Status

**M2 T16 active — S3/P6.** T15/S4 is gated at the real-demo block/OAM boundary; T16 owns the prerequisite source structure and output primitives.

## ROM scope

ROM lines 14460-15069: player/enemy/misc graphics, relative positions, offscreen bits, bounding boxes, OAM writers and output handoff.

## Existing-code disposition

Reorganize every *_gfx.c and frame_snapshot writer by ROM OAM owner. render.c may only derive from canonical output, never infer actors.

## Graph contract

Consumes final gameplay state and produces source-ordered OAM plus game-owned sprite split/visible PPU state.

## Admission S plan

1. **S1 complete (P1-P2)** - Establish the OAM source tree without changing behavior: move each existing sprite writer under `src/game/oam/`, map every OAM byte writer, offset table and graphics helper to ROM labels, and forbid local relative/offscreen reconstruction in gameplay owners.
2. **S2 complete (P1-P2)** - Translate relative position, offscreen-bit and bounding-box writers.
3. **S3 active (P1-P5)** - Translate player, fireball and enemy/misc graphics dispatch, priority, animation and OAM order.
4. **S4 planned** - Compare OAM and sprite-0/status split across title, movement, objects, enemies and endgame.

## Acceptance

All 256 OAM bytes, ordering, attributes, offscreen behavior and PPU split are game-owned and reference-equal.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.

## S1 P1: physical OAM source tree

The former top-level `*_gfx.c` files mixed source-owned OAM writers with general gameplay code, which made it too easy to hide missing `RelativeBlockPosition` state behind a local coordinate computation.  This P is intentionally behavior-preserving: nineteen existing OAM writer translation units now live under `src/game/oam/`; `CMakeLists.txt` and the OpenNT source list consume those same paths.  The public game interface remains `objects.h` until later S1 packets establish exact owner headers, so callers do not acquire graphics policy.  `block_gfx.c` is deliberately moved with the OAM writers, but `BlockObjectsCore` stays in `objects.c`; this makes the forthcoming `RelativeBlockPosition -> GetBlockOffscreenBits -> DrawBlock` boundary explicit instead of adding it to a title-mode route.  The migration inventory and frame-output ledger remain the exhaustive label/byte checklist; S1/P2 will bind their rows to the new file owners before any logic changes. x64 and x86 each pass 78/78 CTest cases. OpenNT recompiles the same paths and links the DOS MZ; its established `OLDNAMES.LIB` warning remains. Refreshed artifacts: mysmb16.exe SHA-256 F5E6E63FAE6DBB00920430CCE2CD497C2DA00E496895988B719D9923E7164EE2, mysmb32.exe 8F4E00DFF79E618E1F09BEFC42EDEF1DF63ED7998C0212BA3441262E961E9AB7, and mysmb64.exe 2D6061877489B73F176BABE5B971992F5B1921879AC8735CE613684F90F6AB55.



## S1 P2: OAM API boundary

objects.h now exports only object-state, collision, movement, and mode-facing operations. The OAM writers are declared by src/game/oam/oam.h, which both the writers and their two callers (objects.c and rame_root.c) include explicitly. The boundary does not hide legitimate dependencies: OAM writers still include objects.h when they invoke a shared ROM geometry primitive, rather than cloning it. This P changes no state machine or rendering rule. x64 and x86 each pass 78/78 CTest cases; OpenNT relinks the DOS MZ with the established OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 1FD186D0868ECF2BE9822638C548826F8FA83E41E6AA05387314D145F02B043D, mysmb32.exe SHA-256 5CA22BE7EBAFA5B4327DE92F5DCF89CA8343939B8418775E213D9D381F97F78A, mysmb64.exe SHA-256 C66DAC32B91781B9309A503148AB17E9726AA73C6F46863BBE1FE088FCA15C2A.


## S2 P1: block relative-position and offscreen primitives

BlockObjectsCore now calls the translated RelativeBlockPosition and GetBlockOffscreenBits after gravity/movement and before the original DrawBlock/DrawBrickChunks call sites. lock_position.c implements the source GetObjRelativePosition, GetXOffscreenBits, GetYOffscreenBits, and GetOffScreenBitsSet semantics for block inputs. The initial implementation incorrectly indexed the Block_Rel_* outputs by ObjectOffset; the 600-frame actual demo trace exposed $03b2, and the source proves those outputs are fixed $03b1/ and $03bc/, while Block_OffscreenBits is fixed $03d4. The writer now consumes those fixed RAM cells. Against the source-reachable title-to-demo continuation, the first work-RAM difference remains sample 68 but moves from $03b1 to $03b3, and work-RAM differences fall from 8,520 to 6,196 bytes; CIRAM, palette, audio commands and all seven PPU scalars remain zero-difference for all 600 samples. OAM remains at its prior first visible difference (sample 124), proving the block refactor did not create a visual substitution. The remaining $03b3//-/ path is RelativeMiscPosition/jump-coin state and is the next S2 node. x64 and x86 each pass 78/78 CTest cases; OpenNT relinks the DOS MZ with the existing OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 B388CA396574B9DFFD6FEE6778E7365B03474ECF3AFBF454D39BC9A3B5ECB532, mysmb32.exe SHA-256 4F30DDEA4925DF429FB0DEEC2DD216DD4146A9F3EB54324F75035D996FE9B9F6, mysmb64.exe SHA-256 849A7170C94E3D839DCBD3F783C27C899E14A86168064D327AC96ECFA329C9BA.
## S2 P2: misc/jump-coin relative state and bounding box

`object_position.c` is now the shared ROM-position owner for both block and misc objects, so its filename no longer claims block-only ownership. The packet translates `RelativeMiscPosition`, `GetMiscOffscreenBits`, and the `GetMiscBoundBox` call site in `MiscObjectsCore`; the jump-coin drawing path consumes `Misc_Rel_XPos` rather than rebuilding a world-coordinate subtraction. `FindEmptyMiscSlot` also records `JumpCoinMiscOffset` at `$06b7`, as the source does. The inline jump-coin gravity approximation has been replaced with the existing exact `ImposeGravity` translation before the position/offscreen/bounding-box sequence. In the source-reachable title-to-demo continuation, this removes the prior first discrepancy at sample 68 / `$03d6` (misc offscreen bits); the first remaining work-RAM discrepancy is sample 72 / `$03d4` (block offscreen bits), and work-RAM differences fall from 3,432 to 3,417 bytes. CIRAM, palette, audio commands and all seven PPU scalars remain zero-difference across all 600 samples; OAM remains at its previous first visible mismatch (sample 124), so this packet introduces no substituted sprite result. x64 and x86 each pass 78/78 CTest cases. The OpenNT target recompiles and links the DOS MZ through the same sources; its established `OLDNAMES.LIB` warning remains. Refreshed artifacts: mysmb16.exe SHA-256 D629D36FD872890F9D00929CA128D16FF6989420BCF49CB0A29C9B135C70705D, mysmb32.exe SHA-256 2E7CE13A13A4D4186D3E9F409B16BC1318C488B28B5FE20D6365B3CDCBABDF13, mysmb64.exe SHA-256 405BC0271DEB294AD29DFFBB34423591802DBC9A82752C9A105AF524E07831A9.

## S3 P1: power-up fixed relative scratch

RunPUSubs now writes fixed Enemy_Rel_XPos ($03ae), Enemy_Rel_YPos ($03b9), and Enemy_OffscreenBits ($03d1); GetEnemyBoundBox and DrawPowerUp consume those same cells. The 600-sample route reduces work-RAM differences from 1,352 to 2 and moves the first one to sample 422. x64/x86 each pass 78/78; OpenNT links MZ. Artifacts: 16=186BEB7C457E86CFDCD0270B016D0D74F075D3E40C160FB357DEB2FB16137816, 32=A9AF9CEF351C9E28E9B954E1B389634753A4C0ED90B0FD0482E25D5E227A341B, 64=FF39EEBB84FFBA03E5FA4D03F596CA0CB42E21B65506F0926903CEBC3DF6BE6F.


## S3 P2: player geometry single-owner extraction

`RelativePlayerPosition` now has one owner in `src/game/oam/object_position.c`, alongside the source `GetObjRelativePosition` family. `player.c` retains source call order and gameplay decisions but calls that primitive. Its former private `BoundingBoxCore` table and writer are removed; every player, enemy, fireball and item route now calls the one `mysmb_world_set_bounding_box` implementation in `src/game/world/collision.c`. This is a behavior-preserving structural packet: it neither alters controls, collision decisions, OAM bytes, nor platform code. The 600-sample title-to-demo route remains exactly at the preceding baseline: one two-byte work-RAM discrepancy at sample 422, while CIRAM, palette, audio commands and all seven PPU scalars remain equal. Full x64/x86 CTest and the OpenNT MZ build are required before this packet is committed; refreshed three-architecture executables are attached to the same P.

## S3 P3: player graphics/OAM single-owner extraction

ROM labels `PlayerGfxHandler` through `ExPlyrAt`, together with `GetPlayerOffscreenBits`, now live in `src/game/oam/player_gfx.c`; its public calls are the OAM API `mysmb_oam_draw_player` and `mysmb_oam_draw_intermediate_player`. `player.c` contains no player graphics dispatch, tile selection, OAM-row writer, offscreen-mask writer, or `PlayerGraphicsTable` access. `RenderPlayerSub` invokes the existing single `RelativePlayerPosition` primitive rather than rebuilding the relative coordinates locally. The inventory binds every relocated ROM label to this packet, with status intentionally `ported; route trace pending`: the current 600-frame title-to-demo route proves the extraction preserved the prior output baseline but does not close all player animation and fireball-throw branches. x64/x86 full CTest, OpenNT MZ link, and refreshed executable artifacts are required for the P commit.

## S3 P4: fireball relative-coordinate OAM ownership

`RelativeFireballPosition` now owns the precise ROM mapping `$74/$8d/$d5 -> $03af/$03ba` in `src/game/oam/object_position.c`.  `DrawFireball` and `DrawExplosion_Fireball` consume only those fixed relative scratch bytes and the original sprite-offset arrays (`FBall_SprDataOffset` `$06f1`, `Alt_SprDataOffset` `$06ec`); neither reconstructs a host/world coordinate.  `FireballObjCore` retains its source order and explicitly invokes the relative-position primitive on its explosion branch before the OAM writer, matching the ROM `FireballExplosion` leaf.  The existing focused fireball smoke now exercises the corrected mapping, including normal and explosion OAM bytes.  The broader `FireballObjCore`, offscreen-bit, bounding-box and collision paths remain assigned to their respective source nodes and require a controlled reference route before they can be marked conformant.  Validation passed: x64 78/78 CTest, x86 78/78 CTest, the OpenNT MZ link (with its existing `OLDNAMES.LIB` warning), and the focused smoke. The existing 600-sample title-to-demo trace stays at two work-RAM bytes in one sample; CIRAM, palette, audio commands and all seven PPU scalar fields are equal. OAM remains an open baseline: 3,622 bytes differ, first at sample 124 / offset `$d8`. Refreshed artifacts: `mysmb16.exe` CB9DC61CE72254F04D53E34F1E0BA4EB3F9972A42ADC5960FA6E4CD9AD310727, `mysmb32.exe` 6DC1D145E6AD15D358316C65DF8CA3CCA9C61D15AE46F13C6277F89EA3817A0A, `mysmb64.exe` 99182911214D66F9E6428F94B2555045669C44ADFF5FDF25FBD175FDCF616944.
## S3 P5: fireball fixed offscreen and bounding-box scratch

`GetFireballOffscreenBits` now lives with the source `GetXOffscreenBits`/`GetYOffscreenBits` primitives in `src/game/oam/object_position.c`.  As the ROM requires, each slot selects its own SprObject page/X/Y input through `GetProperObjOffset`, but the result is written to the single `FBall_OffscreenBits` cell `$03d2`; `FireballObjCore` performs the original `$cc` mask from that fixed cell.  `GetFireballBoundBox` now consumes the same fixed `Fireball_Rel_XPos/$03af` and `Fireball_Rel_YPos/$03ba` pair that the preceding relative-position call writes, while preserving slot-specific controls `$04a0/$04a1` and output boxes `$04c8/$04cc`.  The focused regression covers slot one explicitly, including the fixed relative/offscreen cells and its separate OAM/bounding-box destinations. The existing 600-frame reference route remains unchanged at its prior two-byte/one-sample work-RAM difference and its open OAM baseline; this route does not spawn a fireball. Validation passed: x64 78/78 CTest, x86 78/78 CTest, focused slot-one smoke, and the OpenNT MZ link (with its existing `OLDNAMES.LIB` warning). Refreshed artifacts: `mysmb16.exe` 1ABB2595D65B5B9FD2082B3686E41D9F69692386B88B787336962F02A1499E4E, `mysmb32.exe` D71A9D6FFE91DF4678DB4996013B0937174069772DF9911A49ECE69572FE5478, `mysmb64.exe` 1B720FF277046CD037A9FAF1307963877A6FF103559F2262FB20F010A193179E.
## S3 P6: enemy relative-coordinate source interface

ROM `RelativeEnemyPosition -> VariableObjOfsRelPos -> GetObjRelativePosition` now has one T16 owner in `src/game/oam/object_position.c`, exported as `mysmb_oam_relative_enemy_position`. The selected enemy slot supplies X/Y inputs; it writes the fixed `Enemy_Rel_XPos/$03ae` and `Enemy_Rel_YPos/$03b9` scratch pair after subtracting `ScreenLeft_X_Pos`. It does not decide collision, enemy state, score, audio, or platform output. A direct shared-core regression proves slot three writes those fixed cells, so T17's later `HandleEnemyFBallCol` migration can consume the source interface instead of reconstructing coordinates. Full x64 and x86 suites pass 79/79 each; the OpenNT DOS MZ relinks from the same shared source with its established OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 0A86CB50530729FB145861438E819182EC2B686380FD06C04E9B1B9825B9FDC6, mysmb32.exe SHA-256 44B50661F67539E475F7A2C4530FD58ABBCCF804E09A3E381A3FF9403990E36F, mysmb64.exe SHA-256 1BA20F45C279232E475697BB7A0A00DDC76A7B1C3CEC437180C3A16CD4F795FC.