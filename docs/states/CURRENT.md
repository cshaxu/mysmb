# Project Status

## Current Work

M1 T3 S4 is admitted to apply the title stream to the native name-table state.

## M1 T3 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation |
| Admission And Approval | Owner approved M1 execution and the native-C/no-emulator route on 2026-09-22; T3 S2 established original reset state at `f187bf2`. |
| Objective | Translate the name-table portion of `$8e92-$8eec` as a title-stream-specific C90 writer and verify it consumes the ignored local title unit without a runtime ROM reader or generic PPU. |
| Non-goals | Do not commit ROM bytes, CHR, source listing, generated code/data, screenshots, traces, or ROM-embedded executable; do not introduce a CPU, PPU, APU, instruction decoder, or generic memory bus. |
| Reference Baseline | T3 S3 `c5da0e3`; owner-local ROM; byte-verified title command format and `$013a` input extent; public sources remain local research references only. |
| Candidate Proposal | [M1 static-C source pipeline](../proposals/m1-source-corpus-and-local-toolchain.md) |
| Files And ABI Surface | `src/game/` title command writer, local-only title integration smoke, root CMake integration, and project-owned command-format test. |
| Applicable Rules | Task Reading Set; Execution, Documentation, Architecture, Coding, and source/research policies. |
| Verification | Unit-test sequential, vertical, and repeated title writes; build the ignored local title unit and run an integration smoke against the native name tables. |
| Expected Markers | Native ROM-specific title command writer and local title integration smoke exist without protected material in Git. |
| Asset Needs | Owner-local ROM only for extraction verification; no ROM-derived payload enters tracked files. |
| Reporting Requirements | Report command format, state ownership, local-output containment, and build/test result. |
| Stop Conditions | Stop for owner direction if title transfer requires a generic PPU abstraction or an uncontained ROM dependency. |
| Exit Criteria | The local title stream reaches native name-table state through verified C90 logic, without runtime instruction interpretation or a generic PPU. |
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
