# M2 T26: Victory, terminal modes and floating scores

## Exact node contract

T26 is the source-order successor to T25. It owns the 32 inventory labels
from ROM lines 1137--1363; `ScreenRoutines` at line 1386 belongs to T27. All
32 labels are presently received by historical `M2 T15 S4`. T26 S1 audits
them without changing that receipt; only T26 S2 may accept the exact transfer.

| Source group | Exact labels |
| --- | --- |
| Victory dispatch and walking | `VictoryMode`, `AutoPlayer`, `VictoryModeSubroutines`, `SetupVictoryMode`, `PlayerVictoryWalk`, `PerformWalk`, `DontWalk`, `ExitVWalk` |
| Victory messages | `PrintVictoryMessages`, `MRetainerMsg`, `ThankPlayer`, `SecondPartMsg`, `EvalForMusic`, `PrintMsg`, `IncMsgCounter`, `SetEndTimer`, `IncModeTask_A`, `ExitMsgs` |
| End-world transition | `PlayerEndWorld`, `EndExitOne`, `EndChkBButton`, `EndExitTwo` |
| Floating-score data and actor | `FloateyNumTileData`, `ScoreUpdateData`, `FloateyNumbersRoutine`, `ChkNumTimer`, `DecNumTimer`, `LoadNumTiles`, `ChkTallEnemy`, `GetAltOffset`, `FloateyPart`, `SetupNumSpr` |

`VictoryMode` calls `VictoryModeSubroutines`, conditionally enters the shared
enemy loop, then calls the later player/OAM chain. T26 owns only its terminal
branches and outputs. `PlayerGfxHandler`, player movement, scrolling, area
pointers, enemy loop, score arithmetic, OAM primitives, audio handlers and
termination are named collaborators owned by their received source slices.
No platform adapter may read or write terminal game state.

## S plan

| S | Role | ROM-logic evidence | Operational evidence | Forecast |
| --- | --- | --- | --- | --- |
| S1 | Audit all 32 labels, source calls, RAM/table reads/writes, native boundary and dependency owners. | Listing graph and per-label write map. | Ledger admission and documentation gate. | 0 |
| S2 | Accept the 32 labels and migrate only terminal dispatch/message/end-world ownership. | Source-order branch/table review. | Focused tests, x86/x64, DOS16, purity, three artifacts. | 0 |
| S3 | Complete floating-score table/actor route within its received terminal collaboration boundary. | Table and OAM/write-order review. | Focused actor tests and controlled frame route. | 0 |
| S4 | Establish ROM logic equivalence through source-reachable victory, end-world and B-enable routes. | Branches, writes, callees and controlled/reachable ROM routes. | Cross-width traces and required builds. | Up to 32 |
| S5 | Close only labels proven by both tracks; transfer every unresolved label to an accepted successor. | Per-label source disposition. | Final gates and three artifacts. | Up to 32 |
| S6 | Restore only the source-owned outer VictoryMode call order. | Compare `VictoryMode`'s task-zero/nonzero branch order and named existing collaborators. | Focused root tests, cross-width builds, DOS16, purity, three artifacts. | 0 |
| S7 | Independently compare the repaired outer victory route. | Source-reachable or controlled full-domain ROM route for `VictoryMode` and `AutoPlayer`. | Cross-width traces, DOS16, purity, three artifacts. | Up to 2 |

## Chain-delivery amendment

