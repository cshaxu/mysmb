# M3 T40: Win32 console-session identity

## Problem

After Tab switches text presentation to the graphical window, the product
closes its current `mysmb_win32_text_console` and detaches with `FreeConsole`.
A later Tab treats text entry as a new launch and re-runs launch policy, which
uses a `cmd.exe`/PowerShell parent-name whitelist before `AttachConsole`.
That is an incorrect initial-launch policy: any parent with a usable console,
regardless of executable name, must select text. It is also incorrect for an
already established console session and breaks arbitrary hosts, terminals and
RDP paths.

## Required behavior

Each borrowed text entry owns an explicit Win32 console-session object:
its CONIN/CONOUT handles, game screen buffer, borrowed-shell restoration data
and optional host window capabilities. Text -> graphics suspends and hides this
borrowed object without freeing its handles or detaching. Graphics -> text
resumes the same object and game screen buffer. A console allocated by MySMB
from an initial graphical session closes when graphics resumes. No
parent-process lookup or `AttachConsole` may run on the borrowed resume path.
Before a borrowed console is hidden, its parent screen buffer is restored and
the separate MySMB screen buffer is cleared; this preserves the parent while
ensuring a stale game frame cannot reappear.

Only process shutdown, an explicit device-loss recovery, or a failed initial
open closes the object and releases the console attachment. Initial startup
selects text solely by whether the direct parent owns a console that can be
shared or attached; it never classifies a parent by executable name.

## S1: session-preserving Tab repair

- Add explicit Win32-only suspend/resume operations for an opened text console.
- Change the root presenter lifecycle to resume an existing suspended console
  before consulting startup policy or starting asynchronous acquisition.
- Keep device-loss recovery distinct from a normal user Tab: a lost input or
  output handle still closes and retries the graphical presenter safely.
- Extend the owned and borrowed lifecycle fixtures to prove two or more
  text -> graphics -> text cycles retain the same input/output/screen-buffer
  handles and never invoke a second console acquisition.
- Verify normal Escape/shutdown restores a borrowed shell exactly once.
- Replace the initial `cmd`/PowerShell name whitelist with direct parent-console
  detection, and prove a test executable with an arbitrary name starts its
  child in text when it shares that console.
- Prove graphical -> temporary owned text -> graphical closes the owned console
  window and clears its device object, while borrowed cycles retain identity.
- Prove borrowed text -> graphics restores the parent buffer and blanks every
  cell of the retained MySMB game buffer before that host is hidden.

## Boundaries

Only `src/platform/win32`, its platform tests and composition-root lifecycle
may change. No original game/ROM logic, shared IO/text/PPU semantics, DOS16
behavior, product process creation, or console-system configuration is
permitted. The repair receives no ROM nodes or control edges.

## Acceptance

Both x86 and x64 must demonstrate that a borrowed console survives repeated
graphical/text presentation switches using the same console object, while an
owned console closes on graphics return. The tests must reject a borrowed
resume path that calls launch policy, `AttachConsole`, `AllocConsole`, or
changes the object handle identity. Device loss and final shutdown retain their
established close behavior. Product source changes require focused Win32 tests,
platform-purity, x86/x64 builds, the unchanged DOS16 link, and refreshed local
target artifacts.

## S1 P1 delivery

The Win32 text-console object now has explicit suspend/resume operations.  A
normal Tab flushes stale console input, hides the console host when available,
and retains the existing CONIN handle, game output-screen-buffer handle and
borrowed-shell restoration state.  Returning from graphics validates those
same handles and reactivates the existing game buffer.  The root checks an
already-open console before calling initial launch policy, so the resume path
does not inspect a parent, call `AttachConsole`, `AllocConsole` or start the
asynchronous acquisition thread. Initial startup accepts any direct parent
with a shared or attachable console, without classifying its executable name.

If resume validation fails, the existing device is closed and only then may the
ordinary initial-open path run.  Thus device loss remains recoverable without
turning a normal presenter switch into a stale-handle reuse.  Process shutdown
still closes the retained object once and restores the borrowed shell.

