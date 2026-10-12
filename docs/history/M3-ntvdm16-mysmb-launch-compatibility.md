# NTVDM16 MySMB DOS launch compatibility

## Objective

Repair the current `mysmb16.exe` launch path under the owner-provided NTVDM
(`run16`) on Windows so that the real DOS executable starts, reaches graphics,
accepts its standard controls, and exits normally.

## Scope

- Reproduce failure with the existing `run16` invocation and record its exact
  loader or runtime symptom below ignored `build/`.
- Inspect MZ header, relocation, startup, memory allocation, DOS interrupt and
  VGA initialization compatibility in the DOS16 platform boundary.
- Test the corrected executable through NTVDM and retain DOSBox as a separate
  compatibility check.

## Non-goals

- No NTVDM configuration edits, emulator patches, DOSBox-only workaround,
  shared game/PPU/ROM logic change, Win32 change, or alternative executable
  format.
- Do not accept a title-only launch: graphics, input and orderly exit are part
  of the route.

## Planned S tasks

### S1 — bounded failure receipt and loader classification

Capture the actual `run16` command, MZ header/relocation facts, failure phase
and minimal diagnostic evidence.  Classify the issue as loader allocation,
startup/CRT, interrupt/vector, mode setup, unsupported instruction, or later
runtime fault before modifying code.

### S2 — DOS16 compatibility repair

Apply the smallest platform-only repair required by S1.  Preserve the existing
DOSBox route and all shared game/PPU semantics.  Validate launch, title,
Start, W/S/A/D, J/K, Tab, Escape and normal return to the host shell through
NTVDM, then repeat the DOSBox route.

## Acceptance

`mysmb16.exe` must start with the unmodified owner `run16` environment and
complete the named graphical and input route without crash, corruption or
host configuration change.  A source change refreshes the three local target
artifacts under the repository delivery policy.

## Owner-directed archival

The owner confirmed this candidate completed on 2026-10-12 and directed its
removal from the queue. It was never admitted as a separate numeric T, so this
record preserves that owner disposition rather than inventing a task-level
automated verification claim. The earlier M3 T34 run16 text-colour receipt is
related evidence only; it is not relabelled as this candidate's complete route.
