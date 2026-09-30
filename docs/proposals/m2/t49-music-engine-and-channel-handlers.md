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
