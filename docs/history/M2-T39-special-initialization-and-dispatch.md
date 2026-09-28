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

## S2 admission: Complete fireworks initialization

After S1 commit a14bbad, coordinator accepts transfer-174 from T19 S5 for
FireworksXPosData, FireworksYPosData, InitFireworks, StarFChk and ExitFWk.
All five are open and expected new: baseline 990/1,992, maximum 995. This is
one complete data/initializer chain, original $C631-$C689, owned by shared
enemy/frenzy.c. The original frenzy vector calls InitFireworks; later drawing,
explosion stepping and the containing dispatcher remain outside this S.

Preserve timer-first gating, counter decrement, byte-Y descending star-ID
scan without fabricated fallback, scratch $00 page subtraction, saved X,
state-adjusted table index, carry propagation and explosion aliases. Normal
source producers constrain the table index to 0..5. Reuse the existing source
NMI/vector recording mechanism, preparing only original RAM and observing
actual entry/return. Cover all six table indexes, both timer outcomes, star
scan outcomes, all caller slots, counter/state combinations, X borrow/carry
and page wrap. A missing-star diagnostic is bounded by the external harness;
do not add a gameplay fallback or declare nontermination a successful spawn.

The separate operational track uses full-RAM native footprints, strict C90
x86/x64 builds, existing cross-chain regressions, DOS16 link, platform purity,
hidden-window response and the three owner-authorized EXEs. Similar-issue
sweep covers the sole initializer, star partner/counter producers, table
consumers and explosion aliases. Source policy and owner-local provenance
are unchanged, with no new third-party import. All temporary records remain
in ignored build/m2-t39-s2; raw budget four MB, twenty-second recorder timeout,
cleanup owned by S2. Stop on unadmitted repairs or hidden differences. S3-S9
remain planned, with no change to their custody.

## S2 original fireworks proof

All five planned fireworks nodes close: 990 -> 995/1,992, no scoped transfer.
T39 remains open; S3 Bullet Bill / swimming-fish frenzy allocation is next.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| FireworksXPosData | $C631 | Six horizontal offsets match original ROM; all indexes have original execution and carry cases; match |
| FireworksYPosData | $C637 | Six vertical positions match original ROM; all indexes have original execution; match |
| InitFireworks | $C63D | Timer-first gate; counter decrement, original scratch $00 page borrow, indexed X/page carry, Y/flag and explosion writes; match |
| StarFChk | $C64C | Byte-Y descending scan starts at five, preserves first-match priority and has no invented missing-partner return; match |
| ExitFWk | $C689 | Return for both busy timer and completed initialization with unrelated RAM preserved; match |

Actual original/native comparison passes 240/240 on x86/x64. The 120 original
NMI/vector routes prepare only RAM; no CPU PC, return stack, ROM patch, child
substitution or scratch masking is used. All three code labels and 38
instructions execute. Both conditional branches take both outcomes; all twelve
data bytes match ROM and all six indexes have recorded consumers. Coverage
runs without snapshot observers produce identical frame records in all cases.
The initializer has no child calls. Hardware stack storage is excluded while
mapped game RAM $0109-$0139 remains included.

Routes cover all six caller and star slots, descending scan priority, timer
busy/expired, each counter/state index combination, counter byte wrap, X
subtraction borrow, offset addition carry and page wrap. The source producers
GameTimerFireworks/SetFWC choose counter/state pairs 1/5, 3/3 or 6/0; the
SetoffF gate excludes zero and negative counters. These constrain ordinary
consumer indexes to 0..5; additional controlled RAM combinations check byte
semantics without claiming they are natural full-game states. Missing-partner
behavior follows the original byte scan with no fabricated fallback; no claim
of a successful spawn is made for a nonterminating scan.

Independent full-RAM tests pass 139,770 cases per native width, including all
256 X values and preserved unrelated fields. Nine focused initializer/stream
regressions per width pass with the final shared objects. The cross-chain
matrix retains all 1,320 previous actual matches and adds 240:
1,560/1,780. The 220 existing downstream differences remain assigned to their
original source-order owners, including frenzy JumpEngine scratch for S5.

Focused endgame, object-layout, mode and Bowser regressions retain four passes
and four explicit failures: endgame exit six and Bowser exit four, each on both
widths. Comparing the unmodified endgame test functions against the previous
S1 objects confirms identical results: star timer tick fails, while fireworks
animation, initializer and stream-record checks pass. A local diagnostic runs
each original assertion group separately; the committed test is not weakened.
Star timing remains with T19 S5 custody pending its planned T41 source slice;
its failing assertion is not presented as a newly proven ROM discrepancy.
Bowser damage retains its existing later collision ownership.

All 85 shared units build with strict C90 for x86/x64; self-tests, hidden-window
response and platform purity pass. DOS16 links with the existing OLDNAMES
warning and remains link-only, with no graphical/runtime or 486 claim. The
only gameplay change is in shared enemy/frenzy.c. The two data consumers,
star/counter producers, explosion aliases and initializer callers were swept;
no outside-scope actor repair or platform gameplay change is included.

Reproduce using fireworks_fixture.h cases 0..119, recorder options
--fixture=t39-fireworks=N, --fireworks-snapshot and --control-children, with
--pc-coverage run separately. enemy_loop_actual_check compares the unmodified
shared initializer against actual source entry/return RAM. The focused native
target is mysmb.fireworks-initialization-chain. Existing owner-local provenance
is unchanged. Evidence remains under ignored build/m2-t39-s2, below 1.1 MB raw
output within the four-MB budget; each recorder has a twenty-second timeout.

Three owner-authorized test artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255451 | 4f522661497aeb7dd6d667cea05a5bf65d11eec8e60a6e56477d6d60f4f55f35 |
| mysmb32.exe | 338024 | 0d156c91540265ace9b750b20a7a36137c37cf4daaff874a6481f6bf09cd5cc3 |
| mysmb64.exe | 345616 | 012f70bbbbec92be0b30330b3837b4d3e667481024db8f1dad5b4bc1f9c95771 |

## S3 admission: Bullet Bill and swimming-fish allocation

After S2 commit 020d87a, coordinator accepts transfer-175 from T19 S5 for
all fourteen exact S3 table-row labels. All are open and expected new:
baseline 995/1,992, maximum 1,009. The original $C68A-$C71A data/control
chain is owned by shared enemy/frenzy.c. InitEnemyFrenzy is the containing
caller; proven PutAtRightExtent/FinishFlame and CheckpointEnemyID with the
Bullet Bill/swimming-fish initializers are dependencies, with no repeated credit.

Restore timer-first gating, water slot limit, World2 constant one and original
PRNG threshold/species table; land scans only slots zero through four for an
active frenzy Bullet Bill before queuing blast sound. Common allocation resets
an all-set filter, rotates through eight height bits, preserves ID-before-filter
order, calls the shared right-edge/finish child, stores its zero return in the
Y-force dummy, then sets the timer and tail-calls CheckpointEnemyID. No movement,
collision, graphics or containing-frenzy-dispatch repair is admitted.

The ROM-logic track audits all tables, branches, reads/writes and child order
using original NMI/vector entry and return records, with only RAM fixtures;
cover timer gates, water limits, PRNG/world species thresholds, active/inactive
Bullet Bills in every scanned slot, ignored slot five, every filter/index,
filter exhaustion and right-edge carry. Keep actual child failures visible.
The operational track uses focused full-RAM contracts, strict C90 x86/x64,
DOS16 link, platform purity, hidden-window probes and three authorized EXEs.
Similar-issue sweep covers filter producers/consumers, World2 comparison,
shared placement return semantics and initializer tail dependencies.

Existing owner-ROM/listing provenance remains local; no new external material
is imported. Temporary evidence stays below ignored build/m2-t39-s3, four-MB
raw budget and twenty-second recorder timeout, with S3 cleanup ownership.
Stop on unadmitted repair, source execution patching or hidden differences.
S4-S9 remain planned and retain their current node receivers.

