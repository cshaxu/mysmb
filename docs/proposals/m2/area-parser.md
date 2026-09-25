# M2 candidate: Area graphics and parser

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 1825-5314 except InitializeMemory: metatiles, attributes, palettes, headers, parser tasks/core, block buffer and scrolling setup.

## Existing-code disposition

Refactor src/game/area.c by source ownership; replace synthetic parser/spawn shortcuts. Actor behavior stays outside this slice.

## Graph contract

Feeds area state, collision block buffer, CIRAM, palette and parse schedule to gameplay.

## Admission S plan

1. **S1 after admission** - Inventory area tables, headers, parser-task branches, renderer branches and current C owners.
2. **S2 after admission** - Translate header/bootstrap and parser core with source-identical offsets and page semantics.
3. **S3 after admission** - Translate metatile, attribute, palette, name-table and block-buffer mutations.
4. **S4 after admission** - Translate column/scroll scheduling and compare area entry, columns, hidden-block and pipe routes.

## Acceptance

Area RAM, parser offsets, block buffer, CIRAM, attributes, palette and scroll state match reference. Parser does not invent actor initialization.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
