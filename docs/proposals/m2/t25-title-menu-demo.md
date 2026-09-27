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
| S6 | Re-open the retained title integration after its named dependencies change; first isolate the earliest aligned-ROM divergence before any node credit. | Source-PC and write-order audit at the first divergent NMI. | Controlled x86/x64 recorder comparison and focused title tests. | 0 |
| S7 | Accept the S6 receipt and credit only the first natural idle prefix: `TitleScreenMode`, `GameMenuRoutine`, `NullJoypad`, and `RunDemo`; retain every later branch label. | Exact PC reachability, source order, latch clear and GameCore-tail review. | Focused title smoke, 600-frame output replay, x86/x64 trace equality, DOS16 build and purity. | 4 |
| S8 | Receive the remaining branch labels and credit only the next source-order `ResetTitle` leaf. | PC reachability from the GameCore return-six branch and exact four-write audit. | Focused reset smoke, controlled replay, cross-width builds, DOS16 and purity. | 1 |

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

## S5 per-node closure accounting

All 26 labels remain **unmatched, retained by M2 T25 S5**. The common missing
evidence is not an unspecified title defect: the controlled product-start
route cannot reach the ROM's title-menu countdown until T18 supplies
`InitializeGame`'s `$07a2=$18` write. The table records the exact state of
each label so a later replay can promote only what its route proves.

| Labels | S3/S4 source disposition | Required before ROM-match credit |
| --- | --- | --- |
| `TitleScreenMode`, `GameMenuRoutine`, `ChkSelect`, `ChkWorldSel`, `SelectBLogic`, `NullJoypad` | Task selector and menu branches reviewed; S4 exercised Select and B branch state locally. | Regenerated title route after T18 initialization, including neutral and Select frames. |
| `WSelectBufferTemplate`, `IncWorldSel`, `UpdateShroom`, `GoContinue` | S4 corrected the X=0 six-byte template write and source-order world write; focused regression verifies `$0300..$0305`. | Controlled world-select-enabled ROM state and matching VRAM-buffer observation. |
| `StartGame`, `ChkContinue`, `StartWorld1`, `InitScores`, `ExitMenu` | S4 corrected the expired-demo reset leaf; normal Start/A+Start writes and downstream area owner are mapped. | Start and A+Start route after aligned countdown; area-pointer dependent bytes remain their existing owner evidence. |
| `RunDemo`, `ResetTitle` | S4 corrected `GameCoreRoutine` return followed by immediate task-six reset; focused regression covers the RAM writes. | Aligned idle-to-demo route through a ROM-reachable task-six return. |
| `MushroomIconData`, `DrawMushroomIcon`, `IconDataRead`, `ExitIcon` | Source byte order and two-player overwrite reviewed; existing focused test covers both icon layouts. | Aligned Select route comparing queued bytes and committed output. |
| `DemoActionData`, `DemoTimingData`, `DemoEngine`, `DoAction`, `DemoOver` | Literal tables, action/timer order and terminal zero timing reviewed; focused regression covers first, middle and terminal actions. | Aligned idle-to-demo trace through the complete action sequence. |

No inventory state changes in S5. This is a closure-accounting checkpoint,
not a task closure: it retains the exact title labels until the recorded T18
dependency changes the route evidence.

## S5 P1: aligned title-route replay

T18 S4 has supplied the source-ordered `InitializeGame` write, so S5 reran
the controlled product bootstrap from the same original-ROM cold state.  Four
600-sample routes are retained under `build/m2-t25-s5/`: idle, a one-frame
Start at sample 40, a one-frame A+Start at sample 40, and a one-frame Select
at sample 40.  In every route, CPU work RAM `$0300-$07ff`, OAM backing, both
CIRAM pages, palette, visible OAM, audio-command state and all PPU scalars are
zero-difference. The only raw differences are CPU stack and zero-page state
outside these received title nodes.

