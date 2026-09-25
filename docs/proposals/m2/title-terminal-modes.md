# M2 candidate: Title and terminal modes

## Status

M2 T15 S1-S3 are complete; S4 is active in P1.

## ROM scope

ROM lines 982-1385: title menu, world selection, demo, victory, end-world and floating-number labels.

## Existing-code disposition

Audit title/mode branches spread through game.c, area.c, object/OAM helpers and smoke tests. Keep only label-owned code.

## Graph contract

Entered through the operation-mode tree; emits text/VRAM, OAM and audio requests.

## Admission S plan

1. **S1 complete (P1)** - Bind title, select/start and demo labels to current code or replacement targets; record button-edge semantics.
2. **S2 complete (P1-P3)** - Translate title bootstrap, menu, selection and demo state/data paths; prove idle and Select NMI output.
3. **S3 complete (P1-P8)** - Translate victory, end-world and floating-number paths including text/OAM/audio output; P5 freezes the ROM-slice module boundaries before further terminal changes, and P8 restores the RenderPlayerSub post-scroll handoff.
4. **S4 active (P1)** - Compare only source-reachable routes at NMI return. P1 establishes title-start/right and idle-to-demo baselines; P2 must reach terminal routes from recorded source-valid checkpoints or prove their prerequisite state; P3 resolves every output difference at its ROM owner and deletes displaced branches.

## Acceptance

Mode task bytes and ROM-owned text, OAM and audio outputs agree at NMI return.

Platform code may not read or write these game decisions. Delete replaced code in the same admitted task once its ROM trace proves the replacement.

## S2 P1: title subtree boundary

src/game/title_modes.c now owns the translated TitleScreenMode leaves: title-area preparation, title command transfer, title data binding/bootstrap, GameMenuRoutine, StartGame, and DemoEngine. game.c retains shared game-frame and later terminal-mode owners. `title_modes.h` owns the fixed title-buffer ABI used by the remaining ScreenRoutines leaf. The same source was rebuilt for x86, x64, and OpenNT DOS; x86/x64 CTest each passed 78/78.

## S2 P2: menu branches

`title_modes.c` now translates ChkSelect through ResetTitle: exact-button selection, per-press debounce, two-player icon rewrite, world-select B increment/template, demo input handoff, and reset behavior. It moves the existing ScreenRoutines call to the title owner without adding platform behavior.
## S2 P3: title frame-route evidence

Two bounded 600-sample NMI-return comparisons were produced below `build/t15-s2-p3` and are not tracked: idle title (`0:0`) and a one-frame Select press at frame 200.  The reference uses NES serial `Select=$04`; the native recorder uses decoded `Select=$20`.  In both comparisons CPU OAM backing, CPU work RAM `$0300-$07ff`, both CIRAM pages, palette, visible OAM, audio command bytes, and all seven PPU scalar bytes had zero differences.  The Select trace confirms `ChkSelect -> DrawMushroomIcon -> UpdateScreen` including the ROM's temporary `$2000=$94` transfer phase.  x86/x64 native traces are byte-identical for the idle route.  Remaining recorder differences are only 6502 temporary zero-page and stack execution state.

## S3 P1: terminal subtree boundary

src/game/terminal_modes.c now owns the contiguous ROM terminal-mode tree: TransposePlayers, ContinueGame, NextArea, PlayerLoseLife, SetupGameOver/RunGameOver, VictoryModeSubroutines, and PrintVictoryMessages. The public dispatch leaves remain called from the shared frame root; game.c no longer contains these mode decisions. FloateyNumbers remains in objects.c, its existing ROM object/OAM owner. The migration is body-preserving except for replacing module-local literal RAM operands with the same named source addresses. x64 and x86 CTest each passed 78/78; OpenNT linked the DOS MZ with the existing OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 256D5D148FB18B2AD5FF66BFAD438E56E2D194C60242B001D9C0E6D627B3E711, mysmb32.exe 77A8B6EFD6C76EBEC81E2574AEEE3A67E607AC427DFF06E1937305186C9DA68F, and mysmb64.exe AF234360CEEE40C2B4CEE7F23E0B50D15F7BC8E5029E6BA63BE20C6DEFE7F2D7.

## S3 P2: PlayerVictoryWalk scroll sequence

The original PlayerVictoryWalk always calls AutoControlPlayer, then, until ScreenLeft_PageLoc reaches DestinationPageLoc, adds 0x80 to ScrollFractional, derives the carry-adjusted one-or-two-pixel amount, calls ScrollScreen, calls UpdScrollVar, and increments VictoryWalkControl. The C path had returned directly to message task 3 once the player reached x=0x60, omitting the remaining page scroll. terminal_modes.c now retains that exact branch order: the generic player owner supplies ScrollScreen through mysmb_player_scroll_screen, and the shared area-parser owner supplies UpdScrollVar. A mode regression checks the walk counter, fractional byte, scroll amount, and screen position after the first forced-scroll frame. Full x64 and x86 CTest passed 78/78; the rebuilt OpenNT DOS MZ retains the existing OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 D1C101442F2052C286616ABA81CB58D22D570D340BA821CF13A6F04921FC447B, mysmb32.exe 29F1F47C03D7CEDA415621820CA2404E6BF455A1F1FE3DD208F8146B546E5568, and mysmb64.exe 5F6A48F44B02A2414024F2257200F97DD13E3171105E1ED6D54B7B6131E482A8.

