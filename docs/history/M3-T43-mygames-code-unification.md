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

S1 established the design. The owner then admitted the Mario-first S2-S7
implementation and limited the current goal to completing the split and
preparing to import Mine. This task closes that receiving phase; actual Mine
import and Win16 runtime adoption remain a separately admitted future task.

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
| Physical keyboard and mouse input | shared IO/controller bytes and platform roots | application/window key dispatch | Put only lossless physical input-event contracts in `lib/kvm`. Each app owns every key/mouse binding, repeat policy and gameplay/menu/presentation meaning. |
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

`lib/kvm` contains contracts and reusable algorithms only. It has no
`windows.h`, DOS interrupt, ROM, PPU, board, sound or save format dependency.
The three host libraries may depend on `lib/kvm`; neither app depends on the
other. A host library reports lossless physical key, mouse, focus, terminal
and presentation capabilities. It never assigns an input meaning. In
particular, `lib/kvm` does not reserve Tab, WASD, J/K, mouse buttons, menu
keys, repeat behavior or controller mapping: each app maps received physical
events to its own game/menu commands and separately requests a view switch.
A host library does not choose gameplay actions, own game state, redraw app
artwork, or introduce a helper process.

## Planned migration sequence

The steps are intentionally separated so that directory relocation, shared
contract extraction and behavior changes are independently reviewable.

### S2 — Mario-only structural baseline

Create `app-mario/` and the top-level superbuild, then move MySMB source into
its app boundary with build bridges. The exact same DOS16, Win32 x86 and
Win32 x64 products must build before and after the move. Mine is not imported
and no public behavior changes. This establishes the receiving layout before
any shared-code extraction.

#### S2 admission

The admitted implementation scope is the existing MySMB source tree, its
project-owned tests and the CMake/build paths that name them. It is a pure
directory and build-ownership migration: no C function body, public behavior,
ROM mapping, resource input, app input binding or product option may change.
The root CMake file becomes a superbuild that adds `app-mario`; the application
CMake file remains the sole owner of Mario target definitions. Shared libraries
are placeholders only in this S and no Mine source is read or imported.

The pre/post acceptance comparison is: the same source inventory is reachable
only below `app-mario`, the root configure path remains `cmake -S .`, and the
existing Ninja x86/x64 product targets plus the OpenNT DOS16 build command
resolve source, tests and tools through their new ownership paths. Product
output names and locations remain unchanged.

### S3 — `lib/kvm` presentation and raw-input contracts

Extract neutral text cell/glyph/palette contracts plus lossless physical
key/mouse/focus event and presentation-request interfaces. Mario's text
scenes remain in `app-mario`; Mario alone maps events to controller buttons,
save/load, pause, exit and Tab. Unit tests cover each contract conversion
once; integration tests prove that app-owned bindings can request a view
switch without a host API.

### S4 — Mario-only `lib/win32` extraction

Move MySMB's window loop, Console session, parent/owned lifecycle, terminal
capability selection, VT/indexed present adapters and raw event capture into
`lib/win32`. `app-mario` keeps all input meanings and the decision to toggle
text/graphics. Test borrowed Console launch, graphical launch, borrowed
suspend/resume, owned Console lifetime, app-requested Tab round trips,
visible-terminal VT output and indexed fallback.

### S5 — Mario-only `lib/dos16` extraction

Move DOS bootstrap, BIOS raw keyboard, B800 text present, 16-colour projection,
timer and optional raw mouse primitives into `lib/dos16`. Mario retains its
VGA/PPU compositor, sound, game input mapping and text/graphics choice. Test
the physical-event and colour-cell contracts against the same `lib/kvm` frame
used by the Win32 indexed fallback.

### S6 — receiving seams for Win16 and Mine

Define the `lib/win16` callback/build seam and the future `app-mine` target
interface without importing Mine source. This is a compile-contract and
documentation task only: no fictitious Mario Win16 product is claimed and no
Mine file is copied. It makes the later history-preserving import mechanical
instead of forcing a second architectural redesign.

### S7 — Mario structural parity and duplicate-owner removal

Run the Mario DOS16, Win32 x86 and Win32 x64 matrix after all extractions.
Check application-owned launch binding, state preservation across app-requested
view switches, colour policy, input mapping, close/exit, game-state identity
and absence of duplicate MySMB platform implementations. Remove superseded
Mario adapters only after the shared library is its sole owner.

### Deferred import phase - Mine provenance and history-preserving import

Only after S2-S7 are accepted, record Mine revision/ownership/distribution
receipt, import its history beneath `app-mine/`, and prove its existing targets
through the superbuild. This S does not yet refactor Mine behavior.

### Deferred adoption phase - Mine adoption and Win16 delivery

