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

## S1 closure — renderer and attribute-output chain

S1 is current-exact with **zero feasible differences**. The static source
comparison covers SMB1 lines 1825–1962 and the shared `src/game/area.c`
owner: the thirteen-row metatile loop, both parser-task tile sides, all four
attribute quadrants, the seventh-row exits, name-table wrap, the carry-aware
attribute address calculation, seven output commands, each attribute clear,
and the selector-six handoff. `AreaParserTaskHandler` retains the source
post-decrement dispatch: selectors 1, 2, 5 and 6 call the renderer, while the
final selector-zero completion calls the attribute writer and returns through
the common handler.

The bounded owner-local ROM/native matrix uses `t28-render-left`,
`t28-render-right`, `t28-attribute-left`, and `t28-attribute-right`. Original
ROM, x86 and x64 agree on all scoped `VRAM_Buffer2` command bytes,
`AttributeBuffer` bytes, `CurrentNTAddr`, and `VRAM_Buffer_AddrCtrl`; x86 and
x64 snapshots are byte-identical. The focused `area_output_smoke` executable
also passes on both widths. No shared product source changed, so this audit
does not refresh the three committed product artifacts. The current registry
advances from 166 to **177 exact nodes** and from 347 to **370 exact feasible
control edges**; historical credit remains 1,992 / 1,992.

## S2 admission — palette-rotation chain

S2 receives the contiguous seven-label chain `ColorRotatePalette`,
`BlankPalette`, `Palette3Data`, `ColorRotation`, `GetBlankPal`, `GetAreaPal`
and `ExitColorRot` at SMB1 lines 1970–2024. The audit compares the
frame-counter eighth-frame gate, buffer-capacity gate, eight-byte blank copy,
area-type palette selection, rotating colour insertion, offset wrap and every
return path. The controlled owner-local ROM/native route will exercise each
gate, all four area types and rotation offsets 0–6. A feasible difference
stays in S2 for shared `area.c` repair and re-audit before S3 is admitted.

## S2 closure — palette-rotation chain

S2 is current-exact with **zero feasible differences**. SMB1 lines 1970–2024
match the shared `area.c` implementation and its `engine.c` caller: both
early-return gates, the complete blank command, all four area palette rows,
the cycle-byte overwrite, Buffer1 offset increment, six-step wrap and return
to `ProcELoop`. The four controlled ROM/x86/x64 fixtures cover normal output,
offset five wrap, a non-eighth frame and a full buffer; their scoped output
bytes and state are exact, and x86/x64 agree. No product source changed.

## S3 admission — block-metatile chain

S3 receives `BlockGfxData`, `RemoveCoin_Axe`, `WriteBlankMT`,
`ReplaceBlockMetatile`, `DestroyBlockMetatile`, `WriteBlockMetatile`,
`UseBOffset`, `MoveVOffset`, `PutBlockMetatile`, `SaveHAdder` and `RemBridge`
at SMB1 lines 2034–2118. It will compare the metatile selector ladder,
water-specific blank, VRAM packet address arithmetic, residual counter/flag
writes, vertical carry and bridge completion through controlled original-ROM
and native routes. A feasible difference remains in S3 for shared game-layer
repair and re-audit before S4 is admitted.

## S3 closure ? block-metatile chain

S3 is current-exact after one shared-C repair. `mysmb_area_write_block_metatile`
had an invented high-Buffer1 rejection that does not exist in SMB1 lines
2061?2117. Removing it restores the source `INY` `$ff`-to-`$00` wrap; after
`RemBridge`, `MoveVOffset` stores `$09`. The direct focused test covers this
wrap and the controlled original-ROM/x86/x64 remove-water, write-block, bridge
and destroy matrix agrees on every scoped VRAM command byte, source-visible
zero-page field and address-control result. All eleven nodes, 31 incident
feasible controls and three material handoffs are current-exact. Focused x86
and x64 tests pass, the OpenNT DOS16 link succeeds and platform-purity passes.
The refreshed artifacts are SHA-256 `45DBEA08EBAC6103DAD2D60B83F31B9A2B27E0D0FB3FFF23C1786BAACB7DC765`
(DOS16), `682E088D8421F3339CAA7E06DDD3A8FBF4064ED060DDF1C30588660FA30DE30F`
(Win32) and `EC30CA5F81616BB4BC996FD70A059F4435D44FECBE6FAD536FAD90214E8A527F`
(Win64).

## S4 admission ? metatile graphics and palette-table chain

S4 receives `MetatileGraphics_Low`, `MetatileGraphics_High`, `Palette0_MTiles`,
`Palette1_MTiles`, `Palette2_MTiles`, `Palette3_MTiles`, `WaterPaletteData`,
`GroundPaletteData`, `UndergroundPaletteData`, `CastlePaletteData`,
`DaySnowPaletteData`, `NightSnowPaletteData`, `MushroomPaletteData` and
`BowserPaletteData` at SMB1 lines 2145?2326. The entry is the low pointer table
and the exit is the Bowser palette stream. All tables share the portable
`area.c` table-consumer owner; the ROM route proves bound PRG byte identity and
selector-driven command output before any credit is recorded.

