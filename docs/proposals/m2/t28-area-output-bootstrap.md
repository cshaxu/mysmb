# M2 T28: Area output primitives and bootstrap

## Status

T28 is the source-order receiver for ROM lines 1825--2794. It begins after
T27's screen task and precedes T29's area-object parser. All behavior stays in
shared game code; host adapters only submit the resulting frame and input.

**T28 S1--S6 are closed at 230 / 1,992.** S7 is the active source-order
chain. T28 S6 owned only the twelve-label joypad/VRAM-output/NMI chain below.

## Exact source-order chains

| S | Entry and exit | Exact labels in source order | Dependency and common proof route |
| --- | --- | --- | --- |
| S1 | `RenderAreaGraphics -> RenderAttributeTables -> SetVRAMCtrl` | `RenderAreaGraphics`, `DrawMTLoop`, `RightCheck`, `LLeft`, `NextMTRow`, `SetAttrib`, `ExitDrawM`, `RenderAttributeTables`, `SetATHigh`, `AttribLoop`, `SetVRAMCtrl`, `MetatileGraphics_Low`, `MetatileGraphics_High` | T29 supplies ordinary parser-produced metatiles. A controlled ROM/native entry seeds the same metatile/task/nametable state and compares Buffer2, attribute state, address-control and output. |
| S2 | `ColorRotation -> ExitColorRot` | `ColorRotatePalette`, `BlankPalette`, `Palette3Data`, `ColorRotation`, `GetBlankPal`, `GetAreaPal`, `ExitColorRot` | T31 GameEngine is the natural caller. Controlled frame-boundary entries cover every-eighth-frame, buffer-capacity and rotate-wrap branches. |
| S3 | `RemoveCoin_Axe -> RemBridge` | `BlockGfxData`, `RemoveCoin_Axe`, `WriteBlankMT`, `ReplaceBlockMetatile`, `DestroyBlockMetatile`, `WriteBlockMetatile`, `UseBOffset`, `MoveVOffset`, `PutBlockMetatile`, `SaveHAdder`, `RemBridge` | T36/T37 block and endgame producers supply requests. Controlled block-buffer fixtures prove source command and offset order. |
| S4 | metatile, palette and message data | `Palette0_MTiles`, `Palette1_MTiles`, `Palette2_MTiles`, `Palette3_MTiles`, `WaterPaletteData`, `GroundPaletteData`, `UndergroundPaletteData`, `CastlePaletteData`, `DaySnowPaletteData`, `NightSnowPaletteData`, `MushroomPaletteData`, `BowserPaletteData`, `MarioThanksMessage`, `LuigiThanksMessage`, `MushroomRetainerSaved`, `PrincessSaved1`, `PrincessSaved2`, `WorldSelectMessage1`, `WorldSelectMessage2` | Consumers from S1--S3, T27 and T31 bind local source bytes; direct table/consumer comparisons prove every byte. |
| S5 | `JumpEngine -> InitATLoop` | `JumpEngine`, `InitializeNameTables`, `WriteNTAddr`, `InitNTLoop`, `InitATLoop` | T27 `InitScreen` and T31 mode roots call it. Controlled table-vector/name-table entries cover all branches. |
| S6 | `ReadJoypads -> WritePPUReg1` | `ReadJoypads`, `ReadPortBits`, `PortLoop`, `Save8Bits`, `WriteBufferToScreen`, `SetupWrites`, `GetLength`, `OutputToVRAM`, `RepeatByte`, `UpdateScreen`, `InitScroll`, `WritePPUReg1` | T22 NMI owns the natural route. ROM/native NMI traces and controlled output commands prove serial input and output packet behavior. |
| S7 | `PrintStatusBarNumbers -> NoTopSc` | `StatusBarData`, `StatusBarOffset`, `PrintStatusBarNumbers`, `OutputNumbers`, `SetupNums`, `DigitPLoop`, `ExitOutputN`, `DigitsMathRoutine`, `AddModLoop`, `StoreNewD`, `EraseDMods`, `EraseMLoop`, `BorrowOne`, `CarryOne`, `UpdateTopScore`, `TopScoreCheck`, `GetScoreDiff`, `CopyScore`, `NoTopSc` | T27/T35/T36 callers provide source selectors. Direct arithmetic and status-output routes cover all carries, borrows and zero suppression. |
| S8 | `InitializeGame -> ISpr0Loop` | `DefaultSprOffsets`, `Sprite0Data`, `InitializeGame`, `ClrSndLoop`, `InitializeArea`, `ClrTimersLoop`, `StartPage`, `SetInitNTHigh`, `SetSecHard`, `CheckHalfway`, `DoneInitArea`, `PrimaryGameSetup`, `SecondaryGameSetup`, `ClearVRLoop`, `ShufAmtLoop`, `ISpr0Loop` | T22 first-NMI and T31 mode roots supply entry. Cold-start and area-entry routes prove initialization, no host-owned gameplay branch. |

