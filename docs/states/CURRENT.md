# Project Status

## M3 T19 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: retained M3 T19 S1 P3, Win32 implementation. S2-S4 remain planned, not concurrently admitted. |
| Admission And Approval | Owner approves a suitable design and repair of Win32/64, Win16 and DOS16 audio based on the audit. Retain T19/S1; no new T. |
| Objective | Implement and verify the shared audio facts and Win32 asynchronous device lifetime, app transactions and responsive shutdown. Owner authorizes autonomous single-person coordinator/executor review through T closure and six-product build/test delivery. |
| Non-goals | No additional production process, driver/service manipulation, game/APU/PPU rewrite, new audio backend, Mine music feature or save-format change. |
| Reference Baseline | b9204497; T45 S4 closed pending owner play acceptance. |
| Candidate Proposal | [T19 audio lifetime](../proposals/m3/bounded-windows-audio-startup.md). |
| Files And ABI Surface | lib/kvm audio declarations, lib/win32 PCM/session, Mario Win32 adapters and mirrored tests/build wiring;10-16files,700-1200lines estimate. Library device/session and app transaction interfaces change; core and save wire ABI remain stable. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding, source policy and current component map. |
| Verification | S1 owner fault/stall tests, app load/focus/exit joins, both native-width suites and host integration, six local product builds across both apps, ledger/documentation gates. Matrix and platform limits are in the proposal. |
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

## S1 P3 closure checkpoint

S1 implementation and coordinator review are complete. Both widths313/313,
independent library23/23, Mario host15/15 and Mine host3/3 on both widths pass.
Six local products are refreshed; provenance, real-device delay and rerun,
owner tests and retained platform limits are recorded in the proposal.
S2 has not yet been admitted. S1 adds no ROM equivalence credit.
