# M2 T67: Cohort M sound commands and current-equivalence proof

Owner approved continued source-order M2 execution. T66 closed before T67.
Actual inventory M has126 pending nodes,296 pending raw controls and five
pending enumerated material rows. It includes music selection and partial
Square2/Square1 streams beyond sound effects; the inventory, not the brief
program title, defines scope. No regrouping into N or source-order bypass.
Current1716/1992 exact nodes,3649/4316 feasible controls(raw4342,infeasible26),
403/493 material partial. Maximum T67 nodes1842/1992 if all126 receive dual
proof. Historical1992/1992 separate; every admission expectedMatches empty
in the historical ledger, with named current pending promotions below.

## Bounded source-order S plan

| S | Chain, shared owner and original route | Nodes / intended current fresh | Exact labels | Owned control IDs | Material IDs |
| --- | --- | --- | --- | --- | --- |
| S1 | SoundEngine title/pause/queue/DAC and shared register-frequency entries; native audio_step/dump/play/set helpers | 22 / 22 | SoundEngine; SndOn; InPause; PTone1F; ContPau; PTone2F; PTRegC; DecPauC; SkipPIn; RunSoundSubroutines; SkipSoundSubroutines; NoIncDAC; StrWave; Dump_Squ1_Regs; PlaySqu1Sfx; SetFreq_Squ1; Dump_Freq_Regs; NoTone; Dump_Sq2_Regs; PlaySqu2Sfx; SetFreq_Squ2; SetFreq_Tri | control-03164, control-03165, control-03166, control-03167, control-03168, control-03169, control-03170, control-03171, control-03172, control-03173, control-03174, control-03175, control-03176, control-03177, control-03178, control-03179, control-03180, control-03181, control-03182, control-03183, control-03184, control-03185, control-03186, control-03187, control-03188, control-03189, control-03190, control-03191, control-03192, control-03193, control-03194, control-03195, control-03196, control-03197, control-03198, control-03199, control-03200, control-03201, control-03202, control-03203, control-03204, control-03205, control-04061, control-04062, control-04063, control-04064, control-04065, control-04066, control-04067 | none |
| S2 | Square1 effect phases/dispatcher/length/stop and swim table; actual complete Square1 handler routes | 30 / 30 | SwimStompEnvelopeData; PlayFlagpoleSlide; PlaySmallJump; PlayBigJump; JumpRegContents; ContinueSndJump; N2Prt; FPS2nd; DmpJpFPS; PlayFireballThrow; PlayBump; Fthrow; ContinueBumpThrow; DecJpFPS; Square1SfxHandler; CheckSfx1Buffer; ExS1H; PlaySwimStomp; ContinueSwimStomp; BranchToDecLength1; PlaySmackEnemy; ContinueSmackEnemy; SmSpc; SmTick; DecrementSfx1Length; StopSquare1Sfx; ExSfx1; PlayPipeDownInj; ContinuePipeDownInj; NoPDwnL | control-03206, control-03207, control-03208, control-03209, control-03210, control-03211, control-03212, control-03213, control-03214, control-03215, control-03216, control-03217, control-03218, control-03219, control-03220, control-03221, control-03222, control-03223, control-03224, control-03225, control-03226, control-03227, control-03228, control-03229, control-03230, control-03231, control-03232, control-03233, control-03234, control-03235, control-03236, control-03237, control-03238, control-03239, control-03240, control-03241, control-03242, control-03243, control-03244, control-03245, control-03246, control-03247, control-03248, control-03249, control-03250, control-03251, control-03252, control-03253, control-03254, control-03255, control-03256, control-03257, control-03258, control-03259, control-03260, control-03261, control-03262, control-03263, control-03264, control-03265, control-03266, control-03267, control-03268, control-03269, control-03270, control-03271, control-03272, control-03273, control-03274, control-03275, control-04068, control-04069, control-04070, control-04071, control-04072, control-04073, control-04074 | material-00438 |
| S3 | Square2 tables/effect phases/priority/secondary-counter/stop; actual complete Square2 handler routes | 36 / 36 | ExtraLifeFreqData; PowerUpGrabFreqData; PUp_VGrow_FreqData; PlayCoinGrab; PlayTimerTick; CGrab_TTickRegL; ContinueCGrabTTick; N2Tone; PlayBlast; ContinueBlast; SBlasJ; PlayPowerUpGrab; ContinuePowerUpGrab; LoadSqu2Regs; DecrementSfx2Length; EmptySfx2Buffer; StopSquare2Sfx; ExSfx2; Square2SfxHandler; CheckSfx2Buffer; ExS2H; Cont_CGrab_TTick; JumpToDecLength2; PlayBowserFall; BlstSJp; ContinueBowserFall; PBFRegs; EL_LRegs; PlayExtraLife; ContinueExtraLife; DivLLoop; PlayGrowPowerUp; PlayGrowVine; GrowItemRegs; ContinueGrowItems; StopGrowItems | control-03276, control-03277, control-03278, control-03279, control-03280, control-03281, control-03282, control-03283, control-03284, control-03285, control-03286, control-03287, control-03288, control-03289, control-03290, control-03291, control-03292, control-03293, control-03294, control-03295, control-03296, control-03297, control-03298, control-03299, control-03300, control-03301, control-03302, control-03303, control-03304, control-03305, control-03306, control-03307, control-03308, control-03309, control-03310, control-03311, control-03312, control-03313, control-03314, control-03315, control-03316, control-03317, control-03318, control-03319, control-03320, control-03321, control-03322, control-03323, control-03324, control-03325, control-03326, control-03327, control-03328, control-03329, control-03330, control-03331, control-03332, control-03333, control-03334, control-03335, control-03336, control-03337, control-03338, control-03339, control-03340, control-03341, control-03342, control-03343, control-04075, control-04076, control-04077 | material-00439, material-00440, material-00441 |
| S4 | Noise brick/flame/dispatcher/length/stop and table; actual complete Noise handler routes | 11 / 11 | BrickShatterFreqData; PlayBrickShatter; ContinueBrickShatter; PlayNoiseSfx; DecrementSfx3Length; ExSfx3; NoiseSfxHandler; CheckNoiseBuffer; ExNH; PlayBowserFlame; ContinueBowserFlame | control-03344, control-03345, control-03346, control-03347, control-03348, control-03349, control-03350, control-03351, control-03352, control-03353, control-03354, control-03355, control-03356, control-03357, control-03358, control-03359, control-03360 | material-00442 |
| S5 | ContinueMusic and M-owned music selection/header/Square2/Square1 stream prefixes; original live entry routes, N boundary kept explicit | 27 / 27 | ContinueMusic; MusicHandler; LoadEventMusic; NoStopSfx; LoadAreaMusic; NoStop1; GMLoopB; HandleAreaMusicLoopB; FindAreaMusicHeader; FindEventMusicHeader; LoadHeader; HandleSquare2Music; EndOfMusicData; NotTRO; MusicLoopBack; VictoryMLoopBack; Squ2LengthHandler; Squ2NoteHandler; Rest; SkipFqL1; MiscSqu2MusicTasks; NoDecEnv1; HandleSquare1Music; FetchSqu1MusicData; Squ1NoteHandler; SkipCtrlL; MiscSqu1MusicTasks | control-03361, control-03362, control-03363, control-03364, control-03365, control-03366, control-03367, control-03368, control-03369, control-03370, control-03371, control-03372, control-03373, control-03374, control-03375, control-03376, control-03377, control-03378, control-03379, control-03380, control-03381, control-03382, control-03383, control-03384, control-03385, control-03386, control-03387, control-03388, control-03389, control-03390, control-03391, control-03392, control-03393, control-03394, control-03395, control-03396, control-03397, control-03398, control-03399, control-03400, control-03401, control-03402, control-03403, control-03404, control-03405, control-03406, control-03407, control-03408, control-03409, control-03410, control-03411, control-03412, control-03413, control-03414, control-03415, control-03416, control-03417, control-03418, control-03419, control-03420, control-03421, control-03422, control-03423, control-03424, control-03425, control-03426, control-03427, control-03428, control-03429, control-03430, control-04078, control-04079, control-04080, control-04081, control-04082, control-04083, control-04084, control-04085, control-04086, control-04087, control-04088, control-04089 | none |
| S6 | Full M census, current SoundEngine cross-chain routes and integrated three-target regression | 126 / 0 | All126 above, exact prerequisite | Remaining owned census; external owners stay explicit | All five plus any admitted in-scope enumeration |

All production logic belongs to src/game/audio.c and neutral game output.
S1 owns dispatcher/register writes; S2-S4 own effect branches in source order;
S5 owns actual M music prefixes. T68 retains N nodes/data and continuation
contracts. Calls into a later effect/music owner execute unchanged original
code and real C callees for caller input/return/order observation; that does
not promote the callee, table owner or unrelated downstream nodes. If an
unproven dependency blocks an owned contract, resolve the dependency scope
explicitly before claiming exact; do not stub a child, patch instructions or
infer coverage. Every scoped mismatch is repaired and reaudited in its S.

## Receiving and participation map

