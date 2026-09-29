# M2 T43: terrain collision and bounding boxes

## Task contract

Admitted under the continuing owner-approved M2 mandate after cd70ae9.
Baseline1,382/1,992. Scope150 unique nodes:136 expected new and14 retained
matches, maximum1,518/1,992. Exact labels, current receivers and per-S expected
subsets are listed below. Only S1 is admitted now; later S groups keep their
current receivers until explicit admission. No investigation-only credit.

The old13000 boundary split SprObjectCollisionCore before its two return
labels. Include NoCollisionFound and CollisionFound, ending at13022 before
BlockBufferChk_Enemy. The following slice starts13023, reducing its111 nodes
to109. Source order is unchanged. This slice includes player and enemy terrain,
fireball background and bounding boxes; its title reflects actual source.

## Delivery and proof rules

Each S implements one complete listed control/data chain. Map all branches,
reads, writes, tables, entry/return registers and call/tail order first. Move
its single production owner out of mixed legacy code as needed; remove old
bodies after wiring the original caller. Do not build a parallel algorithm.
Platform code contains no gameplay and no runtime emulator is introduced.

Original proof uses naturally reached or controlled-input original NMI roots,
with no ROM/PC/stack/register/output patch. Compare complete child inputs and
used return state before any child replay. Verify the same root separately
with real native descendants and name every remaining child discrepancy.
Local passing tests or observed gameplay do not replace this logic track.
Retained matches are rechecked at relevant changed boundaries, never recounted.

Each S runs its focused native CTest, affected caller tests, strict C90 x86/x64,
DOS16 compile/link, platform purity and refreshed three EXEs once per P.
Each label's row receives both proof tracks or an accepted exact transfer.
T closure adds a cross-chain matrix and final integrated delivery. No isolated
caller result claims descendant or whole-game equivalence.

Owner-local ROM and listing remain nonredistributable research/build inputs.
Generated resources, raw records and logs stay in ignored build. S1 permits
2,048 controlled cases and100 MB raw records, with20-second process deadlines
and checkpoints. Coordinator owns cleanup after dependent regressions.
Three owner-authorized EXEs are the delivery exception; DOS remains link-only.

## Source-ordered S chains

### S1: Player terrain root: head, feet and sides

Source lines11924-12146; entry `PlayerBGCollision`; final label `AreaChangeTimerData`. Shared owner: `src/game/player/terrain.c`.
31 scoped nodes; 31 expected new; 0 retained.
Logic route and dependency boundary: Coin/axe, climbing, pipe, impede, metatile classification, block-buffer and head-hit children remain separate; verify their complete inputs and terminal tail transfers.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `PlayerBGUpperExtent`, `PlayerBGCollision`, `SetFallS`, `SetPSte`, `ChkOnScr`, `ExPBGCol`, `ChkCollSize`, `GBBAdr`, `HeadChk`, `SolidOrClimb`, `NYSpd`, `DoFootCheck`, `AwardTouchedCoin`, `ChkFootMTile`, `ContChk`, `LandPlyr`, `InitSteP`, `DoPlayerSideCheck`, `SideCheckLoop`, `BHalf`, `ExSCH`, `CheckSideMTiles`, `ContSChk`, `ChkPBtm`, `PipeDwnS`, `PlyrPipe`, `SetCATmr`, `ChkGERtn`, `StopPlayerMove`, `ExCSM`, `AreaChangeTimerData`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 11924 | `PlayerBGUpperExtent` | open | M2 T17 S6 |
| 11927 | `PlayerBGCollision` | open | M2 T17 S6 |
| 11942 | `SetFallS` | open | M2 T17 S6 |
| 11943 | `SetPSte` | open | M2 T17 S6 |
| 11944 | `ChkOnScr` | open | M2 T17 S6 |
| 11952 | `ExPBGCol` | open | M2 T17 S6 |
| 11954 | `ChkCollSize` | open | M2 T17 S6 |
| 11964 | `GBBAdr` | open | M2 T17 S6 |
| 11971 | `HeadChk` | open | M2 T17 S6 |
| 11992 | `SolidOrClimb` | open | M2 T17 S6 |
| 11997 | `NYSpd` | open | M2 T17 S6 |
| 12000 | `DoFootCheck` | open | M2 T17 S6 |
| 12019 | `AwardTouchedCoin` | open | M2 T17 S6 |
| 12022 | `ChkFootMTile` | open | M2 T17 S6 |
| 12030 | `ContChk` | open | M2 T17 S6 |
| 12040 | `LandPlyr` | open | M2 T17 S6 |
| 12049 | `InitSteP` | open | M2 T17 S6 |
| 12052 | `DoPlayerSideCheck` | open | M2 T17 S6 |
| 12059 | `SideCheckLoop` | open | M2 T17 S6 |
| 12075 | `BHalf` | open | M2 T17 S6 |
| 12086 | `ExSCH` | open | M2 T17 S6 |
| 12088 | `CheckSideMTiles` | open | M2 T17 S6 |
| 12094 | `ContSChk` | open | M2 T17 S6 |
| 12101 | `ChkPBtm` | open | M2 T17 S6 |
| 12111 | `PipeDwnS` | open | M2 T17 S6 |
| 12115 | `PlyrPipe` | open | M2 T17 S6 |
| 12124 | `SetCATmr` | open | M2 T17 S6 |
| 12126 | `ChkGERtn` | open | M2 T17 S6 |
| 12140 | `StopPlayerMove` | open | M2 T17 S6 |
| 12142 | `ExCSM` | open | M2 T17 S6 |
| 12144 | `AreaChangeTimerData` | open | M2 T17 S6 |

### S2: Coin and axe metatile effects

Source lines12147-12168; entry `HandleCoinMetatile / HandleAxeMetatile`; final label `ErACM`. Shared owner: `src/game/player/terrain_metatiles.c`.
3 scoped nodes; 3 expected new; 0 retained.
Logic route and dependency boundary: Erase block-buffer tile, award coin and axe mode transition; existing coin award and bridge setup are children.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `HandleCoinMetatile`, `HandleAxeMetatile`, `ErACM`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12147 | `HandleCoinMetatile` | open | M2 T17 S6 |
| 12152 | `HandleAxeMetatile` | open | M2 T17 S6 |
| 12159 | `ErACM` | open | M2 T17 S6 |

### S3: Flagpole and vine climbing

Source lines12169-12262; entry `HandleClimbing`; final label `ExPVne`. Shared owner: `src/game/player/climbing.c`.
14 scoped nodes; 14 expected new; 0 retained.
Logic route and dependency boundary: Bind positioning and score tables; flagpole/vine state, facing, page carry, sound and score; preserve caller exits.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `ClimbXPosAdder`, `ClimbPLocAdder`, `FlagpoleYPosData`, `HandleClimbing`, `ExHC`, `ChkForFlagpole`, `FlagpoleCollision`, `ChkFlagpoleYPosLoop`, `MtchF`, `RunFR`, `VineCollision`, `PutPlayerOnVine`, `SetVXPl`, `ExPVne`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12169 | `ClimbXPosAdder` | open | M2 T17 S6 |
| 12172 | `ClimbPLocAdder` | open | M2 T17 S6 |
| 12175 | `FlagpoleYPosData` | open | M2 T17 S6 |
| 12178 | `HandleClimbing` | open | M2 T17 S6 |
| 12184 | `ExHC` | open | M2 T17 S6 |
| 12186 | `ChkForFlagpole` | open | M2 T17 S6 |
| 12192 | `FlagpoleCollision` | open | M2 T17 S6 |
| 12212 | `ChkFlagpoleYPosLoop` | open | M2 T17 S6 |
| 12217 | `MtchF` | open | M2 T17 S6 |
| 12218 | `RunFR` | open | M2 T17 S6 |
| 12222 | `VineCollision` | open | M2 T17 S6 |
| 12231 | `PutPlayerOnVine` | open | M2 T17 S6 |
| 12244 | `SetVXPl` | open | M2 T17 S6 |
| 12259 | `ExPVne` | open | M2 T17 S6 |

### S4: Invisible tiles and jumpspring landing

Source lines12263-12294; entry `ChkInvisibleMTiles / ChkForLandJumpSpring`; final label `NoJSFnd`. Shared owner: `src/game/player/terrain_metatiles.c`.
7 scoped nodes; 7 expected new; 0 retained.
Logic route and dependency boundary: Invisible comparison flags, spring identities and activation; reached from player head/foot routes.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `ChkInvisibleMTiles`, `ExCInvT`, `ChkForLandJumpSpring`, `ExCJSp`, `ChkJumpspringMetatiles`, `JSFnd`, `NoJSFnd`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12263 | `ChkInvisibleMTiles` | open | M2 T17 S6 |
| 12267 | `ExCInvT` | open | M2 T17 S6 |
| 12273 | `ChkForLandJumpSpring` | open | M2 T17 S6 |
| 12284 | `ExCJSp` | open | M2 T17 S6 |
| 12286 | `ChkJumpspringMetatiles` | open | M2 T17 S6 |
| 12292 | `JSFnd` | open | M2 T17 S6 |
| 12293 | `NoJSFnd` | open | M2 T17 S6 |

### S5: Vertical pipe entry and warp selection

Source lines12295-12342; entry `HandlePipeEntry`; final label `ExPipeE`. Shared owner: `src/game/player/pipe_entry.c`.
3 scoped nodes; 3 expected new; 0 retained.
Logic route and dependency boundary: Two foot tiles, directional input, timers, world lookup and area transition; original pipe route.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `HandlePipeEntry`, `GetWNum`, `ExPipeE`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12295 | `HandlePipeEntry` | open | M2 T17 S6 |
| 12326 | `GetWNum` | open | M2 T17 S6 |
| 12341 | `ExPipeE` | open | M2 T17 S6 |

### S6: Player side impediment

Source lines12343-12379; entry `ImpedePlayerMove`; final label `ExIPM`. Shared owner: `src/game/player/impede.c`.
5 scoped nodes; 5 expected new; 0 retained.
Logic route and dependency boundary: Direction-dependent CPY/ADC/SBC carry, speed80 edge, page wrap and collision latch; called by terrain/platforms.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `ImpedePlayerMove`, `RImpd`, `NXSpd`, `PlatF`, `ExIPM`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12343 | `ImpedePlayerMove` | open | M2 T17 S6 |
| 12354 | `RImpd` | open | M2 T17 S6 |
| 12358 | `NXSpd` | open | M2 T17 S6 |
| 12365 | `PlatF` | open | M2 T17 S6 |
| 12372 | `ExIPM` | open | M2 T17 S6 |

### S7: Metatile classification

Source lines12380-12419; entry `CheckForSolidMTiles / CheckForClimbMTiles / CheckForCoinMTiles`; final label `ExEBG`. Shared owner: `src/game/world/metatiles.c`.
8 scoped nodes; 7 expected new; 1 retained.
Logic route and dependency boundary: Bind threshold tables, attribute rotation, coin sound and exact flags; shared ExEBG remains retained evidence.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `SolidMTileUpperExt`, `CheckForSolidMTiles`, `ClimbMTileUpperExt`, `CheckForClimbMTiles`, `CheckForCoinMTiles`, `CoinSd`, `GetMTileAttrib`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12380 | `SolidMTileUpperExt` | open | M2 T17 S6 |
| 12383 | `CheckForSolidMTiles` | open | M2 T17 S6 |
| 12388 | `ClimbMTileUpperExt` | open | M2 T17 S6 |
| 12391 | `CheckForClimbMTiles` | open | M2 T17 S6 |
| 12396 | `CheckForCoinMTiles` | open | M2 T17 S6 |
| 12403 | `CoinSd` | open | M2 T17 S6 |
| 12407 | `GetMTileAttrib` | open | M2 T17 S6 |
| 12415 | `ExEBG` | ROM-match complete | M2 T31 S2 |

### S8: Enemy terrain dispatch and stun

