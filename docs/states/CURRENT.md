# Project Status

## Current Work

M1 T3 S3 is admitted to prepare the owner-local title command stream for native consumption.

## M1 T3 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation |
| Admission And Approval | Owner approved M1 execution and the native-C/no-emulator route on 2026-09-22; T3 S2 established original reset state at `f187bf2`. |
| Objective | Extract the byte-verified title command stream read by `$86ff-$8731` from owner-local CHR into an ignored C90 unit, with a deterministic extent and no runtime ROM reader. |
| Non-goals | Do not commit ROM bytes, CHR, source listing, generated code/data, screenshots, traces, or ROM-embedded executable; do not introduce a CPU, PPU, APU, instruction decoder, or generic memory bus. |
| Reference Baseline | T3 S2 `f187bf2`; owner-local ROM; byte-verified title read at PPU `$1ec0` for `$013a` bytes; public sources remain local research references only. |
| Candidate Proposal | [M1 static-C source pipeline](../proposals/m1-source-corpus-and-local-toolchain.md) |
| Files And ABI Surface | Project-owned title extractor, ignored local C90 title data unit, root CMake target, and synthetic extractor test. |
| Applicable Rules | Task Reading Set; Execution, Documentation, Architecture, Coding, and source/research policies. |
| Verification | Verify the `$013a` extent with a synthetic NROM, build the ignored generated C90 unit, and run CMake tests. |
| Expected Markers | Local title data generator, local C90 target, and neutral extent test exist without protected material in Git. |
| Asset Needs | Owner-local ROM only for extraction verification; no ROM-derived payload enters tracked files. |
| Reporting Requirements | Report verified source span, local-output containment, build/test result, and title-transfer dependency still deferred. |
| Stop Conditions | Stop for owner direction if verified ROM bytes disagree with the stated title span or if extraction cannot remain local. |
| Exit Criteria | The title command stream has a reproducible ignored C90 generation path with no runtime ROM reader. |
| Original Owner Request | Execute M1 and establish the SMB foundation: native C, Win32 first, 16-bit compatible, with no runtime NES emulator. |
| Similar-Issue Sweep | Search all tracked files for ROM paths, ROM extensions, generated output references, and third-party listing text; retain only policy-approved neutral tooling and ignore rules. |

## Current Technical Baseline

- `mysmb_game` is a C90 non-ROM foundation with a neutral frame/input contract. `mysmb_win32` builds x86 and x64 PE windows around that core; `mysmb_dos16_core` is its host-free DOS compiler input. The OpenNT source checkout has no discovered built compiler binary, so its large-model compile remains a local-host prerequisite. No ROM, disassembly, translated game logic, native renderer, oracle, or ROM-derived executable is admitted.

## Recent M0 Closures

| Task | Compact result |
| --- | --- |
| T1 | M0 governance, source boundary, MTSP lifecycle, roadmap, and local documentation gate established at `3771fbc`; no ROM or third-party material admitted. [History](../history/M0-T1-governance-and-translation-plan.md). |

## Recent M1 Closures

| Task | Compact result |
| --- | --- |
| T2 | Shared C90 core, x64/x86 Win32 window builds, and DOS16 compiler input established at `62e2d22`; both core smoke tests pass. [History](../history/M1-T2-win32-platform-foundation.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