## S3 original Bullet and swimming-fish proof

All fourteen planned nodes close: 995 -> 1,009/1,992, no scoped transfer.
T39 remains open; S4 grouped enemy records is next.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| Bitmasks | $C68A | All eight original mask bytes match; source consumers use every index; match |
| Enemy17YPosData | $C692 | All eight original heights match; placement child outputs prove every consumer; match |
| SwimCC_IDData | $C69A | Both species bytes match original and execute on both sides of world/PRNG selection; match |
| BulletBillCheepCheep | $C69C | Timer-first gate, water slot limit and area branch; common shared child chain preserves exact writes; match |
| ChkW2 | $C6B4 | World2 is one; increment selector only outside that world; match |
| Get17ID | $C6BC | Mask selector to one bit and load the original species table; match |
| Set17ID | $C6C3 | Write ID before all-set filter reset and random height selection; match |
| GetRBit | $C6D1 | Read three PRNG low bits after optional filter reset; match |
| ChkRBit | $C6D6 | Rotate through eight mask indexes with wrap; preserve occupied-bit loop; match |
| AddFBit | $C6E6 | OR selected bit, call shared placement, store its zero return, set timer and tail-call checkpoint; match |
| DoBulletBills | $C6FD | Enter land scan without changing state first; match |
| BB_SLoop | $C6FF | Scan only slots zero through four; require both nonzero flag and frenzy Bullet Bill ID; match |
| ExF17 | $C710 | Return on timer, water capacity or existing Bullet Bill without invented writes; match |
| FireBulletBill | $C711 | OR blast sound and branch with constant ID eight into Set17ID; match |

Actual original/native comparison passes 364/364 across x86/x64. The 182
RAM-only NMI/vector routes execute the original caller and actual children;
there is no PC/stack/ROM patch, child substitution or scratch masking. All
eleven code labels and 58 instructions execute. Ten conditional branches
exercise both outcomes; the final BNE follows LDA #8 and correctly never
falls through. Eighteen table bytes match ROM, all eight mask/height indexes
execute, and both swimming species have source consumers. Coverage without
snapshot observers gives identical frame records in all 182 cases.

Twenty-five captured roots take a gate; 157 allocate with the exact child
sequence PutAtRightExtent -> CheckpointEnemyID. Child snapshots show shared
FinishFlame writes before the dummy receives zero and the selected actor
initializer runs. The full actual return comparison checks inherited caller
scratch, preserved state and every RAM write; hardware stack storage is
excluded while mapped $0109-$0139 game RAM remains included. No additional
credit is taken for already proven positioning/vector/initializer children.

Cases cover all caller slots, water rejection after slot two, World2 and
other worlds, PRNG values below/equal/above $AA, all-set filter reset, bit
rotation/wrap, land active/inactive/wrong-ID checks, ignored slot five and
right-edge carry/page wrap. Native full-RAM contracts independently pass
1,182,858 cases per width, including every filter byte and every PRNG byte.
They also verify preserved state when gated and all ordinary world choices.

The old Bullet Bill smoke first failed at exit 101 because it expected species
11 for World2/low PRNG, contrary to source constant one and SwimCC_IDData[0].
Its expectation is corrected to ten, dummy zero is checked from a sentinel,
and the existing-Bullet-Bill check now expires the timer so it actually tests
the active-slot gate. Both widths pass. No collision assertion is weakened.

Ten focused initializer/stream regressions per width pass with final shared
objects. The complete cross-chain matrix preserves all 1,560 prior matches,
adds four previously failing full initializer-vector matches and 364 new
roots: 1,928/2,144. The 216 remaining downstream differences stay explicit
with their existing source-order owners. Other focused endgame/layout/mode/
Bowser runs retain four passes and the four already established star-timer
exit-six / Bowser-damage exit-four failures, one of each per width.

Strict C90 builds compile all 85 shared units on x86/x64; self-tests, bounded
hidden-window response and platform purity pass. DOS16 links with the existing
OLDNAMES warning and remains link-only, with no runtime/graphics or physical
486 certification. Gameplay changes are confined to shared enemy/frenzy.c.
The similar-issue sweep found one filter allocation owner, checked its source
reset/selection producers, World2 selection and both shared-child dependencies.
No containing dispatcher, moving actor, collision or platform repair is added.

Reproduce with bullet_swimming_fish_fixture.h cases 0..181 and recorder options
--fixture=t39-bullet-swim=N, --bullet-swim-snapshot and --control-children;
run --pc-coverage separately. The RAM fixture inverts the original single ROR
step to exercise exact low/high PRNG values without changing source execution.
enemy_loop_actual_check compares actual shared-C results. The native target is
mysmb.bullet-swimming-fish-chain. Existing owner-local provenance is unchanged;
all new evidence stays below ignored build/m2-t39-s3, under 2.9 MB raw output
within the four-MB budget, with twenty-second per-recorder timeouts.

Three owner-authorized test artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255285 | 1a26223929fe40e6089d68ce746e853e3129297f5ad157b00561d75d1e75cf3d |
| mysmb32.exe | 338083 | 52d716fa0eb66b688e103fb624e710ac05046351070f82be7ed7405ef5a088c9 |
| mysmb64.exe | 345152 | f9e0514c8e3c1ca80d3dacb3887bc666f7be519de0de205b40105025a1e4c255 |

## S4 admission: Grouped enemy records

After S3 commit a44dd1a, coordinator accepts transfer-176 from T19 S5 for
HandleGroupEnemies, PullID, SnglID, SetYGp, CntGrp, GrLoop, GSltLp and NextED.
All eight are open and expected new: baseline 1,009/1,992, maximum 1,017.
The complete original $C71B-$C786 group chain belongs to shared enemy/group.c.
Its parser caller, CheckpointEnemyID and normal/Goomba initializer children,
and Inc2B tail are dependencies already audited in earlier chains.

Preserve source species/hard-mode choice, scratch $01/$00 ID/Y, scratch
$02/$03 page/X and their 24-pixel carry, two/three count, zero-to-four free-slot
scan, per-member checkpoint, RAM count decrement, exhaustion and exactly one
record advance on every terminal path. Do not replace source scratch with
private locals or make ObjectOffset follow the group scan: the source does
not write it here. Movement, drawing, collision and parser repair are outside S4.

ROM proof uses unchanged original enemy records via RAM-only NMI parser
fixtures and actual root/child return snapshots. Six group IDs occur in the
original level record inventory; native contracts also cover both unused but
code-defined group IDs. Cover original branch outcomes, hard modes, capacity
masks including full/partial groups, entry from slot five, right-edge carry,
page wrap and record-offset wrap. Preserve any unsupported entry or child gap
instead of patching source execution. Operational proof includes full-RAM
contracts, strict C90 x86/x64, DOS link, platform purity, hidden-window probes
and all three authorized EXEs. Sweep scratch users, count/record advancement
and child write boundaries. Existing owner-local ROM/listing provenance is
unchanged, no third-party import; temporary evidence stays under ignored
build/m2-t39-s4, four-MB raw budget, twenty-second recorder timeout, S4 cleanup
owner. Later S rows retain custody; no actor or platform gameplay is admitted.

## S4 original grouped-enemy proof

All eight planned group nodes close: 1,009 -> 1,017/1,992, no scoped transfer.
T39 remains open; S5 remaining small initializers and frenzy dispatch is next.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| HandleGroupEnemies | $C71B | Subtract group base, preserve selector and select default green Koopa or hard-mode Goomba/Buzzy family; match |
| PullID | $C72F | Restore group selector after hard-mode species choice; match |
| SnglID | $C730 | Write original ID to scratch $01; select vertical row from group bit one; match |
| SetYGp | $C73A | Write scratch Y $00, right page $02 and right X $03; match |
| CntGrp | $C74D | Write two/three-member count from group bit zero; match |
| GrLoop | $C750 | Restart scan for every member; decrement source RAM count after the checkpoint child; match |
| GSltLp | $C752 | Scan only slots zero through four; write member fields, advance scratch by 24 with carry and call checkpoint; match |
| NextED | $C784 | Single Inc2B tail on complete or capacity-exhausted group, preserving remaining count and ObjectOffset; match |