## S3 P3: immediate area-pointer transitions

ROM NextArea and PlayerEndWorld both call LoadAreaPointer immediately after changing AreaNumber or WorldNumber. The prior C path deferred this until a later setup task, leaving the pointer fields stale for a frame. terminal_modes.c now uses one terminal-owner helper for the three source call sites: ContinueGame, NextArea, and PlayerEndWorld. The owner-local area regression binds the SMB1 PRG, executes PlayerEndWorld from world 1, and compares the area pointer, type, low offset, enemy pointer and area-data pointer bytes with a direct LoadAreaPointer result for world 2 area 1. x64 and x86 CTest passed 78/78; OpenNT linked the DOS MZ with the existing OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 1D78FD2166BCD973E3579A362965D34D4C22E8B09035BAB6C230FF3958DF3821, mysmb32.exe F8818B1D229A02D6A3AE056C7F9D5FA0F6C3C70959F8B1EBF63E8EA5753214AF, and mysmb64.exe C0F7AC3E1F43AA9737EE1FC9C26400AB34675C1B764ECD2836FE821DFFD2B2EE.

## S3 P4: FloateyNumbers terminal collaborator

FloateyNumbersRoutine remains owned by objects.c because GameEngine invokes it after each enemy slot, but it is a T15 terminal-mode collaborator through score, extra-life and OAM output. ROM comparison found two missing effects: a Spiny score must use the ordinary enemy OAM offset, and control 0x0b at timer 0x2b increments NumberofLives and queues Sfx_ExtraLife (Square2SoundQueue=0x40). The shared object route now implements both in source order. The Floatey OAM regression covers the 1-UP score, sound queue and Spiny offset. x64 and x86 CTest passed 78/78; OpenNT linked the DOS MZ with the existing OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 B160B17030A2168CA7B3323E20078AADFBB26D0D796980044BE0463D87D088BB, mysmb32.exe AE565456561C4AA39F8BBED9C2FA8A565FC527080A348163328376819156AA45, and mysmb64.exe C87A5281478765A34B295DA39DC70075468ECC486DD9DF2FA25CA1C16D3D4E82.

## S3 P5: structure and platform-boundary gate

The T15 label map now records the concrete source-owner boundaries that govern all remaining migration. title_modes.c owns only title/menu/demo, terminal_modes.c owns only terminal mode leaves, and Floatey remains an object-loop collaborator because GameEngine invokes it once per enemy slot. game.c is prohibited from reacquiring title or terminal decisions; its screen/task leaves are reserved for the separately admitted Screen/text/status candidate. The platform audit found and corrected only physical-key translation: Win32 maps J to NES A and K to NES B; DOS scan codes J and K map to the same shared button bits. No platform file reads or writes game RAM, mode/task state, collision, scroll, HUD/text, or OAM construction. This is structural and input-adapter work, not a gameplay-rule change. A clean rebuild also exposed two stale core-smoke expectations for CPU RAM 0160 and 01fe. InitializeMemory deliberately leaves that range unspecified; the test now checks only source-owned initialized state. Full rebuilt x64 and x86 suites each pass 78/78; OpenNT links the DOS MZ with the existing OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 5902B97D80B1F281F6D37B055F1B0D7E7C35F6F8C2572CC49E8D27A660E5C851, mysmb32.exe EAEFB29870C48A1EB59C5119B4E1E5D09F3AE5DE0D35E6AAB293D7BB761FEF6C, and mysmb64.exe 62CA33C0819323C97B12910C1986A746DD6C96540FDC54243A69613001501DCE.

## S3 P6: Game Over text path and timer ownership

The ROM GameEngine calls RunGameTimer only from GameMode after GameCoreRoutine reaches GameEngine. The native frame root had invoked the timer tail after every operating mode. A controlled comparison entered GameOverMode by changing only OperMode and OperMode_Task after 30 already-equal title NMI samples. ROM SetupGameOver and ScreenRoutines then reached DisplayIntermediate and WriteGameText. The incorrect global timer call queued a 207a timer command after the Game Over text and overwrote its buffer. mysmb_game_run_timer now returns unless OperMode equals GameMode (1). The mode smoke asserts that a GameOverMode ScreenRoutines frame cannot reload GameTimerCtrl. Against local nxvm MyNES reference commit f91686808, samples 30 through 119 have zero differences in CPU OAM backing, work RAM 0300-07ff, both CIRAM pages, palette, visible OAM, audio commands, and all PPU scalar values; only CPU temporary zero-page and stack differ. The controlled native trace is byte-identical for x86 and x64. Full rebuilt x64 and x86 suites each pass 78/78; OpenNT links the DOS MZ with the existing OLDNAMES.LIB warning. Refreshed artifacts: mysmb16.exe SHA-256 9CD55AF3172C5F9AC0C42C8888716CBBEF7D7FED59187DDBBF7F1CC609BA580A, mysmb32.exe 77235705EB618ABE1E9C1C3D4DC2D9327695E214DB4C056B9AED7BFBEE7FD08B, and mysmb64.exe E4861538ED2AB774DE412CF9471E0BE41D9789B0D7464EF0D10C4C88AE71F417.

