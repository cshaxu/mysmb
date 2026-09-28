# M2 T36: Vine, hammer, coin and misc-object chains

## Source-order scope and chain plan

The original lines 6730-7200 contain 56 labels. Fourteen cannon/bullet nodes
retain T31 S2 accepted proof. The six chains below target 41 incomplete labels,
maximum 813 from incoming 772. Their current receiver is T24 S2 until each S
is admitted. S1-S4 are closed; S5 score and HUD handoff is next. Numeric S entries below are a plan within
this T; only individual receipt enables implementation.

PowerUpObjHandler (line 7184) begins a state machine continuing into the next
source slice. Keep its existing T24 S2 custody and admit it with those successors
in the next task. It receives no completion credit here. This explicit boundary
keeps a complete chain together; T36 may close 55/56 slice labels, with this
one named consumer exception, not claim the entire slice complete.

| S | Complete source chain | Exact target labels |
| --- | --- | --- |
| S1 | Vine growth, retirement and block write | `VineObjectHandler`, `RunVSubs`, `VDrawLoop`, `KillVine`, `WrCMTile`, `ExitVH` |
| S2 | Hammer allocation and actor lifetime | `HammerEnemyOfsData`, `HammerXSpdData`, `SpawnHammerObj`, `SetMOfs`, `NoHammer`, `ProcHammerObj`, `SetHSpd`, `SetHPos`, `RunAllH`, `RunHSubs` |
| S3 | Coin creation and misc allocation | `CoinBlock`, `SetupJumpCoin`, `JCoinC`, `FindEmptyMiscSlot`, `FMiscLoop`, `UseMiscS` |
| S4 | Misc dispatch and jumping coin lifetime | `MiscObjectsCore`, `MiscLoop`, `ProcJumpCoin`, `JCoinRun`, `RunJCSubs`, `MiscLoopBack` |
| S5 | Coin tally, score and HUD handoff | `CoinTallyOffsets`, `ScoreOffsets`, `StatusBarNybbles`, `GiveOneCoin`, `CoinPoints`, `AddToScore`, `GetSBNybbles`, `UpdateNumber`, `NoZSup` |
| S6 | Power-up initialization | `SetupPowerUp`, `PwrUpJmp`, `StrType`, `PutBehind` |

Retained complete, no new credit: `CannonBitmasks`, `ProcessCannons`, `ThreeSChk`, `FireCannon`, `Chk_BB`, `Next3Slt`, `ExCannon`, `BulletBillXSpdData`, `BulletBillHandler`, `SetupBB`, `ChkDSte`, `BBFly`, `RunBBSubs`, `KillBB`.

## Exact node disposition at T admission

