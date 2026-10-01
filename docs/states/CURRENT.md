# Project Status

## Current Work

## M2 T53 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T53 S3 — Cohort A `ScreenOff` corrective re-audit. |
| Admission And Approval | Owner-directed continuation under the approved source-order T53–T70 proof program. |
| Objective | Repair and re-audit the source `ScreenOff` display-mask/scroll/OAM/VRAM transaction order until no current-equivalence difference remains. |
| Non-goals | No historical-node credit, no victory/floatey successor admission, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 75 exact, 1 mismatch, 1,916 needs-evidence; 4,324 feasible control relations. S3 scope: `ScreenOff` and its four recorded transaction relations; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t53-cohort-a-current-proof.md. |
| Files And ABI Surface | Shared `src/game/frame_root.c`, frame-root tests and registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: static transaction-order comparison plus controlled owner-local NMI records. Operational: frame-root focused checks, x86/x64/DOS16 builds, platform-purity and refreshed three ignored local artifacts because this S changes product code. |
| Expected Markers | The source writes the temporary display mask before scroll reset, OAM DMA and VRAM update; all four recorded transaction relations and `ScreenOff` are current-exact. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t53-s3; refreshed local artifacts for the implementation P. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | A transaction-order difference remains after repair, an original branch lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only when `ScreenOff` and every allocated transaction relation are exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Every `mysmb_game_commit_display_state` and `mysmb_game_commit_vram_buffer` caller and all NMI display-mask/scroll/OAM/VRAM transaction relations. |

## Current Technical Baseline

M2 T53 S1 found a `ScreenOff` transaction-order mismatch and cannot be treated as closed for source-order progression until this corrective S re-audit reaches zero differences. T53 S2 evidence remains recorded but does not authorize successor admission. M2 T53 S3 is the sole active corrective packet. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
