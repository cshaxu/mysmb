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

## T51 S4 closure: original enemy-stream data and consumer chain

S4 closes all 34 admitted labels from **1,958 / 1,992** to **1,992 / 1,992**. The local audit binds every original stream literal span to the owner-local ROM, validates all 34 pointer-table entries and record framing, and preserves the E_GroundArea9 / E_GroundArea10 shared terminator. The new local-ROM shared C consumer test selects every family/area pointer with GetAreaDataAddrs and invokes mysmb_enemy_stream_process_current; it checks the resulting pointer registers and first-record consumption or terminator branch. x86 and x64 stream tests pass, platform purity passes, and the same shared source compiles and links with OpenNT DOS16. No node was deferred or transferred.

## T51 S5 admission: cross-route integration certification

S5 owns no node credit. It begins at **1,992 / 1,992** and validates the complete translated graph through the T51 cross-route matrix, x86/x64 and OpenNT DOS16 artifacts, and platform-purity audit. It cannot alter game logic merely to satisfy a platform route.

## T51 S5 integration finding: full matrix remains incomplete

The initial x64 matrix exposed eleven failures. S5 adjudicated
`enemy-background-entry` against `BlockBufferCollision` at `$e1ae`: its final
`DoEnemySideCheck` necessarily writes scratch `$02`, `$03`, `$05`, `$06` and
`$07`. The former test expected `$02/$03/$05` to remain zero, so it did not
describe the ROM route. Its corrected expectation passes the focused test on
x86 and x64; the full x86 matrix now has 233 tests with exactly ten failures:
core, area-entry, player bounding-box, enemy terrain state, hammer-bro, enemy
collision, Bowser, title/demo, end-to-end and local-area. S5 remains open and
M2 cannot close. Each remaining failure must be traced through its shared C
owner and original route before a node status changes.

### S5 P1: enemy-background-entry source-shaped expectation

This P changes no translated game or platform code and earns no node credit.
The final `EnemyJump -> DoEnemySideCheck -> BlockBufferCollision` route was
re-read from `$e163`, `$e0fe`, and `$e1ae`.  `BlockBufferCollision` writes its
probe scratch `$02`, `$03`, `$05`, `$06`, and `$07`; the legacy test preserved
only the final two writes and therefore falsely diagnosed the shared C route.
Its expectation now includes the ROM-selected right probe: `$05=$50`,
`$02=$60` normally or `$50` after the landing alignment, and `$03=$51` only
for the non-landing wall case.  No production behavior changed.

Focused and complete matrices agree: x86 and x64 each pass this route, and
each full 243-test matrix passes 233 tests with the same ten independently
open legacy failures named above. OpenNT's original DOS16 compiler/linker
also builds the same shared C90 source into a 264165-byte MZ executable, with
only the established C4761 conversion and absent `OLDNAMES.LIB` warnings.
The refreshed three-target artifacts are `mysmb16.exe`
`D3FE87771AFA2EA86435F41EA954055A21750A59151F76491B972BC11E175C2C`,
`mysmb32.exe` `07921E3F6374F992395BA33EFC350321E2CD30603CE145C171931B3BC800C3CD`,
and `mysmb64.exe` `F0EFDAFBB738DFE0D170BE3368B9526485A3C91D6A6533CE6671373E9A57F328`.
S5 remains open: this evidence removes one false test assertion, but does not
waive the ten remaining cross-route adjudications.

### S5 P2: enemy-terrain-state deterministic fixture and source result

This P likewise changes no production source and earns no node credit. The
legacy terrain fixture initialized only `game.ram`, leaving `area_prg` and
`area_prg_size` indeterminate. Its terrain route legitimately selects a
bound-ROM table when present, so the uninitialized pointer caused the reported
x86/x64 access violation rather than a game-logic fault. The fixture now
zeroes its complete game structure before selecting the intended fallback
tables.

