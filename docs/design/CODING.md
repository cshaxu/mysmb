# Source Layout

## Current And Target Trees

T44 places production sources in the owner-required topology:
shared components at `src/lib/{kvm,dos16,win32,win16}`, translated Mario code
at `src/app-mario/core`, and Mario-specific I/O/presentation/assembly below
`src/app-mario/kvm`. The future Mine receiving boundary is
`src/app-mine/{core,kvm}`. Tests live at the corresponding paths below
`test/`, including nested production subsystems; there is no extra per-app
src/test layer in the target. After the owner's Win16 insertion, source
movement is complete in S3 and mirrored test movement is S4,
as recorded in [the completed migration](../history/M3-T44-nxvm-source-test-layout.md).
The current local product boundary is already `assets/mario` and future
Mine products use `assets/mine`.

```text
src/lib/{kvm,dos16,win16,win32}/  shared neutral contracts and host mechanics
src/app-mario/core/              translated original game logic
src/app-mario/kvm/{app,io,ppu,text,platform}/  Mario-specific assembly/presentation
src/app-mine/{core,kvm}/         receiving boundary; no imported game code
test/lib/{kvm,dos16,win16,win32}/ shared-owner tests
test/app-mario/{core,kvm}/       tests nested by their production owner
test/app-mario/kvm/ppu/validate/ test-only reference projections
test/app-mine/{core,kvm}/        receiving boundary; no acceptance claim
tools/                          generators and governance/build entry points
assets/mario/                   local mysmb16.exe, mysmb32.exe, mysmb64.exe
assets/mine/                    future local Mine products
```

## Independent library build and tests

Configure with `cmake -S . -B build/library -G Ninja -DMYGAMES_BUILD_MARIO=OFF
-DMYGAMES_BUILD_MINE=OFF`, selecting the intended C compiler and ccache launcher.
No ROM or app include path is needed. Build and CTest that directory; use
`mygames_win32_host_integration` for the real private-desktop window/Console
probe. The Mario-enabled tree adds `mysmb_win32_host_integration` for app
bindings, Tab, snapshots and borrowed/owned session lifecycles.

Shared fixtures are built by their library CMake owner and live in matching
`test/lib` directories. The cross-library dependency gate is
`test/lib/test_dependency_purity.py`; Mario's separate gate covers app/core/PPU
boundaries without duplicating library assertions. Physical-host joins are
named integration targets, not silently skipped unit tests.

`Build-Dos16LibraryProbe.ps1` produces model-qualified static device libraries
and no-game clients with separate S/L object directories and matching CRT.
`Build-Win16LibraryProbe.ps1` qualifies the neutral USER client with the chosen
memory model and owner-provided SDK/CRT. Never link S objects to L libraries.
Actual Win3.x/DOS execution is a separate integration proof from host mocks.
Temporary runtime copies and every output stay below ignored build.

The reusable declarations are in `src/lib/*`; Mario `kvm/io` contains its
own controller/save/APU/palette and presentation assembly. Its codecs and
synthesizer are shared between Mario platforms, not imported by another app.
Apps own every keyboard/mouse meaning and every refresh/dirty/deadline policy.

## Files And Names

Translated files use subsystem names, not arbitrary ROM addresses. Every translated file or routine records its address provenance in an adjacent mapping record. Generated source remains beneath ignored `generated/`.

## Source Organization

`io/` includes its own contract headers and portable C90 `string.h` memory operations;
the contained `io/file` service also uses portable `stdio.h`. These standard
operations add no game or device dependency. It owns decoded two-port input,
a borrowed read-only256x240indexed frame or synchronous bounded row producer,
an owned ordered audio snapshot,
and selected80x25/retained80x50text cells. Cells remain three bytes;the neutral
frame retains4000-cell capacity and adds selected rows and a16-entry RGB
palette with a source-color map. Selected glyph IDs and their Unicode/reflection
mapping live in lib/kvm/glyph. It contains no game state, ROM data, host API,
or text quantizer. The Mario integer audio renderer owns APU-to-PCM synthesis. Shared color lookup and indexed row scaling
consume only the neutral video contract. Its segmented borrowed views use explicit far pointers under both DOS16 and
Win16; application state remains independent of host pointer width.
Existing game and platform representations remain until their admitted
adapter migrations; the boundary test checks their numeric compatibility.

`text/elements` is an isolated, optional element-template
compositor. It consumes explicit immutable presentation descriptors and emits
the neutral IO text frame; it has no RAM/OAM/resource or host dependency.
S2 adds optional per-instance source-decision observations and DMA latching
under core/observation,plus read-only actor/background/HUD
assembly. Both roots enable observations and bind an early Tab text preview.
DOS allocates the full text frame/workspace capacity for exclusive authored
text or bounded pixel rows (15532bytes after layout/palette metadata);
only the active synchronous presenter view is valid,and every graphical band
rebuilds after text. Neutral row views retain absolute logical coordinates and
expire before the next producer call;the legacy full-frame path stays supported. Windows uses a real console.
Observations are outside original
game state;observer_snapshot explicitly serializes both phases into schema2's
opaque presentation extension. Full source entries retain stable anchors even
after partial overwrite. Legacy schema1 lacks those receipts and invalidates
them on restore while retaining the destination's observation preference.
The DOS transaction workspace uses a bounded far-heap allocation. The dormant
`validate/text_frame` pixel sampler is not used by this module.

