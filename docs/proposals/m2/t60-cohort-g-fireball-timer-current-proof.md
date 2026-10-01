# M2 T60: Cohort G fireballs, bubbles and timers current-equivalence proof
T60 follows closed T59 in the owner-approved source order. It audits 49 labels from `ProcFireball_Bubble` through `VineHeightData`. Historical accounting remains 1,992 / 1,992; this task records fresh current shared-C evidence only.
## Task scope and closure
Every chain needs static ROM comparison, controlled original-ROM/current x86/x64 proof, focused native verification, shared OpenNT DOS16 link and platform purity. A shared source repair refreshes all three assets. A feasible mismatch stays in its S until repaired and re-audited. S9 supplies T-level cross-chain proof.
## Planned source-order S chains
| S | Entry to exit | Labels | Shared C owner |
| --- | --- | ---: | --- |
| S1 | `ProcFireball_Bubble -> BublExit` | 5 | src/game/fireball/fireball_spawn.c; src/game/fireball/bubble.c |
| S2 | `FireballXSpdData -> FireballExplosion` | 6 | src/game/fireball/fireball_core.c with declared world/OAM child boundaries |
| S3 | `BubbleCheck -> BubbleTimerData` | 8 | src/game/fireball/bubble.c |
| S4 | `RunGameTimer -> WarpZoneObject` | 5 | src/game/timer.c and shared world owner |
| S5 | `ProcessWhirlpools -> WhPull` | 8 | src/game/whirlpool.c |
| S6 | `FlagpoleScoreMods -> ExitFlagP` | 7 | src/game/enemy/star_flag.c; src/game/oam/flagpole_gfx.c |
| S7 | `Jumpspring_Y_PosData -> ExJSpring` | 7 | src/game/jumpspring.c with declared OAM child boundary |
| S8 | `Setup_Vine -> VineHeightData` | 3 | src/game/vine.c |
| S9 | `Cohort G cross-chain closure` | 0 | shared game owners only |

## Exact node scope
| ROM node | S | Current state |
| --- | --- | --- |
| `ProcFireball_Bubble` | S1 | `needs-evidence` |
| `ProcFireballs` | S1 | `needs-evidence` |
| `ProcAirBubbles` | S1 | `needs-evidence` |
| `BublLoop` | S1 | `needs-evidence` |
| `BublExit` | S1 | `needs-evidence` |
| `FireballXSpdData` | S2 | `needs-evidence` |
| `FireballObjCore` | S2 | `needs-evidence` |
| `RunFB` | S2 | `needs-evidence` |
| `EraseFB` | S2 | `needs-evidence` |
| `NoFBall` | S2 | `needs-evidence` |
| `FireballExplosion` | S2 | `needs-evidence` |
| `BubbleCheck` | S3 | `needs-evidence` |
| `SetupBubble` | S3 | `needs-evidence` |
| `PosBubl` | S3 | `needs-evidence` |
| `MoveBubl` | S3 | `needs-evidence` |
| `Y_Bubl` | S3 | `needs-evidence` |
| `ExitBubl` | S3 | `needs-evidence` |
| `Bubble_MForceData` | S3 | `needs-evidence` |
| `BubbleTimerData` | S3 | `needs-evidence` |
| `RunGameTimer` | S4 | `needs-evidence` |
| `ResGTCtrl` | S4 | `needs-evidence` |
| `TimeUpOn` | S4 | `needs-evidence` |
| `ExGTimer` | S4 | `needs-evidence` |
| `WarpZoneObject` | S4 | `needs-evidence` |
| `ProcessWhirlpools` | S5 | `needs-evidence` |
| `WhLoop` | S5 | `needs-evidence` |
| `NextWh` | S5 | `needs-evidence` |
| `ExitWh` | S5 | `needs-evidence` |
| `WhirlpoolActivate` | S5 | `needs-evidence` |
| `LeftWh` | S5 | `needs-evidence` |
| `SetPWh` | S5 | `needs-evidence` |
| `WhPull` | S5 | `needs-evidence` |
| `FlagpoleScoreMods` | S6 | `needs-evidence` |
| `FlagpoleScoreDigits` | S6 | `needs-evidence` |
| `FlagpoleRoutine` | S6 | `needs-evidence` |
| `SkipScore` | S6 | `needs-evidence` |
| `GiveFPScr` | S6 | `needs-evidence` |
| `FPGfx` | S6 | `needs-evidence` |
| `ExitFlagP` | S6 | `needs-evidence` |
| `Jumpspring_Y_PosData` | S7 | `needs-evidence` |
| `JumpspringHandler` | S7 | `needs-evidence` |
| `DownJSpr` | S7 | `needs-evidence` |
| `PosJSpr` | S7 | `needs-evidence` |
| `BounceJS` | S7 | `needs-evidence` |
| `DrawJSpr` | S7 | `needs-evidence` |
| `ExJSpring` | S7 | `needs-evidence` |
| `Setup_Vine` | S8 | `needs-evidence` |
| `NextVO` | S8 | `needs-evidence` |
| `VineHeightData` | S8 | `needs-evidence` |

