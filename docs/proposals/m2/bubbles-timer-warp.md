# M2 T35: Bubbles, timer and adjacent actor chains

## Source-order plan

The source slice is lines 6409-6729, 38 exact labels. Sixteen already-proven
labels retain their maintenance receiver and accepted evidence; the 22
incomplete labels below are expected new matches, maximum 772 from 750.
Only S1 is admitted. Later S numbers remain within this T proposal until
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
