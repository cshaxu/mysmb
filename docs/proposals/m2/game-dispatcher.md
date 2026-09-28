# M2 candidate: Game frame dispatcher

## Status

**M2 T31 open; S4 implementation complete at 628 / 1,992.** Closed T30 precedes
this task in the source-order recovery plan. S1 through S3 are closed;
S4 remains the active packet for final cross-chain review. No successor is admitted.

## Exact task scope and chain plan

The 31 labels below (source lines 5315-5582) are all open at admission.
Task baseline is 540 / 1,992; intended match set is exactly these 31,
maximum 571 before any explicitly admitted corrective dependency. Existing
receiver is T24 S2; S1's two labels transferred and are now complete. Future S rows are plans,
not concurrent admissions or newly assigned custody.

| Planned S | Exact labels in source order | Shared owner / verification boundary |
| --- | --- | --- |
| S1 | `GameMode`, `GameCoreRoutine` | dispatcher.c entry table, controller copy, child-return gate |
| S2 | `GameEngine`, `ProcELoop`, `NoChgMus`, `CycleTwo`, `ClrPlrPal`, `SaveAB`, `UpdScrollVar`, `RunParser`, `ExitEng` | GameEngine caller/slot order and palette/parser tail |
| S3 | `ScrollHandler`, `ChkNearMid`, `ScrollScreen`, `InitScrlAmt`, `ChkPOffscr`, `KeepOnscr`, `InitPlatScrl`, `X_SubtracterData`, `OffscrJoypadBitsData`, `GetScreenPosition` | player scrolling, screen boundary and data helpers |
| S4 | `GameRoutines`, `PlayerEntrance`, `ChkBehPipe`, `IntroEntr`, `EntrMode2`, `VineEntr`, `OffVine`, `PlayerRdy`, `ExitEntr`, `AutoControlPlayer` | player-state vector and normal/pipe/vine entry branches |

Each S performs source mapping, C translation and both verification tracks
for its own chain. S2 verifies caller order without claiming child routines;
S3 verifies scroll carry/offscreen branches; S4 verifies all vector targets
and entry transitions. T closure adds one cross-chain matrix. No map-only
or one-label paperwork phase is created.

## S1 admission: GameMode and GameCoreRoutine

Scope/expected: `GameMode`, `GameCoreRoutine`, both open. Baseline 540,
expected two, maximum 542. Accept transfer-121 from T24 S2. The source entry
is OperModeExecutionTree or title RunDemo; exit is the selected setup child,
early return after GameRoutines, or GameEngine entry. Existing initialized
area/screen/setup callees retain their proofs. GameEngine and GameRoutines
bodies remain explicitly uncertified later-chain dependencies.

Create the shared dispatcher module and separate its two exact entry routines
from the NMI frame root. Extract the existing game-routine and engine bodies
into named shared-C callees without repairing their later-chain behavior or
granting credit. Remove the host-data-presence mode-selector fallback.
GameCoreRoutine copies SavedJoypadBits[CurrentPlayer] to the master byte,
calls GameRoutines once, reloads OperMode_Task, and enters GameEngine only
for unsigned task >= 3. All title/game callers use this one implementation.

ROM-logic proof requires exact vector bytes and source branches, original
NMI routes through tasks 0/1/2/3, a source-reachable life-loss task-changing
return, and normal GameEngine entry. Call-boundary evidence may prove these
two entry nodes without certifying later child interiors; every residual
must be attributed, not suppressed into a whole-frame match claim.
Independent tests verify selector targets, both controller offsets, call
order and post-child task gate, plus current frame-route regressions.
Build strict C90 x86/x64 and DOS16, check purity/startup, refresh three EXEs.

Owner ROM/disassembly remain non-redistributable local research inputs.
All temporary products and traces stay under ignored build/m2-t31-s1;
20 MB trace budget, twenty-second recorder limit, bounded fixture count.
S1 owns cleanup through T review. No PC/stack/ROM patch is allowed. Existing
owner authorization covers the three tracked artifacts; DOS is link-only.

## Acceptance

Dispatcher task-byte transitions and call ordering match ROM evidence; it contains no approximated child behavior.

## T30/S14 dependency counterexample

