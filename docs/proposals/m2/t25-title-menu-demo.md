# M2 T25: Title menu, world selection and demo

## Exact node contract

T25 is the first future source-order slice after the immutable historical T23/T24 records. It owns the 26 inventory labels from ROM lines 982–1133. Victory begins at line 1137 and belongs to T26. All labels are presently received by historical `M2 T15 S4`; S1 is an audit only and must not change ownership.

| Node | ROM lines | Existing native owner boundary | Current receiver |
| --- | --- | --- | --- |
| `TitleScreenMode` | 982 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `WSelectBufferTemplate` | 993 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `GameMenuRoutine` | 996 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `StartGame` | 1004 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `ChkSelect` | 1005 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `ChkWorldSel` | 1013 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `SelectBLogic` | 1018 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `IncWorldSel` | 1033 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `UpdateShroom` | 1039 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `NullJoypad` | 1047 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `RunDemo` | 1049 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `ResetTitle` | 1053 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `ChkContinue` | 1059 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `StartWorld1` | 1065 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `InitScores` | 1077 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `ExitMenu` | 1080 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `GoContinue` | 1081 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `MushroomIconData` | 1090 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `DrawMushroomIcon` | 1093 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `IconDataRead` | 1095 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `ExitIcon` | 1105 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `DemoActionData` | 1109 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `DemoTimingData` | 1114 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `DemoEngine` | 1119 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `DoAction` | 1129 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |
| `DemoOver` | 1133 | `title_modes.c` / `frame_root.c` title-mode path | M2 T15 S4 |

## S plan

| S | Role and receipt sequence | ROM-logic evidence | Operational evidence | Completion forecast |
| --- | --- | --- | --- | --- |
| S1 | Audit the exact 26-node call tree, tables, reads/writes and current C boundaries; no ownership transfer. | Listing call graph and source-order write map. | Ledger admission and documentation gate. | 0 |
| S2 | Accept all 26 labels from T15 S4 and migrate only the shared title/menu/demo owner. | Branch/table/call-order review against the S1 map. | Focused C tests, x86/x64, DOS16, purity, three artifacts. | 0 |
| S3 | Receive S2 output and prove ROM logic equivalence. | Controlled title, Select/world, Start and demo routes; reads/writes/tables/call order. | Cross-width trace equality. | 0 |
| S4 | Receive S3 output and complete operational verification. | Recheck source-reachable branches after any repair. | Focused tests, x86/x64, DOS16, runtime route and purity. | 0 |
| S5 | Receive S4 output and close only labels supported by both tracks. | Review evidence/dispositions label by label. | Re-run required gates and publish three artifacts. | Up to 26 |

No platform adapter may decide menu state, world selection, demo input, timing, score reset, or title transition.

## S1 source-contract audit

The original execution tree is `TitleScreenMode -> JumpEngine`: task 0
`InitializeGame`, task 1 `ScreenRoutines`, task 2 `PrimaryGameSetup`, task 3
`GameMenuRoutine`. The task-3 chain is `StartGame -> ChkContinue ->
StartWorld1 -> InitScores`; non-start input is `ChkSelect -> ChkWorldSel ->
SelectBLogic`, with `DrawMushroomIcon` or `IncWorldSel -> GoContinue`. An
expired demo timer selects `DemoEngine -> DoAction/DemoOver`, then either
`ResetTitle` or `RunDemo -> GameCoreRoutine`. All 26 labels remain within that
chain. The first Victory label is `VictoryMode` at 1137 and is excluded.

Existing shared ownership is `title_modes.c` with NMI mode dispatch in
`frame_root.c`; no platform source owns these decisions. The audit found that
current `mysmb_game_title_step` models the menu branches and demo tables, but
its demo path clears or replaces the saved input and returns without modeling
the source `RunDemo -> GameCoreRoutine` same-frame handoff. `SavedJoypad2Bits`
OR semantics also lacks a separate shared state owner. These are explicit S2
migration obligations; S1 grants no ROM-match credit.

The 26 labels transfer from historical `M2 T15 S4` to accepted `M2 T25 S2`.
S2 must preserve the stated source ordering and address both recorded gaps
before any equivalence forecast.

## S2 shared-C migration result

`mysmb_game_title_step` now ORs the two source joypad latches before the exact
Start/A+Start comparisons and returns whether its source control path reaches
`RunDemo`. `mysmb_frame_root_step` invokes the existing shared GameCore path
only for that true result; Start and ResetTitle consume the title branch. No
GameCore dispatcher was copied into the title owner, and no platform code
changed. `title_demo_smoke` proves a demo frame advances the existing entrance
subroutine from zero to seven, in addition to its title-table and terminal
checks; it also proves player-two Start follows the source comparison.

The direct x86/x64 C90 compilations passed, the focused x64 linked smoke and
both Win32 product `--self-test` invocations passed, platform purity passed,
and OpenNT produced the DOS16 MZ. The known pre-existing OpenNT C4761 and
OLDNAMES.LIB warnings remain non-T25 warnings. S2 adds no ROM-match credit and
transfers all 26 labels to S3 for independent ROM equivalence proof.

