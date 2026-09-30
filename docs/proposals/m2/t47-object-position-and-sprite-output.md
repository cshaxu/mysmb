# M2 T47: object position, offscreen bits and sprite output

## Task contract

T47 owns the 40 consecutive original source labels from `ExPlyrAt`
(line 14781) through `SetHFAt` (line 15040), ending before the sound
engine. All 40 are incomplete and currently received by M2 T16 S4.
The incoming baseline is **1,709 / 1,992**; the maximum is **1,749 /
1,992**. The owner-local ROM and reviewed listing establish control,
RAM/OAM reads and writes, and PRG data offsets. Raw traces and generated
work remain under ignored `build/`. Platform code cannot contain game
logic. Each S performs node-level ROM-to-C control/read/write comparison
and separate focused native x86/x64, DOS16, purity and three-EXE
operational verification. T closure adds a cross-chain route matrix.

| S | Original source-order labels | Count | Shared owner and route |
| --- | --- | ---: | --- |
| S1 | `ExPlyrAt` | 1 | `player_gfx.c`; GameEngine player attribute child |
| S2 | `RelativePlayerPosition`, `RelativeBubblePosition`, `RelativeFireballPosition`, `RelWOfs`, `RelativeMiscPosition`, `RelativeEnemyPosition`, `RelativeBlockPosition`, `VariableObjOfsRelPos`, `GetObjRelativePosition` | 9 | `object_position.c`; GameEngine actor-position calls and bounded object variants |
| S3 | `GetPlayerOffscreenBits` | 1 | `player_gfx.c`; GameEngine player offscreen child |
| S4 | `GetFireballOffscreenBits`, `GetBubbleOffscreenBits`, `GetMiscOffscreenBits`, `ObjOffsetData`, `GetProperObjOffset`, `GetEnemyOffscreenBits`, `GetBlockOffscreenBits`, `SetOffscrBitsOffset`, `GetOffScreenBitsSet`, `RunOffscrBitsSubs`, `XOffscreenBitsData`, `DefaultXOnscreenOfs`, `GetXOffscreenBits`, `XOfsLoop`, `XLdBData`, `ExXOfsBS`, `YOffscreenBitsData`, `DefaultYOnscreenOfs`, `HighPosUnitData`, `GetYOffscreenBits`, `YOfsLoop`, `YLdBData`, `ExYOfsBS`, `DividePDiff`, `SetOscrO`, `ExDivPD` | 26 | `object_position.c`; original object offscreen helper chain with actor variants |
| S5 | `DrawSpriteObject`, `NoHFlip`, `SetHFAt` | 3 | shared game OAM sprite writer; original sprite-output caller |
| **Total** | **14781–15040** | **40** | |

S1 and S3 are single labels because the source sequence crosses from
player graphics to object positioning and back; they cannot be merged
with nonadjacent or differently owned nodes. S2 and S4 keep adjacent
actor variants and their common helpers together, with separate
ROM-reachable variants for each branch family under one GameEngine
frame route. The S2 exit is `GetObjRelativePosition`; its outgoing
calls into the later offscreen chain receive no premature credit. S4
ends at `ExDivPD`, and S5 takes the distinct sprite-writing boundary.

All 40 labels are intended ROM-match completions, not mapping-only
audits. An S may close with fewer matches only if it names the exact
remaining labels, failed track and accepted receiving successor. The
canonical inventory and `NODE_PROGRESS.md` retain node-level status;
the node/task ledger records custody transfer on each admission.

## S1 admission: player attribute exit

Entry and exit are the original `ExPlyrAt` at `$f129`, immediately
after T46 `C_S_IGAtt`; successor in source order is S2
`RelativePlayerPosition`. Exact scope and intended new match:
`ExPlyrAt` (incoming **audited; evidence incomplete**), one label.
Baseline **1,709 / 1,992**, maximum **1,710 / 1,992**. The original
GameEngine player graphics child naturally reaches the final RTS via
attribute-changing and unchanged paths. Compare the source branch
successors and complete RAM/OAM output against the shared C
`mysmb_oam_check_player_attributes` path. No new game behavior is
authorized by the exit label itself.

### S1 closure: player attribute return

