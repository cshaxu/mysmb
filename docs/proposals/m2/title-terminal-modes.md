# M2 candidate: Title and terminal modes

## Status

M2 T15 S1 is complete in P1; S2 is active. S3-S4 remain queued behind the S1 map.

## ROM scope

ROM lines 982-1385: title menu, world selection, demo, victory, end-world and floating-number labels.

## Existing-code disposition

Audit title/mode branches spread through game.c, area.c, object/OAM helpers and smoke tests. Keep only label-owned code.

## Graph contract

Entered through the operation-mode tree; emits text/VRAM, OAM and audio requests.

## Admission S plan

1. **S1 complete (P1)** - Bind title, select/start and demo labels to current code or replacement targets; record button-edge semantics.
2. **S2 active** - Translate title bootstrap, menu, selection and demo state/data paths.
3. **S3 queued** - Translate victory, end-world and floating-number paths including text/OAM/audio output.
4. **S4 queued** - Compare title-start, demo, victory and game-over reference routes; remove displaced branches.

## Acceptance

Mode task bytes and ROM-owned text, OAM and audio outputs agree at NMI return.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.

## S2 P1: title subtree boundary

src/game/title_modes.c now owns the translated TitleScreenMode leaves: title-area preparation, title command transfer, title data binding/bootstrap, GameMenuRoutine, StartGame, and DemoEngine. game.c retains shared game-frame and later terminal-mode owners. `title_modes.h` owns the fixed title-buffer ABI used by the remaining ScreenRoutines leaf. The same source was rebuilt for x86, x64, and OpenNT DOS; x86/x64 CTest each passed 78/78.

## S2 P2: menu branches

`title_modes.c` now translates ChkSelect through ResetTitle: exact-button selection, per-press debounce, two-player icon rewrite, world-select B increment/template, demo input handoff, and reset behavior. It moves the existing ScreenRoutines call to the title owner without adding platform behavior.
## S2 P3: title frame-route evidence

Two bounded 600-sample NMI-return comparisons were produced below `build/t15-s2-p3` and are not tracked: idle title (`0:0`) and a one-frame Select press at frame 200.  The reference uses NES serial `Select=$04`; the native recorder uses decoded `Select=$20`.  In both comparisons CPU OAM backing, CPU work RAM `$0300-$07ff`, both CIRAM pages, palette, visible OAM, audio command bytes, and all seven PPU scalar bytes had zero differences.  The Select trace confirms `ChkSelect -> DrawMushroomIcon -> UpdateScreen` including the ROM's temporary `$2000=$94` transfer phase.  x86/x64 native traces are byte-identical for the idle route.  Remaining recorder differences are only 6502 temporary zero-page and stack execution state.
