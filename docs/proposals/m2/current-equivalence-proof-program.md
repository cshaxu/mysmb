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
| T65 | Cohort K: block queries and object/OAM output | shared block-buffer entries/tables; vine/hammer/flagpole/platform/coin/power-up/enemy/block/fireball/bubble output; player graphics tables. |
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
## Current checkpoint after T64

[T64's retained node/edge and integration proof](../../history/M2-T64-terrain-collision-current-proof.md)
is closed. Current exact nodes 1480/1992, feasible controls 3181/4323 and
material 368/487; historical mapping 1992/1992 remains separate. Cohort J
has no pending owned nodes/controls/material rows; global material enumeration
remains partial. T65 is the next unadmitted source cohort, followed by T66-T70.
Incoming boundary relations outside J retain their original pending owners.

## Current checkpoint after T65 S1

[T65 S1](t65-cohort-k-block-query-object-output-current-proof.md) is closed;
T65 is open and S2 is next. Current exact nodes 1494/1992, feasible controls
3192/4322 (raw 4342, infeasible 20), material 371/490 partial. Historical
1992/1992 is separate. Earlier checkpoint paragraphs retain closure-time facts.

## Current checkpoint after T65 S2

[T65 S2](t65-cohort-k-block-query-object-output-current-proof.md) is closed;
T65 is open and S3 is next. Current exact nodes 1502/1992, feasible controls
3204/4322 (raw 4342, infeasible 20), material 373/492 partial. Historical
1992/1992 remains separate. Earlier checkpoint paragraphs retain their facts.

## Current checkpoint after T65 S3

[T65 S3](t65-cohort-k-block-query-object-output-current-proof.md) is closed;
T65 is open, S4 next. Current nodes 1514/1992, feasible controls 3213/4321
(raw 4342, infeasible 21), material 380/492 partial; historical 1992/1992
remains separate. Planned Cohort L must restore PlayerOffscreenChk's actual
DumpTwoSpr call instead of direct stores before claiming that graph contract.

## Current checkpoint after T65 S4

[T65 S4](t65-cohort-k-block-query-object-output-current-proof.md) is closed;
T65 stays open, S5 next. Current nodes 1523/1992, feasible controls 3226/4321
(raw 4342, infeasible 21), material 381/492 partial. Historical 1992/1992
remains separate; no later-scope node or relation is pre-credited.

## Current checkpoint after T65 S5

[T65 S5](t65-cohort-k-block-query-object-output-current-proof.md) is closed;
T65 stays open, S6 next. Current nodes 1533/1992, feasible controls 3257/4321
(raw 4342, infeasible 21), material 381/492 partial. Historical 1992/1992 is
separate; dependency-node and external material evidence retains later scope.

## Current checkpoint after T65 S6

[T65 S6](t65-cohort-k-block-query-object-output-current-proof.md) is closed;
T65 stays open, S7 next. Current nodes 1538/1992, feasible controls 3266/4321
(raw 4342, infeasible 21), material 382/492 partial. Historical 1992/1992 is
separate; external caller relations retain their own audit scope.

## Current checkpoint after T65 S7

[T65 S7](t65-cohort-k-block-query-object-output-current-proof.md) closed;
T65 open, S8 next. Current nodes1544/1992, controls3276/4321 (raw4342,
infeasible21), material384/492 partial; historical1992/1992 separate.
S9 must consolidate raw clip callers into the original shared column/row/
erase sequence, avoiding duplicate erase; internal pending status is retained.

## Current checkpoint after T65 S8

[T65 S8](t65-cohort-k-block-query-object-output-current-proof.md) closes35
nodes,83 feasible controls and five material rows; two raw fallthroughs are
source-infeasible. Current nodes1579/1992, controls3359/4319(raw4342,
infeasible23), material389/492 partial. Historical1992/1992 separate.
T65 remains open with54 pending nodes; S9 next, not yet admitted.

## Current checkpoint after T65 S9

[T65 S9](t65-cohort-k-block-query-object-output-current-proof.md) closes22
nodes and62 feasible controls; two raw controls are source-infeasible.
Current nodes1601/1992, controls3421/4317(raw4342,infeasible25), material389/492
partial; historical1992/1992 separate. T65 stays open with32 pending nodes;
S10 next, not yet admitted. External block/player caller returns remain pending.

## Current checkpoint after T65 S10

[T65 S10](t65-cohort-k-block-query-object-output-current-proof.md) closes14
nodes,36 controls and one material row. Current1615/1992 nodes,3457/4317
controls(raw4342,infeasible25),390/492 material partial; historical1992/1992
distinct. T65 stays open with18 pending nodes; S11 next, not admitted.
External BlockObjectsCore/BouncingBlockHandler caller boundaries remain pending.

## Current checkpoint after T65 S11

[T65 S11](t65-cohort-k-block-query-object-output-current-proof.md) closes7
nodes,7 controls and one material row. Current1622/1992 nodes,3464/4317
controls(raw4342,infeasible25),391/492 material partial; historical1992/1992
separate. T65 remains open with11 pending nodes; S12 next, not admitted.
Shared projectile/explosion output repairs retain exact incoming caller credit.

## Current checkpoint after T65 S12

[T65 S12](t65-cohort-k-block-query-object-output-current-proof.md) closes6
nodes and16 controls. Current1628/1992 nodes,3480/4317 feasible controls
(raw4342,infeasible25),391/492 material partial; historical1992/1992 separate.
T65 stays open with5 pending nodes; S13 next, not admitted.

## Current checkpoint after T65 S13

[T65 S13](t65-cohort-k-block-query-object-output-current-proof.md) closes2
nodes and3 controls. Current1630/1992 nodes,3483/4317 controls(raw4342,
infeasible25),391/492 material partial; historical1992/1992 separate.
T65 remains open with3 pending table nodes; S14 next, not admitted.

## Current checkpoint after T65 S14

[T65 S14](t65-cohort-k-block-query-object-output-current-proof.md) closes3
table nodes and3 material rows, no control promotion. Current1633/1992 nodes,
3483/4317 controls(raw4342,infeasible25),394/492 material partial; historical
1992/1992 separate. T65 has all154 planned nodes exact; S15 census remains
unadmitted and required before T closure. T66 player-control proof not inferred.
