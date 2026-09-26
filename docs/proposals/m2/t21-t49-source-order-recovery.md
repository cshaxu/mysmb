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

### T22/S11 P2 Start ordering repair

`mysmb_game_power_on` now represents `Start` alone: it clears the portable
container and records the source's physical `$2000 = $10` write while leaving
the `$2000` mirror untouched. The shared `mysmb_game_reset` remains the exact
`WBootCheck`/`ColdBoot` entry. Both composition roots invoke `power_on` before
their existing two timing boundaries and invoke `reset` only after them. They
still only perform timing, input and presentation work; neither root reads nor
writes translated RAM, PPU, palette, OAM or gameplay state.

The local title/recorder fixtures now bind inert owner-local data between the
two shared entries, then explicitly enter `reset` before their first NMI.
Focused x86 and x64 checks cover the cold/warm clear boundary, the Start
physical-register state, first-NMI boundary, DOS root, title bootstrap,
platform purity and both Windows self-tests. The controlled three-NMI trace
remains byte-identical across x86/x64 and retains zero differences in OAM,
CIRAM, palette, audio and all PPU scalars; its remaining RAM bytes have the
T22/S10 dispositions.

### T22/S11 P3 EndlessLoop timing repair

The composition roots previously performed `ColdBoot` and the first shared NMI
in one host boundary. They now return immediately after the shared reset and
perform `mysmb_game_tick` on the next boundary, matching the source's
`EndlessLoop` wait for the following VBlank. The DOS root smoke verifies two
initial VBlank boundaries, one ColdBoot-only boundary, then the first NMI and
presentation boundary. The same Win32 start function returns without ticking
on its ColdBoot boundary. No host adapter reads or changes translated game
state.

## T22/S11 closure and T22/S14 equivalence review

T22/S11 closes at 4 / 1,992 as declared: it made no after-the-fact node-credit
claim. It completed three bounded implementation parts: the cold/warm clear
boundary test, `Start → VBlank1 → VBlank2 → ColdBoot` ordering, and the
separate `EndlessLoop → next NMI` boundary. Every source change is shared C or
a timing-only composition call; platform-purity, cross-width focused tests,
controlled route comparison and the DOS16 link pass.

T22/S14 receives the same seven labels solely to independently review their
complete evidence set. It forecasts all seven matches, raising the maximum to
11 / 1,992. The review must reject any label whose source instructions,
branch conditions, writes, call order, controlled route or operational route
do not all agree. It may update the canonical inventory only after that review.

## T22/S14 boot-root equivalence result

All seven labels are ROM-match complete. The review used the source listing
and the bounded cold-start coverage to verify the following individual facts.

| Label | Source behavior and shared-C equivalent | ROM logic-equivalence evidence | Operational evidence |
| --- | --- | --- | --- |
| `Start` | CPU-only `SEI`/`CLD`/stack setup has no portable game-state analogue; its physical `$2000=$10` write is recorded by `power_on` before either host timing boundary. | Reference coverage enters `$8000`; source order and pre-reset physical-register smoke agree. | x86/x64 and DOS16 call the shared entry before the two timing boundaries; purity passes. |
| `VBlank1` | First source status polling loop is represented by the first timing-only boundary. | Reference coverage includes `$800a`; no translated RAM write occurs. | Win32 self-tests and DOS root smoke require exactly the first boundary. |
| `VBlank2` | Second source status polling loop is represented by the second timing-only boundary. | Reference coverage includes `$800d`; no translated RAM write occurs. | Win32 self-tests and DOS root smoke require exactly the second boundary. |
| `WBootCheck` | Descending six-digit test followed by `$07ff==$a5` selects `$07d6` warm or `$07fe` cold clear origin. | Source branch/read order is mirrored directly in `boot.c`. | Reset-root smoke exercises valid warm and invalid cold paths. |
| `ColdBoot` | Clear, APU reset/enable, mode/seed writes, physical `$2001=$06`, sprite/name-table initialization, screen disable and NMI enable run in `mysmb_game_reset`. | Source write/call order is reviewed against lines 721-736; controlled route has equal visible PPU/OAM/CIRAM/palette/audio output. | Focused x86/x64 tests and OpenNT DOS16 link pass. |
| `EndlessLoop` | No game work occurs after reset until the following timing boundary invokes the shared NMI tick. | Source jump at `$8057` is covered; the root now has a distinct ColdBoot-only boundary. | DOS root smoke proves reset boundary then first NMI/presentation boundary; Windows follows the same return-before-tick function. |
| `InitializeMemory` | Descending `$07xx` through `$00xx` clear retains `$0160-$01ff` and accepts each source caller's Y origin. | Source loops and `$fe`/`$d6` origins are reviewed directly. | Full RAM boundary smoke and reset-root branch smoke pass on x86/x64; shared code links with OpenNT. |