The project-owned x86/x64 text-switch fixture passes with repeated borrowed
text -> graphics -> text cycles and compares retained input/output handles
across each cycle.  Both native self-tests, launch-policy and
console-capability smoke tests, platform-purity, and the unchanged DOS16 MZ
link pass.  Live RDP/Terminal interaction remains owner acceptance evidence.

## S1 P2 owned-console closure

A reported graphical launch -> Tab -> graphical return exposed that P1 had
retained MySMB's temporary owned console just like a borrowed console. The
root now closes the console object whenever it is not borrowed, which releases
the owned console host before restoring the graphical window. The fixture
asserts both a cleared device object and a destroyed owned-console HWND; it
continues to prove borrowed handle identity separately.

## S1 P3 borrowed-buffer clear

Borrowed Tab suspension now reactivates the saved parent screen buffer, clears
the retained MySMB game screen buffer to blank/default cells, then hides the
host. This does not erase the parent shell contents. The borrowed fixture reads
all 2,000 compact-frame cells from the retained game buffer after each switch
and rejects any surviving glyph or attribute.

## S2: Console API palette/index renderer

The owner has selected the repair directly: the Win32 adapter must always set
all sixteen `CONSOLE_SCREEN_BUFFER_INFOEX.ColorTable` entries through the
Console API, encode each `CHAR_INFO.Attributes` value from the frame's
four-bit foreground/background indices, and submit the bounded 80×25 or 80×50
grid through `WriteConsoleOutputW`. A successful
`ENABLE_VIRTUAL_TERMINAL_PROCESSING` call must not select a true-RGB escape
stream, call `WriteConsoleW` for colored game pixels or rely on terminal escape
interpretation.

S2 changes only `src/platform/win32/text_console.*`, its platform tests and
necessary composition declarations. It does not change shared game/ROM/PPU/IO
or text-scene semantics, DOS16 behavior, console-host configuration, the
NTVDM64 project or process topology. It receives zero ROM nodes and zero
control edges.

The implementation removes the VT-RGB output selection and dynamic terminal
stream buffer. It applies the full 16-entry palette on the initial canonical
palette and on every new source palette, preserves existing geometry,
borrowed/owned-console session identity, Tab, input, close and device-loss
handling, then always emits indexed `CHAR_INFO` cells.

Focused capability and text-switch tests must force VT-mode negotiation to
succeed and prove that the API palette/index path still runs. They must reject
any RGB escape write and compare all sixteen palette entries plus representative
foreground/background attributes. x86/x64 builds/tests, platform purity, the
unchanged DOS16 route and refreshed target artifacts complete the operational
proof.

### S2 P1 API palette/index delivery

The Win32 adapter no longer allocates a terminal RGB stream, enables output VT
mode, or selects a renderer from VT negotiation. Opening a text device applies
the canonical sixteen entries through `SetConsoleScreenBufferInfoEx`; each
source-palette change applies all sixteen source entries through that same API.
Every frame is submitted as indexed `CHAR_INFO` cells through
`WriteConsoleOutputW`. If a host refuses palette mutation, the existing
nearest-index fallback remains active, so geometry, input, session identity and
device-loss behavior do not become host-specific.

The focused capability fixture reports VT output as available, forbids a
`WriteConsoleW` reference at compile time, and verifies all sixteen palette
entries and all foreground/background attributes. Both Windows widths build
the product, capability fixture and text-switch fixture; both capability runs,
both product self-tests and platform-purity checks pass. The deleted terminal
stream fixture exercised only the retired RGB escape implementation. DOS16
production sources are unchanged; its retained artifact is therefore not a
claim of a newly linked DOS16 route for this Win32-only part.

### S2 P2 hidden-carrier geometry repair

