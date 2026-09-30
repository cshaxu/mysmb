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

## S2 closure: noise effects and music handoff

All **12** admitted labels are ROM-match complete: **1,837 -> 1,849 / 1,992**.
`src/game/audio.c` now preserves the original noise queue and buffer shifts, brick
phase tables, direct noise-register write order, terminal mute path, Bowser-flame
phase, and the `ContinueMusic` tail into square-two music handling.

| Source PC | Labels | Shared-C mapping |
| --- | --- | --- |
| `$f62b` | `BrickShatterFreqData` | owner-local ROM table readers |
| `$f63b-$f666` | `PlayBrickShatter`, `ContinueBrickShatter`, `PlayNoiseSfx`, `DecrementSfx3Length`, `ExSfx3` | brick phase, APU writes and terminal path |
| `$f667-$f67f` | `NoiseSfxHandler`, `CheckNoiseBuffer`, `ExNH` | queue/buffer dispatcher and exits |
| `$f680-$f68f` | `PlayBowserFlame`, `ContinueBowserFlame` | flame phase and shared noise tail |
| `$f691` | `ContinueMusic` | explicit square-two handoff |

The owner-ROM `SoundEngine` route covered six noise states and one controlled
`ContinueMusic` state, eight calls each. x86 and x64 comparison checkers found
**zero differences across 112 RAM/APU comparisons**. Focused audio, dispatcher
and platform-purity checks pass on both widths. Full CTest is **224/235** on each
width with the same eleven pre-existing failures and no new failure. The original
OpenNT16 target compiled the same shared core and linked a valid **263,173-byte**
MZ executable. No platform adapter chooses an effect, branches on game state, or
mutates translated game state.

The three owner-authorized artifacts were refreshed at closure; their SHA-256
values are recorded in the active packet closure update.

## S3 admission: music selection and header loading

S3 receives the next **10** source-order labels from `MusicHandler` through `LoadHeader`: `MusicHandler`, `LoadEventMusic`, `NoStopSfx`, `LoadAreaMusic`, `NoStop1`, `GMLoopB`, `HandleAreaMusicLoopB`, `FindAreaMusicHeader`, `FindEventMusicHeader`, and `LoadHeader`. Baseline is **1,849 / 1,992**; all ten are expected matches, for a maximum **1,859 / 1,992**. Shared owner is `src/game/audio.c`; predecessor is S2 `ContinueMusic`, successor is S4 `HandleSquare2Music`.

The ROM-logic track uses bounded original-ROM `SoundEngine` invocations for event and area music selection. It compares queue-bit priority, `NoStopSfx` and `NoStop1` exits, loop-B resolution, header-table pointer selection, RAM music offsets/counters and direct APU reset writes. The operational track runs focused dispatch tests plus x86/x64 builds and self-tests, OpenNT DOS16 link, platform-purity check and refreshed three target EXEs. No stream-parsing label from S4 or later is credited.

## S3 closure: music selection and header loading

All **10** admitted labels are ROM-match complete: **1,849 -> 1,859 / 1,992**.
The one shared owner, `src/game/audio.c`, now follows the source queue-priority
prefix through the `HandleSquare2Music` entry boundary. No Win32 or DOS16
adapter selects music, changes a queue, or writes music RAM/APU state.

| Source PC | Labels | Shared-C equivalence |
| --- | --- | --- |
| `$f694-$f6a3` | `MusicHandler` | `mysmb_audio_select_music` preserves event-first selection and the no-queue continuation boundary. |
| `$f6a4-$f6c7` | `LoadEventMusic`, `NoStopSfx` | Event buffer, DeathMusic square-effect stop sequence, interrupted-area preservation, time-running length adder and source bit scan are in source order. |
| `$f6c8-$f6d3` | `LoadAreaMusic`, `NoStop1`, `GMLoopB` | Underground-only square-one stop and `$10` ground selector seeding are preserved. |
| `$f6d4-$f6ec` | `HandleAreaMusicLoopB`, `FindAreaMusicHeader` | Area buffer/event clear, ground `$11..$31` loop progression and the residual square-two offset write precede header selection. |
| `$f6f1-$f6f4` | `FindEventMusicHeader` | The source `INY; LSR; BCC` carry order supplies the header selector. |
| `$f6f5-$f733` | `LoadHeader` | Owner-ROM offset table/header bytes initialize all music offsets/counters and perform `$4015=$0b,$0f`. |

