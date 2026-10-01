# M2 T55: Cohort C bootstrap, VRAM and PPU current-equivalence proof

M2 T55 is the source-order first half of Cohort C. It audits the 67 labels from `RenderAreaGraphics` through `WritePPUReg1` after T54 S7 closed. It does not change historical ROM-match accounting. Every S remains an audit until its controlled original-ROM/x86/x64 route and graph relations have been proven; a feasible mismatch stays in that S for repair and re-audit before its successor is admitted.

## Task scope and delivery

| Planned S | Source entry to exit | Labels | Shared owner | ROM route family |
| --- | --- | ---: | --- | --- |
| S1 | `RenderAreaGraphics through SetVRAMCtrl` | 11 | `src/game/area.c` | Controlled area-parser renderer entry: metatile row direction, attribute boundary and control-six output. |
| S2 | `ColorRotatePalette through ExitColorRot` | 7 | `src/game/area.c` | Controlled rotation counter and blank/area palette routes. |
| S3 | `BlockGfxData through RemBridge` | 11 | `src/game/area/block_metatile.c` | Controlled block replacement, destroy, blank and bridge metatile routes. |
| S4 | `MetatileGraphics_Low through BowserPaletteData` | 14 | `src/game/area.c` | Bound data-table consumer routes for graphics and ordinary/special palette selectors. |
| S5 | `MarioThanksMessage through WorldSelectMessage2` | 7 | `src/game/area.c` | Controlled message-stream selector routes that consume the contiguous text data. |
| S6 | `JumpEngine through InitATLoop` | 5 | `src/game/dispatcher.c plus src/game/boot.c` | Controlled vector and name-table-clear route, including inline table return behavior. |
| S7 | `ReadJoypads through Save8Bits` | 4 | `src/game/frame_root.c` | Controlled both-port serial input, Select/Start suppression and saved-byte routes. |
| S8 | `WriteBufferToScreen through WritePPUReg1` | 8 | `src/game/frame_root.c plus src/game/boot.c` | Controlled empty/repeat/multi-write VRAM packet and scroll/register handoff routes. |

## Exact source-order labels

