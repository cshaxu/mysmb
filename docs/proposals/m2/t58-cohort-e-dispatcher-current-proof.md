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

## S1 closure — game dispatcher and engine tail

All 11 labels are current-equivalence exact: `GameMode`, `GameCoreRoutine`, `GameEngine`, `ProcELoop`, `NoChgMus`, `CycleTwo`, `ClrPlrPal`, `SaveAB`, `UpdScrollVar`, `RunParser` and `ExitEng`. The static contract verifies the four selector targets; controller-byte selection/reload gate; GameEngine actor, OAM, block, cannon, whirlpool, flagpole, timer, palette and parser order; the six-slot/dual-block loop; and palette/music/parser branch semantics.

The original-ROM/current matrix has four selector fixtures, both GameCoreRoutine post-child outcomes, two 600-frame normal routes and fifteen engine-tail routes. It compares declared persistent RAM and full recorded output without output exclusions; x86 and x64 records are byte-identical. The focused x86/x64 dispatcher, caller, slot and environment tests and platform-purity test pass. No product source mismatch was found, so no executable refresh is due. The 70 feasible incident relations are exact; 58 received fresh S1 evidence and 12 retain compatible prior exact evidence.

S2 may now be admitted for `ScrollHandler -> GetScreenPosition`.


## S2 admission — scroll threshold and player-edge chain

S2 admits the contiguous ten-label chain `ScrollHandler -> GetScreenPosition`: `ScrollHandler`, `ChkNearMid`, `ScrollScreen`, `InitScrlAmt`, `ChkPOffscr`, `KeepOnscr`, `InitPlatScrl`, `X_SubtracterData`, `OffscrJoypadBitsData` and `GetScreenPosition`. All ten are currently `needs-evidence`; none is already current-exact. The common shared owner is `src/game/scroll.c`. Its predecessors are the established player/pipe callers (`DontWalk`, `PlayerSubs`, `VerticalPipeEntry`) and its successors are the established edge-clamp consumer `GetXOffscreenBits`, caller returns, and `StartPage`'s screen-position reuse. The chain does not claim the physics, pipe-entry or offscreen-bit producer families owned by adjacent S chains.

Historical accounting remains 1,992 / 1,992, so the historical expected-match set is empty. The current registry begins at 510 exact labels and 946 exact feasible control relations. Subject to both tracks, this S can promote the ten labels and its 25 unresolved feasible incident control relations, reaching at most 520 labels and 971 feasible control relations. The two other incident relations already exact remain subject to regression review.

**ROM-logic track.** Compare source lines 5403–5497 with the C90 owner: add platform scroll force; all `$50`/`$70` and signed/decrement gates; `ScrollScreen` byte arithmetic, page carry, PPU nametable-bit merge and tail handoff; raw offscreen-bit selection; both edge tables; left/right page borrow; speed nullification predicate; and `GetScreenPosition`’s `$ff` carry. Use the controlled original-ROM natural-entry snapshot matrix for all 24 `t31-scroll` cases, including all nine branch outcomes, then run the snapshot through the current x86/x64 C owner. The route compares persistent RAM with only original CPU scratch `$00-$07` and stack `$0100-$01ff` excluded; it does not infer upstream physics or `GetXOffscreenBits` correctness.

**Operational track.** Run `mysmb.player-scroll-chain`, the x86/x64 snapshot checker, the original-ROM/current scroll matrix, the shared DOS16 core link and platform-purity check. A shared-game source repair refreshes `assets/mysmb16.exe`, `assets/mysmb32.exe` and `assets/mysmb64.exe`; an audit-only conclusion does not.

## S2 closure criteria

Every scoped label and feasible incident relation is current-exact with static and controlled-route proof. A discrepancy remains in S2's shared owner until repaired and re-audited on the same route; only then may S3 be admitted.

## S2 closure — scroll threshold and player-edge chain

All ten labels are current-equivalence exact: `ScrollHandler`, `ChkNearMid`, `ScrollScreen`, `InitScrlAmt`, `ChkPOffscr`, `KeepOnscr`, `InitPlatScrl`, `X_SubtracterData`, `OffscrJoypadBitsData` and `GetScreenPosition`. The static source audit found no C/ROM difference. It confirms force addition, the `$50` and `$70` gates, the `DEY/BMI` and `CPY` cases, carry into screen page and nametable bit zero, raw offscreen-bit polarity, both two-byte tables, right-edge page borrow, speed clearing and the `$ff` right-screen calculation.

The controlled original-ROM matrix has 24 natural `ScrollHandler` entries and both outcomes of all nine source branches. Fresh direct C90 x86/x64 builds run the existing exhaustive scroll contract and replay every original snapshot: 48 persistent-RAM comparisons pass with only CPU scratch `$00-$07` and stack `$0100-$01ff` excluded; native widths are byte-identical. Platform-purity passes. No product source changed, so no artifact refresh is due. All 27 incident feasible relations are exact: 25 receive S2 evidence, while `DontWalk -> ScrollScreen` and `ScrollScreen -> DontWalk` retain their compatible prior exact evidence.

S3 may now be admitted for `GameRoutines -> CloudExit`.

## S3 admission — game routine, entrance and player-control chain

S3 admits the contiguous 23-label chain `GameRoutines -> CloudExit`: `GameRoutines`, `PlayerEntrance`, `ChkBehPipe`, `IntroEntr`, `EntrMode2`, `VineEntr`, `OffVine`, `PlayerRdy`, `ExitEntr`, `AutoControlPlayer`, `PlayerCtrlRoutine`, `DisJoyp`, `SaveJoyp`, `SizeChk`, `ChkMoveDir`, `SetMoveDir`, `PlayerSubs`, `PlayerHole`, `HoleDie`, `HoleBottom`, `ChkHoleX`, `ExitCtrl` and `CloudExit`. All 23 are currently `needs-evidence`. Shared C owners are `src/game/entry.c` and `src/game/player_control.c`; entry/transition, movement, OAM, collision and mode children remain their respective source-order owners. Predecessors are the completed dispatcher and scroll chains; successors are the admitted-later pipe, mode, collision, OAM and end-level families.

Historical accounting remains 1,992 / 1,992; historical expected-match set is empty. The current registry begins at 520 exact labels and 971 exact feasible controls. This S expects to promote the 23 scoped labels and 92 unresolved feasible incident controls, reaching at most 543 labels and 1,063 feasible controls. Eight other incident controls retain prior exact evidence and must pass regression review.

**ROM-logic track.** Compare the `GameRoutines` JumpEngine vector, ordinary/pipe/vine entrance branches, controller suppression and three input partitions, crouch filter, bounding-box selector, moving-direction signed branch, ordered player children, hole/death/music gates and cloud-area transition. Use the original controlled `t31-entrance` route plus `t32` player-control natural-entry snapshots and current x86/x64 owner replays; each route declares its RAM/output exclusions and does not certify child algorithms outside this S.

**Operational track.** Run `mysmb.player-entry-chain`, `mysmb.player-control-chain`, caller/snapshot checks and platform purity on x86/x64, then link the unchanged shared DOS16 core. A shared-game source repair refreshes all three target artifacts; an audit-only conclusion does not.

## S3 closure criteria

Every scoped label and feasible incident control relation is current-exact with static and controlled-route evidence. Any discrepancy remains in the named shared owner until repaired and re-audited before S4 admission.
