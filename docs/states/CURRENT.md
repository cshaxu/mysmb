# Project Status

## Current Work

**M2 T43 is closed at 1,517 / 1,992.** Its 150 scoped nodes are closed:
136 new ROM-match completions and 14 retained/rechecked completions. The
separate `KillEnemies` historical claim was revoked during S3 and remains
with M2 T29 S8; it is not a T43 scope debt. T44 is the next source-order
candidate and has not yet been admitted.

## T43 Closure

[T43 terrain and collision closure](../history/M2-T43-terrain-and-bounding-boxes.md#t43-closure)
contains the task-wide cross-chain matrix, node accounting and integrated
three-target evidence.

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and Win32
x86/x64. Host adapters provide input, timing and presentation only. The local
original-ROM execution tools are validation-only and are not linked into the
game. ROM-derived resources and build intermediates remain under ignored build
output; the owner-authorized three test EXEs are in assets/.

## Preserved limits

M2 remains incomplete. Existing graphics, audio, child/full-frame and legacy
runtime debts retain their tracker/ledger records. DOS16 has build/link
evidence; there is no supported claim of DOS graphical playability, resource
binding or physical 486SX performance. Earlier task records remain under
history/.