ROM logic evidence used five controlled, source-reachable `SoundEngine` routes:
DeathMusic, TimeRunningOutMusic, GroundMusic, UndergroundMusic and WaterMusic.
Each route supplied eight original calls, for **40 entry states per width**.
The x86 and x64 checkers compare queue-derived selector/header fields, music
RAM outputs and master-control output at the S3/S4 boundary: **zero
differences in all 80 comparisons**. Raw records remain under ignored
`build/m2-t49-s3/`; the checker derives its expected header bytes directly
from the owner-local ROM table and does not copy those bytes into the product.

Operational evidence: focused `music-header-smoke`, `audio-smoke` and
`platform-purity` pass; full x86 and x64 CTest each remain **224/235**, with
only the same eleven registered baseline failures. The original OpenNT16
`cl16` route compiles the shared source and links a **263,957-byte MZ** image
(with its established `OLDNAMES.LIB` warning). Packaged owner-authorized
artifacts are `mysmb16.exe` `F21B3C6398C2DA655382281B601797EEF91E0FE4C9C7FCC14D76B54E567D609E`,
`mysmb32.exe` `260DBA9CF997551D60FEFEB6FCB030ECB435E50E6A3CAC2C9753A2BDBB83E782`,
and `mysmb64.exe` `A3FAEBD5F716BEB0D1818372116DBFC7AD1E22DDCE9B3C4D1D4BA9E15CC50896`.

Similar-issue sweep: all music queue/buffer, selector, header-reset and
loop-B production paths are in `audio.c`; no platform-layer hit exists. S4
stream parsing and later header/data ownership remain uncredited.


## S4 admission: square-two music stream and envelope tail

S4 receives the next **11** source-order labels from `HandleSquare2Music`
through `NoDecEnv1`: `HandleSquare2Music`, `EndOfMusicData`, `NotTRO`,
`MusicLoopBack`, `VictoryMLoopBack`, `Squ2LengthHandler`, `Squ2NoteHandler`,
`Rest`, `SkipFqL1`, `MiscSqu2MusicTasks`, and `NoDecEnv1`. Baseline is
**1,859 / 1,992**; all eleven are intended matches, for a maximum
**1,870 / 1,992**. The shared owner is `src/game/audio.c`; predecessor is
S3 `LoadHeader`, and successor is S5 `HandleSquare1Music`.

The ROM-logic track enters original `SoundEngine` only after a source-selected
non-death header. It exercises bounded square-two length, note, rest, normal
loop, victory loop and envelope-tail states, then compares control sequence,
stream bytes, `$f0/$f4/$f5/$f8`, counters and square-two APU writes at the
S4/S5 boundary. The operational track adds one chain-level stream test as
needed, runs focused audio/purity checks, x86/x64 builds and self-tests, the
existing OpenNT DOS16 link, and refreshes all three owner-authorized EXEs.
No square-one, triangle, noise, shared length/control, or music-data label is
credited by this admission.


## S4 closure: square-two music stream and envelope tail

All **11** admitted labels are ROM-match complete: **1,859 -> 1,870 / 1,992**.
`src/game/audio.c` now preserves the original `HandleSquare2Music` route as one
contiguous shared-C chain: decrement/fetch, length-byte lookup, note/rest dispatch,
source terminator exits, same-invocation header fallthrough after loop-back, and the
pre-decrement-Y envelope-table access. No platform adapter selects music, mutates
music RAM, or emits APU policy.

