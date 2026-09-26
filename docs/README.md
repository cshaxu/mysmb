# Documentation Guide

This is the sole documentation entry point.

## Task Reading Set

Before changing work for an S, read this guide, [Current](states/CURRENT.md), [Execution Rules](rules/EXECUTION.md), and [Contributing](../CONTRIBUTING.md). Planning or admission also reads [Queue](states/QUEUE.md) and [Roadmap](design/ROADMAP.md). Code, build, or test work reads Architecture, Source Layout, Architecture Rules, and Coding Rules. Governance work reads Documentation Rules. ROM, disassembly, asset, trace, or third-party research reads the [source policy](etc/operations/policy/source-policy.md).

## Orientation Map

Read [Goals](design/GOAL.md), [Architecture](design/ARCHITECTURE.md), [Source Layout](design/CODING.md), [Product UX](design/UI.md), and [Roadmap](design/ROADMAP.md) for project orientation.

## Daily Operation

`states/CURRENT.md` is the sole active-task and technical-baseline authority. `states/QUEUE.md` contains ordered, unnumbered candidates. `states/TODO.md` contains unplanned debt. Only an approved active task receives a numeric T.

[Node-to-task ledger](states/NODE_TASK_LEDGER.md) records the receiving S for
every ROM node, historical T/S evidence, and accepted transfers. Register and
validate it at every subsequent S admission and closure.

For M2, every task publishes its exact node target at admission and reports completed, incomplete, and transferred labels at closure. ROM logic-equivalence evidence and native test/run evidence are separate required tracks; see [Execution Rules](rules/EXECUTION.md#per-task-node-contract-and-dual-verification).

## Supporting Detail

[etc/README.md](etc/README.md) indexes supporting contracts, provenance, evidence, templates, and research. It cannot define a competing current design, rule, queue, or active state.
