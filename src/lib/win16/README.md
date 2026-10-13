# Win16 host and receiving contract

`mygames_win16_contract` is a C90 interface target linked to KVM. It currently
declares application callbacks. T44 S2 adds a USER/GDI graphical host and a
local NE/MZ build route. Mario uses the unchanged portable core and PPU;
its scoped Win3.1 runtime evidence is recorded in the T44 proposal.

Each application supplies a context, title and supported views. Input callbacks
receive neutral physical events; the application decides what they mean.
The app reports its requested presentation and exit state, and supplies text
frames or synchronous graphics bands. The graphical host owns event dispatch,
timing, GDI devices and window lifetime. It must consume callbacks without
assigning Tab, mouse, keyboard or gameplay meanings.

The contract fixture proves app-owned input can select a view and exit through
this ABI. It is a native compile/contract test, not Win3.x runtime evidence.
The current Mario admission is graphical-only: its app ignores Tab. DOS
graphics/text switching remains in the functional embedded MZ entry. Real
DOS-prompt handoff and a Win16 text presenter remain future work.

The host consumes canonical indexed bands, with bottom-up 8bpp DIB output or
explicit 4bpp reduction for a sixteen-colour display. The DIB conversion has
portable synthetic tests; these do not replace real Win3.x host acceptance.
The NE/MZ binder verifies unchanged DOS code, relocation and entry state and
preserves resident allocation bounds after the historical linker wraps it.

The host calls app update after input or an app-requested wake. The app returns
whether its image is dirty and a next wake delay (zero waits for input).
Only dirty output is recomposed; WM_PAINT replays retained pixels. Focus
changes clear physical keys and are delivered to the app; pause/rebase,
fixed tick rate, catch-up limits and frame skipping belong to the app.

Actual runtime qualification covers Win3.1 enhanced mode with the standard
sixteen-colour VGA driver. Its device palette approximates source colours;
the 8bpp conversion is unit-tested but has no qualified 256-colour driver
receipt. Win16 text/prompt devices remain deferred capabilities.

The audio service owns unsigned-eight-bit mono waveform buffers and the
Win3.x MMSYSTEM lifetime. It dynamically discovers exports, retries temporary
device ownership at most once per second and never blocks on a full queue.
Reset discards queued PCM; failed driver teardown retains owned memory rather
than freeing an in-flight buffer. A missing waveform driver is optional.

The file service discovers the executable using the supplied WinMain instance
and publishes a completed candidate with an eight-dot-three backup/rollback
sequence. It knows no game keys, snapshot schema, slot name or audio synthesis.
Mario binds these services to its shared snapshot and integer PCM owners.
