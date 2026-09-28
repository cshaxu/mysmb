# M2 T37: Power-up actor, blocks and movement primitives

## Source-order scope and exact accounting

T36 closed in 263a75e at 813 / 1,992. This slice receives its explicit
PowerUpObjHandler boundary exception (line7184), then covers original
lines7201-7787. The listing contains 74 labels, including that exception.
Three labels retain accepted T31 S2 proof; 71 incomplete labels are planned
for completion, giving a maximum 884 / 1,992. The old broad roadmap caption
is corrected without changing source ranges or sequence. This is not a
second pass over vines, cannon or flagpole setup.

The nine S chains below follow original source order. Each performs source
mapping, implementation, original-ROM logic comparison and operational proof
as one delivery. Only S1 is admitted now. Later S rows are a plan, with
current receivers retaining custody until exact accepted transfers. No fixed
mapping/implementation/audit/test/documentation S phases are introduced.

| S | Chain | Planned shared owner | Expected new / total | Exact labels in original order |
| --- | --- | --- | ---: | --- |
| S1 | Power-up actor lifetime | game/power_up.c | 6 / 6 | `PowerUpObjHandler`, `ShroomM`, `GrowThePowerUp`, `ChkPUSte`, `RunPUSubs`, `ExitPUp` |
| S2 | Player head-hit and block positioning | game/blocks/head.c | 13 / 13 | `BlockYPosAdderData`, `PlayerHeadCollision`, `DBlockSte`, `ChkBrick`, `StartBTmr`, `ContBTmr`, `PutOldMT`, `PutMTileB`, `SmallBP`, `BigBP`, `Unbreak`, `InvOBit`, `InitBlock_XY_Pos` |
| S3 | Block bump, content vector and metatile lookup | game/blocks/bump.c | 11 / 11 | `BumpBlock`, `BlockCode`, `MushFlowerBlock`, `StarBlock`, `ExtraLifeMushBlock`, `VineBlock`, `ExitBlockChk`, `BrickQBlockMetatiles`, `BlockBumpedChk`, `BumpChkLoop`, `MatchBump` |
| S4 | Brick shatter, coin-above and chunk creation | game/blocks/chunks.c | 4 / 4 | `BrickShatter`, `CheckTopOfBlock`, `TopEx`, `SpawnBrickChunks` |
| S5 | Block and brick-chunk lifetime | game/blocks/lifetime.c | 5 / 5 | `BlockObjectsCore`, `ChkTop`, `BouncingBlockHandler`, `KillBlock`, `UpdSte` |
| S6 | Deferred block metatile replacement | game/blocks/replacement.c | 3 / 3 | `BlockObjMT_Updater`, `UpdateLoop`, `NextBUpd` |
| S7 | Horizontal movement primitive and entries | game/world/movement.c | 6 / 6 | `MoveEnemyHorizontally`, `MovePlayerHorizontally`, `MoveObjectHorizontally`, `SaveXSpd`, `UseAdder`, `ExXMove` |
| S8 | Vertical movement adapters | game/world/movement.c and enemy/movement.c | 11 / 14 | `MovePlayerVertically`, `NoJSChk`, `MoveD_EnemyVertically`, `MoveFallingPlatform`, `ContVMove`, `MoveRedPTroopaDown`, `MoveRedPTroopaUp`, `MoveRedPTroopa`, `MoveDropPlatform`, `MoveEnemySlowVert`, `SetMdMax`, `MoveJ_EnemyVertically`, `SetHiMax`, `SetXMoveAmt` |
| S9 | Gravity core and adjacent entries | game/world/movement.c | 12 / 12 | `MaxSpdBlockData`, `ResidualGravityCode`, `ImposeGravityBlock`, `ImposeGravitySprObj`, `MovePlatformDown`, `MovePlatformUp`, `SetDplSpd`, `RedPTroopaGrav`, `ImposeGravity`, `AlterYP`, `ChkUpM`, `ExVMove` |

Retained complete with T31 S2 custody: MoveD_EnemyVertically,
MoveFallingPlatform and ContVMove. Their scope inclusion supports adapter
integration and gives no new conformance credit.

## Implementation and validation boundaries

- S1 owns PowerUpObjHandler through ExitPUp. It consumes T36 initializer
  state, movement/terrain, relative/offscreen/box, graphics, player collision
  and bounds children. It removes the split movement-versus-finish caller,
  preserving the original continuous six-child tail. Child internals stay
  with their own owners; a necessary unchanged child seam gives no credit.
- S2 owns the complete head-hit caller and coordinate entry, from the Y-adder
  table through InitBlock_XY_Pos. It calls existing blanking, metatile lookup,
  bump and shatter entries. Prove blank-before-read ordering, saved carry,
  player size, coin-brick timers, block-buffer writes and final control toggle.
  Later S3/S4 child implementations are called through declared boundaries;
  their algorithms are not repaired prematurely in S2.
- S3 owns BumpBlock, its original content dispatch and complete table lookup.
  Prove all matched indices and no-match carry, top-coin child ordering and
  exact coin/power-up/vine entry arguments. Reuse T36 coin and initializer
  owners; do not duplicate their score, allocation or type normalization.
- S4 owns BrickShatter, CheckTopOfBlock and SpawnBrickChunks as a connected
  break/coin-above chain. Preserve source RAM scratch, removal-before-spawn,
  paired chunk coordinate/speed writes and score child ordering.
- S5 owns the entire block/brick lifetime branch family. Preserve low-state
  stack semantics, both gravity/horizontal calls, original reload points,
  relative/offscreen/draw order, byte comparisons and replacement/retirement.
- S6 owns the two-slot metatile updater loop. Preserve occupied-VRAM gate,
  ObjectOffset even on skipped slots, original block-buffer addressing,
  ReplaceBlockMetatile call and flag-clear order. Do not absorb VRAM child
  algorithms from the area-output owner.
- S7 owns all three horizontal movement entries and their shared arithmetic.
  Prove 4.4 carry, signed adder/page propagation, Jumpspring gate, return A
  displacement and enemy ObjectOffset reload. Audit callers of old shortcuts.
- S8 owns the adjacent vertical adapters, retaining the three accepted nodes.
  Prove timer/Jumpspring gates, sprite-index conversions, exact force/max
  parameters and reload contracts. The gravity child is exercised through
  its existing boundary until S9; adapter proof is not gravity-core credit.
- S9 owns the common gravity chain and its nearby block/platform entries.
  Prove data binding, dummy/fraction carry, signed-byte limit comparisons,
  upward subtraction and wrapped page motion. ResidualGravityCode has no
  ordinary incoming ROM edge: record this honestly. Audit its prefix/BIT
  bytes, test the corresponding native entry and validate its shared reached
  successor separately; do not manufacture a CPU jump or claim natural
  execution. If that evidence cannot satisfy the node contract, retain it
  incomplete with an exact accepted disposition rather than grant credit.

Every S declares its source root/exit and route before implementation. Each
node retains individual table/branch/read/write/call evidence. Each P runs
one focused regression set, x86/x64 strict C90, DOS16 link, platform purity
and three owner-authorized local artifacts. Original-ROM logic proof and
native operational proof remain separate. T closure combines all S results
and retained dependencies in a final cross-chain matrix, preserving child
failures instead of hiding or relabeling them.

## Exact incoming node disposition

| ROM line | Label | Incoming conformance | Receiver before admission | Planned chain |
| ---: | --- | --- | --- | --- |
| 7184 | `PowerUpObjHandler` | mapped; evidence incomplete | M2 T24 S2 | S1 |
| 7202 | `ShroomM` | open | M2 T24 S2 | S1 |
| 7206 | `GrowThePowerUp` | mapped; evidence incomplete | M2 T24 S2 | S1 |
| 7223 | `ChkPUSte` | open | M2 T24 S2 | S1 |
| 7226 | `RunPUSubs` | mapped; evidence incomplete | M2 T24 S2 | S1 |
| 7232 | `ExitPUp` | open | M2 T24 S2 | S1 |
| 7241 | `BlockYPosAdderData` | open | M2 T24 S2 | S2 |
| 7244 | `PlayerHeadCollision` | mapped; evidence incomplete | M2 T24 S2 | S2 |
| 7251 | `DBlockSte` | open | M2 T24 S2 | S2 |
| 7265 | `ChkBrick` | open | M2 T24 S2 | S2 |
| 7274 | `StartBTmr` | open | M2 T24 S2 | S2 |
| 7279 | `ContBTmr` | open | M2 T24 S2 | S2 |
| 7282 | `PutOldMT` | open | M2 T24 S2 | S2 |
| 7283 | `PutMTileB` | open | M2 T24 S2 | S2 |
| 7297 | `SmallBP` | open | M2 T24 S2 | S2 |
| 7298 | `BigBP` | open | M2 T24 S2 | S2 |
| 7308 | `Unbreak` | open | M2 T24 S2 | S2 |
| 7309 | `InvOBit` | open | M2 T24 S2 | S2 |
| 7316 | `InitBlock_XY_Pos` | mapped; evidence incomplete | M2 T24 S2 | S2 |
| 7332 | `BumpBlock` | mapped; evidence incomplete | M2 T24 S2 | S3 |
| 7349 | `BlockCode` | mapped; evidence incomplete | M2 T24 S2 | S3 |
| 7363 | `MushFlowerBlock` | open | M2 T24 S2 | S3 |
| 7367 | `StarBlock` | open | M2 T24 S2 | S3 |
| 7371 | `ExtraLifeMushBlock` | open | M2 T24 S2 | S3 |
| 7376 | `VineBlock` | open | M2 T24 S2 | S3 |
| 7381 | `ExitBlockChk` | open | M2 T24 S2 | S3 |
| 7386 | `BrickQBlockMetatiles` | mapped; evidence incomplete | M2 T24 S2 | S3 |
| 7393 | `BlockBumpedChk` | mapped; evidence incomplete | M2 T24 S2 | S3 |
| 7395 | `BumpChkLoop` | open | M2 T24 S2 | S3 |
| 7400 | `MatchBump` | open | M2 T24 S2 | S3 |
| 7404 | `BrickShatter` | mapped; evidence incomplete | M2 T24 S2 | S4 |
| 7420 | `CheckTopOfBlock` | mapped; evidence incomplete | M2 T24 S2 | S4 |
| 7437 | `TopEx` | open | M2 T24 S2 | S4 |
| 7441 | `SpawnBrickChunks` | mapped; evidence incomplete | M2 T24 S2 | S4 |
| 7468 | `BlockObjectsCore` | mapped; evidence incomplete | M2 T24 S2 | S5 |
| 7500 | `ChkTop` | open | M2 T24 S2 | S5 |
| 7506 | `BouncingBlockHandler` | mapped; evidence incomplete | M2 T24 S2 | S5 |
| 7519 | `KillBlock` | open | M2 T24 S2 | S5 |
| 7520 | `UpdSte` | open | M2 T24 S2 | S5 |
| 7527 | `BlockObjMT_Updater` | mapped; evidence incomplete | M2 T24 S2 | S6 |
| 7529 | `UpdateLoop` | open | M2 T18 S4 | S6 |
| 7546 | `NextBUpd` | open | M2 T18 S4 | S6 |
| 7555 | `MoveEnemyHorizontally` | open | M2 T17 S6 | S7 |
| 7561 | `MovePlayerHorizontally` | open | M2 T17 S6 | S7 |
| 7566 | `MoveObjectHorizontally` | open | M2 T17 S6 | S7 |
| 7581 | `SaveXSpd` | open | M2 T17 S6 | S7 |
| 7586 | `UseAdder` | open | M2 T17 S6 | S7 |
| 7604 | `ExXMove` | open | M2 T17 S6 | S7 |
| 7611 | `MovePlayerVertically` | open | M2 T17 S6 | S8 |
| 7617 | `NoJSChk` | open | M2 T17 S6 | S8 |
| 7624 | `MoveD_EnemyVertically` | ROM-match complete | M2 T31 S2 | S8 retained |
| 7630 | `MoveFallingPlatform` | ROM-match complete | M2 T31 S2 | S8 retained |
| 7632 | `ContVMove` | ROM-match complete | M2 T31 S2 | S8 retained |
| 7636 | `MoveRedPTroopaDown` | open | M2 T17 S6 | S8 |
| 7640 | `MoveRedPTroopaUp` | open | M2 T17 S6 | S8 |
| 7643 | `MoveRedPTroopa` | open | M2 T17 S6 | S8 |
| 7656 | `MoveDropPlatform` | open | M2 T17 S6 | S8 |
| 7660 | `MoveEnemySlowVert` | open | M2 T17 S6 | S8 |
| 7662 | `SetMdMax` | open | M2 T17 S6 | S8 |
| 7667 | `MoveJ_EnemyVertically` | open | M2 T17 S6 | S8 |
| 7669 | `SetHiMax` | open | M2 T17 S6 | S8 |
| 7670 | `SetXMoveAmt` | open | M2 T17 S6 | S8 |
| 7678 | `MaxSpdBlockData` | open | M2 T17 S6 | S9 |
| 7681 | `ResidualGravityCode` | open | M2 T17 S6 | S9 |
| 7685 | `ImposeGravityBlock` | open | M2 T17 S6 | S9 |
| 7691 | `ImposeGravitySprObj` | open | M2 T17 S6 | S9 |
| 7698 | `MovePlatformDown` | open | M2 T17 S6 | S9 |
| 7702 | `MovePlatformUp` | open | M2 T17 S6 | S9 |
| 7711 | `SetDplSpd` | open | M2 T17 S6 | S9 |
| 7719 | `RedPTroopaGrav` | open | M2 T17 S6 | S9 |
| 7729 | `ImposeGravity` | open | M2 T17 S6 | S9 |
| 7739 | `AlterYP` | open | M2 T17 S6 | S9 |
| 7761 | `ChkUpM` | open | M2 T17 S6 | S9 |
| 7784 | `ExVMove` | open | M2 T17 S6 | S9 |

