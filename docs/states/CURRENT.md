# Project Status

## Current Work

**Active implementation packet: M2 T29 S5, the fourteen-node area-parser
dispatch and scenery-selection chain. M2 T29 S4 is closed at 302 / 1,992.**

M2 T24 S2 remains the metadata-verified custodian of its 138 unallocated
nodes; it is not this implementation packet and cannot preempt M2 T29 S4.
The [historical unresolved node closure package](../proposals/m2/historical-node-closure-package.md)
remains a queued historical record and cannot preempt the T29 source-order continuation.

**All other numeric M2 task states in retained proposal text are historical or
queued records. Only the M2 T29 S5 packet below is active.**

## Retained M2 T15 summary

| Field | Historical record |
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

## M2 T29 S4 Packet (closed)

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T29 S4, implementation; life-loss, game-over and player-exchange state chain. |
| Admission And Approval | Owner-approved source-order continuation after T29 S3 closure; accepted ledger transfer `transfer-085-t18-s4-to-t29-s4-life-mode` receives all seventeen labels from M2 T18 S4. |
| Objective | Translate and prove `HalfwayPageNybbles -> DoNothing2` as one shared terminal-mode state boundary. |
| Non-goals | No host-mode branch, synthetic leaf-PC or stack entry, screen/text routine redesign, area-pointer implementation change, or label outside the seventeen-node receipt. |
| Reference Baseline | 285 / 1,992 complete; seventeen scoped incomplete labels; expected seventeen matches; maximum 302 / 1,992. |
| Candidate Proposal | [M2 T29 parser and geometry](../proposals/m2/t29-area-parser-geometry.md). |
| Files And ABI Surface | Shared `terminal_modes.c` owner, mode/root callers, project-owned mode/death smokes, controlled ROM/native recorders, ledger/progress records, and three target artifacts for each implementation P. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, source policy and node ledger. |
| Verification | ROM logic audit `$91bd-$92af`: half-way table/index/nybble branches; lose-life writes; GameOver JumpEngine dispatch; setup/run/termination branches; ContinueGame ordering; player-record swap and carry result; residual write/return. Source-RAM-only GameEngine fixtures cover surviving/final life loss, Game Over Start/timer outcomes, and single/two-player termination. Operational verification runs mode/dispatch/death-music smokes, x86/x64 builds, DOS16 link, platform-purity gate, and package checks. |
| Expected Markers | Table bytes, screen/sprite/music/life writes, world/level half-way result, mode/task writes, Start/timer decisions, `ContinueWorld`, seven-byte player swap, and `$06c9=$ff`. |
| Asset Needs | Refresh mysmb16.exe, mysmb32.exe and mysmb64.exe for every implementation P. |
| Reporting Requirements | Record every node disposition, data/branch/read/write/call-order evidence, source-RAM fixture route result, focused-test/build/package results, three artifact hashes, and every residual transferred outside the chain. |
| Stop Conditions | Stop on an unmatched table byte, state write/order, branch/call sequence, unadmitted dependency, recorder mismatch, or platform gameplay logic. |
| Exit Criteria | All seventeen labels have both ROM-logic and operational evidence without unrelated credit. |
| Original Owner Request | Strict source order, dual verification and shared game logic only. |
| Similar-Issue Sweep | Audit every game-mode dispatch, terminal-mode caller, player-record exchange and platform source; platform code may only supply physical input/timing and submit the completed game frame. |

## M2 T29 S5 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T29 S5, implementation; area-parser dispatch and scenery-selection chain. |
| Admission And Approval | Owner-approved continuation under the T29 source-order plan; accepted ledger transfer from M2 T18 S4 receives all fourteen labels. |
| Objective | Translate and prove `AreaParserTaskHandler -> AreaParserCore` as one shared C parser-dispatch chain. |
| Non-goals | No renderer/metatile leaves, area-stream decoder, platform parser branch, synthetic leaf-PC or stack entry, or label outside the fourteen-node receipt. |
| Reference Baseline | 302 / 1,992 complete; fourteen scoped open labels; expected fourteen matches; maximum 316 / 1,992. |
| Candidate Proposal | [M2 T29 parser and geometry](../proposals/m2/t29-area-parser-geometry.md). |
| Files And ABI Surface | Shared area parser owner, project-owned parser smokes, controlled ROM/native recorders, ledger/progress records, and three target artifacts for each implementation P. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, source policy and node ledger. |
| Verification | ROM logic audit `$92b0` through the AreaParserCore handoff: vector selection, task branches, column increment/carry, scenery and terrain tables, and parser caller/result order. Source-RAM-only GameEngine fixtures cover task-zero/nonzero, wrap and scenery/terrain selections. Operational verification runs parser-schedule/parser-buffer smokes, x86/x64 builds, DOS16 link, purity, and package checks. |
| Expected Markers | Task/vector bytes, column/page updates, scenery table selections, terrain render bits, parser task result and AreaParserCore handoff. |
| Asset Needs | Refresh mysmb16.exe, mysmb32.exe and mysmb64.exe for every implementation P. |
| Reporting Requirements | Record every node disposition, data/branch/read/write/call-order evidence, source-RAM fixture route result, focused-test/build/package results, three artifact hashes, and every residual transferred outside the chain. |
| Stop Conditions | Stop on an unmatched table byte, state write/order, branch/call sequence, unadmitted dependency, recorder mismatch, or platform gameplay logic. |
| Exit Criteria | All fourteen labels have both ROM-logic and operational evidence without unrelated credit. |
| Original Owner Request | Strict source order, dual verification and shared game logic only. |
| Similar-Issue Sweep | Audit every parser task/vector and platform source; platform code may only provide physical input/timing and submit the completed game frame. |