| ROM line | Label | Planned S | Current owner | Incoming state |
| ---: | --- | --- | --- | --- |
| 1825 | `RenderAreaGraphics` | S1 | `src/game/area.c` | needs-evidence |
| 1840 | `DrawMTLoop` | S1 | `src/game/area.c` | needs-evidence |
| 1878 | `RightCheck` | S1 | `src/game/area.c` | needs-evidence |
| 1886 | `LLeft` | S1 | `src/game/area.c` | needs-evidence |
| 1888 | `NextMTRow` | S1 | `src/game/area.c` | needs-evidence |
| 1889 | `SetAttrib` | S1 | `src/game/area.c` | needs-evidence |
| 1914 | `ExitDrawM` | S1 | `src/game/area.c` | needs-evidence |
| 1920 | `RenderAttributeTables` | S1 | `src/game/area.c` | needs-evidence |
| 1930 | `SetATHigh` | S1 | `src/game/area.c` | needs-evidence |
| 1940 | `AttribLoop` | S1 | `src/game/area.c` | needs-evidence |
| 1962 | `SetVRAMCtrl` | S1 | `src/game/area.c` | needs-evidence |
| 1970 | `ColorRotatePalette` | S2 | `src/game/area.c` | needs-evidence |
| 1973 | `BlankPalette` | S2 | `src/game/area.c` | needs-evidence |
| 1977 | `Palette3Data` | S2 | `src/game/area.c` | needs-evidence |
| 1983 | `ColorRotation` | S2 | `src/game/area.c` | needs-evidence |
| 1991 | `GetBlankPal` | S2 | `src/game/area.c` | needs-evidence |
| 2004 | `GetAreaPal` | S2 | `src/game/area.c` | needs-evidence |
| 2024 | `ExitColorRot` | S2 | `src/game/area.c` | needs-evidence |
| 2034 | `BlockGfxData` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2041 | `RemoveCoin_Axe` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2047 | `WriteBlankMT` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2052 | `ReplaceBlockMetatile` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2058 | `DestroyBlockMetatile` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2061 | `WriteBlockMetatile` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2076 | `UseBOffset` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2080 | `MoveVOffset` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2086 | `PutBlockMetatile` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2097 | `SaveHAdder` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2118 | `RemBridge` | S3 | `src/game/area/block_metatile.c` | needs-evidence |
| 2145 | `MetatileGraphics_Low` | S4 | `src/game/area.c` | needs-evidence |
| 2148 | `MetatileGraphics_High` | S4 | `src/game/area.c` | needs-evidence |
| 2151 | `Palette0_MTiles` | S4 | `src/game/area.c` | needs-evidence |
| 2192 | `Palette1_MTiles` | S4 | `src/game/area.c` | needs-evidence |
| 2240 | `Palette2_MTiles` | S4 | `src/game/area.c` | needs-evidence |
| 2252 | `Palette3_MTiles` | S4 | `src/game/area.c` | needs-evidence |
| 2263 | `WaterPaletteData` | S4 | `src/game/area.c` | needs-evidence |
| 2275 | `GroundPaletteData` | S4 | `src/game/area.c` | needs-evidence |
| 2287 | `UndergroundPaletteData` | S4 | `src/game/area.c` | needs-evidence |
| 2299 | `CastlePaletteData` | S4 | `src/game/area.c` | needs-evidence |
| 2311 | `DaySnowPaletteData` | S4 | `src/game/area.c` | needs-evidence |
| 2316 | `NightSnowPaletteData` | S4 | `src/game/area.c` | needs-evidence |
| 2321 | `MushroomPaletteData` | S4 | `src/game/area.c` | needs-evidence |
| 2326 | `BowserPaletteData` | S4 | `src/game/area.c` | needs-evidence |
| 2331 | `MarioThanksMessage` | S5 | `src/game/area.c` | needs-evidence |
| 2339 | `LuigiThanksMessage` | S5 | `src/game/area.c` | needs-evidence |
| 2347 | `MushroomRetainerSaved` | S5 | `src/game/area.c` | needs-evidence |
| 2358 | `PrincessSaved1` | S5 | `src/game/area.c` | needs-evidence |
| 2366 | `PrincessSaved2` | S5 | `src/game/area.c` | needs-evidence |
| 2375 | `WorldSelectMessage1` | S5 | `src/game/area.c` | needs-evidence |
| 2382 | `WorldSelectMessage2` | S5 | `src/game/area.c` | needs-evidence |
| 2395 | `JumpEngine` | S6 | `src/game/dispatcher.c` | needs-evidence |
| 2412 | `InitializeNameTables` | S6 | `src/game/boot.c` | needs-evidence |
| 2421 | `WriteNTAddr` | S6 | `src/game/boot.c` | needs-evidence |
| 2427 | `InitNTLoop` | S6 | `src/game/boot.c` | needs-evidence |
| 2436 | `InitATLoop` | S6 | `src/game/boot.c` | needs-evidence |
| 2446 | `ReadJoypads` | S7 | `src/game/frame_root.c` | needs-evidence |
| 2454 | `ReadPortBits` | S7 | `src/game/frame_root.c` | needs-evidence |
| 2455 | `PortLoop` | S7 | `src/game/frame_root.c` | needs-evidence |
| 2474 | `Save8Bits` | S7 | `src/game/frame_root.c` | needs-evidence |
| 2482 | `WriteBufferToScreen` | S8 | `src/game/frame_root.c` | needs-evidence |
| 2495 | `SetupWrites` | S8 | `src/game/frame_root.c` | needs-evidence |
| 2501 | `GetLength` | S8 | `src/game/frame_root.c` | needs-evidence |
| 2504 | `OutputToVRAM` | S8 | `src/game/frame_root.c` | needs-evidence |
| 2506 | `RepeatByte` | S8 | `src/game/frame_root.c` | needs-evidence |
| 2523 | `UpdateScreen` | S8 | `src/game/frame_root.c` | needs-evidence |
| 2527 | `InitScroll` | S8 | `src/game/boot.c` | needs-evidence |
| 2533 | `WritePPUReg1` | S8 | `src/game/boot.c` | needs-evidence |

## S1 admission — renderer and attribute-output chain

S1 owns the contiguous eleven-label `RenderAreaGraphics → SetVRAMCtrl` chain. Its predecessor is the closed T54 screen-task output boundary; its successor is S2 palette rotation. The ROM-logic track compares metatile draw direction, row/column arithmetic, attribute-table selection, loop exits and the control-six handoff. The operational track uses one bounded original-ROM/current x86/x64 renderer fixture, focused area-render checks, shared-source DOS16 link and platform-purity audit. Since every scoped label is historically complete, S1 expects zero historical-credit delta; it must still record each current-equivalence disposition and every incident feasible control/material edge.

## T55 closure standard

T55 closes only after all eight S chains have current dispositions for their 67 labels, every owned feasible control/material relation has a shared-C counterpart and evidence, all scoped mismatches have been repaired and re-audited to zero, and a cross-chain ROM/native matrix covers renderer, input, VRAM and scroll handoffs. A source build or visible frame alone is insufficient.
