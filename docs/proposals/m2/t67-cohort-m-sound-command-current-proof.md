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