Source lines12420-12522; entry `EnemyToBGCollisionDet / ChkToStunEnemies`; final label `ExEBGChk`. Shared owner: `src/game/enemy/background.c`.
18 scoped nodes; 12 expected new; 6 retained.
Logic route and dependency boundary: Preserve certified dispatch; bind state/speed data, block-hit effects and A-based demotion/stun; landing remains next child.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `EnemyBGCStateData`, `EnemyBGCXSpdData`, `NoEToBGCollision`, `HandleEToBGCollision`, `GiveOEPoints`, `ChkToStunEnemies`, `Demote`, `SetStun`, `SetWYSpd`, `SetNotW`, `ChkBBill`, `NoCDirF`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12420 | `EnemyBGCStateData` | open | M2 T17 S6 |
| 12423 | `EnemyBGCXSpdData` | open | M2 T17 S6 |
| 12426 | `EnemyToBGCollisionDet` | ROM-match complete | M2 T31 S2 |
| 12439 | `DoIDCheckBGColl` | ROM-match complete | M2 T31 S2 |
| 12443 | `HBChk` | ROM-match complete | M2 T31 S2 |
| 12446 | `CInvu` | ROM-match complete | M2 T31 S2 |
| 12452 | `YesIn` | ROM-match complete | M2 T31 S2 |
| 12455 | `NoEToBGCollision` | open | M2 T17 S6 |
| 12461 | `HandleEToBGCollision` | open | M2 T17 S6 |
| 12476 | `GiveOEPoints` | open | M2 T17 S6 |
| 12480 | `ChkToStunEnemies` | open | M2 T17 S6 |
| 12489 | `Demote` | open | M2 T17 S6 |
| 12491 | `SetStun` | open | M2 T17 S6 |
| 12503 | `SetWYSpd` | open | M2 T17 S6 |
| 12504 | `SetNotW` | open | M2 T17 S6 |
| 12509 | `ChkBBill` | open | M2 T17 S6 |
| 12515 | `NoCDirF` | open | M2 T17 S6 |
| 12518 | `ExEBGChk` | ROM-match complete | M2 T31 S2 |

### S9: Enemy landing and grounded state

Source lines12523-12616; entry `LandEnemyProperly`; final label `SetD6Ste`. Shared owner: `src/game/enemy/background.c`.
14 scoped nodes; 14 expected new; 0 retained.
Logic route and dependency boundary: Vertical nibble windows, state tables, red-koopa edge, direction and falling transitions; original ground route.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `LandEnemyProperly`, `SChkA`, `ChkLandedEnemyState`, `SetForStn`, `ExSteChk`, `ProcEnemyDirection`, `InvtD`, `CNwCDir`, `LandEnemyInitState`, `NMovShellFallBit`, `ChkForRedKoopa`, `Chk2MSBSt`, `GetSteFromD`, `SetD6Ste`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12523 | `LandEnemyProperly` | ROM-match complete | M2 T43 S9 |
| 12535 | `SChkA` | ROM-match complete | M2 T43 S9 |
| 12537 | `ChkLandedEnemyState` | ROM-match complete | M2 T43 S9 |
| 12552 | `SetForStn` | ROM-match complete | M2 T43 S9 |
| 12556 | `ExSteChk` | ROM-match complete | M2 T43 S9 |
| 12558 | `ProcEnemyDirection` | ROM-match complete | M2 T43 S9 |
| 12571 | `InvtD` | ROM-match complete | M2 T43 S9 |
| 12575 | `CNwCDir` | ROM-match complete | M2 T43 S9 |
| 12580 | `LandEnemyInitState` | ROM-match complete | M2 T43 S9 |
| 12589 | `NMovShellFallBit` | ROM-match complete | M2 T43 S9 |
| 12597 | `ChkForRedKoopa` | ROM-match complete | M2 T43 S9 |
| 12603 | `Chk2MSBSt` | ROM-match complete | M2 T43 S9 |
| 12610 | `GetSteFromD` | ROM-match complete | M2 T43 S9 |
| 12611 | `SetD6Ste` | ROM-match complete | M2 T43 S9 |

### S10: Enemy side, jump and hammer terrain

Source lines12617-12731; entry `DoEnemySideCheck / EnemyJump / HammerBroBGColl`; final label `NoUnderHammerBro`. Shared owner: `src/game/enemy/background.c`.
16 scoped nodes; 9 expected new; 7 retained.
Logic route and dependency boundary: Retain certified side/jump leaves; complete bump response, distance borrow, landing and hammer underside path.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `ChkForBump_HammerBroJ`, `NoBump`, `InvEnemyDir`, `PlayerEnemyDiff`, `EnemyLanding`, `HammerBroBGColl`, `KillEnemyAboveBlock`, `UnderHammerBro`, `NoUnderHammerBro`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12617 | `DoEnemySideCheck` | ROM-match complete | M2 T31 S2 |
| 12624 | `SdeCLoop` | ROM-match complete | M2 T31 S2 |
| 12632 | `NextSdeC` | ROM-match complete | M2 T31 S2 |
| 12636 | `ExESdeC` | ROM-match complete | M2 T31 S2 |
| 12638 | `ChkForBump_HammerBroJ` | open | M2 T17 S6 |
| 12646 | `NoBump` | open | M2 T17 S6 |
| 12654 | `InvEnemyDir` | open | M2 T17 S6 |
| 12660 | `PlayerEnemyDiff` | open | M2 T17 S6 |
| 12671 | `EnemyLanding` | open | M2 T17 S6 |
| 12679 | `SubtEnemyYPos` | ROM-match complete | M2 T31 S2 |
| 12686 | `EnemyJump` | ROM-match complete | M2 T31 S2 |
| 12701 | `DoSide` | ROM-match complete | M2 T31 S2 |
| 12705 | `HammerBroBGColl` | open | M2 T17 S6 |
| 12711 | `KillEnemyAboveBlock` | open | M2 T17 S6 |
| 12717 | `UnderHammerBro` | open | M2 T17 S6 |
| 12726 | `NoUnderHammerBro` | open | M2 T17 S6 |

#### S10 closure: enemy side, jump and Hammer terrain

All nine expected nodes close: `ChkForBump_HammerBroJ`, `NoBump`,
`InvEnemyDir`, `PlayerEnemyDiff`, `EnemyLanding`, `HammerBroBGColl`,
`KillEnemyAboveBlock`, `UnderHammerBro`, and `NoUnderHammerBro`.
The shared C path preserves the original slot-five sound gate, Hammer Bro
`SetHJ` tail, low-byte subtraction borrow, landing alignment, `$23` defeat
tail, and the nonzero-tile Hammer terrain branches. Controlled original child
records match 759/759 `PlayerEnemyDiff` entries and 1/1 Hammer terrain entry.
The focused chain, landing and platform-purity CTests pass; strict C90 x86/x64
builds self-test and the OpenNT large-model DOS link produces an MZ image.
Refreshed artifact SHA-256 values are `b542801ddde07c0f840c93590bdf795f30e188e41f11e90e76ab96d7839672eb`
(DOS16), `e0941f0fdddf41aba6cb74cbb37e8254bc574ebf41be57334b5eee02d0ea33d7`
(Win32 x86), and `3fd5d4f73cb92c1e4824b46864b1182a47d80e2d1062b62607fb6dd706e20f76`
(Win32 x64). Completion moves 1,477/1,992 to 1,486/1,992.

### S11: Enemy ground query and pass-through tiles

Source lines12732-12750; entry `ChkUnderEnemy / ChkForNonSolids`; final label `NSFnd`. Shared owner: `src/game/enemy/background.c`.
3 scoped nodes; 3 expected new; 0 retained.
Logic route and dependency boundary: Exact query adder and returned metatile/flags, non-solid identities; common ground caller.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `ChkUnderEnemy`, `ChkForNonSolids`, `NSFnd`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12732 | `ChkUnderEnemy` | open | M2 T17 S6 |
| 12737 | `ChkForNonSolids` | open | M2 T17 S6 |
| 12747 | `NSFnd` | open | M2 T17 S6 |

#### S11 closure: enemy ground query and pass-through tiles

All three expected nodes close: `ChkUnderEnemy`, `ChkForNonSolids`, and
`NSFnd`. The shared C wrapper fixes the source A=`$00`, Y=`$15` bottom-middle
probe; the predicate retains the five exact CMP identities `$26`, `$c2`,
`$c3`, `$5f`, and `$60`, with its boolean value representing the original Z
branch. The old common callers now use the wrapper, while Hammer terrain keeps
its source-specific nonzero test. Controlled original child records match
549/549 query entries for returned metatile, row, address and contact nibble,
and 1,013/1,013 predicate entries for the Z result. Focused caller, terrain,
platform-purity and exact predicate CTests pass. Strict C90 Win32 x86/x64
builds self-test; the shared source list also links into an OpenNT large-model
DOS MZ image. Refreshed artifact SHA-256 values are
a `d7da920dfef2023dd93f88cf76f591706c24ea419f744ec42dbc23242449c25a`
(DOS16), `4fb1a4c22f72317164a47bf4c3548b6e8d8aca39cda0cdcda2e90c560379407f`
(Win32 x86), and `dc37ee92a9b729776a4ed4b25cbbbfd1e0f57171017ec155da5995cf3aabe4f8`
(Win32 x64). Completion moves 1,486/1,992 to 1,489/1,992.

### S12: Fireball background collision

Source lines12751-12790; entry `FireballBGCollision`; final label `InitFireballExplode`. Shared owner: `src/game/world/collision.c`.
3 scoped nodes; 3 expected new; 0 retained.
Logic route and dependency boundary: Offscreen/Y gates, ground query, bounce flag and explosion; retain source order.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `FireballBGCollision`, `ClearBounceFlag`, `InitFireballExplode`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12751 | `FireballBGCollision` | open | M2 T17 S6 |
| 12772 | `ClearBounceFlag` | open | M2 T17 S6 |
| 12777 | `InitFireballExplode` | open | M2 T17 S6 |

#### S12 closure: Fireball background collision

All three source-adjacent nodes are ROM-match complete. `FireballBGCollision`
retains the original Y gate, bottom probe, non-solid branch, bounce alignment
and explosion tail; `ClearBounceFlag` and `InitFireballExplode` retain their
respective RAM writes. Five controlled original-record cases cover blank,
solid bounce, upward explosion, existing-bounce explosion and non-solid tile
routes; the shared C checker matches every owned write in all five. It also
matches 22 retained original fireball-core child records. Focused fireball,
platform-purity and ground-query CTests pass. Strict Win32 x86/x64 builds
self-test, and DOS16 links as an MZ image. Artifact SHA-256 values are
`13dadada9e06778380526ef21ef53b9acfca39e30482788150dc8083c94644b8`
(DOS16), `c387d05f9bb89e17d894944478fbb235b2c37a6a2e17fb90a0f3256d994e1d75`
(Win32 x86), and `0b49207fbfe5ee79effdea9af7b99b4bae188261046bafd35282c7ff0850e770`
(Win32 x64). Completion moves 1,489/1,992 to 1,492/1,992.

### S13: Object bounding-box entry selection

Source lines12791-12877; entry `GetFireballBoundBox / GetEnemyBoundBox`; final label `MoveBoundBoxOffscreen`. Shared owner: `src/game/world/bounding_box.c`.
11 scoped nodes; 11 expected new; 0 retained.
Logic route and dependency boundary: Bind control data, miscellaneous/platform entries, masked offscreen computation and offscreen box writes; core is next child.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `BoundBoxCtrlData`, `GetFireballBoundBox`, `GetMiscBoundBox`, `FBallB`, `GetEnemyBoundBox`, `SmallPlatformBoundBox`, `GetMaskedOffScrBits`, `CMBits`, `LargePlatformBoundBox`, `SetupEOffsetFBBox`, `MoveBoundBoxOffscreen`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12791 | `BoundBoxCtrlData` | open | M2 T17 S6 |
| 12805 | `GetFireballBoundBox` | audited; evidence incomplete | M2 T17 S6 |
| 12813 | `GetMiscBoundBox` | open | M2 T17 S6 |
| 12819 | `FBallB` | open | M2 T17 S6 |
| 12822 | `GetEnemyBoundBox` | open | M2 T17 S6 |
| 12828 | `SmallPlatformBoundBox` | open | M2 T17 S6 |
| 12833 | `GetMaskedOffScrBits` | open | M2 T17 S6 |
| 12844 | `CMBits` | open | M2 T17 S6 |
| 12850 | `LargePlatformBoundBox` | open | M2 T17 S6 |
| 12857 | `SetupEOffsetFBBox` | open | M2 T17 S6 |
| 12866 | `MoveBoundBoxOffscreen` | open | M2 T17 S6 |


#### S13 closure: Object bounding-box entry

