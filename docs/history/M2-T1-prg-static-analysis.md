# M2 T1 PRG Static Analysis

## Outcome

T1 performs the requested complete owner-local PRG static analysis before
further native-C translation. Project-owned tools decode direct 2A03 control
flow, resolve the static dispatch idiom, reconstruct local listing layout, and
reconcile listing landmarks against direct-ROM instruction signatures.

The 32 KiB PRG ledger has zero unresolved bytes: 22,821 direct-CFG code bytes,
12 reconciled code bytes, 6,422 same-address structured data bytes, 3,358
relocated structured data bytes, 149 ROM-only revision data bytes, and six
vector bytes. The full architecture, address anchors, measured listing shift,
memory/hardware boundary, and M2 implementation consequences are recorded in
[the static architecture record](../etc/architecture/smb1-prg-analysis.md).

The local listing is a different revision after its source-side `$aeb8` point.
1,428 unique direct-ROM opcode anchors prove an unchanged early mapping and a
later ROM offset of `$24`; native translation must name actual ROM addresses.

## Evidence

- The local direct-ROM ledger reports NMI `$8082`, reset `$8000`, IRQ `$fff0`,
  18 static dispatch tables, 177 candidate dispatch targets, and no unresolved
  PRG bytes.
- The ROM SHA-256, reproducible local command shape, containment, and all
  coverage dispositions are in the architecture record; no ROM bytes,
  disassembly, listing text, trace, or generated data is tracked.
- ROM-free CTest passes 9 of 9 tests, including synthetic decoder, layout,
  reconciliation, and complete-ledger contracts. Documentation governance and
  `git diff --check` pass.

## Transfer

The next M2 candidate translates title selection/start using actual ROM
`$8231`, `$8245`, `$8255`, and `$aedc` route anchors and a deterministic native
checkpoint. Area, player, object, collision, and audio candidates follow the
architecture record's dependency order.
