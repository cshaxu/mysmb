# Project Status

## M3 T46 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M3 T46 S3 closed after review; T46 closed for owner acceptance. No new T allocated, no active S. |
| Admission And Approval | Owner explicitly requests the discovered full-span acceleration repair and ABCD total memory account. |
| Objective | Remove DOS callback16-row limit for valid spans; measure exact output, cost and memory before/after. |
| Non-goals | No core/PPU semantics, caching policy, emulator setting or20ms guarantee. |
| Reference Baseline | 736020ea; optimized original DOS objects and accepted neutral T46 timing receipts. |
| Candidate Proposal | [S3 full-span copy repair](../history/M3-T46-dos16-ram-presenter-memory-tiers.md#owner-directed-reopening-s3-full-span-copy-repair). |
| Files And ABI Surface | DOS slot copier only; original signature/owner unchanged. Estimated1product file/under10lines,4-6test/tool files/200-300lines. |
| Applicable Rules | Task Reading Set, C90 and segmented ABI, source policy, continuable tests, build-only generated outputs. |
| Verification | Actual DOS assembly boundary probe; ABC/ABD/ABCD three-repeat exact VGA/palette/RAM old/new comparison; full native suites, original DOS optimized link, three local products and governance. |
| Expected Markers | Empty scope/expected/actual; new ROM node/edge credit0. |
| Asset Needs | Owner-local ROM for existing build/route only, no import/publication. Raw budget48MiB under active ignored build workspace,180seconds per run; cleanup on acceptance. |
| Reporting Requirements | Before/after phase costs and clock sensitivity; actual memory categories and overhead; all tests/artifacts, residual20ms gap and ROM counts. |
| Stop Conditions | Pixel/RAM mismatch, segment overrun, register/stack corruption, new resident cache, emulator setting change, or unexplained test failure. |
| Exit Criteria | Full-height contiguous/split copies exact; invalid parameters rejected; old/new timing improves with unchanged pixels/cache size; all applicable tests and three local artifacts ready. |
| Original Owner Request | Fix discovered bottleneck; assess remaining under20ms target and ABCD plus program conventional memory. |
| Similar-Issue Sweep | All callback binds/row caps,240*64DWORD count, far span/odd-width bounds, count-sum overflow and fallback behavior. |

## Current Technical Baseline

T46 S1/S2 are accepted; T46 and S3 are closed for owner acceptance; no active implementation work. Four queue candidates
retain order. ABD required/C optional. T46 measured ABD61.265ms versus
ABCD41.370ms/gameplay rendering, excluding tick/audio/waits. Long groups rejected
by the16-row DOS callback trigger a slower exact fallback. The valid240-row callback repair is qualified by actual DOS copy and matched-frame receipts. Historical1992/1992,retained1991/1992nodes and4260/4261feasible
controls(raw4342,infeasible81) unchanged; no whole-game certificate.

## S roadmap

S3 closed: actual-DOS boundary regression, minimal copy repair, matched timings,
space accounting, native/DOS validation and three local products, then review.

## S3 closure checkpoint

ABCD gameplay rendering41.370to25.746ms,saving15.624ms/about37.8%;20ms still not
met. ABC control24.265to24.285ms; ABD61.265ms unchanged. Actual DOS36copy cases,
nine invalid cases and optional source pass;18old/new launches/288frame records
have exact VGA/palette/original-RAM equality. Native x86/x64 each317/317; both
private-desktop host joins15/15 pass. All three local Mario EXEs refreshed,
Win16 NE payload unchanged. Memory: caches190KiB, known loaded/runtime/DMA/PSP
subtotal602.637KiB plus rounding/allocator/environment overhead; roughly603KiB
plus headroom. Cache policy unchanged, loader+16bytes, no new ROM credit.
[Full S3 results](../history/M3-T46-dos16-ram-presenter-memory-tiers.md#s3-p1-closure-full-height-acceleration-and-space-account).