| ROM line | Node | Incoming status | Current receiver | Planned disposition |
| ---: | --- | --- | --- | --- |
| 6730 | `VineObjectHandler` | mapped; evidence incomplete | M2 T24 S2 | S1 |
| 6746 | `RunVSubs` | open | M2 T24 S2 | S1 |
| 6752 | `VDrawLoop` | open | M2 T24 S2 | S1 |
| 6760 | `KillVine` | open | M2 T24 S2 | S1 |
| 6766 | `WrCMTile` | open | M2 T24 S2 | S1 |
| 6780 | `ExitVH` | open | M2 T24 S2 | S1 |
| 6785 | `CannonBitmasks` | ROM-match complete | M2 T31 S2 | Retained |
| 6788 | `ProcessCannons` | ROM-match complete | M2 T31 S2 | Retained |
| 6792 | `ThreeSChk` | ROM-match complete | M2 T31 S2 | Retained |
| 6809 | `FireCannon` | ROM-match complete | M2 T31 S2 | Retained |
| 6832 | `Chk_BB` | ROM-match complete | M2 T31 S2 | Retained |
| 6840 | `Next3Slt` | ROM-match complete | M2 T31 S2 | Retained |
| 6842 | `ExCannon` | ROM-match complete | M2 T31 S2 | Retained |
| 6846 | `BulletBillXSpdData` | ROM-match complete | M2 T31 S2 | Retained |
| 6849 | `BulletBillHandler` | ROM-match complete | M2 T31 S2 | Retained |
| 6862 | `SetupBB` | ROM-match complete | M2 T31 S2 | Retained |
| 6876 | `ChkDSte` | ROM-match complete | M2 T31 S2 | Retained |
| 6880 | `BBFly` | ROM-match complete | M2 T31 S2 | Retained |
| 6881 | `RunBBSubs` | ROM-match complete | M2 T31 S2 | Retained |
| 6886 | `KillBB` | ROM-match complete | M2 T31 S2 | Retained |
| 6891 | `HammerEnemyOfsData` | open | M2 T24 S2 | S2 |
| 6895 | `HammerXSpdData` | open | M2 T24 S2 | S2 |
| 6898 | `SpawnHammerObj` | open | M2 T24 S2 | S2 |
| 6904 | `SetMOfs` | open | M2 T24 S2 | S2 |
| 6919 | `NoHammer` | open | M2 T24 S2 | S2 |
| 6928 | `ProcHammerObj` | mapped; evidence incomplete | M2 T24 S2 | S2 |
| 6952 | `SetHSpd` | open | M2 T24 S2 | S2 |
| 6962 | `SetHPos` | open | M2 T24 S2 | S2 |
| 6977 | `RunAllH` | open | M2 T24 S2 | S2 |
| 6978 | `RunHSubs` | open | M2 T24 S2 | S2 |
| 6988 | `CoinBlock` | mapped; evidence incomplete | M2 T24 S2 | S3 |
| 7000 | `SetupJumpCoin` | mapped; evidence incomplete | M2 T24 S2 | S3 |
| 7014 | `JCoinC` | mapped; evidence incomplete | M2 T24 S2 | S3 |
| 7025 | `FindEmptyMiscSlot` | mapped; evidence incomplete | M2 T24 S2 | S3 |
| 7027 | `FMiscLoop` | open | M2 T24 S2 | S3 |
| 7033 | `UseMiscS` | open | M2 T24 S2 | S3 |
| 7038 | `MiscObjectsCore` | mapped; evidence incomplete | M2 T24 S2 | S4 |
| 7040 | `MiscLoop` | open | M2 T24 S2 | S4 |
| 7053 | `ProcJumpCoin` | mapped; evidence incomplete | M2 T24 S2 | S4 |
| 7071 | `JCoinRun` | open | M2 T24 S2 | S4 |
| 7088 | `RunJCSubs` | open | M2 T24 S2 | S4 |
| 7093 | `MiscLoopBack` | open | M2 T24 S2 | S4 |
| 7100 | `CoinTallyOffsets` | open | M2 T24 S2 | S5 |
| 7103 | `ScoreOffsets` | open | M2 T24 S2 | S5 |
| 7106 | `StatusBarNybbles` | open | M2 T24 S2 | S5 |
| 7109 | `GiveOneCoin` | open | M2 T24 S2 | S5 |
| 7125 | `CoinPoints` | open | M2 T24 S2 | S5 |
| 7129 | `AddToScore` | open | M2 T24 S2 | S5 |
| 7134 | `GetSBNybbles` | open | M2 T24 S2 | S5 |
| 7138 | `UpdateNumber` | open | M2 T24 S2 | S5 |
| 7145 | `NoZSup` | open | M2 T24 S2 | S5 |
| 7150 | `SetupPowerUp` | mapped; evidence incomplete | M2 T24 S2 | S6 |
| 7163 | `PwrUpJmp` | open | M2 T24 S2 | S6 |
| 7175 | `StrType` | open | M2 T24 S2 | S6 |
| 7176 | `PutBehind` | open | M2 T24 S2 | S6 |
| 7184 | `PowerUpObjHandler` | mapped; evidence incomplete | M2 T24 S2 | Next source-slice consumer |

Each S uses one shared game owner and completes original branch/read/write/
call/data proof plus operational tests, all three builds and artifacts. S2
joins adjacent hammer spawn and processing through the same ordinary-frame
lifecycle; it must exercise both enemy-spawn and misc-dispatch entries. S3
preserves its score child boundary; S4 consumes existing hammer/gravity/OAM
children; S5 owns the score/HUD callers, not the status-output children; S6
owns setup, not the following power-up state machine. Later admissions name
exact entry/exit addresses and route fixtures before implementation. T closure
reuses accepted node proof and runs one final cross-chain matrix.

## S1 admission: complete vine actor chain

Transfer-148 receives VineObjectHandler (mapped; evidence incomplete),
RunVSubs, VDrawLoop, KillVine, WrCMTile and ExitVH (open). Scope six,
expected six, incoming 772, maximum 778. The original $B94B actor entry
through ExitVH is reached by RunEnemyObjectsCore and consumes T35's proven
height table. Shared game/vine.c owns state and call order. DrawVine,
GetEnemyOffscreenBits, RelativeEnemyPosition, EraseEnemyObject and
BlockBufferCollision retain their child ownership and receive no new credit.

Move the actor from objects.c. Put the original slot-five gate in the actor,
not its dispatcher. Preserve frame-bit growth and byte wrapping; height gates;
relative then offscreen then indexed draw loop; horizontal offscreen retirement
in reverse vine order; post-child height/count reads; and empty block-buffer
write only for height >=20 and row <D0. Remove invented flag/ID checks and
index/count clamps. Valid growth state has one or two vine entries. Expose the
existing collision helper's computed row before its invalid-row return, so
the caller can make the original row decision; preserve its address algorithm
and return behavior. This is a child output-contract seam, not child proof.

ROM proof uses source-RAM fixtures at ordinary NMI/actor dispatch, captures
root and direct child entry/return, compares original branch decisions and
persistent writes, and records actual-child failures separately. No reference
CPU/stack/ROM/output edits. Focused tests cover child order, reverse erase,
post-child mutation, row/height boundaries and slot gates. Operational proof
includes actor dispatch, relevant regressions, C90 x86/x64 builds, DOS16 link,
platform purity, hidden-window probes and three owner-authorized EXEs.

