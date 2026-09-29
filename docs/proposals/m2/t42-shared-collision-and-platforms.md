# M2 T42: shared collision and platforms

## Task contract

Admitted under the continuing owner-approved M2 mandate after T41 commit
a8d38ed. Baseline 1,284/1,992. All 98 exact targets below are incomplete and
intended for completion; no investigation-only credit. Maximum 1,382/1,992.
The current receiver column is the admission-time custody snapshot. Only S1
receives custody now; later S rows are plans, not concurrent admissions.

The original 11085-12000 slice cut PlayerBGCollision at DoFootCheck. Move
the contiguous twelve labels starting PlayerBGUpperExtent at line 11924
to the immediately following terrain slice (11924-13000, 148 nodes).
T42 ends at line 11923, 98 nodes. This preserves source order and keeps
the terrain caller intact; no completed claim or historical task changes.

## Planned S chains

Every S implements and proves its complete listed chain. Exact membership
and incoming status are in the checklist below. Every listed incomplete
member is that S's expected-new subset. Baselines are recounted at admission.
Children outside the chain remain named dependencies: compare full child
inputs and caller branches independently from actual-child integration.
An isolated caller proof cannot certify its descendants or whole-game output.
Every S reports both tracks and every remaining actual-child discrepancy.

### S1: Fireball enemy scan

6 nodes; source lines 11085-11144; entry `FireballEnemyCollision`, last label
`ExitFBallEnemy`. Sole shared owner: `src/game/world/fireball_enemy.c`.
Dependency boundary: FireballObjCore -> SprObjectCollisionCore / HandleEnemyFBallCol.
Original-ROM route/logic exit: Fireball active/parity gates, descending eligibility and repeated hits; child box inputs and live scratch reloads.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

### S2: Fireball hit and defeat

11 nodes; source lines 11145-11227; entry `BowserIdentities`, last label
`ExHCF`. Sole shared owner: `src/game/world/fireball_enemy.c`.
Dependency boundary: S1 -> relative position, vertical initialization, stun and floating score.
Original-ROM route/logic exit: Bowser duplicate selection, health and world identity, immunity, Piranha carry, state and score; downstream stun retains its owner.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

### S3: Hammer contact

3 nodes; source lines 11228-11261; entry `PlayerHammerCollision`, last label
`ExPHC`. Sole shared owner: `src/game/world/hammer_collision.c`.
Dependency boundary: MiscObjectsCore -> PlayerCollisionCore / InjurePlayer.
Original-ROM route/logic exit: Parity, timer/offscreen gates, collision latch, horizontal reversal, star immunity and injury call.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

### S4: Power-up pickup

6 nodes; source lines 11262-11308; entry `HandlePowerUpCollision`, last label
`NoPUp`. Sole shared owner: `src/game/world/powerup_collision.c`.
Dependency boundary: PlayerEnemyCollision -> erasure, score, player mode and colors.
Original-ROM route/logic exit: All four power-up kinds, small/super/fire status, timer/music and source call inputs; player-mode child retained until S5.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

### S5: Player enemy response and score

34 nodes; source lines 11309-11570; entry `ResidualXSpdData`, last label
`ExSFN`. Sole shared owner: `src/game/world/player_enemy_collision.c`.
Dependency boundary: PlayerEnemyCollision -> S4, S2 defeat, facing, injury, stomp, floating score.
Original-ROM route/logic exit: One contact-route family covers shell kicks, injury/death, stomp/demotion/revival and all adjacent tables, with child interfaces explicit.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

### S6: Enemy pair collision

16 nodes; source lines 11571-11733; entry `SetBitsMask`, last label
`ExTA`. Sole shared owner: `src/game/world/enemy_collision.c`.
Dependency boundary: EnemiesCollision -> collision core, pair response, defeat and turnaround.
Original-ROM route/logic exit: Descending pair scan, area/parity eligibility, latch masks, shell combinations, live offsets and chained score.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

### S7: Platform collision

14 nodes; source lines 11734-11860; entry `LargePlatformCollision`, last label
`NoSideC`. Sole shared owner: `src/game/enemy/platform_collision.c`.
Dependency boundary: LargePlatformCollision / SmallPlatformCollision -> shared top, underside and side response.
Original-ROM route/logic exit: Platform route with wide and two-box small geometry, collision flags, player state and positional side responses.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

