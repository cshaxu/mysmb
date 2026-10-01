# Project Status

## Current Work

## M2 T52 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T52 S4 — B2 background-to-player palette fall-through remediation. |
| Admission And Approval | Owner-directed continuation of T52 after closed S3. |
| Objective | Restore the source `GetBackgroundColor -> NoBGColor -> GetPlayerColors` fall-through for all background controls. |
| Non-goals | No platform-owned palette logic and no historical-credit increase. |
| Reference Baseline | 1,992 / 1,992 historical; three received historical-complete labels, expected delta zero. |
| Candidate Proposal | docs/proposals/m2/t52-current-audit-mismatch-remediation.md. |
| Files And ABI Surface | Shared src/game/game.c and src/game/area.c; focused tests plus validation-only local/reference recorder fixtures. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Controlled ROM ScreenRoutines task-10 route with background controls 4-7; focused palette command test; x86/x64/DOS16 and purity. |
| Expected Markers | Screen task increments to 11 and the `$3f10`, length-four player palette command is emitted for both zero and nonzero background controls. |
| Asset Needs | Owner-local ROM and ignored local three-EXE outputs. |
| Reporting Requirements | Three labels, controls 00204-00206, both verification tracks and unchanged numerator. |
| Stop Conditions | Any screen task, VRAM command or palette mutation outside the received chain. |
| Exit Criteria | All three labels and source fall-through controls are current-equivalence exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | All shared screen-routine branches that emit a VRAM-address control and fall through to a palette producer. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64. Platform adapters do not own game logic.
