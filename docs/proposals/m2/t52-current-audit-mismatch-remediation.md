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

## T52 closure

T52 closes only when all six runtime chains have ROM logic-equivalence and
operational proof, the registry has no remaining A2/A6/A7/B2/B3/H9 mismatch,
the A7 material handoff is exact, H1–H8 have been removed as infeasible graph
relations, and all three targets run the same shared game source.  It then
hands the remaining current-equivalence `needs-evidence` records to the T53+
source-order proof program.