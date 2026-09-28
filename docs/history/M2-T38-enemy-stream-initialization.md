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
without counting them as new completions. Initial scope was 91 unique labels,
then open with M2 T19 S5, maximum 975 / 1,992. S6 subsequently receives
three mandatory duplicate-child nodes: updated scope 94, maximum 978 / 1,992.
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
| S6 | Firebar initializers and mandatory duplicate child | enemy/init_targets.c | 7 / 7 | `FirebarSpinSpdData`, `FirebarSpinDirData`, `InitLongFirebar`, `InitShortFirebar`, `DuplicateEnemyObj`, `FSLoop`, `FlmEx` |
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

## S4 admission: common initializers and shared tails

After S3 commit 2294663, coordinator accepts transfer-168 from T19 S5 for
all 23 source-ordered labels in the S4 plan row. All are open: incoming
925/1,992, expected 23, maximum 948. S3 remains closed. Entry is the admitted
initializer vector; exits are source returns or the existing EraseEnemyObject
and TallBBox2 handoffs. Shared enemy/init_targets.c owns this implementation.
S4 restores the original $C2F1-$C397 common family, including both data tables,
exact write footprints, shared speed/box/vertical tails, signed-Y center
selection and frenzy-dependent Lakitu rejection. Branches and byte carry
are read from the admitted local ROM/listing before implementing C.

Non-goals: no frenzy-generator, firebar, platform, Bowser, piranha or green
Paratroopa body repair; no platform gameplay. These pending child bodies
currently call the old common default block; isolate that legacy block so
correcting InitNormalEnemy does not silently migrate unrelated nodes.
Existing EraseEnemyObject is a child dependency, not new completion credit.
TallBBox2 is a one-write successor outside this receipt; expose its exact
handoff without crediting its deferred label. All required calls and aliases
are swept, not only current visible enemy types.

ROM-logic evidence reuses S3's recorded initializer routes and S2's occupied
frenzy cases, adding bounded source-RAM branch cases where needed. Compare
actual full portable RAM without child substitution for internal shared
tails; keep any external-child comparison explicit. Native tests separately
exercise sentinel write footprints, all six slots, mode/PRNG bits, Y sign
and wrap boundaries, plus cross-width builds, DOS16 link and platform purity.
Three owner-authorized EXEs accompany every P; DOS remains link-only.
Reference provenance remains the owner-local SMB1 ROM and reviewed listing;
no third-party implementation import. Existing S2/S3 snapshots are retained
as S4 dependencies. New raw evidence stays beneath build/m2-t38-s4, four-MB
budget, twenty-second per-run timeout, cleanup owner S4. Stop on unadmitted
repair, altered reference execution or concealed mismatches. Closure requires
individual dispositions, both proof tracks, tracker/ledger agreement and
three artifacts. No S4 node is credited on admission.

### S4 implementation checkpoint

The common family now uses the original shared SetESpd/TallBBox/SetBBox/
InitVStf and SmallBBox tails. Normal initialization no longer invents flag
or state writes. Podoboo preserves unrelated horizontal state, retainer only
sets Y, Bullet Bill only sets direction/box, and Cheep-Cheep binds the original
PRNG movement bit without clearing unrelated force/dummy fields. Lakitu
rejects occupied frenzy via the existing EraseEnemyObject; its successful
branch resets reappearance and follows the horizontal/TallBBox2 calls.
Unadmitted piranha, green Paratroopa, firebar, platform and Bowser bodies retain
the isolated legacy defaults; they are not silently changed by this repair.

Reused S3 original records match all 60 scoped entry comparisons across both
widths. The complete initializer matrix improves 128/220 -> 136/220, and the
S2 parser matrix improves 110/160 -> 138/160. The integrated checker now also
retains original game RAM $0109-$0139, including the floatey-number and shell
chain fields cleared by EraseEnemyObject, instead of checking only digit
modifier RAM in that region. A separate sentinel test passes 23,040 full-RAM
write-footprint cases per width, covering all slots and Y bytes, both hard
mode selectors, PRNG bit selection and Lakitu rejection. Strict C90 passes.

This is not closure: the inherited original fixtures wrap the red Paratroopa
Y into the lower half, so its other sign branch needs an additional original
RAM-only route. The source data-table binding and complete branch/call audit,
remaining focused regressions, three-target delivery and node updates also
remain required. All 23 nodes remain uncredited at this checkpoint.

