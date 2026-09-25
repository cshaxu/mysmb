# M2 candidate: Audio engine

## Status

Candidate execution plan only. Owner admission assigns a numeric M2 T. The entries below become S1 through Sn only after that admission.

## ROM scope

ROM lines 15070-16368: SoundEngine, queues/priorities, Square 1/2, noise, music/channel handlers and tables.

## Existing-code disposition

Refactor audio.c around original queues and handlers; portable command output remains a sink for ROM-owned state.

## Graph contract

Called during NMI before gameplay; consumes queued sound bytes and yields portable audio command state.

## Admission S plan

1. **S1 after admission** - Map queue bytes, priority branches, channel tables and current audio functions.
2. **S2 after admission** - Translate SoundEngine and Square 1/2 effect handlers.
3. **S3 after admission** - Translate noise effects and timing/length branches.
4. **S4 after admission** - Translate music selection, headers, channel handlers and loops.
5. **S5 after admission** - Compare queue/RAM/audio-command traces for jump, coin, powerup, damage, timer, end and title/game-over.

## Acceptance

Audio queue mutation and portable command state match ROM at NMI return; platform decides no priority or duration.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
