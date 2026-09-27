"""Validate and render the neutral node/T/S responsibility ledger.

No ROM input, production source edits, or implicit ownership transfers.
"""
import argparse
import json
import re
from collections import Counter, defaultdict
from pathlib import Path


def require(condition, message):
    if not condition:
        raise ValueError(message)


def read_json(path):
    return json.loads(Path(path).read_text(encoding="utf-8-sig"))


def inventory(root, path):
    result = {}
    for line in (root / path).read_text(encoding="utf-8").splitlines():
        if re.match(r"^\|\s*\d+\s*\|", line):
            cells = [x.strip() for x in line.split("|")[1:-1]]
            name = cells[1].strip("`")
            require(name not in result, "Duplicate inventory node: " + name)
            result[name] = (int(cells[0]), cells[3])
    return result


def unique_labels(labels, known, context):
    require(isinstance(labels, list), context + " must be a label array")
    require(len(labels) == len(set(labels)), context + " contains duplicate nodes")
    require(set(labels) <= set(known), context + " contains unknown nodes")


def evidence(root, path):
    require(isinstance(path, str) and path, "Missing evidence path")
    p = Path(path)
    require(not p.is_absolute() and ":" not in path and ".." not in p.parts,
            "Evidence must be repository-relative: " + path)
    require((root / p).is_file(), "Missing evidence: " + path)


def validate(root, data):
    require(data.get("schemaVersion") == 1, "Unsupported ledger schema")
    inv = inventory(root, data["inventory"])
    require(len(inv) == data["total"], "Ledger denominator differs from inventory")
    registry = {}
    tasks = {}
    for task in data["tasks"]:
        tid = task["id"]
        require(re.fullmatch(r"M\d+ T(?:\d+|d)", tid), "Invalid task ID: " + tid)
        require(tid not in tasks, "Duplicate task: " + tid)
        tasks[tid] = task
        require(task["evidence"], "Task needs evidence: " + tid)
        for path in task["evidence"]:
            evidence(root, path)
        for sub in task["subtasks"]:
            sid = sub["id"]
            require(re.fullmatch(re.escape(tid) + r" S[1-9]\d*", sid), "Wrong subtask parent: " + sid)
            require(sid not in registry, "Duplicate subtask: " + sid)
            registry[sid] = sub
            require(sub["evidence"], "S needs evidence: " + sid)
            for path in sub["evidence"]:
                evidence(root, path)
            require(sub["admissionRole"] in ("audit", "implementation"), "Unknown S role")
            if sub["canReceive"]:
                require(bool(sub.get("receipt")), "Receiving S needs acceptance: " + sid)
    packages = {}
    for package in data["futurePackages"]:
        require(package["id"] not in packages, "Duplicate future package")
        packages[package["id"]] = package
        evidence(root, package["proposal"])
        require(package["reason"], "Future package needs a reason")
        if "plans" in package:
            unique_labels(package["scope"], inv, "Queued package scope")
            require(package["scopeCount"] == len(package["scope"]), "Queued package scope count differs")
            require(set(package["incomingStates"]) == set(package["scope"]), "Queued package incoming-state snapshot incomplete")
            primary = []
            plan_ids = set()
            for plan in package["plans"]:
                require(re.fullmatch(r"S[1-9]\d*", plan["id"]), "Invalid planned S slot")
                require(plan["id"] not in plan_ids, "Duplicate planned S slot")
                require(set(plan["dependsOn"]) <= plan_ids, "Planned S dependency is missing or forward/cyclic")
                plan_ids.add(plan["id"])
                unique_labels(plan["scope"], inv, "Planned S scope")
                unique_labels(plan["expectedMatches"], inv, "Planned S expected matches")
                require(plan["scopeCount"] == len(plan["scope"]), "Planned S count differs")
                require(set(plan["expectedMatches"]) <= set(plan["scope"]), "Planned forecast outside scope")
                require(plan["focusedTests"] and plan["romRoute"], "Planned S needs validation targets")
                require(plan["scopeRole"] in ("primary", "integration"), "Unknown planned S scope role")
                if plan["scopeRole"] == "primary":
                    primary.extend(plan["scope"])
                else:
                    require(not plan["scope"], "Integration S must not duplicate primary node credit")
            require(len(primary) == len(set(primary)), "Node assigned to multiple planned primary S slots")
            require(set(primary) == set(package["scope"]), "Queued S plans omit or add package nodes")
            proposal = (root / package["proposal"]).read_text(encoding="utf-8")
            named = re.findall(r"(?m)^\|\s*\d+\s*\|\s*`([^`]+)`\s*\|", proposal)
            require(len(named) == len(set(named)) and set(named) == set(primary), "Proposal exact-node rows differ from queued plan")
    node_map = {}
    for node in data["nodes"]:
        n = node["label"]
        require(n not in node_map, "Duplicate node ownership: " + n)
        require(n in inv and node["line"] == inv[n][0], "Unknown/moved node: " + n)
        node_map[n] = node
        sid = node["receiver"]
        require(sid in registry and registry[sid]["canReceive"], "No registered receiver: " + n)
        require(node["receivingBasis"], "Missing responsibility basis: " + n)
        if node["futurePackage"] is not None:
            require(node["futurePackage"] in packages, "Unknown future package: " + n)
            require(registry[sid]["admissionRole"] == "audit", "Future candidate needs explicit audit custody")
        require(node["history"], "Node needs historical evidence or an explicit audit record")
        for item in node["history"]:
            require(item["task"] in tasks, "Unknown historical task")
            if item["subtask"] is not None:
                require(item["subtask"] in registry and item["subtask"].startswith(item["task"] + " S"),
                        "Unknown/misparented historical S")
            require(item["relation"], "Historical relation must state its evidence boundary")
            evidence(root, item["evidence"])
    require(set(node_map) == set(inv), "Inventory has nodes without receivers")
    owners = {}
    ids = set()
    for event in data["events"]:
        require(event["id"] not in ids, "Duplicate event ID")
        ids.add(event["id"])
        apply_event(root, event, owners, registry, inv)
    require(owners == {n: x["receiver"] for n, x in node_map.items()},
            "Current owners differ from accepted event history")
    for run in data["runs"]:
        require(run["subtask"] in registry, "Unknown run S")
        require(run["kind"] == registry[run["subtask"]]["admissionRole"], "Run role differs from S registry")
        for field in ("scope", "expectedMatches", "actualMatches", "incomingComplete"):
            unique_labels(run[field], inv, "Run " + field)
        require(set(run["expectedMatches"]) <= set(run["scope"]), "Run forecast outside scope")
        require(set(run["actualMatches"]) <= set(run["scope"]), "Run actual outside scope")
        require(len(run["incomingComplete"]) == run["baseline"], "Run incoming completed-name count differs")
        require(not set(run["expectedMatches"]) & set(run["incomingComplete"]), "Run forecast double-counts existing matches")
        require(not set(run["actualMatches"]) & set(run["incomingComplete"]), "Run actual double-counts existing matches")
        require(run["maximumComplete"] == run["baseline"] + len(run["expectedMatches"]), "Run forecast count differs")
        evidence(root, run["evidence"])
    current = (root / "docs/states/CURRENT.md").read_text(encoding="utf-8")
    for sid in re.findall(r"(?m)^## (M\d+ T(?:\d+|d) S\d+) Packet\s*$", current):
        require(sid in registry, "Active packet S must be registered: " + sid)
        require(any(r["subtask"] == sid for r in data["runs"]), "Active S needs a registered exact scope and forecast: " + sid)
    return inv, registry, node_map


