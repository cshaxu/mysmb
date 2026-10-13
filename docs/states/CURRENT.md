# Project Status

## M3 T19 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Resumption: retained M3 T19 S1 P1; audit/research/design only in this owner-approved turn. |
| Admission And Approval | Owner explicitly approves entering the retained audio task for audit, research and design. No new T or S number. |
| Objective | Reconcile the suspended plan with current shared PCM/app code and produce a bounded single-process design and verification matrix. |
| Non-goals | No product implementation, new EXE, additional production process, driver/service manipulation, ROM or DOS/Win16 audio change. |
| Reference Baseline | 453ae52d; T45 S4 closed pending owner play acceptance. |
| Candidate Proposal | [T19 audio lifetime](../proposals/m3/bounded-windows-audio-startup.md). |
| Files And ABI Surface | Current/queue/ledger/proposal; about5documentation files,150-250lines plus required ledger metadata. No ABI change. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding, source policy and current component map. |
| Verification | Current call-site and test audit, bounded neutral device probes on both native widths, official WinMM lifetime contracts and governance gates. |
| Expected Markers | Empty ROM scope/expected/actual; historical1992/1992; no new equivalence credit. |
| Asset Needs | Project-owned PCM/probes only, no ROM. Microsoft API documentation is a reference, not imported code. Raw outputs contained under build/t19-s1-audit. |
| Reporting Requirements | Distinguish measured normal calls, static defects, unreproduced historical stalls, proposed behavior and outstanding proof. |
| Stop Conditions | No forced thread termination, freed driver-owned buffers, sibling writes or production edits in this design phase. |
| Exit Criteria | Audit/design receipt with ownership, state transitions, failure handling, app transactions, tests and implementation boundary; T/S stay open until implemented and verified. |
| Original Owner Request | Admit this T for audit, research and design. |
| Similar-Issue Sweep | Every WinMM entry, partial preparation, renderer continuity, reset/load atomicity, title status, close/Console lifetime and existing tests. |

## Current Technical Baseline

T19 S1 is active again. Its queue entry is removed; the five other candidates
retain their order. T45 S4 remains closed pending owner visual acceptance;
its local products and pending acceptance materials are preserved.
Historical1992/1992, retained1991/1992nodes and4260/4261feasible controls
(4342raw,81infeasible) remain unchanged; this is not ROM certification.

## S1 audit and design checkpoint

Current-source audit and revised design are recorded in the proposal.
Both widths pass the unchanged PCM owner test and8normal-device cycles each;
no historical8-second stall reproduced. Production code and EXEs unchanged.
Implementation, controlled-stall lifecycle prototype and product acceptance
remain outstanding in S1; this checkpoint does not close S1 or T19.
