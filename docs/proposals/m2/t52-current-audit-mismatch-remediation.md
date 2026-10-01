# M2 T52: current-audit mismatch remediation

## Task contract

T52 is the bounded remediation task created after T51's historical
source-order completion and current-equivalence certification handoff.  It
owns every discrepancy already confirmed by the current-equivalence registry,
but it does not claim that the remaining `needs-evidence` population has been
verified.  All behavior changes are in shared `src/game/` owners and are
identical for DOS16, Win32 x86 and Win32 x64.

The task addresses ten historically complete labels that currently have a
semantic mismatch, ten feasible control relations and one feasible material
relation.  These labels earn no additional historical numerator credit;
T52 instead changes their current-equivalence dispositions only after ROM
logic and operational proof.  Fifteen additional listed control relations are
extractor false positives; their correction removes infeasible relations from
the canonical graph and does not modify game behavior.

## Planned S chains

| S | Chain and owner | Current-equivalence target |
| --- | --- | --- |
| S1 | `RotPRandomBit -> SkipSprite0 -> OperModeExecutionTree`, enclosing `NonMaskableInterrupt`; `frame_root.c` | A2: 3 nodes and 2 control edges |
| S2 | `ChkSelect -> ChkWorldSel`; `title_modes.c` | A6: 1 node and 1 control edge |
| S3 | `DecNumTimer -> LoadNumTiles -> AddToScore`; `objects.c` | A7: 2 nodes, 4 control edges and 1 material edge |
| S4 | `GetBackgroundColor -> NoBGColor -> GetPlayerColors`; `game.c` / `area.c` | B2: 2 nodes and 2 control edges |
| S5 | `DisplayTimeUp -> OutputInter -> NoTimeUp`; `game.c` | B3: 1 node and 1 control edge |
| S6 | `DrawLargePlatform`; `oam/small_platform_gfx.c` | H9: 1 node |
| S7 | `JumpEngine` vectors, constant branches and instruction-skipping joins; audit extractor only | H1–H8: remove 15 infeasible control relations from the graph |

A later S is admitted only after its exact node custody, ROM route and
operational tests are recorded.  S7 is a zero-code, zero-node audit S within
T52; it corrects the graph denominator rather than marking a nonexistent
runtime edge exact.

## T52 S1 admission: A2 NMI-prefix state handoff

S1 enters at `RotPRandomBit`, follows the unpaused `SkipSprite0` path and
ends at the `OperModeExecutionTree` dispatch boundary, with
`NonMaskableInterrupt` as the enclosing NMI owner.  The predecessor is the
NMI timer/pause prefix; successors are the mode dispatcher and RTI-equivalent
tail.  The exact labels are `NonMaskableInterrupt`, `RotPRandomBit` and
`SkipSprite0`, transferred from their historical receiving S records solely
for this corrective implementation.

The ROM-logic track uses a controlled cold-boot NMI route stopped immediately
before the source `OperModeExecutionTree` call.  It compares the seven-byte
LFSR state and source scratch `$00`, the PPU control mirror/physical phase,
scroll writes, pause selection and dispatch boundary.  The operational track
runs the focused A2 regression on x86/x64, full relevant frame-root routes,
OpenNT DOS16 compilation, platform-purity audit and refreshes the three local
target artifacts.  The repair must write the source scratch bit and preserve
d7-clear PPU control through dispatch, restoring d7 only at the RTI-equivalent
tail.  No platform source may own either decision.

## T52 S2 admission: A6 title-demo/world-select order

S2 enters at `ChkSelect`, follows its non-Select path through the `DemoTimer`
gate and ends at the `ChkWorldSel` successor. The received labels are
`ChkSelect` (source line 1005) and `ChkWorldSel` (line 1013), in source order.
`GameMenuRoutine` is the caller; `SelectBLogic`, `NullJoypad`, `DemoEngine`
and `RunDemo` are the successor boundaries. The two labels move under this
corrective receipt from T25 S10 and T25 S11. They were historically complete,
so S2 has a zero-credit forecast and preserves the **1,992 / 1,992** historical
numerator.

The ROM-logic track proves both sides of the conditional source relation: with
`DemoTimer=0`, `WorldSelectEnableFlag=1` and B input, `ChkSelect` must enter
the demo path before `ChkWorldSel`; with a nonzero timer, the same B input may
reach `ChkWorldSel`, then its shared `SelectBLogic` tail. It compares the
first post-menu state boundary, including `OperMode_Task`, controller byte,
world-select fields and timer writes. The operational track adds this boundary
case to `mysmb.title-demo-smoke`, runs it against ROM-configured Win32 x86/x64
routes, runs platform purity and the existing OpenNT DOS16 link, then refreshes
all three local artifacts. No platform source may make the menu decision.

