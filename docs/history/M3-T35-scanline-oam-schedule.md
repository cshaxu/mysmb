# M3 T35: Scanline OAM Composition Schedule

The owner authorizes a bounded performance experiment after T34 closes: use
additional shared PPU memory if it can reduce the actual composition cost
without changing source-visible rendering semantics.  This record is both the
admitted proposal and, after closure, the retained task history.

## S1 Admission

The candidate is a per-frame scanline OAM schedule.  At frame begin, the
shared PPU may append an OAM index to every visible scanline covered by that
eight-pixel sprite.  The maximum is 64 sprites times eight scanlines, or 512
one-byte entries.  A 241-entry unsigned-short offset table makes each output
row addressable; the bounded workspace cost is therefore 994 bytes before
ordinary structure alignment and remains below the owner's 10KiB allowance.

The schedule is not gameplay state and has one owner: the immutable
`mysmb_ppu_frame_view` used by the shared compositor.  It is built from the
same visible OAM snapshot that the current implementation reads.  Per-row
entries are appended while scanning OAM in descending index order, so every
row retains existing draw order, sprite-0 treatment, clipping, palette,
priority and background-opacity behavior.  Windows and DOS consume the same
shared result; neither platform gains rendering policy.

S1 may edit only `src/ppu/frame.c`, `src/ppu/frame.h`, focused PPU tests and
build registration needed for those tests.  Expected product change is
150--260 C lines and at most 1,024 bytes of view/workspace state.  It owns no
ROM label or control edge; expected matches and actual matches are empty.

Acceptance has two separate gates:

1. Exactness: compare all 61,440 pixels between the current reference model
   and every scheduled output, including arbitrary strip boundaries, masks,
   split scrolling, clipped sprites, flips, behind-background priority and
   OAM overlap/order.
2. Value: measure only shared PPU composition, excluding DOS VGA publication
   and pacing.  Retain the schedule only if it produces a reproducible,
   material reduction on dense-sprite workloads.  Otherwise remove it before
   closure.

If retained, S1 must run focused x86/x64 PPU regressions, the established
DOS16 build/link route and platform-purity review, then refresh all three
local target artifacts.  If rejected with no product source retained, it
closes with the measurement and no artifact refresh.  No ROM source,
third-party material, display mode, cache policy, frameskip or platform code
is in scope.
