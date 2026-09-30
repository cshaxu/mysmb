# Project Status

## Current Work

**M2 T49 S3 is active at 1,849 / 1,992.** It owns the 10-label music selection and header-loading chain from `MusicHandler` through `LoadHeader`.

## M2 T49 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Active M2 T49 S3, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 source-order mandate; accepted transfer of 10 exact labels from M2 Td S4. |
| Objective | Translate and prove music queue selection, header lookup and header loading. |
| Non-goals | No square/triangle/noise stream parsing or platform audio policy credit. |
| Reference Baseline | 1,849/1,992; 10 open scope labels, 10 expected matches, maximum 1,859/1,992. |
| Candidate Proposal | T49 S3 music selection and header loading. |
| Files And ABI Surface | Shared audio.c, owner-ROM bindings, bounded audio records, focused tests and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and node validation. |
| Verification | NMI SoundEngine event/area selection paths with selector, header, RAM and APU parity; separate x86/x64/DOS16 operational pass. |
| Expected Markers | Event priority, area loop-B lookup, header pointer, music offsets and channel reset writes. |
| Asset Needs | Owner-local ROM/listing inputs; raw records below ignored build; owner-authorized three EXEs. |
| Reporting Requirements | Ten exact dispositions, separate ROM-logic and operational tracks, similar-issue sweep and artifact hashes. |
| Stop Conditions | Forced selector, invented header mapping, platform gameplay or premature S4-S9 credit. |
| Exit Criteria | Ten labels individually compared, operational gates and three EXEs, tracker and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All music queues/buffers, header selectors, channel reset writes and loop-B paths. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32 x86/x64. Host adapters provide input, timing and presentation only. Full CTest is 224/235 on each Windows architecture with the same 11 recorded baseline failures and no new failures. DOS16 remains an active OpenNT-toolchain target.