All eleven source-adjacent entry nodes are ROM-match complete. The shared
`GetMiscBoundBox` route now applies `CheckRightScreenBBox` for hammers as the
original does. Original entry/return records match 22 fireball calls, 16 normal
enemy calls plus six controlled screen-edge vectors, 48 misc calls, and twelve
small/large platform calls including their controlled edge vectors. These cover
the left and right masks, whole-box offscreen branch, table binding and box
writes. Focused fireball, hammer, platform-caller, terrain-chain and platform
purity CTests pass. Strict Win32 x86/x64 builds self-test, and DOS16 links as
an MZ image. Artifact SHA-256 values are
`cbb0473990551c33047dcb624528528969edada1f77cb8eb6ee5eacf21cb5a55`
(DOS16), `2f8a2699bd277eaf693500bb9bb67c8941f284aee3e16b2ef1b91f015254b279`
(Win32 x86), and `5715ebbbc6a57a11e6325c4dd5b9ec1e2fd097e0eec8dd2d7f4487e1486e1768`
(Win32 x64). Completion moves 1,492/1,992 to 1,503/1,992.

### S14: Bounding-box coordinates and edge clipping

Source lines12878-12955; entry `BoundingBoxCore`; final label `NoOfs2`. Shared owner: `src/game/world/bounding_box.c`.
7 scoped nodes; 7 expected new; 0 retained.
Logic route and dependency boundary: Original table offsets, byte additions, horizontal screen wrap and clipping; full RAM/returned-register proof.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `BoundingBoxCore`, `CheckRightScreenBBox`, `SORte`, `NoOfs`, `CheckLeftScreenBBox`, `SOLft`, `NoOfs2`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12878 | `BoundingBoxCore` | ROM-match complete | M2 T43 S14 |
| 12916 | `CheckRightScreenBBox` | ROM-match complete | M2 T43 S14 |
| 12935 | `SORte` | ROM-match complete | M2 T43 S14 |
| 12936 | `NoOfs` | ROM-match complete | M2 T43 S14 |
| 12939 | `CheckLeftScreenBBox` | ROM-match complete | M2 T43 S14 |
| 12948 | `SOLft` | ROM-match complete | M2 T43 S14 |
| 12949 | `NoOfs2` | ROM-match complete | M2 T43 S14 |


#### S14 closure: Bounding-box core and edge clipping

All seven nodes are ROM-match complete: 1,503 -> 1,510 / 1,992. One shared
`world/bounding_box.c` owner follows `BoundBoxCtrlData`, the four byte-addition
writes, `CMP`/`SBC` screen-middle decision, and the right/left clipping stores.
The original valid control domain 0 through 11 is exercised with byte-wrap
vectors. The source-only `$80-$9f` near-left no-clip interval, full left clip,
right clip, and early right-edge return are all separately tested.

Original caller records replay without a native mismatch on both widths:
16 ordinary enemy plus 6 controlled edge calls, 4 ordinary platform plus 8
controlled platform-edge calls, and 48 misc calls. Those records exercise the
shared entry/return box output; the existing fireball entry route remains a
retained S13 boundary because its available archived snapshot records do not
contain a captured bounding-box child. Focused core and clipping checks pass,
platform purity passes, strict C90 x86/x64 builds and self-tests pass, and the
shared DOS16 source links as an MZ image. No platform adapter contains box or
collision gameplay.

| Node | Original address | Disposition |
| --- | --- | --- |
| BoundingBoxCore | DC71 | Four source table-relative byte additions and box writes match. |
| CheckRightScreenBBox | DC9F | Source middle-page comparison and right-half selection match. |
| SORte | DCC7 | Right corner receives `$ff`; left is changed only when positive. |
| NoOfs | DCCD | Negative right edge returns with both horizontal coordinates retained. |
| CheckLeftScreenBBox | DCD0 | `$80-$9f` retains and `$a0-$ff` clips as in source. |
| SOLft | DCE6 | Positive right edge preserves while left becomes zero. |
| NoOfs2 | DCEC | Left-side no-clip exit preserves coordinates. |

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257709 | 0681013f83d1d02751b36655d7e75fbeb841647079b7e8476917dbf3907ce05e |
| mysmb32.exe | 362077 | 9ab8e1c671364a01061301112b17d78202cb02b8d09ba02c479e254ba60db013 |
| mysmb64.exe | 370174 | b6f96e20724f0a4d54f822b8519d4be581d7d66de18cf72a51fb4c7ee51955e1 |

### S15: Shared box collision geometry

Source lines12956-13022; entry `PlayerCollisionCore / SprObjectCollisionCore`; final label `CollisionFound`. Shared owner: `src/game/world/geometry.c`.
7 scoped nodes; 7 expected new; 0 retained.
Logic route and dependency boundary: Both entries, two-axis loop, equality/wrapping branches, carry/Y return and RAM6/7; include both terminal labels.
Operational exit: focused chain CTest, affected caller and actual-child comparisons, cross-width build, DOS16 link, purity and three artifacts.
Expected-new subset: `PlayerCollisionCore`, `SprObjectCollisionCore`, `CollisionCoreLoop`, `SecondBoxVerticalChk`, `FirstBoxGreater`, `NoCollisionFound`, `CollisionFound`.

| Line | Node | Incoming status | Current receiver |
| --- | --- | --- | --- |
| 12956 | `PlayerCollisionCore` | ROM-match complete | M2 T43 S15 |
| 12959 | `SprObjectCollisionCore` | ROM-match complete | M2 T43 S15 |
| 12964 | `CollisionCoreLoop` | ROM-match complete | M2 T43 S15 |
| 12979 | `SecondBoxVerticalChk` | ROM-match complete | M2 T43 S15 |
| 12989 | `FirstBoxGreater` | ROM-match complete | M2 T43 S15 |
| 13002 | `NoCollisionFound` | ROM-match complete | M2 T43 S15 |
| 13007 | `CollisionFound` | ROM-match complete | M2 T43 S15 |



#### S15 closure: Shared box collision geometry

All seven nodes are ROM-match complete: 1,510 -> 1,517 / 1,992. The shared
`world/geometry.c` owner preserves both original entries, the X/Y two-axis
loop, equality and byte-wrap comparison branches, and terminal carry/Y state
through RAM `$06/$07`. Callers select their own boxes and reactions; no
platform adapter contains collision policy.

The original logic track directly replays 152 captured natural collision-child
records from player-contact, enemy-pair and platform-collision NMI routes. For
each record, C receives the original pre-call 2 KiB RAM image and matches the
original post-call 2 KiB RAM image and carry result on x86 and x64. Focused
vectors separately exercise terminal paths, equality and vertical wrap.

The operational track passes focused core/world-movement checks, strict C90
builds on x86/x64, platform purity and the shared OpenNT DOS16 MZ link. Product
self-tests pass during the Win32 links. The DOS linker retains its existing
OLDNAMES warning; no DOS graphical runtime claim is made.

| Node | Original address | Disposition |
| --- | --- | --- |
| PlayerCollisionCore | DCF6 | Player-box entry initializes source scratch `$06/$07`. |
| SprObjectCollisionCore | DCF9 | Sprite-box entry retains the shared two-axis contract. |
| CollisionCoreLoop | DCFE | X/Y comparison loop and source counter progression match. |
| SecondBoxVerticalChk | DD0F | Lower-first branch and wrapped vertical test match. |
| FirstBoxGreater | DD19 | Upper-first equality/range branches match. |
| NoCollisionFound | DD26 | Clear-carry return restores source Y/scratch offset. |
| CollisionFound | DD2B | Set-carry terminal restores source Y/scratch offset. |

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257805 | 4acb78964330041c41f82d56c36bbc414fbae943f00bacc4cced2ba3ce71c5ba |
| mysmb32.exe | 362805 | a767b1f521d8dbaf4e5558725cd8218d5bc5cdceb3088bb555c9424d9f3f7d53 |
| mysmb64.exe | 370426 | 9525a53fbde41aa6a93280a8e79495035b46d15591e4b4a973f1cc6b0b3e3f22 |

## S1 admission

All31 S1 labels above are open and expected new, from PlayerBGUpperExtent
through AreaChangeTimerData. Baseline1,382, maximum1,413. Coordinator accepts
transfer-219 from M2 T17 S6. Focused test: mysmb.player-terrain-chain.
Original NMI player background route supplies the root; head/feet/sides remain
one state phase, including early exits and terminal coin/axe/impede transfers.
Metatile classifiers, block query, head-hit, climb/pipe and award children keep
their existing responsibility until their respective admissions.

First audit compares the existing split native helpers with original branch,
scratch and call order, then replaces the root in shared player/terrain.c.
The same single path serves DOS16, x86 and x64. All31 exact dispositions,
complete child inputs, data binding and separate actual-child gaps are needed
before credit. Similar-issue sweep covers duplicate head/feet/side paths,
climbing-to-falling state, returned probe scratch, terminal call handling,
masked table indexing, flag lifetimes and hidden host gameplay.

## S1 initial source audit (no completion credit)

Admission gate passes:31 scope,31 expected-new, all open, baseline1,382,
maximum1,413, accepted S1 ownership. Documentation governance also passes.
Direct owner-ROM decoding maps DC64-DE02 to192 instructions and56 conditional
branches; table bytes DC62-DC63 and DE03-DE04 are adjacent data. Coverage is
pending, not inferred from decoding. The ignored source-audit record lists
all control targets against the original symbols and marks external children.

Three verified translation differences guide the full root migration:

- Original normal or climbing Player_State (0 or3) becomes falling2 before
  the on-screen check when not swimming. The old native root handles only0.
- Original HeadChk tests returned query scratch RAM04; the old native head
  helper substitutes Player_Y_Position low nibble. Child outputs must become
  the sole source for the root's decisions.
- Original upper-extent index is PlayerSize, incremented when crouching;
  the old native helper reduces both to booleans. Bind source bytes and exact
  byte indexing instead of inventing saturation behavior.

The source also uses one live EB probe cursor and RAM00/01 foot/side scratch
across all three phases. Existing native split helpers recompute tables and
retain copied terrain structures. They require a complete ABI/write-footprint
comparison before reuse. No production fix or new conformance credit has yet
been claimed for S1. The next action is to establish exact child seams and
replace this single root/phase chain, preserving separately owned children.

## S1 structural migration checkpoint (not closure)

Six existing functions moved verbatim from player.c to player/terrain.c:
collision base, background root, head, feet, sides and side-metatile handling.
Their single production definitions are verified; function-body hashes are
recorded locally. Existing coin/climb children remain in player.c and expose
an internal terrain_children.h seam. No original-ROM semantic repair or new
node credit is claimed by this move. Build manifests include the new owner.

All119 shared files compile with strict C90 on x86/x64 and product self-tests
pass. Five affected suites pass per width: player route, friction, collision
regression, hazard and platform. The sixth, player bounding-box smoke, fails
identically against both the previous118-file object set and the new119-file
set. It remains a known pre-existing failure, not a relaxed test assertion.
An initial test link ran before x86 compilation finished; that harness run was
discarded and all twelve suite results were rerun after the build completed.

DOS compilation passes. LINK5.60 rejects the existing LLIBCE.LIB with L1104
on the new object set. Link-only retries with a larger segment table and an
identical locally staged library reproduce the error; no sibling files were
modified. DOS link is pending diagnosis. Delivered assets remain unchanged;
no P commit or three-target completion is claimed. All temporary build and
research outputs remain ignored below build/m2-t43-s1.

S1 remains active. Next: resolve the linker failure and establish exact
original child interfaces for the complete terrain chain, then migrate its
branch/call/scratch semantics and perform original-ROM proof before closure.

## S1 linker recovery and entry-state checkpoint (not closure)

The prior L1104 failure is resolved. A control link of the previous object set
against the same unchanged runtime succeeds. The123-source-object set plus
stack fails as direct inputs, but grouping the two player objects in an OMF
library succeeds. This isolates sensitivity to direct linker input count;
no claim is made about an unmeasured internal file-handle limit.

The DOS build now groups up to16 compiled objects per OMF library, leaving
main and stack explicit. All119 shared sources still compile; no source is
omitted or moved into the platform. LIB filenames avoid hyphens, which the old
librarian parses as removal operators. Grouping and linking were checked first,
then the complete checked-in build script passed end to end. Only the existing
OLDNAMES warning remains. The final MZ header file size agrees with the output;
the linker reports no unresolved symbols. Runtime inputs were read-only;
local OMF libraries stay below ignored build.

The terrain root now also performs the original state3-to2 transition on the
non-swimming path before checking high Y. Both widths pass262,144 guard/state
combinations with full RAM comparison and offscreen inputs that invoke no
children. This is native/static branch evidence only, not original execution
coverage or certification of the complete31-node chain. Original child ABI,
head/foot/side state migration and dual closure proof remain unfinished.
Assets remain the last committed delivery; this is not a new P or node credit.

