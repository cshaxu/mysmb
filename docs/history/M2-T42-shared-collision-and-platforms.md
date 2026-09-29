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
`ExHCF`. Sole shared owner: `src/game/world/fireball_hit.c`.
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

## S2 admission: fireball hit response

S1 closed in 34bac77. Coordinator accepts transfer-211 from M2 T17 S6.
Baseline 1,290/1,992; eleven scoped/expected-new labels, maximum 1,301:

`BowserIdentities` (audited; evidence incomplete), `HandleEnemyFBallCol` (audited; evidence incomplete), `ChkBuzzyBeetle` (audited; evidence incomplete), `HurtBowser` (audited; evidence incomplete), `SetDBSte` (audited; evidence incomplete), `ChkOtherEnemies` (audited; evidence incomplete), `ShellOrBlockDefeat` (audited; evidence incomplete), `StnE` (audited; evidence incomplete), `GoombaPoints` (audited; mismatch), `EnemySmackScore` (audited; evidence incomplete), `ExHCF` (audited; evidence incomplete).

Original data $D736-$D73D and code $D73E-$D7C3. Extract the hit response
into world/fireball_hit.c (separate from the scan caller so each keeps one
bounded owner); expose ShellOrBlockDefeat for later source callers.
Keep the unproved ChkToStunEnemies body in world/collision.c behind its
named typed seam, without repairing it. Reuse existing relative-coordinate,
InitVStf and floating-score owners. Prove their full input RAM and arguments;
the source InitVStf returns A=0 and stun preserves X. Restore live $01 after
relative position and Bowser defeat, exact immunity/defeat flow and Goomba
score selection. Bowser table uses original world index without &7 aliasing;
local bound PRG supplies out-of-table reads, legal table constants remain
available to resource-free primitive tests. Missing resource is not a ROM
equivalence case. No platform or unadmitted child algorithm changes.

Logic route: naturally reached FireballEnemyCollision -> HandleEnemyFBallCol,
bounded entry inputs for normal/duplicate actors, health zero/one/multiple,
all worlds, immunity, Piranha carry and score branches. Full child input,
source return contracts, instruction/branch coverage and separate actual-root
comparison. Native route: mysmb.fireball-hit-chain, scan/core and affected
collision tests on both widths, strict C90 builds, DOS16 link, platform
purity, hidden windows and three refreshed EXEs. Preserve prior actual matches;
report descendant differences separately. Per-node evidence remains required.

Existing owner-local ROM/listing provenance and nonredistributable containment
continue. Ignored build/m2-t42-s2: at most 1,024 fixtures, 90 MB raw records,
twenty-second process deadlines and resumable checkpoints; coordinator owns
cleanup after dependent regressions. Owner-authorized EXEs remain the standing
delivery exception. DOS link-only; no whole-game equivalence assertion.
Similar-issue sweep: duplicate hit/defeat owners, live slot reloads, source
ID constants, ADC carry, Bowser table binding and child return values.
All eleven nodes must be proved or explicitly transferred before closure.

## S2 original fireball hit proof

S2 P1 closes all eleven expected nodes: 1,290 -> 1,301/1,992. No scoped
node is deferred or transferred. S3 hammer contact is next; T42 stays open.
Admission gate confirmed eleven received incomplete labels and maximum1,301.

| Node | Individual evidence and disposition |
| --- | --- |
| BowserIdentities | Original $D736 table binding, all eight world consumers, no &7 alias; native bound-PRG tests cover all byte indices. ROM-match complete. |
| HandleEnemyFBallCol | Relative-position call precedes live $01 reload; duplicate low-nibble selection falls back to the original live slot. ROM-match complete. |
| ChkBuzzyBeetle | Buzzy immunity follows duplicate selection; direct Bowser enters the same health path. ROM-match complete. |
| HurtBowser | Byte decrement including zero wrap, nonfatal exit and InitVStf X/A contract on lethal hit. ROM-match complete. |
| SetDBSte | World < 3 selects state23, other worlds state20; original sound and live score slot. ROM-match complete. |
| ChkOtherEnemies | Bullet Bill frenzy, Podoboo and IDs >=21 exit before stun/defeat. ROM-match complete. |
| ShellOrBlockDefeat | Piranha CMP carry enters ADC18, producing Y+25 modulo256 and the original stun A input. ROM-match complete. |
| StnE | Stun child preserves X; returned state low five bits are ORed with20. ROM-match complete. |
| GoombaPoints | Post-stun ID5 earns control6, ID6 earns control1, other IDs control2. ROM-match complete. |
| EnemySmackScore | Floating-score child receives original slot/control before Square1SoundQueue=8. ROM-match complete. |
| ExHCF | Immunity, nonfatal Bowser and score paths retain exact return footprints. ROM-match complete. |

Original code $D73E-$D7C3 and eight data bytes $D736-$D73D are checked
directly against the owner-local PRG and reviewed listing. All 64 instructions
execute. Both outcomes of twelve conditional branches execute; $D787 follows
LDA #9 and therefore always takes its BNE, as in C. All eight Bowser identity
consumers execute. 512 bounded routes reach HandleEnemyFBallCol through real
NMI, FireballObjCore and FireballEnemyCollision, with entry-only RAM inputs.
Normal and duplicate Bowser, duplicate non-Bowser fallback, immunity, health
0/1/2, worlds0..7, Piranha carry/wrap, post-stun score and live $01 are covered.

Full-input caller comparison passes 1,024/1,024 on x86/x64. Children are
RelativeEnemyPosition, InitVStf, ChkToStunEnemies and SetupFloateyNumber.
Original X/slot and A/score inputs are validated before recorded child RAM
returns; relative position restores X from ObjectOffset (then the caller
replaces it with $01), InitVStf preserves X and returns A0, and stun preserves
X. Hardware return-stack storage is excluded; mapped $0109-$0139, scratch,
queues and OAM backing are compared. No original code, CPU, PC, stack or
output patch. Observer-free original frames equal observed originals; this
does not compare native whole frames or certify child implementations.

Actual-child comparison is deliberately reported separately: 0/1,024 exact
RAM matches. Every difference is solely $00 in these fixtures: original
RelativeEnemyPosition stores the input slot there, and the later original
PlayerEnemyDiff child can overwrite it. Current relative-position and legacy
stun descendants omit those scratch writes. RelativeEnemyPosition remains
with M2 T16 S4; ChkToStunEnemies remains with M2 T17 S6 until its planned
source admission. No other byte differs in this bounded matrix, and the
former score-control mismatch is gone. This does not prove those children
for other inputs or make the complete hit path ROM-equal.

The production response moves to world/fireball_hit.c, leaving the scan
owner independent. ShellOrBlockDefeat is a shared entry for later callers;
no extra runtime path replaces it. The existing stun body is only exposed as
an explicitly unproved dependency and is otherwise unchanged. Original
InitVStf replaces duplicated initialization writes. Bowser's world index is
unmasked; bound PRG supports the source indexed read, while the eight legal
constants support resource-free primitive tests. An unbound out-of-domain
read is not an equivalence case. No platform or emulator code is introduced.

Similar-issue sweep covers live cached slots, duplicate Bowser selection,
source ID constants, carry into Piranha Y, score selection, table indexing
and all hit call sites. One old direct-call test omitted the source caller's
$01=2 precondition and expected Goomba control2; it now supplies $01 and
expects original control1. Existing collision/OAM suites then pass on both
widths. Unadmitted terrain/contact approximations remain with their owners.

Native proof passes 69,632 ID/Y/health/world combinations per width, plus
relative-child live-slot mutation and all256 unmasked bound-PRG indices.
Five CTests pass: hit, scan, dispatcher, core and platform purity. Fifteen
initializer/platform suites per width pass. Prior actual matrix retains all
18,928/29,434 matches; S1 independently retains all920/2,048, with no losses.
These sample counts remain distinct from node completion counts.

All112 shared C files compile under strict C90 for x86/x64; self-tests and
hidden responsive windows pass. DOS16 compiles/links with the preexisting
OLDNAMES warning. All three EXEs are refreshed. DOS remains link-only, with
no claim of graphical playability, resource binding or 486SX performance.

Reproduce fireball_hit_fixture.h cases0..511 using --fixture=t42-fireball-hit=N,
--fireball-hit-snapshot, --control-children and --pc-coverage. The
fireball_hit_snapshot_check caller harness checks child input/return contracts;
enemy_loop_actual_check uses actual children. Native CTest is
mysmb.fireball-hit-chain. Ignored build/m2-t42-s2 contains bounded records,
case checkpoints and evidence summaries; coordinator owns later cleanup.

