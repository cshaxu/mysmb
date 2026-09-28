# M2 candidate: Game frame dispatcher

## Status

**M2 T31 open; S2 active at 576 / 1,992.** Closed T30 precedes this task in the
source-order recovery plan. S1 is closed; S2 is the only active chain.

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
