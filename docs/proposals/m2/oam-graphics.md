# M2 candidate: OAM, offscreen and graphics

## Status

**M2 T16 active — S1/P1.** T15/S4 is gated at the real-demo block/OAM boundary; T16 owns the prerequisite source structure and output primitives.

## ROM scope

ROM lines 14460-15069: player/enemy/misc graphics, relative positions, offscreen bits, bounding boxes, OAM writers and output handoff.

## Existing-code disposition

Reorganize every *_gfx.c and frame_snapshot writer by ROM OAM owner. render.c may only derive from canonical output, never infer actors.

## Graph contract

Consumes final gameplay state and produces source-ordered OAM plus game-owned sprite split/visible PPU state.

## Admission S plan

1. **S1 active (P1)** - Establish the OAM source tree without changing behavior: move each existing sprite writer under `src/game/oam/`, map every OAM byte writer, offset table and graphics helper to ROM labels, and forbid local relative/offscreen reconstruction in gameplay owners.
2. **S2 planned** - Translate relative position, offscreen-bit and bounding-box writers.
3. **S3 planned** - Translate player and enemy/misc graphics dispatch, priority, animation and OAM order.
4. **S4 planned** - Compare OAM and sprite-0/status split across title, movement, objects, enemies and endgame.

## Acceptance

All 256 OAM bytes, ordering, attributes, offscreen behavior and PPU split are game-owned and reference-equal.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.

## S1 P1: physical OAM source tree

The former top-level `*_gfx.c` files mixed source-owned OAM writers with general gameplay code, which made it too easy to hide missing `RelativeBlockPosition` state behind a local coordinate computation.  This P is intentionally behavior-preserving: nineteen existing OAM writer translation units now live under `src/game/oam/`; `CMakeLists.txt` and the OpenNT source list consume those same paths.  The public game interface remains `objects.h` until later S1 packets establish exact owner headers, so callers do not acquire graphics policy.  `block_gfx.c` is deliberately moved with the OAM writers, but `BlockObjectsCore` stays in `objects.c`; this makes the forthcoming `RelativeBlockPosition -> GetBlockOffscreenBits -> DrawBlock` boundary explicit instead of adding it to a title-mode route.  The migration inventory and frame-output ledger remain the exhaustive label/byte checklist; S1/P2 will bind their rows to the new file owners before any logic changes. x64 and x86 each pass 78/78 CTest cases. OpenNT recompiles the same paths and links the DOS MZ; its established `OLDNAMES.LIB` warning remains. Refreshed artifacts: mysmb16.exe SHA-256 F5E6E63FAE6DBB00920430CCE2CD497C2DA00E496895988B719D9923E7164EE2, mysmb32.exe 8F4E00DFF79E618E1F09BEFC42EDEF1DF63ED7998C0212BA3441262E961E9AB7, and mysmb64.exe 2D6061877489B73F176BABE5B971992F5B1921879AC8735CE613684F90F6AB55.

