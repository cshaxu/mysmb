# Project Status

## Current Work

**M2 T45 S3 is closed at 1,658 / 1,992.** Its seven
`DrawFireball` through `KillFireBall` OAM labels have
ROM-match evidence. T45 S4 is next and not yet admitted.

## M2 T45 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T45 S3, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; two exact labels transfer from M2 T16 S4 and five from M2 T17 S6. |
| Objective | Translate and prove the original DrawFireball through KillFireBall projectile/explosion OAM chain. |
| Non-goals | No fireball motion/collision rewrite, S4-S5 graphics, platform gameplay logic, ROM emulator, or release claim. |
| Reference Baseline | Closed from 1,651/1,992; seven actual new matches, final 1,658; T24 D3/D4 mismatches resolved. |
| Candidate Proposal | [T45 S3 projectile and explosion OAM](../proposals/m2/t45-object-oam-tail-and-graphics.md#s3-admission-record). |
| Files And ABI Surface | Shared src/game/oam/fireball_gfx.c, firebar_gfx.c and fireworks_gfx.c, source-reachable child probes, three EXEs; no platform gameplay code. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original fireball/firebar/fireworks child branch and RAM/OAM comparisons, focused native tests, x86/x64 and DOS16 builds, purity and artifacts. |
| Expected Markers | Four-frame tile, eight-frame flip, three explosion tiles, kill transition and four-sprite coordinate ordering. |
| Asset Needs | Owner-local SMB1 ROM and reviewed listing for local verification only; ignored-build records and owner-authorized three EXEs. |
| Reporting Requirements | Seven individual node dispositions, two verification tracks, T24 D3/D4 resolution and artifact hashes. |
| Stop Conditions | Forced CPU branch, unadmitted external dependency, invented graphics policy or platform gameplay. |
| Exit Criteria | Met: seven ROM control/read/write/PC or data proofs, native x86/x64 matches, DOS16 link, purity, refreshed EXEs and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | Every fireball/firebar/fireworks caller using this source tail. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