`ExPlyrAt` is **ROM-match complete**, one expected and one actual new
match. The count advances **1,709 → 1,710 / 1,992**. The original
GameEngine reached `$f129` in all eight bounded attribute variants
retained from T46 S4, including paths that changed OAM and the
no-change branch. The RTS reads or writes no game RAM/OAM. The shared
C attribute function returns at the same point; all **16** x86/x64
child comparisons match the complete non-stack 2 KB RAM/OAM image.
The machine-checked source PC and native comparisons are in ignored
`build/m2-t47-s1/rom-logic-result.json`; raw owner-ROM call records
remain ignored under `build/m2-t46-s4/`.

The separate operational track rebuilt x86/x64 and DOS16; all six
focused player OAM, sprite OAM and platform-purity CTests passed;
both Win32 self-tests exited successfully; DOS16 produced a valid
261,775-byte MZ image. The three owner-authorized EXEs were refreshed
in `assets/`. Since this S corrects evidence for an existing RTS and
does not change production C, their SHA-256 values remain:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `34d5d07f88bad46f8624cd03cced42b597dc66901587cdf176844d8898f35a14` |
| `assets/mysmb32.exe` | `2e02ad6d5fe905894f1fd06ee93680049b3eec4becb3ed0df332be36fa1ab0b8` |
| `assets/mysmb64.exe` | `a971e80a4d01085dec7ab298a3ab0e8bb27ca430eb7e059b64ef02c91a7564fe` |

The similar-issue sweep checked every `ChkForPlayerAttrib` return
successor in the original listing and its single shared-C owner.
No other exit node is claimed by this S. S2 begins at
`RelativePlayerPosition` and is now admitted below.

## S2 admission: shared relative object coordinates

The next contiguous chain begins at `RelativePlayerPosition` (14786)
and ends at `GetObjRelativePosition` (14834). Its exact nine labels
are the S2 row in the task table. `RelativePlayerPosition` is
**audited; mismatch**, `RelativeFireballPosition` is **audited;
evidence incomplete**, and the other seven are **open**. All nine are
intended new ROM matches: **1,710 → 1,719 / 1,992** maximum. M2 T16
S4 transfers their custody to T47 S2. The source predecessor is S1
`ExPlyrAt`; the successor is S3 `GetPlayerOffscreenBits`, which is not
credited here. The shared owner is `src/game/oam/object_position.c`.
The existing bubble relative-position body in `fireball/bubble.c`
must be moved to this owner, with callers using its public OAM entry;
the C split must not duplicate the source's common offset/coordinate
logic.

The original GameEngine actor-position route covers player, enemy,
fireball, bubble, block and misc variants at naturally reached entries.
The nine labels share `GetObjRelativePosition` and the source
`ObjectOffset`/`$00` scratch contract. For each variant compare branch
and call order, indexed source coordinates, `SprObject_Rel_XPos/YPos`
writes, `$00` and restored X/ObjectOffset behavior against native C on
x86/x64. The platform-independent operational track then builds all
three targets, runs focused relative-position/actor regression tests,
purity, and refreshes the three EXEs. Original CPU PC/stack/ROM are
never altered; bounded RAM variants are allowed only at naturally
reached entries.

### S2 closure: shared relative object coordinates

All **nine expected labels are ROM-match complete**; there are no S2
deferrals. The count advances **1,710 → 1,719 / 1,992**. The original
GameEngine naturally reached all nine source PCs on player, bubble,
fireball, misc, enemy and block routes. Each route was captured in its
ordinary state and in a bounded RAM edge variant. The recorder changed
neither ROM nor CPU PC/stack. Across **12 routes and 30 original child
calls**, x86 and x64 each matched every non-stack RAM/OAM byte after
the child: **60 comparisons, zero differences**. Return X matched
`ObjectOffset` in every record. Raw records and the machine-checked
PC/write summary remain under ignored `build/m2-t47-s2/`.

| Source PC | Label and original control/read/write contract | C owner |
| --- | --- | --- |
| `$f12a` | `RelativePlayerPosition`: X=Y=0, fall into `RelWOfs`; no `$0755` write | `mysmb_oam_relative_player_position` |
| `$f131` | `RelativeBubblePosition`: bubble slot through source offset table; fixed relative result 3 | `mysmb_oam_relative_bubble_position` |
| `$f13b` | `RelativeFireballPosition`: fireball slot through source offset table; fixed result 2 | `mysmb_oam_relative_fireball_position` |
| `$f142` | `RelWOfs`: save source slot to `ObjectOffset`, call common position routine, restore X | shared relative wrappers; original return-X check |
| `$f148` | `RelativeMiscPosition`: misc slot through source offset table; fixed result 6 | `mysmb_oam_relative_misc_position` |
| `$f152` | `RelativeEnemyPosition`: source displacement 1, result 1; preserve incoming slot in `$00` | `mysmb_oam_relative_enemy_position` |
| `$f159` | `RelativeBlockPosition`: two calls with displacement 9, results 4 and 5, slots X and X+2; final `$00` is X+2 | `mysmb_oam_relative_block_position` |
| `$f165` | `VariableObjOfsRelPos`: write incoming X to `$00`, add displacement and call common routine | `mysmb_oam_variable_obj_relative_position` |
| `$f171` | `GetObjRelativePosition`: indexed `SprObject_Y_Position` to relative Y; indexed X minus `ScreenLeft_X_Pos` to relative X, with eight-bit wrap | `mysmb_oam_get_obj_relative_position` |

