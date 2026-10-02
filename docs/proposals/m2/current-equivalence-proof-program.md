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
| T66 | Cohort L: player graphics, relative position, offscreen and OAM | PlayerGfxHandler/action/change-size/attributes; relative object entries; offscreen wrappers and X/Y tables; DrawSpriteObject flip/output. Exact83-node scope follows inventory. |
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

[T65 S1](../../history/M2-T65-block-query-object-output-current-proof.md) is closed;
T65 is open and S2 is next. Current exact nodes 1494/1992, feasible controls
3192/4322 (raw 4342, infeasible 20), material 371/490 partial. Historical
1992/1992 is separate. Earlier checkpoint paragraphs retain closure-time facts.

## Current checkpoint after T65 S2

[T65 S2](../../history/M2-T65-block-query-object-output-current-proof.md) is closed;
T65 is open and S3 is next. Current exact nodes 1502/1992, feasible controls
3204/4322 (raw 4342, infeasible 20), material 373/492 partial. Historical
1992/1992 remains separate. Earlier checkpoint paragraphs retain their facts.

## Current checkpoint after T65 S3

[T65 S3](../../history/M2-T65-block-query-object-output-current-proof.md) is closed;
T65 is open, S4 next. Current nodes 1514/1992, feasible controls 3213/4321
(raw 4342, infeasible 21), material 380/492 partial; historical 1992/1992
remains separate. Planned Cohort L must restore PlayerOffscreenChk's actual
DumpTwoSpr call instead of direct stores before claiming that graph contract.

## Current checkpoint after T65 S4

[T65 S4](../../history/M2-T65-block-query-object-output-current-proof.md) is closed;
T65 stays open, S5 next. Current nodes 1523/1992, feasible controls 3226/4321
(raw 4342, infeasible 21), material 381/492 partial. Historical 1992/1992
remains separate; no later-scope node or relation is pre-credited.

## Current checkpoint after T65 S5

[T65 S5](../../history/M2-T65-block-query-object-output-current-proof.md) is closed;
T65 stays open, S6 next. Current nodes 1533/1992, feasible controls 3257/4321
(raw 4342, infeasible 21), material 381/492 partial. Historical 1992/1992 is
separate; dependency-node and external material evidence retains later scope.

## Current checkpoint after T65 S6

[T65 S6](../../history/M2-T65-block-query-object-output-current-proof.md) is closed;
T65 stays open, S7 next. Current nodes 1538/1992, feasible controls 3266/4321
(raw 4342, infeasible 21), material 382/492 partial. Historical 1992/1992 is
separate; external caller relations retain their own audit scope.

## Current checkpoint after T65 S7

[T65 S7](../../history/M2-T65-block-query-object-output-current-proof.md) closed;
T65 open, S8 next. Current nodes1544/1992, controls3276/4321 (raw4342,
infeasible21), material384/492 partial; historical1992/1992 separate.
S9 must consolidate raw clip callers into the original shared column/row/
erase sequence, avoiding duplicate erase; internal pending status is retained.

## Current checkpoint after T65 S8

[T65 S8](../../history/M2-T65-block-query-object-output-current-proof.md) closes35
nodes,83 feasible controls and five material rows; two raw fallthroughs are
source-infeasible. Current nodes1579/1992, controls3359/4319(raw4342,
infeasible23), material389/492 partial. Historical1992/1992 separate.
T65 remains open with54 pending nodes; S9 next, not yet admitted.

## Current checkpoint after T65 S9

[T65 S9](../../history/M2-T65-block-query-object-output-current-proof.md) closes22
nodes and62 feasible controls; two raw controls are source-infeasible.
Current nodes1601/1992, controls3421/4317(raw4342,infeasible25), material389/492
partial; historical1992/1992 separate. T65 stays open with32 pending nodes;
S10 next, not yet admitted. External block/player caller returns remain pending.

## Current checkpoint after T65 S10

