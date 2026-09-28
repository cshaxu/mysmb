# M2 T39: Special initialization, frenzy and actor dispatch

## Scope and source-boundary correction

T38 closed in 328aae6 at 978/1,992. The previous line-9300 cut splits the
Hammer Bro state machine before MoveHammerBroXDir. Keep the entire movement
phase with T40, beginning MovePodoboo at line 9212; T39 ends after
EraseEnemyObject at line 9211. This transfers twelve planned labels to the
following source slice without changing their existing receivers or status.

T39 receives 83 contiguous labels plus the necessary FlameTimerData,
SetFlameTimer and ExFl dependency. InitBowserFlame already has this exact
original call; its timer logic is duplicated inline in two native callers.
Establish one shared timer entry/table here and retain its later actor caller
without changing the actor's other behavior. The future source slice reuses
these three nodes without counting them again.

There are 86 unique scoped nodes: 81 incomplete targets and five retained
matches (DuplicateEnemyObj, FSLoop, FlmEx, NoRunCode, EraseEnemyObject).
Maximum is 1,059/1,992. Incomplete labels currently belong to T19 S5; the
three duplicate labels belong to T38 S6, and NoRunCode/EraseEnemyObject to
T31 S2. Only the admitted S1 receives custody now; later rows retain those
receivers until their own admission.

## Source-ordered chain plan

Every row performs source mapping, shared-C migration, original logic proof,
independent operational validation and one three-target delivery. No separate
mapping/audit/paperwork S is inserted. Caller-only substitution, if necessary
for later unadmitted children, must be labeled and actual-child failures kept.

| S | Chain | Shared owner | Expected / scoped | Exact labels in source order (dependencies last) |
| --- | --- | --- | ---: | --- |
| S1 | Bowser and flame initializer, including timer dependency | enemy/init_targets.c and enemy/frenzy.c | 12 / 15 | `InitBowser`, `DuplicateEnemyObj`, `FSLoop`, `FlmEx`, `FlameYPosData`, `FlameYMFAdderData`, `InitBowserFlame`, `SetFrT`, `PutAtRightExtent`, `SpawnFromMouth`, `SetMF`, `FinishFlame`, `FlameTimerData`, `SetFlameTimer`, `ExFl` |
| S2 | Fireworks allocation | enemy/frenzy.c | 5 / 5 | `FireworksXPosData`, `FireworksYPosData`, `InitFireworks`, `StarFChk`, `ExitFWk` |
| S3 | Bullet Bill / swimming-fish frenzy allocation | enemy/frenzy.c | 14 / 14 | `Bitmasks`, `Enemy17YPosData`, `SwimCC_IDData`, `BulletBillCheepCheep`, `ChkW2`, `Get17ID`, `Set17ID`, `GetRBit`, `ChkRBit`, `AddFBit`, `DoBulletBills`, `BB_SLoop`, `ExF17`, `FireBulletBill` |
| S4 | Grouped enemy records | enemy/group.c | 8 / 8 | `HandleGroupEnemies`, `PullID`, `SnglID`, `SetYGp`, `CntGrp`, `GrLoop`, `GSltLp`, `NextED` |
| S5 | Remaining small initializers and frenzy dispatch/stop | enemy/init_targets.c and enemy/frenzy.c | 9 / 9 | `InitPiranhaPlant`, `InitEnemyFrenzy`, `NoFrenzyCode`, `EndFrenzy`, `LakituChk`, `NextFSlot`, `InitJumpGPTroopa`, `TallBBox2`, `SetBBox2` |
| S6 | Platform initialization and positioning | enemy/init_targets.c | 20 / 20 | `InitBalPlatform`, `AlignP`, `SetBPA`, `InitDropPlatform`, `InitHoriPlatform`, `InitVertPlatform`, `SetYO`, `CommonPlatCode`, `SPBBox`, `CasPBB`, `LargeLiftUp`, `LargeLiftDown`, `LargeLiftBBox`, `PlatLiftUp`, `PlatLiftDown`, `CommonSmallLift`, `PlatPosDataLow`, `PlatPosDataHigh`, `PosPlatform`, `EndOfEnemyInitCode` |
| S7 | Actor vector and retainer dispatch | enemy/core.c and actor entry owners | 3 / 4 | `RunEnemyObjectsCore`, `JmpEO`, `NoRunCode`, `RunRetainerObj` |
| S8 | Normal actor and movement vector | enemy/core.c and movement entry owner | 4 / 4 | `RunNormalEnemies`, `SkipMove`, `EnemyMovementSubs`, `NoMoveCode` |
| S9 | Special actor wrappers and shared erasure | enemy/core.c and actor/platform entry owners | 6 / 7 | `RunBowserFlame`, `RunFirebarObj`, `RunSmallPlatform`, `RunLargePlatform`, `SkipPT`, `LargePlatformSubroutines`, `EraseEnemyObject` |