Owner run16 acceptance of P1 failed with incorrect colours followed by an
automatic exit. A bounded hidden probe reproduced the exit and recorded the
native worker's `ERROR_INVALID_PARAMETER`: MySMB changed NTVWM's invisible
2x4 carrier font to its visible 8x16/8x8 preference, then the temporary
one-cell geometry transaction exposed an invalid sampled viewport. This is a
Win32 adapter geometry defect, not a missing colour field in the NTVWM/NTCON
wire contract: that contract transmits indexed cells and all sixteen RGB
palette entries.

P2 keeps the API-palette/index renderer. It prohibits both
`mysmb_win32_console_fit` and the temporary 1x1 geometry probe from changing a
Console without a usable visible host window. Such a carrier retains its
host-owned dimensions while MySMB writes only its bounded 80-column frame.
The second probe then identified the remaining defect: this Console's
`GetConsoleScreenBufferInfoEx` returns inclusive right/bottom viewport bounds,
while its setter consumes exclusive bounds. The palette helper therefore
converts those two fields before every ColorTable write, preserving geometry
without a run16-specific branch. The focused fixture rejects both a font API
call and a geometry mutation for a hidden carrier, and asserts the inclusive to
exclusive conversion. A repeated bounded run16 probe must remain alive past the
former failure interval and must not record a malformed captured rectangle
before this part can close.

The first P2 probe proved that retaining the 2x4 carrier and avoiding the
geometry transaction alone were necessary but insufficient. The final
inclusive-to-exclusive conversion keeps each palette update from shrinking the
captured window. The focused fixture passes for both Windows widths, and the
repeated bounded run16 probe remains alive throughout the former eight-second
failure interval without an invalid captured rectangle or error 87. Its lone
launch-time `ERROR_NOT_FOUND` configuration lookup is normal absence of an
optional text configuration and is neither a capture nor presentation failure.

### S2 P3 native and carrier bound contracts

P2 made the exclusive-bound conversion unconditional. Owner acceptance then
proved that a regular CMD Console also displayed incorrect colours: its native
inclusive `SetConsoleScreenBufferInfoEx` contract rejected the enlarged
rectangle, leaving the adapter on its default-palette fallback. Restoring the
native bounds fixed that standard path but reproduced the NTVWM worker exit,
so the two contracts cannot be represented by one unconditional rectangle.

P3 records the distinction as a device capability, not a host/process-name
branch. A usable normal console, Terminal-style console, or any non-carrier
font uses the standard inclusive rectangle unchanged. Only the documented
invisible 2x4 carrier selects the relay's exclusive right/bottom values. The
focused fixture proves both paths with the same neutral RGB palette and the
same indexed cells. It also rejects a process-name policy. The bounded run16
probe remains alive through the former failure interval; x86/x64 focused tests
and platform-purity verify the adapter boundary. Live colour acceptance in a
normal CMD and run16 remains the owner-visible final check.

### S2 P4 standard sixteen-colour fallback

Owner testing established that some Terminal-hosted Console API buffers accept
`SetConsoleScreenBufferInfoEx` yet do not visibly apply its `ColorTable` to
`WriteConsoleOutputW` cells. The API return value therefore cannot prove an
authored palette is visible. P4 keeps the P2 session and geometry repair, but
stops relying on custom `ColorTable` entries. For a source palette, it maps
each authored slot to the nearest fixed standard Console colour and writes
those foreground/background indices through `CHAR_INFO`. Canonical text frames
continue to use their standard indices directly. The focused fixture proves
both mapping cases, x86/x64 focused tests and platform purity pass, and the
Win32 artifacts are refreshed. This is a Win32 adapter result with zero ROM
nodes or edges.

### S3 VT capability presentation

S3 is admitted by owner direction to support both presentation capabilities
from the same neutral text frame. It must attempt to enable
`ENABLE_VIRTUAL_TERMINAL_PROCESSING` on the current output buffer, then confirm
the terminal path with a bounded Device Attributes query/reply before using
authored RGB SGR. Expired, absent or malformed confirmation retains S2's
standard sixteen-colour `WriteConsoleOutputW` mapping. The choice is solely the
result of buffer operations and the reply, never a process name, window title,
launcher or run16 rule. Scope is the Win32 console adapter and its focused fixture; no
shared text, game, ROM, DOS16, NTVDM64 or configuration code may change.
### S3 P1 dual capability renderer