## S4 original common initializer proof

S4 closes all 23 received and expected labels, with no scoped transfer:
925 -> 948 / 1,992. This is actual common-initializer proof, without child
return substitution. Other initializer and actor bodies remain incomplete;
S5 Lakitu/Spiny allocation is next in the original sequence.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| InitGoomba | $C2F1 | Call normal speed initialization then SmallBBox, preserving unrelated state; match |
| InitPodoboo | $C2F7 | Set high-Y/Y to two, interval timer to one, state zero, then SmallBBox; match |
| InitRetainerObj | $C307 | Write only the fixed Y coordinate $B8; match |
| NormalXSpdData | $C30C | Both original speed bytes bound to their consuming primary-mode paths; match |
| InitNormalEnemy | $C30E | Select primary-mode index, read speed and enter shared speed/box tails without flag/state writes; match |
| GetESpd | $C316 | Read the selected original normal-speed byte; match |
| SetESpd | $C319 | Write horizontal speed then enter TallBBox; match |
| InitRedKoopa | $C31E | Call normal initializer before setting state one; match |
| HBroWalkingTimerData | $C326 | Both original walking-delay bytes and legal secondary-mode indexes verified; match |
| InitHammerBro | $C328 | Zero throw timer/speed, read walking delay and enter SetBBox with $0B; match |
| InitHorizFlySwimEnemy | $C33D | Supply zero speed to shared SetESpd; match |
| InitBloober | $C342 | Zero BlooperMoveSpeed then fall through SmallBBox; match |
| SmallBBox | $C346 | Select box nine; fixed nonzero load makes its BNE unconditional; match |
| InitRedPTroopa | $C34A | Save original Y, select signed-Y center adjustment, add with vector-proven clear carry, then TallBBox; match |
| GetCent | $C355 | Preserve wrapped ADC result in center Y with both sign branches executed; match |
| TallBBox | $C35A | Select box three for SetBBox; match |
| SetBBox | $C35C | Write box and direction two, then InitVStf; match |
| InitVStf | $C363 | Clear only vertical speed and movement force; match |
| InitBulletBill | $C36B | Write only direction two and box nine; match |
| InitCheepCheep | $C375 | Call SmallBBox then preserve PRNG bit four and original Y at their source aliases; match |
| InitLakitu | $C385 | Read frenzy buffer and select setup versus erase; match |
| SetupLakitu | $C38A | Clear reappearance timer, call horizontal initializer then the existing TallBBox2 tail; match |
| KillLakitu | $C395 | Tail-call existing EraseEnemyObject; all eight source fields, including mapped stack-page game data, checked; match |

Thirty retained S3 entry scenarios plus 52 added RAM-only NMI scenarios give
164/164 actual portable-RAM matches across x86/x64. The added cases exercise
both red-Paratroopa Y signs, both Cheep-Cheep PRNG bit values and free/occupied
Lakitu frenzy. Each of the 21 code labels is observed in original execution;
both data tables match original ROM bytes and their consuming routes. All
three conditional branches execute both outcomes. SmallBBox's fourth branch
is source-unconditional: LDA #$09 makes BNE taken, so an untaken observation
would require altered source semantics. All eleven original call/tail edges
are mapped to shared native entries/tails. Fifty-two observer-free coverage
runs produce byte-identical original frame records.

The native sentinel test checks 23,046 complete-RAM cases per width, including
the separate SetupLakitu entry with occupied frenzy; that direct entry must
bypass InitLakitu's rejection. Original InitializeArea clears SecondaryHardMode
through InitializeMemory and the sole named SetSecHard producer increments
it once, bounding the walking-timer selector to zero/one. InitRedPTroopa has
only the initializer-vector incoming reference; JumpEngine ASL of $0F clears
carry before its center-position ADC. These source invariants are explicit,
not synthesized clamps. Hardware stack remains outside the native RAM proof,
but its game-variable region $0109-$0139 is now retained, including floatey
numbers and shell-chain state cleared by EraseEnemyObject.

