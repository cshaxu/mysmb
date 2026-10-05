# M3 T25: DOS16 frame-rate root-cause measurement

The owner reports that the actual DOSBox game is too slow to play. Prior startup,
input and exit probes establish operation, not frame throughput. This task is
**diagnosis only**: measure the existing DOS16 product and identify the dominant
cause with reproducible evidence. It does not edit product code, package a new
EXE or claim a performance repair. [The repair candidate](../proposals/m3/dos16-performance-repair.md)
retains follow-up implementation and acceptance.

## Planned S1 scope and estimate

ROM-node scope `[]` (0 labels), expected new matches `[]` (0), incoming
historical mapping 1992/1992, maximum 1992/1992. This is host performance
measurement with no ROM equivalence or final-certificate credit.

Measure the same resource-bound DOS16 binary/workload at DOSBox's installed
default `core=auto`, `cycles=auto` and explicit `core=dynamic`, `cycles=max`.
Record logical frames per wall second, startup/Start delays and gameplay-stage
costs: game tick, 256x240 PPU, 320x200 scale, VGA transfer, snapshot, wait.
Use a locally instrumented copy under ignored `build/m3-t25-s1/` if necessary;
measure tap overhead and distinguish emulated CPU time from physical 486SX.
Keep ROM-derived binaries and raw captures local; retain neutral timing totals.

## Read-only pre-admission measurement, 2026-10-05

M3 T24 S4 became active during this investigation, so the diagnosis remains
unnumbered in the queue. The following measurements used ignored local copies
only. They are preliminary evidence for admission/closure review, not an
assertion that a second S was active.

DOSBox 0.74-3, `machine=svga_s3`, `output=surface`, no sound, and one scripted
snapshot-load/movement/exit route were held constant. The two CPU settings
were `core=auto;cycles=auto` (matching the installed default) and
`core=dynamic;cycles=max`. The ROM-derived input EXE had SHA-256
`8BBEBD05F17C499BBC08C9287D462E78999E3D3CB7276991D9317567FF92897C`.
Each pair of runs used byte-identical measurement EXEs; only the CPU settings
changed. The saved gameplay state stayed local under `build/`.

| CPU setting | Minimal-counter frames / wall time | Instrumented frames / running frames / wall time | PPU background | VGA scale | VGA transfer | Game tick | Snapshot | Wait |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| auto/auto | 11 / 26.69 s | 12 / 8 / 26.80 s | 1599.1 ms | 139.2 ms | 10.85 ms | 9.45 ms | 30.45 ms | 1.58 ms |
| dynamic/max | 1145 / 26.49 s | 1303 / 1093 / 26.50 s | 16.117 ms | 1.458 ms | 0.119 ms | 0.101 ms | 0.268 ms | 0.528 ms |

Stage values are mean guest PIT time per stage call. Full PPU means were
1615.4 and 16.304 ms; the background path alone consumed 67.0% and 87.9%
of measured root-step time. Sprite means were 15.924 and 0.174 ms. Root-step
means were 1789.5 and 18.298 ms. The 60 Hz budget is 16.667 ms: at
`dynamic/max` the background pass alone nearly exhausts it. At `auto/auto`
the background pass is about 96 times that budget. The PIT wait is negligible,
so the game is compute-limited, not paused by pacing. The shared game tick,
snapshot and device transfer are not the dominant cost. This diagnosis names
`mysmb_ppu_background_row` in `src/game/ppu_frame.c` as the bounded follow-up
owner. Its 240-row/256-pixel software background pass, far-buffer writes, and
OpenNT16 `/AL /Gs` build are the code path to investigate. The measurements
establish the routine and CPU configuration as causes; they do not yet isolate
one machine instruction or prove a particular optimization will be safe.

A 100-pair PIT timestamp check cost 0.087 ms per pair at auto/auto and 0.006 ms
at dynamic/max. The counter-only runs, which contain no per-stage timestamps,
remained very slow and show no evidence that instrumentation created the
bottleneck. `cycles=max` is host-load dependent, so its absolute frame count
varies; no physical 486SX result is claimed. The unseeded title/Start route
separately showed 34 frames and no gameplay entry under auto/auto versus 1151
frames with 740 gameplay frames under dynamic/max; the held-load seeded route
above avoids interpreting a missed brief Start press as a game hang.

Reproduction materials and raw logs are confined to ignored
`build/m3-t25-s1/`. The diagnostic source mirror adds timing/counter calls and
an exit-time summary only; tracked `src/` and packaged EXEs were not changed.

## Acceptance

Review the measured routine, CPU-setting effect and instrumentation control;
then publish a closure record when this candidate can be admitted under the
single-active-S rule. No source optimization or semantics change belongs to
this diagnosis task.


## S1 admission

Owner directs closure of T24 and admission of the next queued T. T24 S1-S4
are closed. M3 T25 S1 P1 is now the sole active task,diagnosis only.
Review the preliminary measurements above against retained local receipts,
source mirror and input identities before accepting their conclusions.
Estimate:zero product-source lines;approximately60-120 governance lines.
One S covers measurement validation,dominant-path diagnosis and a bounded
repair handoff. Existing preliminary numbers are not an admitted closure.

Scope/expected/actual new ROM labels are empty;historical1992/1992,local
nodes1991/1992,feasible controls4260/4261(raw4342,infeasible81) remain unchanged.
Exit requires reproducible same-binary/workload comparisons,instrumentation
overhead controls,stage attribution and explicit emulator/hardware limits.
No optimization,product refresh or physical486SX acceptance in this T.
