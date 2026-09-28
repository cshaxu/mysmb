# M2 T40: Enemy movement, firebars and Lakitu distance

## Scope and source boundary

T39 closed in fa80503 at 1,059/1,992. T40 begins MovePodoboo at line 9212
and ends after ExMoveLak at line 10091. The previous line-10100 cut entered
BridgeCollapse; keep BridgeCollapseData (10092) and BridgeCollapse (10098)
with the complete bridge/Bowser chain in the next slice. This moves two
planned labels without changing their current receivers or match status.

Scope is 120 unique nodes: 107 incomplete targets and thirteen retained
matches. Maximum is 1,166/1,992. All incomplete labels currently belong to
T19 S5; retained normal-motion labels and tables belong to T31 S2. Only S1
receives its nodes now. Later S rows show planned ownership but retain their
current ledger receivers until their own admission.

## Source-ordered S plan

Every S delivers one whole control/data chain with original logic proof,
independent native validation and three EXEs. Distinct short movement leaves
stay separate when their original caller routes/branch families differ.
Adjacent timer tables, internal labels and normal-movement fallthrough remain
with their consumers. No separate mapping/test/paperwork S is added.

| S | Chain | Shared owner | Expected / scoped | Exact labels in source order |
| --- | --- | --- | ---: | --- |
| S1 | Podoboo movement | enemy/podoboo.c | 2 / 2 | `MovePodoboo`, `PdbM` |
| S2 | Hammer Bro state machine and normal/defeated tail | enemy/movement.c and Hammer Bro owner | 11 / 24 | `HammerThrowTmrData`, `XSpeedAdderData`, `RevivedXSpeed`, `ProcHammerBro`, `ChkJH`, `DecHT`, `HammerBroJumpLData`, `HammerBroJumpCode`, `SetHJ`, `HJump`, `MoveHammerBroXDir`, `Shimmy`, `SetShim`, `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`, `SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`, `ChkKillGoomba`, `NKGmba` |
| S3 | Jumping/red Paratroopa movement | enemy/movement.c and Paratroopa owner | 5 / 5 | `MoveJumpingEnemy`, `ProcMoveRedPTroopa`, `NoIncPT`, `MoveRedPTUpOrDown`, `MovPTDwn` |
| S4 | Green Paratroopa and shared X counters | enemy/movement.c and shared X-counter owner | 10 / 10 | `MoveFlyGreenPTroopa`, `YSway`, `NoMGPT`, `XMoveCntr_GreenPTroopa`, `XMoveCntr_Platform`, `NoIncXM`, `IncPXM`, `DecSeXM`, `MoveWithXMCntrs`, `XMRight` |
| S5 | Bloober movement/swimming state | Bloober movement owner | 16 / 16 | `BlooberBitmasks`, `MoveBloober`, `FBLeft`, `SBMDir`, `BlooberSwim`, `SwimX`, `LeftSwim`, `MoveDefeatedBloober`, `ProcSwimmingB`, `BSwimE`, `SlowSwim`, `NoSSw`, `ChkForFloatdown`, `Floatdown`, `NoFD`, `ChkNearPlayer` |
| S6 | Bullet Bill movement | Bullet Bill movement owner | 2 / 2 | `MoveBulletBill`, `NotDefB` |
| S7 | Swimming Cheep-Cheep movement | swimming fish movement owner | 7 / 7 | `SwimCCXMoveData`, `MoveSwimmingCheepCheep`, `CCSwim`, `CCSwimUpwards`, `ChkSwimYPos`, `YPDiff`, `ExSwCC` |
| S8 | Firebar position, rendering and collision chain | firebar actor and OAM owners | 32 / 32 | `FirebarPosLookupTbl`, `FirebarMirrorData`, `FirebarTblOffsets`, `FirebarYPos`, `ProcFirebar`, `SusFbar`, `SkpFSte`, `SetupGFB`, `SetMFbar`, `DrawFbar`, `NextFbar`, `SkipFBar`, `DrawFirebar_Collision`, `AddHA`, `SubtR1`, `ChkFOfs`, `VAHandl`, `AddVA`, `SetVFbr`, `FirebarCollision`, `AdjSm`, `BigJp`, `FBCLoop`, `ChkVFBD`, `ChkFBCl`, `Chk2Ofs`, `ChgSDir`, `SetSDir`, `NoColFB`, `GetFirebarPosition`, `GetHAdder`, `GetVAdder` |
| S9 | Flying Cheep-Cheep movement | flying fish movement owner | 6 / 6 | `PRandomSubtracter`, `FlyCCBPriority`, `MoveFlyingCheepCheep`, `FlyCC`, `AddCCF`, `BPGet` |
| S10 | Lakitu movement and distance helper | enemy/frenzy.c and Lakitu movement owner | 16 / 16 | `LakituDiffAdj`, `MoveLakitu`, `ChkLS`, `Fr12S`, `LdLDa`, `SetLSpd`, `SetLMov`, `PlayerLakituDiff`, `ChkLakDif`, `SetLMovD`, `ChkPSpeed`, `ChkSpinyO`, `ChkEmySpd`, `SubDifAdj`, `SPixelLak`, `ExMoveLak` |

- S1: Expired/nonexpired timer, real InitPodoboo call, post-init PRNG read,
  force/timer/speed writes and unconditional MoveJ_EnemyVertically tail.
- S2: Hammer throw/jump timers, spawn carry, offscreen gate, PRNG jump length,
  shimmy/player-distance direction and direct normal/defeated fallthrough.
  Revalidate thirteen retained normal-motion/table nodes; do not double count.
- S3: Jumping gravity/horizontal order and red Paratroopa center/direction state.
- S4: Green X/Y modes, shared primary/secondary counters and signed movement.
- S5: Bloober direction, swim acceleration/deceleration, float-down/player gates
  and defeated tail, including source byte aliases and underflow behavior.
- S6: Bullet timer/defeat gates, signed horizontal motion and shared gravity.
- S7: Swimming-fish fractional X motion, Y anchor distance and direction flips.
- S8: Full firebar actor, tables and position/collision loop; long-bar aliases,
  mirrored offsets, OAM and injury gates belong to this continuous chain.
- S9: Flying-fish gravity, PRNG vertical adjustment and sprite priority state.
- S10: Lakitu range/turn/speed plus PlayerLakituDiff scratch and register result;
  reuse this helper for prior Spiny callers and expose their actual regressions.

Each admission names original entry/exit, dependency receipts, exact current
states and expected matches. Dependencies already proved in T37/T38/T39 are
reused; unproved child returns may be substituted only after complete input
comparison and with actual-child failures separately retained. Source and
native validation remain distinct. Every P refreshes DOS16/x86/x64 artifacts;
T closure combines the route matrix, exact node dispositions and platform
purity. No source-order jump or implicit child conformance is permitted.

## S1 admission: Podoboo movement

Coordinator accepts transfer-184 for MovePodoboo and PdbM, both open and
expected new. Baseline 1,059/1,992, maximum 1,061. Source $C9B0-$C9CD follows
EraseEnemyObject and ends at the unconditional MoveJ_EnemyVertically tail.
Shared owner is enemy/podoboo.c; actor/aggregate declarations remain compatible.
S2 is the next Hammer Bro/normal-motion chain.

Replace the copied inline initialization with the proven InitPodoboo entry.
Read PRNG only after that child returns; set force OR $80, timer (low nibble
OR six), speed $F9, then execute gravity on both timer branches. Remove the
non-source flag/ID check from the source entry and retain it only on the legacy
bulk interface. Do not modify initializer or gravity algorithms.

Original unchanged NMI routes cover both timer branches, PRNG extremes and
both edge slots; separate observer-free records check noninterference. Use
actual shared initializer/gravity comparison as the primary proof, with exact
child input/order records for diagnosis. Independent native contracts exercise
all six slots, every PRNG byte, post-init mutation and preserved unrelated RAM.
Recheck earlier actual matches, strict C90 x86/x64, DOS16 link, platform purity,
hidden-window response and all three EXEs. Stop on unadmitted child repair,
original CPU/ROM/stack patching or masked state differences.

Existing owner-local ROM/listing provenance and local-only redistribution
status are unchanged; no third-party implementation import. Generated data,
raw records, logs and intermediates stay in ignored build/m2-t40-s1, with
four-MB raw budget, twenty-second recorder timeout and S1 cleanup ownership.
Concurrent independent records use unique paths and stable checkpoint files.

## S1 original Podoboo proof

S1 P1 closes both expected nodes: 1,059 -> 1,061/1,992. Neither scoped
node remains unfinished or transferred. T40 continues with its planned S2.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| MovePodoboo | $C9B0 | Timer read/branch, real InitPodoboo child, post-child PRNG and force/timer/speed stores match; new ROM-match complete. |
| PdbM | $C9CB | Both paths unconditionally tail-call MoveJ_EnemyVertically, preserving initializer and gravity effects; new ROM-match complete. |

All twelve instructions in $C9B0-$C9CD execute in unchanged original-ROM
NMI routes. Sixteen roots take the expired branch and 48 the active branch;
slots zero/five and entry timers 0/1/2/255 are observed. The eight PRNG seed
values pass through the original NMI LFSR before entry; they are not falsely
reported as the same eight entry values. The actual post-initializer values
observed are 0, 3, 4, 7, 63, 64 and 127. Independent native contracts cover
all 256 post-child bytes on all six slots and four timer cases (6,144 cases
per width), with child-mutated eligibility flags and complete RAM footprints.

Original caller handoffs pass 128/128 across x86/x64, covering 80 child
records. Entry RAM is compared before any diagnostic recorded return is
used. Separately, real shared initializer and gravity execution also passes
128/128; these are the primary node proofs. Comparisons exclude hardware
stack bytes but retain mapped $0109-$0139 variables. Original ROM, CPU,
stack and scratch are never patched. All 64 observer-free frames equal the
observed recordings. This noninterference check does not claim full-game
native frame equality. Neither scoped caller writes PPU/audio state directly.

The shared movement now resides in enemy/podoboo.c. Its original source
entry has no extra flag/ID condition. The legacy aggregate retains its
eligibility filter before calling the same entry. InitPodoboo and gravity
remain their existing shared owners; the copied initializer and incorrect
old address comment are removed. No platform-specific gameplay was added.

Similar-issue sweep covers all Podoboo movement declarations, normal-vector
and bulk callers, initializer dispatcher/owner and graphics callers. The
normal vector directly reaches the new entry; only the legacy bulk interface
filters objects. Initialization has one implementation. The graphics entry
is unchanged and no graphics node receives credit. Adjacent actor algorithms
retain their planned later S ownership.

Strict C90 builds pass for all 89 shared units on x86/x64. Self-tests and
hidden-window message-response probes pass on both widths; platform purity
passes. Fifteen prior full native suites plus normal/vector/retainer/cannon
caller contracts pass per width. Existing Bowser damage and endgame star
timer failures remain unchanged; existing Spiny and other child gaps remain.
DOS16 builds/links with the pre-existing OLDNAMES warning and remains
link-only: no DOS graphics, resource-binding or 486 performance claim.

The integrated original-snapshot matrix is 3,382/4,170; all 3,254 previously
passing comparisons remain passing. Remaining differences retain their
existing source-order owners.

Reproduce with podoboo_movement_fixture.h cases 0..63,
--fixture=t40-podoboo=N, --podoboo-snapshot, --control-children and a separate
--pc-coverage run. podoboo_snapshot_check diagnoses caller handoffs;
enemy_loop_actual_check executes real children. mysmb.podoboo-movement is
the native mutation-contract target. Local source-audit.json and checkpoint
summaries record exact coverage. Raw records occupy 873,952 bytes under the
four-MB bound in ignored build/m2-t40-s1, with unique concurrent paths and
twenty-second per-run timeout. They remain local regression inputs while
the admitted dependent chains need them. Source provenance is unchanged.
The three owner-authorized EXEs are refreshed together.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256429 | eff523d19aa55fb250274b9fff7a2be620277cdc61e9ce587be0fa20adb4dced |
| mysmb32.exe | 343892 | 6469c8a3b414adedaf9a1051505fa20409b07d3c6f032547ff9961ff272a2d9e |
| mysmb64.exe | 351075 | 713251f563349d18dc59f6f9d469f0e9815f33dc1853773b61d048c42730f4b6 |

## S2 admission: Hammer Bro and normal movement

S1 closed in 3f77065. Coordinator accepts transfers-185/186. S2 receives
the entire source-ordered 24-node row above, $C9CE-$CAF8 (lines 9229-9395).
Baseline 1,061/1,992; eleven expected new, thirteen retained; maximum 1,072.