`text/compact_elements` is the independently authored25-row art bank;
`text/elements` retains the50-row bank. Shared actor/background/caption traversal
uses the selected layout. `text/layout` owns frame initialization and source
palette binding;hosts consume neutral RGB/cells only. At most16palette colors
are resident:additional source hues use the nearest admitted RGB entry.
Compact source-rectangle projection preserves committed OAM ownership and
partial visibility without decoding CHR or executing a game selector.

Background text assembly exports authored-cell occupancy in its2900-byte
caller-owned far workspace. Actors use a separate500-byte far claim map and
consume committed entries in original priority order. Each entry keeps its
own palette/behind-background flag;only authored opaque cells claim priority.
Independent chunks/effects use their own positions,while whole actors retain
source-selected template anchors. These maps contain no CHR/pixel samples.
Player receipts also latch pre-throw graphics,executed partial/full throw
and actual one-sided swim-kick replacement. No selector is rerun. Vine
cap/leaves,platform spans and flag/score components use their own completed
entry positions;small components align to a cell center within their source
rectangle so a one-row authored glyph cannot disappear between cells.

`text/scene` composes background and actor cells with the
same far workspace on every target. The Win32 console device consumes only
the neutral text frame and physical events;the root retains one game/audio
instance while switching presenters. Shared IO accepts one Tab press until
release. The early preview does not certify unfinished title/misc artwork.

`io/control` owns application-request lifecycle independently of the game.
The third input byte carries requests;the two controller bytes keep their
original meaning. Roots consume the shared exit latch before advancing a tick;
physical adapters may buffer events but do not decide application termination.

`io/snapshot`, `snapshot_store` and `snapshot_keys` own portable file bytes,
one staged transaction and shortcut edges. Product roots capture only on P;
legacy cache APIs remain compatible but have no product storage instance.
Header/payload streaming removes the full-file wire buffer. Fixed-width program
bytes remain opaque to IO. `app/game_snapshot` marshals public game fields;
Win32 audio snapshot modules marshal host synthesis state arithmetically.
`io/file` provides stdio services;each host supplies executable-path,
replacement and device-reset services. Only roots connect these owners.

`src/app-mario/core/` cannot include host headers or platform macros. `src/app-mario/kvm/platform/` cannot mutate game internals. `validate/` is linked only by tests and recorders;it is absent from products. CMake selects `mysmb-win32-x86`, `mysmb-win32-x64`, or `mysmb-dos16`; compile definitions are permitted only beneath the platform roots. The OpenNT 16-bit C compiler verifies the same core in real-mode large-model mode; the later DOS adapter owns linking the full MZ executable. Modern 32/64-bit compilers run the Win32 product.

## Component boundaries

PPU storage is one embedded ppu/state object;CPU RAM,source decisions and NMI
startup guard now live in core;all translated routines and observation receipts are now core. The DMA primitive
borrows the original CPU OAM span;its caller keeps commit timing and receipt
order. app snapshot binds the same numeric fields in the same byte order.
The independent ppu/frame target consumes only const PPU state and neutral IO
types;composition owns its selection. Core has no compositor dependency.
All translated OAM/APU writers remain in core. Authored text and snapshot
receipt encoding belong to text;render/frame/page projections belong to validate.

S6 separates core observation receipts from text scene/snapshot consumers.
Core links only PPU storage;app snapshot links the independent text codec.
Validation projections link only `test/app-mario`/recorder targets;no product linkage.

## Platform component boundary

ppu/frame uses one compositor for canonical and slot views. io/video explicitly
declares32-entry slot-to-master views;io/palette_expand also owns allocation-free
nibble expansion. Both products use slot views. DOS nibble assembly/DAC shadow
and Windows RGB conversion remain host-owned. Mode/reset invalidation is device
lifetime logic. The DOS loader initially reserves4KiB optional near heap beyond
initialized data/stack;the original startup derives the actual heap end from
the PSP allocation,capped at64KiB. Near allocation failure keeps far fallbacks.

io/palette_expand owns the default cached or allocation-free span expansion
and zero-fill path;ppu/frame always uses it when no host acceleration succeeds.
io/planar_frame owns the portable uniform-row fill as well as exact geometry.
Host assembly is an equivalent encoder under the neutral span contract,not a
separate feature path. Windows and DOS composition bind the same capabilities.

T44 S2 adds the native Win16 composition root alongside dos16 and win32.
Shared planar pixel layout is
io/planar_frame;it knows only neutral pixels,dimensions,capacity and an optional
synchronous row encoder. The DOS root supplies its private dos16/planar_row
encoder. Native bands deinterleave256x240identity coordinates into64-byte plane
rows;the retained scaled/plane layouts are separate from the production native
chain4 device. Graphics borrows4096source bytes inside the existing15532-byte
text/row store and submits directly. Shared IO imports no host declaration or assembly. File/path services
are io/file with portable stdio;replacement and executable discovery stay in
the appropriate host,whose declarations are host-owned. The retired pixel
sampler is validate/text_frame and links only to tests. No compatibility copy
or forwarding directory remains at the old platform locations.

Win16 P/O controls are app-owned and use the existing snapshot codec, validation
and synchronous file store. src/lib/win16 owns module-path discovery, backup file
replacement and the MMSYSTEM waveform queue. Mario io/audio_renderer is the
single integer synthesizer for DOS16 and Win16; device drivers consume PCM
without inspecting original sound commands. Saving pauses dispatch only for
the file operation; loading restores game/APU state and reinitializes physical
synthesis phase, matching the existing DOS save contract.
