# M2 T48: sound-effect queue and channel handlers

## Task contract

The owner-approved source-order plan assigns T48 the **74 open labels**
from `SoundEngine` (line 15070) through `Cont_CGrab_TTick` (line 15498).
They are currently received by M2 Td S4. Incoming conformance is
**1,749 / 1,992**; the maximum is **1,823 / 1,992**. The next label,
`JumpToDecLength2` at 15501, belongs to the next source slice and
receives no T48 credit. `src/game/audio.c` is an existing provisional
translation, not a conformance certificate.

| S | Exact source-order labels | Count | Chain and shared owner |
| --- | --- | ---: | --- |
| S1 | `SoundEngine`, `SndOn`, `InPause`, `PTone1F`, `ContPau`, `PTone2F`, `PTRegC`, `DecPauC`, `SkipPIn`, `RunSoundSubroutines`, `SkipSoundSubroutines`, `NoIncDAC`, `StrWave` | 13 | NMI sound entry, pause control, queue clearing and DAC tail; `audio.c` |
| S2 | `Dump_Squ1_Regs`, `PlaySqu1Sfx`, `SetFreq_Squ1`, `Dump_Freq_Regs`, `NoTone`, `Dump_Sq2_Regs`, `PlaySqu2Sfx`, `SetFreq_Squ2`, `SetFreq_Tri` | 9 | Shared APU register writers and frequency helpers; `audio.c` |
| S3 | `SwimStompEnvelopeData`, `PlayFlagpoleSlide`, `PlaySmallJump`, `PlayBigJump`, `JumpRegContents`, `ContinueSndJump`, `N2Prt`, `FPS2nd`, `DmpJpFPS`, `PlayFireballThrow`, `PlayBump`, `Fthrow`, `ContinueBumpThrow`, `DecJpFPS` | 14 | Square-one effect phases; `audio.c` |
| S4 | `Square1SfxHandler`, `CheckSfx1Buffer`, `ExS1H`, `PlaySwimStomp`, `ContinueSwimStomp`, `BranchToDecLength1`, `PlaySmackEnemy`, `ContinueSmackEnemy`, `SmSpc`, `SmTick`, `DecrementSfx1Length`, `StopSquare1Sfx`, `ExSfx1`, `PlayPipeDownInj`, `ContinuePipeDownInj`, `NoPDwnL` | 16 | Square-one queue selection and effect lifetime; `audio.c` |
| S5 | `ExtraLifeFreqData`, `PowerUpGrabFreqData`, `PUp_VGrow_FreqData`, `PlayCoinGrab`, `PlayTimerTick`, `CGrab_TTickRegL`, `ContinueCGrabTTick`, `N2Tone`, `PlayBlast`, `ContinueBlast`, `SBlasJ`, `PlayPowerUpGrab`, `ContinuePowerUpGrab`, `LoadSqu2Regs`, `DecrementSfx2Length`, `EmptySfx2Buffer`, `StopSquare2Sfx`, `ExSfx2` | 18 | Square-two effect data, writers and lifetime; `audio.c` |
| S6 | `Square2SfxHandler`, `CheckSfx2Buffer`, `ExS2H`, `Cont_CGrab_TTick` | 4 | Square-two queue dispatcher; `audio.c` |
| **Total** | **15070–15498** | **74** | |

The S boundaries follow original source order. A called routine in a
later S is a named dependency, not an early conformance claim. Each S
performs its own node-level control, table, RAM and APU-write review
against a source-reachable or bounded original-ROM route, then an
independent x86/x64/DOS16 operational pass. T closure combines these
chains and checks sound effects alongside T49's later music dependency.

The owner-supplied `smb1.nes` and reviewed `SMBDIS.ASM` are local,
nonredistributable research inputs. Raw traces and generated records
stay under ignored `build/` during diagnosis and are deleted after use.
Only neutral evidence is tracked. The three EXEs are refreshed per P
under the owner's standing artifact instruction; platform code only
consumes shared game audio output.

## S1 admission: SoundEngine pause and queue/DAC control

Entry is original `$f2d0` `SoundEngine`, exit is `StrWave`'s RTS before
`Dump_Squ1_Regs`. S1 owns exactly the first **13 open labels** listed
above, expects 13 ROM matches, and can reach at most **1,762 / 1,992**.
Predecessor is T47 `SetHFAt` in source order; `Dump_Squ1_Regs` is the
next source label. `RunSoundSubroutines` calls later square/noise/music
handlers; S1 proves its call order and queue effects without assigning
those called nodes premature credit. The common C owner is
`src/game/audio.c`, with neutral APU output fields in `game.h`.

The ROM-logic track captures source-reachable SoundEngine calls from
NMI on title, active gameplay, pause-start, pause-hold and pause-end
routes. Bounded changes to sound queue/RAM at natural entry may test
the two tone values, counter thresholds, queue clearing, DAC up/down
and idle branches. Record original control PCs, RAM and APU writes and
compare the C entry's corresponding outputs; do not redirect the CPU
or invent a sound policy. The operational track runs the focused
`mysmb.audio-smoke` and platform-purity CTests, x86/x64 self-tests,
DOS16 link, and all three executable artifacts. Existing downstream
handler differences are recorded by exact receiving S, not waived.

