# M2 T61: Cohort H blocks, items and miscellaneous actors current-equivalence proof

T61 continues the approved source-order proof program immediately after closed
T60. It audits the 129 labels from `VineObjectHandler` through `ExVMove`.
Historical ROM-match accounting remains **1,992 / 1,992**. This task records
fresh current shared-C equivalence evidence only.

## Task contract

T61 closes only after each scoped label and each feasible relation owned by an
admitted chain is current-exact. Each chain performs its ROM mapping, required
shared-C repair, original-ROM/current x86/x64 comparison, focused operational
proof, platform-purity check, and shared DOS16 link. Product-source repairs
also refresh all three local executable artifacts. A feasible difference stays
in its owning S until repaired and re-audited on the same route.

The task begins at the deferred `VineHeightData -> VineObjectHandler` material
boundary from T60. It does not claim unadmitted collision, relative-position,
OAM, enemy-loop or dispatcher child semantics; those relations receive an
explicit boundary disposition in the owning chain.

## Planned source-order S chains

| S | Entry to exit | Labels | Shared C owner and route family |
| --- | --- | ---: | --- |
| S1 | `VineObjectHandler -> ExitVH` | 6 | `src/game/vine.c` plus named shared world/OAM children; vine growth, draw, erase and metatile-write routes. |
| S2 | `CannonBitmasks -> KillBB` | 14 | shared cannon/Bullet Bill game chain; scheduler, spawn, movement and retirement routes. |
| S3 | `HammerEnemyOfsData -> RunHSubs` | 10 | shared hammer game chain; spawning, speed/position, collision and draw routes. |
| S4 | `CoinBlock -> MiscLoopBack` | 12 | shared coin/misc game chain; allocation, jump-coin and descending misc-loop routes. |
| S5 | `CoinTallyOffsets -> NoZSup` | 9 | shared score/status game chain; tally, score and status-number routes. |
| S6 | `SetupPowerUp -> ExitPUp` | 10 | shared power-up game chain; initialization, emergence, collision and draw handoffs. |
| S7 | `BlockYPosAdderData -> SpawnBrickChunks` | 28 | shared player-head/block game chain; bump, metatile, item and shatter routes. |
| S8 | `BlockObjectsCore -> NextBUpd` | 8 | shared block lifetime and update chain; gravity, movement, draw and replacement routes. |
| S9 | `MoveEnemyHorizontally -> ExXMove` | 6 | shared horizontal-motion primitive; carry/page and caller-return routes. |
| S10 | `MovePlayerVertically -> ExVMove` | 26 | shared vertical/gravity primitives; player, enemy and platform routes. |

The exact 129-label task scope is the concatenation of these source-order
chains. All labels are `needs-evidence` at admission except `AddToScore`, which
is already current-exact and is retained only as S5's required in-chain
handoff. The current baseline is **690 / 1,992 exact nodes** and **1,376 /
4,324 exact feasible control relations**; T61 can reach at most 818 exact
nodes if its 128 pending labels pass both tracks.

## S1 admission - vine actor lifecycle

S1 admits the contiguous six-label chain `VineObjectHandler -> ExitVH`:
`VineObjectHandler`, `RunVSubs`, `VDrawLoop`, `KillVine`, `WrCMTile`, and
`ExitVH`. Its predecessor is T60 S8's exact setup chain. The shared owner is
`src/game/vine.c`; it calls existing shared relative/offscreen, OAM,
block-buffer and enemy-lifecycle primitives at their original boundaries.
Platform adapters remain pixel consumers and cannot add any vine rule.

**ROM-logic track.** Controlled original-ROM/current x86/x64 routes cover the
frame-bit growth gate, relative/offscreen handoff, six-sprite drawing loop,
wrapped horizontal retirement, terminal metatile write, and all six returns.
The comparison records branch predicates, RAM reads/writes, `VineHeightData`
binding, child call order and owner-boundary inputs/outputs.

**Operational track.** Run the focused vine actor route on x86/x64, compare
width records, run platform purity, and link the shared DOS16 target. A
shared-game repair refreshes `assets/mysmb16.exe`, `assets/mysmb32.exe`, and
`assets/mysmb64.exe`; an audit-only result does not.

