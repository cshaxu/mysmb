# M2 T27: Screen routines, HUD and game text

## Status

T27 is the source-order screen/HUD/text task for ROM lines 1386--1824. It uses chain-based S delivery: each node remains individually tracked, while one admitted S covers a bounded contiguous source chain and its ROM route. S1 is closed. S2 is the active admitted contiguous status/text chain; S3 is reserved for the two integration roots whose dependencies extend into later source-order tasks.

## Scope and ownership

The 67 exact labels below remain ordered by original source. Shared game owners may write only game-owned RAM, VRAM-buffer, CIRAM, palette and PPU snapshot state. Win32 and DOS adapters only consume the neutral output; they may not choose text, status, palette, task or timer outcomes.

| S | Chain | Lines | Exact labels | ROM route and acceptance focus |
| --- | --- | ---: | --- | --- |
| S1 | Screen-task root, initial setup and palette initialization (`ScreenRoutines -> NoAltPal`) | 1386--1513 | `ScreenRoutines`, `InitScreen`, `SetupIntermediate`, `AreaPalette`, `GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`, `BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`, `GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`, `SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B`, `NoAltPal` | task-vector dispatch, screen setup, intermediate palette call, palette branches and VRAM address writes; exact branch/read/write comparison plus one controlled ROM route, focused project test, x86/x64 build, DOS16 link and platform-purity gate. |
| S2 | Status, intermediate display, title drawing and game text (`WriteTopStatusLine -> NoReset`) | 1517--1813 | exact 43 labels in the table below | one controlled contiguous screen route; all local branches/data loops plus title, status, two-player, time-up, lives/name, warp and reset behavior. `AreaParserTaskControl` is retained for S3 because it calls the current T18 S4 parser owner. |
| S3 | Dispatch/parser integration (`ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol`) | 1386, 1595 | `ScreenRoutines`, `AreaParserTaskControl`, `TaskLoop`, `OutputCol` | close only after every ScreenRoutines table target and the current T18 S4 parser call are independently proven; no duplicate leaf credit. |

## Exact node list

| ROM line | Node | Incoming status | Planned S |
| ---: | --- | --- | --- |
| 1386 | `ScreenRoutines` | open | S3 |
| 1408 | `InitScreen` | ROM-match complete | S1 (closed) |
| 1418 | `SetupIntermediate` | ROM-match complete | S1 (closed) |
| 1436 | `AreaPalette` | ROM-match complete | S1 (closed) |
| 1439 | `GetAreaPalette` | ROM-match complete | S1 (closed) |
| 1442 | `SetVRAMAddr_A` | ROM-match complete | S1 (closed) |
| 1443 | `NextSubtask` | ROM-match complete | S1 (closed) |
| 1448 | `BGColorCtrl_Addr` | ROM-match complete | S1 (closed) |
| 1451 | `BackgroundColors` | ROM-match complete | S1 (closed) |
| 1455 | `PlayerColors` | ROM-match complete | S1 (closed) |
| 1460 | `GetBackgroundColor` | ROM-match complete | S1 (closed) |
| 1465 | `NoBGColor` | ROM-match complete | S1 (closed) |
| 1467 | `GetPlayerColors` | ROM-match complete | S1 (closed) |
| 1473 | `ChkFiery` | ROM-match complete | S1 (closed) |
| 1477 | `StartClrGet` | ROM-match complete | S1 (closed) |
| 1479 | `ClrGetLoop` | ROM-match complete | S1 (closed) |
| 1489 | `SetBGColor` | ROM-match complete | S1 (closed) |
| 1502 | `SetVRAMOffset` | ROM-match complete | S1 (closed) |
| 1507 | `GetAlternatePalette1` | ROM-match complete | S1 (closed) |
| 1512 | `SetVRAMAddr_B` | ROM-match complete | S1 (closed) |
| 1513 | `NoAltPal` | ROM-match complete | S1 (closed) |
| 1517 | `WriteTopStatusLine` | open | S2 |
| 1524 | `WriteBottomStatusLine` | open | S2 |
| 1553 | `DisplayTimeUp` | open | S2 |
| 1560 | `NoTimeUp` | open | S2 |
| 1565 | `DisplayIntermediate` | open | S2 |
| 1577 | `PlayerInter` | open | S2 |
| 1579 | `OutputInter` | open | S2 |
| 1584 | `GameOverInter` | open | S2 |
| 1589 | `NoInter` | open | S2 |
| 1595 | `AreaParserTaskControl` | open; T18 S4 parser dependency | S3 |
| 1597 | `TaskLoop` | open; T18 S4 parser dependency | S3 |
| 1603 | `OutputCol` | open; T18 S4 parser dependency | S3 |
| 1612 | `DrawTitleScreen` | open | S2 |
| 1624 | `OutputTScr` | open | S2 |
| 1629 | `ChkHiByte` | open | S2 |
| 1639 | `ClearBuffersDrawIcon` | open | S2 |
| 1643 | `TScrClear` | open | S2 |
| 1648 | `IncSubtask` | open | S2 |
| 1653 | `WriteTopScore` | open | S2 |
| 1656 | `IncModeTask_B` | open | S2 |
| 1661 | `GameText` | open | S2 |
| 1662 | `TopStatusBarLine` | open | S2 |
| 1671 | `WorldLivesDisplay` | open | S2 |
| 1680 | `TwoPlayerTimeUp` | open | S2 |
| 1682 | `OnePlayerTimeUp` | open | S2 |
| 1686 | `TwoPlayerGameOver` | open | S2 |
| 1688 | `OnePlayerGameOver` | open | S2 |
| 1693 | `WarpZoneWelcome` | open | S2 |
| 1704 | `LuigiName` | open | S2 |
| 1707 | `WarpZoneNumbers` | open | S2 |
| 1712 | `GameTextOffsets` | open | S2 |
| 1719 | `WriteGameText` | open | S2 |
| 1728 | `Chk2Players` | open | S2 |
| 1731 | `LdGameText` | open | S2 |
| 1733 | `GameTextLoop` | open | S2 |
| 1740 | `EndGameText` | open | S2 |
| 1756 | `PutLives` | open | S2 |
| 1765 | `CheckPlayerName` | open | S2 |
| 1775 | `ChkLuigi` | open | S2 |
| 1778 | `NameLoop` | open | S2 |
| 1782 | `ExitChkName` | open | S2 |
| 1784 | `PrintWarpZoneNumbers` | open | S2 |
| 1790 | `WarpNumLoop` | open | S2 |
| 1804 | `ResetSpritesAndScreenTimer` | open | S2 |
| 1809 | `ResetScreenTimer` | open | S2 |
| 1813 | `NoReset` | open | S2 |

