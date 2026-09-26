# M2 node-backfill validation matrix

This matrix turns historical M2 evidence into audited node matches. It is a validation queue, not a completion claim. The canonical counts remain in [M2 ROM-node progress](../../states/NODE_PROGRESS.md).

## Required evidence per node

A node can become ROM-match complete only when its inventory row links: original label and branch/write audit; shared C owner; focused CTest; a source-reachable ROM controller route; x86/x64 comparison of affected RAM, CIRAM, palette, OAM, PPU and audio state; and the P's 16/32/64 executable record.

## Backfill batch B1 �w^~)�t existing mapped nodes

| Candidate group | Nodes | Existing basis | Baseline tests | Required before count increases |
| --- | ---: | --- | --- | --- |
| Fireball core and OAM | 5 | T16/T20 source owners and focused smokes | mysmb.fireball-oam-smoke; mysmb.collision-regression-smoke | Source-reachable fireball route and frame comparison |
| Player OAM/action subtree | 46 | T16 S3 owner extraction and OAM smokes | mysmb.player-oam-smoke; mysmb.sprite-oam-smoke | Action, size, death and swim route coverage |
| Relative/offscreen helpers | 4 | T16 S3 focused smokes | mysmb.player-bounding-box-smoke; mysmb.bounding-box-clip-smoke | Visible, edge and offscreen source routes |

B1's declared scope is the 77 names already listed as mapped-but-unmatched in the progress report. Its expected node delta is 0 to 77 / 1,995: no individual node is pre-approved for completion. The closure report must name the exact subset actually proven and leave the remainder mapped/unmatched.

## Backfill batch B2"��y��y� root and title evidence

| Candidate group | Existing evidence | Baseline tests | Route requirement |
| --- | --- | --- | --- |
| Reset, NMI, timer, pause | T14 source map and bounded NMI records | mysmb.reset-root-smoke; mysmb.pseudorandom-smoke; mysmb.pause-root-smoke | Cold, warm, pause and title NMI routes |
| Title/demo/menu | T15 label map and title records | mysmb.local-title-oracle; mysmb.local-title-bootstrap-smoke; mysmb.title-demo-smoke | Start, Select, B/world, demo and reset-title routes |

B2 begins only after each route is narrowed to labels actually executed. A whole-frame zero-difference result is evidence for the route, never automatic proof for every label in its enclosing subsystem.

## Backfill batch B3+�u���T active gameplay routes

| Candidate group | Baseline tests | Route requirement |
| --- | --- | --- |
| Player/world collision | mysmb.player-route-smoke; mysmb.player-friction-smoke; mysmb.collision-regression-smoke | Wall, head/block, pipe, vine, damage and stomp |
| Area/parser | mysmb.area-parser-column-smoke; mysmb.area-initialize-smoke; mysmb.parser-schedule-smoke | Area entry, hidden/question block, pipe and column scroll |
| Enemy stream/actors | mysmb.enemy-stream-smoke; mysmb.enemy-collision-smoke; mysmb.flying-cheep-smoke | Normal, group, frenzy, sixth-slot and collision routes |
| Audio | mysmb.audio-smoke | Jump, coin, grow, damage, timer and terminal routes |

## S admission and closure template

| Field | Required record |
| --- | --- |
| Node baseline | ROM-match complete / 1,992 before any change. |
| Expected node delta | Exact inventory labels expected to become matches and maximum resulting fraction. |
| Test baseline | Named focused CTests and original-ROM controller scripts. |
| Closure delta | Exact labels proven, labels still unmatched, resulting fraction and evidence links. |
| Target delivery | Build/validation record for mysmb16.exe, mysmb32.exe and mysmb64.exe. |


## B1 baseline execution

The first focused baseline ran on 2026-09-26 before any node-completion claim.
Both build/m2-x64 and build/m2-x86 passed 10/10 selected CTests:
reset-root, pseudorandom, pause-root, player bounding-box, bounding-box clip,
title demo, player OAM, fireball OAM, local title oracle, and local title
bootstrap. This establishes the repeatable CTest lane for B1/B2; it changes no
node status and leaves the progress fraction at 0 / 1,992 until the required
ROM-route comparisons are attached.