The supplied ROM and reviewed listing remain local research/build inputs;
no third-party implementation is imported. Temporary evidence belongs only
in ignored build/m2-t36-s1, twenty seconds per run and four MB retained raw
batch. S1 owns cleanup through T review. DOS remains link-only. Closure needs
six exact dispositions, both proof tracks, ledger/tracker updates and hashes.
Sweep every vine state writer, caller, graphics-owned retirement and collision
query consumer. Defer child algorithms and all later chains explicitly.

## S1 original vine actor proof

Six received labels are proven from baseline 772 to 778. The actor has one
shared owner in game/vine.c beside its previously proven setup/table. Its
slot argument is explicit and the original slot-five rejection occurs inside
VineObjectHandler. RunEnemyObjectsCore always dispatches the original entry;
its test now checks that boundary instead of reproducing the old parent gate.
The former objects.c body, invented flag/ID gates and count/index clamps are
removed. Original active growth state has one or two registered vines.

| Node | Address | Proven original contract |
| --- | --- | --- |
| VineObjectHandler | $B94B | Slot-five gate; registered-count height selection; frame-bit growth and byte wrapping |
| RunVSubs | $B96A | Height-eight gate; relative position then offscreen information |
| VDrawLoop | $B979 | Draw from zero, increment byte index, compare against current post-child count |
| KillVine | $B98A | Reverse registered-slot erase; signed index termination; clear count/height after final child |
| WrCMTile | $B999 | Re-read height; X=6/Y=1B/A=1 collision child; row D0 gate; write 26 only to empty cell |
| ExitVH | $B9B7 | Early/final return; original X reload has no additional persistent RAM write |

Forty-two source-RAM scenarios execute ordinary NMI/GameEngine and selected
RunEnemyObjectsCore slots, including every non-five slot, one/two vine entries,
height/frame combinations, height/Y wrapping, both horizontal edges and block
row/content gates. Ten branch sites have both outcomes and all six labels
are executed. Original root/child return PCs and depths are read from the
actual stack; no CPU, stack, ROM or output mutation is performed. Observed,
coverage-enabled and unobserved frame outputs are byte-identical.

Isolated caller comparison replays observed original child returns and checks
child identities/arguments plus 1,791 persistent RAM bytes. Scratch 0-7 and
hardware stack are excluded except digit data 0133-0139. The block child
observer also verifies original X=6/A=1 and records Y=1B; its native seam maps
that sprite-object X to enemy slot five and returns the original row/address.
All 84 caller comparisons match across x86/x64. EraseEnemyObject's proven
A=0 return contract supplies the caller's final clears; its body is unchanged.

Actual native children are independently executed: 52 matches and 32 failures,
identical across widths. Failing cases are 5,7,13,15,17,19,21,23,25,27,31,32,
34,37,39,41 on each width. All differences are OAM Y bytes 0200,020C,0210 or
0214. The existing DrawVine/ChkFTop clipping uses an extra host comparison
instead of the original wrapped subtraction. These child nodes retain
M2 T17 S6 custody, are recorded in TODO and receive no completion credit.
Neither the full actor's visual output nor full-frame equivalence is claimed.

Reproduce vine_actor_fixture.h cases 0..41 with one frame, warmup one, zero
buttons, --fixture=t36-vine=N, --vine-actor-snapshot and --control-children.
Repeat with --pc-coverage and without observers. Build both modes of
vine_actor_snapshot_check.c and run verify_vine_actor_snapshots.py against
the contained batch and owner ROM. The caller test has explicit child
substitutions; the separate actual test links the real game children.

Independent tests pass 2,560 combinations per width, plus non-five slot gates
and child mutations of count/height. They verify relative/offscreen/draw order,
reverse erase, post-child re-reads, frame/height boundaries, row gates and empty
cell preservation. Enemy dispatch and cannon-child boundary tests pass on
both widths. Fourteen bubble/fireball OAM, player route, status, mode, vine OAM
and vine setup regressions pass; two enemy-terrain regressions also pass.
All 70 shared units compile in strict C90 for both Windows widths. Self-tests,
two-second hidden-window/message probes and platform purity pass. DOS16
compiles/links with the existing OLDNAMES warning; it remains link-only,
without resource binding or DOS/486 gameplay qualification.

The collision helper exposes its already-computed row before the invalid-row
return. Its coordinates/address computation and return decisions are unchanged;
no child conformance credit follows from this seam. The consumer sweep covers
normal terrain, frenzy landing, side collision, power-up ground/side paths,
walking landing and hammer-bro terrain: all existing callers still gate terrain
values on successful return. Only the vine caller consumes the row on failure.
The old actor has one production dispatcher and direct test callers; all now
pass the original slot explicitly. OAM remains drawing-only and platform
sources are untouched. Shared-game setup tests link the shared library now
that vine.c also owns the actor's declared child dependencies.

Final owner-authorized local P1 artifacts:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258679 | 99a761d677a492204831625b33c1cdf03ae32f7449c90e53b6cca98702764875 |
| mysmb32.exe | 328190 | 3889aea4df77bc586c18da9b2f7ba2bc983317a27d60b8095cc2a207a1f06c8e |
| mysmb64.exe | 335314 | 8a56a4a92fa73667f972750c9f45d25086e942da4e4a481984c2c381f4b26257 |

