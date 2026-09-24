# M3 T7 DOS Hardware Hooks

## Outcome

The linked DOS root now uses BIOS keyboard and timing services plus real VGA
and text-memory presentation.  Direction keys, Enter, Z, and X map to the
native input buttons.  F1 selects either the 320x200 indexed VGA frame in
Mode 13h or the 80x25 colored text frame at B800.  The loop uses BIOS
`int 15h/AH=86h` for an approximately 60Hz frame delay.

## Boundary

All BIOS calls, video-mode changes, and far-memory writes are in
`src/platform/dos16/main_dos16.c`.  The DOS root continues to call the one
native game tick and then submits neutral-derived frames through hooks.  The
portable game, render, text-frame, and VGA-frame units contain no DOS API.
VGA pages and their frame pointers are explicitly far only for the OpenNT
DOS target, keeping four 16KB pages outside DGROUP.

## Runtime Evidence And Limitation

The configured OpenNT large-model target compiles and links this hardware
hook path into the ignored MZ artifact.  The available NTVDM validation host
does not yet provide DOS graphical display, so this task does not claim live
visible rendering or physical-keyboard evidence.  M3 T8 is reserved for a
DOS runtime/host verification route and 486SX-oriented pacing review.

## Similar-Issue Sweep

The project was searched for BIOS calls, video-memory constants, hardware
compile defines, and `int86`.  Every production hit is limited to the DOS
entry file or the DOS-only far-pointer declaration in the VGA frame ABI; no
hit appears under `src/game`.  No platform hook mutates game RAM directly and
no protected asset is introduced.

## Verification

- ROM-free CTest: 27 of 27 passed.
- Owner-local CTest: 29 of 29 passed.
- Win32 x86 and x64 builds passed.
- OpenNT large-model DOS target compiled and linked the hardware hook path.
- Documentation governance and `git diff --check` passed.

