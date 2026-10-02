# Project Status

## Current Work

## M2 T64 S24 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S24 admitted — enemy landing alignment. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S23. |
| Objective | Audit `$E14F-$E155` `EnemyLanding`. |
| Non-goals | Caller return edges remain in their caller-chain audits; no platform adaptation changes. |
| Reference Baseline | Historical 1,992 / 1,992; incoming current exact 1,441 / 1,992 nodes and 3,016 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | src/game/world/collision.c, project-owned route/oracle harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | Static `$E14F-$E155` audit; controlled original-ROM landing entries per x86/x64 width; focused landing-chain and purity tests. |
| Expected Markers | 1 node; `control-02675` InitVStf call relation. |
| Asset Needs | Refresh all three artifacts only if shared product C changes. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current totals. |
| Stop Conditions | Any mismatch or missing route blocks closure. |
| Exit Criteria | `InitVStf` writes plus high-nibble Y alignment match every scoped route. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | Vertical speed/force initialization, preserved fractional state and Y-nibble alignment. |

## Current Technical Baseline

T64 S24 is admitted at **1,441 / 1,992** current-exact nodes and **3,016 /
4,324** current-exact feasible controls. Historical conformance remains **1,992 /
1,992**.

`EnemyLanding` calls `InitVStf` to clear vertical speed and force, then aligns
`Enemy_Y_Position` to its high nibble plus bit 3. The shared owner is
`src/game/world/collision.c:mysmb_world_land_enemy`.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,441 / 1,992** nodes and **3,016 / 4,324** feasible
  controls (raw **4,342**, infeasible **18**).
- Scope: **1** label (`EnemyLanding`); expected historical matches: **0**;
  maximum historical complete **1,992 / 1,992**.

## S24 closure — EnemyLanding

EnemyLanding and control-02675 are current-exact. Two direct original-ROM entries verify InitVStf's speed/force writes and Y high-nibble-plus-8 alignment on x86/x64 with zero differences. Focused chain, terrain-state and platform-purity tests pass. No product C changed and no EXE refresh is due.

Current totals: historical **1,992 / 1,992**; current exact nodes **1,442 / 1,992**; current exact feasible controls **3,017 / 4,324** (raw **4,342**, infeasible **18**).
