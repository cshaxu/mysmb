# Project Status

## M3 T19 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Closed: M3 T19 S5 P1; owner-directed correction complete, waiting for acceptance. |
| Admission And Approval | Owner requests Mine Win16 duplicate-menu repair and explicitly authorizes T19 S5. Single-person executor/coordinator review. |
| Objective | Hide the native menu in Mine Win16 text view, restore it in graphics, preserve geometry, input and menu lifetime. |
| Non-goals | No game, audio, DOS, Win32 policy or ROM changes. |
| Reference Baseline | 6fe73028, clean worktree. |
| Candidate Proposal | [T19 retained record and S5 amendment](../history/M3-T19-three-platform-audio-lifetime.md#s5-owner-directed-menu-correction). |
| Files And ABI Surface | Mine Win16 root and generic Win16 host menu mechanism, mirrored tests; estimated 3-6 source/test files, 80-160 lines. No application struct ABI change. |
| Applicable Rules | Task Reading Set: Execution, Documentation, Architecture, Coding, source policy and current component map. |
| Verification | Owner-local host menu lifecycle tests, native suites, original small/large-model Win16 builds, actual Win3.x graphics/text/graphics and close-in-text routes. |
| Expected Markers | Empty scope/expected/actual; historical1992/1992; no ROM equivalence credit. |
| Asset Needs | Existing owner-local Win3.x test image and Mario ROM build input only; protected products/captures remain ignored beneath build and local assets. |
| Reporting Requirements | Before/after menu behavior, geometry, test counts, product provenance, diff size and retained limitations. |
| Stop Conditions | No global desktop control, sibling writes, system settings changes or app-specific policy in lib. |
| Exit Criteria | One menu in either view, repeated switches and text-mode close safe, applicable tests/builds pass, products refreshed and reviewed commit pushed. |
| Original Owner Request | Reopen T19, add an S to remove duplicated native menu when Mine enters character view. |
| Similar-Issue Sweep | Menu attachment, detached ownership, restore flags and menu-dependent client sizing across Win16 clients; Win32 and DOS reviewed for analogous double menus. |

## Current Technical Baseline

T19 S1-S5 engineering scope is closed, pending owner acceptance. No active S. Its queue entry is removed; the five other candidates
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

## S5 P1 closure checkpoint

Mine Win16 hides its native menu in text view and restores the same menu in
graphics; sizing uses the actual attachment. The host retains detached ownership
through close. Both315test suites and independent24tests pass. Actual Win3.x
single-menu/return/repeat/text-exit and Mario regression routes pass; both hybrid
products rebuilt and locally refreshed. No audio/game/ROM change or new
certification credit. Wait for owner acceptance before build cleanup.
