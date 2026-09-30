# Long-Term Review Ledger

## Translation Debt

- [x] **Legacy core, title/demo, end-to-end, and local-area smoke fixtures:** T51 S5 P8 completed the remaining source-route adjudications. The core fixture now supplies only the table windows and caller state read by its selected ROM children; the title/demo case follows `PlayerLoseLife -> ContinueGame`; the ROM-free end-to-end case stops at the source-valid title-to-game handoff; and the local-area case runs against owner-local generated data. Native x86/x64 matrices pass 218/218. This resolves the former legacy-suite blocker only; it does not waive the separate active discrepancies below. [T51 S5 P8](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p8-legacy-suite-source-route-closure).

- [x] **KillEnemies entry store:** The earlier T43 finding is superseded by T51 S3: the shared `$9716` owner now stores the incoming identifier in RAM00 before its five-slot zero/load loop, and controlled WarpNum/flagpole callers verify the selective result. The current x86/x64 primitive check also passes. [T51 S3 closure](../proposals/m2/t51-residual-equivalence-and-certification.md#t51-s3-closure-killenemies-shared-primitive).


- [x] **Platform vertical preflight carry:** T42 S9 restores original carry for high-Y exits. Four cross-width S7 cases now retain only independently owned geometry scratch differences. [Proof](../history/M2-T42-shared-collision-and-platforms.md#s9-original-collision-preflight-proof).
- [x] **Side response speed80 and scratch:** The earlier T42 S7 finding is superseded by T43 S6. `RImpd` now preserves the source `CPY #$01`/`BPL` speed80 exit, while `PlatF` writes the RAM00 high adder and preserves carry/page wrap. The current exhaustive x86/x64 impede route passes. [T43 S6 proof](../history/M2-T43-terrain-and-bounding-boxes.md#s6-impede-proof).

- [x] **ForceInjury timer gate:** The earlier T35 scenario is superseded by T42 S5. `InjurePlayer` retains its timer guard, while timer expiry calls the direct source-shaped `ForceInjury(A)` entry; the current cross-width player/enemy contact route passes both guarded and direct cases. [T42 S5 proof](../history/M2-T42-shared-collision-and-platforms.md#s5-player-enemy-response-and-score-proof).

- [x] **Legacy core entry fixture:** T51 S5 P8 compared its entrance-loop assertion with the `PlayerEntrance` forced-right child route and removed the unsupported forty-frame X threshold. The core route now reaches its subsequent source-shaped checks on both widths. [T51 S5 P8](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p8-legacy-suite-source-route-closure).

- [ ] **T31 cross-chain residual receipt:** final four-frame game-entry 0/1 routes repeat the known cold-screen PPU-control bit difference at sample 2; game-entry 1 also differs at `MusicOffset_Square2` (`$f7`) at sample 1. NMI/snapshot review remains with the existing T24 S2 custody path, and music sequencing with M2 Td S4's existing audio custody until source-order admission. Pipe/vine failures remain with T23 S5 and T16 S4. These are investigation responsibilities, not new root-cause certificates or concurrent admissions. [Matrix and exact limits](../history/M2-T31-game-dispatcher.md#t31-cross-chain-results).

- [x] **GameCoreRoutine post-child return:** T31 S1 restores the original task reload/early return; surviving/final life-loss NMI routes match. [Entry closure](../history/M2-T31-game-dispatcher.md#s1p1-entry-chain-closure).
- [x] **Engine palette caller and former legacy-suite debt:** T31 S2 P1 removed the extra palette command. T51 S5 P8 then supplied source-valid table/resource and caller setup for the local-area warp-text and core block-replacement routes; both full native matrices now pass. The independent cold-screen snapshot discrepancy remains below. [T51 S5 P8](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p8-legacy-suite-source-route-closure).
- [ ] **Cold-screen snapshot control bit (`TODO(High)`):** unchanged native PPU-control bit 7 differs from original on Start-route samples 1/202 and idle sample 1; persistent game state and all other recorded output match. Admission path: NMI/snapshot corrective review after the admitted source-order chain; T31 entry proof does not certify this field. [Evidence](../history/M2-T31-game-dispatcher.md#s1p1-entry-chain-closure).

- [x] **NextArea Silence selector:** T32 S4 restores original $80 in the shared end-level owner and verifies its write after pointer/mode/halfway updates. The direct original NextArea boundary matches native execution on both widths; player-control descendants remain separately incomplete. [Evidence](../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof).
- [ ] **Historic inline-data address annotations (`TODO(High)`):** the source indexer omitted inline labeled data before T30 S14. Scoped pointer/header addresses now have byte-checked corrected bindings. Recheck later table annotations against the corrected listing at each source-order admission; the [full census](../etc/architecture/m2-t24-s1-full-node-census.md) does not certify unreviewed addresses.


- [ ] **Inactive legacy area readers (`TODO(High)` before full M2 certification):** mysmb_area_next_object and its unused lookahead/emitter cluster retain flat-address decoding and must be removed or consolidated into the authoritative parser. No active frame/root calls them; they receive no conformance credit. [S11 sweep](../history/M2-T30-area-object-rendering.md#s11p1-parser-index-wrap-rom-proof).

- [x] **Jumpspring pre-parser offscreen mismatch:** Superseded by the source-shaped T41 S13 `OffscreenBoundsCheck` carry chain and revalidated through `JumpspringHandler`. At screen origin the ROM's `SBC #$48` wraps the left edge to `$ff:$b8`; a page-zero object `$32` is retained. The current x86/x64 integrated handler check verifies that boundary, the `$00-$03` scratch result, and absence of erasure. [T51 S5 P18](../proposals/m2/t51-residual-equivalence-and-certification.md#s5-p18-jumpspring-screen-origin-offscreen-revalidation).

- [ ] **DOS resource binding (`TODO(High)`):** the current DOS composition root powers on and resets the game without binding owner-local PRG, CHR or title data; the OpenNT build does not compile generated resource sources. An MZ link is therefore build evidence only. Admission path: [presentation adapters](../proposals/m3-presentation-adapters.md); require resource binding and an actual boot-to-game route before claiming DOS playability.

- [x] **DOS16 OpenNT compiler execution:** the earlier host-observer finding is superseded.  The original OpenNT 16-bit toolchain now compiles and links the shared C target; every active M2 implementation S continues to build its MZ artifact through that route.  DOS resource binding remains separate work and an MZ link alone still does not establish DOS game playability.

- [ ] **T24 missing-path finding (`TODO(High)`): cannon scheduler and whirlpool activation.** T22 owns ProcessCannons, ProcessWhirlpools and WhirlpoolActivate; BulletBillHandler and player jump parameters are only collaborators. [Audit evidence](../etc/architecture/m2-t24-s1-full-node-census.md#additional-concrete-scope-findings); admission path: [blocks/items S4](../proposals/m2/blocks-items-misc.md). No repair is admitted here.

- [x] **T24 audit D1: non-fiery fireball dispatch.** T34 S1 supersedes the
  historical snapshot: `ProcFireball_Bubble` uses the original single
  PlayerStatus partition before its fireball/bubble branches. Current x86/x64
  dispatch-chain checks pass. [T34 S1 proof](../history/M2-T34-fireball-dispatch-core.md#s1-original-dispatch-proof).
- [x] **T24 audit D2: Goomba ID and score handoff.** T42 S1/S2 supersede the
  historical fixture: `GoombaDie` recognizes ID 6 and `GoombaPoints` preserves
  the source score-control choices. Current x86/x64 fireball scan and hit-chain
  checks pass. [T42 S1 proof](../history/M2-T42-shared-collision-and-platforms.md#s1-original-fireball-scan-proof), [T42 S2 proof](../history/M2-T42-shared-collision-and-platforms.md#s2-fireball-hit-proof).
- [x] **T24 audit D3-D4: fireball flip phase and explosion sprite order.** T45 S3 supersedes both audits: it restores frame-bit-three attribute selection and the second/third explosion-sprite Y order, with source-reachable original OAM comparisons and current x86/x64 fireball OAM checks passing. [T45 S3 closure](../history/M2-T45-object-oam-tail-and-graphics.md#s3-closure-projectile-and-explosion-oam).
- [ ] **T24 audit D6-D8 (`TODO(High)`): throw pose/timer, intermediate attributes and swimming animation freeze.** T45 S5 resolves former D5 swim-kick tile selection through the original table and consumer route. D6-D8 remain independently unverified; retain their exact nodes from the [77-node report](../etc/architecture/m2-t24-s1-node-verification.md) for source-route audit before closure.
- [ ] **T24 audit D9 (`TODO(High)`): relative-position scroll write ownership.** T16/T23 owns RelativePlayerPosition versus RenderPlayerSub ordering. Evidence: [paired seeded-write probe](../etc/architecture/m2-t24-s1-node-verification.md). Admission path: [OAM](../proposals/m2/oam-graphics.md).
- [ ] **T24 coverage debt (`TODO(High)`): missing individual proof and incomplete historic scope.** Every unfinished label, responsibility, historical S/P reference and evidence gap is named in the [full census](../etc/architecture/m2-t24-s1-full-node-census.md); the [progress ledger](NODE_PROGRESS.md) owns counts. Each responsible source-slice proposal must admit exact names and expected completions before implementation. A passing whole-route or CTest count cannot close unexecuted or unaudited nodes.

- [x] **Jumpspring graphics child:** T44 S8 removed the unsupported slot-five guard and restored the source frame, flip, work-byte and OAM path. All 32 current original graphics-child records match non-stack RAM/OAM on both widths; the earlier T35 differences remain historical evidence. [Closure](../history/M2-T44-block-buffer-and-object-graphics.md#s8-closure-enemy-graphics-and-animation). The separate pre-parser screen-origin route still needs integrated revalidation.

- [x] **Vine OAM wrapped clipping:** The earlier T36 child discrepancy is superseded by T44 S2. `DrawVine -> ChkFTop -> NextVSp` now consumes caller-relative coordinates, applies the source wrapped subtraction and emits all six OAM rows; original replay and current x86/x64 vine OAM checks pass. [T44 S2 closure](../history/M2-T44-block-buffer-and-object-graphics.md#s2-closure-vine-object-graphics).

- [ ] **Misc bounding-box screen clipping (`TODO(High)`):** T36 S2 exposes the existing GetMiscBoundBox child unchanged; it computes the box but omits the original CheckRightScreenBBox tail. The 63 scoped hammer scenarios match and do not certify edge cases. Keep this child with its existing collision receiver and test wrapped screen edges when admitted. [Evidence](../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof).

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

- [ ] **Actor-vector and retainer actual-child gaps:** T39 S7 proves only the
  four caller nodes (360/360); actual native children match 42/360, retaining
  174 vector and 144 retainer failures in that historical build. T44 S8 now
  proves the 72 retainer graphics children at zero differences; other vector
  and actor descendants retain source-order custody. Replace the provisional
  large/small platform seams in their receiving slice.
  GetEnemyOffscreenBits/RelativeEnemyPosition remain with T16 S4.
  [Original gap](../history/M2-T39-special-initialization-and-dispatch.md#s7-original-actor-vector-and-retainer-proof),
  [graphics closure](../history/M2-T44-block-buffer-and-object-graphics.md#s8-closure-enemy-graphics-and-animation).

- [ ] **Normal actor/movement actual-child gaps:** T39 S8 proves its four
  caller nodes with 252/252 original comparisons, while actual-child failures
  remain separately recorded. T44 S8 now proves the 84 original ordinary
  graphics children and 33 additional controlled graphics children at zero
  differences on both widths. Preserve the separate movement and collision
  descendants under their source-order ledger owners.
  [Exact caller/child boundary](../history/M2-T39-special-initialization-and-dispatch.md#s8-original-normal-actor-and-movement-vector-proof).

- [ ] **Special actor/platform child gaps:** T39 S9 proves six callers and
  retains erasure, with 184/184 original comparisons but 32/184 actual-child
  matches. Extracted platform collision/physics entries retain their existing
  source-order owners: balance peer/second small box, positioning, X/Right
  movement and source scratch remain unproved. [S9 exact boundary](../history/M2-T39-special-initialization-and-dispatch.md#s9-original-special-actor-and-platform-proof).
