# M2 source-order recovery plan: T21–T49

This replaces the oversized historical T21 package. Each task is a bounded source-order and call-graph responsibility; planned task identifiers become active only at individual admission.

| T | Responsibility | ROM lines | Node count |
| --- | --- | ---: | ---: |
| T21 | Boot and cold initialization (including its `InitializeMemory` call-root exception) | 699–737; 2795 | 7 |
| T22 | NMI, PPU commit, input and frame timing | 743–981 | 33 |
| T23 | Title menu, world selection and demo | 982–1180 | 33 |
| T24 | Victory, terminal modes and floating scores | 1181–1385 | 25 |
| T25 | Screen routines, HUD and game text | 1386–1824 | 67 |
| T26 | Area bootstrap, pointers and headers | 1825–2794 | 102 |
| T27 | Area object parsing and large-object geometry | 2796–3990 | 157 |
| T28 | Area rendering, metatiles, attributes and block buffer | 3991–5314 | 146 |
| T29 | Game dispatcher and entry modes | 5315–5582 | 31 |
| T30 | Player control, friction, jump and swim | 5583–5900 | 49 |
| T31 | Player state, scrolling, pipes, vines and block actions | 5901–6297 | 62 |
| T32 | Fireball dispatch, active core and explosion | 6298–6408 | 11 |
| T33 | Bubbles, game timer and Warp Zone object | 6409–6729 | 38 |
| T34 | Blocks, coins, brick pieces and misc allocation | 6730–7200 | 56 |
| T35 | Powerups, vines, cannon, whirlpool and flagpole setup | 7201–7787 | 73 |
| T36 | Enemy stream, records, slots and initialization | 7788–8500 | 85 |
| T37 | Enemy groups, frenzy and special initialization | 8501–9300 | 98 |
| T38 | Normal, defeated and swimming enemy movement | 9301–10100 | 110 |
| T39 | Platforms, Bowser flame, fireworks and remaining actors | 10101–11084 | 121 |
| T40 | Shared collision, bounding boxes and movement primitives | 11085–12000 | 110 |
| T41 | Player terrain, head, foot, side and pipe collision | 12001–13000 | 136 |
| T42 | Enemy terrain, landing, stun and side collision | 13001–14000 | 111 |
| T43 | Projectile, powerup and player/enemy collision completion | 14001–14459 | 45 |
| T44 | Relative positions, offscreen bits and player/enemy OAM | 14460–14780 | 43 |
| T45 | Object OAM, sprite tables and graphics attributes | 14781–15069 | 40 |
| T46 | Sound-effect queue and square/noise handlers | 15070–15500 | 74 |
| T47 | Music engine, channel handlers and event switching | 15501–16050 | 101 |
| T48 | Music data, tables and audio-data consumers | 16051–16368 | 28 |
| T49 | Cross-route ROM equivalence and three-target certification | integration | 0 |

## Mandatory S structure

1. **S1 — node contract:** exact labels, call edges, RAM/table writes and C owner.
2. **S2 — shared-C migration:** implement only the admitted owner boundary.
3. **S3 — ROM logic-equivalence:** source branches, reads/writes, tables, call order and reachable/controlled route.
4. **S4 — operational verification:** focused tests, x86/x64 builds, DOS16 compilation, platform purity and applicable runtime route.
5. **S5 — closure:** update `NODE_PROGRESS.md`; report complete, incomplete and transferred labels; transfer every unresolved node.

## T21 admission target

T21 owns exactly `Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`,
`EndlessLoop`, and `InitializeMemory`.  The five physically adjacent NMI/PPU
nodes (`VRAM_AddrTable_Low`, `VRAM_AddrTable_High`, `VRAM_Buffer_Offset`,
`NonMaskableInterrupt`, `ScreenOff`) are held in source-order custody for T22.
No fireball or later gameplay node belongs to T21.