## T52 S2 closure: A6 title-demo/world-select order

S2 closes both received labels without changing historical conformance credit:
`ChkSelect` and `ChkWorldSel` are now current-equivalence `exact`, and
`control-00087` is exact. The historical fraction remains **1,992 / 1,992**.

The ROM fixture applies its state only at a normal NMI return. With expired
`DemoTimer`, enabled world selection and B, coverage follows `$8245-$8269`
and enters `DemoEngine` at `$836b`; it does not enter `ChkWorldSel`. With a
nonzero timer and the same B condition, it reaches `$826c-$8273` and does not
enter `DemoEngine`. The shared C regression asserts the matching fields and
both ROM-configured Win32 widths pass it with platform-purity and host
self-tests. The existing OpenNT DOS16 pipeline recompiled the shared title
unit and linked the DOS executable; the linker has its longstanding optional
`OLDNAMES.LIB` warning but produced the refreshed executable with exit code 0.

## T52 S3 admission: A7 floatey-number score timer order

S3 owns the contiguous `FloateyNumbersRoutine -> DecNumTimer -> LoadNumTiles
-> AddToScore` chain in `objects.c`/the shared score owner. It receives
`FloateyNumbersRoutine`, `DecNumTimer`, `LoadNumTiles` and `AddToScore` in
source order. The predecessor is the GameEngine enemy-slot loop; successors
are `ChkTallEnemy` and status-number output. Historical credit remains
**1,992 / 1,992**: all four labels are corrective, zero-credit receipts.

The ROM-logic route uses the original floatey-number slot with timer `$2b` and
control `$0b`. It proves that `DEC` writes timer `$2a` before score-table read
and `AddToScore`, while the branch comparison retains the pre-decrement A
value `$2b`; it also exercises a non-award timer. The operational track adds a
focused ordering regression, runs x86/x64 routes, platform purity and OpenNT
DOS16 linkage, and refreshes three local artifacts. No platform adapter may
participate in this chain.

## T52 closure

T52 closes only when all six runtime chains have ROM logic-equivalence and
operational proof, the registry has no remaining A2/A6/A7/B2/B3/H9 mismatch,
the A7 material handoff is exact, H1–H8 have been removed as infeasible graph
relations, and all three targets run the same shared game source.  It then
hands the remaining current-equivalence `needs-evidence` records to the T53+
source-order proof program.

## T52 S3 closure: A7 floatey-number score timer order

S3 closes all four received labels without changing the historical numerator:
`FloateyNumbersRoutine`, `DecNumTimer`, `LoadNumTiles`, and `AddToScore` are
current-equivalence `exact`; `control-00176` through `control-00179` and
`material-00004` are exact. Historical conformance remains **1,992 / 1,992**.

The controlled normal-NMI owner-ROM route with floatey control `$0b` and timer
`$2b` executes `$84c3-$84e4`, then the score call at `$bc27-$bc48`. Source
review confirms the relevant 6502 distinction: `DEC` writes RAM `$2a`, while
the following `CMP` still compares the earlier accumulator value `$2b`.
The shared C now preserves that order before its score-table and `AddToScore`
path. `mysmb.floatey-oam-smoke` checks the award and non-award timer values;
both ROM-configured Win32 widths pass it, platform purity and their window
self-tests. The OpenNT DOS16 build links the same shared `objects.c` unit and
refreshes the local executable; its existing optional `OLDNAMES.LIB` warning
does not change the successful exit status. All three local artifacts were
refreshed under the ignored build directory.

## T52 S4 admission: B2 background-to-player palette fall-through

S4 owns `GetBackgroundColor -> NoBGColor -> GetPlayerColors` in source order.
It receives all three labels from M2 T27 S1. The predecessor is ScreenRoutines
task 10; successors are the VRAM-buffer consumer and task 11. Historical
credit remains **1,992 / 1,992**. The ROM-logic route covers background
controls 4-7 and zero, proving that both paths increment the task and fall
through to the `$3f10` player palette command. The operational track uses the
focused palette command test, x86/x64 self-tests and purity, plus the shared
OpenNT DOS16 link and three ignored local artifacts.

## T52 S4 closure: B2 background-to-player palette fall-through

