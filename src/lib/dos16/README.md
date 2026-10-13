# DOS16 host services

`mygames_dos16` depends on `mygames_kvm`. Its portable decoder, PIT phase
conversion and text-cell conversion build in the native contract-test matrix.
The real-mode `host.c` and `video_mode.c` use the DOS large-model ABI and are
compiled by `tools/Build-OpenNt16Dos.ps1`; a DOS CMake system also selects them.

Applications own their composition root, input bindings, presentation choice,
game state and artwork. The library provides these services:

- `dos16/raw_keyboard.h`: Set-1 scan decoding, independent held states for
  ordinary and extended scans, and make/break/repeat receipts.
- `dos16/host.h`: one keyboard IRQ sink with opaque application context,
  idempotent teardown, BIOS/PIT timestamps, video-state capture/restoration
  and 80-column 25/50-row text-mode setup.
- `dos16/text_cells.h`: synchronous indexed KVM text-frame conversion to
  caller-owned B800-compatible words. The target must hold 2,000 words for
  25 rows or 4,000 words for 50 rows. Palette projection is owned by KVM.
- `dos16/pit_clock.h`: pure conversion of latched PIT status/count to phase.

The keyboard sink executes in IRQ context. It must complete bounded work,
avoid DOS/BIOS calls and allocation, and retain only application-owned input
state. Open rejects an empty sink or an already-owned keyboard vector. Close
restores the previous vector before clearing the sink. The clock samples
the BIOS-owned timer without programming a new rate or vector.

An app captures video state before its first mode change, explicitly chooses
graphics or text, writes its neutral frame, then restores video state during
teardown. The host does not assign Tab or Escape semantics. Mario's VGA/PPU
compositor and sound adapters are application components.

Owner-local tests cover portable decoder/cell contracts and every PIT phase.
Mario's native device probe exercises IRQ lifetime, timestamp progression,
text-mode geometry, graphics/text switching and complete video restoration
under DOSBox, using synthetic output rather than game resources.