| ASM line | Label | Existing maintenance receiver | T67 audit S | Incoming current |
| --- | --- | --- | --- | --- |
| 15070 | `SoundEngine` | M2 T48 S1 | S1 | needs-evidence |
| 15075 | `SndOn` | M2 T48 S1 | S1 | needs-evidence |
| 15084 | `InPause` | M2 T48 S1 | S1 | needs-evidence |
| 15099 | `PTone1F` | M2 T48 S1 | S1 | needs-evidence |
| 15101 | `ContPau` | M2 T48 S1 | S1 | needs-evidence |
| 15108 | `PTone2F` | M2 T48 S1 | S1 | needs-evidence |
| 15109 | `PTRegC` | M2 T48 S1 | S1 | needs-evidence |
| 15112 | `DecPauC` | M2 T48 S1 | S1 | needs-evidence |
| 15121 | `SkipPIn` | M2 T48 S1 | S1 | needs-evidence |
| 15125 | `RunSoundSubroutines` | M2 T48 S1 | S1 | needs-evidence |
| 15134 | `SkipSoundSubroutines` | M2 T48 S1 | S1 | needs-evidence |
| 15147 | `NoIncDAC` | M2 T48 S1 | S1 | needs-evidence |
| 15150 | `StrWave` | M2 T48 S1 | S1 | needs-evidence |
| 15155 | `Dump_Squ1_Regs` | M2 T48 S2 | S1 | needs-evidence |
| 15160 | `PlaySqu1Sfx` | M2 T48 S2 | S1 | needs-evidence |
| 15163 | `SetFreq_Squ1` | M2 T48 S2 | S1 | needs-evidence |
| 15166 | `Dump_Freq_Regs` | M2 T48 S2 | S1 | needs-evidence |
| 15174 | `NoTone` | M2 T48 S2 | S1 | needs-evidence |
| 15176 | `Dump_Sq2_Regs` | M2 T48 S2 | S1 | needs-evidence |
| 15181 | `PlaySqu2Sfx` | M2 T48 S2 | S1 | needs-evidence |
| 15184 | `SetFreq_Squ2` | M2 T48 S2 | S1 | needs-evidence |
| 15188 | `SetFreq_Tri` | M2 T48 S2 | S1 | needs-evidence |
| 15194 | `SwimStompEnvelopeData` | M2 T48 S3 | S2 | needs-evidence |
| 15198 | `PlayFlagpoleSlide` | M2 T48 S3 | S2 | needs-evidence |
| 15206 | `PlaySmallJump` | M2 T48 S3 | S2 | needs-evidence |
| 15210 | `PlayBigJump` | M2 T48 S3 | S2 | needs-evidence |
| 15213 | `JumpRegContents` | M2 T48 S3 | S2 | needs-evidence |
| 15220 | `ContinueSndJump` | M2 T48 S3 | S2 | needs-evidence |
| 15227 | `N2Prt` | M2 T48 S3 | S2 | needs-evidence |
| 15230 | `FPS2nd` | M2 T48 S3 | S2 | needs-evidence |
| 15231 | `DmpJpFPS` | M2 T48 S3 | S2 | needs-evidence |
| 15234 | `PlayFireballThrow` | M2 T48 S3 | S2 | needs-evidence |
| 15239 | `PlayBump` | M2 T48 S3 | S2 | needs-evidence |
| 15242 | `Fthrow` | M2 T48 S3 | S2 | needs-evidence |
| 15247 | `ContinueBumpThrow` | M2 T48 S3 | S2 | needs-evidence |
| 15253 | `DecJpFPS` | M2 T48 S3 | S2 | needs-evidence |
| 15256 | `Square1SfxHandler` | M2 T48 S4 | S2 | needs-evidence |
| 15276 | `CheckSfx1Buffer` | M2 T48 S4 | S2 | needs-evidence |
| 15294 | `ExS1H` | M2 T48 S4 | S2 | needs-evidence |
| 15296 | `PlaySwimStomp` | M2 T48 S4 | S2 | needs-evidence |
| 15304 | `ContinueSwimStomp` | M2 T48 S4 | S2 | needs-evidence |
| 15313 | `BranchToDecLength1` | M2 T48 S4 | S2 | needs-evidence |
| 15316 | `PlaySmackEnemy` | M2 T48 S4 | S2 | needs-evidence |
| 15325 | `ContinueSmackEnemy` | M2 T48 S4 | S2 | needs-evidence |
| 15333 | `SmSpc` | M2 T48 S4 | S2 | needs-evidence |
| 15334 | `SmTick` | M2 T48 S4 | S2 | needs-evidence |
| 15336 | `DecrementSfx1Length` | M2 T48 S4 | S2 | needs-evidence |
| 15340 | `StopSquare1Sfx` | M2 T48 S4 | S2 | needs-evidence |
| 15347 | `ExSfx1` | M2 T48 S4 | S2 | needs-evidence |
| 15349 | `PlayPipeDownInj` | M2 T48 S4 | S2 | needs-evidence |
| 15353 | `ContinuePipeDownInj` | M2 T48 S4 | S2 | needs-evidence |
| 15365 | `NoPDwnL` | M2 T48 S4 | S2 | needs-evidence |
| 15369 | `ExtraLifeFreqData` | M2 T48 S5 | S3 | needs-evidence |
| 15372 | `PowerUpGrabFreqData` | M2 T48 S5 | S3 | needs-evidence |
| 15380 | `PUp_VGrow_FreqData` | M2 T48 S5 | S3 | needs-evidence |
| 15386 | `PlayCoinGrab` | M2 T48 S5 | S3 | needs-evidence |
| 15391 | `PlayTimerTick` | M2 T48 S5 | S3 | needs-evidence |
| 15395 | `CGrab_TTickRegL` | M2 T48 S5 | S3 | needs-evidence |
| 15401 | `ContinueCGrabTTick` | M2 T48 S5 | S3 | needs-evidence |
| 15407 | `N2Tone` | M2 T48 S5 | S3 | needs-evidence |
| 15409 | `PlayBlast` | M2 T48 S5 | S3 | needs-evidence |
| 15416 | `ContinueBlast` | M2 T48 S5 | S3 | needs-evidence |
| 15422 | `SBlasJ` | M2 T48 S5 | S3 | needs-evidence |
| 15424 | `PlayPowerUpGrab` | M2 T48 S5 | S3 | needs-evidence |
| 15428 | `ContinuePowerUpGrab` | M2 T48 S5 | S3 | needs-evidence |
| 15437 | `LoadSqu2Regs` | M2 T48 S5 | S3 | needs-evidence |
| 15440 | `DecrementSfx2Length` | M2 T48 S5 | S3 | needs-evidence |
| 15444 | `EmptySfx2Buffer` | M2 T48 S5 | S3 | needs-evidence |
| 15448 | `StopSquare2Sfx` | M2 T48 S5 | S3 | needs-evidence |
| 15453 | `ExSfx2` | M2 T48 S5 | S3 | needs-evidence |
| 15455 | `Square2SfxHandler` | M2 T48 S6 | S3 | needs-evidence |
| 15478 | `CheckSfx2Buffer` | M2 T48 S6 | S3 | needs-evidence |
| 15496 | `ExS2H` | M2 T48 S6 | S3 | needs-evidence |
| 15498 | `Cont_CGrab_TTick` | M2 T48 S6 | S3 | needs-evidence |
| 15501 | `JumpToDecLength2` | M2 T49 S1 | S3 | needs-evidence |
| 15504 | `PlayBowserFall` | M2 T49 S1 | S3 | needs-evidence |
| 15509 | `BlstSJp` | M2 T49 S1 | S3 | needs-evidence |
| 15511 | `ContinueBowserFall` | M2 T49 S1 | S3 | needs-evidence |
| 15517 | `PBFRegs` | M2 T49 S1 | S3 | needs-evidence |
| 15518 | `EL_LRegs` | M2 T49 S1 | S3 | needs-evidence |
| 15520 | `PlayExtraLife` | M2 T49 S1 | S3 | needs-evidence |
| 15524 | `ContinueExtraLife` | M2 T49 S1 | S3 | needs-evidence |
| 15527 | `DivLLoop` | M2 T49 S1 | S3 | needs-evidence |
| 15537 | `PlayGrowPowerUp` | M2 T49 S1 | S3 | needs-evidence |
| 15541 | `PlayGrowVine` | M2 T49 S1 | S3 | needs-evidence |
| 15544 | `GrowItemRegs` | M2 T49 S1 | S3 | needs-evidence |
| 15551 | `ContinueGrowItems` | M2 T49 S1 | S3 | needs-evidence |
| 15564 | `StopGrowItems` | M2 T49 S1 | S3 | needs-evidence |
| 15569 | `BrickShatterFreqData` | M2 T49 S2 | S4 | needs-evidence |
| 15573 | `PlayBrickShatter` | M2 T49 S2 | S4 | needs-evidence |
| 15577 | `ContinueBrickShatter` | M2 T49 S2 | S4 | needs-evidence |
| 15585 | `PlayNoiseSfx` | M2 T49 S2 | S4 | needs-evidence |
| 15591 | `DecrementSfx3Length` | M2 T49 S2 | S4 | needs-evidence |
| 15598 | `ExSfx3` | M2 T49 S2 | S4 | needs-evidence |
| 15600 | `NoiseSfxHandler` | M2 T49 S2 | S4 | needs-evidence |
| 15609 | `CheckNoiseBuffer` | M2 T49 S2 | S4 | needs-evidence |
| 15616 | `ExNH` | M2 T49 S2 | S4 | needs-evidence |
| 15618 | `PlayBowserFlame` | M2 T49 S2 | S4 | needs-evidence |
| 15622 | `ContinueBowserFlame` | M2 T49 S2 | S4 | needs-evidence |
| 15632 | `ContinueMusic` | M2 T49 S2 | S5 | needs-evidence |
| 15635 | `MusicHandler` | M2 T49 S3 | S5 | needs-evidence |
| 15645 | `LoadEventMusic` | M2 T49 S3 | S5 | needs-evidence |
| 15651 | `NoStopSfx` | M2 T49 S3 | S5 | needs-evidence |
| 15662 | `LoadAreaMusic` | M2 T49 S3 | S5 | needs-evidence |
| 15666 | `NoStop1` | M2 T49 S3 | S5 | needs-evidence |
| 15667 | `GMLoopB` | M2 T49 S3 | S5 | needs-evidence |
| 15669 | `HandleAreaMusicLoopB` | M2 T49 S3 | S5 | needs-evidence |
| 15682 | `FindAreaMusicHeader` | M2 T49 S3 | S5 | needs-evidence |
| 15686 | `FindEventMusicHeader` | M2 T49 S3 | S5 | needs-evidence |
| 15691 | `LoadHeader` | M2 T49 S3 | S5 | needs-evidence |
| 15720 | `HandleSquare2Music` | M2 T49 S4 | S5 | needs-evidence |
| 15730 | `EndOfMusicData` | M2 T49 S4 | S5 | needs-evidence |
| 15736 | `NotTRO` | M2 T49 S4 | S5 | needs-evidence |
| 15750 | `MusicLoopBack` | M2 T49 S4 | S5 | needs-evidence |
| 15753 | `VictoryMLoopBack` | M2 T49 S4 | S5 | needs-evidence |
| 15756 | `Squ2LengthHandler` | M2 T49 S4 | S5 | needs-evidence |
| 15763 | `Squ2NoteHandler` | M2 T49 S4 | S5 | needs-evidence |
| 15769 | `Rest` | M2 T49 S4 | S5 | needs-evidence |
| 15771 | `SkipFqL1` | M2 T49 S4 | S5 | needs-evidence |
| 15774 | `MiscSqu2MusicTasks` | M2 T49 S4 | S5 | needs-evidence |
| 15783 | `NoDecEnv1` | M2 T49 S4 | S5 | needs-evidence |
| 15788 | `HandleSquare1Music` | M2 T49 S5 | S5 | needs-evidence |
| 15794 | `FetchSqu1MusicData` | M2 T49 S5 | S5 | needs-evidence |
| 15806 | `Squ1NoteHandler` | M2 T49 S5 | S5 | needs-evidence |
| 15816 | `SkipCtrlL` | M2 T49 S5 | S5 | needs-evidence |
| 15819 | `MiscSqu1MusicTasks` | M2 T49 S5 | S5 | needs-evidence |