- S1: Original initializer-vector routes for Bowser and flame, including duplicate-before-front setup, exact timer/frame fields, bridge clear, sound queue, right-edge/mouth coordinates, force selection and shared finish. Timer counter legal values come from original zero initialization and masked increments.

- S2: Original fireworks entry with star-flag partner: counter decrement, descending ID scan, scratch-page subtraction, indexed offsets, carry and explosion state. Missing-partner source nontermination must not be hidden by a fabricated fallback.

- S3: Original land/water entry: slot limits, world/PRNG selector, active Bullet Bill scan, filter reset and bit rotation, shared position/finish then checkpoint. Preserve child return A used for dummy force.

- S4: Original group-record entry for all group IDs: hard-mode species, scratch $00-$03, Y/count selectors, free-slot scan, per-enemy checkpoint and single record advancement. Preserve original full-slot behavior.

- S5: Initializer and frenzy vectors: exact Piranha aliases and box-only tail, JumpEngine pointer scratch/selection, NoFrenzyCode, EndFrenzy state changes rather than invented flag clears, jumping green Paratroopa entry. Dependencies completed earlier are reused.

- S6: Platform vector routes: balance/drop/horizontal/vertical setup, box selection, rising/falling lift tails and three positioning offsets with page carry. Remove generic defaults only where source excludes their writes.

- S7: Actor vector routes for every ID: ObjectOffset reload, source selector arithmetic/table, exact child boundaries and retainer offscreen/relative/graphics order. NoRunCode retained; descendant bodies are not automatically certified.

- S8: Normal enemy caller: attributes, offscreen/relative/graphics/boxes/collisions in exact order, timer-gated movement dispatch and terminal bounds. Prove full movement vector and retain actual child failures separately.

- S9: Flame/firebar/platform wrappers: original call order, repeated relative computation, timer gate and platform vector. Reuse EraseEnemyObject with all eight source fields; no cross-platform gameplay branches.

Each admission records exact ROM addresses, dependencies and original NMI RAM
routes before editing. Each closure requires node-level branch/read/write/data
and call evidence plus focused native tests, x86/x64 strict C90, DOS16 link,
platform purity and three owner-authorized EXEs. T closure combines source
proof with a cross-chain actual matrix. DOS remains link-only and remaining
full-game, graphics/audio and actor/collision debts cannot be hidden.

## S1 admission: Bowser and flame initialization

Coordinator accepts transfer-172 (twelve open labels) and transfer-173 (three
retained duplicate labels) after T38 closes. Scope is exactly the S1 table row:
15 received, twelve expected new, baseline 978/1,992, maximum 990. InitBowser
and InitBowserFlame are the adjacent Bowser initializer family reached through
the original initializer/frenzy vectors; the shared timer is an explicit child
dependency. The original actor is outside scope except replacing its duplicate
inline timer call with the same shared entry.

Shared owners are enemy/init_targets.c and enemy/frenzy.c, plus that narrow
objects.c timer-call deduplication. Preserve duplicate-child source order,
Bowser frame timer versus interval timer, original bridge reset and preserved
unrelated state. For flames preserve NoiseSoundQueue, no invented slot gate,
PRNG aliases, unsigned position/force comparison, mouth X subtraction without
page borrow, right-edge page carry and final writes. Valid timer counter is
0..7 by original producers; verify all eight table entries and wrap.

ROM proof uses original NMI initialization entry records and all branch/table
variants, without CPU PC/stack/ROM patching. Native proof uses full-RAM sentinel
contracts, original actual comparisons, cross-width builds, DOS link, purity,
hidden-window response and three artifacts. Similar-issue sweep covers both
SetFlameTimer callers, both duplicate callers and all flame positioning users.

Owner-local ROM/listing provenance is unchanged, with no third-party source
import. All new records, logs and intermediates stay below ignored
build/m2-t39-s1, raw budget four MB, twenty-second recorder timeout, S1 cleanup
ownership. Stop on unadmitted repair, hidden mismatch or platform game logic.
No new match is recorded at admission. Future S2-S9 remain planned only.

## S1 original Bowser and flame proof

S1 closes twelve expected new nodes and retains three existing matches:
978 -> 990/1,992, fifteen scoped, no unfinished scoped node or transfer.
T39 remains open; S2 fireworks allocation is the next planned chain.

