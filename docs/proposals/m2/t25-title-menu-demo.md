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

## S3 ROM-logic equivalence audit and S4 handoff

S3 re-read the complete listing range at lines 982--1133 and compared every
branch, table byte, RAM read/write and callee boundary with the shared C
owner.  The static table values and source-mode dispatch agree for
`TitleScreenMode`, `MushroomIconData`, `DrawMushroomIcon`, `IconDataRead`,
`ExitIcon`, `DemoActionData`, `DemoTimingData`, `DemoEngine`, `DoAction`, and
`DemoOver` on the valid ROM-reachable state range. `StartGame`, `ChkSelect`,
`ChkWorldSel`, `SelectBLogic`, `NullJoypad`, `ChkContinue`, `StartWorld1`,
`InitScores`, `ExitMenu`, and `GoContinue` have their source reads/writes
identified, but remain uncredited because their enclosing menu branches still
have the gaps below. No label receives ROM-match credit in S3.

Three source-owned mismatches were found:

1. `IncWorldSel -> GoContinue -> UpdateShroom` must return with X equal to
   zero and write all six bytes of `WSelectBufferTemplate` to
   `VRAM_Buffer1-1 + 0..5`; then it writes `WorldNumber + 1` to
   `VRAM_Buffer1+3`. The C loop began at the newly selected world number.
   This affects `WSelectBufferTemplate`, `IncWorldSel`, and `UpdateShroom`.
2. `RunDemo` calls `GameCoreRoutine` and immediately tests
   `GameEngineSubroutine`; a value of six must fall through `ResetTitle` in
   the same frame. The shared C handoff reached GameCore but omitted that
   post-call test. This affects `GameMenuRoutine`, `RunDemo`, and
   `ResetTitle`.
3. `StartGame -> ChkContinue` with `DemoTimer == 0` branches to the complete
   `ResetTitle` leaf. The C shortcut only cleared `OperMode` and
   `OperMode_Task`, omitting the sprite-zero clear and `DisableScreenFlag`
   increment. This affects `StartGame`, `ChkContinue`, and `ResetTitle`.

The current owner-local recorder was rebuilt from the current two C units and
the original-ROM title/start/right route was re-run below `build/m2-t25-s3`.
Its raw 600-sample comparison is deliberately retained as a diagnostic, not
as a match claim: it diverges before the menu branch because the current
title-bootstrap trace fixture is not aligned to the ROM NMI bootstrap. S4
must repair the three enumerated source gaps first, then establish a
controlled route whose initial RAM/NMI phase is demonstrably the same. This
does not authorize a visual or platform workaround.

All 26 labels transfer unchanged to S4. S4 owns only the three listed shared
title/frame-root repairs and the corrected controlled routes; it forecasts no
completion credit. S5 remains the sole node-credit/closure gate after both
logic and operational evidence are independently present.

## S4 P1: source-gap repair

S4 repaired the three S3 findings in shared C only. `IncWorldSel` now restores
the source `GoContinue` X=0 effect before `UpdateShroom` copies all six bytes
at `$0300..$0305`; it then overwrites `$0304` with the one-based world digit.
The expired `StartGame -> ChkContinue` path now calls the single title-owned
`ResetTitle` routine, including the sprite-zero and disable-screen writes.
The frame root records the `RunDemo` return, invokes the existing shared
GameCore body only for that return, then performs the source's immediate
`GameEngineSubroutine == 6` check through the same title-owned reset routine.
No platform source changed.

`title_demo_smoke` now covers the six-byte B/world template, expired Start
reset writes, and the post-GameCore task-six reset, in addition to the prior
player-two Start and demo data checks. It passed from a current x64 link; the
same changed C units and test compile under strict C90 for x86. The x86/x64
product targets were rebuilt, OpenNT linked the DOS MZ, and platform purity
passed. OpenNT retains only its pre-existing C4761 and OLDNAMES.LIB warnings.

Refreshed local artifacts: `mysmb16.exe`
`D00A226B7B9628A65C7169FBDACB9C942FD5C2860A6404F4AE02A4E83D8E9C90`,
`mysmb32.exe`
`33942B8EC68ED08F07F22F18C1A56D149B12216A534C20BC8FF4603C0F28C6CF`,
and `mysmb64.exe`
`4EB308DD887518B87E7B7D5DEE520F8253F18CC195EE8FA1BCE316BE8E4E41B6`.

S4 remains active. Its pre-repair current-recorder title/start/right run was
diagnostic only and still has an unaligned bootstrap phase; it cannot serve as
the required controlled original-ROM route. The next S4 part must align that
fixture, rerun the repaired paths, and only then transfer the 26 labels to S5.

## S4 P2: controlled cold-start disposition

The current native recorder was run from the product bootstrap, alongside the
original-ROM recorder. Samples 0--25 agree on `OperMode`, `OperMode_Task`,
`ScreenRoutineTask`, display-disable progression, and the title setup
sequence. At every one of those samples the ROM has `DemoTimer=$18` (then
`$17` after the timer cadence), while native C has `$00`. At sample 26 native
C consequently enters `DemoEngine` (`DemoAction=1`, `DemoActionTimer=$9a`,
`GameEngineSubroutine=7`) while the ROM remains in title menu countdown.

This is the original `InitializeGame` write at lines 2674--2683:
`LDA #$18; STA DemoTimer`, not an S4 title-menu rule. The authoritative node
ledger already receives `InitializeGame` at M2 T18 S4, and the NMI recovery
plan already records the identical `$07a2=$18` handoff. S4 makes no duplicate
startup repair. Its three source-gap tests remain valid; the full-route
disposition is **blocked by the pre-existing T18 owner**, not a title-node
match. All 26 labels therefore transfer to S5 for final, per-label accounting
without credit. S5 must retain this dependency and cannot promote any label
until the T18 `InitializeGame` repair and a regenerated controlled route are
available.