## S1 admission: complete power-up actor state machine

Transfer-154 receives PowerUpObjHandler, GrowThePowerUp and RunPUSubs
(mapped; evidence incomplete), ShroomM, ChkPUSte and ExitPUp (open).
The six-label scope and expected-match set are identical. Baseline 813 /
1,992; maximum 819. Entry $BC85 ends at ExitPUp $BCEA, before the block
Y-adder table. Shared game/power_up.c owns the state machine; the completed
T36 initializer remains game/power_up_init.c. S2-S9 remain unadmitted.

Original semantics: write ObjectOffset=5 even for state zero, branch on the
old state high bit, gate movement on TimerControl, dispatch mushrooms/1-ups
through MoveNormalEnemy then EnemyToBGCollisionDet, and stars through
MoveJumpingEnemy then EnemyJump. Flowers and other type bytes skip movement.
Emergence changes Y/state only on frame low bits zero, compares the old
state to 11, and installs speed10/state80/priority0/direction1. The six-pixel
gate is only on the emergence branch. Every reached RunPUSubs executes
relative, offscreen, box, draw, PlayerEnemyCollision and bounds in that order.
Do not insert an ID/state recheck between collision and bounds.

### S1 existing-code audit and migration map

| Original boundary | Existing C / disposition |
| --- | --- |
| PowerUpObjHandler | Replace objects.c step/prepare body with one source-owned actor; ensure entry ObjectOffset write |
| MoveJumpingEnemy | Extract the existing gravity-then-horizontal body from the ID14 wrapper into a reusable movement child; retain wrapper eligibility outside the child |
| MoveNormalEnemy | Reuse enemy/movement.c entry; remove the actor's private mushroom movement/terrain approximation |
| EnemyJump / EnemyToBGCollisionDet | Reuse enemy/background.c entries; child repair remains outside S1 |
| RelativeEnemyPosition | Use the existing source helper, replacing the private coordinate calculation |
| GetEnemyOffscreenBits / GetEnemyBoundBox | Reuse existing offscreen and enemy_bounds entries without algorithm edits |
| DrawPowerUp | Reuse the existing game OAM child |
| PlayerEnemyCollision | Connect the existing power-up collision child at the common current-slot boundary; do not let the ordinary-enemy default consume power-ups |
| OffscreenBoundsCheck | Always run after collision, including collection/ID changes, with the original child-return slot contract |
| RunEnemyObjectsCore | One actor call; remove its second finish call and the redundant finish API/test stubs |

The old finish routine's ID and state checks are not ROM caller branches.
Its post-collision ID check skips a source child and must disappear. Existing
power-up collision internals, graphics, bounds and movement primitives stay
uncertified unless separately proven; exposing or reconnecting them adds no
child credit. A child-interface change may preserve original outputs needed
by this caller but may not silently repair an unadmitted child algorithm.

ROM evidence uses ordinary NMI enemy dispatch with source-RAM scenarios:
state zero; emergence states around 5/6 and 10/11/12; all four frame phases;
active states, timer on/off, normal/flower/star/extra-life types; collection
and offscreen retirement. Capture actual root/direct-child entry/return RAM,
arguments and branch coverage from real stack PCs/depths. Compare source
caller sequencing separately from actual native child outcomes. Never alter
reference PC, stack, ROM, child returns or resulting output. Independent
native checks exercise byte states, exact writes and continuation after a
child changes object identity. Regress T36 initialization and nearby actor
routes, build all three targets and run bounded hidden-window probes.

Existing owner ROM and reviewed listing are local research inputs with no
redistribution claim or third-party implementation import. Every temporary
artifact stays below ignored build/m2-t37-s1. Reference runs use twenty-second
per-run and four-MB raw batch budgets; S1 owns cleanup through T review.
No platform gameplay branch is permitted. DOS remains link-only. Closure
requires six exact dispositions, both validation tracks, caller sweep,
tracker/ledger and all three artifact hashes. Whole-game parity is not
inferred from this scoped actor proof.

### S1 admission gate and exact source locations

The admission checker passes: scope six, expected six, incoming complete
813 / 1,992, maximum 819. The named incoming rows are PowerUpObjHandler,
GrowThePowerUp and RunPUSubs mapped/incomplete; ShroomM, ChkPUSte and
ExitPUp open. Ledger validation reports zero orphan nodes. Documentation
governance passes. These checks admit work and add no conformance credit.

| Node | Original address | Source branch contract |
| --- | --- | --- |
| PowerUpObjHandler | $BC85 | Fixed slot and zero/high-bit/timer/type dispatch |
| ShroomM | $BCAA | MoveNormalEnemy then EnemyToBGCollisionDet, then common tail |
| GrowThePowerUp | $BCB3 | Frame gate, decrement Y, increment state, compare pre-increment state |
| ChkPUSte | $BCD2 | Emergence-only threshold six |
| RunPUSubs | $BCD8 | Six direct children in original order, no post-collision guard |
| ExitPUp | $BCEA | Return to original caller |

Direct child addresses from the reviewed original symbol map:
MoveJumpingEnemy $CAF9, EnemyJump $E163, MoveNormalEnemy $CA77,
EnemyToBGCollisionDet $DFC1, RelativeEnemyPosition $F152,
GetEnemyOffscreenBits $F1AF, GetEnemyBoundBox $E243, DrawPowerUp $E6D2,
PlayerEnemyCollision $D853 and OffscreenBoundsCheck $D67A. Use these
original entries for observation; old approximate addresses in legacy C
comments are not the reference authority.

## S1 original power-up actor proof

S1/P1 completes the six received actor nodes, expected six, with no transfer:
PowerUpObjHandler, ShroomM, GrowThePowerUp, ChkPUSte, RunPUSubs and ExitPUp.
Conformance moves from 813 to 819 / 1,992. This is proof of the actor's own
branches, writes and child-call order; it is not a certificate for child
algorithms or whole-game equivalence.

### Original logic and node dispositions

The reviewed original interval is $BC85-$BCEA, exclusive end $BCEB.
The shared owner is src/game/power_up.c. No imported translation is used.

| Complete node | Source/C correspondence and original evidence |
| --- | --- |
| PowerUpObjHandler | Sets ObjectOffset=5 before inactive return; state high-bit, timer and exact type 0/3/2 branches select the original children. |
| ShroomM | MoveNormalEnemy then EnemyToBGCollisionDet before the common tail; no private mushroom terrain implementation remains. |
| GrowThePowerUp | FrameCounter low two bits gate Y decrement/state increment; old state >=$11 writes speed $10, state $80, attributes 0 and direction 1. |
| ChkPUSte | Only the emergence path compares current state against six; inactive/active paths retain their separate source decisions. |
| RunPUSubs | Relative position, offscreen bits, bounding box, drawing, player collision and bounds run in that exact order, including bounds after collection. |
| ExitPUp | All original exits return to the current-slot actor caller; the extra finish-tail entry and post-collision ID guard are removed. |

Fifty source-RAM scenarios enter through ordinary NMI enemy dispatch,
fixture IDs 1596-1645. The recorder observes real root/child stack boundaries;
it does not change PC, stack, ROM, child returns or resulting output. Nine
conditional source sites cover both outcomes; all six labels and all ten
child IDs execute. Observation, coverage and unobserved frame outputs agree.
The four collection and two offscreen cases retire the original slot.

Both native widths match all 100 caller comparisons across 1,791 persistent
RAM bytes (scratch 0-7 and hardware stack excluded, except persistent
$0133-$0139). Caller checks replay observed original child results only at
native child seams; they do not prove child interiors. Independent native
checks cover 10,240 combinations per width, including continuation after a
collision clears ID/state, and check the full 2,048-byte write footprint.

### Actual-child failures retained

Actual native children produce 84 matches and 16 failures across both widths.
Independent child entry/return diagnostics identify the same differences:

| Cases per width | Responsible original child | Exact mismatch and disposition |
| --- | --- | --- |
| 29, 33, 37, 41, 45 | DrawPowerUp | OAM $020E is $21 instead of $61: flower flip attribute. Retain existing M2 T17 S6 custody for source-order graphics admission. |
| 48, 49 | DrawPowerUp | Offscreen OAM Y bytes $0200/$0204/$0208/$020C/$0210/$0214 are not hidden to $F8. Same existing graphics receiver. |
| 46 | PlayerEnemyCollision / HandlePowerUpCollision | Star collection leaves AreaMusicQueue $FB at $00 instead of $40. Retain existing M2 T17 S6 collision custody. |

No failed actual-child result is counted as a passing integrated route.
These child nodes were not received by S1 and receive no new credit.

### Operational checks and similar-issue sweep

- All 76 shared C units compile under strict C90 for x86 and x64; both
  executable self-tests pass. Hidden two-second window probes create MySMB
  windows and answer WM_NULL without global input or desktop interaction.
- Twenty surrounding regression runs and twelve directly affected runs pass
  across both widths, including collision, enemy dispatcher, cannon children,
  power-up initialization and actor lifetime. Initialization retains 71,680
  cases per width and 72 residual dispatch cases per width.
