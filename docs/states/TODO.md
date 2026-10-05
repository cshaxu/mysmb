# Long-Term Review Ledger

## Translation Debt

- [ ] **Default-all legacy Cannon Children harness link:** T28 S6 P4's
  default-all build attempt fails in x86/x64 because its direct OAM sources
  reference observation record without linking that owner. Product/focused
  targets pass. Admit a test-binding repair before claiming default-all success;
  no translated logic change is implied.
  [Failure and scoped receipts](../history/M3-T28-dos-rendering-optimization.md#s6-p4-checkpoint-omit-overwritten-raw-reads-in-the-valid-chr-cache-path).

- [ ] **DOS16 optimizer/performance qualification (M4):** T9 S5 observes slow
  graphical frames in SoftPC with accepted original compiler flags. The same
  compiler rejects /Ox or /G3 even for a small neutral color unit with an
  internal buffer/out-of-memory diagnostic;flags withdrawn. Retain the working
  original toolchain. M4 measures actual486SX performance and qualifies any
  compiler configuration or presentation optimization before shipping it.
  [Operational scope](../history/M3-T9-shared-io-and-graphical-output.md#s5-admission---sustained-dos-graphics).

- [x] **Shared sprite-clear child graph:** T70 S6 P2 restores one shared
  SprInitLoop,zero/four entry selectors and the actual NMI child call/return.
  512 full RAM roots and64 complete OAM NMI cases match both widths.
  [Closure proof](../history/m2/t70-final-current-certification.md#s6-p2-closure---shared-sprite-clear-child-graph).

- [ ] **Within-scanline split output proof (High):** T70 S6 observes original
  physical scroll writes inside scanline31 after sprite-zero hit/delay;the
  shared compositor currently represents the active split as32 complete rows.
  This does not certify per-dot fine-X/background-fetch pixel equality.
  Capture original completed pixels and current shared output under actual
  scroll routes,then resolve source-proven differences before final T70/M2
  certification. [Scoped phase proof and limits](../history/m2/t70-final-current-certification.md#s6-p1-verified-part---conditional-visible-scroll-and-saved-control-handoff).


- [x] **Music fetch order beyond immutable PRG inputs:** T69 S14 restores all
  four Square1/Square2 fetch sites to original old-Y, INC, indirect-read order.
  Four original alias families and retained music integration match current
  x86/x64. Earlier immutable-PRG proof is retained; broader whole-game and
  final integrated certification remain T69 S15/T70 obligations.
  [S14 source and operational proof](../history/M2-T69-cross-cohort-current-proof.md#s14-p2-closure---original-square-music-alias-operation-order).

- [x] **Original dump-child graph fidelity (High)** T70 S1 reconciles this early finding with actual shared DumpTwoSpr calls in block_gfx.c/player_gfx.c and T65 S10/T66 S1 real-child inputs, RTS returns and full output. The source store-only shortcuts are gone. Column-only paths retain distinct source semantics. [Current closure](../history/M2-T65-block-query-object-output-current-proof.md), [player row/erase proof](../history/M2-T66-player-relative-offscreen-current-proof.md).


- [x] **Legacy core, title/demo, end-to-end, and local-area smoke fixtures:** T51 S5 P8 completed the remaining source-route adjudications. The core fixture now supplies only the table windows and caller state read by its selected ROM children; the title/demo case follows `PlayerLoseLife -> ContinueGame`; the ROM-free end-to-end case stops at the source-valid title-to-game handoff; and the local-area case runs against owner-local generated data. Native x86/x64 matrices pass 218/218. This resolves the former legacy-suite blocker only; it does not waive the separate active discrepancies below. [T51 S5 P8](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p8-legacy-suite-source-route-closure).

- [x] **KillEnemies entry store:** The earlier T43 finding is superseded by T51 S3: the shared `$9716` owner now stores the incoming identifier in RAM00 before its five-slot zero/load loop, and controlled WarpNum/flagpole callers verify the selective result. The current x86/x64 primitive check also passes. [T51 S3 closure](../proposals/m2/t51-residual-equivalence-and-certification.md#t51-s3-closure-killenemies-shared-primitive).


- [x] **Platform vertical preflight carry:** T42 S9 restores original carry for high-Y exits. Four cross-width S7 cases now retain only independently owned geometry scratch differences. [Proof](../history/M2-T42-shared-collision-and-platforms.md#s9-original-collision-preflight-proof).
- [x] **Side response speed80 and scratch:** The earlier T42 S7 finding is superseded by T43 S6. `RImpd` now preserves the source `CPY #$01`/`BPL` speed80 exit, while `PlatF` writes the RAM00 high adder and preserves carry/page wrap. The current exhaustive x86/x64 impede route passes. [T43 S6 proof](../history/M2-T43-terrain-and-bounding-boxes.md#s6-impede-proof).

- [x] **ForceInjury timer gate:** The earlier T35 scenario is superseded by T42 S5. `InjurePlayer` retains its timer guard, while timer expiry calls the direct source-shaped `ForceInjury(A)` entry; the current cross-width player/enemy contact route passes both guarded and direct cases. [T42 S5 proof](../history/M2-T42-shared-collision-and-platforms.md#s5-player-enemy-response-and-score-proof).

- [x] **Legacy core entry fixture:** T51 S5 P8 compared its entrance-loop assertion with the `PlayerEntrance` forced-right child route and removed the unsupported forty-frame X threshold. The core route now reaches its subsequent source-shaped checks on both widths. [T51 S5 P8](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p8-legacy-suite-source-route-closure).

- [x] **T31 cold-screen and game-entry residual receipt:** T51 S5 P23 restores the original NMI RTI PPU-control write. P24 replays all four original game-entry cases and both retained 600-frame Start/Idle routes with the current shared library: the historical `MusicOffset_Square2` (`$f7`) difference is absent, and all retained persistent-RAM/output checks are now exact on x86/x64. Pipe/vine routes remain independently owned diagnostic paths. [Matrix and exact limits](../history/M2-T31-game-dispatcher.md#t31-cross-chain-results), [T51 S5 P23/P24](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p23-restore-nmi-rti-ppu-control).

- [x] **GameCoreRoutine post-child return:** T31 S1 restores the original task reload/early return; surviving/final life-loss NMI routes match. [Entry closure](../history/M2-T31-game-dispatcher.md#s1p1-entry-chain-closure).
- [x] **Engine palette caller and former legacy-suite debt:** T31 S2 P1 removed the extra palette command. T51 S5 P8 then supplied source-valid table/resource and caller setup for the local-area warp-text and core block-replacement routes; both full native matrices now pass. The independent cold-screen snapshot discrepancy remains below. [T51 S5 P8](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p8-legacy-suite-source-route-closure).
- [x] **Cold-screen snapshot control bit:** T51 S5 P23 restores the original NMI `PHA` / `PLA` physical `$2000` return behavior. The game tree may change the RAM mirror for the following NMI, but the current frame restores its saved control byte with d7 set at RTI. Fresh owner-local original replay matches `$90` at Start samples 1/202 and idle sample 1 on x86/x64. [T51 S5 P23](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p23-restore-nmi-rti-ppu-control).

- [x] **NextArea Silence selector:** T32 S4 restores original $80 in the shared end-level owner and verifies its write after pointer/mode/halfway updates. The direct original NextArea boundary matches native execution on both widths; player-control descendants remain separately incomplete. [Evidence](../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof).
- [ ] **Historic inline-data address annotations (`TODO(High)`):** the source indexer omitted inline labeled data before T30 S14. Scoped pointer/header addresses now have byte-checked corrected bindings. Recheck later table annotations against the corrected listing at each source-order admission; the [full census](../etc/architecture/m2-t24-s1-full-node-census.md) does not certify unreviewed addresses. T70 S3 reconciles25 flagged numeric range comments and fixes16 annotations;unflagged comments and executable numeric data bindings still require source-bound reconciliation. [S3 closure](../history/m2/t70-final-current-certification.md#s3-p1-closure---corrected-current-provenance-without-semantic-changes).


- [x] **Inactive legacy area readers:** T70 S2 removes the seven unused next/decode/emitter/lookahead/preparation functions and obsolete API. Both legacy tests now use the real persistent parser;original boundary NMI replay matches both widths. Active owner bodies are unchanged and all29 admitted original mappings retained. [S2 closure](../history/m2/t70-final-current-certification.md#s2-p1-closure---one-active-parser-and-retained-original-semantics).

- [x] **Jumpspring pre-parser offscreen mismatch:** Superseded by the source-shaped T41 S13 `OffscreenBoundsCheck` carry chain and revalidated through `JumpspringHandler`. At screen origin the ROM's `SBC #$48` wraps the left edge to `$ff:$b8`; a page-zero object `$32` is retained. The current x86/x64 integrated handler check verifies that boundary, the `$00-$03` scratch result, and absence of erasure. [T51 S5 P18](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p18-jumpspring-screen-origin-offscreen-revalidation).

- [ ] **DOS resource binding (`TODO(High)`):** the current DOS composition root powers on and resets the game without binding owner-local PRG, CHR or title data; the OpenNT build does not compile generated resource sources. An MZ link is therefore build evidence only. Admission path: [presentation adapters](../proposals/m3-presentation-adapters.md); require resource binding and an actual boot-to-game route before claiming DOS playability.

- [x] **DOS16 OpenNT compiler execution:** the earlier host-observer finding is superseded.  The original OpenNT 16-bit toolchain now compiles and links the shared C target; every active M2 implementation S continues to build its MZ artifact through that route.  DOS resource binding remains separate work and an MZ link alone still does not establish DOS game playability.

- [x] **T24 missing-path finding (`TODO(High)`): cannon scheduler and whirlpool activation.** T70 S1 confirms both are called by the current shared engine. cannon.c preserves descending slots, random-mask selection, timer decrement and real offscreen/bullet children; whirlpool.c preserves extent/page tests, center carry and gravity tail. T60 S5 water/NMI proof and T69 S8 original cannon child routes supersede the historic omission. [Whirlpool proof](../history/M2-T60-cohort-g-fireball-timer-proof.md), [cannon joins](../history/M2-T69-cross-cohort-current-proof.md#s8-p2-closure---actual-vinecannon-joins).


- [x] **T24 audit D1: non-fiery fireball dispatch.** T34 S1 supersedes the
  historical snapshot: `ProcFireball_Bubble` uses the original single
  PlayerStatus partition before its fireball/bubble branches. Current x86/x64
  dispatch-chain checks pass. [T34 S1 proof](../history/M2-T34-fireball-dispatch-core.md#s1-original-dispatch-proof).
- [x] **T24 audit D2: Goomba ID and score handoff.** T42 S1/S2 supersede the
  historical fixture: `GoombaDie` recognizes ID 6 and `GoombaPoints` preserves
  the source score-control choices. Current x86/x64 fireball scan and hit-chain
  checks pass. [T42 S1 proof](../history/M2-T42-shared-collision-and-platforms.md#s1-original-fireball-scan-proof), [T42 S2 proof](../history/M2-T42-shared-collision-and-platforms.md#s2-fireball-hit-proof).
- [x] **T24 audit D3-D4: fireball flip phase and explosion sprite order.** T45 S3 supersedes both audits: it restores frame-bit-three attribute selection and the second/third explosion-sprite Y order, with source-reachable original OAM comparisons and current x86/x64 fireball OAM checks passing. [T45 S3 closure](../history/M2-T45-object-oam-tail-and-graphics.md#s3-closure-projectile-and-explosion-oam).
- [x] **T24 audit D6-D8 (`TODO(High)`): throw pose/timer, intermediate attributes and swimming animation freeze.** Superseded by T66 S1: current player_gfx.c clears/restores the original throw timer and selects three/four rows, reads the following intermediate sprite attribute, and retains idle swimming animation when timer/index/A are zero. The source-bound 75040 original roots and actual row/erase returns cover all44 labels/103 controls, both outcomes of each branch. [Current player source and proof](../history/M2-T66-player-relative-offscreen-current-proof.md).


- [x] **T24 audit D9 (`TODO(High)`): relative-position scroll write ownership.** T70 S1 source check finds the 0755 write only in RenderPlayerSub's shared row publisher; RelativePlayerPosition retains relative-coordinate/scratch ownership. T66 S1/S2 source and original/native routes supersede the historic seeded-write finding. [Current relative/render proof](../history/M2-T66-player-relative-offscreen-current-proof.md).


- [x] **T24 coverage debt (`TODO(High)`): missing individual proof and incomplete historic scope.** The old missing-label/ownership backlog is superseded by the registered 1992 individual current node rows with source/RAM/table contracts and original/native evidence, plus the closed T53-T69 source-order program. T70 S1 checks original label bindings and evidence availability without treating those checks as semantic proof. Global material enumeration, evidence freshness and complete end-to-end certification remain explicitly open in [T70](../history/m2/t70-final-current-certification.md); this closes only the historic unallocated/missing-label backlog.


- [x] **Jumpspring graphics child:** T44 S8 removed the unsupported slot-five guard and restored the source frame, flip, work-byte and OAM path. All 32 current original graphics-child records match non-stack RAM/OAM on both widths; the earlier T35 differences remain historical evidence. [Closure](../history/M2-T44-block-buffer-and-object-graphics.md#s8-closure-enemy-graphics-and-animation). The separate pre-parser screen-origin route still needs integrated revalidation.

- [x] **Vine OAM wrapped clipping:** The earlier T36 child discrepancy is superseded by T44 S2. `DrawVine -> ChkFTop -> NextVSp` now consumes caller-relative coordinates, applies the source wrapped subtraction and emits all six OAM rows; original replay and current x86/x64 vine OAM checks pass. [T44 S2 closure](../history/M2-T44-block-buffer-and-object-graphics.md#s2-closure-vine-object-graphics).

- [x] **Misc bounding-box screen clipping (`TODO(High)`)** Current shared hammer/coin GetMiscBoundBox entries call BoundingBoxCore then canonical CheckRightScreenBBox with the source +9 misc slot offset. T69 S7/S9 original full parent routes and call/return joins supersede the early omitted-tail finding; current source retains midpoint scratch and wrapped clipping. [Bounds and misc proof](../history/M2-T69-cross-cohort-current-proof.md).


- [x] **GiveOneCoin extra-life sound:** Resolved in T36 S5 and rechecked on the T36 final build. The original hundred-coin transition queues sound40; all 96 S3 actual-child comparisons now match. Historical 48 sound-only failures remain recorded as the pre-fix evidence. [Resolution](../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof).

- [x] **Power-up drawing attributes and offscreen hiding:** Resolved by T44 S7. `DrawPowerUp` now follows `PUpDrawLoop`, `FlipPUpRightSide` and `PUpOfs`, including flower flip `$40` and inherited third-row hiding; all 50 original child records and root snapshots match on both Windows widths. [Closure](../history/M2-T44-block-buffer-and-object-graphics.md#s7-closure-power-up-graphics).

- [x] **Star pickup music:** The T37 S1 case 46 finding is superseded by T42 S4's complete `PlayerEnemyCollision -> HandlePowerUpCollision` source chain.  Its star branch writes `AreaMusicQueue` `$fb = $40` after common pickup setup, and the original actor comparison now matches that case on both Windows widths.  The current direct pickup chain still passes 393,216 type/status/slot cases per width. [Closure](../history/M2-T42-shared-collision-and-platforms.md#s4-power-up-collision-and-palette).

- [x] **BrickShatter second chunk and audio:** T37 S2 original child snapshots isolate second-chunk high Y at $00C0/$00C1 (original zero/native one), missing NoiseSoundQueue $01 and extra Square1SoundQueue $02. Sixteen actual-child comparisons fail across both widths. Keep BrickShatter/SpawnBrickChunks with existing M2 T24 S2 custody until the already planned T37 S4 admission. [Proof](../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof).

Resolved by T37 S4: unchanged final-build S2/S3 snapshots match 264/264; sixteen old shatter failures are gone. [Proof](../history/M2-T37-power-up-block-movement.md#s4-original-shatter-top-coin-and-chunk-proof).

- [x] **Score/coin scratch return divergence:** The later audit identified the shared `PrintStatusBarNumbers -> OutputNumbers` body as the cause.  The ROM writes the selector to `$00`, stores the live VRAM command pointer in `$02`, counts digits through `$03`, then leaves `$03` at zero.  `status.c` now preserves those writes and uses `$00` between the two calls.  All 56 original score/HUD snapshots match with scratch `$00-$07` included on both widths; the 32 shatter cases therefore no longer differ at `$02`. [T51 S5 P16](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p16-score-and-coin-scratch-return-repair).

- [x] **Block/chunk drawing edge output:** The T37 S5 OAM failures are superseded by T45 S2. The source-shaped block/chunk chain now uses original relative positions, offscreen bits, signed carries, mirrored X and column hiding; current x86/x64 block OAM checks pass. [T45 S2 closure](../history/M2-T45-object-oam-tail-and-graphics.md#s2-closure-block-and-brick-chunk-oam).

- [x] **Block replacement VRAM high-row output:** `PutBlockMetatile` now models the ROM's eight-bit `ADC #$20` result before its two `ASL/ROL` operations.  The former wide C expression incorrectly retained the discarded ADC carry and added four to the nametable high byte. All 32 original replacement snapshots now match on each width, including the former twelve `$0301/$0306` high-row failures. [T51 S5 P17](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p17-block-replacement-vram-high-row-repair).

- [x] **PlayerLakituDiff scratch and adjustment semantics:** The earlier T38 caller-only discrepancy is superseded by T40 S10. The shared Lakitu chain now copies the source adjustment bytes, preserves `PlayerEnemyDiff` page/low scratch handling, distance clamping, turn delay and returned speed. Its 1,024 original routes and current x86/x64 route pass. [T40 S10 closure](../history/M2-T40-enemy-movement-and-firebar.md#s10-lakitu-movement-and-distance-helper).

- [x] **Star-flag timer native-test assertion:** The early T39 fixture finding is
  superseded by T41 S6. The source-shaped `AwardGameTimerPoints -> NoTTick`
  chain preserves the frame-bit sound gate and the two score-modifier calls;
  all twenty star-flag labels have ROM-match evidence. The current star-flag
  native route passes 779 cases on each x86/x64 width. [T41 S6 closure](../history/M2-T41-bridge-bowser-and-platforms.md#s6-star-flag-and-end-area-score-chain).

- [x] **Lakitu smoke Spiny-generation failure:** The historical T39 S5
  diagnostic is superseded by T40 S10. The shared source-shaped Lakitu distance
  helper preserves Spiny's distinct adjustment bytes and call order; all former
  124 Spiny differences became original/native matches. The current
  `mysmb.lakitu-smoke` route passes on x86 and x64. [T40 S10 closure](../history/M2-T40-enemy-movement-and-firebar.md#s10-lakitu-movement-and-distance-helper).

- [x] **Actor-vector and retainer actual-child gaps** T70 S1 reconciles the T39 diagnostic with the real current EnemyRun vector, source-shaped retainer/graphics children and canonical relative/offscreen owners. T63/T66 and T69 S13 actual original parent/child routes supersede the historical child failures; no provisional platform seam remains in the current dispatcher. [Actor join proof](../history/M2-T69-cross-cohort-current-proof.md#s13-p3-closure---real-frenzygroupactor-consumers-and-shared-repairs).


- [x] **Normal actor/movement actual-child gaps** The current RunNormalEnemies path uses the source-shaped graphics, bounding, terrain, collision, movement and bounds children, with canonical offscreen writes restored in T69 S15. T63/T64/T65 member proofs plus T69 S15 real child inputs/returns and full parent comparison supersede the T39 caller-only boundary. [Latest actual-child proof](../history/M2-T69-cross-cohort-current-proof.md#s15-p3-closure---real-offscreen-children-and-nmi-integration).


- [x] **Special actor/platform child gaps** The current small/large runners use the real platform box/collision/movement/OAM owners with original order and slot reloads. Source-shaped balance/position/X/right semantics are covered by T63/T64 and T69 actual children; S15 proves paired balance slots and canonical offscreen input/return states. [Latest integrated platform proof](../history/M2-T69-cross-cohort-current-proof.md#s15-p3-closure---real-offscreen-children-and-nmi-integration).
