# M2 T24 S1 - verification of 77 mapped nodes

## Result and evidence boundary

This is the initial 77-node snapshot. The later owner-expanded
[full evidence census](m2-t24-s1-full-node-census.md) includes all prior T/S
responsibilities and backfills 62 additional historical mappings. Its revision
note supersedes current-code claims for the subsequently changed fireball
files; the failures below remain evidence of the recorded snapshot only.

All 77 incoming nodes have an individual source/C/test/route disposition below:
**3 ROM-match complete, 19 mismatch-affected, 55 partial / evidence incomplete**.
The resulting project total is **3 / 1,992 (0.15%)**, with 74 audited pending
and 1,915 other open nodes. Audited is not synonymous with complete.

Admission forecast was eight named completions. Actual matches are
`PlayerOffscreenChk`, `PROfsLoop`, `NPROffscr`. The other five forecast labels
(`RelativePlayerPosition`, `RenderPlayerSub`, `DrawPlayerLoop`,
`DrawPlayer_Intermediate`, `PIntLoop`) fail D9, D6 or D7 below. No gameplay
repair is included. Partial nodes are deliberately not promoted on a passing
group smoke or an unrelated route. Parent/continuation labels marked mismatch
include the named broken behavior, not necessarily a different defect each.

The source mapping covers all 77 label/line pairs (72 code, five data). Every
instruction opcode in each local code span was checked against the owner ROM
at its reconciled address: unchanged early mapping and +0x24 in the late region.
Opcode alignment establishes address mapping, not semantic equivalence by itself.
The listing hash remains c8e91408db55341394f41000a6eeb6a9e804ab78c2172d2477ec278fe22e55df.
Both generated native 32 KiB PRG arrays were compared in full to the owner ROM;
they are identical. No ROM bytes, tables, trace payloads or executable data are
included in this report.

## Current-code and delivery identity

Git baseline: `45ec7767c11a5d3039dae7f0f1b53129bc8f4c08`.
Source fingerprint: `6c2e8257a4fe880c3ae331d5c2c5c7d43d3758f21ed133ece5b1d9c6d66418b5` (SHA-256 of sorted relative `src/**/*.c` and `src/**/*.h` names, tab, individual SHA-256, newline).

Both native build trees were checked with `cmake --build`; Ninja reported
no work needed. All nine focused tests in the owner table passed on x64 and
x86 (9/9 each). Current-header reference infrastructure was freshly compiled
under ignored audit output; a relocated stale reference archive initially
failed and was excluded. The normal CMake compiler probe/build stalled, so
the generated compile commands were executed directly for the 42 validation
objects; no sibling source or build tree was changed.

DOS16 was freshly compiled/linked with Build-OpenNt16Dos.ps1. Existing C4761
conversion warnings and the OLDNAMES.LIB linker warning remain; link succeeded.
All three local delivery files were refreshed before the audit-only clarification. Both Win32 --self-test
processes were explicitly waited for and returned zero.

| Artifact | SHA-256 |
| --- | --- |
| `mysmb16.exe` | `2355a6129ee55cdf38d5259b4faf50d0c3c31f53dc67be67fb3cc13351cd6b6d` |
| `mysmb32.exe` | `f905b63e301bd253c858601eacab5fb84586bfe4d7c14612916a80e36a4b05fc` |
| `mysmb64.exe` | `0cd85eeebdad62958481763bc9d8d506108ca6658f44c35ef4362aba7c877e5e` |

## Fresh source-reachable routes

All routes start from the original ROM and change controller input only. Each
record has 600 NMI-return samples. Native serial-button conversion is bit
reversal. PC counters are from the recorded window only, excluding warmup.
Zero-page and stack remain outside the existing frame-output equality contract;
direct routine probes additionally compare selected semantic state there.

| Route | Warmup NMIs | x86/x64 equal | Contracted output comparison |
| --- | ---: | --- | --- |
| title | 0 | yes | All work RAM, CPU OAM, CIRAM, palette, visible OAM, audio and PPU scalar fields equal. |
| mushroom | 0 | yes | All work RAM, CPU OAM, CIRAM, palette, visible OAM, audio and PPU scalar fields equal. |
| death | 600 | yes | All work RAM, CPU OAM, CIRAM, palette, visible OAM, audio and PPU scalar fields equal. |
| demo | 0 | yes | All work RAM, CPU OAM, CIRAM, palette, visible OAM, audio and PPU scalar fields equal. |
| fire-attempt | 0 | yes | All work RAM, CPU OAM, CIRAM, palette, visible OAM, audio and PPU scalar fields equal. |
| castle | 2220 | yes | work-ram: 1 samples, first 599; cpu-oam: 3 samples, first 553; oam: 3 samples, first 554; audio: 1 samples, first 599 |

