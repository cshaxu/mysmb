# Project Status

## M3 T19 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Resumption: retained M3 T19 S1 P2; approved three-platform design amendment. S1 remains the Win32 implementation chain; S2-S4 are planned, not concurrently admitted. |
| Admission And Approval | Owner approves a suitable design and repair of Win32/64, Win16 and DOS16 audio based on the audit. Retain T19/S1; no new T. |
| Objective | Define shared device contracts and complete per-platform lifecycle repairs; this P fixes the scope, findings, S sequence and measurable acceptance before implementation. |
| Non-goals | No additional production process, driver/service manipulation, game/APU/PPU rewrite, new audio backend, Mine music feature or save-format change. |
| Reference Baseline | efd9015a; T45 S4 closed pending owner play acceptance. |
| Candidate Proposal | [T19 audio lifetime](../proposals/m3/bounded-windows-audio-startup.md). |
| Files And ABI Surface | This P: Current/proposal/ledger, about4documentation files and200-250lines. Planned S1: lib/kvm audio declarations, lib/win32 PCM/session, Mario Win32 adapters and mirrored tests/build wiring;10-16files,700-1200lines estimate. No ABI change in this design P. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding, source policy and current component map. |
| Verification | Current DOS/Win16/Win32 lifecycle and test audit; node-ledger/admission and documentation gates for this P. Implementation matrix and platform-specific limits are in the proposal's three-platform amendment. |
| Expected Markers | Empty ROM scope/expected/actual; historical1992/1992; no new equivalence credit. |
| Asset Needs | Project-owned PCM/probes only, no ROM. Microsoft API documentation is a reference, not imported code. Raw outputs contained under build/t19-s1-audit. |
| Reporting Requirements | Distinguish measured normal calls, static defects, unreproduced historical stalls, proposed behavior and outstanding proof. |
| Stop Conditions | No forced thread termination, freed driver-owned buffers, sibling writes, hidden retry loops or unsupported hard-cancellation claims. Only the active S may change product owners. |
| Exit Criteria | S1 closes only after the Win32 lifecycle chain and its tests/products pass; T19 closes only after S2 Win16, S3 DOS16 and S4 integration fulfill the fixed findings/acceptance register. Design completion is not repair completion. |
| Original Owner Request | Design and resolve audio problems on all three platforms from the audit conclusions. |
| Similar-Issue Sweep | All host calls, partial cleanup, queues, renderer continuity, reset/load, focus/Tab, teardown, Win16 retry/reentrancy and DOS DMA/IRQ/polling; each finding has a receiving S. |

## Current Technical Baseline

T19 S1 is active again. Its queue entry is removed; the five other candidates
retain their order. T45 S4 remains closed pending owner visual acceptance;
its local products and pending acceptance materials are preserved.
Historical1992/1992, retained1991/1992nodes and4260/4261feasible controls
(4342raw,81infeasible) remain unchanged; this is not ROM certification.

## Approved execution sequence

S1: shared facts/ownership contract and Win32 asynchronous lifetime/app joins.
S2: Win16 cooperative lifecycle, bounded retries and app/host close/load joins.
S3: DOS16 bounded DSP/IRQ lifecycle, queue publication and fault containment.
S4: integrated product qualification, memory/cost/audio receipts and T closure.
Only S1 is active. Admission of each next S requires predecessor closure,
the before-work brief, its own packet/ledger run and a reviewed scope.

## S1 audit and design checkpoint

Current-source audit and revised design are recorded in the proposal.
Both widths pass the unchanged PCM owner test and8normal-device cycles each;
no historical8-second stall reproduced. Production code and EXEs unchanged.
The approved three-platform amendment records12additional DOS/Win16/cross-host
clauses plus the retained A1-A8 Win32 findings. Current tests cover some error
returns but do not prove responsiveness or the DOS hardware path. No new
production/test code or EXE is included in P2. Implementation, controlled-stall
lifecycle prototype and product acceptance remain outstanding in S1;
this checkpoint does not close S1 or T19.
