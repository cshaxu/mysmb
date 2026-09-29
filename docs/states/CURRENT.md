# Project Status

## Current Work

**M2 T43 S14 is closed at 1,510/1,992: 7 scoped, 7 ROM-match complete.**
T43 covers 150 nodes; the revised global maximum of 1,517 retains the KillEnemies debt.

## M2 T43 S14 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation M2 T43 S14, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; accepted transfer 234. |
| Objective | Translate `BoundingBoxCore` through `NoOfs2`, including source byte arithmetic and both horizontal screen-edge clipping branches. |
| Non-goals | No collision geometry, no caller selection rewrite, no platform gameplay. |
| Reference Baseline | 1,503/1,992; scope 7/expected 7, maximum 1,510. |
| Candidate Proposal | [S14 bounding-box coordinates and edge clipping](../proposals/m2/t43-terrain-and-bounding-boxes.md#s14-bounding-box-coordinates-and-edge-clipping). |
| Files And ABI Surface | Shared `src/game/world/` bounding-box owner, its declared game-only interface, focused tests/recorder, manifests and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original control-table offsets, byte-coordinate writes, right/left clipping branches and call order; separate native operational proof. |
| Expected Markers | Four coordinate writes, source middle-screen comparison, right and left clipping writes, retained caller routes. |
| Asset Needs | Owner-local nonredistributable ROM/listing; bounded records below ignored build. Three owner-authorized EXEs. |
| Reporting Requirements | Seven named dispositions, dual proof, retained dependency results and artifact hashes. |
| Stop Conditions | Forced original CPU path, concealed descendant mismatch, unadmitted algorithm rewrite or platform gameplay. |
| Exit Criteria | Met: seven nodes have source and ROM-route evidence, focused tests, cross-width builds, DOS16 link, purity proof and refreshed three EXEs. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All bounding-box core callers, table bindings, byte carries, page/screen comparisons, left/right edge writes and direct platform references. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only. The local original-ROM execution tools are validation-only and are not linked into the game. ROM-derived resources and build intermediates remain under ignored build output; the owner-authorized three test EXEs are in assets/.

## Preserved limits

M2 remains incomplete. Existing graphics, audio, child/full-frame and legacy runtime debts retain their tracker/ledger records. DOS16 has build/link evidence; there is no supported claim of DOS graphical playability, resource binding or physical 486SX performance. Earlier task records remain under history/.