## S1 foot-phase checkpoint (not closure)

The duplicated left/right landing paths now share DoFootCheck-ChkFootMTile-
LandPlyr-InitSteP order. A left coin returns before the right query. Otherwise
RAM00 receives right and RAM01 left; nonzero left selects the decision tile,
while coordinate metadata comes from the last right query. Both feet reach
the same axe branch. The invented metatile-minimum solid gate is removed;
pipe processing follows Y alignment and precedes speed/force/stomp resets.
Impede's terminal path stores MovingDir in RAM00 before invoking the child.
Existing axe and spring effects are exposed as separately owned S2/S4 child
bodies, with no proof credit for those descendants.

The new focused player-terrain-chain native test checks nine call-order and
state scenarios across both widths: early coin, right coin, either-foot axe,
both selection paths landing, last-query contact nibble, terminal impede,
spring-animation exit and hidden tiles. Test children assert ordering and
metadata, including distinct left/right coordinates. Both widths pass; this
is not original execution proof. The two changed production units compile
under strict C90. Original192-instruction/56-branch root proof remains pending.

Affected runs expose two additional existing assumptions, left unfixed in
tracked tests pending original-ROM replay: collision_regression_smoke exits38
because its isolated left axe expects left-address erasure, whereas original
ErACM consumes the last query; player_route_smoke first fails its second climb
step at line212 because state3 no longer persists through empty background.
The pre-existing bounding-box failure remains. Friction, hazard and platform
suites still pass on both widths. These failures are explicit open validation
work, not waived or counted as success. No S1 node or P is closed, and assets
remain unchanged. Next work completes the original root/child ABI and records
these exact counterexamples in the original ROM before deciding test changes.

## S1 original terrain control proof

S1 P1 closes all31 expected control/data nodes:1,382 ->1,413/1,992.
No scoped node is deferred or transferred. This certifies the terrain caller
against its original child contracts, not the still-incomplete descendant
implementations or whole-game behavior. T43 and M2 remain open.

| Node | Original entry | Evidence and disposition |
| --- | --- | --- |
| PlayerBGUpperExtent | DC62 | Bound upper-extent data uses raw byte size plus wrapped crouch increment. ROM-match complete. |
| PlayerBGCollision | DC64 | Disable, engine, swimming and vertical guards retain original order. ROM-match complete. |
| SetFallS | DC82 | Normal and climbing non-swim states select falling state2. ROM-match complete. |
| SetPSte | DC84 | Swimming stores1; falling selection stores2 before the screen guard. ROM-match complete. |
| ChkOnScr | DC86 | High-Y1 gate precedes FF collision-mask initialization and low-Y guard. ROM-match complete. |
| ExPBGCol | DC97 | Every entry early return leaves the appropriate prior writes intact. ROM-match complete. |
| ChkCollSize | DC98 | Crouch, size and swimming choose the original three adder entries. ROM-match complete. |
| GBBAdr | DCAB | Bound adder read initializes the single EB cursor shared by all phases. ROM-match complete. |
| HeadChk | DCBA | Head query, coin, rising-speed, contact-nibble, solid/water/bounce and head-child order. ROM-match complete. |
| SolidOrClimb | DCEA | Solid head contact suppresses bump sound only for metatile26. ROM-match complete. |
| NYSpd | DCF2 | Head velocity stop stores1 and continues into the feet phase. ROM-match complete. |
| DoFootCheck | DCF6 | Left coin returns before right query; otherwise both feet preserve original cursor order. ROM-match complete. |
| AwardTouchedCoin | DD1A | All three coin sites perform the classifier sound before the terminal coin child. ROM-match complete. |
| ChkFootMTile | DD1D | Left tile has priority; last right query supplies metadata; climb/speed/axe order is exact. ROM-match complete. |
| ContChk | DD2D | Hidden and spring gates precede the last-query nibble and terminal impede branch. ROM-match complete. |
| LandPlyr | DD44 | Spring child precedes Y alignment, then pipe child and vertical/stomp resets. ROM-match complete. |
| InitSteP | DD5A | Spring-active and landed paths both store normal state0 before side checks. ROM-match complete. |
| DoPlayerSideCheck | DD5E | Sides start at EB+2 and initialize RAM00 to2 without resetting the collision mask. ROM-match complete. |
| SideCheckLoop | DD66 | Upper probes store EB, preserve exclusions and run both sides in source order. ROM-match complete. |
| BHalf | DD85 | Lower probes reload the upper cursor, enforce vertical bounds and decrement RAM00. ROM-match complete. |
| ExSCH | DD9B | Side early and exhausted-loop returns retain the original scratch state. ROM-match complete. |
| CheckSideMTiles | DD9C | Hidden check precedes climb tail transfer. ROM-match complete. |
| ContSChk | DDA9 | Coin and spring checks precede ordinary wall/pipe classification. ROM-match complete. |
| ChkPBtm | DDBB | Normal state and facing-right gates precede the two pipe metatile comparisons. ROM-match complete. |
| PipeDwnS | DDCE | Zero sprite attributes alone enqueue the pipe sound. ROM-match complete. |
| PlyrPipe | DDD7 | Priority bit is ORed; aligned X skips the area timer write. ROM-match complete. |
| SetCATmr | DDEA | Screen-left page selects one of the two bound timer values. ROM-match complete. |
| ChkGERtn | DDF0 | Engine7 returns; engine8 changes to2; other engines retain their value. ROM-match complete. |
| StopPlayerMove | DDFF | Impede receives the current RAM00 physical-side counter before returning. ROM-match complete. |
| ExCSM | DE02 | Side terminal paths stop the root without another probe. ROM-match complete. |
| AreaChangeTimerData | DE03 | Both original area-timer entries are consumed by the pipe route. ROM-match complete. |

### Logic track and child boundary

The original DC64-DE02 control range has192 instructions and56 conditional
branches.1,034 controlled-input ordinary NMI routes execute all192 and109 of
112 branch outcomes. DCFC's Y>=CF and DD71/DD90's Y>=E4/D0 exits are dominated
by the root Y<CF guard for valid original object-slot inputs: head descendants
do not increase Player_Y_Position, and LandPlyr only masks its low nibble;
spring and pipe children do not change that coordinate. Those three outcomes
are audited as unreachable from this root, not reported as executed. All31
labels are accounted for, including both data consumers. Both timer entries
and the raw, wrapped upper-extent index are checked against the bound PRG.

Only RAM inputs at the naturally reached DC64 entry are controlled. ROM, PC,
registers, stack and outputs are untouched. Observer-free original frames are
identical in all1,034 cases. Metatile values0-255 are each exercised at head,
selected foot and side, followed by state, cursor, size/crouch, nibble, spring
and pipe-edge scenarios. Raw evidence occupies37,236,610 bytes, below100 MB;
process deadlines are20 seconds. Original frame/OAM/palette/audio effects here
are queued through RAM; the root does not directly write PPU/APU ports.

The caller checker compares every child input RAM byte, excluding hardware
stack return storage but retaining mapped0109-0139. Query entry kind and Y,
metatile arguments, selected coordinates, side counter and pipe inputs are
checked before installing any original child return. The passive recorder
asserts query return Y and A against the original returned scratch. Coin carry
and each consumed return are preserved. All1,034 caller results match on both
widths. Pure metatile classifications are audited against their original
four-group tables and exhaustive metatile routes; S4/S7 retain ownership of
their leaf bodies and final organization.

Separately, the real native root matches59/1,034 full RAM snapshots per width.
No difference is masked to raise that count. Independent execution of every
captured real child produces the following identical x86/x64 results. All
consumed query metadata and coin carry match; remaining differences are only
RAM00-07, and retain the named existing child owners.

| Original child | Exact RAM matches / calls per width | Remaining owner / differences |
| --- | ---: | --- |
| BlockBufferColli_Head | 0/959 | Following block-buffer slice; RAM02-05 |
| BlockBufferColli_Feet | 0/1928 | Following block-buffer slice; RAM02-05 |
| BlockBufferColli_Side | 812/2600 | Following block-buffer slice; RAM02-05 |
| CheckForCoinMTiles | 1722/1722 | Retained S7 classifier responsibility; no credit here |
| PlayerHeadCollision | 0/59 | Existing block-head/VRAM descendant maintenance; RAM00,02-07 |
| HandleCoinMetatile | 0/23 | S2 and its VRAM descendant; RAM00,02,03 |
| HandleAxeMetatile | 0/3 | S2; RAM00 |
| HandleClimbing | 159/159 | S3; no credit here |
| ChkForLandJumpSpring | 177/177 | S4; no credit here |
| HandlePipeEntry | 177/177 | S5; no credit here |
| ImpedePlayerMove | 0/242 | S6; RAM00 |

Total independent child matches are3,047/8,049 per width. This fresh evidence
is available to the planned successor chains; it does not admit or close them.
No child algorithm was rewritten to make the caller comparison pass. The
transitional query adapter exposes the source cursor and entry kind while
retaining the coordinate child's explicitly incomplete scratch/range behavior.
Coin sound moved to its actual classifier boundary; the redundant coin
forwarder was removed, leaving one existing effect implementation.

### Operational track and review

The terrain root now has one owner in game/player/terrain.c. Head, feet and
sides consume one EB cursor; root guards and collision-mask initialization
are not duplicated in fragments. The old asymmetric foot paths are replaced
by the source left-priority/last-query sequence, and side predicates retain
hidden/climb/coin/spring/state/facing/pipe order. Shared platform code is
unchanged; all game semantics remain common to all three targets.

Similar-issue sweep covered all three terrain phases, all production query
call sites, duplicate table/base selection, terminal child exits, state reset,
and direct fragment tests. The old generic coordinate helper and enemy query
remain separate existing children; they receive no new certification. The
legacy world landing helper has only a direct test caller and is not a
production terrain owner or part of this conformance claim. Direct
fragment tests explicitly supply the root's cursor/mask preconditions.

Original cases0 and3 establish the two disputed regression expectations:
an isolated left axe retains the left tile and erases the last right query's
coordinate; climbing through empty background falls to state2. Case329 also
confirms metatile1 reaches LandPlyr; the invented minimum-solid expectation
was removed. The independent horizontal-climb fixture now explicitly restores
its required state3. Assertions were changed only after those original runs.

Focused player-terrain-chain, player-route and platform-purity tests pass;
all nine retained T42 chain tests pass. The selected CTest set is12/13:
core-smoke still stops at its old entrance-loop assertion. HEAD code with T42
objects reproduces the identical assertion on both widths. The separate
bounding-box suite also retains its independently reproduced baseline failure.
Neither is waived as a pass. Five other affected suites, including collision,
player route, friction, hazard and platforms, pass on both widths.

All119 shared units compile as strict C90 on x86/x64. Both products pass
self-tests and hidden-window creation/response probes without desktop input.
DOS16 compiles and links the same shared sources using the recovered OMF
library grouping; only the existing OLDNAMES warning remains. DOS graphical
playability, resource binding and physical486SX performance are still unproved.
An intermediate checker link overlapped object rebuilding and failed; that run
was discarded. Final comparisons use the completed object sets and pass both
widths. All temporary material stays below ignored build/m2-t43-s1.

Reproduce the original routes using t43-player-terrain cases0-1033 with
player-terrain-snapshot, entrance-children and pc-coverage. Compare using
player_terrain_snapshot_check (caller), enemy_loop_actual_check (actual root)
and player_terrain_children_check (independent actual children). Native CTest
is mysmb.player-terrain-chain. The owner-authorized three EXEs are refreshed;
no ROM, generated source, raw snapshot or research artifact is committed.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257063 | 39b332ca740e54520a6454ece92e9fa1aea68367d84d7509eb0859137105209d |
| mysmb32.exe | 357781 | 43dd675a2db2632d5c09e3f8da773559f44a98b3084510d5d186c011aa0bbfd8 |
| mysmb64.exe | 365660 | 80da88d761dcfd28e1ee342e2f1b1cbfc0a35210385c36ba65dca2f8a6bbd043 |

## S2 admission