The owner ROM's three `ObjOffsetData` bytes were checked directly
against the `SprObject` RAM-array displacements used by the C helper.
This is the fixed owner-ROM specialization of the caller edge; the
`ObjOffsetData` and `GetProperObjOffset` labels themselves remain
uncredited and assigned to S4. The defect sweep covered all six actor
callers. It removed the duplicate bubble calculation, the spurious
player `$0755` write, and the missing enemy/block `$00` writes.
The edge routes check coordinate wrap, source indexing, and scratch
preservation; no platform adapter gained game logic.

The separate operational track rebuilt Win32 x86, x64 and DOS16.
Focused player route, block lifetime, four actor OAM and platform-purity
tests passed **7/7 on each Windows architecture**. Both packaged
Win32 `--self-test` runs exited zero. The DOS16 linker produced a valid
262,191-byte MZ executable. The broader pre-refactor suite was
**222/233 on both x86 and x64**; its same 11 known T46 S4 baseline
failures are unchanged, and no new failures appeared. The final
helper-only refactor was checked by the focused tests and all 60 ROM
comparisons above.

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `b5b9ad5127acfb5bfed06694e8f9785123c65c6ab47b5a07c64822a6eee263c0` |
| `assets/mysmb32.exe` | `4b5f76acec61ae49427dd31dc43b68465ab4bec39ec5d616694bbe7fd5c8b173` |
| `assets/mysmb64.exe` | `fc91bd0c1813c78e664f121c73a3d68091e72f012641b8830bcf65b5d1365035` |

S3 `GetPlayerOffscreenBits` is next in source order and remains
unadmitted at this closure.

## S3 admission: player offscreen entry

The exact source-order scope is **one incomplete label**,
`GetPlayerOffscreenBits` (line 14846, `$f180`, incoming **audited;
evidence incomplete**); the intended ROM-match set is the same one
label. The baseline is **1,719 / 1,992**, maximum **1,720 / 1,992**.
M2 T16 S4 transfers this label to T47 S3. Predecessor is S2
`GetObjRelativePosition`; the next source label, S4
`GetFireballOffscreenBits`, and the shared `GetOffScreenBitsSet` child
remain uncredited here. The shared owner is
`src/game/oam/player_gfx.c`; the host platform must remain free of game
logic.

The original entry loads X=0 and Y=0, then jumps into the shared
offscreen-bit chain. On a naturally reached GameEngine player route,
record the entry PC, register setup and successor PC, plus the returned
offscreen byte and RAM/OAM state. Compare the corresponding shared-C
player entry on x86 and x64, and separate wrapper correctness from
outgoing S4 helper obligations. The operational track runs player OAM
and platform-purity tests, builds all three targets and refreshes the
three EXEs. Only a source-reachable route and exact argument/dataflow
proof can close this label; S4 child nodes keep their own future tests.

### S3 closure: player offscreen entry

`GetPlayerOffscreenBits` is **ROM-match complete**, one expected and one
actual new match; **1,719 → 1,720 / 1,992**. The owner ROM bytes at
`$f180` are `A2 00 A0 00 4C C0 F1`: X=0, Y=0, jump to
`GetOffScreenBitsSet` at `$f1c0`. The natural GameEngine and bounded
player-coordinate edge routes each hit `$f180`, `$f182`, `$f184` and
`$f1c0` 11 times. Sixteen naturally entered child calls were captured
at their stack-derived returns. Every one reached `$f1c0` with X=Y=0,
restored X from `ObjectOffset`, and returned the player offscreen byte
at `$03d0`. The corresponding shared-C entry matched that result and
every non-stack RAM/OAM byte outside the downstream helper's scratch
set on x86 and x64: **32 comparisons, zero entry/result differences**.
The machine-checked summary and raw owner-ROM records remain under
ignored `build/m2-t47-s3/`.

