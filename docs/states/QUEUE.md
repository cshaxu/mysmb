# Queue

## First Priority - M2 Source-Order Recovery

The owner-approved [source-order recovery plan](../proposals/m2/t21-t49-source-order-recovery.md) is the sole authority for the remaining M2 implementation sequence. Historical numeric records are immutable: `M2 T23` remains Player route and `M2 T24` remains the node-audit/custody record. T25 through T29 have completed their admitted source-order chains. T30/S1 is closed at 433 / 1,992. T30/S2 is closed at 435 / 1,992. T30/S3 is closed at 442 / 1,992; T30/S4 is closed at 452 / 1,992; T30/S5 is closed at 455 / 1,992; T30/S6 is closed at 459 / 1,992; T30/S7 is closed at 460 / 1,992; T30/S8 is closed at 468 / 1,992; T30/S9 is closed at 476 / 1,992; T30/S10 is closed at 480 / 1,992 (six new matches, two prior claims revoked); T30/S11 restores DecodeAreaData at 481 / 1,992; T30/S12 restores DrawPipe at 482 / 1,992; T30/S13 closes the shared block-address chain and restores SetInitNTHigh at 484 / 1,992.

The plan retains boot as `T21` and NMI as `T22`, then assigns future source slices continuously through `T51`. This queue contains candidates only; the plan's identifiers become active only with an approved packet.

T29 is closed at 422 / 1,992. T30/S1 completed the three-label `EndlessRope -> DrawRope` chain. T30/S2 completed `CoinMetatileData -> RowOfCoins`; T30/S3 completed `C_ObjectRow -> ColObj`, and later T30 labels remain dependencies.

