# M2 T50: music data, tables and audio-data consumers

## Task contract

T50 owns the next **28 open source-order labels** from `Star_CloudMData`
(line 16077) through `BrickShatterEnvData` (line 16368). It starts at
**1,924 / 1,992** and can reach **1,952 / 1,992**. The sole translated owner
is `src/game/audio.c`; platforms consume only its neutral command state. Owner
ROM and the reviewed assembly are local research inputs only. Generated records,
traces and build output remain under ignored `build/`.

| S | Entry -> exit | Exact source-order labels | Owner | Dependency and one ROM route | Expected matches |
| --- | --- | --- | --- | --- | ---: |
| S1 | `Star_CloudMData -> VictoryMusData` | `Star_CloudMData`, `GroundM_P1Data`, `SilenceData`, `GroundM_P2AData`, `GroundM_P2BData`, `GroundM_P2CData`, `GroundM_P3AData`, `GroundM_P3BData`, `GroundMLdInData`, `GroundM_P4AData`, `GroundM_P4BData`, `DeathMusData`, `GroundM_P4CData`, `CastleMusData`, `GameOverMusData`, `TimeRunOutMusData`, `WinLevelMusData`, `UndergroundMusData`, `WaterMusData`, `EndOfCastleMusData`, `VictoryMusData` | `src/game/audio.c` | Receives T49 S9 header records; selector-driven `SoundEngine` streams every channel record through the shared CPU-address reader. | 21 |
| S2 | `FreqRegLookupTbl -> WaterEventMusEnvData` | `FreqRegLookupTbl`, `MusicLengthLookupTbl`, `EndOfCastleMusicEnvData`, `AreaMusicEnvData`, `WaterEventMusEnvData` | `src/game/audio.c` | Follows S1; direct music note/control records exercise frequency, length and envelope lookup consumers. | 5 |
| S3 | `BowserFlameEnvData -> BrickShatterEnvData` | `BowserFlameEnvData`, `BrickShatterEnvData` | `src/game/audio.c` | Follows S2; original noise-SFX records exercise the two envelope-table consumers. | 2 |

The S boundaries retain source order. They split only where the ROM changes from
music stream payloads to music lookup/envelope consumers, then to distinct
noise-SFX envelope consumers. Each S performs node mapping, shared-C comparison,
original-ROM route proof and one three-target operational pass; no platform
source gains audio-table or gameplay logic.

## S1 admission: music stream payload records

S1 receives **21** open labels from `Star_CloudMData` through `VictoryMusData`.
Baseline is **1,924 / 1,992**; all 21 are expected matches, for a maximum of
**1,945 / 1,992**. It follows T49 S9's header-table load and precedes S2's
frequency/length/envelope lookup data. The shared C owner is `src/game/audio.c`.

ROM-logic verification will enumerate every S1 header-selected song record,
compare its four source channel start offsets, then consume each channel until
its source terminator or documented loopback. It will compare byte addresses,
byte values, offset/counter updates, control-byte branches and final APU/RAM
outputs against bounded original `SoundEngine` routes. The operational track runs
a focused stream-record checker, audio smoke, platform purity, Win32 x86/x64
builds and self-tests, OpenNT DOS16 compile/link, and refreshes all three
owner-authorized EXEs. Every scoped record remains owner-local ROM data; no ROM
bytes, generated data or traces are tracked.

## S1 closure: music stream payload records

S1 closes all **21 / 21** admitted labels, raising the verified count from
**1,924 / 1,992** to **1,945 / 1,992**. The payload is not copied into C:
`mysmb_audio_load_music_header` retains the source CPU pointer and every music
channel fetch goes through the shared owner-ROM reader in `audio.c`.

The focused record check names all 49 valid `MusicHeaderData` selectors from
the original event, area and ground-layout tables. It compares each selected
Square2 CPU pointer with its source-label address, proves that all 21 distinct
payload labels are reached, restores the matching event/area music buffer, and
runs one shared `SoundEngine` tick. Both Win32 widths report `21` records and
zero failures. The separate existing music-header smoke and header-table check
also pass on both widths. T49's channel-handler chain remains the evidence for
byte decoding, counters, control branches and APU writes; its handlers consume
these S1 pointers without platform-local audio state.

The operational track compiled the same shared C tree as an OpenNT DOS16 MZ
(`264149` bytes; `MZ` signature), with only the established C4761 conversion
warnings and `OLDNAMES.LIB` linker warning. The required artifacts are
`mysmb16.exe` `BC29D277B101470596389E82B575D7D32F0ECDE2048722D5047DAA1E99C2A0DB`,
`mysmb32.exe` `61511329829DB30935A9EA8C2B8FEF47B8FD3744D8066A8FFC11ED4BAFFD839C`,
and `mysmb64.exe` `A5DE24E79172D57923486E1B7603465D1EB6F6CFD5927B12ED778195BC832D8B`.

Similar-issue sweep: every legal event selector (1–8), area selector (9–16)
and ground-layout selector (17–49) was checked; all duplicate headers resolve
to the same source label and none introduces platform-local music state. S2
retains the lookup/envelope records and S3 retains the noise-envelope records.

## S2 admission: music lookup and envelope tables

S2 receives **five** open labels: `FreqRegLookupTbl`, `MusicLengthLookupTbl`,
`EndOfCastleMusicEnvData`, `AreaMusicEnvData`, and `WaterEventMusEnvData`.
Its baseline is **1,945 / 1,992**; all five are expected matches, with a
maximum of **1,950 / 1,992**. The chain follows S1's stream pointers and ends
at the final normal-music envelope table before S3's noise-only tables.

