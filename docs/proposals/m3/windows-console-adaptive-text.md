# Windows Text Console Fit And Restore

Admitted M3 T33 S1 under explicit owner implementation/build/test/commit
instruction. Current packet owns execution;the owner will perform actual
visible Terminal/Console Host verification after delivery. T32 remains
suspended and the new performance package remains queued. Four delivery
cohorts below are combined into one bounded S with capability/lifecycle tests,
three products and a pending owner visual gate.

## Problem And Owner Contract

The authored text scene is 80x50 cells. The owner previously observed a usable,
fully visible, approximately square-cell text window at 150% desktop scaling;
the remaining defect then was maximize followed by the caption Restore button.
That operation fell back to the graphical window rather than keeping the game
in text mode. Current Windows Terminal presentation preserves its native font
and viewport, so an 80x30 view clips 20 scene rows and a tall cell remains tall
when the user merely reduces font size. The earlier live visual appearance is
owner evidence, not proof that `SetCurrentConsoleFontEx` changed Terminal's
physical glyph metrics. Reproduce and distinguish those facts.

Both Windows Terminal and classic Console Host must remain usable. On entry,
try the prior Consolas 8x8 request for both hosts and measure what actually
happens; do not skip the attempt merely because of a host-name classification.
The same fit and lifetime policy applies to both; differences are expressed as
observed device capabilities rather than a hard-coded host-type decision.
Prefer a complete 80x50 view with approximately square cells. When the window
is smaller, fit cells down to the available view; when enlarged, grow them only
up to the normal 8x8 target. After Restore, recompute the fit for the restored
view and return to the prior size when the view is unchanged. If a host does not
honor programmatic font or geometry changes, preserve its settings and keep
text mode responsive while using the best verified presentation it supports.
Do not claim a clipped or vertically stretched view is a complete visual fix.

Tab alone requests a normal graphics/text presenter switch. Maximize, Restore,
minimize, font/viewport change, DPI change or an in-flight partial write must
not be interpreted as Tab, exit, game-state loss or persistent device failure.
Escape, close and genuine device loss keep their existing explicit behavior.
No global Windows default-terminal setting, user's unrelated Terminal profile,
shell state or system font is modified. Borrowed console settings changed by
the game must be restored on Tab, exit and error.

## Code Boundary And Investigation

- `src/platform/win32/text_console.c`: host capability probe and font request
  in `mysmb_win32_text_console_open`, classic geometry in
  `mysmb_win32_console_geometry`, Terminal viewport/write in
  `mysmb_win32_terminal_present`, and borrowed-host restoration in close.
- `src/platform/win32/text_console.h` and the Win32 root: replace the current
  `terminal` flag's multiple behavioral meanings with only the capabilities
  actually needed, such as usable host window, mutable font/viewport, and VT
  output. The `GetClassNameA("ConsoleWindowClass")`/caption/message-parent
  heuristic must no longer decide whether font fit is attempted, whether a
  resize is fatal, or which window may be shown. A console HWND is optional;
  input/output handles remain the health authority. Root code that currently
  branches on `g_console.terminal` must receive the corresponding explicit
  window capability instead of reintroducing a new host-name check.
- `src/platform/win32/main_win32.c`: `mysmb_win32_build_frame` currently folds
  every presentation failure into `g_text_failed`; the tick then calls
  `mysmb_win32_switch_presenter`. Separate a transient unavailable frame from
  confirmed permanent device loss so Restore never silently invokes Tab's
  presenter switch.
- `src/io/video.h` and `src/text/` continue to own the neutral 80x50 authored
  scene. Do not change ROM/game/PPU semantics or silently discard text rows.
  A smaller-host projection, if needed, is a separately measured presentation
  design with visual review, not a change to original game logic.

Compare the pre-S4 T29 implementation with `2959c348` and the T24 Restore
record. Do not revert the whole T29 commit: it also introduced bounded
asynchronous console acquisition and native Terminal RGB output. Reintroduce
only useful font/fit behavior after testing it on both actual hosts. Read back
requested and effective console metrics, visible rows/columns and write status,
but do not equate a successful or virtualized API readback with physical glyph
geometry. Keep observations under an ignored `build/` directory.

Keep one Win32 console-device owner and one resize/fit state machine. Probe
capabilities on the game's output buffer after saving borrowed-shell state;
never destructively test the user's shell buffer. A failed optional operation
does not make the device unusable. Use direct console-cell writes or VT output
according to verified output capability and fidelity, not a window class name.
Do not add a second policy engine, duplicate scene composition, a platform
dependency in `io/` or `text/`, or a wrapper that merely forwards the same
state. The output backend may differ, but the requested font target,
ready/defer/lost result, resize policy and Tab semantics must be shared.

## Proposed Delivery Cohorts

These are planning cohorts, not allocated S identifiers. Split or combine at
admission according to the measured dependency boundary.