Expected new (all open): `HammerThrowTmrData`, `ProcHammerBro`, `ChkJH`, `DecHT`, `HammerBroJumpLData`, `HammerBroJumpCode`, `SetHJ`, `HJump`, `MoveHammerBroXDir`, `Shimmy`, `SetShim`.

Retained ROM matches: `XSpeedAdderData`, `RevivedXSpeed`, `MoveNormalEnemy`, `FallE`, `MEHor`, `SlowM`, `SteadM`, `AddHS`, `ReviveStunned`, `SetRSpd`, `MoveDefeatedEnemy`, `ChkKillGoomba`, `NKGmba`.

Entry is ProcHammerBro ($C9D8), with its preceding throw/speed tables and
internal jump-length table. Both normal and defeated movement tails stay
in the same S; exit is the native movement return after NKGmba. S1 Podoboo
is complete; S3 jumping/red Paratroopa is the next chain, not part of S2.
Shared owners are enemy/hammer_bro.c and enemy/movement.c. Extract the
source actor from objects.c, retaining only bulk eligibility there. Expose
the real defeated entry instead of copying its two-child tail. Do not
duplicate MoveNormalEnemy or silently retain the approximate local tail.

Logic track: bind all four tables to original bytes; cover defeat, jump
timer decrement, offscreen throw skip, existing throw timer, spawn carry
success/failure, vertical thresholds $70/$80, both PRNG bits and secondary
hard mode. Preserve scratch $00, post-child reads, signed page subtraction,
walking timer/facing and the original unconditional normal-motion fallthrough.
Use unchanged NMI routes with actual child execution and complete input/order
diagnostics; no original CPU/stack/ROM patch or scratch masking.

Dependencies: SpawnHammerObj and shared movement/gravity/erasure have
existing proofs. PlayerEnemyDiff is still an open later-source dependency;
its former inline arithmetic must have an explicit shared child boundary.
Record that seam separately, preserve its current receiving owner and grant
no child-node credit here. Any reused source arithmetic, carry/negative
result and scratch effects must be visible in the child-input and actual
comparison evidence. Unrelated callers/child algorithm repairs are not
implicitly admitted. If a child prevents actual closure, report the exact
gap instead of declaring caller tests to be end-to-end fidelity.

Operational track: focused Hammer Bro, normal-motion and child-order/mutation
tests on both native widths; retain prior original-snapshot matches; strict
C90 builds, DOS16 link, purity, hidden-window response and three refreshed
EXEs. Revalidate the thirteen retained nodes without duplicate credit. The
existing Bowser/endgame/Spiny gaps remain separate obligations.

Similar-issue sweep covers the source/bulk actor guards, both hard-mode
aliases, hammer spawn carry consumers, the defeated entry and normal-motion
aliases. No presentation adapter may gain gameplay. Existing owner-local
ROM/listing provenance is unchanged, with no third-party import. Temporary
research, bounded records, logs and generated artifacts stay below ignored
build/m2-t40-s2. Declare fixture count and raw-byte/time budgets before
recording; independent records use unique paths and resumable checkpoints.
S2 closes only after exact node dispositions, both evidence tracks, ledger,
tracker and all three artifact records agree.

## S2 original Hammer Bro and normal proof

S2 P1 closes eleven expected new nodes and revalidates thirteen retained
matches: 1,061 -> 1,072/1,992. All 24 scoped nodes are complete; no scoped
unfinished transfer remains. PlayerEnemyDiff keeps its later-source owner
and receives no node credit. S3 is next in the existing source-order plan.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| HammerThrowTmrData | $C9CE | Both secondary-mode throw timer bytes and consumers; new match |
| XSpeedAdderData | $C9D0 | All four signed temporary speed-adder bytes and consumers; retained match |
| RevivedXSpeed | $C9D4 | All four primary-mode revival speed bytes and consumers; retained match |
| ProcHammerBro | $C9D8 | Defeated priority and complete throw/jump/movement sequence; new match |
| ChkJH | $C9E1 | Jump timer decrement and offscreen throw gate; new match |
| DecHT | $CA0A | Existing/failed-spawn timer decrement; successful spawn bypasses it; new match |
| HammerBroJumpLData | $CA10 | Both jump length bytes selected by secondary mode and PRNG mask; new match |
| HammerBroJumpCode | $CA12 | Jumping-state guard and Y sign/$70 thresholds; new match |
| SetHJ | $CA37 | Vertical speed, jump bit and scratch-selected PRNG index; new match |
| HJump | $CA4B | Jump frame length and PRNG OR $C0 jump timer; new match |
| MoveHammerBroXDir | $CA58 | Frame bit $40 selects shimmy speed before distance child; new match |
| Shimmy | $CA62 | Distance child input and page-sign facing decision; new match |
| SetShim | $CA75 | Post-distance interval timer, facing write and normal tail; new match |
| MoveNormalEnemy | $CA77 | Retained state priority and normal/defeated shared entries; retained match |
| FallE | $CA98 | Vertical child followed by fresh state read; retained match |
| MEHor | $CAAF | State two horizontal direct tail; retained match |
| SlowM | $CAB2 | Falling non-power-up slow index; retained match |
| SteadM | $CAB4 | Saved input speed restored only on temporary-speed path; retained match |
| AddHS | $CABB | Sign index, source adder and exact horizontal child inputs; retained match |
| ReviveStunned | $CAC8 | Stunned timer zero/nonzero and state reset; retained match |
| SetRSpd | $CADF | Frame parity and primary mode select revival speed; retained match |
| MoveDefeatedEnemy | $CAE5 | Shared vertical then horizontal tail, including mixed defeat bits; retained match |
| ChkKillGoomba | $CAEB | Timer $0E and Goomba tests; actual erasure child; retained match |
| NKGmba | $CAF8 | Source return reached with no extra stores; retained match |

The source audit binds twelve bytes in four tables and executes all 138
instructions in $C9D8-$CA0F and $CA12-$CAF8. Both outcomes of every feasible
conditional branch occur. The only untaken side is $CAAD BNE: its preceding
BEQ already handles equality without changing flags, so fallthrough there
is structurally impossible. This is an explicit source proof, not a masked
coverage gap. Both scoped entry families reach their original successors.

Original caller diagnostics and real shared-child execution each pass
712/712 across x86/x64. Full RAM is compared, including scratch and mapped
$0109-$0139; only hardware-stack bytes are excluded. Recorded child returns
are used only after their complete original input comparison. Spawn carry
and distance A/sign returns are explicit observer ABI, and ordinary/defeated
movement remains real C inside the caller proof. All 356 independently
observed/unobserved frame pairs agree; this proves observer noninterference,
not full-game native graphics/audio conformance.

Route scope is explicit: 316 cases are ordinary NMI fixture routes. Forty
use controlled input RAM at a naturally reached entry: cases 256..287 set
Hammer Bro state/jump timer/Y/secondary mode/two PRNG bytes before $C9D8;
cases 300..307 set primary mode/interval timer and one Koopa ID before
$CA77. Graphics/background phases otherwise replace these branch inputs
before observation. Inputs apply identically without observers; original
ROM bytes, PC, registers, hardware stack and output state are never patched.
The four final power-up speed-exemption cases use the original ShroomM route.
No controlled-case result is represented as an unmodified end-to-end game.

The actor body moves from objects.c to enemy/hammer_bro.c; source flag/ID
and master-timer gates are removed, with eligibility retained only by the
legacy bulk caller. Throw success sets the current state bit and skips the
decrement; failure decrements the current timer. Secondary hard mode replaces
the wrong primary flag. The jump selection preserves scratch and both PRNG
reads. MoveDefeatedEnemy now has one shared entry, preserving vertical then
horizontal movement even when the defeat bit coexists with other state bits.
Normal movement remains the existing owner and source state-priority logic.

enemy/distance.c exposes the source dependency boundary: low subtraction
in $00 and wrapped page subtraction returned as A. It replaces the actor's
unsigned world comparison. That child remains separately uncredited. Other
legacy inline distance consumers are not silently migrated or certified by
this task; their existing ownership remains. No host adapter was changed.

Native tests pass per width: 12,288 mutated-spawn/distance caller cases plus
12,288 defeated-tail cases; the existing Hammer Bro integration test; 9,984
hammer child contracts; and 1,253,376 normal movement cases spanning all
six slots, all speeds, state priority, timer, hard mode and power-up aliases.
Fifteen earlier full native suites and normal/vector/retainer/cannon contracts
also pass. The integrated original-snapshot matrix is 4,094/4,882, preserving
all 3,382 previous passing comparisons. The existing 788 differences retain
their source-order owners. Known Bowser damage and endgame star-timer failures
remain unchanged; no general playability or full-ROM completion is claimed.

All 91 shared units build with strict C90 on both native widths. Self-tests,
hidden-window response and platform purity pass. DOS16 links with the old
OLDNAMES warning and remains link-only; no DOS graphics/resource binding or
physical 486 performance claim is made. Three EXEs are refreshed together.

Similar-issue sweep checks every Hammer Bro source/bulk caller, primary and
secondary difficulty use, jump PRNG addresses, throw carry consumer, defeat
entry and normal-motion alias. One source actor and one normal/defeated
movement owner remain. Hammer terrain and graphics are unchanged. The
distance seam is visible and uncredited rather than hidden inside the actor.

Reproduce hammer_movement_fixture.h cases 0..355 with
--fixture=t40-hammer-movement=N, --hammer-movement-snapshot,
--control-children and an independent --pc-coverage run.
hammer_movement_snapshot_check links real actor/movement with explicit child
diagnostics; enemy_loop_actual_check uses real children. Focused targets are
mysmb.hammer-movement-caller and mysmb.normal-enemy-movement. An initial
incorrect gravity observer address was corrected to $BFAD before evidence
acceptance; affected records were regenerated, without a production patch.
The local checkpoint/coverage audit records exact inputs and branch hits.
Source provenance is unchanged; artifacts remain owner-local inputs/outputs.

Final raw records occupy 6,766,928 bytes with 910 child handoffs, below the
16-MB declared budget in ignored build/m2-t40-s2; each run has a twenty-
second timeout and unique checkpoint/output paths. Superseded diagnostic
raw records are removed after acceptance. Current records remain inputs for
dependent admitted regressions.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256337 | 3a6eb3f128033be4f54084730fb6a134d3cb5b2d8e9b1e8cbbabec8fa6d55f20 |
| mysmb32.exe | 344558 | fcccb5a530645e07ec7bb9f93e336517721ecba20f4252eee4dc96e7a086f327 |
| mysmb64.exe | 351809 | 3013f8bf34fe1dfe35a62528258c4045b4701b904f1665e2aca17b4e5a69c2ea |

## S3 admission: Jumping and red Paratroopa movement

S2 closed in 7618120. Coordinator accepts transfer-187. Exact scope and
expected new set (all open): MoveJumpingEnemy, ProcMoveRedPTroopa, NoIncPT,
MoveRedPTUpOrDown and MovPTDwn. Baseline 1,072/1,992, maximum 1,077.
Source range $CAF9-$CB24 follows the normal/defeated tail; S4 begins at
MoveFlyGreenPTroopa. Owners are enemy/movement.c and enemy/paratroopa.c.

Preserve the jumping gravity-then-horizontal chain. Red movement must clear
Enemy_YMF_Dummy whenever speed OR force is zero, before comparing current
Y with the original anchor. Below the anchor it advances Y only every eight
frames and returns; otherwise compare central Y and select the existing
up/down gravity entries. Restore source entries without extra flag/ID guards;
keep bulk eligibility at the legacy boundary and remove redundant jumping
forwarders when all source callers already use the shared movement owner.
Do not change the proven gravity or horizontal algorithms.

Logic proof covers speed/force combinations, fractional sentinel, equal and
adjacent anchor/center values, all eight frame phases, both directions and
actual shared children. Use original NMI routes; explicitly identify any
controlled RAM inputs at naturally reached entries needed for narrow branch
coverage. CPU, PC, stack and ROM remain untouched. Source branch/read/write
and original child-input/order evidence remain separate from native tests.

Operational proof covers all six slots, no extra eligibility gate, ordinary
and mutating child contracts, prior original matches, strict C90 x86/x64,
DOS16 link, platform purity, hidden-window response and three EXEs. Each of
the five nodes must have exact evidence and disposition before closure.
Similar-issue sweep covers jumping/red source callers, bulk wrappers, RAM
aliases and the order of fractional reset versus anchor/center comparisons.
No green flying actor or host gameplay belongs to this S.

Existing owner-local ROM/listing provenance and redistribution limits remain;
no third-party code import. All research, trace, build and log outputs stay in
ignored build/m2-t40-s3. Begin with 160 original routes, eight-MB raw budget,
twenty-second per-run timeout, unique outputs and resumable checkpoints.
Actual failed child routes may not be hidden by caller-only proof.

## S3 original jumping and red Paratroopa proof

