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
