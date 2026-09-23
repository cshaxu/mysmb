# Product UX

## DOS Native Game

The primary graphical product is a real-mode DOS game for a 25 MHz 486SX. It launches directly into the game and has no emulator monitor, runtime ROM picker, or required configuration menu. MS-DOS 5.0 is the required baseline; DOS 3.3 compatibility is pursued when it requires no compromise.

## Text Presentation

The text product uses an 80×25 colored character scene. It draws known game objects and their states using filled cells, outlines, and glyph detail; it is not a luminance-to-ASCII filter.

## Host Resources

The DOS adapter uses VGA Mode X 320×240, BIOS keyboard input, PIT-based 60 Hz timing, and a lightweight PC Speaker sound path. NTVDM64 is the Windows integration host for the same DOS executable; the 486SX remains the performance authority. Windows later supplies native graphical/full-screen and colored text presentations.
