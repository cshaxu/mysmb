# SMB1 ROM migration inventory and conformance checklist

Generated from `build/reference-source/SMBDIS.ASM`; SHA-256: `c8e91408db55341394f41000a6eeb6a9e804ab78c2172d2477ec278fe22e55df`. This file is the mandatory work index for the native C port. It intentionally records no inferred equivalence: an item is conformant only when its original branch semantics, writes, and frame-trace evidence are recorded.

## Rules

- ROM assembly is the authority for all game behavior. The C source must name the original routine(s) it ports.
- `src/game` owns every game decision, PPU-state construction, OAM construction, and input decoding. `src/platform` may only collect host input, schedule frames, and submit the already constructed frame.
- A green unit test alone does not close an item. Each behavioral item needs a ROM-reference frame script and comparison of the affected CPU RAM, CIRAM, palette, OAM, PPU state, and audio state.
- No ad-hoc behavior change is permitted. A repair first names the checklist entry, original labels, exact source branch path, and regression route.
- The control graph is authoritative for executable structure. Data labels are separately tracked because tables and constants are part of ROM fidelity, but they do not become synthetic C functions.

## Inventory size

- Assembly labels: `1992`

## Match accounting

The current aggregate and the named unfinished set are maintained in the [M2 ROM-node progress report](../../states/NODE_PROGRESS.md). In this table, only an explicit ROM-reference-verified completion counts as a match; `open`, `ported`, `mapped`, or `route trace pending` do not. Every S admission and closure records its `completed / 1992` total there and updates the exact rows below before claiming progress.

## Authoritative top-level execution tree

```text
Start / ColdBoot
├─ InitializeMemory, InitializeNameTables, title bootstrap
└─ NonMaskableInterrupt — once per frame
   ├─ InitScroll(0,0) → OAM DMA → UpdateScreen
   ├─ SoundEngine → ReadJoypads → PauseRoutine → UpdateTopScore
   ├─ timer bank / FrameCounter / LFSR
   ├─ sprite-0 split: MoveSpritesOffscreen + SpriteShuffler → scene scroll
   └─ OperModeExecutionTree
      ├─ TitleScreenMode
      ├─ GameMode
      │  ├─ InitializeArea
      │  ├─ ScreenRoutines
      │  ├─ SecondaryGameSetup
      │  └─ GameCoreRoutine
      │     ├─ GameRoutines[GameEngineSubroutine]
      │     └─ GameEngine
      │        ├─ ProcFireball_Bubble
      │        ├─ six × (EnemiesAndLoopsCore → FloateyNumbersRoutine)
      │        ├─ player relative position / PlayerGfxHandler
      │        ├─ block objects → misc objects → cannon/whirlpool/flagpole
      │        └─ timer/palette/parser/save-input tail
      ├─ VictoryMode
      └─ GameOverMode
```

The labels and branches behind every line remain open until individually bound below. Source anchors: `NonMaskableInterrupt` line 764, `OperModeExecutionTree` line 954, `GameMode` line 5310, `GameCoreRoutine` line 5318, `GameEngine` line 5336, and `GameRoutines` line 5583.

## Logical tree and module gates

- [ ] **Boot, reset, NMI, timing and input**
  - [ ] `Start` — ROM line 699; C owner/evidence pending
  - [ ] `ColdBoot` — ROM line 721; C owner/evidence pending
  - [ ] `NonMaskableInterrupt` — ROM line 764; C owner/evidence pending
  - [ ] `PauseRoutine` — ROM line 876; C owner/evidence pending
  - [ ] `OperModeExecutionTree` — ROM line 954; C owner/evidence pending
- [ ] **Title, demo, selection and victory modes**
  - [ ] `TitleScreenMode` — ROM line 982; C owner/evidence pending
  - [ ] `GameMenuRoutine` — ROM line 996; C owner/evidence pending
  - [ ] `DemoEngine` — ROM line 1119; C owner/evidence pending
  - [ ] `VictoryMode` — ROM line 1137; C owner/evidence pending
  - [ ] `PlayerEndWorld` — ROM line 1256; C owner/evidence pending
- [ ] **Screen sequencing, text, status and PPU buffers**
  - [ ] `ScreenRoutines` — ROM line 1386; C owner/evidence pending
  - [ ] `InitScreen` — ROM line 1408; C owner/evidence pending
  - [ ] `WriteTopStatusLine` — ROM line 1517; C owner/evidence pending
  - [ ] `WriteBottomStatusLine` — ROM line 1524; C owner/evidence pending
  - [ ] `AreaParserTaskControl` — ROM line 1595; C owner/evidence pending
  - [ ] `WriteGameText` — ROM line 1719; C owner/evidence pending
- [ ] **Area parser, metatile/attribute rendering and scrolling**
  - [ ] `RenderAreaGraphics` — ROM line 1825; C owner/evidence pending
  - [ ] `RenderAttributeTables` — ROM line 1920; C owner/evidence pending
  - [ ] `AreaParserTaskHandler` — ROM line 3060; C owner/evidence pending
  - [ ] `AreaParserCore` — ROM line 3179; C owner/evidence pending
  - [ ] `AreaParserTasks` — ROM line 3073; C owner/evidence pending
  - [ ] `ScrollScreen` — ROM line 5427; C owner/evidence pending
- [ ] **Game engine, mode transitions and timers**
  - [ ] `GameCoreRoutine` — ROM line 5326; C owner/evidence pending
  - [ ] `GameEngine` — ROM line 5336; C owner/evidence pending
  - [ ] `GameRoutines` — ROM line 5499; C owner/evidence pending
  - [ ] `GameTimerExpired` — label lookup pending
  - [ ] `PlayerEndLevel` — ROM line 5856; C owner/evidence pending
- [ ] **Player movement, physics, collision and size state**
  - [ ] `PlayerCtrlRoutine` — ROM line 5583; C owner/evidence pending
  - [ ] `MovePlayerHorizontally` — ROM line 7561; C owner/evidence pending
  - [ ] `PlayerBGCollision` — ROM line 11927; C owner/evidence pending
  - [ ] `PlayerHeadCollision` — ROM line 7244; C owner/evidence pending
  - [ ] `PlayerChangeSize` — ROM line 5757; C owner/evidence pending
- [ ] **Enemy stream, object initialization and enemy behavior**
  - [ ] `ProcessEnemyData` — ROM line 7911; C owner/evidence pending
  - [ ] `PositionEnemyObj` — ROM line 7967; C owner/evidence pending
  - [ ] `CheckpointEnemyID` — ROM line 8080; C owner/evidence pending
  - [ ] `EnemiesAndLoopsCore` — ROM line 7788; C owner/evidence pending
  - [ ] `RunNormalEnemies` — ROM line 9092; C owner/evidence pending
- [ ] **Blocks, coins, power-ups, vines and miscellaneous objects**
  - [ ] `BlockObjMT_Updater` — ROM line 7527; C owner/evidence pending
  - [ ] `BumpBlock` — ROM line 7332; C owner/evidence pending
  - [ ] `CoinBlock` — ROM line 6988; C owner/evidence pending
  - [ ] `SetupPowerUp` — ROM line 7150; C owner/evidence pending
  - [ ] `PowerUpObjHandler` — ROM line 7184; C owner/evidence pending
  - [ ] `VineObjectHandler` — ROM line 6730; C owner/evidence pending
- [ ] **Fireballs, projectile collision and special hazards**
  - [ ] `FireballObjCore` — ROM line 6352; C owner/evidence pending
  - [ ] `FireballBGCollision` — ROM line 12751; C owner/evidence pending
  - [ ] `FireballEnemyCollision` — ROM line 11085; C owner/evidence pending
  - [ ] `ProcFireball_Bubble` — ROM line 6298; C owner/evidence pending
- [ ] **Object graphics, OAM construction and offscreen bits**
  - [ ] `PlayerGfxHandler` — ROM line 14460; C owner/evidence pending
  - [ ] `EnemyGraphicsEngine` — label lookup pending
  - [ ] `MiscObjOffset` — label lookup pending
  - [ ] `GetEnemyOffscreenBits` — ROM line 14879; C owner/evidence pending
  - [ ] `GetFireballOffscreenBits` — ROM line 14851; C owner/evidence pending
- [ ] **Audio engine, music and sound effects**
  - [ ] `SoundEngine` — ROM line 15070; C owner/evidence pending
  - [ ] `Square1SfxHandler` — ROM line 15256; C owner/evidence pending
  - [ ] `Square2SfxHandler` — ROM line 15455; C owner/evidence pending
  - [ ] `NoiseSfxHandler` — ROM line 15600; C owner/evidence pending
  - [ ] `MusicHandler` — ROM line 15635; C owner/evidence pending
- [ ] **Shared arithmetic, RNG, VRAM and utility primitives**
  - [ ] `InitializeMemory` — ROM line 2795; C owner/evidence pending
  - [ ] `GetPlayerOffscreenBits` — ROM line 14846; C owner/evidence pending
  - [ ] `RelativePlayerPosition` — ROM line 14786; C owner/evidence pending
  - [ ] `MoveObjectHorizontally` — ROM line 7566; C owner/evidence pending
  - [ ] `ImposeGravity` — ROM line 7729; C owner/evidence pending

## Mandatory conformance gates

- [ ] Every label below is assigned to exactly one logical owner or explicitly classified as a local branch of an assigned owner.
- [ ] Every `src/game` entry point has its ROM label set, state-write map, and trace route recorded.
- [ ] Every visible OAM family, status-bar split, palette/CIRAM path, and audio queue has a matching reference route.
- [ ] W1-1 title/start, movement/jump, coin/block, mushroom/fire-flower, damage/death/restart, pipe, flag/castle, warp and two-player routes pass frame comparison on x86 and x64.
- [ ] x86 and x64 native traces are byte-identical for every approved route.
- [ ] DOS backend consumes the same game frame contract; its adapter has no game-state write.

## Complete ROM label index — unclassified items remain open

