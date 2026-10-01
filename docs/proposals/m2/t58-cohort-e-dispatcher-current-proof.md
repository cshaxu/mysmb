# M2 T58: Cohort E dispatcher, control and transition current-equivalence proof
T58 continues the approved source-order proof program immediately after T57. It audits the 79 Cohort-E labels from `GameMode` through `ExitNA`. Historical ROM-match accounting remains 1,992 / 1,992; this task records fresh current ROM-logic and operational evidence only.
## Task scope and closure
T58 closes only after each scoped label and each feasible relation incident to its six chains is current-exact. Each S performs its source comparison, any required shared-C repair, original-ROM/current x86/x64 controlled-route comparison, focused native verification and platform-purity check. A product-source repair also links the shared DOS16 core and refreshes all three target artifacts. A feasible difference stays in its owning S until the same route and static audit are clean.
## Planned source-order S chains
| S | Entry to exit | Labels | Shared C owner and common route |
| --- | --- | ---: | --- |
| S1 | `GameMode -> ExitEng` | 11 | src/game/dispatcher.c, src/game/engine.c, src/game/engine_slots.c, src/game/engine_tail.c; GameMode selector and controlled GameEngine frame route. |
| S2 | `ScrollHandler -> GetScreenPosition` | 10 | src/game/player.c and shared scroll owner; scroll threshold, page-crossing and player-on/off-screen matrix. |
| S3 | `GameRoutines -> CloudExit` | 23 | src/game/entry.c, src/game/player_control.c, src/game/player.c; normal, pipe, vine and cloud-entry control matrix. |
| S4 | `Vine_AutoClimb -> RightPipe` | 11 | src/game/player_transition.c and src/game/player/pipe_entry.c; vine auto-climb and both pipe directions matrix. |
| S5 | `PlayerChangeSize -> ExitDeath` | 14 | src/game/player_modes.c and src/game/player.c; grow, shrink, injury blink and death timing matrix. |
| S6 | `FlagpoleSlide -> ExitNA` | 10 | src/game/player_end_level.c and src/game/player_transition.c; flagpole descent, castle/end-level and next-area matrix. |

## Exact node scope

| ROM line | Node | Planned S | Current state |
| ---: | --- | --- | --- |
| 5315 | `GameMode` | S1 | `needs-evidence` |
| 5326 | `GameCoreRoutine` | S1 | `needs-evidence` |
| 5336 | `GameEngine` | S1 | `needs-evidence` |
| 5339 | `ProcELoop` | S1 | `needs-evidence` |
| 5371 | `NoChgMus` | S1 | `needs-evidence` |
| 5377 | `CycleTwo` | S1 | `needs-evidence` |
| 5380 | `ClrPlrPal` | S1 | `needs-evidence` |
| 5381 | `SaveAB` | S1 | `needs-evidence` |
| 5385 | `UpdScrollVar` | S1 | `needs-evidence` |
| 5398 | `RunParser` | S1 | `needs-evidence` |
| 5399 | `ExitEng` | S1 | `needs-evidence` |
| 5403 | `ScrollHandler` | S2 | `needs-evidence` |
| 5422 | `ChkNearMid` | S2 | `needs-evidence` |
| 5427 | `ScrollScreen` | S2 | `needs-evidence` |
| 5451 | `InitScrlAmt` | S2 | `needs-evidence` |
| 5453 | `ChkPOffscr` | S2 | `needs-evidence` |
| 5463 | `KeepOnscr` | S2 | `needs-evidence` |
| 5475 | `InitPlatScrl` | S2 | `needs-evidence` |
| 5479 | `X_SubtracterData` | S2 | `needs-evidence` |
| 5482 | `OffscrJoypadBitsData` | S2 | `needs-evidence` |
| 5487 | `GetScreenPosition` | S2 | `needs-evidence` |
| 5499 | `GameRoutines` | S3 | `needs-evidence` |
| 5519 | `PlayerEntrance` | S3 | `needs-evidence` |
| 5532 | `ChkBehPipe` | S3 | `needs-evidence` |
| 5536 | `IntroEntr` | S3 | `needs-evidence` |
| 5541 | `EntrMode2` | S3 | `needs-evidence` |
| 5549 | `VineEntr` | S3 | `needs-evidence` |
| 5562 | `OffVine` | S3 | `needs-evidence` |
| 5567 | `PlayerRdy` | S3 | `needs-evidence` |
| 5575 | `ExitEntr` | S3 | `needs-evidence` |
| 5580 | `AutoControlPlayer` | S3 | `needs-evidence` |
| 5583 | `PlayerCtrlRoutine` | S3 | `needs-evidence` |
| 5595 | `DisJoyp` | S3 | `needs-evidence` |
| 5597 | `SaveJoyp` | S3 | `needs-evidence` |
| 5615 | `SizeChk` | S3 | `needs-evidence` |
| 5623 | `ChkMoveDir` | S3 | `needs-evidence` |
| 5629 | `SetMoveDir` | S3 | `needs-evidence` |
| 5630 | `PlayerSubs` | S3 | `needs-evidence` |
| 5649 | `PlayerHole` | S3 | `needs-evidence` |
| 5661 | `HoleDie` | S3 | `needs-evidence` |
| 5670 | `HoleBottom` | S3 | `needs-evidence` |
| 5672 | `ChkHoleX` | S3 | `needs-evidence` |
| 5680 | `ExitCtrl` | S3 | `needs-evidence` |
| 5682 | `CloudExit` | S3 | `needs-evidence` |
| 5691 | `Vine_AutoClimb` | S4 | `needs-evidence` |
| 5697 | `AutoClimb` | S4 | `needs-evidence` |
| 5702 | `SetEntr` | S4 | `needs-evidence` |
| 5708 | `VerticalPipeEntry` | S4 | `needs-evidence` |
| 5722 | `MovePlayerYAxis` | S4 | `needs-evidence` |
| 5730 | `SideExitPipeEntry` | S4 | `needs-evidence` |
| 5733 | `ChgAreaPipe` | S4 | `needs-evidence` |
| 5736 | `ChgAreaMode` | S4 | `needs-evidence` |
| 5740 | `ExitCAPipe` | S4 | `needs-evidence` |
| 5742 | `EnterSidePipe` | S4 | `needs-evidence` |
| 5751 | `RightPipe` | S4 | `needs-evidence` |
| 5757 | `PlayerChangeSize` | S5 | `needs-evidence` |
| 5762 | `EndChgSize` | S5 | `needs-evidence` |
| 5765 | `ExitChgSize` | S5 | `needs-evidence` |
| 5769 | `PlayerInjuryBlink` | S5 | `needs-evidence` |
| 5776 | `ExitBlink` | S5 | `needs-evidence` |
| 5778 | `InitChangeSize` | S5 | `needs-evidence` |
| 5786 | `ExitBoth` | S5 | `needs-evidence` |
| 5791 | `PlayerDeath` | S5 | `needs-evidence` |
| 5797 | `DonePlayerTask` | S5 | `needs-evidence` |
| 5804 | `PlayerFireFlower` | S5 | `needs-evidence` |
| 5812 | `CyclePlayerPalette` | S5 | `needs-evidence` |
| 5821 | `ResetPalFireFlower` | S5 | `needs-evidence` |
| 5824 | `ResetPalStar` | S5 | `needs-evidence` |
| 5830 | `ExitDeath` | S5 | `needs-evidence` |
| 5835 | `FlagpoleSlide` | S6 | `needs-evidence` |
| 5847 | `SlidePlayer` | S6 | `needs-evidence` |
| 5848 | `NoFPObj` | S6 | `needs-evidence` |
| 5853 | `Hidden1UpCoinAmts` | S6 | `needs-evidence` |
| 5856 | `PlayerEndLevel` | S6 | `needs-evidence` |
| 5868 | `ChkStop` | S6 | `needs-evidence` |
| 5874 | `InCastle` | S6 | `needs-evidence` |
| 5876 | `RdyNextA` | S6 | `needs-evidence` |
| 5888 | `NextArea` | S6 | `needs-evidence` |
| 5895 | `ExitNA` | S6 | `needs-evidence` |

