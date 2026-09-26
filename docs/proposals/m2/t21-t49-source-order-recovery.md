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

## T22/S6 closure and T22/S7 migration

T22/S6 closed as a zero-credit source contract and transferred all twelve
labels to T22/S7. It established the owner, state boundary and successor
without claiming that a source map or an existing C body is ROM-equivalent.

T22/S7 is a bounded shared-C call-placement migration. It may only:

1. split neutral C-container construction from the shared `Start`/`ColdBoot`
   state root;
2. leave both platform roots with a two-boundary wait plus inert resource
   binding, without title/area initialization; and
3. invoke the existing title-bootstrap boundary from `frame_root.c` only after
   the shared NMI prologue has run for mode/task zero.

It must preserve the existing title/area implementation body for the future
owners of `InitializeGame`, `InitializeArea`, pointer loading and header
parsing. Its expected ROM-match set is empty: the migration supplies a
source-order prerequisite, then T22/S8 will audit the affected first-NMI
branches and T23/T26 will verify the subordinate title/area nodes. Focused
tests are `mysmb.reset-root-smoke`, `mysmb.local-title-bootstrap-smoke`,
`mysmb.dos16-root-smoke` and `mysmb.platform-purity`; the ROM route is a
three-NMI cold-start recorder run beginning at reset, with the first
operation-mode dispatch sampled after the NMI prologue.

### T22/S7 P1 result

The implementation adds `mysmb_game_power_on` as the neutral C-container plus
`Start`/`ColdBoot` entry, retaining `mysmb_game_initialize` only as a focused
test-fixture constructor. Win32 and DOS roots now call `power_on`; their only
remaining game-facing work before the first tick is inert data attachment.
`frame_root.c` is the sole production caller of the title bootstrap and calls
it from mode/task zero after `mysmb_frame_root_begin` has completed the NMI
prologue. The title boundary now leaves task one, matching the source
`InitializeArea` increment at that call boundary.

The direct-caller sweep found and removed the Win32 production call and both
owner-local test/recorder calls. The DOS root has no owner-local ROM data
binding in this build, so its no-data fixture branch still advances task one;
it does not add a separate DOS gameplay path. Owner-local DOS resource
composition remains an asset-composition concern and receives no false
equivalence claim here.

Focused x86 and x64 CTests passed: reset root, pre-NMI boundary, local title
bootstrap, DOS root, platform purity, and their corresponding Win32 self-test.
The OpenNT large-model DOS link produced `mysmb-dos16.exe`. The three packaged
targets are refreshed with SHA-256 values `C17F279F6FBD4CE80F16FA2B6BDC27FFD320EBD99A91117311CE3D4EE167B8B0`,
`A37CDDA2B0113BF14460B1D33E9383BD1AF13F97A1897D407743AB8E5555374D`, and
`5735F4091A519CB2A9352B8141A265529ABEA765D0D453B84277EEB48D09C5EF` for
16-bit DOS, Win32 x86, and Win32 x64 respectively.

The ignored three-NMI ROM comparison gives byte-identical x86/x64 native
traces. It still differs from the ROM in 49 CPU-RAM bytes and three PPU-mask
bytes, while CPU OAM backing, both name tables, palette, visible OAM, audio
command state and the other PPU scalars are equal on this bounded route. Thus
S7 closes with zero newly complete labels; its twelve labels transfer to a
source-branch evidence S before any conformance credit.

## T22/S8 first-NMI branch audit

T22/S7 closed its call-placement migration with zero new ROM-match labels and
transferred the same twelve labels to T22/S8. S8 owns a bounded source-branch
audit and repair of the first three cold-start NMIs. It must trace the source
order through `ScreenOff`, VRAM address-table selection and selected-buffer
clear, then account for each observed RAM/PPU difference by source owner. It
may repair only writes owned by the twelve received labels. `InitBuffer`, timer,
sprite-0, operation-tree, title and area descendants remain with their current
receivers and must be transferred rather than edited.

Its exact expected-match set is empty. The first task is to turn the existing
49-RAM-byte and three-PPU-mask-byte difference report into branch/write
evidence; it may not promote a node on visual output or a passing CTest.
Focused tests are `mysmb.reset-root-smoke`, `mysmb.boot-nmi-boundary-smoke`,
`mysmb.local-title-bootstrap-smoke`, `mysmb.dos16-root-smoke` and
`mysmb.platform-purity`. The ROM route remains reset plus three NMI samples,
with x86/x64 native-trace equality checked separately from ROM equivalence.

### T22/S8 P1 result

The three-frame route was rerun with an explicit `0:0` input script. The
earlier S7 recorder invocation held Start while sampling, so its raw-count
comparison is retained only as a call-placement observation; this controlled
route is the valid branch comparison.

`ScreenOff` was repaired in `mysmb_game_commit_display_state`: it now reads
`$0779`, applies the source `$e6` or `$1e` mask according to
`DisableScreenFlag`, stores the mirror, and only then publishes physical
PPU mask state. The focused pre-NMI test now asserts the first-NMI `$0779`,
physical mask and visible mask values.

On the controlled route, x86 and x64 native traces are byte-identical. The
ROM comparison drops from 49 CPU-RAM and three PPU-mask differences to 43
CPU-RAM differences and zero PPU-visible differences. The remaining values
are: the 6502 stack window `$01f6-$01ff`, `InitializeGame`'s `$07a2=$18`
demo-timer write, and subsequent `LoadAreaPointer` zero-page scratch values.
These are not manufactured by S8: the stack is not portable game state, and
the two executable descendants retain their registered receivers.