Final actual matrices are 166/192 loop, 138/160 parser, 136/220 complete
initializer and 104/104 added common-family comparisons. All 404 previously
matching roots remain matched. Remaining failures belong to pending children;
no scratch bytes or failed comparisons are hidden. Thirty-eight of forty
related native regressions pass; both existing Bowser exit-four failures
remain. Common, NoInit and stream focused tests pass against final objects.
All 85 shared units compile as strict C90 on both Windows widths; self-tests
and bounded hidden-window response probes pass. DOS16 links with the existing
OLDNAMES warning, without runtime/resource/physical-486 qualification.
Platform purity passes and no platform source changes.

The similar-issue sweep covers every admitted initializer, source aliases,
data producer and incoming call. Pending frenzy/platform/Bowser/MovePodoboo
and movement/collision callers still own their incoming-edge migration;
public SetupLakitu, SmallBBox and InitVStf entries are available to them.
Those later caller nodes are not credited by this S. Unadmitted initializer
bodies keep isolated legacy defaults, so fixing InitNormalEnemy does not
silently repair their behavior. TallBBox2 and EraseEnemyObject dependencies
receive no new node credit. Source order and later node custody are preserved.

Reproduce with enemy_init_fixture cases 110-161, reference_frame_recorder,
enemy_loop_actual_check and enemy_common_init_smoke, plus retained S3 scoped
records. Owner-local raw evidence remains below build/m2-t38-s4 (669,829 bytes,
four-MB budget and twenty-second process timeouts); retained S2/S3 dependencies
stay in their own ignored directories. No new source/ROM import is introduced.
Three owner-authorized test EXEs follow; this is not full-game certification.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 254757 | 41eab99a186ef0e194bbd65732b759d79d5c7e748256dc1ab78d3effab2aca24 |
| mysmb32.exe | 337722 | ce559a214fdfcec696c19dba3ffcb50b90182ac8399513e378c2417b1223c88b |
| mysmb64.exe | 344807 | 46472e77ca6e92ec0196f3770502c7e07160b39b3ea8769660d8e1b6274a548e |

## S5 admission: Lakitu and Spiny allocation chain

After S4 commit 608e036, coordinator accepts transfer-169 from T19 S5 for
all thirteen exact labels in the S5 plan row. All are open: incoming 948/1,992,
expected thirteen, maximum 961. Shared enemy/frenzy.c owns the $C398-$C44E
source chain: PRDiffAdjustData and LakituAndSpinyHandler through ChpChpEx.
Entry is the original frenzy dispatcher, with SetupLakitu and SmallBBox now
available from S4. Exits are original timer/slot/state gates, the no-free-slot
return, Lakitu recreation or Spiny egg completion. Preserve original descending
searches, counter wrap, exact RAM scratch writes and shared child call order.

PutAtRightExtent and PlayerLakituDiff remain separately owned dependencies.
Expose their existing native entries without granting child-node credit or
repairing their unadmitted interiors. The former can be extracted from the
existing flame-position/finish body; the latter currently has missing scratch
semantics. Original child-entry/return records may prove caller obligations,
but actual-child execution and residual differences must be separately kept.
No frenzy-dispatcher, flying-fish, firebar, movement/collision or platform fix
is admitted. Similar-issue sweep covers every incoming handler call, both
allocation scans and all producer/consumer aliases of the random scratch.

ROM-logic proof audits the immutable twelve-byte table, every branch/write,
ObjectOffset restoration and child argument/order against original NMI routes.
Native proof covers gates, allocation order, counter wrap, PRNG combinations,
source-fixed zero speed/rightward egg direction and full-RAM write footprints;
then x86/x64, DOS16 link, platform purity and three owner-authorized EXEs.
Existing owner-local ROM/listing provenance is retained, without third-party
implementation import. Reuse S3/S4 records where applicable; new raw records
stay below build/m2-t38-s5 with a four-MB budget, twenty-second run timeout
and S5 cleanup ownership. Stop for unadmitted repair, patched reference state
outside the declared NMI RAM fixture, hidden mismatch or platform gameplay.
Closure requires all thirteen exact dispositions, dual evidence, ledger and
tracker agreement and three EXEs. No node credit is awarded at admission.

## S5 original Lakitu/Spiny proof

