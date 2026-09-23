# M2 T5 Object Routes

## Outcome

T5 translates the admitted object ownership route into the portable C90 core:
blocks and coins, power-ups and fireballs, score/timer state, ordinary and
special enemies, projectiles, firebars, Bowser/flames, and platform objects.
The core has no emulator, renderer, or host-input dependency.

## Evidence

- Source provenance is the owner-local reconciled SMB1 program's object roots
  `$aa0f-$b3c2`, `$ba55-$c2ff`, and `$cxxx-$e3xx`; platform dispatch is
  `RunLargePlatform` through `RunSmallPlatform`. The listing and ROM remain
  local research inputs only.
- Focused project-owned smoke programs exercise collision outcomes, power
  state, ordinary/special enemy motion, firebars, Bowser/flames, and platform
  initialization, fractional lifts, rider transfer, horizontal scroll
  handoff, and paired balance decks.
- The final platform increment passed ROM-free CTest (20 tests), owner-local
  CTest (22 tests), Win32 x64/x86 builds, and the OpenNT large-model core
  compile. Documentation governance and `git diff --check` also passed.

## Audit And Transfer

The portable game layer was swept for object dispatches and host/platform
imports: object routes remain under `src/game`; `windows.h` remains confined
to the Win32 adapter. OAM-only platform ropes and Bowser's rear half are
renderer work, while bridge collapse belongs to the mode route. Death,
restart, warp, continue, and completion state transitions transfer to T6;
audio command ownership transfers to T7.
