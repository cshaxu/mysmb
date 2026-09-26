# Node/task ledger workflow

The [execution policy](../../rules/EXECUTION.md#node-to-s-responsibility-and-transfers)
owns the rule. The [ledger view](../../states/NODE_TASK_LEDGER.md) is generated
from JSON and provides both node-to-S and S-to-node lookup. These commands
read neutral metadata only and never repair gameplay or run ROM material.

## Find the exact current and historical scope

```powershell
python tools/node_task_ledger.py --subtask "M2 T19 S3"
python tools/node_task_ledger.py
```

`received` is the current primary responsibility. `historical` is the exact
set mentioned in recorded sections, with relation/evidence details in JSON.
`runs` contains admitted estimates and actual names. A historical mention is
not automatically implementation ownership or a completed match. Unknown old
S numbers remain null; consult the linked T evidence rather than guessing S1.

## Register a future T/S

Allocate the next T or S according to the execution policy and active packet.
Add the task/subtask registry entry with proposal evidence. An accepting S
has `canReceive: true`, `receipt` stating the actual acceptance authority,
`admissionRole` of `implementation` or `audit`, and `recordKinds` describing
the basis. A candidate without allocated T/S stays in `futurePackages` with
an explicit registered custodian. Its ID is not a numeric implementation T.

For implementation work, record two independent evidence tracks in the
proposal and closure report: ROM logic-equivalence (original branches, reads,
writes, tables, call order and a reachable or controlled route) and operational
test/run verification (focused tests, target builds, DOS16 compilation and
applicable runtime routes). Passing either track never substitutes for the
other. Update `NODE_PROGRESS.md` with exact completed, incomplete, and
transferred labels before reporting a T closure.

Register a `runs` entry with the exact full S ID, kind, scope, baseline,
incomingComplete names, expectedMatches, maximumComplete, actualMatches,
evidence and state. Incoming-complete names are a frozen admission snapshot;
they prevent counting the same completion again. Audit and conformance are
separate: a ledger-only run forecasts and produces zero new matches.

## Accept an ownership transfer

Save an event under `build/<task>/transfer.json` with this shape, replacing the
example IDs/names with the actually approved receiver and exact node set:

```json
{
  "id": "transfer-unique-id",
  "type": "transfer",
  "from": "M2 T24 S2",
  "to": "M2 T25 S1",
  "nodes": ["Start"],
  "acceptedBy": "Named accepting authority and approval basis",
  "evidence": "docs/proposals/m2/approved-receiver.md"
}
```

The example does not register or admit T25. The real receiver and evidence
must exist first. A sender cannot invent the receiver's acceptance.

```powershell
python tools/node_task_ledger.py --transfer build/<task>/transfer.json
```

After validation, append the event to JSON and update the listed node receivers.
Clear `futurePackage` only when actual implementation responsibility is
accepted. Keep all previous events and historical relations. Then run:

```powershell
python tools/node_task_ledger.py --write
powershell -NoProfile -ExecutionPolicy Bypass -File tools/Verify-NodeProgress.ps1 -RepositoryRoot . -AdmissionPath build/<task>/node-admission.json
```

The admission file includes `taskId` and `kind` as well as the established
baseline/total/scope/expectedMatches/maximumComplete/focusedTests/romRoute
fields. Its scope and forecast must agree exactly with a registered run.
Implementation scope must already belong to that S. Read-only audit scope may
overlap other receiving responsibilities without claiming their implementation.

## Record actual progress and close

Update individual inventory evidence before claiming a new match. Record the
exact newly completed names in the run's actualMatches; do not include names
already complete at admission. Transfer every unfinished retained node to an
accepted successor. Save a closure file with taskId, actualMatches, complete,
total and evidence, then run `python tools/node_task_ledger.py --closure
build/<task>/closure.json`. A completed metadata deliverable with unfinished
custody keeps its S open until transfer; it is not a reason to drop nodes.

Regenerate the view and run the documentation gate after every change. Zero
orphan nodes and consistent counts prove ledger integrity, not ROM conformance.

## Initial validation record

T24 S2 registered all 1,992 nodes with ten receiving subtasks. The registry
contains 40 known T records and 53 historical/planned S records. Future work
has 138 explicit custodial receipts, not unassigned nodes. Tests passed 17
scenarios: 15 malformed/orphan/stale/unaccepted/double-counting cases rejected,
one accepted-transfer replay, and one closure after complete custody transfer.
The test-only future S was never written to the real ledger. Documentation,
admission and diff checks pass. No product source/test/asset changes belong to
this ledger task.
