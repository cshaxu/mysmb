# M2 Native Logic And Oracle

## Purpose

Turn the M1 title-command foundation into the original native C game route.
M2 translates program logic in dependency order and compares deterministic
native checkpoints with an owner-local reference. It preserves the shared C90
game layer, the Win32 x86/x64 product, and OpenNT large-model core compile.

## Candidate Order

1. **Title progression and deterministic checkpoint core.** Translate the
   title selection/start route, add game-owned input latching and a neutral
   checkpoint schema, and prove the first state transition against bounded
   local reference runs. This is admitted as M2 T1.
2. **Area bootstrap and background/object command route.** Translate area
   headers, page state, background commands, and object-parser setup needed
   after a title start.
3. **Player route and collision.** Translate player movement, collision,
   scrolling, and player-object state with fixed-input checkpoints.
4. **Object route.** Translate enemy, item, projectile, timer, score, and
   power-state ownership in bounded source-address slices.
5. **Mode route.** Translate death, restart, warp, continue, and completion
   transitions, including their original state preservation requirements.
6. **Audio command route.** Translate music and sound-effect command state as
   neutral game commands; host playback remains a later adapter concern.
7. **End-to-end oracle and Win32 route.** Run a bounded playable route through
   title, level, death or completion, and compare named native/reference
   checkpoints before M2 closes.

## Admission Boundary

Each implementation task records reviewed address ranges, local-only ROM and
source provenance, RAM/register assumptions, input script, frame checkpoints,
and comparison disposition. No task may add a CPU, PPU, APU, generic bus, or
runtime dependency on `nnes`. Generated owner data, traces, screenshots, and
ROM-embedded binaries remain ignored.

## M2 Exit

The Win32 x86/x64 native product is playable end to end through translated C
logic, the same core remains OpenNT large-model compilable, and deterministic
local oracle runs explain every admitted checkpoint difference.