Retained raw evidence: 2046157 bytes, below four MB.
Six received labels complete within their caller contracts, six expected; no received-node transfers. Progress 772 -> 778 / 1,992. T36 remains open for S2-S6 and its explicit next-slice consumer boundary.

## S2 admission: hammer allocation and actor lifetime

Transfer-149 receives ten labels, nine open and ProcHammerObj mapped with
incomplete evidence. Scope and expected matches are exactly HammerEnemyOfsData,
HammerXSpdData, SpawnHammerObj, SetMOfs, NoHammer, ProcHammerObj, SetHSpd,
SetHPos, RunAllH and RunHSubs. Baseline 778 / 1,992, maximum 788.
Original tables start at $BA89/$BA92; SpawnHammerObj spans $BA94-$BAC2,
and ProcHammerObj spans $BAC3-$BB37. One shared game/hammer.c owner receives
both entries from the existing hammer-bro and misc dispatch callers.

Preserve the fixed second LSFR byte, the original enemy-flag indexed read
including offset six, success carry as the returned byte, and exactly three
spawn writes. Preserve freeze, attachment/countdown, release speed table,
ObjectOffset reloads, carry/page arithmetic and child order: gravity,
horizontal motion, player collision, offscreen, relative, bounding box, draw.
No invented parent-active or slot clamp. Legal facing values are one and two.
Original shared movement and position primitives provide child boundaries;
existing player-hammer collision and bounding-box algorithms retain their
separate obligations. Interface extraction gives no child conformance credit.

The ROM track uses ordinary NMI source-RAM fixtures through hammer-bro spawn
and misc dispatch, observing original root/child entry and return without
patching CPU, stack, ROM or outputs. Compare tables, every branch, persistent
writes and ordered child arguments; report actual-child differences separately
from caller comparisons. Native tests cover all allocation candidates,
occupied flags, untouched collision flags, countdown/release/freeze/motion,
page wrapping and child sequencing. Reuse existing recorder and build paths.
One final operational pass runs focused tests, relevant regressions, strict
C90 x86/x64 builds, DOS16 link, platform purity, hidden-window probes and
three owner-authorized local EXEs. DOS remains link-only, not playable proof.

Existing owner ROM and reviewed listing are local research/build inputs only;
no third-party implementation import. Temporary outputs stay under ignored
build/m2-t36-s2, twenty seconds per reference run and four MB retained raw
batch; S2 owns containment through T review. Sweep all spawn/actor callers,
slot ownership, hammer collision and graphics preparation consumers. S3 coin
allocation and child algorithm repair remain outside this receipt. Closure
requires exact dispositions, both proof tracks, tracker/ledger and hashes.

### S2 implementation checkpoint (not closure)

Admission gate passes: Total 1992, Complete 778, MappedPending 131,
Open 1083, ScopeCount 10, ExpectedDelta 10, MaximumComplete 788. All ten
received names above remain incomplete; no progress credit is added.
Shared game/hammer.c now owns the two tables and allocation/actor entries.
The legacy misc caller supplies ObjectOffset at the hammer child boundary;
the rest of MiscLoop remains with S4. The existing bounding-box child is
exposed unchanged, with its missing screen-edge clipping still requiring
separate child proof. The existing collision child is exposed unchanged.
Motion and position use the already-declared shared primitives.

Both original ROM table bindings match (eleven bytes). Strict C90 compilation
of changed game units and the independent hammer-chain test passes on x86
and x64: 9,984 cases per width cover every random byte, allocation rejection,
untouched RAM, all byte states, freeze, facing, slot, page carry and child
order, including a child-mutated ObjectOffset reload. Documentation governance
passes. These are preliminary checks, not ROM caller equivalence or P delivery.
Original natural-entry/return comparisons, actual-child diagnostics, final
three-target builds and artifact refresh remain required before S2 closure.

## S2 original hammer lifecycle proof

All ten received nodes are proven; progress 778 -> 788 / 1,992. One shared
game/hammer.c owner supplies both production entries. The old objects.c
allocation/actor bodies and private horizontal movement copy are removed.
The original fixed LSFR address, indexed enemy flag (including offset six),
three spawn writes, carry result, state branches, reloads and child order
replace the extra parent checks, slot clamp and collision-flag clear.

| Node | Address | Proven original contract |
| --- | --- | --- |
| HammerEnemyOfsData | $BA89 | Nine allocation dependency offsets; all candidates exercised |
| HammerXSpdData | $BA92 | Two released speeds; both legal directions exercised |
| SpawnHammerObj | $BA94 | Fixed second LSFR byte, low-three-bit selection and bit-three fallback |
| SetMOfs | $BAA0 | Misc and indexed enemy occupancy checks, ObjectOffset parent, three writes and success carry |
| NoHammer | $BABF | No persistent writes and clear carry on either allocation rejection |
| ProcHammerObj | $BAC3 | Timer gate, masked state, parent read, gravity and horizontal motion with original object offset |
| SetHSpd | $BAF3 | Vertical speed FE, parent state bit-three clear, indexed facing speed and ObjectOffset reload |
| SetHPos | $BB09 | Byte countdown, parent X+2 with page carry, Y-0A and high byte one |
| RunAllH | $BB28 | PlayerHammerCollision after movement, using reloaded misc slot |
| RunHSubs | $BB2B | Offscreen, relative position, bounding box and drawing in original order |

