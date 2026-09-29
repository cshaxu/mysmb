# M2 T45: object OAM tail and graphics

## Task contract

T45 owns the 45 source labels from `CheckToMirrorLakitu` (line 14007) through
`SwimKickTileNum` (line 14457), within planned source lines 14001-14459.
The incoming verified count is **1,624 / 1,992**. All 45 labels remain
incomplete: 41 are open, while `DrawFireball`, `DrawExplosion_Fireball`,
`PlayerGraphicsTable` and `SwimKickTileNum` have earlier audits but no ROM
match. The maximum resulting count is **1,669 / 1,992**. No scope label is
already complete; no investigation-only credit is planned.

This is the source continuation of T44's `EggExc` branch. It completes the
enemy graphics OAM/offscreen tail, then block/chunk, projectile/explosion,
small-platform, bubble and player graphics-data consumers. Shared
`src/game/oam/` owns all gameplay and sprite decisions. Win32 and DOS16
adapters only present the shared game result. Existing public translations
are not implementation inputs; the owner-local ROM and reviewed listing
remain nonredistributable research/build inputs. Raw records, logs and all
intermediate files stay under ignored `build/`.

| S | Contiguous source chain | Scope | Expected new | Current receiver |
| --- | --- | ---: | ---: | --- |
| S1 | `CheckToMirrorLakitu` to `MoveESprColOffscreen` | 13 | 13 | T17 S6 |
| S2 | `DefaultBlockObjTiles` to `ExBCDr` | 14 | 14 | T17 S6 |
| S3 | `DrawFireball` to `KillFireBall` | 7 | 7 | T17 S6 (5), T16 S4 (2) |
| S4 | `DrawSmallPlatform` to `ExSPl` | 6 | 6 | T17 S6 |
| S5 | `DrawBubble` to `SwimKickTileNum` | 5 | 5 | T17 S6 (3), T16 S4 (2) |
| **Total** | **14007-14457** | **45** | **45** | **Exact transfers at admission** |

Each S first maps source control, table reads, work bytes, OAM writes and
successors. The ROM-logic track then compares bounded original-ROM child
inputs/outputs, all non-stack RAM/OAM and branch PCs on a source-reachable or
RAM-controlled original caller route. Native tests or a visible screen do not
substitute for this track. The separate operational track runs focused tests,
strict C90 x86/x64 builds, a DOS16 MZ link, platform-purity check and three
owner-authorized executable artifacts at each P. Existing eleven unrelated
full-suite failures retain their recorded baseline; any new failure blocks
the affected P. T closure adds a cross-chain matrix and final integrated
three-target run.

## S1: enemy graphics mirror, row draw and offscreen tail

Entry `CheckToMirrorLakitu` after T44 `EggExc`; exit
`MoveESprColOffscreen`. Exact source-order labels:
`CheckToMirrorLakitu`, `NVFLak`, `CheckToMirrorJSpring`,
`SprObjectOffscrChk`, `LcChk`, `Row3C`, `Row23C`, `AllRowC`,
`ExEGHandler`, `DrawEnemyObjRow`, `DrawOneSpriteRow`,
`MoveESprRowOffscreen`, `MoveESprColOffscreen`. Thirteen open labels transfer
from T17 S6 only when S1 is admitted. Shared owner: `src/game/oam/`;
predecessor T44 S8 ordinary/Bowser/spring draw, successor S2 block OAM.

The source route is `RunNormalEnemies -> EnemyGfxHandler` plus the existing
Bowser and jumpspring callers. Exercise Lakitu both sides of the frenzy-timer
branch, spring attributes, row/column offscreen masks d2-d7, final enemy
erase, and the three `DrawEnemyObjRow` calls. Original child snapshots from
T44 establish the incoming handler boundary; S1 must compare the tail's
branches and writes explicitly, not infer completion from the prior parent
match. The operational track includes the ordinary/Bowser/retainer/spring
snapshots and affected OAM tests on both Windows widths, DOS16 link, purity
and three EXEs. Admission baseline 1,624; expected completion 13; maximum
1,637 / 1,992.

### S1 admission record

The continuing owner-approved M2 mandate admits **M2 T45 S1** at
**1,624 / 1,992**. All thirteen labels transfer from M2 T17 S6. The prior
T44 original-PC records reach eleven labels in this exact span. `NVFLak`
and `MoveESprRowOffscreen` have no captured entry yet; S1 must produce
bounded original-route witnesses for both before claiming a complete chain.

