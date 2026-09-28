# M2 T35: Bubbles, timer and adjacent actor chains

## Source-order plan

The source slice is lines 6409-6729, 38 exact labels. Sixteen already-proven
labels retain their maintenance receiver and accepted evidence; the 22
incomplete labels below are expected new matches, maximum 772 from 750.
All four S chains and T35 are closed at 772 / 1,992. Later S numbers remain within this T proposal until
individual admission and receipt, not concurrent execution.

| S | Exact nodes | Current receiver / shared owner |
| --- | --- | --- |
| S1 | `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`, `Y_Bubl`, `ExitBubl`, `Bubble_MForceData`, `BubbleTimerData` | M2 Td S5 -> S1 / game/fireball/bubble.c |
| S2 | `RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer` | M2 Td S5 / game timer owner |
| S3 | `Jumpspring_Y_PosData`, `JumpspringHandler`, `DownJSpr`, `PosJSpr`, `BounceJS`, `DrawJSpr`, `ExJSpring` | M2 T24 S2 / shared jumpspring owner |
| S4 | `Setup_Vine`, `NextVO`, `VineHeightData` | M2 T24 S2 / shared vine initialization/data owner |

Previously complete, no new credit: `WarpZoneObject`, `ProcessWhirlpools`, `WhLoop`, `NextWh`, `ExitWh`, `WhirlpoolActivate`, `LeftWh`, `SetPWh`, `WhPull`, `FlagpoleScoreMods`, `FlagpoleScoreDigits`, `FlagpoleRoutine`, `SkipScore`, `GiveFPScr`, `FPGfx`, `ExitFlagP`.

Warp and whirlpool nodes retain T31 S2 proof; flagpole nodes retain T22 S5
proof. T closure reuses those accepted contracts and integrates the changed
chains. S2 must preserve timer gates and digit/injury child order. S3 owns
the complete jumpspring state/graphics-caller chain. S4 owns Setup_Vine and
NextVO with the adjacent VineHeightData binding; its later movement consumer
remains a dependency of the next source slice, with no consumer credit.

## S1 admission: bubble creation and movement

Eight exact labels from BubbleCheck through BubbleTimerData are open.
Transfer-144 receives all eight from M2 Td S5. Scope/expected eight, baseline
750, maximum 758. Entry $B6F9 BubbleCheck or $B70B SetupBubble falls through
MoveBubl to $B74A ExitBubl; the two adjacent tables end at $B74E.

The shared owner is game/fireball/bubble.c. Proven ProcAirBubbles dispatch
and Entrance_GameTimerSetup are the callers. Relative/offscreen/OAM leaves
remain outside this chain and retain their existing receivers. Audit random
scratch storage, inactive/timer gates, facing carry, world-coordinate carry,
Y wrap, both data bindings, setup-to-movement fallthrough, subtraction borrow
and the status-bar threshold. Similar-issue sweep includes every SetupBubble
caller, duplicate bubble movement body and bubble timer/coordinate writer.

ROM proof records real BubbleCheck and SetupBubble entry/return RAM reached
through ordinary NMI; compare actual native functions, including shared $07
input/output where it crosses these entries. Cover both branch outcomes and
table selections, all three slots, page/Y wrapping, idle and expiry. No CPU,
stack, reference ROM or output patching is allowed. Operational proof is a
focused bubble chain test, existing bubble/fireball/player regression,
strict C90 x86/x64 builds, DOS16 link, platform purity and three artifacts.

Existing owner-local SMB1 ROM and reviewed listing are research/build inputs
only; no third-party implementation import. All raw evidence and temporary
files stay in ignored build/m2-t35-s1, with a twenty-second run budget and
four-MB retained batch budget; S1 owns cleanup through T review. Local three
EXE delivery follows the owner's standing exception. DOS remains link-only.
Closure requires eight exact dispositions, separate original-logic and
operational evidence, tracker/ledger updates and three artifact identities.

## S1 original bubble proof