Sixty-three source-RAM cases enter through ordinary NMI/GameEngine. Cases
0-26 exercise all nine allocation candidates, occupied misc slots and occupied
enemy flags through the actual hammer-bro spawn caller. Cases 27-62 cover
attachment, release, flight and freeze across all nine misc slots with both
directions and coordinate carry/wrap. The LSFR initialization accounts for
the original NMI rotation; no CPU, stack, ROM or output is modified. Original
stack depth/return address determines root and child observation boundaries.
Spawn return carry is captured from the original processor status.

Both ROM data tables match, eleven bytes total. Six conditional branch sites
execute both outcomes; BNE at BB26 follows LDA #1 and takes its sole reachable
outcome. Every code label executes. Observed, coverage-enabled and unobserved
frame outputs are byte-identical. Root snapshots also match between observed
and coverage runs. Reproduce with hammer_chain_fixture.h cases 0-62, one frame,
warmup one, zero buttons, --fixture=t36-hammer=N, --hammer-chain-snapshot and
--control-children; repeat with --pc-coverage and without observers.

The isolated caller comparison replays observed original direct-child returns,
checks child identity/slot plus 1,791 persistent RAM bytes, and checks spawn
carry separately. It excludes scratch 0-7 and hardware stack except digit
data 0133-0139. All 126 x86/x64 caller checks match. The independent actual-child
build also matches all 126 entries and returns for these scenarios. This is
bounded root evidence; child interiors, untested screen-edge clipping and
whole-frame/game equivalence are not newly certified. The existing misc box
child still lacks the original screen-edge clipping; its receipt remains
with the later collision slice. No child node receives completion credit.

Independent native tests pass 9,984 cases per width: every random byte,
rejection path, untouched RAM, byte state, freeze, facing, slot, page carry
and child order, plus a child-mutated ObjectOffset reload. Both hammer-bro
behavior and OAM regressions pass on both widths, alongside fourteen retained
bubble/fireball/player/status/mode/vine regressions. The OAM test now includes
its existing declared header, fixing its strict-C90 implicit declaration.

All 71 shared C units compile in strict C90 for x86/x64; both executable
self-tests and bounded two-second hidden-window/message probes pass. DOS16
compiles/links with the known OLDNAMES warning. It remains link-only, without
resource binding, DOS playability or 486 performance qualification. Platform
sources are untouched and the platform-purity gate passes.

The caller sweep finds the existing hammer-bro spawn entry and misc actor
dispatch. Misc dispatch supplies the original ObjectOffset input at the
hammer child boundary; remaining MiscLoop behavior belongs to S4. Normal
enemy dispatch already receives ObjectOffset from the engine. Legacy whole
hammer-bro test wrappers remain compatibility callers. Existing player-hammer
collision and bounding-box bodies are exposed unchanged; movement and position
use the shared original primitives. The old combined prepare_hammer helper
has no production caller after this migration and receives no credit.

Final owner-authorized local P1 artifacts:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258041 | 0e80153ae9a269ba8e779322a1bc75ebb73133b894a130d12e9c901688b294b2 |
| mysmb32.exe | 327976 | d1d2cf59a9955edd4991537024d983754c2e936b145816327e69665b23f78b9f |
| mysmb64.exe | 335135 | e7c22215c5206953d1b79bc37deeb8679d4fb600044750e5d669c162c554a417 |

Retained raw evidence: 3005766 bytes, below four MB.
Ten received labels complete, ten expected; no received-node transfers. Progress 778 -> 788 / 1,992. T36 remains open for S3-S6 and its next-slice consumer exception.

## S3 admission: coin creation and misc allocation

Transfer-150 receives CoinBlock, SetupJumpCoin, JCoinC and FindEmptyMiscSlot
(mapped; evidence incomplete), FMiscLoop and UseMiscS (open). Scope and
expected matches are those six labels. Baseline 788 / 1,992, maximum 794.
Original entries are CoinBlock $BB38, SetupJumpCoin $BB51, common JCoinC
$BB6C and FindEmptyMiscSlot $BB84 through UseMiscS $BB92 (end $BB95).
The shared game/coin.c owner receives both creation entries and the allocator.

Preserve the three-slot search 8/7/6 and fallback 8, residual slot store,
and carry from incoming state or CPY #5. CoinBlock uses that carry in SBC
#10; SetupJumpCoin uses the final ASL carry when adding the vertical status
offset. JCoinC sets speed/high-Y/state/sound and ObjectOffset, calls GiveOneCoin,
then increments CoinTallyFor1Ups. Do not clear movement fractions absent from
the original. Migrate the two legacy coordinate-only callers to the actual
entry contracts and remove their duplicated tally calls. Expose the existing
score child and move its caller-owned 1-up tally increment to the original
call boundaries; this extraction does not repair or certify GiveOneCoin.
The independent direct collection caller keeps its existing tally behavior.