Continuation after7825a0b. Scope and expected-new set are the same three open
nodes: HandleCoinMetatile, HandleAxeMetatile, ErACM. Baseline1,413/1,992;
maximum1,416. Coordinator accepts transfer-220 from M2 T17 S6. Source DE05-DE24
forms two entries sharing the erase tail, followed by GiveOneCoin or the
RemoveCoin_Axe tail. Move the sole owner to player/terrain_metatiles.c, removing
the old objects/player bodies. Preserve complete pointer high/low/row, byte
coin-tally wrap, mode/task/speed stores and original call order.

The S1 original captures supply the incoming actual-child baseline. Fresh
ordinary NMI terrain routes will record the two entries and their immediate
children, compare complete child inputs before any replay, and run the actual
native descendants separately. No child algorithms are admitted for rewrite;
VRAM/status scratch gaps retain their existing owners. Focused native test:
mysmb.terrain-metatile-chain. Repeat S1 caller proof and affected collision/route
tests, compile all shared sources on both Windows widths, link DOS16, check
platform purity and deliver all three owner-authorized EXEs in the P.

Owner-local ROM and reviewed listing remain nonredistributable inputs. This
S permits512 controlled routes,50 MB raw records,20-second process deadlines,
and ignored build/m2-t43-s2 containment; coordinator owns cleanup after dependent
regression use. No emulator enters the product. Similar-issue sweep covers
both erasure paths, hard-coded pointer high bytes and duplicate coin/axe owners.

S2 admission gate validates3 unique scoped labels,3 expected matches, all open;
1,413 incoming and1,416 maximum. Ledger registration and accepted custody pass.

## S2 coin and axe proof

S2 P1 closes the three expected nodes: 1,413 -> 1,416 / 1,992.
No scoped node is deferred or transferred. This certifies these handlers
against their original child contracts; real descendant mismatches below
remain open with existing owners. T43 and M2 remain incomplete.

| Node | ROM entry | Disposition and logic |
| --- | --- | --- |
| HandleCoinMetatile | DE05 | ROM-match complete. Erase child returns before wrapped CoinTallyFor1Ups increment and terminal GiveOneCoin. |
| HandleAxeMetatile | DE0E | ROM-match complete. Zero OperMode_Task, set OperMode to2 and Player_X_Speed to18, then enter common erase tail. |
| ErACM | DE1C | ROM-match complete. Zero the full RAM06/07 pointer plus RAM02 row, then tail-transfer to RemoveCoin_Axe. |

### Original logic track

The DE05-DE24 range decodes from the owner ROM to13 instructions, with no
conditional branches. All13 execute in128 controlled ordinary NMI routes.
ROM, CPU registers, PC, stack and outputs are untouched. RAM inputs are set
only at naturally reached terrain/coin/axe entries. The cases vary pointer
high byte4-6, low byte, row and page carry, tally wrap, area type, coin count,
current player and life count. Observer-free and observed original frame
outputs are identical in all128 cases. Raw evidence is1,313,152 bytes within
the admitted50 MB budget; each process has a20-second deadline.

The caller checker validates every immediate child's input RAM and the
low/row arguments before installing its original return. RAM comparison
excludes hardware stack storage while retaining mapped0109-0139. Both widths
match128/128 caller results. The same native chain with real children matches
16/128 full RAM results per width. These counts are separate; descendant
outputs are not masked to improve the actual-native result.

Independent native execution of the192 captured children per width confirms:

| Child | Exact RAM matches / calls | Remaining differences and owner |
| --- | ---: | --- |
| RemoveCoin_Axe | 32/128 | RAM00 for nonzero AreaType; existing M2 T28 S3 VRAM maintenance |
| GiveOneCoin | 0/64 | RAM02/03 and, in56 calls, RAM00; existing score/status descendant owners |

The independently observed child gaps explain the actual root differences.
No VRAM or score child algorithm is changed by S2. All consumed child returns
and call order are checked at the root contract; neither child consumes its
entry CPU A/X/Y before defining the registers it uses. Effects in this range
are RAM writes and queued VRAM/status work, with no direct PPU/APU port write.

Reproduce with reference_frame_recorder options fixture=t43-coin-axe cases0-127,
terrain-metatile-snapshot, entrance-children and pc-coverage; compare using
terrain_metatile_snapshot_check in caller, actual and independent-child modes.
The recorder's child-file final range check initially rejected the new mode75;
extending that observer-only guard and rerunning the entire matrix resolved
it. An earlier option-prefix length typo was corrected before the accepted
runs. No failed capture is used as proof.

### Operational track and review

One shared owner, game/player/terrain_metatiles.c, replaces the legacy
objects/player bodies and the redundant axe wrapper. Both handlers use the
same erase tail. The old hard-coded0500 pointer base and invented range gate
are removed; all production callers supply original query RAM pointers.
CMake and the DOS manifest compile the same120 shared units. Platform files
are unchanged, and platform-purity passes.

The similar-issue sweep checks both erasures, every production coin/axe call,
full pointer carry, tally ordering/wrap and duplicate owners. The focused
native test passes6,144 cases on each width, including a child that changes
the tally toFF before return, proving the increment occurs after that return.
Direct core-test fixtures now supply the original pointer preconditions.

The retained S1 caller matrix remains1,034/1,034 per width; actual-root matches
remain59/1,034, with no loss of previously matching cases. Collision regression,
player route, friction, hazard and platform suites pass on x86/x64. The
bounding-box baseline failure remains unchanged. Selected CTests pass4/5:
coin/axe chain, terrain chain, player route and platform purity pass; core-smoke
retains its entrance-loop failure. Both HEAD and current source reproduce
line137 on each width, before the changed coin fixtures. Neither baseline
failure is counted as a pass.

Strict C90 builds and product self-tests pass on x86/x64. Hidden own-process
window probes confirm creation and message responsiveness without desktop
input. DOS16 compiles and links; only the existing OLDNAMES warning remains.
DOS graphics, resource binding and physical486SX performance remain unproved.
Owner-authorized three EXEs are refreshed; no ROM, generated resource source,
raw record or temporary research output enters the commit.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257015 | 0f6cf557302e17c7bfbd5859f4046460dd431d71db59725bd7f0bb08361d4b46 |
| mysmb32.exe | 358007 | d93a053bc60cf112b52967cb6c5d1c79dc1091e4f5051a280cc58c660379623c |
| mysmb64.exe | 365922 | d5cf6d7f53dab58e28f49f18a5045bf1a078b7754a01b22f80275f9af1434354 |

## S3 admission

Continuation after60162e3 under the continuing M2 mandate. Transfer-221 accepts
the14 exact open nodes in the S3 source-order table above from M2 T17 S6.
Scope and expected-new sets are identical; baseline1,416/1,992, maximum1,430.
DE25-DE2D contains three bound tables; DE2E-DEBC is HandleClimbing through
ExPVne. One shared player/climbing.c owner replaces the legacy player body.

The S1 terrain caller is the predecessor; hidden/jumpspring S4 is next.
Preserve every contact/metatile/engine gate, flagpole score, sound, state and
byte/page adjustment. Remove the duplicated KillEnemies loop and expose its
existing area owner without changing that child's algorithm. Independently
compare child inputs and actual outputs; no descendant credit or hidden gap.

Original-ROM proof uses controlled RAM inputs at naturally reached climbing
entries, all source branches and all three table consumers. Preserve CPU,
ROM, stack and outputs. Allow1,024 bounded routes,50 MB raw output and20-second
process deadlines below ignored build/m2-t43-s3; coordinator owns cleanup after
regression use. Owner-local ROM/listing are nonredistributable research inputs.

Operational proof uses mysmb.climbing-chain, retained S1 actual climbing and
root routes, affected collision/player tests, strict C90 x86/x64 builds,
DOS16 link, platform purity and three owner-authorized EXEs per P. Similar-issue
sweep covers duplicated kill loops, invented metatile guards, raw facing/table
indices, byte wrap and page adjustment. No platform gameplay is admitted.

## S3 climbing proof

S3 P1 completes all14 expected climbing nodes. Incoming1,416 plus14 new
matches minus one invalidated historical KillEnemies claim gives1,429/1,992.
No S3 node is deferred or transferred. This corrects the maximum1,430 forecast
by an independently demonstrated out-of-scope baseline defect; it does not
conceal a missed S3 node. T43's original1,518 global forecast consequently
becomes1,517 unless that maintenance defect is separately repaired and proved.
T43 and M2 remain incomplete.

Admission gate validated14 unique open labels,14 expected matches and accepted
transfer-221; the exact scoped set is the S3 table above. Both verification
tracks and final node dispositions follow.

| Node | Original address | Logic and disposition |
| --- | --- | --- |
| ClimbXPosAdder | DE25 | Bound X adders use the original absolute address plus raw facing byte. ROM-match complete. |
| ClimbPLocAdder | DE27 | Bound page adders retain the independent wrapped page sum. ROM-match complete. |
| FlagpoleYPosData | DE29 | All original table bytes bind; score reads indices4 through1 and falls to default0. ROM-match complete. |
| HandleClimbing | DE2E | Contact scratch below6 or at least10 returns before any state mutation. ROM-match complete. |
| ExHC | DE38 | Both contact rejection paths preserve RAM. ROM-match complete. |
| ChkForFlagpole | DE39 | Metatiles24 and25 select flagpole; all other admitted values follow VineCollision. ROM-match complete. |
| FlagpoleCollision | DE41 | Engine5 skips flag setup; facing and scroll lock precede engine4 gate and KillEnemies33. ROM-match complete. |
| ChkFlagpoleYPosLoop | DE68 | Descending Y threshold comparisons preserve both compare and decrement exits. ROM-match complete. |
| MtchF | DE70 | Store the selected score only after flag setup and threshold scan. ROM-match complete. |
| RunFR | DE73 | Store engine4 and transfer directly to common positioning. ROM-match complete. |
| VineCollision | DE7A | Only metatile26 above the status threshold selects automatic climbing. ROM-match complete. |
| PutPlayerOnVine | DE88 | Set climbing state, zero horizontal speed/force, then compare wrapped relative X. ROM-match complete. |
| SetVXPl | DEA1 | Raw facing selects X table; page updates only when the original block low byte is zero. ROM-match complete. |
| ExPVne | DEBC | Both page-update and nonzero-block returns end the same positioning chain. ROM-match complete. |

### Original logic track

DE2E-DEBC decodes to71 instructions and12 conditional branches. All71 and all24
branch directions execute in1,024 controlled ordinary NMI routes. The three
adjacent DE25-DE2D tables bind to the original PRG; raw facing-byte reads use
the original absolute-indexed addresses. The flagpole score loop consumes
indices4 through1; reaching0 exits without reading the table's first entry.
That byte is bound and audited, not falsely reported as an executed read.

Only RAM inputs at naturally reached terrain and climbing entries are
controlled. CPU registers, ROM, PC, stack and outputs are unchanged. Fixtures
cover all256 contact bytes, all256 facing bytes, all256 block-low bytes,
engine gates, score thresholds, relative-X edge, scroll-lock wrap, page wrap
and matching/nonmatching enemy slots including untouched slot5. Observed and
observer-free original frames match in all1,024 final cases. After the source
constant review,64 cases were rerecorded to add matching cannon-enemy IDs;
unchanged cases retain identical inputs. Accepted raw records total4,472,960
bytes, under50 MB; every process has a20-second deadline.

The native caller check validates KillEnemies' input A and complete RAM before
installing the original return. Hardware-stack storage is excluded, while
mapped0109-0139 is retained. Both widths match1,024/1,024 caller results.
With real native children,960/1,024 full RAM results match. The64 paths that
invoke KillEnemies differ only at RAM00; independent child execution confirms
that same one-byte difference in all64 calls per width. No difference is masked.
The child defines its own X/Y and the caller immediately reloads A/X after
return, so no CPU-register return is consumed by this chain.

**Historical claim corrected:** original KillEnemies at9716 begins by storing
its incoming A in RAM00. The existing area helper omits that write. Original
captures have33; the independently executed child retains02. KillEnemies is
therefore changed from ROM-match complete to mapped, with current maintenance
receiver M2 T29 S8 retained. Its algorithm is not rewritten in S3. KillELoop
and NoKillE retain their separate earlier proofs; the discovered missing store
belongs to the entry node. The historical T29 record remains immutable, and
this current audit supersedes its aggregate claim for that node.

Reproduce with reference_frame_recorder fixture=t43-climbing cases0-1023,
climbing-snapshot, entrance-children and pc-coverage; compare using
climbing_snapshot_check in caller, actual and independent-child modes.

### Operational track and review