Actual original/native comparison passes 230/230 across x86/x64. The 115
entering NMI routes read unchanged original level records and execute all eight
labels, 55 instructions and both outcomes of all seven conditional branches.
No CPU PC, return-stack, ROM or child-return patch is used. Original child
records show one, two or three checkpoint calls followed by exactly one Inc2B
tail; scratch $00-$03, preserved ObjectOffset and remaining group count agree.
Hardware stack storage is excluded while mapped $0109-$0139 RAM is retained.

Thirteen additional full-capacity inputs are source gates, not matched group
returns. The original parser visits its entry but never HandleGroupEnemies:
slot five rejects ordinary group records. These reproduce recorder exit 69
because no root snapshot exists; separate PC coverage confirms the missing
entry and frame equality. Partial allocation followed by a full scan covers
the group routine's capacity exit in 53 entering routes. Independent native
contracts additionally verify initially full capacity without inventing a ROM
entry. This corrects the admission's proposed slot-five entry expectation.

All 31 nonfull capacity masks occur at original entry, both hard modes execute,
51 routes wrap the record cursor and six wrap the final scratch page. For page
$FF fixtures, the parser's +$30 lookahead must remain in range before the group
can enter; the three-member +$18 chain then provides real page-wrap coverage.
The original level-record inventory contains IDs $37-$3C; all six are used.
Code-defined $3D/$3E are covered by source branch semantics and native tests,
without claiming original level records or execution for those two inputs.

Independent full-RAM contracts pass 262,144 cases per width: all eight group
IDs, both hard modes, all 32 capacity masks, every X/cursor byte and page zero/
$FF. Source-return observation and observer-free coverage produce equal frame
records for all 128 entering/gated fixtures. No scratch byte is masked from
actual comparisons. The new shared implementation makes source RAM the owner
of group ID/Y/page/X/count, preserving the original child boundaries.

Eleven focused initializer/stream regressions per width pass on final objects.
The full cross-chain matrix retains all 1,928 prior matches, adds 230 new roots
and resolves all ten earlier parser differences: 2,168/2,374. The parser set is
now 160/160. The remaining 206 downstream differences stay with their existing
owners. Focused endgame/layout/mode/Bowser checks retain four passes and the
four established star-timer exit-six / Bowser-damage exit-four failures.

All 85 shared units build in strict C90 for x86/x64; self-tests, bounded hidden
window response and platform purity pass. DOS16 links with the existing
OLDNAMES warning and remains link-only, without graphical/runtime or physical
486 certification. Only shared enemy/group.c changes gameplay. The similar
issue sweep covers group scratch/count users, child writes and the single
record-advance tail; no parser, actor or platform gameplay repair is included.

Reproduce with group_enemy_fixture.h cases 0..127, --fixture=t39-group=N,
--group-snapshot and --control-children; use --pc-coverage in separate runs.
Full masks (cases below 96 with remainder 14/15 modulo 16, plus 127) must
show no group entry and are not fed to enemy_loop_actual_check. Other cases
compare actual shared-C returns. The native target is mysmb.group-enemy-chain.
Existing owner-local provenance is unchanged; temporary evidence remains under
ignored build/m2-t39-s4, under 2.4 MB raw output within the four-MB budget and
twenty-second recorder timeout. No third-party implementation is imported.

Three owner-authorized test artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255381 | 8b8ab34cb4db865ecabd9c27e87babe7f76b2daf93265e475341ce55cbd957c8 |
| mysmb32.exe | 338083 | ca72eadfe0e50e3a4a52e79345d284ae0cbfe51b0c8e78afe0995f5bc8cad965 |
| mysmb64.exe | 345664 | 3721e3bbcc654c3e7027a49579ba3b75dac022138432165cce2cc952f1090df1 |

## S5 admission: Small initializers and frenzy dispatch

After S4 commit 8f8a508, coordinator accepts transfer-177 from T19 S5 for the
nine exact S5 table-row labels. All are open and expected new: baseline
1,017/1,992, maximum 1,026. Shared owners are enemy/init_targets.c and
frenzy.c, with narrow initializer-vector/header cleanup to remove the obsolete
Piranha entry wrapper. The original range is $C787-$C7DE, including the six
frenzy vector words and shared box-only tail.

Restore Piranha's exact speed/state/move flag/down/up Y writes and shared
SetBBox2 tail, without generic defaults. Jumping green Paratroopa sets direction
and X speed before TallBBox2/SetBBox2 only. Frenzy dispatch writes its buffer,
uses ID minus $12 and the original JumpEngine scratch/table before each child.
EndFrenzy scans IDs in all six slots, sets matching Lakitu states to one even
when inactive, then clears frenzy and only its own flag. No broader actors,
platform initializers, moving/graphics/collision children or platform game
logic are admitted.

ROM proof audits branch/read/write/call order, all twelve vector bytes and
actual entry/return RAM. Reuse earlier initializer/frenzy records and add
bounded RAM-only cases for field preservation, Y wrap, all Lakitu patterns
and all six dispatcher selectors. The $13 NoFrenzyCode selector is a residual
vector entry: the outer initializer maps that ID to NoInitCode. To observe
this original RTS without changing code, PC or stack, an explicitly labeled
controlled-input case may replace only Enemy_ID at the naturally reached
InitEnemyFrenzy boundary, before its first instruction and snapshot. It must
run identically with and without observation and cannot be claimed as a natural
outer-vector route. All other fixtures remain NMI RAM preparations. Child
interiors such as PlayerLakituDiff retain their existing discrepancies.

Operational proof uses full-RAM contracts, strict C90 x86/x64, DOS16 link,
platform purity, hidden-window response and three authorized EXEs. Sweep both
Piranha callers, shared box-only tails, all vector entries and EndFrenzy state/
flag consumers. Existing owner-local provenance remains unchanged; no external
implementation is imported. New records stay in ignored build/m2-t39-s5,
four-MB raw budget, twenty-second timeout and S5 cleanup ownership. Stop on
unadmitted repairs, hidden differences or CPU/ROM patching. S6-S9 retain custody.

## S5 original small-initializer and frenzy proof

All nine planned nodes close: 1,017 -> 1,026/1,992, no scoped transfer.
T39 remains open; S6 platform initialization is next, not yet admitted.
Admission gate confirms scope nine, expected nine, all incoming open and
maximum 1,026. Transfer-177 registers each exact receiver before implementation.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| InitPiranhaPlant | $C787 | Exact speed/state/move flag/down/up Y writes, then SetBBox2; remove generic-default wrapper; match |
| InitEnemyFrenzy | $C7A0 | Buffer write, six-way original vector and JumpEngine scratch before selected child; match |
| NoFrenzyCode | $C7B7 | Original RTS reached with explicit residual RAM input at natural frenzy entry; no invented outer-vector route; match |
| EndFrenzy | $C7B8 | Descending six-ID scan, Lakitu state writes, clear request and only controller flag; match |
| LakituChk | $C7BA | Compare every slot ID with Lakitu, independently of its flag; match |
| NextFSlot | $C7C6 | Decrement scan through zero, then clear buffer and controller flag; match |
| InitJumpGPTroopa | $C7D1 | Direction two and speed $F8, then shared TallBBox2 tail without generic defaults; match |
| TallBBox2 | $C7D9 | Load box three and enter shared SetBBox2 tail; match |
| SetBBox2 | $C7DB | Single indexed box write, preserving every other RAM byte; match |

