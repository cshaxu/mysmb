# Project Status

## Current Work

## M2 T53 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T53 S1 — Cohort A reset/NMI through operating-mode dispatch current-equivalence audit. |
| Admission And Approval | Owner-directed continuation under the approved source-order T53–T70 proof program. |
| Objective | Audit the 39-label reset/NMI/pause/timer/LFSR/sprite/OAM/dispatch chain and its internal relations against the original ROM. |
| Non-goals | No historical-node credit, no cross-cohort final proof, and no platform-owned game decision. Any mismatch becomes a later candidate rather than an unscoped repair. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 70 exact, 1 mismatch, 1,921 needs-evidence; 4,326 feasible control relations. S1 scope at admission: 39 labels, 22 exact and 17 needs-evidence; 38 are now exact and `ScreenOff` is mismatch. Every scoped node has a current disposition; 75 internal relations remain under independent audit. Expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t53-cohort-a-current-proof.md. |
| Files And ABI Surface | Shared `src/game/boot.c`, `src/game/frame_root.c`, declared shared callees and tests/registry/ledger evidence only; platform adapters remain outside gameplay. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: static node/edge audit plus controlled owner-local reset/NMI records. Operational: focused root tests, x86/x64 builds and self-tests, OpenNT DOS16 link, platform-purity and three ignored local artifacts. |
| Expected Markers | Every scoped label and internal relation has a recorded current disposition; no unsupported promotion; reset/display/timer/pause/sprite-zero/selector branch evidence is separated. |
| Asset Needs | Owner-local ROM only for ignored traces under build/m2-t53-s1; local 16/32/64 artifacts refreshed only for a completed implementation P. |
| Reporting Requirements | Report exact scoped labels, incoming/current dispositions, control/material relations, current-registry before/after and separate operational outcome. |
| Stop Conditions | An original branch lacks a shared-C counterpart, a route mismatch appears, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S may close only with an individual disposition for all 39 labels and its 75 internal relations, reproducible route evidence and both verification tracks. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | All reset/NMI display, buffer, pause, timer, LFSR, sprite-zero, OAM and dispatcher call/return relations in lines 699–981. |

## Current Technical Baseline

M2 T52 is closed. M2 T53 S1 is the sole active packet. One shared native C90 game implementation serves DOS16 and Win32 x86/x64; platform adapters do not own game logic.
