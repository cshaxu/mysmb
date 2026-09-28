# M2 T32: Player control and mode chains

## Status

T32 follows closed T31. S1-S3 are closed with 38 scoped matches; S4 alone is active.
Task baseline 628 / 1,992. The source-range plan lists 49 open labels;
48 are intended matches here, maximum 676. PlayerMovementSubs begins the
next complete movement-state chain at line 5899; it retains T23 S5 custody
until T33 admission instead of receiving a one-label partial implementation.
No friction/jump implementation is claimed merely from the old range title.

## Exact chain plan

The rows preserve admission-time open nodes in original source order.
S1-S3 are closed; S4 is now admitted by its exact ledger receipt. Each S carries source audit, shared-C implementation,
ROM comparison, native tests and one three-target delivery together.

| S | Exact labels | Shared-game responsibility |
| --- | --- | --- |
| S1 | `PlayerCtrlRoutine`, `DisJoyp`, `SaveJoyp`, `SizeChk`, `ChkMoveDir`, `SetMoveDir`, `PlayerSubs`, `PlayerHole`, `HoleDie`, `HoleBottom`, `ChkHoleX`, `ExitCtrl`, `CloudExit` | Controller decode, movement handoff, bounding/scroll/collision call order and hole/cloud tail |
| S2 | `Vine_AutoClimb`, `AutoClimb`, `SetEntr`, `VerticalPipeEntry`, `MovePlayerYAxis`, `SideExitPipeEntry`, `ChgAreaPipe`, `ChgAreaMode`, `ExitCAPipe`, `EnterSidePipe`, `RightPipe` | Vine entry and pipe movement/area-transition chain |
| S3 | `PlayerChangeSize`, `EndChgSize`, `ExitChgSize`, `PlayerInjuryBlink`, `ExitBlink`, `InitChangeSize`, `ExitBoth`, `PlayerDeath`, `DonePlayerTask`, `PlayerFireFlower`, `CyclePlayerPalette`, `ResetPalFireFlower`, `ResetPalStar`, `ExitDeath` | Size, injury, death and palette timer-state chain |
| S4 | `FlagpoleSlide`, `SlidePlayer`, `NoFPObj`, `Hidden1UpCoinAmts`, `PlayerEndLevel`, `ChkStop`, `InCastle`, `RdyNextA`, `NextArea`, `ExitNA` | Flagpole, castle entry, hidden 1-up threshold and NextArea chain |

Deferred boundary label: `PlayerMovementSubs` (open, existing T23 S5).
Its successors belong to the next movement-state source slice; no completion
credit or new receiving S is invented. S2-S4 node receipts will be validated
at their own admission. T closure checks all 49 dispositions and integrates
the chains once, retaining actual child/output failures.

## S1 admission: PlayerCtrlRoutine through CloudExit

Scope and expected matches are the thirteen exact S1 labels above, all open.
Baseline 628, expected 13, maximum 641. Original entry is GameRoutines or
AutoControlPlayer; source lines 5583-5687 end at ExitCtrl or CloudExit/SetEntr.
Use a shared game/player_control.c owner, retaining player.c child algorithms
behind declared seams where extraction is required. Platforms never inspect
or alter game RAM. No broad physics, collision, OAM or audio repair is admitted.

Predecessor: T31's verified saved-input and thirteen-way dispatch contracts.
Successors: PlayerMovementSubs (T23 S5), ScrollHandler (T31 S3), player
offscreen/relative/bounding/terrain children (their existing receivers),
and SetEntr (planned S2, current T23 S5). Caller proof cannot certify those
children. Their existing production failures stay visible. Source-order
extraction may expose unchanged child bodies but grants no child credit.

ROM logic track: compare water/high-Y input suppression, death-mode bypass,
AB/LR/UD masks, ground-down cancellation, movement-before-size reads,
zero-speed moving-direction preservation, ordered scroll/offscreen/relative/
bounding/terrain calls, priority-bit gates, signed-byte hole comparisons,
death-music/timer/cloud thresholds and SetEntr-before-alt-increment ordering.
Use ordinary NMI source-RAM fixtures and read-only natural boundaries;
record both caller contracts and actual production child discrepancies.
No PC/stack/ROM mutation or removed mismatch bytes is allowed.