S5 closes all thirteen received and expected caller/data nodes, with no
scoped transfer: 948 -> 961 / 1,992. This is caller-chain proof, not completion
of PlayerLakituDiff, PutAtRightExtent or the containing frenzy dispatcher.
S6 firebar initialization remains next in the original source sequence.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| PRDiffAdjustData | $C398 | Twelve original bytes bound to all four PRNG selectors and their reverse scratch order; match |
| LakituAndSpinyHandler | $C3A4 | Honor timer before slot gate; set timer and descend through ID slots without a flag filter; match |
| ChkLak | $C3B4 | Compare ID and descend from slot four to zero; original taken and fallthrough edges observed; match |
| ChkNoEn | $C3CA | Descend through flag slots; retain the all-occupied exit after wrapped counter threshold; match |
| CreateL | $C3D3 | Write state and Lakitu ID, call SetupLakitu, then PutAtRightExtent with Y argument $20; match |
| RetEOfs | $C3E3 | Restore source ObjectOffset after temporary allocation-slot selection; native slot argument remains local; match |
| ExLSHand | $C3E5 | Preserve every early-return footprint: busy timer, special slot, low counter, player height and Lakitu state; match |
| CreateSpiny | $C3E6 | Copy Lakitu page/X, set high Y, subtract eight with byte wrap; do not manufacture an ID write; match |
| DifLoop | $C40F | Write table offsets seed, seed+4 and seed+8 to RAM $03,$02,$01, then reload ObjectOffset; match |
| UsePosv | $C433 | Preserve low-player-speed PRNG sign-selection route; its value is discarded by the next original child; match |
| SetSpSpd | $C434 | Call SmallBBox after PlayerLakituDiff; its zero A clears horizontal speed and prevents the BMI branch; match |
| SpinyRte | $C440 | Set rightward direction, vertical speed $FD, enabled flag and egg state five in original order; match |
| ChpChpEx | $C44E | Return after the egg writes without touching unrelated RAM; match |

Eighty controlled NMI RAM routes enter through the original queue, checkpoint
and frenzy vector. No fixture changes CPU PC, stack or ROM. All twelve code
labels execute, the twelve-byte table matches the original ROM, and all twelve
variable conditional branches execute both outcomes. The two remaining edges
are fixed by source: $C3D1 BMI follows an exhausted DEX/BPL scan with X=$FF;
$C43D BMI cannot be taken because SmallBBox returned A=$00. The native
allocation matrix independently covers all 256 counter bytes and all 32 slot
masks. All four original child call edges are mapped explicitly.

Caller comparison passes 160/160 across x86/x64. The host-only
lakitu_spiny_snapshot_check instruments the production frenzy and initializer
objects: it checks the child-entry portable RAM and call order, then explicitly
substitutes the recorded original child-return RAM. It neither certifies child
interiors nor changes the original execution. Source inspection additionally
checks child slot arguments, PutAtRightExtent's $20 argument and the discarded
PlayerLakituDiff return value. Eighty observer-free runs produce byte-identical
original frame records. Hardware return-stack storage is excluded, but all
mapped game variables at $0109-$0139 remain compared.

Actual native execution without substitutions matches 36/160. All remaining
124 comparisons differ only at RAM $00: the pre-existing PlayerLakituDiff
omits the original scratch-distance write. Its static adjustment table and
other branch semantics also remain unadmitted; a discarded return value does
not make that child conformant. PlayerLakituDiff retains its existing ledger
owner and later source-order slice. PutAtRightExtent is extracted unchanged
from the prior flame positioning/finish body, with no child-node credit.

The independent native caller-footprint matrix passes 71,163 cases per width:
timer/slot gates, counter wrap, all free-slot masks, coordinate/page carry,
player-height and Lakitu-state gates, PRNG selectors and all player-speed
bytes. It explicitly evaluates the existing distance child at its boundary;
that test is not an independent correctness claim for the child. The focused
CTest is mysmb.lakitu-spiny-chain. All 544 previously matching actual roots
remain matched: loop 166/192, parser 138/160, full initializer 136/220 and the
added S4 common cases 104/104. Forty related regression runs retain the same
38 passes and the two pre-existing Bowser exit-4 failures, one per width.

Strict C90 builds compile all 85 shared translation units for x86/x64; both
self-tests and bounded hidden-window response probes pass. DOS16 links with
the existing OLDNAMES warning. It remains link-only: no DOS runtime, resource
binding, playability or physical 486 performance claim is made. Platform
purity passes; all changes to gameplay stay in the shared game owner.