S1 has six labels in scope and six intended current-exact labels. Historical
expected-match credit remains zero because the historic ledger is already
1,992 / 1,992. Its current maximum is **696 / 1,992 exact nodes**. Any feasible
node or edge difference remains in S1 until the same ROM and native route
passes; only then can S2 start.

## S1 closure - vine actor lifecycle

All six scoped labels are current-exact. Static comparison of `$B94B-$B9B9` with `src/game/vine.c` found no feasible difference in the slot-five gate, height-table selection, frame-bit growth, height-eight gate, child call order, zero-based draw loop, reverse erase loop, height reset, block probe or terminal return. The shared ROM route records all ten branch sites with both outcomes. The same 42 original snapshots give 84 caller checks and 84 complete current-source calls at zero difference across x86/x64; focused 2,560-case smoke, platform purity and the OpenNT DOS16 link pass.

The closure promotes the six labels, 15 internal feasible control relations and the deferred `VineHeightData -> VineObjectHandler` material consumer boundary. No product source changed, so executable artifacts were not refreshed. Current re-audit advances from **690 / 1,992** to **696 / 1,992 exact nodes** and from **1,376 / 4,324** to **1,391 / 4,324 exact feasible control relations**; historical accounting remains **1,992 / 1,992**.

## S2 admission - cannon and Bullet Bill lifecycle

S2 admits the 14-label, source-contiguous `CannonBitmasks -> KillBB` chain:
`CannonBitmasks`, `ProcessCannons`, `ThreeSChk`, `FireCannon`, `Chk_BB`,
`Next3Slt`, `ExCannon`, `BulletBillXSpdData`, `BulletBillHandler`, `SetupBB`,
`ChkDSte`, `BBFly`, `RunBBSubs`, and `KillBB`. The shared owner is
`src/game/cannon.c`; the source window is `$B9BA-$BA56`. Its external
boundaries are only the established offscreen, movement, relative-position,
bounding-box, collision, graphics, and erase primitives.

**ROM-logic track.** Compare the water-area exit, slot-two-to-zero scheduler,
random mask selection, timer decrement/spawn carry behavior, Bullet Bill
orientation and proximity kill, timer-control movement gate, defeated descent,
and final child-call order. Check each table binding and every internal feasible
control relation; do not claim unadmitted child semantics.

**Operational track.** Build focused original-ROM/current x86/x64 route cases
for every branch and state handoff, then run platform-purity and the standard
DOS16 link. Any source repair refreshes all three local EXEs; an audit-only
result does not. This S starts at **696 / 1,992 current-exact nodes** and
**1,391 / 4,324 current-exact feasible control edges**; historical accounting
remains **1,992 / 1,992**.

## S2 closure - cannon and Bullet Bill lifecycle

All 14 scoped labels are current-exact. Static comparison of `$B9BA-$BA56` with `src/game/cannon.c` found no feasible difference in the water gate, slot-two-to-zero scheduler, hard-mode mask, expired-timer spawn, carry-preserving proximity check, movement gate, defeated descent, common child order, or erase return. The two table consumer bindings and all 26 internal feasible control relations agree with the source route.

Twenty-five controlled original-ROM routes replayed as 50 current x86/x64 runs. Each compares 1,782 persistent RAM bytes and complete frame output; all match, and both native widths are byte-identical. The focused cannon smoke, dispatcher static contract, platform-purity audit, and OpenNT DOS16 link pass. No product source changed, so executable artifacts were not refreshed. Current re-audit advances to **710 / 1,992 exact nodes** and **1,417 / 4,324 exact feasible control relations**; historical accounting remains **1,992 / 1,992**.

## S3 admission - hammer actor lifecycle

S3 admits the ten-label `HammerEnemyOfsData -> RunHSubs` chain:
`HammerEnemyOfsData`, `HammerXSpdData`, `SpawnHammerObj`, `SetMOfs`,
`NoHammer`, `ProcHammerObj`, `SetHSpd`, `SetHPos`, `RunAllH`, and `RunHSubs`.
The owner is `src/game/hammer.c`, for original source `$BA88-$BB09`.

**ROM-logic track.** Verify pseudo-random hammer-slot selection, enemy-slot
exclusion, carry return contract, state transition, gravity/horizontal-move
order, HammerXSpdData direction selection, spawn coordinates and common
collision/offscreen/relative/bounding-box/draw sequence. Child internals remain
outside S3 while their inputs, outputs and ordering are recorded.