The eight-node $B6F9-$B74E chain is implemented in game/fireball/bubble.c.
Admission passed with eight open nodes, eight expected, baseline 750 and
maximum 758. Two missing source behaviors are restored: BubbleCheck always
stores the random bit in $07, and SetupBubble falls through MoveBubl on every
entry, including when the initial Y happens to equal the offscreen F8 marker.
There is one movement body used by direct setup and ordinary checking;
offscreen, relative-position and graphics children remain unchanged.

| Node | Address | Proven original contract |
| --- | --- | --- |
| BubbleCheck | $B6F9 | Random-bit write, active versus inactive Y, creation timer gate |
| SetupBubble | $B70B | Facing-bit carry, X/page carry, Y+8/high-Y, timer-table read, immediate movement |
| PosBubl | $B714 | Facing adder retains LSR carry, so right adds nine and left adds zero |
| MoveBubl | $B732 | Dummy-force subtraction and borrow propagate into wrapped Y |
| Y_Bubl | $B748 | Store resulting Y or F8 when the post-subtraction byte is below 20 |
| ExitBubl | $B74A | Return after idle or movement with original persistent state |
| Bubble_MForceData | $B74B | Both force bytes and random-bit selection |
| BubbleTimerData | $B74D | Both timer bytes and random-bit selection |

Thirty controlled source-RAM scenarios run through ordinary NMI/GameEngine.
Twenty-four observe BubbleCheck and six observe SetupBubble at its actual
caller's fallthrough; all three slots and both random selections are covered.
The recorder reads the original stack return address/depth and captures entry
and return RAM without modifying CPU, stack, ROM or outputs. The native test
executes the actual shared function, with no substituted child returns. It
compares 1,785 persistent bytes, including the explicit $07 random input/output;
only scratch 0-6 and the hardware stack are excluded. All sixty x86/x64
comparisons match. Four branch sites have both outcomes; the executable labels
are hit and all four table bytes match the ROM. Observed, coverage-enabled
and unobserved frame outputs are identical. Raw evidence is 997,728 bytes.

Reproduce cases 0-29 of bubble_core_fixture.h with --fixture=t35-bubble=N,
one frame, zero buttons, warmup one and --bubble-snapshot. Repeat with
--pc-coverage and without observation. Compile bubble_core_snapshot_check.c
with the shared bubble source for both widths, then run
test/verify_bubble_core_snapshots.py over the contained batch and owner ROM.
No protected trace or generated program data is a tracked fixture.

The independent entry-consistency test passes 18,432 cases per width, plus
explicit wrapped-Y, borrow, timer-idle and F8-creation checks. Full strict C90
builds compile 67 shared units per Windows width; self-tests and two-second
hidden-window/message probes pass. Bubble OAM, fireball OAM and player-route
regressions pass on both widths. Platform purity passes. DOS16 compiles and
links with the existing OLDNAMES warning; it remains link-only and has no DOS
playability or physical-486 claim.

Similar-issue sweep identifies exactly the BubbleCheck setup call and the
Entrance_GameTimerSetup direct call in player.c; both consume the single
SetupBubble implementation. The former duplicate movement body is removed.
Coordinate, dummy-force, timer and random scratch writes have one shared
owner. Relative/offscreen/OAM bodies and platform source are unchanged.

Final owner-authorized local P1 artifacts:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258835 | 1e44d32605ba1dd83ab6a3867495f018d23e0dd5a8d27846ecd91403408ddd0e |
| mysmb32.exe | 326346 | 9bb69f9789ea7a7129d959eaf7aae6c9e885bf995e72bff420b81a196e7b14cb |
| mysmb64.exe | 334388 | 24d44a28dbea56e61830e93bf0a140afaf191335cf9dc8a594862630637bc700 |

Final review accepts 8/8 expected matches, exactly the table above, with no
deferred or transferred received node. Progress 750 -> 758 / 1,992. S1 closes
after node-ledger and documentation validation; T35 remains open. S2 timer
admission is next; the other sixteen previously complete source-slice nodes
retain their maintenance receivers and accepted evidence.

## S2 admission: timer gates, countdown and expiry