Similar-issue sweep checks the sole frenzy-dispatch caller, both descending
searches, both PlayerLakituDiff consumers and all PutAtRightExtent source
callers. The existing MoveLakitu body and BulletBillCheepCheep positioning
remain unchanged for their later source slices. The Bowser flame caller now
uses the extracted identical positioning/finish entry, preserving its current
behavior. No actor movement, frenzy-vector scratch, firebar or platform fix
is silently included.

Reproducible neutral harnesses are lakitu_spiny_fixture.h,
lakitu_spiny_chain_smoke.c, lakitu_spiny_snapshot_check.c and the extended
enemy_loop_actual_check.c/reference_frame_recorder.c. Record with
--fixture=t38-spiny=N (0 through 79), --lakitu-spiny-snapshot and
--control-children; run --pc-coverage separately. Only the host caller checker
build instruments frenzy.c and init_targets.c with -finstrument-functions;
production and actual comparisons use ordinary objects. Original records,
coverage, build logs and summaries remain below ignored build/m2-t38-s5;
raw evidence is below 1.3 MB of the four-MB budget with twenty-second recorder
timeouts. Prior S1-S4 evidence is reused in place.

The following owner-authorized test artifacts are refreshed together; this is
not full-game certification.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 254769 | 82ccf7ec3012ff5952ad96b2129ce5f6830f1d6d65bdee710fd99f063996fbcf |
| mysmb32.exe | 337896 | 63912054d168cfdfbd5cb41c2d711732cbc8ccd6dd4bb15590d9590a06fb6e17 |
| mysmb64.exe | 344978 | 5bbbb2061c9398d361107af4d3fa8c117d23cff1a922e246b36e773ee68b987c |

## S6 admission: firebar initialization and duplicate dependency

After S5 commit 5d7ead6, coordinator accepts transfer-170 from T19 S5.
The four original S6 labels are joined by DuplicateEnemyObj, FSLoop and FlmEx:
InitLongFirebar directly calls this missing native child. These three dependency
nodes are admitted here rather than adding a no-op or fabricated substitute.
The later Bowser slice retains their original source position and maintenance
obligation, reuses this child, and must not count them again. T38's initial
91-node forecast becomes 94 unique labels, maximum 978/1,992; S7 remains ten.
This is the same immediate-dependency rule already applied to the S1 loop.

All seven labels in the updated S6 row are open: incoming 961/1,992, seven
expected, maximum 968. Shared enemy/init_targets.c owns the firebar entries
$C44F-$C487 and duplicate dependency $C575-$C59C (exact symbol/ROM bounds are
checked before credit). Entry is the original initializer vector, IDs $1B-$1F;
long entry calls the shared duplicate child before continuing the short entry.
Exit uses the existing TallBBox2 box-only tail, with no new credit for that tail.

Restore both five-byte data tables, ID-minus-$1B indexing after the child,
low spin-state clear only, Y/X plus four with carry to page, and unchanged
unrelated flags/state/vertical fields. The duplicate child scans source RAM
with byte-sized Y, writes the duplicate offset and high-bit parent flag, copies
coordinates, enables the parent and sets duplicate high-Y. Do not introduce a
six-slot cap absent from the original. Bowser's caller and actor/OAM semantics
remain outside this S; wire its child only during its own source admission.

ROM proof uses the retained initializer records plus bounded NMI RAM variants
for every firebar ID, fractional sentinels, coordinate carry/wrap and duplicate
selection. Compare actual child results; no original PC/stack/ROM patching.
Native proof independently checks full-RAM footprints and duplicate aliases,
then cross-width C90 builds, DOS16 link, platform purity, hidden-window probes
and three owner-authorized EXEs. Similar-issue sweep covers both source callers
of DuplicateEnemyObj, vector firebar entries and the TallBBox2 consumers.

The existing owner-local ROM/listing remains research/build input, with no
third-party implementation import. New records, logs and intermediates stay
below ignored build/m2-t38-s6 with a four-MB raw budget and twenty-second
recorder timeouts; S6 owns cleanup. Stop on unadmitted repairs, hidden mismatch,
reference mutation or platform game logic. Closure requires all seven exact
node dispositions, both proof tracks, ledger/tracker and three artifact records.

## S6 original firebar and duplicate proof

