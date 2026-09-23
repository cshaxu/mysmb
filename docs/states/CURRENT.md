# Project Status

## Current Work

M1 T2 S1 is admitted to break the milestone into executable tasks and queue the
remaining work before platform code begins.

## M1 T2 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New |
| Admission And Approval | Owner approved M1 admission and requested its T-task breakdown and queue on 2026-09-22. |
| Objective | Define the shortest implementation sequence to a Win32 x86/x64 title scene while keeping the shared C core 16-bit compatible, then admit T2 as the platform-foundation task. |
| Non-goals | Do not inspect or import ROMs, disassemblies, third-party translations, generated code, or assets; do not write a separate paper-only milestone. |
| Reference Baseline | M0 closure `ac5090b`; Win32-first/DOS-compatible correction `90bad31`; current C90 skeleton. |
| Candidate Proposal | [M1 Win32 and 16-bit-compatible platform foundation](../proposals/m1-win32-platform-foundation.md) |
| Files And ABI Surface | M1 proposal and Queue; Current packet. No game or platform ABI change in S1. |
| Applicable Rules | Task Reading Set; Execution, Documentation, Architecture, and Coding rules. Source policy is read for the queued source task but no protected input enters S1. |
| Verification | Documentation governance gate; review the dependency order against the M1 roadmap exit and verify no ROM/third-party material is tracked. |
| Expected Markers | One admitted T2 foundation task and ordered candidates for source pipeline, title runtime, and title oracle. |
| Asset Needs | None in S1. The later source-pipeline candidate requires an owner-local ROM and reviewed source admission. |
| Reporting Requirements | State why each task exists, its runnable deliverable, its dependency, and its M1 exit contribution. |
| Stop Conditions | Stop for owner direction if the first foundation task cannot build the same core for Win32 and the OpenNT 16-bit compiler without violating the platform boundary. |
| Exit Criteria | Queue has the ordered M1 implementation path, every candidate has an acceptance criterion, and T2 S2 can begin platform/build implementation directly. |
| Original Owner Request | Start M1 admission; first break down M1 T tasks and add them to the Queue. |
| Similar-Issue Sweep | Not applicable: S1 plans a new milestone rather than repairing an implementation defect. |

## Current Technical Baseline

- `mysmb` is a C90 skeleton only. The first runnable target is a native Win32 window built as x86 and x64. The core must remain compatible with the later 25 MHz 486SX real-mode DOS target, MS-DOS 5.0 or later, with DOS 3.3 desired. The OpenNT 16-bit C toolchain checks DOS compatibility; NTVDM64 is not a DOS graphics validation platform. No ROM, disassembly, translated game logic, native renderer, oracle, or ROM-derived executable is admitted.

## Recent M0 Closures

| Task | Compact result |
| --- | --- |
| T1 | M0 governance, source boundary, MTSP lifecycle, roadmap, and local documentation gate established at `3771fbc`; no ROM or third-party material admitted. [History](../history/M0-T1-governance-and-translation-plan.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
