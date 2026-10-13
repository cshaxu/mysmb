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

The clock bounds each dispatch to four logical ticks and retains remaining
credit. Catch-up skips obsolete composition; a completed DIB is painted
synchronously so timer traffic cannot starve presentation. Focus changes
clear physical keys and reset host timing. No host code reads game state.

Actual runtime qualification covers Win3.1 enhanced mode with the standard
sixteen-colour VGA driver. Its device palette approximates source colours;
the 8bpp conversion is unit-tested but has no qualified 256-colour driver
receipt. Win16 audio, save/load and text devices are deferred capabilities.
