# Project Status

## Current Work

## M2 T51 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T51 S5 — audit, cross-route integration certification |
| Admission And Approval | Continuing owner-approved M2 completion mandate; zero-credit final S of admitted T51. |
| Objective | Independently verify the completed shared game graph across native x86/x64 and OpenNT DOS16 delivery paths. |
| Non-goals | No new ROM-node credit, platform-owned game logic, or behavior rewrite. |
| Reference Baseline | 1,992 / 1,992 at admission; zero nodes in scope and zero expected matches. |
| Candidate Proposal | docs/proposals/m2/t51-residual-equivalence-and-certification.md S5. |
| Files And ABI Surface | Shared game roots, platform adapters, build and test configuration only. |
| Applicable Rules | Execution, architecture, coding, documentation and source/research policy. |
| Verification | Full x86/x64 build and CTest, focused ROM routes, platform purity, OpenNT DOS16 compile/link and three artifacts. |
| Expected Markers | 1,992 / 1,992; no inventory state change; three executable artifacts. |
| Asset Needs | Owner-local ROM only in ignored build inputs; no raw or derived ROM source enters tracked evidence. |
| Reporting Requirements | Record test matrix, artifact hashes, failed routes and any deferred issue. |
| Stop Conditions | Stop on any shared-core semantic discrepancy, test failure, or platform-boundary violation. |
| Exit Criteria | All matrix lanes pass, M2 conformance remains 1,992 / 1,992, and no unresolved governance or artifact defect remains. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; DOS16 stays active via OpenNT, without DOSBox. |
| Similar-Issue Sweep | Check all platform sources for game-state decisions before final closure. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 stays active through the existing OpenNT toolchain. Platform adapters do
not own game logic.

## Current S5 Finding

S5 P8 has completed the project-owned native regression matrix: x64 and x86
each pass 218 / 218 tests, owner-local area routing passes on both widths,
and the OpenNT DOS16 link is current. This does not close S5 or M2. The
review ledger retains independently recorded original-ROM discrepancies and
the DOS16 owner-resource binding gap; each requires source-route treatment
before the final certification can claim complete game behavior.
