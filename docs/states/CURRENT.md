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

The prior S5 native matrix has x64 and x86 at 218 / 218 and owner-local area
routing passing on both widths. P17 repairs the block-replacement high-row
VRAM route: all 32 original snapshots match on each width, including the
twelve former `$0301/$0306` differences. P18 independently revalidates the
former jumpspring screen-origin concern through `JumpspringHandler` and the
shared `OffscreenBoundsCheck`: a page-zero jumpspring remains live against the
ROM-wrapped `$ff:$b8` left boundary on x86 and x64. The final full matrix must
be rerun after the remaining shared-core repairs. S5 and M2 remain open because
the review ledger still contains independently recorded original-ROM
discrepancies; DOS resource binding is a separate M3 presentation delivery
requirement.
