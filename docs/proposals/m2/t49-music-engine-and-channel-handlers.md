# M2 T49: music engine and channel handlers

## Task contract

T49 owns the next **101 open source-order labels** from `JumpToDecLength2`
(line 15501) through `DeathMusHdr` (line 16048), ending before the subsequent
music-data region. It begins at **1,823 / 1,992** and can reach
**1,924 / 1,992**. Shared owner is `src/game/audio.c`; platforms only consume
its neutral audio state. Every node must receive separate original-ROM
control/read/write equivalence and x86/x64/DOS16 operational evidence before
credit. Owner ROM and reviewed assembly remain local research inputs; traces,
recorders and generated data stay under ignored `build/`.

| S | Exact source-order labels | Count | Chain boundary and owner |
| --- | --- | ---: | --- |
| S1 | `JumpToDecLength2`, `PlayBowserFall`, `BlstSJp`, `ContinueBowserFall`, `PBFRegs`, `EL_LRegs`, `PlayExtraLife`, `ContinueExtraLife`, `DivLLoop`, `PlayGrowPowerUp`, `PlayGrowVine`, `GrowItemRegs`, `ContinueGrowItems`, `StopGrowItems` | 14 | Remaining square-two fall, 1-up and grow-item phases; `audio.c` |
| S2 | `BrickShatterFreqData`, `PlayBrickShatter`, `ContinueBrickShatter`, `PlayNoiseSfx`, `DecrementSfx3Length`, `ExSfx3`, `NoiseSfxHandler`, `CheckNoiseBuffer`, `ExNH`, `PlayBowserFlame`, `ContinueBowserFlame`, `ContinueMusic` | 12 | Noise effects and handoff into music; `audio.c` |
| S3 | `MusicHandler`, `LoadEventMusic`, `NoStopSfx`, `LoadAreaMusic`, `NoStop1`, `GMLoopB`, `HandleAreaMusicLoopB`, `FindAreaMusicHeader`, `FindEventMusicHeader`, `LoadHeader` | 10 | Event/area selection and header loading; `audio.c` |
| S4 | `HandleSquare2Music`, `EndOfMusicData`, `NotTRO`, `MusicLoopBack`, `VictoryMLoopBack`, `Squ2LengthHandler`, `Squ2NoteHandler`, `Rest`, `SkipFqL1`, `MiscSqu2MusicTasks`, `NoDecEnv1` | 11 | Square-two music stream and envelope tail; `audio.c` |
| S5 | `HandleSquare1Music`, `FetchSqu1MusicData`, `Squ1NoteHandler`, `SkipCtrlL`, `MiscSqu1MusicTasks`, `NoDecEnv2`, `DeathMAltReg`, `DoAltLoad` | 8 | Square-one stream and alternate control; `audio.c` |
| S6 | `HandleTriangleMusic`, `TriNoteHandler`, `NotDOrD4`, `MediN`, `LongN`, `LoadTriCtrlReg` | 6 | Triangle stream and control register selection; `audio.c` |
| S7 | `HandleNoiseMusic`, `FetchNoiseBeatData`, `NoiseBeatHandler`, `StrongBeat`, `LongBeat`, `SilentBeat`, `PlayBeat`, `ExitMusicHandler` | 8 | Noise beat stream; `audio.c` |
| S8 | `AlternateLengthHandler`, `ProcessLengthData`, `LoadControlRegs`, `NotECstlM`, `WaterMus`, `AllMus`, `LoadEnvelopeData`, `LoadUsualEnvData`, `LoadWaterEventMusEnvData` | 9 | Shared music byte, length, control and envelope helpers; `audio.c` |
| S9 | `MusicHeaderData`, `TimeRunningOutHdr`, `Star_CloudHdr`, `EndOfLevelMusHdr`, `ResidualHeaderData`, `UndergroundMusHdr`, `SilenceHdr`, `CastleMusHdr`, `VictoryMusHdr`, `GameOverMusHdr`, `WaterMusHdr`, `WinCastleMusHdr`, `GroundLevelPart1Hdr`, `GroundLevelPart2AHdr`, `GroundLevelPart2BHdr`, `GroundLevelPart2CHdr`, `GroundLevelPart3AHdr`, `GroundLevelPart3BHdr`, `GroundLevelLeadInHdr`, `GroundLevelPart4AHdr`, `GroundLevelPart4BHdr`, `GroundLevelPart4CHdr`, `DeathMusHdr` | 23 | Header table/data consumed by S3-S8; `audio.c` |
| **Total** | **15501–16048** | **101** | |

The S boundaries preserve source order and group only one shared control/data
path. A later S dependency may be invoked for operational continuity but earns
no early credit. S1 alone is admitted below; S2-S9 remain planned ownership
until separately admitted.

## S1 admission: remaining square-two effects

S1 receives exactly 14 open labels from `JumpToDecLength2` through
`StopGrowItems`. Baseline is **1,823 / 1,992**; all 14 are intended matches,
for a maximum **1,837 / 1,992**. Its predecessor is T48 S6
`Cont_CGrab_TTick`; its successor is S2 `BrickShatterFreqData`. The source
route starts at an unchanged NMI `SoundEngine` call with bounded natural
square-two queue/buffer states for Bowser fall, extra life, power-up reveal
and vine growth. It compares source PC order, shifts, state counters, RAM
buffers and APU writes against the common C owner.

