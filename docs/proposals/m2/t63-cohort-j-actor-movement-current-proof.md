# M2 T63: Cohort J actor, movement and platform current-equivalence proof

T63 continues the approved source-order current-equivalence program after T62.
It audits the first **244** of Cohort J’s 497 labels, from `RunFirebarObj`
through `MoveLiftPlatforms`.  T64 begins at `OffscreenBoundsCheck`; it owns
terrain, projectile and contact/collision chains. Historical ROM-match
accounting remains **1,992 / 1,992**. This task contributes only fresh
current shared-C proof.

## Task contract

Each S is one bounded source-order shared-owner chain. It must compare original
branch predicates, RAM/table reads and writes, call/return order, and material
handoffs with the portable C owner. Its independent operational track uses the
same controlled original-ROM route and current x86/x64 record, focused checks,
platform-purity, the shared DOS16 link, and all three local artifacts only when
product code changes. Owner-supplied ROMs, disassembly material, generated
records and binaries remain local below ignored `build/` or `assets/`.

## Source-ordered chains

| S | Source lines | Labels | Chain | Shared C owner | Exact labels |
| --- | ---: | ---: | --- | --- | --- |
| S1 | 9150–9150 | 1 | `RunFirebarObj -> RunFirebarObj` | `src/game/enemy/{core,normal,dispatch_targets,special_callers}.c` | RunFirebarObj |
| S2 | 9156–9182 | 4 | `RunSmallPlatform -> LargePlatformSubroutines` | `src/game/enemy/platform_callers.c` | RunSmallPlatform, RunLargePlatform, SkipPT, LargePlatformSubroutines |
| S3 | 9198–9224 | 3 | `EraseEnemyObject -> PdbM` | `src/game/enemy/{lifecycle,podoboo}.c` | EraseEnemyObject, MovePodoboo, PdbM |
| S4 | 9229–9316 | 13 | `HammerThrowTmrData -> SetShim` | `src/game/enemy/hammer_bro.c` | HammerThrowTmrData, XSpeedAdderData, RevivedXSpeed, ProcHammerBro, ChkJH, DecHT, HammerBroJumpLData, HammerBroJumpCode, SetHJ, HJump, MoveHammerBroXDir, Shimmy, SetShim |
| S5 | 9318–9392 | 11 | `MoveNormalEnemy -> NKGmba` | `src/game/enemy/movement.c` | MoveNormalEnemy, FallE, MEHor, SlowM, SteadM, AddHS, ReviveStunned, SetRSpd, MoveDefeatedEnemy, ChkKillGoomba, NKGmba |
| S6 | 9396–9421 | 5 | `MoveJumpingEnemy -> MovPTDwn` | `src/game/enemy/{movement,paratroopa}.c` | MoveJumpingEnemy, ProcMoveRedPTroopa, NoIncPT, MoveRedPTUpOrDown, MovPTDwn |
| S7 | 9427–9481 | 10 | `MoveFlyGreenPTroopa -> XMRight` | `src/game/enemy/{green_paratroopa,x_counter}.c` | MoveFlyGreenPTroopa, YSway, NoMGPT, XMoveCntr_GreenPTroopa, XMoveCntr_Platform, NoIncXM, IncPXM, DecSeXM, MoveWithXMCntrs, XMRight |
| S8 | 9490–9592 | 16 | `BlooberBitmasks -> ChkNearPlayer` | `src/game/enemy/bloober.c` | BlooberBitmasks, MoveBloober, FBLeft, SBMDir, BlooberSwim, SwimX, LeftSwim, MoveDefeatedBloober, ProcSwimmingB, BSwimE, SlowSwim, NoSSw, ChkForFloatdown, Floatdown, NoFD, ChkNearPlayer |
| S9 | 9603–9686 | 9 | `MoveBulletBill -> ExSwCC` | `src/game/enemy/{bullet_bill,swimming_cheep}.c` | MoveBulletBill, NotDefB, SwimCCXMoveData, MoveSwimmingCheepCheep, CCSwim, CCSwimUpwards, ChkSwimYPos, YPDiff, ExSwCC |
| S10 | 9703–9922 | 32 | `FirebarPosLookupTbl -> GetVAdder` | `src/game/enemy/firebar.c` | FirebarPosLookupTbl, FirebarMirrorData, FirebarTblOffsets, FirebarYPos, ProcFirebar, SusFbar, SkpFSte, SetupGFB, SetMFbar, DrawFbar, NextFbar, SkipFBar, DrawFirebar_Collision, AddHA, SubtR1, ChkFOfs, VAHandl, AddVA, SetVFbr, FirebarCollision, AdjSm, BigJp, FBCLoop, ChkVFBD, ChkFBCl, Chk2Ofs, ChgSDir, SetSDir, NoColFB, GetFirebarPosition, GetHAdder, GetVAdder |
| S11 | 9941–9982 | 6 | `PRandomSubtracter -> BPGet` | `src/game/enemy/flying_cheep.c` | PRandomSubtracter, FlyCCBPriority, MoveFlyingCheepCheep, FlyCC, AddCCF, BPGet |
| S12 | 9990–10087 | 16 | `LakituDiffAdj -> ExMoveLak` | `src/game/enemy/lakitu.c` | LakituDiffAdj, MoveLakitu, ChkLS, Fr12S, LdLDa, SetLSpd, SetLMov, PlayerLakituDiff, ChkLakDif, SetLMovD, ChkPSpeed, ChkSpinyO, ChkEmySpd, SubDifAdj, SPixelLak, ExMoveLak |
| S13 | 10092–10152 | 6 | `BridgeCollapseData -> NoBFall` | `shared game core: bridge/area/enemy/OAM` | BridgeCollapseData, BridgeCollapse, SetM2, MoveD_Bowser, RemoveBridge, NoBFall |
| S14 | 10156–10159 | 2 | `PRandomRange -> RunBowser` | `shared game core: enemy/bowser.c` | PRandomRange, RunBowser |
| S15 | 10167–10169 | 2 | `KillAllEnemies -> KillLoop` | `shared game core: enemy/loop.c` | KillAllEnemies, KillLoop |
| S16 | 10176–10283 | 15 | `BowserControl -> SetFBTmr` | `shared game core: enemy/bowser.c` | BowserControl, ChkMouth, FeetTmr, ResetMDr, B_FaceP, GetPRCmp, GetDToO, CompDToO, HammerChk, SetHmrTmr, SkipToFB, MakeBJump, ChkFireB, SpawnFBr, SetFBTmr |
| S17 | 10289–10323 | 4 | `BowserGfxHandler -> ProcessBowserHalf` | `shared game core: oam/bowser_gfx.c` | BowserGfxHandler, CopyFToR, ExBGfxH, ProcessBowserHalf |
| S18 | 10337–10347 | 3 | `FlameTimerData -> ExFl` | `shared game core: enemy/frenzy.c` | FlameTimerData, SetFlameTimer, ExFl |
| S19 | 10349–10356 | 2 | `ProcBowserFlame -> SFlmX` | `shared game core: enemy/bowser_flame.c` | ProcBowserFlame, SFlmX |
| S20 | 10374–10434 | 7 | `SetGfxF -> ExFlmeD` | `shared game core: oam/bowser_flame_gfx.c` | SetGfxF, FlmeAt, DrawFlameLoop, M3FOfs, M2FOfs, M1FOfs, ExFlmeD |
| S21 | 10438–10457 | 3 | `RunFireworks -> FireworksSoundScore` | `shared game core: enemy/fireworks.c` | RunFireworks, SetupExpl, FireworksSoundScore |
| S22 | 10468–10589 | 19 | `StarFlagYPosAdder -> DelayToAreaEnd` | `shared game core: enemy/star_flag.c` | StarFlagYPosAdder, StarFlagXPosAdder, StarFlagTileData, RunStarFlagObj, GameTimerFireworks, SetFWC, IncrementSFTask1, StarFlagExit, AwardGameTimerPoints, NoTTick, EndAreaPoints, ELPGive, RaiseFlagSetoffFWorks, SetoffF, DrawStarFlag, DSFLoop, DrawFlagSetTimer, IncrementSFTask2, DelayToAreaEnd |
| S23 | 10596–10596 | 1 | `StarFlagExit2 -> StarFlagExit2` | `src/game/enemy/star_flag.c` | StarFlagExit2 |
| S24 | 10602–10656 | 6 | `MovePiranhaPlant -> PutinPipe` | `shared game core: enemy/piranha.c` | MovePiranhaPlant, ChkPlayerNearPipe, ReversePlantSpeed, SetupToMovePPlant, RiseFallPiranhaPlant, PutinPipe |
| S25 | 10664–10677 | 2 | `FirebarSpin -> SpinCounterClockwise` | `shared game core: enemy/firebar_children.c` | FirebarSpin, SpinCounterClockwise |
| S26 | 10692–10916 | 26 | `BalancePlatform -> ExPF` | `shared game core: enemy/balance_platform.c` | BalancePlatform, DoBPl, CheckBalPlatform, ChkForFall, MakePlatformFall, ChkOtherForFall, ChkToMoveBalPlat, ColFlg, PlatUp, PlatSt, PlatDn, DoOtherPlatform, DrawEraseRope, EraseR1, OtherRope, EraseR2, EndRp, ExitRp, SetupPlatformRope, GetLRp, GetHRp, ExPRp, InitPlatformFall, StopPlatforms, PlatformFall, ExPF |
| S27 | 10921–11023 | 20 | `YMovingPlatform -> ExLiftP` | `shared game core: enemy/platform.c` | YMovingPlatform, SkipIY, ChkYCenterPos, YMDown, ChkYPCollision, ExYPl, XMovingPlatform, PositionPlayerOnHPlat, PPHSubt, SetPVar, ExXMP, DropPlatform, ExDPl, RightPlatform, ExRPl, MoveLargeLiftPlat, MoveSmallPlatform, MoveLiftPlatforms, ChkSmallPlatCollision, ExLiftP |

