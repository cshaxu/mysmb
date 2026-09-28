# M2 T38: Enemy stream, slots and initialization

## Scope, boundary correction and exact forecast

T37 closed in 4b07a7a at 884 / 1,992. The original plan cut this slice
at line 8500 inside InitFlyingCheepCheep. Keep its three remaining labels
D2XPos1, D2XPos2 and FinCCSt with that initializer through line 8528;
the next slice begins at InitBowser, line 8529. This preserves source order
and removes a split function; those three labels are not credited twice.

The contiguous slice has 88 labels. S1 also receives the already identified
AreaDataOfsLoopback consumer dependency (original transfer-113), plus
KillAllEnemies/KillLoop, required by ExecGameLoopback's immediate caller.
The later Bowser slice retains their dependency and maintenance evidence,
without counting them as new completions. Total scope is 91 unique labels,
all currently open with M2 T19 S5. Expected new 91, maximum 975 / 1,992.
Only S1 receives implementation custody now; future rows retain T19 S5
until admission. Historical T19 work remains evidence, not this active plan.

## Source-ordered chain plan

Each S below performs original node mapping, shared-C migration, ROM semantic
comparison, native verification and one three-target delivery. Nodes within
a row share their caller branch family; small internal tables/labels are not
separate delivery units. S3 proves the complete initializer vector, including
its many child boundaries, rather than just three textual labels.

| S | Chain | Shared owner | Expected / scoped | Exact nodes |
| --- | --- | --- | ---: | --- |
| S1 | Enemy flags, castle loops and frenzy handoff | enemy/core.c and enemy/loop.c | 19 / 19 | `EnemiesAndLoopsCore`, `ChkAreaTsk`, `ChkBowserF`, `ExitELCore`, `LoopCmdWorldNumber`, `LoopCmdPageNumber`, `LoopCmdYPosition`, `ExecGameLoopback`, `ProcLoopCommand`, `FindLoop`, `IncMLoop`, `WrongChk`, `DoLpBack`, `InitMLp`, `InitLCmd`, `ChkEnemyFrenzy`, `AreaDataOfsLoopback`, `KillAllEnemies`, `KillLoop` |
| S2 | Enemy records, page controls and parser continuation | enemy/stream.c | 19 / 19 | `ProcessEnemyData`, `CheckEndofBuffer`, `CheckRightBounds`, `CheckPageCtrlRow`, `PositionEnemyObj`, `CheckRightExtBounds`, `CheckForEnemyGroup`, `BuzzyBeetleMutate`, `StrID`, `CheckFrenzyBuffer`, `StrFre`, `InitEnemyObject`, `ExEPar`, `DoGroup`, `ParseRow0e`, `NotUse`, `CheckThreeBytes`, `Inc3B`, `Inc2B` |
| S3 | Initializer checkpoint and vector | enemy/init.c | 3 / 3 | `CheckpointEnemyID`, `InitEnemyRoutines`, `NoInitCode` |
| S4 | Common enemy initializers and shared reset entries | enemy/init_targets.c | 23 / 23 | `InitGoomba`, `InitPodoboo`, `InitRetainerObj`, `NormalXSpdData`, `InitNormalEnemy`, `GetESpd`, `SetESpd`, `InitRedKoopa`, `HBroWalkingTimerData`, `InitHammerBro`, `InitHorizFlySwimEnemy`, `InitBloober`, `SmallBBox`, `InitRedPTroopa`, `GetCent`, `TallBBox`, `SetBBox`, `InitVStf`, `InitBulletBill`, `InitCheepCheep`, `InitLakitu`, `SetupLakitu`, `KillLakitu` |
| S5 | Lakitu/Spiny allocation and movement setup | enemy/frenzy.c | 13 / 13 | `PRDiffAdjustData`, `LakituAndSpinyHandler`, `ChkLak`, `ChkNoEn`, `CreateL`, `RetEOfs`, `ExLSHand`, `CreateSpiny`, `DifLoop`, `UsePosv`, `SetSpSpd`, `SpinyRte`, `ChpChpEx` |
| S6 | Firebar initializer data and entries | enemy/init_targets.c | 4 / 4 | `FirebarSpinSpdData`, `FirebarSpinDirData`, `InitLongFirebar`, `InitShortFirebar` |
| S7 | Flying Cheep-Cheep complete initializer | enemy/frenzy.c | 10 / 10 | `FlyCCXPositionData`, `FlyCCXSpeedData`, `FlyCCTimerData`, `InitFlyingCheepCheep`, `MaxCC`, `GSeed`, `RSeed`, `D2XPos1`, `D2XPos2`, `FinCCSt` |

## Implementation and verification contracts

- S1 restores the missing high-bit duplicate-slot branch in EnemiesAndLoopsCore
  and the missing ProcLoopCommand path before stream parsing. Loopback changes
  only the original page/cursor fields; world-seven multipart counters and all
  eleven table entries are compared individually. KillAllEnemies must invoke
  the existing EraseEnemyObject owner for slots four down to zero and clear
  frenzy at the original point. Frenzy activation calls the original initializer
  handoff; record advancement remains with the stream owner.
- S2 compares six-slot eligibility, terminators, page-select state, two/three-byte
  records, position-before-bounds, extended bounds, world filter, hard-mode
  ID mutation, group/frenzy handoffs and exactly ordered cursor advancement.
  Group and initializer children keep their own semantic obligations.
