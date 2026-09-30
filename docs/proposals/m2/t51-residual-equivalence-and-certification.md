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
`E_WaterArea1` through `E_WaterArea3`. The ranges are inclusive; they name
every source label in each numbered family.

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
