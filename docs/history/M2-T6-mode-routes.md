# M2 T6 Mode Routes

## Outcome

T6 translates the native mode transitions for small-player death, life loss,
restart, two-player record exchange, game over, pipes and Warp Zone targets,
flagpole/axe completion, VictoryMode, and next-world transfer. Presentation
of bridge tiles and text remains an adapter concern; the C90 core owns every
state handoff.

## Evidence

- Owner-local source provenance covers `PlayerLoseLife`, `TransposePlayers`,
  `GameOverMode`, `ContinueGame`, `HandlePipeEntry`, `FlagpoleSlide`,
  `HandleAxeMetatile`, `PlayerEndLevel`, and `VictoryModeSubroutines`.
- `mode_smoke` covers life/halfway recovery, Game Over timing, solo title
  return, second-player continuation, level-area transfer, Warp Zone middle
  pipe target selection, and next-world transition.
- The final increment passed ROM-free CTest (21 tests), owner-local CTest
  (23 tests), Win32 x64/x86 builds, OpenNT large-model core compilation,
  documentation governance, and `git diff --check`.

## Audit And Transfer

The mode sweep repaired the previously unrepresented small-player death path:
all translated damaging object routes now converge on the original
`InjurePlayer`/`KillPlayer` ownership. No host input or renderer code enters
`src/game`. Event-music and effect queues are preserved as RAM commands but
their command semantics transfer to T7.
