# M3 Presentation Adapters

## Purpose

Replace the temporary Win32 gameplay drawing with a portable, neutral render
command seam.  The same commands will later feed native Win32, DOS VGA, and
an 80x25 colored-object presentation without creating a second gameplay path.

## Candidate Order

1. Define game-owned neutral block, actor, and palette command ownership and
   prove deterministic generation from the existing C90 state.
2. Make the Win32 adapter consume that command state for gameplay rendering.
3. Add DOS VGA and colored text adapters over the same commands.

## Boundary

Commands describe existing native game state.  They do not contain ROM bytes,
host handles, terminal escape sequences, or input/gameplay mutation.