## S4 closure ? metatile graphics and palette-table chain

S4 is current-exact with no shared-C repair. The local generated PRG exactly
matches the original ROM's 32 KiB PRG region (`5374abb64cfb9b5d961856c60166cedc55859164cf2b8867730e144fa2bdd594`). Static audit maps the pointer tables, metatile rows and NMI table selectors to shared `area.c` and `frame_root.c`; x86/x64 `area_data_smoke` verifies all four metatile rows and all eight palette streams. The 14 nodes and eight previously unproven material handoffs are exact. No product code changed, so artifacts are not refreshed.

## S5 admission and closure ? message-stream chain

S5 receives the contiguous seven streams `MarioThanksMessage` through
`WorldSelectMessage2` at SMB1 lines 2331?2387. Static comparison maps each to
VRAM address controls 12?18 and the shared NMI/area consumers. The local PRG
is byte-identical to the original ROM and `area_data_smoke` passes all streams
on x86 and x64. All seven nodes and their seven NMI material handoffs are
current-exact; no product source changed, so artifacts remain unchanged.

## S6 admission ? JumpEngine and name-table initialization chain

S6 receives `JumpEngine`, `InitializeNameTables`, `WriteNTAddr`, `InitNTLoop`
and `InitATLoop` at SMB1 lines 2395?2441. It owns every feasible incident
vector/caller-return relation for `JumpEngine`, plus the shared boot clear and
PPU-control sequence. It will not accept visually similar dispatch: each vector
target and continuation must map to a source-owned shared C call relation.

## S6 P1 ? restore name-table PPU write order

The initial static audit found a feasible shared-C difference before node
credit: `InitializeNameTables` in the ROM calls `WriteNTAddr` with `$24`, then
`$20`, so it clears name table 1 before name table 0.  The C loop had written
the same final bytes in the reverse order.  `boot.c` now executes table 1 then
table 0 while retaining the 768 `$24` writes, 64 zero attribute writes, buffer
reset and scroll/control sequence.  This is a shared-game repair; no platform
source decides the order.

Focused x86 and x64 `name-table-init-smoke` and
`game-entry-dispatch-smoke` pass.  The packaged x86/x64 self-tests return zero;
the OpenNT DOS16 MZ link succeeds (with its pre-existing `OLDNAMES.LIB`
warning), and the platform-purity gate passes.  The three required artifacts
were refreshed: `mysmb16.exe` SHA-256
`c3a03911ef011cb91f198717df645547fc959626a1b1929f005ff2ab968b635b`,
`mysmb32.exe` SHA-256
`dde28ebb0b5c813e358e712bb1a209534e6ef77c1b3f878ae55fadfaebc7401c`, and
`mysmb64.exe` SHA-256
`5acd0cdd379846a0e9ce46a880d7ba5e79f1481833491d9b45b24e9dac5f0e7d`.
S6 remains open for its required full incident-control and ROM/native route
audit; this P does not grant current-exact node credit.

## S6 P2 ? direct dispatcher and boot static evidence

The local, ignored S6 audit report now checks the actual source rather than
historical annotations.  It confirms the ROM `JumpEngine` shift, stack-return
replacement and indirect target jump; the `$2400` then `$2000` name-table
order; the native 768-tile/64-attribute loops and buffer/scroll resets; and
the shared-C operating-mode and game-mode vector owners.  The x86 and x64
name-table smoke executables both pass against this source.  This is evidence
only: the remaining incident vector/return relations and controlled ROM route
must still pass before S6 can close.  No product source changed, so this P
does not refresh artifacts.

## S6 P3 ? ROM-bound cold-start route

The ROM-bound `local-title-bootstrap-smoke` now passes on both current x86 and
x64 builds.  That route begins with the shared power-on/reset sequence,
executes `InitializeNameTables`, then reaches the title-mode dispatcher with
the owner-local PRG and title data bound.  It complements the isolated
name-table check by proving the boot caller and title continuation on the
actual local-ROM build path.  It does not observe every S6 vector family, so
the remaining incident-edge audit stays open.  No product source changed and
no artifacts are refreshed.

## S6 P4 ? incident vector-family map

The S6 local static audit now covers every incident `JumpEngine` caller family:
operating/title/victory/game-over modes; area-parser and area-object routes;
game routines and player movement; block code; enemy initialization, frenzy,
core, movement and platform routes; and the star-flag route.  Each ROM label
has a named shared-C dispatcher owner, and x86/x64
`game-entry-dispatch-smoke` confirms the four-entry `GameMode` selector.  This
eliminates an unmapped-owner finding, but the audit still must compare each
family's selector domain and return continuation before closing S6.  No
product source changed and no artifacts are refreshed.
