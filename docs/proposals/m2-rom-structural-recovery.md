# M2 ROM Structural Recovery

## Rule

The original SMB1 disassembly is the executable specification. A C node is accepted only when it has one ROM-node owner, matching control-flow edges, state-write evidence, and a reference-frame route. Platform code may collect input and present a complete frame only.

## S0 — inventory and contracts

| T | Work | Exit evidence |
|---|---|---|
| T0.1 | Classify every ROM control node and data table | One owner or explicit local-branch parent per item |
| T0.2 | Record C owner, RAM/PPU/OAM/audio write set and source range | No anonymous game-state writer |
| T0.3 | Freeze reference recorder, input scripts and frame comparator | Same trace schema on every route |
| T0.4 | Audit platform purity and frame contract | No platform game-state decision |

## S1 — frame root

T1.1 Cold boot and memory; T1.2 NMI order and VRAM/OAM transfer; T1.3 input, pause, timers and LFSR; T1.4 sprite-0 split and visible PPU commit.

## S2 — operation modes

T2.1 title/demo/menu; T2.2 GameMode task tree; T2.3 GameRoutines dispatch; T2.4 victory/game-over/two-player transitions.

## S3 — area and PPU state

T3.1 area pointers and headers; T3.2 parser task and object streams; T3.3 block buffer/metatiles; T3.4 nametable/attributes; T3.5 status/palette/scroll.

## S4 — player

T4.1 controller partition; T4.2 movement/friction/gravity; T4.3 player/background collision; T4.4 head and side collision; T4.5 entrance/pipe/vine/scroll; T4.6 size, injury and death.

## S5 — enemy stream and initialization

T5.1 EnemiesAndLoopsCore and ObjectOffset; T5.2 loop commands/frenzy; T5.3 ProcessEnemyData page/edge rows; T5.4 group enemies; T5.5 CheckpointEnemyID and initialization jump table.

## S6 — object logic

T6.1 normal enemies and background collision; T6.2 power-ups and blocks; T6.3 fireballs and projectiles; T6.4 misc objects; T6.5 hazards/platforms/Bowser/endgame.

## S7 — OAM and graphics

T7.1 player OAM; T7.2 normal/special enemy OAM; T7.3 items/projectiles/effects; T7.4 offscreen/priority/shuffle; T7.5 OAM DMA reference proof.

## S8 — audio

T8.1 queues; T8.2 music streams; T8.3 sound effects; T8.4 frame timing.

## S9 — portable products

T9.1 canonical frame contract; T9.2 Win32 x86/x64; T9.3 DOS16 adapter; T9.4 cross-width byte equality; T9.5 486 qualification.

## S10 — M2 closure

T10.1 title/start; T10.2 W1-1 movement and blocks; T10.3 items/fireball; T10.4 death/restart; T10.5 pipes/warp; T10.6 flag/castle; T10.7 two-player; T10.8 audio; T10.9 x86/x64 and platform audit; T10.10 unresolved-node audit.

Each T closes only with ROM source path, generated/reference script, frame comparison, x86/x64 result, and a sweep of adjacent callers. S10 closes M2 only when every admitted node and route passes.