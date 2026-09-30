# H9 large-platform Y-source repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no production-code change.

## Confirmed discrepancy

At `SMBDIS.ASM` line 13366, `DrawLargePlatform` loads `Enemy_Y_Position,x` and passes that byte to `DumpFourSpr` for its first four sprite Y coordinates. Current `src/game/oam/small_platform_gfx.c:mysmb_objects_draw_large_platform` instead loads `MYSMB_SMALL_PLATFORM_REL_Y` (`$03b9`). These are distinct ROM state cells; scrolling or actor preparation can make their values differ.

## Smallest candidate chain

Change only the initial Y-source binding in `mysmb_objects_draw_large_platform` to `Enemy_Y_Position + slot` (`$00cf+x`). Preserve the existing source-equivalent final-two-row castle/secondary-hard override, cloud tile selection, six-column offscreen masking and full-hide tail.

## Required proof after a later admission

Run controlled original-ROM/x86/x64 large-platform routes with a deliberately distinct `Enemy_Y_Position,x` and `Enemy_Rel_YPos`, then verify the first four OAM Y records use the former. Re-run castle, secondary-hard, cloud override, per-column and full-offscreen cases to prove the neighboring chain has not changed.
