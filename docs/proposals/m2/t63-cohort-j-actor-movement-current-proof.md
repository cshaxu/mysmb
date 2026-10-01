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

## S2 admission — small/large platform caller and movement-vector bridge

S2 admits `RunSmallPlatform`, `RunLargePlatform`, `SkipPT`, and
`LargePlatformSubroutines` (lines 9156–9194). It owns 27 feasible direct
control relations: both ordered runner paths, TimerControl branch/fall-through,
the seven-entry movement dispatch and all direct return/tail boundaries. The
extractor's `LargePlatformSubroutines -> EraseEnemyObject` fall-through is
source-infeasible and remains excluded. It owns five material handoffs: small
caller state; large collision/timer; seven-entry vector/scratch; post-movement
relative state; and bounds state.

Children (`GetEnemyOffscreenBits`, relative/box/collision/OAM/bounds and seven
movement-vector targets) remain later source-order boundaries. The ROM-logic
track compares child order, master-timer skip, `Enemy_ID - $24` vector index,
duplicated lift target and JumpEngine scratch. The operational route uses ROM
large IDs `$24-$2a` and small IDs `$2b-$2c`, both slots, timer values and
child-mutated state against fresh x86/x64 caller records; it runs
`mysmb.platform-caller`, purity and the DOS16 link. A feasible difference
remains in S2 for repair and re-audit.

### S2 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **984 / 1,992**.
- Current exact feasible control edges: **1,924 / 4,324**.
- Raw control edges: **4,342**; infeasible controls: **18**.
- Scope: **4** labels; expected promotions: **4**; maximum current exact
  node count on successful closure: **988 / 1,992**.

## S2 closure — small/large platform caller and movement-vector bridge

All four scoped labels are current-exact. Static `$C5BB-$C5E9` comparison
confirms the complete small/large caller order, both TimerControl outcomes,
`Enemy_ID-$24` selection, the seven target words including the duplicated
large-lift entry, and JumpEngine scratch protocol. All 27 feasible direct
controls and five material handoffs are exact; the extracted fall-through to
`EraseEnemyObject` remains ROM-infeasible. Fresh current-source ROM/x86/x64
caller replay matches 36 platform fixtures per width (**72 / 72**). The
focused caller contract covers 3,240 footprints per width, platform purity
passes and DOS16 links with its known `OLDNAMES.LIB` warning. No product source
changed, so artifacts were not refreshed. Platform children remain explicit
later source-order obligations.

Historical mapping remains **1,992 / 1,992**; current exact status is
**988 / 1,992 nodes** and **1,950 / 4,324 feasible controls** (raw
**4,342**, infeasible **18**).

## S3 admission — lifecycle erase and Podoboo gravity bridge

S3 admits `EraseEnemyObject`, `MovePodoboo` and `PdbM` (lines 9198–9224). It
owns eleven feasible controls: the Podoboo timer branch/call/fall-through/tail
and six established caller returns to the exact clear routine. It owns three
material handoffs: eight cleared lifecycle fields, timer/slot initialization
eligibility, and random-derived force/timer/speed into the gravity tail.
`InitPodoboo` and `MoveJ_EnemyVertically` remain source-order child boundaries.
The ROM route covers all six slots, zero/nonzero timer, post-child random-byte
read and gravity tail; current x86/x64 caller records and focused lifecycle /
Podoboo contracts form the operational track.

### S3 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **988 / 1,992**.
- Current exact feasible controls: **1,950 / 4,324**.
- Raw controls: **4,342**; infeasible controls: **18**.
- Scope: **3** labels; expected promotions: **3**; maximum current exact
  node count on successful closure: **991 / 1,992**.

## S3 closure — lifecycle erase and Podoboo gravity bridge

All three labels are current-exact. Static `$C998-$C9CD` comparison confirms
the eight current-slot clear stores, the timer-zero branch, child call,
post-child PRNG read, force/timer/speed writes, unconditional gravity tail and
the six established lifecycle caller returns. Fresh current-source original-ROM
caller replay passes **128 / 128** Podoboo comparisons (64 x86 and 64 x64).
The focused Podoboo contract covers 6,144 footprints per width and the
lifecycle/caller contract covers 3,240 per width. Platform purity passes; the
shared OpenNT DOS16 source link produces the local MZ output with its known
`OLDNAMES.LIB` warning. No product source changed, so the three local EXE
artifacts were not refreshed.

The three nodes, eleven feasible controls and three material handoffs are now
exact. Child interiors `InitPodoboo` and `MoveJ_EnemyVertically` remain their
separate source-order obligations. Historical mapping remains **1,992 /
1,992**; current exact status is **991 / 1,992 nodes** and **1,961 / 4,324
feasible controls** (raw **4,342**, infeasible **18**).

## S4 admission — Hammer Bro throw, jump and horizontal bridge