The ROM-logic track compares `Dump_Freq_Regs`' paired table reads, the exact
`ProcessLengthData` index addition, and all three `LoadEnvelopeData` branches
against the source CPU table addresses. The operational track adds a focused
lookup-table test, runs the existing music-stream test and platform-purity
check on x86/x64, links the OpenNT DOS16 target, and refreshes the three
required executable artifacts. All reads remain in shared `audio.c`.

## S2 closure: music lookup and envelope tables

S2 closes all **five / five** admitted labels, moving verified conformance
from **1,945 to 1,950 / 1,992**: `FreqRegLookupTbl`,
`MusicLengthLookupTbl`, `EndOfCastleMusicEnvData`, `AreaMusicEnvData`, and
`WaterEventMusEnvData`. No labels were deferred or transferred.

The ROM-logic evidence follows the source chain exactly. `Dump_Freq_Regs`
reads each frequency pair as `table+1,Y` then `table,Y`, returns before writes
when the low byte is zero, and writes the original channel-relative APU
offsets. `ProcessLengthData` applies its low-three-bit mask and both source
addends before its table read. `LoadEnvelopeData` selects the castle-event,
water/event, or normal-area table in the source branch order. The focused
owner-ROM checker covers all 51 frequency pairs through both square-one and
triangle offsets, all 48 length entries plus indexed addition, and all 52
normal-music envelope entries; it reports 203 checks and zero failures on
both Windows widths. The test contains only source addresses and reads table
bytes from the owner-local ROM at runtime.

The operational track passed the music header, header table, stream record and
platform-purity tests on Win32 x86 and x64. The same C90 shared core compiled
and linked through the existing OpenNT DOS16 chain into a 264149-byte MZ
program; established C4761 conversion and `OLDNAMES.LIB` warnings remain
non-fatal. Refreshed artifact hashes are `mysmb16.exe`
`0FE56863DA85261D8739D6BC709D24DCAA04C9D0288BB1D73EE512EFB17E847A`,
`mysmb32.exe` `8428BA6DE8236BF0ED186ABC28BE09F0E5E9928D9035396F145146DEC5398E98`,
and `mysmb64.exe` `733218FA79BDE49D3F28FF802742FE9D6AA59F4A9716068505DDB2301A6A49EE`.

Similar-issue sweep: all three `Dump_Freq_Regs` channel offsets, every
length-table index, and all three normal-music envelope branches route through
shared `audio.c`; no platform adapter reads or interprets music-table data.

## S3 admission: noise-envelope consumers

S3 receives **2** open labels in source order: `BowserFlameEnvData` and
`BrickShatterEnvData`. Its baseline is **1,950 / 1,992**; both are expected
matches, for a maximum of **1,952 / 1,992**. The contiguous shared-owner route
is `NoiseSfxHandler -> PlayBrickShatter/ContinueBrickShatter` and
`PlayBowserFlame/ContinueBowserFlame -> PlayNoiseSfx`. The ROM-logic track
compares queue and active-buffer branches, length shift/index semantics,
CPU-address table reads, APU writes and decrement order. The operational track
runs focused noise envelope and snapshot checks, x86/x64 builds, the existing
OpenNT DOS16 compile/link, platform purity, and refreshes all three artifacts.
DOS16 remains active through that original toolchain; DOSBox is not used.

## S3 closure: noise-envelope consumers

S3 closes both admitted labels, `BowserFlameEnvData` and
`BrickShatterEnvData`, raising verified conformance from **1,950 to 1,952 /
1,992**. No scoped label was deferred or transferred.

The ROM-logic track follows `NoiseSfxHandler` exactly. A queued brick-shatter
bit selects `PlayBrickShatter`, initializes length `$20`, and then only odd
length phases execute `LSR`, `TAY`, `BrickShatterEnvData,Y`, `PlayNoiseSfx`,
and the decrement tail. The shared C reader uses CPU `$ffea + Y`. The brick
terminal phase retains the source order: it writes the envelope, then the
decrement tail mutes noise at zero. A Bowser-flame bit selects
`PlayBowserFlame`, initializes `$40`, shifts the live length and reads
`BowserFlameEnvData-1,Y`; the C reader deliberately starts at `$ffc9`, so
`Y=1..32` selects source bytes `$ffca..$ffe9`. It writes the source `$0f`
period and `$18` length register before the common decrement. No platform
source reads either table or implements these branches.

The focused owner-ROM test drives the shared `mysmb_audio_step` route for all
16 brick phases and all 32 Bowser phases, checking the selected envelope,
noise registers and length transition. It reports **48 checks, zero failures**
on both Win32 x86 and x64. Existing music lookup verification also reports
203 checks, zero failures on both widths; the platform-purity gate passes on
both widths. The same shared C90 source compiled and linked with the existing
OpenNT DOS16 toolchain to a 264149-byte MZ executable; its established C4761
conversion and `OLDNAMES.LIB` warnings remain non-fatal. Refreshed artifacts:
`mysmb16.exe` `0FE56863DA85261D8739D6BC709D24DCAA04C9D0288BB1D73EE512EFB17E847A`,
`mysmb32.exe` `2262FBB943A56995DA323F9803829549AD35EDDB419BB4265CD4F809E6432E7E`,
and `mysmb64.exe` `58EF871A0B1588811932A056A966556FCDB21B491E32B9ECF23FA85F2F9F18B7`.

Similar-issue sweep: both noise-envelope reads in `src/game/audio.c` were
reviewed for CPU base, index calculation, queue versus active-buffer routing,
APU write order and decrement order. Both are shared-game-only; no platform
adapter has a matching production read or branch.