Operational track: independent child-call tests and exhaustive byte gates,
existing player-route/entry regressions, strict C90 x86/x64 and OpenNT DOS16,
platform purity and all three EXEs once per implementation P. DOS remains
link-only. This first S does not promise whole-game or whole-player equivalence.

Owner ROM and reviewed disassembly remain local, non-redistributable research
inputs. No third-party implementation is imported. Existing owner-authorized
three artifact inclusion remains in force. Temporary products stay below
ignored build/m2-t32-s1; raw trace cap 4 MB, twenty-second recorder limit,
S1 cleanup ownership through T review. Similar-issue sweep covers all player
control entry sites, duplicate input decode, post-movement bounding setup,
hole exits and physical/platform button adapters.

## S1 initial source-to-C audit

The thirteen-node admission and documentation gates pass at 628, with all
thirteen incoming states open. The source audit finds concrete caller gaps:

- Water input suppression currently clears only a local argument, while the
  original DisJoyp clears SavedJoypadBits itself. Crouching is also calculated
  inside input decoding even though the original movement child owns it.
- The native climbing branch returns before the common SizeChk, direction,
  scroll/offscreen and hole tail. Original PlayerMovementSubs returns to the
  same PlayerCtrlRoutine continuation for every movement state.
- The ordinary path omits GetPlayerOffscreenBits, calls relative position a
  second time after terrain collision, and lacks the original priority-bit
  clearing predicates. The shared caller must invoke each original child in
  source order, without importing child algorithm repair.
- The hole tail uses unsigned less-than where the source uses BMI on the
  wrapped eight-bit subtraction result. Test all high-Y values and retain
  the distinction between the first threshold 2 and later threshold 4/6.
- CloudExit inlines a partial transition instead of clearing override,
  calling SetEntr, then incrementing the returned alternate-entry byte.
  Expose the existing transition child before correcting its caller;
  SetEntr's own implementation remains the next S responsibility.

Implementation begins with structural separation of movement and terrain
children from the caller, then restores the one common continuation. Tests
must mutate child-return state to prove post-child reads and verify that
climbing cannot bypass the common caller tail. These are source-derived
requirements; the retained T31 vine failures are regression evidence only.

## S1 implementation checkpoint: common player-control continuation

PlayerCtrlRoutine now has one shared player_control.c owner. The movement
and terrain children are extracted from player.c without admitting their
full algorithm repair. Input decoding writes the original SavedJoypadBits
on water suppression; crouch calculation moves to the movement child.
All movement returns, including climbing, use one size/direction/scroll/
offscreen/relative/bounding/terrain continuation. The duplicate post-terrain
relative-position call is removed. Priority predicates and both wrapped
CMP/BMI hole tests follow the source; CloudExit clears override, calls the
extracted SetEntr child, then increments its returned alternate-entry byte.
SetEntr's missing sprite-0 transition remains explicitly S2 work.

The [independent caller test](../../../test/player_control_chain_smoke.c)
passes under strict C90 on x86/x64: all 256 inputs in four states, all 65,536
water high-Y/low-Y pairs, thirteen mode priority gates across every Y byte,
and every high-Y value with cloud/timer/music/death combinations. Mutating
child callbacks verify post-movement size/direction, post-terrain priority
reads, exact six-child order and SetEntr-before-increment behavior.
Production-linked player-route and area-initialization regressions plus the
prior entry-chain callback suite pass on both widths. OpenNT large-model
compilation passes for both changed shared modules (player.c retains its
existing integral-conversion warning). Platform purity passes.

Similar-issue sweep checks entry.c's normal/auto-control paths, player.c's
vine/injury/flagpole/end-level/death callers and terminal_modes.c's automatic
walk caller. All still enter the single shared control routine; no platform
source changes. The full DOS and CMake source lists include the new owner.
Original-ROM boundary proof and three-executable P delivery remain pending;
all thirteen labels remain open and the count remains 628 / 1,992. Published
assets are unchanged from T31; these uncommitted changes are not a release.

