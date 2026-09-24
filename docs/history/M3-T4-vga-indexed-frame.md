# M3 T4 VGA Indexed Frame

## Outcome

The neutral command stream now drives a deterministic 320x200 indexed-color
VGA frame.  Its background and actor palette policy matches the existing
presentation adapters without importing any ROM graphics.  The frame unit is
compiled by the OpenNT large-model target.

## 16-bit Storage Repair

The initial contiguous 64,000-byte member was rejected by the OpenNT C
compiler as too large for one object.  The final contract receives four
explicit 16,000-byte pages through `mysmb_vga_frame_initialize`.  Pixel
offsets select a page and page-relative index.  Each allocation is within the
16-bit compiler's object limit, while the complete logical 320x200 frame is
still present.  This is a deliberate DOS-facing storage contract, not a host
allocation workaround.

## Mapping And Evidence

Each VGA pixel samples the neutral 32x30 tile frame; actor rectangles overlay
the resulting background after scaling 256x240 coordinates to 320x200 with
16-bit-safe 5/4 and 5/6 arithmetic.  `mysmb.vga-frame-smoke` verifies sky,
block, terrain, player, and enemy index values, including page-spanning
logical offsets.

## Similar-Issue Sweep

The VGA source and test were searched for game-RAM access, game construction,
DOS interrupt and port APIs, console output, escape sequences, and render
frame bypasses.  Production code only consumes the neutral frame.  Game state
exists only in test setup; no hardware operation, host mutation, or protected
asset is present.  DOS hardware writes, input polling, timing, and executable
linking are deferred to M3 T5.

## Verification

- ROM-free CTest: 26 of 26 passed.
- Owner-local CTest: 28 of 28 passed.
- Win32 x86 and x64 builds passed.
- OpenNT large-model target compiled `vga_frame.c` successfully.
- Documentation governance and `git diff --check` passed.