The sole shared player/climbing.c owner replaces the legacy player body.
The duplicated ascending enemy-kill loop is removed in favor of the existing
descending area child. Its visibility changes, but its body is unchanged.
Source review and original captures correct the old cannon-enemy ID12 to33.
The invented non-26 rejection is removed: the original alternate branch
continues to PutPlayerOnVine. Raw facing indices replace boolean normalization,
and bound PRG supplies the three original data tables. No platform file changes.

The similar-issue sweep checks every production climbing/kill call, duplicate
loops, metatile exclusions, score loop order, source constants, index width and
byte/page arithmetic. The area-warp caller remains unchanged. The focused
native test passes515 scenarios per width, including entry no-write guards,
engine4/5 skips, child-before-score ordering and synthetic bound-table indexing.

S1 retains all1,034 caller matches and the exact same59 actual-root matches
per width. All159 captured real climbing-child calls still match per width.
Collision regression, player route, friction, hazard and platform suites pass
on both widths. Bounding-box retains its baseline failure. Selected CTests
pass5/6: climbing, terrain-metatile, terrain, player route and platform purity;
core-smoke still fails the pre-existing entrance loop. HEAD and current code
both reproduce line137 on both widths. These failures are not reported as passes.

All121 shared units compile as strict C90 on x86/x64; product self-tests and
hidden own-window creation/message probes pass. DOS16 compiles and links the
same shared sources with the existing OLDNAMES warning. DOS graphical runtime,
resource binding and physical486SX performance remain unproved. The three
owner-authorized EXEs are refreshed. No ROM, generated resource source, raw
capture or temporary research output is committed.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257063 | a10925a41b4e94e92162902389eff2d69e7e84544577ae3c442bc9a70643f60d |
| mysmb32.exe | 358232 | 66792dbce565297c6bdb6b7bcea067cbaf70077869a9527d0ce95291ed6955aa |
| mysmb64.exe | 366185 | 4191e42e90f3a79e71cdc5be29bf009459b4f7679669fe364f561ca66a68baca |

## S4 admission

Continuation after34fa4e9. Transfer-222 accepts all seven open S4 labels from
M2 T17 S6. Scope and expected-new sets are exactly ChkInvisibleMTiles, ExCInvT,
ChkForLandJumpSpring, ExCJSp, ChkJumpspringMetatiles, JSFnd and NoJSFnd.
Baseline1,429/1,992, maximum1,436. DEBD-DEE7 has the two predicates and landing
activation; player/terrain_metatiles.c is the sole shared owner. Climbing S3
precedes this group; pipe-entry S5 follows. Terrain callers consume invisible Z
and spring C; activation invokes the spring predicate before its four stores.

Replace inline terrain predicates with named source helpers and move the
unchanged activation body from player.c. No generic fireball/background helper
or unrelated node is admitted. Source audit covers every caller and consumed
flag; ROM proof records the naturally reached helper entries and returns from
512 ordinary NMI foot/side metatile routes. Do not modify CPU, PC, stack, ROM or
outputs. Owner-local inputs stay nonredistributable. Keep raw records below
ignored build/m2-t43-s4,50 MB,20-second process deadlines; coordinator owns
cleanup after regression use.

Native operational proof uses mysmb.hidden-spring-chain, retained terrain and
177 original landing-child calls per width, affected collision/player tests,
strict C90 x86/x64, DOS16 link, purity and three owner-authorized EXEs per P.
The similar-issue sweep distinguishes the source leaf predicates from generic
legacy fireball exclusions and checks both spring identities, no-write exits,
field widths, duplicate activation bodies and actual callers. No platform
business logic or descendant rewrite is admitted.

## S4 hidden and spring proof

S4 P1 completes all seven expected nodes:1,429 ->1,436/1,992. No scoped node
is deferred or transferred. This group has direct actual-native proof, with
no original child-return substitution. Other previously recorded whole-game
and descendant gaps remain open; T43 and M2 are incomplete.

Admission validated seven unique open labels, seven expected matches and
accepted transfer-222. The source-order set and individual dispositions are:

| Node | Original address | Logic and disposition |
| --- | --- | --- |
| ChkInvisibleMTiles | DEBD | Compare hidden coin5F first, then hidden1-up60; expose the original consumed Z. ROM-match complete. |
| ExCInvT | DEC3 | Both comparison exits preserve the input metatile and all RAM. ROM-match complete. |
| ChkForLandJumpSpring | DEC4 | Invoke spring predicate before writing force70, spring forceF9, timer3 and animation1. ROM-match complete. |
| ExCJSp | DEDC | Non-spring return performs no writes; spring return follows the four original stores. ROM-match complete. |
| ChkJumpspringMetatiles | DEDD | Compare top67 then bottom68; return the original C without changing input or RAM. ROM-match complete. |
| JSFnd | DEE6 | Either matched spring metatile sets the consumed carry result. ROM-match complete. |
| NoJSFnd | DEE7 | All other metatiles return cleared carry; both paths preserve RAM. ROM-match complete. |

### Original logic track

DEBD-DEE7 contains22 instructions and four conditional branches. All22 and all
eight branch directions execute in512 ordinary NMI routes: the existing player
terrain fixture cases328-839 exhaust256 foot and256 side tile inputs. RAM is
controlled only at the naturally reached terrain root. No original ROM, CPU
register, PC, stack or output is changed. Observer-free and observed frames
are identical in all512 cases. Primary raw records total4,281,382 bytes below
the50 MB budget; each process has a20-second deadline.

The recorder observes actual child inputs and returns. Invisible returns
must preserve A and expose Z; spring predicates must preserve A and expose C.
All source callers are audited: two invisible BEQ consumers, one side spring
BCC consumer and the landing activation's spring BCC consumer. Other CPU flags
are not consumed across these calls. Native Boolean results represent those
specific original flags; no emulated CPU state enters the product.

Both widths independently execute each real C entry from original input RAM,
comparing consumed flags and complete RAM except hardware return-stack storage,
while retaining mapped0109-0139. There is no child replay or difference mask.

| Entry | Calls per width | Distinct original input tiles | Exact results |
| --- | ---: | ---: | ---: |
| ChkInvisibleMTiles | 348 | 255 | 348/348 |
| ChkForLandJumpSpring | 91 | 91 | 91/91 |
| ChkJumpspringMetatiles, direct side calls | 92 | 92 | 92/92 |

The nested spring predicate also executes in all91 landing calls; its branches
are included in PC coverage, while landing's actual full-RAM result proves the
composed activation. The direct-entry total is531/531 per width. Empty tile0
is skipped by the original terrain caller before the invisible helper; its
simple comparison semantics are source-audited and covered by the exhaustive
native predicate test, not misreported as original execution.

Reproduce using reference_frame_recorder with fixture=t43-player-terrain
cases328-839, hidden-spring-snapshot, entrance-children and pc-coverage.
hidden_spring_snapshot_check validates every captured real entry and original
return flag. The recorder also asserts preserved A before writing each pure
predicate record.

### Operational track and review

One owner, game/player/terrain_metatiles.c, now contains the two predicates
and spring landing activation. The activation body leaves player.c, and the
two invisible caller sites plus the side spring site call the source-named
helpers. Landing calls the same spring helper before its four stores. No
separate algorithm or platform-specific gameplay is introduced.

The similar-issue sweep checks all original predicate callers, both spring
identities, consumed flags, no-write exits and duplicate activation stores.
The legacy fireball coordinate collision helper has its own generic exclusion
list and does not represent either source leaf; its algorithm is unchanged
and receives no S4 credit. Isolated terrain-root tests retain explicit pure
predicate contracts; the actual leaf proof above is independently executed.

Native tests exhaust all256 predicate inputs and1,024 full-RAM initial-state
cases per width. All pass. S1 retains all1,034 caller results and the exact same
59 actual-root matches per width; all177 retained original landing-child calls
also match. Collision regression, player route, friction, hazard and platform
suites pass on both widths. Bounding-box retains its known baseline failure.
Selected CTests pass6/7, including the new hidden-spring test and the three
prior chain tests, player route and purity. Core-smoke still fails the existing
entrance loop; HEAD and current source reproduce line137 on both widths.
Neither old failure is counted as a pass.

All121 shared units compile as strict C90 on x86/x64; product self-tests and
hidden own-window creation/message probes pass. DOS16 compiles and links with
the existing OLDNAMES warning. DOS graphical runtime, resource binding and
physical486SX performance remain unproved. All three owner-authorized EXEs are
refreshed; no ROM, generated resource source, raw capture or temporary research
artifact is committed. Platform files remain unchanged.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257175 | cf1f1e127c5de7a06342a970d48012ae67f18652c010ec55029c07058dedf81c |
| mysmb32.exe | 358371 | 795153c55053fc18d29fc0563de094010b4332328c86d7951569e00a59f5ad24 |
| mysmb64.exe | 366834 | 9c5710ad69cca93ef57a9c2efd97e17fb536df47f033e71377a9d2603f93541b |

## S5 admission

Continuation after2a1988e. Transfer-223 accepts HandlePipeEntry, GetWNum and
ExPipeE from M2 T17 S6. All three are open and expected new:1,436/1,992,
maximum1,439. DEE8-DF4A is one shared player/pipe_entry.c owner. S4 hidden/spring
precedes it; S6 impediment follows. External data tables retain their existing
owners; this chain must read their bound PRG addresses without inventing limits.

Source audit identifies three existing gaps: missing WorldAddrOffsets and
AreaAddrOffsets lookup/store, zero instead of Silence80, and a12-byte local
warp table indexed beyond its extent for some source control values. Preserve
down/right/left gate order, timer/sound/priority writes, raw warp selectors,
X thresholds60/A0, byte-decremented world number, area pointer before resets,
entry resets and byte-wrapped hidden/timer increments. No extra area-loader
call or AreaType side effect is permitted. No child algorithm is rewritten.

Original proof uses512 controlled RAM input routes at naturally reached pipe
entry inside ordinary NMI terrain calls, with no ROM/CPU/PC/stack/output patch.
Owner-local ROM/listing remain nonredistributable. All raw material stays below
ignored build/m2-t43-s5,50 MB,20-second process deadlines; coordinator owns
cleanup after dependent regression use. Compare actual full RAM on both widths,
with branch/store and three table-read audit; no child replay is needed.

Operational proof: mysmb.pipe-entry-chain, retained177 original pipe-child
calls, terrain caller/actual baselines, affected tests, strict C90 x86/x64,
DOS16 link, purity and three owner-authorized EXEs. Resource-free warp tests
must explicitly supply synthetic bound PRG rather than rely on incomplete
hard-coded production tables. Similar-issue sweep covers all pipe callers,
lookup bounds, silence, reset order, byte wrap and duplicate legacy bodies.

## S5 pipe entry proof

S5 P1 completes HandlePipeEntry, GetWNum and ExPipeE:1,436 ->1,439/1,992.
All three expected nodes have direct actual-native proof; none is deferred
or transferred. Other M2 gaps, including KillEnemies and the legacy runtime
failures, remain open. Admission validated the three exact open labels,
maximum1,439 and accepted transfer-223.

| Node | Original address | Logic and disposition |
| --- | --- | --- |
| HandlePipeEntry | DEE8 | Down/right/left gates precede timer, mode, sound and priority; nonzero warp then selects the original raw table index. ROM-match complete. |
| GetWNum | DF22 | Read warp number, decrement the world byte, read world and area offsets, store destination then silence and entry resets; increment both flags with byte wrap. ROM-match complete. |
| ExPipeE | DF4A | All rejected and non-warp exits preserve their proper write footprint; warp exit follows the complete lookup/reset chain. ROM-match complete. |

### Original logic track

DEE8-DF4A has46 instructions and six conditional branches. All46 and all12
branch directions execute in512 controlled ordinary NMI routes. Only RAM at
naturally reached terrain/pipe entries is controlled; original CPU, ROM, PC,
stack and outputs are untouched. Observed and observer-free original frames
match in all512 cases. Primary raw records total2,101,248 bytes below50 MB;
process deadlines are20 seconds.

The routes exercise down/right/left failures, non-warp entry, every possible
warp-control byte, both60/A0 X boundaries, raw table indices including12-14,
nonzero high-bit selectors whose low bits are zero, priority replacement,
entry-field reset and hidden/timer byte wrap. All512 actual native full-RAM
results match on each width, excluding hardware return-stack storage while
retaining mapped0109-0139. There are no external child calls, original-return
substitutions or masked game-state differences in this chain.