| ROM source line | label | owner | status | evidence |
|---:|---|---|---|---|
| 699 | `Start` | T22 S14: shared boot/timing boundary | ROM-match complete | [T22 S14 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s14-boot-root-equivalence-result) |
| 706 | `VBlank1` | T22 S14: shared boot/timing boundary | ROM-match complete | [T22 S14 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s14-boot-root-equivalence-result) |
| 708 | `VBlank2` | T22 S14: shared boot/timing boundary | ROM-match complete | [T22 S14 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s14-boot-root-equivalence-result) |
| 712 | `WBootCheck` | T22 S14: shared boot/timing boundary | ROM-match complete | [T22 S14 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s14-boot-root-equivalence-result) |
| 721 | `ColdBoot` | T22 S14: shared boot/timing boundary | ROM-match complete | [T22 S14 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s14-boot-root-equivalence-result) |
| 737 | `EndlessLoop` | T22 S14: shared boot/timing boundary | ROM-match complete | [T22 S14 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s14-boot-root-equivalence-result) |
| 743 | `VRAM_AddrTable_Low` | T22 S15: shared frame-root selector-table owner | ROM-match complete | [T22 S15 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s15-vram-address-table-equivalence-result) |
| 752 | `VRAM_AddrTable_High` | T22 S15: shared frame-root selector-table owner | ROM-match complete | [T22 S15 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s15-vram-address-table-equivalence-result) |
| 761 | `VRAM_Buffer_Offset` | T22 S15: shared frame-root selector-table owner | ROM-match complete | [T22 S15 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s15-vram-address-table-equivalence-result) |
| 764 | `NonMaskableInterrupt` | T22 S15: independent selector-table equivalence review; src/game/frame_root.c | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nonmaskableinterrupt) |
| 776 | `ScreenOff` | T22 S9: src/game/frame_root.c mirror-to-physical mask branch | ROM-match complete | [T22 S9 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s9-screenoff-evidence) |
| 796 | `InitBuffer` | T22 S23: shared frame-root selected-header clear | ROM-match complete | [T22 S23 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s23-initbuffer-equivalence-result) |
| 814 | `DecTimers` | T22 S25: independent timer/LFSR equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dectimers) |
| 820 | `DecTimersLoop` | T22 S25: independent timer/LFSR equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dectimersloop) |
| 823 | `SkipExpTimer` | T22 S25: independent timer/LFSR equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipexptimer) |
| 825 | `NoDecTimers` | T22 S25: independent timer/LFSR equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nodectimers) |
| 826 | `PauseSkip` | T22 S25: independent timer/LFSR equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pauseskip) |
| 837 | `RotPRandomBit` | T22 S25: independent timer/LFSR equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rotprandombit) |
| 843 | `Sprite0Clr` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sprite0clr) |
| 851 | `Sprite0Hit` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sprite0hit) |
| 855 | `HBlankDelay` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hblankdelay) |
| 857 | `SkipSprite0` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipsprite0) |
| 868 | `SkipMainOper` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipmainoper) |
| 876 | `PauseRoutine` | T22 S24: independent pause-route equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pauseroutine) |
| 885 | `ChkPauseTimer` | T22 S24: independent pause-route equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkpausetimer) |
| 889 | `ChkStart` | T22 S24: independent pause-route equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkstart) |
| 904 | `ClrPauseTimer` | T22 S24: independent pause-route equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clrpausetimer) |
| 906 | `SetPause` | T22 S24: independent pause-route equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setpause) |
| 907 | `ExitPause` | T22 S24: independent pause-route equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitpause) |
| 912 | `SpriteShuffler` | T22 S15: independent selector-table equivalence review; src/game/frame_root.c | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spriteshuffler) |
| 917 | `ShuffleLoop` | T22 S15: independent selector-table equivalence review; src/game/frame_root.c | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-shuffleloop) |
| 926 | `StrSprOffset` | T22 S15: independent selector-table equivalence review; src/game/frame_root.c | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strsproffset) |
| 927 | `NextSprOffset` | T22 S15: independent selector-table equivalence review; src/game/frame_root.c | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextsproffset) |
| 934 | `SetAmtOffset` | T22 S15: independent selector-table equivalence review; src/game/frame_root.c | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setamtoffset) |
| 937 | `SetMiscOffset` | T22 S15: independent selector-table equivalence review; src/game/frame_root.c | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setmiscoffset) |
| 954 | `OperModeExecutionTree` | T22 S15: independent selector-table equivalence review; src/game/frame_root.c | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-opermodeexecutiontree) |
| 965 | `MoveAllSpritesOffscreen` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/boot.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveallspritesoffscreen) |
| 969 | `MoveSpritesOffscreen` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movespritesoffscreen) |
| 972 | `SprInitLoop` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sprinitloop) |
| 982 | `TitleScreenMode` | T15 responsibility (implementation not certified); `frame_root.c:mysmb_frame_root_step` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-titlescreenmode) |
| 993 | `WSelectBufferTemplate` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-wselectbuffertemplate) |
| 996 | `GameMenuRoutine` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_title_step` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gamemenuroutine) |
| 1004 | `StartGame` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_start_from_title` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-startgame) |
| 1005 | `ChkSelect` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_title_step` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkselect) |
| 1013 | `ChkWorldSel` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkworldsel) |
| 1018 | `SelectBLogic` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_title_step` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-selectblogic) |
| 1033 | `IncWorldSel` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_title_step` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incworldsel) |
| 1039 | `UpdateShroom` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_title_step` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-updateshroom) |
| 1047 | `NullJoypad` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_title_step` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nulljoypad) |
| 1049 | `RunDemo` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rundemo) |
| 1053 | `ResetTitle` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_title_step` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-resettitle) |
| 1059 | `ChkContinue` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_start_from_title` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkcontinue) |
| 1065 | `StartWorld1` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_start_from_title` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-startworld1) |
| 1077 | `InitScores` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initscores) |
| 1080 | `ExitMenu` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitmenu) |
| 1081 | `GoContinue` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_start_from_title` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gocontinue) |
| 1090 | `MushroomIconData` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mushroomicondata) |
| 1093 | `DrawMushroomIcon` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawmushroomicon) |
| 1095 | `IconDataRead` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-icondataread) |
| 1105 | `ExitIcon` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exiticon) |
| 1109 | `DemoActionData` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-demoactiondata) |
| 1114 | `DemoTimingData` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-demotimingdata) |
| 1119 | `DemoEngine` | T15 responsibility (implementation not certified); `title_modes.c:mysmb_game_step_title_demo` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-demoengine) |
| 1129 | `DoAction` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doaction) |
| 1133 | `DemoOver` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-demoover) |
| 1137 | `VictoryMode` | T15 responsibility (implementation not certified); `frame_root.c` + `terminal_modes.c:mysmb_game_step_victory` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-victorymode) |
| 1144 | `AutoPlayer` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-autoplayer) |
| 1147 | `VictoryModeSubroutines` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_step_victory` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-victorymodesubroutines) |
| 1159 | `SetupVictoryMode` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_step_victory` + `player.c` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupvictorymode) |
| 1169 | `PlayerVictoryWalk` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_step_victory` + `player.c` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playervictorywalk) |
| 1178 | `PerformWalk` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-performwalk) |
| 1180 | `DontWalk` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dontwalk) |
| 1195 | `ExitVWalk` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitvwalk) |
| 1201 | `PrintVictoryMessages` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_print_victory_messages` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-printvictorymessages) |
| 1215 | `MRetainerMsg` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mretainermsg) |
| 1217 | `ThankPlayer` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-thankplayer) |
| 1223 | `SecondPartMsg` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-secondpartmsg) |
| 1232 | `EvalForMusic` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-evalformusic) |
| 1236 | `PrintMsg` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-printmsg) |
| 1240 | `IncMsgCounter` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incmsgcounter) |
| 1248 | `SetEndTimer` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setendtimer) |
| 1251 | `IncModeTask_A` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incmodetask_a) |
| 1252 | `ExitMsgs` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitmsgs) |
| 1256 | `PlayerEndWorld` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_step_victory` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerendworld) |
| 1271 | `EndExitOne` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endexitone) |
| 1272 | `EndChkBButton` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endchkbbutton) |
| 1281 | `EndExitTwo` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endexittwo) |
| 1287 | `FloateyNumTileData` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-floateynumtiledata) |
| 1303 | `ScoreUpdateData` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-scoreupdatedata) |
| 1308 | `FloateyNumbersRoutine` | T15 responsibility (implementation not certified); `objects.c:mysmb_objects_step_floatey_number` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-floateynumbersroutine) |
| 1315 | `ChkNumTimer` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chknumtimer) |
| 1320 | `DecNumTimer` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decnumtimer) |
| 1328 | `LoadNumTiles` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadnumtiles) |
| 1338 | `ChkTallEnemy` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chktallenemy) |
| 1355 | `GetAltOffset` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getaltoffset) |
| 1358 | `FloateyPart` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-floateypart) |
| 1363 | `SetupNumSpr` | T15 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupnumspr) |
| 1386 | `ScreenRoutines` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-screenroutines) |
| 1408 | `InitScreen` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initscreen) |
| 1418 | `SetupIntermediate` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupintermediate) |
| 1436 | `AreaPalette` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areapalette) |
| 1439 | `GetAreaPalette` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getareapalette) |
| 1442 | `SetVRAMAddr_A` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setvramaddr_a) |
| 1443 | `NextSubtask` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextsubtask) |
| 1448 | `BGColorCtrl_Addr` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bgcolorctrl_addr) |
| 1451 | `BackgroundColors` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-backgroundcolors) |
| 1455 | `PlayerColors` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playercolors) |
| 1460 | `GetBackgroundColor` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getbackgroundcolor) |
| 1465 | `NoBGColor` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nobgcolor) |
| 1467 | `GetPlayerColors` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getplayercolors) |
| 1473 | `ChkFiery` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfiery) |
| 1477 | `StartClrGet` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-startclrget) |
| 1479 | `ClrGetLoop` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clrgetloop) |
| 1489 | `SetBGColor` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setbgcolor) |
| 1502 | `SetVRAMOffset` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setvramoffset) |
| 1507 | `GetAlternatePalette1` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getalternatepalette1) |
| 1512 | `SetVRAMAddr_B` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setvramaddr_b) |
| 1513 | `NoAltPal` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noaltpal) |
| 1517 | `WriteTopStatusLine` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writetopstatusline) |
| 1524 | `WriteBottomStatusLine` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writebottomstatusline) |
| 1553 | `DisplayTimeUp` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-displaytimeup) |
| 1560 | `NoTimeUp` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notimeup) |
| 1565 | `DisplayIntermediate` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-displayintermediate) |
| 1577 | `PlayerInter` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerinter) |
| 1579 | `OutputInter` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-outputinter) |
| 1584 | `GameOverInter` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gameoverinter) |
| 1589 | `NoInter` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nointer) |
| 1595 | `AreaParserTaskControl` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areaparsertaskcontrol) |
| 1597 | `TaskLoop` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-taskloop) |
| 1603 | `OutputCol` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-outputcol) |
| 1612 | `DrawTitleScreen` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawtitlescreen) |
| 1624 | `OutputTScr` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-outputtscr) |
| 1629 | `ChkHiByte` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkhibyte) |
| 1639 | `ClearBuffersDrawIcon` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clearbuffersdrawicon) |
| 1643 | `TScrClear` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-tscrclear) |
| 1648 | `IncSubtask` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incsubtask) |
| 1653 | `WriteTopScore` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writetopscore) |
| 1656 | `IncModeTask_B` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incmodetask_b) |
| 1661 | `GameText` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gametext) |
| 1662 | `TopStatusBarLine` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-topstatusbarline) |
| 1671 | `WorldLivesDisplay` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-worldlivesdisplay) |
| 1680 | `TwoPlayerTimeUp` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-twoplayertimeup) |
| 1682 | `OnePlayerTimeUp` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-oneplayertimeup) |
| 1686 | `TwoPlayerGameOver` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-twoplayergameover) |
| 1688 | `OnePlayerGameOver` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-oneplayergameover) |
| 1693 | `WarpZoneWelcome` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-warpzonewelcome) |
| 1704 | `LuigiName` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-luiginame) |
| 1707 | `WarpZoneNumbers` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-warpzonenumbers) |
| 1712 | `GameTextOffsets` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gametextoffsets) |
| 1719 | `WriteGameText` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writegametext) |
| 1728 | `Chk2Players` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk2players) |
| 1731 | `LdGameText` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ldgametext) |
| 1733 | `GameTextLoop` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gametextloop) |
| 1740 | `EndGameText` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endgametext) |
| 1756 | `PutLives` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-putlives) |
| 1765 | `CheckPlayerName` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkplayername) |
| 1775 | `ChkLuigi` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkluigi) |
| 1778 | `NameLoop` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nameloop) |
| 1782 | `ExitChkName` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitchkname) |
| 1784 | `PrintWarpZoneNumbers` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-printwarpzonenumbers) |
| 1790 | `WarpNumLoop` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-warpnumloop) |
| 1804 | `ResetSpritesAndScreenTimer` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-resetspritesandscreentimer) |
| 1809 | `ResetScreenTimer` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-resetscreentimer) |
| 1813 | `NoReset` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noreset) |
| 1825 | `RenderAreaGraphics` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-renderareagraphics) |
| 1840 | `DrawMTLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawmtloop) |
| 1878 | `RightCheck` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rightcheck) |
| 1886 | `LLeft` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lleft) |
| 1888 | `NextMTRow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextmtrow) |
| 1889 | `SetAttrib` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setattrib) |
| 1914 | `ExitDrawM` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitdrawm) |
| 1920 | `RenderAttributeTables` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-renderattributetables) |
| 1930 | `SetATHigh` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setathigh) |
| 1940 | `AttribLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-attribloop) |
| 1962 | `SetVRAMCtrl` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setvramctrl) |
| 1970 | `ColorRotatePalette` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-colorrotatepalette) |
| 1973 | `BlankPalette` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blankpalette) |
| 1977 | `Palette3Data` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-palette3data) |
| 1983 | `ColorRotation` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-colorrotation) |
| 1991 | `GetBlankPal` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getblankpal) |
| 2004 | `GetAreaPal` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getareapal) |
| 2024 | `ExitColorRot` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitcolorrot) |
| 2034 | `BlockGfxData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockgfxdata) |
| 2041 | `RemoveCoin_Axe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-removecoin_axe) |
| 2047 | `WriteBlankMT` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writeblankmt) |
| 2052 | `ReplaceBlockMetatile` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-replaceblockmetatile) |
| 2058 | `DestroyBlockMetatile` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-destroyblockmetatile) |
| 2061 | `WriteBlockMetatile` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writeblockmetatile) |
| 2076 | `UseBOffset` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-useboffset) |
| 2080 | `MoveVOffset` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movevoffset) |
| 2086 | `PutBlockMetatile` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-putblockmetatile) |
| 2097 | `SaveHAdder` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-savehadder) |
| 2118 | `RemBridge` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rembridge) |
| 2145 | `MetatileGraphics_Low` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-metatilegraphics_low) |
| 2148 | `MetatileGraphics_High` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-metatilegraphics_high) |
| 2151 | `Palette0_MTiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-palette0_mtiles) |
| 2192 | `Palette1_MTiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-palette1_mtiles) |
| 2240 | `Palette2_MTiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-palette2_mtiles) |
| 2252 | `Palette3_MTiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-palette3_mtiles) |
| 2263 | `WaterPaletteData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-waterpalettedata) |
| 2275 | `GroundPaletteData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundpalettedata) |
| 2287 | `UndergroundPaletteData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-undergroundpalettedata) |
| 2299 | `CastlePaletteData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-castlepalettedata) |
| 2311 | `DaySnowPaletteData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-daysnowpalettedata) |
| 2316 | `NightSnowPaletteData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nightsnowpalettedata) |
| 2321 | `MushroomPaletteData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mushroompalettedata) |
| 2326 | `BowserPaletteData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bowserpalettedata) |
| 2331 | `MarioThanksMessage` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mariothanksmessage) |
| 2339 | `LuigiThanksMessage` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-luigithanksmessage) |
| 2347 | `MushroomRetainerSaved` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mushroomretainersaved) |
| 2358 | `PrincessSaved1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-princesssaved1) |
| 2366 | `PrincessSaved2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-princesssaved2) |
| 2375 | `WorldSelectMessage1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-worldselectmessage1) |
| 2382 | `WorldSelectMessage2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-worldselectmessage2) |
| 2395 | `JumpEngine` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpengine) |
| 2412 | `InitializeNameTables` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initializenametables) |
| 2421 | `WriteNTAddr` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writentaddr) |
| 2427 | `InitNTLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initntloop) |
| 2436 | `InitATLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initatloop) |
| 2446 | `ReadJoypads` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-readjoypads) |
| 2454 | `ReadPortBits` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-readportbits) |
| 2455 | `PortLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-portloop) |
| 2474 | `Save8Bits` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-save8bits) |
| 2482 | `WriteBufferToScreen` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writebuffertoscreen) |
| 2495 | `SetupWrites` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupwrites) |
| 2501 | `GetLength` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getlength) |
| 2504 | `OutputToVRAM` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-outputtovram) |
| 2506 | `RepeatByte` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-repeatbyte) |
| 2523 | `UpdateScreen` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-updatescreen) |
| 2527 | `InitScroll` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initscroll) |
| 2533 | `WritePPUReg1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-writeppureg1) |
| 2544 | `StatusBarData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-statusbardata) |
| 2552 | `StatusBarOffset` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-statusbaroffset) |
| 2555 | `PrintStatusBarNumbers` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-printstatusbarnumbers) |
| 2564 | `OutputNumbers` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-outputnumbers) |
| 2578 | `SetupNums` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupnums) |
| 2592 | `DigitPLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-digitploop) |
| 2604 | `ExitOutputN` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitoutputn) |
| 2608 | `DigitsMathRoutine` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-digitsmathroutine) |
| 2613 | `AddModLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-addmodloop) |
| 2619 | `StoreNewD` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-storenewd) |
| 2623 | `EraseDMods` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-erasedmods) |
| 2625 | `EraseMLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-erasemloop) |
| 2629 | `BorrowOne` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-borrowone) |
| 2632 | `CarryOne` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-carryone) |
| 2639 | `UpdateTopScore` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-updatetopscore) |
| 2644 | `TopScoreCheck` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-topscorecheck) |
| 2647 | `GetScoreDiff` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getscorediff) |
| 2655 | `CopyScore` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-copyscore) |
| 2661 | `NoTopSc` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notopsc) |
| 2665 | `DefaultSprOffsets` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-defaultsproffsets) |
| 2669 | `Sprite0Data` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sprite0data) |
| 2674 | `InitializeGame` | T18 responsibility (implementation not certified); `title_modes.c:mysmb_game_begin_title_bootstrap` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initializegame) |
| 2678 | `ClrSndLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clrsndloop) |
| 2685 | `InitializeArea` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initializearea) |
| 2690 | `ClrTimersLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clrtimersloop) |
| 2697 | `StartPage` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-startpage) |
| 2705 | `SetInitNTHigh` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setinitnthigh) |
| 2728 | `SetSecHard` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setsechard) |
| 2729 | `CheckHalfway` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkhalfway) |
| 2733 | `DoneInitArea` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doneinitarea) |
| 2742 | `PrimaryGameSetup` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-primarygamesetup) |
| 2750 | `SecondaryGameSetup` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-secondarygamesetup) |
| 2754 | `ClearVRLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clearvrloop) |
| 2775 | `ShufAmtLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-shufamtloop) |
| 2780 | `ISpr0Loop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ispr0loop) |
| 2795 | `InitializeMemory` | T22 S14: shared boot/timing boundary | ROM-match complete | [T22 S14 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s14-boot-root-equivalence-result) |
| 2799 | `InitPageLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initpageloop) |
| 2800 | `InitByteLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initbyteloop) |
| 2804 | `InitByte` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initbyte) |
| 2805 | `SkipByte` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipbyte) |
| 2814 | `MusicSelectData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-musicselectdata) |
| 2818 | `GetAreaMusic` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getareamusic) |
| 2830 | `ChkAreaType` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkareatype) |
| 2834 | `StoreMusic` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-storemusic) |
| 2836 | `ExitGetM` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitgetm) |
| 2840 | `PlayerStarting_X_Pos` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerstarting_x_pos) |
| 2844 | `AltYPosOffset` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-altyposoffset) |
| 2847 | `PlayerStarting_Y_Pos` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerstarting_y_pos) |
| 2851 | `PlayerBGPriorityData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerbgprioritydata) |
| 2854 | `GameTimerData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gametimerdata) |
| 2858 | `Entrance_GameTimerSetup` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-entrance_gametimersetup) |
| 2874 | `ChkStPos` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkstpos) |
| 2881 | `SetStPos` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setstpos) |
| 2900 | `ChkOverR` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkoverr) |
| 2911 | `ChkSwimE` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkswime) |
| 2914 | `SetPESub` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setpesub) |
| 2921 | `HalfwayPageNybbles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-halfwaypagenybbles) |
| 2931 | `PlayerLoseLife` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerloselife) |
| 2944 | `StillInGame` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-stillingame) |
| 2951 | `GetHalfway` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gethalfway) |
| 2960 | `MaskHPNyb` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-maskhpnyb) |
| 2965 | `SetHalfway` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sethalfway) |
| 2971 | `GameOverMode` | T18 responsibility (implementation not certified); `frame_root.c` + `terminal_modes.c:mysmb_game_step_game_over` | mapped; evidence incomplete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gameovermode) |
| 2981 | `SetupGameOver` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupgameover) |
| 2993 | `RunGameOver` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rungameover) |
| 3001 | `TerminateGame` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-terminategame) |
| 3015 | `ContinueGame` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuegame) |
| 3027 | `GameIsOn` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gameison) |
| 3029 | `TransposePlayers` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-transposeplayers) |
| 3039 | `TransLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-transloop) |
| 3048 | `ExTrans` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-extrans) |
| 3052 | `DoNothing1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-donothing1) |
| 3055 | `DoNothing2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-donothing2) |
| 3060 | `AreaParserTaskHandler` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areaparsertaskhandler) |
| 3065 | `DoAPTasks` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doaptasks) |
| 3071 | `SkipATRender` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipatrender) |
| 3073 | `AreaParserTasks` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areaparsertasks) |
| 3087 | `IncrementColumnPos` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incrementcolumnpos) |
| 3094 | `NoColWrap` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nocolwrap) |
| 3106 | `BSceneDataOffsets` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bscenedataoffsets) |
| 3109 | `BackSceneryData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-backscenerydata) |
| 3131 | `BackSceneryMetatiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-backscenerymetatiles) |
| 3145 | `FSceneDataOffsets` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fscenedataoffsets) |
| 3148 | `ForeSceneryData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-forescenerydata) |
| 3158 | `TerrainMetatiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-terrainmetatiles) |
| 3161 | `TerrainRenderBits` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-terrainrenderbits) |
| 3179 | `AreaParserCore` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areaparsercore) |
| 3184 | `RenderSceneryTerrain` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendersceneryterrain) |
| 3187 | `ClrMTBuf` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clrmtbuf) |
| 3193 | `ThirdP` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-thirdp) |
| 3198 | `RendBack` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendback) |
| 3223 | `SceLoop1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sceloop1) |
| 3231 | `RendFore` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendfore) |
| 3235 | `SceLoop2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sceloop2) |
| 3238 | `NoFore` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nofore) |
| 3242 | `RendTerr` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendterr) |
| 3249 | `TerMTile` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-termtile) |
| 3253 | `StoreMT` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-storemt) |
| 3258 | `TerrLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-terrloop) |
| 3269 | `NoCloud2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nocloud2) |
| 3270 | `TerrBChk` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-terrbchk) |
| 3275 | `NextTBit` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nexttbit) |
| 3285 | `EndUChk` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enduchk) |
| 3290 | `RendBBuf` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendbbuf) |
| 3295 | `ChkMTLow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkmtlow) |
| 3306 | `StrBlock` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strblock) |
| 3319 | `BlockBuffLowBounds` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbufflowbounds) |
| 3326 | `ProcessAreaData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-processareadata) |
| 3328 | `ProcADLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procadloop) |
| 3345 | `Chk1Row13` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk1row13) |
| 3363 | `Chk1Row14` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk1row14) |
| 3367 | `CheckRear` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkrear) |
| 3370 | `RdyDecode` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rdydecode) |
| 3372 | `SetBehind` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setbehind) |
| 3373 | `NextAObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextaobj) |
| 3374 | `ChkLength` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chklength) |
| 3378 | `ProcLoopb` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procloopb) |
| 3384 | `EndAParse` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endaparse) |
| 3386 | `IncAreaObjOffset` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incareaobjoffset) |
| 3393 | `DecodeAreaData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decodeareadata) |
| 3397 | `Chk1stB` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk1stb) |
| 3408 | `ChkRow14` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkrow14) |
| 3416 | `ChkRow13` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkrow13) |
| 3429 | `Mask2MSB` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mask2msb) |
| 3431 | `ChkSRows` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chksrows) |
| 3442 | `LrgObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lrgobj) |
| 3450 | `NotWPipe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notwpipe) |
| 3452 | `SpecObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-specobj) |
| 3455 | `MoveAOId` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveaoid) |
| 3459 | `NormObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-normobj) |
| 3472 | `LeavePar` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-leavepar) |
| 3473 | `InitRear` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initrear) |
| 3479 | `LoopCmdE` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loopcmde) |
| 3480 | `BackColC` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-backcolc) |
| 3489 | `StrAObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-straobj) |
| 3492 | `RunAObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runaobj) |
| 3561 | `AlterAreaAttributes` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-alterareaattributes) |
| 3580 | `Alter2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-alter2) |
| 3586 | `SetFore` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfore) |
| 3591 | `ScrollLockObject_Warp` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-scrolllockobject_warp) |
| 3600 | `WarpNum` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-warpnum) |
| 3606 | `ScrollLockObject` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-scrolllockobject) |
| 3615 | `KillEnemies` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killenemies) |
| 3619 | `KillELoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killeloop) |
| 3623 | `NoKillE` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nokille) |
| 3629 | `FrenzyIDData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-frenzyiddata) |
| 3632 | `AreaFrenzy` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areafrenzy) |
| 3635 | `FreCompLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-frecomploop) |
| 3640 | `ExitAFrenzy` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitafrenzy) |
| 3646 | `AreaStyleObject` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areastyleobject) |
| 3653 | `TreeLedge` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-treeledge) |
| 3665 | `MidTreeL` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-midtreel) |
| 3670 | `EndTreeL` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endtreel) |
| 3673 | `MushroomLedge` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mushroomledge) |
| 3682 | `EndMushL` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endmushl) |
| 3696 | `AllUnder` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-allunder) |
| 3699 | `NoUnder` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nounder) |
| 3706 | `PulleyRopeMetatiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pulleyropemetatiles) |
| 3709 | `PulleyRopeObject` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pulleyropeobject) |
| 3717 | `RenderPul` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-renderpul) |
| 3719 | `MushLExit` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mushlexit) |
| 3724 | `CastleMetatiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-castlemetatiles) |
| 3737 | `CastleObject` | T18: `src/game/area.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-castleobject) |
| 3748 | `CRendLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-crendloop) |
| 3759 | `ChkCFloor` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkcfloor) |
| 3772 | `NotTall` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nottall) |
| 3789 | `PlayerStop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerstop) |
| 3791 | `ExitCastle` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitcastle) |
| 3795 | `WaterPipe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-waterpipe) |
| 3810 | `IntroPipe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-intropipe) |
| 3817 | `VPipeSectLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vpipesectloop) |
| 3823 | `NoBlankP` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noblankp) |
| 3825 | `SidePipeShaftData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sidepipeshaftdata) |
| 3828 | `SidePipeTopPart` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sidepipetoppart) |
| 3831 | `SidePipeBottomPart` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sidepipebottompart) |
| 3835 | `ExitPipe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitpipe) |
| 3840 | `RenderSidewaysPipe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendersidewayspipe) |
| 3855 | `DrawSidePart` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawsidepart) |
| 3862 | `VerticalPipeData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-verticalpipedata) |
| 3868 | `VerticalPipe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-verticalpipe) |
| 3876 | `WarpPipe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-warppipe) |
| 3900 | `DrawPipe` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawpipe) |
| 3911 | `GetPipeHeight` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getpipeheight) |
| 3921 | `FindEmptyEnemySlot` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-findemptyenemyslot) |
| 3923 | `EmptyChkLoop` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-emptychkloop) |
| 3929 | `ExitEmptyChk` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitemptychk) |
| 3933 | `Hole_Water` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hole_water) |
| 3944 | `QuestionBlockRow_High` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-questionblockrow_high) |
| 3948 | `QuestionBlockRow_Low` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-questionblockrow_low) |
| 3960 | `Bridge_High` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridge_high) |
| 3964 | `Bridge_Middle` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridge_middle) |
| 3968 | `Bridge_Low` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridge_low) |
| 3983 | `FlagBalls_Residual` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagballs_residual) |
| 3991 | `FlagpoleObject` | T22 responsibility; `area.c`: object decode; `oam/flagpole_gfx.c`: start/step | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-flagpoleobject) |
| 4018 | `EndlessRope` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endlessrope) |
| 4023 | `BalancePlatRope` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-balanceplatrope) |
| 4034 | `DrawRope` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawrope) |
| 4039 | `CoinMetatileData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-coinmetatiledata) |
| 4042 | `RowOfCoins` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rowofcoins) |
| 4049 | `C_ObjectRow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-c_objectrow) |
| 4052 | `C_ObjectMetatile` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-c_objectmetatile) |
| 4055 | `CastleBridgeObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-castlebridgeobj) |
| 4060 | `AxeObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-axeobj) |
| 4064 | `ChainObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chainobj) |
| 4070 | `EmptyBlock` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-emptyblock) |
| 4074 | `ColObj` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-colobj) |
| 4079 | `SolidBlockMetatiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-solidblockmetatiles) |
| 4082 | `BrickMetatiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-brickmetatiles) |
| 4086 | `RowOfBricks` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rowofbricks) |
| 4091 | `DrawBricks` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawbricks) |
| 4094 | `RowOfSolidBlocks` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rowofsolidblocks) |
| 4097 | `GetRow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getrow) |
| 4099 | `DrawRow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawrow) |
| 4104 | `ColumnOfBricks` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-columnofbricks) |
| 4109 | `ColumnOfSolidBlocks` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-columnofsolidblocks) |
| 4112 | `GetRow2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getrow2) |
| 4120 | `BulletBillCannon` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bulletbillcannon) |
| 4135 | `SetupCannon` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupcannon) |
| 4146 | `StrCOffset` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strcoffset) |
| 4151 | `StaircaseHeightData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-staircaseheightdata) |
| 4154 | `StaircaseRowData` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-staircaserowdata) |
| 4157 | `StaircaseObject` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-staircaseobject) |
| 4162 | `NextStair` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextstair) |
| 4172 | `Jumpspring` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpspring) |
| 4197 | `Hidden1UpBlock` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hidden1upblock) |
| 4204 | `QuestionBlock` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-questionblock) |
| 4208 | `BrickWithCoins` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-brickwithcoins) |
| 4212 | `BrickWithItem` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-brickwithitem) |
| 4220 | `BWithL` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bwithl) |
| 4223 | `DrawQBlk` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawqblk) |
| 4228 | `GetAreaObjectID` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getareaobjectid) |
| 4233 | `ExitDecBlock` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitdecblock) |
| 4237 | `HoleMetatiles` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-holemetatiles) |
| 4240 | `Hole_Empty` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hole_empty) |
| 4265 | `StrWOffset` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strwoffset) |
| 4266 | `NoWhirlP` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nowhirlp) |
| 4273 | `RenderUnderPart` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-renderunderpart) |
| 4289 | `DrawThisRow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawthisrow) |
| 4290 | `WaitOneRow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-waitonerow) |
| 4296 | `ExitUPartR` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitupartr) |
| 4300 | `ChkLrgObjLength` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chklrgobjlength) |
| 4303 | `ChkLrgObjFixedLength` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chklrgobjfixedlength) |
| 4310 | `LenSet` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lenset) |
| 4313 | `GetLrgObjAttrib` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getlrgobjattrib) |
| 4326 | `GetAreaObjXPosition` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getareaobjxposition) |
| 4336 | `GetAreaObjYPosition` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getareaobjyposition) |
| 4349 | `BlockBufferAddr` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbufferaddr) |
| 4353 | `GetBlockBufferAddr` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getblockbufferaddr) |
| 4376 | `AreaDataOfsLoopback` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areadataofsloopback) |
| 4381 | `LoadAreaPointer` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadareapointer) |
| 4384 | `GetAreaType` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getareatype) |
| 4392 | `FindAreaPointer` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-findareapointer) |
| 4402 | `GetAreaDataAddrs` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getareadataaddrs) |
| 4434 | `StoreFore` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-storefore) |
| 4472 | `StoreStyle` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-storestyle) |
| 4485 | `WorldAddrOffsets` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-worldaddroffsets) |
| 4491 | `AreaAddrOffsets` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areaaddroffsets) |
| 4492 | `World1Areas` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-world1areas) |
| 4493 | `World2Areas` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-world2areas) |
| 4494 | `World3Areas` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-world3areas) |
| 4495 | `World4Areas` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-world4areas) |
| 4496 | `World5Areas` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-world5areas) |
| 4497 | `World6Areas` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-world6areas) |
| 4498 | `World7Areas` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-world7areas) |
| 4499 | `World8Areas` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-world8areas) |
| 4509 | `EnemyAddrHOffsets` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemyaddrhoffsets) |
| 4512 | `EnemyDataAddrLow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemydataaddrlow) |
| 4520 | `EnemyDataAddrHigh` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemydataaddrhigh) |
| 4528 | `AreaDataHOffsets` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areadatahoffsets) |
| 4531 | `AreaDataAddrLow` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areadataaddrlow) |
| 4539 | `AreaDataAddrHigh` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areadataaddrhigh) |
| 4550 | `E_CastleArea1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_castlearea1) |
| 4558 | `E_CastleArea2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_castlearea2) |
| 4565 | `E_CastleArea3` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_castlearea3) |
| 4574 | `E_CastleArea4` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_castlearea4) |
| 4583 | `E_CastleArea5` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_castlearea5) |
| 4589 | `E_CastleArea6` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_castlearea6) |
| 4598 | `E_GroundArea1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea1) |
| 4606 | `E_GroundArea2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea2) |
| 4613 | `E_GroundArea3` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea3) |
| 4619 | `E_GroundArea4` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea4) |
| 4627 | `E_GroundArea5` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea5) |
| 4636 | `E_GroundArea6` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea6) |
| 4643 | `E_GroundArea7` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea7) |
| 4650 | `E_GroundArea8` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea8) |
| 4656 | `E_GroundArea9` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea9) |
| 4662 | `E_GroundArea10` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea10) |
| 4666 | `E_GroundArea11` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea11) |
| 4674 | `E_GroundArea12` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea12) |
| 4679 | `E_GroundArea13` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea13) |
| 4687 | `E_GroundArea14` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea14) |
| 4695 | `E_GroundArea15` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea15) |
| 4700 | `E_GroundArea16` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea16) |
| 4704 | `E_GroundArea17` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea17) |
| 4714 | `E_GroundArea18` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea18) |
| 4722 | `E_GroundArea19` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea19) |
| 4731 | `E_GroundArea20` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea20) |
| 4738 | `E_GroundArea21` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea21) |
| 4743 | `E_GroundArea22` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_groundarea22) |
| 4751 | `E_UndergroundArea1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_undergroundarea1) |
| 4760 | `E_UndergroundArea2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_undergroundarea2) |
| 4769 | `E_UndergroundArea3` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_undergroundarea3) |
| 4777 | `E_WaterArea1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_waterarea1) |
| 4783 | `E_WaterArea2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_waterarea2) |
| 4791 | `E_WaterArea3` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-e_waterarea3) |
| 4799 | `L_CastleArea1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_castlearea1) |
| 4814 | `L_CastleArea2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_castlearea2) |
| 4832 | `L_CastleArea3` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_castlearea3) |
| 4849 | `L_CastleArea4` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_castlearea4) |
| 4865 | `L_CastleArea5` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_castlearea5) |
| 4884 | `L_CastleArea6` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_castlearea6) |
| 4900 | `L_GroundArea1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea1) |
| 4915 | `L_GroundArea2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea2) |
| 4931 | `L_GroundArea3` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea3) |
| 4944 | `L_GroundArea4` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea4) |
| 4963 | `L_GroundArea5` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea5) |
| 4980 | `L_GroundArea6` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea6) |
| 4995 | `L_GroundArea7` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea7) |
| 5009 | `L_GroundArea8` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea8) |
| 5027 | `L_GroundArea9` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea9) |
| 5042 | `L_GroundArea10` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea10) |
| 5048 | `L_GroundArea11` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea11) |
| 5059 | `L_GroundArea12` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea12) |
| 5066 | `L_GroundArea13` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea13) |
| 5081 | `L_GroundArea14` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea14) |
| 5096 | `L_GroundArea15` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea15) |
| 5113 | `L_GroundArea16` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea16) |
| 5123 | `L_GroundArea17` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea17) |
| 5143 | `L_GroundArea18` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea18) |
| 5160 | `L_GroundArea19` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea19) |
| 5177 | `L_GroundArea20` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea20) |
| 5191 | `L_GroundArea21` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea21) |
| 5200 | `L_GroundArea22` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_groundarea22) |
| 5210 | `L_UndergroundArea1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_undergroundarea1) |
| 5231 | `L_UndergroundArea2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_undergroundarea2) |
| 5252 | `L_UndergroundArea3` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_undergroundarea3) |
| 5271 | `L_WaterArea1` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_waterarea1) |
| 5282 | `L_WaterArea2` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_waterarea2) |
| 5299 | `L_WaterArea3` | T18 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-l_waterarea3) |
| 5315 | `GameMode` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gamemode) |
| 5326 | `GameCoreRoutine` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gamecoreroutine) |
| 5336 | `GameEngine` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gameengine) |
| 5339 | `ProcELoop` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-proceloop) |
| 5371 | `NoChgMus` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nochgmus) |
| 5377 | `CycleTwo` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cycletwo) |
| 5380 | `ClrPlrPal` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clrplrpal) |
| 5381 | `SaveAB` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-saveab) |
| 5385 | `UpdScrollVar` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-updscrollvar) |
| 5398 | `RunParser` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runparser) |
| 5399 | `ExitEng` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exiteng) |
| 5403 | `ScrollHandler` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-scrollhandler) |
| 5422 | `ChkNearMid` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chknearmid) |
| 5427 | `ScrollScreen` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-scrollscreen) |
| 5451 | `InitScrlAmt` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initscrlamt) |
| 5453 | `ChkPOffscr` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkpoffscr) |
| 5463 | `KeepOnscr` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-keeponscr) |
| 5475 | `InitPlatScrl` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initplatscrl) |
| 5479 | `X_SubtracterData` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-x_subtracterdata) |
| 5482 | `OffscrJoypadBitsData` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-offscrjoypadbitsdata) |
| 5487 | `GetScreenPosition` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getscreenposition) |
| 5499 | `GameRoutines` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gameroutines) |
| 5519 | `PlayerEntrance` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerentrance) |
| 5532 | `ChkBehPipe` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkbehpipe) |
| 5536 | `IntroEntr` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-introentr) |
| 5541 | `EntrMode2` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-entrmode2) |
| 5549 | `VineEntr` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vineentr) |
| 5562 | `OffVine` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-offvine) |
| 5567 | `PlayerRdy` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerrdy) |
| 5575 | `ExitEntr` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitentr) |
| 5580 | `AutoControlPlayer` | dispatcher candidate / historical T8 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-autocontrolplayer) |
| 5583 | `PlayerCtrlRoutine` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerctrlroutine) |
| 5595 | `DisJoyp` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-disjoyp) |
| 5597 | `SaveJoyp` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-savejoyp) |
| 5615 | `SizeChk` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sizechk) |
| 5623 | `ChkMoveDir` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkmovedir) |
| 5629 | `SetMoveDir` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setmovedir) |
| 5630 | `PlayerSubs` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playersubs) |
| 5649 | `PlayerHole` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerhole) |
| 5661 | `HoleDie` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-holedie) |
| 5670 | `HoleBottom` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-holebottom) |
| 5672 | `ChkHoleX` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkholex) |
| 5680 | `ExitCtrl` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitctrl) |
| 5682 | `CloudExit` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cloudexit) |
| 5691 | `Vine_AutoClimb` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vine_autoclimb) |
| 5697 | `AutoClimb` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-autoclimb) |
| 5702 | `SetEntr` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setentr) |
| 5708 | `VerticalPipeEntry` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-verticalpipeentry) |
| 5722 | `MovePlayerYAxis` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveplayeryaxis) |
| 5730 | `SideExitPipeEntry` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sideexitpipeentry) |
| 5733 | `ChgAreaPipe` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chgareapipe) |
| 5736 | `ChgAreaMode` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chgareamode) |
| 5740 | `ExitCAPipe` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitcapipe) |
| 5742 | `EnterSidePipe` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-entersidepipe) |
| 5751 | `RightPipe` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rightpipe) |
| 5757 | `PlayerChangeSize` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerchangesize) |
| 5762 | `EndChgSize` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endchgsize) |
| 5765 | `ExitChgSize` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitchgsize) |
| 5769 | `PlayerInjuryBlink` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerinjuryblink) |
| 5776 | `ExitBlink` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitblink) |
| 5778 | `InitChangeSize` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initchangesize) |
| 5786 | `ExitBoth` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitboth) |
| 5791 | `PlayerDeath` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerdeath) |
| 5797 | `DonePlayerTask` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doneplayertask) |
| 5804 | `PlayerFireFlower` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerfireflower) |
| 5812 | `CyclePlayerPalette` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cycleplayerpalette) |
| 5821 | `ResetPalFireFlower` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-resetpalfireflower) |
| 5824 | `ResetPalStar` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-resetpalstar) |
| 5830 | `ExitDeath` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitdeath) |
| 5835 | `FlagpoleSlide` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagpoleslide) |
| 5847 | `SlidePlayer` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-slideplayer) |
| 5848 | `NoFPObj` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nofpobj) |
| 5853 | `Hidden1UpCoinAmts` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hidden1upcoinamts) |
| 5856 | `PlayerEndLevel` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerendlevel) |
| 5868 | `ChkStop` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkstop) |
| 5874 | `InCastle` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incastle) |
| 5876 | `RdyNextA` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rdynexta) |
| 5888 | `NextArea` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextarea) |
| 5895 | `ExitNA` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitna) |
| 5899 | `PlayerMovementSubs` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playermovementsubs) |
| 5907 | `SetCrouch` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setcrouch) |
| 5908 | `ProcMove` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procmove) |
| 5916 | `MoveSubs` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movesubs) |
| 5923 | `NoMoveSub` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nomovesub) |
| 5928 | `OnGroundStateSub` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ongroundstatesub) |
| 5933 | `GndMove` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gndmove) |
| 5940 | `FallingSub` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fallingsub) |
| 5947 | `JumpSwimSub` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpswimsub) |
| 5959 | `DumpFall` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dumpfall) |
| 5961 | `ProcSwim` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procswim) |
| 5969 | `LRWater` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lrwater) |
| 5972 | `LRAir` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lrair) |
| 5975 | `JSMove` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jsmove) |
| 5982 | `ExitMov1` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitmov1) |
| 5986 | `ClimbAdderLow` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climbadderlow) |
| 5988 | `ClimbAdderHigh` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climbadderhigh) |
| 5991 | `ClimbingSub` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climbingsub) |
| 6000 | `MoveOnVine` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveonvine) |
| 6019 | `ClimbFD` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climbfd) |
| 6022 | `CSetFDir` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-csetfdir) |
| 6032 | `ExitCSub` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitcsub) |
| 6033 | `InitCSTimer` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initcstimer) |
| 6039 | `JumpMForceData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpmforcedata) |
| 6042 | `FallMForceData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fallmforcedata) |
| 6045 | `PlayerYSpdData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playeryspddata) |
| 6048 | `InitMForceData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initmforcedata) |
| 6051 | `MaxLeftXSpdData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-maxleftxspddata) |
| 6054 | `MaxRightXSpdData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-maxrightxspddata) |
| 6058 | `FrictionData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-frictiondata) |
| 6061 | `Climb_Y_SpeedData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climb_y_speeddata) |
| 6064 | `Climb_Y_MForceData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climb_y_mforcedata) |
| 6067 | `PlayerPhysicsSub` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerphysicssub) |
| 6079 | `ProcClimb` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procclimb) |
| 6086 | `SetCAnim` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setcanim) |
| 6089 | `CheckForJumping` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforjumping) |
| 6097 | `NoJump` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nojump) |
| 6099 | `ProcJumping` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procjumping) |
| 6109 | `InitJS` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initjs) |
| 6133 | `ChkWtr` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkwtr) |
| 6141 | `GetYPhy` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getyphy) |
| 6159 | `PJumpSnd` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pjumpsnd) |
| 6163 | `SJumpSnd` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sjumpsnd) |
| 6164 | `X_Physics` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-x_physics) |
| 6172 | `ProcPRun` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procprun) |
| 6184 | `ChkRFast` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkrfast) |
| 6191 | `FastXSp` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fastxsp) |
| 6193 | `SetRTmr` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setrtmr) |
| 6195 | `GetXPhy` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getxphy) |
| 6201 | `GetXPhy2` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getxphy2) |
| 6213 | `ExitPhy` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitphy) |
| 6217 | `PlayerAnimTmrData` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playeranimtmrdata) |
| 6220 | `GetPlayerAnimSpeed` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getplayeranimspeed) |
| 6229 | `ChkSkid` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkskid) |
| 6236 | `SetRunSpd` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setrunspd) |
| 6238 | `ProcSkid` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procskid) |
| 6246 | `SetAnimSpd` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setanimspd) |
| 6252 | `ImposeFriction` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-imposefriction) |
| 6260 | `JoypFrict` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-joypfrict) |
| 6262 | `LeftFrict` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-leftfrict) |
| 6274 | `RghtFrict` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rghtfrict) |
| 6285 | `XSpdSign` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xspdsign) |
| 6290 | `SetAbsSpd` | T23 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setabsspd) |
| 6298 | `ProcFireball_Bubble` | T20: `src/game/fireball/fireball_spawn.c` | audited; revalidation required | [D1 snapshot; current body changed](m2-t24-s1-full-node-census.md#node-procfireball_bubble) |
| 6330 | `ProcFireballs` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procfireballs) |
| 6336 | `ProcAirBubbles` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procairbubbles) |
| 6340 | `BublLoop` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bublloop) |
| 6347 | `BublExit` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bublexit) |
| 6349 | `FireballXSpdData` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fireballxspddata) |
| 6352 | `FireballObjCore` | T20/T16: `src/game/fireball/fireball_core.c` | audited; revalidation required | [Changed C owner; prior partial evidence](m2-t24-s1-full-node-census.md#node-fireballobjcore) |
| 6380 | `RunFB` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runfb) |
| 6401 | `EraseFB` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-erasefb) |
| 6403 | `NoFBall` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nofball) |
| 6405 | `FireballExplosion` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fireballexplosion) |
| 6409 | `BubbleCheck` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bubblecheck) |
| 6419 | `SetupBubble` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupbubble) |
| 6425 | `PosBubl` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-posbubl) |
| 6440 | `MoveBubl` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movebubl) |
| 6450 | `Y_Bubl` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-y_bubl) |
| 6451 | `ExitBubl` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitbubl) |
| 6453 | `Bubble_MForceData` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bubble_mforcedata) |
| 6456 | `BubbleTimerData` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bubbletimerdata) |
| 6461 | `RunGameTimer` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rungametimer) |
| 6486 | `ResGTCtrl` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-resgtctrl) |
| 6494 | `TimeUpOn` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-timeupon) |
| 6497 | `ExGTimer` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exgtimer) |
| 6501 | `WarpZoneObject` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-warpzoneobject) |
| 6519 | `ProcessWhirlpools` | T22 responsibility; no scheduler/activation C owner found | audited; implementation missing | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-processwhirlpools) |
| 6526 | `WhLoop` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-whloop) |
| 6546 | `NextWh` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextwh) |
| 6548 | `ExitWh` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitwh) |
| 6550 | `WhirlpoolActivate` | T22 responsibility; no scheduler/activation C owner found | audited; implementation missing | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-whirlpoolactivate) |
| 6577 | `LeftWh` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-leftwh) |
| 6586 | `SetPWh` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setpwh) |
| 6587 | `WhPull` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-whpull) |
| 6598 | `FlagpoleScoreMods` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagpolescoremods) |
| 6601 | `FlagpoleScoreDigits` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagpolescoredigits) |
| 6604 | `FlagpoleRoutine` | T22 responsibility; `area.c`: object decode; `oam/flagpole_gfx.c`: start/step | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-flagpoleroutine) |
| 6635 | `SkipScore` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipscore) |
| 6636 | `GiveFPScr` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-givefpscr) |
| 6643 | `FPGfx` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fpgfx) |
| 6646 | `ExitFlagP` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitflagp) |
| 6650 | `Jumpspring_Y_PosData` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpspring_y_posdata) |
| 6653 | `JumpspringHandler` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpspringhandler) |
| 6667 | `DownJSpr` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-downjspr) |
| 6669 | `PosJSpr` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-posjspr) |
| 6682 | `BounceJS` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bouncejs) |
| 6688 | `DrawJSpr` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawjspr) |
| 6698 | `ExJSpring` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exjspring) |
| 6702 | `Setup_Vine` | T22 responsibility; `objects.c`: `mysmb_objects_start_vine`, `mysmb_objects_step_vine`; `oam/vine_gfx.c`: `mysmb_objects_draw_vine` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-setup_vine) |
| 6716 | `NextVO` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextvo) |
| 6727 | `VineHeightData` | T20 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vineheightdata) |
| 6730 | `VineObjectHandler` | T22 responsibility; `objects.c`: `mysmb_objects_start_vine`, `mysmb_objects_step_vine`; `oam/vine_gfx.c`: `mysmb_objects_draw_vine` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-vineobjecthandler) |
| 6746 | `RunVSubs` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runvsubs) |
| 6752 | `VDrawLoop` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vdrawloop) |
| 6760 | `KillVine` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killvine) |
| 6766 | `WrCMTile` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-wrcmtile) |
| 6780 | `ExitVH` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitvh) |
| 6785 | `CannonBitmasks` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cannonbitmasks) |
| 6788 | `ProcessCannons` | T22 responsibility; no scheduler/activation C owner found | audited; implementation missing | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-processcannons) |
| 6792 | `ThreeSChk` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-threeschk) |
| 6809 | `FireCannon` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firecannon) |
| 6832 | `Chk_BB` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk_bb) |
| 6840 | `Next3Slt` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-next3slt) |
| 6842 | `ExCannon` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-excannon) |
| 6846 | `BulletBillXSpdData` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bulletbillxspddata) |
| 6849 | `BulletBillHandler` | T22 responsibility; `src/game/objects.c`: `mysmb_objects_step_bullet_bills` (existing actor only, not the missing cannon scheduler) | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-bulletbillhandler) |
| 6862 | `SetupBB` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupbb) |
| 6876 | `ChkDSte` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkdste) |
| 6880 | `BBFly` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bbfly) |
| 6881 | `RunBBSubs` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runbbsubs) |
| 6886 | `KillBB` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killbb) |
| 6891 | `HammerEnemyOfsData` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hammerenemyofsdata) |
| 6895 | `HammerXSpdData` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hammerxspddata) |
| 6898 | `SpawnHammerObj` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spawnhammerobj) |
| 6904 | `SetMOfs` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setmofs) |
| 6919 | `NoHammer` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nohammer) |
| 6928 | `ProcHammerObj` | T22 responsibility; `objects.c`: `mysmb_objects_step_misc`, `mysmb_objects_step_hammer`; game OAM helper | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-prochammerobj) |
| 6952 | `SetHSpd` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sethspd) |
| 6962 | `SetHPos` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sethpos) |
| 6977 | `RunAllH` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runallh) |
| 6978 | `RunHSubs` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runhsubs) |
| 6988 | `CoinBlock` | T22 responsibility; `objects.c`: `mysmb_objects_start_jump_coin`; callers in head-bump/top-of-block paths | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-coinblock) |
| 7000 | `SetupJumpCoin` | T22 responsibility; `objects.c`: `mysmb_objects_start_jump_coin`; callers in head-bump/top-of-block paths | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-setupjumpcoin) |
| 7014 | `JCoinC` | T22 responsibility; `objects.c`: `mysmb_objects_start_jump_coin`; callers in head-bump/top-of-block paths | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-jcoinc) |
| 7025 | `FindEmptyMiscSlot` | T22 responsibility; `objects.c`: `mysmb_objects_start_jump_coin`; callers in head-bump/top-of-block paths | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-findemptymiscslot) |
| 7027 | `FMiscLoop` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fmiscloop) |
| 7033 | `UseMiscS` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-usemiscs) |
| 7038 | `MiscObjectsCore` | T22 responsibility; `objects.c`: `mysmb_objects_step_misc`, `mysmb_objects_step_hammer`; game OAM helper | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-miscobjectscore) |
| 7040 | `MiscLoop` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-miscloop) |
| 7053 | `ProcJumpCoin` | T22 responsibility; `objects.c`: `mysmb_objects_step_misc`, `mysmb_objects_step_hammer`; game OAM helper | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-procjumpcoin) |
| 7071 | `JCoinRun` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jcoinrun) |
| 7088 | `RunJCSubs` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runjcsubs) |
| 7093 | `MiscLoopBack` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-miscloopback) |
| 7100 | `CoinTallyOffsets` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cointallyoffsets) |
| 7103 | `ScoreOffsets` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-scoreoffsets) |
| 7106 | `StatusBarNybbles` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-statusbarnybbles) |
| 7109 | `GiveOneCoin` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-giveonecoin) |
| 7125 | `CoinPoints` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-coinpoints) |
| 7129 | `AddToScore` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-addtoscore) |
| 7134 | `GetSBNybbles` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getsbnybbles) |
| 7138 | `UpdateNumber` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-updatenumber) |
| 7145 | `NoZSup` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nozsup) |
| 7150 | `SetupPowerUp` | T22 responsibility; `objects.c`: `mysmb_objects_start_power_up`, `mysmb_objects_step_power_up`, `mysmb_objects_finish_power_up`; `oam/power_up_gfx.c` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-setuppowerup) |
| 7163 | `PwrUpJmp` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pwrupjmp) |
| 7175 | `StrType` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strtype) |
| 7176 | `PutBehind` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-putbehind) |
| 7184 | `PowerUpObjHandler` | T22 responsibility; `objects.c`: `mysmb_objects_start_power_up`, `mysmb_objects_step_power_up`, `mysmb_objects_finish_power_up`; `oam/power_up_gfx.c` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-powerupobjhandler) |
| 7202 | `ShroomM` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-shroomm) |
| 7206 | `GrowThePowerUp` | T22 responsibility; `objects.c`: `mysmb_objects_start_power_up`, `mysmb_objects_step_power_up`, `mysmb_objects_finish_power_up`; `oam/power_up_gfx.c` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-growthepowerup) |
| 7223 | `ChkPUSte` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkpuste) |
| 7226 | `RunPUSubs` | T22 responsibility; `objects.c`: `mysmb_objects_start_power_up`, `mysmb_objects_step_power_up`, `mysmb_objects_finish_power_up`; `oam/power_up_gfx.c` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-runpusubs) |
| 7232 | `ExitPUp` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitpup) |
| 7241 | `BlockYPosAdderData` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockyposadderdata) |
| 7244 | `PlayerHeadCollision` | T22 responsibility; `objects.c`: `mysmb_objects_start_head_bump`, `mysmb_objects_start_brick_chunks`, helpers | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-playerheadcollision) |
| 7251 | `DBlockSte` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dblockste) |
| 7265 | `ChkBrick` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkbrick) |
| 7274 | `StartBTmr` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-startbtmr) |
| 7279 | `ContBTmr` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-contbtmr) |
| 7282 | `PutOldMT` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-putoldmt) |
| 7283 | `PutMTileB` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-putmtileb) |
| 7297 | `SmallBP` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-smallbp) |
| 7298 | `BigBP` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bigbp) |
| 7308 | `Unbreak` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-unbreak) |
| 7309 | `InvOBit` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-invobit) |
| 7316 | `InitBlock_XY_Pos` | T22 responsibility; `objects.c`: `mysmb_objects_start_head_bump`, `mysmb_objects_start_brick_chunks`, helpers | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-initblock_xy_pos) |
| 7332 | `BumpBlock` | T22 responsibility; `objects.c`: `mysmb_objects_start_head_bump`, `mysmb_objects_start_brick_chunks`, helpers | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-bumpblock) |
| 7349 | `BlockCode` | T22 responsibility; `objects.c`: metatile classifiers and `mysmb_objects_power_up_for_block` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-blockcode) |
| 7363 | `MushFlowerBlock` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mushflowerblock) |
| 7367 | `StarBlock` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-starblock) |
| 7371 | `ExtraLifeMushBlock` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-extralifemushblock) |
| 7376 | `VineBlock` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vineblock) |
| 7381 | `ExitBlockChk` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitblockchk) |
| 7386 | `BrickQBlockMetatiles` | T22 responsibility; `objects.c`: metatile classifiers and `mysmb_objects_power_up_for_block` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-brickqblockmetatiles) |
| 7393 | `BlockBumpedChk` | T22 responsibility; `objects.c`: metatile classifiers and `mysmb_objects_power_up_for_block` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-blockbumpedchk) |
| 7395 | `BumpChkLoop` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bumpchkloop) |
| 7400 | `MatchBump` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-matchbump) |
| 7404 | `BrickShatter` | T22 responsibility; `objects.c`: `mysmb_objects_start_head_bump`, `mysmb_objects_start_brick_chunks`, helpers | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-brickshatter) |
| 7420 | `CheckTopOfBlock` | T22 responsibility; `objects.c`: `mysmb_objects_check_top_of_block`, `mysmb_objects_collect_coin`, `mysmb_objects_start_brick_chunks` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-checktopofblock) |
| 7437 | `TopEx` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-topex) |
| 7441 | `SpawnBrickChunks` | T22 responsibility; `objects.c`: `mysmb_objects_check_top_of_block`, `mysmb_objects_collect_coin`, `mysmb_objects_start_brick_chunks` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-spawnbrickchunks) |
| 7468 | `BlockObjectsCore` | T22 responsibility; `objects.c`: `mysmb_objects_step_blocks`; `area.c`: `mysmb_area_apply_block_replacements` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-blockobjectscore) |
| 7500 | `ChkTop` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chktop) |
| 7506 | `BouncingBlockHandler` | T22 responsibility; `objects.c`: `mysmb_objects_step_blocks`; `area.c`: `mysmb_area_apply_block_replacements` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-bouncingblockhandler) |
| 7519 | `KillBlock` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killblock) |
| 7520 | `UpdSte` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-updste) |
| 7527 | `BlockObjMT_Updater` | T22 responsibility; `objects.c`: `mysmb_objects_step_blocks`; `area.c`: `mysmb_area_apply_block_replacements` | mapped; evidence incomplete | [T24 historical/current owner audit](m2-t24-s1-full-node-census.md#node-blockobjmt_updater) |
| 7529 | `UpdateLoop` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-updateloop) |
| 7546 | `NextBUpd` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextbupd) |
| 7555 | `MoveEnemyHorizontally` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveenemyhorizontally) |
| 7561 | `MovePlayerHorizontally` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveplayerhorizontally) |
| 7566 | `MoveObjectHorizontally` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveobjecthorizontally) |
| 7581 | `SaveXSpd` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-savexspd) |
| 7586 | `UseAdder` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-useadder) |
| 7604 | `ExXMove` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exxmove) |
| 7611 | `MovePlayerVertically` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveplayervertically) |
| 7617 | `NoJSChk` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nojschk) |
| 7624 | `MoveD_EnemyVertically` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moved_enemyvertically) |
| 7630 | `MoveFallingPlatform` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movefallingplatform) |
| 7632 | `ContVMove` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-contvmove) |
| 7636 | `MoveRedPTroopaDown` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveredptroopadown) |
| 7640 | `MoveRedPTroopaUp` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveredptroopaup) |
| 7643 | `MoveRedPTroopa` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveredptroopa) |
| 7656 | `MoveDropPlatform` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movedropplatform) |
| 7660 | `MoveEnemySlowVert` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveenemyslowvert) |
| 7662 | `SetMdMax` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setmdmax) |
| 7667 | `MoveJ_EnemyVertically` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movej_enemyvertically) |
| 7669 | `SetHiMax` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sethimax) |
| 7670 | `SetXMoveAmt` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setxmoveamt) |
| 7678 | `MaxSpdBlockData` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-maxspdblockdata) |
| 7681 | `ResidualGravityCode` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-residualgravitycode) |
| 7685 | `ImposeGravityBlock` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-imposegravityblock) |
| 7691 | `ImposeGravitySprObj` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-imposegravitysprobj) |
| 7698 | `MovePlatformDown` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveplatformdown) |
| 7702 | `MovePlatformUp` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveplatformup) |
| 7711 | `SetDplSpd` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setdplspd) |
| 7719 | `RedPTroopaGrav` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-redptroopagrav) |
| 7729 | `ImposeGravity` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-imposegravity) |
| 7739 | `AlterYP` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-alteryp) |
| 7761 | `ChkUpM` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkupm) |
| 7784 | `ExVMove` | T22 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exvmove) |
| 7788 | `EnemiesAndLoopsCore` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemiesandloopscore) |
| 7796 | `ChkAreaTsk` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkareatsk) |
| 7801 | `ChkBowserF` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkbowserf) |
| 7807 | `ExitELCore` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitelcore) |
| 7812 | `LoopCmdWorldNumber` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loopcmdworldnumber) |
| 7815 | `LoopCmdPageNumber` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loopcmdpagenumber) |
| 7818 | `LoopCmdYPosition` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loopcmdyposition) |
| 7821 | `ExecGameLoopback` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-execgameloopback) |
| 7851 | `ProcLoopCommand` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procloopcommand) |
| 7857 | `FindLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-findloop) |
| 7875 | `IncMLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incmloop) |
| 7883 | `WrongChk` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-wrongchk) |
| 7886 | `DoLpBack` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dolpback) |
| 7888 | `InitMLp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initmlp) |
| 7891 | `InitLCmd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initlcmd) |
| 7896 | `ChkEnemyFrenzy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkenemyfrenzy) |
| 7911 | `ProcessEnemyData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-processenemydata) |
| 7918 | `CheckEndofBuffer` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkendofbuffer) |
| 7931 | `CheckRightBounds` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkrightbounds) |
| 7950 | `CheckPageCtrlRow` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkpagectrlrow) |
| 7967 | `PositionEnemyObj` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-positionenemyobj) |
| 7983 | `CheckRightExtBounds` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkrightextbounds) |
| 8006 | `CheckForEnemyGroup` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforenemygroup) |
| 8014 | `BuzzyBeetleMutate` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-buzzybeetlemutate) |
| 8020 | `StrID` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strid) |
| 8028 | `CheckFrenzyBuffer` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkfrenzybuffer) |
| 8035 | `StrFre` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strfre) |
| 8037 | `InitEnemyObject` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initenemyobject) |
| 8041 | `ExEPar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exepar) |
| 8043 | `DoGroup` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dogroup) |
| 8046 | `ParseRow0e` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-parserow0e) |
| 8064 | `NotUse` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notuse) |
| 8066 | `CheckThreeBytes` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkthreebytes) |
| 8072 | `Inc3B` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-inc3b) |
| 8073 | `Inc2B` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-inc2b) |
| 8080 | `CheckpointEnemyID` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkpointenemyid) |
| 8092 | `InitEnemyRoutines` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initenemyroutines) |
| 8158 | `NoInitCode` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noinitcode) |
| 8163 | `InitGoomba` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initgoomba) |
| 8169 | `InitPodoboo` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initpodoboo) |
| 8181 | `InitRetainerObj` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initretainerobj) |
| 8188 | `NormalXSpdData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-normalxspddata) |
| 8191 | `InitNormalEnemy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initnormalenemy) |
| 8196 | `GetESpd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getespd) |
| 8197 | `SetESpd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setespd) |
| 8202 | `InitRedKoopa` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initredkoopa) |
| 8210 | `HBroWalkingTimerData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hbrowalkingtimerdata) |
| 8213 | `InitHammerBro` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-inithammerbro) |
| 8225 | `InitHorizFlySwimEnemy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-inithorizflyswimenemy) |
| 8231 | `InitBloober` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initbloober) |
| 8234 | `SmallBBox` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-smallbbox) |
| 8239 | `InitRedPTroopa` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initredptroopa) |
| 8245 | `GetCent` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getcent) |
| 8248 | `TallBBox` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-tallbbox) |
| 8249 | `SetBBox` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setbbox) |
| 8252 | `InitVStf` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initvstf) |
| 8259 | `InitBulletBill` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initbulletbill) |
| 8268 | `InitCheepCheep` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initcheepcheep) |
| 8279 | `InitLakitu` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initlakitu) |
| 8283 | `SetupLakitu` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setuplakitu) |
| 8289 | `KillLakitu` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killlakitu) |
| 8295 | `PRDiffAdjustData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-prdiffadjustdata) |
| 8300 | `LakituAndSpinyHandler` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lakituandspinyhandler) |
| 8308 | `ChkLak` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chklak) |
| 8318 | `ChkNoEn` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chknoen) |
| 8323 | `CreateL` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-createl) |
| 8330 | `RetEOfs` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-reteofs) |
| 8331 | `ExLSHand` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exlshand) |
| 8335 | `CreateSpiny` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-createspiny) |
| 8355 | `DifLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-difloop) |
| 8376 | `UsePosv` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-useposv) |
| 8377 | `SetSpSpd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setspspd) |
| 8383 | `SpinyRte` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spinyrte) |
| 8390 | `ChpChpEx` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chpchpex) |
| 8394 | `FirebarSpinSpdData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebarspinspddata) |
| 8397 | `FirebarSpinDirData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebarspindirdata) |
| 8400 | `InitLongFirebar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initlongfirebar) |
| 8403 | `InitShortFirebar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initshortfirebar) |
| 8430 | `FlyCCXPositionData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flyccxpositiondata) |
| 8436 | `FlyCCXSpeedData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flyccxspeeddata) |
| 8441 | `FlyCCTimerData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flycctimerdata) |
| 8444 | `InitFlyingCheepCheep` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initflyingcheepcheep) |
| 8457 | `MaxCC` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-maxcc) |
| 8473 | `GSeed` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gseed) |
| 8483 | `RSeed` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rseed) |
| 8503 | `D2XPos1` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-d2xpos1) |
| 8513 | `D2XPos2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-d2xpos2) |
| 8519 | `FinCCSt` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-finccst) |
| 8529 | `InitBowser` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initbowser) |
| 8551 | `DuplicateEnemyObj` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-duplicateenemyobj) |
| 8553 | `FSLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fsloop) |
| 8569 | `FlmEx` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flmex) |
| 8573 | `FlameYPosData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flameyposdata) |
| 8576 | `FlameYMFAdderData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flameymfadderdata) |
| 8579 | `InitBowserFlame` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initbowserflame) |
| 8597 | `SetFrT` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfrt) |
| 8604 | `PutAtRightExtent` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-putatrightextent) |
| 8615 | `SpawnFromMouth` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spawnfrommouth) |
| 8635 | `SetMF` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setmf) |
| 8640 | `FinishFlame` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-finishflame) |
| 8653 | `FireworksXPosData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fireworksxposdata) |
| 8656 | `FireworksYPosData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fireworksyposdata) |
| 8659 | `InitFireworks` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initfireworks) |
| 8666 | `StarFChk` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-starfchk) |
| 8697 | `ExitFWk` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitfwk) |
| 8701 | `Bitmasks` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bitmasks) |
| 8704 | `Enemy17YPosData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemy17yposdata) |
| 8707 | `SwimCC_IDData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-swimcc_iddata) |
| 8710 | `BulletBillCheepCheep` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bulletbillcheepcheep) |
| 8722 | `ChkW2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkw2) |
| 8726 | `Get17ID` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-get17id) |
| 8730 | `Set17ID` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-set17id) |
| 8736 | `GetRBit` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getrbit) |
| 8738 | `ChkRBit` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkrbit) |
| 8746 | `AddFBit` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-addfbit) |
| 8755 | `DoBulletBills` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dobulletbills) |
| 8757 | `BB_SLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bb_sloop) |
| 8765 | `ExF17` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exf17) |
| 8767 | `FireBulletBill` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebulletbill) |
| 8780 | `HandleGroupEnemies` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlegroupenemies) |
| 8792 | `PullID` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pullid) |
| 8793 | `SnglID` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-snglid) |
| 8798 | `SetYGp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setygp) |
| 8808 | `CntGrp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cntgrp) |
| 8809 | `GrLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-grloop) |
| 8810 | `GSltLp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gsltlp) |
| 8835 | `NextED` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nexted) |
| 8839 | `InitPiranhaPlant` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initpiranhaplant) |
| 8855 | `InitEnemyFrenzy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initenemyfrenzy) |
| 8872 | `NoFrenzyCode` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nofrenzycode) |
| 8877 | `EndFrenzy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endfrenzy) |
| 8879 | `LakituChk` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lakituchk) |
| 8884 | `NextFSlot` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextfslot) |
| 8893 | `InitJumpGPTroopa` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initjumpgptroopa) |
| 8898 | `TallBBox2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-tallbbox2) |
| 8899 | `SetBBox2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setbbox2) |
| 8904 | `InitBalPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initbalplatform) |
| 8911 | `AlignP` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-alignp) |
| 8917 | `SetBPA` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setbpa) |
| 8925 | `InitDropPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initdropplatform) |
| 8932 | `InitHoriPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-inithoriplatform) |
| 8939 | `InitVertPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initvertplatform) |
| 8947 | `SetYO` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setyo) |
| 8955 | `CommonPlatCode` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-commonplatcode) |
| 8957 | `SPBBox` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spbbox) |
| 8964 | `CasPBB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-caspbb) |
| 8969 | `LargeLiftUp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-largeliftup) |
| 8973 | `LargeLiftDown` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-largeliftdown) |
| 8976 | `LargeLiftBBox` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-largeliftbbox) |
| 8981 | `PlatLiftUp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platliftup) |
| 8990 | `PlatLiftDown` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platliftdown) |
| 8998 | `CommonSmallLift` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-commonsmalllift) |
| 9007 | `PlatPosDataLow` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platposdatalow) |
| 9010 | `PlatPosDataHigh` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platposdatahigh) |
| 9013 | `PosPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-posplatform) |
| 9025 | `EndOfEnemyInitCode` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endofenemyinitcode) |
| 9030 | `RunEnemyObjectsCore` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runenemyobjectscore) |
| 9038 | `JmpEO` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jmpeo) |
| 9080 | `NoRunCode` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noruncode) |
| 9085 | `RunRetainerObj` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runretainerobj) |
| 9092 | `RunNormalEnemies` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runnormalenemies) |
| 9105 | `SkipMove` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipmove) |
| 9107 | `EnemyMovementSubs` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemymovementsubs) |
| 9135 | `NoMoveCode` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nomovecode) |
| 9140 | `RunBowserFlame` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runbowserflame) |
| 9150 | `RunFirebarObj` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runfirebarobj) |
| 9156 | `RunSmallPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runsmallplatform) |
| 9168 | `RunLargePlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runlargeplatform) |
| 9176 | `SkipPT` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skippt) |
| 9182 | `LargePlatformSubroutines` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-largeplatformsubroutines) |
| 9198 | `EraseEnemyObject` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-eraseenemyobject) |
| 9212 | `MovePodoboo` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movepodoboo) |
| 9224 | `PdbM` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pdbm) |
| 9229 | `HammerThrowTmrData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hammerthrowtmrdata) |
| 9232 | `XSpeedAdderData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xspeedadderdata) |
| 9235 | `RevivedXSpeed` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-revivedxspeed) |
| 9238 | `ProcHammerBro` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-prochammerbro) |
| 9243 | `ChkJH` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkjh) |
| 9260 | `DecHT` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decht) |
| 9263 | `HammerBroJumpLData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hammerbrojumpldata) |
| 9266 | `HammerBroJumpCode` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hammerbrojumpcode) |
| 9285 | `SetHJ` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sethj) |
| 9295 | `HJump` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hjump) |
| 9301 | `MoveHammerBroXDir` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movehammerbroxdir) |
| 9307 | `Shimmy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-shimmy) |
| 9316 | `SetShim` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setshim) |
| 9318 | `MoveNormalEnemy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movenormalenemy) |
| 9336 | `FallE` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-falle) |
| 9347 | `MEHor` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mehor) |
| 9349 | `SlowM` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-slowm) |
| 9350 | `SteadM` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-steadm) |
| 9355 | `AddHS` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-addhs) |
| 9363 | `ReviveStunned` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-revivestunned) |
| 9377 | `SetRSpd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setrspd) |
| 9381 | `MoveDefeatedEnemy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movedefeatedenemy) |
| 9385 | `ChkKillGoomba` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkkillgoomba) |
| 9392 | `NKGmba` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nkgmba) |
| 9396 | `MoveJumpingEnemy` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movejumpingenemy) |
| 9402 | `ProcMoveRedPTroopa` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procmoveredptroopa) |
| 9414 | `NoIncPT` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noincpt) |
| 9416 | `MoveRedPTUpOrDown` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveredptupordown) |
| 9421 | `MovPTDwn` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movptdwn) |
| 9427 | `MoveFlyGreenPTroopa` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveflygreenptroopa) |
| 9438 | `YSway` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ysway) |
| 9443 | `NoMGPT` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nomgpt) |
| 9445 | `XMoveCntr_GreenPTroopa` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xmovecntr_greenptroopa) |
| 9448 | `XMoveCntr_Platform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xmovecntr_platform) |
| 9460 | `NoIncXM` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noincxm) |
| 9461 | `IncPXM` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incpxm) |
| 9463 | `DecSeXM` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decsexm) |
| 9468 | `MoveWithXMCntrs` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movewithxmcntrs) |
| 9481 | `XMRight` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xmright) |
| 9490 | `BlooberBitmasks` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blooberbitmasks) |
| 9493 | `MoveBloober` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movebloober) |
| 9506 | `FBLeft` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fbleft) |
| 9510 | `SBMDir` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sbmdir) |
| 9512 | `BlooberSwim` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blooberswim) |
| 9520 | `SwimX` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-swimx) |
| 9532 | `LeftSwim` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-leftswim) |
| 9542 | `MoveDefeatedBloober` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movedefeatedbloober) |
| 9545 | `ProcSwimmingB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procswimmingb) |
| 9565 | `BSwimE` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bswime) |
| 9567 | `SlowSwim` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-slowswim) |
| 9579 | `NoSSw` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nossw) |
| 9581 | `ChkForFloatdown` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforfloatdown) |
| 9585 | `Floatdown` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-floatdown) |
| 9590 | `NoFD` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nofd) |
| 9592 | `ChkNearPlayer` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chknearplayer) |
| 9603 | `MoveBulletBill` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movebulletbill) |
| 9608 | `NotDefB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notdefb) |
| 9616 | `SwimCCXMoveData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-swimccxmovedata) |
| 9620 | `MoveSwimmingCheepCheep` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveswimmingcheepcheep) |
| 9625 | `CCSwim` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ccswim) |
| 9660 | `CCSwimUpwards` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ccswimupwards) |
| 9671 | `ChkSwimYPos` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkswimypos) |
| 9682 | `YPDiff` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ypdiff) |
| 9686 | `ExSwCC` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exswcc) |
| 9703 | `FirebarPosLookupTbl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebarposlookuptbl) |
| 9716 | `FirebarMirrorData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebarmirrordata) |
| 9719 | `FirebarTblOffsets` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebartbloffsets) |
| 9723 | `FirebarYPos` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebarypos) |
| 9726 | `ProcFirebar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procfirebar) |
| 9737 | `SusFbar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-susfbar) |
| 9745 | `SkpFSte` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skpfste) |
| 9748 | `SetupGFB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupgfb) |
| 9766 | `SetMFbar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setmfbar) |
| 9769 | `DrawFbar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawfbar) |
| 9778 | `NextFbar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextfbar) |
| 9782 | `SkipFBar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipfbar) |
| 9784 | `DrawFirebar_Collision` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawfirebar_collision) |
| 9793 | `AddHA` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-addha) |
| 9803 | `SubtR1` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-subtr1) |
| 9805 | `ChkFOfs` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfofs) |
| 9809 | `VAHandl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vahandl) |
| 9817 | `AddVA` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-addva) |
| 9819 | `SetVFbr` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setvfbr) |
| 9822 | `FirebarCollision` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebarcollision) |
| 9838 | `AdjSm` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-adjsm) |
| 9844 | `BigJp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bigjp) |
| 9845 | `FBCLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fbcloop) |
| 9851 | `ChkVFBD` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkvfbd) |
| 9866 | `ChkFBCl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfbcl) |
| 9868 | `Chk2Ofs` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk2ofs) |
| 9877 | `ChgSDir` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chgsdir) |
| 9882 | `SetSDir` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setsdir) |
| 9889 | `NoColFB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nocolfb) |
| 9896 | `GetFirebarPosition` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getfirebarposition) |
| 9904 | `GetHAdder` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gethadder) |
| 9922 | `GetVAdder` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getvadder) |
| 9941 | `PRandomSubtracter` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-prandomsubtracter) |
| 9944 | `FlyCCBPriority` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flyccbpriority) |
| 9947 | `MoveFlyingCheepCheep` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveflyingcheepcheep) |
| 9954 | `FlyCC` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flycc) |
| 9971 | `AddCCF` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-addccf) |
| 9982 | `BPGet` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bpget) |
| 9990 | `LakituDiffAdj` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lakitudiffadj) |
| 9993 | `MoveLakitu` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movelakitu) |
| 9998 | `ChkLS` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkls) |
| 10005 | `Fr12S` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fr12s) |
| 10008 | `LdLDa` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ldlda) |
| 10013 | `SetLSpd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setlspd) |
| 10024 | `SetLMov` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setlmov) |
| 10027 | `PlayerLakituDiff` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerlakitudiff) |
| 10037 | `ChkLakDif` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chklakdif) |
| 10053 | `SetLMovD` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setlmovd) |
| 10055 | `ChkPSpeed` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkpspeed) |
| 10073 | `ChkSpinyO` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkspinyo) |
| 10078 | `ChkEmySpd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkemyspd) |
| 10081 | `SubDifAdj` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-subdifadj) |
| 10083 | `SPixelLak` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spixellak) |
| 10087 | `ExMoveLak` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exmovelak) |
| 10092 | `BridgeCollapseData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridgecollapsedata) |
| 10098 | `BridgeCollapse` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridgecollapse) |
| 10111 | `SetM2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setm2) |
| 10116 | `MoveD_Bowser` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moved_bowser) |
| 10120 | `RemoveBridge` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-removebridge) |
| 10152 | `NoBFall` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nobfall) |
| 10156 | `PRandomRange` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-prandomrange) |
| 10159 | `RunBowser` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runbowser) |
| 10167 | `KillAllEnemies` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killallenemies) |
| 10169 | `KillLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killloop) |
| 10176 | `BowserControl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bowsercontrol) |
| 10182 | `ChkMouth` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkmouth) |
| 10185 | `FeetTmr` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-feettmr) |
| 10192 | `ResetMDr` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-resetmdr) |
| 10197 | `B_FaceP` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-b_facep) |
| 10211 | `GetPRCmp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getprcmp) |
| 10222 | `GetDToO` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getdtoo) |
| 10237 | `CompDToO` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-compdtoo) |
| 10240 | `HammerChk` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hammerchk) |
| 10250 | `SetHmrTmr` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sethmrtmr) |
| 10258 | `SkipToFB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skiptofb) |
| 10259 | `MakeBJump` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-makebjump) |
| 10265 | `ChkFireB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfireb) |
| 10270 | `SpawnFBr` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spawnfbr) |
| 10283 | `SetFBTmr` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfbtmr) |
| 10289 | `BowserGfxHandler` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bowsergfxhandler) |
| 10296 | `CopyFToR` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-copyftor) |
| 10321 | `ExBGfxH` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exbgfxh) |
| 10323 | `ProcessBowserHalf` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-processbowserhalf) |
| 10337 | `FlameTimerData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flametimerdata) |
| 10340 | `SetFlameTimer` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setflametimer) |
| 10347 | `ExFl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exfl) |
| 10349 | `ProcBowserFlame` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procbowserflame) |
| 10356 | `SFlmX` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sflmx) |
| 10374 | `SetGfxF` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setgfxf) |
| 10384 | `FlmeAt` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flmeat) |
| 10388 | `DrawFlameLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawflameloop) |
| 10417 | `M3FOfs` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-m3fofs) |
| 10423 | `M2FOfs` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-m2fofs) |
| 10429 | `M1FOfs` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-m1fofs) |
| 10434 | `ExFlmeD` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exflmed) |
| 10438 | `RunFireworks` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runfireworks) |
| 10447 | `SetupExpl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupexpl) |
| 10457 | `FireworksSoundScore` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fireworkssoundscore) |
| 10468 | `StarFlagYPosAdder` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-starflagyposadder) |
| 10471 | `StarFlagXPosAdder` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-starflagxposadder) |
| 10474 | `StarFlagTileData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-starflagtiledata) |
| 10477 | `RunStarFlagObj` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runstarflagobj) |
| 10491 | `GameTimerFireworks` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gametimerfireworks) |
| 10503 | `SetFWC` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfwc) |
| 10506 | `IncrementSFTask1` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incrementsftask1) |
| 10509 | `StarFlagExit` | T19/T18: `src/game/endgame_objects.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-starflagexit) |
| 10512 | `AwardGameTimerPoints` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-awardgametimerpoints) |
| 10522 | `NoTTick` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nottick) |
| 10529 | `EndAreaPoints` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endareapoints) |
| 10534 | `ELPGive` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-elpgive) |
| 10543 | `RaiseFlagSetoffFWorks` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-raiseflagsetofffworks) |
| 10549 | `SetoffF` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setofff) |
| 10555 | `DrawStarFlag` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawstarflag) |
| 10559 | `DSFLoop` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dsfloop) |
| 10580 | `DrawFlagSetTimer` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawflagsettimer) |
| 10585 | `IncrementSFTask2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incrementsftask2) |
| 10589 | `DelayToAreaEnd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-delaytoareaend) |
| 10596 | `StarFlagExit2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-starflagexit2) |
| 10602 | `MovePiranhaPlant` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movepiranhaplant) |
| 10619 | `ChkPlayerNearPipe` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkplayernearpipe) |
| 10624 | `ReversePlantSpeed` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-reverseplantspeed) |
| 10632 | `SetupToMovePPlant` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setuptomovepplant) |
| 10638 | `RiseFallPiranhaPlant` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-risefallpiranhaplant) |
| 10656 | `PutinPipe` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-putinpipe) |
| 10664 | `FirebarSpin` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebarspin) |
| 10677 | `SpinCounterClockwise` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spincounterclockwise) |
| 10692 | `BalancePlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-balanceplatform) |
| 10697 | `DoBPl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dobpl) |
| 10701 | `CheckBalPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkbalplatform) |
| 10709 | `ChkForFall` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforfall) |
| 10720 | `MakePlatformFall` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-makeplatformfall) |
| 10723 | `ChkOtherForFall` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkotherforfall) |
| 10733 | `ChkToMoveBalPlat` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chktomovebalplat) |
| 10750 | `ColFlg` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-colflg) |
| 10752 | `PlatUp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platup) |
| 10754 | `PlatSt` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platst) |
| 10756 | `PlatDn` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platdn) |
| 10758 | `DoOtherPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dootherplatform) |
| 10771 | `DrawEraseRope` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-draweraserope) |
| 10796 | `EraseR1` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-eraser1) |
| 10800 | `OtherRope` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-otherrope) |
| 10819 | `EraseR2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-eraser2) |
| 10822 | `EndRp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endrp) |
| 10828 | `ExitRp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitrp) |
| 10831 | `SetupPlatformRope` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupplatformrope) |
| 10840 | `GetLRp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getlrp) |
| 10857 | `GetHRp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gethrp) |
| 10883 | `ExPRp` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exprp) |
| 10885 | `InitPlatformFall` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initplatformfall) |
| 10898 | `StopPlatforms` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-stopplatforms) |
| 10904 | `PlatformFall` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platformfall) |
| 10916 | `ExPF` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-expf) |
| 10921 | `YMovingPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ymovingplatform) |
| 10933 | `SkipIY` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipiy) |
| 10935 | `ChkYCenterPos` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkycenterpos) |
| 10941 | `YMDown` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ymdown) |
| 10943 | `ChkYPCollision` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkypcollision) |
| 10947 | `ExYPl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exypl) |
| 10952 | `XMovingPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xmovingplatform) |
| 10959 | `PositionPlayerOnHPlat` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-positionplayeronhplat) |
| 10969 | `PPHSubt` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pphsubt) |
| 10970 | `SetPVar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setpvar) |
| 10973 | `ExXMP` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exxmp) |
| 10977 | `DropPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dropplatform) |
| 10982 | `ExDPl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exdpl) |
| 10987 | `RightPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rightplatform) |
| 10995 | `ExRPl` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exrpl) |
| 10999 | `MoveLargeLiftPlat` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movelargeliftplat) |
| 11003 | `MoveSmallPlatform` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movesmallplatform) |
| 11007 | `MoveLiftPlatforms` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveliftplatforms) |
| 11019 | `ChkSmallPlatCollision` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chksmallplatcollision) |
| 11023 | `ExLiftP` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exliftp) |
| 11031 | `OffscreenBoundsCheck` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-offscreenboundscheck) |
| 11041 | `LimitB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-limitb) |
| 11042 | `ExtendLB` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-extendlb) |
| 11074 | `TooFar` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-toofar) |
| 11075 | `ExScrnBd` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exscrnbd) |
| 11085 | `FireballEnemyCollision` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-fireballenemycollision) |
| 11101 | `FireballEnemyCDLoop` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-fireballenemycdloop) |
| 11115 | `GoombaDie` | T17: `src/game/world/collision.c` | audited; mismatch | [T24 S1: D2](m2-t24-s1-node-verification.md#node-goombadie) |
| 11120 | `NotGoomba` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-notgoomba) |
| 11135 | `NoFToECol` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-noftoecol) |
| 11141 | `ExitFBallEnemy` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-exitfballenemy) |
| 11145 | `BowserIdentities` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-bowseridentities) |
| 11148 | `HandleEnemyFBallCol` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-handleenemyfballcol) |
| 11160 | `ChkBuzzyBeetle` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-chkbuzzybeetle) |
| 11167 | `HurtBowser` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-hurtbowser) |
| 11182 | `SetDBSte` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-setdbste) |
| 11189 | `ChkOtherEnemies` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-chkotherenemies) |
| 11197 | `ShellOrBlockDefeat` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-shellorblockdefeat) |
| 11204 | `StnE` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-stne) |
| 11215 | `GoombaPoints` | T17: `src/game/world/collision.c` | audited; mismatch | [T24 S1: D2](m2-t24-s1-node-verification.md#node-goombapoints) |
| 11220 | `EnemySmackScore` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-enemysmackscore) |
| 11224 | `ExHCF` | T17: `src/game/world/collision.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-exhcf) |
| 11228 | `PlayerHammerCollision` | T17: `src/game/objects.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-playerhammercollision) |
| 11256 | `ClHCol` | T17: `src/game/objects.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-clhcol) |
| 11258 | `ExPHC` | T17: `src/game/objects.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-exphc) |
| 11262 | `HandlePowerUpCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlepowerupcollision) |
| 11279 | `Shroom_Flower_PUp` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-shroom_flower_pup) |
| 11292 | `SetFor1Up` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfor1up) |
| 11297 | `UpToSuper` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-uptosuper) |
| 11302 | `UpToFiery` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-uptofiery) |
| 11305 | `NoPUp` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nopup) |
| 11309 | `ResidualXSpdData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-residualxspddata) |
| 11312 | `KickedShellXSpdData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-kickedshellxspddata) |
| 11315 | `DemotedKoopaXSpdData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-demotedkoopaxspddata) |
| 11318 | `PlayerEnemyCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerenemycollision) |
| 11339 | `NoPECol` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nopecol) |
| 11341 | `CheckForPUpCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforpupcollision) |
| 11346 | `EColl` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ecoll) |
| 11350 | `KickedShellPtsData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-kickedshellptsdata) |
| 11353 | `HandlePECollisions` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlepecollisions) |
| 11398 | `KSPts` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-kspts) |
| 11399 | `ExPEC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-expec) |
| 11401 | `ChkForPlayerInjury` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforplayerinjury) |
| 11405 | `ChkInj` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkinj) |
| 11413 | `ChkETmrs` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chketmrs) |
| 11421 | `TInjE` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-tinje) |
| 11426 | `InjurePlayer` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-injureplayer) |
| 11430 | `ForceInjury` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-forceinjury) |
| 11440 | `SetKRout` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setkrout) |
| 11441 | `SetPRout` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setprout) |
| 11448 | `ExInjColRoutines` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exinjcolroutines) |
| 11452 | `KillPlayer` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killplayer) |
| 11461 | `StompedEnemyPtsData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-stompedenemyptsdata) |
| 11464 | `EnemyStomped` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemystomped) |
| 11490 | `EnemyStompedPts` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemystompedpts) |
| 11506 | `ChkForDemoteKoopa` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfordemotekoopa) |
| 11521 | `RevivalRateData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-revivalratedata) |
| 11524 | `HandleStompedShellE` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlestompedshelle) |
| 11536 | `SBnce` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sbnce) |
| 11540 | `ChkEnemyFaceRight` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkenemyfaceright) |
| 11545 | `LInj` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-linj) |
| 11549 | `EnemyFacePlayer` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemyfaceplayer) |
| 11554 | `SFcRt` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sfcrt) |
| 11558 | `SetupFloateyNumber` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupfloateynumber) |
| 11566 | `ExSFN` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exsfn) |
| 11571 | `SetBitsMask` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setbitsmask) |
| 11574 | `ClearBitsMask` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clearbitsmask) |
| 11577 | `EnemiesCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemiescollision) |
| 11595 | `ECLoop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ecloop) |
| 11629 | `YesEC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-yesec) |
| 11632 | `NoEnemyCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noenemycollision) |
| 11637 | `ReadyNextEnemy` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-readynextenemy) |
| 11644 | `ExitECRoutine` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitecroutine) |
| 11648 | `ProcEnemyCollisions` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procenemycollisions) |
| 11667 | `ShellCollisions` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-shellcollisions) |
| 11680 | `ExitProcessEColl` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitprocessecoll) |
| 11683 | `ProcSecondEnemyColl` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procsecondenemycoll) |
| 11701 | `MoveEOfs` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveeofs) |
| 11707 | `EnemyTurnAround` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemyturnaround) |
| 11721 | `RXSpd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rxspd) |
| 11729 | `ExTA` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exta) |
| 11734 | `LargePlatformCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-largeplatformcollision) |
| 11748 | `ChkForPlayerC_LargeP` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforplayerc_largep) |
| 11762 | `ExLPC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exlpc) |
| 11768 | `SmallPlatformCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-smallplatformcollision) |
| 11777 | `ChkSmallPlatLoop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chksmallplatloop) |
| 11788 | `MoveBoundBox` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveboundbox) |
| 11799 | `ExSPC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exspc) |
| 11804 | `ProcSPlatCollisions` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procsplatcollisions) |
| 11807 | `ProcLPlatCollisions` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-proclplatcollisions) |
| 11818 | `ChkForTopCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfortopcollision) |
| 11834 | `SetCollisionFlag` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setcollisionflag) |
| 11841 | `PlatformSideCollisions` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platformsidecollisions) |
| 11855 | `SideC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sidec) |
| 11856 | `NoSideC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nosidec) |
| 11861 | `PlayerPosSPlatData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerpossplatdata) |
| 11864 | `PositionPlayerOnS_Plat` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-positionplayerons_plat) |
| 11871 | `PositionPlayerOnVPlat` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-positionplayeronvplat) |
| 11888 | `ExPlPos` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-explpos) |
| 11892 | `CheckPlayerVertical` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkplayervertical) |
| 11901 | `ExCPV` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-excpv) |
| 11905 | `GetEnemyBoundBoxOfs` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getenemyboundboxofs) |
| 11908 | `GetEnemyBoundBoxOfsArg` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getenemyboundboxofsarg) |
| 11924 | `PlayerBGUpperExtent` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerbgupperextent) |
| 11927 | `PlayerBGCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerbgcollision) |
| 11942 | `SetFallS` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfalls) |
| 11943 | `SetPSte` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setpste) |
| 11944 | `ChkOnScr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkonscr) |
| 11952 | `ExPBGCol` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-expbgcol) |
| 11954 | `ChkCollSize` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkcollsize) |
| 11964 | `GBBAdr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gbbadr) |
| 11971 | `HeadChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-headchk) |
| 11992 | `SolidOrClimb` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-solidorclimb) |
| 11997 | `NYSpd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nyspd) |
| 12000 | `DoFootCheck` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dofootcheck) |
| 12019 | `AwardTouchedCoin` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-awardtouchedcoin) |
| 12022 | `ChkFootMTile` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfootmtile) |
| 12030 | `ContChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-contchk) |
| 12040 | `LandPlyr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-landplyr) |
| 12049 | `InitSteP` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initstep) |
| 12052 | `DoPlayerSideCheck` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doplayersidecheck) |
| 12059 | `SideCheckLoop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sidecheckloop) |
| 12075 | `BHalf` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bhalf) |
| 12086 | `ExSCH` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exsch) |
| 12088 | `CheckSideMTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checksidemtiles) |
| 12094 | `ContSChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-contschk) |
| 12101 | `ChkPBtm` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkpbtm) |
| 12111 | `PipeDwnS` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pipedwns) |
| 12115 | `PlyrPipe` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-plyrpipe) |
| 12124 | `SetCATmr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setcatmr) |
| 12126 | `ChkGERtn` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkgertn) |
| 12140 | `StopPlayerMove` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-stopplayermove) |
| 12142 | `ExCSM` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-excsm) |
| 12144 | `AreaChangeTimerData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areachangetimerdata) |
| 12147 | `HandleCoinMetatile` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlecoinmetatile) |
| 12152 | `HandleAxeMetatile` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handleaxemetatile) |
| 12159 | `ErACM` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-eracm) |
| 12169 | `ClimbXPosAdder` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climbxposadder) |
| 12172 | `ClimbPLocAdder` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climbplocadder) |
| 12175 | `FlagpoleYPosData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagpoleyposdata) |
| 12178 | `HandleClimbing` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handleclimbing) |
| 12184 | `ExHC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exhc) |
| 12186 | `ChkForFlagpole` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforflagpole) |
| 12192 | `FlagpoleCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagpolecollision) |
| 12212 | `ChkFlagpoleYPosLoop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkflagpoleyposloop) |
| 12217 | `MtchF` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mtchf) |
| 12218 | `RunFR` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runfr) |
| 12222 | `VineCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vinecollision) |
| 12231 | `PutPlayerOnVine` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-putplayeronvine) |
| 12244 | `SetVXPl` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setvxpl) |
| 12259 | `ExPVne` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-expvne) |
| 12263 | `ChkInvisibleMTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkinvisiblemtiles) |
| 12267 | `ExCInvT` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-excinvt) |
| 12273 | `ChkForLandJumpSpring` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforlandjumpspring) |
| 12284 | `ExCJSp` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-excjsp) |
| 12286 | `ChkJumpspringMetatiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkjumpspringmetatiles) |
| 12292 | `JSFnd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jsfnd) |
| 12293 | `NoJSFnd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nojsfnd) |
| 12295 | `HandlePipeEntry` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlepipeentry) |
| 12326 | `GetWNum` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getwnum) |
| 12341 | `ExPipeE` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-expipee) |
| 12343 | `ImpedePlayerMove` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-impedeplayermove) |
| 12354 | `RImpd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rimpd) |
| 12358 | `NXSpd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nxspd) |
| 12365 | `PlatF` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-platf) |
| 12372 | `ExIPM` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exipm) |
| 12380 | `SolidMTileUpperExt` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-solidmtileupperext) |
| 12383 | `CheckForSolidMTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforsolidmtiles) |
| 12388 | `ClimbMTileUpperExt` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-climbmtileupperext) |
| 12391 | `CheckForClimbMTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforclimbmtiles) |
| 12396 | `CheckForCoinMTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforcoinmtiles) |
| 12403 | `CoinSd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-coinsd) |
| 12407 | `GetMTileAttrib` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getmtileattrib) |
| 12415 | `ExEBG` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exebg) |
| 12420 | `EnemyBGCStateData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemybgcstatedata) |
| 12423 | `EnemyBGCXSpdData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemybgcxspddata) |
| 12426 | `EnemyToBGCollisionDet` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemytobgcollisiondet) |
| 12439 | `DoIDCheckBGColl` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doidcheckbgcoll) |
| 12443 | `HBChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hbchk) |
| 12446 | `CInvu` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cinvu) |
| 12452 | `YesIn` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-yesin) |
| 12455 | `NoEToBGCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noetobgcollision) |
| 12461 | `HandleEToBGCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handleetobgcollision) |
| 12476 | `GiveOEPoints` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-giveoepoints) |
| 12480 | `ChkToStunEnemies` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chktostunenemies) |
| 12489 | `Demote` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-demote) |
| 12491 | `SetStun` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setstun) |
| 12503 | `SetWYSpd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setwyspd) |
| 12504 | `SetNotW` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setnotw) |
| 12509 | `ChkBBill` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkbbill) |
| 12515 | `NoCDirF` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nocdirf) |
| 12518 | `ExEBGChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exebgchk) |
| 12523 | `LandEnemyProperly` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-landenemyproperly) |
| 12535 | `SChkA` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-schka) |
| 12537 | `ChkLandedEnemyState` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chklandedenemystate) |
| 12552 | `SetForStn` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setforstn) |
| 12556 | `ExSteChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exstechk) |
| 12558 | `ProcEnemyDirection` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procenemydirection) |
| 12571 | `InvtD` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-invtd) |
| 12575 | `CNwCDir` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cnwcdir) |
| 12580 | `LandEnemyInitState` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-landenemyinitstate) |
| 12589 | `NMovShellFallBit` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nmovshellfallbit) |
| 12597 | `ChkForRedKoopa` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforredkoopa) |
| 12603 | `Chk2MSBSt` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk2msbst) |
| 12610 | `GetSteFromD` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getstefromd) |
| 12611 | `SetD6Ste` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setd6ste) |
| 12617 | `DoEnemySideCheck` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doenemysidecheck) |
| 12624 | `SdeCLoop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sdecloop) |
| 12632 | `NextSdeC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextsdec) |
| 12636 | `ExESdeC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exesdec) |
| 12638 | `ChkForBump_HammerBroJ` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforbump_hammerbroj) |
| 12646 | `NoBump` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nobump) |
| 12654 | `InvEnemyDir` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-invenemydir) |
| 12660 | `PlayerEnemyDiff` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerenemydiff) |
| 12671 | `EnemyLanding` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemylanding) |
| 12679 | `SubtEnemyYPos` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-subtenemyypos) |
| 12686 | `EnemyJump` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemyjump) |
| 12701 | `DoSide` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doside) |
| 12705 | `HammerBroBGColl` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hammerbrobgcoll) |
| 12711 | `KillEnemyAboveBlock` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killenemyaboveblock) |
| 12717 | `UnderHammerBro` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-underhammerbro) |
| 12726 | `NoUnderHammerBro` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nounderhammerbro) |
| 12732 | `ChkUnderEnemy` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkunderenemy) |
| 12737 | `ChkForNonSolids` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfornonsolids) |
| 12747 | `NSFnd` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nsfnd) |
| 12751 | `FireballBGCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fireballbgcollision) |
| 12772 | `ClearBounceFlag` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clearbounceflag) |
| 12777 | `InitFireballExplode` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initfireballexplode) |
| 12791 | `BoundBoxCtrlData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-boundboxctrldata) |
| 12805 | `GetFireballBoundBox` | T20/T16: `src/game/fireball/fireball_core.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-getfireballboundbox) |
| 12813 | `GetMiscBoundBox` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getmiscboundbox) |
| 12819 | `FBallB` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fballb) |
| 12822 | `GetEnemyBoundBox` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getenemyboundbox) |
| 12828 | `SmallPlatformBoundBox` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-smallplatformboundbox) |
| 12833 | `GetMaskedOffScrBits` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getmaskedoffscrbits) |
| 12844 | `CMBits` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cmbits) |
| 12850 | `LargePlatformBoundBox` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-largeplatformboundbox) |
| 12857 | `SetupEOffsetFBBox` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setupeoffsetfbbox) |
| 12866 | `MoveBoundBoxOffscreen` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveboundboxoffscreen) |
| 12878 | `BoundingBoxCore` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-boundingboxcore) |
| 12916 | `CheckRightScreenBBox` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkrightscreenbbox) |
| 12935 | `SORte` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sorte) |
| 12936 | `NoOfs` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noofs) |
| 12939 | `CheckLeftScreenBBox` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkleftscreenbbox) |
| 12948 | `SOLft` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-solft) |
| 12949 | `NoOfs2` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noofs2) |
| 12956 | `PlayerCollisionCore` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playercollisioncore) |
| 12959 | `SprObjectCollisionCore` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sprobjectcollisioncore) |
| 12964 | `CollisionCoreLoop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-collisioncoreloop) |
| 12979 | `SecondBoxVerticalChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-secondboxverticalchk) |
| 12989 | `FirstBoxGreater` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firstboxgreater) |
| 13002 | `NoCollisionFound` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nocollisionfound) |
| 13007 | `CollisionFound` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-collisionfound) |
| 13023 | `BlockBufferChk_Enemy` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbufferchk_enemy) |
| 13032 | `ResidualMiscObjectCode` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-residualmiscobjectcode) |
| 13040 | `BlockBufferChk_FBall` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbufferchk_fball) |
| 13046 | `ResJmpM` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-resjmpm) |
| 13047 | `BBChk_E` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bbchk_e) |
| 13052 | `BlockBufferAdderData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbufferadderdata) |
| 13055 | `BlockBuffer_X_Adder` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbuffer_x_adder) |
| 13061 | `BlockBuffer_Y_Adder` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbuffer_y_adder) |
| 13067 | `BlockBufferColli_Feet` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbuffercolli_feet) |
| 13070 | `BlockBufferColli_Head` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbuffercolli_head) |
| 13074 | `BlockBufferColli_Side` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbuffercolli_side) |
| 13078 | `BlockBufferCollision` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbuffercollision) |
| 13111 | `RetXC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-retxc) |
| 13112 | `RetYC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-retyc) |
| 13126 | `VineYPosAdder` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vineyposadder) |
| 13129 | `DrawVine` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawvine) |
| 13156 | `VineTL` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-vinetl) |
| 13169 | `SkpVTop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skpvtop) |
| 13170 | `ChkFTop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkftop) |
| 13177 | `NextVSp` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextvsp) |
| 13187 | `SixSpriteStacker` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sixspritestacker) |
| 13189 | `StkLp` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-stklp) |
| 13203 | `FirstSprXPos` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firstsprxpos) |
| 13206 | `FirstSprYPos` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firstsprypos) |
| 13209 | `SecondSprXPos` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-secondsprxpos) |
| 13212 | `SecondSprYPos` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-secondsprypos) |
| 13215 | `FirstSprTilenum` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firstsprtilenum) |
| 13218 | `SecondSprTilenum` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-secondsprtilenum) |
| 13221 | `HammerSprAttrib` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hammersprattrib) |
| 13224 | `DrawHammer` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawhammer) |
| 13232 | `ForceHPose` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-forcehpose) |
| 13234 | `GetHPose` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gethpose) |
| 13239 | `RenderH` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-renderh) |
| 13268 | `NoHOffscr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nohoffscr) |
| 13277 | `FlagpoleScoreNumTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagpolescorenumtiles) |
| 13284 | `FlagpoleGfxHandler` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagpolegfxhandler) |
| 13326 | `ChkFlagOffscreen` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkflagoffscreen) |
| 13335 | `MoveSixSpritesOffscreen` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movesixspritesoffscreen) |
| 13338 | `DumpSixSpr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dumpsixspr) |
| 13342 | `DumpFourSpr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dumpfourspr) |
| 13345 | `DumpThreeSpr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dumpthreespr) |
| 13348 | `DumpTwoSpr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dumptwospr) |
| 13352 | `ExitDumpSpr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitdumpspr) |
| 13357 | `DrawLargePlatform` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawlargeplatform) |
| 13374 | `ShrinkPlatform` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-shrinkplatform) |
| 13377 | `SetLast2Platform` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setlast2platform) |
| 13386 | `SetPlatformTilenum` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setplatformtilenum) |
| 13402 | `SChk2` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-schk2) |
| 13408 | `SChk3` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-schk3) |
| 13414 | `SChk4` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-schk4) |
| 13420 | `SChk5` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-schk5) |
| 13426 | `SChk6` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-schk6) |
| 13431 | `SLChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-slchk) |
| 13435 | `ExDLPl` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exdlpl) |
| 13439 | `DrawFloateyNumber_Coin` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawfloateynumber_coin) |
| 13444 | `NotRsNum` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notrsnum) |
| 13460 | `JumpingCoinTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpingcointiles) |
| 13463 | `JCoinGfxHandler` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jcoingfxhandler) |
| 13489 | `ExJCGfx` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exjcgfx) |
| 13500 | `PowerUpGfxTable` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-powerupgfxtable) |
| 13506 | `PowerUpAttributes` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-powerupattributes) |
| 13509 | `DrawPowerUp` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawpowerup) |
| 13530 | `PUpDrawLoop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pupdrawloop) |
| 13555 | `FlipPUpRightSide` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flippuprightside) |
| 13562 | `PUpOfs` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pupofs) |
| 13576 | `EnemyGraphicsTable` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemygraphicstable) |
| 13621 | `EnemyGfxTableOffsets` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemygfxtableoffsets) |
| 13627 | `EnemyAttributeData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemyattributedata) |
| 13633 | `EnemyAnimTimingBMask` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemyanimtimingbmask) |
| 13636 | `JumpspringFrameOffsets` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpspringframeoffsets) |
| 13639 | `EnemyGfxHandler` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemygfxhandler) |
| 13661 | `CheckForRetainerObj` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforretainerobj) |
| 13674 | `CheckForBulletBillCV` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforbulletbillcv) |
| 13682 | `SBBAt` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sbbat) |
| 13687 | `CheckForJumpspring` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforjumpspring) |
| 13694 | `CheckForPodoboo` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforpodoboo) |
| 13704 | `CheckBowserGfxFlag` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkbowsergfxflag) |
| 13711 | `SBwsrGfxOfs` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sbwsrgfxofs) |
| 13713 | `CheckForGoomba` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforgoomba) |
| 13722 | `GmbaAnim` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gmbaanim) |
| 13732 | `CheckBowserFront` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkbowserfront) |
| 13746 | `ChkFrontSte` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkfrontste) |
| 13750 | `FlipBowserOver` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flipbowserover) |
| 13753 | `DrawBowser` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawbowser) |
| 13756 | `CheckBowserRear` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkbowserrear) |
| 13761 | `ChkRearSte` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkrearste) |
| 13770 | `CheckForSpiny` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforspiny) |
| 13780 | `NotEgg` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notegg) |
| 13782 | `CheckForLakitu` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforlakitu) |
| 13792 | `NoLAFr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nolafr) |
| 13794 | `CheckUpsideDownShell` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkupsidedownshell) |
| 13807 | `CheckRightSideUpShell` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkrightsideupshell) |
| 13819 | `CheckForDefdGoomba` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkfordefdgoomba) |
| 13829 | `CheckForHammerBro` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforhammerbro) |
| 13841 | `CheckForBloober` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforbloober) |
| 13856 | `CheckToAnimateEnemy` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checktoanimateenemy) |
| 13878 | `CheckForSecondFrame` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforsecondframe) |
| 13883 | `CheckAnimationStop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkanimationstop) |
| 13893 | `CheckDefeatedState` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkdefeatedstate) |
| 13905 | `DrawEnemyObject` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawenemyobject) |
| 13916 | `SkipToOffScrChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skiptooffscrchk) |
| 13919 | `CheckForVerticalFlip` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforverticalflip) |
| 13943 | `FlipEnemyVertically` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flipenemyvertically) |
| 13957 | `CheckForESymmetry` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkforesymmetry) |
| 13965 | `ContES` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-contes) |
| 13975 | `ESRtnr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-esrtnr) |
| 13979 | `SpnySC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-spnysc) |
| 13982 | `MirrorEnemyGfx` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mirrorenemygfx) |
| 13994 | `EggExc` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-eggexc) |
| 14007 | `CheckToMirrorLakitu` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checktomirrorlakitu) |
| 14026 | `NVFLak` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nvflak) |
| 14033 | `CheckToMirrorJSpring` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checktomirrorjspring) |
| 14044 | `SprObjectOffscrChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sprobjectoffscrchk) |
| 14054 | `LcChk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lcchk) |
| 14060 | `Row3C` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-row3c) |
| 14067 | `Row23C` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-row23c) |
| 14073 | `AllRowC` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-allrowc) |
| 14085 | `ExEGHandler` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exeghandler) |
| 14088 | `DrawEnemyObjRow` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawenemyobjrow) |
| 14093 | `DrawOneSpriteRow` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawonespriterow) |
| 14097 | `MoveESprRowOffscreen` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveesprrowoffscreen) |
| 14104 | `MoveESprColOffscreen` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveesprcoloffscreen) |
| 14119 | `DefaultBlockObjTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-defaultblockobjtiles) |
| 14122 | `DrawBlock` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawblock) |
| 14133 | `DBlkLoop` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dblkloop) |
| 14147 | `ChkRep` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkrep) |
| 14159 | `SetBFlip` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setbflip) |
| 14167 | `BlkOffscr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blkoffscr) |
| 14174 | `PullOfsB` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pullofsb) |
| 14175 | `ChkLeftCo` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkleftco) |
| 14178 | `MoveColOffscreen` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movecoloffscreen) |
| 14182 | `ExDBlk` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exdblk) |
| 14187 | `DrawBrickChunks` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawbrickchunks) |
| 14197 | `DChunks` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dchunks) |
| 14242 | `ChnkOfs` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chnkofs) |
| 14250 | `ExBCDr` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exbcdr) |
| 14254 | `DrawFireball` | T16: `src/game/oam/fireball_gfx.c` | audited; mismatch | [T24 S1: D3](m2-t24-s1-node-verification.md#node-drawfireball) |
| 14261 | `DrawFirebar` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawfirebar) |
| 14275 | `FireA` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firea) |
| 14280 | `ExplosionTiles` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-explosiontiles) |
| 14283 | `DrawExplosion_Fireball` | T16: `src/game/oam/fireball_gfx.c` | audited; mismatch | [T24 S1: D4](m2-t24-s1-node-verification.md#node-drawexplosion_fireball) |
| 14292 | `DrawExplosion_Fireworks` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawexplosion_fireworks) |
| 14327 | `KillFireBall` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-killfireball) |
| 14334 | `DrawSmallPlatform` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawsmallplatform) |
| 14361 | `TopSP` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-topsp) |
| 14369 | `BotSP` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-botsp) |
| 14379 | `SOfs` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sofs) |
| 14386 | `SOfs2` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sofs2) |
| 14392 | `ExSPl` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exspl) |
| 14397 | `DrawBubble` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawbubble) |
| 14413 | `ExDBub` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exdbub) |
| 14418 | `PlayerGfxTblOffsets` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playergfxtbloffsets) |
| 14424 | `PlayerGraphicsTable` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-playergraphicstable) |
| 14457 | `SwimKickTileNum` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D5](m2-t24-s1-node-verification.md#node-swimkicktilenum) |
| 14460 | `PlayerGfxHandler` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D5](m2-t24-s1-node-verification.md#node-playergfxhandler) |
| 14466 | `CntPl` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D5](m2-t24-s1-node-verification.md#node-cntpl) |
| 14489 | `SwimKT` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D5](m2-t24-s1-node-verification.md#node-swimkt) |
| 14495 | `BigKTS` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D5](m2-t24-s1-node-verification.md#node-bigkts) |
| 14497 | `ExPGH` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-expgh) |
| 14499 | `FindPlayerAction` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-findplayeraction) |
| 14503 | `DoChangeSize` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-dochangesize) |
| 14507 | `PlayerKilled` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-playerkilled) |
| 14511 | `PlayerGfxProcessing` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D6](m2-t24-s1-node-verification.md#node-playergfxprocessing) |
| 14532 | `SUpdR` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D6](m2-t24-s1-node-verification.md#node-supdr) |
| 14535 | `PlayerOffscreenChk` | T16: `src/game/oam/player_gfx.c` | ROM-match complete | [T24 S1: complete](m2-t24-s1-node-verification.md#node-playeroffscreenchk) |
| 14547 | `PROfsLoop` | T16: `src/game/oam/player_gfx.c` | ROM-match complete | [T24 S1: complete](m2-t24-s1-node-verification.md#node-profsloop) |
| 14551 | `NPROffscr` | T16: `src/game/oam/player_gfx.c` | ROM-match complete | [T24 S1: complete](m2-t24-s1-node-verification.md#node-nproffscr) |
| 14561 | `IntermediatePlayerData` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-intermediateplayerdata) |
| 14564 | `DrawPlayer_Intermediate` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D7](m2-t24-s1-node-verification.md#node-drawplayer_intermediate) |
| 14566 | `PIntLoop` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D7](m2-t24-s1-node-verification.md#node-pintloop) |
| 14587 | `RenderPlayerSub` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D6](m2-t24-s1-node-verification.md#node-renderplayersub) |
| 14601 | `DrawPlayerLoop` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D6](m2-t24-s1-node-verification.md#node-drawplayerloop) |
| 14610 | `ProcessPlayerAction` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D8](m2-t24-s1-node-verification.md#node-processplayeraction) |
| 14626 | `ProcOnGroundActs` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-procongroundacts) |
| 14642 | `NonAnimatedActs` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-nonanimatedacts) |
| 14649 | `ActionFalling` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-actionfalling) |
| 14654 | `ActionWalkRun` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-actionwalkrun) |
| 14659 | `ActionClimbing` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-actionclimbing) |
| 14666 | `ActionSwimming` | T16: `src/game/oam/player_gfx.c` | audited; mismatch | [T24 S1: D8](m2-t24-s1-node-verification.md#node-actionswimming) |
| 14676 | `GetCurrentAnimOffset` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-getcurrentanimoffset) |
| 14680 | `FourFrameExtent` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-fourframeextent) |
| 14684 | `ThreeFrameExtent` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-threeframeextent) |
| 14687 | `AnimationControl` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-animationcontrol) |
| 14701 | `SetAnimC` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-setanimc) |
| 14702 | `ExAnimC` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-exanimc) |
| 14705 | `GetGfxOffsetAdder` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-getgfxoffsetadder) |
| 14712 | `SzOfs` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-szofs) |
| 14714 | `ChangeSizeOffsetAdder` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-changesizeoffsetadder) |
| 14718 | `HandleChangeSize` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-handlechangesize) |
| 14728 | `CSzNext` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-csznext) |
| 14729 | `GorSLog` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-gorslog) |
| 14734 | `GetOffsetFromAnimCtrl` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-getoffsetfromanimctrl) |
| 14741 | `ShrinkPlayer` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-shrinkplayer) |
| 14750 | `ShrPlF` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-shrplf) |
| 14753 | `ChkForPlayerAttrib` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-chkforplayerattrib) |
| 14767 | `KilledAtt` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-killedatt) |
| 14774 | `C_S_IGAtt` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-c_s_igatt) |
| 14781 | `ExPlyrAt` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-explyrat) |
| 14786 | `RelativePlayerPosition` | T16: `src/game/oam/object_position.c` | audited; mismatch | [T24 S1: D9](m2-t24-s1-node-verification.md#node-relativeplayerposition) |
| 14791 | `RelativeBubblePosition` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-relativebubbleposition) |
| 14797 | `RelativeFireballPosition` | T16: `src/game/oam/object_position.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-relativefireballposition) |
| 14801 | `RelWOfs` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-relwofs) |
| 14805 | `RelativeMiscPosition` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-relativemiscposition) |
| 14811 | `RelativeEnemyPosition` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-relativeenemyposition) |
| 14816 | `RelativeBlockPosition` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-relativeblockposition) |
| 14825 | `VariableObjOfsRelPos` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-variableobjofsrelpos) |
| 14834 | `GetObjRelativePosition` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getobjrelativeposition) |
| 14846 | `GetPlayerOffscreenBits` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-getplayeroffscreenbits) |
| 14851 | `GetFireballOffscreenBits` | T16: `src/game/oam/object_position.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-getfireballoffscreenbits) |
| 14857 | `GetBubbleOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getbubbleoffscreenbits) |
| 14863 | `GetMiscOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getmiscoffscreenbits) |
| 14869 | `ObjOffsetData` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-objoffsetdata) |
| 14872 | `GetProperObjOffset` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getproperobjoffset) |
| 14879 | `GetEnemyOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getenemyoffscreenbits) |
| 14884 | `GetBlockOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getblockoffscreenbits) |
| 14888 | `SetOffscrBitsOffset` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setoffscrbitsoffset) |
| 14894 | `GetOffScreenBitsSet` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getoffscreenbitsset) |
| 14911 | `RunOffscrBitsSubs` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runoffscrbitssubs) |
| 14927 | `XOffscreenBitsData` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xoffscreenbitsdata) |
| 14931 | `DefaultXOnscreenOfs` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-defaultxonscreenofs) |
| 14934 | `GetXOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getxoffscreenbits) |
| 14937 | `XOfsLoop` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xofsloop) |
| 14953 | `XLdBData` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-xldbdata) |
| 14959 | `ExXOfsBS` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exxofsbs) |
| 14963 | `YOffscreenBitsData` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-yoffscreenbitsdata) |
| 14968 | `DefaultYOnscreenOfs` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-defaultyonscreenofs) |
| 14971 | `HighPosUnitData` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-highposunitdata) |
| 14974 | `GetYOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getyoffscreenbits) |
| 14977 | `YOfsLoop` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-yofsloop) |
| 14993 | `YLdBData` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-yldbdata) |
| 14999 | `ExYOfsBS` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exyofsbs) |
| 15003 | `DividePDiff` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dividepdiff) |
| 15015 | `SetOscrO` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setoscro) |
| 15016 | `ExDivPD` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exdivpd) |
| 15025 | `DrawSpriteObject` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawspriteobject) |
| 15036 | `NoHFlip` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nohflip) |
| 15040 | `SetHFAt` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sethfat) |
| 15070 | `SoundEngine` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-soundengine) |
| 15075 | `SndOn` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sndon) |
| 15084 | `InPause` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-inpause) |
| 15099 | `PTone1F` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ptone1f) |
| 15101 | `ContPau` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-contpau) |
| 15108 | `PTone2F` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ptone2f) |
| 15109 | `PTRegC` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-ptregc) |
| 15112 | `DecPauC` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decpauc) |
| 15121 | `SkipPIn` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skippin) |
| 15125 | `RunSoundSubroutines` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runsoundsubroutines) |
| 15134 | `SkipSoundSubroutines` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipsoundsubroutines) |
| 15147 | `NoIncDAC` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noincdac) |
| 15150 | `StrWave` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strwave) |
| 15155 | `Dump_Squ1_Regs` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dump_squ1_regs) |
| 15160 | `PlaySqu1Sfx` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playsqu1sfx) |
| 15163 | `SetFreq_Squ1` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfreq_squ1) |
| 15166 | `Dump_Freq_Regs` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dump_freq_regs) |
| 15174 | `NoTone` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notone) |
| 15176 | `Dump_Sq2_Regs` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dump_sq2_regs) |
| 15181 | `PlaySqu2Sfx` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playsqu2sfx) |
| 15184 | `SetFreq_Squ2` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfreq_squ2) |
| 15188 | `SetFreq_Tri` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfreq_tri) |
| 15194 | `SwimStompEnvelopeData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-swimstompenvelopedata) |
| 15198 | `PlayFlagpoleSlide` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playflagpoleslide) |
| 15206 | `PlaySmallJump` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playsmalljump) |
| 15210 | `PlayBigJump` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playbigjump) |
| 15213 | `JumpRegContents` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumpregcontents) |
| 15220 | `ContinueSndJump` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuesndjump) |
| 15227 | `N2Prt` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-n2prt) |
| 15230 | `FPS2nd` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fps2nd) |
| 15231 | `DmpJpFPS` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-dmpjpfps) |
| 15234 | `PlayFireballThrow` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playfireballthrow) |
| 15239 | `PlayBump` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playbump) |
| 15242 | `Fthrow` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fthrow) |
| 15247 | `ContinueBumpThrow` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuebumpthrow) |
| 15253 | `DecJpFPS` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decjpfps) |
| 15256 | `Square1SfxHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-square1sfxhandler) |
| 15276 | `CheckSfx1Buffer` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checksfx1buffer) |
| 15294 | `ExS1H` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exs1h) |
| 15296 | `PlaySwimStomp` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playswimstomp) |
| 15304 | `ContinueSwimStomp` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continueswimstomp) |
| 15313 | `BranchToDecLength1` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-branchtodeclength1) |
| 15316 | `PlaySmackEnemy` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playsmackenemy) |
| 15325 | `ContinueSmackEnemy` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuesmackenemy) |
| 15333 | `SmSpc` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-smspc) |
| 15334 | `SmTick` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-smtick) |
| 15336 | `DecrementSfx1Length` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decrementsfx1length) |
| 15340 | `StopSquare1Sfx` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-stopsquare1sfx) |
| 15347 | `ExSfx1` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exsfx1) |
| 15349 | `PlayPipeDownInj` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playpipedowninj) |
| 15353 | `ContinuePipeDownInj` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuepipedowninj) |
| 15365 | `NoPDwnL` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nopdwnl) |
| 15369 | `ExtraLifeFreqData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-extralifefreqdata) |
| 15372 | `PowerUpGrabFreqData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-powerupgrabfreqdata) |
| 15380 | `PUp_VGrow_FreqData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pup_vgrow_freqdata) |
| 15386 | `PlayCoinGrab` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playcoingrab) |
| 15391 | `PlayTimerTick` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playtimertick) |
| 15395 | `CGrab_TTickRegL` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cgrab_ttickregl) |
| 15401 | `ContinueCGrabTTick` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuecgrabttick) |
| 15407 | `N2Tone` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-n2tone) |
| 15409 | `PlayBlast` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playblast) |
| 15416 | `ContinueBlast` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continueblast) |
| 15422 | `SBlasJ` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sblasj) |
| 15424 | `PlayPowerUpGrab` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playpowerupgrab) |
| 15428 | `ContinuePowerUpGrab` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuepowerupgrab) |
| 15437 | `LoadSqu2Regs` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadsqu2regs) |
| 15440 | `DecrementSfx2Length` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decrementsfx2length) |
| 15444 | `EmptySfx2Buffer` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-emptysfx2buffer) |
| 15448 | `StopSquare2Sfx` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-stopsquare2sfx) |
| 15453 | `ExSfx2` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exsfx2) |
| 15455 | `Square2SfxHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-square2sfxhandler) |
| 15478 | `CheckSfx2Buffer` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checksfx2buffer) |
| 15496 | `ExS2H` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exs2h) |
| 15498 | `Cont_CGrab_TTick` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-cont_cgrab_ttick) |
| 15501 | `JumpToDecLength2` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-jumptodeclength2) |
| 15504 | `PlayBowserFall` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playbowserfall) |
| 15509 | `BlstSJp` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blstsjp) |
| 15511 | `ContinueBowserFall` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuebowserfall) |
| 15517 | `PBFRegs` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-pbfregs) |
| 15518 | `EL_LRegs` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-el_lregs) |
| 15520 | `PlayExtraLife` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playextralife) |
| 15524 | `ContinueExtraLife` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continueextralife) |
| 15527 | `DivLLoop` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-divlloop) |
| 15537 | `PlayGrowPowerUp` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playgrowpowerup) |
| 15541 | `PlayGrowVine` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playgrowvine) |
| 15544 | `GrowItemRegs` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-growitemregs) |
| 15551 | `ContinueGrowItems` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuegrowitems) |
| 15564 | `StopGrowItems` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-stopgrowitems) |
| 15569 | `BrickShatterFreqData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-brickshatterfreqdata) |
| 15573 | `PlayBrickShatter` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playbrickshatter) |
| 15577 | `ContinueBrickShatter` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuebrickshatter) |
| 15585 | `PlayNoiseSfx` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playnoisesfx) |
| 15591 | `DecrementSfx3Length` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-decrementsfx3length) |
| 15598 | `ExSfx3` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exsfx3) |
| 15600 | `NoiseSfxHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noisesfxhandler) |
| 15609 | `CheckNoiseBuffer` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checknoisebuffer) |
| 15616 | `ExNH` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exnh) |
| 15618 | `PlayBowserFlame` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playbowserflame) |
| 15622 | `ContinueBowserFlame` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuebowserflame) |
| 15632 | `ContinueMusic` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-continuemusic) |
| 15635 | `MusicHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-musichandler) |
| 15645 | `LoadEventMusic` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadeventmusic) |
| 15651 | `NoStopSfx` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nostopsfx) |
| 15662 | `LoadAreaMusic` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadareamusic) |
| 15666 | `NoStop1` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nostop1) |
| 15667 | `GMLoopB` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gmloopb) |
| 15669 | `HandleAreaMusicLoopB` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handleareamusicloopb) |
| 15682 | `FindAreaMusicHeader` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-findareamusicheader) |
| 15686 | `FindEventMusicHeader` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-findeventmusicheader) |
| 15691 | `LoadHeader` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadheader) |
| 15720 | `HandleSquare2Music` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlesquare2music) |
| 15730 | `EndOfMusicData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endofmusicdata) |
| 15736 | `NotTRO` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nottro) |
| 15750 | `MusicLoopBack` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-musicloopback) |
| 15753 | `VictoryMLoopBack` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-victorymloopback) |
| 15756 | `Squ2LengthHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-squ2lengthhandler) |
| 15763 | `Squ2NoteHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-squ2notehandler) |
| 15769 | `Rest` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rest) |
| 15771 | `SkipFqL1` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipfql1) |
| 15774 | `MiscSqu2MusicTasks` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-miscsqu2musictasks) |
| 15783 | `NoDecEnv1` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nodecenv1) |
| 15788 | `HandleSquare1Music` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlesquare1music) |
| 15794 | `FetchSqu1MusicData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fetchsqu1musicdata) |
| 15806 | `Squ1NoteHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-squ1notehandler) |
| 15816 | `SkipCtrlL` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-skipctrll) |
| 15819 | `MiscSqu1MusicTasks` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-miscsqu1musictasks) |
| 15828 | `NoDecEnv2` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nodecenv2) |
| 15830 | `DeathMAltReg` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-deathmaltreg) |
| 15833 | `DoAltLoad` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-doaltload) |
| 15835 | `HandleTriangleMusic` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handletrianglemusic) |
| 15853 | `TriNoteHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-trinotehandler) |
| 15863 | `NotDOrD4` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notdord4) |
| 15871 | `MediN` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-medin) |
| 15873 | `LongN` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-longn) |
| 15875 | `LoadTriCtrlReg` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadtrictrlreg) |
| 15878 | `HandleNoiseMusic` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-handlenoisemusic) |
| 15885 | `FetchNoiseBeatData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-fetchnoisebeatdata) |
| 15894 | `NoiseBeatHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-noisebeathandler) |
| 15911 | `StrongBeat` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strongbeat) |
| 15917 | `LongBeat` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-longbeat) |
| 15923 | `SilentBeat` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-silentbeat) |
| 15926 | `PlayBeat` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playbeat) |
| 15931 | `ExitMusicHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitmusichandler) |
| 15934 | `AlternateLengthHandler` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-alternatelengthhandler) |
| 15942 | `ProcessLengthData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-processlengthdata) |
| 15951 | `LoadControlRegs` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadcontrolregs) |
| 15957 | `NotECstlM` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notecstlm) |
| 15962 | `WaterMus` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-watermus) |
| 15963 | `AllMus` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-allmus) |
| 15967 | `LoadEnvelopeData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadenvelopedata) |
| 15974 | `LoadUsualEnvData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadusualenvdata) |
| 15981 | `LoadWaterEventMusEnvData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loadwatereventmusenvdata) |
| 15989 | `MusicHeaderData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-musicheaderdata) |
| 16027 | `TimeRunningOutHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-timerunningouthdr) |
| 16028 | `Star_CloudHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-star_cloudhdr) |
| 16029 | `EndOfLevelMusHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endoflevelmushdr) |
| 16030 | `ResidualHeaderData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-residualheaderdata) |
| 16031 | `UndergroundMusHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-undergroundmushdr) |
| 16032 | `SilenceHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-silencehdr) |
| 16033 | `CastleMusHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-castlemushdr) |
| 16034 | `VictoryMusHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-victorymushdr) |
| 16035 | `GameOverMusHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gameovermushdr) |
| 16036 | `WaterMusHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-watermushdr) |
| 16037 | `WinCastleMusHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-wincastlemushdr) |
| 16038 | `GroundLevelPart1Hdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart1hdr) |
| 16039 | `GroundLevelPart2AHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart2ahdr) |
| 16040 | `GroundLevelPart2BHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart2bhdr) |
| 16041 | `GroundLevelPart2CHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart2chdr) |
| 16042 | `GroundLevelPart3AHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart3ahdr) |
| 16043 | `GroundLevelPart3BHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart3bhdr) |
| 16044 | `GroundLevelLeadInHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelleadinhdr) |
| 16045 | `GroundLevelPart4AHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart4ahdr) |
| 16046 | `GroundLevelPart4BHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart4bhdr) |
| 16047 | `GroundLevelPart4CHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundlevelpart4chdr) |
| 16048 | `DeathMusHdr` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-deathmushdr) |
| 16077 | `Star_CloudMData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-star_cloudmdata) |
| 16089 | `GroundM_P1Data` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p1data) |
| 16094 | `SilenceData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-silencedata) |
| 16104 | `GroundM_P2AData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p2adata) |
| 16114 | `GroundM_P2BData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p2bdata) |
| 16124 | `GroundM_P2CData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p2cdata) |
| 16134 | `GroundM_P3AData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p3adata) |
| 16140 | `GroundM_P3BData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p3bdata) |
| 16148 | `GroundMLdInData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundmldindata) |
| 16158 | `GroundM_P4AData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p4adata) |
| 16167 | `GroundM_P4BData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p4bdata) |
| 16176 | `DeathMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-deathmusdata) |
| 16179 | `GroundM_P4CData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-groundm_p4cdata) |
| 16193 | `CastleMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-castlemusdata) |
| 16217 | `GameOverMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-gameovermusdata) |
| 16226 | `TimeRunOutMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-timerunoutmusdata) |
| 16236 | `WinLevelMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-winlevelmusdata) |
| 16253 | `UndergroundMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-undergroundmusdata) |
| 16264 | `WaterMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-watermusdata) |
| 16295 | `EndOfCastleMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endofcastlemusdata) |
| 16313 | `VictoryMusData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-victorymusdata) |
| 16326 | `FreqRegLookupTbl` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-freqreglookuptbl) |
| 16341 | `MusicLengthLookupTbl` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-musiclengthlookuptbl) |
| 16349 | `EndOfCastleMusicEnvData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endofcastlemusicenvdata) |
| 16352 | `AreaMusicEnvData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areamusicenvdata) |
| 16355 | `WaterEventMusEnvData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-watereventmusenvdata) |
| 16362 | `BowserFlameEnvData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bowserflameenvdata) |
| 16368 | `BrickShatterEnvData` | T21 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-brickshatterenvdata) |

## Control-graph size

- Executable control nodes with an explicit edge: `1578`
- Static/data-only or unconnected labels requiring separate classification: `414`