S3 P1 closes all five expected nodes: 1,072 -> 1,077/1,992. No scoped
unfinished node or transfer remains; S4 is next in the existing plan.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| MoveJumpingEnemy | $CAF9 | Existing shared gravity-then-horizontal child order and real child execution; new ROM match |
| ProcMoveRedPTroopa | $CAFF | Zero combined speed/force clears the fractional accumulator before anchor comparison; new ROM match |
| NoIncPT | $CB18 | All eight frame phases: increment only phase zero, then source return; new ROM match |
| MoveRedPTUpOrDown | $CB19 | Current versus central Y selects the source up/down gravity entries; new ROM match |
| MovPTDwn | $CB22 | Below-center branch reaches the real downward red-gravity child; new ROM match |

Original NMI routes cover jumping movement and red Paratroopa speed/force,
anchor equality/adjacency, center selection, both edge slots and all eight
slow-step frame phases. All scoped instructions and both outcomes of each
branch execute. No mid-entry input injection is used for this S. ROM, CPU,
hardware stack and output state remain unchanged. Caller diagnostics and
real shared-child execution independently pass 320/320 across x86/x64.
Caller records compare full child-entry RAM before substituting recorded
returns. Actual runs execute the real gravity/horizontal children. Hardware
stack bytes alone are excluded; scratch and mapped $0109-$0139 are compared.
All 160 observer-free frames equal their observed records; that check proves
observer noninterference, not full-game native frame conformance.

The source defect was the ordering of the fractional reset: zero vertical
speed/force must clear $0417+slot even at or above the original-height anchor.
The former implementation only cleared it below that anchor, incorrectly
carrying a fractional remainder into gravity on the other path. The shared
enemy/paratroopa.c owner now follows the original sequence. Its entry has
no extra eligibility guard; legacy bulk callers retain their own filters.
The unused jumping slot wrapper is removed, and both normal-vector and
legacy bulk callers reach the existing MoveJumpingEnemy owner directly.
The star/power-up consumer continues using that same shared owner.

Independent native contracts pass 10,368 full-RAM cases per width across
six slots, eight phases, four speed/force combinations, adjacent Y/anchor/
center values and zero/nonzero fractional sentinels. Deliberately unrelated
flag/ID bytes ensure the source entry has no extra gate. Child mutation is
preserved. Existing Paratroopa integration and normal-movement tests pass,
as do fifteen earlier full native suites and prior caller contracts.

The final original-snapshot matrix is 4,414/5,202; all 4,094 previously
passing comparisons remain passing. Unfinished graphics/collision and other
child differences retain their source-order owners. Existing Bowser damage
and endgame star-timer failures remain unchanged.

All 92 shared units compile in strict C90 for x86/x64, and both self-tests
and hidden-window response probes pass. Platform purity passes. DOS16 links
with the old OLDNAMES warning and remains link-only: no graphics/resource-
binding or physical 486 performance claim. The three EXEs are refreshed.

Similar-issue sweep covers all red/jumping declarations, normal-vector and
bulk callers, the star consumer, alias addresses $0401/$0058 and reset order.
No duplicate movement algorithm or host gameplay was introduced. The green
flying actor remains S4's obligation; no child node receives extra credit.

Reproduce paratroopa_movement_fixture.h cases 0..159 with
--fixture=t40-paratroopa=N, --paratroopa-snapshot, --control-children and a
separate --pc-coverage run. paratroopa_movement_snapshot_check links real
movement callers with explicit child boundaries; enemy_loop_actual_check
executes real children. The native target is mysmb.paratroopa-movement.
Exact source coverage and child ordering are recorded in local
source-audit.json. Owner-local provenance and redistribution limits remain.

The 19 scoped instructions and 160 child handoffs use 2,020,960 raw bytes under
the eight-MB budget in ignored build/m2-t40-s3. Each record uses a unique
path, stable checkpoint and twenty-second timeout. Current records remain
local regression inputs for dependent admitted chains.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256273 | 5a97ff191aaf7e721446ad3dcbb8029a6b98a65ca48edcce59382f0cbc196213 |
| mysmb32.exe | 344693 | 9810abe209c2cdb0f70606c5e85b2d0990ad6d9c62462920cd260e01bb9be628 |
| mysmb64.exe | 352493 | da272948b484a2b8c6a45f10084ac113f7972768dc6601ef3b396b1c0910c18a |

## S4 admission: Green Paratroopa and shared X counters

S3 closed in 5d2a330. Coordinator accepts transfer-188. All ten labels in
the S4 plan row are open and expected new: MoveFlyGreenPTroopa, YSway, NoMGPT, XMoveCntr_GreenPTroopa, XMoveCntr_Platform, NoIncXM, IncPXM, DecSeXM, MoveWithXMCntrs, XMRight.
Baseline 1,077/1,992, maximum 1,087. Source $CB25-$CB86 follows the red
Paratroopa chain and ends before BlooberBitmasks. Shared owners are
enemy/paratroopa.c and enemy/x_counter.c with an explicit shared header.

Restore the source calls XMoveCntr_GreenPTroopa -> XMoveCntr_Platform and
MoveWithXMCntrs. The green entry supplies $13; the shared platform entry
stores its input maximum in $01 even when frame phase skips the counter
update. Preserve exact equality tests, byte overflow, primary bits zero/one,
secondary increment/decrement, temporary two's complement, direction and
the saved counter across the horizontal child. Store its returned A in $00.
Then read the current frame again: only every fourth frame writes +/-1 to
$00 and adds it to Y, without changing Y-high. The source entry has no
extra flag/ID gate; bulk eligibility remains at its legacy boundary.

Logic proof binds all ten labels to original branches, RAM writes and child
order. Exercise zero/equal/adjacent/wrapped counters, phase bits, direction,
Y wrap and actual horizontal children. Use original NMI routes plus explicit
controlled RAM input at a naturally reached entry only if needed; never
patch ROM, registers, PC, stack or outputs. Platform-specific maximum values
may be tested through the shared entry, without claiming platform actor
callers or child algorithms complete. Those callers keep their later owners.

Native contracts cover every byte of the counters/maximum where useful,
full RAM footprints, mutated child returns and frame/state changes. Preserve
prior original matches, strict C90 x86/x64 and DOS16 link; run platform purity,
hidden-window response and refresh all three EXEs. Scope closes only when
exact node dispositions, both verification tracks, ledger/tracker and
artifacts agree. S5 Bloober movement remains next in source order.

Similar-issue sweep covers the old green inline algorithm, source/bulk
callers, shared counter aliases and future platform entry seams. No host
gameplay or unrelated platform actor repair is admitted. Existing owner-local
ROM/listing provenance is unchanged; no third-party import. Temporary inputs,
records, logs and builds stay in ignored build/m2-t40-s4. Begin with 256
original routes, twelve-MB raw budget, twenty-second timeout per run, unique
paths and stable checkpoints. Child failures remain visible separately.

## S4 original green Paratroopa and counter proof

S4 P1 closes all ten expected nodes: 1,077 -> 1,087/1,992. No scoped
unfinished node or transfer remains; S5 is next in the existing plan.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| MoveFlyGreenPTroopa | $CB25 | Calls counter then horizontal movement and reads post-child frame state; new ROM match |
| YSway | $CB3B | Writes plus/minus one to scratch and wraps Y as one byte; new ROM match |
| NoMGPT | $CB44 | Skipped phase preserves horizontal displacement in scratch; new ROM match |
| XMoveCntr_GreenPTroopa | $CB45 | Presets maximum $13 before the shared counter entry; new ROM match |
| XMoveCntr_Platform | $CB47 | Stores incoming maximum even on skipped phases; original platform caller supplies $0E; new ROM match |
| NoIncXM | $CB5C | Off-phase counter return leaves primary and secondary unchanged; new ROM match |
| IncPXM | $CB5D | Exact maximum or zero endpoint increments primary with byte wrap; new ROM match |
| DecSeXM | $CB60 | Odd primary decrements nonzero secondary and reverses at zero; new ROM match |
| MoveWithXMCntrs | $CB66 | Saves secondary across signed horizontal movement and restores it; new ROM match |
| XMRight | $CB7C | Writes facing, calls horizontal child, stores returned A before restoration; new ROM match |

Original NMI routes exercise 256 green-actor cases plus 32 real platform
caller cases at the shared counter entry. All 53 scoped instructions and
both outcomes of all seven branches execute. Green supplies maximum $13;
the platform caller supplies $0E. No mid-entry RAM injection, ROM patch,
register/PC/stack patch or output patch is used. Caller diagnostics and
actual shared-child execution each pass 576/576 across x86/x64. Child-entry
RAM is compared before recorded returns are substituted in diagnostics;
actual runs execute the real horizontal child. Only hardware stack bytes
are excluded; scratch and mapped $0109-$0139 remain compared. All 288
observer-free frames equal observed records. This is observer noninterference,
not a whole-game native frame-conformance claim. Platform actor callers and
horizontal child nodes receive no additional credit.

The old green inline algorithm is replaced by source-ordered calls into
shared enemy/green_paratroopa.c and enemy/x_counter.c. A separate green
owner keeps the existing red-Paratroopa standalone tests independent.
Exact equality replaces the old saturating approximation; byte wrap,
maximum scratch, saved secondary counter, horizontal returned A and
post-child frame/Y behavior follow the source. The actor entry has no
extra eligibility guard; the legacy bulk boundary retains flag/ID filtering.

Independent native contracts pass 196,608 counter cases and 24,576
child-mutation/actor cases per width. They cover all maximum bytes, all
secondary bytes across movement cases, six slots, primary wrap, signed
movement, phase/Y wrap and restoration after a child changes RAM. Retained
Paratroopa/platform and earlier native contracts pass. The final original
snapshot matrix is 4,990/5,778, preserving all 4,414 prior matches. Existing
788 downstream differences retain their source-order owners; Bowser damage
and endgame star-timer failures remain unchanged.

All 94 shared units compile in strict C90 for x86/x64. Both executable
self-tests and hidden-window response probes pass. Platform purity passes.
DOS16 initially hit LINK L1049 as the shared source count grew. Local LINK
5.60 help confirms /SEGMENTS support; adding /SEGMENTS:1024 increases the
linker's table capacity without changing /AL or game behavior. The complete
modified DOS build then links successfully, retaining the existing OLDNAMES
warning. DOS remains link-only; no graphical playability, resource binding
or physical 486 performance claim is made. All three EXEs are refreshed.

Similar-issue sweep covers the old green inline body, source and bulk
callers, primary/secondary aliases and shared platform seams. The green
source path has one implementation; later platform actor approximations
remain their existing obligations. No platform gameplay code was added.

Reproduce green_counter_fixture.h cases 0..287 with
--fixture=t40-green-counter=N, --green-counter-snapshot, --control-children
and separate --pc-coverage. green_counter_snapshot_check compares caller
boundaries; enemy_loop_actual_check executes shared children. The native
CTest is mysmb.green-paratroopa-counters. Local source-audit.json records
instruction/branch coverage and child ordering. There are 256 child records
and 3,506,592 raw bytes below the twelve-MB budget in ignored
build/m2-t40-s4. Each record has a unique path, stable checkpoint and
twenty-second timeout. The coordinator retains these local regression
inputs for dependent admitted chains. Existing owner-local provenance and
redistribution limits remain; no new third-party import occurred.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256513 | 005cb1b17c4aef467551a017a2f0b60abeae3aedaa9889e682f86155b6550f73 |
| mysmb32.exe | 345328 | cfdb77d1c8409cd9d8920acbe0ba8dc60b6e2e66cb166e1c44150be2a06e77a0 |
| mysmb64.exe | 353197 | f3297ce2b5fa60d4071558b2359c333c855c200507d0b0604b365e861ba07e50 |

## S5 admission: Bloober movement and swimming

S4 closed in 17c144f. Coordinator accepts transfer-189. All sixteen labels
are open and expected new: BlooberBitmasks, MoveBloober, FBLeft, SBMDir, BlooberSwim, SwimX, LeftSwim, MoveDefeatedBloober, ProcSwimmingB, BSwimE, SlowSwim, NoSSw, ChkForFloatdown, Floatdown, NoFD, ChkNearPlayer.
Baseline 1,087/1,992, maximum 1,103. The contiguous source chain starts at
BlooberBitmasks ($CB87), includes MoveBloober and ProcSwimmingB, and ends
before MoveBulletBill. Shared owner is enemy/bloober.c. Legacy bulk callers
retain eligibility filtering; the source actor entry has no extra gate.

