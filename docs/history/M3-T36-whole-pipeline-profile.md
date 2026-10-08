# M3 T36: Whole-Pipeline Performance Assessment

The owner directs a comprehensive search for further performance opportunities,
including shared core, PPU, DOS presentation and Win32 presentation, while
retaining original game semantics and one portable core implementation.

## S1 Admission

S1 owns instrumentation and evidence only.  It will construct an ignored,
profile-only measurement route that separates input/control, startup/game tick,
PPU preparation/composition, palette work, device publication, audio handoff
and pacing.  It will report each stage separately for the current DOS16 and
host routes where a valid clock exists.  It does not modify translated game
decisions, render output, platform behavior, cache allocation, executable
release artifacts or ROM-facing code.

The expected change is 200--350 lines of project-owned profile/test support,
or no tracked source if the existing diagnostic surfaces are sufficient.  Any
temporary source, executable, trace, image and receipt stays below ignored
`build/`.  The measurement must not change persistent DOSBox configuration or
use host wall-clock time as a 486SX claim.

The output is a finite candidate table.  Every candidate names its owner,
shared/DOS/Win32 applicability, measured stage, expected memory effect,
semantic risk, exact proof route and accept/defer/reject disposition.  Core
candidates must use the same C90 source for all targets: no DOS-specific game
logic, platform macros, pointer representation or state layout may enter
`src/core`.

S1 has zero ROM node and edge scope, expected matches and actual matches.  If
no product code remains changed, it needs no artifact refresh.  A retained
optimization requires a successor S with focused ROM-route/state evidence,
operational tests, platform-purity review and three refreshed local targets.
