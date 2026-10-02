# Project Status

## Current Work

## M2 T64 S23 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S23 admitted — player/enemy horizontal difference. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S22. |
| Objective | Audit `$E143-$E14A` `PlayerEnemyDiff`. |
| Non-goals | Its individual caller return edges remain in their caller-chain audits; no platform adaptation changes. |
| Reference Baseline | Historical 1,992 / 1,992; incoming current exact 1,440 / 1,992 nodes and 3,016 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | src/game/enemy/distance.c, project-owned route/oracle harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | Static `$E143-$E14A` audit; controlled original-ROM low-byte borrow/no-borrow entries per x86/x64 width; focused distance-chain and purity tests. |
| Expected Markers | 1 node; source-owned write and return contract recorded by the graph audit. |
| Asset Needs | Refresh all three artifacts only if shared product C changes. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current totals. |
| Stop Conditions | Any mismatch or missing route blocks closure. |
| Exit Criteria | `$00` low subtraction and page return preserve original borrow semantics on every scoped route. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | Byte subtraction wrapping, low-byte borrow propagation, scratch `$00` ownership and caller-visible A result. |

## Current Technical Baseline

T64 S23 is admitted at **1,440 / 1,992** current-exact nodes and **3,016 /
4,324** current-exact feasible controls. Historical conformance remains **1,992 /
1,992**.

`PlayerEnemyDiff` is a compact cross-page arithmetic primitive. It subtracts
the player X byte from the enemy X byte into `$00`, preserves that subtraction's
borrow, then returns enemy page minus player page minus the preserved borrow.
The shared owner is `src/game/enemy/distance.c:mysmb_enemy_player_difference`.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,440 / 1,992** nodes and **3,016 / 4,324** feasible
  controls (raw **4,342**, infeasible **18**).
- Scope: **1** label (`PlayerEnemyDiff`); expected historical matches: **0**;
  maximum historical complete **1,992 / 1,992**.

## S23 closure — player/enemy horizontal difference

`PlayerEnemyDiff` is current-exact. The original low-byte subtraction writes
`$00`, and its borrow is consumed by the page subtraction returned in A; the
shared C owner preserves this exact sequence. Four direct original-ROM cases
cover borrow, no-borrow and page wrapping. x86/x64 checks have zero differences
in A and `$00`; focused chain, terrain-state and platform-purity tests pass.
No product C changed and no EXE refresh is due.

Current totals: historical mapping **1,992 / 1,992**; current exact nodes
**1,441 / 1,992**; current exact feasible controls **3,016 / 4,324** (raw
**4,342**, infeasible **18**); exact material relations **358 / 487**.
