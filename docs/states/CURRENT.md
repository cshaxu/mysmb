# Project Status

## Current Work

M1 T4 S1 is admitted to display the native title state in the local Win32 build.

## M1 T4 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New |
| Admission And Approval | Owner approved M1 execution and the native-C/no-emulator route on 2026-09-22; T3 produced the local title-data and native name-table path at `417780b`. |
| Objective | Build the owner-local Win32 title target from native game state, title command data, and CHR graphics; preserve a ROM-free foundation target. |
| Non-goals | Do not commit ROM bytes, CHR, source listing, generated code/data, screenshots, traces, or ROM-embedded executable; do not introduce a CPU, PPU, APU, instruction decoder, or generic memory bus. |
| Reference Baseline | T3 `417780b`; owner-local ROM; native title state; title CHR page `$1000-$1fff`; public sources remain local research references only. |
| Candidate Proposal | [M1 static-C source pipeline](../proposals/m1-source-corpus-and-local-toolchain.md) |
| Files And ABI Surface | Win32 platform renderer, local-only target wiring, and optional owner-local OpenNT C90 core-compile target; no game-layer Windows dependency. |
| Applicable Rules | Task Reading Set; Execution, Documentation, Architecture, Coding, and source/research policies. |
| Verification | Build x64 owner-local Win32 target with embedded ignored artifacts; run all project tests; verify the normal target still configures without `MYSMB_ROM_PATH`; compile `src/game/game.c` with OpenNT `/AL /c` through an owner-local compiler path. |
| Expected Markers | Conditional local Win32 target linkage and native 2bpp title renderer exist without protected material in Git. |
| Asset Needs | Owner-local ROM only for extraction verification; no ROM-derived payload enters tracked files. |
| Reporting Requirements | Report target containment, native rendering inputs, build/test results, and visual-validation gap if any. |
| Stop Conditions | Stop for owner direction if the renderer requires game-layer host APIs, a generic PPU, or a distributable ROM-embedded executable. |
| Exit Criteria | A local Win32 executable builds from native title state and local CHR/title data while the default build remains ROM-free. |
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