Preserve defeated movement, PRNG/hard-mode mask data, odd-slot player
moving direction and even-slot PlayerEnemyDiff, scratch and sign semantics.
Keep the original swim counter/force/speed aliases, eight-frame acceleration
and deceleration, exact endpoint equality, two-tick float timer and continued
float-down after timer expiry while below the player threshold. ChkNearPlayer
uses inherited carry in its ADC: trace that carry through the original
JumpEngine and direction paths instead of assuming Y+16. Vertical movement
subtracts modulo 256 before the $20 comparison. Horizontal movement preserves
page carry/borrow. Existing distance and slow-gravity children are dependencies;
this S neither repairs nor credits their nodes.

Logic proof first maps each label, branch, RAM read/write and call edge, then
compares unchanged original NMI actor routes and actual native children.
Exercise both masks, slot parities, signed/page differences, all swim phases,
counter/force byte wrap, threshold adjacency, expired/nonexpired timer and
defeated tail. Explicit controlled RAM inputs at naturally reached entries
are allowed only if ordinary routes miss a branch; never patch ROM, CPU,
PC, hardware stack or outputs. Child substitutions are diagnostic only,
following complete input comparison; actual child failures remain visible.

The independent operational track uses native full-RAM contracts, retained
original matches, strict C90 x86/x64 builds, DOS16 link, platform purity,
hidden-window response and three refreshed EXEs. Each label receives an
individual disposition. No unmatched node is silently closed. S6 Bullet
Bill remains next. Similar-issue sweep covers the inline/bulk/source Bloober
routes, direction carry, counter/force aliases and float-down fallback.

Existing owner-local ROM/listing provenance and redistribution limits remain;
there is no third-party import. Temporary scripts, research, traces and builds
stay in ignored build/m2-t40-s5. Start with up to 512 original input routes,
a sixteen-MB raw budget, twenty-second per-run timeout, unique output paths
and stable checkpoints. The coordinator owns trace retention/cleanup after
dependent admitted regressions no longer require these local inputs.

### S5 implementation checkpoint (not closure)

The shared Bloober owner has replaced the old inline actor. Eligibility
checks remain at the legacy bulk boundary. Source review identified missing
float-down after timer expiry, an extra pre-subtraction Y-underflow guard,
unsigned world comparison instead of PlayerEnemyDiff's page-result sign,
and lost carry at ChkNearPlayer. The implementation now follows these source
paths. JumpEngine's ASL of ID seven establishes initial carry zero; odd-slot
direction selection establishes carry one; even slots obtain the final
subtraction carry from the page operands and low-byte borrow. The source
distance child remains the scratch/result owner and receives no node credit.

Ten explicit full-RAM boundary contracts pass in strict C90 on x86/x64,
including timer-expired drift, inherited-carry threshold, signed page result,
vertical underflow, horizontal page wrap and the defeated child. These are
native contracts only. Original-ROM route/branch coverage, final regressions,
DOS link and delivery are still pending. No S5 label is promoted and no P
commit or executable refresh is claimed at this checkpoint.

## S5 original Bloober swimming proof

S5 P1 closes all sixteen expected nodes: 1,087 -> 1,103/1,992. No scoped
unfinished node or transfer remains; S6 is next in the existing plan.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| BlooberBitmasks | $CB87 | Original two-byte masks bound to both hard-mode consumer paths; new ROM match |
| MoveBloober | $CB89 | Defeat gate and random-mask direction selection match original; new ROM match |
| FBLeft | $CBA2 | Even-slot distance child preserves scratch and page-result sign; new ROM match |
| SBMDir | $CBAA | Odd/even direction stores and inherited carry preserved; new ROM match |
| BlooberSwim | $CBAC | Swim child precedes modulo-byte Y subtraction and status-bar comparison; new ROM match |
| SwimX | $CBBB | Direction selects horizontal add or subtract with page carry; new ROM match |
| LeftSwim | $CBCE | Left movement preserves byte subtraction and page borrow; new ROM match |
| MoveDefeatedBloober | $CBDC | Defeated tail executes the real slow vertical child; new ROM match |
| ProcSwimmingB | $CBDF | Counter phase selects float, acceleration or deceleration; new ROM match |
| BSwimE | $CC03 | Acceleration phase skips or returns after exact force-two endpoint; new ROM match |
| SlowSwim | $CC04 | Deceleration writes force/speed and exact-zero counter/timer changes; new ROM match |
| NoSSw | $CC1B | Deceleration skipped phase and nonzero force return preserve state; new ROM match |
| ChkForFloatdown | $CC1C | Timer zero reaches player comparison, nonzero reaches float-down; new ROM match |
| Floatdown | $CC21 | Even frame increments Y with byte wrap; new ROM match |
| NoFD | $CC28 | Odd frame skips float increment; new ROM match |
| ChkNearPlayer | $CC29 | Inherited ADC carry and wrapped threshold choose continued float or reset; new ROM match |

The 512 unchanged original NMI routes cover both hard-mode masks, both edge
slots/parities, PRNG direction gates, distance sign, swimming counter phases,
force byte endpoints/wrap, expired/nonexpired timers and defeated movement.
All 90 instructions and fifteen conditional branches execute on both paths.
The sixteenth branch at $CBA0 is structurally unconditional: the preceding
BCC only falls through with carry set, and LDY preserves carry before BCS.
No impossible fallthrough is claimed as exercised. Both original table bytes
are checked and each hard-mode consumer occurs in 256 entry snapshots.

Caller-boundary and actual-child runs each pass 1,024/1,024 across x86/x64.
There are 120 recorded PlayerEnemyDiff calls and 32 defeated slow-gravity
calls. Caller diagnostics compare child-entry RAM before substituting original
returns; actual runs execute the existing shared children. All RAM including
scratch and mapped $0109-$0139 is checked except the hardware stack. No ROM,
CPU/register, PC, stack or output patch or mid-entry RAM injection is used.
512 observer-free frame records equal the observed originals. This proves
observer noninterference, not full-game native frame conformance. No distance,
gravity or caller node receives incidental completion credit.

Source review and implementation remove the old unsigned direction comparison,
extra actor eligibility gate, missing expired-timer float-down path and extra
Y-underflow rejection. The shared enemy/bloober.c owner preserves the original
call order and byte operations. Initial carry is zero from JumpEngine's ASL
of ID seven. An odd slot establishes carry one; an even slot derives the
PlayerEnemyDiff final subtraction carry from its page operands and low-byte
borrow. The child owns its original scratch/result. ChkNearPlayer therefore
adds sixteen plus inherited carry before its wrapped-byte player comparison.
The original routes exercise this threshold with carry zero in 80 snapshots
and carry one in 48. Source entry has no extra flag/ID guard; only the legacy
bulk boundary keeps those eligibility checks.

Independent full-RAM native contracts cover ten explicit boundary cases per
width, including signed page-result direction, inherited-carry threshold,
continued float-down, vertical underflow, force endpoint/wrap, page carry/
borrow and defeated child writes. Prior native contracts and focused suites
pass. The combined final original-snapshot matrix is 6,016/6,802. All 4,990
previous matches remain; two existing comparisons improve with this actor
repair. The 786 remaining downstream differences retain their original
source-order owners. Existing Bowser damage and endgame star-timer failures
remain explicit and unchanged.

All 95 shared units compile in strict C90 on x86/x64; executable self-tests
and hidden-window response probes pass. DOS16 links using the existing large
model and segment capacity, retaining the OLDNAMES warning. Platform purity
passes. DOS remains link-only; graphical playability, resource binding and
physical 486 performance are not established. Three test EXEs are refreshed.

Similar-issue sweep covers source/bulk/vector Bloober callers, direction and
carry, force/counter byte aliases, timer/player fallthrough and vertical
subtraction order. The old actor body is removed from objects.c; the shared
owner is present in both manifests. No game logic enters host adapters.

Reproduce bloober_movement_fixture.h cases 0..511 using --fixture=t40-bloober=N,
--bloober-snapshot, --control-children and a separate --pc-coverage run.
bloober_movement_snapshot_check diagnoses caller boundaries;
enemy_loop_actual_check executes actual children. The native CTest is
mysmb.bloober-movement. Source-audit and input-audit scripts remain local.
Initial input phases missed acceleration/deceleration after NMI increment;
those records are retained separately, and corrected ordinary input phases
cover both paths without changing execution. Each set uses 4,991,792 raw
bytes, together below the sixteen-MB budget, under ignored build/m2-t40-s5.
Unique paths, twenty-second timeouts and stable checkpoints bound each run.
The coordinator retains these local inputs for dependent regressions.
Existing owner-ROM/listing provenance and redistribution limits remain.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256371 | bba6308aa8a52daf41f73464a15da74036b107162d5c79ceffe7bc823e13d410 |
| mysmb32.exe | 345634 | c962aa591fe08b19840f24842b70672cb2faff18a8f33075d8a700b27f6c33ee |
| mysmb64.exe | 353539 | 5790311c229b49514b0149ab0e58df054d6c171fe8e2d71a38379c7aa7fbfa25 |

## S6 admission: Bullet Bill movement

S5 closed in 4155d2a. Coordinator accepts transfer-190. Both scoped labels,
MoveBulletBill and NotDefB, are open and expected new. Baseline 1,103/1,992;
maximum 1,105. Source $CC36-$CC45 follows Bloober and ends before
SwimCCXMoveData. Shared owner is enemy/bullet_bill.c; the legacy bulk boundary
retains eligibility filtering. Existing horizontal and jumping-gravity
children are dependencies, not newly certified nodes.

The original actor tests state bit $20. Defeated movement tail-calls
MoveJ_EnemyVertically; otherwise it writes fixed speed $E8 and tail-calls
MoveEnemyHorizontally. The earlier plan's timer-gate wording was inaccurate:
the source actor has no timer, player-facing or other-state gate. Remove
those extra semantics from this entry. Preserve caller-controlled timing,
original child inputs/order and scratch/byte effects. Do not modify cannon
actors, collision, drawing or gravity/horizontal algorithms.

Logic proof maps both labels and their branch, store and tail calls against
unchanged original NMI routes, covering state bits, slots, page/fraction
boundaries and real children. Diagnostic substitution follows full child-input
comparison; actual-child differences remain separately reported. Native
contracts exhaust state bytes and check exact child selection, speed and
write footprints, including unrelated eligibility/timer values. Preserve
prior original matches; run strict C90 x86/x64 builds, DOS16 link, platform
purity, window probes and refresh all three EXEs once for the chain.

Similar-issue sweep covers the inline actor, movement vector, legacy bulk
caller and Bullet Bill tests. Repair tests that asserted the removed
non-ROM player-facing rule, with explicit source rationale. S7 swimming
Cheep-Cheep remains next. No host gameplay or unadmitted child repair.
Existing owner-local ROM/listing provenance and redistribution limits remain;
no third-party import. Use ignored build/m2-t40-s6 for all outputs, up to
128 original routes, eight-MB raw budget, twenty-second per-run timeout,
unique paths and stable checkpoints. The coordinator owns trace retention
and cleanup after dependent regressions no longer need these local inputs.

## S6 original Bullet Bill movement proof

S6 P1 closes both expected nodes: 1,103 -> 1,105/1,992. No scoped
unfinished node or transfer remains; S7 is next in the existing plan.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| MoveBulletBill | $CC36 | State bit $20 selects the original jumping-gravity tail with unchanged input; new ROM match |
| NotDefB | $CC3F | All other states store fixed $E8 speed before the real horizontal tail; new ROM match |

All seven original instructions and both outcomes of the state-bit branch
execute in 128 unchanged original NMI routes. The two tail destinations
are $BF92 MoveJ_EnemyVertically and $BF02 MoveEnemyHorizontally, each observed
64 times. Caller-boundary and actual-child comparisons independently pass
256/256 across x86/x64. The original entry, store and tail-call order are
preserved; no source child receives additional completion credit.

Caller diagnostics compare full child-entry RAM before substituting recorded
returns. Actual runs execute the existing shared horizontal/gravity code.
Hardware stack bytes alone are excluded; scratch and mapped $0109-$0139
remain checked. All 128 observer-free frames equal observed records, proving
observer noninterference rather than full-game native frame conformance.
No mid-entry RAM, ROM, CPU/register, PC, stack or output patch is used.
The first diagnostic observer used the inner gravity boundary $BFAD instead
of the immediate child $BF92; actual-child results already passed. Correcting
the observer to the original symbol boundary resolves its scratch-input
mismatch without changing production code. Initial records remain separate.

The shared enemy/bullet_bill.c owner removes the old player-facing speed,
state/frame-timer initialization and timer/state-zero gates. The original
non-defeated path always stores $E8, even when other state bits are set.
Defeated movement uses the original jumping-gravity child, whose force is
$1C, replacing the old $3D helper selection. Source entry has no extra flag
or ID check; those filters remain only at the legacy bulk boundary. Native
contracts exhaust all 256 state bytes, six slots and two unrelated gate
values (3,072 full-RAM cases per width), including exact single child choice,
child mutation retention and the unchanged facing/state/timer footprint.

