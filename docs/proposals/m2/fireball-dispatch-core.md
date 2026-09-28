# M2 T34: Fireball dispatch and core

## Source-order plan

T33 closes at 739 / 1,992. T34 owns eleven incomplete labels in source lines
6298-6408, expected eleven, maximum 750. Existing custody is M2 Td S5;
only the first five transfer at S1 admission. Historical T20 is not reopened.

| S | Exact source-order nodes | Shared owner and contract |
| --- | --- | --- |
| S1 | `ProcFireball_Bubble`, `ProcFireballs`, `ProcAirBubbles`, `BublLoop`, `BublExit` | Fireball spawn/dispatch and ordered bubble caller loop |
| S2 | `FireballXSpdData`, `FireballObjCore`, `RunFB`, `EraseFB`, `NoFBall`, `FireballExplosion` | Fireball state, initialization, active child ordering and explosion dispatch |

## S1 admission: fireball and bubble dispatch

Scope five, expected five, maximum 744 from incoming 739. ProcFireball_Bubble
is audited/revalidation-required; ProcFireballs, ProcAirBubbles, BublLoop and
BublExit are open. Transfer-142 accepts all five from M2 Td S5. GameEngine
calls this chain before enemy-slot work. Shared game/fireball owns dispatch;
BubbleCheck, relative/offscreen/graphics, movement and collision children
retain their existing receivers until their source-order admission. Extract
child seams where necessary without claiming child equivalence.

Audit PlayerStatus partition, new-B press, counter-selected slot, high-Y,
crouch and climbing gates, sound/state/timer/counter writes, slot-zero then
slot-one order, area gate, and bubble indices two through zero with original
ObjectOffset and child-call order. Use natural NMI original caller/child
entry-return observations and separately run actual native children, retaining
all differences. Independent mutation/call-order tests, strict C90 x86/x64,
DOS16 link, platform purity and three local artifacts provide the operational
track. Do not patch reference CPU, stack, ROM or outputs to obtain matches.

Similar-issue sweep covers all spawn/dispatch definitions, state/timer/sound
writers and bubble loops. Original source-line numbers in old address comments
must not be treated as ROM addresses. S2 owns the core state machine and its
embedded explosion branch; S1 may only expose unchanged child boundaries.

Owner ROM and listing remain local research inputs, not imported source or
redistributable assets. Temporary evidence stays under ignored build/m2-t34-s1,
with four MB per retained batch and twenty seconds per recorder run. S1 owns
cleanup through T review. DOS remains link-only. T closure requires all eleven
exact dispositions, both proof tracks, integrated regression and three artifact
identities; unadmitted downstream mismatches keep their existing ownership.

## S1 implementation checkpoint

The original dispatch path is separated from child interiors. fireball_spawn.c
owns the one PlayerStatus gate, spawn branch, ordered slot-zero/slot-one calls,
and ProcAirBubbles/BublLoop/BublExit. fireball_core.c exposes the unchanged
single-slot core as mysmb_fireball_step_object; its state initialization and
explosion behavior remain S2 work. bubble.c exposes its existing check,
relative-position, offscreen and draw bodies at their original boundaries.
No child algorithm is certified or repaired by this extraction.

The dispatch now writes ObjectOffset before each descending bubble slot,
as the original BublLoop does. It reads AreaType after both fireball children
return, and does not re-read PlayerStatus between those two calls. Original
spawn sound/state/timer/counter operations stay in the existing shared helper.
The incorrect source-line-as-address comment is corrected to identify a
source line. No platform source changed.

The focused callback test passes 6,144 spawn-gate combinations on each Windows
width, including counter overflow and animation-timer underflow. It separately
checks all fourteen fireball/bubble child calls, per-slot ObjectOffset, the
post-child area gate and status changes that must not suppress the second
fireball call. Each extracted source also compiles with strict C90 flags on
both widths. These are operational checks, not original-ROM node proof.

At this intermediate checkpoint all five received nodes were incomplete at
739 / 1,992. The original comparisons, actual-child diagnostics, three-target
delivery and final review are completed in the closure record below.

