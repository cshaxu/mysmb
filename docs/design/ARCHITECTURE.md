# System Architecture

## Product Shape

MySMB is one native product with a portable translated program and separate host adapters. The primary development runtime is a native Win32 window, built for both 32-bit and 64-bit Windows. The core remains compatible with the later real-mode 16-bit DOS executable for a 25 MHz 486SX. It is not a general NES emulator and does not depend on `nnes` at runtime.

## Modules, Ownership, And Assembly

`core/` owns the original RAM container and all translated CPU/OAM/source-sound routines. `core/observation` owns source-decision receipts;`text/` owns authored scenes and receipt encoding. `validate/` owns render/frame/page projections used only by tests and recorders. `assets/` owns generated, owner-local ROM derivatives. `validate/` owns reference-execution comparison through local tools such as `nnes`. `platform/win32` owns the development window, input, audio, and timing; `platform/dos16` later owns BIOS keyboard, PIT, VGA, and sound access. Each target has its own small composition root.

`ppu/state` now owns the single addressed/visible PPU storage and immutable
CHR binding embedded in the game container. Core retains all original NMI
control/write decisions and its startup guard. The DMA primitive borrows CPU
RAM OAM and commits visible bytes at the existing call point;observation commit
follows as before. The independent ppu/frame compositor now borrows const PPU state and has no
game-container dependency. The read-only compositor is separate from CPU decisions and host devices.

## Product And Host Boundary

The shared `io/` contract layer has no dependency on `core/`, `ppu/`, `text/`, `validate/` or `platform/`.
Composition roots connect decoded controller input and compositor output to
adapters. Video borrows the entire original indexed frame; audio snapshots
preserve every ordered write, including same-value retriggers. Game state
and output producers remain in `core/`; synthesis and device state remain
in adapters. Shared text presentation assembles authored cells;the early
Win32 console preview consumes them through the same neutral IO boundary.

`app/game_io` marshals the public game output at the composition boundary.
It copies decoded input and ordered audio,borrows compositor pixels,and never
reads original RAM,changes game state,or calls a device. Win32's audio adapter
accepts only the neutral audio frame;its synthesis state remains host-owned.

DOS16 uses the same glue and full indexed frame. Shared IO owns the stable
64-color presentation palette and generic bounded row scaling;VGA owns fixed
direct256x240-to320x400 enlargement without borders or source-row loss,
four32000-byte Mode X video planes,submitted from1280-byte16row scratch,
640x400 scanout,
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

Game code may request neutral buttons, frame ticks, and command sinks. Windows and DOS adapters translate those contracts to host APIs. Text rendering consumes game object/state commands; it never infers semantics from a bitmap. The runtime contains no 6502 CPU, generic NES PPU, or generic NES APU emulator. Platform selection happens at CMake target boundaries; `core/` does not fork on platform macros.

Windows launch policy selects text for a direct CMD/PowerShell parent with an
attachable console;other or unknown parents select graphics. The console
subsystem makes interactive CMD wait for the same game process;non-shell
entry detaches its startup console before showing graphics. Shell text uses
a separate game screen buffer in the borrowed console. Tab/error/exit restore
the shell buffer,title,input mode and window placement before detaching;
the shell buffer retains its own font,palette,cursor and contents. Tab back
reattaches to the same parent,with one game instance and no helper process.
Escape/root close exits only the game. Closing a borrowed host window itself
is Windows' shared-console close,which can terminate its attached shell too;
the game never explicitly closes or terminates that shell. An owned console
close posts root exit and waits for cleanup. DOS starts graphically.

Windows keyboard state is owned by the event adapter:window key/system-key
messages and console key records feed one held-key/short-press state. The root
samples it at a logical tick;no global asynchronous keyboard query is needed.
Either Shift and simultaneous aliases keep independent physical states.
Window focus belongs to local focus/activation messages,not global foreground
HWND equality. Console key records establish device input,including Unicode
character-only records;internal focus records are optional loss/gain hints.
Loss,presenter changes and snapshot restore clear stale game keys. A valid
subsequent console down needs no gain record. Tab/P/O/Escape retain their shared
application-request owners. No original game routine handles host input.
The console owns explicit input/output device handles and requests key records,
not terminal escape-sequence input. Device font size may shrink to fit its
unchanged80x50 shared frame on a small desktop;no artwork or game state changes.

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
opaque presentation extension. Shared text presentation owns its
source-decision receipt encoding and validation;IO only checks the version,
length and integrity. New saves preserve producer/visible phases without
re-executing a selector. Schema1 remains readable with absent receipts and
therefore cannot promise immediate restored text. DOS allocates its transaction
workspace on the far heap;platform code owns memory lifetime,not receipt logic.

Windows graphical geometry scales the unchanged indexed frame to the full
client area. Native sizing constrains16:15client units,with non-client and
DPI margins;minimum,maximized,restored and programmatic sizes share that
device owner. Zero-sized clients skip drawing;no crop or letterbox owner.

Console geometry belongs to the Windows device. A restored host repairs the
80x50buffer/view before presenting;maximized font remains unchanged. A bounded
in-flight clipped write defers a frame,while genuine handle loss keeps recovery.
Borrowed shutdown restores the original shell cell view after pixel placement,
so host rounding cannot silently remove a row. No geometry changes game state.

Text has an immutable core-state consumer dependency;core calls only its own
observation producer/commit API. App snapshot explicitly links text snapshot
encoding. Neither text scenes nor their codec are members of the core library.
