# G0 extracted-control false-relation correction candidate

## Status

Unnumbered audit-governance candidate produced by the active Td S9
current-equivalence audit. It has no admitted implementation task or numeric
identifier and authorizes no production C change.

## Confirmed discrepancy

Fifteen entries in the current extracted control graph are not executable ROM
control relations. They come from the extractor following a byte-adjacent
fall-through after an indirect `JumpEngine`, table body, or a transfer that
has no source continuation. Their IDs are:

`control-01339`, `control-01405`, `control-01408`, `control-01415`,
`control-01502`, `control-01515`, `control-01537`, `control-01552`,
`control-01632`, `control-01711`, `control-02036`, `control-03743`,
`control-03769`, `control-03784`, and `control-03868`.

They span source lines 7349–10483. Each is recorded as `mismatch` because the
registry currently treats it as a required executable control edge while the
ROM instruction semantics prove that no such control transfer exists. This is
an audit-graph defect, not evidence of a missing shared-C behavior.

## Required outcome

Repair the control-edge extractor and canonical-total evidence so indirect
jump/vector boundaries, pointer data and non-returning transfers do not
produce false executable relations. Retain a reviewed tombstone or equivalent
provenance record for each removed relation; do not hide it by relabeling a C
owner. Re-run the complete graph allocation and ensure every remaining edge
has one disposition.

## Receiving audit items

Control edges: the fifteen IDs above. No ROM node, material edge, platform
adapter or shared gameplay owner is a receiving item.