## Prior M2 T25 S25 Packet (closed)

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T25 S25, implementation; title-idle demo data and engine chain. |
| Admission And Approval | Owner-approved source-order M2 plan; S24 completed `ExitIcon` and transferred the remaining 5 title/menu/demo labels to S25. |
| Objective | Establish and credit the complete title-idle demo data and engine chain. |
| Non-goals | No label outside the five-node chain (`DemoActionData`, `DemoTimingData`, `DemoEngine`, `DoAction`, `DemoOver`), new gameplay approximation, platform gameplay logic, or credit without exact data binding, source consumer, and operational replay proof. |
| Reference Baseline | 95 / 1,992 complete; 5 scoped labels; expected matches DemoActionData, DemoTimingData, DemoEngine, DoAction and DemoOver; maximum 100 / 1,992. |
| Candidate Proposal | [T25 title/menu/demo plan](../proposals/m2/t25-title-menu-demo.md). |
| Files And ABI Surface | Shared title/frame-root owners, local/reference recorders, ledger, and three target artifacts for any implementation P. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, source policy and node ledger. |
| Verification | Static source audit of ROM `$8340-$838a`; controlled original-ROM idle-to-demo path; focused title regression, data-binding/consumer inspection, controlled replay, cross-width builds, DOS16 and purity gate. |
| Expected Markers | Source table reads, timer branch, action index, action/timer writes and terminal carry return. |
| Asset Needs | Refresh and report mysmb16.exe, mysmb32.exe and mysmb64.exe for each implementation P. |
| Delivery Profile | S25 is the first multi-node chain under [M2 chain-based S delivery](../rules/EXECUTION.md#m2-chain-based-s-delivery). |
| Reporting Requirements | Record table bytes, all engine branch outcomes, idle-to-demo trace result and all five chain-node dispositions. |
| Stop Conditions | Stop on trace injection, external-owner change, recorder alignment error, a nonmatching source branch, or platform gameplay logic. |
| Exit Criteria | The chain is completed only when both tables, timer branches, action write/decrement and terminal carry return agree; no unrelated node is credited. |
| Original Owner Request | Execute original nodes in source order with strict parity and no platform gameplay logic. |
| Similar-Issue Sweep | Check every score/coin clear caller and StartWorld1 fallthrough; verify that platform sources neither own the loop nor mutate its ROM-owned state. |

## Prior M2 T29 S3 Packet (closed)

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T29 S3, implementation; player/area-entry initialization chain. |
| Admission And Approval | Owner-approved source-order continuation after T29 S2 closure; accepted ledger transfer `transfer-084-t18-s4-to-t29-s3-area-entry` receives all eleven labels from M2 T18 S4. |
| Objective | Translate and prove `PlayerStarting_X_Pos -> SetPESub` in shared C. |
| Non-goals | No platform gameplay branch, host palette policy, synthetic leaf-PC or stack entry, or label outside the eleven-node receipt. |
| Reference Baseline | 274 / 1,992 complete; eleven scoped open labels; expected eleven matches; maximum 285 / 1,992. |
| Candidate Proposal | [M2 T29 parser and geometry](../proposals/m2/t29-area-parser-geometry.md). |
| Files And ABI Surface | Shared player/area-entry owner and existing palette, vine and bubble collaborators; project-owned entrance smoke; controlled ROM/native recorder fixtures; ledger/progress records; and three target artifacts for each implementation P. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, source policy and node ledger. |
| Verification | ROM logic-equivalence audits `$9116-$9196`: exact five data bindings; page/force/facing/state/collision/halfway writes; water flag; alternate-entry index override; player position/attributes and palette call; timer reload gate; vine call; bubble gate; final subroutine write. A source-RAM-only GameEngine task-zero route covers ground/water, normal/alternate entry, timer reload/preserve, vine and bubble branches. Operational verification runs entrance-focused smoke, x86/x64 builds, DOS16 link, platform-purity gate, and package checks. |
| Expected Markers | Data bytes `$28,$18,$38,$28`, `$08,$00`, nine Y bytes, eight priority bytes and timer bytes `$20,$04,$03,$02`; `Player_PageLoc`, force/facing/high-Y/state/collision/halfway writes; `SwimmingFlag`; alternate selector behavior; position/attribute/palette sequence; timer/reset writes; optional vine/bubble calls; `GameEngineSubroutine=$07`. |
| Asset Needs | Refresh mysmb16.exe, mysmb32.exe and mysmb64.exe for every implementation P. |
| Reporting Requirements | Record every node disposition, data/branch/read/write/call-order evidence, source-RAM fixture route result, focused-test/build/package results, three artifact hashes, and every residual transferred outside the chain. |
| Stop Conditions | Stop on an unmatched data byte, state write/order, branch/call sequence, unadmitted dependency, recorder mismatch, or platform gameplay logic. |
| Exit Criteria | All eleven labels have both ROM-logic and operational evidence without unrelated credit. |
| Original Owner Request | Strict source order, dual verification and shared game logic only. |
| Similar-Issue Sweep | Audit every production entrance initializer, alternate-entry selector, timer reload owner and platform source; platform code may only provide physical input/timing and submit the completed game frame. |

## Prior M2 T28 S8 closure

| Field | Required record |
| --- | --- |
| Identifier Mode | M2 T28 S8, implementation; initialization/bootstrap chain. |
| Admission And Approval | Owner-approved source-order continuation; ledger receipt accepts sixteen labels from legacy T18 custody. |
| Objective | Translate and prove `DefaultSprOffsets -> ISpr0Loop` in shared C. |
| Non-goals | No platform initialization branch, host reset policy, synthetic leaf entry, or label outside the sixteen-node receipt. |
| Reference Baseline | 249 / 1,992 complete; sixteen scoped incomplete labels; expected 16 matches; maximum 265 / 1,992. |
| Candidate Proposal | [M2 T28 area output and bootstrap](../proposals/m2/t28-area-output-bootstrap.md). |
| Files And ABI Surface | Shared game/title initialization owners and headers, controlled ROM/native recorder, focused shared-game smoke, ledger and three target artifacts for each implementation P. |
| Applicable Rules | Task Reading Set, execution, architecture, coding, source policy and node ledger. |
| Verification | Source audit of `$8fc0-$905a`; controlled original-ROM/native cold-start and area-entry routes; focused initialization regression; x86/x64, DOS16 and purity checks. |
| Expected Markers | Source data binding, bounded memory clears, page/name-table state, hard-mode and halfway branches, VRAM reset, OAM shuffle/sprite-0 state and mode-task handoff. |
| Asset Needs | Refresh mysmb16.exe, mysmb32.exe and mysmb64.exe for every implementation P. |
| Reporting Requirements | Record every initialization data byte, source branch and all sixteen node dispositions. |
| Stop Conditions | Stop on unmatched source behavior, unadmitted dependency, recorder mismatch or platform gameplay logic. |
| Exit Criteria | All sixteen labels have ROM and operational evidence without unrelated credit. |
| Original Owner Request | Strict source order, dual verification and shared game logic only. |
| Similar-Issue Sweep | Audit every direct reset/area-init/VRAM-clear/OAM-shuffle mutation; platform sources may only supply physical input and submit the completed frame. |

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

M2 T19 S3/P2 is complete: `InitEnemyFrenzy -> InitFlyingCheepCheep` has the same shared `game/enemy/frenzy.c` owner; regular Flying Cheep actor handling remains reserved for T19 S4.

M2 T19 S3/P3 is complete: `InitEnemyObject -> CheckpointEnemyID -> InitEnemyRoutines` now has one shared `game/enemy/init.c` owner; stream parsing no longer contains initialization dispatch.

M2 T19 S5/P20 restores ROM current-slot `EnemiesCollision`: no frame-root global collision scan manufactures bounding boxes; the pipe route OAM residual is removed.
M2 T16 S3/P8 restores defeated-Goomba mirrored OAM attributes and its route evidence is consumed by the updated T17 pipe comparison.
