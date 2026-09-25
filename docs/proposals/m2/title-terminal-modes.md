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

src/game/title_modes.c now owns the translated TitleScreenMode leaves: title-area preparation, title command transfer, title data binding/bootstrap, GameMenuRoutine, StartGame, and DemoEngine. game.c retains shared game-frame and later terminal-mode owners. 	itle_modes.h owns the fixed title-buffer ABI used by the remaining ScreenRoutines leaf. The same source was rebuilt for x86, x64, and OpenNT DOS; x86/x64 CTest each passed 78/78.
