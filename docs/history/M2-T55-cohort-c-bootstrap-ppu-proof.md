# M2 T55 closure: Cohort C bootstrap, VRAM and PPU proof

T55 closed the source-order Cohort C bootstrap slice from
`RenderAreaGraphics` through `WritePPUReg1`.

- 67 of 67 scoped nodes are current-exact.
- 137 feasible control relations are exact; five relations are source-infeasible
  and retain their instruction-semantic disposition.
- All 25 scoped material producer-consumer relations are exact.
- The final matrix covers renderer/attribute output, both-port joypad serial
  input and debounce, and VRAM packet, scroll and PPU-control handoff.

The S8 audit repaired the packet interpreter so its `$00/$01` indirect pointer
advances after every ROM-format packet and the physical PPU control value is
published at the packet-header write point. The ROM/native repeat and vertical
routes, focused x86/x64 checks, platform-purity gate and DOS16 build pass.
The source repair refreshed all three target artifacts.

Historical migration accounting remains 1,992 / 1,992. The separate current
equivalence registry reaches 233 exact nodes and 471 exact feasible controls.
The detailed S evidence and source maps remain in the retained
[T55 proposal](../proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md).
