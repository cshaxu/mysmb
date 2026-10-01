# Project Status

## Current Work

## M2 T55 S8 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T55 S8 — VRAM packet and PPU handoff current-equivalence audit. |
| Admission And Approval | T55 S7 closed with zero scoped feasible differences; owner authorization permits source-order S8 admission. |
| Objective | Closed: audited `WriteBufferToScreen` through `WritePPUReg1`, repair every feasible shared-C mismatch, and repeat scoped ROM/native evidence until each node and incident feasible control is exact. |
| Non-goals | No platform rendering/input decisions, no historical-node credit, and no successor admission before this chain closes with zero feasible differences. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 225 exact and 1,767 needs-evidence nodes; 458 exact feasible controls. Scope: eight labels and 13 pending incident feasible controls; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md. |
| Files And ABI Surface | Shared `src/game/frame_root.c` and `src/game/boot.c`; focused packet/recorder tests only. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: source packet header branches, payload/read pointer, terminator and scroll/control call-return relations. Operational: controlled original-ROM/x86/x64 packet matrix, focused x86/x64 tests, DOS16 build if product source changes, and platform-purity audit. |
| Expected Markers | Empty, sequential, vertical and repeat packets preserve physical `$2000`, `$2005`, VRAM outputs, mirror state, zero-page pointer progression and terminal transfer in shared C. |
| Asset Needs | Refresh all three artifacts only if product source changes. |
| Reporting Requirements | Report all eight labels and each scoped feasible control with separate static ROM-logic and operational results; report repair/re-audit loop before closure. |
| Stop Conditions | A feasible ROM/C difference remains after repair, an incident control lacks a shared-C counterpart, or platform code makes a gameplay decision. |
| Exit Criteria | Every scoped node and incident feasible control is exact under static and controlled evidence; any discovered mismatch is repaired and re-audited in S8. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | Header d7/d6 decoding, increment/repeat modes, source-pointer carry, terminator routing, physical/mirror `$2000`, and scroll-register write order. |

## S8 Closure

S8 closes with eight current-exact nodes and 13 current-exact feasible control relations. The shared packet interpreter now retains the ROM `$00/$01` indirect-pointer advance through every packet and publishes each packet header's physical `$2000` state. Input-identical original-ROM/native repeat and vertical routes cover both header branch families; direct chained carry, NMI-parent, x86/x64, platform-purity and DOS16 checks pass. Historical status remains 1,992 / 1,992, while the fresh registry is **233 exact nodes** and **471 exact feasible controls**.

## Current Technical Baseline

M2 T55 S7 is active after the closed S6 dispatcher audit. It continues Cohort C with the contiguous two-port joypad serial-read chain.

## S5 Closure

`MarioThanksMessage`, `LuigiThanksMessage`, `MushroomRetainerSaved`,
`PrincessSaved1`, `PrincessSaved2`, `WorldSelectMessage1` and
`WorldSelectMessage2` are current-exact. The local PRG remains byte-identical
to the original ROM, and x86/x64 command-route tests consume all seven streams
through controls 12?18. The NMI address-table and shared `area.c` message
consumer preserve each selector and packet stream. No product source changed.
The registry advances from 209 to **216 exact nodes**; control-edge count
remains **411 exact feasible controls**. Historical conformance remains 1,992
/ 1,992.

## S4 Closure

`MetatileGraphics_Low`, `MetatileGraphics_High`, `Palette0_MTiles`,
`Palette1_MTiles`, `Palette2_MTiles`, `Palette3_MTiles`, `WaterPaletteData`,
`GroundPaletteData`, `UndergroundPaletteData`, `CastlePaletteData`,
`DaySnowPaletteData`, `NightSnowPaletteData`, `MushroomPaletteData` and
`BowserPaletteData` are current-exact. The generated local PRG matches the
original ROM's complete 32 KiB PRG region byte-for-byte, while the x86/x64 area
data smoke test covers every four-tile metatile row and all eight palette
selectors. The static audit confirms that `area.c` and `frame_root.c` consume
those tables through the source pointer and NMI selector routes. No shared
product source changed. The registry advances from 195 to **209 exact nodes**;
control-edge count remains **411 exact feasible controls**. Historical
conformance remains 1,992 / 1,992.

## S3 Closure

