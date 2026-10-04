# Source Layout

## Current And Target Trees

```text
src/game/       portable translated logic and original RAM model
src/io/         neutral controller/video/audio contracts; inert text placeholder
src/app/        public game-to-IO composition glue; no gameplay/device policy
src/assets/     generated owner-local declarations; never tracked
src/validate/   owner-ROM reference adapters and trace comparison
src/platform/   win32 and dos16 host adapters
src/main-*.c    one small composition root per host target
test/           project-owned unit and integration harnesses
tools/          local generators and governance checks
assets/         ignored local package outputs: mysmb16.exe, mysmb32.exe, mysmb64.exe
```

## Files And Names

Translated files use subsystem names, not arbitrary ROM addresses. Every translated file or routine records its address provenance in an adjacent mapping record. Generated source remains beneath ignored `generated/`.

## Source Organization

`io/` includes its own contract headers and portable C90 `string.h` memory operations. These standard operations add no game or device dependency. It owns decoded two-port input,
a borrowed read-only 256x240 indexed frame, an owned ordered audio snapshot,
and reserved 80x50 text cells. It contains no game state, ROM data, host API,
audio synthesis, or text quantizer. Shared color lookup and indexed row scaling
consume only the neutral video contract. Its sole target-dependent representation
is the far pointer required to address pixels with the DOS16 compiler.
Existing game and platform representations remain until their admitted
adapter migrations; the boundary test checks their numeric compatibility.

`game/presentation/text/elements` is an isolated, optional element-template
compositor. It consumes explicit immutable presentation descriptors and emits
the neutral IO text frame; it has no RAM/OAM/resource or host dependency.
S2 adds optional per-instance source-decision observations and DMA latching
under game/presentation/text/observation,plus read-only actor/background/HUD
assembly. No product root enables text yet. Observations are outside original
game state;observer_snapshot explicitly serializes both phases into schema2's
opaque presentation extension. Full source entries retain stable anchors even
after partial overwrite. Legacy schema1 lacks those receipts and invalidates
them on restore while retaining the destination's observation preference.
The DOS transaction workspace uses a bounded far-heap allocation. The dormant
`platform/text` pixel sampler is not used by this module.

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

`io/control` owns application-request lifecycle independently of the game.
The third input byte carries requests;the two controller bytes keep their
original meaning. Roots consume the shared exit latch before advancing a tick;
physical adapters may buffer events but do not decide application termination.

`io/snapshot`, `snapshot_store` and `snapshot_keys` own portable file bytes,
staged transactions,last-running cache and shortcut edges. Fixed-width program
bytes remain opaque to IO. `app/game_snapshot` marshals public game fields;
Win32 audio snapshot modules marshal host synthesis state arithmetically.
`platform/file` provides stdio services;each host supplies executable-path,
replacement and device-reset services. Only roots connect these owners.

`game/` cannot include host headers or platform macros. `platform/` cannot mutate game internals. `validate/` is optional at runtime and cannot become the gameplay path. CMake selects `mysmb-win32-x86`, `mysmb-win32-x64`, or later `mysmb-dos16`; compile definitions are permitted only beneath the platform roots. The OpenNT 16-bit C compiler verifies the same core in real-mode large-model mode; the later DOS adapter owns linking the full MZ executable. Modern 32/64-bit compilers run the Win32 product.