Audit participation preserves existing maintenance custody. No transfers.
Per-node manual source evidence covers predicates, RAM reads/writes, byte
wrapping, table addresses/indexes, call/return/tail and producer/consumer
edges. A source visit alone never proves equality. Every feasible edge needs
its actual current counterpart and runtime route; impossible fallthroughs
require instruction proof and remain in raw counts.

## S1 admission and dual proof contract

Scope22 pending labels: SoundEngine; SndOn; InPause; PTone1F; ContPau; PTone2F; PTRegC; DecPauC; SkipPIn; RunSoundSubroutines; SkipSoundSubroutines; NoIncDAC; StrWave; Dump_Squ1_Regs; PlaySqu1Sfx; SetFreq_Squ1; Dump_Freq_Regs; NoTone; Dump_Sq2_Regs; PlaySqu2Sfx; SetFreq_Squ2; SetFreq_Tri.
Intended current exact22, maximum1738/1992. Historical baseline/maximum1992,
incomingComplete retained, historical actual/expectedMatches empty. Source
entry SoundEngine through SetFreq_Tri before SwimStompEnvelopeData; shared
owner audio.c with public audio.h helper ABI. No platform/audio synthesis
changes or product presentation rewrite.

ROM track: Unchanged original SoundEngine F2D0 entry/real RTS controlled title, pause, unpause, empty normal dispatch and all-byte DAC states; original F381-F3B0 register/frequency helper entries. Compare1841 non-stack RAM bytes,24 final APU bytes and every ordered APU write; real calls/returns/branches and local frequency table reads, x86/x64. No downstream music/effect node credit.
Retain RAM scratch and0109-0139 aliases; exclude only actual CPU stack0100-
0108/013A-01FF and transient registers unused by native ABI. Compare required
returned A where helper ABI exposes it. Capture actual memory-store instruction
addresses and values for APU2000-independent4000-4017 writes before execution;
compare ordered stream as well as final registers, including repeated writes.
No final-register-only acceptance. Helpers use owner-local original frequency
data without copying it into tracked fixtures; N frequency table credit deferred.
Normal dispatcher route uses empty SFX/music with actual callees and records
their order/returns; no claim of full music/effect proof. Title must preserve
queues/DAC; pause skips normal children; queue clearing precedes old-DAC write.

Operational track: focused audio/local-death/music-header/square2/noise smoke
and platform purity on x86/x64; current minimal checker builds, original
OpenNT DOS16 link. Product-code repair refreshes three user-authorized assets
EXEs in same P; pure evidence retains T66 S2 products including tested audio,
title/focus pause. Full integrated native regression at T closure. Similar-issue
sweep covers queue priority, old-versus-new DAC, pause start/termination,
frequency zero/wrap and register-write ordering across all admitted helpers.

Owner-local original SMB1 ROM and reviewed SMBDIS are nonredistributable
research inputs only; unchanged original execution via read-only reference
driver, not a production emulator. Raw/scripts/logs/probes stay ignored under
build/m2-t67-s1, budget128MiB raw,1024 roots per batch,120 seconds per process,
524288 CPU instructions per root. Coordinator deletes raw after comparison.
Neutral metadata alone retained. S1 remains active on any scoped difference or
missing branch/edge evidence. No S2 admission before S1 dual proof/closure.

## S1 P2 closure - current source audit and original ordered commands

Completed22 expected labels by exact name: SoundEngine; SndOn; InPause; PTone1F; ContPau; PTone2F; PTRegC; DecPauC; SkipPIn; RunSoundSubroutines; SkipSoundSubroutines; NoIncDAC; StrWave; Dump_Squ1_Regs; PlaySqu1Sfx; SetFreq_Squ1; Dump_Freq_Regs; NoTone; Dump_Sq2_Regs; PlaySqu2Sfx; SetFreq_Squ2; SetFreq_Tri.
No deferred scoped labels, no custody transfers, no product-code changes.
Current1716->1738/1992 nodes,3649->3694 exact feasible controls; four proven
impossible fallthroughs change feasible denominator4316->4312 (raw4342,
infeasible30). Material403/493 partial unchanged, historical1992/1992 separate.
T67 remains open with104 pending nodes; S2 next unadmitted.

The S control allocation is corrected to caller ownership for return relations.
This preserves all296 M raw IDs exactly once: S1 owns49 (45 exact/4 infeasible),
later effect/music returns belong to their actual consuming S2-S5. It prevents
credit for unobserved later calls. No relation deleted or moved out of M.

| Inventory label | Current shared C counterpart | Manual source/RAM/control contract |
| --- | --- | --- |
| `SoundEngine` | `mysmb_audio_step` | Title OperMode=0 writes only master disable, returns without clearing queues or touching DAC; non-title enters normal/pause control. |
| `SndOn` | `mysmb_audio_step` | Ordered4017=FF then4015=0F; PauseMode!=0 wins; otherwise PauseQueue==1 enters pause, other queues enter normal dispatch. |
| `InPause` | `mysmb_audio_step` | Existing pause buffer continues; empty buffer/empty queue skips; nonzero queue copies both flags, disables, clears three effect buffers, enables, length2A. |
| `PTone1F` | `mysmb_audio_pause_tone` | Initial/repeated first tone44 uses X84/Y7F via actual PlaySqu1Sfx; LDA44 forces BNE taken. |
| `ContPau` | `mysmb_audio_step` | Length24/18 chooses64,1E chooses44; all other byte lengths skip tone then decrement modulo256. |
| `PTone2F` | `mysmb_audio_pause_tone` | Second tone64 reaches same ordered controls/frequency path. |
| `PTRegC` | `mysmb_audio_pause_tone -> mysmb_audio_play_squ1_sfx` | Calls actual square-one helper with tone A,X84,Y7F before decrement. |
| `DecPauC` | `mysmb_audio_step` | Decrement modulo256; zero disables; saved buffer2 clears pause flag, other buffers retain it; pause buffer clears. |
| `SkipPIn` | `mysmb_audio_step` | Zero clears pause buffer, unconditional BEQ skip; never dispatches normal children in this frame. |
| `RunSoundSubroutines` | `mysmb_audio_step` | Real Square1,Square2,Noise,Music calls in original order, then clear FB/FC; empty children tested, no child node promotion. |
| `SkipSoundSubroutines` | `mysmb_audio_step` | Clear FF/FE/FD/FA, capture old7C0, inspect F4&3; update counter before storing original old value to4011. |
| `NoIncDAC` | `mysmb_audio_step` | Old DAC zero remains zero; otherwise decrement; active music at old>=30 increments then decrements netzero. |
| `StrWave` | `mysmb_audio_step` | Write old DAC, never post-update counter, as final command. |
| `Dump_Squ1_Regs` | `mysmb_audio_dump_squ1_regs` | Write Y to4001 then X to4000, retaining same-value writes. |
| `PlaySqu1Sfx` | `mysmb_audio_play_squ1_sfx` | Actual dump then square-one frequency, return frequency A. |
| `SetFreq_Squ1` | `mysmb_audio_set_freq_squ1` | Frequency writer X offset0. |
| `Dump_Freq_Regs` | `mysmb_audio_dump_freq_regs` | Y=A; low CPU FF01+Y wrapped16 first; zero returns A0 without writes; otherwise low to4002+X then (FF00+Y|08) to4003+X, returned high A. |
| `NoTone` | `mysmb_audio_dump_freq_regs zero return / native no-op at direct RTS` | Zero-low path returns without command; direct original RTS does not mutate RAM/APU/A. |
| `Dump_Sq2_Regs` | `mysmb_audio_dump_sq2_regs` | Write X to4004 then Y to4005, preserving order difference from Square1. |
| `PlaySqu2Sfx` | `mysmb_audio_play_sq2_sfx` | Actual dump then square-two frequency, return frequency A. |
| `SetFreq_Squ2` | `mysmb_audio_set_freq_sq2` | X offset4, original nonzero LDX makes BNE unconditional. |
| `SetFreq_Tri` | `mysmb_audio_set_freq_tri` | X offset8, original nonzero LDX makes BNE unconditional. |

Fourteen controlled route modes ran15,360 total original roots per width:
title2048; pause continuation2048; pause start2048; silent pause skip2048;
empty normal dispatch256; nine original helper entries768 each. Every helper
varies all256 A values, legal X offsets0/4/8 and a full Y permutation; CPU
FF01+FF wraps to0000 and zero-low NoTone are included. Paused DAC paths cover
all old byte values and F4 low-two-bit classes; pause buffers1/2, lengths0/1/
18/1E/24/2A, unsigned wrap and terminal branches observed. Output fields:
1841 RAM bytes (including0109-0139),24 APU registers, ordered command count,
each index/value and native mapped returned A. True CPU stack0100-0108 and
013A-01FF, unmapped transient registers excluded. No RAM scratch exclusions.

Every scoped feasible control has a recorded actual source-to-next transition;
calls use their real unchanged callees and RTS continuations. For normal
empty child routes, full observed caller state and write order agree, but
unexercised active effect/music nodes remain pending for their own S. No
dependency table promotion. Original memory-store observation records every
APU write at4000-4017 before actual CPU execution; repeated same-value writes
remain distinct. A negative control swapped two commands while retaining
identical final RAM/APU: both native checkers reject it, showing final register
equality alone cannot pass this contract. No fixture byte committed.

The four impossible IDs are03172,03184,03203,03205: LDA44/BNE, LDA0/STA/BEQ,
LDX4/BNE and LDX8/BNE respectively. Known Z flags prove impossibility, not
absence of coverage. Raw IDs and proofs retained in registry.

Operational checker builds pass both widths, focused7/7 tests each including
platform purity and Win32 death audio; original OpenNT DOS16 link passes with
existing OLDNAMES.LIB warning. No interactive DOS claim. Three T66 S2 EXEs
retained byte-identical; owner-tested audio/title/focus-pause remain included:

- `mysmb16.exe`: 260839 bytes, SHA256 `1f99e8e864fcd5da449f3a643eab4f82e550b5b2229e71e167dd77ac96025fa0`.
- `mysmb32.exe`: 373854 bytes, SHA256 `efb2534dc2bb7074afb4c79db301431ef47beb18d09cd99c7f73a3ee631bed8b`.
- `mysmb64.exe`: 380886 bytes, SHA256 `87c198fc900fe0a4b744dd70459117c19d711ecf67957ebf7894374c6f0fdc84`.

