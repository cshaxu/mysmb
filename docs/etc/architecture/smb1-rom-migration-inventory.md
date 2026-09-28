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
  - [x] `WriteGameText` — ROM line 1719; T27 S2 P21 controlled ROM-entry proof
- [ ] **Area parser, metatile/attribute rendering and scrolling**
  - [ ] `RenderAreaGraphics` — ROM line 1825; C owner/evidence pending
  - [ ] `RenderAttributeTables` — ROM line 1920; C owner/evidence pending
  - [ ] `AreaParserTaskHandler` — ROM line 3060; C owner/evidence pending
  - [ ] `AreaParserCore` — ROM line 3179; C owner/evidence pending
  - [ ] `AreaParserTasks` — ROM line 3073; C owner/evidence pending
  - [ ] `ScrollScreen` — ROM line 5427; C owner/evidence pending
- [ ] **Game engine, mode transitions and timers**
  - [x] `GameCoreRoutine` - ROM line 5326; T31 S1 dispatcher entry proof (child interiors remain open).
  - [ ] `GameEngine` — ROM line 5336; C owner/evidence pending
  - [x] `GameRoutines` - ROM line 5499; T31 S4 thirteen-target caller proof; child interiors retain separate status.
  - [ ] `GameTimerExpired` — label lookup pending
  - [ ] `PlayerEndLevel` — ROM line 5856; C owner/evidence pending
- [ ] **Player movement, physics, collision and size state**
  - [x] `PlayerCtrlRoutine` - ROM line 5583; T32 S1 caller proof; actual child chain remains incomplete.
  - [ ] `MovePlayerHorizontally` — ROM line 7561; C owner/evidence pending
  - [ ] `PlayerBGCollision` — ROM line 11927; C owner/evidence pending
  - [ ] `PlayerHeadCollision` — ROM line 7244; C owner/evidence pending
  - [ ] `PlayerChangeSize` — ROM line 5757; C owner/evidence pending
- [ ] **Enemy stream, object initialization and enemy behavior**
  - [ ] `ProcessEnemyData` — ROM line 7911; C owner/evidence pending
  - [ ] `PositionEnemyObj` — ROM line 7967; C owner/evidence pending
  - [ ] `CheckpointEnemyID` — ROM line 8080; C owner/evidence pending
  - [ ] `EnemiesAndLoopsCore` — ROM line 7788; C owner/evidence pending
  - [x] `RunNormalEnemies` — ROM line 9092; [S8 caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s8-original-normal-actor-and-movement-vector-proof); child interiors remain separate.
