# M2 node-backfill validation matrix

This matrix turns historical M2 evidence into audited node matches. It is a validation queue, not a completion claim. The canonical counts remain in [M2 ROM-node progress](../../states/NODE_PROGRESS.md).

## Required evidence per node

A node can become ROM-match complete only when its inventory row links: original label and branch/write audit; shared C owner; focused CTest; a source-reachable ROM controller route; x86/x64 comparison of affected RAM, CIRAM, palette, OAM, PPU and audio state; and the P's 16/32/64 executable record.

## Latest audit: T24 S1

The [initial 77-node verification](m2-t24-s1-node-verification.md) produced
three complete nodes, 19 mismatch-affected nodes and 55 partial results on its
recorded snapshot. Subsequent concurrent fireball changes require affected
nodes to be reverified; no repair is performed or certified by this audit.
The owner expanded scope to all integrated nodes and all preceding T/S
responsibilities. The [full 1,992-node evidence census](m2-t24-s1-full-node-census.md)
backfills 62 omitted historical mappings and names every responsibility and
evidence gap. Current counts are maintained only in the progress report.
Full evidence census does not mean full semantic verification: only three
nodes currently have the required complete chain. Sections below preserve the
earlier zero-completion audit and its historical trace limitations.

## Backfill batch B1 - existing mapped nodes

| Candidate group | Nodes | Existing basis | Baseline tests | Required before count increases |
| --- | ---: | --- | --- | --- |
| Fireball core and OAM | 5 | T16/T20 source owners and focused smokes | mysmb.fireball-oam-smoke; mysmb.collision-regression-smoke | Source-reachable fireball route and frame comparison |
| Player OAM/action subtree | 46 | T16 S3 owner extraction and OAM smokes | mysmb.player-oam-smoke; mysmb.sprite-oam-smoke | Action, size, death and swim route coverage |
| Relative/offscreen helpers | 4 | T16 S3 focused smokes | mysmb.player-bounding-box-smoke; mysmb.bounding-box-clip-smoke | Visible, edge and offscreen source routes |
| Fireball/enemy collision | 17 | T17/S5/P20 inventory entries | mysmb.collision-regression-smoke | Fireball hit, immunity, defeat and Bowser routes |
| Hammer/player collision | 3 | T17/S5/P21 inventory entries | mysmb.collision-regression-smoke | Hammer/player hit, miss and gate routes |
| Castle/star flag | 2 | T18/S2/P5 inventory entries | mysmb.endgame-objects-smoke | Page-twelve castle and star-flag task routes |

B1 originally contained 77 mapped-but-unmatched names (5 + 46 + 4 + 17 + 3 + 2). It is a historical cohort, not the entire current audit scope or an S estimate. T24 S1 forecast eight named matches and proved three; see the latest audit above. Each implementation S must select and name its own realistic expected subset before starting. Closure names the exact subset proven and leaves the remainder unmatched.

The groups partition that named list as follows: fireball core/OAM is
`ProcFireball_Bubble`, `FireballObjCore`, `GetFireballBoundBox`, `DrawFireball`,
`DrawExplosion_Fireball`; player OAM/action is the 46 mapped inventory rows
from `PlayerGraphicsTable` through `ExPlyrAt`; helpers are
`RelativePlayerPosition`, `RelativeFireballPosition`, `GetPlayerOffscreenBits`,
`GetFireballOffscreenBits`; fireball/enemy collision is the 17 mapped rows
from `FireballEnemyCollision` through `ExHCF`; hammer/player is
`PlayerHammerCollision`, `ClHCol`, `ExPHC`; castle/star flag is `CastleObject`
and `StarFlagExit`. Data labels remain data and need consumer-route evidence.

## Backfill batch B2 - root and title evidence

| Candidate group | Existing evidence | Baseline tests | Route requirement |
| --- | --- | --- | --- |
| Reset, NMI, timer, pause | T14 source map and bounded NMI records | mysmb.reset-root-smoke; mysmb.pseudorandom-smoke; mysmb.pause-root-smoke | Cold, warm, pause and title NMI routes |
| Title/demo/menu | T15 label map and title records | mysmb.local-title-oracle; mysmb.local-title-bootstrap-smoke; mysmb.title-demo-smoke | Start, Select, B/world, demo and reset-title routes |

B2 begins only after each route is narrowed to labels actually executed. A whole-frame zero-difference result is evidence for the route, never automatic proof for every label in its enclosing subsystem.

## Backfill batch B3+ - active gameplay routes

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

## Historical accounting-only audit, 2026-09-26 (before T24 S1)

