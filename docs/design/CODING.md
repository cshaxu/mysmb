# Source Layout

## Current And Target Trees

```text
src/game/       portable translated logic and original RAM model
src/assets/     generated owner-local declarations; never tracked
src/validate/   owner-ROM reference adapters and trace comparison
src/platform/   win32 and dos16 host adapters
src/main-*.c    one small composition root per host target
test/           project-owned unit and integration harnesses
tools/          local generators and governance checks
assets/         ignored local package outputs: mysmb16.exe, mysmb32.exe, mysmb64.exe
```

## Files And Names

Translated files use subsystem names, not arbitrary ROM addresses. Every translated file or routine records its address provenance in an adjacent mapping record. Generated source remains beneath ignored `generated/`.

## Source Organization

`game/` cannot include host headers or platform macros. `platform/` cannot mutate game internals. `validate/` is optional at runtime and cannot become the gameplay path. CMake selects `mysmb-win32-x86`, `mysmb-win32-x64`, or later `mysmb-dos16`; compile definitions are permitted only beneath the platform roots. The OpenNT 16-bit C compiler verifies the same core in real-mode large-model mode; the later DOS adapter owns linking the full MZ executable. Modern 32/64-bit compilers run the Win32 product.