Similar-issue sweep of admitted SoundEngine/register helpers found no current
product discrepancy: title early return, pause priority/start/repeat/end, queue
clear order, old DAC update/store, zero frequency/16-bit wrap and opposite
Square1/2 register-write orders match source. Active effect priority and music
branches remain S2-S5; no global all-audio claim. Neutral local evidence:
build/m2-t67-s1 route-summary.json, coverage-summary.json, mode logs, negative-
summary.json, focused-x86/x64.log and dos16-link.log. Raw cleaned; probes
removed after proof. Ledger/progress/registry/documentation gates required.

## S2 admission - Square1 complete effect chain

Scope30 pending nodes, intended current fresh30, maximum1768/1992:
SwimStompEnvelopeData; PlayFlagpoleSlide; PlaySmallJump; PlayBigJump; JumpRegContents; ContinueSndJump; N2Prt; FPS2nd; DmpJpFPS; PlayFireballThrow; PlayBump; Fthrow; ContinueBumpThrow; DecJpFPS; Square1SfxHandler; CheckSfx1Buffer; ExS1H; PlaySwimStomp; ContinueSwimStomp; BranchToDecLength1; PlaySmackEnemy; ContinueSmackEnemy; SmSpc; SmTick; DecrementSfx1Length; StopSquare1Sfx; ExSfx1; PlayPipeDownInj; ContinuePipeDownInj; NoPDwnL. Scope and intended current set are identical, each
needs-evidence. Current1738/1992 nodes,3694/4312 feasible controls(raw4342,
infeasible30),403/493 material partial. Historical1992/1992 separate with
expectedMatches empty. Existing receiving map retained; no maintenance transfer.

S2 consumes accepted S1 register/frequency writers. Shared owner audio.c:
step_square1 priority/queue shifts, play/continue jump/flagpole/throw helpers,
length/stop paths and owner-local F3B0+length envelope reader. Source entry
SwimStompEnvelopeData through NoPDwnL before Square2 tables; control scope
is source-owned non-return edges and caller-owned returns as corrected in S1.
Material00438 requires actual remaining-length table read before envelope
write/decrement, including all14 valid table bytes; arbitrary byte lengths
are CPU-address semantics, not fabricated extra table membership.

ROM track: Unchanged original F2D0 SoundEngine -> actual Square1SfxHandler -> real RTS. Start matrix4096 inputs all256 queue bytes/16 initial profiles; continuation65536 inputs all256 buffer bytes by all256 lengths. Other channels/music inactive real callees; full1841 RAM,24 APU and ordered command sequence compare x86/x64, actual scoped transitions and SwimStompEnvelopeData reads. Static source15194-15365; no active Square2/noise/music credit.
The probe executes complete actual SoundEngine unchanged, with same controlled
initial RAM passed to native public audio_step. No test-only entry into private
Square1 helper, mocked children or patched ROM. Later inactive children return
normally and are not promoted. Confirm priority bit7 then bits0..6, unshifted
buffer save/live queue shifts, starts falling into continuation exactly once,
jump25/20 tones, bump6, swim6, smack8, pipe bit gate, decrement0->FF and1->0,
stop4015=0E then0F. Compare1841 RAM including0109-0139, final APU24 bytes,
all ordered write indices/values; exclude only true CPU stack/unmapped transient
registers. Actual call/return/fallthrough recording and source impossibility
proof required for every scoped edge. No absence-only infeasible classification.

Operational track: focused audio/music/death/channel/purity tests both widths,
minimal native checker builds and original OpenNT DOS16 link. Product-code
repair publishes all3 owner-authorized EXEs in same P; audit/test-only retains
byte-verified existing3 builds. Similar-issue sweep includes start-vs-continue
double commands, queue precedence, terminal mute and byte-index/wrap behavior.
Any feasible diff remains in S2 until repaired and reaudit clean; S3 unadmitted.

Owner-local original ROM/reviewed ASM are nonredistributable research inputs;
all probes/raw/scripts/logs under ignored build/m2-t67-s2,128MiB raw budget,
1024 roots/batch,120seconds/process,524288 instructions/root. Coordinator deletes
raw after comparison. No third-party code import or platform game logic.

## S2 P2 closure - Square1 source chain and full ordered output

Completed all30 expected labels by exact name: SwimStompEnvelopeData; PlayFlagpoleSlide; PlaySmallJump; PlayBigJump; JumpRegContents; ContinueSndJump; N2Prt; FPS2nd; DmpJpFPS; PlayFireballThrow; PlayBump; Fthrow; ContinueBumpThrow; DecJpFPS; Square1SfxHandler; CheckSfx1Buffer; ExS1H; PlaySwimStomp; ContinueSwimStomp; BranchToDecLength1; PlaySmackEnemy; ContinueSmackEnemy; SmSpc; SmTick; DecrementSfx1Length; StopSquare1Sfx; ExSfx1; PlayPipeDownInj; ContinuePipeDownInj; NoPDwnL.
No deferred owned nodes/feasible relations, no transfers, no product-code diff.
Owned77 raw controls:66 exact feasible and11 source-infeasible retained raw.
Material00438 exact. Current1738->1768/1992 nodes,3694->3760 feasible controls;
denominator4312->4301 solely from instruction/path impossibility proofs,
raw4342/infeasible41. Material403->404/493, enumeration partial. Historical
1992/1992 separate; historical actualMatches empty. T67 remains open with74
pending nodes; S3 next unadmitted, no later effect/music node promotion.

| Inventory label | Shared counterpart | Manual source/state/control contract |
| --- | --- | --- |
| `SwimStompEnvelopeData` | `mysmb_audio_swim_stomp_envelope` | Owner-local CPU F3B0+remaining length, fourteen actual table entries at lengths1..14; byte length0/15..255 keeps original neighboring CPU-byte semantics. |
| `PlayFlagpoleSlide` | `mysmb_audio_square1_play_flagpole` | Length40; SetFreq_Squ1(62) before control pair X99/YBC; then decrement exactly once in step_square1. |
| `PlaySmallJump` | `mysmb_audio_square1_play_jump small!=0` | A26, unconditional branch to common jump control load. |
| `PlayBigJump` | `mysmb_audio_square1_play_jump small==0` | A18, falls into common jump control load. |
| `JumpRegContents` | `mysmb_audio_square1_play_jump` | Real PlaySqu1Sfx X82/YA7, then length28 before same-frame continuation/decrement. |
| `ContinueSndJump` | `mysmb_audio_square1_continue_jump` | Length25 emits X5F/YF6; otherwise length20 emits X48/YBC; other bytes emit nothing before decrement. |
| `N2Prt` | `mysmb_audio_square1_continue_jump` | Second comparison length20; length25 already emitted second-phase controls. |
| `FPS2nd` | `mysmb_audio_square1_play_flagpole / continue_jump` | YBC shared between flagpole X99 and jump-third X48. |
| `DmpJpFPS` | `mysmb_audio_dump_squ1_regs called by Square1 phases` | Actual ordered Y then X stores, flag-preserving original helper; nonzero Y constants make BNE to decrement. |
| `PlayFireballThrow` | `mysmb_audio_square1_play_throw fireball!=0` | Length05/Y99; same common fixed frequency0C/controlX9E. |
| `PlayBump` | `mysmb_audio_square1_play_throw fireball==0` | Length0A/Y93; same common fixed frequency0C/controlX9E. |
| `Fthrow` | `mysmb_audio_square1_play_throw` | Save selected length before actual PlaySqu1Sfx(0C,9E,selectedY). |
| `ContinueBumpThrow` | `mysmb_audio_square1_continue_throw` | Only length06 writes4001=BB, then decrement once. |
| `DecJpFPS` | `mysmb_audio_step_square1 shared decrement after jump/throw` | CMP6!=0 or LDA BB guarantees nonzero Z on throw; jump phase comparators/nonzero control loads also guarantee branch to decrement. |
| `Square1SfxHandler` | `mysmb_audio_step_square1` | Store original nonzero queue to F1, prioritize bit7 then bits0..6 while shifting live FF; start chosen phase once; queue0 checks buffer. |
| `CheckSfx1Buffer` | `mysmb_audio_first_square1 used by step_square1` | Zero buffer returns; otherwise bit7 then bits0..6 select matching continuation; no live queue shifts on continuation. |
| `ExS1H` | `mysmb_audio_step_square1 buffer==0 return` | No active buffer means no Square1 writes, length change or terminal mute. |
| `PlaySwimStomp` | `mysmb_audio_step_square1 effect04 start` | Length0E then PlaySqu1Sfx(26,9E,9C), immediately one envelope continuation in same frame. |
| `ContinueSwimStomp` | `mysmb_audio_step_square1 effect04 continuation` | Read envelope using old remaining length before4000 write; length06 additionally writes4002=9E before decrement. |
| `BranchToDecLength1` | `mysmb_audio_step_square1 shared length tail` | All original incoming paths have Z0: non-equal CPY6/CMP branches or fixed LDA9E, so continuation always reaches one decrement. |
| `PlaySmackEnemy` | `mysmb_audio_step_square1 effect08 start` | Length0E then PlaySqu1Sfx(28,9F,CB); fixed original nonzero frequency high|8 makes BNE directly to decrement, no same-frame smack continuation. |
| `ContinueSmackEnemy` | `mysmb_audio_step_square1 effect08 queue==0` | Length08 writes4002=A0 then4000=9F; other lengths write4000=90; one decrement. |
| `SmSpc` | `mysmb_audio_step_square1 smack non8 branch` | Spaces write90, without frequency rewrite. |
| `SmTick` | `mysmb_audio_step_square1 smack4000 write` | Writes chosen90/9F before shared decrement. |
| `DecrementSfx1Length` | `mysmb_audio_step_square1 final length--` | Unsigned byte decrement; zero length wrapsFF, length1 reaches zero and stops. |
| `StopSquare1Sfx` | `mysmb_audio_step_square1 terminal branch` | Clear only F1 then ordered4015=0E,4015=0F; terminal mute does not reorder same-value/retrigger commands. |
| `ExSfx1` | `mysmb_audio_step_square1 return after decrement/stop` | Return preserves result; unrelated queue clear/DAC belong actual SoundEngine caller. |
| `PlayPipeDownInj` | `mysmb_audio_step_square1 effect10 start` | Length2F, then pipe continuation gate and decrement in same frame. |
| `ContinuePipeDownInj` | `mysmb_audio_step_square1 effect10 continuation` | Original two LSR/carry tests and AND2 correspond exactly to (length&0B)==08; eligible frame calls PlaySqu1Sfx(44,9A,91). |
| `NoPDwnL` | `mysmb_audio_step_square1 pipe shared tail` | Both write and skip phases reach one common decrement; no double phase or extra command. |

