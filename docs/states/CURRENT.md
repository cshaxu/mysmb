# Project Status

## Current Work

M1 T3 S1 is admitted to implement the local static-C source pipeline.

## M1 T3 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New |
| Admission And Approval | Owner approved M1 execution and specified the owner-local SMB1 ROM route on 2026-09-22; T2 closed at `5cb6ff4`. |
| Objective | Bind the selected owner-local ROM and a reviewed SMB1 assembly listing to a bounded parser/generator that emits ignored C90 translation units and an address map for the boot/title dependency slice. |
| Non-goals | Do not commit ROM bytes, CHR, source listing, generated code/data, screenshots, traces, or ROM-embedded executable; do not run a 6502 emulator in the product. |
| Reference Baseline | T2 foundation `5cb6ff4`; owner-local ROM route `nxvm-assets/roms-mynes/smario1.nes`; `nnes` is a later validation-only reference. |
| Candidate Proposal | [M1 static-C source pipeline](../proposals/m1-source-corpus-and-local-toolchain.md) |
| Files And ABI Surface | Ignored local input binding and generated output; project-owned parser/generator, address-map metadata format, root CMake integration, and tests. |
| Applicable Rules | Task Reading Set; Execution, Documentation, Architecture, Coding, and source/research policies. |
| Verification | Identify ROM header and mapper locally; verify each generated output is ignored; run generator deterministically; compile generated C through `mysmb_game`; inspect address-map coverage for its admitted boot/title slice. |
| Expected Markers | Local input configuration, project-owned generator, generated C90 unit, neutral address map, and build target exist without protected material in Git. |
| Asset Needs | One owner-local ROM and one separately reviewed assembly listing, neither committed. |
| Reporting Requirements | Record input identity only in local ignored metadata; report provenance review, generated slice coverage, build/test result, output containment, and unresolved listing/tool gaps. |
| Stop Conditions | Stop for owner direction if the selected ROM does not match the reviewed listing, the listing lacks a clear redistribution/reuse basis, or generated output cannot be contained locally. |
| Exit Criteria | The boot/title dependency slice has a reproducible local C90 generation path, provenance/address mapping, and a successful compile without a runtime 6502 emulator. |
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
