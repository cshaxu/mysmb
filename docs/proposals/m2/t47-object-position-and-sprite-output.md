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