Raw trace bytes: 9745484, below90 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 259497 | 19b9361640e0740d3632d94fe742a36adb5821b66090f09f2aca8030734f4479 |
| mysmb32.exe | 356409 | 1c3e61fd893ce9ddda0f9361cabc3b8a4784652bebb222e9a7d90e8aaf4ad9d9 |
| mysmb64.exe | 364039 | 5ff9cc3f857a73f1867d7eb634ffecd5e8301e0a6015a9f2a3f12820b85d447c |

## S3 admission: player hammer contact

S2 closed in 25a4ce6. Coordinator accepts transfer-212 from M2 T17 S6.
Baseline 1,301/1,992; three scoped/expected-new labels, maximum 1,304:

`PlayerHammerCollision` (audited; evidence incomplete), `ClHCol` (audited; evidence incomplete), `ExPHC` (audited; evidence incomplete).

Original $D7C4-$D7FF is one complete hammer contact chain. Extract only
this body from objects.c to world/hammer_collision.c, preserving its API.
Restore the live ObjectOffset reload after PlayerCollisionCore and byte-sized
box index. Preserve odd-frame, timer/offscreen, latch, byte negation and star
gates, then InjurePlayer tail. Keep existing geometry and injury children as
explicit dependencies; S5 owns injury. Do not repair their algorithms here.

Original route reaches PlayerHammerCollision through ordinary NMI/ProcHammerObj.
Entry-only RAM fixtures cover all nine misc slots, gates, hit/miss, latch,
speed sign/zero/wrap, star and injury inputs. Check all source branches,
full child input RAM/arguments and carry; report actual-child results separately.
Native test mysmb.hammer-contact-chain additionally changes ObjectOffset in
the geometry child to prove both miss and hit reloads. One chain validation
and three-target build/package pass per P; previous scan/hit/hammer roots and
known actual matches remain regression baselines. No host gameplay changes.

Source and research provenance remains the existing owner-local ROM/listing;
unreviewed/nonredistributable data stays ignored. build/m2-t42-s3 has at most
576 cases, 50 MB raw records, twenty-second process limits and checkpoints;
coordinator owns dependent retention/cleanup. Owner-authorized EXE delivery
continues; DOS remains link-only. Every node needs both proof tracks, with
unproved descendants named rather than counted as complete.
Similar-issue sweep covers misc-slot caches, wrapped indices, collision
latches, injury handoffs and duplicate hammer collision owners.

## S3 original hammer contact proof

S3 P1 closes all three audited-incomplete expected nodes: 1,301 ->
1,304/1,992. Admission/closure gates confirm exact received scope; no
scoped node remains incomplete or transfers. T42 remains open; S4 is next.

| Node | Individual evidence and disposition |
| --- | --- |
| PlayerHammerCollision | Odd-frame and timer/offscreen gates; wrapped box Y; geometry carry; live ObjectOffset; latch, byte negation, star gate and injury tail. ROM-match complete. |
| ClHCol | Carry-clear path reloads ObjectOffset and clears that misc collision latch only. ROM-match complete. |
| ExPHC | Parity, timer/offscreen, latched/star and miss exits preserve source return footprint. ROM-match complete. |

All 30 original instructions in $D7C4-$D7FF and both outcomes of five
branches execute. 288 entry-input fixtures reach the root through ordinary
NMI/ProcHammerObj across all nine misc slots, parity, timer/offscreen, box
hit/miss, collision latch, speed extrema, star immunity and injury states.
No source ROM, CPU, PC, stack or output mutation. Observed and observer-free
original frames agree; this is not a native full-frame comparison.

Caller comparison passes 576/576 across x86/x64. PlayerCollisionCore's
original Y box argument, complete child-input RAM and returned carry are
checked; its initial X is overwritten by the source child. On return, the
caller reloads ObjectOffset for both carry results. InjurePlayer's tail
receives the same RAM and misc X; its original return is observed at the
parent's hardware return address. Stack return storage is excluded but
mapped $0109-$0139, scratch, queues and OAM backing remain compared.

Separate actual-child comparison matches 54/576. Every remaining sample
differs at $06 because current geometry omits the source scratch store; 18
also differ at $07. Among the failing samples, 234 have missing injury sound
$FF and palette-command bytes $0300-$0307; 104 differ at $00. Geometry stays
with its M2 T17 S6 receiver until source-order admission, and InjurePlayer
is planned for T42 S5 (still M2 T17 S6 custody). The current injury child
omits original sound/palette work. Those algorithms are not repaired or
certified here; this caller proof is not whole-hit or gameplay equality.

The sole hammer contact body moves from objects.c to world/hammer_collision.c.
Its address comment, byte-sized box offset and post-geometry ObjectOffset
reload are restored. Similar-issue sweep covers every production hammer
caller, duplicated body, misc slot cache, box index, latch, negation and
injury handoff. ProcHammerObj already supplies the source ObjectOffset;
geometry and injury remain separate shared-game owners. Platform diff is
empty and no emulator is linked into the runtime.

Native proof passes 18,432 gate/latch/speed cases per width, child-mutated
ObjectOffset on hit and miss, and all 256 wrapped box indices. Five CTests
pass: contact, hammer lifecycle, fireball scan/hit and platform purity.
Existing collision/OAM suites pass on both widths. The prior hammer lifecycle
retains 126/126 actual-parent comparisons under its original persistent-RAM
contract, which excludes scratch0..7; no broader claim is inferred. The
actor matrix retains all 18,928/29,434 matches. S1's 2,048 and S2's 1,024
actual results are unchanged from the latest S2 baseline, including known
failures. Fifteen initializer/platform native suites per width also pass.

All 113 shared files pass strict C90 x86/x64 and product self-tests; hidden
windows create/respond without desktop input. DOS16 compiles/links with the
preexisting OLDNAMES warning. Three EXEs are refreshed. DOS stays link-only;
no DOS graphics, resource binding or physical 486SX performance is certified.

Reproduce hammer_contact_fixture.h cases0..287 using
--fixture=t42-hammer-contact=N, --hammer-contact-snapshot, --control-children
and --pc-coverage. hammer_contact_snapshot_check verifies the caller;
enemy_loop_actual_check exercises actual children. Native CTest:
mysmb.hammer-contact-chain. Ignored build/m2-t42-s3 retains bounded records
and checkpoints with twenty-second process deadlines and coordinator cleanup
ownership after dependent verification.

Raw records: 4494547 bytes, below 50 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 259513 | 1c44dee115434c57c617117c8f2fede699c8da641c012acfe43c8c78fcc67460 |
| mysmb32.exe | 356625 | a291a8b53371da47647764869459af460cad41b5495e34a983f25f5a05176ca1 |
| mysmb64.exe | 364291 | f5703a930a65475e5580986d5e048a6c4066dafd40f3629caa0b35d50ab61b9a |

## S4 admission: power-up pickup

S3 closed in 2fb45bd. Coordinator accepts transfer-213 from M2 T17 S6.
Baseline 1,304/1,992; six scoped/expected-new labels, maximum 1,310:

`HandlePowerUpCollision` (open), `Shroom_Flower_PUp` (open), `SetFor1Up` (open), `UpToSuper` (open), `UpToFiery` (open), `NoPUp` (open).

Original $D800-$D84C. Extract the pickup body into world/powerup_collision.c.
Give the existing collection API its source enemy-slot argument and update
its sole gameplay caller plus direct tests. Restore EraseEnemyObject then
SetupFloateyNumber(control6), pickup sound, fresh PowerUpType, star timer AND
music, 1UP control overwrite, player status and palette/SetPRout sequence.
The old inline SetPRout effect becomes one named shared objects.c dependency;
its original node remains S5-owned, with no credit here. Existing erasure,
floating-score and palette implementations remain their own dependencies.

Logic proof: ordinary NMI PowerUpObjHandler -> PlayerEnemyCollision reaches
the pickup root; input fixtures cover types, player statuses, source order,
score overwrite, music, live child state and child arguments. Separate actual
child comparisons from full-input caller contracts. Native proof includes all
byte types/statuses and source child mutation; CTest mysmb.powerup-pickup-chain,
affected power-up and collision tests, strict C90 x86/x64, DOS16 link,
platform purity, hidden-window response and three EXEs once per P.

