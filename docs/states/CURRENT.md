# Project Status

## Current Work

## M2 T55 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T55 S4 ? Cohort C metatile graphics and palette-table current-equivalence audit. |
| Admission And Approval | T55 S3 closed with zero scoped feasible differences after its repair; owner-directed source-order continuation. |
| Objective | Audit `MetatileGraphics_Low` through `BowserPaletteData`, repair every feasible shared-C difference, and repeat the scoped ROM/native and graph audit to zero. |
| Non-goals | No historical-node credit, no message-stream audit, and no platform-owned game decision. |
| Reference Baseline | Historical 1,992 / 1,992. Current registry: 195 exact, 1,797 needs-evidence nodes; 411 exact, 3,913 needs-evidence feasible controls. Scope: 14 labels; expected historical delta 0. |
| Candidate Proposal | docs/proposals/m2/t55-cohort-c-bootstrap-ppu-proof.md. |
| Files And ABI Surface | Shared `src/game/area.c`, focused recorder/tests and current-equivalence registry only; platforms remain presentation/input adapters. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, documentation and source policy. |
| Verification | ROM-logic: PRG byte identity, static table/consumer audit and controlled original-ROM/x86/x64 table selector routes. Operational: focused x86/x64 checks, DOS16 link if source changes and platform-purity audit. |
| Expected Markers | All 14 labels and incident feasible material handoffs have a shared-C table-binding/selector/output counterpart with no scoped difference. |
| Asset Needs | Owner-local ROM only for ignored evidence below build/m2-t55-s4; refresh artifacts only if product code changes. |
| Reporting Requirements | Report each exact scoped label, every material disposition, current-registry before/after and separate operational outcome. |
| Stop Conditions | A feasible ROM/C difference remains after repair, a table handoff lacks a shared-C counterpart, a trace exceeds its budget, or platform code makes a gameplay decision. |
| Exit Criteria | The S closes only when every scoped node and incident feasible material handoff is exact under static and controlled ROM/native evidence. |
| Original Owner Request | Faithful shared original-ROM C logic for DOS16 and Win32, with auditable node and graph equivalence. |
| Similar-Issue Sweep | All PRG table offset consumers, ordinary/special palette selectors, PPU command packet application and NMI pointer handoffs. |

## Current Technical Baseline

M2 T55 S4 is active after the closed S3 block-metatile audit. It continues Cohort C with the contiguous metatile-graphics and palette-table chain.

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
