# M2 T14 S1 frame-root label map

Scope is SMBDIS lines 699-981 plus InitializeMemory at line 2795. This map records current ownership only; `mapped` never means ROM-equivalent.

| ROM line | Label | Current C owner | Status |
|---:|---|---|---|
| 699 | `Start` | src/game/game.c initialization | mapped; semantics unverified |
| 706 | `VBlank1` | src/game/game.c initialization | mapped; semantics unverified |
| 708 | `VBlank2` | src/game/game.c initialization | mapped; semantics unverified |
| 712 | `WBootCheck` | src/game/game.c initialization | mapped; semantics unverified |
| 721 | `ColdBoot` | src/game/game.c initialization | mapped; semantics unverified |
| 737 | `EndlessLoop` | src/game/game.c initialization | mapped; semantics unverified |
| 743 | `VRAM_AddrTable_Low` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 752 | `VRAM_AddrTable_High` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 761 | `VRAM_Buffer_Offset` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 764 | `NonMaskableInterrupt` | src/game/frame_root.c | mapped; semantics unverified |
| 776 | `ScreenOff` | src/game/game.c PPU helper | mapped; semantics unverified |
| 796 | `InitBuffer` | src/game/game.c PPU helper | mapped; semantics unverified |
| 814 | `DecTimers` | src/game/game.c root helper | mapped; semantics unverified |
| 820 | `DecTimersLoop` | src/game/game.c root helper | mapped; semantics unverified |
| 823 | `SkipExpTimer` | src/game/game.c root helper | mapped; semantics unverified |
| 825 | `NoDecTimers` | src/game/game.c root helper | mapped; semantics unverified |
| 826 | `PauseSkip` | src/game/game.c root helper | mapped; semantics unverified |
| 837 | `RotPRandomBit` | src/game/game.c root helper | mapped; semantics unverified |
| 843 | `Sprite0Clr` | src/game/frame_root.c | mapped; semantics unverified |
| 851 | `Sprite0Hit` | src/game/frame_root.c | mapped; semantics unverified |
| 855 | `HBlankDelay` | src/game/frame_root.c | mapped; semantics unverified |
| 857 | `SkipSprite0` | src/game/frame_root.c | mapped; semantics unverified |
| 868 | `SkipMainOper` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 876 | `PauseRoutine` | src/game/game.c mode-tree legacy | mapped; semantics unverified |
| 885 | `ChkPauseTimer` | src/game/game.c mode-tree legacy | mapped; semantics unverified |
| 889 | `ChkStart` | src/game/game.c mode-tree legacy | mapped; semantics unverified |
| 904 | `ClrPauseTimer` | src/game/game.c mode-tree legacy | mapped; semantics unverified |
| 906 | `SetPause` | src/game/game.c mode-tree legacy | mapped; semantics unverified |
| 907 | `ExitPause` | src/game/game.c mode-tree legacy | mapped; semantics unverified |
| 912 | `SpriteShuffler` | src/game/frame_root.c | mapped; semantics unverified |
| 917 | `ShuffleLoop` | src/game/frame_root.c | mapped; semantics unverified |
| 926 | `StrSprOffset` | src/game/frame_root.c | mapped; semantics unverified |
| 927 | `NextSprOffset` | src/game/frame_root.c | mapped; semantics unverified |
| 934 | `SetAmtOffset` | src/game/frame_root.c | mapped; semantics unverified |
| 937 | `SetMiscOffset` | src/game/frame_root.c | mapped; semantics unverified |
| 954 | `OperModeExecutionTree` | src/game/game.c mode-tree legacy | mapped; semantics unverified |
| 965 | `MoveAllSpritesOffscreen` | src/game/game.c initialization | mapped; semantics unverified |
| 969 | `MoveSpritesOffscreen` | src/game/game.c initialization | mapped; semantics unverified |
| 972 | `SprInitLoop` | src/game/game.c initialization | mapped; semantics unverified |
| 2795 | `InitializeMemory` | src/game/game.c initialization | mapped; semantics unverified |

## P1 extraction boundary

- `frame_root.c` now owns the mechanical NMI prologue/epilogue seam and delegates legacy helpers without duplicating their logic.
- `game.c` retains mode-tree and initialization behavior until each exact label path is moved and reference-compared.
- No platform source owns a label or writes root game state.

## P2 executable evidence

| Artifact | SHA-256 |
|---|---|
| `assets/mysmb16.exe` | `3e91417b1fea88a6f517907ec5026eb387b76f980fd8a90b0201485da07a06ff` |
| `assets/mysmb32.exe` | `1db5aea89bbcb832c77fb13992e04c99f657053e4e72107ae43d631ff234bfa4` |
| `assets/mysmb64.exe` | `44082de41f2f677eff440e46d93f784f6179308b624c8ad30e4e5bafe3873b24` |
`r`nx86 and x64 CTest each passed 75/75 after the shared seam extraction. The OpenNT large-model DOS link produced `mysmb16.exe` from the same source set.`r`n