# M2 T61: Cohort H blocks, items and miscellaneous actors current-equivalence proof

T61 continues the approved source-order proof program immediately after closed
T60. It audits the 129 labels from `VineObjectHandler` through `ExVMove`.
Historical ROM-match accounting remains **1,992 / 1,992**. This task records
fresh current shared-C equivalence evidence only.

## Task contract

T61 closes only after each scoped label and each feasible relation owned by an
admitted chain is current-exact. Each chain performs its ROM mapping, required
shared-C repair, original-ROM/current x86/x64 comparison, focused operational
proof, platform-purity check, and shared DOS16 link. Product-source repairs
also refresh all three local executable artifacts. A feasible difference stays
in its owning S until repaired and re-audited on the same route.

The task begins at the deferred `VineHeightData -> VineObjectHandler` material
boundary from T60. It does not claim unadmitted collision, relative-position,
OAM, enemy-loop or dispatcher child semantics; those relations receive an
explicit boundary disposition in the owning chain.

## Planned source-order S chains

| S | Entry to exit | Labels | Shared C owner and route family |
| --- | --- | ---: | --- |
| S1 | `VineObjectHandler -> ExitVH` | 6 | `src/game/vine.c` plus named shared world/OAM children; vine growth, draw, erase and metatile-write routes. |
| S2 | `CannonBitmasks -> KillBB` | 14 | shared cannon/Bullet Bill game chain; scheduler, spawn, movement and retirement routes. |
| S3 | `HammerEnemyOfsData -> RunHSubs` | 10 | shared hammer game chain; spawning, speed/position, collision and draw routes. |
| S4 | `CoinBlock -> MiscLoopBack` | 12 | shared coin/misc game chain; allocation, jump-coin and descending misc-loop routes. |
| S5 | `CoinTallyOffsets -> NoZSup` | 9 | shared score/status game chain; tally, score and status-number routes. |
| S6 | `SetupPowerUp -> ExitPUp` | 10 | shared power-up game chain; initialization, emergence, collision and draw handoffs. |
| S7 | `BlockYPosAdderData -> SpawnBrickChunks` | 28 | shared player-head/block game chain; bump, metatile, item and shatter routes. |
| S8 | `BlockObjectsCore -> NextBUpd` | 8 | shared block lifetime and update chain; gravity, movement, draw and replacement routes. |
| S9 | `MoveEnemyHorizontally -> ExXMove` | 6 | shared horizontal-motion primitive; carry/page and caller-return routes. |
| S10 | `MovePlayerVertically -> ExVMove` | 26 | shared vertical/gravity primitives; player, enemy and platform routes. |

The exact 129-label task scope is the concatenation of these source-order
chains. All labels are `needs-evidence` at admission except `AddToScore`, which
is already current-exact and is retained only as S5's required in-chain
handoff. The current baseline is **690 / 1,992 exact nodes** and **1,376 /
4,324 exact feasible control relations**; T61 can reach at most 818 exact
nodes if its 128 pending labels pass both tracks.

## S1 admission - vine actor lifecycle

S1 admits the contiguous six-label chain `VineObjectHandler -> ExitVH`:
`VineObjectHandler`, `RunVSubs`, `VDrawLoop`, `KillVine`, `WrCMTile`, and
`ExitVH`. Its predecessor is T60 S8's exact setup chain. The shared owner is
`src/game/vine.c`; it calls existing shared relative/offscreen, OAM,
block-buffer and enemy-lifecycle primitives at their original boundaries.
Platform adapters remain pixel consumers and cannot add any vine rule.

**ROM-logic track.** Controlled original-ROM/current x86/x64 routes cover the
frame-bit growth gate, relative/offscreen handoff, six-sprite drawing loop,
wrapped horizontal retirement, terminal metatile write, and all six returns.
The comparison records branch predicates, RAM reads/writes, `VineHeightData`
binding, child call order and owner-boundary inputs/outputs.

**Operational track.** Run the focused vine actor route on x86/x64, compare
width records, run platform purity, and link the shared DOS16 target. A
shared-game repair refreshes `assets/mysmb16.exe`, `assets/mysmb32.exe`, and
`assets/mysmb64.exe`; an audit-only result does not.

S1 has six labels in scope and six intended current-exact labels. Historical
expected-match credit remains zero because the historic ledger is already
1,992 / 1,992. Its current maximum is **696 / 1,992 exact nodes**. Any feasible
node or edge difference remains in S1 until the same ROM and native route
passes; only then can S2 start.
