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
`RelativePlayerPosition` and remains unadmitted.