All seven received nodes are complete: four planned firebar data/entry nodes
and three admitted immediate-dependency nodes. Progress is 961 -> 968/1,992,
with no scoped transfer. T38's updated total is 94, maximum 978; S7 retains
ten flying-fish nodes. The later Bowser caller must reuse the duplicate child
and cannot count these dependency nodes a second time.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| FirebarSpinSpdData | $C44F | All five speed bytes bound to original ROM and their five consuming IDs; match |
| FirebarSpinDirData | $C454 | All five direction bytes bound to original ROM and their five consuming IDs; match |
| InitLongFirebar | $C459 | Invoke original duplicate child before entering short initialization; duplicate retains pre-adjustment coordinates; match |
| InitShortFirebar | $C45C | Clear only low spin state; index by post-child ID minus $1B, write spin fields, add four to Y/X with page carry, then box-only tail; match |
| DuplicateEnemyObj | $C575 | Scan for zero flag, store duplicate offset/high-bit parent flag, copy page/X, enable parent, set duplicate high-Y and copy Y in exact order; match |
| FSLoop | $C577 | Byte-sized ascending scan without an invented slot-count bound; both branch directions execute; match |
| FlmEx | $C59C | Return preserves the caller slot and unrelated RAM; actual long-entry completion includes this shared child exit; match |

Actual original/native comparison passes 100/100 across x86/x64: ten retained
S3 firebar scenarios plus forty new RAM-only NMI scenarios, each on both
widths. Every firebar ID, both initializer entries, coordinate wrap/page carry,
fractional/vertical sentinels and different duplicate slots are covered. No
child-return substitution is used. All five code labels execute, both five-byte
tables match the original ROM and native constants, the duplicate scan's
conditional branch executes both outcomes, and both call/tail edges are
verified. Forty observer-free runs produce byte-identical frame records.

The focused mysmb.firebar-initialization-chain test passes 9,216 independent
full-RAM footprints per width: all five IDs, all six parent slots and all
coordinate bytes, plus direct duplicate scans for all 256 byte-sized target
indices. The latter are deliberate native boundary tests, not a claim that
every such index occurs during ordinary gameplay. Original retained routes
also exercise the scan beyond the normal five actor slots. Hardware return
stack is excluded from reference comparison; mapped game RAM $0109-$0139 is
retained. No original PC, stack, ROM or result is patched.

All 580 prior actual matches remain. The cross-chain matrix now has 612
matches: loop 166/192, parser 150/160 (was 138), full initializer 156/220
(was 136), prior common cases 104/104 and Lakitu/Spiny 36/160. The latter's
124 PlayerLakituDiff scratch differences are unchanged. Forty related native
regression runs preserve 38 passes and the two existing Bowser exit-4 failures.
This S does not claim full-game behavior or repair those other children.

All 85 shared C units compile under strict C90 for x86/x64. Both self-tests,
bounded hidden-window responsiveness checks and platform-purity checks pass.
DOS16 links with the existing OLDNAMES warning; this remains link-only, without
DOS runtime, resource-binding, playability or physical 486 certification.

Similar-issue sweep finds four short and one long vector entry, two original
DuplicateEnemyObj callers (long firebar and the future Bowser initializer),
and the shared TallBBox2 consumers. The existing box-only tail is reused,
without generic flag/state/vertical resets. Bowser's legacy initializer and
both actors' later OAM/movement bodies remain for their planned source slices;
no host adapter or unadmitted caller is changed.

Reproduce with the extended enemy_init_fixture.h cases 162 through 201 and
reference_frame_recorder --fixture=t38-init=N --enemy-init-snapshot plus
--control-children; record --pc-coverage separately. Compare snapshots using
enemy_loop_actual_check with ordinary shared objects, and run
firebar_initialization_smoke. Retained S3 cases 54 through 63 cover the original
five IDs in both normal/special slots. Logs, records, source audit and build
summaries stay below ignored build/m2-t38-s6; raw evidence is below 0.6 MB of
the four-MB budget, with twenty-second recorder timeouts. Existing owner-local
ROM/listing provenance is unchanged; no third-party implementation is imported.

Three owner-authorized test artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255089 | 20fd70eb82c4528c554e4c7ecbb1532ddaf7a7bfe93b080a903bf0e508d1c1a8 |
| mysmb32.exe | 337962 | 3dbe7c6d63285fa32506ad941e61c4d00696474ae898836f0a614aac68d0662d |
| mysmb64.exe | 345555 | 5bc98c329aaf99e5da997b2cf662b75943a30be0c26f879d2642972af1add01b |

