# Project Status

## Current Work

## M2 T51 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T51 S5 — cross-route integration certification and discrepancy disposition |
| Admission And Approval | Continuation of the owner-approved M2 ROM-equivalence program; Td S9 has closed its zero-credit current-equivalence governance audit. |
| Objective | Complete the existing T51 integration review by dispositioning its cross-route findings, preserving evidence boundaries, and admitting any necessary shared-core repair only as the next T51 subtask. |
| Non-goals | No unplanned game logic repair, node-credit promotion, platform-owned game behavior, M2 closure, or new numeric T allocation. |
| Reference Baseline | Historical accounting: 1,992 / 1,992. Current re-audit: 38 exact, 1,944 needs-evidence and 10 mismatch nodes; 76 exact, 4,241 needs-evidence and 25 mismatch control edges; 3 exact, 483 needs-evidence and 1 mismatch material relations. S5 owns zero implementation labels. |
| Candidate Proposal | docs/proposals/m2/t51-residual-equivalence-and-certification.md; audit evidence in docs/proposals/m2/current-equivalence-reaudit.md and docs/states/M2_CURRENT_EQUIVALENCE.md. |
| Files And ABI Surface | Governance states, integration evidence and test expectations only. Any later repair must use a separately admitted T51 S6 packet and shared `src/game/` owner. |
| Applicable Rules | Execution, documentation, architecture, coding and source/research policy. |
| Verification | Cross-route source and ROM review; current node/edge registry integrity; x86/x64 operational routes; OpenNT DOS16 build; platform-purity and documentation governance. |
| Expected Markers | No S5 node-count increase; every S5 finding is either source-proved, retained as a current discrepancy, or handed to one bounded next-S shared-core repair chain. |
| Asset Needs | Owner-local ROM only below ignored build paths; no ROM, derived source, trace or executable is committed. |
| Reporting Requirements | Report historical and current-equivalence counts separately; identify each finding's ROM entry, shared owner, predecessor/successor and repair disposition. |
| Stop Conditions | Stop any code change until a bounded next-S packet has named its source-order chain, custody, original route and dual verification tracks. |
| Exit Criteria | Existing S5 integration findings are dispositioned without suppressing current mismatches; the next required repair is bounded under T51 or S5 is closed if no repair remains. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; platform adapters contain no gameplay logic; DOS16 remains active through OpenNT. |
| Similar-Issue Sweep | For every current mismatch, inspect adjacent shared-owner entry/exit and scratch/register handoff; audit all platform sources for game-state decisions. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 stays active through the existing OpenNT toolchain. Platform adapters do
not own game logic.

## Td S9 Closure Baseline

The current-equivalence governance audit closed with every registry record
dispositioned and source-anchored. It found bounded shared-core discrepancies;
it did not establish fresh whole-graph equivalence. The next code change,
if admitted, must remain inside the existing T51 continuation and must repair
the ROM-defined owner chain rather than a platform adapter.