Transfer-145 receives exactly RunGameTimer, ResGTCtrl, TimeUpOn and ExGTimer
from M2 Td S5, all open. Scope four, expected four, baseline 758, maximum 762.
Entry $B74F through $B7A3 is one chain. Shared game/timer.c will own its
existing body and the PrintStatusBarNumbers tail currently misplaced in
GameEngine; caller adjustment restores the original boundary, not a new
parent behavior. Digit arithmetic, status output and ForceInjury keep their
existing owners and receive no new completion credit.

Audit mode/engine/Y-high/control gates, OR-of-digits zero test, exact 100
music condition, timer reload, DigitModifier+5, DigitsMath Y=23 and status
selector A4, forced-small injury then expiration-flag increment. Verify the
post-child increment, byte wrapping and immediate return paths. Similar-issue
sweep includes every run-timer definition/caller and duplicate countdown/HUD
path. No platform gameplay logic or unadmitted child repair is allowed.

Original proof uses source-RAM scenarios at ordinary NMI to observe the
timer's true entry/return and three child boundaries. Compare the original
branches, persistent RAM, digit-modifier bytes and call arguments; run actual
native children separately and retain mismatches. Do not mutate reference
CPU, stack, ROM or outputs. Operational proof includes focused timer/engine
caller tests, existing status and game regressions, strict C90 x86/x64 builds,
DOS16 link, platform purity, bounded Windows probes and three artifacts.

Existing owner-local ROM and reviewed listing are research/build inputs only;
no source import. All raw traces/logs/generated data stay in ignored
build/m2-t35-s2, twenty seconds per recorder run and four MB retained raw
batch; S2 owns cleanup through T review. Local three-EXE delivery follows the
owner's standing exception; DOS remains link-only. Closure requires four
exact dispositions, both proof tracks, ledger/progress updates and hashes.

## S2 original timer proof

Four open labels were admitted, expected four, baseline 758 and maximum 762.
The existing timer body now has one shared owner, game/timer.c. Its original
PrintStatusBarNumbers tail is inside that function, rather than conditionally
issued by GameEngine. The engine has one timer call at the original position.
Digit math, status output and injury child bodies remain unchanged; the C
return value is retained for existing direct consumers, not treated as a
6502 register contract. CMake and DOS build lists contain the same new owner.

| Node | Address | Proven contract |
| --- | --- | --- |
| RunGameTimer | $B74F | Mode, engine, Y-high and timer gates; OR-of-three-digits zero test; exact 100 music test |
| ResGTCtrl | $B786 | Reload 18, modifier FF at 0139, digit math with Y=23, then status selector A4 |
| TimeUpOn | $B79A | Clear PlayerStatus, call ForceInjury, then increment current expiration byte with wrapping |
| ExGTimer | $B7A3 | Early/expiry return without invented countdown or output calls |

Sixteen ordinary-NMI source-RAM scenarios cover both outcomes at all eight
branch sites. The observer reads the actual root/child entry and return
addresses/depths; no CPU, stack, ROM or output mutation occurs. Caller proof
compares child identity, digit/status arguments and 1,791 persistent RAM
bytes, replaying original child returns only in that isolated caller test.
Scratch 0-7 and hardware stack are excluded, but digit-modifier data 0133-0139
is explicitly included despite occupying stack-page addresses. All 32 caller
checks pass across x86/x64. Observer, coverage and unobserved outputs match.

Actual native children are also executed: thirty comparisons match; scenario
13 fails on both widths. With InjuryTimer nonzero, original ForceInjury still
kills the already-small player, while the current child incorrectly applies
the InjurePlayer entry's timer gate. The five differences are engine 000E,
player state 001D, vertical speed 009F, event music 00FC and timer control
0747. This is retained with the existing M2 T17 S6 receiver for ForceInjury
and KillPlayer and recorded in TODO; no child repair or equivalence is claimed.

Reproduce timer_fixture.h cases 0-15 at ordinary NMI, one frame, warmup one,
zero buttons, --fixture=t35-timer=N, --timer-snapshot and --control-children.
Repeat with PC coverage and without observers. Build both modes of
timer_snapshot_check.c, and run test/verify_timer_snapshots.py against the
contained batch and owner ROM. The verifier checks instruction boundaries,
all eight branch outcomes, all four label hits, observer invariance, caller
results and matching cross-width actual-child diagnostics.