## S7 admission: complete flying-fish initializer

After S6 commit d9921d3, coordinator accepts transfer-171 from T19 S5 for
all ten exact labels in the S7 plan row. All are open: incoming 968/1,992,
ten expected, maximum 978. Shared enemy/frenzy.c owns $C488-$C548, all three
tables and InitFlyingCheepCheep through FinCCSt. Entry is the original frenzy
vector, exit is the existing ChpChpEx return or completed spawn. SmallBBox
is a proven S4 child and ChpChpEx is an S5 maintenance dependency, with no
new credit for either. The frenzy dispatcher and moving fish actor remain
separate, unadmitted interiors.

Restore timer-first gating, SmallBBox before slot-limit rejection, random timer,
secondary-hard limit in scratch $00, original $00/$01 random intermediates,
player-speed classes and register-Y-dependent position selection. Moving
players retain the speed-table index in Y; stationary players load Y from
scratch $00. Preserve direction inversion, add/subtract carry/page wrap and
final flag/high-Y/Y writes. Do not add an Enemy_ID write absent from source.

ROM proof binds all 32 table bytes and every branch/write/call to original
NMI RAM routes with varied slots, speed thresholds, PRNG and coordinates.
Actual child comparisons remain separate from the surrounding dispatcher's
known scratch debt. Native proof checks full-RAM footprints across the state
matrix, then strict C90 x86/x64, DOS16 link, platform purity, hidden-window
probes and three owner-authorized EXEs. Similar-issue sweep covers the sole
frenzy entry, scratch producers/consumers, all table indexes and actor callers.

Existing owner-local ROM/listing provenance is unchanged; no third-party
implementation import. New records/logs/intermediates stay beneath ignored
build/m2-t38-s7 with a four-MB raw budget, twenty-second recorder timeout and
S7 cleanup ownership. Stop on reference PC/stack/ROM patch, hidden mismatch,
unadmitted repair or platform gameplay. Close only with ten exact dispositions,
both proof tracks, tracker/ledger agreement and all three artifacts.

## S7 original flying-fish proof

All ten planned flying-fish nodes close with actual original/native proof:
968 -> 978/1,992, no scoped transfer. All seven S chains have completed their
updated 94 unique T38 targets. The final aggregate review below closes T38; no later T is admitted by
this S closure.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| FlyCCXPositionData | $C488 | All sixteen position bytes match original ROM and are consumed by recorded routes; match |
| FlyCCXSpeedData | $C498 | All twelve speed bytes match original ROM and all offsets execute; match |
| FlyCCTimerData | $C4A4 | All four timer bytes match original ROM and all offsets execute; match |
| InitFlyingCheepCheep | $C4A8 | Timer-first gate; shared SmallBBox before random timer and capacity rejection, including slot five; match |
| MaxCC | $C4C4 | Write three/four capacity to RAM $00 and compare the original current slot; match |
| GSeed | $C4E4 | Preserve player-speed bias and first PRNG bits in $00/$01 before conditional third-byte replacement; match |
| RSeed | $C4F8 | Recover speed-table index from saved bias plus $01, preserving Y for the moving-player position route; match |
| D2XPos1 | $C51C | Stationary path reloads Y from $00; moving path keeps speed index; use Y bit one and original carry for addition; match |
| D2XPos2 | $C530 | Subtract original position table value and propagate borrow to player page; match |
| FinCCSt | $C53C | Write resulting page, flag/high-Y one and Y=$F8; no fabricated ID write; match |

Actual original/native comparison passes 304/304 across x86/x64, with no
child-return substitutions. The 152 controlled NMI RAM routes exercise all
six slots, timer busy/expired, normal/hard limits, stationary/slow/fast/high-bit
player speeds, every table index and page carry/borrow. All seven code labels
execute; all 32 data bytes match both ROM and native constants; all nine
conditional branches execute both outcomes. The SmallBBox call and FinCCSt
jump retain their source order. Every position/speed/timer index has a recorded
consumer. Observer-free coverage runs produce identical frame records.

The independent full-RAM test passes 26,106 cases per width. It checks busy
timer immutability, post-SmallBBox slot rejection and the complete low-bit PRNG
combination matrix across player-speed thresholds and coordinate/page wrap.
The old flying_cheep_smoke was first run unchanged on both old and new cores:
both failed at its obsolete parser-with-null-source queue entry. Updating only
that fixture to the original queue owner, ProcLoopCommand, makes both cores
pass; no production parser change or weakened state assertion is included.