## S1 admission - fireball and bubble dispatch chain
S1 admits `ProcFireball_Bubble`, `ProcFireballs`, `ProcAirBubbles`, `BublLoop` and `BublExit`. It owns the PlayerStatus partition, spawn call, ordered two-slot core calls, water-only bubble partition, descending bubble loop and caller return. S2 owns fireball-core bodies; S3 owns bubble state/movement. Historical receivers retain custody because this is an audit overlap.

Current registry baseline is 641 exact labels and 1,238 exact feasible controls. Five scoped labels are `needs-evidence`; S1 expects those five current promotions, reaching at most 646. Historical expected matches are empty because historical conformance is already 1,992 / 1,992.

**ROM-logic track.** Compare original lines 6298-6348 with shared C, including PlayerStatus, spawn eligibility, slot ordering, water branch, descending loop and returns. Replay controlled original-ROM/current x86/x64 GameEngine fireball and water-bubble entries, recording child boundaries.

**Operational track.** Run focused x86/x64 C90 dispatch routes and smoke checks, shared DOS16 link and platform purity. A source repair builds and validates all three product executables.

## S1 closure criteria
All five labels and owned feasible relations are current-exact. Any difference is repaired in the shared game owner and re-audited before S2.

## S1 closure - fireball and bubble dispatch chain

All five scoped labels are current-exact. Static review of original source lines 6298-6348 found no feasible difference in the shared dispatch owner. Thirty-two controlled original-ROM routes begin at an ordinary NMI boundary, alter only source-read RAM, and reach `GameMode -> GameCoreRoutine -> GameEngine -> ProcFireball_Bubble` through the original stack. They cover both outcomes of all nine dispatch branches. Fresh x86/x64 checks replayed 64 observed immediate-child boundaries and 64 actual shared-C executions; every comparison of the 1,784 persistent game-RAM bytes matched, and x86/x64 results were identical. The child bodies remain S2/S3 responsibility; S1 proves their call, return, slot and ordering boundary only.

The closure promotes `ProcFireball_Bubble`, `ProcFireballs`, `ProcAirBubbles`, `BublLoop` and `BublExit`, plus 25 feasible caller, branch, fall-through and return relations. Registry count: 641 -> 646 exact labels and 1,238 -> 1,263 exact feasible relations. Historical accounting remains 1,992 / 1,992. The focused strict-C90 dispatch smoke, OpenNT DOS16 link and platform-purity audit pass. No product source changed, so no three-executable refresh is due.

## S2 admission - fireball core state chain

S2 admits `FireballXSpdData`, `FireballObjCore`, `RunFB`, `EraseFB`, `NoFBall` and `FireballExplosion`: the contiguous `$B687-$B6F8` core chain. It owns the two speed bytes; high-bit, zero and one state partition; X-plus-four page carry; initialization decrement; gravity/movement child order; background `$cc` erase gate; and explosion tail. It depends on S1's two ordered caller slots and hands bubble logic to S3. Current registry baseline is 646 exact labels and 1,263 exact feasible controls; these six labels and their core-only relations are `needs-evidence`, with a maximum of 652 labels after successful current audit. Historical expected matches remain empty because historical conformance is already 1,992 / 1,992.

