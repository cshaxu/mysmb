# Project Status

## M3 T46 S1 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | New M3 T46; S1 active, S2 planned. Highest prior M3 identifier is T45. |
| Admission And Approval | Owner admits former queue position3, DOS16 cache allocation/performance qualification, and directs continuation. Single-person coordinator/executor. |
| Objective | Establish actual D/A/B/C allocation, near/far ownership, failure cleanup and natural versus injected memory-tier receipts. |
| Non-goals | No game/PPU semantics, cache policy, audio, Mine, Win32/Win16 behavior, DOSBox settings or extra cache changes. |
| Reference Baseline | 4b962237; accepted product code6d505085. |
| Candidate Proposal | [T46 allocation and tier qualification](../proposals/m3/dos16-ram-presenter-memory-tiers.md). |
| Files And ABI Surface | Mario DOS root read-only; mirrored test/tool instrumentation, estimated3-6files/150-300lines. No production ABI or allocation-policy change. |
| Applicable Rules | Task Reading Set, source policy, architecture/coding boundaries and long-running command rule. |
| Verification | Original DOS16 optimized compiler/linker; actual DOSBox run without configuration changes; explicit failure-injection owner tests; admission and closure gates. |
| Expected Markers | Empty ROM scope and expectedMatches; baseline1992/1992, maximum1992/1992; no new equivalence credit. |
| Asset Needs | Owner-local SMB ROM, existing qualified DOS toolchain and installed DOSBox; local build/probe containment only, no redistribution. |
| Reporting Requirements | Separate loader allocation, dynamic live bytes, free/largest block, natural availability and injected outcomes. Report each required/optional cache and cleanup. |
| Stop Conditions | No guessed memory threshold, changed emulator configuration, skipped required caches, protected artifact commit or game/PPU modification. |
| Exit Criteria | S1 allocation/failure matrix resolved with real runtime receipts and labelled injected cases; no leak or unreported missing required tier. S2 timing remains separate. |
| Original Owner Request | Admit queue3 DOS16 cache allocation and performance qualification. |
| Similar-Issue Sweep | Near/far allocation provenance, preflight versus real failure, required D/A/B exits, optional C binding, shutdown ownership and unsupported fallback. |

## Current Technical Baseline

T19 is accepted and closed. T46 S1 alone is active; four other candidates
retain their order. ABD is mandatory, C optional. Static source inspection
confirms the intended request order but is not runtime verification.
Historical1992/1992, retained1991/1992nodes and4260/4261feasible controls
(4342raw,81infeasible) unchanged; no whole-game certification claim.

## S roadmap

S1: actual allocation/ownership/failure receipts and cleanup.
S2: matched warmed title/gameplay ABD-versus-ABCD exact pixels and timing.
S2 is admitted only after S1 closure; no policy change is implied by measurement.