**Operational track.** Compare controlled original-ROM/current x86/x64 hammer
routes, run focused smoke and platform-purity checks, and link DOS16. A source
repair refreshes all three local EXEs. Baseline: historical **1,992 / 1,992**;
current **710 / 1,992 exact nodes** and **1,417 / 4,324 exact feasible control
relations**.

## S3 closure - hammer actor lifecycle

All ten scoped hammer labels are current-exact. Static comparison of `$BA88-$BB09` with `src/game/hammer.c` found no feasible difference in random slot selection, enemy-slot exclusion, carry return, state transition, gravity/movement order, direction-indexed speed, coordinate/page carry, or common tail order. The two material bindings and 12 internal feasible control relations agree.

Sixty-three original hammer snapshots replay as 126 x86/x64 caller routes with zero differences; focused hammer smoke executes 9,984 cases per width with zero errors. The complete-current replay identifies an external dependency gap only: cases 27–44 differ after `RunHSubs -> GetMiscBoundBox` in `$04d0-$04f2`; `GetMiscBoundBox` and control-01241 remain `needs-evidence` with receiver **M2 T43 S13**. This is not credited by S3 and blocks no statement about that child. No product source changed, so executable artifacts were not refreshed. Current re-audit advances to **720 / 1,992 exact nodes** and **1,429 / 4,324 exact feasible control relations**; historical accounting remains **1,992 / 1,992**.

## S4 admission — coin and misc lifecycle

S4 admits the contiguous original chain `$BB38-$BBF7`, `CoinBlock -> MiscLoopBack`: `CoinBlock`, `SetupJumpCoin`, `JCoinC`, `FindEmptyMiscSlot`, `FMiscLoop`, `UseMiscS`, `MiscObjectsCore`, `MiscLoop`, `ProcJumpCoin`, `JCoinRun`, `RunJCSubs`, and `MiscLoopBack`. All twelve are currently `needs-evidence`; S4 therefore has twelve unique scoped labels and twelve current-exact candidates, while the historical migration forecast remains zero new `ROM-match complete` names (**1,992 / 1,992** baseline and maximum).

The shared owners are `src/game/coin.c` and `src/game/misc.c`. S3 is the predecessor; S5 score/tally handling is the next source-order dependency. The chain hands off after `RunJCSubs` to named world/OAM children only; their semantics remain external. ROM-logic evidence will compare normal and jump-coin setup, allocation carry/fallback, d7 dispatch, slot-loop state changes, gravity argument construction, page carry, retirement and child order on controlled original-ROM/current x86/x64 routes. Operational evidence is a focused chain harness, cross-width comparison, platform-purity check and DOS16 shared-core link. A source repair refreshes all three local executable artifacts.

## S4 closure — coin and misc lifecycle

All twelve scoped labels are current-exact: `CoinBlock`, `SetupJumpCoin`, `JCoinC`, `FindEmptyMiscSlot`, `FMiscLoop`, `UseMiscS`, `MiscObjectsCore`, `MiscLoop`, `ProcJumpCoin`, `JCoinRun`, `RunJCSubs`, and `MiscLoopBack`. The static `$BB38-$BBF7` comparison found no feasible difference in SBC and four-ASL carry propagation, descending slot search and fallback, state initialization, ObjectOffset write-before-read, high-bit dispatch, gravity argument construction, reload, speed-five transition, scroll page carry, state-`$30` retirement, or the descending loop. Nineteen internal feasible control relations are exact.

Forty-eight original coin-creation and forty-two original misc-lifetime routes replayed on current x86/x64 callers for 180 passing checks. The complete-current product build also passed all 180 routes. Focused smoke completed 16,400 coin cases and 13,825 misc cases per architecture with zero errors. Boundaries to `GiveOneCoin`, hammer processing, gravity, relative position, offscreen, bounding box and graphics retain their existing receiving tasks; their child semantics are not credited by S4. No product source changed, so executable artifacts were not refreshed. Current re-audit advances to **732 / 1,992 exact nodes** and **1,448 / 4,324 exact feasible control relations**; historical accounting remains **1,992 / 1,992**.