ROM-logic proof will use controlled ordinary-NMI routes through the same GameEngine caller for inactive, initialization, active, carry, offscreen and explosion cases, recording immediate-child boundaries. Operational proof will use strict-C90 x86/x64 core checks, DOS16 link and platform purity. Any feasible core difference is repaired in the shared owner and re-audited before S3.

## S2 closure - fireball core state chain

All six scoped labels are current-exact. Static review of original lines 6349-6408 found no feasible difference in `src/game/fireball/fireball_core.c`: the two speed bytes, high-bit/zero/one state partition, X-plus-four carry to page, state decrement, slot-plus-seven movement, ObjectOffset reload, fixed child sequence, `$cc` erase gate and explosion tail follow the original. Thirty-two ordinary-NMI GameEngine routes cover both outcomes of all four core branches. Fresh x86/x64 results contain 64 matching observed-child boundary replays and 64 matching actual shared-C executions across the persistent game RAM. The independent strict-C90 smoke exhausts 5,120 state/facing/carry cases, all 256 offscreen masks and the ObjectOffset reload path.

The closure promotes `FireballXSpdData`, `FireballObjCore`, `RunFB`, `EraseFB`, `NoFBall` and `FireballExplosion`, plus 24 feasible control relations. Registry count: 646 -> 652 exact labels and 1,263 -> 1,287 exact feasible relations. Historical accounting remains 1,992 / 1,992. DOS16 links and platform purity passes. No product source changed, so no three-executable refresh is due.

## S3 admission - bubble state and movement chain

S3 admits `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`, `Y_Bubl`, `ExitBubl`, `Bubble_MForceData` and `BubbleTimerData`, the contiguous `$B6F9-$B74E` bubble body. It owns the random-bit selection, inactive sentinel, timer gate, facing carry into placement, page carry, fractional borrow, status-bar cutoff and both tables. Current registry baseline is 652 exact labels and 1,287 exact feasible controls; these eight labels are `needs-evidence`, with a maximum of 660 labels after a successful current audit. Historical expected matches remain empty because historical conformance is already 1,992 / 1,992. The ROM route will use ordinary-NMI water-area GameEngine entries and record the BubbleCheck, relative-position, offscreen and draw caller boundaries. Any feasible difference remains in S3 for shared-owner repair and re-audit before S4.

## S3 closure - bubble state and movement chain

All eight scoped labels are current-exact. Static comparison of `SMBDIS.ASM` `$B6F9-$B74E` against `src/game/fireball/bubble.c` found no feasible difference: `BubbleCheck` writes the random bit before its active/sentinel/timer partition; `SetupBubble` retains the facing carry through X/page placement; both tables bind exactly; the selected fractional subtraction carries its borrow into Y; and the `< $20` cutoff writes `$f8`.

Thirty controlled ordinary-NMI water-area fixtures entered the original GameEngine path. They cover both direct entries, all three slots, both pseudo-random selections and both outcomes of every branch at `$B704`, `$B709`, `$B710` and `$B744`. The retained owner-local route snapshots replayed through the actual shared C owner on x86 and x64: all 60 comparisons match over 1,785 persistent RAM bytes, with no child substitution. The strict C90 entry smoke covers 18,432 cases per width, including carry, page wrap, borrow, sentinel and timer-idle cases. The shared OpenNT DOS16 link and platform-purity audit pass.

The closure promotes `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`, `Y_Bubl`, `ExitBubl`, `Bubble_MForceData` and `BubbleTimerData`, plus 11 feasible caller, branch, fall-through and return relations. Current registry count: 652 -> 660 exact labels and 1,287 -> 1,298 exact feasible control relations. Historical accounting remains 1,992 / 1,992. No product source changed, so no three-executable refresh is due.

