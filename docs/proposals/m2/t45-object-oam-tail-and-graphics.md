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

### S2 admission record

The continuing owner-approved M2 source-order mandate admits **M2 T45 S2**
at **1,637 / 1,992**. The fourteen exact labels from
`DefaultBlockObjTiles` through `ExBCDr` are all open, received from
M2 T17 S6; expected new matches are all fourteen, maximum **1,651 / 1,992**.
The caller route is original `BlockObjectsCore -> DrawBlock` and
`BlockObjectsCore -> DrawBrickChunks`, with both slots and source-RAM
controlled area, replacement, offscreen and chunk state. T37 S5 already
isolated 34/64 root OAM-only failures to these child graphics entries;
those are the first regression targets, not authority for new behavior.
The owner-local ROM and reviewed listing are for bounded local comparison
only. Raw records, generated probes, logs and intermediates remain under
ignored `build/m2-t45-s2/`. PC, registers, stack and ROM bytes are not
forced. Each label requires source control/read/write mapping and original
child proof; native x86/x64, DOS16 link, purity and three EXEs form the
separate operational track.

| ROM line | Label | Incoming |
| ---: | --- | --- |
| 14119 | `DefaultBlockObjTiles` | open |
| 14122 | `DrawBlock` | open |
| 14133 | `DBlkLoop` | open |
| 14147 | `ChkRep` | open |
| 14159 | `SetBFlip` | open |
| 14167 | `BlkOffscr` | open |
| 14174 | `PullOfsB` | open |
| 14175 | `ChkLeftCo` | open |
| 14178 | `MoveColOffscreen` | open |
| 14182 | `ExDBlk` | open |
| 14187 | `DrawBrickChunks` | open |
| 14197 | `DChunks` | open |
| 14242 | `ChnkOfs` | open |
| 14250 | `ExBCDr` | open |

### S2 closure: block and brick-chunk OAM

All **14 / 14** scoped labels become ROM-match complete. M2 moves from
**1,637** to **1,651 / 1,992**, with no deferred S2 label. The original
four-byte `DefaultBlockObjTiles` binding at `$ebcd` is `85 85 86 86`;
all thirteen executable labels have original-PC witnesses. Across the
`$ebd1-$ecdd` chain, all ten conditional branches have both outcomes in
the original T37 lifetime caller and eight bounded RAM-only variants.
No variant changes original PC, CPU registers, stack or ROM bytes.

| Source label | Original decision or write and shared C binding | PC witness |
| --- | --- | --- |
| `DefaultBlockObjTiles` | Four ROM bytes bind the two row tile pairs; `block_gfx.c` array | ROM byte check |
| `DrawBlock` | Copy block relative X/Y into `$05/$02`, palette `$03` into `$04`, flip control `$01` into `$03`; `mysmb_objects_draw_bouncing_block` | lifetime 10 |
| `DBlkLoop` | Two `DrawOneSpriteRow` calls store four OAM entries and increment scratch Y; same function | lifetime 10 |
| `ChkRep` | Area type chooses lined top brick; metatile `$c4` selects used-block tiles; same function | lifetime 10, variants 0-3 |
| `SetBFlip` | Area palette and `$40/$80/$c0` attributes for used block; same function | lifetime 10, variants 0/2 |
| `BlkOffscr` | Read original `Block_OffscreenBits` `$03d4`; d2 hides right column; same function | lifetime 10, variant 2 |
| `PullOfsB` | Restore saved bits before d3 check; same function | lifetime 10 |
| `ChkLeftCo` | d3 hides left column for block and chunk callers; both functions | lifetime 10/12 |
| `MoveColOffscreen` | Write `$f8` to two left-column Y entries; both functions and S1 enemy tail | lifetime 10 |
| `ExDBlk` | Return after either column branch; same functions | lifetime 10 |
| `DrawBrickChunks` | Engine subroutine 5 selects `$75`/palette 2, otherwise `$84`/palette 3; `mysmb_objects_draw_brick_chunks` | lifetime 12, variant 4 |
| `DChunks` | Four tile/attribute stores, row Y and reflected X with both 6502 ADC carries; same function | lifetime 12, variants 4-7 |
| `ChnkOfs` | Signed original relative X and unsigned X comparison select right-column hide; same function | lifetime 12, variants 5-7 |
| `ExBCDr` | Return with `$00` holding original relative X; same function | lifetime 12 |

