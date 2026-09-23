# Project Status

## Current Work

**Idle.**

## Current Technical Baseline

- `mysmb` is a C90 skeleton only. The first runnable target is a native Win32 window built as x86 and x64. The core must remain compatible with the later 25 MHz 486SX real-mode DOS target, MS-DOS 5.0 or later, with DOS 3.3 desired. The OpenNT 16-bit C toolchain checks DOS compatibility; NTVDM64 is not a DOS graphics validation platform. No ROM, disassembly, translated game logic, native renderer, oracle, or ROM-derived executable is admitted.

## Recent M0 Closures

| Task | Compact result |
| --- | --- |
| T1 | M0 governance, source boundary, MTSP lifecycle, roadmap, and local documentation gate established at `3771fbc`; no ROM or third-party material admitted. [History](../history/M0-T1-governance-and-translation-plan.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