- The collision fixture initially failed at return 3: its legacy partial-actor
  setup omitted enemy ID/flag and visible screen bounds. The full actor now
  consumes those source-owned inputs. Supplying them restores the existing
  collision assertions without changing production collision algorithms.
  The flower test now observes state five before executing the complete
  state-six collection frame instead of manually calling the removed tail.
- The sweep removes all finish-tail calls/stubs and private actor movement,
  terrain and relative-position duplicates; the enemy dispatcher enters the
  actor once. The shared current-slot collision entry now selects the existing
  power-up child. The jumping movement extraction preserves its two existing
  child calls and grants no child conformance credit. Platform purity passes.
- OpenNT DOS16 compiles and links with the existing OLDNAMES library warning.
  DOS still lacks resource binding: this is link evidence, not playability,
  graphics or 486SX performance qualification. Prior core/full-frame and
  other recorded child debts remain incomplete.

Reproduction: build the CMake mysmb_power_up_actor_smoke,
mysmb_power_up_actor_snapshot_check, mysmb_power_up_actor_caller_check and
mysmb_power_up_actor_child_check targets with the owner-local ROM binding.
Record fixtures 1596-1645 using reference_frame_recorder's
--power-up-actor-snapshot option, and run
`python test/verify_power_up_actor_snapshots.py <ignored-directory> <owner-rom>`.
The child checker consumes each corresponding .calls file. Raw artifacts
remain ignored and bounded under build/m2-t37-s1; no raw RAM is committed.

Three owner-authorized test executables are refreshed with this P. These
are local test delivery, not redistributable release or M2 closure evidence.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256943 | accdc9451d6dd8769316c315915f66931ce4fcf7dac2446e12e310abf470bc71 |
| mysmb32.exe | 329522 | b99e2c1017b1daf9c4e747e92d56d10cdc2ac65897959e619eb09172012e5fd9 |
| mysmb64.exe | 336853 | e64645f0deeed4465e8d84914ac960ac8bb0a3fa19fa6419276ea39da357f9b8 |

Retained raw evidence: 2755008 bytes, below four MB. S1 closes; S2 is next, not yet admitted.


## S2 admission: head-hit and block positioning

After S1 commit d722829, receive thirteen labels from M2 T24 S2 by accepted
transfer-155. Baseline 819 / 1,992; expected thirteen, maximum 832. The shared
owner will be game/blocks/head.c. S3/S4 bump, lookup and shatter children
retain their existing custody until their planned source-order admissions.

| Label | Incoming status | Expected disposition |
| --- | --- | --- |
| BlockYPosAdderData | open | ROM-match complete after both proof tracks |
| PlayerHeadCollision | mapped; evidence incomplete | ROM-match complete after both proof tracks |
| DBlockSte | open | ROM-match complete after both proof tracks |
| ChkBrick | open | ROM-match complete after both proof tracks |
| StartBTmr | open | ROM-match complete after both proof tracks |
| ContBTmr | open | ROM-match complete after both proof tracks |
| PutOldMT | open | ROM-match complete after both proof tracks |
| PutMTileB | open | ROM-match complete after both proof tracks |
| SmallBP | open | ROM-match complete after both proof tracks |
| BigBP | open | ROM-match complete after both proof tracks |
| Unbreak | open | ROM-match complete after both proof tracks |
| InvOBit | open | ROM-match complete after both proof tracks |
| InitBlock_XY_Pos | mapped; evidence incomplete | ROM-match complete after both proof tracks |

### Source contract and implementation boundary

Audit the contiguous $BCEB table and PlayerHeadCollision through
InitBlock_XY_Pos, ending before BumpBlock. Preserve the incoming metatile
independently from the later buffer read; set block state before
DestroyBlockMetatile, reload SprDataOffset_Ctrl after that child, save row
and low pointer, then read the actual pointed byte. Preserve lookup carry
across the size branch. Implement coin timer first-use, running and expired
paths; coordinate addition preserves carry across AND; blank the buffer only
after InitBlock_XY_Pos. Set bounce timer and original-metatile scratch before
size/crouch Y alignment, dispatch BumpBlock or BrickShatter, then reload and
invert the control byte after the child.

Existing code incorrectly merges all this with child behavior, computes
lookup from the incoming argument before DestroyBlockMetatile, and blanks
the RAM before the VRAM child. Extract the head owner and explicit child
seams. The existing bump/shatter interiors may be moved intact to expose
those seams; no S3/S4 node receives completion credit or algorithm repair.
Preserve the existing public head-hit adapter for player callers and tests.
Audit every adapter call and every block-position writer for duplicate
ownership. No platform gameplay changes are permitted.

### Dual proof and delivery

The ROM track checks the two table bytes, each branch/read/write and child
order from the original listing and ROM. Source-RAM scenarios enter through
ordinary NMI/player head collision, never a forced PC/stack entry. Cover both
sizes and crouch, slots, matching/nonmatching blocks, first/running/expired
coin timers and X/Y wrapping. Observe original direct-child entry/return
state and root exit; report caller equivalence separately from actual child
failures. Do not mask a child discrepancy or count it as parent-wide gameplay
parity. The operational track checks a focused native callback/coordinate
matrix, collision and block regressions, x86/x64 strict C90, DOS16 link,
platform purity, hidden-window responsiveness and all three EXEs per P.

Existing owner ROM and locally reviewed listing remain ignored research
inputs with no redistribution claim or third-party implementation import.
All temporary outputs stay below build/m2-t37-s2. Recorder budgets are twenty
seconds per process and four MB raw per batch; S2 owns cleanup through T
review. Only source input RAM may be set; never reference outputs or child
return values. Every label needs both tracks before tracker promotion.
DOS remains link-only; whole-game and retained child failures remain open.

### S2 implementation checkpoint, not closure

The named admission and documentation gates pass at baseline 819, scope and
expected thirteen, maximum 832. The shared head owner and existing public
adapter now live in game/blocks/head.c; the old monolithic head body has been
removed. Existing bump/shatter child bodies remain in objects.c behind
explicit declarations for their S3/S4 migration, without child credit.
CMake and OpenNT source lists include the new owner.

The original two bytes at $BCEB match the bound Y-adder data. Strict C90
native checks pass on both widths: 131,072 coordinate/page/slot cases and
sixteen child-order cases per width. A child deliberately changes the control
byte and buffer between entry and read, ensuring the caller reloads them;
another changes control before the final XOR. These synthetic native tests
are operational evidence, not a replacement for original-ROM observations.
Platform purity and diff whitespace checks pass.

Still required before S2 closure: original NMI root/child recording and branch
coverage, actual-child diagnostics, collision/block integration regressions,
all three final executable builds, hidden-window probes, node-by-node proof,
tracker update and P commit. Completion remains 819 / 1,992; the packaged
EXEs still belong to committed S1 d722829.

## S2 original head-hit and positioning proof

S2/P1 proves all thirteen received labels, expected thirteen, no transfers.
The shared owner is game/blocks/head.c. Conformance changes from
819 to 832 / 1,992. The table and caller/coordinate nodes are complete;
BumpBlock, BlockBumpedChk and BrickShatter interiors receive no credit here.

### Original source and node proof

| Node | Address | Source semantics preserved |
| --- | --- | --- |
| BlockYPosAdderData | $BCEB | Both original bytes verified against the owner ROM; consumed for size/crouch alignment. |
| PlayerHeadCollision | $BCED | Preserve incoming metatile; state write precedes DestroyBlockMetatile; reload control and pointed block after the child. |
| DBlockSte | $BCFA | Size-selected state, original row/low-pointer writes, buffer read and lookup in source order. |
| ChkBrick | $BD1A | Preserve lookup carry across player-size selection; matched blocks force state $11 and default replacement $C4. |
| StartBTmr | $BD2C | First multi-coin hit writes timer $0B and increments its flag only when clear. |
| ContBTmr | $BD39 | Running timer retains tile; expired timer selects $C4. |
| PutOldMT | $BD40 | Transfer selected old/empty tile to the replacement write. |
| PutMTileB | $BD41 | Replacement, coordinate child, blank buffer, bounce timer, saved original tile and size/crouch decision in that order. |
| SmallBP | $BD61 | Select adder index one for small or crouching player. |
| BigBP | $BD62 | Byte Y addition and high-nibble alignment precede state-dependent bump/shatter dispatch. |
| Unbreak | $BD78 | Call BumpBlock only for state $11. |
| InvOBit | $BD7B | Reload and invert control after the child returns. |
| InitBlock_XY_Pos | $BD84 | X+8 carry survives AND and increments page; copy page and player high Y. |

Seventy-two source-RAM scenarios enter through ordinary NMI/player collision,
fixture IDs 1646-1717. They cover both slots, small/big/crouching states,
ordinary/question/hidden/coin blocks, first/running/expired timers and X-page
carry. All twelve code labels execute; all ten conditional sites exercise
both outcomes. Observer-enabled, coverage and unobserved frame outputs agree.
No PC, stack, ROM, original child return or output is altered.

Across x86/x64, 144 caller comparisons match over 1,791 persistent RAM bytes;
scratch 0-7 and hardware stack are excluded except persistent $0133-$0139.
Original observed child returns are replayed only at native seams for caller
proof. Actual native children are tested separately: 128 matches, 16 failures.
Independent child entry/return checks isolate all failures to BrickShatter:
cases 12/13/24/25/48/49/60/61 per width copy a second chunk high-Y byte to
$00C0/$00C1 (original zero, native one), omit NoiseSoundQueue $FD=$01 and
incorrectly set Square1SoundQueue $FF=$02. Retain BrickShatter/SpawnBrickChunks
with existing M2 T24 S2 custody until planned T37 S4 receipt. These are failed
integrated comparisons, not passing gameplay routes or transferred S2 nodes.

### Native verification, sweep and delivery

Independent native tests pass 131,072 coordinate/page/slot cases and sixteen
callback-order cases per width. The latter deliberately change control/buffer
inside child calls, checking reloads and preservation of the incoming tile.
Thirty-two related/surrounding regression runs pass across both widths.
The initial collision regression stopped at 47 because the old direct-call
fixture supplied only a metatile argument, leaving its source buffer empty.
The fixture now supplies the original buffer input; expectations are unchanged.
The array-layout direct-call fixtures were corrected the same way.

The caller sweep finds one production head adapter caller in player.c and two
original coordinate consumers: head collision and ChkOverR's entrance-vine
setup. Both now use the same coordinate owner; the duplicated entrance body
is removed without changing its setup-vine sequence. The native coordinate
matrix covers every X/page pair and both slots; vine setup and mode
regressions pass. Existing bump/shatter bodies were exposed intact for later
migration; no child repair is smuggled into this caller proof.

All 77 shared units compile as strict C90 on x86/x64. Both executable self-tests
and bounded hidden-window creation/WM_NULL probes pass. Platform purity passes.
OpenNT DOS16 compiles/links with the retained OLDNAMES warning. It still lacks
resource binding and has no playable-runtime or 486SX qualification claim.
Prior core/full-frame and other child debts remain open.

Reproduce with CMake mysmb_block_head_smoke, mysmb_block_head_snapshot_check,
mysmb_block_head_caller_check and mysmb_block_head_child_check. Record
`--fixture=t37-head=N` (0-71) with `--block-head-snapshot=...` and
`--control-children=...`; run coverage separately using `--pc-coverage=...`.
Run `python test/verify_block_head_snapshots.py <ignored-directory> <owner-rom>`.
Raw snapshots remain ignored below build/m2-t37-s2, within the four-MB budget.
The tracked record contains only neutral findings, addresses and artifact hashes.