## S1 admission contract

S1 receives exactly its thirteen listed labels from the legacy T18 receiver.
The baseline is 163 / 1,992; all thirteen are open and are expected to become
ROM-match complete, for a maximum of 176 / 1,992. The shared owners are
`src/game/area.c` and the neutral frame-output contract; no platform source is
in scope. Its equivalence track compares the original loop, row/side attribute
bits, metatile-table reads, Buffer2 packet, attribute packet and `$0773`
write. Its operational track uses a controlled original-ROM/native entry,
focused renderer regression, x86/x64 builds, DOS16 link, platform-purity gate
and the three packaged executables.

## T28 closure

T28 closes only after all eight chains have independent ROM logic-equivalence
and operational proof, incomplete labels have accepted successors, and one
cross-chain area-entry/NMI/output matrix passes on all three targets.

## S1/P1 renderer and attribute equivalence result

S1 closes at **176 / 1,992**: all thirteen admitted labels are ROM-match
complete. `area.c` exposes the two original shared-game entries without
creating a platform branch. The direct renderer regression covers both parser
task sides, all four attribute quadrants, the name-table low-byte wrap,
`MetatileGraphics_Low/High` reads, Buffer2's vertical packet and `$0773=6`.
The attribute regression covers both resulting attribute states, all seven
source packets, their buffer offset and clearing behavior.

The original-ROM recorder separately enters `$88ae` for left and right
columns, and `$896a` for the corresponding attribute states. In each route
the scoped Buffer2, attribute-buffer, current-name-table and address-control
bytes are zero-difference against the native trace. This avoids inventing a
caller stack while preserving each original routine boundary. x86 and x64
pass `area-output`, `local-area`, `area-parser-column`, platform-purity and
Win32 self-tests. The shared source links to the OpenNT DOS16 MZ. Refreshed
artifacts are `mysmb16.exe` SHA-256
`0263AB1F1B0E6D54A6472411CF25F14D6BF158785AA1CC47F86F3874E289C78D`,
`mysmb32.exe` `7C88264EB32911E13BBE97A52F6E7241CB1914562095626774C4FB1C9D8B5DF5`,
and `mysmb64.exe` `C656377F5A05DD7302AC203A6CA569406ABD8689FDCF2122C629EF1BB7110E68`.

## S2 admission contract

S2 receives exactly `ColorRotatePalette`, `BlankPalette`, `Palette3Data`,
`ColorRotation`, `GetBlankPal`, `GetAreaPal` and `ExitColorRot` from the
legacy T18 receiver.  The baseline is 176 / 1,992; all seven are open and
expected to become ROM-match complete, for a maximum of 183 / 1,992.  The
shared owner is `src/game/area.c`; no platform source is in scope.

Its ROM-equivalence route enters the original color-rotation routines with
controlled frame-counter, palette-buffer capacity and palette-index state to
cover the timer gate, full-buffer no-op, blank-palette path, normal-area path
and rotation wrap.  The operational track adds a focused shared-game test,
then runs x86/x64 builds, the DOS16 link, platform-purity gate and refreshes
all three package executables.  T31 `GameEngine` remains the unadmitted
natural caller, so this S does not claim a fabricated caller stack.

## S2 closure: palette rotation equivalence

S2 closes at **183 / 1,992**. The shared `area.c` translation preserves the
original `$89e1-$8a38` order: low-three-bit frame gate, Buffer1 `$31` capacity
gate, eight-byte `BlankPalette` copy, four `Palette3Data` overwrites, rotating
color overwrite, offset advance and six-entry wrap. Controlled original-ROM
entries at `$89e1` cover normal area data, wrap, frame-gate and full-buffer
leaves. For each route, the owned frame-counter, Buffer1 offset/command bytes
and color-rotate offset are zero-difference against native C. The focused
palette test covers all area types and rotation values; x86/x64, DOS16 and
platform-purity were verified for this P.