## S5 admission — score, coin tally and status-number chain

S5 admits `$BBF8-$BC48`, `CoinTallyOffsets -> NoZSup`: `CoinTallyOffsets`, `ScoreOffsets`, `StatusBarNybbles`, `GiveOneCoin`, `CoinPoints`, `AddToScore`, `GetSBNybbles`, `UpdateNumber`, and `NoZSup`. The first five table/caller labels and final three status labels are `needs-evidence`; `AddToScore` is already exact and must be revalidated as this chain's handoff. Thus the current-exact forecast is eight candidates from **732 / 1,992** to **740 / 1,992**; historical accounting remains **1,992 / 1,992**.

The shared owner is `src/game/score.c`. S4 is its predecessor and S6 power-up is successor. ROM logic compares both table indices, coin increment and 100-coin branch, life/sound writes, CoinPoints modifier, score/status tail, status-print order, zero suppression and returned ObjectOffset. Digit-math and status-print internals are named external child boundaries. Operational proof uses original controlled caller routes plus current x86/x64 caller/full-product checks, focused smoke, platform purity and DOS16 link. A source repair refreshes all three local executables.

## S5 closure — score, coin tally and status-number chain

All nine scoped labels are current-exact; eight newly promoted and `AddToScore` revalidated. Static `$BBF8-$BC48` comparison found no feasible difference in table selection, current-player reads, threshold/life/sound branch, digit modifiers, child order, VRAM indexing, zero suppression or ObjectOffset return. Seven internal controls are exact. Original caller and full current routes each passed 112 x86/x64 checks; focused smoke passed 2,560 cases per architecture. Digit math and status-print child internals remain external. No source changed. Current: **740 / 1,992** nodes and **1,455 / 4,324** feasible controls; historical **1,992 / 1,992**.


## S6 admission — power-up initialization and lifecycle chain

S6 admits the contiguous original chain `$BC49-$BCEA`, `SetupPowerUp -> ExitPUp`: `SetupPowerUp`, `PwrUpJmp`, `StrType`, `PutBehind`, `PowerUpObjHandler`, `ShroomM`, `GrowThePowerUp`, `ChkPUSte`, `RunPUSubs`, and `ExitPUp`. All ten labels are `needs-evidence`; this is ten unique scoped labels and ten current-exact candidates. The current-equivalence forecast is **740 / 1,992** to **750 / 1,992** nodes, while historical accounting remains **1,992 / 1,992**.

The shared owners are `src/game/power_up_init.c` and `src/game/power_up.c`. S5 is the predecessor; S7 block/head processing is the source-order successor. ROM logic compares fixed-slot state, flag, page/X/Y initialization, type derivation, attributes and sound writes; inactive/emergence/active dispatch; mushroom and star movement branches; flower emergence; the state-six collision/draw threshold; and the exact `RunPUSubs` child order. Existing movement, collision, relative-position, offscreen, bounding-box and OAM children remain named external boundaries. Operational proof uses controlled original-ROM/current x86/x64 callers and full-product routes, a focused power-up chain harness, platform-purity and DOS16 shared-core link. A product-source repair refreshes all three local executables.


## S6 closure - power-up initialization and lifecycle chain

All ten scoped labels are current-exact: `SetupPowerUp`, `PwrUpJmp`, `StrType`, `PutBehind`, `PowerUpObjHandler`, `ShroomM`, `GrowThePowerUp`, `ChkPUSte`, `RunPUSubs`, and `ExitPUp`. Static `$BC49-$BCEA` comparison found no feasible owned difference in fixed-slot initialization, byte subtraction, player-status type reduction, priority/sound tail, high-bit active test, timer/type dispatch, emergence state progression, state-six threshold, or child order. Nineteen internal controls and the two fixed-slot material handoffs are exact.

Fresh current x86/x64 checks pass 72 initialization snapshots, 100 actor caller routes and 100 complete-current actor routes. Focused initialization smoke runs 71,680 cases and actor smoke runs 10,240 cases per architecture with zero failure. Platform purity and the OpenNT DOS16 link pass. Movement, terrain, relative-position, offscreen, bounding-box, OAM and player-collision children remain external boundaries. No product source changed. Current: **750 / 1,992** nodes and **1,474 / 4,324** feasible controls; historical **1,992 / 1,992**.


