# M2 candidate: Frame root

## Status

M2 T14 S1 is complete; M2 T14 S2 is active. P1 extracted the behavior-preserving seam; P2 maps every root label to its current C owner. P10 ports the PauseRoutine OAM branch: paused frames do not move ordinary OAM entries offscreen. P11 physically moves the real operating-mode tree and object loop from game.c into frame_root.c; game.c now retains only the public entry delegation and game-owned subordinate routes. P12 adds a direct `UpdateTopScore` regression for chained digit borrow and both-player ordering. P13 restores the ROM `DecTimers → FrameCounter → LFSR` order and prevents `$0009` from advancing on a paused frame. P14 regresses both paused and unpaused `$0009` branches at the shared frame boundary. P15 moves reset/cold-boot leaves out of game.c into the dedicated shared boot.c owner. P16 translates WBootCheck/ColdBoot into that owner and adds warm/cold branch regressions. P17 moves all NMI prologue leaves into frame_root.c and proves the cold-start visible output over eight fresh samples; the host constructor remains a separate container setup path. Its corrected fresh 600-sample ROM comparison has zero differences in OAM, work RAM, CIRAM, palette, audio commands and PPU scalars; x86 and x64 native traces are byte-identical. x86/x64 each pass 77 tests and OpenNT relinks the 16-bit target. Every P commit refreshes assets/mysmb16.exe, assets/mysmb32.exe and assets/mysmb64.exe.

## ROM scope

ROM lines 699-981 plus InitializeMemory at 2795: reset, cold boot, NMI, joypad latch, timers, LFSR, OAM/VRAM commit, sprite-0 split and operation-mode dispatch.

## Existing-code disposition

Split the mixed top of src/game/game.c into dedicated frame-root and boot owners. Preserve fixed RAM and verified cold-RAM layout; remove host-shaped sequencing.

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