## S3 admission contract

S3 receives exactly `BlockGfxData`, `RemoveCoin_Axe`, `WriteBlankMT`,
`ReplaceBlockMetatile`, `DestroyBlockMetatile`, `WriteBlockMetatile`,
`UseBOffset`, `MoveVOffset`, `PutBlockMetatile`, `SaveHAdder` and `RemBridge`.
The baseline is 183 / 1,992; all eleven are open and expected to become
ROM-match complete, for a maximum of 194 / 1,992. Shared owners are
`src/game/area/block_metatile.c` and its existing shared-game collaborators;
no platform source or producer logic is in scope.

## S3 closure: block-graphics command chain

S3 closes at **194 / 1,992**. `BlockGfxData` is read from the embedded local
PRG, while `RemoveCoin_Axe`, `DestroyBlockMetatile`, the replacement tail and
the bridge-collapse consumer use one shared `area/block_metatile.c` chain.
The C call sequence preserves `PutBlockMetatile -> RemBridge`, source table
selection, the two name-table rows, terminator, zero-page address cells and
the post-call ten-byte offset advance.

Controlled original-ROM entries for water coin removal, block replacement,
destroy and direct bridge output have zero differences over their owned
zero-page, Buffer1/Buffer2 and address-control bytes. The focused block,
collision and platform-purity tests pass on x86 and x64, both Win32 self-tests
pass, and the shared source links with OpenNT DOS16. The refreshed artifacts
are `mysmb16.exe` SHA-256 `7E70564A089473EC39851D4800A3D87DE4387E5AA2D2FE91B32F5E9932F2E7F6`,
`mysmb32.exe` `7B6EDA302897643B8103BDD0F1D0AFD59DDA9BCB3D7D28BAF036A6AF965A70B8`,
and `mysmb64.exe` `60FBC1EB1C268BBFF148113856E0FD44911AFADEE9E244F57118E57A2A5E819C`.

## S4 admission contract

S4 receives the nineteen adjacent data labels listed in the source-order table:
four metatile tables, eight palette streams and seven terminated message
streams. The baseline is 194 / 1,992 and all are open, for a maximum of
213 / 1,992. Existing shared `area.c` consumers are in scope for audit and
repair; no ROM-derived byte array may be added to tracked C. Controlled
original-ROM/native entries will compare table reads and the resulting
palette/name-table command output, while focused area regressions, x86/x64,
DOS16 and platform-purity checks provide the operational track.

## S4 closure: data-chain equivalence

S4 closes at **213 / 1,992**. No ROM-derived array was added to tracked C:
the shared `area.c` consumers retain source pointer reads for the four
metatile palettes and select each palette/text stream by the original VRAM
address-control values. `area-data-smoke` verifies every valid four-byte
metatile entry through the expanded name-table result, every byte of the four
area and four special palette streams through the palette snapshot, and every
terminated write in all seven message streams through the name tables. Its
expected output is independently reconstructed from the bound PRG command
stream; malformed pointers, terminators, addresses and command lengths fail.

This is static-data equivalence rather than an invented callable ROM entry:
the source labels are byte streams, and the evidence is their exact PRG range,
the original source consumers, and their complete observable output. The
focused data, area-output, palette-timing and victory-message tests pass on
x86 and x64 together with platform-purity and both Win32 self-tests. The same
shared core links into the OpenNT DOS16 MZ; the packaging pass refreshed the
three required artifacts, which remained byte-identical to S3 because no
production byte changed.

## S5 closure: name-table initialization chain

S5 closes at **218 / 1,992**. `JumpEngine`, `InitializeNameTables`,
`WriteNTAddr`, `InitNTLoop`, and `InitATLoop` are all represented by the
shared mode/screen selectors and `boot.c:mysmb_game_initialize_name_tables`.
The source `$8e19-$8e5b` order is preserved: control mirror `ORA #$10` then
`AND #$f0`, table-one then table-zero address selection, four `Y=$c0` loop
passes, the 64-byte attribute tail, both Buffer1 resets, and the zero-scroll
tail. The focused smoke makes the full two 960-byte `$24` regions, two
64-byte zero attribute regions, mirror control and buffer/scroll writes
observable.