The idle continuation was then warmed for 600 samples and recorded for a
further 600. It enters `DemoEngine` with the same action/timer sequence and
has the same zero-difference gameplay-visible output over the full observed
window. This establishes operational evidence for the normal title, Select,
Start/A+Start, `RunDemo`, `DemoEngine`, `DoAction`, and their shared output
handoffs. It does not yet traverse a world-select-enabled ROM state or reach
the terminal `DemoOver` reset; `WSelectBufferTemplate`, `IncWorldSel`,
`UpdateShroom`, `GoContinue`, and `DemoOver` remain deliberately uncredited.
No node count changes in this P: S5 will promote labels only after the
remaining source-reachable routes are captured and reviewed individually.

Current randomized-test artifacts are the shared-code products from T18 S4:
`mysmb16.exe` `F2F7FFEA7AA57078DEFAD3510EC41D02C50AD063AB9470E6E3D3ABFB8A049CF9`,
`mysmb32.exe` `5F5E0B6620420AA06AFD5D7CC83AAC6F87112C9DE2F7888B09248D86567DFF16`, and
`mysmb64.exe` `112FFAC9405C79889737B16E3EF5B3C91349EFEE5DE25D63042A6B89FFE4786F`.

## S5 P2: late-demo boundary disposition

The next 600-sample window after an 1,800-sample idle warmup remains identical
in both CIRAM pages, palette, audio-command state, and every PPU scalar. Its
first shared game-state difference is `$0456` (`Player_X_Position`) at the
window start; visible OAM first differs at sample 585, in player sprite rows.
The original labels on that route are `PlayerGfxHandler` and collaborators,
whose ledger receiver is M2 T16 S4. This is an explicit cross-slice residual,
not a T25 repair opportunity. T25 retains the title/demo labels without credit
until the complete demo terminal path can be replayed after that player-graphics
owner supplies its own evidence or repair.

## S5 P3: controlled world-selection branch and terminal boundary

`EndChkB` at ROM lines 1272--1280 is the only source writer of
`WorldSelectEnableFlag` (`$07fc`), but it belongs to the later terminal slice.
For this title-only branch proof, the owner-local ROM and native recorders now
accept one bounded `--ram-write=frame:address:value` precondition. It accepts
only CPU RAM `$0000..$07ff`, applies once at the named recorder frame, and is
not compiled into a product or platform adapter. The controlled route writes
`$07fc=$01` at frame 40 and supplies B in that same title-menu frame. Its
600-sample ROM comparison has zero differences in work RAM, OAM backing,
both CIRAM pages, palette, visible OAM, audio-command state and every PPU
scalar. This is the operational branch evidence for `ChkWorldSel`,
`SelectBLogic`, `IncWorldSel`, `GoContinue`, `UpdateShroom`, and
`WSelectBufferTemplate`.

A 3,600-frame idle warmup followed by a 600-sample terminal attempt does not
prove `DemoOver`: before the terminal action sequence, ROM and C differ in
player position and player sprite output. The first visible OAM difference is
in the `PlayerGfxHandler` route, received by M2 T16 S4. T25 neither modifies
that owner nor treats the later divergent demo timer/action values as T25
evidence. The recorders reject malformed or duplicate controlled-write
arguments; their direct C11/C90 builds pass. No node count changes in this P.

## S5 closure and S6 retained integration receipt

S5 closes at **42 / 1,992** with zero new matches. Its admission forecast was
explicitly empty, so the route evidence above cannot be retroactively counted
as a node-completion claim. All 26 title labels transfer unchanged to accepted
T25 S6. S6 is a bounded post-dependency integration receipt, not a duplicate
implementation pass: it may establish node credit only after T16 has resolved
the player/OAM route needed for the terminal demo continuation and T26 has
established the natural `EndChkBButton` producer route. Its later admission
must declare a fresh exact expected-match subset and independently rerun both
logic and operational evidence.

## S6 admission: first-divergence title integration

T26 now supplies the natural terminal producer evidence named by S5.  S6
receives the same 26 labels at **74 / 1,992**, but forecasts no completion
credit: the current full title route must be re-established before the earlier
per-label proof can be reused.  A controlled no-input comparison begins from
the shared `power_on -> reset` sequence with owner-local title sources bound.
Frames 0--25 agree in RAM `$0300..$07ff`, CIRAM, palette, OAM, audio and PPU
scalars.  Frame 26 is the first divergence, in title VRAM-buffer bytes; frame
27 is the first OAM divergence.  Neighbouring-frame comparison does not reduce
the difference, so this is a source state/write discrepancy rather than a
recorder frame-index offset.

