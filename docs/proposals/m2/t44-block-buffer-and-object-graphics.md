# M2 T44: block buffer and object graphics

## Task contract

T44 owns the 109 inventory labels from `BlockBufferChk_Enemy` at source line
13023 through `EggExc` at line 13994. All are open except the retained
`CheckForBulletBillCV` and `SBBAt` pair. The task follows source order and
contains shared game logic only; platform adapters receive no collision,
object-state or sprite-selection policy.

| S | Source chain | Scope | Expected new |
| --- | --- | ---: | ---: |
| S1 | Block-buffer probe and coordinate core | 14 | 14 |
| S2 | Vine object graphics | 6 | 6 |
| S3 | Six-sprite and hammer graphics | 14 | 14 |
| S4 | Flagpole graphics and sprite dumps | 9 | 9 |
| S5 | Large-platform graphics | 11 | 11 |
| S6 | Floatey-number and jumping-coin graphics | 5 | 5 |
| S7 | Power-up graphics | 6 | 6 |
| S8 | Enemy graphics and animation | 44 | 42 |
| **Total** | **13023-13994** | **109** | **107** |

All incoming open labels currently retain M2 T17 S6 custody until their
source-order S accepts an exact transfer. The two retained labels remain
rechecked at their S7 boundary and do not receive duplicate credit.

## Planned source-order chains

### S1: Block-buffer probe and coordinate core

Entry `BlockBufferChk_Enemy`; exit `RetYC`; shared owner
`src/game/world/block_buffer.c`. Predecessor: T43 shared box collision.
Successors: enemy/fireball and player terrain callers plus S2 vine rendering.
Scope: `BlockBufferChk_Enemy`, `ResidualMiscObjectCode`, `BlockBufferChk_FBall`,
`ResJmpM`, `BBChk_E`, `BlockBufferAdderData`, `BlockBuffer_X_Adder`,
`BlockBuffer_Y_Adder`, `BlockBufferColli_Feet`, `BlockBufferColli_Head`,
`BlockBufferColli_Side`, `BlockBufferCollision`, `RetXC`, `RetYC`.

The ROM-logic track compares selector-specific entry state, table binding,
X/Y/page carry, block-buffer address, metatile result and terminal returns from
source-reachable enemy, fireball and player callers. The operational track runs
a focused chain test, affected callers, strict C90 x86/x64 builds, DOS16 link,
platform-purity audit and three refreshed EXEs. Admission baseline is
1,517/1,992; this exact scope expects 14 new matches and a maximum 1,531.

#### S1 implementation checkpoint

The shared owner now has distinct enemy, miscellaneous-object and fireball
entries, with the original 28-byte X/Y tables, source scratch `$02-$07`, page
carry and vertical/horizontal return selection in one implementation. The
former duplicated coordinate algorithms and their invented range rejection
were removed from `collision.c`. `ResidualMiscObjectCode` addresses the
original misc portion of the common sprite arrays (`$7a/$93/$db`) through
X+13, rather than treating it as an enemy slot.

Operational checks pass on both Windows widths: block-buffer core, address,
enemy-query and fireball tests, followed by each product self-test. The full
shared source set compiles under strict C90 for x86 and x64; the same sources
link to the OpenNT DOS16 MZ program. Checkpoint artifacts are `mysmb16.exe`
258117 bytes SHA-256 `e7fe9194ff667ff47631539b2e6cf021ea5197f26e60523a10d80f09f08d33a0`,
`mysmb32.exe` 364373 bytes SHA-256
`3b981815e3ff0c70488fe0cfbd0999d4af37833211798a93c09d00c8b8d321f1`, and
`mysmb64.exe` 372536 bytes SHA-256
`9fa393d68c084d00109037ce64fb7e58cd91372dd8649aa1978d52611980e88e`.

This checkpoint awards no node credit. The remaining ROM-logic track must
observe original selector entries and return state before S1 can close.

#### S1 closure: block-buffer probe and coordinate core

S1 closes all fourteen received labels, moving the M2 count from **1,517** to
**1,531 / 1,992**. The shared owner is
`src/game/world/block_buffer.c`; no platform adapter contains selector,
collision, object-coordinate or return-path policy.