### S8: Platform rider positioning

4 nodes; source lines 11861-11891; entry `PlayerPosSPlatData`, last label
`ExPlPos`. Sole shared owner: `src/game/enemy/platform_position.c`.
Dependency boundary: T41 platform movement -> small/vertical position entries.
Original-ROM route/logic exit: Small-platform table consumed by its placement path; engine/Y-high gates, low-Y borrow into high Y, speed/force reset. Replace T41 legacy seams.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

### S9: Collision entry preflight

4 nodes; source lines 11892-11923; entry `CheckPlayerVertical`, last label
`GetEnemyBoundBoxOfsArg`. Sole shared owner: `src/game/world/collision.c`.
Dependency boundary: Player/platform callers -> CheckPlayerVertical / GetEnemyBoundBoxOfs.
Original-ROM route/logic exit: Source carry result for player vertical eligibility and bounding-box index/masked-offscreen result; do not rewrite generic boxes.
Operational exit: focused native chain cases on x86/x64, prior affected
caller regressions, DOS16 link, platform purity and three refreshed EXEs.

## Exact node checklist

| ROM line | Label | Incoming status | Incoming receiver | Planned S |
| --- | --- | --- | --- | --- |
| 11085 | `FireballEnemyCollision` | audited; evidence incomplete | M2 T17 S6 | S1 |
| 11101 | `FireballEnemyCDLoop` | audited; evidence incomplete | M2 T17 S6 | S1 |
| 11115 | `GoombaDie` | audited; mismatch | M2 T17 S6 | S1 |
| 11120 | `NotGoomba` | audited; evidence incomplete | M2 T17 S6 | S1 |
| 11135 | `NoFToECol` | audited; evidence incomplete | M2 T17 S6 | S1 |
| 11141 | `ExitFBallEnemy` | audited; evidence incomplete | M2 T17 S6 | S1 |
| 11145 | `BowserIdentities` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11148 | `HandleEnemyFBallCol` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11160 | `ChkBuzzyBeetle` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11167 | `HurtBowser` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11182 | `SetDBSte` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11189 | `ChkOtherEnemies` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11197 | `ShellOrBlockDefeat` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11204 | `StnE` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11215 | `GoombaPoints` | audited; mismatch | M2 T17 S6 | S2 |
| 11220 | `EnemySmackScore` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11224 | `ExHCF` | audited; evidence incomplete | M2 T17 S6 | S2 |
| 11228 | `PlayerHammerCollision` | audited; evidence incomplete | M2 T17 S6 | S3 |
| 11256 | `ClHCol` | audited; evidence incomplete | M2 T17 S6 | S3 |
| 11258 | `ExPHC` | audited; evidence incomplete | M2 T17 S6 | S3 |
| 11262 | `HandlePowerUpCollision` | open | M2 T17 S6 | S4 |
| 11279 | `Shroom_Flower_PUp` | open | M2 T17 S6 | S4 |
| 11292 | `SetFor1Up` | open | M2 T17 S6 | S4 |
| 11297 | `UpToSuper` | open | M2 T17 S6 | S4 |
| 11302 | `UpToFiery` | open | M2 T17 S6 | S4 |
| 11305 | `NoPUp` | open | M2 T17 S6 | S4 |
| 11309 | `ResidualXSpdData` | open | M2 T17 S6 | S5 |
| 11312 | `KickedShellXSpdData` | open | M2 T17 S6 | S5 |
| 11315 | `DemotedKoopaXSpdData` | open | M2 T17 S6 | S5 |
| 11318 | `PlayerEnemyCollision` | open | M2 T17 S6 | S5 |
| 11339 | `NoPECol` | open | M2 T17 S6 | S5 |
| 11341 | `CheckForPUpCollision` | open | M2 T17 S6 | S5 |
| 11346 | `EColl` | open | M2 T17 S6 | S5 |
| 11350 | `KickedShellPtsData` | open | M2 T17 S6 | S5 |
| 11353 | `HandlePECollisions` | open | M2 T17 S6 | S5 |
| 11398 | `KSPts` | open | M2 T17 S6 | S5 |
| 11399 | `ExPEC` | open | M2 T17 S6 | S5 |
| 11401 | `ChkForPlayerInjury` | open | M2 T17 S6 | S5 |
| 11405 | `ChkInj` | open | M2 T17 S6 | S5 |
| 11413 | `ChkETmrs` | open | M2 T17 S6 | S5 |
| 11421 | `TInjE` | open | M2 T17 S6 | S5 |
| 11426 | `InjurePlayer` | open | M2 T17 S6 | S5 |
| 11430 | `ForceInjury` | open | M2 T17 S6 | S5 |
| 11440 | `SetKRout` | open | M2 T17 S6 | S5 |
| 11441 | `SetPRout` | open | M2 T17 S6 | S5 |
| 11448 | `ExInjColRoutines` | open | M2 T17 S6 | S5 |
| 11452 | `KillPlayer` | open | M2 T17 S6 | S5 |
| 11461 | `StompedEnemyPtsData` | open | M2 T17 S6 | S5 |
| 11464 | `EnemyStomped` | open | M2 T17 S6 | S5 |
| 11490 | `EnemyStompedPts` | open | M2 T17 S6 | S5 |
| 11506 | `ChkForDemoteKoopa` | open | M2 T17 S6 | S5 |
| 11521 | `RevivalRateData` | open | M2 T17 S6 | S5 |
| 11524 | `HandleStompedShellE` | open | M2 T17 S6 | S5 |
| 11536 | `SBnce` | open | M2 T17 S6 | S5 |
| 11540 | `ChkEnemyFaceRight` | open | M2 T17 S6 | S5 |
| 11545 | `LInj` | open | M2 T17 S6 | S5 |
| 11549 | `EnemyFacePlayer` | open | M2 T17 S6 | S5 |
| 11554 | `SFcRt` | open | M2 T17 S6 | S5 |
| 11558 | `SetupFloateyNumber` | open | M2 T17 S6 | S5 |
| 11566 | `ExSFN` | open | M2 T17 S6 | S5 |
| 11571 | `SetBitsMask` | open | M2 T17 S6 | S6 |
| 11574 | `ClearBitsMask` | open | M2 T17 S6 | S6 |
| 11577 | `EnemiesCollision` | open | M2 T17 S6 | S6 |
| 11595 | `ECLoop` | open | M2 T17 S6 | S6 |
| 11629 | `YesEC` | open | M2 T17 S6 | S6 |
| 11632 | `NoEnemyCollision` | open | M2 T17 S6 | S6 |
| 11637 | `ReadyNextEnemy` | open | M2 T17 S6 | S6 |
| 11644 | `ExitECRoutine` | open | M2 T17 S6 | S6 |
| 11648 | `ProcEnemyCollisions` | open | M2 T17 S6 | S6 |
| 11667 | `ShellCollisions` | open | M2 T17 S6 | S6 |
| 11680 | `ExitProcessEColl` | open | M2 T17 S6 | S6 |
| 11683 | `ProcSecondEnemyColl` | open | M2 T17 S6 | S6 |
| 11701 | `MoveEOfs` | open | M2 T17 S6 | S6 |
| 11707 | `EnemyTurnAround` | open | M2 T17 S6 | S6 |
| 11721 | `RXSpd` | open | M2 T17 S6 | S6 |
| 11729 | `ExTA` | open | M2 T17 S6 | S6 |
| 11734 | `LargePlatformCollision` | open | M2 T17 S6 | S7 |
| 11748 | `ChkForPlayerC_LargeP` | open | M2 T17 S6 | S7 |
| 11762 | `ExLPC` | open | M2 T17 S6 | S7 |
| 11768 | `SmallPlatformCollision` | open | M2 T17 S6 | S7 |
| 11777 | `ChkSmallPlatLoop` | open | M2 T17 S6 | S7 |
| 11788 | `MoveBoundBox` | open | M2 T17 S6 | S7 |
| 11799 | `ExSPC` | open | M2 T17 S6 | S7 |
| 11804 | `ProcSPlatCollisions` | open | M2 T17 S6 | S7 |
| 11807 | `ProcLPlatCollisions` | open | M2 T17 S6 | S7 |
| 11818 | `ChkForTopCollision` | open | M2 T17 S6 | S7 |
| 11834 | `SetCollisionFlag` | open | M2 T17 S6 | S7 |
| 11841 | `PlatformSideCollisions` | open | M2 T17 S6 | S7 |
| 11855 | `SideC` | open | M2 T17 S6 | S7 |
| 11856 | `NoSideC` | open | M2 T17 S6 | S7 |
| 11861 | `PlayerPosSPlatData` | open | M2 T17 S6 | S8 |
| 11864 | `PositionPlayerOnS_Plat` | open | M2 T17 S6 | S8 |
| 11871 | `PositionPlayerOnVPlat` | open | M2 T17 S6 | S8 |
| 11888 | `ExPlPos` | open | M2 T17 S6 | S8 |
| 11892 | `CheckPlayerVertical` | open | M2 T17 S6 | S9 |
| 11901 | `ExCPV` | open | M2 T17 S6 | S9 |
| 11905 | `GetEnemyBoundBoxOfs` | open | M2 T17 S6 | S9 |
| 11908 | `GetEnemyBoundBoxOfsArg` | open | M2 T17 S6 | S9 |

