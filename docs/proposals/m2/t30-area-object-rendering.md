# M2 T30: Area object rendering and metatile chains

T30 follows closed T29 geometry and resumes original source order at the first
uncompleted label after `FlagpoleObject`.  It owns the area-object rendering,
metatile and block-buffer portion of the recovery-plan range.  Each admitted S
receives one bounded chain from the existing T18 custody; future T30 chains
remain unadmitted until their exact predecessor and source route are recorded.

All behavior stays in portable `src/game`.  Windows and DOS provide only
input, timing and completed-frame submission.  The owner-supplied SMB1 NROM
and reviewed disassembly are local-only evidence inputs; no ROM-derived source
or trace becomes tracked product data.

## T30/S1 admission: rope object rendering chain

| Field | Record |
| --- | --- |
| Entry and exit | `EndlessRope -> DrawRope` |
| Exact source-order labels | `EndlessRope` (4018), `BalancePlatRope` (4023), `DrawRope` (4034) |
| Shared owner | `src/game/area.c`, including the neutral area-object state and its existing UnderPart collaborator |
| Receipt | `transfer-098-t18-s4-to-t30-s1-rope-rendering` transfers the three labels from T18 custody |
| Predecessor / successor | T29/S10's completed allocation/final-object boundary precedes this chain; `CoinMetatileData -> RowOfCoins` is the next unadmitted T30 chain |
| ROM-logic track | Audit `$99bb-$99cc`: Endless uses `X=0,Y=15`; balance saves/restores object offset, clears rows 1..15 using `$44`, obtains the lower-nibble length, then uses `X=1`; DrawRope tail-jumps with `$40`. The ordinary area-parser object route exercises the same parser dispatch; source-shaped object records cover the mutually exclusive endless and balance variants without leaf-PC or stack injection. |
| Operational track | Add focused project-owned rope/area smoke coverage, compare the chain-owned parser/metatile state against the original route, build x86/x64, link DOS16, run platform-purity, and refresh all three target artifacts once for implementation P1. |

Baseline: **430 / 1,992**.  Incoming state for every scope label is `open`.
Expected new matches: the same three labels.  Maximum result: **433 / 1,992**.
No renderer, platform adapter, unrelated area object, or `RenderUnderPart`
node receives credit in this S.

## T30 chain order after S1

T30 continues strictly in inventory source order.  The next admissions begin
with `CoinMetatileData -> RowOfCoins`, then retain the adjacent row/column,
cannon/stair, question/brick, hole/underpart, length/attribute and block-buffer
chains as separate receipts where their caller or ROM route changes.  This is
a boundary map only; no later T30 label is admitted or credited by S1.

## S1/P1: ROM rope chain and three-target delivery

`EndlessRope` at `$99d0` loads `X=$00`, `Y=$0f` and tail-enters
`DrawRope`.  `BalancePlatRope` at `$99d7` preserves the parser object offset
across its `$44` blanking pass at `X=$01,Y=$0f`, reloads the second object
byte's low nibble through `GetLrgObjAttrib`, then enters the same `DrawRope`
entry at `$99e9`.  Shared `area.c` now represents those three labels as
`mysmb_area_endless_rope`, `mysmb_area_balance_platform_rope` and
`mysmb_area_draw_rope`; the latter is the one `$40` call into the separately
owned `RenderUnderPart` primitive.

The project-owned `mysmb.area-rope-object-smoke` uses ordinary row-15
area-parser records, never a leaf-PC or stack entry.  It verifies the endless
13-row rope output and terminal height, then verifies the balance rope's
blanking-before-low-nibble-reload order, rope/blank boundary and terminal
height.  The existing special-object smoke remains green.  This is the
operational track; the ROM-logic track is the branch, register and shared-RAM
write audit above.

The manual C90 x64 and x86 smoke builds passed, and their Windows executables
passed `--self-test`.  OpenNT16 linked `mysmb-dos16.exe` as an `MZ` image.
`python test/test_platform_purity.py` passed.  The refreshed artifacts are
`assets/mysmb16.exe` SHA-256
`8BB51F180C55172BA7E324AC1003E8010D3912DAC9659F53F6833A0C9314B241`,
`assets/mysmb32.exe` SHA-256
`5A31D204F5797B78DEA9828C443FB1A47A5080D677917D43D6F82353BD40C937`, and
`assets/mysmb64.exe` SHA-256
`FC89FD9626FFDC11A71F33E191F8A5F71F82CEAAF0309A7EF2C8EA9EC790A1DC`.

All three scope labels are ROM-match complete.  The result is **433 / 1,992**;
there are no uncompleted labels in this receipt.  `CoinMetatileData -> RowOfCoins`
remains the next unadmitted source-order chain.