## S1/P1: shared control owner and partial runtime delivery

This P delivers the reviewed structural separation and caller repairs above,
with all thirteen expected nodes still open. Expected S matches remain 13;
actual newly certified matches for this P are zero (628 / 1,992 unchanged).
S1 remains active until its original branch/caller proof is complete.

The prior twenty-two original entrance snapshots are unchanged. Against the
new shared core, 18 width comparisons match and 26 still fail. The vine
cases no longer differ in bounding control `$0499` or the four box bytes;
remaining differences include animation timer `$070c` and early scroll-position
write `$0755`. Normal/pipe cases still expose `$00eb`, and NextArea still
exposes its known silence-queue difference. These are retained failures,
not evidence that the entrance route is fully correct.

The new [production control checker](../../../test/player_control_snapshot_check.c)
reads actual PlayerCtrlRoutine child entries/returns from the prior read-only
ROM observer, binds local program data and runs the real native child chain.
Seven original boundaries across both widths produce fourteen comparisons;
all fourteen retain the documented `$00eb`, `$070c` and/or `$0755` differences.
No scratch exclusion is broadened and no child return is substituted in this
checker. The current evidence does not yet certify any S1 label.

All 63 shared sources compile under strict C90 on x86/x64. Independent caller,
production player-route, area-initialization and entry-chain tests pass in
both widths. Full OpenNT DOS16 linking succeeds with its existing warnings;
both Windows self-tests and two-second hidden-window/message probes pass.
DOS remains link-only with no owner-data or 486 runtime claim. Platform purity
and documentation governance pass. The three artifacts are refreshed:

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257357 | 567dfcc5db5f63f0d385ee411bef6fc16e5e1d78145096494e2bb8543fc9c572 |
| mysmb32.exe | 322723 | 7639f54632fa8d16ddcbdc60d91e83c1bcc186de3f537b5f4b4a5a52a2bb8cce |
| mysmb64.exe | 330128 | e3b10754d60ab7bdd44ae92591e559b4d4d3999f797b8647ad451ed8e5e72c39 |

Next within the same S: source-RAM control-entry fixtures for water/death,
priority, high-Y hole and cloud branches; original child-entry/return audit
and complete branch coverage. Do not absorb physics/OAM child repair or mark
callback/native tests alone as ROM equivalence. All temporary outputs remain
under the admitted ignored root; prior original recordings are reused read-only.

## S1/P2: original caller proof

Fifty controlled source-RAM routes enter PlayerCtrlRoutine naturally from
GameRoutines, PlayerEntrance, FlagpoleSlide, PlayerEndLevel or SideExitPipeEntry.
The read-only observer obtains actual return PCs and depths from the original
stack, records each immediate child's entry and return, and never mutates
execution. All fifty frame records equal both coverage-only and completely
unobserved runs. Raw evidence is 2,872,371 bytes under the 4 MB cap.

The [reproducible verifier](../../../test/verify_player_control_snapshots.py)
decodes every instruction in `$b0e9-$b1c6`, checks both outcomes of all 23
conditional branches and confirms all thirteen admitted entry labels execute.
Fifty [caller-boundary checks](../../../test/player_control_caller_check.c)
pass on each width: 100 matches over all 1,784 persistent bytes, including
both PPU mirrors. Each child identity/order and entry RAM are compared before
replaying the actual original child result. BoundingBoxCore also checks the
original object offset zero and native coordinate/control arguments.

The first 48 fixtures missed the mode-below-four priority branch and the
still-playing death-music branch. A natural SideExitPipeEntry route and a
death-event queue input exercise both; no PC/stack change or branch exclusion
was used. Coverage is complete only after these two source-reachable cases.

This establishes only the thirteen caller nodes' source contracts. The
production checker executes real native children against the same original
entry/return snapshots and retains **100 failing comparisons, zero matches**.
The movement-freeze input exposes the existing PlayerMovementSubs failure to
honor PlayerChangeSizeFlag (including ClimbSideTimer and downstream position
changes). Movement/state work remains with T23 S5 for the next source chain;
relative-position/OAM work remains with T16 S4; SetEntr remains planned S2.
No child algorithm is certified or newly repaired to improve these counts.

