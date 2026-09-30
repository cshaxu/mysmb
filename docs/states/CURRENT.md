# Project Status

## Current Work

**M2 T48 S5 is active at 1,801 / 1,992.** T47 closed all 40
source-order labels through `SetHFAt`. T48 owns the next 74 labels
from `SoundEngine` to `Cont_CGrab_TTick`; S1 completed its 13-label
SoundEngine pause/queue/DAC chain through `StrWave`; S2 closed nine
register/frequency helper labels through `SetFreq_Tri`. S3 closed 14
square-one effect-phase labels through `DecJpFPS`. S4 closed 16
square-one dispatch/lifetime labels through `NoPDwnL`. S5 owns the next
18 square-two data/effect labels through `ExSfx2`.

## M2 T48 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Active M2 T48 S5, source-order implementation. |
| Admission And Approval | Continuing owner-approved M2 source-order mandate; accepted transfer of 18 exact S5 labels from M2 Td S4. |
| Objective | Translate and prove square-two effect data, coin/timer, blast, power-up and effect lifetime from `ExtraLifeFreqData` through `ExSfx2`. |
| Non-goals | No premature S6 square-two dispatcher or T49 music-node credit; no platform sound policy. |
| Reference Baseline | 1,801/1,992; 18 open scope labels, 18 expected new matches, maximum 1,819/1,992. T48 total scope 74, maximum 1,823. |
| Candidate Proposal | [T48 S5](../proposals/m2/t48-sound-effects-and-channel-handlers.md#s5-admission-square-two-effect-data-and-phases). |
| Files And ABI Surface | Shared `src/game/audio.c`, owner-ROM table binding, bounded sound-entry records, focused tests and three EXEs. |
| Applicable Rules | Task Reading Set, execution, architecture/coding, documentation, source policy, ledger and node validation. |
| Verification | Natural NMI SoundEngine and bounded square-two queue/buffer routes; source PC, table, branch, RAM and APU parity, then separate x86/x64/DOS16 operational pass. |
| Expected Markers | Owner-ROM frequency tables, coin/timer, blast, power-up, decrement and stop behavior. |
| Asset Needs | Owner-local smb1.nes and reviewed SMBDIS.ASM are local nonredistributable inputs; all raw records under ignored build; owner-authorized three EXEs. |
| Reporting Requirements | Eighteen exact dispositions, separate ROM-logic and operational tracks, similar-issue sweep and artifact hashes. |
| Stop Conditions | Forced CPU branch, invented APU behavior, platform gameplay or uncredited downstream assumptions. |
| Exit Criteria | Pending: 18 source labels individually compared, operational gates and three EXEs, tracker and ledger closure. |
| Original Owner Request | Faithful original ROM logic in shared native C for DOS16, x86 and x64. |
| Similar-Issue Sweep | All square-two effect/data branches, table users and platform audio decision points. |

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and
Win32 x86/x64. Host adapters provide input, timing and presentation only.
The three owner-authorized local EXEs are current with T48 S4. Full CTest
is 222/233 on each Windows architecture, with the same 11 recorded
baseline failures and no new failures; both Win32 self-tests and the
DOS16 link pass. M2 remains open with 191 nodes not ROM-match complete.