Original/native actual comparison passes 392/392 across x86/x64, from 196
controlled routes. All nine code labels and 37 instructions execute; both
conditional branches take both outcomes. All twelve vector bytes match the
owner ROM; each of six selectors has six original child-entry records with
its exact $04-$07 JumpEngine scratch. The busy-timer routes isolate dispatch;
previous initializer-family records retain actual child-body comparisons.
No child-return substitution or scratch masking is used. Hardware-stack RAM
is excluded while mapped $0109-$0139 variables remain compared.

One residual source edge is explicitly bounded: outer InitEnemyRoutines maps
ID $13 to NoInitCode, while the inner frenzy vector contains NoFrenzyCode.
Six cases reach InitEnemyFrenzy naturally with ID $12, then supply $13 in its
Enemy_ID RAM input before the first instruction and snapshot. This is a
controlled function-input route, not a natural outer-vector or level-data
claim. PC, return stack, ROM and jump table remain untouched. The same input
is applied without observation; all 196 separate coverage runs produce equal
frame records. Other cases use NMI RAM setup only.

Piranha cases cover all six slots and eight boundary Y values, including
subtraction underflow and checkpoint addition wrap. EndFrenzy records cover
all 32 combinations of the five noncontroller Lakitu IDs; the sixth ID belongs
to the stop controller in this natural queue route. Independent native tests
cover all 64 ID masks and all 64 active/inactive flag masks in every controller
slot, every Y byte, field preservation and all six busy-timer vector targets:
27,684 complete-RAM contracts per width. These native inputs supplement,
and do not replace, the original control-flow and write proof.

Twelve focused initializer/stream tests per width pass with final objects.
The full actual matrix is 2,602/2,766, retaining all 2,168 previous matches,
adding 392 new roots and resolving 42 earlier caller differences. The remaining
164 downstream differences retain their source-order owners.

Endgame/layout/mode/Bowser regressions retain their established four passes
and four star-timer exit-six / Bowser-damage exit-four failures. The additional
Lakitu smoke still fails in its Spiny-generation assertion before EndFrenzy;
the same diagnostic test against prior S4 and final S5 objects on both widths
reports the identical failure (original test line 76). Only the source-invalid
EndFrenzy expectation was corrected: Lakitu flags remain, states become one.
No broader Lakitu/Spiny behavior is certified or repaired here.

All 85 shared units pass strict C90 x86/x64 builds, self-tests and bounded
hidden-window message probes. Platform purity passes. DOS16 links with the
existing OLDNAMES warning and remains link-only, without runtime/graphics,
resource binding or physical 486 certification. Gameplay changes are confined
to shared enemy initialization and frenzy; platform code is unchanged.

Similar-issue sweep: initializer-vector and area-object Piranha callers now
share the exact existing body; the obsolete generic-default wrapper and its
header declaration are removed. TallBBox2 callers (jumping green Paratroopa,
SetupLakitu and firebar) share SetBBox2; existing common/firebar proofs stay
valid. All five outer frenzy aliases share the six-entry nested vector; the
residual sixth selector is documented above. EndFrenzy is called only by its
initializer entry; the legacy smoke expectation is corrected without changing
actor code. Remaining platform generic defaults stay with S6.

Reproduce using small_initializers_fixture.h cases 0..195,
--fixture=t39-small-init=N, --small-init-snapshot and --control-children;
run --pc-coverage separately. Cases 166..171 are the explicitly controlled
residual ID inputs. Feed root snapshots to enemy_loop_actual_check with final
shared objects and original local PRG. Native target:
mysmb.small-initializers-frenzy-chain. Provenance is unchanged; no third-party
implementation is imported. Raw evidence stays in ignored build/m2-t39-s5,
under 1.9 MB within the four-MB and twenty-second per-recorder budgets.

Three owner-authorized test artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255377 | ef9a3a58a3b42046519a84f02fde29294d1ce1d4ed26c46cba328c07ccd0acb3 |
| mysmb32.exe | 338112 | da2752dd7c677b4bce8dedc043cbb51b1ad6bf6a7c8656f25627cd045c11854a |
| mysmb64.exe | 345692 | dcca155c00cf3a4309ad673c0e21a350cdf1478932ccf54ff801dbcbf95a41fb |

## S6 admission: Platform initialization and positioning

After S5 commit 0f73dcc, coordinator accepts transfer-178 from T19 S5 for all
twenty exact S6 table-row labels. Admission is 1,026/1,992; all twenty are open
and expected new, maximum 1,046. Source range $C7DF-$C881 includes eight
initializer entries, common tails, six positioning-table bytes and the final
RTS. Shared owner is enemy/init_targets.c; the original checkpoint and vector
remain the predecessor, actor dispatch S7 remains the successor. InitVStf is
already proven; reuse it without new credit.

Remove generic defaults absent from original writes. Restore balance's
optional -8, alignment/state order, +8 and drop/common fallthrough; horizontal
counter zero; vertical absolute top/center calculation without changing Y;
common vertical-state reset and castle/hard-mode box selection. Large lifts
must call small lifts, including +12 positioning, then overwrite the box;
small lifts preserve unrelated fields. PosPlatform preserves byte addition
and page carry for all three original offsets. EndOfEnemyInitCode remains
an empty native return, reached by original outer vector ID $36.

ROM proof uses unchanged original NMI/queue/vector routes for all platform
IDs and EndOfEnemyInitCode, original read/write/branch/call order, all table
indexes, both Y signs, hard/castle branches, alignment and page carry/wrap.
No PC, stack, ROM, child-return or scratch patching is permitted. Independent
native full-RAM contracts, retained original regressions, strict C90 x86/x64,
DOS16 link, host-purity and hidden-window checks precede three-EXE delivery.
Sweep all initializer aliases, common-tail callers and legacy-default users.
No platform movement/collision/drawing or host gameplay change is admitted.

Existing owner-local ROM/listing provenance is unchanged; no external code
is imported. New raw evidence stays in ignored build/m2-t39-s6, four-MB budget,
twenty-second recorder timeout and S6 cleanup ownership. Stop for unadmitted
repair or unexplained discrepancies. S7-S9 retain their existing receivers.

## S6 original platform initialization proof

All twenty planned platform initialization nodes close: 1,026 -> 1,046/1,992,
no scoped transfer. T39 remains open; S7 actor-vector/retainer dispatch is next.
Admission gate confirms twenty scoped and expected open nodes, maximum 1,046;
transfer-178 accepts custody before implementation.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| InitBalPlatform | $C7DF | Decrement Y twice; optional -8, alignment, +8 and drop/common fallthrough in original order; match |
| AlignP | $C7ED | Read old alignment into enemy state and select next pair marker by sign; match |
| SetBPA | $C7F8 | Store next alignment, clear direction, +8 then fall through InitDropPlatform; match |
| InitDropPlatform | $C803 | Write collision flag $FF then enter CommonPlatCode; match |
| InitHoriPlatform | $C80B | Zero XMoveSecondaryCounter only before common tail; match |
| InitVertPlatform | $C812 | Preserve original Y while deriving top magnitude and center from its sign; match |
| SetYO | $C81F | Write top, add selected $40/$C0 to original Y and write center; match |
| CommonPlatCode | $C828 | Call existing InitVStf then fall through SPBBox; match |
| SPBBox | $C82B | Castle/hard branches choose large platform box five or six; match |
| CasPBB | $C83B | Store only the selected box and return; match |
| LargeLiftUp | $C83F | Call PlatLiftUp before shared large box overwrite; match |
| LargeLiftDown | $C845 | Call PlatLiftDown before shared large box overwrite; match |
| LargeLiftBBox | $C848 | Enter SPBBox without resetting lift speed or force; match |
| PlatLiftUp | $C84B | Set force $10 and speed $FF, then CommonSmallLift; match |
| PlatLiftDown | $C857 | Set force $F0 and speed zero, then CommonSmallLift; match |
| CommonSmallLift | $C860 | PosPlatform index one adds twelve before box four; match |
| PlatPosDataLow | $C86B | All three low addends match original and execute through PosPlatform; match |
| PlatPosDataHigh | $C86E | All three high addends match original and execute with carry; match |
| PosPlatform | $C871 | Original low-byte addition and carry-fed page addition for +8/+12/-8; match |
| EndOfEnemyInitCode | $C881 | Original RTS reached via vector ID $36; native caller has an empty return; match |