## S1 admission contract

S1 is one contiguous source chain: `ScreenRoutines -> InitScreen -> SetupIntermediate -> AreaPalette/GetAreaPalette -> GetBackgroundColor -> GetPlayerColors -> SetBGColor -> GetAlternatePalette1 -> NoAltPal` at ROM lines 1386--1513. It receives exactly the first 21 labels below from T24 S2 custody. Its baseline is 100 / 1,992; all are open; 20 leaf/data nodes are expected to become ROM-match complete, for a maximum 120 / 1,992. `ScreenRoutines` remains in S1 scope but cannot close until its remaining 11 dispatch targets receive their own chain evidence and the final T27 integration chain proves the whole table. It compares every task-vector selection, task-byte increment, area/intermediate branch, palette-table binding, player-status save/restore, VRAM address-control write and carry-return behavior against the owner-supplied local ROM/disassembly. Its operational lane uses focused screen status smoke plus a controlled title-to-area-entry original-ROM route, then x86/x64 native traces, DOS16 link and platform-purity check. Owner-supplied ROM/disassembly are local research inputs only; generated traces stay under ignored `build/` and are not committed.

## T27 closure

T27 closes only after every S1--S3 node has both ROM logic-equivalence evidence and operational evidence, a cross-chain title/area-entry/status/warp matrix passes, all incomplete labels are transferred to accepted successors, and one integrated three-target regression runs.

## S1 closure: screen initialization and palette chain

S1 closes exactly 20 labels: `InitScreen`, `SetupIntermediate`, `AreaPalette`,
`GetAreaPalette`, `SetVRAMAddr_A`, `NextSubtask`, `BGColorCtrl_Addr`,
`BackgroundColors`, `PlayerColors`, `GetBackgroundColor`, `NoBGColor`,
`GetPlayerColors`, `ChkFiery`, `StartClrGet`, `ClrGetLoop`, `SetBGColor`,
`SetVRAMOffset`, `GetAlternatePalette1`, `SetVRAMAddr_B` and `NoAltPal`.
`ScreenRoutines` remains uncredited because its 15-entry table reaches chains
outside S1. The shared C owner now preserves GetBackgroundColor's source order:
it increments `ScreenRoutineTask` before falling through to GetPlayerColors.

The focused smoke covers InitScreen's mode-zero and nonzero branches,
SetupIntermediate's status/background save and restore, the four-color palette
packet, area palette selection, background-control selection and mushroom-style
selection. Title/demo, local-area and platform-purity regressions pass. A
source-reachable one-Start 200-frame ROM route has zero differing frames for
ROM/x86, ROM/x64 and x86/x64 in work RAM `$0300-$07ff`, CIRAM, palette, OAM,
audio and PPU scalars. The shared C builds as the x86/x64 product and links as
OpenNT DOS16 MZ. Refreshed artifacts: `mysmb16.exe`
`646C4FAC9ECA0DDC4D4208177FBB025D5225FDB40787D513A5131996BDF2DAA3`,
`mysmb32.exe` `AE2E88A5244A955250C12D62CD8D2588D3E219D08B17384C4E9A66CA208721FA`,
and `mysmb64.exe` `C0FDADA6D1DBA84C0CAD13CBBD889B0215A7D179ABF517D5C5C6D75D51B45B9E`.

## S2/P1: DisplayIntermediate castle precedence repair

Original ROM lines 1565--1589 take the `AreaType == 3` branch to
`PlayerInter` before testing `DisableIntermediate`. The shared C path had
combined the disable flag with the NoInter condition, causing a castle route
with that flag set to skip the lives display. `game.c` now preserves the
source branch order. `screen_status_smoke` covers the castle/disabled branch;
its intentionally incomplete text source proves the task remains at six
rather than incorrectly taking NoInter task eight. No S2 label is credited by
this narrow repair: the whole 45-label chain still requires its complete
source and ROM-route evidence.

P1 operational evidence: x64 screen-status/local-area/platform-purity CTests
pass; x86 screen-status smoke passes; the shared source rebuilds x86/x64
products and OpenNT DOS16 MZ. Refreshed local artifacts: `mysmb16.exe`
`8CA1BBE6BB79A765245F03E5312CD16C8EB7C06D11586E51462B99CDF62CEFB5`,
`mysmb32.exe` `AE2E88A5244A955250C12D62CD8D2588D3E219D08B17384C4E9A66CA208721FA`, `mysmb64.exe` `C0FDADA6D1DBA84C0CAD13CBBD889B0215A7D179ABF517D5C5C6D75D51B45B9E`.

