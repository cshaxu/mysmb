# Queue

## First Priority - M2 Source-Order Recovery

The owner-approved [source-order recovery plan](../proposals/m2/t21-t49-source-order-recovery.md) is the sole authority for the remaining M2 implementation sequence. Historical numeric records are immutable: `M2 T23` remains Player route and `M2 T24` remains the node-audit/custody record. T25 through T29 have completed their admitted source-order chains. T30/S1 is closed at 433 / 1,992. T30/S2 is closed at 435 / 1,992. T30/S3 is closed at 442 / 1,992; T30/S4 is closed at 452 / 1,992; T30/S5 is closed at 455 / 1,992; T30/S6 is closed at 459 / 1,992; T30/S7 is closed at 460 / 1,992; T30/S8 is closed at 468 / 1,992; T30/S9 is closed at 476 / 1,992; T30/S10 is closed at 480 / 1,992 (six new matches, two prior claims revoked); T30/S11 restores DecodeAreaData at 481 / 1,992; T30/S12 restores DrawPipe at 482 / 1,992; T30/S13 closes the shared block-address chain and restores SetInitNTHigh at 484 / 1,992.

The plan retains boot as `T21` and NMI as `T22`, then assigns future source slices continuously through `T51`. This queue contains candidates only; the plan's identifiers become active only with an approved packet.

T29 is closed at 422 / 1,992. T30/S1 completed the three-label `EndlessRope -> DrawRope` chain. T30/S2 completed `CoinMetatileData -> RowOfCoins`; T30/S3 completed `C_ObjectRow -> ColObj`, and later T30 labels remain dependencies.

Every future M2 admission follows the [chain-based S delivery rule](../rules/EXECUTION.md#m2-chain-based-s-delivery): nodes remain individually tracked, while one S delivers a bounded contiguous call/data chain with one shared ROM route and one three-target validation pass.  The fixed five-stage S pattern is retired for future admissions; historical S records remain evidence only.

## Current-chain transition

Before any new numeric M2 repair task, the active
[current-equivalence re-audit](../proposals/m2/current-equivalence-reaudit.md)
classifies the present build in original ROM source order. Its confirmed
mismatches become ordered but unnumbered repair candidates. This prevents
historical diagnostic debt from being selected piecemeal and preserves numeric
T allocation for accepted implementation work.

1. [A2 NMI-prefix state-handoff repair](../proposals/m2/a2-nmi-prefix-repair-candidate.md)
   — confirmed shared `frame_root.c` chain for source scratch `$00` and
   d7-clear `$2000` timing before operation-mode dispatch. This is an
   unnumbered candidate, not an admitted task.

2. [A6 title-menu timer-gate repair](../proposals/m2/a6-title-menu-order-repair-candidate.md)
   — confirmed shared `title_modes.c` `ChkSelect -> ChkWorldSel` ordering
   mismatch when the demo timer is zero and world-select B is latched. This is
   an unnumbered candidate, not an admitted task.

3. [A7 Floatey timer-gate repair](../proposals/m2/a7-floatey-timer-gate-repair-candidate.md)
   — confirmed shared `objects.c` `DecNumTimer -> LoadNumTiles -> AddToScore`
   timing mismatch: current C checks `$2b` before decrement while the ROM
   checks it after decrement. This is an unnumbered candidate, not an admitted
   task.

[T42](../history/M2-T42-shared-collision-and-platforms.md#t42-closure) is closed:
98/98 scoped nodes, total1,382/1,992. Its nine chains end at
GetEnemyBoundBoxOfsArg. Final actual actor matches21,544/29,434; unresolved
children keep their ledger receivers and original source-order slices.

[T43](../history/M2-T43-terrain-and-bounding-boxes.md#t43-closure) is closed: 150/150 scoped nodes, 136 new and 14 retained/rechecked completions, ending at 1,517 / 1,992. Its S3 review revoked the task-external historical KillEnemies claim; that node remains assigned to M2 T29 S8 and is not a T43 scope debt. The next unadmitted source slice begins BlockBufferChk_Enemy at13023 with109 nodes.

[T44](../history/M2-T44-block-buffer-and-object-graphics.md#t44-closure) is closed: 109/109 scoped labels, 107 new and two retained/rechecked completions, ending at 1,624 / 1,992. T45 is the next unadmitted source-order candidate, beginning at `CheckToMirrorLakitu` after the `EggExc` boundary.

[T45 object OAM tail and graphics](../history/M2-T45-object-oam-tail-and-graphics.md#t45-closure) is closed: 45/45 scoped labels match, ending at 1,669 / 1,992. [T46 player graphics control](../proposals/m2/t46-player-graphics-control.md) is closed at 1,709 / 1,992: all 43 scoped labels match, including three retained/rechecked and 40 new across S1–S4. [T47 object position and sprite output](../history/M2-T47-object-position-and-sprite-output.md#t47-closure) is closed: all 40 scoped labels match, ending at 1,749 / 1,992. [T48 sound effects](../history/M2-T48-sound-effects-and-channel-handlers.md#t48-closure) is closed: all 74 scoped labels match, ending at 1,823 / 1,992. [T49 music/channel handlers](../proposals/m2/t49-music-engine-and-channel-handlers.md#s9-closure-music-header-table-and-records) is closed at 1,924 / 1,992. [T50 music data and audio consumers](../proposals/m2/t50-music-data-and-audio-consumers.md#s2-closure-music-lookup-and-envelope-tables) is closed at 1,952 / 1,992 after all 28 scoped music-data and audio-consumer labels match. T51 is active for 40 residual source-order nodes before its final cross-route certification.

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
