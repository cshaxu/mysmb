# M2 T21 — boot and cold initialization

## Exact target

T21 owns exactly 7 ROM boot labels: `Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, `InitializeMemory`. Baseline is **3 / 1,992**; S1 forecasts no new completed nodes.

## S plan

1. **S1 active — node contract:** establish root call edges, RAM/OAM ownership, tables and both verification routes.
2. **S2 — shared-C migration:** translate only the admitted boot/cold-init owners.
3. **S3 — ROM logic-equivalence:** compare branches, reads/writes, initialization order and controlled cold/warm routes.
4. **S4 — operational verification:** focused tests, x86/x64, DOS16, platform purity and boot route.
5. **S5 — closure:** update `NODE_PROGRESS.md`, report every label and transfer unresolved work.

## S1/P1 source contract

| Node | ROM behavior | Current shared-C owner | S3 logic-equivalence route | S4 operational route |
| --- | --- | --- | --- | --- |
| `Start` | Initialize CPU/`$2000`, then wait for two vblanks. | `mysmb_game_reset`, `src/game/boot.c`. | Compare state after the two hardware waits and before `WBootCheck`. | Root smoke, x86/x64 build, DOS16 link. |
| `VBlank1`, `VBlank2` | Poll `$2002` until vblank; no game-RAM write. | No core busy wait. | Prove the source no-write interval and retain it as a platform-wait adaptation. | Platform timing contract; no host loop substitutes for ROM proof. |
| `WBootCheck` | Validate six score digits and `$07ff == $a5`; select cold/warm offset. | `mysmb_game_reset`. | Controlled valid/invalid score and marker cases. | `mysmb.reset-root-smoke`; x86/x64 build; DOS16 link. |
| `ColdBoot` | Call `InitializeMemory`; reset mode/seed; write sound/PPU state; hide sprites; initialize name tables; enable NMI. | `mysmb_game_reset` plus helpers in `boot.c`. | Controlled cold and valid-warm state through final NMI-enable mirror write. | `mysmb.ram-cold-start-smoke`; root smoke; three targets. |
| `EndlessLoop` | Idle after final boot write; NMI drives later execution. | No C loop; scheduling is platform plus T22 NMI owner. | Prove no source game-state write before NMI entry. | Boot-to-first-frame route per target. |
| `InitializeMemory` | Descending page clear `$07xx` through `$00xx`, preserving `$0160-$01ff`. | `mysmb_game_initialize_memory`, `boot.c`. | Boundary pages and preserved page-one window for `$fe` and `$d6` starts. | `mysmb.ram-cold-start-smoke`; x86/x64 build; DOS16 link. |

No label is complete in S1. `VBlank1`, `VBlank2`, and `EndlessLoop` require
explicit platform-adaptation evidence in both later verification tracks.

## S1 closure

S1 established the source contract for all seven labels, separated the NMI/PPU consumers to deferred T22 custody, and ran the x86/x64 operational baseline. It claims no ROM-match completion and transfers all seven labels to S2.

## S2/P1 shared-C migration record

`ColdBoot` is the only admitted owner with direct APU writes.  The source
returns from `InitializeMemory` with A=`$00`, writes it to `$4011`, then writes
`$0f` to `$4015`; `mysmb_game_reset` now records those two values in portable
shared game output (`apu_delta_counter_load`, `apu_channel_enable`) before its
existing PPU/OAM/name-table sequence.  No Windows or DOS file reads, derives,
or changes these values.  `WBootCheck` still supplies `$d6` or `$fe` exactly,
and `InitializeMemory` retains its page-one `$0160-$01ff` skip rule.

The C container constructor now clears owner-local storage and enters
`mysmb_game_reset`; it no longer duplicates a partial host-only cold-boot
sequence.  The one pre-first-frame OAM backing copy initializes the portable
container only.  Its source-timed `$4014` commit remains a T22 boundary.

This P implements the seven-node owner boundary but makes no new ROM-match
claim.  S3 must still compare every branch, write and call ordering; S4 must
still run the three target artifacts and purity checks.

P1 operational record: the focused cold-start, reset-root, frame-snapshot and
platform-purity CTests pass in both native x86 and x64 Makefile trees.  The
same shared source relinks the OpenNT DOS16 MZ, retaining the pre-existing
`OLDNAMES.LIB` linker warning.  Refreshed local artifacts are
`mysmb16.exe` `C257D5918993648BA996CCC0B8E93420AA5FEE8B35667B8C1BE711121A1DCDB1`,
`mysmb32.exe` `577E583D9F8C497ECD6F3018155ED9A3119739A1B764F3AE29F39583B5AB81F9`,
and `mysmb64.exe` `858B37C468A1FE1339BD5DD691000069E346AC7F6ED01E4DA8E5B2503E08C23B`.

## S2 closure and S3 admission

S2 closes with **0** new ROM-match nodes: all seven labels were implemented
but no source-equivalence result was claimed.  It transfers `Start`,
`VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, and
`InitializeMemory` to S3.  The conformance count remains **3 / 1,992**.

