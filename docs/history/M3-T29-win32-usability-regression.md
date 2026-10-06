# M3 T29: Win32 window and console usability regression

## Admission and owner boundary

Owner admits T29 ahead of pending DOS graphics optimization. Sole active S1
investigates the owner-reported last-good dfc13a21 and first-bad41d161e3 product
boundary. Artifact dates/subsystems/source provenance require verification;
a product refresh is not proof that its enclosing source change caused failure.

## Subtasks

- S1: bind historical/current artifacts and sources; reproduce initial client
  size and Tab transition using actual products on an isolated desktop; locate
  blocked calls/messages and missing test coverage. Estimate100-200 neutral
  probe lines; no product repair before the diagnosis. Bound each process to
  60seconds, logs to2MiB, all temporary material below ignored build.
- S2: repair the identified Win32 geometry/console lifecycle chain and similar
  issues; expected30-150 platform lines, revised with diagnosis. Preserve GUI
  initial512x480 client,16:15 resizing, neutral authored80x50 cells, CMD launch,
  one game instance, keyboard and shell restoration. No game/PPU/DOS semantics.
- S3: actual x86/x64 product startup and repeated graphics/text/graphics cycles,
  input and Escape/root close, launcher/CMD routes and relevant DPI geometry;
  current focused tests and three products for changed code. Explain historical
  test blind spots and owner-RDP/hardware limits rather than claiming coverage.

## Verification and scope

Current baseline is cf85c7a0/P22 three EXEs. Neutral host probes only; local
owner products remain local and no asset/third-party import is authorized.
Original DOS16 toolchain remains; no DOSBox settings change. Never take user
focus, use foreground keyboard injection or create a helper process in product.
Tests may create bounded child processes on private desktops.

Every S has empty ROM scope/expected/actual,zero new matches;historical1992/1992,
local1991/1992nodes and4260/4261feasible controls(raw4342/infeasible81) retained.
No ROM custody change or final certification credit. Existing tracked EXE
owner exception applies to required refreshed products; no new ROM derivatives.
Close only when reported client sizing and Tab usability have actual-product
proof on both widths, scoped similar issues are disposed and governance passes.


## S1 P1 diagnosis checkpoint

Verified Git-retained last-good dfc13a21 x64 artifact:380216bytes,GUI subsystem,
SHA256b361c9c16bab4a5c6fe723b929fca2419e4faa394f11af4ca963b77dc31accd2.
Its artifact last-change commit is f47386c5,not its enclosing dfc13a21 source.
First-bad41d161e3 artifact:327275bytes,console subsystem,
SHA256e4287bf0389721c0403982e47ee330132ca3fa2d1d69fc0dba8dff86c0f5cb87.
41d161e3 source already includes T24 f03e1b72/b9997a33 host changes;binary
refresh and source cause remain distinct. Current x64 artifact329323bytes.

Bounded private-desktop actual product probes use DPI-aware measurement and
owned-window messages only. At current150percent desktop scaling,last-good
client is768x720 physical pixels,first-bad/current512x480. An unaware observer
reports current341x320 virtual units;that measurement is not physical size.
The source still sets scale2,while T24 enables per-monitor DPI awareness without
scaling the desired initial client to DPI. Old DPI-unaware binary receives
Windows bitmap enlargement;new binary uses fixed physical dimensions. This
explains the measured reduction. Owner's specific256x224 dimensions were not
reproduced;do not replace that report with an invented measured value.

Current actual product remains responsive after targeted Tab messages but no
usable text presenter persists in this private-desktop route. A locally linked
current-source instrumentation probe,with no gameplay changes,shows:
- Tab is accepted with focused input and enters console acquisition.
- AllocConsole takes about1.16-3.41seconds in observed runs,synchronously
  blocking root pumping during that call. No indefinite deadlock proved.
- Input handle,font,palette and80x50geometry APIs succeed.
- EnableMenuItem(GetSystemMenu(...)) fails with ERROR_INVALID_MENU_HANDLE1401;
  current open code treats this optional window decoration as fatal,closes the
  working console devices and returns to graphics.
- A contained variant bypassing only that menu gate reaches console-open done.
  The next root step still treats IsWindow(console.window)==FALSE as device
  loss and switches back,although initial device output succeeded. Instrumented
  logs explicitly report console HWND invalid. This is a second independent
  HWND-lifetime assumption to audit,not proof of invalid console handles.

The private-desktop HWND result is scoped evidence;owner's live host/RDP case
needs the resulting supported-device behavior,not a claim that its host was
observed. Console validity must be tested through actual input/output operations;
owned/borrowed traditional window decoration and placement need applicability
checks. Never simply suppress genuine handle-loss fallback.

S2 receives DPI-scaled initial client construction with correct margins and
bounded sizing,optional console HWND/menu capabilities,device-validity fallback
and actual input/Tab/cleanup proof. Close menus/control handling,shell settings
restoration and startup policy remain requirements. No product code changed in
S1;contained variants are not delivered fixes. S3 must exercise actual product
owned-console Tab as well as CMD reuse,not just an embedded root fixture.
Existing tests use embedded roots/constructed windows and separate launch routes;
passing those does not establish this combined startup+DPI+owned-Tab contract.

Probe failures from a three-second window-discovery deadline are invalid
startup verdicts;retry uses a12-second discovery bound. Diagnostic variants
and logs remain local under ignored build,each route bounded under60seconds/
2MiB. Product processes are terminated only if their bounded close does not
finish. No foreground activation or desktop switch by the controlling probe.

Admission/node ledger and documentation gates pass;scope/expected/actual[],new0,
historical1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342,
infeasible81) unchanged. S1 diagnosis retained;T29 remains active and unclosed.
Three P22 products unchanged;no code-only build or successful repair claim.
