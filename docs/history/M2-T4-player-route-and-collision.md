# M2 T4 Player Route And Collision

## Outcome

T4 translates the admitted player-control route: input partitioning, walk/run
friction, jump/swim/fall gravity, crouching, climbing and auto-climbing,
normal and pipe entrances, terrain head/foot/side collision, pipe handoffs,
screen-edge clamps, and scrolling. The portable C90 layer has no host input
or emulator dependency.

## Evidence

- Source provenance covers player dispatch and physics at `$b04a-$b5cb`,
  scroll at `$af93-$b068`, entrances at `$b069-$b0e5`, and background
  collision at `$dc64-$de46`.
- Project-owned fixed-input tests cover neutral/right/jump/climb/pipe paths,
  timers, collision gates, and frame-ordering of movement and scroll state.
- A temporary ignored nnes probe used the owner-local NROM only. From the
  playable start checkpoint `page=0 x=40 y=176`, held Right reached the
  neutral checkpoint `page=0 x=246 y=176 xspeed=24 screen_page=0
  screen_x=134`. The native flat-ground fixture reaches the same checkpoint
  after 156 complete frames. No ROM path, bytes, trace, or generated adapter
  is tracked.
- ROM-free and owner-local CTest, Win32 x64/x86 builds, OpenNT large-model
  core compile, documentation governance, and diff checks pass.

## Audit And Transfer

The review repaired movement-direction ordering, player collision engine
gates, all alternate entrance routes, vine auto-climb dispatch, and the
one-frame `Player_Pos_ForScroll` handoff. Object-owned vine growth, blocks,
coins, springs, enemies, items, projectiles, timer/score, and power state
remain T5. Death, warp/completion modes remain T6; neutral audio remains T7.