4096 complete unchanged original SoundEngine start roots vary every queue byte
and16 prior-state profiles.65536 continuation roots exhaust every buffered byte
by every length byte; all other channels/music inactive but actual callees run.
Actual original Square1 caller entry/RTS and all feasible phase transfers
observed. Same RAM feeds public real C audio_step, not a private test clone.
Compare1841 RAM bytes including0109-0139 aliases,24 final APU registers and
the complete ordered command count/index/value sequence. Only true CPU stack
0100-0108/013A-01FF and unmapped transient registers excluded. Zero differences
in69,632 roots on both x86/x64. Queue shifts/priority and source-order state
writes additionally have the explicit static proof above; final queue clearing
is never used as a substitute for that transient-state audit.

Original indexed B9 read observation covers all14 valid envelope members at
lengths1..14 before control write/decrement, and all256 CPU-offset cases.
Offsets0/15..255 access neighboring original program bytes, not extra declared
envelope members; they are not table-extension credit. Native owner-local
F3B0+length reader and ordered4000/4002 writes match. No protected bytes retained
as tracked fixture or data array; no dependency/music-table node promotion.

Every unobserved raw fallthrough is separately proven impossible:

- `control-03208`: LDX99 before BNE FPS2nd sets Z0.
- `control-03210`: LDA26 before BNE JumpRegContents sets Z0.
- `control-03216`: LDYF6 before BNE DmpJpFPS sets Z0.
- `control-03222`: DmpJpFPS receives YF6/BC set by nonzero LDY; real Dump_Squ1_Regs only STY/STX/RTS preserves Z0.
- `control-03224`: LDY99 before BNE Fthrow sets Z0.
- `control-03231`: Every DecJpFPS entry has Z0: throw CMP6 unequal or LDA BB, jump CMP20 unequal or nonzero LDY on25/20 phases.
- `control-03241`: Queue0 already branched to buffer; any remaining positive nonzero byte has a winning bit0..6, bit7 already branched. Last BCS cannot fall through.
- `control-03251`: Buffer0 already branched ExS1H; any nonzero byte has bit7 or one winning bit0..6. Last BCS cannot fall through.
- `control-03257`: BranchToDecLength1 inputs carry Z0 from unequal CPY6/DecJpFPS branch or fixed LDA9E; BNE always taken.
- `control-03260`: Actual bound ROM FF29 frequency low for A28 is nonzero; high|08 is nonzero, so PlaySqu1Sfx returns Z0 and BNE always taken.
- `control-03263`: LDA9F before BNE SmTick sets Z0.

Immediate loads, the flag-preserving real store helper and fixed frequency
binding were checked against unchanged PRG/source index; queue/buffer proofs
exhaust the unsigned-byte bit cases. Absence of runtime hits alone is not the
basis. Source listing index has no mismatch in admitted range. Actual feasible
call returns include all seven caller-owned helper continuations listed for S2.

Operational native checker builds pass;7/7 focused tests each include audio,
header/death/channel smoke and platform purity. Original OpenNT DOS16 link
passes with existing OLDNAMES.LIB warning; no interactive DOS claim. No current
Square1 product repair required. Similar-issue sweep found no extra/double start
or continuation command, wrong selected queue bit, incorrect pipe gate, old/new
length index, byte wrap or reordered stop writes. Later active Square2/noise/
music remain S3-S5. Three T66 S2 products retained byte-identical:

- `mysmb16.exe`: 260839 bytes, SHA256 `1f99e8e864fcd5da449f3a643eab4f82e550b5b2229e71e167dd77ac96025fa0`.
- `mysmb32.exe`: 373854 bytes, SHA256 `efb2534dc2bb7074afb4c79db301431ef47beb18d09cd99c7f73a3ee631bed8b`.
- `mysmb64.exe`: 380886 bytes, SHA256 `87c198fc900fe0a4b744dd70459117c19d711ecf67957ebf7894374c6f0fdc84`.

Neutral local evidence under ignored build/m2-t67-s2: route-summary.json,
mode14/15 summaries/logs, coverage-summary.json, focused-x86/x64.log and
dos16-link.log. Raw deleted after each batch; compiled probe cleaned on closure.
Ledger/registry/progress/documentation gates required before P2 commit.

## S3 admission - Square2 complete effect chain

Scope36 pending nodes, intended current fresh36, maximum1804/1992:
ExtraLifeFreqData; PowerUpGrabFreqData; PUp_VGrow_FreqData; PlayCoinGrab; PlayTimerTick; CGrab_TTickRegL; ContinueCGrabTTick; N2Tone; PlayBlast; ContinueBlast; SBlasJ; PlayPowerUpGrab; ContinuePowerUpGrab; LoadSqu2Regs; DecrementSfx2Length; EmptySfx2Buffer; StopSquare2Sfx; ExSfx2; Square2SfxHandler; CheckSfx2Buffer; ExS2H; Cont_CGrab_TTick; JumpToDecLength2; PlayBowserFall; BlstSJp; ContinueBowserFall; PBFRegs; EL_LRegs; PlayExtraLife; ContinueExtraLife; DivLLoop; PlayGrowPowerUp; PlayGrowVine; GrowItemRegs; ContinueGrowItems; StopGrowItems. Scope and intended current set are identical, each
needs-evidence. Current1768/1992 nodes,3760/4301 feasible controls(raw4342,
infeasible41),404/493 material partial. Historical1992/1992 separate with
expectedMatches empty. Existing receiving map retained; no maintenance transfer.

S3 consumes accepted S1 register/frequency writers. Shared owner audio.c:
step_square2 priority/queue shifts, coin/timer/blast/power-up/Bowser/extra-life/
grow helpers and independent secondary counter. Source entry ExtraLifeFreqData
through StopGrowItems before BrickShatterFreqData; control scope
is source-owned non-return edges and caller-owned returns as corrected in S1.
Material00439-00441 requires actual index producer/read/write order for six
extra-life,27 power-up plus three residual,32 growth bytes; arbitrary byte lengths
are CPU-address semantics, not fabricated extra table membership.

ROM track: Unchanged original F2D0 SoundEngine -> actual Square2SfxHandler -> real RTS. Start4096 roots all256 queues/16 saved-state profiles including extra-life protection; continuation65536 all256 buffers by all256 lengths; growth65536 independent primary/secondary byte pairs. Real inactive other channels/music, full1841 RAM/24 APU/ordered writes x86/x64; scoped transitions and three frequency-table reads. Source15369-15564; no later noise/music credit.
The probe executes complete actual SoundEngine unchanged, with same controlled
initial RAM passed to native public audio_step. No test-only entry into private
Square2 helper, mocked children or patched ROM. Later inactive children return
normally and are not promoted. Confirm existing buffer bit40 wins over all
queued bits, then new bit7/bits0..6 priority, original buffer/live queue shifts,
coin30/blast18/Bowser08 tone changes, every-eight extra-life and even power-up
reads, secondary increment/wrap/equality with preserved primary growth length,
decrement0->FF and1->0, stop4015=0D then0F. Compare1841 RAM including0109-0139, final APU24 bytes,
all ordered write indices/values; exclude only true CPU stack/unmapped transient
registers. Actual call/return/fallthrough recording and source impossibility
proof required for every scoped edge. No absence-only infeasible classification.

Operational track: focused audio/music/death/channel/purity tests both widths,
minimal native checker builds and original OpenNT DOS16 link. Product-code
repair publishes all3 owner-authorized EXEs in same P; audit/test-only retains
byte-verified existing3 builds. Similar-issue sweep includes start-vs-continue
double commands, queue precedence, terminal mute and byte-index/wrap behavior.
Any feasible diff remains in S3 until repaired and reaudit clean; S4 unadmitted.

Owner-local original ROM/reviewed ASM are nonredistributable research inputs;
all probes/raw/scripts/logs under ignored build/m2-t67-s3,128MiB raw budget,
1024 roots/batch,120seconds/process,524288 instructions/root. Coordinator deletes
raw after comparison. No third-party code import or platform game logic.

## S3 P2 closure - Square2 priority, counters and frequency consumers

Completed36 expected labels: ExtraLifeFreqData; PowerUpGrabFreqData; PUp_VGrow_FreqData; PlayCoinGrab; PlayTimerTick; CGrab_TTickRegL; ContinueCGrabTTick; N2Tone; PlayBlast; ContinueBlast; SBlasJ; PlayPowerUpGrab; ContinuePowerUpGrab; LoadSqu2Regs; DecrementSfx2Length; EmptySfx2Buffer; StopSquare2Sfx; ExSfx2; Square2SfxHandler; CheckSfx2Buffer; ExS2H; Cont_CGrab_TTick; JumpToDecLength2; PlayBowserFall; BlstSJp; ContinueBowserFall; PBFRegs; EL_LRegs; PlayExtraLife; ContinueExtraLife; DivLLoop; PlayGrowPowerUp; PlayGrowVine; GrowItemRegs; ContinueGrowItems; StopGrowItems.
No deferred owned feasible relations or labels, no transfers, no product diff.
Owned71 raw controls:60 exact feasible,10 impossible fallthroughs and one
impossible branch03319. Material00439-00441 exact. Current1768->1804/1992
nodes,3760->3820 exact feasible controls; denominator4301->4290 only through
explicit instruction/path proofs(raw4342,infeasible52). Material404->407/493,
enumeration partial. Historical1992/1992 distinct, actualMatches empty. T67
still open with38 pending nodes; S4 noise next unadmitted.