The castle input is the existing project-local `area_prefix.inc` controller
sequence (SHA-256 8a88f7cdae75bdcbeebccd3e54a7439c1fa10aca4f1ba1be3e511f034b8de610),
not the separate movie-input probe. It reaches CastleObject five times and
StarFlagExit 52 times. Its residuals are not hidden or used as a clean certificate.
Neither the named fire-attempt route nor any other recorded route reaches
FireballObjCore, fireball/enemy collision, or hammer/player collision. The
first-mushroom route is not proof of mushroom pickup, growth, or Fire Mario.

Reproduction: the tracked reference recorder now accepts
`--pc-coverage=build/<task>/<route>-pc.csv`; invoke it with ROM path, output
trace, 600, initial buttons, controller script and optional --warmup.
Use `test/local_frame_recorder.c` with the corresponding native script,
--bootstrap-title and the same warmup. Compare with Compare-M2FrameTrace.ps1.
Exact scripts and neutral per-route hashes are in the route manifest below.
Audit harness sources, aggregate PC counts and neutral results are retained
under ignored `build/m2-t24-s1/`; new raw frame payloads are deleted after
summarization. Existing other-task traces are untouched.

## Paired direct-ROM probes

The audit-only node_probe.c calls the real ROM at each reconciled entry with
an explicit synthetic RAM/register fixture and bounded return (20,000 steps).
It compares the actual production C functions, including the static selector
through an audit-only include of player_gfx.c. RAM is cleared per case and the
return stack is reset per call. It is supplemental branch evidence, never
controller reachability. Separately compiled x86 and x64 probes give identical
neutral results. Known failure cases are evidence of defects, not passing tests.

| Probe | Cases | Differences |
| --- | ---: | ---: |
| DrawFireball frame phases | 32 | 16 |
| Fireball explosion states 0x80..0x86 | 7 | 6 |
| Swimming kick output, two sizes/eight phases | 16 | 8 |
| HandleChangeSize, two sizes/ten indices/four phases | 80 | 0 |
| ProcessPlayerAction, sizes/states/swim/index/timer/A matrix | 192 | 2 |
| Player offscreen rows, three Y pages/32 Y positions | 96 | 0 |

Additional single/pair probes prove the non-fiery fireball-step gate, both
Goomba/Koopa ID distinctions, intermediate sprite attributes, throwing timer,
and premature Player_Pos_ForScroll write. The 96 offscreen cases first compare
the real ROM GetPlayerOffscreenBits result, then the entire affected 32-byte
player OAM output. Together with clean recorded routes, exact code mapping,
branch successor counts, focused tests and delivery identities, this closes
the three offscreen labels only. It does not close PlayerGfxHandler.

## Mismatches and repair ownership

| ID | Reproduced difference | Owner and required follow-up |
| --- | --- | --- |
| D1 | With non-fiery status and an active fireball, ROM ProcFireball_Bubble leaves X=80; C advances it to 84. The ROM skips both slot updates on its first gate. | T20: preserve the composition gate, then controller-route proof. |
| D2 | Goomba is ID 6, Green Koopa ID 0. State-2 probes invert collision skip/hit; ROM score codes for IDs 6/0 are 1/2, C uses 2/1. | T17: fix both comparisons and incorrect collision-regression score expectations; sweep ID constants. |
| D3 | Frame 8 attribute ROM=0xc2/C=0x02; frame 16 ROM=0x02/C=0xc2. | T16: flip uses bit 3, not bit 4; correct the smoke expectation and test all phases. |
| D4 | Explosion sprite +4 Y is ROM=100/C=92; +8 Y is ROM=92/C=100. | T16/T20: restore column ordering and replace the self-confirming fixture. |
| D5 | Facing/size/tile-dependent swimming kick write is missing; eight of sixteen paired outputs differ. | T16: restore SwimKT/BigKTS/SwimKickTileNum continuation and swimming routes. |
| D6 | Throwing timer should become 5 from 6 with animation timer 5; C leaves 6. Nine OAM bytes differ; second three/four-row draw is absent. | T16/T20: restore timer/pose/row-count handoff and real Fire Mario route. |
| D7 | Intermediate bottom-right attributes read another sprite in ROM. Seeded source=3 yields ROM=0x43/C=0x40. | T16: preserve source attribute dependency and add the missing fixture. |
| D8 | Idle swimming with zero swim timer/index and no A should preserve index 0; C advances to 1. | T16/T23: restore the freeze branch and source swimming input route. |
| D9 | RelativePlayerPosition should leave seeded 0x0755=0xa5 unchanged; C overwrites it with relative X=0x50. | T16/T23: restore RenderPlayerSub ownership/order of that write and rerun scrolling routes. |

## C owners and focused test lanes

An owner entry identifies the current implementation/repair location; missing
branches in that file are explicitly called out below. Several ROM labels
are represented by one C function and are not invented as separate functions.

