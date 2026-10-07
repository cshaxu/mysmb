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

## S1 P2 restore the actual T24 geometry contract

Owner questions why T24worked. Static source comparison finds T24
f03e1b72always attempts8x8font,80x50buffer and80x50view;T29 S4
2959c348classifies Terminal and skips font/geometry,clipping to native view.
P1 restores font attempts but still incorrectly gates initial geometry on
window_usable. A notification HWND is not evidence that buffer/view operations
are unsupported. Earlier attribution to Terminal alone was premature.

Same-host isolated neutral probe reproduces the T24sequence:game starts
120x30;shrink view,set80x50buffer,set80x50view all succeed,error0;observed
80x50and original shell120x30restored. Installed Terminal1.24.12741.0.
Separate CSI8;50;80tprobe does not establish50rows in this context,so is not
adopted. Microsoft official1.23release and PR17721 describe conditional
single-tab/pane,non-fullscreen resizing;not font control. MIT source/patch is
read-only under ignored build,no source imported. Patch SHA256
33d54297991e9e628d7794a5ee17bc171daed4d0b48d1f61eda13e375ba0b5bf.

Product+31/-10lines in the same Win32device/header:one optional entry geometry
attempt regardless of host HWND;read back actual buffer/view,retain independent
geometry_usable. If partially unsupported,restore pre-attempt size/view so no
1x1view remains. Borrowed-shell geometry restoration follows the demonstrated
device capability. Real-window activation/minimize/Restore remains separately
window-owned;no per-frame forced resizing on a notification host. Shared game,
PPU,IO,text,DOS and root source unchanged. No new helper process or settings.

Two widths18/18native tests pass. Current capability fixture additionally
covers no-window accepted geometry and rollback after tiny-view/buffer failure;
all prior transient/device-loss/minimize/Restore tests pass. Actual final x86/
x64product probes each read80x50/4000cells on three text entries,retain768x720
at144DPI,return through Tab twice and exit0through Escape. Default and explicit
classic borrowed-parent fixtures pass shell font/input/title/cursor/view/error
restoration. Physical Terminal glyph shape/live caption behavior still awaits
owner review;80x50device readback alone is not physical-display certification.

Three existing assets refreshed. DOS original-tool rebuild remains identical
307349B/SHA33e6bbd39273d0c99e214026b66655d66ffb548bd0336d96daa38614b80ae1e2;
x86318478B/SHA77da36ae51f70cf9da9c6d62757c03f4565f28a6a6dcbe7dcfe335b685c639f9;
x64331790B/SHA2c30c56b2c819272814f2e636da61e8ea8e99c5ad4c9c9c87b76ec728c53503c.
Windows file deltas+512/+1024B,no DOS memory change. Source/product hashes
bind the final probe receipts;runtime PE sections survive debug stripping.
Historical1992/1992,local1991/1992nodes and4260/4261controls unchanged,new0.

Similar-issue sweep:entry geometry,borrowed restoration,all window_usable
uses and optional partial failures. HWND capability now governs only actual
window operations;device geometry is tested directly. P1full-view limitation
is superseded for measured device viewport,not silently relabeled visual
acceptance. T33/S1remain active awaiting owner verification;no queue advance.

## S1 P3 and T33 owner-directed engineering closure

Owner explicitly requests work through closure. Final repair+22/-18product
lines removes the second raw Restore size sequence:entry and settled classic
Restore share the same rollback-safe device operation. A reproduced first-
request fault left a1x1view despite valid handles. One additional bounded
attempt now recovers;two persistent failures roll back to the prior view,
never an infinite/per-frame Terminal sizing loop. Later successful geometry
updates the borrowed-restoration capability. Core/PPU/text/IO/DOS unchanged.

Current-source capability fixtures pass both widths,including transient
recovery and two-failure rollback,partial writes and genuine device loss.
Final native18/18each width passes. Current actual default/classic/maximized
parent fixtures perform four entry/exit cycles each width;all accepted views
compare4000independently expected glyphs,including four Unicode corners,
exactly. Caption maximize/Restore remains responsive;final classic view80x50,
font8x8logical. Shell font,input,title,cursor,buffer and geometry restored.
An intermediate fixture linker failure is excluded;supervision now stops on
failed compilation before execution and current-source fixtures are bound.

Neutral real Console Host captures after caption Restore are visually checked:
all80columns/50rows and corner glyphs visible. At150%DPI,the complete physical
capture is982x656;an earlier655x438capture was cropped by DPI virtualization
in the harness,not by the product. Capture temporarily selects thread DPI
awareness and restores it. Neutral captures contain no ROM assets and remain
ignored. Only current successful captures/fixtures are closure evidence.

Actual final products retain768x720graphics at144DPI;three text entries each
read80x50/4000cells,two Tab returns and Escape exit0. Owned and borrowed
lifetimes pass. Installed/default terminal settings and user desktop untouched;
no production helper process. Original DOS rebuild remains byte-identical,
DGROUP49264/stack2048 unchanged.

Final existing assets:DOS307349B/SHA
33e6bbd39273d0c99e214026b66655d66ffb548bd0336d96daa38614b80ae1e2;
x86318478B/SHA02fbe39d8dea4a74da395b8884e11ee8d534087ad60035cce8c5d7854ab6f90b;
x64331790B/SHA773a39d6fa55f890d83e03b2ff0aa05cba9f625772342b4823dc6c65336cc954.
No further EXE build is needed for the documentation closure;source/product
receipts bind these exact final outputs. New ROM-node/control credit0;
historical1992/1992,local1991/1992nodes and4260/4261feasible controls unchanged.

S1/T33close under the latest owner mandate and earlier permitted native
Terminal Restore size/clipping contract. This is tested engineering closure,
not full physical Terminal/all-DPI visual certification. Terminal physical
font/live caption observation is retained as HOST-T33-VISUAL in TODO;no user
validation is invented and no M2/global performance claim is made. The
original proposal is archived alongside this record. CURRENT is idle;
remaining performance package is queue head,not automatically admitted.

## S2 Owner Acceptance And T33 Closure

Owner reports the delivered result perfect/successful and explicitly closes
T33,then requests the next queue task. Accept default80x25 and retained80x50,
white information text,question marks,source-bound colors,spring highlights
and distinct running phases under the observed play conditions. Source
delivery is f7ff2b2f,32files,+846/-119lines; three current local product hashes
and sizes are bound in the T34 admission record. Each Windows width20checks,
53legacy byte-identical cells,1200read-only native frames,actual Tab/CMD routes
and original DOS build/stock-config startup/text/input/exit evidence are retained.
This documentation closure rebuilds no EXE and changes no product code.

S2/T33 close by owner-directed acceptance. The transferred complete-gallery
contract was not exhaustively reviewed:53remaining-object fixture cases and
approved player/power-up groups are retained,not a complete reachable-state
census. Its unresolved full pose/background/information inventory remains
explicitly deferred as TEXT-GALLERY-REMAINDER in TODO under this closure
mandate. Do not call unreviewed rows visually approved. Physical host/all-DPI
and486SX qualification likewise are not inferred from owner acceptance.

No ROM-node custody changes or promotions. Historical1992/1992,local1991/1992
nodes and4260/4261feasible controls,raw4342/infeasible81,new0. M2 final
certification remains incomplete. T34 S1 receives only native VGA work; no
character redesign or whole-ROM audit is folded into its scope.