The existing Bullet Bill integration smoke passes on both widths after
replacing its old gravity amount and pre-movement sprite-X expectations with
source-derived values. The core smoke's Bullet Bill assertions now expect
fixed left speed and preserved state/facing/frame timer. Its earlier player
entrance failure is unchanged against the S5 object baseline; it is not
claimed passing. Existing Bowser damage and endgame star-timer failures also
retain their previous owners. Earlier focused native contracts pass.

All 96 shared units compile in strict C90 for x86/x64; self-tests and hidden
window-response probes pass. DOS16 links with the existing OLDNAMES warning
and remains link-only: no graphical/resource-binding or physical 486 speed
claim. Platform purity passes and all three EXEs are refreshed.

Similar-issue sweep covers the old inline actor, original movement vector,
legacy bulk path, and the two tests that encoded obsolete movement behavior.
The old duplicate actor is removed and both manifests use the shared owner.
Cannon allocation, collision and graphics algorithms are unchanged. No host
adapter contains new gameplay logic.

Reproduce bullet_movement_fixture.h cases 0..127 with
--fixture=t40-bullet-movement=N, --bullet-movement-snapshot,
--control-children and a separate --pc-coverage run.
bullet_movement_snapshot_check diagnoses caller inputs and returns;
enemy_loop_actual_check executes real children. The native CTest is
mysmb.bullet-bill-movement. The final raw set uses 1,616,768 bytes; the initial
observer set is retained separately, together below the eight-MB budget in
ignored build/m2-t40-s6. Unique paths, twenty-second timeouts and checkpoints
bound each run. The coordinator retains local inputs for dependent regressions.
Existing owner-ROM/listing provenance and redistribution limits remain.

The final original-snapshot matrix is 6,276/7,058. All 6,016 prior matches
remain; 4 earlier comparisons improve. The remaining 782 downstream
differences retain their existing source-order owners.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255971 | f603e81307516cad0243be5d03547ad2ec2b2853fd006e4983f08d169c6f9611 |
| mysmb32.exe | 345850 | 893bf46e91ed59e54551a8688844e6dc030d9c1ff70b2042c52c0c3994de0711 |
| mysmb64.exe | 353791 | e23e6578e9f3205f8cc81daf678d1c72c3f48d766ea16c3b9f35389d29332089 |

## S7 admission: Swimming Cheep-Cheep movement

S6 closed in 6a10b72. Coordinator accepts transfer-191. All seven labels are
open and expected new: SwimCCXMoveData, MoveSwimmingCheepCheep, CCSwim, CCSwimUpwards, ChkSwimYPos, YPDiff, ExSwCC.
Baseline 1,105/1,992; maximum 1,112. Source $CC46-$CCC6 follows Bullet Bill
and ends before the firebar tables. Shared owner is enemy/swimming_cheep.c.
MoveEnemySlowVert remains the existing child dependency without new credit.

Preserve the four-byte SwimCCXMoveData binding, including the unused trailing
data, and ID-selected force subtraction with borrow through X/page. Store
the state AND $20 result in scratch $03 (zero on the swimming branch), and
scratch $02 first from the table, then $20 before the slot check. Slots zero
and one skip vertical movement. Other slots add/subtract $20 in the Y fraction,
carry/borrow through Y and Y-high, then take the sign of the wrapped difference
from original Y. Negative difference selects $10 (down), nonnegative selects
zero (up), changing the flag only when the magnitude is at least $0F.
The defeated branch calls the real slow-gravity child. Retain eligibility
filtering only at the legacy bulk boundary. Do not alter fish initializers,
child gravity, graphics, firebars or host adapters.

Logic proof maps each table, branch, RAM read/write and child edge first,
then compares unchanged original NMI routes and actual children. Exercise
both IDs, all slot classes, state bits, fractional carry/borrow, coordinate
wrap, both sign paths, and magnitude $0E/$0F/$10 plus signed extremes.
Controlled RAM input at a naturally reached entry is allowed only when a
branch cannot be reached through ordinary NMI inputs; no ROM, CPU, PC, stack
or output patch. Diagnostic child substitution requires full input comparison;
real-child differences remain visible. Native full-RAM contracts independently
check scratch, masked state, byte arithmetic and the turnaround rule.

Preserve prior original matches; run strict C90 x86/x64, DOS16 link, platform
purity, hidden-window probes and refresh three EXEs once for the chain.
Individual node proof and tracker/ledger updates are required at closure.
S8 firebar remains next. Similar-issue sweep covers the inline/source/vector/
bulk swimming-fish routes, scratch aliases, state masking and direction tests.
Existing owner-local ROM/listing provenance and redistribution limits remain;
no third-party import. All outputs stay below ignored build/m2-t40-s7, with
up to 512 original routes, sixteen-MB raw budget, twenty-second per-run timeout,
unique paths and stable checkpoints. The coordinator owns local trace retention
and cleanup once dependent admitted regressions no longer need the records.

### S7 implementation checkpoint (not closure)

The source actor now lives in shared enemy/swimming_cheep.c; the old inline
body is removed and both build manifests use the shared owner. The source
entry preserves masked-zero scratch $03 and $20 scratch $02 before its slot
gate, instead of applying the raw state byte to Y. Height comparison uses
the sign of byte subtraction and restores the original flag direction.
The legacy bulk boundary alone retains the ID/eligibility filter.

Eleven explicit full-RAM native boundary cases pass in strict C90 on x86/x64:
slot zero/one Y preservation, X fraction/page borrow, Y fraction/high wrap,
signed wrapped difference, exact magnitude threshold and defeated child.
These contracts do not establish ROM equivalence. Original-route instruction/
branch evidence, final regressions and three-target delivery remain pending;
no node promotion or P commit is claimed at this checkpoint.

## S7 original swimming Cheep-Cheep proof

S7 P1 closes all seven expected nodes: 1,105 -> 1,112/1,992. No scoped
unfinished node or transfer remains; S8 is next in the existing plan.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| SwimCCXMoveData | $CC46 | Four original table bytes bound; both used ID-selected forces exercised; new ROM match |
| MoveSwimmingCheepCheep | $CC4A | State bit $20 selects the original slow-gravity child without extra gates; new ROM match |
| CCSwim | $CC53 | Masked-zero scratch, table force subtraction and page borrow precede slot gate; new ROM match |
| CCSwimUpwards | $CC99 | Y fraction subtraction propagates borrow through Y and Y-high; new ROM match |
| ChkSwimYPos | $CCAC | Y-high stored before wrapped anchor difference sign and magnitude; new ROM match |
| YPDiff | $CCBF | Exact $0F threshold selects up zero or down $10 from original sign; new ROM match |
| ExSwCC | $CCC6 | First two slots and below-threshold paths retain the prescribed RAM footprint; new ROM match |

The 512 unchanged original NMI routes exercise both fish IDs (256 each),
slots zero, one, two and five (128 each), state-mask branches, X fractional
borrow, both Y fractional directions, wrapped height sign and the $0F
magnitude threshold. All 62 instructions and both outcomes of all five
conditional branches execute. The four bytes at SwimCCXMoveData match the
bound C table; the first two are consumed by IDs ten/eleven and the trailing
two remain explicitly unused source data. No extra algorithm is inferred.

Caller diagnostics and actual-child comparisons each pass 1,024/1,024 across
x86/x64. Sixty-four defeated cases reach the original $BF8C slow-gravity child;
other paths have no external child. Diagnostic substitution follows complete
child-input RAM comparison, while actual runs execute the shared gravity
implementation. Scratch and mapped $0109-$0139 remain checked; only hardware
stack bytes are excluded. No mid-entry input, ROM, CPU/register, PC, stack or
output patch is used. All 512 observer-free frames equal the observed records;
this proves observer noninterference, not full-game native frame conformance.
The gravity child receives no additional node-completion credit.

Shared enemy/swimming_cheep.c replaces the old inline actor. Its source entry
has no eligibility guard; legacy bulk filtering remains at that boundary.
The old implementation incorrectly added the raw state byte into vertical
movement and omitted the source scratch stores. The original non-defeated
path stores masked zero in $03 and ultimately $20 in $02, including slots
zero/one before returning. Fractional carry/borrow propagates through X/page
and Y/Y-high exactly. Height comparison uses the sign of wrapped subtraction,
not an unsigned ordering of the coordinates; negative difference chooses
$10 (down) and nonnegative chooses zero (up), only at magnitude >= $0F.
The old direction assignment was reversed. The original state/table/child
order now has one shared owner across all three targets.

Eleven explicit full-RAM native cases per width independently cover early
slot exit, X/page borrow, Y fraction/high wrap, raw state masking, exact
threshold, wrapped signed differences including $80, and defeated child
mutation. Earlier native contracts and focused suites pass. The combined
original-snapshot matrix is 7,308/8,082, preserving all 6,276 prior matches
and improving eight earlier comparisons. The remaining 774 downstream
comparison differences retain their original source-order owners. Existing
Bowser damage and endgame star-timer failures remain unchanged; the broad
core smoke's earlier player-entrance failure is not claimed resolved.

All 97 shared units compile in strict C90 for x86/x64, and both executable
self-tests and hidden-window response probes pass. DOS16 links with the
existing OLDNAMES warning and remains link-only; graphical playability,
resource binding and physical 486 performance are unproven. Platform purity
passes. All three test executables are refreshed.

Similar-issue sweep covers the former inline actor, movement vector and
legacy bulk route, force/dummy/anchor aliases, scratch writes and signed
turnaround. The existing core swim checks already describe the applicable
fractional movement and defeated child; they need no expectation change.
No duplicate movement owner or host gameplay is introduced.

Reproduce swimming_cheep_movement_fixture.h cases 0..511 using
--fixture=t40-swimming-cheep=N, --swimming-cheep-snapshot,
--control-children and a separate --pc-coverage run.
swimming_cheep_movement_snapshot_check diagnoses child boundaries;
enemy_loop_actual_check executes actual children. The native CTest is
mysmb.swimming-cheep-movement. Local source-audit.json records exact
instruction/branch and table-consumer evidence. Raw inputs use 4,631,168
bytes, below the sixteen-MB budget, under ignored build/m2-t40-s7.
Unique paths, twenty-second timeouts and checkpoints bound every run.
The coordinator retains local inputs for dependent admitted regressions.
Existing owner-ROM/listing provenance and redistribution limits remain.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 255767 | 57053dff2c7759dbdc0cf2fe43051c0ce33fa51899d1e092269d927022545e0c |
| mysmb32.exe | 346134 | 0368c97f6685376f4f9f505820e43c9b91f8daf6be161426c99c31470b9e92da |
| mysmb64.exe | 353598 | c427eea7cead73dcd1974c7f32483f9069760a47c640ce3401d1e4ad6e1e673f |

## S8 admission: Firebar position, drawing and collision

S7 closed in 524cf36. Coordinator accepts transfer-192. The 32 exact labels
below are all open and expected new; baseline 1,112/1,992, maximum 1,144.
Source $CCC7-$CED4 follows swimming Cheep-Cheep and ends before
PRandomSubtracter. This remains one bounded source chain in the approved
plan. Shared owners will be enemy/firebar.c and the game OAM boundary.
No platform adapter receives gameplay or coordinate logic.

### Original sequence and implementation boundary

ProcFirebar calls GetEnemyOffscreenBits before any spin, tests only bit $08,
then conditionally calls FirebarSpin using its returned high byte. Long bars
adjust phase $08/$18, save $EF, call RelativeEnemyPosition and retain the
apparently residual GetFirebarPosition call. RelativeEnemyPosition's source
return A is relative X, and its $00 write is the slot; do not silently omit
that boundary or substitute a phase value. Initialize the center sprite and
collide it before setting $ED to five/eleven and iterating the outer balls.
After outer index four, change OAM allocation through DuplicateObj_Offset.

DrawFirebar_Collision preserves byte sign/coordinate operations and the
non-wrapped absolute X separation threshold $59; Y=$F8 remains offscreen.
FirebarCollision first calls DrawFirebar, saves returned Y, and skips damage
on star/timer or player high-Y gates. Small/crouched Mario uses the +$18
probe; big standing Mario uses zero, +$0C and +$18. Differences use signed
byte subtraction/negation. Player X comes from sprite one X plus four,
not a world-coordinate approximation. Set Enemy_MovingDir for slot zero,
save/restore $00 across InjurePlayer, restore OAM offset plus four, and
continue drawing the chain after injury. Compatibility injury reporting
must not truncate the source loop or the already-proved RunFirebarObj tail.