Migrate Mine to the already-proven KVM/Win32/DOS16 owners, extract the generic
Mine Win16 USER/GDI and NE/MZ host into `lib/win16`, then add the Mario Win16
adapter. Each app retains its own keyboard/mouse semantics. The final matrix
covers the targets each app declares, including Win3.x double-click graphical
launch and in-window app-requested text view.

## S1 acceptance and next admission gate

S1 closes only when this ownership map, capability gaps, import provenance
gate, app-owned input rule and staged migration order are committed and pass
documentation governance. It does **not** claim the monorepo or Win16 Mario
port exists. S2-S7 deliberately require no Mine import. S8 cannot begin until
the owner approves the final receiving structure and Mine's revision/provenance
receipt is recorded.

### S1 closure receipt

S1 established the shared-candidate map, the rule that applications own all
keyboard and mouse semantics, and the Mario-first S2-S7 order. The Mine tree
was inspected read-only and is not imported. This receipt is design evidence
only; it does not assert any future library or Win16 Mario target exists.

### S2 closure receipt

S2 moved **288** Mario source files and **639** Mario-owned test files below
`app-mario/`; the root now owns only the superbuild.  The three target names
remain `mysmb-dos16`, `mysmb-win32-x86`, and `mysmb-win32-x64`.  Root
configuration, the focused core/I/O/launch/purity tests on both Win32 widths,
the OpenNT DOS16 link and its memory receipt passed.  The DOS product reports
384,656 bytes minimum loaded memory.  The M2 path ledger was reconciled to the
new file locations as metadata only; its incomplete final-certification status
and open obligations are unchanged.  No Mine content was imported and no
Mario C function body or input binding changed.

### S3 admission — `lib/kvm` neutral presentation and physical input

S3 creates `lib/kvm` as the only owner of portable fixed-width types, text
cells/frame geometry, semantic sixteen-colour palette projection, selected
CP437 glyph conversion, video-view contracts, and lossless physical input and
presentation-request event contracts.  It may move only host-neutral code out
of `app-mario/src/io`.  Mario retains NES controller bytes, all gameplay/menu
commands, save/load/pause/exit decisions, Tab meaning, mouse meaning, PPU/OAM
art, ROM logic and layout selection.  `lib/kvm` cannot name a Mario key,
controller button, menu action, Win32 API, DOS interrupt, PPU or game state.

Acceptance requires a separate `kvm` CMake target, one owner for every moved
contract, app-local translation of raw events into Mario commands, focused
unit coverage for cells/palette/glyph/event conversion, and unchanged x86/x64
launch/text behaviour.  DOS16 link is rebuilt if moved code enters its product
closure.  No Mine source is read or imported.

### S3 closure receipt

S3 establishes `lib/kvm` as the single source owner for portable fixed-width
types, cells and video contracts, the semantic sixteen-colour palette, CP437
glyph conversion, and raw physical input/presentation declarations.  The
former `io/color.*`, `io/text_glyph.*`, `io/types.h`, and `io/video.h` owners
were removed from Mario.  `app-mario/src/app/input_mapping.*` is the sole new
Mario policy adapter: it assigns WASD, J/K, Enter, either Shift, Escape, P, O
and Tab their Mario meanings; KVM assigns none.

`mygames.kvm-contract-smoke` and `mysmb.app-input-mapping-smoke` exercise the
new owners; both x86 and x64 focused core/I/O/launch/purity matrices pass.
The S2 relocation also required the Mario-owned Python checks to resolve the
repository's shared `tools/` and `build/` directories from their new
`app-mario/test/` location; their assertions and evidence scopes are unchanged.
The rebuilt DOS16 product links through the previously accepted, locally
contained Overlay Linker 3.65 route (tool SHA-256
`124a3c800edc16b60f696d35a9dfec798b68b78fe2ca90c5988ea76bdeab1a8a`), which
remains a build-only tool and is neither imported nor redistributed.  Its MZ
product is 361,067 bytes with 384,768 bytes minimum loaded memory.  This task
changes no ROM node or control edge, and no Mine source was read or imported.

### S4 admission — `lib/win32` host extraction

S4 moves only generic Win32/x64 host ownership from
`app-mario/src/platform/win32` into `lib/win32`: window lifecycle, borrowed or
owned Console lifecycle, terminal-capability selection, VT/indexed text
projection, raw keyboard/focus/mouse capture, timing, and device presentation.
The library emits only KVM physical events and consumes app-requested
presentation.  Mario retains `input_mapping`, controller state, all command
decisions, frame/PPU content, save/load, audio intent, and the decision that a
Tab event requests a view switch.  No Mine source or Win16 implementation is
admitted.

The receiving library must have no Mario names or game-state access.  The
Mario adapter must be the only location converting KVM events into Mario
commands.  Acceptance covers borrowed-console start, graphical start, a
borrowed suspend/resume round trip, an owned-console lifetime round trip,
visible-terminal RGB VT, indexed fallback, raw-event mapping, x86/x64 product
builds, and the unchanged DOS16 product link.

