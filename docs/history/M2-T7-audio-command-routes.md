# M2 T7 Audio Command Routes

## Outcome

T7 translates the original sound engine's game-owned command state into the
portable C90 core.  It preserves the pause, area-music, event-music, square-1,
square-2, and noise queues; their RAM buffers; priority selection; length
counters; event-over-area ownership; death interruption; and the 1-UP lock on
square 2.  It deliberately emits no host playback and makes no APU, CPU, or
emulator dependency.

## Evidence

- The owner-local, byte-reconciled program identifies `SoundEngine` and its
  handlers at `$f2d0-$f694`, with command queues at `$fa-$ff`, buffers at
  `$f1-$f4/$07b1-$07b2`, and state counters at `$07bb-$07c6`.  The ROM and
  disassembly remained local inputs; no bytes, generated output, or trace was
  added to Git.
- `audio_smoke` supplies fixed original queue commands.  Its checkpoints prove
  event music takes precedence over an area command, death preserves the old
  area command while clearing square effects, small-jump priority wins over a
  lower square-1 bit and advances its 40-frame counter, 1-UP resists a Bowser
  fall request, and pause interrupts effects without consuming event music.
- The final increment passed ROM-free CTest (22 tests), owner-local CTest (24
  tests), Win32 x86 build, and OpenNT large-model core compilation.  The
  documentation gate and `git diff --check` also passed.

## Audit And Transfer

The T7 similar-issue sweep found no host playback import or emulator component
under `src/game`.  Every active queue/buffer address is centralized in
`audio.c`; `game.c`, `objects.c`, and `player.c` retain only producer writes to
the event-music queue, which are consumed by the new route.  This completes
the admitted audio ownership.  T8 now owns the deterministic end-to-end
checkpoint script and its Win32 presentation path.
