# Project Status

## Current Work

## M2 T64 S25 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T64 S25 admitted — jumping enemy terrain chain. |
| Admission And Approval | Owner-approved T64 source-order continuation after closed S24. |
| Objective | Audit `$E15B-$E182` `SubtEnemyYPos -> EnemyJump -> DoSide`. |
| Non-goals | Child bodies `ChkUnderEnemy`, `ChkForNonSolids`, `EnemyLanding`, and `DoEnemySideCheck` retain their own proof; no platform adaptation changes. |
| Reference Baseline | Historical 1,992 / 1,992; incoming current exact 1,442 / 1,992 nodes and 3,017 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t64-cohort-j-terrain-collision-current-proof.md. |
| Files And ABI Surface | src/game/enemy/jump_terrain.c, project-owned route/oracle harnesses. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation governance and source policy. |
| Verification | Static `$E15B-$E182` audit; controlled original-ROM chain entries per x86/x64 width; focused terrain-chain and purity tests. |
| Expected Markers | 3 nodes; `control-02676` through `control-02685`. |
| Asset Needs | Refresh all three artifacts only if shared product C changes. |
| Reporting Requirements | Exact labels and relation dispositions plus historical/current totals. |
| Stop Conditions | Any mismatch or missing route blocks closure. |
| Exit Criteria | Wrapped Y compare, speed gate, ordered terrain calls, landing speed write, and unconditional side tail match every scoped route. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16, Win32 x86 and Win32 x64. |
| Similar-Issue Sweep | Eight-bit arithmetic, branch carry semantics, child call ordering and post-landing side-probe tail. |

## Current Technical Baseline

T64 S25 is admitted at **1,442 / 1,992** current-exact nodes and **3,017 /
4,324** current-exact feasible controls. Historical conformance remains **1,992 /
1,992**.

The chain adds `$3e` in eight-bit arithmetic, branches on the resulting carry,
checks falling speed and terrain children in source order, writes `$fd` after a
successful landing, and always tails into the separately owned side check.

- Historical mapping: **1,992 / 1,992**.
- Incoming current exact: **1,442 / 1,992** nodes and **3,017 / 4,324** feasible controls (raw **4,342**, infeasible **18**).
- Scope: **3** labels (`SubtEnemyYPos`, `EnemyJump`, `DoSide`); expected historical matches: **0**; maximum historical complete **1,992 / 1,992**.
## S25 closure — jumping enemy terrain chain

S25 is current-exact: `SubtEnemyYPos`, `EnemyJump` and `DoSide` each have static ROM/C control, state and call-order evidence plus four direct original-ROM `$E163` routes replayed by x86/x64 current owners. The named controls `control-02676` through `control-02685` are exact. No product C changed and no executable refresh is due.

Current totals: historical **1,992 / 1,992**; current exact nodes **1,445 / 1,992**; current exact feasible controls **3,027 / 4,324** (raw **4,342**, infeasible **18**).