| ROM labels | Exact C/ROM disposition |
| --- | --- |
| `BlockBufferChk_Enemy`, `BBChk_E` | Enemy entry changes the slot to `X + 1`, invokes the common core, restores the object slot and returns the metatile comparison result. Original execution reaches `$e388`, `$e3a5`, `$e3f0`, `$e429` and `$e42b` through `ChkUnderEnemy`/side-check routes. |
| `ResidualMiscObjectCode`, `ResJmpM` | Misc entry uses `X + $0d`, `Y = $1b` and A=0 for the vertical return. The complete local control graph has no inbound source edge to this residual entry; it is therefore verified by its exact static sequence and bound-data focused test, without inventing a CPU route. |
| `BlockBufferChk_FBall` | Fireball entry uses its distinct common-sprite arrays, `X + 7`, `Y = $1a` and the vertical return. Original `FireballBGCollision` reaches `$e39c`, `$e3a3`, `$e3a5`, `$e3f0` and `$e42b`. |
| `BlockBufferAdderData`, `BlockBuffer_X_Adder`, `BlockBuffer_Y_Adder` | The production path binds the original PRG bytes at `$e3ad`, `$e3b0` and `$e3cc`; the resource-free fallback has the exact 3+28+28 byte tables. The local-ROM test compares every byte before exercising recorded probes. |
| `BlockBufferColli_Feet`, `BlockBufferColli_Head`, `BlockBufferColli_Side` | Feet increments Y; head selects A=0; side selects A=1 and X=0. Original player records reach `$e3e8`, `$e3e9`, `$e3f0` and `$e42b`; the native checker compares row, metatile, contact nibble and scratch `$02-$07`. |
| `BlockBufferCollision`, `RetXC`, `RetYC` | The common core preserves selector state in `$04`, carries X into the page/column calculation, reads the block buffer, and returns X or Y low nibble exactly as selected. |

The ROM-logic evidence is produced by ordinary one-frame NMI execution of the
local original ROM with RAM-only fixtures, preserving the ROM CPU, stack and
program counter. Records under `build/m2-t44-s1/` cover player terrain,
enemy background and fireball background entries. The x64 and x86 native
`mysmb_block_buffer_player_actual_check` replay matches all recorded player
child state; the focused enemy and fireball checks match their recorded
states. Strict C90 x86/x64 product builds, the OpenNT DOS16 link and
`test_platform_purity.py` pass.

The three required MZ products were freshly built as DOS16, Win32 x86 and
Win32 x64. The committed asset package remains `assets/mysmb16.exe` (258117
bytes, `e7fe9194ff667ff47631539b2e6cf021ea5197f26e60523a10d80f09f08d33a0`),
`assets/mysmb32.exe` (364373 bytes,
`3b981815e3ff0c70488fe0cfbd0999d4af37833211798a93c09d00c8b8d321f1`) and
`assets/mysmb64.exe` (372536 bytes,
`9fa393d68c084d00109037ce64fb7e58cd91372dd8649aa1978d52611980e88e`). No
S1 node is deferred.

### S2: Vine object graphics

Entry `VineYPosAdder`; exit `NextVSp`; shared owner
`src/game/oam/vine_gfx.c`. Predecessor: S1 block-buffer core. Successors: S3
shared six-sprite graphics and the existing vine object handler. Scope:
`VineYPosAdder`, `DrawVine`, `VineTL`, `SkpVTop`, `ChkFTop`, `NextVSp`.

All six incoming labels are open and expected to become matches. The ROM-logic
route is the original `VDrawLoop` caller through both vine offsets: it verifies
the `$00/$02` scratch, relative Y plus the two-entry table, vine object/OAM
offset selection, six tile writes, top-tile branch and 100-pixel clip. The
operational route is a focused vine-OAM trace/replay, strict C90 x86/x64
builds, DOS16 link, platform-purity audit and all three target artifacts.
Admission baseline is 1,531/1,992, with a maximum 1,537/1,992.

#### S2 implementation checkpoint

`vine_gfx.c` now consumes the fixed `Enemy_Rel_XPos`/`Enemy_Rel_YPos` scratch
written by the ROM caller rather than recomputing world coordinates. It also
uses the original wrapped eight-bit `VineStart_Y_Position - Sprite_Y_Position`
comparison for `ChkFTop`; the prior extra ordering condition was removed.
The focused vine OAM smoke check passes, and 42 original vine-actor snapshots
match in both x64 and x86. This is a checkpoint only: S2 still needs the
individual node evidence, three-target package and closure accounting.

#### S2 closure: vine object graphics

S2 closes all six received labels, moving M2 from **1,531** to
**1,537 / 1,992**. The shared owner remains
`src/game/oam/vine_gfx.c`; no Windows or DOS adapter selects a tile, OAM slot,
clip result, or object state.

