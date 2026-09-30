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

### S2 ROM-logic evidence

The unchanged owner ROM reached all nine helper PCs after naturally
entering `SoundEngine` from NMI. The recorder varied only sound queue
and music selection RAM at that entry. Twenty-two retained routes
produced **429 original helper entry/return pairs**. Both native
widths compared the input A/X/Y, full 24-register APU image, and
resulting A/APU output at each pair: **858 comparisons, zero
differences**. Source inspection separately confirms no helper writes
CPU RAM and confirms the store order shown below. The original
`Dump_Freq_Regs` path took the nonzero frequency branch 99 times and
the zero-low-byte `NoTone` branch six times. Refactoring the S1 pause
tone through these helpers retained 84/84 original SoundEngine-entry
comparisons across both widths.

| Node / original PC | Hits | Original branch, read, write and native owner |
| --- | ---: | --- |
| `Dump_Squ1_Regs` `$f381` | 39 | Y to `$4001`, then X to `$4000`; `mysmb_audio_dump_squ1_regs`. |
| `PlaySqu1Sfx` `$f388` | 18 | Calls square-one control writer, then square-one frequency writer; `mysmb_audio_play_squ1_sfx`. |
| `SetFreq_Squ1` `$f38b` | 39 | Selects X=0 and falls through; `mysmb_audio_set_freq_squ1`. |
| `Dump_Freq_Regs` `$f38d` | 105 | Y=A, reads `$ff01+Y`; zero branches to `NoTone`, otherwise writes `$4002+X`, reads `$ff00+Y`, ORs `$08`, writes `$4003+X`; `mysmb_audio_dump_freq_regs`. The shared read preserves 16-bit CPU-address wrap. |
| `NoTone` `$f39e` | 105 | RTS without another APU write; six entries came from zero-LSB branch; zero and nonzero return-A values were compared. |
| `Dump_Sq2_Regs` `$f39f` | 39 | X to `$4004`, then Y to `$4005`; `mysmb_audio_dump_sq2_regs`. |
| `PlaySqu2Sfx` `$f3a6` | 18 | Calls square-two control writer, then its frequency writer; `mysmb_audio_play_sq2_sfx`. |
| `SetFreq_Squ2` `$f3a9` | 45 | Selects X=4 and branches into shared frequency writer; `mysmb_audio_set_freq_sq2`. Return A preserves the rest/non-rest decision for its later music caller. |
| `SetFreq_Tri` `$f3ad` | 21 | Selects X=8 and branches into shared frequency writer; `mysmb_audio_set_freq_tri`. |

This certifies the helper nodes as callable shared game logic. The
existing square-effect and music dispatch paths remain provisional;
S3–S6 and T49 must connect their original call sites to these helpers
and prove whole-chain state and APU output before receiving credit.

### S2 closure: APU register and frequency helpers

**P1 result: nine intended matches, nine actual matches, no scoped
deferments; 1,762 → 1,771/1,992.** The nine individual dispositions
are the nine source-PC rows above. The ROM-logic track used the
unchanged owner ROM and real helper stack returns, with no forced CPU
branch or substituted program data. The helper checker compared all
24 APU registers and return A on 429 original calls in each native
width. The S1 pause entry was independently replayed on its original
14 routes and 42 calls per width, with no S1-owned regression.

The operational track rebuilt Win32 x86/x64 and DOS16 from the shared
C source. The DOS16 toolchain linked a valid MZ executable; both
Windows EXEs passed `--self-test`. The final x86 and x64 CTest matrices
each passed **222/233** with exactly the 11 pre-existing T47 failures
and no new failure; focused `mysmb.audio-smoke` and
`mysmb.platform-purity` passed on both widths. The three packaged
artifacts match their built sources byte-for-byte:

| Owner-requested artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `a0834c14ff5dd54c6a8d2714e36a899d56a0a3917a4309edba0b21aa4fc1bdf9` |
| `assets/mysmb32.exe` | `50a6ec76bedbb287465942c0f4cc23eb0ec534327ad803f9acc2b4220f2a0de0` |
| `assets/mysmb64.exe` | `9f893232f84b213d6c5f4d2b779c4d951be367a9c43beef2604c8808bb1f2a39` |

The similar-issue sweep found the helper implementations and the
frequency-table access only in shared `src/game/audio.c`; no platform
source owns APU lookup or branch policy. Pause tone now calls the
shared square-one helper. The remaining provisional square effects,
music callers, and frame-wide APU behavior stay with their named
S3–S6/T49 nodes; S2's callable-helper proof does not close them.

## S3 admission: square-one effect phases

