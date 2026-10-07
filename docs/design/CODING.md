# Source Layout

## Current And Target Trees

```text
src/core/       all translated ROM logic,RAM,OAM/APU writers and observation receipts
src/text/       authored immutable scene/element consumers and receipt snapshot codec
src/ppu/        neutral addressed/visible state and read-only shared pixel compositor
src/io/         neutral controller/video/audio/text contracts and glyph IDs
src/app/        public game-to-IO composition glue; no gameplay/device policy
src/assets/     generated owner-local declarations; never tracked
src/validate/   test-only projections,owner-ROM reference and trace comparison
src/platform/   win32 and dos16 host adapters
src/main-*.c    one small composition root per host target
test/           project-owned unit and integration harnesses
tools/          local generators and governance checks
assets/         ignored local package outputs: mysmb16.exe, mysmb32.exe, mysmb64.exe
```

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
mapping live in io/text_glyph. It contains no game state, ROM data, host API,
audio synthesis, or text quantizer. Shared color lookup and indexed row scaling
consume only the neutral video contract. Its sole target-dependent representation
is the far pointer required to address pixels with the DOS16 compiler.
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

`core/` cannot include host headers or platform macros. `platform/` cannot mutate game internals. `validate/` is linked only by tests and recorders;it is absent from products. CMake selects `mysmb-win32-x86`, `mysmb-win32-x64`, or `mysmb-dos16`; compile definitions are permitted only beneath the platform roots. The OpenNT 16-bit C compiler verifies the same core in real-mode large-model mode; the later DOS adapter owns linking the full MZ executable. Modern 32/64-bit compilers run the Win32 product.

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
Validation projections link only test/recorder targets;no product linkage.

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

Only dos16 and win32 are children of platform. Shared planar pixel layout is
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