The shared C leaf uses the original `$03bc/$03b1` relative positions and
`$03d4` offscreen bits instead of recalculating clipping from world X.
It preserves `SEC/SBC/ADC/ADC` carries for both chunk X positions and
applies d7 to the first two sprite Y entries. The T37 S5 original child
records now match **30/30** on each width, and the eight new branch cases
match **8/8**, comparing every non-stack 2 KB RAM/OAM byte. The full T37
block lifetime outputs move from 30/64 matches to **64/64** on both widths;
the 34 previously retained OAM failures are resolved. The similar-issue
sweep found one live block graphics owner for both original child calls;
the old world-X clipping helper was removed. No platform code changed.

The separate operational track passes the block OAM smoke, platform purity,
both product self-tests, full x86/x64 builds and OpenNT DOS16 MZ link.
The full suites each pass **222/233**, retaining exactly the same eleven
unrelated failures as S1. Three refreshed owner-authorized artifacts:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `1de8eeff0226b9970c79289248128f15bfb491ed548d5b5d2f020d3b8981e431` |
| `assets/mysmb32.exe` | `a2d2451deda16baf37689bfe03457bf64e5352b38a3d65f8ab091fcbc500e247` |
| `assets/mysmb64.exe` | `199c5f0ec19cb2af6d781e752783aae4dfd04f76f30bb60c8bfc9ef70e6f272b` |

The owner ROM is outside the repository. Raw child records, coverage,
diagnostic probes, build intermediates and logs remain under ignored
`build/`. This closes the block/chunk graphics chain, not whole-game
frame equivalence or physical DOS 486SX performance.

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

### S3 admission record

The continuing owner-approved M2 source-order mandate admits **M2 T45 S3**
at **1,651 / 1,992**. Seven exact labels are in scope and all seven are
expected to become ROM-match complete, for a maximum **1,658 / 1,992**.
`DrawFireball` and `DrawExplosion_Fireball` transfer from M2 T16 S4 with
audited T24 D3/D4 mismatches; the other five transfer from M2 T17 S6 with
open status. Shared `src/game/oam/` owns the chain. S2 block/chunk graphics
precedes it, and S4 small-platform graphics follows it.

| ROM line / PC | Label | Incoming |
| --- | --- | --- |
| 14254 / `$ecde` | `DrawFireball` | audited; mismatch D3 |
| 14261 / `$eced` | `DrawFirebar` | open |
| 14275 / `$ed02` | `FireA` | open |
| 14280 / `$ed06` | `ExplosionTiles` | open |
| 14283 / `$ed09` | `DrawExplosion_Fireball` | audited; mismatch D4 |
| 14292 / `$ed17` | `DrawExplosion_Fireworks` | open |
| 14327 / `$ed61` | `KillFireBall` | open |

The ROM-logic track compares source-reachable original `FireballObjCore`,
`ProcFirebar` and `FireworksObj` child calls with bounded RAM-only frame,
state and relative-coordinate variants. It covers tile phase, attribute flip,
all three explosion tiles, kill transition, four-sprite order, branches and
non-stack RAM/OAM. D3/D4 expected output remains unchanged. The separate
operational track runs focused fireball/firebar/fireworks OAM tests, strict
x86/x64 builds, OpenNT DOS16 MZ link, platform purity and refreshed three
owner-authorized EXEs. The owner-local ROM and reviewed listing are local
verification inputs only. Raw snapshots, probes, logs and intermediates stay
under ignored `build/m2-t45-s3/`; no original PC, register, stack or ROM
modification is permitted.

### S3 closure: projectile and explosion OAM

All **7 / 7** scoped labels are ROM-match complete. M2 advances from
**1,651** to **1,658 / 1,992** with no deferred S3 label. The owner ROM
contains `68 67 66` at the `ExplosionTiles` table. Original PC coverage
reaches each executable label from its normal parent: `FireballObjCore`,
the firebar actor, or the fireworks actor. In 78 bounded original-route
coverage runs, `DrawFireball` enters 12 times, `DrawFirebar` 108,
`FireA` 108, `DrawExplosion_Fireball` eight,
`DrawExplosion_Fireworks` 34 and `KillFireBall` four. The explosion kill
branch at `$ed15` takes and falls through four times each.