The reset-plus-three-NMI controlled comparison remains byte-identical across
x86/x64. It has zero differences in CPU OAM, CIRAM, palette, visible OAM,
audio and PPU scalar output. Its 43 remaining RAM bytes are outside these
seven labels: the 6502 stack window, `InitializeGame` state and later pointer
scratch, plus the separately received VRAM table state. The canonical
inventory, full census and progress report record the resulting 11 / 1,992
count.

## T22/S12 VRAM address-table contract

T22/S12 receives exactly `VRAM_AddrTable_Low`, `VRAM_AddrTable_High` and
`VRAM_Buffer_Offset`. It begins at 11 / 1,992 with no completion forecast and
a maximum of 11 / 1,992. It must preserve NMI's selector-to-pointer writes
into `$00/$01`, the selector-six offset branch, the selected-buffer clear and
the call order around `UpdateScreen`. It may not alter title, area or message
producers. Focused tests will cover selector values 0-18, default buffer,
selector 5, selectors 6/7 and palette/message data routes, with controlled
NMI traces and all three target builds kept separate from logic equivalence.

### T22/S12 P1 table/write migration

The shared NMI owner now contains the reviewed 19-entry low/high table and
writes the selected source pointer to `$00/$01` before consuming it. It always
clears the selected source header afterward: `$0340/$0341` only for selector
6, and `$0300/$0301` for every other selector, including selector 7. The new
project-owned smoke executes selectors 0 through 18 and checks each pointer,
address-control reset and clear branch on x86 and x64. This is an
implementation checkpoint; S12 still has no completion credit until its
controlled ROM comparison and independent label review are complete.

## T22/S12 closure and T22/S15 independent table review

T22/S12 closes at **11 / 1,992**, exactly as forecast: it adds no ROM-match credit. Its source-table migration places all 19 low/high selector entries in the shared NMI owner, stores the selected address in `$00/$01` before the consumer, selects buffer offset zero except for selector six, clears `$0340/$0341` only for selector six and clears `$0300/$0301` for every other selector. The project-owned smoke exercises selectors 0 through 18 and every clear branch. The controlled three-NMI no-input ROM route has byte-identical x86/x64 native traces and no PPU-visible difference; its remaining `$00` difference is the subsequent `RotPRandomBit` scratch write and belongs to the separately received `NonMaskableInterrupt` integration node, not to a table repair.

The three data labels transfer to T22/S15 rather than receiving premature credit. S15 is the independent review: it must use a local, ignored reference recorder with a controlled NMI breakpoint after the pointer stores and before the LFSR scratch path, compare the selected pointer and selected header clear for selectors 0 through 18, then review table bytes, selector branch, reads, writes and call order against the shared C owner. Its exact target rows are:

| ROM line | Node | Current state | S15 proof obligation |
| ---: | --- | --- | --- |
| 743 | `VRAM_AddrTable_Low` | mapped; source migration complete | Every selector's low byte and `$00` write agree at the controlled NMI point. |
| 752 | `VRAM_AddrTable_High` | mapped; source migration complete | Every selector's high byte and `$01` write agree at the controlled NMI point. |
| 761 | `VRAM_Buffer_Offset` | mapped; source migration complete | Selector-six offset and each selected header clear agree after `UpdateScreen`. |

