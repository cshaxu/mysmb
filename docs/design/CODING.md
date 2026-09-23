# Source Layout

## Current And Target Trees

```text
src/game/       portable translated logic and original RAM model
src/assets/     generated owner-local declarations; never tracked
src/validate/   owner-ROM reference adapters and trace comparison
src/platform/   dos16 first, then win32 and other host adapters
src/main.c      composition root
test/           project-owned unit and integration harnesses
tools/          local generators and governance checks
```

## Files And Names

Translated files use subsystem names, not arbitrary ROM addresses. Every translated file or routine records its address provenance in an adjacent mapping record. Generated source remains beneath ignored `generated/`.

## Source Organization

`game/` cannot include host headers. `platform/` cannot mutate game internals. `validate/` is optional at runtime and cannot become the gameplay path. The OpenNT 16-bit C compiler is the primary DOS build tool; it must produce a real-mode large-model MZ executable. Modern 32/64-bit compilers validate the same game sources.
