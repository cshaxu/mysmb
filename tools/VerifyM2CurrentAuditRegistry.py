"""Validate the neutral M2 current-equivalence node and edge audit ledger."""
import argparse
import json
from pathlib import Path


STATUSES = {"unclassified", "exact", "needs-evidence", "mismatch"}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def audit_fields(record, identity):
    require(record.get("status") in STATUSES,
            "%s has an unknown disposition" % identity)
    if record["status"] != "unclassified":
        require(record.get("currentCounterpart"),
                "%s has a disposition without a current counterpart" % identity)
        require(record.get("semanticContract"),
                "%s has a disposition without a semantic contract" % identity)
        require(record.get("semanticEvidence"),
                "%s has a disposition without semantic evidence" % identity)
    if record["status"] == "exact":
        require(record.get("operationalEvidence"),
                "%s is exact without operational evidence" % identity)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--registry", required=True, type=Path)
    args = parser.parse_args()
    registry = json.loads(args.registry.read_text(encoding="utf-8"))
    nodes = registry["nodes"]
    edges = registry["controlEdges"]
    require(registry["nodeTotal"] == 1992 == len(nodes),
            "node total must be the canonical 1,992")
    require(registry["controlEdgeTotal"] == 4342 == len(edges),
            "control-edge total must be the canonical 4,342")
    require(len({node["label"] for node in nodes}) == len(nodes),
            "node labels must be unique")
    require(len({edge["id"] for edge in edges}) == len(edges),
            "control-edge identities must be unique")
    for node in nodes:
        audit_fields(node, "node %s" % node["label"])
        if node["status"] != "unclassified":
            require(node.get("currentOwner"),
                    "node %s has a disposition without a current owner" % node["label"])
    for edge in edges:
        audit_fields(edge, "control edge %s" % edge["id"])
    material = registry.get("materialEdges", [])
    require(len({edge.get("id") for edge in material}) == len(material),
            "material-edge identities must be unique")
    for edge in material:
        for key in ("producer", "consumer", "storage", "feasiblePath"):
            require(edge.get(key), "material edge %s has no %s" %
                    (edge.get("id", "<unnamed>"), key))
        audit_fields(edge, "material edge %s" % edge["id"])
    counts = {status: sum(node["status"] == status for node in nodes)
              for status in sorted(STATUSES)}
    edge_counts = {status: sum(edge["status"] == status for edge in edges)
                   for status in sorted(STATUSES)}
    print(json.dumps({"nodes": counts, "controlEdges": edge_counts,
                      "materialEdges": len(material),
                      "materialEnumeration": registry["dataEdges"]["status"]},
                     indent=2))


if __name__ == "__main__":
    main()