The operational track is P1's unchanged 63-source build, focused regressions,
DOS16 link and three artifacts. The added caller checker compiles as strict
C90 and passes all fifty cases on x86/x64. The reference recorder rebuilds;
all original/production checks above use it and the same P1 game objects.
The three packaged EXEs retain P1's listed hashes because no production
source changed in P2. This evidence is not full-player or whole-game parity.

S1 expected/actual caller matches: 13/13; global progress 628 -> 641 / 1,992.
Exact completed labels: `PlayerCtrlRoutine`, `DisJoyp`, `SaveJoyp`, `SizeChk`, `ChkMoveDir`, `SetMoveDir`, `PlayerSubs`, `PlayerHole`, `HoleDie`, `HoleBottom`, `ChkHoleX`, `ExitCtrl`, `CloudExit`.
The actual-child failures above receive no credit. Final review remains
pending under the current S1 packet.

## S1 closure review

The coordinator closes S1 with all thirteen received nodes proven within
their own caller contracts; none is transferred or left without disposition.
Source-order audit, 23 two-outcome branches, 100 original caller comparisons,
focused regressions, three builds/artifact hashes, purity and governance
evidence were reviewed. Actual-child failures remain with their explicitly
recorded existing owners and give no child credit. Global count is 641.

## S2 admission: vine and pipe transition chain

Scope/expected, all open: `Vine_AutoClimb`, `AutoClimb`, `SetEntr`, `VerticalPipeEntry`, `MovePlayerYAxis`, `SideExitPipeEntry`, `ChgAreaPipe`, `ChgAreaMode`, `ExitCAPipe`, `EnterSidePipe`, `RightPipe`.
Baseline 641 / 1,992, unique scope eleven, expected eleven, maximum 652.
Transfer-135 accepts these from T23 S5. Original source lines 5691-5753
span Vine_AutoClimb through RightPipe. Entry routes are GameRoutines modes
1/2/3, PlayerEntrance, CloudExit and NextArea; successors are AutoControlPlayer
and ScrollHandler with their existing scoped proofs and child limitations.

Create one shared game/player_transition.c owner. Restore the upward-control
override, SetEntr -> ChgAreaMode handoff, wrapping Y addition, scroll-before-
destination reads, unconditional area-timer decrement including zero-to-ff,
post-child timer reads, disable-screen increment and task/sprite-0 clears.
EnterSidePipe selects forced right/zero input from the low X nibble after
setting horizontal speed. Replace duplicate owned bodies and expose the
common transition entry; do not repair movement, terrain, rendering or music.
No child receives completion credit from caller extraction.

ROM logic track: exact source predicates, byte wraps and write/call order;
source-RAM ordinary-NMI routes and read-only original boundaries. Operational
track: exhaustive transition timer/coordinate/state tests with mutating child
callbacks, existing control/entry/scroll regressions, strict C90 x86/x64,
OpenNT DOS16, platform purity and three artifact results per implementation P.
Shared child failures remain explicit, never converted into full-game proof.

Use the existing owner-local ROM/listing only as non-redistributable research
inputs, with no third-party implementation import. Temporary products stay
under ignored build/m2-t32-s2, raw budget 4 MB, twenty-second recorder limit,
S2 cleanup owner through T review. Existing owner authorization covers all
three local EXEs; DOS remains link-only. Similar-issue sweep: every SetEntr,
pipe exit, area-mode and Y-axis caller, including NextArea; platform sources
remain host adaptation only.

## S2 implementation checkpoint

One shared player_transition.c now owns all eleven admitted labels. Duplicate
vine/pipe/Y-axis bodies are removed from player.c. NextArea calls the shared
ChgAreaMode at its original call position; its remaining music/area algorithm
is not repaired or certified here. The NextArea zero-silence discrepancy
remains planned S4 work. CloudExit and both original entrance callers use the
same SetEntr and movement entries through their existing declarations.