The final S1-S7 cross-chain matrix preserves all 692 previously matching
actual comparisons. It includes loop, parser, full initializer, S4 common,
S5 Spiny, S6 firebar and S7 flying-fish roots. Existing child failures remain
explicit in the matrix; successful caller proof does not certify descendants.
The focused earlier initializer/stream/common/firebar/Lakitu and corrected
flying-fish native tests all pass on both widths. Forty additional regression
runs retain 38 passes and the two baseline Bowser exit-4 failures.

Strict C90 builds compile all 85 shared units for x86/x64; self-tests, bounded
hidden-window response probes and platform purity pass. DOS16 links with the
existing OLDNAMES warning and remains link-only: no runtime, resource-binding,
playability or physical 486 claim. All gameplay changes remain in the shared
owner. The frenzy dispatcher's nested JumpEngine scratch and the moving actor
are untouched and retain their planned later source slices.

Similar-issue sweep covers the sole production frenzy entry, all three data
consumers, scratch $00/$01 producers, stationary/moving Y selection, and the
actor boundary. Existing SmallBBox and ChpChpEx dependencies are reused with
no repeated node credit. No new external source or implementation is imported.

Reproduce using flying_fish_fixture.h cases 0 through 151 and the recorder's
--fixture=t38-fish=N, --flying-fish-snapshot and --control-children options;
run --pc-coverage separately. enemy_loop_actual_check compares the actual
shared chain without instrumentation/substitution. Native targets are
mysmb.flying-fish-initialization-chain and mysmb.flying-cheep-smoke. New local
records/logs/build summaries remain beneath ignored build/m2-t38-s7, with less
than 1.9 MB raw output under the four-MB budget and twenty-second recorder
timeouts. Earlier S records are reused in place. Hardware return-stack storage
is excluded from snapshots, but mapped game RAM $0109-$0139 remains checked.

Three owner-authorized test artifacts are refreshed together:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255585 | cc34d4af1cd1a96ec3a2cb442d09c1767728712afc21817603511ec14432f938 |
| mysmb32.exe | 337962 | 2c0184a49a5f39da5e9f91d9bbe4b79c1549c0707a0069e05b5a34b3fde9f7e4 |
| mysmb64.exe | 345555 | ea0eb8098a6631b03c02817ae3c1a34f738df676bb8b2e258242059aed277822 |

## T38 closure

The seven source-ordered S chains complete 94 unique original nodes:
S1 19, S2 19, S3 3, S4 23, S5 13, S6 7 and S7 10. All expected labels are
ROM-match complete, none are retained unfinished in T38, and no completion
credit is inferred for unadmitted descendants. Global progress is 884 ->
978/1,992. The initial 91-node forecast gained the three explicitly admitted
DuplicateEnemyObj dependency nodes; the later Bowser slice reuses them.

The final integrated cross-chain comparison uses ordinary shared C objects,
without recorded child-return substitution:

| Original route family | Actual matches | Remaining differences |
| --- | ---: | ---: |
| loop | 166/192 | 26 |
| stream | 150/160 | 10 |
| init | 156/220 | 64 |
| common | 104/104 | 0 |
| spiny | 36/160 | 124 |
| firebar | 80/80 | 0 |
| fish | 304/304 | 0 |

Total 996/1,220 actual comparisons match; 224 remain. All 692 earlier matching
roots are preserved. The 26 loop descendants, ten parser descendants, 64
initializer descendants and 124 PlayerLakituDiff scratch cases retain their
separate original-node ownership and planned source slices. Their failures
are neither discarded nor certified by the caller proofs. The final matrix
and prior S evidence are complementary: node-level source audits certify the
94 scoped nodes; the integrated matrix exposes remaining downstream work.

S7's final build, seven focused native targets per width, forty additional
regressions, platform-purity check, hidden-window probes and the three recorded
artifact hashes form the T-level delivery. Earlier accepted S proofs are reused
rather than rerun as new paperwork units. Baseline Bowser native failures and
DOS link-only limits remain explicit. This closes T38, not M2 or full-game
certification. Next is the queued special-initialization/frenzy slice beginning
InitBowser; it is not admitted by this closure.
