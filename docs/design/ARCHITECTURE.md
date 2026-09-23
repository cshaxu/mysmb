# System Architecture

## Product Shape

MySMB is one native product with a portable translated program and separate host adapters. Its primary runtime is a real-mode 16-bit DOS executable for a 25 MHz 486SX. It is not a general NES emulator and does not depend on `nnes` at runtime.

## Modules, Ownership, And Assembly

`game/` owns translated routines, original RAM layout, object slots, frame phases, and neutral draw/audio command streams. `assets/` owns generated, owner-local ROM derivatives. `validate/` owns reference-execution comparison through local tools such as `nnes`. `platform/dos16` owns BIOS keyboard, PIT, VGA, and sound access; later platform directories own their respective hosts. `main` is the sole composition root.

## Product And Host Boundary

Game code may request neutral buttons, frame ticks, and command sinks. DOS and later Windows adapters translate those contracts to host APIs. Text rendering consumes game object/state commands; it never infers semantics from a bitmap. The runtime contains no 6502 CPU, generic NES PPU, or generic NES APU emulator.

## Runtime Admission Boundary

ROM material enters only at an admitted local build/research boundary. The normal native product embeds only locally generated owner material and is not a tracked or distributed output.
