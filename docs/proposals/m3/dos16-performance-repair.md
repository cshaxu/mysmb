# Candidate: DOS16 playability repair

The owner reported unusable DOSBox gameplay speed. [the admitted diagnosis](../../history/M3-T25-dos16-performance-diagnosis.md)
measures the frame rate and stage costs before implementation. Admit this
candidate only after reviewing that diagnostic result. It has zero ROM-node
scope and zero expected matches unless the admitted repair explicitly changes
that contract.

A future S may optimize only the measured dominant DOS16 path. A later S
checks old/new indexed frames, VGA bytes, game state, audio commands,
snapshots, pause and three-target builds, then repeats the same DOSBox workload
under default and explicit accelerated CPU settings. Do not reduce game ticks,
image content or input semantics to meet a frame target. Emulator results do
not establish real 25 MHz 486SX qualification, which remains M4.
