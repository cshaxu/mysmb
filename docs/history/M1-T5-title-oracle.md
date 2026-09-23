# M1 T5 Title Oracle

## Outcome

T5 builds a local reference from `nnes` commit
`9ee5f902d82fda72059cb992dde00817cd1ff5af` beneath ignored MySMB output and
compares its bounded title checkpoint with the native C title-command state.
The reference copy did not alter the sibling worktree; its pre-existing dirty
entry count remained 458.

At the named 1,200-slice checkpoint, the reference reached frame 31 without a
trap and reported CIRAM FNV-1a `3cbce965`; native command transfer reported
`5df676ec`. The difference is expected for M1: native C implements the title
VRAM-command transfer while the reference has continued through later original
title-route updates. M2 owns translating that state route and turning the
disposition into equality checkpoints.

The oracle exposed and corrected a title-table boundary defect: the 960-byte
tile region ends at `0x3c0`, followed by the 64-byte attribute region. The
previous `0x300` boundary left title-command destinations uninitialized.

## Evidence

- Native default and owner-local CTest suites pass: 5 and 6 tests.
- The local x64 native title oracle and ignored reference probe complete at the
  named checkpoint; neither emits a ROM, frame, screenshot, or trace.
- Documentation governance and `git diff --check` pass.
- The local OpenNT large-model C90 compile, Win32 title build, and title
  command path were established by M1 T4 at `6400a66`.

## Transfer

M1 closes with a ROM-free default build, owner-local title build, native Win32
composition, a large-model core compile, and a bounded reference oracle. M2
must translate the title state route before claiming reference-state equality.