| ROM label | Exact translated behavior and evidence |
| --- | --- |
| `VineYPosAdder` | The bound two-byte table is `{ $00, $30 }`; both offsets are asserted by the focused OAM check. |
| `DrawVine` | Consumes caller-written `Enemy_Rel_XPos` and `Enemy_Rel_YPos`, selects `VineObjOffset` and `Enemy_SprDataOffset`, and emits the same six four-byte OAM entries. |
| `VineTL` | Writes six `$e1` body tiles at four-byte OAM strides. |
| `SkpVTop` | Replaces only offset-zero row zero with cap tile `$e0`; the offset-one route retains `$e1`. |
| `ChkFTop` | Performs the source unsigned eight-bit subtraction and `$64` comparison, replacing clipped Y values with `$f8`; no invented coordinate-order condition remains. |
| `NextVSp` | Advances four OAM bytes per iteration, completes six rows, then restores the caller's vine-offset Y value. |

The ROM-logic track uses 42 local original-ROM `VDrawLoop` actor records. Their
source PC aggregate reaches `DrawVine` 50 times, `VineTL` 300 times,
`SkpVTop` 50 times, `ChkFTop` 300 times, and `NextVSp` 300 times; the C actor
snapshot replay has zero mismatches on both x64 and x86. The focused native
OAM check covers both Y-table offsets, cap/body selection, horizontal
alternation, attributes and wrapped clipping. The operational track passes
strict C90 x86/x64 product builds and self-tests, the OpenNT DOS16 link,
platform-purity audit, and the refreshed three-executable package recorded in
the artifact manifest: `mysmb16.exe` 258021 bytes
`7d86df167a3303d23feb54740c634c9cdf5a5606b7282e2d8dc96658749d9911`,
`mysmb32.exe` 364373 bytes
`35f1810372eed6c65029b8c588691b2832e2941fa570201d7f9643db834c7618`, and
`mysmb64.exe` 372536 bytes
`c807a969d546246b3e427ad70300a5cd54ce26d89228874999fba04e11c8bc9e`.
No S2 label is deferred.

### S3: Six-sprite and hammer graphics

Entry `SixSpriteStacker`; exit `NoHOffscr`; shared owner
`src/game/oam/hammer_gfx.c` plus the reusable OAM stacker seam. Predecessor:
S2 vine graphics. Successors: S4 dump helpers and all hammer callers. Scope:
`SixSpriteStacker`, `StkLp`, `FirstSprXPos`, `FirstSprYPos`,
`SecondSprXPos`, `SecondSprYPos`, `FirstSprTilenum`, `SecondSprTilenum`,
`HammerSprAttrib`, `DrawHammer`, `ForceHPose`, `GetHPose`, `RenderH`,
`NoHOffscr`.

All fourteen incoming labels are open and expected to become matches. The
ROM-logic route is original `ProcHammerObj` through `DrawHammer`, using
timer-control and state/pose variants; `VDrawLoop` supplies the independent
six-sprite stacker consumer. It compares the eight source table bytes, pose
branch, cumulative coordinates, tile/attribute writes, offscreen state clear
and two-sprite dump. The operational track runs the hammer-graphics snapshot
check plus focused vine and stacker tests, strict C90 x86/x64 builds, DOS16
link, platform-purity audit and three fresh
target artifacts. Admission baseline is 1,537/1,992; scope and expected set
are both 14 labels, with maximum 1,551/1,992.

#### S3 closure: six-sprite and hammer graphics

S3 closes all fourteen received labels, moving M2 from **1,537** to
**1,551 / 1,992**. Shared OAM code owns the translated writes; Windows and
DOS only consume the resulting OAM store.

| ROM labels | Exact C/ROM disposition |
| --- | --- |
| `SixSpriteStacker`, `StkLp` | `mysmb_oam_stack_six_sprite_data` performs exactly six `Sprite_Data,Y` stores, adds `$08` after each store, and advances one four-byte OAM record. `DrawVine` now invokes it before its own cap/clip work. |
| `FirstSprXPos`, `FirstSprYPos`, `SecondSprXPos`, `SecondSprYPos` | The four original pose entries are bound in source order and the second X/Y positions use the ROM's cumulative addition from the first coordinate. |
| `FirstSprTilenum`, `SecondSprTilenum`, `HammerSprAttrib` | The exact `$80/$82/$81/$83`, `$81/$83/$80/$82`, and `$03/$03/$c3/$c3` tables drive both hammer OAM rows. |
| `DrawHammer`, `ForceHPose`, `GetHPose`, `RenderH`, `NoHOffscr` | Timer control or non-one state forces pose zero; otherwise `FrameCounter >> 2 & 3` selects the pose. Rendering writes two OAM rows, reloads `ObjectOffset` before the `$fc` offscreen test, clears that source-selected misc state and emits the `$f8` dump only when required. |