T22/S15 begins at **11 / 1,992**, forecasts exactly these three matches and has a maximum of **14 / 1,992**. Its ROM-equivalence track is the controlled NMI recorder plus source branch/write/call-order review. Its operational track is `mysmb.vram-address-table-smoke`, `mysmb.boot-nmi-boundary-smoke`, `mysmb.platform-purity`, x86/x64 builds and trace equality, the OpenNT DOS16 link, and the three packaged executables. `NonMaskableInterrupt` and `RotPRandomBit` remain outside S15 and retain their current receiver.

## T22/S15 VRAM address-table equivalence result

All three table labels are **ROM-match complete**, raising conformance from
**11 / 1,992** to **14 / 1,992**.  The independent local ROM probe stops at the
NMI entry, injects each selector with inert zero-length buffer data, and samples
after the original pointer stores and selected-header clear.  For selectors
0–18 it observed all 19 expected low bytes, all 19 expected high bytes, all 19
selected clear bases, and pointer-before-clear order in every run.  Selector 6
alone cleared `$0340/$0341`; every other selector cleared `$0300/$0301`.

The shared C smoke independently exercises the same 19 selector values and
branches.  x86 and x64 focused tests pass, platform purity passes, the OpenNT
DOS16 link succeeds, and the three refreshed artifacts have SHA-256 values
`B799A75BDF54D32BA3F0231FC7D92FEF0335AA8623FF215C1E6D4E6A0C3AE7B5`,
`AC64B35175FF380B2EC2D51D86C2B03A7176A9304BF04E5D2BD19C0B7F76AE49`, and
`200AED0EBCE16C723AEAA1D05B260F92AA691C306029D03B8E255CA8D7B97CBA` for
DOS16, Win32 x86, and Win32 x64.  The ignored probe, ROM input and raw output
remain below `build/`; no ROM-derived material is tracked.

## T22/S13 NMI root integration audit

T22/S13 receives `NonMaskableInterrupt` only.  It begins at **14 / 1,992**,
forecasts no new match and has a maximum of **14 / 1,992**.  It must audit the
parent's exact call order around the now-complete table consumer, then identify
every still-open direct NMI descendant and its current ledger receiver before
any cross-owner edit.  It may repair only the parent integration body; timer,
LFSR, sprite-zero, shuffle, pause and operation-mode leaves cannot be absorbed
into the parent or platform layer.  Its ROM-equivalence route is the reset plus
controlled NMI probe and the existing no-input three-NMI comparison.  Its
operational track is `mysmb.boot-nmi-boundary-smoke`,
`mysmb.vram-address-table-smoke`, `mysmb.platform-purity`, x86/x64 route
equality, DOS16 link and the three artifacts.  The required exit is an exact
source-order dependency map and accepted successor transfers for unresolved
leaves; no parent-node credit is permitted without the whole parent contract.

## T22/S13 parent audit, source-order child recovery and closure

S13 audited the complete NMI body at ROM lines 764–981.  It confirms that
`mysmb_frame_root_begin` is the shared parent composition point and that both
platforms remain outside game state.  It also found a governance error: after
the initial all-node census, 28 direct NMI descendants had remained in T24/S2
custody even though the approved source-order plan assigns the NMI slice to
T22.  The parent cannot be certified while those child branches are elsewhere.

S13 closes with no new match at **14 / 1,992** and transfers the parent to
T22/S22 for final independent integration review.  The 28 descendants transfer
directly from T24/S2, under the owner-approved source-order plan, to these
accepted sequential receivers:

| Next S | Source-order responsibility | Exact labels |
| --- | --- | --- |
| S16 | selected VRAM buffer header clear | `InitBuffer` |
| S17 | pause call and all pause branches | `PauseRoutine`, `ChkPauseTimer`, `ChkStart`, `ClrPauseTimer`, `SetPause`, `ExitPause` |
| S18 | timer bank then LFSR continuation | `DecTimers`, `DecTimersLoop`, `SkipExpTimer`, `NoDecTimers`, `PauseSkip`, `RotPRandomBit` |
| S19 | sprite-0 split and OAM-offscreen loop | `Sprite0Clr`, `Sprite0Hit`, `HBlankDelay`, `SkipSprite0`, `SkipMainOper`, `MoveAllSpritesOffscreen`, `MoveSpritesOffscreen`, `SprInitLoop` |
| S20 | sprite-offset shuffle | `SpriteShuffler`, `ShuffleLoop`, `StrSprOffset`, `NextSprOffset`, `SetAmtOffset`, `SetMiscOffset` |
| S21 | mode dispatch at the tail of NMI | `OperModeExecutionTree` |
| S22 | parent integration review after direct children | `NonMaskableInterrupt` |

