# Project Status

## M3 T47 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation M3 T47 S3; S3 closed for owner acceptance; T47 remains open. |
| Admission And Approval | Owner explicitly requests pure8086 build/run performance benchmark; single-person executor/coordinator. |
| Objective | Measure isolated8086 ISA fallback versus current386-accelerated DOS, same routes/cache/cycle budget. |
| Non-goals | No product source/EXE replacement, core semantic change, cache policy change, Win16 rollout, max test or real8088 timing claim. |
| Reference Baseline | dca5db47; current four delivered products retained; existing original DOS objects and compiler/runtime. |
| Candidate Proposal | [S3 admission](../proposals/m3/nesticle-forensic-performance-audit.md#s3-admission---isolated-8086-instruction-cost-benchmark). |
| Files And ABI Surface | Neutral benchmark preparation/audit tooling and evidence; private copied source/harness; no product ABI changes. |
| Applicable Rules | Task Reading Set, source policy, bounded local artifacts, ISA/output equivalence and continuable builds/tests. |
| Verification | G0 compiler and adapter/CRT code audit; same-input AB/ABC title/game RAM/palette/full-output comparison and stage timers; instruction compatibility limits explicit. |
| Expected Markers | Historical1992/1992;scope=[],expectedMatches=[],actualMatches=[],maximum1992; retained1991/1992nodes,4260/4261controls unchanged. |
| Asset Needs | Owner-local ROM, current local EXEs/objects and original compiler/runtime; generated source/binary/log below ignored build only; no redistribution. |
| Reporting Requirements | Measured median/range stage and total cost, ratios, code/memory size, cache conditions, output hashes, ISA proof limits; do not extrapolate to actual8088. |
| Stop Conditions | Output mismatch, unexplained post8086 code, memory violation, two identical probe failures; no global emulator setting changes. |
| Exit Criteria | Met: reproducible bounded current/i86 benchmark, output agreement and explicit ISA/runtime evidence or named remaining blocker. |
| Original Owner Request | Compile/run pure8086 ISA and benchmark how much performance changes. |
| Similar-Issue Sweep | Inline raw opcodes, compiler defaults/all objects, CRT code, segment copy word/tail counts, cache-dependent paths, startup and timing overhead. |


## Current Technical Baseline

Formal products remain dca5db47: pure DOS16c, DOS/Win16 hybrid16w and32/64,
with S2 normal per-tick publication and opt-in turbo. Only the isolated build
uses8086 replacements. S3 below records finite same-budget comparisons, not
a product ISA downgrade or actual8088 qualification. Historical1992/1992,
retained1991/1992nodes and4260/4261feasible controls remain unchanged.

## S3 Closure

Isolated /G0 candidate and timed probe pass CODE/CRT scanning with zero newer
ISA candidates after proven switch-data exclusions. Three repeated AB/ABC
comparisons retain identical RAM/palette/full VGA output (192measured samples).
ABC gameplay raw instrumented frame40.030to50.282ms(+25.61%); AB74.909to
103.971ms(+38.80%). Calibrated game tick remains9.05ms; composition and VGA
word copying explain the increase. Uninstrumented ready-title process28.202to
21.251images/s, average35.459to47.057ms(+32.71%). No actual8088 hardware or
Win16-window speed claim. Pure MZ/loader448bytes smaller, no added cache.
Two ISA tool unit tests pass. All product source and four published EXEs
remain unchanged. Detailed finite evidence and reproduction are in the
proposal. S3 closed, T47 open; S4-S6 not admitted. ROM counts unchanged.