Existing owner-local ROM/listing provenance and nonredistributable containment
remain; ignored build/m2-t42-s4 allows at most 384 fixtures, 50 MB raw records,
twenty-second process deadlines and resumable checkpoints. Coordinator owns
cleanup after dependent regressions. Owner-authorized three EXEs remain the
standing delivery exception. DOS link-only; no complete-game claim.
Similar-issue sweep covers partial erasure, early type caching, world-coordinate
score substitution, absent star music, direct-call preconditions and duplicate
pickup effects. No unadmitted child repair or platform gameplay is authorized.
Every scoped node needs dual proof or exact accepted transfer before closure.

## S4 original power-up pickup proof

S4 P1 closes all six expected open labels: 1,304 -> 1,310/1,992.
No scoped label remains incomplete or transfers. T42 stays open; S5 is next.

| Node | Individual evidence and disposition |
| --- | --- |
| HandlePowerUpCollision | EraseEnemyObject, score control6, pickup sound and fresh type dispatch in original order. ROM-match complete. |
| Shroom_Flower_PUp | Fresh PlayerStatus dispatch: small, super and already-fiery exits. ROM-match complete. |
| SetFor1Up | Overwrite only the source slot floating-score control with 0B after common setup. ROM-match complete. |
| UpToSuper | Store super status and call SetPRout with A9/Y0. ROM-match complete. |
| UpToFiery | Call SetPRout with A12/Y0 after fiery status and GetPlayerColors. ROM-match complete. |
| NoPUp | Preserve the source no-upgrade return footprint. ROM-match complete. |

All 35 original instructions in $D800-$D84C and both outcomes of four
branches execute. 128 controlled input fixtures enter through ordinary NMI,
PowerUpObjHandler and PlayerEnemyCollision. Types, statuses, player/area
palette settings and command offsets cover the common path and each tail.
Only entry RAM inputs change; original code, PC, stack and outputs do not.
Observed and observer-free original frames agree, not native full frames.

Caller comparison passes 256/256 on x86/x64. Complete child input RAM,
erase/score slot X, score A6, palette entry X and SetPRout A/Y are checked
before replaying recorded child results. Erase/score preserve X; SetPRout
returns ObjectOffset. Palette and SetPRout do not consume incoming X.
Hardware return storage is excluded; mapped $0109-$0139 remains compared.
Separate actual-child comparison passes 240/256. The sixteen fiery cases
differ only at $00 (original FF, native78), from GetPlayerColors. That child
keeps receiver M2 T27 S1 and its existing scratch gap; this S does not repair
or certify its implementation. SetPRout and SetupFloateyNumber remain S5
dependencies. This proves the six caller labels, not whole-game equality.

The single pickup body now lives in game/world/powerup_collision.c with an
explicit enemy-slot argument. Its existing caller and direct tests use slot5.
Full erasure replaces partial field clearing; score setup uses prepared
relative coordinates, then sound and fresh type/status reads. Star music is
restored; 1UP overwrites score control after common setup. The old SetPRout
effects have one named dependency seam pending S5. Similar-issue review covers
all collection call sites, duplicate effects, type caching, score coordinates,
erasure and star music. No platform gameplay changes or runtime emulator.

Native checks pass 393,216 type/status/slot combinations on each width and
child-mutated type/status checks. Four CTests pass: pickup, actor, initializer
and platform purity. Collision/OAM suites pass on both widths. Existing
core_smoke and local_area_smoke still fail at lines136 (entrance) and450
(warp rendering), respectively: instrumented baseline S3 and current S4
fail at exactly the same assertions on both widths. Their pickup API changes
do not certify these broad tests; no assertion is weakened or removed.

Old actual power-up actor comparisons improve from84/100 to86/100: star
case46 now matches on both widths. All prior matches remain; fourteen prior
OAM/graphics failures remain unchanged. The actor matrix retains18,928/29,434
matches, and S1/S2/S3 retain all3,648 prior actual outcomes including failures.
Fifteen initializer/platform native suites also pass on both widths.

All114 shared files compile as strict C90 for x86/x64. Both product self-tests
pass and hidden windows create/respond without desktop input. DOS16 links
with the existing OLDNAMES warning; DOS graphics, resource binding and 486SX
performance remain unverified. Three owner-authorized test EXEs are refreshed.

Reproduce powerup_pickup_fixture.h cases0..127 with
--fixture=t42-powerup-pickup=N, --powerup-pickup-snapshot, --control-children
and --pc-coverage. powerup_pickup_snapshot_check validates callers;
enemy_loop_actual_check runs actual children. Native CTest is
mysmb.powerup-pickup-chain. Ignored build/m2-t42-s4 holds bounded records and
checkpoints with twenty-second process deadlines; coordinator owns cleanup
after dependent verification. A corrected fixture uses slot5 box $04C4-$04C7;
the rejected earlier box fixture never produced closure evidence.

Raw records: 2260491 bytes, below50 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 259513 | c1122e366fbd4bec4821876d8d6a90ec0a8183e8d9e69112c5f37b0c8c5610e0 |
| mysmb32.exe | 356931 | fb78427c6dd5e1b8a005808237eec073cc3f4fb31f9047cd7730baaef775a0ef |
| mysmb64.exe | 365144 | 3095b200d1125ff37305d98f07493d26a57e23d9421f62e1006fe1f6c3ccb18f |

## S5 admission: player enemy response and score

S4 closed in92c925a. Coordinator accepts transfer-214 from M2 T17 S6.
Baseline1,310/1,992;34 scoped/expected-new labels, maximum1,344:

`ResidualXSpdData` (open), `KickedShellXSpdData` (open), `DemotedKoopaXSpdData` (open), `PlayerEnemyCollision` (open), `NoPECol` (open), `CheckForPUpCollision` (open), `EColl` (open), `KickedShellPtsData` (open), `HandlePECollisions` (open), `KSPts` (open), `ExPEC` (open), `ChkForPlayerInjury` (open), `ChkInj` (open), `ChkETmrs` (open), `TInjE` (open), `InjurePlayer` (open), `ForceInjury` (open), `SetKRout` (open), `SetPRout` (open), `ExInjColRoutines` (open), `KillPlayer` (open), `StompedEnemyPtsData` (open), `EnemyStomped` (open), `EnemyStompedPts` (open), `ChkForDemoteKoopa` (open), `RevivalRateData` (open), `HandleStompedShellE` (open), `SBnce` (open), `ChkEnemyFaceRight` (open), `LInj` (open), `EnemyFacePlayer` (open), `SFcRt` (open), `SetupFloateyNumber` (open), `ExSFN` (open).

Original $D84D-$DA24 forms the complete contact/response/score chain.
Consolidate specialized legacy collision bodies into shared
world/player_enemy_collision.c. Preserve source gates, live ObjectOffset,
box child arguments, power-up/star tails, collision latches, kick scoring,
injury/death, stomp/demotion/revival and facing/score writes. Distinguish
InjurePlayer from ForceInjury(A); update timer's direct forced entry.
Move SetPRout and SetupFloateyNumber to this owner. ResidualXSpdData is
unreferenced in the original listing: bind its two source bytes and record
that fact, never invent a gameplay consumer to obtain coverage.

Source children CheckPlayerVertical/GetEnemyBoundBoxOfs, generic geometry,
EnemyTurnAround, SetStun, PlayerEnemyDiff, GetPlayerColors, InitVStf and S2/S4
retain independent ownership. Expose legacy child boundaries as needed,
without silently repairing their algorithms or awarding their nodes.
Remove duplicated production contact rules; old aggregate testing interfaces
may prepare inputs and call the same core, but cannot retain separate responses.

Logic proof uses controlled original NMI contact routes plus directly reached
injury/score entries, checking source branches, data binding, complete child
inputs/arguments and live state. Record actual-child comparisons separately.
Operational proof uses mysmb.player-enemy-contact-chain, existing caller and
power-up/hammer/firebar/timer regressions, strict C90 x86/x64 and DOS16 link,
platform purity and three owner-authorized EXEs once per completed P.
Known baseline core/local-area smoke failures retain their S4 evidence.

Owner-local ROM/listing provenance and nonredistributable containment remain
unchanged. Ignored build/m2-t42-s5 permits at most4,096 original fixtures,
150 MB raw output, twenty-second process limits and resumable checkpoints.
Coordinator owns cleanup after dependent verification. No product emulator,
platform gameplay or whole-game/DOS graphics certification. Similar-issue
sweep covers duplicate ID-dispatch collision bodies, source slot reloads,
forced versus guarded injury, scratch/score coordinates and byte-wrap tables.
Each exact label needs both proof tracks before closure; admission is no credit.

## S5 original player contact proof

S5 P1 closes all34 expected open labels:1,310 ->1,344/1,992.
No scoped label remains incomplete or transfers. T42 stays open; S6 is next.

