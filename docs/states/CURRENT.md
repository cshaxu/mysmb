# Project Status

## Current Work

## M2 T61 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T61 S6 audit — Cohort H power-up initialization and lifecycle chain. |
| Admission And Approval | Owner-approved source-order proof program; S5 is closed and this packet admits S6 only. |
| Objective | Audit and, if required, repair `SetupPowerUp -> ExitPUp` against original-ROM semantics. |
| Non-goals | No movement, terrain-collision, relative-position, offscreen, bounding-box, OAM or player-collision child semantic claim beyond named S6 handoffs; no platform-adapter logic. |
| Reference Baseline | Historical 1,992 / 1,992; current 740 / 1,992 exact nodes and 1,455 / 4,324 exact feasible control relations. |
| Candidate Proposal | docs/proposals/m2/t61-cohort-h-blocks-items-current-proof.md. |
| Files And ABI Surface | `src/game/power_up_init.c`, `src/game/power_up.c`, and named shared children; platform adapters remain consumers. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original-ROM/current x86/x64 caller and full-product routes, focused power-up smoke, platform purity and DOS16 link. |
| Expected Markers | Ten scoped labels, all current-exact candidates; 19 owned internal feasible control relations. |
| Asset Needs | Audit initially; a shared-game repair refreshes three local EXEs. |
| Reporting Requirements | State every label and boundary disposition, historical 1,992 / 1,992, exact nodes / 1,992 and exact feasible controls / 4,324. |
| Stop Conditions | Any feasible difference remains in S6 until repaired and re-audited. |
| Exit Criteria | All ten labels and owned internal feasible relations exact; platform adapters contain no game logic. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Fixed-slot usage; power-up type, player-status and frame gates; state transitions; byte-width/carry behavior; child order; all type branches and offscreen/collision handoffs. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic. T61 S6 is the sole active packet.

## T61 S5 Closure

Eight newly exact score/tally nodes and seven internal edges; 112 x86/x64 caller and full-product routes passed; no source changed.