## S2/P2: PlayerInter before OutputInter

ROM `PlayerInter` at lines 1577--1579 invokes `DrawPlayer_Intermediate`
before it enters `OutputInter/WriteGameText`. The shared screen state machine
now has that exact call order. Existing local-area intermediate and screen
status regressions pass, along with platform purity; x86/x64 products and
OpenNT DOS16 MZ rebuild from the shared source. Refreshed artifacts:
`mysmb16.exe` `22E30540D963EAB0530E3784A802AC5F7E048B790EF8E738512EC3EA94CFB603`,
`mysmb32.exe` `AE2E88A5244A955250C12D62CD8D2588D3E219D08B17384C4E9A66CA208721FA`,
and `mysmb64.exe` `C0FDADA6D1DBA84C0CAD13CBBD889B0215A7D179ABF517D5C5C6D75D51B45B9E`.
No S2 node credit is claimed before the complete chain proof.

## S2/P3: DisplayTimeUp OutputInter writes

ROM lines 1553--1561 clear `GameTimerExpiredFlag` before `OutputInter`, which
then restores `DisableScreenFlag`, resets the timer and advances the screen
task. The shared C now preserves those writes. Focused status, local-area and
platform-purity tests pass; x86/x64 and DOS16 rebuild. `mysmb16.exe`
`3BA599B460EBBB9E3C262BAB75CE2DE97D8B1EF7486B28F862F004D1FC8AE48A`;
x86/x64 artifacts remain the same byte hashes recorded in P2.

## S2/P4: WriteGameText lives and player-name tails

ROM `EndGameText`/`PutLives` writes crown tile `$9f` when the displayed life
count reaches ten, while `CheckPlayerName` also applies to top status selector
zero. The shared text writer now preserves both branches and the TIME UP /
GAME OVER player-selection rule. Local ROM-table smoke coverage, platform
purity and x86/x64 builds pass; DOS16 links. `mysmb16.exe`
`E912E3F3E6967C6D31834F1256937585F5871FAC3358BF0BBE627AE0F67F4ECA`;
the x86/x64 hashes remain as recorded in P3.
## S2 chain-delivery confirmation

S2 retains its admitted 43-label `WriteTopStatusLine -> NoReset` scope and
will close it as one chain.  It does not create separate mapping, migration,
audit, test, or paperwork S stages.  Each remaining P may repair and compare
adjacent members of that chain, but credits none until the shared ROM route and
operational track cover the named label.  Any member blocked by the T18 S4 parser
or another accepted owner transfers by exact name before S2 closes.

## Current-T delivery amendment

This applies from the current S2 closure onward.  S3 and every later T27
receipt use the source-order chain table in the recovery plan, rather than a
fixed mapping/migration/audit/operations/closure sequence.  Each admitted
chain names its entry/exit, exact labels, sole shared-game owner, accepted
dependencies, common ROM route, focused tests, and forecast completion subset.
It completes both evidence tracks and one three-target delivery for the chain,
while preserving individual tracker and ledger disposition for every label.
A split is allowed only for an unadmitted dependency, owner boundary, or
different ROM route; a zero-credit S must name that exact gate.

For S2, the six retained Warp labels remain S2 custody until an accepted
receiver exists: `WarpZoneWelcome`, `WarpZoneNumbers`, `WriteGameText`,
`EndGameText`, `PrintWarpZoneNumbers`, and `WarpNumLoop`. They await the
source-reachable T18 S4 `ScrollLockObject_Warp -> WriteGameText` route. S3 is not a generic receiver for
those leaves: it receives only its four registered dispatch/parser integration
labels.
## S2/P5: unconditional screen-task continuations

The ROM source at lines 1517--1589 has no branch on a native output-capacity
result. `WriteTopStatusLine` and `WriteBottomStatusLine` always reach
`IncSubtask`; `GameOverInter` always reaches `IncModeTask_B`; and the castle
or enabled `PlayerInter` path calls `WriteGameText`, `ResetScreenTimer`, clears
`DisableScreenFlag`, and returns with task seven. The shared C had invented
retry branches when a safe native command writer returned zero. It now keeps
that return only as neutral-output containment and always performs the ROM
state transition. The focused status smoke intentionally supplies an incomplete
text binding for the castle path and proves task 6 becomes 7, screen timer is
7, and screen output is reenabled, so this test cannot confuse a C-only retry
with the original `NoInter` branch.

The similar-issue sweep reviewed every S2 caller of the three text/status
writers in `game.c`: task 2, task 3, GameOverInter and PlayerInter. Task 4 was
already unconditional; task 14 already advances `OperMode_Task` regardless of
the title-score writer result. No platform file contains these decisions.

Operational evidence: focused x64 `screen-status`, `local-area`, and
platform-purity CTests pass; x86 screen-status and local-area executables pass;
both refreshed Win32 products pass `--self-test`; and the same source compiles
and links to the OpenNT DOS16 MZ (existing C4761 warnings only). Refreshed
local artifacts are `mysmb16.exe`
`47ACB049659D01EAC904B698B7111441657D11B421DFE2133A32A50DBB02B06E`,
`mysmb32.exe`
`95D1AF2D2706D658CAFE9ED2122E3DD16F14EFC1BBFF74BB42D6CA6E7B9E4BB0`,
and `mysmb64.exe`
`56C07DD8C873BC12450EAC3C8DB555ED72383DAF8310A9EB4BFA0710704C69E5`.
No S2 node is credited yet: the remaining chain still requires its declared
source-level matrix and controlled original-ROM route.
## S2/P6: controlled cold-title ROM route