## S4 admission - game timer and warp chain

S4 admits `RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer` and `WarpZoneObject`, the contiguous timer/warp handoff from `$B74F` through `$B7A2`. It owns title/death/player-high early exits, timer cadence, digit decrement and underflow effects, time-up latch/audio transfer, and the area-object warp-zone transfer. S3 is its predecessor; S5 owns the following whirlpool branch. Current registry baseline is 660 exact labels and 1,298 exact feasible controls; all five scoped labels are `needs-evidence`. Historical expected matches remain empty because historical conformance is already 1,992 / 1,992. The ROM logic track will use controlled ordinary-NMI modes for every early exit, timer decrement/underflow and warp object route; the operational track will run focused strict-C90 x86/x64 checks, shared DOS16 link and platform purity. Any feasible difference remains in S4 for shared-owner repair and re-audit before S5.

## S4 closure - game timer and warp chain

All five scoped labels are current-exact. Static comparison of `SMBDIS.ASM` `$B74F-$B7B2` found no feasible difference in the shared owners. `timer.c` preserves every mode/death/high-Y/control-timer exit, zero-timer transition, time-running-out queue condition, timer reload, digit decrement, status queue, time-up injury and expiration increment. `enemy/core.c` preserves the WarpZoneObject scroll-lock and bitwise Y predicate, then clears the lock, increments the zone control and tails into the shared enemy eraser.

The timer proof exercises 16 controlled ordinary-NMI entries, both outcomes of all eight source branches and observed original child boundaries. All 32 x86/x64 actual shared-C runs match the 1,791 compared persistent bytes. The Warp Zone proof covers ten ordinary-NMI routes, both source branches, all six active slots, dispatcher vector binding and the erase tail; its 20 x86/x64 frame records match all compared persistent RAM and output. Strict C90 builds, shared OpenNT DOS16 link and platform purity pass.

The closure promotes `RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer` and `WarpZoneObject`, plus 19 feasible caller, branch, fall-through, tail-jump and return relations. Current registry count: 660 -> 665 exact labels and 1,298 -> 1,317 exact feasible control relations. Historical accounting remains 1,992 / 1,992. No product source changed, so no three-executable refresh is due.

## S5 admission - whirlpool chain

S5 admits `ProcessWhirlpools`, `WhLoop`, `NextWh`, `ExitWh`, `WhirlpoolActivate`, `LeftWh`, `SetPWh` and `WhPull`, the contiguous `$B7B3-$B80B` water-area movement chain. It owns water/timer gating, reverse whirlpool scan, page-aware extent comparisons, center calculation, frame-parity lateral pull, collision-bit gate and vertical pull setup. S4 is its predecessor and S6 owns the following flagpole chain. Current registry baseline is 665 exact labels and 1,317 exact feasible controls; all eight scoped labels need evidence. Historical expected matches remain empty because historical conformance is already 1,992 / 1,992. ROM logic proof will use ordinary-NMI water/non-water and extent/center/collision routes; operational proof will use strict-C90 x86/x64 routes, shared DOS16 link and platform purity. Any feasible difference remains in S5 for shared-owner repair and re-audit before S6.

## S5 closure - whirlpool chain

All eight scoped labels are current-exact. Static comparison of `SMBDIS.ASM` `$B7B3-$B84A` against `src/game/whirlpool.c` found no feasible difference: water and master-timer exits, descending slot loop, page-aware left/right comparisons, center carry, alternating-frame pull, collision-bit gate and the `WhPull` gravity tail retain source order and byte semantics.

Twelve controlled ordinary-NMI routes cover water/non-water and timer gates, missing/left/right/inside extent paths, page wraps, center-side pulls, collision gate and overlapping-slot precedence. All nine source branches take both outcomes. The 24 x86/x64 records match the original ROM across 1,782 persistent RAM bytes and output, and x86/x64 records are byte-identical. The strict C90 exhaustive smoke, shared OpenNT DOS16 link and platform-purity audit pass.