Independent tests cover 1,560 gate/countdown combinations per width and
post-child expiration wrap. The engine caller test now rejects a separate
timer-HUD call from the parent; all 512 controller/return combinations pass
per width. The status arithmetic test was missing its timer declaration;
including frame_root.h fixes that strict-C90 compile error without changing
its expectations. Bubble OAM, fireball OAM, player route, status arithmetic
and mode regression pass on both widths (ten executions). Both release builds
compile all 68 shared units as strict C90 and pass self-test and bounded
hidden-window/message probes. Platform purity passes. DOS16 compiles/links
with the existing OLDNAMES warning; it remains link-only, not playable evidence.

An additional one-frame integration matrix runs the same sixteen source-RAM
fixtures through the complete native frame. Both widths agree. All sixteen
routes retain ROM output differences: every route has RAM 0778 and 690 output
byte differences; scenario 13 also has the five injury bytes above and one
additional output difference. No complete-frame match is claimed. Rebuilding
the recorder against S1's unchanged core yields byte-identical outputs for
all 32 runs, proving this boundary relocation did not introduce those frame
differences. PPU/initial-state output investigation stays with the existing
T24 S2 custody; the injury difference stays with T17 S6. This supplemental
matrix does not replace the scoped timer proof or certify child interiors.

The similar-issue sweep found one timer definition and one engine caller;
the former parent-owned HUD call is removed. Direct timer callers receive
the complete original tail. No duplicated countdown, ForceInjury body or
platform gameplay path was introduced. Final local artifacts follow the
owner's delivery exception:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258835 | e16de5f219768840b005bdd9d8c7b23abaf8aa0dd44f27f0541ec9641a7e84ee |
| mysmb32.exe | 326562 | f51ac607300e5361e16ed837b4169b366cc45c129f65b617d3956d56bcc83b0e |
| mysmb64.exe | 334640 | b19ff0050003cac7917d22a7a4c9101cdfc8dbc55d4b0f64e65db25fb094a4ab |

Retained raw evidence including integration is 882534 bytes, below four MB.
Final review accepts 4/4 expected matches, exactly the node table above;
there are no unfinished received labels or transfers. Progress 758 -> 762 /
1,992. Ledger/documentation checks gate closure. S2 closes; T35 remains open
for S3 jumpspring and S4 vine initialization/data.

## S3 admission: jumpspring state and caller chain

Transfer-146 receives seven open labels from M2 T24 S2: Jumpspring_Y_PosData,
JumpspringHandler, DownJSpr, PosJSpr, BounceJS, DrawJSpr and ExJSpring.
Scope/expected seven, baseline 762, maximum 769. The source table and chain
span $B8B6-$B91D; RunEnemyObjectsCore is the predecessor. Move the state
body from oam/normal_enemy_gfx.c to shared game/jumpspring.c, leaving the
existing graphics child in its OAM owner with a declared original boundary.
Offscreen, relative, graphics and bounds children keep their receivers and
are not certified or independently repaired here.

Audit initial offscreen call, timer/animation gates, frame-minus-one table
index, player Y wrap, fixed spring Y plus table, new-A rising edge, stored
force and final launch/reset. Restore the original relative/graphics/bounds
order before re-reading animation/timer and incrementing the animation.
Remove the actor's invented slot/flag/ID gates, leaving admission to its
original caller. Replace the inline distance erase shortcut with the shared
OffscreenBoundsCheck child. Similar-issue sweep covers all spring state,
force/timer writers and step callers, including slot five and byte wrapping.

ROM proof observes original selected-slot entry/return and four direct
children through ordinary NMI/actor dispatch, compares branches, table bytes,
call arguments and persistent RAM, and separately retains actual-child
differences. No CPU/stack/ROM/output patching. Operational proof includes
focused state/call-order mutation tests, actor dispatch and existing game
regressions, C90 x86/x64, DOS16 link, platform purity, bounded window probes
and three artifacts. Child seam extraction earns no child credit.

