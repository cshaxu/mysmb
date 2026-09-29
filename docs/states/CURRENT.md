# Project Status

## Current Work

**M2 T43 S15 is closed at 1,517/1,992: 7 scoped, 7 ROM-match complete.**
T43 covers 150 nodes; the revised global maximum of 1,517 retains the KillEnemies debt.

## M2 T43 S15 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation M2 T43 S15, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; accepted transfer 235. |
| Objective | Translate `PlayerCollisionCore` through `CollisionFound`, including both box entries, two-axis loop, wrap/equality branches and terminal state. |
| Non-goals | No caller-specific collision policy, no actor reaction rewrite, no platform gameplay. |
| Reference Baseline | 1,510/1,992; scope 7/expected 7, maximum 1,517. |
| Candidate Proposal | [S15 shared box collision geometry](../proposals/m2/t43-terrain-and-bounding-boxes.md#s15-shared-box-collision-geometry). |
| Files And ABI Surface | Shared `src/game/world/` geometry owner, game-only interface, focused tests/recorder, manifests and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original two-axis comparison branches, scratch `$06/$07`, return/carry state and caller order; separate native operational proof. |
| Expected Markers | Player and sprite entry selection, wrapped comparisons, no-collision and collision terminal writes. |
| Asset Needs | Owner-local nonredistributable ROM/listing; bounded records below ignored build. Three owner-authorized EXEs. |
| Reporting Requirements | Seven named dispositions, dual proof, retained dependency results and artifact hashes. |
| Stop Conditions | Forced original CPU path, concealed descendant mismatch, unadmitted algorithm rewrite or platform gameplay. |
| Exit Criteria | Met: all seven nodes have source and ROM-route evidence, focused tests, cross-width builds, DOS16 link, purity proof and refreshed three EXEs. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All shared-box callers, coordinate order, equality/wrap branches, RAM `$06/$07`, terminal flags and direct platform references. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only. The local original-ROM execution tools are validation-only and are not linked into the game. ROM-derived resources and build intermediates remain under ignored build output; the owner-authorized three test EXEs are in assets/.

## Preserved limits

M2 remains incomplete. Existing graphics, audio, child/full-frame and legacy runtime debts retain their tracker/ledger records. DOS16 has build/link evidence; there is no supported claim of DOS graphical playability, resource binding or physical 486SX performance. Earlier task records remain under history/.