The Goomba bumped-block expectation was also re-read through
`HandleEToBGCollision` at `$dffa`, `KillEnemyAboveBlock` at `$e164`,
`ShellOrBlockDefeat` at `$d795`, and the fall-through `ChkToStunEnemies` tail.
The source calls `SetStun` once under `ShellOrBlockDefeat`, then calls it a
second time after `GiveOEPoints`; each decrements Y twice. Starting at `$50`,
the correct final Y is therefore `$4c`, not the former `$4e`. Focused x86 and
x64 tests pass after that expectation correction. S5 remains open pending the
remaining nine cross-route failures.

### S5 P3: area-entry water-bubble expectation

No production source changes or node credit occur in this P. `Entrance_GameTimerSetup`
at `$9131` calls `SetupBubble` in water areas. `SetupBubble` at `$b6f9` falls
directly into `MoveBubl` at `$b713`: with this fixture's random selector one,
the initial Y `$08` borrows under force `$50`, compares below `$20`, and writes
the offscreen sentinel `$f8`. The old test expected the pre-fall-through `$08`.
The corrected x86/x64 focused test passes; S5 remains open for eight failures.

### S5 P4: player bounding-box initialization order

No production behavior changed. The legacy smoke entered `PlayerCtrlRoutine`
without the preceding `InitializeArea -> GetScreenPosition` route. The ROM
`GetScreenPosition` at `$b038` derives `ScreenRight_X_Pos` and
`ScreenRight_PageLoc`; `ChkPOffscr` reads those bytes before relative position
and `BoundingBoxCore`. Initializing that source precondition restores the
expected control-one box `$2b,$c4,$35,$d0`. The focused x86/x64 test passes;
S5 remains open for seven failures.

### S5 P5: Hammer Bro allocation and terrain fixture

No production code changes or node credit occur here. The `$fe` fixture had
marked all `Misc_State`, reserve `Enemy_Flag`, and block-buffer bytes occupied.
`SpawnHammerObj` requires its selected misc and reserve-enemy slots free; an
empty block buffer reaches `NoUnderHammerBro`, which sets state d0 before
`ProcHammerBro` sets throwing d3. The source result is `$09`, not `$08`.
After restoring these source preconditions, the focused Hammer Bro route
passes on x86 and x64; the complete x86 and x64 243-test matrices each retain
the same six unrelated legacy failures. S5 remains open for their ROM adjudication.

### S5 P6: enemy-pair current-slot fixture

No production code changes or node credit occur here. `EnemiesCollision` at
`$DA33` enters from `RunNormalEnemies` with `ObjectOffset` already selecting
the current object; `GetEnemyBoundBoxOfs` reads that RAM register before the
descending candidate loop. The smoke fixture supplied C argument one but left
`$08` at zero, so it compared slot zero's box with itself and set its collision
latch. Initializing `$08 = 1` restores the original caller precondition. The
newly built x86 and x64 focused test both pass. S5 remains open for five
unrelated legacy failures.

### S5 P7: Bowser fixture source-route completion

This P changes no translated game or platform source and earns no node credit.
The Bowser smoke had several independently missing source-route predecessors.
`MemoryInit` initializes original CPU RAM only, so the fixture first uses the
complete game constructor to establish null host-side resource bindings.
`FireballEnemyCollision` requires the `RunNormalEnemies`-prepared
`EnemyOffscrBitsMasked` byte; the fireball and Bowser coordinates are placed
in the visible left half because `CheckRightScreenBBox` clips the exact
right-edge position. The fifth-fireball assertion invokes the direct
`FireballObjCore` child, preventing a sibling fireball slot in the parent
wrapper from overwriting the child route's scratch state.

The bridge assertion binds only the required local `BlockGfxData[12..15]`
bytes (`$24`) before `RemBridge`, then invokes the NMI-side `UpdateScreen`
buffer commit directly. Entering the complete GameEngine at that point would
be a different ROM route and requires a fully bound area image. The focused
`mysmb.bowser-smoke` route now passes on freshly built x86 and x64 targets;
the platform-purity audit also passes. The existing OpenNT DOS16 toolchain
links the unchanged shared C90 sources to a 264165-byte MZ executable
(`D3FE87771AFA2EA86435F41EA954055A21750A59151F76491B972BC11E175C2C`),
with only its established C4761 and `OLDNAMES.LIB` warnings. The three
owner-local application artifacts are unchanged because this P changes only
the test fixture. S5 remains open for four unrelated legacy failures: `core`,
`title-demo`, `end-to-end`, and `local-area`.

