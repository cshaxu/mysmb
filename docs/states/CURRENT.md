# Project Status

## Current Work

M1 T2 S2 is admitted to implement the platform foundation.

## M1 T2 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation |
| Admission And Approval | Owner approved M1 admission and requested a Win32-first, 16-bit-compatible C foundation on 2026-09-22; S1 task breakdown committed at `e6a6859`. |
| Objective | Implement the shared C90 core, native Win32 window/event loop, fixed 60 Hz host contract, CMake target split, and a non-ROM visible smoke scene. |
| Non-goals | Do not inspect or import ROMs, disassemblies, third-party translations, generated code, or assets; do not add a NES CPU/PPU/APU emulator or DOS VGA implementation. |
| Reference Baseline | M1 S1 plan `e6a6859`; current C90 skeleton; OpenNT and NTVDM64 worktrees may be inspected but are not linked or imported. |
| Candidate Proposal | [M1 Win32 and 16-bit-compatible platform foundation](../proposals/m1-win32-platform-foundation.md) |
| Files And ABI Surface | Root CMake; `src/game`; `src/platform/win32`; target-specific mains; core smoke test; current packet. |
| Applicable Rules | Task Reading Set; Execution, Documentation, Architecture, and Coding rules. Source policy: no protected input enters S2. |
| Verification | Configure/build core and Win32 targets with current x64 compiler; run headless core smoke; inspect include/dependency graph; run documentation gate; identify a real OpenNT 16-bit compiler command or report that specific missing host prerequisite. |
| Expected Markers | `mysmb_game` core, `mysmb_win32` window target, neutral input/frame/render contracts, 60 Hz scheduler, and smoke scene exist. |
| Asset Needs | None. The later source-pipeline candidate alone requires owner-local ROM and reviewed source admission. |
| Reporting Requirements | Report x64 build/run evidence, any x86/OpenNT availability finding, dependency-boundary review, and absence of ROM/third-party material. |
| Stop Conditions | Stop for owner direction only if the shared core cannot compile without platform headers or if an available OpenNT compiler cannot produce a C90 large-model object for it. |
| Exit Criteria | Win32 target compiles; headless core smoke proves the 60 Hz frame path; game code has no platform include; and OpenNT tool availability is either proven with a compile or identified as a concrete missing prerequisite. |
| Original Owner Request | Execute M1 and establish the SMB foundation: native C, Win32 first, 16-bit compatible, with no runtime NES emulator. |
| Similar-Issue Sweep | Inspect all production sources and CMake targets for host API includes or platform macros outside platform roots; fix each in this foundation scope. |

## Current Technical Baseline

- `mysmb` is a C90 skeleton only. The first runnable target is a native Win32 window built as x86 and x64. The core must remain compatible with the later 25 MHz 486SX real-mode DOS target, MS-DOS 5.0 or later, with DOS 3.3 desired. The OpenNT 16-bit C toolchain checks DOS compatibility; NTVDM64 is not a DOS graphics validation platform. No ROM, disassembly, translated game logic, native renderer, oracle, or ROM-derived executable is admitted.

## Recent M0 Closures

| Task | Compact result |
| --- | --- |
| T1 | M0 governance, source boundary, MTSP lifecycle, roadmap, and local documentation gate established at `3771fbc`; no ROM or third-party material admitted. [History](../history/M0-T1-governance-and-translation-plan.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
