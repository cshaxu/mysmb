# Project Status

## Current Work

**Idle.**

## Current Technical Baseline

- `mysmb` is a C90 skeleton only. Its primary target is a 25 MHz 486SX running real-mode MS-DOS 5.0 or later; the desired compatibility floor is MS-DOS 3.3. The OpenNT 16-bit C toolchain and NTVDM64 are M1 validation/build inputs. No ROM, disassembly, translated game logic, native renderer, oracle, or ROM-derived executable is admitted.

## Recent M0 Closures

| Task | Compact result |
| --- | --- |
| T1 | M0 governance, source boundary, MTSP lifecycle, roadmap, and local documentation gate established at `3771fbc`; no ROM or third-party material admitted. [History](../history/M0-T1-governance-and-translation-plan.md). |

## Recent Governance

- **M0 Td S1 P1:** Set real-mode DOS on a 25 MHz 486SX as the primary target; make the OpenNT 16-bit compiler and NTVDM64 part of the M1 build/validation route.