| Inventory label | Shared counterpart | Manual source/state/control contract |
| --- | --- | --- |
| `ExtraLifeFreqData` | `mysmb_audio_square2_extra_life_freq` | Owner-local F4D3+index, six data members indexes1..6; divided old length supplies index before decrement. |
| `PowerUpGrabFreqData` | `mysmb_audio_square2_power_up_freq` | Owner-local F4D9+index,27 named data bytes plus three residual bytes before next label; even old length/2 supplies index. |
| `PUp_VGrow_FreqData` | `mysmb_audio_square2_grow_vine_freq` | Owner-local F4F8+index,32 shared growth bytes at indexes0..31; incremented secondary byte/2 supplies index. |
| `PlayCoinGrab` | `mysmb_audio_square2_play_coin_timer timer==0` | A35/X8D starts coin; nonzero X branches common controls. |
| `PlayTimerTick` | `mysmb_audio_square2_play_coin_timer timer!=0` | A06/X98 starts timer and falls common controls. |
| `CGrab_TTickRegL` | `mysmb_audio_square2_play_coin_timer` | Save length35/06, actual PlaySqu2Sfx A42/X8D-or98/Y7F then one continuation/decrement. |
| `ContinueCGrabTTick` | `mysmb_audio_square2_continue_coin_timer` | Length30 writes4006=54; other lengths skip tone; one decrement. |
| `N2Tone` | `mysmb_audio_square2_continue_coin_timer` | Branch to decrement always has nonzero Z from unequal CMP30 or LDA54. |
| `PlayBlast` | `mysmb_audio_square2_play_blast` | Length20, actual PlaySqu2Sfx(5E,9F,94), selected buffer continuation supplies exactly one decrement without another start write. |
| `ContinueBlast` | `mysmb_audio_square2_continue_blast` | Length18 writes PlaySqu2Sfx(18,9F,93), otherwise no tone; one decrement. |
| `SBlasJ` | `mysmb_audio_square2_play_blast / continue_blast` | Nonzero A5E/18 always routes shared Bowser/blast register phase. |
| `PlayPowerUpGrab` | `mysmb_audio_square2_play_power_up` | Set length36; same frame selected continuation performs table read/decrement. |
| `ContinuePowerUpGrab` | `mysmb_audio_square2_continue_power_up` | Odd old length skips frequency; even shifts once, reads table-1,Y and emits actual PlaySqu2Sfx(freq,5D,7F); one decrement. |
| `LoadSqu2Regs` | `mysmb_audio_play_sq2_sfx followed by square2_decrement` | Actual ordered controls/frequency then common length tail; source X/Y depend on original entry. |
| `DecrementSfx2Length` | `mysmb_audio_square2_decrement` | Byte decrement, zero wrapsFF; length1 terminates and clears buffer. |
| `EmptySfx2Buffer` | `mysmb_audio_square2_decrement / continue_grow_item` | Clear F2 before ordered terminal mute; grow path preserves ordinary length. |
| `StopSquare2Sfx` | `shared audio terminal writers; mysmb_audio_stop_square2_sfx for later callers` | Ordered4015=0D then0F; this entry itself does not clear F2, whereas preceding EmptySfx2Buffer does. Later music calls uncredited. |
| `ExSfx2` | `Square2 phase/decrement return` | Return after length or stop; queue clear/DAC remain SoundEngine caller. |
| `Square2SfxHandler` | `mysmb_audio_step_square2` | Saved buffer bit40 wins before new queue; otherwise save unshifted queue and bit7 then bits0..6 priority, shifting live FE. |
| `CheckSfx2Buffer` | `mysmb_audio_step_square2 buffer dispatch` | Zero returns; bit7 then lower winning bits select continuation. Bit40-only path already intercepted before queue read. |
| `ExS2H` | `mysmb_audio_step_square2 buffer==0 return` | No active effect means no Square2 commands/counter change. |
| `Cont_CGrab_TTick` | `mysmb_audio_square2_continue_coin_timer` | Coin/timer buffer bits1/10 share actual continuation/decrement path. |
| `JumpToDecLength2` | `mysmb_audio_square2_jump_to_decrement` | Direct common decrement from noneligible extra-life or Bowser phases. |
| `PlayBowserFall` | `mysmb_audio_square2_play_bowser_fall` | Length38, frequency18/Y C4 shared load writes then decrement once; caller returns immediately. |
| `BlstSJp` | `mysmb_audio_square2_load_bowser_regs / blast writers` | A18/5E from starts or blast continuation is nonzero; always proceeds common register path. |
| `ContinueBowserFall` | `mysmb_audio_square2_continue_bowser_fall` | Only old length08 emits frequency5A/Y A4; other lengths trampoline to decrement. |
| `PBFRegs` | `mysmb_audio_square2_load_bowser_regs / blast writers` | X9F common control for Bowser/blast phases. |
| `EL_LRegs` | `mysmb_audio_play_sq2_sfx from extra-life or shared Bowser load` | Nonzero X9F or preceding Y7F always branches to shared LoadSqu2Regs; extra-life uses X82. |
| `PlayExtraLife` | `mysmb_audio_square2_play_extra_life` | Length30 then immediate actual extra-life continuation. |
| `ContinueExtraLife` | `mysmb_audio_square2_continue_extra_life` | Old length low3bits nonzero takes decrement; otherwise index=length>>3, actual table read and PlaySqu2Sfx(freq,82,7F) before decrement. |
| `DivLLoop` | `mysmb_audio_square2_continue_extra_life low-three-bit test` | Original three LSR carry decisions equal (length&7)!=0; eligible length/8 index is unsigned, including0. |
| `PlayGrowPowerUp` | `mysmb_audio_square2_play_grow_item length10` | Length10 and unconditional common start; not vine fallthrough. |
| `PlayGrowVine` | `mysmb_audio_square2_play_grow_item length20` | Length20 uses same actual common growth start. |
| `GrowItemRegs` | `mysmb_audio_square2_play_grow_item` | Save primary length, write4005=7F, secondary0; fall into exactly one increment phase. |
| `ContinueGrowItems` | `mysmb_audio_square2_continue_grow_item` | Increment secondary modulo256, index=secondary>>1; equality to unchanged primary stops, else4004=9D and actual SetFreq_Squ2(table[index]); never decrement primary. |
| `StopGrowItems` | `mysmb_audio_square2_continue_grow_item equality branch` | Clear buffer then ordered4015=0D/0F, with primary and incremented secondary retained. |

Original full SoundEngine runs unchanged with actual Square2 entry/RTS:
4096 starts vary256 queues/16 saved-state profiles including40/C0/41 protected
buffers;65536 continuations exhaust256 buffered bytes by256 length bytes;
65536 growth inputs independently exhaust256 primary bytes by256 secondary
bytes. Other channels/music inactive, but their real original/native calls
execute. Public native audio_step consumes identical RAM, not a private test
clone. Full1841 RAM (including0109-0139),24 final APU registers and every
ordered command count/index/value compare zero differences in135,168 roots
each x86/x64. Only true CPU stack0100-0108/013A-01FF and unmapped transient
registers excluded. Static audit additionally proves live queue shifts/save,
priority and phase order; SoundEngine final clear alone cannot prove them.

Actual indexed original reads cover all six ExtraLifeFreqData bytes at1..6,
27 named PowerUpGrab bytes plus three residual bytes at1..30, and32 shared
growth bytes at0..31. Full-byte controlled lengths also exercise neighboring
program offsets (extra0..31, power-up0..127, grow0..127); these are CPU address
semantics, not invented extra data members or uncredited table owners. Index
producers and actual ordered consumer outputs before decrement are matched.
Growth equality/wrap keeps ordinary length unchanged; stop clears buffer and
emits0D/0F, exactly as the original. All scoped feasible edges have recorded
actual transitions and three caller-owned register helper returns.

Unobserved edges have explicit independent instruction/path proofs:

- `control-03277`: LDX8D sets Z0 before BNE common coin/timer entry.
- `control-03284`: N2Tone reached with Z0 from unequal CMP30 or fixed LDA54; BNE always taken.
- `control-03286`: LDA5E sets Z0 before BNE SBlasJ.
- `control-03290`: SBlasJ receives fixed nonzero A5E or18, so BNE BlstSJp always taken.
- `control-03310`: Nonzero new queue bit7 or bits0..6 must dispatch; zero queue already branches buffer. Final queue BCS cannot fall through.
- `control-03319`: Saved buffer bit40 is intercepted by entry AND40/BNE. New nonzero queue dispatches directly to a start and returns, never CheckSfx2Buffer; its last bit40 branch is unreachable.
- `control-03320`: At CheckSfx2Buffer zero already returns, bit40 already intercepted, and any remaining nonzero buffer has bit7 or a winning bit0..5; last BCS cannot fall through.
- `control-03325`: BlstSJp receives A18 from Bowser start or nonzero blast A5E/18; BNE PBFRegs always taken.
- `control-03330`: PBFRegs sets X9F/Z0; extra-life arrives after Y7F/Z0; EL_LRegs BNE always taken.
- `control-03336`: LDY7F sets Z0 before DivLLoop tail BNE EL_LRegs.
- `control-03338`: LDA10 sets Z0 before BNE GrowItemRegs.

These conclusions use the original bound PRG/index and exhaustive byte-bit
case reasoning.03319 is an impossible branch, not just an untested hit: the
entry protection and direct nonzero queue dispatch exclude its bit40 input.
No absence-only infeasible classification; all raw IDs retained. No active
music/noise or later cross-cohort boundary promotion.

Native checker builds pass;7/7 focused tests each include audio/header/death/
channel/purity. Original OpenNT DOS16 link passes with existing OLDNAMES.LIB
warning, no interactive DOS claim. Similar-issue sweep found no priority loss,
double tone/decrement, wrong threshold/division/parity, primary-vs-secondary
counter confusion, byte wrap, stop-buffer or command-order discrepancy. No
product repair required; three T66 S2 products retained byte-identical:

- `mysmb16.exe`: 260839 bytes, SHA256 `1f99e8e864fcd5da449f3a643eab4f82e550b5b2229e71e167dd77ac96025fa0`.
- `mysmb32.exe`: 373854 bytes, SHA256 `efb2534dc2bb7074afb4c79db301431ef47beb18d09cd99c7f73a3ee631bed8b`.
- `mysmb64.exe`: 380886 bytes, SHA256 `87c198fc900fe0a4b744dd70459117c19d711ecf67957ebf7894374c6f0fdc84`.

Neutral local evidence under ignored build/m2-t67-s3: route/coverage summaries,
mode16/17/18 indexed-read/transition logs, checker-build and focused native
logs, dos16-link.log. Raw deleted per batch, probe removed at closure. Ledger,
registry, admission/progress and documentation gates required before P2 commit.

## S4 admission - noise effects and exact stream boundary

Scope11 pending/intended current fresh11, maximum1815/1992:
BrickShatterFreqData; PlayBrickShatter; ContinueBrickShatter; PlayNoiseSfx; DecrementSfx3Length; ExSfx3; NoiseSfxHandler; CheckNoiseBuffer; ExNH; PlayBowserFlame; ContinueBowserFlame. Both sets identical; each needs-evidence.
Incoming current1804/1992 nodes,3820/4290 feasible controls(raw4342,
infeasible52),407/493 material partial; historical1992/1992 separate with
expectedMatches empty. Maintenance receiving map retained.

Shared owner audio.c; source15569-15629, BrickShatterFreqData through
ContinueBowserFlame. Owned controls03344-03360 and material00442.
Accepted S1 command writer and SoundEngine entry/return are predecessors.
BrickShatterEnvData/BowserFlameEnvData are owner-local consumer bindings;
their later N nodes receive no promotion. ContinueMusic/real music-stream
callees are an explicit output/return boundary dependency, not S5 admission.
The source BNE after flame table read may fall through for controlled byte
lengths outside the normal64-count phase: audit the actual predicate, do not
declare impossible merely because normal playback reads nonzero members.

