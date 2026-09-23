# Roadmap

## M0: Governance And Translation Plan

Establish project authorities, source/research boundary, M/T/S/P lifecycle, M0 plan, validation contract, and portable-C constraints. Exit when the project can admit ROM research without ambiguity about provenance or proof.

## M1: Static-C And Win32 Bring-Up

Admit one ROM revision and reviewed disassembly under local-only policy. Build a static 6502-to-C90 conversion path and display the title scene in native Win32 x86 and x64 windows. The OpenNT compiler must compile the same core in large-model DOS mode. `nnes` supports reference validation; NTVDM64 supports only non-graphical DOS checks.

## M2: Complete C Logic And Oracle

Complete the static C translation and its local oracle: deterministic inputs, state checkpoints, and frame comparisons. Title, gameplay, death, warp, completion, objects, area parsing, and audio commands run through translated C; the Win32 x86/x64 executable is playable end to end while DOS-core compilation remains green.

## M3: DOS VGA And Text Presentations

Refactor generated C only where trace coverage remains intact. Add the DOS VGA Mode X adapter and 80×25 colored-object presentation over the same game state; neither becomes a logic path.

## M4: 486SX Qualification And Closure

Measure and tune the real DOS executable on a 25 MHz 486SX. Verify supported MS-DOS versions, VGA timing, input, sound, full-route behavior, and Win32/DOS cross-build equivalence; close only with no unexplained logic divergence.

## M5 And Later: Optional Host Expansion

Add further host adapters only when they preserve the validated C game layer and do not weaken DOS 16-bit compatibility.
