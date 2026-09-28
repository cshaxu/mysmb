# M2 candidate: Player route

## T32 S1 movement dependency receipt

The coordinator records a concrete source mismatch under existing T23 S5
PlayerMovementSubs custody: the native movement child lacks the original
PlayerChangeSizeFlag early return after PlayerPhysicsSub, so frozen movement
still changes ClimbSideTimer, motion forces and position. Fifty source-RAM
control fixtures retain all production-call failures while independently
proving caller contracts. Repair with the complete movement-state chain in
source order; no extra dependency is admitted into T32 S1. See the
[caller proof and retained failures](player-control-modes.md#s1p2-original-caller-proof).

## T31 S4 evidence receipt for existing T23 S5 custody

The coordinator records additional failing-route evidence for the existing
PlayerCtrlRoutine and NextArea responsibility; no node changes receiver and
no implementation is admitted by this receipt. See the
[entry-chain checkpoint](../../history/M2-T31-game-dispatcher.md#s4-original-boundary-checkpoint).
The ordinary NMI entrance fixtures retain full production-call failures:
low-Y/pipe control produces `$00eb=$00` instead of `$13`; vine routes differ
in animation, bounding-box and movement fields; NextArea leaves `$00fc=$00`
instead of the original silence command `$80`. The vine differences remain
child-chain findings pending per-node attribution, not claimed root causes.
Repair in source order and rerun the production entrance checker against the
same original snapshots; caller callback success cannot close these gaps.

## Status

**M2 T23 active — S1/P1 and S2/P1 complete; S2 remains active.**

## ROM scope

ROM lines 5583-6297: PlayerCtrlRoutine, movement/state/size, pipe/vine/scroll interaction and player-originated block actions.

## Existing-code disposition

Audit player.c and player code in game.c/objects.c; retain fixed-width arithmetic/RAM offsets only with label proof.

## Graph contract

Consumes latched input, block buffer and object state; writes player state, scroll, block events, OAM/audio queues.

## Admission S plan

1. **S1 after admission** - Create label-to-function/write map for controller partition, state and movement.
2. **S2 after admission** - Translate horizontal/vertical physics, acceleration, gravity and page carry.
3. **S3 after admission** - Translate player/background/head collision and block handoffs.
4. **S4 after admission** - Translate size, injury, pipe, vine, entrance and scroll branches.
5. **S5 after admission** - Compare walk/jump, walls, hidden blocks, powerups, pipes, damage/death and scrolling.

## Acceptance

Player state, collision results, scroll, block events, OAM and audio agree with every approved ROM route.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
## S1/P1: ImposeFriction label and write map

`ImposeFriction` at listing lines 6252–6288 is a shared-game owner.  It reads
`Left_Right_Buttons & Player_CollisionBits`, `$0057` (`Player_X_Speed`),
`$0705` (`Player_X_MoveForce`) and `$0701/$0702` (friction addends), then
writes only `$0057`, `$0705` and `$0700` (`Player_XSpeedAbsolute`).  Its four
source branches are fixed:

1. no direction plus zero speed: write absolute speed zero;
2. no direction plus positive speed: `RghtFrict`, subtract toward zero;
3. no direction plus negative speed: `LeftFrict`, add toward zero;
4. held direction: Right uses `LeftFrict` (add/right acceleration), Left uses
   `RghtFrict` (subtract/left acceleration).

The sole implementation owner is `src/game/player.c`:
`mysmb_player_impose_friction`.  It is reached by `PlayerMovementSubs` and
never by a platform adapter.  S2/P1 may change only this selector and the
player-route regression; no collision, OAM, renderer, DOS, or Win32 code is in
scope.

## S2/P1 acceptance

A ROM-free regression must prove all four branches with fractional borrow/carry:
positive no-input slows leftward arithmetic toward zero, negative no-input
slows rightward arithmetic toward zero, and held Left/Right retain their source
acceleration paths.  The x86/x64 and OpenNT builds must consume the same shared
source; the three packaged executables are refreshed for the implementation
packet.
## S2/P1: released-direction friction

`mysmb_player_impose_friction` now translates the `ImposeFriction` selector
without merging released input with Left acceleration.  With no effective
direction, a positive `$0057` selects `RghtFrict` (subtraction) and a negative
`$0057` selects `LeftFrict` (addition); both converge on zero.  Held Right
continues to select addition and held Left subtraction, including the source
right-precedence behavior for both bits.

`test/player_friction_smoke.c` asserts byte-level speed, fractional force and
absolute speed for all four paths.  The player route, friction, DOS16 input,
and Win32 self-tests pass on x86 and x64.  The DOS16 link succeeds with the
known interactive `OLDNAMES.LIB` warning.  A full x64 CTest run has three
pre-existing T17 collision-fixture failures (`hazard-collision`, `bullet-bill`,
`hammer-bro`): their fixtures omit the player primary bounding box after T17
made PlayerCtrlRoutine its sole runtime producer.  They are not modified by
this T23 packet and remain an explicit T17 follow-up, rather than a reason to
restore the removed object-side box write.

Refreshed artifacts: `mysmb16.exe`
`4485D9BAA0FD7488130C91BE880BF7EA5A8A3FCE984BEED822C48D75A02DC80D`,
`mysmb32.exe` `A5A3D6DB2124387DEC73C44E8C88BF3A4A347D4D5C029DFBA22A2FEA3931F392`,
and `mysmb64.exe` `A6C357AE988CFC126AC6176AF1E70F4A13245582B0596FBEBC11C1A0FD4E5417`.
## Chain-delivery governance amendment

The fixed "map, migrate, equivalence audit, operational test, closure" S
sequence in this proposal is historical planning evidence only.  For the next
admission or continuation in this task, one S must deliver one bounded,
contiguous ROM control/data chain: it records the exact labels in source order,
its entry and exit, one shared C owner, predecessor/successor dependencies,
and one ROM route that exercises the chain.  Mapping, the shared-C repair when
needed, node-by-node control/read/write/table/call-order comparison, and the
operational proof belong to that same S.

The node inventory and ledger still retain a separate row and final
completion disposition for every label.  A chain P runs one common ROM replay,
focused tests, x86/x64 builds, DOS16 link, platform-purity check, and refreshes
the three required local target artifacts.  T closure adds only the
cross-chain route matrix and integrated three-target regression.  It must not
recreate those gates for each leaf.  A chain may not cross an unadmitted
dependency, a different shared-owner boundary, or a branch family requiring a
different ROM route.  The binding authority is
[the M2 chain-delivery rule](../../rules/EXECUTION.md#m2-chain-based-s-delivery).
