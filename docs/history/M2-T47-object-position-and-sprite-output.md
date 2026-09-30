# M2 T47: object position, offscreen bits and sprite output

## T47 closure

All **40 source-order labels** from `ExPlyrAt` through `SetHFAt` are
ROM-match complete across S1–S5. The verified numerator advances
**1,709 → 1,749 / 1,992**. No T47 label is deferred. The next source
label, `SoundEngine`, remains open for the subsequent source-order
candidate.

| Chain | Original route and node proof | Native comparisons |
| --- | --- | ---: |
| S1: player attribute exit (1) | Eight original `ExPlyrAt` entries, including OAM-change and no-change paths | 16, zero differences |
| S2: relative object positions (9) | Twelve natural/edge player, bubble, fireball, misc, enemy and block routes; 30 child calls | 60, zero differences |
| S3: player offscreen entry (1) | Natural and edge GameEngine routes; 16 child calls; downstream scratch difference explicitly transferred to S4 | 32 entry/result comparisons, zero differences |
| S4: shared offscreen bits (26) | Twelve natural/edge actor routes, 32 child calls, six original ROM data tables; closes S3 scratch difference | 64 full RAM/OAM comparisons, zero differences |
| S5: two-sprite row writer (3) | Player, ordinary enemy and block routes; 38 child calls; both flip branches | 76 full RAM/OAM and X/Y comparisons, zero differences |

The [T47 proposal](../proposals/m2/t47-object-position-and-sprite-output.md)
records every node's source PC, control/read/write disposition and
per-S evidence. Original-ROM records and generated diagnostics stay in
ignored `build/`. All translated behavior, scratch RAM and OAM writes
reside in shared C game code. DOS16 and Win32 adapters only consume the
resulting frame. The separate operational regression built all three
targets; x86 and x64 each passed 222/233 full CTests with the same 11
prior baseline failures, and both Win32 self-tests passed. DOS16
linked. The three owner-authorized executable hashes are in the
[S5 closure](../proposals/m2/t47-object-position-and-sprite-output.md#s5-closure-shared-sprite-row-writer).