S4 admits the continuous `HammerThrowTmrData -> SetShim` chain (lines
9229–9316): `HammerThrowTmrData`, `XSpeedAdderData`, `RevivedXSpeed`,
`ProcHammerBro`, `ChkJH`, `DecHT`, `HammerBroJumpLData`,
`HammerBroJumpCode`, `SetHJ`, `HJump`, `MoveHammerBroXDir`, `Shimmy`, and
`SetShim`. The shared owner is `src/game/enemy/hammer_bro.c`; its normal and
defeated movement children remain explicit S5 boundaries. S4 owns its 24
feasible outgoing controls and eight material handoffs, including the two
normal-movement table bindings whose consumers begin in S5.

The ROM-logic track audits `$C9CE-$CA76`: both tables, defeated precedence,
jump/throw timers, sprite-offscreen gate, hammer child result, jump speed and
length selection, frame shimmy, player-difference direction, and normal-move
entry. The operational track replays the controlled 356-case original ROM
Hammer movement boundary on current x86/x64 and runs the focused Hammer Bro
smokes, platform-purity and DOS16 link. Any feasible difference remains in S4
for shared-owner repair and repeat audit.

### S4 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **991 / 1,992**.
- Current exact feasible controls: **1,961 / 4,324**.
- Raw controls: **4,342**; infeasible controls: **18**.
- Scope: **13** unique labels; expected current promotions: **13**; maximum
  current exact node count on successful closure: **1,004 / 1,992**.

## S4 closure — Hammer Bro throw, jump and horizontal bridge

All 13 labels are current-exact. Static `$C9CE-$CA76` comparison confirms both
timer/length tables, defeated precedence, jump and throw timing, sprite
offscreen gate, hammer-spawn result handling, PRNG/secondary-hard jump
selection, shimmy speed, player-difference facing and normal-movement entry.
Fresh current-source original-ROM route replay passes **712 / 712** comparisons
(356 per x86 and x64). The focused caller state contract covers 12,288
footprints per width. Platform purity passes, and the shared OpenNT DOS16 link
produces its local MZ output with its known `OLDNAMES.LIB` warning. No product
source changed, so no three-EXE artifact refresh is due.

The chain closes 13 nodes, 24 feasible controls and eight material handoffs
exact. `MoveNormalEnemy` and `MoveDefeatedEnemy` interiors remain the following
source-order S5 obligation. Historical mapping remains **1,992 / 1,992**;
current exact status is **1,004 / 1,992 nodes** and **1,985 / 4,324 feasible
controls** (raw **4,342**, infeasible **18**).

## S5 admission — normal and defeated enemy movement chain

S5 admits the contiguous `MoveNormalEnemy -> NKGmba` chain (lines
9318–9392, `$CA77-$CAF8`): `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`,
`SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`,
`ChkKillGoomba`, and `NKGmba`. The shared C owner is
`src/game/enemy/movement.c`. Its predecessor is S4's `SetShim` handoff;
its child boundaries are the already-owned gravity, horizontal-movement and
lifecycle routines. S6 begins at `MoveJumpingEnemy`.

S5 owns 28 feasible direct controls: state-priority branches, vertical-child
call and post-child dispatch, temporary horizontal-speed adjustment and
restore, revive timer and hard-mode table selection, defeated movement tail,
and Goomba erase gate. It owns four material handoffs: normal-state to fall,
post-gravity state to horizontal dispatch, revive timer/ID to the Goomba gate,
and Goomba-ID/timer to erase. The ROM-logic track compares the source control
order and table/RAM contracts at `$CA77-$CAF8`, then replays 132 controlled
original-ROM direct normal-movement records through current x86 and x64. The
operational track runs the exhaustive normal-enemy movement contract, platform
purity and shared DOS16 link. A feasible difference remains in S5 for repair
and repeat audit.

### S5 admission totals

- Historical mapping: **1,992 / 1,992**.
- Current exact nodes: **1,004 / 1,992**.
- Current exact feasible control edges: **1,985 / 4,324**.
- Raw control edges: **4,342**; infeasible controls: **18**.
- Scope: **11** unique labels; expected current promotions: **11**; maximum
  current exact node count on successful closure: **1,015 / 1,992**.

## S5 closure — normal and defeated enemy movement chain

All 11 scoped labels are current-exact. Static `$CA77-$CAF8` comparison
confirms the state-bit priority, source child ordering, post-gravity state
reread, power-up exception, temporary speed table/index and restoration,
revive timer/Goomba gate, frame/hard-mode revived-speed selection, and
defeated vertical/horizontal tail. The 28 feasible direct controls and four
material handoffs are exact. Fresh current-source original-ROM caller replay
passes **264 / 264** comparisons (132 per x86 and x64). The exhaustive normal
movement contract covers **1,253,376** state/speed/slot/ID/timer/hard-mode
footprints per width. Platform purity passes, and OpenNT DOS16 shared-source
link produces the local MZ output with its known `OLDNAMES.LIB` warning. No
product source changed, so the three local EXE artifacts were not refreshed.

Historical mapping remains **1,992 / 1,992**; current exact status is
**1,015 / 1,992 nodes** and **2,013 / 4,324 feasible controls** (raw
**4,342**, infeasible **18**). S6 begins with `MoveJumpingEnemy`.
