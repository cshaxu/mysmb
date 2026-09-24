# M3 T1 Neutral Render-Command Seam

## Outcome

The portable C90 game layer now produces a deterministic neutral frame made
of thirty name-table tile rows followed by visible player and enemy actor
commands.  The Win32 composition root builds that frame after initialization
and after every game tick, then consumes the first actor command for the
temporary gameplay marker.  This establishes one read-only presentation
boundary without altering the validated native gameplay route.

## Ownership And Contract

- `src/game/render.h` defines the fixed-capacity command and frame ABI;
  commands carry only kind, screen position, row extent/data offset, and a
  neutral actor identity.
- `src/game/render.c` reads the existing name table and translated player and
  enemy slot state.  World positions are converted against the current screen
  origin and objects outside the current 256-pixel view are omitted.
- The renderer neither writes game RAM nor carries handles, input state,
  terminal control sequences, ROM bytes, or platform conditionals.
- The command sequence is a stable tile-row prefix followed by player and
  active visible enemy slots in slot order.  It can therefore be consumed by
  Win32 now and by a later VGA or colored-text adapter without another logic
  route.

## Fixed-Input Evidence

`mysmb.render-smoke` supplies a known name-table value, an active player, and
one active enemy.  It verifies row count, row-data offsets, actor order,
screen-relative positions, identities, and offscreen culling.  The existing
core smoke additionally verifies the initialized title-frame prefix.  These
checks exercise no owner ROM material.

## Similar-Issue Sweep

The closure sweep searched the game, Win32 adapter, and tests for render
construction, direct Win32 game-RAM access, and calls to the game tick.  The
new game renderer has no `game->ram` assignment.  The only production tick
root remains the Win32 step routine; its two direct mode reads select title
or gameplay presentation and do not mutate state.  The Win32 paint routine
now bounds-checks the actor-command index before drawing.  No duplicate frame
builder, host-owned gameplay mutation, or protected asset reference was
found.  Further visual consumption of tile and actor commands is deferred to
M3 T2.

## Verification

- ROM-free CTest: 24 of 24 passed.
- Owner-local CTest: 26 of 26 passed.
- Win32 x86 and x64 builds passed.
- OpenNT large-model portable-core compile passed, including `render.c`.
- Documentation governance and `git diff --check` passed.

