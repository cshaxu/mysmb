# M2 T18: Area graphics and parser

## Status

**M2 T18 active — S2/P1 and S3/P1.** The ROM continuation reaches `ReplaceBlockMetatile` after block state has already been produced. Its missing `$03f0` increment belongs to the area/metatile output slice, so this task owns the producer rather than adding a compensating write to objects or OAM.

## ROM scope

ROM lines 1825-5314 except `InitializeMemory`: metatiles, attributes, palettes, headers, parser tasks/core, block buffer and scrolling setup. The initial boundary is `ReplaceBlockMetatile -> WriteBlockMetatile -> PutBlockMetatile` (lines 2052-2099) and its caller `BlockObjMT_Updater` (7527-7548).

## Graph contract

Area code owns block-buffer and VRAM-command mutations. It consumes a completed block replacement request and emits only area RAM/VRAM-buffer state; it never decides player, actor, OAM, or platform behavior.

## Formal S breakdown

1. **S1 complete (P1) — source ownership boundary.** Map metatile command labels and move the block-metatile writer from object routing to `src/game/area/` without changing bytes. Evidence: bounded trace unchanged.
2. **S2 active (P1) — headers and parser core.** Translate source offsets, page semantics, and parser task branches.
3. **S3 planned — metatile/block-buffer mutations.** Translate `ReplaceBlockMetatile`, `DestroyBlockMetatile`, `WriteBlockMetatile`, `PutBlockMetatile`, attributes, palette and name-table writes. Evidence: hidden-block, question-block, coin, and pipe traces.
4. **S4 planned — column/scroll scheduling and closure.** Translate column scheduling and prove area entry and scroll routes by reference trace.

## Acceptance

Area RAM, parser offsets, block buffer, CIRAM, attributes, palette and scroll state match reference. Platform code may not read or write these game decisions. Replaced code is removed in the same admitted P after its trace proves the replacement.
## S1 P1: block metatile writer boundary

BlockObjMT_Updater and its ReplaceBlockMetatile command writer now live in src/game/area/block_metatile.c; frame root and tests call the area API. The 600-sample continuation is unchanged: first work-RAM mismatch remains sample 82 / $03f0, with 2,893 differing work-RAM bytes; CIRAM, palette, audio and PPU remain zero-difference. x64/x86 pass 78/78; OpenNT links DOS MZ with its existing OLDNAMES.LIB warning. Artifacts: 16 00AB5AD16398B908135E17BACB05A7A92B0B1C0C188AF38C974E801350AD6982, 32 79F8BFBBFE71F70F1D2E9F18E1C1D97370B2D5B993F991031D719A443C912CA3, 64 CD71364ADF964DC81F27183D727417F3180761DB66A423AC3DD7B556F9353ED8.

## S3 P1: restore flower `GetPlayerColors` producer

`HandlePowerUpCollision` at ROM lines 11285–11290 writes fiery
`PlayerStatus=$02`, calls `GetPlayerColors`, and only then tail-jumps to
`UpToFiery`. The shared power-up route had omitted that palette-command
producer, leaving the sprite palette stale after a flower pickup. It now uses
the existing area-owned `mysmb_area_queue_player_palette` translation of
`GetPlayerColors`; neither platform adapter participates. The local-area
regression enters through `mysmb_objects_collect_power_up` with a super
player and proves the exact `$3f10`, length-four VRAM command and fiery
palette bytes before the engine-routine handoff.
## S2 P2: restore `Hidden1UpBlock` selector-three branch

The 1-1 source route reached the normal-row object bytes `$06,$83`.  The
low-nibble selector is `Hidden1UpBlock` (`$a065`): when `Hidden1UpFlag` is
set, the ROM clears it and enters `BrickWithItem`, producing
`BrickQBlockMetatiles[3]=$60` in a ground area or `[8]=$59` elsewhere.  The
shared parser had omitted selector three, so it left the metatile buffer
blank; the following `RenderAreaGraphics`/`RenderAttributeTables` pass lost
both `$03fc=$01` and the queued `$23e0=$01` attribute write.  The parser now
implements that source branch and its two table outcomes.  The focused smoke
covers enabled, disabled, and non-ground cases.  The existing 600-sample
pipe/stomp source route is zero-difference for work RAM `$0300-$07ff`, both
CIRAM pages, palette, OAM, audio, and PPU scalars on x86 and x64; remaining
zero-page/stack differences are emulator-private scratch state.  Full CTest
passes 83/83 on each host architecture.  Derived traces and compare reports:
`build/m2-t18-s2-p2-hidden1up/traces/`.