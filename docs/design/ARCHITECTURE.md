# System Architecture

## Product Shape

MySMB is one native product with a portable translated program and separate host adapters. The primary development runtime is a native Win32 window, built for both 32-bit and 64-bit Windows. The core remains compatible with the later real-mode 16-bit DOS executable for a 25 MHz 486SX. It is not a general NES emulator and does not depend on `nnes` at runtime.

## Modules, Ownership, And Assembly

`game/` owns translated routines, original RAM layout, object slots, frame phases, and neutral draw/audio command streams. `assets/` owns generated, owner-local ROM derivatives. `validate/` owns reference-execution comparison through local tools such as `nnes`. `platform/win32` owns the development window, input, audio, and timing; `platform/dos16` later owns BIOS keyboard, PIT, VGA, and sound access. Each target has its own small composition root.

## Product And Host Boundary

The shared `io/` contract layer has no dependency on `game/` or `platform/`.
Composition roots connect decoded controller input and compositor output to
adapters. Video borrows the entire original indexed frame; audio snapshots
preserve every ordered write, including same-value retriggers. Game state
and output producers remain in `game/`; synthesis and device state remain
in adapters. Shared game text presentation assembles authored cells;the early
Win32 console preview consumes them through the same neutral IO boundary.

`app/game_io` marshals the public game output at the composition boundary.
It copies decoded input and ordered audio,borrows compositor pixels,and never
reads original RAM,changes game state,or calls a device. Win32's audio adapter
accepts only the neutral audio frame;its synthesis state remains host-owned.

DOS16 uses the same glue and full indexed frame. Shared IO owns the stable
64-color presentation palette and bounded row scaling;VGA owns paged storage,
DAC programming and video memory. DOS devices own physical held-key decoding,
BIOS mode lifetime and PIT sampling. Only its composition root binds local
immutable program resources and allocates the shared compositor's pixel store.
The DOS root also owns far-heap text storage and the presenter choice;VGA
devices accept neutral cells in80x50 mode. Mode changes retain keyboard/clock
state,and the same shared game scene is used by the Windows console preview.

Application requests are separate from both NES controller ports. Shared
`io/control` owns the sticky exit decision for Escape on all three targets;
adapters deliver a request and roots then close their devices. DOS buffers a
short press until decoded input consumes it;Win32 accepts window key messages
and window-close requests. No exit request changes original game state.

Game code may request neutral buttons, frame ticks, and command sinks. Windows and DOS adapters translate those contracts to host APIs. Text rendering consumes game object/state commands; it never infers semantics from a bitmap. The runtime contains no 6502 CPU, generic NES PPU, or generic NES APU emulator. Platform selection happens at CMake target boundaries; `game/` does not fork on platform macros.

Shared IO declares selected one-cell CP437-compatible glyph IDs,with unchanged
ASCII letters/digits and three-byte cells. Authored scene owners choose borders
and silhouettes. Windows explicitly maps IDs to Unicode console cells;DOS
submits the same IDs to its BIOS font slots. Neither host chooses game artwork.

## Runtime Admission Boundary

ROM material enters only at an admitted local build/research boundary. The normal native product embeds only locally generated owner material and is not a tracked or distributed output.

Shared `io/snapshot` owns fixed bytes,integrity/resource checks and a
last-running-boundary cache. Program-state bytes are opaque;composition owns
field binding and running eligibility. The codec validates canonical numeric
records with integers only. Win32 audio adapters convert host double values
arithmetically;DOS need not link floating-point code to read the same format.
`io/snapshot_store` owns staging,complete-write/close-before-replace and silent
error logging through file-service hooks. `app/game_snapshot` explicitly binds
all mutable game fields,preserves immutable resource pointers and decides
completed-running eligibility. Physical P/O edges and executable-directory
discovery belong to host adapters;roots commit validated game/audio candidates,
redraw and reset clock/input/device queues. No translated routine changes.
DOS marks audio-renderer state absent because it has no synthesis/device owner.
The same format is read by all targets;DOS cannot promise atomic replacement
or PCM continuation through intervening DOS gameplay.

Snapshot schema2 preserves the original core/audio offsets and appends an
opaque presentation extension. Shared game text presentation owns its
source-decision receipt encoding and validation;IO only checks the version,
length and integrity. New saves preserve producer/visible phases without
re-executing a selector. Schema1 remains readable with absent receipts and
therefore cannot promise immediate restored text. DOS allocates its transaction
workspace on the far heap;platform code owns memory lifetime,not receipt logic.