- S3 binds every initializer vector entry, ID-below-$15 Y adjustment with the
  original carry, masked-offscreen state, exact return/continuation and NoInitCode.
  It proves call selection, never credits unverified initializer children.
- S4 translates the complete common initializer family through KillLakitu,
  including shared speed/reset/box tails and data tables. Original selected-ID
  stream routes exercise each entry and shared tail. No runtime replacement
  by visually similar actor behavior is allowed.
- S5 keeps PRDiffAdjustData with the complete Lakitu/Spiny allocation chain:
  timers, slots, random differences, carry/sign selection, speed and spawn state.
  Existing collision/movement successors are separate dependencies.
- S6 keeps both firebar data tables with short/long initialization: original
  ID arithmetic, duplicate allocation handoff, fractional state and spin setup.
- S7 owns the whole flying-fish initializer, including its formerly split tail:
  timer/hard-mode gates, PRNG selection, speed/direction, player-relative
  position carry and final activation. No partial-function completion.

Each row uses ordinary NMI controlled source-RAM routes at its caller roots,
read-only original entry/return recording, node-level branch/write/data review
and separate native tests. Original PC/stack/ROM/output are never patched.
Caller substitution, when needed for incomplete children, is identified as
caller-only proof; actual-child differences remain independently recorded.
Each P includes strict C90 x86/x64, DOS16 link, platform-purity review,
bounded hidden Windows probes and three owner-authorized EXEs. DOS remains
link-only. T closure adds a cross-chain matrix and final integrated delivery.

## S1 admission: complete enemy flag and loop-command chain

After T37 closure, coordinator accepts transfer-165 from T19 S5 for the
nineteen exact S1 labels above. Incoming 884 / 1,992; expected nineteen,
maximum 903. All nineteen are open, no retained-match double counting.
The first four labels stay in enemy/core.c; loop.c owns loop tables, rewind,
loop-command/frenzy dispatch and the kill-all child. Stream.c retains parser
record logic and init.c retains initializer logic. Existing core currently
routes all nonzero flags to actors and skips the entire loop path for free
slots: both conflict with the original source. No host/platform repair is
part of this chain.

ROM evidence covers zero/nonzero/high-bit flags, referenced duplicate flags,
parser-task mask, all loop-table matches and no-match, player position/state,
world-seven counters, page underflow, erase-call order and frenzy versus
stream handoff. Compare original RAM and child inputs/returns; native tests
independently exercise gates and complete write footprint. Report every
scoped label and every unverified child; do not use screenshots as proof.

Existing owner-local ROM and admitted disassembly are local research/build
inputs; no third-party implementation import or redistribution is introduced.
Temporary files stay beneath ignored build/m2-t38-s1; raw trace budget four MB,
recorder timeout twenty seconds, cleanup owner S1. Three artifacts are the
owner-authorized local delivery. Existing full-game and platform limitations
remain. Stop for unadmitted parent repair, altered reference execution,
masked mismatch or game behavior placed in platform code.

### S1 source migration checkpoint, not closure

Admission, ledger and documentation gates pass at 884 / 1,992. The shared
core now distinguishes the high-bit duplicate-slot reference from a live
actor flag, and free-slot parser turns enter the new enemy/loop.c owner.
That owner translates the three loop tables, loopback-offset table, page
rewind, world-seven counters, ordered kill-all dependency and frenzy/stream
handoff. Existing initializer and stream interiors remain separate children.
The source owner is included in both product build lists; core.c and loop.c
compile individually under strict C90 x64. Original-route recording, native
branch/write tests, legacy test seam updates and full three-target delivery
are pending. No node credit or runtime correctness claim is added yet.

### S1 native boundary and table checkpoint

The four loop tables match all forty-four bytes at original ROM addresses
$C06B, $C076, $C081 and $9BF8. The local check reads the owner ROM directly;
its script and neutral result remain beneath build/m2-t38-s1.

The registered enemy-loop test passes 337,920 caller cases on each of x86
and x64 under strict C90. Cases cover all eleven records, all pass-counter
values, correct-counter values zero through three and $FF, correct/wrong Y,
nonzero player state, loop/column/no-match gates, frenzy selection and the
complete caller RAM write footprint. Mock children assert descending erase
order before the frenzy-buffer clear and initialized state at the checkpoint
handoff. These mocks prove the caller contract, not child implementations.

The dispatch test covers every high-bit flag at all six slots with live/dead
references, and all parser-task bytes; both it and the existing cannon-child
test pass on both widths. The cannon mock now names the loop handoff that
core actually calls and still fails on any unexpected call. Platform purity
passes. Original reachable branch/child snapshots, full builds and three-EXE
delivery remain pending. Progress stays 884 / 1,992; no P or S closure yet.

### S1 original loop-route checkpoint

Eighty-eight controlled source-RAM cases enter EnemiesAndLoopsCore at $C047
through ordinary NMI, with slot zero free and the parser-task gate open.
Eleven loop records each exercise correct height, wrong height, nonzero
player state, counter wrap, absent loop command, nonzero column, unmatched
world and queued frenzy. The recorder observes real hardware-stack returns;
it does not redirect the CPU or substitute original child execution.