The full inventory recount and local hash/label comparison found 1,992 unique
labels, matching all source-line pairs. See the [accounting correction](../../states/NODE_PROGRESS.md#accounting-audit-2026-09-26).
The 77 pending labels match the progress report exactly. No node was promoted.

The existing title and mushroom pairs were compared again for both x64 and
x86, 600 samples each. All contracted output fields in the table below were
equal; each route's x86/x64 native files also had identical SHA-256 hashes.
Zero-page and stack still differ and remain excluded from these bounded output
claims. The existing fireball x64 pair was rechecked: work RAM first differs
at zero-based sample 18, CPU OAM backing at 237, and visible OAM at 238.
This proves properties of the existing trace files, not freshness against the
current working tree or branch coverage for every label. PC/branch-to-label
evidence is still absent; broad route equality cannot close individual nodes.

Reproduce using `tools/Compare-M2FrameTrace.ps1 -ReferenceTrace <reference>
-NativeTrace <native>`. Inputs under `build/m2-t17-s6-current/traces/` are
`reference-v2.msfr` with `native-x64-bootstrap.msfn` / `native-x86-bootstrap.msfn`,
`mushroom-reference.msfr` with `mushroom-native-x64.msfn` / `mushroom-native-x86.msfn`,
and `fire-sixth-landjump-reference.msfr` with `fire-sixth-landjump-native-x64.msfn`.
Neutral audit outputs are under `build/node-progress-audit/`. The audit reuses
existing build artifacts; it is not an implementation P or a delivery refresh.

Validation: the same ten focused tests listed below passed again on both
existing x64 and x86 build trees (10/10 each). The node checker passes on
PowerShell 7 and Windows PowerShell, accepts an explicit zero-delta audit and
a named one-node estimate, and rejects duplicate/unknown/out-of-scope estimate
labels, wrong closing counts, duplicate inventory rows and malformed cells.
The documentation gate and `git diff --check` pass. The gate now reads UTF-8,
accepts CRLF headings and checks repository Markdown without ignored build
outputs. Its corruption sweep found and repaired the B1/B2/B3 headings here
and three damaged range separators in the T15 label map and frame-root
proposal; no historical behavior or closure claim was changed.

Audit closure: incoming and resulting ROM matches are both 0 / 1,992,
expected and actual completion delta are both zero, and all 77 pending labels
remain with their recorded owners. B1 fireball divergence stays with T20/T17/
T16; B2 per-label root/title branch evidence stays with T14/T15; B3 per-label
power-up/collision evidence stays with T22/T17. Before any backfill promotion,
bind source execution and branch/write coverage to the exact labels, identify
the tested source revision and executable records, and rerun the relevant
routes when current-code evidence is needed. The historical comparisons above
do not meet those missing requirements on their own.


## B1 baseline execution

The first focused baseline ran on 2026-09-26 before any node-completion claim.
Both build/m2-x64 and build/m2-x86 passed 10/10 selected CTests:
reset-root, pseudorandom, pause-root, player bounding-box, bounding-box clip,
title demo, player OAM, fireball OAM, local title oracle, and local title
bootstrap. This establishes the repeatable CTest lane for B1/B2; it changes no
node status and leaves the progress fraction at 0 / 1,992 until the required
ROM-route comparisons are attached.


## First comparison results

| Batch | Existing bounded pair | Result | Node-count disposition |
| --- | --- | --- | --- |
| B1 fireball/OAM | fire-sixth-landjump reference vs x64 native, 600 samples | CIRAM, palette, audio and PPU scalars were equal; work RAM first differed at sample 18 and OAM first differed at sample 238. | No fireball/OAM node is backfilled. The OAM divergence remains an explicit B1 blocker. |
| B2 title/NMI | reference-v2 vs native-x64-bootstrap, 600 samples | CPU OAM backing, work RAM, both CIRAM pages, palette, visible OAM, audio and seven PPU scalars had zero differences. Zero-page and stack remained outside the output contract. | Route baseline accepted; no individual root/title label is counted until branch-execution coverage is attached. |
| B3 mushroom/collision | mushroom reference vs x64 native, 600 samples | CPU OAM backing, work RAM, both CIRAM pages, palette, visible OAM, audio and PPU scalars were equal. Zero-page and stack remained outside the output contract. | Route baseline accepted; next audit binds the executed power-up/collision labels before any count increase. |

These historical raw pairs are owned by the active gameplay task under ignored build output; this audit creates no new raw traces and does not delete inputs still used by that task. These results establish which historical evidence can be reused and prevent a false aggregate increment.
