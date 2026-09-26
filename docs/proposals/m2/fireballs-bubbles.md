# M2 candidate: Fireballs and bubbles

## Status

**M2 T20 closed after S4/P1 transfer.** The responsibility ledger accepted T20/S4 as
the receiving implementation subtask for the 24-node fireball, bubble,
timer, and warp-entry group. Historical S1-S3 records remain evidence only;
they no longer receive implementation work. OAM scratch/output remains
delegated to T16, and shared movement/collision primitives remain delegated
to T17.

## ROM scope

ROM lines 6298-6729: fireball/bubble dispatch, setup/core, relative position, offscreen bits and background/enemy collision.

## Existing-code disposition

Extract fireball code from objects.c; remove world-distance offscreen shortcuts and keep state in shared RAM.

## Graph contract

Called before enemy slots; consumes player/collision/enemy state and writes fireball RAM/OAM/audio.

## Admission S plan

1. **S1 complete (P1-P2)** - Establish the source owner boundary: extract fireball/bubble dispatch and its named labels from `objects.c` into `src/game/fireball/` without behavior changes; map every RAM field, helper and cross-slice call.
2. **S2 active (P1-P4)** - Translate spawn/page carry, the Sfx_Fireball queue write, movement/gravity and the relative-position/offscreen-bit call sequence, consuming T16/T17 primitives rather than duplicating them.
3. **S3 planned** - Translate background/enemy collision and clear/effect branches.
4. **S4 active (P1)** - Own the ledger-accepted 24-node group from
   `ProcFireball_Bubble` through `WarpZoneObject`; translate or revalidate
   each source branch and hand unresolved cross-slice nodes to their existing
   receivers.

## Acceptance

Lifetime comes from ROM offscreen bits and collision branches, never a host distance test.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.

## S1/P1 admission record

The existing implementation interleaves `ProcFireball_Bubble`, `FireballObjCore`, fireball collision, and bubble calls with unrelated block/item/enemy owners in `objects.c`. S1/P1 moved the fireball core to an explicit game owner and declares its call dependencies: T16 supplies relative/offscreen/OAM writes; T17 supplies common gravity, horizontal movement, bounding-box and block-buffer primitives; T19 retains enemy-slot scheduling. No state transition, sound value, collision threshold, or renderer behavior may change in S1. BubbleCheck remains an explicit dependency in `fireball/bubble.c` for the next S1 packet; S2 begins only after the complete T20 owner boundary compiles and has the three-target artifact baseline.

## S1/P1: fireball core source boundary

`FireballObjCore` and its current setup/movement/collision call sequence now live in `src/game/fireball/fireball_core.c`, declared by `src/game/fireball/fireball.h`. `GameEngine` reaches it through this owner API instead of `objects.h`. The existing enemy-hit effect is named as an explicit cross-module call and the existing bubble step is named as an explicit temporary T20 dependency; no algorithm or state transition changes in this structural P. All three targets and the reference trace are required before the P is closed.
## S2/P1: fireball spawn sound queue

The `ProcFireball_Bubble` creation branch now writes the original `Sfx_Fireball` literal `$20` to `Square1SoundQueue/$00ff` after every source eligibility check and immediately before allocating the fireball state. The regression proves a newly valid fireball queues `$20`, while a held B button does not queue it again. This is shared C core behavior across all targets.
## S2/P2: fireball throw-timer handoff

At the same original spawn point, `PlayerAnimTimerSet/$070c` now transfers to `FireballThrowingTimer/$0711`, then its decremented value transfers to `PlayerAnimTimer/$0781`. The focused fireball regression proves `$0711 = 6` and `$0781 = 5` from an input value of 6, alongside the S2/P1 one-shot sound-queue check. This remains shared game-core behavior; neither Win32 nor DOS owns it.

## S2/P3: source-label cutover

`ProcFireball_Bubble` now has its own shared C90 owner, `src/game/fireball/fireball_spawn.c`; `FireballObjCore` remains in `fireball_core.c` and calls the spawn owner before its source-order two-slot loop. The old object-owner fireball API has no remaining production or test consumer. This is a body-preserving extraction: movement/gravity, offscreen/OAM, and collision calls remain explicitly delegated to T17/T16 at their original label boundaries. The focused fixture now initializes every RAM input read by the original spawn and offscreen routines, so x86 and x64 execute the same branch rather than inheriting host stack bytes.