| Node | Individual evidence and disposition |
| --- | --- |
| ResidualXSpdData | Unreferenced original two-byte table bound exactly; no invented consumer. ROM-match complete. |
| KickedShellXSpdData | Two direction-selected shell speeds bound to source bytes. ROM-match complete. |
| DemotedKoopaXSpdData | Two direction-selected demoted speeds bound to source bytes. ROM-match complete. |
| PlayerEnemyCollision | Parity, vertical, mask, engine and state gates; prepared boxes; live ObjectOffset and contact tails. ROM-match complete. |
| NoPECol | Gate/miss return preserves source footprint after optional latch clear. ROM-match complete. |
| CheckForPUpCollision | Power-up ID selects the S4 tail before star logic. ROM-match complete. |
| EColl | Star timer selects defeat; zero selects ordinary response. ROM-match complete. |
| KickedShellPtsData | Three near-revival kick scores bound to source bytes and indexed by interval timer. ROM-match complete. |
| HandlePECollisions | Collision latch, enemy type, water and state branches precede kick or injury. ROM-match complete. |
| KSPts | Choose chain-plus-three or interval-indexed score, then SetupFloateyNumber. ROM-match complete. |
| ExPEC | Latched, masked and defeated-Goomba exits retain their source writes. ROM-match complete. |
| ChkForPlayerInjury | Y-speed sign/zero dispatch selects stomp or injury checks. ROM-match complete. |
| ChkInj | ID threshold and byte-wrapped player Y plus12 select top contact. ROM-match complete. |
| ChkETmrs | Stomp and injury timers precede relative-X facing decisions. ROM-match complete. |
| TInjE | Left-side contact tests moving direction before turn/injury. ROM-match complete. |
| InjurePlayer | InjuryTimer guard precedes ForceInjury. ROM-match complete. |
| ForceInjury | PlayerStatus selects death or status/sound/palette injury sequence; consumes source A. ROM-match complete. |
| SetKRout | Injury/death select player state1 before SetPRout. ROM-match complete. |
| SetPRout | Write engine/state, halt timers and zero scroll in source order. ROM-match complete. |
| ExInjColRoutines | Reload ObjectOffset at injury return; no RAM side effect. ROM-match complete. |
| KillPlayer | Zero X speed, death music, FC Y speed, engine11 and state1. ROM-match complete. |
| StompedEnemyPtsData | Four stomp scores bound to source bytes and original ID dispatch. ROM-match complete. |
| EnemyStomped | Spiny injury and stomp sound precede source ID/points branches. ROM-match complete. |
| EnemyStompedPts | Score, saved direction, SetStun, state20, InitVStf and FD bounce in order. ROM-match complete. |
| ChkForDemoteKoopa | ID demotion, normal state, score3, InitVStf, facing and demoted speed. ROM-match complete. |
| RevivalRateData | Two hard-mode revival intervals bound to source bytes. ROM-match complete. |
| HandleStompedShellE | State4, byte stomp-chain increment, score, stomp timer and interval writes. ROM-match complete. |
| SBnce | FC player bounce and return. ROM-match complete. |
| ChkEnemyFaceRight | Right-side direction check selects direct injury or turnaround. ROM-match complete. |
| LInj | EnemyTurnAround precedes guarded injury. ROM-match complete. |
| EnemyFacePlayer | PlayerEnemyDiff sign selects direction and returned speed-table index. ROM-match complete. |
| SFcRt | Store direction and decrement index without extra scratch writes. ROM-match complete. |
| SetupFloateyNumber | Store score control, timer30, enemy Y and prepared relative X. ROM-match complete. |
| ExSFN | Score return has no additional RAM writes. ROM-match complete. |

All210 original instructions in $D84D-$DA24 execute. Six tables (15 bytes)
match the original; ResidualXSpdData is unreferenced original data. Of41
branches,39 execute both ways. $D963 follows LDA #0B and must take BNE;
$D985 cannot take its Podoboo branch from this root because the earlier
ID check routes Podoboo to injury before every EnemyStomped incoming edge.
Thus80/80 feasible outcomes are covered; no infeasible edge is called tested.

1,600 controlled RAM-input cases reach PlayerEnemyCollision from ordinary
NMI/PowerUpObjHandler. Original ROM code, PC, stack and outputs are unchanged.
Observed and observer-free frames agree. Full caller comparison passes
3,200/3,200 across x86/x64. Complete child input RAM and consumed arguments
are checked before replaying child outputs: vertical carry, box Y, geometry
Y/carry, pickup/defeat slots, palette input, stun, initialization, distance
slot/sign and turnaround. Register inputs overwritten before use are excluded
explicitly; source X preservation is checked where the caller consumes it.
Hardware return storage is excluded; mapped $0109-$0139 remains compared.

Actual children match1,184/3,200. All2,016 differences include $06;96 also
include $07 and1,156 include $00. There are no other differing RAM addresses
in this matrix. Geometry and SetStun keep M2 T17 S6 custody; GetPlayerColors
keeps M2 T27 S1. Their known scratch omissions remain unresolved. Vertical,
box-offset and turnaround dependency seams retain S9/S6 responsibility;
this caller proof does not certify their implementations or full gameplay.

One shared player_enemy_collision.c replaces the separate enemy-type
responses. Collision callbacks consume prepared boxes; compatibility test
adapters only select/prepare inputs and call that owner. SetPRout and source
SetupFloateyNumber move here. Guarded InjurePlayer and direct ForceInjury(A)
are distinguished, and RunGameTimer uses the latter. Injury sound/palette,
kick interval scoring, byte-wrapped stomps, demotion and source facing order
are restored. Existing SetStun is split from its demotion prelude without
changing its algorithm. Legacy terrain/pair world-coordinate score preparation
stays with its original pending owners, not this source-relative entry.

Similar-issue review covers every collision dispatch/caller, duplicated
response, timer address, forced/guarded injury and score coordinate. The
first source comparison caught an interval/frame-timer address transcription
error; it was corrected to $0796 before final verification and rebuild.
Pre-correction native outputs are explicitly retained only as rejected
local diagnostics. Platform diff is empty; no runtime emulator is linked.

Native tests pass460,288 kick/injury/stomp combinations per width plus
live-slot mutation and gate contracts. Three focused CTests pass: contact,
timer and platform purity. Six affected suites pass on both widths.
Old bullet/Hammer Bro/paratroopa tests had omitted the AreaType=land input;
two also left the C structure or preserved NES RAM uninitialized. Those
inputs are corrected without weakening assertions, following the original
water-injury branch and InitializeMemory's partial-clear contract.
Known broad core/local-area smoke failures retain the S4 baseline record.

The actual actor matrix improves18,928 ->18,936/29,434 with no lost prior
match. Earlier fireball scan/hit, hammer-contact and pickup matrices retain
all prior matches:920/2,048,0/1,024,54/576 and240/256, respectively. Timer
parents pass32/32 and hammer lifecycle126/126. Power-up parents retain86/100
with the existing fourteen OAM failures. These retained parent contracts do
not enlarge their original scratch/output coverage.

All115 shared files compile as strict C90 for x86/x64; both product self-tests
and hidden-window response probes pass. DOS16 compiles/links with the known
OLDNAMES warning. Three owner-authorized EXEs are refreshed after the final
correction. DOS graphics/resource binding and486SX performance remain unproved.

Reproduce player_enemy_contact_fixture.h cases0..1599 with
--fixture=t42-player-enemy-contact=N, --player-enemy-contact-snapshot,
--control-children and --pc-coverage. player_enemy_contact_snapshot_check
proves callers; enemy_loop_actual_check runs actual children. Recorder permits
the combined observation options; per-process deadlines remain20 seconds.
Ignored build/m2-t42-s5 has resumable checkpoints; coordinator owns cleanup
after dependent regressions. Native CTest:mysmb.player-enemy-contact-chain.

Raw records: 41311722 bytes, below150 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256233 | 3217e11afc45cc9039be1dfac8c286e5456eefc0450472f20ab38457c5513bfa |
| mysmb32.exe | 354516 | 80a3784a553a857a27a060e21684b4bb5b42b02af32de18be043d614b73f7f04 |
| mysmb64.exe | 362755 | 9334617e30843e02917fb00eb0b11e9932573c1b71b12d0a33464765be818072 |

## S6 admission: enemy pair collision

S5 closed in0f2626c. Coordinator accepts transfer-215 from M2 T17 S6.
Baseline1,344/1,992;16 scoped and expected-new nodes, maximum1,360:

