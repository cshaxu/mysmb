# Project Status

## Current Work

## M2 T52 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T52 S3 — A7 floatey-number score timer-order remediation. |
| Admission And Approval | Owner-directed continuation of T52 after closed S2. |
| Objective | Restore the original timer write, score-table and AddToScore order. |
| Non-goals | No platform-owned score logic and no historical-credit increase. |
| Reference Baseline | 1,992 / 1,992 historical; four received historical-complete labels, expected delta zero. |
| Candidate Proposal | docs/proposals/m2/t52-current-audit-mismatch-remediation.md#t52-s3-admission-a7-floatey-number-score-timer-order. |
| Files And ABI Surface | Shared src/game/objects.c and focused tests only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Controlled ROM timer-$2b and non-award floatey routes; focused C ordering test; x86/x64/DOS16 and purity. |
| Expected Markers | Timer is RAM $2a before score mutation; score still awards only from pre-decrement $2b. |
| Asset Needs | Owner-local ROM and ignored local three-EXE outputs. |
| Reporting Requirements | Four labels, four control edges, one material edge, both verification tracks and unchanged numerator. |
| Stop Conditions | Any score, life, sound or OAM change outside the received chain. |
| Exit Criteria | All four labels, four controls and ScoreUpdateData handoff are current-equivalence exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | All timer decrement-plus-branch chains in shared game code. |

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64. Platform adapters do not own game logic.