## S2/P4: consume shared movement primitives

`FireballObjCore` now preserves its source `TXA; ADC #$07` object selection by passing offsets 7 and 8 to the T17 common `ImposeGravity` and `MoveObjectHorizontally` implementations. Its duplicate C arithmetic has been deleted. The delegated primitives use the original common SprObject bases, so offset seven lands exactly on the fireball fields; setup, relative/offscreen, bounding-box, collision, erase and draw order are unchanged.
## S2/P5: source offscreen boundary proof

The focused shared-core fixture now calls `GetFireballOffscreenBits` directly against the ROM screen window `$071a/$071b/$071c/$071d`. It proves the four source boundary bytes: world anchors `$00/$08/$f7/$ff` yield `$08/$00/$03/$07`. Thus `FireballObjCore` retains `$08` through `$f7` only when its existing `$cc` mask permits it; no screen-width or host-coordinate rule participates. The historic duplicated window setup in the fixture was also removed.

## S3/P1: background collision branch proof

The same fixture now directly proves `FireballBGCollision`'s source probe `(X + $04, (Y + $08) & $f0) - $20` and its four branch outcomes: a solid first contact sets speed `$fd` and the bouncing flag; the next solid contact sets state `$80` and `Sfx_Bump`; a non-solid `$c2` clears a stale bouncing flag; and a status-bar Y position clears that flag without probing. These are shared game-core transitions consumed identically by DOS16, Win32 x86, and Win32 x64.
## S3/P2: enemy-hit audio queues

`HandleEnemyFBallCol` used invented queue values. The ROM writes `$80` (`Sfx_BowserFall`) to `Square2SoundQueue/$00fe` when the final Bowser hit reaches `HurtBowser`, then reaches `EnemySmackScore`, which writes `$08` (`Sfx_EnemySmack`) to `Square1SoundQueue/$00ff`. Ordinary eligible enemy hits only perform the latter `$08` write. The shared collision owner now follows those two source writes; the Bowser and generic collision fixtures assert them separately. `FireballBGCollision` retains its independent `$02` bump sound.
## S3/P3: complete source enemy-slot scan

`FireballEnemyCollision` now owns the complete ROM loop, starting at slot four and descending through slot zero.  A source collision sets `Fireball_State` to `$80`, immediately calls `HandleEnemyFBallCol`, then continues scanning; it does not return after the first hit.  The focused collision fixture places two eligible enemies in the same fireball box and proves both receive the `$22` defeated-state handoff in one even frame.  `ProcFireball_Bubble` also now follows its source instruction order: choose and test the counter-selected slot before Y/crouch/climbing eligibility, and increment `FireballCounter` only after the timer writes.

## S4/P1 admission: ledger-accepted fireball and bubble entry group

The active implementation scope is exactly `ProcFireball_Bubble`,
`ProcFireballs`, `ProcAirBubbles`, `BublLoop`, `BublExit`,
`FireballXSpdData`, `FireballObjCore`, `RunFB`, `EraseFB`, `NoFBall`,
`FireballExplosion`, `BubbleCheck`, `SetupBubble`, `PosBubl`, `MoveBubl`,
`Y_Bubl`, `ExitBubl`, `Bubble_MForceData`, `BubbleTimerData`,
`RunGameTimer`, `ResGTCtrl`, `TimeUpOn`, `ExGTimer`, and `WarpZoneObject`.
Its incoming baseline is 3 / 1,992 with no forecast match claim. The current
P restores the source `PlayerStatus` gate before both fixed fireball slots:
non-fiery status branches directly to `ProcAirBubbles`. It also keeps the
post-gate fire-button checks in the creation helper, so the source label has
one shared-game owner. Collision, OAM/offscreen, and later whirlpool/flagpole/
jumpspring/vine nodes remain with T17/S6, T16/S4, and T22/S5 respectively.
Each following P must record its exact node subset, source branch/write audit,
focused tests, ROM-route result or blocker, three local target artifacts, and
an accepted transfer for every unresolved node.

## T20 closure

No node became ROM-match complete in S4/P1. All 24 unfinished labels were
transferred by accepted ledger events to M2 T21 S6, which is the fireball,
bubble, timer and Warp closure group. T20 therefore retains no unfinished
custody.
