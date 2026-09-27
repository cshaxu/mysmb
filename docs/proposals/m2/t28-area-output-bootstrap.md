# M2 T28: Area output primitives and bootstrap

## Status

T28 is the source-order receiver for ROM lines 1825--2794. It begins after
T27's screen task and precedes T29's area-object parser. All behavior stays in
shared game code; host adapters only submit the resulting frame and input.

**T28 S1 is active.**  It owns only the first thirteen-label renderer and
attribute-packet chain below; the later chains are queued, not implied by this
admission.

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