`SetBitsMask` (open), `ClearBitsMask` (open), `EnemiesCollision` (open), `ECLoop` (open), `YesEC` (open), `NoEnemyCollision` (open), `ReadyNextEnemy` (open), `ExitECRoutine` (open), `ProcEnemyCollisions` (open), `ShellCollisions` (open), `ExitProcessEColl` (open), `ProcSecondEnemyColl` (open), `MoveEOfs` (open), `EnemyTurnAround` (open), `RXSpd` (open), `ExTA` (open).

Original $DA25-$DB44 is one contiguous pair-scan/response chain, including
both seven-byte mask tables and EnemyTurnAround. Shared owner is
world/enemy_collision.c. RunNormalEnemies supplies prepared boxes; child
boundaries are GetEnemyBoundBoxOfs, SprObjectCollisionCore, ShellOrBlockDefeat
and SetupFloateyNumber. Preserve descending scan, RAM1 and ObjectOffset
reloads, candidate-first geometry arguments, latch masks, shell combinations,
chain score wrapping and turnaround eligibility. Remove the old pair body;
terrain-only legacy defeat remains pending its own admitted source slice.

Logic proof compares original controlled NMI enemy-pair entries, branches,
tables and full child input/consumed argument contracts before replaying
child results. Actual-child integration is reported separately with named
differences; child algorithms outside S6 are not silently repaired or credited.
Operational proof uses mysmb.enemy-pair-chain, affected contact/actor tests,
strict C90 x86/x64, DOS16 link, platform purity and three refreshed EXEs
once per P. Prior S5 evidence is the incoming regression baseline.

Owner-local ROM/listing provenance and nonredistributable containment are
unchanged. Ignored build/m2-t42-s6 permits4,096 fixtures and150 MB raw records,
twenty-second process deadlines and resumable checkpoints. Coordinator owns
cleanup after dependent regressions. Three owner-authorized EXEs remain the
delivery exception; DOS link-only and no whole-game equality claim.
Similar-issue sweep covers cached offsets, box argument order, duplicated
defeat/score effects, latch updates and byte-table indexing. All16 nodes need
dual proof or accepted exact transfers before closure; admission is no credit.

## S6 original enemy pair proof

S6 P1 closes all16 expected open nodes:1,344 ->1,360/1,992.
No scoped label remains incomplete or transfers. T42 remains open; S7 is next.

| Node | Individual evidence and disposition |
| --- | --- |
| SetBitsMask | Seven set-mask bytes bound to original PRG; original unmasked indexing retained. ROM-match complete. |
| ClearBitsMask | Seven clear-mask bytes bound to original PRG; source miss path uses the clear table. ROM-match complete. |
| EnemiesCollision | Parity, area, current ID and mask gates; source box child and incoming-X decrement. ROM-match complete. |
| ECLoop | Store candidate in RAM1, preserve first box and filter each descending candidate. ROM-match complete. |
| YesEC | State-bit bypass or newly set latch enters the same pair response. ROM-match complete. |
| NoEnemyCollision | Clear the live current-slot mask in the live candidate collision bits. ROM-match complete. |
| ReadyNextEnemy | Restore first box and reload/decrement RAM1 after every child path. ROM-match complete. |
| ExitECRoutine | Source return has no extra RAM effect; returned X is unused by the C caller. ROM-match complete. |
| ProcEnemyCollisions | Combined defeated-state guard precedes current-shell and second-shell dispatch. ROM-match complete. |
| ShellCollisions | Second defeat, live current chain read, live score slot and live chain increment. ROM-match complete. |
| ExitProcessEColl | Defeated-state and Hammer Bro suppression return without extra writes. ROM-match complete. |
| ProcSecondEnemyColl | Second-shell defeat, RAM1 chain lookup, live ObjectOffset score and live RAM1 increment. ROM-match complete. |
| MoveEOfs | Turn the candidate then reload ObjectOffset before turning the current enemy. ROM-match complete. |
| EnemyTurnAround | Preserve ID13/17/5 exemptions, ID18/14 turns and other ID>=7 exemption. ROM-match complete. |
| RXSpd | Byte-negate X speed and XOR direction with3 without additional scratch writes. ROM-match complete. |
| ExTA | Turnaround return preserves the original RAM footprint. ROM-match complete. |

All134 original instructions in $DA33-$DB44 execute. Both adjacent mask
tables bind all14 source bytes. Twenty-six of28 branches execute both ways.
The taken ID13/17 exits at $DB20/$DB24 cannot occur from this pair root:
both objects are filtered before EnemyTurnAround. Their exact source tests
are retained and full-byte native ID tests cover those leaf exits. Thus
54/54 feasible root outcomes execute; the two excluded edges are not called
ROM-executed. No PC, stack, code or output modification obtains coverage.

1,024 controlled entry-RAM fixtures reach EnemiesCollision through ordinary
NMI/RunNormalEnemies. Original frames with and without observers agree.
The caller comparison passes2,048/2,048 on x86/x64. Full child input RAM and
consumed registers are checked before replaying child outputs: box-offset Y
and X preservation, candidate-first geometry X/Y and returned carry, defeat
slot/X preservation, and floating-score X/A and X preservation. Hardware
return storage is excluded; all mapped $0109-$0139 variables remain compared.
Turnaround and pair response are implemented directly, not child substitutions.

Actual children match696/2,048. The remaining1352 comparisons differ only
at $00/$06/$07, the existing SetStun/distance and geometry scratch omissions.

Those descendants retain M2 T17 S6 custody and their later source slices.
GetEnemyBoundBoxOfs remains T42 S9-owned. Source-relative score and the
already translated ShellOrBlockDefeat are used without changing their child
algorithms. This S proves its sixteen nodes, not full-game equivalence.

One shared world/enemy_collision.c replaces the legacy pair and turnaround
bodies. It restores RAM1 writes/reloads, live ObjectOffset after children,
candidate-first box order, both source latch tables and shared defeat/score
calls. The now-unused world-coordinate score helper is removed. The old
terrain-only simplified defeat helper stays with the terrain owner. The
similar-issue sweep reviews all production pair/turnaround callers, both
score implementations, cached offsets, child argument order and latch paths.
Platform files are unchanged; no emulator is linked into the product.

Native tests pass393,472 state/latch/chain/ID/speed/direction combinations
per width, plus child-mutated offsets, miss masks and gates. Three CTests
pass: pair chain, prior contact chain and platform purity. Six affected
suites pass on both widths. All18,936 prior actual actor matches remain;
five preceding collision matrices retain920/2,048,0/1,024,54/576,240/256 and
1,184/3,200 matches respectively. Existing descendant failures are not hidden
or credited. The broad core/local-area baseline limitations remain unchanged.

All116 shared files compile as strict C90 for x86/x64. Both product self-tests
and hidden-window creation/response probes pass. DOS16 compiles/links with
the known OLDNAMES warning. Three owner-authorized EXEs are refreshed. DOS
graphics, resource binding and physical486SX performance remain unproved.

Reproduce enemy_pair_fixture.h cases0..1023 with --fixture=t42-enemy-pair=N,
--enemy-pair-snapshot, --control-children and --pc-coverage. Use
enemy_pair_snapshot_check for callers and enemy_loop_actual_check for actual
children. Native CTest is mysmb.enemy-pair-chain. Ignored build/m2-t42-s6
contains resumable checkpoints and bounded raw records; per-process limit
is20 seconds. Coordinator owns cleanup after dependent regression.

Raw records: 32202654 bytes, below150 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256329 | 39021432fed66a7957199ef9c4807e08ed9dffbef504d42292f8ec979877a0c7 |
| mysmb32.exe | 355274 | 586ce58cb7e7ecb73fdd4d67e73ec8b2ae953fc82454b579a6c12c1edc62e342 |
| mysmb64.exe | 363036 | 2f5f377b2cfe577911aec5a1424d9f1378e98b9f64208481ac70cbec667dea4a |

## S7 admission: platform collision

S6 closed in16c21d3. Coordinator accepts transfer-216 from M2 T17 S6.
Baseline1,360/1,992;14 scoped and expected-new nodes, maximum1,374:

`LargePlatformCollision` (open), `ChkForPlayerC_LargeP` (open), `ExLPC` (open), `SmallPlatformCollision` (open), `ChkSmallPlatLoop` (open), `MoveBoundBox` (open), `ExSPC` (open), `ProcSPlatCollisions` (open), `ProcLPlatCollisions` (open), `ChkForTopCollision` (open), `SetCollisionFlag` (open), `PlatformSideCollisions` (open), `SideC` (open), `NoSideC` (open).

