# M2 T32: Player control and mode chains

## Status

T32 admitted in source order after closed T31. S1 alone is active.
Task baseline 628 / 1,992. The source-range plan lists 49 open labels;
48 are intended matches here, maximum 676. PlayerMovementSubs begins the
next complete movement-state chain at line 5899; it retains T23 S5 custody
until T33 admission instead of receiving a one-label partial implementation.
No friction/jump implementation is claimed merely from the old range title.

## Exact chain plan

Every row below lists open nodes in original source order. The existing
receiver is T23 S5. Only S1's thirteen labels transfer now; later S rows
are unadmitted plans. Each S carries source audit, shared-C implementation,
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