ROM track: Unchanged F2D0 SoundEngine, actual NoiseSfxHandler and real RTS:4096 starts (256 queues by16 profiles),65536 continuations (256 buffers by256 lengths). Full1841 RAM/24 APU/ordered commands x86/x64, actual transitions and noise table reads. Zero flame envelope must fall through ContinueMusic to stream processing, not queue selection; real boundary callees run without S5 credit.
Static node audit covers queue precedence and mutation, odd brick index,
flame preceding-byte index, 16-bit address wrap, decrement0->FF/1->0,
terminal mute/clear and exact stream fallthrough. Every feasible difference
is repaired and rerun in S4 before S5. No mocked children or patched ROM.

Operational track: focused audio/music/channel/purity tests x86/x64, original
OpenNT DOS16 link; product repair refreshes all3 authorized assets EXEs,
audit-only retains byte-identical products. Sweep similar table-result
unconditional-branch translations and queue-vs-stream boundaries in audio.c.
Owner-local original ROM/reviewed ASM remain nonredistributable inputs;
ignored build/m2-t67-s4 contains logs/raw,128MiB raw budget,1024 roots/batch,
120seconds/process,524288steps/root; coordinator deletes raw after comparison.

## S4 P2 closure - exact noise effects and zero-envelope fallthrough

Completed all11 expected labels: BrickShatterFreqData; PlayBrickShatter; ContinueBrickShatter; PlayNoiseSfx; DecrementSfx3Length; ExSfx3; NoiseSfxHandler; CheckNoiseBuffer; ExNH; PlayBowserFlame; ContinueBowserFlame.
No deferred labels/owned feasible edges or transfers.17 owned controls exact,
material00442 exact; no new infeasible rows. Current1804->1815/1992 nodes,
3820->3837/4290 feasible controls(raw4342,infeasible52),407->408/493 material
partial. Historical1992/1992 remains separate; actualMatches empty. T67 open
with27 pending music-prefix nodes, S5 next unadmitted.

| Inventory label | Shared counterpart | Manual source/state/control contract |
| --- | --- | --- |
| `BrickShatterFreqData` | `mysmb_audio_brick_shatter_frequency` | Owner-local F62B+Y,16 table members; odd old remaining length/2 supplies unsigned index before decrement. Extended byte lengths preserve neighboring CPU reads. |
| `PlayBrickShatter` | `mysmb_audio_play_brick_shatter` | Save length20 then actual continuation once; initial even phase emits no noise register writes. |
| `ContinueBrickShatter` | `mysmb_audio_continue_brick_shatter` | LSR carry selects odd lengths only; index=old length/2 reads frequency F62B and envelope FFEA, then shared three-register write and one decrement. Even lengths decrement only. |
| `PlayNoiseSfx` | `mysmb_audio_play_noise_sfx` | Ordered400C=A,400E=X,400F=18; continues to noise length tail. Brick X is frequency-table result, flame X0F. |
| `DecrementSfx3Length` | `mysmb_audio_decrement_noise_length` | Unsigned byte decrement0->FF/1->0; nonzero returns; zero writes400C=F0 then clears F3, without own queue clear. |
| `ExSfx3` | `noise length helper return` | Return after nonterminal or mute/clear path; SoundEngine owns subsequent music/DAC/queue clearing. |
| `NoiseSfxHandler` | `mysmb_audio_step_noise` | Nonzero live FD saved unshifted into F3; live FD shifted in bit0 then bit1 priority, brick before flame. Unsupported bits reach buffer check with actual shifted queue retained. |
| `CheckNoiseBuffer` | `mysmb_audio_step_noise buffer dispatch` | Zero buffer returns; bit0 selects brick, else bit1 selects flame; copy shifts preserve actual F3. Unsupported bits do not alter length or emit effect commands. |
| `ExNH` | `mysmb_audio_step_noise no active selector return` | No buffered noise or unsupported-only bits returns to caller without noise counter/write change. |
| `PlayBowserFlame` | `mysmb_audio_play_bowser_flame` | Save length40 and immediately enter actual continuation once. |
| `ContinueBowserFlame` | `mysmb_audio_continue_bowser_flame / run_music_stream` | Index=old length/2 reads FFC9+Y with 16-bit wrap. Nonzero envelope writes noise(loaded A,0F,18) and decrements; zero falls through ContinueMusic into actual stream tasks, bypassing queue/header selection and noise decrement. Normal later SoundEngine music call remains separate. |

Original unchanged F2D0 SoundEngine/real NoiseSfxHandler/real RTS routes:
4096 starts cover256 queue bytes by16 saved-state profiles;65536 continuations
cover every256 buffer bytes by256 length bytes.128 additional roots exercise
zero-envelope lengths102/103 with active area music and independent counter
values3..66; the Square1 header offset is nonzero. These confirm the extra
stream invocation and later ordinary music invocation each advance original
channel counters. Public native audio_step uses identical input RAM/APU and
real callees, not private test clones or patched ROM.69760 roots each x86/x64
have zero differences:1841 RAM bytes including0109-0139,24 final APU registers,
every ordered write count/index/value. Only CPU stack0100-0108/013A-01FF and
unmapped transient registers excluded. All17 scoped edges actually observed,
including03360 zero-result fallthrough; none inferred from missing coverage.

Indexed original reads cover all16 frequency and brick-envelope members,
flame preceding byte/index0 and32 proper members/index1..32. Full byte lengths
also exercise adjacent PRG and wrapped low RAM at indexes0..127; no invented
extra table membership. Envelope producer nodes remain later N custody and
uncredited; their actual consumer reads/output are proven for this chain.

Found and repaired a feasible difference: C treated source BNE PlayNoiseSfx
as unconditional. Controlled original length66 reads zero at FFC9+51; original
keeps noise length66 and enters ContinueMusic, C instead emitted noise and
decremented65. Shared audio.c now branches on loaded envelope; zero runs the
same stream tasks used by ordinary music handling, without selecting queues
or decrementing noise. Full source/current comparison rerun clean after fix.
Normal flame lengths1..64 read nonzero envelopes; this finding proves a
controlled-state semantic gap, not a claim of a newly observed ordinary-game
audio symptom. No platform implementation or game state fork was added.

Similar-issue sweep: noise helpers and adjacent Square1/Square2 table branches
in audio.c checked against source. Brick effect intentionally writes even a
zero loaded envelope after its carry-controlled entry; only flame uses the
loaded value as its branch predicate. Frequency helpers preserve NoTone;
existing length/parity, extra-life priority and growth-counter predicates
remain explicit. Music selection remains gated separately; stream fallthrough
does not replay queue selection. No other scoped repair hit. Noise CTest adds
neutral zero-envelope inactive/active-music regression; initial active test
omitted Square1 stream offset and was corrected to provide that prerequisite,
then checked against original active-boundary records rather than changing
production to satisfy the mistaken assertion.

Operational: full248/248 tests each width, updated focused7/7 each, purity
included. Original OpenNT DOS16 link passes with inherited OLDNAMES.LIB warning;
no interactive DOS claim. Native products and original DOS16 product rebuilt
and packaged together under owner's explicit EXE authorization:

- `mysmb16.exe`: 260903 bytes, SHA256 `aab03505ce4ac8f97b6af89c46964289f2d7ef07dacae0857680e862dcadc0d2`.
- `mysmb32.exe`: 373920 bytes, SHA256 `c3c6a7332e3b93952190dd14b01a5b9f07df1f2541d11b0d9d6f43e2a440d207`.
- `mysmb64.exe`: 380951 bytes, SHA256 `507fa3cd92cd53b3b158b709c1f9b21ac8d62ae5a005033eab0b136cd8e17dbc`.

Existing owner audio/title/focus-pause features remain in the source/products.
Neutral evidence under ignored build/m2-t67-s4: pre-fix-difference, modes19-21,
route/coverage summaries, full/focused tests and builds, dos16-link. Raw deleted
per batch; probe removed at closure. Ledger/registry/progress/docs gates must
pass before P2 commit. Unrelated owner I/O proposal/queue/source work preserved.

## S5 admission - M-owned music selection and stream prefixes

Scope27 pending/intended current fresh27, maximum1842/1992:
ContinueMusic; MusicHandler; LoadEventMusic; NoStopSfx; LoadAreaMusic; NoStop1; GMLoopB; HandleAreaMusicLoopB; FindAreaMusicHeader; FindEventMusicHeader; LoadHeader; HandleSquare2Music; EndOfMusicData; NotTRO; MusicLoopBack; VictoryMLoopBack; Squ2LengthHandler; Squ2NoteHandler; Rest; SkipFqL1; MiscSqu2MusicTasks; NoDecEnv1; HandleSquare1Music; FetchSqu1MusicData; Squ1NoteHandler; SkipCtrlL; MiscSqu1MusicTasks. Sets identical, every node needs-evidence.
Incoming current1815/1992 nodes,3837/4290 feasible controls(raw4342,
infeasible52),408/493 material partial. Historical1992/1992 separate with
expectedMatches empty; maintenance receiving map retained.

Shared owner audio.c, ContinueMusic through MiscSqu1MusicTasks in actual M
inventory/source15632-15826.82 owned raw controls03361-03430/04078-04089;
no currently enumerated M material row remains. Accepted command/frequency
helpers and exact noise stream boundary are predecessors. Header/music/
envelope tables, AlternateLengthHandler and triangle/noise continuation are
explicit actual N dependencies: execute original/current real callees and
audit input/output/order, but do not promote their nodes or own later scope.

ROM track: Unchanged F2D0 SoundEngine -> real MusicHandler/header/stream callees -> real RTS. Exhaust256 queue bytes with saved-state profiles, then sequential real music playback for all8 event and8 area selectors. Full1841 RAM/24 APU/ordered commands x86/x64; scoped actual transitions, pointer/header/note/envelope consumer audit; uncovered feasible paths get controlled original inputs, never inferred credit.
Static contracts: event priority/death stops/area save/time-out length adder;
area underground stop/ground header advance32->11; header bit scan and exact
CPU reads; all six header fields/counter resets/master writes; Square2
length/note/rest/effect priority/envelope old index; EndOfMusicData timeout,
victory,area loop and terminal return; Square1 zero-prefix loop/alternate
register/note-length/control/effect gating and actual N tail handoffs.
Header loader guards and current return classifications are reviewed against
source, not justified only by happy-path songs. Any scoped feasible diff
must be repaired and reaudited here before S6. No synthetic ROM patch/mock.

