# M2 T46: player graphics control

## Task contract

T46 owns the 43 original labels from `PlayerGfxHandler` (line 14460)
through `C_S_IGAtt` (line 14774), the source-order 14460–14780 slice.
All 43 currently have custody under M2 T16 S4. Three
(`PlayerOffscreenChk`, `PROfsLoop`, `NPROffscr`) are already ROM-match
complete; 40 are audited but incomplete. The incoming baseline is
**1,669 / 1,992** and the maximum is **1,709 / 1,992**. No T47
`ExPlyrAt` or relative-position helper is credited here.

The owner-local `smb1.nes` and reviewed `SMBDIS.ASM` establish original
control flow, RAM/OAM reads and writes, and the PRG table addresses. Both
are nonredistributable research inputs; raw traces, generated output,
build products and local scripts remain below ignored `build/`. The
portable C90 implementation is shared under `src/game/oam/player_gfx.c`;
platform adapters cannot contain graphics decisions. Each S proves
individual labels on an original source-reachable route and compares
native x86/x64 state. The separate operational track runs focused
CTests, strict x86/x64 builds, DOS16 link, platform purity and refreshes
the three owner-authorized EXEs for every P. T closure requires a
cross-chain matrix and final three-target regression.

| S | Contiguous source chain and exact labels | Scope | New |
| --- | --- | ---: | ---: |
| S1 | `PlayerGfxHandler`, `CntPl`, `SwimKT`, `BigKTS`, `ExPGH`, `FindPlayerAction`, `DoChangeSize`, `PlayerKilled`, `PlayerGfxProcessing`, `SUpdR`, `PlayerOffscreenChk`, `PROfsLoop`, `NPROffscr` | 13 | 10 |
| S2 | `IntermediatePlayerData`, `DrawPlayer_Intermediate`, `PIntLoop`, `RenderPlayerSub`, `DrawPlayerLoop` | 5 | 5 |
| S3 | `ProcessPlayerAction`, `ProcOnGroundActs`, `NonAnimatedActs`, `ActionFalling`, `ActionWalkRun`, `ActionClimbing`, `ActionSwimming`, `GetCurrentAnimOffset`, `FourFrameExtent`, `ThreeFrameExtent`, `AnimationControl`, `SetAnimC`, `ExAnimC` | 13 | 13 |
| S4 | `GetGfxOffsetAdder`, `SzOfs`, `ChangeSizeOffsetAdder`, `HandleChangeSize`, `CSzNext`, `GorSLog`, `GetOffsetFromAnimCtrl`, `ShrinkPlayer`, `ShrPlF`, `ChkForPlayerAttrib`, `KilledAtt`, `C_S_IGAtt` | 12 | 12 |
| **Total** | **14460–14774** | **43** | **40** |

S1 follows the original GameEngine player draw child; S2 uses the
world/lives intermediate-draw caller and ordinary player renderer;
S3 returns to the GameEngine action and animation branches; S4 follows
size-change and attribute branches. Calls from S1 into later chains are
recorded as successor edges, never credited by association. All four
remain under T16 S4 custody until individually admitted.

## S1: player draw dispatch, throw and offscreen control

Entry `PlayerGfxHandler` follows T45 `SwimKickTileNum`; exit
`NPROffscr` precedes S2 `IntermediatePlayerData`. Exact scope is
the 13 S1 names above, with ten expected new matches and the three
retained/rechecked offscreen matches. Shared owner:
`src/game/oam/player_gfx.c`. S2–S4 provide the callee action, row
rendering, size and attribute branches; S1 must witness these outgoing
edges without crediting their implementations.

The ROM-logic route is the original GameEngine call into
`PlayerGfxHandler`, using the prior underwater player child fixture
and bounded RAM-only variants at the naturally reached entry. It must
cover injury-frame skip, ordinary versus killed and size-change
dispatch, swimming kick facing/size/frame gates, normal and fireball
throw rendering, and four offscreen-row bits. Record original PCs,
control successors, RAM/OAM reads and writes; compare all non-stack
child RAM/OAM against native x86/x64. Original CPU PC, registers,
stack and ROM remain untouched. The operational baseline is the
prior 84 player children on each width, four focused player/OAM/purity
CTests, full builds and DOS16 link, two Win32 self-tests, and prior
full-suite **222/233** on each width with eleven known failures.