The implementation restores JoypadOverride before forced-up control, the
SetEntr/pipe shared transition and sprite-0 clear, unconditional wrapping
ChangeAreaTimer decrement, and destination/timer reads after child calls.
No host code changed. The [transition test](../../../test/player_transition_chain_smoke.c)
checks all 65,536 low-Y/addend pairs, all 65,536 high/low-Y vine pairs, every
timer with the warp/area branches, and all 65,536 horizontal-position/timer
pairs. Mutating scroll/auto-control children verify returned selectors and
timer values are read after the child, not cached before it.

Strict C90 tests pass on x86/x64: transition chain, control chain, entrance
chain, production player-route and area initialization (ten executions).
The three changed production modules compile on both widths; the new owner
also compiles with OpenNT large model. Platform purity passes. CMake and the
full DOS source list include the shared owner. Original-ROM branch/boundary
proof, full three-target builds and P delivery are still pending. All eleven
nodes remain open at 641 / 1,992; published assets remain S1/P1.

## S2 P1 original transition proof

The preceding checkpoint is superseded by the completed chain proof and
three-target build. Original-ROM ordinary-NMI fixtures exercise 28 routes:
six vine, eight side-pipe, twelve vertical-pipe and two upward entrance
Y-movement routes. The observer reads original entry/return boundaries and
immediate child calls; it does not change PC, stack, ROM or executing state.
Observed, coverage-only and unobserved frame outputs agree for every route.
Raw local evidence totals 950,079 bytes within the admitted 4 MB budget.

| Original node | Address | Shared C semantic obligation proved |
| --- | --- | --- |
| Vine_AutoClimb | B1C7 | High-Y/low-Y exit predicate, otherwise forced-up control |
| AutoClimb | B1D1 | Override 8, climbing state 3, AutoControlPlayer argument 8 |
| SetEntr | B1DD | Alternate entrance 2 before common area-mode change |
| VerticalPipeEntry | B1E5 | Low-Y increment, scroll, then warp/area reads |
| MovePlayerYAxis | B200 | Wrapping low-byte addition without high-Y carry |
| SideExitPipeEntry | B206 | EnterSidePipe returns before timer and mode 2 transition |
| ChgAreaPipe | B20B | Unconditional wrapping decrement; only zero changes area |
| ChgAreaMode | B213 | Increment disable-screen, clear mode task then sprite-0 flag |
| ExitCAPipe | B21E | Return without additional writes |
| EnterSidePipe | B21F | Speed 8 before testing low X nibble; aligned X clears speed/input |
| RightPipe | B22E | AutoControlPlayer receives selected forced-right/zero input |

All six conditional branches have both outcomes and all eleven labels execute.
The [caller checker](../../../test/player_transition_caller_check.c) passes
56 comparisons across x86/x64, covering child identity/order/argument,
all 1,784 persistent RAM bytes at child entry and caller return. Only scratch
bytes 0-7 and the hardware stack are excluded; PPU mirrors are included.
The checker replays observed original child returns, so its proof is scoped
to these callers, not the native child algorithms.

The separate [production checker](../../../test/player_transition_snapshot_check.c)
retains 30 matches and 26 failures. Matches cover the early vine exit, all
vertical-pipe routes and both direct Y-movement routes; failures cover the
other five vine routes and eight side-pipe routes on both widths. Player
movement and relative/output dependencies remain with T23 S5 and T16 S4;
their failures are not suppressed or credited. No full-player, whole-frame
or whole-game equivalence is claimed by this boundary proof.

Reproduce the original observation using the reference recorder's
`--fixture=t32-transition=N` for N=0..27, `--transition-snapshot` and
`--control-children`, followed by the
[verification harness](../../../test/verify_player_transition_snapshots.py).
Owner ROM, original traces, fixtures and generated data stay below ignored
build outputs and are not committed. Tests contain neutral harness logic.