The loop snapshot checker matches all 88 original cases on each native
width. It executes production loop.c and lifecycle.c, compares all portable
RAM at child entry and caller return, and substitutes recorded parser or
initializer returns only after checking their incoming state. This is caller
proof with the real native erase implementation, not parser/initializer
equivalence. CPU stack bytes are excluded except persistent score bytes
$0133-$0139. The zero-state InitEnemyObject handoff is checked at its original
entry; its following duplicate zero write does not change the compared state.

Seven representative runs without observers produce byte-identical frame
records to their observed counterparts. Raw data and reproducible runners
remain bounded under build/m2-t38-s1. Duplicate/live-slot and closed-parser
ROM routes, exact branch coverage, actual successor differences and final
three-platform delivery remain pending; no node credit is claimed yet.

### S1 coverage correction and integrated build checkpoint

Branch auditing exposed that the first fixture's ordinary player-control
phase changed unsupported standing state to falling before the loop entry.
Those earlier 88 matches did not prove the correct-ground branch. The fixture
now uses the original palette-transition state to preserve player state;
all 88 snapshots were regenerated and still match on both widths. No CPU,
stack, ROM or recorded output is patched. Forty independent coverage runs
are byte-identical to their observed frame records and hit both outcomes of
all seventeen genuine conditional branches in the admitted code ranges.
The eighteenth branch, BNE at $C113, is the original unconditional path
following the failed BEQ at $C111; only its taken outcome is feasible.

Eight additional roots cover duplicate-slot flags, self-reference, offsets
beyond the six actor slots, live actors and the closed parser-task gate.
The expanded comparison yields 188/192 matches across both widths. Four
failures are the two live-actor cases at each width: existing
RunEnemyObjectsCore/JumpEngine omits the original $04-$07 scratch writes.
The checker preserves these failures and does not replace this child's
result. Actor-dispatch interiors remain outside S1; exact future disposition
and the caller-boundary review are still required before closure.

All 83 shared units compile under strict C90 for both Windows widths; input
self-tests and bounded hidden-window responsiveness probes pass. DOS16
links with the existing OLDNAMES warning, without a runtime claim. The
twenty related regression runs retain only the two prior Bowser exit-four
failures. Candidate builds remain under build/m2-t38-s1/release-local;
assets are not yet replaced and no implementation P is committed.

## S1 original loop and slot proof

S1 closes nineteen received labels, all nineteen expected and all newly
proven, with no unfinished scoped transfer. Progress 884 -> 903 / 1,992.
This is node/caller conformance, not whole-game equality. Source order and
successor interiors retain the boundaries declared at admission.

| Node | Original address | Individual obligation and evidence |
| --- | --- | --- |
| EnemiesAndLoopsCore | $C047 | High-bit reference versus live actor versus free-slot selection; native exhaustive flags and original roots; match |
| ChkAreaTsk | $C053 | Parser-task low-three-bit comparison; no stream work on task seven; match |
| ChkBowserF | $C05F | All sixteen peer offsets, dead/live/self reference; only dead peer clears current flag; match |
| ExitELCore | $C06A | Original no-write return after closed gate or duplicate handling; match |
| LoopCmdWorldNumber | $C06B | Eleven world bytes at $C06B and reverse lookup; match |
| LoopCmdPageNumber | $C076 | Eleven page bytes at $C076 paired with world entries; match |
| LoopCmdYPosition | $C081 | Eleven Y bytes at $C081 and player-state gate; match |
| ExecGameLoopback | $C08C | Five modulo-byte page rewinds, four cursor/page clears, selected area offset; match |
| ProcLoopCommand | $C0CC | Loop/column gates, reverse search, ground test, multi-loop state, original successors; match |
| FindLoop | $C0D8 | DEY/BMI termination and world/page mismatch branches; match |
| IncMLoop | $C102 | Byte-wrap pass increment and third-pass/correct-count split; match |
| WrongChk | $C115 | Wrong height/state world-seven path versus immediate rewind; match |
| DoLpBack | $C11C | Loopback before descending kill-all, original ObjectOffset reload before successor; match |
| InitMLp | $C122 | Pass counter cleared before correct counter; match |
| InitLCmd | $C12A | Loop command cleared only on a matched record path; match |
| ChkEnemyFrenzy | $C12F | Queued ID, flag, state, queue-clear and initializer handoff; otherwise parser; match |
| AreaDataOfsLoopback | $9BF8 | Eleven offset bytes at $9BF8 consumed by the selected loop row; match |
| KillAllEnemies | $D071 | Slots four through zero erased before frenzy buffer clear; shared erase owner; match |
| KillLoop | $D073 | Descending erase loop and signed termination, source call-order audit and native assertions; match |

The final corrected fixtures and branch audit prove all seventeen true
conditional branches in both directions; BNE $C113 is necessarily taken.
The four tables match 44 original bytes. Independent native loop tests run
337,920 cases per width, including full write footprints and erase order.
The original recording uses source RAM only at NMI and real call/return
stack observation. Forty observer-free coverage routes produce identical
frames. The fixture correction above remains part of the evidence history.

The two tracks remain distinct. The caller checker has 188/192 exact matches;
its four failures are two live-dispatch cases at each width. Their child
entry is exact and the reviewed core has no post-child write. Independent
RunEnemyObjectsCore execution reproduces every differing byte at return.
Thus the source call selection and return edge are proven, but its child
interior remains unmatched. Parser/initializer substitution in the other
caller cases is explicit and earns no child credit.

