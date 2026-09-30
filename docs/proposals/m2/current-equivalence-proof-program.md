# M2 current-equivalence proof program: T53–T70

## Purpose

This is the post-T52 verification program for the current C build.  It is
separate from historical `ROM-match complete` accounting.  Its exit requires
every original label, feasible control relation and feasible material relation
to have a fresh ROM-logic and operational disposition.  A route proves only
its executed chain; all other labels and edges remain pending until covered.

T52 repairs the currently known semantic mismatches.  T53 begins the full
source-order proof pass.  The task IDs below are owner-directed planning IDs;
only one S is active at a time and each S receives an exact label/edge subset,
original-ROM route and dual verification packet at admission.

## Task and S decomposition

| Task | Audit range | Planned bounded S chains |
| --- | --- | --- |
| T53 | Cohort A: reset, NMI, title/menu/demo | NMI timer/pause/sprite-zero alternatives; title/menu/world-select/demo; victory/end-message/floatey branches; A-edge and material handoffs. |
| T54 | Cohort B: screen tasks, HUD and text | screen-init/palette variants; status-number arithmetic; intermediate/time-up/game-over task transitions; text/warp/lives output. |
| T55 | Cohort C first half: area bootstrap, VRAM and PPU | nametable initialization; joypad serial I/O; VRAM packet output; scroll/register handoff. |
| T56 | Cohort C second half: area parser | parser task schedule; scenery/terrain; area-object decode; special-object and area-pointer data consumers. |
| T57 | Cohort D: renderer, metatiles and block buffer | render rows/attributes; replacement and bridge/block writes; metatile/palette data consumers; scroll-output joins. |
| T58 | Cohort E: dispatcher, control and transitions | GameEngine dispatch; player entrance/control; death/restart; pipe/vine/flagpole/area transition. |
| T59 | Cohort F: player motion and physics | ground/air/water/climb motion; jump/fall forces; X physics/friction; animation/action gates. |
| T60 | Cohort G: fireballs, bubbles and timers | fireball spawn/move/offscreen/background/enemy chain; bubble chain; game timer/whirlpool/flagpole/jumpspring/vine routes. |
| T61 | Cohort H: blocks, items and miscellaneous actors | power-up/block chains; coins/score; block objects; world gravity/movement; object dispatch graph validation. |
| T62 | Cohort I: enemy stream, initialization and groups | stream records/pointers; initializer vectors; ordinary/frenzy groups; Lakitu/Spiny/Bullet Bill family routes. |
| T63 | Cohort J first half: enemy loop and movement | enemy loop dispatch; normal/special actors; movement/gravity; platform/hammer/Bowser routes. |
| T64 | Cohort J second half: enemy terrain and collisions | enemy terrain state; player/enemy collision; projectile collision; star-flag/end-level actor routes. |
| T65 | Cohort K: shared collision and player terrain | bounding boxes; player terrain probes; platform collision; fireball background collision; shared tables. |
| T66 | Cohort L: relative position, offscreen and OAM | relative/offscreen bit chains; player/enemy/object OAM; title/endgame sprite output; scanline split state. |
| T67 | Cohort M: sound effects | sound dispatcher; square/noise effect handlers; queue priority; effect tables and APU command order. |
| T68 | Cohort N: music and music data | music selection/header load; square/triangle/noise streams; loop and envelope handling; data-table consumers. |
| T69 | Cross-cohort integration | all caller-to-callee and producer-to-consumer relations that cross the T53–T68 ownership boundaries; recorder route matrix and shared-frame state. |
| T70 | Final current-equivalence certification | complete node/edge/material ledger sweep, all route matrix replay, three-target operational regression and final platform-purity audit. |

## Common S admission and closure rule

Each S names a contiguous ROM entry-to-exit chain, every exact inventory label
and owned relation, current shared-C owner, predecessor/successor dependencies
and one reproducible original-ROM route.  Its ROM-logic track compares branch
predicates, reads, writes, table bindings and call/return order.  Its
operational track runs focused x86/x64 tests, the same shared-source DOS16
link, platform-purity check and three-target artifact refresh.

At closure, the registry records each scoped label and edge as `exact`,
`mismatch`, or retained `needs-evidence` with its next receiving S.  No task
may promote an unexecuted branch merely because an adjacent route matched.