# Product UX

## Windows Native Game

The first graphical product is a native Win32 window built for x86 and x64. It launches directly into the game and has no emulator monitor, runtime ROM picker, or required configuration menu.

## DOS Native Game

The later DOS graphical product targets a 25 MHz 486SX. MS-DOS 5.0 is the required baseline; DOS 3.3 compatibility is pursued when it requires no compromise.

## Text Presentation

The text product defaults to an 80x25 colored character scene. The retained
80x50 interface and artwork remain available for regression and a future
selection switch;there is no new user-facing switch yet. Shared text owners
draw semantic color masses with character landmarks from committed object
observations,not a bitmap sampler. Tab switches graphics/text over the same
game state on DOS16 and Windows. ASCII information and selected CP437 details
remain shared. Blue/dark scenes keep light information text;question blocks
retain a visible question mark even at one/two rows tall.

## Host Resources

The Win32 adapter supplies the development window and normal graphical/full-screen presentation. DOS uses native256x240 VGA chain4 output with hardware scan repetition,observed as512x480scanout. All61440source pixels are preserved without software resampling or an intermediate plane copy. Physical LCD height filling and side borders depend on the display hardware. DOS owns physical keyboard input and PIT pacing;nominal gameplay cadence remains unqualified and there is currently no DOS audio renderer. NTVDM64 is not the accepted DOS graphics validation platform;the486SX remains the physical graphics and performance qualification target.

## Quick Snapshot

P synchronously captures the current gameplay state to `mysmb.sav` beside the
executable;O validates and restores it,including from the title screen.
Paused saves preserve the actual pause state;Enter resumes a restored paused
game through its original control path. Application ticks stop during I/O,
without changing the original pause flag. No per-frame snapshot is maintained.
Each press is handled once and never enters
the controller stream. Failures are silent and append best-effort diagnostics
to `mysmb.log`;`mysmb.tmp` is the pending slot. Files remain local user data.
All three targets share the format. DOS currently has no audio renderer/output;
Windows restores active synthesis state for Windows-originated saves. DOS
replacement has a documented delete/rename interruption window. The
[T10 acceptance record](../history/M3-T10-shared-io-quick-snapshot.md#t10-acceptance-matrix)
records scoped evidence and limitations.

Windows Terminal keeps its native font and window size. On Restore the device
redraws the visible portion of the selected scene;owner accepts clipping
beyond this viewport. Classic console requests the selected80x25view
(80x50through the retained interface). Palette and font acceptance are
separate from buffer readback and remain subject to owner play testing.
No Windows default-terminal setting is changed by the product.