GetFirebarPosition preserves its A input, triangular X/Y lookup, $00-based
table offset and $01/$02/$03 writes. The preliminary residual call can read
outside the named arrays due to relative-X input; audit the exact immutable
ROM data addresses rather than clamp, skip, invent a default, or allow C
array overflow. Such bounded table-data access is not instruction execution.
All executable program behavior remains native shared C.

External child nodes GetEnemyOffscreenBits, FirebarSpin,
RelativeEnemyPosition, DrawFirebar and InjurePlayer retain their existing
receivers/status. Add narrowly typed shared child entry seams only where
needed to expose original A/Y/scratch contracts; do not silently certify or
rewrite unrelated callers. Record each existing child discrepancy separately.
The later DrawFirebar node is distinct from the in-scope DrawFbar loop and
DrawFirebar_Collision. The current force-injury helper omits original injury
sound/palette behavior; its actual-child gap must not be hidden or patched
by the firebar caller. Similar scrutiny applies to relative-position scratch.

### Node checklist and proof targets

| Node | Original address | Required individual proof |
| --- | --- | --- |
| FirebarPosLookupTbl | $CCC7 | Bind all 99 lookup bytes and consumer indices; row eight currently has a copied value mismatch |
| FirebarMirrorData | $CD2A | Bind quadrant mirror values and exact indexed reads including residual-call addresses |
| FirebarTblOffsets | $CD2E | Bind all twelve offsets; retain source byte indexing and adjacency |
| FirebarYPos | $CD3A | Bind the two additional big-player vertical collision probes |
| ProcFirebar | $CD3C | Offscreen-before-spin, timer gate, original child order and center/outer iteration |
| SusFbar | $CD55 | Paused spin state is read without speed update |
| SkpFSte | $CD65 | Long-bar phases eight/twenty-four increment once |
| SetupGFB | $CD6A | Save phase, relative child return/scratch, residual lookup and center coordinates |
| SetMFbar | $CD96 | Store short/long maximum after center collision |
| DrawFbar | $CD9C | Lookup and collision/draw repeated in original sequence |
| NextFbar | $CDB2 | Increment index and compare to $ED after duplicate-OAM switch |
| SkipFBar | $CDBA | Offscreen branch returns before motion or drawing |
| DrawFirebar_Collision | $CDBB | Preserve mirror scratch and coordinate-to-OAM order |
| AddHA | $CDCB | Horizontal signed adder plus relative X with byte wrap |
| SubtR1 | $CDE2 | Unsigned ordering selects non-wrapped absolute horizontal distance |
| ChkFOfs | $CDE6 | $59 distance gate hides Y while preserving sprite X |
| VAHandl | $CDEE | Anchor Y $F8 short-circuits vertical mirror handling |
| AddVA | $CDFF | Vertical signed adder plus relative Y with byte wrap |
| SetVFbr | $CE03 | Store OAM Y and scratch $07 before collision entry |
| FirebarCollision | $CE08 | Draw child first, saved Y and star/timer/high-Y gates |
| AdjSm | $CE28 | Small or crouching probe counter two and Y plus $18 |
| BigJp | $CE31 | Preserve big standing initial Y probe |
| FBCLoop | $CE32 | Signed byte vertical difference and absolute magnitude |
| ChkVFBD | $CE3C | Vertical eight-pixel and far-right X gates |
| ChkFBCl | $CE58 | Player sprite-one X plus four and signed horizontal threshold |
| Chk2Ofs | $CE5C | Advance big-player probe table or exit at counter two |
| ChgSDir | $CE6F | Choose injury direction from modded sprite X comparison |
| SetSDir | $CE78 | Slot-zero direction, injury child, saved $00 and resumed source loop |
| NoColFB | $CE85 | Saved OAM offset plus four and ObjectOffset restoration |
| GetFirebarPosition | $CE8E | Preserve caller A through both triangular lookups and mirror selection |
| GetHAdder | $CE9A | Horizontal oscillation plus original per-ball table index |
| GetVAdder | $CEBA | Vertical oscillation plus original per-ball table index and mirror output |

### Verification and containment

First migrate this mapped chain, then use unchanged original NMI routes
with both bar lengths, all phases, spin directions/speeds, paused state,
edge coordinates, duplicate OAM, player sizes/crouching/probes, star/timer
and damage outcomes. Observe child inputs before any diagnostic substitution;
run actual children separately and retain every difference under its owner.
Controlled RAM inputs at naturally reached entries are allowed when ordinary
routes miss a source branch; no ROM, CPU/register, PC, stack or output patch.
No claimed closure is based on visible resemblance or native tests alone.

Independent native contracts cover exact RAM/OAM footprints, modulo and
non-modulo distinctions, child order/mutations, saved loop/OAM state and
continued processing after injury. Reuse earlier passing original matches;
run strict C90 x86/x64, DOS16 link, platform purity, hidden-window probes and
three-EXE refresh once for this chain. Report every scoped disposition.
Only source-proved caller/table nodes may be credited; actual child gaps
remain explicit. Unfinished scoped nodes require accepted named transfer.
S9 flying Cheep-Cheep remains next, without any invented task number.

Similar-issue sweep covers objects.c, firebar OAM helper, special caller,
source child seams, initializers and firebar tests. Existing owner-local
ROM/listing provenance and redistribution limits remain; no third-party
import. All investigation, generated data and traces remain below ignored
build/m2-t40-s8. Start with at most 512 original routes and a 64-MB raw budget
because each frame can contain twelve repeated collision/draw calls. Use
unique output paths, twenty-second per-run timeout, checkpoints and a bounded
child-record count verified against the chain. The coordinator retains local
inputs for dependent admitted regressions and owns cleanup afterward.

### S8 implementation checkpoint (not closure)

The old approximate actor has been replaced by shared enemy/firebar.c,
with explicit position, coordinate/draw and collision entries. The source
offscreen, spin, relative and OAM child contracts have typed boundaries;
the existing injury helper remains a separately tracked dependency. The
obsolete per-ball OAM API has no remaining callers and is removed. The
legacy aggregate retains eligibility and compatibility injury reporting,
while the source actor continues all balls after injury.

Position lookups use the existing immutable area_prg binding, including
table-adjacent bytes reached by the residual call. The source data address
range requires at least $4E2E bytes from the PRG base. Missing data is an
explicit unmet resource prerequisite: the actor stops after the offscreen
check rather than fabricating lookup values. This does not establish DOS
resource binding or graphical playability. ROM proof must provide the owner
data binding; unit contracts use synthetic project-owned data instead.

Native chain contracts pass on x86/x64 for center plus five/eleven outer
balls, the duplicate OAM switch, saved child-return Y, phase-eight adjustment,
continued drawing after injury mutates scratch, offscreen early exit and
residual indexed data reads. These are not original-ROM equivalence proof.
Instruction/branch recordings and actual-child comparisons remain pending;
no S8 node is promoted and no P commit is claimed at this checkpoint.

Recorder sizing must allow up to 27 immediate child records: three setup
children plus twelve draws and twelve injury calls when injury invincibility
causes the injury child to return without setting TimerControl. The existing
64-record storage is sufficient, but this mode's current sixteen-record
admission limit must be raised explicitly before recording. Never truncate
the tail of a long-bar route to fit a diagnostic buffer.

## S8 original firebar chain proof

S8 P1 closes all 32 expected caller/data nodes: 1,112 -> 1,144/1,992.
No scoped unfinished node or transfer remains. External-child gaps remain
with their existing receivers; S9 is next in the approved source sequence.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| FirebarPosLookupTbl | $CCC7 | All 99 bytes bound and consumed; original $CD0B value restored by immutable binding; new ROM match |
| FirebarMirrorData | $CD2A | Bind quadrant mirror values and exact indexed reads including residual-call addresses; new ROM match |
| FirebarTblOffsets | $CD2E | Bind all twelve offsets; retain source byte indexing and adjacency; new ROM match |
| FirebarYPos | $CD3A | Bind the two additional big-player vertical collision probes; new ROM match |
| ProcFirebar | $CD3C | Offscreen-before-spin, timer gate, original child order and center/outer iteration; new ROM match |
| SusFbar | $CD55 | Paused spin state is read without speed update; new ROM match |
| SkpFSte | $CD65 | Long-bar phases eight/twenty-four increment once; new ROM match |
| SetupGFB | $CD6A | Save phase, relative child return/scratch, residual lookup and center coordinates; new ROM match |
| SetMFbar | $CD96 | Store short/long maximum after center collision; new ROM match |
| DrawFbar | $CD9C | Lookup and collision/draw repeated in original sequence; new ROM match |
| NextFbar | $CDB2 | Increment index and compare to $ED after duplicate-OAM switch; new ROM match |
| SkipFBar | $CDBA | Offscreen branch returns before motion or drawing; new ROM match |
| DrawFirebar_Collision | $CDBB | Preserve mirror scratch and coordinate-to-OAM order; new ROM match |
| AddHA | $CDCB | Horizontal signed adder plus relative X with byte wrap; new ROM match |
| SubtR1 | $CDE2 | Unsigned ordering selects non-wrapped absolute horizontal distance; new ROM match |
| ChkFOfs | $CDE6 | $59 distance gate hides Y while preserving sprite X; new ROM match |
| VAHandl | $CDEE | Anchor Y $F8 short-circuits vertical mirror handling; new ROM match |
| AddVA | $CDFF | Vertical signed adder plus relative Y with byte wrap; new ROM match |
| SetVFbr | $CE03 | Store OAM Y and scratch $07 before collision entry; new ROM match |
| FirebarCollision | $CE08 | Draw child first, saved Y and star/timer/high-Y gates; new ROM match |
| AdjSm | $CE28 | Small or crouching probe counter two and Y plus $18; new ROM match |
| BigJp | $CE31 | Preserve big standing initial Y probe; new ROM match |
| FBCLoop | $CE32 | Signed byte vertical difference and absolute magnitude; new ROM match |
| ChkVFBD | $CE3C | Vertical eight-pixel and far-right X gates; new ROM match |
| ChkFBCl | $CE58 | Player sprite-one X plus four and signed horizontal threshold; new ROM match |
| Chk2Ofs | $CE5C | Advance big-player probe table or exit at counter two; new ROM match |
| ChgSDir | $CE6F | Choose injury direction from modded sprite X comparison; new ROM match |
| SetSDir | $CE78 | Slot-zero direction, injury child, saved $00 and resumed source loop; new ROM match |
| NoColFB | $CE85 | Saved OAM offset plus four and ObjectOffset restoration; new ROM match |
| GetFirebarPosition | $CE8E | Preserve caller A through both triangular lookups and mirror selection; new ROM match |
| GetHAdder | $CE9A | Horizontal oscillation plus original per-ball table index; new ROM match |
| GetVAdder | $CEBA | Vertical oscillation plus original per-ball table index and mirror output; new ROM match |
The 512 original NMI routes cover short/long bars, all phases, both spin
directions, timer pause, slot zero/five, duplicate OAM, wrap/edge coordinates,
player probe forms and injury. Cases zero through three supply Player_Y_HighPos
as two at the naturally reached actor entry; cases four through seven align
sprite-one X/Y with the center ball and set powered-player status there.
The other 504 cases need no mid-entry inputs. All changes are declared RAM
inputs independent of observation; ROM, CPU registers, PC, stack and outputs
are never patched. All 512 observer-free frames equal observed records.
This is observer noninterference, not native full-frame conformance.

All 205 scoped instructions and both feasible outcomes of 26 conditional
branches execute. The remaining BNE at $CDEC follows LDA #$F8 and cannot
fall through. All 28 code labels have entry coverage. The four immutable
tables bind exactly to the owner PRG; all 99 position bytes and four mirror
bytes are consumed, along with the eleven operative offsets. The twelfth
offset is retained source data beyond the eleven-ball loop. The two Y
probe bytes are consumed by the original big-standing-player probe loop.
The 4,032 position calls include the residual relative-X call. Bounded
adjacent reads are preserved rather than clamped; all byte inputs are
bounded by $CE2D. No instruction bytes are executed by the game.

Caller-boundary comparisons pass 1,024/1,024 on x86/x64. Each complete child
input is compared before its recorded return is substituted. Root exit RAM,
all scratch and mapped $0109-$0139 are checked; only hardware-stack storage
is excluded. The scoped code reads bound data and writes original RAM/OAM,
with no other output surface. Real-child root comparisons are separately
292/1,024: these failures are preserved, not accepted as full-chain matches.

| External child | Actual entry/return comparisons | Difference and existing receiver |
| --- | ---: | --- |
| GetEnemyOffscreenBits | 0/1,024 | Missing $04-$07 scratch writes, plus $00 in 192 comparisons; M2 T16 S4 |
| FirebarSpin | 640/640 | Current seam matches these inputs; node remains with M2 T19 S5 |
| RelativeEnemyPosition | 416/896 | Missing $00 slot write in 480 comparisons; M2 T16 S4 |
| DrawFirebar | 8,064/8,064 | RAM and returned Y match these inputs; node remains with M2 T17 S6 |
| InjurePlayer | 12/20 | Powered injury misses $00, Square1SoundQueue and $0300-$0307 palette-buffer writes in eight comparisons; M2 T17 S6 |

