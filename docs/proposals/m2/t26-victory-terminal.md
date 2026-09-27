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
