# Embedded C Resource Source Candidate

## Owner direction

The owner directs a future MySMB task to replace the owner-local ROM build
input with checked-in C source containing the complete Super Mario Bros. ROM
resource image expressed as hexadecimal arrays. This is a deliberate exception
to the current local-only resource policy: the owner has requested that the
translated product no longer load or generate from `smario1.nes`/`smb1.nes`.

The queue entry is a candidate only. It receives its numeric M/T/S identity
when admitted after the active T39 work; it does not alter current DOS16
performance work.

## Intended outcome

One reviewed C resource package becomes the only resource dependency for all
three products. It contains, in source-readable `0xNN` arrays and named slices:

- PRG code/data image, including game tables, area streams and pointers;
- CHR pattern image, with named tile, sprite and background ranges;
- title/menu data and icons;
- music tracks, sound-effect streams, envelopes and lookup tables; and
- compile-time size, offset, CRC and layout assertions.

The generated C must preserve the original byte order and mapper-visible PRG
and CHR layout exactly. Game, PPU, audio and presentation code continue to
consume their existing neutral resource interfaces; this task must not create a
separate DOS, Win32 or text interpretation of any resource.

## Planned execution shape

1. Admit a source-policy exception and update the policy to state its exact
   owner authorization, scope and redistribution decision.
2. Create a deterministic local converter below `build/` that reads the
   owner-supplied ROM once and emits reviewed C header/source input arranged by
   named resource section. The converter and its receipts remain local.
3. Check in only the approved C resource source and neutral resource manifest;
   remove the normal build dependency on an external ROM path.
4. Rewire x86, x64 and DOS16 to link the same resource package. Runtime and
   build invocation must succeed when the original ROM file is absent.
5. Compare every embedded byte/range, PRG/CHR boundary, offset, size and CRC
   with the local source ROM before accepting generated input. Then run the
   existing ROM-equivalence, audio, PPU, title, area and product launch suites.

## Acceptance conditions

- A clean x86, x64 and DOS16 build requires no ROM path and performs no ROM
  file read.
- Exact byte/offset/length/CRC receipts cover the entire PRG and CHR payload;
  named sprite, tile, area, title and audio sections collectively cover the
  same bytes with no gaps or overlaps.
- The three products use one common resource owner and preserve current
  behavior on title, gameplay, text, graphics, audio, save/load and DOS16
  routes.
- The policy exception, provenance, generated-source review and distribution
  decision are explicit before any ROM-derived C source is committed.
- No original `.nes` file, disassembly, third-party source or build trace is
  committed as part of the task.

## Risks and boundaries

The resulting C source will be large and contains ROM-derived expression. The
owner must retain responsibility for its distribution status. The task must not
claim that hexadecimal spelling makes the bytes independently authored. It also
must not replace current logic with a resource interpreter, duplicate data per
platform, or introduce a runtime ROM loader as a fallback.
