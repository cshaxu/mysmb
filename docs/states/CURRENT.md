# Project Status

## M2 T67 S4 Packet

| Field | Required record |
| --- | --- |
| Identifier Mode | Continuation: M2 T67 S4 P1 active; S1-S3 closed, T67 open. |
| Admission And Approval | Owner approved source-order continuation; coordinator admits11 planned noise nodes. |
| Objective | Audit/repair11 noise nodes,17 owned controls and material00442 against original source and ordered output. |
| Non-goals | No S5/N node promotion, platform logic or unrelated work. |
| Reference Baseline | Historical1992/1992; current exact1804/1992 nodes,3820/4290 feasible controls(raw4342,infeasible52),407/493 material partial. |
| Candidate Proposal | [T67 exact126-node plan](../proposals/m2/t67-cohort-m-sound-command-current-proof.md), S4 exact11-node scope. |
| Files And ABI Surface | src/game/audio.c and audio.h neutral APU ABI; test/tools probes and governance. |
| Applicable Rules | [Execution](../rules/EXECUTION.md), [Architecture](../rules/ARCHITECTURE.md), [Coding](../rules/CODING.md), [Documentation](../rules/DOCUMENT.md), [Source policy](../etc/operations/policy/source-policy.md); README Task Reading Set and admitted T67 proof program. |
| Verification | Unchanged F2D0 SoundEngine, actual NoiseSfxHandler and real RTS:4096 starts (256 queues by16 profiles),65536 continuations (256 buffers by256 lengths). Full1841 RAM/24 APU/ordered commands x86/x64, actual transitions and noise table reads. Zero flame envelope must fall through ContinueMusic to stream processing, not queue selection; real boundary callees run without S5 credit. |
| Expected Markers | Current pending11/intended fresh11, maximum1815/1992; historical expectedMatches empty. |
| Asset Needs | Owner-local ROM/reviewed ASM nonredistributable; ignored build/m2-t67-s4,128MiB raw,1024 roots/batch,120seconds/run,524288steps/root and cleanup. |
| Reporting Requirements | Report exact nodes/1992, feasible controls/total and material/partial total; distinguish historical1992; no promotion before both proof tracks. |
| Stop Conditions | Any scoped feasible diff or missing dual/edge/table proof keeps S4 open; S5 unadmitted. |
| Exit Criteria | 11 nodes and owned feasible controls/material00442 exact; tests/purity/OpenNT link pass; repair refreshes3 EXEs; ledger/tracker gates pass. |
| Original Owner Request | Complete M2 by original-ROM node and edge alignment in planned source order; repair within each S and report cumulative totals. |
| Similar-Issue Sweep | Table-result branch semantics, odd/divided indexes, terminal mute, live queue shifts and music stream-vs-selection handoff. |

## Current Technical Baseline

- Historical mapping: **1992/1992**, not current certification.
- Current exact nodes: **1804/1992**.
- Current exact feasible controls: **3820/4290** (raw4342,infeasible52).
- Exact material relations: **407/493**, enumeration partial.
- Latest three products are T66 S2 P2 builds including audio/title/focus pause.
- T67 S4 active:11 pending noise nodes/intended fresh11; no admission credit.
