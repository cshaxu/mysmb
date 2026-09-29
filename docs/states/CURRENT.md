# Project Status

## Current Work

**M2 T44 S1 closed at 1,531 / 1,992.** It completed the fourteen-node shared
`BlockBufferChk_Enemy` through `RetYC` block-buffer chain. T44 S2 has not yet
been admitted; no implementation work may start in its vine-graphics scope
until its exact transfer, baseline and validation route are registered.

## M2 T44 S1 Closure

| Field | Record |
| --- | --- |
| Scope | Fourteen shared block-buffer labels from `BlockBufferChk_Enemy` through `RetYC`. |
| Result | All fourteen are ROM-match complete; 1,517 → 1,531 / 1,992. |
| Logic proof | Original-ROM ordinary-NMI records cover the player, enemy and fireball entries, table binding, carries, scratch state and return selection. |
| Operational proof | Focused x86/x64 checks, strict C90 product builds, DOS16 link and platform-purity audit pass. |
| Shared boundary | All gameplay changes remain under `src/game/`; platform code owns only input, timing and presentation. |
| Evidence | [T44 proposal S1 closure](../proposals/m2/t44-block-buffer-and-object-graphics.md#s1-closure-block-buffer-probe-and-coordinate-core). |

## Preserved limits

M2 remains incomplete. The next source-order chain is T44 S2 vine graphics;
it needs a separate admitted packet before execution. ROM-derived resources
and temporary records remain below ignored build output. The three
owner-authorized test EXEs remain in `assets/`.
