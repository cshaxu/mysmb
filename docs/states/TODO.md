# Long-Term Review Ledger

## Translation Debt

- [ ] **Eight failing legacy smoke tests require ROM adjudication and useful diagnostics.** The failures are `core`, `player-bounding-box`, `hammer-bro`, `enemy-collision`, `bowser`, `title-demo`, `end-to-end`, and `local-area`. S5 also removed `area-entry`: water `SetupBubble` falls through `MoveBubl`, so its selector-one fixture correctly writes bubble Y `$f8`, not the pre-movement `$08`. Previous S5 source reviews corrected the `enemy-background-entry` scratch expectation and the `enemy-terrain-state` uninitialized fixture/final-Y expectation. Retain the eight remaining tests until each assertion is compared with the original ROM: correct a wrong expectation or fix shared C in its receiving node's maintenance/source-order chain, and make failures identify their exact case. This baseline is not an acceptance waiver for M2 closure. [T48 S4 review](../proposals/m2/t48-sound-effects-and-channel-handlers.md#s4-closure-square-one-dispatch-and-lifetime).

- [ ] **KillEnemies entry store:** T43 S3 independently proves64/64 original child calls differ at RAM00: original stores incoming33, existing area helper retains02. Its historical completion is revoked; maintenance receiver remains M2 T29 S8. Repair requires that original store plus both warp and flagpole callers in a separately admitted maintenance chain. No extra S3 child algorithm change. [Evidence](../history/M2-T43-terrain-and-bounding-boxes.md#s3-climbing-proof).


- [ ] **Terrain descendant scratch:** T43 S1 independently compares8,049 original child calls per width. Query metadata and consumed returns match, but block queries omit RAM02-05; coin/axe/head/impede descendants retain RAM00-07 differences. Full native root matches59/1,034. S2 completes the coin/axe caller contract with128/128 matches, while actual roots match16/128 and independent VRAM/status children retain RAM00/02/03 gaps ([S2 proof](../history/M2-T43-terrain-and-bounding-boxes.md#s2-coin-and-axe-proof)). Impede belongs to S6, classifiers S7, queries the following source slice; block-head/VRAM children retain existing ledger maintenance custody. No out-of-order admission or descendant credit. [Exact child matrix](../history/M2-T43-terrain-and-bounding-boxes.md#s1-original-terrain-control-proof).


- [x] **Platform vertical preflight carry:** T42 S9 restores original carry for high-Y exits. Four cross-width S7 cases now retain only independently owned geometry scratch differences. [Proof](../history/M2-T42-shared-collision-and-platforms.md#s9-original-collision-preflight-proof).
- [ ] **Side response speed80 and scratch (`TODO(High)`):** T42 S7 exposes ImpedePlayerMove/RImpd treating80 as negative instead of preserving the original CPY #1/BPL result. Forty cross-width samples alter X speed/position/timer; ordinary paths also omit RAM0's high-adder write. Existing M2 T17 S6 custody; following source-order player-terrain slice. [Evidence](../history/M2-T42-shared-collision-and-platforms.md#s7-original-platform-collision-proof).

- [ ] **Remaining initializer child bodies after S6:** Common and firebar initializers now match; the full vector retains 64/220 actual child failures (piranha, frenzy generators, platforms and Bowser). S7 has proven the flying-fish child; the containing frenzy dispatcher still has nested JumpEngine scratch debt. Other bodies retain their existing source-order custody. [S6 evidence](../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof).


- [ ] **Remaining parser descendants:** S6 improves actual parser comparisons to 150/160; ten remaining initializer/group failures retain their existing custody and source slices. [S6 evidence](../history/M2-T38-enemy-stream-initialization.md#s6-original-firebar-and-duplicate-proof).


- [ ] **Enemy successor scratch-state fidelity:** T38 S1 independently reproduces 180/192 integrated failures at $04-$07 in existing parser/initializer/actor-dispatch children. ProcessEnemyData and CheckpointEnemyID/InitEnemyRoutines await T38 S2/S3 admission; RunEnemyObjectsCore/JmpEO remain with existing T19 S5 for the later actor-dispatch slice. No child credit or waiver. The related bridge.c five-flag clear also remains with the later bridge caller slice; it must use the full kill-all semantics when migrated. [Exact scope and evidence](../history/M2-T38-enemy-stream-initialization.md#s1-original-loop-and-slot-proof).


- [ ] **ForceInjury incorrectly inherits the InjurePlayer timer gate:** T35 S2's original timer scenario 13 reaches TimeUpOn with InjuryTimer nonzero. Original ForceInjury still kills the small player; the current shared child returns early. Both widths differ at engine/state/Y-speed/music/timer-control bytes. Retain with the existing M2 T17 S6 receiver for ForceInjury/KillPlayer and source-order collision admission; no child repair or credit in the timer S. [Timer evidence](../history/M2-T35-bubbles-timer-warp.md#s2-admission-timer-gates-countdown-and-expiry).

- [ ] **Legacy core entry fixture:** T33 S3's extra `core_smoke` run stops at the entrance-loop assertion in `test/core_smoke.c` (line 136). The prior S2 build fails at the identical first assertion. Retain under the existing entry-owner maintenance path (T31 S4); audit the fixture against original entry semantics before changing its expectation or production code. Later assertions were not reached. [Scoped evidence](../history/M2-T33-player-movement-state.md#s3-original-physics-proof).

- [ ] **T31 cross-chain residual receipt:** final four-frame game-entry 0/1 routes repeat the known cold-screen PPU-control bit difference at sample 2; game-entry 1 also differs at `MusicOffset_Square2` (`$f7`) at sample 1. NMI/snapshot review remains with the existing T24 S2 custody path, and music sequencing with M2 Td S4's existing audio custody until source-order admission. Pipe/vine failures remain with T23 S5 and T16 S4. These are investigation responsibilities, not new root-cause certificates or concurrent admissions. [Matrix and exact limits](../history/M2-T31-game-dispatcher.md#t31-cross-chain-results).

- [x] **GameCoreRoutine post-child return:** T31 S1 restores the original task reload/early return; surviving/final life-loss NMI routes match. [Entry closure](../history/M2-T31-game-dispatcher.md#s1p1-entry-chain-closure).
- [ ] **Engine palette caller and legacy suite debt (`TODO(High)`):** T31 S2 P1 removes the extra palette command at $0300-$0307 and the timer buffer assertions now pass. The old local-area suite later fails its warp-text fixture, while core retains a ROM-free block replacement expectation failure; those fixture debts remain with their existing source owners. No suite pass is claimed. [Evidence](../history/M2-T31-game-dispatcher.md#s1p1-entry-chain-closure).
- [ ] **Cold-screen snapshot control bit (`TODO(High)`):** unchanged native PPU-control bit 7 differs from original on Start-route samples 1/202 and idle sample 1; persistent game state and all other recorded output match. Admission path: NMI/snapshot corrective review after the admitted source-order chain; T31 entry proof does not certify this field. [Evidence](../history/M2-T31-game-dispatcher.md#s1p1-entry-chain-closure).

- [x] **NextArea Silence selector:** T32 S4 restores original $80 in the shared end-level owner and verifies its write after pointer/mode/halfway updates. The direct original NextArea boundary matches native execution on both widths; player-control descendants remain separately incomplete. [Evidence](../history/M2-T32-player-control-modes.md#s4-p1-original-end-level-proof).
- [ ] **Historic inline-data address annotations (`TODO(High)`):** the source indexer omitted inline labeled data before T30 S14. Scoped pointer/header addresses now have byte-checked corrected bindings. Recheck later table annotations against the corrected listing at each source-order admission; the [full census](../etc/architecture/m2-t24-s1-full-node-census.md) does not certify unreviewed addresses.


- [ ] **Inactive legacy area readers (`TODO(High)` before full M2 certification):** mysmb_area_next_object and its unused lookahead/emitter cluster retain flat-address decoding and must be removed or consolidated into the authoritative parser. No active frame/root calls them; they receive no conformance credit. [S11 sweep](../history/M2-T30-area-object-rendering.md#s11p1-parser-index-wrap-rom-proof).

- [ ] **Jumpspring pre-parser offscreen mismatch (`TODO(High)`):** T30/S7 GameEngine probes found native jumpsprings cleared by the unsigned `screen - 0x48` comparison near screen origin while ROM retains them, changing allocation before area creation. S7 proves creation through original ScreenRoutines; runtime/offscreen repair remains with its existing source-order receiver. [Evidence](../history/M2-T30-area-object-rendering.md#t30s7-admission-jumpspring-creation-chain).

- [ ] **DOS resource binding (`TODO(High)`):** the current DOS composition root powers on and resets the game without binding owner-local PRG, CHR or title data; the OpenNT build does not compile generated resource sources. An MZ link is therefore build evidence only. Admission path: [presentation adapters](../proposals/m3-presentation-adapters.md); require resource binding and an actual boot-to-game route before claiming DOS playability.

- [x] **DOS16 OpenNT compiler execution:** the earlier host-observer finding is superseded.  The original OpenNT 16-bit toolchain now compiles and links the shared C target; every active M2 implementation S continues to build its MZ artifact through that route.  DOS resource binding remains separate work and an MZ link alone still does not establish DOS game playability.

- [ ] **T24 missing-path finding (`TODO(High)`): cannon scheduler and whirlpool activation.** T22 owns ProcessCannons, ProcessWhirlpools and WhirlpoolActivate; BulletBillHandler and player jump parameters are only collaborators. [Audit evidence](../etc/architecture/m2-t24-s1-full-node-census.md#additional-concrete-scope-findings); admission path: [blocks/items S4](../proposals/m2/blocks-items-misc.md). No repair is admitted here.

- [ ] **T24 audit D1 (`TODO(High)`): non-fiery fireball dispatch.** T20 owns revalidation of the concurrently changed implementation; the recorded snapshot violates the ROM PlayerStatus guard. Evidence: [D1 and named nodes](../etc/architecture/m2-t24-s1-node-verification.md). Admission path: [fireballs and bubbles](../proposals/m2/fireballs-bubbles.md). Audit does not certify the subsequent repair.
- [ ] **T24 audit D2 (`TODO(High)`): Goomba ID and score handoff.** T17 owns GoombaDie/GoombaPoints and the self-confirming collision fixture. Evidence: [paired probes](../etc/architecture/m2-t24-s1-node-verification.md). Admission path: [collision/world](../proposals/m2/collision-world.md).
- [ ] **T24 audit D3-D4 (`TODO(High)`): fireball flip phase and explosion sprite order.** T16/T20 own DrawFireball/DrawExplosion_Fireball and incorrect expected OAM. Evidence: [32/7-case probes](../etc/architecture/m2-t24-s1-node-verification.md). Admission path: [OAM](../proposals/m2/oam-graphics.md).
- [ ] **T24 audit D5-D8 (`TODO(High)`): swim kick, throw pose/timer, intermediate attributes and swimming animation freeze.** T16 with T20/T23 collaborators owns the exact mismatch nodes named in the [77-node report](../etc/architecture/m2-t24-s1-node-verification.md). Admission path: [OAM](../proposals/m2/oam-graphics.md). No gameplay or expectation change is admitted by the audit.
- [ ] **T24 audit D9 (`TODO(High)`): relative-position scroll write ownership.** T16/T23 owns RelativePlayerPosition versus RenderPlayerSub ordering. Evidence: [paired seeded-write probe](../etc/architecture/m2-t24-s1-node-verification.md). Admission path: [OAM](../proposals/m2/oam-graphics.md).
- [ ] **T24 coverage debt (`TODO(High)`): missing individual proof and incomplete historic scope.** Every unfinished label, responsibility, historical S/P reference and evidence gap is named in the [full census](../etc/architecture/m2-t24-s1-full-node-census.md); the [progress ledger](NODE_PROGRESS.md) owns counts. Each responsible source-slice proposal must admit exact names and expected completions before implementation. A passing whole-route or CTest count cannot close unexecuted or unaudited nodes.

- [x] **Jumpspring graphics child:** T44 S8 removed the unsupported slot-five guard and restored the source frame, flip, work-byte and OAM path. All 32 current original graphics-child records match non-stack RAM/OAM on both widths; the earlier T35 differences remain historical evidence. [Closure](../history/M2-T44-block-buffer-and-object-graphics.md#s8-closure-enemy-graphics-and-animation). The separate pre-parser screen-origin route still needs integrated revalidation.

- [ ] **Vine OAM wrapped clipping (`TODO(High)`):** T36 S1 proves the six vine caller nodes, while actual-child comparison retains 32 failures at OAM Y bytes 0200/020C/0210/0214. DrawVine/ChkFTop/NextVSp retain M2 T17 S6 custody; repair the original wrapped subtraction and recheck all source rows when that graphics slice is admitted. [Evidence](../history/M2-T36-misc-object-chains.md#s1-original-vine-actor-proof).

- [ ] **Misc bounding-box screen clipping (`TODO(High)`):** T36 S2 exposes the existing GetMiscBoundBox child unchanged; it computes the box but omits the original CheckRightScreenBBox tail. The 63 scoped hammer scenarios match and do not certify edge cases. Keep this child with its existing collision receiver and test wrapped screen edges when admitted. [Evidence](../history/M2-T36-misc-object-chains.md#s2-original-hammer-lifecycle-proof).

- [x] **GiveOneCoin extra-life sound:** Resolved in T36 S5 and rechecked on the T36 final build. The original hundred-coin transition queues sound40; all 96 S3 actual-child comparisons now match. Historical 48 sound-only failures remain recorded as the pre-fix evidence. [Resolution](../history/M2-T36-misc-object-chains.md#s5-original-score-and-hud-proof).

- [x] **Power-up drawing attributes and offscreen hiding:** Resolved by T44 S7. `DrawPowerUp` now follows `PUpDrawLoop`, `FlipPUpRightSide` and `PUpOfs`, including flower flip `$40` and inherited third-row hiding; all 50 original child records and root snapshots match on both Windows widths. [Closure](../history/M2-T44-block-buffer-and-object-graphics.md#s7-closure-power-up-graphics).

- [ ] **Star pickup music:** T37 S1 case 46 isolates PlayerEnemyCollision/HandlePowerUpCollision leaving AreaMusicQueue $FB=$00 instead of original $40 on both widths. Keep existing M2 T17 S6 collision custody until source-order admission. [Proof](../history/M2-T37-power-up-block-movement.md#s1-original-power-up-actor-proof).

- [x] **BrickShatter second chunk and audio:** T37 S2 original child snapshots isolate second-chunk high Y at $00C0/$00C1 (original zero/native one), missing NoiseSoundQueue $01 and extra Square1SoundQueue $02. Sixteen actual-child comparisons fail across both widths. Keep BrickShatter/SpawnBrickChunks with existing M2 T24 S2 custody until the already planned T37 S4 admission. [Proof](../history/M2-T37-power-up-block-movement.md#s2-original-head-hit-and-positioning-proof).

Resolved by T37 S4: unchanged final-build S2/S3 snapshots match 264/264; sixteen old shatter failures are gone. [Proof](../history/M2-T37-power-up-block-movement.md#s4-original-shatter-top-coin-and-chunk-proof).

- [ ] **Score/coin scratch return divergence:** T37 S4 expands RAM comparison to $02/$06/$07. All 32 native actual shatter runs differ at $02; isolated AddToScore differs in all 16 cases and SetupJumpCoin additionally in cases 8-11 on both widths. Keep existing T36 S5 score and T36 S3 coin maintenance custody, with T28 S7 status-output dependency; admit a bounded repair through the queue, without parallel implementation or presumed deeper root cause. [Exact proof and limits](../history/M2-T37-power-up-block-movement.md#s4-original-shatter-top-coin-and-chunk-proof).

- [ ] **Block/chunk drawing edge output:** T37 S5 actual roots retain 34 OAM-only failures across both widths. Independent children isolate DrawBlock in cases 4/6/8/10 and DrawBrickChunks in 3/13/15/17/19/20/21/23/25/27/28/29/31, involving sprite hiding and mirrored X. Keep existing M2 T17 S6 custody until source-order graphics admission; no drawing repair in S5. [Original proof and limits](../history/M2-T37-power-up-block-movement.md#s5-original-block-lifetime-proof).

- [ ] **Block replacement VRAM high-row output:** T37 S6 cases 6/7/14/15/22/23 differ only at VRAM address-high bytes $0301/$0306 on both widths (12 actual failures). Independent ReplaceBlockMetatile snapshots reproduce original $20/native $24 or original $24/native $28. Keep existing T28 S3 maintenance custody for the child and its VRAM calculation; no deeper instruction is certified as root cause here and no child repair is included in S6. [Original proof and limits](../history/M2-T37-power-up-block-movement.md#s6-original-block-replacement-proof).

- [ ] **PlayerLakituDiff original scratch and adjustment semantics:** T38 S5 caller proof retains 124/160 actual failures, all at RAM $00, while the child still uses a static adjustment table and simplified branches. Preserve its existing ledger receiver and later source-order admission; caller proof grants no child credit. [S5 evidence](../history/M2-T38-enemy-stream-initialization.md#s5-original-lakitu-spiny-proof).

- [ ] **Star-flag timer native-test assertion:** T39 S2 runs the unchanged endgame timer-tick assertion against both S1 and S2 shared objects; both fail with exit six on x86/x64. Other endgame groups, including fireworks animation/initializer/stream, pass independently. Keep AwardGameTimerPoints/NoTTick with existing M2 T19 S5 custody until the planned T41 actor slice; compare the source behavior before deciding whether the fixture or implementation is wrong. [S2 evidence](../history/M2-T39-special-initialization-and-dispatch.md#s2-original-fireworks-proof).

- [ ] **Retained Lakitu smoke Spiny-generation failure:** T39 S5 compares the
  same diagnostic assertion with S4 and S5 shared objects on x86/x64; all four
  fail at original lakitu_smoke.c line 76, before EndFrenzy. Preserve the
  existing Lakitu/Spiny source-order receivers. The nine initializer/frenzy
  matches grant no child or full-actor credit. [S5 proof](../history/M2-T39-special-initialization-and-dispatch.md#s5-original-small-initializer-and-frenzy-proof).

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