## S1 admission: fireball enemy scan

Six scoped and expected-new nodes listed above; baseline 1,284/1,992,
maximum 1,290. Coordinator accepts transfer-210 from M2 T17 S6.
Original $D6D9-$D735, FireballEnemyCollision through ExitFBallEnemy.
Extract the existing caller into world/fireball_enemy.c and retain its ABI.
Restore Goomba ID 6, per-iteration $01, byte-sized box offsets, ObjectOffset
reload after collision, live $01 before hit and at loop continuation. Keep
the source multi-hit loop. Generic collision and hit handling remain explicit
dependencies; the next S owns hit handling, generic collision stays in its
later source slice. No child repair or new host logic is admitted here.

Logic evidence: naturally reached original FireballEnemyCollision, bounded
entry fixtures, all original branches, child input RAM/arguments, returned
carry and call order. Independently report actual-child results and preserve
prior 18,928 actual matches. Original execution, PC, stack and outputs are
not patched. Focused native test: mysmb.fireball-enemy-scan.
Operational evidence: strict C90 x86/x64, affected fireball regression,
DOS16 link, platform purity, hidden-window response and three EXEs per P.
DOS remains link-only. Neither a build nor a caller proof certifies playability.

Provenance: existing owner-local original ROM and reviewed disassembly;
unreviewed/nonredistributable source remains local. Research and generated
data stay below ignored build/m2-t42-s1. Recorder budget: at most 1,024
cases, 90 MB raw data, twenty seconds per process, resumable case checkpoints;
coordinator owns cleanup after dependent validation. Owner-authorized EXE
delivery is the standing exception; ROM and raw trace inputs stay untracked.
Similar-issue sweep: ID constants, missing scratch writes, wrapped offsets,
live child state and duplicate owners in fireball callers. No unrelated repair.