| Source label | Original control, data and write binding | PC/data witness |
| --- | --- | --- |
| `DrawFireball` | `FBall_SprDataOffset,x` selects Y/X OAM stores from relative scratch, then falls into the shared tile/attribute code; `fireball_gfx.c` | original core; 32 controlled phases |
| `DrawFirebar` | `FrameCounter >> 2` chooses `$64/$65` tile for both direct firebar and fireball callers; `firebar_gfx.c` and `fireball_gfx.c` | original firebar/core; 32 phases |
| `FireA` | Carry from the second shift pair selects `$02/$c2` attribute. Original `$ecfe` branch reaches both successors **112/112** under RAM-only frame variants; both C leaves use bit 3. | original core/firebar phases |
| `ExplosionTiles` | Original three bytes `68 67 66` feed the explosion consumer; fireworks original calls cover indexes 0/1/2 in **158/158/156** cases; fireball C uses the same three-value order. | ROM bytes and original actor calls |
| `DrawExplosion_Fireball` | Alternate OAM offset, old state to three-value index, state increment before branch; `fireball_gfx.c` | original core states `$80/$85/$86/$ff` |
| `DrawExplosion_Fireworks` | Four equal tiles, Y positions top at entries 0/8 and bottom at 4/12, X positions left at 0/4 and right at 8/12, attributes `02/82/42/c2`; shared fireball/fireworks OAM leaves | original core/fireworks children |
| `KillFireBall` | Index >= 3 clears the indexed state and returns without four-sprite writes; `fireball_gfx.c` | original core states `$86/$ff`; `$ed15` branch |

The T24 D3/D4 mismatches are resolved by changing the shared fireball
attribute selector from frame bit 4 to bit 3 and restoring the second/third
explosion sprite Y order. The existing smoke expectation that had encoded
both mistakes was corrected and now asserts frames eight and sixteen.
The similar-issue sweep covered all three projectile OAM owners and their
production callers: fireball core, firebar actor and fireworks actor. The
firebar leaf already used bit 3, and the fireworks leaf already used the
original four-sprite order; they required proof, not another policy.
No platform gameplay source changed.

The ROM-logic track compared every non-stack 2 KB RAM/OAM byte for
**25** fireball, **448** firebar and **472** fireworks original child
record streams on each native width, with zero mismatches. Those streams
contain **4,529** natural graphics child calls per width. The separate
32-phase fireball and 32-phase firebar original routes compare another
**224** child calls per width with zero mismatches. Original CPU PC,
registers, stack and ROM bytes were never changed; the phase variant writes
only FrameCounter RAM at the naturally reached graphics entry. Raw streams,
intermediate probes and logs remain in ignored `build/m2-t45-s3/`.

The operational track passes the focused fireball/firebar/fireworks OAM and
platform-purity tests, strict C90 x86/x64 builds, OpenNT DOS16 MZ link and
both Win32 product self-tests. The full x86 and x64 suites each pass
**222/233** with exactly the eleven pre-existing failures from S2 and no
new failure. Python validation was rerun with its temporary directory under
ignored `build/` after the initial sandbox Temp denial. DOS remains link-only;
no physical 486SX timing claim is made. Three owner-authorized artifacts:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `1afa4400013394ca7dd0575461f848ea8e8b4bb76777fe239482ebbe1d4b5595` |
| `assets/mysmb32.exe` | `d6317184cc6514f51884860169e8297d5c17ba4cc83711b6fc093b28a0ebe4d0` |
| `assets/mysmb64.exe` | `c2448d735c4c1c493d0d34a98c4263ad2a5925cda945b80d9e5f274aa7ee1b09` |

## S4: small-platform graphics

Entry `DrawSmallPlatform`; exit `ExSPl`. Exact labels:
`DrawSmallPlatform`, `TopSP`, `BotSP`, `SOfs`, `SOfs2`, `ExSPl`.
All six are open under T17 S6 until admission. Shared owner:
`src/game/oam/` small-platform draw. The original small-platform actor route
must cover top/bottom rows, horizontal offscreen clipping and terminal
offset state. T41 actor movement/position is an input, not part of S4.

### S4 admission record

The continuing owner-approved M2 source-order mandate admits **M2 T45 S4**
at **1,658 / 1,992**. The six labels below are all open and transfer from
M2 T17 S6. All six are expected to become ROM-match complete, giving a
maximum **1,664 / 1,992**. `DrawSmallPlatform` is the entry and `ExSPl`
the exit. Shared `src/game/oam/small_platform_gfx.c` owns the graphics
decisions; S3 projectile graphics precedes it and S5 bubble/player data
follows. The T41 small-platform caller supplies relative position and
offscreen scratch, so that producer is an input rather than S4 logic.

