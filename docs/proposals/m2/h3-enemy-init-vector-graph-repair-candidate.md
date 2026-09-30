# H3 enemy initializer-vector graph repair candidate

## Status

Unnumbered current-equivalence governance repair candidate. It authorizes no
production-code change and has no numeric M2 task.

## Confirmed discrepancy

At `SMBDIS.ASM` line 8093, `InitEnemyRoutines` calls `JumpEngine` and is
immediately followed by fifty-five target-pointer words. The current extracted
graph wrongly records `control-01502` as a fall-through to `NoInitCode` and
`control-03769` as a JumpEngine return to `InitEnemyRoutines`. As proved by
JumpEngine at lines 2395–2408, the routine consumes the JSR return address
and indirect-jumps to the selected word; a target RTS resumes the caller of
`InitEnemyObject`.

## Smallest candidate chain

Correct the extractor/registry representation of this JumpEngine call and its
initializer-vector targets. Preserve all fifty-five real dispatch entries and
the target-to-caller return handoff. No shared C stream or initializer code
requires modification.

## Required proof after a later admission

Regenerate the initializer-vector graph fragment and run original-ROM/x86/x64
routes across representative normal, group, frenzy, power-up, vine, platform
and retainer IDs. Verify that all real dispatches remain registered while the
two infeasible edges are removed or reclassified.
