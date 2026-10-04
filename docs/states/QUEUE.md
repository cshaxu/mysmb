# Queue

## To-Do

This file lists work that has not started. It is not a source-order archive,
a task ledger, or a record of completed work. Active work is recorded only in
[CURRENT.md](CURRENT.md); closed tasks remain in their proposal/history record
and in the generated [node/task ledger](NODE_TASK_LEDGER.md).

## Cross-host I/O and presentation

1. [Shared I/O contracts and operational graphic frames](../proposals/shared-io-and-presentation-switching.md) — one unnumbered T candidate with six planned S slots. Define 256x240 graphic-frame, controller, ordered-audio, and inert text-placeholder contracts under `src/io`; no console gameplay or presentation switching yet. A major acceptance condition is that the DOS16 graphical executable actually boots and plays normally in a graphics-capable DOS runtime, beyond merely linking. Owner defers remaining acceptance verification until after these I/O/presentation candidates;admission still rebinds the current source and preserves known proof limits.
2. [Shared I/O quick snapshot](../proposals/shared-io-quick-snapshot.md) — one unnumbered T candidate with five planned S slots, after the `src/io` split above. DOS16 and Win32 use P to save one `mysmb.sav` beside the executable via `mysmb.tmp`, and O to load and immediately continue. Save/load failures are silent; each attempts a best-effort append to `mysmb.log`, whose own failure is silent.
3. [Colored ASCII text-frame gameplay and graphics/console switching](../proposals/colored-ascii-text-frame-gameplay.md) — one unnumbered T candidate after quick snapshot. Replace the placeholder with a real 80x50, colored, printable-ASCII game picture and implement bidirectional DOS16 graphics/text-mode and Win32 GUI/console switching, preserving one game instance and the 256x240 graphical path.

## Deferred M2 verification

4. [Remaining current-equivalence certification](../proposals/m2/remaining-current-certification.md) — queue tail;130 owner groups/910 facets,two evidence gaps,13 route/pixel slots and four pending final packages. Retain prior scoped proofs;planned S slots and exact IDs are in the proposal/ledger. No task number or admission yet.