## T closure criteria

Account for all 98 labels individually with source/control/data/child proof
and native evidence. Combine accepted S evidence into one cross-chain matrix;
rerun actual-child regression and explain every changed result. Refresh three
targets once for final integration. Transfer any unproved node by exact name
to an accepted receiver before closure; no hidden completion by association.

## S1 original fireball scan proof

S1 P1 closes all six expected nodes: 1,284 -> 1,290/1,992. No scoped
node is deferred or transferred. S2 is next; T42 remains open. Admission
gate confirmed six received labels: GoombaDie was audited mismatch; the
other five were audited evidence-incomplete. No already-complete credit.

| Node | Individual evidence and disposition |
| --- | --- |
| FireballEnemyCollision | Inactive/exploding and odd-frame exits; source byte box calculation and scan entry. ROM-match complete. |
| FireballEnemyCDLoop | Descending enemy slots store live $01 before state, flag, ID and offscreen eligibility. ROM-match complete. |
| GoombaDie | Goomba is ID 6; only its state >= 2 takes this source exclusion. ROM-match complete. |
| NotGoomba | Masked offscreen gate and enemy/fireball box arguments match original collision child inputs. ROM-match complete. |
| NoFToECol | Saved fireball box survives children; carry selects hit, ObjectOffset and $01 are reloaded, and hits do not terminate scanning. ROM-match complete. |
| ExitFBallEnemy | All gate and scan exits preserve the caller RAM footprint; original restores X from ObjectOffset, with no C register-state representation. ROM-match complete. |

