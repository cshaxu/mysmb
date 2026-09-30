# Project Status

## Current Work

## M2 T52 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T52 S1 — A2 NMI-prefix state-handoff remediation |
| Admission And Approval | Owner-directed successor to closed T51: repair every confirmed current-equivalence discrepancy under T52, beginning with A2. |
| Objective | Restore the ROM NMI-prefix scratch and PPU-control handoff through `RotPRandomBit -> SkipSprite0 -> OperModeExecutionTree`. |
| Non-goals | No platform-owned game logic, no historical node-credit increase, no unrelated NMI redesign, and no M2 closure claim. |
| Reference Baseline | Historical accounting 1,992 / 1,992. Current registry before S1: A2 has three mismatched nodes and two mismatched control edges; T52 S1 scope is those three historical-complete labels and expects zero historical credit. |
| Candidate Proposal | docs/proposals/m2/t52-current-audit-mismatch-remediation.md; docs/proposals/m2/a2-nmi-prefix-repair-candidate.md. |
| Files And ABI Surface | Shared `src/game/frame_root.c`, its focused tests and current-equivalence registry; no platform adapter behavior. |
| Applicable Rules | Execution, documentation, architecture, coding and source/research policy. |
| Verification | Controlled original-ROM cold-boot NMI prefix to the `OperModeExecutionTree` boundary; x86/x64 focused route and build; OpenNT DOS16 link; platform-purity; three target artifacts. |
| Expected Markers | ROM scratch `$00` equals the first masked LFSR bit; d7 remains clear in PPU control at dispatch and returns only at the RTI-equivalent tail; A2 registry delta is three nodes and two edges to exact after proof. |
| Asset Needs | Owner-local ROM only below ignored build paths; no ROM, derived source, trace or executable is committed. |
| Reporting Requirements | Report the three named labels, two edges, first divergent field/frame before repair, both verification tracks and unchanged historical numerator. |
| Stop Conditions | Stop if the corrected handoff changes pause, sprite-zero, scroll, or mode-dispatch behavior outside the named boundary; record any new discrepancy as a bounded successor candidate. |
| Exit Criteria | All three A2 labels and both A2 edges are ROM-logic and operationally exact; x86/x64/DOS16 use the same shared source; subsequent T52 S chains remain unadmitted until this S closes. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; DOS16 remains active through OpenNT and platforms contain no gameplay decisions. |
| Similar-Issue Sweep | Inspect all `frame_root.c` scratch writes and PPU-control d7 phase transitions; classify each as source-equivalent, mismatch, or later bounded candidate. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 stays active through the existing OpenNT toolchain. Platform adapters do
not own game logic.