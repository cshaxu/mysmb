# Project Status

## Current Work

**M2 T49 S6 is active at 1,878 / 1,992.** It owns the six-label triangle
music-stream and control-register chain from `HandleTriangleMusic` through
`LoadTriCtrlReg`.

## M2 T49 S6 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Active M2 T49 S6, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 source-order mandate; accepted transfer of six exact labels from M2 Td S4. |
| Objective | Translate and prove triangle stream parsing, note timing and control-register selection. |
| Non-goals | No noise stream, shared length/control helper, music data or platform audio-policy credit. |
| Reference Baseline | 1,878/1,992; six open scope labels, six expected matches, maximum 1,884/1,992. |
| Candidate Proposal | T49 S6 triangle music stream and control register. |
| Files And ABI Surface | Shared audio.c, owner-ROM bindings, bounded audio records, focused tests and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and node validation. |
| Verification | Original-ROM SoundEngine route after selected music header; triangle stream-control, RAM and APU parity; separate x86/x64/DOS16 operational pass. |
| Expected Markers | Stream offset/length, zero-byte control branch, note/control path and `$4008` selector. |
| Asset Needs | Owner-local ROM/listing inputs; raw records below ignored build; owner-authorized three EXEs. |
| Reporting Requirements | Six exact dispositions, separate ROM-logic and operational tracks, similar-issue sweep and artifact hashes. |
| Stop Conditions | Invented stream parser semantics, copied ROM music bytes into tracked product data, platform gameplay/audio policy, or premature S7-S9 credit. |
| Exit Criteria | Six labels individually compared, operational gates and three EXEs, tracker and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All triangle stream offsets, null/control branch, length/note pair and music control-register paths. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32
x86/x64. Host adapters provide input, timing and presentation only. S5 closed
at 1,878/1,992 with four bounded original-ROM routes at zero x86/x64
difference. DOS16 remains an active OpenNT-toolchain target.
