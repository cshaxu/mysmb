# B2 palette fall-through repair candidate

## Status

Unnumbered current-equivalence repair candidate. This is audit evidence only;
it is not an admitted M2 task and authorizes no production change.

## Confirmed discrepancy

At `SMBDIS.ASM` lines 1460–1503, `GetBackgroundColor` has two local
predecessor paths into `NoBGColor`:

- zero `BackgroundColorCtrl` branches straight to `NoBGColor`;
- a nonzero value loads `BGColorCtrl_Addr-4` into `VRAM_Buffer_AddrCtrl` and
  falls through to the same label.

`NoBGColor` increments `ScreenRoutineTask`, then unconditionally falls into
`GetPlayerColors`. Thus both paths construct the `$3f10`, length-four player
palette command after the task increment.

Current shared C [`src/game/game.c`](../../src/game/game.c) case 10 increments
the task but only calls `mysmb_area_sync_player_palette` in its `else` branch.
For controls 4–7 it writes the address-control byte then exits the switch,
omitting the `GetPlayerColors` producer. This changes both the control
handoff and the feasible palette-table consumption path.

## Smallest candidate chain

`GetBackgroundColor -> NoBGColor -> GetPlayerColors -> ChkFiery /
StartClrGet / ClrGetLoop -> SetBGColor -> SetVRAMOffset` in the shared
`game.c` / `area.c` ownership boundary. The repair must preserve the ROM
write order: optional address-control selection, task increment, then the
unconditional palette command. Platform adapters are outside this chain.

## Required proof after a later admission

Run original-ROM and x86/x64 routes for every valid `AreaType`, both players,
normal/fiery status, and `BackgroundColorCtrl` zero, 4, 5, 6 and 7. Compare
the task byte, VRAM address control, Buffer1 command header/payload/offset and
the PPU palette after the consuming NMI. The repair may be credited only when
the two mismatched labels and `control-00205` / `control-00206` become exact
without regressing the surrounding screen-task dispatch.