Original $D6D9-$D735 is decoded directly from the owner-local PRG and checked
against the reviewed listing. All 54 instructions and both outcomes of all
twelve conditional branches execute over 1,024 bounded naturally reached
NMI/fireball routes. The six inventory labels preserve the source branch and
loop structure. No invented early exit after a hit remains. Inputs cover both
fireball slots, parity/state gates, enemy states and ID ranges, flags,
offscreen exclusion, box hits/misses and multiple hit calls.

Caller comparisons pass 2,048/2,048 on x86/x64. Every child receives matching
full input RAM and source X/Y or slot arguments before its recorded result is
applied. Collision return carry is recorded independently. Stack return storage
is excluded from comparisons; mapped $0109-$0139, scratch and OAM backing are
included. The saved fireball box remains constant even when a child changes
live $01/ObjectOffset. Source X restore is an internal CPU convention; the C
caller has a void result and its parent already owns live ObjectOffset.
No source CPU, PC, stack, branch or output mutation is used. Observer-free
original frames equal observed originals; this is not native full-frame proof.

An initial hostile ID 255 fixture prevents a subsequent original actor
dispatch from finishing the frame. Those 64 input cases were replaced by
valid ID 46 and rerun; other checkpoints were reused. No failed sample was
counted or hidden. The native exhaustive eligibility test still includes all
256 IDs. Final original fixture cases 0..1023 all complete.

Actual-child comparisons are separately 920/2,048. All 1,128 remaining
differences include $06/$07, which SprObjectCollisionCore writes but the
current const geometry helper omits. Of those samples, 488 also differ at
$00 and 48 at $0110-$0114. The hit child retains the incorrect ID-0 score
selection (original GoombaPoints compares ID 6); T42 S2 owns that node.
SprObjectCollisionCore and its descendant scratch writes retain their exact
M2 T17 S6 custody until their source-order admission. These are child gaps,
not hidden caller passes, new node credit, or a claim of gameplay equality.

Production ownership moves only FireballEnemyCollision out of the mixed
world/collision.c file into world/fireball_enemy.c. The ABI and actual child
owners remain unchanged. The source Goomba constant, per-loop $01 store,
byte-width box offsets, post-child live slot and loop reloads are restored.
Similar-issue sweep inspected every fireball collision call, duplicated
owner, ID comparison and live-offset use. The hit-child ID-0 comparison is
recorded for S2, not silently repaired here; no other source owner is added.

Native tests pass 131,072 ID/state eligibility combinations per width, plus
child-mutation cases for hit, miss, ObjectOffset and saved-box behavior.
The four CTests (scan, dispatcher, core and platform purity) pass. Existing
collision regression and fireball OAM tests pass on both widths, as do fifteen
initializer/platform suites. Prior actual matrix remains 18,928/29,434 with
zero lost matches. Known descendant differences remain explicitly unproved.

All 111 shared sources pass strict C90 x86/x64 and self-tests; hidden Win32
windows create and respond without desktop input. DOS16 compiles/links with
the existing OLDNAMES warning. Three owner-authorized EXEs are refreshed.
DOS remains link-only, without graphical or 486SX performance certification.
The platform diff is empty; no runtime emulator or host gameplay is introduced.

Reproduce fireball_enemy_scan_fixture.h cases 0..1023 with
--fixture=t42-fireball-enemy-scan=N, --fireball-enemy-scan-snapshot,
--control-children and --pc-coverage. fireball_enemy_scan_snapshot_check
checks the caller; enemy_loop_actual_check uses actual children. Focused
CTest: mysmb.fireball-enemy-scan. Raw records remain ignored under
build/m2-t42-s1 with checkpoint reuse, twenty-second process deadlines and
coordinator cleanup ownership after dependent regression work.

Raw trace bytes: 24425273, below the admitted 90 MB budget.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 259321 | 2cbf3eb0319cdced29685c782820bb89dd75c57e5ae54df4922c9b43c8ecb8d2 |
| mysmb32.exe | 354449 | cb992e8ff35eef96bd3b67e68a681557d7d31bf2b71ed0a6f85e911e5af5d01f |
| mysmb64.exe | 363070 | ba4c471be69a64b93fd06a06ff92f4d978f21691ee3639300241704de8473dd9 |
