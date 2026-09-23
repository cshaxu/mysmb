# Project Status

## Current Work

M1 T3 S2 is admitted to convert the verified reset-memory dependency into portable native C.

## M1 T3 S2 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation |
| Admission And Approval | Owner approved M1 execution and the native-C/no-emulator route on 2026-09-22; T3 S1 established local containment and verified the reset slice. |
| Objective | Replace the T2 placeholder state with a portable C90 owner for original `$0000-$07ff` RAM and OAM, and translate the verified `$90cc-$90e6` reset-memory routine as named native logic. |
| Non-goals | Do not commit ROM bytes, CHR, source listing, generated code/data, screenshots, traces, or ROM-embedded executable; do not introduce a CPU, PPU, APU, instruction decoder, or generic memory bus. |
| Reference Baseline | T3 S1 `1af9abf`; owner-local ROM; byte-for-byte verified `$90cc-$90e6` reset routine; public sources remain local research references only. |
| Candidate Proposal | [M1 static-C source pipeline](../proposals/m1-source-corpus-and-local-toolchain.md) |
| Files And ABI Surface | `src/game/` portable RAM/OAM state and reset routine; neutral game frame contract; project-owned unit test. |
| Applicable Rules | Task Reading Set; Execution, Documentation, Architecture, Coding, and source/research policies. |
| Verification | Unit-test cold and warm reset ranges, preserved stack range, and OAM ownership; run CMake C90 builds and inspect for no platform dependencies in `src/game/`. |
| Expected Markers | Named RAM/OAM state, address provenance, static reset implementation, and neutral test exist without protected material in Git. |
| Asset Needs | Owner-local ROM only for address verification; no ROM-derived payload enters tracked files. |
| Reporting Requirements | Report verified address span, reset semantics, build/test result, source containment, and any deferred reset dependency. |
| Stop Conditions | Stop for owner direction if verified ROM bytes disagree with the stated routine span or if conversion requires a generic emulator abstraction. |
| Exit Criteria | The portable game core owns the required original RAM/OAM state and reproduces the verified reset-memory writes as native C without runtime instruction interpretation. |
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
