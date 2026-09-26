# M2 node-to-subtask responsibility ledger

## Admission

M2 T24 S2 continues the owner-requested audit. The owner explicitly requested
a ledger connecting every node to previous and future T/S tasks, with a
receiving responsibility for every node. This authorizes responsibility
registration and governance tooling, not implementation repairs or concurrent
execution of the receiving backlog.

Scope: all 1,992 exact canonical inventory labels, incoming statuses unchanged.
Baseline and maximum closing conformance: 3 / 1,992. Expected newly matched
labels: empty (zero). Tests: ledger consistency, admission/transfer rejection
checks and documentation governance. ROM route baseline: the retained T24 S1
six-route report; this metadata task creates no ROM runs or target artifacts.

## Contract

The machine-readable ledger has one current receiving S per node, an evidence
backed history of task/subtask mentions, a task/subtask registry, and replayable
accepted assignment/transfer events. A historical T-only record keeps a null S
and an explicit historical gap; no S1 is invented. Planned S responsibilities
are not claims of execution or node completion.

Existing open slice tasks receive their nodes through their already documented
verification/closure S. Closed-root and unnumbered screen/dispatcher work stays
in explicit M2 T24 S2 custody with a linked unnumbered receiving candidate,
until an admitted future T/S accepts it. This custodian cannot disappear or
close while it holds unfinished nodes. Numeric future task IDs are allocated
only on admission. Every later admission must register its T/S and exact node
set; changes of primary ownership require an accepted transfer event.

Historical evidence and all-node audit/census participation may overlap;
current responsibility cannot. The reverse view lists exact node names and
counts per receiving S, plus all known historical T/S records. Conformance
status remains exclusively in the canonical inventory, not copied into a
second mutable authority.

## Review

Check all 1,992 unique label/line pairs, registered receivers, evidence paths,
event continuity, receiver counts, exact planned/actual sets and custody of
unassigned future work. Reject unknown nodes, duplicate ownership, deletion of
the last receiver, unaccepted transfers, stale admission baselines, and closure
with unfinished retained nodes. Preserve unrelated production/test changes.