The ROM-logic track covers the jump-to-decrement trampoline, the negative
Bowser-fall queue route, active and newly selected 1-up phases, both grow
selectors and terminal grow clearing. It must preserve all source table
access and call order; no platform may select effects. The operational track
uses focused audio/dispatcher tests, new source-route checks as needed,
x86/x64 builds and self-tests, the existing OpenNT DOS16 target, platform
purity and refreshed three executable artifacts. Closure individually names
all fourteen node dispositions and records any successor transfer.

### S1 closure: remaining square-two effects

All **14** admitted labels are ROM-match complete: **1,823 -> 1,837 / 1,992**.
The shared `audio.c` owner now follows the source chain directly: the decrement
trampoline, Bowser-fall initial/length-eight register phases, extra-life's
three-shift gate, and both grow-item selectors with their independent secondary
counter and empty-buffer exit.

| Source PC | Label | Source behavior and shared-C mapping |
| --- | --- | --- |
| `$f5c5` | `JumpToDecLength2` | Unconditional entry reaches `DecrementSfx2Length`; `mysmb_audio_square2_jump_to_decrement` preserves that tail. |
| `$f5c8` | `PlayBowserFall` | Initializes `$07bd` to `$38`, loads A/Y `$18/$c4`, then takes the shared register/decrement tail. |
| `$f5cd` | `BlstSJp` | Unconditional nonzero branch supplies the shared Bowser/blast register path. |
| `$f5cf` | `ContinueBowserFall` | Only remaining length `$08` loads `$5a/$a4`; every other length takes the decrement trampoline. |
| `$f5d5` | `PBFRegs` | Loads X `$9f` before the shared square-two register helper. |
| `$f5d6` | `EL_LRegs` | Nonzero branch enters `LoadSqu2Regs`, whose decrement fallthrough remains shared. |
| `$f5d8` | `PlayExtraLife` | Initializes `$07bd` to `$30` and falls into its continuation. |
| `$f5dc` | `ContinueExtraLife` | Checks the current length before source's three logical shifts and shared register/decrement tail. |
| `$f5df` | `DivLLoop` | Any of the three shifted low bits takes the decrement trampoline; exact multiples of eight index `ExtraLifeFreqData-1,Y`. |
| `$f5e9` | `PlayGrowPowerUp` | Supplies grow length `$10` to `GrowItemRegs`. |
| `$f5ed` | `PlayGrowVine` | Supplies grow length `$20` to the same register setup. |
| `$f5f0` | `GrowItemRegs` | Writes length, direct `$4005=$7f`, clears `$07be`, then falls into the first grow phase. |
| `$f5f7` | `ContinueGrowItems` | Increments `$07be`, compares its half value with `$07bd`, otherwise writes `$4004=$9d` and calls `SetFreq_Squ2` with `PUp_VGrow_FreqData,Y`. |
| `$f604` | `StopGrowItems` | Equality takes `EmptySfx2Buffer`, preserving the `$4015=$0d,$0f` stop sequence. |

The unchanged owner ROM was sampled through `SoundEngine` in eight bounded
states: new and continuing Bowser fall, new and active extra-life, power-up
reveal, vine growth, and both grow-item terminal states. Each state supplied
eight NMI calls. The x86 and x64 C checkers compare `$f2`, `$fe`, `$07bd`,
`$07be`, and square-two/master APU output after each call: **128 comparisons,
zero differences**. The recorder and raw records remain under ignored
`build/m2-t49-s1/`.

Focused audio, dispatcher and platform-purity CTests pass on x86 and x64;
both Win32 `--self-test` routes pass. Full CTest stays **223/234** on each
width with the same eleven registered baseline failures and no new failure.
The original OpenNT16 target compiles the same shared core and links a valid
262,421-byte MZ executable. The three refreshed owner-authorized artifacts are:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `43ea2f97a0c910ac2a8d362e7c76cdf365176b706b588a0eadaed26db9e52e85` |
| `assets/mysmb32.exe` | `3e5dd6f32b56fad985b97ed8da1971a93d17c62abe329a2be04e20935772b42e` |
| `assets/mysmb64.exe` | `938a27e272738034cbff15e63f08eff69d40cc8dd755b2f57ef135b8d0c4c137` |

The similar-issue sweep searched all square-two queue/buffer routes. The only
production dispatch point is `src/game/audio.c`; no platform adapter selects
an effect, branches on game state, or mutates game RAM/APU state. S2's noise
and music labels remain out of scope and retain their existing custody.

## S2 admission: noise effects and music handoff

S2 receives the next **12** source-order labels from `BrickShatterFreqData`
through `ContinueMusic`. Baseline is **1,837 / 1,992**; all 12 are intended
matches, for a maximum **1,849 / 1,992**. This bounded `audio.c` chain
contains the brick table/phase, the square-two-independent noise queue and
buffer dispatcher, Bowser flame phase, and the final tail into the S3
square-two music entry. Its predecessors are the S1 square-two chain and
the already-complete shared APU writers; S3's music handler is its successor.

ROM-logic evidence will enter unchanged `SoundEngine` through NMI on brick,
Bowser flame, buffered phase, end-of-length, and no-noise states. It compares
the original branch selection, `$fd/$f3/$7f` reads and writes, owner-ROM
table bytes, APU noise registers, and the `ContinueMusic` handoff. Operational
evidence is one chain-level focused test set plus x86/x64 builds and self-tests,
the original OpenNT DOS16 link, platform-purity audit, and all three artifacts.
No music stream node is credited by this admission.