T63’s exact target is the 244 labels enumerated above. Each label’s existing
receiver remains authoritative in `NODE_TASK_LEDGER`; these are overlapping
audit admissions, so no historical implementation custody transfers. The
planned S owns only relations whose source endpoint lies in its chain, unless a
later packet explicitly assigns a cross-chain boundary. S27 stops before
`OffscreenBoundsCheck` at line 11031, which belongs to T64.

## S1 admission — Firebar actor caller/bounds bridge

S1 admits only `RunFirebarObj` (line 9150), a one-label boundary forced by the
next source label changing to the independent platform-caller owner. Incoming
`JmpEO -> RunFirebarObj` selector edges remain current-exact T62 evidence. S1
owns `RunFirebarObj -> ProcFirebar` (call) and
`RunFirebarObj -> OffscreenBoundsCheck` (tail jump), plus the
`RunFirebarObj -> OffscreenBoundsCheck` firebar-processing-state material
handoff. `ProcFirebar` and `OffscreenBoundsCheck` are explicit later T63/T64
child boundaries and receive no node credit from S1.

The ROM-logic track compares the unconditional child call, post-child tail jump
and slot/return preservation at `$C5B5-$C5B9` with
`mysmb_objects_step_firebars_slot` in `src/game/enemy/special_callers.c`. The
operational route records short and long Firebar slots, including a child injury
result, from the original-ROM actor dispatcher through the bounds entry and
compares the matching current x86/x64 caller records. It also runs
`mysmb.special-actor-caller`, platform purity, and the shared DOS16 link. Any
feasible difference remains in S1 for repair and re-audit before S2 admission.

