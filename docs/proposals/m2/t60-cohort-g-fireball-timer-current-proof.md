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
