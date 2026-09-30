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
address. It reports the canonical total before classification begins; no
planning estimate may replace that total. A dynamic route can mark only the
nodes and edges it actually executes. Static source review checks every other
edge. A node cannot be current-exact if an owned required edge is mismatched;
an edge cannot be current-exact merely because both endpoints have local
tests.

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