Original $DB45-$DC16 covers large and small platform collision plus the
shared underside/top/side response. Sole owner: enemy/platform_collision.c.
Preserve timer/state gates, balance-partner-first then current checks, stack
slot preservation, small-platform two-box Y wrapping, live RAM0/ObjectOffset,
collision flags and the right-side SBC's clear carry. Remove the legacy
world-coordinate contact/placement shortcut. Rider positioning stays in S8.

Dependencies are CheckPlayerVertical, GetEnemyBoundBoxOfs/Arg, geometry and
ImpedePlayerMove. Expose the box-offset argument and A-mask result needed by
this caller, keeping S9 ownership and explicit proof separation. No other
child algorithm repair or credit. Logic proof compares controlled original
NMI platform entries, full child inputs/arguments and ordered RAM writes.
Report actual-child differences separately. Operational proof uses
mysmb.platform-collision-chain, affected platform/contact regressions,
strict C90 x86/x64, DOS16 link, platform purity and three refreshed EXEs.

Owner-local ROM/listing provenance and nonredistributable containment remain.
Ignored build/m2-t42-s7 permits4,096 fixtures and150 MB raw records,20-second
process limits and resumable checkpoints. Coordinator owns cleanup after
dependent regressions. Owner-authorized three EXEs are the delivery exception;
DOS link-only and no complete-game claim. Similar-issue sweep covers replaced
coordinate heuristics, premature rider placement, linked-platform slots,
two-box restoration, side subtraction carry and live child state. All14
nodes need dual proof or accepted exact transfers; admission is no credit.

## S7 original platform collision proof

S7 P1 closes all14 expected open nodes:1,360 ->1,374/1,992.
No scoped label remains incomplete or transfers. T42 stays open; S8 is next.

| Node | Individual evidence and disposition |
| --- | --- |
| LargePlatformCollision | Initialize FF collision flag, timer/state gates, balance partner before live current slot. ROM-match complete. |
| ChkForPlayerC_LargeP | Vertical gate, explicit box argument, saved Y position and stack-preserved platform slot. ROM-match complete. |
| ExLPC | Return reloads ObjectOffset; caller uses the live slot for the balance second check. ROM-match complete. |
| SmallPlatformCollision | Timer preserves prior flag; otherwise clear flag, vertical gate and counter2. ROM-match complete. |
| ChkSmallPlatLoop | Reload ObjectOffset, consume box/mask outputs, skip offscreen or top-above20 boxes. ROM-match complete. |
| MoveBoundBox | Add80 with byte wrapping to both Y corners and decrement live RAM0. ROM-match complete. |
| ExSPC | Return after gate or two misses without restoring a box prematurely. ROM-match complete. |
| ProcSPlatCollisions | Reload ObjectOffset before entering the common small-platform response. ROM-match complete. |
| ProcLPlatCollisions | Wrapped underside difference under4 and upward speed select jump cancellation. ROM-match complete. |
| ChkForTopCollision | Wrapped top difference under6 and nonnegative speed select rider collision. ROM-match complete. |
| SetCollisionFlag | Small IDs43/44 use counter, other IDs use checked slot; store to live owner and clear player state. ROM-match complete. |
| PlatformSideCollisions | Left difference under8, then right difference minus an extra1 under9. ROM-match complete. |
| SideC | Call the existing ImpedePlayerMove with the source RAM0 side counter. ROM-match complete. |
| NoSideC | No-side return reloads ObjectOffset without extra player movement. ROM-match complete. |

All100 original instructions in $DB45-$DC16 execute, with both outcomes of
all19 branches (38/38). No adjacent data table belongs to this chain.
784 controlled entry-RAM fixtures reach the two platform collision entries
through ordinary NMI/RunLargePlatform/RunSmallPlatform. ROM code, PC, stack
and outputs are unchanged; observed and observer-free original frames agree.
Caller comparisons pass1,568/1,568 across x86/x64. Full child input RAM and
consumed box argument, geometry Y, returned carry/Y and RAM0 side counter
are checked before replaying child results. The box argument's returned Y
and low offscreen nibble are checked. CheckPlayerVertical preserves X;
geometry preserves Y; the large caller preserves its own X on the stack.
Hardware return storage is excluded; mapped $0109-$0139 remains compared.

Actual children match28/1,568. All1,540 mismatches include the existing
geometry scratch omissions at $06/$07;132 also differ at $00. Two further
semantic child gaps are explicitly retained, not hidden as scratch-only:

- Cases384 and1408 on both widths: CheckPlayerVertical incorrectly rejects
  Player_Y_High=0. Original carry remains clear on that branch. Player_State
  and PlatformCollisionFlag differ. Four comparisons; M2 T17 S6 custody,
  planned T42 S9 source admission.
- Twenty cases per width: right-side ImpedePlayerMove treats speed80 as
  negative, whereas original CPY #1 produces7F and BPL skips movement.
  Native X speed, X position and SideCollisionTimer differ. Forty comparisons;
  M2 T17 S6 custody, following player-terrain source slice. Ordinary side
  paths also retain this child's missing RAM0 high-adder write.

Neither dependency receives credit here. Generic geometry keeps its original
receiver. The box argument/result seam is exposed for this caller; S9 still
owns GetEnemyBoundBoxOfs/Arg proof. These results certify the fourteen caller
nodes, not actual whole-game equivalence or completed platform integration.

One shared enemy/platform_collision.c replaces world-coordinate contact and
premature rider-placement heuristics. Large balance decks check partner then
current; small platforms inspect two Y boxes with original wrapping. Both
use the original underside/top/side response and collision-flag rules. Rider
placement remains S8. Similar-issue review covers all callers, linked slots,
byte differences, carry, live RAM0/ObjectOffset, flags and duplicate placement.
Platform adapters are unchanged; no runtime emulator is introduced.

Native tests pass196,608 top/underside/side boundary combinations per width,
plus two-box restoration, second-deck landing, gates and child-mutated slots.
Seven focused CTests pass: collision, caller, four platform movement chains
and platform purity. Eight affected suites pass on both widths. The legacy
platform smoke lacked prepared player bounds, screen edges and object box
controls and used an uninitialized C structure. Its inputs now supply those
engine preconditions; all original movement assertions remain unchanged.
The small-platform OAM smoke receives its declaration header and fixes one
misleadingly indented return; its assertions remain unchanged.

All18,936 prior actual actor matches remain. Six previous collision matrices
retain every match:920/2,048,0/1,024,54/576,240/256,1,184/3,200 and696/2,048.
Known child and broad core/local-area failures remain explicit. All117 shared
files compile as strict C90 for x86/x64; self-tests and hidden-window response
pass. DOS16 compiles/links with the existing OLDNAMES warning. Three EXEs are
refreshed; DOS graphics/resource binding and physical486SX speed are unproved.

Reproduce platform_collision_fixture.h with --fixture=t42-platform-collision=N,
--platform-collision-snapshot, --control-children and --pc-coverage. Selected
inclusive case ranges are0-129,256-257,384-385,512-513,640-799,896-1153,
1280-1281,1408-1409,1536-1537,1664-1695,1792-1983 (784 total). Gated cases
avoid redundant geometry combinations. platform_collision_snapshot_check
proves callers; enemy_loop_actual_check tests actual children. Ignored
build/m2-t42-s7 holds bounded records and resumable checkpoints with20-second
process deadlines. Coordinator owns cleanup after dependent regressions.

Raw records: 20125007 bytes, below150 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256905 | 2b61637abc7f2343d1e72ba2e7b6180d2c36e9a09c8e9a5f9f1556485a841a09 |
| mysmb32.exe | 356145 | fcd4a63edad4d5abd68a03d74af2815a87993b49acb6a589bf98eaeb92d5ff51 |
| mysmb64.exe | 363941 | efffc377962c8bc4e8fd64c37dc2c44455625cb6696c0aff572eb633d6c96cb2 |

## S8 admission: platform positioning

S7 closed in9b02973. Coordinator accepts transfer-217 from M2 T17 S6.
Baseline1,374/1,992;4 scoped and expected-new nodes, maximum1,378:

`PlayerPosSPlatData` (open), `PositionPlayerOnS_Plat` (open), `PositionPlayerOnVPlat` (open), `ExPlPos` (open).

