# Project Status

## Current Work

**Idle.**

M2 T1 closed after full PRG static analysis. The next candidate is title
selection/start translation using its actual-ROM route anchors.

## Current Technical Baseline

- `mysmb_game` is a C90 native title foundation with translated reset, OAM, name-table, and title-command routines. `mysmb_win32` builds x86 and x64 PE windows around that core; `mysmb_dos16_core` is its host-free DOS compiler input and has passed a local OpenNT large-model compile. Owner-local title data and CHR are generated only into ignored output. `nnes` is a validation-only local reference and is never linked into MySMB.

## Recent M0 Closures

| Task | Compact result |
| --- | --- |
| T1 | M0 governance, source boundary, MTSP lifecycle, roadmap, and local documentation gate established at `3771fbc`; no ROM or third-party material admitted. [History](../history/M0-T1-governance-and-translation-plan.md). |

## Recent M1 Closures

| Task | Compact result |
| --- | --- |
| T2 | Shared C90 core, x64/x86 Win32 window builds, and DOS16 compiler input established at `62e2d22`; both core smoke tests pass. [History](../history/M1-T2-win32-platform-foundation.md). |
| T5 | Local title oracle closes M1. The checkpoint mismatch is bounded and deferred to M2 state-route translation. [History](../history/M1-T5-title-oracle.md). |

## Recent M2 Closures

| Task | Compact result |
| --- | --- |
| T1 | Full direct-ROM PRG analysis, revision reconciliation, and source-address architecture record completed with zero unresolved PRG bytes. [History](../history/M2-T1-prg-static-analysis.md). |

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
