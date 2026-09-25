# M2 candidate: Title and terminal modes

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 982-1385: title menu, world selection, demo, victory, end-world and floating-number labels.

## Existing-code disposition

Audit title/mode branches spread through game.c, area.c, object/OAM helpers and smoke tests. Keep only label-owned code.

## Graph contract

Entered through the operation-mode tree; emits text/VRAM, OAM and audio requests.

## Admission S plan

1. **S1 after admission** - Bind title, select/start and demo labels to current code or replacement targets; record button-edge semantics.
2. **S2 after admission** - Translate title bootstrap, menu, selection and demo state/data paths.
3. **S3 after admission** - Translate victory, end-world and floating-number paths including text/OAM/audio output.
4. **S4 after admission** - Compare title-start, demo, victory and game-over reference routes; remove displaced branches.

## Acceptance

Mode task bytes and ROM-owned text, OAM and audio outputs agree at NMI return.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