| Key | Current file and implementation | Repair owner | Focused tests |
| --- | --- | --- | --- |
| P | [src/game/oam/player_gfx.c](../../../src/game/oam/player_gfx.c): `mysmb_oam_draw_player / mysmb_oam_player_select_gfx / mysmb_oam_draw_intermediate_player` | T16 | mysmb.player-oam-smoke; mysmb.sprite-oam-smoke |
| R | [src/game/oam/object_position.c](../../../src/game/oam/object_position.c): `mysmb_oam_relative_player_position / mysmb_oam_relative_fireball_position / mysmb_oam_get_fireball_offscreen_bits` | T16 | mysmb.player-bounding-box-smoke; mysmb.fireball-oam-smoke; mysmb.bounding-box-clip-smoke |
| F | [src/game/fireball/fireball_core.c](../../../src/game/fireball/fireball_core.c): `mysmb_fireball_step / mysmb_fireball_get_bounding_box` | T20/T16 | mysmb.fireball-oam-smoke |
| S | [src/game/fireball/fireball_spawn.c](../../../src/game/fireball/fireball_spawn.c): `mysmb_fireball_try_spawn; composition in mysmb_fireball_step` | T20 | mysmb.fireball-oam-smoke |
| G | [src/game/oam/fireball_gfx.c](../../../src/game/oam/fireball_gfx.c): `mysmb_oam_draw_fireball / mysmb_oam_draw_fireball_explosion` | T16 | mysmb.fireball-oam-smoke |
| C | [src/game/world/collision.c](../../../src/game/world/collision.c): `mysmb_world_fireball_enemy_collision / mysmb_world_handle_fireball_enemy_hit / mysmb_world_stun_enemy` | T17 | mysmb.collision-regression-smoke |
| H | [src/game/objects.c](../../../src/game/objects.c): `mysmb_objects_check_hammer_collision` | T17 | mysmb.hammer-bro-oam-smoke |
| A | [src/game/area.c](../../../src/game/area.c): `mysmb_area_apply_parser_object` | T18 | mysmb.area-parser-column-smoke |
| E | [src/game/endgame_objects.c](../../../src/game/endgame_objects.c): `mysmb_objects_step_star_flags` | T19/T18 | mysmb.endgame-objects-smoke |

## Individual dispositions

PC counts below are entry executions (data rows have consumers instead).
Branch totals count local conditional instructions with both successors seen
over the six routes; an unconditional BNE idiom is not expected to have both
outcomes. This numeric column alone never proves semantic equivalence.
Partial means inspected/tested to the stated limit, not verified complete.