Operational evidence: the five focused tests listed above pass on both
widths, all 64 shared production units build under strict C90 on x86/x64,
and the full OpenNT DOS16 link succeeds. Both Windows self-tests pass;
bounded hidden-window probes create a responsive window without user input.
These startup probes do not establish playability or performance. DOS16
remains link-only, without owner PRG/CHR/title binding or 486 qualification.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 257341 | 8919fa728f0bd2735015c40e151d123cbb7ea092043eca97e2f5c1ddfbac2dae |
| mysmb32.exe | 323093 | 821a1e589abac163c27e4cc3b35ee3dfd31fee944d5a59ed6e9f787f746938f5 |
| mysmb64.exe | 330532 | 157dfc158c36d43e7ab473badb0effd1c02857edf4f00289b91817663957fb5a |

Similar-issue review covers every production vine/pipe/Y-axis/SetEntr and
area-mode caller. The duplicate implementations were removed; NextArea uses
the shared mode transition while its music discrepancy remains planned S4.
No platform source changed and platform-purity verification passes.

S2 expected/actual caller matches: 11/11; global progress 641 -> 652 / 1,992.
Exact completed labels: `Vine_AutoClimb`, `AutoClimb`, `SetEntr`, `VerticalPipeEntry`, `MovePlayerYAxis`, `SideExitPipeEntry`, `ChgAreaPipe`, `ChgAreaMode`, `ExitCAPipe`, `EnterSidePipe`, `RightPipe`.
No child receives credit. Final review and S3 admission remain pending.

## S2 closure review

All eleven received caller nodes have their own source/ROM and operational
proof. Expected/actual matches are 11/11; none needs transfer. The coordinator
reviewed production and observer changes, six two-outcome branches, 56 caller
comparisons, the 30/26 actual-child match/failure result, focused native tests,
three builds/artifacts, platform purity and passing progress/ledger/document
gates. S2 closes at 652 / 1,992. The retained child failures do not receive
credit and remain under their existing owners. T32 remains open.

## S3 admission: size injury death and palette chain

Scope/expected, all open: `PlayerChangeSize`, `EndChgSize`, `ExitChgSize`, `PlayerInjuryBlink`, `ExitBlink`, `InitChangeSize`, `ExitBoth`, `PlayerDeath`, `DonePlayerTask`, `PlayerFireFlower`, `CyclePlayerPalette`, `ResetPalFireFlower`, `ResetPalStar`, `ExitDeath`.
Baseline 652 / 1,992; fourteen unique labels, expected fourteen, maximum 666.
Transfer-136 accepts the exact set from T23 S5. Source lines 5757-5830 and
addresses B233-B2A3 cover PlayerChangeSize through ExitDeath. GameRoutines
selects size/injury/death/flower entries; their common timer/palette exits
share this chain. PlayerCtrlRoutine is an existing child with retained
movement/output gaps, not a new implementation receipt. Star-palette callers
use the same shared reset/cycle primitives; no duplicate algorithm is added.

Use a shared game/player_modes.c owner. Preserve exact TimerControl equality
and unsigned threshold branches, InitChangeSize guard and write order,
DonePlayerTask resets, PlayerCtrlRoutine calls, palette masks and frame shift.
Audit all existing size/injury/death/flower/star palette callers; extract or
replace only owned semantics, with no movement, terrain, audio or OAM repair.

ROM logic track compares original predicates, reads/writes, entry/exit and
child order on ordinary-NMI mode routes with source-RAM boundary fixtures.
Reuse the existing control/transition observer mechanism and keep real-child
failures separate from scoped caller evidence. Operational track covers all
byte timer/palette/size branches, existing player regressions, strict C90
x86/x64, OpenNT DOS16, platform purity and three EXEs once per implementation P.

Existing owner-local ROM/listing are non-redistributable research inputs;
no third-party translation is imported. Generated evidence stays in ignored
build/m2-t32-s3, capped at 4 MB raw and twenty seconds per recorder run. S3
owns cleanup through T review. DOS delivery remains link-only. Before credit,
each exact label needs both evidence tracks; inherited child failures remain
visible and receive no credit. Admission checks confirm 652, scope/expected
14/14, maximum 666 and accepted responsibility for every label.

