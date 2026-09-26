# Project Status

## Current Work

**M2 T21 S2 active: audit and migrate the shared C boot/cold-initialization owner.**

M2 T24 S2 remains the metadata-verified custodian of its 138 unallocated
nodes; it is not this implementation's active packet and cannot preempt T21.
The [historical unresolved node closure package](../proposals/m2/historical-node-closure-package.md)
remains queued after the active T21 closure task.

**M2 T23 S2/P1 complete (S2 active); M2 T22 S1/P2 active; M2 T21 S2/P2 and S5/P1 active; M2 T20 S4/P1 active; M2 T19 S5/P20, and M2 T18 S2/P1 active; M2 T17 S6/P6 active (S2/S3 complete; source-route closure active); M2 T16 S3/P8 active; M2 T15 S4 remains gated at its cross-slice block prerequisite.**

| Field | Record |
| --- | --- |
| Identifier Mode | Implementation |
| Objective | Create the source-owned OAM/offscreen module tree before migrating the real-demo block/OAM prerequisite; retain T15 title/terminal route evidence without cross-slice fixes. |
| Scope | game title/mode leaves, area text/OAM collaborators, owner-local trace fixtures, OpenNT DOS build, and three executable artifacts. |
| Result | T14 is closed: reset/cold boot live in boot.c; the complete NMI prologue, pause, shuffle and operation-mode tree live in frame_root.c; the 600-sample title-start route has zero differences in OAM/CIRAM/palette/audio/PPU output and byte-identical x86/x64 native traces. T15 S1 mapped the title/terminal tree and found missing Select-icon and world-select B branches; S2 migrated and traced those menu paths in ROM order; S3/P1-P8 isolates the complete terminal mode tree in terminal_modes.c, fixes its mapped terminal collaborators, freezes ROM-slice module boundaries, restores GameMode-only timer ownership exposed by controlled GameOver reference output, and restores RenderPlayerSub's post-scroll Player_Pos_ForScroll handoff exposed by controlled VictoryWalk reference output; its controlled Victory task-3 message route now has matching NMI output evidence. S4/P1 adds two source-reachable 600-sample NMI routes: title Start/right and idle-to-demo; both have zero differences in OAM backing, work RAM, CIRAM, palette, visible OAM, audio, and PPU output. S4/P2 uses the actual demo continuation to repair the airborne LRAir friction edge and InitBlock_XY_Pos carry semantics. S4/P3 freezes the resulting cross-slice differences at their ROM owners: RelativeBlockPosition/GetBlockOffscreenBits go to the OAM/offscreen-and-graphics structural task, while BlockObjectsCore/jump-coin state go to the blocks/items/misc structural task; T15 will not accumulate these unrelated fixes. DOS PPU buffer uses far runtime storage so the shared compositor builds in 16-bit mode; the physical-key adapter maps J to B and K to A on both Windows and DOS. |
| Artifact rule | Every P commit includes refreshed mysmb16.exe, mysmb32.exe, and mysmb64.exe. |
| Node-progress rule | Before work, every M2 S records baseline, exact inventory labels, exact expected matches, maximum closing count, focused CTests and ROM route. Closure records actual count, evidence/disposition and transfers. Baseline: [M2 ROM-node progress](NODE_PROGRESS.md). |
| Stop condition | Stop if extraction changes a ROM-owned state transition or introduces platform gameplay logic. |

Audit result: **3 / 1,992** complete. The [full census](../etc/architecture/m2-t24-s1-full-node-census.md) records every prior responsibility and missing proof; [initial 77-node probes](../etc/architecture/m2-t24-s1-node-verification.md) found nine discrepancy classes. No production repair belongs to T24 S1. Current counts and version-sensitive revalidation states are in [NODE_PROGRESS](NODE_PROGRESS.md).

S2 ledger deliverable: [all-node T/S ledger](NODE_TASK_LEDGER.md) registers
1,992 unique receivers, 40 known T records and 53 known/planned S records.
1,854 nodes are accepted by existing slice closure subtasks; 138 remain in
T24 S2 custody (40 closed-root, 67 screen/status, 31 dispatcher) until future
admission and accepted transfer. S2 remains open for that custody, even though
the ledger/tooling deliverable is verified. Seventeen validation scenarios,
including fifteen rejection cases, pass; conformance remains 3 / 1,992.

