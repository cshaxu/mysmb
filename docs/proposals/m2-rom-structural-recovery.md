# M2 ROM Structural-Recovery Candidates

## Status

This is a candidate set, not an allocation of numeric implementation tasks. M2 Td S1 governs this proposal and `states/QUEUE.md`; it creates no product code, no numeric T, and no future S allocation.

## Decision

The SMB1 ROM disassembly is the executable specification. A future implementation candidate must define a bounded ROM control-graph slice, its state-write set, a source-owner mapping, reference-frame inputs, focused regression, acceptance predicate, and stop condition. Platform code may collect host input and submit the completed frame only.

## Ordered candidates

1. **Frame-root conformance.** Reconcile cold boot, NMI ordering, input latch, pause, timers, OAM/VRAM submission, sprite-0 split, and operation-mode dispatch before object behavior.
2. **Area/PPU conformance.** Reconcile area parser, block buffer, nametable, attributes, palette, status and scroll state.
3. **Player conformance.** Reconcile input partition, physics, collision, pipes/vines, scrolling, size and injury.
4. **Enemy-stream conformance.** Reconcile `EnemiesAndLoopsCore`, `ProcessEnemyData`, ObjectOffset, groups, frenzy and initialization dispatch.
5. **Object/OAM/audio conformance.** Reconcile object handlers, visible OAM, queues and frame timing after their predecessors.
6. **Cross-platform route audit.** Prove the shared game frame contract across Win32 x86/x64 and DOS16.

No candidate becomes `M2 T<n> S1` until owner approval. Its detailed S breakdown is created only at that admission.