S2 closed at **1,771/1,992**. S3 accepts the next 14 **open** labels
in source order: `SwimStompEnvelopeData`, `PlayFlagpoleSlide`,
`PlaySmallJump`, `PlayBigJump`, `JumpRegContents`, `ContinueSndJump`,
`N2Prt`, `FPS2nd`, `DmpJpFPS`, `PlayFireballThrow`, `PlayBump`,
`Fthrow`, `ContinueBumpThrow`, `DecJpFPS`. All 14 are intended to
become ROM matches, for a maximum **1,785/1,992**. The slice begins
with the original envelope data immediately after `SetFreq_Tri` and
ends at `DecJpFPS` before S4's `Square1SfxHandler`. The shared owner
is `src/game/audio.c`; S2's frequency helpers are admitted dependencies.

The ROM-logic track enters the unchanged ROM's `SoundEngine` through
NMI and varies only original sound queue/RAM at that entry. It covers
small/big jump, flagpole slide, fireball throw and bump, then advances
their original counters into later phases. It compares source PCs,
table reads, branch decisions, RAM counters and APU writes with the
shared C owner. The envelope data is read from the owner ROM rather
than copied into tracked source. S4's dispatcher and effect-lifetime
nodes remain explicit dependencies, without premature credit. The
operational track runs focused audio and purity checks, full x86/x64
regression against the 11-failure baseline, both Windows self-tests,
DOS16 MZ build, and three refreshed owner-requested EXEs.

### S3 ROM-logic evidence

The unchanged owner ROM reached 13 executable S3 labels through the
original NMI `SoundEngine` call. Five queue selections covered small
and big jump, bump, fireball throw and flagpole slide; eight bounded
buffer/counter states covered continuation and second/third phases.
These **13 active routes produced 39 original SoundEngine calls**.
The native x86/x64 checker compared square-one buffer and length RAM,
and all four square-one APU registers after each call: **78 comparisons,
zero S3-owned differences**. The original swim/stomp route executed
`ContinueSwimStomp`'s indexed read at `$f46c` three times. That source
instruction reads `SwimStompEnvelopeData-1,Y`; the shared C accessor
was checked against all 14 owner-ROM table entries. The table remains
outside tracked C source. No ROM byte, CPU PC or return stack was
altered by the recorder.

| Node / original PC | Hits | Source control and shared C mapping |
| --- | ---: | --- |
| `SwimStompEnvelopeData` `$f3b1` | data; three source reads | Fourteen owner-ROM bytes read through `mysmb_audio_swim_stomp_envelope`, indexed by the original remaining-length Y. S4 owns the eventual swim/stomp caller. |
| `PlayFlagpoleSlide` `$f3bf` | 3 | Length `$40`, frequency offset `$62`, then X=`$99`/Y=`$bc` control writes; `mysmb_audio_square1_play_flagpole`. |
| `PlaySmallJump` `$f3cd`, `PlayBigJump` `$f3d1`, `JumpRegContents` `$f3d3` | 3, 3, 6 | Frequency `$26` or `$18` with X=`$82`/Y=`$a7`, then length `$28`; `mysmb_audio_square1_play_jump`. |
| `ContinueSndJump` `$f3df`, `N2Prt` `$f3ec` | 18, 15 | Remaining length `$25` selects X=`$5f`/Y=`$f6`; `$20` selects the third phase, otherwise proceeds to the decrement tail; `mysmb_audio_square1_continue_jump`. |
| `FPS2nd` `$f3f2`, `DmpJpFPS` `$f3f4` | 6, 9 | Shared Y=`$bc` flagpole/third-jump path and square-one control writer. |
| `PlayFireballThrow` `$f3f9`, `PlayBump` `$f3ff`, `Fthrow` `$f403` | 3, 3, 6 | Length `$05`/`$0a`, Y=`$99`/`$93`, X=`$9e`, shared frequency `$0c`; `mysmb_audio_square1_play_throw`. |
| `ContinueBumpThrow` `$f40d`, `DecJpFPS` `$f419` | 18, 39 | Remaining length `$06` writes `$bb` to `$4001`; source branches into S4's decrement tail. The shared C phase helper runs before that same provisional decrement. |

The `Square1SfxHandler` dispatcher, swim/stomp caller and decrement
lifetime are S4 scope. S3's direct phase comparisons prove this slice
and its S2 helper calls; they do not certify the whole square-one
handler or the later music/noise routes.

### S3 closure: square-one effect phases

