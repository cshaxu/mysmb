# M2 Reopened Frame Equivalence

## Why M2 Is Reopened

The previous M2 closure proved selected logic checkpoints, not the stated
end-to-end native result. A source audit found that gameplay rendering has no
translated PPU-update or OAM route: it copies one name table and emits a
16-by-16 actor identity marker. The Win32 consumer turns those values into
flat colors, while only the title path uses owner-local CHR. That contradicts
M2's playable-product exit criterion.

| Audit target | Current evidence | Required correction |
| --- | --- | --- |
| `game/render.c` | One name-table snapshot and actor identities only. | Carry the complete native frame output required by the translated PPU/OAM writers. |
| `area.c` and `objects.c` | Multiple routes explicitly omit OAM or defer name-table writes. | Translate each omitted output route with its source-address provenance. |
| `main_win32.c` | Gameplay chooses colors from tile ranges and draws rectangles; Select is absent. | Consume native frame output through locally generated CHR and map every NES button. |
| M2 oracle | Compares selected RAM checkpoints only. | Compare frame-indexed RAM, PPU-visible state, OAM, scroll, palette, and audio-command state against the owner-local reference. |

## Recovery Queue

T9 is admitted now. The following allocations are reserved in dependency
order; each remains a candidate until its predecessor closes.

1. **T9 — output ownership ledger and oracle contract.** Reconcile every
   PRG routine that writes PPU/OAM-facing state, define a portable canonical
   frame snapshot, and make the local reference recorder emit bounded,
   frame-indexed comparison data. No visual substitution is permitted.
2. **T10 — translated background output.** Translate dynamic name-table,
   attribute, palette, scroll, status-bar, metatile replacement, and update
   buffer effects into the canonical snapshot.
3. **T11 — translated OAM output.** Translate player, enemy, projectile,
   item, effect, score, platform, boss, priority, and animation-frame OAM
   writers. An object remains incomplete until its visible states compare.
4. **T12 — native Win32 frame consumer and complete controller mapping.**
   Decode owner-local CHR from the canonical snapshot for both background and
   sprites; map A, B, Select, Start, and directions without host game state.
5. **T13 — frame oracle.** Run bounded owner-local scripts through title,
   1-1, injury/death/restart, Warp Zone, flagpole/castle, two-player exchange,
   and audio transitions. Explain every mismatch at a declared frame phase.
6. **T14 — cross-width route proof.** Run the same native scripts on Win32
   x86/x64, preserve OpenNT large-model compilation, and prove one portable
   core path.
7. **T15 — M2 closure audit.** Re-run the PRG omission sweep, reject flat
   marker/placeholder output, review all frame differences, and update the
   roadmap only if every M2 exit requirement has direct evidence.

## Exit

M2 may close only when the owner-local Win32 x86/x64 build presents the same
translated background and sprite frame state as the reference for every
admitted route, accepts the complete NES controller set, and has no
unexplained RAM, PPU-visible, OAM, scroll, palette, or audio-command
difference. `nnes` remains a validation-only reference and is never linked
into the product.