| Source PC | Labels | Source-equivalent shared-C behavior |
| --- | --- | --- |
| `$f738-$f74a` | `HandleSquare2Music` | Counter decrement, indirect `MusicData,Y` read, stream-offset increment and fallthrough after `LoadHeader`. |
| `$f74b-$f779` | `EndOfMusicData`, `NotTRO`, `MusicLoopBack`, `VictoryMLoopBack` | Terminal mute/clear, time-running interrupted-area restore, normal-area loop and victory event reload retain source order. |
| `$f77a-$f797` | `Squ2LengthHandler`, `Squ2NoteHandler`, `Rest` | `ProcessLengthData` result, second byte fetch, frequency/no-tone branch, envelope save and register writes. |
| `$f798-$f7b4` | `SkipFqL1`, `MiscSqu2MusicTasks`, `NoDecEnv1` | Active SFX skips frequency/envelope work; otherwise preserved pre-decrement envelope index drives `$4004/$4005`. |

ROM-logic evidence uses six bounded original-ROM `SoundEngine` routes, eight calls
each: normal stream, terminal death, time-running restore, victory reload, normal
area loop, Square2-SFX ownership, and a real stream rest. The x86 and x64 checkers
compare the scoped stream pointer/offset, buffer/counters/envelope and Square2 APU
outputs: **all 48 samples per width have zero differences**. Raw records and recorder
outputs remain below ignored `build/m2-t49-s4/`.

Operational evidence: the focused audio/header checks and platform-purity scan pass
on both Windows widths; x86 and x64 Win32 products build; the unchanged OpenNT16
toolchain compiles the same `audio.c` and links a valid 263,877-byte MZ image
(with the established `OLDNAMES.LIB` warning). Refreshed owner-authorized artifacts:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `53DC415A1C638C3E910B5822CA0B6D37F721769BFEB1C456FC4957FEBF864078` |
| `assets/mysmb32.exe` | `B9C7608E77AD6E9028CFE2B1D726D683BF2ABE91489A6FB12FD6AD36213BAD4D` |
| `assets/mysmb64.exe` | `A16607FCB942070003C11F4B38C0AEF5799E5DE29501A68ABDD33566B0DE6003` |

Similar-issue sweep: every production music-stream fetch, offset, terminator, loop,
rest, Square2-SFX gate and envelope path is in `src/game/audio.c`; no Win32 or
DOS16 platform source contains game/audio branching or translated-state mutation.
S5+ channel/data helpers retain their separate ledger custody and receive no credit.


## S5 admission: square-one music stream and alternate control

S5 receives **8** source-order labels: `HandleSquare1Music`, `FetchSqu1MusicData`,
`Squ1NoteHandler`, `SkipCtrlL`, `MiscSqu1MusicTasks`, `NoDecEnv2`, `DeathMAltReg`,
and `DoAltLoad`. Baseline is **1,870 / 1,992**; all eight are expected matches,
for a maximum **1,878 / 1,992**. Shared owner remains `src/game/audio.c`;
predecessor is S4 `NoDecEnv1`, successor is S6 `HandleTriangleMusic`.

The ROM-logic track will compare Square1's distinct duration-bit encoding, null-data
loop, SFX suppression, death alternate-control sequence and envelope tail against
bounded original `SoundEngine` records. The operational track runs focused audio and
purity checks, x86/x64 builds, the existing OpenNT DOS16 link, and refreshes all
three owner-authorized EXEs. No S6+ channel/helper/data label is credited.

## S5 closure: square-one music stream and alternate control

All **8** admitted labels are ROM-match complete: **1,870 -> 1,878 / 1,992**.
`src/game/audio.c` now follows the original Square1 path from its independent
offset gate through the Square1-only duration encoding, null-data control loop,
rest bypass, SFX ownership exit, envelope decay and death alternate register.
The implementation reads the owner-local music and lookup data through the
shared CPU-address reader; no platform adapter selects music or writes game
audio state.