| ROM line / PC | Label | Incoming | Prior original-PC witness |
| --- | --- | --- | --- |
| 14007 / `$eb12` | `CheckToMirrorLakitu` | open | ordinary graphics |
| 14026 / `$eb3e` | `NVFLak` | open | missing |
| 14033 / `$eb4e` | `CheckToMirrorJSpring` | open | ordinary graphics |
| 14044 / `$eb64` | `SprObjectOffscrChk` | open | ordinary graphics |
| 14054 / `$eb74` | `LcChk` | open | ordinary graphics |
| 14060 / `$eb7e` | `Row3C` | open | ordinary graphics |
| 14067 / `$eb89` | `Row23C` | open | ordinary graphics |
| 14073 / `$eb93` | `AllRowC` | open | ordinary graphics |
| 14085 / `$eba9` | `ExEGHandler` | open | ordinary graphics |
| 14088 / `$ebaa` | `DrawEnemyObjRow` | open | ordinary graphics |
| 14093 / `$ebb2` | `DrawOneSpriteRow` | open | ordinary graphics |
| 14097 / `$ebb7` | `MoveESprRowOffscreen` | open | missing |
| 14104 / `$ebc1` | `MoveESprColOffscreen` | open | Bowser graphics |

The ROM input is the owner-local `smb1.nes` revision already used by T44;
the reviewed `SMBDIS.ASM` listing supplies label and branch meaning. Original
CPU PC/stack/registers and ROM bytes stay unmodified. Only bounded RAM at a
naturally reached call entry may vary. Recorder outputs, derived coverage,
diagnostic patches and logs remain under ignored `build/m2-t45-s1/` with
per-process time limits and no raw trace commit. The source-policy review
permits this local verification use; it grants no redistributability.

### S1 closure: enemy OAM tail

All **13 / 13** scoped labels become ROM-match complete. M2 moves from
**1,624** to **1,637 / 1,992**; none is deferred. Original PC coverage from
the T44 normal/Bowser child routes plus five new RAM-controlled original
normal calls reaches every executable label. The new Lakitu state `$20`
reaches `NVFLak` at `$eb3e`. Four d5-d7 mask cases reach
`MoveESprRowOffscreen` at `$ebb7` without forcing PC, registers, stack or
ROM. Original `DumpTwoSpr` writes exactly one two-sprite row per call. The
prior C translation wrongly treated d6 as two rows and d7 as all three;
the corrected shared game OAM tail maps d7/d6/d5 to first/second/third row,
and d3/d2 to left/right columns across all rows.

| Source label | Original decision or write and shared C binding | PC witness |
| --- | --- | --- |
| `CheckToMirrorLakitu` | ID `$11`, vertical flag and frenzy timer select lower-row attributes; `normal_enemy_gfx.c` Lakitu branch | `g0v2` |
| `NVFLak` | Vertical flag selects first-row masks `$81` and `$41`; same Lakitu branch | `lakitu-v5` |
| `CheckToMirrorJSpring` | IDs `>= $18` write `$82/$c2` to lower rows; `mysmb_oam_draw_jumpspring` and normal handler | `g0v2` |
| `SprObjectOffscrChk` | Reload object offset, shift d2 into carry; `enemy_offscreen_tail.h` | `g0v2` |
| `LcChk` | d3 hides left column of three rows; same tail | `g0v2` |
| `Row3C` | d5 calls row mover at offset `$10`; same tail | `goomba-v16` |
| `Row23C` | d6 calls row mover at offset `$08`; same tail | `goomba-v17` |
| `AllRowC` | d7 calls row mover at offset `$00`, then conditional erase; same tail and normal handler | `goomba-v18` |
| `ExEGHandler` | Return after offscreen processing or erase exception; normal/Bowser/spring callers | `g0v2` |
| `DrawEnemyObjRow` | Read adjacent source tile bytes into `$00/$01`; `mysmb_enemy_draw_row` | `g0v2` |
| `DrawOneSpriteRow` | Tail jump to `DrawSpriteObject`; `mysmb_enemy_draw_row` | `g0v2` |
| `MoveESprRowOffscreen` | Add sprite offset and write `$f8` through `DumpTwoSpr`, one row only; shared tail | `goomba-v16` |
| `MoveESprColOffscreen` | Add sprite offset, hide three entries in one column; shared tail | `b0` |

The five new original child snapshots compare every non-stack 2 KB RAM/OAM
byte with shared C at **5/5 zero differences on x86 and x64**. The preceding
normal **84/84**, Bowser **1,024/1,024**, retainer **72/72** and spring
**32/32** child calls remain zero-difference on both widths. The similar-issue
sweep covered all production copies of the mistaken row policy: normal,
Bowser, hammer bro, Spiny, Podoboo, power-up and the older directly callable
Bloober, Cheep, Bullet Bill, Goomba and Piranha OAM helpers. They now use the
original row mapping. The power-up OAM smoke assertion was corrected to
expect only the first row hidden for d7.