Owner-local ROM/listing remain research/build inputs with no third-party
implementation import. Evidence stays in ignored build/m2-t35-s3; each
recorder run has a twenty-second limit and the retained raw batch a four-MB
limit. S3 owns cleanup through T review. Local EXE delivery follows the
owner's standing exception; DOS remains link-only. Closure requires seven
exact dispositions, both proof tracks, tracker/ledger updates and hashes.

## S3 original jumpspring proof

Seven open labels were admitted at 762, expected seven, maximum 769.
The shared actor now lives in game/jumpspring.c, with one existing dispatcher
caller and an extracted OAM child. DOS and Windows compile the same actor.
The actor no longer imposes slot/flag/ID gates or substitutes a world-distance
erase. Initial offscreen information precedes state changes; relative, graphics
and bounds calls precede the final animation/timer reads.

| Node | Address | Proven original contract |
| --- | --- | --- |
| Jumpspring_Y_PosData | $B8B6 | Four bytes 08,10,08,00 and active animation-minus-one selection |
| JumpspringHandler | $B8BA | Offscreen first, master timer and animation gates |
| DownJSpr | $B8D5 | Player Y minus two with byte wrapping |
| PosJSpr | $B8D9 | Fixed spring Y plus selected table byte; frame and rising-A gates |
| BounceJS | $B8F4 | Frame-three force transfer to player speed, then animation reset |
| DrawJSpr | $B902 | Relative position, graphics, bounds; re-read animation/timer after children |
| ExJSpring | $B91D | Return with original persistent state and conditional timer reload/increment |

Thirty-two source-RAM scenarios enter through ordinary NMI/GameEngine and
RunEnemyObjectsCore. The observer reads original return addresses and stack
depths without changing CPU, stack, ROM or output. Cases include slots 0, 2
and 5, animation 0..4, timer gates, current/previous A, coordinate wrapping
and both horizontal boundaries. All nine branches have both outcomes; all
six executable labels are hit and all four data bytes match the owner ROM.
Observer, coverage-enabled and unobserved frame outputs are identical.

The isolated caller comparison replays recorded original child returns and
checks four child identities/slot arguments and 1,791 persistent RAM bytes.
Scratch 0-7 and hardware stack are excluded, except digit data 0133-0139.
All 64 x86/x64 caller comparisons match. This proves the received caller/data
nodes, not the child algorithms. Active animation indices follow the original
1..4 invariant; no invented index clamp or fallback table is introduced.

Actual native children run separately: all 64 comparisons retain differences,
identical across widths. Differences are confined in these cases to graphics
work bytes 00EC/00EF and OAM 0200-0217. Existing EnemyGfxHandler spring tile
selection, flip attributes and slot-five drawing guard remain uncorrected;
the child retains M2 T17 S6 custody and receives no completion credit. Neither
whole-actor visual equivalence nor full-frame ROM equality is claimed.

Reproduce jumpspring_core_fixture.h cases 0..31 using one frame, warmup one,
--fixture=t35-jumpspring=N, --jumpspring-snapshot and --control-children.
Serial input is 1 when (N / 5) bit zero is set, otherwise zero. Repeat with
--pc-coverage and without observation. Compile jumpspring_snapshot_check.c
with/without MYSMB_CALLER_CHECK and run verify_jumpspring_snapshots.py against
the contained batch and owner ROM. Original t30-spring fixtures are preserved.

Independent focused tests pass 480 combinations per width, all six slots,
byte wrapping and post-bounds animation/timer mutation. Enemy dispatch passes
on both widths. Ten bubble/fireball OAM, player, status and mode regression
executions pass. All 69 shared units compile in strict C90 for x86/x64; both
release self-tests and two-second hidden-window/message probes pass. Platform
purity passes. DOS16 compiles and links with the existing OLDNAMES warning;
it remains link-only, without resource binding or DOS/486 playability proof.