Original/native comparison passes 480/480 across x86/x64. The 240 NMI RAM
routes execute unmodified queue and initializer vectors for IDs $24-$2C and
$36. All eighteen code labels, 72 instructions and both outcomes of all five
conditional branches execute. All six positioning-table bytes match original,
and all three indices have original consumers. No PC, stack, ROM, input-at-
entry or child-return patch is used. Hardware stack storage is excluded from
actual RAM comparison while mapped $0109-$0139 variables remain compared.
All 240 observer-free coverage runs produce identical frame records.

Original PosPlatform child records verify each intermediate coordinate, not
only the net result: 51 carry cases and fifteen page-wrap cases. Balance has
optional -8 before alignment, then +8 before InitVStf; large lifts have +12
before their large-box tail; small lifts have +12 before box four. The child
observer records InitVStf return at the same PC where SPBBox begins, so that
fallthrough is not a separate child snapshot. Original instruction coverage,
branch audit and full root returns prove that tail; large lifts additionally
record its distinct child entry. No missing snapshot is claimed as an observed
call. Both vertical Y signs, both alignment signs, all four area types, both
hard-mode values, and boxes four/five/six occur in original runs.

Independent full-RAM native contracts pass 245,760 cases per width: all ten
vector selectors, six slots, every X/Y/alignment byte, zero/$FF pages and all
area/hard combinations. EndOfEnemyInitCode is additionally tested through its
real checkpoint caller, including the caller's original JumpEngine scratch.
The original final target is a no-op; an empty wrapper is not added merely to
supply a C function name.

Thirteen focused initializer/stream tests per width pass on final objects.
The full actual matrix is 3,118/3,246, retaining all 2,602 prior matches,
adding 480 new roots and resolving 36 earlier initializer differences. The
remaining 128 downstream differences retain their existing source-order owners.

The platform smoke passes on both widths after correcting its source-invalid
large-lift box-five expectation to box six for non-castle/non-hard input and
checking the original +12 offset. Its independent later rider/horizontal/
balance checks remain passing; they do not certify those unadmitted actors.
Endgame/layout/mode/Bowser checks retain their existing four passes and four
star-timer exit-six / Bowser-damage exit-four failures. The previously recorded
Lakitu/Spiny failure and actual child discrepancies remain open.

All 85 shared units build under strict C90 on x86/x64. Self-tests, bounded
hidden-window message probes and platform purity pass. DOS16 links with the
existing OLDNAMES warning and remains link-only, without runtime/graphics,
resource binding or physical 486 certification. Only shared init_targets.c
changes product behavior; no host adapter gains gameplay logic.

Similar-issue sweep covers every platform initializer-vector alias and the
original common-tail call sites. Balance now falls through drop/common;
large lifts reuse small-lift entries, and common code reuses InitVStf. The
last remaining uses of generic platform/default initialization were exactly
these entries, so both obsolete helpers are removed. Earlier common, firebar,
Piranha, frenzy and group proofs remain passing. No movement, collision or
graphics child body is modified.

Reproduce platform_initialization_fixture.h cases 0..239 using
--fixture=t39-platform-init=N, --platform-init-snapshot and --control-children;
run --pc-coverage separately. Feed roots to enemy_loop_actual_check with final
shared objects and local original PRG. Native target:
mysmb.platform-initialization-chain. Existing owner-local provenance is
unchanged, no third-party implementation is imported. Raw evidence stays in
ignored build/m2-t39-s6, under 3.3 MB within the four-MB budget and twenty-second
per-recorder limit; retain it for the T39 cross-chain review.

Three owner-authorized test artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 254857 | 3afdf144b0265ac12a6d5cb6dcfc88e962eb4a2fb0f69bcffdab009ffc106517 |
| mysmb32.exe | 338826 | 08c4151e2d786e6d95c022dd2302bad711c0f2dc400796566558cad65862a04b |
| mysmb64.exe | 345378 | 3291a887195e110c96e24f75ec1bfaf07eaabc3863469591fe9e5b9f7e838573 |

## S7 admission: Actor vector and retainer call boundaries

After S6 commit b2bb5ab, coordinator accepts transfers-179/180. Scope is
RunEnemyObjectsCore, JmpEO, NoRunCode and RunRetainerObj; the first, second
and fourth are expected new: the two dispatch labels are audited mismatches,
while RunRetainerObj is open. NoRunCode is a retained match. Baseline
1,046/1,992, three expected new, maximum 1,049; four scoped receivers.
Original range $C882-$C8DF contains the actor selector, 34 vector words, an
empty return and the retainer's three ordered children.

Restore ObjectOffset reload, ID-below-$15 selector zero or ID-minus-$14,
source JumpEngine scratch and every vector entry. Split the existing platform
child binding into distinct RunLargePlatform/RunSmallPlatform boundaries and
combine Bowser's existing step/draw under its single RunBowser boundary.
These pending child bodies remain under their S9/later source owners and earn
no credit. A shared enemy/dispatch_targets.c owns these source entry seams;
temporary platform forwarding seams are specifically allowed here to restore
the original parent edges before S9 replaces their bodies. They are not new
host abstractions or claims that the legacy platform child is correct.

Separate RunRetainerObj into offscreen, relative-position and graphics calls
in that order. Existing graphics moves to an explicitly named retainer OAM
child without caller position/offscreen work; preserve its remaining behavior
and record actual mismatches. This is boundary extraction, not an unadmitted
graphics rewrite. CMake and DOS build manifests must include the new shared
unit. No platform-specific gameplay or movement/collision repair is admitted.

ROM proof compares all vector words, selector branches and source-reachable
NMI live-slot routes. A caller-only harness may compare every immediate
child's full RAM input and then substitute its recorded original return;
this certifies only the four scoped call nodes. Separate full native-child
runs must retain all actual differences, including OAM/relative/offscreen
children. Do not mask scratch or patch original CPU/stack/ROM. NoRunCode
retains its no-op body despite the caller's required scratch writes.

Independent native call/write contracts, retained regressions, strict C90
x86/x64, DOS16 link, platform purity and hidden-window checks precede three
EXE delivery. Sweep all run-object callers, source vector aliases, retainer
callers and tests relying on old combined child seams. Existing local ROM/
listing provenance remains unchanged; no external implementation import.
Raw evidence stays in ignored build/m2-t39-s7, eight-MB budget for vector and
retainer roots/children, twenty-second per-recorder timeout, S7 ownership.
Stop on unadmitted repair or concealed child discrepancies. S8/S9 stay planned.

## S7 original actor-vector and retainer proof

S7 closes three expected new caller nodes and retains NoRunCode:
1,046 -> 1,049/1,992, four scoped, no unfinished scoped transfer. Admission
confirms two audited mismatches (RunEnemyObjectsCore/JmpEO), one open target
(RunRetainerObj), one retained match and maximum 1,049. Transfers-179/180
register exact custody before implementation. S8 normal-actor/movement dispatch
is next; T39 remains open.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| RunEnemyObjectsCore | $C882 | Reload ObjectOffset; below-$15 selector zero, otherwise ID minus $14; dispatch every original target with exact child input; new caller match |
| JmpEO | $C88F | All 34 words bind original targets; JumpEngine stores $C891 and target in scratch before the child; new caller match |
| NoRunCode | $C8D6 | Original RTS remains empty; all seven no-op IDs preserve child semantics after caller scratch; retained match |
| RunRetainerObj | $C8D7 | GetEnemyOffscreenBits, RelativeEnemyPosition then EnemyGfxHandler with exact RAM handoffs; caller-only match; new caller match |