Operational: focused tests/checker x86/x64, original OpenNT DOS16 link/purity.
Product repair refreshes all3 owner-authorized EXEs; audit/test-only retains
byte-identical S4 products. Sweep source predicates and RAM/APU write order
in the complete admitted music chain. Source policy: owner-local original
ROM/reviewed ASM nonredistributable, no third-party import. All local scripts,
logs/raw under ignored build/m2-t67-s5,128MiB raw budget,1024 roots/batch,
120seconds/process,524288steps/root; coordinator deletes raw after comparison.

## S5 P2 closure - exact music selection and prefix streams

All27 expected labels completed: ContinueMusic; MusicHandler; LoadEventMusic; NoStopSfx; LoadAreaMusic; NoStop1; GMLoopB; HandleAreaMusicLoopB; FindAreaMusicHeader; FindEventMusicHeader; LoadHeader; HandleSquare2Music; EndOfMusicData; NotTRO; MusicLoopBack; VictoryMLoopBack; Squ2LengthHandler; Squ2NoteHandler; Rest; SkipFqL1; MiscSqu2MusicTasks; NoDecEnv1; HandleSquare1Music; FetchSqu1MusicData; Squ1NoteHandler; SkipCtrlL; MiscSqu1MusicTasks.
No deferral or transfer.82 raw controls:78 feasible exact,4 independently
impossible fallthroughs retained. Current1815->1842/1992 nodes,3837->3915
exact feasible controls; denominator4290->4286(raw4342,infeasible56).
Material408/493 remains partial; no new M producer/table row fabricated or
later N row promoted. Historical1992/1992 separate, actualMatches empty.
All126 T67 nodes now exact; T67 remains open until S6 census/integration.

| Inventory label | Shared counterpart | Manual source/state/control contract |
| --- | --- | --- |
| `ContinueMusic` | `mysmb_audio_continue_music / run_music_stream` | Actual stream handoff starts Square2, then real Square1/triangle/noise continuations; no queue/header selection replay. |
| `MusicHandler` | `mysmb_audio_step_music / select_music` | Event queue before area queue; without queues, active-buffer OR controls continuation; both clear returns without stream work. |
| `LoadEventMusic` | `mysmb_audio_load_event_music` | Save exact event A; death1 stops Square1 then Square2, clears only Square1 buffer; others skip stops. |
| `NoStopSfx` | `mysmb_audio_load_event_music` | Save current area buffer into alternate, clear length adder/area; event40 sets adder8, otherwise0; actual header bit scan follows. |
| `LoadAreaMusic` | `mysmb_audio_load_area_music` | Exact area4 stops Square1; other masks skip stop, then common ground-counter initialization. |
| `NoStop1` | `mysmb_audio_load_area_music` | Ground header counter10 starts all new area selections before area loop handler. |
| `GMLoopB` | `mysmb_audio_handle_area_music_loop / load_area_music` | Store supplied ground selector, re-enter area chain; reset11 must increment again before header read. |
| `HandleAreaMusicLoopB` | `mysmb_audio_handle_area_music_loop` | Clear event, save area; area!=1 bit scan. Area1 increments byte counter;32 resets11 and loops to increment12, otherwise direct header. |
| `FindAreaMusicHeader` | `mysmb_audio_handle_area_music_loop` | Residual F7=08 precedes area selector scan with Y8; later LoadHeader resets F7. |
| `FindEventMusicHeader` | `mysmb_audio_find_header_selector` | Increment selector before each LSR; lowest set bit selects event1..8 or area9..16; reachable caller mask nonzero. |
| `LoadHeader` | `mysmb_audio_load_music_header` | All256 byte selectors read F90C+Y then six bytes F90D+offset; exact RAM field/counter/reset/master0B->0F order. Missing/short owner binding guards are outside admitted complete-ROM ABI. |
| `HandleSquare2Music` | `mysmb_audio_step_square2_music` | Byte decrement; nonzero runs tail. Zero increments stream offset before CPU pointer read; zero ends, positive note, negative length followed by next note. |
| `EndOfMusicData` | `mysmb_audio_end_square2_music` | Exact event40 restores nonzero alternate area first; otherwise Victory mask4 loops; area masked5F loops; no remaining music clears both buffers then triangle0/Square1 90/Square2 90 and returns. |
| `NotTRO` | `mysmb_audio_end_square2_music` | AND4 result, not unmasked original event, becomes A for victory tail load; event40 with zero saved area leaves zero A at this test. |
| `MusicLoopBack` | `mysmb_audio_handle_area_music_loop from end_square2_music` | Actual tail loads area header and resumes Square2 in same invocation; timeout uses saved area, ordinary loop uses masked5F area. |
| `VictoryMLoopBack` | `mysmb_audio_load_event_music from end_square2_music` | Tail transfer consumes masked event4; reload/header then current Square2 note in same invocation. |
| `Squ2LengthHandler` | `mysmb_audio_step_square2_music / process_music_length` | Actual length lookup saves7B3, then increments stream offset and reads second byte as note without a second length classification. |
| `Squ2NoteHandler` | `mysmb_audio_step_square2_music` | Active F2 skips frequency/control but still loads note counter. Otherwise actual SetFreq/LoadControlRegs/rest and Dump_Sq2_Regs order. |
| `Rest` | `mysmb_audio_step_square2_music` | Save returned A as envelope; rest keeps SetFreq X4 and Ynote while nonrest supplies X82/Y7F; ordered dump follows. |
| `SkipFqL1` | `mysmb_audio_step_square2_music` | Copy original note-length buffer7B3 to counter7B4 regardless effect ownership. |
| `MiscSqu2MusicTasks` | `mysmb_audio_step_square2_music tail` | F2 nonzero or event&91 skips envelope tail; otherwise old envelope index is used while RAM is decremented. |
| `NoDecEnv1` | `mysmb_audio_step_square2_music / load_music_envelope` | Zero index is still read; actual helper then4004 envelope/4005 7F, actual Square1 handoff. |
| `HandleSquare1Music` | `mysmb_audio_step_square1_music` | OffsetF8 zero goes straight to triangle; else byte counter decrement decides fetch vs tail. |
| `FetchSqu1MusicData` | `mysmb_audio_step_square1_music zero-prefix loop` | Increment offset and read CPU stream. Each zero writes4000=83/4001=94/saves alt94, then loops; first nonzero note goes note handler. |
| `Squ1NoteHandler` | `mysmb_audio_step_square1_music` | Actual alternate length bits0/7/6 produce lookup/count; active F1 goes directly triangle, else masked note SetFreq/LoadControlRegs. |
| `SkipCtrlL` | `mysmb_audio_step_square1_music` | Save frequency-return A or loaded envelope; actual Dump_Squ1_Regs with source X/Y values before tail. |
| `MiscSqu1MusicTasks` | `mysmb_audio_step_square1_music tail` | F1 nonzero bypasses writes; event&91 bypasses envelope but retains actual alternate-register tail; otherwise pre-decrement index read and alternate tail before triangle. |

20736 unchanged original roots compare full1841 RAM (including0109-0139),
24 APU registers and every ordered command count/index/value each x86/x64:
4096 event queue profiles,4096 area queue profiles,4096 continuous music
states (256 calls for each8 event/8 area selector),4096 controlled terminal/
ground reset/victory/timeout routes,4096 active-effect/tail profiles,256 direct
LoadHeader selector boundaries from F6F5 to F73A. Full SoundEngine entry F2D0
and real RTS used otherwise. Source N continuation/table callees execute
actually, with boundary outputs/returns audited, but their nodes uncredited.
Only CPU stack0100-0108/013A-01FF/unmapped transient registers excluded.
Direct header helper has no C A-register ABI, so its transient A is excluded;
all its RAM/APU/order is compared. All27 node entries/78 feasible edges seen.

Continuous route preserves actual prior original RAM/APU between calls while
restoring the recorder CPU/PPU timing baseline per root. Initial full-machine
continuation accidentally accumulated reference-machine scheduling outside
the audio-only root; corrected recorder containment, then replayed. No ROM
instruction patched, no child mocked, no native output used as original input.
Final roots were rerun against final shared C after all repairs.

Repairs by original source: ground header32->LDY11/GMLoopB must re-enter the
increment path and actually load12; previous C loaded11. Victory tail consumes
AND4 output, previous C loaded full event mask. LoadHeader has no selector
0/40 upper guard; removed C-specific byte restrictions and restored its F7
reset after note counters. Full256 original selector boundary proves this
contract; adjacent data reads retain original CPU indexing, not new table
membership. Existing complete-ROM binding guards remain outside ROM state.
No platform game logic added. Similar-issue sweep covers all admitted event/
area masks, forced branches, loop re-entry, header reads/write order, Square1
zero-prefix/alternate controls, Square2 length/rest/effect/envelope tails.
Other forced branches follow fixed nonzero flags; actual zero-result flame
branch remains as accepted S4 repair, not forcibly unconditional.

Unobserved raw fallthroughs independently proven impossible:

- `control-03371`: LDX08 sets Z0 before BNE FindEventMusicHeader.
- `control-03380`: LDY11 sets Z0 before BNE GMLoopB.
- `control-03389`: Zero data already branches EndOfMusicData; nonnegative data already branches Squ2NoteHandler; surviving negative data necessarily makes BNE taken.
- `control-03418`: LDA94/STA leave Z0 before BNE FetchSqu1MusicData; note entry is the earlier nonzero-byte branch, not this fallthrough.

Note03418's earlier annotation described a different branch; corrected to
the actual LDA94/BNE instruction, retaining historical evidence. No absence-
only infeasible classification. Actual scoped header/stream fields and helper
data consumers were audited; remaining table-producer material census stays
with N and global enumeration remains partial.

Operational: final builds/248 tests each width pass; direct256-selector table
checker passes each. Original OpenNT DOS16 link passes, inherited OLDNAMES.LIB
warning retained; no interactive DOS claim. A prior same-tree concurrent
full/checker build failed artifact links; all final builds run without that
contention and no failed/stale artifact is acceptance evidence. All3 products
refreshed together under owner authorization, retaining audio/title/focus pause:

- `mysmb16.exe`: 260887 bytes, SHA256 `f0f539f9a4c687a25259325db9702c5a5974d05a9be0492a57b79c2224372a83`.
- `mysmb32.exe`: 373920 bytes, SHA256 `deb1b52df54056b5480d282a87e79f6972872a1a662bf763446032cf80bea238`.
- `mysmb64.exe`: 380951 bytes, SHA256 `7372175fca354684ab12fcecc166b6d1adda080a09d6481e6c0250b07ea14da8`.

Neutral ignored evidence under build/m2-t67-s5: modes22-27, route/coverage
summaries, pre-fix terminal diff, final tests/builds/header-table/DOS16 logs.
Raw removed per batch, probe removed at closure. Registry/ledger/progress/docs
gates required before P2 commit; unrelated owner work remains unstaged.
