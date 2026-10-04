"""Validate fixed audit accounting; never infer semantic equivalence."""
import argparse
import collections
import hashlib
import json
from pathlib import Path


FACETS = {
    'producerConsumer', 'addressAlias', 'overwrite', 'crossPhaseLifetime',
    'registerFlagStack', 'callerReturn', 'sourceBinding',
}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def identity_digest(items):
    payload = '\n'.join(sorted(items)).encode('utf-8')
    return hashlib.sha256(payload).hexdigest()


def validate(ledger, registry, root):
    require(ledger['schemaVersion'] == 1, 'unknown ledger schema')
    universe = ledger['universe']
    uses = ledger['uses']
    require(len(uses) == universe['instructionSites'] == 10691,
            'missing instruction site')
    require(len({u['id'] for u in uses}) == len(uses), 'duplicate use ID')
    require(len({u['pc'] for u in uses}) == len(uses), 'duplicate source PC')
    require(identity_digest(u['id'] + ':' + u['pc'] for u in uses) ==
            universe['instructionIdentitySha256'], 'source universe changed')
    require({u['label'] for u in uses} <=
            {n['label'] for n in registry['nodes']}, 'unknown inventory label')
    regions = dict(collections.Counter(u['memoryRegion'] for u in uses
                                      if u['memoryRegion'] != 'none'))
    require(regions == universe['memoryRegions'], 'memory universe changed')
    require(sum(regions.values()) == universe['explicitMemorySites'] == 4171,
            'memory site count changed')
    groups = ledger['groups']
    require(len({g['id'] for g in groups}) == len(groups), 'duplicate group')
    group_map = {g['id']: g for g in groups}
    node_paths = {n['label']: n['currentSourcePaths'] for n in registry['nodes']}
    source_paths = set(ledger['sourceSnapshot'])
    use_ids = {u['id'] for u in uses}
    group_counts = collections.Counter()
    group_paths = collections.defaultdict(set)
    require(identity_digest(group_map) == universe['groupIdentitySha256'],
            'obligation group universe changed')
    require(all(u['group'] in group_map for u in uses), 'unassigned use')
    for use in uses:
        group_counts[use['group']] += 1
        group_paths[use['group']].update(node_paths[use['label']])
        require(use['currentOwner'] == group_map[use['group']]['currentOwner'],
                'wrong group owner: ' + use['id'])
        require(use['localDisposition'] in ('accepted-scoped', 'needs-evidence'),
                'unknown local disposition')
        require(use['localDisposition'] != 'accepted-scoped' or
                use['localReceipt'], 'accepted site without receipt')
    for group in groups:
        require(set(group['facets']) == FACETS, 'missing integration facet')
        paths = group_paths[group['id']]
        require(set(group['currentSourcePaths']) == paths and
                paths <= source_paths,
                'missing concrete source dependency for group')
        require(group['useCount'] == group_counts[group['id']],
                'group membership count changed')
        for facet in group['facets'].values():
            require(facet['status'] in ('pending-reconciliation', 'closed'),
                    'unknown facet status')
            if facet['status'] == 'closed':
                require(all(facet.get(k) for k in
                            ('domain', 'staticEvidence', 'romEvidence')),
                        'closed facet without domain and dual evidence')
    for path, digest in ledger['sourceSnapshot'].items():
        source = root / path
        require(source.is_file(), 'missing source dependency: ' + path)
        normalized = source.read_text(encoding='utf-8').encode('utf-8')
        require(hashlib.sha256(normalized).hexdigest() == digest,
                'source dependency changed; reconcile affected proofs: ' + path)
    findings = ledger['findings']
    require(len({f['id'] for f in findings}) == len(findings), 'duplicate finding')
    for finding in findings:
        require(finding['status'] in ('open', 'closed'), 'unknown finding status')
        require(set(finding['useIds']) <= use_ids,
                'finding outside fixed universe')
        require(all(finding.get(k) for k in ('oldEvidence', 'missingCondition',
                    'gameplayImpact', 'receiver', 'exit')), 'incomplete finding')
        if finding['status'] == 'closed':
            require(finding.get('repairOrExclusionEvidence') and
                    finding.get('reAuditEvidence'), 'unsupported finding closure')
    for key, total in [('nodeTotal', 1992), ('rawControlEdgeTotal', 4342)]:
        require(registry[key] == total, 'node/control universe changed')
    require(identity_digest(n['label'] for n in registry['nodes']) ==
            universe['nodeIdentitySha256'], 'node identity universe changed')
    require(identity_digest(e['id'] + ':' + e['from'] + ':' + e['to'] + ':' +
                            e['type'] for e in registry['controlEdges']) ==
            universe['controlIdentitySha256'], 'control identity universe changed')
    routes = ledger['coverageSlots']
    require(len({r['id'] for r in routes}) == len(routes), 'duplicate coverage slot')
    plan = ledger['executionPlan']
    queued = plan.get('state') == 'queued-owner-approved-deferral'
    if queued:
        require(plan['activeReceiver'] is None and
                plan.get('historicalReceiver') == ledger['taskId'],
                'queued plan must not retain an active receiver')
        proposal = plan.get('queuedProposal', '')
        require(proposal and (root / proposal).is_file(),
                'queued plan needs an existing proposal')
        handoff = plan.get('handoff', {})
        require(handoff.get('evidence') and
                (root / handoff['evidence']).is_file(),
                'queued plan needs accepted closure evidence')
        pending = {g['id'] for g in groups
                   if any(f['status'] != 'closed' for f in g['facets'].values())}
        require(len(handoff.get('pendingGroupIds', [])) == len(pending) and
                set(handoff['pendingGroupIds']) == pending,
                'handoff omits or duplicates pending groups')
        require(handoff.get('pendingFacets') == sum(
            f['status'] != 'closed' for g in groups for f in g['facets'].values()),
            'handoff pending facet count changed')
        slots = plan.get('queuedSlots', [])
        require(slots and len({s['id'] for s in slots}) == len(slots),
                'queued slots missing or duplicated')
        assigned = [gid for s in slots for gid in s.get('groupIds', [])]
        require(len(assigned) == len(pending) and set(assigned) == pending,
                'queued slots omit or duplicate pending groups')
        assigned = [cid for s in slots for cid in s.get('coverageIds', [])]
        require(len(assigned) == len(routes) and
                set(assigned) == {c['id'] for c in routes},
                'queued slots omit or duplicate coverage')
        require(set(handoff.get('findingIds', [])) == {f['id'] for f in findings}
                and set(handoff.get('coverageIds', [])) == {c['id'] for c in routes},
                'handoff loses finding or coverage identities')
    else:
        require(plan['activeReceiver'] == ledger['taskId'] == 'M2 T70 S17',
                'wrong current plan receiver')
    order = plan['groupOrder']
    require(len(order) == len(groups) and set(order) == set(group_map),
            'plan misses or duplicates owner obligations')
    phases = {p['key']: p for p in plan['phases']}
    require(set(phases) == {'material', 'pixels', 'routes', 'snapshot'},
            'missing continuation phase')
    require(phases['material']['groupIds'] == order and
            set(phases['material']['findingIds']) == {f['id'] for f in findings},
            'current material plan misses existing obligations')
    assigned_coverage = phases['pixels']['coverageIds'] + phases['routes']['coverageIds']
    require(len(assigned_coverage) == len(routes) and
            set(assigned_coverage) == {r['id'] for r in routes},
            'coverage slot omitted or duplicated in successor plan')
    require(set(phases['snapshot']['packageKeys']) ==
            {g['key'] for g in registry['finalCertification']['gapClosure']},
            'final plan misses a certification package')
    for route in routes:
        require(route['status'] in ('pending', 'closed'), 'unknown coverage status')
        if route['status'] == 'closed':
            require(all(route.get(k) for k in ('manifest', 'terminalCheckpoint',
                        'branchContract', 'evidence')), 'unsupported route closure')
    facets = [v for g in groups for v in g['facets'].values()]
    if registry['finalCertification']['status'] == 'complete':
        require(all(u['localDisposition'] == 'accepted-scoped' for u in uses) and
                all(f['status'] == 'closed' for f in facets) and
                all(f['status'] == 'closed' for f in findings) and
                all(r['status'] == 'closed' for r in routes),
                'final certificate leaves ledger obligations open')
    return dict(metadataValidationOnly=True, instructionSites=len(uses),
                acceptedScopedSites=sum(u['localDisposition'] == 'accepted-scoped'
                                        for u in uses),
                explicitMemorySites=sum(regions.values()), groups=len(groups),
                integrationFacets=len(facets),
                closedIntegrationFacets=sum(f['status'] == 'closed' for f in facets),
                openFindings=sum(f['status'] == 'open' for f in findings),
                coverageSlots=len(routes),
                closedCoverageSlots=sum(r['status'] == 'closed' for r in routes),
                localExactNodes=registry['nodeCounts']['exact'],
                feasibleControlTotal=registry['feasibleControlEdgeTotal'],
                materialReceipts=len(registry['materialEdges']),
                materialReceiptTotalIsNotAnAuditDenominator=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--ledger', type=Path,
                        default=Path('docs/states/M2_AUDIT_LEDGER.json'))
    parser.add_argument('--registry', type=Path,
                        default=Path('docs/states/M2_CURRENT_EQUIVALENCE.json'))
    args = parser.parse_args()
    ledger = json.loads(args.ledger.read_text(encoding='utf-8'))
    registry = json.loads(args.registry.read_text(encoding='utf-8'))
    print(json.dumps(validate(ledger, registry, args.ledger.resolve().parents[2]),
                     indent=2))


if __name__ == '__main__':
    main()
