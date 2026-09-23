# Source Layout

## Current And Target Trees

```text
src/game/       portable translated logic and original RAM model
src/assets/     generated owner-local declarations; never tracked
src/validate/   owner-ROM reference adapters and trace comparison
src/platform/   win32, dos16, and other host adapters
src/main.c      composition root
test/           project-owned unit and integration harnesses
tools/          local generators and governance checks
```

## Files And Names

Translated files use subsystem names, not arbitrary ROM addresses. Every translated file or routine records its address provenance in an adjacent mapping record. Generated source remains beneath ignored `generated/`.

## Source Organization

`game/` cannot include host headers. `platform/` cannot mutate game internals. `validate/` is optional at runtime and cannot become the gameplay path.
