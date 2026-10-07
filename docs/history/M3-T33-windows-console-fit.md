# M3 T33 Windows Console Fit And Restore

## S1 admission

Owner admits queue head and requests implementation,three builds/tests,commit
and wait for owner visual verification. One bounded S covers capability/font
fit and stable presenter lifecycle;estimate150-250Win32product lines plus
focused host-state tests. Entry console-open,exit ready/defer/lost presentation
and borrowed-shell restoration. No game/PPU/DOS logic change.

Baseline T32 S8 P21 products retained. Scope/expected/actual[],new0;historical
1992/1992,local1991/1992nodes and4260/4261feasible controls unchanged. Normal
8x8font is attempted regardless of host class;optional unsupported geometry
and resize races cannot turn into automatic presenter switches. Private-host
checks prove device behavior,not actual Terminal visible glyph metrics. Owner
visual verification remains explicit before full visual closure.

## S1 P1 implementation and delivery awaiting owner visual verification

Three product owners change:+134/-95lines in text_console.c/header and
main_win32.c. No core,PPU,IO,text or DOS source changes. GetClassName and
multi-purpose terminal behavior are removed. A visible usable host window is
an optional activation/geometry capability;VT selection uses output mode
support. Every output receives the8x8Consolas request,with bounded4..8targets
and150mssettled viewport fitting. Borrowed fonts are saved/restored alongside
existing shell buffer,input,title,cursor and placement lifetimes.

Presentation explicitly returns ready/defer/lost. Valid-host resize,query
unavailability,partial write or invalid-parameter/not-ready error defers a
frame;no120frame timeout turns resize into Tab. Actual invalid/access-denied
handles and120consecutive other failed writes keep device-loss recovery.
Only lost causes root recovery. VT uses its existing exact RGB stream;it does
not call the palette setter,which the first actual probe showed shrinking
Terminal30rows to29. This regression was repaired before publication.

Focused capability fixtures pass x86/x64:no-effect/accepted font,settled
resize,visible/unavailable window,maximize/Restore optional geometry failure,
minimize,200partial writes,200invalid-parameter errors,access loss and bounded
persistent non-resize failure. Final CTest18/18per width passes,including
keyboard/launch/core/PPU/snapshot/text and platform purity. Standalone current-
source actual-parent fixtures additionally pass both widths through borrowed
font/input/title/cursor/buffer/error restoration and actual classic caption
maximize/Restore. The private classic host reports80x50and8x8after Restore,
including a maximized starting shell;this is API/device observation,not owner
visible glyph acceptance.

Actual final product private-desktop probes at144DPI retain768x720graphics,
perform two text/graphics returns and Escape exit0. Native Terminal stays
80x30on all three entries,with exact current RGB authored content visible.
Font readback0x16shows the request is not effective here. Physical glyph shape,
actual Terminal caption Restore and complete80x50in that host remain UNPROVED;
this delivery does not declare the full visual objective met. Owner explicitly
requested waiting for real verification;T33/S1stay active awaiting that result,
no successor admission and no task closure.

Original-tool DOS16 rebuild equals P21 byte-for-byte:307349bytes,
SHA25633e6bbd39273d0c99e214026b66655d66ffb548bd0336d96daa38614b80ae1e2.
DGROUP49264,stack2048and loader bounds unchanged;old exact-binary DOS route
receipts remain applicable rather than rerunning unrelated gameplay.
Final local x86317966bytes SHA256105e16293ae2d5d48f48243b76986831c1ef6404200581367e708404868e62ae;
x64330766bytes SHA25636198c47bc63a375fc173d6e3ed177b0470e0be016d045259c6a5ce57e4244f8.
All three existing owner-authorized asset paths refreshed;DOS has no binary
diff. Debug stripping leaves runtime PE sections unchanged. Research/probes
remain ignored;no new ROM/resource or third-party material is added.

Similar-issue sweep:all four root terminal tests/present-failure uses,console
open/optional font/palette/window operations,both writers,geometry retry,
borrowed close and test error-exit branch inspected. Every production hit is
changed within the one console-device owner;no parallel fit/game policy.
Historical1992/1992,local1991/1992nodes and4260/4261feasible controls unchanged,
new0. Scoped host tests do not complete the deferred M2certificate.
