# M3 T29: Win32 window and console usability regression

## Current disposition

T29 S1-S3 closed. DPI sizing and valid-device console switching are repaired
and accepted within the actual x86/x64 host routes below. Live RDP/multi-monitor
hardware and universal cold-launch latency are not claimed. Remaining DOS
performance/ROM certification tasks retain their separate queue positions.

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


## S1 closure and S2 admission

Owner requests immediate repair. S1 diagnosis closes with named DPI/menu/HWND
findings above and explicit host/RDP limits. S2 accepts the Win32-only repair;
50-100platform lines plus150-250neutral actual-product probe lines estimated.
DPI initial client follows the window DPI;console handles/output define device
health,optional menu/window capabilities do not invalidate working cells/input.
Borrowed shell geometry is restored only when that window capability was saved.
Actual product x86/x64 cycles and original DOS16 build plus three EXEs required.
ROM scope/expected/actual[],new0;no game/PPU/text/DOS behavior change.


## S2 P1 closure and S3 admission

DPI initial client is built from96-DPI scale2 units using actual window DPI and
DPI-aware non-client margins. Initial creation/size normalization is guarded
until this rectangle is installed. At144DPI actual product clients are768x720
on both widths; subsequent Tab returns retain that size. DPI query zero falls
back to96. Existing aspect/maximize/restore/edge-drag tests remain passing.

Console acquisition now requires working devices and buffer geometry,not an
optional system menu or HWND existence. Borrowed placement is captured/restored
only when available,with cleared saved storage;input mode/title/cell view restore
remain mandatory. Frame presentation rejects invalid input handles and retains
existing output/geometry error recovery. Menu capability no longer closes a
valid console;root fallback is driven by actual presentation failure. No worker,
extra product process,game/PPU/text content or DOS behavior change.

Actual source diff:Win32 main+21/-3,text_console+13/-7,test+12/-0;new neutral
actual-product tool122lines. Four source/test/tool files,+168/-10. Similar-issue
sweep covers initial/minimized/restored/DPI rectangles,optional owned menu and
borrowed placement,root HWND-loss inference,input/output rejection,control-close
and shell buffer/font/title/input ownership. No remaining scoped source hit.

Both widths final source builds/link pass,5focused tests pass and13host route
groups pass including embedded DPI/invalid-input tests,owned/borrowed settings,
Unicode/focus/snapshot recovery,other/CMD/PowerShell/pwsh launch and actual CMD
CONIN Tab -> window Tab -> console Escape -> waiting prompt -> usable shell.
New actual-product tool verifies three text entries/two graphical returns,
4000-cell readback on each entry,80x50 buffers,preserved size,responsive root and
console Escape exit0. This also passes on the final assets binaries.

Original DOS16 compiler/linker rebuild and MZ/map check pass;DOS file305163bytes,
SHA256f0a281bf630431853d489e20fdabf7d622dc5f119133f9026c5f94423895ad6a
remains identical. Final Windows packaging removes COFF/debug metadata;all
retained runtime section RVAs/data are unchanged from tested linked products,
removed sections are debug-only. Final assets actual-product routes recheck them:
- mysmb32.exe308238bytes,SHA2567f51518be2fd9f992d953d8ded8114ee77adb64b20ab303e15182654a9babdde.
- mysmb64.exe320526bytes,SHA256687b01bcde43e57e1f1d5616d4c06a3e3cecb5b9681a71168aeef9b6c11ea975.
All three published files are bound to the compiled outputs. No new imported
resource or committed diagnostic binary;logs/prototypes stay ignored below build.

S2 closes;S3 accepts integrated review of these exact bindings,scope/purity,
retained route applicability and final documentation/node gates. S3 is audit-only,
estimated15-35neutral record lines,no new implementation or broad test rerun.
Live owner RDP and physical multi-monitor DPI dragging remain unobserved;the
host/device checks are scoped operational acceptance,not hardware/global ROM
certification. Synchronous console allocation retains host startup cost;no
indefinite hang occurs in passing actual routes. Configured DOS speed remains
unaccepted and queued separately.
Historical1992/1992,local1991/1992nodes,4260/4261controls(raw4342/infeasible81),
scope/expected/actual[],new0,custody unchanged.


Final bounded-tool check: x86 passes;one parallel x64 attempt misses root-window
publication within12seconds and is terminated by its cleanup. No text/Tab route
is credited from that attempt. Immediate sequential same-binary retry completes
all three entries/two returns/Escape in about5seconds. Similar early discovery
misses existed during S1 instrumentation. Cause of the isolated publication
latency is unproved;retain the failed receipt and do not claim universal cold
startup latency or live RDP qualification from finite successful routes.


## S3 P1 integrated closure

Review binds final assets to S2 product hashes and accepted runtime-section
metadata stripping proof. Actual final-assets tool passes both widths; x64
sequential repeat discharges the executed usability route,not a universal
cold-start timing claim. Five focused tests/thirteen host groups per width
retain their exact source/product dependencies. Reusing those accepted receipts
requires no further implementation or unrelated full-project replay.

Source sweep confirms all repair owners are platform/win32 plus neutral test/
tool logic. Optional HWND/menu/placement operations no longer decide console
validity;invalid input and existing output failures still reject presentation.
DPI initial sizes use actual window DPI and correct margins before first show.
Graphical/text cells,game state,PPU output,DOS input and toolchain are unchanged.
Three products have reviewed MZ/PE machine/subsystem/hash bindings and original
DOS16 relink equality;no assets beyond the existing owner exception are added.

S1 diagnosis,S2 repair and S3 integrated audit close. T29's reported window
shrink and inability to retain text mode have scoped actual-product proof.
The isolated private-desktop12-second discovery miss is retained in TODO with
its failed receipt and retry,not erased or described as repaired. Live owner
RDP and physical multi-monitor DPI checks remain applicability limits.
Documentation,node admission/closure and reviewed diff checks pass;historical
1992/1992,local1991/1992nodes and4260/4261feasible controls(raw4342/infeasible81),
scope/expected/actual[],new0,custody unchanged. Products remain S2 final hashes.
CURRENT becomes idle;pending PPU/DOS proposals remain unnumbered and unadmitted.
