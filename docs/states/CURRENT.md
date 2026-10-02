# Project Status

## Current Work

## M2 T64 S22 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S22 admitted — enemy direction inversion tail. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S21. |
| Objective | Audit `$E140` `InvEnemyDir` tail jump to `RXSpd`. |
| Non-goals | `RXSpd` remains its separately owned predecessor; no platform adaptation changes. |
| Reference Baseline | Historical 1,992 / 1,992; incoming current exact 1,439 / 1,992 nodes and 3,015 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | src/game/objects.c, project-owned route/oracle harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | Static `InvEnemyDir` audit; controlled original-ROM ordinary-bump route per x86/x64 width; focused bump/jump-hammer and purity tests. |
| Expected Markers | 1 node; `control-02674` tail relation. |
| Asset Needs | Refresh all three artifacts only if shared product C changes. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current totals. |
| Stop Conditions | Any mismatch or missing route blocks closure. |
| Exit Criteria | Every scoped feasible path has an identical shared-C counterpart and original-ROM route evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | Signed X-speed inversion, moving-direction XOR and `RXSpd` tail-call order. |

## Current Technical Baseline

T64 S22 concludes at **1,440 / 1,992** current-exact nodes and **3,016 /
4,324** current-exact feasible controls. Historical conformance remains **1,992 /
1,992**.

`InvEnemyDir` is the ROM tail at `$E140`, an unconditional jump to `RXSpd`.
The shared `mysmb_objects_bump_enemy` ordinary path is its C counterpart: it
negates the byte X speed and XORs moving direction with 3. The controlled
original-ROM ordinary bump route is compared with current x86/x64 output.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,439 / 1,992** nodes and **3,015 / 4,324** feasible
  controls (raw **4,342**, infeasible **18**).
- Scope: **1** label (`InvEnemyDir`); expected historical matches: **0**;
  maximum historical complete **1,992 / 1,992**.

## S22 closure — enemy direction inversion tail

`InvEnemyDir` and its sole feasible relation `control-02674`
(`InvEnemyDir` to `RXSpd`) are current-exact. Static comparison proves the ROM
instruction is an unconditional tail jump and the shared C ordinary-bump path
performs the same two `RXSpd` writes: two's-complement X speed and direction
XOR 3. Controlled ordinary original-ROM entries replay with zero x86/x64
differences in sound, X speed and direction; focused chain, terrain-state and
platform-purity tests pass on both widths. No product C changed and no EXE
refresh is due.

Current totals: historical mapping **1,992 / 1,992**; current exact nodes
**1,440 / 1,992**; current exact feasible controls **3,016 / 4,324** (raw
**4,342**, infeasible **18**); exact material relations **358 / 487**.