[T65 S10](../../history/M2-T65-block-query-object-output-current-proof.md) closes14
nodes,36 controls and one material row. Current1615/1992 nodes,3457/4317
controls(raw4342,infeasible25),390/492 material partial; historical1992/1992
distinct. T65 stays open with18 pending nodes; S11 next, not admitted.
External BlockObjectsCore/BouncingBlockHandler caller boundaries remain pending.

## Current checkpoint after T65 S11

[T65 S11](../../history/M2-T65-block-query-object-output-current-proof.md) closes7
nodes,7 controls and one material row. Current1622/1992 nodes,3464/4317
controls(raw4342,infeasible25),391/492 material partial; historical1992/1992
separate. T65 remains open with11 pending nodes; S12 next, not admitted.
Shared projectile/explosion output repairs retain exact incoming caller credit.

## Current checkpoint after T65 S12

[T65 S12](../../history/M2-T65-block-query-object-output-current-proof.md) closes6
nodes and16 controls. Current1628/1992 nodes,3480/4317 feasible controls
(raw4342,infeasible25),391/492 material partial; historical1992/1992 separate.
T65 stays open with5 pending nodes; S13 next, not admitted.

## Current checkpoint after T65 S13

[T65 S13](../../history/M2-T65-block-query-object-output-current-proof.md) closes2
nodes and3 controls. Current1630/1992 nodes,3483/4317 controls(raw4342,
infeasible25),391/492 material partial; historical1992/1992 separate.
T65 remains open with3 pending table nodes; S14 next, not admitted.

## Current checkpoint after T65 S14

[T65 S14](../../history/M2-T65-block-query-object-output-current-proof.md) closes3
table nodes and3 material rows, no control promotion. Current1633/1992 nodes,
3483/4317 controls(raw4342,infeasible25),394/492 material partial; historical
1992/1992 separate. T65 has all154 planned nodes exact; S15 census remains
unadmitted and required before T closure. T66 player-control proof not inferred.

## Current checkpoint after T65 closure

