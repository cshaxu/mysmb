# Project Status

## M3 T19 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed: M3 T19 S4 P1 and T19 engineering scope; waiting for owner acceptance/instruction. |
| Admission And Approval | Owner approves a suitable design and repair of Win32/64, Win16 and DOS16 audio based on the audit. Retain T19; admit S4 after reviewed S3 closure. |
| Objective | Qualify all platform audio and six products; repair the integrated DOS presentation-starvation finding through app scheduling only. Owner authorizes autonomous single-person coordinator/executor review through T closure and six-product build/test delivery. |
| Non-goals | No additional production process, host driver/service manipulation, game/APU/PPU rewrite, new audio backend, Mine music feature or save-format change. |
| Reference Baseline | 82d6da42; T45 S4 closed pending owner play acceptance. |
| Candidate Proposal | [T19 audio lifetime](../history/M3-T19-three-platform-audio-lifetime.md). |
| Files And ABI Surface | Mario I/O presentation scheduling and DOS binding, mirrored tests and final receipts;5-8files,150-300lines estimate. Library device/session and app transaction interfaces change; core and save wire ABI remain stable. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding, source policy and current component map. |
| Verification | S3 hardware port/FLAGS/queue/fault/lost IRQ owner tests and actual DOS PCM, both native-width suites and host integration, six local product builds across both apps, ledger/documentation gates. Matrix and platform limits are in the proposal. |
| Expected Markers | Empty ROM scope/expected/actual; historical1992/1992; no new equivalence credit. |
| Asset Needs | Owner local ROM for products only. Owner-provided Windows3.1 installation media supplies its Microsoft Sound Blaster driver solely to an ignored private test image; proprietary, not redistributed or committed. Neutral PCM probes and protected captures remain under build. Microsoft API docs are references only. |
| Reporting Requirements | Distinguish measured normal calls, static defects, unreproduced historical stalls, proposed behavior and outstanding proof. |
| Stop Conditions | No forced thread termination, freed driver-owned buffers, sibling writes, hidden retry loops or unsupported hard-cancellation claims. Only the active S may change product owners. |
| Exit Criteria | S4 closes only after the fixed acceptance register, product runtime and audio evidence pass; T19 closes only after S2 Win16, S3 DOS16 and S4 integration fulfill the fixed findings/acceptance register. Design completion is not repair completion. |
| Original Owner Request | Design and resolve audio problems on all three platforms from the audit conclusions. |
| Similar-Issue Sweep | All host calls, partial cleanup, queues, renderer continuity, reset/load, focus/Tab, teardown, Win16 retry/reentrancy and DOS DMA/IRQ/polling; each finding has a receiving S. |

## Current Technical Baseline

T19 S4 and T19 engineering scope are closed. No active S. Its queue entry is removed; the five other candidates
retain their order. T45 S4 remains closed pending owner visual acceptance;
its local products and pending acceptance materials are preserved.
Historical1992/1992, retained1991/1992nodes and4260/4261feasible controls
(4342raw,81infeasible) remain unchanged; this is not ROM certification.

## Approved execution sequence

S1: shared facts/ownership contract and Win32 asynchronous lifetime/app joins.
S2: Win16 cooperative lifecycle, bounded retries and app/host close/load joins.
S3: DOS16 bounded DSP/IRQ lifecycle, queue publication and fault containment.
S4: integrated product qualification, memory/cost/audio receipts and T closure.
No S is active; do not auto-admit the next queue candidate. Admission of each next S requires predecessor closure,
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

## S4 P1 and T19 closure checkpoint

Both315test suites, independent24tests and Mario15/Mine3host routes per width
pass; all six local products compile and are refreshed. Final DOS and Win3.x
products pass actual lifecycle checks and nonflat audio capture. Current Windows
endpoint is absent (real-device targets77); retain S1normal transport evidence,
current accepting-sink nonflat data and explicit owner listening qualification.
No current physical audio pass is claimed. ROM counters unchanged. The fixed
findings register and caveats are in the archived T19 record. Five queue items
unchanged; wait for owner. Clean this build evidence after owner acceptance.