The owner-local reference recorder and the current shared-C recorder each
started from the ROM cold state, used zero controller input, and sampled 200
consecutive NMI returns through the title screen path. The native recorder used
its source-owned title bootstrap; the reference recorder ran the owner-supplied
local ROM. Their ignored raw records are bounded below `build/m2-t27-s2/`.
Across all 200 samples, work RAM `$0300-$07ff`, both CIRAM pages, palette, OAM,
audio-command state, and all PPU scalar bytes have zero differing frames. This
operational route exercises the S2 title/status progression with the ROM's
actual VRAM and OAM timing. It does not by itself prove every game-text,
intermediate, two-player, Time Up, Game Over, or Warp branch, so no node credit
is added.

The three focused local title tests also pass on the current x64 owner: title
command transfer, title palette oracle, and cold-title bootstrap sequence.
## S2/P7: controlled Time Up, intermediate and Game Over routes

Three named recorder-only S2 fixtures are applied at a real NMI boundary after
sixty ordinary cold-title samples. They are mirrored in the project-owned
native recorder and the isolated reference recorder; neither is linked into a
product or platform adapter. Each records four subsequent NMI returns.

- `t27-screen-timeup` enters GameMode/ScreenRoutines task four with the timer
  expiry latch set.
- `t27-screen-intermediate` enters GameMode task one/ScreenRoutines task six
  with castle `AreaType` and `DisableIntermediate` set, exercising the source
  `PlayerInter` precedence and its OAM/text/timer tail.
- `t27-screen-gameover` enters GameOverMode task one/ScreenRoutines task six,
  exercising `GameOverInter` and its mode-task transition.

For all three routes, the ROM and current shared C have zero differing frames
in work RAM `$0300-$07ff`, both CIRAM pages, palette, OAM, audio-command state
and PPU scalar output. The recorder source itself builds in the isolated MyNES
reference graph and the native recorder builds in the x64 project graph. This
adds operational branch evidence for the listed screen/text calls; it does not
credit individual labels before the S2 source-level matrix and remaining
text/warp branch routes are complete.
## S2/P8: controlled remaining screen-task branches and Warp selector matrix

Four additional recorder-only snapshots were applied after sixty ordinary
cold-title NMIs on both the local original-ROM reference and the shared-C
recorder. They are injected at the same NMI boundary and each records the next
four NMI returns.

- `t27-screen-no-timeup` enters GameMode task one / screen task four without
  `GameTimerExpiredFlag`, proving the source `NoTimeUp -> IncSubtask` path.
- `t27-screen-player-intermediate` enters the ordinary, non-castle
  `PlayerInter` route and proves its lives-text/OAM/reset tail separately from
  the castle precedence route in P7.
- `t27-screen-reset-pending` enters screen task five with a nonzero
  `ScreenTimer`, proving `NoReset` leaves the task and OAM state intact.
- `t27-screen-reset-expired` enters the same task with zero `ScreenTimer`,
  proving `MoveAllSpritesOffscreen -> ResetScreenTimer -> IncSubtask`.

All four ROM/native comparisons have zero differing samples in work RAM
`$0300-$07ff`, both CIRAM pages, palette, OAM, audio-command state and PPU
scalar output. Raw records remain ignored under
`build/m2-t27-s2/p8-screen-fixtures/`.

The project-owned local-area smoke now independently checks the source table
indices for all three Warp Zone selectors: selector four uses `$07f2-$07f4`,
selector five `$07f6-$07f8`, and selector six `$07fa-$07fc`, with the ROM's
three writes spaced four bytes apart and `$2c` buffer offset. This completes
the local selector matrix but does not replace the still-required
source-reachable original-ROM warp route.

Focused x64 `screen-status`, `local-area` and platform-purity CTests pass; x86
`local-area`, `screen-status` and product self-test pass; the same shared
source links to the OpenNT DOS16 MZ with only the established C4761 and
OLDNAMES warnings. The three user-testable artifacts were refreshed from those
builds: `mysmb16.exe`
`47ACB049659D01EAC904B698B7111441657D11B421DFE2133A32A50DBB02B06E`,
`mysmb32.exe`
`95D1AF2D2706D658CAFE9ED2122E3DD16F14EFC1BBFF74BB42D6CA6E7B9E4BB0`,
and `mysmb64.exe`
`56C07DD8C873BC12450EAC3C8DB555ED72383DAF8310A9EB4BFA0710704C69E5`.

## S2/P9: alternate-entry, two-player text and task-seven routes

The P8 matrix exposed a real shared-owner data binding error. The local ROM's
`LuigiName` is PRG `$07ed-$07f1`; the prior `area.c` binding used `$07e1`,
which is part of the preceding Warp Zone message. The one-player tests did not
exercise the name replacement path, and the existing two-player assertion had
the same incorrect expected offset. The shared binding and its direct smoke
expectation now use `$07ed`. No platform code or product-specific path is
involved.

After the repair, seven additional paired recorder fixtures each have zero
differences across four NMI returns in work RAM `$0300-$07ff`, both CIRAM
pages, palette, OAM, audio-command state and PPU scalars:

- alternate-entry `NoInter`;
- two-player Time Up for both current-player values, proving the required
  inversion before `ChkLuigi`;
- two-player Game Over for both current-player values, proving it does not
  invert before `ChkLuigi`;
- task-seven `ResetSpritesAndScreenTimer` with both pending and expired
  `ScreenTimer` values.

The raw paired records remain ignored below
`build/m2-t27-s2/p9-screen-fixtures/`. This expands branch evidence only; all
43 S2 labels remain uncredited until their complete source and operational
acceptance matrix is closed.

The refreshed P9 artifacts are `mysmb16.exe`
`9B884AC39DC42F4145ED47E956CB89D779414E8A55565E4712147CA0F35574CF`,
`mysmb32.exe`
`2047E4D31CDB0B626C1D4EE0C418820A8EB332D642C9CA431A78755265B904F1`,
and `mysmb64.exe`
`E519F402868C21A8BBF973497CF16249F97F7D8CE5CA923C782F09496CFD55D8`.

## S2/P10: title transfer and buffer-boundary audit

`DrawTitleScreen` reads CHR `$1ec0`, discards the initial PPU read, and the
`OutputTScr` / `ChkHiByte` loop copies exactly `$013a` bytes through CPU RAM
`$0300-$0439`. The owner-local title generator directly extracts that CHR
range. The expanded title-bootstrap smoke now reaches the actual screen task
12 and asserts every copied byte, preserves a `$043a` sentinel, and observes
task advancement to 13. It then reaches task 13, proves the source clear range
`$0300-$04ff`, verifies the ROM-owned eight-byte icon overwrite at the buffer
start, and observes advancement to 14.

This is a direct data/boundary audit plus the existing 200-NMI cold-title ROM
route. It does not credit the nodes: the non-title exits, title-score
`UpdateNumber` collaborator, and final cross-branch matrix remain required.

## S2/P11: non-title title-task exits

The focused x86 and x64 screen-status smoke now enters screen tasks 12 and 13
with a nonzero operating mode. For each, it proves the ROM
`DrawTitleScreen`/`ClearBuffersDrawIcon` `bne IncModeTask_B` behavior:
`OperMode_Task` advances and `ScreenRoutineTask` remains unchanged. This is
source-control evidence only; the title route itself remains covered by P10.

## S2/P12: direct GameText offset-table audit

The local-area smoke now asserts the owner-ROM `GameTextOffsets` bytes at
PRG `$07fe-$0806` and the five message terminators at `$0778`, `$0797`,
`$07aa`, `$07bf` and `$07ec`. This records the actual local-ROM table shape
for top status, lives, both Time Up/Game Over choices and Warp Zone rather than
deriving data positions from the differing listing revision.

## S2/P13: title-mode NoInter precedence

The focused screen-status smoke enters task six with title `OperMode`, castle
area type and an enabled intermediate display. It proves the source's first
title-mode test takes `NoInter` to task eight before all later conditions.

The focused assertion passes on x64 and x86. Both Win32 products pass their
native self-test, and the same shared source links as the OpenNT DOS16 MZ
(only the established C4761 warnings). The refreshed artifacts are
`mysmb16.exe` `9B884AC39DC42F4145ED47E956CB89D779414E8A55565E4712147CA0F35574CF`,
`mysmb32.exe` `2047E4D31CDB0B626C1D4EE0C418820A8EB332D642C9CA431A78755265B904F1`,
and `mysmb64.exe` `E519F402868C21A8BBF973497CF16249F97F7D8CE5CA923C782F09496CFD55D8`.

## S2/P14: complete GameText selector/data-tail matrix

One project-owned smoke now invokes selectors zero through six from a fresh
shared game state. For every selector it derives the source offset and the
terminator length from the locally bound ROM at run time, then compares every
copied command byte and its terminator. The same matrix covers selector-zero
Luigi replacement, both TIME UP player inversions, both GAME OVER player
choices, the lives crown/world/level patches, and all three spaced Warp Zone
number patches. It contains no message or asset fixture.

This is direct source/data and shared-C evidence for the contiguous
`GameTextOffsets -> WarpNumLoop` branch family. The paired Time Up/Game Over
fixtures already provide its NMI-route evidence. The Warp entry remains
pending a source-reachable original-ROM parser route, so no node credit is
claimed by this P.

The matrix passes as the x64 CTest and x86 executable smoke; both Win32
products pass self-test, and the shared source links as DOS16 with the
established C4761 warnings. The refreshed artifacts are `mysmb16.exe`
`9B884AC39DC42F4145ED47E956CB89D779414E8A55565E4712147CA0F35574CF`,
`mysmb32.exe` `2047E4D31CDB0B626C1D4EE0C418820A8EB332D642C9CA431A78755265B904F1`,
and `mysmb64.exe` `E519F402868C21A8BBF973497CF16249F97F7D8CE5CA923C782F09496CFD55D8`.

## S2/P15: original W1-2 Warp object binding

The local-area smoke no longer copies a synthetic three-byte area stream. It
positions the persistent parser at W1-2's actual PRG `$2cd5` row-13 Warp
object (`$6d,$c5`) with its required page and column state. The test proves
the parser selects Warp text selector five, writes the true Warp command
stream, and patches the selector-five three-number row from the local ROM.