Three owner-authorized EXEs accompany this P as local testing artifacts, not
redistributable release or M2 closure evidence.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257345 | d203e2ab11aa686be94027fe2173ac0cdebd9421cb56a3870db519b9f7d4a4ee |
| mysmb32.exe | 330054 | ddc52a274e1e0475fcc68b33a75a93af0b7c3a0abd2cd33a5f7a4a6f19da2d83 |
| mysmb64.exe | 337416 | aa18e8e322e55da9c3090449110d481b8ab2abdc6b92839d61cd68491feea124 |

Retained raw evidence: 3905357 bytes. S2 closes; S3 block bump/content/lookup is next, not yet admitted.


## S3 admission: block bump, contents and lookup

After S2 commit baae695, transfer-156 receives eleven incomplete labels from
M2 T24 S2. Baseline 832 / 1,992; expected eleven, maximum 843. Shared owner:
game/blocks/bump.c. S2 consumes the lookup through its declared interface;
CheckTopOfBlock and shatter remain planned S4 dependencies. CoinBlock,
SetupPowerUp and Setup_Vine retain their accepted shared owners.

| Label | Incoming status | Expected disposition |
| --- | --- | --- |
| BumpBlock | mapped; evidence incomplete | Complete after both proof tracks |
| BlockCode | mapped; evidence incomplete | Complete after both proof tracks |
| MushFlowerBlock | open | Complete after both proof tracks |
| StarBlock | open | Complete after both proof tracks |
| ExtraLifeMushBlock | open | Complete after both proof tracks |
| VineBlock | open | Complete after both proof tracks |
| ExitBlockChk | open | Complete after both proof tracks |
| BrickQBlockMetatiles | mapped; evidence incomplete | Complete after both proof tracks |
| BlockBumpedChk | mapped; evidence incomplete | Complete after both proof tracks |
| BumpChkLoop | open | Complete after both proof tracks |
| MatchBump | open | Complete after both proof tracks |

Audit $BD9B-$BE01, including the nine-word BlockCode vector, overlapping BIT
entry bytes and fourteen table bytes. BumpBlock first calls CheckTopOfBlock,
then initializes bump sound, block X speed, Y force, player Y speed and block
Y speed. It reloads scratch $05 after that child, searches the original table
backward from index thirteen and exits on carry-clear. Found indices >=9
subtract five before dispatch. Preserve all nine dispatch entries, power-up
type writes, coin carry zero and the vine slot-five/control-index contract.

Replace duplicated metatile classifications with this lookup and vector;
return the original index/no-match status explicitly to both head and bump
callers. Move the existing table definition to the shared block owner without
changing its area-parser consumers. Expose the existing top-of-block child
without repairing its internals; record actual-child differences for S4.
No shatter, gravity, platform or unadmitted graphics repair belongs here.

ROM proof uses ordinary NMI source-RAM head-hit scenarios covering all table
entries, no-match, both slots and coins above. Observe real child boundaries,
lookup result/branches, dispatch and byte writes; do not set PC, stack, ROM,
reference child returns or outputs. Separate caller proof from actual-child
results and recheck the accepted S2 routes after the lookup API change.
Native checks independently cover all 256 lookup inputs, child-call ordering,
all dispatch targets and exact state writes; run focused regressions, strict
C90 x86/x64, DOS16 link, platform purity, hidden-window probes and three EXEs.

The owner-local ROM and reviewed listing remain ignored research inputs with
no redistribution claim or imported implementation. All temporary outputs
stay under build/m2-t37-s3. Recorder budgets: twenty seconds per process,
four MB raw per batch; S3 retains cleanup responsibility through T review.
Each node needs both tracks before inventory promotion. DOS remains link-only.

### S3 implementation checkpoint, not closure

Admission/ledger/documentation gates pass at 832, scope eleven, maximum 843.
The shared bump owner now clears Block_X_Speed, performs CheckTopOfBlock
before initialization and the $05 read, searches from index thirteen down,
normalizes indices 9-13 and executes the complete nine-entry content vector.
The former coin/power/vine metatile classifications are removed. The one
fourteen-byte table definition moves from area/block_metatile.c to blocks/bump.c;
existing parser consumers keep its shared declaration. Head collision uses
the same lookup with explicit original Y/no-match result. The existing
CheckTopOfBlock body is exposed unchanged for planned S4, not certified here.

Owner-ROM data audit matches all fourteen bytes at $BDE8, all nine little-
endian targets at $BDC0 and the overlapping BIT entry bytes at $BDD2-$BDD9.
Strict C90 focused checks pass on both native widths: 256 lookup values and
512 dispatch/full-RAM write cases per width. S2's 131,072 coordinate cases
and sixteen child-order cases per width also pass after the lookup interface
change. Platform purity passes. CMake/OpenNT source lists include the new
owner, and CMake registers the focused bump test.

Still required: source-reachable NMI proof for every table/dispatch branch
and coin-above handoff, actual-child diagnostics, rechecking S2 original
snapshots, final related regressions, three target builds/artifacts, window
probes and node accounting. No node is promoted yet. Packaged EXEs remain
the committed S2 baae695 versions, and S3 has no P commit yet.

## S3 original block content and lookup proof

S3/P1 completes all eleven received labels, expected eleven, no transfers.
Conformance moves from 832 to 843 / 1,992. The shared owner is
src/game/blocks/bump.c; original table consumers retain one data definition.

| Complete node | Original address | Proven source contract |
| --- | --- | --- |
| BumpBlock | $BD9B | CheckTopOfBlock first, then sound/X-speed/force/player-speed/Y-speed writes, then reload $05 and lookup. |
| BlockCode | $BDBD | Preserve original index; subtract five only for indices 9-13; nine dispatch words match original ROM. |
| MushFlowerBlock | $BDD2 | Type zero entry and shared SetupPowerUp tail; BIT overlap bytes audited. |
| StarBlock | $BDD5 | Type two entry with original shared tail. |
| ExtraLifeMushBlock | $BDD8 | Type three entry and $39 write before SetupPowerUp. |
| VineBlock | $BDDF | Enemy slot five, block index from SprDataOffset_Ctrl, then Setup_Vine. |
| ExitBlockChk | $BDE7 | Original no-match and vine return behavior. |
| BrickQBlockMetatiles | $BDE8 | All fourteen original bytes and their parser/bump consumers bind to one definition. |
| BlockBumpedChk | $BDF6 | Start at original index thirteen and return index plus carry meaning. |
| BumpChkLoop | $BDF8 | Descending compare/decrement loop; all fourteen matches and no-match covered. |
| MatchBump | $BE01 | Match preserves carry-set meaning; exhausted lookup returns $FF/carry-clear. |

Sixty source-RAM scenarios enter the original BumpBlock through ordinary
NMI/player head collision, fixture IDs 1718-1777: fourteen table entries and
one unmatched brick, both block slots, with and without a coin above. All ten
code labels execute and all four conditional sites take both outcomes. Thirty
coin-above scenarios increment the original coin tally. The original top
child overwrites $05 in those scenarios; the caller's post-child lookup follows
that value, rather than a cached entry metatile. Every direct child target is
observed. Observer-enabled, coverage and unobserved frame outputs agree.

Both native widths match all 120 caller comparisons, all 120 actual-child
root comparisons and all 120 independent child snapshot checks. The compared
1,791 persistent RAM bytes exclude scratch 0-7 and hardware stack except
$0133-$0139. Source audit and focused write tests additionally verify the
scratch-dependent lookup and argument handoffs. No reference PC, stack, ROM,
child result or output is modified. Caller tests replay observed child results
only at native seams; actual-child checks run the real shared implementations.
Passing this bounded matrix gives no unrelated child-node completion credit.

The accepted S2 snapshot matrix is rechecked after the lookup interface change:
144 caller matches and 128 actual matches; the same sixteen BrickShatter
failures remain byte-for-byte identical and stay assigned to planned S4.
No S2 claim is silently replaced by a synthetic test.

Native tests pass 256 lookup values and 512 dispatch/full-RAM write cases per
width, plus S2's 131,072 coordinate and sixteen callback cases per width.
Thirty-two related/surrounding regression runs pass. All 78 shared units
compile under strict C90 for x86/x64, executable self-tests and bounded hidden
window/WM_NULL probes pass, and platform purity passes. OpenNT DOS16 links
with the retained OLDNAMES warning. DOS remains without resource binding and
has no playable-runtime or 486SX qualification claim.

The similar-issue sweep removes all separate coin/power/vine metatile
classification helpers and the forward boolean lookup. Head and bump now use
one reverse-index lookup, while parser consumers use the same relocated
fourteen-byte table. Existing CheckTopOfBlock is exposed unchanged, and the
shatter body stays for S4. No host adapter owns any part of this game logic.
Prior full-frame/core and unrelated child debts remain open.

Reproduction: build mysmb_block_bump_smoke, mysmb_block_bump_snapshot_check,
mysmb_block_bump_caller_check and mysmb_block_bump_child_check. Record
`--fixture=t37-bump=N` (0-59) with `--block-bump-snapshot=...` and
`--control-children=...`; run coverage separately using `--pc-coverage=...`.
Run `python test/verify_block_bump_snapshots.py <ignored-directory> <owner-rom>`.
Raw snapshots remain ignored below build/m2-t37-s3 within the four-MB budget.

The three owner-authorized local test EXEs are refreshed with this P; they
are not redistributable release evidence or a claim that M2 is complete.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257089 | c617a5019b091600a2a3a4facba3f1c3cd5b96f90b441fec831e4b88b1f8eab5 |
| mysmb32.exe | 330061 | 0ef6e50ae26799960750612036f042ba0ce9b9b475ec60d3ad9a4d7fda3308b3 |
| mysmb64.exe | 337974 | d1b72a1b13b182e2536ee40de1358fc3426f7fd7970b803ec9a79097f683c5c6 |

Retained raw evidence: 2834812 bytes. S3 closes; S4 shatter/coin-above/chunks is next, not yet admitted.


## S4 admission: shatter, top coin and chunk creation

After S3 commit ae6fc0a, accepted transfer-157 receives four incomplete labels
from M2 T24 S2. Baseline 843 / 1,992; expected four, maximum 847. Shared owner:
game/blocks/chunks.c. This connected source group also resolves the S2
BrickShatter child debt; no separate corrective S is allocated.

| Label | Incoming status | Expected disposition |
| --- | --- | --- |
| BrickShatter | mapped; evidence incomplete | Complete after both proof tracks |
| CheckTopOfBlock | mapped; evidence incomplete | Complete after both proof tracks |
| TopEx | open | Complete after both proof tracks |
| SpawnBrickChunks | mapped; evidence incomplete | Complete after both proof tracks |

Original range $BE02-$BE6F: BrickShatter first checks the top coin, writes
replacement flag and NoiseSoundQueue=$01, spawns chunks, sets player Y speed
$FE before the five-point-digit modifier and AddToScore, then reloads control.
CheckTopOfBlock reloads control, returns at row zero, otherwise subtracts $10
and writes scratch $02 even without a coin. It reads through the original
$06/$07 pointer, removes only $C2 before RemoveCoin_Axe, reloads control and
calls SetupJumpCoin. No cached pre-child scratch may replace the live values.
SpawnBrickChunks retains its exact coordinate/speed/force writes and redundant
$FA write; it does not copy the second chunk's Y high byte.

