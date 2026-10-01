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

Every M2 P that changes product code refreshes and reports all three target artifacts: `assets/mysmb16.exe`, `assets/mysmb32.exe`, and `assets/mysmb64.exe`, with their build/validation results. Audit-only, documentation-only and test-evidence-only P work does not require an artifact refresh. This delivery requirement is additive to, and cannot be substituted for, the node accounting and ordinary P evidence.

### Current-equivalence re-audit

Historical `ROM-match complete` accounting and a current-build equivalence
result are distinct facts. When a milestone-wide re-audit is active, every
progress or commit report must state: historical complete / total, current
exact nodes / 1,992, and current exact feasible control relations / 4,324
(the raw and infeasible counts when relevant). Reports must not call the
historical completion numerator a current end-to-end verification result. The current-equivalence registry owns
one of four states for every inventory label: `unclassified`, `exact`,
`needs-evidence`, or `mismatch`. A node enters `exact` only after its current
source audit and a current original-ROM route prove the required branch,
read/write, table and output contract. Route equality alone is evidence for
the executed chain; it does not classify unobserved labels.

The re-audit proceeds in source-order cohorts. Each cohort first records the
current shared-C owner and source dependency graph, then runs the original ROM
and current x86/x64 records under the same fixture. It records every compared
field and every explicit ABI exclusion. The graph audit is an equal acceptance
track: every extracted control relation (call, tail jump, branch, fall-through,
return and vector dispatch) and every material game-state producer-to-consumer
edge must have a current C counterpart and a disposition. A relation proven
impossible by the ROM's instruction semantics receives the explicit
`infeasible` disposition, remains in the raw extractor ledger with its proof,
and is excluded from the feasible-control denominator. Every feasible original
edge must have a current C counterpart. A route replay marks
only the nodes and edges it actually observes; it never infers coverage of an
unobserved graph connection. An S finding a feasible mismatch does not close
or advance to its successor. It becomes the corrective shared-owner chain (or
transfers that chain to an explicitly admitted corrective receiver), repairs
the mismatch, and repeats the same static and ROM/native audit until its
scoped feasible paths have no unresolved difference. Only then may the next
source-order S be admitted. No node promotion or "all complete" conclusion
may be made from a planning pass alone.

Before each M2 S, report both the number of unique labels in scope and the number expected to become complete; list both sets by exact inventory name, including incoming status. The expected set must be a subset of scope and exclude already completed nodes. The maximum closing numerator is the incoming completed count plus that expected count. A validation queue size is not an S estimate. Run `tools/Verify-NodeProgress.ps1 -AdmissionPath build/<task>/node-admission.json` and copy its named/countable result into the proposal and packet. The JSON fields are `baseline`, `total`, `scope` (label array), `expectedMatches` (label array), `maximumComplete`, `focusedTests` (test-name array), and `romRoute` (reproducible route description). Explicit empty arrays and zero expected matches are valid for mapping-only work. Closure reports expected versus actual labels/counts, explains misses and transfers, and updates the canonical rows before rerunning the gate.

## M2 Chain-Based S Delivery

An M2 implementation S is a bounded, contiguous ROM control/data chain, not a
fixed five-stage paperwork unit and not necessarily one label.  Its admission
must name the chain entry and exit, exact labels in source order, shared C
owner, predecessor/successor dependencies, and one ROM route that exercises
the chain.  A chain may contain adjacent data, loop and leaf labels when they
share that route and owner.

A chain must not cross an unadmitted dependency, a different ownership
boundary, or a branch family requiring a different ROM route.  An S may be an
explicit zero-credit audit only when it states the concrete missing dependency
or evidence.  Otherwise the same S performs the node mapping, any required
shared-C migration, ROM logic-equivalence comparison, and operational proof.

Node accounting remains individual: the inventory and ledger record every
label's control flow, reads, writes, data binding, caller/successor and final
status.  A chain-level ROM replay, focused tests, x86/x64 builds, DOS16 link,
platform-purity check, and refreshed three executable artifacts are run once
per implementation P, rather than recreated for each member label.  An S may
credit only the members proven by both tracks and transfers the rest by exact
name.  T closure adds a cross-chain route matrix and one final integrated
three-target regression; it does not repeat each member's already accepted
chain proof.

### M2 Chain Admission And Closure Reports

This delivery rule is **node-level in accountability and chain-level in
delivery**. The coordinator reports the exact nodes an S will attempt before
implementation begins, and reports their individual dispositions when that S
closes. This is the admission and closure work of the same S, never a new
paperwork phase.

