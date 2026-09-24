# M3 T3 Colored Text Frame

## Outcome

The project now has a deterministic 80x25 colored-object frame adapter.
`mysmb_text_frame_build` consumes only the neutral render frame and produces
2,000 character/color cells.  It is a data adapter rather than a console
writer, so no terminal host, escape sequence, or game-core platform branch is
needed.

## Mapping Policy

- Each text cell samples the corresponding 32x30 tile-space location and
  receives a full background character and color; sky is blank blue, terrain
  is `#` green, and block ranges use `+` or `.` with a brown/gold color.
- Actors overlay their screen-relative cell rectangle after background fill.
  The player is `@`; Goombas and Koopa classes use distinct letters; firebars
  use `*`; Bowser is `B`; remaining actor identities use `o`.
- Both glyph and color are properties of the adapter, derived solely from the
  neutral command identity.  They are intentionally not bitmap conversion or
  ROM-derived artwork.

## Fixed-Input Evidence

`mysmb.text-frame-smoke` seeds sky, block, terrain, player, and enemy state;
builds the neutral frame; then checks sampled background cells and the
screen-relative player/enemy glyph and color overlays.  The test contains no
owner media and runs in both standard configurations.

## Similar-Issue Sweep

The text adapter and its test were searched for direct game-RAM access,
game-state constructors, terminal APIs, text-output functions, escape
sequences, and render-frame bypasses.  Production text code accesses only
`mysmb_render_frame`; the game object occurs only in the test setup.  No host
mutation, protected asset, or terminal-output leakage was found.  A real DOS
console/video writer and VGA Mode X adapter are deferred to M3 T4.

## Verification

- ROM-free CTest: 25 of 25 passed.
- Owner-local CTest: 27 of 27 passed.
- Win32 x86 and x64 builds passed.
- OpenNT large-model portable-core compile passed.
- Documentation governance and `git diff --check` passed.