No external child receives completion credit. The combined actual-root
matrix is 7,600/9,106, retaining all 7,308 previous matches. Its 1,506
comparison failures remain explicit dependencies, not deferred scoped nodes.

Shared enemy/firebar.c replaces the former approximate actor. Its source
sequence retains the preliminary lookup, center collision, five/eleven outer
balls, duplicate-OAM switch, original byte/nonwrapped distance operations,
sprite-one player X, source probe loop, slot-zero injury direction and saved
loop/OAM state. Injury does not stop the remaining balls. The old copied
position value at $CD0B was wrong; immutable binding removes that divergence.
Only typed child seams are introduced; their known gaps are not patched in
the caller. OAM allocation has one owner. The old per-ball drawing API is
removed; existing RunFirebarObj still reaches its bounds tail after injury.

Independent native chain contracts and the corrected integration smoke pass
on both widths. The latter now supplies synthetic data, valid viewport state
and source sprite/probe inputs; it is not a ROM fixture. Earlier focused
contracts and fifteen initialization/platform smokes per width pass.
Existing Bowser damage and endgame star-timer failures remain unchanged;
the broad core smoke's earlier player-entrance failure is not claimed fixed.
All 99 shared units compile under strict C90 for x86/x64. Self-tests and
hidden-window response probes pass without foreground input. DOS16 links
with the existing OLDNAMES warning and remains link-only: resource binding,
graphical playability and physical 486 performance are not established.
Platform purity passes and all three owner-authorized test EXEs are refreshed.

Similar-issue review covers the former inline owner, special caller, five
child seams, OAM, initializers and firebar tests. The legacy aggregate is
only used by its smoke test; runtime dispatch supplies the original slot.
The separate fireball drawing routine and external child interiors retain
their original ownership and are not silently rewritten here.

Reproduce firebar_chain_fixture.h cases 0..511 with --fixture=t40-firebar-chain=N,
--firebar-chain-snapshot, --control-children and a separate --pc-coverage run.
firebar_chain_snapshot_check provides caller proof; enemy_loop_actual_check
runs real children; firebar_children_actual_check isolates each real child's
recorded entry. Native tests are mysmb.firebar-chain and mysmb.firebar-smoke.
Local source-audit, data-binding-audit, child-actual-summary, final-root-regressions
and retained-proof summaries remain under ignored build/m2-t40-s8. Raw inputs
including superseded controlled-input records use 26,640,124 bytes, below the
64-MB budget. Unique paths, twenty-second timeouts and checkpoints bound runs;
the coordinator retains inputs for dependent regressions and owns cleanup.
Owner-local ROM/listing provenance and redistribution restrictions remain.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256195 | 41a74ca38113d8786d21871fe80af05b5e26ebeb9ac0101bde60ae3445d1924e |
| mysmb32.exe | 347941 | 0cd01bc18cf4ba83c13184078739ac6681c4c32310f964784c1657589fcabeed |
| mysmb64.exe | 355482 | 73fa296205f27e2a904faea65b52a0827411a552a1cdac88905479bc13d430ef |

## S9 admission: Flying Cheep-Cheep movement

S8 closed in 9b621d5. Coordinator accepts transfer-193 under the approved
source-order plan. Baseline 1,144/1,992; all six scoped nodes are open and
expected new, maximum 1,150. The chain spans $CED5-$CF24, following firebars
and ending before LakituDiffAdj; S10 remains next.

| Node | Original address | Required individual proof |
| --- | --- | --- |
| PRandomSubtracter | $CED5 | Bind five bytes and all sixteen original indexed addresses, including adjacent bytes |
| FlyCCBPriority | $CEDA | Bind five bytes and sixteen priority reads, including code-adjacent data |
| MoveFlyingCheepCheep | $CEDF | Defeated bit clears attributes before MoveJ_EnemyVertically tail |
| FlyCC | $CEED | Horizontal child before SetXMoveAmt with Y=$0D, A=$05; read post-gravity force/Y |
| AddCCF | $CF0C | Signed wrapped difference magnitude below eight adds $10 to force with byte wrap |
| BPGet | $CF1E | Read priority from final high nibble and write Enemy_SprAttrib |

Shared enemy/flying_cheep.c replaces the abbreviated inline body. Original
entry has no flag/ID/timer guards; preserve compatibility guards only in the
legacy aggregate. Reuse the existing proved horizontal and gravity entries;
no child receives extra credit. Use the immutable area_prg binding for lookup
adjacency, bounded through $CEE9, without copying instruction bytes into code
or interpreting them. Missing binding is an explicit unmet prerequisite for
the lookup tail, not permission to invent values. DOS binding remains unproven.

ROM logic proof starts from this source/branch/read/write map. Observe original
NMI actor entries for defeated/live, all sixteen force nibbles, signed
subtraction, magnitude boundary and wrap, then compare original root RAM and
child order/inputs with native C on both widths. Child substitution is diagnostic
only after input comparison; actual children run separately. Controlled RAM
inputs at naturally reached entries are allowed to cover missing branches;
no ROM, PC, CPU/register, stack or output patch. Prove observer noninterference.
Independent native contracts test full RAM footprints, child mutation/order,
priority and force wrap. Refresh three EXEs once after strict C90 x86/x64,
DOS16 link, focused regressions, prior matching routes, hidden-window probes
and platform purity. Existing injury/offscreen/graphics gaps remain explicit.

Similar-issue sweep covers inline/aggregate movement, normal-actor vector,
initializer force/attribute aliases and flying-fish tests. Existing owner-local
ROM and disassembly provenance and local-only redistribution limits remain;
no third-party import. Keep generated data, records and logs in ignored
build/m2-t40-s9, at most 512 cases and 16 MB raw, unique paths, twenty-second
per-run deadlines and checkpoints. Coordinator owns retention/cleanup after
all dependent regressions. No node credit before both verification tracks.

## S9 original flying Cheep-Cheep movement proof

S9 P1 closes all six expected nodes: 1,144 -> 1,150/1,992. No scoped
unfinished node or transfer remains; S10 is next in the existing plan.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| PRandomSubtracter | $CED5 | Five bound source bytes and all sixteen original indexed addresses consumed; new ROM match |
| FlyCCBPriority | $CEDA | Five bound priority bytes and all sixteen indexed addresses consumed; new ROM match |
| MoveFlyingCheepCheep | $CEDF | State bit $20 clears attributes before the exact jumping-gravity tail; new ROM match |
| FlyCC | $CEED | Horizontal then original $0D/$05 gravity; post-child state selects lookup; new ROM match |
| AddCCF | $CF0C | Wrapped signed magnitude below eight adds $10, including force wrap; new ROM match |
| BPGet | $CF1E | Final force high nibble selects original attribute data and exact write; new ROM match |
The 512 original NMI routes execute all 37 scoped instructions and both
outcomes of all three conditional branches: defeated/live (32/480), signed
wrapped difference (231 negative/249 nonnegative), and threshold adjustment.
All sixteen subtractor and priority indices are consumed, including the
original table-adjacent code bytes. The ten named data bytes and bound
32-KB immutable view match the owner ROM exactly; the last indexed address
is $CEE9. Case fifteen also exercises force $F0 plus $10 wrapping to zero
and then selecting priority index zero. These bytes are data, never executed.

Original caller and actual-child root comparisons both pass 1,024/1,024 on
x86/x64. Each live route calls horizontal movement before SetXMoveAmt with
$0D/$05; defeated routes clear attributes before the jumping-gravity tail.
The caller reads force and Y only after the child returns. Complete child
input is checked before diagnostic return substitution; actual comparisons
use the real shared children. All RAM, including scratch and mapped
$0109-$0139, is checked; hardware-stack storage alone is excluded. The
scoped owner has no PPU/audio/CIRAM output or host access. No ROM, CPU,
PC, stack or output patch and no mid-entry RAM override is used. The
512 observer-free frames equal the observed records; this establishes
observer noninterference, not whole-game native frame equivalence.

Shared enemy/flying_cheep.c replaces the abbreviated inline movement.
It restores defeated attribute clearing, source horizontal/gravity order,
wrapped signed distance, force adjustment and final sprite-attribute lookup.
The source entry has no extra flag/ID/timer guard. Those guards remain only
at the legacy aggregate boundary. Existing movement/gravity children and
normal-actor vector are reused and receive no additional completion credit.
The lookup tail requires immutable owner data; DOS binding is not established.

Independent native contracts exhaust all 256 post-child forces against all
256 byte differences, plus the defeated path: 65,537 cases per width.
They check full RAM footprints, deliberate child mutations/order, threshold
seven/eight, signed $80, force overflow, source entry without compatibility
guards and final indexed priority. The integration smoke now supplies
synthetic project-owned data and checks actual priority output and defeat
clearing; its legacy timer check remains explicitly at the aggregate boundary.

The combined original-root matrix is 8,628/10,130, retaining all 7,600 prior
matches and improving four earlier comparisons. The 1,502 remaining child/
frame-route differences retain their existing source-order owners. Earlier
native contracts, fifteen initialization/platform smokes per width and
focused layout/mode tests pass. Known Bowser damage and endgame star-timer
failures remain unchanged; the broad core smoke's player-entrance failure
is not claimed resolved. All 100 shared units compile under strict C90 for
x86/x64. Both self-tests and hidden-window response probes pass. DOS16 links
with the existing OLDNAMES warning and remains link-only, without graphical,
resource-binding or physical 486 performance claims. Platform purity passes;
all three owner-authorized test EXEs are refreshed once for S9 P1.

Similar-issue review covers the old inline/aggregate body, normal movement
vector, flying-fish initializer, $0434 force/$03C5 attribute aliases and tests.
There is one runtime movement owner; no host adapter contains new logic.
The defeated initializer and shared gravity/horizontal semantics are unchanged.

Reproduce flying_cheep_movement_fixture.h cases 0..511 with
--fixture=t40-flying-cheep-movement=N, --flying-cheep-movement-snapshot,
--control-children and a separate --pc-coverage run. Caller proof uses
flying_cheep_movement_snapshot_check; enemy_loop_actual_check runs real
children. Native contracts are mysmb.flying-cheep-movement and
mysmb.flying-cheep-smoke. Source-audit, data-binding-audit, retained-proof and
final-root-regressions summaries remain below ignored build/m2-t40-s9.
Unique paths, twenty-second timeouts and checkpoints bound each run; raw
inputs including the superseded wrap case remain below the 16-MB budget.
Coordinator retains them for dependent regressions and owns later cleanup.
Existing owner-ROM/listing provenance and redistribution limits remain.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256643 | 3ff8f4059c64aba06081f2630ea6f892c9e973c6bd81b19f21d71b575553d64e |
| mysmb32.exe | 348669 | 46b236ef19cf0e16648274c7bd2b409b035da19a29a466540b424b69b60205cd |
| mysmb64.exe | 356246 | ad5c0abd18d0e1958ed0c32f2b88a5308c768456ce24f7988aa46fc36c6bfdf8 |

## S10 admission: Lakitu movement and distance

S9 closed in 3a59dca. Coordinator accepts transfer-194 under the approved
source-order plan. Baseline 1,150/1,992; all sixteen scoped labels below are
open and expected new, maximum 1,166. Source $CF25-$CFDC ends before the
bridge/Bowser slice. This is T40's final chain; its closure also assembles
T40's cross-chain evidence and exact 120-node disposition without duplicating
already accepted proof or inventing another S.

| Node | Original address | Required individual proof |
| --- | --- | --- |
| LakituDiffAdj | $CF25 | Three table values copied to scratch in reverse-index order |
| MoveLakitu | $CF28 | Defeated bit selects the MoveD_EnemyVertically tail |
| ChkLS | $CF31 | Nonzero live state clears frenzy/direction and sets speed $10 |
| Fr12S | $CF40 | Zero state requests Spiny before scratch/table setup |
| LdLDa | $CF47 | Populate $01-$03 before the shared distance child |
| SetLSpd | $CF53 | Store returned speed including delayed-turn result, no extra exit |
| SetLMov | $CF67 | Direction bit chooses sign, then horizontal child |
| PlayerLakituDiff | $CF6C | PlayerEnemyDiff page sign and low scratch determine byte distance |
| ChkLakDif | $CF7D | Clamp at $3C and compare full direction byte for Lakitu |
| SetLMovD | $CF9C | Commit new direction only at the original delay boundary |
| ChkPSpeed | $CF9F | Mask/divide scratch distance; preserve speed/scroll gates |
| ChkSpinyO | $CFC1 | Spiny-specific bypass of vertical-state adjustment reset |
| ChkEmySpd | $CFCB | Zero vertical state resets adjustment index only on this path |
| SubDifAdj | $CFD1 | Read caller-provided $01-$03, never hardcode Lakitu data here |
| SPixelLak | $CFD6 | Subtract once plus masked distance with byte wrap |
| ExMoveLak | $CFDC | Return original accumulator, including decremented speed |