An isolated reference-frame experiment reached the same original object but
showed an earlier GameCore-route difference: the ROM's timer command and the
native player's palette command diverge before the common parser output. That
precondition belongs to the accepted T18 S4 parser chain. It is
therefore recorded as a dependency, not hidden with a T27 RAM workaround; the
source-reachable ROM frame route remains pending T18 S4. No S2 node credit is
claimed here.

The local test passes in both x64 and true i686 Win32 builds. The Win32
self-tests and OpenNT DOS16 link pass; the latter retains only its established
C4761 warnings. The refreshed artifacts are `mysmb16.exe`
`9B884AC39DC42F4145ED47E956CB89D779414E8A55565E4712147CA0F35574CF`,
`mysmb32.exe` `66776FB670940ED69BB80F085449B83848E8EB7687391201E3DF9BCD661C3331`,
and `mysmb64.exe` `9A932AF31C68EFD3C339D0F66BB60BF7DD0110E08652620E00E93989BBFC65AC`.

## S2/P16: task-two two-player status-chain proof

The local-ROM smoke now enters the actual `ScreenRoutines` task-two dispatch
with `NumberOfPlayers=1` and `CurrentPlayer=1`.  It proves the exact shared
route `WriteTopStatusLine -> IncSubtask`, with the intervening
`TopStatusBarLine -> WriteGameText -> CheckPlayerName -> NameLoop` output
coming from the local ROM's `$07ed-$07f1` Luigi name bytes.  The test also
checks the source task transition from two to three and the initial `$2043`
VRAM command, so it cannot be satisfied by a direct text-writer call.

This fills the only remaining local proof gap for `WriteTopStatusLine`; it
does not claim S2 closure or conceal the independent `GetSBNybbles`,
`UpdateNumber`, and T18 S4 Warp-route dependencies.  The focused local-area and
screen-status smokes, together with platform-purity, pass in the x64 owner
build.  Cross-width products and the DOS16 link are refreshed for this P.
The refreshed artifacts are `mysmb16.exe`
`9B884AC39DC42F4145ED47E956CB89D779414E8A55565E4712147CA0F35574CF`,
`mysmb32.exe` `66776FB670940ED69BB80F085449B83848E8EB7687391201E3DF9BCD661C3331`,
and `mysmb64.exe` `9A932AF31C68EFD3C339D0F66BB60BF7DD0110E08652620E00E93989BBFC65AC`.

## S2/P17: partial chain conformance disposition

The retained ROM recordings were rechecked: the 200-frame cold-title route
and 14 four-frame fixtures cover Time Up, Game Over, castle and ordinary
intermediate display, title/alternate-entry `NoInter`, both reset branches,
and title tasks 12/13. The compared work RAM `$0300-$07ff`, CIRAM, palette,
OAM, audio state and PPU scalars are zero-difference in every route.

This P credits the 35 self-contained labels with both source/data and route
evidence. It retains eight labels without credit: `WriteBottomStatusLine`
awaits `GetSBNybbles`; `WriteTopScore` awaits `UpdateNumber`; and
`WarpZoneWelcome`, `WarpZoneNumbers`, `WriteGameText`, `EndGameText`,
`PrintWarpZoneNumbers`, and `WarpNumLoop` await T18 S4's parser
precondition for a source-reachable Warp route. S2 remains active and keeps
their custody.

## S2/P18: remove the synthetic GameCore status recovery

The source call graph separates the two mode-task paths: `GameMode` task one
dispatches `ScreenRoutines`, whose table entry three reaches
`WriteBottomStatusLine`; task three dispatches `GameCoreRoutine` and has no
status-writer call.  The shared frame root had added a GameCore-tail recovery:
when `ScreenRoutineTask == 3`, it called the bottom-status writer and advanced
the task only when the native buffer helper returned success.  That call and
its capacity-dependent state transition do not exist in the ROM.

The recovery call is removed.  `game.c` remains the translated caller for the
GameMode task-three status entry and preserves the original unconditional
`IncSubtask` transition.  The focused shared-game smoke sets GameMode task
three and a sentinel screen task three, then proves a frame-root GameCore turn
does not alter either `ScreenRoutineTask` or the VRAM-buffer offset.  This is
the controlled operational counterpart to the original `GameMode` task vector
and `GameCoreRoutine` source comparison; it adds no node credit because the
`GetSBNybbles` helper remains under its registered owner.

Focused `screen-status`, `local-area`, and platform-purity CTests pass on both
native widths; each Win32 executable passes `--self-test`; the shared source
links as OpenNT DOS16 with only established C4761 warnings.  The refreshed
artifacts are `mysmb16.exe`
`426E82B0FD0065BACD6DC54F7A0E51DCB9A3FA5C6AC2602782F83691DE850E94`,
`mysmb32.exe`
`B5F6F8C178BBDCBDFAA019A7DFDBD6350A843ECB737A188E26A1CD9DBBE12D7B`,
and `mysmb64.exe`
`2606478C41C3122B2500E6465FE570C6C6B2292608D9C65A468846217624E3EE`.

The post-repair ROM replay regenerates the 200-frame zero-input cold-title
route and all fourteen four-frame controlled screen fixtures: Time Up,
castle/ordinary intermediate, Game Over, NoTimeUp, alternate NoInter, both
task-five and task-seven timer outcomes, and both Mario/Luigi Time Up and Game
Over selections.  Every sample has zero differences in work RAM `$0300-$07ff`,
both CIRAM pages, palette, OAM, audio state and PPU scalars.  The raw paired
records remain ignored below `build/m2-t27-s2/p18-regression/`.

