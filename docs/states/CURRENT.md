# Project Status

## Current Work

**Idle.**

[M2 T48](../history/M2-T48-sound-effects-and-channel-handlers.md#t48-closure)
closed all 74 source-order sound-effect labels from `SoundEngine` through
`Cont_CGrab_TTick` at **1,823 / 1,992** ROM-match complete. The next
unadmitted source-order candidate begins at `JumpToDecLength2`; it receives no
T48 credit.

## Current Technical Baseline

The product uses one shared native C90 game implementation for DOS16 and
Win32 x86/x64. Host adapters provide input, timing and presentation only. The
three owner-authorized local EXEs are current with T48 S6. Full CTest is
223/234 on each Windows architecture, with the same 11 recorded baseline
failures and no new failures; both Win32 self-tests and the OpenNT DOS16 link
pass. M2 remains open with 169 nodes not ROM-match complete.
