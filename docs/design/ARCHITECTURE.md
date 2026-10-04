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
in adapters. Text cells are an inert contract until the later text task.

`app/game_io` marshals the public game output at the composition boundary.
It copies decoded input and ordered audio,borrows compositor pixels,and never
reads original RAM,changes game state,or calls a device. Win32's audio adapter
accepts only the neutral audio frame;its synthesis state remains host-owned.

Game code may request neutral buttons, frame ticks, and command sinks. Windows and DOS adapters translate those contracts to host APIs. Text rendering consumes game object/state commands; it never infers semantics from a bitmap. The runtime contains no 6502 CPU, generic NES PPU, or generic NES APU emulator. Platform selection happens at CMake target boundaries; `game/` does not fork on platform macros.

## Runtime Admission Boundary

ROM material enters only at an admitted local build/research boundary. The normal native product embeds only locally generated owner material and is not a tracked or distributed output.