One ordinary NMI/player-head-bump route reaches CoinBlock and the above-block
coin path reaches SetupJumpCoin. Controlled RAM scenarios cover both block
slots, slot occupancy/fallback, entry carry, wrapped coordinates and preserved
fraction bytes. Observe original root and score-child entry/return from the
real stack; no PC, stack, ROM or output mutation. Compare original branches,
register-derived inputs, persistent writes and child ordering. Actual native
child comparisons remain separate from isolated caller comparisons.

Operational proof covers focused independent allocator/creation tests, existing
block/coin and relevant regressions, x86/x64 strict C90 builds, DOS16 link,
platform purity, hidden-window probes and three owner-authorized local EXEs.
The existing owner ROM and reviewed listing are local research/build inputs;
no third-party implementation is imported. Outputs remain below ignored
build/m2-t36-s3, twenty seconds per reference run and four MB raw batch;
S3 owns containment through T review. DOS remains link-only. S4 misc lifetime
and S5 score internals remain outside scope. Sweep every creation/allocation
caller and every GiveOneCoin/1-up tally boundary. Closure requires six exact
node dispositions, both proof tracks, tracker/ledger and artifact hashes.

### S3 implementation checkpoint (not closure)

Admission gate passes with Total 1992, Complete 788, MappedPending 130,
Open 1074, ScopeCount 6, ExpectedDelta 6 and MaximumComplete 794. No scoped
node is marked complete yet. Shared game/coin.c now owns the allocator and
both original creation entries with the common JCoinC tail. The coordinate-only
creation API is removed. The two production callers now supply block slot and
original carry/scratch inputs; the above-block path removes the metatile before
creation. Score-child extraction leaves its digit behavior unchanged, moving
the caller-owned 1-up tally increment to JCoinC and direct collection as in
the source. Missing GiveOneCoin extra-life sound remains S5's responsibility.

Strict C90 compilation of the changed shared units passes on x86/x64.
Independent coin-allocation tests pass 16,400 cases per width, covering all
occupancy masks, both carry inputs and block slots, every coordinate byte,
fraction preservation, complete persistent write footprint and post-child
tally behavior. The legacy core test now invokes the original setup contract
and isolates its next coin-collection scenario because setup itself scores.
ROM root/child comparisons and final build/artifact delivery remain pending;
these preliminary tests do not establish node equivalence or S3 closure.

## S3 original coin allocation proof

All six received caller/allocation nodes are proven, 788 -> 794 / 1,992.
The two creation entries, common JCoinC tail and three-slot allocator have
one shared game/coin.c owner. The old coordinate-only creation body is removed;
the creation caller owns the original score call and post-child 1-up tally.

| Node | Address | Proven original contract |
| --- | --- | --- |
| CoinBlock | $BB38 | Allocate; block page/X OR 5/Y minus 10 using allocator-return carry; common tail |
| SetupJumpCoin | $BB51 | Allocate; saved block page; buffer column shifted four times; ADC 20 with final ASL carry |
| JCoinC | $BB6C | Speed FB, high Y/state/sound one, ObjectOffset, GiveOneCoin then increment 1-up-block tally |
| FindEmptyMiscSlot | $BB84 | Start at eight; preserve input carry until a comparison executes |
| FMiscLoop | $BB86 | Scan states at 8/7/6; CPY 5 sets carry; fallback to eight after all occupied |
| UseMiscS | $BB92 | Store selected slot in JumpCoinMiscOffset and return |

Forty-eight controlled source-RAM scenarios execute ordinary NMI/GameEngine,
player head collision and the original BumpBlock/CoinBlock or above-block
CheckTopOfBlock/SetupJumpCoin path. Both block slots, every occupancy mask,
selected slots 6/7/8, both SetupJumpCoin final-ASL carries, tally wrap and
100-coin transitions are covered. No CPU, stack, ROM or output is patched.
Entry carry is read from the original status register and real stack returns
bound root and score-child observation. Both allocator branch sites exercise
both outcomes; every scoped code label executes. Observed, coverage-enabled
and unobserved frame outputs are byte-identical, as are root snapshots in
the observed and coverage runs.

The source audit and original entries show that JumpEngine ASL clears carry
for every legal BlockCode index, including the 5D coin brick. The old native
5D carry-one special case was wrong. Its call now supplies carry zero;
FindEmptyMiscSlot can subsequently set carry when slot eight is occupied.
The old array-layout test's 5D height expectation is corrected accordingly.

Both widths pass all 96 isolated caller comparisons: child identity/slot,
original entry and return state over 1,791 persistent RAM bytes. Scratch 0-7
and hardware stack are excluded except digit data 0133-0139. Actual native
children independently match 48 cases and fail 48, identical across widths.
Every failure is exactly RAM 00FE: original 40, native 01 when the coin count
reaches 100. The existing GiveOneCoin omits Sfx_ExtraLife; that child retains
its existing custody and planned S5 repair, with no credit from this receipt.
This is caller/allocation proof, not complete coin scoring or full-game parity.

