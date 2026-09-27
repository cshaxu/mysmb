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
