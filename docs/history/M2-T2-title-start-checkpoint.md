# M2 T2 Title Start Checkpoint

## Outcome

T2 translates the admitted title-menu input and start branch into the portable
C90 game layer. The translation records the actual ROM provenance for the
controller latch (`$8e5c-$8e90`), title/menu dispatch (`$8231/$8245`), and
start route (`$8255`). It preserves the original select/start edge behavior,
the Start and A+Start branches, the Continue world/area mirrors, first-game
flags, score/coin clear, and the mode/task transfer into gameplay.

The game layer exposes a neutral checkpoint schema. No host API, emulator, or
owner asset enters the portable runtime.

## Evidence

- The project-owned smoke test covers Start, held-Start suppression, Select
  one-shot behavior, and A+Start Continue mirrors.
- A temporary ignored reference harness ran the owner-local NROM from a stable
  title point, injected one Start event, and advanced a bounded window. Its
  neutral result was `mode=1 task=1 demo=0 world=0 area=0 hidden=1
  offhidden=1 trap=0`.
- The native boundary checkpoint immediately after the same Start semantics is
  mode 1/task 0 with demo 0, world/area 0/0, and both 1UP flags 1. The later
  reference task value is expected: its bounded window also executes
  InitializeArea, which is the next admitted route.
- ROM-free CTest passes 9 of 9. Owner-local title CTest passes 10 of 10. x64
  and x86 Win32 builds and the local OpenNT large-model core compile pass.
  Documentation governance and `git diff --check` pass.

## Audit

The review found that the first implementation of A+Start copied only the
visible world/area pair. ROM `GoContinue` also updates off-screen world and
area mirrors; the repair is covered by the smoke test. The portable game layer
contains no host input read, platform macro, or stale source-side post-shift
address provenance.

## Transfer

M2 T3 owns ROM `$92b0`, `$9508`, and `$9c03`: it must translate the area
bootstrap that advances gameplay task 0 to task 1 and consumes the pointer
state established by T2.
