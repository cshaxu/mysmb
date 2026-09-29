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
| S5 | Platform, floatey and jumping-coin graphics | 16 | 16 |
| S6 | Power-up graphics | 6 | 6 |
| S7 | Enemy graphics and animation | 44 | 42 |
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

`FlagpoleScoreNumTiles`, `FlagpoleGfxHandler`, `ChkFlagOffscreen`,
`MoveSixSpritesOffscreen`, `DumpSixSpr`, `DumpFourSpr`, `DumpThreeSpr`,
`DumpTwoSpr`, `ExitDumpSpr`.

### S5: Platform, floatey and jumping-coin graphics

`DrawLargePlatform`, `ShrinkPlatform`, `SetLast2Platform`,
`SetPlatformTilenum`, `SChk2`, `SChk3`, `SChk4`, `SChk5`, `SChk6`, `SLChk`,
`ExDLPl`, `DrawFloateyNumber_Coin`, `NotRsNum`, `JumpingCoinTiles`,
`JCoinGfxHandler`, `ExJCGfx`.

### S6: Power-up graphics

`PowerUpGfxTable`, `PowerUpAttributes`, `DrawPowerUp`, `PUpDrawLoop`,
`FlipPUpRightSide`, `PUpOfs`.

### S7: Enemy graphics and animation

All remaining source labels from `EnemyGraphicsTable` through `EggExc`,
including retained `CheckForBulletBillCV` and `SBBAt`. Its admission will list
the exact 44 labels and re-estimate its new-match subset.
