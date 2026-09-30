# Project Status

## Current Work

**Idle.**

M2 T50 S2 closed at **1,950 / 1,992** after matching the shared
music frequency, length and normal-envelope lookup chain. The next source-order
candidate is M2 T50 S3, which retains the two noise-envelope tables.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 remains active: every P uses the existing OpenNT toolchain to compile and
link the same shared C core, then refreshes `mysmb16.exe` with the Win32
artifacts. DOSBox is not part of this workflow.
