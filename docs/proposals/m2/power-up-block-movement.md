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