## S1 original dispatch proof

Original $B624-$B686 has five scoped nodes and nine conditional branches.
The shared dispatcher restores the original call tree while unchanged core,
bubble and rendering children retain their own proof obligations.

| Node | Address | Proven contract |
| --- | --- | --- |
| ProcFireball_Bubble | $B624 | Single PlayerStatus partition; new-B/slot/Y/crouch/state gates and spawn writes |
| ProcFireballs | $B664 | Slot zero then slot one, without rechecking status |
| ProcAirBubbles | $B66E | Post-child AreaType gate |
| BublLoop | $B675 | Indices 2/1/0, ObjectOffset and four original children in order |
| BublExit | $B686 | Water-loop completion and non-water return |

Thirty-two ordinary-NMI scenarios cover all nine branches in both directions.
The observer records ProcFireball_Bubble's real hardware-stack return and up
to fourteen immediate children: FireballObjCore, BubbleCheck,
RelativeBubblePosition, GetBubbleOffscreenBits and DrawBubble. Each child's
original X argument and 2,048-byte entry/return RAM are captured without
changing CPU, stack, ROM or outputs. The native caller checker compares slot
arguments and 1,784 persistent RAM bytes at every entry and final return,
replaying only the observed original child returns. All 64 caller checks pass
across x86/x64. Scratch $00-$07 and hardware stack are outside the native ABI.

The separate actual-native check yields 34 matches and 30 failures. Cases
2-15 on each width retain ObjectOffset ($08), original 01 versus native 00,
because the original FireballObjCore writes it even for an inactive slot.
This is explicitly T34 S2 core work, not repaired by S1 extraction. Cases
15/31 additionally differ at $0204/$0208 (04/FC exchanged), the existing
explosion-OAM child issue with its graphics owner. Water bubbles eventually
write ObjectOffset zero, so that final-state match does not certify the
fireball core's missing intermediate write. Both widths report identical
failures. No mismatch is masked or relabeled as a complete child.

Reproduce with fireball_dispatch_fixture.h cases 0-31 at ordinary NMI,
one frame and warmup one. Set logical B for cases whose value modulo sixteen
is at least four; otherwise use zero. Reverse the controller byte for the
reference serial interface. Record `--fixture=t34-dispatch=N` with
`--dispatch-snapshot=...` and `--control-children=...`; repeat with PC coverage
and without observers. Observed, coverage and unobserved frames are identical.
Build both modes of fireball_dispatch_snapshot_check.c and run
verify_fireball_dispatch_snapshots.py over the contained batch. Raw evidence
is 2,107,441 bytes, below the admitted four-MB limit.

The independent callback test passes 6,144 gate combinations per width and
checks original slot order, all bubble calls and post-child area reads. Both
widths compile all 67 shared units as strict C90. Bubble OAM, fireball OAM and
player-route suites pass (six executions); Windows self-tests and hidden
window/message probes pass. The full DOS16 build links. Platform purity
passes. Similar-issue sweep confirms a single spawn/dispatch owner, one
single-slot core and one descending bubble caller loop; extraction preserves
child algorithm text and return/continue meaning. No platform source changes.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258845 | a3c874cba1f956c0ea7e892632c5b0429c2ca53cf99b4b74717700cc8b397281 |
| mysmb32.exe | 326131 | 6805c6d6f89f7f51144136d45f55a02f51a87c8a9dcf57a35bd15b43e7a46d9b |
| mysmb64.exe | 334177 | 4313ef7b97b3670b3e95aa2f9f1fd9627b4ef46c99267f1683353c53ff1eefa4 |

DOS remains link-only and local binaries follow the owner-authorized delivery
exception. Final review accepts 5/5 expected matches, exactly the five rows
above; no received node is unfinished and no child receives credit. Progress
739 -> 744 / 1,992 (one prior audited node and four open nodes completed).
Ledger and documentation checks pass. S1 closes; T34 remains open.