S3 receives the same seven labels, with no expected new matches and a maximum
of **3 / 1,992**.  It must compare the source sequence from `Start` through
the final `WritePPUReg1`, including the controlled warm/cold branch, and must
separately record `VBlank1`, `VBlank2`, and `EndlessLoop` as no-game-state
platform boundaries.  Its focused operational baseline remains the root,
cold-start, frame-snapshot and platform-purity tests; it cannot substitute
those tests for branch/write equivalence.

## S3/P1 source audit

| Node | Source branch/write result | S3 disposition |
| --- | --- | --- |
| `Start` | `SEI`, `CLD`, stack setup and the initial `$2000=$10` precede the two waits; they have no portable game-RAM effect. | Pending platform-boundary proof; no match claim. |
| `VBlank1`, `VBlank2` | Each is a `$2002` poll with no game-RAM write. | Pending platform timing proof; no match claim. |
| `WBootCheck` | Source reads score digits `$07dc` down through `$07d7`, then `$07ff`; an invalid digit branches directly to cold reset. | Corrected the C loop to the same descending read/branch order; controlled source route remains required. |
| `ColdBoot` | `InitializeMemory` return A writes `$4011`, then mode, validation/seed, `$4015`, `$2001`, OAM, name tables, screen-disable increment and final `WritePPUReg1`. | Corrected final `$2000` physical/mirror write to `$90`; helper bodies remain separately owned dependencies. |
| `EndlessLoop` | No game-state write after final `WritePPUReg1`; NMI owns future execution. | Pending platform scheduler boundary proof; no match claim. |
| `InitializeMemory` | Page 7 starts at caller Y; after the first page Y stays `$ff`; page-one `$60-$ff` is skipped. | Direct all-`$0000-$07ff` cold/warm sentinel regression passes; retained pending the S3 controlled route record. |

The two corrections are source-derived: no timing, collision, rendering, or
platform rule was introduced.  S3/P1 remains an audit/correction result and
does not alter the forecast of zero new ROM-match nodes.

S3/P1 operational record: the four focused CTests pass on x86 and x64; the
same source relinks the DOS16 MZ with its existing `OLDNAMES.LIB` warning.
Refreshed local artifacts are `mysmb16.exe`
`126103DC5DB509C6B22C9CA87F57214403207C6FC402C17CB4B117DF704B8F3A`,
`mysmb32.exe` `FA2A8D07697175DC1C2E259172F76B7D38CB61902EFF2105C67982C3306F830A`,
and `mysmb64.exe` `45D9B49678DF4A698E647E9DBA9ADCA2660D1F74F8B81F36736D082016E898B1`.

## S3 closure and S4 admission

S3 closes without a new ROM-match claim. `WBootCheck`, `ColdBoot`, and
`InitializeMemory` now have their source branch/read/write audit and
controlled storage regression, but `Start`, `VBlank1`, `VBlank2`, and
`EndlessLoop` show one shared remaining contract: both host adapters must
consume two no-game-state startup vblank intervals before the first game tick.
This is a platform timing boundary, not a translated game-state branch. S3
therefore transfers all seven labels to S4 rather than falsely completing the
three C-only leaves.

S4 receives **7** labels: `Start`, `VBlank1`, `VBlank2`, `WBootCheck`,
`ColdBoot`, `EndlessLoop`, and `InitializeMemory`. Baseline is **3 / 1,992**;
the expected ROM-match set is all seven labels, so its maximum is **10 /
1,992**. It must make Windows x86/x64 and DOS16 consume exactly two timing
intervals before the first shared `mysmb_game_tick`, with no mutation of
`mysmb_game` by platform code. Its ROM-equivalence route combines the S3
cold/warm storage checks with a controlled two-boundary/no-tick/first-tick
sequence. Its operational route builds and runs focused boot, DOS-root,
platform-purity, x86/x64 and OpenNT DOS16 checks, then refreshes all three
local artifacts.

The S4 stop condition is any platform access to game internals beyond the
public initialization/tick/frame contracts. A scheduler delay does not become
a game flag, a game RAM write, or a platform-specific gameplay path.

## S4/P1 platform startup boundary

