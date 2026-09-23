# M1 Static-C Source Pipeline

## Purpose

Admit one owner-supplied SMB1 ROM revision and reviewed disassembly source only as local inputs, then build a 6502-assembly-to-C90 static conversion path. Its deliverable is generated owner-local C translation units with source-address mapping, never a runtime CPU emulator.

## Candidate Scope

Define provenance, ROM identity handling, local paths, disassembly review, address map format, code/data coverage, generated-output containment, and probe budgets. Implement enough parser, symbol, and generator infrastructure to translate the boot/title dependency slice after the platform foundation exists.

## Admission Need

This candidate depends on the platform foundation. It requires explicit owner approval and source-policy review before it receives a numeric task identifier. Its acceptance is a repeatable local generator that emits C90 and a source-address map without tracked ROM derivatives.
