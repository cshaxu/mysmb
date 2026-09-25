# M2 ROM structural-recovery coverage map

## Status

`M2 Td S3` governance work. This is a complete candidate map of the ROM executable structure, not a numeric implementation-task allocation. The 1,992-label source index remains authoritative in [the ROM migration inventory](../etc/architecture/smb1-rom-migration-inventory.md). No candidate becomes `M2 T<n> S1` without owner approval.

## How the map is complete

The disassembly has 1,578 labels that participate in explicit control-flow edges and 414 static, table, or unconnected labels. Each executable label belongs to exactly one source-line slice below; `InitializeMemory` is the single explicit exception and belongs to Frame root rather than its physical source neighborhood. A static/table label is reviewed with the slice that consumes it; it is never invented as a separate C function. This partitions the entire source index while preserving the actual call graph rather than pretending that the ROM is a linear program.

| Candidate | ROM source-line slice | Control-graph responsibility | Dependencies and outputs |
|---|---:|---|---|
| Frame root | 699–981, plus `InitializeMemory` at 2795 | reset, cold boot, NMI, input latch, timer/LFSR, OAM DMA/VRAM commit, sprite-0 split, operation-mode dispatch | root of every frame; supplies mode, input, timing and PPU phase |
| Title and terminal modes | 982–1385 | title menu, demo, victory, player-end-world, float numbers | entered by operation-mode tree; emits text/OAM/audio requests |
| Screen, text and status | 1386–1824 | screen routines, status lines, game text, area-parser scheduling | consumes mode/area state; writes VRAM buffers and fixed HUD state |
| Area graphics and parser | 1825–5314 except `InitializeMemory` | metatile rendering, attributes, palettes, area header/object parser, block buffer | feeds collision and scrolling; writes CIRAM/palette/area state |
| Game frame dispatcher | 5315–5582 | game mode, game-core routine, `GameEngine`, game-routine dispatch | invokes all per-frame gameplay slices in ROM order |
| Player route | 5583–6297 | player control, movement, state, pipes/vines/scroll interaction, player-driven block actions | consumes input, area collision and object state; emits player/OAM/audio events |
| Fireballs and bubbles | 6298–6729 | fireball spawn/core/background/enemy collision and bubble paths | invoked before enemy slots by `GameEngine`; consumes collision and enemy state |
| Blocks, items and misc | 6730–7787 | vines, coins, bump/break blocks, power-ups, misc objects, cannon/whirlpool/flagpole setup | invoked after player path; writes block buffer, object, score and audio state |
| Enemy stream and actors | 7788–11084 | loop commands, `ProcessEnemyData`, positioning, groups, frenzy, initialization and enemy handlers | six ROM slots after fireball; consumes area stream and collision state |
| Collision and world primitives | 11085–14459 | player/enemy/item/projectile collisions, bounds, gravity, movement, score and shared geometry | called by player, fireball, block/item and enemy slices; writes shared game state |
| OAM, offscreen and graphics | 14460–15069 | player/enemy/object graphics, relative positions, offscreen bits, OAM construction | consumes final game state; produces source-ordered OAM and sprite split state |
| Audio engine | 15070–16368 | sound-effect queues, priorities, music and channel handlers | consumes ROM sound queues; produces portable audio command state |

## Candidate execution packets

Each candidate has an audited admission S plan. These are implementation blueprints only; they become formal S1 through Sn after the owner admits the candidate as a numbered M2 T.

1. [Frame root](m2/frame-root.md)
2. [Title and terminal modes](m2/title-terminal-modes.md)
3. [Screen, text and status](m2/screen-status.md)
4. [Area graphics and parser](m2/area-parser.md)
5. [Game frame dispatcher](m2/game-dispatcher.md)
6. [Player route](m2/player-route.md)
7. [Fireballs and bubbles](m2/fireballs-bubbles.md)
8. [Blocks, items and misc](m2/blocks-items-misc.md)
9. [Enemy stream and actors](m2/enemy-stream-actors.md)
10. [Collision and world primitives](m2/collision-world.md)
11. [OAM, offscreen and graphics](m2/oam-graphics.md)
12. [Audio engine](m2/audio-engine.md)

## Actual graph, not a serial rewrite order

```text
Start/ColdBoot
  └─ NMI frame root
      ├─ input/timer/PPU phase ────────────────┐
      └─ operation-mode tree                    │
          ├─ title and terminal modes ── screen/text/status
          └─ game dispatcher ── area parser/graphics
              ├─ player ─┬─ blocks/items/misc ─┐
              ├─ fireballs ├─ enemy stream/actors ├─ collision/world primitives
              └─ OAM/graphics ──────────────────┘
                   └─ audio queues/engine
```

The arrows describe source-call or source-state dependency, not host-platform ownership. Every branch, state write and table read remains subject to its label-level checklist row before a candidate can close.

## Admission rule

When an owner chooses one candidate, its packet must cite the exact inventory labels and edges it will close, list its `src/game` owners and state writes, give ROM-reference input routes, and define a bounded regression. Only then does governance allocate the next numeric T and create that T's S breakdown. A candidate cannot absorb labels outside its listed source slice without a new governance decision.