### S4 closure receipt

S4 creates `lib/win32` as the sole owner of reusable Win32/x64 frame timing,
parent-console detection, borrowed/owned Console lifecycle, terminal
capability and text presentation, raw key normalization, and generic window
geometry. The former Mario host leaf sources were moved there and are built
once through `mygames_win32`; no forwarding copies remain under
`app-mario/src/platform/win32`.

Mario retains the composition root, input meaning, controller state, Tab/P/O/
Escape decisions, core/PPU calls, audio and snapshot consequences. The new
boundary is a lossless KVM physical event followed by
`app-mario/src/app/input_mapping`; the library has no Mario identifier,
controller bit, PPU/core include, or application request. During the move a
release-edge gap was found: P/O had notified the Mario snapshot gate only on
press, leaving a key held after its first use. The app mapping now emits the
same app request on both non-repeat edges; the root forwards `pressed` to the
existing app-owned gate. This fixes repeated save/load without assigning a
Mario command to `lib/win32`.

Test ownership is closed as follows: `mygames.win32-contract-smoke` covers
the library's rows/frame-wait/launch public contracts;
`mysmb.app-input-mapping-smoke` covers Mario P/O edge semantics;
`mysmb.win32-keyboard-smoke` covers the raw-event-to-Mario boundary; and the
composition-root snapshot/self-test fixtures cover real window messages,
focus, snapshot delivery and teardown. The full matrices passed: x64 258/258
and x86 289/289. A fresh DOS16 Link 3.65 build completed with
`mysmb-dos16.exe` at 361,067 bytes and 384,768 bytes minimum loaded memory.
The purity sweep found no Mario/core/PPU/request symbols in `lib/win32` and
no duplicate former leaf owner. Documentation governance passed.

The run16 probe was intentionally non-authoritative: in the non-interactive
pipe host, both an ordinary DOS command and LINK return the documented host
status 87 before DOS execution. This neither validates nor rejects NTVDM64 or
LINK. A later interactive Console probe may run `run16 --wait LINK /?`; this
S makes no NTVDM64 source or configuration change.

### S5 implementation checkpoint (not closure)

The shared DOS16 library now owns Set-1 physical make/break/repeat decoding,
PIT phase conversion and indexed KVM cell-to-B800 word conversion. Mario's
adapter still assigns controller, save/load, exit and presentation meanings.
The PIT exhaustive unit test moves with its production owner. The library
cell test checks full 25/50-row buffers and end sentinels; its initial
two-cell fixture was invalid and its earlier passing result is discarded.
The library purity gate now resolves the actual repository root; previous
empty-directory scans are not reused as evidence.

The synthetic DOSBox device probe links against the extracted objects and
passes two graphics/text round trips, 61,440 buffered and direct pixel checks
with zero mismatches, and restoration to the original video mode. The fresh
OpenNT compilation and DOS LINK 3.65 product link also succeed. These are
local operational checks, not new ROM-equivalence claims. S5 remains open:
finish the DOS host-lifecycle ownership review, current-product matrix and
test-owner closure before advancing to the Win16/Mine receiving seam.

The continued extraction moves keyboard IRQ capture/acknowledgment and
installation/restoration, BIOS/PIT timestamp sampling, BIOS 25/50-row setup,
and video mode/font/cursor capture/restoration into the DOS host. The IRQ
calls an application scan sink with an opaque context. The native probe
additionally checks empty/duplicate keyboard-open rejection, vector
installation/restoration, an advancing timestamp, both text row counts and
complete video-state restoration. All pass in DOSBox with synthetic pixels.
The linked product is 361,691 bytes with 385,392 bytes minimum loaded memory;
dynamic allocations are excluded from that loader figure. Mario's private
CRT hooks remain app-owned because their no-argument/no-environment-vector
premise belongs to Mario's composition root. The reused native/lifecycle probe
object inventory now has one build-tool owner.

A separate hidden-CMD run16 LINK help probe timed out without output. It
adds no NTVDM64 compatibility conclusion; the DOSBox link is the accepted
operational route. The x86/x64 complete matrices are still in progress, so
this checkpoint remains uncommitted and S5 remains active.

Final product-header inspection invalidated the old S4/S5 tree labelled x86:
it selected the x64 compiler and emitted PE64 despite its x86 filename. Its
290 passing tests are same-width evidence only. S5 uses the existing i686
Ninja/ccache preset for the real x86 replacement matrix, and CMake now rejects
a named x86/x64 target whose compiler pointer width disagrees. The resource-
bound x64 matrix passed 290/290 and its PE64 self-test passed. The real x86
matrix remains pending; neither the filename nor the old S4 receipt is reused
as width evidence.