| Node / ROM address | Owner/test key | Source-route entry hits | Branches both/total | Disposition and source/write audit |
| --- | --- | --- | --- | --- |
| <a id="node-castleobject"></a>`CastleObject` / `$9806` | A | castle=5 | 0/0 | **partial**. Length/row initialization and five-column metatile path inspected; castle route enters 5 times, but has output residuals; tall/all-slots-full continuations still need clean evidence. |
| <a id="node-procfireball_bubble"></a>`ProcFireball_Bubble` / `$b624` | S | castle=600, death=434, demo=574, fire-attempt=407, mushroom=407, title=420 | 0/7 | **mismatch D1**. C always steps two slots after spawn rejection; ROM non-fiery gate skips the slot loop. Active slot advances X in C only (D1). |
| <a id="node-fireballobjcore"></a>`FireballObjCore` / `$b689` | F | none | 0/3 | **partial**. Spawn, gravity, relative/offscreen, box and collision order inspected. Zero controller-route entries; downstream draw/explosion mismatches D3/D4 block closure. |
| <a id="node-starflagexit"></a>`StarFlagExit` / `$d311` | E | castle=52 | 0/0 | **partial**. ROM return maps to task-zero/task>=5 continue with no OAM write. 52 castle entries; no clean castle comparison or sixth-slot dispatch proof. |
| <a id="node-fireballenemycollision"></a>`FireballEnemyCollision` / `$d6d9` | C | none | 0/3 | **partial**. State/d7/even-frame gates and box selection inspected. No controller-route entry; Goomba filter in the called scan has D2. |
| <a id="node-fireballenemycdloop"></a>`FireballEnemyCDLoop` / `$d6ee` | C | none | 0/4 | **partial**. Descending slots 4..0 and continuing after hit are present. No route hit; state/flag/ID/offscreen filters require source-reachable branch evidence. |
| <a id="node-goombadie"></a>`GoombaDie` / `$d706` | C | none | 0/2 | **mismatch D2**. ROM compares Goomba ID 6; C compares 0. Paired state-2 probes invert hit/skip for IDs 0 and 6 (D2). |
| <a id="node-notgoomba"></a>`NotGoomba` / `$d710` | C | none | 0/2 | **partial**. Masked offscreen gate, enemy-box selection and collision handoff inspected. Directed box smoke exists; no controller-route hit. |
| <a id="node-noftoecol"></a>`NoFToECol` / `$d72c` | C | none | 0/1 | **partial**. Fireball box restoration and descending loop represented by C locals/loop. No source-reachable hit/miss scan evidence. |
| <a id="node-exitfballenemy"></a>`ExitFBallEnemy` / `$d733` | C | none | 0/0 | **partial**. Return/current-slot handoff uses C slot argument. No controller route reaches the fireball collision exit. |
| <a id="node-bowseridentities"></a>`BowserIdentities` / `$d736` | C | data consumer | 0/0 | **partial**. Eight replacement IDs match the ROM table in source order. No controller-reachable Bowser defeat consuming the table. |
| <a id="node-handleenemyfballcol"></a>`HandleEnemyFBallCol` / `$d73e` | C | none | 0/2 | **partial**. Relative coordinates and Bowser proxy-slot selection inspected. Synthetic helper smoke only; score descendant has D2 and no controller-route hit. |
| <a id="node-chkbuzzybeetle"></a>`ChkBuzzyBeetle` / `$d752` | C | none | 0/2 | **partial**. Buzzy immunity and Bowser dispatch present. No source-reachable immunity/Bowser branch comparison. |
| <a id="node-hurtbowser"></a>`HurtBowser` / `$d75c` | C | none | 0/2 | **partial**. HP decrement, vertical reset, frenzy clear and replacement ID/state inspected. Synthetic Bowser case is not a source-reachable defeat route. |
| <a id="node-setdbste"></a>`SetDBSte` / `$d77d` | C | none | 0/1 | **partial**. World-dependent defeated state, Bowser-fall queue and score-9 handoff inspected. No controller-route evidence for either world-state branch. |
| <a id="node-chkotherenemies"></a>`ChkOtherEnemies` / `$d789` | C | none | 0/3 | **partial**. Bullet Bill, Podoboo and ID>=0x15 exclusions present. Directed fixtures do not supply the missing original-controller routes. |
| <a id="node-shellorblockdefeat"></a>`ShellOrBlockDefeat` / `$d795` | C | none | 0/1 | **partial**. Piranha carry-preserving Y+0x19 and stun handoff inspected; directed Piranha regression passes. No original-controller entry. |
| <a id="node-stne"></a>`StnE` / `$d7a1` | C | none | 0/1 | **partial**. Stun, defeat bit and Hammer Bro score selection inspected. No original-controller hit; downstream Goomba score has D2. |
| <a id="node-goombapoints"></a>`GoombaPoints` / `$d7b6` | C | none | 0/1 | **mismatch D2**. ROM selects score 1 for ID 6 and 2 for ID 0; C reverses these. Existing synthetic score expectation is wrong (D2). |
| <a id="node-enemysmackscore"></a>`EnemySmackScore` / `$d7bc` | C | none | 0/0 | **partial**. Floatey setup then queue 0x08 inspected. Helper test runs, but no original-controller hit and upstream score selection differs. |
| <a id="node-exhcf"></a>`ExHCF` / `$d7c3` | C | none | 0/0 | **partial**. Early immunity/remaining-HP returns and final return mapped. No source-reachable exit evidence. |
| <a id="node-playerhammercollision"></a>`PlayerHammerCollision` / `$d7c4` | H | none | 0/5 | **partial**. Odd-frame and TimerControl|offscreen gates, previous bounding box, one-shot flag, speed reversal and injury inspected. Hammer fixture passes; no controller-route hit. |
| <a id="node-clhcol"></a>`ClHCol` / `$d7fa` | H | none | 0/0 | **partial**. No-hit path clears per-hammer collision flag. Synthetic coverage only; no source-reachable miss case. |
| <a id="node-exphc"></a>`ExPHC` / `$d7ff` | H | none | 0/0 | **partial**. Frame/timer/offscreen/already-hit/star exits map to C returns. No controller route reaches this exit. |
| <a id="node-getfireballboundbox"></a>`GetFireballBoundBox` / `$e22d` | F | none | 0/1 | **partial**. Owner corrected to fireball_core.c; slots use controls 0x04a0/1 and boxes 0x04c8/cc with fixed relative inputs. Directed slot tests pass; no original route. |
| <a id="node-drawfireball"></a>`DrawFireball` / `$ecde` | G | none | 0/0 | **mismatch D3**. ROM flip carry uses FrameCounter bit 3; C uses bit 4. 16/32 paired cases differ (D3). |
| <a id="node-drawexplosion_fireball"></a>`DrawExplosion_Fireball` / `$ed09` | G | none | 0/1 | **mismatch D4**. State progression agrees, but C swaps second/third sprite Y rows versus ROM. 6/7 paired cases differ (D4). |
| <a id="node-playergraphicstable"></a>`PlayerGraphicsTable` / `$ee17` | P | data consumer | 0/0 | **partial**. Both generated native PRG arrays match owner ROM, including the full 208-byte table. Drawing consumers execute; full action/size/swim consumer coverage remains incomplete. |
| <a id="node-swimkicktilenum"></a>`SwimKickTileNum` / `$eee7` | P | data consumer | 0/0 | **mismatch D5**. ROM two-tile kick table has no equivalent kick consumer in current C (D5); a mapped data label does not prove its use. |
| <a id="node-playergfxhandler"></a>`PlayerGfxHandler` / `$eee9` | P | castle=600, death=434, demo=574, fire-attempt=407, mushroom=407, title=420 | 0/2 | **mismatch D5**. Injury alternation is present, but swimming kick continuation is missing. 8/16 swim-output probes differ (D5); source injury alternatives also lack route coverage. |
| <a id="node-cntpl"></a>`CntPl` / `$eef3` | P | castle=600, death=434, demo=574, fire-attempt=407, mushroom=407, title=420 | 1/6 | **mismatch D5**. Killed/size dispatch exists; swimming-state call/return and frame-bit-2 kick continuation are missing (D5). |
| <a id="node-swimkt"></a>`SwimKT` / `$ef1f` | P | none | 0/2 | **mismatch D5**. Facing-selected sprite, size and replacement-tile gate have no C continuation (D5). |
| <a id="node-bigkts"></a>`BigKTS` / `$ef2d` | P | none | 0/0 | **mismatch D5**. ROM writes selected kick tile to sprite 7/8; C never makes this write (D5). |
| <a id="node-expgh"></a>`ExPGH` / `$ef33` | P | none | 0/0 | **partial**. Injury/kick exit represented by returns, but no controller PC hit; missing swimming predecessor D5 prevents complete exit-path evidence. |
| <a id="node-findplayeraction"></a>`FindPlayerAction` / `$ef34` | P | castle=600, death=192, demo=574, fire-attempt=407, mushroom=407, title=365 | 0/0 | **partial**. Action selection followed by drawing is mapped; shared ProcessPlayerAction has D8 and drawing has D6. Wrapper is not independently complete. |
| <a id="node-dochangesize"></a>`DoChangeSize` / `$ef3a` | P | none | 0/0 | **partial**. HandleChangeSize then graphics handoff mapped; 80 controlled size cases agree. No source-reachable size-change entry. |
| <a id="node-playerkilled"></a>`PlayerKilled` / `$ef40` | P | death=242, title=55 | 0/0 | **partial**. Death offset 14 selected and death route output agrees. Retained partial: independent killed-entry interaction with the shared throwing/attribute path is not certified. |
| <a id="node-playergfxprocessing"></a>`PlayerGfxProcessing` / `$ef45` | P | castle=600, death=434, demo=574, fire-attempt=407, mushroom=407, title=420 | 0/3 | **mismatch D6**. FireballThrowingTimer compare/clear/restore and second throw-pose rendering are absent. ROM timer 5 versus C 6, with 9 OAM differences (D6). |
| <a id="node-supdr"></a>`SUpdR` / `$ef76` | P | none | 0/0 | **mismatch D6**. ROM selects three/four rows for the second throw rendering; C has no second rendering (D6). |
| <a id="node-playeroffscreenchk"></a>`PlayerOffscreenChk` / `$ef7a` | P | castle=600, death=434, demo=574, fire-attempt=407, mushroom=407, title=420 | 0/0 | **ROM-match complete**. Vertical nibble, starting OAM offset +24 and four-row setup match. Full local block executed; 96 paired offscreen cases and clean title/mushroom/death/demo routes agree. |
| <a id="node-profsloop"></a>`PROfsLoop` / `$ef8c` | P | castle=2400, death=1736, demo=2296, fire-attempt=1628, mushroom=1628, title=1680 | 1/1 | **ROM-match complete**. Both bit-test outcomes executed in clean routes; only selected row Ys are set to 0xf8. All 96 paired vertical cases agree. |
| <a id="node-nproffscr"></a>`NPROffscr` / `$ef95` | P | castle=2400, death=1736, demo=2296, fire-attempt=1628, mushroom=1628, title=1680 | 1/1 | **ROM-match complete**. Subtract-eight row walk and loop/exit both executed; four-row termination and unaffected OAM bytes agree in the 96 paired cases. |
| <a id="node-intermediateplayerdata"></a>`IntermediatePlayerData` / `$ef9e` | P | data consumer | 0/0 | **partial**. Fixed coordinates/facing/attributes/row count represented by C locals. Consumer runs, but its final attribute-source discrepancy D7 blocks consumer certification. |
| <a id="node-drawplayer_intermediate"></a>`DrawPlayer_Intermediate` / `$efa4` | P | death=1, fire-attempt=1, mushroom=1, title=1 | 0/0 | **mismatch D7**. ROM copies attributes from the following sprite before OR 0x40; C reuses destination attributes. Seeded source=3 gives ROM 0x43, C 0x40 (D7). |
| <a id="node-pintloop"></a>`PIntLoop` / `$efa6` | P | death=6, fire-attempt=6, mushroom=6, title=6 | 1/1 | **mismatch D7**. Six scratch values are represented as constants/locals, but the continuation through final attribute store has D7. |
| <a id="node-renderplayersub"></a>`RenderPlayerSub` / `$efbe` | P | castle=600, death=434, demo=574, fire-attempt=407, mushroom=407, title=420 | 0/0 | **mismatch D6**. Scroll copy and four-row path observed; source accepts caller-provided row count, while C has no three-row throw rendering (D6). |
| <a id="node-drawplayerloop"></a>`DrawPlayerLoop` / `$efdc` | P | castle=2400, death=1740, demo=2296, fire-attempt=1632, mushroom=1632, title=1684 | 1/1 | **mismatch D6**. Normal four-row loop executes, but source variable-row call contract is not implemented for the throw continuation (D6). |
| <a id="node-processplayeraction"></a>`ProcessPlayerAction` / `$efec` | P | castle=600, death=192, demo=574, fire-attempt=407, mushroom=407, title=365 | 3/5 | **mismatch D8**. State/size selector checked with 192 paired cases; 2 idle-swim cases differ because the animation freeze path is missing (D8). |
| <a id="node-procongroundacts"></a>`ProcOnGroundActs` / `$f00b` | P | castle=229, death=191, demo=574, fire-attempt=291, mushroom=287, title=365 | 3/4 | **partial**. Crouch/stand/walk/skid selector inspected. The action matrix uses speed 8; high-speed skid and crouch need paired branch-specific cases and clean routes. |
| <a id="node-nonanimatedacts"></a>`NonAnimatedActs` / `$f028` | P | castle=346, death=3, demo=478, fire-attempt=171, mushroom=125, title=176 | 0/0 | **partial**. Animation reset and size-adjusted offset agree in sampled action cases. Crouch/skid alternatives and full caller coverage are still missing. |
| <a id="node-actionfalling"></a>`ActionFalling` / `$f034` | P | castle=23, mushroom=22 | 0/0 | **partial**. Retained animation index matches controlled falling cases and 22 mushroom entries. Big-player falling is only observed in the residual-bearing castle route. |
| <a id="node-actionwalkrun"></a>`ActionWalkRun` / `$f03c` | P | castle=229, death=189, demo=96, fire-attempt=236, mushroom=260, title=189 | 0/0 | **partial**. Offset 4 and extent 3 agree in sampled cases. Big-player walk/run has no clean original route certificate. |
| <a id="node-actionclimbing"></a>`ActionClimbing` / `$f044` | P | castle=2 | 0/1 | **partial**. Moving/stationary split inspected and controlled moving case agrees. Only 2 castle entries with one branch outcome; clean/stationary route missing. |
| <a id="node-actionswimming"></a>`ActionSwimming` / `$f050` | P | none | 0/2 | **mismatch D8**. ROM freezes animation when JumpSwimTimer, animation index and A are zero; C advances it. Two paired cases fail (D8). |
| <a id="node-getcurrentanimoffset"></a>`GetCurrentAnimOffset` / `$f062` | P | castle=254, death=189, demo=96, fire-attempt=236, mushroom=282, title=189 | 0/0 | **partial**. Retained animation index mapped into local arithmetic. Walk/fall observed, but clean climbing/swimming caller evidence missing. |
| <a id="node-fourframeextent"></a>`FourFrameExtent` / `$f068` | P | castle=229, death=189, demo=96, fire-attempt=236, mushroom=260, title=189 | 0/0 | **partial**. Extent value 3 matches controlled walk/swim cases. Shared swimming predecessor is incorrect and has no source route. |
| <a id="node-threeframeextent"></a>`ThreeFrameExtent` / `$f06d` | P | castle=2 | 0/0 | **partial**. Extent value 2 matches controlled moving-climb cases. Only residual-bearing castle route reaches it. |
| <a id="node-animationcontrol"></a>`AnimationControl` / `$f06f` | P | castle=231, death=189, demo=96, fire-attempt=236, mushroom=260, title=189 | 2/2 | **partial**. Pre-update offset, timer reload, increment and wrap inspected; both local branches execute. Extent-2 climbing and swimming still lack clean source-route certificates. |
| <a id="node-setanimc"></a>`SetAnimC` / `$f08c` | P | castle=57, death=45, demo=21, fire-attempt=77, mushroom=54, title=45 | 0/0 | **partial**. Animation-index write agrees in sampled matrix and walk routes. Caller-specific climb/swim coverage remains incomplete. |
| <a id="node-exanimc"></a>`ExAnimC` / `$f08f` | P | castle=231, death=189, demo=96, fire-attempt=236, mushroom=260, title=189 | 0/0 | **partial**. Pre-update graphics offset return represented by C local value. Remaining climb/swim callers have no clean certificate. |
| <a id="node-getgfxoffsetadder"></a>`GetGfxOffsetAdder` / `$f091` | P | castle=600, death=192, demo=574, fire-attempt=407, mushroom=407, title=365 | 1/1 | **partial**. Size-zero/no-add versus +8 matches both-size controlled cases. Big-size controller branch appears only on castle route with residuals. |
| <a id="node-szofs"></a>`SzOfs` / `$f09b` | P | castle=600, death=192, demo=574, fire-attempt=407, mushroom=407, title=365 | 0/0 | **partial**. Return of adjusted selector is mapped; lacks clean big-player caller route despite paired selector agreement. |
| <a id="node-changesizeoffsetadder"></a>`ChangeSizeOffsetAdder` / `$f09c` | P | data consumer | 0/0 | **partial**. All 20 entries exercised through 80 valid size-change probes and agree. No controller route reaches the size-change consumer. |
| <a id="node-handlechangesize"></a>`HandleChangeSize` / `$f0b0` | P | none | 0/2 | **partial**. Both sizes, indices 0..9 and frame phases 0..3 pass 80 paired cases. No source-reachable grow/shrink entry. |
| <a id="node-csznext"></a>`CSzNext` / `$f0c3` | P | none | 0/0 | **partial**. Animation index update/wrap agrees in the 80 size cases; no controller route executes the write. |
| <a id="node-gorslog"></a>`GorSLog` / `$f0c6` | P | none | 0/1 | **partial**. Big/small growth/shrink dispatch agrees in the 80 size cases; no original-controller entry. |
| <a id="node-getoffsetfromanimctrl"></a>`GetOffsetFromAnimCtrl` / `$f0d0` | P | castle=254, death=189, demo=96, fire-attempt=236, mushroom=282, title=189 | 0/0 | **partial**. Shift-by-three/table addition agrees for tested reachable animation indices. Size-change/climb/swim callers still lack clean source routes. |
| <a id="node-shrinkplayer"></a>`ShrinkPlayer` / `$f0d7` | P | none | 0/1 | **partial**. Ten-entry index shift and frame selector agree in controlled shrink cases. No controller-driven shrink sequence. |
| <a id="node-shrplf"></a>`ShrPlF` / `$f0e5` | P | none | 0/0 | **partial**. Selected graphics-offset read agrees in controlled shrink cases. No source-reachable shrink return. |
| <a id="node-chkforplayerattrib"></a>`ChkForPlayerAttrib` / `$f0e9` | P | castle=600, death=434, demo=574, fire-attempt=407, mushroom=407, title=420 | 2/5 | **partial**. Killed/crouch/standing/size-offset dispatch inspected. Only 2/5 local branches have both route outcomes; grow/crouch alternatives remain unproven. |
| <a id="node-killedatt"></a>`KilledAtt` / `$f105` | P | death=242, title=55 | 0/0 | **partial**. Third-row flip masks agree on death route and c8 synthetic fixture. Source-reachable c8 growth caller is absent. |
| <a id="node-c_s_igatt"></a>`C_S_IGAtt` / `$f117` | P | death=244, demo=478, fire-attempt=27, mushroom=27, title=231 | 0/0 | **partial**. Fourth-row flip masks agree for standing/death output. Crouch and c0/c8 size-transition source routes remain missing. |
| <a id="node-explyrat"></a>`ExPlyrAt` / `$f129` | P | castle=600, death=434, demo=574, fire-attempt=407, mushroom=407, title=420 | 0/0 | **partial**. Return after attribute writes maps to C exit. Missing attribute-dispatch alternatives prevent complete caller evidence. |
| <a id="node-relativeplayerposition"></a>`RelativePlayerPosition` / `$f12a` | R | castle=1200, death=851, demo=1146, fire-attempt=810, mushroom=810, title=821 | 0/0 | **mismatch D9**. Relative XY agrees, but C additionally writes Player_Pos_ForScroll 0x0755, owned by RenderPlayerSub in ROM. Seeded ROM 0xa5 becomes C 0x50 (D9). |
| <a id="node-relativefireballposition"></a>`RelativeFireballPosition` / `$f13b` | R | none | 0/0 | **partial**. Fixed XY destinations and per-slot sources inspected; slot-one smoke passes. No source-reachable fireball entry. |
| <a id="node-getplayeroffscreenbits"></a>`GetPlayerOffscreenBits` / `$f180` | P | castle=1200, death=851, demo=1146, fire-attempt=810, mushroom=810, title=821 | 0/0 | **partial**. 96 paired vertical cases agree; duplicated C helper is called inside drawing, while ROM also calls it before injury gating. Full call-order and horizontal edge proof remain. |
| <a id="node-getfireballoffscreenbits"></a>`GetFireballOffscreenBits` / `$f187` | R | none | 0/0 | **partial**. Slot offset +7/+8, fixed destination and nibble merge inspected; boundary smoke passes. No original-controller fireball entry. |