Remove the old merged shatter implementation from objects.c. Keep score,
coin allocation and VRAM children in their existing owners; no child repair
or new credit belongs here. Audit every head/bump top-coin caller, chunk field
writer, sound write and score ordering. Platform code stays unchanged.

ROM proof uses source-RAM ordinary NMI/head-hit routes and real root/direct-
child observations. Cover both slots, no-coin/coin/top-row-zero paths and
coordinate wrapping. Revalidate the complete accepted S2/S3 matrices, retain
unexplained differences and require the sixteen known shatter differences to
resolve rather than weaken their expectations. Separate actual-child proof
from caller seams. Native checks verify the full write footprint, preservation
of second Y high, scratch and child order; run focused regressions, strict
C90 x86/x64, DOS16 link, platform purity, bounded window probes and three EXEs.

Owner-local ROM/listing remain ignored research inputs with no redistribution
claim or imported implementation. Keep all temporary artifacts below
build/m2-t37-s4; limit each recorder to twenty seconds and each raw batch to
four MB. S4 owns cleanup through T review. Never alter reference PC, stack,
ROM, child returns or outputs. Four exact node dispositions, both tracks,
tracker/ledger and artifact hashes are required before closure. DOS remains
link-only; unrelated/full-game failures remain open.

### S4 implementation checkpoint, not closure

Admission, ledger and documentation gates pass at 843, scope/expected four,
maximum 847. The original shatter/top-coin/chunk group now has one shared
blocks/chunks.c owner. It replaces the merged approximations in objects.c.
The original noise sound, replacement flag, player-speed-before-score order,
row-offset write on misses, full pointer read and second Y-high preservation
are restored. Bump/head callers retain the same declared child contracts.

Strict C90 focused tests pass on x86/x64: 512 full-RAM chunk footprints,
64 no-coin/zero-row paths and four coin/shatter child-order cases per width.
Actual original-root revalidation now matches all 144 S2 and all 120 S3
comparisons. The sixteen prior S2 BrickShatter differences are gone without
changing their recorded original expectations. This is a concrete resolution
candidate, not S4 closure: the dedicated S4 original-node coverage, final
regressions and all three delivered artifacts are still required.

Platform purity passes. No node count is changed yet; completion remains
843 / 1,992. Assets still contain the committed S3 ae6fc0a executables.


## S4 original shatter, top-coin and chunk proof

S4/P1 proves the four received caller/local nodes: BrickShatter,
CheckTopOfBlock, TopEx and SpawnBrickChunks. Expected four, actual four;
no scoped node transfers. Progress 843 -> 847 / 1,992. This credits the
local branches, writes and calls, not equivalence of their child interiors.

| Original node | Shared C mapping and source contract |
| --- | --- |
| BrickShatter $BE02-$BE1E | blocks/chunks.c: check top first, replacement/noise=1, spawn, player speed=$FE before digit modifier=5 and score; caller reloads control at its continuation. |
| CheckTopOfBlock $BE1F-$BE3F | Reload control; row-zero return; subtract $10 into $02 even on a miss; full $06/$07 indirect read; only $C2 cleared, before RemoveCoin_Axe then SetupJumpCoin with reloaded slot. |
| TopEx $BE40 | Shared return reached by zero-row, noncoin and coin paths. |
| SpawnBrickChunks $BE41-$BE6F | Original position/page, speed/force writes including repeated $FA; low-Y plus eight wraps without writing either high-Y byte. |

Sixteen ordinary NMI/head-hit scenarios cover both slots, byte wrap,
zero-row/noncoin/coin paths. All four original PCs are reached; both branch
sites have taken and fallthrough observations. Observed and unobserved frame
outputs and separately collected coverage snapshots are byte-identical.
No original PC, stack, child return or output is patched. Native caller
checks consume separately recorded original child returns; that seam proof
is explicitly separate from native actual-child execution.

Both widths yield 32 caller matches comparing 1,794 RAM bytes (including
scratch $02/$06/$07). All 32 actual executions match the previous 1,791-byte
persistent comparison, but all 32 FAIL the expanded comparison at $02.
Independent child snapshots isolate AddToScore in all sixteen cases and
SetupJumpCoin additionally in cases 8-11. No other compared byte differs.
This is retained evidence, not a green full-chain result. Existing score
(T36 S5), coin (T36 S3) and status-output (T28 S7) maintenance responsibilities
remain; the deeper faulty instruction is not established by these boundaries.

Rechecking the final build against the unchanged S2/S3 original snapshots
matches all 144 head-hit and all 120 bump/content roots. The sixteen prior
S2 BrickShatter differences are resolved; earlier narrower evidence does
not certify the newly checked child scratch bytes.

Operational evidence: strict C90 x86/x64 focused checks pass 512 full-RAM
chunk footprints, 64 row paths and four child-order cases per width. All
head/bump focused regressions also pass on both widths: 131,072 coordinate
cases, 16 head child-order cases, 256 lookups and 512 bump dispatch/write cases.
All
32 surrounding regression runs pass. Both final Windows builds compile 79
shared units, pass input self-test, create a hidden window and respond to a
bounded message probe. DOS16 links with the existing OLDNAMES warning and
remains link-only, with no playable or physical 486SX qualification claim.
Platform purity passes; no platform implementation changes.

The similar-issue sweep covers all head/bump top-coin callers, old shatter
and chunk writers, sound queues and score order. Remove the old merged
bodies from objects.c; one chunks.c owns the original group. Block lifetime,
gravity, score, coin and graphics interiors remain their declared successors.
Known full-frame and unrelated child debts remain open.

Reproduce using mysmb_block_chunks_smoke and the snapshot/caller/child
check targets. Record `--fixture=t37-chunks=N` (0-15),
`--block-chunks-snapshot=...`, and `--control-children=...`; collect
`--pc-coverage=...` separately. Run
`python test/verify_block_chunks_snapshots.py <ignored-directory> <owner-rom>`.
The verifier reports expanded failures rather than suppressing them. Final
S2/S3 checkers consume the original retained head/bump snapshots. All raw
research and build evidence stays below ignored build/m2-t37-s4.

Three owner-authorized test artifacts follow. They are not redistributable
release evidence or a claim that M2 is complete.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256977 | 9c69b77766cc0c34e5440aa396f908ac58198e61a73179a38b9ee59f7d396b45 |
| mysmb32.exe | 330270 | f83c2d3f86dd230e1657f129d35e2e9f9f78ee439f25781a5cfae1621968ac0f |
| mysmb64.exe | 338219 | d4663710a7a83fb097120ef4b4180906f97622a010547f2076f784be9bf8990e |

Retained raw evidence: 756772 bytes. S4 closes; S5 block lifetime is next, not yet admitted.


## S5 admission: block and brick-chunk lifetime

S4 closed in d6fb78f. Transfer-158 receives five incomplete labels from
T24 S2: BlockObjectsCore, ChkTop, BouncingBlockHandler, KillBlock and UpdSte.
Baseline 847 / 1,992; expected five, maximum 852. BlockObjectsCore and
BouncingBlockHandler are mapped but incomplete; the other three are open.
Shared owner: game/blocks/lifetime.c.

Original $BE70-$BED3 preserves inactive-state store, the saved low nibble,
and block-to-SprObject offset conversion. The chunk path calls gravity and
horizontal movement for both objects, reloads ObjectOffset, then relative,
offscreen and chunk drawing. High-Y zero retains saved state; otherwise
clamp only a second Y greater than $F0, and retire when first Y >= $F0.
Bounce calls gravity, reloads ObjectOffset, relative/offscreen/DrawBlock,
then checks low-Y nibble: below five sets replacement and clears state.
All returns store the selected state at the live block slot.

Move the existing public step entry out of objects.c. Remove its duplicate
horizontal algorithm in favor of the existing shared SprObject movement
entry. This gives no movement or gravity credit: S7/S9 own those algorithms.
Keep the existing block-relative/offscreen/draw children. If their register
return contract needs representation, expose that seam without changing the
child algorithm. Predecessors are block initialization/bump/shatter; next is
S6 metatile replacement. Audit all block-step callers, slot reloads and
movement/draw order. Platforms remain unchanged.

Use ordinary NMI GameEngine block-slot routes with source-RAM fixtures for
inactive, bounce, paired chunks, wrap, high-Y zero and threshold boundaries.
Read-only root/direct-child observers reuse the existing recorder machinery.
Separate caller proof from actual-child differences; no altered original PC,
stack, ROM, return or output. Cover every original node and both outcomes of
conditional branches. Independent native tests check full write footprint,
call order, saved state and reload behavior. Run strict C90 x86/x64,
applicable regressions, DOS16 link, platform purity, bounded hidden-window
probes and refresh three owner-authorized EXEs at P closure.

Existing owner-local ROM/listing are local research inputs without a
redistribution claim; no third-party implementation import. All raw traces,
logs and intermediate outputs stay below ignored build/m2-t37-s5, capped
at four MB raw evidence and twenty seconds per recorder run. S5 owns cleanup.
Record exact node disposition, both proof tracks, residual responsibilities,
tracker/ledger and hashes. DOS remains link-only; child and full-game failures
must remain explicit. No out-of-scope repair or completion credit.


## S5 original block lifetime proof

S5/P1 completes BlockObjectsCore, ChkTop, BouncingBlockHandler, KillBlock
and UpdSte: expected five, actual five, no scoped transfers. Progress is
847 -> 852 / 1,992. Caller/local control-flow proof does not certify child
interiors or the complete game.

| Node | Shared C mapping and original contract |
| --- | --- |
| BlockObjectsCore $BE70 | blocks/lifetime.c: inactive state store; saved low nibble; select bounce or paired chunk path; original gravity/movement calls with block/SprObject offsets and ObjectOffset reload. |
| ChkTop $BEAA | First chunk Y >= $F0 retires; otherwise preserve saved low state. Second Y is clamped only above $F0 before this check. High-Y zero bypasses both checks and retains state. |
| BouncingBlockHandler $BEB3 | Gravity, reload, relative, offscreen, DrawBlock; low Y nibble below five writes replacement flag and retires. |
| KillBlock $BECF | Set selected state to zero without an additional replacement write on the chunk path. |
| UpdSte $BED1 | Store selected state, including the inactive path, to the current block slot and return. |

The original instruction stream $BE70-$BED3 is authoritative where comments
misdescribe high-Y zero as killing the object. All original nodes are observed
through 32 source-RAM ordinary NMI/GameEngine scenarios selecting both slots.
Six conditional branches have both outcomes. BCS at $BEB1 is only reached
after the preceding BCC falls through, with no intervening carry mutation;
its taken-only observation is justified by the original bytes, not a missing
scenario disguised as two-way coverage.

Read-only root and direct-child observations use real stack returns, with no
CPU/ROM/stack/output redirection. Separately observed and unobserved frame
outputs and coverage snapshots are byte-identical. The x86/x64 caller checks
match 64/64 across 1,791 persistent RAM bytes including OAM. Scratch $00-$07
and CPU stack are outside this comparison; native tests verify this caller
has no scratch write. Original child-return substitution is confined to the
caller test executable, never reference execution or production.

Actual native roots match 30/64 and retain 34 OAM-only failures. Independent
child entries isolate DrawBlock in cases 4/6/8/10 and DrawBrickChunks in
3/13/15/17/19/20/21/23/25/27/28/29/31, on both widths. Differences concern
sprite hiding and mirrored X coordinates; no other compared RAM differs.
Keep these exact failures with existing M2 T17 S6 drawing custody until
source-order graphics admission. No graphics repair or child completion
credit is claimed here. Existing scratch/score and full-frame debts remain.

