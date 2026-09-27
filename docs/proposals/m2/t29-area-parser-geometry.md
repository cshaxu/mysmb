# M2 T29: Area parser and large-object geometry

T29 is the source-order receiver for ROM lines 2796--3990.  It follows the
closed T28 bootstrap chains and precedes T30's rendering and metatile chains.
All business behavior belongs in shared C90 game code.  Windows and DOS are
limited to physical input, timing, and submission of the completed frame.

## Delivery contract

This task uses the binding [M2 chain-based S delivery
rule](../../rules/EXECUTION.md#m2-chain-based-s-delivery).  Each S admits one
bounded contiguous control/data chain with one shared owner and one
reproducible original-ROM route.  It performs source mapping, any necessary
shared-C repair, node-level ROM control/data/call comparison, and operational
proof in the same delivery.  Labels remain individually accounted in the
inventory, ledger, and progress tracker.

ROM-equivalence and operational evidence are separate.  Every implementation
P refreshes and records `assets/mysmb16.exe`, `assets/mysmb32.exe`, and
`assets/mysmb64.exe`; one chain-level replay and one three-target build package
cover all labels in that P.  T29 closure additionally requires a cross-chain
parser/area-entry regression matrix.  A chain splits only at an unadmitted
dependency, a shared-game owner boundary, or a branch family that needs a
different source route.

Every T29 S begins with its exact node list, source entry/exit, common owner,
incoming status, expected completions, predecessor/successor receipts and two
separate verification plans. It closes with a per-label tracker disposition:
ROM-match complete, deferred with the failed track, or transferred by exact
name. The chain performs its mapping, repair when required, ROM control/data
audit and operational evidence together. It does not create a separate S for
an adjacent table, loop or helper that shares its route and owner.

## Planned source-order chains

The table is a planning map, not an advance completion claim.  Every row must
receive an exact ledger receipt and active-packet admission before code work.

| S | Entry and exit | Labels in source order | Shared owner and ROM route |
| --- | --- | --- | --- |
| S1 | `InitPageLoop -> SkipByte` | `InitPageLoop`, `InitByteLoop`, `InitByte`, `SkipByte` | Shared memory-clear primitive; natural reset/cold-start route proves page descent, stack exclusion, and byte writes. |
| S2 | `MusicSelectData -> ExitGetM` | `MusicSelectData`, `GetAreaMusic`, `ChkAreaType`, `StoreMusic`, `ExitGetM` | Shared area/music selector; ordinary area-entry route covers title return, pipe, cloud, and area-type selection. |
| S3 | `PlayerStarting_X_Pos -> SetPESub` | `PlayerStarting_X_Pos`, `AltYPosOffset`, `PlayerStarting_Y_Pos`, `PlayerBGPriorityData`, `GameTimerData`, `Entrance_GameTimerSetup`, `ChkStPos`, `SetStPos`, `ChkOverR`, `ChkSwimE`, `SetPESub` | Shared player/area entry boundary; normal GameEngine entrance route covers water, alternate entrance, timer reload, vine, and bubble branches. |
| S4 | `HalfwayPageNybbles -> DoNothing2` | `HalfwayPageNybbles`, `PlayerLoseLife`, `StillInGame`, `GetHalfway`, `MaskHPNyb`, `SetHalfway`, `GameOverMode`, `SetupGameOver`, `RunGameOver`, `TerminateGame`, `ContinueGame`, `GameIsOn`, `TransposePlayers`, `TransLoop`, `ExTrans`, `DoNothing1`, `DoNothing2` | Shared mode/life-transition family; death, game-over, continue, and two-player routes are separately sampled under one state-transition owner. |
| S5 | `AreaParserTaskHandler -> AreaParserCore` | `AreaParserTaskHandler`, `DoAPTasks`, `SkipATRender`, `AreaParserTasks`, `IncrementColumnPos`, `NoColWrap`, `BSceneDataOffsets`, `BackSceneryData`, `BackSceneryMetatiles`, `FSceneDataOffsets`, `ForeSceneryData`, `TerrainMetatiles`, `TerrainRenderBits`, `AreaParserCore` | Shared parser dispatch; natural area-parser task route proves task vector, column wrap, and scenery data selection. |
| S6 | `RenderSceneryTerrain -> BlockBuffLowBounds` | `RenderSceneryTerrain`, `ClrMTBuf`, `ThirdP`, `RendBack`, `SceLoop1`, `RendFore`, `SceLoop2`, `NoFore`, `RendTerr`, `TerMTile`, `StoreMT`, `TerrLoop`, `NoCloud2`, `TerrBChk`, `NextTBit`, `EndUChk`, `RendBBuf`, `ChkMTLow`, `StrBlock`, `BlockBuffLowBounds` | Shared parser/metatile staging; parser-column route proves metatile buffer and block-buffer write order. |
| S7 | `ProcessAreaData -> SetFore` | `ProcessAreaData`, `ProcADLoop`, `Chk1Row13`, `Chk1Row14`, `CheckRear`, `RdyDecode`, `SetBehind`, `NextAObj`, `ChkLength`, `ProcLoopb`, `EndAParse`, `IncAreaObjOffset`, `DecodeAreaData`, `Chk1stB`, `ChkRow14`, `ChkRow13`, `Mask2MSB`, `ChkSRows`, `LrgObj`, `NotWPipe`, `SpecObj`, `MoveAOId`, `NormObj`, `LeavePar`, `InitRear`, `LoopCmdE`, `BackColC`, `StrAObj`, `RunAObj`, `AlterAreaAttributes`, `Alter2`, `SetFore` | Shared area-stream decoder; source-reachable object-stream route covers row/length/rear-column and normal/large/special object decisions. |
| S8 | `ScrollLockObject_Warp -> MushLExit` | `ScrollLockObject_Warp`, `WarpNum`, `ScrollLockObject`, `KillEnemies`, `KillELoop`, `NoKillE`, `FrenzyIDData`, `AreaFrenzy`, `FreCompLoop`, `ExitAFrenzy`, `AreaStyleObject`, `TreeLedge`, `MidTreeL`, `EndTreeL`, `MushroomLedge`, `EndMushL`, `AllUnder`, `NoUnder`, `PulleyRopeMetatiles`, `PulleyRopeObject`, `RenderPul`, `MushLExit` | Shared special-object parser path; source object streams cover scroll locks, enemy cleanup, frenzy, ledges, and pulley geometry. |
| S9 | `CastleMetatiles -> GetPipeHeight` | `CastleMetatiles`, `CastleObject`, `CRendLoop`, `ChkCFloor`, `NotTall`, `PlayerStop`, `ExitCastle`, `WaterPipe`, `IntroPipe`, `VPipeSectLoop`, `NoBlankP`, `SidePipeShaftData`, `SidePipeTopPart`, `SidePipeBottomPart`, `ExitPipe`, `RenderSidewaysPipe`, `DrawSidePart`, `VerticalPipeData`, `VerticalPipe`, `WarpPipe`, `DrawPipe`, `GetPipeHeight` | Shared large-object geometry path; castle and pipe object streams cover all floor/height/warp variants. |
| S10 | `FindEmptyEnemySlot -> FlagBalls_Residual` | `FindEmptyEnemySlot`, `EmptyChkLoop`, `ExitEmptyChk`, `Hole_Water`, `QuestionBlockRow_High`, `QuestionBlockRow_Low`, `Bridge_High`, `Bridge_Middle`, `Bridge_Low`, `FlagBalls_Residual` | Shared allocation/final object geometry; natural object route covers slot scan and terminal stream data consumers. |

## S1 admission: InitializeMemory loop chain

S1 receives exactly `InitPageLoop`, `InitByteLoop`, `InitByte`, and
`SkipByte` from legacy `M2 T18 S4`.  Its baseline is **265 / 1,992**.  All
four labels are currently open and are expected to become ROM-match complete,
for a maximum of **269 / 1,992**.

The common shared-game owner is the portable memory-clear primitive already
called by the translated cold-start path.  The ROM track audits the original
`$8fbe` parent and `$8fc2-$8fda` loop: descending page traversal, the
`$0100-$015f` write region, the preserved stack window `$0160-$01ff`, Y-byte
wrap, and return condition.  The route is ordinary reset/cold start; the
recorder may set only documented reset input/state and must never inject a
leaf PC or stack.

The operational track adds `mysmb.ram-cold-start-smoke` and
`mysmb.reset-root-smoke` on x86 and x64,
paired ROM/native cold-start recording, the platform-purity gate, OpenNT
DOS16 link, and the three required artifacts.  No platform file may own a
clear range, RAM boundary, or game-state default.

T29 closes only after every planned chain has dual-track evidence, every
incomplete label has an accepted successor, and the integrated area-entry,
parser-column, object-stream, and large-object regression matrix passes on
all three targets.

## S1 closure: InitializeMemory loop chain

S1 closes at **269 / 1,992**. `InitPageLoop`, `InitByteLoop`, `InitByte`,
and `SkipByte` are ROM-match complete; no scoped node is deferred or
transferred. The shared C90 owner was already correct, so this S adds no
product approximation or platform branch.

The source audit maps the four labels to `$90d2`, `$90d4`, `$90dc`, and
`$90de`. `mysmb_game_initialize_memory` preserves the source page descent
from `$07` to `$00`, Y wrap, the `$0100-$015f` clear, and the `$0160-$01ff`
skip. A natural original-ROM cold-start recording reached those PCs 24, 5,819,
5,339, and 5,819 times respectively; it covers both the ordinary store and
the page-one skipped-store branch. The project-owned cold-start smoke checks
the entire `$0000-$07ff` result for both original caller values `$fe` and
`$d6`.

`mysmb.ram-cold-start-smoke`, `mysmb.reset-root-smoke`, and
`mysmb.platform-purity` passed on Win32 x86 and x64. The shared core linked as
an OpenNT DOS16 MZ. The refreshed delivery artifacts are `mysmb16.exe`
`35F2F7E4BC35003422D03177114297D0B08FB2BCE848F7B226CC1E773B68BDA9`,
`mysmb32.exe` `F6C837731891CD03329E45F7756D108B20133AD2402B0CFB9AEB72D12A193B43`,
and `mysmb64.exe` `BF47B6738F830527A21C695FB305CB266843E5DFE627053C86B9F7F30845FB3F`.

## S2 admission: area-music selection chain

S2 receives exactly `MusicSelectData`, `GetAreaMusic`, `ChkAreaType`,
`StoreMusic`, and `ExitGetM` through accepted ledger event
`transfer-083-t18-s4-to-t29-s2-area-music`.  The five labels are open at the
**269 / 1,992** baseline; this contiguous source chain forecasts all five as
ROM-match complete, for a maximum **274 / 1,992**.

The shared owner is the portable area/music selection path.  Its ROM track
compares `$90e7-$9115` as one chain: the six music bytes, the `OperMode` early
return, alternate-entrance gate, pipe-entry tests, area-type and cloud
selection, `AreaMusicQueue` store, and return boundary.  The recorder may
establish only source-RAM preconditions at a frame boundary; it may not inject
a leaf program counter or stack.  Fixtures cover title return, ordinary
area-type selection, pipe entry, alternate pipe bypass, and cloud override.

The operational track uses the project-owned area-music smoke plus x86 and
x64 builds, the OpenNT DOS16 link, platform-purity check, and one refreshed
three-executable package for the chain P.  The chain cannot claim a label
until both evidence tracks pass.  No platform source may choose music, inspect
these area-control bytes, or write the music queue.

## S2 closure: area-music selection chain

S2 closes at **274 / 1,992**. `MusicSelectData`, `GetAreaMusic`,
`ChkAreaType`, `StoreMusic`, and `ExitGetM` are ROM-match complete; no scoped
node is deferred or transferred.

The source audit bound the six bytes at `$90e7` to `$02,$01,$04,$08,$10,$20`.
It corrected two existing shared-C deviations: `AltEntranceControl` is `$0752`
rather than `$0769`, and pipe entrance values `$06/$07` store index five and
return before the cloud-override branch. The source-RAM-only original-ROM
GameMode task-two route reached `$90ed-$9115` for ordinary area type, pipe,
alternate-entry and cloud paths; the title task-two route reached the
`OperMode` early return. The native queue bytes match the reference at `$01`,
`$20`, `$08`, `$10`, and the unchanged title value `$80`. The focused smoke
also proves every table value, both pipe entries, and title preservation.

`mysmb.area-music-smoke`, `mysmb.platform-purity`, and the Win32 self-test
passed on x86 and x64. The x86 and x64 normal-route native traces have the
same SHA-256 `628848D00C1934AF04FC268DA3C930F955EB208BFABF8DDBD7AC51D3694433DA`.
The shared core relinked as a DOS16 MZ (the pre-existing OpenNT
`OLDNAMES.LIB` warning remains). Refreshed artifacts are `mysmb16.exe`
`B7DED6EFBF17E06877F75577F34780B6541D6600E8B8B5F36E8F58C9AFADEA05`,
`mysmb32.exe` `C2301D9381A73743730B13439A80098EE13D8573348CE88BB8276D3991BAB4BE`,
and `mysmb64.exe` `1CC58667681F0966DDBAE9E5D70E346B5790C865206E3BDBD496E4F8C71E217C`.

## S3 admission: player/area-entry initialization chain

S3 receives exactly `PlayerStarting_X_Pos`, `AltYPosOffset`,
`PlayerStarting_Y_Pos`, `PlayerBGPriorityData`, `GameTimerData`,
`Entrance_GameTimerSetup`, `ChkStPos`, `SetStPos`, `ChkOverR`, `ChkSwimE`,
and `SetPESub` through accepted ledger event
`transfer-084-t18-s4-to-t29-s3-area-entry`. The eleven labels are open at the
**274 / 1,992** baseline and form one contiguous source chain from `$9116`
through `$9196`; S3 forecasts all eleven as ROM-match complete, for a maximum
**285 / 1,992**.

The shared owner is the portable player/area-entry boundary. The ROM track
binds each source table byte and compares the complete routine in source order:
the page, force, facing/high-Y, player-state, collision and halfway writes;
water/swimming branch; normal and alternate entry index selection; position,
attribute and palette sequence; timer reload gate; `JoypadOverride` vine path;
water bubble path; and final `GameEngineSubroutine = $07` handoff. Palette,
vine and bubble routines remain separate shared-game collaborators and are
called in the original sequence, never reimplemented by a platform adapter.

The original-ROM route enters through the GameEngine task-zero dispatch and
may establish only source-RAM preconditions at a frame boundary; it may not
inject a leaf program counter or stack. Its fixtures cover ground and water,
normal and alternate entry, timer reload and preservation, vine and bubble
branches. The operational track adds an entrance-focused project-owned smoke,
x86/x64 builds, OpenNT DOS16 link, platform-purity check, and one refreshed
three-executable package for the chain P. S3 cannot credit a member until both
the ROM-equivalence and operational tracks pass.

## S3 P1: shared-entry implementation and preliminary route evidence

P1 binds all five data regions in shared C and restores the complete source
write/call order through `SetPESub`. It removes the non-source scroll-position
write and defensive index exits, preserves the priority table's adjacent timer
dummy byte at index eight, restores the timer stores in `$07f8`, `$07fa`,
`$07f9` order, and calls the shared vine and bubble owners at the original
branch positions. `Setup_Vine` now retains its source sound queue write and
unbounded reachable slot progression; `SetupBubble` has one shared C owner
used by both the entrance and bubble-handler callers.

The controlled original-ROM GameEngine route reached `$9131-$919a` for the
normal, alternate, vine and water fixtures. The focused entrance smoke covers
the resulting data bindings and RAM markers. It passes on Win32 x86 and x64,
alongside the platform-purity gate; the shared source also compiles and links
as a DOS16 MZ. The package hashes are `mysmb16.exe`
`BBCD0251AEA05AB2693B4FAE6DEC4F7F9BB21E8B92101278CF43FD2EF6AFB1F0`,
`mysmb32.exe` `3EB44802AB63BE1906CE1379EC6EDDA9DAD3390C255C4AC9D1395E0`,
and `mysmb64.exe` `488D91CBB0BCEE5D4758EAE8AB6045BA30703BBEFD42996004CDC4627E4B28E9`.
This is an implementation checkpoint, not S3 closure: return-boundary
reference capture and the final node-by-node evidence update remain required.

## S3 P2: carry-correct bubble collaborator and final package

The source `SetupBubble` sequence shifts `PlayerFacingDir`, loads either zero
or eight into Y, and then executes `TYA` followed by `ADC Player_X_Position`.
`TYA` preserves the carry left by `LSR`; facing right therefore adds `$09`,
not `$08`.  The shared bubble collaborator now preserves that machine-level
effect for both `Entrance_GameTimerSetup` and its pre-existing bubble-handler
caller.  The entrance and bubble/OAM smokes assert the resulting `$31` and
`$49` X coordinates respectively.

The controlled source-RAM-only GameEngine route remains the ROM track: normal,
alternate, vine and water fixtures each execute `$9131-$919a`, covering every
S3 branch without synthetic PC or stack injection.  An attempted recorder
rebuild for a narrower RTS-boundary capture stalled in its isolated external
dependency build; it is not counted as evidence.  The established route
coverage plus the static `$9116-$919e` control/data/call audit are the ROM
evidence, while the focused native tests provide the independent operational
track.

`mysmb.area-entry-smoke`, `mysmb.bubble-oam-smoke`, and
`mysmb.platform-purity` pass on x86 and x64.  The shared sources compile into
the OpenNT DOS16 MZ; the linker continues to emit its pre-existing
`OLDNAMES.LIB` warning after producing the executable.  P2 artifacts are
`mysmb16.exe` `29AB94C5769B4BACD46FF6C9C3050B6F6E4FE9899ECC505E9B7CD51582CDDE44`,
`mysmb32.exe` `5F13B7C461042C0382E6EE5CC8783FB7474D730A692F42D6AC7711E411C2C451`,
and `mysmb64.exe` `274AD1E83935A8B5F72613FF44F46FAA1FEA28A6F40D4417023B92CDE1C3F857`.

## S3 closure: player/area-entry initialization chain

S3 closes **11 / 11** expected labels: `PlayerStarting_X_Pos`,
`AltYPosOffset`, `PlayerStarting_Y_Pos`, `PlayerBGPriorityData`,
`GameTimerData`, `Entrance_GameTimerSetup`, `ChkStPos`, `SetStPos`,
`ChkOverR`, `ChkSwimE`, and `SetPESub`.  The resulting conformance count is
**285 / 1,992**.  No label is deferred or transferred.

The data labels are bound byte-for-byte from `$9116-$912b`; the routine labels
are audited in source order from page/force/facing/state initialization through
alternate-entry selection, palette call, timer gate, override-vine branch,
water-bubble branch, and the `$07` engine-subroutine handoff.  The source route
exercised those branches through ordinary GameEngine dispatch.  Operational
evidence is the focused x86/x64 smoke and purity pass, the DOS16 compile/link,
and the P2 three-artifact package above.  `src/game` remains the sole owner of
all entry, vine, and bubble business behavior; no platform source was changed.

## S4 admission: life-loss, game-over and player-exchange state chain

S4 receives exactly `HalfwayPageNybbles`, `PlayerLoseLife`, `StillInGame`,
`GetHalfway`, `MaskHPNyb`, `SetHalfway`, `GameOverMode`, `SetupGameOver`,
`RunGameOver`, `TerminateGame`, `ContinueGame`, `GameIsOn`,
`TransposePlayers`, `TransLoop`, `ExTrans`, `DoNothing1`, and `DoNothing2`
through accepted ledger event `transfer-085-t18-s4-to-t29-s4-life-mode`.
All seventeen labels are incomplete at the **285 / 1,992** baseline. S4
forecasts all seventeen as ROM-match complete for a maximum **302 / 1,992**.

The admitted chain is the complete shared terminal-mode state boundary from
the half-way-page data through the residual return leaves. Its one shared C90
owner is `terminal_modes.c`; `frame_root.c` remains only the already-declared
GameEngine/operation-mode dispatcher. The chain includes the forward
`TransposePlayers` collaborator because both `PlayerLoseLife` and
`TerminateGame` call it before their terminal result. It does not take
ownership of `LoadAreaPointer`, `ScreenRoutines`, or rendering/text leaves.

The ROM comparison covers `$91bd-$92af` in source order: all sixteen
half-way-table bytes; lose-life screen/sprite/music/life writes; all
world/level/index/nybble/page outcomes; the three-way GameOver JumpEngine
selection; setup, Start/timer and termination branches; ContinueGame write
order; carry-qualified seven-byte player-record exchange; and the `$06c9=$ff`
residual store plus return. A source-RAM-only GameEngine fixture family reaches
this state boundary naturally for surviving and final loss, Game Over with
Start/timer outcomes, and one/two-player termination. It never injects a leaf
PC or stack.

The operational track begins with `mysmb.mode-smoke`,
`mysmb.oper-mode-dispatch-smoke`, `mysmb.local-death-music-smoke`, and
`mysmb.platform-purity` on x86/x64. Each implementation P must also build the
OpenNT DOS16 MZ, refresh all three required artifacts, and document their
hashes. S4 may credit a label only after both tracks establish its data,
control-flow, state-write and caller/result semantics.

## S4 P1: state-machine structure and loss-return repair

P1 establishes source-named shared C leaves for the half-way-page selection,
SetupGameOver, RunGameOver, TerminateGame and GameOverMode dispatcher while
retaining the already separate ContinueGame and TransposePlayers calls. The
half-way data remains private to the life-loss state owner. No host or
platform source changes.

The audit found a concrete source-order defect in the frame root. `GameRoutines`
dispatches `PlayerLoseLife` once; after its `ContinueGame` return, the ROM
continues the current GameEngine tail and uses the new entry subroutine only on
the next frame. The C root was re-dispatching the newly written subroutine in
the same frame. It now records that the current GameRoutines slot has already
run and retains only the object/timer tail. `mysmb.mode-smoke` proves that the
surviving-life path leaves the entry subroutine at zero rather than executing
the entrance initializer immediately.

The dispatch smoke fixtures were also corrected to preserve source-reachable
preconditions: NMI decrements DemoTimer before GameMenuRoutine, and ColdBoot's
screen-disable increment precedes SetupGameOver's increment. Focused
`mysmb.mode-smoke`, `mysmb.oper-mode-dispatch-smoke`,
`mysmb.local-death-music-smoke`, and `mysmb.platform-purity` pass on x86 and
x64. The shared C90 sources compile and link into the OpenNT DOS16 MZ, with
the existing `OLDNAMES.LIB` linker warning. P1 artifacts are `mysmb16.exe`
`6E9A9040AD7D870AE6C003845AAFAEFC73D77A779B0C35945D920CACEBB45999`,
`mysmb32.exe` `F65C52079AEC6FEA3EDC7CD3177C04FCF235D5CD3E4FC0E44CAF2A4E443AC426`,
and `mysmb64.exe` `9483AE9DF1862AFA2989AE1903CF80A8369DB4AB491FF49BDFD876526DF20E35`.

This is an implementation checkpoint, not S4 closure. The original-ROM
fixture family, per-label state/control evidence, and inventory updates remain
required before any of the seventeen labels can be credited.

## S4 P2 and closure: controlled ROM routes and terminal-mode chain

P2 adds six source-RAM-only fixtures to the owner-local reference recorder.
After a 600-frame ordinary warmup, they enter normal NMI processing for a
surviving loss, final loss, Game Over setup, Game Over timer wait, single-player
Start termination, and two-player Start continuation.  They do not inject a
program counter or stack.  Their aggregate PC coverage proves the source
branches at `$91cd-$9215` (surviving half-way selection and continuation),
`$91cd-$91e8` (final-life mode handoff), `$9218-$9236` (GameOverMode setup),
`$9218-$9246` (RunGameOver wait), `$9218-$9263` (single-player termination),
and `$9218-$92a9` (two-player exchange and continuation).

The static source comparison closes the remaining node-level details: all
sixteen `HalfwayPageNybbles` bytes are `$56,$40,$65,$70,$66,$40,$66,$40,$66,$40,$66,$60,$65,$70,$00,$00`; `PlayerLoseLife` writes screen gate, sprite-zero,
silence and decremented lives before its signed branch; `StillInGame` derives
the table index from world and level bit one; `GetHalfway` retains LSR carry
across TYA before high/low nybble selection; `MaskHPNyb` uses the original
greater-than screen-page reset; and `SetHalfway` calls exchange before
ContinueGame.  `GameOverMode` selects setup, screen routines or run from its
task; setup, waiting and both Start outcomes are independently routed.  The
two-player route proves the descending seven-byte `TransLoop`, carry-clear
continuation result and player flip; the solo route proves `ExTrans` carry-set
title return.  `DoNothing2` returns before `DoNothing1`'s `$06c9=$ff` residual
store in SecondaryGameSetup.

The independent native tests `mysmb.mode-smoke`,
`mysmb.oper-mode-dispatch-smoke`, `mysmb.local-death-music-smoke`, and
`mysmb.platform-purity` pass on x86 and x64.  The shared C90 source links to
the OpenNT DOS16 MZ; its existing `OLDNAMES.LIB` warning remains non-fatal.
P2 artifacts are `mysmb16.exe`
`6E9A9040AD7D870AE6C003845AAFAEFC73D77A779B0C35945D920CACEBB45999`,
`mysmb32.exe` `0197F9C8AA69E258A36E6E9CA6EDB257602A88F68DDC9B2791DBEAF61C6749D3`,
and `mysmb64.exe` `6E67453D9774266701D045D1CA50080553E475BE56C72EDA874E5B44C34851A1`.

S4 closes **17 / 17** expected labels: `HalfwayPageNybbles`,
`PlayerLoseLife`, `StillInGame`, `GetHalfway`, `MaskHPNyb`, `SetHalfway`,
`GameOverMode`, `SetupGameOver`, `RunGameOver`, `TerminateGame`,
`ContinueGame`, `GameIsOn`, `TransposePlayers`, `TransLoop`, `ExTrans`,
`DoNothing1`, and `DoNothing2`.  The conformance total becomes **302 / 1,992**.
No scoped node is deferred or transferred.  `src/game` remains the sole owner
of game behavior; the reference recorder is validation-only and neither
Windows nor DOS source contains a terminal-mode branch.

## S5 admission: area-parser dispatch and scenery-selection chain

S5 receives exactly `AreaParserTaskHandler`, `DoAPTasks`, `SkipATRender`,
`AreaParserTasks`, `IncrementColumnPos`, `NoColWrap`, `BSceneDataOffsets`,
`BackSceneryData`, `BackSceneryMetatiles`, `FSceneDataOffsets`,
`ForeSceneryData`, `TerrainMetatiles`, `TerrainRenderBits`, and
`AreaParserCore` through the accepted source-order receipt from M2 T18 S4.
All fourteen labels are open at the **302 / 1,992** baseline and are forecast
to become complete, for a maximum **316 / 1,992**.

This is one continuous parser-dispatch data chain from `$92b0` through the
AreaParserCore handoff. The shared C90 owner is the area-parser family. The
ROM route starts with source RAM only at a normal NMI boundary and reaches the
ordinary GameEngine parser call; fixtures cover parser task zero and nonzero,
column increment/wrap, background/foreground scenery selection and terrain
bit routing. It may not inject a leaf program counter or stack. The source
track compares vector selection, increment/carry/order, table bytes and every
shared-RAM read/write before the later renderer boundary. The operational
track runs parser-schedule and parser-buffer focused smokes, x86/x64 builds,
OpenNT DOS16 link, the purity gate and the three required artifacts once per
implementation P. S5 does not take ownership of S6's metatile/block-buffer
renderer leaves or S7's area-stream decoder.

## S5 P1: restore backloading parser order

P1 restores the `AreaParserCore` backloading prefix in shared C.  In the ROM,
when `BackloadingFlag` is nonzero, `ProcessAreaData` runs once before
`RenderSceneryTerrain`; the renderer then performs its own second call before
the block-buffer commit.  The previous C path kept only the latter call, so a
first row-14 stream control object could not affect the scenery/terrain column
being prepared.  `mysmb_area_parser_task_step` now executes the prefix only
for the source Core vector slots and only while backloading.

The parser-column smoke now supplies a source-shaped row-14 terrain control
object and proves terrain control five, background scenery two and the `$54`
staging metatile all arise in the same task-seven column.  The audit also
found a stale test expectation in selector-seven VRAM submission: source
`InitBuffer` transfers buffer two for selectors six and seven, but clears it
only for six.  The shared implementation already matched that behavior; the
buffer-commit smoke now asserts selector seven preserves `$0340/$0341` while
it clears buffer one.

`mysmb.area-parser-column-smoke`, `mysmb.parser-schedule-smoke`,
`mysmb.parser-buffer-commit-smoke`, and `mysmb.platform-purity` pass on x86
and x64. The shared C90 source links into the OpenNT DOS16 MZ with the existing
non-fatal `OLDNAMES.LIB` warning. P1 artifacts are `mysmb16.exe`
`6D10344BB3EF3E3019CB1952072BD6BEB38CCD4BB94D4A5F4604446A73B51FEF`,
`mysmb32.exe` `3BFDD8F7D10030BDFFC744052494B176A75C942CB010DBE178BD0174A2E7822C`,
and `mysmb64.exe` `20FCDABAAF6D9DBC7A39B795A6D7505E1A698C3AEED2E6C728C794F34D83FDDC`.

This is an implementation checkpoint, not S5 closure. Source-RAM ROM routes,
the exact vector/data-table audit, and per-label completion dispositions remain
required before any of S5's fourteen labels may receive credit.

## S5 P2: natural parser-dispatch ROM route

P2 adds the `t29-parser-dispatch` owner-local reference fixture. After a
600-frame ordinary warmup, it writes only source RAM at an NMI return to select
normal GameEngine task eight, parser task eight, zero VRAM selector and the
first parser column. Eight following ROM frames naturally execute
`AreaParserTaskHandler` and its `RunParser` caller. The route never redirects
the program counter or supplies a stack.

The resulting PC coverage records `$92b0-$92c8` eight times, the two
`IncrementColumnPos` entries at `$92db-$92f6`, and both source Core-vector
passes through `$93fc` and the ordinary object/parser tail. It establishes the
real dispatcher cadence separately from the P1 backloading regression. The
shared-game source is unchanged from P1; the three P1 artifacts remain the
verified package identities: `mysmb16.exe`
`6D10344BB3EF3E3019CB1952072BD6BEB38CCD4BB94D4A5F4604446A73B51FEF`,
`mysmb32.exe` `3BFDD8F7D10030BDFFC744052494B176A75C942CB010DBE178BD0174A2E7822C`,
and `mysmb64.exe` `20FCDABAAF6D9DBC7A39B795A6D7505E1A698C3AEED2E6C728C794F34D83FDDC`.

This remains a non-closing evidence checkpoint: exact source table values and
all fourteen individual control/data dispositions are still pending.

## S5 P3: local scenery and terrain data-consumer proof

P3 adds `mysmb.area-parser-data-smoke`, a local-only consumer test for the
seven admitted scenery/terrain data labels.  It binds the owner-local PRG at
runtime and independently derives the source column result from the ROM's
offset, page-residue, three-metatile, foreground-overlay, terrain-bit and
block-buffer-bound operations.  It covers all three background families across
their three page residues and sixteen columns, all foreground families, all
four area types and sixteen terrain controls, cloud masking, and the world-8
water/castle exception.  It contains no ROM table bytes.

The existing task-zero/nonzero schedule, backloading ordering and buffer
commit smokes remain the control-flow checks.  The ordinary source-RAM-only
parser-dispatch route continues to cover the real `AreaParserTaskHandler`
cadence and both Core-vector calls; an attempted synthetic backloading state
at the title warmup boundary was rejected because the original ROM correctly
remains in its own preload loop without the preceding area-initialization
route.  It is not counted as route evidence.

`mysmb.area-parser-data-smoke`, `mysmb.area-parser-column-smoke`,
`mysmb.parser-schedule-smoke`, `mysmb.parser-buffer-commit-smoke`,
`mysmb.area-data-smoke` and `mysmb.platform-purity` pass on Win32 x86 and
x64.  The shared source links as an OpenNT DOS16 MZ with the pre-existing
non-fatal `OLDNAMES.LIB` warning.  The refreshed package identities are
`mysmb16.exe` `6D10344BB3EF3E3019CB1952072BD6BEB38CCD4BB94D4A5F4604446A73B51FEF`,
`mysmb32.exe` `3BFDD8F7D10030BDFFC744052494B176A75C942CB010DBE178BD0174A2E7822C`,
and `mysmb64.exe` `20FCDABAAF6D9DBC7A39B795A6D7505E1A698C3AEED2E6C728C794F34D83FDDC`.
This remains an implementation checkpoint: per-label source-audit
dispositions and tracker closure are still pending.

## S5 closure and S6 admission: parser-dispatch data chain

S5 closes **14 / 14** expected labels at **316 / 1,992**:
`AreaParserTaskHandler`, `DoAPTasks`, `SkipATRender`, `AreaParserTasks`,
`IncrementColumnPos`, `NoColWrap`, `BSceneDataOffsets`,
`BackSceneryData`, `BackSceneryMetatiles`, `FSceneDataOffsets`,
`ForeSceneryData`, `TerrainMetatiles`, `TerrainRenderBits`, and
`AreaParserCore`. No scoped label is deferred.

The ROM-logic evidence is the source-order audit of `$92b0-$92fb`: zero task
becomes eight before the decrement; the decrement is both JumpEngine selector
and persisted task value; vectors select increment, graphics, graphics, core,
increment, graphics, graphics, core; the final zero task calls the attribute
owner only after its selected vector returns. `IncrementColumnPos` retains the
four-bit column wrap, page carry, five-bit block-column mask, and its shared
`NoColWrap` tail. `AreaParserCore` performs the backloading
`ProcessAreaData` call before its scenery handoff; the scenery owner performs
the second source call before block-buffer commit.

The seven data labels bind to the owner-local PRG ranges and neutral SHA-256
identities: `BSceneDataOffsets` `$12f7`/3
`C8FB459015DC06ADA0CF28025EFFB1FE66B28B04071D79445EDD939CA9AE888E`,
`BackSceneryData` `$12fa`/144
`81092B806E0D38BA25FDF7F23709576CC5C370B346BEB5EFC593430C38797DB7`,
`BackSceneryMetatiles` `$138a`/36
`DCAD9DD5AE28C1758B75C1833621E441BF9283ADC03EEAA39DE1B884C21589C9`,
`FSceneDataOffsets` `$13ae`/3
`B30329774A4F526EB0D891479A6692D643EAD0B84721003174C9D5992F66D84A`,
`ForeSceneryData` `$13b1`/39
`F7A296A83E79DA4582BF7A39D787F442F67772CBD91157225D826587BE79C367`,
`TerrainMetatiles` `$13d8`/4
`884F7AAF67D7AA593F4794B5437531B6010AE474DA705B2FB9C4B955A8819B4C`,
and `TerrainRenderBits` `$13dc`/32
`A942453254BE2BFDDE94EF03F0C301131BDCB643A53FB7F96AB111983DB8379E`.
The hashes are local verification metadata; neither table data nor the ROM is
tracked.

The ordinary source-RAM-only parser route reaches `$92b0-$92c8` on all eight
task slots, both increment paths `$92db-$92f6`, and both Core-vector passes
through `$93fc`, without program-counter or stack injection. The independent
operational track is P3's x86/x64 parser/data tests and purity check, plus the
shared DOS16 link and the three P3 artifacts. The inventory, progress report
and ledger record all fourteen completed labels.

S6 now receives exactly `RenderSceneryTerrain`, `ClrMTBuf`, `ThirdP`,
`RendBack`, `SceLoop1`, `RendFore`, `SceLoop2`, `NoFore`, `RendTerr`,
`TerMTile`, `StoreMT`, `TerrLoop`, `NoCloud2`, `TerrBChk`, `NextTBit`,
`EndUChk`, `RendBBuf`, `ChkMTLow`, `StrBlock`, and `BlockBuffLowBounds`
through accepted transfer `transfer-087-t18-s4-to-t29-s6-scenery-column`.
These twenty labels are open at **316 / 1,992** and forecast twenty matches,
for a maximum of **336 / 1,992**.

S6 is the contiguous shared `area.c` column-construction owner from `$92fc`
through `$9376`. Its ROM track compares metatile clearing, page-remainder
background selection, three-row and foreground overlays, terrain type/cloud,
world-eight and underground exceptions, bit-mask traversal, `ProcessAreaData`
handoff, block-buffer address and low-bound stores. Its operational track uses
the existing parser-column/data/buffer tests and any added focused renderer
smokes, x86/x64 builds, OpenNT DOS16 link, purity and one three-artifact
package per implementation P. It does not receive `ProcessAreaData` or any
area-object decoder leaf; that starts S7.

## S6 P1: staged-column and physical-page proof

The S6 source audit maps the complete `$9404-$94fc` sequence to
`mysmb_area_render_scenery_terrain_column` in shared `area.c`.  The routine
clears all thirteen staging slots, reduces `CurrentPageLoc` modulo three for
background selection, limits the background overlay to three rows below row
eleven, then applies nonzero foreground rows.  Its terrain scan preserves the
two source bytes, least-significant-bit-first order, cloud lower-byte mask,
world-eight water override, underground row-eleven replacement, and the
post-`ProcessAreaData` block-buffer threshold against the four owner-local
`BlockBuffLowBounds` values.  Source-label comments mark those C boundaries
without introducing a second renderer.

`mysmb.area-parser-data-smoke` now independently calculates both source
states from the locally bound PRG: the thirteen-byte `MetatileBuffer` at the
`RendBBuf` handoff and the final collision-qualified physical block-buffer
column.  It covers every background family, page residue and column on both
physical pages; each foreground family; all area types and terrain controls;
cloud masking; and the world-eight exception.  This closes the earlier gap in
which a correct final block buffer could conceal an incorrect staging column.
It remains a consumer test and embeds no ROM data.

The audit also found legacy pre-play terrain/page helpers that synthesize a
look-ahead path outside the source `AreaParserTaskHandler` cadence.  They
depend on `ProcessAreaData` and object-stream state, which is outside S6's
received labels.  S6 does not extend or certify that path; S7 must replace it
as part of the complete source-owned area-stream route before it can supply
evidence for normal play initialization.

On x86 and x64, `mysmb.area-parser-data-smoke`,
`mysmb.area-parser-column-smoke`, `mysmb.parser-schedule-smoke`,
`mysmb.parser-buffer-commit-smoke`, `mysmb.area-data-smoke`, and
`mysmb.platform-purity` pass. The common C90 source links into the OpenNT
DOS16 MZ; the existing non-fatal `OLDNAMES.LIB` warning remains. P1 artifacts
are `mysmb16.exe` `6D10344BB3EF3E3019CB1952072BD6BEB38CCD4BB94D4A5F4604446A73B51FEF`,
`mysmb32.exe` `D97EB426EBFF244F1B65CF76420A766E1528C1E8CCE604DFEC36FF0A9119DF8B`,
and `mysmb64.exe` `FCC9FA1C202BB532053F7EC99707A2A369C4E6F5469BB6DD9F9AF42A70DDAB01`.
This is an implementation checkpoint, not S6 closure: the controlled
original-ROM route and individual completion dispositions remain required.

## S6 closure and S7 admission: scenery-column chain

S6 closes **20 / 20** expected labels at **336 / 1,992**:
`RenderSceneryTerrain`, `ClrMTBuf`, `ThirdP`, `RendBack`, `SceLoop1`,
`RendFore`, `SceLoop2`, `NoFore`, `RendTerr`, `TerMTile`, `StoreMT`,
`TerrLoop`, `NoCloud2`, `TerrBChk`, `NextTBit`, `EndUChk`, `RendBBuf`,
`ChkMTLow`, `StrBlock`, and `BlockBuffLowBounds`. No scoped label is
deferred. The natural parser route covers `$9404-$94fb`; the static source
audit and PRG-bound staged-column test establish the otherwise route-specific
background, foreground, cloud, world-eight and underground branches. The
operational evidence is P1's six focused x86/x64 tests, DOS16 link and three
artifacts. All business behavior remains in shared `area.c`.

S7 receives exactly `ProcessAreaData`, `ProcADLoop`, `Chk1Row13`, `Chk1Row14`,
`CheckRear`, `RdyDecode`, `SetBehind`, `NextAObj`, `ChkLength`, `ProcLoopb`,
`EndAParse`, `IncAreaObjOffset`, `DecodeAreaData`, `Chk1stB`, `ChkRow14`,
`ChkRow13`, `Mask2MSB`, `ChkSRows`, `LrgObj`, `NotWPipe`, `SpecObj`,
`MoveAOId`, `NormObj`, `LeavePar`, `InitRear`, `LoopCmdE`, `BackColC`,
`StrAObj`, `RunAObj`, `AlterAreaAttributes`, `Alter2`, and `SetFore` through
accepted transfer `transfer-088-t18-s4-to-t29-s7-area-stream`. These 32 open
labels begin at **336 / 1,992**, forecast all 32 as matches, and have a
maximum closing count of **368 / 1,992**. The shared owner is the existing
area-stream decoder in `area.c`; S7 is responsible for replacing the legacy
pre-play look-ahead shortcut with the source `ProcessAreaData` route, rather
than retaining a parallel initialization algorithm.

## S7 P1: end-of-stream active-slot continuation

The source audit found that `DecodeAreaData` reaches `EndAParse` on `$fd`,
returns to `ProcessAreaData`, then still executes `ChkLength` and the lower
slots of `ProcADLoop`. The prior C owner returned from the whole parser at
that marker, dropping active objects held in lower slots. It now preserves the
source fallthrough: an active terminal slot decrements, and the descending
loop continues through the remaining slots.

`mysmb.area-parser-terminal-slot-smoke` supplies a terminal current stream
item and an active saved lower-slot hidden coin object. It proves the latter
is rendered and its length transitions from zero to `$ff`, the exact
`EndAParse -> ChkLength -> ProcADLoop` outcome. It passes on x86 and x64 with
the parser-column, parser-schedule, area-data and platform-purity tests. The
common C90 source links into the OpenNT DOS16 MZ with the existing non-fatal
`OLDNAMES.LIB` warning. P1 artifacts are `mysmb16.exe`
`2C8D9054D98F15FCC31107E12A798D4B39C6E9C131BA214C9C6478BF8B973EB6`,
`mysmb32.exe` `C4EC561B1D1E92155EDB174C8AE8E524087079FD3F98FFC93917524C03171FF9`,
and `mysmb64.exe` `BE358277DBA10A2E0D16DEFF2C858DEF97040A1AC77E2F12E9D38A04A2A31637`.
This is an implementation checkpoint, not S7 closure.

## S7 P2: backloading row-14 attribute dispatch

`Chk1Row14` bypasses the behind-page rejection while `BackloadingFlag` is set.
The source subsequently reaches `StrAObj` and `AlterAreaAttributes`, even if
the row-14 object belongs to an earlier page. Shared C now saves that object's
offset, advances the stream cursor, and invokes the existing shared attribute
owner in the same path. The terminal-slot smoke proves terrain control five,
background scenery two, and the two-byte cursor advance for this case.

The focused parser tests and platform-purity gate pass on x86/x64; OpenNT
links the common source as DOS16 with the existing non-fatal `OLDNAMES.LIB`
warning. P2 artifacts are `mysmb16.exe`
`7FFD79B23BF59A1853DC6677F80C8A72ECF60F029DFF8F946D12DFBBCCD3CE6D`,
`mysmb32.exe` `3A8ABB1FCE60E86C63627A65D5A7C8F7906D2270B02F34C505ED554B3393AB7E`,
and `mysmb64.exe` `0702C4EB8AAD654242F664B840C011B49D47C023A7F17F5CA0B1AE8AF9DB7EAE`.

## S7 P3: row-13 loop-command marker

`Mask2MSB` recognizes row-13 `$4b` and increments `LoopCommand` before the
decoder reaches `LoopCmdE`. The shared parser now writes `$0745` at that
source point; it does not absorb the later game-engine loop consumer. The
terminal-slot smoke covers the marker and cursor advance. x86/x64 focused
tests pass and the common source links as DOS16 with the existing non-fatal
`OLDNAMES.LIB` warning. P3 artifacts are `mysmb16.exe`
`70BCAE3A5110B2CF22D5CD5FA77B861C77448877D5A6D22BEDD7EBFE149E7984`,
`mysmb32.exe` `6F45A66C0DFD10DECAFB148AF40C687827281DB2C76AB3CEDFBC747607169075`,
and `mysmb64.exe` `11C3C0DD06EB1E0FE39C6D6C333D1FC27857232E3EC4FD7FA423E5BC8F8CD2CD`.

## S7 P4: current-page preload termination

The `NormObj -> InitRear -> LoopCmdE` path now follows the source return
boundary. When an inactive object is on `CurrentPageLoc` while
`BackloadingFlag` is nonzero, the ROM clears `BackloadingFlag`,
`BehindAreaParserFlag` and `ObjectOffset`, then returns before `BackColC` can
compare its column, stage it, or advance `AreaDataOffset`. The former shared C
path incorrectly fell through the column branch. `mysmb.area-parser-terminal-
slot-smoke` now establishes that source state and checks all three cleared
bytes, unchanged cursor and unchanged metatile staging.

The focused area-stream chain tests (`mysmb.area-parser-terminal-slot-smoke`,
`mysmb.area-parser-column-smoke`, `mysmb.parser-schedule-smoke`,
`mysmb.area-data-smoke` and `mysmb.platform-purity`) pass on x86 and x64. The
same portable C90 owner links into the OpenNT DOS16 MZ with the existing
non-fatal `OLDNAMES.LIB` warning. P4 artifacts are `mysmb16.exe`
`E40B1A8501FDF70FC63293004D4BCFCE83489B67079C9256DAF2D68EC8983CBC`,
`mysmb32.exe` `9080D2438659CC63E34919EA0F3AB287D24F17BA123BA9B64AF49F2BB9EA5BA7`,
and `mysmb64.exe` `82495C19698524F9031976F511C719443A502A28346B8803FAF824C210981739`.
This remains an implementation checkpoint: the chain's complete
node-by-node source audit, legacy initial-area route replacement and final
dual-track closure are still required.

## S7 P5: source-owned initial area parser route

The title-area composition path previously rendered fixed terrain then copied
and scanned an area-stream snapshot to synthesize a partial object lead-in.
That bypassed the admitted `ProcessAreaData` three-slot state. It now performs
the source's twelve `AreaParserTaskControl` column sets: each set executes the
already translated two-column task sequence, then the shared NMI VRAM commit
consumes its buffer before the next set. The loop ends only after the ROM's
`ColumnSets` underflow to `$ff`; no copied `mysmb_game` or alternate stream
cursor remains on this production entry.

`mysmb.local-title-smoke`, `mysmb.local-title-oracle`,
`mysmb.local-title-bootstrap-smoke`, `mysmb.title-demo-smoke`, the parser
column/terminal-slot smokes and `mysmb.platform-purity` pass on x86 and x64.
The unchanged shared C90 owner links into the OpenNT DOS16 MZ with the known
non-fatal `OLDNAMES.LIB` warning. P5 artifacts are `mysmb16.exe`
`D492129CA82488C95EDBBA73581A3328763DA0BAE1589AE46A158D7CDB1BF9CB`,
`mysmb32.exe` `871D411DEDFD3103C3AE0182DAC8D63EC7C05AED67B0BD61B232F3FDB296D596`,
and `mysmb64.exe` `DE4EFDBE8B333B8B028E6F2A40732F04730D4942D5C805AA599A5EA307AC0566`.
This remains an implementation checkpoint: the scanner compatibility helpers
are retained for their separate legacy test consumers, but no production
initial-area caller uses them; final per-label audit and dual-track closure
remain required.

## S7 P6: final-slot behind-page loopback

`ProcADLoop` clears `BehindAreaParserFlag` before every descending slot. The
ROM therefore repeats `ProcessAreaData` only when slot zero leaves that flag
set; an earlier slot's behind-page skip is not sufficient. Shared C now resets
its corresponding loopback state at each slot. The terminal-slot smoke uses a
slot-two behind-page object, a slot-one active object and a slot-zero page
control object: the active length changes from one to zero exactly once,
instead of an invented second pass changing it to `$ff`.

The focused area-stream tests pass on x86 and x64, together with parser
scheduling, data and platform-purity checks. The common C90 code links into
the OpenNT DOS16 MZ with the existing non-fatal `OLDNAMES.LIB` warning. P6
artifacts are `mysmb16.exe`
`CA402E7AF77932DE44BAD68CEC054A3BFFDA14E9381AC0AA1E05D8C556CED4F7`,
`mysmb32.exe` `BFD495637A472080C4D7351E555F4D5F86C0E417264E4B06D0231EEB76F1E829`,
and `mysmb64.exe` `CB60DE551148AFB4F3F5610A47B29E021D87818436A0A5BAAB236241D93CB856`.

## S7 P7: source loopback state and backload completion

`ProcADLoop` now writes its descending slot to `ObjectOffset` (`$08`) before
each decode, and the outer parser repeats under either source condition:
the final slot's `BehindAreaParserFlag` or a still-set `BackloadingFlag`.
The artificial 255-pass escape was removed; the ROM has no such alternative
termination. Backload test streams now include the source-required
current-page object that reaches `InitRear`, so the loop ends by clearing the
flag rather than by accepting a truncated `$fd` stream.

`mysmb.area-parser-terminal-slot-smoke`,
`mysmb.area-parser-column-smoke`, `mysmb.parser-schedule-smoke`,
`mysmb.area-data-smoke` and `mysmb.platform-purity` pass on x86 and x64.
The common C90 code links into the OpenNT DOS16 MZ with the pre-existing
non-fatal `OLDNAMES.LIB` warning. P7 artifacts are `mysmb16.exe`
`F76FE63A5BCA852585C4E679FC74BA57EDF934D38B3289C29BD6C48F66066DE3`,
`mysmb32.exe` `0FEF848402E8FAB65DBDE7EEEAFC91297BBBB2F753BA19D3B24D36ED9CE1E0C3`,
and `mysmb64.exe` `6236B23DD448D6F89A5FAAED6CFBB382DCBE46C3545B635CF372474FCBFD7364`.

## S7 P8: row-14 attribute branch evidence

The source audit maps `AlterAreaAttributes -> Alter2 -> SetFore` to the
shared row-14 parser path. Its focused stream cases prove: d6 clear writes
terrain and background scenery; d6 set with a low value reaches `SetFore`
without touching `BackgroundColorCtrl`; and d6 set with values four through
seven writes `BackgroundColorCtrl` before forcing foreground scenery to zero.
No platform source participates in these writes.

The full focused area-stream set passes on x86 and x64, and shared C90 links
into the OpenNT DOS16 MZ with the existing non-fatal `OLDNAMES.LIB` warning.
The refreshed P8 artifact hashes remain `mysmb16.exe`
`F76FE63A5BCA852585C4E679FC74BA57EDF934D38B3289C29BD6C48F66066DE3`,
`mysmb32.exe` `0FEF848402E8FAB65DBDE7EEEAFC91297BBBB2F753BA19D3B24D36ED9CE1E0C3`,
and `mysmb64.exe` `6236B23DD448D6F89A5FAAED6CFBB382DCBE46C3545B635CF372474FCBFD7364`.

## S7 P9: ordinary parser route and DecodeAreaData handoff

P9 makes the existing `t29-parser-dispatch` source-RAM fixture available to
the native frame recorder as well as the isolated original-ROM recorder.  It
starts after a bounded 600-frame ordinary NMI warmup and writes only the
normal GameEngine mode/task, parser task, column and area-parser state.  No
program counter, return stack or parser leaf is injected.  The next eight
original-ROM frames cover the `ProcessAreaData` entry and descending loop,
the row-13/row-14/rear/length branches, `DecodeAreaData` through
`LeavePar`, and the normal small/large dispatch selection.

The shared C decoder now also preserves `DecodeAreaData`'s source-owned
zero-page handoff at `RunAObj`: `$07` contains the JumpEngine addend and `$00`
the selected object ID.  The terminal-slot regression asserts the original
small-object (`$16`, ID two), row-12 special-object (`$08`, ID five), and
warp-pipe large-object (zero, zero) results, in addition to the prior terminal,
backload, loop and attribute cases.  The native and ROM route agree on the
persistent parser state, staging metatiles and PPU-visible frame output.  The
final NMI sample may reuse `$00/$07` in later source routines, so it is not a
valid post-frame oracle for this parser-local temporary handoff; the focused
source-shaped regression observes it at the chain boundary.

`mysmb.area-parser-terminal-slot-smoke`,
`mysmb.area-parser-column-smoke`, `mysmb.parser-schedule-smoke`,
`mysmb.area-data-smoke` and `mysmb.platform-purity` pass on x86 and x64.  The
common source links as the OpenNT DOS16 MZ with the existing non-fatal
`OLDNAMES.LIB` warning.  P9 artifacts are `mysmb16.exe`
`D6C90F62D4A574594B2FE99076555D3892540ACD58807C7B357324B1354FCC48`,
`mysmb32.exe` `B09221D8B7A519E08DAB782A09D8B0601B4EE76EF61C20F7B94CB60C5934215C`,
and `mysmb64.exe` `231376C16CDA178A02E25C40D5F4320EE0570DFD8B47F69396AAD611C6589221`.
This remains a checkpoint: S7 will only close after each of its thirty-two
labels has a separately recorded control/read/write/call-order disposition.
