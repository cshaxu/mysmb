# Retained Presentation Performance Qualification

## Purpose

Continue performance work after M3 T38 without reopening its accepted exact
current-background sprite-union presenter.  This candidate has zero ROM-node
and control-edge scope.  It must use a temporary diagnostic copy below
`build/`, and it may not change game/core/PPU policy, output dimensions,
cadence, DOSBox settings or artifact selection merely to improve a benchmark.

## Planned S sequence

| S | bounded owner | completion condition |
| --- | --- | --- |
| S1 | Rebuild a no-readback PIT fixture from the selected product source and time the post-Start route at `core=normal`, `cycles=fixed 3000`. | Same source/presenter identity as the selected MZ; a separate prior 260-frame physical oracle; comparable root-step delta against T38 S10's 39,026 ticks. |
| S2 | Attribute the retained graphics route only if S1 still exceeds the 16.67ms frame budget. | One named >=20% owner and one bounded candidate, or an explicit no-change rejection. |
| S3 | Attribute the DOS and Win32 text paths separately, then test at most one changed-cell or batched-output improvement. | Exact neutral cells, colors, request order and text-mode lifecycle, with no graphical/core policy change. |
| S4 | Package and target-era qualification. | Current x86/x64/DOS16 artifacts, DOS memory/stack receipt, and an explicitly limited 486-class or calibrated run receipt. |

The prior private `cycles=max` measurement remains diagnostic only.  It cannot
be compared with fixed-3000 evidence.  The first fixed-3000 attempt still had
full VGA readback enabled, reached fixture frame 40 in sixty seconds, and is
therefore not a presentation timing result; it establishes only that the
oracle must be excluded from the timing binary.