The original child `GetOffScreenBitsSet` still differs from C in its
`$00`, `$04–$07` scratch effects: 34 byte comparisons on the natural
route and 37 on the edge route per native width. These exact gaps are
**not waived** and do not count as S3 success for any S4 node. They
remain assigned to S4's common offscreen-helper chain. The S3 wrapper
itself has no branch or scratch write outside setting the two zero
register arguments and tail-calling that child. The similar-issue sweep
checked the player GameEngine caller and the shared helper handoff;
no production or platform source change was needed.

Operational verification rebuilt Win32 x86, x64 and DOS16; focused
player route, player OAM and platform-purity tests passed **3/3 on each
Windows architecture**. Both packaged Windows `--self-test` runs exited
zero. DOS16 linked a valid MZ image. The three owner-authorized EXEs
were refreshed and are byte-identical to S2 because production code
did not change:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `b5b9ad5127acfb5bfed06694e8f9785123c65c6ab47b5a07c64822a6eee263c0` |
| `assets/mysmb32.exe` | `4b5f76acec61ae49427dd31dc43b68465ab4bec39ec5d616694bbe7fd5c8b173` |
| `assets/mysmb64.exe` | `fc91bd0c1813c78e664f121c73a3d68091e72f012641b8830bcf65b5d1365035` |

S4 begins at `GetFireballOffscreenBits` and remains unadmitted here.

## S4 admission: shared offscreen-bit chain

The exact **26 incomplete source-order labels** are the S4 row in the
task table, from `GetFireballOffscreenBits` (14851) through `ExDivPD`
(15016). All 26 are intended new ROM matches; **1,720 → 1,746 /
1,992** maximum. `GetFireballOffscreenBits` is incoming **audited;
evidence incomplete**; the other 25 are **open**. M2 T16 S4 transfers
their custody to T47 S4. S3 `GetPlayerOffscreenBits` is the caller-side
predecessor; S5 `DrawSpriteObject` is the next source label and remains
uncredited. The shared game owner is `src/game/oam/object_position.c`;
actor callers may delegate to it, while host adapters do no offscreen
calculation.

The original `GetOffScreenBitsSet` combines horizontal and vertical
nibbles after `RunOffscrBitsSubs`, restoring X from `ObjectOffset`.
The X/Y loops and `DividePDiff` preserve `$00`, `$04–$07` scratch
effects, table indices and eight-bit arithmetic. Prove the fixed PRG
tables against the owner ROM, then compare each entry variant
(player, fireball, bubble, misc, enemy, block) on source-reachable
GameEngine routes, including edge inputs at natural entries. Each
of the 26 labels requires a source PC or data-consumer proof and
individual control/read/write disposition. The S3 player scratch
discrepancy is an explicit S4 regression input. The independent
operational track runs relevant actor OAM tests, x86/x64 builds,
DOS16 link, platform purity and all three executable artifacts.

### S4 closure: shared offscreen-bit chain

All **26 expected labels are ROM-match complete**, with no S4 deferral;
the count advances **1,720 → 1,746 / 1,992**. The original GameEngine
reached player, fireball, bubble, misc, enemy and block offscreen
entrances in natural and bounded edge variants. Across **12 routes and
32 original child calls**, the shared C chain matched every non-stack
RAM/OAM byte after each call on x86 and x64: **64 comparisons, zero
differences**. This includes the S3 discrepancy in `$00`, `$04–$07`:
the player route now also matches those scratch bytes. Return X equals
`ObjectOffset` in all captured calls. The original CPU PC/stack/ROM was
never redirected or modified; only selected actor RAM was varied at
naturally reached entries. Raw records and machine-checked node/route
summaries stay in ignored `build/m2-t47-s4/`.