## S3 P1 original timer-state proof

The shared player_modes.c owns all fourteen admitted labels. Size, injury,
death and flower bodies are removed from player.c. The GameEngine star caller
uses the same CyclePlayerPalette and ResetPalStar leaves as the flower route;
the leaves preserve non-palette attribute bits and the original scratch write.
No platform code changed. Existing physical input mappings are unaffected.

The source audit found a real omitted branch: injury's CMP F0 / BCS ExitBlink
retains Z into BNE ExitBoth. Exactly F0 falls into InitChangeSize; values above
F0 return. The former C `>= F0` return incorrectly skipped this fallthrough.
The implementation now shares guarded InitChangeSize between injury and size.
The disassembly's unconditional-branch comment is not authoritative over its
instructions; an initial mistaken interpretation was rejected by ROM coverage.

| Original node | Address | Proved semantics |
| --- | --- | --- |
| PlayerChangeSize | B233 | F8 invokes guarded initialization |
| EndChgSize | B23D | Only C4 invokes DonePlayerTask |
| ExitChgSize | B244 | Return preserves other timer values |
| PlayerInjuryBlink | B245 | Unsigned F0 gate, C8 completion, otherwise PlayerCtrlRoutine |
| ExitBlink | B253 | Above F0 returns; exactly F0 falls into InitChangeSize |
| InitChangeSize | B255 | Existing flag guards animation clear, flag increment and size XOR |
| ExitBoth | B268 | No extra state writes |
| PlayerDeath | B269 | Below F0 calls PlayerCtrlRoutine; otherwise returns |
| DonePlayerTask | B273 | Clear TimerControl before selecting subroutine 8 |
| PlayerFireFlower | B27D | C0 completion; otherwise FrameCounter shifted twice |
| CyclePlayerPalette | B288 | Low two color bits to scratch, merge with upper attributes |
| ResetPalFireFlower | B297 | DonePlayerTask before ResetPalStar |
| ResetPalStar | B29A | Clear palette bits, retain upper six attributes |
| ExitDeath | B2A3 | Return without extra writes |

Twenty-two ordinary-NMI routes cover size, injury, death, flower and the two
star-palette entries. The read-only observer reuses the control/transition
boundary mechanism; it reads original stack return addresses without patching
ROM, PC, stack or running state. All eight conditional branches have both
outcomes and every received node executes. Observed, coverage-only and
unobserved frame outputs agree. Raw local evidence is 705,870 bytes, within
the admitted 4 MB budget and twenty-second per-run limit.

The [shared checker](../../../test/player_modes_snapshot_check.c) is built in
two explicit modes. Caller mode checks the real child boundary and replays
its observed original return; all 44 x86/x64 comparisons match over 1,784
persistent RAM bytes. Only scratch 0-7 and hardware stack are excluded.
Production mode calls actual native children: 34 match, ten fail. The failing
five routes are injury EF/C7/00 and death EF/00, on both widths. Existing
PlayerCtrlRoutine descendants still differ in animation/movement state;
their T23 S5 and output dependencies retain their prior status and ownership.
No child credit or complete gameplay claim follows from scoped caller proof.

Reproduce with reference `--fixture=t32-modes=N` for N=0..21,
`--modes-snapshot` and `--control-children`, then the
[verification harness](../../../test/verify_player_modes_snapshots.py).
Original material, recorded RAM/frames and generated data remain local ignored
outputs. Only project-owned harnesses and neutral conclusions are tracked.

Operational evidence: the modes, engine-tail, control, transition and entrance
focused tests pass on x86/x64 (ten executions). Modes tests exercise every
timer/flag pair for size, every flag/size byte pair for injury F0, all injury
and death timers, and all attribute/frame pairs for palette behavior.
Mutating PlayerCtrlRoutine callbacks verify child-return state is preserved.
All 65 shared game units build as strict C90 on both Windows widths, both
self-tests pass, and the full OpenNT DOS16 link succeeds. Hidden-window probes
confirm creation and message responsiveness for two seconds per width; this
is not playability/performance evidence. DOS remains link-only without owner
program/title binding or physical 486 validation. Platform purity passes.