Reproduce coin_allocation_fixture.h cases 0-47 with one frame, warmup one,
zero buttons, --fixture=t36-coin=N, --coin-allocation-snapshot and
--control-children; repeat with --pc-coverage and without observers. Build
both modes of coin_allocation_snapshot_check.c; the caller mode explicitly
replays original score-child returns and the actual mode links real game code.
verify_coin_allocation_snapshots.py checks all branches, labels, slot/carry
variants, observer neutrality and cross-width results without masking failures.

Independent native tests pass 16,400 cases per width, checking all allocator
occupancy combinations, both carries and block slots, all coordinate bytes,
untouched fractions, full write footprint and post-child tally mutation.
Twenty block-array/OAM, hammer, bubble/fireball, player/status/mode and vine
regressions pass. The existing core smoke's direct creation call now supplies
the original setup inputs and isolates its following collection test because
setup itself scores. Its previously recorded earlier entrance failure remains
outside this scope; no full core-smoke pass is claimed.

The caller sweep covers both production creation paths and the independent
direct collection path. The score child loses only its misplaced caller-owned
1-up increment; direct collection still increments before calling it, while
JCoinC increments after return. The above-block caller erases the metatile
and queues removal before supplying original buffer inputs to SetupJumpCoin.
Remaining score internals, CheckTopOfBlock behavior and misc lifetime retain
their separate obligations. No platform source contains a new gameplay path.

All 72 shared C units compile in strict C90 on x86/x64; executable self-tests
and bounded two-second hidden-window/message probes pass. DOS16 compiles and
links with the known OLDNAMES warning. It remains link-only without resource
binding, DOS gameplay or 486 qualification. Platform purity passes.

Final owner-authorized local P1 artifacts:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258329 | 727cd4c325df8f90be07beec813c9d6ff6f1b48070455dfeeae19fdac563e37f |
| mysmb32.exe | 328387 | 54c4ddd73b68762aff0c0dbe8245af4ec2defe713e17955405828b07d2f3e187 |
| mysmb64.exe | 336603 | 887767ae45a6510e20b486b73b20b2b7c63b24f0104e603a65b64d4149d655c1 |

Retained raw evidence: 2182652 bytes, below four MB.
Six received labels complete, six expected; no received-node transfers. Progress 788 -> 794 / 1,992. T36 remains open for S4-S6 and its next-slice consumer exception.

## S4 admission: misc dispatch and jumping coin lifetime

Transfer-151 receives MiscObjectsCore and ProcJumpCoin (mapped; evidence
incomplete), MiscLoop, JCoinRun, RunJCSubs and MiscLoopBack (open). Scope
and expected matches are those six labels. Baseline 794 / 1,992, maximum 800.
Original MiscObjectsCore entry $BB96 through MiscLoopBack ends at $BBF7.
Shared game/misc.c owns the complete descending dispatcher and coin states;
the proven S2 hammer entry and S3-created coin state are its dependencies.

Preserve ObjectOffset on every slot including empty entries, zero/high-bit
dispatch, exact state-one gravity and speed-five transition, floatey-state
increment/scroll carry and exact 30 retirement, then relative/offscreen/box/
graphics order. Restore source gravity scratch 00=50,01=03,02=06 and the
ObjectOffset reload. Child return-slot contracts govern the descending loop.
Expose existing coin graphics and its existing clipped bounding-box path
without changing child algorithms. Hammer and coin currently use differing
legacy box children; their eventual unification belongs to the collision
receipt, not an unadmitted algorithm repair here.

ROM proof uses source RAM at ordinary NMI/GameEngine -> MiscObjectsCore,
with empty, single and mixed active arrays, both high-bit states, speed and
state boundaries, scroll carry and retirement. Observe the real root and
direct-child entry/return from actual stack state, never patch CPU, stack,
ROM or outputs. Record direct call arguments, persistent writes, branch
outcomes and separate actual-child differences. Native focused tests cover
all byte states, slot/loop order, scratch and reload contracts, page carry
and child sequencing. One final operational pass runs relevant regressions,
x86/x64 strict C90 builds, DOS16 link, platform purity, hidden-window probes
and three owner-authorized local EXEs. DOS remains link-only.

The existing owner ROM and reviewed listing remain local research inputs;
no third-party implementation is imported. Temporary outputs stay below
ignored build/m2-t36-s4, twenty seconds per reference run and four MB raw
batch; S4 owns containment through T review. S5 score and S6 power-up work
remain unadmitted. Sweep all misc dispatcher callers, state/slot writers,
gravity users and drawing/box consumers. Closure requires six exact node
dispositions, both proof tracks, tracker/ledger and artifact hashes.

### S4 implementation checkpoint (not closure)

Admission gate passes: Total 1992, Complete 794, MappedPending 126, Open 1072,
ScopeCount 6, ExpectedDelta 6, MaximumComplete 800. All six labels remain
incomplete. The original descending misc loop now has one game/misc.c owner;
objects.c retains the unchanged graphics and clipped box child algorithms
behind declared interfaces. Every visited slot supplies ObjectOffset. Coin
gravity now uses the shared sprite-object primitive with the original scratch
parameters and reload, while retirement and graphics retain source ordering.

