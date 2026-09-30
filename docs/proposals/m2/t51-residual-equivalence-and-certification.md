# M2 T51: residual source-order equivalence and cross-route certification

## Task contract

T51 corrects the final-row assumption in the source-order recovery plan. The
former zero-node certification row cannot close M2 while 40 exact inventory
nodes remain incomplete. T51 therefore owns those residual nodes in original
source order, followed by a zero-credit integration certification S. The shared
C game layer remains the only business-logic owner; DOS16 and Win32/x86/x64
consume the same result through their platform adapters.

The task begins at **1,952 / 1,992** and can reach **1,992 / 1,992**. Its
exact target is `NonMaskableInterrupt`, `ScreenRoutines`,
`AreaParserTaskControl`, `TaskLoop`, `OutputCol`, `KillEnemies`,
`E_CastleArea1` through `E_CastleArea6`, `E_GroundArea1` through
`E_GroundArea22`, `E_UndergroundArea1` through `E_UndergroundArea3`, and
`E_WaterArea1` through `E_WaterArea3`. The ranges are inclusive; they name every source label in each numbered family.

## Exact residual-node allocation

| S | ROM line | Exact label |
| --- | ---: | --- |
| S1 | 764 | `NonMaskableInterrupt` |
| S2 | 1386 | `ScreenRoutines` |
| S2 | 1595 | `AreaParserTaskControl` |
| S2 | 1597 | `TaskLoop` |
| S2 | 1603 | `OutputCol` |
| S3 | 3615 | `KillEnemies` |
| S4 | 4550 | `E_CastleArea1` |
| S4 | 4558 | `E_CastleArea2` |
| S4 | 4565 | `E_CastleArea3` |
| S4 | 4574 | `E_CastleArea4` |
| S4 | 4583 | `E_CastleArea5` |
| S4 | 4589 | `E_CastleArea6` |
| S4 | 4598 | `E_GroundArea1` |
| S4 | 4606 | `E_GroundArea2` |
| S4 | 4613 | `E_GroundArea3` |
| S4 | 4619 | `E_GroundArea4` |
| S4 | 4627 | `E_GroundArea5` |
| S4 | 4636 | `E_GroundArea6` |
| S4 | 4643 | `E_GroundArea7` |
| S4 | 4650 | `E_GroundArea8` |
| S4 | 4656 | `E_GroundArea9` |
| S4 | 4662 | `E_GroundArea10` |
| S4 | 4666 | `E_GroundArea11` |
| S4 | 4674 | `E_GroundArea12` |
| S4 | 4679 | `E_GroundArea13` |
| S4 | 4687 | `E_GroundArea14` |
| S4 | 4695 | `E_GroundArea15` |
| S4 | 4700 | `E_GroundArea16` |
| S4 | 4704 | `E_GroundArea17` |
| S4 | 4714 | `E_GroundArea18` |
| S4 | 4722 | `E_GroundArea19` |
| S4 | 4731 | `E_GroundArea20` |
| S4 | 4738 | `E_GroundArea21` |
| S4 | 4743 | `E_GroundArea22` |
| S4 | 4751 | `E_UndergroundArea1` |
| S4 | 4760 | `E_UndergroundArea2` |
| S4 | 4769 | `E_UndergroundArea3` |
| S4 | 4777 | `E_WaterArea1` |
| S4 | 4783 | `E_WaterArea2` |
| S4 | 4791 | `E_WaterArea3` |


| S | Source-order chain | Exact target count | Primary owner | ROM route |
| --- | --- | ---: | --- | --- |
| S1 | `NonMaskableInterrupt` | 1 | `src/game/frame_root.c` | Controlled original NMI boundary through all direct NMI children. |
| S2 | `ScreenRoutines -> OutputCol` | 4 | `src/game/game.c`, `src/game/area.c` | Title/game/game-over screen tasks through parser completion and VRAM selector 6. |
| S3 | `KillEnemies` | 1 | `src/game/area.c` | Warp-zone and flagpole callers across all five enemy slots. |
| S4 | `E_CastleArea1 -> E_WaterArea3` | 34 | `src/game/enemy/stream.c` | Every enemy-stream pointer-table selector through bounded original area streams. |
| S5 | Cross-route integration certification | 0 | shared game roots | Reproducible title, gameplay, collision, terminal and audio route matrix. |

S1--S4 are implementation chains and may credit only their exact labels after
both ROM-logic and operational evidence. S5 has no node delta: it verifies the
completed graph, platform purity and three-target delivery. It cannot replace
an incomplete predecessor proof.

## T51 S1 admission: NMI parent integration

S1 receives `NonMaskableInterrupt` as its one source-order label. Baseline is
**1,952 / 1,992**; it is mapped but not complete and is the sole expected
match, so the maximum result is **1,953 / 1,992**. The source parent is the
NMI entry at `$82bc`; its direct completed children are `ScreenOff`,
`InitScroll`, `UpdateScreen`, `InitBuffer`, `SoundEngine`, `ReadJoypads`,
`PauseRoutine`, `UpdateTopScore`, timer work, sprite-zero handling, sprite
offscreen movement, sprite shuffle and `OperModeExecutionTree`.

