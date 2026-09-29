# Project Status

## Current Work

**M2 T45 S2 is closed at 1,651 / 1,992.** Its fourteen
`DefaultBlockObjTiles` through `ExBCDr` block/chunk OAM
labels all have ROM-match evidence. T45 S3 is next and is
not yet admitted.

## M2 T45 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T45 S2, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; fourteen exact labels transferred from M2 T17 S6. |
| Objective | Translate and prove the original DrawBlock and DrawBrickChunks OAM chain from DefaultBlockObjTiles through ExBCDr. |
| Non-goals | No S3-S5 graphics migration, platform gameplay logic, ROM emulator, or release claim. |
| Reference Baseline | Closed from 1,637/1,992; 14 actual new matches, final 1,651; T37 S5 root OAM child gap resolved. |
| Candidate Proposal | [T45 S2 block and chunk OAM](../proposals/m2/t45-object-oam-tail-and-graphics.md#s2-admission-record). |
| Files And ABI Surface | Shared src/game/oam/block_gfx.c and source-reachable child probes, three EXEs; no platform gameplay code. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original block/chunk child branch and RAM/OAM comparisons, focused native tests, x86/x64 and DOS16 builds, purity and artifacts. |
| Expected Markers | Brick tiles, replacement attributes, d2/d3 column hiding, chunk mirrored X, d7 top-row hide and signed relative-X check. |
| Asset Needs | Owner-local SMB1 ROM and reviewed listing for local verification only; ignored-build records and owner-authorized three EXEs. |
| Reporting Requirements | Fourteen individual node dispositions, two verification tracks, T37 S5 gap resolution and artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented clipping policy or platform gameplay. |
| Exit Criteria | Met: 14 ROM control/read/write/PC or data proofs, native x86/x64 root matches, DOS16 link, purity, refreshed EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | Every block and brick-chunk OAM caller using this source tail. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