| Source PC | Labels | Shared-C equivalence and original route |
| --- | --- | --- |
| `$f72c-$f735` | `HandleSquare1Music`, `FetchSqu1MusicData` | Offset zero bypasses Square1, counter decrement gates fetch, and null bytes write `$4000=$83`, `$4001=$94`, retain `$07ca=$94`, then fetch again. |
| `$f746-$f759` | `Squ1NoteHandler`, `SkipCtrlL` | Original bit 0/7/6 duration selector feeds the shared owner-ROM length table. The controlled GroundM_P1 rest takes the `SetFreq_Squ1` zero path; the following control dump retains zero X and the masked-note Y. |
| `$f75c-$f76d` | `MiscSqu1MusicTasks`, `NoDecEnv2` | A live Square1 SFX reaches the immediate Triangle handoff; otherwise the pre-decrement envelope index selects the same owner-ROM envelope byte. |
| `$f770-$f773` | `DeathMAltReg`, `DoAltLoad` | Death music bypasses envelope replacement and writes `$07ca`, or the source default `$7f`, to `$4001`. |

The unchanged owner-ROM `SoundEngine` route recorded four bounded states, each
with eight calls: a GroundM_P1 rest/control bypass, a real null-data loop
followed by an audible note, a live Square1 SFX ownership exit, and a death
alternate-control tail. The dedicated Square1 music checker compares `$f1`,
`$f8`, `$7b6`, `$7b7`, `$7ca`, and `$4000-$4003` after every call. Both x86 and
x64 report **32 comparisons with zero differences**.

Focused audio/header smoke checks pass on both Windows widths, platform purity
passes, and the existing OpenNT16 route compiles the same shared C sources and
links its MZ executable. The refreshed owner-authorized artifacts are:

| Artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `09A9500657C9BF812AD899D1AE1563BABC0C9539DD248807265B606DFC93E8E4` |
| `assets/mysmb32.exe` | `4037D2955D055B735F983703F397F0A0A15A98641733A5C5DEEC3D31477F889B` |
| `assets/mysmb64.exe` | `F506FF5B5403BFC7EFF96C1DC13E4931CDFA6116C21578D9C9A82DED7B4745B8` |

Similar-issue sweep: every production Square1 music fetch, duration selection,
null loop, rest, SFX gate, envelope tail and alternate-control write is in
`src/game/audio.c`. `src/platform/` contains no audio/gameplay control flow.
The triangle, noise and shared helper chains retain their separate source-order
custody and receive no S5 credit.

## S6 admission: triangle music stream and control register

S6 receives **6** source-order labels: `HandleTriangleMusic`, `TriNoteHandler`,
`NotDOrD4`, `MediN`, `LongN`, and `LoadTriCtrlReg`. Baseline is **1,878 / 1,992**;
all six are expected matches, for a maximum **1,884 / 1,992**. Shared owner is
`src/game/audio.c`; predecessor is S5 `DoAltLoad`, successor is S7
`HandleNoiseMusic`.

The ROM-logic track will compare the unconditional triangle counter decrement,
the zero-byte control branch, length-byte plus note pair, frequency output, and
the event/area/length selector of `$4008` using bounded original `SoundEngine`
records. The operational track will run focused audio tests, x86/x64 builds,
the existing OpenNT DOS16 link, platform-purity audit and refreshed three EXEs.
No S7+ node receives credit.

## S6 closure: triangle music stream and control register

All **6** admitted labels are ROM-match complete: **1,878 -> 1,884 / 1,992**.
The shared `audio.c` owner now follows the source triangle path: unconditional
counter decrement, CPU-address stream fetch, zero-byte `$4008` control write,
length-plus-note pair, frequency dump and exact event/area/length control
selection. No platform code contains audio logic.

