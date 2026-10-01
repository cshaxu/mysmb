# Project Status

## Current Work

## M2 T61 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S5 audit — Cohort H score, coin tally and status-number chain. |
| Admission And Approval | Owner-approved source-order proof program; S4 is closed and this packet admits S5 only. |
| Objective | Audit and, if required, repair `CoinTallyOffsets -> NoZSup` against original-ROM semantics. |
| Non-goals | No digit-math or status-print child semantic claim beyond S5 handoffs, and no platform-adapter logic. |
| Reference Baseline | Historical 1,992 / 1,992; current 732 / 1,992 exact nodes and 1,448 / 4,324 exact feasible control relations. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | `src/game/score.c` and named shared game/status children; platform adapters remain consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 caller and full-product routes, focused score/HUD smoke, platform purity and DOS16 link. |
| Expected Markers | Nine scoped labels; eight current-exact candidates, with AddToScore revalidated as the in-chain exact handoff. |
| Asset Needs | Audit initially; a shared-game repair refreshes three local EXEs. |
| Reporting Requirements | State every label and boundary disposition, historical 1,992 / 1,992, exact nodes / 1,992 and exact feasible controls / 4,324. |
| Stop Conditions | Any feasible difference remains in S5 until repaired and re-audited. |
| Exit Criteria | All nine labels and owned internal feasible relations exact; platform adapters contain no game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Table indices, current-player selection, 100-coin threshold, sound/life writes, digit modifier, VRAM offset arithmetic, zero suppression and ObjectOffset return. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T61 S5 is the sole active packet.