| Source PC | Node | Control/data evidence and shared C mapping |
| --- | --- | --- |
| `$f187` | `GetFireballOffscreenBits` | 3 PC hits; table-adjusted source slot, destination 2; `mysmb_oam_get_fireball_offscreen_bits` |
| `$f191` | `GetBubbleOffscreenBits` | 6 hits; table-adjusted source slot, destination 3; bubble delegates to `mysmb_oam_get_bubble_offscreen_bits` |
| `$f19b` | `GetMiscOffscreenBits` | 2 hits; table-adjusted source slot, destination 6; `mysmb_oam_get_misc_offscreen_bits` |
| `$f1a5` | `ObjOffsetData` | ROM bytes `07 16 0d` bound to `mysmb_obj_offset_data`, exercised by the three preceding actor wrappers |
| `$f1a8` | `GetProperObjOffset` | 22 hits; slot + selected table byte; `mysmb_oam_proper_source_offset` |
| `$f1af` | `GetEnemyOffscreenBits` | 4 hits; source displacement 1, destination 1; `mysmb_oam_get_enemy_offscreen_bits` |
| `$f1b6` | `GetBlockOffscreenBits` | 4 hits; source displacement 9, destination 4; `mysmb_oam_get_block_offscreen_bits` |
| `$f1ba` | `SetOffscrBitsOffset` | 8 hits; write incoming slot to `$00`, add displacement; `mysmb_oam_set_offscreen_bits_offset` |
| `$f1c0` | `GetOffScreenBitsSet` | 59 hits; combine horizontal low and vertical high nibbles, write fixed result and `$00`; `mysmb_oam_get_offscreen_bits_set` |
| `$f1d7` | `RunOffscrBitsSubs` | 59 hits; X high nibble to `$00`, then Y helper; `mysmb_oam_run_offscreen_bits_subs` |
| `$f1e3` | `XOffscreenBitsData` | 16 original ROM bytes bound to `mysmb_x_offscreen_bits_data` and consumed by both X loop edges |
| `$f1f3` | `DefaultXOnscreenOfs` | ROM bytes `07 0f 07` bound to `mysmb_default_x_onscreen_ofs` |
| `$f1f6` | `GetXOffscreenBits` | 68 hits; source X to `$04`, right-edge-first scan; `mysmb_oam_get_x_offscreen_bits` |
| `$f1fa` | `XOfsLoop` | 127 hits; edge/page subtraction writes `$07`, signed/page branches; X helper loop |
| `$f21e` | `XLdBData` | 127 hits; indexed X table read and source X restoration; X helper load |
| `$f22a` | `ExXOfsBS` | 68 hits; nonzero result or exhausted left edge returns; X helper exit |
| `$f22b` | `YOffscreenBitsData` | 9 original ROM bytes bound to `mysmb_y_offscreen_bits_data` and consumed by Y loop |
| `$f234` | `DefaultYOnscreenOfs` | ROM bytes `04 00 04` bound to `mysmb_default_y_onscreen_ofs` |
| `$f237` | `HighPosUnitData` | ROM bytes `ff 00` bound to `mysmb_high_pos_unit_data` |
| `$f239` | `GetYOffscreenBits` | 59 hits; source X to `$04`, top-edge-first scan; `mysmb_oam_get_y_offscreen_bits` |
| `$f23d` | `YOfsLoop` | 107 hits; vertical high/low subtraction writes `$07`; Y helper loop |
| `$f260` | `YLdBData` | 107 hits; indexed Y table read and source X restoration; Y helper load |
| `$f26c` | `ExYOfsBS` | 59 hits; nonzero result or exhausted bottom edge returns; Y helper exit |
| `$f26d` | `DividePDiff` | 138 hits; always write adder to `$05`, compare `$07` with `$06`, divide near edge; `mysmb_oam_divide_pixel_diff` |
| `$f280` | `SetOscrO` | 44 hits; select divided offset, add side-specific adder for left/bottom; divide helper branch |
| `$f281` | `ExDivPD` | 138 hits; preserve default offset on far side; divide helper return |

The shared game chain now has one source-order table/loop/scratch owner.
The duplicate player and bubble calculations were removed; all six
actor callers use the same nibble-packing routine. The similar-issue
sweep also checked the explicit X helper used by player scrolling and
small-platform graphics. Those callers remain in game code; no host
adapter contains offscreen logic.

The separate operational track built Win32 x86, x64 and DOS16. Focused
player scroll, five actor OAM, small-platform OAM and platform-purity
tests passed **8/8 on each Windows architecture**. Both packaged
Win32 `--self-test` runs exited zero; DOS16 linked a valid
260,245-byte MZ image. Full CTest was **222/233 on both x86 and x64**,
with precisely the same 11 previously recorded baseline failures and
no new failures. The owner-authorized three EXEs were refreshed:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `43b96d62449e5f677df4736e3e10621c6d1c6e46ee3cd344f3c500619bf33e3a` |
| `assets/mysmb32.exe` | `abd2b7b6a17e74b968f76319a752ec53f4806029544ec1a9ed68f703fa174f5a` |
| `assets/mysmb64.exe` | `31caa48109875babd74ab1ea575f6818a30db3d7954c43c8395a776d423a5909` |