The closure promotes `ProcessWhirlpools`, `WhLoop`, `NextWh`, `ExitWh`, `WhirlpoolActivate`, `LeftWh`, `SetPWh` and `WhPull`, plus 16 feasible branch, loop, jump and tail relations. Current registry count: 665 -> 673 exact labels and 1,317 -> 1,333 exact feasible control relations. Historical accounting remains 1,992 / 1,992. No product source changed, so no three-executable refresh is due.

## S6 admission - flagpole chain

S6 admits `FlagpoleScoreMods`, `FlagpoleScoreDigits`, `FlagpoleRoutine`, `SkipScore`, `GiveFPScr`, `FPGfx` and `ExitFlagP`, the contiguous `$B84B-$B8B9` flag-and-score chain. It owns table selection, slot-five flag identification, slide/climb/height gates, fractional flag/floatey movement, score award, next-task handoff and OAM-child ordering. S5 is its predecessor; S7 owns jumpspring. Current registry baseline is 673 exact labels and 1,333 exact feasible controls; all seven scoped labels need evidence. Historical expected matches remain empty because historical conformance is already 1,992 / 1,992. ROM proof will use ordinary-NMI flag states and controlled score/height paths; operational proof will use strict-C90 x86/x64 routes, shared DOS16 link and platform purity. Any feasible difference remains in S6 for shared-owner repair and re-audit before S7.

## S6 closure - flagpole chain

All seven scoped labels are current-exact. Static comparison of `SMBDIS.ASM` `$B84B-$B8B9` against `src/game/oam/flagpole_gfx.c` found no feasible difference: slot five is assigned before the flag-ID predicate; task/state and both height gates retain their source polarity; the two score tables bind exactly; the dummy-byte carry and borrow move the flag and floatey number in source order; and the score, task handoff, offscreen, relative-position and graphics children remain ordered as in the ROM. `HandleClimbing` is the preceding score writer and confines the reachable score index to 0-4.

Two controlled ordinary-NMI routes exercise the real flagpole object and the slide-to-score transition. Across four frames per route, all 16 original-ROM/current x86/x64 comparisons match 1,782 persistent bytes and complete output; x86 and x64 records are byte-identical. The original route covers both outcomes of the flag-ID and task gates, while focused score/OAM smokes cover the complementary player-state path, fractional motion, offscreen path and all five legal table indices on both widths. The shared OpenNT DOS16 link and platform-purity audit pass.

The closure promotes `FlagpoleScoreMods`, `FlagpoleScoreDigits`, `FlagpoleRoutine`, `SkipScore`, `GiveFPScr`, `FPGfx` and `ExitFlagP`, two material score-table edges and 17 feasible branch, call, fall-through and return relations. Current registry count: 673 -> 680 exact labels and 1,333 -> 1,350 exact feasible control relations. Historical accounting remains 1,992 / 1,992. No product source changed, so no three-executable refresh is due.

## S7 admission - jumpspring chain

S7 admits `Jumpspring_Y_PosData`, `JumpspringHandler`, `DownJSpr`, `PosJSpr`, `BounceJS`, `DrawJSpr` and `ExJSpring`, the contiguous `$B8BA-$B8F7` jumpspring chain. It owns the frame-indexed Y table, timer/animation gates, two-pixel player movement, fixed spring positioning, new-A-button bounce predicate, force handoff, relative-position/draw order and return. S6 is its predecessor and S8 owns the following vine setup. Current registry baseline is 680 exact labels and 1,350 exact feasible controls; all seven scoped labels need evidence. Historical expected matches remain empty because historical conformance is already 1,992 / 1,992. ROM proof will use ordinary-NMI spring animation routes and controlled new-button/force paths; operational proof will use focused x86/x64 smoke, shared DOS16 link and platform purity. Any feasible difference remains in S7 for shared-owner repair and re-audit before S8.

## S7 closure - jumpspring chain

