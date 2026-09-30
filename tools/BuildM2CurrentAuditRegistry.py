"""Build the neutral, reviewable baseline for the M2 current-equivalence audit.

The generated registry contains inventory names, reviewed assembly line numbers,
source-order cohort ownership and control-edge identities.  It intentionally
does not contain assembly text, ROM bytes, generated C, traces or a verdict:
those are supplied by the per-cohort semantic and operational audits.
"""
import argparse
import json
import re
from pathlib import Path


INVENTORY_ROW = re.compile(r"^\|\s*(\d+)\s*\|\s*`([^`]+)`\s*\|")

# Inclusive source line ranges, in the approved source-order plan.
COHORTS = (
    ("A", 699, 1385), ("B", 1386, 1824), ("C", 1825, 3990),
    ("D", 3991, 5314), ("E", 5315, 5900), ("F", 5901, 6297),
    ("G", 6298, 6729), ("H", 6730, 7787), ("I", 7788, 9149),
    ("J", 9150, 13022), ("K", 13023, 14459), ("L", 14460, 15069),
    ("M", 15070, 15820), ("N", 15821, None),
)


def load_inventory(path):
    nodes = []
    for raw in path.read_text(encoding="utf-8").splitlines():
        match = INVENTORY_ROW.match(raw)
        if match:
            nodes.append({"label": match.group(2), "asmLine": int(match.group(1))})
    return nodes


def cohort_for(line):
    for name, start, end in COHORTS:
        if line >= start and (end is None or line <= end):
            return name
    raise ValueError("inventory label outside approved source plan: %d" % line)


def counts(items, field):
    result = {}
    for item in items:
        value = item[field]
        result[value] = result.get(value, 0) + 1
    return dict(sorted(result.items()))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--inventory", required=True, type=Path)
    parser.add_argument("--control-graph", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()

    nodes = load_inventory(args.inventory)
    if len(nodes) != 1992 or len({node["label"] for node in nodes}) != len(nodes):
        raise ValueError("inventory is not the canonical 1,992 unique-label set")
    node_lines = {node["label"]: node["asmLine"] for node in nodes}
    for node in nodes:
        node["cohort"] = cohort_for(node["asmLine"])
        node["status"] = "unclassified"
        node["currentOwner"] = None
        node["currentCounterpart"] = None
        node["semanticEvidence"] = []
        node["operationalEvidence"] = []

    graph = json.loads(args.control_graph.read_text(encoding="utf-8"))
    edges = []
    for identity, edge in enumerate(graph["edges"], 1):
        record = dict(edge)
        record["id"] = "control-%05d" % identity
        # A control edge belongs to its executable source.  Vector edges have
        # no source label and are reviewed by the target's cohort.  Return
        # records point callee -> caller, but their source instruction is the
        # caller's JSR, so the caller owns that integration edge.
        if edge["from"] == "<vector>":
            record["cohort"] = cohort_for(node_lines[edge["to"]])
        elif edge["type"] == "return":
            record["cohort"] = cohort_for(node_lines[edge["to"]])
        else:
            record["cohort"] = cohort_for(node_lines[edge["from"]])
        record["status"] = "unclassified"
        record["currentCounterpart"] = None
        record["semanticEvidence"] = []
        record["operationalEvidence"] = []
        edges.append(record)

    if len(edges) != graph["totalEdges"]:
        raise ValueError("control graph total changed while building registry")
    registry = {
        "schemaVersion": 1,
        "purpose": "M2 current node and control-edge equivalence audit",
        "nodeTotal": len(nodes),
        "controlEdgeTotal": len(edges),
        "dataEdges": {
            "status": "not-yet-enumerated",
            "rule": "Material RAM/table producer-consumer edges require source-path proof; writer-reader cartesian candidates are not audit edges."
        },
        "materialEdges": [],
        "cohorts": [
            {"id": name, "startLine": start, "endLine": end}
            for name, start, end in COHORTS
        ],
        "nodeCounts": counts(nodes, "cohort"),
        "controlEdgeCounts": counts(edges, "cohort"),
        "controlEdgeTypeCounts": counts(edges, "type"),
        "nodes": nodes,
        "controlEdges": edges,
    }
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(registry, indent=2, sort_keys=False) + "\n",
                           encoding="utf-8")
    print(json.dumps({
        "nodes": len(nodes), "nodeCohorts": registry["nodeCounts"],
        "controlEdges": len(edges), "controlEdgeCohorts": registry["controlEdgeCounts"],
        "controlEdgeTypes": registry["controlEdgeTypeCounts"],
    }, indent=2))


if __name__ == "__main__":
    main()