The ROM-logic track aggregates original records that execute `DrawHammer` 54
times, all pose-branch paths and the offscreen path. A graphics-specific
replay of all 63 original hammer records passes at zero differences on both
x64 and x86; it deliberately masks only `$04d0-$04f2`, the separately owned
`GetMiscBoundBox` dependency, whose 18 known records remain outside this
chain. The hammer-graphics snapshot check compares all 63 records after
excluding only the declared bounding-box dependency; focused vine and stacker
tests exercise the shared six-sprite consumer, including 8-bit OAM-offset
wraparound. The refreshed package is `mysmb16.exe` 258165
bytes `074723d5a169c7a9fe535b7b8867ff6f8fa8192cba3272d5a1062d5b37aacb22`,
`mysmb32.exe` 364658 bytes
`a6a99292d8963842a63b70a156a5d846d504123c6535b21889dc570bf88860c7`, and
`mysmb64.exe` 372856 bytes
`b36762adb84e00c100416441b49465a080e81533035f2a7e0948159bf60f479a`.
No S3 label is deferred.

### S4: Flagpole graphics and sprite dumps

Entry `FlagpoleScoreNumTiles`; exit `ExitDumpSpr`; shared owners
`src/game/oam/flagpole_gfx.c` and the shared OAM helper seam. Predecessor: S3
OAM stacker. Successors: S5 platform/floatey graphics, fire attempts, death
and enemy graphics callers. Scope: `FlagpoleScoreNumTiles`,
`FlagpoleGfxHandler`, `ChkFlagOffscreen`, `MoveSixSpritesOffscreen`,
`DumpSixSpr`, `DumpFourSpr`, `DumpThreeSpr`, `DumpTwoSpr`, `ExitDumpSpr`.

All nine incoming labels are open and expected to become matches. The
ROM-logic route is `FlagpoleRoutine`/`FPGfx` through the flagpole handler,
covering its fixed flag OAM rows, optional score row, `$0e` offscreen mask and
the dump-helper fall-throughs. Additional original fire-attempt and death
routes cover helper counts that flagpole does not enter. The operational track
runs focused flagpole/OAM checks, x86/x64 C90 builds, DOS16 link,
platform-purity audit and three refreshed target artifacts. Admission baseline
is 1,551/1,992; this nine-node scope expects nine new matches and a maximum
of 1,560/1,992.

#### S4 closure: flagpole graphics and sprite dumps

S4 closes all nine received labels, moving M2 from **1,551** to **1,560 /
1,992**. `src/game/oam/flagpole_gfx.c` owns the complete source-order
flagpole graphics chain; `src/game/oam/sprite_dump.c` owns the generic OAM
dump fall-through. Neither Win32 nor DOS code selects tiles, score rows,
offscreen masks, or sprite counts.

| ROM labels | Exact translated behavior and evidence |
| --- | --- |
| `FlagpoleScoreNumTiles` | The bound table is the exact five source pairs: `$f9/$50`, `$f7/$50`, `$fa/$fb`, `$f8/$fb`, `$f6/$fb`. |
| `FlagpoleGfxHandler` | Reloads `ObjectOffset` and `Enemy_SprDataOffset`, draws the three fixed flag rows, initializes `$02/$03/$04` before the collision gate, and invokes the existing child-row seam only for the score pair. |
| `ChkFlagOffscreen` | Reloads the source slot and applies exactly `Enemy_OffscreenBits & $0e`; any set bit dispatches the six-row dump. |
| `MoveSixSpritesOffscreen`, `DumpSixSpr`, `DumpFourSpr`, `DumpThreeSpr`, `DumpTwoSpr`, `ExitDumpSpr` | The shared helpers preserve the original fall-through stores at `+20`, `+16`, `+12`, `+8`, `+4`, and `+0`; `MoveSixSpritesOffscreen` supplies `$f8`. |

