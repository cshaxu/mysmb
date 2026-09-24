# M3 T2 Win32 Command Consumer

## Outcome

The Win32 gameplay paint route now consumes every neutral render command.
Tile rows produce deterministic 8x8 colored blocks and actor commands produce
screen-relative colored actor blocks.  The previous sky, fixed ground, and
single-player-marker path has been removed.

## Palette Policy And Boundary

The adapter maps tile ranges to a small host palette: the sky tile remains
sky blue, high tile values use green, block-range values use brown, and the
remaining visible values use a gold accent.  Actor identity zero is red for
the player; other identities select one of two enemy colors.  This policy is
host presentation only: it uses command data and contains no CHR, palette,
or other protected ROM material.

The local title renderer remains separate because it is an admitted
owner-local title-data composition route.  Active gameplay has one source:
the render frame built after the native game tick.

## Similar-Issue Sweep

The Win32 source was searched for direct game-RAM/name-table drawing, game
ticks, command construction, and GDI paint calls.  Direct game-state reads
remain only in the owner-local title path and its title-versus-gameplay
selection.  The active gameplay drawer reads `g_render_frame` alone.  There
is one game tick root and one render-frame build after it.  No host mutation,
command bypass, duplicate palette mapping, or protected asset leakage was
found.  DOS VGA and colored-text consumers remain deferred to M3 T3.

## Verification

- ROM-free CTest: 24 of 24 passed.
- Owner-local CTest: 26 of 26 passed.
- Win32 x86 and x64 builds passed.
- OpenNT large-model portable-core compile passed.
- Documentation governance and `git diff --check` passed.

