# M2 T14 frame-root label map

Scope is SMBDIS lines 699-981 plus InitializeMemory at line 2795. This map records current ownership only; `mapped` never means ROM-equivalent.

| ROM line | Label | Current C owner | Status |
|---:|---|---|---|
| 699 | `Start` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 706 | `VBlank1` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 708 | `VBlank2` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 712 | `WBootCheck` | src/game/boot.c reset subtree | translated; warm/cold branch regression |
| 721 | `ColdBoot` | src/game/boot.c reset subtree | translated; reset-output regression |
| 737 | `EndlessLoop` | src/game/boot.c reset subtree | mapped; semantics unverified |
| 743 | `VRAM_AddrTable_Low` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 752 | `VRAM_AddrTable_High` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 761 | `VRAM_Buffer_Offset` | src/game/game.c VRAM constants/table | mapped; semantics unverified |
| 764 | `NonMaskableInterrupt` | src/game/frame_root.c | translated structure; branch semantics pending trace |
| 776 | `ScreenOff` | src/game/frame_root.c | translated; NMI leaf owner |
| 796 | `InitBuffer` | src/game/frame_root.c | translated; NMI leaf owner |
| 814 | `DecTimers` | src/game/frame_root.c | translated; NMI leaf owner |
| 820 | `DecTimersLoop` | src/game/frame_root.c | translated; NMI leaf owner |
| 823 | `SkipExpTimer` | src/game/frame_root.c | translated; NMI leaf owner |
| 825 | `NoDecTimers` | src/game/frame_root.c | translated; NMI leaf owner |
| 826 | `PauseSkip` | src/game/frame_root.c | translated; NMI leaf owner |
| 837 | `RotPRandomBit` | src/game/frame_root.c | translated; NMI leaf owner |
| 843 | `Sprite0Clr` | src/game/frame_root.c | mapped; semantics unverified |
| 851 | `Sprite0Hit` | src/game/frame_root.c | mapped; semantics unverified |
| 855 | `HBlankDelay` | src/game/frame_root.c | mapped; semantics unverified |
| 857 | `SkipSprite0` | src/game/frame_root.c | mapped; semantics unverified |
| 868 | `SkipMainOper` | src/game/frame_root.c | translated structure; root owner |
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
| 965 | `MoveAllSpritesOffscreen` | src/game/boot.c reset subtree | translated; reset-output regression |
| 969 | `MoveSpritesOffscreen` | src/game/boot.c reset subtree | translated; reset-output regression |
| 972 | `SprInitLoop` | src/game/boot.c reset subtree | translated; reset-output regression |
| 2795 | `InitializeMemory` | src/game/boot.c reset subtree | translated; cold/warm RAM regressions |

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
set.  This was a placement proof only at P15; P16 supplies the following branch
translation and focused regression.

| Artifact | SHA-256 |
|---|---|
| `assets/mysmb16.exe` | `4481c7e178c891e58cd66d50334cbfb4f240f1911091c9c539a148d2eabbe03e` |
| `assets/mysmb32.exe` | `0982ddc7fd927ae310e1c838c177ba26b80238172237c40376982726d0f625a6` |
| `assets/mysmb64.exe` | `a910e88338cab5cec07ea542930b3cb598122086430ab2cbcc4f833a80727cb4` |

x86 and x64 each pass 77/77 tests; the OpenNT large-model linker produced the
16-bit DOS executable from the same source set.

## P16 reset-branch evidence

P16 adds `mysmb_game_reset`, the shared translation of `WBootCheck` and
`ColdBoot`.  It checks all six `$07d7-$07dc` digits before `$07ff`, uses the
ROM's `$d6` or `$fe` `InitializeMemory` offset, then applies the documented
boot writes in order.  `mysmb_game_initialize` remains a separate host
container constructor until its full first-NMI route is compared; P16 does not
claim that this replacement has happened.

`mysmb.reset-root-smoke` locks both the valid warm path and an invalid-digit
cold path, including the expected RAM, PPU mask, OAM producer state and next
NMI DMA phase.  x86 and x64 each pass 78/78 tests; the 16-bit OpenNT link
uses this same `boot.c`.

| Artifact | SHA-256 |
|---|---|
| `assets/mysmb16.exe` | `7b89f585888f9350990a7da5718349b932256d500c1eeca898012c7bd5ef3566` |
| `assets/mysmb32.exe` | `e935c4cc4642e6eddb927423851466d7075b4b80d9e91031210cc002d700330b` |
| `assets/mysmb64.exe` | `ac379d7445785ad46408a1588aa40c3337d4b6518f455f662d955ff007985b29` |

## P17 NMI-leaf ownership evidence

P17 moves `UpdateScreen`/buffer reset, display-register commit, `DecTimers`,
`RotPRandomBit`, and `SpriteShuffler` from `game.c` into `frame_root.c`.  The
former title compatibility helpers invoke the same root-owned primitives; no
platform source gained a game decision.  A fresh 8-sample cold-start trace in
`build/t14-s2-p17` has zero differences for CPU OAM RAM, work RAM, both CIRAM
pages, palette, visible OAM, audio commands, and all PPU scalar fields.  The
remaining CPU differences are emulator zero-page/stack temporaries.

| Artifact | SHA-256 |
|---|---|
| `assets/mysmb16.exe` | `25f3e372313775cdc9f27b085d0d2b61c5a6df20b794185ba32f081e4a458f19` |
| `assets/mysmb32.exe` | `a3ae2a573143411832c87b0a1a7287b8448ca7878615dd642bc8f6da968624bb` |
| `assets/mysmb64.exe` | `e7bacc932f11e7386586b10690917250b09f76f062dca4d2d632f3af93a0e2bf` |

x86 and x64 each pass 78/78; the 16-bit OpenNT linker uses the same root.

## P18 title-buffer boundary recovery

The first post-P17 600-sample comparison exposed CIRAM-page-0 differences at
sample 23.  The physical move had widened the `VRAM_Buffer_AddrCtrl == 5`
title stream from the ROM's `$013a` bytes to `$0100`; P18 restores `$013a`.
A fresh 600-sample ROM comparison in `build/t14-s2-p18` then returns zero
differences in CPU OAM RAM, work RAM, both CIRAM pages, palette, visible OAM,
audio commands and all seven PPU scalars.  The x86 and x64 native traces are
byte-identical with SHA-256
`8b4f97d0af2c81ef0fa30330396b606dc3cc892f8cc91e7d7abf7c87a9eba3f2`.

| Artifact | SHA-256 |
|---|---|
| `assets/mysmb16.exe` | `51bc5c0052aa9f06365866e71b1ce6e38bc3a6ec7cd9039775d2cda7349d0f65` |
| `assets/mysmb32.exe` | `b667f36dbb772273a218ab59f1be48591398056f575c50e245d4c6a567b482d2` |
| `assets/mysmb64.exe` | `a6360868dd9e7377aae666f13684a6b3b17243873f125eb7091be2107c6c19ae` |

x86 and x64 each pass 78/78; the 16-bit OpenNT link uses the corrected root.
