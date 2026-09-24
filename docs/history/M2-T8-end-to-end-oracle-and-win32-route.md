# M2 T8 End-To-End Oracle And Win32 Route

## Outcome

T8 closes the M2 bounded title-to-play oracle.  The native Win32 composition
root uses the same C90 `mysmb_game_tick` route as the deterministic tests;
no host gameplay state or emulator dependency was introduced.  Two frame-order
repairs were required during the audit: player death preserves the controller
partition from the collision frame, and the GameEngine tail clears that
transient directional partition after object processing.

## Source Scope And Frame Context

- Reviewed source spans are GameEngine and its `SaveAB` tail at `$94a5`,
  player control/death at `$b04a-$b5cb`, and ordinary player/enemy collision
  at `$dcfd-$ddcb`.
- The fixed script is Start for one native tick, neutral for three entrance
  ticks, then held Right for the bounded play window.
- The native run is sampled after complete `mysmb_game_tick` calls.  The
  local reference is sampled at PPU-frame boundaries; its game main-loop work
  can occur on either side of that boundary.  Raw probes and reference media
  remained ignored local outputs and were removed or retained only under
  ignored build directories.

## Checkpoints

| Route point | Native C90 | Local original reference | Disposition |
| --- | --- | --- | --- |
| Title transfer and entrance completion | mode 1, task 1, engine 8, page 0, x 40, y 176 | playable engine 8 after the corresponding title route | Same gameplay handoff; task 1 is the native area-work representation of the original display task 3. |
| Held-Right control point | 156 complete ticks: page 0, x 246, y 176, x-speed 24, screen x 134 | 158 PPU frames: page 0, x 246, y 176, x-speed 24, screen x 134 | Exact state checkpoint. |
| First ordinary-enemy injury | mode 1, engine 11, state 1; x-speed 0, y-speed FC; direction is cleared at the object-loop tail | mode 1, engine 11, state 1; x-speed 0, y-speed FC; direction is zero | Exact mode, player-state, and motion handoff. |
| Death arc | Same rising/falling y-position and y-speed sequence after injury | Same sequence | Exact after the input-latch and frame-tail repairs. |

The raw PPU-frame observation places the original injury at page 1/x 39/screen
x 183 and the complete native tick at page 1/x 42/screen x 186.  This bounded
three-pixel difference is a sampling-phase effect: ordinary-enemy collision is
performed before that enemy's movement, while nnes exposes RAM at the PPU
boundary after a variable amount of the next main-loop work.  The adjacent
observations prove the source order on both sides: the original moves the
enemy from x 50 to x 49 before its next collision pass; the native C does the
same.  No product coordinate adjustment is applied.

## Composition Review And Presentation Boundary

- `src/platform/win32/main_win32.c` owns only window timing, key mapping,
  initialization, and drawing.  Its single gameplay mutation path is
  `mysmb_game_tick`; x86 and x64 builds use that same core.
- The active Win32 gameplay renderer remains a simple host presentation after
  the title scene.  It does not yet draw the translated block/object command
  state faithfully.  That is the M3 adapter boundary, not a second gameplay
  path.
- The portable game layer remains free of `nnes`, ROM paths, host input state,
  and unbounded trace output.

## Similar-Issue Sweep

The closure sweep searched the Win32 root and portable C for direct game-state
mutation outside initialization, bypasses around `mysmb_game_tick`, reference
tool/product coupling, unbounded reference output, and stale checkpoint
claims.  The only production tick call is the Win32 step root; initialization
and local title binding are composition concerns.  Reference-tool names occur
only in policy, history, proposals, and an ignored local wrapper.  The two
frame-order defects above were the only production behavior hits and are
covered by project-owned smoke assertions.

## Verification

- ROM-free CTest: 23 of 23 passed.
- Owner-local CTest: 25 of 25 passed.
- Win32 x86 and x64 builds passed.
- OpenNT large-model portable-core compile passed.
- Documentation governance and `git diff --check` passed.