The fully integrated diagnostic has only 12/192 matches, with 180 failures
at $04-$07. All 180 independently replayed child entries reproduce the
identical whole-root difference, with no scratch masking. ProcessEnemyData,
CheckpointEnemyID/InitEnemyRoutines and RunEnemyObjectsCore/JmpEO retain
these defects under their existing T19 S5 custody, for planned source-order
admission (parser S2, vector S3, later actor dispatch). No failure is waived
and no child completion is claimed.

Similar-issue sweep: core.c is the current-slot gate used by engine and
victory paths. loop.c is the sole new castle-loop/page-rewind owner;
stream.c retains cursor/page parsing and legacy queue handling, and init.c
retains initializer pages and IDs. Area parsing produces the loop/frenzy
commands. lifecycle.c owns the eight erase writes and is reused unchanged.
The old bridge.c five-flag clear is a separate incomplete bridge caller;
its replacement by the exact kill-all handoff stays with the later bridge
slice, not an unreviewed S1 change. Native platforms contain no added game
logic. Build lists include the new shared owner for all targets.

All 83 shared units compile as strict C90 for x86/x64; self-tests and bounded
hidden-window responsiveness checks pass. DOS16 links, with the existing
OLDNAMES warning; resource binding/playability/486 performance remain unproven.
Of forty selected regressions, thirty-eight pass and the two existing Bowser
exit-four failures persist. Platform purity and diff checks pass.
Recheck the original/native evidence and delivered hashes with
`python -X utf8 -B test/verify_enemy_loop_snapshots.py build/m2-t38-s1 <owner-rom>`.
Raw traces stay beneath the admitted ignored build directory within its
four-MB budget. The three owner-authorized local artifacts are refreshed;
these are test deliveries, not certification of full game fidelity.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 253619 | 6048063830bed98bdbda0fa8a2e81dbf16f91ae09f3f85071f2be40fba02a8da |
| mysmb32.exe | 331681 | fc2402082e3e1e7e33c7e134e4a09d6e2e293f5ccfde7f8e2c05b53812b07955 |
| mysmb64.exe | 339245 | f04faf2de1b4418daef4e57c4ec2271bd4de01083eeca3a6f26d3a771ee79978 |

## S2 admission: enemy records and parser continuation

After S1 commit 3c322d5, coordinator accepts transfer-166 from T19 S5 for
all nineteen S2 labels in the source-ordered chain table. Incoming 903/1,992;
all nineteen are open and expected, maximum 922. S1 remains closed and no
other S is active. Shared enemy/stream.c owns the parser; predecessor loop.c
and initializer/group successors retain their separate node obligations.

Source $C144 through Inc2B preserves slot-five eligibility, scratch $06/$07
extended bounds and page carry, second-byte page increment before row-$0F
control, page-control return to ProcLoopCommand, position-before-bounds,
row-$0E third-byte selection, hard-mode skip/mutation, group tail handoff,
frenzy/vine fallback, state-zero initialization and post-initializer flag
check before cursor advancement. All byte cursors wrap as original Y/RAM
bytes; host arithmetic must not replace these semantics.

Initial audit finds the current implementation omits scratch $06/$07,
processes row-$0F before the second-byte page increment, continues locally
instead of returning through ProcLoopCommand, conflates ChkEnemyFrenzy with
ProcessEnemyData and advances the cursor even if initialization clears the
flag. These are hypotheses grounded in the source comparison; each repaired
branch must receive original-ROM proof. Group/initializer internals and
RunEnemyObjectsCore scratch debt are outside S2. Existing child bodies may
be exposed as explicit handoffs without granting them credit.

Two verification tracks: source byte/branch/write/call audit and controlled
original NMI routes with read-only entry/return capture; separately strict
C90 native boundary tests, affected regressions, x86/x64 builds and hidden
probes, DOS16 link, platform purity and three local EXEs per P. Reuse S1's
88 loop snapshots to detect continuation regressions and independently
attribute remaining child failures. No forced PC/stack/ROM/output edits.
Owner-local ROM/listing are the existing research/build inputs; no third-party
implementation is imported. Temporary outputs remain under ignored
build/m2-t38-s2, raw budget four MB and recorder timeout twenty seconds;
cleanup owner S2. No node credit until both tracks and ledger agree.

### S2 parser migration checkpoint

Admission and documentation gates pass. The parser now writes original
extended-boundary scratch bytes with byte/page carry and low-nibble masking;
processes the second-byte page increment before row-$0F; returns through
ProcLoopCommand after page-control records; wraps Y record offsets; keeps
position writes before bounds; and consumes a normal record only if its
initializer returns with the enemy flag still set. Queued frenzy is no
longer duplicated inside ProcessEnemyData. Group and initializer interiors
remain unchanged and uncredited. The loop/parser continuation is an explicit
source tail edge, not a platform path.

Reusing all 96 original S1 snapshots without child substitution, both widths
improve from 6/96 to 83/96 full portable-RAM matches. The thirteen remaining
failures have identical x86/x64 outputs and retain only $04-$07 differences
in initializer/actor-dispatch successors. This is predecessor regression
evidence, not coverage of every new S2 parser branch.

