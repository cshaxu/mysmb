# Project Status

## Current Work

**M2 T44 S7 is closed at 1,582 / 1,992.** It completed the six-node
`PowerUpGfxTable` through `PUpOfs` power-up graphics chain with no deferred
labels.

## M2 T44 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed M2 T44 S7, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 mandate; exact transfer 242 from M2 T17 S6. |
| Objective | Translate and prove the power-up OAM graphics chain. |
| Non-goals | No platform host gameplay and no enemy-animation chain. |
| Reference Baseline | Closed from 1,576/1,992; scope 6/actual 6, final 1,582. |
| Candidate Proposal | [T44 block-buffer and object graphics](../proposals/m2/t44-block-buffer-and-object-graphics.md#s7-power-up-graphics). |
| Files And ABI Surface | Shared game power-up OAM owner, recorder/test and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and validation matrix. |
| Verification | Original `PowerUpObjHandler -> DrawPowerUp`, followed separately by focused native tests and three-target operational proof. |
| Expected Markers | Four graphics rows, palette table, type branches, right-side flip and offscreen handoff. |
| Asset Needs | Owner-local ROM/listing and bounded ignored-build records; three owner-authorized EXEs. |
| Reporting Requirements | Six named dispositions, dual proof, dependency results and artifact hashes. |
| Stop Conditions | Forced CPU path, unadmitted dependency, invented OAM policy or platform gameplay. |
| Exit Criteria | Met: every scoped node has source-route proof, focused test evidence, x86/x64 builds, DOS16 link, purity proof and refreshed EXEs. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | Power-up types, palette and flip branches, OAM rows and offscreen handoff. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only.