**P1 result: 14 intended matches, 14 actual matches, no scoped
deferments; 1,771 to 1,785/1,992.** The 14 individual dispositions are
the source-PC/data rows above. The ROM-logic track used 39 original
SoundEngine calls over 13 bounded effect routes, 78 x86/x64 native
comparisons of the S3-owned RAM/APU outputs with zero differences, and
all 14 owner-ROM envelope bytes. Original NMI entry, CPU code and return
stack were preserved. S4's queue dispatcher and lifetime remain open.

The operational track built Win32 x86/x64 and DOS16 from shared C. Both
Windows products passed `--self-test`; DOS16 linked as an MZ executable.
The full x86 and x64 CTest matrices each passed **222/233**, with exactly
the 11 recorded baseline failures and no new failure. The focused audio
and platform-purity tests passed on both widths. Two pre-existing smoke
tests had passed an uninitialized host container to the RAM-only
`mysmb_game_initialize_memory`; initializing that container removed an
x64-only OAM-test crash and restored the collision test's prior failure
code. This changed test setup only, not translated game behavior.

| Owner-requested artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `d292f16ea303307ca21b409cbc13dfbb3a472dc46933cffefa287781b738cae` |
| `assets/mysmb32.exe` | `281e4884e4ec1954bc064c21c714c20a2ab7ea49ceea5e10bcfb702218280291` |
| `assets/mysmb64.exe` | `e5a1e233daa101e67414ff1532b33bcf5fc3a1b00dd870f61d59944fc04a33e2` |

The similar-issue sweep found square-one phase decisions only in shared
`src/game/audio.c`; neither platform adapter selects effects or modifies
sound queues. The test-fixture defect was checked in the two failing
tests and corrected before the full cross-width regression. The
unmigrated square-one dispatcher, swim/stomp continuation and effect
lifetime are explicitly S4's next source-order chain.

## S4 admission: square-one dispatch and lifetime

S3 closed at **1,785/1,992**. S4 accepts the next 16 **open** labels in
source order: `Square1SfxHandler`, `CheckSfx1Buffer`, `ExS1H`,
`PlaySwimStomp`, `ContinueSwimStomp`, `BranchToDecLength1`,
`PlaySmackEnemy`, `ContinueSmackEnemy`, `SmSpc`, `SmTick`,
`DecrementSfx1Length`, `StopSquare1Sfx`, `ExSfx1`, `PlayPipeDownInj`,
`ContinuePipeDownInj`, `NoPDwnL`. All 16 are intended ROM matches, for
a maximum **1,801/1,992**. This chain begins with the original
`Square1SfxHandler` queue selector immediately after `DecJpFPS` and
ends at `NoPDwnL` before S5's `ExtraLifeFreqData`. Shared owner is
`src/game/audio.c`; S2 register helpers and S3 effect phases are its
predecessor dependencies. The S5/S6 square-two route is outside scope.

The ROM-logic track enters the unchanged ROM's SoundEngine through NMI,
selects each square-one queue priority and continuation buffer route,
and checks original dispatch PCs, shifts, branch order, effect counters,
stop behavior, table reads and APU writes against shared C. The route
also covers swim/stomp, smack and pipe effects missing from S3. The
operational track runs focused audio and purity tests, x86/x64 full
regression against the 11-failure baseline, both Windows self-tests,
DOS16 MZ link and three refreshed EXEs. Any unresolved dependency is
reported by exact label rather than silently credited.

### S4 ROM-logic evidence

The unchanged owner ROM was entered through NMI SoundEngine with only
original queue, buffer and counter RAM varied at the entry. Twenty-four
bounded routes produced 192 original entry/return calls. The shared C
checker compared Square1SoundBuffer, Square1SoundQueue,
Squ1_SfxLenCounter and APU `$4000`–`$4003` plus `$4015` after every
call: **384 x86/x64 comparisons, zero S4-owned differences**. Eight
S3 continuation routes were replayed separately on 64 original calls
and both native widths without regression. The source coverage log hit
all 16 S4 labels, including the zero-counter stop, no-effect exit,
priority-bit overlap, swim envelope and pipe gating branches. No ROM
byte, CPU PC or return stack was altered.