[T65's retained proof](../../history/M2-T65-block-query-object-output-current-proof.md)
is closed after S15. Current1633/1992 nodes,3485/4317 feasible controls
(raw4342,infeasible25),394/492 material partial; historical1992/1992 separate.
K has154 exact nodes,307 exact feasible controls plus6 infeasible,26 exact
material rows. Current full/independent integration and248/248 native tests
per width plus original DOS16 link pass. Ten external incoming controls
retain their named pending owners. T66 actual Cohort L inventory is next,
not admitted; no milestone-wide proof inferred from this closure.

## T66 admission checkpoint

[T66 exact83-node plan](../../history/M2-T66-player-relative-offscreen-current-proof.md) is admitted
with S1 player graphics44 nodes active. No exact credit at admission; current
1633/1992 nodes and3485/4317 feasible controls. Remaining S chains follow
original source order; accepted historical mapping1992/1992 stays separate.

## Current checkpoint after T66 S1

[T66 S1](../../history/M2-T66-player-relative-offscreen-current-proof.md) closes44 nodes,
103 controls and2 material rows. Current1677/1992 nodes,3588/4317 feasible
controls(raw4342,infeasible25),396/492 material partial; historical1992/1992
separate. Original75040 roots/127104 actual row/erase returns match both
widths;12/12 focused tests each and original DOS16 link pass,3 products
refreshed. T66 stays open with39 pending nodes; S2 next, not admitted.

## Current checkpoint after T66 S2

[T66 S2](../../history/M2-T66-player-relative-offscreen-current-proof.md) closes9 nodes,
18 controls and one newly enumerated consumed block-return material relation.
Current1686/1992 nodes,3606/4317 feasible controls(raw4342,infeasible25),
397/493 material partial; historical1992/1992 separate. All393216 original
roots match both widths;12/12 focused tests each and original DOS16 link
pass,3 products refreshed. T66 has30 pending nodes; S3 next unadmitted.

## Current checkpoint after T66 S3

[T66 S3](../../history/M2-T66-player-relative-offscreen-current-proof.md) closes11 nodes,
18 controls/material00432 without production differences. Current1697/1992
nodes,3624/4317 controls(raw4342,infeasible25),398/493 material partial;
historical1992/1992 separate.393216 original roots match both widths,14/14
focused tests each and original DOS16 link pass. Three S2 products retained;
T66 has19 pending nodes and S4 next unadmitted.

## Current checkpoint after T66 S4

[T66 S4](../../history/M2-T66-player-relative-offscreen-current-proof.md) closes6 nodes,
9 controls/material00433-00434 without production differences. Current1703/
1992 nodes,3633/4317 controls(raw4342,infeasible25),400/493 material partial;
historical1992/1992 separate.131072 original roots match both widths;14/14
focused tests each and original DOS16 link pass. Three S2 products retained;
T66 has13 pending nodes, S5 next unadmitted.

## Current checkpoint after T66 S5

[T66 S5](../../history/M2-T66-player-relative-offscreen-current-proof.md) closes10 nodes,
13 controls/material00435-00437 without production differences. Current1713/
1992 nodes,3646/4317 controls(raw4342,infeasible25),403/493 material partial;
historical1992/1992 separate.131072 original roots match both widths;14/14
focused tests each and original DOS16 link pass. Three S2 products retained;
T66 has3 pending nodes, S6 next unadmitted before S7 integration closure.

## Current checkpoint after T66 S6

[T66 S6](../../history/M2-T66-player-relative-offscreen-current-proof.md) closes3 nodes,
3 feasible controls and instruction-proven impossible03162, retained raw.
Current1716/1992 nodes,3649/4316 controls(raw4342,infeasible26),403/493
material partial; historical1992/1992 separate.131072 original roots match
both widths;16 focused tests each and original DOS16 link pass. Three S2
products retained; all83 T66 nodes exact, T open for S7 integration closure.

## Current checkpoint after T66 closure

[T66 retained closure](../../history/M2-T66-player-relative-offscreen-current-proof.md)
closes all83 owned nodes,164 feasible controls/one proven infeasible raw edge,
10 material rows. S7 zero fresh credit;20,512 current original integration roots
zero differences each width,248 native tests each and original DOS16 link pass.
Current1716/1992 nodes,3649/4316 controls(raw4342,infeasible26),403/493 material
partial; historical1992/1992 separate. Fifteen H-owned incoming controls remain
pending for cross-cohort/T69. T67 next unadmitted; M2 not complete.

## T67 admission checkpoint

[T67 exact126-node plan](../../history/M2-T67-sound-command-current-proof.md) follows the
actual M inventory, including its music selection and partial stream prefixes.
S1 admits22 SoundEngine/register nodes, intended fresh22/max1738/1992; no
admission credit. Current1716/1992 nodes,3649/4316 controls,403/493 material
partial. Remaining S follows source order; T68 owns N, T69 external joins.

## Current checkpoint after T67 S1

[T67 S1](../../history/M2-T67-sound-command-current-proof.md) closes22 nodes and45
feasible controls, with four instruction-proven impossible fallthroughs retained.
Current1738/1992 nodes,3694/4312 controls(raw4342,infeasible30),403/493 material
partial; historical1992/1992 separate.15,360 original roots agree both widths
including ordered APU writes;7 focused tests each and original DOS16 link pass.
No product differences,3 existing EXEs retained; S2 next unadmitted, T67 open.

## Current checkpoint after T67 S2

[T67 S2](../../history/M2-T67-sound-command-current-proof.md) closes30 Square1 nodes,
66 feasible controls/material00438, with11 source-infeasible fallthroughs retained.
Current1768/1992 nodes,3760/4301 controls(raw4342,infeasible41),404/493 material
partial; historical1992/1992 separate.69,632 actual original roots agree both
widths including ordered APU writes;7 tests each/original DOS16 link pass.
No product repair,3 existing EXEs retained; S3 next unadmitted, T67 open.

## Current checkpoint after T67 S3

[T67 S3](../../history/M2-T67-sound-command-current-proof.md) closes36 Square2 nodes,
60 feasible controls and material00439-00441, with11 impossible controls retained.
Current1804/1992 nodes,3820/4290 controls(raw4342,infeasible52),407/493 material
partial; historical1992/1992 separate.135,168 actual original roots agree both
widths including ordered APU writes;7 tests each/original DOS16 link pass.
No product repair,3 existing EXEs retained; S4 next unadmitted, T67 open.

## Current checkpoint after T67 S4

[T67 S4](../../history/M2-T67-sound-command-current-proof.md) closes11 noise nodes,
17 feasible controls/material00442 after repairing zero-envelope stream
fallthrough;69760 unchanged original roots agree each width. Current1815/1992
nodes,3837/4290 controls(raw4342,infeasible52),408/493 material partial;
historical1992/1992 separate.248 tests each plus7 updated focused tests and
original DOS16 link pass; all3 EXEs refreshed. S5 next unadmitted, T67 open.

## Current checkpoint after T67 S5

[T67 S5](../../history/M2-T67-sound-command-current-proof.md) closes27 music-prefix
nodes/78 controls after original ground-loop/victory-mask/header repairs;
4 impossible raw fallthroughs retained. Current1842/1992 nodes,3915/4286
controls(raw4342,infeasible56),408/493 material partial; historical1992/1992
separate.20736 roots both widths zero differences;248 tests each/256 header
selectors each/OpenNT link pass;3 EXEs refreshed. All126 T67 nodes exact;
T67 open for S6 census/integration, next unadmitted.

## Current checkpoint after T67 closure

[Closed T67](../../history/M2-T67-sound-command-current-proof.md) proves all126
M nodes/266 feasible controls/5 material rows;30 impossible raw controls retained.
S6 adds73728 mixed/title/pause original roots each width, zero differences and
actual four channel call/return joins. Current1842/1992 nodes,3915/4286 controls
(raw4342,infeasible56),408/493 material partial; historical1992/1992 separate.
Full builds/248 tests each/purity/OpenNT link pass;3 S5 products unchanged.
M2 still open; remaining150 nodes/371 feasible controls/85 material rows.
T68 next unadmitted, then cross-cohort/final certification.

## Current checkpoint after T68 S1

[T68 S1](../../history/M2-T68-music-data-current-proof.md) closes17 nodes/41 controls,
5 impossible raw fallthroughs proven. Current1859/1992 nodes,3956/4281 controls
(raw4342,infeasible61),408/493 material partial; historical1992/1992 separate.
200961 original roots each width agree after zero-loopback/INC-order repairs;
248 tests each/purity/OpenNT link pass,all3 products refreshed. T68 open,
S2 next unadmitted;60 N plus73 earlier C labels remain pending. Cross-cohort
audit must resolve Square1/Square2 controlled RAM-alias fetch-order scope
in TODO before whole-domain certification; earlier PRG evidence remains bounded.

## Current checkpoint after T68 S2

[T68 S2](../../history/M2-T68-music-data-current-proof.md) closes9 helpers/8 controls,
2 impossible raw fallthroughs. Current1868/1992 nodes,3964/4279 controls
(raw4342,infeasible63),408/493 material partial; historical1992/1992 distinct.
786432 original roots each width zero diff after original two-ADC carry repair;
248 tests each/purity/OpenNT link pass,3 EXEs refreshed. T68 open, S3 next
unadmitted;51 N plus73 earlier C nodes remain pending. Earlier Square1/Square2
RAM-alias fetch order remains explicit cross-cohort debt, not silently closed.

## Current checkpoint after T68 S3

[T68 S3](../../history/M2-T68-music-data-current-proof.md) closes23 music-header nodes/
23 material relations after all171 region bytes are actually indexed/read and
native consumers proven. Current1891/1992 nodes,3964/4279 controls
(raw4342,infeasible63),431/493 material partial; historical1992/1992 distinct.
12544 original roots both widths zero diff; current builds/4 focused tests each/
purity/OpenNT link pass;3 S2 products byte-identical retained. T68 open,S4 next
unadmitted;28 N plus73 earlier C nodes remain pending, no final certification.

## Current checkpoint after T68 S4

[T68 S4](../../history/M2-T68-music-data-current-proof.md) closes21 streams and adds62
actual typed material relations. Current1912/1992 nodes,3964/4279 controls
(raw4342,infeasible63),493/555 material partial; denominator493->555 reflects
new source-path enumeration.1348 bytes actually read,4 explicit source-unused
storage retained;51201 original roots each width zero diff. Current builds/
4 focused tests each/purity/OpenNT link pass;3 S2 products unchanged. T68 open,
S5 next unadmitted;7 N plus73 C labels and external relations remain pending.

## Current checkpoint after T68 S5

[T68 S5](../../history/M2-T68-music-data-current-proof.md) closes7 table nodes and7
material relations. Current1919/1992 nodes,3964/4279 controls(raw4342,
infeasible63),500/555 material partial.250 declared-consumer bytes/2304 actual
original roots each width zero differences;current builds/4 focused tests
each/purity/OpenNT link pass;3 products unchanged. All77 N nodes exact;
T68 open,S6 integration next unadmitted. Earlier73 C nodes and external
relations remain pending; historical1992/1992 is not current certification.

## Current checkpoint after T68 closure

[Closed T68](../../history/M2-T68-music-data-current-proof.md) proves all77 N
nodes/49 feasible controls/92 material;7 impossible raw controls retained.
S6 adds16384 mixed/sequential/title/pause original roots each width,zero diff.
Current1919/1992 nodes,3964/4279 controls(raw4342,infeasible63),500/555 material
partial;historical1992/1992 separate. Full builds/248 tests each/purity/OpenNT
link pass;3 S2 products unchanged. T69 cross-cohort work next unadmitted;
earlier73 C nodes/315 controls/55 enumerated material rows and M alias debt
remain before final certification. M2 remains open.

## Current checkpoint after T69 S1

[T69 S1](t69-cross-cohort-current-proof.md) closes19 status nodes/29 feasible
controls/2 material,1 impossible retained. Current1938/1992 nodes,3993/4278
controls(raw4342,infeasible64),502/555 material partial;historical1992/1992
separate.196608 final original roots each width zero diff after source repairs;
current builds/4 focused tests each/purity/OpenNT link pass,3 EXEs refreshed.
T69 open,S2 next unadmitted;54 nodes/285 controls/53 enumerated material
rows plus explicit M alias debt remain before certification.

## Current checkpoint after T69 S2

[T69 S2](t69-cross-cohort-current-proof.md) closes21 initialization nodes,
42 controls/2 material after original task/mirror/call/write-order repairs.
Current1959/1992 nodes,4035/4278 feasible controls(raw4342,infeasible64),
504/555 material partial;historical1992/1992 separate.5888 original returning
roots each width zero diff;4 focused tests each/purity/current builds/OpenNT
link pass,3 EXEs refreshed together. T69 open,S3 next unadmitted;33 nodes,
243 feasible controls,51 enumerated material rows plus earlier M alias debt
remain before certification.

## Current checkpoint after T69 S3

[T69 S3](t69-cross-cohort-current-proof.md) closes5 area-music nodes/8 controls/
1 material without product repairs. Current1964/1992 nodes,4043/4278 feasible
controls(raw4342,infeasible64),505/555 material partial;historical1992/1992
separate.8192 original returning roots each width zero diff;3 focused tests
each/purity/current builds/OpenNT target pass,3 S2 EXEs retained byte-identical.
T69 open,S4 next unadmitted;28 nodes/235 controls/50 enumerated material plus
earlier M alias debt remain before certification.