Independent strict-C90 tests pass 131,090 full state/write cases and two
live-slot reload cases per width; engine-slot ordering passes both widths.
All 32 surrounding regression runs pass. Final Windows builds compile 80
shared source units, pass input self-test, create hidden windows and respond
to bounded message probes. DOS16 links with the existing OLDNAMES warning;
it remains link-only, without resource binding or physical 486SX qualification.
Platform purity passes and platform source is unchanged.

The similar-issue sweep finds the two engine-slot callers already writing
ObjectOffset before the shared step. Move the public step to lifetime.c,
remove the duplicated horizontal algorithm from objects.c and use existing
world movement with slot+9/slot+11. Its carry propagation is no longer a
separate block-only implementation. Gravity and drawing remain single-owner
children; their full equivalence is not granted by this caller delivery.

Reproduce with mysmb_block_lifetime_smoke and the snapshot/caller/child
check targets. Record `--fixture=t37-lifetime=N` (0-31),
`--block-lifetime-snapshot=...`, `--control-children=...`; record
`--pc-coverage=...` separately. Run
`python test/verify_block_lifetime_snapshots.py <ignored-directory> <owner-rom>`.
The verifier retains actual failures and rejects non-OAM discrepancies.
Raw evidence remains ignored below build/m2-t37-s5, within the four-MB budget.

Three owner-authorized local test EXEs follow. They are not redistributable
release evidence or a claim that M2 is complete.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256561 | 600878167653a10b2ec6fb121a9c46bd394f0eb26599993381e52178e3059b9d |
| mysmb32.exe | 330411 | 2a32459cde26ce6a2f42aebafeafc5082db2b5948244161286910805e2f7f040 |
| mysmb64.exe | 338397 | 3193cffb20e3f575a79502aa55f68ec43670748484ce66cd65d7fd723b189040 |

Retained raw evidence: 1944726 bytes. S5 closes; S6 metatile replacement is next, not yet admitted.


## S6 admission: two-slot block metatile replacement

After S5 commit b22b97a, transfers 159/160 receive BlockObjMT_Updater from
T24 S2 and UpdateLoop/NextBUpd from T18 S4. All three remain incomplete.
Baseline 852 / 1,992; expected three, maximum 855. One contiguous chain at
$BED4-$BF01 lives in game/blocks/replacement.c; entry retains the existing
public updater ABI. Predecessors supply the flags and replacement bytes;
ReplaceBlockMetatile remains an unchanged area-output child.

Start X=1; store ObjectOffset at each loop even on skipped slots. Test
VRAM_Buffer1 at $0301 (not the offset at $0300), then replacement flag.
Write $06, $07=5 and $02 in source order, store the metatile through the
pointer, call ReplaceBlockMetatile, then explicitly clear the flag. DEX/BPL
visits slot zero and exits with ObjectOffset zero. Expose the existing child
without importing its algorithm or giving it new credit. Audit every updater
caller, replacement-flag writer and buffer-busy test; no platform gameplay.

Prove original control/data writes and call boundaries through ordinary NMI
GameEngine routes: busy/empty VRAM, either/both flags, nonunit flags, row and
column boundaries. Reference recording is read-only, with no CPU/stack/ROM
or output patching. Separate caller proof and actual child differences.
Independent native tests check full writes, two-slot order, busy recheck,
pointer scratch and post-child flag clear. Run strict C90 x86/x64, applicable
regressions, DOS16 link, platform purity, hidden-window probes and three
owner-authorized EXEs. Keep all temporary research, snapshots and builds
below ignored build/m2-t37-s6; raw budget four MB, recorder timeout twenty
seconds each, cleanup owner S6. Existing owner-local ROM/listing are research
inputs, with no redistribution or third-party implementation import.

Report all three labels, both proof tracks, residual ownership and artifact
hashes. No gravity/movement/VRAM-child repair. DOS remains link-only and no
complete-game equivalence follows from a caller match.


## S6 original block replacement proof

S6/P1 completes BlockObjMT_Updater, UpdateLoop and NextBUpd: expected three,
actual three, no scoped transfers. Progress 852 -> 855 / 1,992. This proves
the local loop and its child-call contract, not all VRAM-child interiors.

| Node | Shared C mapping and original contract |
| --- | --- |
| BlockObjMT_Updater $BED4 | blocks/replacement.c retains the public updater entry and starts slot one. |
| UpdateLoop $BED6 | ObjectOffset is written on every iteration, including skipped slots. Test command byte $0301, then flag; write $06, $07=5 and $02, store metatile through the pointer, call ReplaceBlockMetatile, explicitly clear flag afterwards. |
| NextBUpd $BEFE | Decrement slot; signed BPL loop visits slot zero and then exits. Final ObjectOffset is zero. |

Original $BED4-$BF01 instructions are compared to the shared implementation.
Thirty-two source-RAM ordinary NMI/GameEngine scenarios reach every node,
both slots at the child boundary and both outcomes of all three branches.
They cover busy/empty VRAM, either/both/no flags, nonunit flags, row and
column bounds. VRAM controller six selects the other command buffer during
NMI so explicit busy-buffer cases survive to the ordinary updater call.
The original has no range-clamping substitute for its indirect store; the
native maximum address for byte inputs is $06FE, within shared RAM.

Original root/direct-child observations are read-only real-stack boundaries.
No CPU/stack/ROM/return/output is patched; observed/unobserved frame outputs
and separately collected coverage snapshots are identical. On both widths,
64 caller comparisons match across 1,794 RAM bytes, including scratch
$02/$06/$07, OAM and VRAM. Scratch $00/$01/$03-$05 and CPU stack are excluded;
the independent full-write test covers the loop's own complete footprint.
Child-return substitution exists only in the isolated native caller checker.

Actual native roots match 52/64. Cases 6/7/14/15/22/23 retain twelve failures
across both widths, solely VRAM bytes $0301/$0306. Independent original
ReplaceBlockMetatile entry/exit checks reproduce those same differences.
High-row inputs yield original $20/native $24 or original $24/native $28.
Keep this child and its deeper VRAM calculation with existing T28 S3
maintenance custody; S6 does not silently repair, credit or suppress it.
The exact deeper instruction remains a later admitted audit responsibility.

Strict C90 focused native checks pass 131,072 full-pointer/write cases and
nine gate/loop cases per width. They verify both-slot ordering, nonunit flag
clear, ObjectOffset on skipped iterations and rechecking busy state after a
child writes VRAM. All 36 surrounding regressions pass, including block
graphics and engine caller ordering. Final Windows builds compile 81 shared
units, pass input self-test and hidden-window creation/message probes.
DOS16 links with the known OLDNAMES warning and remains link-only; there is
no DOS resource-binding or physical 486SX qualification claim. Platform
purity passes and platform source is unchanged.

The caller sweep finds one production engine call in original order, before
block lifetime. Remove the updater body from area/block_metatile.c, expose
its existing ReplaceBlockMetatile child unchanged, and keep one replacement
loop in game/blocks/replacement.c. Prior score/scratch, drawing and full-game
mismatches remain open. No movement or graphics algorithms change.

Reproduce with mysmb_block_replacement_smoke and snapshot/caller/child check
targets. Record `--fixture=t37-replacement=N` (0-31),
`--block-replacement-snapshot=...` and `--control-children=...`; collect
`--pc-coverage=...` separately. Run
`python test/verify_block_replacement_snapshots.py <ignored-directory> <owner-rom>`.
The verifier retains the actual-child failures and rejects other changed RAM.
Raw research remains below ignored build/m2-t37-s6 within four MB.

Three owner-authorized test artifacts follow, without redistribution or
complete-game equivalence claims.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256593 | 8cef2d07b0e08bd5034b4c884ab328ebee1f496884264579a037ab81d2764fd1 |
| mysmb32.exe | 330627 | 31026a0162aff4199ee6cd7ad5b8c24d13b6c37ced2c106a43898d55f15bbc08 |
| mysmb64.exe | 338649 | 7b83be2811032513d148c49e0c25897610f66774e59e503786da5a9ee27922be |

Retained raw evidence: 1218036 bytes. S6 closes; S7 horizontal movement is next, not yet admitted.


## S7 admission: horizontal movement primitive and entries

S6 closed in 7a18044. Transfer-161 receives six incomplete labels from
T17 S6: MoveEnemyHorizontally, MovePlayerHorizontally, MoveObjectHorizontally,
SaveXSpd, UseAdder and ExXMove. Baseline 855 / 1,992; expected six, maximum
861. Original $BF02-$BF4C has one shared owner in game/world/movement.c.

Preserve enemy INX and ObjectOffset return contract; player loads
JumpspringAnimCtrl, returns it without writes when nonzero, otherwise selects
SprObject offset zero. The common routine writes fraction to $01, signed
integer to $00 and page adder to $02. Fractional ADC carry feeds X-position
ADC; that carry feeds page ADC. Return original fractional carry plus signed
integer in A. Do not infer carry by comparing only the wrapped result.
ExXMove is also a later vertical-adapter return target; S7 proves its return
semantics through the horizontal entries, without crediting S8 interiors.

Remove duplicate player arithmetic and expose the common/ enemy displacement
as portable byte return values. Audit production call sites and update test
stubs for the declared ABI; represent source X restoration through the
existing caller slot/ObjectOffset contract, never an emulated CPU at runtime.
No vertical movement, friction, collision, drawing or platform algorithm
repair belongs here. S8/S9 retain vertical and gravity responsibilities.

ROM proof compares original entry/return RAM plus returned displacement on
ordinary NMI player, enemy and other SprObject paths, including jumpspring
blocked/unblocked cases and positive/negative fractional/page carries.
No PC, stack, ROM or reference output patching. Independent native arithmetic
checks enumerate all speed/fraction bytes with boundary positions/pages and
valid object offsets, verify whole write footprint and zero-write early exit.
Run relevant actor/player/lifetime regressions, strict C90 x86/x64, DOS16 link,
platform purity and bounded window probes; refresh three owner-authorized
EXEs at P closure. Keep child, full-frame and unrelated failures explicit.

Use existing owner-local ROM/listing as local research only; no third-party
implementation import or redistribution claim. All temporary research and
builds belong under ignored build/m2-t37-s7. Raw trace budget four MB, each
recorder timeout twenty seconds; cleanup owner S7. Before closure, record all
six dispositions, both verification tracks, tracker/ledger and artifact
hashes. DOS remains link-only. No completion credit from compilation alone.


## S7 original horizontal movement proof

S7/P1 completes MoveEnemyHorizontally, MovePlayerHorizontally,
MoveObjectHorizontally, SaveXSpd, UseAdder and ExXMove: expected six,
actual six, no scoped transfers. Progress 855 -> 861 / 1,992.

| Node | Shared mapping and original contract |
| --- | --- |
| MoveEnemyHorizontally $BF02 | world/movement.c increments enemy slot to SprObject offset and returns the common byte displacement. Original X restoration is a caller/ObjectOffset contract, not a runtime CPU register. |
| MovePlayerHorizontally $BF09 | player.c keeps the jumpspring gate; nonzero control returns unchanged with no writes; otherwise delegates offset zero to the common primitive. |
| MoveObjectHorizontally $BF0F | world/movement.c writes fraction $01, accumulates force, carries into X, then carries into page; retains the original fractional carry for its return. |
| SaveXSpd $BF23 | Signed integer nibble is written to $00, including negative extension. |
| UseAdder $BF2C | Zero or $FF page adder goes to $02 before movement. |
| ExXMove $BF4C | Return the byte displacement, or the blocked player's loaded control. The later vertical entry shares this RTS but receives no S7 implementation credit. |

