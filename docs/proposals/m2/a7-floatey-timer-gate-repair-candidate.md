# A7 Floatey timer-gate repair candidate

## Status

Unnumbered repair candidate produced by the active Td S9 current-equivalence
audit. It has no admitted implementation task or numeric identifier.

## Confirmed chain

The smallest shared-owner chain is `DecNumTimer -> LoadNumTiles -> AddToScore`
inside `src/game/objects.c:mysmb_objects_step_floatey_number`. Its predecessor
is `ChkNumTimer`; its non-score successor is `ChkTallEnemy`; the one-up
variant also writes lives and the square-two sound queue before `LoadNumTiles`.

## Evidence and required outcome

Original ROM `DecNumTimer` at source lines 1320–1337 executes `DEC
FloateyNum_Timer,x` before `CMP #$2b`. Therefore an initial timer of `$2c`
decrements to `$2b` and performs score-table/1-UP work during that frame; an
initial timer of `$2b` decrements to `$2a` and does not.

Current shared C checks `FloateyNum_Timer == 0x2b` before its decrement. It
therefore skips the source event for initial `$2c` and performs it for initial
`$2b`. This is a source-semantic mismatch in shared game logic, independent
of DOS or Win32 adapters.

The repair must decrement first, then make all `$2b` score and one-up choices
from that decremented value, preserving the source order of lives/sound,
ScoreUpdateData lookup, digit modifier write and AddToScore. It must not move
this timing into any platform adapter.

## Receiving audit items

Node: `DecNumTimer`.

Control edges: `control-00176` (`DecNumTimer -> ChkTallEnemy`),
`control-00177` and `control-00178` (`DecNumTimer -> LoadNumTiles`), and
`control-00179` (`LoadNumTiles -> AddToScore`).

Expected current-audit delta after a successful repair and fresh route proof:
one node and four control edges from `mismatch` to `exact`; no historical
node-accounting credit is implied by this candidate.
