# Project Status

## Current Work

## M2 T62 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T62 S1 audit — Cohort I enemy flag, loop and frenzy-handoff chain. |
| Admission And Approval | Continuing owner-approved M2 source-order proof program after closed T61; this packet admits S1 only. |
| Objective | Audit and repair `EnemiesAndLoopsCore -> ChkEnemyFrenzy` against original-ROM semantics. |
| Non-goals | Stream parsing, initialization, actor behavior, rendering, and platform gameplay are outside S1. |
| Reference Baseline | Historical 1,992 / 1,992; current 834 / 1,992 nodes and 1,615 / 4,324 feasible controls. |
| Candidate Proposal | docs/proposals/m2/t62-cohort-i-enemy-stream-current-proof.md. |
| Files And ABI Surface | Shared `src/game/enemy/core.c` and `loop.c`; `stream.c`, initializer and actor paths are named child boundaries. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 loop routes, focused C90 loop checks, purity and DOS16 link. |
| Expected Markers | 16 nodes, 27 internal feasible controls and 3 internal material handoffs. |
| Asset Needs | Owner-supplied local `smb1.nes` and derived recorder data stay under ignored build paths; a shared-game repair refreshes three local EXEs. |
| Reporting Requirements | Report historical 1,992 / 1,992, exact nodes / 1,992, exact feasible controls / 4,324, raw 4,342 and infeasible 18. |
| Stop Conditions | Any feasible difference remains in S1 until repaired and re-audited. |
| Exit Criteria | Closed: all 16 nodes, 27 feasible internal controls and 3 material handoffs are exact; platform code has no enemy-loop rule. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | All high-bit slot references, loop-table consumers, page/cursor rewinds, kill-all callers and frenzy activation paths. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; T62 S1 is closed pending S2 admission.

## T61 Closure

T61 Cohort H closed ten source-order chains from `VineObjectHandler` through
`ExVMove`. Historical migration remains **1,992 / 1,992**; current exact
registry is **818 / 1,992** nodes and **1,588 / 4,324** feasible controls
(raw **4,342**, infeasible **18**). No product source changed in S10.

## T62 S1 Closure

`EnemiesAndLoopsCore -> ChkEnemyFrenzy` is current-exact: 16 nodes, 27 feasible internal controls and three material handoffs passed `$C047-$C0C3` static comparison, 96 controlled original-ROM/current x86/x64 routes per width, focused C90 loop checks, platform purity and DOS16 link. Historical migration remains **1,992 / 1,992**; current registry is **834 / 1,992** exact nodes and **1,615 / 4,324** exact feasible controls (raw **4,342**, infeasible **18**). No product source changed.