## Route manifest

- **title**: reference script `0:0,200:8,201:0,240:128,310:129,340:128`; warmup 0; reference SHA-256 `596d094792657747a1535efa749347294603d146a81eacf6822f3dc4f1955acf`; native x86/x64 SHA-256 `d06be2916b12991d47e1f3e3ca45bd3d0eb390c39b3f6b911d0511dd5d64c8e6`; aggregate-PC SHA-256 `fae641c31cb85588602892da8e7f72a1b1f225fd516066b1acc43afac1e65e68`.
- **mushroom**: reference script `0:0,40:8,42:0,220:128,300:129,342:128,390:129,432:128`; warmup 0; reference SHA-256 `177d1c705cb770c1cef07d19a28add27a90b888487684d19c2a858f697f7691a`; native x86/x64 SHA-256 `f080881fa7c12e86b08d7d840abebd268aede8e6c4c6414ae24a61b70c44e94a`; aggregate-PC SHA-256 `668b08f333722c0d346659e05fee3e0dd3436c70a386a583759927091ed9b868`.
- **death**: reference script `0:0,200:8,201:0,240:128,310:129,340:128`; warmup 600; reference SHA-256 `a64a98563ee1ad6b2cceb361a9da8bdb45d72830d37b0ac18e886c86dd0cca98`; native x86/x64 SHA-256 `8af83c38b0a313705ff2d82ca169cc18dd997d10f61a73628073d9126d4bf906`; aggregate-PC SHA-256 `c392f4c93594458efc775659d7ae3085a65e88fc49102af906593930d0588f36`.
- **demo**: reference script `0:0`; warmup 0; reference SHA-256 `d27180500ae7f5d3bba097053867f0620cb9527887122606409e44134836c809`; native x86/x64 SHA-256 `5eb877723dbf53c1da3ce31061793c1439883c403fe7009803f59c35bffe51d8`; aggregate-PC SHA-256 `c367ba3f9860d9218bc183e21c2859def15b88e3c31b8aeb50b6e8d596384dd7`.
- **fire-attempt**: reference script `0:0,40:8,42:0,220:130,260:131,276:130,346:131,354:66,410:67,440:130,510:131,535:130`; warmup 0; reference SHA-256 `f14e22b430b214a695e144075bea20fb35062179bc9dd63a2c6a279d552501f7`; native x86/x64 SHA-256 `8fd218d44dcfa9776ffe9009f371ff5d71d4c7925963457c59199f582f04c58b`; aggregate-PC SHA-256 `b2a32ebe095a6400beebb2484b981542a453e5b5f00b3d58a2564dca8fd661a9`.
- **castle**: reference script `0:0,40:8,42:0,220:130,260:131,276:130,346:131,354:66,410:67,440:130,510:131,535:130,720:129,752:128,820:129,852:128,920:129,952:128,1020:129,1052:128,1160:131,1192:130,1300:131,1332:66,1380:130,1422:131,1454:130,1490:131,1522:130,1580:131,1612:130,1690:131,1722:130,1790:131,1822:130,1890:131,1922:130,1990:131,2160:130,2161:131,2184:130,2185:131,2208:130,2209:131,2232:130,2233:131,2256:130,2257:131,2259:130,2274:131,2291:130,2320:131,2430:130,2433:131,2450:130,2460:131,2520:130,2536:131,2600:130,2616:131,2690:130,2706:131,2780:130,2802:131,2819:130,2820:66`; warmup 2220; reference SHA-256 `159f01130e5e51b1d6f5f919c996e51912f083c2a9173776f3061c7f774049f7`; native x86/x64 SHA-256 `6afbaa136fd2f7ef9468cac37538b8b2c95b851214eb02030d2d44a796887e02`; aggregate-PC SHA-256 `a5f0ad7398d3a58db4928267b3e25e59005291bc25c9e4f7da476a8138f4b469`.

## Review and closure

All 77 rows are bound to this audit. The three completions and all 74 deferred labels are named above; owner/test keys assign each deferral. New matching count is 3, not 77. The owner-expanded census and progress report carry later mapping/revalidation states. No gameplay repair is included. Raw trace payloads are removed after summarization; no raw program data is included in these Markdown reports. Existing tracked local assets are not publication or conformance evidence, and no commit is made by this audit.