def apply_event(root, event, owners, registry, inv):
    require(event["type"] in ("accept", "transfer"), "Unknown ownership event")
    unique_labels(event["nodes"], inv, "Event nodes")
    require(event["nodes"], "Empty ownership event")
    require(event.get("acceptedBy"), "Unaccepted handoff")
    evidence(root, event["evidence"])
    target = event["to"]
    require(target in registry and registry[target]["canReceive"], "Unregistered receiving S")
    if event["type"] == "accept":
        require(event["from"] is None, "Initial acceptance must start without an owner")
        require(all(n not in owners for n in event["nodes"]), "Duplicate initial acceptance")
    else:
        require(event["from"] in registry and event["from"] != target, "Invalid transfer source/target")
        require(all(owners.get(n) == event["from"] for n in event["nodes"]), "Transfer sender does not own every node")
    for n in event["nodes"]:
        owners[n] = target


def check_admission(root, data, context, admission):
    inv, registry, nodes = context
    sid = admission.get("taskId")
    require(sid in registry, "Admission must name a registered taskId including S")
    require(admission.get("kind") in ("audit", "implementation"), "Admission needs kind")
    require(admission["kind"] == registry[sid]["admissionRole"], "Admission role differs from registry")
    scope, expected = admission["scope"], admission["expectedMatches"]
    unique_labels(scope, inv, "Admission scope")
    unique_labels(expected, inv, "Admission forecast")
    complete = {n for n, (_, s) in inv.items() if s == "ROM-match complete"}
    require(admission["baseline"] == len(complete) and admission["total"] == len(inv), "Stale admission baseline")
    require(set(expected) <= set(scope) and not set(expected) & complete, "Invalid forecast subset")
    require(admission["maximumComplete"] == len(complete) + len(expected), "Wrong closing forecast")
    require(admission.get("focusedTests") and admission.get("romRoute"), "Admission needs validation baseline")
    if admission["kind"] == "implementation":
        require(all(nodes[n]["receiver"] == sid for n in scope), "S must receive nodes before implementation admission")
    runs = [r for r in data["runs"] if r["subtask"] == sid and r["scope"] == scope and r["expectedMatches"] == expected
            and r["baseline"] == admission["baseline"] and r["maximumComplete"] == admission["maximumComplete"]]
    require(runs, "Admission scope/forecast must first be registered in ledger runs")
    require(any(set(r["incomingComplete"]) == complete and not r["actualMatches"] for r in runs),
            "Admission needs a fresh incoming-complete snapshot and no claimed actual matches")