Source reads bind WarpZoneNumbers at87F2, WorldAddrOffsets at9CB4 and
AreaAddrOffsets at9CBC. The world byte is decremented before indexing; the
area lookup uses the original world offset alone, before AreaNumber is reset.
Raw indices can select neighboring original data, as the ROM does. The table
nodes keep their existing owners and receive no duplicate credit here. The
terrain caller discards the native acceptance Boolean and overwrites CPU
register results in the original sequence; RAM is the consumed output contract.

Reproduce with reference_frame_recorder fixture=t43-pipe-entry cases0-511,
pipe-entry-snapshot and pc-coverage, then pipe_entry_snapshot_check using the
bound original PRG and the real linked game objects.

### Operational track and review

Shared player/pipe_entry.c replaces the legacy player body. The repair restores
both destination lookups and AreaPointer store, replaces the wrong zero music
queue with Silence80, and removes the out-of-bounds12-entry local warp array.
It preserves right-foot before left-foot guards, source store order, raw byte
indices and wraps. No area-loader child is invented, so AreaType is unchanged.
The reader consumes bound program data; no partial copied production table
substitutes for it. Resource-free tests explicitly bind synthetic data.

The similar-issue sweep checks all pipe callers, raw indexing, table binding,
silence, pointer/reset order, both byte increments and duplicate owners. The
production terrain caller remains the sole caller and supplies the original
RAM01/RAM00 foot values. Platform files are unchanged. The mode regression
fixture now supplies explicit synthetic warp/world/area bytes and checks the
destination pointer and silence, retaining its original world/mode/timer checks.

Native tests pass1,044 full-RAM cases per width, including all directional
bytes, failed tile combinations, position thresholds, adjacent-table indices
and a synthetic zero warp byte that must decrement toFF. S1 retains all1,034
caller results and the exact same59 actual-root matches per width. All177
previously captured pipe-child calls still match. Mode, collision regression,
player route, friction, hazard and platform suites pass on both widths.
Bounding-box retains its baseline failure. Selected CTests pass8/9: all five
T43 chains, mode, player route and purity pass; core-smoke retains the existing
entrance-loop failure. HEAD and current source reproduce line137 on both
widths. Neither legacy failure is reported as a pass.

All122 shared units compile as strict C90 on x86/x64; product self-tests and
hidden own-window creation/message probes pass. DOS16 compiles and links with
the existing OLDNAMES warning. DOS graphical runtime, resource binding and
physical486SX performance remain unproved. All three owner-authorized EXEs
are refreshed; no ROM, generated resource source, raw capture or temporary
research output is committed.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257355 | ecc41e0f31f3589ec6ffa8bf9feaaa062b26b326ab7706298dc40663fd4f556d |
| mysmb32.exe | 359106 | 7fd005aefc8de86181614c4573e5738670a66307c5668eb87d17e311d6b82911 |
| mysmb64.exe | 367084 | 329c0a5192bdd024c5e3c2e110883e7133105917a079b5a3690f6d30d6ad0755 |

## S6 admission

Continuation afterb9bfd6e. Transfer-224 accepts the five open labels
ImpedePlayerMove, RImpd, NXSpd, PlatF and ExIPM from M2 T17 S6.
All five are expected new:1,439/1,992, maximum1,444. One player/impede.c owner
replaces the legacy body. S5 pipe entry precedes it; S7 classifiers follow.
Terrain and platform callers keep their owners and receive regression checks.

Preserve side1 versus every other source byte, CPY result sign (especially
right-side speed80), timer/speed stores, RAM00 high adder, low-byte carry into
page and collision-mask write on every exit. Existing code omits RAM00, treats
80 as a rightward correction and rejects non1/2 sides. No parent algorithm
rewrite or guessed threshold is admitted.

Original proof controls RAM only at a naturally reached ImpedePlayerMove
inside ordinary NMI terrain flow. Budget1,024 routes,50 MB and20-second process
deadlines below ignored build/m2-t43-s6; no CPU/ROM/PC/stack/output patch.
Owner-local ROM/listing are nonredistributable. Coordinator owns cleanup after
regression use. Compare actual full RAM and audit all source branches/stores.

Operational proof uses mysmb.impede-chain, exhaustive native speed/side and
page-edge cases, retained242 original terrain impede calls, terrain and
platform caller regressions, strict C90 x86/x64, DOS16 link, purity and three
owner-authorized EXEs. Similar-issue sweep covers every impede caller, scratch
handoff, signed byte comparisons, carry/page wrap and duplicate owners.

## S6 impede proof

S6 P1 completes all five expected nodes: 1,439 -> 1,444 / 1,992.
No scoped node is deferred or transferred. Transfer-224 is accepted;
other M2 discrepancies retain their existing receivers. This is one source
chain and one delivery, with individual node evidence below.

| Node | Original address | Logic and disposition |
| --- | --- | --- |
| ImpedePlayerMove | DF4B | Read speed and the caller RAM00 side; only side1 selects the left branch, whose negative-speed exit clears the collision bit without position stores. ROM-match complete. |
| RImpd | DF5E | All other side bytes select mask02; BPL tests the byte result of speed minus one, so speed80 exits without correction. ROM-match complete. |
| NXSpd | DF66 | On correction, store timer10 then speed00; derive the signed high adder without changing skipped-path scratch. ROM-match complete. |
| PlatF | DF74 | Store the high adder to RAM00; add correction to X with cleared carry, then add high byte and carry to page, with byte wrap. ROM-match complete. |
| ExIPM | DF81 | Invert side mask and AND/store collision bits on every path, then return. ROM-match complete. |

### Original logic track

The chain spans DF4B-DF8A: 33 instructions and four conditional branches.
All instructions and all eight branch directions execute in 1,024 controlled
ordinary NMI routes. Fixture t43-impede uses the existing terrain case681 to
reach the original entry. Only RAM inputs are controlled; original ROM, CPU,
PC, hardware stack and computed outputs are untouched. Observed and
observer-free original frames match in all 1,024 cases. Raw primary snapshots
total 4,202,496 bytes below the 50 MB budget; process deadlines are 20 seconds.

Cases0-511 cover both physical sides with all 256 speed bytes. Cases512-767
cover every possible side byte with boundary speeds; cases768-1023 cover all
X bytes under correction. Page00/FF, both X edges, collision masks and dirty
timer/scratch values are included. Both native widths match all 1,024 actual
original results across every one of the 2,048 RAM bytes, including the stack.
No child-output substitution or state mask is used. There are no child calls,
external data tables, CIRAM/palette/OAM-register/PPU/audio accesses in this
leaf; its write footprint is exactly RAM00,0057,006D,0086,0490,0785.

Reproduce using reference_frame_recorder with fixture=t43-impede cases0-1023,
impede-snapshot and pc-coverage; compare with impede_snapshot_check linked to
the actual shared owner. The original return registers are not consumed by
the admitted terrain/platform callers; their RAM handoff is verified below.

### Operational track and review

Shared player/impede.c replaces the old player.c body. The repair restores the
RAM00 high-adder store, the CPY speed80 boundary and the original non1 side
branch. Low-byte carry and page wrap follow the original two additions.
There is one owner for DOS16, Win32 x86 and x64; no host adapter was changed.

The similar-issue sweep covers every production caller: four terrain call
sites and one platform-response call. Each supplies the source RAM00 value,
including the foot path's explicit MovingDir copy. Side scratch, signed-byte
comparisons, timer/speed order, carry/page edges and mask-only exits were
reviewed. No unrelated parent implementation or duplicate impede body remains.

Native tests pass 262,144 full-RAM cases per width, covering all side/speed
pairs at four page/X boundaries. All 242 independently captured original
terrain impede calls now match all 2,048 RAM bytes on both widths. S1 retains
all 1,034 caller matches and the same 59 actual-root matches per width.
The platform matrix retains all 784 caller and 14 actual-root matches per
width. Against HEAD, the remaining platform actual differences at RAM00,
0057,0086,0785 are eliminated; only the existing RAM06/07 child discrepancies
remain. These unresolved parent results are not claimed as complete gameplay.

Mode, collision, player route, friction, hazard and platform suites pass on
both widths. Bounding-box retains its recorded failure. Selected CTests pass
9/10: the six T43 chains, mode, player route and purity pass; core-smoke still
fails at source line137 on both HEAD and current, on both widths. Both legacy
failures remain explicit. No broader equivalence is inferred from these tests.

All 123 shared units compile under strict C90 on x86/x64. Product self-tests
and hidden own-window creation/message probes pass. DOS16 compiles and links
with the existing OLDNAMES warning. DOS graphical runtime, resource binding
and physical 486SX performance remain unproved. The owner-authorized three
EXEs are refreshed; no ROM, generated data, raw traces or research output is
committed.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257307 | b61a7f6cb1cb828e0f4bde9e7a39439b63c404b6a75873365b882ece9a862cea |
| mysmb32.exe | 359322 | 23db30f3998571eda5be64c11e180aee58f61288e0773ce908f824d31d16a860 |
| mysmb64.exe | 367336 | 7eeefaa17b728ce01a8f4890f51803e4cc80eb42c41c6d29db5c8d797b846eb8 |

## S7 admission

Continuation after e0e816c. Transfers225/226 receive SolidMTileUpperExt,
CheckForSolidMTiles, ClimbMTileUpperExt, CheckForClimbMTiles,
CheckForCoinMTiles, CoinSd, GetMTileAttrib and ExEBG. The first seven are open
and expected new; ExEBG is retained complete. Baseline 1,444/1,992, maximum
1,451. Scope8/expected7; one common world/metatiles.c owner replaces the
scattered classifier bodies and the head caller's duplicate solid table.
S6 impediment precedes it; S8 enemy terrain dispatch follows.

Logic proof binds the two four-byte original threshold tables, metatile group
extraction, comparison carry, unchanged metatile inputs and coin sound write.
The existing terrain caller uses carry and preserves the metatile argument;
no CPU interpreter or platform game logic is introduced. Parent algorithms
retain their owners; only the classifier call boundary changes.

Use the retained 1,034 ordinary NMI terrain fixtures with passive classifier
entry/return capture. Only existing RAM fixture inputs are controlled; no
CPU/register, ROM, PC, stack or output patch. Explicitly audit inputs excluded
by the original parent gates rather than forcing an unreachable call. Capture
full RAM and consumed return flags; separately run real native descendants.
Owner-local ROM/listing are nonredistributable. Budget1,034 routes/100 MB,
20-second process deadlines and ignored build/m2-t43-s7 containment;
coordinator owns cleanup after regression use.

Operational proof: mysmb.metatile-classification-chain, every byte against
all classifier predicates and table groups, retained terrain caller/actual
baselines, affected native tests, strict C90 x86/x64, DOS16 link, platform
purity and three owner-authorized EXEs. Review all classifier callers,
duplicate threshold owners, table binding, group index and coin sound writes.

## S7 metatile classification proof

S7 P1 completes all seven expected nodes and retains ExEBG: 1,444 ->
1,451 / 1,992. All eight scoped dispositions are recorded below. No member
is deferred or transferred at closure; other M2 gaps retain their receivers.
Admission passed scope8/expected7, maximum1,451 with transfers225/226.

| Node | Original address | Logic and disposition |
| --- | --- | --- |
| SolidMTileUpperExt | DF8B | All four threshold bytes bind original DF8B through DF8E and are selected by the metatile high-bit group. ROM-match complete. |
| CheckForSolidMTiles | DF8F | Call the common group extractor, compare the unchanged metatile against the selected solid threshold, return comparison carry without RAM writes. ROM-match complete. |
| ClimbMTileUpperExt | DF96 | All four threshold bytes bind original DF96 through DF99 and retain group order. ROM-match complete. |
| CheckForClimbMTiles | DF9A | Call the common group extractor, compare the unchanged metatile against the climb threshold and return carry without RAM writes. ROM-match complete. |
| CheckForCoinMTiles | DFA1 | Compare C2 then C3; either match takes CoinSd, otherwise clear carry and preserve RAM. ROM-match complete. |
| CoinSd | DFAB | Load coin sound01 and store RAMFE; successful comparison carry remains set. ROM-match complete. |
| GetMTileAttrib | DFB0 | Preserve the metatile while extracting bits7-6 to group0-3; equivalent to the original ASL/ROL/ROL sequence. ROM-match complete. |
| ExEBG | DFB8 | Retained common RTS; the classifier register/RAM contract and existing enemy return ownership are preserved. Retained ROM-match complete. |

### Original logic track