No node is promoted because S8 declared an empty forecast. The next bounded
evidence S must nominate `ScreenOff` explicitly before it can close that
label. Focused x86/x64 tests and platform purity pass; OpenNT links the DOS
MZ.

## T22/S9 ScreenOff evidence

T22/S8 transferred `ScreenOff` alone to T22/S9 and the other eleven labels to
T22/S10. S9 forecasts exactly one match: `ScreenOff`; its maximum result is
4 / 1,992. The proof route is reset plus three no-input NMIs. It verifies the
source `Mirror_PPU_CTRL_REG2` read, `$e6` screen-off mask, mirror store,
physical mask write, and the later mirror-to-physical write. Its evidence is
the focused pre-NMI smoke, byte-identical x86/x64 native traces, zero ROM
difference in all PPU scalars after the repair, and the three packaged targets.

### T22/S9 result

`ScreenOff` is ROM-match complete. The controlled no-input route executes its
source mirror read, `DisableScreenFlag` branch, `$e6` mask, `$0779` store and
physical PPU-mask writes. The focused smoke confirms the first-NMI state; the
ROM comparison has zero differences in every PPU scalar and x86/x64 native
traces are byte-identical. The inventory, full census, progress report and
ledger record the resulting 4 / 1,992 count.

## T22/S10 remaining NMI-root evidence

T22/S10 receives the remaining eleven labels. It starts with no completion
forecast and must separate `InitializeGame`/`LoadAreaPointer` descendants and
non-portable 6502 stack mechanics from the received root labels before any
repair or completion proposal.

## T22/S10 classification and successor boundaries

The controlled no-input cold-start comparison leaves 43 CPU-RAM bytes after
`ScreenOff` is complete. T22/S10 audited every remaining difference against
the source call sequence and separates them as follows.

| Observed state | Source owner and reason | T22/S10 disposition |
| --- | --- | --- |
| `$07a2 = $18` | `InitializeGame` explicitly writes `DemoTimer` after its shorter `InitializeMemory` call. | Evidence handoff to the existing `M2 T18 S4` receiver for `InitializeGame`; T22 must not manufacture the write. |
| `$04-$07` after title work | `LoadAreaPointer` / `GetAreaDataAddrs` scratch-pointer work is downstream of `InitializeGame`. | Evidence handoff to the existing `M2 T18 S4` receiver for `LoadAreaPointer`; no T22 edit. |
| `$00-$01` during NMI | `NonMaskableInterrupt` indexes `VRAM_AddrTable_Low` and `VRAM_AddrTable_High` and stores the selected pointer in zero page before `UpdateScreen`. | Transfer the three table labels to T22/S12; the current C consumer performs the result but does not model these source writes. |
| `$01f6-$01ff` | 6502 return-address stack bytes are produced by `JSR`, interrupt entry and `RTI`; they are not portable game state or a source label output. | Retain only as a T49 canonical-comparison exclusion candidate. Do not add emulated stack state to `mysmb_game`. |

The remaining eleven labels are therefore not one repair unit. T22/S11 receives
the seven boot labels, T22/S12 receives the three VRAM address-table labels,
and T22/S13 receives the parent `NonMaskableInterrupt` integration label.
No label is complete from this classification: x86/x64 trace equality and
unchanged visible PPU output establish only that the current route is stable.

### T22/S10 closure

T22/S10 closes at 4 / 1,992 with no new match. Its source evidence prevents
two incorrect repairs: adding `InitializeGame` state to the cold boot root,
and treating the 6502 call stack as shared C gameplay data. The ledger records
three accepted transfers. The next active package is T22/S11, limited to
`Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop` and
`InitializeMemory`.

## T22/S11 boot-root proof

T22/S11 receives exactly seven labels: `Start`, `VBlank1`, `VBlank2`,
`WBootCheck`, `ColdBoot`, `EndlessLoop` and `InitializeMemory`. It begins at
4 / 1,992 with no completion forecast and a maximum of 4 / 1,992. It must
prove the cold and warm branches instruction-by-instruction, distinguish the
two hardware vblank waits from shared game-state work, and bind a controlled
reset route to the C90 owner without importing host policy. Focused tests are
`mysmb.reset-root-smoke`, `mysmb.boot-nmi-boundary-smoke` and
`mysmb.platform-purity`; the ROM route is reset plus three no-input NMIs.

T22/S12 is pre-accepted for the three table labels and T22/S13 for the parent
NMI label, but neither is active until the current S closes.

### T22/S11 P1 boot-branch boundary test

The source uses `$07fe` for a cold clear and `$07d6` for a warm clear.
`InitializeMemory` descends from that supplied byte through page zero and
deliberately skips `$0160-$01ff`; the warm branch consequently preserves the
top-score window above `$07d6`, while the cold branch clears it. The project
owned reset-root smoke now pins both branch boundaries, the preserved stack
window and the subsequent cold-write overrides (`$07ff` and `$07a7`).

This is source-branch and shared-C test evidence only. It does not complete a
label: `Start`'s CPU setup, the two hardware vblank waits and `EndlessLoop`
need a portable timing-boundary disposition, and the seven labels still need
a controlled original-ROM route before any completion claim.