S6 may investigate only this source slice and its registered shared
collaborators.  It must identify the original PCs and title-mode writes behind
the first difference, compare the corresponding C call order, and add focused
coverage before proposing any label credit.  The unresolved player/OAM route
remains outside this S6 repair boundary; no T16 result may be inferred from a
title trace.

## S6 P1: source-order title integration repair

The first divergent title NMI exposed two source-order omissions.  First, the
shared title bootstrap had reversed `InitializeGame` and `InitializeArea` and
had omitted the `$07b0-$07cf` `ClrSndLoop`.  The repair now executes
`InitializeMemory($6f)`, clears the sound workspace, writes `DemoTimer`, calls
`LoadAreaPointer`, then enters `InitializeArea`.  The previously combined
native pointer helper is split at the ROM boundary: `LoadAreaPointer` retains
the area selector across the smaller area clear, while `GetAreaDataAddrs`
rebuilds zero-page pointers and decodes the header afterwards.

Second, `NullJoypad -> RunDemo` must call `GameCoreRoutine` in the same frame.
The shared dispatcher had placed that tail in the mutually-exclusive outer
mode chain, so it never ran after a title menu branch.  It is now a subsequent
source-owned condition.  This restores the initial entrance setup, player
palette transfer, and title-area state without giving any platform adapter a
gameplay decision.

The focused bootstrap smoke preloads sentinels in `$074c` and
`$07b0-$07cf`; it proves the two source clears at the first title NMI.  A
fresh no-input original-ROM comparison is equal in work RAM `$0300-$07ff`,
both CIRAM pages, palette, visible OAM, audio and PPU scalars for frames
0--598.  The final recorder frame deliberately contains a Start input only to
express an otherwise idle local script and is excluded.  Win32 x86/x64 product
self-tests, the OpenNT DOS16 MZ link, and platform-purity verification pass.

S6 closes at **74 / 1,992** with zero new labels.  Its admission explicitly
forecast no matches, so the repaired whole-route evidence is retained for the
next title subtask rather than converted into retroactive node credit.  The
same 26 labels remain in their T25 receiver for an exact branch-coverage and
logic-credit admission.

## S7 admission: first title-idle prefix

S7 accepts all 26 retained labels from S6 so that no closed subtask remains a
receiver.  Its exact active scope and forecast are only the source-order idle
prefix: `TitleScreenMode`, `GameMenuRoutine`, `NullJoypad`, and `RunDemo`.
The incoming baseline is **74 / 1,992**, the expected set is the same four
labels, and the maximum result is **78 / 1,992**.  The other 22 labels remain
received by S7 without credit; later branch-specific admissions must transfer
them before any closure.

The ROM-PC evidence target is `$8231 TitleScreenMode -> $8245
GameMenuRoutine -> $82bb NullJoypad -> $82c0 RunDemo` on the natural no-input
title route.  The source review must verify the task-three `JumpEngine`
selection, the `SavedJoypad1Bits = 0` write, and the same-frame
`GameCoreRoutine` call.  Operational proof is the focused title smoke plus
the controlled 600-sample title replay, with cross-width native trace equality.
The recorder's final input-sentinel sample remains excluded from equality.

## S7 closure: first title-idle prefix

S7 completes exactly four labels: `TitleScreenMode`, `GameMenuRoutine`,
`NullJoypad`, and `RunDemo`.  The original-ROM recorder reaches their entry
PCs `$8231`, `$8245`, `$82bb`, and `$82c0` once each on the natural no-input
title route.  Source review maps the task-zero mode selection to the shared
frame root, the task-three menu body and joypad-one clear to the shared title
owner, and the same-frame `GameCoreRoutine` tail to the shared frame root.
`local_title_bootstrap_smoke` and `title_demo_smoke` pass, including the
title bootstrap clears and the RunDemo game-core handoff.

