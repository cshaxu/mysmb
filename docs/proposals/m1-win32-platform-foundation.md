# M1 Win32 And 16-Bit-Compatible Platform Foundation

## Purpose

Turn the current C90 skeleton into the smallest real product shape: a shared
game library, native Win32 x86/x64 window targets, and an OpenNT-compilable
DOS16 core target. This task deliberately contains no ROM logic.

## Implementation Sequence

S1 records this M1 task order. S2 creates the target graph, neutral frame/input
contracts, Win32 event/window loop, fixed 60 Hz scheduler, and a visible
non-ROM smoke scene. It also proves that the shared core compiles through the
OpenNT 16-bit route. S3 closes the foundation after both Windows targets run.

## Acceptance

The same C90 core builds under Win32 x86, Win32 x64, and the OpenNT 16-bit
compiler. A Win32 window runs a 60 Hz host loop without host APIs leaking into
the core. The next source-pipeline task can add translated code without
altering target ownership.