## S2/P19: status caller-boundary completion

Two recorder-only snapshots now enter the original `ScreenRoutines` table at
task three and task fourteen after sixty ordinary cold-title NMIs.  The first
executes `WriteBottomStatusLine`: it crosses the registered external
`GetSBNybbles` boundary, appends the World/Level command, sets the resulting
buffer offset, and takes the unconditional `IncSubtask` edge.  The second
executes `WriteTopScore`: it enters `UpdateNumber` with the source `$fa`
selector, then takes `IncModeTask_B`.  Each native/reference four-frame pair
has zero differences in work RAM `$0300-$07ff`, CIRAM, palette, OAM, audio and
PPU scalars.

`WriteBottomStatusLine` and `WriteTopScore` are therefore complete as caller
nodes: their source entry, external-call boundary, own writes and successor
edge all have both evidence tracks.  This does not credit `GetSBNybbles`,
`UpdateNumber`, `PrintStatusBarNumbers`, or `NoZSup`; those helper nodes retain
their T22 S5 responsibility and require their own chain evidence.  The paired
records remain ignored under `build/m2-t27-s2/p19-status-callers/`.

The recorder sources compile on x86 and x64.  Focused screen-status,
local-area and platform-purity CTests pass on both widths, and both Win32
products pass `--self-test`.  The shared product relinks under OpenNT DOS16
with the established C4761 warnings only; the three packaged artifact hashes
remain
`426E82B0FD0065BACD6DC54F7A0E51DCB9A3FA5C6AC2602782F83691DE850E94`,
`B5F6F8C178BBDCBDFAA019A7DFDBD6350A843ECB737A188E26A1CD9DBBE12D7B`, and
`2606478C41C3122B2500E6465FE570C6C6B2292608D9C65A468846217624E3EE` for
DOS16, Win32 x86 and Win32 x64 respectively.

## S2/P20: Warp-route ownership correction

The original route inspection corrects an earlier dependency attribution.  The
W1-2 stream reaches `ScrollLockObject_Warp` at ROM line 3591, then `WarpNum`
sets `WarpZoneControl` and the object handler calls `WriteGameText` at line
3602.  The parser nodes `ScrollLockObject_Warp`, `WarpNum`, and
`ScrollLockObject` are currently received by M2 T18 S4 in the canonical
ledger.  They are not T29 or GameCore nodes.  The existing local-area smoke
does exercise the real `$6d,$c5` W1-2 object bytes and observes its selector
five output, but it is not an accepted original-ROM equivalence proof of that
T18 S4 chain.  Consequently the six T27 Warp leaves retain their existing
custody and no credit changes in this P; their concrete prerequisite is now
recorded accurately for the later accepted transfer.

## S2 per-node source/evidence matrix

This matrix is the S2 source-review record. `Mapped` means the ROM branch,
read/write sequence and shared-C owner were reviewed. `Route` names operational
coverage already obtained; it is not a completion mark. `Pending` names the
remaining required branch or dependency. Every row remains incomplete until
both tracks are accepted at S2 closure.