The paired owner-ROM/native recorder enters the ordinary
`TitleScreenMode -> ScreenRoutines -> InitScreen` path at an NMI boundary and
captures the original at `NextSubtask` (`$85c8`), after both source calls
return. It does not inject a leaf PC. Both CIRAM pages and every PPU scalar
are zero-difference. The reference is before `IncSubtask`; the native frame
ends after that source successor, so its screen-task increment is separately
accounted for rather than hidden. Focused x86/x64 name-table, NMI-boundary,
snapshot, purity and Win32 self-tests pass; the same core is built for the
OpenNT DOS16 MZ. No platform source owns a name-table or PPU-state decision.
The S5 packaging pass produced `mysmb16.exe`
`7DFFE343566C3B7A4EB9F905B4816F810118EAB6146C9A98E76AF964CC3CE01F`,
`mysmb32.exe` `355A074CF5167BD47DE1A152F6C71DE6B2AFBBEEBDD1118EE5250DF2501A64F3`,
and `mysmb64.exe` `E47E64B3DC9D90F155C6C8DD4C6DC9DD147F00BE4BC2C536F1817B65C09F4A28`.

## S6 admission contract

S6 receives exactly these twelve adjacent labels from the legacy T18 receiver:
`ReadJoypads`, `ReadPortBits`, `PortLoop`, `Save8Bits`,
`WriteBufferToScreen`, `SetupWrites`, `GetLength`, `OutputToVRAM`,
`RepeatByte`, `UpdateScreen`, `InitScroll`, and `WritePPUReg1`. The baseline
is **218 / 1,992**; all twelve are open and expected to become ROM-match
complete, for a maximum of **230 / 1,992**.

The shared owners are `src/game/frame_root.c`, `src/game/game.c`, and their
shared C90 headers. The source route is `$8e5c-$8ef0`: strobe both controller
ports, shift exactly eight serial bits into `$06fc/$06fd`, apply the original
Start/Select mask at `$074a/$074b`, then process each selected VRAM packet,
including increment mode, repeat mode, terminator, palette-address reset,
zero-scroll tail, and `$0778` mirror write. T22's NMI is the natural caller;
the controlled evidence must enter through that route or an ordinary source
caller, never fabricate a leaf stack.

ROM equivalence compares each source branch, RAM/table read and write, and
call order. Operational evidence adds a focused shared-game smoke, paired
original-ROM/native route recordings, x86/x64 builds, the OpenNT DOS16 link,
platform-purity gate, and all three packaged artifacts. Platform adapters may
supply physical input and submit a completed frame only; they may not own
serial controller state, debounce, VRAM interpretation, PPU mirrors, or scroll.

## S6 P1 implementation checkpoint

P1 introduces the shared two-port serial latch and the shared PPU packet
writer. The focused `joypad-vram-chain-smoke` covers both `$06fc/$06fd`
ports, held Start/Select suppression, linear/repeat/32-byte increments,
nametable mirroring, palette mirroring, `$0778`, and the `InitScroll` tail.
It passes on x86 and x64 with frame-snapshot, platform-purity and each Win32
self-test. The identical core has a newly linked OpenNT DOS16 MZ.

This is an implementation checkpoint only: no S6 node receives completion
credit until the planned original-ROM/NMI comparison has established the
source call sequence and observed RAM/PPU state. The broader x64 regression
currently retains five pre-existing failures (`core`, `parser-buffer-commit`,
`bowser`, `mode`, `oper-mode-dispatch`); the focused S6 tests pass, and these
unrelated assertions are not silently repaired under this receipt.

## S6 P2 verification checkpoint

The focused shared smoke now drives the actual NMI Buffer1 selector through
both remaining packet forms: `$43` writes one byte three times with linear
increment, and `$83` writes three distinct bytes with vertical increment.
It checks their name-table locations and the original post-NMI Buffer1 header
and selector clears. The paired recorder also has an NMI-entry-only fixture
and a natural `UpdateScreen` successor capture point. That route confirms the
source call reaches the requested NMI boundary, but its current reference PPU
sample does not retain the injected tile payload; it is therefore diagnostic
only and does not credit S6 labels. Completion remains gated on a trace route
that makes those source writes observable.

## S6 P3 source-route correction

The recorder now brackets the ordinary source NMI packet at
`WriteBufferToScreen` (`$8e92`) and its `InitScroll` successor (`$8ee6`). It
prepares Buffer1 only after the normal NMI prefix has started, pauses at the
actual packet entry, then resumes the ROM until the packet has completed. This
corrects the earlier outer-NMI capture, which could sample before the packet
or after unrelated title work. The matching native recorder invokes the shared
NMI prefix only at its configured frame boundary.