The original $BF02-$BF4C stream defines source order and byte arithmetic.
Remove the duplicate player arithmetic: player and enemy wrappers now reach
one common implementation. Generic/enemy APIs return mysmb_u8 instead of
void; existing callers may ignore it, while player movement keeps storing
the actual result in Player_X_Scroll. No vertical/friction/collision or
platform algorithm changes. Source C uses no emulated CPU at runtime.

Ninety-six ordinary NMI routes provide 32 original entries each for player,
enemy and direct block SprObject movement. All six nodes are reached; all
three conditional branches have both outcomes. Positive, negative and zero
returns are observed, with blocked/unblocked player gates. The read-only
observer captures original A at the real stack return; it also checks enemy
X against ObjectOffset and direct movement X against its entry offset.
No original PC, stack, ROM or output is patched. Observed/unobserved frame
outputs and separately observed coverage snapshots are byte-identical.

Both final widths match all 192 original roots across 1,799 RAM bytes,
including every zero-page scratch byte, plus all 192 original return-A
values. CPU stack is excluded except original digit modifiers. This is
actual execution of the whole horizontal group with no child-return
substitution, not a mock-child proof. It does not certify upstream enemy
or player logic or unrelated full-game output.

Independent native checks use signed fixed-point world-position arithmetic,
not a copied instruction sequence. Per width, 2,360,832 cases cover all speed
and fractional bytes, boundary positions/pages, seven object offsets,
player and all six enemy entries, the entire RAM write footprint and return.
All 255 nonzero jumpspring values return unchanged without any RAM write.
The tests use host-only wide arithmetic; production remains portable C90.

Ten ABI-focused actor/lifetime regressions and 36 surrounding regressions
pass. The changed caller-test stubs match the byte-return ABI; callers that
discard A retain their original behavior. All 81 shared source files compile
under strict C90 on x86/x64; Windows self-tests and hidden-window message
probes pass. DOS16 links with the known OLDNAMES warning and remains
link-only, without resource-binding or physical 486SX qualification.
Platform purity passes and no platform source changed.

The similar-issue sweep covers every production horizontal call: player
movement, normal/jumping/frenzy enemies, cannon, fireballs, hammers, block
lifetime and remaining legacy object entries. Only player/common duplicate
arithmetic is consolidated here. Callers that are still awaiting source-order
migration, including platform-object consumers, receive no completion credit;
the now-available return value does not itself repair those callers. Prior
score scratch, drawing, VRAM high-row and full-frame debts remain open.

Reproduce with mysmb_horizontal_movement_smoke and
mysmb_horizontal_snapshot_check. Record `--fixture=t37-horizontal=N` (0-95)
with `--horizontal-snapshot=...`; collect `--pc-coverage=...` separately.
Run `python test/verify_horizontal_snapshots.py <ignored-directory> <owner-rom>`.
Raw evidence stays under ignored build/m2-t37-s7, below four MB. The three
owner-authorized local test artifacts below are not redistribution or full
M2 completion evidence.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256369 | cdaf06338de6411e669e83ee82b8c463ee4c6e4f61d43d7c83a6858e91a02abd |
| mysmb32.exe | 330115 | 676c48db51eede4db9646a1a1909d906219a4857a10575cd10de8371dc16722a |
| mysmb64.exe | 338649 | 560f3a11d43077b70a7671f9d166ee8b31df4b27e29e221a906a1d3bcc8f50b0 |

Retained raw evidence: 3638691 bytes. S7 closes; S8 vertical adapters is next, not yet admitted.


## S8 admission: vertical adapter entries

After S7 commit a470d60, transfer-162 receives eleven incomplete labels from
T17 S6: MovePlayerVertically, NoJSChk, MoveRedPTroopaDown, MoveRedPTroopaUp,
MoveRedPTroopa, MoveDropPlatform, MoveEnemySlowVert, SetMdMax,
MoveJ_EnemyVertically, SetHiMax and SetXMoveAmt. Transfer-163 receives
maintenance custody for MoveD_EnemyVertically, MoveFallingPlatform and
ContVMove from T31 S2 because their shared adapter dependency changes.
Their original conformance evidence remains, with no new credit. This
supersedes the plan's pre-admission custody expectation, not its source order.
Total scope fourteen, expected eleven new; baseline 861, maximum 872 / 1,992.

Original $BF4D-$BFA0: player selects offset zero, bypasses jumpspring gating
when TimerControl is nonzero, otherwise exits on nonzero animation control;
then writes VerticalForce to $00 and supplies max four to gravity. MoveD
selects $3D except exact state five falls into $20; falling also enters $20.
Red down/up entries select direction zero/one, increment enemy offset and
write downward three, upward six and max two to $00/$01/$02 before the
RedPTroopaGrav child. Drop selects $7F/max two; slow selects $0F/max two;
jumping selects $1C/max three. SetXMoveAmt writes $00, converts enemy index
to SprObject index and calls gravity; original X reload is ObjectOffset.

Shared owners remain game/world/movement.c, enemy/movement.c and the player
entry. Name the missing adapters and connect existing actor call sites at
their child boundary. Remove duplicated downward arithmetic in favor of the
existing shared gravity child. Extract the existing inline red gravity body
unchanged to expose its boundary; its arithmetic is not repaired or credited
until S9. Parent actor state-machine deficiencies remain with their owners.
No gravity-core, friction, terrain, rendering or platform algorithm repair.

ROM track uses ordinary NMI player, enemy, red-paratroopa and platform paths,
read-only real-stack entry/child returns, exact gates/parameters/scratch/slot
and retained MoveD/falling comparisons. No original PC, stack, ROM or output
patch. Native focused checks cover timer/jumpspring combinations, every enemy
state selector, force/max/direction and post-child preservation. Run relevant
actor/player regressions, strict C90 x86/x64, DOS16 link, platform purity and
bounded hidden-window probes; each implementation P refreshes three EXEs.
Keep caller equivalence and actual child differences separate.

Existing owner-local ROM/listing remain local research without redistribution
or third-party implementation import. All temporary research, traces and
builds stay below ignored build/m2-t37-s8; four-MB raw budget, twenty seconds
per recorder run, cleanup owner S8. Report fourteen dispositions, eleven
expected versus actual new matches, retained evidence, both proof tracks and
artifact hashes. DOS remains link-only. Unproven child/full-game behavior
cannot be inferred from adapter completion.

### S8 implementation and original-route checkpoint, not closure

The shared adapters now select the original gates, force, maximum, direction
and sprite offset. Existing gravity bodies are isolated in
`src/game/world/gravity.c` without repairing their arithmetic; S9 owns that
file's common-gravity consolidation and proof. The horizontal owner remains
`world/movement.c`. Normal-enemy regression links the actual gravity owner
while retaining its existing horizontal mock. Named slow/jumping/red/drop
adapters replace the corresponding legacy actor call sites; this does not
credit those parent state machines.

Original recordings use `test/vertical_fixture.h` scenarios 0-31 through
`reference_frame_recorder --fixture=t37-vertical=N --vertical-snapshot=PATH`
and `--control-children=PATH`. The fixture changes source RAM only at the
ordinary NMI boundary. Eight four-case families select player, ordinary
enemy, falling platform, red down, red up, drop platform, slow and jumping
entries. The recorder checks original gravity-entry A/X and enemy return X
against ObjectOffset, without changing reference execution. Separate
coverage and unobserved runs produce identical root snapshots and frame
records for all 32 cases. All fourteen scoped labels execute; the three
conditional branches at $BF52/$BF57/$BF69 have both outcomes. The immediate
constant branches at $BF8A/$BF90 are always taken, as the source requires.
Retained raw evidence is 1,378,834 bytes, below the four-MB budget.

`test/vertical_snapshot_check.c` compares 1,799 RAM bytes, including all
zero-page scratch and persistent score bytes, excluding only transient
hardware-stack storage. Across x86/x64, all 64 caller checks match when the
recorded original gravity result is supplied at the child boundary. This
proves the adapter path only. Actual native gravity yields two matches and
62 differences: $02/$07 scratch preservation is incomplete, and red cases
15/19 additionally produce the wrong high Y byte at $00B6. These are concrete
S9 gravity obligations; they must not be hidden by excluding scratch or by
claiming integrated vertical movement is complete.

Native adapter checks pass 460,324 cases per width. Both strict C90 builds
compile 82 shared units; DOS16 links only. The Win32 probes create responsive
hidden windows for two seconds in both widths, and input self-tests pass.
Of 40 selected regression runs, 38 pass and both Bowser runs exit four.
The S7 x64 objects reproduce exit four with the unchanged Bowser test;
this is baseline evidence, not a waiver or proof of the deeper cause.
Platform-purity checks pass. No final S8 artifacts are packaged or committed.

S8 remains active at 861 / 1,992. Final source/child review, reproducible
verification summaries, exact dispositions, tracker/ledger closure and
three-artifact delivery are still required. None of this checkpoint adds
node credit or closes S9 gravity work.

## S8 original vertical adapter proof

S8/P1 closes the fourteen received adapter labels: eleven new matches and
three retained matches. Progress is 861 -> 872 / 1,992. No scoped node is
transferred unfinished. Gravity interiors remain outside this credit.

| Original node | Address | Native owner / exact obligation | Disposition |
| --- | --- | --- | --- |
| MovePlayerVertically | $BF4D | player.c: offset zero, TimerControl bypass and Jumpspring gate | New match |
| NoJSChk | $BF59 | player.c: VerticalForce to scratch zero, max four, gravity tail | New match |
| MoveD_EnemyVertically | $BF63 | enemy/movement.c: exact state five selects falling force | Retained, revalidated |
| MoveFallingPlatform | $BF6B | enemy/movement.c: force $20 | Retained, revalidated |
| ContVMove | $BF6D | enemy/movement.c: joins max-three path | Retained, revalidated |
| MoveRedPTroopaDown | $BF70 | enemy/movement.c: direction zero | New match |
| MoveRedPTroopaUp | $BF75 | enemy/movement.c: direction one | New match |
| MoveRedPTroopa | $BF77 | enemy/movement.c: sprite index, scratch 3/6/2, direction, red child | New match |
| MoveDropPlatform | $BF88 | enemy/movement.c: force $7F, constant branch to max two | New match |
| MoveEnemySlowVert | $BF8C | enemy/movement.c: force $0F | New match |
| SetMdMax | $BF8E | enemy/movement.c: max two, constant branch to common adapter | New match |
| MoveJ_EnemyVertically | $BF92 | enemy/movement.c: force $1C | New match |
| SetHiMax | $BF94 | enemy/movement.c: max three | New match |
| SetXMoveAmt | $BF96 | enemy/movement.c: force scratch, slot+1, gravity call, caller slot contract | New match |

The preceding checkpoint records the original routes, child boundaries and
operational results. Reproduce the evidence review with
`python -X utf8 -B test/verify_vertical_snapshots.py build/m2-t37-s8 <owner-rom>`.
The verifier checks all fourteen labels, actual original branch and call
operands, all four player gate combinations, exact child cardinality, both
outcomes of conditional branches, the two constant branches, and identical
observed/unobserved frames. Native caller and actual-child modes of
`test/vertical_snapshot_check.c` compile against the same production objects;
only caller mode replaces the gravity boundary with recorded original output.
All 64 caller checks match all 1,799 compared bytes. The 62 actual failures
remain explicit: scratch $02/$07, plus red cases 15/19 high-Y carry. S9 must
repair and rerun these original states using the actual common gravity owner.