The separate operational track passes **17/17 focused CTests** on each
Windows width, including platform purity and product self-tests. Full x86
and x64 suites each pass **222/233**; their identical eleven failures are
the T44 baseline, with no new failure. Strict x86/x64 builds and the OpenNT
DOS16 MZ link pass. Three refreshed owner-authorized executable artifacts:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `dde34d66ccc8d62ba351584b154193b746a15252b315681218fc124be7a3e0bc` |
| `assets/mysmb32.exe` | `965350a02e25519523dacceaea05fd1aa746f40208c5669ebffe46d06ee29eb6` |
| `assets/mysmb64.exe` | `4d0ee05f2b31da7f9f716983e836e77b99e5d54fe5034ab0d33060a4f6dbc32a` |

ROM-derived child snapshots, PC traces and generated intermediate files
remain only in ignored `build/`; the owner ROM remains outside this repo.
This verifies the bounded S1 chain, not whole-game frame equivalence or a
physical DOS 486SX performance result.

## S2: block and brick-chunk graphics

Entry `DefaultBlockObjTiles`; exit `ExBCDr`. Exact labels:
`DefaultBlockObjTiles`, `DrawBlock`, `DBlkLoop`, `ChkRep`, `SetBFlip`,
`BlkOffscr`, `PullOfsB`, `ChkLeftCo`, `MoveColOffscreen`, `ExDBlk`,
`DrawBrickChunks`, `DChunks`, `ChnkOfs`, `ExBCDr`. All fourteen are open with
T17 S6 custody until admission. Shared owner: block/chunk OAM in
`src/game/oam/`; predecessor S1 sprite-row/offscreen primitives; successor
S3 projectile graphics. The ROM-logic route is the original block-hit and
brick-shatter caller, covering repeated rows, mirrored attributes, wrapped
column hiding and each chunk. Recheck the recorded T37 S5 edge-output gap.
Operational proof follows the common dual-track build/artifact contract.

## S3: fireball, firebar and explosions

Entry `DrawFireball`; exit `KillFireBall`. Exact labels:
`DrawFireball`, `DrawFirebar`, `FireA`, `ExplosionTiles`,
`DrawExplosion_Fireball`, `DrawExplosion_Fireworks`, `KillFireBall`.
`DrawFireball` and `DrawExplosion_Fireball` currently belong to T16 S4
and have audited mismatches; the other five are open under T17 S6.
Shared owner: fireball/firebar/fireworks OAM in `src/game/oam/`.
The original fireball core and firebar/fireworks actor calls supply frame,
phase, tile order and OAM comparisons. Explicitly recheck T24 D3/D4 rather
than changing expected output. Fireball game motion/collision remains with
its own prior source owner; S3 selects graphics and lifetime tail only.

## S4: small-platform graphics

Entry `DrawSmallPlatform`; exit `ExSPl`. Exact labels:
`DrawSmallPlatform`, `TopSP`, `BotSP`, `SOfs`, `SOfs2`, `ExSPl`.
All six are open under T17 S6 until admission. Shared owner:
`src/game/oam/` small-platform draw. The original small-platform actor route
must cover top/bottom rows, horizontal offscreen clipping and terminal
offset state. T41 actor movement/position is an input, not part of S4.

## S5: bubble and player graphics data

Entry `DrawBubble`; exit `SwimKickTileNum`. Exact labels:
`DrawBubble`, `ExDBub`, `PlayerGfxTblOffsets`, `PlayerGraphicsTable`,
`SwimKickTileNum`. The first three are open under T17 S6; the latter two
are incomplete audited labels under T16 S4. Shared owner: bubble/player
graphics in `src/game/oam/`. Original bubble and player-render callers
prove bubble position/offscreen output and bind the two player data tables
to owner ROM bytes. `SwimKickTileNum` also requires the T24 D5 swim-kick
route; translating table values without consumer parity earns no match.

## Completion boundary

At every S closure, record all scoped label dispositions separately in the
canonical inventory and node progress ledger. A label with an unresolved
branch or native mismatch remains incomplete and transfers by exact name to
an accepted successor. Task closure reports the before/after count, all
45 named outcomes, source-route evidence, x86/x64 and DOS16 checks, platform
purity and three executable hashes. The next source label `PlayerGfxHandler`
belongs to T46; T45 does not credit that body by association.
