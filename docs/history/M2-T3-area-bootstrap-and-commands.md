# M2 T3 Area Bootstrap And Commands

## Outcome

T3 translates the first native area route after title start. It covers the
task-0 initialization state, actual NROM area-pointer tables, two-byte area
header, stream selection/page control, DecodeAreaData dispatch classification,
and a bounded neutral command queue. The Win32 owner-local composition binds
locally generated PRG only; the portable layer never includes generated data.

## Evidence

- Synthetic tests cover table bounds, header bit fields, page controls, stream
  end, and dispatch classification.
- The owner-local first-area smoke verifies the runtime chain from Start to
  gameplay task 1, area pointer `25`, type 1, header fields 2/1/2, and the
  first queued object command. It records neutral values only.
- ROM-free CTest passes 9 of 9. Owner-local area smoke passes. Win32 x64/x86
  and the OpenNT large-model compilation of both game units pass. Governance
  and diff checks pass.

## Audit And Transfer

The review corrected the physical table layout after the area-offset table:
the four type offsets begin after all 36 world-area entries, rather than at
the area table start. Synthetic and owner-local tests cover the corrected
layout. T4 owns player input, motion, collision, scrolling, and their fixed
input checkpoints; T3's neutral area commands are its terrain/object source.