The similar-issue sweep covers every fixed slow/jumping/red/drop call site in
objects.c, bridge.c, player.c and enemy/movement.c. Ordinary state-five and
falling adapters now use the same gravity child. Gravity extraction preserves
old child arithmetic; parent actor gates, collisions and platform positioning
remain unproven where previously incomplete. Neither integration nor a named
wrapper grants their nodes completion. No platform source contains this work.

38 of 40 selected regressions pass; the unchanged Bowser test exits four in
both widths, reproduced against S7 x64 objects. Its exact assertion/deeper
cause is still a separate open diagnostic, not a newly accepted behavior.
Input self-tests and bounded hidden-window probes pass in x86/x64. Both strict
C90 builds compile 82 shared sources; OpenNT DOS16 links with the existing
OLDNAMES warning. DOS remains link-only, without playable/resource/486SX proof.
Documentation, node and ledger gates must pass before the P commit.

All three owner-authorized local artifacts are refreshed; none is whole-game
or release-conformance evidence. Earlier graphics/VRAM/full-frame debts remain.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256001 | 04d0a02d5fc31de8710e21f33e76d063d55b1a1e0d2058f506416c2722ab9301 |
| mysmb32.exe | 331814 | 5a56262093fe29b1746149c027bfc6a46805b587576d5794188a00de219c816e |
| mysmb64.exe | 338841 | 17e2326170eeb256726c2355df22efef9fbbbee06c1b0faa28391ecec08c12d0 |

S8 closes; S9 common gravity is next and not yet admitted.


## S9 admission: common gravity and adjacent entries

After S8 commit 8bed1c2, accepted transfer-164 receives all twelve S9 labels
from T17 S6. All are incomplete: MaxSpdBlockData, ResidualGravityCode,
ImposeGravityBlock, ImposeGravitySprObj, MovePlatformDown, MovePlatformUp,
SetDplSpd, RedPTroopaGrav, ImposeGravity, AlterYP, ChkUpM and ExVMove.
Baseline 872 / 1,992; expected twelve, maximum 884. ResidualGravityCode is
conditional on the previously specified residual-entry proof, not assumed
complete by association with a reachable successor.

Original $BF9F-$C046 owns a single gravity body. Shared world/gravity.c must
preserve dummy/force carry into signed speed plus low/high Y; store scratch
$07 sign before high-Y addition; add downward force; test the N flag of the
wrapped CMP result rather than a host signed/unsigned ordering; optionally
subtract upward force and clamp with the original fractional thresholds.
Entry wrappers preserve max/scratch writes, block slot conversion, platform
ID force selection, BIT-skipped entry bytes and red/platform direction.
Remove duplicated player/misc/block/red arithmetic in favor of this owner.
Existing actor state machines remain independently incomplete.

ROM proof reuses all 32 S8 roots and adds bounded ordinary block/platform
and gravity-boundary routes for missing branch/limit cases. Validate original
RAM, branch and call semantics before numerical test expansion. Residual
code has no natural incoming edge: audit bytes/data and native entry, plus
its reached successor separately; no forced PC/stack/ROM or output edits.
Record any insufficient residual proof as unfinished with accepted custody.

Native proof covers full write footprint, carry/wrap and CMP-N boundaries,
applicable actor/block/misc regressions, strict x86/x64 C90, DOS16 link,
platform purity and hidden Windows probes. Refresh three EXEs for P delivery.
Existing S8 red high-Y and scratch differences must be rerun against actual
gravity, without caller substitution. Retain earlier independent failures.

Existing owner-local ROM/listing are research/build inputs only; no third-party
implementation is imported. New temporary artifacts stay under ignored
build/m2-t37-s9, with a four-MB raw-trace budget, twenty-second recorder timeout
and S9 cleanup ownership; S8 evidence is reused read-only. No platform logic
or unsupported playable DOS claim. Report all twelve exact dispositions,
expected versus actual new matches, both proof tracks and final artifact hashes.

### S9 common-body checkpoint, not closure

Admission and documentation gates pass for twelve received incomplete labels
at 872 / 1,992. The shared gravity body now follows $BFD7-$C046, including
scratch $07, full fractional/low-Y/high-Y carry, wrapped CMP-N comparisons
and upward fractional clamp. Block, misc, red and player compatibility
entries share that body; platform and residual entry adapters are present
but their source-route proof and remaining platform integration are pending.

`build/m2-t37-s9/check-s8.py` compiles current gravity/player sources against
the S8 production objects in both widths and invokes the unchanged actual
mode of vertical_snapshot_check.c on all 32 retained original roots.
All 64 actual comparisons match all 1,799 compared RAM bytes. This resolves
the S8 scratch and red high-Y differences without substituting child output.
It does not yet establish block/platform entries, maximum-speed boundaries,
residual-entry completeness, three-target delivery or S9 closure.

The initial duplicate sweep distinguishes player ClimbingSub integration
from gravity, and identifies remaining legacy platform movement arithmetic
in objects.c for source-owner review. Hammer/misc production callers already
reach the shared sprite-gravity API. Parent actor/collision proof is not
granted by this change. No new nodes are credited at this checkpoint.

### S9 block/platform and branch checkpoint, not closure

The ordinary NMI gravity fixture adds 32 cases: eight block entry, eight
platform-down, eight platform-up and eight common-body red-actor states.
`test/gravity_snapshot_check.c` runs the real production owner and compares
all 1,799 non-transient RAM bytes; all 64 x86/x64 checks match. Together with
the S8 actual regression, 128 original/native comparisons pass. Separate
observed, coverage and unobserved runs preserve identical frames and root
states for all new cases; raw trace volume is 1,234,812 bytes.

Original opcode decoding of $BFA4-$C046 and combined S8/S9 coverage proves
both outcomes at $BFE6, $C006, $C00D, $C019, $C034 and $C03B. The platform
ID comparison at $BFC1 only takes its ordinary branch; the unreachable-by-
ordinary-platform-dispatch ID-$29 arm is covered by native entry testing,
not misreported as original route coverage. ResidualGravityCode likewise
still needs its final static/no-incoming-edge audit.

Six independent native cases per width check wrapped CMP-N down/up clamps,
the signed-speed-plus-fraction carry that preserves high Y, block versus
residual max-speed selection, and platform ID-$29 force selection.
The tests are registered as mysmb.gravity; none substitutes for original
route evidence. The YMovingPlatform caller now selects the common platform
gravity entry at its original center comparison; remaining parent collision,
positioning, balance-platform and lift movement semantics retain their own
unproven scope.

Current x86/x64 strict C90 builds and input self-tests pass for 82 shared
sources. OpenNT DOS16 links with the existing OLDNAMES warning. Of forty
selected regression runs, thirty-eight pass and the same two Bowser tests
exit four. No new regression failure appears in this selected set. Final
static/node review, hidden-window probes, package/ledger updates and the S9
P commit remain outstanding; assets still contain the committed S8 delivery.

## S9 original common gravity proof

S9/P1 completes all twelve received labels, expected twelve, no unfinished
scope transfer. Progress is 872 -> 884 / 1,992. The residual entry has
static/native proof under its explicit admission exception, not natural-ROM
execution credit. T37 still requires its final cross-chain closure review.

| Original node | Address | Exact implementation and proof | Disposition |
| --- | --- | --- | --- |
| MaxSpdBlockData | $BF9F | Both table bytes bound to original ROM; native residual/normal entries select 6/8 | Match |
| ResidualGravityCode | $BFA1 | LDY zero and BIT-overlap skip LDY one; no symbolic incoming edge; native max-six entry and separately reached common successor | Match, static/native residual proof |
| ImposeGravityBlock | $BFA4 | Force $50, table index one, sprite block offset, original block roots | Match |
| ImposeGravitySprObj | $BFAD | A maximum to scratch two, direction zero to common gravity; S8 actual roots | Match |
| MovePlatformDown | $BFB4 | Direction zero with BIT-skipped upward load; ordinary platform-down roots | Match |
| MovePlatformUp | $BFB7 | Direction one and common platform parameter selection; upward roots | Match |
| SetDplSpd | $BFC5 | Downward 5/9, upward 10, maximum 3; ordinary roots plus native residual ID29 arm | Match |
| RedPTroopaGrav | $BFD1 | Shared gravity call and original ObjectOffset return contract | Match |
| ImposeGravity | $BFD7 | Fractional ADC carry and sign selection; all shared sprite arrays | Match |
| AlterYP | $BFE9 | Scratch-seven sign and low/high-Y carry, downward acceleration and wrapped CMP-N clamp | Match |
| ChkUpM | $C018 | Direction gate, negative maximum, upward subtraction and wrapped CMP-N/fractional clamp | Match |
| ExVMove | $C046 | Original reached return after each gravity exit | Match |

The preceding checkpoints contain source mapping, independent native checks,
read-only recording proof and the exact similar-issue sweep. Reproduce the
final review with `python -X utf8 -B test/verify_gravity_snapshots.py
build/m2-t37-s9 build/m2-t37-s8 <owner-rom> <admitted-listing>`.
The verifier checks original prefix/table binding, all twelve named nodes,
all six gravity branches in both directions, no observed residual entry,
original versus native root RAM, and each native boundary executable.
All 128 actual comparisons match 1,799 bytes; no child substitution is used.
Both original conditional platform directions execute. The source ID29 arm
has only native/static proof because ordinary platform dispatch does not
reach MovePlatformUp/Down for that ID. No PC/stack/ROM patch supplies a route.

The residual byte audit identifies BIT absolute $01A0, which writes no RAM
and only affects N/V/Z. Subsequent LDA resets N/Z, and the shared gravity
body explicitly clears carry before addition and never consumes the BIT's
V flag. Skipping that non-observable read preserves native entry behavior;
it is not an emulator dependency. The admitted disassembly contains exactly
one symbol occurrence, its declaration; this is a no-symbolic-incoming-edge
claim, not an exhaustive assertion about arbitrary corrupted machine states.

Common gravity replaces old player/block/misc/red copies. YMovingPlatform
now delegates its center-selected movement to the same owner; parent gates,
collision/positioning, balance-platform and lift algorithms are not newly
credited. The pure climbing integrator remains with ClimbingSub, not gravity.
Vertical adapter mocks gained explicit failing stubs for unrelated new
entrypoints so they retain their narrow boundary and remain linkable.

Both widths pass the six focused boundary cases and 460,324 adapter cases.
All 82 shared units build under strict C90; x86/x64 self-tests and bounded
hidden-window probes pass. DOS16 links with the existing OLDNAMES warning;
no DOS runtime/resource/performance certification is claimed. Of forty
selected regressions, thirty-eight pass and the two baseline Bowser failures
remain at exit four. Prior score/graphics/VRAM/full-frame debts remain;
S8 gravity scratch/red high-Y differences are resolved by the actual tests.
Raw S9 evidence is 1,234,812 bytes; S8 evidence is reused read-only.

All three owner-authorized local artifacts are refreshed. Documentation,
node and ledger gates must pass before the P commit.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 252643 | 6f54332be752b558801d4a50a636fec950fb2f883992110bd5bc8340344540f7 |
| mysmb32.exe | 330106 | a81a7589d75c26b4b8daae51b6e6cb8d1db96a270811bca1266e49e2ce0bfd30 |
| mysmb64.exe | 337128 | fe601c6fee0dc77fef16279614b64f9c4051733261882e26cf621c2cdfcf0600 |