| Node | Original address | Individual proof and disposition |
| --- | --- | --- |
| InitBowser | $C549 | Duplicate first; set front, body/bridge, origin, breath/direction, feet/frame timer, HP and speed; preserve bbox, state, force and counter; new match |
| DuplicateEnemyObj | $C575 | Retained source slot scan, duplicate identity and coordinate copies; actual Bowser caller now covered; retained match |
| FSLoop | $C577 | Retained byte-Y scan executes occupied and free outcomes, including duplicate slot six; retained match |
| FlmEx | $C59C | Retained shared return from duplicate and busy flame timer; retained match |
| FlameYPosData | $C59D | All four bytes match ROM and all four PRNG indexes have original consumers; new match |
| FlameYMFAdderData | $C5A1 | Both bytes match ROM; below/equal/above comparison and both force values execute; new match |
| InitBowserFlame | $C5A3 | Timer-first gate, clear Y force, noise queue OR, then source front-ID branch; no invented slot gate; new match |
| SetFrT | $C5C9 | Set source timer result and PRNG alias, select original height before right-edge placement; new match |
| PutAtRightExtent | $C5D8 | Set Y, add 32 to right-edge X with page carry and byte wrap, tail to FinishFlame; new match |
| SpawnFromMouth | $C5EC | Subtract 14 from Bowser X without page borrow, copy page, add eight to Y, select original PRNG alias; new match |
| SetMF | $C614 | Unsigned target-height comparison selects force; clear frenzy buffer before common finish; new match |
| FinishFlame | $C61F | Write box eight, high-Y/flag one, X force/state zero and preserve other fields; new match |
| FlameTimerData | $D1D1 | All eight timer bytes match original and every index has a recorded consumer; new match |
| SetFlameTimer | $D1D9 | Read old counter, increment and mask stored counter, return old-index table value; shared by both native callers; new match |
| ExFl | $D1EA | Original timer return covered after every legal counter, including seven-to-zero wrap; new match |

Original execution proves 320/320 actual root comparisons across x86/x64.
The 160 controlled NMI RAM routes use the unchanged ROM loop and vectors to
reach Bowser or flame initialization. No PC, hardware stack or ROM patch,
child-return substitution, or scratch-byte masking is used. All twelve code
labels and 107 instructions execute; all five conditional branches take both
outcomes. Fourteen table bytes match ROM and every index has a recorded
consumer. Immediate calls preserve duplicate-before-Bowser setup and the
flame timer dependency; right-edge placement tails to the common finish.
Observer-free coverage runs produce identical frame records in all 160 cases.

Routes include all six parent slots, duplicate scans through slot six,
timer busy/expired, both front-ID paths, every timer/PRNG index, both secondary
modes, mouth X underflow without page borrow, Y wrap, both vertical forces,
and right-edge page carry/wrap. The source counter has no named writer beyond
SetFlameTimer's masked increment and is cleared by original memory/area
initialization. The native timer entry preserves that reachable 0..7 domain.
The two callers now share one entry/table; the broader Bowser actor is not
certified by this deduplication.

Independent full-RAM sentinel tests pass 107,522 cases per native width.
Eight focused initializer/stream/common/firebar/Spiny/flying-fish/Bowser-flame
tests per width pass with the final shared objects. The complete prior-chain
matrix preserves all 996 previous matches and adds four full Bowser-vector
comparisons plus 320 new root comparisons: 1,320/1,540. Its 220 remaining
mismatches stay with their existing downstream owners. The flame vector still
differs at nested JumpEngine scratch $04-$07, assigned to T39 S5; no masking
or broader dispatcher repair is included here.

Forty additional regressions retain 38 passes and two baseline bowser_smoke
exit-4 failures. Diagnostic execution locates those failures at the existing
fireball/HurtBowser assertions, after the stream-flame assertions pass. The
old initializer test incorrectly asserted bbox ten and omitted the duplicate;
only those source-invalid expectations and noise-queue preservation are
corrected. Collision expectations are retained unchanged for their source
owner; a passing initializer does not certify later damage behavior.

All 85 shared C units build under strict C90 on x86/x64; self-tests, bounded
hidden-window message probes and platform purity pass. DOS16 links with the
existing OLDNAMES warning and remains link-only, without runtime, graphical
playability, resource binding or physical 486 evidence. No platform gameplay
change is present. Three owner-authorized test EXEs are delivered together.

Similar-issue sweep covers both SetFlameTimer callers, original counter
producers, both duplicate consumers, flame sound queues and shared position/
finish callers. Earlier firebar and Spiny routes remain in the regression
matrix; their retained child gaps are not reclassified by this S.

Reproduce with bowser_flame_fixture.h cases 0..159, recorder options
--fixture=t39-bowser-flame=N, --bowser-flame-snapshot and --control-children;
run --pc-coverage separately. enemy_loop_actual_check consumes actual entry/
return RAM, excluding hardware return-stack storage while retaining mapped
$0109-$0139 game RAM. The focused native target is
mysmb.bowser-flame-initialization-chain. New evidence stays under ignored
build/m2-t39-s1, below 1.8 MB raw output within the four-MB budget, with a
20-second per-recorder timeout. Existing owner-ROM provenance is unchanged;
no third-party implementation is imported.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255515 | 4d6eafd6ca9119a584142e38d74336f9275d91b6b4b69c3fad6088a5619fa639 |
| mysmb32.exe | 338024 | d60b9f30eae8f84609ca0ad9821b07f328d08bd1c1add0be1883b51736e7d931 |
| mysmb64.exe | 345616 | ee207536c5c46bd234cb172aaa03ccb77d27554eb70c9a52efdc65fa5a9351b1 |