For operational proof, two independently compiled native recorders (Win32
x86 and Win64) are byte-identical for all 600 samples.  Each has zero
differences against the original-ROM NMI-return recording in CPU work RAM
`$0300-$07ff`, both CIRAM pages, palette, visible OAM, audio-command bytes and
all PPU scalar outputs for frames 0--598.  Frame 599 remains intentionally
outside that comparison because the local recorder uses it as its mandatory
input sentinel.  The shared core also links as the OpenNT DOS16 MZ target and
the platform-purity test passes.  The released artifact hashes are:
`mysmb16.exe` `97B68F6134905356CCCA9EDBDABAD441FF5CF3B772A19BA38E8FAD5C21FC5970`,
`mysmb32.exe` `0CDEC53F0E44DE1F5DAD804F68046F238D5BEFA0782FEFDA467D3D2D6796CD05`,
and `mysmb64.exe` `E9850EDA3C75107C07C855560A7CFCE5D516AEC8A31B7EE8F1000B1C2536973A`.

The remaining 22 received labels are not inferred from this route.  They
transfer to S8 for the next source-order branch admission.  S7 therefore
closes at **78 / 1,992** with no retained unfinished receiver.

## S8 admission: ResetTitle

S8 receives the 22 uncompleted labels and scopes only `ResetTitle` for this
admission.  Its incoming baseline is **78 / 1,992**; its expected set is
`ResetTitle`, so the maximum is **79 / 1,992**.  The branch begins after
`RunDemo` returns with `GameEngineSubroutine = $06`: original PC `$82c9`
writes zero to `OperMode`, `OperMode_Task` and `Sprite0HitDetectFlag`, then
increments `DisableScreenFlag`.  The shared title reset routine is its only
native owner and both the frame-root tail and title-menu callers must use it.

## S8 closure: ResetTitle

The natural no-input title demo route, warmed for 1,200 frames and then
recorded for 600, reaches original PC `$82c9` once.  The source clears
`OperMode`, `OperMode_Task` and `Sprite0HitDetectFlag`, then increments
`DisableScreenFlag`; the shared native reset routine has exactly those writes.
The x86 and x64 native records are byte-identical and each has zero differences
against the ROM in work RAM `$0300-$07ff`, CIRAM, palette, visible OAM, audio
and PPU scalars for all 600 samples.  Focused title smoke and platform purity
pass; the shared code builds as DOS16 and both Win32 products pass self-test.
Artifacts: `mysmb16.exe`
`97B68F6134905356CCCA9EDBDABAD441FF5CF3B772A19BA38E8FAD5C21FC5970`,
`mysmb32.exe` `F82B44FDB869643FAEA266792988A9E6791DB7BAB348B7B133C07D2F0163CCF1`,
and `mysmb64.exe` `68EC5D94C471BE199102A3E133A2C8D320D13866A876030D07D02E2BC467AE0F`.

`ResetTitle` alone completes.  The other 21 labels require their own exact
branch packets and transfer before S8 closure.  S8 therefore closes at
**79 / 1,992**.

## S9 admission: StartGame direct jump

S9 receives the 21 uncompleted labels from S8 and scopes only `StartGame`.
The incoming baseline is **79 / 1,992**; its expected set is `StartGame`, so
the maximum is **80 / 1,992**.  ROM `$8255` is a one-instruction `JMP
ChkContinue`; it has no writes of its own.  The static listing is therefore
the direct PC proof.  The controlled Start route must additionally show the
successor `$8258/$825a`; the ROM coverage recorder intentionally does not
record unconditional-JMP instruction PCs, so that omission is not evidence
that the jump was skipped.

The native title owner must select the same two comparisons, then immediately
enter the shared start-continuation routine without platform intervention or a
synthetic intermediate game transition.  A 200-frame original-ROM/native
replay, x86/x64 equality, focused title smoke, DOS16 build, and platform-purity
check are required.  `ChkContinue` and every other received label remain
uncredited in S9 regardless of the shared successor route.

## S9 closure: StartGame direct jump

S9 completes exactly `StartGame`, reaching **80 / 1,992**.  The original
listing at `$8255` is exactly `JMP ChkContinue`; controlled Start input reaches
that PC once and its `$8258/$825a` successor fourteen times in the 200-frame
reference capture.  The shared C comparison accepts only Start and A+Start,
then immediately calls the shared start-continuation routine.  There is no
platform-owned branch or state mutation in that route.

