# Project Status

## Current Work

**M2 T49 S1 is active at 1,823 / 1,992.** T48 closed all 74 sound-effect
labels through `Cont_CGrab_TTick`. T49 owns the next 101 music/channel labels
from `JumpToDecLength2` through `DeathMusHdr`; S1 receives its first 14
remaining square-two effect labels through `StopGrowItems`.

## M2 T49 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Active M2 T49 S1, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 source-order mandate; accepted transfer of 14 exact labels from M2 Td S4. |
| Objective | Translate and prove remaining square-two Bowser fall, extra-life and grow-item effect paths. |
| Non-goals | No S2 noise-effect, music-stream or platform audio policy credit. |
| Reference Baseline | 1,823/1,992; 14 open scope labels, 14 expected matches, maximum 1,837/1,992. |
| Candidate Proposal | [T49 S1](../proposals/m2/t49-music-engine-and-channel-handlers.md#s1-admission-remaining-square-two-effects). |
| Files And ABI Surface | Shared `src/game/audio.c`, owner-ROM bindings, bounded audio records, focused tests and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and node validation. |
| Verification | NMI SoundEngine routes with original PC, queue/buffer, counter and APU parity; then separate x86/x64/DOS16 operational pass. |
| Expected Markers | Decrement trampoline, Bowser fall, extra-life guard/phase, power-up reveal and vine-growth completion. |
| Asset Needs | Owner-local ROM/listing inputs; raw records below ignored build; owner-authorized three EXEs. |
| Reporting Requirements | Fourteen exact dispositions, separate ROM-logic and operational tracks, similar-issue sweep and artifact hashes. |
| Stop Conditions | Forced CPU branch, invented audio behavior, platform gameplay or premature S2-S9 credit. |
| Exit Criteria | Fourteen labels individually compared, operational gates and three EXEs, tracker and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All square-two queue/buffer selectors, extra-life guard and shared APU decision points. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and
Win32 x86/x64. Host adapters provide input, timing and presentation only.
The three owner-authorized local EXEs are current with T48 S6. Full CTest is
223/234 on each Windows architecture, with the same 11 recorded baseline
failures and no new failures; both Win32 self-tests and the OpenNT DOS16 link
pass. M2 remains open with 169 nodes not ROM-match complete.