The existing enemy-stream smoke initially stopped at exit five: its queued
frenzy case incorrectly called ProcessEnemyData directly despite naming
ChkEnemyFrenzy. The case now enters the actual loop-command predecessor and
keeps all expected queue/ID/flag writes; both widths pass the whole smoke.
The parser compiles under strict C90 on both widths. S2 original record/page
boundary fixtures, branch coverage, full builds and delivery remain pending;
no new node credit, P commit or replacement of S1 artifacts yet.

### S2 native boundaries and first record-route evidence

The registered enemy-stream boundary test passes 66,560 cases per width:
all 65,536 right-page/right-X pairs and 1,024 cursor/order/initializer-return
cases. It checks full portable RAM, eight-bit INY/cursor wrap, rejected
initializers preserving records, and page-bit-before-row-$0F behavior.
The initializer and loop continuation are explicit native test substitutes;
this test grants no original-ROM child credit.

The reference recorder now observes ProcessEnemyData at $C144 and its
CheckpointEnemyID, ProcLoopCommand and HandleGroupEnemies boundaries.
Sixty-four controlled NMI cases use eight original enemy-record addresses
covering Goomba, hard-mode, both page-control forms, area-entry rows, groups,
terminator and ordinary records. Variants include near/behind/far bounds,
hard flags, slot five, wrapped source Y and vine fallback. Record bytes,
CPU entry and stack are never patched. All 64 record successfully; the
initial x64 integrated comparison matches 44/64. Twenty differences remain
unresolved pending individual child-entry/return attribution; no parser
completion claim follows from these results. Eight representative families
produce identical frame bytes with and without the observers. Raw outputs
remain below the admitted four-MB budget in build/m2-t38-s2.

### S2 successor attribution and coverage checkpoint

The existing group body is moved unchanged into enemy/group.c, with an
explicit header; its old caller-side cursor increment now uses the shared
Inc2B tail at the group's original exit. This exposes the original DoGroup
boundary without claiming group-body fidelity. Both product source lists
include it, while the isolated boundary test rejects unexpected group calls.
The original group child argument is recorded from A; other child arguments
are recorded from X. Native pre-call RAM and each argument are checked before
any recorded successor state is substituted.

All 128 parser caller comparisons match across x86/x64. Fully integrated
execution remains 88/128, and every x64 output is byte-identical to its
pre-extraction result. Fifty-two independent actual child checks reproduce
their enclosing parser result exactly, including all forty failures. Those
failures belong to checkpoint/initializer, group and loop-to-initializer
successors; their scratch, vine and actor-state differences remain failures.
The two native boundary suites still pass all 66,560 cases per width.

The first complete 64-route observer-free coverage sweep preserves all frame
bytes and identifies 23 conditional branches. Six lack one outcome:
$C161 slot-five power-up eligibility, $C1EF secondary-hard acceptance,
$C1FB ID-at-least-$3F, $C213 initializer-cleared flag, $C219 nonzero frenzy
buffer and $C259 row-$0E at CheckThreeBytes. More original fixtures or an
explicit source-reachability proof are required for these paths before S2
closure. In particular CheckThreeBytes is entered only after its caller has
excluded row-$0E; no fabricated reference PC/stack will create that edge.

## S2 original enemy parser proof

S2 closes all nineteen received and expected labels, no scoped transfer;
903 -> 922 / 1,992. Each match is the node/caller obligation below, not a
claim that initializer/group/actor descendants or the full game match.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| ProcessEnemyData | $C144 | Eight-bit record offset, original data pointer and terminator fallback; match |
| CheckEndofBuffer | $C150 | Row-$0E exception and slot-five $2E gate; residual gate has explicit native/static proof; match |
| CheckRightBounds | $C164 | Right-X plus $30, masked low nibble, carried page in scratch $06/$07; match |
| CheckPageCtrlRow | $C189 | Second-byte page increment precedes row-$0F and ProcLoopCommand continuation; match |
| PositionEnemyObj | $C1AB | Page/X writes before ordinary right-boundary comparison; match |
| CheckRightExtBounds | $C1CB | Extended-boundary borrow semantics then high-Y/Y positioning; match |
| CheckForEnemyGroup | $C1F1 | Hard-mode and group-ID selection; ID $3F arm has native/static proof; match |
| BuzzyBeetleMutate | $C1FD | Goomba changes to Buzzy only with PrimaryHardMode; match |
| StrID | $C208 | ID/flag installation, state-zero initialization and flag-dependent record consumption; match |
| CheckFrenzyBuffer | $C216 | Frenzy-buffer priority then exact vine-offset equality gate; match |
| StrFre | $C224 | Fallback ID write without inventing an activation flag; match |
| InitEnemyObject | $C226 | Zero state then CheckpointEnemyID, independent of record consumption; match |
| ExEPar | $C22D | Original return with no extra cursor write; match |
| DoGroup | $C22E | Exact group argument and tail handoff through shared Inc2B; no group-body credit; match |
| ParseRow0e | $C231 | Wrapped third-byte access, world filter and area/entrance writes; match |
| NotUse | $C24D | Unmatched world still consumes exactly three bytes; match |
| CheckThreeBytes | $C250 | Only incoming source edge excludes row-$0E; redundant reread/branch audited; match |
| Inc3B | $C25B | One extra cursor increment before the common two-byte tail; match |
| Inc2B | $C25E | Two byte-wrapped increments then page-select clear, including group tail; match |