Four unchanged original-ROM SoundEngine record groups cover zero-byte control,
length-plus-note, area control and Win-Castle control. Each group has eight
calls; x86 and x64 each compare 32 triangle RAM/APU results with zero
differences. Platform purity passes, both Win32 products build, and OpenNT16
links the same shared C MZ image. Refreshed artifacts: mysmb16
`D0DE7161D69E60238FFFA004CE2A49E3485ABBEAC60FE84F71C9006C97E3AF4F`,
mysmb32 `6461D0772FCBAF99A16FB014F525D731C1D103D6B8FC2F447FE0F80AB934A28C`,
and mysmb64 `22368DD5475B9CA2D6108DD5B40ECDF88027D83780C92E69A3B6C6377FCC65C2`.


## S7 admission: noise beat stream and exit

S7 receives **8** source-order labels: `HandleNoiseMusic`, `FetchNoiseBeatData`,
`NoiseBeatHandler`, `StrongBeat`, `LongBeat`, `SilentBeat`, `PlayBeat`, and
`ExitMusicHandler`. The baseline is **1,884 / 1,992**; all eight are expected
matches, for a maximum **1,892 / 1,992**. The contiguous chain is owned by
`src/game/audio.c`; its predecessor is S6 `LoadTriCtrlReg` and its successor is
S8 `AlternateLengthHandler`.

The ROM-logic track will exercise unchanged `SoundEngine` routes for the
underground/castle bypass, nonzero beat-counter exit, zero-byte noise loopback,
and each short/strong/long/silent beat class. It compares the area gate, counter
and offset mutations, source loop, duration conversion call boundary and
`$400c/$400e/$400f` writes. The operational track will add one chain-level
snapshot check, run x86/x64 builds, the existing OpenNT DOS16 link,
platform-purity audit and refresh the three owner-authorized executables. No S8
helper or later music-data node receives S7 credit.


## S7 closure: noise beat stream and exit

All **8** admitted labels are ROM-match complete: **1,884 -> 1,892 / 1,992**.
The shared owner follows the source area gate, beat-counter exit, zero-byte
loopback, `AlternateLengthHandler` boundary and source order for silent, short,
strong and long noise writes. No platform layer selects or writes music state.

Six unchanged original-ROM SoundEngine record groups cover the area bypass,
counter exit, zero-loopback silent beat and short/strong/long beat cases. Each
contains eight calls; x86 and x64 each compare 48 scoped RAM/APU results with
zero differences. Platform purity passes; both Win32 products build; OpenNT16
links the same shared C image. Refreshed artifacts: mysmb16
`181FBACF36E268BFA96881A39C95872897C41A2735B7C91CA4EB95D7142045DF`, mysmb32
`887DFBD4D34ED1F7301150AC68E04F3084B106666556A9C19635EF7E59297F65`, and mysmb64
`FC0949910C662162115BC24EFAA42963A2497FCBF1E1DE2C332086C86A8B7595`.


## S8 admission: shared length, control and envelope helpers

S8 receives **9** source-order labels: `AlternateLengthHandler`,
`ProcessLengthData`, `LoadControlRegs`, `NotECstlM`, `WaterMus`, `AllMus`,
`LoadEnvelopeData`, `LoadUsualEnvData`, and `LoadWaterEventMusEnvData`.
Baseline is **1,892 / 1,992**; all nine are expected matches, for a maximum
**1,901 / 1,992**. Shared owner is `src/game/audio.c`; predecessor is S7
`ExitMusicHandler`, successor is S9 `MusicHeaderData`. ROM proof compares
rotation-derived length indexes, table lookup index, control A/X/Y triples, and
all three envelope table selection paths. Operational proof uses x86/x64,
OpenNT DOS16, purity and refreshed artifacts.


## S8 closure: shared length, control and envelope helpers

All **9** labels are ROM-match complete: **1,892 -> 1,901 / 1,992**. Shared `audio.c` now preserves the source helper boundary. Square2 default, water and Win-Castle records plus Square1 and noise paths compare RAM/APU outputs at zero difference on x86/x64.