### S1 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **983 / 1,992**.
- Current exact feasible control edges: **1,922 / 4,324**.
- Raw control edges: **4,342**; infeasible controls: **18**.
- S1 scope: **1** unique label; expected current promotions: **1**;
  maximum current exact node count after successful closure: **984 / 1,992**.

## S1 closure — Firebar actor caller/bounds bridge

`RunFirebarObj` is current-exact. Static original-ROM `$C5B5-$C5B9` and the
shared C caller agree: it calls `ProcFirebar`, preserves its compatibility
return value, then reaches `OffscreenBoundsCheck` unconditionally. The two
direct control relations and the one firebar-processing-to-bounds material
handoff are exact. Fresh current-source x86/x64 caller replay matches 32
Firebar ROM fixtures per width (**64 / 64**); the focused caller contract
covers 3,072 child-result/slot footprints per width. Platform purity passes.
The OpenNT DOS16 shared-source link produces the local MZ binary with the
known `OLDNAMES.LIB` warning. No product source changed, so the three local
executable artifacts were not refreshed.

`ProcFirebar` and `OffscreenBoundsCheck` remain their explicit later
source-order nodes; no child semantics were inferred from the caller proof.
Historical mapping remains **1,992 / 1,992**; current exact status is
**984 / 1,992 nodes** and **1,924 / 4,324 feasible controls** (raw
**4,342**, infeasible **18**).