The final eighty original NMI fixtures give 160/160 caller matches at both
widths. Every child argument and portable RAM entry is checked before its
recorded return is substituted. Actual execution, without substitution or
scratch masking, gives 88/160 matches and 72 retained failures. Of 84
independent child checks, 74 reproduce the exact root output. Ten additional
root differences are the proven continuation of InitLakitu failing to clear
the flag: the native parser consequently advances $0739 by two and clears
$073B, while the original retains both. The independent diagnostic confirms
all other differences match the child output. No parser fix suppresses this
failed child contract. InitLakitu/KillLakitu remain for S4; checkpoint/vector
scratch for S3; group and remaining initializer interiors keep their existing
T19 S5 custody and planned source slices. No descendant earns credit here.

Twenty of 23 original conditional branches execute both outcomes. The three
exceptions are explicit static/native proof, not fabricated execution:
all 34 original symbol-named enemy streams (502 records) contain no ordinary
ID $2E or $3F record; focused native cases prove slot-five power-up and
non-group $3F handoffs with child substitutes. This does not certify behavior
for arbitrary corrupt pointers or the $3F initializer itself. CheckThreeBytes
has one symbolic incoming jump, immediately after its caller excludes row
$0E; its other outcome cannot occur on that original edge. The row-$0E
ParseRow0e/Inc3B route is independently executed. Source tables, control
conditions and immutable PRG reads justify these exact exceptions.

All eighty observer-free coverage runs produce identical frame records.
The predecessor S1 matrix improves from 12/192 to 166/192 actual matches;
remaining successor failures remain explicit. Native boundary tests pass
66,562 cases per width, plus the complete existing stream smoke. All 84
shared units compile as strict C90 on x86/x64; self-tests and bounded hidden
window probes pass. DOS16 links with the existing OLDNAMES warning, without
runtime/resource/486 qualification. Thirty-eight of forty selected regression
runs pass; the same two Bowser exit-four failures remain. Platform purity
passes; raw trace files remain beneath the admitted four-MB build budget.

Similar-issue sweep covers current/slot/next parser APIs, normal record and
fallback initialization, group tail advancement and loop-page continuation.
Queued frenzy now belongs only to its predecessor, so the legacy smoke's
queued case uses that original entry with its same state assertions. Group
extraction preserves every prior actual result; its implementation is not
silently repaired. Shared Inc2B is used by both ordinary and group exits.
The stream header now records the correct source range. Both build lists
include group.c; platform source contains no gameplay changes.

Reproduce diagnostics from the project-owned enemy_stream_snapshot_check.c,
enemy_loop_actual_check.c and enemy_stream_boundary_smoke.c against the
admitted owner-local snapshots and PRG. Caller and actual modes remain
separate. Local runners/results are under build/m2-t38-s2; no raw trace or
ROM data is committed. The three owner-authorized EXEs below are test
artifacts, not full-game certification.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 253491 | 223fbf7727b720d228237a38cead9b47681e7c3fa4eb4ca0bbcdcd8698d1a45d |
| mysmb32.exe | 332541 | 9917dd3c2d4f321442eab7c62e9afaeae54538275cb852de9a14bef1344a2f37 |
| mysmb64.exe | 340139 | 3664b90010ad299347cb06cfc82d9f290b7452ebb256cd4064c51874bc351a1f |

## S3 admission: checkpoint and full initializer vector

After S2 commit 52ccb53, coordinator accepts transfer-167 from T19 S5 for
CheckpointEnemyID, InitEnemyRoutines and NoInitCode. All three are open;
incoming 922/1,992, expected three, maximum 925. S2 remains closed.
The three labels cover a complete 55-entry vector and 31 distinct targets,
not three isolated leaf changes. Shared enemy/init.c owns the checkpoint
and vector; existing initializer/frenzy/platform/vine/power-up successors
retain their separate responsibilities. Child extraction may expose original
entry contracts but earns no child credit and must preserve existing results.

The original CMP $15 leaves carry clear on the below-$15 arm, so ADC $08
is exactly a byte-wrapped eight-pixel Y addition, followed by the masked
offscreen write. Larger IDs skip both writes. JumpEngine saves $C281 into
$04/$05 and the selected original target into $06/$07, then tail-dispatches.
NoInitCode performs no subsequent game-state mutation. The native port must
select native C entries; it must not execute original instructions at runtime.
Audit the 55 original entries and all aliases, not a visually similar ID
classification or unconditional shared actor setup.

Two tracks: original source/control/data/write/target-entry comparison using
ordinary NMI routes and read-only child snapshots; independent C90 tests of
all valid IDs, Y wrap, all slots and no-init write footprints, x86/x64 builds,
DOS16 link, platform purity and three EXEs. Reuse S2 original child snapshots
to measure actual improvements and preserve unrelated failures. Reference
inputs are the already admitted owner-local ROM/listing; no third-party
implementation import. Temporary data stays under ignored build/m2-t38-s3,
raw budget four MB, twenty-second recorder timeout, cleanup owner S3.
Stop for unadmitted child repair, changed reference PC/stack/ROM/output,
concealed mismatches or platform gameplay. Completion requires exact scoped
node dispositions, both verification tracks, updated tracker/ledger and
three local artifacts; node credit remains zero at admission.

