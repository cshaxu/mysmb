# Execution Policy

This file owns MySMB task lifecycle, M/T/S/P identifiers, evidence, and closure. One S is active at a time.

## Request Lifecycle

Discussion and read-only research need no active packet. Before any change, the coordinator creates the sole active packet in `states/CURRENT.md`, after owner approval and proposal review. It must contain the fixed `Field | Required record` table with: Identifier Mode, Admission And Approval, Objective, Non-goals, Reference Baseline, Candidate Proposal, Files And ABI Surface, Applicable Rules, Verification, Expected Markers, Asset Needs, Reporting Requirements, Stop Conditions, Exit Criteria, Original Owner Request, and Similar-Issue Sweep.

## Roles And Execution Cycle

The coordinator admits, scopes, reviews, and closes work. An executor may question and complete only the admitted S. A material scope or policy objection pauses affected work for coordinator direction. Review compares the owner request, packet, rules, evidence, and actual Git diff.

## Change Discipline

Preserve unrelated changes. Every implementation repair records a similar-issue sweep: the defect class, search scope, every production hit and disposition, and post-fix verification. Work outside scope is deferred to `TODO.md` or a later candidate.

## Work Identifiers

Use `M<milestone> T<task> S<subtask> P<part>` for implementation and its design prerequisites. `M<milestone> Td S<subtask> P<part>` is reserved for an approved standalone governance task. A P is one complete reviewable commit.

## Linear Identifier Allocation

Queue candidates remain unnumbered. On approval, allocate the next ascending T and create one active packet. `New` starts `S1`; `Continuation` uses the latest open T and next S; `Corrective` is limited to the latest closed T; `Governance` allocates the next milestone-local Td S. Completed numeric tasks receive a record under `history/` and their proposal is retained there.

## Documentation Governance Gate

Every closure runs `powershell -NoProfile -ExecutionPolicy Bypass -File tools/Verify-DocumentationGovernance.ps1 -RepositoryRoot .`. The gate checks topology, required authorities, links, active-packet fields, and absence of local paths in tracked Markdown. Passing it does not replace a semantic review.

## Milestone Closure Evidence

A milestone closes only when its roadmap exit criteria, task evidence, deferred debt, source policy, and applicable tests agree. Local ROM-derived executables are not release evidence and are never committed.

## M2 ROM-node Progress Accounting

The [M2 ROM-node progress report](../states/NODE_PROGRESS.md), its linked inventory, and the [node-backfill validation matrix](../etc/architecture/m2-node-backfill-validation-matrix.md) are the sole quantitative basis for M2 conformance progress. Before work starts, every S admission must record its incoming ROM-match-complete / total fraction, the exact inventory labels in scope, the exact subset expected to become matches, the maximum expected resulting fraction, and its focused CTest plus original-ROM route baseline. An S closure must record the resulting fraction, every completed and deferred label by name, and the ROM-reference evidence that justifies each newly completed node. A C owner, source move, unit test, or build alone remains unfinished.

Every M2 P continues to refresh and report all three target artifacts: `assets/mysmb16.exe`, `assets/mysmb32.exe`, and `assets/mysmb64.exe`, with their build/validation results. This delivery requirement is additive to, and cannot be substituted for, the node accounting and ordinary P evidence.

## Build Tree Hygiene

Build trees, generated C/data, traces, and ROM-derived executables are local outputs. Delete temporary products once no active S needs them; verify a target is beneath an ignored owned output directory before recursive cleanup.

## Recorder Trace Containment

An owner-ROM trace run declares a unique ignored output path, time/no-progress and byte budgets, checkpoints, and cleanup owner. Raw traces are never fixtures or committed evidence; retain only neutral summaries needed by an admitted S.
