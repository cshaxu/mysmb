# Project Status

## Current Work

M1 T2 S3 is admitted to close the platform foundation.

## M1 T2 S3 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation |
| Admission And Approval | Owner approved M1 admission and requested a Win32-first, 16-bit-compatible C foundation on 2026-09-22; S2 implementation committed at `62e2d22`. |
| Objective | Review and close the platform foundation, retaining its concrete OpenNT tool-availability finding for the later DOS adapter work. |
| Non-goals | Do not add ROM logic, third-party source, DOS VGA code, or a NES emulator. |
| Reference Baseline | T2 S2 implementation `62e2d22`; x64 and x86 MinGW build trees. |
| Candidate Proposal | [M1 Win32 and 16-bit-compatible platform foundation](../proposals/m1-win32-platform-foundation.md) |
| Files And ABI Surface | Current status and T2 history record only. |
| Applicable Rules | Task Reading Set; Execution and Documentation rules. |
| Verification | Re-run documentation governance, x64/x86 builds, CTest smoke, PE architecture inspection, and source-boundary search. |
| Expected Markers | T2 history records `mysmb_game`, `mysmb_win32`, x86/x64 PE evidence, and the unbuilt OpenNT compiler prerequisite. |
| Asset Needs | None. |
| Reporting Requirements | Preserve truthful build, test, architecture, and OpenNT availability results. |
| Stop Conditions | Stop for owner direction only if closure evidence contradicts the S2 implementation. |
| Exit Criteria | T2 history is complete and the next queued source-pipeline task can be admitted. |
| Original Owner Request | Execute M1 and establish the SMB foundation: native C, Win32 first, 16-bit compatible, with no runtime NES emulator. |
| Similar-Issue Sweep | Completed in S2: `rg` found the sole `windows.h` include under `src/platform/win32`; no platform macro occurs beneath `src/game`. |

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
