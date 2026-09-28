# M2 T35: Bubbles, timer and adjacent actor chains

## Source-order plan

The source slice is lines 6409-6729, 38 exact labels. Sixteen already-proven
labels retain their maintenance receiver and accepted evidence; the 22
incomplete labels below are expected new matches, maximum 772 from 750.
S1 is closed; S2 is admitted. Later S numbers remain within this T proposal until
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