Create shared enemy/lakitu.c and remove the old duplicate bodies from frenzy.c.
Use the existing PlayerEnemyDiff typed return/scratch seam; its node retains
its own later receiver. Existing horizontal/gravity children are reused.
Lakitu movement loads its own table; Spiny continues supplying its distinct
adjusters through the same shared helper. Preserve source scratch writes and
call order, remove the fabricated zero return and caller early exit, and keep
flag/ID eligibility only on the legacy aggregate. No platform game logic.

Prove source branches, scratch, returned A, node/control/data relationships
against original NMI movement and helper entry routes, plus retained Spiny
caller samples. Compare child input before any diagnostic substitution and
run real children separately. Controlled RAM inputs at naturally reached
entries are allowed for branch coverage; ROM, CPU/register, PC, stack and
output patches are forbidden. Native contracts independently cover full RAM
footprints, custom adjusters, capped signed byte distance, turnaround delay,
unsigned speed gates, subtract-one loop and child mutations. Recheck all
previous matching routes, strict C90 x86/x64, DOS16 link, hidden-window probes,
platform purity, governance and the three EXEs once for S10 P1.

The validation harness may batch existing snapshot inputs in one process
provided every case resets all native state; this reduces process-launch
cost without reducing comparisons. Similar-issue review covers both consumers,
existing helper seams, scratch and speed/direction aliases, initializers and
tests. Owner-local ROM/listing provenance and redistribution limits remain.
All temporary/generated material stays under ignored build/m2-t40-s10, with
at most 1,024 new original cases, 32-MB raw budget, unique paths, twenty-second
per-run deadlines and checkpoints. Coordinator retains inputs for dependent
regressions and owns cleanup. No completion credit before both proof tracks.

## S10 original Lakitu movement and distance proof

S10 P1 closes all sixteen expected nodes: 1,150 -> 1,166/1,992. No scoped
unfinished node or transfer remains; T40 cross-chain review follows.

| Node | Original address | Individual evidence and disposition |
| --- | --- | --- |
| LakituDiffAdj | $CF25 | Three table values copied to scratch in reverse-index order; new ROM match |
| MoveLakitu | $CF28 | Defeated bit selects the MoveD_EnemyVertically tail; new ROM match |
| ChkLS | $CF31 | Nonzero live state clears frenzy/direction and sets speed $10; new ROM match |
| Fr12S | $CF40 | Zero state requests Spiny before scratch/table setup; new ROM match |
| LdLDa | $CF47 | Populate $01-$03 before the shared distance child; new ROM match |
| SetLSpd | $CF53 | Store returned speed including delayed-turn result, no extra exit; new ROM match |
| SetLMov | $CF67 | Direction bit chooses sign, then horizontal child; new ROM match |
| PlayerLakituDiff | $CF6C | PlayerEnemyDiff page sign and low scratch determine byte distance; new ROM match |
| ChkLakDif | $CF7D | Clamp at $3C and compare full direction byte for Lakitu; new ROM match |
| SetLMovD | $CF9C | Commit new direction only at the original delay boundary; new ROM match |
| ChkPSpeed | $CF9F | Mask/divide scratch distance; preserve speed/scroll gates; new ROM match |
| ChkSpinyO | $CFC1 | Spiny-specific bypass of vertical-state adjustment reset; new ROM match |
| ChkEmySpd | $CFCB | Zero vertical state resets adjustment index only on this path; new ROM match |
| SubDifAdj | $CFD1 | Read caller-provided $01-$03, never hardcode Lakitu data here; new ROM match |
| SPixelLak | $CFD6 | Subtract once plus masked distance with byte wrap; new ROM match |
| ExMoveLak | $CFDC | Return original accumulator, including decremented speed; new ROM match |
The 1,024 original NMI routes comprise 512 MoveLakitu entries and 512
PlayerLakituDiff entries. Declared RAM inputs at naturally reached entries
vary page/low distance, full-byte direction, current speed, player speed,
scroll amount, caller-supplied adjustment values and Lakitu/Spiny/other IDs.
Helper cases change the ID/adjusters only at the reached helper entry;
observation mode never controls those inputs. No ROM, CPU/register, PC,
stack or output patch is used. All 1,024 observer-free frames equal their
observed counterparts; this is not a native full-game frame claim.

All 92 scoped instructions and sixteen label/data consumers are covered.
Seventeen conditional branches have both outcomes. BNE at $CF3E follows
LDA #$10 and cannot fall through. BNE at $CFC9 cannot fall through because
zero Player_X_Speed already branches to SubDifAdj at $CFAB and no intervening
instruction changes that memory. Both infeasible sides are explicitly
recorded rather than forced with execution patches. The three LakituDiffAdj
bytes match the native table and the reversed copy loop executes all entries.

Caller-boundary and actual-child comparisons each pass 2,048/2,048 on x86/x64,
including the helper's returned accumulator. Complete child inputs are
compared before diagnostic substitution; real children run separately. All
scratch and mapped $0109-$0139 RAM remain checked; hardware-stack storage
alone is excluded. The scoped code has no other output surface. Existing
PlayerEnemyDiff remains an external dependency with no incidental node credit.

Shared enemy/lakitu.c replaces both old frenzy.c bodies and preserves the
original copy/subtraction loops. PlayerEnemyDiff's page-byte sign selects the
low-byte absolute difference, followed by cap and original delayed turn.
The delay returns the decremented speed, not zero; MoveLakitu always stores
that result and reaches horizontal motion. The shared helper reads $01-$03,
so Spiny retains its own adjustment set. The speed/scroll gates and Spiny
exception control the index reset exactly; scratch $00 remains original.
Flag/ID eligibility stays only on the legacy aggregate. Initializer logic,
other child algorithms and host adapters are unchanged.

Independent full-RAM native contracts pass seventeen cases per width,
including custom adjusters, cap, byte overflow, delayed-turn return, unsigned
player speed, direction values beyond one and source child order. The old
Lakitu integration smoke also passes after correcting its missing original
current-slot ID/ObjectOffset preconditions and its stale direction-two
expectation: SmallBBox returns A=0, so SetSpSpd stores direction one.
That test failed identically before this S; no gameplay code was changed to
satisfy its old assumptions. Existing original Spiny comparisons improve
from 36/160 to 160/160 under the shared distance repair.

The final actual-root matrix is 10,804/12,178, retaining all 8,628 previous
matches and improving 128 prior failures. Remaining 1,374 differences keep
their source-order owners. Fifteen initializer/platform smokes per width,
earlier native contracts, layout/mode tests, platform purity and governance
pass. Existing Bowser/endgame smoke failures remain; broad player-entrance
failure is not claimed repaired. Batch validation resets the entire native
state for every case and cross-checks spaced cases against separate process
execution, retaining identical per-case results and full difference output.

All 101 shared units compile in strict C90 for x86/x64; both self-tests and
hidden-window response probes pass. DOS16 links with the existing OLDNAMES
warning and remains link-only. Resource binding, graphical playability and
physical 486 performance remain unproven. All three test EXEs are refreshed.

Similar-issue review covers both original consumers, PlayerEnemyDiff's typed
seam, speed/direction aliases, scratch arrays, existing Spiny setup and tests.
There is one shared distance owner and no platform gameplay. Reproduce
lakitu_movement_fixture.h cases 0..1023 using --fixture=t40-lakitu-movement=N,
--lakitu-movement-snapshot, --control-children and --pc-coverage separately.
lakitu_movement_snapshot_check verifies caller inputs/returns;
enemy_loop_actual_check runs real bodies, including optional --batch with
one snapshot path per input line. Native contracts are
mysmb.lakitu-movement-distance and mysmb.lakitu-smoke.

Source-audit, original-results, actual-results, native-chain, retained-proof
and final-root-regressions stay below ignored build/m2-t40-s10. Raw original
records use 14,770,048 bytes, below 32 MB. Unique paths, twenty-second recorder
deadlines and checkpoints bound runs; the coordinator retains inputs for
dependent regressions and owns cleanup. Existing local owner-ROM/listing
provenance and redistribution limits remain.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 256563 | 34c9cc45af08acf5f91d5909c0ccccfa50c8dc8bfc705ecab62c8b09d287519a |
| mysmb32.exe | 348913 | 816b265f334b7ae62e03a5700c161b9eaceef69331bacc76621d601623539bba |
| mysmb64.exe | 356526 | ef5ce4215bcc0a4640f71a7575f8afe8295d750163408d2bd1f30ccd123788fa |

## T40 closure

All ten source-ordered S chains are closed. All 120 unique scoped nodes are
individually ROM-match complete: 107 new and thirteen retained, bringing the
canonical count from 1,059 to 1,166/1,992. No scoped unfinished node remains
and no closure transfer is required. Each label keeps its exact maintenance
receiver. Reused external dependencies receive no duplicate credit.

| Chain | Scoped | New matches |
| --- | ---: | ---: |
| M2 T40 S1 | 2 | 2 |
| M2 T40 S2 | 24 | 11 |
| M2 T40 S3 | 5 | 5 |
| M2 T40 S4 | 10 | 10 |
| M2 T40 S5 | 16 | 16 |
| M2 T40 S6 | 2 | 2 |
| M2 T40 S7 | 7 | 7 |
| M2 T40 S8 | 32 | 32 |
| M2 T40 S9 | 6 | 6 |
| M2 T40 S10 | 16 | 16 |

Retained matches: XSpeedAdderData, RevivedXSpeed, MoveNormalEnemy, FallE, MEHor, SlowM, SteadM, AddHS, ReviveStunned, SetRSpd, MoveDefeatedEnemy, ChkKillGoomba, NKGmba.

The integrated matrix below runs actual shared C children without recorded
return substitution. It complements the individual source/caller/data proofs;
a caller's completed status does not certify an unproved descendant.

| Original route family | Actual matches | Remaining differences |
| --- | ---: | ---: |
| loop | 192/192 | 0 |
| stream | 160/160 | 0 |
| init | 220/220 | 0 |
| common | 104/104 | 0 |
| spiny | 160/160 | 0 |
| firebar | 80/80 | 0 |
| fish | 304/304 | 0 |
| bowser-flame | 320/320 | 0 |
| fireworks | 240/240 | 0 |
| bullet-swim | 364/364 | 0 |
| group | 230/230 | 0 |
| small-init | 392/392 | 0 |
| platform-init | 480/480 | 0 |
| actor-dispatch | 42/360 | 318 |
| normal-actor | 80/252 | 172 |
| special-actor | 32/184 | 152 |
| podoboo | 128/128 | 0 |
| hammer-movement | 712/712 | 0 |
| paratroopa | 320/320 | 0 |
| green-counter | 576/576 | 0 |
| bloober | 1024/1024 | 0 |
| bullet-movement | 256/256 | 0 |
| swimming-cheep | 1024/1024 | 0 |
| firebar-chain | 292/1024 | 732 |
| flying-cheep-movement | 1024/1024 | 0 |
| lakitu-movement | 2048/2048 | 0 |

Total 10,804/12,178 actual comparisons match. All 8,628 S9 matches remain;
128 former differences now match, including all 124 prior Spiny failures.
S10 contributes 2,048 additional matching comparisons. The remaining 1,374
differences are actor-dispatch (318), normal-actor (172), special-actor (152)
and firebar-chain (732). These are sample counts, not node counts. Existing
offscreen, relative-coordinate, collision/injury, graphics and other child
obligations retain their exact ledger receivers and source-order admission.
This review neither hides those differences nor certifies full-game equality.

S10's final 101-unit strict C90 x86/x64 builds, independent native contracts,
cross-chain comparisons, DOS16 link, platform-purity check, self-tests and
hidden-window response probes supply this integrated T delivery. Its three
executable sizes and hashes above are verified against assets/. Earlier
accepted chain proofs are reused without repeating their node lifecycles.
Existing Bowser/endgame and broad player-entrance smoke gaps remain explicit.
DOS16 is link-only: no graphical playability, resource binding or physical
486SX performance claim is made. Platform adapters contain no new gameplay.

T40 is closed; M2 remains incomplete. The next queued source slice begins
BridgeCollapseData at line 10092 and BridgeCollapse at line 10098, preserving
the complete bridge/Bowser chain. This closure does not admit T41; publish
its exact node scope and S ownership before implementation under the continuing
approved M2 mandate.
