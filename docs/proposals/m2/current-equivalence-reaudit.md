# M2 current-equivalence re-audit

## Purpose

The historical node inventory says every one of the 1,992 labels has a
ROM-match-complete record. That remains useful accountability evidence, but it
does not make a fresh current-build, whole-graph equivalence claim. Later
shared-core migrations can repair a historical mismatch, invalidate a stale
fixture, or regress a route outside the original node's local test. This audit
makes the current result observable before any further repair task is planned.

## Td S9 scope

Td S9 is governance and audit setup only. It creates separate current node and
edge registries, extracts the complete original ROM graph, allocates all
labels and edges into source-order cohorts, and defines a uniform source/route
comparison contract. It admits no production code and grants no node credit.
Its input is the owner-local ROM and reviewed source listing, used only below
ignored `build/` paths according to the source policy.

The baseline deliberately has two values:

| Measure | Value | Interpretation |
| --- | ---: | --- |
| Historical node accounting | 1,992 / 1,992 | Prior per-node completion claims retained for traceability. |
| Current-equivalence audit | 0 / 1,992 classified | No cohort has yet completed the new, uniform current-build audit. |

The full cohort allocation and live counts are in
[M2 current-equivalence re-audit](../../states/M2_CURRENT_EQUIVALENCE.md).

## Node and edge acceptance

The audit has two mandatory and independent ledgers:

| Ledger | Unit | Required comparison |
| --- | --- | --- |
| Node | Every original label | Original control semantics, reads, writes, table binding and C owner. |
| Edge | Every original connection | C counterpart for call/tail-jump, branch, fall-through, return, vector dispatch and material RAM/table producer-to-consumer relationship. |

The edge extractor records a stable endpoint/type identity and a source
address. It reports the canonical control total before classification begins;
no planning estimate may replace that total. The companion registry builder
allocates every node and control edge once to a source-order cohort. Material
RAM/table edges are added only after a source-path review proves a producer,
consumer and feasible path; a static writer-reader cross product is not an
edge registry. A dynamic route can mark only the nodes and edges it actually
executes. Static source review checks every other edge. A node cannot be
current-exact if an owned required edge is mismatched; an edge cannot be
current-exact merely because both endpoints have local tests.

`exact` is a whole-chain claim for the audited scope. For every candidate
node, the audit must enumerate all original incoming and outgoing control
relations, including call, tail-jump, conditional, fall-through, return and
selector-dispatch relations. Each relation receives a separate current C
counterpart, predicate/order contract and evidence. A node can therefore be
locally output-equal yet remain `needs-evidence` when one of its relations has
not been audited. The same rule applies to each proven feasible material data
edge: producer write or table selection, consumer read/index and the state
handoff path are independently compared. No endpoint result implies an edge
result, and no edge result implies a node result.

Each source-order cohort is reviewed in two ordered passes. First, the
**node-semantics pass** writes a contract for every label: predicates,
reads/writes, table binding, outputs and current shared-C owner. It compares
those contracts with controlled ROM and native routes and assigns a node
disposition. Second, the **integration pass** independently walks every
original outgoing and incoming control relation, then each proven material
producer-to-consumer data relation. It verifies counterpart, condition,
ordering, return/dispatch behavior and state handoff. A matching node pair is
not evidence that the edge between them is correct. A cohort may report local
node results before its edge pass finishes, but cannot be described as
current-equivalent or closed until both ledgers have a disposition for its
scope.

## Execution order

The audit follows cohorts A through N in original source order. One cohort may
be split only at a different shared-C owner or a different ROM route family;
the split must retain source order and an exact label list. Each cohort has two
independent tracks:

- **Logic track:** original branch/control flow, state/table reads, writes and
  caller/successor order are compared against the current shared C owner.
- **Operational track:** an owner-local original-ROM route and current x86/x64
  route run with the same fixture. Persistent RAM, CIRAM, palette, visible OAM,
  PPU and audio output are compared. OpenNT DOS16 continues to compile the
  same shared source, but its separate resource binding is not treated as game
  logic evidence.

Every cohort reports exact, needs-evidence and mismatch labels **and edges**
separately.
An exact output trace without branch coverage is `needs-evidence`, not exact.
A mismatch report contains the first divergent field/frame, original source
entry, C owner and smallest contiguous candidate repair chain.

## Repair planning after audit evidence

There are no preallocated repair T numbers. Td S9 appends only unnumbered
queue candidates, ordered by source position, after a mismatch is confirmed.
Each candidate contains the precise chain, owner, predecessor/successor,
reproduction route and expected label delta. On later owner approval it
receives the next ascending T number and bounded S breakdown. This prevents a
historical TODO item or a single stale trace from becoming an ad-hoc repair.

## Td S9 exit

The registry has all 1,992 labels allocated once; the complete ROM graph has a
canonical edge total and every edge is allocated once; the reporting and
evidence format distinguishes historical accounting from current equivalence;
and the queue has a reviewable, source-order candidate format. Then cohorts
execute without changing this governance contract unless the audit itself
proves it insufficient.

## Td S9 closure: current-equivalence governance

Td S9 closes with zero implementation-node credit.  The historical ledger
remains **1,992 / 1,992**; that numerator is retained only as prior
per-node completion accounting and is not a fresh equivalence assertion.

The current registry is complete as a governance deliverable: all 1,992 ROM
labels, 4,342 extracted control relations and 487 currently proven feasible
material relations have one source-order cohort allocation, a semantic or
integration disposition, and a current shared-C source-path anchor.  Its
closing dispositions are 38 exact, 1,944 needs-evidence and 10 mismatch
nodes; 76 exact, 4,241 needs-evidence and 25 mismatch control edges; and
3 exact, 483 needs-evidence and 1 mismatch material relations.  The
needs-evidence entries remain deliberately unpromoted until their required
branch/table/read-write route is observed or source-proved.

The ordered queue records every confirmed discrepancy without assigning a new
numeric T.  The first executable repair remains the A2 NMI-prefix chain:
`RotPRandomBit -> SkipSprite0 -> OperModeExecutionTree`, with the enclosing
`NonMaskableInterrupt` handoff.  It belongs to the still-open T51 continuation
rather than a new task number.  Td S9 changed no production or platform source,
created no artifact, and did not assert M2 closure.