**Caller equivalence is not child equivalence.** Original caller comparison
passes 360/360 across x86/x64. The harness compares every immediate child's
complete RAM input before applying its recorded original return; it certifies
only the four scoped nodes. It never patches original ROM, PC, return stack
or child execution, and does not mask scratch. Hardware-stack RAM is excluded
while mapped $0109-$0139 variables remain compared. Actual native-child runs
are separate and match only 42/360: 174 vector and 144 retainer mismatches
remain visible. No child interior receives credit from the caller harness.

All 54 actor IDs and 34 selectors execute through natural NMI live-slot paths;
the two source selector-branch outcomes occur. All twelve scoped instructions
execute and all 68 vector bytes match original. Ninety-two source vector child
records verify target identity, current slot and $04-$07 before entry. The
seven NoRunCode IDs have no child body; WarpZoneObject uses its previously
proved native body with a closed source gate. Seventy-two retainer routes
cover all six slots, both world-dependent drawings and position/offscreen
variants, with 216 ordered original child records. All 180 observer-free
coverage runs produce identical frame records.

The parent now has separate large/small platform entry identities and one
Bowser child entry. Their temporary shared-game seams preserve legacy child
behavior until the already planned S9/later owners replace it. This narrow
structural exception was explicit at admission; it grants no platform/Bowser
conformance. RunRetainerObj now owns offscreen, relative and graphics order;
the OAM function consumes completed relative/offscreen state and retains its
existing unproven drawing body, including its old guard. No host gameplay
logic or platform selection is introduced.

Independent native checks cover every actor ID in all six slots, no-op scratch,
source loop gates/high-bit references and WarpZoneObject combinations. Retainer
call contracts cover 1,536 complete-RAM inputs per width with strict child
order and argument checks. Cannon/no-op tests now expect the source caller's
scratch writes instead of incorrectly demanding unchanged RAM. Fifteen full
initializer/stream/retainer/platform regressions per width pass. The complete
actual matrix is 3,164/3,606: all 3,118 prior matches remain, four old loop
mismatches are fixed and 42 new actual routes match. Loop roots are now 192/192.
The remaining 442 differences are the prior 124 Spiny differences plus 318
newly exposed actor/retainer differences, not caller proof failures.

Known child boundaries remain assigned without new transfers:
RunNormalEnemies belongs to planned S8; RunBowserFlame, RunFirebarObj,
RunSmallPlatform and RunLargePlatform belong to planned S9; RunBowser,
RunFireworks and RunStarFlagObj retain their later source-order admission.
These labels remain with T19 S5 until received. GetEnemyOffscreenBits and
RelativeEnemyPosition remain with T16 S4; EnemyGfxHandler remains with T17 S6.
Already proved caller nodes such as PowerUpObjHandler do not make their
unproved graphics descendants complete. Preserve actual mismatch logs for
those consumers rather than accepting an ancestor-wide match.

All 86 shared units build in strict C90 on x86/x64; self-tests, bounded hidden
window response and platform purity pass. DOS16 links with its existing
OLDNAMES warning and remains link-only, without runtime/graphics, resource
binding or physical 486 certification. Endgame/layout/mode/Bowser checks retain
the four existing passes and four star-timer/Bowser-damage failures. The prior
Lakitu/Spiny smoke gap stays open. Three test EXEs are refreshed together.

Similar-issue sweep covers all run-object callers, all vector aliases,
retainer callers and the three standalone tests that stubbed former combined
entries. CMake and DOS manifests include dispatch_targets.c. The removed
retainer position/offscreen calculation has one shared-game caller owner;
no duplicate production path remains. No unrelated actor body is rewritten.

Reproduce actor_dispatch_fixture.h cases 0..179, --fixture=t39-actor-dispatch=N,
--actor-dispatch-snapshot and --control-children; run --pc-coverage separately.
Cases 0..107 are vector roots; 108..179 are retainer roots. The caller checker
links core/lifecycle for vector cases, or dispatch_targets with the test-only
MYSMB_RETAINER_CALLER definition for retainer cases. enemy_loop_actual_check
links all real shared children and must retain the separate failures above.
Focused CTests are mysmb.enemy-dispatch-smoke and mysmb.retainer-call-chain.
Existing local provenance is unchanged, no third-party implementation import;
raw evidence is under 2.9 MB in ignored build/m2-t39-s7, within the admitted
eight-MB and twenty-second per-recorder bounds, retained for T39 review.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255053 | d1a616a10ac7af748816067e0196b0f2456d88f478bbd675b4d1755a4e49c000 |
| mysmb32.exe | 339368 | db9640d53c93d1f7b6cb7c3de532a1d1e259675cec372b43358876252f472e32 |
| mysmb64.exe | 346463 | 46a52706949a9a8e163e3949fa21922279dc0e6cae172797eb3224e2b25a8418 |

## S8 admission: Normal actor and movement vector

After S7 commit df340c0, coordinator accepts transfer-181 for RunNormalEnemies,
SkipMove, EnemyMovementSubs and NoMoveCode. All four are open and expected
new: baseline 1,049/1,992, maximum 1,053. Shared owner is enemy/normal.c,
source $C8E0-$C934. S7 supplies the actor-vector predecessor; S9 is next.

Restore the 21-word movement vector and JumpEngine scratch. ID $0E must bind
the existing MoveJumpingEnemy entry, not its legacy guarded bulk adapter.
Keep the normal caller's attribute clear, offscreen/relative/graphics/box/
background/enemy/player collision sequence, post-child TimerControl decision,
optional movement and final OffscreenBoundsCheck. Move the existing Goomba
selection into the normal graphics entry so the caller has one EnemyGfxHandler
boundary; do not rewrite drawing children. Existing legacy aggregate interfaces
retain their declared player-box setup behavior, outside this source entry.

Prove all four caller nodes using unchanged original NMI live-slot routes,
all normal IDs, both timer paths, exact table bytes, child order and RAM inputs.
The caller harness may apply recorded original child returns only after full
entry comparison. For RunNormalEnemies, keep EnemyMovementSubs native and
observe its selected leaf, proving the two adjacent callers together. Separate
actual-child comparisons retain downstream graphics/collision/movement gaps.
No CPU/stack/ROM patching, scratch masking or child-body certification.

Independent native checks cover child-mutated ID/timer/flags, no-op movement,
all slots and source write footprints. Strict C90 x86/x64, DOS16 link, purity,
hidden-window response and three EXEs complete the operational track. Sweep
normal graphics callers, every movement alias and legacy jumping adapters.
No host-platform gameplay or unrelated actor repair is admitted. Existing
owner-local ROM/listing provenance is unchanged; no external import. Raw
records stay in ignored build/m2-t39-s8, eight-MB budget, twenty-second recorder
timeout and S8 cleanup ownership. Stop on unadmitted repair or hidden failures.

## S8 original normal-actor and movement-vector proof

S8 closes all four expected caller nodes: 1,049 -> 1,053/1,992.
Transfer-181 registered all four open nodes before implementation; no scoped
node remains unfinished or transferred. T39 stays open; S9 is next.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| RunNormalEnemies | $C8E0 | Clear sprite attributes; exact seven preprocessing children, post-child timer gate, native movement vector and terminal bounds; new caller match |
| SkipMove | $C902 | Both timer branches reach the same final OffscreenBoundsCheck; no flag/handled-result early return; new caller match |
| EnemyMovementSubs | $C905 | All 21 source words, aliases and JumpEngine scratch agree; current post-child ID selects the original movement entry; new caller match |
| NoMoveCode | $C934 | Original empty RTS for IDs 9 and 19; vector scratch remains, no movement child is called; new caller match |

The shared caller now binds one normal graphics entry, including Goomba
selection inside that child, and retains all later collision/movement/bounds
phases. The vector restores original $04-$07 scratch and calls MoveJumpingEnemy
directly, removing its former guarded legacy adapter from this path. The
aggregate test interface retains its existing box-preservation contract;
it is not the source single-slot gameplay caller.

