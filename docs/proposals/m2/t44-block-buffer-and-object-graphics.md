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

### S2: Vine object graphics

`VineYPosAdder`, `DrawVine`, `VineTL`, `SkpVTop`, `ChkFTop`, `NextVSp`.

### S3: Six-sprite and hammer graphics

`SixSpriteStacker`, `StkLp`, `FirstSprXPos`, `FirstSprYPos`, `SecondSprXPos`,
`SecondSprYPos`, `FirstSprTilenum`, `SecondSprTilenum`, `HammerSprAttrib`,
`DrawHammer`, `ForceHPose`, `GetHPose`, `RenderH`, `NoHOffscr`.

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