Original $DC17-$DC40: bind the two-byte PlayerPosSPlatData, small-entry
counter offset, overlapping BIT/LDA entries and common vertical placement.
Sole owner enemy/platform_position.c. Preserve engine11 and enemy-high-Y
exits, byte-wrapped table addition, subtraction borrow into player high Y,
vertical speed/force reset and unchanged Player_State. Replace both legacy
bodies and remove old_y compatibility metadata from the small API/caller and
test stubs. Existing movement algorithms remain independently owned.

Logic proof directly compares original leaf RAM output, with no child replay,
using ordinary NMI large/small lift routes. Capture the incoming small counter
from A. Audit both entry decodings of the BIT-overlap bytes, table binding,
branches and full RAM footprint. Native proof covers coordinate/guard/counter
boundaries, all affected platform parent contracts and actual integrations,
strict C90 x86/x64, DOS16 link, platform purity and three refreshed EXEs.

Owner-local ROM/listing provenance and nonredistributable containment remain.
Ignored build/m2-t42-s8 permits1,024 fixtures and50 MB raw records,20-second
process deadlines and checkpoints. Coordinator owns cleanup after dependent
regressions. Three owner-authorized EXEs are the delivery exception; DOS
link-only, no whole-game claim. Similar-issue sweep covers duplicate rider
placement, stale delta metadata, high-byte borrow, unintended state clearing,
entry guards and unmasked table indices. Four exact nodes need both tracks
or accepted transfers; admission is no credit.

## S8 original platform positioning proof

S8 P1 closes all four expected open nodes: 1,374 -> 1,378/1,992.
No scoped node remains incomplete or transfers. T42 remains open; S9 is next.

| Node | Individual evidence and disposition |
| --- | --- |
| PlayerPosSPlatData | Both source bytes bound at DC17; unmasked counter-minus-one indexing retains source PRG reads. ROM-match complete. |
| PositionPlayerOnS_Plat | Counter-selected wrapped height addition enters the shared tail without reloading enemy Y. ROM-match complete. |
| PositionPlayerOnVPlat | Engine11/enemy-high-Y guards, subtract20 with high-byte borrow, speed/force reset; Player_State unchanged. ROM-match complete. |
| ExPlPos | Guarded exits preserve all RAM; successful return adds no extra state or scratch writes. ROM-match complete. |

All 22 original instructions across both DC19/DC21 entry decodings execute,
with both outcomes of both branches. The DC20 BIT consumes DC21/DC22 as
its absolute operand, skipping the vertical entry's LDA for the small path.
The operand reads PRG, and BIT flags are not consumed by the placement tail.
Both table bytes at DC17 are bound. This overlapping code is audited as two
entry paths, not an incorrect single linear instruction stream.

584 controlled RAM-input cases enter through ordinary NMI large/small lift
movement. Inputs are applied before the original movement caller; it supplies
the small entry's actual A counter. No code, PC, stack, registers or output is
patched. The snapshot records incoming X/A. Original frames with and without
observers agree. Direct original-versus-native RAM comparison passes
1,168/1,168 across x86/x64, with no child substitution. Hardware return storage
is excluded; mapped $0109-$0139 remains compared. There is no remaining
scoped RAM mismatch, but this is not full-game or full-native-frame proof.

Shared enemy/platform_position.c replaces both legacy placement bodies.
Small counter1 selects +80 and counter2 +0 before wrapped height subtraction.
Engine11 and enemy-high-Y guards preserve prior player values. The subtraction
borrow updates player high Y; only Y, high Y, Y speed and move force change.
Player_State is preserved. The small API carries its original collision
counter; old_y metadata and the delta heuristic are removed from the caller
and test stubs. Source caller RAM/slot/counter assertions remain intact.
The similar-issue sweep covers every placement call, guards, borrow, table
indexing, unintended state clearing and both old duplicate bodies. Platform
adapters remain unchanged; no product emulator is introduced.

Native tests pass 393,216 full-RAM guard/height/counter cases per width.
Synthetic test-owned PRG bytes exercise every unmasked counter index, while
original-ROM cases cover both legal table entries and eight extended values.
Eight CTests pass: positioning, collision, platform caller, four movement
chains and platform purity. Eight affected suites pass on both widths.
The renamed small-child API retains 64 representative original lift-caller
contracts across both widths, including both slots and large/small paths.

The complete actual actor matrix improves 18,936 -> 21,544/29,434 without
losing a prior match. Vertical platforms now match1,024/1,024; horizontal
platforms1,536/1,536; lifts1,024/1,024. Balance platforms improve to1,920/2,048;
their 128 other child differences keep existing owners. All seven earlier
collision matrices retain their complete outcomes, including S7's vertical,
geometry and side-response gaps. Broad core/local-area limits remain.

All118 shared files compile as strict C90 for x86/x64. Product self-tests and
hidden-window response probes pass. DOS16 compiles/links with the existing
OLDNAMES warning. Three EXEs are refreshed; DOS graphics/resource binding and
physical486SX performance remain unproved.

Reproduce platform_position_fixture.h cases0..583 with
--fixture=t42-platform-position=N, --platform-position-snapshot and
--pc-coverage. enemy_loop_actual_check compares both entries directly.
Native CTest: mysmb.platform-positioning-chain. Ignored build/m2-t42-s8 holds
bounded records and checkpoints with20-second process limits; coordinator
owns cleanup after dependent regressions.

Raw records: 4978600 bytes, below50 MB.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257097 | 11c7c9d6dc359a7cd3e26fd85c614cf123aa1c7b3f1d9e29323e2136e4ea50b7 |
| mysmb32.exe | 357461 | a8286842ba3346eca4b7a41af3551a930a9012251be3dd837317ce548a56b549 |
| mysmb64.exe | 364780 | 9337dba3ee07979f650a8bb137d341d336539b236463e5d76edb22d8e78e1e89 |

## S9 admission: collision preflight

S8 closed in7d3c9da. Coordinator accepts transfer-218 from M2 T17 S6.
Baseline1,378/1,992;4 scoped and expected-new nodes, maximum1,382:
CheckPlayerVertical, ExCPV, GetEnemyBoundBoxOfs, GetEnemyBoundBoxOfsArg
(all open). Original DC41 through the return preceding PlayerBGUpperExtent.
Sole shared owner src/game/world/collision.c. Player/platform collision callers
are predecessors; generic geometry and terrain remain independent successors.

Restore original carry: offscreen >=F0 returns1; otherwise high-Y !=1 returns0;
only high-Y1 compares low Y with D0. Preserve byte-wrapped box-index multiply
and add, entry ObjectOffset versus argument, low offscreen nibble and its
compare carry. Audit every consumer and any intentionally dead A/Y/flags.
No geometry, movement or side-response repair is admitted.

Logic evidence requires original control-flow/read/write/register audit and
controlled original NMI platform/contact routes, unmodified ROM outputs and
both-width comparisons. Native evidence covers all preflight bytes, unchanged
RAM, caller regressions, strict C90 x86/x64, DOS16 link, purity and three EXEs.
Focused CTest: mysmb.collision-preflight-chain. Four labels need both tracks;
admission gives no credit. Existing source provenance: owner-local ROM and
local listing are nonredistributable research inputs only. Raw outputs remain
in ignored build/m2-t42-s9, bounded to2,048 fixtures/100 MB with20-second
process deadlines and checkpoints; coordinator owns cleanup after regressions.
Owner-authorized three EXEs remain the delivery exception. DOS link-only.
Similar-issue sweep covers all carry/offset consumers and duplicate preflight.

S9 admission gate passes: scope4, expected4, baseline1378, maximum1382;
CheckPlayerVertical, ExCPV, GetEnemyBoundBoxOfs and GetEnemyBoundBoxOfsArg
are individually confirmed open with S9 receiving ownership.

## S9 implementation checkpoint (not closure)

CheckPlayerVertical now preserves the clear CMP-F0 carry on high-Y exits.
All three production caller sites use the same shared helper: player contact,
large-platform and small-platform collision. No platform adapter changed.
The two box-offset consumers without a mask (player contact and enemy pair)
overwrite the original A/carry before use; platform consumers request the low
nibble explicitly. Their full entry/exit audit remains pending.

Both widths compile all118 shared C90 files and pass product self-tests.
Native preflight tests pass16,842,752 byte-input cases per width.
The existing S7 original child captures were compared directly against real
preflight helpers, without substituting child outputs: 2112 calls per width
pass returned carry/index/mask and mapped RAM checks. The recorded argument
entry Y is independently checked by the original recorder. This reuse does
not yet establish complete branch coverage or the ObjectOffset entry proof.
The existing S7 actual matrix retains28/1,568 matches and loses none; remaining
geometry scratch masks prevent whole-call match credit for repaired carry.

