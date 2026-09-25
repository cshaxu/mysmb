# M2 candidate: Frame root

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 699-981 plus InitializeMemory at 2795: reset, cold boot, NMI, joypad latch, timers, LFSR, OAM/VRAM commit, sprite-0 split and operation-mode dispatch.

## Existing-code disposition

Split the mixed top of src/game/game.c into the only frame-root owner. Preserve fixed RAM and verified cold-RAM layout; remove host-shaped sequencing.

## Graph contract

Root of every frame. It calls mode dispatch only after NMI-side input, timers and PPU commit.

## Admission S plan

1. **S1 after admission** - Map root labels, branches, writes and current game.c locations; freeze NMI-return reference traces.
2. **S2 after admission** - Translate reset/cold boot and NMI prologue in ROM order, including input, timers, LFSR, OAM DMA and VRAM buffers.
3. **S3 after admission** - Translate pause, sprite shuffle/split and operation-mode tree; expose one game-owned frame boundary.
4. **S4 after admission** - Delete superseded root sequencing and compare title, start, pause and first-play frame routes.

## Acceptance

Root-owned RAM, visible OAM, CIRAM, palette, PPU phase and audio queues match reference. Every host calls one shared game frame entry.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
