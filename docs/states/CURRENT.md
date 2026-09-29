# Project Status

## Current Work

**M2 T45 S1 is closed at 1,637 / 1,992.** Its 13 original
`CheckToMirrorLakitu` through `MoveESprColOffscreen` labels
all have ROM-match evidence. T45 S2 is next; it is not yet admitted.

## M2 T45 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T45 S1, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; thirteen exact labels transferred from M2 T17 S6. |
| Objective | Translate and prove the original enemy graphics mirror, row-draw and offscreen tail from `CheckToMirrorLakitu` through `MoveESprColOffscreen`. |
| Non-goals | No S2-S5 graphics migration, platform gameplay logic, ROM emulator, or release claim. |
| Reference Baseline | Closed from 1,624/1,992; 13 actual new matches, final 1,637; all thirteen original-PC witnesses. |
| Candidate Proposal | [T45 S1 enemy OAM tail](../proposals/m2/t45-object-oam-tail-and-graphics.md#s1-admission-record). |
| Files And ABI Surface | Shared `src/game/oam/` owner, bounded original recorder/test, three EXEs; no platform gameplay code. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original normal/Bowser/jumpspring branch and RAM/OAM comparisons, focused native tests, x86/x64 and DOS16 builds, purity and artifacts. |
| Expected Markers | Lakitu mirror branches, spring attributes, d2-d7 row/column hiding, source three-row drawing and final erase/return. |
| Asset Needs | Owner-local SMB1 ROM and reviewed listing for local verification only; ignored-build records and owner-authorized three EXEs. |
| Reporting Requirements | Thirteen individual node dispositions, two verification tracks, missing-PC closure, artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented clipping policy or platform gameplay. |
| Exit Criteria | Met: 13 ROM control/read/write/PC proofs, native x86/x64 matches, DOS16 link, purity, refreshed EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | Every enemy mirror, sprite-row, row/column offscreen and erase caller using this tail. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