| ROM line / PC | Label | Incoming |
| --- | --- | --- |
| 14334 / `$ed66` | `DrawSmallPlatform` | open |
| 14361 / `$ed9c` | `TopSP` | open |
| 14369 / `$edaa` | `BotSP` | open |
| 14379 / `$edc3` | `SOfs` | open |
| 14386 / `$edd1` | `SOfs2` | open |
| 14392 / `$edde` | `ExSPl` | open |

The ROM-logic track starts from original `RunSmallPlatform` actor calls,
then varies only bounded input RAM at the naturally reached graphics entry
to cover vertical status-bar clipping and all d3/d2/d1 column masks.
It compares control PCs, OAM and all non-stack RAM after the graphics child,
including the caller-produced scratch. The separate operational track runs
focused small-platform and caller tests, strict C90 x86/x64 builds, OpenNT
DOS16 MZ link, platform purity and refreshed three owner-authorized EXEs.
The owner-local ROM and reviewed listing remain local inputs only. Raw
records, probes, logs and intermediates stay under ignored `build/m2-t45-s4/`;
the original PC, registers, stack and ROM bytes are never modified.

### S4 closure: small-platform graphics

All **6 / 6** scoped labels are ROM-match complete. M2 advances from
**1,658** to **1,664 / 1,992**, with no deferred S4 label. The original
`RunSmallPlatform` route reaches `DrawSmallPlatform` naturally in both slot
zero and slot five. Eight unmodified child records and 64 bounded RAM-only
entry variants match the native x86 and x64 implementation over every
non-stack 2 KB RAM/OAM byte, with zero differences. The variants change
only source input RAM after the original actor reaches `$ed66`; CPU PC,
registers, stack and ROM are untouched. Original PC coverage reaches each
of the six scoped labels in all 64 variants. The top and bottom status-bar
branches reach both successors **16/48** each; the three column-mask
branches each reach both successors **32/32**.

| Source label | Original control, data and write binding | Witness |
| --- | --- | --- |
| `DrawSmallPlatform` | Reads caller-produced `Enemy_Rel_XPos` and `Enemy_OffscreenBits`, indexed `Enemy_Y_Position` and sprite offset; writes tile `$5b`, attribute `$02`, and X columns at +0/+8/+16 for two rows. `small_platform_gfx.c` consumes these inputs without recomputing them. | Original `RunSmallPlatform` child; both slots; 64 input variants. |
| `TopSP` | Selects real top-row Y when `Enemy_Y_Position >= $20`, otherwise `$f8`; writes all three top entries. | Original `$ed98` branch both outcomes 16/48. |
| `BotSP` | Adds `$80` modulo 256 to the original Y, selecting `$f8` on status-bar wrap; writes all three bottom entries. | Original `$eda6` branch both outcomes 16/48. |
| `SOfs` | Offscreen bit d3 hides the first and fourth sprites, then tests d2. | Original `$edb9` branch both outcomes 32/32. |
| `SOfs2` | Offscreen bit d2 hides the second and fifth sprites, then tests d1. | Original `$edc7` branch both outcomes 32/32. |
| `ExSPl` | Offscreen bit d1 hides the third and sixth sprites, then restores `ObjectOffset` as X at return. | Original `$edd4` branch both outcomes 32/32; child exit state. |

The prior draw function recomputed relative X/Y and offscreen bits from
world state, overwriting the caller's source scratch. Replaying an original
child against that version gives a RAM difference at `$0243` (ROM X `$30`,
C X `$50`); the corrected version matches the same record. The existing
smoke test now supplies the caller-produced offscreen byte and checks all
six sprite Y entries. The similar-issue sweep covered this graphics leaf,
its actor caller and the adjacent large-platform leaf; the latter already
consumes relative scratch and retains its earlier owner. No platform
adapter or gameplay source changed.

The separate operational track passes focused small-platform graphics,
special-actor and platform-purity checks, strict C90 x86/x64 builds,
OpenNT DOS16 MZ link and both Win32 product self-tests. The full x86 and
x64 suites each pass **222/233**, with precisely the eleven pre-existing
failures and no new failure. DOS remains link-only; no physical 486SX
timing claim is made. Owner-authorized refreshed products:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `0de19e7146029f0320b4ef027fe9c21ac6e58981b995f8c5c163c2b0f9ad1e30` |
| `assets/mysmb32.exe` | `d4889fb61630eb63dfa622fae2f2d4fa27cca388cb44c23d42ae09f393037363` |
| `assets/mysmb64.exe` | `6b419748c49eb9f527b49dc724b505cbdf078e9a69ee04ed336a8738dc079e6d` |

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