## S7 admission - player-head block and brick-shatter chain

S7 admits the contiguous original `$BCEB-$BE6F` chain `BlockYPosAdderData -> SpawnBrickChunks`: `BlockYPosAdderData`, `PlayerHeadCollision`, `DBlockSte`, `ChkBrick`, `StartBTmr`, `ContBTmr`, `PutOldMT`, `PutMTileB`, `SmallBP`, `BigBP`, `Unbreak`, `InvOBit`, `InitBlock_XY_Pos`, `BumpBlock`, `BlockCode`, `MushFlowerBlock`, `StarBlock`, `ExtraLifeMushBlock`, `VineBlock`, `ExitBlockChk`, `BrickQBlockMetatiles`, `BlockBumpedChk`, `BumpChkLoop`, `MatchBump`, `BrickShatter`, `CheckTopOfBlock`, `TopEx`, and `SpawnBrickChunks`. All 28 labels are `needs-evidence`, giving 28 current-exact candidates: **750 / 1,992** to **778 / 1,992**. Historical accounting remains **1,992 / 1,992**.

The shared owners are `src/game/blocks/head.c`, `src/game/blocks/bump.c`, and `src/game/blocks/chunks.c`. S6 is the predecessor; S8 block-lifetime is the successor. S7 owns 55 feasible internal controls, one explicitly infeasible raw fallthrough (`BlockCode -> MushFlowerBlock`), and four internal material handoffs. ROM logic compares slot selection, scratch block-buffer addressing, player-size/crouch selection, carry-derived block match, coin timer, block coordinate carry, metatile writes, dispatch selectors, coin/vine/power-up handoffs, overhead coin probe, brick replacement, chunk initialization, and ordered child calls. Area, score, coin, power-up, vine and audio children remain named external boundaries. Operational proof uses original-ROM/current x86/x64 callers and full-product routes, focused head/block smoke, platform purity and the DOS16 shared-core link. A shared-game repair refreshes all three local executables.


## S7 closure - player-head block and brick-shatter chain

All 28 scoped labels are current-exact. Static `$BCEB-$BE6F` comparison found no feasible difference in scratch block-buffer access, player-size/crouch selection, carry, coin timer, coordinate/page writes, content dispatch, lookup order, overhead coin path, replacement, chunk initialization or child order. Fifty-five internal feasible controls and four material handoffs are exact; `BlockCode -> MushFlowerBlock` remains the already-proven infeasible raw fallthrough. Fresh x86/x64 routes pass 296 caller and 296 full-current checks. Focused head, bump and chunk smokes pass; platform purity and DOS16 link pass. No source changed. Current: **778 / 1,992** nodes and **1,529 / 4,324** feasible controls; historical **1,992 / 1,992**.


## S8 admission - block lifetime and metatile-update chain

S8 admits `$BE70-$BEDD`, `BlockObjectsCore -> NextBUpd`: `BlockObjectsCore`, `ChkTop`, `BouncingBlockHandler`, `KillBlock`, `UpdSte`, `BlockObjMT_Updater`, `UpdateLoop`, and `NextBUpd`. All eight are `needs-evidence`, yielding eight candidates from **778 / 1,992** to **786 / 1,992**. It owns 16 feasible internal controls. Shared owners are `src/game/blocks/lifetime.c` and `replacement.c`; S7 precedes it and S9 motion follows. ROM logic compares state masking, bounce phase, gravity/motion handoffs, two-slot update loop, metatile replacement and retirement. Platform adapters remain out of scope.


## S8 closure - block lifetime and metatile-update chain

All eight scoped labels are current-exact: `BlockObjectsCore`, `ChkTop`, `BouncingBlockHandler`, `KillBlock`, `UpdSte`, `BlockObjMT_Updater`, `UpdateLoop`, and `NextBUpd`. Static `$BE70-$BF01` comparison found no feasible difference in saved low-nibble state, child offsets, paired chunk movement, carry-preserved retirement, bounce replacement, scratch block-buffer pointer write, busy-buffer gating, or signed two-slot loop order. Sixteen internal feasible controls are exact.