Each receiver must be admitted separately with a fresh exact scope, forecast and
ROM route.  The transfers do not grant conformance credit.  T22/S16 begins at
**14 / 1,992**, has one scoped incomplete label, forecasts no match and has a
maximum of **14 / 1,992**.  It must establish the exact `InitBuffer` branch
and only then nominate a separate proof S; its focused checks are
`mysmb.vram-address-table-smoke`, `mysmb.boot-nmi-boundary-smoke` and
`mysmb.platform-purity`, while its ROM route is the controlled selector probe
with the selected header initialized to a nonzero sentinel.

## T22/S16 InitBuffer source contract and T22/S23 proof transfer

S16 closes at **14 / 1,992**, as forecast, with no new node credit.  It
reviewed the exact sequence after `UpdateScreen`: reload `$0773`, choose
`VRAM_Buffer_Offset[1]` only when the selector is exactly six, clear the
selected offset byte then the selected data byte, and only then clear `$0773`.
The shared C owner preserves that order.  Selector seven transfers buffer two
but takes the non-six clear path, so it clears `$0300/$0301`; this is covered by
the 19-selector project smoke and the controlled ROM sentinel probe.

`InitBuffer` transfers to T22/S23 for independent evidence.  S23 begins at
**14 / 1,992**, forecasts exactly `InitBuffer`, and has a maximum of
**15 / 1,992**.  It must compare the ROM sentinel probe for selector six and
selector seven with the shared C smoke, review the source branch/read/write
order, and repeat x86/x64 tests, DOS16 build, platform-purity check and the
three target artifact package.

## T22/S23 InitBuffer equivalence result and T22/S17 admission

`InitBuffer` is **ROM-match complete**, raising conformance from **14 / 1,992**
to **15 / 1,992**.  The independent ROM sentinel probe observed selector six
write the `$41/$03` buffer-two pointer, then clear `$0340/$0341`; selector
seven wrote the same pointer, then clear `$0300/$0301`.  Both paths observed
the pointer write before the clear.  The shared C smoke covers all selectors
and asserts the same two cases.  Focused x86/x64 tests and platform purity
pass; the refreshed target artifacts retain SHA-256 values
`B799A75BDF54D32BA3F0231FC7D92FEF0335AA8623FF215C1E6D4E6A0C3AE7B5`,
`AC64B35175FF380B2EC2D51D86C2B03A7176A9304BF04E5D2BD19C0B7F76AE49`, and
`200AED0EBCE16C723AEAA1D05B260F92AA691C306029D03B8E255CA8D7B97CBA`.

T22/S17 now begins the next direct NMI call in source execution order,
`PauseRoutine`.  Its six scoped labels are `PauseRoutine`, `ChkPauseTimer`,
`ChkStart`, `ClrPauseTimer`, `SetPause`, and `ExitPause`.  It begins at
**15 / 1,992**, forecasts no match and has a maximum of **15 / 1,992**.  It
must map the operating-mode gates, timer branch, Start debounce, status-bit
update and pause audio queue before any repair or independent proof proposal.

## T22/S17 pause source contract and T22/S24 independent proof admission

S17 closes at **15 / 1,992** with no new node credit, exactly as forecast.  It
mapped the six-label pause subtree at ROM lines 876–907 to the single shared
owner `mysmb_frame_root_pause_step`; no platform code reads or writes the
pause RAM.  The source order is: accept victory mode or game mode/task three;
when `GamePauseTimer` is nonzero decrement it and return; otherwise inspect the
already-latched Start bit; reject a pending bit-seven debounce; on a fresh
Start write `$2b`, queue `GamePauseStatus + 1`, then write `(status ^ 1) | $80`;
on no Start write `status & $7f`; every other route returns without a pause
write.  The native return value is only the source status bit zero consumed by
the subsequent NMI branches, not an added game-state transition.

