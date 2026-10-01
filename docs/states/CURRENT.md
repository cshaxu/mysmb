# Project Status

## Current Work

## M2 T52 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T52 S2 — A6 title-demo/world-select order remediation. |
| Admission And Approval | Owner-directed successor to closed T52 S1; the owner-approved T52 mandate covers every confirmed current-equivalence discrepancy. |
| Objective | Restore the original `ChkSelect -> ChkWorldSel` predicate and ordering in the shared title-menu chain. |
| Non-goals | No platform-owned menu logic, no historical node-credit increase, and no changes beyond the received title-menu chain. |
| Reference Baseline | Historical accounting 1,992 / 1,992. Scope: `ChkSelect` (mismatch) and `ChkWorldSel` (needs-evidence); expected historical-credit delta zero; maximum 1,992. |
| Candidate Proposal | docs/proposals/m2/t52-current-audit-mismatch-remediation.md#t52-s2-admission-a6-title-demoworld-select-order. |
| Files And ABI Surface | Shared `src/game/title_modes.c`, focused title tests and registry; no platform adapter behavior. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source/research policy. |
| Verification | Controlled original-ROM title-menu boundary with DemoTimer zero/nonzero B routes; focused shared-C test; ROM-configured x86/x64, OpenNT DOS16 link and platform purity. |
| Expected Markers | At DemoTimer zero, B cannot alter world selection: original demo/reset path keeps the source post-menu state; only nonzero DemoTimer permits `ChkWorldSel` and its SelectBLogic tail. |
| Asset Needs | Owner-local ROM only below ignored build paths; three locally refreshed executable artifacts are never committed. |
| Reporting Requirements | Report both received labels, `control-00087`, the first divergent field, both title routes, verification tracks and unchanged historical numerator. |
| Stop Conditions | Stop if correction changes Select, Start, demo or world-select behavior outside the named source boundary; record a new discrepancy as a later candidate. |
| Exit Criteria | Both labels and `control-00087` are current-equivalence exact under static and ROM-route proof; all targets use the same shared source. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32, with platform adapters free of gameplay decisions. |
| Similar-Issue Sweep | Every title-menu button priority, DemoTimer gate and SelectBLogic entry; classify each source order as exact, mismatch or deferred evidence. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64. DOS16 stays active through the existing OpenNT toolchain. Platform adapters do not own game logic.
