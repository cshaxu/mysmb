# Project Status

## Current Work

## M2 T61 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S4 audit — Cohort H coin and miscellaneous-object lifecycle. |
| Admission And Approval | Owner-approved source-order proof program; S3 is closed and this packet admits S4 only. |
| Objective | Audit and, if required, repair `CoinBlock -> MiscLoopBack` against original-ROM semantics. |
| Non-goals | No score-digit, gravity, relative-position, offscreen, bounding-box, OAM/graphics, hammer-child or platform-adapter semantic claim beyond S4 handoffs. |
| Reference Baseline | Historical 1,992 / 1,992; current 720 / 1,992 exact nodes and 1,429 / 4,324 exact feasible control relations. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | `src/game/coin.c`, `src/game/misc.c` and named shared-game children; platform adapters remain consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 caller routes, focused coin/misc chain fixture, platform purity and DOS16 link. |
| Expected Markers | Twelve labels and their owned internal feasible relations become exact only after both tracks agree. |
| Asset Needs | Audit initially; a shared-game repair refreshes three local EXEs. |
| Reporting Requirements | State every label and boundary disposition, historical 1,992 / 1,992, exact nodes / 1,992 and exact feasible controls / 4,324. |
| Stop Conditions | Any feasible difference remains in S4 until repaired and re-audited. |
| Exit Criteria | All twelve labels and owned feasible relations exact; platform adapters contain no game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Incoming SBC/ASL carry, slot-eight fallback, d7 dispatch, slot restoration after child calls, page carry, state-$30 retirement and descending-loop termination. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T61 S4 is the sole active packet.