Strict C90 compilation of changed units passes on x86/x64. Independent misc
lifetime tests pass 13,825 cases per width, covering all byte states, all
nine slots, speed 4/5/6, zero/nonzero scroll carry, exact state30 retirement,
timer-independent coin dispatch, every-slot ObjectOffset and mixed descending
child order. Original ROM root/child comparisons, actual-child diagnostics,
final builds and three artifact updates remain pending before S4 closure.

## S4 original misc lifetime proof

All six received dispatcher/coin caller nodes are proven, 794 -> 800 / 1,992.
One shared game/misc.c owns the complete descending loop; the former loop
body is removed from objects.c. It writes ObjectOffset for empty as well as
active slots, uses the original gravity scratch parameters and slot reload,
and preserves state-one, speed-five and exact-state30 decisions.

| Node | Address | Proven original contract |
| --- | --- | --- |
| MiscObjectsCore | $BB96 | Start the loop at slot eight |
| MiscLoop | $BB98 | Store every slot; skip zero state; high bit selects the existing hammer child |
| ProcJumpCoin | $BBA7 | State-one split; increment floating state; scroll addition with page carry; retire only at 30 |
| JCoinRun | $BBC9 | Sprite offset +0D; force50/up03/max06; gravity; ObjectOffset reload; exact speed-five transition |
| RunJCSubs | $BBE8 | Relative, offscreen, bounding box, coin graphics in source order |
| MiscLoopBack | $BBF4 | Decrement restored misc slot and repeat while nonnegative |

Forty-two controlled source-RAM scenarios use ordinary NMI/GameEngine. The
original vertical-pipe caller runs ScrollHandler before MiscObjectsCore,
providing both zero and one-pixel scroll without mid-call state writes. Cases
include each slot independently, jumping/floating/retiring/hammer states,
an empty array, nine floating objects, nine jumping coins, mixed arrays,
state7F/30 boundaries and frozen hammer behavior. Both scroll carry outcomes
are observed. All six conditional branch sites execute both outcomes and all
six scoped labels execute. Real stack return addresses/depths delimit the
root and direct children; no CPU, stack, ROM or output is patched.

All 84 x86/x64 caller comparisons pass. They check child identity/slot and
1,791 persistent RAM bytes, excluding scratch 0-7 and hardware stack except
digit data 0133-0139. Original scratch constants are separately source-audited
and asserted by the native gravity boundary test. Caller mode replays observed
original child returns; separate builds execute the actual shared children.
All 84 actual-child comparisons also match for these scenarios. This is
bounded misc-root evidence, not new child-internal or whole-game certification.

The recorder's contained child capacity is 64 for this nine-slot root (a full
jumping array invokes 45 direct children); existing modes retain their prior
16-child limit. Empty-array capture has zero children. Observed, coverage-enabled
and unobserved frame outputs are byte-identical; observed/coverage root snapshots
also agree. Reproduce misc_lifetime_fixture.h cases 0-41, one frame, warmup one,
zero buttons, --fixture=t36-misc=N, --misc-lifetime-snapshot and --control-children;
repeat with --pc-coverage and without observers. Both modes of
misc_lifetime_snapshot_check.c and verify_misc_lifetime_snapshots.py check
the declared node/branch/child/carry contracts without masking differences.

Independent native tests pass 13,825 cases per width: every byte state, all
nine slots, returned speeds 4/5/6, both scroll carry outcomes, exact retirement,
timer-independent coin processing and mixed descending child order. Twenty
block-array/OAM, hammer, bubble/fireball, player/status/mode and vine regressions
pass. All 73 shared units compile in strict C90 on x86/x64; executable self-tests,
two-second hidden-window/message probes and platform purity pass. DOS16 compiles
and links with its known OLDNAMES warning, remaining link-only without resource
binding, DOS playability or 486 qualification.

The production dispatcher has one engine caller. Existing coin graphics and
the coin-specific clipped bounding-box body are exposed unchanged. Hammer
dispatch uses S2's original actor entry; no child conformance credit is added.
The older specialized misc gravity helper now has no production caller;
the dispatcher uses the shared sprite-object primitive. The previously recorded
hammer/misc bounding-box difference and S3 GiveOneCoin sound defect remain
explicit. No platform source or other object lifetime is modified.

Final owner-authorized local P1 artifacts:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258345 | 431697e1e6095f26b0b815adecf7e7c81af9a101d0e515d0d5d57a46458ed496 |
| mysmb32.exe | 328676 | 32646c7353541430b5c707d9414bfba0de9dd67034a8a2df4ac5826a68ed6374 |
| mysmb64.exe | 336927 | d9fd0f699fd642449f1b7e62f0d6da50e3c1009e7c1d747c2293a9a5bdae688c |

Retained raw evidence: 2315854 bytes, below four MB.
Six received labels complete, six expected; no received-node transfers. Progress 794 -> 800 / 1,992. T36 remains open for S5-S6 and its next-slice consumer exception.
