# Project Status

## M3 T46 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T46 S5 closed after review; T46 closed for owner acceptance, no active S or new T. |
| Admission And Approval | Owner accepts existing no-D evidence and directs cancellation of D and deletion of its code. |
| Objective | Remove D and exclusive full-screen path; route product through existing RAM bands, A/B required and C optional. |
| Non-goals | No core/PPU semantics, caching policy, emulator setting or20ms guarantee. |
| Reference Baseline | 88cc72cf; retained S3/S4 exact pixel/performance receipts and accepted products. |
| Candidate Proposal | [S5 D removal](../history/M3-T46-dos16-ram-presenter-memory-tiers.md#s5-owner-directed-d-removal). |
| Files And ABI Surface | DOS root/main/devices/compositor deletion, build references and owner tests/tools. Estimated8-12files, mostly deletions. |
| Applicable Rules | Task Reading Set, C90 and segmented ABI, source policy, continuable tests, build-only generated outputs. |
| Verification | Reuse existing no-D pixel/performance evidence; changed allocation/band-dispatch checks, native suites, optimized DOS/hybrid builds and three current local products; no repeated matrix. |
| Expected Markers | Empty scope/expected/actual; new ROM node/edge credit0. |
| Asset Needs | Owner-local ROM for existing build/route only, no import/publication. Raw new-output budget2MiB under active ignored build workspace,180seconds per run; cleanup on acceptance. |
| Reporting Requirements | Deleted D surfaces and references; actual allocation/workspace/loader totals, affected test/build results and three artifacts; no invented speed claim. |
| Stop Conditions | Pixel/RAM mismatch, segment overrun, register/stack corruption, new resident cache, emulator setting change, or unexplained test failure. |
| Exit Criteria | No D allocation/API/compositor/build references; product uses RAM bands, AB required/C optional; checks pass and three current local artifacts. |
| Original Owner Request | Cancel D directly using already accepted evidence and clean its code; no repeated cache matrix. |
| Similar-Issue Sweep | D allocation/binds/free/publish/helpers/builds/tests/tools and stale queued full-screen-copy plan; direct-VGA/retained bypass excluded. |

## Current Technical Baseline

T46 S5 closes owner-directed D removal. No active work. Three candidates retain
order; the D-only full-screen-copy candidate is withdrawn. Product uses ordinary
16-row RAM bands; A/B required,C optional. D allocation/API/compositor/build
path is gone. Existing S4 ABC24.285ms calibrated/26.914ms raw route evidence is
retained, not repeated or claimed as new product FPS. The20ms target remains
unmet. Historical1992/1992,retained1991/1992nodes and4260/4261feasible controls
(raw4342,infeasible81) unchanged; no whole-game certificate.

## S5 closure checkpoint

Seven real product allocation/failure/cleanup cases pass. Successful frames
read15ordinary RAM bands; no retained/direct-VGA bypass. Native x86/x64 each
316/316 plus final focused4/4 pass. Optimized184object DOS product/hybrid and
both Windows products build; all three local Mario EXEs refreshed. No new
matrix/ROM trace. Cache payload70KiB required/130KiB with C. Known conventional
memory subtotal ABC541.105KiB/AB481.105KiB, plus rounding/allocator/environment
overhead; not a production live census. Saved63008bytes versus prior ABCD.
[Closure detail](../history/M3-T46-dos16-ram-presenter-memory-tiers.md#s5-p1-closure-d-removed-ram-bands-selected).