S4 closes `GetBackgroundColor`, `NoBGColor` and `GetPlayerColors` as
current-equivalence exact without changing historical credit: it remains
**1,992 / 1,992**. `control-00204` (the zero-control branch),
`control-00205` (the nonzero fall-through) and `control-00206` (the shared
fall-through into the palette producer) are exact. Internal palette-selection
edges and independently enumerated material paths remain assigned to their
source-order owners; this S does not claim them.

The shared C writes the address-control selector only for controls 4-7, then
unconditionally calls the translated `GetPlayerColors` producer. The focused
C test covers zero, every nonzero selector and Mario/Luigi/fiery palette
choices. Five controlled owner-ROM routes use controls 0, 4, 5, 6 and 7 at a
normal NMI-return boundary and resume through ordinary
`GameMode -> ScreenRoutines` dispatch. For each route, the owner ROM and both
native widths agree on task 11, the address-control result, Buffer1 offset and
the `$3f10`, length-four command. The route checker compares only this
chain-owned state, deliberately excluding unrelated uninitialized frame
output. x86/x64 focused tests, Win32 self-tests, platform-purity and the
OpenNT DOS16 link pass. All three ignored target artifacts were refreshed.

## T52 S5 admission: B3 time-up task handoff

S5 owns `DisplayTimeUp -> OutputInter -> return -> NoTimeUp -> IncSubtask` in
`game.c`. It receives `DisplayTimeUp`, `OutputInter` and `NoTimeUp` from M2
T27 S2. The predecessor is ScreenRoutines task 4; its successor is task 6,
while tasks 5 and 7 remain reset controls outside the repair. Historical credit
remains **1,992 / 1,992** and the expected delta is zero.

The ROM-logic track records an expired task-4 visit followed by its cleared-flag
next visit, and separately records the non-expired and task-5/task-7 timer-reset
controls. It compares the task byte, expiration latch, screen timer,
disable-screen flag, text-buffer command and owned OAM fields. The operational
track extends the focused screen-status test, runs native x86/x64 routes,
platform purity and the shared OpenNT DOS16 link, then refreshes all three local
artifacts. No host adapter may make or delay the screen-task transition.

## T52 S5 closure: B3 time-up false-positive disposition

S5 closes without a shared-game repair. The original B3 report omitted the
`OutputInter -> ResetScreenTimer` call: the ROM at `$86d2`, immediately before
`OutputInter` returns, has already written task 5 because ResetScreenTimer
increments `ScreenRoutineTask`. The existing `game.c` case 4 has the same
ordered writes. `DisplayTimeUp`, `OutputInter`, `NoTimeUp`, and
`control-00225` are current-equivalence exact; the historical numerator stays
**1,992 / 1,992**.

The ROM-logic track used a direct RTS probe plus bounded four-frame expired
and non-expired routes. The x86 and x64 C recorders matched the chain-owned
task, expiration latch, screen timer, disable-screen byte and Buffer1 state in
every sample. The focused smoke test, platform-purity check and x86/x64 host
self-tests passed as the separate operational track. The OpenNT DOS16 compiler
rebuilt the shared core through its established source list with its existing
warning set; the retained local three-target artifacts have the recorded S4
hashes because S5 changes no shared gameplay source. The similar-issue sweep
identified this defect class as a missing callee in a static audit: all later
screen-task candidate reviews must include nested shared game calls before
they propose a source change.

## T52 S1 closure: A2 NMI-prefix state handoff

S1 closes its three current-equivalence labels without changing the historical
ROM-match numerator: `NonMaskableInterrupt`, `RotPRandomBit`, and
`SkipSprite0` move from `mismatch` to `exact`; `control-00040` and
`control-00052` likewise move to `exact`. The historical fraction remains
**1,992 / 1,992**, because each label was already historically complete.

ROM-logic proof used the owner ROM on its ordinary NMI path and stopped at
source `$8175`, immediately before `jsr OperModeExecutionTree`. With one
recorder-only NMI-entry mirror precondition of `$0778=$10`, the capture has
`$00=$02`, rotated LFSR bytes `$a9/$40`, and physical `$2000=$10`. This proves
both the source scratch handoff and d7-clear dispatch phase. Static source
review confirms that the return path alone executes `ora #$80`.

Operational proof passed `mysmb.nmi-parent-integration`, Win32 self-test and
platform-purity in ROM-configured x86 and x64 builds. The focused test now
also proves the RTI-equivalent d7 restore. The existing OpenNT DOS16 build
links the same `src/game/frame_root.c`; all three local executable artifacts
were refreshed under the ignored build tree. No platform adapter changed.
