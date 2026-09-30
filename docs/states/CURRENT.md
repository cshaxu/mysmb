# Project Status

## Current Work

## M2 Td S9 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 Td S9 — current-equivalence re-audit and repair-queue governance |
| Admission And Approval | Owner-directed re-audit after historical completion accounting proved insufficient to track present end-to-end equivalence. |
| Objective | Establish current-build, source-order node and edge registries for the complete original ROM graph, then produce an ordered, unnumbered repair queue from confirmed discrepancies. |
| Non-goals | No gameplay repair, node-credit promotion, platform logic, numeric implementation T allocation, or M2 closure. |
| Reference Baseline | Historical accounting: 1,992 / 1,992. Current node registry: 38 exact, 1944 needs-evidence, 10 mismatch, 0 unclassified. Current control-edge registry: 76 exact, 4241 needs-evidence, 25 mismatch, 0 unclassified. Material RAM/table ledger: 3 exact, 1 mismatch and 440 needs-evidence; its final denominator remains pending feasible-path enumeration. Scope is all labels and extracted edges; expected match delta is zero. |
| Candidate Proposal | docs/proposals/m2/current-equivalence-reaudit.md. |
| Files And ABI Surface | Governance states, audit registry, queue and neutral build-local recorder outputs; no production source mutation. |
| Applicable Rules | Execution, documentation, architecture, coding and source/research policy. |
| Verification | Node and edge registry integrity/counts; source-order cohort allocation; fresh original-ROM/x86/x64 preflight; platform-purity and documentation governance. |
| Expected Markers | 1,992 historical labels retained; every label and every extracted ROM graph edge assigned to one audit cohort; each node has a semantic contract, and each control or feasible material edge has an independently audited integration contract; no production artifact change. |
| Asset Needs | Owner-local ROM only under ignored build paths; no ROM, generated source, trace or executable is committed. |
| Reporting Requirements | Report historical count, current node counts and current edge counts separately; after every cohort report exact/needs-evidence/mismatch totals, routes, covered edges, and resulting unnumbered repair candidates. |
| Stop Conditions | Stop implementation on a node or edge mismatch; record its minimal contiguous chain and continue only independent audit cohorts. |
| Exit Criteria | Every label has a current semantic disposition; every extracted control edge and every proven feasible material edge has an independently recorded integration disposition; every mismatch has an ordered repair candidate; and the registries and queue pass governance review. |
| Original Owner Request | Faithful original-ROM C logic shared by DOS16 and Win32; DOS16 stays active via OpenNT, without DOSBox. |
| Similar-Issue Sweep | Audit every platform source for game-state decisions and every current mismatch for adjacent owner-chain effects. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 stays active through the existing OpenNT toolchain. Platform adapters do
not own game logic.

## Current Td S9 Preflight

T51 S5 found that its historical 1,992 / 1,992 status did not itself express
fresh full-graph behavior coverage. Its current T31 preflight replay confirms
the previously recorded PPU and audio residuals are no longer reproducible,
including the old pipe/vine diagnostic samples; this is retained as route
evidence only, not a claim that every label is newly audited. Td S9 now turns
that observation into an explicit whole-graph audit program. DOS resource
binding remains an M3 presentation requirement and does not change the shared
logic audit.
