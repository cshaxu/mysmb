# M3 T43: MyGames code unification

## Objective

Create a controlled monorepo plan for the owner-managed Mario and Mine
applications.  The resulting repository will have application-owned code
below `app-mario/` and `app-mine/`, with reusable host integration below
`lib/dos16/`, `lib/win16/`, `lib/win32/`, and neutral presentation/input
contracts below `lib/kvm/`.

The common result is one coherent interaction model:

| Host and launch | Required experience |
| --- | --- |
| Win32/x64 from an interactive Console | Start in that borrowed Console's text view; Tab preserves game state while moving to the graphical window and back. |
| Win32/x64 started graphically | Start in a graphical window; Tab owns a temporary Console and releases it when graphical mode returns. |
| Win32/x64 text colours | Use authored RGB VT only on a normal visible terminal that accepts it; otherwise use the same indexed 16-colour projection as DOS. |
| DOS16 | Use the indexed 16-colour text projection and host-owned keyboard/video adapters.  An app declares whether a graphical presentation is available. |
| Win3.x | Double-click starts a native GDI window.  Tab changes presentation in that window; it does not require a modern Console. |

This task is an architecture audit and migration design.  It moves no
application source, imports no sibling code, changes no ROM-derived logic,
and produces no product executable.

## Read-only source and provenance boundary

Mine is an owner-managed sibling repository.  S1 reads it only to inventory
its implementation and build boundaries.  No Mine file, Git object, asset,
or generated output enters this repository during S1.  A later import needs a
separate source-policy receipt naming the Mine revision, ownership and
redistribution decision.  The preferred import preserves history with a Git
subtree or an equivalent history-preserving merge; it must not be a
copy-and-paste extraction.

No SMB ROM, disassembly, derived asset, trace, or generated resource is in
scope for this task.

## S1 audit findings

| Concern | MySMB current owner | Mine current owner | Common-library disposition |
| --- | --- | --- | --- |
| Game state and graphics content | `core`, `ppu`, `text`, and Mario app glue; ROM-equivalent PPU/OAM remains Mario-only | Mine core, app, board scene and game data | Keep in `app-mario` and `app-mine`; never extract game rules or render semantics. |
| Neutral text frame and 16-colour meaning | `io/text`, glyph mapping and colour projection | `io/text` cell/attribute and `text/scene` | Define one `lib/kvm` cell, palette and glyph contract.  App code writes semantic cells; hosts project them. |
| Text/graphics switch request and key state | shared IO request edge, platform roots | application/window key dispatch | Put mode-request edge state and normalized key events in `lib/kvm`; each app owns the response permitted by its capabilities. |
| Win32/x64 startup and Console lifecycle | parent Console detection, borrowed buffer preservation, owned Console allocation, Tab suspend/resume | simple parent/owned console open-close | Make MySMB's lifecycle the `lib/win32` baseline.  Mine adopts it; no executable-name or shell-name special case is permitted. |
| VT and indexed colour selection | conservative normal-terminal RGB VT versus hidden indexed carrier; `CHAR_INFO` 16-colour fallback | indexed `WriteConsoleOutputW` only | Keep terminal probing and output device policy in `lib/win32`; `lib/kvm` owns the sixteen semantic colours, not terminal escape sequences. |
| DOS16 text/input | BIOS/B800, keyboard, mode/pacing and device root | BIOS/B800, keyboard and mouse | Extract only host primitives and normalized events into `lib/dos16`.  Mario VGA/PPU composition and Mine board text remain app-owned. |
| Win3.x | absent | Win16 NE/MZ launch plus shared GDI window/text view | Extract Mine's generic Win16 USER/GDI lifecycle into `lib/win16`; port Mario through callbacks later.  Modern Console API is not a Win16 dependency. |
| Audio, save and timing | app/IO contracts plus Win32/DOS drivers | Mine has no equivalent product feature | Leave app contracts and device-specific drivers app-owned until a separately admitted generic service is justified. |

### Capability gaps to close after S1

1. Mario has no Win16 graphical host.  Mine supplies a proven NE/MZ and GDI
   starting point, but the Mario port must consume the shared `lib/win16`
   contract rather than importing Mine window code into its app.