Every future M2 admission follows the [chain-based S delivery rule](../rules/EXECUTION.md#m2-chain-based-s-delivery): nodes remain individually tracked, while one S delivers a bounded contiguous call/data chain with one shared ROM route and one three-target validation pass.  The fixed five-stage S pattern is retired for future admissions; historical S records remain evidence only.

## Current-chain transition

T30 is closed after its [cross-chain audit](../history/M2-T30-area-object-rendering.md#t30-closure),
with 111 of its 146 planned nodes complete and 35 accepted incomplete
consumer transfers. Five earlier-node corrections also remain complete.
T31 and T32 are closed. T32 proves its 48 received caller/data nodes at
676 / 1,992, with eleven integrated routes retaining child/output failures.
T33 is closed with all 63 received movement/physics nodes proven at 739 / 1,992.
T34 is closed with all eleven fireball dispatch/core nodes proven at 750 / 1,992.
Its cross-chain review retains the existing graphics-child failures.
T35 S1 closes eight bubble nodes at 758 / 1,992. Timer S2 closes four caller nodes at 762 / 1,992; S3 jumpspring closes seven data/state/caller nodes at 769 / 1,992; S4 closes three vine initialization/data nodes at 772 / 1,992; T35 is closed. The next source slice starts with VineObjectHandler at line 6730.
T36 S1 closes six vine actor caller nodes at 778 / 1,992; S2 closes ten hammer lifecycle nodes at 788 / 1,992. S3 closes six coin allocation caller nodes at 794 / 1,992; S4 closes six misc lifetime nodes at 800 / 1,992; S5 closes nine score/HUD nodes at 809 / 1,992; S6 closes four initialization nodes at 813 / 1,992. T36 is closed: 41 new plus 14 retained matches; PowerUpObjHandler stays with the next-slice successors.
[The T36 plan](../history/M2-T36-misc-object-chains.md) groups 41 incomplete labels
into six chains, retains fourteen cannon matches, and keeps the trailing
PowerUpObjHandler with its next-slice successors.
T37 S1 closes six power-up actor nodes at 819 / 1,992; S2 closes thirteen head-hit/position nodes at 832 / 1,992; S3 closes eleven block content/lookup nodes at 843 / 1,992; S4 closes four local shatter/top-coin/chunk nodes at 847 / 1,992; S5 closes five block lifetime nodes at 852 / 1,992; S6 closes three replacement nodes at 855 / 1,992; S7 closes six horizontal nodes at 861 / 1,992; S8 closes eleven new and three retained adapter nodes at 872; S9 closes twelve gravity nodes at 884; T37 is closed after its final cross-chain review.
[The T37 plan](../history/M2-T37-power-up-block-movement.md) assigns all 74
labels to nine source-order chains: 71 expected new and three retained,
maximum 884. S1-S9 and T37 are closed: 750/844 final actual comparisons match; 94 prior child failures remain unchanged. [T38](../proposals/m2/t38-enemy-stream-initialization.md) is admitted from EnemiesAndLoopsCore: 91 exact targets in seven chains. S1 closes nineteen loop/flag/frenzy nodes at 903. S2 closes nineteen parser nodes at 922. S3 closes three initializer-vector nodes at 925. S4 closes all 23 common initializer nodes at 948. S5 closes thirteen Lakitu/Spiny nodes at 961. S6 closes all seven firebar/duplicate nodes at 968. S7 flying-fish initialization is next and not yet admitted. T38 scope is now 94; later Bowser work reuses the three dependency nodes without duplicate credit.
The six unfinished enemy callers remain with T19 S5. Enemy-data and loopback obligations
remain with their accepted T19 S5 receiver until source admission.

Every later M2 admission uses the source-order chain table defined by the
recovery plan; it may not revive the retired fixed five-stage pattern. This
changes delivery granularity only: node custody, source order, dual
verification, tracker rows, and three-target P delivery remain mandatory.
## M1 Candidates

1. [Win32 and 16-bit-compatible platform foundation](../proposals/m1-win32-platform-foundation.md) — closed in M1.
2. [Static-C source pipeline](../proposals/m1-source-corpus-and-local-toolchain.md) — closed in M1.
3. [Native title-scene runtime](../proposals/m1-native-title-runtime.md) — closed in M1.
4. [Title-scene oracle](../proposals/m1-title-oracle.md) — closed in M1; title-route equality transfers to M2.

## M2 Candidates

1. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — complete direct-ROM PRG analysis and architecture inventory closed in M2 T1.
2. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — title progression, deterministic input, and the first transition checkpoint.
3. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — area bootstrap and background/object command route.
4. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — player route and collision.
5. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — object route: enemies, items, projectiles, timer, score, and power state.
6. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — death, restart, warp, continue, and completion mode routes.
7. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — neutral audio command route.
8. [Native logic and oracle](../proposals/m2-native-logic-and-oracle.md) — end-to-end playable-route oracle and Win32 validation.
9. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — active T9 output-ownership ledger and local frame-oracle contract; prior M2 closure claims are under correction.
10. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — translated background output; closed in M2 T10.
11. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — translated OAM output; closed in M2 T11.
12. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — Win32 native frame consumer and complete controller mapping; closed in M2 T12.
13. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — frame-indexed owner-local oracle; active in M2 T13.
14. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — cross-width route proof.
15. [M2 reopened frame equivalence](../proposals/m2-reopened-frame-equivalence.md) — closure audit.

## M2 Structural-Recovery Candidates

The historical structural-recovery entries below are retained by their original task records and are not candidates for numeric reuse. Future execution follows the source-order recovery plan above; the retained [structural recovery coverage](../proposals/m2-rom-structural-recovery.md) remains its source-map reference. The queue order is: Title/menu/demo; Victory/terminal; Screen/HUD/text; Area bootstrap; parser; renderer; dispatcher; player control; player state; fireball; bubbles/timer/Warp; blocks; powerups and setup; enemy stream; enemy groups; enemy movement; remaining actors; shared collision; player terrain; enemy terrain; projectile/powerup collision; relative/OAM; object OAM; sound effects; music engine; music data; cross-route certification.

`M2 T24 S2` remains the accepted custody receiver for unresolved nodes until an admitted source-order S accepts each exact label. It does not consume or reserve future numeric task identifiers.

## M3 Candidates

1. [Presentation adapters](../proposals/m3-presentation-adapters.md) — neutral render-command seam and deterministic core ownership.
2. [Presentation adapters](../proposals/m3-presentation-adapters.md) — Win32 consumption of neutral tile-row and actor commands.
3. [Presentation adapters](../proposals/m3-presentation-adapters.md) — deterministic 80x25 colored-object adapter.
4. [Presentation adapters](../proposals/m3-presentation-adapters.md) — DOS VGA indexed-frame adapter and OpenNT compile coverage.
5. [Presentation adapters](../proposals/m3-presentation-adapters.md) — real-mode DOS composition root, hardware hooks, and local MZ link.
6. [Presentation adapters](../proposals/m3-presentation-adapters.md) — reviewed DOS runtime recovery and MZ link evidence.
7. [Presentation adapters](../proposals/m3-presentation-adapters.md) — DOS BIOS input/timing and VGA/text hardware hooks.
8. [Presentation adapters](../proposals/m3-presentation-adapters.md) — bounded DOS runtime verification and pacing evidence.

## M4 Candidates

1. [486SX qualification](../design/ROADMAP.md) — physical host protocol and measured DOS/VGA route evidence.
2. [486SX qualification](../design/ROADMAP.md) — execute the physical-host protocol and record measured route evidence.