### S5 P8: legacy-suite source-route closure

This P changes no shared game or platform behavior and earns no node credit.
It resolves the final four legacy fixtures by comparing each precondition and
postcondition with its selected original-ROM route. `core_smoke` no longer
requires an invented forty-frame entrance X threshold; it uses the per-slot
normal-enemy caller, legal terrain state, caller-owned player bounding box,
current source-table windows and the valid fiery-fireball gate. Its power-up
ground branch now expects `LandEnemyProperly` to align Y to `$58`, clear d6,
and preserve zero vertical force. `title_demo_smoke` follows the actual
`RunDemo -> GameCoreRoutine -> PlayerLoseLife -> ContinueGame` return path.
The ROM-free end-to-end fixture proves only the title-to-game handoff because
an unbound `LoadAreaPointer` cannot enter the parser. `local_area_smoke` is
compiled against owner-local generated PRG/CHR/title data, retaining all
protected data below ignored build output.

The CMake-generated command manifests were executed directly because their
Ninja regeneration wrapper stalls before producing targets. This changes no
build rule: each manifest command used its configured compiler, flags and
link inputs. Both complete native matrices pass, x64 218/218 in 57.97 seconds
and x86 218/218 in 113.15 seconds. The owner-local area route passes on both
widths; platform-purity and documentation-governance checks pass. OpenNT
again compiles and links the complete shared C90 plus DOS adapter to a
264165-byte MZ program, with only the established C4761 and `OLDNAMES.LIB`
warnings. Owner-local Win32 x86/x64 packages embed generated local ROM data
and pass their `--self-test` route. Refreshed artifact hashes are
`mysmb16.exe` `D3FE87771AFA2EA86435F41EA954055A21750A59151F76491B972BC11E175C2C`,
`mysmb32.exe` `DDCD4DC6A16C01E6DC8A50AAB29EF43A85E71A1124D007C494B0A18AD7DFEBF4`,
and `mysmb64.exe` `DE701E81C81CA3F2AE408F463EBB6F85960340FC00CB362B975E3208A519CBFD`.

### S5 P21: coin/axe terrain-tail current replay

This zero-credit audit resolves the final terrain coin/axe VRAM-status tail
without changing production or platform source. The retained T43 S2 original
ROM corpus has 128 parent `HandleCoinMetatile` / `HandleAxeMetatile` calls and
192 ordered child records for `RemoveCoin_Axe` and `GiveOneCoin`. The current
shared library matches every parent and child record on x86 and x64, including
RAM `$00`, `$02`, and `$03`. The earlier mismatches were historical results
from before P16 restored `PrintStatusBarNumbers` / `OutputNumbers` scratch
returns; they are not a remaining terrain-route discrepancy.

The ROM-logic route uses the retained original parent entry and ordered child
boundaries, with owner-local PRG bound only below ignored build output. The
separate operational route runs the project terrain-metatile chain on both
native widths, platform purity, the documentation-governance gate, and hash
verification of the required owner-local delivery artifacts. The retained
artifacts are `mysmb16.exe`
`4E09CEC47999ECEC0C9BA7EF3D6842F3D3285AA41C908A3FD5068F853A2639B7`,
`mysmb32.exe` `0E7039F85B097899184561530CEA130E4508E1F1A9FAFD59DA9F8B50C213E65F`,
and `mysmb64.exe` `855F7E7607B0AEBAC7F2BA5D39E540205B98AD0F6DFC96A6F18B2B13B2481432`.

### S5 P22: enemy loop, parser and initializer current replay

This zero-credit audit resolves three historic child-route ledger rows without
changing production or platform source. The current shared library replays all
96 retained enemy-loop records, all 80 `ProcessEnemyData` parser records, and
all 110 `CheckpointEnemyID` / initializer-vector records on each native width.
Every one matches its original-ROM RAM result: 286 / 286 on x86 and 286 / 286
on x64. In particular, the old loop/parser/initializer `$04-$07` scratch
differences are absent from the current library.