2. Mine has no MySMB-grade Win32 Console session: it does not retain a borrowed
   game screen buffer across Tab transitions and has no authored-RGB VT path.
3. Mine DOS is text-only; Mario DOS already supports graphical/text Tab.  The
   shared contract therefore advertises text and graphics capabilities instead
   of forcing a graphical mode on every app.
4. Both projects encode text colours near their scene code.  The extracted
   interface must move host-independent semantic palette selection to
   `lib/kvm` without flattening Mario's authored 80x25/80x50 art or Mine's
   board glyph semantics.

## Target ownership

```text
app-mario/       translated SMB core, PPU, Mario text scenes, Mario app glue,
                 game-specific audio/save contracts and adapters
app-mine/        Mine game core, board scene, Mine app glue and data

lib/kvm/         neutral text cells/glyphs/palette, normalized input,
                 presentation request and capability contracts
lib/win32/       Win32/x64 window host, Console session, VT/indexed output,
                 Console and window input adapters
lib/win16/       Win16 NE/MZ bootstrap, USER/GDI window loop and in-window
                 text presentation/input adapter
lib/dos16/       DOS process/bootstrap, BIOS keyboard, B800 presenter,
                 optional mouse/timer and declared video-device primitives

tools/           one superbuild and target matrix
test/            library contract tests plus app-specific tests
```

`lib/kvm` contains contracts and reusable algorithms only.  It has no
`windows.h`, DOS interrupt, ROM, PPU, board, sound or save format dependency.
The three host libraries may depend on `lib/kvm`; neither app depends on the
other.  A host library reports physical key, focus, terminal and presentation
capabilities.  It never chooses gameplay actions, owns game state, redraws
app artwork, or introduces a helper process.

## Planned migration sequence

The steps are intentionally separated so that directory relocation, shared
contract extraction and behavior changes are independently reviewable.

### S2 — provenance receipt and monorepo baseline

Admit the Mine revision and history-preserving import method, introduce the
top-level superbuild, and place the two applications below `app-mario/` and
`app-mine/` with build bridges.  There is no behavior change.  Every existing
Mario and Mine target continues to build before library extraction begins.

### S3 — `lib/kvm` neutral contract

Extract text cell/glyph/palette, normalized keyboard event and
presentation-request contracts.  Migrate both apps to the contract while
retaining their own scene producers.  Unit tests cover each contract decision
once; integration tests cover Tab request delivery without host APIs.

### S4 — `lib/win32` Console and window integration

Promote the MySMB Console lifecycle as a reusable Win32 component and wire
Mine to it.  Test borrowed Console launch, graphical launch, borrowed
suspend/resume, owned Console lifetime, Tab round trips, visible-terminal VT
output and indexed fallback.  The output frame stays app-owned.

### S5 — `lib/dos16` text/input host integration

Extract BIOS keyboard, B800 text presentation, indexed colour projection,
timer and optional mouse primitives.  Mario retains its VGA/PPU compositor;
Mine retains its board text producer.  Test DOS text input and colour cells
against the same `lib/kvm` frame used by Win32 indexed fallback.

### S6 — `lib/win16` and Mario Win16 host

Extract the generic Mine Win16 NE/MZ and USER/GDI host, retain Mine's
in-window character Tab view, then add a Mario adapter with graphical and
text callbacks.  The acceptance target is a Win3.x double-click window and a
same-window Tab text view.  No modern Console functionality enters this host.

### S7 — product matrix, parity and cleanup

Run the Mario and Mine target matrix: DOS16, Win16, Win32 x86 and Win32 x64
where each app declares support.  Check launch classification, Tab state
preservation, colour policy, input mapping, window close/exit and no duplicate
platform implementations.  Remove superseded adapters only after both apps
use the shared owner.

## S1 acceptance and next admission gate

S1 closes only when this ownership map, capability gaps, import provenance
gate and staged migration order are committed and pass documentation
governance.  It does **not** claim the monorepo or Win16 Mario port exists.
S2 cannot begin until the owner accepts the directory/import strategy and the
Mine revision/provenance receipt is recorded.