| Artifact | Bytes | SHA-256 |
| --- | ---: | --- |
| mysmb16.exe | 258013 | 24ffbac59909da1091c0d78928fe028a6c25cc470e5608d7315253591d4d1a75 |
| mysmb32.exe | 324076 | 87d920da2c3806210998a1d9d3fd01923295ba5eddfa869baddaaa89c84cf7eb |
| mysmb64.exe | 331035 | 68fbdc6aa1baafdfa534a35db50abe53f6c050a2be6f9dc7d794b048ebb3c706 |

Similar-issue sweep examined all size/injury/death/flower entries and both
GameEngine star palette calls. All owned bodies have a single shared owner;
no duplicated palette algorithm remains at these callers. Original size/
injury/death thresholds and palette masks were audited as one chain.

S3 expected/actual caller matches: 14/14; global progress 652 -> 666 / 1,992.
Exact completed labels: `PlayerChangeSize`, `EndChgSize`, `ExitChgSize`, `PlayerInjuryBlink`, `ExitBlink`, `InitChangeSize`, `ExitBoth`, `PlayerDeath`, `DonePlayerTask`, `PlayerFireFlower`, `CyclePlayerPalette`, `ResetPalFireFlower`, `ResetPalStar`, `ExitDeath`.
No child receives credit. Final review and S4 admission remain pending.

## S3 closure review

All fourteen received labels have their own source/ROM and operational proof;
expected/actual matches are 14/14, with no transfer. Review confirms the F0
injury fallthrough repair, eight two-outcome source branches, 44 original
caller matches, 34 actual-native matches and ten retained child failures.
Focused tests, three target builds/artifacts, purity, closure ledger and
documentation/progress gates pass. S3 closes at 666 / 1,992. Unfinished
movement/output children retain their prior owners; T32 remains open.

## S4 admission: flagpole and end-level chain

Scope/expected, all open: `FlagpoleSlide`, `SlidePlayer`, `NoFPObj`, `Hidden1UpCoinAmts`, `PlayerEndLevel`, `ChkStop`, `InCastle`, `RdyNextA`, `NextArea`, `ExitNA`.
Baseline 666 / 1,992; ten unique labels, expected ten, maximum 676.
Transfer-137 accepts these from T23 S5. Source lines 5835-5895 contain the
flagpole, end-level, hidden-1up threshold table and shared NextArea chain.
GameRoutines modes 4/5 and entry/area callers precede it. AutoControlPlayer,
LoadAreaPointer and ChgAreaMode are successor boundaries; existing child
limitations remain visible without broad movement/parser repair.

Use a shared game/player_end_level.c owner and remove duplicate owned bodies
from player.c/terminal_modes.c. Restore special enemy-slot identity, sound
queue transfer/clear, forced-down/zero input, post-control Y/scroll/collision
reads, star-flag and sprite-priority state, level/world coin threshold, and
NextArea's pointer/timer/mode/halfway/silence call and write order. Bind the
original threshold table through the existing owner-local program-data path.
No platform gameplay code or new generic emulation layer is permitted.

ROM track: audit every original table byte, branch, RAM read/write and child
order, then observe ordinary-NMI flagpole/end-level/NextArea boundaries with
controlled source-RAM cases. Keep actual-child comparisons separate from
caller-only proof. Operational track: bounded input/threshold/queue tests,
mutating children for post-return reads, prior player-chain regressions,
strict C90 x86/x64, full DOS16 link, purity and the three packaged EXEs.

Use the existing owner-local ROM/listing as non-redistributable research;
no external implementation import. Generated evidence stays in ignored
build/m2-t32-s4, bounded to 4 MB raw, twenty seconds per recording, with S4
cleanup ownership through T review. DOS remains link-only. Similar-issue
sweep covers all flagpole/end-level/NextArea callers and all writers of the
owned sound, area-mode, priority and hidden-1up state. Admission gate must
confirm exact scope/expected 10/10, baseline 666 and maximum 676. The later
T32 integrated review is still required after this final planned chain.