### S1 closure: SoundEngine entry

**P1 disposition: 13/13 ROM-match complete; project total 1,762/1,992.**
The source-to-C comparison follows `SoundEngine` at `$f2d0` through
`StrWave` at `$f37d` in `src/game/audio.c`. The original entry is reached
through NMI, including natural title and gameplay calls. Bounded edits to
sound RAM at that same entry exercise pause start, the `$24/$1e/$18`
tone thresholds, both pause exit values, absent pause buffer, active
music queues, and DAC values `$00/$03/$2f/$30`. Neither ROM bytes nor
CPU PC/stack were changed.

| Source label / PC | Original control or output accounted for in shared C |
| --- | --- |
| `SoundEngine` `$f2d0`, `SndOn` `$f2d9` | Title mode writes zero to `$4015` and returns; game mode writes `$ff` to `$4017`, then `$0f` to `$4015`. |
| `InPause` `$f2ee`, `PTone1F` `$f312`, `ContPau` `$f316` | Pause queue starts buffer/mode, clears three effect buffers, re-enables channels, sets `$2a`, plays first tone, and decrements on the same call. |
| `PTone2F` `$f325`, `PTRegC` `$f327`, `DecPauC` `$f32e` | Exact `$24/$1e/$18` tone decisions, square-one APU writes through the still-uncredited `PlaySqu1Sfx` dependency, and decrement/zero handling. |
| `SkipPIn` `$f344`, `RunSoundSubroutines` `$f34b` | Buffer/mode exit and four handler calls; only the active handler route clears area/event music queues. |
| `SkipSoundSubroutines` `$f35d`, `NoIncDAC` `$f377`, `StrWave` `$f37d` | Four sound queues clear, pre-update DAC value is written to `$4011`, and the increment/decrement branch, including `$30` saturation, matches. |

All 13 source PCs were hit in 14 original routes and 42 original
`SoundEngine` calls. The x86 and x64 checkers compared each call,
**84 comparisons with zero S1-owned differences**. Title and pause
routes compared all non-stack 2 KiB RAM and all 24 APU registers.
Natural active-game and DAC-active routes compared S1-owned RAM and
APU `$4011/$4015/$4017`; downstream channel register and RAM differences
remain with T48 S2–S6 and T49. This scope is explicit: S1 does not claim
full sound-engine equivalence yet. The neutral PC-hit and comparison
summary was generated under ignored `build/m2-t48-s1/`.

The separate operational track rebuilt Win32 x86, x64 and DOS16. Both
Windows `--self-test` runs exited zero; DOS16 linked a valid MZ executable.
Full CTest was **222/233** on each Windows width, with exactly the same
11 pre-existing failures as T47. A new x64 test-only crash exposed an
uninitialized host-side ROM pointer in `rom_object_array_layout_smoke`;
the fixture now zero-initializes its container before invoking the
original RAM-only `InitializeMemory` routine. It passes on both widths
and the final full matrix has no new failures. `mysmb.audio-smoke` and
`mysmb.platform-purity` pass on both widths.

| Owner-requested artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `59d0721b338f3695adccf858a5be4b40a3f7fc7c16be2b01a4ff64a9398f6dd9` |
| `assets/mysmb32.exe` | `7663eee3193cc8eadfde53dec4a5d88e1e060df187a209f6e79365105fcccaa3` |
| `assets/mysmb64.exe` | `a2527c84b6da2c6cec48195445be6350cc7f93434da3285e81e835f89cde85b3` |

Similar-issue sweep: the SoundEngine decision path and APU register
mirror are only in shared `src/game/audio.c`; `boot.c` mirrors the two
source boot writes. `frame_root.c` invokes sound, while player, terrain
and metatile code only produce sound queues. No platform source contains
pause/DAC/APU decision logic. The remaining provisional square-one,
square-two, noise and music handlers retain their designated T48 S2–S6
and T49 receivers and must be compared independently before credit.

## S2 admission: APU register and frequency helpers

S1 closed at **1,762/1,992**. S2 accepts the next nine **open** labels
in exact source order: `Dump_Squ1_Regs`, `PlaySqu1Sfx`,
`SetFreq_Squ1`, `Dump_Freq_Regs`, `NoTone`, `Dump_Sq2_Regs`,
`PlaySqu2Sfx`, `SetFreq_Squ2`, `SetFreq_Tri`. The intended matched
subset is all nine, making the maximum **1,771/1,992**. Entry is
`Dump_Squ1_Regs` after S1's `StrWave`; exit is `SetFreq_Tri` before
S3's `SwimStompEnvelopeData`. All nine share `src/game/audio.c`.

The ROM-logic track starts from naturally NMI-reached `SoundEngine`
calls and varies only sound queue/RAM at the reached entry to invoke
the register and frequency helpers. It records the original helper
PCs, source RAM/ROM reads, branch decisions and APU writes through
return, then compares the shared C owner at the same inputs. S3's
effect tables and S4–S6's dispatchers remain named dependencies and
receive no S2 credit. The independent operational track runs focused
audio and platform-purity checks, full x86/x64 regression against the
11-failure baseline, two Windows self-tests, DOS16 MZ build, and three
refreshed owner-requested EXEs.