The classifier code has 23 instructions and two conditional branches; all
instructions and all four branch directions execute. Both four-byte tables
are read in all groups. The existing 1,034 ordinary NMI terrain routes are
reused with a passive observer at DF8F, DF9A, DFA1 and DFB0. Entry/return
records use the real stack-derived return PC and depth, including the nested
GetMTileAttrib call. No CPU/register, ROM, PC, stack or output is modified.
Observed and observer-free original frames match in every route.

The routes contain 5,050 captured classifier calls; every call matches
on each native width. Raw records total 20,773,872 bytes, below the
100 MB bound; each process has a 20-second deadline.

| Entry | Captured calls per width | Input bytes absent from these original routes |
| --- | ---: | --- |
| DF8F | 257 | 00, C2, C3 |
| DF9A | 1407 | 00 |
| DFA1 | 1722 | None |
| DFB0 | 1664 | 00 |

Original parent gates determine the absent inputs; zero metatiles bypass
solid/climb checks, and head coins are consumed before the solid call.
The exhaustive native byte tests separately cover the complete predicate
domains. No unreachable original call is forced to inflate coverage.

Comparisons use the actual native predicate carry and group extractor. They
also check original A/X/Y preservation and the N/Z/C contract against the
source operation; native callers retain arguments rather than storing CPU
registers. Full RAM is compared except exactly the two hardware return-address
bytes written by JSR GetMTileAttrib in solid/climb records. Coin and direct
attribute records compare all 2,048 RAM bytes. No child result is replayed.
Only CoinSd writes game RAM (FE); there are no PPU/CIRAM/palette/OAM-register
or audio-register accesses in this chain. The sound queue store is compared.

Reproduce with reference_frame_recorder fixture=t43-player-terrain cases0-1033,
metatile-calls and pc-coverage, then metatile_classification_snapshot_check
bound to the owner-local original PRG. Retained terrain caller comparisons
remain separately distinguished from real native descendant execution.

### Operational track and review

One world/metatiles.c owns the solid/climb tables, group extractor and coin
predicate. The old player.c coin body, world/collision.c climb body and
player/terrain.c solid table are removed. Classifier call boundaries now use
the shared owner; parent branch order and side effects are unchanged.
The native Boolean returns carry, not a replacement collision policy.

The same owner serves DOS16 and Win32 x86/x64. Bound games read original
threshold addresses; the existing resource-free threshold values are retained
only at this common owner and verified against the original eight bytes.
Synthetic rebound tables prove the native classifiers actually read their
binding. No new copied resource corpus or runtime emulator is introduced.

The similar-issue sweep covers all three terrain climb sites, the head solid
site, the legacy landing seam and all four terrain coin sites. Group extraction,
threshold duplicates, table binding, unchanged argument/RAM and coin sound
writes have explicit dispositions in the table above. The legacy landing
parent remains unmodified apart from passing game to its classifier and gains
no conformance credit. Platform files are unchanged and purity passes.

Each width passes 768 native cases: all 256 bytes with resource-free tables,
original-value bound tables and synthetic bound tables. S1 retains all 1,034
caller matches and the same 59 actual-root matches per width. Mode, collision,
player route, friction, hazard and platform tests pass on both widths.
Bounding-box retains its baseline failure. Selected CTests pass10/11; the
seven T43 chains, mode, player route and purity pass. Core-smoke still fails
at source line137 in HEAD and current on both widths. Both legacy failures
and the unmatched full terrain descendants remain explicit.

All 124 shared units compile as strict C90 on both Win32 widths. Self-tests
and hidden own-window creation/message probes pass. DOS16 compiles and links
with the existing OLDNAMES warning; DOS graphical runtime, resource binding
and physical 486SX performance remain unproved. Three owner-authorized EXEs
are refreshed. ROM, generated resource sources and raw records remain local.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257595 | a2d61b604734325d41ae89cf0b2962c82010d45c4065cb75d1dabe58f6f9b909 |
| mysmb32.exe | 360230 | a4de9eae32fb3e7fed9223e019b6dcaa6043e5737a0ac63169325941d5d10e73 |
| mysmb64.exe | 368276 | 32de22538b8973df01002bbd40527913e782dcd0af479e1944bf9032a5aeac91 |

## S8 admission

Continuation after b02ae38. Transfers227/228 accept18 scoped nodes:
EnemyBGCStateData, EnemyBGCXSpdData, EnemyToBGCollisionDet, DoIDCheckBGColl,
HBChk, CInvu, YesIn, NoEToBGCollision, HandleEToBGCollision, GiveOEPoints,
ChkToStunEnemies, Demote, SetStun, SetWYSpd, SetNotW, ChkBBill, NoCDirF,
ExEBGChk. Retained complete: EnemyToBGCollisionDet, DoIDCheckBGColl, HBChk,
CInvu, YesIn, ExEBGChk. All other12 are open and expected new.
Admission baseline1,451/1,992; scope18/expected12, maximum1,463.

One enemy/background.c owner covers the admitted dispatch, block-hit and
stun chain, preserving original child boundaries. S7 classifiers precedes
this chain; S9 landing/grounded-state, S10 side/jump/hammer and S11 queries
remain separate. Their implementations may be exposed as child seams without
certifying or repairing their internal algorithms here. Table ownership moves
with its actual consumer binding; table proof cannot certify later consumers.

Source audit already identifies wrong Demote input (Enemy_ID instead of A),
missing PlayerEnemyDiff RAM00 store, and duplicate block-hit stun logic with
missing Bloober/bullet distinctions. Restore the admitted original stores,
branches and order, including both vertical decrements and the source sound/
score/defeat child calls. Eliminate duplicate admitted logic rather than add
another parallel path. SetupFloateyNumber returns Enemy_Rel_XPos as A; verify
that handoff before demotion. Unmatched query/landing/side child effects stay
explicit and retain their own source-order responsibility.

Original proof uses retained entry/collision matrices plus bounded ordinary
NMI routes reaching enemy terrain/block-hit/stun entries. Only RAM inputs may
be controlled at a naturally reached entry; no CPU/register, ROM, PC, stack
or computed-output patch. Compare complete child inputs and consumed returns,
and separately execute actual native descendants. Bound both state/speed
tables to original program data; verify consumer routes and all branches.
Owner-local ROM/listing are nonredistributable. Maximum2,048 new routes,
100 MB raw records,20-second process deadlines, ignored build/m2-t43-s8
containment and coordinator cleanup after active regressions.

Operational proof uses mysmb.enemy-background-stun-chain, exhaustive native
source-A/demotion and movement-edge tests, existing enemy-background dispatch,
fireball-hit/player-contact caller and actual regressions, strict C90 x86/x64,
DOS16 link, platform purity and three owner-authorized EXEs. Review every
stun/block-hit caller, scratch handoff, duplicate implementation, table index,
child-call order and slot/return semantics. No platform gameplay changes.

## S8 enemy terrain dispatch and stun proof

S8 closes its twelve expected nodes and retains six dispatch nodes:
1,451 -> 1,463 / 1,992. Landing, jump/hammer, and ground-query child interiors
remain open with S9, S10, and S11; this closure credits only the admitted
parent/data/stun chain.

| Node | Original address | Disposition |
| --- | --- | --- |
| EnemyBGCStateData | DFB9 | Six original state bytes bind through the shared owner. ROM-match complete. |
| EnemyBGCXSpdData | DFBF | Both original direction-speed bytes bind through the shared owner. ROM-match complete. |
| NoEToBGCollision | DFF7 | Zero-query route hands off to the existing grounded-state seam. ROM-match complete. |
| HandleEToBGCollision | DFFA | Non-solid, landing, and $23 block-hit dispatch order matches. ROM-match complete. |
| GiveOEPoints | E016 | Score one enters the float-number child and consumes its returned relative X. ROM-match complete. |
| ChkToStunEnemies | E01B | Original A range and exclusions select demotion. ROM-match complete. |
| Demote | E02B | Source A bit zero reaches Enemy_ID; Enemy_ID is not substituted. ROM-match complete. |
| SetStun | E02F | State low nibble two and two Y decrements match. ROM-match complete. |
| SetWYSpd | E048 | Bloober/water and ordinary speed paths match. ROM-match complete. |
| SetNotW | E04A | Player difference, direction and speed-table selection match. ROM-match complete. |
| ChkBBill | E054 | Only IDs $33 and $08 retain moving direction. ROM-match complete. |
| NoCDirF | E060 | Direction minus one selects the original two-byte speed table. ROM-match complete. |

The logic track records 1,642 source-reachable ordinary NMI routes from the
2,048 bounded fixture inputs; 406 inputs are excluded because their original
parent does not reach the entry. Observed and observer-free frames are equal in
all 1,642 records. The source interval has 79 instructions and 23 conditional
branches; every reachable instruction and both outcomes of each reachable
conditional branch execute. Replayed child entries, input RAM and return RAM
give 1,642 / 1,642 caller matches on x86 and x64. The real descendant run
matches 1,090 / 1,642 routes; the remaining 552 differences are inside the
separately owned S9/S10/S11 child interiors. Direct admitted stun execution
separately matches 98,304 full-RAM native cases per width and 322 retained
original fireball/contact calls.

One shared `game/enemy/background.c` owner now holds data readers, block-hit
parent, demotion and stun. `objects.c` exposes unchanged later-owned landing,
no-ground and kill-above-block seams; `jump_terrain.c` holds the unchanged jump
child body. No platform adapter receives a gameplay branch. Strict C90 product
builds contain 125 shared units on x86 and x64; self-tests and own-window
message probes pass. DOS16 links the identical core. Focused chain, dispatch,
player-route and platform-purity CTests pass. The known core source-line-137
failure reproduces in baseline and current builds and is not waived. DOS
graphical runtime, ROM-resource binding and physical 486SX performance remain
unproved.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257517 | 73a6024f442ad4bab49f5854eeb7fc488e90f52d6515a41c35028ee610bc2e46 |
| mysmb32.exe | 360834 | 889061d782ee2b4793ed64efd4bb8de4eaec3d5e29d5479eb0d7315b70b1cc1a |
| mysmb64.exe | 368892 | 42eb8f8abb6d3e0c848536f60aa7d051d46d915665b04214fd2ec2294c7c61ab |

## S9 admission

Continuation after S8 closure. Transfer229 accepts all fourteen open landing
nodes listed in the S9 source-order table: LandEnemyProperly through SetD6Ste.
Baseline1,463/1,992; scope14/expected14, maximum1,477. `LandEnemyProperly`
is the entry and `SetD6Ste` the exit. S8 is its predecessor; S10 side/jump/
hammer and S11 ground query remain successors. The shared owner is
`game/enemy/background.c`; existing object seams may move unchanged but no
successor algorithm is credited or repaired here.

The logic track will use at most2,048 source-reachable ordinary NMI routes,
controlled only through RAM fixtures at natural landing entries. It compares
state-table reads, nibble gates, state/direction writes and child call order;
parent and real child results remain separate. The operational track will run
the focused landing chain, retained S8 paths, strict x86/x64 C90 builds, DOS16
link, platform purity and refreshed three artifacts. Raw records remain below
ignored build/m2-t43-s9 with100MB and20-second process bounds.

## S9 enemy landing and grounded state proof

S9 closes all fourteen admitted nodes:1,463 ->1,477 /1,992. The shared
`game/enemy/background.c` owner follows the original nibble gate, state-table
read, red-koopa edge, spiny `$12` identity, timer writes, direction decision
and falling-bit clearing order. It delegates side collision, bump and physical
landing to S10-owned seams and credits none of those child interiors.

The original-ROM matrix injects only at natural `DoEnemyToBGCollisionDet`
entries. 1,024 bounded inputs yielded 2,144 root/child stack records. Observer
and observer-free ROM frame outputs are byte-identical. Captured
`LandEnemyProperly` and `ChkForRedKoopa` entries give 2,048 /2,048 matching
`Enemy_State` outcomes in each x64 and x86 replay. Focused landing-chain,
retained caller and platform-purity tests pass. Raw captures and replay reports
remain ignored below `build/m2-t43-s9`.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257517 | 73a6024f442ad4bab49f5854eeb7fc488e90f52d6515a41c35028ee610bc2e46 |
| mysmb32.exe | 360956 | 8e49f54efe8605b2489642728c30f4e877fb9a63e41baa1696d47cbb51375c7c |
| mysmb64.exe | 369012 | 27de764688fa6963b2abfb9a39b47628100a9bc25d1475a3c529c99404eeb289 |
