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