The similar-issue sweep found one dispatcher call, the former combined actor
body, and player-side spring initialization/collision writers. Only the actor
body moves: player initialization stays with its owner; the OAM child retains
its graphics algorithm. No platform sources change. The earlier pre-parser
screen-origin route still requires integrated revalidation after replacing
the inline erase shortcut. No unrelated node receives credit.

Final owner-authorized local artifacts:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258679 | a1516f27e4f10a0345a34b0ac74e81d83cf3dfe00e2e2b2bca9ed92c022aeec6 |
| mysmb32.exe | 327421 | 1ce4c6246e4009b17f49a49c7b711aa6cd579a4bab9e01771d28cc63b7c48ded |
| mysmb64.exe | 335021 | a9a674d1061a8f966f764434e221284b017d05448ccfd38a6b32ae831b193c11 |

Retained raw evidence: 1679794 bytes, below four MB.
Seven received labels proven, seven expected, no received-node transfer. Progress 762 -> 769 / 1,992. T35 remains open for S4 vine initialization/data.

## S4 admission: vine initialization and height data

Transfer-147 receives Setup_Vine (mapped; evidence incomplete), NextVO and
VineHeightData (open) from M2 T24 S2. Scope three, expected three, baseline
769, maximum 772. Setup_Vine $B91E -> NextVO $B93D returns at $B948;
VineHeightData occupies $B949-$B94A. Shared game/vine.c owns initialization
and the two height bytes. ChkOverR/Entrance_GameTimerSetup and vine-block
activation are predecessors; VineObjectHandler is the next source slice and
receives no algorithm changes or completion credit.

Extract the existing setup body from objects.c, exposing original enemy X
and block Y arguments rather than hardcoding enemy slot five. Existing callers
explicitly pass their original five. Preserve flag/ID writes, block-to-enemy
page/X/Y copy order, first-vine start-Y gate, indexed vine-slot registration,
byte-wrapped flag increment and final grow sound. Move the height table to
one declared shared owner and update its existing consumer without changing
the consumer's logic. Sweep every setup caller, vine flag/start-Y writer and
height-table copy; retain unrelated growth/graphics debts.

Original proof observes Setup_Vine entry/return through ordinary NMI and the
entrance caller, compares actual native RAM with no substituted child, and
checks both outcomes of the start-Y gate plus both ROM height bytes. Focused
native cases exercise original arguments, registration indices, byte wrapping
and preservation of unrelated RAM. Operational proof includes entrance/core
regression, strict C90 x86/x64 builds, DOS16 link, platform purity, bounded
Windows probes and three owner-authorized EXEs. T review reuses accepted
S1-S3 proof and runs cross-chain regression on the final shared core.

The owner-local ROM and reviewed listing remain contained research/build
inputs, with no third-party implementation import. All temporary evidence
stays in ignored build/m2-t35-s4, twenty seconds per recorder run and four MB
retained raw batch. S4 owns cleanup through review. DOS remains link-only.
Closure requires exact dispositions, separate original-logic and operational
evidence, ledger/progress updates and artifact identities; neither a build nor
a table move alone certifies a node.

## S4 original vine setup proof

Admission received Setup_Vine (mapped; evidence incomplete), NextVO and
VineHeightData (open), three expected matches from baseline 769 to maximum
772. One shared game/vine.c now owns Setup_Vine and the height data. Its
original enemy X and block Y arguments are explicit; both existing production
callers pass enemy five. The block caller preserves its selected block slot;
the entrance helper passes block zero. The consumer reads the single shared
height table. Its clamp/growth/drawing logic is unchanged and not certified.

| Node | Address | Proven original contract |
| --- | --- | --- |
| Setup_Vine | $B91E | ID and active flag; block page/X/Y copy; first-vine start-Y gate |
| NextVO | $B93D | Indexed enemy-slot registration, byte-wrapped flag increment, grow sound, return |
| VineHeightData | $B949 | Both shared bytes match ROM: 30,60; consumer retains separate proof |

