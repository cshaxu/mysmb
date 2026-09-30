# Project Status

## Current Work

## M2 T51 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T51 S6 — current-equivalence NMI-prefix repair |
| Admission And Approval | Continuation under the owner-approved M2 completion mandate after Td S9 completed the whole-graph static classification and confirmed A2. |
| Objective | Repair and prove the shared `RotPRandomBit -> SkipSprite0 -> OperModeExecutionTree` NMI-prefix chain against the original ROM. |
| Non-goals | No platform-adapter game logic, historical node-credit increase, unrelated NMI migration, graph-extractor repair, or M2 closure. |
| Reference Baseline | Historical accounting: 1,992 / 1,992. Current registry: 38 exact, 1944 needs-evidence, 10 mismatch and 0 unclassified nodes; 76 exact, 4241 needs-evidence, 25 mismatch and 0 unclassified control edges. S6 receives three historically complete labels in current mismatch state and forecasts no historical credit. |
| Candidate Proposal | docs/proposals/m2/t51-residual-equivalence-and-certification.md and docs/proposals/m2/a2-nmi-prefix-repair-candidate.md. |
| Files And ABI Surface | Shared `src/game/frame_root.c`, focused test/route support below `build/m2-t51-s6`, registry, tracker and local three-artifact refresh only. |
| Applicable Rules | Execution, documentation, architecture, coding and source/research policy. |
| Verification | Original ROM/x86/x64 controlled pre-dispatch NMI route for `$00` and `$2000`; focused NMI test; x86/x64 builds; OpenNT DOS16 link; platform-purity and documentation governance. |
| Expected Markers | `$00` equals the source bit/rotation result; `$2000` retains d7 clear through mode dispatch and restores only at RTI equivalent; three nodes and two control edges become current-exact only with route evidence. |
| Asset Needs | Owner-local ROM only below ignored build paths; no ROM, generated trace or executable is committed. |
| Reporting Requirements | Report static source result and ROM/native route result separately; refresh and report local 16/32/64 artifacts after every implementation P. |
| Stop Conditions | Stop on the first divergent NMI field/frame, record the smallest shared-owner chain, and do not repair through Win32 or DOS adapters. |
| Exit Criteria | The three labels and `control-00040`/`control-00052` have fresh source and route evidence, registry dispositions are updated, and the T51 S5 matrix is re-run or its remaining route gap is explicitly recorded. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; DOS16 stays active via OpenNT, without DOSBox. |
| Similar-Issue Sweep | Examine all `frame_root.c` NMI scratch/control writes and all platform-source files for gameplay-state decisions. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 stays active through the existing OpenNT toolchain. Platform adapters do
not own game logic.