Original-ROM caller comparisons pass 252/252 across x86/x64, covering 84
normal roots and 42 movement roots (all 21 IDs, slots zero/five, paused and
unpaused normal paths). The normal-root proof keeps EnemyMovementSubs native.
Only its selected movement leaf is substituted, after exact full RAM input
comparison. Recorded original children run unchanged; no ROM, CPU, return
stack or scratch patch is used. Hardware-stack bytes are excluded while
mapped $0109-$0139 state remains compared. Caller proof grants no child-body
credit. All 126 observation-free frame records equal their observed records;
this checks recorder noninterference, not native full-frame equivalence.

All 16 scoped instructions execute; the timer branch takes both outcomes. The 42 vector bytes match the ROM. Child order/input records total 710 for normal roots and 38 for movement roots. Separate actual native-child comparisons match 58/252; remaining normal/movement failures are {'normal': 168, 'movement': 26}. These are retained child gaps, never masked or counted as caller failures.

The final actual matrix matches 3222/3858 with all 3,164 previous matches retained. Fifteen full initializer/stream/platform/retainer regressions per width pass. Independent normal-caller tests cover 756 cases per width with child-mutated ID, timer and flag, source ordering, no-op aliases and complete 2,048-byte write footprints. Existing vector, retainer and cannon call-contract tests also pass.

All 86 shared units compile in strict C90 on x86/x64. Both self-tests and
bounded hidden-window response probes pass, as does platform purity. DOS16
links with the existing OLDNAMES warning; it has no runtime/graphics, resource
binding or physical 486 performance claim. The focused regression matrix
retains the prior star-timer and Bowser-damage failures; Lakitu/Spiny debt is
unchanged. Three EXEs are refreshed together.

Similar-issue sweep finds one production normal-graphics caller, one movement
vector, and the old guarded jumping adapter used only by its legacy aggregate.
All 21 dispatch aliases and both no-op IDs are checked. No additional platform
logic, child algorithm repair or duplicate gameplay path is introduced.
Children retain their exact existing ledger owners: graphics/offscreen/relative,
collision and movement bodies await their source-order admissions. S9 receives
the following flame/firebar/platform wrappers; T40 begins MovePodoboo.

Reproduce normal_actor_fixture.h cases 0..125 using --fixture=t39-normal-actor=N,
--normal-actor-snapshot and --control-children; run --pc-coverage independently.
normal_actor_snapshot_check links only enemy/normal.c and explicit child
boundaries; enemy_loop_actual_check links every real child. The independent
focused test is mysmb.normal-enemy-caller. Existing owner-local provenance
is unchanged, with no imported third-party implementation. Raw recordings
remain beneath ignored build/m2-t39-s8 for T39 review, within eight MB and
20 seconds per recorder process. Independent cases run concurrently with
unique output paths; production and comparison semantics are unchanged.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255159 | d8de51d91c324aa87312ec7b4e3efa77c65ea8a086cebc56f3b2080d0dd1d644 |
| mysmb32.exe | 339440 | f0ff9837f43b039b69b3f92507c127cac31550d833b37dfae78a6d3a8f631dde |
| mysmb64.exe | 347558 | 6c58fda9394ed85a05ddb8dab50f7c571f189ba0ac08d96b92ab21c908de7eeb |

## S9 admission: Special actor and platform callers

After S8 commit 01578a4, coordinator accepts transfers-182/183. Scope is
RunBowserFlame, RunFirebarObj, RunSmallPlatform, RunLargePlatform, SkipPT,
LargePlatformSubroutines and EraseEnemyObject. The first six are open and
expected new; EraseEnemyObject is a retained match. Baseline 1,053/1,992,
maximum 1,059. Original range $C935-$C9AF follows the S8 movement vector;
MovePodoboo begins the next source-order slice. T39 remains active.

Shared owners are enemy/dispatch_targets.c, platform/actor child boundaries
inside game/, existing collision/OAM entries and enemy/lifecycle.c. Host
platform/ code is excluded. Replace the temporary large/small forwarders with
the actual source caller phases; separate the existing mixed platform body
into collision, movement and drawing responsibilities. Child interiors keep
their own ledger status and actual comparisons. Do not promote a renamed or
extracted legacy child as ROM-equivalent. Required extraction is structural,
not permission to invent alternative platform physics or collision rules.

The flame caller executes ProcBowserFlame, offscreen, relative, box, player
collision and final bounds. Separate the legacy flame body's extra drawing
and ad-hoc collision from its movement boundary; graphics remains a child of
ProcBowserFlame in the source. Firebar always performs final bounds, including
when its old injury return signal is nonzero. Small platforms do offscreen,
relative, box, collision, relative again, draw, move and bounds. Large platforms
do offscreen, relative, box, collision, post-child timer-gated movement vector,
relative again, draw and bounds. The seven-entry vector uses post-child ID,
subtracts $24 and reproduces original JumpEngine scratch. Shared erasure must
still clear exactly eight fields for all six slots.

Original logic evidence covers exact source edges/table words and both timer
branches using bounded original-NMI live-slot records. Compare every child's
entire RAM input before any recorded-return substitution; keep the large
movement vector native while observing selected leaves. Keep separate actual
native-child comparisons and preserve all prior matches. No original ROM,
CPU, hardware-stack or scratch patching. Independent native mutation tests
exercise child changes, ordering, terminal bounds and erasure write footprints.
Operational evidence is strict C90 x86/x64, DOS16 link, hidden-window response,
platform purity and the three test EXEs once for the chain. T39 closure then
reviews its combined matrix and exact 86-node dispositions.

Existing owner-local ROM/listing provenance and unreviewed redistribution
status are unchanged; no external implementation import. Raw recordings and
all generated material stay in ignored build/m2-t39-s9, with eight-MB raw
budget and twenty seconds per recorder process. Use unique per-case paths and
checkpoint summaries for concurrent independent observations; account bytes
without racing deletion of other workers' temporary coverage files. S9 owns
cleanup after T39 review. Stop on unadmitted child repair or masked failure.

### S9 implementation checkpoint: flame and firebar boundaries

Admission gate confirms seven scoped labels, six expected new, one retained,
baseline 1,053 and maximum 1,059. No S9 node is complete yet. Shared
enemy/special_callers.c now expresses $C935 and $C947; objects.c retains
separate ProcBowserFlame ($D1EB) and ProcFirebar ($CD3C) child bodies with
their prior unproved interiors. The flame caller replaces its old inline
rectangle/injury shortcut with GetEnemyBoundBox and PlayerEnemyCollision.
The firebar caller always executes OffscreenBoundsCheck; its legacy aggregate
injury return is preserved only as an outward compatibility result.

Strict C90 caller tests pass 3,072 scenarios on each of x86/x64, covering all
six slots, every byte-valued legacy return, child flag/timer mutation, exact
call order and complete RAM write footprint. Mode and object-array integration
tests link the changed units with all other shared units and pass on both
widths. Platform purity passes. Original-ROM comparisons, remaining platform
implementation, full three-target delivery and S9 closure are still pending.
The committed test EXEs remain the S8 artifacts until the complete S9 P.

The remaining source boundaries are $C94D RunSmallPlatform, $C965
RunLargePlatform, $C979 SkipPT and $C982 LargePlatformSubroutines. The vector
words begin $C98A and end $C997; JumpEngine scratch must retain $C989 and
the selected target. Targets are BalancePlatform ($D432), YMovingPlatform
($D5D3), MoveLargeLiftPlat ($D64F, two aliases), XMovingPlatform ($D607),
DropPlatform ($D631) and RightPlatform ($D63D). Erasure remains $C998.

The current platform aggregate mixes collision, early drawing and movement,
and has no separate SmallPlatformBoundBox ($E24C), LargePlatformBoundBox
($E273), SmallPlatformCollision ($DB7B) or LargePlatformCollision ($DB45)
entries. Extraction must preserve meaningful child responsibilities; a no-op
box function or forwarding the entire aggregate at each phase is not an
acceptable implementation. Source platform collision state is $03A2+slot:
large uses $FF/no-contact or a slot index, while small uses zero/no-contact
or its two-box counter. Audit those handoffs before replacing the temporary
large/small wrappers. DrawSmallPlatform ($ED66), DrawLargePlatform ($E5C8)
and MoveSmallPlatform ($D655) retain independent child status. Neither their
existing coordinate recalculation nor legacy platform physics is certified
by a future caller-only comparison.

