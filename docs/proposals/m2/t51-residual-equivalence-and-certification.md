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

## T51 S3 admission: KillEnemies shared primitive

S3 receives exactly `KillEnemies`, transferred from `M2 T29 S8` by
`transfer-281-to-t51-s3`. Its incoming state is `audited; mismatch`; baseline
is **1,957 / 1,992** and its sole expected match gives a maximum of
**1,958 / 1,992**. The source at `$9716` stores its A-register identifier in
`$00`, loads zero once, starts X at four and decrements through slots four to
zero. For each `Enemy_ID,x` equal to `$00`, it writes that zero to
`Enemy_Flag,x`; nonmatching slots remain untouched.

The shared `src/game/area.c` owner serves the same primitive from the warp-zone
PiranhaPlant caller and the flagpole BulletBill_CannonVar caller. ROM-logic
verification compares the entry `$00` write, load-once zero, inclusive
five-slot order and conditional flag write. Operational verification runs a
controlled all-slots test for both caller IDs, focused x86/x64 tests, the
platform-purity audit, OpenNT DOS16 link, and refreshes all three artifacts.

## T51 S3 closure: KillEnemies shared primitive

S3 closes `KillEnemies`, its only admitted node, from **1,957** to
**1,958 / 1,992**. The shared owner now writes the entry identifier to `$00`,
then begins the source-shaped zero/load and X=4 downward loop. Slots 4 through
0 compare `Enemy_ID,x` with `$00`; only equal slots receive zero in
`Enemy_Flag,x`. The controlled check proves this exact selective result for the
WarpNum PiranhaPlant (`$0d`) and flagpole BulletBill_CannonVar (`$0b`) callers.

The x86 and x64 focused primitive, parser-chain and NMI-parent checks pass.
The platform-purity audit passes. OpenNT links the same C90 core to the
264165-byte DOS16 MZ with only established C4761 and OLDNAMES warnings.
Artifacts: `mysmb16.exe`
`D3FE87771AFA2EA86435F41EA954055A21750A59151F76491B972BC11E175C2C`,
`mysmb32.exe` `A1CA95022E329C65F16255409BACBB2BE7357EF06BA056E4CB38E981336505CF`,
and `mysmb64.exe` `60C17F2C44CE5DF9D4AE62EF5D37C52559F5476848C0D328A04BD6255D421FCD`.

## T51 S4 admission: original enemy-stream data and consumer chain

S4 receives exactly 34 mapped-but-incomplete original data labels through
`transfer-282-to-t51-s4`: `E_CastleArea1` through `E_CastleArea6`,
`E_GroundArea1` through `E_GroundArea22`, `E_UndergroundArea1` through
`E_UndergroundArea3`, and `E_WaterArea1` through `E_WaterArea3`. They are in
their original source order from `$a3a3` through `$a747`; each is expected to
become a match. The baseline is **1,958 / 1,992**, the maximum closing result
is **1,992 / 1,992**, and every incoming label is `mapped; evidence
incomplete`.

The chain begins at the first castle stream and ends at the final water stream.
`GetAreaDataAddrs` selects the corresponding pointer-table entry into `$e9/$ea`;
the shared `src/game/enemy/stream.c` owner then performs the source-current
stream read, record dispatch, cursor movement and terminator handoff. The
completed pointer tables are the predecessor; `ProcessEnemyData` and its actor
children are the successor dependencies. The original-ROM route selects each
family/area pointer, consumes every record with the current-stream owner, and
checks the resulting cursor and terminator behavior.

ROM-logic evidence must separately establish exact local ROM/assembly bytes,
family pointer-table selection, record framing, end markers, the
`E_GroundArea9`/`E_GroundArea10` shared-terminator alias, and the consumer's
source read/call ordering. Operational evidence is the enemy-data audit plus a
local-ROM current-stream consumer check on x86 and x64, platform purity, the
existing OpenNT DOS16 compile/link, and refreshed three-target artifacts.
