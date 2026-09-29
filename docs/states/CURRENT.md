# Project Status

## Current Work

**M2 T44 S8 is admitted at 1,582 / 1,992.** It owns the 44-label
`EnemyGraphicsTable` through `EggExc` enemy graphics and animation tree.
Forty-two open labels are expected to match, for a maximum of 1,624 / 1,992;
two already-complete bullet-bill labels are retained for recheck.

## M2 T44 S8 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation M2 T44 S8, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; exact transfers from M2 T17 S6 and M2 T31 S2. |
| Objective | Translate and prove the original `EnemyGfxHandler` control tree and all 44 named data/branch/OAM nodes. |
| Non-goals | No platform gameplay logic, generic NES emulation, or later audio slice. |
| Reference Baseline | 1,582/1,992; scope 44, expected new 42, retained complete 2, maximum 1,624. |
| Candidate Proposal | [T44 S8 enemy graphics](../proposals/m2/t44-block-buffer-and-object-graphics.md#s8-admission-enemy-graphics-and-animation). |
| Files And ABI Surface | Shared `src/game/oam/` owner, bounded recorder/test, three EXEs; no platform gameplay code. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original `RunNormalEnemies -> EnemyGfxHandler` controlled branch-family records, then separately focused native tests, x86/x64 and DOS16 builds, purity and artifacts. |
| Expected Markers | Exact graphics/offset/attribute/timing tables; retainer, bullet bill, jumpspring, ordinary enemies, Bowser and all drawing/flip/offscreen branches. |
| Asset Needs | Owner-local SMB1 ROM and reviewed listing, nonredistributable; bounded ignored-build records and owner-authorized three EXEs. |
| Reporting Requirements | Forty-four named dispositions, ROM logic and operational proofs, dependencies, artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented object/OAM policy or platform gameplay. |
| Exit Criteria | Every scoped label has source-route proof or exact justified non-entry disposition, native x86/x64 proof, DOS16 link, purity proof, refreshed EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | Every enemy graphics branch, row, animation mask, mirror/flip and OAM offscreen tail. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