An ignored original-ROM NMI-entry probe sampled the original RTI boundary for
six controlled cases: non-game mode exit, game-mode non-task-three exit,
nonzero timer decrement, no-Start bit-seven clear, first Start toggle/queue,
and bit-seven Start debounce.  The relevant results were respectively
`$0776/$0777 = 81/19, 81/19, 01/29, 01/00, 81/2b, 81/00`; fresh Start alone
left pause audio queue `$00fa = 01`.  The project pause smoke and the
x86/x64 focused tests also pass, but this source contract deliberately claims
no equivalence credit.

All six labels transfer to **T22/S24**, the independent proof S.  S24 begins
at **15 / 1,992**, scopes exactly `PauseRoutine`, `ChkPauseTimer`, `ChkStart`,
`ClrPauseTimer`, `SetPause`, and `ExitPause`, forecasts those same six matches,
and has a maximum of **21 / 1,992**.  It must independently compare every
source branch, RAM read/write, queue write, and NMI call position against the
controlled ROM outputs, then run the focused cross-width tests, DOS16 build,
platform-purity check and three-target artifact package.  Any failed label
remains incomplete and transfers to a later repair S; no partial result may
promote the parent NMI node.

## T22/S24 pause equivalence result and T22/S18 admission

All six pause labels are **ROM-match complete**, raising conformance from **15 /
1,992** to **21 / 1,992**.  S24 independently reviewed the source mode gate,
timer early return, Start read, bit-seven debounce return, timer/audio/status
writes, clear-mask write and return edges against `mysmb_frame_root_pause_step`.
A freshly built ignored original-ROM probe injected six states at the NMI entry
and sampled the RTI boundary.  Its six results match the reviewed native cases:
mode exit preserves `$0776/$0777 = $81/$19`; task exit preserves the same
values; timer decrements `$2a` to `$29`; no Start changes `$81` to `$01`; fresh
Start writes `$81/$2b` and `$00fa = $01`; and a bit-seven Start keeps `$81/$00`.
The native pause smoke covers the same six cases on x86 and x64.  Focused
NMI/pause/purity tests pass, the OpenNT DOS16 build links, and the refreshed
artifacts have SHA-256 values `B799A75BDF54D32BA3F0231FC7D92FEF0335AA8623FF215C1E6D4E6A0C3AE7B5`,
`AC64B35175FF380B2EC2D51D86C2B03A7176A9304BF04E5D2BD19C0B7F76AE49`, and
`200AED0EBCE16C723AEAA1D05B260F92AA691C306029D03B8E255CA8D7B97CBA` for
DOS16, Win32 x86 and Win32 x64.

T22/S18 is now active in source order for `DecTimers`, `DecTimersLoop`,
`SkipExpTimer`, `NoDecTimers`, `PauseSkip`, and `RotPRandomBit`.  It begins at
**21 / 1,992**, forecasts no completion and has a maximum of **21 / 1,992**.
It may only map the NMI timer-bank and LFSR control/read/write order, then
transfer the six nodes to a separately admitted proof or repair S.

## T22/S18 timer/LFSR source contract and T22/S25 proof admission

S18 closes at **21 / 1,992** with no node credit.  Its source audit found and repaired one control-order discrepancy: ROM `DecTimersLoop` visits timer offsets from `$14` or `$23` down to zero, while C had visited them upward. `mysmb_game_tick_player_timers` now uses the descending order. The new shared timer smoke covers master-control hold, a frame-timer-only decrement, and interval rollover that selects all `$24` timers; it passes on x86/x64 with the existing LFSR, NMI-boundary and purity checks. The shared source builds for DOS16 and all three artifacts are refreshed.

All six labels transfer to **T22/S25** for independent controlled-ROM proof. S25 begins at **21 / 1,992**, forecasts all six labels and has a maximum of **27 / 1,992**.