| ROM line | Label | Incoming state | Intended S1 disposition |
| ---: | --- | --- | --- |
| 14460 | `PlayerGfxHandler` | audited; mismatch D5 | new match |
| 14466 | `CntPl` | audited; mismatch D5 | new match |
| 14489 | `SwimKT` | audited; mismatch D5 | new match |
| 14495 | `BigKTS` | audited; mismatch D5 | new match |
| 14497 | `ExPGH` | audited; evidence incomplete | new match |
| 14499 | `FindPlayerAction` | audited; evidence incomplete | new match |
| 14503 | `DoChangeSize` | audited; evidence incomplete | new match |
| 14507 | `PlayerKilled` | audited; evidence incomplete | new match |
| 14511 | `PlayerGfxProcessing` | audited; mismatch D6 | new match |
| 14532 | `SUpdR` | audited; mismatch D6 | new match |
| 14535 | `PlayerOffscreenChk` | ROM-match complete | retained/rechecked |
| 14547 | `PROfsLoop` | ROM-match complete | retained/rechecked |
| 14551 | `NPROffscr` | ROM-match complete | retained/rechecked |

### S1 admission record

The continuing owner-approved M2 source-order mandate admits **M2 T46
S1** with 13 scope labels, ten expected new matches and a maximum of
**1,679 / 1,992**. T16 S4 transfers these exact 13 labels to S1; the
three already-complete offscreen labels remain complete and receive
only recheck evidence. Admission validation is in ignored
`build/m2-t46-s1/node-admission.json`. A node closes only after its
own original control/read/write binding and native equivalence are
shown; a full player-child match alone does not certify every branch.

### S1 closure: dispatch, kick, throw and offscreen

All ten incomplete S1 labels gain ROM-match proof; the three previously
complete offscreen labels are retained and rechecked. S1 has **13 / 13**
matching labels and advances M2 from **1,669** to **1,679 / 1,992**.
No S1 label is deferred. This does not credit the downstream S2–S4
callee bodies.

The original GameEngine reaches `PlayerGfxHandler` without altering
CPU PC, registers, stack or ROM. Forty-two prior swimming/pose variants
and twelve new injury, killed, size, throw and offscreen variants cover
**54 original player child calls**. All **108** paired x86/x64 native
checks match every non-stack byte of the 2 KB RAM/OAM image after the
child. The twelve new variants modify only bounded entry RAM. Raw
snapshots/coverage files were deleted after comparison; neutral summaries
are in ignored `build/m2-t46-s1/survey.json` and
`control-results.json`.

| Label | Original control/read/write and branch evidence |
| --- | --- |
| `PlayerGfxHandler` | Injury timer and frame bit gate the whole child: original `$eeec` both exits 2/52; injury-frame `$eef1` both 1/1. Native returns on the same skipped frame and otherwise performs the same downstream writes. |
| `CntPl` | GameEngineSubroutine killed gate `$eef7` 51/2, size-change gate `$eefc` 49/2, swimming/normal gate `$ef01` 24/25, kick frame gate `$ef07` 16/8. All read original RAM and select the corresponding shared-C paths. |
| `SwimKT` | Facing branch `$ef10` 12/4 selects the seventh/eighth sprite; size branch `$ef19` 2/10 and small-player replacement check `$ef22` 6/6 select or suppress the table write. Original OAM bytes match. |
| `BigKTS` | Both `$ef2d` PRG kick-tile indices were proven in T45 S5; the current source-reached child visits `$ef2d` on both big/small cases and writes the selected OAM tile. |
| `ExPGH` | The injury skip and swim replacement exit converge at `$ef33`; 17 of 54 controlled routes visit this PC, including both exit classes. No write occurs after this return. |
| `FindPlayerAction` | Normal and swim branches reach `$ef34` in 49 routes. It calls the source action selector then enters the graphics-processing continuation; paired child state matches. The action selector body remains S3. |
| `DoChangeSize` | A bounded grow/shrink input naturally reaches `$ef3a`; it calls the size selector and enters the same graphics-processing continuation. The size selector body remains S4. |
| `PlayerKilled` | The killed GameEngine branch reaches `$ef40`, reads original action-offset index 14 and falls into graphics processing; output and scratch match. |
| `PlayerGfxProcessing` | Graphics offset, four-row render, attribute call, throw timer clear/restore and optional rerender match. Original throw gate `$ef53` has 4/49 outcomes; timer compare `$ef60` has 3/1. Full RAM/OAM match resolves T24 D6 for this label. |
| `SUpdR` | Throw rerender selects four rows when speed/buttons are zero, three otherwise: original `$ef73` both outcomes 1/2, `$ef76` reached in three cases, OAM and scratch match. |
| `PlayerOffscreenChk` | Retained prior match; all 53 drawing routes reach `$ef7a`, with bounded high-nibble masks `$00`, `$50`, `$f0`. |
| `PROfsLoop` | Retained prior match; 212 row iterations, source `$ef90` selected/dump outcomes 6/206. |
| `NPROffscr` | Retained prior match; 212 row walks, source `$ef9b` loop/exit outcomes 53/159. |

