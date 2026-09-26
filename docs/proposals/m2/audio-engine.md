# M2 candidate: Audio engine

## Status

**M2 T21 active — S1/P1 audit and S2/P1 Square2 grow-effect correction.** The source route is shared game logic; platform code remains a passive audio-command consumer.

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

## S2/P1 result

`Square2SfxHandler -> PlayGrowPowerUp/GrowItemRegs -> ContinueGrowItems` now has its original state ownership in shared `src/game/audio.c`: grow and vine initialize `$07be`, increment it every frame, use its half-value against the unchanged `$07bd` length, and clear the effect only at that equality. Other Square2 setup paths, including `PlayPowerUpGrab`, retain `$07be`; they do not globally clear it.

The focused smoke covers the first two grow frames. The build-local 600-sample W1-1 route (`Start`, `B+Right`, then `A+B+Right` for three frames) was replayed against the prior same-route original-ROM recording. CPU work RAM `$0300-$07ff`, CPU OAM backing, both CIRAM pages, palette, visible OAM, fourteen audio state bytes, and seven PPU-visible scalar bytes have zero differences. Native x86/x64 recordings are byte-identical: SHA-256 `218B086BC5878BBDCD0E21308C9727F73A7EEADC9D393F9911BAEE8C6D03EFE3`. Derived traces remain only in `build/m2-t21-s2-p1`.

Both x64 and x86 CTest suites pass 79/79. The OpenNT DOS16 MZ link passes with its existing `OLDNAMES.LIB` warning. The three P1 artifacts are `mysmb16.exe` `5E51683CD2809AFE82577EBAB6057A504584D55AC956369E6398566786B33C76`, `mysmb32.exe` `5B4C53F25842849BC99FD5EC72562BBE54C10A0152C98C6B299A9E649D0CE678`, and `mysmb64.exe` `323643BB6DB02580EE1904E95DED2C3F50BCFFACE9434C07FCCC801859E77BBB`.
## S2/P2 and S5/P1 result

`LoadEventMusic` now matches the original death-music branch: `StopSquare1Sfx` clears Square1's buffer, while `StopSquare2Sfx` changes only APU registers and retains `$00f2`. The audio smoke asserts that precise ownership rule.

A source-reachable hidden-coin route exposed the missing `SetupJumpCoin → JCoinC` producer in the blocks/items/misc owner. That producer correction is isolated into the separately admitted T22 packet; it causes the original `$01` Square2 queue to reach this audio handler. With the producer present, the 600-sample ROM route has zero differences in all 14 audio snapshot bytes, CPU OAM backing, both CIRAM pages, palette, visible OAM, and seven PPU-visible scalar fields. x86/x64 native recordings are byte-identical with SHA-256 `5B2127F8C36FB6D025DD2DBA173A5CE7BA0C83D066629D1F424BFD74F6FC3867`. One independently pre-existing work-RAM difference remains at sample 447, `$04ac/$04ae` player bounding-box X edges; it has no audio or visible-output difference and is transferred to the player/OAM bounding-box owner. Derived data stays below `build/m2-t21-s5-p1-hidden-coin`.
## Acceptance

Audio queue mutation and portable command state match ROM at NMI return; platform decides no priority or duration.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.