The ROM-logic track binds the owner-local PRG only in ignored replay output and
invokes the original-route entry selected by each retained record, with no
child substitution or masked game RAM. Operational verification runs the
shared enemy-loop check on x86/x64, platform purity and documentation
governance; delivery artifacts remain hash-verified as the P17 set:
`mysmb16.exe` `4E09CEC47999ECEC0C9BA7EF3D6842F3D3285AA41C908A3FD5068F853A2639B7`,
`mysmb32.exe` `0E7039F85B097899184561530CEA130E4508E1F1A9FAFD59DA9F8B50C213E65F`,
and `mysmb64.exe` `855F7E7607B0AEBAC7F2BA5D39E540205B98AD0F6DFC96A6F18B2B13B2481432`.

### S5 P23: restore NMI RTI PPU control

This shared-core repair restores the final `NonMaskableInterrupt` physical
`$2000` write. The ROM saves its d7-cleared control mirror after scroll setup,
runs `OperModeExecutionTree`, then executes `PLA`, `ORA #$80`, and `STA
$2000`. Mode code may update the RAM mirror for the next NMI, but cannot leave
the current frame's physical PPU control at that new mirror. The C root had
omitted this final restoration, allowing a mode-tree name-table write to leave
the visible control at `$10` instead of `$90`.

The repair keeps this state decision in `src/game/frame_root.c`, shared by
Win32 x86/x64 and DOS16. Fresh owner-local original cold-start replay now
matches the PPU-control scalar at the historical Start samples 1/202 and idle
sample 1 on both native widths. The remaining differences in the wider old
title route occur before this NMI tail and are retained separately for their
audio/title owners; no unrelated output is treated as resolved here.

Operational verification uses current x86/x64 NMI-parent, boot-NMI and frame
snapshot checks, platform purity, and an OpenNT DOS16 compile/link. Refreshed
owner-authorized artifacts are `mysmb16.exe`
`40F217DAAFC549E6F32E1B1B73F04CC749CC6E4B137612A19276D6836A60E0E7`,
`mysmb32.exe` `5DB4379CDE428FA4356F1FD1D17FC2FEAA8089E3AB29731AC196A5331E7C79C6`,
and `mysmb64.exe` `FD3D1D06EDA57B33F54B1007C6CFF422D84DA052A18E52B626EE058144D4D963`.

### S5 P16: score and coin scratch-return repair

S5 P16 repairs the T37 S4 score/coin scratch discrepancy in the shared game
owner, `src/game/status.c`. The original `PrintStatusBarNumbers` saves its
incoming selector in `$00`; each `OutputNumbers` pass writes its initial VRAM
buffer command position to `$02`, decrements the digit counter in `$03` to
zero, and then updates the buffer offset. The C body had kept all three values
in locals, so `GiveOneCoin -> AddToScore -> GetSBNybbles -> UpdateNumber`
returned the wrong visible scratch state. The repair restores only those
source writes and makes no platform change.

The local ROM route replays all 56 retained score/HUD snapshots with `$00-$07`
included in comparison: x86 and x64 each match all 56, including the former
AddToScore and SetupJumpCoin cases. The permanent shared `core_smoke` now
checks the source scratch endpoint. It passes after direct x86/x64 relink,
as do the 2,560-case score/HUD and 16,400-case coin-allocation checks on each
width. OpenNT compiles and links the same C90 source; its established C4761
and missing OLDNAMES warnings remain non-fatal. Platform code is unchanged.

Refreshed artifacts are `mysmb16.exe`
`7A242FBF2C74F80CB9BAD55EBA38B78B353165323894E1D5717D88144079B875`,
`mysmb32.exe` `363F79073255697773E8438040BF7E85D833E557BCDCE75C42313D10D34C11B2`,
and `mysmb64.exe` `C8264B98778F7C7209E6D1C81EC824C12F929982B6C0998DEEF9CBB2102BA5BF`.

### S5 P17: block-replacement VRAM high-row repair

