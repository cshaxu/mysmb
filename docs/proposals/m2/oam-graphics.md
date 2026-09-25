# M2 candidate: OAM, offscreen and graphics

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 14460-15069: player/enemy/misc graphics, relative positions, offscreen bits, bounding boxes, OAM writers and output handoff.

## Existing-code disposition

Reorganize every *_gfx.c and frame_snapshot writer by ROM OAM owner. render.c may only derive from canonical output, never infer actors.

## Graph contract

Consumes final gameplay state and produces source-ordered OAM plus game-owned sprite split/visible PPU state.

## Admission S plan

1. **S1 after admission** - Map every OAM byte writer, offset table and graphics helper to ROM labels.
2. **S2 after admission** - Translate relative position, offscreen-bit and bounding-box writers.
3. **S3 after admission** - Translate player and enemy/misc graphics dispatch, priority, animation and OAM order.
4. **S4 after admission** - Compare OAM and sprite-0/status split across title, movement, objects, enemies and endgame.

## Acceptance

All 256 OAM bytes, ordering, attributes, offscreen behavior and PPU split are game-owned and reference-equal.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