## S1 admission — game dispatcher and engine tail
S1 admits the contiguous 11-label chain `GameMode -> ExitEng`: `GameMode`, `GameCoreRoutine`, `GameEngine`, `ProcELoop`, `NoChgMus`, `CycleTwo`, `ClrPlrPal`, `SaveAB`, `UpdScrollVar`, `RunParser`, `ExitEng`. Its predecessor is T57’s completed parser/renderer state; its source successors are the future T59–T66 actor, collision, OAM, timer and music chains. S1 owns the dispatcher’s selection, call order, loop/caller handoffs, palette/music gates and parser-tail decision; it does not claim child semantics that remain in their receiving cohorts.
Current registry admission has 0 already-exact labels and 11 needing fresh evidence: `GameMode`, `GameCoreRoutine`, `GameEngine`, `ProcELoop`, `NoChgMus`, `CycleTwo`, `ClrPlrPal`, `SaveAB`, `UpdScrollVar`, `RunParser`, `ExitEng`. Historical accounting remains 1,992 / 1,992, so the formal historical expected-match set is empty; the current registry can advance at most from 499 to 510 exact labels when all pending labels pass both tracks.
**ROM-logic track.** Compare the four GameMode vectors, `GameCoreRoutine` player selection/reload gate, GameEngine call sequence and six-slot loop, music/palette branches, `SaveAB` partition clear and parser-tail branches against the original ROM. The controlled route records the original ROM and current x86/x64 from a source-reachable GameMode frame with selector 3, then compares declared persistent RAM, CIRAM, palette, OAM, audio and PPU state with named ABI exclusions. Relations to future actor/renderer/timer owners are verified here only for dispatch order, state handoff and return; their child semantics remain in their own T scope.
**Operational track.** Run `mysmb.game-entry-dispatch`, `mysmb.engine-caller`, `mysmb.engine-slots`, `mysmb.engine-environment` and `mysmb.platform-purity` on x86/x64; link the unchanged shared DOS16 core. A shared-game source repair refreshes `assets/mysmb16.exe`, `assets/mysmb32.exe` and `assets/mysmb64.exe`.

## S1 closure criteria

Every S1 label and every feasible incident control relation is current-exact with static and controlled-route evidence. Any mismatch is repaired in the named shared `src/game` owner, then the same route is repeated before S2 admission.