## S3 P7: Victory message route evidence

A second build-only controlled route changed only OperMode, OperMode_Task, message counters, world, and current-player bytes after 30 title NMI samples already known equal. It entered VictoryMode task 3 and executed PrintVictoryMessages with the original message-counter cadence. Against local nxvm MyNES reference commit f91686808, samples 30 through 119 have zero differences in CPU OAM backing, work RAM 0300-07ff, both CIRAM pages, palette, visible OAM, audio commands, and all PPU scalar values; CPU temporary zero-page and stack remain excluded. The x86 and x64 native controlled Victory traces are byte-identical. The executables remain the P6 three-target artifacts: mysmb16.exe SHA-256 9CD55AF3172C5F9AC0C42C8888716CBBEF7D7FED59187DDBBF7F1CC609BA580A, mysmb32.exe 77235705EB618ABE1E9C1C3D4DC2D9327695E214DB4C056B9AED7BFBEE7FD08B, and mysmb64.exe E4861538ED2AB774DE412CF9471E0BE41D9789B0D7464EF0D10C4C88AE71F417.

## S3 P8: RenderPlayerSub scroll handoff

The controlled PlayerVictoryWalk route exposed a source-order omission in the player graphics owner, not a terminal-mode rule.  In the ROM, after PlayerVictoryWalk calls AutoControlPlayer and its explicit ScrollScreen, VictoryMode reaches RelativePlayerPosition -> PlayerGfxHandler -> RenderPlayerSub.  RenderPlayerSub copies Player_Rel_XPos to Player_Pos_ForScroll ($0755); next frame's ScrollHandler consumes that post-scroll value.  `mysmb_player_draw_oam` already reconstructed the relative coordinate for drawing but omitted the `$0755` write, so the next frame reused a pre-scroll coordinate and advanced one extra pixel.  The write now belongs to `player.c` at the translated RenderPlayerSub node, with a player-OAM regression assertion.  In a bounded 80-sample controlled route, samples 30-79 now have zero differences in both CIRAM pages, palette, audio command state and all PPU scalars, including scroll X; the previous scroll drift beginning at sample 42 is absent.  OAM backing/visible OAM still diverge at samples 62/63 because this synthetic fixture retains title-page enemy slots and does not reproduce a source-reachable castle completion state.  That residual is explicitly deferred to S4's complete route fixture and was not hidden by clearing slots.  Full rebuilt x64 and x86 suites each pass 78/78; OpenNT links the DOS MZ with the existing OLDNAMES.LIB warning.

Refreshed artifacts: mysmb16.exe SHA-256 AF7F84D676590800E4A8B0375FEC504C9BF557CFE42E18412817A3B7D9CE58D2, mysmb32.exe DD5DD9ACCB15AAFD848F4AB112834C7C7A76A9F7FC02855631106963F97071F7, and mysmb64.exe C513FE3142FB894B4391C154ED65EB1E950283C8FFDAA5CB49A35EBD0C1C8C9E.

## S4 P1: reachable title-to-play and demo baselines

S3 is complete: its T15 label owners are isolated and its direct terminal leaves have source-level regressions.  S4 begins route proof without treating a forced mode byte as gameplay evidence.  Two independent 600-sample NMI-return runs use the local nxvm MyNES reference at commit `f91686808` and the native x64 recorder.  Route one begins at the real title screen, presses Start for exactly one frame at sample 200, then holds Right from sample 360 through 598.  Route two supplies no controller input and reaches the ROM demo through the title timer.  In both routes CPU OAM backing `$0200-$02ff`, work RAM `$0300-$07ff`, both physical CIRAM pages, palette, visible OAM, audio command bytes, and all seven PPU scalar bytes have zero differences for every one of the 600 samples.  Only 6502 execution temporaries (zero page and stack) differ.  The recorder must explicitly override its mandatory native Start window with `0:0` for the idle route; otherwise it introduces a test-only `$06fc` difference.  P2 is limited to source-reachable terminal checkpoints; the prior synthetic PlayerVictoryWalk probe remains diagnostic evidence only and cannot close a terminal route.

S4 P1 executable verification: mysmb16.exe SHA-256 AF7F84D676590800E4A8B0375FEC504C9BF557CFE42E18412817A3B7D9CE58D2, mysmb32.exe DD5DD9ACCB15AAFD848F4AB112834C7C7A76A9F7FC02855631106963F97071F7, and mysmb64.exe C513FE3142FB894B4391C154ED65EB1E950283C8FFDAA5CB49A35EBD0C1C8C9E. The OpenNT link retains its existing OLDNAMES.LIB warning.
