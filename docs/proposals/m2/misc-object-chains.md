# M2 T36: Vine, hammer, coin and misc-object chains

## Source-order scope and chain plan

The original lines 6730-7200 contain 56 labels. Fourteen cannon/bullet nodes
retain T31 S2 accepted proof. The six chains below target 41 incomplete labels,
maximum 813 from incoming 772. Their current receiver is T24 S2 until each S
is admitted. S1 and S2 are closed; S3 coin allocation is next. Numeric S entries below are a plan within
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