P1 restores the earlier VT renderer as a capability-selected projection above
S2's retained standard Console fallback. After the game output screen buffer is
active, MySMB requests `ENABLE_VIRTUAL_TERMINAL_PROCESSING` on that exact
buffer. Success allocates the terminal stream and emits the text frame's
neutral RGB values with SGR foreground/background sequences. Failure allocates
nothing and retains the S2 nearest-standard-colour `WriteConsoleOutputW`
projection. The selection contains no launcher, process, window title or
run16 condition.

The focused fixture exercises the standard indexed fallback and an enabled-VT
RGB result from the same 25-row source frame, including the exact expected RGB
sequence. x86 and x64 focused capability and platform-purity tests pass. The
Win32 x86/x64 artifacts are refreshed; the unchanged DOS16 artifact is
retained. This remains a platform-only change with zero ROM nodes and edges.

### S3 P2 active VT terminal probe

P1 treated successful `SetConsoleMode(...ENABLE_VIRTUAL_TERMINAL_PROCESSING)`
as sufficient. Owner review correctly identified that this only proves the
Console accepted a mode bit; a relay can still fail to parse the emitted stream.
The revised adapter follows the official Microsoft Edit startup pattern: it
issues a non-printing Device Attributes query to the selected output buffer,
then uses a separate, bounded input-side parser to await a legal CSI `...c`
reply. It never consults `COLORTERM`, a process name, a title, a launcher or a
host setting.

The query begins asynchronously at text-device open and is polled by later
presentation calls for at most 80 ms, so Tab never blocks on terminal I/O.
Unrelated records are held and then delivered through the existing key-reader;
the reply itself is discarded. A completed reply enables the existing authored
RGB SGR writer. A timeout, read failure, incomplete sequence or queue bound
leaves the standard sixteen-colour Console API writer selected. This is a
channel-capability proof, not a false claim that a terminal-standard reply can
prove every possible RGB renderer; Microsoft Edit likewise requires modern RGB
terminal support after this negotiation. The same neutral frame feeds either
output path.

### S3 P3 probe-input ordering repair

Owner acceptance exposed an immediate exit from graphical launch and from Tab
entry. The device-query writer in P2 ran before the Console input handle was
placed in raw event mode. On an affected Console relay, the reply's initial
escape byte therefore arrived as `VK_ESCAPE` rather than a Unicode VT byte and
reached the existing shared exit owner. The process had no crash report: it was
correctly obeying an incorrectly delivered Escape request.

The input mode now changes before the output query is emitted. The bounded
parser also treats a zero-Unicode `VK_ESCAPE` as a tentative reply lead byte;
only a following legal CSI reply consumes it. Any non-CSI sequence or timeout
returns the held records to the ordinary input queue, preserving a real Escape
press. This keeps the capability handshake entirely in the Win32 adapter and
does not alter application-request or game input semantics.

### S3 P4 withdraw in-band terminal query

Owner acceptance established that P2/P3 still made graphical launch or Tab
entry flash and exit. A Device Attributes reply shares the same console input
queue as game controls, so no bounded parser can reliably distinguish a
terminal control reply from a real Escape across all Console relays. The
in-band query is therefore withdrawn rather than retained as a launcher- or
host-specific exception.

S3 returns to P1's explicit output-buffer contract: successful
`SetConsoleMode(...ENABLE_VIRTUAL_TERMINAL_PROCESSING)` on MySMB's active
screen buffer selects authored RGB SGR output; a failure selects S2's standard
sixteen-colour `WriteConsoleOutputW` fallback. No VT query is written, no
console input record is consumed or held by capability detection, and normal
Escape handling is again the sole owner of game exit. This restores RGB VT for
an owned console that accepts VT mode while retaining the fallback for a
buffer that rejects it. A future active terminal query requires a separately
isolated input transport and a newly admitted task; it cannot be added to the
shared game-input channel.