## Current Technical Baseline

- `mysmb_game` is a C90 native logic foundation with translated title, area,
  player, object, mode, audio-command, and background-output routes. Its
  canonical snapshot now has translated name-table, attribute, palette,
  scroll, status, PPU state, and the currently admitted OAM output. The bounded
  trace has exact visible output, but remaining raw-state and route coverage keep
  M2 open. `mysmb_win32` builds
  x86 and x64 PE windows; owner-local title data and CHR are generated only
  into ignored output. `nnes` is validation-only and is never linked into
  MySMB.

## M2 T21 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T21 S2, Continuation; shared-C implementation. |
| Admission And Approval | Owner approved source-order replan and T21 admission on 2026-09-26. |
| Objective | Migrate and audit the shared-C boot/cold-initialization owner for 7 boot nodes. |
| Non-goals | NMI/PPU timing after `ScreenOff`, all gameplay routes, and T20 fireball/bubble nodes are outside T21. |
| Reference Baseline | 3 / 1,992 complete; 7 exact labels received by T21 S2. |
| Candidate Proposal | [T21 boot and cold initialization](../proposals/m2/t21-boot-cold-init.md); [source-order T21–T49 plan](../proposals/m2/t21-t49-source-order-recovery.md). |
| Files And ABI Surface | Boot/root C owners, focused root tests, ledger run and ignored route evidence; no platform gameplay logic. |
| Applicable Rules | Task Reading Set, execution, contributing, architecture, coding, source policy and node-ledger workflow. |
| Verification | S2 changes only shared game code. S3 ROM logic-equivalence and S4 operational verification remain separate. |
| Expected Markers | `Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, `InitializeMemory`; expected matches: empty; maximum 3 / 1,992. |
| Asset Needs | Owner-local ROM and listing are non-redistributable research inputs. Build products, traces and ROM-derived executables remain local; each P refreshes the three local target artifacts without treating them as conformance evidence. |
| Reporting Requirements | For every P, name its exact node subset, branch/write mapping, test and route evidence, actual versus expected matches, blockers/transfers, three-artifact hashes and platform-boundary review. |
| Stop Conditions | Stop if a root branch requires a later NMI, platform, or gameplay owner without an accepted dependency boundary. |
| Exit Criteria | Every admitted write and branch has a shared-C owner or an accepted boundary; S3/S4 have a reviewable implementation basis. |
| Original Owner Request | Replan the backlog in source order and execute small, verifiable tasks. |
| Similar-Issue Sweep | Check every boot/root label for duplicated initialization, host-owned state, stale direct tests, and missing cold/warm branch evidence. |

## Recent M4 Closures

| Task | Compact result |
| --- | --- |
| T1 | The physical 486SX qualification protocol defines build identity, host facts, scripted routes, timing samples, and acceptance evidence without any fabricated measurement. [History](../history/M4-T1-486sx-qualification-protocol.md). |

## Deferred M4 Evidence

- An isolated SoftPC compatibility probe booted the ROM-free DOS MZ for a
  bounded fifteen seconds without host-process exit. It is not physical-host,
  performance, visual, or gameplay evidence. [Record](../history/M4-T2-S1-softpc-compatibility-probe.md).

## Recent M3 Closures

| Task | Compact result |
| --- | --- |
| T1 | Neutral tile-row and actor commands are generated read-only from the native C state; a bounded Win32 consumer and C90/OpenNT verification are in place. [History](../history/M3-T1-neutral-render-command-seam.md). |
| T2 | Win32 consumes every neutral tile-row and actor command with a deterministic host palette, without a second gameplay path. [History](../history/M3-T2-win32-command-consumer.md). |
| T3 | A neutral render frame now yields a deterministic 80x25 character/color frame with full background fill and object glyph/color overlays. [History](../history/M3-T3-colored-text-frame.md). |
| T4 | A 320x200 indexed frame is generated from neutral commands using explicit 16-bit-safe pages and compiles under OpenNT. [History](../history/M3-T4-vga-indexed-frame.md). |
| T5 | The DOS16 root owns one native tick and both presentation-frame submissions through isolated hooks; its source compiles under OpenNT. [History](../history/M3-T5-dos16-composition-root.md). |
| T6 | A configured OpenNT large-model build links the actual DOS root and frame adapters into an ignored MZ executable. [History](../history/M3-T6-opennt-mz-link.md). |
| T7 | BIOS input/timing plus Mode 13h and colored-text hardware hooks are linked into the DOS root while remaining outside game code. [History](../history/M3-T7-dos-hardware-hooks.md). |
| T8 | MZ/map structural evidence is reproducible; the local host's documented lack of graphical DOS presentation prevents a false runtime claim. [History](../history/M3-T8-dos-runtime-structural-evidence.md). |

## Prior M2 Records Under Correction

These records retain their original task evidence but no longer establish M2
completion. T9 audits and replaces the insufficient frame/output proof.

| Task | Compact result |
| --- | --- |
| T1 | Full direct-ROM PRG analysis, revision reconciliation, and source-address architecture record completed with zero unresolved PRG bytes. [History](../history/M2-T1-prg-static-analysis.md). |
| T2 | Title input/start C90 route and bounded owner-local transition checkpoint closed; A+Start mirror audit repaired. [History](../history/M2-T2-title-start-checkpoint.md). |
| T3 | Area bootstrap, actual area-pointer/header parsing, object stream classification, and native command queue closed. [History](../history/M2-T3-area-bootstrap-and-commands.md). |
| T4 | Player physics, terrain collision, entrances, scrolling, and bounded owner-local checkpoint closed. [History](../history/M2-T4-player-route-and-collision.md). |
| T5 | Blocks, items, enemies, projectiles, score/timer/power, firebars, Bowser, and platform routes closed. [History](../history/M2-T5-object-routes.md). |
| T6 | Death, restart, two-player exchange, Warp Zone, and completion modes closed. [History](../history/M2-T6-mode-routes.md). |
| T7 | Original audio queues, priorities, buffers, and neutral command state closed. [History](../history/M2-T7-audio-command-routes.md). |
| T8 | Bounded title-to-play oracle, Win32 composition audit, and two original frame-order repairs were recorded; the output proof is superseded by T9. [History](../history/M2-T8-end-to-end-oracle-and-win32-route.md). |

## Recent M2 Closures

| Task | Compact result |
| --- | --- |
| T10 | Source-owned name tables, attributes, palettes, status, scroll, and PPU commit state now reach the canonical snapshot through native C. [History](../history/M2-T10-translated-background-output.md). |
| T11 | Source-owned player, object, and special-route OAM reaches the native snapshot; bounded Start/right reference evidence has zero OAM and PPU-visible differences. [History](../history/M2-T11-translated-oam-output.md). |
| T12 | The ROM-enabled Win32 composition root decodes native CHR, nametables, palettes, and OAM; its self-test verifies all eight NES controller actions on x86 and x64. |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.

M2 T19 S2/P3 has begun structural recovery: `MoveD_EnemyVertically` is now owned by `src/game/enemy/movement.c`; `objects.c` is no longer a target for new actor logic.

M2 T17 S2/P5 is complete: `MoveObjectHorizontally` now preserves its full ADC carry and `MoveEnemyHorizontally` has one world-owner wrapper; S6/P1-P6 now provide source-reachable movement, mushroom, hidden-block, pipe, stomp, and score evidence; fireball route closure remains pending.

M2 T19 S3/P1 is complete: the full Lakitu/Spiny frenzy function group now has one shared `game/enemy/frenzy.c` owner; T19 S3 remains active for remaining group/initialization dispatch.

M2 T19 S3/P2 is complete: `InitEnemyFrenzy → InitFlyingCheepCheep` has the same shared `game/enemy/frenzy.c` owner; regular Flying Cheep actor handling remains reserved for T19 S4.

M2 T19 S3/P3 is complete: `InitEnemyObject → CheckpointEnemyID → InitEnemyRoutines` now has one shared `game/enemy/init.c` owner; stream parsing no longer contains initialization dispatch.

M2 T19 S5/P20 restores ROM current-slot `EnemiesCollision`: no frame-root global collision scan manufactures bounding boxes; the pipe route OAM residual is removed.
M2 T16 S3/P8 restores defeated-Goomba mirrored OAM attributes and its route evidence is consumed by the updated T17 pipe comparison.
