# Product UX

## Windows Native Game

The first graphical product is a native Win32 window built for x86 and x64. It launches directly into the game and has no emulator monitor, runtime ROM picker, or required configuration menu.

## DOS Native Game

The later DOS graphical product targets a 25 MHz 486SX. MS-DOS 5.0 is the required baseline; DOS 3.3 compatibility is pursued when it requires no compromise.

## Text Presentation

The text product uses an 80×25 colored character scene. It draws known game objects and their states using filled cells, outlines, and glyph detail; it is not a luminance-to-ASCII filter.

## Host Resources

The Win32 adapter supplies the development window and normal graphical/full-screen presentation. The DOS adapter later uses VGA Mode X 320×240, BIOS keyboard input, PIT-based 60 Hz timing, and a lightweight PC Speaker sound path. NTVDM64 may run non-graphical DOS checks but is not a DOS graphics validation platform; the 486SX remains the DOS graphics and performance authority.