| Node / original PC | Hits | Source behavior and shared C mapping |
| --- | ---: | --- |
| `Square1SfxHandler` `$f41b` | 1152 | Save unshifted queue in `$f1`, then test sign and shift `$ff` by source priority; `mysmb_audio_step_square1`. |
| `CheckSfx1Buffer` `$f43f`, `ExS1H` `$f45a` | 1072, 555 | Empty buffer exits; otherwise bit priority selects continuation; same shared handler. |
| `PlaySwimStomp` `$f45b`, `ContinueSwimStomp` `$f469` | 8, 84 | Length `$0e`, initial frequency/control, then indexed owner-ROM envelope write and `$9e` frequency at length six. |
| `BranchToDecLength1` `$f47b` | 317 | Join the common decrement tail after continuation. |
| `PlaySmackEnemy` `$f47d`, `ContinueSmackEnemy` `$f48d` | 8, 57 | Length `$0e`, initial frequency/control; later length eight changes frequency and control, other lengths write spacing control. |
| `SmSpc` `$f49d`, `SmTick` `$f49f` | 47, 57 | `$90` spacing control or `$9f` accent control written to `$4000`. |
| `DecrementSfx1Length` `$f4a2`, `StopSquare1Sfx` `$f4a7`, `ExSfx1` `$f4b5` | 597, 54, 597 | Decrement `$07bb`; on zero clear `$f1` and write `$0e` then `$0f` to `$4015`; return. |
| `PlayPipeDownInj` `$f4b6`, `ContinuePipeDownInj` `$f4bb`, `NoPDwnL` `$f4d1` | 8, 167, 167 | Length `$2f`; write initial or continuation frequency/control only when original two shifts and bit-one gate allow, then decrement. |

The S4 chain is contained in shared `src/game/audio.c`; neither Win32
nor DOS selects an effect or modifies a game queue. S5's square-two
effects and S6's square-two dispatcher retain their own node custody.

### S4 closure: square-one dispatch and lifetime

**P1 result: 16 intended matches, 16 actual matches, no scoped
deferments; 1,785 to 1,801/1,992.** The individual dispositions are
the 16 source-PC rows above. ROM logic proof covers the original bit
priority, buffer continuation, three new effect families and common
decrement/stop branches on 192 owner-ROM calls, with 384 cross-width
comparisons and zero scoped differences. The 64-call S3 continuation
replay also has zero regressions.

The operational track rebuilt Win32 x86/x64 and DOS16 from shared C.
The DOS16 toolchain linked a valid MZ executable and both Windows
products passed `--self-test`. The final x86 and x64 CTest matrices
each passed **222/233**, with exactly the 11 recorded baseline failures
and no new failure; focused audio and platform-purity checks passed.

| Owner-requested artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `449a92710eac74b73774a05d0862d10214da9e799c773350e2523380e1cdffed` |
| `assets/mysmb32.exe` | `1b355ee98e127196deed003fec31aa426366c430590653b9f81de1cd42ebe688` |
| `assets/mysmb64.exe` | `9172d2c71a10ae9386b4df47dee7ea39ff901b30ad0b0ebf5420fbfefff6411f` |

The similar-issue sweep checked the whole square-one queue/buffer
branch family and every shared audio/host boundary. All effect policy
stays in `src/game/audio.c`; host adapters only consume audio output.
The remaining square-two handlers retain S5/S6 custody. S4 neither
credits nor substitutes their unfinished nodes.

## S5 admission: square-two effect data and phases

S4 closed at **1,801/1,992**. S5 accepts the next 18 **open** labels in
source order: `ExtraLifeFreqData`, `PowerUpGrabFreqData`,
`PUp_VGrow_FreqData`, `PlayCoinGrab`, `PlayTimerTick`,
`CGrab_TTickRegL`, `ContinueCGrabTTick`, `N2Tone`, `PlayBlast`,
`ContinueBlast`, `SBlasJ`, `PlayPowerUpGrab`, `ContinuePowerUpGrab`,
`LoadSqu2Regs`, `DecrementSfx2Length`, `EmptySfx2Buffer`,
`StopSquare2Sfx`, `ExSfx2`. All 18 are intended ROM matches, for a
maximum **1,819/1,992**. This shared `src/game/audio.c` chain begins
with the three original frequency-data tables immediately after
`NoPDwnL` and ends at `ExSfx2` before S6's `Square2SfxHandler`.
S2's register helpers and S4's channel separation are predecessors;
S6's dispatcher is a named successor, without premature credit.

The ROM-logic track binds tables through the owner ROM and enters the
original square-two effects through NMI SoundEngine using bounded queue,
buffer and counter states. It compares source PCs, table indices,
branches, RAM writes and APU registers with shared C. The operational
track runs focused audio and purity tests, full x86/x64 regression,
Windows self-tests, DOS16 MZ link and three refreshed EXEs. Every label
will receive an individual disposition at closure.

### S5 ROM-logic evidence

