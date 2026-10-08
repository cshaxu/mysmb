# Project Status

**Active: M3 T39 S3. DOS16 multi-stage retained-presentation work census.**

## M3 T39 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation of M3 T39 after closed S2 implementation commit `7cd1b4a2`. |
| Admission And Approval | Owner approved the ordered S1–S5 performance sequence and, after S2 analysis, directed continuation. |
| Objective | Measure the selected retained presenter across reproducible title, normal gameplay, transition, dense-sprite, and water/castle routes, then identify the dominant physical work by phase. |
| Scope | Ignored product-root DOS16 fixtures, probe/instrumentation and proposal evidence only. No tracked C product edit is planned. |
| Non-goals | Do not modify shared game/PPU logic, DOS cadence, dimensions, buffer policy, persistent DOSBox configuration or enter S4 before the census result. |
| Reference Baseline | S2’s accepted fixed-HUD writer reduces selections to four per commit and saves 1.88% presenter PIT on its matched route. S1’s normal-game sample has 16,384 fixed-HUD A000 bytes/frame, 12 repair tiles/frame and about 200 plane selections/frame. |
| Candidate Proposal | [Retained presentation performance qualification](../proposals/m3/retained-performance-qualification.md#s3----multi-stage-work-census). |
| Files And ABI Surface | Private copies below ignored `build/m3-t39-s3/`; no public or product-source ABI change. |
| Applicable Rules | Execution, Documentation, Architecture, Coding and source policy. |
| Expected Markers | ROM scope[], expectedMatches[], actualMatches[], new0; historical 1992/1992 unchanged. |
| Asset Needs | Existing owner-local generated runtime input, ROM and temporary DOSBox sessions only. |
| Stop Conditions | A named route that cannot be reached reproducibly is reported as unavailable; it must not be replaced with synthetic data or a product behavior change. |
| Verification | For each route record warm-up/sample frames, operating mode/task, HUD restore/commit bytes, changed background bytes, repair tiles/bytes, OAM tiles, sprite bytes and plane selections. Check counter reset and deterministic route receipt. |
| Exit Criteria | One reproducible census matrix, route limitations and a quantified S4 decision basis. No product executable refresh unless product code changes. |
| ROM scope | `[]`; zero nodes and zero control edges. Historical markers unchanged. |
| Reporting | Report each observed route’s per-frame work, the phase that dominates, missing routes and the resulting candidate/rejection criteria for S4. |
| Reporting Requirements | State route count, frame count, retained-mode status, counter categories, code/artifact status and explicit S4 admission state. |
| Original Owner Request | Improve DOS16 speed through evidence-led work; prioritize HUD batching, then phase census, then sprite repair decision and only then composition buffering. |
| Similar-Issue Sweep | Title, normal game, transition, dense OAM, water/castle retained presentation, HUD, cache, repair and sprite paths. |
## Current Technical Baseline

- The selected DOS product is T38 S18 current-background sprite-union presentation; its 260-frame physical oracle was exact.
- T39 S1 closed as read-only comparative research. It found that the historical source's background cache and per-frame sprite redraw do not justify a core rewrite or suppressed sprites; its flat 32-bit RAM composition is not importable into real-mode DOS16.
- A contained DOS16 test rejected the naive 61,440-byte RAM composition surface: 11.983ms/frame versus 6.971ms/frame for the direct split-A000 control. This is not a ban on all later anti-tearing designs, only on repeating that unmodified layout.
- S2's far-pointer plane-batch candidate was rejected after an actual retained-presenter regression. The accepted replacement keeps raw-slot extraction in its original caller and moves only `vga_retained_plane` outside the 32-row loop. The prior apparent early exits were test-host cleanup of a detached DOSBox process, not candidate crashes. S3–S5 remain planned and are not active.

## Recent Closure Summaries

### T39 S1 -- comparative source and work-census research

S1 remained local-only and changed no product source, artifacts or ROM accounting. Its product-root 60-frame normal-game census found the retained background almost idle (4.3 changed-background A000 bytes/frame), while fixed HUD restore plus commit wrote 16,384 bytes/frame and the HUD commit alone selected VGA planes 128 times/frame. This justifies S2's bounded physical writer change. The full research receipt and opportunity ranking are retained in the [T39 proposal](../proposals/m3/retained-performance-qualification.md).