def check_closure(root, data, context, closure):
    inv, registry, nodes = context
    sid = closure["taskId"]
    require(sid in registry, "Closure has unknown S")
    evidence(root, closure["evidence"])
    actual = closure["actualMatches"]
    unique_labels(actual, inv, "Closure actual matches")
    complete = {n for n, (_, s) in inv.items() if s == "ROM-match complete"}
    require(set(actual) <= complete, "Closure claims unverified matches")
    require(closure["complete"] == len(complete) and closure["total"] == len(inv), "Closure aggregate is stale")
    require(any(r["subtask"] == sid and set(actual) <= set(r["scope"]) and r["actualMatches"] == actual for r in data["runs"]),
            "Closure actual set not recorded in S run")
    retained = [n for n in nodes if nodes[n]["receiver"] == sid and n not in complete]
    require(not retained, "S cannot close while retaining unfinished nodes: " + ", ".join(retained[:5]))


def markdown(data):
    nodes = data["nodes"]
    history_by_s = defaultdict(set)
    history_by_t = defaultdict(set)
    for n in nodes:
        for h in n["history"]:
            history_by_t[h["task"]].add(n["label"])
            if h["subtask"]:
                history_by_s[h["subtask"]].add(n["label"])
    def link(path):
        return "[record](../../" + path + ")"
    text = """# Node-to-task responsibility ledger

Generated from [NODE_TASK_LEDGER.json](NODE_TASK_LEDGER.json) by
`python tools/node_task_ledger.py --write`. JSON owns responsibility/history;
the [inventory](../etc/architecture/smb1-rom-migration-inventory.md) alone owns
conformance. This view must not be edited independently.

Every node has exactly one receiving S. Receipt is accountable backlog
ownership, not simultaneous active execution or a completion claim. Historical
mentions can overlap; historical T-only records retain an unknown S instead
of inventing one. Future tasks register and accept transfers on admission.
T24 S2 retains explicit custody of closed-root/unallocated candidates until
an admitted successor accepts them; it cannot close with unfinished custody.

## Receiving subtasks

| Receiving S | Exact node count | Exact node set |
| --- | ---: | --- |
"""
    for sid in sorted({n["receiver"] for n in nodes}):
        labels = [n["label"] for n in nodes if n["receiver"] == sid]
        text += "| " + sid + " | " + str(len(labels)) + " | " + ", ".join("`"+n+"`" for n in labels) + " |\n"
    text += "\n## Future admission packages and queued plans\n\nCustody is a current receipt. Planned coverage is a queued scope and does not\ntransfer existing ownership or allocate a numeric T.\n\n| Candidate | Nodes held in custody | Queued scope / S slots | Admission path / reason |\n| --- | ---: | --- | --- |\n"
    for p in data["futurePackages"]:
        planned = f'{len(p["scope"])} nodes / {len(p["plans"])} planned S' if "plans" in p else "not decomposed here"
        text += f'| {p["id"]} | {sum(n["futurePackage"] == p["id"] for n in nodes)} | {planned} | {link(p["proposal"])}; {p["reason"]} |\n'
    text += "\n## Every node\n\n| ROM line | Node | Current receiving S | Future package / basis | Historical T/S records |\n| ---: | --- | --- | --- | --- |\n"
    for n in nodes:
        history = sorted({h["subtask"] or (h["task"] + " / S not recorded") for h in n["history"]})
        text += f'| {n["line"]} | `{n["label"]}` | {n["receiver"]} | {n["futurePackage"] or "existing closure backlog"}; {n["receivingBasis"]} | '+"; ".join(history)+" |\n"
    text += "\n## All known historical and planned T/S\n\nZero exact labels means the record supplies no exact per-node binding, not\nthat the task did no work. Consult its evidence; never manufacture an S or\nclaim the whole slice was completed. Future IDs are added here on admission.\n\n| T or S | Exact historically mentioned nodes | Current received nodes | Evidence / record boundary |\n| --- | ---: | ---: | --- |\n"
    for t in sorted(data["tasks"], key=lambda t: t["id"]):
        text += f'| {t["id"]} | {len(history_by_t[t["id"]])} | - | '+"; ".join(link(p) for p in t["evidence"])+("; S not recorded" if not t["subtasks"] else "")+" |\n"
        for s in t["subtasks"]:
            text += f'| {s["id"]} | {len(history_by_s[s["id"]])} | {sum(n["receiver"] == s["id"] for n in nodes)} | '+", ".join(s["recordKinds"])+"; "+"; ".join(link(p) for p in s["evidence"])+" |\n"
    text += "\n## Accepted ownership events\n\n| Event | From | Receiving S | Nodes | Acceptance evidence |\n| --- | --- | --- | ---: | --- |\n"
    for e in data["events"]:
        text += f'| {e["id"]} | {e["from"] or "initial ledger"} | {e["to"]} | {len(e["nodes"])} | {e["acceptedBy"]}; {link(e["evidence"])} |\n'
    text += "\n## Recorded S estimates and actual matches\n\nOnly runs with retained exact evidence appear here; older missing estimates\nare not reconstructed as historical promises. Exact scope arrays are in JSON.\n\n| S | Scope count | Incoming complete | Expected new names / count | Actual new names / count | State / evidence |\n| --- | ---: | ---: | --- | --- | --- |\n"
    for r in data["runs"]:
        expected = ", ".join("`"+n+"`" for n in r["expectedMatches"]) or "none"
        actual = ", ".join("`"+n+"`" for n in r["actualMatches"]) or "none"
        text += f'| {r["subtask"]} | {len(r["scope"])} | {r["baseline"]} | {expected} / {len(r["expectedMatches"])} | {actual} / {len(r["actualMatches"])} | {r["state"]}; {link(r["evidence"])} |\n'
    return text


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    p.add_argument("--ledger", type=Path)
    p.add_argument("--write", action="store_true", help="Regenerate Markdown after validating JSON")
    p.add_argument("--admission", type=Path)
    p.add_argument("--closure", type=Path)
    p.add_argument("--transfer", type=Path, help="Validate proposed transfer without changing ownership")
    p.add_argument("--subtask", help="Print exact received, historical and run node sets for one S")
    args = p.parse_args()
    root = args.root.resolve()
    data = read_json(args.ledger or root / "docs/states/NODE_TASK_LEDGER.json")
    context = validate(root, data)
    if args.admission:
        check_admission(root, data, context, read_json(args.admission))
    if args.closure:
        check_closure(root, data, context, read_json(args.closure))
    if args.transfer:
        event = read_json(args.transfer)
        require(event["id"] not in {e["id"] for e in data["events"]}, "Transfer event ID already exists")
        apply_event(root, event, {n: x["receiver"] for n, x in context[2].items()}, context[1], context[0])
    view = markdown(data)
    path = root / "docs/states/NODE_TASK_LEDGER.md"
    if args.write:
        path.write_text(view, encoding="utf-8")
    elif args.ledger is None:
        require(path.is_file() and path.read_text(encoding="utf-8") == view, "Ledger Markdown is stale; run --write")
    if args.subtask:
        require(args.subtask in context[1], "Unknown queried S")
        print(json.dumps({"subtask":args.subtask,
                          "received":[n["label"] for n in data["nodes"] if n["receiver"] == args.subtask],
                          "historical":[n["label"] for n in data["nodes"] if any(h["subtask"] == args.subtask for h in n["history"])],
                          "runs":[r for r in data["runs"] if r["subtask"] == args.subtask]}, indent=2))
        return
    print(json.dumps({"nodes":len(context[0]), "receivers":dict(Counter(n["receiver"] for n in data["nodes"])),
                      "tasks":len(data["tasks"]), "subtasks":len(context[1]), "orphanNodes":0,
                      "custodyNodes":sum(n["futurePackage"] is not None for n in data["nodes"])}, indent=2))


if __name__ == "__main__":
    try:
        main()
    except (ValueError, KeyError, TypeError) as exc:
        raise SystemExit("Node task ledger check failed: " + str(exc))