Both native recorders have zero differing frames against the ROM for CPU work
RAM `$0300-$07ff`, both CIRAM pages, palette, visible OAM, audio and PPU
scalars for all 200 samples; the x86 and x64 records are also identical.
`mysmb.title-demo-smoke`, `mysmb.local-title-bootstrap-smoke`, and
`mysmb.platform-purity` pass.  The DOS16 MZ links with the established C4761
and OLDNAMES warnings.  Product artifacts are `mysmb16.exe`
`97B68F6134905356CCCA9EDBDABAD441FF5CF3B772A19BA38E8FAD5C21FC5970`,
`mysmb32.exe` `3487A89FD2EAE0A1F33CF5D4A0798D685680408EB77314835D29C8352D97A3A4`,
and `mysmb64.exe` `9F06DDBD251358E928646239D3DE85962E91879F0E12481B4376482F95DDFB95`.

The 20 other received labels transfer to S10; their status is unchanged.

## S10 admission: ChkSelect branch entry

S10 receives the 20 uncompleted labels and scopes only `ChkSelect`, the next
source-order executable branch entry after `StartGame`.  Its incoming baseline
is **80 / 1,992**; expected set `ChkSelect`; maximum **81 / 1,992**.
The packet will separately exercise the non-Start, non-A+Start route through
`$8258`, then establish each successor before any later branch label is
credited.  `WSelectBufferTemplate` remains retained as data without an
inferred completion claim.

## S10 closure: ChkSelect branch entry

S10 completes exactly `ChkSelect`, reaching **81 / 1,992**. A 200-frame
no-button route enters `$8258` on every frame and follows `$825a`, `$825c`,
and `$826c` while `DemoTimer` is nonzero. ROM/x86, ROM/x64 and x86/x64 records
have zero differences in work RAM, CIRAM, palette, OAM, audio and PPU scalars.
The final post-capture Start sentinel is outside the 200 captured samples.
The 19 remaining labels transfer to S11 without status change.

## S11 admission: ChkWorldSel branch entry

S11 receives the remaining 19 labels and scopes only `ChkWorldSel`, the next
executable branch target. Baseline **81 / 1,992**; expected `ChkWorldSel`;
maximum **82 / 1,992**.

## S11 closure: ChkWorldSel zero-flag branch

S11 completes exactly `ChkWorldSel`, reaching **82 / 1,992**. With the ROM's
normal zero `WorldSelectEnableFlag`, controlled no-button title replay enters
`$826c`, takes `$826f`, and reaches `NullJoypad` `$82bb`; all 199 no-button
samples agree across ROM/x86/x64 work RAM, CIRAM, palette, OAM, audio and PPU
scalars. `SelectBLogic` remains uncredited because neither its B-enabled nor
Select entry was exercised. The 18 remaining labels transfer to S12.

## S12 admission: SelectBLogic entry

S12 scopes only `SelectBLogic`, with baseline **82 / 1,992**, expected
`SelectBLogic`, and maximum **83 / 1,992**.

## S12 closure: SelectBLogic entry

S12 completes exactly `SelectBLogic`, reaching **83 / 1,992**. Controlled Select reaches `$8276` through `$827d`; 200-frame ROM/x86/x64 output is identical. The 17 remaining labels transfer to S13.

## S13 admission: IncWorldSel branch entry

S13 scopes only `IncWorldSel`, baseline **83 / 1,992**, expected `IncWorldSel`, maximum **84 / 1,992**.

## S13 closure: IncWorldSel controlled B branch

S13 completes exactly `IncWorldSel`, reaching **84 / 1,992**. A local-only fixture writes `$07fc=1` and holds B; ROM and both native widths match for 200 frames, covering `$829c-$82a3`. The remaining 16 labels transfer to S14.

## S14 admission: UpdateShroom write loop

S14 scopes `UpdateShroom`; baseline **84 / 1,992**, expected `UpdateShroom`, maximum **85 / 1,992**.