### S3 initial vector audit

All 110 vector bytes at $C282-$C2EF match the 55 source label addresses.
Fourteen IDs select NoInitCode. Current C incorrectly sends these through
ordinary initialization, omits vector scratch writes and bypasses the common
vector path for the power-up entry. The below-$15 Y/masked-bit prefix is
already present and must not be duplicated when child bodies are separated.
The source table below is an entry/alias inventory, not child completion.

The first implementation checkpoint restores vector scratch before every
declared target, places the existing power-up path after this common prefix,
and returns immediately for all fourteen NoInitCode aliases. Both widths
pass 21,504 full-RAM no-init cases (all aliases, slots and Y bytes). Reusing
S2's eighty original roots, actual matches improve from 88/160 to 106/160,
with eighteen new matches and no regression of a previously matching root.
Strict C90 compilation and platform purity pass. The existing large child
initializer body remains uncredited: explicit native target dispatch and
its 31 successor contracts still require completion, followed by original
target-entry proof, final builds and three-EXE delivery. No S3 node credit,
P commit or replacement of the S2 assets is claimed at this checkpoint.

The next structural checkpoint exposes InitEnemyFrenzy as one shared entry
in enemy/frenzy.c. All five initializer-vector aliases now call that entry;
the buffer write and existing nested selection move with it. Its child
bodies and missing nested JumpEngine scratch are unchanged and uncredited.
Before/after extraction checks cover all 55 IDs, six slots and four bounded
state configurations: 1,320 full-RAM results per width are identical. These
are native preservation checks, not original-ROM equivalence evidence.
Recompiled S2 actual comparisons retain 106/160 matches, and the 21,504
NoInit cases per width still pass. Remaining S3 work is the other target
entry boundaries, original target-entry comparisons and final delivery.
The general actor-default block still belongs to unfinished legacy child
implementation; it must not be attributed to CheckpointEnemyID as proven
original behavior. No new node credit or artifact replacement is made.

The residual $2F vector entry now calls the existing Setup_Vine owner with
the original JumpEngine Y output, $60: ASL doubles ID, then two INY
instructions advance to the target high byte. Entry $36 now returns at
EndOfEnemyInitCode instead of
performing general actor initialization. Neither child body is changed.
The focused enemy-init-handoff harness checks nine entries, all six slots
and every Y byte: 13,824 cases per width verify the full child-entry RAM,
callee/slot/Y selection and return continuation with explicit child mocks.
It does not certify those child implementations. Actual S2 ROM roots now
match 110/160, retaining all previous 106 matches; cases 23 and 55 newly
match on both widths. NoInit retains 21,504 passing cases per width.
The full vector still awaits the remaining entry extraction and original
boundary proof; three-artifact delivery and S3 closure remain pending.

### S3 complete native entry separation, pending original boundary proof

The checkpoint now selects explicit native entries for every declared vector
ID. Existing ordinary actor, firebar, platform and Bowser child bodies move
to enemy/init_targets.c, declared in init_targets.h. Both product build lists
include this shared unit. The firebar entry parameter distinguishes $C459
from $C45C without fabricating an empty forwarding function. Direct piranha
callers retain their existing entry; the vector's legacy default writes stay
inside its separate, still-unverified child entry. The retainer entry likewise
retains its old writes until S4, rather than claiming its missing Y write fixed.
Frenzy, power-up and vine keep their existing subsystem owners. No host code
changes, no child-node transfer and no initializer-interior conformance credit.

All 55 IDs, six slots and four bounded native configurations retain identical
complete RAM output across the extraction: 1,320 cases per width. The initial
extraction misplaced the upward-lift body for IDs $26/$2B; this check caught
both before delivery, and their original legacy force/speed writes were
restored. The complete rerun passes. Actual S2 ROM comparisons still match
110/160; the remaining 50 mismatches are retained.

The handoff harness now covers all 55 entries, six slots and 256 Y values:
84,480 cases per width verify full entry RAM, target identity, slot/required
Y arguments, no-init/end returns and child-return propagation. These explicit
child mocks prove native caller boundaries, not child interiors. All prior
NoInit cases also pass. Original read-only target-entry observations, final
cross-target builds, three EXEs and closure remain required; global node
progress stays 922/1,992. Future S4/S6 owner paths above reflect this source
move without changing their node sets or admission order.

| Original target | Address | IDs |
| --- | --- | --- |
| InitNormalEnemy | $C30E | $00, $01, $02 |
| InitRedKoopa | $C31E | $03 |
| NoInitCode | $C2F0 | $04, $09, $13, $19, $1A, $20, $21, $22, $23, $30, $31, $32, $33, $34 |
| InitHammerBro | $C328 | $05 |
| InitGoomba | $C2F1 | $06 |
| InitBloober | $C342 | $07 |
| InitBulletBill | $C36B | $08 |
| InitCheepCheep | $C375 | $0A, $0B |
| InitPodoboo | $C2F7 | $0C |
| InitPiranhaPlant | $C787 | $0D |
| InitJumpGPTroopa | $C7D1 | $0E |
| InitRedPTroopa | $C34A | $0F |
| InitHorizFlySwimEnemy | $C33D | $10 |
| InitLakitu | $C385 | $11 |
| InitEnemyFrenzy | $C7A0 | $12, $14, $15, $16, $17 |
| EndFrenzy | $C7B8 | $18 |
| InitShortFirebar | $C45C | $1B, $1C, $1D, $1E |
| InitLongFirebar | $C459 | $1F |
| InitBalPlatform | $C7DF | $24 |
| InitVertPlatform | $C812 | $25 |
| LargeLiftUp | $C83F | $26 |
| LargeLiftDown | $C845 | $27 |
| InitHoriPlatform | $C80B | $28, $2A |
| InitDropPlatform | $C803 | $29 |
| PlatLiftUp | $C84B | $2B |
| PlatLiftDown | $C857 | $2C |
| InitBowser | $C549 | $2D |
| PwrUpJmp | $BC60 | $2E |
| Setup_Vine | $B91E | $2F |
| InitRetainerObj | $C307 | $35 |
| EndOfEnemyInitCode | $C881 | $36 |

