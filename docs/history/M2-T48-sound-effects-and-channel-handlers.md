# M2 T48: sound-effect queue and channel handlers

## T48 closure

All **74 source-order labels** from `SoundEngine` through
`Cont_CGrab_TTick` are ROM-match complete across S1-S6. The verified
numerator advances **1,749 -> 1,823 / 1,992**. No T48 label is deferred. The
next source label, `JumpToDecLength2`, belongs to the following music/channel
source slice.

| Chain | Nodes | ROM-logic evidence |
| --- | ---: | --- |
| S1 SoundEngine pause/queue/DAC | 13 | Natural title, game and pause NMI paths; source PC/RAM/APU comparison. |
| S2 APU register/frequency helpers | 9 | Source register order and owner-ROM frequency access. |
| S3 square-one phases | 14 | Effect phase lengths, branches and APU writes. |
| S4 square-one dispatch/lifetime | 16 | Queue priority, buffer selection and lifetime routes. |
| S5 square-two effects/data | 18 | 80 original calls, 160 cross-width comparisons and 68 owner-ROM table bytes. |
| S6 square-two dispatcher | 4 | 80 original calls and 160 cross-width comparisons. |

The [T48 proposal](../proposals/m2/t48-sound-effects-and-channel-handlers.md)
contains each source PC, control/read/write mapping and S-specific evidence.
Raw ROM records remain ignored under `build/`. All translated queue, table,
RAM and APU behavior stays in shared C; platform adapters only consume neutral
output.

The integrated regression leaves both Windows widths at **223/234** CTests,
with the same eleven registered legacy failures and no new one. T48-focused
Win32 tests and self-tests pass. The existing OpenNT16 target links the same
shared source into a valid MZ executable. The artifact hashes are recorded in
the [S6 closure](../proposals/m2/t48-sound-effects-and-channel-handlers.md#s6-closure-square-two-queue-dispatcher).