### S5 closure receipt

The final actual-width matrix passes: PE32 i686 x86 290/290 and PE64 x64
290/290, with both product self-tests passing. DOS16 uses the same OpenNT
compiler and locally retained LINK 3.65, with the synthetic host probe passing
keyboard ownership, clock progression, 25/50-row setup, mode/font/cursor
restoration and zero pixel differences. The three local products were refreshed:
DOS16 361,691 bytes, PE32 411,787 bytes and PE64 365,163 bytes. The MZ minimum
loaded memory is 385,392 bytes, excluding dynamic allocations. No ROM nodes
or control edges are changed or promoted by this infrastructure task.

Raw Set-1/cell conversion and PIT phase tests live with the library; Mario's
keyboard/save/root tests retain app policy assertions. Hardware-only IRQ and
BIOS joins are covered by the native DOSBox probe. The source review retains
the original bounded PIT recapture and pending-IRQ calculation. The dependency
gate examines the actual libraries, and CMake rejects falsely labelled widths.
Superseded PIT owners are removed. The three previously tracked generated EXEs
are removed from the index while their refreshed local copies remain in assets,
following the current AGENTS/source policy. No generated product is published.

### S6 admission

Add only neutral receiving declarations, a Win16 interface target and an
optional app-mine superbuild hook. The current objective stops at import
readiness: no Mine source is read/copied and no Win16 runtime is invented.
The compile contract must expose app-owned callbacks for raw input and app-
requested presentation, with host capability results. An absent app-mine must
configure normally; the receiving documentation must identify the later
provenance/history-preserving import gate. Scope and new ROM matches are empty.

### S6 closure receipt

The optional `MYGAMES_BUILD_MINE` hook defaults off and rejects explicit enable
when the app CMake file is absent. The receiving directory contains only
import/ownership documentation. `mygames_win16_contract` exposes app-owned
physical-input, tick, presentation/exit and text/graphics producer callbacks;
it declares no implemented host entry point. Native PE32 and PE64 contract
tests pass, as do the KVM/DOS contract boundary tests. The actual OpenNT large-
model compiler compiles the callback fixture with far KVM pointers. The purity
gate includes this receiving contract. No Mine source is read or imported,
and no Win3.x runtime or product is claimed. S5 products remain the latest:
S6 changes declarations, build admission and tests, not product execution.

### S7 admission

Audit the final Mario/shared-library ownership and duplicate-owner removal;
run the complete actual-width matrices and confirm the retained DOS product,
host-probe receipt, local artifacts and compile-contract bindings. Verify
the disabled/absent Mine seam and explicitly unimplemented Win16 host. Final
acceptance stops at import readiness; future import/runtime stages require a
separate owner/provenance admission. No ROM node or gameplay work is admitted.

### S7 final receipt and T43 receiving-phase closure

The shared-owner/dependency audit passes: KVM is neutral; DOS16 and Win32
depend on KVM without either application; Win16 is an interface-only target.
The former Mario PIT and Win32 host leaf copies are absent. There is no old
root src/test tree. Mine contains only receiving documentation, and explicit
enable without an imported CMake file rejects configuration. Each app retains
its own bindings and presentation decisions; Mario core/PPU/art remain local.

The final actual-width CTest matrices pass 291/291 each. Both widths also
pass all 13 private-desktop host routes, including borrowed/owned console
lifetimes, input/focus, repeated Tab, snapshot, error recovery, launch/close
and interactive CMD wait/prompt restoration. This host gate found a root
join missed by ordinary CTest: switching cleared Tab-held state, and mapping
discarded its break edge. S7 repairs the app-local transfer and forwards both
non-repeat Tab edges. The app unit test covers break/repeat mapping, and the
real host routes now pass. No input binding or game rule is reassigned to a
library. Estimated zero production change became this bounded root repair.

All three local products are current: DOS16 361,691 bytes, actual PE32 x86
411,787 bytes and PE64 x64 365,675 bytes. Both native product self-tests pass.
DOS recompilation/link/memory verification passes, with the same 385,392-byte
minimum load and original output hash; S7 changes no DOS execution source.
The accepted DOSBox synthetic probe retains zero differences in 61,440
pixels, both text row counts, IRQ and video-state restoration. The callback
contract compiles with the real 16-bit large-model ABI. Product identities
and local assets match their verified builds. No generated EXE is committed.

T43 S1-S7 close under the owner's import-readiness scope. Former import/host
adoption phases transfer to the unnumbered
[Mine import candidate](../proposals/m3/mine-import-host-adoption.md).
This is structural/platform acceptance, not new original-ROM certification:
scope/expected/actual ROM nodes are empty, and the existing incomplete M2
final-certificate boundary remains unchanged. Win16 runtime and Mine game
code remain future work. The prepared tree is ready for their admission.
