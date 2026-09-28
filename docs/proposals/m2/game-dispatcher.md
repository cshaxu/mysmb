# M2 candidate: Game frame dispatcher

## Status

**M2 T31 open; S2 active at 549 / 1,992.** Closed T30 precedes this task in the
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