S5 begins at `DrawSpriteObject` and remains unadmitted here.

## S5 admission: two-sprite row writer

The final T47 source-order chain owns exactly three **open** labels:
`DrawSpriteObject` (15025), `NoHFlip` (15036), and `SetHFAt`
(15040). All three are intended ROM matches, **1,746 → 1,749 /
1,992** maximum. M2 T16 S4 transfers them to T47 S5. S4
`ExDivPD` is the predecessor; `SoundEngine` is the next source
label and belongs to a later T. The shared game OAM owner will expose
one `DrawSpriteObject`-equivalent row writer; existing player/block
and other row callers must use or be checked against that owner.

Capture source-reachable `$f282` calls with CPU X/Y, complete RAM/OAM
before and after the stack-derived return. Compare horizontal flip
and no-flip successors at `$f296`/`$f2a0`, tile order, attributes,
coordinates, `$02` increment, and X/Y return increments against the
shared C routine on x86/x64. Test both branch families, including
an edge-coordinate/attribute RAM variant at a natural entry. The
independent operational track builds DOS16, Win32 x86/x64, checks
focused OAM and platform-purity tests, and refreshes all three EXEs.
T47 closure then combines its five S results in a cross-chain route
matrix and integrated three-target regression.

### S5 closure: shared sprite-row writer

All three expected labels are **ROM-match complete**, with no S5
deferral: **1,746 → 1,749 / 1,992**. Original GameEngine routes
entered `$f282` through player, ordinary enemy and bouncing-block
callers. Natural and bounded flip/coordinate variants supplied 38
stack-returned child calls. On both x86 and x64 the shared C writer
matched return X/Y and every non-stack RAM/OAM byte after each call:
**76 comparisons, zero differences**. The source PC coverage reaches
both the `$f296` no-flip branch and `$f2a0` common attribute/writer
tail. The recorder did not alter ROM, CPU PC or the call stack; raw
records were deleted after the diagnostic comparison. The neutral
proof summary stays under ignored `build/m2-t47-s5/`.

| Source PC | Label | Control, read/write and native mapping |
| --- | --- | --- |
| `$f282` | `DrawSpriteObject` | Read `$03` bit 1 for tile order, `$00/$01` tile pair; write OAM row and `$02`; return X+2, Y+8. Shared `mysmb_oam_draw_sprite_object`. |
| `$f296` | `NoHFlip` | Write `$00` left and `$01` right, clear additional flip attribute; verified by natural player, enemy and block routes. |
| `$f2a0` | `SetHFAt` | OR selected flip bit with `$04`, write both OAM attributes, Y=`$02`, X=`$05` and X+8, then advance `$02`, X and Y; verified on both flip branches. |

The similar-issue sweep found earlier inlined copies at the original
`DrawOneSpriteRow` callers: player, block, power-up and flagpole score.
It also found the ordinary enemy `DrawEnemyObjRow` copy, whose flip
tile order differed from the source. All now call the shared writer;
the flagpole setup also writes `$05` on its no-score branch, as the
original does. The separate unused Koopa/Buzzy drawing function and
other actor-specific OAM arrangements do not call this original row
entry, so this S leaves their distinct source owners in place. Host
adapters are unchanged.

The independent operational track rebuilt the full x86 and x64 target
sets and linked a 258,517-byte DOS16 MZ executable. Player, block,
power-up, ordinary-enemy and flagpole OAM tests plus platform purity
passed on both Windows widths. Both Win32 `--self-test` runs passed.
Full CTest was **222/233 on each width**, with precisely the same 11
previously recorded baseline failures and no new failure. The three
owner-authorized executable artifacts were refreshed:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `a71c286349d91fb74496e4a75ef2b1a20fd693787b6cb730130d0a333270f930` |
| `assets/mysmb32.exe` | `c67a9ff1b597285a68da61e4668e21b16b19b5121feed9630ef5829d969ee72b` |
| `assets/mysmb64.exe` | `00403e4c7b79b8e21ccb2f6667fea296b1f7ca79432be72015737b0c06d2ce96` |

T47's cross-chain proof matrix is recorded in the
[task closure](../../history/M2-T47-object-position-and-sprite-output.md#t47-closure).