The unchanged owner ROM ran ten bounded square-two queue/buffer/counter
routes through NMI SoundEngine. They produced **80 original calls**;
the native checker compared Square2SoundBuffer, Square2SoundQueue,
Squ2_SfxLenCounter and APU `$4004`–`$4007` plus `$4015` after each
return: **160 x86/x64 call comparisons, zero S5-owned differences**.
The source coverage hit every executable S5 label. Direct binding checks
also compared all six `ExtraLifeFreqData`, 30 `PowerUpGrabFreqData` and
32 `PUp_VGrow_FreqData` bytes with the owner ROM. No ROM byte, CPU PC
or return stack was altered, and no frequency table was copied into
tracked source.

| Node / original PC | Hits | Source behavior and shared C mapping |
| --- | ---: | --- |
| `ExtraLifeFreqData` `$f4d4`, `PowerUpGrabFreqData` `$f4da`, `PUp_VGrow_FreqData` `$f4f8` | data | 68 owner-ROM bytes bound through three shared C accessors using the source's table-1,Y addressing. |
| `PlayCoinGrab` `$f518`, `PlayTimerTick` `$f51e`, `CGrab_TTickRegL` `$f522` | 8, 8, 16 | Load `$35`/`$06`, X `$8d`/`$98`, Y `$7f`, frequency `$42`; shared square-two leaf. |
| `ContinueCGrabTTick` `$f52c`, `N2Tone` `$f538` | 165, 165 | At remaining length `$30`, write `$54` to `$4006`; then common decrement. |
| `PlayBlast` `$f53a`, `ContinueBlast` `$f545`, `SBlasJ` `$f550` | 8, 62, 17 | Start length `$20` with `$5e/$9f/$94`; at `$18`, change to `$18/$9f/$93`; then decrement. |
| `PlayPowerUpGrab` `$f552`, `ContinuePowerUpGrab` `$f557`, `LoadSqu2Regs` `$f565` | 8, 144, 93 | Start length `$36`; on even lengths read `PowerUpGrabFreqData-1,Y` and write `$5d/$7f` plus source frequency. |
| `DecrementSfx2Length` `$f568`, `EmptySfx2Buffer` `$f56d`, `StopSquare2Sfx` `$f571`, `ExSfx2` `$f57b` | 379, 11, 11, 379 | Decrement `$07bd`; on zero clear `$f2`, then write `$0d` and `$0f` to `$4015`; return. |

The existing S6 square-two dispatcher remains outside this S's node
credit. S5 only provides its source-accurate effect leaves and tables in
shared `src/game/audio.c`; platforms do not choose queues or effects.

### S5 closure: square-two effect data and phases

**P1 result: 18 intended matches, 18 actual matches, no scoped
deferments; 1,801 to 1,819/1,992.** The individual dispositions are
the rows above. S4's eight continuation routes were regenerated and
compared on both widths without regression. The operational track built
Win32 x86/x64 and DOS16 from shared C; both Windows self-tests passed
and DOS16 linked as a valid MZ executable. Full x86/x64 CTest each
remain **222/233**, with precisely the documented 11 unresolved legacy
failures and no new failure.

| Owner-requested artifact | SHA-256 |
| --- | --- |
| `assets/mysmb16.exe` | `7645b76cc5139f4fd9cd4b18f52eb0b75341bdee0e7f5806d5ccc64b0781b1c5` |
| `assets/mysmb32.exe` | `2df0ca87fabeedde4143b64a67d1bbeb6727bb97eff3609bc7943ef0bf663fb1` |
| `assets/mysmb64.exe` | `29241d6f854f39226a761573c84560e2fd957746b7aedf13c829a7b805033f86` |

The similar-issue sweep covered all square-two data/leaf paths and
confirmed that table indexing, APU writes, counters and stop policy are
owned by shared C only. S6 retains queue-dispatch custody; this closure
does not credit its selection or special extra-life path.

## S6 admission: square-two queue dispatcher

S5 closed at **1,819/1,992**. S6 accepts the final four T48 labels in
source order: `Square2SfxHandler`, `CheckSfx2Buffer`, `ExS2H`, and
`Cont_CGrab_TTick`. All four are intended ROM matches, for a maximum
**1,823/1,992**. The chain begins at the square-two queue dispatcher
after S5's `ExSfx2`, ends at its `ContinueCGrabTTick` trampoline, and
uses S5's exact effect leaves as dependencies. Subsequent Bowser,
extra-life and grow-item implementation labels are T49-or-later scope
and receive no S6 credit.

The ROM-logic track enters unchanged SoundEngine through NMI with
bounded queue and buffer states. It covers sign/bit priority, the
extra-life interruption guard, empty exits and each buffered selector,
then compares PCs, queue shifts, RAM and APU output with shared C. The
operational track reruns the focused audio/purity checks, x86/x64
regression, Windows self-tests, DOS16 MZ link and three EXEs. Closure
will name each of the four node dispositions before T48 can close.
