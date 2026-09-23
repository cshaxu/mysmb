# System Architecture

## Product Shape

MySMB is one native product with a portable translated program and separate host adapters. It is not a general NES emulator and does not depend on `nnes` at runtime.

## Modules, Ownership, And Assembly

`game/` owns translated routines, original RAM layout, object slots, frame phases, and neutral draw/audio command streams. `assets/` owns generated, owner-local ROM derivatives. `validate/` owns reference-execution comparison. `platform/` owns host input, time, video, and audio. `main` is the sole composition root.

## Product And Host Boundary

Game code may request neutral buttons, frame ticks, and command sinks. Windows and DOS adapters translate those contracts to their host APIs. Text rendering consumes game object/state commands; it never infers semantics from a bitmap.

## Runtime Admission Boundary

ROM material enters only at an admitted local build/research boundary. The normal native product embeds only locally generated owner material and is not a tracked or distributed output.