ROM-logic verification compares the complete call sequence and branch gates,
the PPU mirror/mask, OAM DMA, selected VRAM buffer writes and clears, input,
timer, audio and operation-dispatch order at a controlled NMI boundary. It
also records the canonical exclusion for hardware interrupt/JSR stack bytes:
those bytes are CPU mechanics rather than translated game state and are not
added to `mysmb_game`. Operational verification runs the NMI boundary and
VRAM-table focused checks, platform-purity, x86/x64 comparison and builds, the
existing OpenNT DOS16 link, and refreshes the three local artifacts.

No platform source may add NMI decisions, table interpretation or PPU timing;
it only presents the shared game's committed outputs.

## T51 S1 closure: NMI parent integration

S1 closes its sole admitted label, `NonMaskableInterrupt`, from **1,952** to
**1,953 / 1,992**. No label was deferred or transferred. The source review
tracks `$82bc` through RTI: mirror `$2000` with d7 clear; the `ScreenOff`
mask gate; zero-scroll reset, OAM DMA, selected VRAM packet and `InitBuffer`;
then sound, joypad/debounce, pause, top-score, timer, LFSR, sprite-zero and
scroll phases; finally the operation-mode dispatch and the d7 re-enable. The
interrupt/JSR return stack bytes are excluded because they are CPU mechanics
and never translated game state.

The new shared-core `mysmb.nmi-parent-integration` check makes the order
observable in two source-reachable boundaries. Its ordinary NMI proves the
pre-clear OAM DMA image, subsequent sprite-offscreen write, VRAM packet before
header clear, command-derived `$2000` increment-bit result, timer/LFSR updates
and scene scroll. Its start-pause boundary proves joypad then pause before the
timer gate, while the LFSR continues. On both x86 and x64 it passes alongside
`mysmb.boot-nmi-boundary-smoke` and `mysmb.vram-address-table-smoke`; the
platform-purity check passes. The same shared C90 source links through OpenNT
DOS16 into a 264149-byte MZ program; established C4761 conversion and
`OLDNAMES.LIB` warnings remain non-fatal. Refreshed artifacts are
`mysmb16.exe` `0FE56863DA85261D8739D6BC709D24DCAA04C9D0288BB1D73EE512EFB17E847A`,
`mysmb32.exe` `E7025A800CA4D3CDB13814BB58BAFED75FECA9745D695661BE3CA426C873919A`,
and `mysmb64.exe` `CD8D5B0F3A09E741F7DCF5602EE4EF7153741B4F04FEAB97CB186B94E546E130`.

Similar-issue sweep: `src/platform` contains no NMI state decision, PPU mirror
interpretation, VRAM packet routing, input debounce or pause/timer branch.
Those all remain in the shared `src/game/frame_root.c` owner.

## T51 S2 admission: screen parser output chain

S2 receives exactly `ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop` and
`OutputCol`, all open at admission. Its baseline is **1,953 / 1,992** and all
four are expected matches, for a maximum of **1,957 / 1,992**. The source route
is `$852f ScreenRoutines` selector eight through `$86e6`: increment
`DisableScreenFlag`; repeatedly run one `AreaParserTaskHandler` subtask until
`AreaParserTaskNum` reaches zero; decrement `ColumnSets`; increment
`ScreenRoutineTask` only after its negative result; then unconditionally write
selector six to `$0773`. The shared C owners are `game.c` and `area.c`.

ROM-logic verification compares the dispatch table entry, loop exit condition,
underflow branch and writes in that exact order. Operational verification runs
the parser schedule and buffer-commit routes plus the focused parent NMI check
on x86/x64, platform purity, existing OpenNT DOS16 link and three artifact
refreshes.

## T51 S2 closure: screen parser output chain

S2 closes all four admitted labels, `ScreenRoutines`, `AreaParserTaskControl`,
`TaskLoop` and `OutputCol`, from **1,953** to **1,957 / 1,992**. The shared
C switch dispatches selector eight to `mysmb_area_parser_task_control`; that
owner increments `$0774`, executes all eight source parser subtasks until
`$071f` reaches zero, decrements `$071e`, advances `$073c` only on the
negative result, then writes `$0773 = 6`. No platform adapter participates.

The new shared `mysmb.screen-parser-output-chain` check runs both source
branches through the actual eight-subtask route: `ColumnSets=0` produces
`$ff`, advances task eight to nine, and writes selector six; `ColumnSets=1`
produces zero, retains task eight, and writes the same selector only after the
loop. Existing parser schedule and buffer-commit checks also pass, as does the
parent NMI check and platform-purity gate on x86/x64. OpenNT links the same C90
core to a 264149-byte DOS16 MZ; its established C4761 and OLDNAMES warnings
remain non-fatal. Artifacts: `mysmb16.exe`
`0FE56863DA85261D8739D6BC709D24DCAA04C9D0288BB1D73EE512EFB17E847A`,
`mysmb32.exe` `90A87B3A71D039F3A696DF45530474E32BDBF8FD76A3B1B029F546174D7B62D3`,
`mysmb64.exe` `FD5225DF27F4279285D1C1AA9BF182BDFF15DB73AD2D5A59308EC6BD46C7ED65`.