The similar-issue sweep covered production player graphics, frame-root
dispatch, and every other `Player_OffscreenBits` reference. Shared
`oam/player_gfx.c` alone owns the kick, throw, row masking and attribute
decisions; `player.c` and `objects.c` only maintain shared state, and
the platform trees contain no copy. No product C repair is needed in
S1: T45 S5's player-graphics correction is now certified at these exact
original control PCs.

The separate operational track passes four focused player/OAM/purity
CTests on each width, complete x86/x64 builds, OpenNT DOS16 MZ link and
both Win32 product self-tests. The game implementation did not change
after T45 S5, whose full-suite baseline was **222/233** on both widths
with eleven pre-existing failures. All three executables were rebuilt
and refreshed for this P; their unchanged hashes confirm no accidental
product change:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `8bdff925bb8b871ad1f66d28b5de8c821b74571f8bd523fac6fbbd05ea10c7e0` |
| `assets/mysmb32.exe` | `cd7c19ce9a9e44ac3b752ad2bda909e1992f2053af7e0887f0747f474e88eb3` |
| `assets/mysmb64.exe` | `3cc8de08a3460519c27940e4953a86868be31bed2c2cb2545961500bbf51c5ac` |

## S2: intermediate screen and shared player row renderer

Entry `IntermediatePlayerData` follows S1 `NPROffscr`; exit
`DrawPlayerLoop` precedes S3 `ProcessPlayerAction`. Exact scope:
`IntermediatePlayerData`, `DrawPlayer_Intermediate`, `PIntLoop`,
`RenderPlayerSub`, `DrawPlayerLoop`. All five are incomplete and
transfer from M2 T16 S4 on admission. Shared owner is
`src/game/oam/player_gfx.c`. The intermediate world/lives caller
reaches `DrawPlayer_Intermediate`; the ordinary GameEngine and
fireball-throw callers reach `RenderPlayerSub` and share
`DrawPlayerLoop`. S1's dispatch is the predecessor; S3's action
selector is a caller dependency, not a scope credit.

The original-ROM logic track uses the naturally reached
`--fixture=t27-screen-player-intermediate` frame (original `$efa4`
entry and four `$efdc` row iterations), plus the S1 GameEngine
player child for the ordinary four-row and throw three-row uses of
`RenderPlayerSub`. The intermediate child comparison includes all
non-stack RAM/OAM bytes and a seeded attribute-source difference to
resolve T24 D7. Original table bytes, scratch `$02–$07`, scroll
position, row count, loop successors and OAM attributes must agree
on x86/x64. CPU PC, registers, stack and ROM remain unchanged.

The separate operational track runs focused intermediate/player
graphics tests, x86/x64 full builds and product self-tests, DOS16 MZ
link, platform purity and three owner-authorized EXEs. The S1 baseline
is **1,679 / 1,992**; all five labels are expected new matches, so
maximum closure is **1,684 / 1,992**.

