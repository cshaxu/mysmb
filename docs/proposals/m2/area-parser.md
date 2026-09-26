# M2 T18: Area graphics and parser

## Status

**M2 T18 active — S2/P4 and S3/P1.** The ROM continuation reaches `ReplaceBlockMetatile` after block state has already been produced. Its missing `$03f0` increment belongs to the area/metatile output slice, so this task owns the producer rather than adding a compensating write to objects or OAM.

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
## S2 P3: restore `RenderUnderPart` scratch and horizontal-row entry

ROM `Hole_Empty` enters `RenderUnderPart` with `X=$08`, `Y=$0f`; every loop re-entry stores its current Y to `AreaObjectHeight` (`$0735`) before writing a block-buffer row.  The native parser had hand-written rows 8–12 and omitted that source scratch state.  ROM `RowOfBricks`, `RowOfSolidBlocks`, and `RowOfCoins` likewise enter the same helper with `Y=$00` on every continuation column; direct native writes left stale `$0735`.  The shared area owner now uses the translated helper for both call paths, with the per-entry store in source order.  The focused parser smoke asserts the hole result `$0735=$0b`.  In the controller-only cold 600-frame reference route (global frames 600–1199), work RAM `$0300-$07ff`, CPU OAM backing, both CIRAM pages, palette, visible OAM, audio state, and all PPU scalars are zero-difference; `$0735` is `$0b` at global frame 1030 and returns to `$00` at 1116 exactly as in the ROM.  Full x64 and x86 CTest pass 83/83, and the same source links the OpenNT DOS MZ.  Refreshed artifacts: mysmb16.exe `70989598666E6CDA85239E7D43A5BBFFC764E1AB1D4E872CA7DFBD36612F03E1`, mysmb32.exe `2862DDBB1D816A38819D2F36B65343EA5B568DEDA81A35CF15C17A645AAA0877`, mysmb64.exe `9EEC3920CB4EC230E87C24C9CBC7E93741CD2AB4E3141C49F3345E14C2914F75`.
## S2 P4: restore the admitted `CastleObject` column path

The controller-only page-twelve route reaches area bytes `$af,$26`. ROM
`CastleObject` first calls `GetLrgObjAttrib`, then `sty $07`; therefore `$07`
holds the second-byte low nibble (`$06`), not the first-byte row `$0f`.
`ChkLrgObjFixedLength` installs four, `CastleMetatiles[4]` is written at
buffer rows 6--10, and the `ProcessAreaData` tail leaves `$0732=$03`.
The focused parser smoke fixes that exact input and asserts `$06a9-$06ab =
$45,$47,$47` plus the post-decrement length. The subsequent star-flag setup
leaf is retained for the next admitted CastleObject packet; this P reaches
only the source-proven route above.

The 2,220-frame-warmup controller-only ROM replay now has zero differences in
both CIRAM pages, palette, and every PPU scalar across all 600 samples. The
former first parser difference at sample 526 is absent. Its remaining late
sample-599 work-RAM/audio byte and the three late OAM bytes predate neither
CastleObject output nor a visible divergence and stay queued for their named
owners. Full CTest passes 83/83 on x64 and x86, including platform purity;
the shared OpenNT DOS16 link succeeds with its existing `OLDNAMES.LIB`
warning. Artifacts: mysmb16.exe
`BFED12E8BC1201BFE63F774584291DC701D7713523BE91341C5EB1C8942BB790`,
mysmb32.exe `F27A8D690D20AD0D4B58F962F4F7491E01066E2AEE777A5785B5DE39862EDC0D`,
and mysmb64.exe
`4A3067235777F65EAD2912B31E238549A087D6E20F3549EDB11B2FE367F4DA3E`.