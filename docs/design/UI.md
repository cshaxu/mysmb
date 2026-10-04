# Product UX

## Windows Native Game

The first graphical product is a native Win32 window built for x86 and x64. It launches directly into the game and has no emulator monitor, runtime ROM picker, or required configuration menu.

## DOS Native Game

The later DOS graphical product targets a 25 MHz 486SX. MS-DOS 5.0 is the required baseline; DOS 3.3 compatibility is pursued when it requires no compromise.

## Text Presentation

The text product uses an 80×25 colored character scene. It draws known game objects and their states using filled cells, outlines, and glyph detail; it is not a luminance-to-ASCII filter.

## Host Resources

The Win32 adapter supplies the development window and normal graphical/full-screen presentation. The DOS adapter later uses VGA Mode X 320×240, BIOS keyboard input, PIT-based 60 Hz timing, and a lightweight PC Speaker sound path. NTVDM64 may run non-graphical DOS checks but is not a DOS graphics validation platform; the 486SX remains the DOS graphics and performance authority.

## Quick Snapshot

P saves one running frame to `mysmb.sav` beside the executable;O loads and
resumes immediately,including from the title screen. While paused,P saves
the last completed running frame. Each press is handled once and never enters
the controller stream. Failures are silent and append best-effort diagnostics
to `mysmb.log`;`mysmb.tmp` is the pending slot. Files remain local user data.
All three targets share the format. DOS currently has no audio renderer/output;
Windows restores active synthesis state for Windows-originated saves. DOS
replacement has a documented delete/rename interruption window. The
[T10 acceptance record](../history/M3-T10-shared-io-quick-snapshot.md#t10-acceptance-matrix)
records scoped evidence and limitations.