An admitted chain groups adjacent nodes only when they share one contiguous
caller/data path, one shared-game owner, no unadmitted dependency between
them, and one reproducible original-ROM route. It splits at an ownership
boundary or when a materially different branch family needs a different route.
Small tables, loops and helper leaves that meet those conditions stay with
their consumer chain; a separate lifecycle is not justified merely because
they have separate inventory labels.

At admission, the proposal and active packet name the entry/exit, labels in
source order, incoming state, intended ROM-match subset, common C owner,
predecessor/successor dependency and the two verification plans. The
**ROM-logic track** proves table binding, control branches, reads, writes and
call order against a source-reachable or controlled original-ROM route. The
separate **operational track** proves focused tests, x86/x64 builds, DOS16
link, platform purity and the required three artifacts. One replay and one
build/package pass cover the chain; they are not recreated per member.

At closure, update the tracker and report each scoped label as ROM-match
complete, deferred with its failed track, or transferred by exact name. T
closure combines its S results in a cross-chain matrix and one integrated
three-target regression. It does not reopen accepted member proof unless a
regression identifies a concrete discrepancy.

## Per-Task Node Contract And Dual Verification

Before admitting an M2 T, publish its exact target labels and counts, their current receiving S, source-call dependencies, and planned S ownership. A T cannot be described only by a source-line span, feature name, or test suite. Its proposal and active packet must state which labels it intends to complete, which labels are only investigated, and the maximum resulting node count.

Each implementation T separates two independent acceptance tracks. **ROM logic-equivalence verification** compares original control branches, state/table reads, state writes, call order, and a source-reachable or controlled route against the native C owner. **Operational verification** runs focused tests, cross-width builds, DOS16 compilation, platform-purity checks, and applicable interactive or frame-route execution. A passing test, build, or visible game screen is not ROM-equivalence evidence; a successful ROM branch comparison is not proof that every target runs correctly.

At each T closure, update `states/NODE_PROGRESS.md` before reporting the result. The report names: planned target labels/count; labels made `ROM-match complete`; labels that remain incomplete with the specific failed track; labels transferred to a successor; both verification evidence sets; and the before/after complete count. The node ledger records custody and transfers, while `NODE_PROGRESS.md` remains the sole conformance-status authority.

## Node-to-S Responsibility And Transfers

The [node/task ledger](../states/NODE_TASK_LEDGER.md), generated from its
linked JSON, owns current receiving S and historical responsibility records;
the conformance inventory alone owns match status. Every inventory node must
have exactly one registered receiving S at all times. A closure backlog is an
accepted responsibility, not permission for concurrent execution. Historical
T-only evidence keeps its missing S explicit. Planned future T numbers are
not invented; an existing accountable S retains custody until admission.

Before every later T/S admission, register the T and S with proposal evidence,
role, receiving acceptance, and an exact `runs` entry: scope, baseline,
incomingComplete (exact already-complete names at admission),
expectedMatches, maximumComplete and initially empty actualMatches. Add
`taskId` (full M/T/S) and `kind` (`audit` or `implementation`) to the existing
node-admission JSON. Implementation admission requires that S to have received
every scope node; audit participation may overlap without transferring
implementation responsibility. The admission checker enforces both the
estimate and ownership contract. Empty scope is explicit for infrastructure S.

Ownership transfers are append-only events with a unique ID, exact labels,
current sender, registered receiver, acceptance attribution and reviewable
evidence. Validate a proposed event with `python tools/node_task_ledger.py
--transfer build/<task>/transfer.json`; then append it, update each node's
receiver, and regenerate with `--write`. The validator replays all events and
rejects missing or duplicate receivers, a wrong sender, unaccepted transfers,
unknown nodes/S IDs, and stale generated views. It never infers acceptance from
a sender's request. Coordinator acceptance under an explicit owner mandate
is permitted and must be attributed as such.

At S closure record actualMatches in its run and validate a closure JSON with
`taskId`, `actualMatches`, `complete`, `total`, and `evidence` using `--closure`.
Every retained unfinished node must first transfer to an accepted successor;
otherwise the S remains open, even if its metadata deliverable is finished.
Completed nodes keep a maintenance receiver. Never delete historic relations
or events to make closure pass. The documentation gate checks the ledger and
active packet registration. Query exact S node sets with `--subtask "M2 Tn Sm"`.

## Build Tree Hygiene

Build trees, generated C/data, traces, and ROM-derived executables are local outputs. Delete temporary products once no active S needs them; verify a target is beneath an ignored owned output directory before recursive cleanup.

## Recorder Trace Containment

An owner-ROM trace run declares a unique ignored output path, time/no-progress and byte budgets, checkpoints, and cleanup owner. Raw traces are never fixtures or committed evidence; retain only neutral summaries needed by an admitted S.
