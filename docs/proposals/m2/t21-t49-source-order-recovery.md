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
No fireball or later gameplay node belongs to T21. T21 closure transferred its seven root labels into T22 deferred custody because current startup invokes later title bootstrap before the first shared NMI; T22 owns that integrated first-NMI repair and re-admission boundary. Historical T22 S1–S5 records remain immutable, so the source-order intake uses the next available T22 slot, S6.

## T22/S6 first-NMI source contract

T22/S6 receives twelve labels in one dependency chain. The original path is
`Start → VBlank1 → VBlank2 → WBootCheck → ColdBoot → EndlessLoop`; the final
`WritePPUReg1` enables NMI and no title/area initialization occurs on that
path. The first NMI then owns `NonMaskableInterrupt`, including `ScreenOff`,
OAM DMA, the two VRAM-address tables, `VRAM_Buffer_Offset`, update/clear of
the selected buffer, input/timer work and only then the operation-mode tree.

| Node group | Source-owned order | Current native owner | T22/S6 finding |
| --- | --- | --- | --- |
| `Start`, `VBlank1`, `VBlank2` | CPU/PPU setup, then two no-RAM-write status polls | Win32/DOS timing roots and `boot.c` | The two-boundary gate is operationally shared, but must remain before all later game work. |
| `WBootCheck`, `ColdBoot`, `InitializeMemory`, `EndlessLoop` | score/marker branch, RAM clear, cold writes, then idle until NMI | `boot.c` | `mysmb_game_reset` is the examined shared owner; construction must not append later ROM-node writes before NMI. |
| `NonMaskableInterrupt`, `ScreenOff` | mask/scroll/OAM/VRAM/input/timer prologue before operation dispatch | `frame_root.c` | `mysmb_frame_root_begin` is the shared destination for the first-NMI prologue. |
| `VRAM_AddrTable_Low`, `VRAM_AddrTable_High`, `VRAM_Buffer_Offset` | `$0773` selects pointer; buffer is submitted then the selected header is cleared | `frame_root.c` | `mysmb_game_commit_vram_buffer` must remain inside the NMI root and never be called by host bootstrap. |

The audit found one concrete pre-NMI violation: both host roots call
`mysmb_game_initialize`, bind sources and invoke `mysmb_game_begin_title_bootstrap`
before their first shared tick. That bootstrap performs `InitializeGame`/area
work which source executes only after the NMI prologue enters the title-mode
tree. T22/S7 must move that work to the shared first-NMI path, retain host
resource binding as inert data attachment, and test the exact pre-NMI state.
No label is complete from this contract.