S9 stays active at1,378/1,992. No new node credit or P is claimed. Outstanding:
complete original entry/register/control-flow proof, affected and integrated
regressions, DOS link, focused CTest, refreshed three EXEs and closure gates.

## S9 original collision preflight proof

S9 P1 closes all four expected nodes:1,378 ->1,382/1,992. No transfer or
unfinished scoped label remains. T42 cross-chain closure is still pending.

| Node | Evidence and disposition |
| --- | --- |
| CheckPlayerVertical | Offscreen compare carry, high-Y early exit and low-Y compare follow original branches. ROM-match complete. |
| ExCPV | Return preserves RAM and returns original carry; A/Y are dead at every native consumer. ROM-match complete. |
| GetEnemyBoundBoxOfs | ObjectOffset entry returns original wrapped Y index; proven by original contact callers. ROM-match complete. |
| GetEnemyBoundBoxOfsArg | Argument entry preserves wrapped multiply/add and low offscreen nibble; final carry is dead in callers. ROM-match complete. |

Original DC41-DC61 contains19 instructions and two branches. Six ordinary NMI
platform routes execute all19 instructions and4 branch outcomes; observation
leaves original output frames unchanged. Existing S7/S5 child captures compare
3,648 original calls per width directly against the actual C helpers, including
both argument and ObjectOffset entries. No child output substitution occurs.
RAM is unchanged, excluding hardware stack return storage while retaining
mapped0109-0139. S7 recorder independently asserts original argument-entry Y;
S5 records the original ObjectOffset-entry Y. Six fresh routes repeat the
comparison and preserve their original code/register/stack/output state.

The original CMP-F0 carry survives LDY/DEY and the high-Y early exit. C now
returns0 there; only on-screen high-Y1 reaches CMP-D0. This repairs missing
landing/state writes in S7 cases384/1408 on both widths. Their remaining RAM6/7
geometry differences stay with the existing geometry owner. The actual S7
matrix keeps28/1,568 matches; this change does not claim geometry completion.

Box offset entries wrap byte multiply-by-four plus4, with RAM8 loaded only at
the ObjectOffset entry. The argument helper returns the low offscreen nibble.
Original final CMP-0F carry is dead: large platforms overwrite it in geometry,
small platforms use AND2 then CMP or CLC, player contact overwrites in geometry,
and enemy pairs overwrite before their comparison. Vertical A/Y are dead at
all three consumers; X and RAM are preserved. The similar-issue sweep found
only these shared helpers and their player-contact, enemy-pair and platform
consumers; no duplicate host gameplay or unrelated collision repair was added.

Native exhaustive preflight tests pass16,842,752 cases per width; these are
separate from original-ROM evidence. Four CTests pass, including platform
purity, and eight affected suites pass on both widths. All21,544 prior actual
actor matches remain out of29,434, and all earlier collision matches remain.
No whole-game equivalence claim follows from these scoped results.

All118 shared C90 sources compile on x86/x64; self-tests and hidden-window
response probes pass. DOS16 compiles/links with the pre-existing OLDNAMES
warning. Three EXEs are refreshed. DOS graphics/resource binding and physical
486SX performance remain unproved. Source-derived inputs and traces remain
ignored under build; no ROM or raw trace is committed.

Reproduce native test mysmb.collision-preflight-chain. Original checks use
collision_preflight_snapshot_check with S7 platform and S5 contact child files;
for fresh routes use t42-platform-collision cases0,384,385,512,1024,1536 with
platform-collision-snapshot, control-children and pc-coverage. Ignored
build/m2-t42-s9 holds bounded evidence and checkpoints; coordinator owns cleanup.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257097 | 4b900ebd7e178bb376c1a1db771d2e636761f46f29b33ab3d397e61f2564e2d8 |
| mysmb32.exe | 357461 | 56e6eb623e78829b2cc0533f1fa97ffc5f0d0d171ef921f678efad908334b0b8 |
| mysmb64.exe | 364780 | 18db2d672ad004f57f2d1688037bc5b0b180a5ac709e8243c1ebbd745caf1d6c |

## T42 closure

T42 S9 P2 completes the task-wide review following b89f02e; no new S,
node credit or implementation change is introduced. All nine chains close
all98 planned nodes, bringing conformance from1,284 to1,382/1,992. The exact
plan labels equal the union of S scopes, each expected label equals its actual
match, and every label remains with its explicit maintenance receiver.
No scoped unfinished node or transfer remains. External dependencies receive
no credit; their original source-order owners retain responsibility.

| Chain | Planned / completed nodes | Original logic evidence |
| --- | ---: | --- |
| S1 fireball scan | 6/6 | 2,048 caller comparisons |
| S2 fireball hit | 11/11 | 1,024 caller comparisons |
| S3 hammer contact | 3/3 | 576 caller comparisons |
| S4 pickup | 6/6 | 256 caller comparisons |
| S5 player contact | 34/34 | 3,200 caller comparisons |
| S6 enemy pairs | 16/16 | 2,048 caller comparisons |
| S7 platform collision | 14/14 | 1,568 caller comparisons |
| S8 rider positioning | 4/4 | 1,168 direct comparisons |
| S9 preflight | 4/4 | 3,648 direct original calls per width |

Accepted individual branch/table/read/write/call proofs above are retained.
Caller substitution proves only a caller after complete input checks; it does
not certify a descendant. The actual-child matrix on the final S9 source is:

| Collision chain | Actual matches / comparisons |
| --- | ---: |
| fireball-enemy-scan | 920/2048 |
| fireball-hit | 0/1024 |
| hammer-contact | 54/576 |
| powerup-pickup | 240/256 |
| player-enemy-contact | 1184/3200 |
| enemy-pair | 696/2048 |
| platform-collision | 28/1,568 |

Remaining collision differences retain geometry RAM6/7, stun/palette RAM0,
side-response and other recorded child ownership. S9 fixed four high-Y carry
samples' landing/state writes, but geometry scratch still prevents those
whole calls matching. These sample counts are not unfinished node counts.

| Actor route family | Actual matches / comparisons |
| --- | ---: |
| loop | 192/192 |
| stream | 160/160 |
| init | 220/220 |
| common | 104/104 |
| spiny | 160/160 |
| firebar | 80/80 |
| fish | 304/304 |
| bowser-flame | 320/320 |
| fireworks | 240/240 |
| bullet-swim | 364/364 |
| group | 230/230 |
| small-init | 392/392 |
| platform-init | 480/480 |
| actor-dispatch | 46/360 |
| normal-actor | 88/252 |
| special-actor | 56/184 |
| podoboo | 128/128 |
| hammer-movement | 712/712 |
| paratroopa | 320/320 |
| green-counter | 576/576 |
| bloober | 1024/1024 |
| bullet-movement | 256/256 |
| swimming-cheep | 1024/1024 |
| firebar-chain | 300/1024 |
| flying-cheep-movement | 1024/1024 |
| lakitu-movement | 2048/2048 |
| bridge-collapse | 72/360 |
| bowser-control | 16/2048 |
| bowser-graphics | 0/1024 |
| flame-actor | 8/2048 |
| fireworks-lifetime | 472/1024 |
| star-flag | 1552/2048 |
| piranha-movement | 1024/1024 |
| balance-platform | 1920/2048 |
| vertical-platform | 1024/1024 |
| horizontal-platform | 1536/1536 |
| lift-platform | 1024/1024 |
| offscreen-bounds | 2048/2048 |

Total21,544/29,434 actual actor comparisons match. All18,928 matches at T41
closure remain, with2,616 additional matches in T42. The7,890 remaining sample
differences retain independently owned graphics, relative/offscreen, geometry,
status and actor-child gaps. Whole-game and full-native-frame equivalence
remain unproved. Scope closure does not close M2 or conceal those dependencies.

Final integrated evidence reuses the S9 source/artifacts: all118 shared C90
units compile on x86/x64, both self-tests and hidden-window probes pass,
DOS16 links, eight affected suites pass per width, and the final actual actor
matrix plus prior collision matrices retain all previous matches. The nine
T42 native chain CTests and platform purity pass together10/10 in the task-wide
run. No gameplay implementation changed after this delivery; hashes in the S9
artifact table match assets. No extra compile cycle is needed for this record.
DOS graphics/resource binding and physical486SX performance remain unproved.

T42 is closed. M2 remains active at1,382/1,992. The next source slice is
PlayerBGUpperExtent through line13000:148 player terrain nodes. It receives
its exact S plan and admission before implementation. Historical labels and
numbers are preserved; no later T is admitted by this closure.