## S9 original special-actor and platform proof

S9 closes six expected new caller nodes and retains EraseEnemyObject:
1,053 -> 1,059/1,992. Transfers-182/183 establish exact receiving ownership.
Seven scoped nodes are complete; no scoped unfinished transfer remains.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| RunBowserFlame | $C935 | ProcBowserFlame, offscreen, relative, box, player collision and bounds in exact source order; new caller match |
| RunFirebarObj | $C947 | ProcFirebar always followed by bounds; injury return cannot truncate the caller; new caller match |
| RunSmallPlatform | $C94D | Offscreen, relative, small box/collision, repeated relative, draw, move and bounds; new caller match |
| RunLargePlatform | $C965 | Offscreen, relative, large box/collision, post-child timer gate and native movement vector; new caller match |
| SkipPT | $C979 | Both timer branches join the repeated-relative, draw and bounds tail; new caller match |
| LargePlatformSubroutines | $C982 | All seven source words, both lift aliases, post-child ID minus $24 and $C989/target scratch agree; new caller match |
| EraseEnemyObject | $C998 | All eight original stores preserved in all six slots; retained actual ROM match |

Original comparisons pass 184/184 across x86/x64: four flame, 32 firebar,
eight small-platform, 28 large-platform, fourteen vector and six erasure
roots per width. All forty scoped instructions execute, both timer outcomes
occur, all fourteen vector bytes match, and 376 original child-entry records
verify complete RAM handoffs. The large vector remains native inside its
caller proof. Recorded child returns are used only after entry comparison;
no ROM, CPU, hardware-stack or scratch patch is made. Hardware-stack bytes
are excluded while mapped $0109-$0139 variables remain compared. All 92
observation-free frames equal their observed records.

**Caller proof is not child proof.** Actual native children match 32/184;
152 differences remain. The final integrated matrix is 3,254/4,042, with all
3,222 prior actual matches preserved. Earlier Spiny, graphics, collision and
movement gaps remain assigned to their existing source-order receivers.

Shared special_callers.c and platform_callers.c replace the mixed actor
entry boundaries. Small-platform drawing precedes movement; large-platform
movement precedes repeated relative positioning and drawing. The old collision
and physics branches are extracted into explicitly unproved child entries,
using $03A2+slot for their source collision handoff. Incomplete balance-partner,
second-small-box, horizontal movement and player-positioning semantics remain
child obligations. The retained X/Right legacy helper is a temporary child
implementation seam, not a claim that the original algorithms are identical.

Platform box entries use the existing shared box/clip primitives. Horizontal
visibility now exposes the full original table byte for the large-platform
$FE threshold while normal consumers retain its upper nibble. Independent
comparison with the previous helper preserves all 1,966,080 legal-viewport
values per width; focused checks distinguish $FC from $FE and small-platform
horizontal masks from vertical bits. Missing original scratch and child box
semantics remain unproved; no offscreen/helper node receives extra credit.

Native caller contracts pass 3,072 flame/firebar cases, 324 platform cases
and 1,536 erasure footprints per width, including child-mutated flags, timer
and ID. Fifteen full initializer/stream/actor tests plus prior normal/vector/
retainer/cannon caller tests pass on each width. The existing star-timer and
Bowser-damage failures remain unchanged; the prior Lakitu/Spiny gap remains.
All 88 shared units build in strict C90, both self-tests and hidden-window
response probes pass, and platform purity passes. DOS16 links with its old
OLDNAMES warning and remains link-only; no DOS gameplay or 486 claim is made.

Similar-issue sweep covers every special actor caller, all platform vector
aliases, legacy aggregate callers and shared bounding-box consumers. There
is one shared gameplay caller path; no host gameplay or runtime emulator was
added. Reproduce special_actor_fixture.h cases 0..91 with
--fixture=t39-special-actor=N, --special-actor-snapshot, --control-children,
and a separate --pc-coverage run. special_actor_snapshot_check links the real
callers/vector/lifecycle and explicit child boundaries; enemy_loop_actual_check
links real children. Focused targets include mysmb.special-actor-caller and
mysmb.platform-caller. Provenance is unchanged; raw records occupy under
2.4 MB in ignored build/m2-t39-s9, within eight MB and twenty seconds per run.
The three required EXEs are refreshed together.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256621 | 2ad05c6c65ab3ee470272c402d62a47b85cf91354b8d24a87239a521a9e970cc |
| mysmb32.exe | 343164 | a0aeee4e8588c1bdd5459669a14eb7442de659f644b862f2a3d079578a3cf868 |
| mysmb64.exe | 350823 | 817bc7745604b80e1a6ebf83b726efd4fe91bf954bf1be9809e7d8308960f513 |

## T39 closure

All nine source-ordered S chains are closed. The complete scoped set contains
86 unique original nodes: 81 new matches and five retained matches. Global
progress is 978 -> 1,059/1,992. Each label is individually complete in the
inventory and has an exact receiving S; no scoped unfinished node remains.
Retained labels are DuplicateEnemyObj, FSLoop, FlmEx, NoRunCode and
EraseEnemyObject. Dependency reuse receives no duplicate completion credit.

| Chain | Scoped | New matches |
| --- | ---: | ---: |
| M2 T39 S1 | 15 | 12 |
| M2 T39 S2 | 5 | 5 |
| M2 T39 S3 | 14 | 14 |
| M2 T39 S4 | 8 | 8 |
| M2 T39 S5 | 9 | 9 |
| M2 T39 S6 | 20 | 20 |
| M2 T39 S7 | 4 | 3 |
| M2 T39 S8 | 4 | 4 |
| M2 T39 S9 | 7 | 6 |

The final integrated matrix executes actual shared C children, with no
recorded-return substitution. It complements the source-node caller/data
proofs and continues to expose unproved downstream bodies.

| Original route family | Actual matches | Remaining differences |
| --- | ---: | ---: |
| loop | 192/192 | 0 |
| stream | 160/160 | 0 |
| init | 220/220 | 0 |
| common | 104/104 | 0 |
| spiny | 36/160 | 124 |
| firebar | 80/80 | 0 |
| fish | 304/304 | 0 |
| bowser-flame | 320/320 | 0 |
| fireworks | 240/240 | 0 |
| bullet-swim | 364/364 | 0 |
| group | 230/230 | 0 |
| small-init | 392/392 | 0 |
| platform-init | 480/480 | 0 |
| actor-dispatch | 42/360 | 318 |
| normal-actor | 58/252 | 194 |
| special-actor | 32/184 | 152 |

Total 3,254/4,042 actual comparisons match; 788 remain. All 3,222 matches
from the S8 baseline are retained. Differences remain within Spiny (124),
actor/retainer children (318), normal-actor/movement children (194), and
special actor/platform children (152). These are comparison cases, not node
counts. They retain their original source-order responsibility; no ancestor
closure certifies an unproved descendant or full-game equivalence.

S9's final 88-unit strict C90 x86/x64 build, DOS16 link, native caller and
cross-chain regressions, hidden-window probes, platform-purity check and
three recorded executable hashes form this T-level delivery. Earlier accepted
S proofs are reused without repeating each node's lifecycle. Legacy platform
child seams, source scratch, graphics/collision/audio gaps, existing native
star-timer/Bowser failures and DOS link-only limits remain explicit.

T39 is closed, while M2 remains incomplete. The next queued source slice
begins MovePodoboo at line 9212 and includes the whole Hammer Bro movement
phase. No T40 packet is admitted by this closure; its exact nodes and S
ownership must be registered under the continuing M2 mandate before editing.