1. **Baseline and capability experiment.** On the current x86/x64 products,
   record 150% DPI entry, maximize, caption Restore and repeated Tab routes in
   Windows Terminal and classic Console Host. Compare a contained pre-T29-S4
   8x8/80x50 request with current behavior. Capture actual visible frame,
   viewport, font-cell ratio, API results, latency and whether an in-flight
   write causes the graphical fallback. Also exercise borrowed CMD/PowerShell
   and fresh owned-console lifetimes. Do not adopt the experiment as a fix.
2. **Stable presenter lifetime.** Give presentation an explicit
   ready/defer/device-lost result. A temporarily zero, changing or clipped
   viewport, a bounded resize race and a partial write defer drawing without
   switching presenters. Confirmed invalid input/output handles or persistent
   failures use the existing recovery path. Avoid infinite retries, a busy
   loop, and suppression of a real close request. Audit every production caller
   of console presentation and the equivalent classic geometry path.
3. **Capability-based fit.** Remove the window-class-based behavior switch and
   audit every former use of the `terminal` flag, including root window
   activation, shell restoration, font/palette/geometry and output selection.
   On entry and after a settled size change, attempt
   the normal 8x8 target for either host, then smaller approximately square
   candidates only as needed to fit 80x50. Use measured effective dimensions
   and visible rows/columns; retain a last known good setting and restore the
   shell's saved state. Maximize may grow up to 8x8; Restore reapplies the fit
   for its view. Never mutate font/window geometry per video frame or force a
   Terminal resize that its owner does not support. If two output mechanisms
   remain, select by verified device ability and actual rendering fidelity;
   neither gets a separate game or fit policy.
4. **Terminal no-effect branch and acceptance.** If Terminal ignores the font
   request, preserve its font and retain responsive input/Tab/close through
   all resize cycles. Measure whether the complete 80x50 scene fits. If it
   does not, evaluate a bounded viewport-aware presentation or an opt-in
   game-specific Terminal profile; show the owner its exact visual result and
   any lost text detail before adopting it. A global default-terminal change,
   hidden clipping presented as success, or a separate GUI text clone is not
   presumed approved. Record the unresolved full-view limitation explicitly
   if no acceptable in-Terminal solution is demonstrated; do not declare the
   full product-experience objective met.

## Regression And Exit Contract

Use real maximize and caption Restore operations, not just synthetic
`SetWindowPos` resizing. Test at 100%, 150% and 200% DPI where available, with
small/restored/maximized views and repeated cycles. Check actual glyph aspect,
all 80 columns/50 rows when claimed, authored colors and Unicode glyphs, frame
continuity, the same running game state, responsive keyboard/audio, Tab in
both directions, Escape/close, fresh owned and borrowed shell restoration. A
user-visible actual-window check is necessary; console buffer readback and a
private-desktop probe alone cannot certify Terminal's visible font or Restore.
Add capability-matrix tests whose fake window class names do not determine
results: usable/unusable host HWND, accepted/no-effect font request,
resizeable/fixed viewport, direct/VT output, temporary write failure and true
handle loss. Verify the same high-level behavior for equivalent capabilities
on both real hosts. Compare before/after first text entry, maximum, Restore,
Tab return and borrowed-shell exit; reject a fix that improves one host by
regressing the other or weakening the existing game and window behavior.
Preserve current passing graphics, DOS16 behavior, snapshots, focus semantics
and T29 asynchronous acquisition. Product-code adoption requires focused
tests, x86/x64 native builds, DOS16 compilation and refreshed three local
products under the normal task rules; protected products stay local.

The task can close as a full visual repair only when both hosts retain text
mode across maximize/Restore, Tab switches intentionally, and the admitted
display-quality acceptance is visibly met without a regression from the
owner-observed earlier usable view. Report host-specific actual behavior and
remaining limits; no API success flag alone counts as visual acceptance.
This host-presentation task expects no ROM-node or control-edge credit:
scope/expected/actual are empty, new credit zero, with the then-current ledger
totals recorded at admission. No source material is imported.

## T33 S1 P1 delivered state

Implementation,three builds,focused/native and actual host-device tests are
committed and products published. Owner verification is pending;T33/S1remain
active and full visual closure is not claimed. Classic actual caption Restore
reports80x50/8x8. Current Terminal ignores the font request and retains80x30;
full-scene/physical glyph/Terminal caption acceptance remains explicitly open.
[Implementation evidence](../../history/M3-T33-windows-console-fit.md#s1-p1-implementation-and-delivery-awaiting-owner-visual-verification).

## T33 S1 P2 geometry correction

P1's HWND-gated entry geometry omitted a working T24operation sequence.
Same-host neutral and actual product probes now observe80x50after restoring
one optional all-device entry request;borrowed restoration and rollback pass.
Do not infer physical font geometry from readback. The earlier80x30delivery
state is historical;P2products supersede it. Owner live visual/Restore review
remains pending. [Correction](../../history/M3-T33-windows-console-fit.md#s1-p2-restore-the-actual-t24-geometry-contract).