| ROM line / PC | Label | Incoming |
| --- | --- | --- |
| 14561 / `$ef9e` | `IntermediatePlayerData` | audited; evidence incomplete |
| 14564 / `$efa4` | `DrawPlayer_Intermediate` | audited; mismatch D7 |
| 14566 / `$efa6` | `PIntLoop` | audited; mismatch D7 |
| 14587 / `$efbe` | `RenderPlayerSub` | audited; mismatch D6 |
| 14601 / `$efdc` | `DrawPlayerLoop` | audited; mismatch D6 |

### S2 admission record

The continuing owner-approved M2 source-order mandate admits
**M2 T46 S2** with the five exact labels above, all expected new
matches. M2 T16 S4 accepts their transfer to this one shared-game
implementation chain. The admission gate and original route metadata
are under ignored `build/m2-t46-s2/`.

### S2 closure: intermediate data and shared row loop

All **5 / 5** S2 labels are ROM-match complete. M2 advances from
**1,679** to **1,684 / 1,992**, with no S2 deferral. The original
world/lives caller reaches `DrawPlayer_Intermediate` at `$efa4`
without changing CPU PC, registers, stack or ROM. Four bounded
attribute-source variants preserve that natural call and compare the
entire non-stack 2 KB RAM/OAM image after its stack-derived return:
**8/8** native x86/x64 child checks match. The original six data bytes
at PRG `$6f9e–$6fa3` match the reviewed listing locally; the shared
C owner reads them from the owner PRG instead of copying them into
tracked code.

| Label | Original control/data/write binding and witness |
| --- | --- |
| `IntermediatePlayerData` | Six PRG bytes are consumed in reverse order and copied to scratch `$02–$07`. Local listing/ROM data check is **6/6**, and all six resulting scratch bytes match in four original children. |
| `DrawPlayer_Intermediate` | Original `$efa4` reached four times by the world/lives caller. After row drawing, the source reads `Sprite_Attributes+36`, ORs `$40`, and stores `Sprite_Attributes+32`; seeded source/target differences match x86/x64 and resolve T24 D7. |
| `PIntLoop` | Original `$efa6` executes **24** copies across four cases. Branch `$efac` has **20** loop and **4** exit successors; resulting `$02–$07` and all OAM bytes match. |
| `RenderPlayerSub` | Ordinary and fireball-throw GameEngine child routes visit `$efbe` **six** times across four frames. They exercise four-row and three-row calls; scroll-position, scratch and OAM effects match both native widths, resolving T24 D6 for this body. |
| `DrawPlayerLoop` | Original `$efdc` runs **16** intermediate plus **23** ordinary/throw row iterations. The `$efe9` row loop takes **29** repeat and **10** exit successors; table-indexed tiles, scratch countdown and OAM match on both widths. |

The initial original child comparison found nine native differences:
scratch `$00–$07` and the final attribute byte. The repair in shared
`oam/player_gfx.c` restores the original data copy, row-loop scratch
effects and attribute source. A project-owned intermediate child
checker confirms zero non-stack RAM/OAM differences for each variant.
Four GameEngine player children provide a separate full-child check
for ordinary and throw row counts, **8/8** x86/x64 matches. Raw frame,
coverage and child records were deleted after use; only neutral
summaries remain under ignored `build/m2-t46-s2/`.

The similar-issue sweep searched all production player-row callers
and uses of the affected sprite attribute: ordinary and throw
rendering already share the corrected row helper; the intermediate
caller alone had omitted the scratch copy and read the wrong
attribute source. No platform code owns either behavior. The focused
player OAM test now uses synthetic PRG data to verify the input
binding and attribute source without storing protected table bytes.

The separate operational track passes the intermediate original
child checker on x86/x64, three focused CTests per width, complete
x86/x64 builds, OpenNT DOS16 MZ link, both Win32 product self-tests
and platform purity. Full suites each pass **222/233** with exactly
the prior eleven unrelated failures and no new failures. Three
owner-authorized refreshed executables:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `d07cfaec7e989328287cddbb976486287f180290a759890fc4e8db18dba5b8a` |
| `assets/mysmb32.exe` | `c450dbec21e22573bb9aa61cdd3f0746d9360f6e295d819fa640531db5cdc104` |
| `assets/mysmb64.exe` | `1a2fea06ec11eaac1c9634843aa87948c94f42217bfa41b6f94d775d2db8bec4` |