| Node | Shared-C mapping | Current evidence and remaining proof |
| --- | --- | --- |
| `WriteTopStatusLine` | `game.c` task 2 -> `area.c` top-text writer | Mapped; cold-title route, direct selector matrix and P16 two-player task-two ROM-data chain. Local proof complete; retained for S2 chain closure. |
| `WriteBottomStatusLine` | `game.c` task 3 -> `area.c` bottom-status writer | ROM-match complete at its caller boundary: P19 task-three controlled ROM route proves its helper call, own World/Level writes and `IncSubtask`. `GetSBNybbles` remains independently incomplete under T22 S5. |
| `DisplayTimeUp` | `game.c` task 4 | Mapped; screen-status smoke and `t27-screen-timeup` zero-difference route. Pending final chain matrix. |
| `NoTimeUp` | `game.c` task 4 else | Mapped; screen-status smoke and `t27-screen-no-timeup` zero-difference route. Pending final chain matrix. |
| `DisplayIntermediate` | `game.c` task 6 | Mapped; castle, ordinary and alternate-entry fixtures. Pending final branch matrix. |
| `PlayerInter` | `game.c` task 6 and intermediate OAM owner | Mapped; castle and ordinary fixtures prove call order and output tail. Pending final text/name matrix. |
| `OutputInter` | `game.c` task 4/task 6 common writes | Mapped; Time Up and intermediate fixtures. Pending common-path byte matrix. |
| `GameOverInter` | `game.c` task 6, `terminal_modes.c` game-over root | Mapped; one-player plus both two-player-name zero-difference routes. Pending final text-byte matrix. |
| `NoInter` | `game.c` task 6 direct task-8 assignment | Mapped; local-area, alternate-entry and P13 title-mode precedence routes. Pending final cross-branch matrix. |
| `DrawTitleScreen` | `game.c` task 12 | Mapped; 200-frame cold-title route, P10 exact byte matrix and P11 non-title exit. Pending final cross-branch matrix. |
| `OutputTScr` | `game.c` title-data copy loop | Mapped; P10 CHR `$1ec0` / 314-byte task-12 audit. Pending final cross-branch matrix. |
| `ChkHiByte` | `game.c` title-data copy bound | Mapped; P10 `$043a` untouched sentinel. Pending final cross-branch matrix. |
| `ClearBuffersDrawIcon` | `game.c` task 13 | Mapped; P10 clear/icon audit, cold-title route and P11 non-title exit. Pending final cross-branch matrix. |
| `TScrClear` | `game.c` task 13 clear loop | Mapped; P10 complete `$0300-$04ff` audit. Pending final cross-branch matrix. |
| `IncSubtask` | `game.c` task transitions | Mapped; all screen fixtures. Pending final table-wide transition matrix. |
| `WriteTopScore` | `game.c` task 14 -> `area.c` title-score writer | ROM-match complete at its caller boundary: P19 task-fourteen route proves `$fa` helper entry and `IncModeTask_B`. `UpdateNumber` remains independently incomplete under T22 S5. |
| `IncModeTask_B` | `game.c` tasks 12/14 and Game Over branch | Mapped; title and Game Over routes plus P11 non-title task-12/task-13 exits. Pending final cross-branch disposition only. |
| `GameText` | bound local PRG data in `area.c` | Mapped; P14 derives every source text byte/terminator at run time. Pending final chain matrix. |
| `TopStatusBarLine` | selector zero in `area.c` | Mapped; cold-title, two-player Luigi and P14 full-byte matrix. Pending final chain matrix. |
| `WorldLivesDisplay` | selector one in `area.c` | Mapped; local-area, ordinary `PlayerInter` and P14 crown/world/level matrix. Pending final chain matrix. |
| `TwoPlayerTimeUp` | selector two source offset in `area.c` | Mapped; both current-player Time Up routes and P14 full-byte matrix. Pending final chain matrix. |
| `OnePlayerTimeUp` | selector two source offset in `area.c` | Mapped; Time Up fixture and P14 direct source-byte matrix. Pending final chain matrix. |
| `TwoPlayerGameOver` | selector three source offset in `area.c` | Mapped; both current-player Game Over routes and P14 full-byte matrix. Pending final chain matrix. |
| `OnePlayerGameOver` | selector three source offset in `area.c` | Mapped; Game Over fixture and P14 direct source-byte matrix. Pending final chain matrix. |
| `WarpZoneWelcome` | selector four source offset in `area.c` | Mapped; P15 replaces synthetic stream with original W1-2 parser data. Pending controlled original ROM Warp route after the T18 S4 `ScrollLockObject_Warp` precondition. |
| `LuigiName` | `area.c` name replacement loop | Corrected local ROM binding `$07ed`; P14 direct five-byte matrix plus two-player routes. Pending final chain matrix. |
| `WarpZoneNumbers` | `area.c` selector-four-to-six patch source | Mapped; P14 full-byte matrix and P15 original W1-2 selector-five parser route. Pending source-reachable original-ROM Warp route after the T18 S4 `ScrollLockObject_Warp` precondition. |
| `GameTextOffsets` | local PRG offset selection in `area.c` | Mapped; P12 table audit and P14 every-selector matrix. Pending final chain matrix. |
| `WriteGameText` | `area.c` text writer | Mapped; P14 full selector/copy/tail matrix, existing screen routes, and P15 original W1-2 parser data. Pending source-reachable Warp route after the T18 S4 `ScrollLockObject_Warp` precondition. |
| `Chk2Players` | `area.c` selector two/three offset choice | Mapped; both two-player routes and P14 selector matrix. Pending final chain matrix. |
| `LdGameText` | `area.c` PRG source selection | Mapped; P14 every-selector direct source-byte matrix. Pending final chain matrix. |
| `GameTextLoop` | `area.c` terminator-copy loop | Mapped; P14 derives and checks every stream length and terminator. Pending final chain matrix. |
| `EndGameText` | `area.c` terminator/tail dispatch | Mapped; P14 lives/name/warp tail matrix and P15 parser binding. Pending source-reachable Warp route after the T18 S4 `ScrollLockObject_Warp` precondition. |
| `PutLives` | `area.c` lives/world/level patch | Mapped; P14 crown/world/level matrix and ordinary `PlayerInter` route. Pending final chain matrix. |
| `CheckPlayerName` | `area.c` player-name selection | Mapped; P14 matrix and both Time Up/Game Over routes. Pending final chain matrix. |
| `ChkLuigi` | `area.c` current-player branch | Mapped; P14 both current-player values and two-player routes. Pending final chain matrix. |
| `NameLoop` | `area.c` five-byte Luigi replacement | Corrected `$07ed-$07f1` binding; P14 direct-byte matrix. Pending final chain matrix. |
| `ExitChkName` | `area.c` name tail exit | Mapped; P14 complete selector matrix. Pending final chain matrix. |
| `PrintWarpZoneNumbers` | `area.c` selector-four-to-six patch | Mapped; P14 matrix and P15 original W1-2 selector-five route. Pending source-reachable original-ROM Warp route after the T18 S4 `ScrollLockObject_Warp` precondition. |
| `WarpNumLoop` | `area.c` three spaced writes | Mapped; P14 matrix and P15 original W1-2 selector-five route. Pending source-reachable original-ROM Warp route after the T18 S4 `ScrollLockObject_Warp` precondition. |
| `ResetSpritesAndScreenTimer` | `game.c` tasks 5 and 7 -> `boot.c` sprite hide | Mapped; task-five and task-seven pending/expired zero-difference routes. Pending common-tail matrix. |
| `ResetScreenTimer` | `game.c` OutputInter and tasks 5/7 | Mapped; Time Up and intermediate routes. Pending common-tail matrix. |
| `NoReset` | `game.c` tasks 5/7 timer-nonzero branch | Mapped; task-five and task-seven pending zero-difference routes. Pending common-tail matrix. |
