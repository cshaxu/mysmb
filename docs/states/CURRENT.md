# Project Status

## Current Work

**Idle.**

M2 T49 S9 is closed at **1,924 / 1,992**. The next music-data chain has not
been admitted.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 remains active: every P uses the existing OpenNT toolchain to compile and
link the same shared C core, then refreshes `mysmb16.exe` with the Win32
artifacts. DOSBox is not part of this workflow.