Fresh x86 and x64 controlled original-ROM routes pass 64 caller comparisons and 64 complete-current comparisons per width with zero differences. Focused lifetime and replacement C90 tests pass 131,090 and 131,072 cases per width. Platform purity passes; the OpenNT DOS16 link succeeds with its known OLDNAMES warning. The registry reconciliation also added the already-recorded T61 S7 operational evidence to 55 H controls and four H material handoffs, allowing its exact records to pass the registry integrity gate. No product source changed, so local executable artifacts were not refreshed. Historical migration is **1,992 / 1,992**; current exact progress is **786 / 1,992 nodes** and **1,545 / 4,324 feasible controls** from **4,342 raw controls** with **18 infeasible**.


## S9 admission - horizontal movement primitive chain

S9 admits `$BF00-$BF4C`, `MoveEnemyHorizontally -> ExXMove`: `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `SaveXSpd`, `UseAdder`, and `ExXMove`. All six are `needs-evidence`, so the current-exact forecast is **786 / 1,992** to **792 / 1,992** nodes; historical migration accounting remains **1,992 / 1,992**. It owns nine internal feasible control relations, including the shared routine return to the enemy wrapper. The shared owner is `src/game/world/movement.c`, with the player wrapper in `src/game/player.c`; S8 precedes it and S10 vertical/gravity follows.

ROM logic evidence will compare wrapper offset and reload semantics, jumpspring early return, signed speed-nibble extraction, force carry, equal-low-byte ADC carry, X/page writes and returned A. The operational track uses controlled original-ROM/current x86/x64 routes, the focused horizontal C90 arithmetic harness, platform purity and DOS16 shared-core link. A shared-game repair refreshes all three local executables; an audit-only result does not.


## S9 closure - horizontal movement primitive chain

All six scoped labels are current-exact: `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `SaveXSpd`, `UseAdder`, and `ExXMove`. Static `$BF02-$BF4C` comparison found no feasible difference in enemy offset selection/return, jumpspring early return, four-bit fraction and signed integer extraction, carry preservation across force/X/page updates, or final returned A. Nine internal feasible control relations are exact, including `MoveObjectHorizontally -> MoveEnemyHorizontally` return.

The controlled original-ROM route covers 32 player, 32 enemy and 32 direct-generic entries, all six nodes and all three two-outcome branches. Fresh x86/x64 current checks match all 96 snapshots per width (192 comparisons) across 1,799 bytes and returned A. The focused C90 harness passes 2,360,832 arithmetic/write/return cases plus 255 no-write gate cases per width; platform purity passes and the OpenNT DOS16 link completes with the known OLDNAMES warning. No product source changed, so local executable artifacts were not refreshed. Historical migration remains **1,992 / 1,992**; current exact progress is **792 / 1,992 nodes** and **1,554 / 4,324 feasible controls** from **4,342 raw controls** with **18 infeasible**.


## S10 admission - vertical movement and gravity primitive chain

S10 admits `$BF4D-$C0A8`, `MovePlayerVertically -> ExVMove`: `MovePlayerVertically`, `NoJSChk`, `MoveD_EnemyVertically`, `MoveFallingPlatform`, `ContVMove`, `MoveRedPTroopaDown`, `MoveRedPTroopaUp`, `MoveRedPTroopa`, `MoveDropPlatform`, `MoveEnemySlowVert`, `SetMdMax`, `MoveJ_EnemyVertically`, `SetHiMax`, `SetXMoveAmt`, `MaxSpdBlockData`, `ResidualGravityCode`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `MovePlatformDown`, `MovePlatformUp`, `SetDplSpd`, `RedPTroopaGrav`, `ImposeGravity`, `AlterYP`, `ChkUpM`, and `ExVMove`. All 26 are `needs-evidence`: current exact forecast **792 / 1,992** to **818 / 1,992** nodes; historical migration remains **1,992 / 1,992**. It owns 37 internal feasible controls.

The shared owners are `src/game/world/gravity.c`, `src/game/player.c` and named actor wrappers. S9 precedes it; `EnemiesAndLoopsCore` is the successor and excluded. ROM logic compares all entry selector paths, scratch setup, table binding, signed speed/force saturation and branch returns. Operational proof uses vertical/gravity original-ROM routes against x86/x64, focused C90 tests, purity and DOS16 link.
