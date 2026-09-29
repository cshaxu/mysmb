# Project Status

## Current Work

**M2 T43 S12 is closed at 1,492/1,992: 3 scoped, 3 completed.**
T43 covers 150 nodes; revised global maximum 1,517 retains the KillEnemies debt.

## M2 T43 S12 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation M2 T43 S12, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; accepted transfer 232. |
| Objective | `FireballBGCollision`, `ClearBounceFlag`, and `InitFireballExplode`. |
| Non-goals | No fireball core/offscreen rewrite, no bounding-box entry work, no platform gameplay. |
| Reference Baseline | 1,489/1,992; scope 3/expected 3, maximum 1,492. |
| Candidate Proposal | [S12 fireball background collision](../proposals/m2/t43-terrain-and-bounding-boxes.md#s12-fireball-background-collision). |
| Files And ABI Surface | Shared world collision owner, fireball caller seam, tests/recorder, manifests and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original fireball Y/probe/Z paths, bounce/explosion writes and call order; separate native operational proof. |
| Expected Markers | Original ordered Y gate, bottom probe, non-solid branch, bounce alignment and explosion tail. |
| Asset Needs | Owner-local nonredistributable ROM/listing; bounded records below ignored build. Three owner-authorized EXEs. |
| Reporting Requirements | Three named dispositions, dual proof, retained dependency results and artifact hashes. |
| Stop Conditions | Forced original CPU path, concealed descendant mismatch, unadmitted algorithm rewrite or platform gameplay. |
| Exit Criteria | Met: three proved nodes, both proof tracks and three artifacts. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | Fireball collision callers, duplicate non-solid checks, bounce/explosion RAM writes and direct platform references. |

## S8 closure

[Enemy terrain dispatch/stun proof](../proposals/m2/t43-terrain-and-bounding-boxes.md#s8-enemy-terrain-dispatch-and-stun-proof)
closes twelve expected nodes and retains six dispatch nodes:1,451 ->1,463.
The observed original route set has1,642 reachable entries; caller replay
matches on x86/x64 and direct stun matches retained calls. Real child gaps stay
with S9/S10/S11. All three EXEs are refreshed; DOS remains link-only.

## S7 closure

[Classifier proof](../proposals/m2/t43-terrain-and-bounding-boxes.md#s7-metatile-classification-proof)
closes all seven expected nodes and retains ExEBG using 1,034 original routes.
All 23 instructions and four branch directions execute; actual captured
classifier calls match on both widths. A single shared table/predicate owner
replaces duplicates. Terrain baselines remain intact. Ten CTests pass; legacy
failures remain explicit. Three EXEs refreshed; DOS remains link-only.

## S6 closure

[Impede proof](../proposals/m2/t43-terrain-and-bounding-boxes.md#s6-impede-proof)
closes all five nodes with 1,024 actual full-RAM original matches per width.
All 33 instructions and eight branch directions execute. RAM00 and speed80
semantics are restored; 242 retained impede calls match. Terrain/platform
caller baselines remain intact. Nine CTests pass; the old core/bounding-box
failures remain explicit. Three EXEs refreshed; DOS remains link-only.

## S5 closure

[Pipe-entry proof](../proposals/m2/t43-terrain-and-bounding-boxes.md#s5-pipe-entry-proof)
closes all three nodes with512 actual original full-RAM matches per width.
All46 instructions and12 branch directions execute. Missing destination reads,
silence and raw-index semantics are restored. S1 retains1,034 caller,59 actual
and177 pipe-child matches per width. Eight CTests pass; legacy core/bounding-box
failures remain explicit. Three EXEs refreshed; DOS remains link-only.

## S4 closure

[Hidden/spring proof](../proposals/m2/t43-terrain-and-bounding-boxes.md#s4-hidden-and-spring-proof)
closes all seven scoped nodes. Both widths match531 actual original entries
from512 NMI routes, including consumed flags and full RAM. All22 instructions
and eight branch directions execute. S1 retains1,034 caller,59 actual and177
landing-child matches per width. Six selected CTests pass; legacy core and
bounding-box failures remain. Three EXEs refreshed; DOS remains link-only.

## S3 closure

[Climbing proof](../proposals/m2/t43-terrain-and-bounding-boxes.md#s3-climbing-proof)
closes all14 scoped nodes. Both widths match1,024 original caller routes;
all71 instructions and24 branch directions execute. Actual roots match960;
64 KillEnemies calls omit RAM00. Its old completion is revoked, with M2 T29 S8
maintenance retained. S1's1,034 caller,59 actual and159 climbing matches remain.
Five focused CTests pass; legacy core/bounding-box failures remain explicit.
All121 shared units and three EXEs are refreshed; DOS remains link-only.

## S2 closure

[Coin/axe proof](../proposals/m2/t43-terrain-and-bounding-boxes.md#s2-coin-and-axe-proof)
closes HandleCoinMetatile, HandleAxeMetatile and ErACM. Both widths match128
original caller routes; actual-root matches16/128, with independently measured
VRAM/status child gaps retained. Native6,144 cases pass per width; S1 retains
all1,034 caller and59 actual matches. Four focused CTests pass; legacy core
and bounding-box failures remain explicit. Three EXEs refreshed; DOS link-only.

## S1 closure

[Original terrain caller proof](../proposals/m2/t43-terrain-and-bounding-boxes.md#s1-original-terrain-control-proof)
closes31 nodes with1,034 matched caller routes per width. All192 instructions
and109 reachable branch outcomes execute; three dominated outcomes are audited.
Actual root matches59/1,034; independent children3,047/8,049. Scratch gaps retain
their existing owners.12/13 selected CTests pass; core and bounding-box baseline
failures remain explicit. Three EXEs refreshed; DOS link-only. S2 coin/axe is next.

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and
Win32 x86/x64. Host adapters provide input, timing and presentation only.
The local original-ROM execution tools are validation-only and are not linked
into the game. ROM-derived resources and build intermediates remain under
ignored build output; the owner-authorized three test EXEs are in assets/.

## Preserved limits

M2 remains incomplete. Existing graphics, audio, child/full-frame and legacy
runtime debts retain their tracker/ledger records. DOS16 has build/link evidence;
there is no supported claim of DOS graphical playability, resource binding or
physical 486SX performance. Earlier task records remain under history/.