## S6 closure: joypad/VRAM/NMI chain

S6 closes at **230 / 1,992**. All twelve admitted labels are ROM-match
complete. `frame_root.c` owns two-port serial reading, the source Start/Select
mask and the selected-buffer NMI contract; `game.c` owns packet interpretation
and PPU-visible output. Neither Windows nor DOS contains controller serial
state, debounce, packet decoding, scroll or PPU-mirror decisions.

The ordinary ROM NMI Start-and-release route matches `$06fc/$06fd` and
`$074a/$074b` over three frames, with zero CIRAM and OAM differences. The
source packet route exercises both remaining forms: `$43` repeats `$29` at
nametable offsets 0--2 and `$83` writes `$11/$22/$33` at offsets 0, 32 and 64.
For both routes, CIRAM and palette are zero-difference against the shared C
trace. The reference sample stops at `InitScroll`; the native prefix continues
through `InitBuffer` and the NMI control restore, accounting for its two
cleared Buffer1 header bytes and bit-7 control difference without masking a
packet result. The shared smoke separately checks linear, repeated, vertical,
nametable-mirror, palette-mirror, scroll-reset and PPU-mirror semantics.

Focused `joypad-vram-chain`, `frame-snapshot`, platform-purity and Win32
self-tests pass on x86 and x64. The shared code links into the OpenNT DOS16
MZ. All twelve actual matches are recorded in the inventory and ledger; no
node is transferred.

## S7 admission contract

S7 receives these nineteen adjacent labels from the legacy T18 receiver:
`StatusBarData`, `StatusBarOffset`, `PrintStatusBarNumbers`, `OutputNumbers`,
`SetupNums`, `DigitPLoop`, `ExitOutputN`, `DigitsMathRoutine`, `AddModLoop`,
`StoreNewD`, `EraseDMods`, `EraseMLoop`, `BorrowOne`, `CarryOne`,
`UpdateTopScore`, `TopScoreCheck`, `GetScoreDiff`, `CopyScore`, and `NoTopSc`.
The baseline is **230 / 1,992**; all nineteen are open and expected to become
ROM-match complete, for a maximum of **249 / 1,992**.

The shared owner is `src/game/status.c` and its shared C90 header surface.
The source chain is `$8ef4-$8fbf`: select the status destination, write
source-aligned digit fields with zero suppression, adjust score digits through
the add/erase loops, then apply the source top-score comparison and copy path.
T27/T35/T36 remain natural callers. ROM evidence will use controlled,
source-reachable status-number routes that cover score/time/coin destinations,
carry, borrow, zero suppression, unchanged top score and copied top score;
it will not construct an artificial caller stack.

ROM-equivalence evidence must compare control branches, score/time RAM reads
and writes, status-buffer bytes, digit arithmetic and source call order.
Operational evidence will run one focused shared status-arithmetic smoke,
x86/x64 builds, the OpenNT DOS16 link, platform-purity gate and all three
packaged executable artifacts. Windows and DOS may only submit the frame; no
platform source may calculate digits, score, timer, status text or top-score
state.

## S7 P1 shared-owner checkpoint

`src/game/status.c` now owns the portable status-output primitives and is the
only new implementation point for the admitted chain. Existing `area.c`
entry points remain thin shared-game caller adapters while source-call-site
migration is audited; no platform file changed. This checkpoint deliberately
records **no node completion credit**: the arithmetic and top-score callers
remain on their prior local implementations until each source branch is
compared against an original-ROM route.

The x86 and x64 focused status, top-score, platform-purity and Win32 self
tests pass. The same source links into the OpenNT DOS16 target. Packaging
refreshes all three required executable artifacts for this implementation P.

## S7 P2 caller convergence checkpoint

All admitted digit-arithmetic and top-score callers now enter the shared
status owner: object scoring, endgame scoring and the NMI top-score call
retain their original caller timing while delegating their former duplicate
math bodies. `status-arithmetic-smoke` exercises a six-digit carry, a full
borrow propagation, modifier clearing, Mario coin/score output and timer
output. Its first draft caught and corrected the source offset for Mario's
coin digits (`StatusBarOffset[3] - 2 = 22`).

This remains a checkpoint, not completion credit. The focused tests establish
the C-visible state; original-ROM route comparison is still required for all
nineteen labels before the inventory can change.
