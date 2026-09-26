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