## S3 original initializer vector proof

S3 closes all three received and expected labels, with no scoped transfer:
922 -> 925 / 1,992. This proves checkpoint/vector caller semantics; it does
not certify the initialization children, their internal call graphs or full
playability. S4 remains next, with its original 23-node common initializer set.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| CheckpointEnemyID | $C26C | Below-$15 Y+8 byte wrap and masked-offscreen write; both original branch outcomes and target entry RAM match; match |
| InitEnemyRoutines | $C27F | All 55 entries/31 targets, exact vector scratch and native handoffs including residual vine Y=$60; child interiors excluded; match |
| NoInitCode | $C2F0 | All fourteen aliases return without extra game writes; 28 original observations and exhaustive native preservation cases; match |

One hundred ten controlled original NMI routes cover all 55 IDs and all 31
selected addresses. ID zero uses an unchanged ordinary enemy record; other
IDs use the original queued-frenzy predecessor. Slot-zero and slot-five
entries, hard-mode and wrapped Y configurations are explicit fixture inputs.
Two initial fireworks cases lacked the star-flag partner and timed out; their
source-RAM setup was corrected to satisfy the original scan, with no ROM,
PC, stack or output patch. All 110 then returned normally. Each record checks
the reached target and original Y=(ID*2)+2. All 110 observer-free coverage
runs produce byte-identical frame records. The checkpoint branch executes
44 lower-ID and 68 upper-ID outcomes; NoInitCode executes 28 times. All 110
vector bytes also match the original listing labels and ROM.

The two widths provide 220/220 caller matches: compare entry RAM and native
target/arguments before explicitly substituting the observed child return.
No-init and terminal return entries are compared directly. This comparison
excludes hardware-stack bytes except mapped game RAM $0133-$0139; scratch
$00-$07 is included. It is not a CPU-stack-emulation claim. Actual execution
without child substitution matches 128/220 and retains 92 child failures.
Those failures affect IDs $0C, $0D, $12, $14-$17, $1B-$1F, $24-$2D and $35;
their existing T19 S5 custody and scheduled source slices remain responsible.
S4 handles common initializer semantics, S5/S7 their admitted frenzy bodies,
S6 firebar initialization; later source slices handle the other initializers.
No child node receives completion credit from this S.

Native vector tests cover 84,480 cases per width, NoInit tests 21,504, and
pre/post extraction preservation 1,320. The preservation check caught and
corrected a transient upward-lift extraction error before delivery. The
power-up dispatch regression previously omitted source vector scratch;
its expected $04-$07 writes now match the original entry, while its existing
72 child-write cases per width remain intact. Final focused stream tests pass.
Thirty-eight of forty related regressions pass; the two existing Bowser
exit-four failures remain. Earlier actual matrices retain 166/192 loop
matches and improve parser matches from 88/160 at S2 closure to 110/160.
None of the previously matching loop or parser roots is lost.

All 85 shared units compile as strict C90 on x86/x64; self-tests and bounded
hidden-window responsiveness probes pass. DOS16 links with the existing
OLDNAMES warning, without DOS runtime/resource/physical-486 qualification.
Platform purity passes; no platform source changes. Original raw records
are contained under build/m2-t38-s3 (1,402,307 bytes, below the four-MB budget,
with twenty-second process timeouts). Reproduce with enemy_init_fixture.h,
reference_frame_recorder, enemy_init_snapshot_check and the integrated
enemy_loop_actual_check; child substitution and actual modes are separate.

The similar-issue sweep covers all 55 table aliases, every checkpoint caller,
ordinary/frenzy/power-up/vine/terminal paths and both build source lists.
The dispatcher now owns only original checkpoint/dispatch work. Existing
child bodies have explicit shared entries in enemy/init_targets.c and their
existing subsystem owners; this move preserves child behavior and does not
endorse their legacy defaults or missing internal calls. Future S4/S6 owner
paths are updated without changing scope or order. Three owner-authorized
EXEs below are test deliveries, not a claim that the game is ROM-complete.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 254897 | 10d2c9dcdcf92beb87cf3586d93cc6d9a3455c0e2f0aa92a49e9d702fd5e1e18 |
| mysmb32.exe | 336622 | 7fb00dc1a4e9f9e2e1fb45e38eb57bcb183ba33e9eb4de3cde39c5a7bd5af821 |
| mysmb64.exe | 344229 | d8e379d7ca8e1b8182d8f75d81e6b610ff275895a5646173765506582cd94651 |
