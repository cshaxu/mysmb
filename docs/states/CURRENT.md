# Project Status

## Current Work

**Idle.**

[M2 T47](../history/M2-T47-object-position-and-sprite-output.md#t47-closure)
closed all 40 source-order labels from `ExPlyrAt` through `SetHFAt` at
**1,749 / 1,992** ROM-match complete. The next unadmitted source-order
candidate begins at `SoundEngine`; it receives no T47 credit.

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and
Win32 x86/x64. Host adapters provide input, timing and presentation only.
The three owner-authorized local EXEs are current with T47 S5. Full CTest
is 222/233 on each Windows architecture, with the same 11 recorded
baseline failures and no new failures; both Win32 self-tests and the
DOS16 link pass. M2 remains open with 243 nodes not ROM-match complete.