Accept for the planned dispatcher chain: original GameCoreRoutine checks
OperMode_Task after GameRoutines and returns when it is below three. Native
frame_root still executes the enemy/graphics tail after PlayerLoseLife has
changed that task to zero. The source-RAM life-loss counterexample retained
by [T30 S14](../../history/M2-T30-area-object-rendering.md#s14-admitted-dependency-correction)
shows persistent actor state changes absent from ROM. Require a task-changing
exit route and a normal task-three continuation at admission. This node
remains open; S14 does not implement or certify the dispatcher.

Legacy core-smoke and local-area-smoke also have invalid timer-dispatch
fixtures (setup task two and task $7f). Both fail on d67f9f5 before S14.
Repair their fixture contracts against this dispatcher scope before treating
them as full regression gates; do not alter gameplay to satisfy them.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
## Chain-delivery governance amendment

The fixed "map, migrate, equivalence audit, operational test, closure" S
sequence in this proposal is historical planning evidence only.  For the next
admission or continuation in this task, one S must deliver one bounded,
contiguous ROM control/data chain: it records the exact labels in source order,
its entry and exit, one shared C owner, predecessor/successor dependencies,
and one ROM route that exercises the chain.  Mapping, the shared-C repair when
needed, node-by-node control/read/write/table/call-order comparison, and the
operational proof belong to that same S.

The node inventory and ledger still retain a separate row and final
completion disposition for every label.  A chain P runs one common ROM replay,
focused tests, x86/x64 builds, DOS16 link, platform-purity check, and refreshes
the three required local target artifacts.  T closure adds only the
cross-chain route matrix and integrated three-target regression.  It must not
recreate those gates for each leaf.  A chain may not cross an unadmitted
dependency, a different shared-owner boundary, or a branch family requiring a
different ROM route.  The binding authority is
[the M2 chain-delivery rule](../../rules/EXECUTION.md#m2-chain-based-s-delivery).

## S1/P1: entry chain closure

Admission passed at 540 / 1,992, scope and expected set both exactly
GameMode and GameCoreRoutine. Actual result is **2/2 complete**, advancing
to **542 / 1,992 (27.21%)**; 137 mapped incomplete and 1,313 open remain.
No S1 label is deferred or transferred. T31 remains open; S2 is next.

| Node | Source binding and exact native owner | ROM-logic evidence |
| --- | --- | --- |
| GameMode | $aedc-$aee9; dispatcher.c / mysmb_game_mode | OperMode_Task read; original four vector words bind InitializeArea $8fe4, ScreenRoutines $8567, SecondaryGameSetup $9071, GameCoreRoutine $aeea; real Start route executes all four. Selector precondition is source-valid 0..3; invalid table indices are not certified. |
| GameCoreRoutine | $aeea-$aefd; dispatcher.c / mysmb_game_core_routine | CurrentPlayer selects SavedJoypadBits before GameRoutines; reload OperMode_Task after child, compare unsigned against three, return below three or enter GameEngine. Original NMI PC coverage exercises both $aefb branch outcomes, $aefd return and $aefe engine entry. |

Shared frame_root now calls the single GameMode entry and the same
GameCoreRoutine for title RunDemo. The ROM-absent task-one/no-PRG gameplay
fallback is removed. Existing child bodies move unchanged in scheduling
to game/engine.c, so the dispatcher does not call back into NMI orchestration.
GameEngine internals remain S2; GameRoutines internals remain S4. Their
extraction grants no credit. The former misplaced post-demo timer call is
now inside the existing engine body, before returning to RunDemo's caller.
No platform source changes and platform-purity passes.

Four controlled source-RAM NMI routes change neither PC, stack, ROM nor
output. Surviving and final life-loss routes match all 1,782 persistent RAM
bytes and the complete recorded output on both widths. Scratch 0..7, CPU
stack and RAM PPU mirrors remain explicitly excluded. Two normal engine
routes verify each controller selection and the task-three continuation;
all output matches, while eight persistent VRAM bytes $0300-$0307 differ.
This is the existing mysmb_area_sync_player_palette call in the uncertified
engine, absent from the original GameEngine caller sequence. It is a required
S2 correction, not a complete-frame claim or an entry-node mismatch.

Independent entry tests link only dispatcher.c with observable child seams:
three setup targets and 512 combinations of player source / post-child task
give 515 cases per width. Every callback order, reload threshold and saved
controller byte is asserted. Sixty existing focused executions pass across
x86/x64 after five mode-test fixtures use ROM-valid task three instead of
the removed task-one shortcut. Core-smoke's live timer fixture likewise uses
task three rather than setup task two; local-area removes invalid task $7f.
These latter suites still fail later checks: core's ROM-free block replacement
expectation and local-area's timer-only buffer expectation despite the extra
engine palette command. Both identical failures reproduce against the prior
T30/S20 objects using the corrected inputs. No full-suite pass is claimed;
S2 owns the caller/buffer residual, and the existing block owner retains its
fixture debt. No failing expectation was removed or weakened.

Two ordinary 600-frame NMI routes cover title -> Start -> 1-1 -> movement,
and idle -> demo. x86/x64 recordings are identical, as are both routes
against the previous T30/S20 native recorder. Work/OAM RAM $0200-$07ff and
entry state match the original, excluding only the two RAM PPU mirrors.
Original output differs solely in PPU-control NMI-enable bit at cold-screen
samples: Start samples 1 and 202, idle sample 1 (original $90, native $10).
This unchanged snapshot/prologue debt is recorded separately; it is not
silently masked into output equivalence. The
[entry verifier](../../../test/verify_game_entry_routes.py) checks exact
vectors, PC routes, state and every declared residual. It takes an ignored
evidence directory and owner ROM argument; raw evidence remains only in
build/m2-t31-s1, below 20 MB, with twenty-second recorder limits. S1 owns
cleanup through T review.

Strict C90 x86/x64 compilation, both Windows self-tests and hidden-window
creation/message responsiveness pass. DOS16 compiles the same sources and
links MZ, retaining legacy conversion and OLDNAMES.LIB warnings. DOS still
lacks owner-resource binding and is link-only, not playable validation.
Both existing assets Windows EXEs also passed startup probes before this
repair. The owner's startup failure remains unreproduced; this entry repair
must not be reported as its established fix.

Similar-issue sweep: all production entry callers are frame_root's game-mode
and RunDemo paths, plus GameMode's task-three vector target. Both converge
on dispatcher.c. Exactly one child call and one post-child gate remain;
no platform owns selector, controller-master or task-return decisions.
Source material stays local and no standalone ROM/generated source enters
this commit. Prior explicit owner authorization covers the three existing
EXE artifacts, which are test outputs rather than release qualification.

Artifact `mysmb16.exe`: 253025 bytes; SHA-256 `6c43f135b1da66a4926b6718606cadd09e1e4955918102e972870c1a44cc8b13`.

Artifact `mysmb32.exe`: 310643 bytes; SHA-256 `56b7e6e95ae9471d1d1faec4f56442e01ca44b8b825fc1ae6e75c1538bd6a808`.

Artifact `mysmb64.exe`: 317704 bytes; SHA-256 `48222bba5d4e29f29a7f35d675b4f8305cb75d80332f520226bcd48960a69162`.

## S2 admission: GameEngine caller and tail chain

Baseline 542 / 1,992. Scope/expected are exactly the nine open labels
GameEngine, ProcELoop, NoChgMus, CycleTwo, ClrPlrPal, SaveAB,
UpdScrollVar, RunParser and ExitEng; maximum 551. Transfer-122 accepts
these from T24 S2. Admission is continuation under the owner-approved M2 goal.
Entry is GameCoreRoutine's task-three continuation, exit is ExitEng.
Shared owners are game/engine.c and extracted engine-tail helpers.

ROM-logic track audits the original $aefe-$af92 call sequence, six-slot
ProcELoop, slot-one/zero blocks, timer/palette/music order, unsigned and
sign-bit branches, SaveAB and parser handoff. Source-RAM NMI routes and
independent call-boundary tests verify the same decisions. Operational
track runs strict C90 x86/x64, DOS16 link, entry regressions, ordinary
Start/demo routes, platform purity and three refreshed EXEs per P.

The initial audit finds missing ProcessCannons/ProcessWhirlpools entries,
global actor passes outside the original slot dispatcher, and two-slot
block processing hidden inside a child. These are concrete call-boundary
dependencies: do not add no-op placeholders or certify GameEngine/ProcELoop
while they remain. Implement independently bounded tail corrections first;
keep S2 active until every retained node has both proofs or an accepted
exact transfer. No child interior receives credit or an unadmitted repair.
The original timer order, extra palette sync and missing music restoration
are owned by this caller chain. Existing enemy/leaf debt remains explicit.

Owner ROM and reviewed listing are non-redistributable research inputs;
all generated probes/logs/traces remain under ignored build/m2-t31-s2.
Use a 20 MB raw-trace budget and twenty-second recorder limits. S2 owns
cleanup through T review. Never alter reference PC, stack, ROM or output.
Prior owner authorization covers the existing three EXE artifacts; DOS
remains link-only until its separate resource binding debt is resolved.

## S2/P1: verified tail partial delivery

The nine-node admission gate passed at 542 / 1,992, expected nine and maximum
551. This P completes exactly seven nodes; S2 **remains active** with
GameEngine and ProcELoop incomplete. It is not an S or T closure.

| Node | Source / shared C mapping | Disposition |
| --- | --- | --- |
| NoChgMus | $af52; engine_tail.c, frame-counter and star-timer selection | ROM-match complete |
| CycleTwo | $af5d; engine_tail.c, final right shift and palette leaf | ROM-match complete |
| ClrPlrPal | $af64; engine_tail.c, source ResetPalStar branch | ROM-match complete |
| SaveAB | $af67; engine.c, save A/B then clear directional byte | ROM-match complete |
| UpdScrollVar | $af6f; engine_tail.c, control-six gate then parser/scroll gate | ROM-match complete |
| RunParser | $af8f; engine_tail.c, exactly one parser task call | ROM-match complete |
| ExitEng | $af92; shared parser tail return | ROM-match complete |
| GameEngine | $aefe; engine.c, partial caller sequence | Audited mismatch: missing cannon/whirlpool calls and global actor passes |
| ProcELoop | $af03; enemy/core.c legacy combined wrapper | Evidence incomplete: move six-slot schedule to caller and preserve each source-visible slot boundary |

Repairs follow source order: RunGameTimer now precedes ColorRotation;
the ROM-absent engine mysmb_area_sync_player_palette call is removed;
GetAreaMusic is invoked on the exact star-timer-four/interval-zero path.
The existing certified music selector gains external linkage only, with no
body change. NoChgMus/ClrPlrPal preserve the eight-bit CMP/BPL Y result:
the star gate applies to Y-high 0..1 or 130..255. UpdScrollVar similarly
preserves CMP #$20 / BMI: with no pending parser task, scroll $20..$9f
subtracts $20 and clears the second buffer offset before one parser call;
$a0..$ff takes the negative-result exit. Shared helpers move out of game.c
into game/engine_tail.c; Victory's UpdScrollVar uses the same implementation.

The [independent engine-tail test](../../../test/engine_tail_smoke.c)
executes 18,432 palette/music combinations per width, including every Y
high byte, slow/fast phase edges, zero/four/eight star boundaries and
interval gates. Another 1,024 cases cover every scroll byte, active/inactive
parser and control-six gate, observing values at the parser call boundary.
It links only the actual tail owner and observable music/parser seams.

Fifteen source-RAM fixtures enter the original NMI -> GameMode ->
GameCoreRoutine -> PlayerDeath -> GameEngine path. Both widths match all
1,782 persistent RAM bytes and all CIRAM/palette/OAM/audio/PPU output in
every sample; only zero-page scratch 0..7, CPU stack and two RAM PPU mirrors
are excluded, with **no output exclusions**. PC coverage reaches all seven
labels and both outcomes of the Y, star-zero, star-four, interval, palette
speed, pending-task and signed-scroll decisions. The controller-six early
return is covered by exact source audit and the isolated native seam;
these NMI fixtures do not cover it because NMI clears that input. This
limitation is explicit in the [verifier](../../../test/verify_engine_tail_routes.py).
No PC/stack/ROM/output patch or synthetic return is used.

The previously observed eight-byte palette command residual is gone.
Two additional ordinary 600-frame Start/right and idle/demo routes remain
byte-identical to S1 and across widths. Their persistent work RAM and
recorded output match original except the already recorded cold-screen
PPU-control bit at Start samples 1/202 and idle sample 1. No claim is made
that this independent snapshot debt is fixed. Raw traces total 10,780,593
bytes below the 20 MB budget, in ignored build/m2-t31-s2, with twenty-second
per-recorder limits and S2 cleanup ownership through T review.

Sixty existing focused runs and both 515-case entry tests pass, alongside
both engine-tail tests. The old local-area test now passes its timer-only
buffer assertions and later fails its historic warp-text fixture; core-smoke
still fails its ROM-free block metatile expectation. Neither is suppressed
or represented as a full-suite pass. Strict C90 Windows builds, self-tests,
hidden-window responsiveness and platform purity pass. DOS16 links the same
core with existing conversion/OLDNAMES warnings; resource binding is still
missing, so DOS remains link-only. Three existing EXEs are refreshed under
the owner's explicit artifact authorization; no raw ROM or generated C is
committed. Startup failure remains unreproduced, not claimed fixed.

Similar-issue sweep: the only remaining palette-sync production caller is
game.c's screen-task owner, outside this GameEngine chain. Music has exactly
SecondaryGameSetup and this source star-expiry caller. Both GameEngine and
Victory share the same parser tail; no platform source changes. Missing
cannon/whirlpool scheduling, global actor scans and block-slot exposure
remain required S2 work, not empty stubs or certification exceptions.

Progress is **549 / 1,992 (27.56%)**: seven new complete nodes, 139 mapped
incomplete (including the two retained S2 nodes), 1,304 open. Expected nine,
actual seven so far. All nine remain in S2 custody; no transfer or closure.

Artifact `mysmb16.exe`: 253057 bytes; SHA-256 `f4757046079a613846e1be3bf799d35c0d1ae3794a26f1cde75fb06c6b6e2ade`.

Artifact `mysmb32.exe`: 310859 bytes; SHA-256 `13b6b3b9e2450a9590ecd017c9099db589e7e732844aa7555f03f45a805879bd`.

Artifact `mysmb64.exe`: 317956 bytes; SHA-256 `906a95d138cd45792b9dd22a4410d7b4ce3c6d12d8854152d7eb7da69018db26`.

## S2 continuation: combined caller-structure delivery in progress

This is unfinished work within S2, not another admission, completed P or
node-credit event. Keep the seven accepted tail matches and the two pending
callers. Do not package ProcELoop alone; batch the remaining caller structure
and its admitted dependencies before the next three-artifact delivery.

The shared engine_slots owner now exposes fireball followed by six ordered
enemy/floatey pairs, and block slot one followed by zero. Each caller writes
ObjectOffset before its child. Enemy data availability no longer gates the
whole actor phase. The child slot function no longer performs its caller's
store; Victory supplies its own slot-zero store. The old whole-array wrappers
are removed, and block body extraction changes no block-state algorithm.

The independent engine_slots test observes all fifteen child calls, slot
arguments, ObjectOffset and unconditional dispatch with absent source data.
It and enemy-stream, block-OAM, object-array-layout and collision-regression
tests pass on both widths (ten executions). Two controlled original-NMI
routes exercise inactive enemy slots with inactive or active floatey numbers.
Both native widths match all 1,782 persistent RAM bytes and complete output;
the reference executes six enemy/floatey entries, five loop backedges, one
loop exit and two block entries. The
[slot verifier](../../../test/verify_engine_slots_routes.py) preserves exact
counts and comparison exclusions. PC totals alone do not prove ordering;
source audit and the independent native call observations establish that
part. These routes do not certify active enemy child behavior.

The two ordinary 600-frame Start/right and idle/demo routes remain identical
to the accepted S1 native recordings and between widths. Original output
retains only the documented cold-screen PPU-control residuals at Start
samples 1/202 and idle sample 1. No new output exception is introduced.
Evidence is contained in ignored build/m2-t31-s2-p2 under the existing
twenty-second per-recorder and 20 MB trace limits; S2 owns cleanup. Existing
assets are still P1 products, not a delivery of these uncommitted changes.

The remaining structural audit identifies these concrete dependencies:

- Original EnemiesAndLoopsCore is at $c047 in the corrected owner-ROM map.
  Its active branch enters RunEnemyObjectsCore ($c882); the existing native
  child still substitutes normal/retainer/power-up handling and omits the
  high-bit duplicate-enemy branch. Caller-loop evidence does not certify it.
- RunEnemyObjectsCore selects RunNormalEnemies for IDs below $15 and the
  original special-object vector otherwise. RunNormalEnemies owns graphics,
  bounds, terrain/enemy/player collisions, timer-gated movement and offscreen
  cleanup for the current slot. Existing engine-wide actor scans do not
  reproduce those boundaries; merely moving all scans inside the loop would
  multiply work and still use the wrong dispatch.
- ProcessCannons ($b9bc) and ProcessWhirlpools ($b7b8) have no production
  entry. They must become real shared-game implementations at their source
  call positions after MiscObjectsCore and before FlagpoleRoutine. Empty
  wrappers and reuse of unrelated bullet movement are not acceptable.

These child interiors retain their current receiving owners. Before repairing
them, the coordinator must register the exact dependency scope and receiving
acceptance, together with original branch routes; the current caller-seam
authorization does not silently permit new child algorithms. S2 stays active
through that work, and GameEngine/ProcELoop retain their incomplete status.

## S2 admitted dependency amendment: cannons and whirlpools

The coordinator accepts transfer-123 from T24 S2 under the owner's continuing
M2 mandate. This is an explicit necessary-dependency exception to the original
caller-only scope, inside the same active S and combined delivery; it creates
no parallel S or future T number. The original nine-node run and its seven
matches remain unchanged. The added run starts at 549 / 1,992, expects all
22 named incomplete labels below and has a maximum of 571. If the two retained
original callers also close, the combined ceiling is 573. No credit is yet
assigned. The task's original 31-node plan remains, with these 22 explicitly
added dependencies (combined task ceiling 593 from its baseline 540).

- Water chain: `ProcessWhirlpools`, `WhLoop`, `NextWh`, `ExitWh`,
  `WhirlpoolActivate`, `LeftWh`, `SetPWh`, `WhPull`.
- Cannon chain: `CannonBitmasks`, `ProcessCannons`, `ThreeSChk`, `FireCannon`,
  `Chk_BB`, `Next3Slt`, `ExCannon`, `BulletBillXSpdData`, `BulletBillHandler`,
  `SetupBB`, `ChkDSte`, `BBFly`, `RunBBSubs`, `KillBB`.

ProcessWhirlpools, WhirlpoolActivate and ProcessCannons enter as audited
implementation missing; BulletBillHandler is mapped with incomplete evidence;
the other eighteen are open. Shared game owners implement the two original
GameEngine successors after MiscObjectsCore and before FlagpoleRoutine.
No platform files acquire decisions. The corrected ROM entry addresses are
$b7b8 and $b9bc. Existing gravity, offscreen, collision and OAM children are
reused only at their exact source call boundaries, without claiming their
interiors. Enemy dispatch interiors are still outside this added scope.

Source audit covers descending slot order, table bindings, eight-bit carry
and signed-result branches, masked random selection, cannon timer and spawn
writes, bullet initialization/kill/movement/collision/drawing, whirlpool
extent/center selection, alternating horizontal pull and gravity handoff.
Controlled original NMI source-RAM routes cover both branch families through
the real engine, without PC/stack/ROM/output patching. Independent native
tests check arithmetic boundary cases and observable child handoffs, followed
by affected ordinary-route regressions. Original logic proof and operational
proof remain separate. One combined build/package refresh delivers all three
EXEs; DOS remains link-only. The existing provenance, ignored build containment,
twenty-second run limit, 20 MB raw-trace budget and S2 cleanup ownership apply.

The dependency admission gate passes with 22 unique incoming labels, expected
delta 22 and ceiling 571 from 549. The existing two pending callers remain
separately accounted; this is not an assertion that they are complete.

Whirlpool implementation progress: shared game/whirlpool.c now implements
ProcessWhirlpools through WhPull at the GameEngine call position. It preserves
descending five-slot selection, disabled-area flag retention, water flag clear
before timer exit, signed eight-bit page differences, right-extent and center
carry, horizontal direction/phase/collision gates, and the tail gravity call
with player offset zero, force $10 and maximum speed one. ObjectOffset is
not changed by the source register-only X assignment. The existing shared
gravity primitive is reused; no platform or player-state child is repaired.

Independent tests execute 9,600 extent/position/length/phase/collision/area/timer
combinations plus an overlapping-slot precedence case on each width. They
observe gravity arguments, single-call behavior and ObjectOffset preservation.
Twelve controlled original NMI routes take PlayerChangeSize's real idle-return
branch and then reach the original GameEngine; no leaf-PC or stack injection
is used. The NMI increments FrameCounter before the engine, so fixture phase
inputs explicitly account for that increment. Every one of the nine source
conditional branches has both outcomes in the reference PC evidence. All
eight labels execute. Both native widths match all 1,782 persistent RAM bytes
and the entire recorded output, with no output exceptions. The
[environment verifier](../../../test/verify_engine_environment_routes.py)
checks these claims against ignored evidence. This is controlled route proof,
not an ordinary water-level playthrough. Three-target packaging, cannon
implementation and the combined S2 delivery remain pending; no tracker
completion credit or separate small P is claimed for this intermediate work.

Cannon implementation progress: game/cannon.c now occupies the original
post-MiscObjectsCore, pre-ProcessWhirlpools engine position. Its caller scans
slots 2, 1, 0, stores ObjectOffset at each turn, selects the cannon from the
source random-byte/mask pair, decrements a nonzero cannon timer even while
TimerControl inhibits spawning, and skips handling a freshly spawned bullet.
BulletBillHandler preserves the PlayerEnemyDiff page-SBC carry through its
distance ADC, both kill branches, direction/speed/state/frame-timer/sound
writes, defeated gravity before horizontal movement, and the offscreen,
relative-position, bounding-box, player-collision and graphics child order.
The reviewed ROM tables at $b9ba and $ba31 match the two mode masks and two
direction speeds used here; the source-valid hard-mode selector is 0 or 1.

Existing erase and player-collision children gain external linkage only;
their bodies are unchanged and are not certified by this caller work. The
old regular BulletBill movement path is a different enemy ID ($08); it is
not used as a substitute for the cannon variant ($33).

The independent cannon test passes on both widths: 512 random/mask cases,
1,024 carry-dependent distance cases, shared-cannon descending-slot spawn
and timer effects, and observable normal/defeated/paused child sequences.
Sixteen controlled original NMI routes cover both outcomes of all fifteen
cannon/handler conditionals. Eight area/random/timer/spawn routes match all
1,782 persistent RAM bytes and complete output on both widths. Eight active
bullet routes retain persistent RAM differences and are **not accepted**:
motion, state, coordinates, velocity, bounding-control and frame-timer arrays
match, but original object dispatch and child graphics do not. The current
diagnostic preserves every difference in ignored cannon-current.json; it
does not mask them into a whole-frame-equivalence claim.

Concrete remaining child counterexamples:

- The original RunEnemyObjectsCore vector selects NoRunCode for ID $33.
  Native EnemiesAndLoopsCore instead calls the normal-enemy child, modifying
  relative/offscreen bytes before a later cannon kill or bounds exit. This
  is part of the retained enemy-dispatch dependency, not a cannon-distance
  workaround.
- Original CheckForBulletBillCV/SBBAt selects Y minus one, attributes 3 plus
  priority while EnemyFrameTimer is nonzero, zero saved state and graphics
  selector 8. Existing bullet graphics lacks this variant branch. Active
  routes differ at $ef and OAM Y/attribute bytes; output-latch equality in
  that sample does not excuse divergent OAM backing RAM.
- Source EraseEnemyObject clears EnemyFrameTimer at $078a+slot. Existing
  erase implementations use $078e+slot. The controlled routes do not yet
  distinguish that stale-timer case; admit and exercise this exact child
  before claiming kill-path equivalence.
- Existing PlayerEnemyCollision remains restricted/simplified. The current
  routes use the real PlayerChangeSize return and do not prove contact with
  Mario. General collision fidelity remains a named dependency.

After cannon integration, the twelve whirlpool routes still match the saved
original traces on both widths. Ordinary Start/right and idle/demo recordings
remain identical to the accepted native baseline, with only the previously
documented original cold-screen output-latch residual. No new child repair
outside the admitted scope, completion credit, artifact refresh or P commit
is claimed. Continue the combined S2 work with exact child dependency intake.

## S2 cannon-child dependency intake

The coordinator accepts transfer-124 (RunEnemyObjectsCore, JmpEO, NoRunCode,
EraseEnemyObject) from T19 S5 and transfer-125 (CheckForBulletBillCV, SBBAt)
from T17 S6 under the continuing owner mandate. All six are open. Scope is
these six labels; the initial expected subset is NoRunCode, EraseEnemyObject,
CheckForBulletBillCV and SBBAt. Baseline 549, expected four, maximum 553 for
this added run. The combined forecast across all S2 runs is 577. The two
full enemy-vector dispatch nodes remain incomplete until their entire source
target selection and per-slot adapters are implemented and proven; no credit
is given for fixing only the cannon target. All 37 received S2 labels retain
explicit custody. No additional S or separate small P is created.

Implementation scope includes the original NoRunCode target selection in
enemy/core.c, the single shared EraseEnemyObject and both callers, and the
cannon-specific operand preparation, Y/attribute/state selection and working
byte outputs in oam/bullet_bill_gfx.c. Other actor graphics and general player
collision interiors remain outside this correction. Erase must clear the
eight source arrays, including EnemyFrameTimer at $078a+slot, and preserve
unrelated timer slots. The bounds path must use the same erase owner rather
than a second copy. Cannon graphics takes prepared relative/offscreen values
from its caller and reproduces the source branch through the existing drawing
consumer; this does not certify the whole EnemyGfxHandler tree.

Source audit uses the corrected original vector and $c998 erase entry,
CheckForBulletBillCV/SBBAt and their source-defined operand/output handoffs.
Controlled original NMI cannon routes add stale-timer and graphics-work-byte
sentinels; independent tests observe exact erase writes and NoRunCode side
effects. Compare persistent RAM and OAM backing as well as latched output.
The existing dual-verification, provenance, build containment, run/trace
limits and combined three-artifact delivery apply. No active-bullet mismatch
may be converted into an output exception to achieve closure.

## S2/P2: combined slot, environment and cannon-child delivery

This combined P completes **27 additional labels**, advancing **549 -> 576 /
1,992 (28.92%)**. S2 retains all 37 labels and remains active with 34 complete.
GameEngine, RunEnemyObjectsCore and JmpEO are still audited mismatches: the
complete enemy vector and current-slot adapters must replace the engine-wide
actor passes. No S/T closure, transfer of unfinished callers or full-game
conformance claim is made. Original run expected nine/actual eight; environment
run expected 22/actual 22; child run expected four/actual four with two dispatch
labels retained pending. This is one batch delivery, not a P for each leaf.

| Completed node | Source line / shared owner |
| --- | --- |
| `ProcELoop` | 5339 / game/engine_slots.c |
| `ProcessWhirlpools` | 6519 / game/whirlpool.c |
| `WhLoop` | 6526 / game/whirlpool.c |
| `NextWh` | 6546 / game/whirlpool.c |
| `ExitWh` | 6548 / game/whirlpool.c |
| `WhirlpoolActivate` | 6550 / game/whirlpool.c |
| `LeftWh` | 6577 / game/whirlpool.c |
| `SetPWh` | 6586 / game/whirlpool.c |
| `WhPull` | 6587 / game/whirlpool.c |
| `CannonBitmasks` | 6785 / game/cannon.c |
| `ProcessCannons` | 6788 / game/cannon.c |
| `ThreeSChk` | 6792 / game/cannon.c |
| `FireCannon` | 6809 / game/cannon.c |
| `Chk_BB` | 6832 / game/cannon.c |
| `Next3Slt` | 6840 / game/cannon.c |
| `ExCannon` | 6842 / game/cannon.c |
| `BulletBillXSpdData` | 6846 / game/cannon.c |
| `BulletBillHandler` | 6849 / game/cannon.c |
| `SetupBB` | 6862 / game/cannon.c |
| `ChkDSte` | 6876 / game/cannon.c |
| `BBFly` | 6880 / game/cannon.c |
| `RunBBSubs` | 6881 / game/cannon.c |
| `KillBB` | 6886 / game/cannon.c |
| `NoRunCode` | 9080 / game/enemy/core.c |
| `EraseEnemyObject` | 9198 / game/enemy/lifecycle.c |
| `CheckForBulletBillCV` | 13674 / game/oam/bullet_bill_gfx.c |
| `SBBAt` | 13682 / game/oam/bullet_bill_gfx.c |

ROM-logic evidence: two original slot routes, twelve whirlpool routes and 25
cannon/child routes match 1,782 persistent RAM bytes and every recorded output
byte on both widths. Zero-page scratch 0..7, CPU stack and the two RAM PPU
mirrors are the explicit exclusions; there are no output exceptions in these
controlled routes. Cannon coverage includes both outcomes of fifteen handler
branches, both priority-timer branches, seven original NoRunCode vector targets,
and erase counterexamples that clear $078a while preserving another slot's
$078e timer. The source vector/table binding is checked against the owner ROM.
Independent tests establish native callback order, exact argument/state inputs,
all six erase-slot write sets and cannon-specific graphics working bytes.
The prior fifteen tail routes also remain fully matched. Verifiers:
[slots](../../../test/verify_engine_slots_routes.py),
[whirlpools](../../../test/verify_engine_environment_routes.py),
[cannons and child corrections](../../../test/verify_cannon_dispatch_routes.py).

Implementation follows source owners: engine_slots supplies fireball and six
enemy/floatey pairs, then explicit block slots 1/0; whirlpool.c and cannon.c
provide real engine children. Seven NoRunCode targets return before normal
enemy processing. A single enemy/lifecycle.c erase owner replaces both copies
and clears the correct frame timer. Cannon graphics retains its original Y-1,
timer-dependent priority, prepared relative/offscreen inputs and graphics work
bytes. No platform file or gameplay fork is introduced. The unchanged generic
player-collision child is called at its source position but remains uncertified
for contact semantics; these controlled routes do not claim that child.

Operational evidence: strict C90 builds, 60 existing focused executions and
22 additional caller/child/affected regressions pass across x86/x64. The erase
regression's old $078e expectation was corrected to the ROM's $078a and now
also asserts $078e preservation. The legacy bullet test gains its missing
frenzy declaration include, with unchanged assertions. New T31 cannon fixture
and verifier names are separate from the preserved T30 cannon interfaces;
both recorder versions accept and execute the original T30 fixture again.
Ordinary 600-frame Start/right and idle/demo routes remain byte-identical to
the accepted native baseline. The existing original cold-screen PPU-control
residuals at Start 1/202 and idle 1 remain explicit and unrelated.

Windows self-tests and hidden-window creation/message responsiveness pass.
DOS16 links the same C sources as MZ with existing conversion and OLDNAMES
warnings; it remains link-only because owner-resource binding is absent.
No DOS gameplay or physical 486SX qualification is claimed. Historical
core/local-area full-suite fixture debts remain; this is not a full-suite
pass assertion. All three existing EXEs are refreshed under prior explicit
owner authorization, with no raw ROM, generated C or traces committed.
The owner-reported Windows startup failure remains unreproduced.

Similar-issue sweep: both erase implementations now converge on one owner;
no remaining $078e erase write exists in game sources. The cannon variant is
separate from regular enemy ID $08. Source NoRunCode handles all seven targets,
not just $33. Existing global actor scans and missing full-vector adapters are
retained as the three named parent gaps. Platform purity and governance gates
remain required before this P is committed. Raw evidence stays in the ignored
S2 build directories under the declared run/trace limits; S2 owns cleanup.

Artifact `mysmb16.exe`: 255633 bytes; SHA-256 `75ce99495598e186bf5c22edd84c30adaaebe2e0e4f9e985147a27ae193b11f3`.

Artifact `mysmb32.exe`: 314547 bytes; SHA-256 `065978180e384958d3152fe8c9e682c73c3bb7c04c343cc623adfdd2a4ebb677`.

Artifact `mysmb64.exe`: 321784 bytes; SHA-256 `0e0d766d14148d3601b744ac1c366319790c539d088305f2a5fd0efc2d0c0192`.

## S2 remaining dispatch run

The three remaining received labels are GameEngine, RunEnemyObjectsCore and
JmpEO, all audited mismatches. Register a continuation forecast at 576 /
1,992: scope and expected set are those three, maximum 579. Custody remains
S2; this does not create another S or reopen the 34 completed labels.

First expose current-slot entries from the existing actor-array routines,
preserving their bodies and temporary bulk callers until the original vector
can replace those callers as a complete group. No child-body match credit or
new actor algorithm follows from this extraction. Compare the extracted
aggregate behavior with the committed P2 implementation and retain existing
source proofs. Then bind all original vector targets and remove GameEngine's
extra global passes; verify every target/slot at independent call boundaries
and with controlled original NMI routes, plus ordinary integrated regressions.
The current scope permits child call-seam extraction, not unadmitted repairs
to collision, movement or graphics interiors. A missing vector target must
receive explicit dependency intake before implementation; it cannot become
a stub or silently borrow an unrelated child.

The extraction must preserve bulk-loop early exits and inner-loop continues;
simple text replacement across nested loops is not acceptable. Existing
compatibility entry points are temporary integration scaffolding, not an
additional gameplay path to retain after GameEngine migration. Keep the
combined three-product P delivery and source/operational verification split.

Current-slot preparation now exposes nineteen entries across objects,
endgame_objects, enemy/frenzy and oam/bowser_gfx, declared by
game/enemy/actor_slots.h. Seventeen movement/state families, firebar processing
and Bowser drawing retain their existing aggregate callers until integration.
Hammer Bros retains its sixth slot. Firebar's inner ball-loop continues remain
local; its legacy injury return is represented by a temporary aggregate-stop
result so extraction does not accidentally process later slots. That result
is not claimed as an original register or source return convention.

Operational extraction evidence in ignored build/m2-t31-s2-p3 compares all
2,048 RAM bytes with committed P2 for 760 cases on each native width, covering
nineteen entries, five active-slot masks (including six active slots), four
phase/timer combinations and two states. Cases include player-contact inputs;
all snapshots agree across predecessor/current and x86/x64. Strict C90
compilation passes. In addition, 108 controlled native recordings and four
600-frame Start/right or idle/demo recordings are byte-identical to P2.
Raw snapshots and recordings total 17,285,036 bytes, within the 20 MB budget;
each recorder invocation has a twenty-second limit. These are preservation
checks, not new original-ROM equivalence claims or credit for child bodies.

The source audit identifies remaining integration limits explicitly:
RunFirebarObj dispatch covers IDs $1b-$22, whereas the legacy child filters
out $20-$22 and treats only $1f as long. Original BowserGfxHandler writes the
duplicate object's coordinates/state/direction/ID and switches ObjectOffset;
the legacy direct two-half renderer does not reproduce that state path.
WarpZoneObject has no implementation. Exact dependency intake precedes any
repair of those child algorithms. No empty targets, borrowed unrelated actor
paths, or passing predecessor snapshots can close these gaps. The three parent
labels remain incomplete, the total remains 576, and the combined P has not
been packaged or committed.

## S2 missing-vector-target dependency intake

The coordinator accepts WarpZoneObject from M2 Td S5 custody under the
owner's continuing M2 mandate (transfer-126). This is the concrete missing
target required by RunEnemyObjectsCore, not a new T or S. Its incoming state
is open; scope and expected set contain only WarpZoneObject, baseline 576,
maximum 577 for this added run. Together with the three retained parent
labels, the combined ceiling is 580; S2 receives 38 labels, 34 complete.
Other deferred timer/fireball nodes remain with their existing receivers.

Implement source $b7a4: ScrollLock zero returns; otherwise the bitwise AND
of Player_Y_Position and Player_Y_HighPos controls the return. On zero,
clear ScrollLock, increment WarpZoneControl with eight-bit wrap, then call
the existing EraseEnemyObject for the current slot. Do not replace this
unusual AND with a guessed height comparison. Source/vector-byte audit and
controlled NMI warp routes must prove the branches and erase handoff;
independent tests vary both Y bytes, lock, control wrap and all six slots.
The existing provenance, trace limits and combined delivery apply. No new
match is granted until both verification tracks are complete.

The original full vector may now call existing current-slot actor entries.
Parent target-selection tests identify every original target, independently
of unfinished child interiors. Remove each migrated special-object aggregate
call from GameEngine in the same change to avoid double updates. Normal-enemy
global movement/collision passes remain an explicit integration gap until
RunNormalEnemies' source call chain replaces them; no parent completion is
claimed from the special-object vector alone.

The missing-target admission gate passes: one unique open label, expected
delta one and ceiling 577. Current implementation reloads ObjectOffset in
enemy/core.c and routes all source ID families through their current-slot
entries. GameEngine no longer calls the firebar, platform, Bowser motion,
Bowser drawing, Bowser flame, star flag, fireworks or vine aggregate passes.
Vine's source slot-five rejection is retained. Large/small platform targets
still enter the combined legacy body; Bowser still uses its legacy motion and
drawing pair. Those are explicitly incomplete child-structure mappings, not
proof of the original target bodies or complete parent topology.

WarpZoneObject now implements the exact lock, bitwise-Y, wrapped increment
and erase sequence in the shared game layer. The
[dispatch test](../../../test/enemy_dispatch_smoke.c) checks all 54 valid IDs
across six slots, current-slot arguments, the existing compound child calls,
and 131,072 warp input combinations with full-RAM expected write sets.
The existing cannon-child test keeps its NoRunCode assertions and adds only
unexpected-call stubs for the newly linked child seams. Both tests pass on
x86/x64 under strict C90. The eleven retained focused tests also pass on both
widths. No platform source or host-specific gameplay branch changes.

Ten controlled original NMI warp routes cover all six slots, zero lock,
both bitwise-AND outcomes including a noncanonical high byte, control wrap,
and exact EraseEnemyObject entry. Both original conditionals take both edges.
All 1,782 persistent RAM bytes and the complete output match both native
widths, with no output exception. The
[warp verifier](../../../test/verify_engine_warp_routes.py) also binds all
34 original enemy-vector entries to their reviewed target addresses in the
owner ROM. That table check is not runtime evidence for every target.
The fixture uses RAM inputs at NMI, never PC, stack, ROM or output patching.
The 108 prior controlled native records and four ordinary 600-frame records
remain byte-identical to accepted P2 after this dispatcher integration.

Evidence remains in ignored build/m2-t31-s2-p3 under the admitted limits.
This is ongoing work in the same combined P: three-platform delivery is
pending, no tracker match is granted yet, and GameEngine/RunEnemyObjectsCore/
JmpEO remain incomplete. Next integration must restore the normal-enemy
current-slot call chain and the identified special-target structural gaps;
it must not declare closure while the extra normal-actor passes remain.

## S2 normal-enemy caller and movement dependency intake

Transfer-127 accepts seventeen open labels from T19 S5 into the same active
S2, under the continuing owner mandate: RunNormalEnemies, SkipMove,
EnemyMovementSubs, NoMoveCode, XSpeedAdderData, RevivedXSpeed, MoveNormalEnemy,
FallE, MEHor, SlowM, SteadM, AddHS, ReviveStunned, SetRSpd,
MoveDefeatedEnemy, ChkKillGoomba and NKGmba. Baseline 576, scope/expected
seventeen, added-run ceiling 593; combined remaining-run ceiling 597.
S2 now receives 55 labels, with 34 complete. No separate S/P is created.

This chain restores the ordinary-object entry sequence, movement-vector
selection and its normal-movement target. The two tables are adjacent to
ProcHammerBro in source but are consumed by this movement chain; Hammer Bro
interiors remain outside this intake. Shared enemy/movement.c owns the
normal-movement branch tree; caller/slot seams remain in shared game code.
Retain eight-bit state priority (d6 before d7 before d5), vertical-before-
horizontal calls, state-two direct horizontal entry, temporary speed adder
and restoration, hard-mode revival table, and Goomba timer-specific erasure.
Do not preserve the legacy defeated-enemy high-Y erasure as a substitute for
OffscreenBoundsCheck. Existing collision/graphics child interiors remain
uncertified and require separate exact intake for semantic repair.

Source audit covers $c8e0-$c934 and $ca77-$caf8 plus table bytes $c9d0-$c9d7.
Independent call-boundary tests exercise state precedence, timer/ID/frame/
hard-mode cases, temporary speed and restoration. Original controlled NMI
routes must reach these branches through the actual enemy loop; no leaf PC
or stack injection. Ordinary Start/demo and existing engine routes remain
regression gates, with every difference retained. The same combined build,
three-artifact delivery, local provenance and trace limits apply. This
intake grants no completion credit to the seventeen nodes or their children.

The vertical call boundary additionally requires MoveD_EnemyVertically,
MoveFallingPlatform and ContVMove from T17 S6 (transfer-128). The existing
parameterized gravity primitive lacks this source entry's exact-state-five
selection of force $20 instead of $3d. Accept those three open labels in the
same S and combined P: baseline 576, expected three, added-run ceiling 579;
combined ceiling 600, 58 received labels. The shared movement owner restores
that selector and reuses the existing gravity arithmetic. No other vertical
motion target or gravity-internal node receives match credit. The normal
NMI state-five cases must lose their $0434 force mismatch; graphics-work-byte
and OAM differences remain explicit unfinished child evidence.

Implementation progress in the same P: enemy/movement.c now owns
MoveNormalEnemy's full state-selection tree, both speed tables and the exact
MoveD_EnemyVertically state-five force selector. The ordinary portion of
objects.c calls terrain, enemy collision, player collision and timer-gated
movement in source order, replacing its inline defeated/revival/movement
approximation. It no longer erases a defeated actor merely because high Y is
two. The legacy graphics/ID early returns and separately scheduled special
normal-enemy movement remain explicitly pending caller integration.

The independent [movement test](../../../test/normal_enemy_movement_smoke.c)
passes 1,253,376 cases per native width: seventeen selected state combinations,
six slots, all 256 horizontal speed bytes, four IDs, two hard-mode values,
two frame phases and three interval timers. It observes gravity-before-
horizontal handoff, exact temporary speed/restoration, state priority,
revival writes, state-five force and erase/no-erase decisions. Both native
builds use strict C90. ROM bytes independently confirm both four-byte tables.

Thirty-two controlled original NMI routes execute all eleven movement-code
labels and all three vertical-entry labels. The power-up equality edge at
$caab is not exercised by these ordinary-enemy routes; the following BNE at
$caad is unconditional after the failed equality comparison. Other executed
movement conditionals take both outcomes. Native state, speed, force and
coordinate arrays agree after correcting the source state-five selector.
However **none of the 32 routes is accepted as whole-frame ROM equivalence**:
all retain differences at graphics working bytes $eb/$ec/$ed/$ef, and some
retain OAM backing differences. Complete latched output equality does not
override those failures. No extra exclusion or tracker match is introduced.
The diagnostic keeps full differences in normal-route-diagnostic.json and
source coverage in normal-source-coverage.json below the existing build root.
Raw snapshots, records and PC coverage occupy 18,414,084 bytes within the
20 MB allowance. Existing eleven focused tests on each width pass; ordinary
and prior controlled regression checks remain required after further edits.

Similar-issue sweep: the old normal-core defeated high-Y erase, partial
revival logic and direct movement block are removed from their production
caller. Other actor families' distinct movement/graphics/collision bodies
retain their own pending obligations. The new movement owner does not add
a timer gate or platform decision; its caller owns the timer. The three
vertical entries reuse existing gravity arithmetic, without claiming that
arithmetic's entire source family. S2 remains active at 576 with combined
delivery and caller/graphics dependencies unfinished.

## S2 background-entry prerequisite for the normal caller

Accept transfer-129 from T17 S6 for ten open labels: ExEBG,
EnemyToBGCollisionDet, DoIDCheckBGColl, HBChk, CInvu, YesIn, ExEBGChk,
SubtEnemyYPos, EnemyJump and DoSide. Scope/expected ten at baseline 576,
added-run ceiling 586; combined ceiling 610, 68 received labels. This same-S
dependency is necessary because the existing terrain function is only the
walking-enemy body: calling it for every original normal ID would incorrectly
probe flying enemies. Restore the source state/Y/ID entry gates, jump-enemy
landing/bounce path and current-slot handoffs to the existing walking,
hammer and side-check children. Those child interiors remain uncertified.

The same integration extracts existing player-collision special cases to
current-slot entries without changing their algorithms, moves their calls
behind the caller's single PlayerEnemyCollision boundary, and removes the
corresponding global scans. Keep each incomplete child contract explicit;
this does not certify generic collision fidelity. Independent caller tests
must observe complete ordering, timer decisions and post-collision ID reload.
Original NMI and existing actor regressions must retain all discrepancies.
No new P, output exception, platform gameplay or fake no-op child is allowed.

Current integration adds enemy/normal.c as the single RunNormalEnemies and
EnemyMovementSubs caller owner, shared by every target build list. It always
performs attribute clear, offscreen, relative position, graphics, bounding
box, background collision, enemy collision, player collision, timer-gated
movement and final bounds checking. Graphics' legacy handled return no
longer exits the caller. Movement reads the current ID after collision.
Both NoMoveCode IDs ($09/$13) select no movement; $12 selects MoveNormalEnemy,
including its exact state-five path, rather than a second late egg pass.

The six existing special player-collision scans now have current-slot
entries and one caller seam. Their aggregate compatibility interfaces keep
their original early-stop contract but have no production GameEngine call.
Walking terrain's side/bump bodies are extracted once and reused by EnemyJump.
The new background entry rejects flying IDs before walking terrain and
routes Hammer Bro to its existing terrain child. Bullet and Piranha graphics
and Hammer Bro terrain are removed from movement entries; compatibility
aggregate interfaces retain those old combined operations for existing tests.
GameEngine loses eighteen remaining late normal-actor calls, in addition to
the eight special-actor calls already removed. No global actor pass remains
between ProcELoop and the player OAM sequence.

The [normal caller test](../../../test/normal_enemy_caller_smoke.c) verifies
756 combinations per native width: all 21 IDs, six slots, both initial timer
states, and collision children that preserve state, change the movement ID,
or change the timer. A graphics child returning handled and a collision child
clearing the flag cannot skip the remaining caller sequence. Child callbacks
observe order, arguments, attribute clear, offscreen handoff and both NoMove
targets. Both strict C90 builds pass; the owner ROM's 21 movement vector words
also match the reviewed address map. This proves those boundary tests, not
the unfinished child algorithms. OpenNT large-model compilation of the new
normal.c succeeds and emits an object; no new DOS runtime or link claim.

All 108 accepted controlled native records and four 600-frame ordinary
records remain byte-identical to P2. Eleven existing focused tests pass on
both widths after integration. The 32 normal movement ROM routes retain
their previously reported graphics-work-byte/OAM differences and remain
unaccepted as whole-frame matches. Background-entry branch-specific ROM
evidence and broader actor-family routes are still needed. Existing regular
Bullet Bill movement differs from original MoveBulletBill; the specialized
player-collision adapter is still not the complete original shared collision
tree. Firebar, platform and Bowser child gaps remain explicit. They cannot
be certified merely because this caller now reaches them in the right order.

S2 remains at 576 with no additional completion credit, commit or artifact
replacement. The combined delivery must finish the admitted proofs and
resolve the named structural dependencies rather than retain a second
frame-wide execution path or declare the old limited tests full-game proof.

The [background-entry test](../../../test/enemy_background_entry_smoke.c)
now exercises the production entry and children on both native widths under
strict C90. Per width, 608,082 rejected-entry combinations cover six slots,
all 54 vector IDs, every Y byte and eight state patterns. They require all
2,048 RAM bytes to remain unchanged. A further 24,576 jumping-enemy cases
cover every speed byte, six slots, empty/non-solid/solid/bumped-block samples
and a side wall. Their expected landing, vertical-force, speed and direction
writes are explicit, including the block-buffer pointer scratch writes.
The wall lies on the pre-landing probe row: landing moves the probe upward,
so reversing against that wall afterward would fail the call-order test.
Both widths pass. Results are retained as background-entry-tests.json in
the existing ignored P3 root; no raw ROM trace or larger trace budget is added.

This is operational evidence for the admitted entry contract, not original
NMI equivalence or certification of the walking/hammer/side child interiors.
The source audit covers the wrapped Y gate ($06 through $c1), state d5,
Spiny's $25 threshold, ID dispatch and EnemyJump's wrapped speed comparison.
The ten labels remain incomplete pending their original-route evidence.
No additional dependency intake or artifact replacement accompanies this
test addition; S2 and the existing combined P remain open.

Original-route follow-up extends the existing normal fixture to cases 32..55,
without changing cases 0..31 or introducing a new fixture mechanism. These
24 source-RAM setups execute through NMI, GameEngine and the real current-slot
enemy caller. Original PC coverage reaches all ten admitted background labels:
ExEBG, EnemyToBGCollisionDet, DoIDCheckBGColl, HBChk, CInvu, YesIn, ExEBGChk,
SubtEnemyYPos, EnemyJump and DoSide. The state/Y/Spiny gates, jump speed gate,
empty/non-solid probes and solid landing paths take both relevant outcomes.
EnemyJump's repeated Y guard cannot take its rejection edge through this
caller because the identical earlier gate has already passed. The power-up
ID equality edge is not covered by these normal-enemy routes; it needs the
existing power-up caller path, not injection into a normal-ID vector entry.

All 24 scenarios run against both native widths. Their latched output agrees,
but no whole-frame match is accepted: 23 scenarios retain graphics working
byte/OAM differences, and the Bloober scenario (50) additionally differs at
enemy Y $cf, relative Y $03b9 and bounding coordinates $04b1/$04b3. These are
retained as observed whole-chain differences, not attributed to a repaired
child or silently excluded. The green jumping-enemy routes have no additional
persistent differences outside the reported graphics bytes/OAM. Full results
and PC counts are in background-route-diagnostic.json in the P3 build root.
Raw records and coverage now total 19,106,916 bytes, within the unchanged
20 MB limit; each recorder call has a twenty-second timeout. Both native
recorders and the reference recorder were rebuilt for the extended fixture.
Global progress remains 576; original-route reachability does not itself
grant completion credit or certify the unfinished children.

## S2/P3: current-slot integration checkpoint

This combined P delivers the actor-slot extraction, RunNormalEnemies and
EnemyMovementSubs owner, admitted normal/vertical/background entries, warp
handler, and removal of late engine-wide actor scans. It is an implementation
checkpoint in the existing S, not S closure or whole-game certification.
The previously described ROM differences remain visible and all 34 pending
labels retain their status. Global progress remains 576 / 1,992; 34 of this
S's 68 received labels are complete from earlier parts.

Both Windows targets rebuild all 58 shared C sources with strict C90 warnings
as errors, link successfully and pass their self-tests. Hidden two-second
launch probes find a MySMB window and responsive message handling on x86 and
x64 without user input injection. This does not reproduce or claim to fix
the owner's earlier startup report. OpenNT large-model compilation and DOS
link succeed with the existing conversion/OLDNAMES warnings. DOS still lacks
owner-data binding and remains link-only, not a playable DOS validation.

Eleven existing focused tests per native width pass. The previously recorded
dispatch, movement, normal-caller and background-entry tests provide their
bounded operational evidence. All 108 controlled native runs and four
600-frame ordinary runs remain byte-identical to P2. The platform-purity
gate passes; no platform file changes are included. Original normal and
background routes retain every reported mismatch; their latched-output
agreement is not substituted for persistent-RAM agreement.

The three existing owner-authorized test artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257897 | 9082c7172f12fb97a1bd628471ab900762c2c057b8a0a118c5c72a1270a85c7e |
| mysmb32.exe | 320456 | 1341789e671f9e8895642b692179d04f6c86e6f80e39f74a2ca087c3e445e8c2 |
| mysmb64.exe | 327180 | d1d5aae9f7d0d1e576822a76a8894b9afc0cb59ea573ca414e46b70af0b66ac4 |

Builds, logs, raw comparisons and neutral result JSON remain under the
existing ignored P3 root. This checkpoint adds no new S, dependency intake,
trace exclusion or completion credit. Next work must distinguish the admitted
caller's own proof from unfinished child contracts; platform/Bowser/firebar
dispatch structure and the stated source-route coverage gaps still prevent
claiming complete parent equivalence.

Post-P3 implementation, within the existing EnemyJump/DoSide receipt: a
similar-issue sweep found two production implementations of EnemyJump, one
inline in EnemyToBGCollisionDet and one used by the star path. Both callers
now reach the existing shared EnemyJump function, which retains its own
wrapped Y and speed checks and delegates DoSide to the single existing
side-check child. This removes the duplicated bottom/side branch bodies;
it does not repair or certify that child's remaining source differences.
The star caller uses slot five, so the reused bump child's existing sound
condition remains disabled as before. No other power-up movement changes.

Both native widths pass strict C90 compilation, the background-entry matrix
and the existing collision regression including star bounce/status-bar cases.
All 24 background fixture records per width are byte-identical to P3, including
the known ROM differences. Temporary incremental builds and neutral results
use ignored build/m2-t31-s2-p4; two reused raw-record files total 8,842 bytes,
below a 1 MB diagnostic allowance, with thirty-second bounded commands and
S2 cleanup ownership. P3 evidence is preserved. This remains uncommitted work
for the next combined P; published artifacts and completion counts are unchanged.

The [engine caller test](../../../test/engine_caller_smoke.c) adds the missing
whole-parent ordering check around the existing slot and tail tests. It observes
actor processing, player offscreen/relative/graphics, block replacement and
processing, misc, cannons, whirlpools, flagpole, timer/status, color/palette,
SaveAB and parser order. Across all 256 button bytes and both timer results,
the palette child changes the button byte so an early SaveAB would fail;
the parser child requires the saved byte and cleared direction partition.
Unexpected player/mode calls fail explicitly. All 512 cases pass on each
native width with strict C90. This test uses observable child contracts,
not their internal algorithms, and is registered with CTest.

An independent local audit decodes the actual owner's GameEngine instruction
span and checks all nineteen direct JSR operands, in source order, against
the reviewed symbol map. This includes the two distinct BlockObjectsCore
call sites and the conditional music/palette/parser calls. Neutral addresses
and original coverage counts are recorded in engine-source-calls.json under
the P4 root. Operand binding and the caller test do not by themselves certify
the parent or any child: the existing original-route mismatches and dispatch
structure obligations remain open. No completion count is changed.

Coverage reconciliation: the initial P4 lookup searched only P3 records and
therefore reported no hit at the GameEngine GetAreaMusic call site $af4f.
The retained S2/P1 and P2 tail scenarios 1, 7 and 14 each execute that call.
Combining these existing records covers all nineteen original direct call
sites; no new fixture is needed. engine-source-calls.json now retains the
specific contributing record names and counts instead of treating a local
lookup miss as a program coverage gap.

The current P4 native recorders rerun all fifteen existing engine-tail
scenarios against the retained original S2 records: thirty width runs match
all 1,782 persistent RAM bytes and the entire latched output, and x86/x64
records agree. There are no new exclusions. The result is retained in
current-tail-equivalence.json under the bounded P4 root. This supersedes any
claim that music restoration lacks original execution evidence.

Parent-versus-child review for the next combined delivery:

| Boundary | Evidence now available | Remaining obligation |
| --- | --- | --- |
| GameEngine body | Nineteen original call operands and executed sites; 512 native ordering cases per width; six-slot/block-order tests; fifteen current tail equivalence routes | Final combined delivery review and node accounting; this evidence does not certify enemy child interiors |
| RunEnemyObjectsCore / JmpEO | Original vector bytes and current-slot dispatch tests | Distinct large/small platform and Bowser target contracts remain unresolved |
| RunNormalEnemies / EnemyMovementSubs | Original vector, caller ordering tests and real normal/background routes | Existing graphics and specialized child differences remain explicit; no complete parent claim |
| EnemyJump / DoSide | One shared implementation; source branch audit, background matrix, star regressions and byte-identical P3 route preservation | Side-check child contract remains uncertified; original routes still retain graphics differences |

This review fixes the evidence index without moving any node, increasing the
scope, granting child credit or inventing a new S. Published artifacts remain
the committed P3 versions until the next combined implementation delivery.

## S2/P4: parent scheduler and warp proof

The combined P records two completed labels: GameEngine and WarpZoneObject.
Global progress moves from 576 to 578 / 1,992; S2 has 36 complete and 32
incomplete received labels. No node transfers or S/T closure occur.

GameEngine credit covers its own source call order, slot/block scheduling,
timer/status handoff, music/palette branch tree, SaveAB writes and parser
tail. The nineteen original direct call operands and executed call sites,
independent native caller/slot/tail tests and fifteen current original-NMI
tail comparisons establish that boundary. Existing cannon/environment/slot
proofs remain applicable. This does not certify the child enemy dispatcher
or its graphics/collision/movement interiors. Those labels remain open
independently, with the previously reported differences retained.

WarpZoneObject credit covers both source conditions, the bitwise player-Y
test, lock clear, eight-bit control increment and shared erase handoff.
Ten controlled original NMI routes match twenty current native runs on
1,782 persistent RAM bytes and complete output without added exclusions.
Both conditional edges, all six slots and control wrap are covered.

The only production edit in this P unifies EnemyJump and its DoSide handoff.
Both native widths pass the background matrix, star/collision regressions
and 24-route preservation checks. Strict C90 compilation of all 58 shared
sources, Windows self-tests, hidden window/message probes and platform-purity
checks pass. DOS16 compiles and links with the existing toolchain warnings;
it still lacks owner-data binding and is not claimed playable.

The owner-authorized three artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257465 | 69807ccd48e2e7df6564e82037b0863499aef40871a983711f46968f8ea71083 |
| mysmb32.exe | 319944 | edf0096ccec2d9c5a5f2268b532ea9d83ae2d6751052a94c43daca0d50503313 |
| mysmb64.exe | 327180 | f0f7064a73aca167981eed11c29067dd2be868ded69ffa542a4b156be849d22a |

The following exact labels remain unfinished in this S:

`MoveD_EnemyVertically`, `MoveFallingPlatform`, `ContVMove`, `RunEnemyObjectsCore`, `JmpEO`, `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode`, `XSpeedAdderData`, `RevivedXSpeed`, `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`, `SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`, `ChkKillGoomba`, `NKGmba`, `ExEBG`, `EnemyToBGCollisionDet`, `DoIDCheckBGColl`, `HBChk`, `CInvu`, `YesIn`, `ExEBGChk`, `SubtEnemyYPos`, `EnemyJump`, `DoSide`.

Their previously recorded source/route gaps are not waived by parent credit.
The P4 evidence stays below its ignored build root and bounded allowance;
original PC/state are never redirected to a leaf routine.

The next same-S proof step observes MoveNormalEnemy at $ca77 and its natural
RunNormalEnemies successor $c902, using existing normal fixtures 0..31.
The optional reference recorder observer captures RAM only; it never changes
the reference PC, stack, registers, RAM or ordinary frame output. A native
checker receives the observed entry state and calls the production movement
owner, then compares the established 1,782 persistent-byte contract, including
all graphics workspace and OAM. This isolates node behavior without repairing
unadmitted upstream graphics or accepting a failing whole-frame comparison.
Original whole-frame differences remain separate, unchanged evidence.

Snapshots, logs and summaries for this proof stay in ignored
build/m2-t31-s2-p5, capped at 1 MB raw data and twenty seconds per recorder
invocation, with S2 cleanup ownership. Only the existing received normal/
vertical nodes are under investigation; there is no new intake or credit.

The boundary comparison now passes all 32 existing normal-enemy scenarios
on both native widths. Each observed reference frame remains byte-identical
to its P3 original record, demonstrating that the observer does not alter
the original run. The new native checker uses the actual production movement
and gravity implementations and compares the before/after boundary; its
input retains the original graphics working bytes instead of clearing or
excluding them. All 64 comparisons pass the full persistent-RAM contract.

Four added source-RAM fixtures (normal 56..59) reach MoveNormalEnemy through
the real PowerUpObjHandler -> ShroomM caller, using ordinary/1-up mushrooms
and both horizontal directions in state $c0. Their natural successor is
$bcad, before EnemyToBGCollisionDet. They execute the previously missing
power-up equality edge at $caab. All eight native boundary comparisons pass.
The observer still never redirects PC or replaces the original caller stack.
These are movement-node proofs; the native PowerUpObjHandler's separate
legacy movement body is not certified or changed by this fixture addition.

The resulting 36 original entries and 72 native comparisons supplement the
existing source branch/table audit and exhaustive movement test for the
received normal/vertical chain. Whole-frame normal/graphics mismatches remain
recorded and are not relabeled as passes. Completion accounting and the next
combined three-artifact delivery remain pending; the current baseline is 578.

## S2/P5: normal movement and vertical proof

The completed exact labels are: `MoveD_EnemyVertically`, `MoveFallingPlatform`, `ContVMove`, `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`, `SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`, `ChkKillGoomba`, `NKGmba`, `XSpeedAdderData`, `RevivedXSpeed`.

This combined proof delivery raises progress from 578 to 594 / 1,992.
S2 now has 52 complete and sixteen incomplete received labels. No ownership
transfer or S/T closure occurs. Production game code is unchanged from P4;
the new work supplies missing original evidence for the already integrated
shared movement owner, not a replacement gameplay implementation.

[The reproducible verifier](../../../test/verify_normal_movement_snapshots.py)
checks 36 naturally reached original entry/return snapshots against both
native widths, validates both source speed tables, and checks all feasible
movement conditional outcomes. The post-BEQ BNE at $caad cannot fall through
because the same comparison left Z clear. All fourteen code labels execute;
the two adjacent table labels match the owner ROM bytes. The 32 ordinary
reference frame records remain byte-identical with the observer enabled.
The four mushroom routes cover the power-up exemption through ShroomM.
The same 1,782-byte contract includes graphics workspace and OAM: none of
the earlier graphics differences is suppressed. These proofs cover this
movement chain, not its callers, the full gravity family, graphics or the
legacy native power-up movement path. Their earlier gaps stay recorded.

The earlier 1,253,376-case movement test per width complements the original
branch evidence. All 58 shared sources rebuild under strict C90 on x86/x64;
Windows self-tests and hidden window/message probes pass. DOS16 builds and
links with the existing warnings, still without owner-data binding or a
playable-DOS claim. Platform purity passes; no platform/game source changes
are included. Three artifacts are refreshed, with unchanged DOS bytes because
this P changes validation and evidence rather than game implementation:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257465 | 69807ccd48e2e7df6564e82037b0863499aef40871a983711f46968f8ea71083 |
| mysmb32.exe | 319944 | 3a0b0ef77e134a8ca144cbdbbd92061ff6689453cc3cc6e6f8909c086f3a8d9f |
| mysmb64.exe | 327180 | 639f5a8380012bf4b06f209dd512949d440538166c5a34e1a3df265610a67a4c |

Remaining exact labels: `RunEnemyObjectsCore`, `JmpEO`, `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode`, `ExEBG`, `EnemyToBGCollisionDet`, `DoIDCheckBGColl`, `HBChk`, `CInvu`, `YesIn`, `ExEBGChk`, `SubtEnemyYPos`, `EnemyJump`, `DoSide`.

Their dispatch/caller and background-entry obligations remain open, as do
the separately owned whole-frame graphics differences. P5 raw evidence remains
under its declared ignored root and 1 MB cap; no ROM/stack/PC mutation is used.

Post-P5 same-S structure work moves the received EnemyToBGCollisionDet
entry and shared EnemyJump/DoSide body into game/enemy/background.c.
objects.c retains the existing walking, hammer, solid-tile and side-check
children as declared shared-game interfaces. No child algorithm is changed,
no wrapper-only owner is added, and both the normal and star paths use the
same moved jump body. The shared CMake list, DOS16 source list and OpenNT
compile-only list include the owner for every target.

Both native widths compile the changed owners under strict C90. The existing
background matrix (608,082 rejected entries and 24,576 jumping cases per
width) and collision regression, including stars, pass. All 24 background
records per width remain byte-identical to P3, preserving every known ROM
difference. OpenNT large-model compilation of background.c also succeeds.
This is extraction evidence, not new node credit or a full DOS link claim.
Incremental build/log/result files use ignored build/m2-t31-s2-p6 with two
reused 4,421-byte records, a 1 MB raw cap, twenty-second commands and S2
cleanup ownership. The batch remains uncommitted; P5 artifacts and the
594-node baseline remain current until combined delivery.

The [background caller test](../../../test/enemy_background_caller_smoke.c)
now verifies positive child dispatch as well as early returns: 663,552
ID/state/Y/slot combinations select walking, hammer, jump-side or return.
Another 2,359,296 direct EnemyJump combinations cover every Y/speed byte,
six slots, empty/non-solid/solid samples and successful/failed probe results.
Observed child events require bottom query, optional non-solid check,
optional landing, then side check. The landing test child changes Y and
speed so the final side call must observe its Y, while the caller must
overwrite its speed with $fd afterward. Both native widths pass strict C90.

This exposed a source-call discrepancy inside the admitted EnemyJump body:
the C code called the solid predicate even when the sampled block was zero,
whereas the original BEQ after ChkUnderEnemy skips ChkForNonSolids. The owner
now tests nonzero before that call. The previous predicate happened to return
false for zero, so state/output preservation alone had missed the incorrect
call edge. A sweep finds one shared EnemyJump body, reached by normal/star
callers; other terrain child interiors remain outside this repair. Existing
background/star regressions pass again and all 48 background width records
remain byte-identical to P3. These are caller and preservation results, not
completion credit for the remaining ten background nodes.

The same read-only snapshot observer now supports the background entry at
$dfc1 and natural successors $c8f4 (normal caller) / $bcb0 (ShroomM), using
normal fixtures 32..59. The existing native boundary checker accepts the
separate MSNB record type and calls the production background owner. All 28
reference frame outputs remain byte-identical with observation enabled.
Eleven scenarios pass both native widths; seventeen fail both, exclusively
at $eb. No byte is excluded to convert these failures to passes.

This localizes the remaining observed mismatch to DoEnemySideCheck, which
initializes $eb to two and decrements it while selecting direction probes.
The existing native child queries only the leading side and omits this RAM
counter. In the controlled routes, original $eb finishes at zero or one,
while native retains the incoming graphics value $30. This is a side-check
child discrepancy, not upstream graphics noise. The original loop and its
hammer-bump successor remain separately owned; this step does not repair
unreceived nodes or grant parent credit based on masked output.

The expanded checker still passes all 72 prior movement boundary comparisons;
one original movement observer replay also reproduces both prior frame and
snapshot byte-for-byte. Background and regression results are retained under
the existing P6 cap in background-boundary-results.json and boundary-summary.json.
The ten background nodes remain incomplete at the 594-node baseline. Next
review must distinguish the admitted entry's handoffs from the separate
DoEnemySideCheck body without treating whole-call failures as successful runs.

## S2 side-check dependency intake

The coordinator accepts the complete bounded side-check loop from T17 S6
under the continuing owner-approved M2 mandate: DoEnemySideCheck, SdeCLoop,
NextSdeC and ExESdeC (transfer-130). All four are open. Baseline 594 / 1,992,
scope/expected four, added-run ceiling 598. S2 receives 72 labels, 52 complete;
combined remaining ceiling 614. This changes the earlier scope freeze for
one explicitly identified child contract: original boundary comparisons
prove its omitted direction loop causes the observed persistent $eb failures.
It does not import the entire terrain or hammer movement subtree.

The shared enemy/side_collision.c owner will preserve the source status-bar
return, $eb=2 initialization, left/right probe order, direction equality,
empty/non-solid decisions, decrement and solid-bump handoff. The existing
bump child becomes a declared call boundary without changing its algorithm;
its Hammer Bro successor remains uncertified. Independent callback tests
must cover every direction byte and probe ordering. Existing natural NMI
background snapshots must retain their full comparison, including $eb.
The same bounded P6 root, 1 MB raw cap, twenty-second recorder limit and
combined three-target P delivery apply. No completion credit is granted at
intake and no new S/T is allocated.

The intake gate passes with four unique open scope labels, four expected
matches and ceiling 598 from baseline 594. The original loop now lives in
enemy/side_collision.c: it retains $eb initialization/decrement, skips probes
when neither direction matches, avoids the non-solid predicate for empty
tiles, and preserves the current counter when tail-calling the declared
bump child. The prior leading-side approximation is removed from objects.c;
the bump child's algorithm is unchanged. All shared/DOS build lists include
the new owner. The full source shape is restored rather than merely writing
an expected final $eb value.

All 28 original background entry/return snapshots now match both native
widths, eliminating the seventeen $eb-only failures while keeping every
persistent byte in the comparison. Existing background and star/collision
tests pass. The [side caller test](../../../test/enemy_side_caller_smoke.c)
passes 2,359,296 combinations per width, covering all Y/direction bytes,
six slots, query success/failure, and empty/non-solid/solid tiles. It observes
the probe index, source counter during the probe, predicate call ordering,
and tail handoff; a mutating bump child verifies that the caller does not
decrement $eb after the handoff. Original left-side hit and noncanonical
direction route coverage still need review before completion credit.
This remains one uncommitted P6 batch at 594; published artifacts remain P5.

## S2/P6: background and side chain proof

Completed labels: `ExEBG`, `EnemyToBGCollisionDet`, `DoIDCheckBGColl`, `HBChk`, `CInvu`, `YesIn`, `ExEBGChk`, `SubtEnemyYPos`, `EnemyJump`, `DoSide`, `DoEnemySideCheck`, `SdeCLoop`, `NextSdeC`, `ExESdeC`.

The ten received background labels and four side-loop labels now have both
verification tracks. Global progress rises from 594 to 608 / 1,992; S2 has
66 complete of 72 received labels. S2 and T31 remain open. The earlier
seventeen failing background cases remain recorded as pre-repair evidence.

Source audit maps $dfc1-$dff2 to state/Y rejection, Spiny height, jumping,
hammer and walking dispatch; $dfb8/$e066 are their returns. $e15b preserves
the wrapped Y predicate. $e163-$e182 preserves bottom-query, nonzero gate,
solid predicate, landing, $fd speed write and final side handoff. $e0fe-$e123
preserves the status-bar return, $eb direction counter, probe indices,
empty/non-solid branches, loop and bump handoff. Walking, hammer and bump
child interiors are not newly certified by those handoffs.

[The reproducible verifier](../../../test/verify_enemy_background_snapshots.py)
checks 33 original NMI-reached boundaries and 66 native comparisons over
1,782 persistent bytes, including OAM and graphics workspace. All fourteen
labels execute. Every feasible conditional outcome in the admitted entry,
jump and side bodies is observed; EnemyJump's repeated Y rejection cannot
be taken through an entry that just accepted the unchanged Y predicate.
Direct caller tests additionally cover that rejection. Observer-enabled
frame records equal the corresponding unobserved records in all 33 cases.
Cases 60..64 add left solid/non-solid, invalid direction zero/three, and
status-bar return; the latter preserves the incoming $eb value.

The source-call tests pass both widths: 663,552 background dispatch cases,
2,359,296 direct jump cases and 2,359,296 side-loop cases per width. The
production background matrix and star/collision regression also pass.
These establish admitted node semantics, not whole-frame/game equivalence.
The similar-issue sweep finds one shared jump body used by normal/star
callers and one side-loop owner; objects.c retains unchanged declared child
algorithms. No platform file or gameplay fork is introduced.

All 60 shared sources compile under strict C90 for x86/x64. Both Windows
self-tests and hidden window/message probes pass; platform purity passes.
OpenNT DOS16 links with existing warnings. DOS has no owner-data binding,
so this remains link evidence, not a playable-DOS or physical-486 claim.
Three artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257529 | 4d50836662dbdb8ce2c364f9d1aa53d7bf2b45f4dbeaf38a6ed288d4b9659ae3 |
| mysmb32.exe | 320888 | 47af6bf70001d81bc24532467f3801da4ce00b742803d516d74b8e31f987505e |
| mysmb64.exe | 328196 | b7557509acc86fb77bda1f7fb0b949e99ce9945c2f2ca06f3977a877f43c8a7a |

Remaining exact labels: `RunEnemyObjectsCore`, `JmpEO`, `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode`.

These retain their original caller/vector obligations, including distinct
platform/enemy target bindings and unresolved normal graphics/collision child
contracts. No new dependency or S/T is admitted. Raw records remain under
the existing P6 ignored root, 1 MB budget and S2 cleanup ownership.

## S2 closure and exact enemy-caller return

Coordinator closes S2 after P6 with 66 proven of 72 received labels and six
explicitly accepted unfinished transfers. All original nine GameEngine
labels are complete. The union of historical run actualMatches contains
exactly those 66 proven labels; transfer-131 sends only the following six
to the existing M2 T19 S5 enemy closure receiver. Global conformance stays
608 / 1,992. This is responsibility transfer, not conformance credit.

| Transferred labels | Concrete outstanding source contract | Follow-up source chain |
| --- | --- | --- |
| RunEnemyObjectsCore, JmpEO | Restore distinct RunLargePlatform/RunSmallPlatform and RunBowser entry contracts; current combined platform and two-part Bowser adapters are not original targets | Original lines 9030-9091, then platform/Bowser dependencies |
| RunNormalEnemies, SkipMove | Complete the EnemyGfxHandler and PlayerEnemyCollision call contracts; retain recorded persistent graphics/OAM differences and the timer-controlled movement/offscreen order | Original lines 9092-9105 with collision/OAM owners |
| EnemyMovementSubs, NoMoveCode | Prove all 21 original vector bindings at their real child boundaries; legacy specialized movement children remain uncertified, although both no-movement IDs and caller order pass focused tests | Original lines 9107-9136 with the later enemy movement chain |

The receiver accepts these exact obligations under the continuing owner
mandate. Their original source-order home is the planned enemy groups and
dispatch slice (lines 8501-9300); it is not admitted early. The receiver must
revisit source logic and native runtime proof separately and cannot infer
completion from the 66 dispatcher/dependency matches. Existing collision,
graphics, platform and Bowser children keep their registered owners.

S2 closure uses P6's reviewed source, 33 original boundaries, focused tests,
three builds/artifacts, platform purity, progress and documentation gates.
No production file changed after P6 and no duplicate build is needed for
this responsibility transition. No remaining S2 node is ownerless.

## S3 admission: scroll and screen-edge chain

Transfer-132 receives the ten planned labels from T24 S2, all open:
ScrollHandler, ChkNearMid, ScrollScreen, InitScrlAmt, ChkPOffscr, KeepOnscr,
InitPlatScrl, X_SubtracterData, OffscrJoypadBitsData, GetScreenPosition.
Baseline 608 / 1,992; unique scope ten; expected ten; maximum 618.

Entry is ScrollHandler from PlayerCtrlRoutine (plus the declared direct
ScrollScreen caller); exit is InitPlatScrl's return. GetScreenPosition has
its own callers and must preserve their contract. Shared owner starts in
game/player.c; move the bounded chain to a focused shared owner if needed,
with one implementation for all targets. GetXOffscreenBits is an existing
child seam, not permission to repair all offscreen or player physics code.
GameRoutines/PlayerEntrance remain planned S4.

ROM-logic verification checks the wrapped platform-force addition, DEY/BMI
gate, both scroll thresholds, carry/page arithmetic, mirror bit preservation,
GetScreenPosition, left/right clamp borrowing, exact controller comparison,
and final platform-force clear against the original listing and ROM bytes.
Use a source-RAM-controlled ordinary NMI route and natural entry/return
observations; no PC, stack or ROM patching. Every new mismatch is attributed
to the responsible node before implementation is expanded.

Operational verification adds one scroll-chain test, reuses player-route and
horizontal-carry regressions, builds the three targets and checks platform
purity. Every implementation P refreshes three artifacts. DOS remains
link-only until its separate owner-data/runtime obligations are fulfilled.
Owner ROM and its listing remain local, non-redistributable research inputs;
no new third-party source is imported. All raw evidence lives under ignored
build/m2-t31-s3, capped at 2 MB, twenty seconds per recorder invocation, with
S3 cleanup ownership through T review.

Initial source audit finds concrete discrepancies to resolve: DEY/BMI accepts
force $80 but current C rejects it; the no-scroll branch currently rewrites
screen edges/mirror; the mirror mask clears bit 1 although ROM changes only
bit 0. These are audit findings, not yet implementation or completion claims.

The transition gate verifies every S2 run's recorded actual set, the exact
66-label union, and absence of unfinished S2 custody after transfer-131.
S3 admission passes with ten unique open scope/expected labels at 608 and
ceiling 618. The ledger and documentation gates pass. Existing player-route
and horizontal-carry tests pass against the unchanged P6 game objects on
both x86 and x64; these baseline tests do not cover the three source findings.
No gameplay or executable content changes in this admission transition.

## S3 implementation checkpoint: shared scroll owner

The admitted chain now lives in game/scroll.c. player.c's duplicate scroll
bodies and world-coordinate clamp are removed. InitializeArea and the scroll
path call one GetScreenPosition owner. The existing raw GetXOffscreenBits
function is exposed without changing its algorithm; this child keeps its
separate proof status. All shared and OpenNT build lists include scroll.c.

The translated gate tests the wrapped DEY sign, including accepted $80;
InitScrlAmt changes only ScrollAmount before the clamp tail. ScrollScreen
uses the RAM mirror as authority and changes only bit 0. The clamp consumes
raw offscreen bits $80/$20 with left priority, performs the original borrow,
compares the full controller byte, and clears Platform_X_Scroll last. Visible
PPU state is not changed by this gameplay routine. Existing game mirror
caches are synchronized only after the source ScrollScreen write path.

[The scroll-chain caller test](../../../test/player_scroll_chain_smoke.c)
passes strict C90 x86/x64 builds: source boundary cases, all 65,536 low-X/
scroll-amount pairs, and 131,072 offscreen/controller/borrow combinations.
The unscrolled path compares all RAM bytes so accidental edge/mirror writes
cannot hide. OpenNT large-model compilation of the new owner and platform
purity pass. Area initialization and horizontal-carry regressions pass on
both Windows widths.

The original player-route fixture failed after the change because it set
left edge $0100 but left the right edge $0000. The old no-scroll rewrite
silently repaired that inconsistent setup. Its fixture now supplies $01ff,
as InitializeArea/GetScreenPosition would; both widths pass with unchanged
gameplay assertions. Pre-correction failures remain in the local evidence.

Similar-issue sweep found the two ScrollScreen implementations and the
InitializeArea copy of GetScreenPosition; they now share the bounded owner.
No enemy, physics or platform implementation was changed. Original natural
entry/return comparisons, full three-artifact delivery and P1 commit are
still pending. All ten labels remain open at 608; artifacts still identify
S2/P6. This checkpoint grants no ROM-match credit from native tests alone.

## S3/P1: scroll chain proof

Completed exact labels: `ScrollHandler`, `ChkNearMid`, `ScrollScreen`, `InitScrlAmt`, `ChkPOffscr`, `KeepOnscr`, `InitPlatScrl`, `X_SubtracterData`, `OffscrJoypadBitsData`, `GetScreenPosition`.

Expected ten, actual ten: progress rises from 608 to 618 / 1,992. The
shared game/scroll.c owner replaces the legacy player.c copies and both
GetScreenPosition call sites now use it. The original offscreen child is
exposed without alteration. No host code or platform-specific game branch
is added. The earlier source audit, caller tests and fixture correction form
the implementation review; this section supplies the original-ROM proof.

[The reproducible verifier](../../../test/verify_scroll_snapshots.py) checks
the four bytes at $b034-$b037 and all nine conditional branches in $af93-$b049.
Both outcomes of every branch execute across 24 ordinary NMI routes through
GameRoutines -> VerticalPipeEntry -> ScrollHandler. This source caller keeps
the saved horizontal force, allowing $80 and carry/wrap states without
patching a leaf PC, stack, registers or ROM. Samples are read-only at $af93
and the real JSR successor $b1ed. Each observed frame equals the corresponding
unobserved frame. The native boundary checker compares all 1,784 persistent
RAM bytes, including both PPU mirrors; only CPU scratch and the hardware
call-stack page are outside its native ABI contract. All 48 width comparisons
pass. Both speed-preserving controller equalities and right-edge borrow are
exercised. The earlier right-side fixture used a position already beyond the
right edge, producing $ff bits and taking the left-priority branch; its raw
records are retained. The corrected fixture reaches $7f and the missing right
branch. No comparison byte or failed source branch was excluded.

This establishes the ten nodes' source control/data/caller contracts. It
does not certify all player physics, every GetXOffscreenBits caller, or full
game output. Direct ScrollScreen amount-zero behavior and the initialization
GetScreenPosition caller also have independent native regression coverage.

All 61 shared sources compile under strict C90 on x86/x64; both Windows
self-tests and hidden-window message probes pass. The final linked sources
pass player-route, horizontal-carry and area-initialization regressions in
both widths. The recorder compiles in both widths. Platform purity passes.
The new owner compiles under OpenNT and the full DOS16 executable links with
the existing warnings. DOS still lacks owner-data binding and playable/486
runtime evidence; no such claim is made. Three artifacts are refreshed:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257149 | 45849f33bb558a9d0cead8657c3d5211cd57fdbc580f9d4a41ca414953945fe9 |
| mysmb32.exe | 320744 | f6c40bad8e3abaa54f3c22ba902d5754d1e0b78bf6cf5079e5f0aa90a8e89db5 |
| mysmb64.exe | 328085 | 83dab2321b0965bd596f6844ae13956dac6ef5f3d7871573cce9b4f66eee7797 |

All ten S3 labels are complete without additional transfers. S4 remains
unadmitted. S3 raw evidence stays within its 2 MB ignored-root budget and
S3 cleanup responsibility; no original bytes or traces enter the commit.

Closure review passes: the exact ten expected/actual labels agree across
inventory, census, progress and ledger; no unfinished node remains in S3
custody. The closure, progress and documentation gates pass. Actual raw
evidence is 620,968 bytes within the 2 MB cap. S3 closes with P1; T31 remains
open for its planned S4 chain and final cross-chain review.

## S4 admission: game routine vector and player entrance

Transfer-133 receives GameRoutines, PlayerEntrance, ChkBehPipe, IntroEntr,
EntrMode2, VineEntr, OffVine, PlayerRdy, ExitEntr and AutoControlPlayer from
T24 S2. All ten are open. Baseline 618 / 1,992; expected ten; maximum 628.
This is the next planned S after the verified S3 closure, not a new task.

The chain begins at GameRoutines ($b04a), selects its original thirteen
targets, and implements PlayerEntrance through AutoControlPlayer
($b069-$b0e8). Successors are PlayerCtrlRoutine, EnterSidePipe, MovePlayerYAxis
and NextArea. A focused shared entry-mode owner will replace the simplified
player.c entrance body and the engine.c selector. Existing child algorithms
retain their status; extraction into named caller seams is allowed but does
not admit broad player physics, terminal, vine-object or other task repair.

Source audit already finds missing low-Y auto-control, wrongly deferred
alternate entrance three, missing vine height/state/block/collision branches,
and IntroEntr incorrectly using the full SideExitPipeEntry transition. Restore
the exact timer decrement/wrap and DisableIntermediate/NextArea handoff.
AutoControlPlayer must write SavedJoypadBits before entering player control.
The vector must have thirteen distinct source targets; inline legacy child
bodies may move to named game-owned boundaries without completion credit.

ROM-logic verification covers vector bytes, all entrance predicates and RAM
writes, child order and return-dependent X decisions. Use ordinary NMI entry
with controlled source RAM and read-only natural call boundaries. Independent
callback tests verify handoffs and post-child reads; native route regressions,
strict C90 x86/x64, OpenNT DOS link and platform purity form the operational
track. Each implementation P refreshes the three existing EXEs. DOS remains
link-only until its separate owner-data/runtime obligations are satisfied.

Owner ROM/listing remain non-redistributable local research inputs, unchanged
from S3. No third-party implementation is imported. Temporary products and
raw traces remain under ignored build/m2-t31-s4, 2 MB raw budget, twenty-second
recorder limit, S4 cleanup responsibility through T review. No PC/stack/ROM
patching or masked comparison is allowed. Any unrelated child discrepancy
is recorded with its owner before scope changes are considered.

S4 admission passes with ten unique open scope/expected labels and ceiling
628 from 618. The implementation now has one game/entry.c owner for the
thirteen-way GameRoutines selector and PlayerEntrance/AutoControlPlayer.
The simplified entrance body is removed from player.c. Existing flagpole,
end-level and death child bodies move out of the selector into named player
seams without algorithm changes. Both pipe callers share EnterSidePipe;
PlayerEntrance no longer runs the unrelated SideExitPipeEntry transition.
MovePlayerYAxis is shared by the upward entrance and downward pipe caller.

The [entry caller test](../../../test/player_entry_chain_smoke.c) passes on
x86/x64 under strict C90. It covers all thirteen vector selections, all
controller bytes, all ordinary alternate-entry/Y bytes, both pipe header
values with every timer byte, upward Y wrap, and all nonzero vine override
bytes around height/Y/X gates. Mutating child callbacks verify the caller
reads X and the area timer after the child returns. No child can satisfy
AutoControlPlayer without observing the prior SavedJoypadBits write.

Production-linked player-route and area-initialization regressions pass on
both widths; the parent game-entry dispatcher regression passes as well.
OpenNT large-model compilation of entry.c and platform purity pass. The
similar-issue sweep identifies the former engine selector, simplified
entrance, two pipe callers and axis movement sites; these now use the
declared shared boundaries. Other player/terminal/vine-object child interiors
remain outside the proof and unchanged except for the owned AutoControlPlayer
handoff. Natural original-ROM evidence, the full three-target delivery and
P1 commit remain pending. All ten labels stay open at 618 / 1,992; the
published artifacts remain S3/P1.

## S4 original-boundary checkpoint

The original GameRoutines table has thirteen verified target addresses;
thirteen controlled NMI routes reach those actual entries. Twenty-two
entrance routes cover all nine entrance labels and both outcomes of all
eleven conditional branches. Read-only entry/return and child observers
produce identical frame records to unobserved execution; they do not alter
ROM, PC, registers, stack or RAM.

[The reproducible verifier](../../../test/verify_entrance_snapshots.py)
consumes the ignored S4 evidence directory and owner ROM. It verifies 44
x86/x64 caller comparisons over 1,784 persistent bytes, including mirrors.
Caller comparisons check child identity, order, argument and entry RAM, then
use the original executed child return. This proves only caller semantics.
The separate [production checker](../../../test/entrance_snapshot_check.c),
now available as a local-ROM CMake target, executes actual shared C children.
Relinked against the final 62 shared objects on both widths, it retains
18 matching and 26 failing comparisons. No failed comparison is suppressed
and no whole-call equivalence is claimed.

Existing responsibility receipts record player-control/NextArea findings in
[T23 S5](player-route.md#t31-s4-evidence-receipt-for-existing-t23-s5-custody)
and relative-position findings in
[T16 S4](oam-graphics.md#t31-s4-evidence-receipt-for-existing-t16-s4-custody).
These children retain their unfinished status; S4 does not absorb repairs.

Both newly built Windows executables pass their self-tests and a bounded
two-second hidden-window startup/message-response probe without input
injection. This is startup evidence, not a gameplay or performance claim.
S4 remains active at 618 / 1,992 pending final review, accounting and P1
delivery; this checkpoint awards no node credit.

## S4/P1: entry chain proof

Expected ten, actual ten: 618 -> 628 / 1,992. Each row below certifies the
node's own control/read/write/call contract, not its children's algorithms.
The original-boundary checkpoint above records the 26 retained whole-call
failures and their existing owners. No child receives new completion credit.

| Exact node | Original source lines | Shared entry.c semantics and evidence |
| --- | --- | --- |
| GameRoutines | 5499-5515 | Thirteen original vector words and thirteen natural target hits; native callbacks verify the same target binding and controller argument. |
| PlayerEntrance | 5519-5531 | Alternate selector equality, low-Y null controller and header 6/7 gates; original branch outcomes and child-entry RAM agree. |
| ChkBehPipe | 5532-5535 | Attribute gate and forced right input; saved input observed before the real child boundary. |
| IntroEntr | 5536-5540 | EnterSidePipe first, unconditional timer decrement including zero wrap, disable-intermediate increment and NextArea handoff. Child-return replay verifies post-child timer use. |
| EntrMode2 | 5541-5548 | Override gate, upward amount ff and post-child Y threshold 91, including wrap. |
| VineEntr | 5549-5561 | Height 60 gate, Y threshold 99, climbing state and block byte 08 in original order. |
| OffVine | 5562-5566 | Collision flag before auto-control, X threshold 48 evaluated after child return. |
| PlayerRdy | 5567-5574 | Task 08, facing 01, alternate/collision/override reset in original order. |
| ExitEntr | 5575 | Return without extra writes on height/timer/X paths; outer return RAM checked. |
| AutoControlPlayer | 5580-5581 | SavedJoypadBits written before PlayerCtrlRoutine; all 256 input bytes and original child-entry snapshots checked. |

The final 62 shared sources compile as strict C90 on both Windows widths.
Production-linked player-route and area-initialization regressions, entry
callback tests and parent dispatcher tests pass on both widths. The final
native recorders compile on both widths. The production snapshot checker
is linked to those same final shared objects, with 18 matches and 26
failures retained. Both Windows self-tests and bounded hidden startup/message
probes pass. Full OpenNT DOS16 linking succeeds with the existing library
warnings; DOS has no owner-data binding or gameplay/486 qualification claim.
No platform source changes or game-state branches are introduced.

Three refreshed local artifacts (owner-authorized inclusion; not a public release):

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257437 | 0d975b043faa521f201acac16ee18ed01ef52cd600ec8554f2efeeb55c76b150 |
| mysmb32.exe | 322371 | 34be0fb0f878cb074216526644f4a28043c7176dda91147dc419f5666ce2ea2e |
| mysmb64.exe | 329742 | 49a78adaeb2a42d80899003bc62550f8a16c6aeba2d8bda3a54c746cc7731370 |

S4 has all ten expected nodes proven and no unfinished S4 node custody.
The coordinator reviewed source semantics, caller-only proof limits, explicit
child failures, all final tests and three artifact hashes. Node closure,
progress and documentation gates pass at 628 / 1,992. Platform purity passes.
Raw evidence is 991,727 bytes within the 2 MB cap, retained under the ignored
S4 directory through T review. S4's packet remains active until T31's final
cross-chain review is complete; no successor task is admitted.

## T31 cross-chain review scope

The final review reuses S4's unchanged 62-source build and three packaged
artifacts. Under the active S4 packet, run four-frame ordinary-NMI routes:
game-entry cases 0/1/2/3, engine-tail cases 0/2/3, scroll cases 0/5/19,
and entrance cases 0/7/18. Each route runs the original ROM and both native
widths, with a twenty-second limit per recorder. Retain all persistent-RAM
and output differences as diagnostics, with no full-game match claim.
This matrix adds no node credit and does not reopen unrelated child repairs.
Outputs remain in the ignored S4 directory under its existing 2 MB raw cap
and cleanup owner; recheck total size after recording. Original coverage
must demonstrate the dispatcher/engine and selected scroll/entrance joins.

## T31 cross-chain results

The [matrix runner](../../../test/verify_dispatch_chain_regression.py) accepts
the ignored evidence directory and owner ROM as its two arguments. It reuses
the final native recorders and original reference recorder. Thirteen routes
run four complete frames each; x86 and x64 files are identical on all routes.
Every persistent RAM byte (including both PPU mirrors) and every recorded
output byte is compared. CPU scratch and hardware call-stack storage remain
outside the native ABI comparison. No discrepancies are masked.

| Joined route | Original/native result across four frames |
| --- | --- |
| GameMode -> GameCoreRoutine -> GameRoutines -> GameEngine, controller cases 2/3 | All persistent RAM and recorded output match on both widths. |
| Engine-tail cases 0/2/3 | All four frames match on both widths. |
| VerticalPipeEntry -> ScrollHandler -> GameEngine, scroll cases 0/5/19 | All four frames match on both widths, including mirror and PPU output. |
| PlayerEntrance -> PlayerRdy -> GameEngine, entrance case 0 | All four frames match on both widths. |
| Life-loss exits, game-entry cases 0/1 | First frames match. Sample 2 retains the known visible PPU control-bit difference; case 1 also differs in music cursor $f7 at sample 1. |
| Pipe NextArea and vine-to-control, entrance cases 7/18 | Actual native child discrepancies remain and propagate across frames; not certified as full routes. |

Nine routes fully match; four remain diagnostic failures. Original PC
coverage confirms GameMode/GameCoreRoutine/GameRoutines joins, the engine
early return after life loss/NextArea, repeated engine entry for continuing
play, the pipe scroll call and entrance-to-player-control transition.
These results support the scoped caller proofs, not full-game equivalence.

The first matrix run exposed a fixture representation mismatch: source-RAM
scroll/entrance fixtures replace $0778, but the C recorder left its native
cached PPU-control input at the bootstrap value. Only those fixture adapters
now initialize both representations before NMI. No game or platform code
changed and no output is rewritten. The before-fix neutral summary remains
local; the corrected run removes those input-only mirror discrepancies.

The [existing-debt receipt](../../states/TODO.md#translation-debt) retains
PPU/music residuals with their current source owners; prior S4 receipts retain
the pipe/vine child gaps. T31 received 94 distinct labels across all S runs:
88 proven, six previously accepted unfinished enemy-caller transfers to
T19 S5. Its original 31 planned nodes are all proven within their own
contracts. No additional node credit is awarded by this review (628 / 1,992).

Raw evidence totals 1,838,717 bytes, below the admitted 2 MB cap. Current
shared binaries and their three hashes are unchanged from S4/P1 because the
only C change is in the recorder fixture adapter. The same three packaged
EXEs remain the review results; DOS remains link-only. Final task disposition
and successor admission must preserve all these limits and failure receipts.