The original flagpole source-PC aggregate reaches every handler instruction
from `$e54b` through `$e5c7`, including all five dump helper entries. The
focused `mysmb_flagpole_gfx_smoke` checks each score pair, the no-score scratch
initialization, three flag OAM rows, the `$0e` mask, and the six-row dump;
`mysmb_sprite_dump_smoke` independently checks every fall-through endpoint.
Both checks, plus `mysmb_flagpole_oam_smoke`, pass in x86 and x64. Strict C90
product builds pass for both Windows widths; the shared sources link to the
OpenNT DOS16 MZ program. `test_platform_purity.py` remains the architecture
guard for the shared game/platform boundary.

The refreshed required package is `mysmb16.exe` 258661 bytes
`670fe2c1bd4b98032a11cd940aec299ebf75384e6766e7c3a7a44aa84cb1b00e`,
`mysmb32.exe` 365793 bytes
`35246454709cebcad9500c1c1720ee9a3d6ad1e8dd7ebfb4b56bf7a7d0b101fd`, and
`mysmb64.exe` 372856 bytes
`b36762adb84e00c100416441b49465a080e81533035f2a7e0948159bf60f479a`.
No S4 node is deferred.

### S5: Large-platform graphics

`DrawLargePlatform`, `ShrinkPlatform`, `SetLast2Platform`,
`SetPlatformTilenum`, `SChk2`, `SChk3`, `SChk4`, `SChk5`, `SChk6`, `SLChk`,
`ExDLPl`.

The platform route is a single contiguous `LargePlatform` caller through
`DrawLargePlatform` and its six-column offscreen branch. It remains separate
from coin/floatey graphics because those routines enter from `MiscLoop` and
need a distinct original-ROM route. The shared owner is
`src/game/oam/small_platform_gfx.c`; it must consume the already-produced
relative coordinates and offscreen mask, without moving platform policy into
a host adapter. Admission baseline is 1,560/1,992; all eleven open labels are
expected to match, for a maximum 1,571/1,992.

#### S5 P1 implementation checkpoint

`DrawLargePlatform` now follows the source order: stack six X positions from
the caller-written `Enemy_Rel_XPos`, dump four Y rows, always overwrite the
last two rows with either the ordinary Y value or `$f8`, dump the six tile and
attribute rows, then apply the six successive d7..d2 offscreen tests from the
next source enemy slot. The final `Enemy_OffscreenBits` d7 branch dispatches
the shared six-row `$f8` dump. It no longer recomputes relative coordinates or
duplicates `GetXOffscreenBits`.

The focused large-platform regression covers every d7..d2 column, normal
tail-row replacement over stale OAM, castle and secondary-hard tail
suppression, cloud tile `$75`, and whole-object offscreen removal. It passes
on Win32 x86 and x64 together with the existing platform OAM and platform
purity tests. The same source list links as a DOS16 MZ executable. The P1
package is `mysmb16.exe` 258197 bytes
`017ae570e903c96176a80809b50a233d96f1d816c5fca7f415f366bffbc13a29`,
`mysmb32.exe` 361878 bytes
`9993f7b00531140be239a4c400201fd3d6fea039b4cf055ebf44ccf8b0cab0a3`, and
`mysmb64.exe` 370520 bytes
`dcb91fbbd44a1c03ba1895352b8e9496d8e327df3c5051d5cb92b16ffc7233f0`.

This checkpoint grants no node credit. The required original-ROM normal
`RunLargePlatform → DrawLargePlatform` route record has not yet been captured;
the static source comparison and focused native test do not replace it.

#### S5 P2 source-child correction checkpoint

The source-route replay is now in place.  Twenty-eight child records from the
ordinary original-ROM `RunLargePlatform → DrawLargePlatform` route (actor
slots zero and five) replay with zero non-stack RAM differences in both x86
and x64.  The comparison excludes only `$0100-$01ff`, because the 6502 JSR/RTS
stack traffic has no counterpart in the native C call.

That route exposed three observable omissions in P1, which are now corrected
in the shared OAM owner: `DrawLargePlatform` saves `Enemy_SprDataOffset` in
`$02`; `GetXOffscreenBits` now preserves the source `$04-$07` scratch effects;
and the source `INX` changes the common `SprObject` index, so its page/X read
is `Enemy_PageLoc[slot]` / `Enemy_X_Position[slot]`, rather than the next
enemy slot.  The ordinary tail rows are also overwritten on every path, so
stale OAM cannot survive a normal large-platform draw.