All seven scoped labels are current-exact. Static comparison of `SMBDIS.ASM` `$B8B6-$B91D` against `src/game/jumpspring.c` found no feasible difference: the four Y bytes bind after `JumpspringAnimCtrl - 1`; the timer and animation gates preserve their source polarity; the player moves exactly two pixels before the shared position path; the A predicate accepts only a newly pressed A bit; final frame transfers `JumpspringForce` then clears animation; and relative position, OAM, offscreen bounds and timer advance retain source order. The OAM child remains a declared ownership boundary; its focused smoke passes.

Thirty-two fresh controlled original-ROM paths cover both outcomes of all nine source branches. Fresh x86 and x64 current-C caller-boundary checks replay all 64 observed calls and match 1,791 persistent bytes. The direct chain smoke covers 480 timer/animation/button/slot cases per width, the origin-offscreen smoke passes on both widths, the OAM smoke passes on both widths, the shared OpenNT DOS16 link succeeds, and platform-purity passes. The source-order dispatcher edge `JmpEO -> JumpspringHandler` remains with its dispatcher owner and is not credited here.

The closure promotes `Jumpspring_Y_PosData`, `JumpspringHandler`, `DownJSpr`, `PosJSpr`, `BounceJS`, `DrawJSpr` and `ExJSpring`, material edge `material-00094`, and 22 owned feasible call, branch, jump, fall-through and return relations. Current registry count: 680 -> 687 exact labels and 1,350 -> 1,372 exact feasible control relations. Historical accounting remains 1,992 / 1,992. No product source changed, so no three-executable refresh is due.

## S8 admission - vine setup chain

S8 admits `Setup_Vine`, `NextVO` and `VineHeightData`, the contiguous `$B91E-$B94A` vine-setup chain. It owns vine object ID/flag and block-coordinate copies, the zero-offset start-Y conditional, vine-object registration/increment, grow-sound queue and source return; it also proves the two raw height-table bytes. S7 is its predecessor; later `VineObjectHandler` owns table consumption and all growth behavior. Current registry baseline is 687 exact labels and 1,372 exact feasible controls; the three scoped labels need evidence. Historical expected matches remain empty because historical conformance is already 1,992 / 1,992. ROM proof will use controlled ordinary-NMI vine-setup routes for zero/nonzero flag offsets, block coordinates, registration and initialization paths; operational proof will use focused x86/x64 smoke, shared DOS16 link and platform purity. Any feasible difference remains in S8 for shared-owner repair and re-audit before S9.

## S8 closure - vine setup chain

All three scoped labels are current-exact. Static comparison of `SMBDIS.ASM` `$B91E-$B94A` against `src/game/vine.c` found no feasible difference: object ID/flag and block page/X/Y copies retain source order; only a zero `VineFlagOffset` writes `VineStart_Y_Position`; registration uses the pre-increment offset; the offset increments with byte wrap; the grow-vine sound queue is `$04`; and the two raw height bytes are `$30,$60`. `VineObjectHandler` owns later table consumption and was deliberately excluded.

Sixteen fresh controlled original-ROM entries cover both offset-branch outcomes and registrations 0, 1, 2 and 255. Thirty-two actual x86/x64 shared-C returns match all 1,791 persistent bytes, with no child substitution. The focused setup smoke runs 12,288 complete-write-footprint cases per width; the shared OpenNT DOS16 link and platform-purity audit pass.

The closure promotes `Setup_Vine`, `NextVO` and `VineHeightData`, plus four owned branch and return relations. Current registry count: 687 -> 690 exact labels and 1,372 -> 1,376 exact feasible control relations. Historical accounting remains 1,992 / 1,992. No product source changed, so no three-executable refresh is due.

## S9 admission - Cohort G cross-chain closure

S9 has zero node credit. It owns T60 integration only: verify the nine closed chains together, reconcile their immediate boundaries and deferred dispatcher/material ownership, run the Cohort G route matrix on x86/x64, perform the final shared DOS16 link and platform-purity audit, and produce the T60 closure record. The 49 exact labels remain attributed to S1-S8. Any cross-chain discrepancy reopens its owning chain rather than receiving new S9 node credit.
