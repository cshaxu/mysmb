# Project Status

## M3 T19 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: M3 T19 S3 P1, DOS16 implementation; S2 closed at2c8e2603; S4 planned. |
| Admission And Approval | Owner approves a suitable design and repair of Win32/64, Win16 and DOS16 audio based on the audit. Retain T19; admit S3 after reviewed S2 closure. |
| Objective | Implement bounded DOS DSP/IRQ operations, race-free DMA ownership, latched faults and completion watchdog. Owner authorizes autonomous single-person coordinator/executor review through T closure and six-product build/test delivery. |
| Non-goals | No additional production process, driver/service manipulation, game/APU/PPU rewrite, new audio backend, Mine music feature or save-format change. |
| Reference Baseline | 2c8e2603; T45 S4 closed pending owner play acceptance. |
| Candidate Proposal | [T19 audio lifetime](../proposals/m3/bounded-windows-audio-startup.md). |
| Files And ABI Surface | lib/dos16 PCM hardware and machine seam, Mario DOS adapter, mirrored tests/build wiring;7-11files,350-650lines estimate. Library device/session and app transaction interfaces change; core and save wire ABI remain stable. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding, source policy and current component map. |
| Verification | S3 hardware port/FLAGS/queue/fault/lost IRQ owner tests and actual DOS PCM, both native-width suites and host integration, six local product builds across both apps, ledger/documentation gates. Matrix and platform limits are in the proposal. |
| Expected Markers | Empty ROM scope/expected/actual; historical1992/1992; no new equivalence credit. |
| Asset Needs | Project-owned PCM/probes only, no ROM. Microsoft API documentation is a reference, not imported code. Raw outputs contained under build/t19-s1-audit. |
| Reporting Requirements | Distinguish measured normal calls, static defects, unreproduced historical stalls, proposed behavior and outstanding proof. |
| Stop Conditions | No forced thread termination, freed driver-owned buffers, sibling writes, hidden retry loops or unsupported hard-cancellation claims. Only the active S may change product owners. |
| Exit Criteria | S3 closes only after DOS hardware lifecycle, app joins and tests/products pass; T19 closes only after S2 Win16, S3 DOS16 and S4 integration fulfill the fixed findings/acceptance register. Design completion is not repair completion. |
| Original Owner Request | Design and resolve audio problems on all three platforms from the audit conclusions. |
| Similar-Issue Sweep | All host calls, partial cleanup, queues, renderer continuity, reset/load, focus/Tab, teardown, Win16 retry/reentrancy and DOS DMA/IRQ/polling; each finding has a receiving S. |

## Current Technical Baseline

T19 S3 is active. Its queue entry is removed; the five other candidates
retain their order. T45 S4 remains closed pending owner visual acceptance;
its local products and pending acceptance materials are preserved.
Historical1992/1992, retained1991/1992nodes and4260/4261feasible controls
(4342raw,81infeasible) remain unchanged; this is not ROM certification.

## Approved execution sequence

S1: shared facts/ownership contract and Win32 asynchronous lifetime/app joins.
S2: Win16 cooperative lifecycle, bounded retries and app/host close/load joins.
S3: DOS16 bounded DSP/IRQ lifecycle, queue publication and fault containment.
S4: integrated product qualification, memory/cost/audio receipts and T closure.
S3 audio scope is closed; S4 is next and not yet admitted. Admission of each next S requires predecessor closure,
the before-work brief, its own packet/ledger run and a reviewed scope.

## S1 P3 closure checkpoint

S1 implementation and coordinator review are complete. Both widths313/313,
independent library23/23, Mario host15/15 and Mine host3/3 on both widths pass.
Six local products are refreshed; provenance, real-device delay and rerun,
owner tests and retained platform limits are recorded in the proposal.
S2 is now admitted by coordinator under the autonomous mandate. S1 adds no ROM equivalence credit.

## S2 P1 closure checkpoint

Cooperative Win16 lifecycle and Mario load/close joins pass owner tests,
both313test suites plus final9test subsets, independent23test suite,
and final actual Win3.x Mario/Mine graphical/text/input/save/load/exit routes.
Both MZ/NE products rebuilt; four native Windows products retain S1 provenance.
S3/S4 remain outstanding. No ROM credit; see proposal for retained limits.

## S3 P1 closure checkpoint

DOS audio ownership tests315/315 per width, library24/24 and native PCM route pass.
Final hybrid rebuilt. Integrated presentation starvation reproduces on old EXE
and transfers explicitly to S4; T remains unqualified. See proposal receipt.
