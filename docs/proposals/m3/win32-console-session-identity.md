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

The first successful text entry owns an explicit Win32 console-session object:
its CONIN/CONOUT handles, game screen buffer, borrowed-shell restoration data
and optional host window capabilities. Text -> graphics suspends and hides this
object without freeing its handles or detaching. Graphics -> text resumes the
same object and game screen buffer. No parent-process lookup or `AttachConsole`
may run on that resume path.

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

## Boundaries

Only `src/platform/win32`, its platform tests and composition-root lifecycle
may change. No original game/ROM logic, shared IO/text/PPU semantics, DOS16
behavior, product process creation, or console-system configuration is
permitted. The repair receives no ROM nodes or control edges.

## Acceptance

Both x86 and x64 must demonstrate that an owned console and a borrowed console
survive repeated graphical/text presentation switches using the same console
object. The tests must reject a resume path that calls launch policy,
`AttachConsole`, `AllocConsole`, or changes the object handle identity. Device
loss and final shutdown retain their established close behavior. Product source
changes require focused Win32 tests, platform-purity, x86/x64 builds, the
unchanged DOS16 link, and refreshed local target artifacts.

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

The project-owned x86/x64 text-switch fixture passes with repeated borrowed and
owned text -> graphics -> text cycles and now compares the retained input and
output handles across each cycle.  Both native self-tests, launch-policy and
console-capability smoke tests, platform-purity, and the unchanged DOS16 MZ
link pass.  Live RDP/Terminal interaction remains owner acceptance evidence.
