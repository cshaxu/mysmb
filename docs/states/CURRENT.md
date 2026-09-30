# Project Status

## Current Work

**M2 T49 S7 is active at 1,884 / 1,992.** It owns the eight-label noise music
beat chain from `HandleNoiseMusic` through `ExitMusicHandler`.

## M2 T49 S7 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Active M2 T49 S7, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 source-order mandate; accepted transfer of eight exact labels from M2 Td S4. |
| Objective | Translate and prove the noise music gate, stream loop, beat selection and noise-register writes. |
| Non-goals | No shared music-length/control/envelope helper, music header/data or platform audio-policy credit. |
| Reference Baseline | 1,884/1,992; eight open scope labels, eight expected matches, maximum 1,892/1,992. |
| Candidate Proposal | T49 S7 noise beat stream and exit. |
| Files And ABI Surface | Shared audio.c, owner-ROM bindings, bounded audio records, focused tests and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and node validation. |
| Verification | Original-ROM SoundEngine routes for area bypass, counter exit, zero loopback and beat classes; RAM/APU parity; separate x86/x64/DOS16 operational pass. |
| Expected Markers | Area-music gate, noise counter/offset, loopback offset, `AlternateLengthHandler` boundary and `$400c/$400e/$400f`. |
| Asset Needs | Owner-local ROM/listing inputs; raw records below ignored build; owner-authorized three EXEs. |
| Reporting Requirements | Eight exact dispositions, separate ROM-logic and operational tracks, similar-issue sweep and artifact hashes. |
| Stop Conditions | Invented beat parser semantics, copied ROM music bytes into tracked product data, platform gameplay/audio policy, or premature S8-S9 credit. |
| Exit Criteria | Eight labels individually compared, operational gates and three EXEs, tracker and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All noise area gates, beat offsets/loopback, duration conversion boundaries and noise-register selection paths. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32
x86/x64. Host adapters provide input, timing and presentation only. S6 closed
at 1,884/1,992 with four bounded original-ROM triangle routes at zero x86/x64
difference. DOS16 remains an active OpenNT-toolchain target.