The S1--S7 entries above are retained as historical evidence.  Any successor
admission or retained-node repair uses the [M2 chain-delivery rule](../../rules/EXECUTION.md#m2-chain-based-s-delivery): it groups only a contiguous
victory, message, end-world or floating-score call/data chain that has one C
owner and one ROM route.  It still records each label separately and performs
one chain-level replay, three-target package and closure update.  The chain
also performs source mapping, any shared-C repair, and both independent
acceptance tracks: ROM control/data/call parity and operational execution.
No build, replay, or visible route can substitute for the source comparison.

## S1 source-contract obligations

The audit begins from `VictoryMode` at line 1137 and must distinguish direct
terminal behavior from collaborators. It records the five task vectors, the
`PlayerVictoryWalk` scroll call chain, every message-table selector and
counter increment, the `PlayerEndWorld` world transition, and the `$07fc`
write in `EndChkBButton`. The floating-score subtree must retain its source
`ObjectOffset` and OAM-offset call contracts rather than duplicate score or
sprite logic in terminal code. S1 produces no node credit and no product
change.

## S1 source-contract audit result

The 32 labels resolve to two shared-C boundaries. `terminal_modes.c`
`mysmb_game_step_victory` carries the five-vector terminal tree: task zero
delegates `BridgeCollapse`; tasks one through four carry `SetupVictoryMode`,
the `PlayerVictoryWalk` leaves, `PrintVictoryMessages` and `PlayerEndWorld`.
`objects.c` `mysmb_objects_step_floatey_number` carries the two local tables
and `FloateyNumbersRoutine` through `SetupNumSpr`. `frame_root.c` is only the
source `VictoryMode` outer-call owner: it invokes the terminal vector, then
the separately received enemy/relative/player-OAM collaborators.

The direct external dependencies are recorded rather than absorbed: bridge
collapse and retainer actor work; `EnemiesAndLoopsCore`; relative/player OAM;
`AutoControlPlayer` and scrolling; `UpdScrollVar`; `LoadAreaPointer`;
`TerminateGame`/player transpose; score arithmetic and status queuing; and
the two-sprite OAM primitive. Their respective source slices retain their
receipts. T26 may call their existing shared interfaces but must not duplicate
their rules.

Two source-order discrepancies are confirmed for a later T26 implementation
receipt. First, ROM `PlayerEndWorld` only tests `WorldEndTimer`; NMI
`DecTimers` decrements it before the mode tree. The current terminal owner
decrements `$07a1` itself, which is not a source write. Second, ROM
`EndChkBButton` ORs `SavedJoypad1Bits` and `SavedJoypad2Bits` before masking
B, while the current terminal branch consults only `$06fc`. These are T26
owned findings, but S1 intentionally makes no production repair and grants no
node credit. The next S2 receipt will accept all 32 labels and address only
the confirmed terminal-owned behavior.

## S2 implementation result

S2 restored the audited `PlayerEndWorld` and `EndChkBButton` branches in the
shared `terminal_modes.c` owner. `PlayerEndWorld` now observes
`WorldEndTimer` and returns when it is nonzero; it no longer decrements that
timer. `frame_root.c` retains the preceding NMI `DecTimers` ownership. A
focused route starts with `WorldEndTimer = 1` and an interval-timer rollover:
the NMI decrements it to zero, then the same frame enters the next-world
transition. This establishes the ROM's timer write/order without a platform
special case.

`EndChkBButton` now ORs saved joypad latches `$06fc` and `$06fd` before the B
mask. Its taken branch follows `TerminateGame`: it writes Silence to the
event-music queue, sets the world-select flag and current-player lives, then
either resumes the transposed player through the existing shared collaborator
or writes `ContinueWorld`, `OperMode_Task`, `ScreenTimer`, and `OperMode` for
the title return. A focused regression drives B only through `$06fd` and
checks every title-return write.

The code change is restricted to shared game logic and `test/mode_smoke.c`.
The similar-issue sweep covered every terminal `WorldEndTimer` decrement and
every terminal saved-joypad consumer; no other production hit requires a
change. `TerminalModes` remains independent of Win32 and DOS adapters.

Operational evidence for P1: strict C90 x64 and x86 core builds passed the
mode, floatey-OAM and local-area focused harnesses; both native Windows
artifacts passed `--self-test`; the OpenNT large-model DOS build linked; and
the platform-purity gate passed. The refreshed artifact hashes are
`mysmb16.exe` `9C33EBC49CEDAA75CCEFE9477D98320D602DDBCF0D89EDE24DB8811C60473FAC`,
`mysmb32.exe` `00B5E222ACD2DEC9A012DAA22B2EB2F98B036FB0A5594E99BDD224C6E67D3E86`,
and `mysmb64.exe` `007FD8366AF77D0F10C1796A71698EC7AB28D6560116DC3DC02ADFA69AA862AB`.
The expected and actual ROM-match sets remain empty in S2: source repair and
operational proof do not claim the later S4 route-equivalence credit.

## S2 closure and S3 receipt

S2 closed with zero new ROM-match labels after transferring the ten
floating-score labels to S3 and the remaining 22 terminal labels to S4 for
route-equivalence integration. S3 begins with `FloateyNumbersRoutine`:
`objects.c` already preserves the source control clamp, timer-zero clear,
pre-decrement `$2b` score/1-UP test, normal-versus-alternate OAM selection,
carry-sensitive vertical coordinate, and two-sprite tile/attribute/X order.
The S3 focused fixture additionally covers the out-of-range-control clamp and
the status-boundary carry path. Score arithmetic and OAM allocation remain
existing named collaborators rather than being duplicated here.

## S3 closure and S4 unified receipt

S3 completed its zero-credit source-order audit of the ten floating-score labels. The tables match byte-for-byte; `FloateyNumbersRoutine` preserves the ROM control/timer/read/write sequence and delegates only existing score and OAM primitives. The focused fixture covers ordinary output, the `$2b` score and 1-UP branch, alternate OAM selection, and the `$0c` control clamp/status-boundary carry path. S3 transfers all ten labels to S4, which now holds all 32 T26 labels for the only credit-bearing route-equivalence decision.

## S4 controlled floating-score route record

The S4 reference recorder builds the MyNES core graph in an isolated ignored
directory; it does not configure, link, or run the MySMB product through an
emulator. Its input is the owner-supplied local SMB1 NROM, which remains a
local research input. The recorder writes bounded four-sample raw traces only
below `build/`; raw traces are deleted after the recorded result is reduced to
this neutral evidence statement.

The fixed `t26-floatey-oneup` precondition is intentionally narrower than the
existing one-address branch hook. After sixty ordinary NMI boundaries, it sets
the source GameMode/GameCoreRoutine route, suppresses new enemy-stream input,
and prepares slot zero with the ROM's `$0b` floating-number control, `$2b`
timer, position, sprite offset and life count. It does not expose an arbitrary
multi-write product interface. The identical named fixture is applied before
the corresponding shared-C tick.

Across the four controlled frames, the ROM and shared C agree on the
floating-number control, timer decrement, X/Y evolution, parser-task cadence,
the `$2b` 1-UP life increment, and the square-two sound queue. The native
player collaborator changes `GameEngineSubroutine` during the same incomplete
scene, and the ROM's full OAM route overwrites the controlled slot before its
visible-OAM sample. Therefore this route is evidence for the floating-score
state transition only; it is not an OAM or whole-frame equivalence claim.
S4 retains all 32 labels with zero ROM-match credit until source-reachable
victory, end-world and complete OAM routes establish both required tracks.

The companion `t26-endworld-b` precondition reaches `PlayerEndWorld` at
world eight with its timer expired. The reference controller is held at the
ROM serial-B value throughout the bounded run, because the source NMI owns
the saved-controller latches; the native recorder receives the corresponding
decoded B mask. Their first post-branch NMI sample agrees on the complete
terminal write set: world-select enable, lives `$ff`, Silence event queue,
continue world, screen timer, and title mode/task. The existing focused mode
smoke separately covers the second-controller latch required by
`EndChkBButton`. Later title-initialization samples diverge outside this
terminal subtree, so this record is limited to the one post-branch terminal
state and does not credit a node.

Three fixed `PrintVictoryMessages` preconditions complete its branch sweep at
the same controlled NMI boundary. The ROM and shared C first post-call samples
agree respectively on: the initial Mario message selector `$0c` and secondary
counter increment; the World 8 primary-counter-three selector `$0f` plus the
VictoryMusic queue; and the non-World-8 primary-counter-four path that writes
`WorldEndTimer = $06` and advances to terminal task four. These comparisons
cover the message selector/counter and terminal-timer writes, but retain zero
credit because the surrounding victory walk, enemy, player graphics and OAM
collaborators are still not proved as a complete route.

The controlled victory dispatch sweep then compares `SetupVictoryMode` and
both `PlayerVictoryWalk` outcomes. `SetupVictoryMode` agrees on destination
page, EndOfCastleMusic, and task two. The no-walk route agrees on task-three
entry with zero `VictoryWalkControl`. The walking route agrees on control two,
the `$80` fractional increment, one-pixel screen-left advance, right-page
carry, and its retention in task two. The isolated ROM retains a pre-existing
player-X coordinate during the setup-only route while the shared-C fixture
does not prepare that external player state; it is not a T26 terminal write
and is excluded from this comparison. These records provide branch evidence
for `SetupVictoryMode`, `PerformWalk`, `DontWalk`, and `ExitVWalk`, while
whole-route OAM/player evidence remains required before any completion mark.

The ordinary `PlayerEndWorld` controlled route also agrees at its first
post-call NMI boundary: it clears area and level, increments world, requests
the next game timer, clears terminal task four to game task zero, and switches
to GameMode. Together with the World 8 B route, this records both terminal
exits without treating the downstream area-pointer or title bootstrap work as
T26-owned proof.

The `t26-victory-bridge-handoff` fixture covers the remaining task-zero outer
dispatch branch without pretending that its collaborators belong to this
slice. After sixty ordinary NMI boundaries it sets Victory mode/task zero and
selects front slot zero with a non-Bowser ID. ROM `BridgeCollapse` therefore
takes `SetM2`; on the first post-call NMI both runs have Silence in
`EventMusicQueue` (`$00fc = $80`), retain Victory mode (`$0770 = $02`), and
advance the terminal task (`$0772 = $01`). The source then invokes the shared
enemy loop and player/OAM chain, whose output is intentionally excluded from
this comparison. This is direct route evidence for the `VictoryMode` task-zero
handoff and does not credit `BridgeCollapse`, `KillAllEnemies`, enemy-loop, or
player-graphics nodes.

The message-tree sweep also now covers the direct leaves omitted by the first
three message fixtures. `t26-victory-luigi-message` produces selector `$0d`
and secondary counter `$04`; `t26-victory-retainer-message` produces selector
`$0e` and secondary `$04`; and `t26-victory-counter-only` starts with a
nonzero secondary counter and produces `$08` without a selector write. The
first post-call ROM and shared-C samples match each tuple of selector,
secondary/primary counters, event-music queue, and terminal task. Together
with the original first-message, World-8 music, and end-timer fixtures, this
exercises `MRetainerMsg`, both `ThankPlayer` choices, `SecondPartMsg`,
`EvalForMusic`, `PrintMsg`, `IncMsgCounter`, `SetEndTimer`, `IncModeTask_A`,
and `ExitMsgs`; it remains branch evidence rather than a completion claim
until the outer collaborator routes have independent proof.

`PlayerEndWorld` now has a controlled record for both return leaves as well.
`t26-endworld-timer-active` sets timer control and `WorldEndTimer = $05`, so
the NMI does not decrement it before `EndExitOne`; both ROM and C retain
`OperMode/Task = $02/$04`, world `$02`, timer `$05`, and no event queue.
`t26-endworld-no-b` reaches World 8 with an expired timer and both saved
controller latches clear; both retain `OperMode/Task = $02/$04`, World 8,
zero timer, zero event queue, and a clear world-select flag. Along with the
ordinary-next-world and B paths, these records cover `PlayerEndWorld`,
`EndExitOne`, `EndChkBButton`, and `EndExitTwo` at their source call boundary.

The final Floatey direct leaves have corresponding fixed records.
`t26-floatey-timer-zero` enters `ChkNumTimer` with control `$02` and a zero
timer; both ROM and C clear the control while retaining the remaining actor
state. `t26-floatey-numeric-alt` enters with control `$06`, timer `$2b`, a
living ordinary enemy, and the alternate sprite-offset selector. Both execute
the numeric `ScoreUpdateData` path, decrement the timer to `$2a`, retain the
same score-number control/position, and select the same actor state. The
complete NMI subsequently rewrites the temporary two-sprite OAM area through
external graphics work, so this record is confined to the Floatey state and
its existing focused OAM smoke. Together with the 1-UP record, these exercise
the two local tables, clamp, zero-timer exit, pre-decrement update, alternate
offset, Y/carry choice, and two-sprite setup without claiming score or OAM
collaborator completion.

## S4 closure and S5 admission

S4 closes with zero new ROM-match credit, as its admission forecast required.
It transfers all 32 labels to its pre-accepted S5 closure receiver. The
controlled ROM records now support a fresh S5 forecast of 30 direct labels:
every label except `VictoryMode` and `AutoPlayer`. Those two outer labels
remain excluded because their original call order includes the independently
received enemy-loop and player-graphics chains; no S5 test may replace those
owners with a local approximation. S5 begins at 42 / 1,992, receives all 32
labels, forecasts the named 30 direct labels, and may close at no more than
72 / 1,992 only after updating the canonical inventory and independently
confirming both logic and operational tracks.

## S5 per-label evidence matrix

| Exact labels | ROM logic-equivalence evidence | Operational evidence | S5 disposition |
| --- | --- | --- | --- |
| `VictoryModeSubroutines`, `SetupVictoryMode`, `PlayerVictoryWalk`, `PerformWalk`, `DontWalk`, `ExitVWalk` | Controlled setup, no-walk, walk, and task-zero handoff records preserve source vector selection, destination, control, scroll fraction, page carry, and task writes. | x86/x64 mode smoke; DOS16 rebuild; platform-purity gate. | Complete. |
| `PrintVictoryMessages`, `MRetainerMsg`, `ThankPlayer`, `SecondPartMsg`, `EvalForMusic`, `PrintMsg`, `IncMsgCounter`, `SetEndTimer`, `IncModeTask_A`, `ExitMsgs` | Mario, Luigi, World-8 music, regular second-part, counter-only, and end-timer fixtures cover every selector/counter/event/task branch. | x86/x64 mode smoke; DOS16 rebuild; platform-purity gate. | Complete. |
| `PlayerEndWorld`, `EndExitOne`, `EndChkBButton`, `EndExitTwo` | Next-world, World-8 B, active-timer, and no-B fixtures cover all four exits and their source writes. | x86/x64 mode smoke and owner-local area smoke; DOS16 rebuild; platform-purity gate. | Complete. |
| `FloateyNumTileData`, `ScoreUpdateData`, `FloateyNumbersRoutine`, `ChkNumTimer`, `DecNumTimer`, `LoadNumTiles`, `ChkTallEnemy`, `GetAltOffset`, `FloateyPart`, `SetupNumSpr` | 1-UP, zero-timer, numeric alternate-OAM, clamp, and status-carry controlled records cover both local tables and all local branches. | Floatey OAM smoke; x86/x64 mode smoke; DOS16 rebuild; platform-purity gate. | Complete. |
| `VictoryMode`, `AutoPlayer` | Task-zero handoff proves only the terminal boundary. | External enemy-loop and player-graphics/OAM routes remain independently received. | Retain incomplete; transfer at S5 closure. |

## S5 P1 result

The four matrix groups complete exactly the forecast 30 labels. The canonical
inventory, progress report, and full census now record 72 / 1,992 complete.
The S5 run records those same 30 `actualMatches`; it retains only
`VictoryMode` and `AutoPlayer`. `VictoryMode` still requires the original
`EnemiesAndLoopsCore` call and `AutoPlayer` still requires the original
relative-player/player-graphics path, both of which belong to their existing
owners. S5 remains active for their eventual accepted transfer rather than
claiming a terminal-tree completion from its local wrappers.

## S5 closure and S6/S7 receipt

The first full-domain task-zero comparison exposes 85 RAM, one palette, and
25 OAM differences after the source terminal handoff. The current root calls
`mysmb_objects_draw_retainer` but omits the original `EnemiesAndLoopsCore`
call when `OperMode_Task` becomes nonzero; this is a `VictoryMode` outer-call
ordering defect, not an enemy-core rewrite. The same fixture does not prepare
the source player's live state, so it cannot certify `AutoPlayer` or the
player graphics output. S5 closes at 72 / 1,992 after transferring only those
two unresolved labels to pre-accepted S6. S6 has an empty forecast and may
restore the existing shared collaborator call only; S7 receives the two labels
for a fresh, predeclared equivalence decision after an aligned full-domain
route exists.

## S6 closure and S7 admission

S6 restores only the outer source sequence at ROM `$8471`: it runs
`VictoryModeSubroutines`; the resulting task-zero branch goes directly to the
existing player-relative/graphics tail; each resulting nonzero task writes
`ObjectOffset = $00` and executes exactly one shared
`EnemiesAndLoopsCore` slot-zero turn before that tail. The ordinary
GameEngine schedule remains fireball, six current-slot turns and six Floatey
ticks, so it is not substituted into VictoryMode. The extracted single-slot
interface preserves the source-visible `ObjectOffset` write. The shared single-slot dispatcher includes the ROM `RetainerObject ($35)`
branch before ordinary-enemy initialization, so its attributes remain intact
and its existing OAM routine runs at the original dispatch point; no Win32 or
DOS source contains gameplay state or route logic.

The focused mode smoke proves both outer decisions: a continuing bridge task
remains zero and leaves slot-zero enemy attributes untouched, while task one
advances to task two and clears the seeded slot-zero attribute through the
single current-slot actor path, including `ObjectOffset = $00`. Strict C90
x64 and x86 builds pass that smoke; both fresh Win32 products pass
`--self-test`; the shared source links to an OpenNT DOS16 MZ; and
`test_platform_purity.py` passes. The refreshed local artifact SHA-256 values
are `mysmb16.exe` `57DD37DBD7CA011F9B6AF68150A180308427AEA8AEA9739A96171CC20B2AEEB5`,
`mysmb32.exe` `F0F207FA689502732ED18CFC75984890098155612BF84F527835AAB13B9E9454`,
and `mysmb64.exe` `46140F3B72E1FA288AB832298B255960323F88AE78846690CADFA5CD480E0725`.

S6 closes at **72 / 1,992** with zero newly complete labels. Its source-order
repair does not independently prove the complete `VictoryMode` or
`AutoPlayer` behavior: the latter still depends on the aligned
relative-player/player-graphics state and output. Both labels transfer to the
pre-accepted S7 receiver. S7 begins at **72 / 1,992**, scopes exactly
`VictoryMode` and `AutoPlayer`, forecasts those two names, and may close at no
more than **74 / 1,992** only after an aligned controlled or source-reachable
original-ROM route compares the repaired task branch, slot-zero enemy-loop
entry, relative player coordinates and player graphics output, alongside the
usual cross-width, DOS16 and purity verification.

## S7 P1 outer-player call separation

The S7 source audit found one further outer-route mismatch at ROM `$8471`.
`VictoryMode` calls `RelativePlayerPosition` and then `PlayerGfxHandler`; it
does not call `GetPlayerOffscreenBits`.  The prior C convenience entry
`mysmb_oam_draw_player` combined all three GameEngine operations, causing the
Victory path to overwrite `Player_OffscreenBits` before it entered the player
graphics handler.  The shared game OAM owner now exposes those three source
operations separately.  The ordinary GameEngine invokes them in its original
order, while Victory invokes only its original two-call tail.  No platform
source changed.

The bridge handoff fixture now seeds `Player_OffscreenBits` with `$a5`; both
the ROM and C retain it through the task-zero victory branch.  That separate
handoff check proves the S7 repair does not add a GameEngine-only write.

The required similar-issue sweep checked every production caller of the new
three-entry interface.  GameEngine now has the source `$94a5` sequence.  The
three `player.c` relative-position calls are collision/control-path calls;
their source `PlayerMovementSubs` predecessor at `$a4af` also invokes
`GetPlayerOffscreenBits` before `RelativePlayerPosition`.  They remain an
unrepaired, explicitly recorded T16 OAM/offscreen dependency, not an S7
exception.  VictoryMode is the only completed S7 repair point: it correctly
omits that predecessor before its `$847c` AutoPlayer tail.

The retained `t26-victory-outer-player` fixture prepares documented direct
ROM inputs after sixty ordinary NMI boundaries and explicitly clears
`Sprite0HitDetectFlag`.  This selects the source `SkipSprite0` path and avoids
a fixture-unrelated physical sprite-zero wait.  It produces two repeatable NMI
returns in both the ROM reference and shared C.  The first advances task zero
through the bridge handoff; the second runs task one, executes exactly the
slot-zero enemy-core turn, then reaches the `AutoPlayer` relative-position and
graphics tail.  On that second record the two runs agree on `ObjectOffset`,
the player page/X/Y and relative X/Y, player sprite attribute/offset,
player-graphics offset, offscreen bits and `Player_Pos_ForScroll`.  All eight
player OAM entries are byte-identical.  The four bytes immediately following
those entries remain a pre-fixture OAM residual outside the player output;
unprepared enemy and scratch RAM account for the remaining aggregate
differences.  Raw records are local diagnostics below `build/` and are
discarded after this result is recorded.

This is outer-route evidence for `VictoryMode` and `AutoPlayer`, not an
independent completion claim for their shared `RelativePlayerPosition` or
`PlayerGfxHandler` descendants.  Those collaborator labels remain in their
received T16 OAM/offscreen slice.

The focused mode smoke, strict C90 x86/x64 mode-smoke builds, x86/x64 product
`--self-test`, OpenNT DOS16 MZ build, and platform-purity test pass.  The
refreshed artifacts have SHA-256 values `mysmb16.exe`
`229B0E959C0B4002BFE770393A39148101C204B016D36B375C3ADE2C16D04E69`,
`mysmb32.exe`
`07370AE1056DDEBF551CDEC408D0EA48B17130654CFAED749674B76EB26ECB4F`, and
`mysmb64.exe`
`81E9DCE07F3CFD33BA0F0258C1B6762CDE842508729259D8AAD1D22B56A4221B`.

## S7 closure

S7 closes both scoped outer nodes at **74 / 1,992**. `VictoryMode` is matched
by its task-vector, conditional slot-zero `EnemiesAndLoopsCore` turn and
two-call player tail; `AutoPlayer` is matched by the second-record
relative-position and byte-identical eight-sprite graphics output. The
controlled ROM comparison and the native smoke/build/purity track both pass.
No S7 label transfers.