S5 P17 repairs the T37 S6 `ReplaceBlockMetatile` high-row output mismatch in
the shared `src/game/area/block_metatile.c` owner. At `PutBlockMetatile`, the
ROM's `ADC #$20` leaves an eight-bit A result; the following `ASL` overwrites
that addition's carry before either `ROL $05`. The former C expression kept
the wide addition's overflow through the two shifts, producing `$24` where
the ROM emits `$20`, or `$28` where it emits `$24`. The corrected code stores
the wrapped byte before the shifts. No platform source changed.

All 32 retained original block-replacement snapshots now match on both x86
and x64, including the former twelve `$0301/$0306` failures. The permanent
shared core check now covers an overflowing high-row case. Existing exhaustive
block-replacement checks pass on both widths, and OpenNT recompiles and links
the same C90 source with only its established warnings.

Refreshed artifacts are `mysmb16.exe`
`4E09CEC47999ECEC0C9BA7EF3D6842F3D3285AA41C908A3FD5068F853A2639B7`,
`mysmb32.exe` `0E7039F85B097899184561530CEA130E4508E1F1A9FAFD59DA9F8B50C213E65F`,
and `mysmb64.exe` `855F7E7607B0AEBAC7F2BA5D39E540205B98AD0F6DFC96A6F18B2B13B2481432`.

S5 remains open despite the complete native matrix. The review ledger still
contains independently recorded original-ROM discrepancies and the DOS16
resource-binding gap. Passing a project-owned regression suite does not
replace their source-route evidence or establish DOS16 playability.

### S5 P18: jumpspring screen-origin offscreen revalidation

This P closes no inventory node and changes no shared game behavior. It
rechecks the historical T30/S7 report that a jumpspring could be erased before
area creation near screen origin. The current shared `OffscreenBoundsCheck`
already carries the ROM's byte-wise `CPY`, `ADC`, and `SBC` results: for
object `$32`, `ScreenLeft = $00:$00` becomes the left boundary `$ff:$b8`.
The original page-zero spring position is therefore inside the source range;
the right-side object exception is not used to hide an erroneous left erase.

`mysmb.jumpspring-origin-offscreen` enters the real
`JumpspringHandler -> OffscreenBoundsCheck` sequence with that boundary. It
asserts no erasure, preserves the object flag, and checks the original `$00`
through `$03` scratch boundary bytes. The new x86 and x64 checks each pass;
the exhaustive shared offscreen suite also passes 524,288 cases on each
width. This removes the stale pre-T41 finding without granting node credit.
No DOS-specific or platform source changed. The current three delivery
artifacts remain P17's validated outputs while the DOS16 resource-binding
requirement remains a separate M3 concern.

### S5 P19: terrain residual ledger normalization

This zero-credit audit removes a stale subclaim from the terrain debt record.
T43's pre-T44 child output reported missing block-query scratch bytes. T44 S1
later replaced that incomplete seam with the shared
`BlockBufferColli_Head/Feet/Side -> BlockBufferCollision` owner, proving the
original selector paths, tables, page carry and `$02-$07` scratch on original
player, enemy and fireball routes. The remaining terrain record is narrowed
to the independently unproven `PlayerHeadCollision` and coin/axe VRAM/status
tails. No production source or platform code changes in this P, no node credit
is granted, and the three P17 delivery artifacts remain the current validated
outputs.

### S5 P20: PlayerHeadCollision current replay

This zero-credit audit reruns the retained 72 original `PlayerHeadCollision`
snapshots against the current shared game library on both native widths. All
72 records match on x86 and all 72 match on x64. The sixteen historical
failures are no longer present: their `$00c0/$00c1` block-chunk effect and
`$00fd/$00ff` score/status effects were repaired by their later source-owned
chains. This closes the historical head-collision residual without assigning
new node credit. Coin/axe VRAM/status tails remain independently open. No
platform or production source changes; the P17 three-artifact set remains
the validated delivery output.

### S5 P9: historical-debt source-route adjudication

S5 P9 audits four still-open ledger rows against their later, source-order
closures before treating them as active gaps. This is a documentation and
evidence correction only; it admits no new node and changes no game or platform
code. `KillEnemies` is covered by T51 S3, `ImpedePlayerMove` through `ExIPM` by
T43 S6, `ForceInjury` by T42 S5, and `PlayerLakituDiff` by T40 S10. Each later
chain explicitly records original control flow and RAM effects, while the
current focused x86/x64 executables pass their corresponding checks.

