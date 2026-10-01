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