The source sequence at lines 699-737 performs `Start`, waits at `VBlank1`
and `VBlank2` without game-RAM writes, then enters `WBootCheck` and
`ColdBoot`; it loops at `EndlessLoop` until later NMI work. The platform
adapters now preserve that boundary without taking ownership of any game
decision. `src/platform/startup_timing.h` declares the two-boundary constant.
The Windows QPC scheduler and DOS16 root each consume exactly two boundaries
before calling the public `mysmb_game_initialize` and the existing shared
`mysmb_game_tick`. No platform file reads or writes translated RAM, PPU, OAM,
palette, scroll, or object state.

ROM logic-equivalence evidence is complete for the source instruction/order
audit and the controlled C cold/warm storage routes: `reset-root-smoke` covers
the descending `$07dc` through `$07d7` score check and `$07ff` validation, and
`ram-cold-start-smoke` covers both `$fe`/`$d6` memory-clear origins and the
page-one preserved window. `dos16-root-smoke` proves two root invocations do
not start or present the game and the third starts exactly one shared frame;
the Windows self-test proves the identical two-count gate.

A fresh owner-ROM recorder attempt was contained below `build/m2-t21-s4`: the
existing local recorder stopped before its first NMI-return sample (exit 68)
and therefore produced no usable reference coverage. The current nxvm-source
recorder rebuild also cannot configure because its profile template path and
`core-machine-80286-protected-mode-smoke` source assertion are unsatisfied.
No raw trace is tracked and **no ROM-match completion is claimed by P1** until
that reference route is repaired or replaced.

Operational verification passed on x64 and x86: `mysmb.reset-root-smoke`,
`mysmb.ram-cold-start-smoke`, `mysmb.dos16-root-smoke`, `mysmb.platform-purity`,
and each Win32 self-test (5/5 on each width). The shared source relinked the
OpenNT DOS16 MZ; it retains existing C4761 warnings and the
`OLDNAMES.LIB` linker warning. Refreshed local artifacts are `mysmb16.exe`
`EA9B763F9AF01D7B0AA21D3AE25A6C852AF8D13AE8746A486D417ECEBD9B556D`,
`mysmb32.exe` `1D5EBDC3A743FFAE7C85EDCE51C31B7876EF1F7648BEAE7C51F5ED959AB57059`,
and `mysmb64.exe` `24C9CF38A12567A40EB3613481C7B21E808AFBE30F88D44908FA3B05016F1972`.

## S4/P2 recorder repair, closure, and S5 admission

The owner-local reference recorder was rebuilt in its ignored build tree after
its previously linked nnes static libraries were found to have a stale
`core_machine` layout. The stale binary observed the reset PC at the wrong
member offset and stopped with exit 68; no MySMB or nxvm source was changed.
The rebuilt recorder accepted the owner-supplied SMB1 ROM and produced three
bounded NMI-return samples plus aggregate PC coverage. The coverage includes
the reset entry `$8000` and the two source polling loops at `$800a` and
`$800d`; raw trace and coverage remain ignored.

This repairs the reference route, but it does not make a false equivalence
claim. The C constructor currently calls the translated reset and then writes
post-`ColdBoot` setup state that belongs to later source nodes. Therefore the
three samples cannot yet be used as an equivalent post-`ColdBoot` snapshot.
S4's two-boundary Windows/DOS scheduling, direct source audit, controlled RAM
checks, purity evidence, and all three artifacts remain valid operational
facts. Its actual ROM-match set is empty and the conformance count remains
**3 / 1,992**.

S4 closes by transferring all seven exact labels to S5. S5 is admitted with
those labels, the same incoming three completed names, an empty forecast, and
a maximum of **3 / 1,992**. Its purpose is closure reconciliation: determine
the minimal source-owned repair or exact successor transfer required to remove
the constructor's later-node writes, then record every node's final evidence
or explicit transfer. It may not upgrade a label on recorder coverage or a
native test alone.

## S5/P1 closure disposition

S5 compared the source sequence with the shared startup call graph. Both host
roots call `mysmb_game_initialize`, bind local sources, and invoke
`mysmb_game_begin_title_bootstrap` before their first shared tick. That
bootstrap performs later `InitializeGame` and area-bootstrap work, while the
source executes those leaves only through the first NMI title-mode dispatch.
The current constructor also establishes presentation backing state that
belongs to the NMI boundary. This is a source-order ownership discrepancy,
not evidence that the cold-boot writes themselves are equivalent.

No T21 label is upgraded. S5 closes with **0** actual matches and transfers
`Start`, `VBlank1`, `VBlank2`, `WBootCheck`, `ColdBoot`, `EndlessLoop`, and
`InitializeMemory` to the existing T22 NMI/PPU deferred custody. That queued
source-order package now owns the integrated first-NMI boundary: it must
separate container construction from ROM state, move later title bootstrap
work into its source-owned NMI position, and then re-admit exact node credit.
The conformance count remains **3 / 1,992**.
