# M2 candidate: Screen, text and status

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 1386-1824: screen routines, screen subtasks, status lines, game text, title drawing and parser scheduling.

## Existing-code disposition

Separate status/text/VRAM code embedded in game.c and area.c; keep frame_snapshot only as output storage.

## Graph contract

Consumes mode/area state, schedules parser work and writes VRAM-buffer/fixed-status state.

## Admission S plan

1. **S1 after admission** - Map screen-task bytes, status writers, text tables and current C writers.
2. **S2 after admission** - Translate screen task dispatch and VRAM-buffer construction in source order.
3. **S3 after admission** - Translate status and game-text branches including two-player, time-up and warp paths.
4. **S4 after admission** - Compare title, area-entry, timer/status and warp CIRAM/palette/status routes.

## Acceptance

Platforms add no HUD/text. Task bytes and affected name-table, attribute and palette bytes match reference.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
