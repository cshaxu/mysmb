# Project Status

## Current Work

## M2 T52 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T52 S5 — B3 time-up task-handoff remediation. |
| Admission And Approval | Owner-directed continuation of T52 after closed S4. |
| Objective | Audit the complete `DisplayTimeUp -> OutputInter -> ResetScreenTimer` task handoff against the admitted ROM. |
| Non-goals | No platform-owned screen logic, no redesign of `ResetSpritesAndScreenTimer`, and no historical-credit increase. |
| Reference Baseline | 1,992 / 1,992 historical; three received historical-complete labels, expected delta zero. |
| Candidate Proposal | docs/proposals/m2/t52-current-audit-mismatch-remediation.md. |
| Files And ABI Surface | Shared src/game/game.c; focused screen-status test plus validation-only local/reference recorder fixtures. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Controlled ROM ScreenRoutines task-4 route with an expired frame and its next cleared-flag invocation, plus task-5/task-7 reset controls; focused test; x86/x64/DOS16 and purity. |
| Expected Markers | The expired visit clears `$0759`, writes Time Up, resets `$07a0` and `$0774`, and reaches task 5 through `ResetScreenTimer`'s source increment. |
| Asset Needs | Owner-local ROM and ignored local three-EXE outputs. |
| Reporting Requirements | Three labels, control-00225, both verification tracks and unchanged numerator. |
| Stop Conditions | Any task-5/task-7 reset behavior or platform source changes outside the received chain. |
| Exit Criteria | `DisplayTimeUp` and control-00225 are current-equivalence exact; `OutputInter` and `NoTimeUp` have route and source-context evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | All shared screen-routine cases that pass through `OutputInter` or wait in task 5/task 7. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64. Platform adapters do not own game logic.
