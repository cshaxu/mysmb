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

## T52 S6 admission: H9 large-platform Y source

S6 owns `DrawLargePlatform` in `small_platform_gfx.c`, received from M2 T44
S5. The predecessor supplies `Enemy_Rel_XPos` and `Enemy_Y_Position`; the
successor is the six-column offscreen mask. The single historical-complete
label has a zero-credit forecast, retaining **1,992 / 1,992**.

The ROM-logic track uses a controlled child record where world Y and relative
Y differ, then covers the castle, secondary-hard, cloud and full-offscreen
branches. It compares the six OAM records and source scratch `$02`. The
operational track updates the focused graphics smoke test, runs x86/x64 route
checks, platform purity and the OpenNT DOS16 build, and refreshes the three
local artifacts. No adapter owns this coordinate choice.

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

## T52 S6 closure: H9 large-platform Y source

S6 closes `DrawLargePlatform` as current-equivalence `exact`; the historical
conformance numerator remains **1,992 / 1,992** because the received label was
already historically complete.  No adjacent large-platform label is promoted:
`ShrinkPlatform` through `ExDLPl` remain in their source-order evidence cohort.

The source requires `Enemy_Rel_XPos` for `SixSpriteStacker`, then restores the
object slot and loads `Enemy_Y_Position,x` for `DumpFourSpr`.  Shared C now
uses `$00cf + slot` for those first four OAM Y bytes.  The focused fixture sets
that byte to `$40` and the distinct relative-Y byte `$03b9` to `$70`, proving
the selected source independently of coincidental equal coordinates.  It also
retains castle, secondary-hard, cloud, per-column and full-offscreen coverage.

The separate original-ROM route check replays twelve retained
`RunLargePlatform -> DrawLargePlatform` parent records (normal, castle, and
variants 0 through 9) against fresh x64 and x86 shared-C builds, with zero
non-stack RAM differences.  Focused differential smoke tests and platform
purity pass on both widths.  The owner-ROM records, recorder experiment and
build products remain ignored below `build/m2-t52-s6/`; they are not committed.

## T52 S7 admission: H1–H8 infeasible control-edge disposition

S7 has zero inventory-node scope and zero historical-credit forecast. It owns
only `control-01339`, `control-01405`, `control-01408`, `control-01415`,
`control-01502`, `control-01515`, `control-01537`, `control-01552`,
`control-01632`, `control-01711`, `control-02036`, `control-03743`,
`control-03769`, `control-03784` and `control-03868`. Its baseline and maximum
remain **1,992 / 1,992**.

The ROM-logic track proves every candidate directly from `JumpEngine`'s two
`PLA` operations and indirect `JMP`, the constant branch operands, or the
`BIT` opcode-overlap entry. It also verifies that each corresponding real call,
selector/vector, taken-branch and target-return relation remains registered.
The operational track runs the registry validator, node ledger and
Documentation Governance gate, platform-purity audit and the already rebuilt
same-source x86/x64 self-tests plus the OpenNT DOS16 link/artifact check. No
adapter or shared game owner participates in this graph-only disposition.

## T52 S7 closure: H1–H8 infeasible control-edge disposition

S7 closes with zero node-credit change: historical conformance remains
**1,992 / 1,992**, while the current node result remains 54 `exact`, zero
`mismatch` and 1,938 `needs-evidence`. All fifteen scoped relations are now
explicitly `infeasible`: `control-01339`, `control-01405`, `control-01408`,
`control-01415`, `control-01502`, `control-01515`, `control-01537`,
`control-01552`, `control-01632`, `control-01711`, `control-02036`,
`control-03743`, `control-03769`, `control-03784` and `control-03868`.

The source proof is the `JumpEngine` `PLA`/`PLA`/indirect-`JMP` dispatch at
lines 2395–2408, unconditional operand values at the H2/H4/H5 sites, and the
H2 `BIT` overlap. The graph audit asserts that all fifteen relations have that
disposition and that their real alternatives remain: the parent calls and
branches plus 9 block, 55 initializer, 6 frenzy, 7 large-platform and 5
star-flag dispatches, 82 selectors total. The raw ledger remains 4,342
relations; the feasible-control denominator is 4,327. No production or
platform source changed.

Operational proof passed the graph assertion, registry verifier, node ledger,
documentation governance and platform-purity gates. The same shared-source
Win32 x86/x64 artifacts pass their self-tests; the OpenNT DOS16 MZ artifact
was rebuilt in S6 and its signature/hash was rechecked for this graph-only S.

## T52 closure

T52 has closed every confirmed current mismatch from its intake. A2, A6, A7,
B2, B3 and H9 are current-equivalence exact; H1–H8 are explicitly infeasible
extractor records rather than bogus gameplay edges. Historical conformance
remains **1,992 / 1,992** and is not a fresh whole-ROM claim. The next work is
T53's source-order proof program, beginning with Cohort A and admitting its
first bounded chain only after its node/edge scope and original-ROM route are
recorded.
