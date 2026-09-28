# M2 source-order recovery plan: T21–T51

This replaces the oversized historical T21 package. Each task is a bounded source-order and call-graph responsibility; planned task identifiers become active only at individual admission.

## Binding delivery model for every planned task

Every future admission in this plan, from T21 through T51, uses the binding
[M2 chain-based S delivery rule](../../rules/EXECUTION.md#m2-chain-based-s-delivery).
An S is one bounded contiguous control/data chain with a common shared-game
owner and one reproducible ROM route.  It performs its source mapping, any
needed C repair, ROM logic-equivalence comparison, and operational proof in
the same delivery.  A chain may include adjacent data, loops, and leaves; it
must split at an unadmitted dependency, owner boundary, or a branch family
requiring a different ROM route.

Each label remains independently listed in the admission JSON, proposal,
ledger, and progress tracker.  ROM-equivalence verification remains separate
from operational verification.  The latter runs focused tests, Win32 x86/x64,
DOS16, platform purity, and the required three executable artifacts once per
implementation P; T closure adds a cross-chain regression matrix.  Older
single-label or fixed-stage S descriptions elsewhere are retained only as
historical evidence and cannot govern a new admission.

Every remaining task also uses the rule's chain admission and closure reports.
Before each S, record its exact source-ordered labels, entry/exit, shared-game
owner, dependency receipts, expected-match subset, and separate ROM-logic and
operational plans. At closure, record every label as complete, deferred with
the failed track, or transferred by exact name before moving to the next source
chain. Adjacent data, loop and helper labels remain with their consumer S when
one route proves them; a separate S requires an owner, dependency, or ROM-route
boundary.

| T | Responsibility | ROM lines | Node count |
| --- | --- | ---: | ---: |
| T21 | Boot and cold initialization (including its `InitializeMemory` call-root exception) | 699–737; 2795 | 7 |
| T22 | NMI, PPU commit, input and frame timing | 743–981 | 33 |
| T25 | Title menu, world selection and demo | 982–1133 | 26 |
| T26 | Victory, terminal modes and floating scores | 1137–1385 | 32 |
| T27 | Screen routines, HUD and game text | 1386–1824 | 67 |
| T28 | Area bootstrap, pointers and headers | 1825–2794 | 102 |
| T29 | Area object parsing and large-object geometry | 2796–3990 | 157 |
| T30 | Area rendering, metatiles, attributes and block buffer | 3991–5314 | 146 |
| T31 | Game dispatcher and entry modes | 5315–5582 | 31 |
| T32 | Player control and mode transitions; movement entry belongs with its next-chain successors | 5583–5900 | 49 |
| T33 | Player state, scrolling, pipes, vines and block actions | 5901–6297 | 62 |
| T34 | Fireball dispatch, active core and explosion | 6298–6408 | 11 |
| T35 | Bubbles, game timer and Warp Zone object | 6409–6729 | 38 |
| T36 | Blocks, coins, brick pieces and misc allocation | 6730–7200 | 56 |
| T37 | Power-up actor tail, blocks and movement/gravity primitives; receives T36 PowerUpObjHandler boundary exception | 7201–7787; entry 7184 | 74 |
| T38 | Enemy stream, records, slots and initialization; complete flying-fish tail | 7788–8528; loop and duplicate dependencies below | 88 + 6 dependencies |
| T39 | Special initialization and actor dispatch; ends EraseEnemyObject | 8529–9211; flame timer dependency | 83 + 3 dependencies |
| T40 | Complete Podoboo/Hammer Bro, normal, defeated and swimming movement | 9212–10100 | 122 |
| T41 | Platforms, Bowser flame, fireworks and remaining actors | 10101–11084 | 121 |
| T42 | Shared collision, bounding boxes and movement primitives | 11085–12000 | 110 |
| T43 | Player terrain, head, foot, side and pipe collision | 12001–13000 | 136 |
| T44 | Enemy terrain, landing, stun and side collision | 13001–14000 | 111 |
| T45 | Projectile, powerup and player/enemy collision completion | 14001–14459 | 45 |
| T46 | Relative positions, offscreen bits and player/enemy OAM | 14460–14780 | 43 |
| T47 | Object OAM, sprite tables and graphics attributes | 14781–15069 | 40 |
| T48 | Sound-effect queue and square/noise handlers | 15070–15500 | 74 |
| T49 | Music engine, channel handlers and event switching | 15501–16050 | 101 |
| T50 | Music data, tables and audio-data consumers | 16051–16368 | 28 |
| T51 | Cross-route ROM equivalence and three-target certification | integration | 0 |

## Identifier reconciliation (M2 Td S7)

Historical `M2 T23` is the Player-route record and historical `M2 T24` is the
node-audit/custody record. They are immutable evidence, not available source
order slots. The previous draft incorrectly assigned those same identifiers to
Title and Victory. `M2 Td S7` preserves every historical task, subtask,
receiver, transfer and conformance status, reserves no duplicate identifiers,
and shifts only future source-order slices by two: Title begins at `T25`, and
the final certification task is `T51`.

T25 through T28 are closed historical source-order records. The next
admissible source-order implementation task is `M2 T29`, area parser and
large-object geometry. Its S breakdown must be admitted against the exact
inventory labels before any game-code change.

## Mandatory chain delivery structure

T38 admission corrects the old line-8500 split inside InitFlyingCheepCheep:
D2XPos1, D2XPos2 and FinCCSt stay with that complete initializer through
line 8528; T39 starts at InitBowser. T38 also receives AreaDataOfsLoopback
and its immediate loopback dependency KillAllEnemies/KillLoop. Those two
later Bowser-slice labels retain T38 proof and cannot earn duplicate credit
in T41. The [T38 plan](t38-enemy-stream-initialization.md) lists all 91
exact targets and seven S chains. Future custody moves only at S admission.

Every future T in this plan uses the M2 chain-delivery rule in
[Execution](../../rules/EXECUTION.md#m2-chain-based-s-delivery).  The task
table remains the source-order ownership boundary; an admitted S within that
boundary receives a reviewable contiguous control/data chain rather than a
fixed audit/migration/equivalence/operations/closure sequence.

Each chain admission records its source entry and exit, exact labels in order,
shared owner, dependencies and one common ROM route.  It performs mapping,
repair when needed, node-by-node source comparison and operational validation
in the same S.  A single chain P runs its shared replay and three-target
delivery once, then records each member separately in the inventory and
ledger.  A T closes only after its chain matrix covers its call roots and
cross-chain successors, followed by the integrated three-target regression.

Historical S records above remain historical evidence.  This structure applies
to the next admission in every open or future T, including T25's post-S23
receipt and T26--T51.

## Delivery amendment for every queued task

This section governs S delivery for every row in the T21--T51 table.  It
replaces any future reading of a retained proposal table as a required sequence
of separate mapping, migration, equivalence, runtime, or closure S stages.
Those older tables record evidence already produced; they do not prescribe the
next admission.

For every non-closed chain, the next S admission uses one compact source-order
chain table.  Each row names its entry and exit, inventory labels in order,
sole shared-game owner, accepted predecessor and successor receipts, one
original-ROM route, focused tests, and exact forecast completion subset.  The
same S performs mapping, any required C repair, label-level ROM comparison and
operational verification.  One common replay and one three-target package
cover the chain; documentation and tracker updates occur at its end, rather
than becoming standalone S work.

Split a chain only at an unadmitted dependency, a different shared-game owner,
or a branch family requiring a different ROM route.  Every member still has a
separate tracker and ledger disposition and requires both evidence tracks for
credit.  A zero-credit S is allowed only when a named external dependency or
missing evidence prevents that bounded chain from being implemented and
verified together.  T closure adds its call-root/cross-chain matrix and one
integrated three-target regression without repeating accepted member evidence.

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
branches and T25/T28 will verify the subordinate title/area nodes. Focused
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
| `$01f6-$01ff` | 6502 return-address stack bytes are produced by `JSR`, interrupt entry and `RTI`; they are not portable game state or a source label output. | Retain only as a T51 canonical-comparison exclusion candidate. Do not add emulated stack state to `mysmb_game`. |

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

## T22/S25 timer/LFSR equivalence result and T22/S19 admission

All six timer/LFSR labels are **ROM-match complete**, raising conformance from **21 / 1,992** to **27 / 1,992**. The independent ROM probe stops at `$813b`, after the seventh original LFSR rotate and before sprite-zero handling. Master control `2` stayed `1` with timers intact; control `1` decremented frame timers only; zero interval control reset to `$14` and decremented all `$24` timers. All cases incremented FrameCounter and produced LFSR `$d2,$a9,$19,$87,$c0,$00,$ff`, matching the shared C control flow.

T22/S19 is active for the next NMI sprite-zero/OAM subtree at **27 / 1,992**, with zero forecast pending its source contract.


T22/S19 admission correction: `SkipMainOper` is the eighth accepted direct NMI child in the S13 transfer and is therefore included in S19 scope. Its pause-status branch follows `SkipSprite0` after the scene-scroll writes; it cannot be left outside this source-contract package.

## T22/S19 sprite/OAM source contract and T22/S26 proof admission

S19 closes at **27 / 1,992** with no node credit. It mapped the sprite-zero flag gate, the hardware-only PPU status waits, the pause skip, `MoveSpritesOffscreen` offsets `$04..$fc`, and the post-branch scene-scroll handoff. The shared root now publishes scene scroll after that branch. Controlled ROM samples at `SkipSprite0` cover flag absent, active/unpaused and active/paused OAM states; project tests cover the same paths. All eight labels transfer to S26 for independent proof, forecast 35 / 1,992.

## T22/S26 sprite-zero and OAM equivalence result

All eight labels are **ROM-match complete**, raising conformance from **27 / 1,992** to **35 / 1,992**. The independent original-ROM NMI probe exercised the three source branches at the sprite-zero boundary: absent flag preserved OAM (`$0200/$0204/$02fc = 32/33/95`); set flag while unpaused preserved sprite zero and cleared ordinary OAM (`32/248/248`); set flag while paused preserved all three (`32/33/95`). The shared root matches the same `$04..$fc` loop and pause gate. `ppu_frame.c` supplies the ROM split semantic inside the shared game layer: rows 0–31 use zero scroll and subsequent rows consume the committed scene scroll; the focused PPU frame smoke proves that split. The hardware polling loops and 20-count horizontal-blank delay have no portable RAM writes; their observable split barrier is represented solely by that shared PPU semantic, not by either platform adapter. Focused x86/x64 sprite-root, NMI-boundary, PPU-frame and platform-purity tests pass. A fresh OpenNT MZ link and fresh x86/x64 product builds produced `mysmb16.exe` `2872B11D82E95303460528E02B878FBC195D1C18D0B356765CA988E6F21E5244`, `mysmb32.exe` `A08417CE45B49E502CD5981B2396C4149E491E2C95158780F813517DBAA31B1F`, and `mysmb64.exe` `7676730C21A74E133C69BD5E7BDEF26B89E5FB27DE851A99A51273B3408A32F0`.

## T22/S20 sprite-shuffle source-contract admission

S20 begins at **35 / 1,992** for `SpriteShuffler`, `ShuffleLoop`, `StrSprOffset`, `NextSprOffset`, `SetAmtOffset`, and `SetMiscOffset`. It forecasts no completion credit and may only establish the original descending offset traversal, threshold/carry path, shuffle-control wrap, and three-group misc-offset fanout. A separate successor must independently prove each label against controlled ROM output.

## T22/S20 source-contract repair P1

The source audit found one shared-C discrepancy: ROM `SetMiscOffset` starts at `Y=$02`, `X=$08` and writes misc groups 2, 1, then 0. The prior C loop generated the same eventual cells in ascending group order. It now traverses 2→0, preserving the source write sequence. The focused regression covers threshold skipping, overflow plus `$28`, shuffle-control wrap and the `SprDataOffset+5..+7` misc fanout. It passes on x86 and x64. The shared OpenNT MZ relinks with existing C4761/OLDNAMES warnings; refreshed artifacts are `421F5D916B4156CA21E1CFE81BFBDFD5E1ECB6809064BAB0EA896B1984525735`, `F223DCF2A5F164D5DF9E056FFD25BCA58FE35F50AF666D9BC5B4701FA960379B`, and `19430DAF99CCFD461A8E04F602F009CAEAE3EBF9E68CB0357151D19DC4DE736A`. S20 remains at 35 / 1,992 pending independent ROM equivalence proof.

## T22/S20 closure and T22/S27 proof admission

S20 closes at **35 / 1,992** with no node credit after restoring the `SetMiscOffset` group-write order. Its six labels transfer to S27 for independent controlled-ROM proof, forecast **41 / 1,992**.


## T22/S27 sprite-shuffle equivalence result

All six shuffle labels are **ROM-match complete**, raising conformance from **35 /
1,992** to **41 / 1,992**. An independent controlled original-ROM NMI probe
initializes `SprShuffleAmtOffset` to 0, 1 and 2, `SprShuffleAmt` to
`$10/$20/$30`, and fifteen offsets containing below-threshold `$20/$27`,
threshold `$28`, and overflow `$f0` inputs. It samples original RAM after the
shuffle branch. Selector 0 becomes 1 with `$f0 -> $28`; selector 1 becomes 2
with `$f0 -> $38`; selector 2 becomes 0 with `$f0 -> $48`. In every case
offsets below `$28` remain unchanged, qualifying offsets use the source
carry-plus-`$28` path, and misc groups derive from final offsets 5, 6 and 7 in
the original group 2, 1, 0 write order.

`mysmb.sprite-shuffle-smoke` now holds these three ROM-output vectors rather
than inferred C-only expectations. Direct x86 and x64 cross compiles pass, as
does platform-purity. The DOS16 MZ and Win32 x86/x64 product artifacts were
structurally/self-test revalidated; SHA-256 values are
`421F5D916B4156CA21E1CFE81BFBDFD5E1ECB6809064BAB0EA896B1984525735`,
`F223DCF2A5F164D5DF9E056FFD25BCA58FE35F50AF666D9BC5B4701FA960379B`,
and `19430DAF99CCFD461A8E04F602F009CAEAE3EBF9E68CB0357151D19DC4DE736A`
for DOS16, Win32 x86 and Win32 x64 respectively.


## T22/S21 operation-mode dispatch source contract and S28 transfer

S21 closes at **41 / 1,992** with no node credit. ROM `OperModeExecutionTree`
loads `$0770`, invokes `JumpEngine`, and selects exactly one inline vector: 0
`TitleScreenMode`, 1 `GameMode`, 2 `VictoryMode`, or 3 `GameOverMode`. The
source task selectors are then owned by their corresponding leaves. The audit
found that the shared frame root called the title menu helper before this parent
selector and relied on its own guard for non-title frames. `frame_root.c` now
selects mode first and calls that helper only for the source title vector's task
3 leaf; task 0, 1 and 2 retain their existing InitializeGame, ScreenRoutines
and PrimaryGameSetup paths. No platform source changed.

The one label transfers to **T22/S28** for independent controlled-ROM proof.
S28 starts at **41 / 1,992**, scopes only `OperModeExecutionTree`, forecasts
that one match, and has a maximum of **42 / 1,992**. Its ROM track must prove
all four selector values and the selected call boundary; its operational track
is the mode smoke, x86/x64 builds, DOS16 link, platform-purity and three target
artifacts.


## T22/S28 operation-mode dispatch equivalence result

`OperModeExecutionTree` is **ROM-match complete**, raising conformance from
**41 / 1,992** to **42 / 1,992**.  An independent controlled original-ROM
NMI-entry probe set `$0770` to each selector value and sampled the first
selected leaf boundary: 0 reached `$8231` `TitleScreenMode`, 1 reached `$aedc`
`GameMode`, 2 reached `$838b` `VictoryMode`, and 3 reached `$9218`
`GameOverMode`.  The shared C root selects the same four mutually exclusive
routes before entering their leaves; it no longer invokes the title-menu leaf
for a non-title selector.

`mysmb.oper-mode-dispatch-smoke` exercises all four shared-root selections:
title Start changes mode/task to `1/0`; game task zero initializes the saved
halfway page and music queue; victory task one sets its destination page, event
music and task two; and game-over task zero clears sprite-zero, queues its
music and advances task one.  The existing mode smoke, direct x86/x64 C90
builds, platform-purity check, Win32 self-tests and OpenNT DOS16 link pass.
The refreshed artifact SHA-256 values are
`780FC0EC167C5C0CA8CCAF0CA058A041D606A5B16B25A48CB9794DE328167385`,
`7E1FDE53F8C4C0B151A6ED369735598A8BC68E6DF86A3645EAF3FA74CC94DE7A`, and
`75CFC8E8FF1F8D6750A07629F53BBD2E6563FC486B1FD65303D33E6DC59695F3` for
DOS16, Win32 x86 and Win32 x64 respectively.

T22/S22 is now the source-order successor.  It owns only
`NonMaskableInterrupt`, begins at **42 / 1,992**, and may certify the parent
only after rechecking the complete NMI prologue and every now-complete direct
child against a controlled original-ROM NMI route.  It forecasts one parent
match and a maximum of **43 / 1,992**.


## T22/S22 NMI parent dependency audit and custody return

S22 closes at **42 / 1,992** with no new node credit.  The final-parent
admission premise was invalid: `NonMaskableInterrupt` lines 764–872 calls,
in source order, `ScreenOff`, `InitScroll`, `UpdateScreen`, `InitBuffer`,
`SoundEngine`, `ReadJoypads`, `PauseRoutine`, `UpdateTopScore`, the timer
bank, the sprite-zero branch, `MoveSpritesOffscreen`, `SpriteShuffler`, and
`OperModeExecutionTree`.  Eight of those direct route nodes are independently
complete, but `InitScroll`, `UpdateScreen`, `ReadJoypads`, `UpdateTopScore`,
and `SoundEngine` remain open under their recorded owners.  Their shared-C
entry points are not evidence that their original-ROM nodes are complete.

The audit records the dependency set from the original listing and confirms
that the existing focused x86/x64 NMI-boundary and sprite-root checks plus
platform-purity check pass.  It makes no production change and does not use a
partial route to certify the parent.  `NonMaskableInterrupt` transfers back to
T24/S2 owner-authorized custody.  It may be re-admitted for final integration
only after all five named direct dependencies have independently reached
ROM-match complete status.  The required refreshed artifacts have SHA-256 values
`780FC0EC167C5C0CA8CCAF0CA058A041D606A5B16B25A48CB9794DE328167385`,
`33942B8EC68ED08F07F22F18C1A56D149B12216A534C20BC8FF4603C0F28C6CF`, and
`4EB308DD887518B87E7B7D5DEE520F8253F18CC195EE8FA1BCE316BE8E4E41B6` for
DOS16, Win32 x86 and Win32 x64 respectively.

## M2 Td S7 closure

The registry and queue were audited against the plan. Historical `T23` and
`T24` remain intact, and no future source-order row uses either identifier.
Future rows are uniquely `T25` through `T51`, in contiguous ROM order. This
S changes no node receiver, node status, transfer, game source or platform
adapter. Its zero-label closure leaves the M2 numerator at `42 / 1,992`.

## M2 Td S8 admission: legacy receiver reconciliation

T27 S3 exposed a governance-only cycle: its four screen/parser integration
roots depended on parser behavior retained under legacy `M2 T18 S4`, while
that record had closed only an `InitializeGame` prerequisite and supplied no
admittable parser chain. The recovery plan already assigns the physical source
regions to T28 (1825--2794), T29 (2796--3990), and T30 (3991--5314). Td S8
therefore audits every incomplete ledger row against that authoritative table,
returns T27's unclosed roots to T24 S2 custody, and prepares the next T28
receipt without changing any node status or product source.

### Td S8 result

The audit partitions all 1,829 incomplete ledger rows into the authoritative
T21--T51 physical-source ranges; none falls outside the recovery plan. T27 S3
closed with its four integration roots returned to the already accepted T24 S2
custody. The legacy T18 S4 receiver retains the remaining later source labels,
but no longer blocks source-order work: its first thirteen renderer labels were
transferred through a validated receipt to the newly admitted T28 S1. Td S8
changed no node completion status or product source and closes at 163 / 1,992.

T28 S1 was the successor at this historical record. Its receipt was exactly
`RenderAreaGraphics`, `DrawMTLoop`, `RightCheck`, `LLeft`, `NextMTRow`,
`SetAttrib`, `ExitDrawM`, `RenderAttributeTables`, `SetATHigh`, `AttribLoop`,
`SetVRAMCtrl`, `MetatileGraphics_Low`, and `MetatileGraphics_High`.
## Admission record template

Before admitting any listed task, its proposal must replace generic S bullets
with a small source-order chain table.  Every row names: chain entry/exit;
exact inventory labels in order; sole shared-game owner; predecessor and
successor receipts; one ROM route; focused tests; and the exact expected
completion subset.  The admitted packet and ledger run carry the same names
and counts.  There is no standalone mapping, migration, audit, operations, or
paperwork S unless it is an explicit zero-credit chain blocked by a named
external dependency.  Existing historical S/P evidence stays immutable.

T38 S6 admits DuplicateEnemyObj, FSLoop and FlmEx as the missing immediate
InitLongFirebar dependency. The original T39 source span retains those three
labels for reuse/maintenance, with no repeated completion credit. See the
[T38 dependency receipt](../../history/M2-T38-enemy-stream-initialization.md#s6-admission-firebar-initialization-and-duplicate-dependency).

T39 admission keeps the complete movement phase from MovePodoboo (9212)
with T40, removing the split Hammer Bro boundary. Its immediate flame timer
dependency is admitted with S1; the later timer source slice reuses it without
duplicate credit. [Exact T39 chains and receivers](../../history/M2-T39-special-initialization-and-dispatch.md).
