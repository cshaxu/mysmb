"""Validate the neutral M2 current-equivalence node and edge audit ledger."""
import argparse
import json
from pathlib import Path


STATUSES = {"unclassified", "exact", "needs-evidence", "mismatch", "infeasible"}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def source_paths(record, identity, repository_root):
    paths = record.get("currentSourcePaths")
    require(paths is not None,
            "%s has no currentSourcePaths entry" % identity)
    require(isinstance(paths, list) and paths,
            "%s has an empty currentSourcePaths list" % identity)
    require(len(paths) == len(set(paths)),
            "%s has duplicate currentSourcePaths" % identity)
    for path in paths:
        require(isinstance(path, str) and path.startswith("src/") and
                path.endswith(".c"),
                "%s has an invalid current source path" % identity)
        require((repository_root / path).is_file(),
                "%s references a missing current source path %s" %
                (identity, path))


def audit_fields(record, identity, repository_root):
    require(record.get("status") in STATUSES,
            "%s has an unknown disposition" % identity)
    source_paths(record, identity, repository_root)
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
    repository_root = args.registry.resolve().parents[2]
    nodes = registry["nodes"]
    edges = registry["controlEdges"]
    require(registry["nodeTotal"] == 1992 == len(nodes),
            "node total must be the canonical 1,992")
    require(registry["controlEdgeTotal"] == 4342 == len(edges),
            "raw control-edge total must be the canonical 4,342")
    infeasible = [edge for edge in edges if edge["status"] == "infeasible"]
    require(registry.get("rawControlEdgeTotal") == 4342,
            "raw control-edge total must retain the source extractor count")
    require(registry.get("infeasibleControlEdgeTotal") == len(infeasible),
            "infeasible control-edge count is stale")
    require(registry.get("feasibleControlEdgeTotal") == len(edges) - len(infeasible),
            "feasible control-edge denominator is stale")
    require(set(registry.get("infeasibleControlEdgeIds", [])) ==
            {edge["id"] for edge in infeasible},
            "infeasible control-edge identities are stale")
    require(len({node["label"] for node in nodes}) == len(nodes),
            "node labels must be unique")
    require(len({edge["id"] for edge in edges}) == len(edges),
            "control-edge identities must be unique")
    for node in nodes:
        audit_fields(node, "node %s" % node["label"], repository_root)
        if node["status"] != "unclassified":
            require(node.get("currentOwner"),
                    "node %s has a disposition without a current owner" % node["label"])
    for edge in edges:
        audit_fields(edge, "control edge %s" % edge["id"], repository_root)
    material = registry.get("materialEdges", [])
    require(len({edge.get("id") for edge in material}) == len(material),
            "material-edge identities must be unique")
    for edge in material:
        for key in ("producer", "consumer", "storage", "feasiblePath"):
            require(edge.get(key), "material edge %s has no %s" %
                    (edge.get("id", "<unnamed>"), key))
        audit_fields(edge, "material edge %s" % edge["id"], repository_root)
    counts = {status: sum(node["status"] == status for node in nodes)
              for status in sorted(STATUSES)}
    edge_counts = {status: sum(edge["status"] == status for edge in edges)
                   for status in sorted(STATUSES)}
    final = registry.get("finalCertification")
    require(final is not None, "final-certificate boundary must be explicit")
    reviewed_nodes = final["reviewedNodeLabels"]
    reviewed_edges = final["reviewedControlEdgeIds"]
    node_labels = {node["label"] for node in nodes}
    feasible_ids = {edge["id"] for edge in edges
                    if edge["status"] != "infeasible"}
    require(len(set(reviewed_nodes)) == len(reviewed_nodes) and
            set(reviewed_nodes) <= node_labels,
            "final reviewed nodes must be unique known labels")
    require(len(set(reviewed_edges)) == len(reviewed_edges) and
            set(reviewed_edges) <= feasible_ids,
            "final reviewed controls must be unique feasible identities")
    require(final["nodeUniverse"] == len(nodes) and
            final["feasibleControlUniverse"] == len(feasible_ids),
            "final-review universe must agree with source registry")
    cohort_nodes = [label for cohort in final["cohortReview"]
                    for label in cohort["nodeLabels"]]
    cohort_edges = [identity for cohort in final["cohortReview"]
                    for identity in cohort["feasibleControlIds"]]
    require(len(cohort_nodes) == len(nodes) and set(cohort_nodes) == node_labels,
            "final review groups must partition all nodes exactly once")
    require(len(cohort_edges) == len(feasible_ids) and
            set(cohort_edges) == feasible_ids,
            "final review groups must partition feasible controls exactly once")
    require(final["status"] in ("incomplete", "complete"),
            "unknown final-certificate status")
    if final["status"] == "complete":
        require(set(reviewed_nodes) == node_labels and
                set(reviewed_edges) == feasible_ids and
                registry["dataEdges"]["status"] == "complete" and
                final["materialTotal"] == len(material) and
                not final["blockers"] and
                all(record["status"] in ("exact", "infeasible")
                    for record in nodes + edges + material),
                "partial evidence cannot be a complete final certificate")
    print(json.dumps({"nodes": counts, "controlEdges": edge_counts,
                      "rawControlEdges": len(edges),
                      "feasibleControlEdges": len(edges) - len(infeasible),
                      "materialEdges": len(material),
                      "materialEnumeration": registry["dataEdges"]["status"],
                      "ledgerMeaning": "Scoped evidence dispositions, not full certification",
                      "metadataValidationOnly": True,
                      "finalCertificate": final["status"],
                      "finalReviewedNodes": len(reviewed_nodes),
                      "finalReviewedControls": len(reviewed_edges)},
                     indent=2))


if __name__ == "__main__":
    main()