- [ ] **Blocks, coins, power-ups, vines and miscellaneous objects**
  - [ ] `BlockObjMT_Updater` — ROM line 7527; C owner/evidence pending
  - [ ] `BumpBlock` — ROM line 7332; C owner/evidence pending
  - [x] `CoinBlock` — ROM line 6988; [S2 hammer proof](../../history/M2-T36-misc-object-chains.md#s3-original-coin-allocation-proof)
  - [x] `SetupPowerUp` — ROM line 7150; [S6 power-up initialization proof](../../history/M2-T36-misc-object-chains.md#s6-original-power-up-initialization-proof)
  - [ ] `PowerUpObjHandler` — ROM line 7184; C owner/evidence pending
  - [x] `VineObjectHandler` — ROM line 6730; [S1 vine actor proof](../../history/M2-T36-misc-object-chains.md#s1-original-vine-actor-proof)
- [ ] **Fireballs, projectile collision and special hazards**
  - [x] `FireballObjCore` — ROM line 6352; [S2 core proof](../../history/M2-T34-fireball-dispatch-core.md#s2-original-core-proof)
  - [ ] `FireballBGCollision` — ROM line 12751; C owner/evidence pending
  - [ ] `FireballEnemyCollision` — ROM line 11085; C owner/evidence pending
  - [x] `ProcFireball_Bubble` — ROM line 6298; [S1 dispatcher proof](../../history/M2-T34-fireball-dispatch-core.md#s1-original-dispatch-proof)
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
| 764 | `NonMaskableInterrupt` | T24 S2 custody after T22 S22 dependency audit; src/game/frame_root.c | mapped; evidence incomplete | [T22 S22 dependency audit](../../proposals/m2/t21-t49-source-order-recovery.md#t22s22-nmi-parent-dependency-audit-and-custody-return) |
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
| 912 | `SpriteShuffler` | T22 S27: independent controlled-ROM shuffle equivalence; src/game/frame_root.c | ROM-match complete | [T22 S27 controlled-ROM proof](../../proposals/m2/t21-t49-source-order-recovery.md#t22s27-sprite-shuffle-equivalence-result) |
| 917 | `ShuffleLoop` | T22 S27: independent controlled-ROM shuffle equivalence; src/game/frame_root.c | ROM-match complete | [T22 S27 controlled-ROM proof](../../proposals/m2/t21-t49-source-order-recovery.md#t22s27-sprite-shuffle-equivalence-result) |
| 926 | `StrSprOffset` | T22 S27: independent controlled-ROM shuffle equivalence; src/game/frame_root.c | ROM-match complete | [T22 S27 controlled-ROM proof](../../proposals/m2/t21-t49-source-order-recovery.md#t22s27-sprite-shuffle-equivalence-result) |
| 927 | `NextSprOffset` | T22 S27: independent controlled-ROM shuffle equivalence; src/game/frame_root.c | ROM-match complete | [T22 S27 controlled-ROM proof](../../proposals/m2/t21-t49-source-order-recovery.md#t22s27-sprite-shuffle-equivalence-result) |
| 934 | `SetAmtOffset` | T22 S27: independent controlled-ROM shuffle equivalence; src/game/frame_root.c | ROM-match complete | [T22 S27 controlled-ROM proof](../../proposals/m2/t21-t49-source-order-recovery.md#t22s27-sprite-shuffle-equivalence-result) |
| 937 | `SetMiscOffset` | T22 S27: independent controlled-ROM shuffle equivalence; src/game/frame_root.c | ROM-match complete | [T22 S27 controlled-ROM proof](../../proposals/m2/t21-t49-source-order-recovery.md#t22s27-sprite-shuffle-equivalence-result) |
| 954 | `OperModeExecutionTree` | T22 S28: independent operation-mode dispatch proof; src/game/frame_root.c | ROM-match complete | [T22 S28 independent proof](../../proposals/m2/t21-t49-source-order-recovery.md#t22s28-operation-mode-dispatch-equivalence-result) |
| 965 | `MoveAllSpritesOffscreen` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/boot.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveallspritesoffscreen) |
| 969 | `MoveSpritesOffscreen` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-movespritesoffscreen) |
| 972 | `SprInitLoop` | T22 S26: independent sprite-zero/OAM equivalence review; src/game/frame_root.c | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sprinitloop) |
| 982 | `TitleScreenMode` | M2 T25 S7: source-order title-idle prefix; `frame_root.c:mysmb_frame_root_step` | ROM-match complete | [T25 S7 title-idle closure](../../proposals/m2/t25-title-menu-demo.md#s7-closure-first-title-idle-prefix) |
| 993 | `WSelectBufferTemplate` | M2 T25 S20: six-byte world-select data binding; `title_modes.c:world_select_template` | ROM-match complete | [T25 S20 WSelectBufferTemplate closure](../../proposals/m2/t25-title-menu-demo.md#s20-closure-wselectbuffertemplate-data-binding) |
| 996 | `GameMenuRoutine` | M2 T25 S7: source-order title-idle prefix; `title_modes.c:mysmb_game_title_step` | ROM-match complete | [T25 S7 title-idle closure](../../proposals/m2/t25-title-menu-demo.md#s7-closure-first-title-idle-prefix) |
| 1004 | `StartGame` | M2 T25 S9: direct title-menu jump; `title_modes.c:mysmb_game_title_step` | ROM-match complete | [T25 S9 StartGame closure](../../proposals/m2/t25-title-menu-demo.md#s9-closure-startgame-direct-jump) |
| 1005 | `ChkSelect` | M2 T25 S10: non-Start title branch; `title_modes.c:mysmb_game_title_step` | ROM-match complete | [T25 S10 ChkSelect closure](../../proposals/m2/t25-title-menu-demo.md#s10-closure-chkselect-branch-entry) |
| 1013 | `ChkWorldSel` | M2 T25 S11: zero world-select branch; `title_modes.c:mysmb_game_title_step` | ROM-match complete | [T25 S11 ChkWorldSel closure](../../proposals/m2/t25-title-menu-demo.md#s11-closure-chkworldsel-zero-flag-branch) |
| 1018 | `SelectBLogic` | M2 T25 S12: Select title branch; `title_modes.c:mysmb_game_title_step` | ROM-match complete | [T25 S12 SelectBLogic closure](../../proposals/m2/t25-title-menu-demo.md#s12-closure-selectblogic-entry) |
| 1033 | `IncWorldSel` | M2 T25 S13: controlled B branch; `title_modes.c:mysmb_game_title_step` | ROM-match complete | [T25 S13 IncWorldSel closure](../../proposals/m2/t25-title-menu-demo.md#s13-closure-incworldsel-controlled-b-branch) |
| 1039 | `UpdateShroom` | M2 T25 S14: template write loop; `title_modes.c:mysmb_game_title_step` | ROM-match complete | [T25 S14 UpdateShroom closure](../../proposals/m2/t25-title-menu-demo.md#s14-closure-updateshroom-write-loop) |
| 1047 | `NullJoypad` | M2 T25 S7: source-order title-idle prefix; `title_modes.c:mysmb_game_title_step` | ROM-match complete | [T25 S7 title-idle closure](../../proposals/m2/t25-title-menu-demo.md#s7-closure-first-title-idle-prefix) |
| 1049 | `RunDemo` | M2 T25 S7: source-order title-idle prefix; `frame_root.c:mysmb_frame_root_step` | ROM-match complete | [T25 S7 title-idle closure](../../proposals/m2/t25-title-menu-demo.md#s7-closure-first-title-idle-prefix) |
| 1053 | `ResetTitle` | M2 T25 S8: source-order title reset leaf; `title_modes.c:mysmb_game_reset_title` | ROM-match complete | [T25 S8 ResetTitle closure](../../proposals/m2/t25-title-menu-demo.md#s8-closure-resettitle) |
| 1059 | `ChkContinue` | M2 T25 S15: `DemoTimer` and A+Start continuation branch; `title_modes.c:mysmb_game_chk_continue` | ROM-match complete | [T25 S15 ChkContinue closure](../../proposals/m2/t25-title-menu-demo.md#s15-closure-chkcontinue-dual-branch-entry) |
| 1065 | `StartWorld1` | M2 T25 S16: common post-Start continuation; `title_modes.c:mysmb_game_start_world1` | ROM-match complete | [T25 S16 StartWorld1 closure](../../proposals/m2/t25-title-menu-demo.md#s16-closure-startworld1-common-continuation) |
| 1077 | `InitScores` | M2 T25 S17: score/coin descending clear; `title_modes.c:mysmb_game_init_scores` | ROM-match complete | [T25 S17 InitScores closure](../../proposals/m2/t25-title-menu-demo.md#s17-closure-initscores-clear-loop) |
| 1080 | `ExitMenu` | M2 T25 S18: title-menu RTS leaf; `title_modes.c:mysmb_game_exit_menu` | ROM-match complete | [T25 S18 ExitMenu closure](../../proposals/m2/t25-title-menu-demo.md#s18-closure-exitmenu-return) |
| 1081 | `GoContinue` | M2 T25 S19: shared world/area continuation leaf; `title_modes.c:mysmb_game_go_continue` | ROM-match complete | [T25 S19 GoContinue closure](../../proposals/m2/t25-title-menu-demo.md#s19-closure-gocontinue-dual-caller) |
| 1090 | `MushroomIconData` | M2 T25 S21: complete icon-data binding; `title_modes.c:mysmb_game_draw_mushroom_icon` | ROM-match complete | [T25 S21 MushroomIconData closure](../../proposals/m2/t25-title-menu-demo.md#s21-closure-mushroomicondata-binding) |
| 1093 | `DrawMushroomIcon` | M2 T25 S22: icon routine initializer and player branch; `title_modes.c:mysmb_game_draw_mushroom_icon` | ROM-match complete | [T25 S22 DrawMushroomIcon closure](../../proposals/m2/t25-title-menu-demo.md#s22-closure-drawmushroomicon-routine) |
| 1095 | `IconDataRead` | M2 T25 S23: icon copy-loop; `title_modes.c:mysmb_game_draw_mushroom_icon` | ROM-match complete | [T25 S23 IconDataRead closure](../../proposals/m2/t25-title-menu-demo.md#s23-closure-icondataread-loop) |
| 1105 | `ExitIcon` | M2 T25 S24: icon return leaf; `title_modes.c:mysmb_game_draw_mushroom_icon` | ROM-match complete | [T25 S24 ExitIcon closure](../../proposals/m2/t25-title-menu-demo.md#s24-closure-exiticon-return-chain) |
| 1109 | `DemoActionData` | M2 T25 S25: table binding; `title_modes.c:mysmb_game_step_title_demo` | ROM-match complete | [T25 S25 demo-chain closure](../../proposals/m2/t25-title-menu-demo.md#s25-closure-title-idle-demo-data-and-engine-chain) |
| 1114 | `DemoTimingData` | M2 T25 S25: table binding; `title_modes.c:mysmb_game_step_title_demo` | ROM-match complete | [T25 S25 demo-chain closure](../../proposals/m2/t25-title-menu-demo.md#s25-closure-title-idle-demo-data-and-engine-chain) |
| 1119 | `DemoEngine` | M2 T25 S25: shared title demo owner; `title_modes.c:mysmb_game_step_title_demo` | ROM-match complete | [T25 S25 demo-chain closure](../../proposals/m2/t25-title-menu-demo.md#s25-closure-title-idle-demo-data-and-engine-chain) |
| 1129 | `DoAction` | M2 T25 S25: shared title demo owner; `title_modes.c:mysmb_game_step_title_demo` | ROM-match complete | [T25 S25 demo-chain closure](../../proposals/m2/t25-title-menu-demo.md#s25-closure-title-idle-demo-data-and-engine-chain) |
| 1133 | `DemoOver` | M2 T25 S25: shared title demo owner; `title_modes.c:mysmb_game_step_title_demo` | ROM-match complete | [T25 S25 demo-chain closure](../../proposals/m2/t25-title-menu-demo.md#s25-closure-title-idle-demo-data-and-engine-chain) |
| 1137 | `VictoryMode` | T26 S7 outer-route owner; `frame_root.c` + `terminal_modes.c:mysmb_game_step_victory` | ROM-match complete | [T26 S7 outer-route evidence](../../proposals/m2/t26-victory-terminal.md#s7-closure) |
| 1144 | `AutoPlayer` | T26 S7 outer-route owner; `frame_root.c` player/OAM tail | ROM-match complete | [T26 S7 outer-route evidence](../../proposals/m2/t26-victory-terminal.md#s7-closure) |
| 1147 | `VictoryModeSubroutines` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_step_victory` | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1159 | `SetupVictoryMode` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_step_victory` + `player.c` | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1169 | `PlayerVictoryWalk` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_step_victory` + `player.c` | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1178 | `PerformWalk` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1180 | `DontWalk` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1195 | `ExitVWalk` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1201 | `PrintVictoryMessages` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_print_victory_messages` | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1215 | `MRetainerMsg` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1217 | `ThankPlayer` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1223 | `SecondPartMsg` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1232 | `EvalForMusic` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1236 | `PrintMsg` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1240 | `IncMsgCounter` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1248 | `SetEndTimer` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1251 | `IncModeTask_A` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1252 | `ExitMsgs` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1256 | `PlayerEndWorld` | T15 responsibility (implementation not certified); `terminal_modes.c:mysmb_game_step_victory` | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1271 | `EndExitOne` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1272 | `EndChkBButton` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1281 | `EndExitTwo` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1287 | `FloateyNumTileData` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1303 | `ScoreUpdateData` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1308 | `FloateyNumbersRoutine` | T15 responsibility (implementation not certified); `objects.c:mysmb_objects_step_floatey_number` | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1315 | `ChkNumTimer` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1320 | `DecNumTimer` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1328 | `LoadNumTiles` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1338 | `ChkTallEnemy` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1355 | `GetAltOffset` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1358 | `FloateyPart` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1363 | `SetupNumSpr` | T15 responsibility (implementation not certified) | ROM-match complete | [T26 S5 evidence](../../proposals/m2/t26-victory-terminal.md#s5-per-label-evidence-matrix) |
| 1386 | `ScreenRoutines` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-screenroutines) |
| 1408 | `InitScreen` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1418 | `SetupIntermediate` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1436 | `AreaPalette` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1439 | `GetAreaPalette` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1442 | `SetVRAMAddr_A` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1443 | `NextSubtask` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1448 | `BGColorCtrl_Addr` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1451 | `BackgroundColors` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1455 | `PlayerColors` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1460 | `GetBackgroundColor` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1465 | `NoBGColor` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1467 | `GetPlayerColors` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1473 | `ChkFiery` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1477 | `StartClrGet` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1479 | `ClrGetLoop` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1489 | `SetBGColor` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1502 | `SetVRAMOffset` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1507 | `GetAlternatePalette1` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1512 | `SetVRAMAddr_B` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1513 | `NoAltPal` | M2 T27 S1: screen initialization/palette chain; `game.c` + `area.c` | ROM-match complete | [T27 S1 closure](../../proposals/m2/screen-status.md#s1-closure-screen-initialization-and-palette-chain) |
| 1517 | `WriteTopStatusLine` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1524 | `WriteBottomStatusLine` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P19](../../proposals/m2/screen-status.md#s2p19-status-caller-boundary-completion) |
| 1553 | `DisplayTimeUp` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1560 | `NoTimeUp` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1565 | `DisplayIntermediate` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1577 | `PlayerInter` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1579 | `OutputInter` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1584 | `GameOverInter` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1589 | `NoInter` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1595 | `AreaParserTaskControl` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-areaparsertaskcontrol) |
| 1597 | `TaskLoop` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-taskloop) |
| 1603 | `OutputCol` | screen candidate / historical T10 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-outputcol) |
| 1612 | `DrawTitleScreen` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1624 | `OutputTScr` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1629 | `ChkHiByte` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1639 | `ClearBuffersDrawIcon` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1643 | `TScrClear` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1648 | `IncSubtask` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1653 | `WriteTopScore` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P19](../../proposals/m2/screen-status.md#s2p19-status-caller-boundary-completion) |
| 1656 | `IncModeTask_B` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1661 | `GameText` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1662 | `TopStatusBarLine` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1671 | `WorldLivesDisplay` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1680 | `TwoPlayerTimeUp` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1682 | `OnePlayerTimeUp` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1686 | `TwoPlayerGameOver` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1688 | `OnePlayerGameOver` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1693 | `WarpZoneWelcome` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P21](../../proposals/m2/screen-status.md#s2p21-controlled-warp-text-entry-equivalence-and-closure) |
| 1704 | `LuigiName` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1707 | `WarpZoneNumbers` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P21](../../proposals/m2/screen-status.md#s2p21-controlled-warp-text-entry-equivalence-and-closure) |
| 1712 | `GameTextOffsets` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1719 | `WriteGameText` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P21](../../proposals/m2/screen-status.md#s2p21-controlled-warp-text-entry-equivalence-and-closure) |
| 1728 | `Chk2Players` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1731 | `LdGameText` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1733 | `GameTextLoop` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1740 | `EndGameText` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P21](../../proposals/m2/screen-status.md#s2p21-controlled-warp-text-entry-equivalence-and-closure) |
| 1756 | `PutLives` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1765 | `CheckPlayerName` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1775 | `ChkLuigi` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1778 | `NameLoop` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1782 | `ExitChkName` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1784 | `PrintWarpZoneNumbers` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P21](../../proposals/m2/screen-status.md#s2p21-controlled-warp-text-entry-equivalence-and-closure) |
| 1790 | `WarpNumLoop` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P21](../../proposals/m2/screen-status.md#s2p21-controlled-warp-text-entry-equivalence-and-closure) |
| 1804 | `ResetSpritesAndScreenTimer` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1809 | `ResetScreenTimer` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1813 | `NoReset` | M2 T27 S2 shared screen/status/text chain | ROM-match complete | [T27 S2 P17](../../proposals/m2/screen-status.md#s2p17-partial-chain-conformance-disposition) |
| 1825 | `RenderAreaGraphics` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1840 | `DrawMTLoop` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1878 | `RightCheck` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1886 | `LLeft` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1888 | `NextMTRow` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1889 | `SetAttrib` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1914 | `ExitDrawM` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1920 | `RenderAttributeTables` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1930 | `SetATHigh` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1940 | `AttribLoop` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1962 | `SetVRAMCtrl` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 1970 | `ColorRotatePalette` | M2 T28 S2 shared palette rotation chain | ROM-match complete | [T28 S2 palette rotation equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s2-closure-palette-rotation-equivalence) |
| 1973 | `BlankPalette` | M2 T28 S2 shared palette rotation chain | ROM-match complete | [T28 S2 palette rotation equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s2-closure-palette-rotation-equivalence) |
| 1977 | `Palette3Data` | M2 T28 S2 shared palette rotation chain | ROM-match complete | [T28 S2 palette rotation equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s2-closure-palette-rotation-equivalence) |
| 1983 | `ColorRotation` | M2 T28 S2 shared palette rotation chain | ROM-match complete | [T28 S2 palette rotation equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s2-closure-palette-rotation-equivalence) |
| 1991 | `GetBlankPal` | M2 T28 S2 shared palette rotation chain | ROM-match complete | [T28 S2 palette rotation equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s2-closure-palette-rotation-equivalence) |
| 2004 | `GetAreaPal` | M2 T28 S2 shared palette rotation chain | ROM-match complete | [T28 S2 palette rotation equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s2-closure-palette-rotation-equivalence) |
| 2024 | `ExitColorRot` | M2 T28 S2 shared palette rotation chain | ROM-match complete | [T28 S2 palette rotation equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s2-closure-palette-rotation-equivalence) |
| 2034 | `BlockGfxData` | M2 T28 S3 source-table binding | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2041 | `RemoveCoin_Axe` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2047 | `WriteBlankMT` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2052 | `ReplaceBlockMetatile` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2058 | `DestroyBlockMetatile` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2061 | `WriteBlockMetatile` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2076 | `UseBOffset` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2080 | `MoveVOffset` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2086 | `PutBlockMetatile` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2097 | `SaveHAdder` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2118 | `RemBridge` | M2 T28 S3 shared command owner | ROM-match complete | [T28 S3 closure](../../proposals/m2/t28-area-output-bootstrap.md#s3-closure-block-graphics-command-chain) |
| 2145 | `MetatileGraphics_Low` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 2148 | `MetatileGraphics_High` | M2 T28 S1 shared area output chain | ROM-match complete | [T28 S1 renderer/attribute equivalence](../../proposals/m2/t28-area-output-bootstrap.md#s1p1-renderer-and-attribute-equivalence-result) |
| 2151 | `Palette0_MTiles` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2192 | `Palette1_MTiles` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2240 | `Palette2_MTiles` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2252 | `Palette3_MTiles` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2263 | `WaterPaletteData` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2275 | `GroundPaletteData` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2287 | `UndergroundPaletteData` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2299 | `CastlePaletteData` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2311 | `DaySnowPaletteData` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2316 | `NightSnowPaletteData` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2321 | `MushroomPaletteData` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2326 | `BowserPaletteData` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2331 | `MarioThanksMessage` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2339 | `LuigiThanksMessage` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2347 | `MushroomRetainerSaved` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2358 | `PrincessSaved1` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2366 | `PrincessSaved2` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2375 | `WorldSelectMessage1` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2382 | `WorldSelectMessage2` | M2 T28 S4 shared data consumer | ROM-match complete | [T28 S4 data-chain evidence](../../proposals/m2/t28-area-output-bootstrap.md#s4-closure-data-chain-equivalence) |
| 2395 | `JumpEngine` | M2 T28 S5 shared selector boundary | ROM-match complete | [T28 S5 closure](../../proposals/m2/t28-area-output-bootstrap.md#s5-closure-name-table-initialization-chain) |
| 2412 | `InitializeNameTables` | M2 T28 S5 shared boot owner | ROM-match complete | [T28 S5 closure](../../proposals/m2/t28-area-output-bootstrap.md#s5-closure-name-table-initialization-chain) |
| 2421 | `WriteNTAddr` | M2 T28 S5 shared boot owner | ROM-match complete | [T28 S5 closure](../../proposals/m2/t28-area-output-bootstrap.md#s5-closure-name-table-initialization-chain) |
| 2427 | `InitNTLoop` | M2 T28 S5 shared boot owner | ROM-match complete | [T28 S5 closure](../../proposals/m2/t28-area-output-bootstrap.md#s5-closure-name-table-initialization-chain) |
| 2436 | `InitATLoop` | M2 T28 S5 shared boot owner | ROM-match complete | [T28 S5 closure](../../proposals/m2/t28-area-output-bootstrap.md#s5-closure-name-table-initialization-chain) |
| 2446 | `ReadJoypads` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2454 | `ReadPortBits` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2455 | `PortLoop` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2474 | `Save8Bits` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2482 | `WriteBufferToScreen` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2495 | `SetupWrites` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2501 | `GetLength` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2504 | `OutputToVRAM` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2506 | `RepeatByte` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2523 | `UpdateScreen` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2527 | `InitScroll` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2533 | `WritePPUReg1` | M2 T28 S6 shared NMI/VRAM owner | ROM-match complete | [T28 S6 closure](../../proposals/m2/t28-area-output-bootstrap.md#s6-closure-joypad-vram-nmi-chain) |
| 2544 | `StatusBarData` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2552 | `StatusBarOffset` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2555 | `PrintStatusBarNumbers` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2564 | `OutputNumbers` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2578 | `SetupNums` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2592 | `DigitPLoop` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2604 | `ExitOutputN` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2608 | `DigitsMathRoutine` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2613 | `AddModLoop` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2619 | `StoreNewD` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2623 | `EraseDMods` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2625 | `EraseMLoop` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2629 | `BorrowOne` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2632 | `CarryOne` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2639 | `UpdateTopScore` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2644 | `TopScoreCheck` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2647 | `GetScoreDiff` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2655 | `CopyScore` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2661 | `NoTopSc` | M2 T28 S7 shared status owner | ROM-match complete | [T28 S7 closure](../../proposals/m2/t28-area-output-bootstrap.md#s7-closure-status-bar-and-digit-arithmetic-chain) |
| 2665 | `DefaultSprOffsets` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2669 | `Sprite0Data` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2674 | `InitializeGame` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2678 | `ClrSndLoop` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2685 | `InitializeArea` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2690 | `ClrTimersLoop` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2697 | `StartPage` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2705 | `SetInitNTHigh` | M2 T30 S13 shared block-address chain and initial-page producer | ROM-match complete | [T30 S13/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s13p1-block-address-and-initial-page-proof) |
| 2728 | `SetSecHard` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2729 | `CheckHalfway` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2733 | `DoneInitArea` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2742 | `PrimaryGameSetup` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2750 | `SecondaryGameSetup` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2754 | `ClearVRLoop` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2775 | `ShufAmtLoop` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2780 | `ISpr0Loop` | M2 T28 S8 shared initialization owner | ROM-match complete | [T28 S8 closure](../../proposals/m2/t28-area-output-bootstrap.md#s8-closure-initialization-bootstrap-chain) |
| 2795 | `InitializeMemory` | T22 S14: shared boot/timing boundary | ROM-match complete | [T22 S14 complete](../../proposals/m2/t21-t49-source-order-recovery.md#t22s14-boot-root-equivalence-result) |
| 2799 | `InitPageLoop` | M2 T29 S1 shared initialization-loop owner | ROM-match complete | [T29 S1 closure](../../proposals/m2/t29-area-parser-geometry.md#s1-closure-initializememory-loop-chain) |
| 2800 | `InitByteLoop` | M2 T29 S1 shared initialization-loop owner | ROM-match complete | [T29 S1 closure](../../proposals/m2/t29-area-parser-geometry.md#s1-closure-initializememory-loop-chain) |
| 2804 | `InitByte` | M2 T29 S1 shared initialization-loop owner | ROM-match complete | [T29 S1 closure](../../proposals/m2/t29-area-parser-geometry.md#s1-closure-initializememory-loop-chain) |
| 2805 | `SkipByte` | M2 T29 S1 shared initialization-loop owner | ROM-match complete | [T29 S1 closure](../../proposals/m2/t29-area-parser-geometry.md#s1-closure-initializememory-loop-chain) |
| 2814 | `MusicSelectData` | M2 T29 S2 shared area-music owner | ROM-match complete | [T29 S2 closure](../../proposals/m2/t29-area-parser-geometry.md#s2-closure-area-music-selection-chain) |
| 2818 | `GetAreaMusic` | M2 T29 S2 shared area-music owner | ROM-match complete | [T29 S2 closure](../../proposals/m2/t29-area-parser-geometry.md#s2-closure-area-music-selection-chain) |
| 2830 | `ChkAreaType` | M2 T29 S2 shared area-music owner | ROM-match complete | [T29 S2 closure](../../proposals/m2/t29-area-parser-geometry.md#s2-closure-area-music-selection-chain) |
| 2834 | `StoreMusic` | M2 T29 S2 shared area-music owner | ROM-match complete | [T29 S2 closure](../../proposals/m2/t29-area-parser-geometry.md#s2-closure-area-music-selection-chain) |
| 2836 | `ExitGetM` | M2 T29 S2 shared area-music owner | ROM-match complete | [T29 S2 closure](../../proposals/m2/t29-area-parser-geometry.md#s2-closure-area-music-selection-chain) |
| 2840 | `PlayerStarting_X_Pos` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2844 | `AltYPosOffset` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2847 | `PlayerStarting_Y_Pos` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2851 | `PlayerBGPriorityData` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2854 | `GameTimerData` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2858 | `Entrance_GameTimerSetup` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2874 | `ChkStPos` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2881 | `SetStPos` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2900 | `ChkOverR` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2911 | `ChkSwimE` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2914 | `SetPESub` | M2 T29 S3 shared player/area-entry owner | ROM-match complete | [T29 S3 closure](../../proposals/m2/t29-area-parser-geometry.md#s3-closure-playerarea-entry-initialization-chain) |
| 2921 | `HalfwayPageNybbles` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 2931 | `PlayerLoseLife` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 2944 | `StillInGame` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 2951 | `GetHalfway` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 2960 | `MaskHPNyb` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 2965 | `SetHalfway` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 2971 | `GameOverMode` | T18 responsibility (implementation not certified); `frame_root.c` + `terminal_modes.c:mysmb_game_step_game_over` | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 2981 | `SetupGameOver` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 2993 | `RunGameOver` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 3001 | `TerminateGame` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 3015 | `ContinueGame` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 3027 | `GameIsOn` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 3029 | `TransposePlayers` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 3039 | `TransLoop` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 3048 | `ExTrans` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 3052 | `DoNothing1` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 3055 | `DoNothing2` | T18 responsibility (implementation not certified) | ROM-match complete |[T29 S4 closure](../../proposals/m2/t29-area-parser-geometry.md#s4-p2-and-closure-controlled-rom-routes-and-terminal-mode-chain)|
| 3060 | `AreaParserTaskHandler` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3065 | `DoAPTasks` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3071 | `SkipATRender` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3073 | `AreaParserTasks` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3087 | `IncrementColumnPos` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3094 | `NoColWrap` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3106 | `BSceneDataOffsets` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3109 | `BackSceneryData` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3131 | `BackSceneryMetatiles` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3145 | `FSceneDataOffsets` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3148 | `ForeSceneryData` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3158 | `TerrainMetatiles` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3161 | `TerrainRenderBits` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3179 | `AreaParserCore` | T18 responsibility (implementation not certified) | ROM-match complete | [T29 S5 closure](../../proposals/m2/t29-area-parser-geometry.md#s5-closure-and-s6-admission-parser-dispatch-data-chain) |
| 3184 | `RenderSceneryTerrain` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendersceneryterrain) |
| 3187 | `ClrMTBuf` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-clrmtbuf) |
| 3193 | `ThirdP` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-thirdp) |
| 3198 | `RendBack` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendback) |
| 3223 | `SceLoop1` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sceloop1) |
| 3231 | `RendFore` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendfore) |
| 3235 | `SceLoop2` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-sceloop2) |
| 3238 | `NoFore` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nofore) |
| 3242 | `RendTerr` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendterr) |
| 3249 | `TerMTile` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-termtile) |
| 3253 | `StoreMT` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-storemt) |
| 3258 | `TerrLoop` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-terrloop) |
| 3269 | `NoCloud2` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nocloud2) |
| 3270 | `TerrBChk` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-terrbchk) |
| 3275 | `NextTBit` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nexttbit) |
| 3285 | `EndUChk` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enduchk) |
| 3290 | `RendBBuf` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rendbbuf) |
| 3295 | `ChkMTLow` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkmtlow) |
| 3306 | `StrBlock` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-strblock) |
| 3319 | `BlockBuffLowBounds` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-blockbufflowbounds) |
| 3326 | `ProcessAreaData` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-processareadata) |
| 3328 | `ProcADLoop` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procadloop) |
| 3345 | `Chk1Row13` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk1row13) |
| 3363 | `Chk1Row14` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk1row14) |
| 3367 | `CheckRear` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-checkrear) |
| 3370 | `RdyDecode` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-rdydecode) |
| 3372 | `SetBehind` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setbehind) |
| 3373 | `NextAObj` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nextaobj) |
| 3374 | `ChkLength` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chklength) |
| 3378 | `ProcLoopb` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-procloopb) |
| 3384 | `EndAParse` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-endaparse) |
| 3386 | `IncAreaObjOffset` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-incareaobjoffset) |
| 3393 | `DecodeAreaData` | M2 T30 S11 shared area parser | ROM-match complete | [T30 S11/P1 corrected byte-index proof](../../history/M2-T30-area-object-rendering.md#s11p1-parser-index-wrap-rom-proof) |
| 3397 | `Chk1stB` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chk1stb) |
| 3408 | `ChkRow14` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkrow14) |
| 3416 | `ChkRow13` | M2 T30 S16 shared area parser | ROM-match complete | [S16 source binding and full parser routes](../../history/M2-T30-area-object-rendering.md#s16p1-castle-stream-consumption-and-loop-command-order) |
| 3429 | `Mask2MSB` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-mask2msb) |
| 3431 | `ChkSRows` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chksrows) |
| 3442 | `LrgObj` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-lrgobj) |
| 3450 | `NotWPipe` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-notwpipe) |
| 3452 | `SpecObj` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-specobj) |
| 3455 | `MoveAOId` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moveaoid) |
| 3459 | `NormObj` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-normobj) |
| 3472 | `LeavePar` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-leavepar) |
| 3473 | `InitRear` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-initrear) |
| 3479 | `LoopCmdE` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-loopcmde) |
| 3480 | `BackColC` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-backcolc) |
| 3489 | `StrAObj` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-straobj) |
| 3492 | `RunAObj` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runaobj) |
| 3561 | `AlterAreaAttributes` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-alterareaattributes) |
| 3580 | `Alter2` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-alter2) |
| 3586 | `SetFore` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setfore) |
| 3591 | `ScrollLockObject_Warp` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3600 | `WarpNum` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3606 | `ScrollLockObject` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3615 | `KillEnemies` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3619 | `KillELoop` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3623 | `NoKillE` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3629 | `FrenzyIDData` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3632 | `AreaFrenzy` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3635 | `FreCompLoop` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3640 | `ExitAFrenzy` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3646 | `AreaStyleObject` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3653 | `TreeLedge` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3665 | `MidTreeL` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3670 | `EndTreeL` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3673 | `MushroomLedge` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3682 | `EndMushL` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3696 | `AllUnder` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3699 | `NoUnder` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3706 | `PulleyRopeMetatiles` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3709 | `PulleyRopeObject` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3717 | `RenderPul` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3719 | `MushLExit` | T18 responsibility (implementation not certified) | ROM-match complete | [S8 closure](../../proposals/m2/t29-area-parser-geometry.md#s8-closure-special-object-parser-chain) |
| 3724 | `CastleMetatiles` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3737 | `CastleObject` | T18: `src/game/area.c` | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3748 | `CRendLoop` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3759 | `ChkCFloor` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3772 | `NotTall` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3789 | `PlayerStop` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3791 | `ExitCastle` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3795 | `WaterPipe` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3810 | `IntroPipe` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3817 | `VPipeSectLoop` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3823 | `NoBlankP` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3825 | `SidePipeShaftData` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3828 | `SidePipeTopPart` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3831 | `SidePipeBottomPart` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3835 | `ExitPipe` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3840 | `RenderSidewaysPipe` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3855 | `DrawSidePart` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3862 | `VerticalPipeData` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3868 | `VerticalPipe` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3876 | `WarpPipe` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3900 | `DrawPipe` | M2 T30 S12 shared DrawPipe tail | ROM-match complete | [T30 S12/P1 corrected tail proof](../../history/M2-T30-area-object-rendering.md#s12p1-draw-pipe-tail-rom-proof) |
| 3911 | `GetPipeHeight` | T18 responsibility (implementation not certified) | ROM-match complete | [S9 closure](../../proposals/m2/t29-area-parser-geometry.md#s9-closure-castle-and-pipe-large-object-geometry-chain) |
| 3921 | `FindEmptyEnemySlot` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-findemptyenemyslot) |
| 3923 | `EmptyChkLoop` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-emptychkloop) |
| 3929 | `ExitEmptyChk` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-exitemptychk) |
| 3933 | `Hole_Water` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-hole_water) |
| 3944 | `QuestionBlockRow_High` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-questionblockrow_high) |
| 3948 | `QuestionBlockRow_Low` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-questionblockrow_low) |
| 3960 | `Bridge_High` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridge_high) |
| 3964 | `Bridge_Middle` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridge_middle) |
| 3968 | `Bridge_Low` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridge_low) |
| 3983 | `FlagBalls_Residual` | T18 responsibility (implementation not certified) | ROM-match complete | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-flagballs_residual) |
| 3991 | `FlagpoleObject` | T22 responsibility; `area.c`: object decode; `oam/flagpole_gfx.c`: start/step | ROM-match complete | [T22 S5/P1 flagpole-chain evidence](../../proposals/m2/blocks-items-misc.md#s5p1-flagpole-parser-score-and-graphics-route) |
| 4018 | `EndlessRope` | M2 T30 S1 shared `area.c` rope route | ROM-match complete | [T30 S1/P1 rope-chain evidence](../../history/M2-T30-area-object-rendering.md#s1p1-rom-rope-chain-and-three-target-delivery) |
| 4023 | `BalancePlatRope` | M2 T30 S1 shared `area.c` rope route | ROM-match complete | [T30 S1/P1 rope-chain evidence](../../history/M2-T30-area-object-rendering.md#s1p1-rom-rope-chain-and-three-target-delivery) |
| 4034 | `DrawRope` | M2 T30 S1 shared `area.c` rope route | ROM-match complete | [T30 S1/P1 rope-chain evidence](../../history/M2-T30-area-object-rendering.md#s1p1-rom-rope-chain-and-three-target-delivery) |
| 4039 | `CoinMetatileData` | M2 T30 S2 shared `area.c` selector | ROM-match complete | [T30 S2/P1 coin-selector evidence](../../history/M2-T30-area-object-rendering.md#s2p1-coin-selector-and-three-target-delivery) |
| 4042 | `RowOfCoins` | M2 T30 S2 shared `area.c` selector | ROM-match complete | [T30 S2/P1 coin-selector evidence](../../history/M2-T30-area-object-rendering.md#s2p1-coin-selector-and-three-target-delivery) |
| 4049 | `C_ObjectRow` | M2 T30 S3 shared `area.c` castle-column chain | ROM-match complete | [T30 S3/P2 source and route evidence](../../history/M2-T30-area-object-rendering.md#s3p2-executed-original-rom-chain-evidence) |
| 4052 | `C_ObjectMetatile` | M2 T30 S3 shared `area.c` castle-column chain | ROM-match complete | [T30 S3/P2 source and route evidence](../../history/M2-T30-area-object-rendering.md#s3p2-executed-original-rom-chain-evidence) |
| 4055 | `CastleBridgeObj` | M2 T30 S3 shared `area.c` castle-column chain | ROM-match complete | [T30 S3/P2 source and route evidence](../../history/M2-T30-area-object-rendering.md#s3p2-executed-original-rom-chain-evidence) |
| 4060 | `AxeObj` | M2 T30 S3 shared `area.c` castle-column chain | ROM-match complete | [T30 S3/P2 source and route evidence](../../history/M2-T30-area-object-rendering.md#s3p2-executed-original-rom-chain-evidence) |
| 4064 | `ChainObj` | M2 T30 S3 shared `area.c` castle-column chain | ROM-match complete | [T30 S3/P2 source and route evidence](../../history/M2-T30-area-object-rendering.md#s3p2-executed-original-rom-chain-evidence) |
| 4070 | `EmptyBlock` | M2 T30 S3 shared `area.c` castle-column chain | ROM-match complete | [T30 S3/P2 source and route evidence](../../history/M2-T30-area-object-rendering.md#s3p2-executed-original-rom-chain-evidence) |
| 4074 | `ColObj` | M2 T30 S3 shared `area.c` castle-column chain | ROM-match complete | [T30 S3/P2 source and route evidence](../../history/M2-T30-area-object-rendering.md#s3p2-executed-original-rom-chain-evidence) |
| 4079 | `SolidBlockMetatiles` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4082 | `BrickMetatiles` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4086 | `RowOfBricks` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4091 | `DrawBricks` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4094 | `RowOfSolidBlocks` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4097 | `GetRow` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4099 | `DrawRow` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4104 | `ColumnOfBricks` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4109 | `ColumnOfSolidBlocks` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4112 | `GetRow2` | M2 T30 S4 shared `area.c` row/column chain | ROM-match complete | [T30 S4/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s4p1-block-rowcolumn-migration-and-rom-proof) |
| 4120 | `BulletBillCannon` | M2 T30 S5 shared `area.c` cannon chain | ROM-match complete | [T30 S5/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s5p1-cannon-geometry-registration-and-rom-proof) |
| 4135 | `SetupCannon` | M2 T30 S5 shared `area.c` cannon chain | ROM-match complete | [T30 S5/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s5p1-cannon-geometry-registration-and-rom-proof) |
| 4146 | `StrCOffset` | M2 T30 S5 shared `area.c` cannon chain | ROM-match complete | [T30 S5/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s5p1-cannon-geometry-registration-and-rom-proof) |
| 4151 | `StaircaseHeightData` | M2 T30 S6 shared `area.c` staircase chain | ROM-match complete | [T30 S6/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s6p1-staircase-chain-and-rom-proof) |
| 4154 | `StaircaseRowData` | M2 T30 S6 shared `area.c` staircase chain | ROM-match complete | [T30 S6/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s6p1-staircase-chain-and-rom-proof) |
| 4157 | `StaircaseObject` | M2 T30 S6 shared `area.c` staircase chain | ROM-match complete | [T30 S6/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s6p1-staircase-chain-and-rom-proof) |
| 4162 | `NextStair` | M2 T30 S6 shared `area.c` staircase chain | ROM-match complete | [T30 S6/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s6p1-staircase-chain-and-rom-proof) |
| 4172 | `Jumpspring` | M2 T30 S7 shared `area.c` jumpspring creation chain | ROM-match complete | [T30 S7/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s7p1-jumpspring-creation-and-rom-proof) |
| 4197 | `Hidden1UpBlock` | M2 T30 S8 shared `area.c` item-block selection chain | ROM-match complete | [T30 S8/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s8p1-item-block-selection-and-rom-proof) |
| 4204 | `QuestionBlock` | M2 T30 S8 shared `area.c` item-block selection chain | ROM-match complete | [T30 S8/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s8p1-item-block-selection-and-rom-proof) |
| 4208 | `BrickWithCoins` | M2 T30 S8 shared `area.c` item-block selection chain | ROM-match complete | [T30 S8/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s8p1-item-block-selection-and-rom-proof) |
| 4212 | `BrickWithItem` | M2 T30 S8 shared `area.c` item-block selection chain | ROM-match complete | [T30 S8/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s8p1-item-block-selection-and-rom-proof) |
| 4220 | `BWithL` | M2 T30 S8 shared `area.c` item-block selection chain | ROM-match complete | [T30 S8/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s8p1-item-block-selection-and-rom-proof) |
| 4223 | `DrawQBlk` | M2 T30 S8 shared `area.c` item-block selection chain | ROM-match complete | [T30 S8/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s8p1-item-block-selection-and-rom-proof) |
| 4228 | `GetAreaObjectID` | M2 T30 S8 shared `area.c` item-block selection chain | ROM-match complete | [T30 S8/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s8p1-item-block-selection-and-rom-proof) |
| 4233 | `ExitDecBlock` | M2 T30 S8 shared `area.c` item-block selection chain | ROM-match complete | [T30 S8/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s8p1-item-block-selection-and-rom-proof) |
| 4237 | `HoleMetatiles` | M2 T30 S9 shared `area.c` hole/UnderPart chain | ROM-match complete | [T30 S9/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s9p1-hole-registration-and-underpart-rom-proof) |
| 4240 | `Hole_Empty` | M2 T30 S9 shared `area.c` hole/UnderPart chain | ROM-match complete | [T30 S9/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s9p1-hole-registration-and-underpart-rom-proof) |
| 4265 | `StrWOffset` | M2 T30 S9 shared `area.c` hole/UnderPart chain | ROM-match complete | [T30 S9/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s9p1-hole-registration-and-underpart-rom-proof) |
| 4266 | `NoWhirlP` | M2 T30 S9 shared `area.c` hole/UnderPart chain | ROM-match complete | [T30 S9/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s9p1-hole-registration-and-underpart-rom-proof) |
| 4273 | `RenderUnderPart` | M2 T30 S9 shared `area.c` hole/UnderPart chain | ROM-match complete | [T30 S9/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s9p1-hole-registration-and-underpart-rom-proof) |
| 4289 | `DrawThisRow` | M2 T30 S9 shared `area.c` hole/UnderPart chain | ROM-match complete | [T30 S9/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s9p1-hole-registration-and-underpart-rom-proof) |
| 4290 | `WaitOneRow` | M2 T30 S9 shared `area.c` hole/UnderPart chain | ROM-match complete | [T30 S9/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s9p1-hole-registration-and-underpart-rom-proof) |
| 4296 | `ExitUPartR` | M2 T30 S9 shared `area.c` hole/UnderPart chain | ROM-match complete | [T30 S9/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s9p1-hole-registration-and-underpart-rom-proof) |
| 4300 | `ChkLrgObjLength` | M2 T30 S10 shared area-object helper owner | ROM-match complete | [T30 S10/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s10p1-common-helper-rom-proof) |
| 4303 | `ChkLrgObjFixedLength` | M2 T30 S10 shared area-object helper owner | ROM-match complete | [T30 S10/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s10p1-common-helper-rom-proof) |
| 4310 | `LenSet` | M2 T30 S10 shared area-object helper owner | ROM-match complete | [T30 S10/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s10p1-common-helper-rom-proof) |
| 4313 | `GetLrgObjAttrib` | M2 T30 S10 shared area-object helper owner | ROM-match complete | [T30 S10/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s10p1-common-helper-rom-proof) |
| 4326 | `GetAreaObjXPosition` | M2 T30 S10 shared area-object helper owner | ROM-match complete | [T30 S10/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s10p1-common-helper-rom-proof) |
| 4336 | `GetAreaObjYPosition` | M2 T30 S10 shared area-object helper owner | ROM-match complete | [T30 S10/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s10p1-common-helper-rom-proof) |
| 4349 | `BlockBufferAddr` | M2 T30 S13 shared block-address chain and initial-page producer | ROM-match complete | [T30 S13/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s13p1-block-address-and-initial-page-proof) |
| 4353 | `GetBlockBufferAddr` | M2 T30 S13 shared block-address chain and initial-page producer | ROM-match complete | [T30 S13/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s13p1-block-address-and-initial-page-proof) |
| 4376 | `AreaDataOfsLoopback` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 4381 | `LoadAreaPointer` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4384 | `GetAreaType` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4392 | `FindAreaPointer` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4402 | `GetAreaDataAddrs` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4434 | `StoreFore` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4472 | `StoreStyle` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4485 | `WorldAddrOffsets` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4491 | `AreaAddrOffsets` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4492 | `World1Areas` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4493 | `World2Areas` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4494 | `World3Areas` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4495 | `World4Areas` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4496 | `World5Areas` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4497 | `World6Areas` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4498 | `World7Areas` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4499 | `World8Areas` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4509 | `EnemyAddrHOffsets` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4512 | `EnemyDataAddrLow` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4520 | `EnemyDataAddrHigh` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4528 | `AreaDataHOffsets` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4531 | `AreaDataAddrLow` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4539 | `AreaDataAddrHigh` | M2 T30 S14 shared pointer/header chain and terminal caller | ROM-match complete | [T30 S14/P1 dual evidence](../../history/M2-T30-area-object-rendering.md#s14p1-pointer-header-and-caller-proof) |
| 4550 | `E_CastleArea1` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4558 | `E_CastleArea2` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4565 | `E_CastleArea3` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4574 | `E_CastleArea4` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4583 | `E_CastleArea5` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4589 | `E_CastleArea6` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4598 | `E_GroundArea1` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4606 | `E_GroundArea2` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4613 | `E_GroundArea3` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4619 | `E_GroundArea4` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4627 | `E_GroundArea5` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4636 | `E_GroundArea6` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4643 | `E_GroundArea7` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4650 | `E_GroundArea8` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4656 | `E_GroundArea9` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4662 | `E_GroundArea10` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4666 | `E_GroundArea11` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4674 | `E_GroundArea12` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4679 | `E_GroundArea13` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4687 | `E_GroundArea14` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4695 | `E_GroundArea15` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4700 | `E_GroundArea16` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4704 | `E_GroundArea17` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4714 | `E_GroundArea18` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4722 | `E_GroundArea19` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4731 | `E_GroundArea20` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4738 | `E_GroundArea21` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4743 | `E_GroundArea22` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4751 | `E_UndergroundArea1` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4760 | `E_UndergroundArea2` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4769 | `E_UndergroundArea3` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4777 | `E_WaterArea1` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4783 | `E_WaterArea2` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4791 | `E_WaterArea3` | M2 T19 S5 accepted enemy-data consumer, transfer-115 | mapped; evidence incomplete | [T30 S15 binding and counterexample](../../history/M2-T30-area-object-rendering.md#s15p1-enemy-data-bindings-and-accepted-consumer-debt) |
| 4799 | `L_CastleArea1` | M2 T30 S16 shared area parser | ROM-match complete | [S16 source binding and full parser routes](../../history/M2-T30-area-object-rendering.md#s16p1-castle-stream-consumption-and-loop-command-order) |
| 4814 | `L_CastleArea2` | M2 T30 S16 shared area parser | ROM-match complete | [S16 source binding and full parser routes](../../history/M2-T30-area-object-rendering.md#s16p1-castle-stream-consumption-and-loop-command-order) |
| 4832 | `L_CastleArea3` | M2 T30 S16 shared area parser | ROM-match complete | [S16 source binding and full parser routes](../../history/M2-T30-area-object-rendering.md#s16p1-castle-stream-consumption-and-loop-command-order) |
| 4849 | `L_CastleArea4` | M2 T30 S16 shared area parser | ROM-match complete | [S16 source binding and full parser routes](../../history/M2-T30-area-object-rendering.md#s16p1-castle-stream-consumption-and-loop-command-order) |
| 4865 | `L_CastleArea5` | M2 T30 S16 shared area parser | ROM-match complete | [S16 source binding and full parser routes](../../history/M2-T30-area-object-rendering.md#s16p1-castle-stream-consumption-and-loop-command-order) |
| 4884 | `L_CastleArea6` | M2 T30 S16 shared area parser | ROM-match complete | [S16 source binding and full parser routes](../../history/M2-T30-area-object-rendering.md#s16p1-castle-stream-consumption-and-loop-command-order) |
| 4900 | `L_GroundArea1` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 4915 | `L_GroundArea2` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 4931 | `L_GroundArea3` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 4944 | `L_GroundArea4` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 4963 | `L_GroundArea5` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 4980 | `L_GroundArea6` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 4995 | `L_GroundArea7` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5009 | `L_GroundArea8` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5027 | `L_GroundArea9` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5042 | `L_GroundArea10` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5048 | `L_GroundArea11` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5059 | `L_GroundArea12` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5066 | `L_GroundArea13` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5081 | `L_GroundArea14` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5096 | `L_GroundArea15` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5113 | `L_GroundArea16` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5123 | `L_GroundArea17` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5143 | `L_GroundArea18` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5160 | `L_GroundArea19` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5177 | `L_GroundArea20` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5191 | `L_GroundArea21` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5200 | `L_GroundArea22` | M2 T30 S17 shared area parser | ROM-match complete | [S17 full ground-stream evidence](../../history/M2-T30-area-object-rendering.md#s17p1-complete-ground-scene-consumption) |
| 5210 | `L_UndergroundArea1` | M2 T30 S18 shared area parser | ROM-match complete | [S18 full underground-stream evidence](../../history/M2-T30-area-object-rendering.md#s18p1-complete-underground-scene-consumption) |
| 5231 | `L_UndergroundArea2` | M2 T30 S18 shared area parser | ROM-match complete | [S18 full underground-stream evidence](../../history/M2-T30-area-object-rendering.md#s18p1-complete-underground-scene-consumption) |
| 5252 | `L_UndergroundArea3` | M2 T30 S18 shared area parser | ROM-match complete | [S18 full underground-stream evidence](../../history/M2-T30-area-object-rendering.md#s18p1-complete-underground-scene-consumption) |
| 5271 | `L_WaterArea1` | M2 T30 S19 shared area parser | ROM-match complete | [S19 full water-stream evidence](../../history/M2-T30-area-object-rendering.md#s19p1-complete-water-scene-consumption) |
| 5282 | `L_WaterArea2` | M2 T30 S19 shared area parser | ROM-match complete | [S19 full water-stream evidence](../../history/M2-T30-area-object-rendering.md#s19p1-complete-water-scene-consumption) |
| 5299 | `L_WaterArea3` | M2 T30 S19 shared area parser | ROM-match complete | [S19 full water-stream evidence](../../history/M2-T30-area-object-rendering.md#s19p1-complete-water-scene-consumption) |
| 5315 | `GameMode` | M2 T31 S1 shared dispatcher.c | ROM-match complete | [S1 entry dual evidence](../../history/M2-T31-game-dispatcher.md#s1p1-entry-chain-closure) |
| 5326 | `GameCoreRoutine` | M2 T31 S1 shared dispatcher.c | ROM-match complete | [S1 entry dual evidence](../../history/M2-T31-game-dispatcher.md#s1p1-entry-chain-closure) |
| 5336 | `GameEngine` | M2 T31 S2 shared game/engine.c | ROM-match complete | [S2 P4 scoped dual evidence](../../history/M2-T31-game-dispatcher.md#s2p4-parent-scheduler-and-warp-proof) |
| 5339 | `ProcELoop` | M2 T31 S2 shared game/engine_slots.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 5371 | `NoChgMus` | M2 T31 S2 shared engine / engine_tail | ROM-match complete | [S2 P1 dual proof and retained gaps](../../history/M2-T31-game-dispatcher.md#s2p1-verified-tail-partial-delivery) |
| 5377 | `CycleTwo` | M2 T31 S2 shared engine / engine_tail | ROM-match complete | [S2 P1 dual proof and retained gaps](../../history/M2-T31-game-dispatcher.md#s2p1-verified-tail-partial-delivery) |
| 5380 | `ClrPlrPal` | M2 T31 S2 shared engine / engine_tail | ROM-match complete | [S2 P1 dual proof and retained gaps](../../history/M2-T31-game-dispatcher.md#s2p1-verified-tail-partial-delivery) |
| 5381 | `SaveAB` | M2 T31 S2 shared engine / engine_tail | ROM-match complete | [S2 P1 dual proof and retained gaps](../../history/M2-T31-game-dispatcher.md#s2p1-verified-tail-partial-delivery) |
| 5385 | `UpdScrollVar` | M2 T31 S2 shared engine / engine_tail | ROM-match complete | [S2 P1 dual proof and retained gaps](../../history/M2-T31-game-dispatcher.md#s2p1-verified-tail-partial-delivery) |
| 5398 | `RunParser` | M2 T31 S2 shared engine / engine_tail | ROM-match complete | [S2 P1 dual proof and retained gaps](../../history/M2-T31-game-dispatcher.md#s2p1-verified-tail-partial-delivery) |
| 5399 | `ExitEng` | M2 T31 S2 shared engine / engine_tail | ROM-match complete | [S2 P1 dual proof and retained gaps](../../history/M2-T31-game-dispatcher.md#s2p1-verified-tail-partial-delivery) |
| 5403 | `ScrollHandler` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5422 | `ChkNearMid` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5427 | `ScrollScreen` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5451 | `InitScrlAmt` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5453 | `ChkPOffscr` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5463 | `KeepOnscr` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5475 | `InitPlatScrl` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5479 | `X_SubtracterData` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5482 | `OffscrJoypadBitsData` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5487 | `GetScreenPosition` | M2 T31 S3 shared game/scroll.c | ROM-match complete | [S3 P1 scroll-chain proof](../../history/M2-T31-game-dispatcher.md#s3p1-scroll-chain-proof) |
| 5499 | `GameRoutines` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5519 | `PlayerEntrance` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5532 | `ChkBehPipe` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5536 | `IntroEntr` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5541 | `EntrMode2` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5549 | `VineEntr` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5562 | `OffVine` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5567 | `PlayerRdy` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5575 | `ExitEntr` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5580 | `AutoControlPlayer` | M2 T31 S4 shared game/entry.c | ROM-match complete | [S4 P1 caller proof; child failures retained](../../history/M2-T31-game-dispatcher.md#s4p1-entry-chain-proof) |
| 5583 | `PlayerCtrlRoutine` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5595 | `DisJoyp` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5597 | `SaveJoyp` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5615 | `SizeChk` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5623 | `ChkMoveDir` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5629 | `SetMoveDir` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5630 | `PlayerSubs` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5649 | `PlayerHole` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5661 | `HoleDie` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5670 | `HoleBottom` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5672 | `ChkHoleX` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5680 | `ExitCtrl` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5682 | `CloudExit` | M2 T32 S1 shared game/player_control.c | ROM-match complete | [S1 P2 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s1p2-original-caller-proof) |
| 5691 | `Vine_AutoClimb` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5697 | `AutoClimb` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5702 | `SetEntr` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5708 | `VerticalPipeEntry` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5722 | `MovePlayerYAxis` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5730 | `SideExitPipeEntry` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5733 | `ChgAreaPipe` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5736 | `ChgAreaMode` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5740 | `ExitCAPipe` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5742 | `EnterSidePipe` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5751 | `RightPipe` | M2 T32 S2 shared game/player_transition.c | ROM-match complete | [S2 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s2-p1-original-transition-proof) |
| 5757 | `PlayerChangeSize` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5762 | `EndChgSize` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5765 | `ExitChgSize` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5769 | `PlayerInjuryBlink` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5776 | `ExitBlink` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5778 | `InitChangeSize` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5786 | `ExitBoth` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5791 | `PlayerDeath` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5797 | `DonePlayerTask` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5804 | `PlayerFireFlower` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5812 | `CyclePlayerPalette` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5821 | `ResetPalFireFlower` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5824 | `ResetPalStar` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5830 | `ExitDeath` | M2 T32 S3 shared game/player_modes.c | ROM-match complete | [S3 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s3-p1-original-timer-state-proof) |
| 5835 | `FlagpoleSlide` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5847 | `SlidePlayer` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5848 | `NoFPObj` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5853 | `Hidden1UpCoinAmts` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5856 | `PlayerEndLevel` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5868 | `ChkStop` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5874 | `InCastle` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5876 | `RdyNextA` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5888 | `NextArea` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5895 | `ExitNA` | M2 T32 S4 shared game/player_end_level.c | ROM-match complete | [S4 P1 caller proof; actual-child failures retained](../../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof) |
| 5899 | `PlayerMovementSubs` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5907 | `SetCrouch` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5908 | `ProcMove` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5916 | `MoveSubs` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5923 | `NoMoveSub` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5928 | `OnGroundStateSub` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5933 | `GndMove` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5940 | `FallingSub` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5947 | `JumpSwimSub` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5959 | `DumpFall` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5961 | `ProcSwim` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5969 | `LRWater` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5972 | `LRAir` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5975 | `JSMove` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5982 | `ExitMov1` | M2 T33 S1 shared game/player_movement.c | ROM-match complete | [S1 original movement proof; child gaps retained](../../history/M2-T33-player-movement-state.md#s1-original-movement-proof) |
| 5986 | `ClimbAdderLow` | M2 T33 S2 shared game/player.c | ROM-match complete | [S2 original climbing proof](../../history/M2-T33-player-movement-state.md#s2-original-climbing-proof) |
| 5988 | `ClimbAdderHigh` | M2 T33 S2 shared game/player.c | ROM-match complete | [S2 original climbing proof](../../history/M2-T33-player-movement-state.md#s2-original-climbing-proof) |
| 5991 | `ClimbingSub` | M2 T33 S2 shared game/player.c | ROM-match complete | [S2 original climbing proof](../../history/M2-T33-player-movement-state.md#s2-original-climbing-proof) |
| 6000 | `MoveOnVine` | M2 T33 S2 shared game/player.c | ROM-match complete | [S2 original climbing proof](../../history/M2-T33-player-movement-state.md#s2-original-climbing-proof) |
| 6019 | `ClimbFD` | M2 T33 S2 shared game/player.c | ROM-match complete | [S2 original climbing proof](../../history/M2-T33-player-movement-state.md#s2-original-climbing-proof) |
| 6022 | `CSetFDir` | M2 T33 S2 shared game/player.c | ROM-match complete | [S2 original climbing proof](../../history/M2-T33-player-movement-state.md#s2-original-climbing-proof) |
| 6032 | `ExitCSub` | M2 T33 S2 shared game/player.c | ROM-match complete | [S2 original climbing proof](../../history/M2-T33-player-movement-state.md#s2-original-climbing-proof) |
| 6033 | `InitCSTimer` | M2 T33 S2 shared game/player.c | ROM-match complete | [S2 original climbing proof](../../history/M2-T33-player-movement-state.md#s2-original-climbing-proof) |
| 6039 | `JumpMForceData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6042 | `FallMForceData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6045 | `PlayerYSpdData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6048 | `InitMForceData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6051 | `MaxLeftXSpdData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6054 | `MaxRightXSpdData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6058 | `FrictionData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6061 | `Climb_Y_SpeedData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6064 | `Climb_Y_MForceData` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6067 | `PlayerPhysicsSub` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6079 | `ProcClimb` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6086 | `SetCAnim` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6089 | `CheckForJumping` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6097 | `NoJump` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6099 | `ProcJumping` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6109 | `InitJS` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6133 | `ChkWtr` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6141 | `GetYPhy` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6159 | `PJumpSnd` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6163 | `SJumpSnd` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6164 | `X_Physics` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6172 | `ProcPRun` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6184 | `ChkRFast` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6191 | `FastXSp` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6193 | `SetRTmr` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6195 | `GetXPhy` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6201 | `GetXPhy2` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6213 | `ExitPhy` | M2 T33 S3 shared game/player.c | ROM-match complete | [S3 original physics proof](../../history/M2-T33-player-movement-state.md#s3-original-physics-proof) |
| 6217 | `PlayerAnimTmrData` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6220 | `GetPlayerAnimSpeed` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6229 | `ChkSkid` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6236 | `SetRunSpd` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6238 | `ProcSkid` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6246 | `SetAnimSpd` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6252 | `ImposeFriction` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6260 | `JoypFrict` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6262 | `LeftFrict` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6274 | `RghtFrict` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6285 | `XSpdSign` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6290 | `SetAbsSpd` | M2 T33 S4 shared game/player.c | ROM-match complete | [S4 animation/friction proof](../../history/M2-T33-player-movement-state.md#s4-original-animation-and-friction-proof) |
| 6298 | `ProcFireball_Bubble` | M2 T34 S1 shared game/fireball/fireball_spawn.c | ROM-match complete | [S1 dispatch caller proof; child gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s1-original-dispatch-proof) |
| 6330 | `ProcFireballs` | M2 T34 S1 shared game/fireball/fireball_spawn.c | ROM-match complete | [S1 dispatch caller proof; child gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s1-original-dispatch-proof) |
| 6336 | `ProcAirBubbles` | M2 T34 S1 shared game/fireball/fireball_spawn.c | ROM-match complete | [S1 dispatch caller proof; child gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s1-original-dispatch-proof) |
| 6340 | `BublLoop` | M2 T34 S1 shared game/fireball/fireball_spawn.c | ROM-match complete | [S1 dispatch caller proof; child gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s1-original-dispatch-proof) |
| 6347 | `BublExit` | M2 T34 S1 shared game/fireball/fireball_spawn.c | ROM-match complete | [S1 dispatch caller proof; child gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s1-original-dispatch-proof) |
| 6349 | `FireballXSpdData` | M2 T34 S2 shared game/fireball/fireball_core.c | ROM-match complete | [S2 core caller proof; graphics gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s2-original-core-proof) |
| 6352 | `FireballObjCore` | M2 T34 S2 shared game/fireball/fireball_core.c | ROM-match complete | [S2 core caller proof; graphics gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s2-original-core-proof) |
| 6380 | `RunFB` | M2 T34 S2 shared game/fireball/fireball_core.c | ROM-match complete | [S2 core caller proof; graphics gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s2-original-core-proof) |
| 6401 | `EraseFB` | M2 T34 S2 shared game/fireball/fireball_core.c | ROM-match complete | [S2 core caller proof; graphics gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s2-original-core-proof) |
| 6403 | `NoFBall` | M2 T34 S2 shared game/fireball/fireball_core.c | ROM-match complete | [S2 core caller proof; graphics gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s2-original-core-proof) |
| 6405 | `FireballExplosion` | M2 T34 S2 shared game/fireball/fireball_core.c | ROM-match complete | [S2 core caller proof; graphics gaps retained](../../history/M2-T34-fireball-dispatch-core.md#s2-original-core-proof) |
| 6409 | `BubbleCheck` | M2 T35 S1 shared game/fireball/bubble.c | ROM-match complete | [S1 actual bubble-chain proof](../../history/M2-T35-bubbles-timer-warp.md#s1-original-bubble-proof) |
| 6419 | `SetupBubble` | M2 T35 S1 shared game/fireball/bubble.c | ROM-match complete | [S1 actual bubble-chain proof](../../history/M2-T35-bubbles-timer-warp.md#s1-original-bubble-proof) |
| 6425 | `PosBubl` | M2 T35 S1 shared game/fireball/bubble.c | ROM-match complete | [S1 actual bubble-chain proof](../../history/M2-T35-bubbles-timer-warp.md#s1-original-bubble-proof) |
| 6440 | `MoveBubl` | M2 T35 S1 shared game/fireball/bubble.c | ROM-match complete | [S1 actual bubble-chain proof](../../history/M2-T35-bubbles-timer-warp.md#s1-original-bubble-proof) |
| 6450 | `Y_Bubl` | M2 T35 S1 shared game/fireball/bubble.c | ROM-match complete | [S1 actual bubble-chain proof](../../history/M2-T35-bubbles-timer-warp.md#s1-original-bubble-proof) |
| 6451 | `ExitBubl` | M2 T35 S1 shared game/fireball/bubble.c | ROM-match complete | [S1 actual bubble-chain proof](../../history/M2-T35-bubbles-timer-warp.md#s1-original-bubble-proof) |
| 6453 | `Bubble_MForceData` | M2 T35 S1 shared game/fireball/bubble.c | ROM-match complete | [S1 actual bubble-chain proof](../../history/M2-T35-bubbles-timer-warp.md#s1-original-bubble-proof) |
| 6456 | `BubbleTimerData` | M2 T35 S1 shared game/fireball/bubble.c | ROM-match complete | [S1 actual bubble-chain proof](../../history/M2-T35-bubbles-timer-warp.md#s1-original-bubble-proof) |
| 6461 | `RunGameTimer` | M2 T35 S2 shared game/timer.c | ROM-match complete | [S2 timer caller proof; injury gap retained](../../history/M2-T35-bubbles-timer-warp.md#s2-original-timer-proof) |
| 6486 | `ResGTCtrl` | M2 T35 S2 shared game/timer.c | ROM-match complete | [S2 timer caller proof; injury gap retained](../../history/M2-T35-bubbles-timer-warp.md#s2-original-timer-proof) |
| 6494 | `TimeUpOn` | M2 T35 S2 shared game/timer.c | ROM-match complete | [S2 timer caller proof; injury gap retained](../../history/M2-T35-bubbles-timer-warp.md#s2-original-timer-proof) |
| 6497 | `ExGTimer` | M2 T35 S2 shared game/timer.c | ROM-match complete | [S2 timer caller proof; injury gap retained](../../history/M2-T35-bubbles-timer-warp.md#s2-original-timer-proof) |
| 6501 | `WarpZoneObject` | M2 T31 S2 shared game/enemy/core.c | ROM-match complete | [S2 P4 scoped dual evidence](../../history/M2-T31-game-dispatcher.md#s2p4-parent-scheduler-and-warp-proof) |
| 6519 | `ProcessWhirlpools` | M2 T31 S2 shared game/whirlpool.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6526 | `WhLoop` | M2 T31 S2 shared game/whirlpool.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6546 | `NextWh` | M2 T31 S2 shared game/whirlpool.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6548 | `ExitWh` | M2 T31 S2 shared game/whirlpool.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6550 | `WhirlpoolActivate` | M2 T31 S2 shared game/whirlpool.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6577 | `LeftWh` | M2 T31 S2 shared game/whirlpool.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6586 | `SetPWh` | M2 T31 S2 shared game/whirlpool.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6587 | `WhPull` | M2 T31 S2 shared game/whirlpool.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6598 | `FlagpoleScoreMods` | T20 responsibility (implementation not certified) | ROM-match complete | [T22 S5/P1 flagpole-chain evidence](../../proposals/m2/blocks-items-misc.md#s5p1-flagpole-parser-score-and-graphics-route) |
| 6601 | `FlagpoleScoreDigits` | T20 responsibility (implementation not certified) | ROM-match complete | [T22 S5/P1 flagpole-chain evidence](../../proposals/m2/blocks-items-misc.md#s5p1-flagpole-parser-score-and-graphics-route) |
| 6604 | `FlagpoleRoutine` | T22 responsibility; `area.c`: object decode; `oam/flagpole_gfx.c`: start/step | ROM-match complete | [T22 S5/P1 flagpole-chain evidence](../../proposals/m2/blocks-items-misc.md#s5p1-flagpole-parser-score-and-graphics-route) |
| 6635 | `SkipScore` | T20 responsibility (implementation not certified) | ROM-match complete | [T22 S5/P1 flagpole-chain evidence](../../proposals/m2/blocks-items-misc.md#s5p1-flagpole-parser-score-and-graphics-route) |
| 6636 | `GiveFPScr` | T20 responsibility (implementation not certified) | ROM-match complete | [T22 S5/P1 flagpole-chain evidence](../../proposals/m2/blocks-items-misc.md#s5p1-flagpole-parser-score-and-graphics-route) |
| 6643 | `FPGfx` | T20 responsibility (implementation not certified) | ROM-match complete | [T22 S5/P1 flagpole-chain evidence](../../proposals/m2/blocks-items-misc.md#s5p1-flagpole-parser-score-and-graphics-route) |
| 6646 | `ExitFlagP` | T20 responsibility (implementation not certified) | ROM-match complete | [T22 S5/P1 flagpole-chain evidence](../../proposals/m2/blocks-items-misc.md#s5p1-flagpole-parser-score-and-graphics-route) |
| 6650 | `Jumpspring_Y_PosData` | M2 T35 S3 shared game/jumpspring.c | ROM-match complete | [S3 jumpspring caller proof; graphics gap retained](../../history/M2-T35-bubbles-timer-warp.md#s3-original-jumpspring-proof) |
| 6653 | `JumpspringHandler` | M2 T35 S3 shared game/jumpspring.c | ROM-match complete | [S3 jumpspring caller proof; graphics gap retained](../../history/M2-T35-bubbles-timer-warp.md#s3-original-jumpspring-proof) |
| 6667 | `DownJSpr` | M2 T35 S3 shared game/jumpspring.c | ROM-match complete | [S3 jumpspring caller proof; graphics gap retained](../../history/M2-T35-bubbles-timer-warp.md#s3-original-jumpspring-proof) |
| 6669 | `PosJSpr` | M2 T35 S3 shared game/jumpspring.c | ROM-match complete | [S3 jumpspring caller proof; graphics gap retained](../../history/M2-T35-bubbles-timer-warp.md#s3-original-jumpspring-proof) |
| 6682 | `BounceJS` | M2 T35 S3 shared game/jumpspring.c | ROM-match complete | [S3 jumpspring caller proof; graphics gap retained](../../history/M2-T35-bubbles-timer-warp.md#s3-original-jumpspring-proof) |
| 6688 | `DrawJSpr` | M2 T35 S3 shared game/jumpspring.c | ROM-match complete | [S3 jumpspring caller proof; graphics gap retained](../../history/M2-T35-bubbles-timer-warp.md#s3-original-jumpspring-proof) |
| 6698 | `ExJSpring` | M2 T35 S3 shared game/jumpspring.c | ROM-match complete | [S3 jumpspring caller proof; graphics gap retained](../../history/M2-T35-bubbles-timer-warp.md#s3-original-jumpspring-proof) |
| 6702 | `Setup_Vine` | M2 T35 S4 shared game/vine.c | ROM-match complete | [S4 actual vine setup proof](../../history/M2-T35-bubbles-timer-warp.md#s4-original-vine-setup-proof) |
| 6716 | `NextVO` | M2 T35 S4 shared game/vine.c | ROM-match complete | [S4 actual vine setup proof](../../history/M2-T35-bubbles-timer-warp.md#s4-original-vine-setup-proof) |
| 6727 | `VineHeightData` | M2 T35 S4 shared game/vine.c | ROM-match complete | [S4 actual vine setup proof](../../history/M2-T35-bubbles-timer-warp.md#s4-original-vine-setup-proof) |
| 6730 | `VineObjectHandler` | M2 T36 S1 shared game/vine.c | ROM-match complete | [S1 vine actor caller proof; graphics gap retained](../../history/M2-T36-misc-object-chains.md#s1-original-vine-actor-proof) |
| 6746 | `RunVSubs` | M2 T36 S1 shared game/vine.c | ROM-match complete | [S1 vine actor caller proof; graphics gap retained](../../history/M2-T36-misc-object-chains.md#s1-original-vine-actor-proof) |
| 6752 | `VDrawLoop` | M2 T36 S1 shared game/vine.c | ROM-match complete | [S1 vine actor caller proof; graphics gap retained](../../history/M2-T36-misc-object-chains.md#s1-original-vine-actor-proof) |
| 6760 | `KillVine` | M2 T36 S1 shared game/vine.c | ROM-match complete | [S1 vine actor caller proof; graphics gap retained](../../history/M2-T36-misc-object-chains.md#s1-original-vine-actor-proof) |
| 6766 | `WrCMTile` | M2 T36 S1 shared game/vine.c | ROM-match complete | [S1 vine actor caller proof; graphics gap retained](../../history/M2-T36-misc-object-chains.md#s1-original-vine-actor-proof) |
| 6780 | `ExitVH` | M2 T36 S1 shared game/vine.c | ROM-match complete | [S1 vine actor caller proof; graphics gap retained](../../history/M2-T36-misc-object-chains.md#s1-original-vine-actor-proof) |
| 6785 | `CannonBitmasks` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6788 | `ProcessCannons` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6792 | `ThreeSChk` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6809 | `FireCannon` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6832 | `Chk_BB` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6840 | `Next3Slt` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6842 | `ExCannon` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6846 | `BulletBillXSpdData` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6849 | `BulletBillHandler` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6862 | `SetupBB` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6876 | `ChkDSte` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6880 | `BBFly` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6881 | `RunBBSubs` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6886 | `KillBB` | M2 T31 S2 shared game/cannon.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 6891 | `HammerEnemyOfsData` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6895 | `HammerXSpdData` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6898 | `SpawnHammerObj` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6904 | `SetMOfs` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6919 | `NoHammer` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6928 | `ProcHammerObj` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6952 | `SetHSpd` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6962 | `SetHPos` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6977 | `RunAllH` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6978 | `RunHSubs` | M2 T36 S2 shared game/hammer.c | ROM-match complete | [S2 hammer lifecycle proof](../../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof) |
| 6988 | `CoinBlock` | M2 T36 S3 shared game/coin.c | ROM-match complete | [S3 coin allocation caller proof](../../history/M2-T36-misc-object-chains.md#s3-original-coin-allocation-proof) |
| 7000 | `SetupJumpCoin` | M2 T36 S3 shared game/coin.c | ROM-match complete | [S3 coin allocation caller proof](../../history/M2-T36-misc-object-chains.md#s3-original-coin-allocation-proof) |
| 7014 | `JCoinC` | M2 T36 S3 shared game/coin.c | ROM-match complete | [S3 coin allocation caller proof](../../history/M2-T36-misc-object-chains.md#s3-original-coin-allocation-proof) |
| 7025 | `FindEmptyMiscSlot` | M2 T36 S3 shared game/coin.c | ROM-match complete | [S3 coin allocation caller proof](../../history/M2-T36-misc-object-chains.md#s3-original-coin-allocation-proof) |
| 7027 | `FMiscLoop` | M2 T36 S3 shared game/coin.c | ROM-match complete | [S3 coin allocation caller proof](../../history/M2-T36-misc-object-chains.md#s3-original-coin-allocation-proof) |
| 7033 | `UseMiscS` | M2 T36 S3 shared game/coin.c | ROM-match complete | [S3 coin allocation caller proof](../../history/M2-T36-misc-object-chains.md#s3-original-coin-allocation-proof) |
| 7038 | `MiscObjectsCore` | M2 T36 S4 shared game/misc.c | ROM-match complete | [S4 misc lifetime proof](../../history/M2-T36-misc-object-chains.md#s4-original-misc-lifetime-proof) |
| 7040 | `MiscLoop` | M2 T36 S4 shared game/misc.c | ROM-match complete | [S4 misc lifetime proof](../../history/M2-T36-misc-object-chains.md#s4-original-misc-lifetime-proof) |
| 7053 | `ProcJumpCoin` | M2 T36 S4 shared game/misc.c | ROM-match complete | [S4 misc lifetime proof](../../history/M2-T36-misc-object-chains.md#s4-original-misc-lifetime-proof) |
| 7071 | `JCoinRun` | M2 T36 S4 shared game/misc.c | ROM-match complete | [S4 misc lifetime proof](../../history/M2-T36-misc-object-chains.md#s4-original-misc-lifetime-proof) |
| 7088 | `RunJCSubs` | M2 T36 S4 shared game/misc.c | ROM-match complete | [S4 misc lifetime proof](../../history/M2-T36-misc-object-chains.md#s4-original-misc-lifetime-proof) |
| 7093 | `MiscLoopBack` | M2 T36 S4 shared game/misc.c | ROM-match complete | [S4 misc lifetime proof](../../history/M2-T36-misc-object-chains.md#s4-original-misc-lifetime-proof) |
| 7100 | `CoinTallyOffsets` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7103 | `ScoreOffsets` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7106 | `StatusBarNybbles` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7109 | `GiveOneCoin` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7125 | `CoinPoints` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7129 | `AddToScore` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7134 | `GetSBNybbles` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7138 | `UpdateNumber` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7145 | `NoZSup` | M2 T36 S5 shared game/score.c | ROM-match complete | [S5 score and HUD proof](../../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof) |
| 7150 | `SetupPowerUp` | M2 T36 S6 shared game/power_up_init.c | ROM-match complete | [S6 power-up initialization proof](../../history/M2-T36-misc-object-chains.md#s6-original-power-up-initialization-proof) |
| 7163 | `PwrUpJmp` | M2 T36 S6 shared game/power_up_init.c | ROM-match complete | [S6 power-up initialization proof](../../history/M2-T36-misc-object-chains.md#s6-original-power-up-initialization-proof) |
| 7175 | `StrType` | M2 T36 S6 shared game/power_up_init.c | ROM-match complete | [S6 power-up initialization proof](../../history/M2-T36-misc-object-chains.md#s6-original-power-up-initialization-proof) |
| 7176 | `PutBehind` | M2 T36 S6 shared game/power_up_init.c | ROM-match complete | [S6 power-up initialization proof](../../history/M2-T36-misc-object-chains.md#s6-original-power-up-initialization-proof) |
| 7184 | `PowerUpObjHandler` | M2 T37 S1 shared game/power_up.c | ROM-match complete | [S1 actor proof](../../history/M2-T37-power-up-block-movement.md#s1-original-power-up-actor-proof) |
| 7202 | `ShroomM` | M2 T37 S1 shared game/power_up.c | ROM-match complete | [S1 actor proof](../../history/M2-T37-power-up-block-movement.md#s1-original-power-up-actor-proof) |
| 7206 | `GrowThePowerUp` | M2 T37 S1 shared game/power_up.c | ROM-match complete | [S1 actor proof](../../history/M2-T37-power-up-block-movement.md#s1-original-power-up-actor-proof) |
| 7223 | `ChkPUSte` | M2 T37 S1 shared game/power_up.c | ROM-match complete | [S1 actor proof](../../history/M2-T37-power-up-block-movement.md#s1-original-power-up-actor-proof) |
| 7226 | `RunPUSubs` | M2 T37 S1 shared game/power_up.c | ROM-match complete | [S1 actor proof](../../history/M2-T37-power-up-block-movement.md#s1-original-power-up-actor-proof) |
| 7232 | `ExitPUp` | M2 T37 S1 shared game/power_up.c | ROM-match complete | [S1 actor proof](../../history/M2-T37-power-up-block-movement.md#s1-original-power-up-actor-proof) |
| 7241 | `BlockYPosAdderData` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7244 | `PlayerHeadCollision` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7251 | `DBlockSte` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7265 | `ChkBrick` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7274 | `StartBTmr` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7279 | `ContBTmr` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7282 | `PutOldMT` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7283 | `PutMTileB` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7297 | `SmallBP` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7298 | `BigBP` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7308 | `Unbreak` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7309 | `InvOBit` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7316 | `InitBlock_XY_Pos` | M2 T37 S2 shared game/blocks/head.c | ROM-match complete | [S2 head-hit proof](../../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof) |
| 7332 | `BumpBlock` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7349 | `BlockCode` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7363 | `MushFlowerBlock` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7367 | `StarBlock` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7371 | `ExtraLifeMushBlock` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7376 | `VineBlock` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7381 | `ExitBlockChk` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7386 | `BrickQBlockMetatiles` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7393 | `BlockBumpedChk` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7395 | `BumpChkLoop` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7400 | `MatchBump` | M2 T37 S3 shared game/blocks/bump.c | ROM-match complete | [S3 block content proof](../../history/M2-T37-power-up-block-movement.md#s3-original-block-content-and-lookup-proof) |
| 7404 | `BrickShatter` | M2 T37 S4 shared game/blocks/chunks.c | ROM-match complete | [S4 shatter and chunk proof](../../history/M2-T37-power-up-block-movement.md#s4-original-shatter-top-coin-and-chunk-proof) |
| 7420 | `CheckTopOfBlock` | M2 T37 S4 shared game/blocks/chunks.c | ROM-match complete | [S4 shatter and chunk proof](../../history/M2-T37-power-up-block-movement.md#s4-original-shatter-top-coin-and-chunk-proof) |
| 7437 | `TopEx` | M2 T37 S4 shared game/blocks/chunks.c | ROM-match complete | [S4 shatter and chunk proof](../../history/M2-T37-power-up-block-movement.md#s4-original-shatter-top-coin-and-chunk-proof) |
| 7441 | `SpawnBrickChunks` | M2 T37 S4 shared game/blocks/chunks.c | ROM-match complete | [S4 shatter and chunk proof](../../history/M2-T37-power-up-block-movement.md#s4-original-shatter-top-coin-and-chunk-proof) |
| 7468 | `BlockObjectsCore` | M2 T37 S5 shared game/blocks/lifetime.c | ROM-match complete | [S5 lifetime caller proof](../../history/M2-T37-power-up-block-movement.md#s5-original-block-lifetime-proof) |
| 7500 | `ChkTop` | M2 T37 S5 shared game/blocks/lifetime.c | ROM-match complete | [S5 lifetime caller proof](../../history/M2-T37-power-up-block-movement.md#s5-original-block-lifetime-proof) |
| 7506 | `BouncingBlockHandler` | M2 T37 S5 shared game/blocks/lifetime.c | ROM-match complete | [S5 lifetime caller proof](../../history/M2-T37-power-up-block-movement.md#s5-original-block-lifetime-proof) |
| 7519 | `KillBlock` | M2 T37 S5 shared game/blocks/lifetime.c | ROM-match complete | [S5 lifetime caller proof](../../history/M2-T37-power-up-block-movement.md#s5-original-block-lifetime-proof) |
| 7520 | `UpdSte` | M2 T37 S5 shared game/blocks/lifetime.c | ROM-match complete | [S5 lifetime caller proof](../../history/M2-T37-power-up-block-movement.md#s5-original-block-lifetime-proof) |
| 7527 | `BlockObjMT_Updater` | M2 T37 S6 shared game/blocks/replacement.c | ROM-match complete | [S6 replacement caller proof](../../history/M2-T37-power-up-block-movement.md#s6-original-block-replacement-proof) |
| 7529 | `UpdateLoop` | M2 T37 S6 shared game/blocks/replacement.c | ROM-match complete | [S6 replacement caller proof](../../history/M2-T37-power-up-block-movement.md#s6-original-block-replacement-proof) |
| 7546 | `NextBUpd` | M2 T37 S6 shared game/blocks/replacement.c | ROM-match complete | [S6 replacement caller proof](../../history/M2-T37-power-up-block-movement.md#s6-original-block-replacement-proof) |
| 7555 | `MoveEnemyHorizontally` | M2 T37 S7 shared game/world/movement.c and player.c | ROM-match complete | [S7 horizontal proof](../../history/M2-T37-power-up-block-movement.md#s7-original-horizontal-movement-proof) |
| 7561 | `MovePlayerHorizontally` | M2 T37 S7 shared game/world/movement.c and player.c | ROM-match complete | [S7 horizontal proof](../../history/M2-T37-power-up-block-movement.md#s7-original-horizontal-movement-proof) |
| 7566 | `MoveObjectHorizontally` | M2 T37 S7 shared game/world/movement.c and player.c | ROM-match complete | [S7 horizontal proof](../../history/M2-T37-power-up-block-movement.md#s7-original-horizontal-movement-proof) |
| 7581 | `SaveXSpd` | M2 T37 S7 shared game/world/movement.c and player.c | ROM-match complete | [S7 horizontal proof](../../history/M2-T37-power-up-block-movement.md#s7-original-horizontal-movement-proof) |
| 7586 | `UseAdder` | M2 T37 S7 shared game/world/movement.c and player.c | ROM-match complete | [S7 horizontal proof](../../history/M2-T37-power-up-block-movement.md#s7-original-horizontal-movement-proof) |
| 7604 | `ExXMove` | M2 T37 S7 shared game/world/movement.c and player.c | ROM-match complete | [S7 horizontal proof](../../history/M2-T37-power-up-block-movement.md#s7-original-horizontal-movement-proof) |
| 7611 | `MovePlayerVertically` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7617 | `NoJSChk` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7624 | `MoveD_EnemyVertically` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7630 | `MoveFallingPlatform` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7632 | `ContVMove` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7636 | `MoveRedPTroopaDown` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7640 | `MoveRedPTroopaUp` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7643 | `MoveRedPTroopa` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7656 | `MoveDropPlatform` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7660 | `MoveEnemySlowVert` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7662 | `SetMdMax` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7667 | `MoveJ_EnemyVertically` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7669 | `SetHiMax` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7670 | `SetXMoveAmt` | M2 T37 S8 shared player.c and enemy/movement.c | ROM-match complete | [S8 adapter proof](../../history/M2-T37-power-up-block-movement.md#s8-original-vertical-adapter-proof) |
| 7678 | `MaxSpdBlockData` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7681 | `ResidualGravityCode` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) (static/native residual entry) |
| 7685 | `ImposeGravityBlock` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7691 | `ImposeGravitySprObj` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7698 | `MovePlatformDown` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7702 | `MovePlatformUp` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7711 | `SetDplSpd` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7719 | `RedPTroopaGrav` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7729 | `ImposeGravity` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7739 | `AlterYP` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7761 | `ChkUpM` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7784 | `ExVMove` | M2 T37 S9 shared world/gravity.c | ROM-match complete | [S9 gravity proof](../../history/M2-T37-power-up-block-movement.md#s9-original-common-gravity-proof) |
| 7788 | `EnemiesAndLoopsCore` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7796 | `ChkAreaTsk` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7801 | `ChkBowserF` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7807 | `ExitELCore` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7812 | `LoopCmdWorldNumber` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7815 | `LoopCmdPageNumber` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7818 | `LoopCmdYPosition` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7821 | `ExecGameLoopback` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7851 | `ProcLoopCommand` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7857 | `FindLoop` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7875 | `IncMLoop` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7883 | `WrongChk` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7886 | `DoLpBack` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7888 | `InitMLp` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7891 | `InitLCmd` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7896 | `ChkEnemyFrenzy` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 7911 | `ProcessEnemyData` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 7918 | `CheckEndofBuffer` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 7931 | `CheckRightBounds` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 7950 | `CheckPageCtrlRow` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 7967 | `PositionEnemyObj` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 7983 | `CheckRightExtBounds` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8006 | `CheckForEnemyGroup` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8014 | `BuzzyBeetleMutate` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8020 | `StrID` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8028 | `CheckFrenzyBuffer` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8035 | `StrFre` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8037 | `InitEnemyObject` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8041 | `ExEPar` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8043 | `DoGroup` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8046 | `ParseRow0e` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8064 | `NotUse` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8066 | `CheckThreeBytes` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8072 | `Inc3B` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8073 | `Inc2B` | M2 T38 S2 shared enemy/stream.c | ROM-match complete | [S2 parser proof](../../history/M2-T38-enemy-stream-initialization.md#s2-original-enemy-parser-proof); scoped caller proof, child gaps retained |
| 8080 | `CheckpointEnemyID` | M2 T38 S3 shared enemy/init.c | ROM-match complete | [S3 vector proof](../../history/M2-T38-enemy-stream-initialization.md#s3-original-initializer-vector-proof); exact caller boundaries, child gaps retained |
| 8092 | `InitEnemyRoutines` | M2 T38 S3 shared enemy/init.c | ROM-match complete | [S3 vector proof](../../history/M2-T38-enemy-stream-initialization.md#s3-original-initializer-vector-proof); exact caller boundaries, child gaps retained |
| 8158 | `NoInitCode` | M2 T38 S3 shared enemy/init.c | ROM-match complete | [S3 vector proof](../../history/M2-T38-enemy-stream-initialization.md#s3-original-initializer-vector-proof); exact caller boundaries, child gaps retained |
| 8163 | `InitGoomba` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8169 | `InitPodoboo` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8181 | `InitRetainerObj` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8188 | `NormalXSpdData` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8191 | `InitNormalEnemy` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8196 | `GetESpd` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8197 | `SetESpd` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8202 | `InitRedKoopa` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8210 | `HBroWalkingTimerData` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8213 | `InitHammerBro` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8225 | `InitHorizFlySwimEnemy` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8231 | `InitBloober` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8234 | `SmallBBox` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8239 | `InitRedPTroopa` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8245 | `GetCent` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8248 | `TallBBox` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8249 | `SetBBox` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8252 | `InitVStf` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8259 | `InitBulletBill` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8268 | `InitCheepCheep` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8279 | `InitLakitu` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8283 | `SetupLakitu` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8289 | `KillLakitu` | M2 T38 S4 shared enemy/init_targets.c | ROM-match complete | [S4 common initializer proof](../../history/M2-T38-enemy-stream-initialization.md#s4-original-common-initializer-proof); actual source comparisons and exact write footprints |
| 8295 | `PRDiffAdjustData` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8300 | `LakituAndSpinyHandler` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8308 | `ChkLak` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8318 | `ChkNoEn` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8323 | `CreateL` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8330 | `RetEOfs` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8331 | `ExLSHand` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8335 | `CreateSpiny` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8355 | `DifLoop` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8376 | `UsePosv` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8377 | `SetSpSpd` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8383 | `SpinyRte` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8390 | `ChpChpEx` | M2 T38 S5 shared enemy/frenzy.c | ROM-match complete | [S5 Lakitu/Spiny caller proof](../../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof); child differences separately retained |
| 8394 | `FirebarSpinSpdData` | M2 T38 S6 shared enemy/init_targets.c | ROM-match complete | [S6 actual firebar/duplicate proof](../../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof); actual original RAM and full write footprints |
| 8397 | `FirebarSpinDirData` | M2 T38 S6 shared enemy/init_targets.c | ROM-match complete | [S6 actual firebar/duplicate proof](../../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof); actual original RAM and full write footprints |
| 8400 | `InitLongFirebar` | M2 T38 S6 shared enemy/init_targets.c | ROM-match complete | [S6 actual firebar/duplicate proof](../../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof); actual original RAM and full write footprints |
| 8403 | `InitShortFirebar` | M2 T38 S6 shared enemy/init_targets.c | ROM-match complete | [S6 actual firebar/duplicate proof](../../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof); actual original RAM and full write footprints |
| 8430 | `FlyCCXPositionData` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8436 | `FlyCCXSpeedData` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8441 | `FlyCCTimerData` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8444 | `InitFlyingCheepCheep` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8457 | `MaxCC` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8473 | `GSeed` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8483 | `RSeed` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8503 | `D2XPos1` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8513 | `D2XPos2` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8519 | `FinCCSt` | M2 T38 S7 shared enemy/frenzy.c | ROM-match complete | [S7 actual flying-fish proof](../../history/M2-T38-enemy-stream-initialization.md#s7-original-flying-fish-proof); all source branches and data consumers |
| 8529 | `InitBowser` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8551 | `DuplicateEnemyObj` | M2 T38 S6 shared enemy/init_targets.c | ROM-match complete | [S6 actual firebar/duplicate proof](../../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof); actual original RAM and full write footprints |
| 8553 | `FSLoop` | M2 T38 S6 shared enemy/init_targets.c | ROM-match complete | [S6 actual firebar/duplicate proof](../../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof); actual original RAM and full write footprints |
| 8569 | `FlmEx` | M2 T38 S6 shared enemy/init_targets.c | ROM-match complete | [S6 actual firebar/duplicate proof](../../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof); actual original RAM and full write footprints |
| 8573 | `FlameYPosData` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8576 | `FlameYMFAdderData` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8579 | `InitBowserFlame` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8597 | `SetFrT` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8604 | `PutAtRightExtent` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8615 | `SpawnFromMouth` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8635 | `SetMF` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8640 | `FinishFlame` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 8653 | `FireworksXPosData` | M2 T39 S2 shared enemy/frenzy.c | ROM-match complete | [S2 actual fireworks proof](../../history/M2-T39-special-initialization-and-dispatch.md#s2-original-fireworks-proof); all branches, writes and table indexes |
| 8656 | `FireworksYPosData` | M2 T39 S2 shared enemy/frenzy.c | ROM-match complete | [S2 actual fireworks proof](../../history/M2-T39-special-initialization-and-dispatch.md#s2-original-fireworks-proof); all branches, writes and table indexes |
| 8659 | `InitFireworks` | M2 T39 S2 shared enemy/frenzy.c | ROM-match complete | [S2 actual fireworks proof](../../history/M2-T39-special-initialization-and-dispatch.md#s2-original-fireworks-proof); all branches, writes and table indexes |
| 8666 | `StarFChk` | M2 T39 S2 shared enemy/frenzy.c | ROM-match complete | [S2 actual fireworks proof](../../history/M2-T39-special-initialization-and-dispatch.md#s2-original-fireworks-proof); all branches, writes and table indexes |
| 8697 | `ExitFWk` | M2 T39 S2 shared enemy/frenzy.c | ROM-match complete | [S2 actual fireworks proof](../../history/M2-T39-special-initialization-and-dispatch.md#s2-original-fireworks-proof); all branches, writes and table indexes |
| 8701 | `Bitmasks` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8704 | `Enemy17YPosData` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8707 | `SwimCC_IDData` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8710 | `BulletBillCheepCheep` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8722 | `ChkW2` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8726 | `Get17ID` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8730 | `Set17ID` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8736 | `GetRBit` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8738 | `ChkRBit` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8746 | `AddFBit` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8755 | `DoBulletBills` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8757 | `BB_SLoop` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8765 | `ExF17` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8767 | `FireBulletBill` | M2 T39 S3 shared enemy/frenzy.c | ROM-match complete | [S3 actual allocation proof](../../history/M2-T39-special-initialization-and-dispatch.md#s3-original-bullet-and-swimming-fish-proof); all branches, writes and table indexes |
| 8780 | `HandleGroupEnemies` | M2 T39 S4 shared enemy/group.c | ROM-match complete | [S4 actual group proof](../../history/M2-T39-special-initialization-and-dispatch.md#s4-original-grouped-enemy-proof); all branches, writes and table indexes |
| 8792 | `PullID` | M2 T39 S4 shared enemy/group.c | ROM-match complete | [S4 actual group proof](../../history/M2-T39-special-initialization-and-dispatch.md#s4-original-grouped-enemy-proof); all branches, writes and table indexes |
| 8793 | `SnglID` | M2 T39 S4 shared enemy/group.c | ROM-match complete | [S4 actual group proof](../../history/M2-T39-special-initialization-and-dispatch.md#s4-original-grouped-enemy-proof); all branches, writes and table indexes |
| 8798 | `SetYGp` | M2 T39 S4 shared enemy/group.c | ROM-match complete | [S4 actual group proof](../../history/M2-T39-special-initialization-and-dispatch.md#s4-original-grouped-enemy-proof); all branches, writes and table indexes |
| 8808 | `CntGrp` | M2 T39 S4 shared enemy/group.c | ROM-match complete | [S4 actual group proof](../../history/M2-T39-special-initialization-and-dispatch.md#s4-original-grouped-enemy-proof); all branches, writes and table indexes |
| 8809 | `GrLoop` | M2 T39 S4 shared enemy/group.c | ROM-match complete | [S4 actual group proof](../../history/M2-T39-special-initialization-and-dispatch.md#s4-original-grouped-enemy-proof); all branches, writes and table indexes |
| 8810 | `GSltLp` | M2 T39 S4 shared enemy/group.c | ROM-match complete | [S4 actual group proof](../../history/M2-T39-special-initialization-and-dispatch.md#s4-original-grouped-enemy-proof); all branches, writes and table indexes |
| 8835 | `NextED` | M2 T39 S4 shared enemy/group.c | ROM-match complete | [S4 actual group proof](../../history/M2-T39-special-initialization-and-dispatch.md#s4-original-grouped-enemy-proof); all branches, writes and table indexes |
| 8839 | `InitPiranhaPlant` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8855 | `InitEnemyFrenzy` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8872 | `NoFrenzyCode` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8877 | `EndFrenzy` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8879 | `LakituChk` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8884 | `NextFSlot` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8893 | `InitJumpGPTroopa` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8898 | `TallBBox2` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8899 | `SetBBox2` | M2 T39 S5 shared enemy/init_targets.c and frenzy.c | ROM-match complete | [S5 actual initializer/frenzy proof](../../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof); original branches, writes and vector |
| 8904 | `InitBalPlatform` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8911 | `AlignP` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8917 | `SetBPA` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8925 | `InitDropPlatform` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8932 | `InitHoriPlatform` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8939 | `InitVertPlatform` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8947 | `SetYO` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8955 | `CommonPlatCode` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8957 | `SPBBox` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8964 | `CasPBB` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8969 | `LargeLiftUp` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8973 | `LargeLiftDown` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8976 | `LargeLiftBBox` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8981 | `PlatLiftUp` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8990 | `PlatLiftDown` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 8998 | `CommonSmallLift` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 9007 | `PlatPosDataLow` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 9010 | `PlatPosDataHigh` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 9013 | `PosPlatform` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 9025 | `EndOfEnemyInitCode` | M2 T39 S6 shared enemy/init_targets.c and init.c | ROM-match complete | [S6 actual platform initialization proof](../../history/M2-T39-special-initialization-and-dispatch.md#s6-original-platform-initialization-proof); original branches, writes, tables and calls |
| 9030 | `RunEnemyObjectsCore` | M2 T39 S7 shared enemy/core.c and dispatch_targets.c | ROM-match complete | [S7 original caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s7-original-actor-vector-and-retainer-proof); child-input comparison, actual child failures retained |
| 9038 | `JmpEO` | M2 T39 S7 shared enemy/core.c and dispatch_targets.c | ROM-match complete | [S7 original caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s7-original-actor-vector-and-retainer-proof); child-input comparison, actual child failures retained |
| 9080 | `NoRunCode` | M2 T39 S7 shared enemy/core.c and dispatch_targets.c | ROM-match complete | [S7 original caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s7-original-actor-vector-and-retainer-proof); child-input comparison, actual child failures retained |
| 9085 | `RunRetainerObj` | M2 T39 S7 shared enemy/core.c and dispatch_targets.c | ROM-match complete | [S7 original caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s7-original-actor-vector-and-retainer-proof); child-input comparison, actual child failures retained |
| 9092 | `RunNormalEnemies` | M2 T39 S8 shared enemy/normal.c | ROM-match complete | [S8 original caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s8-original-normal-actor-and-movement-vector-proof); child-input comparison, actual child failures retained |
| 9105 | `SkipMove` | M2 T39 S8 shared enemy/normal.c | ROM-match complete | [S8 original caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s8-original-normal-actor-and-movement-vector-proof); child-input comparison, actual child failures retained |
| 9107 | `EnemyMovementSubs` | M2 T39 S8 shared enemy/normal.c | ROM-match complete | [S8 original caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s8-original-normal-actor-and-movement-vector-proof); child-input comparison, actual child failures retained |
| 9135 | `NoMoveCode` | M2 T39 S8 shared enemy/normal.c | ROM-match complete | [S8 original caller proof](../../history/M2-T39-special-initialization-and-dispatch.md#s8-original-normal-actor-and-movement-vector-proof); child-input comparison, actual child failures retained |
| 9140 | `RunBowserFlame` | M2 T39 S9 shared enemy special/platform callers and lifecycle | ROM-match complete | [S9 original caller/erasure proof](../../history/M2-T39-special-initialization-and-dispatch.md#s9-original-special-actor-and-platform-proof); child inputs compared, actual child gaps retained |
| 9150 | `RunFirebarObj` | M2 T39 S9 shared enemy special/platform callers and lifecycle | ROM-match complete | [S9 original caller/erasure proof](../../history/M2-T39-special-initialization-and-dispatch.md#s9-original-special-actor-and-platform-proof); child inputs compared, actual child gaps retained |
| 9156 | `RunSmallPlatform` | M2 T39 S9 shared enemy special/platform callers and lifecycle | ROM-match complete | [S9 original caller/erasure proof](../../history/M2-T39-special-initialization-and-dispatch.md#s9-original-special-actor-and-platform-proof); child inputs compared, actual child gaps retained |
| 9168 | `RunLargePlatform` | M2 T39 S9 shared enemy special/platform callers and lifecycle | ROM-match complete | [S9 original caller/erasure proof](../../history/M2-T39-special-initialization-and-dispatch.md#s9-original-special-actor-and-platform-proof); child inputs compared, actual child gaps retained |
| 9176 | `SkipPT` | M2 T39 S9 shared enemy special/platform callers and lifecycle | ROM-match complete | [S9 original caller/erasure proof](../../history/M2-T39-special-initialization-and-dispatch.md#s9-original-special-actor-and-platform-proof); child inputs compared, actual child gaps retained |
| 9182 | `LargePlatformSubroutines` | M2 T39 S9 shared enemy special/platform callers and lifecycle | ROM-match complete | [S9 original caller/erasure proof](../../history/M2-T39-special-initialization-and-dispatch.md#s9-original-special-actor-and-platform-proof); child inputs compared, actual child gaps retained |
| 9198 | `EraseEnemyObject` | M2 T39 S9 shared enemy special/platform callers and lifecycle | ROM-match complete | [S9 original caller/erasure proof](../../history/M2-T39-special-initialization-and-dispatch.md#s9-original-special-actor-and-platform-proof); child inputs compared, actual child gaps retained |
| 9212 | `MovePodoboo` | M2 T40 S1 shared enemy/podoboo.c | ROM-match complete | [S1 original and actual-child proof](../../history/M2-T40-enemy-movement-and-firebar.md#s1-original-podoboo-proof); Original timer branch, InitPodoboo input/return and post-child PRNG stores; actual initializer/gravity match |
| 9224 | `PdbM` | M2 T40 S1 shared enemy/podoboo.c | ROM-match complete | [S1 original and actual-child proof](../../history/M2-T40-enemy-movement-and-firebar.md#s1-original-podoboo-proof); Unconditional MoveJ_EnemyVertically tail on both timer branches; actual gravity and full RAM match |
| 9229 | `HammerThrowTmrData` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Both secondary-mode throw timer bytes and consumers |
| 9232 | `XSpeedAdderData` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); All four signed temporary speed-adder bytes and consumers |
| 9235 | `RevivedXSpeed` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); All four primary-mode revival speed bytes and consumers |
| 9238 | `ProcHammerBro` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Defeated priority and complete throw/jump/movement sequence |
| 9243 | `ChkJH` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Jump timer decrement and offscreen throw gate |
| 9260 | `DecHT` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Existing/failed-spawn timer decrement; successful spawn bypasses it |
| 9263 | `HammerBroJumpLData` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Both jump length bytes selected by secondary mode and PRNG mask |
| 9266 | `HammerBroJumpCode` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Jumping-state guard and Y sign/$70 thresholds |
| 9285 | `SetHJ` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Vertical speed, jump bit and scratch-selected PRNG index |
| 9295 | `HJump` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Jump frame length and PRNG OR $C0 jump timer |
| 9301 | `MoveHammerBroXDir` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Frame bit $40 selects shimmy speed before distance child |
| 9307 | `Shimmy` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Distance child input and page-sign facing decision |
| 9316 | `SetShim` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Post-distance interval timer, facing write and normal tail |
| 9318 | `MoveNormalEnemy` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Retained state priority and normal/defeated shared entries |
| 9336 | `FallE` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Vertical child followed by fresh state read |
| 9347 | `MEHor` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); State two horizontal direct tail |
| 9349 | `SlowM` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Falling non-power-up slow index |
| 9350 | `SteadM` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Saved input speed restored only on temporary-speed path |
| 9355 | `AddHS` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Sign index, source adder and exact horizontal child inputs |
| 9363 | `ReviveStunned` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Stunned timer zero/nonzero and state reset |
| 9377 | `SetRSpd` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Frame parity and primary mode select revival speed |
| 9381 | `MoveDefeatedEnemy` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Shared vertical then horizontal tail, including mixed defeat bits |
| 9385 | `ChkKillGoomba` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Timer $0E and Goomba tests; actual erasure child |
| 9392 | `NKGmba` | M2 T40 S2 shared enemy/hammer_bro.c and movement.c | ROM-match complete | [S2 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s2-original-hammer-bro-and-normal-proof); Source return reached with no extra stores |
| 9396 | `MoveJumpingEnemy` | M2 T40 S3 shared enemy/movement.c and paratroopa.c | ROM-match complete | [S3 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s3-original-jumping-and-red-paratroopa-proof); Existing shared gravity-then-horizontal child order and real child execution |
| 9402 | `ProcMoveRedPTroopa` | M2 T40 S3 shared enemy/movement.c and paratroopa.c | ROM-match complete | [S3 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s3-original-jumping-and-red-paratroopa-proof); Zero combined speed/force clears the fractional accumulator before anchor comparison |
| 9414 | `NoIncPT` | M2 T40 S3 shared enemy/movement.c and paratroopa.c | ROM-match complete | [S3 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s3-original-jumping-and-red-paratroopa-proof); All eight frame phases: increment only phase zero, then source return |
| 9416 | `MoveRedPTUpOrDown` | M2 T40 S3 shared enemy/movement.c and paratroopa.c | ROM-match complete | [S3 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s3-original-jumping-and-red-paratroopa-proof); Current versus central Y selects the source up/down gravity entries |
| 9421 | `MovPTDwn` | M2 T40 S3 shared enemy/movement.c and paratroopa.c | ROM-match complete | [S3 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s3-original-jumping-and-red-paratroopa-proof); Below-center branch reaches the real downward red-gravity child |
| 9427 | `MoveFlyGreenPTroopa` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Calls counter then horizontal movement and reads post-child frame state |
| 9438 | `YSway` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Writes plus/minus one to scratch and wraps Y as one byte |
| 9443 | `NoMGPT` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Skipped phase preserves horizontal displacement in scratch |
| 9445 | `XMoveCntr_GreenPTroopa` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Presets maximum $13 before the shared counter entry |
| 9448 | `XMoveCntr_Platform` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Stores incoming maximum even on skipped phases; original platform caller supplies $0E |
| 9460 | `NoIncXM` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Off-phase counter return leaves primary and secondary unchanged |
| 9461 | `IncPXM` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Exact maximum or zero endpoint increments primary with byte wrap |
| 9463 | `DecSeXM` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Odd primary decrements nonzero secondary and reverses at zero |
| 9468 | `MoveWithXMCntrs` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Saves secondary across signed horizontal movement and restores it |
| 9481 | `XMRight` | M2 T40 S4 shared enemy/green_paratroopa.c and x_counter.c | ROM-match complete | [S4 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s4-original-green-paratroopa-and-counter-proof); Writes facing, calls horizontal child, stores returned A before restoration |
| 9490 | `BlooberBitmasks` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Original two-byte masks bound to both hard-mode consumer paths |
| 9493 | `MoveBloober` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Defeat gate and random-mask direction selection match original |
| 9506 | `FBLeft` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Even-slot distance child preserves scratch and page-result sign |
| 9510 | `SBMDir` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Odd/even direction stores and inherited carry preserved |
| 9512 | `BlooberSwim` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Swim child precedes modulo-byte Y subtraction and status-bar comparison |
| 9520 | `SwimX` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Direction selects horizontal add or subtract with page carry |
| 9532 | `LeftSwim` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Left movement preserves byte subtraction and page borrow |
| 9542 | `MoveDefeatedBloober` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Defeated tail executes the real slow vertical child |
| 9545 | `ProcSwimmingB` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Counter phase selects float, acceleration or deceleration |
| 9565 | `BSwimE` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Acceleration phase skips or returns after exact force-two endpoint |
| 9567 | `SlowSwim` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Deceleration writes force/speed and exact-zero counter/timer changes |
| 9579 | `NoSSw` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Deceleration skipped phase and nonzero force return preserve state |
| 9581 | `ChkForFloatdown` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Timer zero reaches player comparison, nonzero reaches float-down |
| 9585 | `Floatdown` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Even frame increments Y with byte wrap |
| 9590 | `NoFD` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Odd frame skips float increment |
| 9592 | `ChkNearPlayer` | M2 T40 S5 shared enemy/bloober.c | ROM-match complete | [S5 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s5-original-bloober-swimming-proof); Inherited ADC carry and wrapped threshold choose continued float or reset |
| 9603 | `MoveBulletBill` | M2 T40 S6 shared enemy/bullet_bill.c | ROM-match complete | [S6 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s6-original-bullet-bill-movement-proof); State bit $20 selects the original jumping-gravity tail with unchanged input |
| 9608 | `NotDefB` | M2 T40 S6 shared enemy/bullet_bill.c | ROM-match complete | [S6 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s6-original-bullet-bill-movement-proof); All other states store fixed $E8 speed before the real horizontal tail |
| 9616 | `SwimCCXMoveData` | M2 T40 S7 shared enemy/swimming_cheep.c | ROM-match complete | [S7 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s7-original-swimming-cheep-proof); Four original table bytes bound; both used ID-selected forces exercised |
| 9620 | `MoveSwimmingCheepCheep` | M2 T40 S7 shared enemy/swimming_cheep.c | ROM-match complete | [S7 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s7-original-swimming-cheep-proof); State bit $20 selects the original slow-gravity child without extra gates |
| 9625 | `CCSwim` | M2 T40 S7 shared enemy/swimming_cheep.c | ROM-match complete | [S7 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s7-original-swimming-cheep-proof); Masked-zero scratch, table force subtraction and page borrow precede slot gate |
| 9660 | `CCSwimUpwards` | M2 T40 S7 shared enemy/swimming_cheep.c | ROM-match complete | [S7 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s7-original-swimming-cheep-proof); Y fraction subtraction propagates borrow through Y and Y-high |
| 9671 | `ChkSwimYPos` | M2 T40 S7 shared enemy/swimming_cheep.c | ROM-match complete | [S7 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s7-original-swimming-cheep-proof); Y-high stored before wrapped anchor difference sign and magnitude |
| 9682 | `YPDiff` | M2 T40 S7 shared enemy/swimming_cheep.c | ROM-match complete | [S7 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s7-original-swimming-cheep-proof); Exact $0F threshold selects up zero or down $10 from original sign |
| 9686 | `ExSwCC` | M2 T40 S7 shared enemy/swimming_cheep.c | ROM-match complete | [S7 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s7-original-swimming-cheep-proof); First two slots and below-threshold paths retain the prescribed RAM footprint |
| 9703 | `FirebarPosLookupTbl` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); All 99 bytes bound and consumed; original $CD0B value restored by immutable binding |
| 9716 | `FirebarMirrorData` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Bind quadrant mirror values and exact indexed reads including residual-call addresses |
| 9719 | `FirebarTblOffsets` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Bind all twelve offsets; retain source byte indexing and adjacency |
| 9723 | `FirebarYPos` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Bind the two additional big-player vertical collision probes |
| 9726 | `ProcFirebar` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Offscreen-before-spin, timer gate, original child order and center/outer iteration |
| 9737 | `SusFbar` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Paused spin state is read without speed update |
| 9745 | `SkpFSte` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Long-bar phases eight/twenty-four increment once |
| 9748 | `SetupGFB` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Save phase, relative child return/scratch, residual lookup and center coordinates |
| 9766 | `SetMFbar` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Store short/long maximum after center collision |
| 9769 | `DrawFbar` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Lookup and collision/draw repeated in original sequence |
| 9778 | `NextFbar` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Increment index and compare to $ED after duplicate-OAM switch |
| 9782 | `SkipFBar` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Offscreen branch returns before motion or drawing |
| 9784 | `DrawFirebar_Collision` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Preserve mirror scratch and coordinate-to-OAM order |
| 9793 | `AddHA` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Horizontal signed adder plus relative X with byte wrap |
| 9803 | `SubtR1` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Unsigned ordering selects non-wrapped absolute horizontal distance |
| 9805 | `ChkFOfs` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); $59 distance gate hides Y while preserving sprite X |
| 9809 | `VAHandl` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Anchor Y $F8 short-circuits vertical mirror handling |
| 9817 | `AddVA` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Vertical signed adder plus relative Y with byte wrap |
| 9819 | `SetVFbr` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Store OAM Y and scratch $07 before collision entry |
| 9822 | `FirebarCollision` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Draw child first, saved Y and star/timer/high-Y gates |
| 9838 | `AdjSm` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Small or crouching probe counter two and Y plus $18 |
| 9844 | `BigJp` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Preserve big standing initial Y probe |
| 9845 | `FBCLoop` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Signed byte vertical difference and absolute magnitude |
| 9851 | `ChkVFBD` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Vertical eight-pixel and far-right X gates |
| 9866 | `ChkFBCl` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Player sprite-one X plus four and signed horizontal threshold |
| 9868 | `Chk2Ofs` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Advance big-player probe table or exit at counter two |
| 9877 | `ChgSDir` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Choose injury direction from modded sprite X comparison |
| 9882 | `SetSDir` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Slot-zero direction, injury child, saved $00 and resumed source loop |
| 9889 | `NoColFB` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Saved OAM offset plus four and ObjectOffset restoration |
| 9896 | `GetFirebarPosition` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Preserve caller A through both triangular lookups and mirror selection |
| 9904 | `GetHAdder` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Horizontal oscillation plus original per-ball table index |
| 9922 | `GetVAdder` | M2 T40 S8 shared enemy/firebar.c | ROM-match complete | [S8 original caller/data proof](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof); Vertical oscillation plus original per-ball table index and mirror output |
| 9941 | `PRandomSubtracter` | M2 T40 S9 shared enemy/flying_cheep.c | ROM-match complete | [S9 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s9-original-flying-cheep-movement-proof); Five bound source bytes and all sixteen original indexed addresses consumed |
| 9944 | `FlyCCBPriority` | M2 T40 S9 shared enemy/flying_cheep.c | ROM-match complete | [S9 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s9-original-flying-cheep-movement-proof); Five bound priority bytes and all sixteen indexed addresses consumed |
| 9947 | `MoveFlyingCheepCheep` | M2 T40 S9 shared enemy/flying_cheep.c | ROM-match complete | [S9 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s9-original-flying-cheep-movement-proof); State bit $20 clears attributes before the exact jumping-gravity tail |
| 9954 | `FlyCC` | M2 T40 S9 shared enemy/flying_cheep.c | ROM-match complete | [S9 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s9-original-flying-cheep-movement-proof); Horizontal then original $0D/$05 gravity; post-child state selects lookup |
| 9971 | `AddCCF` | M2 T40 S9 shared enemy/flying_cheep.c | ROM-match complete | [S9 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s9-original-flying-cheep-movement-proof); Wrapped signed magnitude below eight adds $10, including force wrap |
| 9982 | `BPGet` | M2 T40 S9 shared enemy/flying_cheep.c | ROM-match complete | [S9 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s9-original-flying-cheep-movement-proof); Final force high nibble selects original attribute data and exact write |
| 9990 | `LakituDiffAdj` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Three table values copied to scratch in reverse-index order |
| 9993 | `MoveLakitu` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Defeated bit selects the MoveD_EnemyVertically tail |
| 9998 | `ChkLS` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Nonzero live state clears frenzy/direction and sets speed $10 |
| 10005 | `Fr12S` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Zero state requests Spiny before scratch/table setup |
| 10008 | `LdLDa` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Populate $01-$03 before the shared distance child |
| 10013 | `SetLSpd` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Store returned speed including delayed-turn result, no extra exit |
| 10024 | `SetLMov` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Direction bit chooses sign, then horizontal child |
| 10027 | `PlayerLakituDiff` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); PlayerEnemyDiff page sign and low scratch determine byte distance |
| 10037 | `ChkLakDif` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Clamp at $3C and compare full direction byte for Lakitu |
| 10053 | `SetLMovD` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Commit new direction only at the original delay boundary |
| 10055 | `ChkPSpeed` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Mask/divide scratch distance; preserve speed/scroll gates |
| 10073 | `ChkSpinyO` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Spiny-specific bypass of vertical-state adjustment reset |
| 10078 | `ChkEmySpd` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Zero vertical state resets adjustment index only on this path |
| 10081 | `SubDifAdj` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Read caller-provided $01-$03, never hardcode Lakitu data here |
| 10083 | `SPixelLak` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Subtract once plus masked distance with byte wrap |
| 10087 | `ExMoveLak` | M2 T40 S10 shared enemy/lakitu.c | ROM-match complete | [S10 original/actual proof](../../history/M2-T40-enemy-movement-and-firebar.md#s10-original-lakitu-movement-and-distance-proof); Return original accumulator, including decremented speed |
| 10092 | `BridgeCollapseData` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridgecollapsedata) |
| 10098 | `BridgeCollapse` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-bridgecollapse) |
| 10111 | `SetM2` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-setm2) |
| 10116 | `MoveD_Bowser` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-moved_bowser) |
| 10120 | `RemoveBridge` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-removebridge) |
| 10152 | `NoBFall` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nobfall) |
| 10156 | `PRandomRange` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-prandomrange) |
| 10159 | `RunBowser` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-runbowser) |
| 10167 | `KillAllEnemies` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
| 10169 | `KillLoop` | M2 T38 S1 shared enemy/core.c and enemy/loop.c | ROM-match complete | [S1 loop proof](../../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof); caller scope, child failures retained |
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
| 10337 | `FlameTimerData` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 10340 | `SetFlameTimer` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
| 10347 | `ExFl` | M2 T39 S1 shared enemy/init_targets.c and enemy/frenzy.c | ROM-match complete | [S1 actual Bowser/flame proof](../../history/M2-T39-special-initialization-and-dispatch.md#s1-original-bowser-and-flame-proof); original branches, writes and table consumers |
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
| 10664 | `FirebarSpin` | T19 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-firebarspin); [S8 child diagnostic](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof): typed child seam; no node credit |
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
| 11426 | `InjurePlayer` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-injureplayer); [S8 child diagnostic](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof): powered injury sound/palette-buffer differences |
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
| 12415 | `ExEBG` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12420 | `EnemyBGCStateData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemybgcstatedata) |
| 12423 | `EnemyBGCXSpdData` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemybgcxspddata) |
| 12426 | `EnemyToBGCollisionDet` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12439 | `DoIDCheckBGColl` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12443 | `HBChk` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12446 | `CInvu` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12452 | `YesIn` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
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
| 12518 | `ExEBGChk` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
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
| 12617 | `DoEnemySideCheck` | M2 T31 S2 shared game/enemy/side_collision.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12624 | `SdeCLoop` | M2 T31 S2 shared game/enemy/side_collision.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12632 | `NextSdeC` | M2 T31 S2 shared game/enemy/side_collision.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12636 | `ExESdeC` | M2 T31 S2 shared game/enemy/side_collision.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12638 | `ChkForBump_HammerBroJ` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-chkforbump_hammerbroj) |
| 12646 | `NoBump` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-nobump) |
| 12654 | `InvEnemyDir` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-invenemydir) |
| 12660 | `PlayerEnemyDiff` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-playerenemydiff) |
| 12671 | `EnemyLanding` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-enemylanding) |
| 12679 | `SubtEnemyYPos` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12686 | `EnemyJump` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
| 12701 | `DoSide` | M2 T31 S2 shared game/enemy/background.c | ROM-match complete | [S2 P6 scoped chain proof](../../history/M2-T31-game-dispatcher.md#s2p6-background-and-side-chain-proof) |
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
| 13674 | `CheckForBulletBillCV` | M2 T31 S2 shared game/oam/bullet_bill_gfx.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
| 13682 | `SBBAt` | M2 T31 S2 shared game/oam/bullet_bill_gfx.c | ROM-match complete | [S2 P2 dual evidence and remaining dispatch](../../history/M2-T31-game-dispatcher.md#s2p2-combined-slot-environment-and-cannon-child-delivery) |
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
| 14261 | `DrawFirebar` | T17 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-drawfirebar); [S8 child diagnostic](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof): typed child seam; no node credit |
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
| 14811 | `RelativeEnemyPosition` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-relativeenemyposition); [S8 child diagnostic](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof): missing original slot scratch |
| 14816 | `RelativeBlockPosition` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-relativeblockposition) |
| 14825 | `VariableObjOfsRelPos` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-variableobjofsrelpos) |
| 14834 | `GetObjRelativePosition` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getobjrelativeposition) |
| 14846 | `GetPlayerOffscreenBits` | T16: `src/game/oam/player_gfx.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-getplayeroffscreenbits) |
| 14851 | `GetFireballOffscreenBits` | T16: `src/game/oam/object_position.c` | audited; evidence incomplete | [T24 S1: partial](m2-t24-s1-node-verification.md#node-getfireballoffscreenbits) |
| 14857 | `GetBubbleOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getbubbleoffscreenbits) |
| 14863 | `GetMiscOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getmiscoffscreenbits) |
| 14869 | `ObjOffsetData` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-objoffsetdata) |
| 14872 | `GetProperObjOffset` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getproperobjoffset) |
| 14879 | `GetEnemyOffscreenBits` | T16 responsibility (implementation not certified) | open | [T24 S1 evidence audit](m2-t24-s1-full-node-census.md#node-getenemyoffscreenbits); [S8 child diagnostic](../../history/M2-T40-enemy-movement-and-firebar.md#s8-original-firebar-chain-proof): missing original scratch writes |
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
