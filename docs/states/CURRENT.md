# Project Status

## Current Work

**Idle.**

M2 T50 S1 is closed at **1,945 / 1,992**. Its 21 music-stream payload labels
are ROM-match complete through the shared `audio.c` owner-ROM reader; T50 S2
remains the next planned contiguous lookup/envelope chain.

## Current Technical Baseline

One shared native C90 game implementation serves DOS16 and Win32 x86/x64.
DOS16 remains active: every P uses the existing OpenNT toolchain to compile and
link the same shared C core, then refreshes `mysmb16.exe` with the Win32
artifacts. DOSBox is not part of this workflow.
