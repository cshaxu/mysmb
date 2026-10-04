# M2 Fixed-Universe Audit Ledger

This is the readable index of the [neutral audit ledger](M2_AUDIT_LEDGER.json),
linked by the [current-equivalence registry](M2_CURRENT_EQUIVALENCE.json).
[CURRENT](CURRENT.md) remains the sole active packet; the registry owns
node/control dispositions and the six final-certification packages. The
node/task ledger retains implementation responsibility. This index creates
no competing match counter or new M/T/S numbering.

## Baseline And Meaning

P146 establishes version 1 under M2 T70 S17. The owner cancels the overnight
deadline. Existing scoped proofs are retained; this is their explicit
integration accounting, not another whole-project audit round.

| Layer | Fixed inventory / current evidence | Unfinished work |
| --- | --- | --- |
| Nodes | 1992 total; 1991 accepted local contracts | CheckForEnemyGroup has a named applicability gap. Accepted local contracts are not an end-to-end certificate. |
| Controls | 4342 raw; 81 source-infeasible; 4260 of 4261 feasible locally accepted | control-01480 remains evidence-limited; raw identities are retained if feasibility changes. |
| Instruction uses | 10691 unique IDs and PCs; all have retained local receipts | Applicability and integration conditions must be reconciled by group; no local receipt is reset to zero. |
| Explicit memory sites | 4171: RAM3773, ROM250, indirect61, hardware87 | Domains, actual aliases, producers/consumers and phase handoffs must be accounted for. |
| Integration accounting | 136 retained owner groups, seven facets each: 952 fixed cells | Initial cells require reconciliation against existing receipts. These are not 952 defects or 952 new tests. |
| Material receipts | 993 individually registered relationships | Evidence detail, not the audit denominator or an exhaustive data-flow graph. |
| Route/output coverage | 13 named coverage slots | Concrete manifests/checkpoints still need completion; slots are not counts of executable test cases. |
| Final packages | Six existing packages; startup/bindings closed | material/pixels/routes/snapshot remain open. |

The fixed source-site inventory is the accountability denominator. Every
instruction belongs to one owner group, including non-memory instructions
that transport values through registers, flags, calls or the stack. Both
read and write sites are present. Grouping retains the existing owner
descriptions, including multi-file chains; it does not invent a new C owner.
The registry's currentSourcePaths supplies their concrete source mapping.
The ledger binds 186 current source/header/build dependencies by normalized
identity. It contains neutral locations, dispositions and citations, not
ROM bytes, opcodes, traces or generated game data.

## Seven Integration Facets Per Group

1. Producer/consumer: identify all relevant producers and downstream uses,
   including initialization, clears, persistent state and immutable tables.
2. Address/alias: justify effective-address sets and byte arithmetic, indirect
   pointers and index domains; retain actual original alias writes.
3. Overwrite: account for intervening writers and consumption order. A local
   allocation bound is not automatically an all-frame invariant.
4. Cross-phase lifetime: account for NMI/frame, area, entrance, death/restart,
   player transpose and mode handoffs relevant to the group's values.
5. Register/flag/stack: preserve consumed carry/zero/sign values, temporaries,
   stack effects and source control dependence; declare hardware ABI exclusions.
6. Caller/return: reconcile child inputs, side effects, return/fallthrough
   ordering and feasibility with the registered control relations.
7. Source binding: apply retained receipts only to their actual source, data,
   child dependencies, fixtures, fields and exclusions in the final version.

Each cell starts pending-reconciliation rather than presumed incorrect.
Reuse evidence when it covers the condition; do not rerun a proven chain
because its evidence was recorded under an older task. Closure names its
domain, static evidence and original/native evidence. Where one chain proves
several cells, cite it in each applicable cell and run it only once.
An inability to enumerate a writer or justify a legal domain leaves the
existing cell open; it does not spawn a new unbounded denominator.

## Findings And Coverage

Two currently localized proof gaps are indexed by exact use IDs:

| Finding | Missing condition | Possible gameplay effect, if reachable |
| --- | --- | --- |
| gap-stream-domain | Legal entrance/bubble alias to enemy stream and downstream ID3F applicability; P143 decision prefix and P145 alias behavior already agree locally | Enemy pointer/cursor or initializer divergence. Reachability is not yet proved; no confirmed new product mismatch is asserted. |
| gap-overlap-lifetime | Original area row13 writes overlap HammerEnemyOffset; reconcile producer/availability/overwrite-before-consume | Hammer may reference an unexpected enemy if the unproved handoff is reachable. Original stores must not be clamped away. |

These are localized findings, not a declaration that only two global
questions remain. Other integration conditions remain explicitly held by
the group facets, rather than hidden in an aggregate exact count.

The ten route slots cover title/input, gameplay, death/restart, pipes,
vines/clouds, warp, end-world, final completion, two-player handoff and ordered
audio. Three pixel slots cover display masks, sprite-zero/fine-X splitting
and sprite output. Each slot needs a finite manifest, terminal checkpoint,
source branch contract, retained proofs and exclusions before closure.
P126/P127 routes and P144 pixels are retained evidence; their limitations
are recorded, not silently upgraded to full-route coverage.

## Change And Exit Rules

New evidence and findings attach to existing use/group/coverage IDs. A
finding records the earlier receipt, missing condition, exact affected
identities, gameplay impact, receiving S and repair/re-audit evidence.
Do not invent another round or reset already accepted local dispositions.
Increasing test cases or material receipts does not change the denominator.
A source-universe change requires a versioned change event listing exact
added/removed identities and invalidated dependencies; it is never silent.

The finish is reached when all seven facets for every group have applicable
evidence, all findings have repair or source-backed exclusion plus re-audit,
all declared route/pixel slots pass, all six existing packages close and
the final source/data/build snapshot matches. Any confirmed implementation
diff must be repaired and re-audited before advancing. No arbitrary behavior
or reachable original logic may be excluded just to make closure pass.
DOS graphical/hardware qualification remains M3/M4; the original DOS16
compile/link and three-product requirement remain in force for code repairs.

Run `python tools/VerifyM2AuditLedger.py` and the existing registry verifier.
They reject missing/duplicate identities, universe drift, stale source
bindings and unsupported closure. Passing these checks proves accounting
consistency only, not semantic equivalence. Reports state local node/control
counts, reconciled group facets, open findings, coverage slots and final
package status separately. Full M2 certification remains incomplete.
