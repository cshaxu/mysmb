# M2 T14 frame-root label map

Scope is SMBDIS lines 699-981 plus InitializeMemory at line 2795. This map records current ownership only; `mapped` never means ROM-equivalent.

| ROM line | Label | Current C owner | Status |
|---:|---|---|---|
| 699 | `Start` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 706 | `VBlank1` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 708 | `VBlank2` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 712 | `WBootCheck` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 721 | `ColdBoot` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 737 | `EndlessLoop` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 743 | `VRAM_AddrTable_Low` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 752 | `VRAM_AddrTable_High` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 761 | `VRAM_Buffer_Offset` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 764 | `NonMaskableInterrupt` | src/game/frame_root.c | translated structure; branch semantics pending trace |
| 776 | `ScreenOff` | src/game/game.c PPU helper | mapped; semantics unverified |
| 796 | `InitBuffer` | src/game/game.c PPU helper | mapped; semantics unverified |
| 814 | `DecTimers` | src/game/game.c root helper, called by src/game/frame_root.c | translated structure; branch semantics pending trace |
| 820 | `DecTimersLoop` | src/game/game.c root helper | mapped; semantics unverified |
| 823 | `SkipExpTimer` | src/game/game.c root helper | mapped; semantics unverified |
| 825 | `NoDecTimers` | src/game/game.c root helper | mapped; semantics unverified |
| 826 | `PauseSkip` | src/game/game.c root helper | mapped; semantics unverified |
| 837 | `RotPRandomBit` | src/game/game.c root helper, called by src/game/frame_root.c | translated structure; branch semantics pending trace |
| 843 | `Sprite0Clr` | src/game/frame_root.c | mapped; semantics unverified |
| 851 | `Sprite0Hit` | src/game/frame_root.c | mapped; semantics unverified |
| 855 | `HBlankDelay` | src/game/frame_root.c | mapped; semantics unverified |
| 857 | `SkipSprite0` | src/game/frame_root.c | mapped; semantics unverified |
| 868 | `SkipMainOper` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 876 | `PauseRoutine` | src/game/frame_root.c | translated; focused pause/OAM regression |
| 885 | `ChkPauseTimer` | src/game/frame_root.c | translated; focused pause/OAM regression |
| 889 | `ChkStart` | src/game/frame_root.c | translated; focused pause/OAM regression |
| 904 | `ClrPauseTimer` | src/game/frame_root.c | translated; focused pause/OAM regression |
| 906 | `SetPause` | src/game/frame_root.c | translated; focused pause/OAM regression |
| 907 | `ExitPause` | src/game/frame_root.c | translated; focused pause/OAM regression |
| 912 | `SpriteShuffler` | src/game/frame_root.c | mapped; semantics unverified |
| 917 | `ShuffleLoop` | src/game/frame_root.c | mapped; semantics unverified |
| 926 | `StrSprOffset` | src/game/frame_root.c | mapped; semantics unverified |
| 927 | `NextSprOffset` | src/game/frame_root.c | mapped; semantics unverified |
| 934 | `SetAmtOffset` | src/game/frame_root.c | mapped; semantics unverified |
| 937 | `SetMiscOffset` | src/game/frame_root.c | mapped; semantics unverified |
| 954 | `OperModeExecutionTree` | src/game/frame_root.c | translated structure; route semantics pending trace |
| 965 | `MoveAllSpritesOffscreen` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 969 | `MoveSpritesOffscreen` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 972 | `SprInitLoop` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 2795 | `InitializeMemory` | src/game/boot.c reset subtree | mapped; semantics unverified |

## P1 extraction boundary

- `frame_root.c` owns the NMI seam, `PauseRoutine`, and the actual `OperModeExecutionTree` dispatch/object loop.
- `boot.c` owns the reset/cold-boot subtree and initialization leaves; `game.c` retains game-owned leaf routes.
- No platform source owns a label or writes root game state.

## P2 executable evidence

| Artifact | SHA-256 |
|---|---|
| `assets/mysmb16.exe` | `eb7d560fadd246a401cda4f28067b4e825db41f5b785be4c4c6ee1887e18c228` |
| `assets/mysmb32.exe` | `28adcb7ba01ffa540440ef1c9382dfa42ee83e604d685f496deb233c4c304f30` |
| `assets/mysmb64.exe` | `4237b9e08f292eafdc2db25cc2a103e3d677a279793165387e38c1ba5cf675d8` |
x86 and x64 CTest each passed 76/76 after the P11 frame-root relocation. The OpenNT large-model DOS link produced `mysmb16.exe` from the same source set.
## P13 bounded NMI-return evidence

A fresh 600-sample owner-local comparison used ROM controller script
`30:$08,31:0,60:$80` and native decoded-input script
`30:$10,31:0,60:$01`, with the native title bootstrap and a non-interfering
native recorder sentinel interval 599–600. The raw traces remain only in
`build/t14-frame-root-p13`.

Both x64 and x86 native traces have SHA-256
`8b4f97d0af2c81ef0fa30330396b606dc3cc892f8cc91e7d7abf7c87a9eba3f2`.
Against the original ROM, CPU OAM backing RAM, work RAM `$0300-$07ff`, both
CIRAM pages, palette, visible OAM, all 14 audio-command bytes, and each of
the seven PPU scalar bytes have zero differences over samples 0–599. Zero
page and stack are still different and remain outside this route's
output-equivalence claim.

## P15 structural-recovery evidence

P15 moves the existing reset/cold-boot implementation without changing its
branches from `game.c` into the dedicated shared `boot.c` owner.  It also adds
that translation unit to both ordinary CMake builds and the OpenNT DOS source
set.  This is a placement proof only: `WBootCheck` and `ColdBoot` remain marked
semantically unverified until their ROM branch behavior is migrated and traced.

| Artifact | SHA-256 |
|---|---|
| `assets/mysmb16.exe` | `4481c7e178c891e58cd66d50334cbfb4f240f1911091c9c539a148d2eabbe03e` |
| `assets/mysmb32.exe` | `0982ddc7fd927ae310e1c838c177ba26b80238172237c40376982726d0f625a6` |
| `assets/mysmb64.exe` | `a910e88338cab5cec07ea542930b3cb598122086430ab2cbcc4f833a80727cb4` |

x86 and x64 each pass 77/77 tests; the OpenNT large-model linker produced the
16-bit DOS executable from the same source set.