The four historical TODO rows are therefore marked resolved with a direct link
to their superseding closure. This audit does not resolve any remaining row:
the unresolved ledger still supplies the basis for S5's final discrepancy
review, including the distinct DOS16 owner-resource binding gap.

### S5 P10: Spiny historical-route adjudication

S5 P10 resolves one additional historical ledger row without admitting node
credit or changing production code. T39 S5 recorded a `lakitu_smoke` failure
before the later source-order `PlayerLakituDiff` chain existed. T40 S10 then
proved the shared helper's Spiny adjustment, scratch and returned-speed
semantics across original routes, converting all 124 retained Spiny comparisons
to matches. The current `mysmb.lakitu-smoke` executable passes on x86 and x64.
The unrelated actor-vector, normal-actor, special-actor and firebar child
differences remain active and are not affected by this record correction.

### S5 P11: star-flag historical-route adjudication

S5 P11 resolves the T39 endgame timer assertion as superseded historical debt,
not as a new node or implementation change. T41 S6 subsequently migrated and
proved the complete source chain containing `AwardGameTimerPoints` and
`NoTTick`, including frame-bit sound gating and the two modifier calls. The
current x86 and x64 star-flag native route each passes 779 cases. Other
endgame, actor and graphics records are outside this conclusion.

### S5 P12: projectile and block-graphics historical-route adjudication

S5 P12 resolves two historical OAM records and narrows a third mixed record.
T45 S2 proves the complete block/brick-chunk graphics chain that previously
caused the T37 OAM differences. T45 S3 proves `DrawFireball` and
`DrawExplosion_Fireball`, resolving T24 D3/D4. T45 S5 separately resolves D5
through the original `SwimKickTileNum` table and consumer route, so the retained
mixed record now names only D6-D8. Current focused fireball, block and player
OAM tests pass on x86 and x64. This audit does not resolve the retained
throw-pose, attribute or swimming-freeze cases.

### S5 P13: vine-graphics historical-route adjudication

S5 P13 resolves the T36 vine OAM clipping record through T44 S2's complete
source chain. The later chain proves `DrawVine`, `ChkFTop` and `NextVSp` on
original `VDrawLoop` routes, including the wrapped subtraction that caused the
old discrepancy. The current vine OAM check passes on x86 and x64. This does
not assert equivalence for the separate `GetMiscBoundBox` dependency.

### S5 P14: fireball-dispatch and Goomba historical-route adjudication

S5 P14 resolves T24 D1/D2 as historical findings superseded by later complete
source chains. T34 S1 restores the single `PlayerStatus` partition in
`ProcFireball_Bubble`. T42 S1/S2 restore the Goomba ID-six exclusion and score
handoff inside fireball collision processing. Current x86/x64 dispatch, scan
and hit-chain checks pass. No geometry or unrelated collision child is claimed
by this adjudication.

### S5 P15: star-pickup music historical-route adjudication

S5 P15 resolves T37 S1 case 46 as a historical finding superseded by T42 S4's
complete `PlayerEnemyCollision -> HandlePowerUpCollision` chain. The source
star branch queues `$40` in `AreaMusicQueue` `$fb` after the common pickup
setup. T42's original actor comparison records the case as matching on both
Windows widths. The current shared direct pickup-chain executable covers
393,216 type/status/slot cases, including child-mutated type/status inputs,
with zero failures on x86 and x64. This is an evidence adjudication only: it
does not claim the separate score/coin scratch-return discrepancy.

No translated C source or build input changes in this evidence-only P, so the
three current delivery artifacts are retained after hash verification:
`mysmb16.exe` `D3FE87771AFA2EA86435F41EA954055A21750A59151F76491B972BC11E175C2C`,
`mysmb32.exe` `DDCD4DC6A16C01E6DC8A50AAB29EF43A85E71A1124D007C494B0A18AD7DFEBF4`,
and `mysmb64.exe` `DE701E81C81CA3F2AE408F463EBB6F85960340FC00CB362B975E3208A519CBFD`.