The focused large-platform graphics, small-platform OAM, player-scroll,
fireball-OAM, block-OAM, miscellaneous-OAM and platform-purity checks pass on
both Windows widths.  Both product self-tests pass and the shared source links
to the OpenNT DOS16 MZ program.  The refreshed P2 package is `mysmb16.exe`
258325 bytes SHA-256
`c4ddf61a9378b38916710798429b8dde2a880ff6d44c59b5030c92156ad38ff0`,
`mysmb32.exe` 361878 bytes SHA-256
`16ccc4939fc5c8093d9cc27e6ad09bbe662ce896d9ce5dcebba5adfd5f352048`, and
`mysmb64.exe` 370520 bytes SHA-256
`88109e4596cc7f4c0a1951538dcc309f563686cbb5628bc365c9efafda58a236`.

This remains a checkpoint with no node credit.  The normal branch is proven;
castle, secondary-hard, cloud override and whole-object-offscreen branch
families still require controlled original-ROM parent-route records before
S5 can close.

### S6: Floatey-number and jumping-coin graphics

`DrawFloateyNumber_Coin`, `NotRsNum`, `JumpingCoinTiles`,
`JCoinGfxHandler`, `ExJCGfx`.

This is the distinct `MiscLoop` coin/floatey graphics route, after relative
position, offscreen and bounding-box children. It consumes the S4 generic
two-sprite dump helper. It follows S5 in source order but is independently
admitted because it has a different caller and route.

### S7: Power-up graphics

`PowerUpGfxTable`, `PowerUpAttributes`, `DrawPowerUp`, `PUpDrawLoop`,
`FlipPUpRightSide`, `PUpOfs`.

### S8: Enemy graphics and animation

All remaining source labels from `EnemyGraphicsTable` through `EggExc`,
including retained `CheckForBulletBillCV` and `SBBAt`. Its admission will list
the exact 44 labels and re-estimate its new-match subset.

#### S5 closure: large-platform graphics

S5 closes all eleven received labels, moving M2 from **1,560** to **1,571 / 1,992**. `src/game/oam/small_platform_gfx.c` remains the sole owner; no host adapter contains platform, clipping, tile, or OAM policy.

The ROM-logic track replays 28 ordinary `RunLargePlatform -> DrawLargePlatform` records plus ten controlled parent-route records. Those ten cover castle and secondary-hard tail suppression, cloud tile override, whole-object d7 removal, and raw `GetXOffscreenBits` masks `$80`, `$c0`, `$e0`, `$f0`, `$f8`, `$fc` for `SChk2` through `SChk6`. The snapshot comparator reports zero non-6502-stack RAM differences on both x86 and x64 for all 38 records.

`DrawLargePlatform` preserves the source six-X stack, four-plus-two Y dumps, `$5b/$75` tile selection, `$02` scratch write, six successive offscreen checks and `SLChk` six-row removal. `ShrinkPlatform`, `SetLast2Platform`, `SetPlatformTilenum`, `SChk2`, `SChk3`, `SChk4`, `SChk5`, `SChk6`, `SLChk`, and `ExDLPl` are all covered by those parent routes.

Operational proof passes the seven focused x86/x64 tests, both product self-tests, platform-purity audit, and OpenNT DOS16 MZ link. Refreshed artifacts are `mysmb16.exe` `c4ddf61a9378b38916710798429b8dde2a880ff6d44c59b5030c92156ad38ff0`, `mysmb32.exe` `16ccc4939fc5c8093d9cc27e6ad09bbe662ce896d9ce5dcebba5adfd5f352048`, and `mysmb64.exe` `88109e4596cc7f4c0a1951538dcc309f563686cbb5628bc365c9efafda58a236`. No S5 label is deferred.

#### S6 admission: floatey-number and jumping-coin graphics

S6 receives five open labels: `DrawFloateyNumber_Coin`, `NotRsNum`, `JumpingCoinTiles`, `JCoinGfxHandler`, and `ExJCGfx`. It begins at **1,571 / 1,992**, expects all five to become ROM-match complete, and therefore has a maximum of **1,576 / 1,992**. The entry is `MiscLoop -> ProcJumpCoin -> JCoinGfxHandler`; the exit is `ExJCGfx`. The predecessor is S5's OAM helper seam and the successor is S7 power-up graphics. Its one shared owner will be the misc OAM path; host adapters remain consumers only.

The ROM-logic track will use original `MiscLoop` parent-route records to compare state split, frame-parity Y decrement, exact `$60-$63` tile table, two-sprite Y/X/tile/attribute stores and restored `ObjectOffset`. The operational track will add a focused coin/floatey graphics check, replay those records on x86 and x64, build DOS16, audit platform purity and refresh the three required artifacts.
