# Project Status

## Current Work

M2 T1 S1 is admitted for the native title progression and deterministic
checkpoint core.

## M2 T1 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New |
| Admission And Approval | Owner approved M2 admission and task breakdown on 2026-09-23 after M1 closed at `8d0dea4`. |
| Objective | Translate the original title selection/start state route into portable C90, add neutral deterministic input/checkpoint ownership, and establish the first bounded native/reference transition checkpoint. |
| Non-goals | Do not implement area parsing, player physics, collision, enemies, death, warp, completion, audio playback, DOS graphics, a CPU, PPU, APU, generic bus, or a runtime `nnes` dependency. |
| Reference Baseline | M1 `8d0dea4`; owner-local SMB1 ROM and reviewed listing remain local research inputs; `nnes` remains a validation-only reference. |
| Candidate Proposal | [M2 native logic and oracle](../proposals/m2-native-logic-and-oracle.md) |
| Files And ABI Surface | `src/game/` title state, input latch, and neutral checkpoint contract; local-only source/ROM probe output; project-owned tests and optional local oracle tooling. |
| Applicable Rules | Task Reading Set; Execution, Documentation, Architecture, Coding, evidence, and source/research policies. |
| Verification | Build and test ROM-free x64/x86 cores, rebuild the OpenNT large-model core, and run a bounded owner-local title transition reference comparison without committing protected output. |
| Expected Markers | A source-address provenance record, deterministic fixed-input native title transition, and named checkpoint disposition exist without host leakage into `src/game/`. |
| Asset Needs | Owner-local ROM and reviewed source only; generated data, traces, screenshots, and executables remain ignored. |
| Reporting Requirements | Record source-address scope, state and input assumptions, reference revision, checkpoint results, difference disposition, and local-output cleanup. |
| Stop Conditions | Stop for owner direction if a required route cannot be isolated without an emulator, if source provenance diverges materially, or if local containment cannot be preserved. |
| Exit Criteria | The title selection/start route is represented by translated portable C90 state, has a deterministic native input/checkpoint test, and has a bounded local reference comparison with every difference dispositioned. |
| Original Owner Request | Produce an original-logic native C SMB1 implementation, first verifiable on Win32, portable toward real-mode 16-bit DOS, with no runtime NES emulator. |
| Similar-Issue Sweep | Inspect all current title input, frame, state, RAM, and renderer coupling before adding the route; record every production hit and disposition. |

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

## Recent Governance

- **M0 Td S2 P1:** Correct the platform plan: Win32 x86/x64 windows run the first native game; the shared C90 core remains 16-bit compatible, while DOS VGA awaits its dedicated adapter and 486SX validation.
