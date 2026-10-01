# Project Status

## Current Work

## M2 T58 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T58 S5 audit - player size, injury, death and palette chain. |
| Admission And Approval | Owner-approved source-order program; S4 is closed and S5 is admitted. |
| Objective | Audit and repair PlayerChangeSize through ExitDeath against original ROM semantics. |
| Non-goals | No unadmitted movement, audio, renderer or platform semantics beyond declared handoffs. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 554 exact labels and 1,082 exact feasible relations. Scope has 14 labels. |
| Candidate Proposal | docs/proposals/m2/t58-cohort-e-dispatcher-current-proof.md. |
| Files And ABI Surface | Shared player-mode owners and project-owned tests/recorders; platform adapters are consumers only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | Original mode snapshots, x86/x64 C90 caller replays, focused tests, DOS16 link and purity. |
| Expected Markers | Size timers, injury blink, death gates, fire-flower state and palette cycling. |
| Asset Needs | Audit only initially; a shared product repair refreshes all three artifacts. |
| Reporting Requirements | Report every scoped label/relation and both verification tracks before S6. |
| Stop Conditions | Any unresolved source/C difference, route mismatch or platform game logic. |
| Exit Criteria | Scoped labels and feasible relations current-exact. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32. |
| Similar-Issue Sweep | Mode callers, timer decrements, palette state and task transitions. |

## Current Technical Baseline

One shared C90 game implementation serves DOS16 and Win32 x86/x64. T58 S5 is active; S6 is not admitted.
