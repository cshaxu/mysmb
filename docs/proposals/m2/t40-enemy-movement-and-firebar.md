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
