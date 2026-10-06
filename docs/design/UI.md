# Product UX

## Windows Native Game

The first graphical product is a native Win32 window built for x86 and x64. It launches directly into the game and has no emulator monitor, runtime ROM picker, or required configuration menu.

## DOS Native Game

The later DOS graphical product targets a 25 MHz 486SX. MS-DOS 5.0 is the required baseline; DOS 3.3 compatibility is pursued when it requires no compromise.

## Text Presentation

The text product uses an 80×50 colored character scene. It draws known game objects and their states using cells, outlines, and glyph detail; it is not a luminance-to-ASCII filter. Tab switches between graphics and text over the same running game state on DOS16 and Windows. Shared glyph IDs include ASCII text and selected CP437-compatible details.

## Host Resources

The Win32 adapter supplies the development window and normal graphical/full-screen presentation. The DOS adapter uses VGA Mode X 320×400 with horizontal double-dot scanout: the full 256×240 source is stretched to fill 640×400 without added borders or source-row loss. DOS owns physical keyboard input and PIT pacing; nominal gameplay cadence remains unqualified and there is currently no DOS audio renderer. NTVDM64 is not the accepted DOS graphics validation platform; the 486SX remains the physical graphics and performance qualification target.

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

Windows Terminal keeps its native font and window size. On Restore the device
redraws the currently visible portion of the shared80x50scene;owner accepts
clipping beyond this viewport. Classic console retains its80x50restored view.
No Windows default-terminal setting is changed by the product.
