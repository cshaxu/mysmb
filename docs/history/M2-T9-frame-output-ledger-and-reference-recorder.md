# M2 T9: Frame Output Ledger And Reference Recorder

## Result

T9 replaced the unsupported marker-renderer evidence with an explicit output
ownership ledger, a portable native frame-snapshot contract, and a bounded
owner-local reference recorder. It does not establish visual equivalence or
close M2.

## Audit Findings

The audit found that `game/render.c` copies one name table and emits player and
enemy identity rectangles; `platform/win32/main_win32.c` turns those values
into host colors and rectangles. The following production exclusions were
also found and remain T10/T11 work: OAM omissions in `area.c` and `objects.c`,
partial title-only PPU output in `game.c`, and no gameplay palette, scroll, or
attribute submission. Those diagnostic paths remain available but are barred
from M2 gameplay proof.

The ledger records output-owning ROM ranges for NMI, PPU command buffers,
area/background updates, palettes, player graphics, enemy graphics, blocks,
items, projectiles, effects, and the shared sprite-row writer. Direct
reconciliation corrected the planned reference sampling location from `$81f9`
(a SpriteShuffler helper return) to the NMI `RTI` at `$8181`.

## Delivered Contract

`game/frame_snapshot.h` records CPU RAM, name tables, palette, OAM, PPU state,
and bounded audio state. `captured_fields` and `verified_fields` are separate:
current native code can record its available RAM/name-table/OAM/audio data, but
cannot claim a complete frame until every visible field is both populated and
owner-local-reference verified.

The project-owned recorder source builds only in an isolated local `nnes`
reference build. It samples at `$8181`, limits a run to 600 frames and
2,637,012 bytes, and enforces a 512-run no-progress budget per requested
frame. It accepts either one constant controller byte or an optional bounded
`frame:buttons` transition script, which permits a press/release script while
retaining one isolated trace run. A two-frame no-input run produced the
specified 8,802-byte raw record; that raw trace was then deleted. The product
has no `nnes` link dependency.

## Verification

- ROM-free CMake build and test suite: 28/28 passed.
- Owner-local ROM CMake build and test suite: 30/30 passed.
- Win32 x86 owner-local ROM build and test suite: 30/30 passed.
- Configured OpenNT large-model core compile passed, including the snapshot
  unit.
- Isolated reference-recorder build passed; bounded two-frame record size
  matched the contract.
- Documentation governance and `git diff --check` passed.

## Deferred Work

T10 owns translated background, palette, scroll, attribute, status, and VRAM
buffer output. T11 owns every OAM graphics family. T13 performs the first
frame-indexed native/reference comparison; only it may populate verification
evidence for the new snapshot fields.