`BlockGfxData`, `RemoveCoin_Axe`, `WriteBlankMT`, `ReplaceBlockMetatile`,
`DestroyBlockMetatile`, `WriteBlockMetatile`, `UseBOffset`, `MoveVOffset`,
`PutBlockMetatile`, `SaveHAdder` and `RemBridge` are current-exact. The audit
found one feasible shared-C difference: `WriteBlockMetatile` rejected Buffer1
offsets above `$f5`, while the ROM accepts `$ff`, lets `INY` wrap to zero and
later stores final offset `$09`. The invented rejection was removed. Controlled
original-ROM/x86/x64 remove-water, write-block, bridge and destroy routes agree
on each scoped command/state field; x86/x64 snapshots are byte-identical. The
focused x86/x64 wrap test passes, the OpenNT DOS16 link succeeds, platform
purity passes, and the three artifacts were refreshed. The registry advances
from 184 to **195 exact nodes** and from 380 to **411 exact feasible controls**;
historical conformance remains 1,992 / 1,992.

## S2 Closure

`ColorRotatePalette`, `BlankPalette`, `Palette3Data`, `ColorRotation`,
`GetBlankPal`, `GetAreaPal` and `ExitColorRot` are current-exact. The
controlled original-ROM/x86/x64 normal, wrap, frame-gate and buffer-full
matrix has zero scoped byte differences. The shared caller remains
`engine.c`, while the entire decision and write sequence remains in `area.c`.
Focused x86/x64 palette tests and platform-purity checks pass. No product code
changed, so artifacts remain the S7 release. The registry advances to 184
exact nodes and 380 exact feasible controls; historical conformance remains
1,992 / 1,992.

## S1 Closure

`RenderAreaGraphics`, `DrawMTLoop`, `RightCheck`, `LLeft`, `NextMTRow`,
`SetAttrib`, `ExitDrawM`, `RenderAttributeTables`, `SetATHigh`, `AttribLoop`
and `SetVRAMCtrl` are current-exact. The controlled original-ROM/x86/x64
left/right renderer and attribute matrix has zero scoped byte differences.
The four parser renderer selectors, final attribute call and return were
checked against the source dispatch and shared `area.c` owner. Focused x86/x64
area-output tests pass. No product code changed; product artifacts remain the
previous S7 release. The registry advances to 177 exact nodes and 370 exact
feasible controls; historical conformance remains 1,992 / 1,992.

## S5 Closure

`ResetSpritesAndScreenTimer`, `ResetScreenTimer` and `NoReset` are current-exact.
The source audit against SMB1 lines 1804–1813 found no shared-C difference:
task cases five and seven both preserve the nonzero early return and the
zero-timer `MoveAllSpritesOffscreen`, timer-seven reload, task-increment order.
The controlled task-five/task-seven zero/nonzero matrix agrees across original
ROM, x86 and x64 for `ScreenRoutineTask`, `ScreenTimer` and every OAM byte.
The focused screen-status smoke and platform-purity audit pass. The registry
advances from 159 to 162 exact nodes and from 319 to 324 exact feasible
controls; historical conformance remains 1,992 / 1,992. The only code change
is a focused test assertion, so product artifacts were not refreshed.

## S6 Closure

`AreaParserTaskControl`, `TaskLoop` and `OutputCol` are current-exact. The
normal Start route executes 12 parser column sets in ROM, x86 and x64: task 8
remains active through the non-final sets, each selects control 6, and the
final decrement underflows to 255 before advancing to task 9. The five
tracked state bytes agree for samples 6–18. The registry advances from 162 to
165 exact nodes and from 324 to 330 exact feasible controls; historical
conformance remains 1,992 / 1,992. No product code changed.

## S7 Closure

`ScreenRoutines` and its 17 source-owned task-vector relations are
current-exact. The repeat static audit corrects its ROM entry to `$8567` and
removes the former synthetic out-of-domain `OperMode_Task=2` recovery write.
The controlled selector 0–14 original-ROM/x86/x64 matrix is exact, including
`ColumnSets` and `AreaParserTaskNum` for task eight. Focused x86/x64 smoke and
platform-purity checks pass; the shared OpenNT DOS16 build links. Three product
artifacts were refreshed. The registry advances to 166 exact nodes and 347
exact feasible controls; historical conformance remains 1,992 / 1,992.
No successor S is admitted.

One shared native C90 game implementation serves DOS16 and Win32 x86/x64;
platform adapters do not own game logic.

## S7 Closure

S7 closes with four current-exact nodes and eight current-exact feasible control relations. The repair keeps the packet-selected physical `$2000` state visible during the NMI before the existing tail restores its saved d7-enabled value. The original-ROM/x86/x64 controlled route is zero-difference for joypad RAM and PPU scalars; the full per-port debounce sweep, NMI-parent test, platform purity and DOS16 link pass. Historical status remains 1,992 / 1,992, while the fresh current registry is **225 exact nodes** and **458 exact feasible controls**.