Sixteen source-RAM cases enter Setup_Vine through ordinary NMI/GameEngine
and Entrance_GameTimerSetup/ChkOverR. They exercise vine registration counts
0,1,2,255, both gate outcomes, varied entrance/screen-page inputs and wrap.
The observer reads original stack return/depth and entry X/Y without changing
CPU, stack, ROM or output. The actual C leaf matches all 32 x86/x64 return
comparisons across 1,791 persistent bytes. Only scratch 0-7 and hardware
stack are excluded, with digit data 0133-0139 retained. No child substitution
is used. Both executable labels are hit; the shared native table output is
checked against the two owner-ROM bytes. Observer, coverage and unobserved
frame output agree. The source-reachable route passes X=5/Y=0; independent
native argument tests cover all six enemy slots and both block slots.

Reproduce vine_setup_fixture.h cases 0..15 with one frame, warmup one, zero
buttons, --fixture=t35-vine-setup=N and --vine-setup-snapshot. Repeat with
PC coverage and without observation. Build vine_setup_snapshot_check.c with
game/vine.c for both widths, then run verify_vine_setup_snapshots.py against
the contained batch and owner ROM. No ROM-derived fixture is tracked.

Focused tests pass 12,288 combinations per width, checking the complete
2,048-byte RAM write footprint, all registration-byte values and wrapping.
The existing core smoke still fails at its entrance-loop assertion on line
136, before its vine checks. Rebuilding the prior S3 test/header against its
original objects fails at the same first assertion on both widths; the debt
was already recorded under T31 S4. It is not hidden, fixed or counted as a
passing test. Bubble/fireball OAM, player route, status arithmetic, mode and
vine OAM regressions pass on both widths (twelve executions).

Both final Windows builds compile all 70 shared units in strict C90 and
pass self-test and two-second hidden-window/message probes. Platform purity
passes. DOS16 compiles and links with the existing OLDNAMES warning; DOS
remains link-only without resource binding or a playability/486 claim.

The similar-issue sweep finds one setup definition and the two production
callers above, plus the direct core smoke call. All use the explicit original
arguments; no compatibility wrapper or duplicate setup remains. One height
table serves the existing consumer. The entrance helper's block-coordinate
preparation stays with its original caller owner; no platform source changes.

## T35 cross-chain review and closure

The final linked core consumes all four S snapshot sets without recapturing
accepted ROM evidence. Across x86/x64 there are 188 actual-node comparisons:
60/60 bubble matches, 30/32 timer matches, 0/64 jumpspring matches with the
same known graphics-child differences, and 32/32 vine setup matches. All
122 matches and 66 failures agree exactly with the accepted per-S evidence.
The timer/jumpspring isolated caller proofs remain 32/32 and 64/64; child
failures are not suppressed or credited. The sixteen already-proven warp,
whirlpool and flagpole labels retain their accepted original contracts and
maintenance custody, without new completion credit.

Sixteen full-frame entrance/vine scenarios run with the final core on both
Windows widths. All 32 outputs are byte-identical to S3 and match across
widths. Every route still differs from ROM at RAM 0778 and 690 output bytes;
this is an explicit integration limit, not a full-game equivalence claim.
The integration summary records those differences. Its cold PPU/output differences
remain with the existing T24 S2 receiver; the prior timer injury and spring
graphics debts retain their original receivers. T35 adds no unexplained
regression in this bounded matrix.

T35 closes its 38-label source slice: sixteen retained matches plus 22 new
matches across S1=8, S2=4, S3=7 and S4=3. All three S4 labels are complete
within their initialization/data contracts, with no received-node transfer.
Global progress is 750 -> 772 for T35, 769 -> 772 for S4. The next source
slice begins with VineObjectHandler; that consumer remains incomplete and
must be admitted before repair. M2 remains incomplete.

Final owner-authorized local P1 artifacts:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258695 | 265d694b961d3d2334a1007af941d6a67df134ef0440acfb9c705ae670e22cde |
| mysmb32.exe | 328190 | fed49d5eb4fd1158abb7db7b55dac512423988987882a384c9fae1a4098fea59 |
| mysmb64.exe | 335437 | 9fb0fb10594b74babba4279ef012ee01f8da90a3a7dbdadf398f82fcd455eb1d |

Retained S4 raw evidence: 793660 bytes, below four MB.
